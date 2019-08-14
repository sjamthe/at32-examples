/*
 * subscribe_task.cpp
 *
 *  Created on: Mar 18, 2019
 *      Author:
 */

#include "subscribe_task.h"

static ros::NodeHandle *nh_;

void led_cb(const std_msgs::UInt16& cmd_msg);

ros::Subscriber<std_msgs::UInt16> sub_led("led", led_cb);


QueueHandle_t subscribeQueueHandle;

void led_cb(const std_msgs::UInt16& cmd_msg)
{
	xQueueSend( subscribeQueueHandle, (uint16_t*)&cmd_msg.data, portMAX_DELAY);
}


void ROS_SubscribeTaskHandler(void const * argument)
{

  /* USER CODE BEGIN ROS_SpinTaskHandler */
  static uint16_t ledState = 0;

  /* Infinite loop */
  for(;;)
  {
	  if(xQueueReceive( subscribeQueueHandle, &ledState, portMAX_DELAY))
	  {
		  switch(ledState)
		  {
		  	  case 0: HAL_GPIO_WritePin(SUBLED_GPIO_Port, SUBLED_Pin, GPIO_PIN_RESET); break;
	   		  case 1: HAL_GPIO_WritePin(SUBLED_GPIO_Port, SUBLED_Pin, GPIO_PIN_SET); break;
		  }
	  }
  }

  /* USER CODE END ROS_SubscribeTaskHandler */
}



uint32_t rosSubscribeInitTask(ros::NodeHandle *nh)
{
	osThreadId ROS_SubscribeTaskHandle;

	 nh_ = nh;
	 nh_->subscribe(sub_led);
	 osDelay(1);

	 /* Create the queue(s) */
	 /* definition and creation of subscribeQueue */
	 subscribeQueueHandle = xQueueCreate( 4, sizeof(uint16_t) );
	 if (NULL ==  subscribeQueueHandle)
	 {
		 return 1;
	 }

	 /* definition and creation of ROS_SubscribeTask */
	 osThreadDef(ROS_SubscribeTask, ROS_SubscribeTaskHandler, osPriorityNormal, 0, 128);
	 ROS_SubscribeTaskHandle = osThreadCreate(osThread(ROS_SubscribeTask), NULL);
	 if (NULL == ROS_SubscribeTaskHandle)
	 {
	 	return 1;
	 }

	 return 0;

}
