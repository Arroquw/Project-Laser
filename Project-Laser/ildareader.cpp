#include "ildareader.h"
#include <algorithm>

ilda_reader::ilda_reader(std::string read) {
	path_ = read;
}

ilda_reader::~ilda_reader() {
	if (points != nullptr) {
		delete[] points;
	}
}

void ilda_reader::read_file() {
	std::ifstream file(path_, std::ios::binary);
	if (file.is_open()) {
		auto size = getFileSize(file);
		read_ilda_header(file);
		std::cout << hdr_.ilda << std::endl;
		std::cout << (int)hdr_.format_code << std::endl;
		std::cout << hdr_.frame_name << std::endl;
		std::cout << hdr_.company_name << std::endl;
		std::cout << hdr_.number_of_records << std::endl;
		std::cout << hdr_.frame_number << std::endl;
		std::cout << hdr_.total_frames << std::endl;
		std::cout << (int)hdr_.proj_number << std::endl;

		auto pts = hdr_.number_of_records;
		points = new point_3d[pts];
		int i = 0;
		byte x = 0;
		std::cout << file.tellg() << std::endl;
		do {
			file.read(reinterpret_cast<char*>(points)+(i*sizeof point_3d), sizeof point_3d);
			x = points[i].status_code >> 7;
			std::cout << (int)x << std::endl;
			i++;
		} while (x < 0b1);
		std::cout << (int)points[i-1].status_code << std::endl << i;
	} else {
		std::cout << "File not found!" << std::endl;
	}
}

std::streamsize ilda_reader::getFileSize(std::ifstream &ins) {
	ins.ignore(std::numeric_limits<std::streamsize>::max());
	const auto length = ins.gcount();
	ins.clear();
	ins.seekg(0, std::ios::beg);
	return length;
}

std::ifstream& ilda_reader::read_ilda_header(std::ifstream& ins) {
	ins.read(hdr_.ilda, sizeof hdr_.ilda-1);
	hdr_.ilda[4] = '\0';
	ins.ignore(sizeof hdr_.reserved);
	read_word(ins, hdr_.format_code);
	ins.read(hdr_.frame_name, sizeof hdr_.frame_name -1);
	hdr_.frame_name[8] = '\0';
	ins.read(hdr_.company_name, sizeof hdr_.company_name -1);
	hdr_.company_name[8] = '\0';
	read_word(ins, hdr_.number_of_records);
	read_word(ins, hdr_.frame_number);
	read_word(ins, hdr_.total_frames);
	read_word(ins, hdr_.proj_number);
	ins.ignore(sizeof hdr_.reserved2);
	return ins;
}
