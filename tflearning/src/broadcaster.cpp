#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <turtlesim/Pose.h>

std::string turtle_name;

void posecallback(const turtlesim::PoseConstPtr &msg)
{
    static tf::TransformBroadcaster br;

    tf::Transform transform;
    transform.setOrigin(tf::Vector3(msg->x,msg->y,0.0));
    tf::Quaternion q;
    q.setRPY(0,0,msg->theta);
    transform.setRotation(q);

    br.sendTransform(tf::StampedTransform(transform,ros::Time::now(),"world",turtle_name));
    
}

int main(int argc, char  *argv[])
{
    /* code */
    ros::init(argc,argv,"broadcaster");
    if (argc!=2)
    {
        ROS_ERROR("need turtle name as argument");
        return -1;
    }
    turtle_name=argv[1];

    ros::NodeHandle nh;
    ros::Subscriber sub=nh.subscribe(turtle_name+"/pose",10,&posecallback);
    ros::spin();




    return 0;
}
