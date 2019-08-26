/*
* Implement all ROS functions here.
*/

#include "ros.h"
#include "std_msgs/ROSString.h"

ros::NodeHandle nh; /* ROS node handle */

ros::PublisherType *chatter;

void ros_init()
{
    /* ROS init, we can start UART hear in not in bsp */ 
    //nh_ = &nh;
    nh.initNode();

    /* Register Publisher Chatter */
    std_msgs::String str_msg;
    chatter = nh.addPublisher("chatter", &str_msg);
}

void ros_run()
{
    nh.spinOnce1();

    //Note: If Msg is declared outside function/globally publish1 doesn't work.
    //may be constructor is not getting called.
    std_msgs::String str_msg;

    char buf[512];
    sprintf(buf,"Millis %d",millis());
    str_msg.data = buf;
    
    nh.publish1(chatter->topic_id, &str_msg); 

}