// size() (0x00bd9b60): number of 4-byte elements in the vector at +0x354.
#include "game/types.h"

struct Owner_bd9b60 {
    char mPad[0x354];
    void** mpBegin;                           // +0x354
    void** mpEnd;                             // +0x358
    int size() const;
};

// @ 0x00bd9b60
int Owner_bd9b60::size() const
{
    return (int)(mpEnd - mpBegin);
}
