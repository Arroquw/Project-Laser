#include "ilda_reader.h"
#include <stdio.h>

#ifdef BIG_ENDIAN
#define B 8
#define L 0
#elif LITTLE_ENDIAN
#define B 0
#define L 8
#else
#define B 8
#define L 0
#endif

void read3_dt(struct point3_d_true* point, FILE* ins) {
	uint8_t buffer[sizeof(struct point3_d_true)];
	fread(buffer, sizeof(struct point3_d_true), 1, ins);
	point->x_coord = buffer[0] << B | buffer[1] << L;
	point->y_coord = buffer[2] << B | buffer[3] << L;
	point->z_coord = buffer[4] << B | buffer[5] << L;
	point->status_code = buffer[6];
	point->colors.blue = buffer[7];
	point->colors.green = buffer[8];
	point->colors.red = buffer[9];
}

void read2_dt(struct point2_d_true* point, FILE* ins) {
	uint8_t buffer[sizeof(struct point2_d_true)];
	fread(buffer, sizeof(struct point2_d_true), 1, ins);
	point->x_coord = buffer[0] << B | buffer[1] << L;
	point->y_coord = buffer[2] << B | buffer[3] << L;
	point->status_code = buffer[4];
	point->colors.blue = buffer[5];
	point->colors.green = buffer[6];
	point->colors.red = buffer[7];
}

void read3_d(struct point3_d* point, FILE* ins) {
	uint8_t buffer[sizeof(struct point3_d)];
	fread(buffer, sizeof(struct point3_d), 1, ins);
	point->x_coord = buffer[0] << B | buffer[1] << L;
	point->y_coord = buffer[2] << B | buffer[3] << L;
	point->z_coord = buffer[4] << B | buffer[5] << L;
	point->status_code = buffer[6];
	point->color_index = buffer[7];
}

void read2_d(struct point2_d* point, FILE* ins) {
	uint8_t buffer[sizeof(struct point2_d)];
	fread(buffer, sizeof(struct point2_d), 1, ins);
	point->x_coord = buffer[0] << B | buffer[1] << L;
	point->y_coord = buffer[2] << B | buffer[3] << L;
	point->status_code = buffer[4];
	point->color_index = buffer[5];
}

void read_palette(struct palette* point, FILE* ins) {
	uint8_t buffer[sizeof(struct palette)];
	fread(buffer, sizeof(struct palette), 1, ins);
	point->blue = buffer[0];
	point->green = buffer[1];
	point->red = buffer[2];
}

void read_ilda_header(FILE* ins, struct header_ilda *hdr) {
	fread(hdr->ilda, sizeof(hdr->ilda[0]), sizeof hdr->ilda - 1, ins);
	hdr->ilda[4] = '\0';
	fread(hdr->reserved, sizeof(hdr->reserved[0]), sizeof hdr->reserved, ins);
	fread(&hdr->format_code, sizeof hdr->format_code, 1, ins);
	fread(hdr->frame_name, sizeof(hdr->frame_name[0]), sizeof hdr->frame_name - 1, ins);
	hdr->frame_name[8] = '\0';
	fread(hdr->company_name, sizeof(hdr->company_name[0]), sizeof hdr->company_name - 1, ins);
	hdr->company_name[8] = '\0';
	fread(&hdr->number_of_records, sizeof hdr->number_of_records, 1, ins);
	fread(&hdr->frame_number, sizeof hdr->frame_number, 1, ins);
	fread(&hdr->total_frames, sizeof hdr->total_frames, 1, ins);
	fread(&hdr->proj_number, sizeof hdr->proj_number, 1, ins);
	fread(&hdr->reserved2, sizeof hdr->reserved2, 1, ins);
}

void read_ilda() {
	FILE* fp = fopen("C:/Users/Justi/Documents/GitHub/Project-Laser/Ladylegs.ild", "rb");
	struct header_ilda hdr;
	read_ilda_header(fp, &hdr);
	printf("%s\n%d\n%s\n%s\n%d\n%d\n%d\n%d\n", hdr.ilda, hdr.format_code, hdr.company_name, hdr.frame_name, hdr.number_of_records, hdr.frame_number, hdr.total_frames, hdr.proj_number);
	while (hdr.number_of_records != 0) {
		switch (hdr.format_code) {
		case 0:
		{
			struct point3_d point = { 0 };
			for (;point.status_code >> 7 != 1;) {
				read3_d(&point, fp);
				printf("x coord: %d\ny coord: %d\nz_coord: %d\nstatus code: %d\ncolor index: %d\n", point.x_coord, point.y_coord, point.z_coord, point.status_code, point.color_index);
			}
			read_ilda_header(fp, &hdr);
			break;
		}
		case 1:
		{
			struct point2_d point = { 0 };
			for (;point.status_code >> 7 != 1;) {
				read2_d(&point, fp);
				printf("x coord: %d\ny coord: %d\nstatus code: %d\ncolor index: %d\n", point.x_coord, point.y_coord, point.status_code, point.color_index);
			}
			read_ilda_header(fp, &hdr);
			break;
		}
		case 2:
		{
			struct palette point = { 0 };
			for (int i = 0; i < hdr.number_of_records; ++i) {
				read_palette(&point, fp);
				printf("blue: %d\ngreen: %d\nred: %d\n", point.blue, point.green, point.red);
			}
			read_ilda_header(fp, &hdr);
			break;
		}
		case 4:
		{
			struct point2_d_true point = { 0 };
			for (;point.status_code >> 7 != 1;) {
				read2_dt(&point, fp);
				printf("x coord: %d\ny coord: %d\nstatus code: %d\nblue: %d\n", point.x_coord, point.y_coord, point.status_code, point.colors.blue);
			}
			read_ilda_header(fp, &hdr);
			break;
		}
		case 5:
		{
			struct point3_d_true point = { 0 };
			for (;point.status_code >> 7 != 1;) {
				read3_dt(&point, fp);
				printf("x coord: %d\ny coord: %d\nz_coord: %d\nstatus code: %d\ncolor index: %d\n", point.x_coord, point.y_coord, point.z_coord, point.status_code, point.colors.blue);
			}
			read_ilda_header(fp, &hdr);
			break;
		}
		default: break;
		}
	}
	fclose(fp);
}
