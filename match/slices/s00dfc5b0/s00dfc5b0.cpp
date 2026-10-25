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
    Vec44& assignFrom(const Vec44& o);           // 0x00dfcb00 (retail: operator=)
private:
    // declared, never defined: suppresses the implicit memberwise copy-assign so that
    // `vec = other` cannot silently copy the three pointers instead of the elements
    Vec44& operator=(const Vec44& o);
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
};
// the 0x34-element range helpers: this=ecx, real args on the stack, callee pops them
extern "C" void* __fastcall FUN_00dfc690(void* self, int dummy, unsigned n, void* first,
                                         void* last);                    // 0x00dfc690 (ret 0xc)
extern "C" void* __cdecl FUN_00dfc170(void* first, void* last, void* dest); // 0x00dfc170 (caller cleans)
extern "C" void  __fastcall FUN_00dfb850(void* self, int dummy, void* first, void* last); // 0x00dfb850

struct Vec34 {
    void* mpBegin;           // +0x00
    void* mpEnd;             // +0x04
    void* mpCap;             // +0x08
    char  pad0c[0x14 - 0xc];
    void* mOwner;            // +0x14
    Vec34& assignFrom(const Vec34& o);            // 0x00dfcee0 (retail: operator=)
private:
    Vec34& operator=(const Vec34& o);             // never defined (see Vec44)
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
    int   mField00;          // +0x00 sign flag
    char  pad_04[0x2c - 0x04];
    void* mp2c;              // +0x2c
    void* mp30;              // +0x30
    char pad_34[0x210 - 0x34];
    int   mField210;         // +0x210
    void dtor();
};
// @ 0x00dfcc40
void BlobC40::dtor() {
    if (mField00 < 0) return;
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
    mVec.assignFrom(o.mVec);
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
    mVec.assignFrom(o.mVec);
    m184 = o.m184;
    return *this;
}

// ===========================================================================
//  0x00dfcce0  BigRec copy ctor
// ===========================================================================
// BigRec's tail helpers, called with the real (ret 4) convention.
extern "C" void __fastcall FUN_00423650(void* self, int dummy, void* b, void* e); // 0x00423650 (ret 8)
extern "C" void* __fastcall FUN_00c06b10(void* self, int dummy, const void* src); // 0x00c06b10
extern "C" void* __fastcall FUN_006b5430(void* self, int dummy, const void* src); // 0x006b5430
// @ 0x00dfcce0
BigRec& BigRec::ctorr(const BigRec& o) {
    m00 = o.m00;
    m01 = o.m01;
    m02 = o.m02;
    mVec04.assignFrom(o.mVec04);
    mVec170.assignFrom(o.mVec170);
    mVec2dc.assignFrom(o.mVec2dc);
    FUN_006b5430((char*)this + 0x448, 0, (const char*)&o + 0x448);
    if ((char*)&o + 0x45c != (char*)this + 0x45c)
        FUN_00423650((char*)this + 0x45c, 0, o.mW45c, o.mW460);
    m46c = o.m46c;
    m470 = o.m470;
    if ((char*)&o + 0x474 != (char*)this + 0x474)
        FUN_00423650((char*)this + 0x474, 0, o.mW474, o.mW478);
    f484 = o.f484;
    f488 = o.f488; f48c = o.f48c; f490 = o.f490; f494 = o.f494;
    f498 = o.f498; f49c = o.f49c; f4a0 = o.f4a0;
    m4a4 = o.m4a4; m4a8 = o.m4a8; m4ac = o.m4ac; m4b0 = o.m4b0;
    m4b4 = o.m4b4; m4b8 = o.m4b8; m4bc = o.m4bc; m4c0 = o.m4c0; m4c4 = o.m4c4;
    m4c8 = o.m4c8;
    FUN_00c06b10((char*)this + 0x4cc, 0, (const char*)&o + 0x4cc);
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
//  0x00dfcee0  Vec34::assignFrom   (retail: operator=)
// ===========================================================================
// @ 0x00dfcee0
Vec34& Vec34::assignFrom(const Vec34& o) {
    if ((void*)&o == (void*)this)
        return *this;
    Vec34M* t = (Vec34M*)this;
    Vec34M* s = (Vec34M*)&o;
    unsigned n = (unsigned)((char*)s->mpEnd - (char*)s->mpBegin) / 0x34;
    unsigned c = (unsigned)((char*)t->mpCap - (char*)t->mpBegin) / 0x34;
    if (c < n) {
        void* p = FUN_00dfc690(t, 0, n, s->mpBegin, s->mpEnd);
        FUN_00dfb850(t, 0, t->mpBegin, t->mpEnd);
        if (t->mpBegin && *(int*)((char*)t->mpBegin - 4) != 0)
            operator_delete(t->mpBegin);
        t->mpEnd   = (char*)p + n * 0x34;
        t->mpBegin = p;
        t->mpCap   = (char*)p + n * 0x34;
        return *this;
    }
    unsigned sz = (unsigned)((char*)t->mpEnd - (char*)t->mpBegin) / 0x34;
    if (sz < n) {
        FUN_00dfc170(s->mpBegin, (char*)s->mpBegin + sz * 0x34, t->mpBegin);
        void* srcEnd = s->mpEnd;
        void* dstMid = (char*)t->mpBegin + sz * 0x34;
        vec34UninitCopy(&t->mpEnd, (char*)s->mpBegin + sz * 0x34, srcEnd, dstMid,
                        srcEnd);
        t->mpEnd = (char*)t->mpBegin + n * 0x34;
        return *this;
    }
    char* p2 = (char*)FUN_00dfc170(s->mpBegin, s->mpEnd, t->mpBegin);
    FUN_00dfb850(t, 0, p2, t->mpEnd);
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
        d->mVec.assignFrom(s->mVec);
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
    mVec28.assignFrom(o.mVec28);
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
            p->mVec.assignFrom(s->mVec);
            p->m184 = s->m184;
        }
        *cur = *cur + 0x188;
    }
    return cur;
}

