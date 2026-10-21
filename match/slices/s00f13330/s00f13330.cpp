// Slice s00f13330 -- 0x00f13330 .. 0x00f143c0 (15 functions).
#include <intrin.h>
//
// Simulator::cScenarioRewardUI -- the scenario "reward" (Sporepedia reward) UI window:
// its ctor/dtor (both the primary object and the embedded content-validation-summarizer
// sub-object), the pollinator/networking message handlers, the cSPUILayout bootstrap, and
// the small eastl::fixed_vector<int64_t,32> helper set that the layout code uses.
//
// Flags: /O2 /MD /Gy /TP

typedef unsigned int   uint32_t;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long long uint64_t;

typedef void  (__thiscall *FnV)(void*);
typedef int   (__thiscall *FnI)(void*, int);
typedef void* (__thiscall *FnP)(void*);
typedef void* (__thiscall *FnPI)(void*, int);
typedef void* (__thiscall *FnPII)(void*, int, int);
typedef int   (__thiscall *FnII)(void*, int, int);
typedef int   (__thiscall *FnIII)(void*, int, int, int);
typedef void  (__thiscall *FnVI)(void*, int);
typedef void  (__thiscall *FnVII)(void*, int, int);

// ---------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------
extern char* g_pMagic;                 // 0x016c7aa4

// ---------------------------------------------------------------------------
// externals with real names (addresses masked; declarations set conventions)
// ---------------------------------------------------------------------------
extern "C" void* operator_new(uint32_t size, const char* name, int, int, const char*, int); // 0x00f473a0
extern "C" void  operator_delete(void*);   // 0x00f47380
extern "C" void  EA_Messaging_RemoveHandler(void*, void*, void*, void*, void*); // 0x00571db0

extern "C" void* __fastcall FUN_00e0a390(void*);  // 0x00e0a390  ctor helper on obj+8 (thiscall)
extern "C" void  __fastcall FUN_00e0a400(void*);  // 0x00e0a400  dtor helper on obj+8 (thiscall)
extern "C" void  FUN_00e0a4c0(void*, void*, void*); // 0x00e0a4c0 (self, arg)
extern "C" void* __fastcall eastl_vector_dtor(void*);  // 0x005c7f10  vector<...>::~vector (thiscall)
extern "C" void  FUN_00eadb10(void*, int);   // 0x00eadb10
extern "C" void  FUN_00eed9c0(void*, void*); // 0x00eed9c0
extern "C" void  FUN_00eeda20(void*, void*); // 0x00eeda20
extern "C" void* FUN_0067cb30();             // 0x0067cb30
extern "C" void  FUN_00610cb0(void*, void*, void*); // 0x00610cb0  PostTxn0x18
extern "C" void  FUN_00f12a60(void*);        // 0x00f12a60
extern "C" void  FUN_00f12eb0();             // 0x00f12eb0
extern "C" void* FUN_00607a60();             // 0x00607a60  AuthManager
extern "C" void  FUN_00f46920(void*, void*);// 0x00f46920  cOnlineTab::Shutdown
extern "C" void* EA_ResourceMan_GetManager();  // 0x0067dcd0
extern "C" void  FUN_00f12700(void*, void*);// 0x00f12700
extern "C" void* FUN_00f46b50(void*);        // 0x00f46b50
extern "C" int   FUN_008105b0(void*, int, int); // 0x008105b0  cSPUILayout::FindWindowByID
extern "C" int   FUN_008120d0(void*, void*, int, int); // 0x008120d0  cSPUILayout::Init
extern "C" int   FUN_00810590(void*, int);   // 0x00810590  cSPUILayout::SetVisibility
extern "C" void  FUN_00806e40(void*, int, int); // 0x00806e40  SPUIHelpers::AutoSizeWindowForText
extern "C" void* FUN_00810000(void*);        // 0x00810000  cConnectionDialog ctor
extern "C" void  FUN_005508a0(void*, void**); // 0x005508a0  Meta::FUN_005508a0 (_J ret in edx:eax)
extern "C" void* FUN_0054e530(void*, void*, void*, int); // 0x0054e530  GetServerId
extern "C" void* memmove(void*, const void*, unsigned int);  // msvcr90!memmove
extern "C" void* DoInsertValue(void*, void*, uint32_t);      // 0x011e0744

// 0x00e4b990-adjacent line: 0x00f13330 case message id

