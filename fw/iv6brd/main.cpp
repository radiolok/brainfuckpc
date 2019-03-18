/*
 * iv6brd.cpp
 *
 * Created: 14.12.2017 22:57:47
 * Author : radiolok
 */ 

#include <avr/io.h>



//#define COUNTER 1
#define TERMINAL
//#define SHOWER

#if defined(TERMINAL)
#define BAUD_RATE 9600
#else
#define BAUD_RATE 38400
#endif

#include "MTask.h"
#include "log.h"
#include "uart.h"
#include "spi.h"
#include "SegmentDisplay.h"

//#define IP_SHOW
//#define AP_SHOW
#define CMD_SHOW

#if defined(IP_SHOW)
char prefix[] = "I ";
char length = 2;
#elif defined(AP_SHOW)
char prefix[] = "A ";
char length = 2;
#elif defined(CMD_SHOW)
char prefix[] = "C ";
char length = 2;
#else
char prefix[] = "  ";
char length = 2;
#endif

#if defined (SHOWER) || defined(COUNTER)
	static uint32_t SCHEDULER_PERIOD = 1;//ms
#endif


void portReader()
{


	
#if  defined(SHOWER)
	DDRB |= (1<<PB2);
	//read current value
	PORTB &= ~(1<<PB2);
	_delay_us(1);
	PORTB |= (1<<PB2);
	
	union data_t{
		uint8_t bytes[2];
		uint16_t word;		
	} data;
		data.bytes[0] = spi_sendByte(0);
		data.bytes[1] = spi_sendByte(0);
		
	SegmentDisplay::Instance()(data.word, prefix, length);

	
	
#endif

}

/*
Backspace (without delete function) BS
Line feed LF
Carriage Return CR
Clear display ESC [2J
Positioning the character pointer ESC [Py; PxH
Delete until end of line ESC [0K
Set country code ESC Rn
Get Display ID ESC [0c

*/


#if defined(TERMINAL)

#define ChESC  0x1B

void clearDisplay()
{
	uart_putc(ChESC);
	uart_puts("[2J");
}

void setPosition(uint8_t x, uint8_t y)
{
	uart_putc(ChESC);
	uart_putc('[');
	uart_putc(x);
	uart_putc(';');
	uart_putc(y);
	uart_putc('H');
}

#endif


#if defined(SHOWER)
void shower()
{
	sei();
	uart_init(UART_BAUD_SELECT(BAUD_RATE, F_CPU));
	

	MTask::Instance().Init(SCHEDULER_PERIOD, F_CPU);
	spi_init();

	SegmentDisplay::Instance().Init(6, 0x10);
	MTask::Instance().Add(portReader, 0, 5);

	/* Replace with your application code */
	MTask::Instance().Start();

}
#elif defined(TERMINAL)
void terminal()
{
	
	/*
	BIT 0 PB2
	BIT 1 PB1
	BIT 2 PB0
	BIT 3 PD7
	BIT 4 PD6
	BIT 5 PD5 
	BIT 6 PB7
	BIT 7 PB6
	*/
	sei();
	uart_init(UART_BAUD_SELECT(BAUD_RATE, F_CPU));
	uart_set_parity(UART_PARITY_ODD);
	uint8_t old_state = 0;
	
	uint8_t symbols = 0;
	
	uart_puts("hello world!");
	while(1)
	{
		uint8_t state = PINC & (1<<PC1);
		if ( state != old_state)
		{
			if (state)
			{
				uint8_t pinB = PINB;
				uint8_t pinD = PIND;
				
				uint8_t result = 0;
				
				result |= ((pinB >>PB2) & 0x01);
				result |= (((pinB >>PB1) & 0x01) << 1);
				result |= (((pinB >>PB0) & 0x01) << 2);
				result |= (((pinD >>PD7) & 0x01) << 3);
				result |= (((pinD >>PD6) & 0x01) << 4);
				result |= (((pinD >>PD5) & 0x01) << 5);
				result |= (((pinB >>PB7) & 0x01) << 6);
				result |= (((pinB >>PB6) & 0x01) << 7);
				
				symbols++;					
				if (result == 0x0A)
				{
					uart_putc(0x0D);
					symbols = 0;
				}				
				uart_putc(result);			


				if (symbols > 19)
				{
					uart_puts("\r\n");
				}
			}
			_delay_ms(1);
		}		
		old_state = state;

	}
}
#elif defined(COUNTER)

volatile uint32_t instructions_retired = 0;

uint8_t old_state = 0;
void clock_checker()
{
	uint8_t state = PINB & (1<<PB1);
	if ((state) && (state != old_state))
	{
		instructions_retired++;
		SegmentDisplay::Instance()(instructions_retired);
	}
	old_state = state;
}

void counter(void)
{
	sei();


	MTask::Instance().Init(SCHEDULER_PERIOD, F_CPU);

	SegmentDisplay::Instance().Init(6, 10);
	
	SegmentDisplay::Instance()(0L);
	
	MTask::Instance().Add(clock_checker, 0, 1);

	/* Replace with your application code */
	MTask::Instance().Start();
	
}
#endif

int main(void)
{
#if defined(TERMINAL)
	terminal();
#elif defined(SHOWER)
	shower();
#elif defined(COUNTER)
	counter();
#endif
	
}