// ===========================================================================
// Helpers shared with the 0xdfb5b0 container family (bodies live there; these
// declarations are the call ABI observed at the s00dfc5b0 call sites).
// ===========================================================================
extern "C" void* __cdecl UninitCopyD(void* out, const void* first, const void* last,
                                     void* dest, const void* arg5);   // 0x00dfb8e0
extern "C" void* __cdecl CopyAssignD(void* first, void* last, void* dest);   // 0x00dfb930
extern "C" void* __cdecl placeCopy20(void** cur, void* first, void* last, void* dst,
                                     const void* arg5);               // 0x00c04920
extern "C" void  __fastcall FUN_00f28240(void* p, int dummy);   // 0x00f28240 (retail ret 4)
extern "C" void  __cdecl FUN_00f47380(void* p);   // 0x00f47380 (EA_Free)
extern "C" void  __fastcall FUN_00423650(void* self, int dummy, void* b, void* e);   // 0x00423650 (ret 8)
extern "C" void  __fastcall FUN_00dfaaf0(void* self, int dummy, void* first, void* last); // 0x00dfaaf0
extern "C" void* __fastcall FUN_00dfc1e0(void* self, int dummy, unsigned n, void* first,
                                         void* last);                 // 0x00dfc1e0
extern "C" void  __fastcall FUN_00dfa400(void* self, int dummy, unsigned n, void* srcBuf); // 0x00dfa400
extern "C" void* __fastcall FUN_008105b0(void* self, int dummy, u32 id, int recursive); // 0x008105b0
extern "C" void  __fastcall FUN_00812160(void* layout, int dummy, void* name, u32 type,
                                         int a, u32 id);                  // 0x00812160
extern "C" void  __fastcall FUN_0093a1a0(void* self, int dummy, int units);   // 0x0093a1a0
extern "C" void  __fastcall FUN_007c4010(void* viewer, int dummy, int* out);  // 0x007c4010
extern "C" void* __cdecl FUN_0067dd10();          // 0x0067dd10  SP::App

// ===========================================================================
//  0x00dfc6f0  cSPUILayout::Init for the "GGENewScenariov3" panel list
// ===========================================================================
struct GgeLayout {
    char   pad_00[0x0c];
    void*  mpVecBegin;       // +0x0c  eastl vector of 0x24-byte panel entries
    void*  mpVecEnd;         // +0x10
    void*  mpVecCap;         // +0x14
    u8     pad_18[0x38 - 0x18];
    u8     pad_38[0x48 - 0x38];
    u8     mWin48[0x18];     // +0x48  UI window subobject
    u8     mStop60[0x1c];    // +0x60  EA::Stopwatch
    void Init();
};

