//
// Created by raphael on 23/09/18.
//

#ifndef CLIENT_OPUS_H
#define CLIENT_OPUS_H

#define MAX_PACKET_SIZE 2048
#define APPLICATION OPUS_APPLICATION_VOIP

#include "../sound/Config.hpp"

#include <opus.h>
#include <vector>
#include <memory>
#include <iostream>

class Opus {
public:
    Opus();
    ~Opus();

    std::tuple<unsigned char *, int>    encode(const std::vector<SAMPLE> &values);
    std::vector<SAMPLE> decode(const std::tuple<unsigned char *, int> &values);
private:
    OpusDecoder *_decoder;
    OpusEncoder *_encoder;
};


#endif //CLIENT_OPUS_H