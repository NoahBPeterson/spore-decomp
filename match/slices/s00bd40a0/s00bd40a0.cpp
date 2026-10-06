// Slice s00bd40a0: the single function in this slice is
//   0x00BD40A0  FUN_00bd40a0  (7678 bytes, __thiscall, no stack args, ret)
//
// A monolithic routine with a 0x1A0C-byte stack frame (`mov eax,0x1a0c; call
// lib_crt::chkstk`). ECX = this (kept in EBP). It starts by clearing byte
// [+0x340], then walks a container based at [+0x344] (begin/end pointers loaded
// into EBX/EDI and pushed into a helper), and goes on to build a large number of
// temporary records, run several container fills, and finally free a buffer via
// 0x00F47380 (a deallocate helper). Ghidra labels it __fastcall with one int
// argument but ECX is plainly the receiver, so it is a no-argument thiscall.
//
// 7678 bytes (~1900 instructions) is beyond the slice budget for full
// reconstruction, so this file keeps the exact receiver convention and a
// compiling skeleton; recorded as incomplete in partial.txt.
#include "types.h"

namespace SP {

class cBigContainer {
public:
    void Update();                 // 0x00BD40A0

    char pad000[0x340];
    uint8_t mb340;                 // +0x340  scratch flag, cleared on entry
    char pad341[0x3];

    struct Range {
        void* mpBegin;             // +0x344
        void* mpEnd;               // +0x348
    };
    Range mRange;                  // +0x344
};

}  // namespace SP

// @ 0x00BD40A0
void SP::cBigContainer::Update()
{
    mb340 = 0;
    // the 0x1a0c-byte body is not reconstructed (see partial.txt)
}
