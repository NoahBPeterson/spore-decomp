// Slice s008143a0 (w2g7 #2), 32-bit MSVC 2008 SP1.
// cSPUIMainWin message/key handling and AutoRefCount vector helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"
#include <stdlib.h>

static inline void** Vtbl(void* o) { return *(void***)o; }

extern "C" void* __cdecl GetManager();
extern "C" void* __cdecl SP_AppSystem();
extern "C" void* __cdecl SP_MovieSystem();

// refcounted element (ILogReporter-ish)
struct Elem {
    virtual void e00(); virtual void e01(); virtual void e02(); virtual void e03();
    virtual void e04(); virtual void e05(); virtual void e06(); virtual void e07();
    virtual void e08(); virtual void e09();
    void OnWindowClosed();   // 0x816990
};

// eastl::vector<AutoRefCount<Elem>> prefix
struct Vec {
    void* mBegin;   // +0
    void* mEnd;     // +4
    void* mCap;     // +8
    void erase(void* first, void* last);
    void Grow(void* pos, void** val);  // 0x814a30
};

void __cdecl CopyImpl(void* first, void* last, void* dst);   // 0x6782c0

struct WinBase { void SetArea(int); };
struct WinSub : WinBase {};

struct MainWin {
    char pad0[0x4];
    WinSub win;                 // +0x4
    char pad1[0x220 - 0x4 - sizeof(WinSub)];
    uint8_t b220;               // +0x220
    uint8_t b221;               // +0x221
    char pad2[0x268 - 0x222];
    void* mp268;                // +0x268
    void* mp26c;                // +0x26c
    char pad3[0x28d - 0x270];
    uint8_t b28d;               // +0x28d
    char pad4[0x2a8 - 0x28e];
    Vec   mVec;                 // +0x2a8

    void OnKeyDown();                  // 0x8143a0
    void MovieToggle();                // 0x8145d0
    bool SaveReadme(int);              // 0x8148b0
    bool KeyHandler2(int a, int key, int mod);  // 0x814d50
    bool HandleMessage(unsigned id, int* msg);  // 0x814e40
    void RemoveElem(int val);          // 0x815310
    void AddElem(Elem* p);             // 0x815370
    void CloseAll();                   // 0x8153e0
};

struct Y2 {
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
    virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
    virtual void a08();
    virtual bool a09(int, int);   // 0x24
    virtual bool a0a(int, int);   // 0x28
};
struct X2 {
    virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
    virtual void b04(); virtual void b05(); virtual void b06(); virtual void b07();
    virtual void b08(); virtual void b09(); virtual void b0a();
    virtual Y2*  b0b();           // 0x2c
    virtual void b0c(); virtual void b0d();
    virtual Y2*  b0e();           // 0x38
};

void* __cdecl FUN_0067de00();
void* __cdecl FUN_0067dd50();
void* __cdecl SP_ConfigManager();
void __cdecl EA_DateTime_Set(int);
int  __cdecl EA_DateTime_GetParameter(void*, int);
void __cdecl WStr_Format(void*, const wchar_t*, ...);
void* __cdecl FUN_00688cd0();

bool __cdecl sOnEnterEscKeys(int, int, int);   // 0x80a310

// @ 0x00814d50
bool MainWin::KeyHandler2(int a, int key, int mod) {
    if (b28d) return true;
    if ((key == 0x1b || key == 0xd) && mod == 0 && sOnEnterEscKeys(a, key, 0)) return true;
    if (key == 0x56) {
        if (mod == 0) { MovieToggle(); return true; }
    } else if (key == 0x70) {
        void* as = SP_AppSystem();
        if (((bool(__thiscall*)(void*))Vtbl(as)[0x54 / 4])(as) && SaveReadme(mod)) return true;
    }
    if (b220) {
        if (mp268) {
            X2* p = (X2*)mp268;
            if (p->b0b()->a09(key, mod)) return true;
        }
        if (mp26c) {
            X2* q = (X2*)mp26c;
            if (q->b0e()->a0a(key, mod)) return true;
        }
    }
    if (key == 0x43 && mod == 0) { OnKeyDown(); return true; }
    return false;
}

