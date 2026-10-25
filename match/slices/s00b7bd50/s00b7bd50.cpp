// Slice s00b7bd50 (batch bfs1 #35).  SP::cSPPieMenu and related helpers.
// 32-bit MSVC 2008 SP1, mostly /O2 /MD /Gy /EHsc /TP /arch:SSE2.

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern "C" double sqrt(double);
#include <emmintrin.h>

static inline void Vv0(void* p, int slot) {
    ((void(__thiscall*)(void*))(*(void***)p)[slot / 4])(p);
}
static inline void Vv1(void* p, int slot, int a) {
    ((void(__thiscall*)(void*, int))(*(void***)p)[slot / 4])(p, a);
}
static inline void Vv2(void* p, int slot, int a, int b) {
    ((void(__thiscall*)(void*, int, int))(*(void***)p)[slot / 4])(p, a, b);
}
static inline int Vi0(void* p, int slot) {
    return ((int(__thiscall*)(void*))(*(void***)p)[slot / 4])(p);
}

// ---------------------------------------------------------------------------
// cSPUIPieMenuItemWinProc (2008 dev PDB: CustomWinProc, size 0x1c).
// ---------------------------------------------------------------------------
class cSPUIPieMenuItemWinProc { public:
    void** vftable;             // +0x00
    char   pad_04[0xc - 0x04];
    int    mButtonId;           // +0x0c
    int    mItemId;             // +0x10
    bool   bButtonClicked;      // +0x14
    void*  mpHighlightCallback; // +0x18

    void Hide();                // 0x00818330
    bool ContainsWindow(void* hwnd); // 0x00818370
};

// ---------------------------------------------------------------------------
// Simulator::cSpatialObject (retail offsets read from the disassembly).
// The first member is the per-object interface block; `[p]` + slot is the
// dispatch entry (see 0x00b7cb20 / 0x00b7c9c0), matching VRet*() below.
// ---------------------------------------------------------------------------
union Vec3 { float f[3]; int i[3]; u32 u[3]; };

struct SpTransform {            // cSPTransform, 0x20 bytes
    char  mPad00[4];            // +0x00
    Vec3  mVec04;               // +0x04
    float mF10;                 // +0x10
    Vec3  mVec14;               // +0x14
};

struct cSpatialObject {
    void** vftable;             // +0x00
    u32    mFlags;              // +0x04
    SpTransform mXf;            // +0x08
    char   pad_28[0x90 - 0x28];
    void*  mpPropertyList;      // +0x90
};

// ===========================================================================
//  Global state for the ASCII/UTF pie menu (addresses from disassembly).
// ===========================================================================
extern cSPUIPieMenuItemWinProc* g_pPieWinProc;  // 0x0168817c
extern int g_PieMenuState;                      // 0x01688150
extern u8  g_bPieMenuVisible;                   // 0x01688154
extern int g_PieMenuFontRes;                    // 0x04518450

extern "C" void* __cdecl SP_GameInputManager();

// ===========================================================================
//  0x00b7c750  accept callback
// ===========================================================================
// @ 0x00b7c750
void __cdecl PieMenuAcceptCallback(int param, int unused, char condition) {
    if (condition) {
        void* p = SP_GameInputManager();
        Vv1(p, 0x68, param);
    }
}

// ===========================================================================
//  0x00b7c810  static SP::cSPPieMenu::HideUTFMenu(bool)
// ===========================================================================
// @ 0x00b7c810
void __cdecl cSPPieMenu_HideUTFMenu(char bPlaySound) {
    if (g_pPieWinProc) {
        g_pPieWinProc->Hide();
        Vv0(g_pPieWinProc, 0x24);
        cSPUIPieMenuItemWinProc* q = g_pPieWinProc;
        if (q) {
            g_pPieWinProc = 0;
            Vv0(q, 0x04);
        }
        if (bPlaySound) {
            void* gm = SP_GameInputManager();
            Vv2(gm, 0x64, (int)&g_PieMenuFontRes, 1);
        }
    }
    g_PieMenuState = 0;
    g_bPieMenuVisible = 0;
}

// ===========================================================================
//  0x00b7c870  bool pie-menu window contains hwnd
// ===========================================================================
// @ 0x00b7c870
bool __cdecl cSPPieMenu_ContainsWindow(void* hwnd) {
    if (g_bPieMenuVisible) {
        return g_pPieWinProc->ContainsWindow(hwnd);
    }
    return false;
}

