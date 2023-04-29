#include <action.h>
#include <common.h>

bool check_arive(location src, location dst) {

}


std::string move_towards_by_lacation(locaton src, location dst) {

}

std::pair<bool, std::string> move_towards(Player player, std::string dest) {
  assert(LUT.find(dest) != LUT.end() || map.find(dest) != map.end());
  location dst_location, src_location = { player.x, player.y };
  if (LUT.find(dest) != LUT.end()) dst_location = *LUT.find(dest)->second.begin();
  else dst_location = *map.find(dest)->second.begin();
  if (check_arive(src_location, dst_location)) return { false, NULL };
  else return { true, move_towards_by_location(src_location, dst_location) };
}