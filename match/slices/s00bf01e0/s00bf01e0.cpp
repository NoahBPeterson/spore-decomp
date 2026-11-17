// size() (0x00bf01e0): number of 4-byte elements in the vector at +0x9c.
#include "game/types.h"

struct Owner_bf01e0 {
    char mPad[0x9c];
    void** mpBegin;                           // +0x9c
    void** mpEnd;                             // +0xa0
    int size() const;
};

// @ 0x00bf01e0
int Owner_bf01e0::size() const
{
    return (int)(mpEnd - mpBegin);
}