// ---------------------------------------------------------------------------
// class: SP::Simulator::cScenarioRewardUI
// ---------------------------------------------------------------------------
struct RewardUI {
    void*    mVtbl;        // +0x00
    void*    mVtbl04;      // +0x04
    void*    mVtbl08;      // +0x08
    uint32_t mField0c;     // +0x0c
    uint32_t mField10;     // +0x10
    uint32_t mField14;     // +0x14
    uint32_t mField18;     // +0x18
    uint32_t mField1c;     // +0x1c
    uint32_t mField20;     // +0x20
    uint32_t mField24;     // +0x24
    uint32_t mField28;     // +0x28
    uint32_t mField2c;     // +0x2c
    uint8_t  mField30[0x70]; // +0x30 .. +0x9f  embedded content-validation summarizer
    uint32_t mFielda0;     // +0xa0
    uint32_t mFielda4;     // +0xa4
    uint32_t mFielda8;     // +0xa8
    uint32_t mFieldac;     // +0xac
    uint32_t mFieldb0;     // +0xb0
    uint32_t mFieldb4;     // +0xb4
    uint32_t mFieldb8;     // +0xb8
    float    mFbc;         // +0xbc
    float    mFc0;         // +0xc0
    float    mFc4;         // +0xc4
    float    mFc8;         // +0xc8
    float    mFcc;         // +0xcc
    uint32_t mFieldd0;     // +0xd0
    uint32_t mFieldd4;     // +0xd4
    uint32_t mFieldd8;     // +0xd8
    uint32_t mFielddc;     // +0xdc
    uint32_t mFielde0;     // +0xe0
    uint32_t mFielde4;     // +0xe4
    uint32_t mFielde8;     // +0xe8
    uint32_t mFieldec;     // +0xec
    uint32_t mFieldf0;     // +0xf0
    uint32_t mFieldf4;     // +0xf4

    int  FUN_00f133d0(uint32_t, int*);
    void FUN_00f139f0();
};

// ===========================================================================
// 0x00f13330 -- message filter: on a specific reward message, refresh the UI.
// ===========================================================================
// @ 0x00f13330
extern "C" uint8_t __stdcall FUN_00f13330(uint32_t msg, int* data)
{
    if (msg != 0x65ff54a)
        return 1;
    if (*(uint32_t*)((char*)data + 0x10) != 0x40464100u)
        return 1;
    uint32_t kind = *(uint32_t*)((char*)data + 0x18);
    if (kind == 0x146f54c || kind == 0x67c078ceu || kind == 0x88f71bcfu)
        FUN_00f12eb0();
    return 1;
}

// ===========================================================================
// 0x00f13370 -- destructor of the content-validation-summarizer sub-object.
// ===========================================================================
// @ 0x00f13370
extern "C" void* __fastcall FUN_00f13370(void* self, int, uint8_t freeFlag)
{
    char* s = (char*)self;
    *(void**)(s + 0x00) = (void*)0x148c09c;
    *(void**)(s + 0x04) = (void*)0x148c08c;
    _ReadWriteBarrier();
    void** p20 = *(void***)(s + 0x20);
    if (p20)
        ((FnV)(*(void***)((char*)p20 + 0x10))[4 / 4])((char*)p20 + 0x10);
    void** p1c = *(void***)(s + 0x1c);
    if (p1c)
        ((FnV)(*(void***)p1c)[4 / 4])(p1c);
    void** p0c = *(void***)(s + 0x0c);
    if (p0c)
        ((FnV)(*(void***)p0c)[8 / 4])(p0c);
    *(void**)(s + 0x04) = (void*)0x13ec458;
    *(void**)(s + 0x00) = (void*)0x13eb938;
    if (freeFlag & 1)
        operator_delete(s);
    return self;
}

