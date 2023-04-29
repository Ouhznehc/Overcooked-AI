#include <action.h>
#include <common.h>

bool check_arive(location src, location dst) {
  double distance = (src.x - dst.x) * (src.x - dst.x) + (src.y - dst.y) * (src.y - dst.y);
  return distance <= 10.0;
}


std::string move_towards_by_location(location src, location dst) {
  double delta_x = dst.x - src.x, delta_y = dst.y - src.y;
  if (delta_x > 1) return "R";
  if (delta_x < -1) return "L";
  if (delta_y > 1) return "D";
  if (delta_y < -1) return "U";
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