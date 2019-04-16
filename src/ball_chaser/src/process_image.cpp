#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

class ProcessImage{

public:
  ProcessImage(){
    // Define a client service capable of requesting services from safe_move
    _client = _n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    ros::Subscriber sub = _n.subscribe("/camera/rgb/image_raw111", 10, &ProcessImage::process_image_callback, this);
    ROS_INFO("Ready to process_image4");
  }

void process_image_callback(const sensor_msgs::Image img)
{

  ROS_INFO("Callback called");
  uint32_t ballPosition = findBall(img);
  // ROS_INFO_THROTTLE(1, "Found position %zu", ballPosition);
  if (ballPosition <= 0) {
    return; // don't do anything
  }

  if (ballPosition < img.width / 3){
    ROS_INFO_THROTTLE(1, "Driving to left");
    drive_robot(0, 1); // turn left
  } else if (ballPosition < img.width*2 / 3) {
    ROS_INFO_THROTTLE(1, "Driving forward");
    drive_robot(1, 0); // drive forward
  } else {
    ROS_INFO_THROTTLE(1, "Driving right");
    drive_robot(0, -1); // turn right
  }

    // // Get joints current position
    // std::vector<double> joints_current_position = js.position;

    // // Define a tolerance threshold to compare double values
    // double tolerance = 0.0005;

    // // Check if the arm is moving by comparing its current joints position to its latest
    // if (fabs(joints_current_position[0] - joints_last_position[0]) < tolerance && fabs(joints_current_position[1] - joints_last_position[1]) < tolerance)
    //     moving_state = false;
    // else {
    //     moving_state = true;
    //     joints_last_position = joints_current_position;
    // }
}

// // This callback function continuously executes and reads the image data
// void look_away_callback(const sensor_msgs::Image img)
// {

//     bool uniform_image = true;

//     // Loop through each pixel in the image and check if its equal to the first one
    // for (int i = 0; i < img.height * img.step; i++) {
    //     if (img.data[i] - img.data[0] != 0) {
    //         uniform_image = false;
    //         break;
    //     }
    // }

//     // If the image is uniform and the arm is not moving, move the arm to the center
//     if (uniform_image == true && moving_state == false)
//         move_arm_center();
// }


private:

// Define global vector of joints last position, moving state of the arm, and the client that can request services
  // std::vector<double> joints_last_position{ 0, 0 };
  // bool moving_state = false;
  ros::ServiceClient _client;
  ros::NodeHandle _n;

  // This function calls the safe_move service to safely move the arm to the center position
  // void move_arm_center()
  // {

  //     // Request centered joint angles [1.57, 1.57]
  //     simple_arm::GoToPosition srv;
  //     srv.request.joint_1 = 1.57;
  //     srv.request.joint_2 = 1.57;

  //     // Call the safe_move service and pass the requested joint angles

  void drive_robot(float lin_x, float ang_z){
      ROS_INFO("Driving Bot lin_x: %10.4f , ang_z: %10.4f", lin_x, ang_z);
      // TODO: Request a service and pass the velocities to it to drive the robot

      ball_chaser::DriveToTarget srv;
      srv.request.linear_x = lin_x;
      srv.request.angular_z = ang_z;

      if (!_client.call(srv)) {
          ROS_ERROR("Failed to call service to drive_robot");
      };
  }


  uint32_t findBall(const sensor_msgs::Image img) {

    int white_pixel = 255;
    for (int i = 0; i < img.height * img.step; i++) {
        if (img.data[i] == white_pixel) {
          return i;// % img.step;
        }
    }
    return -1;
  }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "process_image");

    ProcessImage processImage;

    // Handle ROS communication events
    ros::spin();

    return 0;
}

