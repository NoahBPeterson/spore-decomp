// Slice s00dea870 -- Spore "galaxy game entry" UI module.
// Flags: /O2 /MD /Gy /TP /arch:SSE (this module has no /EHsc: its string locals
// carry no unwind frame, matching its sibling slice s00de8ad0).
// Compiler: VS2008 SP1 (cl 15.00.30729.01, default /GS).
//
// Retail layout of the module global at 0x016a1344 ("kGUI_PanelIDs"):
//   +0x108 dword, +0x144 cSPUILayout, +0x15c/0x184/0x198/0x1ac pointers,
//   +0x1ec dword, +0x1f2/0x1f3/0x1f4 bytes, +0x200 dword,
//   +0x204 array of 12-byte { panelID dword, float, float } entries.
#include "types.h"

// ---------------------------------------------------------------------------------------------
struct LocInfo { uint32_t mData[3]; };
struct LocBuf  { wchar_t mName[64]; uint16_t mTail; };

class cIVisualEffect {
public:
    virtual void vf0();                                        // +0x00
    virtual void AddRef();                                     // +0x04
    virtual void Release();                                    // +0x08
    virtual void Tick(int);                                    // +0x0c
    virtual bool Find(uint32_t id, void* out, int b, int c, int d); // +0x10
};
class cEffectsWorldSub {
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool Find(uint32_t id, void* out, int a, int b, int c, int d); // +0x0c
    virtual bool Find2(uint32_t id, void* out);                            // +0x10
    virtual bool Find3(uint32_t id, void* out);                            // +0x14
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool Find4(uint32_t id, void* out);                            // +0x24
};
class cEffectsWorld { public: void* mpSub; };
class cMovieSystem {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void PlayMovie(void* pEntry, const void* pDesc);   // +0x10
    virtual bool IsMoviePlaying();                             // +0x14
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15();
    virtual void StopMovies(int);                              // +0x40
};
struct IWindow {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void PlayAnim(int a, int b);                       // +0x7c
};
class cSPUILayout {
public:
    bool Init(const wchar_t* name, int a, char b, int c, uint32_t d); // 0x00812160
    void SetVisibility(bool v);                                       // 0x00810590
    IWindow* FindWindowByID(uint32_t id, int a);                      // 0x008105b0
};
class cSPUIGlobalUI {
public:
    void SetVisibility(bool v);                                       // 0x00e01350
};
class cMessageServer {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual int SendMessage(uint32_t id, uint32_t type, uint32_t a, uint32_t b); // +0x18
    virtual void v7(); virtual void v8();
    virtual int AddHandler(void* obj, uint32_t id);                   // +0x24
};
class DBCheck {
public:
    DBCheck();                                                        // 0x0060b220
    virtual void Prepare();                                           // +0x10
    virtual void Show();                                              // +0x18
};

