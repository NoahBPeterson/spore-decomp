// Slice s00dfc5b0 (batch bfs1 #37).  UI-layout / vector helpers (GGE editor
// scenario layout).  32-bit MSVC 2008 SP1, /O2 /arch=SSE.
//
// The 0x188-byte record is a UI-layout entry:
//   +0x00 u8[3] m00,m01,m02 ; +0x04.. u32 fields ; +0x18 eastl vector (0x18 header,
//   inline 0x44-element buffer at +0x30 .. +0x184) ; +0x184 u32 tail.

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern "C" void __cdecl operator_delete(void* p);
extern "C" void __cdecl sub_f280f0(void* p);   // (element + 4) destructor

struct Elem44  { void sub_f280f0(); };
struct Elem4e0 { void sub_dfbba0(); };
struct Sub28Vec { void sub_dfb850(void* first, void* last); };

// ---------------------------------------------------------------------------
// eastl vector of 0x44-byte values (header 0x18 incl. allocator owner at +0x14)
// ---------------------------------------------------------------------------
struct Val44 { char pad00[0x14]; void* mOwner; char pad18[0x44 - 0x18]; };

struct Vec44 {
    void* mpBegin;           // +0x00
    void* mpEnd;             // +0x04
    void* mpCap;             // +0x08
    char  pad0c[0x14 - 0xc];
    void* mOwner;            // +0x14  (0 => self-allocating)
    Vec44& operator=(const Vec44& o);            // 0x00dfcb00 (member asm)
};

// ---------------------------------------------------------------------------
// eastl vector of 0x34-byte values
// ---------------------------------------------------------------------------
struct Val34 { char pad00[0x14]; void* mOwner; char pad18[0x34 - 0x18]; };

struct Vec34M {
    void* mpBegin;           // +0x00
    void* mpEnd;             // +0x04
    void* mpCap;             // +0x08
    char  pad0c[0x14 - 0xc];
    void* mOwner;            // +0x14
    void* alloc(u32 n, void* first, void* last);                 // 0x00dfc690
    void* copyCtorRange(void* srcF, void* srcL, void* dst);      // 0x00dfc170
    void  destroyRange(void* first, void* last);                 // 0x00dfb850
    Vec34M& operator=(const Vec34M& o);                          // 0x00dfcee0
};

struct Vec34 {
    void* mpBegin;           // +0x00
    void* mpEnd;             // +0x04
    void* mpCap;             // +0x08
    char  pad0c[0x14 - 0xc];
    void* mOwner;            // +0x14
    Vec34& operator=(const Vec34& o);            // 0x00dfcee0
};

extern "C" void  __cdecl vec34UninitCopy(void** out, void* f, void* l,
                                         void* d, void* last);            // 0x00dfbc80

// ---------------------------------------------------------------------------
// 0x188-byte UI-layout entry
// ---------------------------------------------------------------------------
struct Entry188 {
    u32   m00, m04, m08, m0c;    // +0x00 .. +0x0c
    u8    m10;                   // +0x10
    char  pad11[3];
    u32   m14;                   // +0x14
    Vec44 mVec;                  // +0x18  (mVec.mOwner at +0x2c)
    char  pad30[0x184 - 0x30];   // inline 0x44-element storage
    u32   m184;                  // +0x184
    Entry188& operator=(const Entry188& o);      // 0x00dfcc90
    Entry188& ctorr(const Entry188& o);          // 0x00dfd020
};

// ---------------------------------------------------------------------------
// 0x38-byte entry with a 0x34-element vector (external vector assign)
// ---------------------------------------------------------------------------
struct Vec38 {
    void* mpBegin;           // +0x00
    void* mpEnd;             // +0x04
    void* mpCap;             // +0x08
    char  pad0c[0x14 - 0xc];
    u8    mOwner;            // +0x14
    Vec38& operator=(const Vec38& o);            // 0x006a1e80 (external)
};

struct Entry38 {
    char  pad00[8];
    u32   m08, m0c, m10, m14;
    Vec38 mVec;              // +0x18
    void* mp30;              // +0x30  (ref-counted: v[0] AddRef, v[4] Release)
    u32   m34;               // +0x34
    Entry38& operator=(const Entry38& o);        // 0x00dfca50
};

