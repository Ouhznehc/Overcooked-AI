#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <string>
#include <stdlib.h>
#include <framework.h>
#include <debug.h>

char* dir = "UDRL";
int main() {
    std::ios::sync_with_stdio(false);
    std::cerr.tie(nullptr);
    std::cerr << std::nounitbuf;
    std::string s;
    std::stringstream ss;
    int frame;
    init_read();

    /*
        你可以在读入后进行一些相关预处理，时间限制：5秒钟
        init();
    */

    int totalFrame = 14400;
    for (int i = 0; i < totalFrame; i++) {
        bool skip = frame_read(i);
        if (skip) continue;
        /* 输出当前帧的操作，此处仅作示例 */
        std::cout << "Frame " << i << "\n";
        int randnum0 = (rand() * rand()) % 4;
        int randnum1 = (rand() * rand()) % 4;
        std::string player0_Action = "Move " + dir[randnum0];
        std::string player1_Action = "Move " + dir[randnum1];

        /* 合成一个字符串再输出，否则输出有可能会被打断 */
        std::string action = player0_Action + "\n" + player1_Action + "\n";
        std::cout << action;

        /* 不要忘记刷新输出流，否则游戏将无法及时收到响应 */
        std::cout.flush();
    }
}
