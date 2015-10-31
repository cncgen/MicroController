/*
 * ZSC31050.c
 *
 * Created: 21.01.2014 10:13:38
 *  Author: Rouven
 * Überarbeitet von Tarek Meftah
 */ 

#include "config.h"
#include "ZSC31050.h"
#include "i2cmaster.h"
#include <util/delay.h>

//sendet über IIC den Befehl für Command Mode
void Command_mode(void){											
	
	i2c_start_wait(ZSC31050_ADDRESS + I2C_WRITE);
	i2c_write(ZSC31050_CM_COMMAND);
	i2c_stop();	
	_delay_us(50);
}

//sendet über IIC den Befehl EEPROM oder RAM Signatur zu erstellen und speichern
void Signature_write(unsigned char target){							
	
	if (SIGNATURE_EEP)
	{
		i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
		i2c_write(0xC9);
		i2c_stop();
		_delay_ms(50);
	}
	else
	{
		i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
		i2c_write(0xCB);
		i2c_stop();
		_delay_ms(50);	
	}	
		
}

//liest RAM oder EEPROM über IIC aus
void Read_ZSC31050 (volatile unsigned char command[]){				
	
	unsigned char received_byte;
	unsigned char received_byte2;

	switch (command[0]){
			//liest den "kompletten" EEPROM aus und sendet über UART
			case EEP_READ_ALL_COMMAND:								
										for(unsigned char i = 0;i<=15;i++)
										{
											i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
											i2c_write(ZSC31050_EEP_READ_MESS_COMMAND + i);
											i2c_stop();
											_delay_us(50);
											i2c_start(ZSC31050_ADDRESS + I2C_READ);
											received_byte = i2c_readAck();
											received_byte2 = i2c_readNak();
											i2c_stop();
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte;
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte2;
										}
									/*	
									
										for(unsigned char i = 0;i<=1;i++)
										{
											i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
											i2c_write(ZSC31050_EEP_READ_LIMIT_COMMAND +i );
											i2c_stop();
											_delay_us(50);
											i2c_start(ZSC31050_ADDRESS + I2C_READ);
											received_byte = i2c_readAck();
											received_byte2 = i2c_readNak();
											i2c_stop();
											UDR0 = received_byte;
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte2;
										}
										
										for(unsigned char i = 0;i<=2;i++)
										{
											i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
											i2c_write(ZSC31050_EEP_READ_TEMP_COMMAND + i);
											i2c_stop();
											_delay_us(50);
											i2c_start(ZSC31050_ADDRESS + I2C_READ);
											received_byte = i2c_readAck();
											received_byte2 = i2c_readNak();
											i2c_stop();
											UDR0 = received_byte;
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte2;
										}
										
										for(unsigned char i = 0;i<=6;i++)
										{
											i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
											i2c_write(ZSC31050_EEP_READ_CONFIG_COMMAND + i);
											i2c_stop();
											_delay_us(50);
											i2c_start(ZSC31050_ADDRESS + I2C_READ);
											received_byte = i2c_readAck();
											received_byte2 = i2c_readNak();
											i2c_stop();
											UDR0 = received_byte;
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte2;
										}
										*/
										break;
			
			//liest den "kompletten" RAM aus und sendet über UART							
			case RAM_READ_ALL_COMMAND:																
										for(unsigned char i = 0;i<=7;i++)
										{
											i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
											i2c_write(ZSC31050_RAM_READ_MESS_COMMAND + i);
											i2c_stop();
											_delay_us(50);
											i2c_start(ZSC31050_ADDRESS + I2C_READ);
											received_byte = i2c_readAck();
											received_byte2 = i2c_readNak();
											i2c_stop();
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte;
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte2;
										}
										
										for(unsigned char i = 0;i<=1;i++)
										{
											i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
											i2c_write(ZSC31050_RAM_READ_LIMIT_COMMAND +i );
											i2c_stop();
											_delay_us(50);
											i2c_start(ZSC31050_ADDRESS + I2C_READ);
											received_byte = i2c_readAck();
											received_byte2 = i2c_readNak();
											i2c_stop();
											UDR0 = received_byte;
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte2;
										}
										
										for(unsigned char i = 0;i<=2;i++)
										{
											i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
											i2c_write(ZSC31050_RAM_READ_TEMP_COMMAND + i);
											i2c_stop();
											_delay_us(50);
											i2c_start(ZSC31050_ADDRESS + I2C_READ);
											received_byte = i2c_readAck();
											received_byte2 = i2c_readNak();
											i2c_stop();
											UDR0 = received_byte;
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte2;
										}
										
										for(unsigned char i = 0;i<=6;i++)
										{
											i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
											i2c_write(ZSC31050_RAM_READ_CONFIG_COMMAND + i);
											i2c_stop();
											_delay_us(50);
											i2c_start(ZSC31050_ADDRESS + I2C_READ);
											received_byte = i2c_readAck();
											received_byte2 = i2c_readNak();
											i2c_stop();
											UDR0 = received_byte;
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte2;
										}
										
										break;
			
			//liest EEPROM gespeicherte Koeffizienten aus und sendet über UART							
			case EEP_READ_MESS_COMMAND:											
										for(unsigned char i = 0;i<=7;i++)
										{
											i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
											i2c_write(ZSC31050_EEP_READ_MESS_COMMAND + i);
											i2c_stop();
											_delay_us(50);
											i2c_start(ZSC31050_ADDRESS + I2C_READ);
											received_byte = i2c_readAck();
											received_byte2 = i2c_readNak();
											i2c_stop();
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte;
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte2;
										}
																													
										break;
			
			//liest RAM gespeicherte Koeffizienten aus und sendet über UART							
			case RAM_READ_MESS_COMMAND:											
										for(unsigned char i = 0;i<=7;i++)
										{
											i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
											i2c_write(ZSC31050_RAM_READ_MESS_COMMAND + i);
											i2c_stop();
											_delay_us(50);
											i2c_start(ZSC31050_ADDRESS + I2C_READ);
											received_byte = i2c_readAck();
											received_byte2 = i2c_readNak();
											i2c_stop();
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte;
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte2;
										}	
											
										break;
			
			//liest EEPROM gespeicherte Limit Werte aus und sendet über UART							
			case EEP_READ_LIMIT_COMMAND:									
										for(unsigned char i = 0;i<=1;i++)
										{
											i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
											i2c_write(ZSC31050_EEP_READ_LIMIT_COMMAND +i );
											i2c_stop();
											_delay_us(50);
											i2c_start(ZSC31050_ADDRESS + I2C_READ);
											received_byte = i2c_readAck();
											received_byte2 = i2c_readNak();
											i2c_stop();
											UDR0 = received_byte;
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte2;
										}
										
										break;
			
			//liest RAM gespeicherte Limit Werte aus und sendet über UART							
			case RAM_READ_LIMIT_COMMAND:									
										for(unsigned char i = 0;i<=1;i++)
										{
											i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
											i2c_write(ZSC31050_RAM_READ_LIMIT_COMMAND +i );
											i2c_stop();
											_delay_us(50);
											i2c_start(ZSC31050_ADDRESS + I2C_READ);
											received_byte = i2c_readAck();
											received_byte2 = i2c_readNak();
											i2c_stop();
											UDR0 = received_byte;
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte2;
										}
										
										break;
									
			//liest Koeffizienten aus EEPROM für Temperaturmessung aus und sendet über UART							
			case EEP_READ_TEMP_COMMAND:										
										for(unsigned char i = 0;i<=2;i++)
										{
											i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
											i2c_write(ZSC31050_EEP_READ_TEMP_COMMAND + i);
											i2c_stop();
											_delay_us(50);
											i2c_start(ZSC31050_ADDRESS + I2C_READ);
											received_byte = i2c_readAck();
											received_byte2 = i2c_readNak();
											i2c_stop();
											UDR0 = received_byte;
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte2;
										}
										
										break;
								
			//liest Koeffizienten aus RAM für Temperaturmessung aus und sendet über UART							
			case RAM_READ_TEMP_COMMAND:																
										for(unsigned char i = 0;i<=2;i++)
										{
											i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
											i2c_write(ZSC31050_RAM_READ_TEMP_COMMAND + i);
											i2c_stop();
											_delay_us(50);
											i2c_start(ZSC31050_ADDRESS + I2C_READ);
											received_byte = i2c_readAck();
											received_byte2 = i2c_readNak();
											i2c_stop();
											UDR0 = received_byte;
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte2;
										}
										
										break;
		
		//liest Konfiguration aus EEPROM und sendet über UART								
		case EEP_READ_CONFIG_COMMAND:										
										for(unsigned char i = 0;i<=6;i++)
										{
											i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
											i2c_write(ZSC31050_EEP_READ_CONFIG_COMMAND + i);
											i2c_stop();
											_delay_us(50);
											i2c_start(ZSC31050_ADDRESS + I2C_READ);
											received_byte = i2c_readAck();
											received_byte2 = i2c_readNak();
											i2c_stop();
											UDR0 = received_byte;
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte2;
										}
										
										break;
		
		//liest Konfiguration aus RAMund sendet über UART
		case RAM_READ_CONFIG_COMMAND:									
										for(unsigned char i = 0;i<=6;i++)
										{
											i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
											i2c_write(ZSC31050_RAM_READ_CONFIG_COMMAND + i);
											i2c_stop();
											_delay_us(50);
											i2c_start(ZSC31050_ADDRESS + I2C_READ);
											received_byte = i2c_readAck();
											received_byte2 = i2c_readNak();
											i2c_stop();
											UDR0 = received_byte;
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte2;
										}
										
										break;
		
		//liest vom Benzuter frei verwaltbaren EEPROM Bereich aus					
		case EEP_READ_ID_COMMAND:									
										for(unsigned char i = 0;i<=1;i++)
										{
											i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
											i2c_write(ZSC31050_EEP_READ_ID_COMMAND + i);
											i2c_stop();
											_delay_us(50);
											i2c_start(ZSC31050_ADDRESS + I2C_READ);
											received_byte = i2c_readAck();
											received_byte2 = i2c_readNak();
											i2c_stop();
											UDR0 = received_byte;
											while(!(UCSR0A & (1<<UDRE0)));
											UDR0 = received_byte2;
										}
										
										break;
										
			
		
	}	
}

