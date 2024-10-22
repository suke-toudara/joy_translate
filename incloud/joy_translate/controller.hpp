#ifndef JOY_BASE_HPP
#define JOY_BASE_HPP

#include <sensor_msgs/Joy.h>
#include <string>

class controller:
{
    public:
        //方向キー(左十字キー)
        bool  up_btn;
        bool  down_btn;
        bool  right_btn;
        bool  left_btn;

        //bottan
        bool cross_btn;
        bool circle_btn;  
        bool triangle_btn;
        bool square_btn; 

        //etc botttan
        bool share_btn;
        bool options_btn;
        bool ps_btn;

        //touch pad
        bool touch_pad;
        float d_pad_x;
        float d_pad_y;
        
        //joystic
        float joy_left_x;
        float joy_left_y; 
        float joy_right_x;
        float joy_right_y;
        bool R3_btn;
        bool L3_btn;

        //側面ボタン
        bool L1_btn;
        bool R1_btn;
        bool L2_btn;
        bool R2_btn;
    

        void update_key_value(const sensor_msgs::Joy &msg)
        {
            //方向キー(左十字キー)
            cross_btn       = msg.buttons[0];
            circle_btn      = msg.buttons[1];
            triangle_btn    = msg.buttons[2];
            square_btn      = msg.buttons[3];

            //側面ボタン
            L1_btn          = msg.buttons[4];
            R1_btn          = msg.buttons[5];
            L2_btn          = msg.buttons[6];
            R2_btn          = msg.buttons[7];

            //真ん中のボタンSHAREボタン
            share_btn      = msg.buttons[8];
            options_btn     = msg.buttons[9];
            PS_btn          = msg.buttons[10];

            //joystic
            joy_left_x      = msg.axes[0];
            joy_left_y      = msg.axes[1];

            joy_right_x     = msg.axes[3];
            joy_right_y     = msg.axes[4];

            L2              = msg.axes[2]; 
            R2              = msg.axes[5];

            d_pad_x         = msg.axes[6];
            d_pad_y         = msg.axes[7];

            d_pad2btn();
        }
        
        void btn2d_pad()
        {
            //この式変えてもいいかも(例えば制御量　小のときは十字キーとか)
            d_pad_x     = -1*float(right_btn)  + float(left_btn);
            d_pad_y     = -1*float(down_btn)   + float(up_btn);  
        }

        void init_data()
        {
            //方向キー(左十字キー)
            up_btn = 0;
            down_btn = 0;
            right_btn = 0;
            left_btn = 0;

            //bottan
            cross_btn = 0;
            circle_btn = 0;
            triangle_btn = 0;
            square_btn = 0;

            //etc botttan
            share_btn = 0;
            options_btn = 0;
            ps_btn = 0;

            //touch pad
            touch_pad = 0;
            d_pad_x = 0;
            d_pad_y = 0;
            
            //joystic
            joy_left_x = 0;
            joy_left_y = 0;
            joy_right_x = 0;
            joy_right_y = 0;
            R3_btn = 0;
            L3_btn = 0;

            //側面ボタン
            L1_btn = 0;
            R1_btn = 0;
            L2_btn = 0;
            R2_btn = 0;
        }
        
        void print_controller_state() const {
            std::cout << "Left Stick: (" << left_stick_x << ", " << left_stick_y << ")\n";
            std::cout << "Right Stick: (" << right_stick_x << ", " << right_stick_y << ")\n";
            std::cout << "L2 Trigger: " << l2_trigger << ", R2 Trigger: " << r2_trigger << "\n";
            std::cout << "DPad: (" << dpad_x << ", " << dpad_y << ")\n";
            std::cout << "Cross: " << cross_button << ", Circle: " << circle_button << ", Square: " << square_button << ", Triangle: " << triangle_button << "\n";
            std::cout << "L1: " << l1_button << ", R1: " << r1_button << ", L3: " << l3_button << ", R3: " << r3_button << "\n";
            std::cout << "PS Button: " << ps_button << ", Touchpad Button: " << touchpad_button << "\n";
        }
        
        void apply_deadzone(float &value, float deadzone = 0.1) {
            if (std::abs(value) < deadzone) {
                value = 0.0;
            }
        }

        void apply_deadzones() {
            apply_deadzone(joy_left_x);
            apply_deadzone(joy_left_y);
            apply_deadzone(joy_right_x);
            apply_deadzone(joy_right_y);
        }
};
#endif
