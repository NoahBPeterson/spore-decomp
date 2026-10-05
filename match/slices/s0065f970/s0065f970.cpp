// Slice s0065f970: SP UI "feed filter" / "event log" cluster plus the EASTL vector<Key> and
// vector<FeedEntry> helpers that surround it.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
// All functions are present; byte-exact ones are listed in manifest.txt, complete-but-not-exact
// ones in nonmatching.txt and approximate ones in partial.txt.
#include "types.h"

// ---------------------------------------------------------------------------------------------
// EASTL debug allocator.  These are relocations, so only the ABI matters.
// ---------------------------------------------------------------------------------------------
void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int debugFlags, const char* file, int line); // 0x00f473a0
void  __cdecl EASTL_allocator_deallocate(void* p);                                                                                 // 0x00f47380
#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// ---------------------------------------------------------------------------------------------
// UTFWin IWindow.  Only the slots this slice calls are typed; the rest are placeholders that
// keep the byte offsets exact.
// ---------------------------------------------------------------------------------------------
struct IWindow {
    virtual void      s00();                       // +0x00
    virtual int       Release();                   // +0x04
    virtual void      s02();                       // +0x08
    virtual IWindow*  FindWindow(uint32_t id);     // +0x0c
    virtual IWindow*  GetSomething();              // +0x10
    virtual void      s05();                       // +0x14
    virtual void      s06();                       // +0x18
    virtual void      s07();                       // +0x1c
    virtual void      s08();                       // +0x20
    virtual void      s09();                       // +0x24
    virtual uint32_t  GetFlags();                  // +0x28
    virtual void      s11();                       // +0x2c
    virtual void      s12();                       // +0x30
    virtual void      s13();                       // +0x34
    virtual void      s14();                       // +0x38
    virtual void      s15();                       // +0x3c
    virtual void      s16();                       // +0x40
    virtual void      s17();                       // +0x44
    virtual void      s18();                       // +0x48
    virtual void      s19();                       // +0x4c
    virtual void      s20();                       // +0x50
    virtual void      s21();                       // +0x54
    virtual void      s22();                       // +0x58
    virtual void      s23();                       // +0x5c
    virtual void      s24();                       // +0x60
    virtual void      SetLocation(float, float);   // +0x64
    virtual void      s26();                       // +0x68
    virtual void      s27();                       // +0x6c
    virtual void      s28();                       // +0x70
    virtual void      s29();                       // +0x74
    virtual void      s30();                       // +0x78
    virtual void      SetFlag(int, bool);          // +0x7c
    virtual void      s32();                       // +0x80
    virtual void      s33();                       // +0x84
    virtual void      s34();                       // +0x88
    virtual void      s35();                       // +0x8c
    virtual void      s36();                       // +0x90
    virtual void      s37();                       // +0x94
    virtual void      s38();                       // +0x98
    virtual void      s39();                       // +0x9c
    virtual void      s40();                       // +0xa0
    virtual void      s41();                       // +0xa4
    virtual void      s42();                       // +0xa8
    virtual void      s43();                       // +0xac
    virtual void      s44();                       // +0xb0
    virtual void      s45();                       // +0xb4
    virtual void      s46();                       // +0xb8
    virtual void      s47();                       // +0xbc
    virtual void      s48();                       // +0xc0
    virtual void      s49();                       // +0xc4
    virtual void      s50();                       // +0xc8
    virtual void      s51();                       // +0xcc
    virtual void      s52();                       // +0xd0
    virtual void      s53();                       // +0xd4
    virtual void      s54();                       // +0xd8
    virtual void      s55();                       // +0xdc
    virtual void      s56(IWindow* w);             // +0xe0
    virtual void      s57();                       // +0xe4
    virtual void      s58();                       // +0xe8
    virtual void      s59();                       // +0xec
    virtual IWindow*  FindWindowByID(uint32_t id, bool recurse);  // +0xf0
    virtual void      s61();                       // +0xf4
    virtual void      s62();                       // +0xf8
    virtual void      s63();                       // +0xfc
    virtual void      s64();                       // +0x100
    virtual void      SetReloadCallback(void* p);  // +0x104
    virtual void      AttachProc(void* p);         // +0x108
};

