#include "organiz/organize.h"
#include "main.h"


// Drivetrain constructor
ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing! 
    //BACK TO FRONT
    {-11, -16, -13},     // Left Chassis Ports (negative port will reverse it!)
    {12, 17, 14},  // Right Chassis Ports (negative port will reverse it!)

    18,      // IMU Port
    3.25,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)

    // External Gear Ratio (MUST BE DECIMAL) This is WHEEL GEAR / SENSOR GEAR
    // eg. if your drive is 84:36 where the 36t is sensored, your RATIO would be 84/36 which is 2.333
    // eg. if your drive is 36:60 where the 60t is sensored, your RATIO would be 36/60 which is 0.6
    1.66,

    -16,  // Left Rotation Port (negative port will reverse it!)
    17 // Right Rotation Port (negative port will reverse it!)
);  

using namespace okapi;

auto leftencoder = RotationSensor(8, true);
auto rightencoder = RotationSensor(5);
// Define the chassis configuration
/*auto drive = ChassisControllerBuilder()
    .withMotors({-1, -5, -18}, {10, 7, 20}) // Left and right motors
    .withDimensions(AbstractMotor::gearset::blue, {{4_in, 10_in}, imev5GreenTPR})
    .withOdometry({{2.75_in, 7_in}, quadEncoderTPR}, StateMode::CARTESIAN)
    .withSensors(leftencoder, rightencoder)
    .buildOdometry(); 
*/
pros::Motor intake(15);
ez::Piston backClamp(2); // true is down
ez::Piston doinker(8); // true is down
ez::Piston intakePiston(5); //true is down
pros::IMU inertial(18);
pros::Motor ladybrown(2);
pros::Rotation ladyBrownSensor(1);
pros::Optical color_checker(3);

pros::Controller master (CONTROLLER_MASTER);