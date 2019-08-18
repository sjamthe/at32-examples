/*
 * subscribe_task.h
 *
 *  Created on: Mar 18, 2019
 *      Author:
 */

#ifndef INC_SUBSCRIBE_TASK_H_
#define INC_SUBSCRIBE_TASK_H_

#include "FreeRTOS.h"
#include "task.h"
#include "bsp_led.h"
#include "cmsis_os.h"

#include "ros.h"
#include "std_msgs/UInt16.h"

uint32_t rosSubscribeInitTask(ros::NodeHandle *nh);

#endif /* INC_SUBSCRIBE_TASK_H_ */
