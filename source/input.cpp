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
        ss >> player[i].location.x >> player[i].location.y;
        player[i].entity.clear();
    }

    /* 读入实体信息：坐标、实体组成 */
    ss >> entity_count;
    for (int i = 0; i < entity_count; i++) {
        ss >> entity[i].location.x >> entity[i].location.y >> s;
        entity[i].entity.push_back(s);
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
        ss >> player[i].location.x >> player[i].location.y >> player[i].x_velocity >> player[i].y_velocity >> player[i].live;
        getline(ss, s);
        std::stringstream tmp(s);
        player[i].entity.clear();
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
            player[i].entity.push_back(s);
        }
    }

    ss >> entity_count;
    /* 读入实体坐标 */
    for (int i = 0; i < entity_count; i++) {
        ss >> entity[i].location.x >> entity[i].location.y;
        getline(ss, s);
        std::stringstream tmp(s);
        entity[i].entity.clear();
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
            entity[i].entity.push_back(s);
        }
    }
    return false;
}

static void update_static_lut() {
    static_lut.clear();
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            switch (map[i][j]) {
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

void init() {

    update_static_lut();

}