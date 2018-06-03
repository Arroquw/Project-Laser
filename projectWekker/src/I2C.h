#ifndef I2C_H_
#define I2C_H_

// defines
#define P					0x400F0000
#define EXTMODE				(*(unsigned int *)	0x400FC148)


// methods
int rtcRead(int i);
void rtcWrite(int hourdec1, int mindec2);
void setAlarm(int aan, int hour, int minutes);
void i2cInit();
void startTransmit();
void startReceive();

#endif /* I2C_H_ */
