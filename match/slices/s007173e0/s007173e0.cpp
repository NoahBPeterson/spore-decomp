// Slice s007173e0: SP::cAppModeEditorBase vector helpers (resize / range copy /
// copy-assign) plus three larger editor routines.  Built /O2 /MD /Gy /EHsc /TP.
// This region is not in the 2008 dev PDB; layouts read from the disassembly.
#include <stddef.h>

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
    void  move(char* first, char* last, char* dest);          // masked (0x720250)
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
        move(mpEnd, mpEnd, p);
        mpEnd += (int)((mpEnd - p) / 0x18) * 0x18;
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

// @ 0x007173e0
void editorRoutine173e0(void* self, int a, int b, int c)
{
    (void)self; (void)a; (void)b; (void)c;
}

// @ 0x00717bd0
void editorRoutine17bd0(void* self)
{
    (void)self;
}

// @ 0x00717ce0
void editorRoutine17ce0(void* self, int a, int b)
{
    (void)self; (void)a; (void)b;
}

// @ 0x00718050
void editorRoutine18050(void* self, int a, int b)
{
    (void)self; (void)a; (void)b;
}

// @ 0x00718370  EH copy ctor for an object holding two vectors at +0 and +0x14
void editorCopyCtor18370(void* self, const void* src)
{
    (void)self; (void)src;
}
