#include <bits/stdc++.h>
#include <common.h>
#include <enum.h>
#include <debug.h>
#include <IO_handle.h>
#include <task.h>


int main() {
    srand(time(0));
    std::ios::sync_with_stdio(false);
    std::cerr.tie(nullptr);
    std::cerr << std::nounitbuf;
    std::string s;
    std::stringstream ss;
    int frame;
    init_read();
    init();
    /*
        你可以在读入后进行一些相关预处理，时间限制：5秒钟
        init();
    */
    int totalFrame = 14400;
    for (int i = 0; i < totalFrame; i++) {
        bool skip = frame_read(i);
        if (skip) continue;
        if (Fund >= 200) continue;
        look_up_table();
        // for (auto it : map) {
        //     std::cerr << it.first << " " << it.second.begin()->x << " " << it.second.begin()->y << std::endl;
        // }
        /* 输出当前帧的操作，此处仅作示例 */
        std::cout << "Frame " << i << "\n";
        std::pair<std::string, std::string> strategy = allocate_task();
        std::string player0_Action = strategy.first;
        std::string player1_Action = strategy.second;
        /* 合成一个字符串再输出，否则输出有可能会被打断 */
        std::string action = player0_Action + "\n" + player1_Action + "\n";
        std::cout << action;

        /* 不要忘记刷新输出流，否则游戏将无法及时收到响应 */
        std::cout.flush();
    }
}
