// Slice s00ed2600 -- Simulator palette/UI container glue.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

extern char* g_16c757c;   // 0x016c757c
extern char* g_16c7584;   // 0x016c7584
extern char* g_16c7aa4;   // 0x016c7aa4

extern unsigned g_015da7c4; // 0x015da7c4
extern unsigned g_015da7c8; // 0x015da7c8
extern unsigned g_015da7cc; // 0x015da7cc
extern unsigned g_015da7d0; // 0x015da7d0

// ---------------------------------------------------------------- callees
void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int);  // 0xf473a0
void  __cdecl operator_delete(void*);                                           // 0xf47380
void  __cdecl FUN_00ed1f00_v(void*);
int   __stdcall FUN_00ed1f00(void*, int);                                         // 0xed1f00
void* __cdecl FUN_00ed1f40_v(void*, void*);
void  __cdecl FUN_00ed3120_v(void*, int, int);
int   __cdecl FUN_00f3c7f0_v(void*);
int   __cdecl FUN_00f280f0_v(void*);

void* __cdecl eastl_RBTreeIncrement(void*);              // 0x00921580
void  __cdecl eastl_RBTreeErase(void*, void*);           // 0x00921880
void  __cdecl eastl_RBTreeInsert(void*, void*, void*, int); // 0x009216a0
void* __cdecl eastl_RBTreeDecrement(void*);              // 0x009215c0

void  __cdecl RemoveHandler(void*, int, int, int, int);  // 0x00571db0
void* __cdecl FUN_006447c0(int, void**);                 // 0x006447c0
void* __fastcall FUN_00644b10(void*, int);               // 0x00644b10
int   __cdecl GetCurrentGameMode();                      // 0x00b5b800
void  __cdecl FUN_0064a990(void*);                       // 0x0064a990
void  __fastcall ShutdownPaletteUI(void*, int);          // 0x005cba90
void  __fastcall ShutdownPalette(void*, int);            // 0x005c5c20
struct CallbackObj { void Cancel(); };                   // 0x00929c60 (thiscall, 0 args)

struct Singleton;

// ---------------------------------------------------------------- rbtree bits
struct RBNode {
    RBNode*  mpLeft;   // +0x00
    RBNode*  mpRight;  // +0x04
    RBNode*  mpParent; // +0x08
    unsigned mColor;   // +0x0c
    void*    mpValue;  // +0x10
};

struct MapInsertResult {
    RBNode* mpNode;    // +0x00
    char    mbNew;     // +0x04
    char    mPad05[3];
};

struct RefMap {
    unsigned mPad00;   // +0x00
    RBNode*  mAnchor;  // +0x04  (tree sentinel; &mAnchor is the anchor node)
    RBNode*  mBegin;   // +0x08
    RBNode*  mRoot;    // +0x0c
    char     mColor;   // +0x10
    char     mPad11[3];
    int      mSize;    // +0x14
    void Nuke(RBNode* node);                                              // 0x00ed2a10
    void Insert(MapInsertResult* result, void** key, int flag);           // 0x00ed2b30
    void InsertUnique(void** result, RBNode* pos, void** key, char flag);  // 0x00ed2a50
    void Erase(void** result, RBNode* node);                              // 0x00ed2ae0
};

// ---------------------------------------------------------------- vtable views
struct RefVtbl {
    void (__thiscall* mSlot00)(void*, int); // +0x00
    void (__thiscall* mSlot04)(void*);      // +0x04
    void (__thiscall* mSlot08)(void*);      // +0x08
    void (__thiscall* mSlot0c)(void*);      // +0x0c
};
struct RefObj { RefVtbl* mpVtbl; };

struct HandlerVtbl {
    void  (__thiscall* mDestroy)(void*, int);      // +0x00
    void  (__thiscall* mRelease)(void*);           // +0x04
    void  (__thiscall* mReleaseAlt)(void*);        // +0x08
    void* (__thiscall* mLookup)(void*, unsigned);  // +0x0c
    void  (__thiscall* mSlot10)(void*);            // +0x10
    void  (__thiscall* mSlot14)(void*);            // +0x14
    void  (__thiscall* mSlot18)(void*);            // +0x18
    void  (__thiscall* mSlot1c)(void*);            // +0x1c
    void  (__thiscall* mSlot20)(void*);            // +0x20
    void  (__thiscall* mSlot24)(void*);            // +0x24
    int   (__thiscall* mSlot28)(void*);            // +0x28
};
struct Handler {
    HandlerVtbl* mpVtbl;
    void Cleanup();   // 0x00ed0b70 (thiscall, 0 args)
};

