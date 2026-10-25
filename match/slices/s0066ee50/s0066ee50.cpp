// Slice s0066ee50: SP::cSPUILargeAssetView and feed-item helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"

typedef void  (__thiscall *FnVoid)(void*);
typedef void  (__thiscall *FnVoidP)(void*, void*);
typedef void  (__thiscall *FnVoidI)(void*, int);
typedef void  (__thiscall *FnVoidII)(void*, int, int);
typedef int   (__thiscall *FnIntV)(void*);
typedef int   (__thiscall *FnIntIII)(void*, int, int);
typedef char  (__thiscall *FnChrIIP)(void*, int, int, void*);
typedef char  (__thiscall *FnChrIII)(void*, int, int, int);
typedef char  (__thiscall *FnChr6)(void*, void*, int, int, int, int, int);
typedef void* (__thiscall *FnPtrV)(void*);
#define VT(p) (*(void***)(p))

void* __cdecl FUN_0067cb30();                        // 0x0067cb30
void* __cdecl EA_GetManager();                       // 0x0067dcd0
float __cdecl SPUIHelpers_GetElapsedSeconds();       // 0x00805080
void  __cdecl FUN_00808230(void* w, float* v);       // 0x00808230
extern float gF13ef61c;   // 0x013ef61c
extern float gF1485720;   // 0x01485720

struct Dir { unsigned char GetLocalKey(int a, int b, void* key); unsigned char FUN_0054e740(int a, int b); };

// -----------------------------------------------------------------------------
// @ 0x0066f130
// -----------------------------------------------------------------------------
bool __cdecl FUN_0066f130(void* p) {
    if (p) ((FnVoidII)VT(p)[31])(p, 0x1000, 0);
    return false;
}

// -----------------------------------------------------------------------------
// @ 0x0066f1e0
// -----------------------------------------------------------------------------
bool __fastcall FUN_0066f1e0(void* self) {
    int v = *(int*)((char*)self + 0x68);
    if (v != 0 && v != 8) return true;
    return false;
}

// -----------------------------------------------------------------------------
// @ 0x0066f980
// -----------------------------------------------------------------------------
struct LargeView {
    void FUN_0066f980(void* arg);
};

void LargeView::FUN_0066f980(void* arg) {
    (void)arg;
    void** p = (void**)((char*)this + 0xa8);
    int n = 2;
    do {
        void* w = *p;
        if (w) {
            if (((FnIntV)VT(w)[10])(w) & 1) {
                float t = SPUIHelpers_GetElapsedSeconds() * gF13ef61c;
                float v[4];
                v[0] = 0.0f;
                v[1] = 0.0f;
                v[2] = gF1485720;
                v[3] = t;
                FUN_00808230(w, v);
            }
        }
        ++p;
    } while (--n);
}

// -----------------------------------------------------------------------------
// @ 0x0066f150
// -----------------------------------------------------------------------------
bool __cdecl FUN_0066f150(int a, int b) {
    unsigned char key[12];
    *(uint32_t*)&key[0] = 0;
    *(uint32_t*)&key[4] = 0;
    *(uint32_t*)&key[8] = 0;
    void* r = FUN_0067cb30();
    void* dir = *(void**)((char*)r + 0x58);
    bool got = ((Dir*)dir)->GetLocalKey(a, b, key) != 0;
    bool ok = false;
    if (got) {
        void* r2 = FUN_0067cb30();
        void* dir2 = *(void**)((char*)r2 + 0x58);
        if (((Dir*)dir2)->FUN_0054e740(a, b)) {
            ok = true;
        } else {
            void* mgr = EA_GetManager();
            if (((FnChr6)VT(mgr)[3])(mgr, key, 0, 0, 0, 0, 0)) ok = true;
        }
    }
    if (ok) return true;
    return false;
}

typedef void* (__thiscall *FnPtrI)(void*, uint32_t);
typedef unsigned char (__thiscall *FnU8V)(void*);
typedef float (__thiscall *FnFloatV)(void*);
typedef bool (__thiscall *FnBoolI)(void*, uint32_t);

void FUN_0066bf70();      // 0x0066bf70
void FUN_0066c9e0();      // 0x0066c9e0
void FUN_0066d280();      // 0x0066d280
void FUN_010829f0();      // 0x010829f0
float FUN_00a049f0();     // 0x00a049f0
bool FUN_006a25a0();      // 0x006a25a0
void* __cdecl SP_AppSystem();  // 0x0067dd00
extern void* g_15fd918;   // 0x015fd918

