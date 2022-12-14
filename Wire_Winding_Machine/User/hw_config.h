/**
  ******************************************************************************************
    @file    hw_config.h
    @author  phucpv
    @version 1.0
    @date    03/07/2022
    @brief   the hardware definition for ESP32.
  ******************************************************************************************
    @attention
    1. Any commercial product related to this source code is required to specify the source.
    <h2><center>&copy; COPYRIGHT 2022 ...@gmail.com</center></h2>
  ******************************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------------------*/
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

#ifdef _cplusplus
extern "C"
{
#endif

/*
	Pulse input frequency up to 20 kHz
	+ max 20kHz when duty cyle is 25 high / 75 low
	+ max 13kHz when duty cycle is 50 / 50
*/

/****************************************
           User Defition
*****************************************/
#define TB6600DIR_PORT              GPIOB
#define TB6600DIR_PIN               GPIO_PIN_14
#define TB6600EA_PORT               GPIOB
#define TB6600EA_PIN                GPIO_PIN_15
#define TB6600PUL_PORT              GPIOA
#define TB6600PUL                   GPIO_PIN_8

#define MOTOR_STEP		              1.8
#define MOTOR_MAX_STEP_AROUND       200

#ifdef _cplusplus
}
#endif

#endif

/**
    @}
*/

/**
    @}
*/

/**
    @}
*/

/******************* (C) COPYRIGHT 2022 ...@gmail.com *****END OF FILE****/
