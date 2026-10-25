// Slice s00de5040: 0x00DE5040..0x00DE60F0.  SP::cGalaxyGameEntryImpl galaxy
// game-entry screen methods plus several eastl container helpers.
//
//  0x00de5040  cGalaxyGameEntryImpl::UpdateLoginButton  (538 B)
//  0x00de5260  achievement-award sweep                    (102 B)
//  0x00de52d0  pop-back into current dword                ( 48 B)
//  0x00de5300  clear-back loop                            ( 40 B)
//  0x00de5330  handle toggle (a)                          (146 B)
//  0x00de53d0  handle toggle (b)                          (150 B)
//  0x00de5470  cGalaxyGameEntryImpl::ShowGalaxy           (632 B)
//  0x00de56f0  rbtree find-or-zero helper                 ( 70 B)
//  0x00de57b0  helper                                     (127 B)
//  0x00de58c0  helper                                     (134 B)
//  0x00de5950  helper (large)                             (859 B)
//  0x00de5cb0  achievement-presence probe                  ( 75 B)
//  0x00de5d00  helper                                     (226 B)
//  0x00de5df0  helper                                     (226 B)
//  0x00de5ee0  eastl::vector<...>::resize                 (117 B)
//  0x00de60f0  helper                                     (113 B)
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// Transform message (ctor 0x434040, Init 0x832dc0): flags/count + pos + scale + 3x3 rotation.
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float fx, float fy, float fz) : x(fx), y(fy), z(fz) {}
};
struct Matrix3 { float m[9]; };
struct XformMsg {
    uint16_t flags;         // +0x00
    uint16_t count;         // +0x02
    Vec3     pos;           // +0x04
    float    scale;         // +0x10
    Matrix3  rot;           // +0x14