struct LargeAssetView {
    char pad00[0x24];
    void* mWinBakingArea;         // +0x24
    char pad28[0x14];
    void* mWinDescription;        // +0x3c
    char pad40[0x8];
    void* mWinBakingForeground;   // +0x48
    char pad4c[0x10];
    void* mWin5c;                 // +0x5c
    char pad60[0x4];
    void* mExpansionPackBrowser;  // +0x64
    char pad68[0x8];
    void* mAssetVerbs;            // +0x70
    void* mAssetData;             // +0x74
    char pad78[0x8];
    void* mRollover;              // +0x80
    char pad84[0x24];
    uint32_t mFlagsA8;            // +0xa8 (mIsLoaded/mIsPlayable/field_aa/mHasResource)
    uint8_t mIsEditable;          // +0xac
    char padAD[3];

    void FUN_0066ee50(void* arg);
};

// @ 0x0066ee50
void LargeAssetView::FUN_0066ee50(void* arg) {
    if (mWin5c)
        ((FnVoidP)VT(mWin5c)[0x1c / 4])(mWin5c, arg);
    if (mExpansionPackBrowser)
        ((FnVoidP)FUN_010829f0)(mExpansionPackBrowser, arg);
    if (mRollover)
        ((FnVoidP)VT(mRollover)[0x1c / 4])(mRollover, arg);

    if (mWinBakingArea && mWinDescription &&
        (((FnU8V)VT(mWinDescription)[0x28 / 4])(mWinDescription) & 1)) {
        float v[4];
        v[3] = SPUIHelpers_GetElapsedSeconds() * gF13ef61c;
        v[0] = 0.0f;
        v[1] = 0.0f;
        v[2] = gF1485720;
        FUN_00808230(mWinBakingArea, v);
        if (!mIsEditable) {
            mIsEditable = 1;
            void* app = SP_AppSystem();
            ((FnVoidI)VT(app)[0x40 / 4])(app, 1);
        }
    } else if (mIsEditable) {
        mIsEditable = 0;
        void* app = SP_AppSystem();
        ((FnVoidI)VT(app)[0x40 / 4])(app, 0);
    }

    if (mWinBakingForeground &&
        (((FnU8V)VT(mWinBakingForeground)[0x28 / 4])(mWinBakingForeground) & 1)) {
        float v[4];
        v[3] = SPUIHelpers_GetElapsedSeconds() * gF13ef61c;
        v[0] = 0.0f;
        v[1] = 0.0f;
        v[2] = gF1485720;
        FUN_00808230(mWinBakingForeground, v);
    }

    if (mAssetData)
        ((FnVoid)FUN_0066bf70)(mAssetData);

    if (mAssetVerbs) {
        void* r = ((FnPtrV)VT(mAssetVerbs)[0x3c / 4])(mAssetVerbs);
        if (r) {
            void* av = mAssetVerbs;
            uint32_t flags = mFlagsA8;
            void* r2 = ((FnPtrI)VT(av)[0x3c / 4])(av, flags);
            float f = ((FnFloatV)FUN_00a049f0)(r2);
            if (f >= 1.0f)
                ((FnVoid)FUN_0066c9e0)((char*)this - 0xc);
        }
    }

    if (((FnBoolI)FUN_006a25a0)(g_15fd918, 0xb4daca6a))
        ((FnVoid)FUN_0066d280)((char*)this - 0xc);
}

// -----------------------------------------------------------------------------
// Additional helpers referenced by the layout/message handlers below.
// -----------------------------------------------------------------------------
typedef void* (__thiscall *FnPtrVI)(void*, int);
typedef unsigned char (__thiscall *FnU8II)(void*, int, int);
typedef char (__thiscall *FnChrII)(void*, int, int);
typedef unsigned char (__thiscall *FnU8P)(void*, void*);
typedef char (__thiscall *FnChrP)(void*, void*);
typedef void (__thiscall *FnVoidIP)(void*, int, void*);
typedef void (__thiscall *FnVoidIII)(void*, int, int, int);
typedef void (__thiscall *FnVoidPII)(void*, void*, int, int);
typedef void (__thiscall *FnVoidII)(void*, int, int);

