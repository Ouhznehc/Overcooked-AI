#include <a_star.h>

struct Point {
  int x;
  int y;
  Point() :x(0), y(0) {}
  Point(int x, int y) : x(x), y(y) {}
};

struct Node {
  Point parent;
  Point current;
  double f;
  double g;
  double h;

  bool operator < (const Node& other) const {
    return f > other.f;
  }
};


int dx[8] = { 0, 0, -1, 1, -1, 1, -1, 1 };
int dy[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };

std::string Direction[8] = { "U", "D", "L", "R", "LU", "RU", "LD", "RD" };

Node open_list[N][N];
int close_list[N][N];


double distance(Point src, Point dst) {
  // 计算启发式函数（这里使用曼哈顿距离作为启发式函数）
  return std::fabs(src.x - dst.x) + std::fabs(src.y - dst.y);
}

bool is_valid(Point point) {
  // 检查坐标点是否有效
  return point.x >= 0 && point.x < width && point.y >= 0 && point.y < height;
}

bool is_destination(Point src, Point dst) {
  return src.x == dst.x && src.y == dst.y;
}

bool is_obstacle(int id, int direction, Point point) {

  if (map[point.x + dx[direction]][point.y] != '.') return true;
  if (map[point.x][point.y + dy[direction]] != '.') return true;
  if (map[point.x + dx[direction]][point.y + dy[direction]] != '.') return true;

  Point player_point = Point((int)player[id ^ 1].fix.x, (int)player[id ^ 1].fix.y);



  // if (point.x + dx[direction] == player_point.x && point.y == player_point.y) return true;
  // if (point.x == player_point.x && point.y + dy[direction] == player_point.y) return true;
  // if (point.x + dx[direction] == player_point.x && point.y + dy[direction] == player_point.y) return true;

  // if (player[id ^ 1].move_direction == " ") return false;

  int player_direction = -1;
  for (int i = 0; i < 8; i++) if (player[id ^ 1].move_direction == Direction[i]) player_direction = i;

  player_point = Point((int)player[id ^ 1].fix.x + dx[player_direction], (int)player[id ^ 1].fix.y + dy[player_direction]);

  if (point.x + dx[direction] == player_point.x && point.y == player_point.y) return true;
  if (point.x == player_point.x && point.y + dy[direction] == player_point.y) return true;
  if (point.x + dx[direction] == player_point.x && point.y + dy[direction] == player_point.y) return true;

  return false;
}

std::string fetch_first_move(int id, Point start, Point destination) {
  int dx[8] = { 0, 0, -1, 1, -1, 1, -1, 1 };
  int dy[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };

  int start_x = start.x;
  int start_y = start.y;

  double min_H = INFINITY;
  int first_move = -1;

  for (int i = 0; i < 8; i++) {
    int new_x = start_x + dx[i];
    int new_y = start_y + dy[i];

    if (is_valid(Point(new_x, new_y)) && !is_obstacle(id, i, Point(start_x, start_y))) {
      double new_H = distance(Point(new_x, new_y), destination);
      if (new_H < min_H) {
        min_H = new_H;
        first_move = i;
      }
    }
  }
  if (first_move == -1) return " ";
  else return Direction[first_move];
}

void init_list() {
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      open_list[i][j].f = open_list[i][j].g = open_list[i][j].h = INFINITY;
      open_list[i][j].parent.x = open_list[i][j].parent.y = -1;
      open_list[i][j].current.x = i;
      open_list[i][j].current.y = j;

      close_list[i][j] = 0;
    }
  }
}

std::string A_star_direction(int id, Location src, Location dst) {

  Point start = Point((int)src.x, (int)src.y);
  Point destination = Point((int)dst.x, (int)dst.y);
  init_list();
  // 设置起始节点
  int start_x = start.x;
  int start_y = destination.y;

  open_list[start_x][start_y] = { Point(start_x, start_y), Point(start_x, start_y), 0.0, 0.0, 0.0 };

  std::priority_queue<Node> pq;
  pq.push(open_list[start_x][start_y]);

  while (!pq.empty()) {
    Node current = pq.top();
    pq.pop();

    int current_x = current.current.x;
    int current_y = current.current.y;

    if (close_list[current_x][current_y]) continue;

    close_list[current_x][current_y] = 1;

    if (is_destination(current.current, destination)) {
      // 到达目的地，结束算法
      // std::cerr << "Destination reached" << std::endl;
      return fetch_first_move(id, start, destination);
    }

    // 对当前节点的邻居节点进行处理
    for (int i = 0; i < 8; i++) {
      int new_x = current_x + dx[i];
      int new_y = current_y + dy[i];

      if (is_valid(Point(new_x, new_y)) && !is_obstacle(id, i, Point(current_x, current_y)) && !close_list[new_x][new_y]) {
        double g_new = current.g + 1.0; // 此处假设移动一格的代价为1

        if (g_new < open_list[new_x][new_y].g) {
          // 更新邻居节点的父节点和g值
          open_list[new_x][new_y].parent.x = current_x;
          open_list[new_x][new_y].parent.y = current_y;
          open_list[new_x][new_y].g = g_new;
          open_list[new_x][new_y].h = distance(Point(new_x, new_y), destination);
          open_list[new_x][new_y].f = open_list[new_x][new_y].g + open_list[new_x][new_y].h;
          pq.push(open_list[new_x][new_y]);
        }
      }
    }
  }

  // 无法找到路径
  // std::cerr << "No path found." << std::endl;
  return " "; // 返回一个无效的方向值
}

