// Slice s00e4c9e0 (gold0 slice 26).  Functions 0xe4c9e0 .. 0xe4d840.
// Cell-game layer/resource loading: app-data teardown, advected-map catalog loading,
// resource factory read/write, layer grid builders.  Optimised module with SSE:
// /O2 /MD /Gy /TP /arch:SSE.
#include "types.h"

static inline void** Vt(void* p) { return *(void***)p; }
static inline void** Vtp(int p) { return *(void***)p; }

// ---- operator new/delete (EA variants) ----
void* operator new(unsigned size, const char* name, int flags, int line, const char* file, int line2); // 0xf473a0
void  operator_delete__(void* p);                       // 0x00f47380
void* ZoneObject_operator_new(unsigned size, const char* name, int a, int b, int c, int d); // 0x00926020

// ---- external callees (not in this slice) ----
void  FUN_00e824d0();                                   // 0x00e824d0
int*  FUN_00e4c330();                                   // 0x00e4c330
void  FUN_00e4bb10();                                   // 0x00e4bb10
void  FUN_00e4b910(const wchar_t* s);                   // 0x00e4b910
void  FUN_00e82280();                                   // 0x00e82280
void  FUN_00e823a0(void* a, void* b);                   // 0x00e823a0
void* FUN_00e82420(void* a, void* b);                   // 0x00e82420
void* FUN_00e4cad0(const wchar_t* s, int n);            // 0x00e4cad0
bool  FUN_00e4b870();                                   // 0x00e4b870
void* FUN_00e4a9f0(void* s);                            // 0x00e4a9f0
void  FUN_00e4c130(void* p);                            // 0x00e4c130
void  FUN_00e4c440(void* s, void* p);                   // 0x00e4c440
void  FUN_00e4b470(void* s, void* p);                   // 0x00e4b470
void* FUN_00e4b6c0(void* s, void* p);                   // 0x00e4b6c0
int   FUN_008d61e0(void* s);                            // 0x008d61e0 (stdcall, ret 4)
unsigned EA_Hash_FNV1_String16(const void* s, unsigned basis, int a); // 0x00932f30
void  FUN_00e84e40(const char* fmt, ...);               // 0x00e84e40
void  FUN_00b720e0();                                   // 0x00b720e0
void  FUN_00e84940(int);                                // 0x00e84940
void  FUN_00e85a60(unsigned n, int a, void* b, int c, int d, int e); // 0x00e85a60
void  SP_SetCachingType(int a, void* b);                // 0x006ac040
void* SP_cSPMemPool_LockedAlloc(int a, int b, int c, int d, int e, int f); // 0x009289f0
struct cLightCtx { void Dtor(void* p); };               // 0x009276c0 (ecx=g_16c8b44)
void* EA_ResourceMan_GetManager();                      // 0x0067dcd0
void* SP_MessageServer();                               // 0x0067dcc0
void* SP_CheatManager();                                // 0x0067de20
void* SP_GetDataDir(const wchar_t* s);                  // 0x00688cb0
unsigned WStr_Format(wchar_t* out, const wchar_t* fmt, ...); // 0x0041e050
void  EA_ResourceMan_DatabaseDirectoryFiles_ctor(void* self, void* s, int z); // 0x008d7400

// ---- globals ----
extern void* g_pCellAppData;        // 0x016ad060
extern void* g_pCellCellData;       // 0x016ad1f0  (cell-data globals block)
extern char  g_layerCatalog[];      // 0x015a7584
extern char  g_15a758c[];           // 0x015a758c
extern char  g_15a774c[];           // 0x015a774c
extern int   g_16b39a4;             // 0x016b39a4
extern char  g_16b3998[];           // 0x016b3998
extern char  g_16b399c[];           // 0x016b399c
extern char  g_16b39a0[];           // 0x016b39a0 ResourceKey
extern void* g_lightCtx;            // 0x016c8b44 (cLocalLightInfo allocator/context pointer)

// vtable blobs
extern char vtbl_1482de8[], vtbl_13ebcdc[], vtbl_13eb938[], vtbl_1482d38[], vtbl_1482d24[];

