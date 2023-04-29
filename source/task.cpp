#include <task.h>
#include <action.h>
#include <common.h>
#include <debug.h>

std::deque<task> task_pool;

std::pair<std::string, std::string> allocate_task() {
  return { schedule_move(Playes[0], "Plate"), schedule_move(Players[1], "fish") };
}

std::string schedule_move(Player player, std::string dest) {
  auto rc = move_towards(player, dest);
  return "Move " + rc.second;
}