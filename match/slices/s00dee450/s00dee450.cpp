// Slice s00dee450 -- SP::cGalaxyGameEntryUIStateMachine (galaxy game-entry UI) helpers
// (00dee450..00def050).
//
//   00dee450  cGalaxyGameEntryUIStateMachine::HandleMessage (ui message switch)
//   00dee770  cGalaxyGameEntryUIStateMachine::UpdateButtonStdDrawable
//   00dee800  cGalaxyGameEntryUIStateMachine::UpdateButtonSPUIDrawable
//   00dee890  verb-icon counter
//   00dee9a0  hover/cursor update over the layout's window rbtree
//   00deebc0  deleting destructor (base)
//   00deec00  hover dispatch wrapper
//   00deed00  layout-record key test
//   00deed40  layout manager teardown
//   00deede0  apply the grid's current display name to the layout window
//   00deee80  grid-mode message filter
//   00deef20  grid-cell selection callback
//   00deefb0  layout-record value lookup
//   00def020  release/latch teardown
//   00def050  cGalaxyGameEntryUIStateMachine::CheckFileName
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <string.h>

typedef unsigned char  byte;
typedef unsigned short wchar16;

void  operator delete[](void* p) throw();                                   // 0x00f47380
void* operator new(unsigned n, const char* file, unsigned line,
                   unsigned a, unsigned b);                                 // 0x00f473a0

// -------------------------------------------------------------------------------------------
// vtables / globals
// -------------------------------------------------------------------------------------------
extern int  gvtbl_notify;      // 0x0147e618
extern int  gvtbl_base;        // 0x0147dba8
extern int  gDAT_16a1570;      // 0x016a1570
extern int  gDAT_16a1574;      // 0x016a1574
extern int  gDAT_16a1578;      // 0x016a1578
extern int  gDAT_16a157c;      // 0x016a157c
extern int  gDAT_16a1580;      // 0x016a1580
extern byte gDAT_16a0f08;      // 0x016a0f08
struct PanelIDs; extern PanelIDs* gkGUI_PanelIDs;   // 0x016a1344  (pointer global)
extern int  gDAT_1485720;      // 0x01485720  (1.0f)
extern int  gDAT_13ec478;      // 0x013ec478
extern int  gDAT_13ebc58;      // 0x013ebc58  "App"
extern int  gDAT_13ebb38;      // 0x013ebb38  allocator name
extern int  gDAT_13f09b4;      // 0x013f09b4  "Simulator"

// -------------------------------------------------------------------------------------------
// external helpers (call relocations are masked by the matcher)
// -------------------------------------------------------------------------------------------
void      FUN_00de53d0(unsigned a);                          // 0x00de53d0
void      FUN_00ded920(unsigned a, unsigned b);              // 0x00ded920
char __stdcall FUN_00de5cb0(unsigned a);                     // 0x00de5cb0
uint32_t  FUN_00dec990(void* p);                             // 0x00dec990
uint32_t  FUN_004bafc0(void* a, void** b);                   // 0x004bafc0
void*     FUN_004010a0(void* a, unsigned b);                 // 0x004010a0
void*     FUN_005ecf80(void* a);                             // 0x005ecf80
void*     EffectsManagerPtr();                               // 0x0067ddd0
void*     APP_Ptr();                                         // 0x0067dd10
void*     MessageServerPtr();                                // 0x0067dcc0
void*     EditorLaunchData_Ctor();                           // 0x005a9080
char      Editor_Launch();                                   // 0x005a9200
void*     NukeSubtreeImpl(void* tree);                       // 0x009a9600
struct RBNode;
RBNode*   RBTreeIncrement(RBNode* n);                        // 0x00921580
void*     WStr_Assign(void* self, void* first, void* last);  // 0x00423650
void*     WStr_Append(void* self, void* a, void* b);         // 0x00429580
void*     WStr_RangeInit(void* self, void* str);             // 0x00579a90
void*     WStr_AssignRange(void* self, void* first, void* last); // 0x00423650
extern "C" int iswctype(int ch, int type);                   // import
char      CreateImageFromResource2(void* a, void** b, char c, int d, int e); // 0x00806230
void      RemoveHandler(void* a, unsigned b, unsigned c, unsigned d, unsigned e); // 0x00571db0
void*     RbtreeFind(void* outIter, const void* key, void* tree);  // 0x00e39fb0
void*     memcpy_(void* d, const void* s, unsigned n);       // import