// ===========================================================================
// 0x00f133d0 -- pollinator inbound message handler.
// ===========================================================================
// @ 0x00f133d0
int RewardUI::FUN_00f133d0(uint32_t, int* msg)
{
    char* self = (char*)this;

    if (*(int*)((char*)msg + 8) == 1) {
        if (*(int*)((char*)msg + 0x10) != 0x1b)
            return 1;
        uint32_t srv[3];
        srv[0] = 0xffffffffu;
        srv[1] = 0x7fffffffu;
        srv[2] = 0x7fffffffu;
        FUN_00eed9c0(self + 0x10, srv);
        if (srv[2] == 0x7fffffffu)
            srv[2] = 0;
        FUN_00eeda20(self + 0x10, srv);
        FUN_00f12a60(self);
        return 1;
    }

    if (*(int*)((char*)msg + 8) != 0x287259f6)
        return 0;

    uint32_t kind = *(uint32_t*)((char*)msg + 0xc);
    if (kind == 0x5107b1a || kind == 0x7ce91d8) {
        void* am = FUN_0067cb30();
        void* key = (void*)((char*)am + 0x58);
        uint32_t serverId[2];
        FUN_0054e530(key, self + 0x10, serverId, 1);
        void* poll = FUN_0067cb30();
        FUN_00610cb0(poll, (void*)serverId[0], (void*)(kind == 0x5107b1a ? 1u : 0u));
        uint32_t srv[3];
        srv[0] = 0xffffffffu;
        srv[1] = 0x7fffffffu;
        srv[2] = 0x7fffffffu;
        FUN_00eed9c0(self + 0x10, srv);
        srv[2] = (kind == 0x5107b1a) ? 1u : 0xffffffffu;
        FUN_00eeda20(self + 0x10, srv);
        FUN_00f12a60(self);
        return 1;
    }
    if (kind == 0x7737870) {
        uint32_t srv[3];
        srv[0] = 0xffffffffu;
        srv[1] = 0x7fffffffu;
        srv[2] = 0x7fffffffu;
        FUN_00eed9c0(self + 0x10, srv);
        if (srv[2] == 0x7fffffffu)
            srv[2] = 0;
        FUN_00eeda20(self + 0x10, srv);
        FUN_00f12a60(self);
        return 1;
    }
    return 1;
}

// ===========================================================================
// 0x00f135b0 -- reward asset availability check (pollinator request/response).
// ===========================================================================
// @ 0x00f135b0
extern "C" int __fastcall FUN_00f135b0(void* this_, int)
{
    char* self = (char*)this_;
    void** am = (void**)FUN_00607a60();
    if (((FnP)(*(void***)am)[0x24 / 4])(am))
        return 0;
    if (!*(uint32_t*)(g_pMagic + 0xd0))
        return 0;

    char* t = *(char**)(*(char**)(g_pMagic + 0x74) + 0x10);
    uint32_t a = *(uint32_t*)(t + 8);
    uint32_t b = *(uint32_t*)(t + 0x10);

    struct { uint32_t k0; uint32_t k1; uint32_t k2; } key;
    key.k0 = a;
    key.k1 = 0x30bdee3;
    key.k2 = b;
    uint32_t holder = 0;
    uint32_t out = 0;

    void** mgr = (void**)EA_ResourceMan_GetManager();
    uint32_t dummy = 0;
    if (holder) {
        holder = 0;
        ((FnV)(*(void***)holder)[4 / 4])((void*)holder);
    }
    if (!((FnPII)(*(void***)mgr)[0xc / 4])(mgr, (int)&key, (int)&out))
        return 0;
    holder = out;
    void* meta = (void*)((FnPI)(*(void***)holder)[0xc / 4])((void*)holder, 0x30bdee3);
    if (!meta)
        return 0;
    void* idp = ((FnP)(*(void***)meta)[0])(meta);
    uint64_t id = *(uint64_t*)idp;
    if (id == 0xffffffffffffffffull) {
        // release and fail
        if (holder)
            ((FnV)(*(void***)holder)[4 / 4])((void*)holder);
        if (meta)
            ((FnV)(*(void***)meta)[4 / 4])(meta);
        return 0;
    }
    void** am2 = (void**)FUN_00607a60();
    uint64_t myId = 0;
    ((FnP)(*(void***)am2)[0x40 / 4])(am2);
    // compare - returns ecx:edx
    (void)myId;
    (void)dummy;
    if (holder)
        ((FnV)(*(void***)holder)[4 / 4])((void*)holder);
    if (meta)
        ((FnV)(*(void***)meta)[4 / 4])(meta);
    return 0;
}

