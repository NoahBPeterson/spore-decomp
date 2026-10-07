// slice s007a7210  --  SP::cGraphicsSystem::CreateBuiltinModels (2852 bytes).
// Reconstructed C++ (MSVC x86, cl 15.00 /O2 /MD /Gy /EHsc /TP /arch:SSE).
//
// Builds the 15 built-in debug/primitive models: one shared cIMeshBuilder is filled by a
// mesh-generator helper per model, a new cGameModelResource ("Graphics" heap, 0x140 bytes)
// is push_back'ed into mBuiltinModels, the builder's mesh data is compiled into it
// (FUN_0072c0a0) and it is registered under its instance id in group 0xd94352ed.
#include "types.h"

void* operator new(unsigned int n, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);
void  operator delete(void* p, const char* name, int flags, unsigned debugFlags,
                      const char* file, int line);

namespace EA {
template <typename T>
class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
    T* get() const { return mpObject; }
};
}

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float a, float b, float c) : x(a), y(b), z(c) {}
    cSPVector3 operator-() const { return cSPVector3(-x, -y, -z); }
};

namespace SP {

class cMeshData;

// vtable: 0 AddRef, 1 Release, ..., 0xac/4 = 43 GetMeshData
class cIMeshBuilder {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual void v02() = 0; virtual void v03() = 0; virtual void v04() = 0; virtual void v05() = 0;
    virtual void v06() = 0; virtual void v07() = 0; virtual void v08() = 0; virtual void v09() = 0;
    virtual void v10() = 0; virtual void v11() = 0; virtual void v12() = 0; virtual void v13() = 0;
    virtual void v14() = 0; virtual void v15() = 0; virtual void v16() = 0; virtual void v17() = 0;
    virtual void v18() = 0; virtual void v19() = 0; virtual void v20() = 0; virtual void v21() = 0;
    virtual void v22() = 0; virtual void v23() = 0; virtual void v24() = 0; virtual void v25() = 0;
    virtual void v26() = 0; virtual void v27() = 0; virtual void v28() = 0; virtual void v29() = 0;
    virtual void v30() = 0; virtual void v31() = 0; virtual void v32() = 0; virtual void v33() = 0;
    virtual void v34() = 0; virtual void v35() = 0; virtual void v36() = 0; virtual void v37() = 0;
    virtual void v38() = 0; virtual void v39() = 0; virtual void v40() = 0; virtual void v41() = 0;
    virtual void v42() = 0;
    virtual cMeshData* GetMeshData() = 0;   // +0xac
};

class cGameModelResource {
public:
    virtual int AddRef();
    virtual int Release();
    cGameModelResource();                    // 0x007004d0
    uint32_t mData[0x13c / 4];
};

cIMeshBuilder* CreateMeshBuilder();                                                  // 0x00715de0
void CreateBoxMesh(cIMeshBuilder* mb, const cSPVector3& vmin, const cSPVector3& vmax);  // 0x0071cde0
void CreateMesh_c900(cIMeshBuilder* mb);                                             // 0x0071c900
void CreateDiscMesh(cIMeshBuilder* mb, float radius, int segments);                 // 0x0071c9e0
void CreateQuadMesh(cIMeshBuilder* mb, const cSPVector3& vmin, const cSPVector3& vmax); // 0x0071cc20
void CreateMesh_d550(cIMeshBuilder* mb, float a, float b, int c, int d, int e, int f); // 0x0071d550
void CreateMesh_d960(cIMeshBuilder* mb, float a, float b, int c, int d);           // 0x0071d960
void CreateArrowheadMesh(cIMeshBuilder* mb, float size);                            // 0x0071d0d0
void CreateMesh_d2f0(cIMeshBuilder* mb, float size);                                // 0x0071d2f0
void CompileMeshData(cMeshData* data, cGameModelResource* model, int a, int b);     // 0x0072c0a0
bool RegisterModel(cGameModelResource* model, uint32_t instanceID, uint32_t groupID); // 0x00754310

extern const cSPVector3 kOneVector;   // 0x0153b70c  (1,1,1)

struct BuiltinModelVector {
    EA::AutoRefCount<cGameModelResource>* mpBegin;
    EA::AutoRefCount<cGameModelResource>* mpEnd;
    EA::AutoRefCount<cGameModelResource>* mpCapacity;
    uint32_t mAllocator;

