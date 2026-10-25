// Slice s0064bc50 -- cSPUIAssetBrowser launch / update / message handling.
// Module flags: /O2 /MD /Gy /TP /GS-.
#include "types.h"

// Argument block built by Launch for AdvancedLaunch (0x48 bytes).
struct LaunchParams {
    uint32_t f00;
    uint32_t f04, f08, f0c;
    uint8_t  f10, f11, f12, f13, f14;
    uint8_t  pad15[3];
    uint32_t f18, f1c, f20;
    uint8_t  f24;
    uint8_t  pad25[3];
    uint32_t f28;
    uint8_t  f2c;
    uint8_t  pad2d[3];
    uint32_t f30;
    uint32_t f34;
    uint32_t f38;
    uint32_t f3c, f40, f44;
};

extern "C" void __cdecl AdvancedLaunch(LaunchParams* p);   // 0x0064a990

// @ 0x0064bc50
void __cdecl Launch(uint32_t a, uint32_t b, uint32_t c) {
    LaunchParams p;
    p.f04 = 0;
    p.f08 = 0;
    p.f0c = 0;
    p.f10 = 0;
    p.f11 = 0;
    p.f12 = 0;
    p.f14 = 0;
    p.f18 = 0;
    p.f1c = 0;
    p.f20 = 0;
    p.f28 = 0;
    p.f2c = 0;
    p.f3c = 0;
    p.f40 = 0;
    p.f44 = 0;
    p.f00 = a;
    const uint32_t one = 1;
    p.f13 = (uint8_t)one;
    p.f24 = (uint8_t)one;
    p.f34 = one;
    p.f38 = b;
    p.f30 = c;
    AdvancedLaunch(&p);
}

// Target methods are defined below, after the layout declarations.

// ---------------------------------------------------------------------------
// cSPUIAssetBrowser::Update (0x0064c400)
// ---------------------------------------------------------------------------
struct AssetEntry {
    char pad[0x10];
    void* mpObject;
};

struct StopwatchData {
    uint32_t f00, f04, f08, f0c;
};

// Map key stored by asset views (three dwords).
struct AssetKey {
    uint32_t mInstance;   // +0x00
    uint32_t mType;       // +0x04
    uint32_t mGroup;      // +0x08
};

// eastl hashtable<unsigned, ...> iterator and table as seen by its owner.
// The table's fields are at this+0x04 (bucket array) and this+0x08 (count).
struct EaHashIter {
    void* mpNode;         // +0x00 (buckets[count] means "not found")
    void* mpBucket;       // +0x04
};
struct EaMap {
    void* mpAllocator;    // +0x00
    void** mpBuckets;     // +0x04
    uint32_t mBucketCount;// +0x08
    uint32_t mSize;       // +0x0c
    EaHashIter find(const uint32_t& key) const;  // 0x00645ed0
    void** FindOrInsert(const uint32_t& key);    // 0x00646f40
};

struct cSPUIAssetBrowserLayout {
    char pad00[0x14];
    void* mpAnimator;             // +0x14
    void* mpSomething18;          // +0x18
    unsigned char mActive;        // +0x1c
    char pad1d[2];
    unsigned char mField1f;       // +0x1f
    char pad20[0x1c];
    float mTimer;                 // +0x3c
    StopwatchData mStopwatch;     // +0x40
    char pad50[0xc];
    void* mpSomething5c;          // +0x5c
    char pad60[4];
    void* mpSomething64;          // +0x64
    char pad68[0x18];
    void* mpSomething80;          // +0x80
    void* mpSomething84;          // +0x84
    char pad88[0x30];
    void* mpSomethingB8;          // +0xb8
    void* mpSomethingBC;          // +0xbc
    void* mpSomethingC0;          // +0xc0
    char padC4[4];
    void* mpSomethingC8;          // +0xc8
    AssetEntry* mpEntriesBegin;   // +0xcc
    AssetEntry* mpEntriesEnd;     // +0xd0
    AssetEntry* mpEntriesCap;     // +0xd4
    char padD8[0xc];
    AssetKey* mpVec2Begin;        // +0xe4 (key vector)
    AssetKey* mpVec2End;          // +0xe8
    AssetKey* mpVec2Cap;          // +0xec
    char padF0[0x68];
    void* mpSomething158;         // +0x158
    EaMap mMap;                   // +0x15c
    char pad16C[0x10];
    void* mpSomething17c;         // +0x17c
    char pad180[0x20];
    void* mpServer;               // +0x1a0
    void* mpHandler;              // +0x1a4
    uint32_t mMsgId;              // +0x1a8
    unsigned char mField1ac;      // +0x1ac
    char pad1AD[0x1a];
    unsigned char mField1c7;      // +0x1c7
    unsigned char mExpanded;      // +0x1c8
    char pad1C9[0x5f];
    void* mpSomething228;         // +0x228 (= handler's +0x224)
    char pad22C[4];
    int mState230;                // +0x230 (= handler's +0x22c)
    unsigned char mField234;      // +0x234
    char pad235[0x17];
    unsigned char mField24c;      // +0x24c
    char pad24D[1];
    unsigned char mField24e;      // +0x24e

