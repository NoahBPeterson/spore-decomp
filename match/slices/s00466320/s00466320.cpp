// Slice s00466320: SP::EditorUtils::ExportBakedModelToXMF (0x00466690, 1936 bytes, /Od) next to 0x00466320.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (no /EHsc: RAII locals but no EH frame).
//
// Exports a baked editor model as "<dir>/<name>.xmf" (via nSPSkinner::cExportHelper: dummy static skeleton, then one
// mesh gathered by MeshAccum::Export) and writes its diffuse / normal-map / bake-info textures next to it as TGA files.
#include "types.h"

// ---------------------------------------------------------------------------------------------
// strings / containers (shared stub shapes with s004629e0)
// ---------------------------------------------------------------------------------------------
struct CtorSprintf {};
struct wstring {                                           // eastl::basic_string<wchar_t>
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    int      mAllocator;
    wstring(CtorSprintf tag, const wchar_t* fmt, ...);     // 0x473020
    ~wstring() { DeallocateSelf(); }
    void DeallocateSelf();                                 // 0x4237d0
};
struct cstring {                                           // eastl::basic_string<char>
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    int   mAllocator;
    cstring(CtorSprintf tag, const char* fmt, ...);        // 0x472f50
    ~cstring();                                            // 0x530670
};

struct AllocTag { AllocTag() {} };
struct ModelPtr {                                          // intrusive_ptr element
    unsigned int mpObject;
};
struct ModelVec {                                          // vector<intrusive_ptr<..>> (RefVector), 0x14 bytes
    ModelPtr* mpBegin;
    ModelPtr* mpEnd;
    ModelPtr* mpCapacity;
    int mAllocator[2];
    explicit ModelVec(const AllocTag& a);                  // 0x540470
    ~ModelVec();                                           // 0x41eb80
    ModelPtr* end() const { ModelPtr* e = mpEnd; return e; }
};

namespace EA { namespace IO {
bool SplitPath(const wchar_t* pPath, wchar_t* pDrive, wchar_t* pDirectory, wchar_t* pFileName,
               wchar_t* pExtension, int nCapacity);        // 0x930180
} }

// ---------------------------------------------------------------------------------------------
// objects
// ---------------------------------------------------------------------------------------------
struct EditorModel {
    const wchar_t* GetFileName();                          // 0x4ae000 (returns +0x7c)
};
struct ResourceKey {
    unsigned int instanceID;                               // +0
    unsigned int typeID;                                   // +4
    unsigned int groupID;                                  // +8
};

struct Transform {                                         // 0x38 bytes
    char mData[0x38];
    Transform();                                           // 0x409930
};

struct MeshAccum;                                          // ExportHelperB (0x78 bytes)
struct cExportHelper {                                     // ExportHelperA (0xa8 bytes)
    char mData[0xa8];
    cExportHelper();                                       // 0x464300
    ~cExportHelper();                                      // 0x464480
    void SetName(const wchar_t* path);                     // 0x4fe860
    void ExportDummyStaticSkeleton();                      // 0x5001c0
    void ExportMeshBegin(unsigned int numSubmeshes, bool ascii);   // 0x500880
    void ExportMeshEnd();                                  // 0x501200
};
struct MeshAccum {
    char mData[0x78];
    MeshAccum();                                           // 0x464580
    ~MeshAccum();                                          // 0x464680
    void Export(cExportHelper* helper, const ModelVec& models);    // 0x466e20
};