// ---------------------------------------------------------------------------------------------
// Free functions used by this slice (retail addresses; __cdecl unless noted).
void* __cdecl EAAllocate(uint32_t size, const char* pFile, int a, int b, int c, int d); // 0x00f473a0
void* __cdecl FUN_0067dcc0();                          // 0x0067dcc0 -> cMessageServer*
void* __cdecl FUN_0067cb10();                          // 0x0067cb10 -> cMovieSystem*
void* __cdecl FUN_0067de20();                          // 0x0067de20 -> CheatManager*
void* __cdecl FUN_0067de30();                          // 0x0067de30 -> PropertyManager*
void* __cdecl FUN_0067de40();                          // 0x0067de40 -> Locale manager*
void* __cdecl FUN_0067dcd0();                          // 0x0067dcd0 -> ResourceMan::GetManager
void* __cdecl FUN_00b3d240();                          // 0x00b3d240
void* __cdecl FUN_00b3d300();                          // 0x00b3d300
void* __stdcall FUN_00b3d410(int a, int* pKey, int b);  // 0x00b3d410 (args ignored; returns mgr)
void* __cdecl FUN_00b3d4d0();                          // 0x00b3d4d0
void* __cdecl FUN_00ad7db0();                          // 0x00ad7db0
char  __fastcall FUN_00ad7e20(void* self);             // 0x00ad7e20
struct ModalShim { void SetModal(int a); };            // 0x00ad7e40  thiscall, ret 4
char  __cdecl FUN_00805180();                          // 0x00805180
void* __cdecl FUN_00401090();                          // 0x00401090
char  __cdecl FUN_00e01380();                          // 0x00e01380
struct TrigMgrShim { void Func(int a, int b); };         // 0x00de86d0  ret 8, this in ecx
void  __cdecl FUN_00dea560();                          // 0x00dea560
void  __cdecl FUN_00dea730();                          // 0x00dea730
void  __fastcall FUN_00dea7b0(void* self, void* list); // 0x00dea7b0  ret 4, self in ecx
void* __cdecl FUN_00e00630();                          // 0x00e00630
void* __cdecl FUN_0060b3c0();                          // 0x0060b3c0 -> UI::DBCheck*
void  __cdecl FUN_0060b3e0(DBCheck*);                  // 0x0060b3e0
void  __cdecl FUN_00ae0930();                          // 0x00ae0930
char  __cdecl FUN_006ab760(void*, const wchar_t*);     // 0x006ab760
char  __cdecl FUN_0087da90(LocInfo*, const void*);     // 0x0087da90
char  __cdecl FUN_0087e130(const LocInfo*, LocBuf*);   // 0x0087e130
void  __fastcall FUN_005942e0(void* self);             // 0x005942e0
uint32_t __cdecl FUN_004df420(void*);                  // 0x004df420
void  __fastcall FUN_00b33d20(void* self);             // 0x00b33d20 (tail-jumped, this in ecx)
uint32_t __cdecl FUN_00e3e350(void* self, int a, uint32_t b); // 0x00e3e350
void  __cdecl FUN_00f47380(void* p);                   // 0x00f47380 operator delete[]
void  __fastcall FUN_00deac20(void* self);             // 0x00deac20
void  __fastcall FUN_00deb0b0(void* self);             // 0x00deb0b0
void  __fastcall FUN_00de95a0(void* self);             // 0x00de95a0
void  __fastcall FUN_00deb4a0(void* self);             // 0x00deb4a0
void  __fastcall FUN_00deb6d0(void* self);             // 0x00deb6d0
void  __fastcall FUN_00deb770(void* self, void* param); // 0x00deb770  ret 4
void* __fastcall FUN_00f67d90(void* self);             // 0x00f67d90
void* __cdecl FUN_00810000(void* mem);                 // 0x00810000 cConnectionDialog ctor
void  __cdecl FUN_00807bb0(void* wnd, const void* pRect, int a); // 0x00807bb0 SetWindowImage
void  __cdecl FUN_004df310(void* self, const void* key); // 0x004df310
void* __cdecl FUN_0041ea70(void* pProp);               // 0x0041ea70 GetPropertyAsFloat

extern const uint32_t* const g_kPanelIDs;              // 0x016a1344

// char-array accessors for the module global (it is reached through absolute addresses).
inline uint32_t& PI(uint32_t off) { return *(uint32_t*)((char*)g_kPanelIDs + off); }
inline uint8_t& PIB(uint32_t off)  { return *(uint8_t*)((char*)g_kPanelIDs + off); }
inline void*&   PIP(uint32_t off)  { return *(void**)((char*)g_kPanelIDs + off); }

// ---------------------------------------------------------------------------------------------
// SP::cGalaxyGameEntryImpl (retail; the 2008 PDB records size 0xc0).
struct cGalaxyGameEntryImpl {
    virtual void vf0();                                   // +0x00
    virtual void vf1(); virtual void vf2(); virtual void vf3();
    char pad[8];                   // +0x04..0x0b
    void* mp0c;                    // +0x0c
    uint8_t mb0d;                  // +0x0d
    uint8_t mb0e;                  // +0x0e
    uint8_t mb0f;                  // +0x0f
    uint8_t mb10;                  // +0x10
    uint8_t mb11;                  // +0x11
    uint8_t mb12;                  // +0x12
    uint8_t mb13;                  // +0x13
    cSPUILayout* mp14;             // +0x14
    float mf18;                    // +0x18
    float mf1c;                    // +0x1c
    float mf20;                    // +0x20
    uint8_t mb24;                  // +0x24
    char pad25[3];
    uint32_t mu28;                 // +0x28
    char pad2c[0x20];
    uint32_t mKey4c[3];            // +0x4c
    uint32_t mu58;                 // +0x58
};
void cGalaxyGameEntryImpl_PlayOpeningMovie(cGalaxyGameEntryImpl* self); // 0x00deaad0
void cGalaxyGameEntryImpl_UpdateIntro(cGalaxyGameEntryImpl* self, float dt); // 0x00deacd0

