// Slice s00d1e930 -- SP::UseAbility and the ability-slot bookkeeping helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------------------
// callees (call targets are relocation-masked by the checker, so only the call
// encoding / ABI matters)
// ---------------------------------------------------------------------------
void* SP_NounManager();                                      // 0x00b3d300 cdecl
void* SP_PropertyManager();                                  // 0x0067de30 cdecl
void* SP_GetCurrentGameMode();                               // 0x00b5b800 cdecl
void* FUN_00f473a0(size_t, const char*, int, int, int, int); // 0x00f473a0 cdecl operator new
void  FUN_004d3760(void*);                                   // 0x004d3760 thiscall ctor
void  FUN_00f47380(void*);                                   // 0x00f47380 cdecl operator delete
char  FUN_004d92b0(void*, void*);                            // 0x004d92b0 cdecl ReadAbilityData
char  FUN_00685520(int);                                     // 0x00685520 cdecl
void  FUN_00555e80(void*, void*);                            // 0x00555e80 cdecl
void  FUN_00d1f160(uint32_t, uint32_t*, int, void**);        // 0x00d1f160 cdecl
__declspec(noinline) void __cdecl FUN_00d1f250(void**, uint32_t); // 0x00d1f250 cdecl

// ---------------------------------------------------------------------------
// ability-slot tables (populated by FUN_00d1f2a0)
// ---------------------------------------------------------------------------
void* g_169de30[3];   // 0x0169de30
void* g_169de3c[2];   // 0x0169de3c
void* g_169de44[2];   // 0x0169de44
void* g_169de4c[6];   // 0x0169de4c
void* g_169de64[6];   // 0x0169de64

// ---------------------------------------------------------------------------
// ref-counted object: vtable at +0x00, ref count at +0x04
// ---------------------------------------------------------------------------
struct RCObj {
    virtual void vf0(int arg);      // vtable[0]  (destroy/release with a flag)
    int mRef;                       // +0x04
};

// shared release step used by the slot tables and the ability holder
static inline void rc_release(RCObj* p)
{
    int n = p->mRef;
    p->mRef = --n;
    if (n == 0) {
        p->mRef = 1;
        p->vf0(1);
    }
}

// ---------------------------------------------------------------------------
// property list (the object held by FUN_00d1f160's local): vtable[1] releases.
// ---------------------------------------------------------------------------
struct PropList {
    virtual void vf0(int arg);      // vtable[0]
    virtual void vf1();             // vtable[1]  (release)
};

// ===========================================================================
// @ 0x00d1f250
// ===========================================================================
void __cdecl FUN_00d1f250(void** arr, uint32_t count)
{
    for (uint32_t i = 0; i < count; i++) {
        RCObj* p = (RCObj*)arr[i];
        if (p != 0) {
            arr[i] = 0;
            int n = p->mRef;
            p->mRef = --n;
            if (n == 0) {
                p->mRef = 1;
                p->vf0(1);
            }
        }
    }
}

// ===========================================================================
// @ 0x00d1f3c0
// ===========================================================================
void __cdecl FUN_00d1f3c0(void)
{
    FUN_00d1f250(g_169de30, 3);
    FUN_00d1f250(g_169de3c, 2);
    FUN_00d1f250(g_169de44, 2);
    FUN_00d1f250(g_169de4c, 6);
    FUN_00d1f250(g_169de64, 6);
}

// ===========================================================================
// @ 0x00d1f2a0
// ===========================================================================
void __cdecl FUN_00d1f2a0(void)
{
    uint32_t a[6];

    a[0] = 0x6282938f; a[1] = 0xe10f1680; a[2] = 0x042592a5;
    FUN_00d1f160(0xdd91ac58, a, 3, g_169de30);

    a[0] = 0x93f63c50; a[1] = 0x854f28cd;
    FUN_00d1f160(0xdd91ac58, a, 2, g_169de3c);

    if (FUN_00685520(2)) {
        a[0] = 0x672b9a9f; a[1] = 0x0f27ecc2;
        FUN_00d1f160(0xdd91ac58, a, 2, g_169de44);
    }

    a[0] = 0x6282938f; a[1] = 0xe10f1680; a[2] = 0x042592a5;
    a[3] = 0x5a93b784; a[4] = 0xe5aa4c4d; a[5] = 0xdf4f5863;
    FUN_00d1f160(0xc85c1f8b, a, 6, g_169de4c);

    a[0] = 0xb522e3ee; a[1] = 0x515b7e25; a[2] = 0x166a2770;
    a[3] = 0xc60fc2ec; a[4] = 0xec13fdbe; a[5] = 0x2b2f0629;
    FUN_00d1f160(0xc85c1f8b, a, 6, g_169de64);
}

