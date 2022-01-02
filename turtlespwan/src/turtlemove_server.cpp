#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include "turtlespwan/turtlemoveAction.h"
#include <turtlesim/Pose.h>
#include <geometry_msgs/Twist.h>

typedef actionlib::SimpleActionServer<turtlespwan::turtlemoveAction> Server;


ros::Publisher turtle_vel;

struct Myturtle
{
    /* data */
    float x;
    float y;
    float theta;
}turtle_original_pose,turtle_target_pose;



void posecallback(const turtlesim::PoseConstPtr& msg)
{
    ROS_INFO("turtle1+postion:(%f,%f,%f)",msg->x,msg->y,msg->theta);
    turtle_original_pose.x=msg->x;
    turtle_original_pose.y=msg->y;
    turtle_original_pose.theta=msg->theta;
}

void execute(const turtlespwan::turtlemoveGoalConstPtr &goal,Server *as)
{
    turtlespwan::turtlemoveFeedback feedback;
    ROS_INFO("turtlemove is working");
    turtle_target_pose.x=goal->target_x;
    turtle_target_pose.y=goal->target_y;
    turtle_target_pose.theta=goal->target_theata;

    geometry_msgs::Twist vel_msgs;
    float break_flag;
    
    while(1)
    {
        ros::Rate r(10);
        vel_msgs.angular.z=4.0*(atan2(turtle_target_pose.y-turtle_original_pose.y,
        turtle_target_pose.x-turtle_original_pose.x)-turtle_original_pose.theta);

        vel_msgs.linear.x=0.5*sqrt(pow(turtle_target_pose.x-turtle_original_pose.x,2)+
        pow(turtle_target_pose.y-turtle_original_pose.y,2));

        break_flag=sqrt(pow(turtle_target_pose.x-turtle_original_pose.x,2)+
        pow(turtle_target_pose.y-turtle_original_pose.y,2));
        turtle_vel.publish(vel_msgs);

        feedback.current_x=turtle_original_pose.x;
        feedback.current_y=turtle_original_pose.y;
        feedback.current_theta=turtle_original_pose.theta;

        as->publishFeedback(feedback);
        ROS_INFO("breakflag is %f",break_flag);
        if(break_flag<0.1) break;
        r.sleep();
    }

    ROS_INFO("turtlemove is finished.");
    as->setSucceeded();

}


int main(int argc, char  *argv[])
{
    /* code */
    ros::init(argc,argv,"turtlemove_server");

    ros::NodeHandle nh,turtle_node;

    

    ros::Subscriber sub=turtle_node.subscribe("turtle1/pose",10,&posecallback);
    turtle_vel=turtle_node.advertise<geometry_msgs::Twist>("turtle1/cmd_vel",10);


    Server server(nh,"turtle_move",boost::bind(&execute, _1, &server),false);
    server.start();
    ros::spin();

    return 0;
}
