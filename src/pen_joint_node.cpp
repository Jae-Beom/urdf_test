#include <string>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>


int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
    ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
    ros::Rate loop_rate(10);

    double base_to_pen_rev1=0, delta=0.1;

    sensor_msgs::JointState joint_state;

    while (ros::ok()) {
        //update joint_state
        joint_state.header.stamp = ros::Time::now();
        joint_state.name.resize(1);
        joint_state.position.resize(1);
        joint_state.name[0] ="base_to_pen_rev1";
        joint_state.position[0] = base_to_pen_rev1;
        
        // Publish pendulum state
        joint_pub.publish(joint_state);
        
        // Create new pendulum state
        base_to_pen_rev1 += delta;
        if (base_to_pen_rev1 >= 3.14 || base_to_pen_rev1 <= -3.14) delta *= -1;
        
        // This will adjust as needed per iteration
        loop_rate.sleep();
    }
    
    return 0;
}

