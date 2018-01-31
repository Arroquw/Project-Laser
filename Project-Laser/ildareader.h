#pragma once
#include <iostream>
#include <fstream>

typedef unsigned char byte;

struct header_ilda {
	char ilda[4];
	byte reserved[3];
	byte format_code;
	char frame_name[8];
	char company_name[8];
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
	uint16_t x_coord;
	uint16_t y_coord;
	byte status_code;
	true_color colors;
};

class ilda_reader {
public:
	explicit ilda_reader(std::string);
	virtual ~ilda_reader();
	virtual void read_file();
private:
	virtual std::streamsize getFileSize(std::ifstream&);
	virtual void read_ilda_header(std::ifstream&);
	template<typename Word> std::ifstream& read_word(std::ifstream& ins, Word& value, unsigned size = sizeof Word);
	std::string path_;
	header_ilda hdr_;
	point_2d *points;
};

template<typename Word>
inline std::ifstream & ilda_reader::read_word(std::ifstream& ins, Word & value, unsigned size) {
	value = 0;
	for (unsigned n = 0; n < size; ++n) {
		value |= ins.get() << (8*n);
	}
	return ins;
}
