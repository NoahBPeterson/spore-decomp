// Slice s004b7b80: mix of editor/rng helpers near the cSPEditorPhysicsWorld region.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE (frame-pointer) for most; a few x87 float helpers.
#include "types.h"

extern void* g_vtbl;

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---------------------------------------------------------------------------
// comparator helpers (member functions of a MI class; base at -8)
// ---------------------------------------------------------------------------
struct BaseCmp {
    unsigned char* SetEq(unsigned char* out, int a, int b);   // 0x4b8950
};
struct NodeKeyPos {                                               // 12-byte aggregate in a node key
    uint32_t v[3];
};
struct NodeKey {                                                  // 20-byte key copied by value
    uint32_t mId;                                                 // +0x00
    NodeKeyPos mPos;                                              // +0x04
    float mW;                                                     // +0x10
};
struct Node {                                                     // node of the compared tree
    uint32_t pad0[3];                                             // +0x00
    Node* mpNext;                                                 // +0x0c
    NodeKey mKey;                                                 // +0x10
};
struct DerivedCmp {
    char pad[8];
    unsigned char* SetEqFromNodes(unsigned char* out, int a, int b);  // 0x4b8980
    unsigned char* SetEqFromRoots(unsigned char* out, int p2, int a, int b, int p5, int p6);  // 0x4b89c0
};

// @ 0x4b8950
unsigned char* BaseCmp::SetEq(unsigned char* out, int a, int b)
{
    if (a == b) { *out = 1; return out; }
    *out = 0;
    return out;
}

// @ 0x4b8980
unsigned char* DerivedCmp::SetEqFromNodes(unsigned char* out, int a, int b)
{
    int b18 = *(int*)(b + 0x1c);
    int a10 = *(int*)(a + 0x1c);
    ((BaseCmp*)((char*)this - 8))->SetEq(out, a10, b18);
    return out;
}

// @ 0x4b89c0
unsigned char* DerivedCmp::SetEqFromRoots(unsigned char* out, int p2, int a, int b, int p5, int p6)
{
    (void)p2; (void)p5; (void)p6;
    Node* r = (Node*)b;
    while (r->mpNext != 0)
        r = r->mpNext;
    NodeKey k = r->mKey;
    uint32_t key = k.mPos.v[2];
    Node* l = (Node*)a;
    while (l->mpNext != 0)
        l = l->mpNext;
    ((BaseCmp*)((char*)this - 0xc))->SetEq(out, (int)l->mKey.mPos.v[2], (int)key);
    return out;
}

// ---------------------------------------------------------------------------
// misc helpers
// ---------------------------------------------------------------------------
struct PropObj {
    virtual void v0(); virtual void Release();
};

extern "C" {
    void* SP_PropertyManager();
    void  FUN_00425990(void* vec);
    void  FUN_0042dee0();
    void  FUN_004b64b0();
    void  FUN_004b66b0();
    void  FUN_004b62a0();
    void  FUN_004b6340();
    void  FUN_004b69d0();
    void  FUN_004b6450();
    void  FUN_004b6bf0();
    char  SP_GetResourceTypeFromModelType();
    void  FUN_004b8950(void* a, void* b, void* c);
    void  FUN_004b5fb0(void* a, void* b);
    void  FUN_004b54b0(void* a);
    void  FUN_004b5610(void* a);
    void  FUN_004b5a60(void* a);
    void  FUN_004b97e0(void* a, void* b);
    double __fastcall EA_RandomDoubleUniform(void* rng);   // 0x009360d0
    void  FUN_00540470(void* a);
    void  FUN_00540520(void);
    void  FUN_005c7bc0(void* a);
    void* FUN_005c7e80(int a, int b, int c, int d);
    void* FUN_005c7e20(int a, int b, int c, int d);
    void* FUN_005c7b80(void);
    void  FUN_004e8a30(void* a);
    void* operator_new_ea(uint32_t n, const char* tag, int a, int b, int c, int d);
    void  SP_GetPropertyAsKeyInstance(void* list, uint32_t key, uint32_t* out);  // 0x6a12a0
    bool  SP_GetPropertyT(void* list, uint32_t key, float* out);                 // 0x40cf10
}