    void reserve(unsigned int n);                                         // 0x007658f0
    void push_back(const EA::AutoRefCount<cGameModelResource>& value);    // 0x007a6ac0
    EA::AutoRefCount<cGameModelResource>& back() { return *(mpEnd - 1); }
};

class cGraphicsSystem {
public:
    uint32_t pad00[0x40 / 4];
    BuiltinModelVector mBuiltinModels;   // +0x40

    void CreateBuiltinModels();
    void AddBuiltinModel(cIMeshBuilder* mb, uint32_t instanceID);
};

static const uint32_t kBuiltinModelGroup = 0xd94352ed;

__forceinline void cGraphicsSystem::AddBuiltinModel(cIMeshBuilder* mb, uint32_t instanceID)
{
    {
        cGameModelResource* model = new ("Graphics", 0, 0, 0, 0) cGameModelResource();
        mBuiltinModels.push_back(model);
    }
    CompileMeshData(mb->GetMeshData(), mBuiltinModels.back(), -1, 0);
    RegisterModel(mBuiltinModels.back(), instanceID, kBuiltinModelGroup);
}

// @ 0x007a7210  SP::cGraphicsSystem::CreateBuiltinModels
void cGraphicsSystem::CreateBuiltinModels()
{
    mBuiltinModels.reserve(16);

    EA::AutoRefCount<cIMeshBuilder> mb(CreateMeshBuilder());

    {
        cSPVector3 boxMin(-0.1f, -0.1f, -0.1f);
        cSPVector3 boxMax(0.1f, 0.1f, 0.1f);
        CreateBoxMesh(mb, boxMin, boxMax);
    }
    AddBuiltinModel(mb, 0x1565205f);

    CreateMesh_c900(mb);
    AddBuiltinModel(mb, 0x2ebcd6a6);

    CreateDiscMesh(mb, 1.0f, 10);
    AddBuiltinModel(mb, 0xcf571b4e);

    CreateDiscMesh(mb, 1.0f, 64);
    AddBuiltinModel(mb, 0xcd672bca);

    CreateQuadMesh(mb, cSPVector3(-1.0f, -1.0f, 0.0f), cSPVector3(1.0f, 1.0f, 0.0f));
    AddBuiltinModel(mb, 0xf24b36e0);

    CreateBoxMesh(mb, -kOneVector, kOneVector);
    AddBuiltinModel(mb, 0x2099b900);

    CreateMesh_d550(mb, 1.0f, 4.0f, 10, 2, 2, 0);
    AddBuiltinModel(mb, 0xc7862c87);

    CreateMesh_d960(mb, 1.0f, 4.0f, 1, 10);
    AddBuiltinModel(mb, 0xddc5a098);

    CreateArrowheadMesh(mb, 1.0f);
    AddBuiltinModel(mb, 0x7990c40a);

    CreateMesh_d2f0(mb, 1.0f);
    AddBuiltinModel(mb, 0xafa8492a);

    CreateDiscMesh(mb, 1.0f, 16);
    AddBuiltinModel(mb, 0xd622470c);

    CreateDiscMesh(mb, 1.0f, 32);
    AddBuiltinModel(mb, 0xd622470f);

    CreateDiscMesh(mb, 1.0f, 48);
    AddBuiltinModel(mb, 0xd622470e);

    CreateDiscMesh(mb, 1.0f, 64);
    AddBuiltinModel(mb, 0xd6224709);

    CreateDiscMesh(mb, 1.0f, 96);
    AddBuiltinModel(mb, 0xd6224708);
}

}  // namespace SP
