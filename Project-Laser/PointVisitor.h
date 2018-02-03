#pragma once
#include "ildareader.h"

class PointVisitor {
public:
	virtual void visit(point2_d*) = 0;
	virtual void visit(palette*) = 0;
	virtual void visit(point3_d*) = 0;
	virtual void visit(point2_d_true*) = 0;
	virtual void visit(point3_d_true*) = 0;
};

/*
 * maak een afgeleide visitor klasse XVisitor
 *
 * Xvisitor visitor;
 * voor elke point object doe het volgende:
 * object->accept( visitor );
 */