// -------------------------------------------------------------------------------------------
// object model
// -------------------------------------------------------------------------------------------
struct Hashtable {
    uint32_t mHash;                   // +0x00
    void**   mTable;                  // +0x04
    uint32_t mnBucketCount;           // +0x08
    void*    find_(void* outIter, const void* key);   // 0x00645ed0
};

struct HashPair {
    uint32_t key;                     // +0x00
    uint32_t value;                   // +0x04
};

struct Layout {                       // cSPUILayout (at GalaxyUI + 0x28)
    void*    FindWindowByID(uint32_t id, int b);      // 0x008105b0
    char     mPad[0x18];
};

struct PanelIDs {                     // kGUI_PanelIDs target (pointer at 0x016a1344)
    char     pad_00[0x19c];
    void*    mpHandler;               // +0x19c
    char     pad_1a0[0x1f5 - 0x1a0];
    byte     mFlag;                   // +0x1f5

    void FUN_00de5d00(void* a, void* b, void* c, void* d, void* e, void* f, void* g);
};

struct GridObj {                      // the editor grid object (at GalaxyUI + 0x628)
    char      pad_00[0x20];
    wchar16*  mpName;                 // +0x20 (eastl wstring data)
    char      pad_24[0x80 - 0x24];
    float     x;                      // +0x80
    float     y;                      // +0x84
    float     z;                      // +0x88
    char      pad_8c[0xa8 - 0x8c];
    int32_t   mIndex;                 // +0xa8
    char      pad_ac[0xb0 - 0xac];
    void*     mB0;                    // +0xb0
};

struct Record {                       // 0xc0-byte layout record (GalaxyUI + 0x84 + i*0xc0)
    char       pad0[0x20];
    Hashtable  mHash;                 // +0x20
    char       pad2[0xc0 - 0x2c];

    bool FUN_00deed00(uint32_t key);
};

struct RBNode {
    char      pad_00[0x10];
    uint32_t  mKey;                   // +0x10
    union { uint32_t mValue; byte mFlag; };   // +0x14
};

struct Rbtree {                       // eastl::rbtree header (0x18 bytes)
    uint32_t  m00;                    // +0x00
    void*     mpAnchor;               // +0x04  (sentinel "node"; &mpAnchor is the end node)
    void*     mpRoot;                 // +0x08
    void*     mp0c;                   // +0x0c
    byte      mFlag;                  // +0x10
    char      pad_11[0x03];
    uint32_t  mnSize;                 // +0x14

    void DoNukeSubtree(void* node);   // 0x009a9600
};

struct UIDrawable {                    // a drawable window returned by a window vtable slot
    void** vtbl;                       // +0x00
    void   SetImageIcon(int a, void* b);   // 0x00831760
};

struct LaunchData {                    // editor launch-data object (operator new 0x9c)
    char       pad_00[0x0c];
    uint32_t   f0c;                    // +0x0c
    uint32_t   f10;                    // +0x10
    uint32_t   f14;                    // +0x14
    uint32_t   f18;                    // +0x18
    char       pad_1c[0x88 - 0x1c];
    void*      f88;                    // +0x88
    uint32_t   f8c;                    // +0x8c
    uint32_t   f90;                    // +0x90
    uint32_t   f94;                    // +0x94
    uint32_t   f98;                    // +0x98
    uint32_t   f9c;                    // +0x9c

    LaunchData* Ctor();                // 0x005a9080
};

