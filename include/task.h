#ifndef __TASK_H__
#define __TASK_H__


#include <bits/stdc++.h>
#include <enum.h>

typedef struct task {
  std::string action;
  std::string object;
}task;

extern std::deque<task> task_pool;

void update_task_pool();
void schedule_task();
std::pair<std::string, std::string> allocate_task();

#endif