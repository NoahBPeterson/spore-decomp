// src/game/Spui/SPUIShader.cpp -- migrated from slice(s) s0082f9a0, s0082ec70, s0082dc00 by tools/migrate/rewrite.py
// Object file: Spui/SPUIShader.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern int* sLayerRCs;         // 0x154744c : pointer to layer reference counts
extern void* g_appProps;       // 0x15fd918
extern char g_layerFlag0d;     // 0x164e90d
#include <math.h>
#include "cSPUIShaderProxy.h"
#include <new>
#include <string.h>

// ---- items of slice s0082dc00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_layerPool;      // 0x164e910
extern char g_layerFlag0c;     // 0x164e90c
extern int g_rectGlobal[4];    // 0x164e8fc
extern void* g_d3d;            // 0x16f89d0
extern char g_ctrlBlob;        // 0xc2e4e0 (SetSerializer tag)
extern void* g_obj164e8fc;     // 0x164e8fc (viewer object for Update)
extern char g_obj15474a0;                     // 0x15474a0
extern void RegisterCtl(int, void*, void*, void*, void*);
struct ImgHolder { int mDummy; void GetImageResource(void* r); };
struct LayerWinProc {
  char pad0[0x178];
  int mLayer;        // +0x178
  int mRefCount;     // +0x17c
  ImgHolder mImg[2]; // +0x180 (two 4-byte image-holder slots)
  float mFloats[0x10];  // +0x188
  bool SetLayer(int v);
  int ReleaseRef();
  void SetImage(unsigned i, void* r);
  float* FloatAt(int i);
  float GetFloat(unsigned i);
  void SetFloat(float v, unsigned i);
  void* AsInterface(int id);
  void CopyFloats(float* src, int start, int count);
  void SetImage2(unsigned* p, unsigned unused);
};
struct LayerFrame { void Init(void* param); };
struct RefObj { virtual void AddRef(); virtual void Release(); };
struct RelObj { virtual void r00(); virtual void r01(); virtual void r02(int); };
struct IfaceObj { virtual void i00(); virtual void i01(); virtual void i02(); virtual void* Query(unsigned); };
struct Global15474a0 { virtual void g00(); virtual void g01(); virtual void g02(); virtual void g03(void*, int); };
struct CallbackObj {
virtual void c00();
virtual void c01();
virtual void c02();
virtual void c03();
virtual void c04();
  virtual void* GetX();                       // 0x14
  virtual void c06();
  virtual bool SetCb(void*, void*);           // 0x1c
};
struct Renderer2 { void Draw(void*, void*, unsigned); void DrawC(void*, void*, unsigned); };
Renderer2* __cdecl GetRenderer2();            // 0x67cad0
struct UpdObj { void Update(); };             // 0x7c4fd0
struct BlobObj { unsigned Init(); };          // 0x962da0
struct MatMgr {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
virtual void m8();
virtual void m9();
  virtual void* GetMaterial(void*);
};
MatMgr* __cdecl GetMatMgr();                  // 0x67dd70
int __cdecl Handle(int);                      // 0x11fa000
typedef void (__stdcall *DevFn3)(void*, unsigned, void*);
typedef void (__stdcall *DevFn2)(void*, void*);
struct R16 { int v[4]; };
struct LO { char pad[0xc]; char c; unsigned char u; short pad2; void* v; void* q; };
void DestroyLayerProc(LayerWinProc* p);
struct Chunk { Chunk* mpNext; };
struct FixedAllocatorBase {
  char pad0[0x10];
  Chunk* mpHeadChunk;   // +0x10
  bool AddCore(int a, int b);
};
struct Pool5 {
  char pad0[4];
  FixedAllocatorBase* mpAlloc;   // +4
  Chunk* Pop5(int, int, int, int, int);
};
struct Pool3 {
  char pad0[4];
  FixedAllocatorBase* mpAlloc;   // +4
  Chunk* Pop3(int, int, int);
};
// ---- items of slice s0082dc00 end

// unnamed retail callees and globals that name local stubs (address in the comment)

