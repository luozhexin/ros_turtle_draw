#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char  *argv[])
{
    /* code */
    ros::init(argc,argv,"turtle_controller");

    ros::NodeHandle nh;

    ros::Publisher t_pub=nh.advertise<geometry_msgs::Twist>("turtle2/cmd_vel",10);

    geometry_msgs::Twist msg;

    msg.angular.z=2;
    msg.linear.x=2;

    ros::Rate rate(10);

    while (ros::ok())
    {
        /* code */
        t_pub.publish(msg);
        rate.sleep();
        ros::spinOnce();
    }
    
    

    
    return 0;
}
