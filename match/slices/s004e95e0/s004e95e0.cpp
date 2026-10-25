// w1g1 slice s004e95e0 -- editor "functional match" property collectors.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (frame pointer, no C++ EH,
// x87 for float args, SSE for float copies).  Stack-slot holes are the unused
// /Od locals left by the original's inlined helpers; they are reproduced with
// unused named locals.

typedef unsigned int uint32_t;
typedef unsigned int size_t;

struct DeclareParam { int key; int a; int b; };

struct Manager {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20(); virtual void m21();
    virtual void* Find(int a, int b); // +0x58
};

struct Vec { void push_back(const DeclareParam& v); };

// ---- external helpers (relocations are masked) ------------------------------
void* GetMgr401010();                                            // 0x00401010
void* GetManager67dcd0();                                        // 0x0067dcd0
bool GetPropertyAsKey(void* holder, int key, void* out);         // 0x006a1250
bool GetPropertyAsKeyInstance(void* holder, int key, int* out);  // 0x006a12a0
bool GetPropertyAsKeyArray(void* holder, int key, int* count, void** array); // 0x006a0ae0
void* InterfaceCast(void** ref);                                 // 0x00421eb0-ish
void* Alloc(uint32_t size, const char* name, int, int, int, int); // 0x00f473a0
void* operator new(size_t size, const char* name, int, int, int, int); // 0x00f473a0

// Refcounted-object vtable shape used by the palette helpers (+4 AddRef, +8 Release).
struct Iface {
    virtual void v00();
    virtual void AddRef();   // +4
    virtual void Release();  // +8
};

namespace EA { namespace ResourceMan {
struct Key { uint32_t instance; uint32_t type; uint32_t group; };   // 0xc bytes
}}

// ---------------------------------------------------------------------------
// Vector / matrix math shared with the 0x41dc10 family of helpers.  The type
// names are the original's (global Vector3, cSPVector3, cSPVector3R,
// cSPMatrix3) so the operator spellings below mangle as in the image.
// ---------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;
};

struct cSPVector3 : Vector3 { };

// Homogeneous result of a vector/matrix product (xyz plus w).
struct cSPVector3R : Vector3 {
    float w;
};

struct cSPMatrix3 {
    Vector3 mRow[3];                    // +0x00 / +0x0c / +0x18
};

Vector3 operator*(const Vector3& v, const float& scale);            // 0x0041dca0
Vector3 operator+(const Vector3& a, const Vector3& b);             // 0x0041dc10
cSPVector3R operator*(const cSPVector3& v, const cSPMatrix3& m);   // 0x0041daf0
cSPMatrix3 operator*(const cSPMatrix3& a, const cSPMatrix3& b);    // 0x0041de20 (_Unchecked_idl0)
Vector3* BuildBasisMatrix(cSPMatrix3* pMatrix, Vector3 a, Vector3 b, Vector3 c); // 0x00499f10
// Scratch block the world-transform builder fills: handed a pointer, it writes a
// 36-byte matrix at +0x14 of it.
struct cWorldSlot {
    uint32_t pad00[0x14 / 4];           // +0x00 .. +0x13
    cSPMatrix3 mMatrix;                 // +0x14 .. +0x37
    uint32_t pad38[2];                  // +0x38 .. +0x3f
};

void StoreRows(cWorldSlot* pMatrix, Vector3* pValues);             // 0x0049ef80 (3 rows)

// Objects the basis source points at.
struct ICorners {                       // provider behind the basis source's +0x4
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void GetCorners(Vector3* pCorners);   // +0xc (4 vectors)
};

struct cTransformSource {               // owner behind the basis source's +0x0
    uint32_t pad00[4];                  // +0x00 .. +0x0f
    void* mpPrimary;                    // +0x10
    uint32_t pad14;                     // +0x14
    void* mpSecondary;                  // +0x18
    uint32_t pad1c[0x1d8 / 4 - 0x7];    // +0x1c .. +0x1d7
    float mVectorScale;                 // +0x1d8
    cWorldSlot* ComposeInto(cWorldSlot* pOut);    // 0x004363d0 (thiscall)
};

