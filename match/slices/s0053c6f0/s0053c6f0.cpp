// Swarm skin-paint paint-variable commands (copy/add-variable), the
// PaintVarModifier ctor and the 0x14-stride vector insert helpers.
// Unoptimized module.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int size_t;
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
extern "C" void* __cdecl memcpy(void*, const void*, size_t);
extern "C" void* __cdecl memmove(void*, const void*, size_t);
void* operator new[](size_t); void operator delete(void*); void operator delete[](void*);

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3& operator=(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
    float& operator[](uint32_t i) { return (&x)[i]; }
};

namespace EA { namespace ArgScript {
class cIParser { public:
#define PV(n) virtual void pv##n();
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37)
    virtual float GetFloat(const char*);                    // +0x98
    PV(39) PV(40) PV(41)
    virtual cSPVector3 GetVector(const char*);              // +0xa8
#undef PV
};
class cArguments { public:
    const char** MainArguments(int count);                                       // 0x838320
    const char** OptionArguments(const char* name, int count);                   // 0x838330
    const char** OptionArguments(const char* name, int* pCount, int min, int max); // 0x838130
    bool HasFlag(const char* flag);                                             // 0x8380b0
    const char* operator[](int i);
};
class cICommand { public: virtual void AddRef(); virtual void Release(); virtual void Cast(); };
class cCommandBase : public cICommand { public: cIParser* mParser; int mRefCount; };
} }

// An element of the paint-variable table (16 bytes): a point or a control
// record; mByteC is the kind tag, mByteD a count, mWord a float-vector index.
struct Entry16 {
    float x, y, z;
    uint8_t mByteC;
    uint8_t mByteD;
    uint16_t mWord;
};

// A modifier block appended to the paint state (20 bytes): four coefficients
// plus a kind/operand/op selector.
struct Entry20 {
    float m[4];
    uint8_t mA, mB, mC, mD;
};

// Allocator subobject carried by every container here (8 bytes).
struct Allocator { void* mpPool; void* mpReserved; };

template <typename T>
struct SimpleVector {
    T* mpBegin;             // +0x00
    T* mpEnd;               // +0x04
    T* mpCapacity;          // +0x08
    Allocator mAllocator;   // +0x0c
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }
    void resize(uint32_t n, const T& value);                // 0x5370b0
    void push_back(const T& value);                         // 0x537130 / 0x4547f0 / 0x4227f0
    void insert(T* position, uint32_t n, const T& value);   // 0x53cd80
};

// The paint-variable state hanging off the render object at +0x50.
struct EntryVec {
    SimpleVector<Entry16> mEntries;  // +0x00
    SimpleVector<Entry20> mMods;     // +0x14
    SimpleVector<float> mFloats;     // +0x28
};

class cPaintVarCommand : public EA::ArgScript::cCommandBase {
public:
    void* mpState;      // +0x0c  paint state owner
    uint8_t mSlot;      // +0x10
};

class cPaintCopyVar : public cPaintVarCommand {
public:
    void Execute(EA::ArgScript::cArguments& args);                              // 0x53c6f0
};

class cPaintAddVary : public cPaintVarCommand {
public:
    void Execute(EA::ArgScript::cArguments& args, const char** argv, int count); // 0x53c930
};

extern float kDefaultColor[3];      // 0x15e24bc
extern float _HK_REAL_ZERO;         // 0x1485378
extern float _HK_REAL_ONE;          // 0x1485720

inline EntryVec* PaintState(cPaintVarCommand* self)
{
    return *(EntryVec**)((char*)*(void**)((char*)self + 0xc) + 0x50);
}

// @ 0x0053c6f0
void cPaintCopyVar::Execute(EA::ArgScript::cArguments& args)
{
    const char** argv = args.MainArguments(2);
    cSPVector3 a;
    cSPVector3 b;
    a = mParser->GetVector(argv[0]);
    b = mParser->GetVector(argv[1]);
    EntryVec* vec = PaintState(this);
    if ((vec->mEntries.size() <= 0 || vec->mEntries[0].mByteC >= 0xfd) &&
        (vec->mEntries.size() <= 1 || vec->mEntries[1].mByteC >= 0xfe)) {
        if (vec->mEntries.size() < 2) {
            Entry16 def = { kDefaultColor[0], kDefaultColor[1], kDefaultColor[2], 0xff, 0, 0 };
            vec->mEntries.resize(2, def);
        }
        Entry16 e;
        e.x = a.x;
        e.y = a.y;
        e.z = a.z;
        e.mByteC = 0xfe;
        e.mByteD = 3;
        e.mWord = (uint16_t)vec->mFloats.size();
        vec->mEntries[1] = e;
        vec->mFloats.push_back(b[0]);
        vec->mFloats.push_back(b[1]);
        vec->mFloats.push_back(b[2]);
    }
}