struct ModelInst;
struct InstArg {                                           // by-value pointer argument
    ModelInst* mp;
    InstArg(ModelInst* p) : mp(p) {}
};
// Intrusively counted model objects (count at +4).
struct ModelRoot {                                         // 0x100 bytes, ctor 0x740e90
    void* vt;
    int   mnRefCount;
    char  pad8[0x100 - 8];
    ModelRoot();                                           // 0x740e90
    int AddRef() { int n = mnRefCount + 1; mnRefCount = mnRefCount + 1; return n; }
    void Release();                                        // EA::RefCountTemplate<int>::Release 0x453540
    void Init(struct IResource* res);                      // 0x742b30
    void SetInstance(struct ModelInst* inst);              // 0x73ab40
    void Collect(Transform* xf, ModelVec* out);            // 0x743270
};
struct ModelInst {                                         // cModelInstance, 0xa0 bytes, ctor 0x7400f0
    void* vt;
    int   mRefCount;
    char  pad8[0xa0 - 8];
    ModelInst();                                           // 0x7400f0
    int AddRef() { return mRefCount++ + 1; }
    void Release();                                        // 0x453540
    void SetFlags(bool a, bool b);                         // 0x73a800
    void ConstructFromGameModelResource(struct IResource* res);    // 0x742db0
};
void* operator new(unsigned int size, const char* pName, int flags, unsigned int debugFlags,
                   const char* pFile, int line);           // 0xf473a0
template <class T>
struct RefPtr {                                            // eastl::intrusive_ptr
    T* mpObject;
    RefPtr(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~RefPtr() { if (mpObject) mpObject->Release(); }
};
void PrepareModelImpl(unsigned int model);                 // 0x733ed0 (cdecl)
inline void PrepareModel(unsigned int model) { PrepareModelImpl(model); }

// ---------------------------------------------------------------------------------------------
// properties / resource manager / textures
// ---------------------------------------------------------------------------------------------
ResourceKey* DefaultModelKey();                            // 0x6bb640 (returns the address 0x1531cdc)
struct Property {
    char pad0[0x10];
    unsigned short mFlags;                                 // +0x10
    unsigned short mType;                                  // +0x12
    ResourceKey* AsKey();                                  // 0x446ff0 (thiscall)
};
inline ResourceKey* ModelKeyOf(Property* p)
{
    if (p->mType == 0x20 || p->mType == 0x10)
        return p->AsKey();
    return DefaultModelKey();
}
struct IRefCounted {
    virtual void AddRef();
    virtual void Release();                                // +4
};
struct IPropList : IRefCounted {
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8();
    virtual bool GetProperty(unsigned int id, Property** out);     // +0x24
};
struct IResource : IRefCounted {};

template <class T>
struct AutoRefCount {
    T* mp;
    ~AutoRefCount() { if (mp) mp->Release(); }
    void** AsPPVoidParam();                                // 0x41d870
    void** operator&() { return AsPPVoidParam(); }
    T* operator->() const { return mp; }
};
struct PropMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool GetPropList(unsigned int type, unsigned int group, void** out);   // +0x2c
};
PropMgr* GetPropMgr();                                     // 0x67de30
struct ResourceMan {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool GetResource(ResourceKey* key, void** out, int a, int b, int c, int d);   // +0xc
};
ResourceMan* GetManager();                                 // 0x67dcd0

