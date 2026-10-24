// Slice s004ce310: out-of-line EASTL vector<>::insert relocation paths used by the
// creature-editor skin code.  Flags region: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast
// (unoptimised: every temporary lives in an [ebp-..] slot, which is what the retail bodies do).
//
// The four bodies are eastl::vector<T>::DoInsertValue / DoInsertValues instantiations
// (all __thiscall, `this` arriving in ecx, spilling it to a stack slot):
//   004ce310  DoInsertValue  -- float  (4-byte) element
//   004ce550  DoInsertValue  -- 1-byte element
//   004cef00  DoInsertValues -- 8-byte element
//   004cf2c0  DoInsertValues -- 0x34-byte element
#include "types.h"

// ---- imports / in-TU helpers the originals call ----
extern "C" void* memcpy(void* dst, const void* src, unsigned int count);   // @ 0x011e0744
extern "C" void* memmove(void* dst, const void* src, unsigned int count);  // @ 0x013cc480

extern void* EASTL_Allocate(void* allocator, unsigned int n, int align, int flags);  // @ 0x0042dee0
extern void  ElemFree(void* p);                                                      // @ 0x00f47380

// 8-byte element relocation helpers (the vecE8a2<T> instantiations)
extern void* Elem8Copy(void* first, void* last, void* dst);                          // @ 0x004554f0
extern void  Elem8FillN(void* dst, unsigned int n, void* value, int* flag);          // @ 0x0052c8f0
extern void* MovePtr8(void* first, void* last, void* dst);                           // @ 0x004d0960
extern void  MoveTail8(int* holder, void* first, void* last, void* dst, int flag);   // @ 0x00541450

// 0x34-byte element helpers
extern void  E34_dtorA(void* p);                                                     // @ 0x004098a0
extern void  E34_dtorB(void* p);                                                     // @ 0x004d08c0
extern void* E34_MoveHead(void* first, void* pos, void* dst);                        // @ 0x004d0a40
extern void  E34_FillN(void* dst, unsigned int n, void* value, int* flag);           // @ 0x004d0d40
extern void* E34_MoveStart(void* pos, void* end, void* dst);                         // @ 0x004d10b0
extern void  E34_MoveCommit(void* pos, void* end, void* dst);                        // @ 0x004d1130
extern void  E34_MoveTail(void* holder, void* first, void* last, void* dst, int flag); // @ 0x004d0c90
extern void* E34_MoveBack(void* first, void* last, void* dst);                       // @ 0x004d0a00
extern void  E34_Assign(void* dst, void* src);                                       // @ 0x004d1030
extern void  E34_SubDtor(void* p);                                                   // @ 0x0041d140
extern void  E34_VecDtor(void);                                                      // @ 0x004c0b80

// 8-byte element (pair-like; the two 32-bit fields move as a unit via the retail helpers)
struct Elem8 {
    int a;              // +0x00
    int b;              // +0x04
};

typedef char Elem34[0x34];

struct VecF32 {
    float* mpBegin;     // +0x00
    float* mpEnd;       // +0x04
    float* mpCapacity;  // +0x08
    int    mAlloc;      // +0x0c
    float* mpInline;    // +0x10
    void DoInsertValueF32(float* position, float const& value);
};

struct VecU8 {
    unsigned char* mpBegin;     // +0x00
    unsigned char* mpEnd;       // +0x04
    unsigned char* mpCapacity;  // +0x08
    int    mAlloc;              // +0x0c
    unsigned char* mpInline;    // +0x10
    void DoInsertValueU8(unsigned char* position, unsigned char const& value);
};

struct VecE8 {
    Elem8* mpBegin;     // +0x00
    Elem8* mpEnd;       // +0x04
    Elem8* mpCapacity;  // +0x08
    int    mAlloc;      // +0x0c
    Elem8* mpInline;    // +0x10
    void DoInsertValuesE8(Elem8* position, unsigned int n, Elem8 const& value);
};

