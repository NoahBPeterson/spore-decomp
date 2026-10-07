// slice s004f1350 -- SP::cSPEditorModelValidity::TestComplexity
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast /GS- (editor /Od region, no /EHsc, no cookie).
//
// Validity test "too complex" (kValidityTooComplex = bit 0 of the result bitset). Reads the
// per-model-type complexity limits from the editor config property list, then walks every
// rigblock of the model, reads its own complexity properties (skipping blocks flagged as not
// counting), doubles a block's contribution when the config says symmetric copies count and the
// block is an unparented, non-symmetric original, and compares the five running totals with the
// limits. Sibling of TestSize (s004f01f0) and TestLimbs/TestBounds (s004ee9b0).
//
// /Od slot layout: cl orders a scope's locals by a hash of their names, so the locals carry the
// names that reproduce the original frame (found with tools/matching/od_names.py fit 15 / fit 8);
// each declaration is commented with its role.
//
// Note: the original checks the limit of property 0x9187aee3 for -1 but compares the sum against
// the limit of 0x047c1d1b, and vice versa; that cross-over is reproduced as-is.

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

// eastl::bitset<128>: set() as the inline EASTL body (the range check survives /Od).
struct ValidityBits {
    uint32_t mWord[4];
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    __forceinline ValidityBits& set(uint32_t i, bool value) {
        if (i < 128) {
            if (value)
                DoGetWord(i) |= (1u << (i % 32));
            else
                DoGetWord(i) &= ~(1u << (i % 32));
        }
        return *this;
    }
};

enum { kValidityTooComplex = 0 };

struct RefCounted {
    virtual int AddRef();
    virtual int Release();
};

template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T** GetAddress();               // @ 0x0041d870 (releases, returns &mpObject)
    T** AsPPointer() { return GetAddress(); }
};

struct Property {
    char pad[0x12];
    uint16_t mType;                 // +0x12 (1 = bool, 9 = int32, 0xd = float)
    bool* GetBool();                // @ 0x0041e920
    int* GetInt32();                // @ 0x0041e990
    float* GetFloat();              // @ 0x0041ea70
};

struct cPropertyList : RefCounted {
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property*& out);   // +0x24
};

struct cPropertyManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual bool GetPropertyList(uint32_t id, uint32_t group, cPropertyList** ppOut);   // +0x2c
};
cPropertyManager* PropertyManager();                 // @ 0x0067de30
uint32_t GetConfigFromModelType(uint32_t modelType); // @ 0x00432f10
extern uint32_t kEditorConfigGroup;                  // 0x015daa00

// Resource/model manager: +0x6c returns the model complexity of a rigblock property list.
struct cModelManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26();
    virtual float GetComplexity(cPropertyList* pList);                           // +0x6c
};
cModelManager* ModelManager();      // @ 0x00401010

// One rigblock record of the editor model (0x1d8 bytes; copy ctor out of line).
struct cEditorModelBlock {
    uint32_t mGroupID;              // +0x00
    uint32_t mInstanceID;           // +0x04
    uint32_t pad08;
    int mSymmetricParent;           // +0x0c (-1 = none)
    uint32_t pad10[(0x80 - 0x10) / 4];
    char pad80;
    bool mbIsSymmetric;             // +0x81
    char pad82[2];
    uint32_t pad84[(0x1d8 - 0x84) / 4];
    cEditorModelBlock(const cEditorModelBlock& o);  // @ 0x004721e0
};

struct BlockVec {
    cEditorModelBlock* mpBegin;
    cEditorModelBlock* mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
    cEditorModelBlock& operator[](int i) { return mpBegin[i]; }
};

struct cEditorModel {
    uint32_t pad0[6];
    uint32_t mModelType;            // +0x18
    uint32_t pad1[(0x98 - 0x1c) / 4];
    BlockVec mBlocks;               // +0x98
};

inline void GetPropertyInt(cPropertyList* pList, uint32_t id, int& dst) {
    Property* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == 9)
        dst = *prop->GetInt32();
}
inline void GetPropertyFloat(cPropertyList* pList, uint32_t id, float& dst) {
    Property* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == 0xd)
        dst = *prop->GetFloat();
}
inline void GetPropertyBool(cPropertyList* pList, uint32_t id, bool& dst) {
    Property* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == 1)
        dst = *prop->GetBool();
}


