#include <move.h>

#define LIMIT 0

static Location fetch_move_src(Location src, Location dst, int id) {
  Location center_src = Location((int)src.x, (int)src.y);
  Location center_dst = Location((int)dst.x, (int)dst.y);
  src = { src.x - 0.5, src.y - 0.5 };
  double delta_x = std::fabs(src.x - center_src.x);
  double delta_y = std::fabs(src.y - center_src.y);
  if (center_src == center_dst) {
    assert(0);
    if (delta_x < LIMIT && delta_y < LIMIT) {
      player[id].fix.x = center_src.x;
      player[id].fix.y = center_src.y;
    }
  }
  else {
    player[id].fix.x = center_src.x;
    player[id].fix.y = center_src.y;
  }
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

static bool is_arive(Location src, Location dst, int id) {
  double hamilton_distance = std::fabs(src.x - dst.x) + std::fabs(src.y - dst.y);
  // double hamilton_velocity = std::fabs(player[id].x_velocity) + std::fabs(player[id].y_velocity);
  return hamilton_distance < 0.01;
}

static std::string fetch_pick_direction(Location src, Location dst) {
  if (dst.x == 0) return "L";
  if (dst.x == width - 1) return "R";
  if (dst.y == 0) return "U";
  if (dst.y == height - 1) return "D";
  assert(0);
}

std::pair<bool, std::string> move_towards_by_location(Location src, Location dst, int id, bool flag) {
  std::string move_direction = "";
  std::string pick_direction = "";
  Location move_src = fetch_move_src(src, dst, id);
  Location move_dst = fetch_move_dst(dst);
  // if (id == 0) {
  //   std::cerr << "src: " << src.x - 0.5 << " " << src.y - 0.5 << std::endl;
  //   std::cerr << "move_src: " << move_src.x << " " << move_src.y << std::endl;
  //   std::cerr << "dst: " << dst.x << " " << dst.y << std::endl;
  //   std::cerr << "move_dst: " << move_dst.x << " " << move_dst.y << std::endl;
  // }
  if (is_arive(move_src, move_dst, id)) {
    pick_direction = fetch_pick_direction(move_src, dst);
    player[id].move_direction = " ";
    if (flag) return { false, "PutOrPick " + pick_direction };
    else return { true, "Move " };
  }
  move_direction = A_star_direction(id, move_src, move_dst);
  if (player[id].move_direction == move_direction) return { true, "Move " + move_direction };
  if (player[id].x_velocity == 0 && player[id].y_velocity == 0) {
    player[id].move_direction = move_direction;
    return { true, "Move " + move_direction };
  }
  return { true, "Move  " };
}

std::pair<bool, std::string> lazy_around_dog(Location src, Location dst, int id) {
  auto rc = move_towards_by_location(src, dst, id, true);
  if (rc.first) return { false, rc.second };
  else return { false, "Move " };
}