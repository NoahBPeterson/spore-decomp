// Slice s00bdd380 -- 0x80-byte element copy/assignment, eastl range copy helpers and
// cGameData / cCity destructors.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-

typedef unsigned int  u32;
typedef unsigned char u8;

// ---------------------------------------------------------------- 0x80-byte element

// Reference-counted object reached through the element's +0x70 / +0x78 slots.
// AddRef/Release are virtual slots 0xbc and 0xc0.
struct CRefCounted {
    void **m_vtbl;                     // +0x00
    void AddRef()  { ((void (__thiscall *)(CRefCounted *))m_vtbl[0xbc / 4])(this); }
    void Release() { ((void (__thiscall *)(CRefCounted *))m_vtbl[0xc0 / 4])(this); }
};

// Embedded 0x20-byte sub-object at element+0x30 and element+0x50.
struct CElementSub {
    void *m_vtbl;                      // +0x00
    u32   m_u04;                       // +0x04
    u32   m_u08;                       // +0x08
    u32   m_u0c;                       // +0x0c
    u32   m_u10;                       // +0x10
    u32   m_u14;                       // +0x14
    u8    m_u18;                       // +0x18
    u8    m_pad19[3];                  // +0x19
    u32   m_u1c;                       // +0x1c
};

struct CElement {
    u32 m_u00;                         // +0x00
    u32 m_u04;                         // +0x04
    u32 m_u08;                         // +0x08
    u32 m_u0c;                         // +0x0c
    u32 m_u10;                         // +0x10
    u32 m_u14;                         // +0x14
    u32 m_u18;                         // +0x18
    u32 m_u1c;                         // +0x1c
    u8  m_u20;                         // +0x20
    u8  m_pad21[3];                    // +0x21
    float m_f24;                       // +0x24
    float m_f28;                       // +0x28
    float m_f2c;                       // +0x2c
    CElementSub m_a;                   // +0x30
    CElementSub m_b;                   // +0x50
    CRefCounted *m_p70;                // +0x70
    u8  m_u74;                         // +0x74
    u8  m_pad75[3];                    // +0x75
    CRefCounted *m_p78;                // +0x78
    u8  m_pad7c[4];                    // +0x7c

    __declspec(noinline) CElement *CopyConstructFrom(const CElement &src);   // 0x00bdd380
    __declspec(noinline) CElement *CopyAssignFrom(const CElement &src);      // 0x00bdd470
};

// Vtables installed while the embedded sub-objects are copy-constructed.
#define VTBL_SUB_BASE ((void *)0x1465d54)
#define VTBL_SUB_DERIVED ((void *)0x1464450)

// Compiler scheduling barrier (not assembly): keeps the sub-object construction
// order identical to the original translation unit.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

static __forceinline void CopySub(CElementSub &d, const CElementSub &s)
{
    d.m_vtbl = VTBL_SUB_BASE;
    d.m_u04 = 0;
    d.m_u08 = s.m_u08;
    d.m_u0c = s.m_u0c;
    d.m_u10 = s.m_u10;
    d.m_u14 = s.m_u14;
    d.m_u18 = s.m_u18;
    d.m_u1c = s.m_u1c;
    d.m_vtbl = VTBL_SUB_DERIVED;
}

// @ 0x00bdd380
CElement *CElement::CopyConstructFrom(const CElement &src)
{
    m_u00 = src.m_u00;
    m_u04 = src.m_u04;
    m_u08 = src.m_u08;
    m_u0c = src.m_u0c;
    m_u10 = src.m_u10;
    m_u14 = src.m_u14;
    m_u18 = src.m_u18;
    m_u1c = src.m_u1c;
    m_u20 = src.m_u20;
    m_f24 = src.m_f24;
    m_f28 = src.m_f28;
    m_f2c = src.m_f2c;

    CopySub(m_a, src.m_a);
    CopySub(m_b, src.m_b);

    m_p70 = src.m_p70;
    if (m_p70 != 0)
        m_p70->AddRef();
    m_u74 = src.m_u74;
    m_p78 = src.m_p78;
    if (m_p78 != 0)
        m_p78->AddRef();
    return this;
}

