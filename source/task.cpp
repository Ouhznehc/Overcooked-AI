#include <task.h>
#include <action.h>
#include <common.h>
#include <debug.h>
#include <enum.h>

std::deque<task> task_pool;

std::pair<std::string, std::string> allocate_task() {
  return { schedule_move(Player[0], "Plate"), schedule_move(Player[1], "fish") };
}

std::string schedule_move(Player player, std::string dest) {
  auto rc = move_towards(player, dest);
  return "Move " + rc.second;
}