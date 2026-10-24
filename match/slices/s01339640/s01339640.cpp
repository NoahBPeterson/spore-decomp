// Slice s01339640 -- static cString array initializer (partial).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace SP {

struct cString {
    uint32_t mData[5];                                       // 0x14 bytes
};

extern cString gStringTable[10];                             // 0x0168ef48

} // namespace SP

extern "C" void cStringCtor();                               // 0x006b5060
extern "C" void StaticStringDtor();                          // 0x013c3a20
extern "C" int atexit(void (__cdecl*)());                    // 0x011e07ef

// @ 0x0133b9f0
void StaticStringInit()
{
    SP::cString* p = SP::gStringTable;
    int n = 9;
    do {
        ((void (__thiscall*)(void*))cStringCtor)(p);
        ++p;
        --n;
    } while (n >= 0);
    atexit(StaticStringDtor);
}
