#include <task.h>
#include <action.h>
#include <common.h>

std::deque<task> task_pool;

std::pair<std::string, std::string> allocate_task() {
  return { schedule_move("Plate"), schedule_move("fish") };
}

std::string schedule_move(std::string dest) {
  auto rc = move_towards(Players[0], dest);
  return "Move " + rc.second;
}