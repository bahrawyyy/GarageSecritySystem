/*
 * Lcd_Config.h
 *
 *  Created on: Sep 12, 2022
 *      Author: 10
 */

#ifndef HAL_LCD_LCD_CONFIG_H_
#define HAL_LCD_LCD_CONFIG_H_

//This is a file to define index of pins

// LCD is attached to PORTB

// DIO_U8_PIN_0

#define LCD_DATA_PORT DIO_U8_PORT_A


// RS A1
// EN A2
// D4 A3
// D5 A4
// D6 A5
// D7 A6

#define D7 DIO_U8_PIN_6 //Because D7 is attached to the pin no.7
#define D6 DIO_U8_PIN_5
#define D5 DIO_U8_PIN_4
#define D4 DIO_U8_PIN_3

#define LCD_CMD_PORT DIO_U8_PORT_A

#define RS DIO_U8_PIN_1  // A1
#define RW DIO_U8_PIN_0  //
#define EN DIO_U8_PIN_2  // A2

#endif /* HAL_LCD_LCD_CONFIG_H_ */