struct GgeEntry {                      // 0x24-byte element of the +0x0c vector
    u32      f0;                       // +0x00  label ID + index
    u32      f4, f8;                   // +0x04, +0x08
    u8       fC;                       // +0x0c
    u8       pad0d[3];
    void*    mpStrBegin;               // +0x10  wstring buffer (owned)
    void*    mpStrEnd;                 // +0x14
    void*    mpStrCap;                 // +0x18
    u32      gap1c;                    // +0x1c  (not copied by the 0x24 copy ctor)
    u32      f20;                      // +0x20
    void Dtor();
};

void GgeEntry::Dtor() {
    char* b = (char*)mpStrBegin;
    if ((((int)((char*)mpStrCap - b) & 0xfffffffe)) > 2 && b)
        FUN_00f47380(b);
}

struct GgeWin {
    void  SetLocation(float x, float y);   // vtbl +0x64
    float* GetArea();                      // vtbl +0x38
    void  SetFlag(int a, int b);           // vtbl +0x7c
};
struct GgeRect { int left, top, right, bottom; };

static __forceinline void* Vfn(void* p, int slot) { return (*(void***)p)[slot / 4]; }

// One "GGENewScenariov3" panel entry: a 0x24-byte record whose WString is assigned
// from the given literal, then appended to the layout's own vector at +0x0c.
static __forceinline void AddPanelEntry(void* self, u32 i, const wchar_t* name) {
    char* s = (char*)self;
    GgeEntry e2;
    e2.f0 = 0x7bfb2a0 + i;
    e2.f4 = 0x5384d05 + i;
    e2.f8 = 0x5933fe0 + i;
    e2.mpStrBegin = e2.mpStrEnd = e2.mpStrCap = 0;
    ((void (__fastcall*)(void*, int, const wchar_t*))0x579a90)(&e2.mpStrBegin, 0, name);
    e2.fC = 1;
    e2.f20 = i + 1;
    GgeEntry* end = *(GgeEntry**)(s + 0x10);
    if ((void*)end < *(void**)(s + 0x14)) {
        *(void**)(s + 0x10) = (char*)end + 0x24;
        if (end) ((void (__fastcall*)(void*, int, GgeEntry*))0xdfb130)(end, 0, &e2);
    } else {
        ((void (__fastcall*)(void*, int, void*, GgeEntry*))0xdfc000)(s + 0x0c, 0, end, &e2);
    }
    e2.Dtor();
}

// @ 0x00dfc6f0
void GgeLayout::Init() {
    char* self = (char*)this;
    const wchar_t* base = (const wchar_t*)0x147ef18;      // L"GGENewScenariov3"
    const wchar_t* e = base;
    do { ++e; } while (*e);
    FUN_00423650(self + 0x38, 0, (void*)base, (void*)e);
    FUN_00812160(self + 0x48, 0, *(void**)(self + 0x38), 0x40464100u, 1, 0x5b598fau);
    FUN_0093a1a0(self + 0x60, 0, 5);
    GgeRect client;    void* app = FUN_0067dd10();
    void* mainWin = ((void* (__fastcall*)(void*, int))Vfn(app, 0x58))(app, 0);
    FUN_007c4010(mainWin, 0, (int*)&client);
    float cx = (float)((client.right - client.left) / 2);
    float cy = (float)((client.bottom - client.top) / 2);
    void* win = FUN_008105b0(self + 0x48, 0, 0x733ebd5u, 1);
    if (win) {
        float* a = ((float* (__fastcall*)(void*, int))Vfn(win, 0x38))(win, 0);
        const float k = *(float*)0x1471064;
        ((void (__fastcall*)(void*, int, float, float))Vfn(win, 0x64))(
            win, 0, cx - (a[2] - a[0]) * k, cy - (a[3] - a[1]) * k);
        ((void (__fastcall*)(void*, int, int, int))Vfn(win, 0x7c))(win, 0, 1, 0);
    }
    AddPanelEntry(self, 0, (const wchar_t*)0x147eef4);     // "choose adventure"
    AddPanelEntry(self, 1, (const wchar_t*)0x147eecc);     // "choose captain name"
    AddPanelEntry(self, 2, (const wchar_t*)0x147eecc);     // "choose captain name"
    AddPanelEntry(self, 3, (const wchar_t*)0x147eeb0);     // "choose posse"
}