struct VecE34 {
    Elem34* mpBegin;      // +0x00
    Elem34* mpEnd;        // +0x04
    Elem34* mpCapacity;   // +0x08
    int     mAlloc;       // +0x0c
    Elem34* mpInline;     // +0x10
    void DoInsertValuesE34(Elem34* position, unsigned int n, Elem34 const& value);
};

// @ 0x004CE310
void VecF32::DoInsertValueF32(float* position, float const& value)
{
    if (mpEnd != mpCapacity) {
        const float* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        *(float*)mpEnd = *(float*)(mpEnd - 1);
        memmove((void*)(mpEnd - ((((char*)(mpEnd - 1) - (char*)position) >> 2) << 2)),
                position, (unsigned int)((char*)(mpEnd - 1) - (char*)position));
        *position = *pValue;
        ++mpEnd;
        return;
    }

    unsigned int nPrevSize = (unsigned int)(mpEnd - mpBegin);
    unsigned int nNewSize = (nPrevSize == 0) ? 1u : (nPrevSize << 1);
    float* pNewData;
    if (nNewSize == 0)
        pNewData = 0;
    else
        pNewData = (float*)EASTL_Allocate(&mAlloc, nNewSize << 2, 4, 0);

    float* begin = mpBegin;
    void* p = memcpy(pNewData, begin, (unsigned int)((char*)position - (char*)begin));
    float* pNewEnd = (float*)((char*)p + (((char*)position - (char*)begin) >> 2) * 4);
    if (pNewEnd != 0)
        *pNewEnd = value;

    float* end = mpEnd;
    void* r = memcpy(pNewEnd + 1, position, (unsigned int)((char*)end - (char*)position));
    float* pNewEnd2 = (float*)((char*)r + ((((char*)end - (char*)position) >> 2) * 4));

    if (mpBegin != 0 && mpBegin != mpInline)
        ElemFree(mpBegin);

    mpBegin = pNewData;
    mpEnd = pNewEnd2;
    mpCapacity = pNewData + nNewSize;
}

// @ 0x004CE550
void VecU8::DoInsertValueU8(unsigned char* position, unsigned char const& value)
{
    if (mpEnd != mpCapacity) {
        const unsigned char* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        *(unsigned char*)mpEnd = *(unsigned char*)(mpEnd - 1);
        memmove((void*)(mpEnd - (((char*)(mpEnd - 1) - (char*)position))),
                position, (unsigned int)((char*)(mpEnd - 1) - (char*)position));
        *position = *pValue;
        ++mpEnd;
        return;
    }

    unsigned int nPrevSize = (unsigned int)(mpEnd - mpBegin);
    unsigned int nNewSize = (nPrevSize == 0) ? 1u : (nPrevSize << 1);
    unsigned char* pNewData;
    if (nNewSize == 0)
        pNewData = 0;
    else
        pNewData = (unsigned char*)EASTL_Allocate(&mAlloc, nNewSize, 1, 0);

    unsigned char* begin = mpBegin;
    void* p = memcpy(pNewData, begin, (unsigned int)((char*)position - (char*)begin));
    unsigned char* pNewEnd = (unsigned char*)((char*)p + ((char*)position - (char*)begin));
    if (pNewEnd != 0)
        *pNewEnd = value;

    unsigned char* end = mpEnd;
    void* r = memcpy(pNewEnd + 1, position, (unsigned int)((char*)end - (char*)position));
    unsigned char* pNewEnd2 = (unsigned char*)((char*)r + ((char*)end - (char*)position));

    if (mpBegin != 0 && mpBegin != mpInline)
        ElemFree(mpBegin);

    mpBegin = pNewData;
    mpEnd = pNewEnd2;
    mpCapacity = pNewData + nNewSize;
}

