#include "angles.h"
#include <stdint.h>

float processAngle(const int16_t coord) {
    const float constant = 16 / 65535;
    const float retValue = coord * constant;
    return 45 + retValue;
}

float convertToVoltage(float angle) {
    return angle / 2;
}
