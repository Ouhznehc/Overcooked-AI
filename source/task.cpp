#include <task.h>
#include <action.h>
#include <common.h>
#include <debug.h>

std::deque<task> task_pool;

std::pair<std::string, std::string> allocate_task() {
  return { schedule_move(Players[0], "Plate"), schedule_move(Players[1], "fish") };
}

std::string schedule_move(Player player, std::string dest) {
  auto rc = move_towards(player, dest);
  return rc.first ? "Move " + rc.second : NULL;
}

std::string schedule_interact(Player player, std::string dest) {
  auto rc = interact(player, dest);
  return rc.first ? "Interact " + rc.second : NULL;
}

std::string schedule_put_or_pick(Player player, std::string dest) {
  auto rc = put_or_pick(player, dest);
  return rc.first ? "PutOrPick " + rc.second : NULL;
}
