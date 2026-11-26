// src/game/SPEngine/_at_00760000.cpp -- migrated from slice(s) s0076cc00, s0076bc50, s0076acd0, s007689a0, s00767ee0, s00762d70, s00761dc0, s00760ea0 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_00760000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/graphics/Raster.h"

// unnamed retail callees and globals (address in the comment)
extern float g_16f8bec, g_16f8be8, g_16f8bfc, g_16f8bf8;
extern float g_16f8c0c, g_16f8c08, g_16f8c1c, g_16f8c18;
extern float g_16f8c90, g_16f8c94, g_16f8c98, g_16f8c9c;
extern float g_140dea0;
#include <new>
#include <stdlib.h>
#include <xmmintrin.h>
#include <intrin.h>
#include <string.h>
#include "rw/graphics/IndexBuffer.h"
#include "rw/graphics/VertexBuffer.h"
#include "SP/cGraphicsResourceFactory.h"
#include "EA/Messaging/IHandlerRC.h"
#include "SP/cViewer.h"

// ---- items of slice s00760ea0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Alloc16c8b44 {
    void  Free(void* p);                                           // @ 0x9276c0
    void* allocate(int a, int b, int c, int d, int e, int f, int g, int h); // @ 0x928a30
};
extern Alloc16c8b44* g_alloc;          // 0x16c8b44
struct Pair2 { unsigned int x; unsigned int y; };
extern float g_16f8bec, g_16f8be8, g_16f8bfc, g_16f8bf8;
extern float g_16f8c0c, g_16f8c08, g_16f8c1c, g_16f8c18;
extern float g_16f8c90, g_16f8c94, g_16f8c98, g_16f8c9c;
extern float g_140dea0;
// ---- items of slice s00760ea0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern Alloc16c8b44* g_alloc;          // 0x16c8b44

// ---- items of slice s00761dc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_00928a30(void* a, void* b, int c, int d, int e, int f, int g, int h);
extern "C" void* __cdecl FUN_011fb220(void* p);
extern "C" void* __cdecl FUN_011f3220(void* p);
extern "C" void* __cdecl FUN_011f1120();
extern "C" void* __cdecl FUN_006ddcc0(int a, int b, int c, int d);
extern "C" void* __cdecl FUN_006ddd10(int a, void* b);
extern "C" unsigned int __cdecl SP_ColorRGBAToU32(int a);
extern float g_16f8bec, g_16f8be0, g_16f8bfc, g_16f8bf0;
extern float g_16f8c0c, g_16f8c00, g_16f8c1c, g_16f8c10;
extern float g_16f8c70, g_16f8c74, g_16f8c78, g_16f8c7c;
extern float g_16f8be4, g_16f8bf4, g_16f8c04, g_16f8c14;
extern float g_16f8c80, g_16f8c84, g_16f8c88, g_16f8c8c;
extern float g_13eb1bc, g_1485720;
extern int g_15fd918, g_16fa5b8;
extern unsigned int g_16fa38c, g_16f9200, g_1485720b;
extern float g_16077c4, g_16077c8, g_13eb1bcb;
extern float g_neg1;         // 0x013eb1bc  == -1.0f
extern float g_two;          // 0x01470f1c  ==  2.0f
extern float g_one;          // 0x01485720  ==  1.0f
extern float g_1538fe8b, g_140de58b;
extern void* __cdecl FUN_011fa2d0(void* out, int one);   // 0x011fa2d0 MeshCompiledStateLinkCreate
extern void __cdecl FUN_00921440(void* out, unsigned int bucketCount, unsigned int count, int one); // 0x00921440
extern void __cdecl FUN_006f1ab0(unsigned int newBucketCount);                   // 0x006f1ab0
extern void* __cdecl FUN_00f473a0(unsigned int size, const char* name, int f, int df, const char* file, int line);
struct E8x { int a, b; E8x() {} E8x(int x, int y) : a(x), b(y) {} ~E8x(); };
struct D3 { E8x v[4]; };
namespace SP {
struct RefCountedAt8 {
    virtual void v0();
    virtual void v1();
};
}
namespace SP {
struct Alloc16c8b44_s0076_1dc0 {
    void  Free(void* p);
    void* allocate(int a, int b, int c, int d, int e, int f, int g, int h);
};
}
extern SP::Alloc16c8b44_s0076_1dc0* g_alloc_s0076_1dc0;
struct O62A0 {
    virtual void o62A0Slot() = 0;
    ~O62A0() {}
};
struct O62I {
    virtual void o62ISlot() = 0;
    int f8;                                  // +0x08
    O62I() : f8(0) {}
    ~O62I() {}
};
struct O62Desc {                             // 0x38 bytes at +0x0c
    int a[6];
    E8x v[4];                                // +0x24 (E8x has an out-of-line destructor, 0x00c2e4e0)
};
struct O62Ref {
    SP::RefCountedAt8* p;
    O62Ref(SP::RefCountedAt8* r) : p(r) { if (p) p->v0(); }
    ~O62Ref() { if (p) p->v1(); }
};
struct Obj62250 : O62A0, O62I {
    O62Desc d;                               // +0x0c
    O62Ref ref;                              // +0x44
    int state;                               // +0x48
    Obj62250(const int* src, SP::RefCountedAt8* r);   // 0x762250
    ~Obj62250();                                      // 0x7622e0
    void o62A0Slot() {}
    void o62ISlot() {}
};
struct Map2380 {
    char pad0[0x10];
    void* base;                  // +0x10
    char pad14[0x34];
    int cached;                  // +0x48
    int find();                  // @ 0x762380
};
D3 __cdecl FUN_00761300(int);   // forward (slice 25)
const char kEastlAllocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
struct Map262900 {
    char pad0[4];
    unsigned int* buckets;       // +0x4
    unsigned int bucketCount;    // +0x8
    unsigned int count;          // +0xc
    char pad10[4];
    // rehash policy object at +0x10 (its PrepareRehash writes the new bucket count)
    struct TrueType {};
    void insert(void* outIter, const unsigned int* payload, TrueType);   // @ 0x762900
};
struct Cursor262b00 { unsigned int a, b, c; Cursor262b00() : a(0), b(0), c(0) {} };
struct CursorPair262b00 {
    unsigned int first;
    Cursor262b00 second;
    CursorPair262b00(const unsigned int& k, const Cursor262b00& v) : first(k), second(v) {}
};
struct Iter { void* node; void* bucket; unsigned char inserted; char pad[3]; };   // eastl hashtable iterator
struct Hash262b00 {
    char pad0[4];
    void* buckets;               // +0x04
    unsigned int bucketCount;    // +0x08
    void find(Iter* out, const void* key);   // 0x00db4780
    int findInsert(unsigned int* key);       // @ 0x762b00
};
// ---- items of slice s00761dc0 end

// ---- items of slice s00762d70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl EA_New(uint32_t size, const char* file, int a, int b, int c, int d); // 0x0f473a0
extern "C" void  __cdecl EA_Delete(void* p);                                                  // 0x0f47380
extern unsigned char g_flags1630180;   // 0x01630180
extern "C" void* __cdecl F_11f3130(void* vtable);   // 0x011f3130 add-ref vtable
extern "C" void* __cdecl F_11f3580(void* item);     // 0x011f3580 release
extern "C" void* __cdecl F_11f4e90(void* obj);      // 0x011f4e90 release
extern "C" void  __cdecl F_9276c0(void* mgr, void* p); // 0x009276c0
extern "C" void  __cdecl F_762890(void* slot, void* out); // 0x00762890
extern "C" void  __cdecl F_6c1570(void* vec, void* pos, void* val); // 0x006c1570 vector push
extern void* g_mgr16c8b44;                          // 0x016c8b44
struct LockMap { void read64(); void store(int, int); };             // 0x068c140 / 0x068c1b0
struct IObj { virtual void s0(); virtual void s1(); virtual void s2(int); };
struct Obj762f30 { int a4, a8; };
// ---- items of slice s00762d70 end