struct Obj3C {
    HandlerVtbl* mpVtbl;  // +0x00
    void*        mPad04;  // +0x04
    Handler*     mpInner08; // +0x08
};

struct Obj44 {
    unsigned mHash;      // +0x00
    int      mGameMode;  // +0x04
    unsigned mPad08;     // +0x08
    void*    mpLookup0c; // +0x0c
    char     mFlag10;    // +0x10
    char     mFlag11;    // +0x11
    char     mPad12[2];
    char     mFlag14;    // +0x14
    char     mPad15[3];
    unsigned mRec0;      // +0x18
    unsigned mRec1;      // +0x1c
    unsigned mRec2;      // +0x20
    char     mFlag24;    // +0x24
    char     mPad25[0x0b];
    void*    mpAddr30;   // +0x30
    int      mIndex34;   // +0x34
    unsigned mPad38;     // +0x38
    void*    mpInner3c;  // +0x3c
    unsigned mPad40;     // +0x40
    void*    mpRef44;    // +0x44
    void Cleanup();      // 0x00644b60
};

struct SingletonVtbl {
    void* mSlot00;                                   // +0x00
    void (__thiscall* mSlot04)(void*, void*, int);   // +0x04
    void (__thiscall* mSlot08)(void*, void*);        // +0x08
};
struct Singleton { SingletonVtbl* mpVtbl; };
Singleton* __cdecl FUN_00920090();                   // 0x00920090

struct ResVtbl {
    void* mSlot00; void* mSlot04; void* mSlot08; void* mSlot0c;
    void* mSlot10; void* mSlot14; void* mSlot18; void* mSlot1c;
    void* mSlot20; void* mSlot24;
    int (__thiscall* mSlot28)(void*);                // +0x28
};
struct DataVtbl {
    void* mSlot00; void* mSlot04; void* mSlot08;
    void* (__thiscall* mSlot0c)(void*, unsigned);    // +0x0c
};
struct ResEmbedded { DataVtbl* mpVtbl; };
struct Resource {
    ResVtbl*     mpVtbl;    // +0x00
    void*        mp04;      // +0x04
    ResEmbedded  mEmbed08;  // +0x08
    int  GetAllocator();    // 0x007f54d0
    char TestFlag();        // 0x00ecdb80
};

struct AllocRec {
    unsigned m0;      // +0x00
    unsigned m1;      // +0x04
    unsigned m2;      // +0x08
    unsigned mPad0c[3]; // +0x0c..+0x14
    unsigned mKey18;  // +0x18
};

struct ResDB {
    AllocRec* FUN_f3bcb0();          // 0x00f3bcb0
    AllocRec* FUN_f3e8a0(unsigned);  // 0x00f3e8a0
};
struct System {
    char   mPad00[0x74];
    ResDB* mp74; // +0x74
};

struct PaletteUI {
    void UpdateCategories(void* arg);  // 0x005ca980
    int  GetCurrentCategoryIndex();    // 0x005ca9c0
    void* GetSubCategory(int index);   // 0x005cae30
};

struct PageUI {
    char  mPad00[0x34];
    int*  mpItemsBegin; // +0x34
    int*  mpItemsEnd;   // +0x38
};

struct CategoryUI {
    char  mPad00[0x88];
    char* mpEntriesBegin; // +0x88
    char* mpEntriesEnd;   // +0x8c
    char  mPad90[0x10];
    int   mCurrentPage;   // +0xa0
    PageUI* GetPageUI(int index);        // 0x005c2e50
    void    SetPageVisible(int, int);    // 0x005c29a0
    int     SetPageIndex(int);           // 0x005c3bd0
    void    Update(unsigned);            // 0x005c28b0
};

struct IntVec {
    int* mpBegin;    // +0x00
    int* mpEnd;      // +0x04
    int* mpCap;      // +0x08
    int  mInline[30];
    void Resize(int n); // 0x00ed30c0
};

// A 3-pointer vector whose range-destructor helper is 0x00ed2970 (thiscall).
struct ObjVec {
    int* mpBegin;   // +0x00
    int* mpEnd;     // +0x04
    int* mpCap;     // +0x08
    void Destroy(int* begin, int* end); // 0x00ed2970
};

