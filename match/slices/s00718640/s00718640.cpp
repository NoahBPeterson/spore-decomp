// Slice s00718640: more SP::cMeshBuilder vector helpers (index insert+adjust,
// range copy) and larger editor routines.  Built /O2 /MD /Gy /EHsc /TP.
// This region is not in the 2008 dev PDB; layouts read from the disassembly and
// from the constructor in slice s00716110.
#include <stddef.h>

typedef unsigned int u32;
typedef unsigned char u8;

struct VecN {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    VecN& operator=(const VecN& o);                                // masked
    void  insert(void* pos, const void* first, const void* last, int tag); // masked range insert
};
struct VecSlotN { VecN v; char pad[8]; };   // 0x14 bytes

struct Elem28 { VecN v0; char p0[8]; VecN v14; char p1[8]; };

struct MeshBuilder8 {
    char   pad0[0xd0];               // +0x00
    void*  pD0;                      // +0xd0
    char   padD4[0xe8 - 0xd4];
    void*  pE8;                      // +0xe8
    char   padEC[0x150 - 0xec];
    u8     b150;                     // +0x150
    char   pad151[0x160 - 0x151];
    int    n160;                     // +0x160
    char   pad164[0x188 - 0x164];
    VecSlotN v188[8];                // +0x188 .. +0x228

    void addIndices0(int count, const int* values, int delta);
    void addIndices1(int count, const int* values, int delta);
    void addIndicesSlot(int count, const int* values, int delta, int index);
    void addIndicesSlot6(int count, const int* values, int delta, int index);
    void finish();
    // callees (other slices / TUs), masked
    void sub18820();
    void sub17ce0();
    void sub173e0();
    void sub18050();
};

// ---------------------------------------------------------------------------
// range copies / fills
// ---------------------------------------------------------------------------

// @ 0x00718640
Elem28* copyBack28(Elem28* first, Elem28* last, Elem28* dst)
{
    while (last != first) {
        --last;
        --dst;
        dst->v0 = last->v0;
        dst->v14 = last->v14;
    }
    return dst;
}

// @ 0x00719200
void fill28(Elem28* first, Elem28* last, const Elem28* value)
{
    while (first != last) {
        first->v0 = value->v0;
        first->v14 = value->v14;
        ++first;
    }
}

// ---------------------------------------------------------------------------
// insert values then add delta to the freshly inserted elements
// ---------------------------------------------------------------------------

// @ 0x00718680
void MeshBuilder8::addIndices0(int count, const int* values, int delta)
{
    v188[0].v.insert(v188[0].v.mpEnd, values, values + count, count);
    if (delta != 0) {
        int* p = (int*)v188[0].v.mpEnd - count;
        while (p != (int*)v188[0].v.mpEnd) {
            *p += delta;
            ++p;
        }
    }
}

// @ 0x007186e0
void MeshBuilder8::addIndices1(int count, const int* values, int delta)
{
    v188[1].v.insert(v188[1].v.mpEnd, values, values + count, count);
    if (delta != 0) {
        int* p = (int*)v188[1].v.mpEnd - count;
        while (p != (int*)v188[1].v.mpEnd) {
            *p += delta;
            ++p;
        }
    }
}

// @ 0x00718740
void MeshBuilder8::addIndicesSlot(int count, const int* values, int delta, int index)
{
    VecN& v = v188[2 + index].v;
    v.insert(v.mpEnd, values, values + count, count);
    if (delta != 0) {
        int* p = (int*)v.mpEnd - count;
        while (p != (int*)v.mpEnd) {
            *p += delta;
            ++p;
        }
    }
}

// @ 0x007187b0
void MeshBuilder8::addIndicesSlot6(int count, const int* values, int delta, int index)
{
    VecN& v = v188[6 + index].v;
    v.insert(v.mpEnd, values, values + count, count);
    if (delta != 0) {
        int* p = (int*)v.mpEnd - count;
        while (p != (int*)v.mpEnd) {
            *p += delta;
            ++p;
        }
    }
}

// @ 0x00719240
void MeshBuilder8::finish()
{
    if (n160 >= 0) {
        char* base = (char*)pD0 + n160 * 0xd0;
        *(int*)((char*)pE8 - 8) = (*(int*)(base + 0xc0) - *(int*)(base + 0xbc)) >> 2;
    }
    sub18820();
    sub17ce0();
    sub173e0();
    sub18050();
    b150 = 0;
}

// ---------------------------------------------------------------------------
// remaining routines (nonmatching / partial reconstructions)
// ---------------------------------------------------------------------------

// @ 0x00719170  FixedIdVector6 assignment (different element type)
void __cdecl fixedIdDoAssign(void* a, void* b, void* c);
int* fixedIdAssign(int* self, int* other)
{
    if (self != other) {
        self[1] = self[1] + ((self[1] - self[0]) >> 2) * -4;
        fixedIdDoAssign((void*)other[0], (void*)other[1], other);
    }
    return self;
}

// @ 0x00719330  insert range with destructor loop over 0xd0-byte elements
void editorInsert19330(void* self, int a, int b)
{
    (void)self; (void)a; (void)b;
}

// @ 0x00719390  copy + erase range over 0x50-byte elements
void editorErase19390(void* self, int a, int b)
{
    (void)self; (void)a; (void)b;
}

// @ 0x00718820  large editor routine (2384 bytes)
void editorRoutine18820(void* self)
{
    (void)self;
}

// @ 0x007193e0  insert n copies of an element into a vector<0xd0>
void editorInsert193e0(void* self, int a, int b, int c)
{
    (void)self; (void)a; (void)b; (void)c;
}
