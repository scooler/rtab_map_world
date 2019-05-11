# WhereAmI Robot

Based on previous [ChasingRobot](https://github.com/scooler/chasing_robot)

This one uses localization.

## Build

To build just run
```
catkin_make
```

In the main directory. That should create devel directory. So then `source devel/setup.bash` (or `.zsh` if that's your fancy ;) ).


## Run

In order to run:
1) start the world - `roslaunch my_robot world.launch`
2) start the ball-chasing fun part `roslaunch ball_chaser ball_chaser.launch`
3) in gazebo switch tool to moving/gragging (2nd one on top toolbar - cross with arrows)
4) drag the ball in front of the robot's camera (the black cylinder)

The robot spawns now facing an angle (I wanted to test the lidar), so you have to keep dragging the ball, as he'll catch it pretty soon otherwise :)


Have fun !