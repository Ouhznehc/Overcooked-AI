#include <task.h>
#include <action.h>
#include <common.h>
#include <debug.h>
std::deque<task> task_pool;
task player0_task_pool[4] = { {schedule_move_and_put_or_pick, "fish"} , {schedule_move_and_put_or_pick, "Plate"}, {schedule_move_and_put_or_pick, "Plate"}, {schedule_move_and_put_or_pick, "service_window"} };
// task player1_task_pool[7] = { {schedule_move, "dirty_plate_location"}, {schedule_put_or_pick, "dirty_plate_location"}, {schedule_move, "sink"}, {schedule_put_or_pick, "sink"}, {schedule_put_or_pick, "Plate"}, {schedule_move, "service_window"}, {schedule_put_or_pick, "service_window"} };
task* player0_task;
int player0_current;
std::pair<std::string, std::string> allocate_task() {
  if (player0_task == NULL) player0_task = &player0_task_pool[player0_current];
  auto rc0 = player0_task->function(Players[0], player0_task->object);
  if (rc0.first == false) {
    player0_current = (player0_current + 1) % 4;
    player0_task = &player0_task_pool[player0_current];
    return { rc0.second, "" };
  }
  else return { rc0.second, "" };
}

std::pair<bool, std::string> schedule_move_and_put_or_pick(Player player, std::string dest) {
  auto rc = move_and_put_or_pick(player, dest);
  return { rc.first, rc.first ? "Move " + rc.second : "PutOrPick " + rc.second };
}

std::pair<bool, std::string> schedule_interact(Player player, std::string dest) {
  auto rc = interact(player, dest);
  return { rc.first, rc.first ? "Interact " + rc.second : "" };
}
