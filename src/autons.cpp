#include "main.h"

/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;  
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

///
// Constants
///
void default_constants() {
  chassis.pid_heading_constants_set(4, 0, 20);
  chassis.pid_drive_constants_forward_set(2, 0, 35);
  chassis.pid_drive_constants_backward_set(2.5, 0.007, 20, 1);
  chassis.pid_turn_constants_set(3.4, 0.002, 16, 1);
  chassis.pid_swing_constants_set(5, 0, 30);

  chassis.pid_turn_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_swing_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);

  chassis.slew_drive_constants_set(7_in, 80);
  chassis.slew_turn_constants_set(5_deg, 50);
  chassis.slew_swing_constants_set(5_deg, 50);

  
}

void do_nothing() {
  backClamp.set(false);
}
//first auton sketfch out

void blue_ring_rush() {
  chassis.drive_angle_set(90);
  // doinker.set(true);
  backClamp.set(false);

  chassis.pid_drive_set(-10, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0, SWING_SPEED);
  chassis.pid_wait();

  // doinker.set(false);
  intake.move(120);
  pros::delay(1000);
  intake.brake();

  chassis.pid_drive_set(10, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(18, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-135, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-15, DRIVE_SPEED);
  chassis.pid_wait();

  backClamp.set(true);
  pros::delay(200);

  chassis.pid_turn_set(-260, TURN_SPEED);
  chassis.pid_wait();

  intake.move(100);
  chassis.pid_drive_set(28, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-362, TURN_SPEED);
  chassis.pid_wait();

  intake.move(120);
  chassis.pid_drive_set(24, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(0,0);
  pros::delay(500);

  chassis.pid_drive_set(-5, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-431, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(40, DRIVE_SPEED);
  chassis.pid_wait();
  intake.brake();



  // chassis.pid_drive_set(-36_in, 100, true);
  // chassis.pid_wait();

  // backClamp.set(true);

  // chassis.pid_drive_set(0,0);
  // pros::delay(800);    

  // chassis.pid_swing_set(ez::LEFT_SWING, 90, TURN_SPEED-10, true);
  // chassis.pid_wait();

  // intake.move(127);
  
  // chassis.pid_drive_set(32_in, DRIVE_SPEED);
  // chassis.pid_wait();

  // chassis.pid_drive_set(0,0);
  // pros::delay(2000);

  // chassis.pid_turn_set(-90, TURN_SPEED-10, true);
  // chassis.pid_wait();
  
  // chassis.pid_drive_set(47, DRIVE_SPEED);
  // chassis.pid_wait();
}

//second auton sketfch out

void blue_goal_rush() {
  chassis.drive_angle_set(-30);
  doinker.set(true);

  chassis.pid_drive_set(190, DRIVE_SPEED, true);
  chassis.pid_wait();
  
  chassis.pid_turn_set(-10, TURN_SPEED);
  chassis.pid_wait();
  doinker.set(false);

  chassis.pid_drive_set(-10, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-180, TURN_SPEED);
  doinker.set(true);
  chassis.pid_wait();

  chassis.pid_turn_set(-90, TURN_SPEED);
  doinker.set(false);
  chassis.pid_wait();

  chassis.pid_drive_set(-10, DRIVE_SPEED);
  chassis.pid_wait();

  backClamp.set(true);
  intake.move(100);

  chassis.pid_drive_set(0,0);
  chassis.pid_wait();

  pros::delay(2000);
  intake.brake();
  // chassis.drive_angle_set(-90);
  // // doinker.set(true);
  // backClamp.set(false);

  // chassis.pid_drive_set(-10, DRIVE_SPEED);
  // chassis.pid_wait();

  // chassis.pid_swing_set(ez::RIGHT_SWING, 0, SWING_SPEED);
  // chassis.pid_wait();

  // // doinker.set(false);
  // intake.move(120);
  // pros::delay(1000);
  // intake.brake();

  // chassis.pid_drive_set(10, DRIVE_SPEED);
  // chassis.pid_wait();

  // chassis.pid_swing_set(ez::RIGHT_SWING, -45, SWING_SPEED);
  // chassis.pid_wait();

  // chassis.pid_drive_set(18, DRIVE_SPEED);
  // chassis.pid_wait();

  // chassis.pid_turn_set(135, TURN_SPEED);
  // chassis.pid_wait();

  // chassis.pid_drive_set(-15, DRIVE_SPEED);
  // chassis.pid_wait();

  // backClamp.set(true);
  // pros::delay(200);

  // chassis.pid_turn_set(260, TURN_SPEED);
  // chassis.pid_wait();

  // intake.move(100);
  // chassis.pid_drive_set(28, DRIVE_SPEED);
  // chassis.pid_wait();

  // chassis.pid_turn_set(95, TURN_SPEED);
  // chassis.pid_wait();

  // chassis.pid_drive_set(60, DRIVE_SPEED);
  // chassis.pid_wait();
  // intake.brake();

  // chassis.pid_drive_set(-20.5, DRIVE_SPEED);
  // chassis.pid_wait();

  // backClamp.set(true);

  // chassis.pid_drive_set(0,0);
  // pros::delay(800);    

  // chassis.pid_swing_set(ez::RIGHT_SWING, -100, TURN_SPEED-10, true);
  // chassis.pid_wait();

  // intake.move(127);
  
  // chassis.pid_drive_set(12_in, 100);
  // chassis.pid_wait();

  // pros::delay(2000);

  // chassis.pid_drive_set(-31_in, DRIVE_SPEED);
  // chassis.pid_wait();

  // chassis.pid_drive_set(0,0);
  // pros::delay(2000);

  // //doinker.set(true);

  // chassis.pid_turn_set(90_deg, 70);
  // chassis.pid_wait();

  // chassis.pid_drive_set(10, DRIVE_SPEED);
  // chassis.pid_wait();

  // intake.brake();
}

void red_ring_rush() {
    chassis.drive_angle_set(-90);
  // doinker.set(true);
  backClamp.set(false);

  chassis.pid_drive_set(-10, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.pid_wait();

  // doinker.set(false);
  intake.move(120);
  pros::delay(1000);
  intake.brake();

  chassis.pid_drive_set(10, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45, SWING_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(18, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(135, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-15, DRIVE_SPEED);
  chassis.pid_wait();

  backClamp.set(true);
  pros::delay(200);

  chassis.pid_turn_set(260, TURN_SPEED);
  chassis.pid_wait();

  intake.move(100);
  chassis.pid_drive_set(28, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(362, TURN_SPEED);
  chassis.pid_wait();

  intake.move(120);
  chassis.pid_drive_set(24, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(0,0);
  pros::delay(500);

  chassis.pid_drive_set(-5, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(431, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(40, DRIVE_SPEED);
  chassis.pid_wait();
  intake.brake();
}
void red_goal_rush() {
    chassis.drive_angle_set(30);
  doinker.set(true);

  chassis.pid_drive_set(190, DRIVE_SPEED, true);
  chassis.pid_wait();
  
  chassis.pid_turn_set(10, TURN_SPEED);
  chassis.pid_wait();
  doinker.set(false);

  chassis.pid_drive_set(-10, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(180, TURN_SPEED);
  doinker.set(true);
  chassis.pid_wait();

  chassis.pid_turn_set(90, TURN_SPEED);
  doinker.set(false);
  chassis.pid_wait();

  chassis.pid_drive_set(-10, DRIVE_SPEED);
  chassis.pid_wait();

  backClamp.set(true);
  intake.move(100);

  chassis.pid_drive_set(0,0);
  chassis.pid_wait();

  pros::delay(2000);
  intake.brake();
}


void skills_code() {
  chassis.drive_angle_set(0);
  backClamp.set(false);
  
  intake.move(100);
  pros::delay(1000);

  chassis.pid_drive_set(10, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(90, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-10, DRIVE_SPEED);
  chassis.pid_wait();

  
  
  // chassis.pid_drive_set(-5_in, DRIVE_SPEED);
  // chassis.pid_wait();

  // backClamp.set(true);

  // chassis.pid_turn_set(-90_deg, TURN_SPEED);
  // chassis.pid_wait();

  // intake.move(127);

  // chassis.pid_drive_set(10_in, DRIVE_SPEED);
  // chassis.pid_wait();
}
///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED);
  chassis.pid_wait();

}

///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 30
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(30);  // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 30 speed
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 30
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(30);  // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 30 speed
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees.
// If interfered, robot will drive forward and then attempt to drive backwards.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

// . . .
// Make your own autonomous functions here!
// . . .