// ---- items of slice s0082ec70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void     *g_d3dDevice;                 // 0x16f89d0
extern uint8_t   g_bRender3D;                 // 0x164e90c
extern uint8_t   g_bShaderInited;             // 0x164e90d
extern void     *g_pShader2D;                 // 0x164e910
extern void     *g_pShaderProxy;              // 0x164ea4c
extern void     *g_pAllocCore;                // 0x15474a4
extern void     *g_pField154724c;             // 0x154724c
extern void     *g_pField164e8fc;             // 0x164e8fc
extern wchar_t  *g_defaultMat;                // 0x1547250 (pointer to the default material name)
extern char      g_allocTag;                  // 0x13f6b3c
extern char      g_allocFile[];               // 0x13ebb38
extern char      g_fixedAlloc[];              // 0x164e990
extern char      g_vtblBase13fa72c;           // 0x13fa72c
extern char      g_vtblProxy141a668;          // 0x141a668
extern char      g_vtblMatWinProc;            // 0x141a5e8
extern char      g_vtblMatWinProcSec;         // 0x141a5d0
extern char      g_vtblEditorResource;        // 0x13eb938
extern wchar_t   g_emptyW[];                  // 0x1667bac
extern "C" void  __cdecl EA_Free(void *);                                        // 0xf47380
extern "C" void *__cdecl EA_Alloc(uint32_t, const void *, int, int, const char *, int); // 0xf473a0
extern "C" void *__cdecl msvc_memcpy(void *, const void *, uint32_t);            // 0x11e0744
extern "C" void *__cdecl msvc_memmove(void *, const void *, uint32_t);           // 0x13cc480
extern "C" bool  __cdecl FUN_0082e4f0(void *, void *);        // 0x82e4f0
extern "C" void  __cdecl SUB_00951d10(void *);                // 0x951d10
extern "C" void *__cdecl FUN_0067cad0();                      // 0x67cad0
extern "C" int   __cdecl FUN_0067de10();                      // 0x67de10
extern "C" int   __cdecl FUN_0067dd60();                      // 0x67dd60
extern "C" bool  __cdecl SUB_009568c0(int);                   // 0x9568c0
extern "C" void  __cdecl SUB_00956a30();                      // 0x956a30
extern "C" void  __cdecl SUB_007c3c10();                      // 0x7c3c10
extern "C" void *__cdecl FUN_00e23ee0(void *, void *, void *, uint8_t); // 0xe23ee0
extern "C" long  __cdecl _InterlockedExchangeAdd(volatile long *, long);
extern "C" void  __cdecl _ReadWriteBarrier(void);
extern "C" void *__cdecl FUN_00c7ea30(void *src, void *srcEnd, void *dst);   // 0xc7ea30 (memcpy(src, srcEnd, dst))
extern "C" void  __cdecl FUN_00edba80(void *pos, void *last, void *end);     // 0xedba80 (copy_backward)
struct H {
    void  FUN_0082e890();
    void  FUN_00951dc0(void *);
    bool  FUN_009528d0(void *, uint8_t);
    void  SUB_00962d10();
    bool  SUB_009630e0(void *, int);
    void  SUB_009265b0();
    bool  SUB_00926650(int, int);
    void  SUB_009266b0(int, int, int, int, int, int, int, int);
    void  SUB_00c2e4e0();
    void  SUB_007c3c10();
    int   AddBoundingBox(int);
    int   FUN_00a1ad10();
    void *FUN_0082f680(void *, void *);
    void *SUB_007f54d0();
};
struct SPUIShader2D;
class cSPUIShaderProxy_s0082_ec70;
struct u32vector {
    uint32_t *mpBegin;   // +0x00
    uint32_t *mpEnd;     // +0x04
    uint32_t *mpCap;     // +0x08
    uint32_t *mpUnused;  // +0x0c
    uint32_t *mpPool;    // +0x10
    void insert(uint32_t *pos, const uint32_t &val);  // 0x0082f170
};
struct Vec4 { uint32_t v[4]; };
struct Vec4vector {
    Vec4 *mpBegin;   // +0x00
    Vec4 *mpEnd;     // +0x04
    Vec4 *mpCap;     // +0x08
    Vec4 *mpUnused;  // +0x0c
    Vec4 *mpPool;    // +0x10
    void  insert(Vec4 *pos, const Vec4 &val);   // 0x0082f280
    Vec4 *emplace(Vec4 *pos, const Vec4 &val);  // 0x0082f3a0
};
extern u32vector g_layerVec;   // 0x154744c
struct SPUIShader2D {
    uint8_t   flag0;            // +0x000
    char      pad1[3];
    uint32_t  count;            // +0x004
    int32_t   field8;           // +0x008
    uint32_t  flagsC;           // +0x00c
    void     *field10;          // +0x010
    uint32_t  arr14[0x40];      // +0x014
    char      ent114[0x500];    // +0x114  (64 x 0x14)
    int32_t   countB;           // +0x614
    char      items618[0x600];  // +0x618  (16 x 0x60)
    uint32_t  boxC18[4];        // +0xc18
    char      padC28[0x34];     // +0xc28..+0xc5c
    uint32_t  fieldC5C;         // +0xc5c
    int32_t   refC60;           // +0xc60
    uint32_t  fieldC64;         // +0xc64
    void     *proxy;            // +0xc68

    void Process(void *item, uint32_t arg);   // 0x0082ec70
    void Cleanup();                            // 0x0082f020
};
class cSPUIShaderProxy_s0082_ec70 { public:
    void     *vptr;             // +0x000
    char      map[0x118];       // +0x004
    char      name[0x54];       // +0x11c
    uint32_t  materialID;       // +0x170
    int32_t   layerId;          // +0x174
    int32_t   refCount;         // +0x178
    int32_t   field17c;         // +0x17c
    void     *textures[2];      // +0x180
    float     parameters[16];   // +0x188

    __declspec(noinline) cSPUIShaderProxy_s0082_ec70 *Construct(); // 0x0082f410 (ctor body)
    ~cSPUIShaderProxy_s0082_ec70();                           // 0x0082f500
    bool GetParam(uint32_t, uint32_t *, uint32_t *, uint32_t *); // 0x0082f5c0
};
class cSPUIMaterialWinProc { public:
    void     *vptr;             // +0x00
    void     *vptrSec;          // +0x04
    int32_t   refCount;         // +0x08
    uint8_t   mbRecursive;      // +0x0c
    char      pad0d[3];
    wchar_t  *nameBegin;        // +0x10
    wchar_t  *nameEnd;          // +0x14
    wchar_t  *nameCap;          // +0x18
    void     *nameAlloc;        // +0x1c
    void     *myWindow;         // +0x20

