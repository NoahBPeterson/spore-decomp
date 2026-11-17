// size() (0x0062cb10): number of 4-byte elements in the vector at +0x3c.
#include "game/types.h"

struct Owner_62cb10 {
    char mPad[0x3c];
    void** mpBegin;                           // +0x3c
    void** mpEnd;                             // +0x40
    int size() const;
};

// @ 0x0062cb10
int Owner_62cb10::size() const
{
    return (int)(mpEnd - mpBegin);
}
