// Slice s0082ec70 -- UTFWin/SPUI 2D shader system: material winproc, shader proxies,
// and the 2D-system singleton/map that owns them.
// Region flags /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"
#include <new>

// ---------------------------------------------------------------- masked globals
extern void     *g_d3dDevice;                 // 0x16f89d0
extern uint8_t   g_bRender3D;                 // 0x164e90c
extern uint8_t   g_bShaderInited;             // 0x164e90d
extern void     *g_pShader2D;                 // 0x164e910
extern void     *g_pShaderProxy;              // 0x164ea4c
extern void     *g_pAllocCore;                // 0x15474a4
extern void     *g_pField154724c;             // 0x154724c
extern void     *g_pField164e8fc;             // 0x164e8fc
extern wchar_t   g_defaultMat[];              // 0x1547250
extern char      g_allocTag;                  // 0x13f6b3c
extern char      g_allocFile[];               // 0x13ebb38
extern char      g_fixedAlloc[];              // 0x164e990

// vtable / empty-string data addresses (address-of only)
extern char      g_vtblBase13fa72c;           // 0x13fa72c
extern char      g_vtblProxy141a668;          // 0x141a668
extern char      g_vtblMatWinProc;            // 0x141a5e8
extern char      g_vtblMatWinProcSec;         // 0x141a5d0
extern char      g_vtblEditorResource;        // 0x13eb938
extern wchar_t   g_emptyW[];                  // 0x1667bac

// ---------------------------------------------------------------- callee stubs
extern "C" void  __cdecl EA_Free(void *);                                        // 0xf47380
extern "C" void *__cdecl EA_Alloc(uint32_t, const void *, int, int, const char *, int); // 0xf473a0
extern "C" void *__cdecl msvc_memcpy(void *, const void *, uint32_t);            // 0x11e0744
extern "C" void *__cdecl msvc_memmove(void *, const void *, uint32_t);           // 0x13cc480

extern "C" bool  __cdecl FUN_0082e4f0(void *, void *);        // 0x82e4f0
extern "C" void  __cdecl SUB_00951d10(void *);                // 0x951d10
extern "C" int   __cdecl FUN_0067de10();                      // 0x67de10
extern "C" int   __cdecl FUN_0067dd60();                      // 0x67dd60
extern "C" bool  __cdecl SUB_009568c0(int);                   // 0x9568c0
extern "C" void  __cdecl SUB_00956a30();                      // 0x956a30
extern "C" void  __cdecl SUB_007c3c10();                      // 0x7c3c10
extern "C" void *__cdecl FUN_00e23ee0(void *, void *, void *, uint8_t); // 0xe23ee0
extern "C" long  __cdecl _InterlockedExchangeAdd(volatile long *, long);
extern "C" void  __cdecl _ReadWriteBarrier(void);

// thiscall helpers are exposed as members of a dummy class so the compiler emits ecx=this.
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

// ---------------------------------------------------------------- class stubs
struct SPUIShader2D;
struct cSPUIShaderProxy;

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
    int32_t   count;            // +0x004
    int32_t   field8;           // +0x008
    uint32_t  flagsC;           // +0x00c
    void     *field10;          // +0x010
    uint32_t  arr14[0x40];      // +0x014
    char      ent114[0x500];    // +0x114  (64 x 0x14)
    uint32_t  countB;           // +0x614
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

struct cSPUIShaderProxy {
    void     *vptr;             // +0x000
    char      map[0x118];       // +0x004
    char      name[0x54];       // +0x11c
    uint32_t  materialID;       // +0x170
    int32_t   layerId;          // +0x174
    int32_t   refCount;         // +0x178
    int32_t   field17c;         // +0x17c
    void     *textures[2];      // +0x180
    float     parameters[16];   // +0x188

    __declspec(noinline) cSPUIShaderProxy *Construct(); // 0x0082f410 (ctor body)
    ~cSPUIShaderProxy();                           // 0x0082f500
    bool GetParam(uint32_t, uint32_t *, uint32_t *, uint32_t *); // 0x0082f5c0
};

