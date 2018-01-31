#include <iostream>
#include "ildareader.h" 

int main(int argc, char* argv[]) {
	ilda_reader a("../CanGoose.ild");
	a.read_file();
	std::cin.get();
}