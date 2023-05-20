#ifndef __INTERACT_H__
#define __INTERACT_H__

#include <variable.h>

std::pair<bool, std::string> interact_with_object(Location src, Location dst, std::string object, std::vector<std::string> item, int id);

#endif