    void* Get_10();                           // 0x00645300
    void Fn_e20(char one);                    // 0x00644e20
    void BanItem();                           // 0x0064b4b0
    void SetVisibility(int a, int b, int c);  // 0x0064a400
    void LaunchEditorEnd();                   // 0x0064acd0
};

typedef void (__fastcall *VCall_Int)(void*, int, int);
typedef void (__fastcall *VCall_IntInt)(void*, int, int, int);
typedef unsigned int (__fastcall *VCall_UInt)(void*);
typedef bool (__fastcall *VCall_Bool_UIntInt)(void*, int, unsigned int, int);
typedef bool (__fastcall *VCall_Bool_UInt)(void*, int, unsigned int);
typedef void (__fastcall *VCall_Ptr)(void*, int, void*);

static void** VTableOf(void* p) { return *(void***)p; }

void __fastcall FUN_00663350(void* self, int, int delta);                 // 0x00663350
void __fastcall FUN_00655ed0(void* self, int, int delta);                 // 0x00655ed0
void __fastcall FUN_010829f0(void* self, int, int delta);                 // 0x010829f0
void __fastcall FUN_007f63b0(void* self);                                 // 0x007f63b0
void* __cdecl FUN_0067cab0(void);                                         // 0x0067cab0
void __fastcall FUN_00801380(void* self);                                 // 0x00801380
void* __cdecl FUN_00401010(void);                                         // 0x00401010
int __cdecl FUN_004e1c30(void* tool, int id, int defaultValue);            // 0x004e1c30
unsigned long long __fastcall FUN_0093a5e0(StopwatchData* self);          // 0x0093a5e0
void __fastcall FUN_0050f740(void* self, int, void* begin, void* end);     // 0x0050f740
void __cdecl FUN_00809db0(void* p, void* message);                        // 0x00809db0
bool __fastcall FUN_006428b0(void* self);                                 // 0x006428b0
bool __fastcall FUN_00642910(void* self);                                 // 0x00642910
void __fastcall FUN_00644040(void* self, int, int value);                 // 0x00644040

// ---- support types for the message / selection methods -------------------
struct SpVector {
    AssetKey* mpBegin;    // +0x00
    AssetKey* mpEnd;      // +0x04
    AssetKey* mpCap;      // +0x08
    void DoInsertKey(AssetKey* pos, const AssetKey* value);  // 0x004e3e10
    AssetKey* Erase(AssetKey* first, AssetKey* last);        // 0x0050f740
};

struct LocaleString {
    void* mpBegin;        // +0x00
    void* mpEnd;          // +0x04
    void* mpCap;          // +0x08
    void Init(const void* name, const uint32_t* id);          // 0x0057ed80
    void Dtor();                                             // 0x00530670
};

struct LocaleMsg2 {
    char pad[0x18];
    void Ctor(int arg);                                      // 0x00666a60
    void Dtor();                                             // 0x00644ff0
};

struct Feed {                                                // object at base+0x228
    char pad[0x50];
    void* mpName;         // +0x50
};

