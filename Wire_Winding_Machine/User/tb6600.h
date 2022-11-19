#ifndef __TB6600_H__
#define __TB6600_H__

#ifdef __c_plus_plus
extern "C"
{
#endif

#include "stm32f1xx_hal.h"
#include "hw_config.h"
#include "tim.h"

typedef enum  {
	TB6600_RIGHT_2_LEFT = GPIO_PIN_RESET,
	TB6600_LEFT_2_RIGHT = GPIO_PIN_SET
} dir_t;

typedef enum  {
	TB6600_ENABLE = GPIO_PIN_SET,
	TB6600_DISABLE = GPIO_PIN_RESET
} tb6600_en_t;

typedef enum {
	PULSE_PER_REV_200  = 200,
	PULSE_PER_REV_400  = 400,
	PULSE_PER_REV_800  = 800,
	PULSE_PER_REV_1600 = 1600,
	PULSE_PER_REV_3200 = 3200
} pulse_rev_t;

typedef struct 
{
	uint16_t prescaler;
	uint16_t period;
} tim_t;

typedef struct {
	tb6600_en_t en_stt;                 // motor was enbale or disable
	dir_t direction;                    // motor direction left hand or right hand.
	pulse_rev_t pulse_per_rev;          // 200/400/800/1600/3200 pulse per revolution. 
	uint16_t step_number;               // which step motor is on
	uint32_t rev_number_cur;            // The number of revolution currently
	uint32_t number_of_rev;             // setup the number of revolution                  
	uint16_t rpm;                       // speed of step motor
	
	tim_t tim;                          // PPM
} tb6600_t;

void tb6600_init(tb6600_t *tb6600, tb6600_en_t en_stt, dir_t dir, pulse_rev_t pulse_rev);
void tb6600_set_direction(tb6600_t *tb6600, dir_t dir);
void tb6600_get_direction(tb6600_t *tb6600, dir_t *dir);
void tb6600_num_of_rev(tb6600_t *tb6600, uint8_t n_rev);
void tb6600_get_num_of_rev(tb6600_t *tb6600, uint8_t *n_rev);
void tb6600_set_speed(tb6600_t *tb6600, uint16_t speed);
void tb6600_get_speed(tb6600_t *tb6600, uint16_t *speed);
void tb6600_set_status(tb6600_t *tb6600, tb6600_en_t en_stt);
void tb6600_get_status(tb6600_t *tb6600, tb6600_en_t *en_stt);
void tb6600_get_rev_number(tb6600_t *tb6600, uint16_t *rev_num);

#ifdef __c_plus_plus
}
#endif

#endif
