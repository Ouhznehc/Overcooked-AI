#ifndef __ENUM_H__
#define __ENUM_H__

#include <bits/stdc++.h>

typedef struct Location {
    double x;
    double y;
    Location() {
        this->x = 0;
        this->y = 0;
    }
    Location(int x, int y) {
        this->x = (double)x;
        this->y = (double)y;
    }
    Location(double x, double y) {
        this->x = x;
        this->y = y;
    }
    bool operator == (const Location& b) {
        return this->x == b.x && this->y == b.y;
    }
}Location;

typedef struct Ingredient {
    Location location;
    int price; // 坐标以及花费
    std::string name;// 原料名称
}Ingredient;

typedef struct Recipe {
    int time; // 加工耗时
    std::string name_before, name_after; // 加工前后名称
    std::string kind; // 加工容器
}Recipe;

typedef struct Order {
    int valid_frame; // 消失帧
    int price; // 收益
    int frequency; // 出现频率
    std::vector<std::string> recipe; // 需要食材
}Order;

typedef struct Player {
    Location location;
    double x_velocity; // 速度
    double y_velocity;
    int live;// 复活倒计时时间， 0表示存活
    std::vector<std::string> entity; // 手持实体
}Player;

typedef struct Entity {
    Location location;
    std::vector<std::string> entity; // 实体上的的实体
    int current_frame, total_frame; // 容器加工进度
    int sum; // 特指脏盘子数量
}Entity;

#endif