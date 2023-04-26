#include <task.h>
#include <action.h>
std::deque<task> task_pool;

std::pair<std::string, std::string> allocate_task() {
  return { "Move R", "Move D" };
}