// __thiscall dispatch helpers on an explicit vtable-pointer field.
typedef void   (__thiscall *VF0)(void*);
typedef void   (__thiscall *VF1)(void*, int);
typedef void*  (__thiscall *VFP)(void*);
typedef void*  (__thiscall *VFP1)(void*, int);
typedef int    (__thiscall *VFI)(void*);
typedef void   (__thiscall *VF2)(void*, int, int);
typedef void   (__thiscall *VF2P)(void*, void*, int);
typedef char   (__thiscall *VFC2F)(void*, float, float);
typedef void   (__thiscall *VF2F)(void*, float, float, void*);
typedef void   (__thiscall *VFC8)(void*, float, float, float*);
typedef void   (__thiscall *VFIP)(void*, int, void*);
typedef void   (__thiscall *VF3)(void*, int, int, int);
typedef void   (__thiscall *VF1P)(void*, void*);

struct MsgCtx {
    char  pad_00[0x18];
    float mLocal[9];                  // +0x18  (3x3 matrix)
    char  pad_3c[0x48 - 0x3c];
    byte  mFlag44;                    // +0x44
};

namespace SP {

struct Sub608 {                       // sub-object at GalaxyUI + 0x608
    char pad_00[0x0c];
    void FUN_00e20e80();              // 0x00e20e80
};

class GalaxyUI {                      // cGalaxyGameEntryUIStateMachine
public:
    void**     vtbl0;                 // +0x00
    void**     vtbl1;                 // +0x04
    void*      field_08;              // +0x08
    void*      field_0c;              // +0x0c
    void*      field_10;              // +0x10
    void*      mpRef14;               // +0x14
    uint32_t   f18;                   // +0x18
    uint32_t   f1c;                   // +0x1c
    uint32_t   f20;                   // +0x20
    uint32_t   f24;                   // +0x24
    Layout     mLayout;               // +0x28
    Rbtree     mMap40;                // +0x40
    char       pad_58[0x18];
    uint32_t   mFlag70;               // +0x70
    uint32_t   mHoverFlag;            // +0x74
    char       pad_78[0x84 - 0x78];
    Record     mRecords[1];           // +0x84  (variable-length, 0xc0 stride)
    char       pad_144[0x500 - 0x144];
    uint32_t   f500;                  // +0x500
    uint32_t   f504;                  // +0x504
    uint32_t   f508;                  // +0x508
    uint32_t   f50c;                  // +0x50c
    uint32_t   f510;                  // +0x510
    char       pad_514[0x520 - 0x514];
    Rbtree     mMap520;               // +0x520
    char       pad_538[0x5e0 - 0x538];
    uint32_t   f5e0;                  // +0x5e0
    char       pad_5e4[0x608 - 0x5e4];
    Sub608     mSub;                  // +0x608
    void*      mpRef614;              // +0x614
    char       pad_618[0x624 - 0x618];
    GridObj*   mp624;                 // +0x624
    GridObj*   mpGrid;                // +0x628

    void      FUN_00dee2a0();         // 0x00dee2a0
    void*     FUN_00deebc0(unsigned flags);
    void      FUN_00deed40();
    void      FUN_00deede0();
    char      FUN_00deee80(int mode);
    void      FUN_00deef20(unsigned a, unsigned b, void* map);
    uint32_t  FUN_00deefb0(uint32_t key);
    void      FUN_00dee9a0(float a, float b);
    void      FUN_00dee770(uint32_t id, void* refObj);
    void      FUN_00dee800(uint32_t id);
    char      FUN_00dee450(int msg, void* ctx);
    char      FUN_00def050(void* nameObj);
};

class Wrapper {                       // |this| of the hover wrappers (00deec00 / 00def020)
public:
    char       pad0[0x08];
    GalaxyUI*  mpP;                   // +0x08
    char       pad_0c[0x14 - 0x0c];
    void*      mpRef14;               // +0x14

    void FUN_00deec00(float a, float b, float c);
    void FUN_00def020();
};

} // namespace SP

using SP::GalaxyUI;
using SP::Wrapper;

// -------------------------------------------------------------------------------------------
// 00deebc0 : deleting destructor (base)
// -------------------------------------------------------------------------------------------
// @ 0x00deebc0
void* GalaxyUI::FUN_00deebc0(unsigned flags)
{
    void* ref;
    this->vtbl0 = (void**)&gvtbl_notify;
    gDAT_16a1570 = 0;
    ref = this->mpRef14;
    if (ref != 0)
        ((VF0)((void**)*(void**)ref)[1])(ref);
    this->vtbl0 = (void**)&gvtbl_base;
    if (flags & 1)
        operator delete[](this);
    return this;
}

