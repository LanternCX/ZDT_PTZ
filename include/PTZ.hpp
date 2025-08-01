#pragma once

#include <Arduino.h>
#include "Stepper.hpp"

class PTZ {
    public:
        /**
         * @brief 云台构造函数
         * @param _serial 云台串口
         * @param _addr_x 水平轴电机地址
         * @param _addr_y 垂直轴电机地址
         */
        PTZ(HardwareSerial& _serial, int _addr_x, int _addr_y);
        
        /**
         * @brief 云台初始化
         */
        virtual void init();

        /**
         * @brief 设置水平轴电机转速
         * @param speed 转速（单位 rpm，正为 CCW，负为 CW，范围 ±5000）
         * @param acc 加速度（0~255），0 表示直接启动
         */
        virtual void set_x_speed(int16_t speed, uint8_t acc = 0);

        /**
         * @brief 设置垂直轴电机转速
         * @param speed 转速（单位 rpm，正为 CCW，负为 CW，范围 ±5000）
         * @param acc 加速度（0~255），0 表示直接启动，默认 0
         */
        virtual void set_y_speed(int16_t speed, uint8_t acc = 0);

        /**
         * @brief 设置水平轴角度
         * @param angle 目标角度
         * @param speed 到位速度（单位 rpm，正为 CCW，负为 CW，范围 ±5000）
         * @param acc 加速度（0~255），0 表示直接启动，默认 0
         */
        virtual void set_x_angle(float angle, uint16_t speed = 30, uint8_t acc = 0);

        /**
         * @brief 设置垂直轴角度
         * @param angle 目标角度
         * @param speed 到位速度（单位 rpm，正为 CCW，负为 CW，范围 ±5000）
         * @param acc 加速度（0~255），0 表示直接启动，默认 0
         */
        virtual void set_y_angle(float angle, uint16_t speed = 30, uint8_t acc = 0);

        /**
         * @brief 增加水平轴角度
         * @param angle 角度增加量（角度制，单位度，正为 CCW，负为 CW）
         * @param speed 到位速度（单位 rpm，正值，不控制方向）
         * @param acc 加速度（0~255），0 表示直接启动，默认 0
         */
        virtual void add_x_angle(float angle, uint16_t speed = 30, uint8_t acc = 0);

        /**
         * @brief 增加垂直轴角度
         * @param angle 角度增加量（角度制，单位度，正为 CCW，负为 CW）
         * @param speed 到位速度（单位 rpm，正值，不控制方向）
         * @param acc 加速度（0~255），0 表示直接启动，默认 0
         */
        virtual void add_y_angle(float angle, uint16_t speed = 30, uint8_t acc = 0);


        /**
         * @brief 移动到垂直距离为 dis 的平面上坐标为 x, y 的点
         * @param dis 距离平面的距离
         * @param x 横坐标
         * @param y 纵坐标
         */
        virtual void move_to(float dis, float x, float y, uint16_t speed = 30, uint8_t acc = 0);

        /**
         * @brief 获取水平轴角度
         */
        virtual float get_x_angle();

        /**
         * @brief 获取垂直轴角度
         */
        virtual float get_y_angle();

        /**
         * @brief 云台状态清零
         */
        virtual void reset();

        /**
         * @brief 同步所有电机
         */
        virtual void sync_all();
    private:
        HardwareSerial& serial;
        Stepper stepper_x;
        Stepper stepper_y;

        /**
         * @brief 转换角度到步数
         * @param angle 角度
         */
        static int32_t degree_to_step(float angle);

        float last_x_angle = 0;  // 记录上一次水平角度
        float last_y_angle = 0;  // 记录上一次垂直角度
        
        // 速度平滑滤波器 (高斯加权)
        virtual float smooth_speed(float current, float last);
};