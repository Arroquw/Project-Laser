#include "ilda_reader.h"
#include "dac.h"
#include "i2c.h"
#include "GPIO.h"
#include "demo.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
 	gpioInit();
	i2cInit();
	generateSine();
	int n = 0;
	gpio0WritePin(21, 1);
	gpio0WritePin(22, 1);
	while(1) {
		startTransmit(n);
		n ^= 1;
	}
	return 0;
}
