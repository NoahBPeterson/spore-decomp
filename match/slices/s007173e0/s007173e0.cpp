// Slice s007173e0: SP::cAppModeEditorBase vector helpers (resize / range copy /
// copy-assign) plus three larger editor routines.  Built /O2 /MD /Gy /EHsc /TP.
// This region is not in the 2008 dev PDB; layouts read from the disassembly.
#include <stddef.h>
#include <string.h>

typedef unsigned int u32;

// generic eastl-vector-like slot (only begin/end/cap are touched here)
struct VecN {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    VecN& operator=(const VecN& o);   // masked (eastl::vector<T>::operator=)
    void insert(void* pos, void* first, void* last, int tag); // masked range insert
};
struct VecSlotN { VecN v; char pad[8]; };   // 0x14 bytes

// 0x28 / 0x50 byte editor elements holding 2 / 4 vectors
struct Elem28 { VecN v0; char p0[8]; VecN v14; char p1[8]; };
struct Elem50 { VecN v0; char p0[8]; VecN v14; char p1[8];
                VecN v28; char p2[8]; VecN v3c; char p3[8]; };

// ---------------------------------------------------------------------------
// vector resize helpers
// ---------------------------------------------------------------------------

struct Vec30 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void  insert(char* pos, unsigned n, const void* value);   // masked (0x715470)
    void  erase(char* first, char* last);                     // masked (0x9c69f0)
    void  resize(unsigned n, const void* value);
};

// @ 0x00717820
void Vec30::resize(unsigned n, const void* value)
{
    unsigned cur = (unsigned)((mpEnd - mpBegin) / 0x30);
    if (cur < n)
        insert(mpEnd, n - cur, value);
    else
        erase(mpBegin + n * 0x30, mpEnd);
}

struct Vec18 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void  insert(char* pos, unsigned n, const void* value);   // masked (0x722580)
    static void move(char* first, char* last, char* dest);    // masked (0x720250), cdecl: the original sets no ecx
    void  resize(unsigned n);
};

// @ 0x00717890
void Vec18::resize(unsigned n)
{
    unsigned cur = (unsigned)((mpEnd - mpBegin) / 0x18);
    if (cur < n) {
        int fill[6] = { -1, -1, -1, -1, -1, -1 };
        insert(mpEnd, n - cur, fill);
    } else {
        char* p = mpBegin + n * 0x18;
        char* end = mpEnd;
        move(end, end, p);
        mpEnd += (int)((p - end) / 0x18) * 0x18;
    }
}

// ---------------------------------------------------------------------------
// element range copies
// ---------------------------------------------------------------------------

// @ 0x00717ad0
Elem50* copyFwd50(Elem50* first, Elem50* last, Elem50* dst)
{
    while (first != last) {
        dst->v0 = first->v0;
        dst->v14 = first->v14;
        dst->v28 = first->v28;
        dst->v3c = first->v3c;
        ++first;
        ++dst;
    }
    return dst;
}

// @ 0x00717b70
Elem50* copyBack50(Elem50* first, Elem50* last, Elem50* dst)
{
    while (last != first) {
        --last;
        --dst;
        dst->v0 = last->v0;
        dst->v14 = last->v14;
        dst->v28 = last->v28;
        dst->v3c = last->v3c;
    }
    return dst;
}

// @ 0x00718520
void assignFwd50(Elem50* first, Elem50* last, Elem50* src)
{
    while (first != last) {
        first->v0 = src->v0;
        first->v14 = src->v14;
        first->v28 = src->v28;
        first->v3c = src->v3c;
        ++first;
        ++src;
    }
}

// @ 0x00718600
Elem28* copyFwd28(Elem28* first, Elem28* last, Elem28* dst)
{
    while (first != last) {
        dst->v0 = first->v0;
        dst->v14 = first->v14;
        ++first;
        ++dst;
    }
    return dst;
}

// ---------------------------------------------------------------------------
// copy-assignment for the editor object (same member layout as MeshBuilder)
// ---------------------------------------------------------------------------

struct Vec14x4 { char pad[0x30]; VecSlotN v; };   // v at +0x30

