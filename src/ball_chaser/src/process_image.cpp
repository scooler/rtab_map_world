#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

class ProcessImage{

public:
  ProcessImage(ros::NodeHandle &nh);
  void process_image_callback(const sensor_msgs::Image img);

private:

  ros::ServiceClient _client;
  ros::Subscriber _sub1;
  ros::NodeHandle &_nh;

  void drive_robot(float lin_x, float ang_z);

  uint32_t findBall(const sensor_msgs::Image img);
};

ProcessImage::ProcessImage(ros::NodeHandle &nh):
  _nh(nh),
  _client(nh.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot")),
  _sub1(nh.subscribe("/camera/rgb/image_raw", 10, &ProcessImage::process_image_callback, this))
{
  // _sub1 = nh.subscribe("/camera/rgb/image_raw", 10, &ProcessImage::process_image_callback, this); // this works too ...
  ROS_INFO("Ready to process_image16");
}

void ProcessImage::process_image_callback(const sensor_msgs::Image img) {

  ROS_INFO_THROTTLE(1, "Callback called");
  uint32_t ballPosition = findBall(img);
  if (ballPosition == 0) {
    ROS_INFO_THROTTLE(1, "No Ball - Stop Robot");
    drive_robot(0, 0);
    return; // don't do anything
  }
  ROS_INFO_THROTTLE(1, "Found position %zu", ballPosition);

  if (ballPosition < img.step / 3){
    ROS_INFO_THROTTLE(1, "Driving to left");
    drive_robot(0, 1); // turn left
  } else if (ballPosition < img.step*2 / 3) {
    ROS_INFO_THROTTLE(1, "Driving forward");
    drive_robot(1, 0); // drive forward
  } else {
    ROS_INFO_THROTTLE(1, "Driving right");
    drive_robot(0, -1); // turn right
  }

}

void ProcessImage::drive_robot(float lin_x, float ang_z){
    // ROS_INFO("Driving Bot lin_x: %10.4f , ang_z: %10.4f", lin_x, ang_z);

    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    if (!_client.call(srv)) {
        ROS_ERROR("Failed to call service to drive_robot");
    };
}


uint32_t ProcessImage::findBall(const sensor_msgs::Image img) {

  int white_pixel = 255;
  for (int i = 0; i < img.height * img.step; i+= 3) {
      if (img.data[i] == white_pixel && img.data[i+1] == white_pixel && img.data[i+2] == white_pixel) {
        ROS_INFO_THROTTLE(1, "Found white in pixel %d with img.step: %d ", i, img.step);
        return (i % img.step) + 1; // +1 so that it's NEVER 0 - 0 being "NOT FOUND"
      }
  }
  return 0;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "process_image");

    ros::NodeHandle nh;
    ProcessImage processImage(nh);

    // ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);
    // ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, &ProcessImage::process_image_callback, &processImage);


    // Handle ROS communication events
    ros::spin();

    return 0;
}