// -------------------------------------------------------------------------------------------
// 00deec00 : hover dispatch wrapper
// -------------------------------------------------------------------------------------------
// @ 0x00deec00
void Wrapper::FUN_00deec00(float a, float b, float c)
{
    GalaxyUI* p = this->mpP;
    if (p->mHoverFlag != 0) {
        p->FUN_00dee9a0(a, b);
    }
    (void)c;
}

// -------------------------------------------------------------------------------------------
// 00deed00 : layout-record key test
// -------------------------------------------------------------------------------------------
// @ 0x00deed00
bool Record::FUN_00deed00(uint32_t key)
{
    struct Iter { void* node; void* end; } it;
    Hashtable* ht = &mHash;
    ht->find_(&it, &key);
    return it.node != ht->mTable[ht->mnBucketCount];
}
// -------------------------------------------------------------------------------------------
// 00deee80 : grid-mode message filter
// -------------------------------------------------------------------------------------------
// @ 0x00deee80
char GalaxyUI::FUN_00deee80(int mode)
{
    if (mode != 0xb && mode != 1) {
        if (gkGUI_PanelIDs->mFlag == 0 &&
            FUN_00de5cb0(0x26b05664) == 0 &&
            mode == 6 &&
            gDAT_16a0f08 != 0)
            return 0;
        {
            GridObj* g = this->mpGrid;
            if (g == 0) return 0;
            Record*   rec = &this->mRecords[g->mIndex];
            Hashtable* ht = &rec->mHash;
            void* end = ht->mTable[ht->mnBucketCount];
            struct Iter { void* node; void* end; } it;
            uint32_t k = (uint32_t)mode;
            void* r = ht->find_(&it, &k);
            if (*(void**)r == end) return 0;
        }
    }
    return 1;
}

// -------------------------------------------------------------------------------------------
// 00deefb0 : layout-record value lookup
// -------------------------------------------------------------------------------------------
// @ 0x00deefb0
uint32_t GalaxyUI::FUN_00deefb0(uint32_t key)
{
    GridObj* g = this->mpGrid;
    if (g != 0 && g->mIndex != 6) {
        Record*    rec = &this->mRecords[g->mIndex];
        Hashtable* ht  = &rec->mHash;
        struct Iter { void* node; void* end; } it;
        ht->find_(&it, &key);
        if (it.node != ht->mTable[ht->mnBucketCount])
            return ((HashPair*)it.node)->value;
    }
    return 0;
}

// -------------------------------------------------------------------------------------------
// 00def020 : release/latch teardown
// -------------------------------------------------------------------------------------------
// @ 0x00def020
void Wrapper::FUN_00def020()
{
    GalaxyUI* p = this->mpP;
    if (p != 0) {
        p->FUN_00deed40();
        p = this->mpP;
        if (p != 0)
            ((VF1)p->vtbl0[2])(p, 1);
        this->mpP = 0;
    }
}

// -------------------------------------------------------------------------------------------
// 00dee770 : UpdateButtonStdDrawable (rebuild a standard button's image)
// -------------------------------------------------------------------------------------------
// @ 0x00dee770
void GalaxyUI::FUN_00dee770(uint32_t id, void* refObj)
{
    void* w = mLayout.FindWindowByID(id, 1);
    if (w == 0) return;
    void** wvt = *(void***)w;
    void*  d   = ((VFP)wvt[0xa8 / 4])(w);
    if (d == 0) return;
    void** dvt = *(void***)d;
    void*  img = ((VFP1)dvt[0x0c / 4])(d, 0x103c1908);
    if (img == 0) return;
    void*  res = 0;
    CreateImageFromResource2((void*)(size_t)id, &res, 0, -1, -1);
    ((VFIP)dvt[0x14 / 4])(d, 0, res);
    ((VF0)wvt[0x90 / 4])(w);
    if (refObj != 0)
        ((VF0)(*(void***)refObj)[1])(refObj);
}

