/******************************************************************************************************************
Pinmap Keypad 3x4: ROW1 ROW2 ROW3 ROW4 COL1 COL2 COL3 COL4
                   4    5    6    7    0    1    2    3
******************************************************************************************************************/
#include "keypad.h"

static void Keypad_delay(uint16_t Time)
{
	HAL_Delay(Time);
}

void KEYPAD4X4_Init(KEYPAD_t* KEYPAD, char KEYMAP[NUMROWS][NUMCOLS], GPIO_TypeDef* COL1_PORT, uint32_t COL1_PIN, 
										                                                 GPIO_TypeDef* COL2_PORT, uint32_t COL2_PIN,
										                                                 GPIO_TypeDef* COL3_PORT, uint32_t COL3_PIN,
                                                                     GPIO_TypeDef* COL4_PORT, uint32_t COL4_PIN,
										                                                 GPIO_TypeDef* ROW1_PORT, uint32_t ROW1_PIN,
										                                                 GPIO_TypeDef* ROW2_PORT, uint32_t ROW2_PIN,
										                                                 GPIO_TypeDef* ROW3_PORT, uint32_t ROW3_PIN,
										                                                 GPIO_TypeDef* ROW4_PORT, uint32_t ROW4_PIN)
{
	
	KEYPAD->ColPort[0] = COL1_PORT;
	KEYPAD->ColPort[1] = COL2_PORT;
	KEYPAD->ColPort[2] = COL3_PORT;
	KEYPAD->ColPort[3] = COL4_PORT;
	
	KEYPAD->ColPins[0] = COL1_PIN;
	KEYPAD->ColPins[1] = COL2_PIN;
	KEYPAD->ColPins[2] = COL3_PIN;
	KEYPAD->ColPins[3] = COL4_PIN;

	KEYPAD->RowPort[0] = ROW1_PORT;
	KEYPAD->RowPort[1] = ROW2_PORT;
	KEYPAD->RowPort[2] = ROW3_PORT;
	KEYPAD->RowPort[3] = ROW4_PORT;
	
	KEYPAD->RowPins[0] = ROW1_PIN;
	KEYPAD->RowPins[1] = ROW2_PIN;
	KEYPAD->RowPins[2] = ROW3_PIN;
	KEYPAD->RowPins[3] = ROW4_PIN;

	for(uint8_t colum = 0; colum < NUMCOLS; colum++)
	{
		for(uint8_t row = 0; row < NUMROWS; row++)
		{
			KEYPAD->MAP[row][colum] = KEYMAP[row][colum];
		}
	}
	
	HAL_GPIO_WritePin(KEYPAD->ColPort[0], KEYPAD->ColPins[0], GPIO_PIN_SET);
	HAL_GPIO_WritePin(KEYPAD->ColPort[1], KEYPAD->ColPins[1], GPIO_PIN_SET);
	HAL_GPIO_WritePin(KEYPAD->ColPort[2], KEYPAD->ColPins[2], GPIO_PIN_SET);
	HAL_GPIO_WritePin(KEYPAD->ColPort[3], KEYPAD->ColPins[3], GPIO_PIN_SET);
}

char KEYPAD4X4_scan(KEYPAD_t* KEYPAD) // Scan Colums
{
	KEYPAD->Value = 0;
	
	for(uint8_t colum = 0; colum < NUMCOLS; colum++)
	{

		for(uint8_t row = 0; row < NUMROWS; row++)
		{
			HAL_GPIO_WritePin(KEYPAD->ColPort[colum], KEYPAD->ColPins[colum], GPIO_PIN_RESET);
			
			if(HAL_GPIO_ReadPin(KEYPAD->RowPort[row], KEYPAD->RowPins[row]) == KEY_PRESSED)
			{
				Keypad_delay(50);// debound
				while(HAL_GPIO_ReadPin(KEYPAD->RowPort[row], KEYPAD->RowPins[row]) == KEY_PRESSED){}
				KEYPAD->Value = KEYPAD->MAP[row][colum];
					
				return KEYPAD->Value;
			}
			
			HAL_GPIO_WritePin(KEYPAD->ColPort[colum], KEYPAD->ColPins[colum], GPIO_PIN_SET);
		}
	}
	
	return KEY_RELEASED;
}

void KEYPAD4x4_Config(KEYPAD_t* KEYPAD, char KEYMAP_Config[NUMROWS][NUMCOLS])
{
	for(uint8_t colum = 0; colum < NUMCOLS; colum++)
	{
		for(uint8_t row = 0; row < NUMROWS; row++)
		{
			KEYPAD->MAP[row][colum] = KEYMAP_Config[row][colum];
		}
	}
}
