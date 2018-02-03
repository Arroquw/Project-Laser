#pragma once
#include <fstream>
#include <vector>

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

class PointVisitor;

struct point {
	virtual ~point() = default;
	virtual void accept(PointVisitor&) = 0;
};

struct true_color {
	byte blue;
	byte green;
	byte red;
};

struct palette : point {
	byte blue;
	byte green;
	byte red;
	void accept(PointVisitor& visitor) override;
};

struct point2_d : point {
	int16_t x_coord;
	int16_t y_coord;
	byte status_code;
	byte color_index;
	void accept(PointVisitor& visitor) override;
};

struct point3_d : point {
	int16_t x_coord;
	int16_t y_coord;
	int16_t z_coord;
	byte status_code;
	byte color_index;
	void accept(PointVisitor& visitor) override;
};

struct point2_d_true : point {
	int16_t x_coord;
	int16_t y_coord;
	byte status_code;
	true_color colors;
	void accept(PointVisitor& visitor) override;
};

struct point3_d_true : point{
	int16_t x_coord;
	int16_t y_coord;
	int16_t z_coord;
	byte status_code;
	true_color colors;
	void accept(PointVisitor& visitor) override;
};

class ilda_reader {
public:
	explicit ilda_reader(std::string);
	ilda_reader() = default;
	virtual ~ilda_reader();
	virtual void read_file();
	template<typename Word> std::ifstream& read_word(std::ifstream& ins, Word& value, unsigned size = sizeof Word);
private:
	virtual std::streamsize GetFileSize(std::ifstream&);
	virtual std::ifstream& read_ilda_header(std::ifstream&, header_ilda& hdr);
	virtual point* ReadPoint(std::ifstream&, std::vector<point*>&);
	std::string path_;
	header_ilda hdr_;
	header_ilda eof_hdr_;
};

template<typename Word>
std::ifstream & ilda_reader::read_word(std::ifstream& ins, Word & value, const unsigned size) {
	value = 0;
	for (unsigned n = 0; n < size; ++n) {
		Word x = ins.get() << 8*n;
		value |= x;
	}
	return ins;
}