// -------------------------------------------------------------------------------------------
// 00dee800 : UpdateButtonSPUIDrawable (rebuild a SPUI button's image)
// -------------------------------------------------------------------------------------------
// @ 0x00dee800
void GalaxyUI::FUN_00dee800(uint32_t id)
{
    void* w = mLayout.FindWindowByID(id, 1);
    if (w == 0) return;
    void** wvt = *(void***)w;
    void*  d   = ((VFP)wvt[0xa8 / 4])(w);
    if (d == 0) return;
    void** dvt = *(void***)d;
    void*  obj = ((VFP1)dvt[0x0c / 4])(d, 0x53eb526);
    if (obj == 0) return;
    void*  res = 0;
    CreateImageFromResource2((void*)(size_t)id, &res, 0, -1, -1);
    ((UIDrawable*)obj)->SetImageIcon(0, res);
    ((VF0)wvt[0x90 / 4])(w);
}

// -------------------------------------------------------------------------------------------
// 00dee890 : verb-icon counter (scan the editor's item list)
// -------------------------------------------------------------------------------------------
// @ 0x00dee890
uint32_t __stdcall FUN_00dee890(void* editor)
{
    void*  list  = 0;
    FUN_004bafc0(editor, &list);
    void** listv = (void**)list;
    if (listv == 0)
        return 2;
    int count = (int)((char*)listv[0x27] - (char*)listv[0x26]) / 0x8c;
    int n = (count > 0x40) ? 0x40 : count;
    char hasBad = 0;
    char flag   = 0;
    for (int i = 0; i < n; ++i) {
        uint32_t r = FUN_00dec990(*(void**)((char*)listv[0x26] + i * 0x8c));
        if (r == 2) {
            hasBad = 1;
        } else if (r == 3) {
            flag = 1;
        } else if (r == 4) {
            flag = 1;
            hasBad = 1;
        }
    }
    uint32_t result = 0;
    if (hasBad)
        result = (flag == 0) ? 1 : 2;
    if (listv != 0)
        ((VF0)(*(void***)listv)[1])(listv);
    return result;
}

// -------------------------------------------------------------------------------------------
// 00dee9a0 : hover/cursor update over the layout's window rbtree
// -------------------------------------------------------------------------------------------
// @ 0x00dee9a0
void GalaxyUI::FUN_00dee9a0(float a, float b)
{
    Rbtree* tree = &mMap40;
    RBNode* end  = (RBNode*)&tree->mpAnchor;
    RBNode* n;
    for (n = (RBNode*)tree->mpRoot; n != end; n = RBTreeIncrement(n)) {
        void* w = mLayout.FindWindowByID(n->mKey, 1);
        if (w == 0) continue;
        void** vt = *(void***)w;
        char   ok = (char)(((VFI)vt[0x28 / 4])(w) & 1);
        void*  c  = ((VFP)vt[0x10 / 4])(w);
        while (ok & 1) {
            if (c == 0) {
                float out[2];
                ((VFC8)vt[0xc8 / 4])(w, a, b, out);
                char hit = ((VFC2F)vt[0xbc / 4])(w, out[0], out[1]);
                if (hit == 0 && n->mFlag == 1) {
                    FUN_00ded920(n->mKey, 1);
                    n->mFlag = 0;
                }
                break;
            }
            void** cvt = *(void***)c;
            ok = (char)(((VFI)cvt[0x28 / 4])(c) & 1);
            c  = ((VFP)cvt[0x10 / 4])(c);
        }
    }
    for (n = (RBNode*)tree->mpRoot; n != end; n = RBTreeIncrement(n)) {
        void* w = mLayout.FindWindowByID(n->mKey, 1);
        if (w == 0) continue;
        void** vt = *(void***)w;
        char   ok = (char)(((VFI)vt[0x28 / 4])(w) & 1);
        void*  c  = ((VFP)vt[0x10 / 4])(w);
        while (ok & 1) {
            if (c == 0) {
                float out[2];
                ((VFC8)vt[0xc8 / 4])(w, a, b, out);
                char hit = ((VFC2F)vt[0xbc / 4])(w, out[0], out[1]);
                if (hit != 0 && n->mFlag == 0) {
                    FUN_00ded920(n->mKey, 0);
                    n->mFlag = 1;
                }
                break;
            }
            void** cvt = *(void***)c;
            ok = (char)(((VFI)cvt[0x28 / 4])(c) & 1);
            c  = ((VFP)cvt[0x10 / 4])(c);
        }
    }
}