    cSPUIMaterialWinProc();                     // 0x0082f0b0
    void    *Destroy(unsigned flags);           // 0x0082f110
};
struct ParamMap {
    uint32_t *mpBegin;   // +0x000
    uint32_t *mpEnd;     // +0x004
    char      pad08[0x110];
    uint8_t   flag118;   // +0x118
    uint32_t *findInsert(uint32_t *key);   // 0x0082f930
};
struct fixed_wstring {
    void    *alloc0;      // +0
    wchar_t *begin;       // +4
    wchar_t *end;         // +8
    wchar_t *capacity;    // +0xc
    wchar_t *unused10;    // +0x10
    wchar_t *pool;        // +0x14
    wchar_t  buffer[32];  // +0x18
    void assign(const wchar_t *first, const wchar_t *last);   // 0x678ee0
};
cSPUIMaterialWinProc::cSPUIMaterialWinProc()
{
    *(void *volatile *)((char *)this + 4) = &g_vtblBase13fa72c;
    _ReadWriteBarrier();
    refCount = 0;
    vptr     = &g_vtblMatWinProc;
    vptrSec  = &g_vtblMatWinProcSec;
    mbRecursive = 1;
    _ReadWriteBarrier();
    wchar_t *p = g_emptyW;
    nameBegin = p;
    nameEnd   = p;
    nameCap   = p + 1;
    myWindow  = 0;
}
struct QueueItem {
    void    *pData;          // +0x00
    uint8_t  b4, b5, b6, b7;// +0x04
    float    f2, f3, f4, f5; // +0x08,+0x0c,+0x10,+0x14
    char     pad18[0x10];    // +0x18
    float    f10, f11;       // +0x28,+0x2c
    uint8_t  pad30[4];       // +0x30
    float    f13, f14;       // +0x34,+0x38
};
struct IterCopy {
    void *container;                     // +0x00
    void *begin;                         // +0x04
    void *end;                           // +0x08
    void *f0c, *f10, *f14, *f18, *f1c;   // +0x0c..
    IterCopy *Set(int *src);             // 0x00951dc0
};
struct IterData {
    int32_t  id;     // +0x00
    int32_t  acc;    // +0x04
    uint32_t u2c;    // +0x08
    int32_t  u28;    // +0x0c
    void    *p24;    // +0x10
};
static inline int ToInt(float f) { return (int)f; }
cSPUIShaderProxy_s0082_ec70::~cSPUIShaderProxy_s0082_ec70()
{
    char *t = (char *)this;
    for (int i = 1; i >= 0; --i) {
        void *p = *(void **)(t + 0x180 + i * 4);
        if (p) {
            volatile long *rc = (volatile long *)((char *)p + 8);
            _InterlockedExchangeAdd(rc, -1);
            long v = _InterlockedExchangeAdd(rc, 0);
            if (v >= 1)
                _InterlockedExchangeAdd(rc, 0);
            else
                _InterlockedExchangeAdd(rc, 1);
        }
    }
    void *beg  = *(void **)(t + 0x120);
    void *cap  = *(void **)(t + 0x128);
    void *pool = *(void **)(t + 0x130);
    if ((((int)((char *)cap - (char *)beg)) & ~1) > 2 && beg && beg != pool)
        EA_Free(beg);
    void *mb = *(void **)(t + 4);
    if (mb && mb != *(void **)(t + 0x14))
        EA_Free(mb);
    vptr = &g_vtblEditorResource;
}
// ---- items of slice s0082ec70 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void LayerProcDraw(void* a1, void* a2, int a3);  // 0x0082e300 (stays in the slice: not this object's)

// ---- items of slice s0082f9a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl operator_delete__(void*);   // 0xf47380 (operator delete[])
extern "C" uint32_t __cdecl FNV1_String8(const char*, uint32_t basis, int lower);    // 0x932e80
extern "C" uint32_t __cdecl FNV1_String16(const wchar_t*, uint32_t basis, int lower); // 0x932f30
extern const wchar_t* g_defaultMaterialName;   // 0x1547250 (pointer to L"ui_material_default")
struct Str8 { char* b; char* e; char* c; };       // eastl::string (8 bit), heap only
struct Str16 { wchar_t* b; wchar_t* e; wchar_t* c; };
extern "C" void __cdecl ConvertToString8(Str8* out, const wchar_t* src, int len);   // 0x93c440
extern "C" Str16* __cdecl ConvertToString16(Str16* out, const char* src, int len);  // 0x93c5a0
struct FixedStr16   // eastl::fixed string of 32 wchar_t (0x54 bytes)
{
    wchar_t* b; wchar_t* e; wchar_t* c; uint32_t alloc; wchar_t* pool; wchar_t buf[32];
    void assign(const wchar_t* first, const wchar_t* last);   // 0x672750
    FixedStr16* AssignCStr(const wchar_t* s);                  // 0x8369e0
};
struct MemberStr16  // the string at this+0x120 (other fixed allocator instance)
{
    wchar_t* b; wchar_t* e; wchar_t* c;
    void assign(const wchar_t* first, const wchar_t* last);   // 0x678ee0
};
extern bool __cdecl StrEqual(const MemberStr16& a, const wchar_t* b);  // 0x6ab760
struct cArguments
{
    char pad[0x64];
    cArguments();                                  // 0x837ff0
    ~cArguments();                                 // 0x837fa0
    void SplitIntoArguments(const char* s);        // 0x8383c0
    void GetArguments(int& count, char**& argv);   // 0x837f80
    bool HasArgument(const char* name);            // 0x837ee0
};
struct Vec2 { float x, y; };
struct Vec3 { float x, y, z; };
struct Vec4_s0082_f9a0 { float x, y, z, w; };
struct cParser
{
    char pad[0x1b0];
    cParser();    // 0x847490
    ~cParser();   // 0x847200
    bool ParseBool(const char* s);       // 0x8413e0
    float ParseFloat(const char* s);     // 0x8413f0
    Vec2* ParseVector2(Vec2& out, const char* s);   // 0x841540
    Vec3* ParseVector3(Vec3& out, const char* s);   // 0x841590
    Vec4_s0082_f9a0* ParseRGBA(Vec4_s0082_f9a0& out, const char* s);      // 0x841610
    Vec4_s0082_f9a0* ParseRGB(Vec4_s0082_f9a0& out, const char* s);       // 0x8416b0
};
struct PropertyList
{
    virtual void v0();
    virtual void Release();   // 1
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
    virtual void GetPropertyKeys(void* outVec);   // 0x11 (+0x44)
};
struct PropertyManager
{
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
virtual void v11();
    virtual void GetPropertyList(uint32_t id, PropertyList** out);   // 0xc (+0x30)
};
PropertyManager* __cdecl GetPropertyManager();   // 0x67de30  (SP::PropertyManager)
extern bool __cdecl GetPropertyAsUint32Array(PropertyList* list, uint32_t id, uint32_t& count, uint32_t*& arr);   // 0x6a0840
struct PropertyListPtr
{
    PropertyList* p;
    void reset() { PropertyList* o = p; if (o) { p = 0; o->Release(); } }
};
struct KeyVec { uint32_t* b; uint32_t* e; void resize(unsigned n); };   // 0x4cd3c0
extern KeyVec g_keyVec;   // 0x164e9f8
struct MapEntry { uint32_t key, a, b, c; };
extern "C" MapEntry* __cdecl RunInfoCopy(MapEntry* first, MapEntry* last, MapEntry* result);   // 0x705250
struct ShaderProxy
{
    char pad0[4];
    MapEntry* mapBegin;      // +4
    MapEntry* mapEnd;        // +8
    char pad1[0x114];
    MemberStr16 name;        // +0x120
    char pad2[0x48];
    uint32_t nameHash;       // +0x174 (index 0x174)
    char pad3[0x10];
    float params[16];        // +0x188

