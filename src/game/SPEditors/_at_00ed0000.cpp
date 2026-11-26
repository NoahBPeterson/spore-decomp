// src/game/SPEditors/_at_00ed0000.cpp -- migrated from slice(s) s00edaf10, s00ed9f10, s00ed9150, s00ed8490, s00ed74f0, s00ed4730, s00ed37c0, s00ed2600, s00ed1880 by tools/migrate/rewrite.py
// Object file: SPEditors/_at_00ed0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPPalette.h"
#include "SP/cSPPaletteUI.h"
#include <math.h>
#include "SP/cSPEditorNaming.h"
#include "cSPUIAnimator.h"
#include "cSPUILayout.h"
#include "SP/cString.h"

// ---- items of slice s00ed1880 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void* (__thiscall* FV_v)(void*);
typedef void* (__thiscall* FV_i)(void*, int);
typedef void* (__thiscall* FV_p)(void*, void*);
void* __cdecl EAAllocate(unsigned size, const char* name, int, int, int, int);  // 0xf473a0
void* __cdecl FUN_009512c0(void);                                  // 0x009512c0
void* __cdecl FUN_009512d0(int, int, const char*, void*);          // 0x009512d0
void* __cdecl FUN_00ece870(void*, void*);                          // 0x00ece870
void* __cdecl FUN_00572620(void*, void*);                          // 0x00572620
void* __cdecl FUN_005cae30(void*, int);                            // 0x005cae30 GetSubCategory
void* __cdecl FUN_005c2e50(void*, int);                            // 0x005c2e50 GetPageUI
char  FUN_00ecdb80(void*);                                        // 0x00ecdb80 (thiscall)
struct Container;
struct SwatchUIRaw {
    void* CtorEditItem();                                          // 0x00ecf150 (thiscall)
    void* CtorItem();                                              // 0x00ece990 (thiscall)
};
int   FUN_007f54d0(void*);                                        // 0x007f54d0 (thiscall) GetAllocator
struct Container;
struct SwatchQuery {
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual int GetQueryId();  // vtable +0x28
    bool HasDefaultIndex();  // 0x00ecdb80: index at +0x10 equals -1
};
struct Entry {
    void* a;         // +0x00
    void* b;         // +0x04
    int   cat;       // +0x08
    int   page;      // +0x0c
    int   sub;       // +0x10
};
struct EntryVec { Entry* b; Entry* e; char pad[4]; };
struct Container {
    char   pad00[8];
    int    f08;                 // +0x08
    int    pad0c;
    void*  hA;                  // +0x10  handle
    void*  hB;                  // +0x14  handle
    void*  hItemUI;             // +0x18  handle
    char   pad1c[4];
    char   conn[0x38 - 0x20];
    void*  hAvatarUI;           // +0x38
    int    pad3c;
    void*  hPaletteCatUI;       // +0x40  QueryInterface 0x52deed23
    int    pad44;
    char   f48;                 // +0x48  visible flag
    char   pad49[3];
    int    notifier;            // +0x4c
    char   pad50[8];
    int    callback;            // +0x58
    union {
    struct {
    Entry* vec0;                // +0x5c
    Entry* vec0End;             // +0x60
    char   pad64[0x0c];
    Entry* vec1;                // +0x70
    Entry* vec1End;             // +0x74
    };
    struct {
    EntryVec v0;                // +0x5c
    char   pad68[0x08];
    EntryVec v1;                // +0x70
    };
    };
};
// ---- items of slice s00ed1880 end

// ---- items of slice s00ed2600 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_13ebb38[];
extern char* g_16c7aa4;   // 0x016c7aa4
extern unsigned g_015da7c4; // 0x015da7c4
extern unsigned g_015da7c8; // 0x015da7c8
extern unsigned g_015da7cc; // 0x015da7cc
extern unsigned g_015da7d0; // 0x015da7d0
void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int);  // 0xf473a0
void  __cdecl operator_delete(void*);                                           // 0xf47380
int   __stdcall FUN_00ed1f00(void*, int);                                         // 0xed1f00
void* __cdecl eastl_RBTreeIncrement(void*);              // 0x00921580
void  __cdecl eastl_RBTreeErase(void*, void*);           // 0x00921880
void  __cdecl eastl_RBTreeInsert(void*, void*, void*, int); // 0x009216a0
void* __cdecl eastl_RBTreeDecrement(void*);              // 0x009215c0
void  __cdecl RemoveHandler(void*, int, int, int, int);  // 0x00571db0
void* __cdecl FUN_006447c0(int, void**);                 // 0x006447c0
void* __fastcall FUN_00644b10(void*, int);               // 0x00644b10
int   __cdecl GetCurrentGameMode();                      // 0x00b5b800
void  __cdecl FUN_0064a990(void*);                       // 0x0064a990
struct Singleton;
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
    void** InsertUnique(void** result, RBNode* pos, void** key, char flag);  // 0x00ed2a50
    void Erase(void** result, RBNode* node);                              // 0x00ed2ae0
};
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
struct ObjVec {
    int* mpBegin;   // +0x00
    int* mpEnd;     // +0x04
    int* mpCap;     // +0x08
    void Destroy(int* begin, int* end); // 0x00ed2970
};
struct Pal {
    void* f_ed1f40(void*);
    void  f_ed3120(int, int);
    void* f_280f0();
    void  f_dfbba0();
    void  f_ed3350(int a);
    void  f_ed33a0(int a);
};
struct Obj74 { int f_3c7f0(int); };
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
BigElem* FUN_00ed3520(BigElem* first, BigElem* last, BigElem* dst);        // 0x00ed3520
int   FUN_00ed34a0(int a, int b, int c);                                  // 0x00ed34a0
inline void* SpNew(size_t n) { return operator_new((unsigned)n, "Simulator", 0, 0, (const char*)&g_13ebb38, 0xd1); }
void  FUN_00ed3570(BigElem* first, BigElem* last, BigElem* dst);           // 0x00ed3570
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
void Pal::f_ed3120(int, int) {}
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
int* __cdecl FUN_00ed3570(int* first, int* last, int* dst);
// ---- items of slice s00ed2600 end

// ---- items of slice s00ed37c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void VCall(void* p)
{
    ((void(__thiscall*)(void*))(*(void***)p)[N])(p);
}
template <int N, class R> inline R VCall1(void* p, unsigned a)
{
    return ((R(__thiscall*)(void*, unsigned))(*(void***)p)[N])(p, a);
}
inline void* operator new(size_t, void* p) { return p; }
struct Any { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); };
struct PalEntry {
    Any* item;   // +0  (AddRef slot 1, Release slot 2)
    Any* pal;    // +4  (AddRef slot 2, Release slot 3)
    int  cat;    // +8
    int  row;    // +0xc
    int  idx;    // +0x10
    PalEntry() : item(0), pal(0) {}
    ~PalEntry()
    {
        if (pal)  VCall<3>(pal);
        if (item) VCall<2>(item);
    }
};
struct PalVec {
    PalEntry* mpBegin;
    PalEntry* mpEnd;
    PalEntry* mpCapacity;
    int       alloc;
    int       pad;
    void DoInsertValue(PalEntry* pos, const PalEntry& v);   // 0x00ed2d00 (thiscall, ret 8)
    __forceinline void push_back()
    {
        if (mpEnd < mpCapacity) {
            ::new (mpEnd++) PalEntry();
        } else {
            DoInsertValue(mpEnd, PalEntry());
        }
    }
};
void* __cdecl operator new(size_t, const char*, int, int, int, int);   // 0x00f473a0
struct Row {                         // element of Category::rows (+0x34/+0x38 = item pointers)
    char  pad[0x34];
    void** itemsBegin;
    void** itemsEnd;
    void* GetItem(int i);            // 0x005cae30
};
struct RowCell { Row* row; int pad; };
struct Category : Any {              // cSPPalette
    char    pad4[0x84];
    RowCell* rowsBegin;              // +0x88
    RowCell* rowsEnd;                // +0x8c
    bool Init(const void* key, int a, int b, int c, int d, int e, int f);   // 0x005c6340 (ret 0x1c)
    void AddRowLike(int src);        // 0x005c50b0
    Row* GetRow(int i);              // 0x005c2e50
};
struct PaletteUI_s00ed_37c0 : Any {             // cSPPaletteUI (0x6c)
    PaletteUI_s00ed_37c0();                     // 0x005cb3b0
    char  pad4[0x30];
    Category** catBegin;             // +0x34
    Category** catEnd;               // +0x38
    void Init(Category* pal, Any* mainWin, int a, Any* b);   // 0x005cb5a0 (ret 0x10)
    void SetVisible(int v);          // 0x005ca900 (ret 4)
    int  FindCategoryIndex();        // 0x005ca9c0
    Category* GetCategory(int i);    // 0x005cae30
    uint32_t tail[12];
};
struct CastPanel : Any { uint32_t pad[15]; CastPanel(); };                    // 0x005c5e30 (0x40)
struct AvatarUI : Any {
    uint32_t pad[14];
    AvatarUI();            // 0x00ed0ab0
    void Setup(int a);     // 0x00ed1880
};
struct MsgServer { void Register(void* listener, unsigned id); };   // vtable slot 9
MsgServer* __cdecl MessageServer();                          // 0x0067dcc0
struct CallbackBase {                                        // EA::CallbackSystem::Callback
    char pad[0x20];
    CallbackBase(int a, int b, int c, int d, int e, int f, int g);   // 0x00929e70 (ret 0x1c)
    void Set(void* fn, void* obj, int flag);                 // 0x00929da0 (ret 0xc)
    virtual ~CallbackBase();
};
class Scn;
struct ScnCallback : CallbackBase {
    Scn*  owner;     // +0x24
    void* fn;        // +0x28
    int   extra;     // +0x2c
    ScnCallback(Scn* o) : CallbackBase(0, 0, 0x16, 0, 2, 0, 0)
    {
        fn = (void*)0x00ed33f0;
        extra = 0;
        owner = o;
        Set((void*)0x00ed1cf0, this, 0);
    }
    virtual ~ScnCallback() {}
};
struct Globals { char pad[0x74]; struct Sub* sub; };
struct Sub { char pad[0x10]; char* db; char pad2[0xbc]; Any* doc; };
extern Globals* g_16c7aa4_s00ed_37c0;                                   // 0x016c7aa4
struct Record   { char pad[0x27e8]; };
struct RecordMap {
    Record* mpBegin;         // +0x00
    Record* mpEnd;           // +0x04
    Record* mpCapacity;      // +0x08
    int     allocA;          // +0x0c
    int     allocB;          // +0x10
    uint8_t flags;           // +0x14
    Record* Find(int* key);  // 0x00ed37c0 (find-or-insert; returns &record->f8)
};
extern "C" int   __cdecl   FUN_00ed29b0(Record* a, Record* b, int* key, int flag);  // 0x00ed29b0 (lower_bound)
extern "C" Record* __cdecl FUN_00ed3740(RecordMap* self, Record* pos, int* key);    // 0x00ed3740 (insert)
Record* __cdecl FUN_00f2d260(Record* p);                         // 0x00f2d260 (construct element)
char*   __cdecl FUN_00dff1a0(char* dst, char* src);              // 0x00dff1a0 (copy-construct)
void    __cdecl FUN_00dfce90(void* p);                           // 0x00dfce90 (destroy element)
int     __cdecl FUN_00eece20(int key);                           // 0x00eece20 (key -> icon)
Record* __cdecl FUN_00ed1ec0(RecordMap* self);                   // 0x00ed1ec0
class Scn {
public:
    char       pad0[8];
    char       listener[0x1c];        // +8 .. message listener sub-object
    MsgServer* server;                // +0x24
    void*      lstn;                  // +0x28
    const void* lstnName;             // +0x2c
    int        lstnFlag;              // +0x30
    int        lstnZero;              // +0x34
    Any*       mainWin;               // +0x38
    CastPanel* castPanel;             // +0x3c
    PaletteUI_s00ed_37c0* paletteUI;             // +0x40
    int        pad44[2];
    AvatarUI*  avatarUI;              // +0x4c
    Any*       tool;                  // +0x50
    int        pad54;
    ScnCallback* callback;            // +0x58
    PalVec     vecA;                  // +0x5c
    PalVec     vecB;                  // +0x70

    void Finish();                    // 0x00ed3a00
    void SelectCategory(Category* cat, int one);   // 0x00ed3120 (ret 8)
    bool Setup();                     // 0x00ed3c00
};
Any*  __cdecl FUN_00ed1d20(Any* mainWin);                        // 0x00ed1d20 (mainWin -> palette UI)
int   __cdecl FUN_00f46450(int key);                             // 0x00f46450
int   __cdecl FUN_00f43af0(int key);                             // 0x00f43af0
Any*  __cdecl FUN_00f3e8a0(void* db, int key);                   // 0x00f3e8a0 (key -> node)
void  __cdecl FUN_00f40370(void* node);                          // 0x00f40370 (ScenarioNode clear+propagate)
int   __cdecl FUN_00f42580(int key);                             // 0x00f42580
void  __cdecl FUN_00f427c0(void* node);                          // 0x00f427c0
void  __cdecl FUN_00f45970(void* node);                          // 0x00f45970
void  __cdecl FUN_00f45a80(void* node);                          // 0x00f45a80
int   __cdecl GetAllocator(void* obj);                           // 0x007f54d0 (__thiscall obj->GetAllocator)
bool  __cdecl FUN_00ecdb80_s00ed_37c0(void* obj);                           // 0x00ecdb80
void* __cdecl FUN_00ed21f0(void* p);                             // 0x00ed21f0
void* __cdecl FUN_00ed21d0(void* p);                             // 0x00ed21d0
void  __cdecl FUN_00ed2600(void* self, void* a, int b);          // 0x00ed2600
void  __cdecl FUN_00ed3350(void* self, int key);                 // 0x00ed3350
void  __cdecl FUN_00ed33a0(void* self, int key);                 // 0x00ed33a0
void  __cdecl FUN_00ed2410(void* self, void* a, void* b, void* c); // 0x00ed2410
void  __cdecl FUN_00ece300(void* item);                          // 0x00ece300
void* __cdecl FUN_01137690(Any* p);                              // 0x01137690
void  __cdecl FUN_00eef810(void* out, void* a, int b, int c);    // 0x00eef810
void  __cdecl FUN_00dfed90(void* dst, void* src);                // 0x00dfed90
void* __cdecl FUN_00ecdbb0(void* p);                             // 0x00ecdbb0
struct ScnRecBody {                 // helper view (ecx == ProcessMessage this - 8)
    char   pad5c[0x5c];
    PalVec palVecA;                 // +0x5c (== ProcessMessage +0x54)
    PalVec palVecB;                 // +0x70 (== ProcessMessage +0x68)
    void Finish();                  // 0x00ed3a00
    void RemoveIcon(int key);       // 0x00ed38a0
    void ClearTwo(int key);         // 0x00ed3920
    void DeselectTwo(int key);      // 0x00ed39a0
    void ChooseSubCategory(void* sub, int key);  // 0x00ed3b20
    void* FUN_00ed1f00(void* tab, int key);      // 0x00ed1f00 (find by key)
    void* FUN_00ed1f70(void* tab, int key);      // 0x00ed1f70 (insert into vec)
    void  FUN_00ed3120(void* item, int one);     // 0x00ed3120 (select)
};
struct ScnRec {                     // ProcessMessage view (this == ScnRecBody + 8)
    char   pad00[0x38];
    Any*   mainWin;                 // +0x38
    PalVec palVec0;                 // +0x54 (== ScnRecBody +0x4c)
    PalVec palVec1;                 // +0x68 (== ScnRecBody +0x60)
    char   pad7c[0x1e24];
    bool   ProcessMessage(unsigned id, Any* arg);   // 0x00ed4200
};
struct PaletteCtrl {
    void** vt;
    int   GetCurrentCategoryIndex();          // 0x005ca9c0 (slot)
    void* GetSubCategory(int i);              // 0x005cae30
};
struct FillEntry { int f0, f4, f8; };
struct EditorRect { int a0, a4, a8, ac; };
struct Rect3 { int a, b, c; };
void __cdecl FUN_00540520(void* p);                      // 0x00540520
namespace UI {
    void __cdecl ToggleHint(void* checklist, int hi, int lo);   // 0x00efbbe0
}
namespace UI {
    void __cdecl ApplyPlacement(void* self, int alloc);         // 0x00f00790
}
void Scn::Finish()
{
    ((ScnRecBody*)(void*)this)->Finish();
}
// ---- items of slice s00ed37c0 end

// ---- items of slice s00ed4730 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct S_ef72b0 { void f(); };
struct S_f45970 { void* f(); };
struct S_f45a80 { void f(); };
struct S_f46450 { int  f(void*); };
struct S_ed38a0 { void f(int); };
struct S_ed3b20 { void f(void*, void*); };
struct S_644b60 {
    void f();   // 0x00644b60
};
struct Item_ed4730 { int a, b, c; };
struct Vec_ed4730 {
    Item_ed4730* mpBegin;
    Item_ed4730* mpEnd;
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};
struct Getter_ed4730 {
virtual void v0();
virtual void v1();
virtual void v2();
    virtual void* Get(unsigned id);
};
struct Obj4730 { char pad[0x38]; void f(Vec_ed4730* list); };
// ---- items of slice s00ed4730 end