// =============================================================================================
// 0x00dea870  cGalaxyGameEntryAppMode::OnMessage  (this in ecx, 2 dwords, ret 8)
// The app-mode object's only member is +0x0c (the long-lived cGalaxyGameEntryImpl*).
// =============================================================================================
// @ 0x00dea870
bool AppMode_OnMessage(uint8_t* self, uint32_t msgID, uint32_t msgType, int param)
{
    (void)msgType;
    switch (msgID) {
    case 0x61d72de:
        PI(0x1ec) = 3;
        return true;
    case 0x44f1189:
        if (FUN_00b3d4d0() == 0)
            goto ret_true;
        if ((uint32_t)FUN_00ad7db0() != *(uint32_t*)((char*)param + 8))
            goto ret_true;
        ((ModalShim*)FUN_00b3d4d0())->SetModal(1);
        PI(0x1ec) = 6;
        ((cMessageServer*)FUN_0067dcc0())->SendMessage(0x66f8f25, 0, 0, 0);
        if (PIP(0x1ac) != 0) {
            ((cIVisualEffect*)PIP(0x1ac))->Tick(1);
            if (PIP(0x1ac) != 0) {
                cIVisualEffect* e = (cIVisualEffect*)PIP(0x1ac);
                PIP(0x1ac) = 0;
                e->Release();
            }
        }
        goto ret_true;
    case 0x49731ad:
        if (FUN_00b3d4d0() == 0)
            goto ret_true;
        if (PI(0x1ec) == 3) {
            PI(0x1ec) = 4;
            goto ret_true;
        }
        PI(0x1ec) = 5;
        if (PIP(0x15c) != 0) {
            cEffectsWorldSub* w = (cEffectsWorldSub*)PIP(0x15c);
            if (w->Find(0xc19878cd, PIP(0x1ac), 0, 0, 0, 0)) {
                ((cIVisualEffect*)PIP(0x1ac))->Tick(0);
                ((cIVisualEffect*)PIP(0x1ac))->Release();
            }
        }
        FUN_00ae0930();
        goto ret_true;
    case 0x66f6b6f:
        PIB(0x1f4) = 0;
        ((ModalShim*)FUN_00b3d4d0())->SetModal(1);
        PI(0x1ec) = 6;
        ((cMessageServer*)FUN_0067dcc0())->SendMessage(0x66f8f25, 0, 0, 0);
        goto ret_true;
    case 0x67c75bd6:
        *(bool*)(self + 0xe) = (*(uint32_t*)((char*)param + 8) == 1);
        return true;
    case 0x275a9c8c:
        *(bool*)(self + 0x10) = (*(uint32_t*)((char*)param + 8) == 1);
        return true;
    case 0x634297ad:
        *(bool*)(self + 0xf) = (*(uint32_t*)((char*)param + 8) == 1);
        return true;
    case 0xeda117de:
        *(uint32_t*)(self + 0x28) = *(uint32_t*)((char*)param + 8);
        return true;
    case 0x8085c4c:
        *(bool*)(self + 0x12) = true;
        return true;
    default:
        return false;
    }
ret_true:
    return true;
}

// =============================================================================================
// 0x00deaad0  SP::cGalaxyGameEntryImpl::PlayOpeningMovie   (this in ecx)
// A seeded RNG, an AutoRefCount<Effect> from the PropertyManager vtable slot 0x30,
// the movie descriptor seeded from the "UI/Intro" property, the movie entry slot in
// the effects world, and MovieSystem vtable[0x10](entry, &desc).
// =============================================================================================
class cFxMan {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual bool Register(const void* pKey, uint32_t id, void** ppOut); // +0x30
};
class cFxObj {
public:
    virtual void v0();                    // +0x00
    virtual void Release();               // +0x04
    virtual void v2();                    // +0x08
    virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8();
    virtual bool GetProp(uint32_t id, void** ppOut);  // +0x24
};
class cRandomLC {
public:
    void SetSeed(uint32_t s);                          // 0x00936090
    uint32_t RandomUint32Uniform(uint32_t n);          // 0x00a68fb0
};
struct MovieDesc {
    uint32_t mId;      // +0x00
    float    mF0;      // +0x04
    float    mF1;      // +0x08
    float    mF2;      // +0x0c
    float    mF3;      // +0x10
    uint8_t  mB0;      // +0x14
    uint8_t  mB1;      // +0x15
};