// -------------------------------------------------------------------------------------------
// 00deed40 : layout manager teardown
// -------------------------------------------------------------------------------------------
// @ 0x00deed40
void GalaxyUI::FUN_00deed40()
{
    mSub.FUN_00e20e80();
    FUN_00dee2a0();
    if (mpRef14 != 0) {
        void* h = mpRef14;
        mpRef14 = 0;
        RemoveHandler(h, f18, f1c, f20, f24);
    }
    if (mpRef614 != 0) {
        void* r = mpRef614;
        mpRef614 = 0;
        ((VF0)(*(void***)r)[2])(r);
    }
    mMap520.DoNukeSubtree(mMap520.mp0c);
    mMap520.mpRoot  = &mMap520.mpAnchor;
    mMap520.mp0c    = 0;
    mMap520.mFlag   = 0;
    mMap520.mnSize  = 0;
    mMap520.mpAnchor = &mMap520.mpAnchor;
    mMap40.DoNukeSubtree(mMap40.mp0c);
    mMap40.mp0c     = 0;
    mMap40.mFlag    = 0;
    mMap40.mnSize   = 0;
    mMap40.mpRoot   = &mMap40.mpAnchor;
    mMap40.mpAnchor = &mMap40.mpAnchor;
}

// -------------------------------------------------------------------------------------------
// 00deede0 : apply the grid's current display name to the layout window
// -------------------------------------------------------------------------------------------
// @ 0x00deede0
void GalaxyUI::FUN_00deede0()
{
    GridObj* g = this->mpGrid;
    if (g == 0) return;
    // NOTE: the retail prologue rebuilds the localized display name through
    // eastl::wstring/collate helpers (FUN_004010a0 / FUN_005ecf80); this
    // reimplementation only performs the window-update half.
    void* w = mLayout.FindWindowByID(0x7d275bb, 1);
    if (w == 0) return;
    void** wvt = *(void***)w;
    void*  img = ((VFP1)wvt[0x0c / 4])(w, 0xcf428691);
    if (img == 0) return;
    ((VF2P)(*(void***)img)[0x60 / 4])(img, g->mpName, 0);
}

// -------------------------------------------------------------------------------------------
// 00deef20 : grid-cell selection callback
// -------------------------------------------------------------------------------------------
// @ 0x00deef20
void GalaxyUI::FUN_00deef20(unsigned a, unsigned b, void* map)
{
    Rbtree* tree = (Rbtree*)map;
    void*   end  = &tree->mpAnchor;
    void*   it[2];
    uint32_t key = b;
    void**  found = (void**)RbtreeFind(it, &key, map);
    RBNode* node  = (RBNode*)*found;
    if (node == (RBNode*)end) return;
    void* w = mLayout.FindWindowByID(0x5384881, 1);
    ((VF2)(*(void***)w)[0x7c / 4])(w, 1, 0);
    GridObj* g = this->mpGrid;
    void* self = (this != 0) ? (void*)&this->field_08 : 0;
    gkGUI_PanelIDs->FUN_00de5d00((void*)(size_t)node->mValue, self,
                                  (void*)g->mB0, 0, 0, (void*)(size_t)b, 0);
}

