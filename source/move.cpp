#include <move.h>

std::pair<bool, std::string> move_towards_by_location(Location src, Location dst, int id) {
  return { true, "Move R" };
}

std::pair<bool, std::string> lazy_around_dog(Location src, Location dst, int id) {
  return { true, "Move L" };
}