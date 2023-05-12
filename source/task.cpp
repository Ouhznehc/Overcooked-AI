#include <task.h>
#include <action.h>
#include <common.h>
#include <debug.h>

std::deque<task> task_pool;
task player0_task_pool[9] = { {schedule_move_and_put_or_pick, "fish"} , {schedule_move_and_put_or_pick, "Chop"}, {schedule_interact, "fish"}, {schedule_move_and_put_or_pick, "c_fish"}, {schedule_move_and_put_or_pick, "Pan"}, {schedule_interact, "c_fish"}, {schedule_move_and_put_or_pick, "Plate"}, {schedule_move_and_put_or_pick, "s_fish"},  {schedule_move_and_put_or_pick, "service_window"} };
task player1_task_pool[4] = { {schedule_move_and_put_or_pick, "DirtyPlates"}, {schedule_move_and_put_or_pick, "sink"}, {schedule_stop, " "}, {schedule_interact, "DirtyPlates"} };
task* player0_task;
task* player1_task;
int player0_current;
int player1_current;
std::pair<std::string, std::string> allocate_task() {
  if (player0_task == NULL) player0_task = &player0_task_pool[player0_current];
  if (player1_task == NULL) player1_task = &player1_task_pool[player1_current];
  //if (player0_current == 0) player0_task->object = *Order[0].recipe.begin();
  auto rc0 = player0_task->function(Players[0], player0_task->object);
  auto rc1 = player1_task->function(Players[1], player1_task->object);
  if (rc0.first == false) {
    player0_current = (player0_current + 1) % 9;
    player0_task = &player0_task_pool[player0_current];
  }
  if (rc1.first == false) {
    player1_current = (player1_current + 1) % 4;
    player1_task = &player1_task_pool[player1_current];
  }
  return { rc0.second, rc1.second };
}

std::pair<bool, std::string> schedule_move_and_put_or_pick(Player player, std::string dest) {
  auto rc = move_and_put_or_pick(player, dest);
  return { rc.first, rc.first ? "Move " + rc.second : "PutOrPick " + rc.second };
}

std::pair<bool, std::string> schedule_interact(Player player, std::string dest) {
  auto rc = interact(player, dest);
  // std::cerr << rc.first << " " << "Interact " + rc.second << std::endl;
  return { rc.first, rc.first ? "Interact " + rc.second : "Move " + rc.second };
}

std::pair<bool, std::string> schedule_stop(Player player, std::string dest) {
  if (player.x_velocity == 0 && player.y_velocity == 0) return { false, "Move" };
  // std::cerr << "loop " << remainFrame << std::endl;
  return { true, "Move" };
}