// @ 0x00815310
void MainWin::RemoveElem(int val) {
    Vec* v = &mVec;
    Elem** pi = (Elem**)v->mBegin;
    Elem** end = (Elem**)v->mEnd;
    for (; pi != end; ++pi) {
        if ((int)*pi == val) {
            if (pi + 1 < (Elem**)v->mEnd) CopyImpl(pi + 1, v->mEnd, pi);
            v->mEnd = (char*)v->mEnd - 4;
            Elem* last = *(Elem**)v->mEnd;
            if (last) last->e01();
            return;
        }
    }
}

// @ 0x00815370
void MainWin::AddElem(Elem* p) {
    b221 = 0;
    if (p) p->e00();
    Elem* tmp = p;
    if (mVec.mEnd < mVec.mCap) {
        Elem** slot = (Elem**)mVec.mEnd;
        mVec.mEnd = (char*)mVec.mEnd + 4;
        if (slot) {
            *slot = p;
            if (p) p->e00();
        }
    } else {
        mVec.Grow(mVec.mEnd, (void**)&tmp);
    }
    if (tmp) tmp->e01();
}

// @ 0x008153e0
void MainWin::CloseAll() {
    Vec* v = &mVec;
    Elem** i = (Elem**)mVec.mBegin;
    Elem** end = (Elem**)mVec.mEnd;
    for (; i != end; ++i) (*i)->OnWindowClosed();
    v->erase(mVec.mBegin, mVec.mEnd);
}

// ---------------------------------------------------------------------------
// eastl containers / helper objects used by the message handlers
// ---------------------------------------------------------------------------

extern wchar_t gEmptyWStr[];            // 0x01667bac  (L"" sentinel)
extern const wchar_t gSaveNamePrefix[]; // 0x013ec468
extern void* gAppProperties;            // 0x015fd918  (sAppProperties)
extern uint8_t gReadmeEnabled;          // 0x01545198

void operator delete[](void* p);        // 0x00f47380

struct WStr {   // eastl::basic_string<wchar_t, eastl::allocator>
    wchar_t* mpBegin;   // +0x00
    wchar_t* mpEnd;     // +0x04
    wchar_t* mpCap;     // +0x08
    void RangeInitialize(const wchar_t* pSource);             // 0x00579a90
    void Append(const wchar_t* first, const wchar_t* last);   // 0x00429580
    void Assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
};

struct WStr16 {   // eastl::basic_string<wchar_t, fixed_vector_allocator<2,32,2,0,1>>
    wchar_t* mpBegin;        // +0x00
    wchar_t* mpEnd;          // +0x04
    wchar_t* mpCap;          // +0x08
    void*    mpUnused;       // +0x0c
    wchar_t* mpBuffer;       // +0x10  allocator inline-buffer pointer
    wchar_t  mInline[0x20];  // +0x14
    void Construct(const wchar_t* pSource);                   // 0x006743f0
    unsigned Find(wchar_t c, unsigned pos);                   // 0x008364c0
    void Assign(const wchar_t* first, const wchar_t* last);   // 0x00678ee0
    void AssignInline(const wchar_t* first, const wchar_t* last);  // 0x00672750
};

struct WStr16Src {   // substring source (view of a WStr16)
    wchar_t* mpBegin;   // +0x00
    wchar_t* mpEnd;     // +0x04
    wchar_t* mpCap;     // +0x08
    void* StringConstruct(WStr16* pDst, unsigned uIndex);     // 0x008149c0
};

struct CStr {   // eastl::basic_string<char, eastl::allocator>
    char* mpBegin;   // +0x00
    char* mpEnd;     // +0x04
    char* mpCap;     // +0x08
    CStr() : mpBegin((char*)gEmptyWStr), mpEnd((char*)gEmptyWStr), mpCap((char*)gEmptyWStr + 1) {}
    void Destroy();                                             // 0x00530670
    void Assign(const char* first, const char* last);           // 0x00454cb0
    static int Sprintf(CStr* pStr, const char* pFormat, ...);   // 0x00472fe0
};

struct Property {
    char     mPad0[0x12];   // +0x00
    uint16_t mType;         // +0x12
    int*   GetInt();        // 0x0041e990
    bool*  GetBool();       // 0x0041e920
    float* GetFloat();      // 0x0041ea70
};

struct DateTime {
    void Set(int nMode);       // 0x0092e3d0
    int  GetParameter(int n);  // 0x0092df80
};

struct SPcString {
    void Construct();           // 0x006b5060
    void Destroy();             // 0x006b5240
    const wchar_t* GetText();   // 0x006b55c0
};

