/*
* ilda_reader.h
*
*  Created on: 3 Feb 2018
*      Author: Justi
*/

#ifndef ILDA_READER_H_
#define ILDA_READER_H_
#include <stdint.h>
#include <stdio.h>
typedef unsigned char byte;

struct header_ilda {
	char ilda[5];
	byte reserved[3];
	byte format_code;
	char frame_name[9];
	char company_name[9];
	uint16_t number_of_records;
	uint16_t frame_number;
	uint16_t total_frames;
	byte proj_number;
	byte reserved2;
};

struct true_color {
	byte blue;
	byte green;
	byte red;
};

struct palette {
	byte blue;
	byte green;
	byte red;
};

struct point2_d {
	int16_t x_coord;
	int16_t y_coord;
	byte status_code;
	byte color_index;
};

struct point3_d {
	int16_t x_coord;
	int16_t y_coord;
	int16_t z_coord;
	byte status_code;
	byte color_index;
};

struct point2_d_true {
	int16_t x_coord;
	int16_t y_coord;
	byte status_code;
	struct true_color colors;
};

struct point3_d_true {
	int16_t x_coord;
	int16_t y_coord;
	int16_t z_coord;
	byte status_code;
	struct true_color colors;
};

void read_ilda_header(FILE* ins, struct header_ilda* hdr);
void read3_dt(struct point3_d_true* point, FILE* ins);
void read2_dt(struct point2_d_true* point, FILE* ins);
void read3_d(struct point3_d* point, FILE* ins);
void read2_d(struct point2_d* point, FILE* ins);
void read_palette(struct palette* point, FILE* ins);
void read_ilda();


#endif /* ILDA_READER_H_ */