    uint32_t* MapAt(const uint32_t& key);                              // 0x82f930 (returns value triple)
    bool MapLookup(uint32_t hash, uint32_t& off, uint32_t& type, int* cnt);   // 0x82f5c0
    void StoreParams(const float* v, uint32_t off, int n);             // 0x82e380
    bool SetFromArgScript(const wchar_t* args);                        // 0x82f9a0
};
// ---- items of slice s0082f9a0 end

// @ 0x0082e380
void LayerWinProc::CopyFloats(float* src, int start, int count)
{
  float* d = mFloats + start;
  float* e = d + count;
  while (d < e) *d++ = *src++;
}

// @ 0x0082e400
bool AppFlagSet()
{
  void* a = g_appProps;
  int* b = *(int**)((char*)a + 0x3c);
  return b[0x110 / 4] != 0;
}

// @ 0x0082e420
void* LayerWinProc::AsInterface(int id)
{
  if (id <= 0x838293) {
    if (id == 0x838293) return this;
    if (id == (int)0xae9cb0fa) return this;
    if (id == (int)0xee3f516e) return this;
  } else {
    if (id == 0x5234b49) return this;
    if (id == (int)0x6ed3e59b) return this;
  }
  return 0;
}

// @ 0x0082e470
void RegisterE300()
{
  RegisterCtl(0x234, &g_ctrlBlob, &g_ctrlBlob, &g_ctrlBlob, &LayerProcDraw);
}

// @ 0x0082e4c0
void CopyRectGlobal(int* p)
{
  g_rectGlobal[0] = p[0];
  g_rectGlobal[1] = p[1];
  g_rectGlobal[2] = p[2];
  g_rectGlobal[3] = p[3];
}

// @ 0x0082e4f0
int RectNotEqual(int* a, int* b)
{
  if (a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3]) return 0;
  return 1;
}

// @ 0x0082e520
Chunk* Pool5::Pop5(int, int, int, int, int)
{
  FixedAllocatorBase* p = mpAlloc;
  do {
    if (p->mpHeadChunk) {
      Chunk* c = p->mpHeadChunk;
      p->mpHeadChunk = c->mpNext;
      return c;
    }
  } while (p->AddCore(0, 0));
  return 0;
}

// @ 0x0082e550
void __fastcall LayerFrameInit(char* self, int dummy, char* param)
{
  (void)dummy;
  ((UpdObj*)g_obj164e8fc)->Update();
  *(char*)self = (char)((BlobObj*)(self + 0xc28))->Init();
  *(int*)(self + 0x614) = 0;
  *(int*)(self + 4) = 0;
  *(int*)(self + 8) = 0;
  *(int*)(self + 0xc) = 0;
  *(int*)(self + 0x10) = 0;
  *(char**)(self + 0xc68) = param;
  void* m;
  if (*(int*)(param + 0x174) == 0)
    m = 0;
  else
    m = GetMatMgr()->GetMaterial(*(void**)(param + 0x174));
  *(void**)(self + 0xc64) = m;
  void* state = *(void**)(self + 0xc2c);
  int h = Handle(1);
  g_layerFlag0c = (*(int*)(*(int*)((char*)g_appProps + 0x3c) + 0xb8) != 0);
  if (g_layerFlag0c) {
    ((DevFn3)(*(void***)g_d3d)[0xe8 / 4])(g_d3d, 0xae, self + 0xc5c);
    R16* r = (R16*)(self + 0xc4c);
    ((DevFn2)(*(void***)g_d3d)[0x130 / 4])(g_d3d, r);
    ((DevFn3)(*(void***)g_d3d)[0xe4 / 4])(g_d3d, 0xae, (void*)1);
    int e = *(int*)(self + 0xc58), c = *(int*)(self + 0xc54), b = *(int*)(self + 0xc50), a = r->v[0];
    int* d = (int*)(self + 0xc18);
    d[0] = a; d[1] = b; d[2] = c; d[3] = e;
    h = Handle(2);
  }
  *(int*)((char*)state + 0x18) = h;
}

// @ 0x0082e6b0
void __fastcall LayerPoolTick(void* arg)
{
  ((LayerFrame*)g_layerPool)->Init(arg);
}

// @ 0x0082e6c0
bool __cdecl LayerProcRelease(LayerWinProc* p)
{
  unsigned idx = p->mLayer;
  if (idx <= 0xe) sLayerRCs[idx] = sLayerRCs[idx] - 1;
  ((RelObj*)p)->r02(0);
  ((Global15474a0*)&g_obj15474a0)->g03(p, 0);
  return true;
}

// @ 0x0082e700
bool IsLayerUsed(unsigned v)
{
  if (v <= 0xe) return sLayerRCs[v] > 0;
  return false;
}

// @ 0x0082e750
void RenderLayer(void* p)
{
  LO* o;
  if (p) o = (LO*)((IfaceObj*)p)->Query(0x2f009dd0);
  else o = 0;
  if (o->q) {
    unsigned u = o->u;
    if (o->c) {
      void* v = o->v;
      GetRenderer2()->DrawC(o->q, v, u);
    } else {
      void* v = o->v;
      GetRenderer2()->Draw(o->q, v, u);
    }
  }
}

// @ 0x0082e7a0
bool __fastcall LayerWinProcSetChild(LayerWinProc* self, int dummy, CallbackObj* child)
{
  (void)dummy;
  RefObj* old = *(RefObj**)((char*)self + 0x14);
  if ((void*)child != (void*)old) {
    if (child) ((RefObj*)child)->AddRef();
    *(CallbackObj**)((char*)self + 0x14) = child;
    if (old) old->Release();
  }
  CallbackObj* x = (CallbackObj*)child->GetX();
  void* y;
  if (self) y = ((IfaceObj*)self)->Query(0xee3f516e);
  else y = 0;
  bool r = x->SetCb((void*)&RenderLayer, y);
  return r & 0xffffff00;
}