// Palette double-buffered iterator helper (0x005c7b80).
namespace SP {

struct cSPPalette : Iface {
    uint32_t mData[0x40 / 4 - 1];       // +0x04 .. +0x3c (sizeof 0x40)
    cSPPalette();                       // 0x005c5e30
    bool Init(const EA::ResourceMan::Key& key, unsigned int a, unsigned int b,
              unsigned int c, unsigned int d, int e, int modelType);  // 0x005c6340
};

// One palette entry: the 12-byte payload sits at +0xc.
struct cPaletteEntry {
    uint32_t pad00[3];                  // +0x00 .. +0x0b
    DeclareParam mParam;                // +0x0c
};

struct cSPPaletteCursor : Iface {
    uint32_t mData[0x20 / 4 - 1];       // +0x04 .. +0x1c (sizeof 0x20)
    cSPPaletteCursor();                 // 0x005c7b80
    void SetPalette(cSPPalette* pPalette);          // 0x005c7bc0
    cPaletteEntry* First(void*, int*, int*, int*);  // 0x005c7e80
    cPaletteEntry* Next(void*, int*, int*, int*);   // 0x005c7e20
};

// The editor model-type holder the basis builder is called on.
struct cBasisSource {
    cTransformSource* mpObject;         // +0x00
    ICorners* mpProvider;               // +0x04
    cSPVector3 mOrigin;                 // +0x08
    Vector3 mScale;                     // +0x14
    cSPMatrix3 mBasis;                  // +0x20
    void BuildBasis(Vector3* pOutVector, cSPMatrix3* pOutMatrix);   // 0x004e95e0
};

}   // namespace SP

struct ResourceMgr {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void FindResource(void* key, void** out, int, int, int, int); // +0xc
};

struct PaletteMgr {
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
    virtual void GetPalette(int type, void* a, void* b); // +0x2c
};

// Property manager query used by the palette enumerator.
struct PropertyListIface {              // the property list's own vtable: +4 release
    virtual void v00();
    virtual void Release();             // +4
};

struct AutoRefCountPropertyList {       // EA::AutoRefCount<PropertyList> handle
    PropertyListIface* mpObject;        // +0x0
    AutoRefCountPropertyList() : mpObject(0) { }
    void** AsPPVoidParam();             // 0x0041d870
};

struct PropertyManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual void GetPropertyList(int typeId, void* pUser, void** ppOut);  // +0x2c
};

namespace SP {
PropertyManager* PropertyManager();      // 0x0067de30
namespace Editor { int GetConfigFromModelType(int typeId); }   // 0x00432f10
}

extern void* g_pPropertyRequest;         // 0x015daa00

extern DeclareParam g_15dacc8;
extern DeclareParam g_15dabcc;
void FUN_004e9ca0(Vec* out);

// ===========================================================================
// @ 0x004e9c40
// ===========================================================================
void UpgradeParts(DeclareParam param, Vec* out)
{
    int hi;                       // ebp-0x14  manager
    int v9;                       // ebp-0x10  hole
    int key;                      // ebp-0xc   hole
    const int n28 = 0xf45f59d7;   // ebp-8     key constant
    int p30;                      // ebp-4     holder
    hi = (int)GetMgr401010();
    p30 = (int)((Manager*)hi)->Find(param.key, param.b);
    if (p30 != 0) {
        if (GetPropertyAsKey((void*)p30, 0xf45f59d7, &param))
            out->push_back(param);
    }
}

// ===========================================================================
// @ 0x004e9b40
// ===========================================================================
void AddPaintKeys(DeclareParam param, Vec* out)
{
    int mid, elem, n17, p9;
    int owner, v8, n6, t33;
    void* p40;
    void* s;
    int n5;
    void* t2;
    int t23;
    int p1;
    n17 = 0x2196ad5;
    elem = 0xbd110a25;
    mid = 0xdee3d8a8;
    p9 = 0xb0e066a7;
    p40 = GetMgr401010();
    s = ((Manager*)p40)->Find(param.key, param.b);
    if (s != 0) {
        n5 = 0;
        if (GetPropertyAsKeyInstance(s, 0x2196ad5, &n5)) {
            if (n5 == 0xbd110a25) {
                out->push_back(param);
            } else if (n5 == (int)0xdee3d8a8) {
                t23 = 0;
                if (GetPropertyAsKeyArray(s, 0xb0e066a7, &t23, &t2)) {
                    for (p1 = 0; p1 < t23; p1++) {
                        if (*(int*)((char*)t2 + p1 * 0xc) != 0)
                            out->push_back(*(DeclareParam*)((char*)t2 + p1 * 0xc));
                    }
                }
            }
        }
    }
}

