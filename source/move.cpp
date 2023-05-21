#include <move.h>

static Location fetch_move_src(Location src) {
  return src;
}

static Location fetch_move_dst(Location dst) {
  if (dst.x == 0) return { dst.x + 1.5, dst.y + 0.5 };
  if (dst.x == width - 1) return { dst.x - 0.5, dst.y + 0.5 };
  if (dst.y == 0) return { dst.x + 0.5, dst.y + 1.5 };
  if (dst.y == height - 1) return { dst.x + 0.5, dst.y - 0.5 };
  assert(0);
}

static bool is_arive(Location src, Location dst, int id) {
  double hamilton_distance = std::fabs(src.x - dst.x) + std::fabs(src.y - dst.y);
  double hamilton_velocity = std::fabs(player[id].x_velocity) + std::fabs(player[id].y_velocity);
  return hamilton_distance < 0.05;
}

static std::string fetch_pick_direction(Location src, Location dst) {
  if (dst.x == 0) return "L";
  if (dst.x == width - 1) return "R";
  if (dst.y == 0) return "U";
  if (dst.y == height - 1) return "D";
  assert(0);
}

std::pair<bool, std::string> move_towards_by_location(Location src, Location dst, int id) {
  std::string move_direction = "";
  std::string pick_direction = "";
  Location move_src = fetch_move_src(src);
  Location move_dst = fetch_move_dst(dst);
  if (is_arive(move_src, move_dst, id)) {
    pick_direction = fetch_pick_direction(move_src, dst);
    return { false, "PutOrPick " + pick_direction };
  }
  if (move_src.x > move_dst.x) move_direction += "L";
  if (move_src.x < move_dst.x) move_direction += "R";
  if (move_src.y > move_dst.y) move_direction += "U";
  if (move_src.y < move_dst.y) move_direction += "D";

  return { true, "Move " + move_direction };
}

std::pair<bool, std::string> lazy_around_dog(Location src, Location dst, int id) {
  auto rc = move_towards_by_location(src, dst, id);
  if (rc.first) return { false, rc.second };
  else return { false, "Move " };
}