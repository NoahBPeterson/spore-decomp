// size() (0x009d0c80): number of 4-byte elements in the vector at +0xbc.
#include "game/types.h"

struct Owner_9d0c80 {
    char mPad[0xbc];
    void** mpBegin;                           // +0xbc
    void** mpEnd;                             // +0xc0
    int size() const;
};

// @ 0x009d0c80
int Owner_9d0c80::size() const
{
    return (int)(mpEnd - mpBegin);
}
