// size() (0x00837f30): number of 4-byte elements in the vector at +0x14.
#include "game/types.h"

struct Owner_837f30 {
    char mPad[0x14];
    void** mpBegin;                           // +0x14
    void** mpEnd;                             // +0x18
    int size() const;
};

// @ 0x00837f30
int Owner_837f30::size() const
{
    return (int)(mpEnd - mpBegin);
}
