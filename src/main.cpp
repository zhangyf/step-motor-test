#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <wiringPi.h>

// 定义GPIO引脚
const int MOTOR_PIN_1 = 0;
const int MOTOR_PIN_2 = 1;
const int MOTOR_PIN_3 = 2;
const int MOTOR_PIN_4 = 3;

// 步进电机每一步的时间（微秒）
const int STEP_DELAY_MICROSECONDS = 1000; 


// 步进模式: 2相8拍
const std::vector<std::vector<int>> step_sequence = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
};

// 设置GPIO引脚状态
void set_motor_pins(const std::vector<int>& pins) {
    for (size_t i = 0; i < pins.size(); i++) {
        digitalWrite(pins[i], pins[i] ? HIGH : LOW);
    }
}

int main() {
    if (wiringPiSetup() == -1) {
        std::cerr << "WiringPi setup failed" << std::endl;
        return 1;
    }

    pinMode(MOTOR_PIN_1, OUTPUT);
    pinMode(MOTOR_PIN_2, OUTPUT);
    pinMode(MOTOR_PIN_3, OUTPUT);
    pinMode(MOTOR_PIN_4, OUTPUT);

    int total_steps = 4096;
    double steps_per_second = total_steps / 60.0;
    double delay_bwteen_steps = 1000000 / steps_per_second;

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < total_steps; i++) {
        set_motor_pins(step_sequence[i % 8]);

        // 计算驱动脉冲实际花了多长时间
        auto current_time = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(current_time - start_time);

        // 计算还需要睡眠多久才能执行下次驱动脉冲
        int sleep_time = static_cast<int>(delay_bwteen_steps - elapsed_time);
        if (sleep_time > 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(sleep_time));
        }

        start_time = std::chrono::high_resolution_clock::now();
    }

    return 0;
}