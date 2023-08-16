#include "compress_texture.h"
#include <iostream>
#include <cstdint>

using namespace std;

int main()
{
    while (true) {
        static uint64_t compressCount = 0;
        static int32_t outCount = 0;
        for (int32_t i = 0; i < 1000; ++i) {
            test_compress_texture();
            ++compressCount;
        }
        if (++outCount >= 1000) {
            outCount = 0;
            cout << "test_compress_texture compressCount:" << compressCount << endl;
        }
    }
    return 0;
}
