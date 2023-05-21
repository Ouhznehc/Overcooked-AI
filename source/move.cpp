#include <move.h>

static int ValueMap[N][N];
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


void evaluate_map(int id) {
  memset(ValueMap, 0, sizeof(ValueMap));
  int player_x, player_y, cliff_x, cliff_y;
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      if (map[x][y] == '.') ValueMap[x][y] += -1;
      else ValueMap[x][y] += -inf;
      if (map[x][y] == '_') {
        cliff_x = x;
        cliff_y = y;
      }
    }
  }
  player_x = (int)player[id].src.x;
  player_y = (int)player[id].src.y;

  ValueMap[player_x][player_y] += -inf;
  ValueMap[cliff_x][cliff_y] += -inf;
  for (int i = 0; i < 9; i++) {
    ValueMap[player_x + dx[i]][player_y + dy[i]] += -inf;
    ValueMap[cliff_x + dx[i]][cliff_y + dy[i]] += -inf;
  }
}

std::pair<bool, std::string> alert_dest(int id, Location dst) {
  double delta_x = dst.x - player[id].src.x;
  double delta_y = dst.y - player[id].src.y;
  bool x_flag, y_flag;
  if (delta_x > 0 && player[id].x_velocity > 0) {
    if (delta_x < player[id].x_velocity * player[id].x_velocity / ACCELARATE) x_flag = 1;
    else x_flag = 0;
  }
  else if (delta_x < 0 && player[id].x_velocity < 0) {
    if (-delta_x < player[id].x_velocity * player[id].x_velocity / ACCELARATE) x_flag = 1;
    else x_flag = 0;
  }
  if (delta_y > 0 && player[id].y_velocity > 0) {
    if (delta_y < player[id].y_velocity * player[id].y_velocity / ACCELARATE) y_flag = 1;
    else y_flag = 0;
  }
  else if (delta_y < 0 && player[id].y_velocity < 0) {
    if (-delta_y < player[id].y_velocity * player[id].y_velocity / ACCELARATE) y_flag = 1;
    else y_flag = 0;
  }
  if (x_flag || y_flag) {
    if (x_flag && y_flag) return { true, " " };
    else if (x_flag) {
      if (player[id].x_velocity > 0) {
        if (dst.y > player[id].src.y) return { true, "LD" };
        else return { true, "LU" };

        if (dst.y > player[id].src.y) return { true, "RD" };
        else return { true, "RU" };
      }
    }
    else if (y_flag) {
      if (player[id].y_velocity > 0) {
        if (dst.x > player[id].src.x) return { true, "RU" };
        else return { true, "LU" };
      }
      else {
        if (dst.x > player[id].src.x) return { true, "RD" };
        else return { true, "LD" };
      }
    }
    else return { false, " " };
  }
  else return { false, " " };
  return { false, " " };
}

struct int_loc {
  int x, y;
  int_loc(int _x = 0, int _y = 0) : x(_x), y(_y) {}
  operator std::pair<int, int>() const {
    return std::pair<int, int>(x, y);
  }
  bool operator < (const int_loc& b) const {
    return x != b.x ? x < b.x : y < b.y;
  }
  bool operator != (const int_loc& b) const {
    return x != b.x || y != b.y;
  }
  bool operator == (const int_loc& b) const {
    return !((*this) != b);
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
  Node(int_loc _pos = int_loc(), int _score = 0) : pos(_pos), score(_score) {}
  bool operator < (const Node& b) const {
    return score < b.score;
  }
};

std::priority_queue <Node> spfa_pq;
std::map <int_loc, int> dist;
std::map <int_loc, int_loc> frompoint;

int_loc get_shortest_path(int_loc from, int_loc dest) {

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
      goto end;
      return dist[now_node.pos];
    }
    int_loc now_pos = now_node.pos;
    for (int direction = 0; direction < Direction_N; direction++) {
      if (!now_pos[direction].isvalid())
        continue;
      if (dist.find(now_pos[direction]) == dist.end() || dist[now_pos[direction]] < dist[now_pos] + now_pos.get_value()) {
        dist[now_pos[direction]] = dist[now_pos] + now_pos.get_value();
        frompoint[now_pos[direction]] = now_pos;
        spfa_pq.push(Node(now_pos[direction], dist[now_pos[direction]]));
      }
    }
  }

end:
  // std::cerr << "Cycle Count " << cnt << " " << std::endl;
  int_loc nowp = dest;
  while (frompoint[nowp] != from) {
    nowp = frompoint[nowp];
  }
  return nowp;
}

Direction find_best_direction(int_loc src, int_loc dst) {
  if (src == dst)
    return Direction_N;
  int_loc nxtloc = get_shortest_path(src, dst);
  Direction res_direction = Direction_N;
  for (int dir = 0; dir < Direction_N; dir++)
    if (src[dir] == nxtloc) return (Direction)dir;
  return Direction_N;
}


std::string move_towards_spafa(Location src, Location dst) {

  int src_x = (int)src.x, src_y = (int)src.y;
  int dst_x = (int)dst.x, dst_y = (int)dst.y;

  std::string res_name = direction_name[find_best_direction(int_loc(src_x, src_y), int_loc(dst_x, dst_y))];

  return res_name;
}









static Location fetch_move_src(Location src) {
  return src;
}

static Location fetch_move_dst(Location dst) {
  if (dst.x == 0) return { dst.x + 1.5, dst.y + 0.5 };
  if (dst.x == width - 1) return { dst.x - 0.5, dst.y + 0.5 };
  if (dst.y == 0) return { dst.x + 0.5, dst.y + 1.5 };
  if (dst.y == height - 1) return { dst.x + 0.5, dst.y - 0.5 };
  assert(0);
}

static bool is_arive(Location src, Location dst, int id) {
  double hamilton_distance = std::fabs(src.x - dst.x) + std::fabs(src.y - dst.y);
  double hamilton_velocity = std::fabs(player[id].x_velocity) + std::fabs(player[id].y_velocity);
  return std::fabs(player[id].x_velocity) < 0.3 && std::fabs(player[id].y_velocity) < 0.3;
}

static std::string fetch_pick_direction(Location src, Location dst) {
  if (dst.x == 0) return "L";
  if (dst.x == width - 1) return "R";
  if (dst.y == 0) return "U";
  if (dst.y == height - 1) return "D";
  assert(0);
}

std::pair<bool, std::string> move_towards_by_location(Location src, Location dst, int id) {
  std::string move_direction = "";
  std::string pick_direction = "";
  Location move_src = fetch_move_src(src);
  Location move_dst = fetch_move_dst(dst);
  if (is_arive(move_src, move_dst, id)) {
    pick_direction = fetch_pick_direction(move_src, dst);
    return { false, "PutOrPick " + pick_direction };
  }
  else {
    evaluate_map(id);
    auto move = move_towards_spafa(move_src, move_dst);
    auto rc = alert_dest(id, move_dst);
    if (rc.first) return { true, rc.second };
    if (move == " ") {
      if (dst.x == 0 || dst.x == width - 1) {
        if (move_src.y > move_dst.y) return { true, "Move U" };
        else return { true, "Move D" };
      }
      if (dst.y == 0 || dst.y == height - 1) {
        if (move_src.x > move_dst.x) return { true, "Move L" };
        else return { true, "Move R" };
      };
    }
    return { true, "Move " + move };
  }

  return { true, "Move " + move_direction };
}

std::pair<bool, std::string> lazy_around_dog(Location src, Location dst, int id) {
  auto rc = move_towards_by_location(src, dst, id);
  if (rc.first) return { false, rc.second };
  else return { false, "Move " };
}