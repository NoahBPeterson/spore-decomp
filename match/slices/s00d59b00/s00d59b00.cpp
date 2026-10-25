// Slice s00d59b00: cFollowBehavior steering (Approach), two eastl partition/sort helpers and
// four eastl vector routines (Insert/Assign for 8-, 12- and 16-byte elements).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc).
#include "types.h"
#include <math.h>

typedef unsigned int   uint32;
typedef unsigned short uint16;

void* __cdecl operator_new(uint32 size, const char* pName, int a, int b, const char* pAlloc, uint32 line); // 0x00f473a0
void  __cdecl operator_delete(void* p);                                                                    // 0x00f47380

extern const char g_szSimulator[];        // 0x013f09b4 "Simulator"
extern const char g_szAllocatorH[];       // 0x013ebb38 eastl allocator.h path
extern const float g_HK_REAL_ZERO;        // 0x01485378
extern const float g_HK_REAL_ONE;         // 0x01485720
extern const float g_zero_13eb1bc;        // 0x013eb1bc (0.0f)
extern const float g_acos_one;            // 0x0169ec80 quaternion/axis constant fed to FUN_0059aed0

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------------------------- pair<quat, Vector3>
struct QuatPair {
    float q[4];      // +0x00
    Vec3  v;         // +0x10
};

// ---------------------------------------------------------------------------------- steering object
struct cSteerObj {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const QuatPair* GetOrientation();          // +0x30
    virtual void v34();
    virtual void v38();
    virtual void SetOrientation(const QuatPair* q);    // +0x3c
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58();
    virtual const Vec3* GetDirection(Vec3* out);       // +0x5c
};

// ---------------------------------------------------------------------------------- ref-counted sort element
struct IRefCounted {
    virtual void AddRef();                 // slot 0
    virtual void Release();                // slot 1
};

// Minimal intrusive ref-counted pointer (eastl::intrusive_ptr-alike).
struct IntrusivePtr {
    IRefCounted* mpPtr;
    IntrusivePtr() : mpPtr(0) {}
    IntrusivePtr(IRefCounted* p) : mpPtr(p) { if (mpPtr) mpPtr->AddRef(); }
    IntrusivePtr(const IntrusivePtr& o) : mpPtr(o.mpPtr) { if (mpPtr) mpPtr->AddRef(); }
    ~IntrusivePtr() { if (mpPtr) mpPtr->Release(); }
    IntrusivePtr& operator=(const IntrusivePtr& o)
    {
        if (mpPtr != o.mpPtr)
        {
            if (o.mpPtr) o.mpPtr->AddRef();
            IRefCounted* old = mpPtr;
            mpPtr = o.mpPtr;
            if (old) old->Release();
        }
        return *this;
    }
};

// element layout used by the partition helper: position triple at +0xc0
struct SortElem {
    uint32 pad00[0xc0 / 4];
    Vec3   mPosition;      // +0xc0
};

// ---------------------------------------------------------------------------------- callees
void* __stdcall FUN_00d58510(QuatPair* pOut, void* pA, void* pB);      // 0x00d58510  (ret 0xc)
Vec3* __cdecl FUN_0059aed0(Vec3* out, const float* q, const Vec3* v);  // 0x0059aed0  rotate vector by quat
QuatPair __cdecl FUN_005b2500(const QuatPair* a, const QuatPair* b, float t); // 0x005b2500 Slerp
bool  __cdecl FUN_00b3d550(const QuatPair* q);                         // 0x00b3d550
void  __cdecl FUN_00b2af00(void* pA, void* pB);                        // 0x00b2af00
void  __cdecl FUN_00d597b0(int* first, int* last, Vec3 origin);        // 0x00d597b0 make_heap
void  __cdecl FUN_00d592e0(int* first, void* comp, int len, int hole, IntrusivePtr value, Vec3 origin); // 0x00d592e0 adjust_heap
void  __cdecl FUN_00d59820(int* first, int* last, Vec3 origin);        // 0x00d59820 sort_heap
void* __cdecl FUN_00d59410(uint32 n, const void* srcBegin, const void* srcEnd);  // 0x00d59410 (thiscall, ret 0xc)
void* __cdecl FUN_00b84c80(const void* first, const void* last, void* dst);      // 0x00b84c80 (ret 0xc)
void* __cdecl FUN_00951740(void** ppOut, const void* src, const void* srcEnd, void* dst, void* dstEnd); // 0x00951740
void  __cdecl FUN_00edba80(void* first, void* last, void* dst);        // 0x00edba80 copy_backward (ret 0xc)
void* __cdecl FUN_00d577b0(void* first, void* last, void* dst);        // 0x00d577b0 16-byte copy loop
void* __cdecl FUN_004554f0(void* first, void* last, void* dst);        // 0x004554f0 8-byte copy loop

struct Elem8;
struct Elem16;