// ---------------------------------------------------------------------------
// 0x4cc+ byte editor record for the D3A0 / CC E0 copies
// ---------------------------------------------------------------------------
struct FVec {                                     // float vector at +0x20c
    char pad00[0x14];
    FVec& operator=(const FVec& o);               // 0x0050d4e0 (external)
};

struct BigRec {
    u8    m00, m01, m02;     // +0x00
    u8    pad03;
    Vec44 mVec04;            // +0x04
    char  pad1c[0x170 - 0x1c];
    Vec44 mVec170;           // +0x170
    char  pad188[0x2dc - 0x188];
    Vec44 mVec2dc;           // +0x2dc
    char  pad2f4[0x448 - 0x2f4];
    void* mStr448;           // +0x448  (cString; assign 0x006b5430)
    char  pad44c[0x45c - 0x44c];
    void* mW45c;             // +0x45c  (wstring range)
    void* mW460;             // +0x460
    u32   m46c;              // +0x46c
    u32   m470;              // +0x470
    void* mW474;             // +0x474
    void* mW478;             // +0x478
    float f484;              // +0x484
    float f488, f48c, f490, f494, f498, f49c, f4a0;
    u32   m4a4, m4a8, m4ac, m4b0, m4b4, m4b8, m4bc, m4c0, m4c4;
    u8    m4c8;              // +0x4c8
    char  pad4c9[0x4cc - 0x4c9];
    BigRec& ctorr(const BigRec& o);               // 0x00dfcce0
};

// ---------------------------------------------------------------------------
// 0x238-byte record for the D3A0 copy ctor
// ---------------------------------------------------------------------------
struct Sub028 {
    u32   m00, m04, m08, m0c, m10, m14, m18, m1c;
    float f20, f24;                               // +0x20, +0x24
    Vec34 mVec28;                                 // +0x28
    char  pad40[0x1e0 - 0x40];
    float f1e0, f1e4;                             // +0x1e0, +0x1e4
    u32   m1e8, m1ec, m1f0, m1f4, m1f8, m1fc, m200;
    float f204;                                   // +0x204
    u8    b208, b209;                             // +0x208, +0x209
    char  pad20a[0x20c - 0x20a];
    FVec  m20c;                                   // +0x20c
    float f220;                                   // +0x220
    u32   m224, m228, m22c, m230;
    Sub028& operator=(const Sub028& o);           // 0x00dfd3a0
};

// ===========================================================================
//  0x00dfc5b0  destructor: delete two arrays
// ===========================================================================
struct Blob5b0 {
    char pad_00[0x28];
    void* mp28;              // +0x28
    void* mp2c;              // +0x2c
    char pad_30[0x20c - 0x30];
    void* mp20c;             // +0x20c
    void dtor();
};
// @ 0x00dfc5b0
void Blob5b0::dtor() {
    if (mp20c && *(int*)((char*)mp20c - 4) != 0) operator_delete(mp20c);
    ((Sub28Vec*)((char*)this + 0x28))->sub_dfb850(mp28, mp2c);
    void* b = *(void**)((char*)this + 0x28);
    if (b && *(int*)((char*)b - 4) != 0) operator_delete(b);
}

// ===========================================================================
//  0x00dfc600  range destructor, stride 0x188, inner vector of 0x44 elements
// ===========================================================================
struct EffectVec { void EraseRange(void* first, void* last); };
// @ 0x00dfc600
void EffectVec::EraseRange(void* firstP, void* lastP) {
    char* first = (char*)firstP;
    char* last = (char*)lastP;
    for (; first < last; first += 0x188) {
        u32 end = *(u32*)(first + 0x1c);
        for (u32 e = *(u32*)(first + 0x18); e < end; e += 0x44) {
            ((Elem44*)(e + 4))->sub_f280f0();
        }
        int p = *(int*)(first + 0x18);
        if (p && *(int*)(p - 4) != 0) operator_delete((void*)p);
    }
}

