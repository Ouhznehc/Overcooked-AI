#include <move.h>

#define LIMIT 0.35

static Location fetch_move_src(Location src, int id) {
  Location center_src = Location((int)src.x, (int)src.y);
  src = { src.x - 0.5, src.y - 0.5 };
  double delta_x = std::fabs(src.x - center_src.x);
  double delta_y = std::fabs(src.y - center_src.y);
  if (delta_x < LIMIT && delta_y < LIMIT) {
    player[id].fix.x = center_src.x;
    player[id].fix.y = center_src.y;
    player[id].margin = false;
  }
  else player[id].margin = true;
  return player[id].fix;
}

static Location fetch_move_dst(Location dst) {
  if (dst.x == 0) return { dst.x + 1, dst.y };
  if (dst.x == width - 1) return { dst.x - 1, dst.y };
  if (dst.y == 0) return { dst.x, dst.y + 1 };
  if (dst.y == height - 1) return { dst.x, dst.y - 1 };
  std::cerr << dst.x << " " << dst.y << std::endl;
  assert(0);
}

static bool is_almost_arive(Location src, Location dst) {
  return src == dst;
}
static bool is_surely_arive(Location src, Location dst, int id) {
  src = { src.x - 0.5, src.y - 0.5 };
  double delta_x = std::fabs(src.x - dst.x);
  double delta_y = std::fabs(src.y - dst.y);
  double distance = std::sqrt(delta_x * delta_x + delta_y * delta_y);
  bool is_stop = player[id].x_velocity == 0 && player[id].y_velocity == 0;
  return distance < 0.3 && is_stop;
}

static std::string fetch_pick_direction(Location src, Location dst) {
  if (dst.x == 0) return "L";
  if (dst.x == width - 1) return "R";
  if (dst.y == 0) return "U";
  if (dst.y == height - 1) return "D";
  assert(0);
}

static std::string change_move_direction(std::string prev, std::string next, int id) {
  assert(prev != next);
  if (player[id].x_velocity == 0 && player[id].y_velocity == 0 && !player[id].margin) {
    player[id].move_direction = next;
    return next;
  }
  if (player[id].margin) return prev;
  else return " ";
}

static std::string slightly_move_towards(Location src, Location dst, int id) {
  src = { src.x - 0.5, src.y - 0.5 };
  double delta_x = std::fabs(src.x - dst.x);
  double delta_y = std::fabs(src.y - dst.y);
  double distance = std::sqrt(delta_x * delta_x + delta_y * delta_y);
  if (distance < 0.05) return " ";
  std::string ret = "";
  if (src.x > dst.x) ret += "L";
  if (src.x < dst.x) ret += "R";
  if (src.y > dst.y) ret += "U";
  if (src.y < dst.y) ret += "D";
  return ret;
}


std::pair<bool, std::string> move_towards_by_location(Location src, Location dst, int id, bool flag) {
  std::string move_direction = "";
  std::string pick_direction = "";
  Location move_dst = fetch_move_dst(dst);
  Location move_src = fetch_move_src(src, id);

  // if (id == 0) {
  //   std::cerr << "src: " << src.x - 0.5 << " " << src.y - 0.5 << std::endl;
  //   std::cerr << "move_src: " << move_src.x << " " << move_src.y << std::endl;
  //   std::cerr << "dst: " << dst.x << " " << dst.y << std::endl;
  //   std::cerr << "move_dst: " << move_dst.x << " " << move_dst.y << std::endl;
  // }
  if (is_almost_arive(move_src, move_dst)) {
    if (is_surely_arive(src, dst, id)) {
      pick_direction = fetch_pick_direction(move_src, dst);
      player[id].move_direction = " ";
      if (flag) return { false, "PutOrPick " + pick_direction };
      else return { true, "Move " };
    }
    else return { true, "Move " + slightly_move_towards(src, move_dst, id) };
  }
  move_direction = A_star_direction(id, move_src, move_dst);
  if (player[id].move_direction == move_direction) return { true, "Move " + move_direction };
  else return { true, "Move " + change_move_direction(player[id].move_direction, move_direction, id) };
  return { true, "Move " + player[id].move_direction };
}

std::pair<bool, std::string> lazy_around_dog(Location src, Location dst, int id) {
  auto rc = move_towards_by_location(src, dst, id, true);
  if (rc.first) return { false, rc.second };
  else return { false, "Move " };
}