// @ 0x0082e840
Chunk* Pool3::Pop3(int, int, int)
{
  FixedAllocatorBase* p = mpAlloc;
  do {
    if (p->mpHeadChunk) {
      Chunk* c = p->mpHeadChunk;
      p->mpHeadChunk = c->mpNext;
      return c;
    }
  } while (p->AddCore(0, 0));
  return 0;
}

// @ 0x0082e870
void LayerWinProc::SetImage2(unsigned* p, unsigned unused)
{
  (void)unused;
  int* fa = *(int**)((char*)this + 4);
  *p = fa[4];
  fa[4] = (int)p;
}

// @ 0x0082e890
void LayerFrameUpdate()
{
}

// @ 0x0082eb80
void LayerWinProc::SetImage(unsigned i, void* r)
{
  if (i < 2) mImg[i].GetImageResource(r);
}

// @ 0x0082eba0
int LayerWinProc::ReleaseRef()
{
  int old = mRefCount;
  int n = old - 1;
  mRefCount = n;
  if (n == 0 && g_layerFlag0d) DestroyLayerProc(this);
  return n;
}

// @ 0x0082ebd0
LayerWinProc* __fastcall LayerWinProcCtor(LayerWinProc* p)
{
  volatile int* d = (volatile int*)p;
  int zero = 0;
  char one = 1;
  d[1] = 0x13fa72c;
  d[2] = zero;
  d[0] = 0x141a550;
  d[1] = 0x141a538;
  *(volatile char*)((char*)p + 0xc) = one;
  *(volatile char*)((char*)p + 0xd) = one;
  d[4] = zero;
  d[5] = zero;
  return p;
}

// @ 0x0082ec70
void SPUIShader2D::Process(void *itemv, uint32_t arg)
{
    QueueItem *item = (QueueItem *)itemv;
    if (!flag0)
        return;

    cSPUIShaderProxy_s0082_ec70 *px = (cSPUIShaderProxy_s0082_ec70 *)proxy;
    int saved = px->refCount;
    void *r = FUN_0067cad0();
    if (saved != ((H *)r)->FUN_00a1ad10())
        return;

    int q[4];
    IterData it;
    IterCopy range;

    if (countB >= 0x10)
        ((H *)this)->FUN_0082e890();

    if (g_bRender3D) {
        q[0] = ToInt(item->f2);
        q[1] = ToInt(item->f3);
        q[2] = ToInt(item->f4);
        q[3] = ToInt(item->f5);
        if (FUN_0082e4f0((char *)this + 0xc18, q)) {
            ((H *)this)->FUN_0082e890();
            *(uint32_t *)((char *)this + 0xc18) = q[0];
            *(uint32_t *)((char *)this + 0xc1c) = q[1];
            *(uint32_t *)((char *)this + 0xc20) = q[2];
            *(uint32_t *)((char *)this + 0xc24) = q[3];
            void *dev = g_d3dDevice;
            void **vt = *(void ***)dev;
            ((void (__stdcall *)(void *, uint32_t *))vt[0x12c / 4])(dev, (uint32_t *)q);
        }
    }

    range.Set((int *)arg);
    bool changed = false;
    if (range.begin != range.end) {
        do {
            if (!((H *)&range)->FUN_009528d0(&it, (uint8_t)(count > 0))) {
                ((H *)this)->FUN_0082e890();
                changed = false;
                continue;
            }
            uint32_t param = 0;
            if (((flagsC ^ it.u2c) & 2) != 0) {
                if (count != 0) {
                    ((H *)this)->FUN_0082e890();
                    changed = false;
                }
            }
            if (count != 0 && *(int *)((char *)this + 0x114) != it.id) {
                ((H *)this)->FUN_0082e890();
                changed = false;
            }
            if (it.p24) {
                void *a = *(void **)((char *)it.p24 + 4);
                if (a) {
                    int v = *(int *)((char *)a + 4);
                    if (v == 0) {
                        typedef int (__thiscall *FnStr)(void *, const char *);
                        v = ((FnStr)(*(void ***)a)[0xc / 4])(a, "itorButtonBounceDuration");
                        if (v) {
                            void *alloc = ((H *)v)->SUB_007f54d0();
                            if (((*(uint8_t *)((char *)alloc + 4)) & 1) == 0) {
                                int dummy = FUN_0067dd60();
                                void **vt = *(void ***)dummy;
                                ((void (__thiscall *)(void *, void *))vt[0x34 / 4])((void *)dummy, alloc);
                            }
                            v = *(int *)alloc;
                        }
                    }
                    if (v) {
                        if (field10 && field10 != (void *)v) {
                            ((H *)this)->FUN_0082e890();
                            changed = false;
                        }
                        if (field10 && ((flagsC ^ it.u2c) & 1) != 0 && count != 0) {
                            ((H *)this)->FUN_0082e890();
                            changed = false;
                        }
                        field10 = (void *)v;
                        param = 0xff;
                    }
                }
            }
            flagsC |= it.u2c;
            if (!changed) {
                int idx = countB;
                countB = idx + 1;
                float *dst = (float *)((char *)this + idx * 0x60 + 0x618);
                memcpy(dst + 4, item->pData, 0x40);
                const float k = 0.003921569f;
                dst[2] = (float)item->b4 * k;
                dst[0] = (float)item->b6 * k;
                dst[1] = (float)item->b5 * k;
                dst[3] = (float)item->b7 * k;
                if (!g_bRender3D) {
                    dst[0x14] = item->f2 * item->f13 + item->f10;
                    dst[0x15] = item->f5 * item->f14 + item->f11;
                    dst[0x16] = item->f4 * item->f13 + item->f10;
                    dst[0x17] = item->f3 * item->f14 + item->f11;
                } else {
                    dst[0x14] = -10000.0f;
                    dst[0x15] = -10000.0f;
                    dst[0x16] = 10000.0f;
                    dst[0x17] = 10000.0f;
                }
                changed = true;
            }
            field8 += it.acc;
            arr14[count] = (uint32_t)((countB - 1) * 0x600) | param;
            int i2 = count;
            *(int *)(ent114 + i2 * 0x14 + 0)  = it.id;
            *(int *)(ent114 + i2 * 0x14 + 4)  = it.acc;
            *(uint32_t *)(ent114 + i2 * 0x14 + 8)  = it.u2c;
            *(int *)(ent114 + i2 * 0x14 + 0xc) = it.u28;
            *(void **)(ent114 + i2 * 0x14 + 0x10) = it.p24;
            if ((uint32_t)++count >= 0x40) {
                ((H *)this)->FUN_0082e890();
                changed = false;
            }
        } while (range.begin != range.end);
    }
}