// ===========================================================================
//  Property helpers (used by several functions below)
// ===========================================================================
struct Property {
    char  pad_00[0x10];
    u16   mFlags;               // +0x10
    u16   mType;                // +0x12
    char  pad_14[0x40 - 0x14];

    u8*    sub_41e920();        // 0x0041e920 value accessor (bool/enum)
    float* sub_41ea70();        // 0x0041ea70 value accessor (float)
};
struct PropertyList {
    bool GetProperty(u32 key, Property** out) {
        return ((bool(__thiscall*)(void*, u32, Property**))(*(void***)this)[0x24 / 4])(this, key, out);
    }
    bool HasProperty(u32 key) {
        Property* p;
        return GetProperty(key, &p) != 0;
    }
    float GetFloatProperty(u32 key) {
        Property* p;
        if (GetProperty(key, &p) && p->mType == 0xd) return *p->sub_41ea70();
        return 0.0f;
    }
    bool GetBoolProperty(u32 key) {
        Property* p;
        if (GetProperty(key, &p) && p->mType == 1) return *p->sub_41e920() != 0;
        return false;
    }
};

extern "C" void* __cdecl SP_App();

// stub types so the helpers below get `this` in ECX (__thiscall)
struct PlanetModel {
    float GetRadius();              // 0x00b7e4d0
};
struct Viewer {
    void GetCameraLocationInfo(float* out, int a, int b, int c);   // 0x007c3d30
};
struct OtherObj {
    float SomeFloat();              // 0x00c887c0
};

static inline void* VRet(void* p, int slot) {
    return ((void*(__thiscall*)(void*))(*(void***)p)[slot / 4])(p);
}
static inline float VRetF(void* p, int slot) {
    return ((float(__thiscall*)(void*))(*(void***)p)[slot / 4])(p);
}
static inline void* VRet1(void* p, int slot, void* a) {
    return ((void*(__thiscall*)(void*, void*))(*(void***)p)[slot / 4])(p, a);
}
static inline void* VRet2(void* p, int slot, void* a, void* b) {
    return ((void*(__thiscall*)(void*, void*, void*))(*(void***)p)[slot / 4])(p, a, b);
}
static inline void* VRet3(void* p, int slot, void* a, void* b, void* c) {
    return ((void*(__thiscall*)(void*, void*, void*, void*))(*(void***)p)[slot / 4])(p, a, b, c);
}
struct S7c4180 { void sub_7c4180(float* dest, const float* center); };  // 0x007c4180
extern "C" void __cdecl sub_805ea0(float* out);                        // 0x00805ea0

static inline float SqrtF(float x) {
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(x)));
}
static inline float AbsF(float x) {
    Vec3 v;
    v.f[0] = x;
    v.u[0] &= 0x7fffffffu;
    return v.f[0];
}

// Ref-counted object: the interface object lives at [p], its dispatch table at
// [[p]] (see the Release sequences at 0x00b7c480 / 0x00b7bd50).
struct RefObject {
    void* mpIface;              // +0x00
    u32   mFlags;               // +0x04
    char  pad_08[0x40 - 0x08];
    int   mnRefCount;           // +0x40
};

static inline void RefIfaceCall(RefObject* o, int slot, int arg) {
    void*  iface = o->mpIface;
    void** vt = *(void***)iface;
    ((void(__thiscall*)(void*, RefObject*, int))vt[slot / 4])(iface, o, arg);
}
static inline void RefRelease(RefObject* o) {
    if (o->mnRefCount > 1) {
        o->mnRefCount -= 1;
    } else {
        RefIfaceCall(o, 0x170, (int)(o->mFlags >> 31));
    }
}

// ===========================================================================
//  Pie menu value / hash-table node types
// ===========================================================================
struct MenuItemValue {          // 0xc64 bytes
    SpTransform mXf;            // +0x00 (cached transform of the source object)
    char  pad_20[0x38 - 0x20];
    float mRadius;              // +0x38
    char  pad_3c[0x4c - 0x3c];
    void* mpVecBegin;           // +0x4c
    void* mpVecEnd;             // +0x50
    void* mpVecCap;             // +0x54
    char  pad_58[0xc64 - 0x58];