// @ 0x004f1350
bool TestComplexity(cEditorModel* model, ValidityBits* validity)
{
    BlockVec* n20 = &model->mBlocks;   // blocks
    float v1 = 0.0f;   // max complexity cost (0x066f72ae)
    bool self = false;   // symmetric copies count double (0x300dd020)

    uint32_t r = model->mModelType;   // model type
    AutoRefCount<cPropertyList> p28;   // editor config property list
    PropertyManager()->GetPropertyList(GetConfigFromModelType(r), kEditorConfigGroup,
                                       p28.AsPPointer());
    if (!p28) {
        if (validity)
            validity->set(kValidityTooComplex, true);
        return false;
    }

    int mid;   // limit 0x9187aee3
    int t30;   // limit 0x047c1d1b
    int p;   // limit 0x04dbc51f
    int j;   // max bones (0x0684a675)
    if (p28) {
        GetPropertyInt(p28, 0x9187aee3, mid);
        GetPropertyInt(p28, 0x047c1d1b, t30);
        GetPropertyInt(p28, 0x04dbc51f, p);
        GetPropertyFloat(p28, 0x066f72ae, v1);
        GetPropertyInt(p28, 0x0684a675, j);
        GetPropertyBool(p28, 0x300dd020, self);
    }

    int n = 0;   // total of 0x51fa9dfa
    int obj = 0;   // total of 0x3c652302
    int n29 = 0;   // total of 0x04460b63 flags
    float n18 = 0.0f;   // total complexity cost
    int v15 = 0;   // total bones
    bool hash = false;   // block not counted (0x02437197)
    for (int loopI = 0, loopN = n20->size(); loopI < loopN; loopI++) {
        cEditorModelBlock t12((*n20)[loopI]);   // block copy
        AutoRefCount<cPropertyList> p10;   // block property list
        PropertyManager()->GetPropertyList(t12.mInstanceID, t12.mGroupID,
                                           p10.AsPPointer());
        if (!p10) {
            if (validity)
                validity->set(kValidityTooComplex, true);
            return false;
        }

        int chunk = 0;   // block 0x51fa9dfa
        int w = 0;   // block 0x3c652302
        int n34 = 0;   // block 0x04460b63
        int p39 = 1;   // block bones
        float src = 0.0f;   // block complexity cost
        bool last = false;   // block has no symmetric copy (0xafff3a14)
        if (p10) {
            hash = false;
            GetPropertyBool(p10, 0x02437197, hash);
            if (hash)
                continue;
            GetPropertyInt(p10, 0x51fa9dfa, chunk);
            GetPropertyInt(p10, 0x3c652302, w);
            GetPropertyInt(p10, 0x04460b63, n34);
            GetPropertyBool(p10, 0xafff3a14, last);
            src = ModelManager()->GetComplexity(p10);
        }

        if (n34 != 2)
            n34 = 1;
        else
            n34 = 0;

        if (self && !last && t12.mSymmetricParent == -1 && !t12.mbIsSymmetric) {
            chunk *= 2;
            w *= 2;
            n34 *= 2;
            src *= 2.0f;
            p39 *= 2;
        }

        n29 += n34;
        obj += w;
        n += chunk;
        n18 += src;
        v15 += p39;
    }

    if (p != -1 && n29 > p) {
        if (validity)
            validity->set(kValidityTooComplex, true);
        return false;
    }
    if (mid != -1 && n > t30) {
        if (validity)
            validity->set(kValidityTooComplex, true);
        return false;
    }
    if (t30 != -1 && obj > mid) {
        if (validity)
            validity->set(kValidityTooComplex, true);
        return false;
    }
    if (v1 > 0.0f && n18 > v1) {
        if (validity)
            validity->set(kValidityTooComplex, true);
        return false;
    }
    if (j > 0.0f && v15 > j) {
        if (validity)
            validity->set(kValidityTooComplex, true);
        return false;
    }

    if (validity)
        validity->set(kValidityTooComplex, false);
    return true;
}
