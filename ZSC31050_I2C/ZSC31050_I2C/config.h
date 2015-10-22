/*
 * config.h
 *
 * Created: 09.01.2014 10:51:22
 *  Author: Rouven
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

#define BAUD                9600UL					//geforderte BaUDR0ate
#define F_CPU				16000000UL// 14745600UL				//Taktfrequenz
				
#define READ_EEPROM_RAM     0x10					//Befehl aus RAM oder EEPROM zu lesen
#define WRITE_EEPROM_RAM    0x20					//Befehl in RAM oder EEPROM zu schreiben
#define COPY                0x30					//Befehl zum Kopieren
#define READ_OUTPUT         0x40					//Befehl zum Messwerte auslesen

void Uartinit (void);

#endif /* CONFIG_H_ */