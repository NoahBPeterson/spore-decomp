// size() (0x00662a10): number of 4-byte elements in the vector at +0x38.
#include "game/types.h"

struct Owner_662a10 {
    char mPad[0x38];
    void** mpBegin;                           // +0x38
    void** mpEnd;                             // +0x3c
    int size() const;
};

// @ 0x00662a10
int Owner_662a10::size() const
{
    return (int)(mpEnd - mpBegin);
}
