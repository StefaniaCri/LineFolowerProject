# FolowLinerProject

# Collaborators:
<ul>
<li>Bucșă (also the team name)</li>
<li> Ana Oprea (https://github.com/ana-oprea/Line-Follower) </li>
</ul>

# Technical task
  Create a self-calibrating line follower that can follow a black line path. 
 
 # Desription of the project
Met Bucșă, our line follower. What code Bucșă follows:  
  a) a calibration system that move 6 of QTR-8A sensors left-right throuh the black line. Most important to move all the sensor to black/white states. The calibration is made with calibrate function from QTR library.<br>
  b) a path-following algorithm that can keep the robot on the black line. this is a proportional-derivative (PD) controller, using a combination of proportional  and derivative control. The proportional gain (kp) controls the robot's ability to steer towards the line, the derivative gain (kd) helps to stabilize the robot's movement. The kp and kd values of 15 and 30 respectively, indicate that the robot is highly responsive to line detection and able to minimize the error as much as possible. In this specifici scenario, we use an empirical approach, choosing the kp and kd so the line follower can follow a straight line and detect the curves in the course.
  
 # The line follower in action
The objective of the project was to assemble the kit we recieve, and to program it to follow a route in less then 20s. In the link bellow you can see Bucșă following the course and self-calibrating.
The time Bucșă got was 00:19:351 (best one out of three)

[Watch the line follower:racing_car:](https://youtu.be/azvnlHyIW_s)

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




  

