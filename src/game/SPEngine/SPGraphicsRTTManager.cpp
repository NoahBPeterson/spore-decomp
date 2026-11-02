// src/game/SPEngine/SPGraphicsRTTManager.cpp -- migrated from slice(s) s0076ed30, s0076db40, s0076cc00 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsRTTManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cViewer.h"
#include <xmmintrin.h>
#include "rw/graphics/Raster.h"
#include "rw/core/arena/Arena.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void   EASTL_allocator_deallocate(void* p);   // 0x00f47380

// ---- items of slice s0076cc00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchange(long volatile* p, long v);
#pragma intrinsic(_InterlockedExchange)
#define CAT2_(a, b) a##b
#define CAT_(a, b) CAT2_(a, b)
#define PV virtual void CAT_(_pv, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
struct E28 {
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
struct E28Vec {
    E28* mBegin;   // +0
    E28* mEnd;     // +4
    E28* mCap;     // +8

    void insert(E28* position, const E28* value);   // @ 0x0076cc00
};
struct RTTResolver;
RTTResolver* __cdecl GetRTTResolver();                  // 0x0067dd60
struct SysObj {
    SysObj();                     // 0x007c3f70
    void Begin(void* p, int n);   // 0x007c4be0
    void End(int n);              // 0x007c3c50
    char pad[0x174];
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
struct JobItem { uint32_t m0; uint8_t mFlags; };
struct Rec3c_s0076_cc00 { char pad[0x38]; JobItem* mItem; };
struct PrepOwner {
    PV8 PV
    virtual void Prepare(int idx, void* a, unsigned short* o0, unsigned short* o1,
                         unsigned short* o2, unsigned short* o3);   // +0x24
};
struct ResolveMgr {
    PV8 PV4 PV
    virtual void Resolve(JobItem* item);                            // +0x34
};
struct PageInfo {
    char    pad00[0x34];
    int32_t mRefCount;   // +0x34
    int32_t mPad38;      // +0x38
    void    Release(void* arg);   // 0x007b0e60
};
struct PageVec {
    PageInfo* mBegin;   // +0x00
    PageInfo* mEnd;     // +0x04
    PageInfo* mCap;     // +0x08
};
struct cRTTManager {
    char      pad00[0x10];
    bool      mInitialized;       // +0x10
    int32_t   mDefaultResolution; // +0x14
    PageVec   mTexturePages;      // +0x18

    // @ 0x0076d9e0  release one page allocation; true when a page was released.
    bool ReleasePage(int index, void* arg);
};
struct PageRecord_s0076_cc00 {
    int32_t mData[7];   // +0x00
    uint8_t mFlag;      // +0x1c
    PageRecord_s0076_cc00(const PageRecord_s0076_cc00& o);
};
struct OwnedSub {
    void Destroy();    // 0x007c3ba0
    void Cleanup();    // 0x007c4000
};
struct Holder {
    char      pad00[0xc];
    OwnedSub* mSub;   // +0x0c
};
// ---- items of slice s0076cc00 end

// ---- items of slice s0076db40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* EASTL_allocator_allocate(uint32_t n, const char* name, int a, int b, const char* f, int line); // 0x00f473a0
extern "C" long _InterlockedExchangeAdd(volatile long* Addend, long Value);
extern "C" long _InterlockedIncrement(volatile long* Addend);
extern "C" const float g_kBytesToMB;           // 0x0140e4b0 = 9.536743e-07f
#pragma intrinsic(_InterlockedExchangeAdd)
#pragma intrinsic(_InterlockedIncrement)
inline void* operator new(unsigned int, void* p) { return p; }
struct PageRecord {
    int a[7];             // +0x00
    unsigned char b;      // +0x1c
    PageRecord& operator=(const PageRecord& o);
};
PageRecord& PageRecord::operator=(const PageRecord& o)
{
    a[0] = o.a[0]; a[1] = o.a[1]; a[2] = o.a[2]; a[3] = o.a[3];
    a[4] = o.a[4]; a[5] = o.a[5]; a[6] = o.a[6]; b = o.b;
    return *this;
}
struct PageInfo_s0076_db40 {
    void* mData;      // +0x00
    char  pad04[0x24];
    int   mC;         // +0x28
    int   mA;         // +0x2c
    int   mB;         // +0x30
    int   mRefCount;  // +0x34
    void* mTexture;   // +0x38
};
struct PageVec_s0076_db40 { PageInfo_s0076_db40* mBegin; PageInfo_s0076_db40* mEnd; PageInfo_s0076_db40* mCap; };
struct cRTTManager_s0076_db40 {
    char    pad[0x18];
    PageVec_s0076_db40 mTexturePages;   // +0x18

