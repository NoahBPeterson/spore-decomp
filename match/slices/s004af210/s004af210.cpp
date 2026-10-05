// Slice s004af210 — SP::cSPEditorModel vector helpers.
#include "types.h"

extern void FUN_00454280(void* first, void* last);
extern void FUN_004769b0(void* first, void* last);
extern void FUN_004b0590(void* end, int n, void** out);
extern void FUN_004b0a10(void* end, int n, void** out);
extern void FUN_00409c00(void* bbox);
extern void FUN_004b1800(void* end, int n, void* bbox);
extern void FUN_004b0490(void* first, void* last);
extern void* FUN_0042dee0(void* p, int size, int align, int flags);
extern void FUN_004b00a0(void* p);
extern void FUN_004b0180(void* p);
extern void FUN_004b0140();
extern void FUN_004b03f0(void* a, void* b, void* c);
extern void FUN_f47380(void* p);

struct Block194 { uint32_t d[0x76]; };

struct VecBase {
    char* mpBegin;      // +0x0
    char* mpEnd;        // +0x4
    char* mpCapacity;   // +0x8

    void Resize4(unsigned int n);     // 0x4afbf0
    void Resize4F(unsigned int n);    // 0x4afc80
    void Resize24(unsigned int n);    // 0x4aff80
    void Resize1d8(unsigned int n);   // 0x4afd00
    void Reserve194(unsigned int n);  // 0x4afdd0
    Block194* Erase194(Block194* dst, Block194* end);  // 0x4b0340
    void* Init8();                    // 0x4b0040
};

// @ 0x004af210
struct PropVal { unsigned int& GetValue(); };
bool GetPropertyAsUint32(void* propList, unsigned int id, unsigned int* out)
{
    if (propList != 0) {
        int pad;
        int local;
        if ((*(unsigned char(__thiscall*)(void*, unsigned int, int*))(*(void**)((char*)*(void**)propList + 0x24)))(propList, id, &local) != 0) {
            if (*(uint16_t*)(local + 0x12) == 10) {
                *out = ((PropVal*)local)->GetValue();
                return true;
            }
        }
    }
    return false;
}

// @ 0x004afbf0
void VecBase::Resize4(unsigned int n)
{
    if ((unsigned int)((mpEnd - mpBegin) >> 2) < n) {
        void* local = 0;
        FUN_004b0590(mpEnd, n - ((mpEnd - mpBegin) >> 2), &local);
        if (local != 0) {
            (*(void(__thiscall*)(void*))(*(uint32_t*)local + 8))(local);
        }
    }
    else {
        FUN_00454280(mpBegin + n * 4, mpEnd);
    }
}

// @ 0x004afc80
void VecBase::Resize4F(unsigned int n)
{
    if ((unsigned int)((mpEnd - mpBegin) >> 2) < n) {
        float local = 0.0f;
        FUN_004b0a10(mpEnd, n - ((mpEnd - mpBegin) >> 2), (void**)&local);
    }
    else {
        FUN_004769b0(mpBegin + n * 4, mpEnd);
    }
}

// @ 0x004aff80
void VecBase::Resize24(unsigned int n)
{
    if ((unsigned int)((mpEnd - mpBegin) / 0x18) < n) {
        char local[0x18];
        FUN_00409c00(local);
        FUN_004b1800(mpEnd, n - (mpEnd - mpBegin) / 0x18, local);
    }
    else {
        FUN_004b0490(mpBegin + n * 0x18, mpEnd);
    }
}

// @ 0x004b0340
Block194* VecBase::Erase194(Block194* dst, Block194* end)
{
    Block194* out = (Block194*)mpEnd;
    Block194* local_14 = dst;
    for (Block194* local_10 = end; local_10 != out; ++local_10) {
        *local_14 = *local_10;
        ++local_14;
    }
    for (Block194* local_1c = local_14; local_1c < (Block194*)mpEnd; ++local_1c) {
    }
    mpEnd = (char*)mpEnd + ((char*)end - (char*)dst) / 0x1d8 * -0x1d8;
    return dst;
}

// @ 0x004b0040
void* VecBase::Init8()
{
    int local_8 = 8;
    char* local_4 = (char*)this + 0x118;
    while (true) {
        local_8 = local_8 - 1;
        if (local_8 < 0) break;
        local_4 += 0xc;
    }
    int local_10 = 8;
    char* local_c = (char*)this + 0x178;
    while (true) {
        local_10 = local_10 - 1;
        if (local_10 < 0) break;
        local_c += 0xc;
    }
    return this;
}

// @ 0x004afd00
extern void FUN_004b11f0(void* end, int n, void* elem);
void VecBase::Resize1d8(unsigned int n)
{
    if ((unsigned int)((mpEnd - mpBegin) / 0x1d8) < n) {
        char tmp[0x1d8];
        void* elem = Init8();
        FUN_004b11f0(mpEnd, n - (mpEnd - mpBegin) / 0x1d8, elem);
    }
    else {
        Erase194((Block194*)(mpBegin + n * 0x1d8), (Block194*)mpEnd);
    }
}

// @ 0x004afdd0
void VecBase::Reserve194(unsigned int n)
{
    int size = (int)((mpEnd - mpBegin) / 0x1d8);
    if (n == 0xffffffff || (int)n <= size) {
        if (n < (unsigned int)size) Resize1d8(n);
        FUN_004b00a0(this);
        char local[0x14];
        FUN_004b0180(local);
        FUN_004b0140();
    }
    else {
        void* p = (n == 0) ? 0 : FUN_0042dee0(&mpCapacity, n * 0x1d8, 4, 0);
        FUN_004b03f0(mpBegin, mpEnd, p);
        char* old = mpBegin;
        if (old != 0 && *(int*)(old - 4) != 0) {
            FUN_f47380(old);
        }
        int oldCount = (int)((mpEnd - old) / 0x1d8);
        mpBegin = (char*)p;
        mpEnd = oldCount * 0x1d8 + (char*)p;
        mpCapacity = n * 0x1d8 + (char*)p;
    }
}

// @ 0x004af260 — 2446-byte SaveResource (not reconstructed).
bool SaveResource(void* self, void* writer)
{
    (void)self; (void)writer;
    return false;
}
