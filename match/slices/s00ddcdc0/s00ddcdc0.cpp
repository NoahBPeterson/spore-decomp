// Slice s00ddcdc0: scene setup helper at 0x00ddd1a0 (PDB candidate "`anonymous namespace'::CreateCreature").
// Fetches the shared light and three preview models from the model/lighting managers, binds the models
// to the light and a layer, resets seven global name tables, then runs an object-template query and
// copies the uint32 array of one property into a global SimpleVector.
//
// Flags: /O2 /MD /Gy /TP (no /EHsc: locals with destructors get no EH frame in this module).
#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);   // CRT memcpy (0x011e0744)
#pragma intrinsic(memcpy)
void __cdecl EASTL_allocator_deallocate(void* p);                               // 0x00f47380

// ---- reserved virtual slots (placeholders so the real slots land at the original offsets) ----------
#define V1(n) virtual void n();
#define V4(p) V1(p##0) V1(p##1) V1(p##2) V1(p##3)
#define V16(p) V4(p##0) V4(p##1) V4(p##2) V4(p##3)

template <class T>
struct AutoRef {
    T* mp;
    AutoRef() : mp(0) {}
    AutoRef& operator=(T* p)
    {
        T* old = mp;
        if (p != old) {
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
        return *this;
    }
    T* operator->() const { return mp; }
    T** AsOutParam()
    {
        if (mp) {
            T* t = mp;
            mp = 0;
            t->Release();
        }
        return &mp;
    }
    ~AutoRef() { if (mp) mp->Release(); }
};

struct IRef {
    virtual int AddRef();       // +0x00
    virtual int Release();      // +0x04
};

struct ILight : IRef {
    V4(l0) V4(l1) V1(l2) V1(l3)                                   // slots 2..11
    virtual void SetName(uint32_t id);                            // +0x30
};

struct ILayer : IRef {
    V4(y0) V1(y1)                                                 // slots 2..6
    virtual void AddModel(void* model, int a, int b, int c, int d);   // +0x1c
};

struct IModelWorld {
    V16(w0) V1(w1) V1(w2) V1(w3)                                  // slots 0..18
    virtual void SetModelType(int type);                          // +0x4c
};

struct IModel : IRef {
    V16(m0) V16(m1) V16(m2) V16(m3) V4(m4) V4(m5) V1(m6) V1(m7) V1(m8)   // slots 2..76
    virtual void SetFlag(int on);                                 // +0x134
    V1(m9)                                                        // +0x138
    virtual int GetModelType(int a, int b);                       // +0x13c
    virtual void Attach(ILight* light, int a, int b);             // +0x140
};

struct ILightMgr {
    V4(a0) V1(a1) V1(a2)                                          // slots 0..5
    virtual ILight* GetLight(uint32_t key, int a, int b);         // +0x18
};
struct IModelMgr {
    V4(a0) V1(a1)                                                 // slots 0..4
    virtual IModel* GetModel(uint32_t key, int a, int b);         // +0x14
};
struct ILayerMgr {
    V4(a0) V4(a1)                                                 // slots 0..7
    virtual ILayer* GetLayer(const wchar_t* name);                // +0x20
};

ILightMgr* LightingManager();                    // 0x0067dd90
IModelMgr* ModelManager();                       // 0x0067dd80
IModelWorld* ModelWorld();                       // 0x0067dd50
ILayerMgr* LayerManager();                       // 0x0067cb20
extern const wchar_t kLayerName[];               // 0x0147d2d8

// ---- eastl-style containers ----------------------------------------------------------------------
struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
    sp_vector_allocator() {}
};

inline void FreeArray(void* p)
{
    if (p) {
        if (((int*)p)[-1])
            EASTL_allocator_deallocate(p);
    }
}

// Pointer-sized element vectors: the seven global name tables and one uint32 SimpleVector.
template <class T>
struct PtrVecBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    static T* copy_memcpy(T* first, T* last, T* result)
    {
        return (T*)((last - first) * sizeof(T) + (char*)memcpy(result, first, (char*)last - (char*)first));
    }
    T* erase(T* first, T* last)
    {
        T* position = copy_memcpy(last, mpEnd, first);
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};

