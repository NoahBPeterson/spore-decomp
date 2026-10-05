// Slice s004b2320: SP::cSPEditorPaintTheme (editor paint-theme resource) construction, teardown,
// prop (de)serialization and application. Editor region: unoptimized /Od /Ob1, /arch:SSE, no /EHsc.
//
// Retail layout:
//   +0x00 vtable (Editor::cEditorResource)
//   +0x04 vtable (RefCountVTemplate)
//   +0x08 int
//   +0x0c PaintVector mPropTheme   (inline-buffer vector of 0x20-byte elements)
//   +0x128 ModelTree  mModelTheme  (rbtree map)
//   +0x144 propThemeID / +0x148 sourceRef / +0x14c resourceType
//   +0x150 closestRegions (vector) / +0x164 skinEffects[3] / +0x170 skinEffectSeeds[3]
//   +0x17c skinColors[3]
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct cSPColorRGB { uint32_t x, y, z; };
struct PropObj;
struct PropMgr;

extern "C" {
    void* SP_PropertyManager();                 // 0x0067de30
    void  FUN_006a0ae0(PropObj* list, uint32_t name, void* a, void* b);
    void  FUN_006a0760(void* obj, uint32_t id, void* a, void* b);
    void  FUN_004b8750(int a, int b, void* out, int c);
    char  FUN_004b3a50(void* out, int a, uint32_t b);
    void  FUN_00440f60(void* out);
    void  FUN_00440ff0(void* obj);
    void  FUN_00440c40(void* obj, int a);
    void  FUN_004b8180();
    void  FUN_004098a0(void* dst, const void* src);
    void  FUN_00425990(void* vec);
    void  FUN_00455290(void* vec);
    void  FUN_004b3c20(int a);
    void  FUN_004b3190(int a);
}

// The asset view object (members called via ecx).
struct Asset {
    char b[0x800];
    void     GetColor(int i, cSPColorRGB* out);      // 0x004adca0
    uint32_t GetEffect(int i);                        // 0x004adc60
    uint32_t GetSeed(int i);                          // 0x004adc80
    void     SetColor(int i, cSPColorRGB* c);         // 0x004add30
    void     SetEffect(int i, uint32_t v);            // 0x004adcf0
    void     SetSeed(int i, uint32_t v);              // 0x004add10
    void     BeginWrite();                            // 0x004ae250
    int      ModelCount();                            // 0x004accf0
    void*    ModelAt(int i);                          // 0x004accb0
};

// Property-list / manager virtual interfaces (slots matter).
struct PropObj {
    virtual void v0();                                // 0 (+0)
    virtual void Release();                           // 1 (+4)
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual char Has(uint32_t id);                    // 7 (+0x1c)
    virtual void v8(); virtual void v9();
    virtual void* Get(uint32_t id);                   // 10 (+0x28)
};
struct PropMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual char GetPropertyList(int id, uint32_t type, void** out);   // 11 (+0x2c)
};

namespace SP {

struct PaintVector {
    void* mpBegin;          // +0
    void* mpEnd;            // +4
    void* mpCap;            // +8
    char  mInline[0x110];   // +0xc .. +0x11c
    void  Ctor();                             // 0x0041d050
    void* Erase(void* first, void* last);     // 0x004b5570
    void* Insert(void* value);                // 0x00454420
    void  Clear() { Erase(mpBegin, mpEnd); }
};

struct ModelTree {
    char _[0x1c];
    void Ctor(void* tag);       // 0x004b5980
    void Reset();               // 0x004b5030
    void ResetFast();           // 0x004b5a20
    void Nuke(void* node);      // 0x004b5a60
};

class cSPEditorPaintTheme {
public:
    void* mpVtbl0;              // +0x00
    void* mpVtbl1;              // +0x04
    int   mRefCount;            // +0x08
    PaintVector mPropTheme;     // +0x0c
    ModelTree   mModelTheme;    // +0x128
    uint32_t mPropThemeID;      // +0x144
    uint32_t mSourceRef;        // +0x148
    uint32_t mResourceType;     // +0x14c
    void* mpClosestBegin;       // +0x150
    void* mpClosestEnd;         // +0x154
    void* mpClosestCap;         // +0x158
    char  pad_15c[8];           // +0x15c
    uint32_t mSkinEffects[3];   // +0x164
    uint32_t mSkinEffectSeeds[3]; // +0x170
    cSPColorRGB mSkinColors[3]; // +0x17c