// @ 0x0082f020
void SPUIShader2D::Cleanup()
{
    if (count != 0)
        ((H *)this)->FUN_0082e890();
    ((H *)((char *)this + 0xc28))->SUB_00c2e4e0();
    flag0 = 0;
    proxy = 0;
    if (g_bRender3D) {
        ((void (__stdcall *)(void *, int, void *))((*(void ***)g_d3dDevice))[0xe4 / 4])
            (g_d3dDevice, 0xae, *(void **)((char *)this + 0xc5c));
        ((void (__stdcall *)(void *, void *))((*(void ***)g_d3dDevice))[0x12c / 4])
            (g_d3dDevice, (char *)this + 0xc4c);
    }
    ((H *)g_pField164e8fc)->SUB_007c3c10();
}

// @ 0x0082f110
void *cSPUIMaterialWinProc::Destroy(unsigned flags)
{
    vptr    = &g_vtblMatWinProc;
    vptrSec = &g_vtblMatWinProcSec;
    _ReadWriteBarrier();
    void *w = myWindow;
    if (w) {
        void **vt = *(void ***)w;
        ((void (__thiscall *)(void *))vt[1])(w);
    }
    if ((((int)((char *)nameCap - (char *)nameBegin)) & ~1) > 2 && nameBegin)
        EA_Free(nameBegin);
    vptrSec = &g_vtblEditorResource;
    vptr    = &g_vtblEditorResource;
    if (flags & 1)
        EA_Free(this);
    return this;
}

// @ 0x0082f170
void u32vector::insert(uint32_t *pos, const uint32_t &val)
{
    uint32_t *end = mpEnd;
    if (end != mpCap) {
        uint32_t *v = (uint32_t *)&val;
        if ((char *)v >= (char *)pos && (char *)v < (char *)end)
            v = (uint32_t *)((char *)v + 4);
        if (end)
            *end = end[-1];
        int n = (int)((char *)(end - 1) - (char *)pos);
        msvc_memmove((char *)end - ((n >> 2) * 4), pos, (uint32_t)n);
        *pos = *v;
        mpEnd = end + 1;
        return;
    }

    size_t nelem = (size_t)(end - mpBegin);
    size_t newcap;
    uint32_t *nbuf;
    if (nelem == 0) {
        newcap = 1;
    } else {
        newcap = nelem * 2;
        if (newcap == 0) {
            nbuf = 0;
            goto haveBuffer;
        }
    }
    nbuf = (uint32_t *)EA_Alloc((uint32_t)(newcap * 4), &g_allocTag, 0, 0, g_allocFile, 0xd1);
haveBuffer:
    {
        int prefix = (int)((char *)pos - (char *)mpBegin);
        uint32_t *p = (uint32_t *)msvc_memcpy(nbuf, mpBegin, (uint32_t)prefix);
        p = (uint32_t *)((char *)p + (size_t)(prefix >> 2) * 4);
        if (p)
            *p = val;
        int suffix = (int)((char *)mpEnd - (char *)pos);
        p = (uint32_t *)msvc_memcpy((char *)p + 4, pos, (uint32_t)suffix);
        uint32_t *newend = (uint32_t *)((char *)p + (size_t)(suffix >> 2) * 4);
        if (mpBegin && mpBegin != mpPool)
            EA_Free(mpBegin);
        mpBegin = nbuf;
        mpEnd   = newend;
        mpCap   = (uint32_t *)((char *)nbuf + newcap * 4);
    }
}

// @ 0x0082f280
void Vec4vector::insert(Vec4 *pos, const Vec4 &val)
{
    Vec4 *end = mpEnd;
    if (end != mpCap) {
        Vec4 *v = (Vec4 *)&val;
        if ((char *)v >= (char *)pos && (char *)v < (char *)end)
            v = (Vec4 *)((char *)v + 0x10);
        if (end) {
            end[0] = end[-1];
        }
        FUN_00edba80(pos, end - 1, end);
        *pos = *v;
        mpEnd = end + 1;
        return;
    }

    int nelem = (int)((char *)end - (char *)mpBegin) >> 4;
    int newcap;
    Vec4 *nbuf;
    if (nelem == 0) {
        newcap = 1;
    } else {
        newcap = nelem * 2;
        if (newcap == 0) {
            nbuf = 0;
            goto haveBuffer;
        }
    }
    nbuf = (Vec4 *)EA_Alloc((uint32_t)(newcap << 4), &g_allocTag, 0, 0, g_allocFile, 0xd1);
haveBuffer:
    {
        Vec4 *p = (Vec4 *)FUN_00c7ea30(mpBegin, pos, nbuf);
        if (p)
            *p = val;
        Vec4 *q = (Vec4 *)FUN_00c7ea30(pos, mpEnd, (char *)p + 0x10);
        if (mpBegin && mpBegin != mpPool)
            EA_Free(mpBegin);
        mpEnd   = q;
        mpCap   = (Vec4 *)((char *)nbuf + newcap * 0x10);
        mpBegin = nbuf;
    }
}

// @ 0x0082f3a0
Vec4 *Vec4vector::emplace(Vec4 *pos, const Vec4 &val)
{
    Vec4 *end = mpEnd;
    int idx = (int)(pos - mpBegin);
    if (pos == end && end != mpCap) {
        mpEnd = end + 1;
        if (end)
            *end = val;
        return mpBegin + idx;
    }
    insert(pos, val);
    return mpBegin + idx;
}

