// Slice s00cea090 - SPAppMode/CityDisplayStrategy.obj region 0x00cea090..0x00ceb290:
// SP::cCityDisplayStrategy init/update/posse management plus an eastl rbtree erase
// helper used by its AutoRefCount<map> members.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /Isrc/game/include  (no /EHsc)
#include "types.h"

typedef unsigned int uint;

// ---- external callees / accessors (addresses in comments) --------------
void* __cdecl FUN_00f473a0(uint, const char*, int, int, int, int); // 0x00f473a0 EAAllocate
void* __cdecl EAAllocate(uint, const char*, int, int, int, int);    // alias
void  __cdecl FUN_00f47380(void*);                                 // 0x00f47380 operator delete
void* __cdecl FUN_00cf74c0();                                      // 0x00cf74c0 cCivModeStrategy::Get
void* __cdecl FUN_00cf74f0(void*);                                 // 0x00cf74f0 GetState
void* __cdecl FUN_00b3d300();                                      // 0x00b3d300 NounManager
void* __cdecl FUN_00b25fb0(void*);                                 // 0x00b25fb0 GetPlayerCivilization
void* __cdecl FUN_0067ddd0();                                      // 0x0067ddd0 EffectsManager
void* __cdecl FUN_00a206f0();                                      // 0x00a206f0 EA::Audio::GetSystemAT
void* __cdecl FUN_00b3d280();                                      // 0x00b3d280 GetCameraCtl
void* __cdecl FUN_00b3d350();                                      // 0x00b3d350 PlanetModel
void* __cdecl FUN_00bda200(void*, int, int*);                      // 0x00bda200
void* __cdecl FUN_0067dcc0();                                      // 0x0067dcc0 MessageServer
void* __cdecl FUN_00b3d3e0();                                      // 0x00b3d3e0 EventLog
void* __cdecl FUN_00e24c90(void*, void*);                          // 0x00e24c90 cSPUIPosse::FindItem
void* __cdecl FUN_00af14b0(void*);                                 // 0x00af14b0 TimerOwner::Ctor
void  __cdecl FUN_00af1430(void*);                                 // 0x00af1430 TimerOwner::Dtor
void* __cdecl FUN_00e5c780(void*, void*, void*);                   // 0x00e5c780 rbtree::find
void  __cdecl FUN_00e0c490(void*, void*, int*);                    // 0x00e0c490
void  __cdecl FUN_00e04540(void*, float);                          // 0x00e04540
void* __cdecl FUN_00cf8e20(void*, int);                            // 0x00cf8e20
void* __cdecl FUN_00921580(void*);                                 // 0x00921580 RBTreeIncrement
void  __cdecl FUN_00921880(void*, void*);                          // 0x00921880 RBTreeErase
void  __cdecl FUN_00f240d0(void*, int*);                           // 0x00f240d0 EventTree::Destroy
void  __cdecl FUN_0040ce80(void*);                                 // 0x0040ce80
void  __cdecl FUN_00f33a80(void*, void*, void*);                   // 0x00f33a80
void* __cdecl FUN_00537dc0(void*, const void*);                    // 0x00537dc0 cSPTransformOps::Assign
void  __cdecl FUN_00dd5a10(void*, float, float);                   // 0x00dd5a10
void  __cdecl FUN_00f473a0_();                                     // unused

// vtable/register-based member calls modeled via __thiscall stubs
struct Vt { void __thiscall a(); void __thiscall b(); void __thiscall c(); };
struct Vt2 { void __thiscall f(); void __thiscall g(); void __thiscall h(int); };
struct RBTH { void __thiscall Fn(void*, void*); };
struct Iter { void* p; };
struct LayoutObj {
    void* __thiscall ctor0();
    char  __thiscall InitLayout(const void* w, int a, int b, int c);
    void  __thiscall SetVis(int v);
};
struct SelEffObj { void __thiscall Set(int a, int b); };
struct TimerOwnerObj { void __thiscall Ctor(); };
struct EventLogObj { void __thiscall Apply(float a, float b); };

