#include "ilda_reader.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HEADER_SIZE 32

/**
 * \brief Host endianness. File is in big endian so then conversions are in order.
 */
#define LITTLE_ENDIAN 1
/**
 * \brief amount to shift least significant byte, for endianness conversions
 */
#define B 8*LITTLE_ENDIAN
/**
 * \brief amount to shift most significant byte, for endianness conversions
 */
#define L 8*(!LITTLE_ENDIAN)

void print_header(struct header_ilda hdr);

int read3_d(struct point3_d* point, FILE* ins) {
    uint8_t buffer[sizeof(struct point3_d)];
    if (fread(buffer, 1, sizeof buffer, ins) != sizeof buffer) {
        return -1;
    }
    point->x_coord = buffer[0] << B | buffer[1] << L;
    point->y_coord = buffer[2] << B | buffer[3] << L;
    point->z_coord = buffer[4] << B | buffer[5] << L;
    point->status_code = buffer[6];
    point->color_index = buffer[7];
    return 0;
}

int read2_d(struct point2_d* point, FILE* ins) {
    uint8_t buffer[sizeof(struct point2_d)];
    if (fread(buffer, 1, sizeof buffer, ins) != sizeof buffer) {
        return -1;
    }
    point->x_coord = buffer[0] << B | buffer[1] << L;
    point->y_coord = buffer[2] << B | buffer[3] << L;
    point->status_code = buffer[4];
    point->color_index = buffer[5];
    return 0;
}

int read_palette(struct palette* point, FILE* ins) {
    uint8_t buffer[sizeof(struct palette)];
    if (fread(buffer, 1, sizeof buffer, ins) != sizeof buffer) {
        return -1;
    }
    point->blue = buffer[0];
    point->green = buffer[1];
    point->red = buffer[2];
    return 0;
}

int read3_dt(struct point3_d_true* point, FILE* ins) {
    uint8_t buffer[sizeof(struct point3_d_true)];
    if (fread(buffer, 1, sizeof buffer, ins) != sizeof buffer) {
        return -1;
    }
    point->x_coord = buffer[0] << B | buffer[1] << L;
    point->y_coord = buffer[2] << B | buffer[3] << L;
    point->z_coord = buffer[4] << B | buffer[5] << L;
    point->status_code = buffer[6];
    memcpy(buffer + 7, &point->colors, 3);
    return 0;
}

int read2_dt(struct point2_d_true* point, FILE* ins) {
    uint8_t buffer[sizeof(struct point2_d_true)];
    if (fread(buffer, 1, sizeof buffer, ins) != sizeof buffer) {
        return -1;
    }
    point->x_coord = buffer[0] << B | buffer[1] << L;
    point->y_coord = buffer[2] << B | buffer[3] << L;
    point->status_code = buffer[4];
    memcpy(buffer + 5, &point->colors, 3);
    return 0;
}

int read_ilda_header(FILE* ins, struct header_ilda *hdr) {
    uint8_t buffer[HEADER_SIZE];
    if (fread(buffer, 1, sizeof buffer, ins) != sizeof buffer) {
        return -1;
    }
    memcpy(hdr->ilda, buffer, 4);   // first 4 characters contain ilda
    hdr->ilda[4] = '\0';            // terminating null character for C-string
    hdr->format_code = buffer[7];   // bytes 4 to 6 are reserved so continue on byte 7
    memcpy(hdr->frame_name, buffer + 8, 8); // 8 ascii characters
    hdr->frame_name[8] = '\0';
    memcpy(hdr->company_name, buffer + 16, 8);
    hdr->company_name[8] = '\0';
    hdr->number_of_records = buffer[24] << B | buffer[25] << L; // 16 bit integer with endian conversion, entire file is in big endian
    hdr->frame_number = buffer[26] << B | buffer[27] << L;  
    hdr->total_frames = buffer[28] << B | buffer[29] << L;
    hdr->proj_number = buffer[30];
    return 0;
}

void read_ilda() {
    FILE* fp = fopen("../Ladylegs.ild", "rb");
    if (fp != NULL) {
        struct header_ilda hdr;
        read_ilda_header(fp, &hdr);
        print_header(hdr);
        while (hdr.number_of_records != 0) {
            switch (hdr.format_code) {
            case 0:
            {
                struct point3_d point = { 0 };
                for (; point.status_code >> 7 != 1;) {
                    read3_d(&point, fp);
                    printf("x coord: %d\ny coord: %d\nz_coord: %d\nstatus code: %d\ncolor index: %d\n", point.x_coord, point.y_coord, point.z_coord, point.status_code, point.color_index);
                }
                read_ilda_header(fp, &hdr);
                print_header(hdr);
                break;
            }
            case 1:
            {
                struct point2_d point = { 0 };
                for (; point.status_code >> 7 != 1;) {
                    read2_d(&point, fp);
                    printf("x coord: %d\ny coord: %d\nstatus code: %d\ncolor index: %d\n", point.x_coord, point.y_coord, point.status_code, point.color_index);
                }
                read_ilda_header(fp, &hdr);
                print_header(hdr);
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
                print_header(hdr);
                break;
            }
            case 4:
            {
                struct point3_d_true point = { 0 };
                for (; point.status_code >> 7 != 1;) {
                    read3_dt(&point, fp);
                    printf("x coord: %d\ny coord: %d\nz_coord: %d\nstatus code: %d\ncolor index: %d\n", point.x_coord, point.y_coord, point.z_coord, point.status_code, point.colors.blue);

                }
                read_ilda_header(fp, &hdr);
                print_header(hdr);
                break;
            }
            case 5:
            {
                struct point2_d_true point = { 0 };
                for (; point.status_code >> 7 != 1;) {
                    read2_dt(&point, fp);
                    printf("x coord: %d\ny coord: %d\nstatus code: %d\nblue: %d\n", point.x_coord, point.y_coord, point.status_code, point.colors.blue);
                }
                read_ilda_header(fp, &hdr);
                print_header(hdr);
                break;
            }
            default: break;
            }
            if (feof(fp)) {
                break;
            } else if (ferror(fp)) {
                break;
            }
        }
        fclose(fp);
    } else {
        printf("%s\n", "file not found");
        exit(-1);
    }
}
void print_header(const struct header_ilda hdr) {
    printf("%s\n%d\n%s\n%s\n%d\n%d\n%d\n%d\n", hdr.ilda, hdr.format_code, hdr.frame_name, hdr.company_name, hdr.number_of_records, hdr.frame_number, hdr.total_frames, hdr.proj_number);
    getchar();
}
