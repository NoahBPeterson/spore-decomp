// Slice s00891310: copy the 0x44-byte payload at +0xbc to the caller's buffer,
// guarded by a flag at +0x10 and a critical section at +0x28.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <string.h>

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void* cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);

struct Obj_00891310 {
    char pad_000[0x10];                         // +0x000 .. +0x00f
    int  mReady;                                // +0x010
    char pad_014[0x28 - 0x14];                  // +0x014 .. +0x027
    char mCriticalSection[0x28];                // +0x028 (CRITICAL_SECTION)
    char pad_050[0xbc - 0x50];                  // +0x050 .. +0x0bb
    char mPayload[0x44];                        // +0x0bc .. +0x0ff

    bool FUN_00891310(void* dst);
};

// @ 0x00891310
bool Obj_00891310::FUN_00891310(void* dst)
{
    EnterCriticalSection(mCriticalSection);
    if (mReady != 0) {
        memcpy(dst, mPayload, 0x44);
        LeaveCriticalSection(mCriticalSection);
        return true;
    }
    LeaveCriticalSection(mCriticalSection);
    return false;
}