// Slice s00c44f50 - static initializer of the global SP::cString table that
// 0x00c48970 and friends read through absolute addresses.  The table is
// contiguous 0x14-byte cString objects: 16 named entries, then a 10-entry
// block whose resource ids run consecutively (0x43af507 + i), plus one last
// entry that is set up before the block.
// Flags: /O2 /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast
#include "game/types.h"
#include <wchar.h>

// SP::cString, declared here only for its retail size and Load signature
// (0x006b54b0) so the calls below are not inlined.
struct CStr {
    char pad[0x14];
    bool Load(unsigned int id, unsigned int instanceId, const wchar_t* text);
};

// @ 0x00c44f50
void InitStringTable()
{
    CStr* const table = (CStr*)0x168ee08;

    table[0].Load(0x2db6dad3, 0x43af4fa, 0);
    table[1].Load(0x2db6dad3, 0x43af4fb, 0);
    table[2].Load(0x2db6dad3, 0x43af4fc, 0);
    table[3].Load(0x2db6dad3, 0x43af4fd, 0);
    table[4].Load(0x2db6dad3, 0x43af4fe, 0);
    table[5].Load(0x2db6dad3, 0x43af4ff, 0);
    table[6].Load(0x2db6dad3, 0x43af500, 0);
    table[7].Load(0x2db6dad3, 0x43af501, 0);
    table[8].Load(0x2db6dad3, 0x43af520, 0);
    table[9].Load(0x2db6dad3, 0x43af521, 0);
    table[10].Load(0x2db6dad3, 0x43af523, 0);
    table[11].Load(0x2db6dad3, 0x43af523, 0);
    table[12].Load(0x2db6dad3, 0x43af504, 0);
    table[13].Load(0x2db6dad3, 0x43af505, 0);
    table[14].Load(0x2db6dad3, 0x435eced, 0);
    table[15].Load(0x2db6dad3, 0x43af529, 0);
    table[26].Load(0x2db6dad3, 0x43af52a, 0);

    CStr* const block = (CStr*)0x168ef48;
    for (int i = 0; i < 10; ++i)
        block[i].Load(0x2db6dad3, 0x43af507 + i, 0);
}
