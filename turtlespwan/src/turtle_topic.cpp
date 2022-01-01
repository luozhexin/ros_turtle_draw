#include <ros/ros.h>
#include <turtlesim/Pose.h>


void domsg(const turtlesim::Pose::ConstPtr& msg)
{
    ROS_INFO("pose_x is %0.6f,pose_y is %0.6f ",msg->x,msg->y);
}

int main(int argc, char  *argv[])
{
    /* code */
    ros::init(argc,argv,"turtle_subsciber");

    ros::NodeHandle nh;

    ros::Subscriber t_sub=nh.subscribe<turtlesim::Pose>("/turtle2/pose",10,domsg);

    ros::spin();
    return 0;
}
