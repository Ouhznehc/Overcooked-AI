#include <action.h>
#include <common.h>
#include <bits/stdc++.h>

#define E 1e-7
#define LIMIT_RANGE 0.3
#define SAFE_DISTANCE 1.8
#define ACCELARATE 45
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
  if (x_flag || y_flag) {
    if (x_flag && y_flag) return { true, " " };
    else if (x_flag) {
      if (player.x_velocity > 0) {
        if (player.y_velocity > 0) return{ true, "LD" };
        else return { true, "LU" };
      }
      else {
        if (player.y_velocity > 0) return{ true, "RD" };
        else return { true, "RU" };
      }
    }
    else if (y_flag) {
      if (player.y_velocity > 0) {
        if (player.x_velocity > 0) return { true, "RU" };
        else return { true, "LU" };
      }
      else {
        if (player.x_velocity > 0) return { true, "RD" };
        else return { true, "LD" };
      }
    }
    else assert(0);
  }
  else return { false, " " };
}

// std::pair<bool, std::string> alert_player(Player player0, Player player1, Player player) {
//   double delta_x = std::fabs(player1.x - player0.x) - 1;
//   double delta_y = std::fabs(player1.y - player0.y) - 1;
//   int x_flag, y_flag;
//   if (delta_x < (player0.x_velocity - player1.x_velocity) * (player0.x_velocity - player1.x_velocity) / ACCELARATE) x_flag = 1;
//   else x_flag = 0;
//   if (delta_y < (player0.y_velocity - player1.y_velocity) * (player0.y_velocity - player1.y_velocity) / ACCELARATE) y_flag = 1;
//   else y_flag = 0;
//   if (x_flag && y_flag) {
//     int x_move, y_move;
//     if (player.x == player0.x && player.y == player0.y) {
//       if (player.x_velocity - player1.x_velocity > 0) x_move = -1;
//       else x_move = 1;
//     }
//     else {
//       if (player.x_velocity - player0.x_velocity > 0) x_move = -1;
//       else x_move = 1;
//     }
//     if (player.x == player0.x && player.y == player0.y) {
//       if (player.y_velocity - player1.y_velocity > 0) y_move = -1;
//       else y_move = 1;
//     }
//     else {
//       if (player.y_velocity - player0.y_velocity > 0) y_move = -1;
//       else y_move = 1;
//     }
//     if (x_move == 1 && y_move == 1) return { true, "RD" };
//     if (x_move == 1 && y_move == -1) return { true, "RU" };
//     if (x_move == -1 && y_move == 1) return { true, "LD" };
//     if (x_move == -1 && y_move == -1) return { true, "LU" };
//     assert(0);
//   }
//   else return { false, " " };
// }

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
    assert(0);
  }
  else {
    auto move = move_towards(src_location, dst_set_location);
    auto rc = alert_dest(player, dst_set_location);
    if (rc.first) return { true, " " };
    return { true, move };
  }
}
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