// ===========================================================================
//  0x00dfca50  Entry38::operator=
// ===========================================================================
// @ 0x00dfca50
Entry38& Entry38::operator=(const Entry38& o) {
    m08 = o.m08;
    m0c = o.m0c;
    m10 = o.m10;
    m14 = o.m14;
    Vec38* s = (Vec38*)&o.mVec;
    Vec38* d = (Vec38*)&mVec;
    d->operator=(*s);
    d->mOwner = s->mOwner;
    void* src = o.mp30;
    void* cur = mp30;
    if (src != cur) {
        if (src) {
            typedef void (__thiscall *RefFn)(void*);
            RefFn f = *(RefFn*)(*(void**)src);
            f(src);
        }
        mp30 = src;
        if (cur) {
            typedef void (__thiscall *RefFn)(void*);
            RefFn f = *(RefFn*)((char*)*(void**)cur + 4);
            f(cur);
        }
    }
    m34 = o.m34;
    return *this;
}

// ===========================================================================
//  0x00dfcac0  destroy vector of 0x4e0-byte elements
// ===========================================================================
struct BlobAC0 {
    u32 mpBegin;             // +0x00
    u32 mpEnd;               // +0x04
    void dtor();
};
// @ 0x00dfcac0
void BlobAC0::dtor() {
    u32 end = mpEnd;
    for (u32 e = mpBegin; e < end; e += 0x4e0) ((Elem4e0*)e)->sub_dfbba0();
    u32 v = mpBegin;
    if (v && *(int*)(v - 4) != 0) operator_delete((void*)v);
}

// ===========================================================================
//  0x00dfcc40  conditional destructor (uses this+0x210, +0x2c, +0x30)
// ===========================================================================
struct BlobC40 {
    char pad_00[0x2c];
    void* mp2c;              // +0x2c
    void* mp30;              // +0x30
    char pad_34[0x210 - 0x34];
    int   mField210;         // +0x210
    void dtor();
};
// @ 0x00dfcc40
void BlobC40::dtor() {
    if (mField210 < 0) return;
    int a = mField210;
    if (a && *(int*)(a - 4) != 0) operator_delete((void*)a);
    ((Sub28Vec*)((char*)this + 0x2c))->sub_dfb850(mp2c, mp30);
    int b = *(int*)((char*)this + 0x2c);
    if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
}

// ===========================================================================
//  0x00dfcc90  Entry188::operator=
// ===========================================================================
// @ 0x00dfcc90
Entry188& Entry188::operator=(const Entry188& o) {
    m00 = o.m00;
    m04 = o.m04;
    m08 = o.m08;
    m0c = o.m0c;
    m10 = o.m10;
    m14 = o.m14;
    mVec = o.mVec;
    m184 = o.m184;
    return *this;
}

// ===========================================================================
//  0x00dfd020  Entry188 self-allocating copy ctor
// ===========================================================================
// @ 0x00dfd020
Entry188& Entry188::ctorr(const Entry188& o) {
    m00 = o.m00;
    m04 = o.m04;
    m08 = o.m08;
    m0c = o.m0c;
    m10 = o.m10;
    m14 = o.m14;
    Vec44* v = &mVec;
    char* beg = (char*)v + 0x18;
    v->mpBegin = beg;
    v->mpEnd   = beg;
    v->mpCap   = beg + 0x154;
    v->mOwner  = 0;
    mVec = o.mVec;
    m184 = o.m184;
    return *this;
}

