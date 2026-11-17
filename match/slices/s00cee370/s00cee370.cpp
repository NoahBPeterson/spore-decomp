// size() (0x00cee370): number of 4-byte elements in the vector at +0x4.
#include "game/types.h"

struct Owner_cee370 {
    char mPad[0x4];
    void** mpBegin;                           // +0x4
    void** mpEnd;                             // +0x8
    int size() const;
};

// @ 0x00cee370
int Owner_cee370::size() const
{
    return (int)(mpEnd - mpBegin);
}