// retail layout of SP::cCityDisplayStrategy (offsets from disassembly)
struct CDS {
    void*  mpVtbl;         // +0x00
    char   pad00[0x38];
    void*  mpIHandlerVtbl; // +0x38
    uint8_t mbGodModeActive; // +0x3c
    int    mGodModeVehiclePurpose;   // +0x40
    int    mGodModeVehicleLocomotion;// +0x44
    uint   mGodModeCiv;    // +0x48
    void*  mAutoHandler0;  // +0x4c  message id / handler ptr
    void*  mAutoHandler4;  // +0x50
    void*  mAutoHandler8;  // +0x54
    int    mAutoHandlerC;  // +0x58
    void*  mAutoHandler10; // +0x5c
    void*  mpMode;         // +0x60
    void*  mpGlobalCivUI;  // +0x64
    int    mDebugAIPage;   // +0x68
    void*  mPosses[4];     // +0x6c
    char   mMaps[4 * 0x1c];// +0x7c
    void*  mpPosseIconLayout; // +0xec
    void*  mpMiniMapWin;   // +0xf0
    void*  mpTargetingReticle; // +0xf4
    void*  mpErrorReticle; // +0xf8
    char   pad_fc[0x10c - 0xfc];
    void*  mpSelEff0;      // +0x10c
    void*  mpSelEff1;      // +0x110
    void*  mpSelEff2;      // +0x114
    void*  mpSelEff3;      // +0x118
    void*  mpSelEff4;      // +0x11c
    char   pad_end[0];

    void Init();
    void Update();
    void Update2(void* a, int b);
    void Refresh();
    void Assign(void* other);
    void RemoveVehicle(void* out, void* node);
    int  EraseKey(void* key);
    void Destruct();
    void* ctor(void* a);
};

// =======================================================================
// SP::cCityDisplayStrategy::Init (0x00cea090) - 259 bytes
// =======================================================================
// @ 0x00cea090
void CDS::Init()
{
    char* self = (char*)this;
    void* obj = FUN_00f473a0(0x18, "Simulator/PosseItemCivIcons", 0, 0, 0, 0);
    void* pNew;
    if (obj != 0) {
        pNew = ((LayoutObj*)obj)->ctor0();
    } else {
        pNew = 0;
    }
    void* old = *(void**)(self + 0xec);
    if (pNew != old) {
        if (pNew != 0) {
            typedef void(__thiscall* AddR)(void*);
            ((AddR)(*(void**)(*(char**)pNew + 4)))(pNew);
        }
        *(void**)(self + 0xec) = pNew;
        if (old != 0) {
            typedef void(__thiscall* Rel)(void*);
            ((Rel)(*(void**)(*(char**)old + 8)))(old);
        }
    }

    void* layout = *(void**)(self + 0xec);
    char ok = ((LayoutObj*)layout)->InitLayout((const void*)0x1477e3c, 0x40464100, 1, 0x5b598fa);
    if (ok) {
        void* l2 = *(void**)(self + 0xec);
        ((LayoutObj*)l2)->SetVis(0);
    }

    ((SelEffObj*)*(void**)(self + 0x10c))->Set(0, 0);
    ((SelEffObj*)*(void**)(self + 0x110))->Set(1, 0);
    ((SelEffObj*)*(void**)(self + 0x114))->Set(2, 0);
    ((SelEffObj*)*(void**)(self + 0x118))->Set(0, 1);
    ((SelEffObj*)*(void**)(self + 0x11c))->Set(1, 1);

    char* arr = self + 0x100;
    int n = 3;
    do {
        void* sys = FUN_00a206f0();
        void* r;
        if (sys != 0) {
            typedef void* (__thiscall* M)(void*);
            r = ((M)(*(void**)(*(char**)sys + 0x24)))(sys);
        } else {
            r = 0;
        }
        *(void**)arr = r;
        arr += 4;
    } while (--n);
}