void* operator_new(unsigned size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void  operator_delete(void* p);                       // 0x00f47380
void* cSPUILayout_ctor(void* self);                   // 0x00810000
bool  cSPUILayout_Init(void* self, const void* key, bool b, int id);  // 0x008120d0
bool  cSPUILayout_SetParentWin(void* self, void* parent, bool b, int id); // 0x008121b0
void  cSPUILayout_SetReloadCallback(void* self, void* cb, void* ctx); // 0x00810090
void  cSPUILargeAssetView_LoadAssetViewLarge(void* self);  // 0x0066daf0
void* cSPUILayout_FindWindowByID(void* self, int id, int b);  // 0x008105b0

typedef void* (__thiscall *FnPtrCtor)(void*);
typedef bool  (__thiscall *FnInitKey)(void*, const void*, bool, int);
typedef bool  (__thiscall *FnSetParent)(void*, void*, bool, int);
typedef void  (__thiscall *FnSetReload)(void*, void*, void*);
typedef void  (__thiscall *FnVoidth)(void*);
typedef void* (__thiscall *FnFindWin)(void*, int, int);
void  SPDemoBuyer_GetSetting3(int* out);              // 0x00401030 GetSetting3
void  GetManager_EA();                                // (unused placeholder)
void  SubscribeToFeed(void* pollinator, const char* tag);  // 0x00610780
void* FUN_0067cb30();                                 // 0x0067cb30 pollinator accessor
void* EA_ResourceMan_GetManager();                    // 0x0067dcd0
unsigned long long FUN_005508a0();                    // 0x005508a0 Meta::GetId
void  eastl_string_ctor(void* self, int a, const char* fmt, ...);  // 0x00472f50
namespace UI { void CalloutMessageBox(void* self, void* fmt); }  // 0x00809db0
void* SP_MessageServer();                             // 0x0067dcc0
void  GenericLocalKey(void);                          // (see Meta)
void  FUN_006108a0(void* a, void* b, void* c);        // 0x006108a0
void  SPUIHelpers_CalloutWithText(void* self, void* text); // 0x00809db0 variant
void* g_15282b4;  // 0x015282b4 callout format
void* g_15282c0;  // 0x015282c0 callout format
void* g_15282cc;  // 0x015282cc callout format
void* g_13fa29c;  // 0x013fa29c "Sporepedia" literal

// -----------------------------------------------------------------------------
// @ 0x0066efe0  InitLayout  (receiver = cSPUILayout* at this+0x18 holder)
// -----------------------------------------------------------------------------
void __fastcall FUN_0066efe0(void* self)
{
    void* layout = (void*)0;
    void* mem = operator_new(0x18, "Sporepedia", 0, 0, 0, 0);
    if (mem) {
        layout = ((FnPtrCtor)cSPUILayout_ctor)(mem);
    } else {
        layout = (void*)0;
    }
    void* old = *(void**)((char*)self + 0x18);
    if (layout != old) {
        if (layout) ((FnVoid)VT(layout)[1])(layout);
        *(void**)((char*)self + 0x18) = layout;
        if (old) ((FnVoid)VT(old)[2])(old);
    }
    int key[3];
    key[0] = 0x794bb81;
    key[1] = 0x510a95b;
    key[2] = *(int*)0x01527e74;
    ((FnInitKey)cSPUILayout_Init)(*(void**)((char*)self + 0x18),
        (const void*)key, true, 0x5b598fa);
    ((FnSetParent)cSPUILayout_SetParentWin)(*(void**)((char*)self + 0x18),
                             *(void**)((char*)self + 0x1c), true, 0x5b598fa);
    ((FnSetReload)cSPUILayout_SetReloadCallback)(*(void**)((char*)self + 0x18),
                                  (void*)0x0066ee30, self);
    ((FnVoidth)cSPUILargeAssetView_LoadAssetViewLarge)(self);
}

// -----------------------------------------------------------------------------
// @ 0x0066f090  OnModalWindowEnd
// -----------------------------------------------------------------------------
bool __fastcall FUN_0066f090(void* self, void* a, int msgId)
{
    (void)a;
    if (msgId != 0x5107b1a) return false;
    if (!FUN_0067cb30()) return false;
    void* w4c = *(void**)((char*)self + 0x4c);
    if (w4c) ((FnVoidII)VT(w4c)[0x7c / 4])(w4c, 1, 1);
    void* w48 = *(void**)((char*)self + 0x48);
    if (w48) ((FnVoidII)VT(w48)[0x7c / 4])(w48, 1, 0);
    if (!*(void**)((char*)self + 0x70)) return false;
    unsigned long long id = FUN_005508a0();
    char text[0xc];
    *(void**)&text[0] = 0; *(void**)&text[4] = 0; *(void**)&text[8] = 0;
    eastl_string_ctor(text, 0x5107b00, "tag:spore.com,2006:user/%I64u", id);
    void* poll = FUN_0067cb30();
    SubscribeToFeed(poll, *(const char**)&text[0]);
    if (*(int*)&text[8] - *(int*)&text[0] > 1 && *(int*)&text[0] != 0)
        operator_delete(*(void**)&text[0]);
    return false;
}

// -----------------------------------------------------------------------------
// @ 0x0066f200  ctor + DoAnimation  (953 B)
// -----------------------------------------------------------------------------
void* FUN_0066f200_getSetting3();                          // 0x00401030 GetSetting3
void  FUN_007f6210(void* anim, void* win, int idx);        // Animator::RemoveAnimation
void* FUN_007f9340(void** a, void** b);                    // pointer swap helper
void* FUN_007f7eb0(float* out, float a, float b, int c);   // SPUICreateAnimationTimerInterpolation
void* FUN_007f7480(void* a, void* b, float* c, void* d);   // build interpolation
void  AnimHolder_Append(void* holder, int a, void* ref, int d);  // 0x007f8fd0
void* FUN_007f7830(void* a, unsigned b, void* cb, void* variant); // AnimRaw builder
void  Animator_AddAnimation(void* anim, void* win, void* ref, int d); // 0x007f8d10
void  EA_Variant_Destruct(void* v, bool b);                // 0x0093db80
extern float gF13eb8c8;                                    // 0x013eb8c8

// AnimHolder append helper (0x007f8fd0) and the anim builder chain are external;
// this reproduces the original control flow (window rect -> element loop -> anim).
void __fastcall FUN_0066f200(void* self, int idA, int idB)
{
    void* win = cSPUILayout_FindWindowByID(self, idA, 1);
    void* iface = win ? ((FnPtrV)VT(win)[0x10 / 4])(win) : (void*)0;

    int settingPtr = (int)FUN_0066f200_getSetting3();
    int settingVal = settingPtr ? *(int*)((char*)settingPtr + 0x14) : 0;

    if (!win || !iface)
        return;

    float rect[4];
    {
        float* rr = (float*)((void* (__thiscall*)(void*))VT(win)[0x38 / 4])(win);
        rect[0] = rr[0]; rect[1] = rr[1]; rect[2] = rr[2]; rect[3] = rr[3];
    }

    void* itA = (void*)0;
    void* itB = (void*)0;
    ((FnVoidP)VT(iface)[0xcc / 4])(iface, &itA);
    ((FnVoidP)VT(iface)[0xd0 / 4])(iface, &itB);
    int* cur = (int*)itA;
    void* endPtr = (*(void* (__thiscall**)(void*, void*))VT(iface)[0xd0 / 4])(iface, &itB);

    if (*(int*)((char*)self + 4) == 0) {
        ((FnVoidP)VT(iface)[0xe8 / 4])(iface, win);
        while (cur != *(int**)endPtr) {
            int off = *(int*)0x01440aec;
            void* elem = (void*)((char*)cur + off);
            if ((char*)cur + off == (char*)win) {
                *(int*)((char*)self + 4) = idB;
                float* er = (float*)((void* (__thiscall*)(void*))VT(elem)[0x38 / 4])(elem);
                *(float*)((char*)self + 8)   = er[0];
                *(float*)((char*)self + 0xc) = er[1];
                *(float*)((char*)self + 0x10) = er[2];
                *(float*)((char*)self + 0x14) = er[3];
                float* er2 = (float*)((void* (__thiscall*)(void*))VT(elem)[0x38 / 4])(elem);
                rect[0] = 0.0f;
                rect[1] = 0.0f;
                rect[2] = er2[2] - er2[0];
                rect[3] = er2[3] - er2[1];
            } else {
                ((FnVoidII)VT(elem)[0x7c / 4])(elem, 1, 0);
            }
            int* next = *(int**)cur;
            void* end2 = (*(void* (__thiscall**)(void*, void*))VT(iface)[0xd0 / 4])(iface, &itB);
            cur = next;
            if (cur == *(int**)end2) break;
        }
    } else {
        while (cur != *(int**)endPtr) {
            int off = *(int*)0x01440aec;
            void* elem = (void*)((char*)cur + off);
            int eid = ((FnIntV)VT(elem)[0x1c / 4])(elem);
            if (eid != idA) {
                ((FnVoidII)VT(elem)[0x7c / 4])(elem, 1, 1);
            } else {
                *(int*)((char*)self + 4) = 0;
                *(float*)((char*)self + 8)   = rect[0];
                *(float*)((char*)self + 0xc) = rect[1];
                *(float*)((char*)self + 0x10) = rect[2];
                *(float*)((char*)self + 0x14) = rect[3];
            }
            int* next = *(int**)cur;
            void* end2 = (*(void* (__thiscall**)(void*, void*))VT(iface)[0xd0 / 4])(iface, &itB);
            cur = next;
            if (cur == *(int**)end2) break;
        }
    }

    if (settingVal) {
        FUN_007f6210((void*)settingVal, win, -1);
        ((FnVoidII)VT(win)[0x7c / 4])(win, 0x1000, 1);

        // Build the entrance-animation chain and register it with the animator.
        void* animHolderA = (void*)0;
        void* animHolderB = (void*)0;
        FUN_007f9340(&animHolderA, &animHolderB);

        float dur = gF13eb8c8;
        float* interp = (float*)FUN_007f7eb0(&dur, SPUIHelpers_GetElapsedSeconds(), dur, 2);
        void* built = FUN_007f7480((void*)((char*)win + 0x0), (void*)animHolderA, interp, (void*)0);
        void* refA = FUN_007f7830((void*)animHolderA, 2, (void*)0x0066f130, (void*)0);
        AnimHolder_Append((void*)0, 0, (void*)refA, 0);
        AnimHolder_Append((void*)0, 0, (void*)built, 0);
        Animator_AddAnimation((void*)settingVal, win, (void*)refA, 0);

        // release the temporary intrusive_ptrs
        EA_Variant_Destruct(&animHolderA, false);
        (void)animHolderB;
    } else {
        ((FnVoidP)VT(win)[0x6c / 4])(win, rect);
    }
}

// -----------------------------------------------------------------------------
// @ 0x0066f5c0  cUIMissionCard::DoMessage (message dispatch, 798 B)
// -----------------------------------------------------------------------------
bool  FUN_0054e460(void* dir, unsigned long long key, void* out);  // cAssetDirectory::GetLocalKey
bool  FUN_0054e740(void* dir, unsigned long long key);             // cAssetDirectory::IsPending
bool  FUN_0054ed50(void* dir, unsigned long long key, int a, int b);
void  FUN_006108a0(void* poll, void* keyLo, void* keyHi);          // pollinator helper
void* FUN_0067de40();                                              // global accessor
void* FUN_00435e90();
void  FUN_00435ed0(unsigned a, unsigned b);

bool __fastcall FUN_0066f5c0(void* self, void* a, void* msg){
    (void)a;
    if (*(int*)((char*)msg + 8) != 0x287259f6) return false;
    int code = *(int*)((char*)msg + 0xc);

    if (code == 0x7c6d3c0) {
        void* p = *(void**)((char*)self + 0x74);
        if (p) {
            unsigned int v = ((FnIntV)VT(p)[0x28 / 4])(p);
            void* server = SP_MessageServer();
            if ((v >> 1) & 1) {
                FUN_00435ed0((unsigned)(unsigned long)FUN_00435e90(), 0xceaee5e8);
                ((FnVoidIII)VT(server)[0x14 / 4])(server, 0x245c58b1, 0, 0);
                ((FnVoidII)VT(*(void**)((char*)self + 0x74))[0x7c / 4])(
                    *(void**)((char*)self + 0x74), 2, 0);
            } else {
                FUN_00435ed0((unsigned)(unsigned long)FUN_00435e90(), 0xceaee5e8);
                ((FnVoidIII)VT(server)[0x14 / 4])(server, 0x9bad1966, 0, 0);
                ((FnVoidII)VT(*(void**)((char*)self + 0x74))[0x7c / 4])(
                    *(void**)((char*)self + 0x74), 2, 1);
            }
            return true;
        }
        return true;
    }

    // Which of the two 0x28-stride slots to use for the asset key pair.
    if (code == 0x7ce7450 || code == 0x7ce7460) {
        int idx = (code != 0x7ce7460);
        int* pm0 = (int*)((char*)self + 0x18 + idx * 0x28);
        int* pm1 = (int*)((char*)self + 0x1c + idx * 0x28);
        void* obj = FUN_0067de40();
        (*(void (__thiscall**)(void*))((char*)*(void**)obj + 0x20))(obj);
        (*(void (__thiscall**)(void*, int, int))((char*)*(void**)obj + 0x34))(obj, *pm0, *pm1);
        UI::CalloutMessageBox((char*)self + 8, g_15282b4);
        *(int*)((char*)self + 0x6c) = idx + 1;
        return true;
    }

    if (code == 0x53d6fe3a) {
        void* server = SP_MessageServer();
        ((FnVoidP)VT(server)[0x14 / 4])(server, (char*)self + 0x48);
        return true;
    }
    if (code == 0x53d6fe4a) {
        void* server = SP_MessageServer();
        ((FnVoidP)VT(server)[0x14 / 4])(server, (char*)self + 0x20);
        return true;
    }

    // Remaining codes form an asset-key pair lookup + subscribe/load flow.
    if (code == 0xeebd36a1 || code == 0xe5a99ed4 ||
        code == 0xe9079479 || code == 0xb014f74c) {
        int idx = (code == 0xe5a99ed4);
        int kLo = *(int*)((char*)self + 0x18 + idx * 0x28);
        int kHi = *(int*)((char*)self + 0x1c + idx * 0x28);
        if ((kLo & kHi) == -1) return false;

        unsigned char key[0xc];
        *(int*)&key[0] = 0; *(int*)&key[4] = 0; *(int*)&key[8] = 0;
        void* r = FUN_0067cb30();
        unsigned long long k64 = ((unsigned long long)(unsigned)kHi << 32) | (unsigned)kLo;
        bool got = FUN_0054e460(*(void**)((char*)r + 0x58), k64, key);
        if (!got) return false;

        if (code == 0xe5a99ed4 || code == 0xeebd36a1) {
            void* mgr = EA_ResourceMan_GetManager();
            bool ok = ((FnChrP)VT(mgr)[0xc / 4])(mgr, key);
            if (!ok) return false;
            void* server = SP_MessageServer();
            ((FnVoidPII)VT(server)[0x14 / 4])(server, (void*)0x7a43c598, 0, 0);
            return false;
        }

        // b014f74c / e9079479: pending-check + local-key flow
        bool pending = FUN_0054e740(*(void**)((char*)FUN_0067cb30() + 0x58), k64);
        if (!pending) {
            void* mgr = EA_ResourceMan_GetManager();
            bool ok = ((FnChrP)VT(mgr)[0xc / 4])(mgr, key);
            if (!ok) {
                void* d = FUN_0067cb30();
                FUN_0054ed50(*(void**)((char*)d + 0x58), k64, 1, 0);
                FUN_006108a0(FUN_0067cb30(), (void*)(long)kLo, (void*)(long)kHi);
                return false;
            }
            UI::CalloutMessageBox(0, g_15282cc);
            return false;
        }
        FUN_006108a0(FUN_0067cb30(), (void*)(long)kLo, (void*)(long)kHi);
        return false;
    }

    return false;
}

// -----------------------------------------------------------------------------
// @ 0x0066f8e0  two-slot rollover refresh
// -----------------------------------------------------------------------------
bool __fastcall FUN_0066f8e0(void* self, char on, int b, int a, int keyLo)
{
    (void)b;
    void** slot = (void**)((char*)self + 0xb0);
    int*   idp  = (int*)((char*)self + 0x20);
    for (int i = 2; i != 0; --i, ++slot, idp += 10) {
        if (idp[0] == a && idp[1] == keyLo) {
            void* w1 = slot[-2];
            if (w1) ((FnVoidII)VT(w1)[0x7c / 4])(w1, 1, 0);
            if (on == 0) {
                void* w2 = slot[-4];
                if (w2) ((FnVoidII)VT(w2)[0x7c / 4])(w2, 1, 1);
                UI::CalloutMessageBox(0, g_15282c0);
            } else {
                void* w3 = slot[0];
                if (w3) ((FnVoidII)VT(w3)[0x7c / 4])(w3, 1, 1);
                void* server = SP_MessageServer();
                ((FnVoidIII)VT(server)[0x14 / 4])(server, 0x53dd093, 0, 0);
            }
        }
    }
    return true;
}
