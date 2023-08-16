#include "compress_texture.h"
#include <iostream>
#include <cstdint>

using namespace std;

int main()
{
    uint64_t compressCount = 0;
    uint64_t outCount = 0;
    while (true) {
        test_compress_texture();
        ++compressCount;
        if (++outCount >= 10000000) {
            outCount = 0;
            cout << "test_compress_texture compressCount:" << compressCount << endl;
        }
    }
    return 0;
}