    MenuItemValue* sub_b75820();                    // 0x00b75820 default ctor
    void sub_b778b0(const MenuItemValue* src);      // 0x00b778b0 copy ctor
};
// The cached transform lives at value+0x04 (mXf.mVec14), which is also the
// element base of a node's value: &node->mValue is node+0x04, and node+0x08
// is therefore node->mValue.mXf.mVec04 (seen directly in the disassembly).
static inline MenuItemValue* NodeValue(void* node) { return (MenuItemValue*)((char*)node + 4); }

struct ScreenNode {             // key = spatial object pointer
    u32          mKey;          // +0x00
    MenuItemValue mValue;       // +0x04
    ScreenNode*  pNext;         // +0xc68
};
struct ScreenValue {            // the value_type inserted into the map
    u32          mKey;          // +0x00
    MenuItemValue mValue;       // +0x04
};

struct ModelKey { u32 k0, k1, k2; };
struct ModelNode {              // key = {model key, 0, 4.12890625f}
    ModelKey     mKey;          // +0x00
    MenuItemValue mValue;       // +0x0c
    ModelNode*   pNext;         // +0xc70
};
struct ModelValue {
    ModelKey     mKey;          // +0x00
    MenuItemValue mValue;       // +0x0c
};

struct HashIter  { void* node; void* bucket; };
struct HashIter4 { void* node; void* bucket; void* last; void* lastBucket; };

// ===========================================================================
//  Hash table used by cSPPieMenu at +0x54a8/+0x54c8/+0x54e8
// ===========================================================================
struct HashTable {
    char   pad_00[4];
    void** ppBuckets;           // +0x04
    u32    nBucketCount;        // +0x08
    void*  End() { return ppBuckets[nBucketCount]; }

    void  sub_b74800(HashIter* out, const void* key);        // 0x00b74800 find
    void  sub_b74740(HashIter4* out, const void* key);       // 0x00b74740 lower_bound
    void  sub_b79680(HashIter* out, const void* value, int flag);  // 0x00b79680 insert
    void  sub_b795c0(HashIter* out, const void* value, int flag);  // 0x00b795c0 insert (3-dword key)
    void  sub_b766b0(HashIter* out, HashIter it);            // 0x00b766b0 erase
    void  sub_b76580(HashIter* out, HashIter it);            // 0x00b76580 erase (3-dword key)
    void  sub_b76620(const void* key);                       // 0x00b76620 erase by key
    __declspec(noinline) void* sub_b7c1b0(const void* key);  // 0x00b7c1b0 find-or-insert
    char   pad_0c[0x14];        // +0x0c  (each map header is 0x20 bytes)
};

extern "C" bool __cdecl sub_41dd30(const void* a, const void* b);   // 0x0041dd30
extern "C" bool __cdecl sub_41dd90(const void* a, const void* b);   // 0x0041dd90
extern "C" bool __cdecl sub_b78880(void* a, void* b, void* c, int d); // 0x00b78880
extern "C" void __cdecl sub_5f4e10(void* src, void* end, void* dst); // 0x005f4e10
// cSPTransform::operator= (0x00537dc0) is __thiscall: this in ECX, source ptr on the stack.
struct CTransformAssign { void Assign(const void* src); };            // 0x00537dc0
extern "C" void __cdecl FUN_f47380(void* p);                        // 0x00f47380 operator delete
extern "C" void __cdecl sub_b75240(void* a, void* b, int c);        // 0x00b75240

extern "C" u32 g_0156b430;      // 0x0156b430 = 0x40842000
extern "C" int g_01687af0;      // 0x01687af0
extern "C" int g_01687af4;      // 0x01687af4
extern "C" int g_01687af8;      // 0x01687af8

static inline void FreeValueBuffer(MenuItemValue* v) {
    void* p = v->mpVecBegin;
    if (p) {
        if (((int*)p)[-1] != 0) FUN_f47380(p);
    }
}

