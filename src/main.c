/**
 * |----------------------------------------------------------------------
 * | Copyright (C) Pawel Wisniewski, 2016
 * |
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * |----------------------------------------------------------------------
 */
/* Include core modules */
#include "stm32fxxx_hal.h"
/* Include my libraries here */
#include "defines.h"
#include "config.h"
#include "tm_stm32_delay.h"
#include "tm_stm32_usart.h"

#ifdef WITH_LAN
//#include "lan.h"
#endif // WITH_LAN

__attribute__ ((used)) int putchar(int ch) {
	/* Send over debug USART */
	TM_USART_Putc(USART1, ch);

	/* Return OK */
	return ch;
}

#include "os_compat.h"
#include "ug2864.h"

#define PROJECT_NAME	"XHTML_TERMINAL"
#define AUTHOR			"Pablo <w_pawel74@tlen.pl>"

int main(void) {

	/* Init system */
	TM_RCC_InitSystem();

	TM_USART_Init(USART1, TM_USART_PinsPack_1, 115200);

	_D(("---------------------------------------------\n"));
	_D((" Project: %s\n", PROJECT_NAME));
	_D((" Author: %s\n", AUTHOR));
	_D((" Release date: %s %s\n", __DATE__, __TIME__));
	_D(("---------------------------------------------\n"));

	/* Init HAL layer */
	HAL_Init();

	/* Init delay */
	TM_DELAY_Init();

	UG2864_init();

#ifdef WITH_LAN
	// eth initialize
	LAN_init();
#endif // WITH_LAN

	while(1) {

#ifdef WITH_LAN
		LAN_poll();
#endif // WITH_LAN

	}

	return 0;
}