// ---- small stubs ----
struct cCellAppData {                // object at g_pCellAppData
    char pad00[0x20];
    void* mp20;                     // +0x20
    char pad24[0x44 - 0x24];
    void** mpBegin44;               // +0x44
    void** mpEnd48;                 // +0x48
    char pad4c[0x0c];
    int   mStr28Node;               // (used by dtor path)
};

struct cCellDataObj {                // object at *g_pCellCellData
    char pad00[0x18];
    void* mp18;                     // +0x18
    void* mp1c;                     // +0x1c
};

struct cResourceMan {
    void* Load(void* key, void* p2, int p3, int p4, int p5);          // +0xc
    void* GetByKey(void* out, void* key, void* p3, int p4, int p5);   // vtable
};
struct cLayerRes {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int GetLayerType();                                       // +0xc
};

// =====================================================================
// @ 0x00e4c9e0
// =====================================================================
void FUN_00e4c9e0()
{
    FUN_00e824d0();
    cCellAppData* g = (cCellAppData*)g_pCellAppData;
    if (g->mp20) {
        void* o = g->mp20;
        (*(void(__thiscall**)(void*))((char*)Vt(o) + 0xc))(o);
        o = g->mp20;
        (*(void(__thiscall**)(void*))((char*)Vt(o) + 4))(o);
        ((cCellAppData*)g_pCellAppData)->mp20 = 0;
    }
    void* ms = SP_MessageServer();
    (*(void(__thiscall**)(void*, int*, int, int))((char*)Vt(ms) + 0x30))(ms, (int*)0x00e4c330, 0x4a4e97f, 0xffffd8f1);
    FUN_00e4bb10();
    void* rm = EA_ResourceMan_GetManager();
    (*(void(__thiscall**)(void*, int, void*, int))((char*)Vt(rm) + 0x44))(rm, 0, g_pCellAppData, 0);
    cCellAppData* g2 = (cCellAppData*)g_pCellAppData;
    void** it = g2->mpBegin44;
    while (it != g2->mpEnd48) {
        ((cLightCtx*)g_lightCtx)->Dtor(*(void**)it);
        ++it;
        g2 = (cCellAppData*)g_pCellAppData;
    }
    FUN_00b720e0();
    cCellAppData* g3 = (cCellAppData*)g_pCellAppData;
    if (g3) {
        void* v = g3->mpBegin44;
        if (v && *(int*)((char*)v - 4)) operator_delete__(v);
        FUN_00e84940(*(int*)((char*)g3 + 0x34));
        (*(void(__thiscall**)(void*))0x00c2e4e0)((char*)g3 + 4);
        operator_delete__(g3);
    }
}

// =====================================================================
// @ 0x00e4cad0
// =====================================================================
void* FUN_00e4cad0(const wchar_t* name, int line)
{
    (void)line;
    char* base = (char*)0x015a758c - 8;   // object at 0x15a7584
    void* a = (*(void*(__thiscall**)(void*))0x00b72160)(base);
    void* obj = (*(void*(__thiscall**)(void*, void*))0x00b72210)(base, a);
    unsigned h = EA_Hash_FNV1_String16(name, 0x811c9dc5, 1);
    *(unsigned*)((char*)obj + 4) = h;
    wchar_t buf1[6];
    buf1[0] = 0x67bac & 0xffff; buf1[1] = 0x67bac & 0xffff; buf1[2] = 0x67bae & 0xffff;
    void* dd = SP_GetDataDir(name);
    WStr_Format(buf1, L"%s%s", dd);
    wchar_t buf2[6];
    buf2[0] = 0x67bac & 0xffff; buf2[1] = 0x67bac & 0xffff; buf2[2] = 0x67bae & 0xffff;
    void* dd2 = SP_GetDataDir(name);
    WStr_Format(buf2, L"%s%sBinary/", dd2);
    if (FUN_00e4b870()) {
        void* v = FUN_00e4a9f0(buf2);
        *(void**)((char*)obj + 0xc) = v;
        FUN_00e4c130((void*)0);
        FUN_00e4c440(buf1, v);
        FUN_00e4b470(buf1, (void*)0);
    } else {
        *(void**)((char*)obj + 0xc) = 0;
    }
    *(void**)((char*)obj + 8) = FUN_00e4b6c0(buf1, *(void**)obj);
    return obj;
}

