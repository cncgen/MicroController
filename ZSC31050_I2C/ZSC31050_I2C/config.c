//config.c
// überarbeitet von Tarek Meftah


#include <avr/io.h>
#include "config.h"
#include <util/setbaud.h>

void Uartinit (void)
{
	// BaUDR0ate einstellen
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	
	UCSR0C |=  (1<<UCSZ01) | (1<<UCSZ00);			//einstellen 8 Datenbits, 1 Stopbit
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);				//aktivieren Sender, Empfänger und Interrupt
}