// ---- items of slice s00ed74f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const wchar_t g_13ec468[];    // L"" 0x013ec468
extern const float g_1488874;        // 0x01488874: 0.1f
extern const float g_1485378;        // 0x01485378: 0.0f
extern const float g_148a228;        // 0x0148a228: FLT_MAX
extern char     g_1489fe8;           // 0x01489fe8: terrain hint blocks, 0x30 bytes apart
extern char     g_148a018;           // 0x0148a018
extern char     g_148a048;           // 0x0148a048
extern char     g_148a078;           // 0x0148a078
extern char     g_148a0a8;           // 0x0148a0a8
struct Key12 {                       // resource key: instance/type/group
    uint32_t a, b, c;
};
extern Key12    g_15ac1f0;   // 0x015ac1f0
extern Key12    g_15ac1fc;   // 0x015ac1fc
extern Key12    g_15ac208;   // 0x015ac208
struct cNotifyTarget {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
    virtual void v12();
    virtual void SetText(const wchar_t* text, int flags);   // +0x34
};
struct cNotifyHost {                                 // 0x0067de40 singleton
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual cNotifyTarget* GetTarget();              // +0x20
};
struct cText { const wchar_t* GetText(); };          // 0x006b55c0
struct cUIHint {
    char pad[0x78];
    cText mText;                                     // +0x78
};
class cUIHints { public:
    cUIHint* FindByID(uint32_t id);                  // 0x0067aee0
    void     ShowHint(uint32_t id);                  // 0x0067c830
};
struct cNode;
struct cSim {                                        // *(g + 0x74)
    bool   Classify(int* out);                       // 0x00f41270
    bool   f3b920();                                 // 0x00f3b920
    bool   f3b950();                                 // 0x00f3b950
    cNode* ff3f00();                                 // 0x00ff3f00
    bool   f41420(cNode* n, int a, int b, int c);    // 0x00f41420
    void   f45970();                                 // 0x00f45970
    int    f3bf60();                                 // 0x00f3bf60
    void   f3bcc0(int n);                            // 0x00f3bcc0
    void   f45a80();                                 // 0x00f45a80
    void   f427c0();                                 // 0x00f427c0
};
struct cTutorials {
    void MarkDirty();                                // 0x00ef72c0
    void f8860();                                    // 0x00ef8860
};
struct cHintPanel { void f69a0(int a); };            // *(g + 0xd8); 0x00f069a0
struct cGlobals {
    char        pad0[0x74];
    cSim*       sim;                                 // +0x74
    char        pad1[0xd4 - 0x78];
    cTutorials* tutorials;                           // +0xd4
    cHintPanel* hints;                               // +0xd8
};
extern cGlobals* g_16c7aa4_s00ed_74f0;                          // 0x016c7aa4
cUIHints*       __cdecl UIHints();                   // 0x0067cac0
cNotifyHost*    __cdecl NotifyHost();                // 0x0067de40
void            __cdecl CalloutMessageBox(void* where, const Key12* key);   // 0x00809db0
int             __stdcall HintForState(int state);   // 0x00f3b2c0 ($E366)
struct cVerbIconTray {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual void SetSelected(int on);                // +0x1c
};
struct PanelCallout {
    char pad00[0x20];
    cVerbIconTray* mpVerbTray;                       // +0x20  == Panel+0x2c
    char pad24[0x3c - 0x24];
    int  mParam;                                     // +0x3c  == Panel+0x48
    int  mType;                                      // +0x40  == Panel+0x4c
    int  mExtra;                                     // +0x44  == Panel+0x50
    int  mKey;                                       // +0x48  == Panel+0x54
    int  mMode;                                      // +0x4c  == Panel+0x58
    void Dispatch(unsigned unused, unsigned selected);   // 0x00ed74f0
};
struct Panel {                                       // primary object; the handler is its base at +8
    char pad0[0xc];
    PanelCallout mCallout;                           // +0x0c
    void ShowCallout();                              // 0x00ed5910
    void SelectionChanged(int index);                // 0x00ed7490
    void FUN_00ed5640();                             // 0x00ed5640
    void FUN_00ed6720(int i);                        // 0x00ed6720
    void FUN_00ed76e0(int i);                        // 0x00ed76e0
    bool FUN_00ed8130(int msg, int type, int extra); // 0x00ed8130
};
struct cStoreObj;
struct cPropStore {                                  // first argument of the two wrappers
    bool          Find(void* key);                   // 0x00c88940
    cStoreObj*    FindObj(void* key);                // 0x00c888e0
    void          Remove(void* key, int value);      // 0x00c8ad30
    void          Set3(void* a, void* b, void* c);   // 0x00c8b130
    void          SetMax(void* key, float value);    // 0x00c88a00
    void          SetA(void* key, float value);      // 0x00c8a200
    void          SetB(void* key, char value);       // 0x00c8a110
};
struct cStoreObj {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
    virtual uint64_t GetValue();                     // +0x60
};
struct cModelObj {
    char  pad0[0x220];
    float mValue;                                    // +0x220
};
struct cGameData {
    char     pad0[4];
    uint32_t mKind;                                  // +0x04
};
struct cEditorNoun {
    char       pad0[0x18];
    cModelObj* mpModel;                              // +0x18
    int        mSpecies;                             // +0x1c
    cModelObj* GetModel();                           // 0x006c0200
    cGameData* GetGameData();                        // 0x00b18530
};
// ---- items of slice s00ed74f0 end

// ---- items of slice s00ed8490 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_148a22c[];
extern int __cdecl atexit(void*);
typedef void  (__thiscall *FV_v_s00ed_8490)(void*);
struct NounVec8a30 { int* begin; int* end; int* cap; int* pad0; int* pad1; };
struct GData8a30;
struct Holder8a30 {
    GData8a30* GetData(int);                      // 0x00f3e8a0
    char*      GetPlayer(int);                    // 0x00f3be60 (0x534-byte records)
    void       GetAllNouns(int, NounVec8a30*);    // 0x00f40d00 thiscall, ret 8
};
struct Game8a30 { char pad[0x74]; Holder8a30* holder; };
extern Game8a30* g_game8a30;                      // 0x016c7aa4
NounVec8a30 g_nounVec;          // 0x016c7708
int         g_nounVecGuard;     // 0x016c771c
struct RefObj_ed8610 {
    virtual void AddRef();
    virtual void Release();                  // +0x04
};
struct Ref_ed8610 {
    RefObj_ed8610* mp;
    ~Ref_ed8610() { if (mp) mp->Release(); }
};
struct RefArr3_ed8610 {
    Ref_ed8610 m[3];
};
struct Obj8610 {
    void* mpVtbl;                            // +0x00
    Ref_ed8610 m04;                          // +0x04
    Ref_ed8610 m08;                          // +0x08
    Ref_ed8610 m0c;                          // +0x0c
    RefArr3_ed8610 m10;                      // +0x10
    RefArr3_ed8610 m1c;                      // +0x1c
    void f();
};
void* __cdecl FUN_00b3d300(void);                 // SP::NounManager
void* __cdecl FUN_00b1f9b0(void*);                // cGameNounManager::GetAllNouns
void* __cdecl SP_EffectsManager(void);            // 0x67ddd0
int   __cdecl FUN_006c0200(void*);                // 0x6c0200
typedef void  (__thiscall *FVf_v)(void*);
typedef void* (__thiscall *FVf_p)(void*);
typedef void  (__thiscall *FVf_i)(void*, int);
typedef void  (__thiscall *FVf_iip)(void*, int, int, void*);
struct S_c8ad30 {
    void f(int, int);   // 0x00c8ad30
};
struct S_c8b210 { void f(int); };
struct S_c88a00 { void f(int, float); };
struct S_c8a200 { void f(int, float); };
struct Obj8780 { void f(unsigned char b); };
static void grab(int id, int* field)
{
    int* em = (int*)SP_EffectsManager();
    int* old = *(int**)field;
    if (old != 0) {
        *(int**)field = 0;
        ((FVf_v)(*(void***)old)[4 / 4])(old);
    }
    ((FVf_iip)(*(void***)em)[0x2c / 4])(em, id, 0, field);
}
static void clear2(int* field)
{
    int* p = *(int**)field;
    if (p != 0) {
        ((FVf_i)(*(void***)p)[0xc / 4])(p, 0);
        int* q = *(int**)field;
        if (q != 0) {
            *(int**)field = 0;
            ((FVf_v)(*(void***)q)[4 / 4])(q);
        }
    }
}
struct GData8a30 {                                // per-player data holder (SP::cGameData-like)
    bool IsKind1();                               // 0x00f25330
    bool IsKind2();                               // 0x00f25470
};
// ---- items of slice s00ed8490 end

// ---- items of slice s00ed9150 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_1470f1c;
extern unsigned char g_16065f8;
extern void* g_15ad298;
typedef void  (__thiscall *FV_v_s00ed_9150)(void*);
typedef void* (__thiscall *FV_p_s00ed_9150)(void*);
typedef void  (__thiscall *FV_i_s00ed_9150)(void*, int);
typedef void* (__thiscall *FV_ip)(void*, int);
typedef int   (__thiscall *FV_r0)(void*);
struct Step95d0 {
    int   mType;    // +0x00
    void* mA;       // +0x04
    void* mB;       // +0x08
};
void* __cdecl FUN_00ed9040(int, float*);
extern void* g_16c7aa4_s00ed_9150;
void  __cdecl FUN_00ed9150(int* out, float* pos, void* objPos, float f);
void  __cdecl FUN_00ed95d0(int* out1, int* out2, float* pos, Step95d0* step);
void  __cdecl FUN_00ed9560(int* out, void* pos, int key);
void* __cdecl SP_GameInputManager(void);       // 0xb3d250
void* __cdecl FUN_00efc510(void);
char  __cdecl FUN_00efcd90(void);
void* __cdecl FUN_0067cab0(void);
int   __fastcall FUN_008013c0(void*, int);         // cCursorManager::GetCursor (edx = dummy)
void  __fastcall FUN_00801bb0(void*, int, int);    // cCursorManager::SetCursor (edx = dummy)
void* __cdecl SP_App(void);                    // 0x67dd10
int   __cdecl FUN_008d2fb0(int);               // 0x8d2fb0
char  __fastcall FUN_00b0f9a0(void*, int);     // 0xb0f9a0 (edx = dummy)
void* __cdecl FUN_00b3d4d0(void);              // 0xb3d4d0
void* __cdecl FUN_00b3d230(void);              // 0xb3d230
char  __fastcall FUN_00b5ca60(void*, int);     // 0xb5ca60 (edx = dummy)
void* __cdecl FUN_00b3d240(void);              // 0xb3d240
void* __cdecl FUN_00b18e00(void*);             // 0xb18e00
char  __cdecl FUN_00dd18b0(void*);             // 0xdd18b0
char  __cdecl FUN_00e09ad0(void*);             // 0xe09ad0
void* __fastcall FUN_00f3e8a0(void*, int, int);     // 0xf3e8a0 (edx = dummy)
char  __fastcall FUN_00f25530(void*, int);     // 0xf25530 (edx = dummy)
void* __cdecl FUN_0067ddd0(void);              // 0x67ddd0 (effects manager)
// ---- items of slice s00ed9150 end

// ---- items of slice s00ed9f10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char* g_pMagic;                 // 0x016c7aa4
extern char* g_pStrategy;              // 0x015ad298
extern char* g_pStrategySelf;          // 0x015ad328
extern "C" int   EA_Audio_GetSystemAT();              // 0x00a206f0
extern "C" void* GameInputManager();                  // 0x00b3d250
extern "C" void  __fastcall FUN_008014a0(void*);      // 0x008014a0
extern "C" void* CursorManager();                     // 0x0067cab0
extern "C" int   IsModifierKeyDown(int);              // 0x008d2fb0
extern "C" int   cTerrainCameraController_KeysHeld(void*); // 0x00b0f9a0
extern "C" int   FUN_00809970();                      // 0x00809970
extern "C" void  ScenarioTutorials_ReleaseInput();    // 0x00efc860
extern "C" void  ScenarioTutorials_CaptureInput();    // 0x00efc890
extern "C" void* GetRecorderState();                  // 0x00435e90
extern "C" void  FUN_00ed4b60(void*);                 // 0x00ed4b60
extern "C" void  FUN_00ed76e0(void*, int);            // 0x00ed76e0
extern "C" void  FUN_00ed4840(void*);                 // 0x00ed4840
extern "C" void  FUN_00ed48b0(void*);                 // 0x00ed48b0
extern "C" void  FUN_00ed9b40(void*);                 // 0x00ed9b40
extern "C" void  FUN_00ed9b80(void*);                 // 0x00ed9b80
extern "C" void  FUN_00ed9bd0(void*);                 // 0x00ed9bd0
extern "C" void  FUN_00ed9c20(void*);                 // 0x00ed9c20
extern "C" void  FUN_00ed9c60(void*);                 // 0x00ed9c60
extern "C" void  FUN_00ee9260(void*);                 // 0x00ee9260
extern "C" void  cSPPaletteItem_GetPriority(void*);   // 0x00641770
extern "C" void  FUN_00f03ff0(int, void*, int);       // 0x00f03ff0
extern "C" void  FUN_00f01e60(void*);                 // 0x00f01e60
extern "C" void  ScenarioTutorials_TickStopwatch(int);// 0x00efe310
extern "C" void  ScenarioTutorials_SetTargetVisible(int); // 0x00efe4a0
extern "C" void  ScenarioTutorials_ToggleTarget(float);// 0x00efe510
extern "C" void  FUN_00e09bf0(void*);                 // 0x00e09bf0
extern "C" void* GetRefCounted18(void*);              // 0x00eebf80
extern "C" void  cUIBanningContent_ShowConfirmationDialog(int); // 0x00dd1aa0
extern "C" void  CursorTable_AddCursor(void*, void*, void*, void*, void*, void*); // 0x00802050
extern "C" int   Menu2_OnMenuItemSelected(void*, void*, void*); // 0x0081bef0
extern "C" void* Hashtable_DoFindNode(void*, const void*);      // 0x006ab760
extern "C" int FUN_00ed9f10(void* self, void* a, void* b);
typedef void  (__thiscall *FnV)(void*);
typedef int   (__thiscall *FnI)(void*, int);
typedef void* (__thiscall *FnP)(void*);
typedef void* (__thiscall *FnPI)(void*, int);
typedef void* (__thiscall *FnPIII)(void*, int, int, int);
typedef int   (__thiscall *FnII)(void*, int, int);
extern uint8_t g_bEditorMode;          // 0x016065f8
extern uint8_t g_modeObj[];            // 0x016065d8
extern uint32_t g_msgTable[];          // 0x0148a238  (0x7c bytes of message ids)
extern uint32_t g_menuTable[];         // 0x015ac448  (0x78 entries of 0xc bytes)
struct ResourceMan {
    virtual void Unk00();
    virtual void Unk04();
    virtual void Unk08();
    virtual bool Load(const void* key, int, int, int, int, int);  // slot +0x0c
};
extern "C" void* MessageServer_s00ed_9f10();                     // 0x0067dcc0
extern "C" void  FUN_00f01f40(uint32_t, void*);       // 0x00f01f40
extern "C" void  cSPUISpace_KillSetiEffects(uint32_t, uint32_t); // 0x00435ed0
extern "C" void  SetGlobalProperty(uint32_t, float);  // 0x005ca880
extern "C" ResourceMan* ResourceMan_GetManager();     // 0x0067dcd0
struct InputStrategy {
    void*    mVtbl;               // +0x00
    uint32_t mField04;            // +0x04
    void*    mList08;             // +0x08
    void*    mList0c;             // +0x0c
    void*    mList10;             // +0x10
    uint8_t  mFlag14;             // +0x14
    uint32_t mField18;            // +0x18
    uint32_t mField1c;            // +0x1c
    uint32_t mField20;            // +0x20
    void*    mList24;             // +0x24
    uint32_t mField28;            // +0x28
    uint32_t mField2c;            // +0x2c
    uint8_t  mFlag30;             // +0x30
    uint32_t mField34;            // +0x34
    uint32_t mMenu38;             // +0x38
    uint32_t mNaming3c;           // +0x3c  cSPEditorNaming sub-object
    uint32_t mSub44;              // +0x44  RefCount/IMsgHandler vtable
    uint32_t mField48;            // +0x48
    uint32_t mField4c;            // +0x4c
    uint8_t  mFlag50;             // +0x50
    uint8_t  mFlag51;             // +0x51
    void*    mMsgServer54;        // +0x54
    void*    mHandler58;          // +0x58
    uint32_t mHandlerId5c;        // +0x5c
    uint32_t mHandlerCount60;     // +0x60
    uint32_t mHandler64;          // +0x64
    uint32_t mCursorState6c;      // +0x6c
    uint32_t mEntry7c[4];         // +0x7c
    uint32_t mEntry8c[4][3];      // +0x8c .. +0xbb
    uint32_t mEntryBc[4];         // +0xbc
    uint32_t mHandlerCc;          // +0xcc
    uint32_t mHandlerD0;          // +0xd0
    uint32_t mHandlerD4;          // +0xd4
    uint32_t mHandlerD8;          // +0xd8
    uint32_t mHandlerDc;          // +0xdc

