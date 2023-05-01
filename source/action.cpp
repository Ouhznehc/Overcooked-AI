#include <action.h>
#include <common.h>
#include <bits/stdc++.h>

#define E 1e-7
#define LIMIT_RANGE 0.3
#define SAFE_DISTANCE 1.8
#define ACCELARATE 30
#define DELTA_X(src, dst) (dst.x - src.x)
#define DELTA_Y(src, dst) (dst.y - src.y)

const int inf = 100;

const int dx[] = { -1, -1, -1, 0, 1, 1, 1, 0, 0 };
const int dy[] = { -1, 0, 1, 1, 1, 0, -1, -1, 0 };

enum Direction {
  Direction_LU = 0,
  Direction_L = 1,
  Direction_LD = 2,
  Direction_D = 3,
  Direction_RD = 4,
  Direction_R = 5,
  Direction_RU = 6,
  Direction_U = 7,
  Direction_N = 8
};
const std::string direction_name[] = { "LU", "L", "LD", "D", "RD", "R", "RU", "U", " " };


void evaluate_map(Player player) {
  memset(ValueMap, 0, sizeof(ValueMap));
  int player_x, player_y, cliff_x, cliff_y;
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < width; y++) {
      if (Map[y][x] == '.') ValueMap[x][y] += -1;
      else ValueMap[x][y] += -inf;
      if (Map[x][y] == '_') {
        cliff_x = x;
        cliff_y = y;
      }
    }
  }
  if (player.x == Players[0].x && player.y == Players[0].y) {
    player_x = (int)Players[1].x;
    player_y = (int)Players[1].y;
  }
  else {
    player_x = (int)Players[0].x;
    player_y = (int)Players[0].y;
  }

  ValueMap[player_x][player_y] += -inf;
  ValueMap[cliff_x][cliff_y] += -inf;
  for (int i = 0; i < 9; i++) {
    ValueMap[player_x + dx[i]][player_y + dy[i]] += -inf;
    ValueMap[cliff_x + dx[i]][cliff_y + dy[i]] += -inf;
  }
  // location start_location = { (double)(int)src.x, (double)(int)src.y };
  // location end_location = { (double)(int)dst.x, (double)(int)dst.y };
}

double manhattan_distance(location src, location dst) {
  double distance = std::fabs(DELTA_X(src, dst)) + std::fabs(DELTA_Y(src, dst));
  return distance;
}

std::pair<bool, std::string> alert_dest(Player player, location dst) {
  double delta_x = dst.x - player.x;
  double delta_y = dst.y - player.y;
  bool x_flag, y_flag;
  if (delta_x > 0 && player.x_velocity > 0) {
    if (delta_x < player.x_velocity * player.x_velocity / ACCELARATE) x_flag = 1;
    else x_flag = 0;
  }
  else if (delta_x < 0 && player.x_velocity < 0) {
    if (-delta_x < player.x_velocity * player.x_velocity / ACCELARATE) x_flag = 1;
    else x_flag = 0;
  }
  if (delta_y > 0 && player.y_velocity > 0) {
    if (delta_y < player.y_velocity * player.y_velocity / ACCELARATE) y_flag = 1;
    else y_flag = 0;
  }
  else if (delta_y < 0 && player.y_velocity < 0) {
    if (-delta_y < player.y_velocity * player.y_velocity / ACCELARATE) y_flag = 1;
    else y_flag = 0;
  }
  if (x_flag || y_flag) {
    if (x_flag && y_flag) return { true, " " };
    else if (x_flag) {
      if (player.x_velocity > 0) {
        if (player.y_velocity > 0) return{ true, "LD" };
        else return { true, "LU" };
      }
      else {
        if (player.y_velocity > 0) return{ true, "RD" };
        else return { true, "RU" };
      }
    }
    else if (y_flag) {
      if (player.y_velocity > 0) {
        if (player.x_velocity > 0) return { true, "RU" };
        else return { true, "LU" };
      }
      else {
        if (player.x_velocity > 0) return { true, "RD" };
        else return { true, "LD" };
      }
    }
    else assert(0);
  }
  else return { false, " " };
}

