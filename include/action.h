#ifndef __ACTION_H__
#define __ACTION_H__

#include <bits/stdc++.h>
#include <enum.h>

std::pair<bool, char> move_towards(Player player, std::string dest);
bool interact(Player player, std::string object);
bool put_or_pick(Player player, std::string object);

#endif