// ---------------------------------------------------------------------------
// 0x4b7b80: builds a two-colour "paint" ability (gradient colours read from a property list) and
// hands it to the owner's virtual slot 0xa4.
// ---------------------------------------------------------------------------
void* operator new(size_t size, const char* name, int a, int b, int c, int d);   // 0x00f473a0

struct V3;
struct Vec3f { float x, y, z; };                 // same layout as V3 (rw Vector3)
struct Col3 {                                    // three floats passed by value
    float v[3];
    Col3() {}
    Col3(float a, float b, float c) { v[0] = a; v[1] = b; v[2] = c; }
    Col3(const V3& r);
    float& operator[](int i) { return v[i]; }
};
struct V3 {
    float x, y, z;
    V3(const Col3& c) : x(c.v[0]), y(c.v[1]), z(c.v[2]) {}
    V3(float a, float b, float c) : x(a), y(b), z(c) {}
};
inline Col3::Col3(const V3& r) { v[0] = r.x; v[1] = r.y; v[2] = r.z; }
V3 __cdecl LerpVec3(const V3& a, const V3& b, float t);          // 0x00413cc0

struct Color4 {
    float r, g, b, a;
    Color4(float r_, float g_, float b_, float a_);             // 0x0044e410 (ret 0x10)
};

// rw::math::fpu::Vector3Template<float,0> / Col4 (Color4) helpers used by the paint-material builder.
extern float _HK_REAL_ONE;                                       // 0x01485720
extern float _HK_REAL_ZERO;                                      // 0x01485378
extern float g_halfConst;                                        // 0x01471064 (0.5f)
extern float g_sixtyConst;                                       // 0x013ebc4c (60.0f)
extern float g_epsilonConst;                                     // 0x013ebca0 (0.0001f)
extern Vec3f g_blackColor;                                       // 0x01514eb8 (kSwatchColor)

V3* Vector3_SubOut(V3* out, const V3* a, const V3* b);           // 0x0041db10
V3* Vector3_ScaleOut(V3* out, const V3* a, const float* s);      // 0x0041dba0
V3* Vector3_AddOut(V3* out, const V3* a, const V3* b);           // 0x0041dc10
// out = a + (b - a) * t   (0x00413cc0; the trailing float is []-indexed off the parameters)
V3* Vector3_LerpOut(V3* out, const V3* a, const V3* b, const float& t);   // 0x00413cc0

struct PropVal {
    char pad[0x12];
    uint16_t mType;                                              // +0x12
    float* GetFloat();                                           // 0x0041ea70
};
struct PropList {
    virtual void v0();
    virtual void Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, PropVal** out);        // slot 9 (+0x24)
};
struct PropListRef {
    PropList* mpObject;
    PropListRef() : mpObject(0) {}
    ~PropListRef() { if (mpObject) mpObject->Release(); }
    void** AsPPVoidParam();                                      // 0x0041d870 (resets, releases)
    PropList* get() { return mpObject; }
};
struct PropMgr {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
    virtual void m5(); virtual void m6(); virtual void m7(); virtual void m8(); virtual void m9();
    virtual void m10();
    virtual bool GetPropertyList(uint32_t inst, uint32_t group, void** out);   // slot 11 (+0x2c)
};
extern "C" PropMgr* SP_PropertyManager_();                      // 0x0067de30
extern uint32_t g_PaintGroupId;                                  // 0x015d71f8

