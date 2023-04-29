#ifndef __ACTION_H__
#define __ACTION_H__

#include <bits/stdc++.h>
#include <enum.h>

std::pair<bool, std::string> move_towards(Player player, std::string dest);
std::pair<bool, std::string> interact(Player player, std::string object);
std::pair<bool, std::string> put_or_pick(Player player, std::string object);

#endif