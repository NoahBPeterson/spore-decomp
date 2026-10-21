// Slice s00a0bcf0 -- the 0x1c-byte anim-record vector algorithms (single-value
// insert, range insert), the 0x18-byte Sub range constructors, and the anim
// feedback-event dispatcher.  Object file: SPCreatureAnim/SPCreatureAnimManager.obj.
// Module flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

typedef unsigned int   uint;
typedef unsigned short uint16;

// ------------------------------------------------------------------ callees
void* __cdecl EAAllocate(uint size, const char* name, int, int, const char* file, int line); // 0x00f473a0
void  __cdecl operator_delete__(void* p);                                                    // 0x00f47380

const char* const kEastlFile =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

struct WideStr {                        // 3-pointer wide string (0x0c)
    uint16* begin;                      // +0x00
    uint16* end;                        // +0x04
    uint16* cap;                        // +0x08
    void AllocateSelf(int n);                        // 0x00429760
    void Assign(const uint16* b, const uint16* e);   // 0x00423650
};

extern uint16 gEmptyStr16_1667bac;      // 0x01667bac (shared empty wide string)
void* __cdecl memcpy_thunk(void* dst, const void* src, uint n);  // 0x011e0744

struct Rec {                            // 0x1c anim record
    float    f0;                        // +0x00
    float    f4;                        // +0x04
    uint32_t f8;                        // +0x08
    WideStr  s;                         // +0x0c
    uint32_t f18;                       // +0x18
    Rec();
};

// Inline clone of the compiler-inlined Rec copy constructor used by the 0x18
// element range constructor (0x00a0c090).  Write it as a real inline function so
// the optimiser expands the exact same WideStr copy sequence.
inline void __forceinline RecCloneInline(Rec* dst, const Rec* src)
{
    dst->f0 = src->f0;
    dst->f4 = src->f4;
    dst->f8 = src->f8;
    dst->s.begin = 0;
    dst->s.end = 0;
    dst->s.cap = 0;

    const uint16* sb = src->s.begin;
    const uint16* se = src->s.end;
    int chars = (int)(se - sb);
    if (chars <= 0) {
        dst->s.begin = &gEmptyStr16_1667bac;
        dst->s.end = &gEmptyStr16_1667bac;
        dst->s.cap = (uint16*)((char*)&gEmptyStr16_1667bac + 2);
    } else {
        uint16* buf = (uint16*)EAAllocate(2 * (chars + 1), "EASTL", 0, 0, kEastlFile, 0xd1);
        dst->s.begin = buf;
        dst->s.end = buf;
        dst->s.cap = buf + (chars + 1);
    }
    memcpy_thunk(dst->s.begin, sb, 2 * chars);
    dst->s.end = (uint16*)((char*)dst->s.begin + 2 * chars);
}

Rec* __cdecl FUN_00a095f0(Rec* first, Rec* last, Rec* dst);        // 0x00a095f0
Rec* __cdecl FUN_00a09630(Rec* first, Rec* last, Rec* dst);        // 0x00a09630
Rec* __cdecl FUN_00a09680(Rec* first, Rec* last, Rec* dst);        // 0x00a09680
Rec* __cdecl FUN_00a096e0(Rec* first, Rec* last, Rec* dst);        // 0x00a096e0
void __cdecl FUN_00a095a0(Rec* dst, Rec* last, const Rec* value);  // 0x00a095a0
void __cdecl FUN_00a09cc0(Rec* p, uint n, const Rec& a);           // 0x00a09cc0
void __cdecl RecConstruct(Rec* dst, const Rec* src);                // 0x00a093b0

// out-cursor range construct for 0x1c records
struct CursorRec { Rec* p; };
CursorRec* __cdecl FUN_00a09560(CursorRec* out, Rec* first, Rec* last, Rec* init); // 0x00a09560