struct AppEditor {
    char pad0[8];                    // +0x00
    VecSlotN v8;                     // +0x08
    VecSlotN v1c;                    // +0x1c
    VecSlotN v30[4];                 // +0x30
    VecSlotN v80[2];                 // +0x80
    VecSlotN vA8;                    // +0xa8
    VecSlotN vBC;                    // +0xbc
    AppEditor& operator=(const AppEditor& x);
    void  insertRange(int count, char* first, int index);
};

// @ 0x007179e0
AppEditor& AppEditor::operator=(const AppEditor& x)
{
    *(int*)&pad0[0] = *(int*)&x.pad0[0];
    *(int*)&pad0[4] = *(int*)&x.pad0[4];
    v8.v = x.v8.v;
    v1c.v = x.v1c.v;
    for (int i = 0; i < 4; ++i)
        v30[i].v = x.v30[i].v;
    for (int i = 0; i < 2; ++i)
        v80[i].v = x.v80[i].v;
    vA8.v = x.vA8.v;
    vBC.v = x.vBC.v;
    return *this;
}

// @ 0x00717cb0
void AppEditor::insertRange(int count, char* first, int index)
{
    Vec14x4* e = (Vec14x4*)((char*)this + index * 0x14);
    e->v.v.insert(e->v.v.mpEnd, first, first + count * 8, index);
}

// ---------------------------------------------------------------------------
// large editor routines (partial reconstructions)
// ---------------------------------------------------------------------------

// ---- selection-definition object used by 0x7173e0 (0x13c bytes) ----
struct SelRec28 {                   // 0x28-byte group
    int*   idxBegin;    // +0x00
    int*   idxEnd;      // +0x04
    char   pad08[0x0c]; // +0x08
    float* weights;     // +0x14 weight/visibility flags per index
};
struct SelRec50 {                   // 0x50-byte group, two 0x28 sub-records
    int*   idxBegin;    // +0x00
    int*   idxEnd;      // +0x04
    char   pad08[0x0c]; // +0x08
    float* pos;         // +0x14 xyz triples
    char   pad18[0x10]; // +0x18
    int*   idx2Begin;   // +0x28
    int*   idx2End;     // +0x2c
    char   pad30[0x0c]; // +0x30
    float* pos2;        // +0x3c xyz triples
};
struct SelRecD0 {                   // 0xd0-byte usage record
    unsigned flags;     // +0x00 accumulated use bits
    int      count;     // +0x04
    int*     idxBegin;  // +0x08 vertex indices
    int*     idxEnd;    // +0x0c
    int*     idxCap;    // +0x10
    char     pad14[0x08];// +0x14
    int*     view1Begin;// +0x1c second index array
    int*     view1End;  // +0x20
    int*     view1Cap;  // +0x24
    char     pad28[0x80];// +0x28
    int*     view2Begin;// +0xa8 third index array
    int*     view2End;  // +0xac
    int*     view2Cap;  // +0xb0
    char     padB4[0x08];// +0xb4
    int*     remapBegin;// +0xbc index remap
    int*     remapEnd;  // +0xc0
    int*     remapCap;  // +0xc4
};
struct AttrEnt {                      // 0x14-byte attribute/range entry
    int tag;     // +0x00 attribute channel (0..9)
    int rec;     // +0x04 owner record index
    int begin;   // +0x08 first index into the record remap
    int end;     // +0x0c last index into the record remap
    int inner;   // +0x10 inner index
};

struct SelEditor {
    char       pad00[0x08];  // +0x00
    float*     sizeBegin;    // +0x08 vertex-size triples
    float*     sizeEnd;      // +0x0c
    char       pad10[0x0c];  // +0x10
    float*     size2Begin;   // +0x1c
    float*     size2End;     // +0x20
    char       pad24[0xac];  // +0x24
    SelRecD0*  recBegin;     // +0xd0
    SelRecD0*  recEnd;       // +0xd4
    char       padD8[0x0c];  // +0xd8
    AttrEnt*   entBegin;     // +0xe4 attribute/range entries
    AttrEnt*   entEnd;       // +0xe8
    char       padEC[0x0c];  // +0xec
    char*      keyBegin;     // +0xf8 8-byte inner keys
    char*      keyEnd;       // +0xfc
    char       pad100[0x20]; // +0x100
    SelRec28*  r28Begin;     // +0x120
    SelRec28*  r28End;       // +0x124
    char       pad128[0x0c]; // +0x128
    SelRec50*  r50Begin;     // +0x134
    SelRec50*  r50End;       // +0x138
};