// ===========================================================================
//  0x00dfcce0  BigRec copy ctor
// ===========================================================================
struct CString448 { CString448& operator=(const CString448& o); };      // 0x006b5430
struct WString { void assign(void* first, void* last); };              // 0x00423650
struct Tail4cc { void assign(const Tail4cc& o); };                     // 0x00c06b10
// @ 0x00dfcce0
BigRec& BigRec::ctorr(const BigRec& o) {
    m00 = o.m00;
    m01 = o.m01;
    m02 = o.m02;
    mVec04 = o.mVec04;
    mVec170 = o.mVec170;
    mVec2dc = o.mVec2dc;
    ((CString448*)((char*)this + 0x448))->operator=(*(CString448*)((const char*)&o + 0x448));
    if ((char*)&o + 0x45c != (char*)this + 0x45c)
        ((WString*)((char*)this + 0x45c))->assign(o.mW45c, o.mW460);
    m46c = o.m46c;
    m470 = o.m470;
    if ((char*)&o + 0x474 != (char*)this + 0x474)
        ((WString*)((char*)this + 0x474))->assign(o.mW474, o.mW478);
    f484 = o.f484;
    f488 = o.f488; f48c = o.f48c; f490 = o.f490; f494 = o.f494;
    f498 = o.f498; f49c = o.f49c; f4a0 = o.f4a0;
    m4a4 = o.m4a4; m4a8 = o.m4a8; m4ac = o.m4ac; m4b0 = o.m4b0;
    m4b4 = o.m4b4; m4b8 = o.m4b8; m4bc = o.m4bc; m4c0 = o.m4c0; m4c4 = o.m4c4;
    m4c8 = o.m4c8;
    ((Tail4cc*)((char*)this + 0x4cc))->assign(*(const Tail4cc*)((const char*)&o + 0x4cc));
    return *this;
}

// ===========================================================================
//  0x00dfce40  destructor chain
// ===========================================================================
struct Elem3c { void sub_f280f0(); };
struct BlobE40 {
    char pad_00[0x3c];
    Elem3c m3c;              // +0x3c
    char pad_40[0x84 - 0x40];
    void* mp84;              // +0x84
    void* mp88;              // +0x88
    void dtor();
};
// @ 0x00dfce40
void BlobE40::dtor() {
    ((EffectVec*)((char*)this + 0x84))->EraseRange(mp84, mp88);
    if (mp84 && *(int*)((char*)mp84 - 4) != 0) operator_delete(mp84);
    m3c.sub_f280f0();
    ((Elem3c*)this)->sub_f280f0();
}

// ===========================================================================
//  0x00dfce90  destructor: one member + vector of 0x4e0 elements
// ===========================================================================
struct BlobE90 {
    char pad_00[0x70];
    u32 mpBegin70;           // +0x70
    u32 mpEnd74;             // +0x74
    char pad_78[0x2788 - 0x78];
    Elem3c m2788;            // +0x2788
    void dtor();
};
// @ 0x00dfce90
void BlobE90::dtor() {
    m2788.sub_f280f0();
    u32 end = mpEnd74;
    for (u32 e = mpBegin70; e < end; e += 0x4e0) ((Elem4e0*)e)->sub_dfbba0();
    u32 v = mpBegin70;
    if (v && *(int*)(v - 4) != 0) operator_delete((void*)v);
}

// ===========================================================================
//  0x00dfcee0  Vec34::operator=
// ===========================================================================
// @ 0x00dfcee0
Vec34& Vec34::operator=(const Vec34& o) {
    if ((void*)&o == (void*)this)
        return *this;
    Vec34M* t = (Vec34M*)this;
    Vec34M* s = (Vec34M*)&o;
    unsigned n = (unsigned)((char*)s->mpEnd - (char*)s->mpBegin) / 0x34;
    unsigned c = (unsigned)((char*)t->mpCap - (char*)t->mpBegin) / 0x34;
    if (c < n) {
        void* p = t->alloc(n, s->mpBegin, s->mpEnd);
        t->destroyRange(t->mpBegin, t->mpEnd);
        if (t->mpBegin && *(int*)((char*)t->mpBegin - 4) != 0)
            operator_delete(t->mpBegin);
        t->mpEnd   = (char*)p + n * 0x34;
        t->mpBegin = p;
        t->mpCap   = (char*)p + n * 0x34;
        return *this;
    }
    unsigned sz = (unsigned)((char*)t->mpEnd - (char*)t->mpBegin) / 0x34;
    if (sz < n) {
        t->copyCtorRange(s->mpBegin, (char*)s->mpBegin + sz * 0x34, t->mpBegin);
        void* srcEnd = s->mpEnd;
        void* dstMid = (char*)t->mpBegin + sz * 0x34;
        vec34UninitCopy(&t->mpEnd, (char*)s->mpBegin + sz * 0x34, srcEnd, dstMid,
                        srcEnd);
        t->mpEnd = (char*)t->mpBegin + n * 0x34;
        return *this;
    }
    void* p2 = t->copyCtorRange(s->mpBegin, s->mpEnd, t->mpBegin);
    t->destroyRange(p2, t->mpEnd);
    t->mpEnd = (char*)t->mpBegin + n * 0x34;
    return *this;
}

