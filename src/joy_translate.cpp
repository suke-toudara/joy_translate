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
    get_data(msg);
    send_data.linear.x = -1*joy_left_x*127;
    send_data.linear.y = joy_left_y*127;
    send_data.angular.z = -1*joy_right_x*127;
    publisher_->publish(send_data);
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<JoyTranslate>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
