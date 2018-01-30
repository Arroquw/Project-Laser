#include <iostream>
#include <fstream>
#include <string>

typedef unsigned char byte;

struct ilda_header {
	char ilda[4];
	byte format_code[4];
};

struct true_color {
	byte red;
	byte green;
	byte blue;
};

class header_true_color {
	char ilda_[4];
	byte format_code_[4];
	uint32_t data_length_;
	uint32_t colors_;
	true_color color_[];
};

struct point_2_d {
	int16_t x_coord;
	int16_t y_coord;
	int16_t status;
};

struct header_2_d {
	char ilda[4];
	byte format_code[4];
	std::string frame_name;
	std::string company_name;
	uint16_t points;
	uint16_t frame_number;
	uint16_t frames;
	byte head;
	byte future;
	point_2_d point[];
};

class header2d {
public:
	header2d stream(std::ifstream& str);
private:
	byte* hdr_;
};

header2d header2d::stream(std::ifstream & str) {
	str.read(hdr_.ilda, sizeof hdr_.ilda);
	str.read(hdr_.format_code, sizeof hdr_.format_code);
	if( 0 != strncmp(hdr_.ilda, "ILDA", sizeof hdr_.ilda) || hdr_.format_code[3] != 1){
		str.reset(sizeof hdr_.ilda + sizeof hdr_.format_code);
		return;
	}
	str.read(hdr_.frame_name, sizeof hdr_.frame_name);
	str.read(hdr_.company_name, sizeof hdr_.company_name);
	str << points;
	str << frame_number;
	str << frames;
	str << head;
	str << future;
}

void create(ifstream file) {
	while (!file.eof()) {
		
	}
}

int main(int argc, char* argv[]) {
	try {
		ifstream ilda(argv[1]);
		ilda_header *headers = create(ilda);
		while (headers != nullptr);
	} catch (...) {
		const char* usage = 
			"ildareader <ilda file> \n"
			" \n"
			" \n"
			" \n"
			" \n"
			" \n"
			" \n"
			" \n"
			" \n";

		std::cout << usage;
	}
}