// =======================================================================
// SP::cCityDisplayStrategy::Update (0x00cea1a0) - 1354 bytes
// =======================================================================
// @ 0x00cea1a0
void CDS::Update()
{
    char* self = (char*)this;
    char* st = (char*)FUN_00cf74f0(FUN_00cf74c0());
    int idx = *(int*)(st + 0x140);
    if (idx == -1) return;

    char* reticle = self + 0xf4;
    void* fx;
    if (*(void**)(self + 0xf4) == 0) {
        fx = FUN_0067ddd0();
        void* cur = *(void**)reticle;
        if (cur != 0) {
            *(void**)reticle = 0;
            typedef void(__thiscall* Rel)(void*);
            ((Rel)(*(void**)(*(char**)cur + 4)))(cur);
        }
        typedef char(__thiscall* Mk)(void*, int, int, void*);
        char ok = ((Mk)(*(void**)(*(char**)fx + 0x2c)))(fx, *(int*)(idx * 4 + 0x1477f40), 0, reticle);
        if (ok) {
            void* e = *(void**)reticle;
            typedef void(__thiscall* P)(void*, int);
            ((P)(*(void**)(*(char**)e + 8)))(e, 0);
        }
    }

    char* reticle2 = self + 0xfc;
    if (*(void**)(self + 0xfc) == 0) {
        fx = FUN_0067ddd0();
        void* cur = *(void**)reticle2;
        if (cur != 0) {
            *(void**)reticle2 = 0;
            typedef void(__thiscall* Rel)(void*);
            ((Rel)(*(void**)(*(char**)cur + 4)))(cur);
        }
        typedef char(__thiscall* Mk)(void*, int, int, void*);
        char ok = ((Mk)(*(void**)(*(char**)fx + 0x2c)))(fx, 0x78beeec5, 0, reticle2);
        if (ok) {
            void* e = *(void**)reticle2;
            typedef void(__thiscall* P)(void*, int);
            ((P)(*(void**)(*(char**)e + 8)))(e, 0);
        }
    }

    if (*(int*)(idx * 4 + 0x1477f10) != 0) {
        char* r3 = self + 0xf8;
        fx = FUN_0067ddd0();
        void* cur = *(void**)r3;
        if (cur != 0) {
            *(void**)r3 = 0;
            typedef void(__thiscall* Rel)(void*);
            ((Rel)(*(void**)(*(char**)cur + 4)))(cur);
        }
        typedef char(__thiscall* Mk)(void*, int, int, void*);
        char ok = ((Mk)(*(void**)(*(char**)fx + 0x2c)))(fx, *(int*)(idx * 4 + 0x1477f40), 0, r3);
        if (ok) {
            void* e = *(void**)r3;
            typedef void(__thiscall* P)(void*, int);
            ((P)(*(void**)(*(char**)e + 8)))(e, 0);
        }
    }

    void* mode = *(void**)st;
    typedef void(__thiscall* GV)(void*);
    int v = (int)(((GV*)(*(void**)((char*)mode + 0x34)))[0], *(void**)((char*)mode + 0x34));
    (void)v;
}

// =======================================================================
// 0x00cea6f0 - 265 bytes
// =======================================================================
// @ 0x00cea6f0
void CDS::Update2(void* a, int b)
{
    int idx;
    char* st = (char*)FUN_00cf74f0(FUN_00cf74c0());
    idx = *(int*)(st + 0x140);
    if (idx == -1) return;
    void* ref = *(void**)(idx * 4 + 0x1477f70);
    if (ref == 0) return;

    char buf[0x10];
    FUN_00bda200(buf, idx, (int*)a);
    void* fx = FUN_0067ddd0();
    typedef char(__thiscall* Mk)(void*, void*, int, void*);
    char ok = ((Mk)(*(void**)(*(char**)fx + 0x2c)))(fx, *(void**)(idx * 4 + 0x1477f70), 0, buf);
    if (!ok) return;
    (void)b;
}