struct Win280 {
    void Refresh();             // 0x00817cb0
    void Fill(SPcString* pOut); // 0x008175a0
};

struct MovieParams {
    int     mWidth;     // +0x00
    int     mHeight;    // +0x04
    float   mF08;       // +0x08
    float   mF0c;       // +0x0c
    float   mF10;       // +0x10
    uint8_t mB14;       // +0x14
    uint8_t mB15;       // +0x15
    uint8_t mB16;       // +0x16
};

struct MouseMsgData {
    int  mPad0;     // +0x00
    int  mPad1;     // +0x04
    int  mKind;     // +0x08
    int  mCode;     // +0x0c
    char mValue;    // +0x10
};

struct MouseEvent {
    int   mPad0;    // +0x00
    int   mPad1;    // +0x04
    int   mType;    // +0x08
    int   mPad2;    // +0x0c
    float mF10;     // +0x10
    float mF14;     // +0x14
};

struct MouseArg {
    int mPad0;      // +0x00
    int mPad1;      // +0x04
    int mId;        // +0x08
    int mValue;     // +0x0c
    int mValue2;    // +0x10
    int mFlag;      // +0x14
};

struct ResKey3 {
    int mId0;       // +0x00
    int mId1;       // +0x04
    int mId2;       // +0x08
};

struct Variant14 {
    int mData0;     // +0x00
    int mData1;     // +0x04
    int mData2;     // +0x08
    int mPad0c;     // +0x0c
    int mFlags;     // +0x10
};

struct SaveInfo {   // 8 dwords; mData[0] is the default save-name id
    int mData[8];
};

void* __cdecl SP_GetSaveArea(unsigned id);          // 0x006b1f90
bool  __cdecl EA_OpenFile(const wchar_t* pPath);    // 0x00935e60
void* __cdecl EA_Text_GetFontServer(char nServer);  // 0x00885a60
int   __cdecl OpenRecordAsStream(void* key, void* rec, void* stream);  // 0x00808660
void  __cdecl EraseEntry(int handle);               // 0x006861d0

// .rdata wide literals (extern so cl cannot constant-fold their lengths)
extern const wchar_t gReadmeName[];   // 0x014189a0  L"README.txt"
extern const wchar_t gReadmeRel[];    // 0x01418958  L"../../../Spore/SporeApp/README.txt"

static inline bool PropGet(void* pList, unsigned id, void** ppOut) {
    return ((bool(__thiscall*)(void*, unsigned, void**))Vtbl(pList)[0x24 / 4])(pList, id, ppOut);
}

static int StrCmpW(const wchar_t* pA, const wchar_t* pB) {
    for (;;) {
        wchar_t a = *pA, b = *pB;
        if (a != b) return (a < b) ? -1 : 1;
        if (a == 0) return 0;
        ++pA; ++pB;
    }
}

static const wchar_t* StrEndW(const wchar_t* p) { while (*++p) {} return p; }

// @ 0x008143a0
void MainWin::OnKeyDown() {
    void* pTarget = FUN_0067de00();
    if (pTarget == 0) return;

    void* q = FUN_0067dd50();
    SaveInfo info = *(SaveInfo*)((void*(__thiscall*)(void*))Vtbl(q)[0x1c / 4])(q);

    void* pProps = gAppProperties;
    void* pCfg = SP_ConfigManager();
    int nMode = ((int(__thiscall*)(void*, unsigned))Vtbl(pCfg)[0x30 / 4])(pCfg, 0x631621a);

    int nName;
    void* pProp = 0;
    if (nMode != 0) {
        if (pProps != 0) {
            if (PropGet(pProps, 0x46441d2, &pProp) && ((Property*)pProp)->mType == 9)
                nName = *((Property*)pProp)->GetInt();
            else
                nName = info.mData[0];
            PropGet(pProps, 0x46441d3, &pProp);
        } else {
            nName = info.mData[0];
        }
    } else {
        if (pProps != 0) {
            if (PropGet(pProps, 0x473b871, &pProp) && ((Property*)pProp)->mType == 9)
                nName = *((Property*)pProp)->GetInt();
            else
                nName = info.mData[0];
        } else {
            nName = info.mData[0];
        }
    }

    const wchar_t* pPrefix = gSaveNamePrefix;
    void* pArea = SP_GetSaveArea(0x11ac196);
    if (pArea != 0 && ((unsigned(__thiscall*)(void*))Vtbl(pArea)[0x0c / 4])(pArea) == 0x34728492)
        pPrefix = ((const wchar_t*(__thiscall*)(void*))Vtbl(pArea)[0x28 / 4])(pArea);

    CStr text;
    if (*(void**)((char*)this + 0x280) != 0) {
        SPcString cs;
        cs.Construct();
        Win280* pW = (Win280*)*(void**)((char*)this + 0x280);
        pW->Refresh();
        pW->Fill(&cs);
        CStr::Sprintf(&text, "%ls%ls", pPrefix, cs.GetText());
        cs.Destroy();
    } else {
        DateTime dt;
        dt.Set(2);
        CStr::Sprintf(&text, "%lsSpore_%04u-%02u-%02u_%02u-%02u-%02u", pPrefix,
                      dt.GetParameter(1), dt.GetParameter(2), dt.GetParameter(6),
                      dt.GetParameter(8), dt.GetParameter(9), dt.GetParameter(10));
    }

    ((void(__thiscall*)(void*, const char*, unsigned, int, int, int, int))Vtbl(pTarget)[0xa8 / 4])(
        pTarget, text.mpBegin, 0x7d62123, nName, 1, nMode != 0, 1);

    if (text.mpCap - text.mpBegin > 1 && text.mpBegin)
        operator delete[](text.mpBegin);
}

