#ifndef JOY_TRANSLATE_HPP_
#define JOY_TRANSLATE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "std_msgs/msg/int32.hpp"
#include "controller.hpp"

class JoyTranslate : public rclcpp::Node
{
public:
    JoyTranslate(); 

private:
    void joy_output_cb(const sensor_msgs::msg::Joy & msg);
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr joy_twist_pub_;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr mode_pub_;
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub_;
    Controller controller;
    int mode;
    
    float max_linear_velocity_ = 6;
    float min_linear_velocity_ = -6;
    float max_angular_velocity_= 1;
    float min_angular_velocity_ = -1;
};

#endif  // JOY_TRANSLATE_HPP_
