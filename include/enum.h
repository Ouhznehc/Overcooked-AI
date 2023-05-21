#ifndef __ENUM_H__
#define __ENUM_H__

#include <bits/stdc++.h>

enum work_status {
    busy,
    leisure
};

enum player {
    null = -1,
    player0 = 0,
    player1 = 1,
};

enum action {
    move_towards,
    interact_with,
    lazy_around
};

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
    bool operator == (const Location b) {
        return this->x == b.x && this->y == b.y;
    }

    void operator = (const Location& b) {
        this->x = b.x;
        this->y = b.y;
    }
}location_t;

typedef struct Ingredient {
    Location location;
    int price; // 坐标以及花费
    std::string name;// 原料名称
}ingredient_t;

typedef struct Recipe {
    int time; // 加工耗时
    std::string name_before, name_after; // 加工前后名称
    std::string kind; // 加工容器
}recipe_t;

typedef struct Order {
    int valid_frame; // 消失帧
    int price; // 收益
    int frequency; // 出现频率
    std::vector<std::string> recipe; // 需要食材
}order_t;

typedef struct Player {
    Location src;
    Location dst;
    std::string move_direction;
    int status;
    double x_velocity; // 速度
    double y_velocity;
    int live;// 复活倒计时时间， 0表示存活
    std::vector<std::string> item; // 手持实体
}player_t;

typedef struct Entity {
    Location location;
    std::vector<std::string> item; // 实体上的的实体
    int current_frame, total_frame; // 容器加工进度
    int sum; // 特指脏盘子数量
}entity_t;

typedef struct Task {
    int action;
    std::string object;
    std::vector<std::string> item;
}task_t;

typedef std::vector<task_t> packed_task_t;

typedef struct Work {
    int player;
    packed_task_t current_task;
    int task_cnt;
}wort_t;

#endif