    // @ 0x0076db40  lazily resolve the raster from a page's texture instance.
    void* GetTextureHandle(int i, int);  // 0x0076db40 (cRTTManager::GetTextureHandle)
    // @ 0x0076dbb0  page texture pointer.
    void* GetTexture(int i, int reserved);  // 0x0076dbb0 (cRTTManager::GetTexture)
    // @ 0x0076dc00  copy a 4-dword rect for sub-page `sub` into out.
    bool  GetRect(int i, int sub, int* out);  // 0x0076dc00 (cRTTManager::GetRect)
    // @ 0x0076dc70  copy the rect and its (w,h) deltas.
    bool  GetRectSizes(int i, int sub, int* a, int* b, int* c, int* d);  // 0x0076dc70 (cRTTManager::GetRectSizes)
    // @ 0x0076dcf0  copy mA/mB.
    bool  GetAB(int i, int reserved, int* a, int* b);  // 0x0076dcf0 (cRTTManager::GetAB)
    // @ 0x0076dd60  fill the page raster and a sprite texture.
    bool  FillSprite(int i, int a, int b);
    // @ 0x0076ddb0  find a page by (mA,mB,refcount == criteria); returns index.
    bool  FindPage(int a, int b, int c, int* out);
    // @ 0x0076e040  per-page rectangle scale (1/pageSize) in float.
    bool  GetScaledRect(int i, int sub, float* a, float* b);  // 0x0076e040 (cRTTManager::GetScaledRect)
    // @ 0x0076e110  allocate a new texture page.
    bool  AllocateNewPage(int pageId, int w, int h, int depth);  // 0x0076e110 (cRTTManager::AllocateNewPage)
};
struct RTTRaster {
    unsigned D3D9GetMipLevelSize(unsigned char level);          // 0x011f0000, ret 4
    void FillSpriteTexture(int a, unsigned size, int z);        // 0x011f0440, ret 0xc
};
struct RTTTexRef;
struct IRTTResolver {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
    virtual void s12();
    virtual void Resolve(RTTTexRef* t);                         // +0x34
};
struct RTTTexRef {
    RTTRaster* mRaster;     // +0
    unsigned   mFlags;      // +4, bit 0 = raster resolved
};
IRTTResolver* GetRTTResolver_s0076_db40();                                 // 0x0067dd60 (cdecl)
void* FUN_0067dd50();                 // 0x0067dd50
void* SP_IDGenerator();               // 0x0067de60
void  FUN_0076d8e0(void* arg);        // 0x0076d8e0
void  GetImageResource();             // 0x00576650
void  FUN_007b0fa0();                 // 0x007b0fa0
struct SpVec { char* mBegin; char* mEnd; char* mCap; void DeallocateSelf(); };
struct VecElem { int pad0; SpVec v; int pad2[4]; };
void __stdcall FreeElemArray(VecElem* first, VecElem* last);
struct Rec3c {
    char  pad00[0x38];
    void* mTexture;   // +0x38
    void  DestroyOne();
};
struct SomeObj3 {
    char pad[0x18];
    Rec3c* mBegin;    // +0x18
    Rec3c* mEnd;      // +0x1c
    void Destroy();
};
struct PageRecVec {                       // +0x00 (vector<PageRecord>)
    char pad00[0x14];
    void Assign(const PageRecVec& src);                        // 0x0076e4b0 (thiscall, src pushed)
};
struct FloatVec {                         // +0x14 (vector<float,sp_vector_allocator>)
    char pad00[0x14];
    void Assign(const FloatVec& src);                          // 0x0050d4e0 (thiscall, src pushed)
};
struct BigRecBase {
    PageRecVec mPages;    // +0x00
    FloatVec   mFloats;   // +0x14
    BigRecBase(const BigRecBase& src);                         // 0x0076e670 (thiscall, src pushed)
    __forceinline BigRecBase& operator=(const BigRecBase& o)
    {
        mPages.Assign(o.mPages);
        mFloats.Assign(o.mFloats);
        return *this;
    }
};
struct BigRef {                            // +0x38 refcounted texture handle (AutoRef)
    void* p;
    __forceinline BigRef(const BigRef& o) : p(o.p)
    {
        if (p)
            _InterlockedIncrement((volatile long*)((char*)p + 8));
    }
    __forceinline ~BigRef()
    {
        if (p) {
            volatile long* rc = (volatile long*)((char*)p + 8);
            _InterlockedExchangeAdd(rc, -1);
            if (_InterlockedExchangeAdd(rc, 0) < 1)
                _InterlockedIncrement(rc);
            else
                _InterlockedExchangeAdd(rc, 0);
        }
    }
    __forceinline BigRef& operator=(const BigRef& o)
    {
        void* nv = o.p;
        void* ov = p;
        if (nv != ov) {
            if (nv)
                _InterlockedIncrement((volatile long*)((char*)nv + 8));
            p = nv;
            if (ov) {
                volatile long* rc = (volatile long*)((char*)ov + 8);
                _InterlockedExchangeAdd(rc, -1);
                if (_InterlockedExchangeAdd(rc, 0) < 1)
                    _InterlockedIncrement(rc);
                else
                    _InterlockedExchangeAdd(rc, 0);
            }
        }
        return *this;
    }
};
struct BigRec : BigRecBase {              // implicit copy ctor / operator=
    int   f28;            // +0x28
    int   f2c;            // +0x2c
    int   f30;            // +0x30
    int   f34;            // +0x34
    BigRef mRef;          // +0x38