// ===========================================================================
//  0x00dfcb00  Vec44::assignFrom   (retail: operator=)
// ===========================================================================
// @ 0x00dfcb00
Vec44& Vec44::assignFrom(const Vec44& o) {
    if ((void*)&o == (void*)this)
        return *this;
    unsigned n = (unsigned)((char*)o.mpEnd - (char*)o.mpBegin) / 0x44;
    unsigned c = (unsigned)((char*)mpCap - (char*)mpBegin) / 0x44;
    if (c < n) {
        void* p = FUN_00dfc1e0(this, 0, n, o.mpBegin, o.mpEnd);
        FUN_00dfaaf0(this, 0, mpBegin, mpEnd);
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
            operator_delete(mpBegin);
        mpBegin = p;
        mpCap   = (char*)p + n * 0x44;
    } else {
        unsigned sz = (unsigned)((char*)mpEnd - (char*)mpBegin) / 0x44;
        if (sz < n) {
            CopyAssignD(o.mpBegin, (char*)o.mpBegin + sz * 0x44, mpBegin);
            void* srcEnd = o.mpEnd;
            UninitCopyD(&srcEnd, (char*)o.mpBegin + sz * 0x44, o.mpEnd, mpEnd,
                        o.mpEnd);
        } else {
            void* dst = CopyAssignD(o.mpBegin, o.mpEnd, mpBegin);
            FUN_00dfaaf0(this, 0, dst, mpEnd);
        }
    }
    mpEnd = (char*)mpBegin + n * 0x44;
    return *this;
}

// ===========================================================================
//  0x00dfd080  Huge copy ctor (self-allocating inline Vec44 buffers)
// ===========================================================================
struct Huge {
    u8    m00, m01, m02;     // +0x00
    u8    pad03;
    Vec44 mVec04;            // +0x04  inline buffer at +0x1c, capacity 0x154
    char  pad1c[0x170 - 0x1c];
    Vec44 mVec170;           // +0x170
    char  pad188[0x2dc - 0x188];
    Vec44 mVec2dc;           // +0x2dc
    char  pad2f4[0x448 - 0x2f4];
    void* mSub448;           // +0x448  0x38-byte sub-object (0x00dfb280 copy ctor)
    char  pad44c[0x484 - 0x44c];
    float f484, f488, f48c, f490, f494, f498, f49c, f4a0;
    u32   m4a4, m4a8, m4ac, m4b0, m4b4, m4b8, m4bc, m4c0, m4c4;
    u8    m4c8;              // +0x4c8
    char  pad4c9[0x4cc - 0x4c9];
    void* mp4ccBegin;        // +0x4cc  eastl vector of 0x20-byte elements
    void* mp4ccEnd;          // +0x4d0
    void* mp4ccCap;          // +0x4d4
    char  pad4d8[4];
    Huge& copyCtor(const Huge& o);
};
extern "C" void* __fastcall FUN_00dfb280(void* self, int dummy, const void* src);  // 0x00dfb280

// @ 0x00dfd080
Huge& Huge::copyCtor(const Huge& o) {
    m00 = o.m00;
    m01 = o.m01;
    m02 = o.m02;
    struct Init { static void Run(Vec44* v) {
        char* beg = (char*)v + 0x18;
        v->mpBegin = beg;
        v->mpEnd   = beg;
        v->mpCap   = beg + 0x154;
        v->mOwner  = 0;
    } };
    Init::Run(&mVec04);
    mVec04.assignFrom(o.mVec04);
    Init::Run(&mVec170);
    mVec170.assignFrom(o.mVec170);
    Init::Run(&mVec2dc);
    mVec2dc.assignFrom(o.mVec2dc);
    FUN_00dfb280((char*)this + 0x448, 0, (const char*)&o + 0x448);
    f484 = o.f484; f488 = o.f488; f48c = o.f48c; f490 = o.f490;
    f494 = o.f494; f498 = o.f498; f49c = o.f49c; f4a0 = o.f4a0;
    m4a4 = o.m4a4; m4a8 = o.m4a8; m4ac = o.m4ac; m4b0 = o.m4b0;
    m4b4 = o.m4b4; m4b8 = o.m4b8; m4bc = o.m4bc; m4c0 = o.m4c0; m4c4 = o.m4c4;
    m4c8 = o.m4c8;
    unsigned n = (unsigned)((char*)o.mp4ccEnd - (char*)o.mp4ccBegin) / 0x20;
    FUN_00dfa400(&mp4ccBegin, 0, n, (char*)&o + 0x4d8);
    void* cur = mp4ccBegin;
    placeCopy20(&cur, o.mp4ccBegin, o.mp4ccEnd, mp4ccBegin, &o);
    mp4ccEnd = cur;
    return *this;
}
