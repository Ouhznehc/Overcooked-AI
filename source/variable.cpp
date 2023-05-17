#include <variable.h>

/*======== map ========*/
int width;
int height;
char map[N][N];

/*======== ingredient ========*/
int ingredient_count;
ingredient_t ingredient_box[N];

/*======== recipe ========*/
int recipe_count;
recipe_t recipe[N];

/*======== order ========*/
int total_order_count;
int order_count;
order_t total_order[N];
order_t order[N];

/*======== common ========*/
int total_time;
int random_seed;
int remain_frame;
int fund;

/*======== entity ========*/
int entity_count;
entity_t entity[N];

/*======== player ========*/
int player_count;
player_t player[2];

/*======== LUT ========*/
std::map<std::string, std::vector<Location>> static_lut;
std::map<std::string, std::vector<Location>> dynamic_lut;