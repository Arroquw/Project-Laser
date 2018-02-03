#pragma once

#include "PointVisitor.h"

class ReadVisitor : public PointVisitor {
public:
	explicit ReadVisitor( std::ifstream& );
	void visit(point2_d*) override;
	void visit(palette*) override;
	void visit(point3_d*) override;
	void visit(point2_d_true*) override;
	void visit(point3_d_true*) override;
private:
	std::ifstream& m_file;
	ilda_reader ir;
};