    InputStrategy* FUN_00edaa80();
    void  FUN_00edab50();
    void  FUN_00eda9a0();
    void  FUN_00eda130();
    int   FUN_00eda2f0(uint32_t msg, void* data);
    int   FUN_00edae50(uint32_t msg, void* data);
    void  FUN_00edae80();
    void  FUN_00edaca0();
    void  FUN_00edad00();
    void  FUN_00edadd0();
    int   FUN_00eda6f0(uint32_t msg, void* data);
};
struct Recorder { int FUN_00f04060(); };
struct NamingBase {
    int HandleMessage(uint32_t msg, void* data);      // 0x005bf9d0
};
// ---- items of slice s00ed9f10 end

// ---- items of slice s00edaf10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void cSPEditorNaming_ctor();        // 0x005bfff0
extern void cSPEditorNaming_Init();        // 0x005bfd40
extern int   FUN_00edabf0(int);            // 0x00edabf0
extern void  FUN_00f04060();               // 0x00f04060
extern void* cSPUILayout_FindWindowByID(void*, int, int); // 0x008105b0
extern void  SPUIHelpers_SetWindowImage(void*, void*, int);          // 0x00807bb0
extern void  SPUIHelpers_SetTooltipText(void*, int);                 // 0x00806de0
extern int   cGameData_GetPoliticalID(void*);                        // 0x005aacf0
extern int   FUN_0067dd60();                                         // 0x0067dd60
extern void* cSPUIPopupMenuWin_AddMenuItem(void*, void*, int, void*, int); // 0x0081b6a0
extern void  FUN_00edaca0();               // 0x00edaca0
extern void  FUN_00edad00();               // 0x00edad00
extern void  FUN_00edadd0();               // 0x00edadd0
extern void  FUN_00edafd0(void*, void**);  // 0x00edafd0
extern int   FUN_00edac50(int);            // 0x00edac50
extern int   FUN_00edac70(int);            // 0x00edac70
extern int   FUN_00f066c0(int*, void*);    // 0x00f066c0
extern void  FUN_00f03ff0();               // 0x00f03ff0
extern void  FUN_00efbbe0(int, int);       // 0x00efbbe0
extern int   EA_Messaging_MessageServer(); // 0x0067dcc0
extern void  EA_Messaging_RemoveHandler(void* h, void* a, void* b, void* c, void* d); // 0x00571db0
extern int   ScenarioTutorials_GetActive();// 0x00efc520
extern void  SP_cSPUISpace_KillSetiEffects(int, int); // 0x00435ed0
extern int   FUN_00f3be60(int);            // 0x00f3be60
extern void  FUN_00edfda0(int, int*);      // 0x00edfda0
extern int   FUN_006c0200();               // 0x006c0200
extern int   FUN_00ee31d0();               // 0x00ee31d0
extern void  FUN_00f3bfc0();               // 0x00f3bfc0
extern void* FUN_00f38c70();                         // 0x00f38c70
extern void  FUN_00f47630(void*);                    // 0x00f47630
extern "C" char g_148a46c[];   // 0x0148a46c message id list
extern "C" void _ReadWriteBarrier(void);
extern "C" char g_13eb394[];   // IHandler vftable
extern "C" char g_13ec458[];
extern "C" char g_148a478[];   // cScenarioEditModeScriptActsBarUI vftable
extern "C" char g_148a470[];   // cScenarioEditModeScriptActsBarUI IHandler vftable
#pragma intrinsic(_ReadWriteBarrier)
struct cString { char x[0x20]; };
typedef void* (__thiscall *FnPII)(void*, int, int);
extern void* operator_new(uint32_t size, const char* name, int, int, const char*, int); // 0x00f473a0
struct cSPEditorNamingBase {
    void Shutdown();                       // 0x005bfb90
    void SetExpanded(int on);              // 0x005c0380
    bool HandleUIMessage(void* window, void* msg); // 0x005c0100
    void Init();                           // 0x005bfd40
    void ctor();                           // 0x005bfff0
};
struct cSPUILayout_s00ed_af10 {
    bool Init(void* key, int a, int b);              // 0x008120d0
    bool SetParentWin(void* parent, int a, int b);   // 0x008121b0
    void SetVisibility(int on);                      // 0x00810590
    void Shutdown(int a);                            // 0x00811ad0
    void* FindWindowByID(int id, int b);             // 0x008105b0
};
struct cConnectionDialog { cConnectionDialog* ctor(); }; // 0x00810000
struct cSPGuardMgr {
    int  FUN_00f066c0(int* a, void* b);              // 0x00f066c0
    void FUN_00f03ff0(int a, void* b, int c);        // 0x00f03ff0
    void FUN_00f3bfc0(void* a, void* b, int c, int d); // 0x00f3bfc0
    int  FUN_00f3be60(int a);                        // 0x00f3be60
};
struct cSPDialogHolder { void FUN_00f47630(void* p); }; // 0x00f47630
struct cSPDialogMem    { void* FUN_00f38c70(); };       // 0x00f38c70
struct cSPHintHolder  { void FUN_00efbbe0(int a, int b); }; // 0x00efbbe0
struct cSPActsBarOps  { void FUN_00edadd0(); };          // 0x00edadd0
struct cSPRecorder    { int  FUN_006c0200(); };          // 0x006c0200
struct cSPRecording   { int  FUN_00ee31d0(); };          // 0x00ee31d0
extern void  cString_ctor0(cString*);                                // 0x006b5060
extern void  cString_Load(cString*, int, int, int);                  // 0x006b54b0
extern int   cString_GetText(cString*, int, int);                    // 0x006b55c0
extern void  cString_dtor(cString*);                                 // 0x006b5240
extern int   GetRecorderState_s00ed_af10();           // 0x00435e90
struct ERefVec { void erase(void* begin, void* end); };
class cSPUIAnimator_s00ed_af10 { public:
    bool Empty();    // 0x007f6340
    void Update();   // 0x007f63b0
    void ctor();     // 0x007f83e0
    void dtor();     // 0x007f8c20
    void Reset();    // 0x007f8f00
};
struct ActsEntry { uint32_t a, b, c; };
extern ActsEntry g_acts[];   // 0x015ac448
struct ActsBarUI {
    char pad[0xe0];
    void FUN_00edb120(int idx);
    void FUN_00edb4c0(int* level);
    void FUN_00edb6c0();
    void FUN_00edb730();
    bool FUN_00edb750(void* window, void* msg);
    void FUN_00edb9b0(int on);
    void FUN_00edbef0_();   // placeholder (unused)
};
struct cScenarioEditModeScriptActsBarUI {
    char pad[0x50];
    cScenarioEditModeScriptActsBarUI* ctor();
    void dtor();
    void FUN_00edbdd0(int a);
    bool FUN_00edbac0(void* parent);
    void FUN_00edbd30(int on);
    void FUN_00edbe60();
};
extern uint32_t SPUIHelpers_GetImageFromTexture(int, int, int, int); // 0x008060d0
extern void SPUIHelpers_SetDrawableImage(void*, uint32_t, int);      // 0x008068d0
struct RunInfo { uint32_t d[4]; };
struct MsgServer_00edbd30 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual void AddHandler(void* handler, unsigned id);   // +0x24
};
struct Window_00edbd30 {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
    virtual void v30();
    virtual void SetFlag(int flag, int on);                 // +0x7c
};
struct ActsBarView_00edbd30 {
    char pad00[8];
    char mHandler[4];           // +0x08 IHandler base
    cSPUILayout_s00ed_af10* mpLayout;      // +0x0c
    Window_00edbd30* mpWindow;  // +0x10
    char pad14[4];
    MsgServer_00edbd30* mpServer; // +0x18
    void* mpHandler;            // +0x1c
    void* mpIds;                // +0x20
    int   mCount;               // +0x24
    int   mPriority;            // +0x28
};
// ---- items of slice s00edaf10 end

// @ 0x00ed1cf0
void __cdecl FUN_00ed1cf0(char* p, int a, int b)
{
    if (p != 0) {
        char* t = *(char**)(p + 0x24);
        if (t != 0) {
            void* f = *(void**)(p + 0x28);
            if (f != 0)
                ((void(__thiscall*)(void*, int, int))f)(*(char**)(p + 0x2c) + (int)t, a, b);
        }
    }
}

// @ 0x00ed1d70
void* __stdcall FUN_00ed1d70(int a, void* spec)
{
    void* p;
    if (spec == 0)
        spec = FUN_009512c0();
    p = FUN_009512d0(0xa0, 8, "UTFWin/cSPScenarioSwatchEditItemUI", spec);
    if (p != 0) {
        p = ((SwatchUIRaw*)p)->CtorEditItem();
        if (p != 0) {
            p = ((FV_i)(*(void***)((char*)p + 8))[0xc / 4])((char*)p + 8, 0x4785a3d);
            if (p != 0)
                return (char*)p + 0xc;
        }
    }
    return 0;
}

// @ 0x00ed1dc0
void* __stdcall FUN_00ed1dc0(int a, void* spec)
{
    void* p = EAAllocate(0x6c, "UI/cSPScenarioSwatchItemUI", 0, 0, 0, 0);
    if (p != 0) {
        p = ((SwatchUIRaw*)p)->CtorItem();
        if (p != 0) {
            p = ((FV_i)(*(void***)((char*)p + 8))[0xc / 4])((char*)p + 8, 0x4785a3d);
            if (p != 0)
                return (char*)p + 0xc;
        }
    }
    (void)a;
    return 0;
}

// @ 0x00ed1e10
int __fastcall FUN_00ed1e10(Container* self, int* unused, int param)
{    int   i;
    void* p;
    void* cat;

    p = self->hPaletteCatUI;
    if (p != 0)
        cat = ((FV_i)(*(void***)p)[0xc / 4])(p, 0x52deed23);
    else
        cat = 0;

    i = 0;
    if ((*(int*)((char*)cat + 0x38) - *(int*)((char*)cat + 0x34) & -4) > 0) {
        do {
            if (param == (int)((void*(__thiscall*)(void*, int))FUN_005cae30)(cat, i))
                return i;
            ++i;
        } while (i < (*(int*)((char*)cat + 0x38) - *(int*)((char*)cat + 0x34)) >> 2);
    }
    (void)unused;
    return -1;
}

// @ 0x00ed1e70
int __fastcall FUN_00ed1e70(Container* self, int* unused, int key, int arg)
{
    EntryVec* v = &self->v0;
    if (key == 7)
        v = &self->v1;
    Entry* e = v->b;
    Entry* end = v->e;
    int count = 0;
    for (; e != end; ++e) {
        if (e->cat == key && e->page == arg && ((char(__thiscall*)(void*))FUN_00ecdb80)(e->a) == 0)
            ++count;
    }
    (void)unused;
    return count;
}

// @ 0x00ed1ec0
void __fastcall FUN_00ed1ec0(Container* self)
{
    Entry** v[2];
    unsigned i;

    v[0] = &self->vec0;
    v[1] = &self->vec1;
    for (i = 0; i < 2; ++i) {
        Entry** tab = (Entry**)v[i];
        Entry* e = tab[0];
        Entry* end = tab[1];
        for (; e < end; ++e)
            ((FV_v)(*(void***)e->a)[0x20 / 4])(e->a);
    }
}

// @ 0x00ed1f00
void* __stdcall FUN_00ed1f00(Entry** tab, int alloc)
{
    Entry* e = tab[0];
    Entry* end = tab[1];
    for (; e < end; ++e) {
        if (((int(__thiscall*)(void*))FUN_007f54d0)(e->a) == alloc)
            return e;
    }
    return 0;
}

// @ 0x00ed1f40
void* __stdcall FUN_00ed1f40(Entry** tab)
{
    Entry* e = tab[0];
    Entry* end = tab[1];
    for (; e < end; ++e) {
        if (((char(__thiscall*)(void*))FUN_00ecdb80)(e->a) != 0)
            return e;
    }
    return 0;
}

// @ 0x00ed1f70
void* __stdcall FUN_00ed1f70(Entry** tab, int key)
{
    Entry* e;
    Entry* end;

    if (key == (int)0xd37c1045)
        key = (int)0x5b3d1d0d;
    else if (key == (int)0xc7fdcb1e)
        key = (int)0x6031c03a;

    e = tab[0];
    end = tab[1];
    for (; e < end; ++e) {
        SwatchQuery* item = (SwatchQuery*)e->a;
        if (item->GetQueryId() == key && item->HasDefaultIndex())
            return e;
    }
    return 0;
}

// @ 0x00ed20c0
int __fastcall FUN_00ed20c0(Container* self, int* unused, int key)
{
    Entry* e;

    if (key == (int)0xd37c1045)
        key = (int)0x5b3d1d0d;
    else if (key == (int)0xc7fdcb1e)
        key = (int)0x6031c03a;

    e = self->vec0;
    int count = 0;
    for (; e != self->vec0End; ++e) {
        SwatchQuery* item = (SwatchQuery*)e->a;
        if (item->GetQueryId() == key && item->HasDefaultIndex())
            ++count;
    }
    (void)unused;
    return count;
}

// @ 0x00ed2130
void __stdcall FUN_00ed2130(void** slot, void* value)
{
    void* old;
    void* qi;
    void* made;

    if (value == 0) {
        if (*slot == 0)
            return;
        qi = ((FV_i)(*(void***)((char*)*slot + 8))[0xc / 4])((char*)*slot + 8, 0x722de52);
        if (qi == 0) {
            ((void(__thiscall*)(void**, void*))FUN_00572620)(slot, 0);
            return;
        }
        made = EAAllocate(0x24, "UI/cSPScenarioPaletteItemUIBase", 0, 0, 0, 0);
        if (made == 0) {
            ((void(__thiscall*)(void**, void*))FUN_00572620)(slot, 0);
            return;
        }
        ((void(__thiscall*)(void**, void*))FUN_00572620)(slot, FUN_00ece870(made, qi));
        return;
    }

    ((FV_p)(*(void***)value)[0x10 / 4])(value, *slot);
    old = *slot;
    if (value != old) {
        ((FV_v)(*(void***)value)[4 / 4])(value);
        *slot = value;
        if (old != 0)
            ((FV_v)(*(void***)old)[8 / 4])(old);
    }
}

// @ 0x00ed2210
void* __fastcall FUN_00ed2210(void** dst, void* unused, void* src)
{
    void* a = ((void**)src)[0];
    dst[0] = a;
    if (a != 0)
        ((FV_v)(*(void***)a)[4 / 4])(a);
    a = ((void**)src)[1];
    dst[1] = a;
    if (a != 0)
        ((FV_v)(*(void***)a)[8 / 4])(a);
    dst[2] = ((void**)src)[2];
    dst[3] = ((void**)src)[3];
    ((int*)dst)[4] = ((int*)src)[4];
    (void)unused;
    return dst;
}

// @ 0x00ed2260
void* __fastcall FUN_00ed2260(void** dst, void* unused, void** src)
{
    void* na;
    void* oa;
    void* nb;
    void* ob;

    na = src[0];
    oa = dst[0];
    if (na != oa) {
        if (na != 0)
            ((FV_v)(*(void***)na)[4 / 4])(na);
        dst[0] = na;
        if (oa != 0)
            ((FV_v)(*(void***)oa)[8 / 4])(oa);
    }
    nb = src[1];
    ob = dst[1];
    if (nb != ob) {
        if (nb != 0)
            ((FV_v)(*(void***)nb)[8 / 4])(nb);
        dst[1] = nb;
        if (ob != 0)
            ((FV_v)(*(void***)ob)[0xc / 4])(ob);
    }
    dst[2] = src[2];
    dst[3] = src[3];
    ((int*)dst)[4] = ((int*)src)[4];
    (void)unused;
    return dst;
}

// @ 0x00ed22e0
void* __cdecl FUN_00ed22e0(void* first, void* last, void* dst)
{
    for (; first != last; first = (char*)first + 0x14, dst = (char*)dst + 0x14) {
        if (dst != 0) {
            void* a;
            a = ((void**)first)[0];
            *(void**)dst = a;
            if (a != 0)
                ((FV_v)(*(void***)a)[4 / 4])(a);
            a = ((void**)first)[1];
            ((void**)dst)[1] = a;
            if (a != 0)
                ((FV_v)(*(void***)a)[8 / 4])(a);
            ((int*)dst)[2] = ((int*)first)[2];
            ((int*)dst)[3] = ((int*)first)[3];
            ((int*)dst)[4] = ((int*)first)[4];
        }
    }
    return dst;
}