// the three container routines are thiscall members: the caller leaves the vector in ECX.
struct VecHeader {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCapacity;   // +0x08
    void* mpPad0c;      // +0x0c (unused by these routines)
    void* mpInline;     // +0x10 (inline buffer start; mpBegin == this means inline storage)
    void* __thiscall Insert8(Elem8* pos, const Elem8* pValue);      // 0x00d59f00
    void* __thiscall Insert16(Elem16* pos, const Elem16* pValue);   // 0x00d5a140
    void* __thiscall Assign12(void** src);                          // 0x00d5a010
    void* __thiscall Grow12(uint32 n, const char* first, const char* last); // 0x00d59410 (this = vector)
};

struct Elem8 {
    uint32 a;      // +0x00
    uint32 b;      // +0x04
};

struct Elem16 {
    uint32 a;      // +0x00
    float  b;      // +0x04
    float  c;      // +0x08
    float  d;      // +0x0c
};

// ---------------------------------------------------------------------------------- position comparator
// FUN_00ac0730 is a thiscall function: ECX = the reference position (the by-value Vec3 origin) and the
// two stack arguments are element positions (+0xc0 of each element).
struct OriginCompare {
    Vec3 mPosition;        // +0x00 (ECX points at the origin)
    bool __thiscall Compare(void* pA, void* pB);   // 0x00ac0730 (ret 8)
};

// Position (+0xc0) of a ref-counted sort element stored in a pointer slot.
static inline void* PosOf(const int* pSlot)
{
    return *pSlot ? (void*)(*pSlot + 0xc0) : 0;
}

// cFollowBehavior::Approach -- steer the current orientation toward the target orientation by an
// angular step proportional to the travelled distance; returns the clamped facing dot * speed.
// @ 0x00d59b00
float __stdcall cFollowBehavior_Approach(void* pThis, const void* pTarget, float dt, float speed, float turn)
{
    QuatPair target;
    FUN_00d58510(&target, pThis, (void*)pTarget);

    Vec3 dir;
    ((cSteerObj*)pThis)->GetDirection(&dir);

    Vec3 rotated;
    FUN_0059aed0(&rotated, &g_acos_one, (const Vec3*)&target);

    float dot = dir.x * rotated.x + dir.y * rotated.y + dir.z * rotated.z;
    if (dot > g_HK_REAL_ONE)
        dot = g_HK_REAL_ONE;
    if (dot < g_zero_13eb1bc)
        dot = g_zero_13eb1bc;

    float result = dot * speed;
    float angle = (float)acos((double)dot);
    if (angle < 3.402823466e+38f)
    {
        float t;
        if (angle <= g_HK_REAL_ZERO)
        {
            t = g_HK_REAL_ONE;
        }
        else
        {
            t = (dt * turn) / angle;
            if (t > g_HK_REAL_ONE)
                t = g_HK_REAL_ONE;
        }
        QuatPair q = FUN_005b2500(((cSteerObj*)pThis)->GetOrientation(), &target, t);
        if (FUN_00b3d550(&q))
            ((cSteerObj*)pThis)->SetOrientation(&q);
    }
    return result;
}

// Distance-keyed partition (quicksort step) over ref-counted pointer slots. The pivot is a
// by-value ref-counted pointer (released by this function's epilogue).
// @ 0x00d59d00
int* __cdecl FUN_00d59d00(int* first, int* last, IntrusivePtr pOwner, Vec3 origin)
{
    for (;;)
    {
        while (((OriginCompare*)&origin)->Compare(PosOf(first),
                                                  pOwner.mpPtr ? (void*)((char*)pOwner.mpPtr + 0xc0) : 0))
        {
            ++first;
        }
        for (;;)
        {
            --last;
            void* elemPos = PosOf(last);
            void* ownerPos = pOwner.mpPtr ? (void*)((char*)pOwner.mpPtr + 0xc0) : 0;
            if (!((OriginCompare*)&origin)->Compare(ownerPos, elemPos))
                break;
        }
        if (first >= last)
            break;
        FUN_00b2af00(first, last);
        ++first;
    }
    return first;
}

// eastl partial_sort: heap of [begin, middle), scan [middle, last), then sort_heap.
// @ 0x00d59da0
void __cdecl FUN_00d59da0(int* begin, int* middle, int* last, Vec3 pos)
{
    FUN_00d597b0(begin, middle, pos);
    for (int* p = middle; p < last; ++p)
    {
        if (((OriginCompare*)&pos)->Compare(PosOf(p), PosOf(begin)))
        {
            IntrusivePtr* pp = (IntrusivePtr*)p;
            IntrusivePtr* bp = (IntrusivePtr*)begin;
            IntrusivePtr value(*pp);
            *pp = *bp;
            FUN_00d592e0(begin, 0, (int)(middle - begin), 0, value, pos);
        }
    }
    FUN_00d59820(begin, middle, pos);
}

