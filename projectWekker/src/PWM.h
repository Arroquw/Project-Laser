// defines
#define PCONP 				(*(unsigned int *)	0x400FC0C4)
#define PCLKSEL0			(*(unsigned int *)	0x400FC1A8)

#define PINSEL0				(*(unsigned int *)	0x4002C000)
#define PINSEL4 			(*(unsigned int *)	0x4002C010)
#define PINMODE4			(*(unsigned int *)	0x4002C050)

#define PWM1MCR 			(*(unsigned int *)	0x40018014)
#define PWM1TCR				(*(unsigned int *)	0x40018004)
#define PWM1PR				(*(unsigned int *)	0x4001800C)
#define PWM1MR0				(*(unsigned int *)	0x40018018)
#define PWM1MR3 			(*(unsigned int *)	0x40018024)
#define PWM1PCR 			(*(unsigned int *)	0x4001804C)
#define PWM1LER				(*(unsigned int *)	0x40018050)

// methods
void pwmInit();
void pwmOn();
void pwmOff();