// ---------------------------------------------------------------- thiscall stubs
struct Pal {
    void* f_ed1f40(void*);
    void  f_ed3120(int, int);
    void* f_280f0();
    void  f_dfbba0();
    void  f_ed3350(int a);
    void  f_ed33a0(int a);
};
struct Obj74 { int f_3c7f0(int); };

// ---------------------------------------------------------------- element types
struct BigInner {
    char mData[0x27e0];
    BigInner(const BigInner& x);              // 0x00dff1a0
    BigInner& operator=(const BigInner& x);   // 0x00dfee80
};

struct BigElem {
    int      mKey;    // +0x00
    int      mPad04;  // +0x04
    BigInner mInner;  // +0x08
    BigElem(const BigElem& x) : mKey(x.mKey), mInner(x.mInner) {}
    BigElem& operator=(const BigElem& x) { mKey = x.mKey; mInner = x.mInner; return *this; }
};

struct BigVector {
    BigElem* mpBegin; // +0x00
    BigElem* mpEnd;   // +0x04
    BigElem* mpCap;   // +0x08
    void     Insert(BigElem* pos, BigElem* value);       // 0x00ed35d0
    BigElem* InsertAt(BigElem* pos, BigElem* value);     // 0x00ed3740
};

void __stdcall FUN_00ed2970(int* a, int* b);                              // 0x00ed2970
void* FUN_00ed2390(void* first, void* last, void* dst);                    // 0x00ed2390
BigElem* FUN_00ed3520(BigElem* first, BigElem* last, BigElem* dst);        // 0x00ed3520
int   FUN_00ed34a0(int a, int b, int c);                                  // 0x00ed34a0
// free-function operator new mirroring the retail allocator fill.
inline void* SpNew(size_t n) { return operator_new((unsigned)n, "Simulator", 0, 0, (const char*)0x013ebb38, 0xd1); }
void  FUN_00ed3570(BigElem* first, BigElem* last, BigElem* dst);           // 0x00ed3570

// ---------------------------------------------------------------- SimPalette
struct SimPalette {
    void*    mpVtbl00;    // +0x00
    int      mPad04;      // +0x04
    void*    mpVtbl08;    // +0x08
    void*    mpVtbl0c;    // +0x0c
    Handler* mpHandler10; // +0x10
    int      mH14;        // +0x14
    int      mH18;        // +0x18
    int      mH1c;        // +0x1c
    int      mH20;        // +0x20
    Handler* mpHandler24; // +0x24
    int      mH28;        // +0x28
    int      mH2c;        // +0x2c
    int      mH30;        // +0x30
    int      mH34;        // +0x34
    Handler* mp38;        // +0x38
    Obj3C*   mp3c;        // +0x3c
    Handler* mp40;        // +0x40
    Obj44*   mp44;        // +0x44
    char     mFlag48;     // +0x48
    char     mPad49[3];
    Handler* mp4c;        // +0x4c
    Handler* mp50;        // +0x50
    int      mPad54;      // +0x54
    Handler* mp58;        // +0x58
    int*     mpVec5cBegin; // +0x5c
    int*     mpVec5cEnd;   // +0x60
    int*     mpVec5cCap;   // +0x64
    int      mPad68;       // +0x68
    int      mPad6c;       // +0x6c
    int*     mpVec70Begin; // +0x70
    int*     mpVec70End;   // +0x74
    int*     mpVec70Cap;   // +0x78
    int      mPad7c;       // +0x7c
    int      mPad80;       // +0x80
    RefMap   mMap;         // +0x84

    SimPalette* Construct();                                // 0x00ed2e40
    void        Destroy();                                  // 0x00ed2bc0
    void        Shutdown();                                 // 0x00ed2f30
    void        Launch(void* resource, char flag);          // 0x00ed2600
    int         GetOption(int type);                        // 0x00ed20c0
    int         LoadPageState(CategoryUI* cat);             // 0x00ed1e10
    int         CountPageItems(int data, int index);        // 0x00ed1e70
    void        UpdateMap(CategoryUI* cat, int index, int dir); // 0x00ed2410
    void        UpdateCategory(CategoryUI* cat, char flag); // 0x00ed3120
    void        RemoveCategory(int unused, void* arg);      // 0x00ed33f0
};

// 0x00ed3120 is also reached through the older Pal stub name used by the
// already-settled neighbours; keep a declaration so those call sites compile.
void Pal::f_ed3120(int, int) {}