// ===========================================================================
// 0x00f13810 -- constructor of the reward-UI sub-object.
// ===========================================================================
// @ 0x00f13810
extern "C" void* __fastcall FUN_00f13810(void* self)
{
    char* s = (char*)self;
    *(void**)(s + 0x04) = (void*)0x13ec458;
    *(void**)(s + 0x0c) = (void*)0x14426a0;
    *(uint32_t*)(s + 0x08) = 0;
    *(void**)(s + 0x00) = (void*)0x148c0e4;
    *(void**)(s + 0x04) = (void*)0x148c0d4;
    *(void**)(s + 0x0c) = (void*)0x148c0b8;
    *(uint32_t*)(s + 0x10) = 0;
    *(uint32_t*)(s + 0x14) = 0;
    *(uint32_t*)(s + 0x18) = 0;
    *(uint32_t*)(s + 0x1c) = 0;
    *(uint32_t*)(s + 0x20) = 0;
    *(uint32_t*)(s + 0x24) = 0;
    *(uint32_t*)(s + 0x28) = 0;
    *(uint32_t*)(s + 0x2c) = 0;
    *(uint32_t*)(s + 0x38) = 0;
    *(uint8_t*)(s + 0x3c) = 0;
    *(uint32_t*)(s + 0x40) = 0;
    *(uint8_t*)(s + 0x44) = 0;
    *(uint32_t*)(s + 0x48) = 0;
    *(uint32_t*)(s + 0x4c) = 0;
    *(uint32_t*)(s + 0x50) = 0;
    *(uint32_t*)(s + 0x54) = 0;
    *(uint32_t*)(s + 0x58) = 0;
    return self;
}

// ===========================================================================
// 0x00f13890 -- constructor of the embedded content-validation summarizer.
// ===========================================================================
// @ 0x00f13890
extern "C" void* __fastcall FUN_00f13890(void* self)
{
    char* s = (char*)self;
    *(uint32_t*)(s + 0x04) = 0;
    *(void**)(s + 0x00) = (void*)0x148c0ec;
    FUN_00e0a390(s + 8);
    *(uint32_t*)(s + 0x78) = 0;
    *(uint32_t*)(s + 0x7c) = 0;
    *(uint32_t*)(s + 0x80) = 0;
    return self;
}

// ===========================================================================
// 0x00f138c0 -- destructor of the embedded content-validation summarizer.
// ===========================================================================
// @ 0x00f138c0
extern "C" void __fastcall FUN_00f138c0(void* self)
{
    char* s = (char*)self;
    *(void**)(s + 0x00) = (void*)0x148c0ec;
    eastl_vector_dtor(s + 0x78);
    FUN_00e0a400(s + 8);
    *(void**)(s + 0x00) = (void*)0x13ec458;
}

// ===========================================================================
// 0x00f138f0 -- constructor of cScenarioRewardUI.
// ===========================================================================
// @ 0x00f138f0
extern "C" void* __fastcall FUN_00f138f0(void* self)
{
    char* s = (char*)self;
    *(void**)(s + 0x04) = (void*)0x13eb394;
    *(void**)(s + 0x08) = (void*)0x13ec458;
    *(uint32_t*)(s + 0x0c) = 0;
    *(void**)(s + 0x00) = (void*)0x148c114;
    *(void**)(s + 0x04) = (void*)0x148c10c;
    *(void**)(s + 0x08) = (void*)0x148c0fc;
    *(uint32_t*)(s + 0x10) = 0;
    *(uint32_t*)(s + 0x14) = 0;
    *(uint32_t*)(s + 0x18) = 0;
    *(uint32_t*)(s + 0x1c) = 0;
    *(uint32_t*)(s + 0x20) = 0;
    *(uint32_t*)(s + 0x24) = 0;
    *(uint32_t*)(s + 0x2c) = 0;
    *(void**)(s + 0x28) = (void*)0x148c0ec;
    FUN_00e0a390(s + 0x30);
    *(uint32_t*)(s + 0xa0) = 0;
    *(uint32_t*)(s + 0xa4) = 0;
    *(uint32_t*)(s + 0xa8) = 0;
    *(uint32_t*)(s + 0xb4) = 0;
    *(uint32_t*)(s + 0xb8) = 0;
    *(uint32_t*)(s + 0xd0) = 0;
    *(uint32_t*)(s + 0xd4) = 0;
    *(uint32_t*)(s + 0xd8) = 0;
    *(uint32_t*)(s + 0xbc) = 0;
    *(uint32_t*)(s + 0xc0) = 0;
    *(uint32_t*)(s + 0xc4) = 0;
    *(uint32_t*)(s + 0xc8) = 0;
    *(uint32_t*)(s + 0xcc) = 0;
    *(uint32_t*)(s + 0xdc) = 0;
    *(uint32_t*)(s + 0xe0) = 0;
    *(uint32_t*)(s + 0xe4) = 0;
    *(uint32_t*)(s + 0xe8) = 0;
    *(uint32_t*)(s + 0xec) = 0;
    *(uint32_t*)(s + 0xf0) = 0;
    *(uint32_t*)(s + 0xf4) = 0;
    return self;
}

