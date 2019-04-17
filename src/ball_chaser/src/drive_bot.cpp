#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"
#include <std_msgs/Float64.h>


class DriveBot{
public:
  DriveBot(){
    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    _motor_command_publisher = _n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);


    // Define a safe_move service with a handle_safe_move_request callback function
    _service = _n.advertiseService("/ball_chaser/command_robot", &DriveBot::handle_drive_request, this);
    ROS_INFO("Ready to send robot commands");
  }

// This callback function executes whenever a safe_move service is requested
bool handle_drive_request(ball_chaser::DriveToTarget::Request& req,
    ball_chaser::DriveToTarget::Response& res)
{

    ROS_INFO("DriveToTarget received - linear_x:%1.2f, angular_z:%1.2f", (float)req.linear_x, (float)req.angular_z);

    geometry_msgs::Twist motor_command;

    motor_command.linear.x = req.linear_x;
    motor_command.angular.z = req.angular_z;

    _motor_command_publisher.publish(motor_command);

    std::ostringstream stringStream;
    stringStream << req.linear_x << " " << req.angular_z;
    res.msg_feedback = stringStream.str();

    // ROS_INFO_STREAM(res.msg_feedback);

    return true;
}
private:
  ros::NodeHandle _n;
  ros::Publisher _motor_command_publisher;
  ros::ServiceServer _service;
};


int main(int argc, char** argv)
{
    // Initialize the arm_mover node and create a handle to it
    ros::init(argc, argv, "drive_bot");

    DriveBot driver;

    // Handle ROS communication events
    ros::spin();

    return 0;
}