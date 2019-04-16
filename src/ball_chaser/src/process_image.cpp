#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>


// This callback function continuously executes and reads the image data
// void process_image_callback(const sensor_msgs::Image img)
// {

//     ROS_INFO("Callback!");
//     int white_pixel = 255;

//     // TODO: Loop through each pixel in the image and check if there's a bright white one
//     // Then, identify if this pixel falls in the left, mid, or right side of the image
//     // Depending on the white ball position, call the drive_bot function and pass velocities to it
//     // Request a stop when there's no white ball seen by the camera
// }

class ProcessImage{

public:
  ProcessImage(ros::NodeHandle &nh);
  void process_image_callback(const sensor_msgs::Image img);
  // {

  //   // Define a client service capable of requesting services from safe_move
  //   _client = nh.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

  //   // ros::Subscriber sub = _n.subscribe("/camera/rgb/image_raw", 10, &ProcessImage::process_image_callback, this);

  //   // ros::Subscriber sub1 = _n.subscribe("/camera/rgb/image_raw", 10, &ProcessImage::process_image_callback, this);


  //   // ros::NodeHandle n;
  //   // ros::Subscriber sub1 = _n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);
  //   ros::Subscriber sub1 = nh.subscribe("/camera/rgb/image_raw", 10, &ProcessImage::process_image_callback, this);

  //   ROS_INFO("Ready to process_image15");
  // }

private:

// Define global vector of joints last position, moving state of the arm, and the client that can request services
  // std::vector<double> joints_last_position{ 0, 0 };
  // bool moving_state = false;
  ros::ServiceClient _client;
  ros::Subscriber _sub1;
  ros::NodeHandle &_nh;

  // void drive_robot(float lin_x, float ang_z){
  //     ROS_INFO("Driving Bot lin_x: %10.4f , ang_z: %10.4f", lin_x, ang_z);
  //     // TODO: Request a service and pass the velocities to it to drive the robot

  //     ball_chaser::DriveToTarget srv;
  //     srv.request.linear_x = lin_x;
  //     srv.request.angular_z = ang_z;

  //     if (!_client.call(srv)) {
  //         ROS_ERROR("Failed to call service to drive_robot");
  //     };
  // }


  // uint32_t findBall(const sensor_msgs::Image img) {

  //   int white_pixel = 255;
  //   for (int i = 0; i < img.height * img.step; i++) {
  //       if (img.data[i] == white_pixel) {
  //         return i;// % img.step;
  //       }
  //   }
  //   return -1;
  // }
};

ProcessImage::ProcessImage(ros::NodeHandle &nh):
    _nh(nh),
    _client(nh.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot")),
    _sub1(nh.subscribe("/camera/rgb/image_raw", 10, &ProcessImage::process_image_callback, this))
    {
      ROS_INFO("Ready to process_image16");
    }

void ProcessImage::process_image_callback(const sensor_msgs::Image img)
  {

    ROS_INFO("Callback called");
    // uint32_t ballPosition = findBall(img);
    // // ROS_INFO_THROTTLE(1, "Found position %zu", ballPosition);
    // if (ballPosition <= 0) {
    //   return; // don't do anything
    // }

    // if (ballPosition < img.width / 3){
    //   ROS_INFO_THROTTLE(1, "Driving to left");
    //   drive_robot(0, 1); // turn left
    // } else if (ballPosition < img.width*2 / 3) {
    //   ROS_INFO_THROTTLE(1, "Driving forward");
    //   drive_robot(1, 0); // drive forward
    // } else {
    //   ROS_INFO_THROTTLE(1, "Driving right");
    //   drive_robot(0, -1); // turn right
    // }

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




// int main(int argc, char** argv)
// {
//     // Initialize the process_image node and create a handle to it
//     ros::init(argc, argv, "process_image");

//     // Define a client service capable of requesting services from command_robot
//     client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

//     // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
//     ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

//     // Handle ROS communication events
//     ros::spin();

//     return 0;
// }