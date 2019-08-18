/*
 * hearbeat_task.h
 *
 *  Created on: Mar 18, 2019
 *      Author:
 */

#ifndef INC_HEARBEAT_TASK_H_
#define INC_HEARBEAT_TASK_H_

#include  <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "bsp_led.h"
#include "cmsis_os.h"


uint32_t heartbeatInitTask(void);

#endif /* INC_HEARBEAT_TASK_H_ */