// =======================================================================
// 0x00cea970 - 333 bytes
// =======================================================================
// @ 0x00cea970
void CDS::Refresh()
{
    char* self = (char*)this;
    void* cam = FUN_00b3d280();
    if (cam != 0) {
        void* minimap = *(void**)self ? 0 : *(void**)(self + 0xf0);
        (void)minimap;
        if (*(void**)(self + 0xf0) != 0) {
            char tmp[0x10];
            typedef void* (__thiscall* M)(void*, void*);
            char* r = (char*)((M)0xb13900)(cam, tmp);
            typedef void* (__thiscall* M2)(void*);
            void* r2 = ((M2)0xb10200)(cam);
            (void)r; (void)r2;
        }
    }
    void* nm = FUN_00b3d300();
    void* civ = FUN_00b25fb0(nm);
    Update();
    if (*(int*)(self + 0x64) != 0 && civ != 0) {
        float f = *(float*)((char*)civ + 0x98);
        int n = (int)f;
        float fn = (float)n;
        if (f < fn) n -= 1;
        void* v = *(void**)(self + 0x64);
        void* ms = FUN_00cf74c0();
        float r = ((float(__thiscall*)(void*, int))0xcf8e20)(ms, n);
        typedef void(__thiscall* S)(void*, float);
        ((S)0xe04540)(v, r);
    }
    void* posses = self + 0x6c;
    int n = 4;
    do {
        if (*(void**)posses != 0) {
            void* item = FUN_00e24c90(*(void**)posses, 0);
            (void)item;
        }
        posses = (char*)posses + 4;
    } while (--n);
}

// =======================================================================
// 0x00ceaac0 - 86 bytes
// =======================================================================
// @ 0x00ceaac0
void CDS::RemoveVehicle(void* out, void* node)
{
    char* self = (char*)this;
    (*(int*)(self + 0x14)) -= 1;
    void* volatile next = FUN_00921580(node);
    FUN_00921880(node, self + 4);
    void* p0 = *(void**)((char*)node + 0x14);
    if (p0 != 0) {
        typedef void(__thiscall* Rel)(void*);
        ((Rel)(*(void**)(*(char**)p0 + 4)))(p0);
    }
    void* p1 = *(void**)((char*)node + 0x10);
    if (p1 != 0) {
        typedef void(__thiscall* Rel)(void*);
        ((Rel)(*(void**)(*(char**)p1 + 4)))(p1);
    }
    FUN_00f47380(node);
    *(void**)out = next;
}

// =======================================================================
// 0x00ceab20 - 63 bytes
// =======================================================================
// @ 0x00ceab20
int CDS::EraseKey(void* key)
{
    ((RBTH*)this)->Fn(&key, key);
    if (key != (char*)this + 4) {
        char* n = (char*)key;
        RemoveVehicle(&key, n);
        return 1;
    }
    return 0;
}