struct NameVec : PtrVecBase<const char**> {
    void DoInsertValue(const char*** pos, const char** const& value);   // 0x00b96600
    void push_back(const char** const& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) const char**(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

struct ValueVec : PtrVecBase<uint32_t> {
    void DoInsertValue(uint32_t* pos, const uint32_t& value);           // 0x004558a0
    void push_back(const uint32_t& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) uint32_t(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

namespace SP {
namespace FunctionalMatch {
struct Constraint;
}
}

struct ConstraintVec {
    SP::FunctionalMatch::Constraint* mpBegin;
    SP::FunctionalMatch::Constraint* mpEnd;
    SP::FunctionalMatch::Constraint* mpCapacity;
    sp_vector_allocator mAllocator;
    ConstraintVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~ConstraintVec();
    void DoDestroyValues(SP::FunctionalMatch::Constraint* first, SP::FunctionalMatch::Constraint* last);  // 0x004e39a0
    void DoInsertValue(SP::FunctionalMatch::Constraint* pos, const SP::FunctionalMatch::Constraint& v);   // 0x004e39d0
    void push_back(const SP::FunctionalMatch::Constraint& value);
};

namespace SP {
namespace FunctionalMatch {
enum EqualConstraint { kEquals = 0 };
struct Constraint {
    unsigned int mParameter;
    int mType;
    int mMin;
    int mMax;
    ConstraintVec mConstraints;
    Constraint(unsigned int param, EqualConstraint, int value);   // 0x00558960
    Constraint(const Constraint& other);                          // 0x00606880
    ~Constraint()
    {
        mConstraints.DoDestroyValues(mConstraints.mpBegin, mConstraints.mpEnd);
        FreeArray(mConstraints.mpBegin);
    }
};
}
}

inline void ConstraintVec::push_back(const SP::FunctionalMatch::Constraint& value)
{
    if (mpEnd < mpCapacity)
        ::new (mpEnd++) SP::FunctionalMatch::Constraint(value);
    else
        DoInsertValue(mpEnd, value);
}

inline ConstraintVec::~ConstraintVec()
{
    DoDestroyValues(mpBegin, mpEnd);
    FreeArray(mpBegin);
}

struct ResourceKey {
    uint32_t mInstanceID, mTypeID, mGroupID;
};
struct KeyVec {
    ResourceKey* mpBegin;
    ResourceKey* mpEnd;
    ResourceKey* mpCapacity;
    sp_vector_allocator mAllocator;
    KeyVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~KeyVec() { FreeArray(mpBegin); }
};

class cISPObjectTemplateDB {
public:
    V4(d0) V4(d1) V4(d2) V1(d3) V1(d4)                            // slots 0..13
    virtual void FindAssets(KeyVec& results, const ConstraintVec& query);   // +0x38
};
cISPObjectTemplateDB* ObjectTemplateDB();                         // 0x0067cb40

struct IPropertyManager {
    V4(p0) V4(p1) V1(p2) V1(p3) V1(p4)                            // slots 0..10
    virtual bool GetPropertyList(uint32_t id, uint32_t group, IRef** out);   // +0x2c
};
IPropertyManager* PropertyManager();                              // 0x0067de30
bool GetPropertyAsUint32Array(IRef* list, uint32_t id, int* count, uint32_t** data);   // 0x006a0840

// ---- globals -------------------------------------------------------------------------------------
extern const char* gName15a2db0;     // 0x015a2db0
extern const char* gName15a2db4;     // 0x015a2db4
extern const char* gName15a2dbc;     // 0x015a2dbc
extern const char* gName15a2dc8;     // 0x015a2dc8
extern const char* gName15a2dcc;     // 0x015a2dcc
extern const char* gName15a2dd0;     // 0x015a2dd0
extern const char* gName15a2dd4;     // 0x015a2dd4
extern const char* gName15a2dd8;     // 0x015a2dd8
extern const char* gName15a2ddc;     // 0x015a2ddc
extern uint32_t gPropKey;            // 0x015a2df8

extern NameVec gNames0bb0;           // 0x016a0bb0
extern NameVec gNames0bc4;           // 0x016a0bc4
extern NameVec gNames0bd8;           // 0x016a0bd8
extern NameVec gNames0bec;           // 0x016a0bec
extern NameVec gNames0c00;           // 0x016a0c00
extern NameVec gNames0c14;           // 0x016a0c14
extern NameVec gNames0c28;           // 0x016a0c28
extern ValueVec gValues0b90; // 0x016a0b90

struct cModelSetup {
    uint32_t pad0[0x14 / 4];
    AutoRef<IModel> mModelC;         // +0x14
    AutoRef<IModel> mModelA;         // +0x18
    AutoRef<IModel> mModelB;         // +0x1c
    AutoRef<ILight> mLight;          // +0x20
    uint32_t pad24[(0x70 - 0x24) / 4];
    AutoRef<ILayer> mLayer;          // +0x70

    void Setup();
};

// @ 0x00ddd1a0
void cModelSetup::Setup()
{
    IModelMgr* modelMgr = ModelManager();
    ILightMgr* lightMgr = LightingManager();
    mLight = lightMgr->GetLight(0x07b6877f, 0, 0);
    mLight->SetName(0x74d2735b);

    mModelA = modelMgr->GetModel(0x07b6877e, 0, 0);
    IModelWorld* w1 = ModelWorld(); w1->SetModelType(mModelA->GetModelType(0x14, 0));
    mModelA->SetFlag(1);
    mModelA->Attach(mLight.mp, 0, 1);

    mModelB = modelMgr->GetModel(0x07d23d15, 0, 0);
    IModelWorld* w2 = ModelWorld(); w2->SetModelType(mModelB->GetModelType(0x1a, 0));
    mModelB->SetFlag(1);
    mModelB->Attach(mLight.mp, 0, 1);

    mModelC = modelMgr->GetModel(0x07d23d13, 0, 0);
    IModelWorld* w3 = ModelWorld(); w3->SetModelType(mModelC->GetModelType(0xd, 0));
    mModelC->SetFlag(1);
    mModelC->Attach(mLight.mp, 0, 1);

    mLayer = LayerManager()->GetLayer(kLayerName);
    mLayer->AddModel(mModelA.mp, 1, 1, 1, 0);

    const char** n;
    gNames0bb0.clear();
    n = &gName15a2dc8; gNames0bb0.push_back(n);
    gNames0bd8.clear();
    n = &gName15a2dcc; gNames0bd8.push_back(n);
    gNames0bec.clear();
    n = &gName15a2dd4; gNames0bec.push_back(n);
    gNames0c00.clear();
    n = &gName15a2dd8; gNames0c00.push_back(n);
    gNames0c14.clear();
    n = &gName15a2db4; gNames0c14.push_back(n);
    n = &gName15a2ddc; gNames0c14.push_back(n);
    n = &gName15a2dbc; gNames0c14.push_back(n);
    gNames0c28.clear();
    n = &gName15a2dc8; gNames0c28.push_back(n);
    n = &gName15a2db0; gNames0c28.push_back(n);
    gNames0bc4.clear();
    n = &gName15a2dd0; gNames0bc4.push_back(n);

    ConstraintVec query;
    query.push_back(SP::FunctionalMatch::Constraint(0x02dd90af, SP::FunctionalMatch::kEquals, 0x2b978c46));
    query.push_back(SP::FunctionalMatch::Constraint(0x54a32960, SP::FunctionalMatch::kEquals, 1));
    KeyVec results;
    ObjectTemplateDB()->FindAssets(results, query);

    AutoRef<IRef> propList;
    if (PropertyManager()->GetPropertyList(gPropKey, 0, propList.AsOutParam())) {
        int count;
        uint32_t* data;
        if (GetPropertyAsUint32Array(propList.mp, 0x7a35112f, &count, &data)) {
            gValues0b90.clear();
            for (int i = 0; i < count; ++i)
                gValues0b90.push_back(data[i]);
        }
    }
}
