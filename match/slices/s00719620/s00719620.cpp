// Slice s00719620: EASTL vector<T, sp_vector_allocator> insert/resize instances and a
// backward copy helper, from the Spore SWARM/game-model + mesh-builder region.
// Optimized module: /O2 /MD /Gy /EHsc /TP /GS-.
#include "types.h"

// ---------------------------------------------------------------------------
// Element types (opaque; sizes/embedded containers come from the disassembly).
// ---------------------------------------------------------------------------
template <typename T>
struct spv {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAlloc[1];
    spv() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~spv() throw();
};

// 0x28-byte element: two spv<> members at +0 and +0x14.
struct T28 {
    spv<int> m0;      // +0x00
    uint32_t m1;      // +0x10
    spv<int> m2;      // +0x14
    uint32_t m3;      // +0x24
    T28() {}
    ~T28() throw();
    T28(const T28&);
    T28& operator=(const T28&);
};

// 0x50-byte element: four spv<> members at 0, 0x14, 0x28, 0x3c.
struct T50 {
    spv<int> m0;      // +0x00
    uint32_t m1;      // +0x10
    spv<int> m2;      // +0x14
    uint32_t m3;      // +0x24
    spv<int> m4;      // +0x28
    uint32_t m5;      // +0x38
    spv<int> m6;      // +0x3c
    uint32_t m7;      // +0x4c
    T50() {}
    ~T50() throw();
    T50(const T50&);
    T50& operator=(const T50&);
};

// 0xd0-byte element with a nontrivial default ctor/dtor.
struct T140 {
    uint32_t mData[0x34];
    T140();
    T140(const T140&);
    ~T140();
    T140& operator=(const T140&);
};

// 0x8c-byte element copied by the backward-copy helper.
struct Ref;
struct FixedIdVector6 { uint32_t mData[6]; void DoAssign(const FixedIdVector6&); };
struct FixedEntryVector3 { uint32_t mData[3]; void DoAssign(const FixedEntryVector3&); };
struct Obj8C {
    uint32_t mId;             // +0x00
    uint32_t mFlags;          // +0x04
    uint16_t mA;              // +0x08
    uint16_t mB;              // +0x0a
    Ref* mRef;                // +0x0c
    uint32_t mX;              // +0x10
    FixedIdVector6 mV6;       // +0x14
    FixedEntryVector3 mV3;    // +0x2c
    uint32_t mPad[0x14];      // rest up to 0x8c
};

// ---------------------------------------------------------------------------
// Outlined helpers (bodies live in other slices / translation units).  They are
// declard without a definition so the calls stay out of line, as in the original.
// ---------------------------------------------------------------------------
void SpFree(void* p);                                       // 0x00f47380
void* SpAlloc(uint32_t size, const char* area, int a, int b, const char* file, int line); // 0x00f473a0

T28*  UninitMove28(T28* first, T28* last, T28* dest);        // 0x00718570
void  Destroy28(T28* first, T28* last, T28* dest);           // 0x00714c70
T28*  FillN28(T28* dest, uint32_t n, const T28* value, T28* extra); // 0x007184a0
T28*  MoveUninit28(T28* dest, T28* first, T28* last, T28* extra);   // 0x00718420
void  FillRange28(T28* first, T28* last, const T28* value);  // 0x00719200
void  CopyBackward28(T28* first, T28* last, T28* dest);      // 0x00718640

T50*  UninitMove50(T50* first, T50* last, T50* dest);        // 0x00716650
void  Destroy50(T50* first, T50* last, T50* dest);           // 0x00714a20
T50*  FillN50(T50* dest, uint32_t n, const T50* value, T50* extra); // 0x00716540
T50*  MoveUninit50(T50* dest, T50* first, T50* last, T50* extra);   // 0x007164c0
void  FillRange50(T50* first, T50* last, const T50* value);  // 0x00718520
void  CopyBackward50(T50* first, T50* last, T50* dest);      // 0x00717b70

void  Obj8C_Assign(Obj8C* dst, const Obj8C* src);

