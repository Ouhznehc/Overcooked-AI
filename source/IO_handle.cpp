#include <IO_handle.h>
#include <common.h>
#include <bits/stdc++.h>
#include <enum.h>

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
            ss >> Map[i][j];

    /* 读入原料箱：位置、名字、以及采购单价 */
    ss >> IngredientCount;
    for (int i = 0; i < IngredientCount; i++) {
        ss >> s;
        assert(s == "IngredientBox");
        ss >> Ingredient[i].x >> Ingredient[i].y >> Ingredient[i].name >> Ingredient[i].price;
    }

    /* 读入配方：加工时间、加工前的字符串表示、加工容器、加工后的字符串表示 */
    ss >> recipeCount;
    for (int i = 0; i < recipeCount; i++) {
        ss >> Recipe[i].time >> Recipe[i].name_before >> Recipe[i].kind >> Recipe[i].name_after;
    }

    /* 读入总帧数、当前采用的随机种子、一共可能出现的订单数量 */
    ss >> totalTime >> randomizeSeed >> totalOrderCount;

    /* 读入订单的有效帧数、价格、权重、订单组成 */
    for (int i = 0; i < totalOrderCount; i++) {
        ss >> totalOrder[i].valid_frame >> totalOrder[i].price >> totalOrder[i].frequency;
        getline(ss, s);
        std::stringstream tmp(s);
        while (tmp >> s)
            totalOrder[i].recipe.push_back(s);
    }

    /* 读入玩家信息：初始坐标 */
    ss >> k;
    assert(k == 2);
    for (int i = 0; i < k; i++) {
        ss >> Players[i].x >> Players[i].y;
        Players[i].container = Container::None;
        Players[i].entity.clear();
    }

    /* 读入实体信息：坐标、实体组成 */
    ss >> entityCount;
    for (int i = 0; i < entityCount; i++) {
        ss >> Entity[i].x >> Entity[i].y >> s;
        Entity[i].entity.push_back(s);
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
    int currentFrame;
    ss >> currentFrame;
    assert(currentFrame == now_frame);
    ss >> remainFrame >> Fund;
    /* 读入当前的订单剩余帧数、价格、以及配方 */
    ss >> orderCount;
    for (int i = 0; i < orderCount; i++) {
        ss >> Order[i].valid_frame >> Order[i].price;
        Order[i].recipe.clear();
        getline(ss, s);
        std::stringstream tmp(s);
        while (tmp >> s) {
            Order[i].recipe.push_back(s);
        }
    }
    ss >> k;
    assert(k == 2);
    /* 读入玩家坐标、x方向速度、y方向速度、剩余复活时间 */
    for (int i = 0; i < k; i++) {
        ss >> Players[i].x >> Players[i].y >> Players[i].x_velocity >> Players[i].y_velocity >> Players[i].live;
        getline(ss, s);
        std::stringstream tmp(s);
        Players[i].container = Container::None;
        Players[i].entity.clear();
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

            /*
                Todo: 其他容器
            */
            if (s == "Plate")
                Players[i].container = Container::Plate;
            else if (s == "DirtyPlates")
                Players[i].container = Container::DirtyPlates;
            else
                Players[i].entity.push_back(s);
        }
    }

    ss >> entityCount;
    /* 读入实体坐标 */
    for (int i = 0; i < entityCount; i++) {
        ss >> Entity[i].x >> Entity[i].y;
        getline(ss, s);
        std::stringstream tmp(s);
        Entity[i].container = Container::None;
        Entity[i].entity.clear();
        Entity[i].current_frame = Entity[i].total_frame = 0;
        Entity[i].sum = 1;
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
                tmp >> Entity[i].current_frame >> s >> Entity[i].total_frame;
                assert(s == "/");
                break;
            }

            /*
                Todo: 其他容器
            */
            if (s == "Plate")
                Entity[i].container = Container::Plate;
            else if (s == "DirtyPlates") {
                Entity[i].container = Container::DirtyPlates;
                tmp >> Entity[i].sum;
            }
            Entity[i].entity.push_back(s);
        }
    }
    return false;
}

void look_up_table() {
    map.clear();
    for (int i = 0; i < entityCount; i++) {
        for (int j = 0; j < Entity[i].entity.size(); j++) {
            map[Entity[i].entity[j]].push_back({ Entity[i].x, Entity[i].y });
        }
    }
}

void init() {
    LUT.clear();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            switch (Map[i][j]) {
            case 'k': LUT["sink"].push_back({ (double)j, (double)i }); break;
            case 'r': LUT["clean_plate_location"].push_back({ (double)j, (double)i }); break;
            case 'p': LUT["dirty_plate_location"].push_back({ (double)j, (double)i }); break;
            case '$': LUT["service_window"].push_back({ (double)j, (double)i }); break;
            default:
                break;
            }
        }
    }
    for (int i = 0; i < IngredientCount; i++) {
        LUT[Ingredient[i].name].push_back({ (double)Ingredient[i].x, (double)Ingredient[i].y });
    }
}