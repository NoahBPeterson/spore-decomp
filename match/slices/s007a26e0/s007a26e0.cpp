// slice s007a26e0
// Faithful C++ reconstruction (MSVC x86, cl 15.00 /O2 /MD /Gy /EHsc /TP).
//
// The three functions are virtual converters of a polymorphic bone-conversion
// functor.  They move a vector of "pair groups" out of the destination object,
// reserve room in the destination, convert every source pair through the
// functor's per-format converter and append the two converted shared pointers
// (tagged with the source pair's id) to the destination group(s).
//
// Types mirror the EASTL containers used by the original code:
//   Pair   - { refcounted pointer, int tag }            (8 bytes)
//   Group  - eastl::vector<Pair, sp_vector_allocator>   (20 bytes)
//   Group2 - { Group a; Group b; }                      (40 bytes)
// The per-object converters (out records) are 0x70-byte structures which the
// original fills through the external helpers and destroys through the
// out-of-line destructor at 0x0079aeb0.

#include <intrin.h>

// ---- external helpers (this in ecx, remaining arguments on the stack) ----
extern "C" {
void __fastcall FUN_007a0b90(void* self, int, void* other);
void __fastcall FUN_007a1100(void* self, int, int count);
void __fastcall FUN_0079af80(void* self, int, int count);
void __fastcall FUN_0079f4e0(void* self, int, void* pos, void* value);
void __fastcall FUN_0079aeb0(void* self);
void __fastcall FUN_0060d210(void** slot);
void __fastcall FUN_007a1a80(void* self, int, void* source, void* out);
void __fastcall FUN_007a1bc0(void* self, int, void* source, void* out);
void __fastcall FUN_007a1d00(void* self, int, void* source, void* outA, void* outB);
void __fastcall FUN_0079b0d0(void* self, int, void* begin, void* end);  // destroy range of Group

// ---- ordinary helpers ----
void __cdecl FUN_f47380(void* block);                   // operator delete
}

struct Pair {
    void* object;   // +0x00  refcounted pointer (refcount at object + 4)
    int   tag;      // +0x04
};

struct Group {                 // eastl::vector<Pair, sp_vector_allocator>
    Pair* begin;               // +0x00
    Pair* end;                 // +0x04
    Pair* cap;                 // +0x08
    int   alloc0;              // +0x0c
    int   alloc1;              // +0x10
};

struct Group2 {
    Group a;                   // +0x00
    Group b;                   // +0x14
};

struct GroupVec {              // vector of 20-byte groups
    Group* begin;
    Group* end;
    Group* cap;
};

struct Group2Vec {             // vector of 40-byte group pairs
    Group2* begin;
    Group2* end;
    Group2* cap;
};

struct OutRecord {             // 0x70-byte per-object conversion result
    void* sp0;                 // +0x00  shared pointer
    void* sp1;                 // +0x04  shared pointer
    void* u08;                 // +0x08
    void* u0c;                 // +0x0c
    void* u10;                 // +0x10
    void* u14;                 // +0x14
    int   u18;                 // +0x18
    int   u1c;                 // +0x1c
    void* arr20;               // +0x20  array begin
    void* u24;                 // +0x24
    void* u28;                 // +0x28
    int   u2c;                 // +0x2c
    int   u30;                 // +0x30
    int   v34;                 // +0x34  initialised to 4 by the type
    int   v38;                 // +0x38
    int   v3c;                 // +0x3c
    int   v40;                 // +0x40
    int   v44;                 // +0x44
    void* arr48;               // +0x48  array begin
    void* arr4c;               // +0x4c
    void* arr50;               // +0x50
    int   u54;                 // +0x54
    int   u58;                 // +0x58
    int   v5c;                 // +0x5c  initialised to 4 by the type
    int   v60;                 // +0x60
    int   v64;                 // +0x64
    int   v68;                 // +0x68
    int   v6c;                 // +0x6c
};

struct Converter {
    void ConvertPairs1(GroupVec* dest);
    void ConvertPairs2(GroupVec* dest);
    void ConvertPairPairs(Group2Vec* dest);
};

static void InitOut(OutRecord& o)
{
    o.sp0 = 0;
    o.sp1 = 0;
    o.u08 = 0;
    o.u0c = 0;
    o.u10 = 0;
    o.u14 = 0;
    o.u18 = 0;
    o.u1c = 0;
    o.arr20 = 0;
    o.u24 = 0;
    o.u28 = 0;
    o.u2c = 0;
    o.u30 = 0;
    o.v34 = 4;
    o.v38 = 0;
    o.v3c = 0;
    o.v40 = 0;
    o.v44 = 0;
    o.arr48 = 0;
    o.arr4c = 0;
    o.arr50 = 0;
    o.u54 = 0;
    o.u58 = 0;
    o.v5c = 4;
    o.v60 = 0;
    o.v64 = 0;
    o.v68 = 0;
    o.v6c = 0;
}