// ---- items of slice s00767ee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl Dealloc(void* p);                                             // 0xf47380
void __cdecl UnionDestroy(void* p, int type);          // 0x7668c0
void __fastcall FUN_007642c0(void* self);              // 0x7642c0
struct AtomicInt {
    volatile long mValue;
    AtomicInt(long n = 0) { _InterlockedExchange(&mValue, n); }
};
struct BakeIRef {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual ~BakeIRef() {}
};
struct BakeLayer : BakeIRef {
    virtual void DrawLayer() = 0;
};
struct BakeRef {
    virtual ~BakeRef() {}
    AtomicInt mRefCount;
};
struct IObj_s0076_7ee0 {
    virtual void v0();
    virtual int  AddRef();
    virtual int  Release();
    virtual int  GetKind();
    virtual void v4();
    virtual void v5();
    virtual IObj_s0076_7ee0* GetChild();
};
struct IRefB {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
template <class T>
struct AutoRef {
    T* mpObject;
    AutoRef() : mpObject(0) {}
    AutoRef(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRef() { if (mpObject) mpObject->Release(); }
    AutoRef& operator=(T* p) {
        if (p != mpObject) {
            T* old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
struct UnionState {
    char mBytes[0xd0];
    int  mType;
    UnionState() : mType(0) {}
    ~UnionState();
};
UnionState::~UnionState()
{
    if (mType) {
        if (mType == 5) FUN_007642c0(mBytes);
        else            UnionDestroy(mBytes, mType);
        mType = 0;
    }
}
struct VecA {
    IRefB** mpBegin;                    // +0x00
    IRefB** mpEnd;                      // +0x04
    IRefB** mpCapacity;                 // +0x08
    uint32_t mAllocator[2];             // +0x0c
    uint32_t mFlag;                     // +0x14
    void*   mStorage[0x80 / 4];         // +0x18
    VecA()
    {
        mpBegin = (IRefB**)mStorage;
        mpEnd   = mpBegin;
        mFlag = 0;
        mpCapacity = (IRefB**)((char*)mpBegin + 0x80);
    }
    ~VecA();                            // 0x4b5440
};
struct VecB {
    void** mpBegin;                     // +0x00
    void** mpEnd;                       // +0x04
    void** mpCapacity;                  // +0x08
    uint32_t mAllocator[2];             // +0x0c
    uint32_t mFlag;                     // +0x14
    void*  mStorage[0x180 / 4];         // +0x18
    VecB()
    {
        mpBegin = mStorage;
        mpEnd   = mpBegin;
        mFlag = 0;
        mpCapacity = (void**)((char*)mpBegin + 0x180);
    }
    ~VecB()
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            Dealloc(mpBegin);
    }
};
class C68370 : public BakeLayer, public BakeRef {
public:
    virtual int  AddRef();
    virtual int  Release();
    virtual void DrawLayer();

    C68370(IRefB* a, IObj_s0076_7ee0* b, int* c, IObj_s0076_7ee0* d, int e);
    ~C68370();

    AutoRef<IObj_s0076_7ee0> m_pC;                 // +0x0c
    AutoRef<IObj_s0076_7ee0> m_pE;                 // +0x10
    AutoRef<IRefB> m_pA;                // +0x14
    int   m_v18;                        // +0x18
    int   m_v1c;                        // +0x1c
    int   m_v20;                        // +0x20
    int   m_v24;                        // +0x24
    AutoRef<IObj_s0076_7ee0> m_p28;                // +0x28
    UnionState m_state;                 // +0x2c
    AutoRef<IRefB> m_100;               // +0x100
    VecA  m_vecA;                       // +0x104
    VecB  m_vecB;                       // +0x19c
    char  m334;                         // +0x334
};
// ---- items of slice s00767ee0 end

// ---- items of slice s007689a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct Key { uint a, b, c; };       // 12-byte resource key (read from owner+8)
struct Stream {                     // EA::IO::IStream; Write is slot 0x38
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
    virtual bool Write(const void* p, uint n);                  // +0x38
};
struct IMaterialMgr {               // SP::cMaterialManager vtable (offsets recovered from calls)
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
    virtual void s30();
    virtual uint GetMaterialID(void* mat);                      // +0x34 (ret 4)
    virtual void FlagMaterials(uint n, void* mats, uint* out);  // +0x38 (ret 0xc)
virtual void s3c();
virtual void s40();
    virtual void WriteMaterials(uint n, uint* flags, Stream* s, void* ctx); // +0x44 (ret 0x10)
    virtual void s48();
    virtual void CollectKeys(uint n, uint* ids, void* keyVec, int flag);    // +0x4c (ret 0x10)
};
struct LockedRegion { void* data; uint a, b; };
struct VDesc {                      // rw::graphics::VertexDescriptor
    char p0[0xc];
    uint16_t numElements;           // +0xc
    uint8_t lockFlags;              // +0xe
    uint8_t stride;                 // +0xf
    char p1[8];
    char elements[1];               // +0x18, 12 bytes each
    uint8_t GetStride() const { return stride; }
    void Finish();                  // 0x011f3220
};
struct VBuf {                       // rw::graphics::VertexBuffer
    VDesc* desc;
    uint p4, base, numVertices;
    uint Bytes(uint n) const { return desc->GetStride() * n; }
    void* Lock(uint flags, uint off, uint size);               // 0x011f3620 (ret 0xc)
    void Unlock();                                             // 0x011f36a0
};
struct IBuf {                       // rw::graphics::IndexBuffer
    uint p0, p4, numIndices, pc, p10, primType;
    uint GetDepth();                                           // 0x011f4fb0
    IBuf* Lock(uint flags, LockedRegion* r);                   // 0x011f4f20 (ret 8)
    void Unlock(LockedRegion* r);                              // 0x011f4fd0 (ret 4)
};
struct MeshEntry {                  // element of Model+0x18
    char p0[8];
    IBuf* ib;                       // +0x08
    char p1[0x18];
    VBuf* vb;                       // +0x24
};
struct KeyOwner { char p0[8]; Key key; };   // Key at +8
struct SubObj { char p0[0x74]; KeyOwner* owner; char p1[0x7c - 0x78]; };   // 0x7c bytes
struct Pair8 { uint a, b; };
struct sp_alloc { uint d[2]; };
template<class T> struct PVec {
    T* b; T* e; T* cap; sp_alloc a;      // 0x14 bytes
    T& operator[](uint i) { return b[i]; }
    uint size() const { return (uint)(e - b); }
};
struct Model {
    char p0[8];
    char ctx[0x10];                 // +0x08 (passed to the material manager)
    PVec<MeshEntry*> meshes;        // +0x18
    char q0[0x40 - 0x2c];
    PVec<IBuf*> ibs;                // +0x40
    char q1[0x68 - 0x54];
    PVec<VBuf*> vbs;                // +0x68
    char q2[0x90 - 0x7c];
    PVec<VDesc*> descs;             // +0x90
    char q3[0xb8 - 0xa4];
    PVec<void*> mats;               // +0xb8
    char q4[0xe0 - 0xcc];
    PVec<Pair8> pairs;              // +0xe0 (8-byte elements)
    PVec<void*> bvhs;               // +0xf4
    PVec<SubObj> subs;              // +0x108 (0x7c-byte elements)
    char block18[0x18];             // +0x11c
    char pad134[4];                 // +0x134
    char pad138[4];
    KeyOwner* extra;                // +0x13c
};
void* __cdecl Memmove(void* d, const void* s, uint n);          // 0x011e0744
struct KeyVec {
    Key* b; Key* e; Key* cap;
    sp_alloc a;
    uint hdr;                       // 0 header before the local buffer: never freed
    Key buf[32];
    KeyVec() { hdr = 0; b = buf; e = b; cap = buf + 32; }
    ~KeyVec() { if (b && ((uint*)b)[-1] != 0) Dealloc(b); }
    void GrowAndAppend(Key* pos, const Key& v);                 // 0x004e3e10
    void push_back(const Key& v) {
        if (e < cap) { Key* p = e++; if (p) *p = v; }
        else GrowAndAppend(e, v);
    }
    static void Dealloc(void* p);                               // 0x00f47380
};
struct BitVec {
    struct FixedAlloc {
        uint pad6c; uint* pool; uint pad74;
        FixedAlloc(uint* p) : pool(p) {}
    };
    uint* b; uint* e; uint* cap;
    FixedAlloc a;
    uint buf[32];
    BitVec() : a(buf) { e = a.pool; b = e; cap = buf + 32; }
    ~BitVec() { if (b && b != a.pool) KeyVec::Dealloc(b); }
    void Insert(uint* pos, uint n, const uint& val);            // 0x00766950
    void Erase(uint* first, uint* last) {
        Memmove(first, last, (uint)(e - last) * 4);
        e -= (last - first);
    }
    void ResizeFalse(uint n) {
        uint sz = (uint)(e - b);
        if (n > sz) {
            uint v = 0;
            Insert(e, n - sz, v);
        } else {
            Erase(b + n, e);
        }
    }
};
IMaterialMgr* __cdecl MaterialManager();                        // 0x0067dd70
bool __cdecl WriteUint32(Stream* s, const uint* p, uint n, int endian);   // 0x0093aa70
extern const uint kModelHeader;                                 // 0x0140dfd8 (4 bytes)
static inline void PutU32(Stream* s, uint v) { s->Write(&v, 4); }
template<class T> static inline int IndexOf(T* b, T* e, T v) {
    T* p = b;
    while (p != e && *p != v) ++p;
    return p == e ? -1 : (int)(p - b);
}
namespace SP {
class cGraphicsResourceFactory_s0076_89a0 { public:
    bool WriteResourceGameModel(Model* m, Stream* s);           // 0x007689a0 (ret 8)
    bool WriteResourceGameMeshes(void* obj, Stream* s);         // 0x00764f60
    bool WriteResourceRaster(void* obj, Stream* s);             // 0x00767ee0
    bool WriteResourceRasterArena(void* obj, Stream* s);        // 0x00763a80
    bool BuildJob(void* obj, void* a, uint flag);               // 0x00767590
    void WriteMaterialRef(Stream* s, void* p);                  // 0x007656c0 (ret 8)
    void WriteTail(Stream* s, Model* m);                        // 0x00764430 (ret 8)
    bool WriteResource(void* obj, void* src, void* u3, void* u4);   // 0x00769200 (ret 0x10)
};
}
typedef SP::cGraphicsResourceFactory_s0076_89a0 Factory;
// ---- items of slice s007689a0 end

// ---- items of slice s0076acd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl Alloc6(uint32_t size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
extern "C" void* __cdecl MessageServer();                                             // 0x67dcc0
extern "C" void* __cdecl App6750();                                                   // 0x67dd50
extern "C" void* __cdecl App6740();                                                   // 0x67dd40
extern "C" void* __cdecl App67dda0();                                                 // 0x67dda0
extern "C" void  __fastcall InitPhysics(void* self, int unused, int v);               // 0x7c4dd0
extern "C" void* __fastcall NewPhys(void* self, int unused);                          // 0x7c3f70
extern "C" void  __fastcall PhysFini(void* self, int unused);                         // 0x7c3ba0
extern "C" void  __fastcall PhysDel(void* self, int unused);                          // 0x7c4000
extern "C" void  __cdecl FUN_00761110(void* p);                                       // 0x761110
extern "C" void* __cdecl CreateRaster(int a, int b, int c, int d, int e);             // 0x761420
extern "C" void  __cdecl SetCubeMap(void* a, void* b, int c, int d, int e);          // 0x6e51b0
extern "C" bool  __cdecl FUN_011ef750r(void* out, int a, int b, void* p);             // 0x11ef750
extern "C" void  __cdecl FUN_011ef880r(void* p, void* out);                           // 0x11ef880
extern "C" void  __cdecl CopyViewer(void* p, void* a, int b, int c);                  // 0x7c50b0
extern "C" void  __cdecl JobRelease(void* p);                                         // 0x690120
extern "C" void  __cdecl FUN_7c4be0(void* p, void* a, int b);                         // 0x7c4be0
extern "C" void  __cdecl FUN_7c4ba0(void* p, float f);                                // 0x7c4ba0
extern "C" void  __cdecl FUN_7c53d0(void* p, float f);                                // 0x7c53d0
extern "C" void  __cdecl FUN_7c40f0(void* p);                                         // 0x7c40f0
extern "C" void  __cdecl QuatFromMatrix(void* out, void* m, float f);          // 0x472b80
extern "C" void  __cdecl Basis3Build(void* out, void* a, void* b);                    // 0x6b9440
extern "C" void  __cdecl CaptureCubeMap(void* worlds, float* w, void* center, int size, float nearDist,
float farDist, void* dir, int flags);          // 0x6e4210
extern "C" extern float g_f1630698;                                         // 0x01630698
extern "C" extern float g_f163069c;                                         // 0x0163069c
extern "C" extern float g_f16306a0;                                         // 0x016306a0
extern "C" extern float g_m16307d8;                                         // 0x016307d8
extern "C" extern char vtbl_13ec458[];
extern "C" extern char vtbl_140e254[];
extern "C" extern char vtbl_140e244[];
extern "C" extern char vtbl_140e278[];
extern "C" extern char vtbl_140e268[];
struct Vec3 { float x, y, z; };
struct Matrix33 { void Assign(const void* src); };   // 0x0041cb40
struct cSPTransform_s0076_acd0 {
    unsigned short mFlags;              // +0x00
    unsigned short mModificationCount;  // +0x02
    Vec3 mTranslation;                  // +0x04
    float mScale;                       // +0x10
    float mRotation[9];                 // +0x14
};
struct RTTCapture {
    void* mVt0;              // +0x00
    void* mVt1;              // +0x04
    void* mListenerBase;     // +0x08 base address handed to the message server
    void* mRes0c;            // +0x0c refcounted resource
    void* mRes10;            // +0x10 refcounted resource
    void* mPhysA[6];         // +0x14 six physics worlds (mode 0)
    void* mPhysB[6];         // +0x2c six physics worlds (mode 1)
    float mBasis[3];         // +0x44
    int   mFaceSize;         // +0x50 face dimension
    unsigned char m54;       // +0x54
    int   m58;               // +0x58
    unsigned char m5c;       // +0x5c
    unsigned char m5d;       // +0x5d
    void* m60;               // +0x60
    void* mPhysMain;         // +0x64 main physics world
    int   m68;               // +0x68
    void* mRenderTarget;     // +0x6c
    void* mRenderCtx;        // +0x70
    unsigned char pad74[0x9c - 0x74];
    void* mRes9c;            // +0x9c refcounted resource
};
static void SwapRefOwner(void** slot, void* value)
{
    void* old = *slot;
    if (value != old) {
        if (value) {                                                        // AddRef (vtable slot 0)
            void* vt = *(void**)value;
            ((void(__cdecl*)(void))*(void**)vt)();
        }
        *slot = value;
        if (old) {                                                          // Release (vtable slot 1)
            void* vt = *(void**)old;
            ((void(__cdecl*)(void))*((void**)((char*)vt + 4)))();
        }
    }
}
struct B1af { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); };
struct B2af {
virtual void b0();
virtual void b1();
virtual void b2();
virtual void b3();
    int mAtomic;              // +8 in Daf
    B2af() { (void)_InterlockedExchange((volatile long*)&mAtomic, 0); }
};
struct Daf : B1af, B2af {
    char m0c;                 // +0xc
    char padD[0x103];
    int m110, m114, m118, m11c;
    char m120;
    Daf();
    virtual ~Daf();
};
Daf::~Daf() { if (m11c) Dealloc((void*)m11c); }
struct E28 {
    int a0, a4;
    float f8, fc, f10, f14;
    unsigned char b18, b19;
    int i1c, i20, i24;
    E28& operator=(const E28& o);
};
struct D76bBase0 { virtual void Slot0(); ~D76bBase0() {} };
struct D76bBase1 { virtual void Slot0(); ~D76bBase1() {} };
struct ID76bRef { virtual void Slot0(); virtual void Release(); };
struct D76bRef {
    ID76bRef* mp;
    ~D76bRef() { if (mp) mp->Release(); }
};
struct D76bJob { void Release(); };   // 0x690120
struct D76bJobRef {
    D76bJob* mp;
    ~D76bJobRef() { if (mp) mp->Release(); }
};
struct D350Obj : D76bBase0, D76bBase1 {
    int m8;                   // +8
    D76bRef mc, m10, m14;     // +0xc
    int pad18;                // +0x18
    int m1c, m20;             // +0x1c
    char pad24[0x118];
    D76bJobRef m13c;          // +0x13c
    ~D350Obj();
};
struct D660Obj : D76bBase0, D76bBase1 {
    int m8;                   // +8
    D76bRef mc;               // +0xc
    int m10, m14, m18;
    ~D660Obj();
};
struct D350 {
    void* vtbl0;              // +0
    void* vtbl1;              // +4
    int m8;                   // +8
    int mc, m10, m14;
    int pad18;                // +0x18
    int m1c, m20;             // +0x1c
    char pad24[0x118];
    int m13c;                 // +0x13c
    D350();
    ~D350();
};
struct Viewer76 {
    void* mVt0;                 // +0x00
    void* mVt1;                 // +0x04
    void* m8;                   // +0x08
    void* mRes0c;               // +0x0c refcounted resource
    void* mRes10;               // +0x10 refcounted resource
    void* mRes14;               // +0x14 refcounted resource
    void* mPhys18;              // +0x18 physics world
    int   m1c;                  // +0x1c
    int   m20;                  // +0x20
    unsigned char m24;          // +0x24
    int   m28;                  // +0x28
    int   m2c;                  // +0x2c
    int   m30;                  // +0x30
    char  mName[0x138 - 0x34];  // +0x34 resource name
    unsigned char mHasName;     // +0x138
    unsigned char m139;         // +0x139
    void* mJob13c;              // +0x13c refcounted render job
};
struct D660 {
    void* vtbl0;              // +0
    void* vtbl1;              // +4
    int m8;                   // +8
    int mc, m10, m14, m18;
    D660();
    ~D660();
};
struct ViewerResource {
    virtual void AddRef();
    virtual void Release();
};
struct ViewerResourceRef {
    ViewerResource* object;
    void Reset() {
        _ReadWriteBarrier();
        ViewerResource* old = object;
        if (old) {
            object = 0;
            old->Release();
        }
    }
};
struct ViewData76b8 {
    int a, b, c, d;
    ViewData76b8(int x) : a(x), b(0), c(0), d(0) {}
};
struct ViewTarget76b8 {
virtual void v0();
virtual void v1();
virtual void v2();
    virtual void Render(void*, void*, const ViewData76b8&, void*);
};
// ---- items of slice s0076acd0 end

// ---- items of slice s0076bc50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p);   // 0x00f47380
extern char gEmptySpVec;   // 0x01667bac shared empty buffer
extern "C" void* __cdecl App(void);                                               // 0x67dd10
static inline void Deallocate(void* p) { EASTL_allocator_deallocate(p); }
struct cRenderTargetRectID { int mPageID; int mAllocID; };
struct RefCountV { virtual ~RefCountV(); int mRefCount; };
struct IHandlerRC {
    virtual ~IHandlerRC();
    virtual bool HandleMessage(int msgId, void* payload);
    virtual int  AddRef();
    virtual int  Release();
};
struct SpVec {
    void* mBegin;
    void* mEnd;
    void* mCapacity;
};
struct OwnedRefObj {
    virtual ~OwnedRefObj();
    virtual void Release();
};
struct cRTTCapture : RefCountV, IHandlerRC {
    cRenderTargetRectID mCubemapFaceRectID;   // +0x0c
    void*               mCubeViewers[6];      // +0x14
    void*               mImpostorViewers[6];  // +0x2c
    float               mSunDir[3];           // +0x44
    unsigned            mCurrentCubemapRes;   // +0x50
    bool                mOutCoeffs;           // +0x54
    char                pad55[3];
    char*               mCoeffFilename;       // +0x58
    bool                mBrightenDir;         // +0x5c
    bool                mGenerateSH;          // +0x5d
    char                pad5e[2];
    unsigned            mCubeCaptureMessage;  // +0x60
    void*               mSnapshotViewer;      // +0x64
    bool                mJobInProgress;       // +0x68
    char                pad69[3];
    void*               mRTTMgr;              // +0x6c
    void*               mGraphicsSystem;      // +0x70
    cRenderTargetRectID mTempSnapRectID;      // +0x74
    int                 mTempSnapRegistered;  // +0x7c
    void*               mTempSnapZRaster;     // +0x80  refcounted viewer/raster
    unsigned            mTempSnapResolution;  // +0x84
    void*               mOwnedBlock;          // +0x88  heap block with a 4-byte header
    void*               mField8c;             // +0x8c
    void*               mField90;             // +0x90
    char                pad94[8];             // +0x94
    OwnedRefObj*        mEffectsListener;     // +0x9c
    SpVec               mSceneViewJobs;       // +0xa0
    bool                mResetDone;           // +0xb0
    char                padb1[3];

    cRTTCapture();
    ~cRTTCapture();

    // @ 0x0076bc50  Snapshot/cubemap capture job (7 dwords, mixed inlined EASTL setup).
    bool TakeSnapshot(void* view, int res2, int res, int cube, unsigned flags,
                      unsigned p7, unsigned genSH);
    // @ 0x0076c210  Message-driven capture entry (1 arg).
    bool HandleCaptureMessage(void* payload);
    // @ 0x0076c7c0  IHandlerRC::HandleMessage (ecx = IHandlerRC subobject, i.e. capture+8).
    bool HandleMessage(int msgId, void* payload);
};
void* __fastcall Ctor76b350(void* self, int);                          // 0x76b350
void* __fastcall Ctor760c00(void* self, int);                          // 0x760c00
int   __fastcall FUN_00760fd0(void* self, int, int a, int type, int b); // 0x760fd0
void  __fastcall Ctor76b460(void* self, int, void* rect, void* o1, void* o2,
                            void* o3, int res, int scaled, int view, int cube,
                            int tiled, int tiles, int res80);           // 0x76b460
int   __fastcall CopyFrom76b8(void* self, int, void* other);            // 0x7c5240
int   __fastcall FUN_7c4b50(void* self, int, float scale);              // 0x7c4b50
int   __fastcall SetClearColor76c3(void* self, int, const void* color); // 0x7c3c20
typedef int   (__thiscall *FnI0)(void*);
typedef int   (__thiscall *FnI3)(void*, int, int, int*);
typedef void* (__thiscall *FnP0)(void*);
typedef void* (__thiscall *FnP1)(void*, int);
typedef void* (__thiscall *FnP2)(void*, int, int);
typedef void* (__thiscall *FnPp)(void*, void*);
typedef int*  (__thiscall *FnItem)(void*, int);
typedef void* (__thiscall *FnSend)(void*, void*, int, void*);
typedef void* (__thiscall *FnRT)(void*, cRenderTargetRectID*, int, int, int,
                                 int, int, int);
typedef void* (__thiscall *FnS3)(void*, int, int, const char*);
struct DriveObj {
    void* mVtbl;      // +0x00
    int   mRefCount;  // +0x04
    int   mField08;   // +0x08
    int   mField0C;   // +0x0c
    int   mField10;   // +0x10
    int   mField14;   // +0x14
    int   mField18;   // +0x18
    int   mField1C;   // +0x1c
};
struct Color4 { float r, g, b, a; };
struct SnapshotMsg {
    int   mField00;   // +0x00
    int   mField04;   // +0x04
    char  mField08;   // +0x08
    char  mPad09[3];
    int   mField0C;   // +0x0c
    int   mField10;   // +0x10
    int   mMsgID;     // +0x14
    void* mJob;       // +0x18
    void* mViewer;    // +0x1c
    int   mField20;   // +0x20
    int   mField24;   // +0x24
    int   mField28;   // +0x28
};
cRTTCapture::cRTTCapture()
    : mCubemapFaceRectID(), mOutCoeffs(false),
      mCoeffFilename(0), mBrightenDir(false), mGenerateSH(false),
      mCubeCaptureMessage(0), mSnapshotViewer(0), mJobInProgress(false),
      mRTTMgr(0), mGraphicsSystem(0),
      mTempSnapRectID(), mTempSnapRegistered(0), mTempSnapZRaster(0),
      mTempSnapResolution(0), mOwnedBlock(0), mField8c(0), mField90(0),
      mEffectsListener(0), mResetDone(true)
{
    mCubemapFaceRectID.mPageID = -1;
    mCubemapFaceRectID.mAllocID = -1;
    mTempSnapRectID.mPageID = -1;
    mTempSnapRectID.mAllocID = -1;
    mSceneViewJobs.mBegin = &gEmptySpVec;
    mSceneViewJobs.mEnd = &gEmptySpVec;
    mSceneViewJobs.mCapacity = &gEmptySpVec + 1;
}
cRTTCapture::~cRTTCapture()
{
    // mSceneViewJobs (three-pointer vector with a shared empty sentinel)
    {
        int n = (int)((char*)mSceneViewJobs.mCapacity - (char*)mSceneViewJobs.mBegin);
        if (n > 1 && mSceneViewJobs.mBegin != 0)
            Deallocate(mSceneViewJobs.mBegin);
    }
    if (mEffectsListener)
        mEffectsListener->Release();
    if (mOwnedBlock && *(int*)((char*)mOwnedBlock - 4) != 0)
        Deallocate(mOwnedBlock);
    if (mTempSnapZRaster)
        ((OwnedRefObj*)mTempSnapZRaster)->Release();
}
// ---- items of slice s0076bc50 end

// ---- items of slice s0076cc00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void*  EASTL_allocator_allocate(uint32_t n, const char* name, int a, int b, const char* f, int line); // 0x00f473a0
extern float g_01630698;              // 0x01630698
extern float g_0163069c;              // 0x0163069c
extern float g_016306a0;              // 0x016306a0
extern float g_016307d8;              // 0x016307d8
extern void __cdecl FUN_0075d870();                                                     // 0x0075d870
extern char g_emptyStr;                                                                 // 0x01667bac
#pragma intrinsic(_InterlockedExchange)
#define CAT2_(a, b) a##b
#define CAT_(a, b) CAT2_(a, b)
#define PV virtual void CAT_(_pv, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
static const char kAllocatorFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
struct E28_s0076_cc00 {
    int32_t       a0;                 // +0x00
    int32_t       a4;                 // +0x04 (low word used as a ushort by CaptureSceneViews)
    float         f8;                 // +0x08
    float         fc;                 // +0x0c
    float         f10;                // +0x10
    float         f14;                // +0x14
    uint8_t       b18;                // +0x18
    uint8_t       b19;                // +0x19
    uint8_t       pad1a[2];           // +0x1a
    int32_t       i1c;                // +0x1c
    int32_t       i20;                // +0x20
    int32_t       i24;                // +0x24
};
struct AssignThunk { void FUN_0076b1f0(const E28_s0076_cc00* src); };
E28_s0076_cc00* __cdecl FUN_0076b9a0(const E28_s0076_cc00* first, const E28_s0076_cc00* last, E28_s0076_cc00* dst);
struct EraseThunk { void FUN_0076cbb0(E28_s0076_cc00* position); };
struct ResetThunk { void FUN_0076b5d0(); };
struct AppObj;
AppObj* __cdecl FUN_0067dd10();
struct RecordThunk { void FUN_007c40f0(unsigned short* dst); };
struct E28Vec {
    E28_s0076_cc00* mBegin;   // +0
    E28_s0076_cc00* mEnd;     // +4
    E28_s0076_cc00* mCap;     // +8

    void insert(E28_s0076_cc00* position, const E28_s0076_cc00* value);   // @ 0x0076cc00
};
struct Matrix33_s0076_cc00 { void FUN_0041cb40(const void* src); };
struct cSPTransform_s0076_cc00 {
    unsigned short mFlags;              // +0x00
    unsigned short mModificationCount;  // +0x02
    Vec3           mTranslation;        // +0x04
    float          mScale;              // +0x10
    float          mRotation[9];        // +0x14
};
struct AppCtx50 {
    PV4 PV2 PV
    virtual void* GetTransform();        // +0x1c
};
struct AppObj {
    PV8 PV8 PV4
    virtual AppCtx50* GetCtx50();        // +0x50
};
struct MsgServer { PV4 PV virtual void Post(uint32_t id, void* msg, int flag); };
MsgServer* __cdecl MessageServer_s0076_cc00();                     // 0x0067dcc0
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);   // 0x00f473a0
void  operator delete[](void* p);                                           // 0x00f47380
void  operator delete(void* p);                                             // 0x00f47380
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}
struct SysObj {
    SysObj();                     // 0x007c3f70
    void Begin(void* p, int n);   // 0x007c4be0
    void End(int n);              // 0x007c3c50
    char pad[0x174];
};
struct Slot48Obj {
    PV8 PV8 PV2
    virtual void Slot48(int arg); // +0x48
};
struct PrepOut {
    char     pad00[0x40];
    uint32_t m40;      // +0x40
    char     pad44[0x78 - 0x44];
    uint32_t m78;      // +0x78
    uint32_t m7c;      // +0x7c
    uint32_t m80;      // +0x80
    uint32_t m84;      // +0x84
    float    m88;      // +0x88
    float    m8c;      // +0x8c
};
struct ContinueThunk { int FUN_0068f970(); };
struct CaptureHost {
    char             pad00[0x13c];
    ContinueThunk*   mJob;    // +0x13c
};
struct ReleaseObj { virtual void Slot0(); virtual void Release(); };
struct SnapshotWrap {
    char      pad00[0xc];
    SysObj*   mSystem;      // +0x0c
    int32_t   mFlags;       // +0x10
    int32_t   mFlags2;      // +0x14
    void*     mSceneArray;  // +0x18 array of 0x3c records, item pointer at record+0x38
    char      pad1c[0x50 - 0x1c];
    int32_t   mField50;     // +0x50
    char      pad54[0x68 - 0x54];
    uint8_t   mField68;     // +0x68
    char      pad69[0x70 - 0x69];
    void*     mField70;     // +0x70
    char      pad74[0x80 - 0x74];
    void*     mField80;     // +0x80
    void*     mField84;     // +0x84
    E28Vec    mJobs;        // +0x88