// @ 0x00bdd470
CElement *CElement::CopyAssignFrom(const CElement &src)
{
    m_u00 = src.m_u00;
    m_u04 = src.m_u04;
    m_u08 = src.m_u08;
    m_u0c = src.m_u0c;
    m_u10 = src.m_u10;
    m_u14 = src.m_u14;
    m_u18 = src.m_u18;
    m_u1c = src.m_u1c;
    m_u20 = src.m_u20;
    m_f24 = src.m_f24;
    m_f28 = src.m_f28;
    m_f2c = src.m_f2c;

    m_a.m_u08 = src.m_a.m_u08;
    m_a.m_u0c = src.m_a.m_u0c;
    m_a.m_u10 = src.m_a.m_u10;
    m_a.m_u14 = src.m_a.m_u14;
    m_a.m_u18 = src.m_a.m_u18;
    m_a.m_u1c = src.m_a.m_u1c;

    m_b.m_u08 = src.m_b.m_u08;
    m_b.m_u0c = src.m_b.m_u0c;
    m_b.m_u10 = src.m_b.m_u10;
    m_b.m_u14 = src.m_b.m_u14;
    m_b.m_u18 = src.m_b.m_u18;
    m_b.m_u1c = src.m_b.m_u1c;

    _ReadWriteBarrier();
    CRefCounted *new70 = src.m_p70;
    CRefCounted *old70 = m_p70;
    if (new70 != old70) {
        if (new70 != 0)
            new70->AddRef();
        m_p70 = new70;
        if (old70 != 0)
            old70->Release();
    }

    m_u74 = src.m_u74;

    _ReadWriteBarrier();
    CRefCounted *new78 = src.m_p78;
    CRefCounted *old78 = m_p78;
    if (new78 != old78) {
        if (new78 != 0)
            new78->AddRef();
        m_p78 = new78;
        if (old78 != 0)
            old78->Release();
    }
    return this;
}

// @ 0x00bdd580
CElement **__cdecl FUN_00bdd580(CElement **cursor, CElement *first, CElement *last, CElement *dest)
{
    *cursor = dest;
    while (first != last) {
        if (*cursor != 0)
            (*cursor)->CopyConstructFrom(*first);
        *cursor += 1;
        ++first;
    }
    return cursor;
}

// @ 0x00bdd5c0
CElement *__cdecl FUN_00bdd5c0(CElement *first, CElement *last, CElement *dest)
{
    while (first != last) {
        if (dest != 0)
            dest->CopyConstructFrom(*first);
        ++first;
        ++dest;
    }
    return dest;
}

// @ 0x00bdd600
CElement *__cdecl FUN_00bdd600(CElement *first, CElement *last, CElement *dest)
{
    while (first != last) {
        dest->CopyAssignFrom(*first);
        ++first;
        ++dest;
    }
    return dest;
}

// @ 0x00bdd640
CElement *__cdecl FUN_00bdd640(CElement *first, CElement *last, CElement *dest)
{
    while (last != first) {
        --last;
        --dest;
        dest->CopyAssignFrom(*last);
    }
    return dest;
}

// ---------------------------------------------------------------- cGameData-derived object (0x120)

// Objects that own a vtable and are released through it.
struct CVtblObj {
    void **m_vtbl;                     // +0x00
    void Slot1() { ((void (__thiscall *)(CVtblObj *))m_vtbl[1])(this); }
    int Call70(void *out) {
        return ((int (__thiscall *)(CVtblObj *, void *))m_vtbl[0x70 / 4])(this, out);
    }
};

struct CVec3 {
    float x, y, z;
};

// SP::cGonzagoTimer, only the vtable slot is observable here.
struct CGonzagoTimer {
    u8 m_pad[0x20];
};

// Two/three-pointer eastl vector with the game's allocator.
struct CEastlVec12 {
    void *m_begin;                     // +0x00
    void *m_end;                       // +0x04
    void *m_cap;                       // +0x08
};

struct CVector4 {
    void *m_begin;                     // +0x00
    void *m_end;                       // +0x04
    void *m_cap;                       // +0x08
};

