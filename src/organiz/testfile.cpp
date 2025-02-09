#include <cmath>
#include "main.h"


class PIDController {
private:
    double kp;
    double ki;
    double kd;
    double max_output;
    double min_output;
    double setpoint;
    double error_sum;
    double prev_error;

public:
    PIDController(double kp, double ki, double kd, double max_output, double min_output) 
        : kp(kp), ki(ki), kd(kd), max_output(max_output), min_output(min_output) {
        setpoint = 0;
        error_sum = 0;
        prev_error = 0;
    }
    
    void setSetpoint(double target) {
        setpoint = target;
    }
    
    double compute(double input) {
        double error = setpoint - input;
        error_sum += error;
        
        double p_term = kp * error;
        double i_term = ki * error_sum;
        double d_term = kd * (error - prev_error);
        
        double output = p_term + i_term + d_term;
        
        // Limit output within specified bounds
        output = std::max(min_output, std::min(max_output, output));
        
        prev_error = error;
        
        return output;
    }
    
    void reset() {
        error_sum = 0;
        prev_error = 0;
    }
};

class Odometry {
private:
    pros::Imu imu_sensor;
    pros::Rotation left_sensor;
    pros::Rotation right_sensor;
    double wheel_radius;
    double wheelbase_width;
    
    double prev_left_pos;
    double prev_right_pos;
    double prev_heading;
    
    double start_x_position;
    double start_y_position;
    double start_heading;

public:
    Odometry(pros::Imu imu, pros::Rotation left_sensor, pros::Rotation right_sensor, double wheel_radius, double wheelbase_width) 
        : imu_sensor(imu), left_sensor(left_sensor), right_sensor(right_sensor), wheel_radius(wheel_radius), wheelbase_width(wheelbase_width) {
        prev_left_pos = left_sensor.get_position();
        prev_right_pos = right_sensor.get_position();
        prev_heading = imu_sensor.get_rotation();
        
        start_x_position = 0.0;
        start_y_position = 0.0;
        start_heading = prev_heading;
    }
    
    void update() {
        double current_left_pos = left_sensor.get_position();
        double current_right_pos = right_sensor.get_position();
        double delta_left_pos = current_left_pos - prev_left_pos;
        double delta_right_pos = current_right_pos - prev_right_pos;
        
        double delta_heading = imu_sensor.get_rotation() - prev_heading;
        
        double delta_distance = (delta_left_pos + delta_right_pos) / 2.0;
        
        double delta_x = delta_distance * cos(prev_heading * M_PI / 180.0);
        double delta_y = delta_distance * sin(prev_heading * M_PI / 180.0);
        
        start_x_position += delta_x;
        start_y_position += delta_y;
        
        prev_left_pos = current_left_pos;
        prev_right_pos = current_right_pos;
        prev_heading = imu_sensor.get_rotation();
    }
    
    double getX() {
        return start_x_position;
    }
    
    double getY() {
        return start_y_position;
    }
    
    double getHeading() {
        double current_heading = imu_sensor.get_rotation();
        double normalized_heading = std::remainder(current_heading, 360.0); // Ensure heading is within [-360, 360] degrees
        if (normalized_heading < 0) {
            normalized_heading += 360.0; // Convert negative angles to equivalent positive angles
        }
        return normalized_heading;
    }

    void setPos(double x, double y, double angle_degrees) {
        start_x_position = x;
        start_y_position = y;
        start_heading = std::remainder(angle_degrees, 360.0); // Ensure angle is within [-360, 360] degrees
        if (start_heading < 0) {
            start_heading += 360.0; // Convert negative angles to equivalent positive angles
        }
    }
};

struct Point {
    double x;
    double y;
    double angle; // Angle associated with the point

    // Constructor with angle in degrees
    Point(double x, double y, double angle_degrees) : x(x), y(y), angle(angle_degrees * M_PI / 180.0) {}
};

class Drivetrain {
private:
    Odometry odometry;
    PIDController pid_controller_left;
    PIDController pid_controller_right;
    
    std::vector<Point> path; // List of points to follow
    double lookahead_distance; // Distance to look ahead on the path
    double max_velocity; // Maximum velocity of the robot
    double max_acceleration; // Maximum acceleration of the robot
    