// @ 0x00ed2340
void* __cdecl FUN_00ed2340(void* first, void* last, void* dst)
{
    for (; first != last; first = (char*)first + 0x14, dst = (char*)dst + 0x14) {
        void* a = ((void**)first)[1];
        if (a != 0)
            ((FV_v)(*(void***)a)[0xc / 4])(a);
        a = ((void**)first)[0];
        if (a != 0)
            ((FV_v)(*(void***)a)[8 / 4])(a);
    }
    return dst;
}

// @ 0x00ed2410
void __fastcall FUN_00ed2410(Container* self, int* unused, int param2, int param3, int param4)
{
    int   i, k, j;
    void* cat;
    int   n;
    int   keys[2];
    Entry** v[2];

    if (self->hPaletteCatUI == 0)
        cat = 0;
    else
        cat = ((FV_i)(*(void***)self->hPaletteCatUI)[0xc / 4])(self->hPaletteCatUI, 0x52deed23);

    n = (*(int*)((char*)cat + 0x38) - *(int*)((char*)cat + 0x34)) >> 2;
    for (i = 0; i < n; ++i)
        if (param2 == (int)FUN_005cae30(cat, i))
            break;
    if (i >= n)
        return;

    keys[0] = param3;
    keys[1] = param4;

    for (k = 0; k < 2; ++k) {
        int page = keys[k];
        void* pageUI;
        if (page < 0)
            continue;
        if (page >= (int)((*(int*)((char*)self + 0x8c) - *(int*)((char*)self + 0x88)) >> 3))
            continue;
        pageUI = FUN_005c2e50(self, page);

        v[0] = &self->vec0;
        v[1] = &self->vec1;
        for (j = 0; j < 2; ++j) {
            Entry** tab = (Entry**)v[j];
            Entry* e = tab[0];
            Entry* end = tab[1];
            for (; e < end; ++e) {
                if (e->cat != i || e->page != page)
                    continue;
                if (page == param4) {
                    if (e->a != 0) {
                        void* qi = ((FV_i)(*(void***)((char*)e->a + 8))[0xc / 4])(
                                        (char*)e->a + 8, 0x722de52);
                        if (qi != 0) {
                            void* made = EAAllocate(0x24, "UI/cSPScenarioPaletteItemUIBase",
                                                    0, 0, 0, 0);
                            if (made != 0)
                                made = FUN_00ece870(made, qi);
                            else
                                made = 0;
                            {
                                void* old = e->a;
                                if (made != old) {
                                    if (made != 0)
                                        ((FV_v)(*(void***)made)[4 / 4])(made);
                                    e->a = made;
                                    if (old != 0)
                                        ((FV_v)(*(void***)old)[8 / 4])(old);
                                }
                            }
                        }
                    }
                } else if (page == param3) {
                    void* sc = FUN_005cae30(pageUI, e->sub);
                    void* val = 0;
                    if (sc != 0)
                        val = ((FV_i)(*(void***)((char*)sc + 0xc))[0xc / 4])(
                                    (char*)sc + 0xc, 0x722de52);
                    FUN_00ed2130(&e->a, val);
                }
            }
        }
    }
}

// @ 0x00ed2600
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

// @ 0x00ed2a50
void** RefMap::InsertUnique(void** result, RBNode* pos, void** key, char flag)
{
    int side = (flag == 0 && pos != (RBNode*)&mAnchor && *key >= pos->mpValue) ? 1 : 0;
    RBNode* node = (RBNode*)operator_new(0x14, "Simulator", 0, 0, (const char*)g_13ebb38, 0xd1);
    if (&node->mpValue) {
        node->mpValue = *key;
        if (node->mpValue)
            ((RefObj*)node->mpValue)->mpVtbl->mSlot08(node->mpValue);
    }
    eastl_RBTreeInsert(node, pos, &mAnchor, side);
    void** destination = *(void** volatile*)&result;
    mSize++;
    *destination = node;
    return destination;
}

// @ 0x00ed2ae0
void RefMap::Erase(void** result, RBNode* node)
{
    void* next;
    RBNode* n = node;
    mSize--;
    next = (void*)eastl_RBTreeIncrement(n);
    eastl_RBTreeErase(n, &mAnchor);
    if (RefObj* v = (RefObj*)n->mpValue)
        v->mpVtbl->mSlot0c(v);
    operator_delete(n);
    *result = next;
}

// @ 0x00ed2bc0
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

// @ 0x00ed3120
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

// 0x00ed3350 (byte-exact lifted version: match/slices/s00ed3350/s00ed3350.cpp)
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

// 0x00ed33a0 (byte-exact lifted version: match/slices/s00ed33a0/s00ed33a0.cpp)
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

// @ 0x00ed33f0
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

// @ 0x00ed35d0
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

// @ 0x00ed3740
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

// @ 0x00ed37c0
Record* RecordMap::Find(int* key)
{
    Record* end = mpEnd;
    Record* pos = (Record*)FUN_00ed29b0(mpBegin, end, key, flags);
    if (pos != end && *key >= *(int*)pos)
        return (Record*)((char*)pos + 8);

    Record tmp;
    FUN_00f2d260(&tmp);
    *(int*)((char*)&tmp + 0x20) = *key;
    FUN_00dff1a0((char*)&tmp + 4, (char*)key + 4);

    int k = *(int*)((char*)&tmp + 0x20);
    end = mpEnd;
    if (pos == end || *(int*)pos <= k) {
        pos = mpEnd;
    } else {
        pos = mpBegin;
    }
    pos = FUN_00ed3740(this, pos, (int*)((char*)&tmp + 0x20));
    if (pos == end || k < *(int*)pos) {
        pos = (Record*)((char*)FUN_00ed3740(this, pos, (int*)((char*)&tmp + 0x20)));
    }
    FUN_00dfce90((char*)&tmp + 4);
    FUN_00dfce90(&tmp);
    return (Record*)((char*)pos + 8);
}

// @ 0x00ed38a0
void ScnRecBody::RemoveIcon(int key)
{
    int id = key;
    if (id == -1)
        return;

    char* db = g_16c7aa4_s00ed_37c0->sub->db;
    Record* rec = ((RecordMap*)(db + 0x2bf4))->Find(&key);

    PalEntry* e = (PalEntry*)FUN_00ed1f00(&palVecA, id);
    if (!e) {
        int icon = FUN_00eece20((int)rec);
        e = (PalEntry*)FUN_00ed1f70(&palVecA, icon);
        if (!e)
            return;
        void* obj = e->item;
        ((void(__thiscall*)(void*, int))(*(void***)obj)[0x1c / 4])(obj, key);
    }
    FUN_00ed3120(e->pal, 1);
}

// @ 0x00ed3920
void ScnRecBody::ClearTwo(int key)
{
    RecordMap* map = (RecordMap*)(g_16c7aa4_s00ed_37c0->sub->db + 0x2bf4);
    map->Find(&key);

    PalEntry* e = (PalEntry*)FUN_00ed1f00(&palVecA, key);
    if (e) {
        void* obj = e->item;
        ((void(__thiscall*)(void*))(*(void***)obj)[0x20 / 4])(obj);
        FUN_00ed3120(e->pal, 1);
    }

    e = (PalEntry*)FUN_00ed1f00(&palVecB, key);
    if (e) {
        void* obj = e->item;
        ((void(__thiscall*)(void*))(*(void***)obj)[0x20 / 4])(obj);
        FUN_00ed3120(e->pal, 1);
    }
}

// @ 0x00ed39a0
void ScnRecBody::DeselectTwo(int key)
{
    RecordMap* map = (RecordMap*)(g_16c7aa4_s00ed_37c0->sub->db + 0x2bf4);
    map->Find(&key);

    PalEntry* e = (PalEntry*)FUN_00ed1f00(&palVecA, key);
    if (e) {
        void* obj = e->item;
        ((void(__thiscall*)(void*))(*(void***)obj)[0x14 / 4])(obj);
    }

    e = (PalEntry*)FUN_00ed1f00(&palVecB, key);
    if (e) {
        void* obj = e->item;
        ((void(__thiscall*)(void*))(*(void***)obj)[0x14 / 4])(obj);
    }
}

// @ 0x00ed3a00
void ScnRecBody::Finish()
{
    FUN_00ed1ec0((RecordMap*)(g_16c7aa4_s00ed_37c0->sub->db + 0x2bf4));

    char* db  = g_16c7aa4_s00ed_37c0->sub->db;
    Record* b = *(Record**)&db[0x2bf4];
    Record* e = *(Record**)&db[0x2bf8];
    for (; b != e; b = (Record*)((char*)b + 0x27e8))
        RemoveIcon(*(int*)b);

    db = g_16c7aa4_s00ed_37c0->sub->db;
    unsigned count = *(unsigned*)&db[0x2c24];
    char* catBegin;
    if (count < 0x3fffffff)
        catBegin = *(char**)&db[0x2c10] + count * 0x238;
    else
        catBegin = *(char**)&db[0x2c14];
    char* catEnd = *(char**)&db[0x2c14];

    for (;;) {
        if (catEnd == catBegin)
            return;
        int key = *(int*)(catBegin + 4);
        if (key != -2) {
            char* vEnd = *(char**)&db[0x2c00];   // unused
            (void)vEnd;
            // scan palVecB for a matching allocator id
            char* vb = (char*)palVecB.mpBegin;
            char* ve = (char*)palVecB.mpEnd;
            bool found = false;
            for (char* p = vb; p < ve; p += 0x14) {
                if (GetAllocator(*(void**)p) == key) { found = true; break; }
            }
            if (!found) {
                for (char* p = vb; p < ve; p += 0x14) {
                    if (FUN_00ecdb80_s00ed_37c0(*(void**)p)) {
                        void* obj = *(void**)p;
                        ((void(__thiscall*)(void*, int))(*(void***)obj)[0x1c / 4])(obj, key);
                        FUN_00ed3120(*(void**)(p + 4), 1);
                        break;
                    }
                }
            }
        }
        do {
            unsigned f = *(unsigned*)catBegin;
            catBegin += 0x238;
            if ((f >> 0x1e) & 1)
                break;
        } while ((int)*(unsigned*)catBegin < 0);
    }
}

// @ 0x00ed3b20
void ScnRecBody::ChooseSubCategory(void* sub, int key)
{
    char* db = g_16c7aa4_s00ed_37c0->sub->db;
    Sub* node = g_16c7aa4_s00ed_37c0->sub;
    int alloc = GetAllocator(sub);
    if (alloc == -1) {
        int n = FUN_00f46450(key);
        ((void(__thiscall*)(void*, int))(*(void***)sub)[0x1c / 4])(sub, n);
        RemoveIcon(n);
    } else if (alloc == -2) {
        FUN_00f42580(key);
        db[0x14c] = 0;
        ((void(__thiscall*)(void*))(*(void***)sub)[0x14 / 4])(sub);
        FUN_00f40370(node);
        FUN_00f427c0(node);
    } else {
        FUN_00f43af0(alloc);
        Any* rec = FUN_00f3e8a0(db, alloc);
        *((char*)rec + 0x1c) = 0;
        ((void(__thiscall*)(void*))(*(void***)sub)[0x14 / 4])(sub);
        DeselectTwo(alloc);
        FUN_00f40370(node);
        FUN_00f427c0(node);
    }
    MsgServer* m = MessageServer();
    ((void(__thiscall*)(MsgServer*, unsigned, void*, void*))(*(void***)m)[5])(m, 0x07a12a49, 0, 0);
}

// @ 0x00ed4200
bool ScnRec::ProcessMessage(unsigned id, Any* arg)
{
    ScnRecBody* body = (ScnRecBody*)((char*)this - 8);

    if (id == 0x03150c27 || id == 0x044ef2b8) {
        PaletteCtrl* ui = (PaletteCtrl*)FUN_00ed1d20(mainWin);
        int catIndex = ui->GetCurrentCategoryIndex();
        if (id == 0x044ef2b8) {
            void* sub = ui->GetSubCategory(catIndex);
            void* w = *(void**)((char*)sub + 0x18);
            ((void(__thiscall*)(void*, unsigned, int))(*(void***)w)[0xf0 / 4])(w, 0x05d17546, 1);
            if (catIndex <= 5) {
                static const short kHint[6][2] = {
                    { 0x1a, 0x1b }, { 0x2c, 0x2d }, { 0x32, 0x33 },
                    { 0x40, 0x41 }, { 0x56, 0x57 }, { 0x5a, 0x43 },
                };
                void* u = *(void**)((char*)g_16c7aa4_s00ed_37c0->sub->doc);
                (void)u;
                UI::ToggleHint(g_16c7aa4_s00ed_37c0->sub->doc, kHint[catIndex][1], kHint[catIndex][0]);
            }
        }
        // walk both entry vectors and drop the entries of the current category
        for (int v = 0; v < 2; ++v) {
            PalVec* vec = (v == 0) ? &palVec0 : &palVec1;
            PalEntry* b = vec->mpBegin;
            PalEntry* e = vec->mpEnd;
            for (PalEntry* p = b; p < e; ++p) {
                Any* data = p->item ? VCall1<3, Any*>((char*)p->item + 8, 0x0722de52) : 0;
                if (p->cat == catIndex && data)
                    FUN_00ece300(data);
            }
        }
        Any* sub0 = (Any*)ui->GetSubCategory(ui->GetCurrentCategoryIndex());
        ((ScnRecBody*)((char*)this - 8))->FUN_00ed3120(sub0, 0);
        return false;
    }

    switch (id) {
    case 0x030c11c7: {
        if (!FUN_00ed21f0((char*)mainWin + 0x10) || *((char*)mainWin + 0x44))
            return false;
        FillEntry tmp;
        tmp.f0 = tmp.f4 = tmp.f8 = 0;
        FUN_00eef810(&tmp, (char*)mainWin + 0x18, 0, 0);
        VCall<0>(&tmp);
        FUN_00540520(&tmp);
        return false;
    }
    case 0x072ab904: {
        if (!arg)
            return false;
        Any* x = (Any*)FUN_00ed21d0((char*)arg + 0x20);
        FUN_00ed2600((char*)this - 8, x, 0);
        return false;
    }
    case 0x072abb02: {
        if (!arg)
            return false;
        Any* x = (Any*)FUN_00ed21d0((char*)arg + 0x20);
        Any* y = (Any*)FUN_01137690(x);
        y = y ? VCall1<3, Any*>(y, 0x0722de52) : 0;
        int alloc = GetAllocator(y);
        if (*(int*)((char*)arg + 0x14) == 0 || alloc == -1)
            return false;
        UI::ApplyPlacement((void*)0x015ad328, alloc);
        return false;
    }
    case 0x072bdb11: {
        body->Finish();
        return false;
    }
    case 0x07311fe9: {
        FUN_00ed3350((char*)this - 8, (int)arg);
        return false;
    }
    case 0x07311ff7: {
        FUN_00ed33a0((char*)this - 8, (int)arg);
        return false;
    }
    case 0x07326686: {
        body->ClearTwo((int)arg);
        return false;
    }
    case 0x07395b639: {
        body->DeselectTwo((int)arg);
        return false;
    }
    case 0x073e7b71: {
        if (!arg)
            return false;
        Any* x = (Any*)FUN_00ed21d0((char*)arg + 0x20);
        Any* editor = (Any*)FUN_00ecdbb0(x);
        int srcAlloc = GetAllocator(x);
        FUN_00f45970(g_16c7aa4_s00ed_37c0->sub);
        Any* slot = (Any*)FUN_00ecdbb0((char*)arg + 0x24);
        EditorRect r = VCall1<0, EditorRect>(slot, 0x0722de63);
        (void)editor; (void)srcAlloc; (void)r;
        return false;
    }
    case 0x07c7b9bb: {
        if (!arg)
            return false;
        Any* x = (Any*)((char*)arg + 0x20);
        x = x ? VCall1<3, Any*>(x, 0x0722de63) : 0;
        int alloc = GetAllocator(x);
        FUN_00f45970(g_16c7aa4_s00ed_37c0->sub);
        Any* y = (Any*)((char*)arg + 0x24);
        y = y ? VCall1<3, Any*>(y, 0x0722de63) : 0;
        Rect3 rr = VCall1<0, Rect3>(y, 0);
        if (rr.a) {
            body->ChooseSubCategory(x, (int)&rr);
        }
        if (alloc == -1) {
            int z = GetAllocator(y);
            if (z != -2) {
                Any* dbl = (Any*)g_16c7aa4_s00ed_37c0->sub->db;
                Any* p = FUN_00f3e8a0(dbl, GetAllocator(x));
                Any* q = FUN_00f3e8a0(dbl, GetAllocator(y));
                FUN_00dfed90((char*)p + 0x70, (char*)q + 0x70);
            }
        }
        FUN_00f45a80(g_16c7aa4_s00ed_37c0->sub);
        return false;
    }
    case 0x08292e7f: {
        if (!arg)
            return false;
        FUN_00ed2410((char*)this - 8, *(void**)((char*)arg + 8),
                     *(void**)((char*)arg + 0x10), *(void**)((char*)arg + 0x18));
        return false;
    }
    default:
        break;
    }
    return false;
}

