/*
 * publish_task.cpp
 *
 *  Created on: Mar 18, 2019
 *      Author:
 */

#include "publish_task.h"


static ros::NodeHandle *nh_;

char hello[] = "hello world!";

void ROS_PublisheTaskHandler(void const * argument)
{
  /* USER CODE BEGIN ROS_PublisheTaskHandler */
  std_msgs::String str_msg;
  ros::Publisher chatter("chatter", &str_msg);

  nh_->advertise(chatter);

  /* Infinite loop */
  for(;;)
  {
	  str_msg.data = hello;
	  chatter.publish( &str_msg );
	  osDelay(1500);
  }

  /* USER CODE END ROS_PublisheTaskHandler */
}



uint32_t publishInitTask(ros::NodeHandle *nh)
{
	osThreadId ROS_PublisherTaskHandle;

	nh_ = nh;

	/* definition and creation of ROS_PublishTask */
	osThreadDef(ROS_PublisherTask, ROS_PublisheTaskHandler, osPriorityNormal, 0, 128);
	ROS_PublisherTaskHandle = osThreadCreate(osThread(ROS_PublisherTask), NULL);
	if (NULL == ROS_PublisherTaskHandle)
	{
		return 1;
	}
	return 0;
}