typedef CEastlVec12 CVector12;

// The base class (SP::cGameData) contributes the first 0x3c bytes.
struct CGameDataBase {
    void *m_vtbl0;                     // +0x00
    void *m_vtbl4;                     // +0x04
    u8 m_pad08[0x2c];                  // +0x08
    void *m_vtbl34;                    // +0x34
    u8 m_pad38[4];                     // +0x38
};

struct CDerivedGameData : CGameDataBase {
    void *m_p3c;                       // +0x3c
    u8 m_pad40[0x18];                  // +0x40
    void *m_p58;                       // +0x58
    u8 m_pad5c[0x14];                  // +0x5c
    void *m_p70;                       // +0x70
    u8 m_pad74[0x10];                  // +0x74
    CEastlVec12 m_vec84;               // +0x84
    u8 m_pad90[0x20];                  // +0x90
    CGonzagoTimer m_timerB0;           // +0xb0
    CEastlVec12 m_vecD0;               // +0xd0
    u8 m_padDC[8];                     // +0xdc
    CEastlVec12 m_vecE4;               // +0xe4
    u8 m_padF0[8];                     // +0xf0
    u8 *m_arrF8;                       // +0xf8
    u8 m_padFC[4];                     // +0xfc
    u8 *m_arrF8End;                    // +0x100
    u8 m_pad104[4];                    // +0x104
    u8 *m_arr108;                      // +0x108
    u8 m_pad10C[4];                    // +0x10c
    u8 *m_arr108End;                   // +0x110
    u8 m_pad114[8];                    // +0x114
    CVtblObj *m_p11c;                  // +0x11c
};

extern "C" void FUN_00f47380(void *);
extern "C" void FUN_00ae6970();
extern "C" void FUN_00ad92d0();
extern "C" void FUN_00b638b0();
extern "C" void FUN_00bdc770();
extern "C" void FUN_00b184c0();

// @ 0x00bdd680
void __fastcall FUN_00bdd680(CDerivedGameData *self)
{
    if (self->m_p11c != 0)
        self->m_p11c->Slot1();

    int n108 = (int)(((u32)self->m_arr108End - (u32)self->m_arr108) & 0xfffffffeu);
    if (n108 > 2 && self->m_arr108 != 0)
        FUN_00f47380(self->m_arr108);

    int nF8 = (int)(((u32)self->m_arrF8End - (u32)self->m_arrF8) & 0xfffffffeu);
    if (nF8 > 2 && self->m_arrF8 != 0)
        FUN_00f47380(self->m_arrF8);

    ((void (__thiscall *)(void *))FUN_00ae6970)(&self->m_vecE4);
    ((void (__thiscall *)(void *))FUN_00ad92d0)(&self->m_vecD0);
    ((void (__thiscall *)(void *))FUN_00b638b0)(&self->m_timerB0);

    ((void (__thiscall *)(void *, void *, void *))FUN_00bdc770)(
        &self->m_vec84, self->m_vec84.m_begin, self->m_vec84.m_end);

    if (self->m_vec84.m_begin != 0 &&
        ((u32 *)self->m_vec84.m_begin)[-1] != 0)
        FUN_00f47380(self->m_vec84.m_begin);

    if (self->m_p70 != 0 && ((u32 *)self->m_p70)[-1] != 0)
        FUN_00f47380(self->m_p70);

    if (self->m_p58 != 0 && ((u32 *)self->m_p58)[-1] != 0)
        FUN_00f47380(self->m_p58);

    if (self->m_p3c != 0 && ((u32 *)self->m_p3c)[-1] != 0)
        FUN_00f47380(self->m_p3c);

    ((void (__thiscall *)(void *))FUN_00b184c0)(self);
}

// ---------------------------------------------------------------- SP::cCity methods

struct CRBTree {
    u8 m_header[0x0c];
    void *m_root;                      // +0x0c
};

struct CSpatialBlock {
    void *m_vtbl;                      // +0x00
    u8 m_pad04[0xd0];                  // +0x04
};

struct CPaintBlock {
    void *m_vtbl;                      // +0x00
    u8 m_pad04[0x14];                  // +0x04
    void *m_vtbl18;                    // +0x18
};