// =====================================================================
// @ 0x00e4cc10
// =====================================================================
void __stdcall FUN_00e4cc10(short* s)
{
    int v = ((int(__stdcall*)(void*))FUN_008d61e0)(s);
    if (v == -1) {
        if (*s == 0x2e) s += 1;
        EA_Hash_FNV1_String16(s, 0x811c9dc5, 1);
    }
}

// =====================================================================
// @ 0x00e4cc50  SP::LoadAdvectMap
// =====================================================================
void SP_LoadAdvectMap(void* key, void* p2)
{
    struct { void* k; unsigned h; unsigned z; } k1, k2;
    k2.z = 0; k2.h = 0x4805684; k1.k = key; k1.h = 0; k1.z = 0;
    (void)k1;
    void* out;
    void* rm = EA_ResourceMan_GetManager();
    bool ok = (*(bool(__thiscall**)(void*, void*, void*, int, int, int))((char*)Vt(rm) + 0xc))(rm, key, p2, 0, 0, 0);
    (void)ok; (void)out;
    {
        int outbuf[3];
        outbuf[0] = 0; outbuf[1] = 0x4805684; outbuf[2] = 0;
        int keyb[3]; keyb[0] = 0; keyb[1] = 0x4805684; keyb[2] = 0;
        (void)outbuf;
        char* rmgr = (char*)EA_ResourceMan_GetManager();
        char local[12]; *(void**)local = key; *(unsigned*)(local+4) = 0x4805684; *(unsigned*)(local+8) = 0;
        bool ok2 = (*(bool(__thiscall**)(void*, void*, void*, int, int, int))((char*)Vt(rmgr) + 0xc))(rmgr, local, p2, 0, 0, 0);
        if (!ok2) {
            FUN_00e84e40("invalid advection map (key:%X) using empty.advect instead", key);
            unsigned local2[3]; local2[0] = 0xc7ee8594; local2[1] = 0x4805684; local2[2] = 0;
            char* rmgr2 = (char*)EA_ResourceMan_GetManager();
            (*(bool(__thiscall**)(void*, unsigned*, void*, int, int, int))((char*)Vt(rmgr2) + 0xc))(rmgr2, local2, p2, 0, 0, 0);
        }
    }
}

// =====================================================================
// @ 0x00e4cce0
// =====================================================================
void* FUN_00e4cce0(int idx)
{
    return *(void**)(g_15a758c + (idx << 4));
}

// =====================================================================
// @ 0x00e4ccf0  SP::sIsLayerDataPacked
// =====================================================================
bool SP_sIsLayerDataPacked()
{
    void* rm = EA_ResourceMan_GetManager();
    if ((g_16b39a4 & 1) == 0) {
        g_16b39a4 |= 1;
        *(unsigned*)g_16b3998 = 0xc7ee8594;
        *(unsigned*)g_16b399c = 0x4805684;
        *(unsigned*)g_16b39a0 = 0;
    }
    void* o = (*(void*(__thiscall**)(void*, void*))((char*)Vt(rm) + 0x58))(rm, g_16b3998);
    int r = ((cLayerRes*)o)->GetLayerType();
    bool b = (r != 0x34728492);
    return b;
}

