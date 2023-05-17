#include <variable.h>

/*======== map ========*/
int width;
int height;
char map[N][N];

/*======== ingredient ========*/
int ingredient_count;
Ingredient ingredient_box[N];

/*======== recipe ========*/
int recipe_count;
Recipe recipe[N];

/*======== order ========*/
int total_order_count;
int order_count;
Order total_order[N];
Order order[N];

/*======== common ========*/
int total_time;
int random_seed;
int remain_frame;
int fund;

/*======== entity ========*/
int entity_count;
Entity entity[N];

/*======== player ========*/
int player_count;
Player player[2];

/*======== LUT ========*/
std::map<std::string, std::vector<Location>> static_lut;
std::map<std::string, std::vector<Location>> dynamic_lut;