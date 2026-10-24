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

// Handle / manager interfaces used by the game-entry handle wrappers.
struct cGalaxyHandle {
    virtual void h0();              // vtbl+0x00
    virtual void hRelease();        // vtbl+0x04
    virtual void hStart(int a);     // vtbl+0x08
    virtual void hStop(int a);      // vtbl+0x0c
};

struct cGalaxyManager {
    virtual void m0();                                // vtbl+0x00
    virtual void m1();                                // vtbl+0x04
    virtual bool mAdd(unsigned int id, int a, void** out); // vtbl+0x08
    virtual void m3();                                // vtbl+0x0c
};

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

    MapItr  find(const unsigned int& key);   // 0x00e5c780
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

struct cGalaxyGameEntryImpl {
    char    mPad00[0x04];
    RbTree57 mTree4;            // +0x04
    char    mPad18[0x38 - 0x18];
    RbFind56 mRb38;             // +0x38
    char    mPad44[0x10c - 0x44];
    int     mCurrentDword;      // +0x10c
    char*   mBegin;             // +0x110
    char*   mEnd;               // +0x114
    char    mPad118[0x15c - 0x118];
    void*   mpManager;          // +0x15c
    char    mPad160[0x174 - 0x160];
    void*   mpHandleA;          // +0x174
    char    mPad178[0x1b0 - 0x178];
    void*   mpHandleB;          // +0x1b0
    char    mPad1b4[0x1f5 - 0x1b4];
    char    mFlag1f5;           // +0x1f5
    char    mPad1f6[0x254 - 0x1f6];
    RBTreeThing mRbTree;        // +0x254

    void  UpdateLoginButton(void);      // 0x00de5040
    void  FUN_00de5260(void);           // 0x00de5260
    void  FUN_00de52d0(void);           // 0x00de52d0
    void  FUN_00de5300(void);           // 0x00de5300
    void  FUN_00de5330(char p);         // 0x00de5330
    void  FUN_00de53d0(char p);         // 0x00de53d0
    void  ShowGalaxy(void);             // 0x00de5470
    OutKey3* FUN_00de56f0(OutKey3& pOut, KeyNode* key); // 0x00de56f0
    void  FUN_00de57b0(RbNode57** pOut, RbNode57* parent, Key2* key, char flag); // 0x00de57b0
    void  FUN_00de5950(void);           // 0x00de5950
    bool  FUN_00de5cb0(unsigned int a); // 0x00de5cb0
    void  FUN_00de5d00(void);           // 0x00de5d00
    void  FUN_00de5df0(void);           // 0x00de5df0
};

// ===========================================================================

// @ 0x00de5040
void cGalaxyGameEntryImpl::UpdateLoginButton(void)
{
    /* large login-button update; not reconstructed */
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
    char* b = mBegin;
    if (b != mEnd) {
        mCurrentDword = *(int*)(mEnd - 4);
        mEnd -= 4;
        return;
    }
    mCurrentDword = 2;
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

// @ 0x00de5470
void cGalaxyGameEntryImpl::ShowGalaxy(void)
{
    /* large show-galaxy method; not reconstructed */
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
    *pOut = node;
    mTree4.count++;
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

// @ 0x00de5950
void cGalaxyGameEntryImpl::FUN_00de5950(void)
{
    /* large helper; not reconstructed */
}

// @ 0x00de5cb0
bool cGalaxyGameEntryImpl::FUN_00de5cb0(unsigned int a)
{
    cAchievements* c = FUN_00675250(a);
    if (c->FUN_00675e80())
        return true;
    MapItr it = mRbTree.find(a);
    return it.node != (void*)&mRbTree.sentinel;
}

// @ 0x00de5d00
void cGalaxyGameEntryImpl::FUN_00de5d00(void)
{
    /* not reconstructed */
}

// @ 0x00de5df0
void cGalaxyGameEntryImpl::FUN_00de5df0(void)
{
    /* not reconstructed */
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