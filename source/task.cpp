#include <task.h>
#include <action.h>
#include <common.h>
#include <debug.h>

std::deque<task> task_pool;
task taskPool[7] = { {schedule_move, "fish"}, {schedule_put_or_pick, "fish"}, {schedule_move, "Plate"}, {schedule_put_or_pick, "Plate"}, {schedule_put_or_pick, "Plate"}, {schedule_move, "service_window"}, {schedule_put_or_pick, "service_window"} };
task* current_task;
int current;
std::pair<std::string, std::string> allocate_task() {
  if (current_task == NULL) current_task = &taskPool[current];
  auto rc = current_task->function(Players[0], current_task->object);
  if (rc == NULL) current_task = &taskPool[(current + 1) % 7], current++;
  else return { rc, " " };
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
