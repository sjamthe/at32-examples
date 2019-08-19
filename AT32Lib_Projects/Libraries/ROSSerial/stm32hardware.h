/*
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2011, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *  * Neither the name of Willow Garage, Inc. nor the names of its
 *    contributors may be used to endorse or promote prducts derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef STM32HARDWARE_H_
#define STM32HARDWARE_H_

#include "FreeRTOS.h"
#include "bsp_uart_fifo.h"
#include <stdio.h>

class STM32Hardware
{
public:
	STM32Hardware()
	{
	}

	/*
	 * Method: init
	 * ----------------------------
	 *   Initialize the STM32 hardware specific to ROS like UART
	 *   parameters: none
	 *   returns: none
	 */
	void init(void)
	{

	}

	/*
     * Method: read
	 * ----------------------------
	 *   Read a byte of data from ROS connection
	 *   parameters: none
	 *   returns: data, or -1 if there are no data
	 */
	int read(void)
	{
		uint8_t ucData = -1;
		if(comGetChar(COM1,&ucData) == 0) {
			return -1;
		}
		//printf("Got %c\n",ucData);
		return ucData;
	}

	/*
	 * Method: write
     * ----------------------------
	 *   Send data to ROS connection
	 *   parameters: pointer to data array, length of data
	 *   returns: none
	 */
	void write(uint8_t* data, uint32_t length)
	{
		comSendBuf(COM1,data,length);
	}

	/*
	 * Method: time
	 * ----------------------------
     *   Returns milliseconds since start of program
	 *   parameters: none
	 *   returns: time in milliseconds
	 */
	uint32_t time(void)
	{
		return (uint32_t) xTaskGetTickCount();
	}

};

#endif /* STM32H7HARDWARE_H_ */
