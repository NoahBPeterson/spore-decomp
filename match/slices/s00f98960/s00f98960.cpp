// size() (0x00f98960): number of 4-byte elements in the vector at +0x2b8.
#include "game/types.h"

struct Owner_f98960 {
    char mPad[0x2b8];
    void** mpBegin;                           // +0x2b8
    void** mpEnd;                             // +0x2bc
    int size() const;
};

// @ 0x00f98960
int Owner_f98960::size() const
{
    return (int)(mpEnd - mpBegin);
}