// =====================================================================
// @ 0x00e4cd50  SP::CellDataShutdownForApp
// =====================================================================
void SP_CellDataShutdownForApp()
{
    void* rm = EA_ResourceMan_GetManager();
    void* g = g_pCellCellData;
    (*(void(__thiscall**)(void*, int, void*, int))((char*)Vt(rm) + 0x44))(rm, 0, *(void**)((char*)g + 4), 0);
    void* cd = *(void**)g_pCellCellData;
    if (cd) {
        (*(void(__thiscall**)(void*))((char*)Vt(cd) + 0x1c))(cd);
        void* rm2 = EA_ResourceMan_GetManager();
        void* cd2 = *(void**)g_pCellCellData;
        (*(void(__thiscall**)(void*, int, void*, int))((char*)Vt(rm2) + 0x50))(rm2, 0, cd2, 100);
    }
    if (!SP_sIsLayerDataPacked()) {
        void* cm = SP_CheatManager();
        (*(void(__thiscall**)(void*, void*))((char*)Vt(cm) + 0x1c))(cm, *(void**)0x015a5dd4);
        void* cm2 = SP_CheatManager();
        (*(void(__thiscall**)(void*, void*))((char*)Vt(cm2) + 0x1c))(cm2, *(void**)0x015a5dd8);
    }
    operator_delete__(g_pCellCellData);
    g_pCellCellData = 0;
}

// =====================================================================
// @ 0x00e4cde0
// =====================================================================
void FUN_00e4cde0()
{
    FUN_00e4cad0(L"CellGame/", 0x96c);
    char* p = g_layerCatalog;
    do {
        *(void**)(p + 8) = FUN_00e82420(*(void**)p, *(void**)(p + 4));
        p += 0x10;
    } while ((int)p < (int)0x015a7754);
}

// =====================================================================
// @ 0x00e4ce20
// =====================================================================
void FUN_00e4ce20()
{
    FUN_00e4b910(L"CellGame/");
    FUN_00e82280();
}

// =====================================================================
// @ 0x00e4ce40
// =====================================================================
void FUN_00e4ce40(void* a)
{
    FUN_00e823a0(*(void**)g_15a758c, a);
}

// =====================================================================
// @ 0x00e4ce60
// =====================================================================
void FUN_00e4ce60(void* a)
{
    FUN_00e823a0(*(void**)g_15a774c, a);
}

// =====================================================================
// @ 0x00e4ce80
// =====================================================================
struct cLightObj { void* pad00[6]; void* mp18; void* FUN_00e4ce80(unsigned flags); };
void* cLightObj::FUN_00e4ce80(unsigned flags)
{
    *(void**)this = vtbl_1482de8;
    if (mp18) ((cLightCtx*)g_lightCtx)->Dtor(mp18);
    *(void**)this = vtbl_13eb938;
    if (flags & 1) operator_delete__(this);
    return this;
}

// =====================================================================
// @ 0x00e4ced0  SP::PreloadAdvectMap
// =====================================================================
void SP_PreloadAdvectMap(void* key)
{
    int k[3]; k[0] = 0; k[1] = 0; k[2] = 0;
    int local10 = 0;
    (void)local10;
    void* rm = EA_ResourceMan_GetManager();
    (*(void(__thiscall**)(void*, int*, int*, int*, int, int, int, int))((char*)Vt(rm) + 0x10))
        (rm, k, &local10, (int*)key, 0, 0, 0, 0);
    (void)key;
}

// =====================================================================
// @ 0x00e4cf80  SP::cCellFactoryBinary::ReadResource
// =====================================================================
struct cCellFactoryBinary {
    bool ReadResource(void* stream, void* p3, void* p4, void* p5);      // 0x00e4cf80
    unsigned char ReadResourceFromStream(void* s, void* a, void* b);     // 0x00e4d000
};
bool cCellFactoryBinary::ReadResource(void* stream, void* p3, void* p4, void* p5)
{
    void* vt = *(void**)this;
    void* a = (*(void*(__thiscall**)(void*, void*))((char*)Vt(stream) + 0x10))(stream, p5);
    void* b = (*(void*(__thiscall**)(void*, void*, void*))((char*)Vt(stream) + 0x18))(stream, p3, a);
    char r = (*(char(__thiscall**)(void*, void*))((char*)vt + 0x34))(this, b);
    (void)p4;
    return r != 0;
}

