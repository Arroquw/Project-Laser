/*
* ilda_reader.h
*
*  Created on: 3 Feb 2018
*      Author: Justi
*/

#ifndef PROJECT_LASER_ILDA_READER_H_
// ReSharper disable once CppInconsistentNaming
#define PROJECT_LASER_ILDA_READER_H_
#include <stdint.h>
#include <stdio.h>

/**
 * \brief byte typedef
 */
typedef unsigned char byte;

/**
 * \brief Data structure which contains the ilda header fields
 */
struct header_ilda {
	char ilda[4];
	byte format_code;
	char frame_name[9];
	char company_name[9];
	uint16_t number_of_records;
	uint16_t frame_number;
	uint16_t total_frames;
	byte proj_number;
};


/**
 * \brief Colour data structure for the true colour formats
 */
struct true_color {
	byte blue;
	byte green;
	byte red;
};

/**
 * \brief format 2, colour palette for the formats using colour index
 */
struct palette {
	byte blue;
	byte green;
	byte red;
};

/**
 * \brief format 1, size of 6 bytes. 2D point with colour index
 */
struct point2_d {
	int16_t x_coord;
	int16_t y_coord;
	byte status_code;
	byte color_index;
};

/**
 * \brief format 0, size of 8 bytes. 3D point with colour index
 */
struct point3_d {
	int16_t x_coord;
	int16_t y_coord;
	int16_t z_coord;
	byte status_code;
	byte color_index;
};

/**
 * \brief format 4, size of 10 bytes. 3D point with true colour structure.
 */
struct point3_d_true {
    int16_t x_coord;
    int16_t y_coord;
    int16_t z_coord;
    byte status_code;
    struct true_color colors;
};

/**
 * \brief format 5, size of 8 bytes. 2D point with true colour structure
 */
struct point2_d_true {
	int16_t x_coord;
	int16_t y_coord;
	byte status_code;
	struct true_color colors;
};

int read_ilda_header(struct header_ilda* hdr, FILE* ins);
int read3_dt(struct point3_d_true* point, FILE* ins);
int read2_dt(struct point2_d_true* point, FILE* ins);
int read3_d(struct point3_d* point, FILE* ins);
int read2_d(struct point2_d* point, FILE* ins);
int read_palette(struct palette* point, FILE* ins);
void render(int16_t x, int16_t y);
void read_ilda();
uint8_t getDataByte1(int cnt);
uint8_t getDataByte2(int cnt);
void generateSine();

#endif //PROJECT_LASER_ILDA_READER_H_