// ---------------------------------------------------------------- 0x00ed2970
void __stdcall FUN_00ed2970(int* a, int* b)
{
    for (; a < b; a = (int*)((char*)a + 0x14)) {
        int p = a[1];
        if (p) ((void(__thiscall*)(int))(*(int**)p)[3])(p);
        p = a[0];
        if (p) ((void(__thiscall*)(int))(*(int**)p)[2])(p);
    }
}

// ---------------------------------------------------------------- 0x00ed29b0
int* __cdecl FUN_00ed29b0(int* a, int* b, int* key)
{
    int n = (int)((char*)b - (char*)a) / 0x27e8;
    while (n > 0) {
        int half = n >> 1;
        int* mid = (int*)((char*)a + half * 0x27e8);
        if (*mid < *key) {
            a = (int*)((char*)mid + 0x27e8);
            n = n - 1 - half;
        } else {
            n = half;
        }
    }
    return a;
}

// ---------------------------------------------------------------- 0x00ed2a10
// Post-order destruction of a tree rooted at `node`.
void RefMap::Nuke(RBNode* node)
{
    while (node) {
        Nuke(node->mpLeft);
        RBNode* next = node->mpRight;
        void* value = node->mpValue;
        if (value)
            ((RefObj*)value)->mpVtbl->mSlot0c(value);
        operator_delete(node);
        node = next;
    }
}

// ---------------------------------------------------------------- 0x00ed2a50
// @ 0x00ed2a50
// Insert a new refcounted key node beside `pos` in the tree.
void RefMap::InsertUnique(void** result, RBNode* pos, void** key, char flag)
{
    int side = (flag == 0 && pos != (RBNode*)&mAnchor && *key >= pos->mpValue) ? 1 : 0;
    RBNode* node = (RBNode*)operator_new(0x14, "Simulator", 0, 0, (const char*)0x13ebb38, 0xd1);
    if (&node->mpValue) {
        node->mpValue = *key;
        if (node->mpValue)
            ((RefObj*)node->mpValue)->mpVtbl->mSlot08(node->mpValue);
    }
    eastl_RBTreeInsert(node, pos, &mAnchor, side);
    mSize++;
    *result = node;
}

// ---------------------------------------------------------------- 0x00ed2ae0
// @ 0x00ed2ae0
void RefMap::Erase(void** result, RBNode* node)
{
    void* next;
    RBNode* n = node;
    mSize--;
    next = (void*)eastl_RBTreeIncrement(n);
    eastl_RBTreeErase(n, &mAnchor);
    if (n->mpValue)
        ((RefObj*)n->mpValue)->mpVtbl->mSlot0c(n->mpValue);
    operator_delete(n);
    *result = next;
}

// ---------------------------------------------------------------- 0x00ed2b30
// lower_bound + insert_unique.
void RefMap::Insert(MapInsertResult* result, void** key, int flag)
{
    (void)flag;
    RBNode* parent = (RBNode*)&mAnchor;
    RBNode* current = mRoot;
    char less = 1;
    while (current) {
        parent = current;
        less = *key < current->mpValue;
        current = less ? current->mpRight : current->mpLeft;
    }
    RBNode* pos = parent;
    if (less) {
        if (parent == mBegin)
            goto do_insert;
        pos = (RBNode*)eastl_RBTreeDecrement(parent);
    }
    if (*key <= pos->mpValue) {
        result->mpNode = pos;
        result->mbNew = 0;
        return;
    }
do_insert:
    void* node = 0;
    InsertUnique(&node, parent, key, 0);
    result->mpNode = (RBNode*)node;
    result->mbNew = 1;
}