struct cSPUIMaterialWinProc {
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

// ---------------------------------------------------------------- 0x0082f0b0
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

// ---------------------------------------------------------------- 0x0082f110
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

// ---------------------------------------------------------------- 0x0082f020
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

// ---------------------------------------------------------------- 0x0082ec70
struct QueueItem {
    void    *pData;          // +0x00
    uint8_t  b4, b5, b6, b7;// +0x04
    float    f2, f3, f4, f5; // +0x08,+0x0c,+0x10,+0x14
    char     pad18[0x10];    // +0x18
    float    f10, f11;       // +0x28,+0x2c
    uint8_t  pad30[4];       // +0x30
    float    f13, f14;       // +0x34,+0x38
};
struct Range { void *begin; void *end; };
struct IterData {
    int32_t  id;     // +0x00
    int32_t  acc;    // +0x04
    uint32_t u2c;    // +0x08
    int32_t  u28;    // +0x0c
    void    *p24;    // +0x10
};

void SPUIShader2D::Process(void *itemv, uint32_t arg)
{
    QueueItem *item = (QueueItem *)itemv;
    if (!flag0)
        return;

    cSPUIShaderProxy *px = (cSPUIShaderProxy *)proxy;
    int saved = px->refCount;
    int r = ((H *)this)->AddBoundingBox(saved);
    if (saved != ((H *)r)->FUN_00a1ad10())
        return;

    if (0xf < (int)countB)
        ((H *)this)->FUN_0082e890();

    if (g_bRender3D) {
        uint32_t q[4];
        q[0] = (uint32_t)(int)item->f2;
        q[1] = (uint32_t)(int)item->f3;
        q[2] = (uint32_t)(int)item->f4;
        q[3] = (uint32_t)(int)item->f5;
        if (FUN_0082e4f0((char *)this + 0xc18, q)) {
            ((H *)this)->FUN_0082e890();
            *(uint32_t *)((char *)this + 0xc18) = q[0];
            *(uint32_t *)((char *)this + 0xc1c) = q[1];
            *(uint32_t *)((char *)this + 0xc20) = q[2];
            *(uint32_t *)((char *)this + 0xc24) = q[3];
            void *dev = g_d3dDevice;
            void **vt = *(void ***)dev;
            ((void (__stdcall *)(void *, uint32_t *))vt[0x12c / 4])(dev, q);
        }
    }

    Range range;
    ((H *)&range)->FUN_00951dc0((void *)arg);
    bool changed = false;
    if (range.begin != range.end) {
        IterData it;
        do {
            if (!((H *)&range)->FUN_009528d0(&it, (uint8_t)(count != 0))) {
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
                float *src = (float *)item->pData;
                for (int i = 0; i < 0x10; ++i)
                    dst[4 + i] = src[i];
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

// ---------------------------------------------------------------- 0x0082f410
cSPUIShaderProxy *cSPUIShaderProxy::Construct()
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

// ---------------------------------------------------------------- 0x0082f500
cSPUIShaderProxy::~cSPUIShaderProxy()
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

// ---------------------------------------------------------------- 0x0082f5c0
bool cSPUIShaderProxy::GetParam(uint32_t key, uint32_t *out4, uint32_t *outc, uint32_t *out8)
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

// ---------------------------------------------------------------- 0x0082f170
void u32vector::insert(uint32_t *pos, const uint32_t &val)
{
    uint32_t *end = mpEnd;
    if (end != mpCap) {
        const uint32_t *v = &val;
        if (pos >= mpBegin && pos < end)
            v = (const uint32_t *)((char *)pos + 4);
        if (end)
            *end = end[-1];
        uint32_t n = (uint32_t)((char *)(end - 1) - (char *)pos);
        msvc_memmove((char *)end - ((n >> 2) * 4), pos, n);
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
        int prefix = (int)((char *)&val - (char *)mpBegin);
        uint32_t *p = (uint32_t *)msvc_memcpy(nbuf, mpBegin, (uint32_t)prefix);
        p = (uint32_t *)((char *)p + (size_t)(prefix >> 2) * 4);
        if (p)
            *p = val;
        int suffix = (int)((char *)mpEnd - (char *)&val);
        p = (uint32_t *)msvc_memcpy((char *)p + 4, &val, (uint32_t)suffix);
        uint32_t *newend = (uint32_t *)((char *)p + (size_t)(suffix >> 2) * 4);
        if (mpBegin && mpBegin != mpPool)
            EA_Free(mpBegin);
        mpBegin = nbuf;
        mpEnd   = newend;
        mpCap   = (uint32_t *)((char *)nbuf + newcap * 4);
    }
}

// ---------------------------------------------------------------- 0x0082f280
void Vec4vector::insert(Vec4 *pos, const Vec4 &val)
{
    Vec4 *end = mpEnd;
    if (end != mpCap) {
        const Vec4 *v = &val;
        if (pos >= mpBegin && pos < end)
            v = pos + 1;
        if (end)
            *end = end[-1];
        for (Vec4 *p = end - 1; p != pos; --p)
            *p = p[-1];
        *pos = *v;
        mpEnd = end + 1;
        return;
    }

    size_t nelem = (size_t)(end - mpBegin);
    size_t newcap;
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
    nbuf = (Vec4 *)EA_Alloc((uint32_t)(newcap * 0x10), &g_allocTag, 0, 0, g_allocFile, 0xd1);
haveBuffer:
    {
        int prefix = (int)((char *)&val - (char *)mpBegin);
        char *p = (char *)msvc_memcpy(nbuf, mpBegin, (uint32_t)prefix);
        p += prefix;
        if (p)
            *(Vec4 *)p = val;
        int suffix = (int)((char *)mpEnd - (char *)&val);
        p = (char *)msvc_memcpy(p + 0x10, &val, (uint32_t)suffix);
        Vec4 *newend = (Vec4 *)(p + suffix);
        if (mpBegin && mpBegin != mpPool)
            EA_Free(mpBegin);
        mpBegin = nbuf;
        mpEnd   = newend;
        mpCap   = (Vec4 *)((char *)nbuf + newcap * 0x10);
    }
}

// ---------------------------------------------------------------- 0x0082f3a0
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

// ---------------------------------------------------------------- 0x0082f630
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
        node = ((cSPUIShaderProxy *)node)->Construct();
    }
    uint32_t ecx = *(uint32_t *)((char *)node + 0x178);
    if (ecx <= 0xe)
        ++g_layerVec.mpBegin[ecx];
    return node;
}

// ---------------------------------------------------------------- 0x0082f6e0
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

// ---------------------------------------------------------------- 0x0082f760
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

// ---------------------------------------------------------------- 0x0082f8a0
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

// ---------------------------------------------------------------- 0x0082f930
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