// ===========================================================================
//  0x00b7c1b0  HashTable::find-or-insert (one-dword key)
// ===========================================================================
// @ 0x00b7c1b0
void* HashTable::sub_b7c1b0(const void* key) {
    HashIter it;
    sub_b74800(&it, key);
    if (it.node != End()) {
        return (char*)it.node + 4;
    }
    MenuItemValue tmp;
    tmp.sub_b75820();
    ScreenValue value;
    value.mKey = *(const u32*)key;
    value.mValue.sub_b778b0(&tmp);
    HashIter ins;
    // EASTL insert(&out, &value, bool): the original materialises the bool into a byte slot
    // and the compiler passes that dword slot including its stale upper bytes, so equiv sees
    // the stack residue there; the source-level flag is simply false.
    sub_b79680(&ins, &value, 0);
    FreeValueBuffer(&value.mValue);
    FreeValueBuffer(&tmp);
    return (char*)ins.node + 4;
}

// ===========================================================================
//  SP::cSPPieMenu
// ===========================================================================
struct PieItem;
struct PieMgr;
struct PieRoot;
struct PieNotifier {
    char mUnused[0x205c];
    void sub_b75240(void* out, void* msg, int flag);    // 0x00b75240
};
struct PieTable2090 {
    char mUnused[0x3418];
};

struct ItemVec {
    void** mpBegin;             // +0x00
    void** mpEnd;               // +0x04
    void** mpCap;               // +0x08
    void** sub_b05d80(void** it);   // 0x00b05d80 erase
};

struct cSPPieMenu {
    char pad_00[0x1c];
    u8   mFlags1c;              // +0x1c
    char pad_1d[0x20 - 0x1d];
    unsigned b0 : 1;            // +0x20 bit 0
    unsigned b1 : 1;
    unsigned b2 : 1;            // +0x20 bit 2
    unsigned b3 : 1;
    unsigned    : 28;
    char pad_24[0x34 - 0x24];
    PieNotifier  mNotifier34;   // +0x34
    PieTable2090 mTable2090;    // +0x2090
    HashTable mMap54a8;         // +0x54a8
    HashTable mMap54c8;         // +0x54c8
    HashTable mMap54e8;         // +0x54e8
    char pad_5508[0x55a0 - 0x5508];
    int  mField55a0;            // +0x55a0
    ItemVec mItems;             // +0x55a4

    void sub_b77aa0();                                  // 0x00b77aa0
    void sub_b7a710();                                  // 0x00b7a710
    int  sub_b7c290(cSpatialObject* obj, void* res);    // 0x00b7c290
    void* sub_b7c360(cSpatialObject* obj, void* res);   // 0x00b7c360
    void* sub_b7c480(void* model);                      // 0x00b7c480
    void sub_b7bd50(int a, int b);                      // 0x00b7bd50
    bool sub_b78880(void* value, void* obj, void* res, int flag); // 0x00b78880
    void SetSomething(int value);                       // 0x00b7c160
};

struct PieMgr {
    char  mPad00[0x24];
    void* mpBegin24;            // +0x24
    void* mpEnd28;              // +0x28
    int   sub_703d50(float f, void* pos, void* item);   // 0x00703d50
};
struct PieRoot {
    char    mPad[0x55a4];
    PieMgr* mpPieMgr55a4;       // +0x55a4
};
struct RefSlot {
    void* mpObject;             // +0x00
    void  sub_478db0(void* obj);    // 0x00478db0
};

struct PieItem {
    void** mpVtbl;              // +0x00
    char   pad_04[0x38 - 0x04];
    Vec3   mIds;                // +0x38
    float  mRadius;             // +0x44
    float  mF48;                // +0x48
    float  mF4c;                // +0x4c
    int    mF50;                // +0x50
    void*  mpF54;               // +0x54
    int    mF58;                // +0x58
    int    mF5c;                // +0x5c
    int    mF60;                // +0x60
    int    mF64;                // +0x64
    float  mF68;                // +0x68
    int    mF6c;                // +0x6c
    RefSlot mSlot70;            // +0x70
    int    mF74;                // +0x74
    void*  mpF78;               // +0x78
    int    mF7c;                // +0x7c
    int    mF80;                // +0x80
    int    mF84;                // +0x84
    int    mF88;                // +0x88
};

struct PieNotifyMsg {
    int   mType;                // +0x00
    void* mpUnk;                // +0x04
    void* mpItem;               // +0x08
};

