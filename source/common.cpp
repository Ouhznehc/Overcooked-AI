#include <enum.h>
#include <common.h>


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

