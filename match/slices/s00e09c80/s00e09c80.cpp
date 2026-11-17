// size() (0x00e09c80): number of 4-byte elements in the vector at +0x18.
#include "game/types.h"

struct Owner_e09c80 {
    char mPad[0x18];
    void** mpBegin;                           // +0x18
    void** mpEnd;                             // +0x1c
    int size() const;
};

// @ 0x00e09c80
int Owner_e09c80::size() const
{
    return (int)(mpEnd - mpBegin);
}