// ===========================================================================
//  0x00dfd250  uninitialized_copy<0x188>
// ===========================================================================
// @ 0x00dfd250
char* uninitCopy188(char* first, char* last, char* dst) {
    for (; first != last; first += 0x188, dst += 0x188) {
        Entry188* d = (Entry188*)dst;
        Entry188* s = (Entry188*)first;
        d->m00 = s->m00;
        d->m04 = s->m04;
        d->m08 = s->m08;
        d->m0c = s->m0c;
        d->m10 = s->m10;
        d->m14 = s->m14;
        d->mVec = s->mVec;
        d->m184 = s->m184;
    }
    return dst;
}

// ===========================================================================
//  0x00dfd3a0  Sub028::operator=
// ===========================================================================
// @ 0x00dfd3a0
Sub028& Sub028::operator=(const Sub028& o) {
    m00 = o.m00; m04 = o.m04; m08 = o.m08; m0c = o.m0c;
    m10 = o.m10; m14 = o.m14; m18 = o.m18; m1c = o.m1c;
    f20 = o.f20;
    f24 = o.f24;
    mVec28 = o.mVec28;
    f1e0 = o.f1e0;
    f1e4 = o.f1e4;
    m1e8 = o.m1e8; m1ec = o.m1ec; m1f0 = o.m1f0; m1f4 = o.m1f4;
    m1f8 = o.m1f8; m1fc = o.m1fc; m200 = o.m200;
    f204 = o.f204;
    b208 = o.b208;
    b209 = o.b209;
    m20c = o.m20c;
    f220 = o.f220;
    m224 = o.m224; m228 = o.m228; m22c = o.m22c; m230 = o.m230;
    return *this;
}

// ===========================================================================
//  0x00dfd300  range destructor over 0x238-byte records
// ===========================================================================
// @ 0x00dfd300
void __cdecl d300(int* first, int* last) {
    if (first >= last) return;
    int* pi = first + 0x84;
    do {
        if (*first >= 0) {
            int x = *pi;
            if (x && *(int*)(x - 4) != 0) operator_delete((void*)x);
            u32 e1 = (u32)pi[-0x78];
            for (u32 u = (u32)pi[-0x79]; u < e1; u += 0x34) {
                int y = *(int*)(u + 0x1c);
                if (y && *(int*)(y - 4) != 0) operator_delete((void*)y);
            }
            int z = pi[-0x79];
            if (z && *(int*)(z - 4) != 0) operator_delete((void*)z);
        }
        first += 0x8e;
        pi += 0x8e;
    } while (first < last);
}

// ===========================================================================
//  0x00dfd4e0  placement copy<0x188>
// ===========================================================================
// @ 0x00dfd4e0
char** placeCopy188(char** cur, char* first, char* last, char* dst) {
    *cur = dst;
    for (; first != last; first += 0x188) {
        Entry188* p = (Entry188*)*cur;
        if (p) {
            Entry188* s = (Entry188*)first;
            p->m00 = s->m00;
            p->m04 = s->m04;
            p->m08 = s->m08;
            p->m0c = s->m0c;
            p->m10 = s->m10;
            p->m14 = s->m14;
            p->mVec.mpBegin = (char*)p + 0x30;
            p->mVec.mpEnd   = (char*)p + 0x30;
            p->mVec.mOwner  = 0;
            p->mVec.mpCap   = (char*)p + 0x184;
            p->mVec = s->mVec;
            p->m184 = s->m184;
        }
        *cur = *cur + 0x188;
    }
    return cur;
}

// ===========================================================================
//  Stubs restored from HEAD (dropped by the agent rewrite; still partial)
// ===========================================================================
// @ 0x00dfc6f0
void __fastcall c6f0(void* self) { (void)self; }
// @ 0x00dfcb00
void* __fastcall cb00(void* self, void* other) { (void)other; return self; }
// @ 0x00dfd080
void* __fastcall d080(void* self, void* other) { (void)other; return self; }
