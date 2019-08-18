/*
 * spin_task.cpp
 *
 *  Created on: Mar 18, 2019
 *      Author:
 */

#include <stdio.h>
#include "bsp_led.h"
#include "spin_task.h"

static ros::NodeHandle *nh_;


void ROS_SpinTaskHandler(void const * argument)
{

  /* USER CODE BEGIN ROS_SpinTaskHandler */

  /* Infinite loop */
  for(;;)
  {
	bsp_LedToggle(2);
	printf("This is spin Task\r\n");
	osDelay(1000);
	//nh_->initNode();
	nh_->spinOnce1();
  }
  /* USER CODE END ROS_SpinTaskHandler */
}


/*
 * Create spin task
 */
uint32_t rosSpinTaskInit(ros::NodeHandle *nh)
{
	osThreadId ROS_SpinTaskHandle;

	nh_ = nh;

	/* definition and creation of ROS_SpinTask */
	osThreadDef(ROS_SpinTask, ROS_SpinTaskHandler, osPriorityIdle, 0, 128);
	ROS_SpinTaskHandle = osThreadCreate(osThread(ROS_SpinTask), NULL);
	if (NULL == ROS_SpinTaskHandle)
	{
		return 1;
	}
	return 0;

}

