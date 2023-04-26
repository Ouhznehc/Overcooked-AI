#ifndef __IO_HANDLE__
#define __IO_HANDLE__

#include <enum.h>
#include <common.h>
#include <bits/stdc++.h>

extern const int N = 20 + 5;

/* 按照读入顺序定义 */
extern int width, height;
extern char Map[N][N];
extern int IngredientCount;
extern struct Ingredient Ingredient[N];
extern int recipeCount;
extern struct Recipe Recipe[N];
extern int totalTime, randomizeSeed, totalOrderCount;
extern struct Order totalOrder[N];
extern int orderCount;
extern struct Order Order[N];
extern int k;
extern struct Player Players[2 + 5];
extern int entityCount;
extern struct Entity Entity[N];
extern int remainFrame, Fund;


/* 初始化时的读入。 */
void init_read();

/* 每一帧的读入；返回：是否跳帧。 */
bool frame_read(int now_frame);

#endif