// ---------------------------------------------------------------- 0x00ed2bc0
// @ 0x00ed2bc0
// Destructor body of the Simulator palette object.
void SimPalette::Destroy()
{
    mpVtbl00 = (void*)0x01489cc8;
    mpVtbl08 = (void*)0x01489cc0;
    mpVtbl0c = (void*)0x01489cbc;

    Singleton* s = FUN_00920090();
    s->mpVtbl->mSlot08(s, (void*)0x015ac074);
    s = FUN_00920090();
    s->mpVtbl->mSlot08(s, (void*)0x015ac078);

    RBNode* root = mMap.mRoot;
    mMap.Nuke(root);

    ((ObjVec*)((char*)this + 0x70))->Destroy(mpVec70Begin, mpVec70End);
    if (mpVec70Begin && ((int*)mpVec70Begin)[-1])
        operator_delete(mpVec70Begin);

    ((ObjVec*)((char*)this + 0x5c))->Destroy(mpVec5cBegin, mpVec5cEnd);
    if (mpVec5cBegin && ((int*)mpVec5cBegin)[-1])
        operator_delete(mpVec5cBegin);

    if (mp50)
        mp50->mpVtbl->mRelease(mp50);

    if (mp4c)
        mp4c->mpVtbl->mReleaseAlt(mp4c);

    if (mp38)
        mp38->mpVtbl->mRelease(mp38);

    if (mpHandler24) {
        Handler* h = mpHandler24;
        mpHandler24 = 0;
        RemoveHandler(h, mH28, mH2c, mH30, mH34);
    }
    if (mpHandler10) {
        Handler* h = mpHandler10;
        mpHandler10 = 0;
        RemoveHandler(h, mH14, mH18, mH1c, mH20);
    }

    mpVtbl00 = (void*)0x013ec458;
    mpVtbl08 = (void*)0x013eb394;
}

// ---------------------------------------------------------------- 0x00ed2e40
// @ 0x00ed2e40
// Constructor: reset every owning slot and the embedded map.
SimPalette* SimPalette::Construct()
{
    mPad04 = 0;
    *(void* volatile*)&mpVtbl08 = (void*)0x013eb394;
    *(void* volatile*)&mpVtbl0c = (void*)0x0140b5a0;

    mpVtbl00 = (void*)0x01489cc8;
    mpVtbl08 = (void*)0x01489cc0;
    mpVtbl0c = (void*)0x01489cbc;

    mpHandler10 = 0;
    mH14 = 0; mH18 = 0; mH1c = 0; mH20 = 0;
    mpHandler24 = 0;
    mH28 = 0; mH2c = 0; mH30 = 0; mH34 = 0;
    mp38 = 0;
    mp3c = 0;
    mp40 = 0;
    mp44 = 0;
    mFlag48 = 0;
    mp4c = 0;
    mp50 = 0;
    mp58 = 0;
    mpVec5cBegin = 0;
    mpVec5cEnd = 0;
    mpVec5cCap = 0;
    mpVec70Begin = 0;
    mpVec70End = 0;
    mpVec70Cap = 0;

    RBNode* anchor = (RBNode*)&mMap.mAnchor;
    anchor->mpRight = 0;
    anchor->mpParent = 0;
    anchor->mColor = 0;
    anchor->mpLeft  = anchor;
    mMap.mBegin = anchor;
    mMap.mRoot = 0;
    mMap.mColor = 0;
    mMap.mSize = 0;

    Singleton* s = FUN_00920090();
    s->mpVtbl->mSlot04(s, (void*)0x015ac078, 0);
    s = FUN_00920090();
    s->mpVtbl->mSlot04(s, (void*)0x015ac074, 0);

    return this;
}

// ---------------------------------------------------------------- 0x00ed2f30
// @ 0x00ed2f30
// Release every owned sub-object of the palette object.
void SimPalette::Shutdown()
{
    if (mpHandler24) {
        Handler* h = mpHandler24;
        mpHandler24 = 0;
        RemoveHandler(h, mH28, mH2c, mH30, mH34);
    }

    if (mp58) {
        ((CallbackObj*)mp58)->Cancel();
        Handler* h = mp58;
        if (h)
            h->mpVtbl->mDestroy(h, 1);
        mp58 = 0;
    }

    if (mp4c) {
        mp4c->Cleanup();
        Handler* h = mp4c;
        if (h) {
            mp4c = 0;
            h->mpVtbl->mReleaseAlt(h);
        }
    }
    if (mp50) {
        mp50->mpVtbl->mSlot24(mp50);
        Handler* h = mp50;
        if (h) {
            mp50 = 0;
            h->mpVtbl->mRelease(h);
        }
    }

    {
        int* begin = mpVec5cBegin;
        int* end = mpVec5cEnd;
        void* newEnd = FUN_00ed2390(end, end, begin);
        FUN_00ed2970((int*)newEnd, end);
        mpVec5cEnd = mpVec5cBegin;
    }
    {
        int* begin = mpVec70Begin;
        int* end = mpVec70End;
        void* newEnd = FUN_00ed2390(end, end, begin);
        FUN_00ed2970((int*)newEnd, end);
        mpVec70End = mpVec70Begin;
    }

    if (mp40) {
        PaletteUI* ui = (PaletteUI*)mp40->mpVtbl->mLookup(mp40, 0x52deed23);
        ShutdownPaletteUI(ui, 0);
    }

    if (mp3c) {
        if (mp3c->mpInner08) {
            void* inner = mp3c->mpInner08->mpVtbl->mLookup(mp3c->mpInner08, 0x12dca0ea);
            ShutdownPalette(inner, 0);
        }
        mp3c->mpVtbl->mReleaseAlt(mp3c);
        mp3c = 0;
    }

    if (mp40) {
        mp40->mpVtbl->mRelease(mp40);
        mp40 = 0;
    }

    if (mp44) {
        mp44->Cleanup();
        operator_delete(mp44);
        mp44 = 0;
    }

    if (mp38) {
        Handler* h = mp38;
        mp38 = 0;
        h->mpVtbl->mRelease(h);
    }
}