// =====================================================================
// @ 0x00e4cfc0  SP::cCellFactoryBinary::GetSupportedTypes
// =====================================================================
int __stdcall CellFactory_GetSupportedTypes(unsigned* out, unsigned n)
{
    if (out) {
        if (n > 0) {
            out[0] = 0x5c74d18b;
            if (n > 1) { out[1] = 0x4805684; return 2; }
            return 1;
        }
        return 0;
    }
    return 2;
}

// =====================================================================
// @ 0x00e4d000  SP::cCellFactoryBinary::ReadResourceFromStream
// =====================================================================
unsigned char cCellFactoryBinary::ReadResourceFromStream(void* self, void* s, void* k)
{
    unsigned char ok = 0;
    void* obj;
    if (s) obj = (*(void*(__thiscall**)(void*, int))((char*)Vt(s) + 0xc))(s, 0x355d6f5);
    else obj = 0;
    unsigned n = (*(unsigned(__thiscall**)(void*))((char*)Vt(self) + 0x1c))(self);
    cCellDataObj* c = (cCellDataObj*)obj;
    c->mp18 = 0; c->mp1c = 0;   // overwritten below (keys copied in)
    *(int*)((char*)obj + 8) = *(int*)k;
    *(int*)((char*)obj + 0xc) = *((int*)k + 1);
    *(int*)((char*)obj + 0x10) = *((int*)k + 2);
    if (c->mp18) ((cLightCtx*)g_lightCtx)->Dtor(c->mp18);
    void* mem = SP_cSPMemPool_LockedAlloc(n, 0, 0, 0, 0, 0);
    c->mp18 = mem;
    if (mem) {
        unsigned got = (*(unsigned(__thiscall**)(void*, void*, unsigned))((char*)Vt(self) + 0x30))(self, mem, n);
        if (got == n) {
            c->mp1c = (void*)got;
            ok = 1;
        } else {
            ((cLightCtx*)g_lightCtx)->Dtor(c->mp18);
            c->mp18 = 0;
        }
    }
    c->mp1c = (void*)(((int)c->mp18 != 0) ? (int)n : 0);
    SP_SetCachingType(7, c);
    return ok;
}

// =====================================================================
// @ 0x00e4d0d0  EA::ResourceMan::FactoryBinary::WriteResource
// =====================================================================
unsigned FactoryBinary_WriteResource(void* self, void* a, void* s)
{
    void* obj = (*(void*(__thiscall**)(void*, void*))((char*)Vt(s) + 0x18))(s, a);
    unsigned r = 0;
    if (obj) {
        void* kv = a ? (*(void*(__thiscall**)(void*, int))((char*)Vt(a) + 0xc))(a, 0x355d6f5) : 0;
        if (*(int*)((char*)kv + 0x18)) {
            r = (*(unsigned(__thiscall**)(void*, void*, void*))((char*)Vt(obj) + 0x38))(obj, *(void**)((char*)kv + 0x18), *(void**)((char*)kv + 0x1c));
        }
    }
    return r & 0xffffff00u;
}

// =====================================================================
// @ 0x00e4d120
// =====================================================================
struct cProcObj { bool FUN_00e4d120(void* p2, void** out, int p4, int p5); };
bool cProcObj::FUN_00e4d120(void* p2, void** out, int p4, int p5)
{
    bool ok = false;
    if (out) {
        char* obj = (char*)operator new(0x20, "Simulator", 0, 0, 0, 0);
        if (!obj) obj = 0;
        else {
            *(void**)obj = vtbl_13ebcdc;
            *(int*)(obj + 4) = 0;
            *(int*)(obj + 8) = 0;
            *(int*)(obj + 0xc) = 0;
            *(int*)(obj + 0x10) = 0;
            *(int*)(obj + 0x14) = 0;
            *(void**)obj = vtbl_1482de8;
            *(int*)(obj + 0x18) = 0;
            *(int*)(obj + 0x1c) = 0;
        }
        *out = obj;
        if (obj) {
            (*(void(__thiscall**)(void*))((char*)Vt(obj) + 0))(obj);
            if (p2) {
                char c = (*(char(__thiscall**)(void*, void*, void*, int, int))((char*)Vt(this) + 0x24))(this, p2, *out, p4, p5);
                if (!c) {
                    if (*out) (*(void(__thiscall**)(void*, int))((char*)Vt(*out) + 8))(*out, 1);
                    return false;
                }
            }
            ok = true;
        }
    }
    return ok;
}

