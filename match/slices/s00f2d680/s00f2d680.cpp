// Slice s00f2d680 -- Simulator scenario/action object region (bfs2 slice 10).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE  (scalar movss float ops; no x87 copies).
// Class layouts reconstructed from the disassembly; no real names were recoverable for this
// region from the 2008 dev PDB.
#include "types.h"

// ---------------------------------------------------------------- masked externals
void* __cdecl EA_Alloc(size_t, const char*, int, int, const char*, int);  // 0x00F473A0
void  __cdecl EA_Delete(void*);                                           // 0x00F47380

// raw element-mover helpers (out-of-line template instantiations in the original)
void __cdecl MoveA(void*, void*, void*);   // 0x00F2CE90
void __cdecl MoveB(void*, void*, void*);   // 0x00F2BC70
void __cdecl MoveC(void*, void*, void*);   // 0x00F2D5E0
void __cdecl MoveD(void*, void*, void*);   // 0x00F2BBD0

// ---------------------------------------------------------------- fixed_vector<0x44,5>
struct E44 { char pad[0x44]; };

struct FixedVec5 {
    E44* mpBegin;        // +0x00
    E44* mpEnd;          // +0x04
    E44* mpCapacity;     // +0x08
    int  mPad0c;         // +0x0c
    int  mPad10;         // +0x10
    int  mZero14;        // +0x14
    E44  mBuf[5];        // +0x18
    void resize5(int n); // 0x00F0B390 (thiscall, ret 4)
};

// ---------------------------------------------------------------- cString (0x14 in retail)
struct CString {
    char pad[0x14];
    void ctor();                       // 0x006B5060
};

extern wchar_t g_emptyW[];             // 0x01667BAC
extern wchar_t g_emptyW2[];            // 0x01667BAE

// ---------------------------------------------------------------- the 0x4e0 element
struct E4e0 {
    unsigned char mData[0x4e0];
    E4e0();
};

// @ 0x00F2D680
E4e0::E4e0()
{
    unsigned char* b = mData;
    b[0] = 1;
    b[1] = 0;
    b[2] = 0;

    *(void**)(b + 0x04) = b + 0x1c;
    *(void**)(b + 0x08) = b + 0x1c;
    *(void**)(b + 0x0c) = b + 0x170;
    *(int*)(b + 0x18) = 0;
    ((FixedVec5*)(b + 0x04))->resize5(5);

    *(void**)(b + 0x170) = b + 0x188;
    *(void**)(b + 0x174) = b + 0x188;
    *(void**)(b + 0x178) = b + 0x2dc;
    *(int*)(b + 0x184) = 0;
    ((FixedVec5*)(b + 0x170))->resize5(5);

    *(void**)(b + 0x2dc) = b + 0x2f4;
    *(void**)(b + 0x2e0) = b + 0x2f4;
    *(void**)(b + 0x2e4) = b + 0x448;
    *(int*)(b + 0x2f0) = 0;

    ((CString*)(b + 0x448))->ctor();
    *(wchar_t**)(b + 0x45c) = g_emptyW;
    *(wchar_t**)(b + 0x460) = g_emptyW;
    *(wchar_t**)(b + 0x464) = g_emptyW2;
    *(int*)(b + 0x46c) = 0;
    *(int*)(b + 0x470) = 0;
    *(wchar_t**)(b + 0x474) = g_emptyW;
    *(wchar_t**)(b + 0x478) = g_emptyW;
    *(wchar_t**)(b + 0x47c) = g_emptyW2;

    *(float*)(b + 0x484) = 500.0f;
    *(float*)(b + 0x488) = 20.0f;
    *(float*)(b + 0x48c) = 1.0f;
    *(float*)(b + 0x490) = 1.0f;
    *(float*)(b + 0x494) = 1.0f;
    *(int*)(b + 0x4a4) = -1;
    *(int*)(b + 0x4a8) = 0;
    *(int*)(b + 0x4ac) = 0;
    *(int*)(b + 0x4b0) = 0;
    *(int*)(b + 0x4b4) = 0;
    *(int*)(b + 0x4b8) = 0;
    *(int*)(b + 0x4bc) = -1;
    *(int*)(b + 0x4c0) = -1;
    *(int*)(b + 0x4c4) = -1;
    b[0x4c8] = 0;
    *(float*)(b + 0x498) = 10.0f;
    *(float*)(b + 0x49c) = 10.0f;
    *(float*)(b + 0x4a0) = 10.0f;
    *(int*)(b + 0x4cc) = 0;
    *(int*)(b + 0x4d0) = 0;
    *(int*)(b + 0x4d4) = 0;
}

// ---------------------------------------------------------------- generic 0x4e0 vector
struct Vec4e0 {
    E4e0* mpBegin;       // +0x00
    E4e0* mpEnd;         // +0x04
    E4e0* mpCapacity;    // +0x08
    void set_capacity(unsigned n);
    E4e0* Insert(E4e0* position, const E4e0& value);
    unsigned Serialize4e0(void* owner);
};

// @ 0x00F2DBE0
void Vec4e0::set_capacity(unsigned n)
{
    if (n > (unsigned)(mpCapacity - mpBegin)) {
        E4e0* pNewData = n ? (E4e0*)EA_Alloc(n * 0x4e0, "Simulator", 0, 0,
                                             "allocator.h", 0xd1) : 0;
        E4e0* pOldEnd = mpEnd;
        E4e0* pOldBegin = mpBegin;
        MoveA(pOldBegin, pOldEnd, pNewData);
        MoveB(pOldBegin, pOldEnd, pNewData);
        if (mpBegin && ((int*)mpBegin)[-1])
            EA_Delete(mpBegin);
        unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize;
        mpCapacity = pNewData + n;
    }
}