struct ItemVec {
    uint32_t** mpBegin;                                          // +0
    uint32_t** mpEnd;
    uint32_t** mpCap;
    void resize(uint32_t n);                                     // 0x004cd3c0
    uint32_t*& operator[](int i) { return mpBegin[i]; }
};
struct AbilityHost {                                             // 0x1c bytes
    virtual void v0();
    char pad[4];
    ItemVec mItems;                                              // +0x08
    char pad14[8];
    AbilityHost();                                               // 0x0077d1d0
};
struct ColorAbility {                                            // 0x2c bytes
    virtual void v0();
    char pad[0xc - 4];
    Color4 mColorA;                                              // +0x0c
    Color4 mColorB;                                              // +0x1c
    ColorAbility();                                              // 0x004b87c0
};
struct AbilityBase {
    virtual void v0();
    uint16_t mId; uint16_t mFlags;
    void* mpSelf;
    AbilityBase(int id, int flags, int x);                       // 0x0040cfd0 (ret 0xc)
};
struct AbilityItem : AbilityBase {                               // 0xc bytes
    virtual void v0();
    __forceinline AbilityItem() : AbilityBase(0x244, 1, 0) {
        mpSelf = (this == 0) ? 0 : (void*)((char*)this + 0xc);
    }
};

// ---------------------------------------------------------------------------
// 0x4b8180's support types
// ---------------------------------------------------------------------------
struct SwatchMaterial {                                          // cSwatchMaterial
    uint32_t mFlags;                                             // +0x04
    char pad8[0x4c - 8];
    Vec3f mColor;                                                // +0x4c
    float mAlpha;                                                // +0x58
    char mLayer;                                                 // +0x5c
    void SetColor(const Vec3f& color) { mFlags |= 2; mColor = color; }
    void SetAlpha(float alpha) { mAlpha = alpha; mFlags |= 8; }
};
struct ModelTypeObject {                                         // arg +0x24: carries GetModelType
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual int GetModelType(int paint);                         // +0x2c (slot 11)
};
struct PropListV {                                               // cPropertyList (arg +0x28)
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual int GetByKey(int key, void** out);                   // +0x2c (slot 11)
};
struct ShaderStateV {                                            // 0x70 bytes; header + 0x10-byte slots
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void* GetRes(int a, int b);                          // +0x20 (slot 8)
    void InsertResource(unsigned a, unsigned b);                 // 0x0077cb10
    void setSlotU0(int idx, char v);                             // 0x00777a60
    void setSlotU1(int idx, char v);                             // 0x00777a80
    void setSlotV0(int idx, char v);                             // 0x00777aa0
};
struct AbilityHost1c {                                           // cCreatureAbility-lookalike, 0x1c bytes
    virtual void v04();
    char pad4[4];
    ItemVec mItems;                                              // +0x08
    AbilityHost1c();                                             // 0x0077d1d0
};
struct SwatchAbility {                                           // 0x3c bytes = the paint ability
    virtual void v04();
    char pad4[0xc - 4];
    Color4 mColorA;                                              // +0x0c
    Color4 mColorB;                                              // +0x1c
    float mAlphaA;                                               // +0x2c
    float mScaleA;                                               // +0x30
    float mAlphaB;                                               // +0x34
    float mScaleB;                                               // +0x38
    SwatchAbility();                                             // 0x004b8860
};

ShaderStateV* ResourceManager();                                 // 0x0067dd60
void* FUN_0040d010();                                            // 0x0040d010

static inline void ReadFloatProp(PropList* list, uint32_t key, float& out)
{
    if (list) {
        PropVal* v;
        if (list->GetProperty(key, &v) && v->mType == 0xd)
            out = *v->GetFloat();
    }
}

