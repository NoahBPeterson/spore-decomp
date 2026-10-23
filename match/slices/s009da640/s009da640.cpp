// s009da640 -- nSPCreatureAnim::dynamics_phasegroup (0x104-byte element) container and
// EASTL sort/heap internals instantiated for it, plus the phasegroup table builders.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast   (VC9 / VS2008 SP1, the game's main toolset)
//
// The element type has a non-trivial copy ctor / assignment / destructor that live outside this
// slice (0x009d8720 / 0x009d9620 / inline teardown of its 0x38-byte-element vector); every helper
// call below is a relocation and is therefore named by address only.

typedef unsigned int u32;

void operator delete(void*);

// thiscall-shaped helpers, reached through a member call so ecx = the object pointer.
struct Ops {
    void Copy(void* src);        // 0x009d8720  copy-construct this from src
    void Assign(void* src);      // 0x009d9620  assign src to this
    void Ctor();                 // 0x009d75b0  default-construct this
    void F000(void* p);          // 0x009da000
    void F5b0(void* p);          // 0x009da5b0
    void F84f0();                // 0x009d84f0
    void F1090(void* p);         // 0x009d1090
    void F30b0();                // 0x009d30b0
    void F2dd0(void* p1, void* p2, void* p3);  // 0x009d2dd0
};

// ---------------------------------------------------------------------------------------------
// the 0x104-byte element
// ---------------------------------------------------------------------------------------------
struct Elem {
    char b[0x104];

    Elem() { ((Ops*)this)->Ctor(); }
    Elem(const Elem& o) { ((Ops*)this)->Copy((void*)&o); }
    Elem& operator=(const Elem& o) { ((Ops*)this)->Assign((void*)&o); return *this; }
    ~Elem()
    {
        // the element owns an eastl::vector of 0x38-byte records (each holding a counted buffer
        // at +4) at +0x4c; the record vector and its buffer are released with the -4 cookie test.
        char* p = *(char**)(b + 0x4c);
        char* e = *(char**)(b + 0x50);
        if (p != e) {
            int n = (int)(e - p - 1) / 0x38 + 1;
            do {
                void* q = *(void**)(p + 4);
                if (q && *(int*)((char*)q - 4))
                    ::operator delete(q);
                p += 0x38;
            } while (--n);
        }
        void* buf = *(void**)(b + 0x4c);
        if (buf && *(int*)((char*)buf - 4))
            ::operator delete(buf);
    }
};

// 4-byte comparator object; both functors take their operands by value (0x104 bytes each).
struct Compare {
    void* mp;
    bool CmpA(Elem a, Elem b);   // 0x009d7840
    bool CmpB(Elem a, Elem b);   // 0x009d7920
};

// vector of Elem at this+0x10
struct PhaseVec {
    Elem* mpBegin;
    Elem* mpEnd;
    Elem* mpCap;
    void DoDestroyValues(Elem* first, Elem* last);   // 0x009c3240
    void Grow(Elem* pos, const Elem* value);         // 0x009dada0
};

// SP::SimpleVector<unsigned int> at element+0xbc
struct U32Vec {
    u32* mpBegin;
    u32* mpEnd;
    u32* mpCap;
    void DoInsertValue(u32* pos, const u32& value);  // 0x004558a0
};

struct Solver;
struct Bone;
struct Solver {
    bool Fn3430(Bone* a, Bone* b);   // 0x009b3430
    bool Fn5700(Bone* a, Bone* b);   // 0x009b5700
    int  Fn57b0(Bone* a, Bone* b);   // 0x009b57b0
};