//schreibt in RAM oder EEPROM über IIC
unsigned char Write_ZSC31050 (volatile unsigned char command[],volatile unsigned char count){			
	
	
	unsigned char check=0;
	
	switch (command[0]){
			//beschreibt den "kompetten" EEPROM
			case EEP_WRITE_ALL_COMMAND:	
										if (count == 41)
										{
											for(unsigned char i = 0;i<=7;i++)
											{
												i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
												i2c_write((ZSC31050_EEP_WRITE_MESS_COMMAND + i));
												i2c_write(command[2*i+1]);
												i2c_write(command[2*i+2]);
												i2c_stop();
												_delay_ms(50);
											}
											
											for(unsigned char i = 0;i<=1;i++)
											{
												i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
												i2c_write((ZSC31050_EEP_WRITE_LIMIT_COMMAND + i));
												i2c_write(command[2*i+17]);
												i2c_write(command[2*i+18]);
												i2c_stop();
												_delay_ms(50);
											}
											
											for(unsigned char i = 0;i<=2;i++)
											{
												i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
												i2c_write((ZSC31050_EEP_WRITE_TEMP_COMMAND + i));
												i2c_write(command[2*i+21]);
												i2c_write(command[2*i+22]);
												i2c_stop();
												_delay_ms(50);
											}
											
											for(unsigned char i = 0;i<=6;i++)
											{
												i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
												i2c_write((ZSC31050_EEP_WRITE_CONFIG_COMMAND + i));
												i2c_write(command[2*i+27]);
												i2c_write(command[2*i+28]);
												i2c_stop();
												_delay_ms(50);
											}
											
											Signature_write(SIGNATURE_EEP);
											
											check = 1;
										}
										
										break;
			
			//beschreibt den "kompletten" RAM							
			case RAM_WRITE_ALL_COMMAND:		
										if (count == 41)
										{
											for(unsigned char i = 0;i<=7;i++)
											{
												i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
												i2c_write((ZSC31050_RAM_WRITE_MESS_COMMAND + i));
												i2c_write(command[2*i+1]);
												i2c_write(command[2*i+2]);
												i2c_stop();
												_delay_ms(50);
											}
											
											for(unsigned char i = 0;i<=1;i++)
											{
												i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
												i2c_write((ZSC31050_RAM_WRITE_LIMIT_COMMAND + i));
												i2c_write(command[2*i+17]);
												i2c_write(command[2*i+18]);
												i2c_stop();
												_delay_ms(50);
											}
											
											for(unsigned char i = 0;i<=2;i++)
											{
												i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
												i2c_write((ZSC31050_RAM_WRITE_TEMP_COMMAND + i));
												i2c_write(command[2*i+21]);
												i2c_write(command[2*i+22]);
												i2c_stop();
												_delay_ms(50);
											}
											
											for(unsigned char i = 0;i<=6;i++)
											{
												i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
												i2c_write((ZSC31050_RAM_WRITE_CONFIG_COMMAND + i));
												i2c_write(command[2*i+27]);
												i2c_write(command[2*i+28]);
												i2c_stop();
												_delay_ms(50);
											}
				
											Signature_write(SIGNATURE_RAM);
				
											check = 1;
										}
										
										break;
			
			//beschreibt EEPROM mit den Koeffizienten zur Druckkorrektur
			case EEP_WRITE_MESS_COMMAND:		
										if (count == 17)
										{
											for(unsigned char i = 0;i<=7;i++)
											{
												i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
												i2c_write((ZSC31050_EEP_WRITE_MESS_COMMAND + i));
												i2c_write(command[2*i+1]);
												i2c_write(command[2*i+2]);
												i2c_stop();
												_delay_ms(50);								
											}
											
											Signature_write(SIGNATURE_EEP);
											
											check = 1;
										}
										
										break;
			
			//beschreibt RAM mit den Koeffizienten zur Druckkorrektur							
			case RAM_WRITE_MESS_COMMAND:										
										if (count == 17)
										{
											for(unsigned char i = 0;i<=7;i++)
											{
												i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
												i2c_write((ZSC31050_RAM_WRITE_MESS_COMMAND + i));
												i2c_write(command[2*i+1]);
												i2c_write(command[2*i+2]);
												i2c_stop();
												_delay_ms(50);
											}
											
											Signature_write(SIGNATURE_RAM);
											
											check = 1;
										}
										
										break;										
			
			//beschreibt EEPROM mit den Limit Werten							
			case EEP_WRITE_LIMIT_COMMAND:									
										if (count == 5)
										{
											for(unsigned char i = 0;i<=1;i++)
											{
												i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
												i2c_write((ZSC31050_EEP_WRITE_LIMIT_COMMAND + i));
												i2c_write(command[2*i+1]);
												i2c_write(command[2*i+2]);
												i2c_stop();
												_delay_ms(50);
											}
											
											Signature_write(SIGNATURE_EEP);
																						
											check = 1;
										}	
															
										break;
			
			//beschreibt RAM mit den Limit Werten							
			case RAM_WRITE_LIMIT_COMMAND:								
										if (count == 5)
										{
											for(unsigned char i = 0;i<=1;i++)
											{
												i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
												i2c_write((ZSC31050_RAM_WRITE_LIMIT_COMMAND + i));
												i2c_write(command[2*i+1]);
												i2c_write(command[2*i+2]);
												i2c_stop();
												_delay_ms(50);
											}
														
											Signature_write(SIGNATURE_RAM);
														
											check = 1;
										}	
										
										break;
			
			//beschreibt EEPROM mit Temperatur Korrektur Koeffizienten
			case EEP_WRITE_TEMP_COMMAND:	
										if (count == 7)
										{
											for(unsigned char i = 0;i<=2;i++)
											{
												i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
												i2c_write((ZSC31050_EEP_WRITE_TEMP_COMMAND + i));
												i2c_write(command[2*i+1]);
												i2c_write(command[2*i+2]);
												i2c_stop();
												_delay_ms(50);
											}

											Signature_write(SIGNATURE_EEP);
											
											check = 1;
										}	
																		
										break;
			
			//beschreibt RAM mit Temperatur Korrektur Koeffizienten							
			case RAM_WRITE_TEMP_COMMAND:								
										if (count == 7)
										{
											for(unsigned char i = 0;i<=2;i++)
											{
												i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
												i2c_write((ZSC31050_RAM_WRITE_TEMP_COMMAND + i));
												i2c_write(command[2*i+1]);
												i2c_write(command[2*i+2]);
												i2c_stop();
												_delay_ms(50);
											}

											Signature_write(SIGNATURE_RAM);
																		
											check = 1;
										}
										
										break;
			
			//beschreibt EEPROM mit Konfiguration							
			case EEP_WRITE_CONFIG_COMMAND:	
										if (count == 15)
										{
											for(unsigned char i = 0;i<=6;i++)
											{
												i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
												i2c_write((ZSC31050_EEP_WRITE_CONFIG_COMMAND + i));
												i2c_write(command[2*i+1]);
												i2c_write(command[2*i+2]);
												i2c_stop();
												_delay_ms(50);
											}

											Signature_write(SIGNATURE_EEP);
											
											check = 1;
										}
										
										break;
			
			//beschreibt RAM mit Konfiguration							
			case RAM_WRITE_CONFIG_COMMAND:						
										if (count == 15)
										{
											for(unsigned char i = 0;i<=6;i++)
											{
												i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
												i2c_write((ZSC31050_RAM_WRITE_CONFIG_COMMAND + i));
												i2c_write(command[2*i+1]);
												i2c_write(command[2*i+2]);
												i2c_stop();
												_delay_ms(50);
											}

											Signature_write(SIGNATURE_RAM);
				
											check = 1;
										}
										
										break;	
		
		//beschreibt vom Benutzer frei verfügbaren EEPROM								
		case EEP_WRITE_ID_COMMAND:								
									if (count == 5)
									{PORTB &= ~(1<<DDB5); // led Pin 13 auf High setzen
										for(unsigned char i = 0;i<=1;i++)
										{
											i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
											i2c_write((ZSC31050_EEP_WRITE_ID_COMMAND + i));
											i2c_write(command[2*i+1]);
											i2c_write(command[2*i+2]);
											i2c_stop();
											_delay_ms(50);
										}
										PORTB |=(1<<DDB5); // led Pin 13 auf High setzen

										//Signature_write(0);
										
										check = 1;
									}
									
									break;								
	}
	
	return check;
}

