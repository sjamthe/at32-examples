/*
 * subscribe_task.cpp
 *	Operate led #2
 *
 *  Created on: Mar 18, 2019
 *      Author: Shirish Jamthe
 * 
 */

#include "subscribe_task.h"

static ros::NodeHandle *nh_;

void led_cb(unsigned char* cmd_msg);

//QueueHandle_t subscribeQueueHandle;

static int useLed = 3;

void led_cb(unsigned char* msg)
{
	const std_msgs::UInt16 cmd_msg;
	cmd_msg.deserialize(msg);
	int16_t ledState = cmd_msg.data;
	//xQueueSend( subscribeQueueHandle, (uint16_t*)&cmd_msg.data, portMAX_DELAY);
	switch(ledState)
	{
		case 0: bsp_LedOff(2); break;
		case 1: bsp_LedOn(2); break;
	}
	useLed = 2;
}

void ROS_SubscribeTaskHandler(void const * argument)
{

  /* USER CODE BEGIN ROS_SpinTaskHandler */

  /* Infinite loop */
  for(;;)
  {
	//   if(xQueueReceive( subscribeQueueHandle, &ledState, portMAX_DELAY))
	//   {
	// 	  switch(ledState)
	// 	  {
	// 		case 0: bsp_LedOff(2); break;
	//    	  	case 1: bsp_LedOn(2); break;
	// 	  }
	//   }
	//   else 
	//   {
		//bsp_LedToggle(useLed);
		osDelay(100);
	//   }
	//   osDelay(100);
  }

  /* USER CODE END ROS_SubscribeTaskHandler */
}

uint32_t rosSubscribeInitTask(ros::NodeHandle *nh)
{

	osThreadId ROS_SubscribeTaskHandle;
	ros::SubscriberType sub ;

	nh_ = nh;
	//nh_->subscribe(sub_led);

	const std_msgs::UInt16 msg;
	sub.topic_name = "led";
	sub.message_type = msg.getType();
	sub.md5sum = msg.getMD5();
	sub.callback = led_cb;
	
	nh_->addSubscriber(sub);
	
	osDelay(10);

	/* Create the queue(s) */
	/* definition and creation of subscribeQueue */
	// subscribeQueueHandle = xQueueCreate( 4, sizeof(uint16_t) );
	// if (NULL ==  subscribeQueueHandle)
	// {
	// 	return 1;
	// }

	/* definition and creation of ROS_SubscribeTask */
	osThreadDef(ROS_SubscribeTask, ROS_SubscribeTaskHandler, osPriorityNormal, 0, 128);
	ROS_SubscribeTaskHandle = osThreadCreate(osThread(ROS_SubscribeTask), NULL);
	if (NULL == ROS_SubscribeTaskHandle)
	{
	return 1;
	}

	 return 0;

}