    cSPEditorPaintTheme();
    ~cSPEditorPaintTheme();
    void* AsInterface(int type);
    void  SetSource(int source);
    void  Reset();
    void  Reset2();
    uint32_t ReadFromAsset(Asset* asset);
    uint32_t ReadFromProp2(int prop, char useColors);
    uint32_t ReadFromProp(int prop);
    void  WriteToProp(Asset* asset, int resourceType);
    void  ApplyToAsset(int asset, int view);
    void  Apply(int a, int b, int c, int d);
    void  InitClosestRegions(void* a, void* b);
};

}  // namespace SP

using namespace SP;

extern void* g_vtbl_EditorResource;
extern void* g_vtbl_BakeSprites;
extern void* g_vtbl_ContentValidator;
extern void* g_vtbl_PaintTheme0;
extern void* g_vtbl_PaintTheme1;

extern uint32_t DAT_015d6e2c, DAT_015d6e30, DAT_015d6e34;
extern uint32_t DAT_015d6b98, DAT_015d6b9c, DAT_015d6ba0;
extern uint32_t DAT_015d6cc8, DAT_015d6f64;

extern "C" {
    void* FUN_004bb860(void* a);
    char  FUN_004bbe90(void* a);
    char  FUN_004bbed0(void* a);
    char  FUN_0041dd30(void* a, void* b);
    void  FUN_004adca0(Asset* a, int i, cSPColorRGB* out);
    uint32_t FUN_004adc60(Asset* a, int i);
    uint32_t FUN_004adc80(Asset* a, int i);
    void  FUN_004add30(Asset* a, int i, cSPColorRGB* c);
    void  FUN_004adcf0(Asset* a, int i, uint32_t v);
    void  FUN_004add10(Asset* a, int i, uint32_t v);
    void  FUN_004ae250(Asset* a);
    int   FUN_004accf0(Asset* a);
    void* FUN_004accb0(Asset* a, int i);
    void  FUN_004553b0(void* out, void* key);
}

// @ 0x004b24c0
cSPEditorPaintTheme::cSPEditorPaintTheme()
{
    mpVtbl0 = &g_vtbl_EditorResource;
    mpVtbl0 = &g_vtbl_BakeSprites;
    mpVtbl1 = &g_vtbl_ContentValidator;
    mRefCount = 0;
    mpVtbl0 = &g_vtbl_PaintTheme0;
    mpVtbl1 = &g_vtbl_PaintTheme1;
    mPropTheme.Ctor();
    mModelTheme.Ctor(&mSourceRef);
    mPropThemeID = 0;
    mResourceType = 0;
    mpClosestBegin = 0;
    mpClosestEnd = 0;
    mpClosestCap = 0;
    for (int i = 0; i < 3; i++) {
    }
}

// @ 0x004b25e0
cSPEditorPaintTheme::~cSPEditorPaintTheme()
{
    mpVtbl0 = &g_vtbl_PaintTheme0;
    mpVtbl1 = &g_vtbl_PaintTheme1;
    for (void** p = (void**)mpClosestBegin; p < (void**)mpClosestEnd; p++) {
    }
    FUN_00425990(&mpClosestBegin);
    mModelTheme.Nuke(*(void**)((char*)&mModelTheme + 0xc));
    for (char* p = (char*)mPropTheme.mpBegin; p < (char*)mPropTheme.mpEnd; p += 0x20) {
    }
    FUN_00455290(&mPropTheme);
    mpVtbl1 = &g_vtbl_ContentValidator;
    mpVtbl0 = &g_vtbl_EditorResource;
}

// @ 0x004b26a0
void* cSPEditorPaintTheme::AsInterface(int type)
{
    switch (type) {
    case 0x31ec923: return this;
    case (int)0xee3f516e: return this;
    default: return 0;
    }
}

// @ 0x004b26e0
void cSPEditorPaintTheme::SetSource(int source)
{
    mSourceRef = source;
    Reset();
}

// @ 0x004b2710
void cSPEditorPaintTheme::Reset()
{
    ScratchSlots<6>();
    mModelTheme.Reset();
    mPropTheme.Clear();
    mPropThemeID = 0;
    for (int i = 0; i < 3; i++) {
        mSkinColors[i].x = DAT_015d6e2c;
        mSkinColors[i].y = DAT_015d6e30;
        mSkinColors[i].z = DAT_015d6e34;
        mSkinEffects[i] = 0;
        mSkinEffectSeeds[i] = 0x4d2;
    }
}

