#ifndef __KEYPAD_H
#define __KEYPAD_H

#include "stm32f1xx_hal.h"

#define NUMROWS            4
#define NUMCOLS            4
#define KEYS               16

#define KEY_PRESSED        0
#define NON_KEY_RELEASED   0

/* Rows INPUT*/
#define KEYPAD_ROW1_PORT          GPIOA
#define KEYPAD_ROW1_PIN           GPIO_PIN_0
#define KEYPAD_ROW2_PORT          GPIOA
#define KEYPAD_ROW2_PIN           GPIO_PIN_1
#define KEYPAD_ROW3_PORT          GPIOA
#define KEYPAD_ROW3_PIN           GPIO_PIN_2
#define KEYPAD_ROW4_PORT          GPIOA
#define KEYPAD_ROW4_PIN           GPIO_PIN_3

/* Column OUTPUT*/
#define KEYPAD_COLUM1_PORT        GPIOA
#define KEYPAD_COLUM1_PIN         GPIO_PIN_4
#define KEYPAD_COLUM2_PORT        GPIOA
#define KEYPAD_COLUM2_PIN         GPIO_PIN_5
#define KEYPAD_COLUM3_PORT        GPIOA
#define KEYPAD_COLUM3_PIN         GPIO_PIN_6
#define KEYPAD_COLUM4_PORT        GPIOA
#define KEYPAD_COLUM4_PIN         GPIO_PIN_7

typedef struct
{
	uint32_t RowPins[NUMROWS];
	uint32_t ColPins[NUMCOLS];
	GPIO_TypeDef* RowPort[NUMROWS];
	GPIO_TypeDef* ColPort[NUMCOLS];
	char MAP[NUMROWS][NUMCOLS];
	char Value;
} KEYPAD_t;

void KEYPAD4X4_Init(KEYPAD_t* KEYPAD, char KEYMAP[NUMROWS][NUMCOLS], GPIO_TypeDef* ROW1_PORT, uint32_t ROW1_PIN,
										                                                 GPIO_TypeDef* ROW2_PORT, uint32_t ROW2_PIN,
										                                                 GPIO_TypeDef* ROW3_PORT, uint32_t ROW3_PIN,
										                                                 GPIO_TypeDef* ROW4_PORT, uint32_t ROW4_PIN,
                                                                     GPIO_TypeDef* COL1_PORT, uint32_t COL1_PIN, 
										                                                 GPIO_TypeDef* COL2_PORT, uint32_t COL2_PIN,
										                                                 GPIO_TypeDef* COL3_PORT, uint32_t COL3_PIN,
                                                                     GPIO_TypeDef* COL4_PORT, uint32_t COL4_PIN);

char KEYPAD4X4_scan(KEYPAD_t* KEYPAD);

#endif