// =======================================================================
// 0x00ceac50 - 515 bytes
// =======================================================================
// @ 0x00ceac50
void CDS::Destruct()
{
    char* self = (char*)this;
    *(int*)(self) = 0x1477fa8;
    *(int*)(self + 0x38) = 0x1477fa0;

    if (*(void**)(self + 0x4c) != 0) {
        void* h = *(void**)(self + 0x4c);
        void* a1 = *(void**)(self + 0x5c);
        void* a2 = *(void**)(self + 0x58);
        void* a3 = *(void**)(self + 0x54);
        void* a4 = *(void**)(self + 0x50);
        *(void**)(self + 0x4c) = 0;
        ((void(__cdecl*)(void*, void*, void*, void*, void*))0x571db0)(h, a4, a3, a2, a1);
    }

    if (*(void**)(self + 0x64) != 0) {
        void* p = *(void**)(self + 0x64);
        typedef void(__thiscall* M)(void*);
        ((M)(*(void**)(*(char**)p + 0xc)))(p);
        p = *(void**)(self + 0x64);
        if (p != 0) {
            char* sub = (char*)p + 0x68;
            *(void**)(self + 0x64) = 0;
            typedef void(__thiscall* M2)(void*);
            ((M2)(*(void**)(*(char**)sub + 8)))(sub);
        }
    }

    char* posses = self + 0x6c;
    char* maps = self + 0x80;
    int n = 4;
    do {
        if (*(void**)posses != 0) {
            void* p = *(void**)posses;
            typedef void(__thiscall* M)(void*);
            ((M)(*(void**)(*(char**)p + 0x88)))(p);
            p = *(void**)posses;
            if (p != 0) {
                *(void**)posses = 0;
                typedef void(__thiscall* Rel)(void*);
                ((Rel)(*(void**)(*(char**)p + 4)))(p);
            }
        }
        FUN_00f240d0(maps - 4, *(int**)(maps + 8));
        *(void**)(maps) = maps;
        *(void**)(maps + 4) = maps;
        *(int*)(maps + 8) = 0;
        *(uint8_t*)(maps + 0xc) = 0;
        *(int*)(maps + 0x10) = 0;
        posses += 4;
        maps += 0x1c;
    } while (--n);

    if (*(void**)0x169ba4c == self) *(void**)0x169ba4c = 0;

    if (*(void**)(self + 0x10c) != 0) {
        void* p = *(void**)(self + 0x10c);
        typedef void(__thiscall* M)(void*, int);
        ((M)(*(void**)(*(char**)p + 4)))(p, 1);
    }
    if (*(void**)(self + 0x110) != 0) {
        void* p = *(void**)(self + 0x110);
        typedef void(__thiscall* M)(void*, int);
        ((M)(*(void**)(*(char**)p + 4)))(p, 1);
    }
    if (*(void**)(self + 0x114) != 0) {
        void* p = *(void**)(self + 0x114);
        typedef void(__thiscall* M)(void*, int);
        ((M)(*(void**)(*(char**)p + 4)))(p, 1);
    }
    if (*(void**)(self + 0x118) != 0) {
        void* p = *(void**)(self + 0x118);
        typedef void(__thiscall* M)(void*, int);
        ((M)(*(void**)(*(char**)p + 4)))(p, 1);
    }
    if (*(void**)(self + 0x11c) != 0) {
        void* p = *(void**)(self + 0x11c);
        typedef void(__thiscall* M)(void*, int);
        ((M)(*(void**)(*(char**)p + 4)))(p, 1);
    }
    if (*(void**)(self + 0xfc) != 0) {
        void* p = *(void**)(self + 0xfc);
        typedef void(__thiscall* M)(void*);
        ((M)(*(void**)(*(char**)p + 4)))(p);
    }
    if (*(void**)(self + 0xf8) != 0) {
        void* p = *(void**)(self + 0xf8);
        typedef void(__thiscall* M)(void*);
        ((M)(*(void**)(*(char**)p + 4)))(p);
    }
    if (*(void**)(self + 0xf4) != 0) {
        void* p = *(void**)(self + 0xf4);
        typedef void(__thiscall* M)(void*);
        ((M)(*(void**)(*(char**)p + 4)))(p);
    }
    if (*(void**)(self + 0xf0) != 0) {
        void* p = *(void**)(self + 0xf0);
        typedef void(__thiscall* M)(void*);
        ((M)(*(void**)(*(char**)p + 4)))(p);
    }
    if (*(void**)(self + 0xec) != 0) {
        void* p = *(void**)(self + 0xec);
        typedef void(__thiscall* M)(void*);
        ((M)(*(void**)(*(char**)p + 8)))(p);
    }

    char* e = self + 0xec;
    int k = 3;
    do {
        e -= 0x1c;
        FUN_00f240d0(e, *(int**)(e + 0x10));
    } while (--k >= 0);

    char* v = self + 0x7c;
    int m = 3;
    do {
        v -= 4;
        if (*(void**)v != 0) {
            void* p = *(void**)v;
            typedef void(__thiscall* Rel)(void*);
            ((Rel)(*(void**)(*(char**)p + 4)))(p);
        }
    } while (--m >= 0);

    if (*(void**)(self + 0x64) != 0) {
        void* p = *(void**)(self + 0x64);
        char* sub = (char*)p + 0x68;
        typedef void(__thiscall* M)(void*);
        ((M)(*(void**)(*(char**)sub + 8)))(sub);
    }

    if (*(void**)(self + 0x4c) != 0) {
        void* h = *(void**)(self + 0x4c);
        void* a1 = *(void**)(self + 0x5c);
        void* a2 = *(void**)(self + 0x58);
        void* a3 = *(void**)(self + 0x54);
        void* a4 = *(void**)(self + 0x50);
        *(void**)(self + 0x4c) = 0;
        ((void(__cdecl*)(void*, void*, void*, void*, void*))0x571db0)(h, a4, a3, a2, a1);
    }

    *(int*)(self + 0x38) = 0x13eb394;
    FUN_00af1430(self);
}