// ---------------------------------------------------------------- 0x00ed2600
// @ 0x00ed2600
// Launch the palette UI for `resource`.
void SimPalette::Launch(void* resource, char flag)
{
    Resource* res = (Resource*)resource;
    unsigned hash = 0xad63f994;
    int alloc = res->GetAllocator();
    bool isDefault = (alloc == -2);
    int count = 1;
    int type = res->mpVtbl->mSlot28(res);

    if (type != 0x867a9ee9) {
        count = GetOption(type);
        if (!res->TestFlag())
            count++;

        switch (type) {
        case 0xe34e8a60:
            hash = (isDefault ? 0xc3cc8df0u : 0u) + 0xf25aef31u;
            break;
        case 0x6031c03a:
            hash = 0x0b0b84ae;
            break;
        case 0x7998ce71:
            hash = 0x23515eaa;
            break;
        case 0xd37c1045:
            hash = 0x258dc2ac;
            break;
        case 0xe137ff08:
            hash = 0x406d9049;
            break;
        case 0xb10e526f:
            hash = 0x7602b820;
            break;
        case 0xcf56099a:
            hash = 0x54042a4b;
            break;
        case 0x5b3d1d0d: {
            ResDB* db = ((System*)g_16c7aa4)->mp74;
            AllocRec* rec = db->FUN_f3e8a0((unsigned)alloc);
            if (!rec) {
                hash = 0x026d8c5e;
            } else {
                switch (rec->mKey18) {
                case 0x1a4e0708:
                case 0x2090a11b:
                case 0x441cd3e6:
                case 0x449c040f:
                    hash = 0x258dc2ac;
                    break;
                case 0x7d433fad:
                case 0xbc1041e6:
                case 0x9ad7d4aa:
                case 0xf670aa43:
                    hash = 0x9bec2b97;
                    break;
                case 0x2a5147a9:
                case 0x1f2a25b6:
                case 0x8f963dcb:
                case 0xc15695da:
                    hash = 0x6ddbf5f3;
                    break;
                default:
                    break;
                }
            }
            break;
        }
        default:
            break;
        }
    }

    unsigned v0 = 0, v1 = 0, v2 = 0;
    {
        if (res->GetAllocator() != -1) {
            ResDB* db = ((System*)g_16c7aa4)->mp74;
            AllocRec* rec;
            if (res->GetAllocator() == -2)
                rec = db->FUN_f3bcb0();
            else
                rec = db->FUN_f3e8a0((unsigned)res->GetAllocator());
            if (rec) {
                v0 = rec->m0;
                v1 = rec->m1;
                v2 = rec->m2;
            }
        }
    }

    void* data = 0;
    FUN_006447c0(0, &data);
    ((unsigned*)((char*)data + 0x24))[0] = g_015da7c4;
    ((unsigned*)((char*)data + 0x24))[1] = g_015da7c8;
    ((unsigned*)((char*)data + 0x24))[2] = g_015da7cc;
    ((unsigned*)((char*)data + 0x24))[3] = g_015da7d0;
    *((char*)data + 0x34) = 0;

    if (hash) {
        mp44 = (Obj44*)operator_new(0x48, "Simulator", 0, 0, 0, 0);
        if (mp44)
            mp44 = (Obj44*)FUN_00644b10(mp44, 0);
        mp44->mFlag14 = 0;
        mp44->mpAddr30 = (void*)0x00ad0e52;
        mp44->mGameMode = GetCurrentGameMode();
        mp44->mHash = hash;
        mp44->mpLookup0c = res->mEmbed08.mpVtbl->mSlot0c(&res->mEmbed08, 0xee3f516e);
        mp44->mRec0 = v0;
        mp44->mRec1 = v1;
        mp44->mRec2 = v2;
        mp44->mFlag24 = flag;
        mp44->mFlag10 = 0;
        mp44->mFlag11 = 1;

        void* old = mp44->mpRef44;
        if (data != old) {
            if (data)
                ((RefObj*)data)->mpVtbl->mSlot04(data);
            mp44->mpRef44 = data;
            if (old)
                ((RefObj*)old)->mpVtbl->mSlot08(old);
        }

        mp44->mpInner3c = (void*)((char*)this + 0x0c);
        mp44->mIndex34 = isDefault ? 1 : count;
        FUN_0064a990(mp44);
    }

    if (data)
        ((RefObj*)data)->mpVtbl->mSlot08(data);
}