struct SpawnerBase {            // the object owning `this - 4`
    void sub_b77b60(void* table, u32 a, u32 b);   // 0x00b77b60
    void sub_b7a880();                            // 0x00b7a880
    PieItem* sub_b74370();                        // 0x00b74370
};

// Model object stored in the pie menu's item vector.
struct PieObject {
    void*  mpIface;             // +0x00
    u32    mFlags;              // +0x04
    char   pad_08[0x0c - 0x08];
    Vec3   mVecA;               // +0x0c
    char   pad_18[0x34 - 0x18];
    u32    mFlags34;            // +0x34
    char   pad_38[0x40 - 0x38];
    int    mnRefCount;          // +0x40
    char   pad_44[0x58 - 0x44];
    float  mF58;                // +0x58
    char   pad_5c[0x60 - 0x5c];
    int    mF60;                // +0x60
    char   pad_64[0x6c - 0x64];
    u32    mKey6c;              // +0x6c
    union {
        void* mpTarget70;       // +0x70 (kind 4: the spatial object)
        float mPosA[3];         // +0x70
    };
    float  mPosB[3];            // +0x7c
    int    mKind88;             // +0x88
    char   pad_8c[0x90 - 0x8c];
    void*  mpPropertyList;      // +0x90
    void*  sub_b73e70();        // 0x00b73e70
};

extern "C" void* __cdecl sub_67dd80();      // 0x0067dd80 SP::ModelManager
extern "C" PieRoot* __cdecl sub_b3d3c0();   // 0x00b3d3c0

// @ 0x00b7c160
void cSPPieMenu::SetSomething(int value) {
    if (b2) {
        b2 = 0;
        mField55a0 = 0;
        sub_b77aa0();
    }
    if (b0) b2 = 1;
    else    b2 = 0;
    if (b2) {
        mField55a0 = value;
        sub_b7a710();
    }
}

// ===========================================================================
//  0x00b7c790  cdecl helper (release + game-input forward)
// ===========================================================================
// @ 0x00b7c790
void __cdecl cSPPieMenu_ReleaseAndInput(int param) {
    cSPUIPieMenuItemWinProc* p = g_pPieWinProc;
    if (p) Vv0(p, 0x00);
    void* gm = SP_GameInputManager();
    Vv2(gm, 0x64, param, 1);
    if (g_pPieWinProc && p == g_pPieWinProc) {
        p->Hide();
        Vv0(g_pPieWinProc, 0x24);
        cSPUIPieMenuItemWinProc* q = g_pPieWinProc;
        if (q) {
            g_pPieWinProc = 0;
            Vv0(q, 0x04);
        }
        g_bPieMenuVisible = 0;
    }
    if (p) Vv0(p, 0x04);
}

// ===========================================================================
//  0x00b7c890  button vector: set text color for matching item id
// ===========================================================================
struct PieButton {
    char pad_00[0x10];
    int  mId;                    // +0x10
    int  mColor;                 // +0x14
};
struct ButtonVec {
    PieButton* mpBegin;          // +0x00
    PieButton* mpEnd;            // +0x04
    void SetItemTextColor(int id, int color);   // 0x00b7c890
};

extern "C" void __cdecl cSPUIPieMenu_SetItemTextColor(int id, int color);

// @ 0x00b7c890
void ButtonVec::SetItemTextColor(int id, int color) {
    PieButton* it = mpBegin;
    if (it != mpEnd) {
        do {
            if (it->mId == id) {
                it->mColor = color;
                if (g_pPieWinProc) {
                    cSPUIPieMenu_SetItemTextColor(id, color);
                }
                return;
            }
            it = (PieButton*)((char*)it + 0x18);
        } while (it != mpEnd);
    }
}

// ===========================================================================
//  Simulator::cPieMenuScreenPosition
// ===========================================================================
struct cPieMenuScreenPosition {
    void** vftable;              // +0x00
    void** vftable2;             // +0x04
    int    mField8;              // +0x08
    cSpatialObject* mpObject;    // +0x0c
    float  mBaseDistance;        // +0x10

    cPieMenuScreenPosition(cSpatialObject* pObject);
    bool GetPosition(float* outX, float* outY);   // 0x00b7cb00
    bool ShouldBeVisible();                        // 0x00b7cb20
};

extern "C" __declspec(noinline) bool __cdecl PieMenu_ScreenPosition_GetPosition(
    cSpatialObject* obj, float* outX, float* outY);

