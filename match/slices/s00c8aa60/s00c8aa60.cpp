// Slice s00c8aa60 (batch bfs1 #36).  SP::cSpatialObjectView effect helpers and
// Simulator::cStar / cGameData bits.  32-bit MSVC 2008 SP1, /O2 /arch:SSE.
//
// Functions whose bodies need the full inlined EASTL/EASTL-vector machinery are
// stubbed (see partial.txt); the small standalone ones are reproduced exactly.

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern "C" void* __cdecl operator_new(int size, const char* name, int a, int b, int c, int d); // 0x00f473a0

// ---------------------------------------------------------------------------
// One tEffectInfo entry (0x3c bytes).
// ---------------------------------------------------------------------------
struct EffectInfo {
    int   mId;                   // +0x00
    int   mOwner;                // +0x04
    u8    mFlag8;                // +0x08
    u8    mFlag9;                // +0x09
    u8    mFlagA;                // +0x0a
    char  pad_0b[1];
    float mF0c;                  // +0x0c
    u8    mFlag10;               // +0x10
    char  pad_11[3];
    float mF14;                  // +0x14
    float mF18;                  // +0x18
    int   mI1c, mI20, mI24;      // +0x1c
    u8    mFlag28;               // +0x28
    char  pad_29[0x38 - 0x29];
    void* mpEffect;              // +0x38
};

struct cSpatialObjectView {
    char pad_00[0xc0];
    EffectInfo* mpBegin;         // +0x00c0
    EffectInfo* mpEnd;           // +0x00c4

    __declspec(noinline) void* CreateEffectInternal(void* p2, int p3, void* p4, int p5);
    void  CreateEffect4(void* a, void* b, void* c, void* d);   // 0x00c8b040
    void  CreateEffect3(void* a, void* b, void* c);            // 0x00c8b060
    void  CreateEffect1(void* a);                              // 0x00c8b080
    void  sub_b130(void* p2, int p3, void* p4);                // 0x00c8b130
    void  sub_b1a0(void* p);                                   // 0x00c8b1a0
    void  sub_b1b0(void* p2, int p3, void* p4);                // 0x00c8b1b0
    void  sub_b210(void* p);                                   // 0x00c8b210
    bool  sub_b220(int param2, int id, char create, void** out);// 0x00c8b220
    void  sub_ad30(int param2, int id);                        // 0x00c8ad30
    void  DestroyAllEffects(int param);                        // 0x00c8b0a0
    void  sub_b2e0();                                          // 0x00c8b2e0
};

extern "C" void __cdecl c8ae20_opaque();
extern "C" void __cdecl sub_c88d10(void* first, void* last, void* dst);
extern "C" void __cdecl sub_c88c30(void* p);
extern "C" void __cdecl sub_c8a890(void* self);
extern "C" void __cdecl sub_c8a910(void* a, void* b);
extern "C" int  __cdecl sub_b7e0a0(void*);   // (thiscall-shaped helper, ECX=arg)

// ===========================================================================
//  0x00c8b040 / 0x00c8b060 / 0x00c8b080  CreateEffect overloads
// ===========================================================================
// @ 0x00c8b040
void cSpatialObjectView::CreateEffect4(void* a, void* b, void* c, void* d) {
    CreateEffectInternal(a, (int)b, c, (int)d);
}
// @ 0x00c8b060
void cSpatialObjectView::CreateEffect3(void* a, void* b, void* c) {
    CreateEffectInternal(a, (int)b, c, 1);
}
// @ 0x00c8b080
void cSpatialObjectView::CreateEffect1(void* a) {
    CreateEffectInternal(a, 0, a, 1);
}

// ===========================================================================
//  0x00c8b130 / 0x00c8b1a0 / 0x00c8b1b0 / 0x00c8b210
// ===========================================================================
// @ 0x00c8b130
void cSpatialObjectView::sub_b130(void* p2, int p3, void* p4) {
    void* e = CreateEffectInternal(p2, p3, p4, 1);
    if (!*(volatile u8*)0x1695244 && !e) return;
    for (EffectInfo* it = mpBegin; it != mpEnd; it = (EffectInfo*)((char*)it + 0x3c)) {
        if (it->mId == (int)p4) {
            if (!it->mFlag8) { it->mFlag8 = 1; it->mFlagA = 1; }
            return;
        }
    }
}
// @ 0x00c8b1a0
void cSpatialObjectView::sub_b1a0(void* p) { sub_b130(p, 0, p); }
// @ 0x00c8b1b0
void cSpatialObjectView::sub_b1b0(void* p2, int p3, void* p4) {
    void* e = CreateEffectInternal(p2, p3, p4, 0);
    if (!e) return;
    for (EffectInfo* it = mpBegin; it != mpEnd; it = (EffectInfo*)((char*)it + 0x3c)) {
        if (it->mId == (int)p4) {
            if (!it->mFlag8) { it->mFlag8 = 1; it->mFlagA = 1; }
            return;
        }
    }
}
// @ 0x00c8b210
void cSpatialObjectView::sub_b210(void* p) { sub_b1b0(p, 0, p); }