struct CCity : CDerivedGameData {
    CSpatialBlock m_spatial120;        // +0x120
    CPaintBlock m_paint1f4;            // +0x1f4
    u8 *m_arr210;                      // +0x210
    u8 m_pad214[4];                    // +0x214
    u8 *m_arr218;                      // +0x218
    u8 m_pad21c[0x14];                 // +0x21c
    CGonzagoTimer m_t230;              // +0x230
    CGonzagoTimer m_t250;              // +0x250
    CGonzagoTimer m_t270;              // +0x270
    u8 m_pad290[8];                    // +0x290
    CVtblObj *m_p298;                  // +0x298
    u8 m_pad29c[8];                    // +0x29c
    void *m_p2a4;                      // +0x2a4
    u8 m_pad2a8[0x10];                 // +0x2a8
    void *m_p2b8;                      // +0x2b8
    u8 m_pad2bc[0x4c];                 // +0x2bc
    CVector4 m_vec308;                 // +0x308
    u8 m_pad314[0xc];                  // +0x314
    CVtblObj *m_p320;                  // +0x320
    CVtblObj *m_p324;                  // +0x324
    CVtblObj *m_p328;                  // +0x328
    u8 m_pad32c[0x14];                 // +0x32c
    CVector4 m_vec340;                 // +0x340
    u8 m_pad34c[8];                    // +0x34c
    CVector4 m_vec354;                 // +0x354
    void *m_p360;                      // +0x360
    void *m_p364;                      // +0x364
    u8 m_pad368[0x84];                 // +0x368
    u8 m_action3ec[0x64];              // +0x3ec
    u8 m_action450[0x64];              // +0x450
    u8 m_action4b4[0x64];              // +0x4b4
    u8 m_pad518[0x10];                 // +0x518
    void *m_p528;                      // +0x528
    u8 m_pad52c[0x1c];                 // +0x52c
    CVector4 m_vec548;                 // +0x548
    u8 m_pad554[8];                    // +0x554
    CVector12 m_vec55c;                // +0x55c
    u8 m_pad568[8];                    // +0x568
    CRBTree m_tree570;                 // +0x570
    u8 m_pad580[0x10];                 // +0x580
    CVtblObj *m_p590;                  // +0x590
    u8 m_pad594[0xc];                  // +0x594
    CRBTree m_tree5a0;                 // +0x5a0
    u8 m_pad5b0[0xc];                  // +0x5b0
    CRBTree m_tree5bc;                 // +0x5bc
    u8 m_pad5cc[0xc];                  // +0x5cc
    CRBTree m_tree5d8;                 // +0x5d8
    u8 m_pad5e8[0x10];                 // +0x5e8
    CGonzagoTimer m_t5f8;              // +0x5f8
    CVector4 m_vec618;                 // +0x618
    u8 m_pad624[8];                    // +0x624
    CVector4 m_vec62c;                 // +0x62c
    u8 m_pad638[0x4c];                 // +0x638
    void *m_p684;                      // +0x684
    u8 m_pad688[0x18];                 // +0x688
    CGonzagoTimer m_t6a0;              // +0x6a0
    u8 m_pad6c0[8];                    // +0x6c0
    CGonzagoTimer m_t6c8;              // +0x6c8
    CGonzagoTimer m_t6e8;              // +0x6e8
    CGonzagoTimer m_t708;              // +0x708
    CGonzagoTimer m_t728;              // +0x728
    u8 m_pad748[0x1c];                 // +0x748
    void *m_p764;                      // +0x764
    CVtblObj *m_p768;                  // +0x768
    u8 m_pad76c[4];                    // +0x76c
    CGonzagoTimer m_t770;              // +0x770
    CGonzagoTimer m_t790;              // +0x790
    u8 m_pad7b0[8];                    // +0x7b0
    CRBTree m_tree7b8;                 // +0x7b8
    u8 m_pad7c8[0xc];                  // +0x7c8
    CVtblObj *m_p7d4;                  // +0x7d4
    u8 m_pad7d8[0x20];                 // +0x7d8
    void *m_p7f8;                      // +0x7f8
    u8 m_pad7fc[0x14];                 // +0x7fc
    CVtblObj *m_p810;                  // +0x810