void* __cdecl EA_Allocate(unsigned size, const char* area, int a, int b, void* allocator, int line); // 0x00f473a0
void  __cdecl EA_Free(void* p);                                     // 0x00f47380
extern unsigned char g_eastlAllocator;                              // 0x13ebb38

static unsigned* gfxCountArray(int count)
{
    unsigned* a = 0;
    if (count != 0) {
        a = (unsigned*)EA_Allocate((unsigned)(count * 4), "Graphics", 0, 0, &g_eastlAllocator, 0xd1);
        for (int k = 0; k < count; ++k)
            a[k] = 0;
    }
    return a;
}

// @ 0x007173e0
void __fastcall FUN_007173e0(SelEditor* self)
{
    int n1 = (int)(self->sizeEnd - self->sizeBegin) / 3;
    unsigned* c1 = gfxCountArray(n1);
    int n2 = (int)(self->sizeEnd - self->sizeBegin) / 3;
    unsigned* c2 = gfxCountArray(n2);
    int n3 = (int)(self->size2End - self->size2Begin) / 3;
    unsigned* c3 = gfxCountArray(n3);
    int groups = (int)(self->r28End - self->r28Begin);
    if (groups > 0) {
        for (int i = 0; i < groups; ++i) {
            SelRec28* r = self->r28Begin + i;
            int cnt = (int)(r->idxEnd - r->idxBegin);
            for (int j = 0; j < cnt; ++j) {
                if (r->weights[j] > 0.0001f)
                    ++c1[r->idxBegin[j]];
            }
        }
    }
    int groups50 = (int)(self->r50End - self->r50Begin);
    if (groups50 > 0) {
        for (int i = 0; i < groups50; ++i) {
            SelRec50* r = self->r50Begin + i;
            int cnt = (int)(r->idxEnd - r->idxBegin);
            for (int j = 0; j < cnt; ++j) {
                const float* p = r->pos + j * 3;
                if (p[0] * p[0] + p[1] * p[1] + p[2] * p[2] > 9.999999e-09f)
                    ++c2[r->idxBegin[j]];
            }
            int cnt2 = (int)(r->idx2End - r->idx2Begin);
            for (int j = 0; j < cnt2; ++j) {
                const float* p = r->pos2 + j * 3;
                if (p[0] * p[0] + p[1] * p[1] + p[2] * p[2] > 9.999999e-09f)
                    ++c3[r->idx2Begin[j]];
            }
        }
    }
    int recs = (int)(self->recEnd - self->recBegin);
    if (recs > 0) {
        for (int i = 0; i < recs; ++i) {
            SelRecD0* r = self->recBegin + i;
            if (r->idxBegin != r->idxEnd) {
                for (int j = 0; j < r->count; ++j) {
                    int idx = r->idxBegin[j];
                    if ((int)c1[idx] > 0)
                        r->flags |= 0x100;
                    if ((int)c2[idx] > 0)
                        r->flags |= 0x200;
                    if ((r->flags & 0x100) != 0 && (r->flags & 0x200) != 0)
                        break;
                }
            }
            if (r->view1Begin != r->view1End) {
                for (int j = 0; j < r->count; ++j) {
                    if ((int)c3[r->view1Begin[j]] > 0) {
                        r->flags |= 0x400;
                        break;
                    }
                }
            }
        }
    }
    if (c3 != 0 && ((int*)c3)[-1] != 0)
        EA_Free(c3);
    if (c2 != 0 && ((int*)c2)[-1] != 0)
        EA_Free(c2);
    if (c1 != 0 && ((int*)c1)[-1] != 0)
        EA_Free(c1);
}

struct IntVec { int* begin; int* end; int* cap; };

void __fastcall FUN_0052c730(IntVec* self, int unused, IntVec* other); // 0x0052c730 eastl vector swap (this in ecx)
int  __cdecl FUN_00921240(int* vec);                               // 0x00921240 sort key for a group vector
void __cdecl FUN_00715e50(int* first, int* last, int key);         // 0x00715e50 stable sort by that key