// @ 0x00ed4730
void Obj4730::f(Vec_ed4730* list)
{
    ((S_ef72b0*)*(int*)(g_16c7aa4 + 0xd4))->f();
    if (list->mpBegin != list->mpEnd && list->mpBegin->a != 0) {
        ((S_f45970*)*(int*)(g_16c7aa4 + 0x74))->f();
        Getter_ed4730* r = *(Getter_ed4730**)(*(char**)((char*)this + 0x38) + 0xc);
        ((S_ed3b20*)((char*)this - 0xc))->f(r ? r->Get(0x722de52) : 0, list->mpBegin);
        for (unsigned i = 1; i < list->size(); i++) {
            S_f46450* m = *(S_f46450**)(g_16c7aa4 + 0x74);
            Item_ed4730* it = &list->mpBegin[i];
            int v = m->f(it);
            if (v != -1)
                ((S_ed38a0*)((char*)this - 0xc))->f(v);
        }
        ((S_f45a80*)*(int*)(g_16c7aa4 + 0x74))->f();
        S_644b60* obj = *(S_644b60**)((char*)this + 0x38);
        if (obj != 0) {
            obj->f();
            operator_delete(obj);
            *(int*)((char*)this + 0x38) = 0;
        }
    }
}

// @ 0x00ed48a0
char __cdecl FUN_00ed48a0(void* a, int* c)
{
    (void)a;
    unsigned v = (unsigned)c[2] - 1;
    unsigned r = (v & 0xffffff00u) | (v <= 9);
    return (char)r;
}

// @ 0x00ed8130
bool Panel::FUN_00ed8130(int msg, int type, int extra)
{
    if (type != 0x366a930d)
        return false;

    mCallout.mParam = msg;
    mCallout.mType  = type;
    mCallout.mExtra = extra;

    cSim* sim = g_16c7aa4_s00ed_74f0->sim;
    if (sim != 0) {
        mCallout.mMode = 4;
        int out;
        Key12 key;
        if (sim->Classify(&out)) {
            if (sim->f3b950()) {
                key = g_15ac208;
                CalloutMessageBox(&mCallout, &key);
                mCallout.mKey = key.a;
            } else {
                key = g_15ac1f0;
                CalloutMessageBox(&mCallout, &key);
                mCallout.mKey = key.a;
            }
        } else {
            key.a = 0; key.b = 0; key.c = 0;
            int hint = HintForState(out);
            key = g_15ac1fc;
            if (!sim->f3b920()) {
                ShowCallout();
            } else if (key.a != 0) {
                cUIHint* h = UIHints()->FindByID(hint);
                cNotifyTarget* t = NotifyHost()->GetTarget();
                if (h == 0) t->SetText(g_13ec468, 0);
                else        t->SetText(h->mText.GetText(), 0);
                CalloutMessageBox(&mCallout, &key);
                mCallout.mKey = key.a;
            }
        }
    }
    g_16c7aa4_s00ed_74f0->tutorials->f8860();
    return true;
}

// @ 0x00ed82e0
void FUN_00ed82e0(cPropStore* store, void* key, void* extra, char remove, float a, char b)
{
    bool found = store->Find(key);
    if (remove == 0) {
        if (found)
            store->Remove(key, 0);
        return;
    }
    if (found)
        return;
    store->Set3(key, extra, key);
    store->SetMax(key, g_148a228);
    store->SetA(key, a);
    store->SetB(key, b);
}

// @ 0x00ed8350
void FUN_00ed8350(cPropStore* store, void* key, unsigned idLo, unsigned idHi, char flag, float a, char b)
{
    cStoreObj* obj = store->FindObj(key);
    char changed;
    if (obj != 0) {
        uint64_t value = obj->GetValue();
        if ((unsigned)value != idLo || (unsigned)(value >> 32) != idHi)
            changed = 1;
        else
            changed = 0;
    } else {
        changed = 0;
    }

    if (flag == changed) {
        if (obj == 0)
            return;
        store->Remove(key, 0);
        if (!flag)
            return;
        if (!changed && obj != 0)
            return;
    } else if (obj != 0) {
        return;
    }

    store->Set3((void*)idLo, (void*)idHi, key);
    store->SetMax(key, g_148a228);
    store->SetA(key, a);
    store->SetB(key, b);
}

// @ 0x00ed83f0
void* FUN_00ed83f0(cEditorNoun* noun)
{
    void* result = &g_1489fe8;
    cModelObj* model = noun->GetModel();
    float value = model->mValue;
    bool positive = (g_1488874 < fabsf(value)) && (g_1485378 < value);

    uint32_t kind = noun->GetGameData()->mKind;
    switch (kind) {
    case 0x2399be55:
        return positive ? &g_148a0a8 : &g_148a078;
    case 0x24682294:
    case 0x476a98c7:
        return positive ? &g_148a048 : &g_148a018;
    }
    return result;
}

// @ 0x00ed8490
int __cdecl FUN_00ed8490(int p)
{
    if (*(char*)(p + 0x4c8) == 1) {
        int diff = *(int*)(p + 0x4d0) - *(int*)(p + 0x4cc);
        if ((diff & ~0x1f) > 0) {
            int* q = *(int**)(p + 0x4cc);
            int n = 0;
            do {
                if (q[3] == 3 && q[4] == 2)
                    return q[5];
                n++;
                q = (int*)((char*)q + 0x20);
            } while (n < (*(int*)(p + 0x4d0) - *(int*)(p + 0x4cc)) >> 5);
        }
    } else if (*(int*)(p + 0x4b0) == 3) {
        return *(int*)(p + 0x4bc);
    }
    return -1;
}

// @ 0x00ed8500
int __cdecl FUN_00ed8500(int p)
{
    if (*(char*)(p + 0x4c8) == 1) {
        int diff = *(int*)(p + 0x4d0) - *(int*)(p + 0x4cc);
        if ((diff & ~0x1f) > 0) {
            int* q = *(int**)(p + 0x4cc);
            int n = 0;
            do {
                if (q[3] == 4 && q[6] == 2)
                    return q[7];
                n++;
                q = (int*)((char*)q + 0x20);
            } while (n < (*(int*)(p + 0x4d0) - *(int*)(p + 0x4cc)) >> 5);
        }
    } else if (*(int*)(p + 0x4b4) == 3) {
        return *(int*)(p + 0x4c0);
    }
    return -1;
}

// @ 0x00ed8570
int __cdecl FUN_00ed8570(int p)
{
    if (*(char*)(p + 0x4c8) == 1) {
        int diff = *(int*)(p + 0x4d0) - *(int*)(p + 0x4cc);
        if ((diff & ~0x1f) > 0) {
            int* q = *(int**)(p + 0x4cc);
            int n = 0;
            do {
                if (q[3] == 7 && q[4] == 2)
                    return q[7];
                n++;
                q = (int*)((char*)q + 0x20);
            } while (n < (*(int*)(p + 0x4d0) - *(int*)(p + 0x4cc)) >> 5);
        }
    } else if (*(int*)(p + 0x4b8) == 5) {
        return *(int*)(p + 0x4c4);
    }
    return -1;
}

// @ 0x00ed8610
void Obj8610::f()
{
    mpVtbl = (void*)g_148a22c;
    Ref_ed8610* q = m1c.m + 3;
    int i = 2;
    do {
        --q;
        q->~Ref_ed8610();
    } while (--i >= 0);
    q = m10.m + 3;
    i = 2;
    do {
        --q;
        q->~Ref_ed8610();
    } while (--i >= 0);
    m0c.~Ref_ed8610();
    m08.~Ref_ed8610();
    m04.~Ref_ed8610();
}

// 0x00ed8690 (byte-exact lifted version: match/slices/s00ed8690/s00ed8690.cpp)
void FUN_00ed8690(void)
{
    void* nm = FUN_00b3d300();
    int* v = (int*)FUN_00b1f9b0(nm);
    int* end = (int*)((char*)v - 0xc);
    int* it = (*v == 0) ? 0 : (int*)((char*)*v - 0xc);
    while (it != end) {
        int esi = 0;
        if (it != 0)
            esi = ((int(__thiscall*)(void*, int))(*(void***)it)[3])(it, 0x1186577);
        if (FUN_006c0200(it) != 0) {
            ((S_c8ad30*)(void*)esi)->f(0xd79308d, 0);
            ((S_c8ad30*)(void*)esi)->f(0x25e2b68, 0);
            ((S_c8ad30*)(void*)esi)->f(0xe1b86fea, 0);
            ((S_c8ad30*)(void*)esi)->f(0xfeacc46f, 0);
            ((S_c8ad30*)(void*)esi)->f(0xad89ad7d, 0);
            for (unsigned i = 0; i < 3; i++)
                ((S_c8ad30*)(void*)esi)->f((int)(0xcaf390f3u + i), 0);
        }
        int* nxt = (int*)it[3];
        it = (nxt == 0) ? 0 : (int*)((char*)nxt - 0xc);
    }
}

// @ 0x00ed8780
void Obj8780::f(unsigned char b)
{
    char* s = (char*)this;
    if (b != 0) {
        grab(0x654889e6, (int*)(s + 4));
        grab(0x95354ff3, (int*)(s + 8));
        grab(0xcbe66649, (int*)(s + 0xc));
        for (int i = 0; i < 3; i++) {
            grab(0xe3a79142, (int*)(s + 0x10 + i * 4));
            grab(0xe3a79142, (int*)(s + 0x1c + i * 4));
        }
    } else {
        clear2((int*)(s + 4));
        clear2((int*)(s + 8));
        clear2((int*)(s + 0xc));
        int* pa = (int*)(s + 0x10);
        for (int i = 0; i < 3; i++, pa++) {
            // The original clears the paired +0xc field only inside this branch, and its
            // first call is not null-checked (it assumes a live pair).
            if (*(int**)pa != 0) {
                int* a = *(int**)pa;
                ((FVf_i)(*(void***)a)[0xc / 4])(a, 0);
                int* q = *(int**)pa;
                if (q != 0) {
                    *(int**)pa = 0;
                    ((FVf_v)(*(void***)q)[4 / 4])(q);
                }
                int* pb = (int*)((char*)pa + 0xc);
                int* c = *(int**)pb;
                ((FVf_i)(*(void***)c)[0xc / 4])(c, 0);
                int* d = *(int**)pb;
                if (d != 0) {
                    *(int**)pb = 0;
                    ((FVf_v)(*(void***)d)[4 / 4])(d);
                }
            }
        }
    }
}

// @ 0x00ed8950
void __cdecl FUN_00ed8950(int id, int effect)
{
    NounVec8a30 vec;
    vec.begin = 0;
    vec.end = 0;
    vec.cap = 0;
    g_game8a30->holder->GetAllNouns(id, &vec);
    int** end = (int**)vec.end;
    for (int** it = (int**)vec.begin; it != end; ++it) {
        int* noun = *it;
        int* fx = noun ? (int*)((int(__thiscall*)(void*, int))(*(void***)noun)[3])(noun, 0x1186577) : 0;
        ((S_c8b210*)(void*)fx)->f(effect);
        ((S_c88a00*)(void*)fx)->f(effect, 3.402823466e+38f);
        ((S_c8a200*)(void*)fx)->f(effect, 1.0f);
    }
    end = (int**)vec.end;
    for (int** it = (int**)vec.begin; it < end; ++it) {
        int* noun = *it;
        if (noun)
            ((FV_v_s00ed_8490)(*(void***)noun)[1])(noun);
    }
    int* base = vec.begin;
    if (base != 0 && base[-1] != 0)
        operator_delete(base);
}

// @ 0x00ed9040
void* __cdecl FUN_00ed9040(int id, float* pos)
{
    float best = 3.402823466e+38f;
    int* found = 0;
    if (id == -1)
        return 0;
    if ((g_nounVecGuard & 1) == 0) {
        g_nounVecGuard |= 1;
        g_nounVec.begin = 0;
        g_nounVec.end = 0;
        g_nounVec.cap = 0;
        atexit((void*)0x013c8830);
    }
    g_game8a30->holder->GetAllNouns(id, &g_nounVec);
    int** end = (int**)g_nounVec.end;
    for (int** it = (int**)g_nounVec.begin; it != end; ++it) {
        int* noun = *it;
        int* comp = noun ? (int*)((int(__thiscall*)(void*, int))(*(void***)noun)[3])(noun, 0x1186577) : 0;
        float* p = (float*)((FVf_p)(*(void***)comp)[0x2c / 4])(comp);
        float dx = p[0] - pos[0];
        float dy = p[1] - pos[1];
        float dz = p[2] - pos[2];
        float d = dx * dx + dy * dy + dz * dz;
        if (d < best) {
            best = d;
            found = comp;
        }
    }
    return found;
}

// @ 0x00ed9150
void __cdecl FUN_00ed9150(int* out, float* pos, void* objPos, float f)
{
    const float* pA = pos;
    const float* pB = (const float*)objPos;
    float dx = pB[0] - pA[0];
    float dy = pB[1] - pA[1];
    float dz = pB[2] - pA[2];
    float dist = sqrtf(dx * dx + dy * dy + dz * dz);

    int count = 3;
    float scale = f;
    if (f <= 0.0f) {
        scale = dist * (1.0f / 3.0f);
    } else if (f * 3.0f > dist) {
        scale = dist * (1.0f / 3.0f);
    } else if (dist > f * 128.0f) {
        scale = dist * (1.0f / 128.0f);
        count = 128;
    } else {
        count = (int)(dist / f) + 1;
    }

    void* cursor = *(void**)out;
    int oldCount = 0;
    float* oldPts = (float*)((void* (__thiscall*)(void*, int, int*))(*(void***)cursor)[0x50 / 4])(cursor, 13, &oldCount);
    if (oldCount == count &&
        oldPts[0] == pA[0] && oldPts[1] == pA[1] && oldPts[2] == pA[2] &&
        oldPts[(oldCount - 1) * 3 + 0] == pB[0] &&
        oldPts[(oldCount - 1) * 3 + 1] == pB[1] &&
        oldPts[(oldCount - 1) * 3 + 2] == pB[2])
        return;

    float len = sqrtf(dx * dx + dy * dy + dz * dz + 1e-8f);
    float inv = 1.0f / len;
    float sx = dx * inv * scale;
    float sy = dy * inv * scale;
    float sz = dz * inv * scale;

    float pts[130 * 3];
    int n = 0;
    for (int i = 0; i < count; i++) {
        float t = (float)i;
        pts[n * 3 + 0] = pA[0] + sx * t;
        pts[n * 3 + 1] = pA[1] + sy * t;
        pts[n * 3 + 2] = pA[2] + sz * t;
        n++;
    }
    int last = n - 1;
    if (!(pts[last * 3 + 0] == pB[0] && pts[last * 3 + 1] == pB[1] && pts[last * 3 + 2] == pB[2])) {
        pts[n * 3 + 0] = pB[0];
        pts[n * 3 + 1] = pB[1];
        pts[n * 3 + 2] = pB[2];
        n++;
    }

    if (n != oldCount) {
        void* cur = *(void**)out;
        char b = (char)((FV_r0)(*(void***)cur)[0x10 / 4])(cur);
        if (b)
            ((FV_i_s00ed_9150)(*(void***)cur)[0xc / 4])(cur, 1);
        void* old = *(void**)out;
        void* fx = FUN_0067ddd0();
        if (old != 0) {
            *(void**)out = 0;
            ((FV_v_s00ed_9150)(*(void***)old)[4 / 4])(old);
        }
        unsigned __int64 h = ((unsigned __int64 (__thiscall*)(void*, void*))(*(void***)old)[0x60 / 4])(old, out);
        ((void (__thiscall*)(void*, unsigned __int64))(*(void***)fx)[0x2c / 4])(fx, h);
        if (b)
            ((FV_i_s00ed_9150)(*(void***)(*(void**)out))[8 / 4])(*(void**)out, 1);
    }

    void* cur2 = *(void**)out;
    ((void (__thiscall*)(void*, int, void*, int))(*(void***)cur2)[0x40 / 4])(cur2, 13, pts, n);
}

// @ 0x00ed9560
void FUN_00ed9560(int* out, void* p2, int p3)
{
    int* obj = (int*)FUN_00ed9040(p3, (float*)p2);
    if (obj != 0)
        FUN_00ed9150(out, (float*)p2, ((FV_p_s00ed_9150)(*(void***)obj)[0x2c / 4])(obj), g_1470f1c);
    void* recv = *(void**)out;
    if ((char)((FV_r0)(*(void***)recv)[0x10 / 4])(recv)) {
        if (obj == 0)
            ((FV_i_s00ed_9150)(*(void***)*(void**)out)[0xc / 4])(*(void**)out, 0);
    } else {
        if (obj != 0)
            ((FV_i_s00ed_9150)(*(void***)*(void**)out)[8 / 4])(*(void**)out, 0);
    }
}