struct TexData { int format; };
struct Tex {
    TexData* mpData; unsigned char mFlags;
};
struct TexMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void Load(Tex* t);                             // +0x34
};
TexMgr* GetTexMgr();                                       // 0x67dd60
struct TexId { int lo; int hi; };
struct TexIdMgr {                                          // 0x67dd40
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b(); virtual void v1c(); virtual void v1d();
    virtual void v1e(); virtual void v1f(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v2a(); virtual void v2b(); virtual void v2c();
    virtual void GetBakeInfoId(TexId* out);                // +0xb4
    virtual void GetNormalId(TexId* out);                  // +0xb8
    virtual void GetDiffuseId(TexId* out);                 // +0xbc
};
TexIdMgr* GetTexIdMgr();                                   // 0x67dd40
struct TexLookup {                                         // 0x67dda0
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6();
    virtual Tex* GetTexture(int lo, int hi);               // +0x1c
};
TexLookup* GetTexLookup();                                 // 0x67dda0
void SaveTga7b2380(const char* name, TexData* data);       // 0x7b2380 (cdecl)
inline TexData* DataOf(Tex* t)
{
    if (!(t->mFlags & 1)) GetTexMgr()->Load(t);
    return t->mpData;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00466320 (not yet decompiled)
// ---------------------------------------------------------------------------------------------
// @ 0x00466320
void F_00466320() {}

// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------
namespace SP { namespace EditorUtils {

// @ 0x00466690
void ExportBakedModelToXMF(EditorModel* model, const wchar_t* dir, ResourceKey* key)
{
    wchar_t nameTmp[260];
    EA::IO::SplitPath(model->GetFileName(), 0, 0, nameTmp, 0, 4);
    wstring fullPath(CtorSprintf(), L"%ls/%ls", dir, nameTmp);

    cExportHelper helperObj;
    MeshAccum accumA;
    helperObj.SetName(fullPath.mpBegin);
    helperObj.ExportDummyStaticSkeleton();

    AutoRefCount<IPropList> propsX;
    propsX.mp = 0;
    if (GetPropMgr()->GetPropList(key->instanceID, key->groupID, &propsX)) {
        unsigned int propIdOld = 0xf9efbb;
        Property* propOld = 0;
        if (propsX->GetProperty(propIdOld, &propOld)) {
            ResourceKey* resKeyY = ModelKeyOf(propOld);
            AutoRefCount<IResource> resC;
            resC.mp = 0;
            if (GetManager()->GetResource(resKeyY, &resC, 0, 0, 0, 0)) {
                Transform xfD;
                ModelVec modelsC((AllocTag()));
                IResource* rA = resC.mp;

                RefPtr<ModelRoot> rootTmp(new ("Graphics", 0, 0, 0, 0) ModelRoot());
                RefPtr<ModelInst> instC(new ("Graphics", 0, 0, 0, 0) ModelInst());
                rootTmp.mpObject->Init(rA);
                instC.mpObject->SetFlags(false, false);
                instC.mpObject->ConstructFromGameModelResource(rA);
                ModelInst* instArg = instC.mpObject;
                rootTmp.mpObject->SetInstance(instArg);
                rootTmp.mpObject->Collect(&xfD, &modelsC);
                for (ModelPtr* itObj = modelsC.mpBegin; itObj != modelsC.end(); ++itObj)
                    PrepareModel(itObj->mpObject);

                helperObj.ExportMeshBegin(1, false);
                accumA.Export(&helperObj, modelsC);
                helperObj.ExportMeshEnd();

                TexId diffuseIdCur; diffuseIdCur.lo = -1; diffuseIdCur.hi = -1;
                TexId normalId2;  normalId2.lo = -1;  normalId2.hi = -1;
                TexId bakeNew;    bakeNew.lo = -1;    bakeNew.hi = -1;
                GetTexIdMgr()->GetDiffuseId(&diffuseIdCur);
                Tex* tex = GetTexLookup()->GetTexture(diffuseIdCur.lo, diffuseIdCur.hi);
                GetTexIdMgr()->GetNormalId(&normalId2);
                Tex* imgTmp = GetTexLookup()->GetTexture(normalId2.lo, normalId2.hi);
                GetTexIdMgr()->GetBakeInfoId(&bakeNew);
                Tex* bakeTmp = GetTexLookup()->GetTexture(bakeNew.lo, bakeNew.hi);

                cstring diffuseNameD(CtorSprintf(), "%ls/%ls_Diffuse.tga", dir, nameTmp);
                SaveTga7b2380(diffuseNameD.mpBegin, DataOf(tex));
                cstring normalName2(CtorSprintf(), "%ls/%ls_NormalMap.tga", dir, nameTmp);
                SaveTga7b2380(normalName2.mpBegin, DataOf(imgTmp));
                cstring bakeNameX(CtorSprintf(), "%ls/%ls_BakeInfoMap.tga", dir, nameTmp);
                SaveTga7b2380(bakeNameX.mpBegin, DataOf(bakeTmp));
            }
        }
    }
}

} }
