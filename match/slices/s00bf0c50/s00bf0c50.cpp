// size() (0x00bf0c50): number of 4-byte elements in the vector at +0xb0.
#include "game/types.h"

struct Owner_bf0c50 {
    char mPad[0xb0];
    void** mpBegin;                           // +0xb0
    void** mpEnd;                             // +0xb4
    int size() const;
};

// @ 0x00bf0c50
int Owner_bf0c50::size() const
{
    return (int)(mpEnd - mpBegin);
}