// @ 0x00ed95d0
void __cdecl FUN_00ed95d0(int* out1, int* out2, float* pos, Step95d0* step)
{
    void* r1 = 0;
    void* r2 = 0;
    if (step == 0)
        goto tail;

    if (step->mType == 6 || step->mType == 10) {
        void* mgr = *(void**)((char*)g_16c7aa4_s00ed_9150 + 0x74);
        void* tA = FUN_00f3e8a0(mgr, 0, (int)step->mA);
        char bl = (tA == 0) ? (char)1 : (char)(FUN_00f25530(tA, 0) != 0);
        void* tB = FUN_00f3e8a0(mgr, 0, (int)step->mB);
        char al = (tB == 0) ? (char)1 : (char)(FUN_00f25530(tB, 0) != 0);
        if (bl == 0) {
            r1 = FUN_00ed9040((int)step->mB, pos);
            if (r1 != 0) {
                float* v = (float*)((FV_p_s00ed_9150)(*(void***)r1)[0x2c / 4])(r1);
                r2 = FUN_00ed9040((int)step->mA, v);
            } else {
                r1 = FUN_00ed9040((int)step->mA, pos);
            }
        } else if (al == 0) {
            r1 = FUN_00ed9040((int)step->mA, pos);
            if (r1 != 0) {
                float* v = (float*)((FV_p_s00ed_9150)(*(void***)r1)[0x2c / 4])(r1);
                r2 = FUN_00ed9040((int)step->mB, v);
            } else {
                r1 = FUN_00ed9040((int)step->mB, pos);
            }
        } else {
            r1 = FUN_00ed9040((int)step->mA, pos);
            void* rB = FUN_00ed9040((int)step->mB, pos);
            if (r1 == 0) {
                r2 = 0;
                r1 = rB;
            } else if (rB != 0) {
                r2 = FUN_00ed9040((int)step->mB, (float*)((FV_p_s00ed_9150)(*(void***)r1)[0x2c / 4])(r1));
                void* alt = FUN_00ed9040((int)step->mA, (float*)((FV_p_s00ed_9150)(*(void***)rB)[0x2c / 4])(rB));
                float* pa = (float*)((FV_p_s00ed_9150)(*(void***)r1)[0x2c / 4])(r1);
                float* pb = (float*)((FV_p_s00ed_9150)(*(void***)r1)[0x2c / 4])(r1);
                float* pc = (float*)((FV_p_s00ed_9150)(*(void***)r2)[0x2c / 4])(r2);
                float* pd = (float*)((FV_p_s00ed_9150)(*(void***)rB)[0x2c / 4])(rB);
                float* pe = (float*)((FV_p_s00ed_9150)(*(void***)rB)[0x2c / 4])(rB);
                float* pf = (float*)((FV_p_s00ed_9150)(*(void***)alt)[0x2c / 4])(alt);
                float d1 = (pa[0] - pos[0]) * (pa[0] - pos[0]) +
                           (pa[1] - pos[1]) * (pa[1] - pos[1]) +
                           (pa[2] - pos[2]) * (pa[2] - pos[2]);
                float d2 = (pc[0] - pb[0]) * (pc[0] - pb[0]) +
                           (pc[1] - pb[1]) * (pc[1] - pb[1]) +
                           (pc[2] - pb[2]) * (pc[2] - pb[2]);
                float d3 = (pd[0] - pos[0]) * (pd[0] - pos[0]) +
                           (pd[1] - pos[1]) * (pd[1] - pos[1]) +
                           (pd[2] - pos[2]) * (pd[2] - pos[2]);
                float d4 = (pf[0] - pe[0]) * (pf[0] - pe[0]) +
                           (pf[1] - pe[1]) * (pf[1] - pe[1]) +
                           (pf[2] - pe[2]) * (pf[2] - pe[2]);
                if (sqrtf(d1) + sqrtf(d2) > sqrtf(d3) + sqrtf(d4)) {
                    r2 = alt;
                    r1 = rB;
                }
            }
        }
    } else if (step->mType == 9) {
        r1 = FUN_00ed9040((int)step->mA, pos);
        if (r1 != 0) {
            float* v = (float*)((FV_p_s00ed_9150)(*(void***)r1)[0x2c / 4])(r1);
            r2 = FUN_00ed9040((int)step->mB, v);
        } else {
            r1 = FUN_00ed9040((int)step->mB, pos);
        }
    } else {
        r1 = FUN_00ed9040((int)step->mA, pos);
    }

tail:
    if (r1 != 0) {
        FUN_00ed9150(out1, pos, (void*)((FV_p_s00ed_9150)(*(void***)r1)[0x2c / 4])(r1), g_1470f1c);
        if (r2 != 0) {
            float* p1 = (float*)((FV_p_s00ed_9150)(*(void***)r1)[0x2c / 4])(r1);
            float* p2 = (float*)((FV_p_s00ed_9150)(*(void***)r2)[0x2c / 4])(r2);
            FUN_00ed9150(out2, p1, p2, g_1470f1c);
        }
    }

    void* c1 = *(void**)out1;
    char v1 = (char)((FV_r0)(*(void***)c1)[0x10 / 4])(c1);
    if (v1 != 0) {
        if (r1 == 0)
            ((FV_i_s00ed_9150)(*(void***)c1)[0xc / 4])(c1, 0);
    } else {
        if (r1 != 0)
            ((FV_i_s00ed_9150)(*(void***)c1)[8 / 4])(c1, 0);
    }

    void* c2 = *(void**)out2;
    char v2 = (char)((FV_r0)(*(void***)c2)[0x10 / 4])(c2);
    if (v2 != 0) {
        if (r2 == 0)
            ((FV_i_s00ed_9150)(*(void***)c2)[0xc / 4])(c2, 0);
    } else {
        if (r2 != 0)
            ((FV_i_s00ed_9150)(*(void***)c2)[8 / 4])(c2, 0);
    }
}

// @ 0x00ed9cd0
bool __stdcall FUN_00ed9cd0(int unused)
{
    (void)unused;
    void* p = FUN_00b3d4d0();
    int t = *(int*)((char*)p + 0x2c);
    if (t == 1 || t == 2)
        return false;

    void* q = FUN_00b3d230();
    if (FUN_00b5ca60(q, 0) == 1)
        return false;

    void* s = FUN_00b3d240();
    void* obj = ((FV_p_s00ed_9150)(*(void***)s)[0x30 / 4])(s);
    void* edi = 0;
    if (obj != 0)
        edi = (void*)((FV_ip)(*(void***)obj)[0xc / 4])(obj, 0x17f243b);

    void* ebp = FUN_00b18e00(edi);
    void* gm = SP_GameInputManager();
    int ebx = (int)((FV_p_s00ed_9150)(*(void***)gm)[0x34 / 4])(gm);
    if (FUN_00efcd90() != 0)
        return false;

    unsigned esi = 0x1002;
    if (ebx <= 5) {
        switch (ebx) {
        case 0:
            if (ebp != 0 && ((FV_r0)(*(void***)ebp)[0x24 / 4])(ebp) != 0) {
                int n = (int)((FV_r0)(*(void***)g_15ad298)[0x1c / 4])(g_15ad298) != 0;
                esi = 0x747d67b + (unsigned)n;
            }
            break;
        case 1: {
            unsigned k = (unsigned)FUN_00efc510();
            if (k <= 3) {
                if (k == 0 || k == 1)
                    esi = 0x747d67c;
                else if (k == 2)
                    esi = 0x7391920b;
                else
                    esi = 0xf728e452;
            }
            break;
        }
        case 2:
            esi = 0xe84563d4;
            break;
        case 3:
            if (((FV_r0)(*(void***)g_15ad298)[0x1c / 4])(g_15ad298) != 0) {
                esi = 0x747d67c;
            } else if (ebp != 0 && ((FV_r0)(*(void***)ebp)[0x24 / 4])(ebp) != 0) {
                int n = (int)((FV_r0)(*(void***)g_15ad298)[0x1c / 4])(g_15ad298) != 0;
                esi = 0x747d67b + (unsigned)n;
            }
            break;
        case 4:
            if (edi != 0 && FUN_00dd18b0(edi) != 0)
                esi = 0xf212a38b;
            else
                esi = 0x5ecbdffd;
            break;
        case 5:
            if (edi != 0) {
                esi = 0xf6879190;
                if (FUN_00e09ad0(edi) == 0)
                    esi = 0x5ecbdffd;
            } else {
                esi = 0x5ecbdffd;
            }
            break;
        }
    }

    void* cur = FUN_0067cab0();
    int old = FUN_008013c0(cur, 0);
    if ((int)esi != old)
        FUN_00801bb0(cur, 0, (int)esi);
    return true;
}

// @ 0x00ed9e60
bool __stdcall FUN_00ed9e60(char a)
{
    if (g_16065f8 == 0)
        return false;
    if (((FV_r0)(*(void***)g_15ad298)[0x38 / 4])(g_15ad298) != 0)
        return false;

    if (a != 0) {
        if (FUN_008d2fb0(1000) != 0)
            return false;
        if (FUN_008d2fb0(1002) != 0)
            return false;
        if (FUN_008d2fb0(1001) != 0)
            return false;
    }

    void* app = SP_App();
    void* viewer = ((FV_p_s00ed_9150)(*(void***)app)[0x50 / 4])(app);
    void* obj = ((FV_p_s00ed_9150)(*(void***)viewer)[0x38 / 4])(viewer);
    if (obj == 0)
        return true;
    void* z = (void*)((FV_ip)(*(void***)obj)[0xc / 4])(obj, 0x11966ed);
    if (z == 0)
        return true;
    return FUN_00b0f9a0(z, 0) == 0;
}

// @ 0x00ed9f10
extern "C" int FUN_00ed9f10(void* self, void* a, void* b)
{
    (void)self; (void)a;
    if (!EA_Audio_GetSystemAT())
        return 0;
    uint32_t* pmsg = (uint32_t*)b;
    if (!pmsg)
        return 0;
    void* obj = (void*)*pmsg;
    if (!obj)
        return 0;
    void** vt = *(void***)obj;
    void* r = ((FnPI)vt[0xc / 4])(obj, 0x31e56741u);
    if (!r)
        return 0;
    if (*(uint32_t*)((char*)r + 0x50) != 0xb1b104u)
        return 0;
    char* sub = (char*)r + 0x4c;
    uint32_t* rc = (uint32_t*)(sub + 4);
    if (*rc != 0)
        *rc -= 1;
    *pmsg = 0;
    return 1;
}

// @ 0x00eda130
void InputStrategy::FUN_00eda130()
{
    char* self = (char*)this;
    char* si = (self != 0) ? (self + 0x3c) : (char*)0;
    void** in = (void**)FUN_00b3d230();
    ((FnI)(*(void***)in)[0x38 / 4])(in, 1);
    void** gim = (void**)GameInputManager();
    ((FnPIII)(*(void***)gim)[0x10 / 4])(gim, (int)"TriggerConfigScenarioEdit", 0, 1);
    void* fr = ((FnPI)(*(void***)gim)[0x14 / 4])(gim, 0x13f9b6c);   // L"fr-fr"
    void* found = Hashtable_DoFindNode(fr, (const void*)0x13f9b6c);
    void* name = found ? (void*)0x148a394 : (void*)0x1477770;
    ((FnPIII)(*(void***)gim)[0x10 / 4])(gim, (int)name, 0, 0);
    ((FnPI)(*(void***)gim)[0x3c / 4])(gim, (int)"UIMachineScenarioEdit");
    void* cm = CursorManager();
    CursorTable_AddCursor(cm, (void*)0x747d67b, (void*)0x13f9b6c, (void*)1, 0, 0);
    CursorTable_AddCursor(cm, (void*)0x747d67c, (void*)0x13f9b48, (void*)1, 0, 0);
    CursorTable_AddCursor(cm, (void*)0x7e4330b, (void*)0x148a358, (void*)1, 0, 0);
    CursorTable_AddCursor(cm, (void*)0x7e4330c, (void*)0x148a334, (void*)1, 0, 0);
    CursorTable_AddCursor(cm, (void*)0xe84563d4u, (void*)0x148a30c, (void*)1, 0, 0);
    CursorTable_AddCursor(cm, (void*)0xf728e452u, (void*)0x148a2e4, (void*)1, 0, 0);
    CursorTable_AddCursor(cm, (void*)0x7391920bu, (void*)0x148a2bc, (void*)1, 0, 0);

    char* handler = (self != 0) ? (self + 0x44) : (char*)0;
    void* srv = MessageServer_s00ed_9f10();
    *(void**)(self + 0x54) = srv;
    *(void**)(self + 0x58) = handler;
    *(uint32_t*)(self + 0x5c) = (uint32_t)g_msgTable;
    *(uint32_t*)(self + 0x60) = 0x1f;
    *(uint32_t*)(self + 0x64) = 0;
    if (srv && handler) {
        for (unsigned off = 0; off < 0x7c; off += 4)
            ((FnII)(*(void***)srv)[0x24 / 4])(srv, (int)handler, (int)g_msgTable[off / 4]);
    }

    void** b = (void**)FUN_00b3d240();
    uint32_t local = 0;
    ((FnII)(*(void***)b)[0x2c / 4])(b, (int)&local, 1);
    if (si && *(uint32_t*)(si - 4) != 0)
        operator_delete(si);
}

// @ 0x00eda2f0
int InputStrategy::FUN_00eda2f0(uint32_t msg, void* data)
{
    char* self = (char*)this;
    char* g = g_pStrategy;
    int allow = 1;
    if ((g_bEditorMode == 0) || (((FnP)(*(void***)g)[0x38 / 4])(g) != 0)) {
        allow = 0;
    } else {
        if ((IsModifierKeyDown(1000) != 0) || (IsModifierKeyDown(0x3ea) != 0) ||
            (IsModifierKeyDown(0x3e9) != 0)) {
            allow = 0;
        } else {
            void** app = (void**)SP_App();
            void* cam = ((FnP)(*(void***)app)[0x50 / 4])(app);
            void* sub = ((FnP)(*(void***)cam)[0x38 / 4])(cam);
            if (sub) {
                void* q = ((FnPI)(*(void***)sub)[0xc / 4])(sub, 0x11966ed);
                if (q)
                    allow = (cTerrainCameraController_KeysHeld(q) == 0);
            }
        }
    }

    switch (msg) {
    case 0x101:
        if (allow && *(void**)(g_pMagic + 0x14))
            FUN_00ed76e0(*(void**)(g_pMagic + 0x14), 2);
        return 1;
    case 0x106:
        if (allow && *(void**)(g_pMagic + 0x14))
            FUN_00ed4b60(*(void**)(g_pMagic + 0x14));
        return 1;
    case 0x238de9c:
        *(uint8_t*)(self + 0x51) = 1;
        return 1;
    case 0x3a127dc:
        if ((*(uint32_t*)((char*)data + 8) == 0x3a129ee) &&
            (*(uint32_t*)((char*)data + 0x10) == *(uint32_t*)(self + 0x6c))) {
            *(uint32_t*)(self + 0x6c) = 0;
            SetGlobalProperty(0x8dff6314u, 0.0f);
        }
        return 1;
    case 0x44eaa93:
    case 0x452e0ca:
        GetRecorderState();
        cSPUISpace_KillSetiEffects(0xe76c9b4fu, 0);
        FUN_00ed9b80(self);
        return 1;
    case 0x522f9cd:
        FUN_00ed9f10(self, 0, data);
        return 1;
    case 0x522f9ce:
        FUN_00ed9b40(self);
        return 1;
    case 0x620222b:
    case 0x620271c:
    case 0x62663dd:
        FUN_00ed9bd0(self);
        return 1;
    case 0x24ce123:
        if (g == g_pStrategySelf)
            ScenarioTutorials_ReleaseInput();
        return 1;
    case 0x24ce124:
        if ((FUN_00809970() == 0) && (g == g_pStrategySelf))
            FUN_00f01f40(0x24ce124, data);
        return 1;
    case 0x411e1e8d:
        if ((FUN_00809970() == 0) && (g == g_pStrategySelf))
            ScenarioTutorials_CaptureInput();
        return 1;
    case 0x7561116:
        return 1;
    case 0xf3327645:
        FUN_00ed9b80(self);
        return 1;
    case 0xc9d86390:
        if (allow) {
            FUN_00ed4840(g_modeObj);
            GetRecorderState();
            cSPUISpace_KillSetiEffects(0x5416f867u, 0);
            FUN_00ed9c20(g_modeObj);
            cSPPaletteItem_GetPriority(*(void**)(g_pMagic + 0x14));
            FUN_00ee9260(0);
        }
        return 1;
    case 0xc9d86391:
        if (allow) {
            FUN_00ed48b0(g_modeObj);
            GetRecorderState();
            cSPUISpace_KillSetiEffects(0x370d9c35u, 0);
            FUN_00ed9c60(g_modeObj);
            cSPPaletteItem_GetPriority(*(void**)(g_pMagic + 0x14));
            FUN_00ee9260(0);
        }
        return 1;
    case 0xc9d86392:
    case 0xc9d86393:
    case 0xc9d86394:
    case 0xc9d86395:
    case 0xc9d86396:
        if (allow)
            ((FnV)(*(void***)g)[msg - 0xc9d86392 + 1])(g);
        return 1;
    default:
        return 0;
    }
}

