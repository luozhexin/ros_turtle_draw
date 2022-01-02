#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <geometry_msgs/Twist.h>
#include "turtlespwan/turtlemoveAction.h"
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<turtlespwan::turtlemoveAction> Client;

struct Myturtle
{
    /* data */
    float x;
    float y;
    float theta;
}turtle_present_pose;

void doneCb(const actionlib::SimpleClientGoalState &state,
    const turtlespwan::turtlemoveResultConstPtr& result)
{
    ROS_INFO("yay!the turtlemove is finished");
    ros::shutdown();
}

void activeCb()
{
    ROS_INFO("goal just went active");
}

void feedbackCb(const turtlespwan::turtlemoveFeedbackConstPtr &feedback)
{
    ROS_INFO("present_pose is :%f %f %f",feedback->current_x,feedback->current_y,feedback->current_theta);
    
}


int main(int argc, char  *argv[])
{
    /* code */
    ros::init(argc,argv,"turtleclient");

    Client client("turtle_move",true);

    ROS_INFO("waiting for action server to start");
    client.waitForServer();
    ROS_INFO("action server started,sending goal");

    turtlespwan::turtlemoveGoal goal;
    goal.target_x=1;
    goal.target_y=1;
    goal.target_theata=0;

    client.sendGoal(goal,&doneCb,&activeCb,&feedbackCb);

    ros::spin();


    return 0;
}
