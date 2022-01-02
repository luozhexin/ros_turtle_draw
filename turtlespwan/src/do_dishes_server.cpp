#include <ros/ros.h>
#include "turtlespwan/dodishesAction.h"
#include <actionlib/server/simple_action_server.h>

typedef actionlib::SimpleActionServer<turtlespwan::dodishesAction> Server;

void excute(const turtlespwan::dodishesGoalConstPtr& goal, Server* as)
{
    ros::Rate r(1);
    turtlespwan::dodishesFeedback feedback;
    ROS_INFO("dishwasher %d us working",goal->dishwasher_id);

    for(int i=1;i<=10;i++)
    {
        feedback.percent_complete=i*10;
        as->publishFeedback(feedback);
        r.sleep();
    }
    ROS_INFO("dishwasher %d finish working",goal->dishwasher_id);
    as->setSucceeded();

}

int main(int argc, char  *argv[])
{
    /* code */
    ros::init(argc,argv,"dodishes_server");

    ros::NodeHandle nh;

    Server server(nh,"dodishes",boost::bind(&excute,_1,&server),false);

    server.start();

    ros::spin();

    return 0;
}