// The message-handler subobject sits four bytes into cSPUIAssetBrowserLayout;
// its field offsets are the base offsets minus 4.
struct cSPUIAssetBrowserModalHandler {
    char pad00[0x3c];
    StopwatchData mStopwatch;     // +0x3c (= base +0x40)
    char pad4c[0x10c];
    EaMap mMap;                   // +0x158 (= base +0x15c)
    char pad168[0xbc];
    void* mpFeed;                 // +0x224 (= base +0x228)
    char pad228[4];
    int mModalState;              // +0x22c (= base +0x230)
    void OnModalWindowEnd(int unused, uint32_t messageId);   // 0x0064bcd0
};

inline cSPUIAssetBrowserLayout* BrowserOf(cSPUIAssetBrowserModalHandler* handler) {
    return (cSPUIAssetBrowserLayout*)((char*)handler - 4);
}

// SP::AssetBrowser singleton (0x401030).
struct BrowserGlobals {
    char pad00[0x1f];
    unsigned char mField1f;   // +0x1f
    char pad20[0x3c];
    void* mpPanel;            // +0x5c
    char pad60[0x20];
    void* mpTarget;           // +0x80
};

struct MsgMgr { void* Find(uint32_t id, int one); };                    // 0x0045ae10
struct AchievementsSystem {
    void AutoTest(uint32_t id, int one);                               // 0x00676e90
};
struct cSPUIAssetVerbs {
    bool IsVerb(int verb);                     // 0x00656740
    void SetSelection(int a, int b, int c);    // 0x006571e0
};
struct Pollinator {
    void UnsubscribeToFeed(void* arg);         // 0x00610810
    void DeleteMyFeed(void* arg);              // 0x006106f0
};

struct AppRuntimeState { char pad[0x118]; int mField118; };
struct AppPropertyList { char pad[0x3c]; AppRuntimeState* mpState; };
extern AppPropertyList* g_AppProperties;       // 0x015fd918

// ---- retail helpers ------------------------------------------------------
void  __fastcall FUN_00801360(void* self);                        // 0x00801360
void* __cdecl AssetBrowser();                                     // 0x00401030
void* __cdecl MessageManager();                                   // 0x00401050
void* __cdecl MessageServer();                                    // 0x0067dcc0
void* __cdecl App();                                              // 0x0067dd10
void* __cdecl AudioSystem();                                      // 0x00a206f0
AchievementsSystem* __cdecl AchievementsController();             // 0x00675250
void  __cdecl RecordEvent2(uint32_t id, uint32_t value);          // 0x00435ed0
bool  __cdecl FUN_004bbe90(uint32_t id);                          // 0x004bbe90
bool  __cdecl FUN_004bbed0(uint32_t id);                          // 0x004bbed0
uint32_t __cdecl FNVHash(const char* text, uint32_t seed, int mode);// 0x00932e80
Pollinator* __cdecl GetPollinator();                              // 0x0067cb30
void  __cdecl OperatorDelete(void* p);                            // 0x00f47380
void  __fastcall StopwatchRestart(StopwatchData* self);           // 0x00571e80

typedef AssetKey* (__fastcall *VCall_Key)(void*);
typedef bool (__fastcall *VCall_Bool_Key)(void*, int, AssetKey*);
typedef bool (__fastcall *VCall_Bool_KeyInt)(void*, int, AssetKey*, int);
typedef bool (__fastcall *VCall_Bool_KeyIdx)(void*, int, AssetKey*, int*);
typedef void (__fastcall *VCall_Msg)(void*, int, uint32_t, void*, int);
typedef bool (__fastcall *VCall_Bool_Ptr)(void*, int, void*);
typedef bool (__fastcall *VCall_Bool_PtrIdx)(void*, int, void*, void*);
typedef bool (__fastcall *VCall_Bool_PtrInt)(void*, int, void*, int);

__forceinline void AutoTestMessage(uint32_t id) {
    if (g_AppProperties->mpState->mField118 == 0)
        AchievementsController()->AutoTest(id, 1);
}