// @ 0x008145d0
void MainWin::MovieToggle() {
    void* movie = SP_MovieSystem();
    if (movie == 0) return;
    if (((bool(__thiscall*)(void*))Vtbl(movie)[0x30 / 4])(movie)) {
        ((void(__thiscall*)(void*))Vtbl(movie)[0x38 / 4])(movie);
        return;
    }

    MovieParams params;
    params.mWidth  = 0x140;
    params.mHeight = 0xf0;
    params.mF08    = 15.0f;
    params.mF0c    = 60.0f;
    params.mF10    = 0.8f;
    params.mB14    = 1;
    params.mB15    = 0;
    params.mB16    = 1;

    void* pProps = gAppProperties;
    if (pProps != 0) {
        void* pProp = 0;
        if (PropGet(pProps, 0x456f975, &pProp) && ((Property*)pProp)->mType == 9)
            params.mWidth = *((Property*)pProp)->GetInt();
        if (PropGet(pProps, 0x456f976, &pProp) && ((Property*)pProp)->mType == 9)
            params.mHeight = *((Property*)pProp)->GetInt();
        if (PropGet(pProps, 0x456f977, &pProp) && ((Property*)pProp)->mType == 0xd)
            params.mF08 = *((Property*)pProp)->GetFloat();
        if (PropGet(pProps, 0x456f978, &pProp) && ((Property*)pProp)->mType == 0xd)
            params.mF10 = *((Property*)pProp)->GetFloat();
        if (PropGet(pProps, 0x456f979, &pProp) && ((Property*)pProp)->mType == 1)
            params.mB14 = (uint8_t)*((Property*)pProp)->GetBool();
        if (PropGet(pProps, 0x456f974, &pProp) && ((Property*)pProp)->mType == 0xd)
            params.mF0c = *((Property*)pProp)->GetFloat();
        if (PropGet(pProps, 0x456f97a, &pProp) && ((Property*)pProp)->mType == 1)
            params.mB15 = (uint8_t)*((Property*)pProp)->GetBool();
    }

    if (*(void**)((char*)this + 0x280) == 0) {
        DateTime dt;
        dt.Set(2);
        WStr name;
        name.mpBegin = gEmptyWStr;
        name.mpEnd   = gEmptyWStr;
        name.mpCap   = gEmptyWStr + 1;
        WStr_Format(&name, L"Spore_%04u-%02u-%02u_%02u-%02u-%02u",
                    dt.GetParameter(1), dt.GetParameter(2), dt.GetParameter(6),
                    dt.GetParameter(8), dt.GetParameter(9), dt.GetParameter(10));
        ((void(__thiscall*)(void*, const wchar_t*, MovieParams*))Vtbl(movie)[0x2c / 4])(
            movie, name.mpBegin, &params);
        if (name.mpCap - name.mpBegin > 1 && name.mpBegin)
            operator delete[](name.mpBegin);
    } else {
        SPcString cs;
        cs.Construct();
        Win280* pW = (Win280*)*(void**)((char*)this + 0x280);
        pW->Refresh();
        pW->Fill(&cs);
        ((void(__thiscall*)(void*, const wchar_t*, MovieParams*))Vtbl(movie)[0x2c / 4])(
            movie, cs.GetText(), &params);
        cs.Destroy();
    }
}

