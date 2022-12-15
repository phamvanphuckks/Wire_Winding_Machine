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
	TIM_HandleTypeDef *htim;
	
	uint16_t prescaler;
	uint16_t period;
} tim_t;

typedef struct {
	tb6600_en_t en_stt;                 // motor was enbale or disable
	dir_t direction;                    // motor direction left hand or right hand.
	pulse_rev_t pulse_per_rev;          // 200/400/800/1600/3200 pulse per revolution.
	uint16_t step_number;               // which step motor is on
	uint32_t rev_number_cur;            // The number of revolution currently
	uint16_t rpm;                       // speed of step motor
	uint32_t number_of_rev_setup;       // setup the number of revolution
	uint8_t number_of_rev_en;           // enable/disable setting the number of revolution
	
	tim_t tim;                          // PPM
} tb6600_t;

typedef enum {
	CMD_DIR         = 0x01,   // FORWARD and REVERSE DIRECTION
	CMD_NUM_REVO    = 0x02,
	CMD_RPM         = 0x03,
  CMD_START       = 0x04,
  CMD_STOP        = 0x05,
  CMD_PAUSE       = 0x06,
  CMD_RESTART     = 0x07,
	CMD_CLEAR_SETUP = 0x08,
	CMD_REVO_CUR    = 0x09
}	command_type_t;

typedef struct {
	uint8_t header[2];
	uint8_t length;
	uint8_t command;
	uint8_t data[3];
	uint8_t check_sum;
} data_frame_t;

void tb6600_init(tb6600_t *tb6600, tb6600_en_t en_stt, dir_t dir, pulse_rev_t pulse_rev);
void tb6600_set_direction(tb6600_t *tb6600, dir_t dir);
void tb6600_get_direction(tb6600_t *tb6600, dir_t *dir);
void tb6600_set_num_of_rev(tb6600_t *tb6600, uint8_t n_rev, uint8_t stt);
void tb6600_get_num_of_rev(tb6600_t *tb6600, uint8_t *n_rev);
void tb6600_set_rpm(tb6600_t *tb6600, uint16_t rpm);
void tb6600_get_rpm(tb6600_t *tb6600, uint16_t *rpm);
void tb6600_set_status(tb6600_t *tb6600, tb6600_en_t en_stt);
void tb6600_get_status(tb6600_t *tb6600, tb6600_en_t *en_stt);
void tb6600_get_rev_number(tb6600_t *tb6600, uint16_t *rev_num);
void tb6600_reset(tb6600_t *tb6600);

void tb6600_encode_data(data_frame_t *data_frame, command_type_t cmd, uint32_t data);
void tb6600_send_data(const data_frame_t data_frame);

#ifdef __c_plus_plus
}
#endif

#endif
