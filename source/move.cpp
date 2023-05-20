#include <move.h>

static Location fetch_move_src(Location src) {
  return src;
}

static Location fetch_move_dst(Location dst) {
  std::cerr << dst.x << " " << dst.y << std::endl;
  if (dst.x == 0) return { dst.x + 1.5, dst.y + 0.5 };
  if (dst.x == width - 1) return { dst.x - 0.5, dst.y + 0.5 };
  if (dst.y == 0) return { dst.x + 0.5, dst.y + 1.5 };
  if (dst.y == height - 1) return { dst.x + 0.5, dst.y - 0.5 };
  assert(0);
}

std::pair<bool, std::string> move_towards_by_location(Location src, Location dst, int id) {
  std::string move_direction = "";
  Location move_src = fetch_move_src(src);
  Location move_dst = fetch_move_dst(dst);
  if (move_src.x > move_dst.x) move_direction += "L";
  if (move_src.x < move_dst.x) move_direction += "R";
  if (move_src.y > move_dst.y) move_direction += "U";
  if (move_src.y < move_dst.y) move_direction += "D";
  return { true, "Move " + move_direction };
}

std::pair<bool, std::string> lazy_around_dog(Location src, Location dst, int id) {
  auto rc = move_towards_by_location(src, dst, id);
  return { false, rc.second };
}