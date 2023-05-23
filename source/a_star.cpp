#include <a_star.h>

std::string A_star_direction(Location src, Location dst) {
  std::string ret = "";
  if (src.x > dst.x) ret += "L";
  if (src.x < dst.x) ret += "R";
  if (src.y > dst.y) ret += "U";
  if (src.y < dst.y) ret += "D";
  return ret;
}