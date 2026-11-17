// size() (0x00a14690): number of 4-byte elements in the vector at +0x8.
#include "game/types.h"

struct Owner_a14690 {
    char mPad[0x8];
    void** mpBegin;                           // +0x8
    void** mpEnd;                             // +0xc
    int size() const;
};

// @ 0x00a14690
int Owner_a14690::size() const
{
    return (int)(mpEnd - mpBegin);
}
