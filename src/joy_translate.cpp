#include "joy_translate/joy_translate.hpp"

JoyTranslate::JoyTranslate()
: Node("joy_translate_node")
{
    joy_twist_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
    mode_pub_ = this->create_publisher<std_msgs::msg::String>("mode", 10);
    joy_sub_ = this->create_subscription<sensor_msgs::msg::Joy>(
        "joy", 10, std::bind(&JoyTranslate::joy_output_cb, this, std::placeholders::_1));
}

void JoyTranslate::joy_output_cb(const sensor_msgs::msg::Joy::SharedPtr msg)
{
    get_data(msg);
    send_data.linear.x = -1*joy_left_x*127;
    send_data.linear.y = joy_left_y*127;
    send_data.angular.z = -1*joy_right_x*127;
    joy_pub_->publish(send_data);
    mode_pub_->publish(send_data);
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<JoyTranslate>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
