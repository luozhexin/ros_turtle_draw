#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include "turtlespwan/dodishesAction.h"


typedef actionlib::SimpleActionClient<turtlespwan::dodishesAction> Client;

void doneCb(const actionlib::SimpleClientGoalState &state,
        const turtlespwan::dodishesResultConstPtr &result)
{
    ROS_INFO("yay!the dishes are now clean");
    ros::shutdown();
}

void activeCb()
{
    ROS_INFO("goal just went active");
}

void feedbackCb(const turtlespwan::dodishesFeedbackConstPtr &feeeback)
{
    ROS_INFO("percent_complete: %f",feeeback->percent_complete);
}

int main(int argc, char  *argv[])
{
    /* code */
    ros::init(argc,argv,"dodishes_client");
    ros::NodeHandle nh;

    Client client("dodishes",true);

    ROS_INFO("waiting for action server to start.");
    client.waitForServer();
    ROS_INFO("action server started, sending goal.");
    turtlespwan::dodishesGoal goal;
    goal.dishwasher_id=1;

    client.sendGoal(goal,&doneCb,&activeCb,&feedbackCb);
    ros::spin();
    return 0;
}