// @ 0x008148b0
bool MainWin::SaveReadme(int mode) {
    if (mode != 0) return false;

    WStr path;
    path.mpBegin = 0;
    path.mpEnd   = 0;
    path.mpCap   = 0;
    path.RangeInitialize((const wchar_t*)FUN_00688cd0());
    path.Append(gReadmeName, StrEndW(gReadmeName));
    if (!EA_OpenFile(path.mpBegin)) {
        const wchar_t* pDir = (const wchar_t*)FUN_00688cd0();
        path.Assign(pDir, pDir + (StrEndW(pDir) - pDir));
        path.Append(gReadmeRel, StrEndW(gReadmeRel));
        EA_OpenFile(path.mpBegin);
    }
    if (path.mpCap - path.mpBegin > 1 && path.mpBegin)
        operator delete[](path.mpBegin);
    return true;
}

// @ 0x008149c0
void* WStr16Src::StringConstruct(WStr16* pDst, unsigned uIndex) {
    wchar_t* pBegin = mpBegin;
    unsigned uCount = (unsigned)(mpEnd - pBegin);

    if (uIndex < uCount) {
        pDst->mpBuffer = pDst->mInline;          // +0x10
        pDst->mpCap    = pDst->mInline + 0x20;   // +0x08
        pDst->mpEnd    = pDst->mInline;          // +0x04
        pDst->mpBegin  = pDst->mInline;          // +0x00
        *pDst->mInline = 0;
        pDst->AssignInline(pBegin, pBegin + uIndex);
    } else {
        pDst->mpBuffer = pDst->mInline;          // +0x10
        pDst->mpCap    = pDst->mInline + 0x20;   // +0x08
        pDst->mpEnd    = pDst->mInline;          // +0x04
        pDst->mpBegin  = pDst->mInline;          // +0x00
        *pDst->mInline = 0;
        pDst->AssignInline(pBegin, mpEnd);
    }
    return pDst;
}

// @ 0x00814b80
void sTextStyleCallback(int n, void** args, void* p) {
    if (n < 2) return;
    if (StrCmpW((const wchar_t*)args[0], L"font") != 0) return;

    int nStyle = (unsigned char)*(char*)p;
    void* pFontServer = EA_Text_GetFontServer(0);

    WStr16 name;
    name.Construct((const wchar_t*)args[1]);

    unsigned uDot = name.Find(L'.', 0);
    if (uDot != (unsigned)-1) {
        WStr16 sub;
        ((WStr16Src*)&name)->StringConstruct(&sub, uDot);
        name.Assign(sub.mpBegin, sub.mpEnd);
        if (sub.mpCap - sub.mpBegin > 1 && sub.mpBegin && sub.mpBegin != sub.mpBuffer)
            operator delete[](sub.mpBegin);
    }

    ResKey3 key;
    key.mId0 = 0;
    key.mId1 = 0;
    key.mId2 = 0;
    int nStream = 0;

    void* pMgr = GetManager();
    ((void(__thiscall*)(void*, ResKey3*, void*, unsigned, unsigned))Vtbl(pMgr)[0x78 / 4])(
        pMgr, &key, (void*)name.mpBegin, 0x27c5cef, 0x248e873);

    int hRec = OpenRecordAsStream((void*)nStyle, &key, &nStream);
    if (hRec == -1) {
        pMgr = GetManager();
        ((void(__thiscall*)(void*, ResKey3*, void*, unsigned, unsigned))Vtbl(pMgr)[0x78 / 4])(
            pMgr, &key, (void*)name.mpBegin, 0x43b1ec5, 0x248e873);
        hRec = OpenRecordAsStream((void*)nStyle, &key, &nStream);
    }
    if (hRec != -1) {
        int r = ((int(__thiscall*)(void*, int, int))Vtbl(pFontServer)[0x2c / 4])(
            pFontServer, nStream, 2);
        if (r >= 1) {
            ((void(__thiscall*)(void*))Vtbl((void*)nStream)[8 / 4])((void*)nStream);
            hRec = -2;
        }
    }
    if (hRec != -2)
        EraseEntry(hRec);

    if (name.mpCap - name.mpBegin > 1 && name.mpBegin && name.mpBegin != name.mpBuffer)
        operator delete[](name.mpBegin);
}