// ------------------------------------------------------------- container types
struct ItemVec {                        // eastl::vector<Rec, sp_vector_allocator> (0x14)
    Rec*  mpBegin;                      // +0x00
    Rec*  mpEnd;                        // +0x04
    Rec*  mpCapacity;                   // +0x08
    int   mAllocator;                   // +0x0c
    int   mAllocator2;                  // +0x10

    Rec* DoInsertValue(Rec* position, const Rec& value);            // 0x00a0bcf0
    void DoInsertValues(Rec* position, uint n, const Rec& value);   // 0x00a0be60
    void AssignRange(const ItemVec* o);                             // 0x00a0b110
};

struct Sub {                            // 0x18
    ItemVec items;                      // +0x00
    float   f14;                        // +0x14
};

struct SubCursor { Sub* p; };

struct SubItemVec {                     // eastl::vector<Sub, sp_vector_allocator> (0x14)
    Sub* mpBegin;                       // +0x00
    Sub* mpEnd;                         // +0x04
    Sub* mpCapacity;                    // +0x08
    int  mAllocator;                    // +0x0c
};

// inlined 0x1c-record vector-fill helper (Sub::items copy leaves a hole for it)
SubItemVec* __cdecl ConstructSubCursor(SubItemVec* out, const Sub* first, const Sub* last, Sub* init); // 0x00a0c090
Sub* __cdecl ReverseCopySubs(Sub* first, Sub* last, Sub* dst);                                          // 0x00a0c230

// eastl::vector<Vector3, fixed_vector_allocator<16,...> > resize
struct Vec3 { float x, y, z; };
struct Vec3VecSmall {
    Vec3* mpBegin;
    Vec3* mpEnd;
    Vec3* mpCapacity;
    void  resize(uint n);               // 0x00a0ac10
};

// ------------------------------------------------------------- feedback event
struct FBNode {                         // rbtree node holding a cFeedbackEvent value
    void*    l;                         // +0x00
    void*    r;                         // +0x04
    void*    up;                        // +0x08
    uint32_t color;                     // +0x0c
    uint32_t key;                       // +0x10
    uint32_t pad14;                     // +0x14
    uint32_t pad18;                     // +0x18
    uint32_t pad1c;                     // +0x1c
    uint32_t pad20;                     // +0x20
    uint32_t pad24;                     // +0x24
    uint32_t pad28;                     // +0x28
    float    f2c;                       // +0x2c
    uint8_t  b30;                       // +0x30
    uint8_t  pad31;                     // +0x31
    uint8_t  b32;                       // +0x32
    uint8_t  pad33;                     // +0x33
    uint32_t pad34;                     // +0x34
    uint32_t pad38;                     // +0x38
    int      i3c;                       // +0x3c
    Sub*     subsBegin;                 // +0x40
    Sub*     subsEnd;                   // +0x44
};

struct FBMap {                          // rbtree<unsigned, pair<const unsigned, AutoRefCount<cFeedbackEvent>>>
    uint32_t pad0;                      // +0x00
    void*    anchor;                    // +0x04
    FBNode* find(FBNode** out, const uint32_t* key);  // 0x00e5c780
};
extern FBMap g_fbMap_1551a68;           // 0x01551a68

// anim_qb playback entry points
void* __cdecl FUN_00a01a00(void* qb, void* def, const Vec3* pos, int count); // 0x00a01a00
void  __cdecl FUN_00a001f0(void* qb, void* h, int a);                        // 0x00a001f0
void  __cdecl FUN_00a00240(void* qb, void* h, unsigned char v);               // 0x00a00240
void  __cdecl FUN_00a00290(void* qb, void* h, float v);                       // 0x00a00290
void  __cdecl FUN_00a002f0(void* qb, void* h, int v);                         // 0x00a002f0
void  __cdecl FUN_009ffee0(void* qb, void* h, float v);                       // 0x009ffee0
void  __cdecl FUN_00a00080(void* qb, void* h, uint32_t id);                   // 0x00a00080
void  __cdecl FUN_00a00450(void* qb, void* h, void* cb, uint32_t id);         // 0x00a00450
void  __cdecl FUN_00a05ee0();                                                 // 0x00a05ee0
bool  __cdecl qb_enable(void* qb, int animID);                                // 0x00a01b50

