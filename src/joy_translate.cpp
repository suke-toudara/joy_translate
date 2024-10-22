#include "joy_translate.hpp"

JoyTranslate::JoyTranslate()
: Node("joy_translate_node")
{
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
    subscription_ = this->create_subscription<sensor_msgs::msg::Joy>(
        "joy", 10, std::bind(&JoyTranslate::listener_callback, this, std::placeholders::_1));
}

void JoyTranslate::listener_callback(const sensor_msgs::msg::Joy::SharedPtr msg)
{
    geometry_msgs::msg::Twist vel;
    
    // Scale the joystick values to adjust speed
    vel.linear.x = 2.0 * msg->axes[1];  // Forward/backward tilt on joystick
    vel.angular.z = 2.0 * msg->axes[3]; // Left/right tilt on joystick
    
    publisher_->publish(vel);
    
    // Log the linear velocity for debugging
    RCLCPP_INFO(this->get_logger(), "Velocity: Linear=%.2f, Angular=%.2f", msg->axes[1], msg->axes[3]);
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<JoyTranslate>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