// ===========================================================================
//  0x00c8b220  find / create / erase one effect
// ===========================================================================
// @ 0x00c8b220
bool cSpatialObjectView::sub_b220(int param2, int id, char create, void** out) {
    EffectInfo* it = mpBegin;
    EffectInfo* end = mpEnd;
    while (it != end && it->mId != id) it = (EffectInfo*)((char*)it + 0x3c);

    bool created = false;
    void* found = 0;
    if (create) {
        if (it == end) {
            found = CreateEffectInternal((void*)param2, 0, (void*)id, 1);
            created = found != 0;
        } else {
            found = it->mpEffect;
        }
    } else if (it != end) {
        if (it->mpEffect) {
            char c = ((char(__thiscall*)(void*))(*(void***)it->mpEffect)[0x10 / 4])(it->mpEffect);
            if (c || it->mFlag8) {
                ((void(__thiscall*)(void*, int))(*(void***)it->mpEffect)[0xc / 4])(it->mpEffect, 0);
            }
        }
        if ((EffectInfo*)((char*)it + 0x3c) < mpEnd) {
            sub_c88d10((char*)it + 0x3c, mpEnd, it);
        }
        mpEnd = (EffectInfo*)((char*)mpEnd - 0x3c);
        if (mpEnd->mpEffect) {
            ((void(__thiscall*)(void*))(*(void***)mpEnd->mpEffect)[4 / 4])(mpEnd->mpEffect);
        }
    }
    if (out) *out = found;
    return created;
}

// ===========================================================================
//  0x00c8ad30  destroy one effect by id
// ===========================================================================
// @ 0x00c8ad30
void cSpatialObjectView::sub_ad30(int param2, int id) {
    EffectInfo* it = mpBegin;
    EffectInfo* end = mpEnd;
    if (it == end) return;
    while (it->mId != id) {
        it = (EffectInfo*)((char*)it + 0x3c);
        if (it == end) return;
    }
    if (it->mpEffect) {
        char c = ((char(__thiscall*)(void*))(*(void***)it->mpEffect)[0x10 / 4])(it->mpEffect);
        if (c || it->mFlag8) {
            ((void(__thiscall*)(void*, int))(*(void***)it->mpEffect)[0xc / 4])(it->mpEffect, param2);
        }
    }
    for (EffectInfo* p = (EffectInfo*)((char*)it + 0x3c); p < mpEnd; p = (EffectInfo*)((char*)p + 0x3c)) {
        sub_c88c30(p);
    }
    mpEnd = (EffectInfo*)((char*)mpEnd - 0x3c);
    if (mpEnd->mpEffect) {
        ((void(__thiscall*)(void*))(*(void***)mpEnd->mpEffect)[4 / 4])(mpEnd->mpEffect);
    }
}

// ===========================================================================
//  0x00c8b0a0  DestroyAllEffects
// ===========================================================================
// @ 0x00c8b0a0
void cSpatialObjectView::DestroyAllEffects(int param) {
    int force = param;
    for (EffectInfo* it = mpBegin; it != mpEnd; it = (EffectInfo*)((char*)it + 0x3c)) {
        if (!it->mpEffect) continue;
        char c = ((char(__thiscall*)(void*))(*(void***)it->mpEffect)[0x10 / 4])(it->mpEffect);
        if (!c && !it->mFlag8) continue;
        int kind = ((int(__thiscall*)(void*))(*(void***)it->mpEffect)[0x60 / 4])(it->mpEffect);
        if (kind == 0x2abf6155 || kind == 0x2241f9c6) force = 1;
        ((void(__thiscall*)(void*, int))(*(void***)it->mpEffect)[0xc / 4])(it->mpEffect, force);
    }
    sub_c8a890(this);
}

// ===========================================================================
//  0x00c8b2e0  release cached effect handles + destroy all
// ===========================================================================
// @ 0x00c8b2e0
void cSpatialObjectView::sub_b2e0() {
    char* self = (char*)this;
    void* a = *(void**)(self + 0x9c);
    if (a) ((void(__thiscall*)(void*, int))(*(void***)a)[0x16c / 4])(a, 0);
    void* b = *(void**)(self + 0x9c);
    if (b) {
        *(void**)(self + 0x9c) = 0;
        if (*(int*)((char*)b + 0x40) > 1) --*(int*)((char*)b + 0x40);
        else ((void(__thiscall*)(void*, u32))(*(void***)b)[0x170 / 4])(b, (*(u32*)((char*)b + 4)) >> 31);
    }
    void* c = *(void**)(self + 0xa0);
    if (c) {
        *(void**)(self + 0xa0) = 0;
        ((void(__thiscall*)(void*))(*(void***)c)[4 / 4])(c);
    }
    DestroyAllEffects(1);
}