// ===========================================================================
// 0x00f139f0 -- destructor of cScenarioRewardUI.
// ===========================================================================
// @ 0x00f139f0
void RewardUI::FUN_00f139f0()
{
    char* s = (char*)this;
    *(void**)(s + 0x00) = (void*)0x148c114;
    *(void**)(s + 0x04) = (void*)0x148c10c;
    *(void**)(s + 0x08) = (void*)0x148c0fc;
    _ReadWriteBarrier();

    uint32_t h = *(uint32_t*)(s + 0xe4);
    if (h) {
        *(uint32_t*)(s + 0xe4) = 0;
        EA_Messaging_RemoveHandler((void*)h, *(void**)(s + 0xe8), *(void**)(s + 0xec),
                                   *(void**)(s + 0xf0), *(void**)(s + 0xf4));
    }
    void** p38 = *(void***)(s + 0xe0);
    if (p38)
        ((FnV)(*(void***)p38)[4 / 4])(p38);
    void** p37 = *(void***)(s + 0xdc);
    if (p37)
        ((FnV)(*(void***)p37)[4 / 4])(p37);
    void** p2e = *(void***)(s + 0xb8);
    if (p2e)
        ((FnV)(*(void***)p2e)[4 / 4])(p2e);
    void** p2d = *(void***)(s + 0xb4);
    if (p2d)
        ((FnV)(*(void***)p2d)[4 / 4])(p2d);

    *(void**)(s + 0x28) = (void*)0x148c0ec;
    eastl_vector_dtor(s + 0xa0);
    FUN_00e0a400(s + 0x30);
    *(void**)(s + 0x28) = (void*)0x13ec458;

    void** p9 = *(void***)(s + 0x24);
    if (p9)
        ((FnV)(*(void***)((char*)p9 + 4))[8 / 4])((char*)p9 + 4);
    void** p8 = *(void***)(s + 0x20);
    if (p8)
        ((FnV)(*(void***)p8)[4 / 4])(p8);
    void** p7 = *(void***)(s + 0x1c);
    if (p7)
        ((FnV)(*(void***)p7)[4 / 4])(p7);
    void** p6 = *(void***)(s + 0x18);
    if (p6)
        ((FnV)(*(void***)p6)[8 / 4])(p6);
    void** p4 = *(void***)(s + 0x10);
    if (p4)
        ((FnV)(*(void***)((char*)p4 + 4))[8 / 4])((char*)p4 + 4);

    *(void**)(s + 0x08) = (void*)0x13ec458;
    *(void**)(s + 0x04) = (void*)0x13eb394;
    *(void**)(s + 0x00) = (void*)0x13eb938;
}