// @ 0x0082f410
cSPUIShaderProxy_s0082_ec70 *cSPUIShaderProxy_s0082_ec70::Construct()
{
    char *t = (char *)this;
    vptr = &g_vtblProxy141a668;

    char *b = t + 0x1c;
    *(void **)(t + 0x14) = b;
    *(void **)(t + 0x08) = b;
    *(void **)(t + 0x04) = b;
    b += 0x100;
    *(void **)(t + 0x0c) = b;

    wchar_t *s = (wchar_t *)(t + 0x134);
    *(void **)(t + 0x120) = s;
    *(void **)(t + 0x124) = s;
    *(void **)(t + 0x128) = s + 0x20;
    *(void **)(t + 0x130) = s;
    s[0] = 0;

    refCount = 0;
    field17c = 0;
    textures[0] = textures[1] = 0;

    wchar_t *def = g_defaultMat;
    wchar_t *e = def;
    while (*e) ++e;
    ((fixed_wstring *)(t + 0x120))->assign(def, e);

    layerId = 0;
    for (int i = 0; i < 16; ++i)
        parameters[i] = 0.0f;
    return this;
}

// @ 0x0082f5c0
bool cSPUIShaderProxy_s0082_ec70::GetParam(uint32_t key, uint32_t *out4, uint32_t *outc, uint32_t *out8)
{
    uint32_t *end = *(uint32_t **)((char *)this + 8);
    uint32_t *it = (uint32_t *)FUN_00e23ee0(*(void **)((char *)this + 4), end, &key,
                                            *(uint8_t *)((char *)this + 0x11c));
    if (it == end || key < it[0])
        it = end;
    if (it == end)
        return false;
    // Store order follows the original's argument slots: out4 <- it[1], out8 <- it[2], outc <- it[3].
    if (out4) *out4 = it[1];
    if (out8) *out8 = it[2];
    if (outc) *outc = it[3];
    return true;
}

// @ 0x0082f630
void *AcquireShaderProxy()
{
    void *a = g_pAllocCore;
    int *fl = (int *)((char *)a + 0x10);
    while (*fl == 0) {
        if (!((H *)a)->SUB_00926650(0, 0))
            break;
    }
    void *node = (void *)*fl;
    if (node) {
        *fl = *(int *)node;
        node = ((cSPUIShaderProxy_s0082_ec70 *)node)->Construct();
    }
    uint32_t ecx = *(uint32_t *)((char *)node + 0x178);
    if (ecx <= 0xe)
        ++g_layerVec.mpBegin[ecx];
    return node;
}

// @ 0x0082f6e0
void *GetShaderProxy()
{
    if (g_pShaderProxy)
        return g_pShaderProxy;
    void *p = AcquireShaderProxy();
    if (p != g_pShaderProxy) {
        void *old = g_pShaderProxy;
        if (p)
            ((void (__thiscall *)(void *))(*(void ***)p)[0])(p);
        g_pShaderProxy = p;
        if (old)
            ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
    }
    void *q = g_pShaderProxy;
    uint32_t *pLayer = (uint32_t *)((char *)q + 0x178);
    uint32_t layer = *pLayer;
    if (layer) {
        if (layer <= 0xe)
            --g_layerVec.mpBegin[layer];
        *pLayer = 0;
        ++g_layerVec.mpBegin[0];
    }
    return g_pShaderProxy;
}

// @ 0x0082f760
bool Init2DSystem()
{
    if (g_bShaderInited)
        return true;

    for (int i = 0; i < 15; ++i) {
        uint32_t zero = 0;
        if (g_layerVec.mpEnd < g_layerVec.mpCap) {
            uint32_t *slot = g_layerVec.mpEnd;
            g_layerVec.mpEnd = slot + 1;
            if (slot)
                *slot = 0;
        } else {
            g_layerVec.insert(g_layerVec.mpEnd, zero);
        }
    }

    ((H *)g_fixedAlloc)->SUB_009266b0(0x1c8, 4, 0x20, 0, 0, 0, 0, 0);

    SPUIShader2D *o = (SPUIShader2D *)EA_Alloc(0xc6c, &g_allocTag, 0, 0, 0, 0);
    if (o) {
        o->flag0 = 0;
        *(uint32_t *)((char *)o + 0xc18) = 0xffffffff;
        *(uint32_t *)((char *)o + 0xc1c) = 0xffffffff;
        *(uint32_t *)((char *)o + 0xc20) = 0xffffffff;
        *(uint32_t *)((char *)o + 0xc24) = 0xffffffff;
        *(uint32_t *)((char *)o + 0xc60) = 0;
        *(uint32_t *)((char *)o + 0xc64) = 0;
        *(uint32_t *)((char *)o + 0xc68) = 0;
    }
    g_pShader2D = o;
    int *rc = (int *)((char *)o + 0xc60);
    g_bShaderInited = 1;

    bool ok;
    if (*rc != 0 || ((H *)((char *)o + 0xc28))->SUB_009630e0(g_pField154724c, 0x234)) {
        ++*rc;
        void *p = GetShaderProxy();
        if (((bool (__thiscall *)(void *))(*(void ***)p)[0x20 / 4])(p)) {
            ok = true;
            goto done;
        }
    }
    ok = false;
done:
    {
        void *p = GetShaderProxy();
        SUB_00951d10(p);
    }
    if (ok) {
        int x = FUN_0067de10();
        if (SUB_009568c0(x))
            return true;
    }
    return false;
}

// @ 0x0082f8a0
void Shutdown2DSystem()
{
    if (!g_bShaderInited)
        return;
    SUB_00956a30();
    SPUIShader2D *o = (SPUIShader2D *)g_pShader2D;
    if (--*(int *)((char *)o + 0xc60) == 0)
        ((H *)((char *)o + 0xc28))->SUB_00962d10();
    void *p = GetShaderProxy();
    ((void (__thiscall *)(void *))(*(void ***)p)[0x24 / 4])(p);
    void *q = g_pShaderProxy;
    if (q) {
        g_pShaderProxy = 0;
        ((void (__thiscall *)(void *))(*(void ***)q)[1])(q);
    }
    EA_Free(g_pShader2D);
    g_pShader2D = 0;
    g_bShaderInited = 0;
    ((H *)g_fixedAlloc)->SUB_009265b0();
}

