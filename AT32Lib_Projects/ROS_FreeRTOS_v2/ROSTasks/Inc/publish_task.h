/*
 * publish_task.h
 *
 *  Created on: Mar 18, 2019
 *      Author:
 */

#ifndef INC_PUBLISH_TASK_H_
#define INC_PUBLISH_TASK_H_

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

#include "ros.h"
#include "std_msgs/ROSString.h"

uint32_t publishInitTask(ros::NodeHandle *nh);

#endif /* INC_PUBLISH_TASK_H_ */