// std::pair<bool, std::string> alert_player(Player player0, Player player1, Player player) {
//   double delta_x = std::fabs(player1.x - player0.x) - 1;
//   double delta_y = std::fabs(player1.y - player0.y) - 1;
//   int x_flag, y_flag;
//   if (delta_x < (player0.x_velocity - player1.x_velocity) * (player0.x_velocity - player1.x_velocity) / ACCELARATE) x_flag = 1;
//   else x_flag = 0;
//   if (delta_y < (player0.y_velocity - player1.y_velocity) * (player0.y_velocity - player1.y_velocity) / ACCELARATE) y_flag = 1;
//   else y_flag = 0;
//   if (x_flag && y_flag) {
//     int x_move, y_move;
//     if (player.x == player0.x && player.y == player0.y) {
//       if (player.x_velocity - player1.x_velocity > 0) x_move = -1;
//       else x_move = 1;
//     }
//     else {
//       if (player.x_velocity - player0.x_velocity > 0) x_move = -1;
//       else x_move = 1;
//     }
//     if (player.x == player0.x && player.y == player0.y) {
//       if (player.y_velocity - player1.y_velocity > 0) y_move = -1;
//       else y_move = 1;
//     }
//     else {
//       if (player.y_velocity - player0.y_velocity > 0) y_move = -1;
//       else y_move = 1;
//     }
//     if (x_move == 1 && y_move == 1) return { true, "RD" };
//     if (x_move == 1 && y_move == -1) return { true, "RU" };
//     if (x_move == -1 && y_move == 1) return { true, "LD" };
//     if (x_move == -1 && y_move == -1) return { true, "LU" };
//     assert(0);
//   }
//   else return { false, " " };
// }

location set_dest_location(location dst) {
  if (dst.x == 0) return { dst.x + 1.5, dst.y + 0.5 };
  if (dst.y == 0) return { dst.x + 0.5, dst.y + 1.5 };
  if (dst.x == width - 1) return { dst.x - 0.5, dst.y + 0.5 };
  if (dst.y == height - 1) return { dst.x + 0.5, dst.y - 0.5 };
  assert(0);
}

bool check_arive(location src, location dst) {
  // bool flag1 = manhattan_distance(src, dst) <= 1.5;
  bool flag2 = std::fabs(DELTA_X(src, dst)) <= LIMIT_RANGE && std::fabs(DELTA_Y(src, dst)) <= LIMIT_RANGE;
  return true && flag2;
}

struct int_loc {
  int x, y;
  int_loc(int _x = 0, int _y = 0): x(_x), y(_y) {}
  operator std::pair<int, int>() const {
    return std::pair<int, int>(x, y);
  }
  bool operator < (const int_loc& b) const {
    return x != b.x ? x < b.x : y < b.y;
  }
  int_loc operator [](int direction) const {
    return int_loc(x + dx[direction], y + dy[direction]);
  }
  int get_value() const {
    return ValueMap[x][y];
  }
  bool isvalid() const {
    return x < N && y < N && x >= 0 && y >= 0;
  }
};

struct Node {
  int_loc pos;
  int score;
  Node(int_loc _pos = int_loc(), int _score = 0): pos(_pos), score(_score) {}
  bool operator < (const Node& b) const {
    return score < b.score;
  }
};

std::priority_queue <Node> spfa_pq;
std::map <int_loc, int> dist;

int get_shortest_path(int_loc from, int_loc dest) {


  dist.clear();
  while (!spfa_pq.empty()) spfa_pq.pop();

  dist[from] = from.get_value();
  spfa_pq.push(Node(from, dist[from]));

  while (!spfa_pq.empty()) {
    Node now_node = spfa_pq.top();
    spfa_pq.pop();
    if (now_node.score > dist[now_node.pos])
      continue;
    if (now_node.pos.x == dest.x && now_node.pos.y == dest.y) {
      // std::cerr << "Cycle Count " << cnt << " " << std::endl;
      return dist[now_node.pos];
    }
    int_loc now_pos = now_node.pos;
    for (int direction = 0; direction < Direction_N; direction++) {
      if (!now_pos[direction].isvalid())
        continue;
      if (dist.find(now_pos[direction]) == dist.end() || dist[now_pos[direction]] < dist[now_pos] + now_pos.get_value()) {
        dist[now_pos[direction]] = dist[now_pos] + now_pos.get_value();
        spfa_pq.push(Node(now_pos[direction], dist[now_pos[direction]]));
      }
    }
  }

  // std::cerr << "Cycle Count " << cnt << " " << std::endl;
  return dist[dest];
}

Direction find_best_direction(int src_x, int src_y, int dst_x, int dst_y) {
  if (src_x == dst_x && src_y == dst_y)
    return Direction_N;
  Direction res_direction = Direction_N;
  int max_score = INT_MIN;
  for (int dir = 0; dir < Direction_N; dir++) {
    int res = get_shortest_path(int_loc(src_x, src_y)[dir], int_loc(dst_x, dst_y));
    if (res > max_score) {
      max_score = res;
      res_direction = (Direction)dir;
    }
  }
  return res_direction;
}


