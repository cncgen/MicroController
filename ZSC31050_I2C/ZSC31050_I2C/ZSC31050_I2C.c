/*
 * ZSC31050_I2C.c
 *
 * Created: 21.10.2015 12:56:21
 *  Author: tarek
 */ 


/*
 * Bachelor_uC_Programm.c
 *
 * Created: 09.01.2014 10:40:52
 *  Author: Rouven
 */ 

//F_CPU 14745600UL
#include <avr/io.h>
#include "config.h"
#include "ZSC31050.h"
#include <avr/interrupt.h>
#include "i2cmaster.h"
#include <util/delay.h>

void Clear(void);

volatile unsigned char received_command[41];
volatile unsigned char received_data_count;
unsigned char command;

int main(void)
{ 
	unsigned char check_write=0;
	
	DDRC &= ~(1 << DDC5); // SCL, Clear the PC5 pin, PC5 is now an input
	PORTC |= (1 << PORTC5); // SCL, turn On the Pull-up PC5 is now an input with pull-up enabled
	DDRC &= ~(1 << DDC4); // SDA
	PORTC |= (1 << PORTC4); // SDA
	
	Uartinit();												//UART initialisieren
	i2c_init();												//IIC initialisieren
	
	Clear();
	
	_delay_ms(30);
	Command_mode();											//ZSC31050 in Command Mode versetzen

	sei();
    while(1)
    {
		command=0;

		command =received_command[0] & 0xF0;		
		switch(command)										 
		{
					//bei Kommando READ_EEPROM_RAM Lesefunktion aufrufen
					case READ_EEPROM_RAM:	
											//RAM oder EEPROM auslesen																										
											Read_ZSC31050(received_command);																						
											Clear();											
											break;
										
					
					//bei Kommando WRITE_EEPROM_RAM Schreibfunktion aufrufen						
					case WRITE_EEPROM_RAM:	
											// RAM oder EEPROM beschreiben																																								
											check_write = Write_ZSC31050(received_command, received_data_count);	
											if (check_write)
											{
												Clear();
											}				
											break;
											
					//bei Kommando COPY Kopierfunktion aufrufen								
					case COPY:	
											// EEPROM in RAM oder RAM in EEPROM kopieren																							
											//Copy(received_command);				
											Clear();
											break;	
					
					//bei Kommando READ_OUTPUT Outputlesefunktion aufrufen				
					case READ_OUTPUT:	
											//Messwerte auslesen											
											received_data_count = 0;
											//Output(received_command);			
											Clear();											
											break;
					
		}	
    }
}

ISR(USART_RX_vect)
{
 	received_command[received_data_count] = UDR0;	
 	received_data_count++;
	if (received_command[received_data_count-1]==0xFE)
	Clear();
}

void Clear(void){
	
	for (unsigned char i = 0;i<41;i++)
	{
		received_command[i] = 0;
	}
	command = 0;
	received_data_count = 0;	
		
}