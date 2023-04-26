#ifndef __IO_HANDLE__
#define __IO_HANDLE__

/* 初始化时的读入。 */
void init_read();

/* 每一帧的读入；返回：是否跳帧。 */
bool frame_read(int now_frame);

#endif