std::string move_towards(location src, location dst) {
  // return "LU";

  int src_x = (int)src.x, src_y = (int)src.y;
  int dst_x = (int)dst.x, dst_y = (int)dst.y;

  // std::cerr << "src:" << src.x << " " << src.y << std::endl;
  // std::cerr << "dst:" << dst.x << " " << dst.y << std::endl;

  // std::cerr << "here" << std::endl;

  // double delta_x = DELTA_X(src, dst), delta_y = DELTA_Y(src, dst);
  // int x_flag, y_flag;
  // if (std::fabs(delta_x) <= LIMIT_RANGE) x_flag = 0;
  // else if (delta_x > LIMIT_RANGE) x_flag = 1;
  // else x_flag = -1;
  // if (std::fabs(delta_y) <= LIMIT_RANGE) y_flag = 0;
  // else if (delta_y > LIMIT_RANGE) y_flag = 1;
  // else y_flag = -1;
  // if (x_flag == 1 && y_flag == 1) return "RD";
  // if (x_flag == -1 && y_flag == 1) return "LD";
  // if (x_flag == 1 && y_flag == -1) return "RU";
  // if (x_flag == -1 && y_flag == -1) return "LU";
  // if (x_flag == 0 && y_flag == 1) return "D";
  // if (x_flag == 0 && y_flag == -1) return "U";
  // if (x_flag == 1 && y_flag == 0) return "R";
  // if (x_flag == -1 && y_flag == 0) return "L";

  std::string res_name = direction_name[find_best_direction(src_x, src_y, dst_x, dst_y)];
  // fprintf(stderr, "%s\n", res_name.c_str());

  return res_name;
}

std::pair<bool, std::string> move_and_put_or_pick(Player player, std::string dest) {
  if (LUT.find(dest) == LUT.end() && map.find(dest) == map.end()) {
    return { true, " " };
  }


  assert(LUT.find(dest) != LUT.end() || map.find(dest) != map.end());
  location dst_set_location, dst_location, src_location = { player.x, player.y };
  if (LUT.find(dest) != LUT.end()) {
    dst_location = *LUT.find(dest)->second.begin();
    dst_set_location = set_dest_location(dst_location);
  }
  else {
    dst_location = *map.find(dest)->second.begin();
    dst_set_location = set_dest_location(dst_location);
  }
  // std::cerr << "src:" << src_location.x << " " << src_location.y << std::endl;
  // std::cerr << "dst:" << dst_location.x << " " << dst_location.y << std::endl;
  if (check_arive(src_location, dst_set_location)) {
    if (dst_location.y == 0) return { false, "U" };
    if (dst_location.y == height - 1) return { false, "D" };
    if (dst_location.x == 0) return { false, "L" };
    if (dst_location.x == width - 1) return { false, "R" };
    assert(0);
  }
  else {
    evaluate_map(player);
    auto move = move_towards(src_location, dst_set_location);
    auto rc = alert_dest(player, dst_set_location);
    if (rc.first) return { true, " " };
    if (move == " ") {
      if (dst_location.x == 0 || dst_location.x == width - 1) {
        if (src_location.y > dst_set_location.y) return { true, "D" };
        else return { true, "U" };
      }
      if (dst_location.y == 0 || dst_location.y == height - 1) {
        if (src_location.x > dst_set_location.x) return { true, "R" };
        else return { true, "L" };
      };
    }
    return { true, move };
  }
}






std::pair<bool, std::string> interact(Player player, std::string object) {
  location sink_location = *LUT.find("sink")->second.begin();
  if (map.find("DirtyPlates") == map.end()) return { false, " " };
  for (auto it : map.find("DirtyPlates")->second) {
    location plate_location = it;
    if (plate_location.x == sink_location.x && plate_location.y == sink_location.y) {
      if (sink_location.y == 0) return { true, "U" };
      if (sink_location.y == height - 1) return { true, "D" };
      if (sink_location.x == 0) return { true, "L" };
      if (sink_location.x == width - 1) return { true, "R" };
      assert(0);
    }
  }
  return { false, " " };
}





// std::pair<bool, std::string> put_or_pick(Player player, std::string object) {
//   if (player.container == Container::Plate && object == "Plate") return { false, "" };
//   if (player.container == Container::None && object == "service_window") return { false, "" };
//   for (int i = 0; i < player.entity.size(); i++) {
//     if (player.entity[i] == object) return { false, "" };
//   }
//   if (LUT.find(object) == LUT.end() && map.find(object) == map.end()) {
//     return { false, "" };
//   }
//   assert(LUT.find(object) != LUT.end() || map.find(object) != map.end());
//   location dst_location, src_location = { player.x, player.y };
//   if (LUT.find(object) != LUT.end()) dst_location = *LUT.find(object)->second.begin();
//   else dst_location = *map.find(object)->second.begin();
//   if (std::fabs(DELTA_X(src_location, dst_location)) <= LIMIT_RANGE) {
//     if (src_location.y > dst_location.y) return { true, "U" };
//     else return { true, "D" };
//   }
//   if (std::fabs(DELTA_Y(src_location, dst_location)) <= LIMIT_RANGE) {
//     if (src_location.x > dst_location.x) return { true, "L" };
//     else return { true, "R" };
//   }
//   assert(0);
// }