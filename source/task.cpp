#include <task.h>
#include <action.h>
#include <common.h>
#include <debug.h>
std::deque<task> task_pool;
task player0_task_pool[7] = { {schedule_move, "fish"}, {schedule_put_or_pick, "fish"}, {schedule_move, "Plate"}, {schedule_put_or_pick, "Plate"}, {schedule_put_or_pick, "Plate"}, {schedule_move, "service_window"}, {schedule_put_or_pick, "service_window"} };
task* player0_task;
int player0_current;
std::pair<std::string, std::string> allocate_task() {
  if (player0_current == NULL) player0_task = &player0_task_pool[current];
  auto rc = player0_task->function(Players[0], player0_task->object);
  if (rc == "") {
    player0_current = (current + 1) % 7;
    player0_task = &player0_task_pool[player0_current];
    return { "", "" };
  }
  else return { rc, "" };
}

std::string schedule_move(Player player, std::string dest) {
  auto rc = move_towards(player, dest);
  return rc.first ? "Move " + rc.second : "";
}

std::string schedule_interact(Player player, std::string dest) {
  auto rc = interact(player, dest);
  return rc.first ? "Interact " + rc.second : "";
}

std::string schedule_put_or_pick(Player player, std::string dest) {
  auto rc = put_or_pick(player, dest);
  return rc.first ? "PutOrPick " + rc.second : "";
}