// =====================================================================
// @ 0x00e4d1d0
// =====================================================================
void FUN_00e4d1d0(float* in, float* out)
{
    float f1 = in[3], f5 = in[4], f6 = in[5], f2 = in[2], f4 = in[0], f3 = in[1];
    out[0] = in[0]; out[1] = in[1]; out[2] = in[2];
    f4 = (f1 + f4) * 0.5f;
    f5 = (f5 + f3) * 0.5f;
    out[6] = f4;
    f6 = (f6 + f2) * 0.5f;
    out[3] = f4; out[4] = f5; out[5] = f6;
    out[7] = in[1]; out[8] = 0.0f;
    f1 = in[3];
    out[10] = f5; out[9] = f1; out[0xb] = 0.0f;
    f1 = in[0];
    out[0xd] = f5; out[0xc] = f1; out[0xe] = 0.0f; out[0xf] = f4;
    f1 = in[4];
    out[0x12] = f4; out[0x10] = f1; out[0x13] = f5; out[0x14] = f6; out[0x11] = 0.0f;
    out[0x15] = in[3]; out[0x16] = in[4]; out[0x17] = in[5];
}

// =====================================================================
// @ 0x00e4d2b0
// =====================================================================
void FUN_00e4d2b0(int* cursor, int* parent, void* geo, void* factory, float* box, int depth)
{
    float local[24];
    local[0] = 3.402823466e38f; local[1] = 3.402823466e38f; local[2] = -3.402823466e38f;
    local[3] = -3.402823466e38f; local[4] = -3.402823466e38f; local[5] = 3.402823466e38f;
    local[6] = 3.402823466e38f; local[7] = 3.402823466e38f; local[8] = -3.402823466e38f;
    local[9] = -3.402823466e38f; local[10] = -3.402823466e38f; local[11] = 3.402823466e38f;
    local[12] = 3.402823466e38f; local[13] = 3.402823466e38f; local[14] = -3.402823466e38f;
    local[15] = -3.402823466e38f; local[16] = -3.402823466e38f; local[17] = 3.402823466e38f;
    local[18] = 3.402823466e38f; local[19] = 3.402823466e38f; local[20] = -3.402823466e38f;
    local[21] = -3.402823466e38f; local[22] = -3.402823466e38f;
    FUN_00e4d1d0(box, local);
    float* p = local;
    int n = 4;
    int* out = parent;
    do {
        ++out;
        if (geo == 0) {
        emit:
            if (depth == 3) { *out = 0; goto next; }
            {
                int* node = (int*)*cursor;
                *cursor = (int)node + 0x2c;
                *out = (int)node;
                *node = (int)parent;
                node[8] = *(int*)(p + 2);
                node[9] = *(int*)(p + 3);
                node[10] = *(int*)(p + 4);
                node[5] = *(int*)(p - 1);
                node[6] = *(int*)p;
                node[7] = *(int*)(p + 1);
                FUN_00e4d2b0(cursor, node, geo, factory, p - 1, depth + 1);
            }
        } else {
            float* b = (float*)(*(void*(__thiscall**)(void*, void*))((char*)Vt(factory) + 0x60))(factory, geo);
            if (b[0] <= p[2] && p[-1] <= b[3] && b[1] <= p[3] &&
                *p <= b[4] && b[2] <= p[4] && p[1] <= b[5])
                goto emit;
            *out = 0;
        }
    next:
        p += 6;
        --n;
    } while (n != 0);
}