// @ 0x0053c930
void cPaintAddVary::Execute(EA::ArgScript::cArguments& args, const char** argv, int count)
{
    EntryVec* vec = PaintState(this);
    if ((vec->mEntries.size() <= 0 || vec->mEntries[0].mByteC >= 0xfd) &&
        (vec->mEntries.size() <= 1 || vec->mEntries[1].mByteC >= 0xfe)) {
        if (vec->mEntries.size() < 2) {
            Entry16 def = { kDefaultColor[0], kDefaultColor[1], kDefaultColor[2], 0xff, 0, 0 };
            vec->mEntries.resize(2, def);
        }
        Entry16 e;
        e.x = kDefaultColor[0];
        e.y = kDefaultColor[1];
        e.z = kDefaultColor[2];
        e.mByteC = 0xff;
        e.mByteD = (uint8_t)count;
        e.mWord = (uint16_t)vec->mFloats.size();
        for (int i = 0; i < count; ++i) {
            float f = mParser->GetFloat(argv[i]);
            vec->mFloats.push_back(f);
        }
        const char** o = args.OptionArguments("vary", 1);
        if (o)
            e.x = mParser->GetFloat(o[0]);
        o = args.OptionArguments("offset", &count, 1, 2);
        if (o) {
            e.y = mParser->GetFloat(o[0]);
            e.z = (count == 2) ? mParser->GetFloat(o[1]) : e.y;
        }
        int n2 = (int)vec->mEntries.size();
        vec->mEntries.push_back(e);
        Entry20 blk;
        blk.m[0] = _HK_REAL_ZERO;
        blk.m[1] = _HK_REAL_ZERO;
        blk.m[2] = _HK_REAL_ZERO;
        blk.m[3] = _HK_REAL_ZERO;
        blk.mA = mSlot;
        blk.mB = (uint8_t)n2;
        blk.mC = 2;
        blk.mD = 0;
        if (args.HasFlag("add"))
            blk.mC = 1;
        if (args.HasFlag("scaleNorm") && vec->mEntries.size() >= 1 && vec->mEntries[0].mByteC == 0xfd)
            blk.m[0] = _HK_REAL_ONE;
        if (args.HasFlag("scalePos") && vec->mEntries.size() >= 2 && vec->mEntries[1].mByteC == 0xfe)
            blk.m[1] = _HK_REAL_ONE;
        vec->mMods.push_back(blk);
    }
}

// @ 0x0053cca0
void* PaintVarModifierCtor(void* p)
{
    *(void**)p = (void*)0x13f3f10;
    return p;
}

// ---------------------------------------------------------------------------
// container helpers used by the 0x14-stride insert
// ---------------------------------------------------------------------------
void* EASTL_Allocate(Allocator* alloc, uint32_t n, uint32_t align, uint32_t offset); // 0x42dee0
void* CopyRange(const void* first, const void* last, void* dst);                      // 0x47b3d0
void MoveBack(Entry20* first, Entry20* last, Entry20* dstEnd);                        // 0x537240

// @ 0x0053d1a0
void** UninitCopy20(void** out, Entry20* first, Entry20* last, Entry20* dst, uint8_t /*isPod*/)
{
    Entry20* d = dst;
    for (; first != last; ++first) {
        if (d) {
            d->m[0] = first->m[0]; d->m[1] = first->m[1]; d->m[2] = first->m[2]; d->m[3] = first->m[3];
            d->mA = first->mA; d->mB = first->mB; d->mC = first->mC; d->mD = first->mD;
        }
        ++d;
    }
    *out = d;
    return out;
}

// @ 0x0053d230
void* UninitFill20(Entry20* dst, int n, const Entry20* value, uint8_t /*isPod*/)
{
    Entry20* d = dst;
    Entry20* result = dst;
    for (; n != 0; --n) {
        result = d;
        if (d) {
            d->m[0] = value->m[0]; d->m[1] = value->m[1]; d->m[2] = value->m[2]; d->m[3] = value->m[3];
            d->mA = value->mA; d->mB = value->mB; d->mC = value->mC; d->mD = value->mD;
        }
        ++d;
    }
    return result;
}

// @ 0x0053cd80
template <>
void SimpleVector<Entry20>::insert(Entry20* position, uint32_t n, const Entry20& value)
{
    if ((uint32_t)((mpCapacity - mpEnd) / 20) < n) {
        // grow: double (or 1) the capacity, but at least old size + n
        uint32_t oldSize = (uint32_t)((mpEnd - mpBegin) / 20);
        uint32_t newCapacity = oldSize > 0 ? oldSize * 2 : 1;
        if (newCapacity <= oldSize + n)
            newCapacity = oldSize + n;
        Entry20* newBegin = newCapacity ? (Entry20*)EASTL_Allocate(&mAllocator, newCapacity * 20, 4, 0) : 0;
        Entry20* next = (Entry20*)CopyRange(mpBegin, position, newBegin);
        UninitFill20(next, n, &value, 0);
        next = (Entry20*)CopyRange(position, mpEnd, next + n);
        if (mpBegin && *(uint32_t*)((char*)mpBegin - 4) != 0)
            operator delete(mpBegin);
        mpBegin = newBegin;
        mpEnd = next;
        mpCapacity = (Entry20*)((char*)newBegin + newCapacity * 20);
    } else if (n != 0) {
        Entry20 saved(value);
        uint32_t tail = (uint32_t)((mpEnd - position) / 20);
        Entry20* oldEnd = mpEnd;
        if (n < tail) {
            Entry20* out;
            UninitCopy20((void**)&out, mpEnd - n, mpEnd, mpEnd, 0);
            mpEnd = mpEnd + n;
            Entry20* src = oldEnd - n;
            Entry20* dst = oldEnd;
            while (src != position) {
                --src;
                --dst;
                *dst = *src;
            }
            for (Entry20* p = position; p != position + n; ++p)
                *p = saved;
        } else {
            UninitFill20(mpEnd, n - tail, &saved, 0);
            mpEnd = mpEnd + (n - tail);
            MoveBack(position, oldEnd, mpEnd);
            mpEnd = mpEnd + tail;
            for (Entry20* p = position; p != oldEnd; ++p)
                *p = saved;
        }
    }
}
