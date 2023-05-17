#ifndef __SCHEDULE_H__
#define __SCHEDULE_H__

#include <variable.h>

std::pair<bool, std::string> move_towards(std::string object, std::vector<std::string> items);
std::pair<bool, std::string> interact_with(std::string object, std::vector<std::string> items);
#endif