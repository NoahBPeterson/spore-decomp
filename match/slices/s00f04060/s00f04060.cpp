// size() (0x00f04060): number of 4-byte elements in the vector at +0xd0.
#include "game/types.h"

struct Owner_f04060 {
    char mPad[0xd0];
    void** mpBegin;                           // +0xd0
    void** mpEnd;                             // +0xd4
    int size() const;
};

// @ 0x00f04060
int Owner_f04060::size() const
{
    return (int)(mpEnd - mpBegin);
}