// ===========================================================================
// 0x00f13b10 -- build the reward UI layout (windows, sub-tabs, summarizers).
// ===========================================================================
// @ 0x00f13b10
extern "C" int __fastcall FUN_00f13b10(void* self)
{
    char* s = (char*)self;

    // --- create the connection dialog and store at +0x18 ---
    void* nd = operator_new(0x18, "Simulator", 0, 0, 0, 0);
    if (nd)
        nd = FUN_00810000(nd);
    void* oldd = *(void**)(s + 0x18);
    if (nd != oldd) {
        if (nd)
            ((FnV)(*(void***)nd)[4 / 4])(nd);
        *(void**)(s + 0x18) = nd;
        if (oldd)
            ((FnV)(*(void***)oldd)[8 / 4])(oldd);
    }

    if (!FUN_008120d0(*(void**)(s + 0x18), (void*)0x15ad8d8, 1, 0x5b598f7))
        return 1;

    FUN_00810590(*(void**)(s + 0x18), 0);
    {
        void* w = (void*)FUN_008105b0(*(void**)(s + 0x18), -1, 1);
        if (w)
            ((FnVI)(*(void***)w)[0x104 / 4])(w, (int)s);
    }

    static const uint32_t tabIds4[4] = { 0x7c79918, 0x7db8991, 0x7db8990, 0x7c66c00 };
    for (int i = 0; i < 4; ++i) {
        void* w = (void*)FUN_008105b0(*(void**)(s + 0x18), (int)tabIds4[i], 1);
        if (w)
            ((FnVII)(*(void***)w)[0x7c / 4])(w, 1, 0);
    }
    static const uint32_t showIds2[2] = { 0x7e098d0, 0x7e09668 };
    for (int i = 0; i < 2; ++i) {
        void* w = (void*)FUN_008105b0(*(void**)(s + 0x18), (int)showIds2[i], 1);
        if (w)
            ((FnVII)(*(void***)w)[0x7c / 4])(w, 1, 1);
    }

    static const uint32_t pageIds[2] = { 0x7c796d0, 0x7c79820 };
    static const uint32_t subIds[2] = { 0x7c79d78, 0x7e09670 };
    for (int page = 0; page < 2; ++page) {
        void* w = (void*)FUN_008105b0(*(void**)(s + 0x18), (int)pageIds[page], 1);
        if (w)
            ((FnVII)(*(void***)w)[0x7c / 4])(w, 1, 0);
        for (int j = 0; j < 2; ++j) {
            void* sub = (void*)((FnPI)(*(void***)w)[0xf0 / 4])(w, (int)subIds[j]);
            if (sub)
                ((FnVII)(*(void***)sub)[0x7c / 4])(sub, 1, 0);
        }
        void* t1 = (void*)((FnPI)(*(void***)w)[0xf0 / 4])(w, 0x7c79948);
        FUN_00806e40(t1, 0, 0);
        void* t2 = (void*)((FnPI)(*(void***)w)[0xf0 / 4])(w, 0x7c79940);
        FUN_00806e40(t2, 0, 0);
        float* r1 = (float*)((FnP)(*(void***)t1)[0x38 / 4])(t1);
        float* r2 = (float*)((FnP)(*(void***)t2)[0x38 / 4])(t2);
        float arg1 = r1[0] - (r2[2] - r2[0]);
        float arg2 = r2[1];
        ((FnVII)(*(void***)t2)[0x70 / 4])(t2, *(int*)&arg1, *(int*)&arg2);
        void* t3 = (void*)((FnPI)(*(void***)w)[0xf0 / 4])(w, 0x7c79c50);
        FUN_00806e40(t3, 0, 0);
    }

    // --- content-validation summarizer at +0x20 ---
    {
        void* np = operator_new(0xa0, "Simulator", 0, 0, 0, 0);
        if (np)
            np = FUN_00f46b50(np);
        void* oldp = *(void**)(s + 0x20);
        if (np != oldp) {
            if (np)
                ((FnV)(*(void***)np)[0 / 4])(np);
            *(void**)(s + 0x20) = np;
            if (oldp)
                ((FnV)(*(void***)oldp)[4 / 4])(oldp);
        }
    }
    FUN_00f46920(*(void**)(s + 0x20), (void*)FUN_008105b0(*(void**)(s + 0x18), 0x7c7e188, 1));

    // --- cContentValidationSummarizer (0x24 bytes) at +0xb4 ---
    {
        char* np = (char*)operator_new(0x24, "Simulator", 0, 0, 0, 0);
        if (np) {
            *(void**)(np + 0x04) = (void*)0x13ec458;
            *(uint32_t*)(np + 0x08) = 0;
            *(void**)(np + 0x00) = (void*)0x148c09c;
            *(void**)(np + 0x04) = (void*)0x148c08c;
            *(uint32_t*)(np + 0x0c) = 0;
            *(uint32_t*)(np + 0x10) = 0;
            *(uint32_t*)(np + 0x14) = 0;
            *(uint32_t*)(np + 0x18) = 0;
            *(uint32_t*)(np + 0x1c) = 0;
            *(uint32_t*)(np + 0x20) = 0;
        }
        void* oldp = *(void**)(s + 0xb4);
        if (np != oldp) {
            if (np)
                ((FnV)(*(void***)np)[0 / 4])(np);
            *(void**)(s + 0xb4) = np;
            if (oldp)
                ((FnV)(*(void***)oldp)[4 / 4])(oldp);
        }
    }
    FUN_00f12700(*(void**)(s + 0xb4), (void*)FUN_008105b0(*(void**)(s + 0x18), -1, 1));

    // --- reward-UI sub-object (0x5c bytes) at +0x24 ---
    {
        char* np = (char*)operator_new(0x5c, "Simulator", 0, 0, 0, 0);
        if (np) {
            *(void**)(np + 0x04) = (void*)0x13ec458;
            *(uint32_t*)(np + 0x08) = 0;
            *(void**)(np + 0x0c) = (void*)0x14426a0;
            *(void**)(np + 0x00) = (void*)0x148c0e4;
            *(void**)(np + 0x04) = (void*)0x148c0d4;
            *(void**)(np + 0x0c) = (void*)0x148c0b8;
            for (unsigned i = 0x10; i <= 0x2c; i += 4)
                *(uint32_t*)(np + i) = 0;
            *(uint32_t*)(np + 0x38) = 0;
            *(uint8_t*)(np + 0x3c) = 0;
            *(uint32_t*)(np + 0x40) = 0;
            *(uint8_t*)(np + 0x44) = 0;
            *(uint32_t*)(np + 0x48) = 0;
            *(uint32_t*)(np + 0x4c) = 0;
            *(uint32_t*)(np + 0x50) = 0;
            *(uint32_t*)(np + 0x54) = 0;
            *(uint32_t*)(np + 0x58) = 0;
        }
        char* oldp = *(char**)(s + 0x24);
        if (np != oldp) {
            if (np)
                ((FnV)(*(void***)(np + 4))[4 / 4])(np + 4);
            *(void**)(s + 0x24) = np;
            if (oldp)
                ((FnV)(*(void***)(oldp + 4))[8 / 4])(oldp + 4);
        }
    }

    FUN_00e0a4c0((void*)FUN_008105b0(*(void**)(s + 0x18), 0x7c7e1b0, 1), (void*)0x15ad8c0, 0);

    FUN_00f135b0(s, 0);
    {
        void* w = (void*)FUN_008105b0(*(void**)(s + 0x18), 0x7e20437, 1);
        if (w)
            ((FnVII)(*(void***)w)[0x7c / 4])(w, 1, 0);
    }
    return 1;
}

