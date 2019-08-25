/*
* Implement all ROS functions here.
*/

#include "ros.h"

ros::NodeHandle nh; /* ROS node handle */

void ros_init()
{
    /* ROS init, we can start UART hear in not in bsp */ 
    nh.initNode();
}

void ros_run()
{
    nh.spinOnce1(); 

}