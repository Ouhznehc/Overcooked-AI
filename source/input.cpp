#include <input.h>

void init_read() {
    std::string s;
    std::stringstream ss;
    int frame;

    /* 读取初始地图信息 */
    std::getline(std::cin, s, '\0');
    ss << s;

    /* 若按照该读入，访问坐标(x, y)等价于访问Map[y][x],你可按照自己的习惯进行修改 */
    ss >> width >> height;
    std::cerr << "Map size: " << width << "x" << height << std::endl;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            ss >> map[j][i];

    /* 读入原料箱：位置、名字、以及采购单价 */
    ss >> ingredient_count;
    for (int i = 0; i < ingredient_count; i++) {
        ss >> s;
        assert(s == "IngredientBox");
        ss >> ingredient_box[i].location.x >> ingredient_box[i].location.y >> ingredient_box[i].name >> ingredient_box[i].price;
    }

    /* 读入配方：加工时间、加工前的字符串表示、加工容器、加工后的字符串表示 */
    ss >> recipe_count;
    for (int i = 0; i < recipe_count; i++) {
        ss >> recipe[i].time >> recipe[i].name_before >> recipe[i].kind >> recipe[i].name_after;
    }

    /* 读入总帧数、当前采用的随机种子、一共可能出现的订单数量 */
    ss >> total_time >> random_seed >> total_order_count;

    /* 读入订单的有效帧数、价格、权重、订单组成 */
    for (int i = 0; i < total_order_count; i++) {
        ss >> total_order[i].valid_frame >> total_order[i].price >> total_order[i].frequency;
        getline(ss, s);
        std::stringstream tmp(s);
        while (tmp >> s)
            total_order[i].recipe.push_back(s);
    }

    /* 读入玩家信息：初始坐标 */
    ss >> player_count;
    assert(player_count == 2);
    for (int i = 0; i < player_count; i++) {
        ss >> player[i].src.x >> player[i].src.y;
        player[i].item.clear();
    }

    /* 读入实体信息：坐标、实体组成 */
    ss >> entity_count;
    for (int i = 0; i < entity_count; i++) {
        ss >> entity[i].location.x >> entity[i].location.y >> s;
        entity[i].item.push_back(s);
    }
}

bool frame_read(int now_frame) {
    std::string s;
    std::stringstream ss;
    int frame;
    std::getline(std::cin, s, '\0');
    ss.str(s);
    /*
      如果输入流中还有数据，说明游戏已经在请求下一帧了
      这时候我们应该跳过当前帧，以便能够及时响应游戏。
    */
    if (std::cin.rdbuf()->in_avail() > 0) {
        std::cerr << "Warning: skipping frame " << now_frame
            << " to catch up with the game" << std::endl;
        return true;
    }
    ss >> s;
    assert(s == "Frame");
    int current_frame;
    ss >> current_frame;
    assert(current_frame == now_frame);
    ss >> remain_frame >> fund;
    /* 读入当前的订单剩余帧数、价格、以及配方 */
    ss >> order_count;
    for (int i = 0; i < order_count; i++) {
        ss >> order[i].valid_frame >> order[i].price;
        order[i].recipe.clear();
        getline(ss, s);
        std::stringstream tmp(s);
        while (tmp >> s) {
            order[i].recipe.push_back(s);
        }
    }
    ss >> player_count;
    assert(player_count == 2);
    /* 读入玩家坐标、x方向速度、y方向速度、剩余复活时间 */
    for (int i = 0; i < player_count; i++) {
        ss >> player[i].src.x >> player[i].src.y >> player[i].x_velocity >> player[i].y_velocity >> player[i].live;
        getline(ss, s);
        std::stringstream tmp(s);
        player[i].item.clear();
        while (tmp >> s) {
            /*
                若若该玩家手里有东西，则接下来一个分号，分号后一个空格，空格后为一个实体。
                以下是可能的输入（省略前面的输入）：
                 ;  : fish
                 ; @  : fish
                 ; @ Plate : fish
                 ; Plate
                 ; DirtyPlates 1
                ...
            */

            /* 若你不需要处理这些，可直接忽略 */
            if (s == ";" || s == ":" || s == "@" || s == "*")
                continue;
            player[i].item.push_back(s);
        }
    }

    ss >> entity_count;
    /* 读入实体坐标 */
    for (int i = 0; i < entity_count; i++) {
        ss >> entity[i].location.x >> entity[i].location.y;
        getline(ss, s);
        std::stringstream tmp(s);
        entity[i].item.clear();
        entity[i].current_frame = entity[i].total_frame = 0;
        entity[i].sum = 1;
        while (tmp >> s) {
            /*
                读入一个实体，例子：
                DirtyPlates 2
                fish
                DirtyPlates 1 ; 15 / 180

            */

            /* 若你不需要处理这些，可直接忽略 */
            if (s == ":" || s == "@" || s == "*")
                continue;
            if (s == ";") {
                tmp >> entity[i].current_frame >> s >> entity[i].total_frame;
                assert(s == "/");
                break;
            }
            if (s == "DirtyPlates")
                tmp >> entity[i].sum;
            entity[i].item.push_back(s);
        }
    }
    return false;
}