// @ 0x00b7cb00
bool cPieMenuScreenPosition::GetPosition(float* outX, float* outY) {
    cSpatialObject* obj = mpObject;
    return PieMenu_ScreenPosition_GetPosition(obj, outX, outY);
}

// ===========================================================================
//  0x00b7c8e0  compute screen position of a spatial object
// ===========================================================================
// @ 0x00b7c8e0
bool __cdecl PieMenu_ScreenPosition_GetPosition(cSpatialObject* obj,
                                                float* outX, float* outY) {
    if (obj) {
        float bounds[6];
        float* r = (float*)VRet1(obj, 0x6c, bounds);
        float center[3];
        center[0] = (r[0] + r[3]) * 0.5f;
        center[1] = (r[4] + r[1]) * 0.5f;
        center[2] = (r[5] + r[2]) * 0.5f;
        void* app = SP_App();
        float proj[3];
        void* camera = VRet(app, 0x58);
        ((S7c4180*)camera)->sub_7c4180(proj, center);
        float area[4];
        sub_805ea0(area);
        float cx = ((proj[0] + 1.0f) * area[2]) * 0.5f;
        float cy = ((1.0f - proj[1]) * area[3]) * 0.5f;
        *outX = cx;
        *outY = cy;
        return true;
    }
    return false;
}

// ===========================================================================
//  0x00b7cb20  Simulator::cPieMenuScreenPosition::ShouldBeVisible
// ===========================================================================
extern "C" void* __cdecl SP_PlanetModel();

// @ 0x00b7cb20
bool cPieMenuScreenPosition::ShouldBeVisible() {
    PlanetModel* planet = (PlanetModel*)SP_PlanetModel();
    if (!mpObject || !planet) return false;
    float* pos = (float*)VRet(mpObject, 0x2c);
    float px = pos[0], py = pos[1], pz = pos[2];
    VRetF(mpObject, 0x70);
    float f8 = planet->GetRadius();
    ((OtherObj*)mpObject)->SomeFloat();
    void* app = SP_App();
    Viewer* viewer = (Viewer*)VRet(app, 0x58);
    float cam[3];
    viewer->GetCameraLocationInfo(cam, 0, 0, 0);
    float dx = cam[0] - px, dy = cam[1] - py, dz = cam[2] - pz;
    float dist = (float)sqrt((double)(dx * dx + dy * dy + dz * dz));
    if (dist < mBaseDistance) mBaseDistance = dist;
    if (dist < mBaseDistance * 6.0f && dist < f8 * 2.0f) return true;
    return false;
}

// ===========================================================================
//  0x00b7c290  cSPPieMenu::AddItem - get or create the value for an object
//  (hash at +0x54c8, key = the spatial object pointer)
// ===========================================================================
// @ 0x00b7c290
int cSPPieMenu::sub_b7c290(cSpatialObject* obj, void* res) {
    if (!obj || !obj->mpPropertyList) return 0;
    HashTable* map = &mMap54c8;
    HashIter it;
    map->sub_b74800(&it, &obj);
    if (it.node != map->End()) {
        return (int)((char*)it.node + 4);
    }
    MenuItemValue* value = (MenuItemValue*)map->sub_b7c1b0(&obj);
    value->mRadius = obj->mXf.mF10;
    if (!sub_b78880(value, obj, res, 1)) {
        HashIter it2;
        map->sub_b74800(&it2, &obj);
        HashIter dummy;
        map->sub_b766b0(&dummy, it2);
        return 0;
    }
    return (int)value;
}

// ===========================================================================
//  0x00b7c360  cSPPieMenu::get-or-create with transform copy (hash +0x54e8)
// ===========================================================================
// @ 0x00b7c360
void* cSPPieMenu::sub_b7c360(cSpatialObject* obj, void* res) {
    if (!obj || !(obj->mFlags & 0x4000) || !obj->mpPropertyList || !res) return 0;
    float x = obj->mXf.mF10;
    HashTable* map = &mMap54e8;
    HashIter it;
    map->sub_b74800(&it, &obj);
    if (it.node != map->End()) {
        void* node = it.node;
        if (!sub_41dd30((char*)node + 8, &obj->mXf.mVec04) &&
            NodeValue(node)->mXf.mF10 == x &&
            !sub_41dd90((char*)node + 0x18, &obj->mXf.mVec14)) {
            return NodeValue(node);
        }
    }
    MenuItemValue* value = (MenuItemValue*)map->sub_b7c1b0(&obj);
    value->mRadius = x * 1.05f;
    ((CTransformAssign*)value)->Assign(&obj->mXf);
    if (!sub_b78880(value, obj, res, 1)) {
        map->sub_b76620(&obj);
    }
    return value;
}

