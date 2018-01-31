#pragma once
#include <iostream>
#include <fstream>

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

struct point_2d {
	int16_t x_coord;
	int16_t y_coord;
	byte status_code;
	byte color_index;
};

struct point_3d {
	int16_t x_coord;
	int16_t y_coord;
	int16_t z_coord;
	byte status_code;
	byte color_index;
};

class ilda_reader {
public:
	explicit ilda_reader(std::string);
	virtual ~ilda_reader();
	virtual void read_file();
private:
	virtual std::streamsize getFileSize(std::ifstream&);
	virtual std::ifstream& read_ilda_header(std::ifstream&);
	template<typename Word> std::ifstream& read_word(std::ifstream& ins, Word& value, unsigned size = sizeof Word);
	std::string path_;
	header_ilda hdr_;
	point_3d *points;
};

template<typename Word>
inline std::ifstream & ilda_reader::read_word(std::ifstream& ins, Word & value, unsigned size) {
	value = 0;
	
	for (unsigned n = 0; n < size; ++n) {
		Word x = ins.get() << 8*n;
		value |= x;
	
	}
	return ins;
}