// @ 0x00deaad0
void cGalaxyGameEntryImpl_PlayOpeningMovie(cGalaxyGameEntryImpl* self)
{
    (void)self;
    cRandomLC rng;
    rng.SetSeed(0xffffffff);
    cFxObj* pFx = 0;
    cFxMan* pMgr = (cFxMan*)FUN_0067de30();
    if (pFx != 0) {
        cFxObj* dead = pFx;
        pFx = 0;
        dead->Release();
    }
    if (!pMgr->Register(0, 0xeadc458c, (void**)&pFx))
        goto release;
    {
        float fVal;
        cFxObj* pObj = pFx;
        fVal = 0.0f;
        if (pObj != 0) {
            void* pProp = 0;
            if (pObj->GetProp(0x435ba69, (void**)&pProp)) {
                if (*(uint16_t*)((char*)pProp + 0x12) == 0xd)
                    fVal = *(float*)FUN_0041ea70(pProp);
            }
        }
        MovieDesc desc;
        desc.mId = 0;
        desc.mF0 = 0.0f;
        desc.mF1 = 0.0f;
        desc.mF2 = 0.0f;
        desc.mF3 = 0.0f;
        desc.mB0 = 0;
        desc.mB1 = 1;
        uint32_t r = rng.RandomUint32Uniform(0xffffffff);
        desc.mF0 = fVal;
        desc.mF1 = 4.0f;
        *(uint32_t*)((char*)pFx + r * 12 + 4) = 0x376840d7;
        ((cMovieSystem*)FUN_0067cb10())->PlayMovie((void*)((char*)pFx + r * 12), &desc);
    }
release:
    if (pFx != 0)
        pFx->Release();
}


// =============================================================================================
// 0x00deac20  teardown of the app-property list, then PlayOpeningMovie or the reset path.
// this in ecx = the cGalaxyGameEntryImpl whose PlayOpeningMovie is called.
// =============================================================================================
struct AppPropsList {
    virtual void vf0();                 // +0x00
    virtual void Release();             // +0x04
};
struct FlagPair {
    uint8_t  mFlag;      // +0x00
    char     pad1[3];
    void*    mp04;       // +0x04
    uint32_t mId08;      // +0x08
    uint32_t mId0c;      // +0x0c
};

// @ 0x00deac20
void __fastcall FUN_00deac20(cGalaxyGameEntryImpl* self)
{
    AppPropsList* pProps = *(AppPropsList**)0x15fd918;
    FlagPair local;
    AppPropsList* pKeep = pProps;
    local.mFlag = 0;
    local.mp04 = pProps;
    if (pProps != 0)
        pProps->vf0();
    local.mId08 = 0xc14680ef;
    local.mId0c = 0;
    if (pKeep != 0)
        FUN_00dea7b0(&local, pKeep);
    FUN_00dea730();
    if (local.mFlag) {
        cGalaxyGameEntryImpl_PlayOpeningMovie(self);
        PI(0x1ec) = 2;
    } else {
        FUN_00dea560();
        PI(0x1ec) = 6;
        ((cMessageServer*)FUN_0067dcc0())->SendMessage(0x66f8f25, 0, 0, 0);
    }
    if (pKeep != 0) {
        AppPropsList* p = *(AppPropsList**)&local.mp04;
        if (p != 0) {
            p->Release();
        }
    }
}