// ===========================================================================
// cSPUIAssetBrowser::OnModalWindowEnd (message-handler subobject at base+4)
// ===========================================================================
// @ 0x0064bcd0
void cSPUIAssetBrowserModalHandler::OnModalWindowEnd(int unused, uint32_t messageId) {
    (void)unused;
    switch (mModalState) {
    case 1: {
        mModalState = 0;
        void* audio = AudioSystem();
        uint32_t value = audio ? ((VCall_UInt)VTableOf(audio)[0x20 / 4])(audio) : 0;
        RecordEvent2(0xe76c9b4f, value);
        if (messageId == 0x5107b1a)
            BrowserOf(this)->BanItem();
        return;
    }
    case 2: {
        mModalState = 0;
        if (messageId != 0x5107b1a)
            return;
        cSPUIAssetBrowserLayout* base = BrowserOf(this);
        if (!base->Get_10())
            return;
        void* view = base->Get_10();
        AssetKey* src = ((VCall_Key)VTableOf(view)[0x40 / 4])(view);
        AssetKey key;
        key.mInstance = src->mInstance;
        key.mType = src->mType;
        key.mGroup = src->mGroup;
        base->Fn_e20(1);
        void* endNode = mMap.mpBuckets[mMap.mBucketCount];
        EaHashIter it = mMap.find(key.mType);
        if (it.mpNode == endNode) {
            void* value = *mMap.FindOrInsert(key.mType);
            if (((VCall_Bool_Key)VTableOf(value)[0xc / 4])(value, 0, &key))
                return;
        }
        FUN_00801360(FUN_0067cab0());
        StopwatchRestart(&mStopwatch);
        void* server = MessageServer();
        ((VCall_Msg)VTableOf(server)[0x14 / 4])(server, 0, 0x2ba2010, &key, 0);
        switch (key.mInstance) {
        case 0x4178b8e8: case 0x372e2c04: case 0x65672ade:
        case 0x9ea3031a: case 0xccc35c46: case 0xdfad9f51:
            AutoTestMessage(0x2e3fc8f2);
            break;
        case 0x72c49181: case 0x4e3f7777: case 0x47c10953:
        case 0xbdd15f3d: case 0x99e92f05:
            AutoTestMessage(0x71c5a637);
            break;
        case 0x2090a11b: case 0x1a4e0708: case 0x1f2a25b6:
        case 0x2a5147a9: case 0x441cd3e6: case 0x449c040f:
        case 0xbc1041e6: case 0x9ad7d4aa: case 0x98e03c0d:
        case 0x7d433fad: case 0x8f963dcb: case 0xc0b74287:
        case 0xc15695da: case 0xf670aa43:
            AutoTestMessage(0xadda228a);
            break;
        default:
            break;
        }
        return;
    }
    case 5: {
        mModalState = 0;
        if (messageId != 0x5107b1a || !mpFeed)
            return;
        LocaleString str;
        LocaleMsg2 msg;
        str.Init(((Feed*)mpFeed)->mpName, &messageId);
        msg.Ctor(0);
        void* server = MessageServer();
        ((VCall_Msg)VTableOf(server)[0x14 / 4])(server, 0, 0xb3d53f95, &msg, 0);
        GetPollinator()->UnsubscribeToFeed(str.mpBegin);
        msg.Dtor();
        str.Dtor();
        return;
    }
    case 6: {
        mModalState = 0;
        if (messageId != 0x5107b1a || !mpFeed)
            return;
        LocaleString str;
        LocaleMsg2 msg;
        str.Init(((Feed*)mpFeed)->mpName, &messageId);
        msg.Ctor(0);
        void* server = MessageServer();
        ((VCall_Msg)VTableOf(server)[0x14 / 4])(server, 0, 0xb3d53f95, &msg, 0);
        GetPollinator()->DeleteMyFeed(str.mpBegin);
        msg.Dtor();
        str.Dtor();
        return;
    }
    case 7:
        mModalState = 0;
        return;
    default:
        return;
    }
}

