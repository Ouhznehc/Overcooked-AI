#ifndef __INPUT_H__
#define __INPUT_H__

#include <variable.h>
#include <schedule.h>
/* 初始化时的读入。 */
void init_read();

/* 每一帧的读入；返回：是否跳帧。 */
bool frame_read(int now_frame);

void init();

void update_dynamic_lut();

#endif