    void Teardown(int a, int b, int c, int d);              // @ 0x0076d970
    void CreateViewer(int32_t* rect);                       // @ 0x0076d8e0
    void Update(int unused);                                // @ 0x0076cd30
    void push_back(int a0, int a1, float a2, float a3, float a4, float a5,
                   int a6, char a7, char a8, int a9, int a10);   // @ 0x0076d5c0
    void PushThreeJobs(int a0, int a1, int a2, int a3, float a4, float a5,
                       float a6, float a7, int a8, char a9, char a10,
                       int a11, int a12, int a13);          // @ 0x0076d6e0
    void Effects_PrepareRender(int idx, void* a, PrepOut* out, char flag); // @ 0x0076da50
};
struct cFaceCamera;
void __cdecl CaptureSceneViews(int view, cFaceCamera** cameras, float a, float b,
                               float c, float d, unsigned short flags, char opt,
                               int x, int y, int z);          // 0x006e3100
struct RectThing {
    char    pad00[0x78];
    int32_t mW0;      // +0x78
    int32_t mH0;      // +0x7c
    int32_t mW1;      // +0x80
    int32_t mH1;      // +0x84
    float   mFrac;    // +0x88
    float   mScale;   // +0x8c

    // @ 0x0076d7d0
    void SetSize(uint16_t a, uint16_t b, uint16_t c, uint16_t d);
};
struct RefBaseA22 {
    virtual ~RefBaseA22();
    virtual void AddRef();
    virtual void Release();
    long mRefCount;
    int  mField8;
    int  mFieldC;
    int  mField10;
    int  mField14;
    RefBaseA22() : mField10(0) { _InterlockedExchange(&mRefCount, 0); }
};
struct DrvBA22 : RefBaseA22 {
    virtual ~DrvBA22();
    DrvBA22() {}
};
template <class T> struct ARef {
    T* mp;
    ARef(T* p) : mp(p) { if (mp) mp->AddRef(); }
    ~ARef() { if (mp) mp->Release(); }
    T* operator->() const { return mp; }
};
struct CapViewer {
    bool Copy(CapViewer* src, int a, int b);               // 0x007c50b0 (ret 0xc)
    void SetRaster(const void* key, int n);                // 0x007c4be0 (ret 8)
    void FUN_007c3c50(int n);                              // 0x007c3c50 (ret 4)
    void GetSize(float* w, float* h);                      // 0x007c40c0 (ret 8)
    void SetOffset(float x, float y);                      // 0x007c4ad0 (ret 8)
};
struct CapTarget { PV2 PV virtual void Process(int a, int b, void* s, uint32_t c); };   // +0x0c
struct EffectsMgr { PV8 PV8 virtual void SetXY(float a, float b); };                     // +0x40
EffectsMgr* __cdecl EffectsManager();                                                   // 0x0067ddd0
struct DevInfo {
    PV8 PV8 PV8 PV8 PV8 PV8 PV2 PV                                                     // slots 0..50
    virtual void GetPair(uint32_t* out);                                               // +0xcc
};
DevInfo* __cdecl GetDevInfo();                                                          // 0x0067dd40
struct PixFormat { char pad[0x10]; uint8_t mBits; };
struct RasterMgr {
    PV4                                                                                 // slots 0..3
    virtual uint32_t* Create(uint32_t* out, int w, int h, int fmt, int a, int b, int c);   // +0x10
    virtual void Release(uint32_t lo, uint32_t hi);                                     // +0x14
    virtual PixFormat* GetFormat(uint32_t lo, uint32_t hi);                             // +0x18
    PV2
    virtual void GetInfo(uint32_t lo, uint32_t hi, int* w2, int* h2, int* w, int* h);   // +0x24
    PV2
    virtual void Read(uint32_t lo, uint32_t hi, void* dst);                             // +0x30
    PV4 PV
    virtual void SetName(uint32_t lo, uint32_t hi, const char* name);                   // +0x48
};
RasterMgr* __cdecl GetRasterMgr();                                                      // 0x0067dda0
struct ReadMgr {
    PV8 PV8 PV4 PV2
    virtual void Fill(uint32_t* a, uint32_t* b, uint32_t c, float d);                  // +0x58
};
ReadMgr* __cdecl GetReadMgr();                                                          // 0x0067ddb0
struct JobRelease_s0076_cc00 { void Release(); };                                                  // 0x00690120
struct JobObj {
    void (__cdecl* mFn)();   // +0
    int mF4;
    char pad8[0x10];
    int mF18;                // +0x18
    void FUN_0068f9b0(void* daf);                                                       // 0x0068f9b0 (ret 4)
    void FUN_006909b0();                                                                // 0x006909b0
};
struct JobSvc { PV4 virtual void Create(JobObj** out); };                               // +0x10
JobSvc* __cdecl GetJobSvc();                                                            // 0x0068f4d0
struct Daf_s0076_cc00 {
    virtual void AddRef();
    virtual void Release();
    uint32_t mVptr2;
    long mAtomic;
    char mName[0x104];
    void* mFormat;       // +0x110
    int mW;              // +0x114
    int mH;              // +0x118
    void* mPixels;       // +0x11c
    char mFlag;          // +0x120
    Daf_s0076_cc00() throw();       // 0x0076af50
};
struct EStr {
    char* b; char* e; char* c;
    EStr() : b(&g_emptyStr), e(&g_emptyStr), c(&g_emptyStr + 1) {}
    ~EStr() { if (c - b > 1 && b) operator delete(b); }
    int sprintf(const char* fmt, ...);                                                  // 0x00472fe0
};
struct TileCapture {
    char   pad00[0xc];
    CapTarget* mTarget0;     // +0x0c
    CapTarget* mTarget1;     // +0x10
    CapTarget* mTarget2;     // +0x14
    CapViewer* mViewer;      // +0x18
    uint32_t   mRaster[2];   // +0x1c
    bool       mSized;       // +0x24
    uint32_t   mTiles;       // +0x28
    int        mW;           // +0x2c
    int        mH;           // +0x30
    char       mPath[5];     // +0x34
    char       pad39[0x139 - 0x39];
    bool       mDirect;      // +0x139
    char       pad13a[2];
    JobObj*    mJob;         // +0x13c

