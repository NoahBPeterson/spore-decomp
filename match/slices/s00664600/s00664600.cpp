// size() (0x00664600): number of 4-byte elements in the vector at +0x88.
#include "game/types.h"

struct Owner_664600 {
    char mPad[0x88];
    void** mpBegin;                           // +0x88
    void** mpEnd;                             // +0x8c
    int size() const;
};

// @ 0x00664600
int Owner_664600::size() const
{
    return (int)(mpEnd - mpBegin);
}