// =======================================================================
// 0x00ceae70 - 244 bytes
// =======================================================================
// @ 0x00ceae70
void CDS::Assign(void* other)
{
    (void)other;
    void* gm = (void*)0x1654c04;
    if (((void* (*)())0xb5b800)() != gm) return;
    char* self = (char*)this;
    char* o = (char*)other;
    typedef char(__thiscall* IsX)(void*);
    char al = ((IsX)(*(void**)(*(char**)(o + 0x34) + 0x58)))(o + 0x34);
    int idx = *(int*)(o + 0xb20);
    if (*(void**)(self + idx * 4 + 0x6c) == 0) return;
    if (!al) return;
    (void)idx;
}

// =======================================================================
// 0x00ceaf70 - 287 bytes (eastl vector<0x38-byte> push_back)
// =======================================================================
// @ 0x00ceaf70
void* __cdecl FUN_00ceaf70(void* self, void* a, void* b)
{
    char* s = (char*)self;
    void* end = *(void**)(s + 4);
    void* from = a;
    if (end == *(void**)(s + 8)) {
        // need to grow
        int cur = (int)end - *(int*)(s);
        (void)cur;
    }
    {
        char* dest = (char*)end + 0x38;
        (void)dest;
    }
    if (end != *(void**)(s + 8)) {
        void* src = b;
        if ((char*)b >= (char*)a && (char*)b < (char*)end) src = (char*)b + 0x38;
        if (end != 0) FUN_0040ce80((char*)end - 0x38);
        void* e2 = *(void**)(s + 4);
        FUN_00f33a80(e2, (char*)e2 - 0x38, from);
        FUN_00537dc0(a, src);
        *(void**)(s + 4) = (char*)(*(void**)(s + 4)) + 0x38;
        return a;
    }
    return 0;
}