// =====================================================================
// @ 0x00e4d550
// =====================================================================
unsigned FUN_00e4d550(void* self, void* geo, void* factory)
{
    float box[6];
    box[2] = -1.0f; box[3] = -1.0f; box[0] = 1.0f; box[1] = 1.0f; box[4] = 0.0f; box[5] = 0.0f;
    *(float*)((char*)self + 0x20) = 1.0f;
    *(float*)((char*)self + 0x24) = -1.0f; *(float*)((char*)self + 0x28) = 0.0f;
    *(float*)((char*)self + 0x14) = -1.0f; *(float*)((char*)self + 0x18) = 1.0f;
    *(float*)((char*)self + 0x1c) = 0.0f;
    *(int*)self = 0;
    int* cursor = (int*)((char*)self + 0xb * 4);
    float* boxp = box;
    FUN_00e4d2b0(cursor, (int*)self, geo, factory, boxp, 0);
    (void)boxp;
    return (unsigned)((char*)cursor - (char*)self) / 0x2c;
}

// =====================================================================
// @ 0x00e4d600
// =====================================================================
void FUN_00e4d600(int* node, float** out, int depth, int maxDepth)
{
    if (depth == maxDepth) {
        float* p = *out;
        p[0] = (*(float*)((char*)node + 0x14) + *(float*)((char*)node + 0x20)) * 0.5f;
        p[1] = (*(float*)((char*)node + 0x24) + *(float*)((char*)node + 0x18)) * 0.5f;
        p[2] = (*(float*)((char*)node + 0x28) + *(float*)((char*)node + 0x1c)) * 0.5f;
        *out = p + 3;
        return;
    }
    int n = 4;
    do {
        ++node;
        if (*node) FUN_00e4d600((int*)*node, out, depth, maxDepth + 1);
        --n;
    } while (n != 0);
}

// =====================================================================
// @ 0x00e4d6c0
// =====================================================================
void FUN_00e4d6c0(void* a, void* b, int base)
{
    int* p = (int*)base;
    FUN_00e4d550((char*)base + 0x1168, a, b);
    int local8;
    int i = 0;
    int* grid = (int*)((char*)base + 0x28);
    int* cnt = (int*)((char*)base + 0x18);
    int* extra = (int*)((char*)base + 0xc28);
    int* dst = (int*)((char*)base + 0x1138);
    do {
        (void)p;
        local8 = (int)grid;
        FUN_00e4d600(grid, (float**)&local8, i, 0);
        unsigned n = (unsigned)(local8 - (int)grid) / 0xc;
        *cnt = n;
        FUN_00e85a60(n, (int)grid, (void*)0x01482c20, (int)grid, (int)dst, (int)extra);
        dst = (int*)((char*)dst + 0xc);
        ++i;
        ++cnt;
        extra = (int*)((char*)extra + 0x144);
        grid = (int*)((char*)grid + 0x300);
    } while (i < 4);
}

// =====================================================================
// @ 0x00e4d840  SP::LayerLoaderInit
// =====================================================================
void SP_LayerLoaderInit()
{
    wchar_t buf[6];
    buf[0] = 0x67bac & 0xffff; buf[1] = 0x67bac & 0xffff; buf[2] = 0x67bae & 0xffff;
    void* dd = SP_GetDataDir(L"CellGame/Layers/");
    WStr_Format(buf, L"%s%s", dd);
    void* obj = ZoneObject_operator_new(0x168, "Simulator/Cell/Data", 0, 0, 0, 0);
    if (!obj) obj = 0;
    else {
        EA_ResourceMan_DatabaseDirectoryFiles_ctor(obj, buf, 0);
        *(void**)obj = vtbl_1482d38;
        *(void**)((char*)obj + 4) = vtbl_1482d24;
    }
    *(void**)g_pCellCellData = obj;
    void* cd = *(void**)g_pCellCellData;
    (*(void(__thiscall**)(void*))((char*)Vt(cd) + 4))(cd);
    void* rm = EA_ResourceMan_GetManager();
    (*(void(__thiscall**)(void*, int, void*, int))((char*)Vt(rm) + 0x50))(rm, 1, *(void**)g_pCellCellData, 100);
    void* cd2 = *(void**)g_pCellCellData;
    (*(void(__thiscall**)(void*, int, int, int))((char*)Vt(cd2) + 0x18))(cd2, 3, 4, 0);
}