    XformMsg();                                     // 0x00434040
    void Init();                                    // 0x00832dc0 identity transform
    void SetPos(const Vec3& v) { pos = v; flags |= 4; ++count; }
    void SetScale(float s)     { scale = s; ++count; }
};
inline Vec3 operator*(const Vec3& v, const Matrix3& m)
{
    return Vec3(v.x * m.m[0] + v.y * m.m[3] + v.z * m.m[6],
                v.x * m.m[1] + v.y * m.m[4] + v.z * m.m[7],
                v.x * m.m[2] + v.y * m.m[5] + v.z * m.m[8]);
}
inline Vec3& operator+=(Vec3& a, const Vec3& b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

// Handle / manager interfaces used by the game-entry handle wrappers.
struct cGalaxyHandle {
    virtual void h0();              // vtbl+0x00
    virtual void hRelease();        // vtbl+0x04
    virtual void hStart(int a);     // vtbl+0x08
    virtual void hStop(int a);      // vtbl+0x0c
    virtual void h10();             // vtbl+0x10
    virtual void h14();             // vtbl+0x14
    virtual void h18(XformMsg* pMsg); // vtbl+0x18  set transform
};

struct cGalaxyManager {
    virtual void m0();                                // vtbl+0x00
    virtual void m1();                                // vtbl+0x04
    virtual bool mAdd(unsigned int id, int a, void** out); // vtbl+0x08
    virtual void m3();                                // vtbl+0x0c
};

// One galaxy handle slot: created through the manager, torn down through the handle.
struct GalaxyHandleSlot {
    cGalaxyHandle* mpHandle;        // +0x00

    void Create(cGalaxyManager* pManager, uint32_t nId);   // inlined at every call site
    void Stop(int32_t nFlags);
};
inline void GalaxyHandleSlot::Create(cGalaxyManager* pManager, uint32_t nId)
{
    if (mpHandle != 0) {
        cGalaxyHandle* pOld = mpHandle;
        mpHandle = 0;
        pOld->hRelease();
    }
    pManager->mAdd(nId, 0, (void**)&mpHandle);
}
inline void GalaxyHandleSlot::Stop(int32_t nFlags)
{
    if (mpHandle != 0)
        mpHandle->hStop(nFlags);
}

// 0xbc-byte record holding three 0x10-byte vector headers.
struct VecHeader {
    int begin;      // +0
    int cur;        // +4
    int end;        // +8
    int cap;        // +0xc
};
struct RecBC {
    VecHeader a;            // +0x00
    VecHeader b;            // +0x10
    VecHeader c;            // +0x20
    char      rest[0xbc - 0x30];
};

void operator_delete_array(void* p);

namespace eastl { extern wchar_t gEmptyString16[]; }

struct Str16 {
    wchar_t* begin;     // +0
    wchar_t* end;       // +4
    wchar_t* cap;       // +8
    int      unused;    // +0xc

    Str16()
    {
        begin = (wchar_t*)0x1667bac;
        end   = (wchar_t*)0x1667bac;
        cap   = (wchar_t*)0x1667bae;
    }
};
struct cGameData {
    Str16 s0;                       // +0x00
    Str16 s1;                       // +0x10
    Str16 s2;                       // +0x20
    int   z30, z34, z38, z3c, z40, z44;
    int   keep48;                   // +0x48 (not zeroed here)
    int   z4c, z50, z54, z58, z5c, z60, z64, z68, z6c, z70, z74, z78;

    void        FUN_00b26fb0(unsigned int a);  // 0x00b26fb0
    cGameData(unsigned int p2);                // 0x00de60f0
};

inline void FreeHeader(VecHeader& v)
{
    int n = v.end - v.begin;
    if ((n & ~1) > 2 && v.begin != 0)
        operator_delete_array((void*)v.begin);
}

// Achievements controller used by the presence probe (0x00de5cb0).
struct cAchievements {
    bool FUN_00675e80(void);    // 0x00675e80 (hash-map lookup)
    bool FUN_005c0dd0(void);    // 0x005c0dd0
    void AwardAchievement(void); // 0x00676710
};
cAchievements* __stdcall FUN_00675250(unsigned int a);   // 0x00675250
cAchievements* __stdcall FUN_00675250_0(void);           // 0x00675250 (no-arg form)

// rbtree node / increment used by the award sweep (0x00de5260).
struct RBNode { char pad[0x10]; unsigned int id; };
void* __cdecl RBTreeIncrement(void* n);   // 0x00921580

struct MapItr { void* node; };
struct RBTreeThing {
    int     count;      // +0x000
    void*   sentinel;   // +0x004
    void*   root;       // +0x008

    MapItr* find(MapItr& out, const unsigned int& key);   // 0x00e5c780
};

// Node/out types used by the resource-map probe (0x00de56f0).
struct KeyNode {
    char pad[0x1c];
    int  v1c;   // +0x1c
    int  v20;   // +0x20
    int  v24;   // +0x24
};
struct OutKey3 { int a, b, c; };
struct RbFind56 {
    int     count;      // +0x00
    void*   sentinel;   // +0x04 (this+0x3c)
    void*   root;       // +0x08

    void*   Find(void* a, void** b);   // 0x00a21dc0
};

// Types used by the rbtree insert helper (0x00de57b0).
struct Key2 { int a, b; };
struct RbNode57 { char pad[0x10]; Key2 key; };
struct RbTree57 {
    void*   root;       // +0x00 (this+0x04)
    char    pad[0x0c];
    int     count;      // +0x10 (this+0x14)
};
void* __cdecl EAllocNew(int size, const char* file, int flags, int align, void* alloc, int line); // 0x00f473a0
void  __cdecl RBTreeInsert57(void* node, void* parent, void* root, int side);                    // 0x009216a0

struct Wnd;

// UI layout object embedded at +0x144 (vtable, ref count, resource key, collection).
struct cSPUILayout {
    void**   mpVtbl;            // +0x00
    int32_t  mnRefCount;        // +0x04
    uint32_t mHash;             // +0x08
    uint32_t mId;               // +0x0c
    uint32_t mGroup;            // +0x10
    void*    mpCollection;      // +0x14

    bool Init(const wchar_t* pName, uint32_t nId, char bFlag, uint32_t nGroup); // 0x00812160
    Wnd* FindWindowByID(uint32_t nId, char bFlag);                              // 0x008105b0
};

struct cGalaxyGameEntryImpl {
    char       mPad00[0x04];
    RbTree57   mTree4;             // +0x04
    char       mPad18[0x38 - 0x18];
    RbFind56   mRb38;              // +0x38
    char       mPad44[0x100 - 0x44];
    char       mb100;              // +0x100  galaxy shown
    char       mPad101[0x103 - 0x101];
    char       mb103;              // +0x103
    char       mPad104[0x10c - 0x104];
    int        mCurrentDword;      // +0x10c
    char*      mBegin;             // +0x110
    char*      mEnd;               // +0x114
    char       mPad118[0x144 - 0x118];
    cSPUILayout mLayout144;        // +0x144
    void*      mpManager;          // +0x15c  cGalaxyManager*
    GalaxyHandleSlot mHandle160;   // +0x160
    GalaxyHandleSlot mHandle164;   // +0x164
    char       mPad168[0x16c - 0x168];
    GalaxyHandleSlot mHandle16c;   // +0x16c
    GalaxyHandleSlot mHandle170;   // +0x170
    void*      mpHandleA;          // +0x174
    char       mPad178[0x184 - 0x178];
    void*      mpGlobalUI;         // +0x184  cSPUIGlobalUI*
    char       mPad188[0x194 - 0x188];
    float      mf194;              // +0x194  minimum login-button width
    char       mPad198[0x1a0 - 0x198];
    GalaxyHandleSlot mHandle1a0;   // +0x1a0
    char       mPad1a4[0x1b0 - 0x1a4];
    void*      mpHandleB;          // +0x1b0
    char       mPad1b4[0x1f5 - 0x1b4];
    char       mFlag1f5;           // +0x1f5
    char       mPad1f6[0x254 - 0x1f6];
    RBTreeThing mRbTree;           // +0x254
    char       mPad260[0x271 - 0x260];
    char       mb271;              // +0x271  network-activity indicator preference

    void  UpdateLoginButton(char param2);  // 0x00de5040
    void  FUN_00de5260(void);           // 0x00de5260
    void  FUN_00de52d0(void);           // 0x00de52d0
    void  FUN_00de5300(void);           // 0x00de5300
    void  FUN_00de5330(char p);         // 0x00de5330
    void  FUN_00de53d0(char p);         // 0x00de53d0
    void  ShowGalaxy(char param2);      // 0x00de5470
    OutKey3* FUN_00de56f0(OutKey3& pOut, KeyNode* key); // 0x00de56f0
    void  FUN_00de57b0(RbNode57** pOut, RbNode57* parent, Key2* key, char flag); // 0x00de57b0
    void  FUN_00de4910(void);           // 0x00de4910
    void  FUN_00de41b0(void);           // 0x00de41b0
    void  FUN_00de5950(void);           // 0x00de5950
    bool  FUN_00de5cb0(unsigned int a); // 0x00de5cb0
    void  FUN_00de5d00(void);           // 0x00de5d00
    void  FUN_00de5df0(void);           // 0x00de5df0
};

// ===========================================================================

// ---------------------------------------------------------- login button helpers
struct RectF {
    float left;      // +0x00
    float top;       // +0x04
    float right;     // +0x08
    float bottom;    // +0x0c
};
// GUI window: slots 0x0c = child by id, 0x10 = owner, 0x38 = area, 0x74 = set size,
// 0x7c = flag pair, 0x80 = set text, 0xe0 = attach, 0x104 = add window proc
struct Wnd {
    virtual void  w00(); virtual void  w01(); virtual void  w02();
    virtual void* w03(uint32_t nId);                 // +0x0c  named child
    virtual void* w04();                             // +0x10  owner
    virtual void  w05(); virtual void  w06(); virtual void  w07();
    virtual void  w08(); virtual void  w09(); virtual void  w10(); virtual void  w11();
    virtual void  w12(); virtual void  w13();
    virtual RectF* w14();                            // +0x38  window area
    virtual void  w15(); virtual void  w16(); virtual void  w17();
    virtual void  w18(); virtual void  w19(); virtual void  w20(); virtual void  w21();
    virtual void  w22(); virtual void  w23(); virtual void  w24(); virtual void  w25();
    virtual void  w26(); virtual void  w27(); virtual void  w28();
    virtual void  w29(float fWidth, float fHeight);  // +0x74  set size
    virtual void  w30();
    virtual void  w31(int32_t nA, int32_t nB);       // +0x7c  flag pair
    virtual void  w32(const wchar_t* pText);         // +0x80  set text
    virtual void  w33(); virtual void  w34(); virtual void  w35(); virtual void  w36();
    virtual void  w37(); virtual void  w38(); virtual void  w39(); virtual void  w40();
    virtual void  w41(); virtual void  w42(); virtual void  w43(); virtual void  w44();
    virtual void  w45(); virtual void  w46(); virtual void  w47(); virtual void  w48();
    virtual void  w49(); virtual void  w50(); virtual void  w51(); virtual void  w52();
    virtual void  w53(); virtual void  w54(); virtual void  w55();
    virtual void  w56(void* pObject);                // +0xe0  attach
    virtual void  w57(); virtual void  w58(); virtual void  w59(); virtual void  w60();
    virtual void  w61(); virtual void  w62(); virtual void  w63(); virtual void  w64();
    virtual void  w65(void* pProc);                  // +0x104 add window proc
};
// authentication manager: slots 0x24 = ?, 0x38 = account name, 0x58 = logged in
struct cAuth {
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
    virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
    virtual void a08();
    virtual bool a09();                              // +0x24
    virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13();
    virtual const wchar_t* a14();                    // +0x38  account name
    virtual void a15(); virtual void a16(); virtual void a17();
    virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21();
    virtual bool a22();                              // +0x58  logged in
};
// resource key (hash, id, group) the global UI loads its layout with
struct ResKey {
    uint32_t mHash;          // +0x00
    uint32_t mId;            // +0x04
    uint32_t mGroup;         // +0x08
};
struct cGlobalUI {
    virtual void g00();                              // +0x00
    virtual void g04();                              // +0x04
    virtual bool g08(const ResKey* pKey);            // +0x08  load layout
    virtual void g0c(); virtual void g10(); virtual void g14(); virtual void g18();
    virtual void g1c();

    cGlobalUI* Construct();                          // 0x00e03ab0
    Wnd* FindWindowByID(uint32_t nId);               // 0x00e012b0
};
struct WString16 {
    wchar_t* mpBegin;        // +0x00
    wchar_t* mpEnd;          // +0x04
    wchar_t* mpCapacity;     // +0x08
    uint32_t mPad0c;
    uint32_t mPad10;
    void DeallocateSelf();                           // 0x00933960
};
// larger of two floats (address select at the call site)
inline const float* MaxPtr(const float* a, const float* b) { return (*a < *b) ? b : a; }

struct cString47a0 {
    uint32_t m00, m04, m08, m0c;
    void          ctor();                            // 0x006b5060
    void          dtor();                            // 0x006b5240
    bool          Load(uint32_t a, uint32_t b, const wchar_t* pText);  // 0x006b54b0
    const wchar_t* GetText();                        // 0x006b55c0
};
cAuth* __cdecl PollenAuthManager(void);                                    // 0x00607a60
void   __cdecl ConvertToString16(WString16* pOut, const wchar_t* pText);   // 0x0093c6d0
void   __cdecl AutoSizeWindowForText(Wnd* pWnd, int nA, int nB);           // 0x00806e40

// @ 0x00de5040
void cGalaxyGameEntryImpl::UpdateLoginButton(char param2)
{
    Wnd* pWin = ((cGlobalUI*)mpGlobalUI)->FindWindowByID(0x4810f47);
    cAuth* pAuth = PollenAuthManager();
    if (pWin == 0)
        return;
    if (pAuth == 0)
        return;
    if (param2 != 0 && pAuth->a22() && !pAuth->a09()) {
        WString16 str;
        ConvertToString16(&str, pAuth->a14());
        pWin->w32(str.mpBegin);
        str.DeallocateSelf();
    } else {
        cString47a0 str;
        str.ctor();
        if (!pAuth->a22())
            str.Load(0xb7bcef68, 0x562d9e4, L"Register");
        else
            str.Load(0xb7bcef68, 0x662d9ea, L"Login");
        pWin->w32(str.GetText());
        str.dtor();
    }
    const RectF* pRect = pWin->w14();
    float fOldWidth = pRect->right - pRect->left;
    AutoSizeWindowForText(pWin, 0, 0);
    float fNewWidth = pRect->right - pRect->left;
    float fWidth = *MaxPtr(&fNewWidth, &mf194);
    pWin->w29(fWidth, pRect->bottom - pRect->top);
    float fDelta = fWidth - fOldWidth;
    if (fDelta != 0.0f) {
        Wnd* pWin2 = ((cGlobalUI*)mpGlobalUI)->FindWindowByID(0x48102ca);
        if (pWin2 != 0) {
            const RectF* pRect2 = pWin2->w14();
            pWin2->w29((pRect2->right - pRect2->left) + fDelta, pRect2->bottom - pRect2->top);
        }
        Wnd* pWin3 = ((cGlobalUI*)mpGlobalUI)->FindWindowByID(0x695ea48);
        if (pWin3 != 0) {
            const RectF* pRect3 = pWin3->w14();
            pWin3->w29((pRect3->right - pRect3->left) + fDelta, pRect3->bottom - pRect3->top);
        }
    }
}

// @ 0x00de5260
void cGalaxyGameEntryImpl::FUN_00de5260(void)
{
    if (mFlag1f5 == 0) {
        if (!FUN_00675250_0()->FUN_005c0dd0()) {
            for (RBNode* n = (RBNode*)mRbTree.root;
                 n != (RBNode*)((char*)this + 0x258);
                 n = (RBNode*)RBTreeIncrement(n)) {
                if (!FUN_00675250(n->id)->FUN_00675e80())
                    FUN_00675250(n->id)->AwardAchievement();
            }
        }
    }
}

// @ 0x00de52d0
void cGalaxyGameEntryImpl::FUN_00de52d0(void)
{
    if (mBegin == mEnd) {
        mCurrentDword = 2;
        return;
    }
    mCurrentDword = *(int*)(mEnd - 4);
    mEnd -= 4;
}

// @ 0x00de5300
void cGalaxyGameEntryImpl::FUN_00de5300(void)
{
    while (mBegin != mEnd)
        mEnd -= 4;
}

// @ 0x00de5330
void cGalaxyGameEntryImpl::FUN_00de5330(char param2)
{
    if (param2 != 0) {
        cGalaxyHandle** field = (cGalaxyHandle**)&mpHandleA;
        if (mpHandleA != 0)
            return;
        cGalaxyHandle* h = *field;
        cGalaxyManager* m = (cGalaxyManager*)mpManager;
        if (h != 0) {
            *field = 0;
            h->hRelease();
        }
        if (m->mAdd(0x11e401e1, 0, (void**)field)) {
            (*field)->hStart(0);
            return;
        }
    } else {
        cGalaxyHandle* h = (cGalaxyHandle*)mpHandleA;
        if (h != 0) {
            h->hStop(0);
            cGalaxyHandle* h2 = (cGalaxyHandle*)mpHandleA;
            if (h2 != 0) {
                mpHandleA = 0;
                h2->hRelease();
                return;
            }
        }
    }
}

// @ 0x00de53d0
void cGalaxyGameEntryImpl::FUN_00de53d0(char param2)
{
    if (param2 != 0) {
        cGalaxyHandle** field = (cGalaxyHandle**)&mpHandleB;
        if (mpHandleB != 0)
            return;
        cGalaxyManager* m = (cGalaxyManager*)mpManager;
        if (m == 0)
            return;
        cGalaxyHandle* h = *field;
        if (h != 0) {
            *field = 0;
            h->hRelease();
        }
        if (m->mAdd(0x4c4ba0a9, 0, (void**)field)) {
            (*field)->hStart(0);
            return;
        }
    } else {
        cGalaxyHandle* h = (cGalaxyHandle*)mpHandleB;
        if (h != 0) {
            h->hStop(0);
            cGalaxyHandle* h2 = (cGalaxyHandle*)mpHandleB;
            if (h2 != 0) {
                mpHandleB = 0;
                h2->hRelease();
                return;
            }
        }
    }
}

struct cGameEntryOwner {
    void FUN_00df9510(void);        // 0x00df9510
};
cGameEntryOwner* __cdecl FUN_00df5f40(void);   // 0x00df5f40

// @ 0x00de5470
void cGalaxyGameEntryImpl::ShowGalaxy(char param2)
{
    if (param2 != 0) {
        if (mb100 == 0) {
            mHandle160.Create((cGalaxyManager*)mpManager, 0xef572ebb);
            if (mHandle160.mpHandle != 0)
                mHandle160.mpHandle->hStart(0);
            mHandle1a0.Create((cGalaxyManager*)mpManager, 0xf07cd744);
            if (mHandle1a0.mpHandle != 0) {
                mHandle1a0.mpHandle->hStart(0);
                XformMsg msg;
                msg.Init();
                msg.SetScale(0.4f);
                msg.pos += Vec3(0.0f, 0.0f, -60.0f) * msg.rot;
                msg.flags |= 4;
                ++msg.count;
                mHandle1a0.mpHandle->h18(&msg);
            }
            mHandle16c.Create((cGalaxyManager*)mpManager, 0xedd3f703);
            mHandle170.Create((cGalaxyManager*)mpManager, 0xa97afd43);
        }
    } else {
        mHandle1a0.Stop(1);
        mHandle164.Stop(1);
        mHandle160.Stop(1);
        mHandle16c.Stop(1);
        mHandle170.Stop(1);
        FUN_00df5f40()->FUN_00df9510();
    }
    mb100 = param2;
}

// @ 0x00de56f0
OutKey3* cGalaxyGameEntryImpl::FUN_00de56f0(OutKey3& pOut, KeyNode* key)
{
    mRb38.Find((void*)&key, (void**)key);
    if (key != (KeyNode*)&mRb38.sentinel) {
        pOut.a = key->v1c;
        pOut.b = key->v20;
        pOut.c = key->v24;
        return &pOut;
    }
    pOut.a = 0;
    pOut.b = 0;
    pOut.c = 0;
    return &pOut;
}

// @ 0x00de57b0
void cGalaxyGameEntryImpl::FUN_00de57b0(RbNode57** pOut, RbNode57* parent, Key2* key, char flag)
{
    int left = (flag == 0 && parent != (RbNode57*)&mTree4.root
                && key->a >= parent->key.a) ? 1 : 0;
    RbNode57* node = (RbNode57*)EAllocNew(0x18, (const char*)0x13f09b4, 0, 0, (void*)0x13ebb38, 0xd1);
    if (&node->key != 0)
        node->key = *key;
    RBTreeInsert57(node, parent, &mTree4.root, left);
    RbNode57** ppOut = pOut;
    mTree4.count++;
    *ppOut = node;
}

// @ 0x00de58c0
RecBC* FUN_00de58c0(RecBC* p, RecBC* q, RecBC* out)
{
    while (p != q) {
        FreeHeader(p->c);
        FreeHeader(p->b);
        FreeHeader(p->a);
        p++;
        out++;
    }
    return out;
}

// ---- galaxy entry activation -------------------------------------------------
// win-proc interface the entry registers with its windows (object+0x04)
struct IWinProc { virtual void w00(); virtual void w04(); virtual void w08(); };

// property list: virtual +0x14 stores a value, +0x24 reads one back
union VariantPayload {
    uint8_t  mbValue;            // +0x00  inline bool
    void*    mpData;             // +0x00  indirect payload
};
struct cVariant {
    VariantPayload mValue;       // +0x00
    uint32_t mPad04;             // +0x04
    uint32_t mPad08;             // +0x08
    uint32_t mPad0c;             // +0x0c
    uint16_t mnFlags10;          // +0x10
    uint16_t mnTypeId12;         // +0x12

    void   SetBool(bool bValue) { mValue.mbValue = bValue; mnTypeId12 = 1; mnFlags10 = 0; }
    // the bool is stored inline unless the flags say the payload is indirect
    uint8_t GetBool() { return (mnFlags10 & 0x30) ? *(uint8_t*)mValue.mpData : mValue.mbValue; }
    void   Destruct(int32_t nFlags);                 // 0x0093db80
};
struct cPropertyList {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual void v14(uint32_t nKey, cVariant* pValue);          // +0x14
    virtual void* v18(); virtual void* v1c(); virtual void* v20();
    virtual bool v24(uint32_t nKey, cVariant** ppValue);        // +0x24
};
extern cPropertyList* g_pAppPreferences;             // 0x015fd91c

inline bool GetBoolProperty(cPropertyList* pPrefs, uint32_t nKey, uint8_t* pValue)
{
    if (pPrefs == 0)
        return false;
    cVariant* pVar;
    if (!pPrefs->v24(nKey, &pVar))
        return false;
    if (pVar->mnTypeId12 != 1)
        return false;
    *pValue = pVar->GetBool();
    return true;
}

// network-activity indicator proc installed on the connection window
struct NetworkActivityProc {
    NetworkActivityProc* Ctor();                     // 0x00e01690 (returns its this)
};

// singletons
struct cWindowManager {
    virtual void* w04();                             // +0x04
    virtual void  w08(); virtual void  w0c(); virtual void  w10(); virtual void  w14();
    virtual void  w18(); virtual void  w1c(); virtual void  w20(); virtual void  w24();
    virtual void  w28(); virtual void  w2c(); virtual void  w30(); virtual void  w34();
    virtual void  w38(); virtual void  w3c(); virtual void  w40(); virtual void  w44();
    virtual void  w48();
    virtual void  w4c(int32_t nMode, void* pArg);    // +0x4c
};
struct cAppSystem {
    virtual void* a00(); virtual void* a04(); virtual void* a08(); virtual void* a0c();
    virtual void* a10(); virtual void* a14(); virtual void* a18(); virtual void* a1c();
    virtual void* a20(); virtual void* a24(); virtual void* a28(); virtual void* a2c();
    virtual void* a30(); virtual void* a34(); virtual void* a38(); virtual void* a3c();
    virtual void* a40(); virtual void* a44(); virtual void* a48(); virtual void* a4c();
    virtual void* a50();
    virtual bool  a54();                             // +0x54
};
cWindowManager* __cdecl WindowManager(void);         // 0x0067caa0
cAppSystem*     __cdecl AppSystem(void);             // 0x0067dd00

bool     __cdecl IsWorldLayoutFlagSet(uint32_t nFlag);          // 0x00685520
uint32_t __cdecl FNV1_String16(uint32_t nBasis, const wchar_t* pText, int nMode); // 0x00932f30
void     __cdecl SP_SaveResource(cPropertyList* pPrefs, void* pArea);             // 0x006b1d50
void*    __cdecl SP_GetSaveArea(uint32_t nId, int32_t nFlags);                    // 0x006b1f90

extern const wchar_t* g_pNameA;     // 0x016a0d44  alternate galaxy layout name
extern const wchar_t* g_pNameB;     // 0x016a0d34  default galaxy layout name
extern const wchar_t* g_pUIKeyName; // 0x016a0d24

// @ 0x00de5950
void cGalaxyGameEntryImpl::FUN_00de5950(void)
{
    mLayout144.Init(IsWorldLayoutFlagSet(2) ? g_pNameA : g_pNameB, 0x40464100, 1, 0x5b598fa);

    const uint32_t ids[5] = { 0x615b966, 0x61dd69b, 0x615b616, 0x70d74e7, 0x70d7509 };
    uint32_t i;
    for (i = 0; i < 3; ++i)
        mLayout144.FindWindowByID(ids[i], 1)->w65(this != 0 ? (IWinProc*)&mTree4 : 0);

    if (IsWorldLayoutFlagSet(2)) {
        for (i = 3; i < 5; ++i)
            mLayout144.FindWindowByID(ids[i], 1)->w65(this != 0 ? (IWinProc*)&mTree4 : 0);

        mb271 = 1;
        cPropertyList* pPrefs = g_pAppPreferences;
        GetBoolProperty(pPrefs, 0x8069a6c, (uint8_t*)&mb271);
        if (mb271 != 0) {
            cVariant value;
            value.SetBool(false);
            pPrefs->v14(0x8069a6c, &value);
            if ((value.mnFlags10 & 4) != 0)
                value.Destruct(0);
            SP_SaveResource(pPrefs, SP_GetSaveArea(0x11ac192, 0));
        }
    }

    FUN_00de4910();

    cGlobalUI* pNewUI = (cGlobalUI*)EAllocNew(0x68, "UI/GGE/GlobalUI", 0, 0, 0, 0);
    mpGlobalUI = (pNewUI != 0) ? pNewUI->Construct() : 0;
    mb103 = 1;

    ResKey key;
    key.mHash = FNV1_String16(0x811c9dc5, g_pUIKeyName, 1);
    key.mId = 0x510a95b;
    key.mGroup = 0x40464100;
    if (((cGlobalUI*)mpGlobalUI)->g08(&key)) {
        ((cGlobalUI*)mpGlobalUI)->FindWindowByID(0xffffffff)->w65((IWinProc*)&mTree4);
        Wnd* pOwner = ((cGlobalUI*)mpGlobalUI)->FindWindowByID(0x36c4a10);
        if (pOwner != 0) {
            void* pTarget = pOwner->w04();
            ((Wnd*)pTarget)->w56(pOwner);
        }
    }

    UpdateLoginButton(1);
    FUN_00de41b0();

    Wnd* pLogin = ((cGlobalUI*)mpGlobalUI)->FindWindowByID(0x4810f47);
    if (pLogin != 0) {
        const RectF* pRect = pLogin->w14();
        mf194 = pRect->right - pRect->left;
    }

    Wnd* pConn = ((cGlobalUI*)mpGlobalUI)->FindWindowByID(0x10ed852);
    if (pConn != 0) {
        Wnd* pProcHost = (Wnd*)pConn->w03(0x8ed27e7a);
        if (pProcHost != 0) {
            NetworkActivityProc* pProc =
                (NetworkActivityProc*)EAllocNew(0x34, "UI/NetworkActivityProc", 0, 0, 0, 0);
            pProc = (pProc != 0) ? pProc->Ctor() : 0;
            ((Wnd*)pProcHost->w04())->w65(pProc);
        }
    }

    WindowManager()->w4c(1, WindowManager()->w04());

    if (!AppSystem()->a54()) {
        if (((cGlobalUI*)mpGlobalUI)->FindWindowByID(0x3e30d88) != 0)
            ((cGlobalUI*)mpGlobalUI)->FindWindowByID(0x3e30d88)->w31(1, 0);
    }
}

// @ 0x00de5cb0
bool cGalaxyGameEntryImpl::FUN_00de5cb0(unsigned int a)
{
    cAchievements* c = FUN_00675250(a);
    if (c->FUN_00675e80())
        return true;
    MapItr it;
    MapItr* pIt = mRbTree.find(it, a);
    return pIt->node != (void*)&mRbTree.sentinel;
}

// GUI panel request handed to the asset browser: built by 0x00644b10, torn down by
// 0x00644b60 and launched through 0x0064a990.
struct GuiHandle {
    virtual void h00();
    virtual void h04();          // +0x04  release
    virtual void h08();
    virtual void h0c(int a);     // +0x0c  stop
};
struct RefObj2 {
    virtual void r00();
    virtual void r04();          // +0x04  add reference
    virtual void r08();          // +0x08  destroy
};
struct PanelReq {
    uint32_t m00;                // +0x00
    uint32_t m04;                // +0x04
    uint32_t m08;                // +0x08
    uint32_t m0c;                // +0x0c
    uint8_t  m10;                // +0x10
    uint8_t  mPad11[7];
    uint32_t m18;                // +0x18
    uint32_t m1c;                // +0x1c
    uint32_t m20;                // +0x20
    uint8_t  m24;                // +0x24
    uint8_t  mPad25[0xb];
    uint32_t m30;                // +0x30
    uint32_t m34;                // +0x34
    uint32_t m38;                // +0x38
    uint32_t m3c;                // +0x3c
    RefObj2* mpRef;              // +0x40
    uint32_t m44;                // +0x44

    void __thiscall Ctor(void);  // 0x00644b10
    void __thiscall Dtor(void);  // 0x00644b60
};
// global GUI panel manager (0x016a1344): the open panel handle and a dirty flag
struct GuiPanelMgr {
    char       mPad000[0x1b0];
    GuiHandle* mpHandle;         // +0x1b0
    char       mPad1b4[0x24c - 0x1b4];
    uint8_t    mbDirty;          // +0x24c
};
extern GuiPanelMgr* gGuiPanelMgr;                        // 0x016a1344
void __cdecl LaunchPanel(const PanelReq* pReq);          // 0x0064a990

// @ 0x00de5d00
void __stdcall FUN_00de5d00(uint32_t a1, uint32_t a2, uint32_t a3, const uint32_t* aIds,
                            uint8_t aFlag, uint32_t a6, RefObj2* aRef)
{
    GuiHandle** ppHandle = &gGuiPanelMgr->mpHandle;
    if (*ppHandle != 0) {
        (*ppHandle)->h0c(0);
        if (*ppHandle != 0) {
            GuiHandle* pOld = *ppHandle;
            *ppHandle = 0;
            pOld->h04();
        }
    }
    PanelReq req;
    req.Ctor();
    req.m08 = a3;
    req.m38 = a2;
    req.m00 = a1;
    req.m18 = aIds[0];
    req.m0c = a6;
    req.m1c = aIds[1];
    req.m20 = aIds[2];
    req.m30 = 0xad0e52;
    req.m24 = aFlag;
    req.m10 = 1;
    RefObj2* pOld = req.mpRef;
    if (aRef != pOld) {
        if (aRef != 0)
            aRef->r04();
        req.mpRef = aRef;
        if (pOld != 0)
            pOld->r08();
    }
    gGuiPanelMgr->mbDirty = 1;
    LaunchPanel(&req);
    req.Dtor();
}

// eastl hashtable node and lookup result used by the find-or-insert below
struct HashNode8 {
    uint32_t   mKey;             // +0x00
    HashNode8* mpNext;           // +0x04
};
struct InsertResult8 {
    HashNode8* mpNode;           // +0x00
    void*      mpBucket;         // +0x04
    uint8_t    mbInserted;       // +0x08
};
// rehash decision returned by 0x00921440: when the flag is set the table grows to mCount
struct RehashInfo {
    uint8_t  mbNeedsRehash;      // +0x00
    uint8_t  mPad01[3];
    uint32_t mCount;             // +0x04
};
// rehash policy member at hashtable+0x10
struct RehashPolicy {
    void GetNextRehashInfo(RehashInfo* pOut, uint32_t nBuckets, uint32_t nSize,
                           uint32_t nMinBuckets);                    // 0x00921440
};
struct HashTable34 {
    char        mPad00[4];
    HashNode8** mppBuckets;      // +0x04
    uint32_t    mBucketCount;    // +0x08
    uint32_t    mSize;           // +0x0c
    RehashPolicy mPolicy;        // +0x10

    void DoRehash(uint32_t nCount);                                  // 0x00c764f0
    // retail leaves the result pointer in eax and pops three argument dwords (`ret 0xc`),
    // so the helper returns the result pointer and takes an extra trailing argument.
    InsertResult8* FUN_00de5df0(InsertResult8* pOut, const uint32_t* pKey, uint32_t nReserved); // 0x00de5df0
};

// @ 0x00de5df0
InsertResult8* HashTable34::FUN_00de5df0(InsertResult8* pOut, const uint32_t* pKey,
                                        uint32_t nReserved)
{
    (void)nReserved;
    const uint32_t nKey = *pKey;
    uint32_t nSlot = nKey % mBucketCount;
    HashNode8** ppBucket = &mppBuckets[nSlot];
    HashNode8* pNode = *ppBucket;
    while (pNode != 0) {
        if (pNode->mKey == nKey)
            break;
        pNode = pNode->mpNext;
    }
    if (pNode != 0) {
        pOut->mpNode = pNode;
        pOut->mpBucket = ppBucket;
        pOut->mbInserted = 0;
        return pOut;
    }
    RehashInfo info;
    mPolicy.GetNextRehashInfo(&info, mBucketCount, mSize, 1);
    HashNode8* pNew = (HashNode8*)EAllocNew(8, (const char*)0x13f09b4, 0, 0, (void*)0x13ebb38, 0xd1);
    if (pNew != 0)
        pNew->mKey = *pKey;
    pNew->mpNext = 0;
    if (info.mbNeedsRehash != 0) {
        nSlot = nKey % info.mCount;
        DoRehash(info.mCount);
    }
    pNew->mpNext = mppBuckets[nSlot];
    mppBuckets[nSlot] = pNew;
    mSize++;
    pOut->mpNode = pNew;
    pOut->mpBucket = &mppBuckets[nSlot];
    pOut->mbInserted = 1;
    return pOut;
}

// @ 0x00de5ee0
void __stdcall FUN_00de5ee0(RecBC* p, RecBC* q)
{
    for (; p < q; p++) {
        FreeHeader(p->c);
        FreeHeader(p->b);
        FreeHeader(p->a);
    }
}

// @ 0x00de60f0
cGameData::cGameData(unsigned int p2)
{
    z30 = 0; z34 = 0; z38 = 0; z3c = 0; z40 = 0; z44 = 0;
    z4c = 0; z50 = 0; z54 = 0; z58 = 0; z5c = 0; z60 = 0;
    z64 = 0; z68 = 0; z6c = 0; z70 = 0; z74 = 0; z78 = 0;
    FUN_00b26fb0(p2);
}