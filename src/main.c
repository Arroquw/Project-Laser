#include "ilda_reader.h"
#include "dac.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	i2cInit();

	while(1) {
		startTransmit();
	}
	return 0;
}
