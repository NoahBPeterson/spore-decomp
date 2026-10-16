// src/game/SPEngine/SPGraphicsMaterialManager.cpp -- migrated from slice(s) s00712e10, s00711de0, s00711220, s007101f0, s0070efa0, s0070de90, s006e51b0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsMaterialManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern "C" void ShaderStateUnlockHook();
#include <math.h>
#include "SP/cMaterialManager.h"
#include <new>
#include "EA/Thread/Mutex.h"
#include "EA/Audio/FactoryBinarySampleData.h"
#include "EA/ArgScript/cIFileParser.h"
#include "EA/Audio/IPrimitive.h"
#include "SP/cMaterialScriptState.h"
#include <string.h>
#include <intrin.h>
#pragma function(memcpy)

// ---- items of slice s006e51b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct SpriteRef {
    unsigned short type;   // +0
    unsigned short f1;     // +2
    unsigned short f2;     // +4
    unsigned short f3;     // +6
    unsigned short f4;     // +8
    unsigned short f5;     // +10
};
struct ShaderState;
extern "C" void ShaderStateUnlockHook();
__declspec(noinline) void __fastcall ShaderState_Destroy(ShaderState* self);
void operator_delete(void*);
struct SprVec {
    SpriteRef *b, *e, *c;     // begin / end / capacity
    int al[2];                // allocator
    SprVec() { b = 0; e = 0; c = 0; }          // 0x6e5790-style element constructor
    ~SprVec();                                 // 0x7a41a0
    void __thiscall Resize(unsigned int n);    // 0x6e5cd0
    SpriteRef* begin() { return b; }
    SpriteRef* end() { return e; }
    static __forceinline SpriteRef* CopyF(SpriteRef* f, SpriteRef* l, SpriteRef* d)
    {
        for (; f != l; ++f, ++d) {
            *d = *f;
        }
        return d;
    }
    __forceinline SpriteRef* erase(SpriteRef* first, SpriteRef* last)
    {
        SpriteRef* i = CopyF(last, e, first);
        e -= (last - first);
        return first;
    }
    void clear() { erase(begin(), end()); }
};
struct Res {
    void** vtbl;
    void Release() { ((void(__stdcall*)(Res*))vtbl[2])(this); }
};
struct Stream {
    void** vtbl;
    int Read(void* dst, int n) { return ((int(__fastcall*)(Stream*, int, void*, int))vtbl[12])(this, 0, dst, n); }
};
struct ShaderState {
    char    pad0[0x14];
    void*   dispatchCb;       // +0x14  SP::DirectShaderDispatchCallback
    char    pad1[0x20];
    int     f38, f3c, f40, f44;   // f3c: refcount
    Res*    vs[16];               // +0x48
    Res*    ps[16];               // +0x88
    SprVec  tabA[16];             // +0xc8
    SprVec  tabB[16];             // +0x208

    Res* GetVS(int i) { return vs[i]; }
    Res* GetPS(int i) { return ps[i]; }
    ShaderState();                // 0x6e57d0
    ~ShaderState();               // 0x6e56b0
    void Reset();                 // 0x6e5bd0
    bool __thiscall BaseRead(Stream* s, int a, int b);   // 0x777840 SP::cShaderBase::Read
    bool Read(Stream* s, int a, int b);                  // 0x6e5d50
};
// ---- items of slice s006e51b0 end

// ---- items of slice s0070de90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_device; // 0x016f89d0
struct Mat { char _p[0x18]; unsigned mID; };   // cMaterialInternal: mID at +0x18
struct cMaterialManager {
    int  GetIDFromMaterial(Mat* m);
    void GetIDsFromMaterials(int n, Mat** mats, unsigned* ids);
};
struct RC3c  { void AddRef(); void Release(); };
struct RC3b  { void AddRef(); void Release(); };
struct RC14  { int _pad[5]; int mCount; };
struct AutoRef14 { RC14* mpObject; void WeakRelease(); };
struct AutoRefA  { RC3c* mpObject; void Release(); };
struct AutoRefB  { RC3b* mpObject; void Release(); };
struct VObj {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual int  v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
};
struct Holder    { char _p[0xc]; VObj* mpObject; int Get(); };
#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
void* __cdecl EAlloc(size_t n, const char* name, int a, unsigned b, const char* file, int line); // 0x00f473a0
void __cdecl D3D_FlushSomeStates(void);                      // 0x006fd7b0
int  __cdecl ResSize(void* p);                               // 0x00777740
void __cdecl ResCopy(void* dst, int n, void* out);           // 0x00777720
void* __cdecl EAlloc8(size_t n, unsigned a, int b, int c, const char* d, int e, int f, int g); // 0x00f473d0
void __cdecl EFree2(void* p);                                // 0x00f47380
int  __cdecl WriteUint32Stub(void* s, void* d, int n, int f); // 0x0093aa70
void __cdecl FreeStreamStub(void* s);                        // 0x006fe430
void __cdecl FragDeclStub(void* s);                          // 0x006fa480
namespace __equiv_ann1 {
struct RC3b {
    void AddRef();   // 0x006e54c0 (equiv t3)
    void Release();   // 0x006fd300 (equiv t2)
};
}
namespace __equiv_ann1 {
struct RC3c {
    void AddRef();   // 0x006e54c0 (equiv t3)
    void Release();   // 0x006e57a0 (equiv t3)
};
}
// ---- items of slice s0070de90 end

// ---- items of slice s0070efa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl EFree(void* p);                                                                    // 0x00f47380
struct RC3c_s0070_efa0 { void AddRef(); void Release(); };  // refcount at +0x3c
struct RC3b_s0070_efa0 { void AddRef(); void Release(); };  // refcount at +0x3c (second family)
void** AssignCopyA(void** first, void** last, void** dst); // 0x0070e340
void** AssignCopyB(void** first, void** last, void** dst); // 0x0070e390
struct VecBase {
    void** mpBegin; void** mpEnd; void** mpCap;
    void DestroyRange(void** first, void** last);   // 0x70f520
};
struct VecA {
    void** mpBegin; void** mpEnd; void** mpCap;
    ~VecA();
    void Shrink(void** a, void** b);
};
struct VecB {
    void** mpBegin; void** mpEnd; void** mpCap;
    ~VecB();
    void Shrink(void** a, void** b);
};
struct FVecB { char _p[0x20]; void Teardown(); };
struct FVecC { char _p[0x24]; void Teardown(); };
struct HashNodeA { char _p[4]; RC3c_s0070_efa0* mpRef; HashNodeA* mpNext; };
struct HashNodeB { char _p[4]; RC3b_s0070_efa0* mpRef; HashNodeB* mpNext; };
struct Mutex  { void Lock(void* p); void Unlock(); };            // 0x009221b0 / 0x00922270
void* __cdecl ResGetManager(void);                               // 0x0067dcd0
void* __cdecl FindInMap(void* out, void* key);                   // 0x0070f690
int  __cdecl ReadInt32Stub(void*, void*, int, int);              // 0x0093a780
void __cdecl MiscD(void*, int);                                   // 0x006fc780
int  __cdecl ReadShaders_helper2(void*);                          // 0x006ff750
    void AssignCopyA(...); // 0x0070e340
    void AssignCopyB(...); // 0x0070e390
namespace __equiv_ann1 {
struct Mutex {
    void Unlock();   // 0x00922270 (equiv t2)
};
}
// ---- items of slice s0070efa0 end

