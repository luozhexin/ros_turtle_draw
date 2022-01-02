#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <turtlesim/Spawn.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char  *argv[])
{
    /* code */
    ros::init(argc,argv,"my_tf_listener");
    ros::NodeHandle nh;

    ros::service::waitForService("spawn");
    ros::ServiceClient add_turtle=nh.serviceClient<turtlesim::Spawn>("spawn");
    turtlesim::Spawn srv;
    add_turtle.call(srv);

    ros::Publisher turtle_vel=nh.advertise<geometry_msgs::Twist>("turtle2/cmd_vel",10);

    tf::TransformListener listener;
    ros::Rate r(10);
    while (ros::ok())
    {
        /* code */
        tf::StampedTransform transform;
        try
        {
            listener.waitForTransform("/turtle2","/turtle1",ros::Time(0),ros::Duration(3.0));
            listener.lookupTransform("/turtle2","/turtle1",ros::Time(0),transform);
        }
        catch(tf::TransformException &ex)
        {
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
            continue;
        }
        

        geometry_msgs::Twist vel_msg;
        vel_msg.angular.z=4.0*atan2(transform.getOrigin().y(),transform.getOrigin().x());
        vel_msg.linear.x=0.5*sqrt(pow(transform.getOrigin().x(),2)+pow(transform.getOrigin().y(),2));
        turtle_vel.publish(vel_msg);
        r.sleep();
    }
    

    return 0;
}
