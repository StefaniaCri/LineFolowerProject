# FolowLinerProject

# Technical task
  Create a self-calibrating line follower that can follow a black line path.
  
# Components 
  1. Arduino Uno
  2. Zip-ties
  3. A LiPo battery
  4. Wheels (2)
  5. Wires for the line sensor
  6. QTR-8A reflectance sensor, along with screws
  7. Ball caster
  8. Extra wires 
  9. Chassis
  10. Breadboard 
  11. L293D motor driver
  12. DC motors (2)
  
# Setup
<img src="https://user-images.githubusercontent.com/79380914/213724040-7274edad-ea16-4fb0-8690-d04dfb732cd5.jpg"  width="400" height="550" /><span>   </span><img src="https://user-images.githubusercontent.com/79380914/213724034-58e2e5cd-a0d4-44fb-81db-62b7e7b51a09.jpg"  width="550" height="400" />

# Video
[Watch the line follower:racing_car:](https://youtu.be/azvnlHyIW_s)

# Desription of the project

Met Bucșă, our line follower. What code Bucșă follows:  
  a) a calibration system that move the QTR-8A sensors left-right throuh the black line. Most important to move all the sensor to black/white states. The calibration is made with calibrate function from QTR library.<br>
  b) a path-following algorithm that can keep the robot on the black line. this is a proportional-(integral)-derivative (P(I)D) controller, using a combination of proportional, integral, and derivative control. The proportional gain (kp) controls the robot's ability to steer towards the line, the derivative gain (kd) helps to stabilize the robot's movement and reduce overshoots, and the integral gain (ki) helps to eliminate any steady-state errors in the system. In this specific case, the integral gain is set to zero, meaning that the robot will not make any adjustments based on the accumulated error over time, which could be useful in certain scenarios. The kp and kd values of 15 and 30 respectively, indicate that the robot is highly responsive to line detection and able to minimize the error as much as possible.