// IButton: only slot 0x28 differs (SetStateFlag(int, bool)).
struct IButton {
    virtual void      b00();
    virtual int       b01();
    virtual void      b02();
    virtual void      b03();
    virtual void      b04();
    virtual void      b05();
    virtual void      b06();
    virtual void      b07();
    virtual void      b08();
    virtual void      b09();
    virtual void      SetStateFlag(int flag, bool v);   // +0x28
};

// cSPUILayout (0x18 bytes retail).
struct cSPUILayout {
    virtual void s0();
    virtual void s1();
    virtual int  Release();                                       // +0x08
    void Shutdown(bool);                                          // 0x00811ad0
    IWindow* FindWindowByID(uint32_t id, bool recurse);           // 0x008105b0
    char pad[0x18 - 4];
};

// EA::Messaging / SPUIHelpers
void __cdecl EA_RemoveHandler(void* h, uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // 0x00571db0
IWindow* __cdecl SPUIHelpers_SetWindowAreaToParent(IWindow* w);                          // 0x00806bf0
float __cdecl SPUIHelpers_GetElapsedSeconds(float t, int a, void* w, int b);             // 0x00805080
void __cdecl SPUIHelpers_SetWindowScale(IWindow* w, float s);                            // 0x00808210
void __cdecl SPUIHelpers_SetWindowAlpha(IWindow* w, float a);                            // 0x00804fc0

// ---------------------------------------------------------------------------------------------
// 0x0065f970 / 0x0065f9e0 : class holding a counter, a selected index, a root pointer and four
// window pointers.
// ---------------------------------------------------------------------------------------------
struct FeedFilterA {
    int m0;              // +0x00
    int m4;              // +0x04
    IWindow* m8;         // +0x08
    IWindow* mWin[4];    // +0x0c
    void Update4();      // 0x0065f970
    ~FeedFilterA();      // 0x0065f9e0
};

// @ 0x0065f970
void FeedFilterA::Update4() {
    int n = m0 - 1;
    for (int i = 0; i < 4; ++i) {
        IWindow* w = mWin[i];
        if (w) {
            w->SetFlag(1, i <= n);
            IWindow* q = mWin[i]->FindWindowByID(0x5d0dd57a, 0);
            if (q) q->SetFlag(1, i == m4);
        }
    }
}

// @ 0x0065f9e0
FeedFilterA::~FeedFilterA() {
    IWindow** p = mWin + 4;
    int i = 3;
    for (; i >= 0; --i) {
        IWindow* q = *--p;
        if (q) q->Release();
    }
    IWindow* z = m8;
    if (z) z->Release();
}

// ---------------------------------------------------------------------------------------------
// 0x0065fa20 / 0x0065faa0 : feed-filter UI object with a layout at +0x64, four windows at
// +0x6c..+0x78 and an auto message handler at +0x7c.
// ---------------------------------------------------------------------------------------------
struct FeedFilterB {
    char pad00[0x64];
    cSPUILayout* mLayout;      // +0x64
    char pad68[4];
    IWindow* mWin6c;           // +0x6c
    IWindow* mWin70;           // +0x70
    IWindow* mWin74;           // +0x74
    IWindow* mWin78;           // +0x78
    void* mHandler;            // +0x7c
    uint32_t mA80;             // +0x80
    uint32_t mA84;             // +0x84
    uint32_t mA88;             // +0x88
    uint32_t mA8c;             // +0x8c
    void Shutdown();
};

// @ 0x0065fa20
void FeedFilterB::Shutdown() {
    if (mLayout) {
        mLayout->Shutdown(true);
        cSPUILayout* p = mLayout;
        if (p) { mLayout = 0; p->Release(); }
    }
    if (mHandler) {
        void* h = mHandler;
        uint32_t a = mA80, b = mA84, c = mA88, d = mA8c;
        mHandler = 0;
        EA_RemoveHandler(h, a, b, c, d);
    }
}

// @ 0x0065faa0
void __cdecl cSPUIFeedFilter_ReloadCallback(FeedFilterB* self, void* a, char b) {
    if (b == 0) {
        if (self->mWin6c) {
            self->mWin6c->AttachProc(self);
        }
        return;
    }
    IWindow* w = self->mLayout->FindWindowByID(0xb435a20d, true);
    IWindow* old = self->mWin6c;
    if (w != old) {
        if (w) w->s00();
        self->mWin6c = w;
        if (old) old->Release();
    }
    w = self->mLayout->FindWindowByID(0xb435a20c, true);
    old = self->mWin70;
    if (w != old) {
        if (w) w->s00();
        self->mWin70 = w;
        if (old) old->Release();
    }
    w = self->mLayout->FindWindowByID(0x12f66831, true);
    old = self->mWin74;
    if (w != old) {
        if (w) w->s00();
        self->mWin74 = w;
        if (old) old->Release();
    }
    w = self->mLayout->FindWindowByID(0x642a948, true);
    old = self->mWin78;
    if (w != old) {
        if (w) w->s00();
        self->mWin78 = w;
        if (old) old->Release();
    }
    if (self->mWin6c) {
        self->mWin6c->SetReloadCallback(self);
        SPUIHelpers_SetWindowAreaToParent(self->mWin6c);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x0065fbc0 : clone of a 0x14-byte node that owns a refcounted pointer at +0x0c.
// ---------------------------------------------------------------------------------------------
struct RC {
    virtual int AddRef();      // +0x00
    virtual int Release();     // +0x04
};
struct RC4 {
    virtual void s0();
    virtual int  AddRef4();    // +0x04
};

struct Node14 {
    uint32_t a, b, c;
    RC4* d;
    uint32_t e;
};

// @ 0x0065fbc0
Node14* __stdcall CloneNode14(const Node14* src) {
    Node14* p = (Node14*)EASTL_allocator_allocate(0x14, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
    if (p) {
        p->a = src->a;
        p->b = src->b;
        p->c = src->c;
        p->d = src->d;
        if (p->d) p->d->AddRef4();
    }
    p->e = 0;
    return p;
}

// ---------------------------------------------------------------------------------------------
// 0x0065fcd0 / 0x006603d0 : 0x24-byte window/area record copy.
// ---------------------------------------------------------------------------------------------
struct AreaRec {
    uint32_t m0;                 // +0x00
    RC* mRef;                    // +0x04
    uint8_t m8;                  // +0x08
    uint8_t m9;                  // +0x09
    char pad0a[2];
    float f0c, f10, f14, f18;    // +0x0c
    uint32_t m1c;                // +0x1c
    uint32_t m20;                // +0x20
    AreaRec(const AreaRec& o);
    AreaRec* AssignChecked(const uint32_t* head, const void* inner);   // 0x006603d0
};
struct AreaInner {
    RC* ref;                 // +0x00
    uint8_t b4;              // +0x04
    uint8_t b5;              // +0x05
    char pad6[2];
    float f8, f0c, f10, f14;
    uint32_t m18, m1c;
};

// @ 0x0065fcd0
AreaRec::AreaRec(const AreaRec& o) {
    m0 = o.m0;
    mRef = o.mRef;
    if (mRef) mRef->AddRef();
    m8 = o.m8;
    m9 = o.m9;
    f0c = o.f0c;
    f10 = o.f10;
    f14 = o.f14;
    f18 = o.f18;
    m1c = o.m1c;
    m20 = o.m20;
}

// @ 0x006603d0
AreaRec* AreaRec::AssignChecked(const uint32_t* head, const void* innerPtr) {
    const AreaInner* o = (const AreaInner*)innerPtr;
    m0 = *head;
    mRef = o->ref;
    if (mRef) mRef->AddRef();
    m8 = o->b4;
    m9 = o->b5;
    f0c = o->f8;
    f10 = o->f0c;
    f14 = o->f10;
    f18 = o->f14;
    m1c = o->m18;
    m20 = o->m1c;
    return this;
}

// ---------------------------------------------------------------------------------------------
// EASTL Key / vector<Key> / vector<FeedEntry> helpers.
// ---------------------------------------------------------------------------------------------
struct Key {
    uint32_t mInstance;    // +0x00
    uint32_t mType;        // +0x04
    uint32_t mGroup;       // +0x08
};

Key*  __cdecl KeyLowerBound(Key* first, Key* last, const Key* key);   // 0x00660430
bool  __cdecl KeyContains(Key* first, Key* last, const Key* key);     // 0x00660650

// @ 0x00660430
Key* __cdecl KeyLowerBound(Key* first, Key* last, const Key* key) {
    int n = (int)((char*)last - (char*)first) / 0xc;
    while (n > 0) {
        int half = n >> 1;
        Key* mid = (Key*)((char*)first + half * 0xc);
        bool less = mid->mInstance < key->mInstance;
        if (mid->mInstance == key->mInstance) {
            less = mid->mGroup < key->mGroup;
            if (mid->mGroup == key->mGroup)
                less = mid->mType < key->mType;
        }
        if (less) {
            first = (Key*)((char*)mid + 0xc);
            n -= half + 1;
        } else {
            n = half;
        }
    }
    return first;
}

// @ 0x00660650
bool __cdecl KeyContains(Key* first, Key* last, const Key* key) {
    Key* it = KeyLowerBound(first, last, key);
    if (it == last) return false;
    bool less = key->mInstance < it->mInstance;
    if (key->mInstance == it->mInstance) {
        less = key->mGroup < it->mGroup;
        if (key->mGroup == it->mGroup)
            less = key->mType < it->mType;
    }
    return !less;
}

struct KeyVec {
    Key* mBegin;    // +0x00
    Key* mEnd;      // +0x04
    Key* mCap;      // +0x08
    KeyVec& operator=(const KeyVec& o);
};

void  __cdecl CopyOverlap(Key* first, Key* last, Key* dest);   // 0x00b84c80
void  __cdecl UninitCopyPtr(void** out, void* first, void* last, void* dest, void* extra);  // 0x00512050
Key*  __cdecl KeyVecAlloc(uint32_t n, Key* first, Key* last);  // 0x006604b0

// @ 0x006609a0
KeyVec& KeyVec::operator=(const KeyVec& o) {
    if (&o == this) return *this;
    uint32_t n = (uint32_t)(o.mEnd - o.mBegin);
    if ((uint32_t)(mCap - mBegin) < n) {
        Key* p = KeyVecAlloc(n, o.mBegin, o.mEnd);
        if (mBegin) {
            if (*(int*)((char*)mBegin - 4) != 0)
                EASTL_allocator_deallocate(mBegin);
        }
        mCap = p + n;
        mBegin = p;
        mEnd = p + n;
        return *this;
    }
    uint32_t have = (uint32_t)(mEnd - mBegin);
    if (have < n) {
        CopyOverlap(o.mBegin, o.mEnd, mBegin);
        void* last = o.mEnd;
        UninitCopyPtr((void**)&last, o.mBegin + have, o.mEnd, mEnd, mEnd);
        mEnd = mBegin + n;
        return *this;
    }
    CopyOverlap(mBegin, o.mEnd, mBegin);
    mEnd = mBegin + n;
    return *this;
}

// FeedEntry (0x34 bytes): id + flag + two sorted Key vectors.
struct FeedEntry {
    uint32_t m0;             // +0x00
    bool     m4;             // +0x04
    char     pad05[3];
    KeyVec   v08;            // +0x08
    char     pad14[8];
    bool     m1c;            // +0x1c
    char     pad1d[3];
    KeyVec   v20;            // +0x20
    char     pad2c[8];
};

// @ 0x00660ad0
FeedEntry* __cdecl FeedRangeConstruct(FeedEntry** out, FeedEntry* first, FeedEntry* last, FeedEntry* p) {
    *out = p;
    while (first != last) {
        if (*out) {
            (*out)->m0 = first->m0;
            (*out)->m4 = first->m4;
            (*out)->v08 = first->v08;
            (*out)->m1c = first->m1c;
            (*out)->v20 = first->v20;
        }
        ++first;
        ++*out;
    }
    return *out;
}

// @ 0x00660b30
FeedEntry* __cdecl FeedUninitCopy(FeedEntry* first, FeedEntry* last, FeedEntry* dest) {
    while (first != last) {
        if (dest) {
            dest->m0 = first->m0;
            dest->m4 = first->m4;
            dest->v08 = first->v08;
            dest->m1c = first->m1c;
            dest->v20 = first->v20;
        }
        ++first;
        ++dest;
    }
    return dest;
}

// @ 0x00660d70
FeedEntry* __cdecl FeedRangeAssign(FeedEntry* first, FeedEntry* last, FeedEntry* dest) {
    while (first != last) {
        dest->m0 = first->m0;
        dest->m4 = first->m4;
        dest->v08 = first->v08;
        dest->m1c = first->m1c;
        dest->v20 = first->v20;
        ++first;
        ++dest;
    }
    return dest;
}

// @ 0x00660510
FeedEntry* __cdecl FeedDestroyRange(FeedEntry* first, FeedEntry* last, FeedEntry* out) {
    while (first != last) {
        void* p = *(void**)((char*)first + 0x20);
        if (p && *(int*)((char*)p - 4) != 0)
            EASTL_allocator_deallocate(p);
        void* q = *(void**)((char*)first + 0x08);
        if (q && *(int*)((char*)q - 4) != 0)
            EASTL_allocator_deallocate(q);
        ++first;
        ++out;
    }
    return out;
}

// ---------------------------------------------------------------------------------------------
// Key provider interface (slots 0x24 and 0x40 of the object passed to 0x00660880).
// ---------------------------------------------------------------------------------------------
struct KeyProvider {
    virtual void     k00(); virtual void k01(); virtual void k02(); virtual void k03();
    virtual void     k04(); virtual void k05(); virtual void k06(); virtual void k07();
    virtual uint32_t k08();                       // +0x20
    virtual uint32_t k09();                       // +0x24
    virtual void     k10(); virtual void k11(); virtual void k12(); virtual void k13();
    virtual void     k14();
    virtual uint32_t k15();                       // +0x3c
    virtual uint32_t k16();                       // +0x40
};

// @ 0x00660880
struct FeedOwner {
    char pad00[0x1c];
    KeyVec mOther;    // +0x1c
    char pad28[8];
    KeyVec mMain;     // +0x30
    bool Matches(KeyProvider* p, char useOther);
};

// @ 0x00660880
bool FeedOwner::Matches(KeyProvider* p, char useOther) {
    KeyVec* vec = useOther ? &mOther : &mMain;
    if (p == 0) return true;
    uint32_t key = p->k09();
    int count = (int)(vec->mEnd - vec->mBegin) / 0x34;
    for (int i = 0; i < count; ++i) {
        FeedEntry* e = (FeedEntry*)((char*)vec->mBegin + i * 0x34);
        if (e->m0 != key) continue;
        bool bad = false;
        if (e->m4) {
            uint32_t first = *(uint32_t*)((char*)e + 0x08);
            uint32_t last  = *(uint32_t*)((char*)e + 0x0c);
            uint32_t k = p->k16();
            if (!KeyContains((Key*)first, (Key*)last, (Key*)k)) bad = true;
        }
        if (!e->m1c) {
            if (!bad) return false;
        } else if (!bad) {
            uint32_t first = *(uint32_t*)((char*)e + 0x20);
            uint32_t last  = *(uint32_t*)((char*)e + 0x24);
            uint32_t k = p->k16();
            if (KeyContains((Key*)first, (Key*)last, (Key*)k)) return false;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// 0x00660360 : visibility/lock sweep over the map.
// ---------------------------------------------------------------------------------------------
struct FeedTreeNode {
    char pad00[0x14];
    IWindow* mWin;     // +0x14
};
void* __cdecl RBTreeIncrement(void* n);   // 0x00921580

struct FeedFilterC {
    char pad[0xa0];
    FeedTreeNode* mEnd;    // +0xa0
    FeedTreeNode* mBegin;  // +0xa4
    void LockFilterUI(bool locked);
};

// @ 0x00660360
void FeedFilterC::LockFilterUI(bool locked) {
    for (FeedTreeNode* it = mBegin; it != (FeedTreeNode*)&mEnd; it = (FeedTreeNode*)RBTreeIncrement(it)) {
        IWindow* w = it->mWin;
        if (w) {
            w->SetFlag(0x10, locked);
            w = it->mWin;
            if (w) {
                IWindow* b = w->FindWindow(0x8ed27e7a);
                if (b) ((IButton*)b)->SetStateFlag(1, !locked);
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00660b90 : clear the map and reset the anchor.
// ---------------------------------------------------------------------------------------------
void __cdecl TreeNodeDtor(FeedTreeNode* n);   // 0x00d0c930
struct TreeStub { void dtorSubtree(FeedTreeNode* root); };

struct FeedFilterD {
    char pad[0xa0];
    FeedTreeNode* mEnd;    // +0xa0
    FeedTreeNode* mBegin;  // +0xa4
    FeedTreeNode* mRoot;   // +0xa8
    bool mAc;              // +0xac
    char padAd[3];
    uint32_t mB0;          // +0xb0
    void Clear();
};

// @ 0x00660b90
void FeedFilterD::Clear() {
    for (FeedTreeNode* it = mBegin; it != (FeedTreeNode*)&mEnd; it = (FeedTreeNode*)RBTreeIncrement(it)) {
        IWindow* w = it->mWin;
        if (w) {
            IWindow* q = w->GetSomething();
            q->s56(w);
        }
    }
    ((TreeStub*)((char*)this + 0x9c))->dtorSubtree(mRoot);
    mBegin = mEnd;
    mRoot = 0;
    mAc = false;
    mB0 = 0;
    *(FeedTreeNode**)mEnd = mEnd;
}

// ---------------------------------------------------------------------------------------------
// 0x006600c0 : cSPUIFeedFilter::GetSupportedFilterTypes (behavioural reconstruction).
// ---------------------------------------------------------------------------------------------
struct GeneralProperty {
    virtual void p00();
    virtual void p01();
    virtual void p02();
    virtual void p03();
    virtual void p04();
    virtual void p05();
    virtual void p06();
    virtual void p07();
    virtual void p08();
    virtual void p09();
    virtual void p10();
    virtual void p11();
    virtual void GetProperty(int* out, uint32_t key, uint32_t type);   // +0x2c
};

GeneralProperty* __cdecl SP_PropertyManager();                                   // 0x0067de30
void  __cdecl SP_GetPropertyAsKeyInstance(void* a, uint32_t b, void* c);         // 0x006a12a0
void* __cdecl MakeFilterValue(void* self, int a, uint32_t b);                 // 0x0066a5e0
void* __cdecl GetFilterButton(int index);                                        // 0x0066a800
bool  __cdecl FilterVecReserve(void* vec, uint32_t key, void* a, void* b);       // 0x006a0ae0

extern uint32_t g_feedKey1;   // 0x0140042c
extern uint32_t g_feedKey2;   // 0x0140041c
extern void*    g_feedTable[24];  // 0x01400480

struct FilterValue {
    int      gap0;       // +0x00
    uint16_t kind12;     // +0x12
    uint8_t  flags10;    // +0x10
    uint8_t  value21;    // +0x21
    uint8_t  isOne24;    // +0x24
    int      state9;     // +0x24
};

// @ 0x006600c0
void __cdecl cSPUIFeedFilter_GetSupportedFilterTypes(char* self, int param) {
    void* local = 0;
    GeneralProperty* pm = SP_PropertyManager();
    pm->GetProperty((int*)&local, 0xcc489c6f, param);
    if (!local) return;
    if (*(int*)(self + 0x18) == param) {
        void* src = MakeFilterValue(&local, 1, 0x4543c5ec);
        int* dst = (int*)(self + 0x44);
        for (int i = 0; i < 8; ++i) dst[i] = ((int*)src)[i];
        for (int off = 0; off < 0x18; ++off) {
            void* btn = GetFilterButton(off);
            if (!btn) {
                dst[off] = 0;
            } else {
                ((void(__thiscall*)(void*))((*(void***)btn)[1]))(btn);
                *(char*)((char*)dst + off) = (*(int*)((char*)btn + 0x24) != 1);
                ((void(__thiscall*)(void*))((*(void***)btn)[2]))(btn);
            }
        }
        SP_GetPropertyAsKeyInstance(local, 0xb39914fa, self + 0x5c);
    }
    MakeFilterValue(&local, 1, 0x4543c5ec);
    int count = 0;
    char* stack = 0;
    bool ok = FilterVecReserve(local, 0x7435a2d3, &count, &stack);
    char* base = (char*)&count;
    if (ok) {
        for (int i = 0; i < 0x18; ++i) {
            void* btn = GetFilterButton(i);
            if (!btn) continue;
            ((void(__thiscall*)(void*))((*(void***)btn)[1]))(btn);
            *((char*)&local + i) = *(char*)((char*)btn + 0x21);
            if (local) {
                bool c = ((bool(__thiscall*)(void*, void*, void*))((*(void***)local)[9]))(
                    local, g_feedTable[i], base);
                if (c && *(uint16_t*)(base + 0x12) == 1) {
                    void* v = base;
                    if ((*(uint8_t*)(base + 0x10) & 0x30) != 0) v = *(void**)base;
                    *((char*)&local + i) = *(char*)v;
                }
            }
            int st = *(int*)((char*)btn + 0x24);
            if (st == 0) {
                if (*(char*)(self + 0x44 + i) != 0 && *((char*)&local + i) != 0)
                    *(char*)(self + 0x44 + i) = 1;
                else
                    *(char*)(self + 0x44 + i) = 0;
            } else if (st == 1) {
                if (*(char*)(self + 0x44 + i) == 0 && *((char*)&local + i) != 0)
                    *(char*)(self + 0x44 + i) = 1;
                else
                    *(char*)(self + 0x44 + i) = 0;
            }
            ((void(__thiscall*)(void*))((*(void***)btn)[2]))(btn);
        }
    } else {
        for (int i = 0; i < 0x18; ++i) {
            if (local) {
                bool c = ((bool(__thiscall*)(void*, void*, void*))((*(void***)local)[9]))(
                    local, g_feedTable[i], base);
                if (c && *(uint16_t*)(base + 0x12) == 1) {
                    void* v = base;
                    if ((*(uint8_t*)(base + 0x10) & 0x30) != 0) v = *(void**)base;
                    *((char*)&local + i) = *(char*)v;
                    void* btn = GetFilterButton(i);
                    if (btn) {
                        ((void(__thiscall*)(void*))((*(void***)btn)[1]))(btn);
                        int st = *(int*)((char*)btn + 0x24);
                        if (st == 0) {
                            if (*(char*)(self + 0x44 + i) != 0 && *((char*)&local + i) != 0)
                                *(char*)(self + 0x44 + i) = 1;
                            else
                                *(char*)(self + 0x44 + i) = 0;
                        } else if (st == 1) {
                            if (*(char*)(self + 0x44 + i) == 0 && *((char*)&local + i) != 0)
                                *(char*)(self + 0x44 + i) = 1;
                            else
                                *(char*)(self + 0x44 + i) = 0;
                        }
                        ((void(__thiscall*)(void*))((*(void***)btn)[2]))(btn);
                    }
                }
            }
        }
        for (int i = 0; i < count; ++i) {
            void* entry = *(void**)((char*)base + i * 0xc);
            cSPUIFeedFilter_GetSupportedFilterTypes(self, (int)entry);
        }
    }
    if (local) ((void(__thiscall*)(void*))((*(void***)local)[1]))(local);
}

// ---------------------------------------------------------------------------------------------
// 0x0065fd30 : cSPUIEventLog::DoMessage (behavioural reconstruction of the animation sweep).
// ---------------------------------------------------------------------------------------------
struct EventNode {
    char pad00[0x14];
    IWindow* mWin;   // +0x14
    bool b18;        // +0x18
    bool b19;        // +0x19
    char pad1a[2];
    float f1c, f20, f24, f28;
};

struct EventLog {
    char pad[0xa0];
    EventNode* mEnd;    // +0xa0
    EventNode* mBegin;  // +0xa4
    void DoMessage();
};

struct cSPUIAnimator {
    void RemoveAnimation(IWindow* w, int idx);   // 0x007f6210
    void AddAnimation(void* target);             // 0x007f8d10
};
cSPUIAnimator* __cdecl GetAnimator();            // 0x00401030 + [0x14]
void* __cdecl CreateTargetPosition(void* p, IWindow* w);      // 0x007f80d0
void* __cdecl CreateTargetScale(void* p, IWindow* w);         // 0x007f81d0
void* __cdecl CreateTargetShadeAlpha(void* p, IWindow* w);    // 0x007f8290

static cSPUIAnimator* CurrentAnimator() {
    char* browser = (char*)GetAnimator();
    if (!browser) return 0;
    return *(cSPUIAnimator**)(browser + 0x14);
}

// @ 0x0065fd30
void EventLog::DoMessage() {
    for (EventNode* it = mBegin; it != (EventNode*)&mEnd; it = (EventNode*)RBTreeIncrement(it)) {
        IWindow* win = it->mWin;
        if (it->b18) {
            if (!win) continue;
            IButton* btn = (IButton*)win->FindWindow(0x8ed27e7a);
            if (btn) {
                if (it->b19) {
                    btn->SetStateFlag(4, true);
                    btn->SetStateFlag(0x20, true);
                } else {
                    btn->SetStateFlag(4, false);
                }
            }
            float x = it->f24 + it->f1c;
            float y = it->f28 + it->f20;
            cSPUIAnimator* anim = CurrentAnimator();
            if (!anim) {
                SPUIHelpers_SetWindowScale(win, 1.0f);
                SPUIHelpers_SetWindowAlpha(win, 1.0f);
                win->SetLocation(x, y);
            } else {
                anim->RemoveAnimation(win, -1);
                if (!(win->GetFlags() & 0x10)) {
                    float t = SPUIHelpers_GetElapsedSeconds(0.5f, 3, win, 1);
                    float pos[3] = { x, y, t };
                    anim->AddAnimation(CreateTargetPosition(pos, win));
                } else {
                    win->SetLocation(x, y);
                }
                float t2 = SPUIHelpers_GetElapsedSeconds(0.5f, 2, win, 0);
                float sc[3] = { 1.0f, 0.0f, t2 };
                anim->AddAnimation(CreateTargetScale(sc, win));
                float t3 = SPUIHelpers_GetElapsedSeconds(0.5f, 0, win, 2);
                float sh[3] = { 255.0f, 0.0f, t3 };
                anim->AddAnimation(CreateTargetShadeAlpha(sh, win));
            }
            win->SetFlag(0x10, false);
        } else {
            if (!win) continue;
            win->SetFlag(0x10, true);
            cSPUIAnimator* anim = CurrentAnimator();
            if (!anim) {
                SPUIHelpers_SetWindowScale(win, 0.0078125f);
                SPUIHelpers_SetWindowAlpha(win, 0.0f);
            } else {
                anim->RemoveAnimation(win, -1);
                float t = SPUIHelpers_GetElapsedSeconds(0.5f, 1, win, 0);
                float sc[3] = { 0.0078125f, 0.0f, t };
                anim->AddAnimation(CreateTargetScale(sc, win));
                float t2 = SPUIHelpers_GetElapsedSeconds(0.5f, 0, win, 2);
                float sh[3] = { 0.0f, 0.0f, t2 };
                anim->AddAnimation(CreateTargetShadeAlpha(sh, win));
            }
            win->SetFlag(0x10, false);
        }
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00660c10 : texture-instance map find-or-insert (behavioural reconstruction).
// ---------------------------------------------------------------------------------------------
void  __cdecl HashFind(void* self, void* out, const void* key);       // 0x00833840
void  __cdecl HashInsertKey(void* self, void* a, void* b, void* c);   // 0x00660570

struct HashCtx {
    char pad04[4];
    void** mBuckets;   // +0x04
    int    mBucket;    // +0x08
    void* find(void* out, const Key* key) {
        char findResult[0x0c];
        HashFind(this, findResult, key);
        void* it = *(void**)findResult;
        if (it != mBuckets[mBucket])
            return (char*)it + 0x0c;
        Key tmp = *key;
        int isNew = 0;
        HashInsertKey(this, &tmp, (void*)&isNew, 0);
        return (char*)it + 0x0c;
    }
};

// @ 0x00660c10
void* __cdecl TexMapFindOrInsert(HashCtx* self, const Key* key) {
    return self->find(0, key);
}
