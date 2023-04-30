#include <action.h>
#include <common.h>
#include <bits/stdc++.h>

#define LIMIT_RANGE 0.3
#define DELTA_X(src, dst) (dst.x - src.x)
#define DELTA_Y(src, dst) (dst.y - src.y)


double manhattan_distance(location src, location dst) {
  double distance = std::fabs(DELTA_X(src, dst)) + std::fabs(DELTA_Y(src, dst));
  return distance;
}

location set_dest_location(location dst) {
  if (dst.x == 0) return { dst.x + 1.5, dst.y + 0.5 };
  if (dst.y == 0) return { dst.x + 0.5, dst.y + 1.5 };
  if (dst.x == width - 1) return { dst.x - 0.5, dst.y + 0.5 };
  if (dst.y == height - 1) return { dst.x + 0.5, dst.y - 0.5 };
  assert(0);
}

bool check_arive(location src, location dst) {
  // bool flag1 = manhattan_distance(src, dst) <= 1.5;
  bool flag2 = std::fabs(DELTA_X(src, dst)) <= LIMIT_RANGE && std::fabs(DELTA_Y(src, dst)) <= LIMIT_RANGE;
  return true && flag2;
}

std::string move_towards(location src, location dst) {
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

std::pair<bool, std::string> move_and_put_or_pick(Player player, std::string dest) {
  if (LUT.find(dest) == LUT.end() && map.find(dest) == map.end()) {
    return { false, "" };
  }
  assert(LUT.find(dest) != LUT.end() || map.find(dest) != map.end());
  location dst_location, src_location = { player.x, player.y };
  if (LUT.find(dest) != LUT.end()) dst_location = set_dest_location(*LUT.find(dest)->second.begin());
  else dst_location = set_dest_location(*map.find(dest)->second.begin());
  // std::cerr << "src:" << src_location.x << " " << src_location.y << std::endl;
  // std::cerr << "dst:" << dst_location.x << " " << dst_location.y << std::endl;
  if (check_arive(src_location, dst_location)) {
    if (dst_location.x == 1.5) return { false, "L" };
    if (dst_location.x == width - 1.5) return { false, "R" };
    if (dst_location.y == 1.5) return { false, "U" };
    if (dst_location.y == height - 1.5) return { false, "D" };
  }
  else return { true, move_towards(src_location, dst_location) };
  assert(0);

}






std::pair<bool, std::string> interact(Player player, std::string object) {
  location dst_location = set_dest_location(*LUT.find("sink")->second.begin());
  for (int i = 0; i < entityCount; i++) {
    if (Entity[i].total_frame != 0) {
      if (dst_location.y == 1.5) return { true, "U" };
      if (dst_location.y == height - 1.5) return { true, "D" };
      if (dst_location.x == 1.5) return { true, "L" };
      if (dst_location.x == width - 1.5) return { true, "R" };
      break;
    }
  }
  return { false, " " };
}





// std::pair<bool, std::string> put_or_pick(Player player, std::string object) {
//   if (player.container == Container::Plate && object == "Plate") return { false, "" };
//   if (player.container == Container::None && object == "service_window") return { false, "" };
//   for (int i = 0; i < player.entity.size(); i++) {
//     if (player.entity[i] == object) return { false, "" };
//   }
//   if (LUT.find(object) == LUT.end() && map.find(object) == map.end()) {
//     return { false, "" };
//   }
//   assert(LUT.find(object) != LUT.end() || map.find(object) != map.end());
//   location dst_location, src_location = { player.x, player.y };
//   if (LUT.find(object) != LUT.end()) dst_location = *LUT.find(object)->second.begin();
//   else dst_location = *map.find(object)->second.begin();
//   if (std::fabs(DELTA_X(src_location, dst_location)) <= LIMIT_RANGE) {
//     if (src_location.y > dst_location.y) return { true, "U" };
//     else return { true, "D" };
//   }
//   if (std::fabs(DELTA_Y(src_location, dst_location)) <= LIMIT_RANGE) {
//     if (src_location.x > dst_location.x) return { true, "L" };
//     else return { true, "R" };
//   }
//   assert(0);
// }