// @ 0x4b7b80
void FUN_004b7b80(uint32_t instId, Col3 colA, Col3 colB, void* owner, int arg1, int arg2)
{
    PropListRef props;
    AbilityHost* host = new ("Editor", 0, 0, 0, 0) AbilityHost();
    float alphaA = 1.0f;
    float alphaB = 60.0f;
    float unusedVal = 1.0f;
    float tHigh = 0.0f;
    float tLow = 0.0f;
    ColorAbility* ab = new ("Editor", 0, 0, 0, 0) ColorAbility();
    AbilityItem* item = new ("Editor", 0, 0, 0, 0) AbilityItem();
    if (SP_PropertyManager_()->GetPropertyList(instId, g_PaintGroupId, props.AsPPVoidParam())) {
        ReadFloatProp(props.get(), 0x562a3b7, alphaA);
        ReadFloatProp(props.get(), 0x226c551, alphaB);
        ReadFloatProp(props.get(), 0x55d3d82, unusedVal);
        ReadFloatProp(props.get(), 0x25e49bb, tHigh);
        ReadFloatProp(props.get(), 0x265fb07, tLow);
    }
    Col3 half(0.5f, 0.5f, 0.5f);
    Col3 col = LerpVec3(half, colB, tLow);
    if (tHigh > tLow) {
        Col3 col2 = LerpVec3(half, colA, tHigh);
        col = col2;
    }
    ab->mColorA = Color4(colA[0], colA[1], colA[2], alphaA);
    ab->mColorB = Color4(col[0], col[1], col[2], alphaB);
    host->mItems.resize(2);
    host->mItems[0] = (uint32_t*)ab;
    host->mItems[1] = (uint32_t*)item;
    (*(void(__thiscall**)(void*, int, AbilityHost*, int))(*(int*)owner + 0xa4))(owner, arg1, host, arg2);
}

// @ 0x4b8180
void FUN_004b8180(uint32_t instId, Col3 colA, Col3 colB, ModelTypeObject* owner, int self, int paint)
{
    if (paint == 4 || paint == 2 || paint == 1 || paint == 0xa || paint == 0x12 || paint == 0x13 ||
        paint == 0x19 || paint == 0x1a || paint == 0x20 || paint == 0x21 || paint == 0x11) {
        FUN_004b7b80(instId, colA, colB, owner, self, paint);
        return;
    }
    if (paint == 0x32)
        return;

    uint32_t unused0 = 0;
    uint32_t c1Id = 0;
    uint32_t c2Id = 0;
    float alphaA = _HK_REAL_ONE;
    float alphaB = g_sixtyConst;
    float alphaScale = _HK_REAL_ONE;
    float t = g_halfConst;
    float tHigh = g_halfConst;
    float tLow = g_halfConst;

    PropList* list = 0;
    if (SP_PropertyManager_()->GetPropertyList(instId, g_PaintGroupId, (void**)&list)) {
        SP_GetPropertyAsKeyInstance(list, 0xb0e066a4, &c1Id);
        SP_GetPropertyAsKeyInstance(list, 0xb0e066a5, &c2Id);
        SP_GetPropertyAsKeyInstance(list, 0xb0e066a6, &unused0);
        SP_GetPropertyT(list, 0x562a3b7, &alphaA);
        SP_GetPropertyT(list, 0x226c551, &alphaB);
        SP_GetPropertyT(list, 0x55d3d82, &alphaScale);
        if (SP_GetPropertyT(list, 0x562a106, &t))
            t = _HK_REAL_ONE / (t + g_epsilonConst);
        else
            SP_GetPropertyT(list, 0x2327a87, &t);
        SP_GetPropertyT(list, 0x25e49bb, &tHigh);
        SP_GetPropertyT(list, 0x265fb07, &tLow);
    }

    if (self != 0 && owner != 0 && c1Id != 0 && c2Id != 0) {
        AbilityHost1c* host = new ("Editor", 0, 0, 0, 0) AbilityHost1c();
        void* shaderMem = new ("Editor", 0, 0, 0, 0) char[0x70];
        ShaderStateV* shader = 0;
        if (shaderMem)
            shader = (ShaderStateV*)FUN_0040d010();
        ShaderStateV* mgr1 = ResourceManager();
        mgr1->InsertResource(0, (unsigned)mgr1->GetRes(c1Id, 0));
        ShaderStateV* mgr2 = ResourceManager();
        mgr2->InsertResource(1, (unsigned)mgr2->GetRes(c2Id, 0));
        shader->setSlotU0(0, 1);
        shader->setSlotU1(0, 2);
        shader->setSlotV0(0, 2);
        shader->setSlotU0(1, 1);
        shader->setSlotU1(1, 2);
        shader->setSlotV0(1, 2);

        SwatchAbility* ability = new ("Editor", 0, 0, 0, 0) SwatchAbility();
        ability->mColorA = Color4(colA[0], colA[1], colA[2], tHigh);
        ability->mColorB = Color4(colB[0], colB[1], colB[2], tLow);
        ability->mAlphaA = alphaA;
        ability->mScaleA = alphaB;
        ability->mAlphaB = alphaScale;
        ability->mScaleB = t;
        host->mItems.resize(2);
        host->mItems[0] = (uint32_t*)shader;
        host->mItems[1] = (uint32_t*)ability;
        (*(void(__thiscall**)(int, AbilityHost1c*, int))(*(int*)owner + 0xa4))(self, host, paint);
    }

    if (list)
        list->Release();
}