    void Capture(int a1, int a2, CapViewer** pViewer, uint32_t a4);
};
struct ViewState { CapViewer* viewer; int z0, z1, z2; };
#define RENDER_PASS()                                                                 \
    {                                                                                 \
        ViewState vs;                                                                 \
        vs.viewer = mViewer; vs.z0 = 0; vs.z1 = 0; vs.z2 = 0;                         \
        EffectsManager()->SetXY(0.0f, 0.0f);                                          \
        mTarget0->Process(a1, a2, &vs, a4);                                           \
        MessageServer_s0076_cc00()->Post(0x12d74a2, rawMsg, 0);                                  \
        mTarget1->Process(a1, a2, &vs, a4);                                           \
        EffectsManager()->SetXY(0.0f, 0.0f);                                          \
        mTarget2->Process(a1, a2, &vs, a4);                                           \
    }
// ---- items of slice s0076cc00 end

// @ 0x00761c50
unsigned int* __stdcall FUN_00761c50(unsigned int* out, Pair2* arr, int unused)
{
    out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0;
    out[0] = 0;
    unsigned int i = 0;
    Pair2* p = arr;
    do {
        if (p->x != 0)
            out[i] = (unsigned int)g_alloc->allocate((int)p->x, (int)p->y, 0, 0, 0, 0, 0, 0);
        i++;
        p++;
    } while (i < 4);
    return out;
}

// @ 0x00761cc0
void __stdcall FUN_00761cc0(void** arr)
{
    unsigned int i = 0;
    do {
        void* p = arr[i];
        if (p)
            g_alloc->Free(p);
        i++;
    } while (i < 4);
}

// @ 0x00761cf0
void __cdecl FUN_00761cf0(int n)
{
    float f = (float)(-n) * g_140dea0;
    g_16f8be8 = g_16f8bec * f + g_16f8be8;
    g_16f8bf8 = g_16f8bfc * f + g_16f8bf8;
    g_16f8c08 = g_16f8c0c * f + g_16f8c08;
    g_16f8c18 = g_16f8c1c * f + g_16f8c18;
    g_16f8c90 = g_16f8bec * f + g_16f8c90;
    g_16f8c94 = g_16f8bfc * f + g_16f8c94;
    g_16f8c98 = g_16f8c0c * f + g_16f8c98;
    g_16f8c9c = g_16f8c1c * f + g_16f8c9c;
}

// @ 0x00761dc0
void __cdecl FUN_00761dc0()
{
    if (*(int*)(*(int*)(g_15fd918 + 0x3c) + 0x110) != 0 && g_16fa5b8 != 0 &&
        *(int*)(g_16fa5b8 + 0x40) != 0) {
        float f1 = g_13eb1bc / (float)*(unsigned short*)(*(int*)(g_16fa5b8 + 0x40) + 0xc);
        float f2 = g_1485720 / (float)*(unsigned short*)(*(int*)(g_16fa5b8 + 0x40) + 0xe);
        g_16f8be0 = g_16f8bec * f1 + g_16f8be0;
        g_16f8c70 = g_16f8bec * f1 + g_16f8c70;
        g_16f8bf0 = g_16f8bfc * f1 + g_16f8bf0;
        g_16f8c74 = g_16f8bfc * f1 + g_16f8c74;
        g_16f8c00 = g_16f8c0c * f1 + g_16f8c00;
        g_16f8c78 = g_16f8c0c * f1 + g_16f8c78;
        g_16f8c10 = g_16f8c1c * f1 + g_16f8c10;
        g_16f8c7c = g_16f8c1c * f1 + g_16f8c7c;
        g_16f8be4 = g_16f8bec * f2 + g_16f8be4;
        g_16f8c80 = g_16f8bec * f2 + g_16f8c80;
        g_16f8bf4 = g_16f8bfc * f2 + g_16f8bf4;
        g_16f8c84 = g_16f8bfc * f2 + g_16f8c84;
        g_16f8c04 = g_16f8c0c * f2 + g_16f8c04;
        g_16f8c88 = g_16f8c0c * f2 + g_16f8c88;
        g_16f8c14 = g_16f8c1c * f2 + g_16f8c14;
        g_16f8c8c = g_16f8c1c * f2 + g_16f8c8c;
    }
}

// @ 0x00761f90
void __cdecl FUN_00761f90(int a, unsigned int color, int chunk)
{
    unsigned int saved = g_16f9200;
    g_16fa38c |= 2;
    g_16f9200 = 3;
    int i1 = (int)FUN_011f1120();
    unsigned short w = *(unsigned short*)(*(int*)(i1 + 0x40) + 0xc);
    int i2 = (int)FUN_011f1120();
    unsigned short h = *(unsigned short*)(*(int*)(i2 + 0x40) + 0xe);
    unsigned int rgba = SP_ColorRGBAToU32(color);
    (void)a;
    float* out = 0;
    char b[4];
    if (FUN_006ddcc0(2, 4, (int)&out, (int)b)) {
        float fw = (float)w;
        float fh = (float)h;
        float fc;
        *(unsigned int*)&fc = rgba;
        float dx = (g_16077c4 * g_two) / fw;
        float dy = (g_16077c8 * g_two) / fh;
        out[0]  = g_neg1 - dx;   out[1]  = 0.0f;      out[2]  = g_neg1 - dy;
        out[4]  = 0.0f;          out[5]  = g_one;      out[6]  = g_one - dx;
        out[7]  = 0.0f;          out[8]  = g_neg1 - dy;
        out[0xc] = g_one - dx;   out[0xd] = 0.0f;      out[0xe] = g_one - dy;
        out[0x12] = g_neg1 - dx; out[0x13] = 0.0f;     out[0x14] = g_one - dy;
        out[0x10] = g_one;       out[0x11] = 0.0f;     out[0x16] = 0.0f;
        out[0x17] = 0.0f;        out[10]  = g_one;     out[0xb]  = g_one;
        out[3]  = fc;            out[9]   = fc;
        out[0xf] = fc;           out[0x15] = fc;
        FUN_006ddd10(3, (void*)chunk);
    }
    g_16fa38c |= 2;
    g_16f9200 = saved;
}

// @ 0x00762250
Obj62250::Obj62250(const int* src, SP::RefCountedAt8* r)
: d(*(const O62Desc*)src), ref(r), state(-1)
{
}

// @ 0x007622e0
Obj62250::~Obj62250()
{
    SP::RefCountedAt8* held = ref.p;
    if (held == 0) {
        void* p = (void*)d.a[1];
        FUN_011fb220(p);
        g_alloc_s0076_1dc0->Free(p);
    }
}

// @ 0x00762380
int Map2380::find()
{
    if (cached >= 0) return cached;
    void* b = base;
    int n = *(int*)(*(int*)((char*)b + 0x3c) + 8);
    unsigned int* a = *(unsigned int**)((char*)b + 0x34);
    unsigned int local = 0;
    unsigned int* pl = &local;
    if (n > 0) {
        do {
            unsigned int* p;
            if (*pl < a[0]) p = &a[0]; else p = pl;
            *pl = *p;
            if (*pl < a[1]) p = &a[1]; else p = pl;
            *pl = *p;
            if (*pl < a[2]) p = &a[2]; else p = pl;
            *pl = *p;
            a += 4;
        } while (--n != 0);
    }
    cached = (int)(*pl + 1);
    return cached;
}

// @ 0x007623f0
int __cdecl FUN_007623f0(int a, int b, int c, int d, int e, int f)
{
    D3 d3 = FUN_00761300(0);
    int local[4];
    local[0] = (int)FUN_00928a30((void*)d3.v[0].a, (void*)d3.v[0].b, 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    int o = (int)FUN_011f3220(local);
    *(int*)(o + 0x20) = a;
    *(int*)(o + 0x24) = b;
    *(int*)(o + 0x28) = c;
    *(int*)(o + 0x2c) = a;
    *(int*)(o + 0x10) = d;
    *(int*)(o + 0x14) = e;
    *(int*)(o + 0x18) = f;
    return o;
}

// @ 0x007624c0
int __cdecl FUN_007624c0(float a, float b, float c, int d, int e, int f, float p7)
{
    D3 d3 = FUN_00761300(1);
    int local[4];
    local[0] = (int)FUN_00928a30((void*)d3.v[0].a, (void*)d3.v[0].b, 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    int o = (int)FUN_011fa2d0(local, 1);
    // {a, c, b, a} packed as one 16-byte store at +0x30.
    __m128 packed;
    packed = _mm_set_ps(a, b, c, a);
    _mm_storeu_ps((float*)(o + 0x30), packed);
    *(int*)(o + 0x10) = d;
    *(int*)(o + 0x14) = e;
    *(int*)(o + 0x18) = f;
    if (p7 > g_1538fe8b) {
        *(float*)(o + 4) = p7;
        *(float*)(o + 8) = 1.0f / p7;
    } else {
        *(float*)(o + 4) = 0.0f;
        *(float*)(o + 8) = g_140de58b;
    }
    return o;
}

// @ 0x00762900
void Map262900::insert(void* outIter, const unsigned int* payload, TrueType)
{
    unsigned int key = payload[0];
    unsigned int b = key % bucketCount;
    unsigned int* slot = (unsigned int*)((char*)buckets + b * 4);
    unsigned int* e = (unsigned int*)*slot;
    while (e) {
        if (key == *e) {
            *(unsigned int**)outIter = e;
            *((unsigned char*)outIter + 8) = 0;
            *(unsigned int**)((char*)outIter + 4) = slot;
            return;
        }
        e = (unsigned int*)e[4];
    }

    // No existing node: let the policy grow the table if needed, then allocate.
    unsigned char didRehash = 0;
    unsigned int newBucketCount = 0;
    FUN_00921440(&didRehash, bucketCount, count, 1);
    unsigned int* node = (unsigned int*)FUN_00f473a0(0x14, "Graphics", 0, 0, kEastlAllocFile, 0xd1);
    if (node) {
        node[0] = payload[0];
        node[1] = payload[1];
        node[2] = payload[2];
        node[3] = payload[3];
    }
    node[4] = 0;
    if (didRehash) {
        b = key % newBucketCount;
        FUN_006f1ab0(newBucketCount);
    }
    slot = (unsigned int*)((char*)buckets + b * 4);
    node[4] = *slot;
    *slot = (unsigned int)node;
    ++count;
    *(unsigned int**)outIter = node;
    *((unsigned char*)outIter + 8) = 1;
    *(unsigned int**)((char*)outIter + 4) = slot;
}

// @ 0x00762b00
int Hash262b00::findInsert(unsigned int* key)
{
    Iter it;
    find(&it, key);
    if (it.node == *(void**)((char*)buckets + bucketCount * 4)) {
        CursorPair262b00 pair(*key, Cursor262b00());
        ((Map262900*)this)->insert(&it, &pair.first, Map262900::TrueType());
    }
    return (int)(char*)it.node + 4;
}

// @ 0x00762d70
void __cdecl TeardownLightArrays(int count, void** arrays)
{
    void*  vec[3] = { 0, 0, 0 };   // scratch set of already-seen items
    for (int i = 0; i < count; i++) {
        int* arr = (int*)arrays[i];
        int  n   = arr[4];
        for (int j = 0; j < n; j++) {
            void* item = *(void**)((char*)arr + 0x24 + j * 4);
            bool found = false;
            for (void** it = (void**)vec[0]; it != (void**)vec[1]; ++it)
                if (*it == item) { found = true; break; }
            if (found)
                continue;
            F_11f3130(*(void**)item);                     // add-ref
            F_9276c0(g_mgr16c8b44, *(void**)item);
            void* tmp = item;
            F_762890((void*)0x1538ff0, &tmp);
            F_11f3580(item);                              // release
            F_9276c0(g_mgr16c8b44, item);
            if (vec[1] == vec[2]) {
                F_6c1570(vec, vec[1], &item);
            } else {
                *(void**)vec[1] = item;
                vec[1] = (char*)vec[1] + 4;
            }
        }
        void* obj8 = *(void**)((char*)arr + 8);
        void* tmp8 = obj8;
        F_762890((void*)0x1539010, &tmp8);
        F_11f4e90(obj8);
        F_9276c0(g_mgr16c8b44, obj8);
        F_9276c0(g_mgr16c8b44, arr);
    }
    if (vec[0] != 0 && vec[0] != (void*)0)
        EA_Delete(vec[0]);
}

// @ 0x00762f00
void __cdecl SetFlag1630180(unsigned char v)
{ g_flags1630180 = v; }

// @ 0x00762f10
void __cdecl ReleaseViaSlot8(IObj* p)
{
    if (p) p->s2(1);
}

// @ 0x00762f30
void* __stdcall MakeObj762f30(const int* src)
{
    Obj762f30* p = (Obj762f30*)EA_New(0x10, "App", 0, 0, 0, 0);
    if (src != 0) {
        if (p != 0) {
            p->a4 = src[0];
            p->a8 = src[1];
            ((LockMap*)((char*)p + 8))->store(0, 0);
            return p;
        }
    } else {
        if (p != 0) {
            ((LockMap*)((char*)p + 8))->store(0, 0);
            return p;
        }
    }
    return 0;
}

// @ 0x00768540
C68370::~C68370()
{
}

// @ 0x007689a0
bool Factory::WriteResourceGameModel(Model* m, Stream* s)
{
    s->Write(&kModelHeader, 4);
    {
        // Collect the resource keys referenced by the sub-objects and the extra object.
        KeyVec keys;
        uint nsub = (uint)(m->subs.e - m->subs.b);
        for (uint i = 0; i < nsub; ++i) {
            SubObj* so = &m->subs[i];
            KeyOwner* o = so->owner;
            if (o) keys.push_back(o->key);
        }
        if (m->extra) keys.push_back(m->extra->key);

        // The material manager adds each material's dependencies.
        uint nm = (uint)(m->mats.e - m->mats.b);
        for (uint i = 0; i < nm; ++i) {
            uint id = MaterialManager()->GetMaterialID(m->mats[i]);
            MaterialManager()->CollectKeys(1, &id, &keys, 0);
        }

        uint nk = (uint)(keys.e - keys.b);
        WriteUint32(s, &nk, 1, 0);
        uint cnt = (uint)(keys.e - keys.b);
        Key* k = keys.b;
        for (uint i = 0; i < cnt; ++i) {
            uint v = k[i].a;
            if (WriteUint32(s, &v, 1, 0)) {
                v = k[i].c;
                if (WriteUint32(s, &v, 1, 0)) {
                    v = k[i].b;
                    WriteUint32(s, &v, 1, 0);
                }
            }
            k = keys.b;
        }
    }

    uint nmesh = (uint)(m->meshes.e - m->meshes.b);
    s->Write(&nmesh, 4);
    s->Write(m->block18, 0x18);
    s->Write(m->pad134, 4);

    // Index buffers.
    uint nib = (uint)(m->ibs.e - m->ibs.b);
    s->Write(&nib, 4);
    for (uint i = 0; i < nib; ++i) {
        IBuf* ib = m->ibs.b[i];
        uint prim = ib->primType;
        s->Write(&prim, 4);
        uint num = ib->numIndices;
        s->Write(&num, 4);
        uint depth = ib->GetDepth();
        s->Write(&depth, 4);
        LockedRegion r;
        ib->Lock(1, &r);
        void* data = r.data;
        uint size = (depth * num) >> 3;
        s->Write(&size, 4);
        s->Write(data, size);
        ib->Unlock(&r);
    }

    // Vertex descriptors.
    uint ndesc = (uint)(m->descs.e - m->descs.b);
    s->Write(&ndesc, 4);
    for (uint i = 0; i < ndesc; ++i) {
        VDesc* d = m->descs.b[i];
        d->lockFlags |= 1;
        uint ne = d->numElements;
        s->Write(&ne, 4);
        for (uint j = 0; j < ne; ++j)
            s->Write(d->elements + j * 12, 0xc);
        d->Finish();
    }

    // Vertex buffers.
    uint nvb = (uint)(m->vbs.e - m->vbs.b);
    s->Write(&nvb, 4);
    for (uint i = 0; i < nvb; ++i) {
        VBuf* vb = m->vbs.b[i];
        VDesc* want = vb->desc;
        int idx = IndexOf(m->descs.b, m->descs.e, want);
        PutU32(s, idx);
        uint nv = vb->numVertices;
        s->Write(&nv, 4);
        void* data;
        VBuf* lvb;
        void* p = vb->Lock(1, vb->Bytes(vb->base), vb->Bytes(vb->numVertices));
        if (p) { data = p; lvb = vb; }
        uint size = lvb->desc->stride * nv;
        s->Write(&size, 4);
        s->Write(data, size);
        vb->Unlock();
    }

    // Mesh entries: which index/vertex buffer each uses.
    for (uint i = 0; i < nmesh; ++i) {
        MeshEntry* e = m->meshes.b[i];
        VBuf* evb = e->vb;
        IBuf* eib = e->ib;
        int ii = IndexOf(m->ibs.b, m->ibs.e, eib);
        PutU32(s, ii);
        int vi = IndexOf(m->vbs.b, m->vbs.e, evb);
        PutU32(s, vi);
    }

    BitVec flags;
    flags.ResizeFalse(nmesh);
    MaterialManager()->FlagMaterials(nmesh, m->mats.b, flags.b);
    s->Write(flags.b, nmesh * 4);
    MaterialManager()->WriteMaterials(nmesh, flags.b, s, m->ctx);

    uint nbvh = (uint)(m->bvhs.e - m->bvhs.b);
    if (nbvh > nmesh) nbvh = nmesh;
    s->Write(&nbvh, 4);
    for (uint i = 0; i < nbvh; ++i) {
        void* p = m->bvhs.b[i];
        uint present = p != 0;
        WriteUint32(s, &present, 1, 0);
        if (p) WriteMaterialRef(s, p);
    }

    uint npair = (uint)(m->pairs.e - m->pairs.b);
    if (npair > nmesh) npair = nmesh;
    s->Write(&npair, 4);
    for (uint i = 0; i < npair; ++i) {
        Pair8* pr = m->pairs.b + i;
        s->Write(&pr->a, 4);
        s->Write(&pr->b, 4);
    }

    WriteTail(s, m);

    KeyOwner* ex = m->extra;
    Key last;
    last.a = 0; last.c = 0; last.b = 0xffffffff;
    if (ex) { last.a = ex->key.a; last.b = ex->key.b; last.c = ex->key.c; }
    s->Write(&last, 0xc);
    return true;
}

// @ 0x0076acd0
bool __fastcall RegisterListener(RTTCapture* self, int unused)
{
    (void)unused;
    void* ms = MessageServer();
    if (ms) {
        static const int tags[9] = {0x1c91267, 0x3ea7e1b, 0x1c7f3db, 0x1c7f90a, 0x1c7fd85,
                                    0x202ce02, 0x1fb2458, 0x1c91276, 0x1c9127b};
        void* base = self ? &self->mListenerBase : 0;
        for (int i = 0; i < 9; i++)
            ((void(__thiscall**)(void*, void*, int))*(void***)ms)[8](ms, base, tags[i]);
    }
    void* a = Alloc6(0x174, "Graphics", 0, 0, 0, 0);
    void* obj = a ? NewPhys(a, 0) : 0;
    self->mPhysMain = obj;
    InitPhysics(obj, 0, 0);
    for (int i = 0; i < 6; i++) {
        void* q = Alloc6(0x174, "Graphics", 0, 0, 0, 0);
        void* o = q ? NewPhys(q, 0) : 0;
        self->mPhysA[i] = o;
        InitPhysics(o, 0, 0);
        FUN_7c53d0(o, 90.0f);
    }
    for (int i = 0; i < 6; i++) {
        void* q = Alloc6(0x174, "Graphics", 0, 0, 0, 0);
        void* o = q ? NewPhys(q, 0) : 0;
        self->mPhysB[i] = o;
        InitPhysics(o, 0, 1);
        FUN_7c53d0(o, 90.0f);
        FUN_7c4ba0(o, 2.0f);
    }
    void* app = App6750();
    ((void(__thiscall**)(void*))*(void***)app)[7](app);
    self->mRenderTarget = App67dda0();
    self->mRenderCtx = App6740();
    return true;
}

// @ 0x0076af50
Daf::Daf()
{
    m110 = 0; m114 = 0; m118 = 0; m11c = 0;
    m120 = 1;
    m0c = 0;
}

// 0x0076b000 (byte-exact lifted version: match/slices/s0076b000/s0076b000.cpp)
static void FreePhysWorld(void*& slot)
{
    if (slot == 0)
        return;
    PhysFini(slot, 0);
    void* p = slot;
    if (p) {
        PhysDel(p, 0);
        Dealloc(p);
    }
}

// @ 0x0076b1f0
E28& E28::operator=(const E28& o)
{
    a0 = o.a0; a4 = o.a4;
    f8 = o.f8; fc = o.fc; f10 = o.f10; f14 = o.f14;
    b18 = o.b18; b19 = o.b19;
    i1c = o.i1c; i20 = o.i20; i24 = o.i24;
    return *this;
}

// @ 0x0076b240
bool __fastcall RefreshCubeMap(void* self, int, int unused)
{
    (void)unused;
    char* s = (char*)self;
    void* v = *(void**)(s + 0x70);
    int r = ((int(__thiscall**)(void*))*(void***)v)[0x80 / 4](v);
    if (r)
        FUN_00761110((void*)r);
    void* raster = CreateRaster(*(int*)(s + 0x50), *(int*)(s + 0x50), 1, 0x1208, 0x15);
    for (int i = 0; i < 6; i++) {
        char out[8] = {0};
        *(char*)((char*)raster + 0x12) = (char)i;
        if (FUN_011ef750r(out, 0, 2, raster)) {
            void* m = *(void**)(s + 0x6c);
            ((void(__thiscall**)(void*, char*, char*, char*))*(void***)m)[0xc](m, s + 0xc, s + 0x10, out);
            FUN_011ef880r(raster, out);
        }
    }
    void* m2 = *(void**)(s + 0x70);
    ((void(__thiscall**)(void*, void*))*(void***)m2)[0x94 / 4](m2, raster);
    void* m3 = *(void**)(s + 0x6c);
    ((void(__thiscall**)(void*, char*, char*))*(void***)m3)[5](m3, s + 0xc, s + 0x10);
    if (*(char*)(s + 0x5d))
        SetCubeMap(raster, *(void**)(s + 0x50), *(unsigned char*)(s + 0x5c), *(int*)(s + 0x58), 0);
    if (*(void**)(s + 0x60) && MessageServer()) {
        void* ms = MessageServer();
        ((void(__thiscall**)(void*, void*, int, int, int))*(void***)ms)[6](ms, *(void**)(s + 0x60), 0, 0, 0);
    }
    void* m4 = *(void**)(s + 0x70);
    ((void(__thiscall**)(void*, int))*(void***)m4)[0x44 / 4](m4, 0);
    return true;
}

// @ 0x0076b350
D350::D350()
{
    vtbl1 = vtbl_13ec458;
    m8 = 0;
    vtbl0 = vtbl_140e254;
    vtbl1 = vtbl_140e244;
    mc = 0; m10 = 0; m14 = 0;
    m1c = -1; m20 = -1;
    m13c = 0;
}

// @ 0x0076b3c0
D350Obj::~D350Obj()
{
}

// @ 0x0076b460
void __fastcall Ctor76b460(Viewer76* self, int unused, int* block, void* res0c, void* res10, void* res14, int a6, int a7, const char* name, int a9, unsigned char a10, int a11, unsigned char a12)
{
    (void)unused;
    void* q = Alloc6(0x174, "Graphics", 0, 0, 0, 0);
    void* o = q ? NewPhys(q, 0) : 0;
    self->mPhys18 = o;
    InitPhysics(o, 0, 0);
    self->m1c = block[0];
    self->m20 = block[1];
    SwapRefOwner(&self->mRes0c, res0c);
    SwapRefOwner(&self->mRes10, res10);
    SwapRefOwner(&self->mRes14, res14);
    self->m24 = a10;
    self->m30 = a7;
    self->m28 = a11;
    self->m2c = a6;
    self->mHasName = a9 != 0;
    self->m139 = a12;
    if (name) {
        char* d = self->mName;
        do { *d++ = *name; } while (*name++);
    } else {
        self->mName[0] = 0;
    }
}

// @ 0x0076b5d0
void __fastcall ResetRefs76bs(void* self)
{
    char* s = (char*)self;
    if (*(void**)(s + 0x13c)) {
        void* p = *(void**)(s + 0x13c);
        if (p) { *(void**)(s + 0x13c) = 0; ((void(__thiscall*)(void*))JobRelease)(p); }
    }
    if (*(void**)(s + 0x18)) {
        ((void(__thiscall*)(void*))PhysFini)(*(void**)(s + 0x18));
        void* p = *(void**)(s + 0x18);
        if (p) { ((void(__thiscall*)(void*))PhysDel)(p); Dealloc(p); }
    }
    if (*(void**)(s + 0xc)) { void* p = *(void**)(s + 0xc); *(void**)(s + 0xc) = 0; ((void(__thiscall**)(void*))*(void***)p)[1](p); }
    if (*(void**)(s + 0x10)) { void* p = *(void**)(s + 0x10); *(void**)(s + 0x10) = 0; ((void(__thiscall**)(void*))*(void***)p)[1](p); }
    if (*(void**)(s + 0x14)) { void* p = *(void**)(s + 0x14); *(void**)(s + 0x14) = 0; ((void(__thiscall**)(void*))*(void***)p)[1](p); }
}

// @ 0x0076b660
D660::D660()
{
    vtbl1 = vtbl_13ec458;
    m8 = 0;
    vtbl0 = vtbl_140e278;
    vtbl1 = vtbl_140e268;
    mc = 0; m10 = 0;
    m14 = -1; m18 = -1;
}

// @ 0x0076b6c0
D660Obj::~D660Obj()
{
}

// @ 0x0076b720
void __fastcall Ctor76b720(void* self, int, int a2, int a3, int* a4, void* a5, char a6)
{
    char* s = (char*)self;
    volatile int pad[4];
    pad[0] = 0;
    void* q = Alloc6(0x174, "Graphics", 0, 0, 0, 0);
    void* o = q ? ((void*(__thiscall*)(void*))NewPhys)(q) : 0;
    *(void**)(s + 0x10) = o;
    ((void(__thiscall*)(void*, int))InitPhysics)(o, 0);
    ((void(__thiscall*)(void*, void*, int, int))CopyViewer)(o, (void*)a3, 0, 0);
    *(int*)(s + 0x14) = a4[0];
    *(int*)(s + 0x18) = a4[1];
    void* old = *(void**)(s + 0xc);
    if (a5 != old) {
        if (a5) ((void(__thiscall**)(void*))*(void***)a5)[0](a5);
        *(void**)(s + 0xc) = a5;
        if (old) ((void(__thiscall**)(void*))*(void***)old)[1](old);
    }
    *(char*)(s + 0x1c) = a6;
    *(int*)(s + 0x20) = a2;
}

// @ 0x0076b840
void __fastcall ReleaseViewer76b8(void* self)
{
    char* s = (char*)self;
    void* p = *(void**)(s + 0x10);
    if (p) {
        ((void(__thiscall*)(void*))PhysFini)(p);
        void* q = *(void**)(s + 0x10);
        if (q) { ((void(__thiscall*)(void*))PhysDel)(q); Dealloc(q); }
    }
    ViewerResourceRef& resource = *reinterpret_cast<ViewerResourceRef*>(s + 0xc);
    if (resource.object)
        resource.Reset();
}

// @ 0x0076b890
void __fastcall RenderViewer76b8(void* self, int, void* a2, void* a3, void* a4, void* a5)
{
    char* s = (char*)self;
    if (!*(void**)(s + 0xc))
        return;
    ((void(__thiscall*)(void*, void*, int))FUN_7c4be0)(*(void**)(s + 0x10), s + 0x14, 1);
    void* m = App6740();
    ((void(__thiscall**)(void*, int))*(void***)m)[0x44 / 4](m, 1);
    void* m2 = App6740();
    ((void(__thiscall**)(void*, char*))*(void***)m2)[0x9c / 4](m2, s + 0x14);
    (*(ViewTarget76b8**)(s + 0xc))->Render(a2, a3, ViewData76b8(*(int*)(s + 0x10)), a5);
    void* m3 = App6740();
    ((void(__thiscall**)(void*, int))*(void***)m3)[0x44 / 4](m3, 0);
    (void)a4;
}

// @ 0x0076b930
void* __cdecl QuatFromBasis(void* out, void* src, float w)
{
    float m[9];
    int* s9 = (int*)src;
    m[0] = *(float*)&s9[0];
    m[1] = *(float*)&s9[1];
    m[2] = *(float*)&s9[2];
    m[3] = *(float*)&s9[4];
    m[4] = *(float*)&s9[5];
    m[5] = *(float*)&s9[6];
    m[6] = *(float*)&s9[8];
    m[7] = *(float*)&s9[9];
    m[8] = *(float*)&s9[10];
    QuatFromMatrix(out, m, w);
    return out;
}

// @ 0x0076b9a0
E28* __cdecl CopyRange28(E28* first, E28* last, E28* dest)
{
    E28* d = dest;
    while (first != last) {
        if (d)
            *d = *first;
        first = (E28*)((char*)first + 0x28);
        d = (E28*)((char*)d + 0x28);
    }
    return d;
}

// @ 0x0076ba30
void __fastcall CaptureCubeMap76ba(RTTCapture* self, int unused, int faceSize, Vec3* center, int a4, int a5, char orient, char a7, unsigned char a8, int a9, unsigned char a10, Vec3* dir, int a12)
{
    (void)unused; (void)a4; (void)a5;
    self->mBasis[0] = 0.0f;
    self->mBasis[1] = 0.0f;
    self->mBasis[2] = 0.0f;
    Vec3 from = {0.0f, 0.0f, 0.0f};
    if (center)
        from = *center;
    if (dir) {
        self->mBasis[0] = dir->x;
        self->mBasis[1] = dir->y;
        self->mBasis[2] = dir->z;
    }
    float w = 1.0f;
    if (orient) {
        cSPTransform_s0076_acd0 xf;                       // orientation basis for the capture
        xf.mFlags = 0;
        xf.mModificationCount = 0;
        xf.mTranslation.x = g_f1630698;
        xf.mTranslation.y = g_f163069c;
        xf.mTranslation.z = g_f16306a0;
        xf.mScale = 1.0f;
        ((Matrix33*)xf.mRotation)->Assign(&g_m16307d8);
        int* app = (int*)App6740();
        int* ctx = (int*)(*(int(__thiscall**)(int*))(*app + 0x50))(app);
        (*(void(__thiscall**)(int*, cSPTransform_s0076_acd0*))(*ctx + 0x1c))(ctx, &xf);
        FUN_7c40f0(&xf);
        from = xf.mTranslation;
        float basis[16];                        // 4x4 basis the quaternion is read from
        Basis3Build(basis, &xf, 0);
        float* quat = (float*)QuatFromBasis(&basis[8], basis, 0.0f);
        w = quat[3];
    }
    self->m58 = a9;
    self->m54 = a8;
    self->m60 = (void*)a5;
    self->m5d = a7;
    self->mFaceSize = faceSize;
    self->m5c = a10;
    ((void(__thiscall**)(void*, int))*(void***)self->mRenderCtx)[0x44 / 4](self->mRenderCtx, 1);
    CaptureCubeMap(self->mPhysA, &w, &from, faceSize, 0.1f, 10000.0f, dir, a12);
}

// @ 0x0076bc50
bool cRTTCapture::TakeSnapshot(void* view, int res2, int res, int cube, unsigned flags, unsigned p7, unsigned genSH)
{
    void* appCheck = App6740();
    if ((unsigned char)((FnI0)(*(void***)appCheck)[0x3c / 4])(appCheck))
        return false;

    // Replace the stored temp-snapshot raster (0x140-byte D350 object).
    {
        void* raw = Alloc6(0x140, "Graphics", 0, 0, 0, 0);
        void* nw = raw ? Ctor76b350(raw, 0) : 0;
        void* old = mTempSnapZRaster;
        if (nw != old) {
            if (nw)
                ((FnP0)(*(void***)nw)[0])(nw);
            mTempSnapZRaster = nw;
            if (old)
                ((FnP0)(*(void***)old)[1])(old);
        }
    }

    mTempSnapResolution = (unsigned)res2;

    cRenderTargetRectID rect;
    rect.mPageID = -1;
    rect.mAllocID = -1;
    int res80 = (res == 0x80);

    void* p = App6750();
    int* dims = (int*)((FnP0)(*(void***)p)[0x1c / 4])(p);
    int w = dims[0];
    int h = dims[1];
    if (res < w)
        res = w;
    float scale = (float)w / (float)h;
    float invScale = 1.0f / scale;
    int half = (int)_mm_cvtss_si32(_mm_set_ss((float)(unsigned)res * invScale));

    int tiles = 1;
    char tiled = 0;
    if (genSH == 0 && res == w) {
        void* gfx = mGraphicsSystem;
        ((FnP0)(*(void***)gfx)[0x88 / 4])(gfx);
        ((FnPp)(*(void***)gfx)[0xcc / 4])(gfx, &rect);
    } else {
        tiled = 1;
        if (w < res) {
            tiles = (w - 1 + res) / w;
            res = w * tiles;
        }
        void* rtt = App67dda0();
        cRenderTargetRectID out;
        cRenderTargetRectID* rid = (cRenderTargetRectID*)
            ((FnRT)(*(void***)rtt)[0x10 / 4])(rtt, &out, res / tiles,
                                              half / tiles, 0x15, 0, -1, 0);
        int page = rid->mPageID;
        int alloc = rid->mAllocID;
        ((FnS3)(*(void***)rtt)[0x48 / 4])(rtt, page, alloc, "TempSnapshot");
        if (alloc != -1) {
            void* reg = ((FnP2)(*(void***)rtt)[0x18 / 4])(rtt, page, alloc);
            mTempSnapRegistered = (int)reg;
            mTempSnapRectID.mPageID = page;
            mTempSnapRectID.mAllocID = alloc;
        }
        rect.mPageID = mTempSnapRectID.mPageID;
        rect.mAllocID = mTempSnapRectID.mAllocID;
    }

    void* mgr = App6750();

    // Three helper objects dispatched by scene-view item type.
    void* o1;
    {
        void* raw = Alloc6(0x20, "Graphics", 0, 0, 0, 0);
        o1 = raw ? Ctor760c00(raw, 0) : 0;
    }
    if (o1)
        ((FnP0)(*(void***)o1)[0])(o1);
    void* o2;
    {
        void* raw = Alloc6(0x20, "Graphics", 0, 0, 0, 0);
        o2 = raw ? Ctor760c00(raw, 0) : 0;
    }
    if (o2)
        ((FnP0)(*(void***)o2)[0])(o2);
    void* o3;
    {
        void* raw = Alloc6(0x20, "Graphics", 0, 0, 0, 0);
        o3 = raw ? Ctor760c00(raw, 0) : 0;
    }
    if (o3)
        ((FnP0)(*(void***)o3)[0])(o3);

    {
        void* app = App();
        void* src = ((FnP0)(*(void***)app)[0x50 / 4])(app);
        src = ((FnP0)(*(void***)src)[0x1c / 4])(src);
        CopyFrom76b8(mSnapshotViewer, 0, src);
    }
    *(char*)((char*)mSnapshotViewer + 0x16c) = 1;
    FUN_7c4b50(mSnapshotViewer, 0, scale);
    Color4 color = { 0.0f, 0.0f, 0.0f, 0.0f };
    SetClearColor76c3(mSnapshotViewer, 0, &color);

    int count = ((FnI0)(*(void***)mgr)[0x68 / 4])(mgr);
    int threshold = flags ? 0x20 : 0x1a;
    for (int i = 0; i < count; ++i) {
        int* item = (int*)((FnItem)(*(void***)mgr)[0x70 / 4])(mgr, i);
        int type = item[1];
        if (type == 1)
            continue;
        if (type < 8)
            FUN_00760fd0(o1, 0, item[0], type, item[2]);
        else if (type == 8)
            FUN_00760fd0(o2, 0, item[0], 8, item[2]);
        else if ((unsigned)type <= (unsigned)threshold)
            FUN_00760fd0(o3, 0, item[0], type, item[2]);
    }

    int scaled = (int)_mm_cvtss_si32(_mm_set_ss((float)(unsigned)res * invScale));
    Ctor76b460(mTempSnapZRaster, 0, &rect, o1, o2, o3, res, scaled,
               (int)(size_t)view, cube, tiled, tiles, res80);

    // Completion job object posted with the message below.
    void* job = 0;
    {
        void* raw = Alloc6(0x18, "Graphics", 0, 0, 0, 0);
        if (raw) {
            DriveObj* j = (DriveObj*)raw;
            j->mField10 = 0;
            j->mVtbl = (void*)0x13eb90c;
            j->mRefCount = 0;
            j->mVtbl = (void*)0x1452a38;
            job = raw;
        }
    }
    if (job)
        ((FnP0)(*(void***)job)[1])(job);
    ((DriveObj*)job)->mField08 = (int)(unsigned char)p7;

    SnapshotMsg msg;
    msg.mField00 = 1;
    msg.mField04 = 0;
    msg.mField08 = 0;
    msg.mField0C = 0;
    msg.mField10 = 0;
    msg.mMsgID = 0x1c91267;
    msg.mJob = job;
    msg.mViewer = mSnapshotViewer;
    msg.mField20 = 0;
    msg.mField24 = 0;
    msg.mField28 = 0;
    ((FnSend)(*(void***)mgr)[0x78 / 4])(mgr, mTempSnapZRaster, 0, &msg);
    ((FnP1)(*(void***)mGraphicsSystem)[0x48 / 4])(mGraphicsSystem, 1);

    if (job)
        ((FnP0)(*(void***)job)[2])(job);
    if (o3)
        ((FnP0)(*(void***)o3)[1])(o3);
    if (o2)
        ((FnP0)(*(void***)o2)[1])(o2);
    if (o1)
        ((FnP0)(*(void***)o1)[1])(o1);
    return true;
}

// @ 0x0076c210
bool cRTTCapture::HandleCaptureMessage(void* payload)
{
    void* appCheck = App6740();
    if ((unsigned char)((FnI0)(*(void***)appCheck)[0x3c / 4])(appCheck)) {
        void* ms = MessageServer();
        ((FnI3)(*(void***)ms)[0x14 / 4])(ms, (int)payload, 0, 0);
        return false;
    }

    // One-shot capture raster (0x140-byte D350 object).
    void* raster;
    {
        void* raw = Alloc6(0x140, "Graphics", 0, 0, 0, 0);
        raster = raw ? Ctor76b350(raw, 0) : 0;
    }
    if (raster)
        ((FnP0)(*(void***)raster)[0])(raster);

    cRenderTargetRectID rect;
    rect.mPageID = -1;
    rect.mAllocID = -1;

    void* gfx = mGraphicsSystem;
    ((FnP0)(*(void***)gfx)[0x88 / 4])(gfx);
    ((FnPp)(*(void***)gfx)[0xcc / 4])(gfx, &rect);

    void* mgr = App6750();

    // Completion job object (vtable + refcount set up inline).
    DriveObj* job = (DriveObj*)Alloc6(0x20, "Graphics", 0, 0, 0, 0);
    if (job) {
        job->mField18 = 0;
        job->mVtbl = (void*)0x13eb90c;
        job->mRefCount = 0;
        job->mVtbl = (void*)0x1452a38;
    }
    if (job)
        ((FnP0)(*(void***)job)[1])(job);
    job->mField08 = (int)payload;

    // Three helper objects dispatched by scene-view item type.
    void* oA;
    {
        void* raw = Alloc6(0x20, "Graphics", 0, 0, 0, 0);
        oA = raw ? Ctor760c00(raw, 0) : 0;
    }
    if (oA)
        ((FnP0)(*(void***)oA)[0])(oA);
    void* oB;
    {
        void* raw = Alloc6(0x20, "Graphics", 0, 0, 0, 0);
        oB = raw ? Ctor760c00(raw, 0) : 0;
    }
    if (oB)
        ((FnP0)(*(void***)oB)[0])(oB);
    void* oC;
    {
        void* raw = Alloc6(0x20, "Graphics", 0, 0, 0, 0);
        oC = raw ? Ctor760c00(raw, 0) : 0;
    }
    if (oC)
        ((FnP0)(*(void***)oC)[0])(oC);

    {
        void* app = App();
        void* src = ((FnP0)(*(void***)app)[0x50 / 4])(app);
        src = ((FnP0)(*(void***)src)[0x1c / 4])(src);
        CopyFrom76b8(mSnapshotViewer, 0, src);
    }
    Color4 color = { 0.0f, 0.0f, 0.0f, 0.0f };
    SetClearColor76c3(mSnapshotViewer, 0, &color);

    int count = ((FnI0)(*(void***)mgr)[0x68 / 4])(mgr);
    for (int i = 0; i < count; ++i) {
        int* item = (int*)((FnItem)(*(void***)mgr)[0x70 / 4])(mgr, i);
        int type = item[1];
        if (type < 8)
            FUN_00760fd0(oA, 0, item[0], type, item[2]);
        else if (type == 8)
            FUN_00760fd0(oB, 0, item[0], 8, item[2]);
        else if ((unsigned)type <= 0x1a)
            FUN_00760fd0(oC, 0, item[0], type, item[2]);
    }

    Ctor76b460(raster, 0, &rect, oA, oB, oC, 0, 0, 0, 0, 0, 2, 0);
    job->mField10 = (int)raster;

    SnapshotMsg msg;
    msg.mField00 = 1;
    msg.mField04 = 0;
    msg.mField08 = 0;
    msg.mField0C = 0;
    msg.mField10 = 0;
    msg.mMsgID = 0x3ea7e1b;
    msg.mJob = job;
    msg.mViewer = mSnapshotViewer;
    msg.mField20 = 0;
    msg.mField24 = 0;
    msg.mField28 = 0;
    ((FnSend)(*(void***)mgr)[0x78 / 4])(mgr, raster, 0, &msg);
    ((FnP1)(*(void***)mGraphicsSystem)[0x48 / 4])(mGraphicsSystem, 1);

    if (oC)
        ((FnP0)(*(void***)oC)[1])(oC);
    if (oB)
        ((FnP0)(*(void***)oB)[1])(oB);
    if (oA)
        ((FnP0)(*(void***)oA)[1])(oA);
    if (job)
        ((FnP0)(*(void***)job)[2])(job);
    if (raster)
        ((FnP0)(*(void***)raster)[1])(raster);
    return true;
}

// @ 0x0076cc00
void E28Vec::insert(E28_s0076_cc00* position, const E28_s0076_cc00* value)
{
    if (mEnd != mCap) {
        E28_s0076_cc00* last = mEnd;
        if (value >= position && value < mEnd)
            value = value + 1;
        if (last)
            ((AssignThunk*)last)->FUN_0076b1f0(last - 1);
        while (last != position) {
            --last;
            *last = last[-1];
        }
        *position = *value;
        mEnd += 1;
        return;
    }
    uint32_t count = (uint32_t)(mEnd - mBegin);
    uint32_t newCap = count;
    if (count)
        newCap = count * 2;
    else
        newCap = 1;
    E28_s0076_cc00* newData = 0;
    if (newCap)
        newData = (E28_s0076_cc00*)EASTL_allocator_allocate(newCap * sizeof(E28_s0076_cc00), "Graphics", 0, 0,
                                                 kAllocatorFile, 0xd1);
    E28_s0076_cc00* newEnd = FUN_0076b9a0(mBegin, position, newData);
    if (newEnd)
        ((AssignThunk*)newEnd)->FUN_0076b1f0(value);
    E28_s0076_cc00* after = FUN_0076b9a0(position, mEnd, newEnd + 1);
    if (mBegin && *(int*)((char*)mBegin - 4) != 0)
        EASTL_allocator_deallocate(mBegin);
    mBegin = newData;
    mEnd = after;
    mCap = newData + newCap;
}

// @ 0x0076cd30
void SnapshotWrap::Update(int unused)
{
    (void)unused;
    if (mField80) {
        ContinueThunk* jobMgr = ((CaptureHost*)mField80)->mJob;
        if (jobMgr) {
            int state = jobMgr->FUN_0068f970();
            if ((unsigned)(state - 7) <= 1) {
                ((Slot48Obj*)mField70)->Slot48(0);
                ((ResetThunk*)mField80)->FUN_0076b5d0();
                if (mField80) {
                    ReleaseObj* old = (ReleaseObj*)mField80;
                    mField80 = 0;
                    old->Release();
                }
                MsgServer* ms = MessageServer_s0076_cc00();
                if (mField84 && ms)
                    ms->Post((uint32_t)(size_t)mField84, 0, 0);
                mField84 = 0;
            }
        }
    }
    if (mJobs.mBegin != mJobs.mEnd && mField68 == 0) {
        E28_s0076_cc00 job;
        ((AssignThunk*)&job)->FUN_0076b1f0(mJobs.mBegin);
        mField68 = 1;
        CaptureSceneViews(job.a0, (cFaceCamera**)((char*)this + 0x2c),
                          job.f8, job.fc, job.f10, job.f14,
                          *(unsigned short*)&job.a4, (char)job.b19,
                          job.i1c, job.i20, job.i24);
        ((EraseThunk*)&mJobs)->FUN_0076cbb0(mJobs.mBegin);
    }
}

// @ 0x0076ce50
void TileCapture::Capture(int a1, int a2, CapViewer** pViewer, uint32_t a4)
{
    CapTarget* t0 = mTarget0;
    if (t0 == 0)
        return;
    mViewer->Copy(*pViewer, 1, 0);
    RefBaseA22* rawMsg = new("App", 0, 0, 0, 0) DrvBA22();
    ARef<RefBaseA22> msg(rawMsg);
    rawMsg->mField8 = (int)*pViewer;
    if (mSized) {
        uint32_t q[2] = { 0xffffffff, 0xffffffff };
        GetDevInfo()->GetPair(q);
        int u0, v0, wid, hei;
        GetRasterMgr()->GetInfo(q[0], q[1], &u0, &v0, &wid, &hei);
        PixFormat* fmt = GetRasterMgr()->GetFormat(q[0], q[1]);
        uint32_t total = (fmt->mBits >> 3) * wid * hei;
        mH = mTiles * hei;
        mW = mTiles * wid;
        uint8_t* big = new("Graphics", 0, 0, 0, 0) uint8_t[mTiles * mTiles * total];
        uint8_t* tile = new("Graphics", 0, 0, 0, 0) uint8_t[total];
        for (uint32_t j = 0; j < mTiles; j++) {
            for (uint32_t i = 0; i < mTiles; i++) {
                q[0] = 0xffffffff;
                q[1] = 0xffffffff;
                GetDevInfo()->GetPair(q);
                int u1, v1, wid1, hei1;
                GetRasterMgr()->GetInfo(q[0], q[1], &u1, &v1, &wid1, &hei1);
                mViewer->SetRaster(q, 1);
                float fw, fh;
                mViewer->GetSize(&fw, &fh);
                fw = fw * g_two;
                fh = fh * g_two;
                mViewer->SetOffset(-((fw * (float)j) / (float)(mTiles * wid1)),
                                   (fh * (float)i) / (float)(mTiles * hei1));
                mViewer->FUN_007c3c50(7);
                RENDER_PASS()
                if (mDirect) {
                    uint32_t pr[2] = { 0xffffffff, 0xffffffff };
                    RasterMgr* rm = GetRasterMgr();
                    uint32_t tmp[2];
                    uint32_t* r = rm->Create(tmp, 0x80, 0x80, 0x15, 0, -1, 0);
                    pr[0] = r[0];
                    pr[1] = r[1];
                    rm->SetName(r[0], r[1], "ScreenshotThumbnailRTT");
                    GetReadMgr()->Fill(q, pr, a4, 0.0f);
                    rm->GetInfo(pr[0], pr[1], &u0, &v0, &wid, &hei);
                    mH = mTiles * hei;
                    mW = mTiles * wid;
                    rm->Read(pr[0], pr[1], tile);
                    rm->Release(pr[0], pr[1]);
                } else {
                    GetRasterMgr()->Read(q[0], q[1], tile);
                }
                int dst = (mW * i + j) * 4;
                int src = 0;
                for (int y = 0; y < hei; y++) {
                    for (int x = 0; x < wid; x++) {
                        big[dst] = tile[src];
                        big[dst + 1] = tile[src + 1];
                        big[dst + 2] = tile[src + 2];
                        big[dst + 3] = tile[src + 3];
                        dst += mTiles * 4;
                        src += 4;
                    }
                    dst += (mTiles - 1) * mW * 4;
                }
            }
        }
        if (mPath[0] != 0) {
            EStr str;
            str.sprintf("%s.png", mPath);
            Daf_s0076_cc00* rawDaf = new("Graphics", 0, 0, 0, 0) Daf_s0076_cc00();
            ARef<Daf_s0076_cc00> daf(rawDaf);
            {
                char* s = str.b;
                char* d = rawDaf->mName;
                char c;
                do {
                    c = *s++;
                    *d++ = c;
                } while (c);
            }
            rawDaf->mFormat = fmt;
            rawDaf->mW = mW;
            rawDaf->mH = mH;
            rawDaf->mPixels = big;
            rawDaf->mFlag = 0;
            JobSvc* svc = GetJobSvc();
            if (mJob) {
                JobObj* old = mJob;
                mJob = 0;
                ((JobRelease_s0076_cc00*)old)->Release();
            }
            svc->Create(&mJob);
            mJob->mFn = FUN_0075d870;
            mJob->mF4 = 0;
            mJob->mF18 = 4;
            mJob->FUN_0068f9b0(rawDaf);
            mJob->FUN_006909b0();
        } else {
            operator delete(big);
        }
        operator delete(tile);
    } else {
        mViewer->SetRaster(mRaster, 1);
        mViewer->FUN_007c3c50(7);
        RENDER_PASS()
    }
}

// @ 0x0076d5c0
void SnapshotWrap::push_back(int a0, int a1, float a2, float a3, float a4, float a5, int a6, char a7, char a8, int a9, int a10)
{
    cSPTransform_s0076_cc00 xf;
    if (a7) {
        xf.mFlags = 0;
        xf.mModificationCount = 0;
        xf.mTranslation.x = g_01630698;
        xf.mTranslation.y = g_0163069c;
        xf.mTranslation.z = g_016306a0;
        xf.mScale = 1.0f;
        ((Matrix33_s0076_cc00*)xf.mRotation)->FUN_0041cb40(&g_016307d8);
        AppCtx50* ctx = FUN_0067dd10()->GetCtx50();
        ((RecordThunk*)ctx->GetTransform())->FUN_007c40f0((unsigned short*)&xf);
    }
    E28_s0076_cc00& e = *(E28_s0076_cc00*)&xf;
    mField50 = a1;
    e.a0 = a0;
    e.a4 = a1;
    e.f8 = a2;
    e.fc = a3;
    e.f10 = a4;
    e.f14 = a5;
    e.b18 = a7;
    e.b19 = a8;
    e.i1c = a9;
    e.i20 = a10;
    e.i24 = a6;
    if (mJobs.mEnd < mJobs.mCap) {
        E28_s0076_cc00* p = mJobs.mEnd;
        mJobs.mEnd = p + 1;
        if (p)
            ((AssignThunk*)p)->FUN_0076b1f0(&e);
    } else {
        mJobs.insert(mJobs.mEnd, &e);
    }
}

// @ 0x0076d6e0
void SnapshotWrap::PushThreeJobs(int a0, int a1, int a2, int a3, float a4, float a5, float a6, float a7, int a8, char a9, char a10, int a11, int a12, int a13)
{
    push_back(a0, a3, a4, a5, a6, a7, 0,  a9, a10, a11, 5);
    push_back(a1, a3, a4, a5, a6, a7, 0,  a9, a10, a12, 7);
    push_back(a2, a3, a4, a5, a6, a7, a8, a9, a10, a13, 6);
}

// @ 0x0076d7d0
void RectThing::SetSize(uint16_t a, uint16_t b, uint16_t c, uint16_t d)
{
    mW0 = a;
    mH0 = b;
    mW1 = c;
    mH1 = d;
    mFrac = 0.0f;
    mScale = 1.0f;
}
