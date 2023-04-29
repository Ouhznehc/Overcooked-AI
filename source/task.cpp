#include <task.h>
#include <action.h>
#include <common.h>
#include <debug.h>

std::deque<task> task_pool;

std::pair<std::string, std::string> allocate_task() {
  while (1) {
    while (schedule_move(Player[0], "fish"));
    while (schedule_put_or_pick(Player[0], "fish"));
    while (schedule_move(Player[0], "Plate"));
    while (schedule_put_or_pick(Player[0], "Plate"));
    while (schedule_put_or_pick(Player[0], "Plate"));
    while (schedule_move(Player[0], "service_window"));
    while (schedule_put_or_pick(Player[0], "service_window"));
  }
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
