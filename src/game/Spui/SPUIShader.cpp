// src/game/Spui/SPUIShader.cpp -- migrated from slice(s) s0082ec70, s0082dc00 by tools/migrate/rewrite.py
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
extern int* sLayerRCs;         // 0x154744c : pointer to layer reference counts
extern void* g_appProps;       // 0x15fd918
extern char g_layerFlag0d;     // 0x164e90d
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
void DestroyLayerProc(LayerWinProc* p);
// ---- items of slice s0082dc00 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern void* g_layerPool;      // 0x164e910

// ---- items of slice s0082ec70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void     *g_pShaderProxy;              // 0x164ea4c
extern void     *g_pAllocCore;                // 0x15474a4
extern wchar_t   g_defaultMat[];              // 0x1547250
extern char      g_vtblProxy141a668;          // 0x141a668
extern char      g_vtblEditorResource;        // 0x13eb938
extern "C" void  __cdecl EA_Free(void *);                                        // 0xf47380
extern "C" void  __cdecl SUB_007c3c10();                      // 0x7c3c10
extern "C" void *__cdecl FUN_00e23ee0(void *, void *, void *, uint8_t); // 0xe23ee0
extern "C" long  __cdecl _InterlockedExchangeAdd(volatile long *, long);
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
struct cSPUIShaderProxy_s0082_ec70;
struct u32vector {
    uint32_t *mpBegin;   // +0x00
    uint32_t *mpEnd;     // +0x04
    uint32_t *mpCap;     // +0x08
    uint32_t *mpUnused;  // +0x0c
    uint32_t *mpPool;    // +0x10
    void insert(uint32_t *pos, const uint32_t &val);  // 0x0082f170
};
extern u32vector g_layerVec;   // 0x154744c
struct cSPUIShaderProxy_s0082_ec70 {
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
cSPUIShaderProxy_s0082_ec70::~cSPUIShaderProxy_s0082_ec70()
{
    char *t = (char *)this;
    for (int i = 1; i >= 0; --i) {
        void *p = *(void **)(t + 0x180 + i * 4);
        if (p) {
            volatile long *rc8 = (volatile long *)((char *)p + 8);
            _InterlockedExchangeAdd(rc8, -1);
            volatile long *rc0 = (volatile long *)p;
            long v = _InterlockedExchangeAdd(rc0, 0);
            if (v >= 1)
                _InterlockedExchangeAdd(rc0, 0);
            else
                _InterlockedExchangeAdd(rc0, 1);
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

// @ 0x0082e6b0
void LayerPoolTick()
{
  // g_layerPool->Tick(...) (single-arg method)
}

// @ 0x0082e6c0
void LayerProcRelease(LayerWinProc* p)
{
  if ((unsigned)p->mLayer < 0xf) --sLayerRCs[p->mLayer];
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
    if (it == end || key < it[0] || it == it + 4)
        it = end;
    if (it == end)
        return false;
    if (out4) *out4 = it[1];
    if (outc) *outc = it[2];
    if (out8) *out8 = it[3];
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