// @ 0x00eda6f0
int InputStrategy::FUN_00eda6f0(uint32_t msg, void* data)
{
    InputStrategy* self = (InputStrategy*)((char*)this - 0x44);
    if (self->FUN_00eda2f0(msg, data))
        return 1;

    void** d = (void**)data;
    void* q1 = ((FnP)(*(void***)d)[0x10 / 4])(d);
    void* e = ((FnPI)(*(void***)q1)[0x1c / 4])(q1, 0);
    void* o1;
    if ((*(uint8_t*)((char*)e + 0x10) & 0x30) != 0)
        o1 = *(void**)e;
    else if (*(uint16_t*)((char*)e + 0x12) != 0)
        o1 = e;
    else
        o1 = 0;
    uint32_t v17f = 0;
    if (o1)
        v17f = (uint32_t)((FnPI)(*(void***)o1)[0xc / 4])(o1, 0x17f243b);

    void* e1 = ((FnPI)(*(void***)q1)[0x1c / 4])(q1, 1);
    int ebp = *(int*)e1;
    void* e4 = ((FnPI)(*(void***)q1)[0x1c / 4])(q1, 4);
    void* o4;
    if ((*(uint8_t*)((char*)e4 + 0x10) & 0x30) != 0)
        o4 = *(void**)e4;
    else if (*(uint16_t*)((char*)e4 + 0x12) != 0)
        o4 = e4;
    else
        o4 = 0;
    float f10 = *(float*)((char*)o4 + 8);
    void* q2 = ((FnP)(*(void***)d)[0x14 / 4])(d);
    void* esi = ((FnPI)(*(void***)q2)[0x1c / 4])(q2, 0);

    switch (msg) {
    case 0x25db76a: ScenarioTutorials_ToggleTarget(f10); return 1;
    case 0x25db76b:
        if (ebp == 6) { FUN_00f01e60((void*)v17f); return 1; }
        ScenarioTutorials_TickStopwatch(ebp == 4);
        return 1;
    case 0x25db76c: ScenarioTutorials_SetTargetVisible(ebp == 4); return 1;
    case 0x62663dc: FUN_00e09bf0((void*)v17f); return 1;
    case 0x7438ac6: ((FnII)(*(void***)self)[0x14 / 4])(self, ebp, v17f); return 1;
    case 0x7438ac7: {
        int r = ((FnII)(*(void***)self)[0x2c / 4])(self, ebp, v17f);
        if (r == 0) { *(uint32_t*)esi = 2; return 1; }
        if (r == 2) { *(uint32_t*)esi = 1; return 1; }
        return 1;
    }
    case 0x7478fb7:
        if (ebp == 1) {
            if (!((FnI)(*(void***)self)[0x24 / 4])(self, (int)v17f))
                *(uint32_t*)esi = 2;
            return 1;
        }
        if (ebp == 0) {
            ((FnV)(*(void***)self)[0x28 / 4])(self);
            return 1;
        }
        return 1;
    case 0x7da2d5a: {
        if (v17f == 0) return 0;
        uint32_t* r = (uint32_t*)GetRefCounted18((void*)v17f);
        if (!r) return 1;
        if (*r == 0xfffffffeu) return 1;
        uint32_t id = *r;
        void* srv = MessageServer_s00ed_9f10();
        ((FnII)(*(void***)srv)[0x14 / 4])(srv, (int)&id, 0x7465518);
        return 1;
    }
    case 0xb332763d:
        cUIBanningContent_ShowConfirmationDialog((int)v17f);
        return 1;
    default:
        return 0;
    }
}

// @ 0x00edaa80
InputStrategy* InputStrategy::FUN_00edaa80()
{
    char* self = (char*)this;
    *(void**)(self + 0x00) = (void*)0x14771e0;
    *(uint32_t*)(self + 0x0c) = 0;
    *(uint32_t*)(self + 0x10) = 0;
    *(uint32_t*)(self + 0x14) = 0;
    char* e8 = self + 8;
    *(void**)(e8) = e8;
    *(void**)(self + 0x0c) = e8;
    *(uint32_t*)(self + 0x10) = 0;
    *(uint8_t*)(self + 0x14) = 0;
    *(uint32_t*)(self + 0x18) = 0;
    *(uint32_t*)(self + 0x28) = 0;
    char* e24 = self + 0x24;
    *(void**)(e24 + 8) = 0;
    *(void**)(e24 + 0x0c) = 0;
    char* edi = self + 0x3c;
    *(void**)(e24) = e24;
    *(void**)(self + 0x28) = e24;
    *(uint32_t*)(self + 0x2c) = 0;
    *(uint8_t*)(self + 0x30) = 0;
    *(uint32_t*)(self + 0x34) = 0;
    FUN_008014a0(edi);
    *(void**)(self + 0x44) = (void*)0x13eb384;
    *(void**)(self + 0x4c) = 0;
    *(void**)(self + 0x48) = (void*)0x13ec458;
    *(uint8_t*)(self + 0x50) = 0;
    *(uint8_t*)(self + 0x51) = 0;
    *(void**)(self + 0x00) = (void*)0x148a40c;
    *(void**)(edi + 0) = (void*)0x148a3f4;
    *(void**)(self + 0x44) = (void*)0x148a3e4;
    *(void**)(self + 0x48) = (void*)0x148a3d4;
    *(uint32_t*)(self + 0x54) = 0;
    *(uint32_t*)(self + 0x58) = 0;
    *(uint32_t*)(self + 0x5c) = 0;
    *(uint32_t*)(self + 0x60) = 0;
    *(uint32_t*)(self + 0x64) = 0;
    *(uint32_t*)(self + 0x6c) = 0;
    return this;
}

// @ 0x00edabf0
extern "C" unsigned char FUN_00edabf0(uint32_t idx)
{
    char* t = *(char**)(*(char**)(g_pMagic + 0x74) + 0x10);
    struct { uint32_t a; uint32_t b; uint32_t c; } key;
    key.a = *(uint32_t*)(t + 8);
    key.b = *(uint32_t*)(t + 0xc);
    key.c = *(uint32_t*)(t + 0x10);
    uint32_t c = key.c ^ (((idx + 1) ^ key.c) & 0xff);
    key.b = 0x2f7d0004;
    key.c = c;
    ResourceMan* m = ResourceMan_GetManager();
    return (unsigned char)m->Load(&key, 0, 0, 0, 0, 0);
}

// @ 0x00edac50
extern "C" int FUN_00edac50(uint32_t idx)
{
    return FUN_00edabf0(idx) ? -3 : -2;
}

// @ 0x00edac70
extern "C" int FUN_00edac70(uint32_t idx)
{
    Recorder* rg = *(Recorder**)(g_pMagic + 0xd8);
    int n = rg->FUN_00f04060();
    if (n > 0)
        return n - 1;
    return (idx != 0) ? -1 : -2;
}

// @ 0x00edaca0
void InputStrategy::FUN_00edaca0()
{
    char* self = (char*)this;
    void* mgr = *(void**)(g_pMagic + 0x74);
    if (!mgr)
        return;
    uint32_t code = (uint32_t)((FnP)(*(void***)mgr)[8 / 4])(mgr);
    int n = (int)(*(uint32_t*)(self + 0x40) - *(uint32_t*)(self + 0x3c)) >> 2;
    if ((unsigned)n <= 0)
        return;
    int i = 0, off = 0;
    int limit = (int)(*(uint32_t*)(self + 0x40) - *(uint32_t*)(self + 0x3c)) >> 2;
    for (;;) {
        if ((unsigned)off >= 0x78)
            return;
        if (*(uint32_t*)((char*)g_menuTable + off) == code) {
            uint32_t item = *(uint32_t*)(*(uint32_t*)(self + 0x3c) + i * 4);
            Menu2_OnMenuItemSelected(*(void**)(self + 0x38), 0, (void*)item);
            return;
        }
        ++i;
        off += 0xc;
        if ((unsigned)i >= (unsigned)limit)
            return;
    }
}

// @ 0x00edad00
void InputStrategy::FUN_00edad00()
{
    char* self = (char*)this;
    for (int i = 0; i < 4; ++i) {
        *(uint32_t*)(self + 0x8c + i * 0xc) = 0;
        char* e = self + 0x8c + i * 0xc;
        *(uint32_t*)(e + 4) = 0;
        *(uint32_t*)(e + 8) = 0;

        char* t = *(char**)(*(char**)(g_pMagic + 0x74) + 0x10);
        uint8_t ok = 0;
        if (*(int*)(t + 0x68 + i * 4) == 1) {
            struct { uint32_t a; uint32_t b; uint32_t c; } key;
            key.a = *(uint32_t*)(t + 8);
            key.c = (((i + 1) ^ *(uint32_t*)(t + 0x10)) & 0xff) ^ *(uint32_t*)(t + 0x10);
            key.b = 0x2f7d0004;
            ResourceMan* m = ResourceMan_GetManager();
            ok = (uint8_t)m->Load(&key, 0, 0, 0, 0, 0);
        }
        *(uint32_t*)(self + 0x7c + i * 4) = (ok == 0) ? 0xffffffffu : 0xfffffffdu;
        *(uint32_t*)(self + 0xbc + i * 4) = (ok == 0) ? 3u : 1u;
        if (i == 0 && ok == 0) {
            *(uint32_t*)(self + 0x7c) = 0xfffffffeu;
            *(uint32_t*)(self + 0xbc) = 0;
        }
    }
}

// @ 0x00edadd0
void InputStrategy::FUN_00edadd0()
{
    char* self = (char*)this;
    Recorder* rg = *(Recorder**)(g_pMagic + 0xd8);
    int n = rg->FUN_00f04060();
    if (n <= 0)
        return;
    int* p = (int*)(*(int*)(*(int*)(g_pMagic + 0x74) + 0x10) + 0x68);
    int i = 0;
    do {
        if (*p != 0 && *p != 3)
            return;
        ++i;
        ++p;
    } while (i < 4);

    i = 0;
    char* dst = self + 0x8c;
    uint32_t* idx = (uint32_t*)(self + 0x7c);
    do {
        if (i < n) {
            *idx = (uint32_t)i;
            FUN_00f03ff0(i, dst, 0);
        }
        ++i;
        ++idx;
        dst += 0xc;
    } while (i < 4);
}

// @ 0x00edae50
int InputStrategy::FUN_00edae50(uint32_t msg, void* data)
{
    char* self = (char*)this;
    if (msg == 0x7e1e46du)
        ((InputStrategy*)(self - 4))->FUN_00edad00();
    return ((NamingBase*)this)->HandleMessage(msg, data);
}

// @ 0x00edaf10
ActsBarUI* __fastcall FUN_00edaf10(ActsBarUI* self)
{
    cSPEditorNaming_ctor();
    *(void**)((char*)self + 0x00) = (void*)0x148a440;
    *(void**)((char*)self + 0x04) = (void*)0x148a430;
    *(void**)((char*)self + 0x08) = (void*)0x148a420;
    *(uint32_t*)((char*)self + 0x38) = 0;
    void* p = (char*)self + 0x54;
    *(void**)((char*)self + 0x4c) = p;
    *(void**)((char*)self + 0x40) = p;
    *(void**)((char*)self + 0x3c) = p;
    *(void**)((char*)self + 0x44) = (char*)p + 0x28;
    for (int off = 0x8c; off < 0xbc; off += 4)
        *(uint32_t*)((char*)self + off) = 0;
    for (int off = 0xcc; off < 0xe0; off += 4)
        *(uint32_t*)((char*)self + off) = 0;
    return self;
}

// @ 0x00edb120
void ActsBarUI::FUN_00edb120(int idx)
{
    char* self = (char*)this;
    int b1 = FUN_00edabf0(idx), b2 = FUN_00edabf0(idx);
    (void)b2;
    char* g = g_pMagic;
    FUN_00f04060();
    bool shown = (idx != 0) || b1;
    char* layout = (char*)cSPUILayout_FindWindowByID(*(void**)(self + 0x18), 0x7c7a720, 1);
    void* w = (*(FnPII)(*(void**)(*(char**)layout + 0xf0)))(layout, 0x447b980, 1);
    if (w)
        (*(FnII)(*(void**)(*(char**)w + 0x7c)))(w, 2, shown);
    void* w2 = (*(FnPII)(*(void**)(*(char**)layout + 0xf0)))(layout, 0x447b968, 1);
    if (w2)
        (*(FnII)(*(void**)(*(char**)w2 + 0x7c)))(w2, 2, shown);
    void* icon = (*(FnPII)(*(void**)(*(char**)layout + 0xf0)))(layout, 0x771fb08, 1);
    int state = *(int*)(self + 0x7c + idx * 4);
    if (state == -3) {
        *(int*)(self + 0xbc + idx * 4) = 2;
        SPUIHelpers_SetWindowImage(icon, 0, -1);
    } else if (state == -1) {
        *(int*)(self + 0xbc + idx * 4) = 3;
        int* q = (int*)(self + 0x8c + idx * 0xc);
        q[0] = q[1] = q[2] = 0;
    } else if (state == -2) {
        *(int*)(self + 0xbc + idx * 4) = 0;
        int* q = (int*)(self + 0x8c + idx * 0xc);
        q[0] = q[1] = q[2] = 0;
        int pid = cGameData_GetPoliticalID(*(void**)(g + 0x74));
        if (pid) {
            char* sys = (char*)FUN_0067dd60();
            (*(FnII)(*(void**)(*(char**)sys + 0x2c)))(sys, pid, 0);
            uint32_t tex = SPUIHelpers_GetImageFromTexture(q[0], q[2], -1, -1);
            SPUIHelpers_SetDrawableImage(icon, tex, -1);
        }
    } else {
        *(int*)(self + 0xbc + idx * 4) = 1;
        int* q = (int*)(self + 0x8c + idx * 0xc);
        uint32_t tex = SPUIHelpers_GetImageFromTexture(q[0], q[1], -1, -1);
        SPUIHelpers_SetDrawableImage(icon, tex, -1);
    }
    (*(FnII)(*(void**)(*(char**)layout + 0xf0)))(layout, 0x7e08150, 1);
    SPUIHelpers_SetTooltipText(0, -1);
}

// @ 0x00edb4c0
void ActsBarUI::FUN_00edb4c0(int* level)
{
    char* self = (char*)this;
    int base = 0;
    if (*(void**)(g_pMagic + 0x74))
        base = (int)(*(char**)(g_pMagic + 0x74) + 4);
    cSPEditorNaming_Init();
    (void)base; (void)level;
    char* layout = *(char**)(self + 0x18);
    char* w = layout ? (char*)cSPUILayout_FindWindowByID(layout, 0x730f688, 1) : 0;
    char* menu = w ? (char*)(*(FnPI)(*(void**)(*(char**)w + 0xc)))(w, 0x4c058d5) : 0;
    if (menu) {
        (*(FnV)(*(void**)(*(char**)menu + 0x104)))(menu);
        char* old = *(char**)(self + 0x38);
        if (menu != old) {
            (*(FnV)(*(void**)(*(char**)menu)))(menu);
            *(char**)(self + 0x38) = menu;
            if (old)
                (*(FnV)(*(void**)(*(char**)old + 4)))(old);
        }
        uint32_t tmpl[3] = {0xa10d844a, 0x510a95b, 0x40464100};
        for (int i = 0; i < 10; ++i) {
            cString c;
            cString_ctor0(&c);
            char* text = 0;
            if (g_acts[i].b) {
                cString_Load(&c, g_acts[i].b, g_acts[i].c, 0);
                text = (char*)cString_GetText(&c, 0, -1);
            }
            int* item = (int*)cSPUIPopupMenuWin_AddMenuItem(menu, tmpl, 0, text, 1);
            if (item)
                (*(FnV)(*(void**)(*item)))(item);
            if (*(int*)(self + 0x40) < *(int*)(self + 0x44)) {
                int* slot = *(int**)(self + 0x40);
                *(int*)(self + 0x40) = (int)slot + 4;
                if (slot) {
                    *slot = (int)item;
                    if (item)
                        (*(FnV)(*(void**)(*item)))(item);
                }
            } else {
                int* pv = item;
                FUN_00edafd0(*(void**)(self + 0x40), (void**)&pv);
            }
            if (item)
                (*(FnV)(*(void**)(*item + 4)))(item);
            cString_dtor(&c);
        }
    }
    FUN_00edaca0();
    FUN_00edad00();
    char* h = (char*)EA_Messaging_MessageServer();
    *(char**)(self + 0xcc) = h;
    *(char**)(self + 0xd0) = self + 4;
    *(void**)(self + 0xd4) = (void*)0x148a460;
    *(int*)(self + 0xd8) = 1;
    *(int*)(self + 0xdc) = 0;
    if (h && (self + 4))
        (*(FnII)(*(void**)(*(char**)h + 0x24)))(h, 0x7e1e46d, (int)(self + 4));
}

