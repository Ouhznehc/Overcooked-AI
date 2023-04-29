#include <action.h>
#include <common.h>

double manhattan_distance(location src, location dst) {
  double distance = std::fabs(src.x - dst.x) + std::fabs(src.y - dst.y);
  return distance;
}


std::string move_towards_by_location(location src, location dst) {
  double delta_x = dst.x - src.x, delta_y = dst.y - src.y;
  if (delta_x > 0.1) return "R";
  if (delta_x < -0.1) return "L";
  if (delta_y > 0.1) return "D";
  if (delta_y < -0.1) return "U";
  return " ";
}

std::pair<bool, std::string> move_towards(Player player, std::string dest) {
  assert(LUT.find(dest) != LUT.end() || map.find(dest) != map.end());
  location dst_location, src_location = { player.x, player.y };
  if (LUT.find(dest) != LUT.end()) dst_location = *LUT.find(dest)->second.begin();
  else dst_location = *map.find(dest)->second.begin();
  if (manhattan_distance(src_location, dst_location) <= 1.0) return { false, " " };
  else return { true, move_towards_by_location(src_location, dst_location) };
}