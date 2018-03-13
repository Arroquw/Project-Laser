#include "ilda_reader.h"
#include <stdio.h>
#include <GL/freeglut_std.h>

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutCreateWindow("ILDA file");
    glutDisplayFunc(read_ilda);
    glutMainLoop();
	//getchar();
}
