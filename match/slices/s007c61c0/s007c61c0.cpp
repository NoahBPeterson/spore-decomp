// size() (0x007c61c0): number of 4-byte elements in the vector at +0x80.
#include "game/types.h"

struct Owner_7c61c0 {
    char mPad[0x80];
    void** mpBegin;                           // +0x80
    void** mpEnd;                             // +0x84
    int size() const;
};

// @ 0x007c61c0
int Owner_7c61c0::size() const
{
    return (int)(mpEnd - mpBegin);
}
