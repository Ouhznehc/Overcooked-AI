#ifndef __ENUM_H__
#define __ENUM_H__

#include <bits/stdc++.h>

struct Ingredient {
    int x, y, price; // 坐标以及花费
    std::string name;// 原料名称
};

struct Recipe {
    int time; // 加工耗时
    std::string name_before, name_after; // 加工前后名称
    std::string kind; // 加工容器
};

struct Order {
    int valid_frame; // 消失帧
    int price; // 收益
    int frequency; // 出现频率
    std::vector<std::string> recipe; // 需要食材
};

struct Player {
    double x, y; // 坐标
    double x_velocity; // 速度
    double y_velocity;
    int live;// 复活倒计时时间， 0表示存活
    Container container; // 手持容器
    std::vector<std::string> entity; // 手持实体
};

struct Entity {
    double x, y; // 实体坐标
    Container container;// 实体上的容器
    std::vector<std::string> entity; // 实体上的的实体
    int current_frame, total_frame; // 容器加工进度
    int sum; // 特指脏盘子数量
};

enum class Container {
    None,
    Pan,
    Pot,
    Plate,
    DirtyPlates,
};

enum class Tile {
    None,
    Void,
    Floor,
    Wall,
    Table,
    IngredientBox,
    Trashbin,
    ChoppingStation,
    ServiceWindow,
    Stove,
    PlateReturn,
    Sink,
    PlateRack,
};

inline Tile fetch_tile_kind(char kindChar) {
    switch (kindChar) {
    case '_':
        return Tile::Void;
    case '.':
        return Tile::Floor;
    case '*':
        return Tile::Table;
    case 't':
        return Tile::Trashbin;
    case 'c':
        return Tile::ChoppingStation;
    case '$':
        return Tile::ServiceWindow;
    case 's':
        return Tile::Stove;
    case 'p':
        return Tile::PlateReturn;
    case 'k':
        return Tile::Sink;
    case 'r':
        return Tile::PlateRack;
    default:
        assert(0);
    }
}

// inline char getAbbrev(Tile kind) {
//     switch (kind) {
//     case Tile::IngredientBox:
//         return 'i';
//     case Tile::Trashbin:
//         return 't';
//     case Tile::ChoppingStation:
//         return 'c';
//     case Tile::ServiceWindow:
//         return '$';
//     case Tile::Stove:
//         return 's';
//     case Tile::PlateReturn:
//         return 'p';
//     case Tile::Sink:
//         return 'k';
//     case Tile::PlateRack:
//         return 'r';
//     default:
//         assert(0);
//     }
// }

#endif