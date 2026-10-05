// Slice s007bbf80 — SP::cThumbnailManager::DilateStart (0x007bbf80, 3910 bytes)
// A large /O2 /arch:SSE2 /EHsc dilate-pipeline setup: it reads several RTT
// rect ids, builds a cContentValidationSummarizer and a long chain of
// cFilterChainJob objects, configures them, and posts messages.  Only the
// prologue/allocation schedule is reconstructed here — see partial.txt.
#include "types.h"

void* operator new(unsigned int size, const char* group, int a, int b, int c, int d);

struct ContentValidationSummarizer {
    virtual void v0();
    virtual void v1();
    int  m8;
    int  mc, m10, m14;
    unsigned char m20;
    int  m24, m28, m2c, m30;
};

void* __cdecl FUN_0067dd50();

// @ 0x007bbf80
void SP_cThumbnailManager_DilateStart(int param_1)
{
    // RTT manager query (read +0x10 / +0x18 / +0x20 of the argument object).
    (void)*(int*)(param_1 + 0x18);
    (void)*(int*)(param_1 + 8);
    (void)*(int*)(param_1 + 0x10);
    (void)*(int**)(param_1 + 0x20);
    (void)FUN_0067dd50();

    // cContentValidationSummarizer + ~10 cFilterChainJob allocations followed.
    ContentValidationSummarizer* cs = new ("Graphics",0,0,0,0) ContentValidationSummarizer();
    (void)cs;
}
