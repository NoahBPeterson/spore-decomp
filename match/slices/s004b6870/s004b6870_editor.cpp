// Slice s004b6870 (editor part): SP::EditorUtils skin-paint helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast /GS- (the editor module; the EASTL
// instances of this slice are in s004b6870.cpp, built without /arch:SSE).
#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }
void* operator new(unsigned int size, const char* pName, int flags = 0, unsigned debugFlags = 0, const char* pFile = 0, int line = 0);   // 0xf473a0

extern "C" double __cdecl pow(double x, double y);
#pragma intrinsic(pow)
#include <math.h>                                                // pow(float, int) -> _Pow_int<float> @ 0x4537f0

extern float gSkinPaintCurveBase;                                // 0x15d75f0

struct cSPColorRGB {
    float r, g, b;
    cSPColorRGB(float r_, float g_, float b_) : r(r_), g(g_), b(b_) {}
    cSPColorRGB(const cSPColorRGB& c) : r(c.r), g(c.g), b(c.b) {}
};
cSPColorRGB __cdecl HSVToRGB(float h, float s, float v);         // 0x67fe30

namespace EA { namespace Random {
struct RandomLinearCongruential {
    uint32_t mnSeed;
    uint32_t RandomUint32Uniform(uint32_t nLimit);               // 0xa68fb0
    double RandomDoubleUniform();                                // 0x9360d0
};
} }
float __cdecl RandomFloatInRange(EA::Random::RandomLinearCongruential& rng, double fMin, double fMax);   // 0x4b8900
extern EA::Random::RandomLinearCongruential gRandom;            // 0x1601760
extern uint32_t gSkinPaintPropGroup;                             // 0x15d71f8
extern const float kSkinPaintValueMax;                           // 0x13ec4d4

namespace eastl {
struct allocator { allocator() {} };
template <typename T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    vector(const allocator& a = allocator());                    // 0x540470
    ~vector() { DoDestroyValues(mpBegin, mpEnd); DoFree(); }
    void DoFree();                                               // 0x5156b0 (~VectorBase)
    static void DoDestroyValues(T* first, T* last) { for (; first < last; ++first) first->~T(); }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t n) { return mpBegin[n]; }
    void push_back(const T& value);                              // 0x4e19a0
};
}

namespace SP {

struct SkinPaintEntry {
    uint32_t mEffect;
    uint32_t mData[2];
};

struct ResourceKey { uint32_t mInstanceID, mTypeID, mGroupID; };

struct cPropertyList {
    virtual int AddRef();
    virtual int Release();
};
struct cPropertyManager {
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3();
    virtual void _v4(); virtual void _v5(); virtual void _v6(); virtual void _v7();
    virtual void _v8(); virtual void _v9(); virtual void _v10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList** ppList);   // 0x2c
};
cPropertyManager* PropertyManager();                             // 0x67de30
bool __cdecl GetPropertyArray(cPropertyList* pList, uint32_t id, uint32_t* pCount, SkinPaintEntry** ppValues);   // 0x6a0ae0

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T** AsPointerRef()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};

struct cThemeNode {
    char pad0[0xc];
    ResourceKey mKey;                           // +0x0c
    char pad1[0x24 - 0x18];
    uint32_t mType;                             // +0x24
    uint32_t GetType() const { return mType; }
};

struct cThemeReader {
    virtual void _v0();
    virtual int AddRef();
    virtual int Release();
    char pad[0x20 - 4];
    cThemeReader();                                              // 0x5c7b80
    void Read(void* source);                                     // 0x5c7bc0
    cThemeNode* GetFirst(int a, int b, int c, int d);            // 0x5c7e80
    cThemeNode* GetNext(int a, int b, int c, int d);             // 0x5c7e20
    void Close();                                                // 0xc2e4e0
};

struct cSPEditorBlock {
    void UpdateSkin();                                           // 0x441080
};

struct cSPEditorModel {
    void Update();                                               // 0x4ae250
    cSPEditorBlock* GetBlock(uint32_t index);                    // 0x4accb0
    int GetBlockCount();                                         // 0x4accf0
    void SetSkinEffect(int i, uint32_t effect);                  // 0x4adcf0
    void SetSkinEffectSeed(int i, uint32_t seed);                // 0x4add10
    void SetSkinColor(int i, cSPColorRGB color);                 // 0x4add30
};

namespace EditorUtils {

// @ 0x4b7600
float SkinPaintCurve(float x)
{
    return pow(gSkinPaintCurveBase, -pow((x - 0.5f) * 1.5f, 2)) - 0.15f;
}

// @ 0x4b7660
void UpdateModelSkin(cSPEditorModel* model)
{
    model->Update();
    for (int i = 0, n = model->GetBlockCount(); i < n; i++) {
        cSPEditorBlock* block = model->GetBlock(i);
        if (block)
            block->UpdateSkin();
    }
    model->Update();
}

inline void SetSkinColorHSV(cSPEditorModel* model, int i, float h, float s, float v)
{
    model->SetSkinColor(i, HSVToRGB(h, SkinPaintCurve(s), SkinPaintCurve(v)));
}

// @ 0x4b76c0
void ApplySkinPaintThemeToModel(cSPEditorModel* model, void* theme)
{
    if (model && theme) {
    eastl::vector<SkinPaintEntry> lists[3];

    AutoRefCount<cThemeReader> pReader(new("Editor") cThemeReader());
    if (pReader) {
        pReader->Read(theme);
        cThemeNode* node = pReader->GetFirst(0, 0, 0, 0);
        while (node) {
            switch (node->mType) {
            case 0xdee3d8a8: {
                ResourceKey propKey = node->mKey;
                AutoRefCount<cPropertyList> pList(0);
                if (PropertyManager()->GetPropertyList(propKey.mInstanceID, gSkinPaintPropGroup, pList.AsPointerRef())) {
                    SkinPaintEntry* values = 0;
                    uint32_t numValues = 0;
                    GetPropertyArray(pList, 0xb0e066a7, &numValues, &values);
                    if (numValues == 3) {
                        if (values[0].mEffect && !values[1].mEffect && !values[2].mEffect)
                            lists[0].push_back(values[0]);
                        else if (!values[0].mEffect && values[1].mEffect && !values[2].mEffect)
                            lists[1].push_back(values[1]);
                        else if (!values[0].mEffect && !values[1].mEffect && values[2].mEffect)
                            lists[2].push_back(values[2]);
                    }
                }
                break;
            }
            }
            node = pReader->GetNext(0, 0, 0, 0);
        }

        for (int i = 0; i < 3; i++) {
            model->SetSkinEffect(i, 0);
            model->SetSkinEffectSeed(i, gRandom.RandomUint32Uniform(10000));
            int numValues = lists[i].size();
            if (i == 0) {
                if (numValues > 0)
                    model->SetSkinEffect(i, lists[i][0].mEffect);
                SetSkinColorHSV(model, i, RandomFloatInRange(gRandom, 0.0, kSkinPaintValueMax),
                                (float)gRandom.RandomDoubleUniform(), (float)gRandom.RandomDoubleUniform());
            } else {
                if (numValues > 0)
                    model->SetSkinEffect(i, lists[i][0].mEffect);
                model->SetSkinColor(i, cSPColorRGB(1.0f, 1.0f, 1.0f));
            }
        }
        pReader->Close();
    }
    }
}

}  // namespace EditorUtils
}  // namespace SP
