// slice s00645620: cSPUIAssetBrowser dialog/publish helpers.
#include "../s00636320/s00636320.h"
#include <string.h>

// --- reference-counted element types (0x14-byte element) ---
struct cBase0 { virtual void b0(); char pad[0xc]; };              // size 0x10
struct cRefCountA { virtual void AddRef(); virtual void Release(); };        // slots 0,1 at +0
struct cRefCountB { virtual void AddRef(); virtual void Release(); };        // slots 0,1 at +0x10
struct cRefB : cBase0, cRefCountB {};                             // refcount base at +0x10
struct Elem {
    uint32_t a, b, c;   // +0x00
    cRefCountA* p;      // +0x0C
    cRefB*      q;      // +0x10
};

// --- external helpers ---
void* PropertyManager();                          // 0x0067de30
void* GetPropertyAsKeyInstance(void* prop, unsigned key, void* out);  // 0x006a12a0
void* GetPropertyAsKey(void* prop, unsigned key, void* out);   // 0x006a1250
void* GetPropertyAsText(void* prop, unsigned key, void* out);  // 0x006a1360
void  SPDemoBuyer_SetModelName(void* model);          // 0x005cd130
namespace UI { void CalloutMessageBox(void* self, void* fmt); }  // 0x00809db0
int   eastl_hashtable_find(void* table, void* key);   // 0x00645ed0
void* operator_new(unsigned size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void  AssetDiscovery_View_ctor(void* self);           // 0x00657f70
int   CheatManagerGetBool(void* prop);                // cProperty::GetBool 0x0041e920
unsigned char* CheatManagerGetBoolPtr(void* prop);    // cProperty::GetBool (returns bool*)
void  cSPUIAssetGrid_Clear(void* self);               // 0x006543a0
void  FUN_0064e670(bool v);                           // 0x0064e670
void* cSPUILayout_FindWindowByID(void* self, int id, int a);  // 0x008105b0
void  cSPUIAssetBrowser_SetCallToActionMessage(void* self, void* text);  // 0x006455b0
void  FUN_006628d0(void* self);                       // 0x006628d0
void  FUN_00663860(char* a, void* b, int c, int d, void* e);  // 0x00663860
void  FUN_0064f2d0(bool v);                           // 0x0064f2d0
void  FUN_0064f2f0(bool v);                           // 0x0064f2f0
void* FUN_0066a5e0(int a, int b);                     // 0x0066a5e0
void* FUN_0066a800(int i);                            // 0x0066a800
void* cString_ctor(void* self);                       // 0x006b5060
void  cString_dtor(void* self);                       // 0x006b5240
void* cString_GetText(void* self);                    // 0x006b55c0
extern "C" unsigned char g_banPropertyKeys[];         // 0x01400480
extern "C" unsigned char g_sAppProperties[];          // 0x015fd918

struct cAssetBrowser2 { int FUN_00645cc0(); };   // 0x00645CC0
cAssetBrowser2* GetAssetBrowser2();              // 0x00401030

struct IAuthMgr {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4();
    virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8();
    virtual bool a9();                               // +0x24
    virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14();
    virtual void a15(); virtual void a16();
    virtual void a17();                              // +0x44
    virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21();
    virtual bool a22();                              // +0x58
};
IAuthMgr* GetAuthMgr();                              // 0x00607A60

struct cSPUIAssetBrowser {
    char pad04[0x24];
    bool mFlag24;              // +0x024
    bool mFlag25;              // +0x025
    bool mFlag26;              // +0x026 (texture preload changed)
    bool mFlag27;              // +0x027 (asset id changed)
    char pad29[0x29 - 0x28];
    bool mFlag29;              // +0x029
    char pad58[0x58 - 0x2a];
    void* mpLayout;            // +0x058 cSPUILayout
    char pad68[0x68 - 0x5c];
    void* mp68;                // +0x068
    void* mp6c;                // +0x06C
    char pad0bc[0xbc - 0x70];
    void* mp0bc;               // +0x0BC asset grid / view context
    void* mp0c0;               // +0x0C0 feed list
    char pad0cc[0xcc - 0xc4];
    Elem* mp0cc;               // +0x0CC storage begin
    Elem* mp0d0;               // +0x0D0 storage end
    char pad194[0x194 - 0xd4];
    void* mField194;           // +0x194 property instance (intrusive_ptr)
    void* mField198;           // +0x198 asset id (set before 0x194)
    void* mField19c;           // +0x19C current large asset view
    char pad1b8[0x1b8 - 0x1a0];
    int  mField1b8;            // +0x1B8 spore guide config id
    void* mField1bc;           // +0x1BC user callback (intrusive_ptr)
    int  mField1c0;            // +0x1C0 user callback button id
    char mField1c4;            // +0x1C4 caller id byte 0
    char mField1c5;            // +0x1C5 caller id byte 1
    char mField1c6;            // +0x1C6 caller id byte 2
    char mField1c7;            // +0x1C7 caller id byte 3
    char mField1c8;            // +0x1C8 enable-close
    void* mField1cc;           // +0x1CC editor type override
    char mField1d0[0xc];       // +0x1D0 feed list id block
    void* mField1dc;           // +0x1DC last webpage id
    void* mField1e0;           // +0x1E0 texture preload (intrusive_ptr)
    void* mField1e4;           // +0x1E4 web browser (intrusive_ptr)
    void* mField1e8;           // +0x1E8 spore guide page (intrusive_ptr)
    bool  mb1ec;               // +0x1EC
    char pad1f0[0x1f0 - 0x1ed];
    unsigned char mField1f0[0x18];  // +0x1F0 ban type array
    int  mField208;            // +0x208
    char mField20c;            // +0x20C
    char pad230[0x230 - 0x20d];
    int  mField230;            // +0x230
    char mField236;            // +0x236 show large cards
    void* mField238;           // +0x238 window filters
    char pad23d[0x23d - 0x23c];
    bool mb23d;                // +0x23D
    char pad240[0x240 - 0x23e];
    char mField240[0xc];       // +0x240 (window block)
    char pad24d[0x24d - 0x24c];
    bool mb24d;                // +0x24D
    bool mb24e;                // +0x24E
    char pad250[0x250 - 0x24f];
    Elem* mElemHead;           // +0x250 two-Elem intrusive_ptr block

    int  FUN_00645d90();                                  // 0x00645D90
    Elem* FUN_00645db0(Elem* other);                      // 0x00645DB0
    void FUN_00645e20();                                  // 0x00645E20
    static Elem* FUN_00646030(Elem* first, Elem* last, uint32_t* key);   // 0x00646030
    static void FUN_006460b0(Elem* first, Elem* last, Elem* src);        // 0x006460B0
    static Elem* FUN_00646140(Elem* first, Elem* last, Elem* dst);       // 0x00646140
    static Elem* FUN_006461d0(Elem* first, Elem* last, Elem* dst);       // 0x006461D0
    void FUN_00646260();                                  // 0x00646260
    void FUN_006462b0(void* p);                           // 0x006462B0
    void FUN_00645620(void* launch, bool* out);
    void FUN_00645bf0();
    void FUN_00645cc0_();
};

// @ 0x00645D90
int cSPUIAssetBrowser::FUN_00645d90()
{
    int r = mField1c0;
    if (r == 0) {
        r = GetAssetBrowser2()->FUN_00645cc0();
        if (r == 0)
            r = -1;
    }
    return r;
}

// @ 0x00645FF0
void __stdcall FUN_00645ff0(Elem* first, Elem* last)
{
    for (; first < last; first = (Elem*)((char*)first + 0x14)) {
        cRefB* q = first->q;
        if (q)
            q->Release();
        cRefCountA* p = first->p;
        if (p)
            p->Release();
    }
}

// @ 0x00646260
void cSPUIAssetBrowser::FUN_00646260()
{
    mb24d = true;
    IAuthMgr* auth = GetAuthMgr();
    if (auth->a22() && !auth->a9()) {
        FUN_00645e20();
        return;
    }
    GetAuthMgr()->a17();
    mField230 = 0;
}

// @ 0x00645620  PARTIAL
void cSPUIAssetBrowser::FUN_00645620(void* launch, bool* out)
{
    void** pProp = &mField194;                 // +0x194
    if (mField194) {
        mField194 = 0;
        (*(void(__thiscall**)(void*))((char*)*(void**)(char*)pProp + 4))(*pProp);
    }
    void* prop = PropertyManager();            // 0x0067de30
    if (mField194) {
        mField194 = 0;
        (*(void(__thiscall**)(void*))((char*)*(void**)(char*)pProp + 4))(*pProp);
    }
    (*(void(__thiscall**)(void*, void*, unsigned, void**))((char*)*(void**)(char*)prop + 0x2c))(
        prop, *(void**)launch, 0x9a74416b, pProp);

    if (mField194) {
        mFlag27 = (*(void**)launch != mField198);
        mField198 = *(void**)launch;

        // bool -> [this+0x24]
        void* pv = 0;
        if ((*(char(__thiscall**)(void*, unsigned, void**))((char*)*(void**)(char*)pProp + 0x24))(
                *pProp, 0x943d7ed1, &pv) &&
            *(short*)((char*)pv + 0x12) == 1) {
            mFlag24 = *CheatManagerGetBoolPtr(pv);
        }
        char b2 = 0;
        if (mField194 &&
            (*(char(__thiscall**)(void*, unsigned, void**))((char*)*(void**)(char*)pProp + 0x24))(
                *pProp, 0xb4581c25, &pv) &&
            *(short*)((char*)pv + 0x12) == 1) {
            b2 = *CheatManagerGetBoolPtr(pv);
        }
        if (mField236 != b2) {
            if (mp0bc) {
                cSPUIAssetGrid_Clear(mp0bc);   // 0x006543a0
                FUN_0064e670(b2);              // 0x0064e670
            }
            mField236 = b2;
        }
        if (mField194 &&
            (*(char(__thiscall**)(void*, unsigned, void**))((char*)*(void**)(char*)pProp + 0x24))(
                *pProp, 0x55d0c01, &pv) &&
            *(short*)((char*)pv + 0x12) == 1) {
            mFlag25 = *CheatManagerGetBoolPtr(pv);
        }
        char b3 = mFlag25;
        if (mpLayout) {
            void* w = cSPUILayout_FindWindowByID(mpLayout, -0xe, 1);  // 0x008105b0
            if (w) {
                (*(void(__thiscall**)(void*, int, char))((char*)*(void**)(char*)w + 0x7c))(w, 1, b3);
            }
        }
        if (mField194 &&
            (*(char(__thiscall**)(void*, unsigned, void**))((char*)*(void**)(char*)pProp + 0x24))(
                *pProp, 0x563ec02, &pv) &&
            *(short*)((char*)pv + 0x12) == 1) {
            *out = *CheatManagerGetBoolPtr(pv);
        }

        mField1c0 = 0;
        GetPropertyAsKeyInstance(*pProp, 0x5653d86, &mField1c0);
        mField1dc = 0;
        GetPropertyAsKeyInstance(*pProp, 0x144d309a, &mField1dc);
        mb1ec = 0;
        if (mField194 &&
            (*(char(__thiscall**)(void*, unsigned, void**))((char*)*(void**)(char*)pProp + 0x24))(
                *pProp, 0x968adeb5, &pv) &&
            *(short*)((char*)pv + 0x12) == 1) {
            mb1ec = *CheatManagerGetBoolPtr(pv);
        }
        mField1cc = 0;
        GetPropertyAsKeyInstance(*pProp, 0xde08ba58, &mField1cc);
        mField1d0[0] = mField1d0[4] = mField1d0[8] = 0;
        GetPropertyAsKey(*pProp, 0xc6524042, mField1d0);
        mField238 = 0;
        GetPropertyAsKeyInstance(*pProp, 0xe3475119, &mField238);
        mb23d = 0;
        if (mField194 &&
            (*(char(__thiscall**)(void*, unsigned, void**))((char*)*(void**)(char*)pProp + 0x24))(
                *pProp, 0x86c7ff4f, &pv) &&
            *(short*)((char*)pv + 0x12) == 1) {
            mb23d = *CheatManagerGetBoolPtr(pv);
        }
        mField240[0] = mField240[4] = mField240[8] = 0;
        GetPropertyAsKey(*pProp, 0x1b814928, mField240);
        mField1e4 = 0;
        GetPropertyAsKeyInstance(*pProp, 0x144d3099, &mField1e4);
        mField1e8 = 0;
        GetPropertyAsKeyInstance(*pProp, 0x943d7ed0, &mField1e8);

        char b4 = 0;
        if (mField194 &&
            (*(char(__thiscall**)(void*, unsigned, void**))((char*)*(void**)(char*)pProp + 0x24))(
                *pProp, 0x943d7ed2, &pv) &&
            *(short*)((char*)pv + 0x12) == 1) {
            b4 = *CheatManagerGetBoolPtr(pv);
        }
        if (mp0bc) FUN_0064f2d0(b4 != 0);       // 0x0064f2d0
        char b5 = 1;
        if (mField194 &&
            (*(char(__thiscall**)(void*, unsigned, void**))((char*)*(void**)(char*)pProp + 0x24))(
                *pProp, 0x588c721, &pv) &&
            *(short*)((char*)pv + 0x12) == 1) {
            b5 = *CheatManagerGetBoolPtr(pv);
        }
        if (mp0bc) FUN_0064f2f0(b5 != 0);       // 0x0064f2f0

        void* bans = FUN_0066a5e0(1, 0);        // 0x0066a5e0
        memcpy(mField1f0, bans, 0x20);          // 8 dwords
        for (int i = 0; i < 0x18; ++i) {
            void* b = FUN_0066a800(i);          // 0x0066a800
            if (b == 0) {
                mField1f0[i] = 0;
            } else {
                (*(void(__thiscall**)(void*))((char*)*(void**)(char*)b + 4))(b);
                if (mField194 &&
                    (*(char(__thiscall**)(void*, unsigned, void**))((char*)*(void**)(char*)pProp + 0x24))(
                        *pProp, g_banPropertyKeys[i * 4], &pv) &&
                    *(short*)((char*)pv + 0x12) == 1) {
                    void* val = pv;
                    if ((*(unsigned char*)((char*)pv + 0x10) & 0x30) != 0) val = *(void**)pv;
                    mField1f0[i] = *(unsigned char*)val;
                }
                (*(void(__thiscall**)(void*))((char*)*(void**)(char*)b + 8))(b);
            }
        }

        bool hasFilter = GetPropertyAsKey(*pProp, 0xb39914fa, &pv) != 0;
        if (hasFilter) {
            mField208 = 0;
            mField20c = 0;
        }

        char textBuf[0xc];
        cString_ctor(textBuf);
        GetPropertyAsText(*pProp, 0x344ec74e, textBuf);
        void* text = cString_GetText(textBuf);       // 0x006b55c0
        cSPUIAssetBrowser_SetCallToActionMessage(this, text);  // 0x006455b0

        void* oldPreload = mField1e0;
        GetPropertyAsKeyInstance(*pProp, 0x574d7f3, &mField1e0);
        bool changed = (oldPreload != mField1e0);
        mFlag26 = changed;
        if (changed) {
            FUN_006628d0(mp0c0);                      // 0x006628d0
            FUN_00663860((char*)mp0bc, mField1e0, mFlag29,
                         (int)mp68, mp6c);            // 0x00663860
        }
        GetPropertyAsKeyInstance(*pProp, 0x5db9092, &mField19c);
        cString_dtor(textBuf);
    }

    mField1b8 = *(int*)((char*)launch + 4);
    void* newCb = *(void**)((char*)launch + 0xc);
    void* oldCb = mField1bc;
    if (newCb != oldCb) {
        if (newCb) (*(void(__thiscall**)(void*))(*(void**)newCb))(newCb);
        mField1bc = newCb;
        if (oldCb) (*(void(__thiscall**)(void*))((char*)*(void**)oldCb + 4))(oldCb);
    }
    mField1c4 = *(char*)((char*)launch + 0x10);
    mField1c5 = *(char*)((char*)launch + 0x11);
    mField1c6 = *(char*)((char*)launch + 0x12);
    if (*(int*)((char*)g_sAppProperties + 0x118) != 0)
        mField1c4 = 0;
    mField1c7 = *(char*)((char*)launch + 0x14);
    if (mp0bc) {
        char v = (mField1c4 != 0 || mField1c5 != 0) ? 1 : 0;
        *(char*)((char*)mp0bc + 0x1b9) = v;
        *(char*)((char*)mp0bc + 0x1ba) = mField1c6;
    }
    mFlag26 = false;
    mField1c8 = 0;
}
// @ 0x00645BF0  PARTIAL
void cSPUIAssetBrowser::FUN_00645bf0()
{
    if (!mb1ec) {
        return;                                       // original: return mField238
    }
    void* h = mp0bc;
    if (!h || !*(void**)((char*)h + 0xe0))
        return;
    void* key = *(void**)((char*)*(void**)((char*)h + 0xe0) + 0x18);
    void* propTemp = 0;                               // intrusive_ptr<IConfig>
    void* mgr = PropertyManager();
    if (propTemp) {
        void* tmp = propTemp;
        propTemp = 0;
        (*(void(__thiscall**)(void*))((char*)*(void**)(char*)tmp + 4))(tmp);
    }
    (*(void(__thiscall**)(void*, void*, unsigned, void**))((char*)*(void**)(char*)mgr + 0x2c))(
        mgr, key, 0xcc489c6f, &propTemp);
    void* out = 0;
    if (propTemp) {
        GetPropertyAsKeyInstance(propTemp, 0x968ae1b1, &out);
    }
    void* old = propTemp;                             // release the temp property
    if (out) {
        if (old) (*(void(__thiscall**)(void*))((char*)*(void**)(char*)old + 4))(old);
        return;                                       // original returns `out`
    }
    if (old) (*(void(__thiscall**)(void*))((char*)*(void**)(char*)old + 4))(old);
}
// @ 0x00645CC0  PARTIAL
void cSPUIAssetBrowser::FUN_00645cc0_()
{
    if (!mb1ec) {
        return;                                       // original: return mField1dc
    }
    void* h = mp0bc;
    if (!h || !*(void**)((char*)h + 0xe0))
        return;
    void* key = *(void**)((char*)*(void**)((char*)h + 0xe0) + 0x18);
    void* propTemp = 0;
    void* mgr = PropertyManager();
    (*(void(__thiscall**)(void*, void*, unsigned, void**))((char*)*(void**)(char*)mgr + 0x2c))(
        mgr, key, 0xcc489c6f, &propTemp);
    void* out = 0;
    if (propTemp) {
        GetPropertyAsKeyInstance(propTemp, 0x968ae1b0, &out);
    }
    void* old = propTemp;
    if (old) (*(void(__thiscall**)(void*))((char*)*(void**)(char*)old + 4))(old);
}
// @ 0x00645DB0  PARTIAL  (the receiver block is a two-pointer intrusive_ptr pair at +0)
struct IntrusivePair { cRefCountA* p; cRefB* q; };
Elem* cSPUIAssetBrowser::FUN_00645db0(Elem* other)
{
    IntrusivePair* self = (IntrusivePair*)this;
    IntrusivePair* src = (IntrusivePair*)other;
    cRefCountA* newp = src->p;
    cRefCountA* oldp = self->p;
    if (newp != oldp) {
        if (newp) newp->AddRef();
        self->p = newp;
        if (oldp) oldp->Release();
    }
    cRefB* newq = src->q;
    cRefB* oldq = self->q;
    if (newq != oldq) {
        if (newq) newq->AddRef();
        self->q = newq;
        if (oldq) oldq->Release();
    }
    return (Elem*)self;
}
// @ 0x00645E20  PARTIAL (noinline so 00646260 keeps its tail jmp)
void SetModelName(void* self, void* name);              // 0x005cd130
extern "C" void* g_tokenTranslator;                     // 0x015ee298
__declspec(noinline) void cSPUIAssetBrowser::FUN_00645e20()
{
    mb24d = false;
    if (mp0cc != mp0d0) {
        int count = (int)(mp0d0 - mp0cc);
        if (count == 1) {
            Elem* first = mp0cc;
            void* obj = (void*)first->q;
            if (obj != 0) {
                Elem* sel = (count == 1) ? first : (Elem*)0;
                void* model = (*(void*(__thiscall**)(void*))((char*)*(void**)(char*)sel + 0xc))(sel);
                SetModelName(g_tokenTranslator, model);
            }
        }
    }
    UI::CalloutMessageBox((char*)this + 4, (void*)0x152584c);  // 0x00809db0
    mField230 = 2;
    mb24e = true;
}
// @ 0x00646030  PARTIAL
Elem* cSPUIAssetBrowser::FUN_00646030(Elem* first, Elem* last, uint32_t* key)
{
    int len = (int)(last - first);
    if (len > 0) {
        Elem* k = (Elem*)key;
        int half;
        do {
            half = len >> 1;
            Elem* mid = first + half;
            bool less = mid->a < k->a;
            if (mid->a == k->a) {
                less = mid->c < k->c;
                if (mid->c == k->c) {
                    less = mid->b < k->b;
                }
            }
            if (less) {
                first = mid + 1;
                half = len + (-1 - half);
            }
            len = half;
        } while (half > 0);
    }
    return first;
}
// @ 0x006460B0
void cSPUIAssetBrowser::FUN_006460b0(Elem* first, Elem* last, Elem* src)
{
    for (; first != last; first = (Elem*)((char*)first + 0x14)) {
        first->a = src->a;
        first->b = src->b;
        first->c = src->c;
        cRefCountA* newp = src->p;
        cRefCountA* oldp = first->p;
        if (newp != oldp) {
            if (newp) newp->AddRef();
            first->p = newp;
            if (oldp) oldp->Release();
        }
        cRefB* newq = src->q;
        cRefB* oldq = first->q;
        if (newq != oldq) {
            if (newq) newq->AddRef();
            first->q = newq;
            if (oldq) oldq->Release();
        }
    }
}

// @ 0x00646140
Elem* cSPUIAssetBrowser::FUN_00646140(Elem* first, Elem* last, Elem* dst)
{
    while (first != last) {
        dst->a = first->a;
        dst->b = first->b;
        dst->c = first->c;
        cRefCountA* newp = first->p;
        cRefCountA* oldp = dst->p;
        if (newp != oldp) {
            if (newp) newp->AddRef();
            dst->p = newp;
            if (oldp) oldp->Release();
        }
        cRefB* newq = first->q;
        cRefB* oldq = dst->q;
        if (newq != oldq) {
            if (newq) newq->AddRef();
            dst->q = newq;
            if (oldq) oldq->Release();
        }
        first = (Elem*)((char*)first + 0x14);
        dst = (Elem*)((char*)dst + 0x14);
    }
    return dst;
}

// @ 0x006461D0
Elem* cSPUIAssetBrowser::FUN_006461d0(Elem* first, Elem* last, Elem* dst)
{
    while (last != first) {
        last = (Elem*)((char*)last - 0x14);
        dst = (Elem*)((char*)dst - 0x14);
        dst->a = last->a;
        dst->b = last->b;
        dst->c = last->c;
        cRefCountA* newp = last->p;
        cRefCountA* oldp = dst->p;
        if (newp != oldp) {
            if (newp) newp->AddRef();
            dst->p = newp;
            if (oldp) oldp->Release();
        }
        cRefB* newq = last->q;
        cRefB* oldq = dst->q;
        if (newq != oldq) {
            if (newq) newq->AddRef();
            dst->q = newq;
            if (oldq) oldq->Release();
        }
    }
    return dst;
}
// @ 0x006462B0  PARTIAL
void cSPUIAssetBrowser::FUN_006462b0(void* p)
{
    int key = (*(int(__thiscall**)(void*))((char*)*(void**)(char*)p + 0x24))(p);
    void* it = (void*)eastl_hashtable_find((char*)this + 0xf8, &key);
    if ((int)it == *(int*)(*(int*)((char*)this + 0xfc) + *(int*)((char*)this + 0x100) * 4)) {
        int k2 = (*(int(__thiscall**)(void*))((char*)*(void**)(char*)p + 0x40))(p);
        it = (void*)eastl_hashtable_find((char*)this + 0x118, &k2);
        if ((int)it == *(int*)(*(int*)((char*)this + 0x11c) + *(int*)((char*)this + 0x120) * 4)) {
            void* mem = operator_new(0x108, "Sporepedia", 0, 0, 0, 0);
            if (mem) {
                AssetDiscovery_View_ctor(mem);      // 0x00657f70
            }
            return;
        }
    }
    (*(void(__thiscall**)(void*))((char*)*(void**)(char*)it + 4))(it);
}