void Copy(volatile unsigned char command[]){
	
	switch(command[0]){
		//sendet Befehl RAM in EEPROM zu kopieren
		case COPY_RAM2EEP:	
							i2c_start_wait(ZSC31050_ADDRESS + I2C_WRITE);
							i2c_write(ZSC31050_COPY_RAM2EEP);
							i2c_stop();
							_delay_ms(500);
							Signature_write(SIGNATURE_EEP);
							break;
							
		//sendet Befehl EEPROM in RAM zu kopieren					
		case COPY_EEP2RAM:									
							i2c_start_wait(ZSC31050_ADDRESS + I2C_WRITE);
							i2c_write(ZSC31050_COPY_EEP2RAM);
							i2c_stop();
							_delay_us(150);
							Signature_write(SIGNATURE_RAM);
							break;	
		
	}
			
}

void Output(volatile unsigned char command[]){
	
	unsigned char received_byte = 0;
	unsigned char received_byte2 = 0;
	
	switch(command[0]){
					//liest den unkorrigierten ungenullten digitalen Druckwert aus
					case START_P:										
						
									i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
									i2c_write(ZSC31050_START_P);
									i2c_stop();
									_delay_us(50);						
						
									do 
									{
											_delay_ms(250);
											i2c_start(ZSC31050_ADDRESS + I2C_READ);
											received_byte = i2c_readAck();
											received_byte2 = i2c_readNak();	
											i2c_stop();										
											UDR0 = received_byte;
											while(!(UCSR0A & (1<<UDRE0)));
												UDR0 = received_byte2;
											while(!(UCSR0A & (1<<UDRE0)));
												UDR0=0x0A;		
									} while (command[0] != 0xFF);									
									break;
									
					//liest den unkorrigierten ungenullten digitalen Temperaturwert aus
					case START_T1:		
					
									i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
									i2c_write(ZSC31050_START_T1);
									i2c_stop();
									_delay_us(50);
									
									do
									{
										_delay_ms(250);
										i2c_start(ZSC31050_ADDRESS + I2C_READ);
										received_byte = i2c_readAck();
										received_byte2 = i2c_readNak();
										i2c_stop();
										UDR0 = received_byte;
										while(!(UCSR0A & (1<<UDRE0)));
										UDR0 = received_byte2;
										while(!(UCSR0A & (1<<UDRE0)));
										
									} while (command[0] != 0xFF);
									
									break;

                    //liest den auto-null digitalen Druckwert aus
					case START_PAZ:		
					
									i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
									i2c_write(ZSC31050_START_PAZ);
									i2c_stop();
									_delay_us(50);
					
									do
									{
										_delay_ms(250);
										i2c_start(ZSC31050_ADDRESS + I2C_READ);
										received_byte = i2c_readAck();
										received_byte2 = i2c_readNak();
										i2c_stop();
										UDR0 = received_byte;
										while(!(UCSR0A & (1<<UDRE0)));
										UDR0 = received_byte2;
										while(!(UCSR0A & (1<<UDRE0)));
						
									} while (command[0] != 0xFF);
									
									break;
					
					//liest den auto-null digitalen Temperaturwert aus
					case START_TAZ1:						
					
									i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
									i2c_write(ZSC31050_START_TAZ1);
									i2c_stop();
									_delay_us(50);
					
									do
									{
										_delay_ms(250);
										i2c_start(ZSC31050_ADDRESS + I2C_READ);
										received_byte = i2c_readAck();
										received_byte2 = i2c_readNak();
										i2c_stop();
										UDR0 = received_byte;
										while(!(UCSR0A & (1<<UDRE0)));
										UDR0 = received_byte2;
										while(!(UCSR0A & (1<<UDRE0)));
						
									} while (command[0] != 0xFF);
									
									break;
				
				//liest den unkorrigierten auto-genullten digitalen Druckwert aus	
				case START_PAZC:						
				
									i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
									i2c_write(ZSC31050_START_PAZC);
									i2c_stop();
									_delay_us(50);
				
									do
									{
										_delay_ms(250);
										i2c_start(ZSC31050_ADDRESS + I2C_READ);
										received_byte = i2c_readAck();
										received_byte2 = i2c_readNak();
										i2c_stop();
										UDR0 = received_byte;
										while(!(UCSR0A & (1<<UDRE0)));
										UDR0 = received_byte2;
										while(!(UCSR0A & (1<<UDRE0)));
					
									} while (command[0] != 0xFF);
									
									break;
				
				//liest den unkorrigierten auto-genullten digitalen Temperaturwert aus					
				case START_T1AZC:					
									
									i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
									i2c_write(ZSC31050_START_T1AZC);
									i2c_stop();
									_delay_us(50);
									
									do
									{
										_delay_ms(250);
										i2c_start(ZSC31050_ADDRESS + I2C_READ);
										received_byte = i2c_readAck();
										received_byte2 = i2c_readNak();
										i2c_stop();
										UDR0 = received_byte;
										while(!(UCSR0A & (1<<UDRE0)));
										UDR0 = received_byte2;
										while(!(UCSR0A & (1<<UDRE0)));
										
									} while (command[0] != 0xFF);
									
									break;
			
			//liest die Common-Mode-Voltage aus						
			case START_CMV_AZC:			
								
								i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
								i2c_write(ZSC31050_START_CMV_AZC);
								i2c_stop();
								_delay_us(50);
								
								do
								{
									_delay_ms(250);
									i2c_start(ZSC31050_ADDRESS + I2C_READ);
									received_byte = i2c_readAck();
									received_byte2 = i2c_readNak();
									i2c_stop();
									UDR0 = received_byte;
									while(!(UCSR0A & (1<<UDRE0)));
									UDR0 = received_byte2;
									while(!(UCSR0A & (1<<UDRE0)));
									
								} while (command[0] != 0xFF);
								
								break;
			
			//liest den korrigierten digitalen Druckwert aus
			case START_MESS:		
								i2c_start(ZSC31050_ADDRESS + I2C_WRITE);
								i2c_write(ZSC31050_START_MESS);
								i2c_stop();
								_delay_us(250);										
								while(command[0] != 0xFF)
								{		_delay_ms(250);
										i2c_start(ZSC31050_ADDRESS + I2C_READ);
										received_byte = i2c_readAck();
										received_byte2 = i2c_readNak();
										i2c_stop();
										UDR0 = received_byte;
										while(!(UCSR0A & (1<<UDRE0)));
										UDR0 = received_byte2;
										while(!(UCSR0A & (1<<UDRE0)));								
								};
																	
								break;
								
	}
}


