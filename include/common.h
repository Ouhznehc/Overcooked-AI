#ifndef __COMMON_H__
#define __COMMON_H__

#include <string>
#include <vector>
#include <enum.h>

struct Ingredient {
  int x, y, price; // 坐标以及花费
  std::string name;// 原料名称
};

struct Recipe {
  int time; // 加工耗时
  std::string name_before, name_after; // 加工前后名称
  std::string kind; // 加工容器
};

struct Order {
  int valid_frame; // 消失帧
  int price; // 收益
  int frequency; // 出现频率
  std::vector<std::string> recipe; // 需要食材
};

struct Player {
  double x, y; // 坐标
  double x_velocity; // 速度
  double y_velocity;
  int live;// 复活倒计时时间， 0表示存活
  Container container; // 手持容器
  std::vector<std::string> entity; // 手持实体
};

struct Entity {
  double x, y; // 实体坐标
  Container container;// 实体上的容器
  std::vector<std::string> entity; // 实体上的的实体
  int current_frame, total_frame; // 容器加工进度
  int sum; // 特指脏盘子数量
};
#endif