// ===========================================================================
// ability holder (the object whose destructor FUN_00d1f070 is)
// ===========================================================================
struct AbilitySet {
    RCObj* mArr00[3];   // +0x00
    RCObj* mArr0c[2];   // +0x0c
    RCObj* mArr14[2];   // +0x14
    RCObj* mArr1c[6];   // +0x1c
    RCObj* mArr34[6];   // +0x34
    void destroy();
};

// @ 0x00d1f070
void AbilitySet::destroy()
{
    for (int i = 5; i >= 0; i--) rc_release(mArr34[i]);
    for (int i = 5; i >= 0; i--) rc_release(mArr1c[i]);
    for (int i = 1; i >= 0; i--) rc_release(mArr14[i]);
    for (int i = 1; i >= 0; i--) rc_release(mArr0c[i]);
    for (int i = 2; i >= 0; i--) rc_release(mArr00[i]);
}

// ===========================================================================
// @ 0x00d1f160
// ===========================================================================
void __cdecl FUN_00d1f160(uint32_t id, uint32_t* data, int count, void** arr)
{
    void* local4 = 0;
    void* pm = SP_PropertyManager();

    for (int n = count; n != 0; n--) {
        if (local4 != 0) {
            PropList* t = (PropList*)local4;
            local4 = 0;
            t->vf1();
        }

        ((void(__thiscall*)(void*, uint32_t, uint32_t, void**))
             (*(void***)pm)[0x2c / 4])(pm, *data, id, &local4);

        if (local4 != 0) {
            RCObj* nc = (RCObj*)FUN_00f473a0(0x13c, "Simulator/cCreatureAbility", 0, 0, 0, 0);
            if (nc != 0)
                FUN_004d3760(nc);

            RCObj* old = (RCObj*)arr[0];
            if (nc != old) {
                if (nc != 0)
                    nc->mRef++;
                arr[0] = nc;
                if (old != 0)
                    rc_release(old);
            }

            FUN_004d92b0(arr[0], local4);
        }

        data++;
        arr++;
    }

    if (local4 != 0) {
        PropList* t = (PropList*)local4;
        t->vf1();
    }
}

// ===========================================================================
// @ 0x00d1f400
// ===========================================================================
struct cTerrainEditor {
    char  _p000[0x10fc];
    void* mpListA;                        // +0x10fc
    void* mpListB;                        // +0x1100
    bool  GetFlagValue(uint32_t id, int* outValue);      // 0x00c77380
    void  SetFlagValue(uint32_t id, uint32_t value);     // 0x00c79f00
    bool  HasFlagOrInsert(uint32_t id);                  // 0x00c77bf0
};

struct IdVec {                            // grow-able uint32 vector
    uint32_t* mpBegin;                    // +0x00
    uint32_t* mpEnd;                      // +0x04
    uint32_t* mpCap;                      // +0x08
};

char g_1654c01;                           // 0x01654c01  game-mode tag
char g_1654c02;                           // 0x01654c02

void* FUN_00f67d90();                     // 0x00f67d90 thiscall GetCurrentTerrainSphere