// eastl vector<8-byte element>::Insert(pos, value).
// @ 0x00d59f00
void* VecHeader::Insert8(Elem8* pos, const Elem8* pValue)
{
    Elem8* const end = (Elem8*)mpEnd;
    if (end != (Elem8*)mpCapacity)
    {
        const Elem8* value = pValue;
        if (value >= pos && value < end)
            value = value + 1;
        if (end)
            *end = end[-1];
        Elem8* q = (Elem8*)mpEnd;
        Elem8* s = q - 1;
        while (s != pos)
        {
            *--q = *--s;
        }
        uint32 a = value->a;
        pos->a = a;
        pos->b = value->b;
        mpEnd = (Elem8*)mpEnd + 1;
        return (void*)(uintptr_t)a;
    }
    else
    {
        uint32 n = (uint32)(int)(end - (Elem8*)mpBegin);
        if (n > 0)
            n = n * 2;
        else
            n = 1;
        Elem8* pNew;
        if (n)
            pNew = (Elem8*)operator_new(n * 8, g_szSimulator, 0, 0, g_szAllocatorH, 0xd1);
        else
            pNew = 0;
        Elem8* p = (Elem8*)FUN_004554f0(mpBegin, pos, pNew);
        if (p)
            *p = *pValue;
        p = (Elem8*)FUN_004554f0(pos, mpEnd, p + 1);
        if (mpBegin != 0 && mpBegin != mpInline)
            operator_delete(mpBegin);
        mpBegin = pNew;
        mpEnd = p;
        mpCapacity = (char*)pNew + n * 8;
    }
}
// ---------------------------------------------------------------------------------- 00d5a010
// eastl vector<12-byte element>::Assign(const vector&).
// @ 0x00d5a010
void* VecHeader::Assign12(void** src)
{
    if (src == (void**)this)
        return this;
    char* srcBegin = (char*)src[0];
    int n = (int)(((char*)src[1] - srcBegin) / 12);
    char* selfBegin = (char*)mpBegin;
    if ((uint32)n > (uint32)(int)(((char*)mpCapacity - selfBegin) / 12))
    {
        void* buf = Grow12((uint32)n, srcBegin, (const char*)src[1]);
        if (selfBegin != 0 && selfBegin != (char*)mpInline)
            operator_delete(selfBegin);
        mpCapacity = (char*)buf + n * 12;
        mpBegin = buf;
        mpEnd = (char*)buf + n * 12;
        return this;
    }
    int have = (int)(((char*)mpEnd - selfBegin) / 12);
    if ((uint32)n > (uint32)have)
    {
        FUN_00b84c80(srcBegin, srcBegin + have * 12, selfBegin);
        char* pout = (char*)src[1];
        char* mid = (char*)mpBegin + (int)(((char*)mpEnd - (char*)mpBegin) / 12) * 12;
        FUN_00951740((void**)&pout, mid, pout, (char*)mpEnd, (char*)src[1]);
        mpEnd = (char*)mpBegin + n * 12;
        return this;
    }
    FUN_00b84c80(srcBegin, src[1], selfBegin);
    mpEnd = (char*)mpBegin + n * 12;
    return this;
}

// ---------------------------------------------------------------------------------- 00d5a140
// eastl vector<16-byte element>::Insert(pos, value).
// @ 0x00d5a140
void* VecHeader::Insert16(Elem16* pos, const Elem16* pValue)
{
    Elem16* const end = (Elem16*)mpEnd;
    if (end != (Elem16*)mpCapacity)
    {
        const Elem16* value = pValue;
        if (value >= pos && value < end)
            value = value + 1;
        if (end)
        {
            float f0 = end[-1].b;
            float f1 = end[-1].c;
            float f2 = end[-1].d;
            end->a = end[-1].a;
            end->b = f0;
            end->c = f1;
            end->d = f2;
        }
        FUN_00edba80(pos, (Elem16*)mpEnd - 1, (Elem16*)mpEnd);
        *(uint32*)&pos->a = *(const uint32*)&value->a;
        uint32 b = *(const uint32*)&value->b;
        *(uint32*)&pos->b = b;
        *(uint32*)&pos->c = *(const uint32*)&value->c;
        *(uint32*)&pos->d = *(const uint32*)&value->d;
        mpEnd = (Elem16*)mpEnd + 1;
        return (void*)(uintptr_t)b;
    }
    else
    {
        uint32 n = (uint32)(int)(end - (Elem16*)mpBegin);
        if (n > 0)
            n = n * 2;
        else
            n = 1;
        Elem16* pNew;
        if (n)
            pNew = (Elem16*)operator_new(n << 4, g_szSimulator, 0, 0, g_szAllocatorH, 0xd1);
        else
            pNew = 0;
        Elem16* p = (Elem16*)FUN_00d577b0(mpBegin, pos, pNew);
        if (p)
        {
            p->a = pValue->a;
            p->b = pValue->b;
            p->c = pValue->c;
            p->d = pValue->d;
        }
        Elem16* oldEnd = (Elem16*)mpEnd;
        p = (Elem16*)FUN_00d577b0(pos, oldEnd, p + 1);
        if (mpBegin != 0 && mpBegin != mpInline)
            operator_delete(mpBegin);
        mpEnd = p;
        mpCapacity = (char*)pNew + (n << 4);
        mpBegin = pNew;
    }
}
