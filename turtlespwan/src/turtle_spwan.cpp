#include <ros/ros.h>
#include <turtlesim/Spawn.h>
#include <string.h>
#include <turtlesim/Pose.h>

int main(int argc, char  *argv[])
{
    /* code */

    int i=0;
    ros::init(argc,argv,"turtle_spawn");

    ros::NodeHandle nh;

    ros::service::waitForService("/spawn");
    ros::ServiceClient add_turtle=nh.serviceClient<turtlesim::Spawn>("/spawn");

    turtlesim::Spawn srv;

    for(i=2;i<5;i++)
    {
    srv.request.x=5.54+atoll(argv[1])*(double)(i-1);
    srv.request.y=5.54;
    srv.request.theta=0;
    srv.request.name="turtle"+std::to_string(i);

    ROS_INFO("call service to spwan turtle[x:%0.6f,y:%0.6f,name:%s]",
    srv.request.x,srv.request.y,srv.request.name.c_str());

    add_turtle.call(srv);

    ROS_INFO("spwan turtle successfully [name:%s]",srv.request.name.c_str());

    }




    
    return 0;
}