extern float  g_kZero_1485378;          // 0x01485378
extern float  g_kNegOne_13eb1bc;        // 0x013eb1bc
extern void*  g_pRandom_166cd30;        // 0x0166cd30 (EA::Random::RandomMersenneTwister)
double RandomGenerateDouble(void* self);   // 0x009362d0 (ecx = singleton)

struct AnimFbOwner {                    // `this` for the feedback dispatch
    uint32_t pad000[0x184 / 4];         // +0x000
    void*    mpQB;                      // +0x184
    void*    mpFbTarget;                // +0x188 (unused here)
    char*    mpAnimDefHolder;           // +0x18c (holder whose +0x1c -> +0x14 is the def)
    uint32_t c640(uint32_t id, uint32_t* outIndex);   // 0x00a0c640
    void     c670(uint32_t id, uint32_t* outIndex);   // 0x00a0c670
};

// =========================================================== 0x00a0bcf0
// @ 0x00a0bcf0
Rec* ItemVec::DoInsertValue(Rec* position, const Rec& value)
{
    Rec* end = mpEnd;
    if (end != mpCapacity) {
        if (position <= &value && &value < end)
            position = (Rec*)((char*)&value + 0x1c);
        if (end != 0) {
            // Construct the slot one past the end from the last live element, then
            // shift [position, end-1) one to the right and store `value` at position.
            RecConstruct(end, (Rec*)((char*)end - 0x1c));
        }
        FUN_00a096e0(position, (Rec*)((char*)end - 0x1c), end);
        position->f0 = ((Rec*)&value)->f0;
        position->f4 = ((Rec*)&value)->f4;
        position->f8 = ((Rec*)&value)->f8;
        if (&position->s != &((Rec*)&value)->s)
            position->s.Assign(((Rec*)&value)->s.begin, ((Rec*)&value)->s.end);
        mpEnd = (Rec*)((char*)mpEnd + 0x1c);
        return 0;
    }

    uint nOld = (uint)(((char*)end - (char*)mpBegin) / 0x1c);
    uint nCap;
    if (nOld == 0)
        nCap = 1;
    else
        nCap = nOld * 2;
    Rec* pNew;
    if (nCap == 0)
        pNew = 0;
    else
        pNew = (Rec*)EAAllocate(nCap * 0x1c, "EASTL", 0, 0, kEastlFile, 0xd1);

    Rec* begin = mpBegin;
    Rec* pos = FUN_00a095f0(begin, position, pNew);
    FUN_00a09630(begin, position, pNew);
    if (pos != 0)
        RecConstruct(pos, (const Rec*)&value);
    Rec* oldEnd = mpEnd;
    Rec* newEnd = FUN_00a095f0(position, oldEnd, (Rec*)((char*)pos + 0x1c));
    FUN_00a09630(position, oldEnd, (Rec*)((char*)pos + 0x1c));
    begin = mpBegin;
    if (begin != 0 && ((int*)begin)[-1] != 0)
        operator_delete__(begin);
    mpEnd = newEnd;
    mpBegin = pNew;
    mpCapacity = (Rec*)((char*)pNew + nCap * 0x1c);
    return 0;
}