// ---------------------------------------------------------------------------------------------
// free helpers (all relocations)
// ---------------------------------------------------------------------------------------------
int  FUN_009da170(Elem* first, int hole, int len, int top, Elem value, Compare cmp);  // 0x009da170
int  FUN_009da2d0(Elem* first, int hole, int len, int top, Elem value, Compare cmp);  // 0x009da2d0
void FUN_009d9f80(Elem* a, Elem* b);                                                  // 0x009d9f80
Elem* FUN_009d8be0(Elem* a, Elem* b, Elem* c, Compare c1, Compare c2);               // 0x009d8be0
Elem* FUN_009d8ce0(Elem* a, Elem* b, Elem* c, Compare c1, Compare c2);               // 0x009d8ce0
void FUN_009d9840(Elem* first, Elem* last, Compare cmp);                              // 0x009d9840
void FUN_009d9970(Elem* first, Elem* last, Compare cmp);                              // 0x009d9970
void FUN_009d9a90(Elem* first, Elem* last, Compare cmp);                              // 0x009d9a90
void FUN_009d9bc0(Elem* first, Elem* last, Compare cmp);                              // 0x009d9bc0
void FUN_009da730(Elem* first, Elem* last, Compare cmp);                              // 0x009da730
void FUN_009da800(Elem* first, Elem* last, Compare cmp);                              // 0x009da800
void* FUN_009d9ce0(void* a, void* b, void* c);                                        // 0x009d9ce0
void FUN_009cecb0(void* a, void* b, void* c);                                         // 0x009cecb0
void FUN_009d41b0(void* a, void* b, void* c);                                         // 0x009d41b0
void FUN_009d7b20(void* a, void* b, int c);                                           // 0x009d7b20
void FUN_009d2dd0(void* a, void* b, void* c);                                         // 0x009d2dd0
void FUN_009dada0(PhaseVec* self, Elem* pos, const Elem* value);                     // 0x009dada0
int  FUN_009d3410(float f);                                                           // 0x009d3410
u32  FUN_009d0ee0();                                                                  // 0x009d0ee0

// ---------------------------------------------------------------------------------------------
// 0x009da640 -- destroy every element of the vector at +0x10, then tear down the table at +0x24
// ---------------------------------------------------------------------------------------------
struct Anim {
    void A640(void* ctx);                     // 0x009da640
    void A1d0();                              // 0x009db1d0
    void A270();                              // 0x009db270
    Elem* A330();                             // 0x009db330
    void A3f0(void* vec, int count);          // 0x009db3f0
    void A4d0(float f);                       // 0x009db4d0
    int  A590(void* a, void* b, int c);       // 0x009db590
    int  A630(Solver** ps, Bone** a, Bone** b, int c);  // 0x009db630
};

// @ 0x009da640
void Anim::A640(void* ctx)
{
    int n = (*(int*)((char*)this + 0x14) - *(int*)((char*)this + 0x10)) / 0x104;
    int off = 0;
    for (int i = n; i != 0; --i) {
        char* p = *(char**)((char*)this + 0x10) + off;
        ((Ops*)p)->F000(ctx);
        ((Ops*)p)->F5b0(ctx);
        ((Ops*)p)->F84f0();
        ((Ops*)p)->F1090((char*)this + 0x24);
        off += 0x104;
    }
    ((Ops*)this)->F30b0();
}

// ---------------------------------------------------------------------------------------------
// 0x009db1d0 -- destroy the three member vectors and fold their end pointers back
// ---------------------------------------------------------------------------------------------
// @ 0x009db1d0
void Anim::A1d0()
{
    PhaseVec* v = (PhaseVec*)((char*)this + 0x10);
    Elem* begin = v->mpBegin;
    Elem* end = v->mpEnd;
    void* r = FUN_009d9ce0(end, end, begin);
    v->DoDestroyValues((Elem*)r, v->mpEnd);
    long x = (long)((char*)begin - (char*)end);
    v->mpEnd = (Elem*)((char*)end + x / 0x104 * 0x104);

    int b2 = *(int*)((char*)this + 0x24);
    int e2 = *(int*)((char*)this + 0x28);
    FUN_009cecb0((void*)e2, (void*)e2, (void*)b2);
    long x2 = (long)(b2 - e2);
    *(int*)((char*)this + 0x28) = e2 + x2 / 0x108 * 0x108;

    int b3 = *(int*)((char*)this + 0x38);
    int e3 = *(int*)((char*)this + 0x3c);
    FUN_009d41b0((void*)e3, (void*)e3, (void*)b3);
    long x3 = (long)(b3 - e3);
    *(int*)((char*)this + 0x3c) = e3 + x3 / 0x30 * 0x30;
}