// @ 0x004b27c0
void cSPEditorPaintTheme::Reset2()
{
    ScratchSlots<6>();
    mModelTheme.Reset();
    mPropTheme.Clear();
}

// @ 0x004b2800
uint32_t cSPEditorPaintTheme::ReadFromAsset(Asset* asset)
{
    Reset();
    if (asset != 0) {
        void* view = FUN_004bb860(*(void**)((char*)asset + 0x58));
        if (FUN_004bbe90(view)) {
            if (!FUN_004bbe90((void*)mSourceRef))
                return 0;
            mResourceType = (uint32_t)asset;
            for (int i = 0; i < 3; i++) {
                cSPColorRGB col;
                asset->GetColor(i, &col);
                mSkinColors[i] = col;
                mSkinEffects[i] = asset->GetEffect(i);
                mSkinEffectSeeds[i] = asset->GetSeed(i);
            }
            return 1;
        }
        if (FUN_004bbed0(view)) {
            if (!FUN_004bbed0((void*)mSourceRef))
                return 0;
            mResourceType = (uint32_t)asset;
            int n = asset->ModelCount();
            for (int i = 0; i < n; i++)
                FUN_004b3c20((int)asset->ModelAt(i));
            InitClosestRegions((void*)mSourceRef, (void*)mResourceType);
            return 1;
        }
    }
    return 0;
}

// @ 0x004b29b0
uint32_t cSPEditorPaintTheme::ReadFromProp2(int prop, char useColors)
{
    PropObj* list = 0;
    char ok = ((PropMgr*)SP_PropertyManager())->GetPropertyList(prop, DAT_015d6cc8, (void**)&list);
    if (!ok) {
        if (list)
            list->Release();
        return 0;
    }
    int count = 0;
    void* data = 0;
    int unused = 0;
    FUN_006a0ae0(list, 0xb0e066a7, &unused, &count);
    void* colors = 0;
    if (list->Has(0xb0e066a8)) {
        void* p = list->Get(0xb0e066a8);
        if ((*(uint16_t*)((char*)p + 0x10) & 0x30) == 0) {
            if (*(int16_t*)((char*)p + 0x12) != 0)
                colors = p;
        } else {
            colors = *(void**)p;
        }
    }
    for (int i = 0; i < count; i++) {
        int v = *(int*)((char*)data + i * 0xc);
        if (v != 0) {
            mSkinEffects[i] = v;
            mSkinEffectSeeds[i] = 0x4d2;
            if (useColors == 0) {
                mSkinColors[i].x = DAT_015d6b98;
                mSkinColors[i].y = DAT_015d6b9c;
                mSkinColors[i].z = DAT_015d6ba0;
            } else {
                uint32_t* c = (uint32_t*)colors + i * 3;
                mSkinColors[i].x = c[0];
                mSkinColors[i].y = c[1];
                mSkinColors[i].z = c[2];
            }
        }
    }
    if (list)
        list->Release();
    return 1;
}

// @ 0x004b2bb0
uint32_t cSPEditorPaintTheme::ReadFromProp(int prop)
{
    mModelTheme.Nuke(*(void**)((char*)&mModelTheme + 0xc));
    mModelTheme.ResetFast();
    mPropTheme.Erase(mPropTheme.mpBegin, mPropTheme.mpEnd);

    PropMgr* mgr = (PropMgr*)SP_PropertyManager();
    PropObj* list = 0;
    void* key = 0;
    mgr->GetPropertyList(prop, DAT_015d6cc8, (void**)&key);
    list = (PropObj*)key;
    if (list == 0)
        return 0;

    void* colors = 0;
    int count = 0;
    if (list->Has(0xb0e066a7)) {
        void* p = list->Get(0xb0e066a7);
        if ((*(uint16_t*)((char*)p + 0x10) & 0x30) == 0) {
            count = (*(int16_t*)((char*)p + 0x12) != 0) ? 1 : 0;
        } else {
            count = *(int*)((char*)p + 8);
        }
        colors = p;
    }
    void* colorA = 0;
    void* colorB = 0;
    if (list->Has(0xb0e066a8)) {
        void* p = list->Get(0xb0e066a8);
        colorA = p;
        if ((*(uint16_t*)((char*)p + 0x10) & 0x30) == 0) {
            if (*(int16_t*)((char*)p + 0x12) == 0)
                colorA = 0;
        } else {
            colorA = *(void**)p;
        }
    }
    if (list->Has(0xb0e066a9)) {
        void* p = list->Get(0xb0e066a9);
        colorB = p;
        if ((*(uint16_t*)((char*)p + 0x10) & 0x30) == 0) {
            if (*(int16_t*)((char*)p + 0x12) == 0)
                colorB = 0;
        } else {
            colorB = *(void**)p;
        }
    }
    (void)colors;
    for (int i = 0; i < count; i++) {
        int v = *(int*)((char*)colorA + i * 0xc);
        if (v != 0 && v != (int)0xe960add1) {
            uint32_t out[7];
            out[0] = v;
            uint32_t* cb = (uint32_t*)colorB + i * 3;
            out[1] = cb[0];
            out[2] = cb[1];
            out[3] = cb[2];
            cSPColorRGB col;
            FUN_004098a0(&col, (char*)colorA + i * 0xc + 4);
            (void)col;
            uint32_t* dst = (uint32_t*)mPropTheme.Insert(out);
            for (int k = 0; k < 7; k++)
                dst[k] = out[k];
        }
    }
    mPropThemeID = (uint32_t)prop;
    InitClosestRegions((void*)mSourceRef, (void*)mSourceRef);
    if (list)
        list->Release();
    return 1;
}