// =========================================================== 0x00a0be60
// @ 0x00a0be60
void ItemVec::DoInsertValues(Rec* position, uint n, const Rec& value)
{
    uint size = (uint)(((char*)mpEnd - (char*)mpBegin) / 0x1c);
    if (n > size) {
        uint newCap = (uint)(((char*)mpEnd - (char*)mpBegin) / 0x1c) * 2;
        if (size == 0)
            newCap = 1;
        uint need = size + n;
        if (newCap > need)
            need = newCap;
        Rec* pNew;
        if (need == 0)
            pNew = 0;
        else
            pNew = (Rec*)EAAllocate(need * 0x1c, "EASTL", 0, 0, kEastlFile, 0xd1);
        Rec* begin = mpBegin;
        Rec* pos = FUN_00a095f0(begin, position, pNew);
        FUN_00a09630(begin, position, pNew);
        FUN_00a09cc0(pos, n, value);
        Rec* mid = (Rec*)((char*)pos + n * 0x1c);
        Rec* oldEnd = mpEnd;
        Rec* newEnd = FUN_00a095f0(position, oldEnd, mid);
        FUN_00a09630(position, oldEnd, mid);
        begin = mpBegin;
        if (begin != 0 && ((int*)begin)[-1] != 0)
            operator_delete__(begin);
        mpEnd = newEnd;
        mpBegin = pNew;
        mpCapacity = (Rec*)((char*)pNew + need * 0x1c);
        return;
    }
    if (n == 0)
        return;

    CursorRec buf;
    FUN_00a09560(&buf, (Rec*)&value, (Rec*)((char*)&value + 0x1c), 0);

    Rec* end = mpEnd;
    uint have = (uint)(((char*)end - (char*)position) / 0x1c);
    Rec* src;
    if (n < have) {
        // Shift the tail right, then overwrite the gap with `value`.
        src = (Rec*)((char*)end - n * 0x1c);
        FUN_00a09560(&buf, src, end, end);
        mpEnd = (Rec*)((char*)mpEnd + n * 0x1c);
        FUN_00a096e0(position, src, end);
        src = (Rec*)((char*)position + n * 0x1c);
    } else {
        FUN_00a09cc0(end, n - have, buf.p ? *buf.p : value);
        Rec* oldEnd = mpEnd;
        mpEnd = (Rec*)((char*)mpEnd + (n - have) * 0x1c);
        FUN_00a09560(&buf, position, oldEnd, (Rec*)mpEnd);
        mpEnd = (Rec*)((char*)mpEnd + have * 0x1c);
        src = position;
    }
    FUN_00a095a0(position, src, (const Rec*)&value);
    if (buf.p != 0 && ((int*)buf.p)[-1] != 0)
        operator_delete__(buf.p);
}

// =========================================================== 0x00a0c090
// @ 0x00a0c090
SubItemVec* __cdecl ConstructSubCursor(SubItemVec* out, const Sub* first, const Sub* last, Sub* init)
{
    out->mpBegin = init;
    for (; first != last; first = (const Sub*)((const char*)first + 0x18)) {
        Sub* d = out->mpBegin;
        if (d != 0) {
            uint n = (uint)(((char*)first->items.mpEnd - (char*)first->items.mpBegin) / 0x1c);
            Rec* buf;
            if (n == 0)
                buf = 0;
            else
                buf = (Rec*)EAAllocate(n * 0x1c, "EASTL", 0, 0, kEastlFile, 0xd1);
            d->items.mpCapacity = (Rec*)((char*)buf + n * 0x1c);
            d->items.mpBegin = buf;
            d->items.mpEnd = buf;
            for (Rec* s = first->items.mpBegin; s != first->items.mpEnd; ++s) {
                Rec* dst = d->items.mpEnd;
                if (dst != 0)
                    RecCloneInline(dst, s);
                d->items.mpEnd = (Rec*)((char*)dst + 0x1c);
            }
            d->items.mpEnd = (Rec*)((char*)buf + n * 0x1c);
            d->f14 = first->f14;
        }
        out->mpBegin = (Sub*)((char*)out->mpBegin + 0x18);
    }
    return out;
}

// =========================================================== 0x00a0c230
// @ 0x00a0c230
Sub* __cdecl ReverseCopySubs(Sub* first, Sub* last, Sub* dst)
{
    if (last != first) {
        do {
            last = (Sub*)((char*)last - 0x18);
            dst = (Sub*)((char*)dst - 0x18);
            dst->items.AssignRange(&last->items);
            dst->f14 = last->f14;
        } while (last != first);
    }
    return dst;
}

