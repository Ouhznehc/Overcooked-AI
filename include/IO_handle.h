#ifndef __IO_HANDLE__
#define __IO_HANDLE__

#include <enum.h>
#include <bits/stdc++.h>

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


/* 初始化时的读入。 */
void init_read();

/* 每一帧的读入；返回：是否跳帧。 */
bool frame_read(int now_frame);

#endif