#include <iostream>
#include <fstream>

typedef unsigned char byte;

struct header_ilda {
	char ilda[4];
	byte format_code;
	char frame_name[8];
	char company_name[8];
	uint16_t number_of_records;
	uint16_t frame_number;
	uint16_t total_frames;
	byte proj_number = 0;
};

class ilda_reader {
public:
	ilda_reader();
private:
	header_ilda hdr_;

};