// =============================================================================================
// 0x00deacd0  intro/camera state machine. this in ecx (the cGalaxyGameEntryImpl), float dt,
// ret 4.  Switch on kGUI+0x200 (1..4, else return).
// =============================================================================================
// @ 0x00deacd0
void __fastcall FUN_00deacd0(cGalaxyGameEntryImpl* self, float dt)
{
    cSPUILayout* ui = self->mp14;
    if (ui == 0)
        return;
    switch (PI(0x200)) {
    case 1: {
        uint8_t step;
        if (FUN_00805180())
            self->mf1c = self->mf1c - dt;
        if (self->mf1c > 0.0f)
            return;
        if (!PIB(0x1f2))
            return;
        PIB(0x1f2) = 0;
        {
            IWindow* w = ui->FindWindowByID(
                *(uint32_t*)((char*)g_kPanelIDs + (self->mb24 + 0x2b) * 12), 1);
            if (w != 0)
                w->PlayAnim(1, self->mb24 != 2);
        }
        if (self->mb24 == 0) {
            IWindow* w = ui->FindWindowByID(0x67763d0, 1);
            w->PlayAnim(1, 1);
        } else if (self->mb24 == 2) {
            IWindow* w = ui->FindWindowByID(0x67763d0, 1);
            w->PlayAnim(1, 0);
        }
        if (self->mb24 == 5)
            PIB(0x1f4) = 1;
        PI(0x200) = 2;
        return;
    }
    case 2: {
        uint8_t step;
        if (PIB(0x1f4)) {
            if (!((cMovieSystem*)FUN_0067cb10())->IsMoviePlaying()) {
                FUN_00dea560();
                PI(0x200) = 0;
            }
        }
        if (FUN_00805180())
            self->mf18 = self->mf18 - dt;
        if (self->mf18 > 0.0f || self->mf18 == 0.0f)
            break;
        step = self->mb24;
        if (step >= 6)
            break;
        if (step != 0) {
            IWindow* w = ui->FindWindowByID(
                *(uint32_t*)((char*)g_kPanelIDs + (step + 0x2b) * 12), 1);
            if (w != 0)
                w->PlayAnim(1, 0);
        }
        if (self->mb24 == 2) {
            self->mb24 = 6;
            PIB(0x1f3) = 1;
        } else {
            self->mb24 = step + 1;
        }
        PI(0x200) = 3;
        return;
    }
    case 3:
        if (self->mf20 > 0.0f && FUN_00805180()) {
            self->mf20 = self->mf20 - dt;
            return;
        }
        PI(0x200) = 4;
        return;
    case 4: {
        uint8_t step;
        if (self->mb24 == 6) {
            if (!((cMovieSystem*)FUN_0067cb10())->IsMoviePlaying()) {
                FUN_00dea560();
                PI(0x200) = 0;
                return;
            }
        }
        step = self->mb24;
        if (step >= 6)
            return;
        self->mf18 = *(float*)((char*)g_kPanelIDs + step * 12 + 0x20c);
        self->mf1c = *(float*)((char*)g_kPanelIDs + step * 12 + 0x208);
        PIB(0x1f2) = 1;
        if (step == 1)
            self->mf20 = 1.0f;
        if (step == 5) {
            IWindow* w = ui->FindWindowByID(0x5bfe3a8, 1);
            if (w != 0)
                w->PlayAnim(1, 0);
            FUN_00deac20(self);
        }
        PI(0x200) = 1;
        return;
    }
    default:
        return;
    }
}

// =============================================================================================
// 0x00deafc0  frame stepper: UpdateIntro(dt), the DBCheck singleton, then the trigger-manager
// time event with the millisecond count. this in ecx, float dt, ret 4.
// =============================================================================================
// @ 0x00deafc0
void __fastcall FUN_00deafc0(cGalaxyGameEntryImpl* self, float dt)
{
    uint32_t oldState;
    FUN_00deacd0(self, dt);
    oldState = PI(0x1ec);
    if (!((cMovieSystem*)FUN_0067cb10())->IsMoviePlaying() && oldState == 6) {
        if (!self->mb11) {
            if (FUN_0060b3c0() == 0) {
                DBCheck* p = (DBCheck*)EAAllocate(0x18, "UI/DBCheck", 0, 0, 0, 0);
                if (p != 0)
                    p->DBCheck::DBCheck();
                p->Prepare();
                FUN_0060b3e0(p);
            }
            ((DBCheck*)FUN_0060b3c0())->Show();
            self->mb11 = 1;
        } else if (self->mb12 && !self->mb13) {
            FUN_00de95a0((void*)g_kPanelIDs);
            self->mb13 = 1;
        }
    }
    {
        void* mgr = FUN_00b3d4d0();
        int ms = (int)(dt * 1000.0f);
        typedef void (__thiscall *FNFire)(void*, int, int);
        ((FNFire)*(void**)(*(char**)mgr + 0x38))((char*)mgr + 4, ms, ms);
    }
}

// =============================================================================================
// 0x00deb0b0  TitleSequence setup: seed the kGUI+0x204 animation table, load UI/SporeTitleSeq,
// pick the intro step by locale, wire the window images and grids. this in ecx, no args.
// =============================================================================================
struct SetWindowImageFn { void* a; uint32_t b; uint32_t c; };
void __cdecl FUN_00807bb0(void* wnd, const void* pRect, int a); // 0x00807bb0 SetWindowImage
void* __cdecl FUN_00810000(void* mem);                          // 0x00810000 cConnectionDialog ctor

