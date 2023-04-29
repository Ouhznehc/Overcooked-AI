#include <action.h>
#include <common.h>
#include <bits/stdc++.h>

#define LIMIT_RANGE 0.001

double manhattan_distance(location src, location dst) {
  double distance = std::fabs(src.x - dst.x) + std::fabs(src.y - dst.y);
  return distance;
}

bool check_arive(location src, location dst) {
  bool flag1 = manhattan_distance(src, dst) <= 0.8;
  bool flag2 = std::fabs(src.x - dst.x) <= LIMIT_RANGE || std::fabs(src.y - dst.y) <= LIMIT_RANGE;
  return flag1 && flag2;
}

std::string move_towards_by_location(location src, location dst) {
  double delta_x = dst.x - src.x, delta_y = dst.y - src.y;
  int x_flag, y_flag;
  if (std::fabs(delta_x) <= LIMIT_RANGE) x_flag = 0;
  else if (delta_x > LIMIT_RANGE) x_flag = 1;
  else x_flag = -1;
  if (std::fabs(delta_y) <= LIMIT_RANGE) y_flag = 0;
  else if (delta_y > LIMIT_RANGE) y_flag = 1;
  else y_flag = -1;
  if (x_flag == 1 && y_flag == 1) return "RD";
  if (x_flag == -1 && y_flag == 1) return "LD";
  if (x_flag == 1 && y_flag == -1) return "RU";
  if (x_flag == -1 && y_flag == -1) return "LU";
  if (x_flag == 0 && y_flag == 1) return "D";
  if (x_flag == 0 && y_flag == -1) return "U";
  if (x_flag == 1 && y_flag == 0) return "R";
  if (x_flag == -1 && y_flag == 0) return "L";
  return " ";
}

std::pair<bool, std::string> move_towards(Player player, std::string dest) {
  assert(LUT.find(dest) != LUT.end() || map.find(dest) != map.end());
  location dst_location, src_location = { player.x, player.y };
  if (LUT.find(dest) != LUT.end()) dst_location = *LUT.find(dest)->second.begin();
  else dst_location = *map.find(dest)->second.begin();
  if (check_arive(src_location, dst_location)) return { false, " " };
  else return { true, move_towards_by_location(src_location, dst_location) };
}