#include "sbus.h"

namespace nokolat{
    void SBUS::decode(std::array<uint8_t,25> &arg, SBUS_DATA &res){
         if(arg.at(0) == HEADER &&
        (arg.at(24) == FOOTER || arg.at(24)&0x0F == FOOTER2)){

            res.at(0) = arg.at(1);
            res.at(0) += ((int16_t)arg.at(2) & 0b111)<<8;

            res.at(1) = arg.at(2)>>3;
            res.at(1) += ((int16_t)arg.at(3) & 0b111111)<<5;

            res.at(2) = arg.at(3)>>6;
            res.at(2) += ((int16_t)arg.at(4))<<2;
            res.at(2) += ((int16_t)arg.at(5) & 0b1)<<10;

            res.at(3) = arg.at(5)>>1;
            res.at(3) += ((int16_t)arg.at(6) & 0b1111)<<7;

            res.at(4) = arg.at(6)>>4;
            res.at(4) += ((int16_t)arg.at(7) & 0b1111111)<<4;

            res.at(5) = arg.at(7)>>7;
            res.at(5) += ((int16_t)arg.at(8))<<1;
            res.at(5) += ((int16_t)arg.at(9) & 0b11)<<9;

            res.at(6) = arg.at(9)>>2;
            res.at(6) += ((int16_t)arg.at(10) & 0b11111)<<6;

            res.at(7) = arg.at(10)>>5;
            res.at(7) += ((int16_t)arg.at(11))<<3;

            res.at(8) = arg.at(12);
            res.at(8) += ((int16_t)arg.at(13) & 0b111)<<8;

            res.at(9) = arg.at(13)>>3;
            res.at(9) += ((int16_t)arg.at(14) & 0b111111)<<8;

            res.at(10) = arg.at(14)>>6;
            res.at(10) += ((int16_t)arg.at(15))<<2;
            res.at(10) += ((int16_t)arg.at(16) & 0b1)<<10;

            res.at(11) = arg.at(16)>>1;
            res.at(11) += ((int16_t)arg.at(17) & 0b1111)<<7;

            res.at(12) = arg.at(17)>>4;
            res.at(12) += ((int16_t)arg.at(18) & 0b1111111)<<4;

            res.at(13) = arg.at(18)>>7;
            res.at(13) += ((int16_t)arg.at(19))<<1;
            res.at(13) += ((int16_t)arg.at(20) & 0b11)<<9;

            res.at(14) = arg.at(20)>>2;
            res.at(14) += ((int16_t)arg.at(21) & 0b11111)<<6;

            res.at(15) = arg.at(21)>>5;
            res.at(15) += ((int16_t)arg.at(22))<<3;

            res.at(16) = arg.at(23) &0b1;
            res.at(17) = (arg.at(23) &0b10)>>1;

            res.framelost = (arg.at(23)&0b100)>>2;
            res.failsafe = (arg.at(23)&0b1000)>>3;
        }
    }


    SBUS_DATA SBUS::decode(std::array<uint8_t,25> arg){
        SBUS_DATA res;
        decode(arg,res);
        return res;
    }

    std::array<uint8_t,25> SBUS::encode(SBUS_DATA arg){
        std::array<uint8_t,25> res;

        res.at(0) = HEADER;

        res.at(1) = arg.at(0)&0xff;
        res.at(2) = (arg.at(0)>>8 & 0b111) & (arg.at(1)<<3 & 0b11111000);
        res.at(3) = (arg.at(1)>>5 & 0b111111) & (arg.at(2)<<6 & 0b11000000);
        res.at(4) = (arg.at(2)>>2 & 0b11111111);
        res.at(5) = (arg.at(2)>>10 & 0b1) & (arg.at(3)<<1 & 0b11111110);
        res.at(6) = (arg.at(3)>>7 & 0b1111) & (arg.at(4)<<4 & 0b11110000);
        res.at(7) = (arg.at(4)>>4 & 0b1111111) & (arg.at(5)<<7 & 0b10000000);
        res.at(8) = (arg.at(5)>>1 & 0xff);
        res.at(9) = (arg.at(5)>>9 & 0b11) & (arg.at(6)<<2 & 0b11111100);
        res.at(10) = (arg.at(6)>>6 & 0b11111) & (arg.at(7)<<5 & 0b11100000);
        res.at(11) = (arg.at(7)>>3 & 0xff);

        res.at(12) = arg.at(8)&0xff;
        res.at(13) = (arg.at(8)>>8 & 0b111) & (arg.at(9)<<3 & 0b11111000);
        res.at(14) = (arg.at(9)>>5 & 0b111111) & (arg.at(10)<<6 & 0b11000000);
        res.at(15) = (arg.at(10)>>2 & 0b11111111);
        res.at(16) = (arg.at(10)>>10 & 0b1) & (arg.at(11)<<1 & 0b11111110);
        res.at(17) = (arg.at(11)>>7 & 0b1111) & (arg.at(12)<<4 & 0b11110000);
        res.at(16) = (arg.at(12)>>4 & 0b1111111) & (arg.at(13)<<7 & 0b10000000);
        res.at(19) = (arg.at(13)>>1 & 0xff);
        res.at(20) = (arg.at(13)>>9 & 0b11) & (arg.at(14)<<2 & 0b11111100);
        res.at(21) = (arg.at(14)>>6 & 0b11111) & (arg.at(15)<<5 & 0b11100000);
        res.at(22) = (arg.at(15)>>3 & 0xff);

        res.at(23) = (arg.at(16) & 0b1) & (arg.at(17)<<1 & 0b10);
        res.at(23) = (uint8_t)arg.flameLost << 2
        res.at(23) = (uint8_t)arg.failsafe << 3;
        res.at(24) = FOOTER;
    }
}