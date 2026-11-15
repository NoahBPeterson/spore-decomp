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
    u8    mPad0b;                // +0x0b
    float mF0c;                  // +0x0c
    u8    mFlag10;               // +0x10
    u8    mPad11;                // +0x11
    u8    mPad12;                // +0x12
    u8    mPad13;                // +0x13
    float mF14;                  // +0x14
    float mF18;                  // +0x18
    int   mI1c, mI20, mI24;      // +0x1c
    u8    mFlag28;               // +0x28
    u8    mPad29;                // +0x29
    u8    mPad2a;                // +0x2a
    u8    mPad2b;                // +0x2b
    int   mPad2c;                // +0x2c
    int   mPad30;                // +0x30
    int   mPad34;                // +0x34
    void* mpEffect;              // +0x38
};
typedef char EffectInfo_layout_check[(sizeof(EffectInfo) == 0x3c) ? 1 : -1];

struct XformMsg;
struct Effect;
struct Matrix33 {
    float m0, m1, m2, m3, m4, m5, m6, m7, m8;
    void Assign(const float* src);   // 0x0041cb40
    void CopyFrom(const Matrix33& o) {
        m0 = o.m0; m1 = o.m1; m2 = o.m2;
        m3 = o.m3; m4 = o.m4; m5 = o.m5;
        m6 = o.m6; m7 = o.m7; m8 = o.m8;
    }
};

// ---------------------------------------------------------------------------
// eastl::vector<tEffectInfo>: the view stores it inline at +0xc0.
// ---------------------------------------------------------------------------
struct EffectVec {
    EffectInfo* pBegin;      // +0x00
    EffectInfo* pEnd;        // +0x04
    EffectInfo* pCap;        // +0x08
    void DoInsertValue(EffectInfo* pPos, const EffectInfo& value);  // 0x00c8a910
    void push_back_default();                                       // 0x00c8add0
};

// A spawned effect handle (vtable offsets used by the view).
struct Effect {
    virtual void e00();
    virtual void e04();             // +0x04  release
    virtual void e08(int);          // +0x08
    virtual void e0c(int);          // +0x0c
    virtual char e10();             // +0x10  is active
    virtual void e14();
    virtual void e18(XformMsg*);    // +0x18
    virtual void e1c();
    virtual void e20();
    virtual void e24();
    virtual void e28();
    virtual void e2c();
    virtual void e30();
    virtual void e34();
    virtual void e38();
    virtual void e3c();
    virtual void e40();
    virtual void e44(int, void*, int);  // +0x44
};

// Message passed to Effect::e18.
struct XformMsg {
    u16      mFlags;      // +0x00
    u16      mCount;      // +0x02
    float    mPosX;       // +0x04
    float    mPosY;       // +0x08
    float    mPosZ;       // +0x0c
    float    mScale;      // +0x10
    Matrix33 mMatrix;     // +0x14
    void Init();          // 0x00434040
};

// Effects-manager virtual interface (only the slots the view uses).
struct EffectsMgr {
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
    virtual void m10(); virtual void m14(); virtual void m18(); virtual void m1c();
    virtual void m20(); virtual void m24(); virtual void m28();
    virtual char Resolve(void* id, int a, Effect** out);   // +0x2c
};

// cSpatialObjectView virtual interface (only +0x2c / +0x30 are used here).
struct ViewVirtuals {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual float* Transform();      // +0x2c  position
    virtual float* Rotation();       // +0x30  quaternion
};

struct cSpatialObjectView {
    void**  mpVtbl;              // +0x000
    char    pad_04[0xbc];        // +0x004
    EffectVec mEffects;          // +0x0c0

