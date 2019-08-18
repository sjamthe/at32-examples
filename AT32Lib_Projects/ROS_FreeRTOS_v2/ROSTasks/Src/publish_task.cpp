/*
 * publish_task.cpp
 *
 *  Created on: Mar 18, 2019
 *      Author:
 */

#include "publish_task.h"
#include "bsp_led.h"

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
	  bsp_LedToggle(2);
	  //printf("nh_ = %x, id_=%d\n",nh_,chatter.id_);
	  //chatter.publish( &str_msg ); //didn't work.
	   int ret = nh_->publish1(chatter.id_, &str_msg); //publish() doesn't work same like spinOnce() but publish1 works
	   if(ret <=0) {
		   printf("Failed to publish %d\n",ret);
	   }
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
