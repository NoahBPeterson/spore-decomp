// Slice s00b7bd50 (batch bfs1 #35).  SP::cSPPieMenu and related helpers.
// 32-bit MSVC 2008 SP1, mostly /O2 /MD /Gy /EHsc /TP /arch:SSE2.

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern "C" double sqrt(double);

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
struct cSPUIPieMenuItemWinProc {
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
// ---------------------------------------------------------------------------
struct cSpatialObject {
    void** vftable;             // +0x00
    u32    mFlags;              // +0x04
    char   pad_08[0xc - 0x08];
    int    mId;                 // +0x0c
    int    mId2;                // +0x10
    int    mId3;                // +0x14
    float  mX;                  // +0x18
    char   pad_1c[0x90 - 0x1c];
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
//  cSpatialObject / Property helpers (used by several functions below)
// ===========================================================================
struct Property {
    char pad_00[0x12];
    u16  mType;                 // +0x12
    char pad_14[0x14 - 0x12];
};
struct PropertyList {
    void* GetProperty(u32 key) {
        void* out = 0;
        ((bool(__thiscall*)(void*, u32, void**))(*(void***)this)[0x24 / 4])(this, key, &out);
        return out;
    }
    bool HasProperty(u32 key) { return GetProperty(key) != 0; }
    float GetFloatProperty(u32 key) {
        Property* p = (Property*)GetProperty(key);
        return (p && p->mType == 0xd) ? *(float*)((char*)p + 8) : 0.0f;
    }
    bool GetBoolProperty(u32 key) {
        Property* p = (Property*)GetProperty(key);
        return (p && p->mType == 1) ? *(u8*)((char*)p + 8) != 0 : false;
    }
    bool* GetKeyArrayProperty(u32 key) {
        Property* p = (Property*)GetProperty(key);
        return (p && p->mType == 1) ? (bool*)((char*)p + 8) : 0;
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

// Ref-counted model entry stored in cSPPieMenu's item vector.
struct RefObj {
    void** vftable;              // +0x00
    u32    mFlags;               // +0x04
    char   pad_08[0x40 - 0x08];
    int    mnRefCount;           // +0x40
    void Release() {
        if (mnRefCount > 1) --mnRefCount;
        else ((void(__thiscall*)(RefObj*, u32))(*(void***)this)[0x170 / 4])(this, mFlags >> 31);
    }
};

// ===========================================================================
//  SP::cSPPieMenu (retail, offset-preserving stub)
// ===========================================================================
struct cSPPieMenu {
    char pad_00[0x20];
    unsigned b0 : 1;             // +0x20 bit 0
    unsigned b1 : 1;
    unsigned b2 : 1;             // +0x20 bit 2
    unsigned b3 : 1;
    unsigned    : 28;
    char pad_24[0x55a0 - 0x24];
    int  mField55a0;             // +0x55a0
    RefObj** mpModelBegin;       // +0x55a4
    RefObj** mpModelEnd;         // +0x55a8

    void sub_b77aa0();
    void sub_b7a710();
    int  sub_b7c290(cSpatialObject* obj, void* arg2);      // 0x00b7c290
    void* sub_b7c360(cSpatialObject* obj, void* arg2);     // 0x00b7c360
    void* sub_b7c480(void* model);                          // 0x00b7c480
    void  sub_b7bd50(int a, int b);                         // 0x00b7bd50
    void SetSomething(int value);   // 0x00b7c160
};

extern "C" void* __cdecl SP_ModelManager();
extern "C" void* __cdecl sub_b73e70(void* p);
extern "C" void  __cdecl sub_b3d3c0();
extern "C" void  __cdecl sub_b3d350();
extern "C" void  __cdecl sub_b3d250();
extern "C" void  __cdecl sub_537dc0(void* a, void* b);
extern "C" void  __cdecl sub_5f4e10(void* a, void* b, void* c);
extern "C" void  __cdecl sub_b75240(void* a, void* b, int c);
extern "C" void  __cdecl sub_b77b60(void* ctx, int a, int b, void* p);
extern "C" void  __cdecl sub_b7a880(void* ctx);
extern "C" void* __cdecl sub_b74370(void* ctx);
extern "C" void  __cdecl sub_478db0(void* a);
extern "C" int   __cdecl sub_703d50(void* a, void* b, void* c);
extern "C" void* __cdecl sub_b05d80(void* a);

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
    if (!obj) return false;
    float box[8];
    float* r = (float*)VRet1(obj, 0x6c, box);
    float x = (r[0] + r[3]) * 0.5f;
    float y = (r[1] + r[4]) * 0.5f;
    float z = (r[2] + r[5]) * 0.5f;
    void* app = SP_App();
    void* viewer = (void*)VRet(app, 0x58);
    float screen[4];
    VRet1(viewer, 0x58, &screen[0]);   // viewer->something(&local)
    (void)z;
    (void)x; (void)y;
    return true;
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
//  Hash table used by cSPPieMenu at +0x54a8/+0x54c8/+0x54e8
// ===========================================================================
struct HashTable {
    char   pad_00[4];
    void** ppBuckets;            // +0x04
    u32    nBucketCount;         // +0x08
    void*  End() { return ppBuckets[nBucketCount]; }

    void  Find(void* key, void* out);        // 0x00b74800
    void  FindLowerBound(void* key, void* out); // 0x00b74740
    void* LookupOrAdd(void* key);            // 0x00b7c1b0
    void  Erase1(void* it);                  // 0x00b766b0
    void  Erase2(void* it);                  // 0x00b76620
};

extern "C" bool __cdecl sub_41dd30(void* a, void* b);
extern "C" bool __cdecl sub_41dd90(void* a, void* b);
extern "C" bool __cdecl sub_b78880(void* a, void* b, void* c, int d);
extern "C" void __cdecl sub_b76580(void* a, void* b, void* c);
extern "C" void __cdecl sub_b75820(void* a);
extern "C" void __cdecl sub_b778b0(void* a);
extern "C" void __cdecl sub_b79680(void* a, void* b, int c);
extern "C" void __cdecl operator_delete(void* p);

// ===========================================================================
//  0x00b7c1b0  HashTable::LookupOrAdd
//  (inlined EASTL hashtable find + node construction with a wide-string key)
// ===========================================================================
// @ 0x00b7c1b0
void* HashTable::LookupOrAdd(void* key) {
    u32 local[3];
    Find(key, local);
    if (local[0] != (u32)End()) {
        return (void*)(local[0] + 4);
    }
    char tmp[0x40];
    sub_b75820(&tmp);
    u32 k = *(u32*)key;
    sub_b778b0(&k);
    int flag = 0;
    sub_b79680(local, &k, flag);
    return (void*)(local[0] + 4);
}

// ===========================================================================
//  0x00b7c290  cSPPieMenu::AddItem / get-or-create (hash at +0x54c8)
// ===========================================================================
// @ 0x00b7c290
int cSPPieMenu::sub_b7c290(cSpatialObject* obj, void* arg2) {
    if (!obj || !obj->mpPropertyList) return 0;
    float key = *(float*)((char*)obj + 0x18);
    HashTable* map = (HashTable*)((char*)this + 0x54c8);
    u32 local[2];
    map->Find(&key, local);
    if (local[0] != (u32)map->End()) {
        return local[0] + 4;
    }
    void* node = (void*)map->LookupOrAdd(&obj);
    *(float*)((char*)node + 0x38) = key;
    if (!sub_b78880(node, obj, arg2, 1)) {
        map->Find(&key, local);
        map->Erase1((void*)local);
        return 0;
    }
    return (int)node;
}

// ===========================================================================
//  0x00b7c360  cSPPieMenu::get-or-create with transform copy (hash +0x54e8)
// ===========================================================================
// @ 0x00b7c360
void* cSPPieMenu::sub_b7c360(cSpatialObject* obj, void* arg2) {
    if (!obj || !(obj->mFlags & (1u << 14)) || !obj->mpPropertyList || !arg2) return 0;
    float key = *(float*)((char*)obj + 0x18);
    HashTable* map = (HashTable*)((char*)this + 0x54e8);
    u32 local[2];
    map->Find(&key, local);
    if (local[0] != (u32)map->End()) {
        if (!sub_41dd30((void*)(local[0] + 8), (char*)obj + 0xc) &&
            *(float*)(local[0] + 0x14) == key &&
            !sub_41dd90((void*)(local[0] + 0x18), (char*)obj + 0x1c)) {
            return (void*)(local[0] + 4);
        }
    }
    void* node = (void*)map->LookupOrAdd(&obj);
    *(float*)((char*)node + 0x38) = key * 1.05f;
    sub_537dc0((char*)node, (char*)obj + 8);       // cSPTransform::operator=
    if (!sub_b78880(node, obj, arg2, 1)) {
        map->Erase2(&obj);
    }
    return node;
}

// ===========================================================================
//  0x00b7c480  cSPPieMenu::CreateItemFromModel
//  (inlined hash lookups + EASTL vector erase; large stack frame)
// ===========================================================================
// @ 0x00b7c480
void* cSPPieMenu::sub_b7c480(void* model) {
    char pad[0x18fc];
    (void)pad;
    if (!model) return 0;
    if (*(int*)((char*)model + 0x88) == 4) {
        void* mm = SP_ModelManager();
        void* res = VRet1(mm, 0x1c, (void*)0x3fbae24);
        return (void*)sub_b7c290((cSpatialObject*)model, res);
    }
    char* pm = (char*)sub_b73e70(model);
    float f = *(float*)(pm + 0x10);
    if (*(u32*)((char*)model + 0x34) & 4) f = 1.0f;
    // ... (see nonmatching.txt) ...
    (void)f;
    return 0;
}

// ===========================================================================
//  0x00b7bd50  cSPPieMenu::UpdateItems / refresh visible models
//  (large /Od-ish loop over mpModelBegin..mpModelEnd with inlined helpers)
// ===========================================================================
// @ 0x00b7bd50
void cSPPieMenu::sub_b7bd50(int a, int b) {
    (void)a; (void)b;
    char* base = (char*)this - 4;
    sub_b77b60(base, 0, 0, (char*)this + 0x2090);
    if (*(u8*)((char*)this + 0x1c) & 4) sub_b7a880(base);

    RefObj** it = mpModelBegin;
    RefObj** end = mpModelEnd;
    if (it == end) return;
    do {
        RefObj* m = *it;
        if (!m) {
            if (it + 1 < mpModelEnd) {
                sub_5f4e10(it + 1, mpModelEnd, it);
            }
            mpModelEnd = mpModelEnd - 1;
            RefObj* tail = mpModelEnd[-1];
            if (tail) tail->Release();
        } else if (!(m->mFlags & (1u << 14)) || (m->mFlags & (1u << 18))) {
            ++it;
        } else {
            // full item path (property reads, model creation, ref-counting)
            PropertyList* pl = (PropertyList*)((cSpatialObject*)m)->mpPropertyList;
            bool bA = false, bB = false;
            if (pl) {
                if (pl->HasProperty(0x3f6d22a)) bA = pl->GetBoolProperty(0x3f6d22a);
                if (pl->HasProperty(0x37575e5) && pl->GetBoolProperty(0x37575e5)) bB = true;
            }
            if (!bA && !bB) {
                (void)sub_b74370(base);
            }
            if (it + 1 != mpModelEnd) { /* ... */ }
            it = (RefObj**)sub_b05d80((void*)it);
        }
    } while (it != mpModelEnd);
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
        mBaseDistance = (float)sqrt((double)(dx * dx + dy * dy + dz * dz));
    }
}