// @ 0x00deb0b0
void __fastcall FUN_00deb0b0(cGalaxyGameEntryImpl* self)
{
    // kGUI+0x204..0x248 : 6 x { panelID, float, float }
    *(uint32_t*)((char*)g_kPanelIDs + 0x208) = 0;
    *(uint32_t*)((char*)g_kPanelIDs + 0x20c) = 0x3dcccccd;
    *(uint32_t*)((char*)g_kPanelIDs + 0x204) = 0x670a3f8;
    *(uint32_t*)((char*)g_kPanelIDs + 0x214) = 0;
    *(uint32_t*)((char*)g_kPanelIDs + 0x218) = 0x40833333;
    *(uint32_t*)((char*)g_kPanelIDs + 0x210) = 0x5b82b38;
    *(uint32_t*)((char*)g_kPanelIDs + 0x220) = 0;
    *(uint32_t*)((char*)g_kPanelIDs + 0x224) = 0x3f000000;
    *(uint32_t*)((char*)g_kPanelIDs + 0x21c) = 0x670a3f8;
    *(uint32_t*)((char*)g_kPanelIDs + 0x22c) = 0;
    *(uint32_t*)((char*)g_kPanelIDs + 0x230) = 0x40900000;
    *(uint32_t*)((char*)g_kPanelIDs + 0x228) = 0x5bfdc38;
    *(uint32_t*)((char*)g_kPanelIDs + 0x238) = 0;
    *(uint32_t*)((char*)g_kPanelIDs + 0x23c) = 0x40900000;
    *(uint32_t*)((char*)g_kPanelIDs + 0x234) = 0x5bfdc68;
    *(uint32_t*)((char*)g_kPanelIDs + 0x244) = 0x41280000;
    *(uint32_t*)((char*)g_kPanelIDs + 0x248) = 0x40900000;
    *(uint32_t*)((char*)g_kPanelIDs + 0x240) = 0x66f3c30;

    if (FUN_00e01380())
        ((cSPUIGlobalUI*)PIP(0x184))->SetVisibility(false);

    cSPUILayout* pNew = (cSPUILayout*)EAAllocate(0x18, "UI/SporeTitleSeq", 0, 0, 0, 0);
    if (pNew != 0)
        pNew = (cSPUILayout*)FUN_00810000(pNew);
    cSPUILayout* pOld = self->mp14;
    if (pNew != pOld) {
        if (pNew != 0)
            ((AppPropsList*)pNew)->vf0();
        self->mp14 = pNew;
        if (pOld != 0)
            ((AppPropsList*)pOld)->Release();
    }
    if (self->mp14 != 0)
        self->mp14->Init(L"SporeTitleSeq", 0x40464100, 1, (char)0x5b598fa, 0);

    void* pLoc = FUN_0067de40();
    if (FUN_006ab760(*(void**)(*(char**)pLoc + 0x14), L"zh-cn")) {
        self->mb24 = 3;
        IWindow* w = self->mp14->FindWindowByID(0x5bfe3a8, 1);
        if (w != 0)
            w->PlayAnim(1, 1);
    } else {
        self->mb24 = 5;
    }

    if (self->mp14 != 0) {
        uint32_t step = self->mb24;
        self->mf18 = *(float*)((char*)g_kPanelIDs + step * 12 + 0x20c);
        self->mf1c = *(float*)((char*)g_kPanelIDs + step * 12 + 0x208);
        self->mf20 = 0.0f;
        PIB(0x1f3) = 0;
        PIB(0x1f4) = 0;
        PIB(0x1f2) = 1;
        PI(0x200) = 1;

        SetWindowImageFn img;
        img.a = (void*)0x38f538d6;
        img.b = 0x2f7d0004;
        img.c = 0x8a7be0c0;
        IWindow* w1 = self->mp14->FindWindowByID(0x79035d0, 1);
        if (w1 != 0)
            FUN_00807bb0(w1, &img, -1);
        IWindow* w2 = self->mp14->FindWindowByID(0x79035c8, 1);
        if (w2 != 0)
            FUN_00807bb0(w2, &img, -1);

        if (self->mb24 == 5)
            FUN_00deac20(self);

        if (self->mp14 != 0) {
            LocInfo loc;
            LocBuf buf;
            if (FUN_0087da90(&loc, (const void*)0x15a3cb0)) {
                if (FUN_0087e130(&loc, &buf)) {
                    char c = FUN_006ab760(&buf, L"en-us");
                    if (c != 0) {
                        void* pL = FUN_0067de40();
                        if (FUN_006ab760(*(void**)(*(char**)pL + 0x14), L"en-us")) {
                            IWindow* w3 = self->mp14->FindWindowByID(0x5b8bd48, 1);
                            if (w3 != 0)
                                w3->PlayAnim(1, 1);
                            IWindow* w4 = self->mp14->FindWindowByID(0x66f6ef0, 1);
                            if (w4 != 0)
                                w4->PlayAnim(1, 1);
                        }
                    }
                }
            }
            (void)loc; (void)buf;
        }
    }
}