// ===========================================================================
// Vector types
// ===========================================================================
struct Vec28 {
    T28* mpBegin; T28* mpEnd; T28* mpCapacity; uint32_t mAlloc[1];
    void insert(T28* position, uint32_t n, const T28& value);
    void resize(uint32_t n);
};
struct Vec50 {
    T50* mpBegin; T50* mpEnd; T50* mpCapacity; uint32_t mAlloc[1];
    void insert(T50* position, uint32_t n, const T50& value);
    void resize(uint32_t n);
    void erase(T50* first, T50* last);       // 0x00719390, out of line
};
struct Vec140 {
    T140* mpBegin; T140* mpEnd; T140* mpCapacity; uint32_t mAlloc[1];
    void resize(uint32_t n);
    void DoInsertValues(T140* position, uint32_t n, const T140& value); // 0x007193e0
    void erase(T140* first, T140* last);                                 // 0x00719330
};

// @ 0x00719620
void Vec50::insert(T50* position, uint32_t n, const T50& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n != 0) {
            const T50 temp = value;
            T50* const oldEnd = mpEnd;
            const uint32_t nExtra = (uint32_t)(oldEnd - position);
            if (n < nExtra) {
                T50* r;
                MoveUninit50(r, oldEnd - n, oldEnd, oldEnd);
                mpEnd += n;
                CopyBackward50(position, oldEnd - n, oldEnd);
                FillRange50(position, position + n, &temp);
            } else {
                FillN50(oldEnd, n - nExtra, &temp, position);
                mpEnd += n - nExtra;
                T50* r;
                MoveUninit50(r, position, oldEnd, mpEnd);
                mpEnd += nExtra;
                FillRange50(position, oldEnd, &temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = (nPrevSize > 0) ? (nPrevSize * 2) : 1;
        const uint32_t nNewSize = (nGrowSize > (nPrevSize + n)) ? nGrowSize : (nPrevSize + n);
        T50* const pNewData = nNewSize ? (T50*)SpAlloc(nNewSize * sizeof(T50),
            "Graphics", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        T50* pNewEnd = UninitMove50(mpBegin, position, pNewData);
        Destroy50(mpBegin, position, pNewData);
        FillN50(pNewEnd, n, &value, pNewEnd);
        pNewEnd += n;
        pNewEnd = UninitMove50(position, mpEnd, pNewEnd);
        Destroy50(position, mpEnd, pNewEnd);
        if (mpBegin && ((uint32_t*)mpBegin)[-1])
            SpFree(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00719a00
void Vec28::insert(T28* position, uint32_t n, const T28& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n != 0) {
            const T28 temp = value;
            T28* const oldEnd = mpEnd;
            const uint32_t nExtra = (uint32_t)(oldEnd - position);
            if (n < nExtra) {
                T28* r;
                MoveUninit28(r, oldEnd - n, oldEnd, oldEnd);
                mpEnd += n;
                CopyBackward28(position, oldEnd - n, oldEnd);
                FillRange28(position, position + n, &temp);
            } else {
                FillN28(oldEnd, n - nExtra, &temp, position);
                mpEnd += n - nExtra;
                T28* r;
                MoveUninit28(r, position, oldEnd, mpEnd);
                mpEnd += nExtra;
                FillRange28(position, oldEnd, &temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = (nPrevSize > 0) ? (nPrevSize * 2) : 1;
        const uint32_t nNewSize = (nGrowSize > (nPrevSize + n)) ? nGrowSize : (nPrevSize + n);
        T28* const pNewData = nNewSize ? (T28*)SpAlloc(nNewSize * sizeof(T28),
            "Graphics", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        T28* pNewEnd = UninitMove28(mpBegin, position, pNewData);
        Destroy28(mpBegin, position, pNewData);
        FillN28(pNewEnd, n, &value, pNewEnd);
        T28* const pInsertEnd = pNewEnd + n;
        T28* const oldEnd = mpEnd;
        T28* pNewEnd2 = UninitMove28(position, oldEnd, pInsertEnd);
        Destroy28(position, oldEnd, pInsertEnd);
        if (mpBegin && ((uint32_t*)mpBegin)[-1])
            SpFree(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd2;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00719c60
void Vec140::resize(uint32_t n)
{
    if (n > (uint32_t)(mpEnd - mpBegin)) {
        DoInsertValues(mpEnd, n - (uint32_t)(mpEnd - mpBegin), T140());
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// @ 0x00719d30
void Vec50::resize(uint32_t n)
{
    if (n > (uint32_t)(mpEnd - mpBegin)) {
        insert(mpEnd, n - (uint32_t)(mpEnd - mpBegin), T50());
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// @ 0x00719890
void CopyBackward8C(Obj8C* first, Obj8C* last, Obj8C* dest)
{
    while (last != first)
        Obj8C_Assign(--dest, --last);
}
