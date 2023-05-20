#include <schedule.h>
#include <move.h>
#include <interact.h>

static void update_current_task() {
  if (wash_work.task_cnt == -1) {
    wash_work.task_cnt = 0;
    if (dynamic_lut.find("DirtyPlates") != dynamic_lut.end()) {
      // std::cerr << "wash_work: " << "wash_plates" << std::endl;
      wash_work.current_task = order_lut[{"wash_plates"}];
    }
    else {
      // std::cerr << "wash_work: " << "lazy_around" << std::endl;
      wash_work.current_task = order_lut[{"lazy_around"}];
    }
  }
  if (cook_work.task_cnt == -1) {
    cook_work.task_cnt = 0;
    if (dynamic_lut.find("Plate") != dynamic_lut.end()) {
      cook_work.current_task = order_lut[order[0].recipe];
    }
    else {
      cook_work.current_task = order_lut[{"lazy_around"}];
    }
  }
  // std::cerr << "cook_work: " << cook_work.current_task[0].object << std::endl;
}

static std::pair<Location, Location> fetch_task_dst() {
  Location cook_dst, wash_dst;
  std::string cook_object = cook_work.current_task[cook_work.task_cnt].object;
  std::string wash_object = wash_work.current_task[wash_work.task_cnt].object;
  if (static_lut.find(cook_object) != static_lut.end()) cook_dst = static_lut.at(cook_object)[0];
  else if (dynamic_lut.find(cook_object) != dynamic_lut.end()) cook_dst = dynamic_lut.at(cook_object)[0];
  else {
    std::cerr << "cannot find dst" << std::endl;;
    assert(0);
  }
  if (static_lut.find(wash_object) != static_lut.end()) wash_dst = static_lut.at(wash_object)[0];
  else if (dynamic_lut.find(wash_object) != dynamic_lut.end()) wash_dst = dynamic_lut.at(wash_object)[0];
  else {
    std::cerr << "cannot find dst" << std::endl;;
    assert(0);
  }
  return { cook_dst, wash_dst };
}

static double distance(Location a, Location b) {
  return std::max(std::fabs(a.x - b.x), std::fabs(a.y - b.y));
}

static std::pair<task_t, task_t> allocate_task_by_location(Location cook_dst, Location wash_dst) {
  task_t player0_task, player1_task;
  if (player[0].status == work_status::busy) {
    if (cook_work.player == player::player0) {
      player0_task = cook_work.current_task[cook_work.task_cnt];
      player1_task = wash_work.current_task[wash_work.task_cnt];
    }
    else {
      player0_task = wash_work.current_task[wash_work.task_cnt];
      player1_task = cook_work.current_task[cook_work.task_cnt];
    }
  }
  else if (player[1].status == work_status::busy) {
    if (cook_work.player == player::player1) {
      player0_task = wash_work.current_task[wash_work.task_cnt];
      player1_task = cook_work.current_task[cook_work.task_cnt];
    }
    else {
      player0_task = cook_work.current_task[cook_work.task_cnt];
      player1_task = wash_work.current_task[wash_work.task_cnt];
    }
  }
  else {
    if (distance(player[0].src, cook_dst) < distance(player[1].src, cook_dst)) {
      cook_work.player = player::player0;
      wash_work.player = player::player1;
      player0_task = cook_work.current_task[cook_work.task_cnt];
      player1_task = wash_work.current_task[wash_work.task_cnt];
    }
    else {
      cook_work.player = player::player1;
      wash_work.player = player::player0;
      player1_task = cook_work.current_task[cook_work.task_cnt];
      player0_task = wash_work.current_task[wash_work.task_cnt];
    }
  }
  assert(cook_work.player != wash_work.player);
  if (cook_work.player == player::player0) player[0].dst = cook_dst;
  else player[1].dst = cook_dst;
  if (wash_work.player == player::player0) player[0].dst = wash_dst;
  else player[1].dst = wash_dst;
  return { player0_task, player1_task };
}

static std::pair<task_t, task_t> allocate_task() {
  update_current_task();
  auto dst = fetch_task_dst();
  auto cook_dst = dst.first, wash_dst = dst.second;
  return allocate_task_by_location(cook_dst, wash_dst);
}

std::string handle_task(task_t task, int id) {
  std::string action;
  std::pair<bool, std::string> rc;
  switch (task.action) {
  case action::move_towards:
    // std::cerr << "player#" << id << " move_towards" << std::endl;
    rc = move_towards_by_location(player[id].src, player[id].dst, id);
    action = rc.second;
    break;
  case action::interact_with:
    // std::cerr << "player#" << id << " interact_with" << std::endl;
    player[id].status = work_status::busy;
    rc = interact_with_object(player[id].src, player[id].dst, task.object, task.item, id);
    action = rc.second;
    break;
  case action::lazy_around:
    // std::cerr << "player#" << id << " lazy_around" << std::endl;
    rc = lazy_around_dog(player[id].src, player[id].dst, id);
    action = rc.second;
    break;
  default:
    break;
  }
  if (rc.first == false) {
    player[id].status = work_status::leisure;
    if (cook_work.player == id) cook_work.task_cnt++;
    else wash_work.task_cnt++;
  }
  if (cook_work.task_cnt == cook_work.current_task.size()) cook_work.task_cnt = -1;
  if (wash_work.task_cnt == wash_work.current_task.size()) wash_work.task_cnt = -1;
  return action;
}

std::pair<std::string, std::string> schedule_task() {
  std::string player0_action, player1_action;
  auto task = allocate_task();
  auto player0_task = task.first, player1_task = task.second;
  player0_action = handle_task(player0_task, player::player0);
  player1_action = handle_task(player1_task, player::player1);
  return { player0_action, player1_action };
}