// ===========================================================================
//  0x00c8b450 / 0x00c8b520  small range predicates
// ===========================================================================
// @ 0x00c8b450
bool __cdecl c8b450(int k) {
    if (k == 0) return false;
    if (k <= 6) return false;
    if (k > 0xc) return false;
    return true;
}
// @ 0x00c8b520
bool __cdecl c8b520(int k) {
    if (k == 0) return false;
    if (k <= 0) return true;
    if (k <= 3) return false;
    return true;
}

// ===========================================================================
//  0x00c8b470  direction-pair table
// ===========================================================================
// @ 0x00c8b470
void __cdecl c8b470(int k, int* b, int* c) {
    switch (k) {
    case 7:  *c = 5; *b = 5; return;
    case 8:  *b = 5; *c = 4; return;
    case 9:  *b = 5; *c = 6; return;
    case 10: *c = 4; *b = 4; return;
    case 11: *b = 4; *c = 6; return;
    case 12: *c = 6; *b = 6; return;
    }
}

// ===========================================================================
//  Objects whose layout starts with a manager pointer at +0x48.
// ===========================================================================
struct Sub48 {
    void sub_bb9af0(int v);   // 0x00bb9af0
    void sub_bb9b90(int v);   // 0x00bb9b90
    void sub_bb9ad0(int v);   // 0x00bb9ad0
    void sub_a16a90(void* p); // 0x00a16a90
    int  sub_801920();        // 0x00801920
};
struct Font {
    void SetUserData(void* p); // 0x00fd9450
};
struct Obj48 {
    char pad_00[0x34];
    int  mField34;           // +0x34
    int  mField38;           // +0x38
    char pad_3c[4];
    Font* mpFont;            // +0x40
    char pad_44[4];
    Sub48* mp48;             // +0x48
    int   mField4c;          // +0x4c

    void sub_b560();               // 0x00c8b560
    void sub_b570(int param);      // 0x00c8b570
    void sub_b5c0(void* p);        // 0x00c8b5c0
    void sub_b7d0();               // 0x00c8b7d0
    bool sub_b7e0();               // 0x00c8b7e0
    bool sub_b800();               // 0x00c8b800
    void sub_b6d0(void* param);    // 0x00c8b6d0
};

// @ 0x00c8b560
void Obj48::sub_b560() { mp48->sub_bb9af0(2); }
// @ 0x00c8b570
void Obj48::sub_b570(int param) { mp48->sub_bb9b90(param + 0x504); }
// @ 0x00c8b5c0
void Obj48::sub_b5c0(void* p) {
    mp48->sub_bb9ad0(5);
    mp48->sub_a16a90(p);
}
// @ 0x00c8b7d0
void Obj48::sub_b7d0() {
    if (mpFont) mpFont->SetUserData(this);
}
// @ 0x00c8b7e0
bool Obj48::sub_b7e0() {
    int k = mp48->sub_801920();
    if (k != 0) { unsigned int v = (unsigned int)(k - 7); return v <= 5u; }
    return false;
}
// @ 0x00c8b800
bool Obj48::sub_b800() {
    int k = mp48->sub_801920();
    if (k != 0) { unsigned int v = (unsigned int)(k - 1); return v > 2u; }
    return false;
}
// @ 0x00c8b6d0
extern "C" void* __cdecl sub_801920b(void* a, void* b);
void Obj48::sub_b6d0(void* param) {
    mp48 = (Sub48*)param;
    mField4c = *(int*)((char*)param + 0x70);
    int* a = &mField34;
    int* b = &mField38;
    int v = (int)sub_801920b(a, b);
    c8b470(v, a, b);
}

// ===========================================================================
//  0x00c8b5e0  pick max of a list
// ===========================================================================
struct ElemObj { int sub_b8dab0(); };
struct ListArg { int* sub_bba790(); void sub_bb9ad0(int); };
// @ 0x00c8b5e0
void __cdecl c8b5e0(ListArg* arg) {
    int* p = arg->sub_bba790();
    int n = (p[1] - p[0]) >> 2;
    int best = 0;
    for (int i = 0; i < n; ++i) {
        ElemObj* e = (ElemObj*)((int*)p[0])[i];
        if (e->sub_b8dab0() > best) best = e->sub_b8dab0();
    }
    arg->sub_bb9ad0(best);
}

