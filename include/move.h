#ifndef __MOVE_H__
#define __MOVE_H__

#include <variable.h>

std::pair<bool, std::string> move_towards_by_location(Location src, Location dst, int id);
std::pair<bool, std::string> lazy_around_dog(Location src, Location dst, int id);

#endif