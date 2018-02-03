#include "ReadVisitor.h"
#include <iostream>
#include "ildareader.h"

ReadVisitor::ReadVisitor( std::ifstream& file) 
	: m_file(file), ir() {
}

void ReadVisitor::visit(point2_d* point) {
	ir.read_word(m_file, point->x_coord);
	ir.read_word(m_file, point->y_coord);
	ir.read_word(m_file, point->status_code);
	ir.read_word(m_file, point->color_index);
}

void ReadVisitor::visit(palette* point) {
	ir.read_word(m_file, point->blue);
	ir.read_word(m_file, point->green);
	ir.read_word(m_file, point->red);
}

void ReadVisitor::visit(point3_d* point) {
	ir.read_word(m_file, point->x_coord);
	ir.read_word(m_file, point->y_coord);
	ir.read_word(m_file, point->z_coord);
	ir.read_word(m_file, point->status_code);
	ir.read_word(m_file, point->color_index);
	std::cout << static_cast<int>(point->status_code >> 6) << std::endl;
}

void ReadVisitor::visit(point2_d_true* point) {
	ir.read_word(m_file, point->x_coord);
	ir.read_word(m_file, point->y_coord);
	ir.read_word(m_file, point->status_code);
	ir.read_word(m_file, point->colors);
}

void ReadVisitor::visit(point3_d_true* point) {
	ir.read_word(m_file, point->x_coord);
	ir.read_word(m_file, point->y_coord);
	ir.read_word(m_file, point->z_coord);
	ir.read_word(m_file, point->status_code);
	ir.read_word(m_file, point->colors);
}

