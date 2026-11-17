// size() (0x00c87240): number of 4-byte elements in the vector at +0x34.
#include "game/types.h"

struct Owner_c87240 {
    char mPad[0x34];
    void** mpBegin;                           // +0x34
    void** mpEnd;                             // +0x38
    int size() const;
};

// @ 0x00c87240
int Owner_c87240::size() const
{
    return (int)(mpEnd - mpBegin);
}