bool __cdecl FUN_00d1f400(uint32_t param_1)
{
    uint32_t tag = *(uint32_t*)(param_1 + 8);

    void* terr = SP_NounManager();
    cTerrainEditor* sphere = (cTerrainEditor*)
        ((void*(__thiscall*)(void*)) FUN_00f67d90)(terr);

    uint32_t foundA = 0;
    uint32_t foundB = 0;
    IdVec vec;
    vec.mpBegin = 0; vec.mpEnd = 0; vec.mpCap = 0;

    uint32_t nameA;
    uint32_t nameB;

    void* mode = SP_GetCurrentGameMode();
    if (mode == (void*)&g_1654c01) {
        nameA = 0x5ff7927;
        nameB = 0x5ff7928;
        FUN_00555e80(sphere->mpListA, &vec);
    } else if (mode == (void*)&g_1654c02) {
        nameA = 0x5ff7baf;
        nameB = 0x5ff7bb6;
        FUN_00555e80(sphere->mpListA, &vec);
        FUN_00555e80(sphere->mpListB, &vec);
    } else {
        if (vec.mpBegin != 0 && *((int*)vec.mpBegin - 1) != 0)
            FUN_00f47380(vec.mpBegin);
        return false;
    }

    bool okA = sphere->GetFlagValue(nameA, (int*)&foundA);
    if (okA == 0 || sphere->GetFlagValue(nameB, (int*)&foundB) == 0) {
        void* mode2 = SP_GetCurrentGameMode();
        uint32_t n = (uint32_t)(vec.mpEnd - vec.mpBegin);
        uint32_t flags = 0;
        if (mode2 == (void*)&g_1654c01) {
            for (uint32_t i = 0; i < n; i++) {
                uint32_t id = vec.mpBegin[i];
                if (id == 0xe4237bd6)          flags |= 0x20000;
                else if (id == 0x03419db6)     flags |= 0x40000;
                else if (id == 0x630ad0eb)     flags |= 0x80000;
            }
        } else if (mode2 == (void*)&g_1654c02) {
            for (uint32_t i = 0; i < n; i++) {
                int id = (int)vec.mpBegin[i];
                if (id < -0x11f3edc6) {
                    if (id == -0x11f3edc7)         flags |= 0x200000;
                    else if (id == -0x49d6a8dc)    flags |= 0x800000;
                    else if (id == -0x3867e9cf)    flags |= 0x1000000;
                    else if (id == -0x1a0caa4d)    flags |= 0x100000;
                } else if (id == 0x27cb4512)       flags |= 0x2000000;
                else if (id == 0x5961d110)         flags |= 0x400000;
            }
        }
        foundA = flags;
        foundB = 0;
        sphere->SetFlagValue(nameA, flags);
        sphere->SetFlagValue(nameB, foundB);
    }

    // Pack the pair as (high=foundA, low=foundB) and test bit `tag`.
    unsigned long long bits = (unsigned long long)foundB
                            | ((unsigned long long)foundA << 32);
    unsigned long long mask = 1ULL << tag;
    bool result = (bits & mask) != 0;

    if (vec.mpBegin != 0 && *((int*)vec.mpBegin - 1) != 0)
        FUN_00f47380(vec.mpBegin);
    return result;
}

// ---------------------------------------------------------------------------
// support types for SP::UseAbility
// ---------------------------------------------------------------------------
struct cAbilityEntry;
struct cCreatureBase;

struct cCreatureVtbl {
    void* mSlots[0xb0 / 4];                                  // +0x000
    int (__thiscall* fnB0)(cCreatureBase*);                  // +0x0b0  ability count
    cAbilityEntry* (__thiscall* fnB4)(cCreatureBase*, int);  // +0x0b4  ability entry
};

struct cSubC0Vtbl {
    void* mSlots[0x58 / 4];                                  // +0x000
    char (__thiscall* fn58)(void*);                          // +0x058
};

struct cCreatureList {
    cCreatureBase** mpBegin;                                 // +0x00
    cCreatureBase** mpEnd;                                   // +0x04
};

struct cGameNounManager {
    cCreatureList* GetItemID();                              // 0x00b1f9c0
};

struct cBehaviorStimuli {
    void  Set(unsigned int a, unsigned int b, float c, void* d);  // 0x00bc97f0
    void* Play(unsigned int a, unsigned int b);                   // 0x00bc96a0
};

struct Variant {
    int            mD00, mD04, mD08, mD0c;                   // +0x00
    unsigned short mFlags;                                   // +0x10
    unsigned short mTypeId;                                  // +0x12
    Variant& SetInt(const int& value);                       // 0x00671ba0
    void     Destruct(int freeFlag);                         // 0x0093db80
};

struct cCitizen {
    void* GiveOrder(void* a, void* b, void* c);              // 0x00c275b0
};

struct cUIHints {
    void FUN_0067c830(unsigned int id);                      // 0x0067c830
};

