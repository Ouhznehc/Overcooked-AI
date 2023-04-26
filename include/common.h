#ifndef __COMMON_H__
#define __COMMON_H__

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

#endif