// =============================================================================================
// 0x00deb4a0  app-mode enter: stop cheats/movies, (un)register the message handlers, reset the
// kGUI state, hide the global UI and the layout. this in ecx = the cGalaxyGameEntryImpl.
// =============================================================================================
struct Screen {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void StopCheats(int);                             // +0x4c
};
class cMovieSystemExt : public cMovieSystem {
public:
};
struct TriggerScreen {
    char pad[0x44];
    void* mp44;
};

// @ 0x00deb4a0
void __fastcall FUN_00deb4a0(cGalaxyGameEntryImpl* self)
{
    void* pCheat = FUN_0067de20();
    if (pCheat != 0)
        ((Screen*)pCheat)->StopCheats(0);
    void* pMovie = FUN_0067cb10();
    if (pMovie != 0)
        ((cMovieSystem*)pMovie)->StopMovies(0);
    void* pMsg = FUN_0067dcc0();
    if (pMsg != 0) {
        cMessageServer* srv = (cMessageServer*)pMsg;
        void* handler = (self != 0) ? (void*)((char*)self + 8) : 0;
        srv->AddHandler(handler, 0x67c75bd6);
        handler = (self != 0) ? (void*)((char*)self + 8) : 0;
        srv->AddHandler(handler, 0x634297ad);
        handler = (self != 0) ? (void*)((char*)self + 8) : 0;
        srv->AddHandler(handler, 0x275a9c8c);
        handler = (self != 0) ? (void*)((char*)self + 8) : 0;
        srv->AddHandler(handler, 0xeda117de);
        handler = (self != 0) ? (void*)((char*)self + 8) : 0;
        srv->AddHandler(handler, 0x8085c4c);
    }
    *(uint8_t*)((char*)self + 0xd) = 0;
    if (PI(0x1ec) == 1)
        FUN_00deb0b0(self);
    ((cSPUIGlobalUI*)PIP(0x184))->SetVisibility(false);
    {
        void* mgr = FUN_00b3d4d0();
        if (FUN_00ad7e20(mgr) == 0)
            ((ModalShim*)FUN_00b3d4d0())->SetModal(1);
    }
    ((cSPUILayout*)((char*)g_kPanelIDs + 0x144))->SetVisibility(false);
}

// =============================================================================================
// 0x00deb5d0  dispatch on *(this+0xc)+0xa8 (the "cell state" dword). this in ecx.
// =============================================================================================
class cTriggerReceiver {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    void PostTriggerSimple();                                 // 0x00e3e350 thiscall, ret 0xc
};
extern uint32_t DAT_01654c01;
extern uint32_t DAT_01654c02;
extern uint32_t DAT_01654c04;
extern uint32_t DAT_01654c05;
// @ 0x00deb5d0
void __fastcall FUN_00deb5d0(void* self)
{
    uint32_t state = *(uint32_t*)(*(char**)((char*)self + 0xc) + 0xa8);
    if (state > 5)
        return;
    switch (state) {
    case 0:
        FUN_00b33d20(FUN_00b3d240());
        return;
    case 1:
        ((cTriggerReceiver*)FUN_00b3d410(1, (int*)&DAT_01654c01, 1))->PostTriggerSimple();
        return;
    case 2:
        ((cTriggerReceiver*)FUN_00b3d410(1, (int*)&DAT_01654c02, 1))->PostTriggerSimple();
        return;
    case 4:
        ((cTriggerReceiver*)FUN_00b3d410(1, (int*)&DAT_01654c04, 1))->PostTriggerSimple();
        return;
    case 5:
        ((cTriggerReceiver*)FUN_00b3d410(1, (int*)&DAT_01654c05, 1))->PostTriggerSimple();
        return;
    default:
        return;
    }
}