    __forceinline BigRec(const BigRec& o)
        : BigRecBase(o), f28(o.f28), f2c(o.f2c), f30(o.f30), f34(o.f34), mRef(o.mRef) {}
    __forceinline BigRec& operator=(const BigRec& o)
    {
        BigRecBase::operator=(o);
        f28 = o.f28;
        f2c = o.f2c;
        f30 = o.f30;
        f34 = o.f34;
        mRef = o.mRef;
        return *this;
    }
};
struct Obj2c {
    void* vt0;          // +0x00
    void* vt4;          // +0x04
    void* vt8;          // +0x08
    int   mRefCount;    // +0x0c
    char  mFlag;        // +0x10
    int   mSize;        // +0x14
    int   f18, f1c, f20;
};
struct Vec20 { void Construct(int count, void* tag); };   // 0x0076e200 (thiscall)
struct VecF  { void Construct(int count, void* tag); };   // 0x004aa350 (thiscall)
void* eastl_DoInsertValue_11e0744(void*, void*, int);     // 0x011e0744 (cdecl)
struct BigRecOps {
    void* Construct(void* src);
    int   CopyFrom(BigRecOps* src);
};
struct BigRec2 {
    char pad00[0x38];
};
struct CObj18 { void* vt; void* f4; int f8, fc, f10, f14; };
struct CaptureJobMsg {
    int f00, f04;
    char f08;
    int f0c, f10, f14;
    void* f18;
    int f1c, f20, f24, f28;
};
struct cRTTCheat {
    void* Construct(int owner);
    void  Execute(void* args);
};
namespace EA {
namespace ArgScript {
struct cArguments_s0076_db40;
}
}
namespace EA {
namespace ArgScript {
struct cIParser_s0076_db40;
}
}
namespace EA {
namespace ArgScript {
struct cCommandBase_s0076_db40 {
    void* vtbl;       // +0x00
    void* mParser;    // +0x04
    int   mRefCount;  // +0x08
    cCommandBase_s0076_db40();
};
}
}
namespace EA {
namespace ArgScript {
struct cArgumentSpec_s0076_db40 {
    cArgumentSpec_s0076_db40(bool respectHelp);
    void Parse(cArguments_s0076_db40* args, cIParser_s0076_db40* parser);            // 0x0083b9d0
    int  ConstructSpec(const char* name, const char* spec, ...);   // 0x0083bcd0
};
}
}
namespace EA {
namespace ArgScript {
void Output(cIParser_s0076_db40* parser, const char* fmt, ...);  // namespace EA::ArgScript
}
}
struct FlagHolder {
    unsigned char IsSet() const;
};
int __cdecl RasterFormatSize(int width, int height, int format);
namespace rw {
namespace graphics {
struct Raster_s0076_db40 {
    int            m_format;    // +0x00
    char           pad04[8];
    uint16_t       m_width;     // +0x0c
    uint16_t       m_height;    // +0x0e
    uint32_t D3D9GetMipLevelSize(unsigned char level);   // 0x011f0000, thiscall ret 4
};  // namespace rw::graphics
}
}
struct RTTPageRec {
    char     pad00[0x28];
    uint16_t mType;      // +0x28
    uint16_t mWidth;     // +0x2c
    uint16_t mHeight;    // +0x30
    uint16_t mAllocs;    // +0x34
    char     pad36[6];
};
struct RTTPageHolder {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
    virtual void Release();                              // +0x3c
    RTTPageRec* mBegin;   // +0x18
    RTTPageRec* mEnd;     // +0x1c
};
struct cRTTCheatLayout {
    char                         pad00[4];
    EA::ArgScript::cIParser_s0076_db40*     mParser;     // +0x04
    char                         pad08[8];
    EA::ArgScript::cArgumentSpec_s0076_db40 mSpec;       // +0x10
    char                         pad14[0x6c];
    unsigned                     mFlags;      // +0x80, bit0 = list pages, bit1 = release
    char                         pad84[0x54];
    RTTPageHolder*               mPages;      // +0xd8
};
rw::graphics::Raster_s0076_db40* g_defaultCameraRaster;   // 0x015d0838
rw::graphics::Raster_s0076_db40* g_defaultZBufferRaster;  // 0x015d083c
// ---- items of slice s0076db40 end

// ---- items of slice s0076ed30 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct __declspec(align(16)) Elem30 {
    __m128 v;        // +0x00
    float  f[6];     // +0x10
    Elem30& operator=(const Elem30& o);
};
Elem30& Elem30::operator=(const Elem30& o)
{
    v = o.v;
    for (int i = 0; i < 6; ++i) f[i] = o.f[i];
    return *this;
}
struct PageInfo_s0076_ed30 { char pad[0x3c]; };
PageInfo_s0076_ed30* MoveRange76(PageInfo_s0076_ed30* first, PageInfo_s0076_ed30* last, PageInfo_s0076_ed30* out);   // cdecl (0x76e900)
struct PageVec_s0076_ed30 {
    PageInfo_s0076_ed30* mBegin;
    PageInfo_s0076_ed30* mEnd;
    PageInfo_s0076_ed30* mCap;
    void destroyRange(PageInfo_s0076_ed30* first, PageInfo_s0076_ed30* last);   // thiscall (0x76e3b0)
    PageInfo_s0076_ed30* erase(PageInfo_s0076_ed30* first, PageInfo_s0076_ed30* last);     // @ 0x0076ed90
    void AppendPage(void* rec);                           // thiscall (0x76efd0)
};
struct cRTTManager_s0076_ed30 {
    char      pad[4];
    char      mField04[0xc];  // +0x04
    bool      mInitialized;   // +0x10
    char      pad11[7];
    PageVec_s0076_ed30   mTexturePages;  // +0x18
    bool Shutdown();          // 0x0076f210
    bool AllocateNewPage(int a, int b, int c, int d, void* rec);   // thiscall (0x76e110)
    bool FindPage(int a, int b, int c, int* out);                  // thiscall (0x76ddb0)
    void CaptureJob(int* out);                                     // thiscall (0x76dee0)
    bool RTTCheatInit();      // 0x0076f050
    void RTTBigJob(int* out, int a3, int a4, int a5, uint32_t flags, int a7, int a8); // 0x0076f280
};
struct Cheat {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual void RemoveProperty(const char* name);   // slot 7 (+0x1c)
};
struct MsgSrv {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
    virtual void Send(void* base, int id, int val);  // slot 0xb (+0x2c)
};
extern "C" Cheat* CheatManager();
extern "C" MsgSrv* MessageServer();
namespace EA {
namespace ArgScript {
class cArgumentSpec_s0076_ed30 { public:
    char pad[0x10];
    virtual ~cArgumentSpec_s0076_ed30();
};
}
}
namespace EA {
namespace ArgScript {
class cCommandBase_s0076_ed30 { public:
    char pad[0xc];
    virtual ~cCommandBase_s0076_ed30();
};
}
}
struct cRTTCheat_s0076_ed30 : EA::ArgScript::cCommandBase_s0076_ed30 {
    uint32_t pad04[3];                      // +0x04
    EA::ArgScript::cArgumentSpec_s0076_ed30 mParser;   // +0x10
    virtual ~cRTTCheat_s0076_ed30() {}
};
struct FloatVecRef  { void operator=(const void* o); };          // 0x0050d4e0
struct ImageRef     { void GetImageResource(const void* o); };   // 0x00576650
struct BigRec3c {
    void  CopyFrom(BigRec3c* src);        // 0x0076e750  thiscall(1)
    void  Assign(const BigRec3c* src);    // 0x0076e4b0  thiscall(1)
    char  pad00[0x14];
    FloatVecRef vec;                      // +0x14
    char  pad18[0x10];
    int   f28, f2c, f30, f34;             // +0x28
    ImageRef ref;                         // +0x38
};
BigRec3c* __cdecl CopyBigRecRange(BigRec3c* first, BigRec3c* last, BigRec3c* out);     // 0x0076e840
BigRec3c* __cdecl CopyBigRecRangeBack(BigRec3c* first, BigRec3c* last, BigRec3c* out); // 0x0076e9b0
void*     __cdecl DestroyRecRange(BigRec3c* first, BigRec3c* last, BigRec3c* out);     // 0x0076e320
static const char* const kAllocH =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
struct BigVec { BigRec3c* mBegin; BigRec3c* mEnd; BigRec3c* mCap; void Insert(BigRec3c* position, BigRec3c* value); };
struct RTTRec3c {
    void* f00;                                   // +0x00
    int   f04, f08, f0c, f10;
    void* f14;                                   // +0x14
    int   f18, f1c, f20, f24, f28, f2c, f30, f34;
    void* f38;                                   // +0x38
    void Init();      // 0x007b00d0 thiscall(0)
    RTTRec3c() { Init(); }
    ~RTTRec3c();      // 0x0076e2c0 thiscall(0)
};
struct cRTTCheatObj { void Construct(cRTTManager_s0076_ed30* mgr); };  // 0x0076ea60 thiscall(1)
namespace SP {
class cDirectPropertyList_s0076_ed30 { public:
virtual bool v0();
virtual bool v1();
virtual bool v2();
virtual bool v3();
virtual bool v4();
virtual bool v5();
virtual bool v6();
    virtual bool HasProperty(uint32_t prop);      // slot 7 (+0x1c) 0x006a27d0
    int GetIntProperty(uint32_t prop) const;      // 0x006a2660
};
}
namespace SP {
extern cDirectPropertyList_s0076_ed30* sAppProperties;       // 0x015fd918
}
struct Dd50Obj { virtual void* v0(); virtual void* v1(); virtual void* v2();
virtual void* v3();
virtual void* v4();
virtual void* v5();
virtual void* v6();
                 virtual void* v7(); };
extern "C" Dd50Obj* Fn_67dd50();                        // 0x0067dd50
struct W1e70 { int f(void* a, void* b); };              // 0x007b1e70 thiscall(2)
// ---- items of slice s0076ed30 end

// @ 0x0076d820
int __cdecl RasterFormatSize(int width, int height, int format)
{
    int mult = 0;
    switch (format) {
    case 0x1a:
    case 0x6f:
        mult = 2;
        break;
    case 0x1c:
        mult = 1;
        break;
    case 0x15:
    case 0x16:
    case 0x70:
    case 0x72:
        mult = 4;
        break;
    }
    return mult * width * height;
}

// @ 0x0076d970
void SnapshotWrap::Teardown(int, int, int, int)
{
    if (mSystem != 0) {
        mSystem->Begin(&mFlags, 1);
        mSystem->End(7);
    }
}

// @ 0x0076d9a0
PageRecord_s0076_cc00::PageRecord_s0076_cc00(const PageRecord_s0076_cc00& o)
{
    for (int i = 0; i < 7; ++i) mData[i] = o.mData[i];
    mFlag = o.mFlag;
}

// @ 0x0076d9e0
bool cRTTManager::ReleasePage(int index, void* arg)
{
    if (index >= 0 && index < (int)(mTexturePages.mEnd - mTexturePages.mBegin)) {
        PageInfo* p = mTexturePages.mBegin + index;
        if (p->mRefCount > 0) {
            p->Release(arg);
            --p->mRefCount;
            return true;
        }
    }
    return false;
}

// @ 0x0076da50
void SnapshotWrap::Effects_PrepareRender(int idx, void* a, PrepOut* out, char flag)
{
    Rec3c_s0076_cc00* rec = (Rec3c_s0076_cc00*)((char*)mSceneArray + (size_t)idx * 0x3c);
    JobItem* item = rec->mItem;
    if ((item->mFlags & 1) == 0) {
        ResolveMgr* mgr = (ResolveMgr*)GetRTTResolver();
        mgr->Resolve(item);
    }
    out->m40 = item->m0;
    if (flag) {
        unsigned short q0, q1, q2, q3;
        ((PrepOwner*)this)->Prepare(idx, a, &q0, &q1, &q2, &q3);
        out->m78 = q0;
        out->m7c = q1;
        out->m80 = q2;
        out->m84 = q3;
        out->m88 = 0.0f;
        out->m8c = 1.0f;
    }
}

// @ 0x0076db00
bool __stdcall OnCaptureMessage(int msgId, void* payload)
{
    if (msgId == 0x3d037f1) {
        Holder* h = (Holder*)*(void**)((char*)payload + 8);
        OwnedSub* sub = h->mSub;
        if (sub != 0) {
            sub->Destroy();
            sub = h->mSub;
            if (sub != 0) {
                sub->Cleanup();
                EASTL_allocator_deallocate(sub);
            }
        }
        return true;
    }
    return false;
}

// @ 0x0076db40
void* cRTTManager_s0076_db40::GetTextureHandle(int i, int)
{
    if (i < 0 || i >= (int)(mTexturePages.mEnd - mTexturePages.mBegin)) return 0;
    PageInfo_s0076_db40* p = mTexturePages.mBegin + i;
    if (p->mRefCount <= 0) return 0;
    RTTTexRef* t = (RTTTexRef*)p->mTexture;
    if (!(t->mFlags & 1))
        GetRTTResolver_s0076_db40()->Resolve(t);
    return t->mRaster;
}

// @ 0x0076dbb0
void* cRTTManager_s0076_db40::GetTexture(int i, int)
{
    if (i < 0) return 0;
    if (i >= (int)(mTexturePages.mEnd - mTexturePages.mBegin)) return 0;
    if (mTexturePages.mBegin[i].mRefCount <= 0) return 0;
    return mTexturePages.mBegin[i].mTexture;
}

// @ 0x0076dc00
bool cRTTManager_s0076_db40::GetRect(int i, int sub, int* out)
{
    if (i < 0) return false;
    if (i >= (int)(mTexturePages.mEnd - mTexturePages.mBegin)) return false;
    if (mTexturePages.mBegin[i].mRefCount <= 0) return false;
    int* src = (int*)((char*)mTexturePages.mBegin[i].mData + sub * 0x20);
    out[0] = src[0]; out[1] = src[1]; out[2] = src[2]; out[3] = src[3];
    return true;
}

// @ 0x0076dc70
bool cRTTManager_s0076_db40::GetRectSizes(int i, int sub, int* a, int* b, int* c, int* d)
{
    if (i < 0) return false;
    if (i >= (int)(mTexturePages.mEnd - mTexturePages.mBegin)) return false;
    if (mTexturePages.mBegin[i].mRefCount <= 0) return false;
    int* src = (int*)((char*)mTexturePages.mBegin[i].mData + sub * 0x20);
    *a = src[0]; *b = src[1]; *c = src[2] - src[0]; *d = src[3] - src[1];
    return true;
}

// @ 0x0076dcf0
bool cRTTManager_s0076_db40::GetAB(int i, int, int* a, int* b)
{
    if (i < 0) return false;
    if (i >= (int)(mTexturePages.mEnd - mTexturePages.mBegin)) return false;
    if (mTexturePages.mBegin[i].mRefCount <= 0) return false;
    *a = mTexturePages.mBegin[i].mA;
    *b = mTexturePages.mBegin[i].mB;
    return true;
}

// @ 0x0076ddb0
bool cRTTManager_s0076_db40::FindPage(int a, int b, int c, int* out)
{
    unsigned count = (unsigned)((mTexturePages.mEnd - mTexturePages.mBegin));
    unsigned idx = 0;
    if (count != 0) {
        PageInfo_s0076_db40* p = mTexturePages.mBegin;
        do {
            if (p->mRefCount == 0 && p->mA == a && p->mB == b && p->mC == c) {
                *out = idx;
                return true;
            }
            ++idx;
            ++p;
        } while (idx < count);
    }
    return false;
}

// @ 0x0076de20
PageRecord* __cdecl UninitCopyPageRecords(PageRecord** out, PageRecord* first, PageRecord* last, PageRecord* dst)
{
    *out = dst;
    if (first != last) {
        do {
            if (dst) *dst = *first;
            ++first;
            ++dst;
        } while (first != last);
        *out = dst;
    }
    return (PageRecord*)out;
}

// @ 0x0076de80
PageRecord* __cdecl CopyPageRecords(PageRecord* first, PageRecord* last, PageRecord* out)
{
    for (; first != last; ++first, ++out)
        *out = *first;
    return out;
}

// @ 0x0076dee0
void __cdecl RegisterCaptureJob(void* arg)
{
    CObj18* a = (CObj18*)EASTL_allocator_allocate(0x18, "Graphics", 0, 0, 0, 0);
    if (a) {
        a->f4 = (void*)0x13ec458;
        a->f8 = 0;
        a->vt = (void*)0x140e360;
        a->f4 = (void*)0x149bad8;
        a->fc = 0;
        a->f10 = -1;
        a->f14 = -1;
    }
    if (a)
        ((void(__thiscall*)(void*))((void**)a)[0])(a);

    FUN_0076d8e0(arg);

    CObj18* b = (CObj18*)EASTL_allocator_allocate(0x18, "Graphics", 0, 0, 0, 0);
    if (b) {
        b->f10 = 0;
        b->vt = (void*)0x13eb90c;
        _InterlockedExchange((volatile long*)((char*)b + 4), 0);
        b->vt = (void*)0x1452a38;
    }
    if (b)
        ((void(__thiscall*)(void*))((void**)b)[1])(b);

    *(void**)((char*)b + 8) = a;

    CaptureJobMsg msg;
    msg.f00 = 1; msg.f04 = 0; msg.f08 = 0; msg.f0c = 0; msg.f10 = 0;
    msg.f14 = 0x3d037f1; msg.f18 = b; msg.f1c = 0; msg.f20 = 0; msg.f24 = 0; msg.f28 = 0;

    void* r = ((void*(__thiscall*)(void*, int, void*))((void**)a)[0x10 / 4])(a, 0, &msg);
    void* s = FUN_0067dd50();
    ((void(__thiscall*)(void*, void*))((void**)s)[0x78 / 4])(s, r);

    if (b)
        ((void(__thiscall*)(void*))((void**)b)[2])(b);
    ((void(__thiscall*)(void*))((void**)a)[1])(a);
}

// @ 0x0076e040
bool cRTTManager_s0076_db40::GetScaledRect(int i, int sub, float* a, float* b)
{
    if (i < 0) return false;
    if (i >= (int)(mTexturePages.mEnd - mTexturePages.mBegin)) return false;
    if (mTexturePages.mBegin[i].mRefCount <= 0) return false;
    PageInfo_s0076_db40* p = mTexturePages.mBegin + i;
    int* src = (int*)((char*)p->mData + sub * 0x20);
    float sx = 1.0f / (float)p->mA;
    float sy = 1.0f / (float)p->mB;
    a[0] = sx * (float)src[0];
    a[1] = sx * (float)src[1];
    b[0] = sy * (float)src[2];
    b[1] = sy * (float)src[3];
    return true;
}

// @ 0x0076e110
bool cRTTManager_s0076_db40::AllocateNewPage(int pageId, int w, int h, int depth)
{
    void* mgr = FUN_0067dd50();
    ((void(__thiscall*)(void*))((void**)mgr)[0x1c / 4])(mgr);

    void* resolver = GetRTTResolver_s0076_db40();
    int buf[3];
    buf[0] = pageId;
    buf[1] = 0;
    buf[2] = 0x40002a00;
    if (pageId == -1) {
        void* gen = SP_IDGenerator();
        ((void(__thiscall*)(void*, int*, int, int, int, int, int))((void**)gen)[1])
            (gen, buf, 0x2f4e681c, 0, 0, 0x2a, 0);
    }
    void* res = ((void*(__thiscall*)(void*, int, int, int, int, int, int, int, int))
                     ((void**)resolver)[0x3c / 4])
        (resolver, buf[0], buf[2], w, h, 1, 9, depth, 0);
    if (res != 0) {
        ((void(__thiscall*)(void*, void*))GetImageResource)((char*)this + 0x38, res);
        *(int*)((char*)this + 0x28) = depth;
        *(int*)((char*)this + 0x34) = 0;
        *(int*)((char*)this + 0x2c) = w;
        *(int*)((char*)this + 0x30) = h;
        ((void(__thiscall*)(void*, int, int))FUN_007b0fa0)(this, w, h);
        return true;
    }
    return false;
}

// @ 0x0076e1e0
void SpVec::DeallocateSelf()
{
    if ((mCap - mBegin) > 1 && mBegin)
        EASTL_allocator_deallocate(mBegin);
}

// @ 0x0076e2c0
void Rec3c::DestroyOne()
{
    if (mTexture) {
        // AutoRefCount release: atomic decrement at +8, restore when it would drop below 1.
        volatile long* rc = (volatile long*)((char*)mTexture + 8);
        _InterlockedExchangeAdd(rc, -1);
        if (_InterlockedExchangeAdd(rc, 0) < 1)
            _InterlockedIncrement(rc);
        else
            _InterlockedExchangeAdd(rc, 0);
    }
    void* p = *(void**)((char*)this + 0x14);
    if (p && *(int*)((char*)p - 4) != 0)
        EASTL_allocator_deallocate(p);
    p = *(void**)this;
    if (p && *(int*)((char*)p - 4) != 0)
        EASTL_allocator_deallocate(p);
}

// @ 0x0076e320
Rec3c* __cdecl DestroyRecRange(Rec3c* first, Rec3c* last, Rec3c* out)
{
    if (first == last) return out;
    do {
        first->DestroyOne();
        ++first;
        ++out;
    } while (first != last);
    return out;
}

// @ 0x0076e3b0
void __stdcall DestroyRecArray(Rec3c* first, Rec3c* last)
{
    for (; first < last; ++first)
        first->DestroyOne();
}

// @ 0x0076e430
void __stdcall FreeElemArray(VecElem* first, VecElem* last)
{
    for (; first < last; first += 1) {
        if ((first->v.mCap - first->v.mBegin) > 1 && first->v.mBegin)
            EASTL_allocator_deallocate(first->v.mBegin);
    }
}

// @ 0x0076e5c0
void SomeObj3::Destroy()
{
    *(void**)this = (void*)0x140e398;
    *(void**)((char*)this + 4) = (void*)0x140e384;
    *(void**)((char*)this + 8) = (void*)0x140e374;
    DestroyRecArray(mBegin, mEnd);
    if (mBegin && *(int*)((char*)mBegin - 4) != 0)
        EASTL_allocator_deallocate(mBegin);
    *(void**)((char*)this + 8) = (void*)0x13ec458;
    *(void**)((char*)this + 4) = (void*)0x13eb394;
}

// @ 0x0076e610
Obj2c* __cdecl CreateObj2c()
{
    volatile Obj2c* p = (volatile Obj2c*)EASTL_allocator_allocate(0x2c, "Graphics", 0, 0, 0, 0);
    if (p) {
        p->vt4 = (void*)0x13eb384;
        p->mRefCount = 0;
        p->vt8 = (void*)0x13ec458;
        p->mFlag = 0;
        p->vt0 = (void*)0x140e398;
        p->vt4 = (void*)0x140e384;
        p->vt8 = (void*)0x140e374;
        p->mSize = 0x200;
        p->f18 = 0;
        p->f1c = 0;
        p->f20 = 0;
        return (Obj2c*)p;
    }
    return 0;
}

// @ 0x0076e670
void* BigRecOps::Construct(void* src)
{
    char* s = (char*)src;
    char* t = (char*)this;
    ((Vec20*)t)->Construct((*(int*)(s + 4) - *(int*)s) >> 5, s + 0xc);
    PageRecord* out;
    ((void(__cdecl*)(PageRecord**, PageRecord*, PageRecord*, PageRecord*, PageRecord*))UninitCopyPageRecords)
        (&out, *(PageRecord**)s, *(PageRecord**)(s + 4), *(PageRecord**)t, (PageRecord*)s);
    *(void**)(t + 4) = out;
    ((VecF*)(t + 0x14))->Construct((*(int*)(s + 0x18) - *(int*)(s + 0x14)) >> 2, s + 0x20);
    int size = *(int*)(s + 0x18) - *(int*)(s + 0x14);
    void* p = eastl_DoInsertValue_11e0744(*(void**)(t + 0x14), *(void**)(s + 0x14), size);
    *(void**)(t + 0x18) = (char*)p + (size >> 2) * 4;
    return this;
}

// @ 0x0076e750
int BigRecOps::CopyFrom(BigRecOps* src)
{
    Construct(src);
    char* s = (char*)src;
    char* t = (char*)this;
    *(int*)(t + 0x28) = *(int*)(s + 0x28);
    *(int*)(t + 0x2c) = *(int*)(s + 0x2c);
    *(int*)(t + 0x30) = *(int*)(s + 0x30);
    *(int*)(t + 0x34) = *(int*)(s + 0x34);
    int r = *(int*)(s + 0x38);
    *(int*)(t + 0x38) = r;
    if (r != 0)
        _InterlockedIncrement((volatile long*)(r + 8));
    return (int)(size_t)this;
}

// @ 0x0076e7a0
void __stdcall DestroyBigRecArray(BigRec2* first, BigRec2* last)
{
    for (; first < last; ++first) {
        VecElem* e = *(VecElem**)((char*)first + 0x24);
        VecElem* b = *(VecElem**)((char*)first + 0x20);
        for (; b < e; b += 1) {
            if ((b->v.mCap - b->v.mBegin) > 1 && b->v.mBegin)
                EASTL_allocator_deallocate(b->v.mBegin);
        }
        void* p = *(void**)((char*)first + 0x20);
        if (p && *(int*)((char*)p - 4) != 0)
            EASTL_allocator_deallocate(p);
        SpVec* v = (SpVec*)((char*)first + 0x10);
        if ((v->mCap - v->mBegin) > 1 && v->mBegin)
            EASTL_allocator_deallocate(v->mBegin);
        v = (SpVec*)first;
        if ((v->mCap - v->mBegin) > 1 && v->mBegin)
            EASTL_allocator_deallocate(v->mBegin);
    }
}

// @ 0x0076e840
int __cdecl CopyBigRecRange(BigRec* first, BigRec* last, BigRec* out)
{
    for (; first != last; ++first, ++out) {
        if (out)
            ::new (out) BigRec(*first);
    }
    return (int)(size_t)out;
}

// @ 0x0076e900
void* __cdecl CopyBigRecRange2(void* first_, void* last_, void* out_)
{
    BigRec* first = (BigRec*)first_;
    BigRec* last = (BigRec*)last_;
    BigRec* out = (BigRec*)out_;
    for (; first != last; ++first, ++out)
        *out = *first;
    return out;
}

// @ 0x0076e9b0
void* __cdecl CopyBigRecRangeBack(void* first_, void* last_, void* out_)
{
    BigRec* first = (BigRec*)first_;
    BigRec* last = (BigRec*)last_;
    BigRec* out = (BigRec*)out_;
    while (first != last) {
        --first;
        --out;
        *out = *first;
    }
    return out;
}

// @ 0x0076ea60
void* cRTTCheat::Construct(int owner)
{
    ::new (this) EA::ArgScript::cCommandBase_s0076_db40;
    *(void**)this = (void*)0x140e468;
    ::new ((char*)this + 0x10) EA::ArgScript::cArgumentSpec_s0076_db40(true);
    *(int*)((char*)this + 0xd8) = owner;
    ((EA::ArgScript::cArgumentSpec_s0076_db40*)((char*)this + 0x10))->ConstructSpec(
        "Controls the render target manager",
        "-list^", 0,
        "List currently allocated pages",
        "-dump^", 1,
        "Dump all the render target textures in memory", 0);
    return this;
}

// @ 0x0076eb00
void cRTTCheat::Execute(void* args)
{
    cRTTCheatLayout* self = (cRTTCheatLayout*)this;
    self->mSpec.Parse((EA::ArgScript::cArguments_s0076_db40*)args, self->mParser);
    if (self->mFlags & 1) {
        unsigned count = (unsigned)((self->mPages->mEnd - self->mPages->mBegin) / 0x3c);
        count &= 0xffff;
        EA::ArgScript::Output(self->mParser, "%d render target pages allocated:\n", count);

        int total = 0;
        int freed = 0;
        rw::graphics::Raster_s0076_db40* r = g_defaultCameraRaster;
        if (r != 0) {
            unsigned size = r->D3D9GetMipLevelSize(0);
            total = (int)size;
            EA::ArgScript::Output(self->mParser,
                " DebugName: %hs, page %d, %d x %d, type %d, allocs %d, used %d, size %d K\n",
                "MainColor", 0, (int)r->m_width, (int)r->m_height, (int)r->m_format,
                1, 1, (size + 0x3ff) >> 10);
        }
        r = g_defaultZBufferRaster;
        if (r != 0) {
            unsigned size = r->D3D9GetMipLevelSize(0);
            total += (int)size;
            EA::ArgScript::Output(self->mParser,
                " DebugName: %hs, page %d, %d x %d, type %d, allocs %d, used %d, size %d K\n",
                "MainDepth", 0, (int)r->m_width, (int)r->m_height, (int)r->m_format,
                1, 1, (size + 0x3ff) >> 10);
        }
        for (int i = 0; i < (int)count; ++i) {
            RTTPageRec* rec = self->mPages->mBegin + i;
            int size = RasterFormatSize(rec->mWidth, rec->mHeight, rec->mType);
            total += size;
            if (rec->mAllocs == 0)
                freed += size;
            unsigned char used = ((FlagHolder*)rec)->IsSet();
            EA::ArgScript::Output(self->mParser,
                " DebugName: %hs, page %d, %d x %d, type %d, allocs %d, used %d, size %d K\n",
                0, i, (int)rec->mWidth, (int)rec->mHeight, (int)rec->mType, (int)rec->mAllocs,
                (int)used, (size + 0x3ff) >> 10);
        }
        EA::ArgScript::Output(self->mParser, "Total RTT pages: %1.1f MB freed: %1.1f MB\n",
            (double)((float)total * g_kBytesToMB), (double)((float)freed * g_kBytesToMB));
    }
    if ((self->mFlags >> 1) & 1)
        self->mPages->Release();
}

// @ 0x0076ed30
void ForceDel(cRTTCheat_s0076_ed30* p)
{ delete p; }

// @ 0x0076ed90
PageInfo_s0076_ed30* PageVec_s0076_ed30::erase(PageInfo_s0076_ed30* first, PageInfo_s0076_ed30* last)
{
    PageInfo_s0076_ed30* newEnd = MoveRange76(last, mEnd, first);
    destroyRange(newEnd, mEnd);
    mEnd -= last - first;
    return first;
}

// @ 0x0076edf0
void BigVec::Insert(BigRec3c* position, BigRec3c* value)
{
    BigRec3c** v = (BigRec3c**)this;
    BigRec3c* end = v[1];
    if (end != v[2]) {
        if (position <= value && value < end)
            value = (BigRec3c*)((char*)value + 0x3c);
        if (end)
            end->CopyFrom(end - 1);
        CopyBigRecRangeBack(position, end - 1, end);
        position->Assign(value);
        position->vec = &value->vec;
        position->f28 = value->f28;
        position->f2c = value->f2c;
        position->f30 = value->f30;
        position->f34 = value->f34;
        position->ref.GetImageResource(&value->ref);
        v[1] = end + 1;
        return;
    }
    int count = (int)(end - v[0]);
    int newCap;
    BigRec3c* pNew;
    if (count == 0) {
        newCap = 1;
    } else {
        newCap = count * 2;
        if (newCap == 0) { pNew = 0; goto allocdone; }
    }
    pNew = (BigRec3c*)EASTL_allocator_allocate(newCap * 0x3c, "Graphics", 0, 0, kAllocH, 0xd1);
allocdone:
    {
        BigRec3c* first = v[0];
        BigRec3c* mid = CopyBigRecRange(first, position, pNew);
        DestroyRecRange(first, position, pNew);
        if (mid)
            mid->CopyFrom(value);
        BigRec3c* last = v[1];
        BigRec3c* newEnd = CopyBigRecRange(position, last, mid + 1);
        DestroyRecRange(position, last, mid + 1);
        if (v[0] && *(int*)((char*)v[0] - 4) != 0)
            EASTL_allocator_deallocate(v[0]);
        v[1] = newEnd;
        v[0] = pNew;
        v[2] = (BigRec3c*)((char*)pNew + newCap * 0x3c);
    }
}

// @ 0x0076f050
bool cRTTManager_s0076_ed30::RTTCheatInit()
{
    if (mInitialized)
        return false;
    mInitialized = true;
    int w = SP::sAppProperties->HasProperty(0x1132287)
                ? SP::sAppProperties->GetIntProperty(0x1132287) : 0x400;
    int n = SP::sAppProperties->HasProperty(0x11322a0)
                ? SP::sAppProperties->GetIntProperty(0x11322a0) : 2;
    for (int i = n; i != 0; --i) {
        RTTRec3c rec;
        AllocateNewPage(-1, w, w, 0x15, &rec);
        mTexturePages.AppendPage(&rec);
    }
    Cheat* cheat = CheatManager();
    if (cheat) {
        void* mem = EASTL_allocator_allocate(0xdc, "Graphics", 0, 0, 0, 0);
        if (mem)
            ((cRTTCheatObj*)mem)->Construct(this);
    }
    MsgSrv* srv = (MsgSrv*)MessageServer();
    if (srv)
        srv->Send(&mField04, 0x3d037f1, 0);
    return true;
}

// @ 0x0076f280
void cRTTManager_s0076_ed30::RTTBigJob(int* out, int a3, int a4, int a5, uint32_t flags, int a7, int a8)
{
    uint32_t f2 = flags & 2;
    uint32_t f4 = flags & 4;
    bool b1 = (flags & 1) != 0;
    PageVec_s0076_ed30* pages = &mTexturePages;
    int idx = 0;
    int local_4c = -1;
    int cnt = (pages->mBegin == pages->mEnd) ? 0 : (int)(pages->mEnd - pages->mBegin);
    int w = a4;
    BigRec3c* rec = 0;
    if ((f4 != 0 || f2 != 0) && cnt > 0) {
        for (;;) {
            rec = (BigRec3c*)((char*)pages->mBegin + idx * 0x3c);
            w = rec->f28;
            bool ok = (w < 0) || (w == a5) || (a5 == 0x16 && w == 0x15);
            int* pi = (int*)Fn_67dd50()->v7();
            w = a4;
            int matched;
            if ((short)f2 == 0)
                matched = ok && ((short)f4 == 0 || (rec->f2c == 0x400 && rec->f30 == 0x400));
            else
                matched = ok && (rec->f2c == pi[0] && rec->f30 == pi[1]);
            if (matched) {
                local_4c = ((W1e70*)rec)->f((void*)(a3 + a8 * 2), (void*)(a4 + a8 * 2));
                if (local_4c != -1) {
                    rec->f34 += 1;
                    break;
                }
            }
            if (++idx >= cnt)
                break;
        }
        if (local_4c != -1) {
            *out = idx;
            out[1] = local_4c;
            return;
        }
    }
    int idx2;
    int local_50 = -1;
    if ((flags & 8) == 0 && FindPage(a3, w, a5, &w)) {
        int pageIdx = w;
        rec = (BigRec3c*)((char*)pages->mBegin + pageIdx * 0x3c);
        int r = ((W1e70*)rec)->f((void*)a3, (void*)pageIdx);
        local_50 = pageIdx;
        rec->f34 = 1;
        if (b1)
            CaptureJob(&local_50);
        *out = pageIdx;
        out[1] = r;
        return;    }
    idx2 = -1;
    RTTRec3c rec2;
    if (AllocateNewPage(a7, a3, w, a5, &rec2)) {
        local_4c = ((W1e70*)&rec2)->f((void*)a3, (void*)w);
        if (local_4c != -1) {
            idx2 = (int)(pages->mEnd - pages->mBegin);
            local_50 = idx2;
        }
        pages->AppendPage(&rec2);
        if (b1)
            CaptureJob(&local_50);
    }
    *out = idx2;
    out[1] = local_4c;
}