// =======================================================================
// Simulator::cCityDisplayStrategy::cCityDisplayStrategy (0x00ceb090) - 510 bytes
// =======================================================================
// @ 0x00ceb090
void* CDS::ctor(void* a)
{
    char* self = (char*)this;
    ((TimerOwnerObj*)self)->Ctor();
    *(volatile int*)(self + 0x38) = 0x13eb394;
    *(int*)(self) = 0x1477fa8;
    *(int*)(self + 0x38) = 0x1477fa0;
    *(char*)(self + 0x3c) = 0;
    *(int*)(self + 0x40) = 0;
    *(int*)(self + 0x44) = 0;
    *(int*)(self + 0x48) = -1;
    *(int*)(self + 0x4c) = 0;
    *(int*)(self + 0x50) = 0;
    *(int*)(self + 0x54) = 0;
    *(int*)(self + 0x58) = 0;
    *(int*)(self + 0x5c) = 0;
    *(void**)(self + 0x60) = a;
    *(int*)(self + 0x64) = 0;
    *(int*)(self + 0x68) = 0;
    *(int*)(self + 0x6c) = 0;
    *(int*)(self + 0x70) = 0;
    *(int*)(self + 0x74) = 0;
    *(int*)(self + 0x78) = 0;

    char* m = self + 0x80;
    int n = 3;
    do {
        *(int*)(m + 0xc) = 0;
        *(void**)(m) = m;
        *(void**)(m + 4) = m;
        *(int*)(m + 8) = 0;
        *(char*)(m + 0xc) = 0;
        *(int*)(m + 0x10) = 0;
        m += 0x1c;
    } while (--n >= 0);

    *(int*)(self + 0xec) = 0;
    *(int*)(self + 0xf0) = 0;
    *(int*)(self + 0xf4) = 0;
    *(int*)(self + 0xf8) = 0;
    *(int*)(self + 0xfc) = 0;
    *(int*)(self + 0x10c) = 0;
    *(int*)(self + 0x110) = 0;
    *(int*)(self + 0x118) = 0;
    *(int*)(self + 0x11c) = 0;

    void* ms = FUN_0067dcc0();
    void* handler = self + 0x38;
    *(void**)(self + 0x4c) = ms;
    *(void**)(self + 0x50) = handler;
    *(int*)(self + 0x54) = 0x1477fb0;
    *(int*)(self + 0x58) = 3;
    *(int*)(self + 0x5c) = 0;
    if (ms != 0 && handler != 0) {
        int off = 0;
        do {
            void* id = *(void**)(off + 0x1477fb0);
            void* h2 = self + 0x38;
            typedef void(__thiscall* Sub)(void*, void*, void*);
            ((Sub)(*(void**)(*(char**)ms + 0x24)))(ms, h2, id);
            off += 4;
        } while (off < 0xc);
    }

    float c = *(float*)0x146138c;
    void* el = FUN_00b3d3e0();
    *(void**)0x169ba4c = self;
    ((EventLogObj*)el)->Apply(0.0f, c);

    void* o0 = FUN_00f473a0(0x18, "Simulator/cSelectionEffectStreamer", 0, 0, 0, 0);
    if (o0 != 0) *(int*)((char*)o0) = 0x1477e30;
    *(void**)(self + 0x10c) = o0;
    void* o1 = FUN_00f473a0(0x18, "Simulator/cSelectionEffectStreamer", 0, 0, 0, 0);
    if (o1 != 0) *(int*)((char*)o1) = 0x1477e30;
    *(void**)(self + 0x110) = o1;
    void* o2 = FUN_00f473a0(0x18, "Simulator/cSelectionEffectStreamer", 0, 0, 0, 0);
    if (o2 != 0) *(int*)((char*)o2) = 0x1477e30;
    *(void**)(self + 0x114) = o2;
    void* o3 = FUN_00f473a0(0x18, "Simulator/cSelectionEffectStreamer", 0, 0, 0, 0);
    if (o3 != 0) *(int*)((char*)o3) = 0x1477e30;
    *(void**)(self + 0x118) = o3;
    void* o4 = FUN_00f473a0(0x18, "Simulator/cSelectionEffectStreamer", 0, 0, 0, 0);
    if (o4 != 0) *(int*)((char*)o4) = 0x1477e30;
    *(void**)(self + 0x11c) = o4;

    *(int*)(self + 0x100) = 0;
    *(int*)(self + 0x104) = 0;
    *(int*)(self + 0x108) = 0;
    return self;
}
