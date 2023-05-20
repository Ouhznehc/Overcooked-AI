#include <interact.h>
#include <move.h>

static std::string fetch_interact_direction(Location dst) {
  if (dst.x == 0) return "L";
  if (dst.x == width - 1) return "R";
  if (dst.y == 0) return "U";
  if (dst.y == height - 1) return "D";
  assert(0);
}

std::pair<bool, std::string> interact_with_object(Location src, Location dst, std::string object, std::vector<std::string> item, int id) {
  std::string interact_direction = fetch_interact_direction(dst);
  auto rc = move_towards_by_location(src, dst, id);
  if (rc.first) return rc;
  if (object == "Pot" || object == "Pan") return { false, "Interact " + interact_direction };
  for (int i = 0; i < entity_count; i++) {
    std::cerr << entity[i].item[0] << std::endl;
    if (entity[i].item[0] == object) {
      if (entity[i].current_frame == entity[i].total_frame - 1) return { false, "Interact " + interact_direction };
      else return { false, "Interact " + interact_direction };
    }
  }
  assert(0);
}