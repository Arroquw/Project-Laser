#include "ilda_reader.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * \brief since the file is in big endian, conversions have to be in place for little endian cpu's
 */
#define LITTLE_ENDIAN 1 //endianness of host

/**
 * \brief amount to shift least significant byte, for endianness conversions 
 */
#define B (8*LITTLE_ENDIAN)
/**
 * \brief amount to shift most significant byte, for endianness conversions
 */
#define L (8*(!LITTLE_ENDIAN))

void print_header(const struct header_ilda hdr);

/**
* \brief Reads from a file into a point3_d POD structure, should be called if format code '0' is encountered
* \param point point3_d POD structure to read into. Does not need to be initialized.
* \param ins File descriptor to read from. Needs to be opened in binary read mode
* \return returns -1 on read failure and 0 on success.
*/
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

/**
* \brief Reads from a file into a point2_d POD structure, should be called if format code '1' is encountered
* \param point point2_d POD structure to read into. Does not need to be initialized.
* \param ins File descriptor to read from. Needs to be opened in binary read mode
* \return returns -1 on read failure and 0 on success.
*/
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

/**
* \brief Reads from a file into a palette POD structure, should be called if format code '2' is encountered
* \param point palette POD structure to read into. Does not need to be initialized.
* \param ins File descriptor to read from. Needs to be opened in binary read mode
* \return returns -1 on read failure and 0 on success.
*/
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

/**
* \brief Reads from a file into a point3_d_true POD structure, should be called if format code '4' is encountered
* \param point point3_d_true POD structure to read into. Does not need to be initialized.
* \param ins File descriptor to read from. Needs to be opened in binary read mode
* \return returns -1 on read failure and 0 on success.
*/
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

/**
 * \brief Reads from a file into a point2_d_true POD structure, should be called if format code '5' is encountered
 * \param point point2_d_true POD structure to read into. Does not need to be initialized.
 * \param ins File descriptor to read from. Needs to be opened in binary read mode
 * \return returns -1 on read failure and 0 on success.
 */
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

/**
 * \brief Puts ilda header information in the *hdr parameter from the ins* file.
 * \param hdr ilda header POD structure to put data in. Does not need to be initialized.
 * \param ins file descriptor to read from. Needs to be opened in binary read mode.
 * \return returns 0 for success, -1 if read failed, 1 if ILDA header is not recognized and 2 if the final header has been found.
 */
int read_ilda_header(struct header_ilda *hdr, FILE* ins) {
    uint8_t buffer[32];
    if (fread(buffer, 1, sizeof buffer, ins) != sizeof buffer) {
        return -1;
    }
    memcpy(hdr->ilda, buffer, sizeof hdr->ilda);
    if (strncmp(hdr->ilda, "ILDA", sizeof hdr->ilda) != 0) {
        return 1;
    }
    hdr->format_code = buffer[7];
    if (hdr->format_code > 5) {
        hdr->format_code = 0;
    }
    for (auto i = 8u; i < 8 + sizeof hdr->frame_name || buffer[i] == '\0'; ++i) {
        hdr->frame_name[i - 8] = buffer[i];
    }
    for (auto i = 16u; i < 16 + sizeof hdr->frame_name || buffer[i] == '\0'; ++i) {
        hdr->company_name[i - 16] = buffer[i];
    }
    hdr->frame_name[8] = '\0';
    hdr->company_name[8] = '\0';

    hdr->number_of_records = buffer[24] << B | buffer[25] << L; // 16 bit integer with endian conversion, entire file is in big endian
    if (hdr->number_of_records == 0) {
        return 2;
    }
    hdr->frame_number = buffer[26] << B | buffer[27] << L;
    hdr->total_frames = buffer[28] << B | buffer[29] << L;
    hdr->proj_number = buffer[30];
    return 0;
}

/**
 * \brief reads the whole ilda file and prints it on the console. Does not buffer anything. Will exit if file is not found.
 */
void read_ilda() {
    FILE* fp = fopen("../CanadaFlag.ild", "rb");  // NOLINT(android-cloexec-fopen)
    int n = 0;
    if (fp != NULL) {
		struct header_ilda hdr = { 0 };
        if (read_ilda_header(&hdr, fp) == 0) {
            while (hdr.number_of_records != 0) {
                switch (hdr.format_code) {
                case 0:
                {
                    struct point3_d point = { 0 };
                    for (; (point.status_code >> 7 & 1) != 1;) {
                        read3_d(&point, fp);
                        printf("x coord: %d\ny coord: %d\nz_coord: %d\nstatus code: %d\ncolor index: %d\n", point.x_coord, point.y_coord, point.z_coord, point.status_code, point.color_index);
                    }
                    n++;
                    read_ilda_header(&hdr, fp);
                    break;
                }
                case 1:
                {
                    struct point2_d point = { 0 };
                    for (; (point.status_code >> 7 & 1) != 1;) {
                        read2_d(&point, fp);
                        printf("x coord: %d\ny coord: %d\nstatus code: %d\ncolor index: %d\n", point.x_coord, point.y_coord, point.status_code, point.color_index);
                    }
                    read_ilda_header(&hdr, fp);
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
                    read_ilda_header(&hdr, fp);
                    print_header(hdr);
                    break;
                }
                case 4:
                {
                    struct point3_d_true point = { 0 };
                    for (; (point.status_code >> 7 & 1) != 1;) {
                        read3_dt(&point, fp);
                        printf("x coord: %d\ny coord: %d\nz_coord: %d\nstatus code: %d\ncolor index: %d\n", point.x_coord, point.y_coord, point.z_coord, point.status_code, point.colors.blue);

                    }
                    read_ilda_header(&hdr, fp);
                    print_header(hdr);
                    break;
                }
                case 5:
                {
                    struct point2_d_true point = { 0 };
                    for (; (point.status_code >> 7&1) != 1;) {
                        read2_dt(&point, fp);
                        printf("x coord: %d\ny coord: %d\nstatus code: %d\nblue: %d\n", point.x_coord, point.y_coord, point.status_code, point.colors.blue);
                    }
                    read_ilda_header(&hdr, fp);
                    print_header(hdr);
                    break;
                }
                default: break;
                }
                if (feof(fp)) {
                    break;
                } 
                if (ferror(fp)) {
                    break;
                }
            }
            fclose(fp);
        } else {
            printf("%s\n", "file not found");
            exit(-1);
        }
    }
}

void print_header(const struct header_ilda hdr) {
    printf("%s\n%d\n%s\n%s\n%d\n%d\n%d\n%d\n", hdr.ilda, hdr.format_code, hdr.frame_name, hdr.company_name, hdr.number_of_records, hdr.frame_number, hdr.total_frames, hdr.proj_number);
  //  getchar();
}
