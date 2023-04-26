#ifndef __ENUM_H__
#define __ENUM_H__

#include <cassert>
#include <string>

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