// ---- items of slice s007101f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl EastlNew(uint32_t n, const char* name, int flags, int dbg, const char* file, int line);  // 0x00F473A0
void  __cdecl EastlFree(void* p);                                                                       // 0x00F47380
void* __cdecl MemMove(void* dst, const void* src, uint32_t n);                                          // 0x011E0744
void  __cdecl CopyBackwardRef(void* first, void* last, void* resultEnd);                                // 0x0070EC30
void  __cdecl EraseRef(void* first, void* last);                                                        // 0x0070FA60 / 0x0070FAB0
void  __cdecl DoInsertValuesRef(void* position, uint32_t n, const void* value);                         // 0x0070FB00 / 0x0070FD50
void* __cdecl ReallocRef(void* self, uint32_t n, const void* first, const void* last);                  // 0x00710190
void* __cdecl AssignCopyRef(void* first, void* last, void* dst);                                        // 0x006F43E0
void* __cdecl AssignMoveRef(void* out, void* first, void* last, void* dst, void* end);                  // 0x0070EA70
void  __cdecl DestroyRange0(void* first, void* last);                                                   // 0x0070F520
void* __cdecl HashtableFind10(void* self, const uint32_t* key, void* out);                              // 0x00645ED0
void  __cdecl HashtableInsert10(void* self, void* out, const void* value, uint8_t tag);                 // 0x0070F5A0
struct RefObj14 {
    char pad0[0x14];
    int32_t mnRefCount;                       // +0x14
    void AddRef() { ++mnRefCount; }
    void Release() { if (mnRefCount > 1) --mnRefCount; }
};
struct AutoRef14_s0071_01f0 {
    RefObj14* mpObject;
    AutoRef14_s0071_01f0(RefObj14* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRef14_s0071_01f0(const AutoRef14_s0071_01f0& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    AutoRef14_s0071_01f0& operator=(const AutoRef14_s0071_01f0& x)
    {
        RefObj14* pNew = x.mpObject;
        RefObj14* pOld = mpObject;
        if (pNew != pOld) {
            if (pNew) pNew->AddRef();
            mpObject = pNew;
            if (pOld) pOld->Release();
        }
        return *this;
    }
    ~AutoRef14_s0071_01f0() { if (mpObject) mpObject->Release(); }
};
struct VecFixed {
    AutoRef14_s0071_01f0* mpBegin;      // +0x00
    AutoRef14_s0071_01f0* mpEnd;        // +0x04
    AutoRef14_s0071_01f0* mpCapacity;   // +0x08
    uint32_t mAllocator[2];  // +0x0c (unused by this function)
    void DoFree(AutoRef14_s0071_01f0* p, uint32_t) { if (p && ((int32_t*)p)[-1] != 0) EastlFree(p); }
    uint32_t GetNewCapacity(uint32_t c) { return (c > 0) ? (c * 2) : 1; }
    AutoRef14_s0071_01f0* DoAllocate(uint32_t n)
    {
        return n ? (AutoRef14_s0071_01f0*)EastlNew(n * sizeof(AutoRef14_s0071_01f0), "Graphics", 0, 0,
                                        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
                 : 0;
    }
    void DoInsertValue(AutoRef14_s0071_01f0* position, const AutoRef14_s0071_01f0& value);
};
template <class T> inline T* UninitializedMovePtr(T* first, T* last, T* dest)
{
    return (T*)((last - first) * sizeof(T) + (char*)MemMove(dest, first, (uint32_t)((char*)last - (char*)first)));
}
struct RefObj8 {
    char pad0[8];
    int32_t mnRefCount;                       // +0x08
    void AddRef() { ++mnRefCount; }
    void Release() { if (mnRefCount > 1) --mnRefCount; }
};
struct AutoRef8 {
    RefObj8* mpObject;
    AutoRef8(RefObj8* p = 0) : mpObject(p) {}
    AutoRef8(const AutoRef8& x) : mpObject(x.mpObject) {}
    ~AutoRef8() { if (mpObject) mpObject->Release(); }
};
struct RefPtrVecGrow {
    void DoInsertValue(AutoRef8* position, const AutoRef8& value);
};
struct VecSp {
    AutoRef8* mpBegin;       // +0x00
    AutoRef8* mpEnd;         // +0x04
    AutoRef8* mpCapacity;    // +0x08
    uint32_t mAllocator[2];  // +0x0c
    void push_back();
};
struct VecResizeA {
    void* mpBegin;       // +0x00
    void* mpEnd;         // +0x04
    void* mpCapacity;    // +0x08
    uint32_t mAllocator[2];
    uint32_t size() const { return (uint32_t)((char*)mpEnd - (char*)mpBegin) >> 2; }
    void resize(uint32_t n);
};
struct VecResizeB {
    void* mpBegin;       // +0x00
    void* mpEnd;         // +0x04
    void* mpCapacity;    // +0x08
    uint32_t mAllocator[2];
    uint32_t size() const { return (uint32_t)((char*)mpEnd - (char*)mpBegin) >> 2; }
    void resize(uint32_t n);
};
struct VecAsn {
    void* mpBegin;       // +0x00
    void* mpEnd;         // +0x04
    void* mpCapacity;    // +0x08
    uint32_t mAllocator[2];
    void assign(const void* first, const void* last);
};
struct Tex4 {
    uint32_t mValue;
    ~Tex4();
};
struct MapA {
    uint32_t mField0[2];
    uint32_t* mpBucketArray;   // +0x04
    uint32_t mnBucketCount;    // +0x08
    uint32_t mField0c;
    uint8_t mEnd[8];
    Tex4& operator[](const uint32_t& key);
};
struct Mat4 {
    uint32_t mValue;
    ~Mat4();
};
struct MapB {
    uint32_t mField0[2];
    uint32_t* mpBucketArray;   // +0x04
    uint32_t mnBucketCount;    // +0x08
    uint32_t mField0c;
    uint8_t mEnd[8];
    Mat4& operator[](const uint32_t& key);
};
// ---- items of slice s007101f0 end

// ---- items of slice s00711220 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl DestroyRange(void* first, void* last);                                                    // 0x0070F520
struct VecResize {
    void* mpBegin;       // +0x00
    void* mpEnd;         // +0x04
    void* mpCapacity;    // +0x08
    uint32_t mAllocator[2];
    uint32_t size() const { return (uint32_t)((char*)mpEnd - (char*)mpBegin) >> 2; }
    void resize(uint32_t n);
};
struct FreeNode {
    int32_t m0;            // +0x00
    int32_t m4;            // +0x04
    int32_t m8;            // +0x08
    char pad[0x20 - 0x0c];
    FreeNode* mpNext;      // +0x20
};
struct TextureVec {
    void* mpBegin;       // +0x00
    void* mpEnd;         // +0x04
    void* mpCapacity;    // +0x08
    void* DoInsertValue();           // 0x00711170: appends a null element
};
struct TextureRef {
    char pad0[8];
    int32_t mnRefCount;             // +0x08
};
// ---- items of slice s00711220 end

// ---- items of slice s00711de0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_mutexParams;                  // DAT_0140C860 (relocated constant passed to Lock)
void __cdecl AssignRange(void* first, void* last, const void* tag); // 0x7106D0
struct Mutex_s0071_1de0 {
    char mData[0x40];
    void Lock(const void* pTimeout);       // 0x9221B0
    void Unlock();                          // 0x922270
};
struct MutexLock {
    Mutex_s0071_1de0* mpMutex;
    MutexLock(Mutex_s0071_1de0& m, const void* pTimeout) : mpMutex(&m) { m.Lock(pTimeout); }
    ~MutexLock() { mpMutex->Unlock(); }
};
struct MatMap {
    char mData[0x40];                       // +0x174 in the manager
    uint8_t& operator[](const uint32_t& key);   // 0x7129E0
};
struct MaterialManager3 {
    char pad0[0x174];
    MatMap mMap;                            // +0x174
    void* mpInvalidState;                   // +0x1b4
    char pad1[0x258 - 0x1b8];
    Mutex_s0071_1de0 mMutex;                           // +0x258

    bool HasMaterial(uint32_t key);
    uint8_t* GetMaterial(uint32_t key);
    void GetMaterials(int32_t n, const uint32_t* keys, void** out);
    uint8_t* GetMaterialInstance(uint32_t key, void* param3);
};
struct TailVec {
    void* mpBegin;         // +0x00
    void* mpEnd;           // +0x04
    void* mpCapacity;      // +0x08
    char pad0[4];          // +0x0c
    void* mpPoolBegin;     // +0x10
    char mBuffer[16];      // +0x14 inline elements (4 x 4 bytes)
    TailVec(const TailVec& src);
};
struct State27D0 {
    uint32_t m0[9];        // +0x00
    TailVec mVec;          // +0x24
    State27D0* CopyFrom(const State27D0& src);
};
struct State2850 {
    uint32_t m0[9];        // +0x00
    TailVec mVec;          // +0x24
    State2850* CopyFrom2(const State2850& a, const State2850& b);
};
struct FreeNode24 {
    int32_t m00;           // +0x00
    char pad0[0x24 - 0x04];
    void* mpBegin;         // +0x24
    void* mpEnd;           // +0x28
    char pad1[0x34 - 0x2c];
    void* mpCapacity;      // +0x34
    char pad2[0x4c - 0x38];
    FreeNode24* mpNext;    // +0x4c
};
struct HashStr {
    char pad0[4];
    uint32_t* mpBucketArray;   // +0x04 (relative to the embedded object)
    uint32_t mnBucketCount;    // +0x08
    uint32_t mnElementCount;   // +0x0c
    void DoFreeNodes(uint32_t* pNodes, uint32_t n);   // 0x6A85B0
};
struct FreeNodeStr {
    int32_t m00;           // +0x00
    char pad0[0x24 - 0x04];
    FreeNodeStr* mpNext;   // +0x24
    // The embedded string hashtable lives at +0x04:
    //   +0x08 bucket array, +0x0c bucket count, +0x10 element count
};
// ---- items of slice s00711de0 end

// ---- items of slice s00712e10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t gGroupMaterialsA;                        // 0x01535F64
extern uint32_t gGroupMaterialsB;                        // 0x01535F60
extern void* gEmptyBucketArray[2];                       // 0x0154DF28
extern char vtblMaterialManagerA[];                      // 0x0140C908
extern char vtblMaterialManagerB[];                      // 0x0140C904
extern char vtblMaterialManagerBaseA[];                  // 0x013EB938
extern char vtblMaterialManagerBaseB[];                  // 0x013EF094
extern char gEmptyStringChars[];                         // 0x01667BAC (empty string literal)
extern char gEmptyStringCharsEnd[];                      // 0x01667BAD
extern const char gMutexParams[];                        // 0x0140C860 (mutex parameter block; passed by address)
void* __cdecl GetResourceManager();                      // 0x0067DCD0 EA::ResourceMan::GetManager
void* __cdecl GetImageFactory();                         // 0x0067DD60
int __cdecl ReadInt32(void* stream, int* out, int count, int endian);  // 0x0093A780
int __cdecl ReadExact(void* stream, void* buf, int size);              // 0x0093A6C0
struct Mutex_s0071_2e10 {
    void Lock(const void* params);         // 0x009221B0
    void Unlock();                         // 0x00922270
    void Construct(int a, int b);          // 0x009222A0 (Mutex::Mutex)
    void Destroy();                        // 0x00922130 (Mutex::~Mutex)
};
struct Stopwatch {
    void Construct(int a, int b);          // 0x0093A560 (Stopwatch::Stopwatch)
};
struct HashTable {
    uint32_t pad0;
    void** mpBuckets;                      // +4
    uint32_t mnBuckets;                    // +8
    uint32_t mnElements;                   // +0xC
    float mfMaxLoad;                       // +0x10
    float mfGrowth;                        // +0x14
    uint32_t mnNextResize;                 // +0x18
    uint32_t pad1c;

    void InitEmpty()
    {
        mpBuckets = gEmptyBucketArray;
        mnBuckets = 1;
        mnElements = 0;
        mfMaxLoad = 1.0f;
        mfGrowth = 2.0f;
        mnNextResize = 0;
    }

    // distinct DoFreeNodes instantiations (void** buckets, uint count)
    void FreeNodes7112C0(void** a, uint32_t n);
    void FreeNodes70FF50(void** a, uint32_t n);
    void FreeNodes70FD00(void** a, uint32_t n);
    void FreeNodes712B20(void** a, uint32_t n);
    void FreeNodes6A85B0(void** a, uint32_t n);
    void FreeNodes693230(void** a, uint32_t n);
    void FreeNodes712320(void** a, uint32_t n);
};
struct TriWord {                           // small vector-like members destroyed without args
    uint32_t a, b, c;
    void Destroy70F390();
    void Destroy70F320();
};
struct IRefCounted {
    virtual void AddRef();                 // slot 0
    virtual void Release();                // slot 1
};
struct ResourceObject {                    // object cached at cMaterialManager+0x204
    virtual void AddRef();                 // slot 0
    virtual void Release();                // slot 1
    virtual void Slot2();
    virtual void* QueryResource(uint32_t type);   // slot 3 (+0xC)
    char pad[0x10];
    void* mpArena;                         // +0x18
};
struct ResourceManagerStub {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6();
    // slot 7 (+0x1C)
    virtual bool GetResource(const void* key, ResourceObject** out, int a, void* db, int b, int c);
};
struct ImageFactoryStub {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    // slot 8 (+0x20)
    virtual void* GetImage(int a, int b, int c);
};
struct StreamHolder {                      // result of the database lookup of the second key
    virtual void s0(); virtual void s1();
    virtual void Release();                // slot 2 (+8)
    virtual void s3(); virtual void s4(); virtual void s5();
    virtual void* GetStream();             // slot 6 (+0x18)
    virtual void s7(); virtual void s8();
    virtual void Close();                  // slot 9 (+0x24)
};
struct ResourceDatabaseStub {              // parameter of the loader (slot 13 / +0x34)
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12();
    virtual bool GetStream(const void* key, StreamHolder** out, int a, int b, int c, int d);
};
struct ResourceKey {
    uint32_t instance;
    uint32_t type;
    uint32_t group;
};
struct ExportElem {
    int a, b;
    ExportElem();                          // 0x006C0FA0
    ~ExportElem();                         // 0x00C2E4E0
};
struct ExportedObject {
    int type;                              // 0x2000B = texture
    int value;
    int pad8, padC, pad10, pad14;
    ExportElem elems[4];
};
void __stdcall GetExportedObjectByIndex(void* arena, int index, ExportedObject* out); // 0x011E28E0
struct ImageRef {                          // AutoRefCount<cTextureInstance> slot
    void* mpObject;
    void SetFromResource(void* res);       // 0x00576650 GetImageResource
};
struct TexVec {                            // vector<AutoRefCount<cTextureInstance>> at entry+0x20
    ImageRef* mpBegin;
    ImageRef* mpEnd;
    void resize(uint32_t n);               // 0x00711220
};
struct MaterialEntry;
struct EntryRef {                          // AutoRefCount<cMaterialInternal> temp
    MaterialEntry* mp;
    inline EntryRef(MaterialEntry* p);
    inline ~EntryRef();
};
struct MaterialEntry {                     // SP::cMaterialInternal (the used part)
    uint8_t mnFlags;                       // +0
    uint8_t pad1[3];
    uint32_t mFlags[4];                    // +4
    int mnRefCount;                        // +0x14
    uint32_t mnId;                         // +0x18
    uint32_t mnExternalId;                 // +0x1C
    TexVec mTextures;                      // +0x20
    void Unregister();                     // 0x00711380 UnregisterMaterial
};
inline EntryRef::EntryRef(MaterialEntry* p)
{
    mp = p;
    if (p)
        p->mnRefCount++;
}
inline EntryRef::~EntryRef()
{
    if (mp && mp->mnRefCount > 1)
        mp->mnRefCount--;
}
struct MaterialMap : HashTable {
    MaterialEntry* operator_index(const uint32_t* key);   // 0x007129E0 hash_map::operator[]
};
struct HashIter {                          // eastl hashtable_iterator (node, bucket)
    uint32_t* mpNode;
    void** mpBucket;
};
struct StateIdMap : HashTable {
    void find(HashIter* out, const uint32_t* key);        // 0x00645ED0 hashtable::find (writes both words)
    int* operator_index(const uint32_t* key);             // 0x0070F9D0
};
struct EntryVec {                          // fixed vector of AutoRefCount<cMaterialInternal> at +0x244
    MaterialEntry** mpBegin;
    MaterialEntry** mpEnd;
    MaterialEntry** mpCapacity;
    void DoDestroy(MaterialEntry** first, MaterialEntry** last);          // 0x0070E890
    void DoAssignFromIterator(MaterialEntry** pos, EntryRef* value);      // 0x007103E0

    inline void push_back(EntryRef& v)
    {
        MaterialEntry** pos = mpEnd;
        if (pos < mpCapacity) {
            mpEnd = pos + 1;
            if (pos) {
                *pos = v.mp;
                v.mp->mnRefCount++;
            }
        } else {
            DoAssignFromIterator(pos, &v);
        }
    }
};
struct PtrVec {                            // fixed vector<void*> at +0x1d8
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    uint32_t mAllocator;                   // +0xC (allocator word)
    void** mpLocal;                        // +0x10 (address of the inline buffer)
    uint32_t mPad14;                       // +0x14 (buffer starts at +0x18)
    void DoDestroy(void** first, void** last);   // 0x0070F520
};
struct cMaterialScriptState {
    uint32_t pad0;                         // +0
    ResourceObject* mInvalidTexture;       // +4
    HashTable mMap8;                       // +8
    HashTable mMap28;                      // +0x28
    HashTable mMap48;                      // +0x48
    HashTable mMap68;                      // +0x68
    TriWord m88;                           // +0x88
    uint32_t pad94, pad98;
    HashTable mMap9C;                      // +0x9c
    HashTable mMapBC;                      // +0xbc
    TriWord mDC;                           // +0xdc
    uint32_t padE8, padEC;
    HashTable mMapF0;                      // +0xf0
    char* mpLabelBegin;                    // +0x110
    char* mpLabelEnd;                      // +0x114
    char* mpLabelCapacity;                 // +0x118
    char pad11C[0x20];
    HashTable mMap13C;                     // +0x13c
    uint32_t pad15C[2];

    cMaterialScriptState();                // 0x007138F0
    ~cMaterialScriptState();               // 0x00713560
};
struct cMaterialManager_s0071_2e10 {
    void* mpVtblA;                         // +0
    void* mpVtblB;                         // +4
    uint32_t pad8;                         // +8
    IRefCounted* mpListener;               // +0xC
    cMaterialScriptState mScriptState;     // +0x10
    MaterialMap mMaterialsMap;             // +0x174
    StateIdMap mCompiledStateToIDMap;      // +0x194
    uint32_t pad1B4;
    uint8_t mb1B8;
    uint8_t pad1B9[0x13];
    uint32_t mn1CC;                        // +0x1CC
    int32_t mn1D0;                         // +0x1D0
    uint32_t mn1D4;
    PtrVec mPtrVec;                        // +0x1D8
    void* mLocalBuf[4];                    // +0x1F0
    uint32_t mn200;                        // +0x200 material id
    ResourceObject* mpResource;            // +0x204
    Stopwatch mStopwatch;                  // +0x208
    char pad209[0x17];
    uint32_t mn220;                        // +0x220
    uint32_t mn224, mn228, mn22C, mn230, mn234, mn238;
    uint8_t mb23C;
    char pad23D[3];
    uint32_t mnNextMaterialId;             // +0x240
    EntryVec mRegistered;                  // +0x244
    uint32_t pad250, pad254;
    Mutex_s0071_2e10 mMutex;                          // +0x258

    cMaterialManager_s0071_2e10();                    // 0x00713A80
    ~cMaterialManager_s0071_2e10();                   // 0x00713780
    uint32_t GetIDFromCompiledState(uint32_t state, uint32_t id);   // 0x00712E10
    void RegisterMaterial(uint32_t key, int nFlags, const uint32_t* flags, uint32_t nTex,
                          void** texRes);                           // 0x00712F50
    bool ReadExternalReferences(ResourceDatabaseStub* db);          // 0x00713070
};
// ---- items of slice s00712e10 end

// @ 0x006e57a0
int __fastcall ShaderState_Release(ShaderState* self)
{
    int n = *(int*)((char*)self + 0x3c) - 1;
    ShaderStateUnlockHook();
    if (n == 0) {
        ShaderState_Destroy(self);
        operator_delete(self);
    }
    return n;
}







// @ 0x006e5bd0
void ShaderState::Reset()
{
    for (int i = 0; i < 16; ++i) {
        if (vs[i]) {
            vs[i]->Release();
            vs[i] = 0;
        }
        if (ps[i]) {
            ps[i]->Release();
            ps[i] = 0;
        }
        tabA[i].clear();
        tabB[i].clear();
    }
}






// @ 0x0070e2c0
int cMaterialManager::GetIDFromMaterial(Mat* m)
{
    return m->mID;
}






// @ 0x0070e2d0
void cMaterialManager::GetIDsFromMaterials(int n, Mat** mats, unsigned* ids)
{
    for (int i = 0; i < n; i++)
        ids[i] = mats[i]->mID;
}






// @ 0x0070e300
void AutoRef14::WeakRelease()
{
    if (mpObject != 0)
    {
        int c = mpObject->mCount;
        if (c > 1)
            mpObject->mCount = c - 1;
    }
}






// @ 0x0070e320
void AutoRefA::Release()
{
    if (mpObject != 0)
        mpObject->Release();
}






// @ 0x0070e330
void AutoRefB::Release()
{
    if (mpObject != 0)
        mpObject->Release();
}






// @ 0x0070e340
void** AssignCopyA(void** first, void** last, void** dst)
{
    while (first != last)
    {
        void* src = *first;
        void* old = *dst;
        if (src != old)
        {
            if (src != 0)
                ((RC3c*)src)->AddRef();
            *dst = src;
            if (old != 0)
                ((RC3c*)old)->Release();
        }
        ++first;
        ++dst;
    }
    return dst;
}






// @ 0x0070e390
void** AssignCopyB(void** first, void** last, void** dst)
{
    while (first != last)
    {
        void* src = *first;
        void* old = *dst;
        if (src != old)
        {
            if (src != 0)
                ((RC3b*)src)->AddRef();
            *dst = src;
            if (old != 0)
                ((RC3b*)old)->Release();
        }
        ++first;
        ++dst;
    }
    return dst;
}






// @ 0x0070e3e0
void** CopyBackwardA(void** first, void** last, void** dstEnd)
{
    while (last != first)
    {
        void* s = last[-1];
        void* old = dstEnd[-1];
        --last;
        --dstEnd;
        if (s != old)
        {
            if (s != 0)
                ((RC3c*)s)->AddRef();
            *dstEnd = s;
            if (old != 0)
                ((RC3c*)old)->Release();
        }
    }
    return dstEnd;
}






// @ 0x0070e430
void** CopyBackwardB(void** first, void** last, void** dstEnd)
{
    while (last != first)
    {
        void* s = last[-1];
        void* old = dstEnd[-1];
        --last;
        --dstEnd;
        if (s != old)
        {
            if (s != 0)
                ((RC3b*)s)->AddRef();
            *dstEnd = s;
            if (old != 0)
                ((RC3b*)old)->Release();
        }
    }
    return dstEnd;
}






// @ 0x0070e4c0
int Holder::Get()
{
    VObj* p = mpObject;
    if (p != 0)
        return p->v5();
    return 0;
}






// @ 0x0070e4e0
void SP::cMaterialManager::RecreateShaders()
{
    int self = (int)this;
    D3D_FlushSomeStates();
    int n = (*(int*)(self + 0x9c) - *(int*)(self + 0x98)) >> 2;
    for (int i = 0; i < n; i++)
    {
        char* p = (char*)(*(int*)(*(int*)(self + 0x98) + i * 4) + 0x88);
        for (int j = 0; j < 0x10; j++)
        {
            if (*(void**)(p - 0x40) != 0)
            {
                int sz = ResSize(*(void**)(p - 0x40));
                void* nb = EAlloc8(sz, 0x10, 0, 0, "Graphics", 0, 0, 0);
                ResCopy(*(void**)(p - 0x40), sz, nb);
                void* obj = *(void**)(p - 0x40);
                void** vt = *(void***)obj;
                ((void(__thiscall*)(void*))vt[2])(obj);
                *(void**)(p - 0x40) = nb;
            }
            if (*(void**)p != 0)
            {
                int sz = ResSize(*(void**)p);
                void* nb = EAlloc8(sz, 0x10, 0, 0, "Graphics", 0, 0, 0);
                ResCopy(*(void**)p, sz, nb);
                void* obj2 = *(void**)p;
                void** vt2 = *(void***)obj2;
                ((void(__thiscall*)(void*))vt2[2])(obj2);
                *(void**)p = nb;
            }
            p += 4;
        }
    }
}






// @ 0x0070e5e0
void RebuildResources2(int self)
{
    int n = (*(int*)(self + 0x9c) - *(int*)(self + 0x98)) >> 2;
    for (int i = 0; i < n; i++)
    {
        char* p = (char*)(*(int*)(*(int*)(self + 0x98) + i * 4) + 0x88);
        for (int j = 0; j < 0x10; j++)
        {
            void* a = *(void**)(p - 0x40);
            if (a != 0)
            {
                void** vt = *(void***)g_device;
                ((void(__thiscall*)(void*, void*, void*))vt[0x16c / 4])(g_device, a, p - 0x40);
                EFree2(a);
            }
            void* b = *(void**)p;
            if (b != 0)
            {
                void** vt = *(void***)g_device;
                ((void(__thiscall*)(void*, void*, void*))vt[0x1a8 / 4])(g_device, b, p);
                EFree2(b);
            }
            p += 4;
        }
    }
}






// @ 0x0070e6b0
void** MakeHashNode(void** src)
{
    void** p = (void**)EAlloc(0xc, "Graphics", 0, 0, ALLOC_FILE, 0xd1);
    if (p != 0)
    {
        p[0] = src[0];
        void* v = src[1];
        p[1] = v;
        if (v != 0)
            ((RC3c*)v)->AddRef();
    }
    p[2] = 0;
    return p;
}






// @ 0x0070e890
void __stdcall RangeWeakRelease(RC14** first, RC14** last)
{
    while (first < last)
    {
        RC14* p = *first;
        if ((p != 0) && (p->mCount > 1))
            --p->mCount;
        ++first;
    }
}






// @ 0x0070e8c0
void UninitCopyA2(void** out, void** first, void** last, void** dst)
{
    *out = dst;
    void** result = dst;
    try
    {
        for (; first != last; ++first, ++result)
        {
            void* s = *first;
            *result = s;
            if (s != 0)
                ((RC3c*)s)->AddRef();
        }
    }
    catch (...)
    {
        for (void** q = dst; q != result; ++q)
            ((RC3c*)*q)->Release();
        throw;
    }
    *out = result;
}






// @ 0x0070e950
void FillA(void** first, void** last, void** value)
{
    while (first != last)
    {
        void* s = *value;
        void* old = *first;
        if (s != old)
        {
            if (s != 0)
                ((RC3c*)s)->AddRef();
            *first = s;
            if (old != 0)
                ((RC3c*)old)->Release();
        }
        ++first;
    }
}






// @ 0x0070e9a0
void UninitFillNA2(void** first, unsigned n, void** value)
{
    void** result = first;
    try
    {
        for (; n != 0; --n, ++result)
        {
            void* s = *value;
            *result = s;
            if (s != 0)
                ((RC3c*)s)->AddRef();
        }
    }
    catch (...)
    {
        for (void** q = first; q != result; ++q)
            ((RC3c*)*q)->Release();
        throw;
    }
}






// @ 0x0070ea20
void FillB(void** first, void** last, void** value)
{
    while (first != last)
    {
        void* s = *value;
        void* old = *first;
        if (s != old)
        {
            if (s != 0)
                ((RC3b*)s)->AddRef();
            *first = s;
            if (old != 0)
                ((RC3b*)old)->Release();
        }
        ++first;
    }
}






// @ 0x0070ea70
void UninitCopyAtomic8(void** out, void** first, void** last, void** dst)
{
    *out = dst;
    for (; first != last; ++first)
    {
        void** cur = (void**)*out;
        if (cur != 0)
        {
            void* p = *first;
            *cur = p;
            if (p != 0)
                ++*(volatile long*)((char*)p + 8);
        }
        *out = (void**)((char*)*out + 4);
    }
}






// @ 0x0070eac0
void FillAtomic8(void** first, void** last, void** value)
{
    while (first != last)
    {
        void* s = *value;
        void* old = *first;
        if (s != old)
        {
            if (s != 0)
                ++*(volatile long*)((char*)s + 8);
            *first = s;
            if (old != 0)
            {
                volatile long* rc = (volatile long*)((char*)old + 8);
                --*rc;
            }
        }
        ++first;
    }
}






// @ 0x0070eb30
void FillNAtomic8(void** dst, unsigned n, void** value)
{
    for (; n != 0; --n)
    {
        if (dst != 0)
        {
            void* p = *value;
            *dst = p;
            if (p != 0)
                ++*(volatile long*)((char*)p + 8);
        }
        ++dst;
    }
}






// @ 0x0070eb70
void UninitCopyWeak14(void** out, void** first, void** last, void** dst)
{
    *out = dst;
    if (first != last)
    {
        do
        {
            if (dst != 0)
            {
                void* p = *first;
                *dst = p;
                if (p != 0)
                    ++*(int*)((char*)p + 0x14);
            }
            ++first;
            ++dst;
        } while (first != last);
        *out = dst;
    }
}






// @ 0x0070ebb0
void FillWeak14(void** first, void** last, void** value)
{
    while (first != last)
    {
        void* s = *value;
        void* old = *first;
        if (s != old)
        {
            if (s != 0)
                ++*(int*)((char*)s + 0x14);
            *first = s;
            if (old != 0)
            {
                int c = *(int*)((char*)old + 0x14);
                if (c > 1)
                    *(int*)((char*)old + 0x14) = c - 1;
            }
        }
        ++first;
    }
}






// @ 0x0070ebf0
void AssignWeak14(void** first, void** last, void** dst)
{
    while (first != last)
    {
        void* s = *first;
        void* old = *dst;
        if (s != old)
        {
            if (s != 0)
                ++*(int*)((char*)s + 0x14);
            *dst = s;
            if (old != 0)
            {
                int c = *(int*)((char*)old + 0x14);
                if (c > 1)
                    *(int*)((char*)old + 0x14) = c - 1;
            }
        }
        ++first;
        ++dst;
    }
}






// @ 0x0070ec30
void CopyBackwardWeak14(void** first, void** last, void** dstEnd)
{
    while (last != first)
    {
        void* s = last[-1];
        void* old = dstEnd[-1];
        --last;
        --dstEnd;
        if (s != old)
        {
            if (s != 0)
                ++*(int*)((char*)s + 0x14);
            *dstEnd = s;
            if (old != 0)
            {
                int c = *(int*)((char*)old + 0x14);
                if (c > 1)
                    *(int*)((char*)old + 0x14) = c - 1;
            }
        }
    }
}






// @ 0x0070eea0
bool SP::cMaterialManager::WriteShaders(EA::ResourceMan::Database * stream)
{
    int self = (int)this;
    int local[3];
    local[0] = *(int*)(self + 0x200);
    local[1] = 0x469a3f7;
    local[2] = *(int*)0x01535f68;
    int saved = 0;
    void** vt = *(void***)stream;
    char ok = ((char(__thiscall*)(void*, int*, int*, int, int, int, int))vt[0x34 / 4])
              (stream, local, &saved, 2, 6, 1, 0);
    if (ok == 0)
        return 0;
    int s = ((int(__thiscall*)(void*))vt[0x18 / 4])(stream);
    int one = 1;
    WriteUint32Stub((void*)s, &one, 1, 0);
    FreeStreamStub((void*)s);
    FragDeclStub((void*)s);
    ((void(__thiscall*)(void*))vt[0x24 / 4])(stream);
    return 1;
}





// @ 0x0070efa0
bool SP::cMaterialManager::ReadShaders(EA::ResourceMan::Database * stream)
{
    void* self = this;
    int local[3];
    local[0] = *(int*)((char*)self + 0x200);
    local[2] = *(int*)0x01535f68;
    local[1] = 0x469a3f7;
    int saved = 0;
    void** vt = *(void***)stream;
    char ok = ((char(__thiscall*)(void*, int*, int*, int, int, int, int))vt[0x34 / 4])
              (stream, local, &saved, 1, 6, 1, 0);
    if (ok == 0)
        return 1;
    int s = ((int(__thiscall*)(void*))vt[0x18 / 4])(stream);
    ReadInt32Stub((void*)s, &saved, 1, 0);
    if (saved == 1)
    {
        ReadShaders_helper2((void*)s);
        MiscD((void*)s, 1);
        ((void(__thiscall*)(void*))vt[0x24 / 4])(stream);
        return 1;
    }
    return 0;
}





// @ 0x0070f320
VecA::~VecA()
{
    void** first = mpBegin;
    void** last = mpEnd;
    for (; first < last; ++first)
    {
        if (*first != 0)
            ((RC3c_s0070_efa0*)*first)->Release();
    }
    void* p = mpBegin;
    if ((p != 0) && (*(int*)((char*)p - 4) != 0))
        EFree(p);
}





// @ 0x0070f390
VecB::~VecB()
{
    void** first = mpBegin;
    void** last = mpEnd;
    for (; first < last; ++first)
    {
        if (*first != 0)
            ((RC3b_s0070_efa0*)*first)->Release();
    }
    void* p = mpBegin;
    if ((p != 0) && (*(int*)((char*)p - 4) != 0))
        EFree(p);
}





// @ 0x0070f520
void VecBase::DestroyRange(void** first, void** last)
{
    for (; first < last; ++first)
    {
        void* p = *first;
        if (p != 0)
        {
            volatile long* rc = (volatile long*)((char*)p + 8);
            if (*rc > 1)
                --*rc;
        }
    }
}





// @ 0x0070f570
void FillWeak14N(void** dst, unsigned n, void** value)
{
    while (n > 0)
    {
        if (dst != 0)
        {
            void* p = *value;
            *dst = p;
            if (p != 0)
                ++*(int*)((char*)p + 0x14);
        }
        --n;
        ++dst;
    }
}





// @ 0x0070f890
void FVecB::Teardown()
{
    VecBase* v = (VecBase*)((char*)this + 0x20);
    v->DestroyRange(v->mpBegin, v->mpEnd);
    void* p = v->mpBegin;
    if ((p != 0) && (p != *(void**)((char*)v + 0x10)))
        EFree(p);
}





// @ 0x0070f8c0
bool cMaterialManager_HasMaterial(void* self, int key, unsigned flags)
{
    int found[3];
    if (flags == 0)
    {
        Mutex* m = (Mutex*)((char*)self + 600);
        m->Lock((void*)0x0140c860);
        FindInMap(found, &key);
        int* vec = (int*)((char*)self + 0x174);
        if (found[0] != *(int*)(vec[1] + vec[2] * 4))
        {
            char c = *(char*)(found[0] + 4);
            m->Unlock();
            return c != 0;
        }
        m->Unlock();
        found[2] = 0;
    }
    else
    {
        if ((flags & 0xc0000000) != 0x40000000)
            return false;
        found[2] = flags & 0xffffff00;
    }
    found[0] = key;
    found[1] = 0x2f4e681b;
    void* mgr = ResGetManager();
    void** vt = *(void***)mgr;
    return ((char(__thiscall*)(void*, int*, int, int, int, int, int))vt[0xc / 4])
           (mgr, found, 0, 0, 0, 0, 0) != 0;
}





// @ 0x0070fa30
void FVecC::Teardown()
{
    VecBase* v = (VecBase*)((char*)this + 0x24);
    v->DestroyRange(v->mpBegin, v->mpEnd);
    void* p = v->mpBegin;
    if ((p != 0) && (p != *(void**)((char*)v + 0x10)))
        EFree(p);
}





// @ 0x0070fa60
void VecA::Shrink(void** arg1, void** arg2)
{
    void** p = AssignCopyA(arg1, mpEnd, arg2);
    void** end = mpEnd;
    for (; p < end; ++p)
    {
        if (*p != 0)
            ((RC3c_s0070_efa0*)*p)->Release();
    }
    mpEnd = (void**)((char*)mpEnd + ((char*)arg2 - (char*)arg1));
}





// @ 0x0070fab0
void VecB::Shrink(void** arg1, void** arg2)
{
    void** p = AssignCopyB(arg1, mpEnd, arg2);
    void** end = mpEnd;
    for (; p < end; ++p)
    {
        if (*p != 0)
            ((RC3b_s0070_efa0*)*p)->Release();
    }
    mpEnd = (void**)((char*)mpEnd + ((char*)arg2 - (char*)arg1));
}





// @ 0x0070fd00
void __stdcall HashChainDtorA(void** buckets, unsigned n)
{
    for (unsigned i = 0; i < n; i++)
    {
        HashNodeA* node = (HashNodeA*)buckets[i];
        while (node != 0)
        {
            HashNodeA* p = node;
            RC3c_s0070_efa0* ref = p->mpRef;
            node = p->mpNext;
            if (ref != 0)
                ref->Release();
            EFree(p);
        }
        buckets[i] = 0;
    }
}





// @ 0x0070ff50
void __stdcall HashChainDtorB(void** buckets, unsigned n)
{
    for (unsigned i = 0; i < n; i++)
    {
        HashNodeB* node = (HashNodeB*)buckets[i];
        while (node != 0)
        {
            HashNodeB* p = node;
            RC3b_s0070_efa0* ref = p->mpRef;
            node = p->mpNext;
            if (ref != 0)
                ref->Release();
            EFree(p);
        }
        buckets[i] = 0;
    }
}




// @ 0x007101f0
Tex4& MapA::operator[](const uint32_t& key)
{
    void* it[2];
    HashtableFind10(this, &key, it);
    if (it[0] != (void*)*(uint32_t*)((char*)mpBucketArray + mnBucketCount * 4)) {
        return *(Tex4*)((char*)it[0] + 4);
    }
    struct Pair { const uint32_t first; Tex4 second; };
    Pair value = { key, Tex4() };
    uint8_t out[12];
    HashtableInsert10(this, out, &value, 0);
    return *(Tex4*)(*(uint32_t*)out + 4);
}




// @ 0x007102b0
Mat4& MapB::operator[](const uint32_t& key)
{
    void* it[2];
    HashtableFind10(this, &key, it);
    if (it[0] != (void*)*(uint32_t*)((char*)mpBucketArray + mnBucketCount * 4)) {
        return *(Mat4*)((char*)it[0] + 4);
    }
    struct Pair { const uint32_t first; Mat4 second; };
    Pair value = { key, Mat4() };
    uint8_t out[12];
    HashtableInsert10(this, out, &value, 0);
    return *(Mat4*)(*(uint32_t*)out + 4);
}




// @ 0x007103e0
void VecFixed::DoInsertValue(AutoRef14_s0071_01f0* position, const AutoRef14_s0071_01f0& value)
{
    if (mpEnd != mpCapacity) {
        const AutoRef14_s0071_01f0* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new (mpEnd) AutoRef14_s0071_01f0(*(mpEnd - 1));
        CopyBackwardRef(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = GetNewCapacity(nPrevSize);
        AutoRef14_s0071_01f0* const pNewData = DoAllocate(nNewSize);
        AutoRef14_s0071_01f0* pNewEnd = UninitializedMovePtr(mpBegin, position, pNewData);
        ::new (pNewEnd) AutoRef14_s0071_01f0(value);
        pNewEnd = UninitializedMovePtr(position, mpEnd, pNewEnd + 1);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}




// @ 0x007106d0
void VecAsn::assign(const void* first, const void* last)
{
    const uint32_t n = (uint32_t)((const char*)last - (const char*)first) >> 2;
    if ((uint32_t)((char*)mpCapacity - (char*)mpBegin) >> 2 < n) {
        void* pNewData = ReallocRef(this, n, first, last);
        DestroyRange0(mpBegin, mpEnd);
        if (mpBegin && ((int32_t*)mpBegin)[-1] != 0) EastlFree(mpBegin);
        mpBegin = pNewData;
        mpEnd = (char*)pNewData + n * 4;
        mpCapacity = mpEnd;
    } else {
        const uint32_t nSize = (uint32_t)((char*)mpEnd - (char*)mpBegin) >> 2;
        if (n <= nSize) {
            void* pNewEnd = AssignCopyRef((void*)first, (void*)last, mpBegin);
            DestroyRange0(pNewEnd, mpEnd);
            mpEnd = pNewEnd;
        } else {
            const void* position = (const char*)first + nSize * 4;
            AssignCopyRef((void*)first, (void*)position, mpBegin);
            AssignMoveRef(0, (void*)position, (void*)last, mpEnd, (void*)last);
            mpEnd = (void*)last;
        }
    }
}




// @ 0x00711070
void VecResizeA::resize(uint32_t n)
{
    if (n > size()) {
        typedef int32_t value_type;
        value_type value = 0;
        DoInsertValuesRef(mpEnd, n - size(), &value);
    } else {
        EraseRef((char*)mpBegin + n * 4, mpEnd);
    }
}




// @ 0x007110f0
void VecResizeB::resize(uint32_t n)
{
    if (n > size()) {
        typedef int32_t value_type;
        value_type value = 0;
        DoInsertValuesRef(mpEnd, n - size(), &value);
    } else {
        EraseRef((char*)mpBegin + n * 4, mpEnd);
    }
}




// @ 0x00711170
void VecSp::push_back()
{
    if (mpEnd < mpCapacity) {
        ::new (mpEnd++) AutoRef8();
    } else {
        AutoRef8 temp;
        ((RefPtrVecGrow*)this)->DoInsertValue(mpEnd, temp);
    }
}



// @ 0x00711220
void VecResize::resize(uint32_t n)
{
    if (n > size()) {
        int32_t value = 0;
        DoInsertValuesRef(mpEnd, n - size(), &value);
    } else {
        void* first = (char*)mpBegin + n * 4;
        void* pNewEnd = AssignCopyRef(mpEnd, mpEnd, first);
        DestroyRange(pNewEnd, mpEnd);
        mpEnd = (char*)mpEnd - (uint32_t)((char*)mpEnd - (char*)first);
    }
}



// @ 0x007112c0
void __stdcall DoFreeNodes(FreeNode** pNodeArray, uint32_t n)
{
    for (uint32_t i = 0; i < n; ++i) {
        FreeNode* pNode = pNodeArray[i];
        while (pNode) {
            FreeNode* pNext = pNode->mpNext;
            if (pNode->m8 - pNode->m0 > 1 && pNode->m0 != 0)
                EastlFree((void*)pNode->m0);
            EastlFree(pNode);
            pNode = pNext;
        }
        pNodeArray[i] = 0;
    }
}



// @ 0x00711400
void __stdcall GetTexturesFromMaterial(void* material, TextureVec* outVec, bool (__cdecl* filter)(void*))
{
    void** it = *(void***)((char*)material + 0x20);
    void** end = *(void***)((char*)material + 0x24);
    while (it != end) {
        TextureRef* tex = (TextureRef*)*it;
        if (tex != 0 && (filter == 0 || filter(tex))) {
            outVec->DoInsertValue();
            TextureRef** slot = (TextureRef**)((char*)outVec->mpEnd - 4);
            TextureRef* old = *slot;
            if (tex != old)
                *slot = tex;
        }
        ++it;
    }
}


// @ 0x00712320
void __stdcall DoFreeNodes24(FreeNode24** pArray, uint32_t n)
{
    for (uint32_t i = 0; i < n; ++i) {
        FreeNode24* node = pArray[i];
        while (node) {
            FreeNode24* next = node->mpNext;
            DestroyRange(node->mpBegin, node->mpEnd);
            if (node->mpBegin != 0 && node->mpBegin != node->mpCapacity)
                EastlFree(node->mpBegin);
            EastlFree(node);
            node = next;
        }
        pArray[i] = 0;
    }
}


// @ 0x00712760
TailVec::TailVec(const TailVec& src)
{
    void* buf = mBuffer;
    mpBegin = buf;
    mpEnd = buf;
    mpCapacity = (char*)buf + 16;
    mpPoolBegin = buf;
    AssignRange(*(void**)&src.mpBegin, *(void**)&src.mpEnd, 0);
}


// @ 0x007127d0
State27D0* State27D0::CopyFrom(const State27D0& src)
{
    for (int i = 0; i < 9; ++i)
        m0[i] = src.m0[i];
    ::new (&mVec) TailVec(src.mVec);
    return this;
}


// @ 0x00712850
State2850* State2850::CopyFrom2(const State2850& a, const State2850& b)
{
    m0[0] = a.m0[0];
    for (int i = 1; i < 9; ++i)
        m0[i] = b.m0[i - 1];
    ::new (&mVec) TailVec(b.mVec);
    return this;
}


// @ 0x00712b20
void __stdcall DoFreeNodesStr2(FreeNodeStr** pArray, uint32_t n)
{
    for (uint32_t i = 0; i < n; ++i) {
        FreeNodeStr* node = pArray[i];
        while (node) {
            FreeNodeStr* next = node->mpNext;
            HashStr* h = (HashStr*)((char*)node + 4);
            h->DoFreeNodes(h->mpBucketArray, h->mnBucketCount);
            h->mnElementCount = 0;
            if (h->mnBucketCount > 1)
                EastlFree(h->mpBucketArray);
            EastlFree(node);
            node = next;
        }
        pArray[i] = 0;
    }
}


// @ 0x00712ba0
bool MaterialManager3::HasMaterial(uint32_t key)
{
    MutexLock lock(mMutex, &g_mutexParams);
    return mMap[key] != 0;
}


// @ 0x00712c20
uint8_t* MaterialManager3::GetMaterial(uint32_t key)
{
    MutexLock lock(mMutex, &g_mutexParams);
    uint8_t* p = &mMap[key];
    if (*p == 0) {
        *(uint32_t*)(p + 0x18) = key;
        void* invalid = mpInvalidState;
        if (*(void**)(p + 4) != invalid)
            *(void**)(p + 4) = invalid;
    }
    return p;
}


// @ 0x00712cb0
void MaterialManager3::GetMaterials(int32_t n, const uint32_t* keys, void** out)
{
    MutexLock lock(mMutex, &g_mutexParams);
    if (n > 0) {
        intptr_t delta = (intptr_t)((char*)out - (char*)keys);
        do {
            uint8_t* p = &mMap[*keys];
            if (*p == 0) {
                *(uint32_t*)(p + 0x18) = *keys;
                void* invalid = mpInvalidState;
                if (*(void**)(p + 4) != invalid)
                    *(void**)(p + 4) = invalid;
            }
            *(void**)((char*)keys + delta) = p;
            ++keys;
            --n;
        } while (n != 0);
    }
}


// @ 0x00712d60
uint8_t* MaterialManager3::GetMaterialInstance(uint32_t key, void* param3)
{
    if (param3 == 0) {
        MutexLock lock(mMutex, &g_mutexParams);
        uint8_t* p = &mMap[key];
        if (*p == 0) {
            *(uint32_t*)(p + 0x18) = key;
            void* invalid = mpInvalidState;
            if (*(void**)(p + 4) != invalid)
                *(void**)(p + 4) = invalid;
        }
        return p;
    }
    return 0;
}

// @ 0x00712e10
uint32_t cMaterialManager_s0071_2e10::GetIDFromCompiledState(uint32_t state, uint32_t id)
{
    mMutex.Lock(gMutexParams);
    HashIter it;
    mCompiledStateToIDMap.find(&it, &state);
    uint32_t* found = it.mpNode;
    uint32_t result;
    if (found == (uint32_t*)mCompiledStateToIDMap.mpBuckets[mCompiledStateToIDMap.mnBuckets]) {
        // not found: pick the next unused material id
        MaterialEntry* e;
        uint32_t n;
        for (;;) {
            n = mnNextMaterialId++;
            uint32_t* node = (uint32_t*)mMaterialsMap.mpBuckets[n % mMaterialsMap.mnBuckets];
            while (node) {
                if (n == node[0])
                    break;
                node = (uint32_t*)node[0x4c / 4];
            }
            // iterator: the node, or end() (the bucket-array sentinel) when the chain ran out
            uint32_t* endNode = (uint32_t*)mMaterialsMap.mpBuckets[mMaterialsMap.mnBuckets];
            if (node == 0)
                node = endNode;
            if (node == endNode)
                break;           // id not used yet (iterator == end)
        }
        e = mMaterialsMap.operator_index(&n);
        e->mnExternalId = id;
        *(uint8_t*)e = 1;
        ((uint32_t*)e)[1] = state;
        e->mnId = n;
        *mCompiledStateToIDMap.operator_index(&state) = n;
        result = n;
    } else {
        result = found[1];
    }
    mMutex.Unlock();
    return result;
}

// @ 0x00712f50
void cMaterialManager_s0071_2e10::RegisterMaterial(uint32_t key, int nFlags, const uint32_t* flags, uint32_t nTex, void** texRes)
{
    mMutex.Lock(gMutexParams);
    MaterialEntry* e = mMaterialsMap.operator_index(&key);
    e->Unregister();
    e->mnFlags = (uint8_t)nFlags;
    for (int i = 0; i < nFlags; i++)
        e->mFlags[i] = flags[i];
    e->mnId = key;
    e->mTextures.resize(nTex);
    // eastl::copy of the texture resources into the (just resized) texture vector
    for (uint32_t i = 0; i < nTex; i++)
        e->mTextures.mpBegin[i].SetFromResource(texRes[i]);
    e->mnRefCount++;
    {
        EntryRef ref(e);
        mRegistered.push_back(ref);
    }
    mMutex.Unlock();
}

// @ 0x00713070
bool cMaterialManager_s0071_2e10::ReadExternalReferences(ResourceDatabaseStub* db)
{
    mMutex.Lock(gMutexParams);

    ResourceObject* old = mpResource;
    if (old) {
        mpResource = 0;
        old->Release();
    }

    ResourceKey key;
    key.instance = mn200;
    key.type = 0x2F4E681B;
    key.group = gGroupMaterialsA;

    ResourceObject* res = 0;
    ResourceManagerStub* mgr = (ResourceManagerStub*)GetResourceManager();
    if (res) {
        ResourceObject* t = res;
        res = 0;
        t->Release();
    }
    if (mgr->GetResource(&key, &res, 0, db, 0, 0)) {
        ResourceObject* obj = res ? (ResourceObject*)res->QueryResource(0x2F4E681B) : 0;
        ResourceObject* prev = mpResource;
        if (obj != prev) {
            if (obj)
                obj->AddRef();
            mpResource = obj;
            if (prev)
                prev->Release();
        }
    }

    if (!mpResource) {
        if (res)
            res->Release();
        mMutex.Unlock();
        return false;
    }

    ResourceKey key2;
    key2.instance = mn200;
    key2.type = 0x0469A3F7;
    key2.group = gGroupMaterialsB;
    StreamHolder* holder = 0;
    if (!db->GetStream(&key2, &holder, 1, 6, 1, 0)) {
        if (res)
            res->Release();
        mMutex.Unlock();
        return false;
    }

    void* stream = holder->GetStream();
    int version;
    ReadInt32(stream, &version, 1, 0);
    if ((uint32_t)version > 0) {
        holder->Release();
        if (res)
            res->Release();
        mMutex.Unlock();
        return false;
    }

    int exportIndex = 0;
    ImageFactoryStub* factory = (ImageFactoryStub*)GetImageFactory();
    int id;
    ReadInt32(stream, &id, 1, 0);
    while (id != -1) {
        MaterialEntry* e = mMaterialsMap.operator_index((const uint32_t*)&id);
        e->mnId = id;
        ReadExact(stream, e, 1);
        uint8_t nTextures;
        ReadExact(stream, &nTextures, 1);
        e->mTextures.resize(nTextures);
        for (int i = 0; i < nTextures; i++) {
            int a, b;
            ReadInt32(stream, &a, 1, 0);
            ReadInt32(stream, &b, 1, 0);
            void* img = factory->GetImage(a, b, 0);
            e->mTextures.mpBegin[i].SetFromResource(img);
        }
        for (int i = 0; i < e->mnFlags; i++) {
            ExportedObject obj;
            obj.type = 0;
            obj.value = 0;
            obj.pad8 = 0;
            obj.padC = 0;
            obj.pad10 = 0;
            obj.pad14 = 0;
            obj.elems[0].a = 0;
            obj.elems[0].b = 1;
            GetExportedObjectByIndex(mpResource->mpArena, exportIndex, &obj);
            if (obj.type == 0x2000B)
                e->mFlags[i] = obj.value;
            exportIndex++;
        }
        if (e->mTextures.mpBegin != e->mTextures.mpEnd) {
            e->mnRefCount++;
            EntryRef ref(e);
            mRegistered.push_back(ref);
        }
        ReadInt32(stream, &id, 1, 0);
    }
    holder->Close();
    holder->Release();
    if (res)
        res->Release();
    mMutex.Unlock();
    return true;
}

// @ 0x00713560
cMaterialScriptState::~cMaterialScriptState()
{
    mMap13C.FreeNodes7112C0(mMap13C.mpBuckets, mMap13C.mnBuckets);
    mMap13C.mnElements = 0;
    if (mMap13C.mnBuckets > 1)
        EastlFree(mMap13C.mpBuckets);

    if ((uint32_t)(mpLabelCapacity - mpLabelBegin) > 1 && mpLabelBegin)
        EastlFree(mpLabelBegin);

    mMapF0.FreeNodes70FF50(mMapF0.mpBuckets, mMapF0.mnBuckets);
    mMapF0.mnElements = 0;
    if (mMapF0.mnBuckets > 1)
        EastlFree(mMapF0.mpBuckets);

    mDC.Destroy70F390();

    mMapBC.FreeNodes70FD00(mMapBC.mpBuckets, mMapBC.mnBuckets);
    mMapBC.mnElements = 0;
    if (mMapBC.mnBuckets > 1)
        EastlFree(mMapBC.mpBuckets);

    mMap9C.FreeNodes712B20(mMap9C.mpBuckets, mMap9C.mnBuckets);
    mMap9C.mnElements = 0;
    if (mMap9C.mnBuckets > 1)
        EastlFree(mMap9C.mpBuckets);

    m88.Destroy70F320();

    mMap68.FreeNodes6A85B0(mMap68.mpBuckets, mMap68.mnBuckets);
    mMap68.mnElements = 0;
    if (mMap68.mnBuckets > 1)
        EastlFree(mMap68.mpBuckets);

    mMap48.FreeNodes6A85B0(mMap48.mpBuckets, mMap48.mnBuckets);
    mMap48.mnElements = 0;
    if (mMap48.mnBuckets > 1)
        EastlFree(mMap48.mpBuckets);

    mMap28.FreeNodes6A85B0(mMap28.mpBuckets, mMap28.mnBuckets);
    mMap28.mnElements = 0;
    if (mMap28.mnBuckets > 1)
        EastlFree(mMap28.mpBuckets);

    mMap8.FreeNodes6A85B0(mMap8.mpBuckets, mMap8.mnBuckets);
    mMap8.mnElements = 0;
    if (mMap8.mnBuckets > 1)
        EastlFree(mMap8.mpBuckets);

    // AutoRefCount<> release of the invalid texture (atomic decrement, floor at zero)
    ResourceObject* tex = mInvalidTexture;
    if (tex) {
        volatile long* rc = (volatile long*)((char*)tex + 8);
        _InterlockedExchangeAdd(rc, -1);
        long v = _InterlockedExchangeAdd(rc, 0);
        if (v < 1)
            _InterlockedExchangeAdd(rc, 1);
        else
            _InterlockedExchangeAdd(rc, 0);
    }
}

// @ 0x00713780
cMaterialManager_s0071_2e10::~cMaterialManager_s0071_2e10()
{
    mpVtblA = vtblMaterialManagerA;
    mpVtblB = vtblMaterialManagerB;
    mMutex.Destroy();

    mRegistered.DoDestroy(mRegistered.mpBegin, mRegistered.mpEnd);
    MaterialEntry** p = mRegistered.mpBegin;
    if (p && ((int*)p)[-1])
        EastlFree(p);

    if (mpResource)
        mpResource->Release();

    mPtrVec.DoDestroy(mPtrVec.mpBegin, mPtrVec.mpEnd);
    if (mPtrVec.mpBegin && mPtrVec.mpBegin != mPtrVec.mpLocal)
        EastlFree(mPtrVec.mpBegin);

    mCompiledStateToIDMap.FreeNodes693230(mCompiledStateToIDMap.mpBuckets,
                                          mCompiledStateToIDMap.mnBuckets);
    mCompiledStateToIDMap.mnElements = 0;
    if (mCompiledStateToIDMap.mnBuckets > 1)
        EastlFree(mCompiledStateToIDMap.mpBuckets);

    mMaterialsMap.FreeNodes712320(mMaterialsMap.mpBuckets, mMaterialsMap.mnBuckets);
    mMaterialsMap.mnElements = 0;
    if (mMaterialsMap.mnBuckets > 1)
        EastlFree(mMaterialsMap.mpBuckets);

    mScriptState.~cMaterialScriptState();

    if (mpListener)
        mpListener->Release();
    mpVtblA = vtblMaterialManagerBaseA;
    mpVtblB = vtblMaterialManagerBaseB;
}

// @ 0x007138f0
cMaterialScriptState::cMaterialScriptState()
{
    pad0 = 0;
    mInvalidTexture = 0;
    mMap8.InitEmpty();
    mMap28.InitEmpty();
    mMap48.InitEmpty();
    mMap68.InitEmpty();
    m88.a = 0;
    m88.b = 0;
    m88.c = 0;
    mMap9C.InitEmpty();
    mMapBC.InitEmpty();
    mDC.a = 0;
    mDC.b = 0;
    mDC.c = 0;
    mMapF0.InitEmpty();
    mpLabelBegin = gEmptyStringChars;
    mpLabelEnd = gEmptyStringChars;
    mpLabelCapacity = gEmptyStringCharsEnd;
    mMap13C.InitEmpty();
}

// @ 0x00713a80
cMaterialManager_s0071_2e10::cMaterialManager_s0071_2e10()
{
    mpVtblA = 0;
    mpVtblB = vtblMaterialManagerBaseB;
    pad8 = 0;
    mpVtblA = vtblMaterialManagerA;
    mpVtblB = vtblMaterialManagerB;
    mpListener = 0;
    // mScriptState constructed here
    mMaterialsMap.InitEmpty();
    mCompiledStateToIDMap.InitEmpty();
    pad1B4 = 0;
    mn1D0 = -1;
    mn1D4 = 0;
    mPtrVec.mpLocal = &mLocalBuf[0];
    mPtrVec.mpBegin = &mLocalBuf[0];
    mPtrVec.mpEnd = &mLocalBuf[0];
    mPtrVec.mpCapacity = &mLocalBuf[4];
    mb1B8 = 0;
    mn1CC = 1;
    mn200 = 0;
    mpResource = 0;
    mStopwatch.Construct(5, 0);
    mn220 = 0;
    mn224 = 0;
    mn228 = 0;
    mn22C = 0;
    mn230 = 0;
    mn234 = 0;
    mn238 = 0;
    mb23C = 0;
    mnNextMaterialId = 0x200;
    mRegistered.mpBegin = 0;
    mRegistered.mpEnd = 0;
    mRegistered.mpCapacity = 0;
    mMutex.Construct(0, 1);
}