// @ 0x4b8750
void FUN_004b8750(int a, int* b, int c, int d)
{
    if (c != 0) {
        if (d == -1) {
            if (b != 0 && a != 0) {
                (*(void(__thiscall**)(int*, int, int))(*b + 0x54))(b, a, c);
                if (SP_GetResourceTypeFromModelType()) {
                    uint32_t v = 0xffffffff;
                    extern void vec_push_u32(uint32_t*);
                    vec_push_u32(&v);
                }
            }
        } else {
            extern void vec_push_u32(uint32_t*);
            vec_push_u32((uint32_t*)&d);
        }
    }
}

// @ 0x4b87c0
void* __fastcall FUN_004b87c0(void** o)
{
    o[0] = &g_vtbl;
    *(uint16_t*)(o + 1) = 0x212;
    *(uint16_t*)((char*)o + 6) = 0x20;
    o[2] = 0;
    for (int i = 2; i >= 0; i--) {
    }
    o[0] = &g_vtbl;
    void* p = (o == 0) ? 0 : (void*)(o + 3);
    o[2] = p;
    return o;
}

// @ 0x4b8860
void* __fastcall FUN_004b8860(void** o)
{
    o[0] = &g_vtbl;
    *(uint16_t*)(o + 1) = 0x213;
    *(uint16_t*)((char*)o + 6) = 0x30;
    o[2] = 0;
    for (int i = 2; i >= 0; i--) {
    }
    o[0] = &g_vtbl;
    void* p = (o == 0) ? 0 : (void*)(o + 3);
    o[2] = p;
    return o;
}

extern void* g_vtbl;

// @ 0x4b8900
double FUN_004b8900(void* rng, double lo, double hi)
{
    double v = EA_RandomDoubleUniform(rng) * (hi - lo) + lo;
    if (v < hi) {
        if (v >= lo)
            return v;
        return lo;
    }
    return hi;
}

struct ModelTypeObj {                                             // object carrying a model-type virtual
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual int GetModelType(int e);                              // +0x2c (slot 11)
};
struct CmpArg {                                                   // compared operand (key at +0x20)
    uint32_t pad0[8];
    int mModelKey;                                                // +0x20
};
struct ModelCmp {
    char pad[0x10];
    unsigned char* SetEqFromModel(unsigned char* out, CmpArg* a, ModelTypeObj* b, int c);  // 0x4b8a70
};

// @ 0x4b8a70
unsigned char* ModelCmp::SetEqFromModel(unsigned char* out, CmpArg* a, ModelTypeObj* b, int c)
{
    int u = b->GetModelType(c);
    ((BaseCmp*)((char*)this - 0x10))->SetEq(out, a->mModelKey, u);
    return out;
}
