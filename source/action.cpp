#include <action.h>
#include <common.h>
#include <bits/stdc++.h>

#define E 1e-7
#define LIMIT_RANGE 0.3
#define SAFE_DISTANCE 1.8
#define ACCELARATE 30
#define DELTA_X(src, dst) (dst.x - src.x)
#define DELTA_Y(src, dst) (dst.y - src.y)


double manhattan_distance(location src, location dst) {
  double distance = std::fabs(DELTA_X(src, dst)) + std::fabs(DELTA_Y(src, dst));
  return distance;
}

std::pair<bool, std::string> alert_dest(Player player, location dst) {
  double delta_x = dst.x - player.x;
  double delta_y = dst.y - player.y;
  bool x_flag, y_flag;
  if (delta_x > 0 && player.x_velocity > 0) {
    if (delta_x < player.x_velocity * player.x_velocity / ACCELARATE) x_flag = 1;
    else x_flag = 0;
  }
  else if (delta_x < 0 && player.x_velocity < 0) {
    if (-delta_x < player.x_velocity * player.x_velocity / ACCELARATE) x_flag = 1;
    else x_flag = 0;
  }
  if (delta_y > 0 && player.y_velocity > 0) {
    if (delta_y < player.y_velocity * player.y_velocity / ACCELARATE) y_flag = 1;
    else y_flag = 0;
  }
  else if (delta_y < 0 && player.y_velocity < 0) {
    if (-delta_y < player.y_velocity * player.y_velocity / ACCELARATE) y_flag = 1;
    else y_flag = 0;
  }
  if (x_flag || y_flag) return { true, " " };
  else return { false, " " };
}

std::pair<bool, std::string> alert_player(Player player0, Player player1) {
  double delta_x = std::fabs(player1.x - player0.x);
  double delta_y = std::fabs(player1.y - player0.y);
  int x_flag, y_flag;
  if (delta_x < (player0.x_velocity - player1.x_velocity) * (player0.x_velocity - player1.x_velocity) / 60) x_flag = 1;
  else x_flag = 0;
  if (delta_y < (player0.y_velocity - player1.y_velocity) * (player0.y_velocity - player1.y_velocity) / 60) y_flag = 1;
  else y_flag = 0;
  if (x_flag || y_flag) return { true, " " };
  else return { false, " " };
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
  // std::cerr << "src:" << src.x << " " << src.y << std::endl;
  // std::cerr << "dst:" << dst.x << " " << dst.y << std::endl;
  // if (src.x <= SAFE_DISTANCE) return "R";
  // else if (src.x >= width - SAFE_DISTANCE) return "L";
  // if (src.y <= SAFE_DISTANCE) return "D";
  // else if (src.y >= height - SAFE_DISTANCE) return "U";
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
    return { true, " " };
  }
  auto alert = alert_player(Players[0], Players[1]);
  if (alert.first) return{ true, " " };
  location player0_location = { Players[0].x, Players[0].y };
  location player1_location = { Players[1].x, Players[1].y };
  // if (manhattan_distance(player0_location, player1_location) <= 2.0) {
  //   if (player1_location.x == player.x && player1_location.y == player.y) {
  //     return { true, " " };
  //   }
  // }
  assert(LUT.find(dest) != LUT.end() || map.find(dest) != map.end());
  location dst_set_location, dst_location, src_location = { player.x, player.y };
  if (LUT.find(dest) != LUT.end()) {
    dst_location = *LUT.find(dest)->second.begin();
    dst_set_location = set_dest_location(dst_location);
  }
  else {
    dst_location = *map.find(dest)->second.begin();
    dst_set_location = set_dest_location(dst_location);
  }
  // std::cerr << "src:" << src_location.x << " " << src_location.y << std::endl;
  // std::cerr << "dst:" << dst_location.x << " " << dst_location.y << std::endl;
  if (check_arive(src_location, dst_set_location)) {
    if (dst_location.y == 0) return { false, "U" };
    if (dst_location.y == height - 1) return { false, "D" };
    if (dst_location.x == 0) return { false, "L" };
    if (dst_location.x == width - 1) return { false, "R" };
  }
  else {
    auto rc = alert_dest(player, dst_set_location);
    if (rc.first) return { true, rc.second };
    else return { true, move_towards(src_location, dst_set_location) };
  }
  assert(0);

}






std::pair<bool, std::string> interact(Player player, std::string object) {
  location sink_location = *LUT.find("sink")->second.begin();
  if (map.find("DirtyPlates") == map.end()) return { false, " " };
  for (auto it : map.find("DirtyPlates")->second) {
    location plate_location = it;
    if (plate_location.x == sink_location.x && plate_location.y == sink_location.y) {
      if (sink_location.y == 0) return { true, "U" };
      if (sink_location.y == height - 1) return { true, "D" };
      if (sink_location.x == 0) return { true, "L" };
      if (sink_location.x == width - 1) return { true, "R" };
      assert(0);
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