// ===========================================================================
//  0x00c8b640  Simulator::cStar::cStar
// ===========================================================================
struct cGameDataStub { void ctor(); };
struct cStar {
    void** vftable;              // +0x00
    void** vftable2;             // +0x04
    char pad_08[0x34 - 0x08];
    int  mField34;               // +0x34
    int  mField38;               // +0x38
    u8   mFlag3c;                // +0x3c
    char pad_3d[3];
    void* mpSolarSystem;         // +0x40
    u8   mFlag44;                // +0x44
    char pad_45[3];
    void* mpStarRecord;          // +0x48
    int  mKey;                   // +0x4c
    cStar();
};
// @ 0x00c8b640
cStar::cStar() {
    ((cGameDataStub*)this)->ctor();
    mField34 = 0;
    mField38 = 0;
    mFlag3c = 0;
    vftable = (void**)0x1473990;
    vftable2 = (void**)0x147397c;
    mpSolarSystem = 0;
    mpStarRecord = 0;
    mFlag44 = 1;
    mKey = -1;
}

// ===========================================================================
//  0x00c8b700  lazily create solar system
// ===========================================================================
struct cSolarSystem { char pad[0x54]; };
struct Owner40 {
    char pad_00[0x40];
    cSolarSystem* mpSolar;       // +0x40
    void sub_b700();
};
extern "C" void* __cdecl cSolarSystem_ctor(void* p);
extern "C" void  __cdecl sub_c86760(void* p);
// @ 0x00c8b700
void Owner40::sub_b700() {
    if (mpSolar) return;
    void* p = operator_new(0x54, "Simulator/cSolarSystem", 0, 0, 0, 0);
    cSolarSystem* n = p ? (cSolarSystem*)cSolarSystem_ctor(p) : 0;
    cSolarSystem* old = mpSolar;
    if (n != old) {
        if (n) ((void(__thiscall*)(void*))(*(void***)n)[4 / 4])(n);
        mpSolar = n;
        if (old) ((void(__thiscall*)(void*))(*(void***)old)[8 / 4])(old);
    }
    sub_c86760(this);
}

// ===========================================================================
//  0x00c8b790  Simulator::cGameData::RemoveOwner
// ===========================================================================
struct OwnerObj { void sub_c86e50(); };
struct cGameData {
    char pad_00[0x2c];
    void* mpOwner2c;             // +0x2c
    char pad_30[0x10];
    OwnerObj* mpOwner40;         // +0x40
    void RemoveOwner();
};
// @ 0x00c8b790
void cGameData::RemoveOwner() {
    if (mpOwner40) {
        mpOwner40->sub_c86e50();
        OwnerObj* b = mpOwner40;
        if (b) {
            mpOwner40 = 0;
            ((void(__thiscall*)(void*))(*(void***)b)[8 / 4])(b);
        }
    }
    void* c = mpOwner2c;
    if (c) {
        mpOwner2c = 0;
        ((void(__thiscall*)(void*))(*(void***)c)[4 / 4])(c);
    }
}

// ===========================================================================
//  0x00c8b820 / 0x00c8b920 / 0x00c8ba00  tree walks (approximate, see partial.txt)
// ===========================================================================
// @ 0x00c8b820
void __cdecl c8b820(void* view, int id) {
    int* p = ((ListArg*)view)->sub_bba790();
    int n = (p[1] - p[0]) >> 2;
    for (int i = 0; i < n; ++i) {
        char* e = (char*)((int*)p[0])[i];
        int t = *(int*)(e + 0x28);
        if (t == 1 || t == 0) continue;
        (void)0;   // full traversal stubbed
        (void)id;
    }
}
// @ 0x00c8b920
bool __cdecl c8b920(void* view, int id) { (void)view; (void)id; return false; }
// @ 0x00c8ba00
bool __cdecl c8ba00(void* view) { (void)view; return false; }

// ===========================================================================
//  Large inlined bodies (partial): CreateEffectInternal / push_back / Read
// ===========================================================================
// @ 0x00c8ae20
void* cSpatialObjectView::CreateEffectInternal(void* p2, int p3, void* p4, int p5) {
    (void)p2; (void)p3; (void)p4; (void)p5;
    c8ae20_opaque();
    return 0;
}
// @ 0x00c8add0
void __fastcall EffectVec_push_back(cSpatialObjectView* v) { (void)v; }
// @ 0x00c8aa60
void __cdecl c8aa60() {}
// @ 0x00c8b3e0
bool __cdecl c8b3e0_Read(void* self, int param) { (void)self; (void)param; return false; }
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