    int FUN_00bddda0(int a1, int a2, int a3, int a4, int a5, int a6);
};

extern "C" void FUN_00bdca30();
extern "C" void FUN_00bf57b0();
extern "C" void *FUN_00b3d350();
extern "C" void FUN_00b7f250();
extern "C" void FUN_00c88530();

// @ 0x00bddda0
int CCity::FUN_00bddda0(int a1, int a2, int a3, int a4, int a5, int a6)
{
    if (m_p590 == 0)
        return 0;

    CVec3 local28;
    CVec3 local1c;
    CVec3 local10;

    ((void (__thiscall *)(CCity *, CVec3 *, int))FUN_00bdca30)(this, &local28, a2);

    int obj = ((int (__thiscall *)(void *, int, int, int, int, int, CVec3 *, int))FUN_00bf57b0)(
        m_p590, a1, a2, a3, a4, a5, &local28, a6);
    if (obj == 0)
        return 0;

    void *sub = (void *)(obj + 0x34);
    void **vtbl = *(void ***)(obj + 0x34);

    int u = m_p324->Call70(&local1c);

    void *model = FUN_00b3d350();
    int orient = ((int (__thiscall *)(void *, CVec3 *, CVec3 *, int))FUN_00b7f250)(
        model, &local10, &local28, u);

    ((void (__thiscall *)(void *, int))vtbl[0x3c / 4])(sub, orient);

    void **vtbl2 = *(void ***)(obj + 0x34);
    ((void (__thiscall *)(void *, float))vtbl2[0x40 / 4])(sub, *(float *)0x1488874);

    ((void (__thiscall *)(void *, float))FUN_00c88530)(sub, 1.0f);

    return obj;
}

extern "C" void FUN_009a9600();
extern "C" void FUN_00bda710();
extern "C" void FUN_00a05270();
extern "C" void FUN_00ac0520();
extern "C" void FUN_00c8a420();
extern "C" void FUN_00afbad0();

static __forceinline void FreeChecked(void *p)
{
    if (p != 0 && ((u32 *)p)[-1] != 0)
        FUN_00f47380(p);
}

static __forceinline void DestroyTree(CRBTree &t)
{
    void *node = t.m_root;
    while (node != 0) {
        ((void (__thiscall *)(CRBTree *, void *))FUN_009a9600)(&t, ((void **)node)[0]);
        void *next = ((void **)node)[1];
        FUN_00f47380(node);
        node = next;
    }
}

static __forceinline void DestroyObjVector4(CVector4 &v)
{
    for (void **p = (void **)v.m_begin; p < (void **)v.m_end; ++p) {
        CVtblObj *o = (CVtblObj *)*p;
        if (o != 0)
            o->Slot1();
    }
}

static __forceinline void DestroySlot64(CVector4 &v)
{
    for (void **p = (void **)v.m_begin; p < (void **)v.m_end; ++p) {
        CVtblObj *o = (CVtblObj *)*p;
        if (o != 0)
            ((void (__thiscall *)(CVtblObj *))o->m_vtbl[0x64 / 4])(o);
    }
}

static __forceinline void DestroyStride12(CVector12 &v)
{
    for (u8 *p = (u8 *)v.m_begin; p < (u8 *)v.m_end; p += 0xc) {
        CVtblObj *a = *(CVtblObj **)(p + 4);
        if (a != 0)
            a->Slot1();
        CVtblObj *b = *(CVtblObj **)p;
        if (b != 0)
            b->Slot1();
    }
}