// @ 0x00814e40
bool MainWin::HandleMessage(unsigned id, int* msg) {
    char* self = (char*)this;

    if (id <= 0x1ee1001) {
        if (id == 0x1ee1001) {
            MouseMsgData* pData = (MouseMsgData*)msg[2];
            if (pData->mKind == 5) {
                if (pData->mCode == 1000)       self[0x70] = pData->mValue;
                else if (pData->mCode == 0x3e9) self[0x71] = pData->mValue;
                else if (pData->mCode == 0x3ea) self[0x72] = pData->mValue;
            }
            void* pWin = *(void**)(self + 0x4c);
            if (pWin == 0) return false;
            MouseEvent ev;
            if (!((bool(__thiscall*)(void*, MouseMsgData*, MouseEvent*))0x00812db0)(
                    (void*)(self - 0x214), pData, &ev))
                return false;
            void* pMouse = *(void**)(self + 0x90);
            if (pMouse != 0 && ev.mType == 8)
                ((void(__thiscall*)(void*, float, float))Vtbl(pMouse)[0x38 / 4])(
                    pMouse, ev.mF14, ev.mF10);
            ((void(__thiscall*)(void*, MouseEvent*))Vtbl(pWin)[0x34 / 4])(pWin, &ev);
            return false;
        }
        if (id == 0xf62def) {
            if (msg[6] != 0 || msg[4] != 0) return false;
            if (*(int*)(self + 0x2c) ==
                ((unsigned(__thiscall*)(void*))0x006237a0)(gAppProperties))
                return false;
            ((void(__cdecl*)())0x00813120)();
            *(int*)(self + 0x2c) = ((unsigned(__thiscall*)(void*))0x006237a0)(gAppProperties);
            return false;
        }
        return false;
    }

    if (id > 0x2703c9b) {
        if (id == 0x366b9aa) {
            void* pLayout = *(void**)(self + 0x30);
            ((void(__thiscall*)(void*, unsigned))0x00811ad0)(pLayout, 0);
            pLayout = *(void**)(self + 0x30);
            if (pLayout == 0) return true;
            *(void**)(self + 0x30) = 0;
            ((void(__thiscall*)(void*))Vtbl(pLayout)[8 / 4])(pLayout);
            return true;
        }
        if (id == 0x546bbb8) {
            bool bHasMsg = (msg != 0);
            if (gReadmeEnabled == 0) return false;
            if (((bool(__thiscall*)(void*, unsigned))0x006a25a0)(gAppProperties, 0x387d0a9))
                return false;
            if (!((bool(__thiscall*)(void*, unsigned))0x006a25a0)(gAppProperties, 0x387d0a8)
                && bHasMsg)
                return false;
            void* pLayout = *(void**)(self + 0x68);
            if (pLayout == 0) return false;
            void* pWin = ((void*(__thiscall*)(void*, int, int))0x008105b0)(pLayout, -1, 1);
            if (pWin == 0) return false;
            void* pSub = ((void*(__thiscall*)(void*))Vtbl(pWin)[0x10 / 4])(pWin);
            ((void(__thiscall*)(void*, void*))Vtbl(pSub)[0xe8 / 4])(pSub, pWin);
            ((void(__thiscall*)(void*, int, int))Vtbl(pWin)[0x7c / 4])(pWin, 1, bHasMsg ? 1 : 0);
            return false;
        }
        if (id == 0x61205e6) {
            if (self[0xc8] == 0) return false;
            self[0xc8] = 0;
            void* pObj = (void*)(self - 0x210);
            if (((void*(__thiscall*)(void*))Vtbl(pObj)[0x14 / 4])(pObj) == 0) return false;
            void* pUpd = ((void*(__thiscall*)(void*))Vtbl(pObj)[0x14 / 4])(pObj);
            ((void*(__thiscall*)(void*, void*, bool))0x00959050)(pUpd, 0, false);
            return false;
        }
        return false;
    }

    if (id == 0x2703c9b) {
        void* pMsg14 = ((void*(__thiscall*)(void*))Vtbl((void*)msg)[0x14 / 4])(msg);
        void* pMsg10 = ((void*(__thiscall*)(void*))Vtbl((void*)msg)[0x10 / 4])(msg);
        if (((int(__thiscall*)(void*))Vtbl(pMsg10)[0x10 / 4])(pMsg10) != 1) {
            ((void(__thiscall*)(void*, int))Vtbl(pMsg14)[0x2c / 4])(pMsg14, 2);
            return true;
        }

        CStr str;
        Variant14 var;
        void* pv = ((void*(__thiscall*)(void*, int))Vtbl(pMsg10)[0x1c / 4])(pMsg10, 0);
        Variant14* pv2 = ((Variant14*(__thiscall*)(Variant14*, void*))0x0060d9c0)(&var, pv);
        CStr* ps = ((CStr*(__thiscall*)(Variant14*))0x0060ebf0)(pv2);
        if (ps != &str) str.Assign(ps->mpBegin, ps->mpEnd);
        if (var.mFlags & 4)
            ((void(__thiscall*)(Variant14*, bool))0x0093db80)(&var, false);

        unsigned long ul = strtoul(str.mpBegin, 0, 0);
        void* pWM = ((void*(__cdecl*)())0x0067caa0)();
        if (pWM != 0) {
            void* pWmgr = ((void*(__thiscall*)(void*))Vtbl(pWM)[4 / 4])(pWM);
            if (pWmgr != 0) {
                void* pRec = ((void*(__thiscall*)(void*, unsigned long, unsigned, int))
                              Vtbl(pWmgr)[0xf4 / 4])(pWmgr, ul, 0x8ed27e7a, 1);
                if (pRec != 0) {
                    void* pX = ((void*(__thiscall*)(void*))Vtbl(pRec)[0x10 / 4])(pRec);
                    int v = ((int(__thiscall*)(void*))Vtbl(pX)[0x20 / 4])(pX);
                    MouseArg arg;
                    arg.mId     = 0x287259f6;
                    arg.mValue  = (v != 0) ? v : (int)ul;
                    arg.mValue2 = v;
                    arg.mFlag   = (((unsigned(__thiscall*)(void*))
                                    Vtbl(pRec)[0x2c / 4])(pRec) >> 2) & 1;
                    pX = ((void*(__thiscall*)(void*))Vtbl(pRec)[0x10 / 4])(pRec);
                    ((void(__thiscall*)(void*, MouseArg*))Vtbl(pX)[0x114 / 4])(pX, &arg);
                    ((void(__thiscall*)(void*, int))Vtbl(pMsg14)[0x2c / 4])(pMsg14, 0);
                    str.Destroy();
                    return true;
                }
            }
        }
        if (str.mpCap - str.mpBegin > 1 && str.mpBegin)
            operator delete[](str.mpBegin);
        ((void(__thiscall*)(void*, int))Vtbl(pMsg14)[0x2c / 4])(pMsg14, 2);
        return true;
    }

    switch (id) {
    case 0x1ee1002: {
        void* pMgr = ((void*(__cdecl*)())0x00957f30)();
        ((void(__thiscall*)(void*, int, int))Vtbl(pMgr)[0x4c / 4])(pMgr, 1, 0);
        return false;
    }
    case 0x1ee1003: {
        int v = *(int*)msg[2];
        if ((v & 0x24) != 0 || (((v & 2) != 0) && ((v & 0x10) == 0)))
            ((void(__thiscall*)(void*))0x008131b0)((void*)(self - 0x214));
        return false;
    }
    case 0x1ee1006: {
        uint8_t f = *(uint8_t*)(self + 0xf);
        *(uint8_t*)(self + 0xc) = 1;
        ((void(__thiscall*)(void*, int))0x00813300)((void*)(self - 0x214), f);
        return false;
    }
    case 0x1ee1007:
        *(uint8_t*)(self + 0xc) = 0;
        ((void(__thiscall*)(void*, int))0x00813300)((void*)(self - 0x214), 0);
        return false;
    case 0x1ee100d:
        ((void(__thiscall*)(void*))0x008131b0)((void*)(self - 0x214));
        return false;
    case 0x1ee1010:
    case 0x1ee1011:
        if (self[0xc] == 0) return false;
        ((void(__thiscall*)(void*, int))0x00813300)((void*)(self - 0x214), 0);
        if (self[0xf] == 0) return false;
        ((void(__thiscall*)(void*, int))0x00813300)((void*)(self - 0x214), 1);
        return false;
    default:
        return false;
    }
}