// ===========================================================================
// Asset-view selection helpers
// ===========================================================================
// @ 0x0064c0d0
void __fastcall sub_64c0d0(cSPUIAssetBrowserLayout* self) {
    AssetKey key;
    key.mInstance = 0;
    key.mType = 0;
    key.mGroup = 0;
    if (self->mpEntriesBegin != self->mpEntriesEnd) {
        if (self->mpEntriesEnd - self->mpEntriesBegin == 1) {
            void* obj = self->mpEntriesBegin[0].mpObject;
            if (obj) {
                AssetKey* src = ((VCall_Key)VTableOf(obj)[0x40 / 4])(obj);
                key.mInstance = src->mInstance;
                key.mType = src->mType;
                key.mGroup = src->mGroup;
            }
        }
    }
    void* endNode = self->mMap.mpBuckets[self->mMap.mBucketCount];
    EaHashIter it = self->mMap.find(key.mType);
    if (it.mpNode != endNode) {
        void* value = *self->mMap.FindOrInsert(key.mType);
        if (((VCall_Bool_KeyInt)VTableOf(value)[8 / 4])(value, 0, &key, 0)) {
            self->SetVisibility(0, 0, 0);
            return;
        }
    }
    self->mField234 = 1;
    BrowserGlobals* browser = (BrowserGlobals*)AssetBrowser();
    if (browser->mpTarget && browser->mpPanel) {
        ((VCall_IntInt)VTableOf(browser->mpTarget)[0x7c / 4])(browser->mpTarget, 0, 1, 1);
        ((VCall_IntInt)VTableOf(browser->mpTarget)[0x7c / 4])(browser->mpTarget, 0, 0x40, 1);
        ((VCall_Ptr)VTableOf(browser->mpPanel)[0xe8 / 4])(browser->mpPanel, 0, browser->mpTarget);
        browser->mField1f = 1;
    }
    void* handle = self->mpSomething17c;
    if (handle) {
        ((VCall_Int)VTableOf(handle)[0xc / 4])(handle, 0, 0);
        handle = self->mpSomething17c;
        if (handle) {
            self->mpSomething17c = 0;
            ((VCall_UInt)VTableOf(handle)[4 / 4])(handle);
        }
    }
    void* item = ((MsgMgr*)MessageManager())->Find(0x4cf52822, 1);
    if (item) {
        ((VCall_UInt)VTableOf(item)[0])(item);
        ((VCall_UInt)VTableOf(item)[4 / 4])(item);
    } else {
        self->LaunchEditorEnd();
    }
}

__declspec(noinline) void __fastcall sub_64c280(cSPUIAssetBrowserLayout* self);
// @ 0x0064c280
void __fastcall sub_64c280(cSPUIAssetBrowserLayout* self) {
    if (self->mField1ac && self->mpSomethingC8 &&
        ((cSPUIAssetVerbs*)self->mpSomethingC8)->IsVerb(2))
        return sub_64c0d0(self);

    void* server = self->mpServer;
    if (!server && !self->mpHandler)
        return;
    if (self->mpEntriesBegin == self->mpEntriesEnd)
        return;

    void* handler = self->mpHandler;
    SpVector keyVec;
    keyVec.mpBegin = 0;
    keyVec.mpEnd = 0;
    keyVec.mpCap = 0;
    for (int i = 0; i < (int)(self->mpEntriesEnd - self->mpEntriesBegin); ++i) {
        void* obj = self->mpEntriesBegin[i].mpObject;
        if (!obj)
            continue;
        AssetKey* src = ((VCall_Key)VTableOf(obj)[0x40 / 4])(obj);
        if (src->mInstance == 0)
            continue;
        if (keyVec.mpEnd < keyVec.mpCap) {
            AssetKey* dst = keyVec.mpEnd;
            keyVec.mpEnd = dst + 1;
            if (dst) {
                dst->mInstance = src->mInstance;
                dst->mType = src->mType;
                dst->mGroup = src->mGroup;
            }
        } else {
            keyVec.DoInsertKey(keyVec.mpEnd, src);
        }
    }
    self->SetVisibility(0, 0, 0);
    if (server) {
        if (keyVec.mpBegin == keyVec.mpEnd) {
            AssetKey empty;
            empty.mInstance = 0;
            empty.mType = 0;
            empty.mGroup = 0;
            ((VCall_Ptr)VTableOf(server)[0])(server, 0, &empty);
        } else {
            ((VCall_Ptr)VTableOf(server)[0])(server, 0, keyVec.mpBegin);
        }
    }
    if (handler)
        ((VCall_Ptr)VTableOf(handler)[0])(handler, 0, &keyVec);
    if (keyVec.mpBegin) {
        uint32_t* header = (uint32_t*)keyVec.mpBegin;
        if (header[-1] != 0)
            OperatorDelete(keyVec.mpBegin);
    }
}