static inline void RetainObject(void* object)
{
    _InterlockedIncrement((volatile long*)object + 1);
}

// Append {object, tag} to the group, mirroring the inlined eastl::vector
// push_back: the temporary pair takes one reference, the slot another, and the
// temporary's destructor drops its reference again.
static void PushPair(Group* group, void* object, int tag)
{
    Pair temp;
    temp.object = object;
    temp.tag = tag;
    RetainObject(object);
    if (group->end < group->cap) {
        Pair* slot = group->end;
        group->end = slot + 1;
        if (slot != 0) {
            slot->object = object;
            RetainObject(object);
            slot->tag = tag;
        }
    } else {
        FUN_0079f4e0(group, 0, group->end, &temp);
    }
    FUN_0060d210(&temp.object);
}

static void DestroyGroupVector(GroupVec* v)
{
    FUN_0079b0d0(v, 0, v->begin, v->end);
    if (v->begin != 0 && ((int*)v->begin)[-1] != 0)
        FUN_f47380(v->begin);
}

// @ 0x007a26e0
void Converter::ConvertPairs1(GroupVec* dest)
{
    GroupVec source;
    source.begin = 0;
    source.end = 0;
    source.cap = 0;
    FUN_007a0b90(&source, 0, dest);

    int groupCount = (int)(source.end - source.begin);
    FUN_007a1100(dest, 0, groupCount);

    OutRecord out;
    InitOut(out);

    for (int i = 0; i < groupCount; ++i) {
        Group* target = dest->begin + i;
        Group* group = source.begin + i;
        int pairCount = (int)(group->end - group->begin);
        FUN_0079af80(target, 0, pairCount);
        for (int j = 0; j < pairCount; ++j) {
            Pair* pair = group->begin + j;
            FUN_007a1a80(this, 0, pair->object, &out);
            if (out.sp0 != 0)
                PushPair(target, out.sp0, pair->tag);
            if (out.sp1 != 0)
                PushPair(target, out.sp1, pair->tag);
        }
    }

    FUN_0079aeb0(&out);
    DestroyGroupVector(&source);
}

// @ 0x007a2a00
void Converter::ConvertPairs2(GroupVec* dest)
{
    GroupVec source;
    source.begin = 0;
    source.end = 0;
    source.cap = 0;
    FUN_007a0b90(&source, 0, dest);

    int groupCount = (int)(source.end - source.begin);
    FUN_007a1100(dest, 0, groupCount);

    OutRecord out;
    InitOut(out);

    for (int i = 0; i < groupCount; ++i) {
        Group* target = dest->begin + i;
        Group* group = source.begin + i;
        int pairCount = (int)(group->end - group->begin);
        FUN_0079af80(target, 0, pairCount);
        for (int j = 0; j < pairCount; ++j) {
            Pair* pair = group->begin + j;
            FUN_007a1bc0(this, 0, pair->object, &out);
            if (out.sp0 != 0)
                PushPair(target, out.sp0, pair->tag);
            if (out.sp1 != 0)
                PushPair(target, out.sp1, pair->tag);
        }
    }

    FUN_0079aeb0(&out);
    DestroyGroupVector(&source);
}

// @ 0x007a2d20
void Converter::ConvertPairPairs(Group2Vec* dest)
{
    GroupVec source;
    source.begin = 0;
    source.end = 0;
    source.cap = 0;
    FUN_007a0b90(&source, 0, dest);

    int groupCount = (int)(source.end - source.begin);
    FUN_007a1100(dest, 0, groupCount * 2);

    OutRecord outA;
    InitOut(outA);
    OutRecord outB;
    InitOut(outB);

    for (int i = 0; i < groupCount; ++i) {
        Group2* target = dest->begin + i;
        Group* group = source.begin + i;
        int pairCount = (int)(group->end - group->begin);
        FUN_0079af80(&target->a, 0, pairCount);
        FUN_0079af80(&target->b, 0, pairCount);
        for (int j = 0; j < pairCount; ++j) {
            Pair* pair = group->begin + j;
            FUN_007a1d00(this, 0, pair->object, &outA, &outB);
            if (outA.sp0 != 0)
                PushPair(&target->a, outA.sp0, pair->tag);
            if (outA.sp1 != 0)
                PushPair(&target->a, outA.sp1, pair->tag);
            if (outB.sp0 != 0)
                PushPair(&target->b, outB.sp0, pair->tag);
            if (outB.sp1 != 0)
                PushPair(&target->b, outB.sp1, pair->tag);
        }
    }

    FUN_0079aeb0(&outB);
    FUN_0079aeb0(&outA);
    DestroyGroupVector(&source);
}