// ===========================================================================
// @ 0x004ea190  (complete; not byte-exact)
// Recursively adds the declare-param entries that a model-type id maps to.
// ===========================================================================
void FUN_004ea190(int id, Vec* out, int flag)
{
    DeclareParam d;
    switch (id) {
    case 0xdfad9f51:
        d.key = (int)0xc15cfa84;
        d.a = 0;
        d.b = (int)(0x40000000u | (0x61u << 16) | (0x60u << 8));
        out->push_back(d);
        break;
    case 0x372e2c04:
    case 0x9ea3031a:
    case 0xccc35c46:
    case 0x4178b8e8:
    case 0x65672ade:
        d.key = 0xd05c53a3;
        d.a = 0;
        d.b = (int)(0x40000000u | (0x62u << 16) | (0x60u << 8));
        out->push_back(d);
        out->push_back(g_15dacc8);
        out->push_back(g_15dabcc);
        if (flag != 0x5bf8f774)
            FUN_004e9ca0(out);
        break;
    }
}

// ===========================================================================
// @ 0x004e9950  (complete; not byte-exact)
// Walks a holder's property keys; when the "children" key is present it
// recurses into the editor resource's sub-objects.
// ===========================================================================
void Collect9950(DeclareParam param, Vec* out)
{
    void* mgr = GetMgr401010();
    void* holder = ((Manager*)mgr)->Find(param.key, param.b);
    if (holder == 0)
        return;
    if (GetPropertyAsKey(holder, 0x3a3b9d21, &param))
        out->push_back(param);
    if (GetPropertyAsKey(holder, 0x18c1dbe0, &param))
        out->push_back(param);
    if (GetPropertyAsKey(holder, 0xf48eb09, &param))
        out->push_back(param);
    if (!GetPropertyAsKey(holder, 0x22e8410, &param)) {
        out->push_back(param);
    } else {
        ResourceMgr* rm = (ResourceMgr*)GetManager67dcd0();
        void* ref = 0;
        if (ref)
            ((Iface*)ref)->Release();
        rm->FindResource(&param, &ref, 0, 0, 0, 0);
        if (ref) {
            void* res = InterfaceCast(&ref);
            if (res) {
                char* vec = (char*)res + 0x98;
                int begin = *(int*)vec;
                int count = (*(int*)(vec + 4) - begin) / 0x1d8;
                for (int i = 0; i < count; i++) {
                    DeclareParam d;
                    d.key = *(int*)(begin + i * 0x1d8 + 4);
                    d.a = param.a;
                    d.b = *(int*)(begin + i * 0x1d8);
                    Collect9950(d, out);
                }
            }
        }
        if (ref)
            ((Iface*)ref)->Release();
    }
}

// ===========================================================================
// @ 0x004e9fc0  (complete; not byte-exact)
// Builds a palette for one model type and dispatches each entry to the
// AddPaintKey/UpgradeParts collector chosen by `kind`.
// ===========================================================================
void FUN_004e9fc0(const EA::ResourceMan::Key* pKey, Vec* out, int kind)
{
    SP::cSPPalette* pal = new ("Editor", 0, 0, 0, 0) SP::cSPPalette();
    if (pal != 0) {
        pal->AddRef();
        if (pal->Init(*pKey, (unsigned)-1, 0, 0, 0, 0, 0)) {
            SP::cSPPaletteCursor* it = new ("Editor", 0, 0, 0, 0) SP::cSPPaletteCursor();
            if (it != 0) {
                it->AddRef();
                it->SetPalette(pal);
                SP::cPaletteEntry* node = it->First(0, 0, 0, 0);
                while (node != 0) {
                    DeclareParam d = node->mParam;
                    if (kind == 0)
                        Collect9950(d, out);
                    else if (kind == 1)
                        AddPaintKeys(d, out);
                    node = it->Next(0, 0, 0, 0);
                }
            }
            if (it != 0)
                it->Release();
        }
        pal->Release();
    }
}