// @ 0x00bdd780
void __fastcall FUN_00bdd780(CCity *self)
{
    self->m_vtbl0 = (void *)0x14687d8;
    self->m_vtbl4 = (void *)0x14687c4;
    self->m_vtbl34 = (void *)0x1469cc0;
    self->m_spatial120.m_vtbl = (void *)0x1468700;
    self->m_paint1f4.m_vtbl = (void *)0x14686e4;
    self->m_paint1f4.m_vtbl18 = (void *)0x14686d4;

    if (self->m_p810 != 0)
        self->m_p810->Slot1();
    FreeChecked(self->m_p7f8);
    if (self->m_p7d4 != 0)
        self->m_p7d4->Slot1();
    DestroyTree(self->m_tree7b8);

    ((void (__thiscall *)(void *))FUN_00b638b0)(&self->m_t790);
    ((void (__thiscall *)(void *))FUN_00b638b0)(&self->m_t770);
    if (self->m_p768 != 0)
        self->m_p768->Slot1();
    if (self->m_p764 != 0)
        ((void (__thiscall *)(void *))FUN_00a05270)(self->m_p764);

    ((void (__thiscall *)(void *))FUN_00b638b0)(&self->m_t728);
    ((void (__thiscall *)(void *))FUN_00b638b0)(&self->m_t708);
    ((void (__thiscall *)(void *))FUN_00b638b0)(&self->m_t6e8);
    ((void (__thiscall *)(void *))FUN_00b638b0)(&self->m_t6c8);
    ((void (__thiscall *)(void *))FUN_00b638b0)(&self->m_t6a0);

    FreeChecked(self->m_p684);
    DestroyObjVector4(self->m_vec62c);
    FreeChecked(self->m_vec62c.m_begin);

    ((void (__thiscall *)(void *, void *, void *))FUN_00bda710)(
        &self->m_vec618, self->m_vec618.m_begin, self->m_vec618.m_end);
    FreeChecked(self->m_vec618.m_begin);

    ((void (__thiscall *)(void *))FUN_00b638b0)(&self->m_t5f8);

    DestroyTree(self->m_tree5d8);
    DestroyTree(self->m_tree5bc);
    DestroyTree(self->m_tree5a0);
    if (self->m_p590 != 0)
        self->m_p590->Slot1();
    DestroyTree(self->m_tree570);

    DestroyStride12(self->m_vec55c);
    FreeChecked(self->m_vec55c.m_begin);
    DestroySlot64(self->m_vec548);
    FreeChecked(self->m_vec548.m_begin);
    FreeChecked(self->m_p528);

    ((void (__thiscall *)(void *))FUN_00afbad0)(&self->m_action4b4);
    ((void (__thiscall *)(void *))FUN_00afbad0)(&self->m_action450);
    ((void (__thiscall *)(void *))FUN_00afbad0)(&self->m_action3ec);

    DestroyObjVector4(self->m_vec354);
    if (self->m_vec354.m_begin != 0 && self->m_vec354.m_begin != self->m_p364)
        FUN_00f47380(self->m_vec354.m_begin);
    DestroyObjVector4(self->m_vec340);
    FreeChecked(self->m_vec340.m_begin);

    if (self->m_p328 != 0)
        self->m_p328->Slot1();
    if (self->m_p324 != 0)
        self->m_p324->Slot1();
    if (self->m_p320 != 0)
        self->m_p320->Slot1();

    DestroyObjVector4(self->m_vec308);
    FreeChecked(self->m_vec308.m_begin);
    FreeChecked(self->m_p2b8);
    FreeChecked(self->m_p2a4);

    if (self->m_p298 != 0)
        ((void (__thiscall *)(void *))self->m_p298->m_vtbl[0xc0 / 4])(self->m_p298);

    ((void (__thiscall *)(void *))FUN_00b638b0)(&self->m_t270);
    ((void (__thiscall *)(void *))FUN_00b638b0)(&self->m_t250);
    ((void (__thiscall *)(void *))FUN_00b638b0)(&self->m_t230);

    {
        int n = (int)(((u32)self->m_arr218 - (u32)self->m_arr210) & 0xfffffffeu);
        if (n > 2 && self->m_arr210 != 0)
            FUN_00f47380(self->m_arr210);
    }

    self->m_paint1f4.m_vtbl18 = (void *)0x13eb394;
    ((void (__thiscall *)(void *))FUN_00ac0520)(&self->m_paint1f4);
    ((void (__thiscall *)(void *))FUN_00c8a420)(&self->m_spatial120);

    FUN_00bdd680((CDerivedGameData *)self);
}
