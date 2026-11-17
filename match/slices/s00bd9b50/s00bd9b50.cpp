// size() (0x00bd9b50): number of 4-byte elements in the vector at +0x340.
#include "game/types.h"

struct Owner_bd9b50 {
    char mPad[0x340];
    void** mpBegin;                           // +0x340
    void** mpEnd;                             // +0x344
    int size() const;
};

// @ 0x00bd9b50
int Owner_bd9b50::size() const
{
    return (int)(mpEnd - mpBegin);
}