// @ 0x00F2DF80 (inlined generic insert; growth path uses doubling)
E4e0* Vec4e0::Insert(E4e0* position, const E4e0& value)
{
    if (mpEnd != mpCapacity) {
        E4e0* pValue = (E4e0*)&value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        if (mpEnd)
            ((void(__thiscall*)(void*))(void*)MoveA)(mpEnd - 1);
        MoveA(position, mpEnd - 1, mpEnd);
        MoveB(position, mpEnd - 1, mpEnd);
        *(E4e0*)position = *pValue;
        ++mpEnd;
    } else {
        unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        unsigned nNewSize = nPrevSize ? nPrevSize * 2 : 1;
        E4e0* pNewData = nNewSize ? (E4e0*)EA_Alloc(nNewSize * 0x4e0, "Simulator", 0, 0,
                                                    "allocator.h", 0xd1) : 0;
        MoveA(mpBegin, position, pNewData);
        MoveB(mpBegin, position, pNewData);
        MoveA(position, mpEnd, pNewData + nPrevSize + 1);
        MoveB(position, mpEnd, pNewData + nPrevSize + 1);
        if (mpBegin && ((int*)mpBegin)[-1])
            EA_Delete(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize + 1;
        mpCapacity = pNewData + nNewSize;
    }
    return position;
}

// ---------------------------------------------------------------- 0x238 element / vector
struct E238 { char pad[0x238]; };

struct Vec238 {
    E238* mpBegin;
    E238* mpEnd;
    E238* mpCapacity;
    void set_capacity(unsigned n);
    E238* Insert(E238* position, const E238& value);
};

// @ 0x00F2E230
void Vec238::set_capacity(unsigned n)
{
    if (n > (unsigned)(mpCapacity - mpBegin)) {
        E238* pNewData = n ? (E238*)EA_Alloc(n * 0x238, "Simulator", 0, 0,
                                             "allocator.h", 0xd1) : 0;
        E238* pOldEnd = mpEnd;
        E238* pOldBegin = mpBegin;
        MoveC(pOldBegin, pOldEnd, pNewData);
        MoveD(pOldBegin, pOldEnd, pNewData);
        if (mpBegin)
            EA_Delete(mpBegin);
        unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize;
        mpCapacity = pNewData + n;
    }
}

// ---------------------------------------------------------------- serializers
extern void* __cdecl ObjectTemplateDB();       // 0x0067CB40
void  __cdecl ReadInt32(void* stream, void* out, int n, int flag);  // 0x0093A780
void  __cdecl SerializeElement(void* obj, void* v);   // 0x00F2D090
void  __cdecl DestroyElement4e0(void* p);             // 0x00DFD080
void  __cdecl DestroyElement238(void* p);             // 0x00DFDFE0
void  __cdecl CopyElement4e0(void* dst, const void* src);  // 0x00DFCCE0
void  __cdecl CopyElement238(void* dst, const void* src);  // 0x00DFE170
void* __cdecl GetStream(void* obj);            // vtable [0x18] accessor

// @ 0x00F2E370
unsigned Vec4e0::Serialize4e0(void* owner)
{
    unsigned count = 0;
    void* stream = GetStream(owner);
    ReadInt32(stream, &count, 1, 0);
    set_capacity(count);
    for (unsigned i = 0; i < count; ++i) {
        E4e0 tmp;
        SerializeElement(owner, &tmp);
        if (mpEnd < mpCapacity) {
            E4e0* slot = mpEnd++;
            CopyElement4e0(slot, &tmp);
        } else {
            Insert(mpEnd, tmp);
        }
        DestroyElement4e0(&tmp);
    }
    return count;
}

// @ 0x00F2E440
void SerializeVec188(void* vec, void* owner)
{
    unsigned count = 0;
    void* stream = GetStream(owner);
    ReadInt32(stream, &count, 1, 0);
    (void)vec;
    (void)count;
}

// @ 0x00F2E5D0
E238* Vec238::Insert(E238* position, const E238& value)
{
    if (mpEnd != mpCapacity) {
        E238* pValue = (E238*)&value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        if (mpEnd)
            *(E238*)mpEnd = *(mpEnd - 1);
        for (E238* p = mpEnd - 1; p > position; --p)
            *p = *(p - 1);
        *position = *pValue;
        ++mpEnd;
    } else {
        unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        unsigned nNewSize = nPrevSize ? nPrevSize * 2 : 1;
        E238* pNewData = nNewSize ? (E238*)EA_Alloc(nNewSize * 0x238, "Simulator", 0, 0,
                                                    "allocator.h", 0xd1) : 0;
        MoveC(mpBegin, position, pNewData);
        MoveD(mpBegin, position, pNewData);
        MoveC(position, mpEnd, pNewData + 1);
        MoveD(position, mpEnd, pNewData + 1);
        if (mpBegin)
            EA_Delete(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewData + 1;
        mpCapacity = pNewData + nNewSize;
    }
    return position;
}

// @ 0x00F2D7E0 -- serialize this 0x4e0 element from a cVarListSerializer / reader
int SerializeE4e0(void* self, void* reader)
{
    // Layout of the local frame is huge; behaviour: read via cVarListSerializer, then
    // adjust an embedded 0x34 element array and clamp positions.
    (void)self; (void)reader;
    return 0;
}

// ---------------------------------------------------------------- constraint evaluator
struct Constraint {
    unsigned mParameter;
    unsigned mType;
    int      mIntVal;
    int      mPad;
    void ctor(unsigned a, int b, unsigned c);   // 0x00558960
};

// @ 0x00F2DDE0
void EvaluateConstraints()
{
    Constraint c0;
    c0.ctor(0x2dd90af, 0, 0x366a930d);
    Constraint c1;
    c1.ctor(0x15e8afc8, 0, 1);
}