// ---------------------------------------------------------------- 0x00ed3120
// @ 0x00ed3120
// Recompute the visible page set of a palette category.
void SimPalette::UpdateCategory(CategoryUI* cat, char flag)
{
    if (!cat)
        return;

    if (flag) {
        ((RefObj*)cat)->mpVtbl->mSlot08(cat);
        void* key = cat;
        MapInsertResult result;
        mMap.Insert(&result, &key, 0);
        ((RefObj*)cat)->mpVtbl->mSlot0c(cat);
        return;
    }

    int data = LoadPageState(cat);
    int pageCount = (int)(cat->mpEntriesEnd - cat->mpEntriesBegin) / 8;

    IntVec flags;
    flags.Resize(pageCount);

    int visible = 0;
    char sawLast = 0;
    if (pageCount > 0) {
        for (int i = 0; i < pageCount; i++) {
            PageUI* page = cat->GetPageUI(i);
            int itemCount = (int)(page->mpItemsEnd - page->mpItemsBegin);
            int found = CountPageItems(data, i);
            flags.mpBegin[i] = 0;
            if (found == itemCount)
                flags.mpBegin[i] = 1;
            else if (found > 0)
                flags.mpBegin[i] = -1;

            cat->SetPageVisible(i, flags.mpBegin[i] != 0);
            if (flags.mpBegin[i] != 0)
                visible++;
            if (flags.mpBegin[i] == -1)
                sawLast = 1;
        }

        if (!visible) {
            cat->SetPageVisible(cat->mCurrentPage, 1);
        } else if (visible < pageCount) {
            if (flags.mpBegin[cat->mCurrentPage] == 0) {
                for (int i = 0; i < pageCount; i++) {
                    if (flags.mpBegin[i] != 0) {
                        cat->SetPageIndex(i);
                        break;
                    }
                }
            }
            if (!sawLast) {
                int idx = cat->mCurrentPage;
                do {
                    idx++;
                    if (idx == pageCount)
                        idx = 0;
                    if (flags.mpBegin[idx] == 0) {
                        cat->SetPageVisible(idx, 1);
                        break;
                    }
                } while (idx != cat->mCurrentPage);
            }
        }
    } else {
        cat->SetPageVisible(cat->mCurrentPage, 1);
    }

    cat->Update(0);
    UpdateMap(cat, cat->mCurrentPage, -1);

    if (flags.mpBegin && flags.mpBegin != flags.mInline)
        operator_delete(flags.mpBegin);
}

// ---------------------------------------------------------------- 0x00ed33f0
// @ 0x00ed33f0
// Drop the currently selected category from the palette map.
void SimPalette::RemoveCategory(int unused, void* arg)
{
    (void)unused;
    if (!mp40)
        return;
    PaletteUI* ui = (PaletteUI*)mp40->mpVtbl->mLookup(mp40, 0x52deed23);
    if (!ui)
        return;

    ui->UpdateCategories(arg);
    if (!mMap.mSize)
        return;

    int current = ui->GetCurrentCategoryIndex();
    void* category = ui->GetSubCategory(current);

    RBNode* end = (RBNode*)&mMap.mAnchor;
    RBNode* node = mMap.mBegin;
    while (node != end) {
        if (node->mpValue == category)
            break;
        node = (RBNode*)eastl_RBTreeIncrement(node);
    }
    if (node == end)
        node = mMap.mBegin;

    UpdateCategory((CategoryUI*)node->mpValue, 0);
    void* next;
    mMap.Erase(&next, node);
}