void __fastcall sub_64c400(cSPUIAssetBrowserLayout* self, int, int delta) {
    if (self->mActive) {
        if (self->mpSomethingC0)
            FUN_00663350(self->mpSomethingC0, 0, delta);
        if (self->mpSomethingBC)
            FUN_00655ed0(self->mpSomethingBC, 0, delta);
        if (self->mpSomething158)
            ((VCall_Int)VTableOf(self->mpSomething158)[0x14 / 4])(self->mpSomething158, 0, delta);
        if (self->mpSomethingC8)
            FUN_010829f0(self->mpSomethingC8, 0, delta);
        if (self->mpAnimator)
            FUN_007f63b0(self->mpAnimator);

        if (self->mTimer > 0.0f) {
            volatile float timerValue = self->mTimer;
            volatile float scale = (float)0.001;
            timerValue = timerValue - (float)(unsigned int)delta * scale;
            self->mTimer = timerValue;
            if (timerValue <= 0.0f && self->mpSomething84)
                ((VCall_IntInt)VTableOf(self->mpSomething84)[0x7c / 4])(self->mpSomething84, 0, 1, 0);
        }

        if (self->mExpanded) {
            for (int i = 0; i < (int)(self->mpEntriesEnd - self->mpEntriesBegin); ++i) {
                void* p = self->mpEntriesBegin[i].mpObject;
                if (!p) continue;
                unsigned int value = ((VCall_UInt)VTableOf(p)[0x40 / 4])(p);
                void* q = FUN_00401010();
                if (!((VCall_Bool_UIntInt)VTableOf(q)[0x1c / 4])(q, 0, value, 1)) {
                    q = FUN_00401010();
                    if (((VCall_Bool_UInt)VTableOf(q)[0x3c / 4])(q, 0, value))
                        goto skip_expanded_cleanup;
                }
            }
            {
                FUN_00801380(FUN_0067cab0());
                if (self->mpSomething80 && self->mpSomething5c) {
                    ((VCall_IntInt)VTableOf(self->mpSomething80)[0x7c / 4])(self->mpSomething80, 0, 1, self->mActive);
                    ((VCall_IntInt)VTableOf(self->mpSomething80)[0x7c / 4])(self->mpSomething80, 0, 0x40, 0);
                    if (self->mpSomething64)
                        ((VCall_Ptr)VTableOf(self->mpSomething5c)[0xe8 / 4])(self->mpSomething5c, 0, self->mpSomething64);
                    self->mField1f = 0;
                }
                self->mExpanded = 0;
                FUN_0050f740(&self->mpVec2Begin, 0, self->mpVec2Begin, self->mpVec2End);
                sub_64c280(self);
            }
        skip_expanded_cleanup: ;
        }

        int timeout = 2000;
        if (self->mpSomething18)
            timeout = FUN_004e1c30(self->mpSomething18, 0x91756c5, 2000);
        unsigned long long elapsed = FUN_0093a5e0(&self->mStopwatch);
        if (elapsed > (unsigned long long)(long long)timeout) {
            FUN_00801380(FUN_0067cab0());
            self->mStopwatch.f00 = 0;
            self->mStopwatch.f04 = 0;
            self->mStopwatch.f08 = 0;
            self->mStopwatch.f0c = 0;
            self->mField24e = 0;
            if (self->mpSomething80 && self->mpSomething5c) {
                ((VCall_IntInt)VTableOf(self->mpSomething80)[0x7c / 4])(self->mpSomething80, 0, 1, self->mActive);
                ((VCall_IntInt)VTableOf(self->mpSomething80)[0x7c / 4])(self->mpSomething80, 0, 0x40, 0);
                if (self->mpSomething64)
                    ((VCall_Ptr)VTableOf(self->mpSomething5c)[0xe8 / 4])(self->mpSomething5c, 0, self->mpSomething64);
                self->mField1f = 0;
            }
            FUN_00809db0((char*)self + 4, (void*)0x1525840);
        }
    }

    if (self->mpSomethingB8 && FUN_006428b0(self->mpSomethingB8) && !FUN_00642910(self->mpSomethingB8))
        FUN_00644040(self->mpSomethingB8, 0, 0);
}
// Out-parameter filled by the asset-view tracking vtable slot (dead otherwise).
struct OutKey {
    uint32_t mInstance;   // +0x00
    uint16_t mType;       // +0x04
    uint16_t mGroup;      // +0x06
};

