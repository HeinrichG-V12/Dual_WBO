/*
 * config.h
 *
 * Created: 01.12.2021 11:08:45
 *  Author: Heinrich
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

#ifndef F_CPU
#warning "F_CPU war noch nicht definiert, wird nun mit 16MHz definiert"
#define F_CPU 16000000     /* Quarz mit 16 Mhz */
#endif

#ifndef FOSC
#warning "FOSC war noch nicht definiert, wird nun mit F_CPU/1000 definiert"
#define FOSC	F_CPU/1000
#endif

#ifndef CAN_BAUDRATE
#warning "CAN_BAUDRATE war noch nicht definiert, wird nun mit 500kbit definiert"
#define CAN_BAUDRATE	500
#endif



#endif /* CONFIG_H_ */