// =========================================================== 0x00a0c270
// @ 0x00a0c270
uint32_t __cdecl FUN_00a0c270(AnimFbOwner* self, uint32_t id, uint32_t* outIndex)
{
    FBNode* node;
    g_fbMap_1551a68.find(&node, &id);
    if (node == (FBNode*)&g_fbMap_1551a68.anchor)
        return 0;
    if (node->subsBegin == node->subsEnd)
        return 0;

    uint32_t subCount = (uint32_t)(((char*)node->subsEnd - (char*)node->subsBegin) / 0x18);
    uint32_t idx = 0;
    if (subCount > 1) {
        if (outIndex != 0 && *outIndex != 0xffffffffu && *outIndex < subCount) {
            idx = *outIndex;
        } else {
            double r = RandomGenerateDouble(g_pRandom_166cd30);
            Sub* subs = node->subsBegin;
            for (uint32_t i = 0; i < subCount; ++i) {
                if (subs[i].f14 > r) {
                    idx = i;
                    break;
                }
            }
        }
    }
    if (outIndex != 0)
        *outIndex = idx;

    Sub* chosen = (Sub*)((char*)node->subsBegin + idx * 0x18);
    if (chosen->items.mpBegin == chosen->items.mpEnd)
        return 0;

    uint32_t n = (uint32_t)(((char*)chosen->items.mpEnd - (char*)chosen->items.mpBegin) / 0x1c);
    Vec3 buf[16];
    Vec3VecSmall tmp;
    tmp.mpBegin = buf;
    tmp.mpEnd = buf;
    tmp.mpCapacity = buf + 16;
    tmp.resize(n);

    for (uint32_t i = 0; i < n; ++i) {
        Rec* s = (Rec*)((char*)chosen->items.mpBegin + i * 0x1c);
        buf[i].x = s->f8;
        buf[i].y = s->f4;
        buf[i].z = s->f0;
    }

    char* holder = self->mpAnimDefHolder;
    void* def = *(void**)(*(char**)holder + 0x14);
    void* qb = self->mpQB;
    void* h = FUN_00a01a00(qb, def, buf, (int)n);
    FUN_00a001f0(qb, h, 0);
    FUN_00a00240(qb, h, node->b30);
    float f2c = node->f2c;
    if (f2c >= 0.0f)
        FUN_00a00290(qb, h, f2c);
    FUN_00a00080(qb, h, id);

    if (node->i3c == 1) {
        FUN_00a002f0(qb, h, 1);
        FUN_009ffee0(qb, h, g_kNegOne_13eb1bc);
        if (node->b32 != 0 && subCount > 1)
            FUN_00a00450(qb, h, (void*)&FUN_00a05ee0, id);
    } else if (node->i3c == 2) {
        FUN_00a002f0(qb, h, 0);
        FUN_009ffee0(qb, h, g_kNegOne_13eb1bc);
    } else {
        FUN_00a002f0(qb, h, 0);
        FUN_009ffee0(qb, h, 1.0f);
    }

    if (tmp.mpBegin != 0 && tmp.mpBegin != buf)
        operator_delete__(tmp.mpBegin);
    return (uint32_t)(uint)h;
}

// =========================================================== 0x00a0c640
// @ 0x00a0c640
uint32_t AnimFbOwner::c640(uint32_t id, uint32_t* outIndex)
{
    uint32_t h = FUN_00a0c270(this, id, outIndex);
    qb_enable(mpQB, (int)h);
    return h;
}

// =========================================================== 0x00a0c670
// @ 0x00a0c670
void AnimFbOwner::c670(uint32_t id, uint32_t* outIndex)
{
    FUN_00a0c270(this, id, outIndex);
}
