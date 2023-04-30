#ifndef __TASK_H__
#define __TASK_H__


#include <bits/stdc++.h>
#include <enum.h>

typedef struct task {
  std::string(*function)(Player, std::string);
  std::string object;
}task;

extern std::deque<task> task_pool;

void update_task_pool();
void schedule_task();
std::pair<bool, std::string> schedule_move_and_put_or_pick(Player player, std::string dest);
std::pair<bool, std::string> schedule_interact(Player player, std::string dest);
std::pair<std::string, std::string> allocate_task();

#endif