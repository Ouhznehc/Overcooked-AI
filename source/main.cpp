#include <variable.h>
#include <schedule.h>
#include <input.h>

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
    assert(0);
    /*
        你可以在读入后进行一些相关预处理，时间限制：5秒钟
        init();
    */
    int totalFrame = 14400;
    for (int i = 0; i < totalFrame; i++) {
        bool skip = frame_read(i);
        if (skip) continue;
        update_dynamic_lut();
        /* 输出当前帧的操作，此处仅作示例 */
        std::cout << "Frame " << i << "\n";
        auto action = schedule_task();
        auto player0_action = action.first;
        auto player1_action = action.second;
        /* 合成一个字符串再输出，否则输出有可能会被打断 */
        std::string output = player0_action + "\n" + player1_action + "\n";
        std::cout << output;

        /* 不要忘记刷新输出流，否则游戏将无法及时收到响应 */
        std::cout.flush();
        std::cerr.flush();
    }
}