// ---------------------------------------------------------------- 0x00ed35d0
// @ 0x00ed35d0
// vector::insert at an arbitrary position.
void BigVector::Insert(BigElem* pos, BigElem* value)
{
    if (mpEnd != mpCap) {
        if (value >= pos && value < mpEnd)
            value += 1;
        mpEnd->BigElem::BigElem(*(mpEnd - 1));
        FUN_00ed3570(pos, mpEnd - 1, mpEnd);
        *pos = *value;
        ++mpEnd;
    } else {
        unsigned prevSize = (unsigned)(mpEnd - mpBegin);
        unsigned newSize = prevSize ? prevSize * 2 : 1;
        BigElem* newData = newSize
            ? (BigElem*)SpNew(newSize * sizeof(BigElem))
            : 0;
        BigElem* newEnd = FUN_00ed3520(mpBegin, pos, newData);
        FUN_00ed34a0((int)mpBegin, (int)pos, (int)newData);
        if (newEnd)
            newEnd->BigElem::BigElem(*value);
        newEnd = FUN_00ed3520(pos, mpEnd, newEnd + 1);
        FUN_00ed34a0((int)pos, (int)mpEnd, (int)(newEnd));
        if (mpBegin)
            operator_delete(mpBegin);
        mpBegin = newData;
        mpEnd = newEnd;
        mpCap = newData + newSize;
    }
}

// ---------------------------------------------------------------- 0x00ed3740
// @ 0x00ed3740
// vector::insert at the end without growing when possible.
BigElem* BigVector::InsertAt(BigElem* pos, BigElem* value)
{
    int index = (int)(pos - mpBegin);
    if (pos == mpEnd && mpEnd != mpCap) {
        BigElem* slot = mpEnd;
        mpEnd = mpEnd + 1;
        if (slot)
            slot->BigElem::BigElem(*value);
    } else {
        Insert(pos, value);
    }
    return mpBegin + index;
}

// ---------------------------------------------------------------- 0x00ed2b30 (part of RefMap)
// (definition above with the map helpers)

// ---------------------------------------------------------------- 0x00ed3350
// @ 0x00ed3350
void Pal::f_ed3350(int a)
{
    if (a == -2)
        return;
    char* p70 = (char*)this + 0x70;
    if (FUN_00ed1f00(p70, a))
        return;
    void** p = (void**)f_ed1f40(p70);
    if (!p)
        return;
    ((void(__thiscall*)(void*, int))(*(void***)*p)[0x1c / 4])(*p, a);
    f_ed3120((int)p[1], 1);
}

// ---------------------------------------------------------------- 0x00ed33a0
// @ 0x00ed33a0
void Pal::f_ed33a0(int a)
{
    void* r = (void*)FUN_00ed1f00((char*)this + 0x70, a);
    if (a != -2 && r) {
        if (((Obj74*)(*(char**)(g_16c7aa4 + 0x74)))->f_3c7f0(a) == 0) {
            void* q = *(void**)r;
            ((void(__thiscall*)(void*))(*(void***)q)[0x20 / 4])(q);
            f_ed3120(((int*)r)[1], 1);
        }
    }
}

// ---------------------------------------------------------------- 0x00ed34a0
// @ 0x00ed34a0
int __cdecl FUN_00ed34a0(int a, int b, int c)
{
    if (a != b) {
        char* p = (char*)(a + 0x78);
        do {
            ((Pal*)(p + 0x2718))->f_280f0();
            char* e = *(char**)(p + 4);
            for (char* i = *(char**)p; i < e; i += 0x4e0)
                ((Pal*)i)->f_dfbba0();
            void* base = *(void**)p;
            if (base && *(int*)((char*)base - 4))
                operator_delete(base);
            c += 0x27e8;
            a += 0x27e8;
            p += 0x27e8;
        } while (a != b);
    }
    return c;
}

// ---------------------------------------------------------------- 0x00ed3570
struct Inner { void copy(Inner* src); };
struct Big27e8 { char pad[0x27e8]; };

int* __cdecl FUN_00ed3570_impl(int* first, int* last, int* dst);
int* __cdecl FUN_00ed3570(int* first, int* last, int* dst);
int* __cdecl FUN_00ed3570(int* first, int* last, int* dst)
{
    while (last != first) {
        last = (int*)((char*)last - 0x27e8);
        dst  = (int*)((char*)dst  - 0x27e8);
        *dst = *last;
        ((Inner*)((char*)dst + 8))->copy((Inner*)((char*)last + 8));
    }
    return dst;
}