struct cAbilityEntry {
    char  _p000[0x08];
    int   mType;                                             // +0x08
    int   mMode;                                             // +0x0c
    char  _p010[0xa8 - 0x10];
    float mF0a8;                                             // +0x0a8
    char  _p0ac[0xf4 - 0xac];
    float mF0f4;                                             // +0x0f4
    char  _p0f8[0x104 - 0xf8];
    float mF104;                                             // +0x104
    char  _p108[0x115 - 0x108];
    char  mB115;                                             // +0x115
    float GetBound(int which);                               // 0x004d3d70
};

struct cCreatureBase {
    cCreatureVtbl* mpVtbl;                                   // +0x000
    char  _p004[0xc0 - 0x04];
    char  mSubC0;                                            // +0x0c0
    char  _pC1[0x110 - 0xc1];
    unsigned int mFlags110;                                  // +0x110
    char  _p114[0x137 - 0x114];
    char  mB137;                                             // +0x137
    char  _p138[0xb20 - 0x138];
    void* mPtrB20;                                           // +0xb20
    char  _pB24[0xb4c - 0xb24];
    void* mPtrB4c;                                           // +0xb4c
    char  _pB50[0xb58 - 0xb50];
    unsigned int mB58;                                       // +0xb58
    char  mB5c;                                              // +0xb5c
    char  _pB5d[0xe70 - 0xb5d];
    int   mE70;                                              // +0xe70
    int   mE74;                                              // +0xe74

    int   FUN_00c196a0(int a, int b, int c);                 // 0x00c196a0
    void  FUN_00c1b020(int a);                               // 0x00c1b020
    void  FUN_00c18370();                                    // 0x00c18370
    void  FUN_00c13650();                                    // 0x00c13650
    void  FUN_00c03c20(int a);                               // 0x00c03c20
    void  FUN_00c03190(unsigned int a, unsigned int b, float c, int d, int e, int f, int g); // 0x00c03190
    int   FUN_00c0c120();                                    // 0x00c0c120
    int   FUN_00c0c130();                                    // 0x00c0c130
    void  SetSprinting(int on);                              // 0x00c1ad10
    void  SetStealthed(int a, int b);                        // 0x00c1aed0
    void  Attack(int target, int flags);                     // 0x00c1e460
    void* FUN_00c0ee60();                                    // 0x00c0ee60
    void* GetTargetAsCreature();                             // 0x00c0ee70
    int   FUN_00c0e0c0(int a);                               // 0x00c0e0c0
};

void* FUN_00ac80d0(void* obj, void* type);                   // 0x00ac80d0
void* FUN_00d51660();                                        // 0x00d51660
void* FUN_00d2e340();                                        // 0x00d2e340
float FUN_00d38a30(int a, void* b);                          // 0x00d38a30
void* FUN_00ad26d0(void* p);                                 // 0x00ad26d0
float FUN_00d99ac0(void* a, void* b, unsigned int c);        // 0x00d99ac0
void* FUN_0067cac0();                                        // 0x0067cac0

extern float g_147a2d8;                                      // 0x0147a2d8 FLT_MAX
extern float g_1473c70;                                      // 0x01473c70 10.0f
extern char  g_1582df5;                                      // 0x01582df5
char g_1654c10;                                              // 0x01654c10 game-mode tag

