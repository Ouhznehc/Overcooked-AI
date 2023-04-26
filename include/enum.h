#ifndef __ENUM_H__
#define __ENUM_H__

#include <common.h>

const int N = 20 + 5;

/* 按照读入顺序定义 */
int width, height;
char Map[N][N];
int IngredientCount;
struct Ingredient Ingredient[N];
int recipeCount;
struct Recipe Recipe[N];
int totalTime, randomizeSeed, totalOrderCount;
struct Order totalOrder[N];
int orderCount;
struct Order Order[N];
int k;
struct Player Players[2 + 5];
int entityCount;
struct Entity Entity[N];
int remainFrame, Fund;

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