// ---------------------------------------------------------------------------------------------
// 0x009db270 -- initialise the scalar fields and destroy the vector at +0x10
// ---------------------------------------------------------------------------------------------
// @ 0x009db270
void Anim::A270()
{
    *(float*)((char*)this + 0x78) = 1.0f;
    *(float*)((char*)this + 0x7c) = 1.0f;
    *(float*)((char*)this + 0x6c) = 0.0f;
    *(float*)((char*)this + 0x70) = 0.1f;
    *(float*)((char*)this + 0x4c) = 0.0f;
    *(float*)((char*)this + 0x50) = 0.0f;
    *(float*)((char*)this + 0x54) = 0.0f;
    *(float*)((char*)this + 0x58) = 0.0f;
    *(float*)((char*)this + 0x5c) = 0.0f;
    *(float*)((char*)this + 0x60) = 0.0f;
    *(float*)((char*)this + 0x08) = 0.0f;
    *(float*)((char*)this + 0x64) = 0.0f;
    *(float*)((char*)this + 0x68) = 0.0f;
    *(float*)((char*)this + 0x0c) = 0.0f;
    *(float*)((char*)this + 0x74) = 1.0f;
    *(int*)((char*)this + 0x00) = 0;
    *(int*)((char*)this + 0x04) = 0;
    *(float*)((char*)this + 0x80) = 1.0f;

    PhaseVec* v = (PhaseVec*)((char*)this + 0x10);
    Elem* begin = v->mpBegin;
    Elem* end = v->mpEnd;
    void* r = FUN_009d9ce0(end, end, begin);
    v->DoDestroyValues((Elem*)r, v->mpEnd);
    long x = (long)((char*)begin - (char*)end);
    v->mpEnd = (Elem*)((char*)end + x / 0x104 * 0x104);
}

// ---------------------------------------------------------------------------------------------
// 0x009db330 -- append a fresh element initialised with {this, index} and return its address
// ---------------------------------------------------------------------------------------------
// @ 0x009db330
Elem* Anim::A330()
{
    int n = (*(int*)((char*)this + 0x14) - *(int*)((char*)this + 0x10)) / 0x104;
    Elem tmp;
    *(int*)(tmp.b + 0x48) = (int)this;
    *(int*)(tmp.b + 0xb8) = n;

    PhaseVec* v = (PhaseVec*)((char*)this + 0x10);
    Elem* p = v->mpEnd;
    if (p < v->mpCap) {
        v->mpEnd = p + 1;
        if (p)
            ((Ops*)p)->Copy(&tmp);
    } else {
        v->Grow(p, &tmp);
    }
    return (Elem*)((char*)v->mpBegin + n * 0x104);
}

// ---------------------------------------------------------------------------------------------
// 0x009db3f0 -- truncate the index vector of `vec` at `count` and rebuild the mapping
// ---------------------------------------------------------------------------------------------
// @ 0x009db3f0
void Anim::A3f0(void* vec, int count)
{
    int n = (*(int*)((char*)vec + 0xc0) - *(int*)((char*)vec + 0xbc)) >> 2;
    int last = (int)vec;
    for (int i = n - 1; i >= count; --i) {
        last = *(int*)(*(int*)((char*)vec + 0xbc) + i * 4);
        *(int*)((char*)vec + 0xc0) -= 4;
    }

    Elem* e = A330();
    int num = n - count;
    int top = (*(int*)((char*)this + 0x14) - *(int*)((char*)this + 0x10)) / 0x104 - 1;
    U32Vec* sv = (U32Vec*)((char*)e + 0xbc);
    for (int i = 0; i < num; ++i) {
        u32* p = sv->mpEnd;
        if (p < sv->mpCap) {
            sv->mpEnd = p + 1;
            if (p)
                *p = (u32)last;
        } else {
            sv->DoInsertValue(p, (const u32&)last);
        }
        int k = *(int*)(sv->mpBegin + i);
        *(int*)(k * 0x108 + *(int*)((char*)this + 0x24) + 0xc4) = top;
        ++last;
    }
}

