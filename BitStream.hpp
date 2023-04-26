//
// Created by zichu on 2023/4/26.
//

#ifndef ALGRITHMHW_BITSTREAM_HPP
#define ALGRITHMHW_BITSTREAM_HPP

#include <iostream>
#include <queue>

using namespace std;

class BitStream {
private:
    queue<bool> stream;
    FILE *fin;
    int lastCodesCount;

    void _getNewByte();

public:
    BitStream(FILE *fin, int lastCodesCount) : fin(fin), lastCodesCount(lastCodesCount) { }

    bool getBit(bool &data);
};

#endif //ALGRITHMHW_BITSTREAM_HPP