// @ 0x0064c6b0
void __fastcall sub_64c6b0(cSPUIAssetBrowserLayout* self) {
    if (self->mMsgId == 0x54acb9f1) {
        void* app = App();
        if (((VCall_UInt)VTableOf(app)[0x38 / 4])(app) != 0xdbdba1) {
            ((cSPUIAssetVerbs*)self->mpSomethingC8)->SetSelection(0, 0, 0);
            if (self->mpServer || self->mpHandler)
                self->mField24c = 1;
            sub_64c0d0(self);
            return;
        }
    }
    if (self->mField1c7) {
        ((SpVector*)&self->mpVec2Begin)->Erase(self->mpVec2Begin, self->mpVec2End);
        if ((int)(self->mpEntriesEnd - self->mpEntriesBegin) != 0) {
            for (int i = 0; i < (int)(self->mpEntriesEnd - self->mpEntriesBegin); ++i) {
                void* obj = self->mpEntriesBegin[i].mpObject;
                if (!obj)
                    continue;
                AssetKey* src = ((VCall_Key)VTableOf(obj)[0x40 / 4])(obj);
                if (!FUN_004bbe90(src->mType) && !FUN_004bbed0(src->mType))
                    continue;
                OutKey out;
                out.mInstance = FNVHash("AssetBrowser", 0x811c9dc5, 1);
                out.mType = 0x101;
                out.mGroup = 0;
                void* tracker = FUN_00401010();
                if (!((VCall_Bool_Ptr)VTableOf(tracker)[0x18 / 4])(tracker, 0, src)) {
                    if (self->mpVec2End < self->mpVec2Cap) {
                        AssetKey* dst = self->mpVec2End;
                        self->mpVec2End = dst + 1;
                        if (dst) {
                            dst->mInstance = src->mInstance;
                            dst->mType = src->mType;
                            dst->mGroup = src->mGroup;
                        }
                    } else {
                        ((SpVector*)&self->mpVec2Begin)->DoInsertKey(self->mpVec2End, src);
                    }
                }
                void* tracker2 = FUN_00401010();
                if (((VCall_Bool_PtrIdx)VTableOf(tracker2)[0x4c / 4])(tracker2, 0, src, &out)) {
                    void* tracker3 = FUN_00401010();
                    if (!((VCall_Bool_PtrInt)VTableOf(tracker3)[0x1c / 4])(tracker3, 0, src, 1))
                        self->mExpanded = 1;
                }
            }
        }
        if (self->mExpanded) {
            FUN_00801360(FUN_0067cab0());
            if (self->mpSomething80 && self->mpSomething5c) {
                ((VCall_IntInt)VTableOf(self->mpSomething80)[0x7c / 4])(self->mpSomething80, 0, 1, 1);
                ((VCall_IntInt)VTableOf(self->mpSomething80)[0x7c / 4])(self->mpSomething80, 0, 0x40, 1);
                ((VCall_Ptr)VTableOf(self->mpSomething5c)[0xe8 / 4])(self->mpSomething5c, 0, self->mpSomething80);
                self->mField1f = 1;
            }
            return;
        }
    }
    sub_64c280(self);
}