// eastl vector<unsigned>::push_back (sp_vector_allocator growth)
static void PushU32(IntVec* v, int value)
{
    if (v->end < v->cap) {
        *v->end = value;
        v->end = v->end + 1;
        return;
    }
    int cur = (int)(v->end - v->begin);
    int cap = (int)(v->cap - v->begin);
    int ncap = cap * 2;
    if (ncap < cur + 1)
        ncap = cur + 1;
    int* p = (int*)EA_Allocate((unsigned)(ncap * 4), "Graphics", 0, 0, &g_eastlAllocator, 0xd1);
    for (int k = 0; k < cur; ++k)
        p[k] = v->begin[k];
    p[cur] = value;
    if (v->begin != 0 && ((int*)v->begin)[-1] != 0)
        EA_Free(v->begin);
    v->begin = p;
    v->end = p + cur + 1;
    v->cap = p + ncap;
}

// @ 0x00717bd0
void __cdecl FUN_00717bd0(int* map, int* dstRaw)
{
    IntVec* dst = (IntVec*)dstRaw;
    IntVec out;
    int n = (int)(map[1] - map[0]) >> 2;
    out.begin = 0;
    if (n != 0)
        out.begin = (int*)EA_Allocate((unsigned)(n * 4), "Graphics", 0, 0, &g_eastlAllocator, 0xd1);
    out.end = out.begin + n;
    for (int k = 0; k < n; ++k)
        out.begin[k] = 0;
    const int* mapBegin = (const int*)map[0];
    int* src = dst->begin;
    for (unsigned i = 0; i < (unsigned)n; ++i)
        out.begin[i] = src[mapBegin[i]];
    out.cap = out.end;
    FUN_0052c730(dst, 0, &out);
    if (out.begin != 0 && ((int*)out.begin)[-1] != 0)
        EA_Free(out.begin);
}

// @ 0x00717ce0
void __fastcall FUN_00717ce0(SelEditor* self)
{
    int recs = (int)(self->recEnd - self->recBegin);
    for (int i = 0; i < recs; ++i) {
        SelRecD0* r = self->recBegin + i;
        int count = r->count;
        int* order = (int*)gfxCountArray(count);
        for (int k = 0; k < count; ++k)
            order[k] = k;
        IntVec ov = { order, order + count, order + count };
        if (r->view2Begin != r->view2End)
            FUN_00715e50(order, order + count, FUN_00921240((int*)&r->view2Begin));
        if (r->view1Begin != r->view1End)
            FUN_00715e50(order, order + count, FUN_00921240((int*)&r->view1Begin));
        if (r->idxBegin != r->idxEnd)
            FUN_00715e50(order, order + count, FUN_00921240((int*)&r->idxBegin));
        int* gids = 0;
        if (count != 0) {
            gids = (int*)EA_Allocate((unsigned)(count * 4), "Graphics", 0, 0, &g_eastlAllocator, 0xd1);
            for (int k = 0; k < count; ++k)
                gids[k] = -1;
        }
        IntVec groups = { 0, 0, 0 };
        int cur = *ov.begin;
        PushU32(&groups, cur);
        gids[cur] = 0;
        int remaining = count - 1;
        if (remaining > 0) {
            int* it = ov.begin;
            do {
                ++it;
                int idx = *it;
                if (r->idxBegin[cur] != r->idxBegin[idx] ||
                    (r->view1Begin != r->view1End && r->view1Begin[cur] != r->view1Begin[idx]) ||
                    (r->view2Begin != r->view2End && r->view2Begin[cur] != r->view2Begin[idx])) {
                    PushU32(&groups, idx);
                    idx = *it;
                    cur = idx;
                }
                --remaining;
                gids[idx] = (int)(groups.end - groups.begin) - 1;
            } while (remaining != 0);
        }
        int nremap = (int)(r->remapEnd - r->remapBegin);
        for (int k = 0; k < nremap; ++k)
            r->remapBegin[k] = gids[r->remapBegin[k]];
        if (r->idxBegin != r->idxEnd)
            FUN_00717bd0((int*)&groups, (int*)&r->idxBegin);
        if (r->view1Begin != r->view1End)
            FUN_00717bd0((int*)&groups, (int*)&r->view1Begin);
        if (r->view2Begin != r->view2End)
            FUN_00717bd0((int*)&groups, (int*)&r->view2Begin);
        r->count = (int)(groups.end - groups.begin);
        if (gids != 0 && ((int*)gids)[-1] != 0)
            EA_Free(gids);
        if (groups.begin != 0 && ((int*)groups.begin)[-1] != 0)
            EA_Free(groups.begin);
        if (order != 0 && ((int*)order)[-1] != 0)
            EA_Free(order);
    }
}