// ===========================================================================
// @ 0x004e9ca0
// Palette enumerator for one model type: fetches the model's property list,
// walks every palette entry and feeds the once/twice/thrice key holders to
// UpgradeParts.
// ===========================================================================
void FUN_004e9ca0(Vec* out)
{
    AutoRefCountPropertyList handle;                  // ebp-8
    int typeId = SP::Editor::GetConfigFromModelType(0xdfad9f51);   // ebp-4
    PropertyManager* pPropMgr = SP::PropertyManager();              // ebp-0x5c
    void** ppOut = handle.AsPPVoidParam();                          // ebp-0x3c
    pPropMgr->GetPropertyList(typeId, g_pPropertyRequest, ppOut);
    if (handle.mpObject != 0) {
        EA::ResourceMan::Key key;                     // ebp-0x14
        key.instance = 0;
        key.type = 0;
        key.group = 0;
        if (GetPropertyAsKey(handle.mpObject, 0xf5cbe065, &key)) {
            SP::cSPPalette* pPalette =
                new ("Editor", 0, 0, 0, 0) SP::cSPPalette();        // ebp-0x18
            if (pPalette != 0)
                pPalette->AddRef();
            if (pPalette != 0) {
                if (pPalette->Init(key, 0xdfad9f51, 0, 0, 0, 0, 0)) {
                    SP::cSPPaletteCursor* pCursor =
                        new ("Editor", 0, 0, 0, 0) SP::cSPPaletteCursor();  // ebp-0x1c
                    if (pCursor != 0)
                        pCursor->AddRef();
                    if (pCursor != 0) {
                        pCursor->SetPalette(pPalette);
                        SP::cPaletteEntry* pNode = pCursor->First(0, 0, 0, 0);  // ebp-0x20
                        while (pNode != 0) {
                            DeclareParam d = pNode->mParam;         // ebp-0x30
                            void* pHolder = ((Manager*)GetMgr401010())->Find(d.key, d.b);
                            if (pHolder != 0) {
                                UpgradeParts(d, out);
                                if (GetPropertyAsKey(pHolder, 0x3a3b9d21, &d.key))
                                    UpgradeParts(d, out);
                                if (GetPropertyAsKey(pHolder, 0x18c1dbe0, &d.key))
                                    UpgradeParts(d, out);
                                if (GetPropertyAsKey(pHolder, 0xf48eb09, &d.key))
                                    UpgradeParts(d, out);
                            }
                            pNode = pCursor->Next(0, 0, 0, 0);
                        }
                    }
                    if (pCursor != 0)
                        pCursor->Release();
                }
            }
            if (pPalette != 0)
                pPalette->Release();
        }
    }
    if (handle.mpObject != 0)
        handle.mpObject->Release();
}

// ===========================================================================
// @ 0x004e95e0
// Composes the preview object's basis: the provider hands out four corner
// vectors, the owner supplies the world transform, and the result is the
// scaled origin plus the weighted corner sum.
// ===========================================================================
void SP::cBasisSource::BuildBasis(Vector3* pOutVector, cSPMatrix3* pOutMatrix)
{
    cTransformSource* pOwner = mpObject;
    if (pOwner == 0)
        return;
    ICorners* pProvider = mpProvider;
    if (pProvider == 0)
        return;
    void* pSecondary = pOwner->mpSecondary;   // read-only, as the original does
    void* pPrimary = pOwner->mpPrimary;       // read-only, as the original does
    float scale = pOwner->mVectorScale;
    Vector3 corners[4];                 // ebp-0x5c .. ebp-0x2c
    pProvider->GetCorners(corners);
    cWorldSlot world;                   // ebp-0x98; the callee fills a matrix at +0x14
    StoreRows(pOwner->ComposeInto(&world), corners);
    Vector3 sum = corners[0] * mScale.x + corners[1] * mScale.y + corners[2] * mScale.z;
    cSPMatrix3 basis;                   // ebp-0x30
    BuildBasisMatrix(&basis, corners[0], corners[1], corners[2]);
    *pOutMatrix = mBasis * basis;
    *pOutVector = (mOrigin * basis) * scale + sum;
}