    double current_left_velocity;
    double current_right_velocity;
    double wheelbase_width;

public:
    Drivetrain(Odometry odometry, PIDController pid_left, PIDController pid_right, double lookahead_dist, double max_vel, double max_acc, double width) 
        : odometry(odometry), pid_controller_left(pid_left), pid_controller_right(pid_right), lookahead_distance(lookahead_dist), max_velocity(max_vel), max_acceleration(max_acc), current_left_velocity(0), current_right_velocity(0), wheelbase_width(width) {}
    
    void setPath(std::vector<Point> waypoints) {
        path = waypoints;
    }

    double adjustVelocity(double current_velocity, double target_velocity, double distance_remaining) {
        double acceleration_required = (target_velocity * target_velocity - current_velocity * current_velocity) / (2 * distance_remaining);
        double acceleration_clamped = std::min(std::abs(acceleration_required), max_acceleration);
        if (target_velocity > current_velocity) {
            return std::min(current_velocity + acceleration_clamped, target_velocity);
        } else {
            return std::max(current_velocity - acceleration_clamped, target_velocity);
        }
    }
    //updated followpath
    void followPath(std::vector<Point> path) {
    Point current_pose = {odometry.getX(), odometry.getY(), odometry.getHeading()};
    
    // Find the index of the closest point on the path
    int closest_index = 0;
    double closest_distance = std::numeric_limits<double>::max();
    for (int i = 0; i < path.size(); ++i) {
        double distance = std::hypot(path[i].x - current_pose.x, path[i].y - current_pose.y);
        if (distance < closest_distance) {
            closest_distance = distance;
            closest_index = i;
        }
    }
    
    // Find the lookahead point
    int lookahead_index = closest_index;
    double lookahead_distance_squared = lookahead_distance * lookahead_distance;
    while (lookahead_index < path.size() - 1) {
        double dx = path[lookahead_index + 1].x - current_pose.x;
        double dy = path[lookahead_index + 1].y - current_pose.y;
        double distance_squared = dx * dx + dy * dy;
        if (distance_squared > lookahead_distance_squared) {
            break;
        }
        lookahead_index++;
    }
    
    // Calculate the desired heading angle
    double desired_heading = std::atan2(path[lookahead_index].y - current_pose.y, path[lookahead_index].x - current_pose.x);
    
    // Calculate the curvature
    double curvature = 2 * std::sin(desired_heading - odometry.getHeading()) / lookahead_distance;
    
    // Calculate the left and right wheel velocities using the curvature
    double left_velocity = max_velocity * (2 + curvature * wheelbase_width / 2.0);
    double right_velocity = max_velocity * (2 - curvature * wheelbase_width / 2.0);
    
    // Use PID controllers to adjust velocities if necessary
    double left_output = pid_controller_left.compute(left_velocity);
    double right_output = pid_controller_right.compute(right_velocity);
    
    // Set motor speeds accordingly
    // leftMotor.setVelocity(left_output);
    // rightMotor.setVelocity(right_output);
}

    
    void turnInPlace(double desired_heading_degrees, double full_speed_angle_degrees) {
        double current_heading = odometry.getHeading();
        
        // Convert angles to radians
        double desired_heading = desired_heading_degrees;
        double full_speed_angle = full_speed_angle_degrees;
        
        // Normalize desired heading to be in the range [-360, 360] degrees
        desired_heading = std::remainder(desired_heading, 360.0);
        
        // Calculate error in heading
        double error = desired_heading - current_heading;
        
        // Ensure error is within the range [-180, 180] degrees
        if (error > 180.0) {
            error -= 360.0;
        } else if (error < -180.0) {
            error += 360.0;
        }
        
        // Use PID controllers to calculate desired velocities
        double desired_left_velocity = pid_controller_left.compute(error);
        double desired_right_velocity = pid_controller_right.compute(-error);
        
        // Calculate remaining distance to target heading
        double angle_remaining = std::abs(error);
        
        // Calculate distance remaining to full speed point
        double distance_to_full_speed = angle_remaining - full_speed_angle;
        distance_to_full_speed = std::max(distance_to_full_speed, 0.0); // Ensure distance is non-negative
        
        // Slew rate control for acceleration
        current_left_velocity = adjustVelocity(current_left_velocity, desired_left_velocity, distance_to_full_speed);
        current_right_velocity = adjustVelocity(current_right_velocity, desired_right_velocity, distance_to_full_speed);
        
        // Set motor speeds accordingly

    }
};