// =============================================================================================
// 0x00deb670  cGalaxyGameEntry singleton ctor. this in ecx.
// =============================================================================================
// @ 0x00deb670
void* __fastcall FUN_00deb670(void* self)
{
    FUN_00e00630();
    *(uint32_t*)self = 0x147e3b0;
    *(void**)0x16a1484 = self;
    return self;
}

// =============================================================================================
// 0x00deb6a0  cGalaxyGameEntry destructor (deleting). this in ecx, uint8 flags, ret 4.
// =============================================================================================
// @ 0x00deb6a0
void* __fastcall FUN_00deb6a0(void* self, uint8_t flags)
{
    *(void**)0x16a1484 = 0;
    *(uint32_t*)self = 0x147dba8;
    if (flags & 1)
        FUN_00f47380(self);
    return self;
}

// =============================================================================================
// 0x00deb6d0  message handler: when kGUI+0x108 == 12, clear this+0xc, stop the intro movie
// callback and post the "2" UI event. this in ecx.
// =============================================================================================
struct CbInner {
    virtual void v0();
    virtual void Send(uint32_t id, void* p);     // +0x04
};
struct CbObj {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void Stop();                          // +0x50
};

// @ 0x00deb6d0
void __fastcall FUN_00deb6d0(void* self)
{
    if (PI(0x108) != 0xc)
        return;
    *(uint32_t*)((char*)self + 0xc) = 0;
    if (PIP(0x198) != 0) {
        CbObj* p = (CbObj*)PIP(0x198);
        p->Stop();
        float zeros[3] = {0.0f, 0.0f, 0.0f};
        ((CbInner*)((char*)p + 4))->Send(0x2ca298e9, zeros);
    }
    ((TrigMgrShim*)(void*)g_kPanelIDs)->Func(2, 0);
}

// =============================================================================================
// 0x00deb770  load the avatar part resource key at this+0x4c and apply the species/profile.
// this in ecx = the cGalaxyGameEntryImpl, one stack arg, ret 4.
// =============================================================================================
struct ResourceKey3 { uint32_t m[3]; };
struct ResMgr {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool FindKey(const ResourceKey3* key, void** ppOut, int a, int b, int c, int d); // +0xc
};
struct CellKey { uint32_t mType; uint32_t mRest[3]; };
struct PlayerObj {
    char pad[0x10e8];
    void* mpItems;     // +0x10e8
};
struct TerrainObj {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void UnlockAssociatedParts(void*);                 // +0xc
};
struct CollectItems { void EnsureBaseUnlocks(uint32_t id); };  // 0x00598540

// @ 0x00deb770
void __fastcall FUN_00deb770(void* self, void* unused)
{
    (void)unused;
    void* pOut = 0;
    ResMgr* mgr = (ResMgr*)FUN_0067dcd0();
    if (pOut != 0) {
        pOut = 0;
        ((AppPropsList*)pOut)->Release();
    }
    void* pLocal = 0;
    if (mgr->FindKey((ResourceKey3*)((char*)self + 0x4c), &pLocal, 0, 0, 0, 0)) {
        TerrainObj* terr = (TerrainObj*)FUN_00b3d300();
        PlayerObj* pl = (PlayerObj*)FUN_00f67d90(terr);
        void* arg = 0;
        if (pLocal != 0) {
            typedef uint32_t (__thiscall *FNC)(void*, uint32_t);
            arg = (void*)((FNC)*(void**)(*(char**)pLocal + 0xc))(pLocal, 0x3c609f8);
        }
        ((TerrainObj*)(void*)pl)->UnlockAssociatedParts(arg);
        if (*(uint32_t*)((char*)pl + 0x10e8) != 0) {
            ((CollectItems*)*(void**)((char*)pl + 0x10e8))->EnsureBaseUnlocks(0x465c50ba);
            FUN_005942e0(*(void**)((char*)pl + 0x10e8));
        }
        void* pSpec = FUN_00401090();
        FUN_004df310(pSpec, (ResourceKey3*)((char*)self + 0x4c));
    }
    void* pSpec2 = FUN_00401090();
    *(uint32_t*)((char*)self + 0x48) = FUN_004df420(pSpec2);
    if (pLocal != 0) {
        ((AppPropsList*)pLocal)->Release();
    }
}
