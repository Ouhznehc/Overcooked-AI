#include <action.h>
#include <common.h>
#include <bits/stdc++.h>

#define LIMIT_RANGE 0.01
#define DELTA_X(src, dst) (dst.x - src.x + 0.5)
#define DELTA_Y(src, dst) (dst.y - src.y + 0.5)

double manhattan_distance(location src, location dst) {
  double distance = std::fabs(DELTA_X(src, dst)) + std::fabs(DELTA_Y(src, dst));
  return distance;
}

bool check_arive(location src, location dst) {
  bool flag1 = manhattan_distance(src, dst) <= 1.0;
  bool flag2 = std::fabs(DELTA_X(src, dst)) <= LIMIT_RANGE || std::fabs(DELTA_Y(src, dst)) <= LIMIT_RANGE;
  return flag1 && flag2;
}

std::string move_towards_by_location(location src, location dst) {
  double delta_x = DELTA_X(src, dst), delta_y = DELTA_Y(src, dst);
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

std::pair<bool, std::string> interact(Player player, std::string object) {

}
std::pair<bool, std::string> put_or_pick(Player player, std::string object) {
  if (player.container == Container::Plate) return { false, NULL };
  for (int i = 0; i < player.entity.size(); i++) {
    if (player.entity[i] == object) return { false, NULL };
  }
  return { false, NULL };
}