// @ 0x00edb6c0
void ActsBarUI::FUN_00edb6c0()
{
    char* self = (char*)this;
    void* p = *(void**)(self + 0x38);
    if (p) {
        *(void**)(self + 0x38) = 0;
        (*(FnV)(*(void**)(*(char**)p + 4)))(p);
    }
    ((ERefVec*)(self + 0x3c))->erase(*(void**)(self + 0x3c), *(void**)(self + 0x40));
    int h = *(int*)(self + 0xcc);
    if (h) {
        *(int*)(self + 0xcc) = 0;
        EA_Messaging_RemoveHandler((void*)h, *(void**)(self + 0xd0), *(void**)(self + 0xd4),
                                   *(void**)(self + 0xd8), *(void**)(self + 0xdc));
    }
    ((cSPEditorNamingBase*)self)->Shutdown();
}

// @ 0x00edb730
void ActsBarUI::FUN_00edb730()
{
    for (int i = 0; i < 4; ++i)
        FUN_00edb120(i);
}

// @ 0x00edb750
bool ActsBarUI::FUN_00edb750(void* window, void* msg)
{
    char* self = (char*)this;
    char* m = (char*)msg;
    uint32_t id = *(uint32_t*)(m + 8);
    if (id == 0x4cab02d) {
        uint32_t n = *(uint32_t*)(m + 0x10);
        if (n < 10) {
            char* gd = *(char**)(g_pMagic + 0x74);
            (*(FnI)(*(void**)(*(char**)gd + 0xc)))(gd, (int)g_acts[n].a);
        }
        char* snd = (char*)EA_Audio_GetSystemAT();
        void* ar = 0;
        if (snd)
            ar = (*(FnP)(*(void**)(*(char**)snd + 0x20)))(snd);
        SP_cSPUISpace_KillSetiEffects(0xe76c9b4f, (int)ar);
        return true;
    }
    if (id == 0x685a2b9) {
        char* snd = (char*)EA_Audio_GetSystemAT();
        void* ar = 0;
        if (snd)
            ar = (*(FnP)(*(void**)(*(char**)snd + 0x20)))(snd);
        SP_cSPUISpace_KillSetiEffects(0xe76c9b4f, (int)ar);
    } else if (id == 0x287259f6) {
        char* obj = *(char**)(m + 4);
        int idx = (int)(*(FnP)(*(void**)(*(char**)obj + 0x1c)))(obj) - 0x7c7a720;
        int which = *(int*)(m + 0xc);
        if (which == 0x447b968) {
            int v = FUN_00edac70(idx);
            int cur = *(int*)(self + 0x7c + idx * 4);
            if (cur == v)
                *(int*)(self + 0x7c + idx * 4) = FUN_00edac50(idx);
            else {
                *(int*)(self + 0x7c + idx * 4) = cur + 1;
                if (idx == 0 && *(int*)(self + 0x7c) == -1)
                    *(int*)(self + 0x7c) = 0;
            }
        } else if (which == 0x447b980) {
            int v = FUN_00edac50(idx);
            int cur = *(int*)(self + 0x7c + idx * 4);
            if (cur == v)
                *(int*)(self + 0x7c + idx * 4) = FUN_00edac70(idx);
            else {
                *(int*)(self + 0x7c + idx * 4) = cur - 1;
                if (idx == 0 && *(int*)(self + 0x7c) == -1)
                    *(int*)(self + 0x7c) = -2;
            }
        } else if (which == 0x447c040) {
            int* cell = (int*)(self + 0x7c + idx * 4);
            cSPGuardMgr* g1 = (cSPGuardMgr*)*(void**)(g_pMagic + 0xd8);
            if (!g1->FUN_00f066c0(cell, self + 0x8c + idx * 0xc))
                *cell = (idx != 0) - 2;
            for (int i = 0; i < 4; ++i) {
                if (i != idx) {
                    int* other = (int*)(self + 0x7c + i * 4);
                    if (*cell < *other) {
                        *other = *other - 1;
                        if (i == 0 && *(int*)(self + 0x7c) == -1)
                            *(int*)(self + 0x7c) = -2;
                    }
                    cSPGuardMgr* g2 = (cSPGuardMgr*)*(void**)(g_pMagic + 0xd8);
                    g2->FUN_00f03ff0(*other, self + 0x8c + i * 0xc, 0);
                }
            }
            char* snd2 = (char*)EA_Audio_GetSystemAT();
            void* ar2 = 0;
            if (snd2)
                ar2 = (*(FnP)(*(void**)(*(char**)snd2 + 0x20)))(snd2);
            SP_cSPUISpace_KillSetiEffects(0x29a5412f, (int)ar2);
            for (int i = 0; i < 4; ++i)
                FUN_00edb120(i);
            return true;
        } else {
            return ((cSPEditorNamingBase*)self)->HandleUIMessage(window, msg);
        }
        int v = *(int*)(self + 0x7c + idx * 4);
        if (v >= 0) {
            cSPGuardMgr* g3 = (cSPGuardMgr*)*(void**)(g_pMagic + 0xd8);
            g3->FUN_00f03ff0(v, self + 0x8c + idx * 0xc, 0);
        }
        int rs = GetRecorderState_s00ed_af10();
        SP_cSPUISpace_KillSetiEffects(0xe10deda0, rs);
        FUN_00edb730();
        return true;
    }
    return ((cSPEditorNamingBase*)self)->HandleUIMessage(window, msg);
}

// @ 0x00edb9b0
void ActsBarUI::FUN_00edb9b0(int on)
{
    char* self = (char*)this;
    ((cSPEditorNamingBase*)self)->SetExpanded(on);
    if ((char)on) {
        ((cSPActsBarOps*)self)->FUN_00edadd0();
        for (int i = 0; i < 4; ++i)
            FUN_00edb120(i);
        return;
    }
    void* mgr = *(void**)(g_pMagic + 0x74);
    ((cSPGuardMgr*)mgr)->FUN_00f3bfc0(*(void**)(self + 0xbc), self + 0x8c, 0, 0);
    for (int i = 0; i < 4; ++i) {
        int tmp[3] = {0, 0, 0};
        cSPGuardMgr* g1 = (cSPGuardMgr*)*(void**)(g_pMagic + 0xd8);
        g1->FUN_00f03ff0(*(int*)(self + 0x7c + i * 4), tmp, 1);
        ((cSPGuardMgr*)mgr)->FUN_00f3bfc0(*(void**)(self + 0xbc + i * 4), tmp, 1, i);
    }
    ((cSPHintHolder*)*(void**)(g_pMagic + 0xd4))->FUN_00efbbe0(0x16, 0x17);
}

// @ 0x00edba80
RunInfo* do_copy(RunInfo* first, RunInfo* last, RunInfo* result)
{
    while (last != first) {
        --last;
        --result;
        *result = *last;
    }
    return result;
}

// @ 0x00edbac0
bool cScenarioEditModeScriptActsBarUI::FUN_00edbac0(void* parent)
{
    char* s = (char*)this;
    char* dlg = 0;
    void* buf = operator_new(0x18, (const char*)0x013f6b3c, 0, 0, 0, 0);
    if (buf)
        dlg = (char*)((cConnectionDialog*)buf)->ctor();
    char* old = *(char**)(s + 0xc);
    if (dlg != old) {
        if (dlg)
            (*(FnV)(*(void**)(*(char**)dlg + 4)))(dlg);
        *(char**)(s + 0xc) = dlg;
        if (old)
            (*(FnV)(*(void**)(*(char**)old + 8)))(old);
    }
    if (!((cSPUILayout_s00ed_af10*)*(void**)(s + 0xc))->Init((void*)0x015ac580, 0, 0x5b598fa))
        return false;
    char* old2 = *(char**)(s + 0x10);
    if (parent != old2) {
        if (parent)
            (*(FnV)(*(void**)(*(char**)parent)))(parent);
        *(char**)(s + 0x10) = (char*)parent;
        if (old2)
            (*(FnV)(*(void**)(*(char**)old2 + 4)))(old2);
    }
    ((cSPUILayout_s00ed_af10*)*(void**)(s + 0xc))->SetParentWin(*(void**)(s + 0x10), 1, 0x5b598fa);
    ((cSPUILayout_s00ed_af10*)*(void**)(s + 0xc))->SetVisibility(0);
    char* w = (char*)((cSPUILayout_s00ed_af10*)*(void**)(s + 0xc))->FindWindowByID(0x743b980, 1);
    char* old3 = *(char**)(s + 0x14);
    if (w != old3) {
        if (w)
            (*(FnV)(*(void**)(*(char**)w)))(w);
        *(char**)(s + 0x14) = w;
        if (old3)
            (*(FnV)(*(void**)(*(char**)old3 + 4)))(old3);
    }
    if (!*(void**)(s + 0x14))
        return false;
    float* r = (float*)(*(FnP)(*(void**)(*(char**)(s + 0x10) + 0x38)))(*(void**)(s + 0x10));
    float x0 = r[0];
    float x2 = r[2];
    (*(FnII)(*(void**)(*(char**)(s + 0x14) + 0x70)))(*(void**)(s + 0x14), 0, 0);
    char* q = *(char**)(s + 0x14);
    float* r2 = (float*)(*(FnP)(*(void**)(*(char**)q + 0x38)))(q);
    float h = r2[3] - r2[1];
    float wd = x2 - x0;
    (*(FnII)(*(void**)(*(char**)q + 0x74)))(q, *(int*)&wd, *(int*)&h);
    void* found = ((cSPUILayout_s00ed_af10*)*(void**)(s + 0xc))->FindWindowByID(0x7c3fbfe, 1);
    if (found) {
        void* obj = operator_new(0x44, (const char*)0x013f6b3c, 0, 0, 0, 0);
        if (obj)
            obj = ((cSPDialogMem*)obj)->FUN_00f38c70();
        else
            obj = 0;
        ((cSPDialogHolder*)(s + 0x4c))->FUN_00f47630(obj);
        char* slot = *(char**)(s + 0x4c);
        void* f2w = ((cSPUILayout_s00ed_af10*)*(void**)(s + 0xc))->FindWindowByID(0x7c3fbfe, 1);
        (*(FnI)(*(void**)(*(char**)slot + 0x10)))(slot, (int)f2w);
    }
    return true;
}

// @ 0x00edbcb0
void cScenarioEditModeScriptActsBarUI::dtor()
{
    char* s = (char*)this;
    char* c = *(char**)(s + 0x4c);
    if (c)
        (*(FnV)(*(void**)(*(char**)c + 0x14)))(c);
    ((cSPUIAnimator_s00ed_af10*)(s + 0x2c))->Reset();
    int h = *(int*)(s + 0x18);
    if (h) {
        *(int*)(s + 0x18) = 0;
        EA_Messaging_RemoveHandler((void*)h, *(void**)(s + 0x1c), *(void**)(s + 0x20),
                                   *(void**)(s + 0x24), *(void**)(s + 0x28));
    }
    if (*(void**)(s + 0xc))
        ((cSPUILayout_s00ed_af10*)*(void**)(s + 0xc))->Shutdown(1);
    char* p = *(char**)(s + 0x10);
    if (p) {
        *(void**)(s + 0x10) = 0;
        (*(FnV)(*(void**)(*(char**)p + 4)))(p);
    }
    p = *(char**)(s + 0xc);
    if (p) {
        *(void**)(s + 0xc) = 0;
        (*(FnV)(*(void**)(*(char**)p + 8)))(p);
    }
}

// @ 0x00edbd30
void cScenarioEditModeScriptActsBarUI::FUN_00edbd30(int on)
{
    ActsBarView_00edbd30* s = (ActsBarView_00edbd30*)this;
    if ((char)on) {
        void* sub = s ? s->mHandler : 0;
        MsgServer_00edbd30* h = (MsgServer_00edbd30*)EA_Messaging_MessageServer();
        s->mpServer = h;
        s->mpHandler = sub;
        s->mpIds = g_148a46c;
        s->mCount = 1;
        s->mPriority = 0;
        if (h && sub)
            h->AddHandler(sub, 0x7c41ae9);
    } else if (void* h = s->mpServer) {
        s->mpServer = 0;
        EA_Messaging_RemoveHandler(h, s->mpHandler, s->mpIds, (void*)s->mCount, (void*)s->mPriority);
    }
    s->mpWindow->SetFlag(1, on);
    s->mpLayout->SetVisibility(1);
}

// @ 0x00edbdd0
void cScenarioEditModeScriptActsBarUI::FUN_00edbdd0(int a)
{
    char* s = (char*)this;
    char* c = *(char**)(s + 0x4c);
    if (c)
        (*(FnI)(*(void**)(*(char**)c + 0x18)))(c, a);
    if (!((cSPUIAnimator_s00ed_af10*)(s + 0x2c))->Empty())
        ((cSPUIAnimator_s00ed_af10*)(s + 0x2c))->Update();
}

// @ 0x00edbe00
cScenarioEditModeScriptActsBarUI* cScenarioEditModeScriptActsBarUI::ctor()
{
    char* s = (char*)this;
    *(int*)(s + 4) = 0;
    *(void* volatile*)(s + 8) = g_13eb394;
    *(void**)(s + 0) = g_148a478;
    *(void**)(s + 8) = g_148a470;
    *(int*)(s + 0xc) = 0;
    *(int*)(s + 0x10) = 0;
    *(int*)(s + 0x14) = 0;
    _ReadWriteBarrier();
    *(int*)(s + 0x18) = 0;
    *(int*)(s + 0x1c) = 0;
    *(int*)(s + 0x20) = 0;
    *(int*)(s + 0x24) = 0;
    *(int*)(s + 0x28) = 0;
    ((cSPUIAnimator_s00ed_af10*)(s + 0x2c))->ctor();
    *(int*)(s + 0x4c) = 0;
    return (cScenarioEditModeScriptActsBarUI*)s;
}

// @ 0x00edbe60
void cScenarioEditModeScriptActsBarUI::FUN_00edbe60()
{
    char* s = (char*)this;
    *(void**)(s + 0) = g_148a478;
    *(void**)(s + 8) = g_148a470;
    _ReadWriteBarrier();
    char* c = *(char**)(s + 0x4c);
    if (c)
        (*(FnV)(*(void**)(*(char**)c + 0xc)))(c);
    ((cSPUIAnimator_s00ed_af10*)(s + 0x2c))->dtor();
    int h = *(int*)(s + 0x18);
    if (h) {
        *(int*)(s + 0x18) = 0;
        EA_Messaging_RemoveHandler((void*)h, *(void**)(s + 0x1c), *(void**)(s + 0x20),
                                   *(void**)(s + 0x24), *(void**)(s + 0x28));
    }
    char* p = *(char**)(s + 0x14);
    if (p)
        (*(FnV)(*(void**)(*(char**)p + 4)))(p);
    p = *(char**)(s + 0x10);
    if (p)
        (*(FnV)(*(void**)(*(char**)p + 4)))(p);
    p = *(char**)(s + 0xc);
    if (p)
        (*(FnV)(*(void**)(*(char**)p + 8)))(p);
    *(void**)(s + 0) = g_13ec458;
    _ReadWriteBarrier();
    *(void**)(s + 8) = g_13eb394;
}

// @ 0x00edbef0
bool __fastcall FUN_00edbef0(char* self, int, int id, int* p)
{
    if (id != 0x7c41ae9)
        return false;
    int a = *(int*)((char*)p + 8);
    if (*(void**)(g_pMagic + 0x74) != 0) {
        int cmp = *(int*)(self + 0x44) ? (*(int*)(self + 0x44) + 4) : 0;
        if (*(int*)((char*)p + 0x10) == cmp) {
            int idx = ScenarioTutorials_GetActive();
            int r = ((cSPGuardMgr*)*(void**)(g_pMagic + 0x74))->FUN_00f3be60(idx);
            if (r) {
                FUN_00edfda0(r + 0x78, &a);
                char* snd = (char*)EA_Audio_GetSystemAT();
                void* ar = 0;
                if (snd)
                    ar = (*(FnP)(*(void**)(*(char**)snd + 0x20)))(snd);
                SP_cSPUISpace_KillSetiEffects(0xe76c9b4f, (int)ar);
                int rec = ((cSPRecorder*)*(void**)(g_pMagic + 0x14))->FUN_006c0200();
                ((cSPRecording*)rec)->FUN_00ee31d0();
            }
        }
    }
    return false;
}
