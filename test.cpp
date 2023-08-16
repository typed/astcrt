#include "compress_texture.h"
#include <iostream>
#include <cstdint>
#include <time.h>

using namespace std;

int main()
{
    uint64_t compressCount = 0;
    time_t lastTime = time(0);
    while (true) {
        test_compress_texture();
        ++compressCount;
        time_t nowTime = time(0);
        if (nowTime > lastTime) {
            lastTime = nowTime;
            cout << "test_compress_texture compressCount:" << compressCount << "\r";
        }
    }
    return 0;
}