    __declspec(noinline) Effect* CreateEffectInternal(void* p2, int p3, void* p4, int p5);
    void  UpdateEffects();                                     // 0x00c8aa60
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

extern "C" void __cdecl sub_c88d10(void* first, void* last, void* dst);
extern "C" void __cdecl sub_c88c30(void* p);
extern "C" void __cdecl sub_c8a890(void* self);
extern "C" float __cdecl EffectTime(void* self);            // 0x00c88d90
extern "C" void* __cdecl EffectsManager();                  // 0x0067ddd0
extern "C" void* __cdecl StarManager();                     // 0x00b3d2a0
extern "C" float* __cdecl Matrix3FromQuaternion(float* dst, const float* q); // 0x0059c190

// ===========================================================================
//  0x00c8b040 / 0x00c8b060 / 0x00c8b080  CreateEffect overloads
// ===========================================================================
// @ 0x00c8b040
#pragma optimize("", off)
void cSpatialObjectView::CreateEffect4(void* a, void* b, void* c, void* d) {
    CreateEffectInternal(a, (int)b, c, (int)d);
}
#pragma optimize("", on)
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
    for (EffectInfo* it = mEffects.pBegin; it != mEffects.pEnd; it = (EffectInfo*)((char*)it + 0x3c)) {
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
    for (EffectInfo* it = mEffects.pBegin; it != mEffects.pEnd; it = (EffectInfo*)((char*)it + 0x3c)) {
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
    EffectInfo* it = mEffects.pBegin;
    EffectInfo* end = mEffects.pEnd;
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
        if ((EffectInfo*)((char*)it + 0x3c) < mEffects.pEnd) {
            sub_c88d10((char*)it + 0x3c, mEffects.pEnd, it);
        }
        mEffects.pEnd = (EffectInfo*)((char*)mEffects.pEnd - 0x3c);
        if (mEffects.pEnd->mpEffect) {
            ((void(__thiscall*)(void*))(*(void***)mEffects.pEnd->mpEffect)[4 / 4])(mEffects.pEnd->mpEffect);
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
    EffectInfo* it = mEffects.pBegin;
    EffectInfo* end = mEffects.pEnd;
    if (it == end) return;
    while (it->mId != param2) {
        it = (EffectInfo*)((char*)it + 0x3c);
        if (it == end) return;
    }
    if (it->mpEffect) {
        char c = ((char(__thiscall*)(void*))(*(void***)it->mpEffect)[0x10 / 4])(it->mpEffect);
        if (c || it->mFlag8) {
            ((void(__thiscall*)(void*, int))(*(void***)it->mpEffect)[0xc / 4])(it->mpEffect, id);
        }
    }
    for (EffectInfo* p = (EffectInfo*)((char*)it + 0x3c); p < mEffects.pEnd; p = (EffectInfo*)((char*)p + 0x3c)) {
        ((void(__thiscall*)(void*, void*))sub_c88c30)(it, p);
    }
    mEffects.pEnd = (EffectInfo*)((char*)mEffects.pEnd - 0x3c);
    if (mEffects.pEnd->mpEffect) {
        ((void(__thiscall*)(void*))(*(void***)mEffects.pEnd->mpEffect)[4 / 4])(mEffects.pEnd->mpEffect);
    }
}

// ===========================================================================
//  0x00c8b0a0  DestroyAllEffects
// ===========================================================================
// @ 0x00c8b0a0
void cSpatialObjectView::DestroyAllEffects(int param) {
    int force = param;
    for (EffectInfo* it = mEffects.pBegin; it != mEffects.pEnd; it = (EffectInfo*)((char*)it + 0x3c)) {
        if (!it->mpEffect) continue;
        char c = ((char(__thiscall*)(void*))(*(void***)it->mpEffect)[0x10 / 4])(it->mpEffect);
        if (!c && !it->mFlag8) continue;
        unsigned long long id = ((unsigned long long(__thiscall*)(void*))(*(void***)it->mpEffect)[0x60 / 4])(it->mpEffect);
        if (id == 0x2abf6155ULL) {
            force = 1;
        } else {
            id = ((unsigned long long(__thiscall*)(void*))(*(void***)it->mpEffect)[0x60 / 4])(it->mpEffect);
            if (id == 0x2241f9c6ULL) force = 1;
        }
        ((void(__thiscall*)(void*, int))(*(void***)it->mpEffect)[0xc / 4])(it->mpEffect, force);
    }
    ((void(__thiscall*)(void*, EffectInfo*, EffectInfo*))sub_c8a890)(&mEffects.pBegin, mEffects.pBegin, mEffects.pEnd);
}

// ===========================================================================
//  0x00c8b2e0  release cached effect handles + destroy all
// ===========================================================================
// @ 0x00c8b2e0
void cSpatialObjectView::sub_b2e0() {
    char* self = (char*)this;
    // [self+0x9c] holds a pointer to a handle whose first field is the real object;
    // the original loads ecx = *(void**)(self+0x9c) then edx = *ecx (the vtable) and
    // passes the handle, not the object, as the first stack argument.
    void* h1 = *(void**)(self + 0x9c);
    if (h1) {
        void* o1 = *(void**)h1;
        ((void(__thiscall*)(void*, void*, int))(*(void***)o1)[0x16c / 4])(o1, h1, 0);
    }
    void* h2 = *(void**)(self + 0x9c);
    if (h2) {
        *(void**)(self + 0x9c) = 0;
        if (*(int*)((char*)h2 + 0x40) > 1) --*(int*)((char*)h2 + 0x40);
        else {
            void* o2 = *(void**)h2;
            ((void(__thiscall*)(void*, void*, u32))(*(void***)o2)[0x170 / 4])(
                o2, h2, (*(u32*)((char*)h2 + 4)) >> 31);
        }
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
extern "C" int __cdecl FUN_00801920(void* a, void* b);
// @ 0x00c8b6d0
#pragma optimize("", off)
void Obj48::sub_b6d0(void* param) {
    mp48 = (Sub48*)param;
    mField4c = *(int*)((char*)param + 0x70);
    int* a = &mField34;
    int* b = &mField38;
    int v = ((int (__fastcall*)(void*))FUN_00801920)(param);
    c8b470(v, a, b);
}
#pragma optimize("", on)

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
    bool Read(int param);        // 0x00c8b3e0
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
//  0x00c8b820 / 0x00c8b920 / 0x00c8ba00  effect tree walks
// ===========================================================================
struct Vec2 { void** pBegin; void** pEnd; };

extern float g_13ec4d0;   // 0x013ec4d0 = 100.0f

struct ItemObj {
    u8    pad_00[0x38];
    int   mId;        // +0x38
    float mValue;     // +0x3c
    int   GetId();            // 0x00a1ad10
    void  SetId(int id);      // 0x00ff03b0
    void  SetValue(float v);  // 0x00ff03c0
    float GetValue();         // 0x00b7e0a0
};

struct Obj2 {
    u8        pad_00[0x3c];
    ItemObj** pItems;         // +0x3c
    ItemObj** pItemsEnd;      // +0x40
};

struct Node2 {
    u8      pad_00[0x28];
    int     mKind;            // +0x28
    u8      pad_2c[0x130];
    Obj2**  pObjs;            // +0x15c
    Obj2**  pObjsEnd;         // +0x160
    u8      pad_164[0x30];
    int     mType;            // +0x194
    int     GetType();        // 0x00b8dab0
    char    IsFlagged();      // 0x00b8d970
    Obj2*   GetObj(int i);    // 0x00b8dec0
};

struct View2 {
    Vec2* GetList();          // 0x00bba790
};

// @ 0x00c8b820
void __cdecl c8b820(void* view, int id) {
    Vec2* list = ((View2*)view)->GetList();
    int n = (int)(list->pEnd - list->pBegin);
    for (int i = 0; i < n; ++i) {
        Node2* node = (Node2*)list->pBegin[i];
        int kind = node->mKind;
        if (kind == 1 || kind == 0) continue;
        if (node->IsFlagged()) continue;
        int j = 0;
        int n2 = (int)(node->pObjsEnd - node->pObjs);
        for (; j < n2; ++j) {
            Obj2* obj = node->GetObj(j);
            int n3 = (int)(obj->pItemsEnd - obj->pItems);
            for (int k = 0; k < n3; ++k) {
                ItemObj* item = obj->pItems[k];
                if (item->GetId() == id) {
                    item->SetId(-1);
                    item->SetValue(0.0f);
                }
            }
        }
    }
}
// @ 0x00c8b920
bool __cdecl c8b920(void* view, int id) {
    Node2* node = (Node2*)view;
    if (node->GetType() == 5) {
        int kind = node->mKind;
        if (kind != 1 && kind != 0 && !node->IsFlagged()) {
            int j = 0;
            int n2 = (int)(node->pObjsEnd - node->pObjs);
            for (; j < n2; ++j) {
                Obj2* obj = node->GetObj(j);
                int n3 = (int)(obj->pItemsEnd - obj->pItems);
                for (int k = 0; k < n3; ++k) {
                    ItemObj* item = obj->pItems[k];
                    if (item->GetId() != id) return false;
                    if (item->GetValue() < g_13ec4d0) return false;
                }
            }
            if (node->pObjs != node->pObjsEnd) return true;
        }
    }
    return false;
}
// @ 0x00c8ba00
bool __cdecl c8ba00(void* view) {
    Node2* node = (Node2*)view;
    if (node->GetType() == 5) {
        int kind = node->mKind;
        if (kind != 1 && kind != 0 && !node->IsFlagged()) {
            int first = -1;
            int j = 0;
            int n2 = (int)(node->pObjsEnd - node->pObjs);
            for (; j < n2; ++j) {
                Obj2* obj = node->GetObj(j);
                int n3 = (int)(obj->pItemsEnd - obj->pItems);
                for (int k = 0; k < n3; ++k) {
                    ItemObj* item = obj->pItems[k];
                    if (item->GetValue() != g_13ec4d0) return false;
                    if (first == -1) first = item->GetId();
                    if (first != item->GetId()) return false;
                }
            }
            if (node->pObjs != node->pObjsEnd) return true;
        }
    }
    return false;
}

// ===========================================================================
//  Large inlined bodies: effect vector push_back / CreateEffectInternal /
//  per-frame update / serializer read.
// ===========================================================================
// @ 0x00c8add0
void EffectVec::push_back_default() {
    EffectInfo tmp;
    tmp.mpEffect = 0;
    if (pEnd < pCap) {
        EffectInfo* slot = pEnd;
        pEnd = slot + 1;
        if (slot)
            slot->mpEffect = 0;
    } else {
        DoInsertValue(pEnd, tmp);
        if (tmp.mpEffect)
            ((Effect*)tmp.mpEffect)->e04();
    }
}

// @ 0x00c8ae20
Effect* cSpatialObjectView::CreateEffectInternal(void* p2, int p3, void* p4, int p5) {
    Effect* local = 0;
    if (*(u8*)0x1695244 == 0) {
        EffectsMgr* mgr = (EffectsMgr*)EffectsManager();
        if (local) {
            Effect* old = local;
            local = 0;
            old->e04();
        }
        if (!mgr->Resolve(p2, p3, &local))
            goto done;
    }

    {
        EffectInfo* it = mEffects.pBegin;
        EffectInfo* end = mEffects.pEnd;
        while (it != end && it->mId != (int)p4)
            it = (EffectInfo*)((char*)it + 0x3c);

        if (it == end) {
            mEffects.push_back_default();
            it = (EffectInfo*)((char*)mEffects.pEnd - 0x3c);
        } else {
            Effect* cur = (Effect*)it->mpEffect;
            if (cur) {
                cur->e0c(1);
                it->mpEffect = 0;
                cur->e04();
            }
        }

        it->mId    = (int)p4;
        it->mOwner = (int)p2;

        Effect* oldEffect = (Effect*)it->mpEffect;
        if (local != oldEffect) {
            if (local)
                local->e00();
            it->mpEffect = local;
            if (oldEffect)
                oldEffect->e04();
        }

        it->mF0c    = *(float*)0x13f1160;
        it->mFlag8  = 0;
        it->mFlag9  = (u8)p5;
        it->mFlagA  = 0;
        it->mFlag10 = 0;
        it->mF14    = *(float*)0x1485720;
        it->mF18    = 0.0f;
        it->mI1c    = *(int*)0x1695248;
        it->mI20    = *(int*)0x169524c;
        it->mI24    = *(int*)0x1695250;
        it->mFlag28 = 0;

        if (local) {
            XformMsg msg;
            msg.mFlags = 0;
            msg.mCount = 0;
            msg.mPosX  = *(float*)0x16952f4;
            msg.mPosY  = *(float*)0x16952f8;
            msg.mPosZ  = *(float*)0x16952fc;
            msg.mScale = *(float*)0x1485720;
            msg.mMatrix.Assign((const float*)0x16952d0);

            float* pos = ((ViewVirtuals*)this)->Transform();
            msg.mPosX = pos[0];
            msg.mPosY = pos[1];
            msg.mPosZ = pos[2];
            msg.mFlags |= 4;
            msg.mCount++;

            float* quat = ((ViewVirtuals*)this)->Rotation();
            Matrix33 mat;
            Matrix3FromQuaternion(&mat.m0, quat);
                msg.mMatrix.CopyFrom(mat);
            msg.mFlags |= 2;
            msg.mCount++;

            local->e18(&msg);
            if (it->mFlag28)
                local->e44(5, &it->mI1c, 3);
            local->e08(0);
        }
    }

done:
    Effect* result = local;
    if (local)
        local->e04();
    return result;
}

// @ 0x00c8aa60
void cSpatialObjectView::UpdateEffects() {
    if (mEffects.pBegin == mEffects.pEnd)
        return;

    float t = EffectTime(this);

    if (*(u8*)0x1695244 == 0) {
        for (EffectInfo* it = mEffects.pBegin; it != mEffects.pEnd; ) {
            Effect* e = (Effect*)it->mpEffect;
            if (!e) {
                it = (EffectInfo*)((char*)it + 0x3c);
                continue;
            }
            char active = e->e10();
            bool flag = it->mFlag9 != 0 || it->mFlagA != 0;
            if (active || flag) {
                if (it->mF0c <= t) {
                    if (active)
                        ((Effect*)it->mpEffect)->e0c(0);
                } else if (it->mFlag8 && !active && flag) {
                    ((Effect*)it->mpEffect)->e08(0);
                    it->mFlagA = 0;
                }
                it = (EffectInfo*)((char*)it + 0x3c);
            } else {
                if ((EffectInfo*)((char*)it + 0x3c) < mEffects.pEnd)
                    sub_c88d10((char*)it + 0x3c, mEffects.pEnd, it);
                mEffects.pEnd = (EffectInfo*)((char*)mEffects.pEnd - 0x3c);
                if (mEffects.pEnd->mpEffect)
                    ((Effect*)mEffects.pEnd->mpEffect)->e04();
            }
        }
        return;
    }

    for (EffectInfo* it = mEffects.pBegin; it != mEffects.pEnd; ) {
        char local = 0;
        if (!it->mFlag8) {
            it = (EffectInfo*)((char*)it + 0x3c);
            continue;
        }

        Effect* e = (Effect*)it->mpEffect;
        if (it->mF0c > t) {
            if (e) {
                local = e->e10();
            } else {
                EffectsMgr* mgr = (EffectsMgr*)EffectsManager();
                if (mgr->Resolve((void*)it->mOwner, 0, (Effect**)&it->mpEffect)) {
                    XformMsg msg;
                    msg.Init();
                    float* pos = ((ViewVirtuals*)this)->Transform();
                    msg.mPosX = pos[0];
                    msg.mPosY = pos[1];
                    msg.mPosZ = pos[2];
                    msg.mFlags |= 4;
                    msg.mCount++;
                    float* quat = ((ViewVirtuals*)this)->Rotation();
                    Matrix33 mat;
                    Matrix3FromQuaternion(&mat.m0, quat);
                    msg.mMatrix.CopyFrom(mat);
                    msg.mFlags |= 2;
                    msg.mCount++;
                    ((Effect*)it->mpEffect)->e18(&msg);
                    if (it->mFlag28)
                        ((Effect*)it->mpEffect)->e44(5, &it->mI1c, 3);
                    ((Effect*)it->mpEffect)->e08(0);
                    local = 1;
                }
            }
        } else {
            if (e) {
                local = e->e10();
                ((Effect*)it->mpEffect)->e0c(0);
                if (it->mpEffect) {
                    it->mpEffect = 0;
                    ((Effect*)e)->e04();
                }
            } else if (!it->mFlag9) {
                local = 0;
            }
        }

        if (it->mFlag8 && !local) {
            Effect* dead = (Effect*)it->mpEffect;
            if (dead) {
                it->mpEffect = 0;
                dead->e04();
            }
            if ((EffectInfo*)((char*)it + 0x3c) < mEffects.pEnd)
                sub_c88d10((char*)it + 0x3c, mEffects.pEnd, it);
            mEffects.pEnd = (EffectInfo*)((char*)mEffects.pEnd - 0x3c);
            if (mEffects.pEnd->mpEffect)
                ((Effect*)mEffects.pEnd->mpEffect)->e04();
        } else {
            it = (EffectInfo*)((char*)it + 0x3c);
        }
    }
}

// --- 0x00c8b3e0 ------------------------------------------------------------
struct VarListSerializer {
    u8 pad_a14[0xa14];
    void Init(void* obj, const char* name, u32 flags);   // 0x00692f90
    bool Read(int param);                                // 0x00693e10
};
struct StarMgr {
    int  FUN_00ba6d80(u32 id);        // 0x00ba6d80
    void FUN_00baf590(u32 id, void* o);// 0x00baf590
};

// @ 0x00c8b3e0
bool cStar::Read(int param) {
    VarListSerializer ser;
    ser.Init(this, (const char*)0x157a828, 0x1a80d26);
    bool ok = ser.Read(param);

    int v = ((StarMgr*)StarManager())->FUN_00ba6d80((u32)mKey);
    mpStarRecord = (void*)v;
    ((StarMgr*)StarManager())->FUN_00baf590((u32)mKey, this);
    return ok;
}

// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