// ===========================================================================
// 0x00f14060 -- copy a linked list of pairs into a flat array.
// ===========================================================================
// @ 0x00f14060
extern "C" void FUN_00f14060(uint32_t* node, uint32_t* end, uint32_t* out)
{
    if (node == end)
        return;
    do {
        *out = node[2];
        out[1] = node[3];
        out += 2;
        node = (uint32_t*)node[0];
    } while (node != end);
}

// ===========================================================================
// 0x00f14090 -- copy a linked list of pairs into a flat array, backwards.
// ===========================================================================
// @ 0x00f14090
extern "C" void FUN_00f14090(uint32_t start, uint32_t* end, uint32_t* out)
{
    if ((uint32_t*)start == end)
        return;
    do {
        start = *(uint32_t*)(start + 4);
        out[-2] = *(uint32_t*)(start + 8);
        out[-1] = *(uint32_t*)(start + 0xc);
        out -= 2;
    } while ((uint32_t*)start != end);
}

// ===========================================================================
// 0x00f140c0 -- destructor of the reward-UI sub-object.
// ===========================================================================
// @ 0x00f140c0
extern "C" void* __fastcall FUN_00f140c0(void* self, int, uint8_t freeFlag)
{
    char* s = (char*)self;
    *(void**)(s + 0x00) = (void*)0x148c0ec;
    eastl_vector_dtor(s + 0x78);
    FUN_00e0a400(s + 8);
    *(void**)(s + 0x00) = (void*)0x13ec458;
    if (freeFlag & 1)
        operator_delete(s);
    return self;
}