// @ 0x004CEF00
void VecE8::DoInsertValuesE8(Elem8* position, unsigned int n, Elem8 const& value)
{
    if (((unsigned int)(mpCapacity - mpEnd)) < n) {
        unsigned int nPrevSize = (unsigned int)(mpEnd - mpBegin);
        unsigned int nNewSize = (nPrevSize == 0) ? 1u : (nPrevSize << 1);
        unsigned int nWant = (nPrevSize + n < nNewSize) ? nNewSize : (nPrevSize + n);

        Elem8* pNewData;
        if (nWant == 0)
            pNewData = 0;
        else
            pNewData = (Elem8*)EASTL_Allocate(&mAlloc, nWant << 3, 4, 0);

        Elem8* p = (Elem8*)Elem8Copy(mpBegin, position, pNewData);
        Elem8FillN(p, n, (void*)&value, 0);
        Elem8* pNewEnd = (Elem8*)Elem8Copy(position, mpEnd, &p[n]);

        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            ElemFree(mpBegin);

        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nWant;
        return;
    }

    if (n == 0)
        return;

    Elem8 tmp;
    tmp.a = value.a;
    tmp.b = value.b;

    unsigned int tail = (unsigned int)(mpEnd - position);
    Elem8* end = mpEnd;

    if (n < tail) {
        int holder;
        MoveTail8(&holder, end - n, end, end, 0);
        mpEnd = end + n;
        Elem8* d = end;
        Elem8* s = end - n;
        while (s != position) {
            *--d = *--s;
        }
        for (Elem8* it = position; it != position + n; ++it) {
            it->a = tmp.a;
            it->b = tmp.b;
        }
    } else {
        Elem8FillN(mpEnd, n - tail, &tmp, 0);
        mpEnd = mpEnd + (n - tail);
        MovePtr8(position, end, mpEnd);
        mpEnd = mpEnd + tail;
        for (Elem8* it = position; it != end; ++it) {
            it->a = tmp.a;
            it->b = tmp.b;
        }
    }
}

// @ 0x004CF2C0
void VecE34::DoInsertValuesE34(Elem34* position, unsigned int n, Elem34 const& value)
{
    if (((unsigned int)(mpCapacity - mpEnd)) < n) {
        unsigned int nPrevSize = (unsigned int)(mpEnd - mpBegin);
        unsigned int nNewSize = (nPrevSize == 0) ? 1u : (nPrevSize << 1);
        unsigned int nWant = (nPrevSize + n < nNewSize) ? nNewSize : (nPrevSize + n);

        Elem34* pNewData;
        if (nWant == 0)
            pNewData = 0;
        else
            pNewData = (Elem34*)EASTL_Allocate(&mAlloc, nWant * 0x34, 4, 0);

        Elem34* p = (Elem34*)E34_MoveHead(mpBegin, position, pNewData);
        E34_FillN(p, n, (void*)&value, 0);
        Elem34* mid = &p[n];
        Elem34* end = mpEnd;
        Elem34* pNewEnd = (Elem34*)E34_MoveStart(position, end, mid);
        E34_MoveCommit(position, end, mid);

        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            ElemFree(mpBegin);

        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nWant;
        return;
    }

    if (n == 0)
        return;

    E34_dtorA((void*)&value);
    E34_dtorB((void*)((char*)&value + 0x0c));

    unsigned int tail = (unsigned int)(mpEnd - position);
    Elem34* end = mpEnd;

    if (n < tail) {
        char holder[4];
        E34_MoveTail(holder, end - n, end, end, 0);
        mpEnd = end + n;
        Elem34* d = end;
        Elem34* s = end - n;
        while (s != position) {
            memcpy((char*)d - 0x34, (char*)s - 0x34, 0x0c);
            E34_SubDtor((char*)s - 0x28);
            --d;
            --s;
        }
        for (Elem34* it = position; it != position + n; ++it) {
            E34_Assign(it, (void*)&value);
        }
    } else {
        E34_FillN(mpEnd, n - tail, (void*)&value, 0);
        mpEnd = mpEnd + (n - tail);
        E34_MoveBack(position, end, mpEnd);
        mpEnd = mpEnd + tail;
        for (Elem34* it = position; it != end; ++it) {
            E34_Assign(it, (void*)&value);
        }
    }

    (void)E34_dtorA;
}  // (retail leaves the value-local teardown to the caller)