// -------------------------------------------------------------------------------------------
// 00dee450 : cGalaxyGameEntryUIStateMachine::HandleMessage (ui message switch)
// -------------------------------------------------------------------------------------------
// @ 0x00dee450
char GalaxyUI::FUN_00dee450(int msg, void* ctx)
{
    if (msg == 0x625e26a) {
        if (mFlag70 != 0) {
            FUN_00de53d0(1);
            float m[9];
            memcpy_(m, &gDAT_16a1580, sizeof(m));
            void*     em  = EffectsManagerPtr();
            PanelIDs* ids = gkGUI_PanelIDs;
            if (ids->mpHandler != 0) {
                void* h = ids->mpHandler;
                ids->mpHandler = 0;
                ((VF0)(*(void***)h)[1])(h);
            }
            ((VF2P)(*(void***)em)[0x2c / 4])(em, &ids->mpHandler, 0x3d6ef67);
            if (ids->mpHandler != 0) {
                void* h = ids->mpHandler;
                ((VF1)(*(void***)h)[0x18 / 4])(h, (int)(size_t)ctx);
                ((VF1)(*(void***)h)[0x08 / 4])(h, 0);
            }
            void* w = mLayout.FindWindowByID(0x5384881, 1);
            ((VF2)(*(void***)w)[0x7c / 4])(w, 1, 1);
        }
        return 1;
    }
    if (msg == 0x5b5c746) {
        if (f5e0 == 0) {
            FUN_00de53d0(0);
            LaunchData* d = (LaunchData*)operator new(0x9c, "App", 0, 0, 0);
            if (d != 0) {
                void* app = APP_Ptr();
                LaunchData* obj = d->Ctor();
                if (obj != 0) {
                    obj->f0c = f500;
                    obj->f10 = f504;
                    obj->f14 = f508;
                    obj->f18 = f50c;
                    obj->f90 = ((VFI)(*(void***)app)[0x38 / 4])(app);
                    obj->f88 = 0;
                    obj->f8c = ((VFI)(*(void***)app)[0x0c / 4])(app);
                    if (obj->f8c != 0)
                        ((VF0)(*(void***)(size_t)obj->f8c)[1])((void*)(size_t)obj->f8c);
                    obj->f94 = (uint32_t)(size_t)&gDAT_13f09b4;   // "Simulator"
                    obj->f98 = (uint32_t)(size_t)&gDAT_13ebc58;   // "App"
                    obj->f9c = 0;
                    Editor_Launch();
                    ((VF0)(*(void***)obj)[1])(obj);
                }
            }
            return 1;
        }
        f5e0 = f5e0 - 1;
        void* ms = MessageServerPtr();
        ((VF3)(*(void***)ms)[0x18 / 4])(ms, 0x5b5c746, 0, 0);
        return 1;
    }
    if (msg == 0x30c11c7 && mFlag70 != 0) {
        void* w = mLayout.FindWindowByID(0x5384881, 0);
        ((VF1)(*(void***)w)[0x7c / 4])(w, 1);
        if (((MsgCtx*)ctx)->mFlag44 == 0)
            ((VF1P)this->vtbl1[0])(&this->vtbl1, ((MsgCtx*)ctx)->mLocal);
        return 1;
    }
    return 1;
}

// -------------------------------------------------------------------------------------------
// 00def050 : cGalaxyGameEntryUIStateMachine::CheckFileName
// -------------------------------------------------------------------------------------------
// @ 0x00def050
char GalaxyUI::FUN_00def050(void* nameObj)
{
    // NOTE: approximate reimplementation of the retail in-place wstring sanitation
    // (strip leading characters that are not alpha-numeric, then runs of separators).
    wchar16** s     = (wchar16**)nameObj;
    wchar16*  begin = s[0];
    wchar16*  end   = s[1];
    char      changed = 0;
    while (begin != end && !iswctype(*begin, 0x107)) {
        for (wchar16* p = begin; p + 1 != end; ++p)
            *p = p[1];
        if (end != begin) --end;
        changed = 1;
    }
    if (begin != end) {
        static const wchar16 kBad[] = { '.', ',', '/', '?', ']', '$', '[', '{',
                                        '\\', '|', ';', ':', '*', '\'', '"', 0 };
        wchar16* w = begin;
        while (w != end) {
            char bad = 0;
            for (int i = 0; kBad[i] != 0; ++i)
                if (*w == kBad[i]) { bad = 1; break; }
            if (bad) {
                changed = 1;
                wchar16* q = w;
                while (q != end && *q == *w) ++q;
                for (wchar16* p = q; p != end; ++p)
                    *(w + (p - q)) = *p;
                end -= (q - w);
            } else {
                ++w;
            }
        }
    }
    s[0] = begin;
    s[1] = end;
    return changed;
}