// ===========================================================================
// 0x00f14140 -- eastl::fixed_vector<int64_t,32>::DoInsertValue (single).
// ===========================================================================
// @ 0x00f14140
extern "C" void FUN_00f14140(char* self, uint32_t* pos, uint32_t* value)
{
    uint32_t* end = *(uint32_t**)(self + 4);
    uint32_t* cap = *(uint32_t**)(self + 8);
    if (end != cap) {
        uint32_t* src = value;
        if ((uint32_t)pos <= (uint32_t)value && (uint32_t)value < (uint32_t)end)
            src = value + 2;
        if (end) {
            end[0] = end[-2];
            end[1] = end[-1];
        }
        uint32_t n = (uint32_t)((char*)end - 8 - (char*)pos);
        memmove((void*)((char*)end - n), pos, n);
        pos[0] = src[0];
        pos[1] = src[1];
        *(uint32_t**)(self + 4) = end + 2;
        return;
    }
    int count = (int)((char*)end - *(char**)self) >> 3;
    int newCap;
    char* dst;
    if (count == 0) {
        newCap = 1;
    } else {
        newCap = count * 2;
    }
    if (newCap == 0) {
        dst = 0;
    } else {
        dst = (char*)operator_new((uint32_t)(newCap * 8), "Simulator", 0, 0,
                                  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }
    {
        uint32_t n1 = (uint32_t)((char*)pos - *(char**)self);
        char* mid = (char*)DoInsertValue(dst, *(void**)self, n1);
        uint32_t* at = (uint32_t*)(mid + (n1 >> 3) * 8);
        if (at) {
            at[0] = value[0];
            at[1] = value[1];
        }
        uint32_t n2 = (uint32_t)(*(char**)(self + 4) - (char*)pos);
        char* r = (char*)DoInsertValue(at + 2, pos, n2);
        uint32_t* old = *(uint32_t**)self;
        if (old != 0 && old != *(uint32_t**)(self + 0x10))
            operator_delete(old);
        *(char**)self = dst;
        *(char**)(self + 4) = r + (n2 >> 3) * 8;
        *(char**)(self + 8) = dst + newCap * 8;
    }
    return;
}

// ===========================================================================
// 0x00f143c0 -- eastl::fixed_vector<int64_t,32>::insert (range).
// ===========================================================================
// @ 0x00f143c0
extern "C" void FUN_00f143c0(char* self, uint32_t* pos, uint32_t* first, uint32_t* last)
{
    if (first == last)
        return;
    unsigned n = 0;
    for (uint32_t* p = first; p != last; p = (uint32_t*)p[0])
        ++n;
    uint32_t* end = *(uint32_t**)(self + 4);
    unsigned room = (unsigned)((char*)*(uint32_t**)(self + 8) - (char*)end) >> 3;
    if (n > room) {
        unsigned used = (unsigned)((char*)end - *(char**)self) >> 3;
        unsigned grow = used * 2;
        if (used == 0)
            grow = 1;
        unsigned want = n + used;
        if (want > grow)
            grow = want;
        char* dst = grow ? (char*)operator_new(grow * 8, "Simulator", 0, 0,
                          "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        uint32_t n1 = (uint32_t)((char*)pos - *(char**)self);
        char* mid = (char*)DoInsertValue(dst, *(void**)self, n1);
        uint32_t* at = (uint32_t*)(mid + (n1 >> 3) * 8);
        for (uint32_t* p = first; p != last; p = (uint32_t*)p[0]) {
            at[0] = p[2];
            at[1] = p[3];
            at += 2;
        }
        uint32_t n2 = (uint32_t)(*(char**)(self + 4) - (char*)pos);
        char* r = (char*)DoInsertValue(at, pos, n2);
        uint32_t* old = *(uint32_t**)self;
        if (old != 0 && old != *(uint32_t**)(self + 0x10))
            operator_delete(old);
        *(char**)(self + 4) = r + (n2 >> 3) * 8;
        *(char**)self = dst;
        *(char**)(self + 8) = dst + grow * 8;
        return;
    }

    unsigned tail = (unsigned)((char*)end - (char*)pos) >> 3;
    if (n < tail) {
        uint32_t* src = end - n * 2;
        DoInsertValue((void*)end, src, (uint32_t)((char*)end - (char*)src));
        *(char**)(self + 4) += n * 8;
        memmove((void*)((char*)(end - n * 2) - ((char*)src - (char*)pos)), pos, (uint32_t)((char*)src - (char*)pos));
        FUN_00f14060(first, last, pos);
        return;
    }
    uint32_t* mid = first;
    FUN_00eadb10(&mid, (int)tail);
    FUN_00f14060(mid, last, end);
    *(char**)(self + 4) += (n - tail) * 8;
    DoInsertValue(*(void**)(self + 4), pos, (uint32_t)(*(char**)(self + 4) - (char*)pos));
    *(char**)(self + 4) += tail * 8;
    FUN_00f14090((uint32_t)first, mid, (uint32_t*)((char*)pos + tail * 8));
}