struct Span5 {                        // 0x14-byte description span
    int tag;     // +0x00
    int rec;     // +0x04
    int begin;   // +0x08
    int end;     // +0x0c
    int inner;   // +0x10
};
struct IntVecF { float* begin; float* end; float* cap; };

void __cdecl FUN_0042b9e0(float* dst, const int* first, const int* last, int count);  // 0x0042b9e0
void __cdecl FUN_00428900(Span5* pos, const Span5* value);       // eastl vector<cAnimationCurve>::DoInsertValue
void __cdecl FloatVec_Release(IntVecF* v);                        // eastl::vector<float>::~vector
void __fastcall FUN_00715120(void* self, int unused, IntVec* other); // 0x00715120 vector<0x14-record> copy-assign (this in ecx)

// @ 0x00718050
void __fastcall FUN_00718050(SelEditor* self)
{
    IntVecF accum = { 0, 0, 0 };
    Span5* spans = 0;
    Span5* spansEnd = 0;
    Span5* spansCap = 0;
    int recs = (int)(self->recEnd - self->recBegin);
    for (int i = 0; i < recs; ++i) {
        SelRecD0* r = self->recBegin + i;
        accum.begin = 0;
        accum.end = 0;
        accum.cap = 0;
        for (int tag = 0; tag < 10; ++tag) {
            for (int j = 0; j < (int)((self->keyEnd - self->keyBegin) >> 3); ++j) {
                int start = (int)(accum.end - accum.begin);
                int nEnt = (int)((self->entEnd - self->entBegin) / 0x14);
                for (int e = 0; e < nEnt; ++e) {
                    AttrEnt* en = self->entBegin + e;
                    if (en->rec != i || en->tag != tag || en->inner != j)
                        continue;
                    FUN_0042b9e0(accum.end, r->remapBegin + en->begin * 4,
                                 r->remapBegin + en->end * 4, recs);
                    int end = (int)(accum.end - accum.begin);
                    if (tag != 4 && start < end) {
                        Span5 s = { tag, i, start, end, j };
                        if (spansEnd < spansCap) {
                            *spansEnd = s;
                            ++spansEnd;
                        } else {
                            FUN_00428900(spansEnd, &s);
                        }
                    }
                }
                int end = (int)(accum.end - accum.begin);
                if (tag == 4 && start < end) {
                    Span5 s = { 4, i, start, end, j };
                    if (spansEnd < spansCap) {
                        *spansEnd = s;
                        ++spansEnd;
                    } else {
                        FUN_00428900(spansEnd, &s);
                    }
                }
            }
        }
        FloatVec_Release(&accum);
        if (accum.begin != 0 && ((int*)accum.begin)[-1] != 0)
            EA_Free(accum.begin);
    }
    Span5* first = spans;
    IntVec spansVec = { (int*)spans, (int*)spansEnd, (int*)spansCap };
    FUN_00715120((void*)&self->entBegin, 0, &spansVec);
    if (first != 0 && ((int*)first)[-1] != 0)
        EA_Free(first);
}

void __fastcall FUN_004aa350(void* self, int unused, unsigned count, void** allocator); // 0x004aa350 eastl reserve (this in ecx)

// @ 0x00718370
void* __fastcall FUN_00718370(int* self, int unused, int* src)
{
    int n0 = src[1] - src[0];
    FUN_004aa350((void*)self, 0, (unsigned)(n0 >> 2), (void**)(src + 3));
    int* end0 = (int*)memcpy((void*)self[0], (const void*)src[0], (unsigned)n0);
    self[1] = (int)end0 + (n0 >> 2) * 4;
    int n1 = src[6] - src[5];
    FUN_004aa350((void*)(self + 5), 0, (unsigned)(n1 >> 2), (void**)(src + 8));
    int* end1 = (int*)memcpy((void*)self[5], (const void*)src[5], (unsigned)n1);
    self[6] = (int)end1 + (n1 >> 2) * 4;
    return self;
}
