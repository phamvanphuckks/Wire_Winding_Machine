#include "tb6600.h"
#include "stdio.h"

/*
 * Init the tb6600
 */
void tb6600_init(tb6600_t *tb6600, tb6600_en_t en_stt, dir_t dir, pulse_rev_t pulse_rev)
{
	tb6600->en_stt                 = en_stt;
	tb6600->direction              = dir;
	tb6600->pulse_per_rev          = pulse_rev;
	tb6600->rev_number_cur         = 0;
	tb6600->step_number            = 0;
	tb6600->rpm                    = 0;
	tb6600->number_of_rev_setup    = 0;
	tb6600->number_of_rev_en       = 0;

	tb6600->tim.period             = 0;
	tb6600->tim.prescaler          = 0;

	tb6600_set_direction(tb6600, tb6600->direction);
	tb6600_set_status(tb6600, tb6600->en_stt);
}

/*
 * set direction for step motor
 */
void tb6600_set_direction(tb6600_t *tb6600, dir_t dir)
{
	tb6600->direction = dir;

	HAL_GPIO_WritePin(TB6600DIR_PORT, TB6600DIR_PIN, (GPIO_PinState)tb6600->direction);
}

/*
 * get direction for step motor
 */
void tb6600_get_direction(tb6600_t *tb6600, dir_t *dir)
{
	(*dir) = tb6600->direction;
}

/*
 * set number of revolution to count down to 0
 */
void tb6600_set_num_of_rev(tb6600_t *tb6600, uint8_t n_rev, uint8_t stt)
{
	tb6600->number_of_rev_setup = n_rev;
	tb6600->number_of_rev_en = stt;
}

/*
 * get number of revolution to count down to 0
 */
void tb6600_get_num_of_rev(tb6600_t *tb6600, uint8_t *n_rev)
{
	(*n_rev) = tb6600->number_of_rev_setup;
}

/*
 * set rpm for step motor
 */
void tb6600_set_rpm(tb6600_t *tb6600, uint16_t rpm)
{
	tb6600->rpm = rpm;
	
	// timer
	tb6600->tim.period = (uint16_t)((float)(60.0/((tb6600->rpm)*(tb6600->pulse_per_rev)))/(float)(1.0/(12000.0)))/2 - 1;
	
	if(tb6600->tim.period < 1)
	{
		tb6600->tim.period = 1;
	}
	
  if(tb6600->tim.period > 65535)
	{
		tb6600->tim.period = 65535;
	}
	
//	__HAL_TIM_SET_AUTORELOAD(&htim2, tb6600->tim.period);
	
	/* USER CODE END TIM2_Init 1 */
	htim2.Init.Period = tb6600->tim.period;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
}

/*
 * get rpm for step motor
 */
void tb6600_get_rpm(tb6600_t *tb6600, uint16_t *rpm)
{
	(*rpm) = tb6600->rpm;
}

/*
 * enable/disable step motor
 */
void tb6600_set_status(tb6600_t *tb6600, tb6600_en_t en_stt)
{
	tb6600->en_stt = en_stt;
	HAL_GPIO_WritePin(TB6600EA_PORT, TB6600EA_PIN, (GPIO_PinState)en_stt);
}

/*
 * get status of step motor
 */
void tb6600_get_status(tb6600_t *tb6600, tb6600_en_t *en_stt)
{
	(*en_stt) = tb6600->en_stt;
}

/*
 * get number of revolution currently
 */
void tb6600_get_rev_number(tb6600_t *tb6600, uint16_t *rev_num)
{
	(*rev_num) = tb6600->rev_number_cur;
}

/*
 * Reset motor parameter
 */
void tb6600_reset(tb6600_t *tb6600)
{
	tb6600->rev_number_cur         = 0;
	tb6600->step_number            = 0;
	tb6600->rpm                    = 0;
	tb6600->number_of_rev_setup    = 0;
	tb6600->number_of_rev_en       = 0;
}

void tb6600_encode_data(data_frame_t *data_frame, command_type_t cmd, uint32_t data)
{
	data_frame->header[0] = 0x55;
	data_frame->header[1] = 0xAA;
	data_frame->length    = 0x04;
	data_frame->command   = cmd;
	data_frame->data[2]   = data & 0xFF;
	data_frame->data[1]   = (data >> 8)  & 0xFF;
	data_frame->data[0]   = (data >> 16) & 0xFF;
	data_frame->check_sum = (uint8_t) (0xFF - (data_frame->length + (uint8_t) data_frame->command + data_frame->data[0] + data_frame->data[1] + data_frame->data[2]));
}

void tb6600_send_data(const data_frame_t data_frame)
{
	printf("%.02x%.02x%.02x%.02x%.02x%.02x%.02x%.02x", data_frame.header[0], data_frame.header[1], data_frame.length, 
	                                                                       data_frame.command, 
	                                                                       data_frame.data[0],
	                                                                       data_frame.data[1],
	                                                                       data_frame.data[2],
	                                                                       data_frame.check_sum);
}
