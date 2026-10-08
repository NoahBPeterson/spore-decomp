// Slice s008b2250 -- cNibbleReader::ReadPacked (0x008b2b30, 174 bytes).
//
// Walks a nibble stream. State: a byte cursor plus a half flag (0 = byte-aligned, the next
// nibble is the high nibble of *cursor; 1 = high nibble consumed, the next is the low nibble).
// A value is a signed byte (two nibbles) times 16, plus one nibble (12 bits). If that value is
// in [-128, 127] (unsigned 16-bit (v + 0x80) <= 0xff), a second signed byte (two more nibbles)
// is appended as the low byte.
#include "types.h"

class cNibbleReader {
public:
    const uint8_t* mpCursor;   // +0x00
    uint16_t mHalf;            // +0x04

    uint16_t ReadPacked();     // 0x008b2b30 (thiscall, no args)
};

uint16_t cNibbleReader::ReadPacked() {
    uint16_t half = mHalf;
    const uint8_t* p;
    uint8_t b;
    if (half == 0) {
        p = mpCursor;
        b = *p;
        p = p + 1;
        mpCursor = p;
    } else {
        p = mpCursor;
        uint8_t a = *p;
        p = p + 1;
        mpCursor = p;
        b = (uint8_t)((a << 4) + (p[0] >> 4));
    }
    int32_t hi = (int8_t)b;
    uint16_t v;
    if (half == 0) {
        mHalf = 1;
        v = (uint16_t)(hi << 4);
        v = (uint16_t)(v + (p[0] >> 4));
    } else {
        mHalf = 0;
        v = (uint16_t)(hi << 4);
        v = (uint16_t)(v + (p[0] & 0xf));
        p = p + 1;
        mpCursor = p;
    }
    uint16_t result = v;
    if ((uint16_t)(v + 0x80) <= 0xff) {
        if (mHalf == 0) {
            int16_t lo = (int8_t)*mpCursor;
            mpCursor = mpCursor + 1;
            result = (uint16_t)((v << 8) + lo);
        } else {
            uint8_t a = mpCursor[0];
            mpCursor = mpCursor + 1;
            int16_t lo = (int8_t)((a << 4) + (mpCursor[0] >> 4));
            result = (uint16_t)((v << 8) + lo);
        }
    }
    return result;
}