// ===========================================================================
//  0x00b7c480  cSPPieMenu::CreateItemFromModel
//  (inlined lower_bound over the 3-dword-key map at +0x54a8, then insertion)
// ===========================================================================
// @ 0x00b7c480
void* cSPPieMenu::sub_b7c480(void* model_) {
    PieObject* model = (PieObject*)model_;
    if (!model) return 0;
    if (model->mKind88 == 4) {
        void* mm = sub_67dd80();
        void* resource = VRet1(mm, 0x1c, (void*)0x3fbae24);
        return (void*)sub_b7c290((cSpatialObject*)model->mpTarget70, resource);
    }
    float height = *(float*)((char*)model->sub_b73e70() + 0x10);
    if (model->mFlags34 & 4) height = 1.0f;
    ModelKey key;
    key.k0 = model->mKey6c;
    key.k1 = 0;
    key.k2 = g_0156b430;
    HashTable* map = &mMap54a8;
    HashIter4 it;
    map->sub_b74740(&it, &key);
    void* node = it.node;
    char** bucket = (char**)it.bucket;
    void* last = it.last;
    while (node != last) {
        if (AbsF(((MenuItemValue*)((char*)node + 4))->mRadius - height)
            <= 1.52587890625e-05f) {
            return (char*)node + 0xc;
        }
        node = *(void**)((char*)node + 0xc70);
        while (!node) {
            node = *++bucket;
        }
    }
    void* mm = sub_67dd80();
    void* factory = VRet1(mm, 0x1c, (void*)0xeb9968);
    if (factory) Vv0(factory, 0);
    RefObject* m2 = (RefObject*)VRet3(factory, 0xc, (void*)(size_t)key.k0,
                                      (void*)(size_t)key.k2, 0);
    MenuItemValue* val = 0;
    if (m2) {
        m2->mnRefCount += 1;
        MenuItemValue tmp;
        ModelValue pv;
        tmp.sub_b75820();
        pv.mKey = key;
        pv.mValue.sub_b778b0(&tmp);
        HashIter ins;
        map->sub_b795c0(&ins, &pv, 0);
        FreeValueBuffer(&pv.mValue);
        FreeValueBuffer(&tmp);
        val = (MenuItemValue*)((char*)ins.node + 0xc);
        val->mRadius = height;
        if (!sub_b78880(val, m2, factory, 0)) {
            HashIter dummy;
            map->sub_b76580(&dummy, ins);
            val = 0;
        }
        RefIfaceCall(m2, 0x16c, 0);
        RefRelease(m2);
    }
    Vv0(factory, 4);
    return val;
}