// @ 0x004b2f80
void cSPEditorPaintTheme::WriteToProp(Asset* asset, int resourceType)
{
    if (asset == 0)
        return;
    void* view = FUN_004bb860(*(void**)((char*)asset + 0x58));
    if (FUN_004bbe90(view)) {
        for (int i = 0; i < 3; i++) {
            if (mSkinEffects[i] == 0)
                continue;
            if (FUN_0041dd30(&DAT_015d6b98, &mSkinColors[i]))
                FUN_004add30(asset, i, &mSkinColors[i]);
            FUN_004adcf0(asset, i, mSkinEffects[i]);
            FUN_004add10(asset, i, mSkinEffectSeeds[i]);
        }
    } else if (FUN_004bbed0(view)) {
        PropObj* list = 0;
        if (resourceType != -1) {
            PropMgr* mgr = (PropMgr*)SP_PropertyManager();
            if (list)
                list->Release();
            mgr->GetPropertyList(resourceType, DAT_015d6f64, (void**)&list);
        }
        FUN_004ae250(asset);
        int n = asset->ModelCount();
        for (int i = 0; i < n; i++) {
            void* model = asset->ModelAt(i);
            ApplyToAsset((int)model, (int)list);
        }
        FUN_004ae250(asset);
        if (list)
            list->Release();
    }
}

// @ 0x004b3190
void cSPEditorPaintTheme::ApplyToAsset(int p, int x)
{
    if (p != 0) {
        int b18 = *(int*)(p + 0x18);
        int a10 = *(int*)(p + 0x10);
        Apply(a10, b18, x, p);
    }
}

// @ 0x004b31d0
void cSPEditorPaintTheme::Apply(int a, int b, int c, int d)
{
    int local8 = 0;
    int localc = 0;
    if (c != 0)
        FUN_006a0760((void*)c, 0xf21a7bdc, &localc, &local8);
    if (a == 0 || b == 0)
        return;
    int vec[3] = {0, 0, 0};
    FUN_004b8750(a, b, vec, -1);
    int* begin = *(int**)&vec[0];
    int* end = *(int**)&vec[1];
    int n = (int)(end - begin) >> 2;
    for (int i = 0; i < n; i++) {
        int region = begin[i];
        if (!(localc != 0 && !(region < local8 && *(char*)(localc + region) != 0)))
            continue;
        int out[8];
        FUN_00440f60(out);
        int extra = 0;
        if (d != 0)
            extra = *(int*)(d + 0x1c);
        char ok = FUN_004b3a50(out, region, extra);
        if (!ok)
            continue;
        if (d == 0) {
            FUN_00440ff0(out);
            FUN_004b8180();
        } else {
            if (out[0] == 0) {
                int base = d + 0x4c8;
                int tmpA = 0, tmpB = 0;
                FUN_004553b0(&tmpA, &region);
                int node = (tmpA == tmpB) ? *(int*)(base + 4) : tmpA;
                if (node != *(int*)(base + 4))
                    out[0] = *(int*)(node + 4);
            }
            FUN_00440c40(out, region);
        }
    }
    FUN_00425990(vec);
}

// @ 0x004b2320
struct RefCounted { virtual void V0(); virtual void V1(); };
void ConstructArray(RefCounted** p, unsigned int n, RefCounted** src)
{
    while (n != 0) {
        if (p != 0) {
            *p = *src;
            if (*p != 0)
                (*p)->V1();
        }
        --n;
        ++p;
    }
}
