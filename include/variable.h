#ifndef __VARIABLE_H__
#define __VARIABLE_H__

#include <enum.h>

#define N 25

/*======== map ========*/
extern int width;
extern int height;
extern char map[N][N];

/*======== ingredient ========*/
extern int ingredient_count;
extern Ingredient ingredient_box[N];

/*======== recipe ========*/
extern int recipe_count;
extern Recipe recipe[N];

/*======== order ========*/
extern int total_order_count;
extern int order_count;
extern Order total_order[N];
extern Order order[N];

/*======== common ========*/
extern int total_time;
extern int random_seed;
extern int remain_frame;
extern int fund;


/*======== entity ========*/
extern int entity_count;
extern Entity entity[N];



/*======== player ========*/
extern int player_count;
extern Player player[2];

/*======== LUT ========*/
extern std::map<std::string, std::vector<Location>> static_lut;
extern std::map<std::string, std::vector<Location>> dynamic_lut;
extern std::map <std::vector<std::string>, packed_task_t> order_lut;

#endif