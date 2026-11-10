// Slice s00887090 -- eastl string assign (see nonmatching.txt).
// Flags: /O2 /MD /Gy /EHsc /TP

typedef unsigned int  uint32_t;
typedef char          eastl_char;

#include <string.h>

struct basic_string
{
    eastl_char* mpBegin;        // +0x00
    eastl_char* mpCapacity;     // +0x04
    eastl_char* mpEnd;          // +0x08
    uint32_t    mPad0c;         // +0x0c
    eastl_char  mSso[16];       // +0x10

    void assign(const eastl_char* p, uint32_t n);
};

// 0x00f473a0: debug allocation with source-location arguments
void* AllocDebug(uint32_t n, const char* msg, int a, int b, const char* file, int line);
// 0x00f47380: operator delete
void* FreeDebug(void* p);

// 0x00886560: resize the buffer to hold `n` characters
void Grow(basic_string* self, uint32_t n);

// @ 0x00887090
void basic_string::assign(const eastl_char* p, uint32_t n)
{
    if (n != 0xffffffffu && n > (uint32_t)(mpCapacity - mpBegin))
    {
        uint32_t old = (uint32_t)(mpEnd - mpBegin);
        eastl_char* nb = (eastl_char*)AllocDebug(n + 1, "Assertion failed", 0, 0, "EASTL/string.h", 0xd1);
        memcpy(nb, mpBegin, mpCapacity - mpBegin);
        nb[old] = 0;
        if ((uint32_t)(mpEnd - mpBegin) > 1 && mpBegin != 0 && mpBegin != mSso)
            FreeDebug(mpBegin);
        mpBegin = nb;
        mpCapacity = nb + n + 1;
        mpEnd = nb + old;
        return;
    }
    Grow(this, n);
    memcpy(mpBegin, p, n);
    mpEnd = mpBegin + n;
    mpEnd[0] = 0;
    if ((mpCapacity - mpBegin) > 1)
    {
        if (mpBegin != 0 && mpBegin != mSso)
            FreeDebug(mpBegin);
    }
}