// ---------------------------------------------------------------------------------------------
// 0x009db4d0 -- clear the +0x24 table, seed the index vector, then walk the list
// ---------------------------------------------------------------------------------------------
// @ 0x009db4d0
void Anim::A4d0(float f)
{
    FUN_009d7b20(*(void**)((char*)this + 0x24), *(void**)((char*)this + 0x28), 0);
    Elem* e = A330();
    int n = (*(int*)((char*)this + 0x28) - *(int*)((char*)this + 0x24)) / 0x108;
    U32Vec* sv = (U32Vec*)((char*)e + 0xbc);
    for (int i = 0; i < n; ++i) {
        u32* p = sv->mpEnd;
        if (p < sv->mpCap) {
            sv->mpEnd = p + 1;
            if (p)
                *p = (u32)i;
        } else {
            sv->DoInsertValue(p, (const u32&)i);
        }
    }
    int x = FUN_009d3410(f);
    while (x != 0) {
        u32 v = FUN_009d0ee0();
        A3f0((void*)x, (int)v);
        x = FUN_009d3410(f);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x009db590 -- record one or two indices and forward to the +0x38 table
// ---------------------------------------------------------------------------------------------
// @ 0x009db590
int Anim::A590(void* a, void* b, int c)
{
    Elem* e = A330();
    U32Vec* sv = (U32Vec*)((char*)e + 0xbc);
    u32* p = sv->mpEnd;
    if (p < sv->mpCap) {
        sv->mpEnd = p + 1;
        if (p)
            *p = (u32)c;
    } else {
        sv->DoInsertValue(p, (const u32&)c);
    }
    int r = 1;
    if (a != b) {
        c = c + 1;
        p = sv->mpEnd;
        if (p < sv->mpCap) {
            sv->mpEnd = p + 1;
            if (p)
                *p = (u32)c;
        } else {
            sv->DoInsertValue(p, (const u32&)c);
        }
        r = 2;
    }
    ((Ops*)e)->F2dd0((char*)this + 0x38, a, b);
    return r;
}

// ---------------------------------------------------------------------------------------------
// 0x009db630 -- pick the lower bone (when comparable) and append its index pair
// ---------------------------------------------------------------------------------------------
// @ 0x009db630
int Anim::A630(Solver** ps, Bone** pa, Bone** pb, int c)
{
    Solver* s = *ps;
    Bone* a = *pa;
    Bone* b = *pb;
    if (!s->Fn3430(a, b) || s->Fn5700(a, b)) {
        int i = s->Fn57b0(a, b);
        pa = pb = (Bone**)(i * 0x30 + *(int*)((char*)this + 0x38));
    }
    unsigned n = (unsigned)((*(int*)((char*)this + 0x14) - *(int*)((char*)this + 0x10)) / 0x104);
    if (n < 6)
        return A590(pa, pb, c);
    return 0;
}

// =============================================================================================
// EASTL heap / introsort instantiations for Elem
// =============================================================================================

// @ 0x009da6c0
void FUN_009da6c0(Elem* first, Elem* last, Compare cmp)
{
    int n = (int)((char*)last - (char*)first) / 0x104;
    if (n >= 2) {
        int i = ((n - 2) >> 1) + 1;
        Elem* p = (Elem*)((char*)first + i * 0x104);
        do {
            --i;
            p = (Elem*)((char*)p - 0x104);
            FUN_009da170(first, i, n, i, *p, cmp);
        } while (i != 0);
    }
}

// @ 0x009da790
void FUN_009da790(Elem* first, Elem* last, Compare cmp)
{
    int n = (int)((char*)last - (char*)first) / 0x104;
    if (n >= 2) {
        int i = ((n - 2) >> 1) + 1;
        Elem* p = (Elem*)((char*)first + i * 0x104);
        do {
            --i;
            p = (Elem*)((char*)p - 0x104);
            FUN_009da2d0(first, i, n, i, *p, cmp);
        } while (i != 0);
    }
}

// @ 0x009da860
Elem* FUN_009da860(Elem* first, Elem* last, Elem pivot, Compare cmp)
{
    for (;;) {
        while (cmp.CmpA(*first, pivot))
            ++first;
        do {
            last = (Elem*)((char*)last - 0x104);
        } while (cmp.CmpA(pivot, *last));
        if (first >= last)
            return first;
        FUN_009d9f80(first, last);
        ++first;
    }
}

// @ 0x009dab00
Elem* FUN_009dab00(Elem* first, Elem* last, Elem pivot, Compare cmp)
{
    for (;;) {
        while (cmp.CmpB(*first, pivot))
            ++first;
        do {
            last = (Elem*)((char*)last - 0x104);
        } while (cmp.CmpB(pivot, *last));
        if (first >= last)
            return first;
        FUN_009d9f80(first, last);
        ++first;
    }
}

// @ 0x009da980
void FUN_009da980(Elem* first, Elem* middle, Elem* last, Compare cmp)
{
    FUN_009da6c0(first, middle, cmp);
    for (Elem* i = middle; i < last; ++i) {
        if (cmp.CmpA(*i, *first)) {
            Elem temp(*i);
            *i = *first;
            FUN_009da170(first, 0, (int)((char*)middle - (char*)first) / 0x104, 0, temp, cmp);
        }
    }
    FUN_009da730(first, middle, cmp);
}

// @ 0x009dac20
void FUN_009dac20(Elem* first, Elem* middle, Elem* last, Compare cmp)
{
    FUN_009da790(first, middle, cmp);
    for (Elem* i = middle; i < last; ++i) {
        if (cmp.CmpB(*i, *first)) {
            Elem temp(*i);
            *i = *first;
            FUN_009da2d0(first, 0, (int)((char*)middle - (char*)first) / 0x104, 0, temp, cmp);
        }
    }
    FUN_009da800(first, middle, cmp);
}

// @ 0x009daef0
void FUN_009daef0(Elem* first, Elem* last, int depth, Compare cmp)
{
    while (((char*)last - (char*)first) / 0x104 > 0x1c && depth > 0) {
        Elem* mid = (Elem*)((char*)first + ((char*)last - (char*)first) / 0x208 * 0x104);
        Elem* med = FUN_009d8be0(first, mid, (Elem*)((char*)last - 0x104), cmp, cmp);
        Elem* cut = FUN_009da860(first, last, *med, cmp);
        --depth;
        FUN_009daef0(cut, last, depth, cmp);
        last = cut;
    }
    if (depth == 0)
        FUN_009da980(first, last, last, cmp);
}

// @ 0x009dafd0
void FUN_009dafd0(Elem* first, Elem* last, int depth, Compare cmp)
{
    while (((char*)last - (char*)first) / 0x104 > 0x1c && depth > 0) {
        Elem* mid = (Elem*)((char*)first + ((char*)last - (char*)first) / 0x208 * 0x104);
        Elem* med = FUN_009d8ce0(first, mid, (Elem*)((char*)last - 0x104), cmp, cmp);
        Elem* cut = FUN_009dab00(first, last, *med, cmp);
        --depth;
        FUN_009dafd0(cut, last, depth, cmp);
        last = cut;
    }
    if (depth == 0)
        FUN_009dac20(first, last, last, cmp);
}

// @ 0x009db0b0
void FUN_009db0b0(Elem* first, Elem* last, Compare cmp)
{
    if (first != last) {
        int n = (int)((char*)last - (char*)first) / 0x104;
        int i = n;
        int depth = 0;
        while (i != 0) {
            i >>= 1;
            ++depth;
        }
        FUN_009daef0(first, last, depth * 2 - 2, cmp);
        if (n > 0x1c) {
            FUN_009d9840(first, (Elem*)((char*)first + 0x1c70), cmp);
            FUN_009d9970((Elem*)((char*)first + 0x1c70), last, cmp);
        } else {
            FUN_009d9840(first, last, cmp);
        }
    }
}

// @ 0x009db140
void FUN_009db140(Elem* first, Elem* last, Compare cmp)
{
    if (first != last) {
        int n = (int)((char*)last - (char*)first) / 0x104;
        int i = n;
        int depth = 0;
        while (i != 0) {
            i >>= 1;
            ++depth;
        }
        FUN_009dafd0(first, last, depth * 2 - 2, cmp);
        if (n > 0x1c) {
            FUN_009d9a90(first, (Elem*)((char*)first + 0x1c70), cmp);
            FUN_009d9bc0((Elem*)((char*)first + 0x1c70), last, cmp);
        } else {
            FUN_009d9a90(first, last, cmp);
        }
    }
}
