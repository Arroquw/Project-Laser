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
		points = new point_2d[hdr_.number_of_records];
		file.read(reinterpret_cast<char*>(points), hdr_.number_of_records);
		std::for_each(points, points + hdr_.number_of_records, [&](point_2d x) {std::cout << x.x_coord << std::endl; });
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

void ilda_reader::read_ilda_header(std::ifstream& ins) {
	ins.read(reinterpret_cast<char*>(&hdr_), sizeof header_ilda);
}