// ===========================================================================
//  0x00b7bd50  cSPPieMenu::UpdateItems - refresh the visible pie items
// ===========================================================================
// @ 0x00b7bd50
void cSPPieMenu::sub_b7bd50(int a, int b) {
    (void)a; (void)b;
    SpawnerBase* base = (SpawnerBase*)((char*)this - 4);
    base->sub_b77b60(&mTable2090, 0, 0);
    if (mFlags1c & 4) base->sub_b7a880();

    void** it = mItems.mpBegin;
    if (it == mItems.mpEnd) return;
    do {
        PieObject* m = (PieObject*)*it;
        if (!m) {
            void** end = mItems.mpEnd;
            if (it + 1 < end) sub_5f4e10(it + 1, end, it);
            end -= 1;
            mItems.mpEnd = end;
            RefObject* tail = (RefObject*)*end;
            if (tail) RefRelease(tail);
        } else if (!(m->mFlags & 0x4000) || (m->mFlags & 0x40000)) {
            it += 1;
        } else {
            PropertyList* pl = (PropertyList*)m->mpPropertyList;
            bool bErase = false;
            if (pl) {
                bool bFirst = pl->GetBoolProperty(0x3f6d22a);
                bool bSecond = pl->GetBoolProperty(0x37575e5);
                bErase = !bSecond || bFirst;
            }
            if (!bErase) {
                Vec3 delta;
                delta.f[0] = m->mPosB[0] - m->mPosA[0];
                delta.f[1] = m->mPosB[1] - m->mPosA[1];
                delta.f[2] = m->mPosB[2] - m->mPosA[2];
                float radius = 3.4028234663852886e+38f;
                Property* p;
                if (m->mpPropertyList &&
                    pl->GetProperty(0x254cf89, &p) && p->mType == 0xd) {
                    radius = *p->sub_41ea70();
                }
                float halfDiag = SqrtF(delta.f[0] * delta.f[0] +
                                       delta.f[1] * delta.f[1]) * 0.5f;
                if (radius > halfDiag) radius = halfDiag;
                float f48 = radius;
                if (m->mpPropertyList &&
                    pl->GetProperty(0x254cf8f, &p) && p->mType == 0xd) {
                    f48 = *p->sub_41ea70();
                }
                float f4c = delta.f[2];
                if (m->mpPropertyList &&
                    pl->GetProperty(0x254cf97, &p) && p->mType == 0xd) {
                    f4c = *p->sub_41ea70();
                }
                PieItem* item = base->sub_b74370();
                if (item) Vv0(item, 0);
                Vv0(item, 0x54);
                item->mIds = m->mVecA;
                item->mRadius = radius;
                item->mF48 = f48;
                item->mF4c = f4c;
                item->mF68 = m->mF58;
                item->mSlot70.sub_478db0(m);
                item->mF6c = m->mF60;
                item->mF74 = 0;
                RefObject* old = (RefObject*)item->mpF78;
                if (old) {
                    item->mpF78 = 0;
                    RefRelease(old);
                }
                item->mF7c = g_01687af0;
                item->mF80 = g_01687af4;
                item->mF84 = g_01687af8;
                item->mF5c = 0;
                item->mF50 = 0;
                item->mF58 = 0;
                void* p54 = item->mpF54;
                if (p54) {
                    item->mpF54 = 0;
                    Vv0(p54, 0x38);
                }
                item->mF88 = 4;
                PieMgr* mgr = sub_b3d3c0()->mpPieMgr55a4;
                if (mgr && item->mF64 < 0 && mgr->mpBegin24 != mgr->mpEnd28) {
                    item->mF64 = mgr->sub_703d50(item->mF48, &item->mIds, item);
                }
                PieNotifyMsg msg;
                msg.mType = 1;
                msg.mpUnk = 0;
                msg.mpItem = item;
                Vv0(item, 0);
                void* out = 0;
                mNotifier34.sub_b75240(&out, &msg, 0);
                if (msg.mpItem) Vv0(msg.mpItem, 4);
                Vv0(item, 4);
            }
            it = mItems.sub_b05d80(it);
            continue;
        }
    } while (it != mItems.mpEnd);
}

// ===========================================================================
//  0x00b7c9c0  Simulator::cPieMenuScreenPosition::cPieMenuScreenPosition
// ===========================================================================
// @ 0x00b7c9c0
cPieMenuScreenPosition::cPieMenuScreenPosition(cSpatialObject* pObject) {
    vftable2 = (void**)0x13ec458;
    mField8 = 0;
    vftable = (void**)0x14651bc;
    vftable2 = (void**)0x14651ac;
    mpObject = pObject;
    if (mpObject) Vv0(mpObject, 0xbc);
    mBaseDistance = 0.0f;
    if (mpObject) {
        float* pos = (float*)VRet(mpObject, 0x2c);
        float px = pos[0], py = pos[1], pz = pos[2];
        void* app = SP_App();
        Viewer* viewer = (Viewer*)VRet(app, 0x58);
        float cam[3];
        viewer->GetCameraLocationInfo(cam, 0, 0, 0);
        float dx = cam[0] - px, dy = cam[1] - py, dz = cam[2] - pz;
        double sum = (double)dx * dx + (double)dy * dy + (double)dz * dz;
        __m128d sv = _mm_sqrt_pd(_mm_load_sd(&sum));
        mBaseDistance = (float)_mm_cvtsd_f64(sv);
    }
}
