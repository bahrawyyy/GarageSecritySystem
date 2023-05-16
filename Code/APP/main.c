/*
 * main.c
 *
 *  Created on: May 4, 2023
 *      Author: Abdallah
 */

#define F_CPU 16000000UL

#include "../HAL/Lcd/Lcd.h"
#include "../MCAL/EXT_INTERRUPTS/EXT_INTERRUPTS.h"
#include "../MCAL/Timer/Timer.h"
#include <util/delay.h>
#include "../HAL/KPD/KPD_interface.h"
#include <string.h>


volatile u16 countOverflows=0,Copy_counter;
u8 password[] = "1234";
u8 flag=0;

#define MOTOR_PIN DIO_U8_PIN_4
#define RED_LED DIO_U8_PIN_0

// Indication of correct password
void LED_ON(void)
{
	DIO_ES_tSetPinValue(DIO_U8_PORT_C, RED_LED, HIGH);
//	_delay_ms(500);
//	DIO_ES_tSetPinValue(DIO_U8_PORT_C, RED_LED, LOW);
//	_delay_ms(500);
}

u8 input[5] = {'\0'}; // Initialize input array
u8 indexz = 0;



void delay()
{
	// delay / tick_time = num_counts
	// no. of counts / 256 = num_overflows
	// no. of counts mod 256 = no. of rest counts
	// TCNT value to reach the no. of rest counts
	// TCNT0 = 256 - no. of rest counts
	countOverflows++;
	// 8 As first interrupt will occur at 208, then 7 interrupts
	if(countOverflows == 245)
	{
		DIO_ES_tSetPinValue(DIO_U8_PORT_C, MOTOR_PIN, LOW);
		lcd_ES_tclear();
		Lcd_ES_tsendString("Garage Closed");
		_delay_ms(1500);
		lcd_ES_tclear();
		Lcd_ES_tsendString("Enter Password");
		LCD_ES_tGoTo(1, 5);
		memset(input, '\0', sizeof(input));
		indexz=0;
		TCCR0 = 0x00;
		//TCNT0 = 256-36;
		countOverflows=0;
	}
}

int main()
{
	sei();   // Enabling global interrupt
	DIO_ES_tInit();
	Lcd_ES_tInit();

	u8 Value;
	u8 count=0;


	// Interrupt pin INT2
	EXI_TriggerEdge(EX_INT2,FALLING_EDGE);
	EXI_ENABLE(EX_INT2);
	EXI_Set_CallBack(EX_INT2,LED_ON);

	DIO_ES_tSetPinValue(DIO_U8_PORT_B, DIO_U8_PIN_2, HIGH);



	// When password is wrong three times
	// LED as external interrupt


	// Give the user the option to create a password
	// Looping every 20 seconds or something

	Lcd_ES_tsendString("Enter Password !");
	LCD_ES_tGoTo(1, 5);




	while(1)
	{
		//while(flag==0){
			// KeyPad interfacing
			KPD_ES_tGetKeyPressed(&Value);
			if(Value != KPD_U8_NOT_PRESSED){

				Lcd_ES_tsendChar('*');
				input[indexz] = Value; // Store input in array
				indexz++;
				if (indexz >= 4) { // Check if password entered
					if (strcmp(input, password) == 0) {
						// Password is correct, perform action
						//						DIO_ES_tSetPinValue(DIO_U8_PORT_B, DIO_U8_PIN_2, HIGH);
						lcd_ES_tclear();
						Lcd_ES_tsendString("Garage opened");

						DIO_ES_tSetPinValue(DIO_U8_PORT_C, MOTOR_PIN, HIGH);


						Timer0_Init(TIMER0_NORMAL_MODE, TIMER0_PRESCALAR_1024,OC0_DISCONNECTED);
						Timer0_OVInterrupt_Enable();

						TCNT0 = 256-36;
						Timer0_OVF_SetCallBack(delay);
						flag=0;

//						break;

					}
					else {
						// Password is incorrect, reset input
						lcd_ES_tclear();
						Lcd_ES_tsendString("Wrong Password");
						memset(input, '\0', sizeof(input));
						indexz = 0;
						_delay_ms(1500);
//						_delay_ms(1500);
//						_delay_ms(1500);
						flag=0;
						count++;
						lcd_ES_tclear();
						Lcd_ES_tsendString("Try again");
						LCD_ES_tGoTo(1, 5);
						if(count == 3){
							lcd_ES_tclear();
							Lcd_ES_tsendString("Blocked !!!");
							count=0;
							DIO_ES_tSetPinValue(DIO_U8_PORT_B, DIO_U8_PIN_2, LOW);
						}

					}
				}
			}
		//}





	}

	return 0;
}





// Motor (In case controlling speed)
// and Enabling timer2 instead
//	Timer0_Init(TIMER0_PHASE_CORRECT_MODE, TIMER0_PRESCALAR_8,OC0_NON_INVERTING);
//	OCR0=128;    // Duty cycle 50% , Frequency
//	// delay();
//	// Timer0_stop();  // OCR0=0;
//	// Timer2_stop();
