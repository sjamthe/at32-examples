/*
 * spin_task.h
 *
 *  Created on: Mar 18, 2019
 *      Author:
 */

#ifndef INC_SPIN_TASK_H_
#define INC_SPIN_TASK_H_

#include "FreeRTOS.h"
#include "task.h"
//#include "main.h"
#include "cmsis_os.h"

#include "ros.h"
//#include "std_msgs/UInt16.h"

uint32_t rosSpinTaskInit(ros::NodeHandle *nh);


#endif /* INC_SPIN_TASK_H_ */
