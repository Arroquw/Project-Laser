#include "ildareader.h"
#include <string>
#include <limits>
#include <iostream>
#include "PointVisitor.h"
#include "ReadVisitor.h"
#include <vector>

ilda_reader::ilda_reader(const std::string read) {
	path_ = read;
}

ilda_reader::~ilda_reader() {
}

void ilda_reader::read_file() {
	std::ifstream file(path_, std::ios::binary);
	if (file.is_open()) {
		read_ilda_header(file, hdr_);
		std::cout << hdr_.ilda << std::endl;
		std::cout << static_cast<int>(hdr_.format_code) << std::endl;
		std::cout << hdr_.frame_name << std::endl;
		std::cout << hdr_.company_name << std::endl;
		std::cout << hdr_.number_of_records << std::endl;
		std::cout << hdr_.frame_number << std::endl;
		std::cout << hdr_.total_frames << std::endl;
		std::cout << static_cast<int>(hdr_.proj_number) << std::endl;

		const auto pts = hdr_.number_of_records;
		std::vector<point*> points(pts);
		switch (hdr_.format_code) {
		//case 0: points.push_back(new point3_d[pts]); break;
		case 0: for(auto i = 0u; i < pts; ++i) {
			points[i] = new point3_d();
		}break;
		case 1: for (auto i = 0u; i < pts; ++i) {
			points[i] = new point2_d();
		}break;
		case 2: for (auto i = 0u; i < pts; ++i) {
			points[i] = new palette();
		}break;
		case 4: for (auto i = 0u; i < pts; ++i) {
			points[i] = new point2_d_true();
		}break;
		case 5: for (auto i = 0u; i < pts; ++i) {
			points[i] = new point3_d_true();
		}break;
		default: throw std::exception("");
		}
		ReadPoint(file, points);
	} else {
		std::cout << "File not found!" << std::endl;
	}
}

std::streamsize ilda_reader::GetFileSize(std::ifstream &ins) {
	ins.ignore(std::numeric_limits<std::streamsize>::max());
	const auto length = ins.gcount();
	ins.clear();
	ins.seekg(0, std::ios::beg);
	return length;
}

std::ifstream& ilda_reader::read_ilda_header(std::ifstream& ins, header_ilda& hdr) {
	ins.read(hdr.ilda, sizeof hdr.ilda - 1);
	hdr.ilda[4] = '\0';
	ins.ignore(sizeof hdr.reserved);
	read_word(ins, hdr.format_code);
	ins.read(hdr.frame_name, sizeof hdr.frame_name - 1);
	hdr.frame_name[8] = '\0';
	ins.read(hdr.company_name, sizeof hdr.company_name - 1);
	hdr.company_name[8] = '\0';
	read_word(ins, hdr.number_of_records);
	read_word(ins, hdr.frame_number);
	read_word(ins, hdr.total_frames);
	read_word(ins, hdr.proj_number);
	ins.ignore(sizeof hdr.reserved2);
	return ins;
}

point* ilda_reader::ReadPoint(std::ifstream& file, std::vector<point*> &points) {
	auto i = 0;
	//byte x;
	ReadVisitor visitor(file);
	std::cout << file.tellg() << std::endl;
	do {
		points[i++]->accept(visitor);
	} while (i < hdr_.number_of_records && !file.eof());
	read_ilda_header(file, eof_hdr_);
	std::cout << eof_hdr_.company_name << std::endl;
	return points[0];
}

void palette::accept(PointVisitor& visitor) {
	visitor.visit(this);
}

void point2_d::accept(PointVisitor & visitor) {
	visitor.visit(this);
}

void point3_d::accept(PointVisitor& visitor) {
	visitor.visit(this);
}

void point2_d_true::accept(PointVisitor& visitor) {
	visitor.visit(this);
}

void point3_d_true::accept(PointVisitor& visitor) {
	visitor.visit(this);
}