static void update_static_lut() {
    static_lut.clear();
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            switch (map[i][j]) {
            case 's': static_lut["hot"].push_back(Location(i, j)); break;
            case 'c': static_lut["Chop"].push_back(Location(i, j)); break;
            case 'k': static_lut["sink"].push_back(Location(i, j)); break;
            case 'r': static_lut["clean_plate_location"].push_back(Location(i, j)); break;
            case 'p': static_lut["dirty_plate_location"].push_back(Location(i, j)); break;
            case '$': static_lut["service_window"].push_back(Location(i, j)); break;
            default:
                break;
            }
        }
    }
    for (int i = 0; i < ingredient_count; i++) {
        static_lut[ingredient_box[i].name].push_back(ingredient_box[i].location);
    }
}

static void update_order_lut() {
    for (int i = 0; i < total_order_count; i++) {
        std::vector<std::string> items;
        items.clear();
        packed_task_t packed_task;
        packed_task.clear();
        std::sort(total_order[i].recipe.begin(), total_order[i].recipe.end());
        for (auto recipe : total_order[i].recipe) {
            if (recipe == "fish" || recipe == "rice" || recipe == "kelp") {
                packed_task.push_back({ action::move_towards, recipe, {""} });
                packed_task.push_back({ action::move_towards, "Plate", items });
            }
            else if (recipe == "c_fish") {
                packed_task.push_back({ action::move_towards, "fish", {""} });
                packed_task.push_back({ action::move_towards, "Chop", {""} });
                packed_task.push_back({ action::interact_with, "Chop", {"fish"} });
                packed_task.push_back({ action::move_towards, "Chop", {"c_fish"} });
                packed_task.push_back({ action::move_towards, "Plate", items });
            }
            else if (recipe == "s_rice") {
                packed_task.push_back({ action::move_towards, "rice", {""} });
                packed_task.push_back({ action::move_towards, "Pot", {""} });
                packed_task.push_back({ action::interact_with, "Pot", {"rice" } });
                packed_task.push_back({ action::move_towards, "Pot", {"s_rice"} });
                packed_task.push_back({ action::move_towards, "Plate", items });
                packed_task.push_back({ action::move_towards, "hot", {""} });
            }
            else if (recipe == "s_fish") {
                packed_task.push_back({ action::move_towards, "fish", {""} });
                packed_task.push_back({ action::move_towards, "Chop", {""} });
                packed_task.push_back({ action::interact_with, "Chop", {"fish"} });
                packed_task.push_back({ action::move_towards, "Chop", {"c_fish"} });
                packed_task.push_back({ action::move_towards, "Pan", {""} });
                packed_task.push_back({ action::move_towards, "Pan", {"s_fish"} });
                packed_task.push_back({ action::move_towards, "Plate",  items });
                packed_task.push_back({ action::move_towards, "hot", {""} });
            }
            else {
                std::cerr << "Unknown Recipe" << std::endl;
                assert(0);
            }
            items.push_back(recipe);
        }
        assert(items == total_order[i].recipe);
        packed_task.push_back({ action::move_towards, "Plate", items });
        packed_task.push_back({ action::move_towards, "service_window", {""} });
        order_lut[total_order[i].recipe] = packed_task;
    }
    packed_task_t packed_task;
    packed_task.clear();
    packed_task.push_back({ action::move_towards, "dirty_plate_location", {""} });
    packed_task.push_back({ action::move_towards, "sink", {""} });
    packed_task.push_back({ action::interact_with, "sink", {"DirtyPlates"} });
    order_lut[{"wash_plates"}] = packed_task;

    packed_task.clear();
    packed_task.push_back({ action::lazy_around, "dirty_plate_location", {""} });
    order_lut[{"lazy_around"}] = packed_task;
}

void init() {
    update_static_lut();
    update_order_lut();
    cook_work.player = wash_work.player = player::null;
    cook_work.task_cnt = wash_work.task_cnt = -1;
    player[0].status = player[1].status = work_status::leisure;
}

void update_dynamic_lut() {
    dynamic_lut.clear();
    for (int i = 0; i < entity_count; i++) {
        for (auto it : entity[i].item) {
            dynamic_lut[it].push_back(entity[i].location);
        }
    }
    for (int i = 0; i < player_count; i++) {
        if (player[i].item.size()) player[i].status = work_status::busy;
    }
}