// ===========================================================================
// @ 0x00d1e930   SP::UseAbility
// ===========================================================================
void __cdecl SP_UseAbility(cCreatureBase* self, int index)
{
    if (index == -1)
        return;

    cCreatureVtbl* vt = *(cCreatureVtbl**)self;
    int count = vt->fnB0(self);
    if (index >= count)
        return;

    cAbilityEntry* entry = vt->fnB4(self, index);
    int type = entry->mType;

    if (entry->mMode == 0)
        self->mE74 = index;
    else if (entry->mMode == 1)
        self->mE70 = index;

    if (((cSubC0Vtbl*)*(void**)((char*)self + 0xc0))->fn58((char*)self + 0xc0) != 0
        && entry->mB115 != 0) {
        void* x = FUN_00d51660();
        if (((*(unsigned int*)((char*)x + 0x6c) >> 4) & 1) != 0) {
            ((cCreatureBase*)FUN_00ac80d0(self, (void*)0x18eb45e))
                ->FUN_00c03190(0, 0x10, g_147a2d8, index, 0, 0, 0);
            return;
        }
    }

    switch (type) {
    // ---- 0x28 : interact / use ------------------------------------------
    case 0x28: {
        if (self->GetTargetAsCreature() == 0)
            break;
        self->FUN_00c196a0(index, 1, 0);
        return;
    }

    // ---- 0x27, 0x50 : sprint toggle -------------------------------------
    case 0x27:
    case 0x50: {
        if (self->FUN_00c0c120() != 0) {
            self->SetSprinting(0);
            cCreatureList* list = ((cGameNounManager*)SP_NounManager())->GetItemID();
            for (cCreatureBase** it = list->mpBegin; it != list->mpEnd; ++it)
                (*it)->SetSprinting(0);
        } else {
            self->FUN_00c196a0(index, 0, 1);
            self->SetSprinting(1);
            cCreatureList* list = ((cGameNounManager*)SP_NounManager())->GetItemID();
            for (cCreatureBase** it = list->mpBegin; it != list->mpEnd; ++it)
                (*it)->SetSprinting(1);
        }
        return;
    }

    // ---- 0x0d, 0x52 : stealth toggle ------------------------------------
    case 0x0d:
    case 0x52: {
        if (self->FUN_00c0c130() != 0) {
            self->SetStealthed(0, 0);
            cCreatureList* list = ((cGameNounManager*)SP_NounManager())->GetItemID();
            for (cCreatureBase** it = list->mpBegin; it != list->mpEnd; ++it)
                (*it)->SetStealthed(0, 0);
            return;
        }
        if (self->FUN_00c196a0(index, 0, 1) != (unsigned int)index)
            break;
        self->SetStealthed(1, 0);
        cCreatureList* list = ((cGameNounManager*)SP_NounManager())->GetItemID();
        for (cCreatureBase** it = list->mpBegin; it != list->mpEnd; ++it)
            (*it)->SetStealthed(1, 0);
        return;
    }

    // ---- 0x10 : play visual effect --------------------------------------
    case 0x10: {
        ((cCreatureBase*)FUN_00ac80d0(self, (void*)0x18eb45e))
            ->FUN_00c03190(0x800, 0, g_147a2d8, 0, 0, 0, 0);
        cTerrainEditor* sphere =
            (cTerrainEditor*)((void*(__thiscall*)(void*))FUN_00f67d90)(SP_NounManager());
        sphere->HasFlagOrInsert(0x52da1fa);
        return;
    }

    // ---- 0x53 ------------------------------------------------------------
    case 0x53: {
        if (((self->mB58 >> 9) & 1) != 0) {
            self->FUN_00c18370();
            return;
        }
        if (self->mB137 != 0 || (self->mFlags110 & 0x1000) != 0)
            goto useAbility;
        break;
    }

    // ---- 0x11 ------------------------------------------------------------
    case 0x11: {
        if (self->mB137 == 0)
            break;
        if (SP_GetCurrentGameMode() == (void*)&g_1654c10
            && ((self->mB58 >> 9) & 1) != 0
            && *(unsigned int*)((char*)self->mPtrB20 + 0x610) > 2) {
            self->FUN_00c13650();
            return;
        }
        goto useAbility;
    }

    // ---- 0x12, 0x51 ------------------------------------------------------
    case 0x12:
    case 0x51: {
        void* x = FUN_00d2e340();
        if (*(int*)((char*)x + 8) <= 0)
            break;
        if (self->FUN_00c0e0c0(0x5485a4c) != 0)
            break;
        if (self->FUN_00c0e0c0(0x77300ff) != 0)
            break;
        if (type != 0x51)
            --*(int*)((char*)FUN_00d2e340() + 8);
        self->FUN_00c1b020((int)entry->mF104);
        return;
    }

    // ---- 0x1d : attack ---------------------------------------------------
    case 0x1d: {
        if (((self->mB58 >> 9) & 1) == 0)
            goto attack;
        ((cCreatureBase*)FUN_00ac80d0(self, (void*)0x18eb45e))->FUN_00c03c20(index);
        return;
    }

    // ---- 0x22..0x25, 0x40, 0x4c..0x4f, 0x54..0x56 : play order -----------
    case 0x22: case 0x23: case 0x24: case 0x25:
    case 0x40: case 0x4c: case 0x4d: case 0x4e: case 0x4f:
    case 0x54: case 0x55: case 0x56: {
        if (((self->mB58 >> 9) & 1) == 0)
            break;
        cCreatureBase* obj = (cCreatureBase*)FUN_00ac80d0(self, (void*)0x18eb45e);
        void* cb = self->mPtrB4c;
        if (*(int*)((char*)cb + 0x1d8) != 0x941bd4bf) {
            obj->FUN_00c03190(0x10000, 0, g_147a2d8, 0, 0,
                              (int)self->GetTargetAsCreature(), 0);
            return;
        }
        cBehaviorStimuli* stim = (cBehaviorStimuli*)((char*)cb + 8);
        stim->Set(0x10000000, 0, g_1473c70, 0);
        void* r = stim->Play(0x10000000, 0);
        *(int*)((char*)r + 0x10) = index;
        *(int*)((char*)r + 0x0c) = 0;
        return;
    }

    // ---- 0x1e..0x21, 0x3d, 0x3e, 0x41, 0x42, 0x48..0x4b : use on target --
    case 0x1e: case 0x1f: case 0x20: case 0x21:
    case 0x3d: case 0x3e: case 0x41: case 0x42:
    case 0x48: case 0x49: case 0x4a: case 0x4b: {
        cTerrainEditor* sphere =
            (cTerrainEditor*)((void*(__thiscall*)(void*))FUN_00f67d90)(SP_NounManager());
        sphere->HasFlagOrInsert(0x52da1fe);
        if (self->FUN_00c0ee60() == 0)
            break;
        cAbilityEntry* entry2 = vt->fnB4(self, index);
        float rangeFactor = FUN_00d38a30(0, self);
        void* z = FUN_00ad26d0(self->FUN_00c0ee60());
        float result = g_147a2d8;
        if (z != 0) {
            float bits = g_147a2d8;
            *(unsigned char*)&bits = (unsigned char)(entry2->mMode == 1);
            result = FUN_00d99ac0((void*)((char*)self + 0xc0), z, *(unsigned int*)&bits);
        }
        if (((self->mB58 >> 9) & 1) != 0
            && !(((entry2->mF0f4 + entry2->mF0a8) * rangeFactor) < result)) {
            if (!(result < entry2->GetBound((int)((self->mB58 >> 9) & 1)))) {
                if (((self->mB58 >> 9) & 1) != 0) {
                    ((cCreatureBase*)FUN_00ac80d0(self, (void*)0x18eb45e))
                        ->FUN_00c03c20(index);
                    return;
                }
                goto attack;
            }
        }
        if (g_1582df5 != 0)
            goto labAttack;
        if (entry2->GetBound((int)((self->mB58 >> 9) & 1)) > result)
            goto labAttack;
        if (result > (entry2->mF0f4 + entry2->mF0a8) * rangeFactor)
            goto labAttack;
        if (((self->mB58 >> 9) & 1) == 0)
            break;
        if (!(entry2->GetBound(1) > result))
            break;
        if (SP_GetCurrentGameMode() == (void*)&g_1654c01)
            ((cUIHints*)FUN_0067cac0())->FUN_0067c830(0xc30cd054);
        return;
    labAttack:
        if (entry2->mMode == 1)
            self->mB5c = 1;
        ((cCreatureBase*)FUN_00ac80d0(self, (void*)0x18eb45e))
            ->FUN_00c03190(0x20, 0, g_147a2d8, index, 0, 0, 0);
        return;
    }

    // ---- 0x31..0x33 ------------------------------------------------------
    case 0x31: case 0x32: case 0x33: {
        ((cCreatureBase*)FUN_00ac80d0(self, (void*)0x18eb45e))
            ->FUN_00c03190(0x8000, 0, g_147a2d8, index, 0, 0, 0);
        return;
    }

    // ---- 0x34..0x39 : give order to citizen ------------------------------
    case 0x34: case 0x35: case 0x36: case 0x37: case 0x38: case 0x39: {
        cCitizen* citizen = (cCitizen*)FUN_00ac80d0(self, (void*)0x18eb4b7);
        if (citizen == 0)
            break;
        Variant v;
        v.SetInt(index);
        citizen->GiveOrder((void*)0x16, 0, &v);
        if ((v.mFlags & 4) != 0)
            v.Destruct(0);
        return;
    }

    default:
        break;
    }

    return;

useAbility:
    self->FUN_00c1b020((int)entry->mF104);
    return;

attack:
    self->Attack(index, 0);
    return;
}