// @ 0x0082f930
uint32_t *ParamMap::findInsert(uint32_t *key)
{
    uint32_t *end = mpEnd;
    uint32_t *it = (uint32_t *)FUN_00e23ee0(mpBegin, end, key, flag118);
    if (it == end || *key < *it) {
        uint32_t local[4];
        local[0] = *key;
        local[1] = 0x10;
        local[2] = 0;
        local[3] = 0xffffffff;
        it = (uint32_t *)((H *)this)->FUN_0082f680(it, local);
    }
    return it + 1;
}

// @ 0x0082f9a0
bool ShaderProxy::SetFromArgScript(const wchar_t* args)
{
    g_keyVec.resize(0);
    {
        MapEntry* f = mapBegin;
        MapEntry* l = mapEnd;
        RunInfoCopy(l, l, f);
        mapEnd += -(l - f);
    }
    Str8 s8;
    ConvertToString8(&s8, args, -1);

    FixedStr16 fs;
    fs.b = fs.buf; fs.e = fs.b; fs.pool = fs.buf; fs.c = fs.buf + 32; fs.buf[0] = 0;
    {
        const wchar_t* p = args;
        while (*p) ++p;
        fs.assign(args, args + (p - args));
    }
    {
    cArguments a;
    a.SplitIntoArguments(s8.b);
    int count = 0;
    char** argv = 0;
    a.GetArguments(count, argv);
    if (count > 0)
    {
        Str16 t;
        fs.AssignCStr(ConvertToString16(&t, argv[0], -1)->b);
        if ((((char*)t.c - (char*)t.b) & ~1) > 2 && t.b) operator_delete__(t.b);
        if (count > 1)
        {
            PropertyListPtr list; list.p = 0;
            PropertyManager* mgr = GetPropertyManager();
            list.reset();
            uint32_t h = FNV1_String8(argv[0], 0x811c9dc5, 1);
            mgr->GetPropertyList(h, &list.p);
            if (!list.p)
            {
                mgr = GetPropertyManager();
                list.reset();
                h = FNV1_String16(g_defaultMaterialName, 0x811c9dc5, 1);
                mgr->GetPropertyList(h, &list.p);
            }
            if (list.p)
            {
                list.p->GetPropertyKeys(&g_keyVec);
                while (g_keyVec.b != g_keyVec.e)
                {
                    uint32_t key = *--g_keyVec.e;
                    uint32_t n = 0;
                    uint32_t* arr = 0;
                    if (GetPropertyAsUint32Array(list.p, key, n, arr) || n == 2)
                    {
                        int type = arr[1];
                        int comps;
                        switch (type)
                        {
                        case 0: case 1: comps = 1; break;
                        case 2: comps = 2; break;
                        case 3: case 5: comps = 3; break;
                        case 4: case 6: comps = 4; break;
                        default: continue;
                        }
                        uint32_t off = arr[0];
                        if (off + comps <= 0x10)
                        {
                            uint32_t* v = MapAt(key);
                            v[0] = off; v[1] = comps; v[2] = type;
                        }
                    }
                }
                cParser parser;
                uint32_t off = 0x10;
                uint32_t type = 0xffffffff;
                for (int i = 1; i < count; ++i)
                {
                    const char* arg = argv[i];
                    if (*arg == '-')
                    {
                        if (a.HasArgument(arg + 1))
                        {
                            uint32_t tmp = 0x10;
                            off = 0x10;
                            uint32_t h2 = FNV1_String8(arg + 1, 0x811c9dc5, 1);
                            if (MapLookup(h2, tmp, type, 0)) off = tmp;
                            continue;
                        }
                    }
                    if (off < 0x10)
                    {
                        switch (type)
                        {
                        case 0: params[off] = parser.ParseFloat(arg); break;
                        case 1: params[off] = parser.ParseBool(arg) ? 1.0f : 0.0f; break;
                        case 2: { Vec2 tmp; const Vec2* r = parser.ParseVector2(tmp, arg);
                                  float v[4] = { r->x, r->y, 0, 0 }; StoreParams(v, off, 2); break; }
                        case 3: { Vec3 tmp; const Vec3* r = parser.ParseVector3(tmp, arg);
                                  float v[4] = { r->x, r->y, r->z, 0 }; StoreParams(v, off, 3); break; }
                        case 4: { Vec4_s0082_f9a0 tmp; const Vec4_s0082_f9a0* r = parser.ParseRGBA(tmp, arg);
                                  float v[4] = { r->x, r->y, r->z, r->w }; StoreParams(v, off, 4); break; }
                        case 5: { Vec3 tmp; const Vec3* r = parser.ParseVector3(tmp, arg);
                                  float v[4] = { r->x, r->y, r->z, 0 }; StoreParams(v, off, 3); break; }
                        case 6: { Vec4_s0082_f9a0 tmp; const Vec4_s0082_f9a0* r = parser.ParseRGB(tmp, arg);
                                  float v[4] = { r->x, r->y, r->z, r->w }; StoreParams(v, off, 4); break; }
                        }
                    }
                }
            }
            if (list.p) list.p->Release();
        }
    }
    if (fs.e - fs.b) name.assign(fs.b, fs.e);
    if (name.e - name.b == 0)
    {
        const wchar_t* p = g_defaultMaterialName;
        while (*p) ++p;
        name.assign(g_defaultMaterialName, g_defaultMaterialName + (p - g_defaultMaterialName));
    }
    if (StrEqual(name, g_defaultMaterialName)) nameHash = 0;
    else nameHash = FNV1_String16(name.b, 0x811c9dc5, 1);
    }
    if ((((char*)fs.c - (char*)fs.b) & ~1) > 2 && fs.b && fs.b != fs.pool) operator_delete__(fs.b);
    if (s8.c - s8.b > 1 && s8.b) operator_delete__(s8.b);
    return true;
}
