// slice s00776730: shader-profile / model-preview helpers.
// cShaderPreviewA (ctor 0x776730 etc.) and cShaderPreviewB (ctor 0x776920 etc.) share a base
// (refcounted object + message listener sub-object, ShConst block, texture hash/vector).
#include "types.h"
#include <new>
#include <intrin.h>

// @ 0x007776c0  SP::VSProfileFromVersion
extern char g_vsProfile[];   // 0x01539eb8 ("vs_x_x")
char* VSProfileFromVersion(unsigned int version) {
    int lo = (int)(version & 0xff);
    g_vsProfile[3] = (char)(version >> 8) + '0';
    char c = (char)lo;
    if (lo < 10)
        c = c + '0';
    g_vsProfile[5] = c;
    return g_vsProfile;
}

// ---------------------------------------------------------------------------
// Supporting declarations
// ---------------------------------------------------------------------------
struct Matrix3 { float m[9]; void Assign(const Matrix3* src); };

// Transform used for the viewer's scale modifier / camera transform.
struct Xform {
    uint16_t a, b;
    float    pos[3];
    float    one;
    Matrix3  m;
    void AccumulateScaled(const uint32_t* flags);   // 0x40cd80
};
struct Transform : Xform {
    Transform();   // 0x409930
    void Init();   // 0x5aa530
};

extern "C" float __cdecl VectorLength(const float* v);         // 0x40ae50

struct ResKey { uint32_t a, b; };
struct cTextureInstance { void* tex; uint32_t pad; volatile long refCount; };
struct TexPtr {
    cTextureInstance* p;
    TexPtr() : p(0) {}
    TexPtr(const TexPtr& o) : p(o.p) { if (p) _InterlockedExchangeAdd(&p->refCount, 1); }
    ~TexPtr() {
        if (p) {
            _InterlockedExchangeAdd(&p->refCount, -1);
            long n = _InterlockedExchangeAdd(&p->refCount, 0);
            if (n < 1) _InterlockedExchangeAdd(&p->refCount, 1);
            else       _InterlockedExchangeAdd(&p->refCount, 0);
        }
    }
    void Assign(void* res);   // 0x576650 GetImageResource
};
struct TexPtrVec {
    TexPtr* mpBegin; TexPtr* mpEnd; TexPtr* mpCap;
    void DoInsertValue(TexPtr* pos, const TexPtr* v);   // 0x425a80
    void DestroyRange(TexPtr* first, TexPtr* last);     // 0x70f520
};
extern "C" TexPtr* __cdecl copy_intrusive(TexPtr* first, TexPtr* last, TexPtr* dest);   // 0x6f43e0
extern "C" void* __cdecl eastl_move_thunk(void* dst, const void* src, uint32_t n);      // 0x11e0744

struct TexHash {                       // 0x20 bytes, at +0x140
    uint32_t pad0;
    void*    mpBuckets;
    uint32_t mnBuckets;
    uint32_t mnCount;
    float    mfLoad;
    float    mfGrow;
    uint32_t mnRehash;
    uint32_t pad1;
    int* Find(const ResKey* key);      // 0x6f6630 operator[]
};

struct CompiledState {
    void Dispatch();   // 0x11ee580
};
struct ActiveState {
    static void SetTexture(int slot, void* tex);   // 0x11f1280
};
extern uint32_t g_rasterDelta;          // 0x16f8b00
extern "C" void __cdecl FUN_00761f90(CompiledState* cs, const void* vec, uint32_t flags);

struct ShConst {
    char data[0x100];
    ShConst();                                                  // 0x77d170
    void SetIndexed(int idx, float a, float b, float c, float d);  // 0x77ca20
};

struct cViewer {
    cViewer();    // 0x7c3f70
    ~cViewer();   // 0x7c4000
    void Copy(uint32_t v, int a, int b);   // 0x7c50b0
    void GetXform(Xform* out);             // 0x7c40f0
    void SetXform(const Xform* in);        // 0x7c4d00
    bool Update();                         // 0x7c4fd0
    void Finish();                         // 0x7c3c10
    void Init(int a);                      // 0x7c4dd0
    void Cleanup();                        // 0x7c3ba0
};

struct cImageInfo { uint32_t pad[3]; uint16_t width; uint16_t height; };
struct cImageRes {
    uint32_t pad; uint32_t flags;
    cImageInfo* GetInfo();   // 0x46f260
};
struct ImgPtr {
    cImageRes* p;
    void Assign(void* res);   // 0x576650
};
struct ImgRef {
    void* p;
    ImgRef() : p(0) {}
    ~ImgRef();   // 0x576620
};
struct SlotEntry { uint32_t pad; CompiledState* cs; };
struct IImageSource {
    virtual void i0(); virtual void i1(); virtual void i2(); virtual void i3();
    virtual void i4(); virtual void i5(); virtual void i6(); virtual void i7();
    virtual void* Lookup(uint32_t k0, uint32_t k1, int flags);   // +0x20
};
extern "C" IImageSource* __cdecl GetImageSource();                // 0x67dd60

// Resource-ish interface with the two virtuals used here.
struct IResSource {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual bool IsReady();                 // slot 15 (+0x3c)
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
    virtual void* GetDefaultTexture();      // slot 34 (+0x88)
};

struct IMessageServer {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual void AddListener(void* listener, uint32_t msgId);                       // +0x20
    virtual void m9(); virtual void m10();
    virtual void RemoveListener(void* listener, uint32_t msgId, uint32_t extra);    // +0x2c
};
struct IMaterialManager {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual void m8(); virtual void m9(); virtual void m10();
    virtual void Register(int id, const void* desc, void* data);                    // +0x2c
};
extern "C" IMessageServer*   __cdecl GetMessageServer();      // 0x67dcc0
extern "C" IMaterialManager* __cdecl GetMaterialManager();    // 0x67dd70
extern "C" IResSource*       __cdecl GetResSourceA();         // 0x67dda0
extern "C" IResSource*       __cdecl GetResSourceB();         // 0x67dd40
extern "C" void*             __cdecl operator_new(uint32_t sz, const char* name, int, int, int, int);   // 0xf473a0
extern "C" void              __cdecl operator_delete__(void* p);   // 0xf47380
extern char g_matDesc[];                 // 0x1631058
extern Matrix3 g_identityB;              // 0x1630f38
extern float g_xfInit[3];                // 0x1630df8

struct cRefObjBase {
    virtual ~cRefObjBase() {}
    int refCount;
    cRefObjBase() : refCount(0) {}
};
struct cListenerBase { virtual ~cListenerBase() {} virtual void l0(); };

struct SlotVec {                 // fixed vector header at +0x10c
    SlotEntry** mpBegin; SlotEntry** mpEnd; SlotEntry** mpCap;
    void Init(int n);            // 0x758ee0
};

extern float g_vec4[4];                   // 0x1539bc8
extern float g_one;                       // 0x1485720 (1.0f)
extern float g_two;                       // 0x1470f1c (2.0f)
extern float g_vec3[3];                   // 0x1630eb8
extern Matrix3 g_identity3;               // 0x1630ff4
extern char g_emptyBuckets[];             // 0x154df28

struct AGap { float vec[4]; uint32_t key[2]; uint16_t mode; uint8_t has; uint8_t flagB; cViewer* viewer; };
struct BGap { uint32_t key[2]; uint16_t mode; uint16_t pad; float vec[4]; uint8_t flagA; uint8_t flagB; uint16_t pad2; };

struct cShaderBase : cRefObjBase, cListenerBase {
    ShConst  sh;                          // +0x0c
    SlotVec  slots;                       // +0x10c
    uint32_t pad118[2];
    union { AGap a; BGap b; } g;          // +0x120
    TexHash  hash;                        // +0x140
    TexPtrVec texVec;                     // +0x160

    cShaderBase() {
        slots.mpBegin = 0; slots.mpEnd = 0; slots.mpCap = 0;
        hash.mpBuckets = g_emptyBuckets; hash.mnBuckets = 1; hash.mnCount = 0;
        hash.mfLoad = g_one; hash.mfGrow = g_two; hash.mnRehash = 0;
        texVec.mpBegin = 0; texVec.mpEnd = 0; texVec.mpCap = 0;
    }
    bool LoadTexture(ResKey key);         // 0x777290
    bool LoadImg(uint32_t k0, uint32_t k1, void** out);   // 0x6f44c0
    void BaseInit();                      // 0x67dd50
    void ClearTexVec() {
        TexPtr* b = texVec.mpBegin; TexPtr* e = texVec.mpEnd;
        TexPtr* r = copy_intrusive(e, e, b);
        texVec.DestroyRange(r, texVec.mpEnd);
        texVec.mpEnd += -(e - b);
    }
    void ClearSlotVec() {
        SlotEntry** b = slots.mpBegin; SlotEntry** e = slots.mpEnd;
        eastl_move_thunk(b, e, (uint32_t)((char*)e - (char*)e));
        slots.mpEnd += -(e - b);
    }
};

struct cShaderPreviewA : cShaderBase {
    uint32_t pad16c[2];
    ImgPtr   imgRes;                      // +0x174
    uint16_t scaleFlags;                  // +0x178 (low flag bits tested with 6)
    uint16_t pad17a;
    float    v17c[3];
    float    scale;                       // +0x188
    Matrix3  mat;                         // +0x18c
    IResSource* res1b0;
    IResSource* res1b4;
    float    f1b8;
    int      mode1bc;
    float    f1c0, f1c4;

    cShaderPreviewA();
    void  Draw(int unused, uint32_t* pViewerArg, uint32_t flags);   // 0x776a60
    bool  Init();                                                   // 0x776f40
    bool  Shutdown();                                               // 0x777060
    bool  SetSlot(int mode, uint32_t k0, uint32_t k1, int* pNext);  // 0x7773c0
    virtual void r0();
    virtual void l0();
};
struct cShaderPreviewB : cShaderBase {
    uint32_t pad16c[2];
    uint8_t  flag174;
    uint8_t  pad175[3];
    IResSource* res178;
    IResSource* res17c;

    cShaderPreviewB();
    void  Draw(int unused, int unused2, cViewer** ppViewer, uint32_t flags);   // 0x776e60
    bool  Init();                                                   // 0x777130
    bool  Shutdown();                                               // 0x7771f0
    bool  SetSlot(int mode, uint32_t k0, uint32_t k1, int* pNext);  // 0x7775a0
    virtual void r0();
    virtual void l0();
};

// Thunk-ish layout helpers: A uses g.a.*, B uses g.b.*

// @ 0x00776730
cShaderPreviewA::cShaderPreviewA() {
    g.a.vec[0] = g_vec4[0]; g.a.vec[1] = g_vec4[1]; g.a.vec[2] = g_vec4[2]; g.a.vec[3] = g_vec4[3];
    g.a.key[0] = 0xffffffff; g.a.key[1] = 0xffffffff;
    g.a.has = 0; g.a.flagB = 0; g.a.viewer = 0; g.a.mode = 0;
    imgRes.p = 0; scaleFlags = 0; pad17a = 0;
    v17c[0] = g_vec3[0]; v17c[1] = g_vec3[1]; v17c[2] = g_vec3[2];
    scale = g_one;
    mat.Assign(&g_identity3);
    f1b8 = g_one;
    res1b0 = 0; res1b4 = 0;
    mode1bc = -1;
    f1c0 = 0.0f; f1c4 = 0.0f;
}

// @ 0x00776920
cShaderPreviewB::cShaderPreviewB() {
    g.b.key[0] = 0xffffffff; g.b.key[1] = 0xffffffff;
    g.b.mode = 0;
    g.b.vec[0] = g_one; g.b.vec[1] = g_one; g.b.vec[2] = g_one; g.b.vec[3] = g_one;
    g.b.flagA = 0; g.b.flagB = 0;
    flag174 = 0; res178 = 0; res17c = 0;
}


static inline float Clamp01(float t) {
    if (t <= 0.0f) t = 0.0f;
    if (t >= 1.0f) t = 1.0f;
    return t;
}

// @ 0x00776a60
void cShaderPreviewA::Draw(int unused, uint32_t* pViewerArg, uint32_t flags) {
    (void)unused;
    if (!g.a.has) return;
    cViewer* viewer = g.a.viewer;
    viewer->Copy(*pViewerArg, 0, 0);
    if (scale != 1.0f || (scaleFlags & 6)) {
        Xform xf;
        xf.a = 0; xf.b = 0;
        xf.pos[0] = g_xfInit[0]; xf.pos[1] = g_xfInit[1]; xf.pos[2] = g_xfInit[2];
        xf.one = 1.0f;
        xf.m.Assign(&g_identityB);
        viewer->GetXform(&xf);
        xf.AccumulateScaled((uint32_t*)&scaleFlags);
        viewer->SetXform(&xf);
    }
    uint16_t mode = g.a.mode;
    CompiledState* cs = slots.mpBegin[mode]->cs;
    void* tex = 0;
    if (mode == 5) {
        uint32_t k0 = g.a.key[0], k1 = g.a.key[1];
        if ((k0 & k1) != 0xffffffff) {
            if (k0 == 0x11330cf && k1 == 0) {
                tex = res1b4->GetDefaultTexture();
            } else {
                int* idx = hash.Find((ResKey*)g.a.key);
                tex = texVec.mpBegin[*idx].p->tex;
                if (!tex) return;
            }
        }
    } else if (mode == 4) {
        if (!imgRes.p) return;
        if (!(imgRes.p->flags & 1)) return;
        cImageInfo* info = imgRes.p->GetInfo();
        float w = (float)info->width;
        float h = (float)info->height;
        float invW = g_one / w;
        float invH = g_one / h;
        Transform tf;
        tf.Init();
        float aux = 0.0f;
        float f10 = 50.0f;
        int m = mode1bc;
        if (m != -1) {
            if (m == 2) {
                f10 = 80.0f;
            } else {
                viewer->GetXform(&tf);
                float len = VectorLength(tf.pos);
                aux = len;
                if (m == 0) {
                    float t = Clamp01((2338.0f - (len - 300.0f)) * 0.000427716f);
                    f10 = t * -15.0f + 60.0f;
                    aux = 0.2f;
                } else if (m == 1) {
                    float t = Clamp01((2190.0f - (len - 10.0f)) * 0.000456621f);
                    aux = t;
                    f10 = t * -10.0f + 80.0f;
                }
            }
        }
        sh.SetIndexed(0, f1b8, f10, aux, 0.0f);
        sh.SetIndexed(2, w, h, invW, invH);
    }
    if (viewer->Update()) {
        cs->Dispatch();
        if (tex) {
            ActiveState::SetTexture(0, tex);
            g_rasterDelta |= 1;
        }
        FUN_00761f90(cs, &g.a.vec, flags);
        viewer->Finish();
    }
}

// @ 0x00776e60
void cShaderPreviewB::Draw(int unused, int unused2, cViewer** ppViewer, uint32_t flags) {
    (void)unused; (void)unused2;
    if (!g.b.flagA) return;
    void* tex = 0;
    if (!(*ppViewer)->Update()) return;
    uint32_t k0 = g.b.key[0], k1 = g.b.key[1];
    SlotEntry** arr = slots.mpBegin;
    uint32_t mode = g.b.mode;
    SlotEntry* ent;
    if ((k0 & k1) == 0xffffffff)
        ent = arr[mode];
    else
        ent = arr[mode + 6];
    CompiledState* cs = ent->cs;
    if ((k0 & k1) != 0xffffffff) {
        if (k0 == 0x11330cf && k1 == 0) {
            tex = res17c->GetDefaultTexture();
        } else {
            int* idx = hash.Find((ResKey*)g.b.key);
            tex = texVec.mpBegin[*idx].p->tex;
            if (!tex) return;
        }
    }
    cs->Dispatch();
    ActiveState::SetTexture(0, tex);
    g_rasterDelta |= 1;
    FUN_00761f90(cs, g.b.vec, flags);
    (*ppViewer)->Finish();
}

// @ 0x00776f40
bool cShaderPreviewA::Init() {
    BaseInit();
    g.a.vec[0] = g_vec4[0]; g.a.vec[1] = g_vec4[1]; g.a.vec[2] = g_vec4[2]; g.a.vec[3] = g_vec4[3];
    g.a.has = 0;
    g.a.mode = 0;
    g.a.key[0] = 0xffffffff; g.a.key[1] = 0xffffffff;
    res1b0 = GetResSourceA();
    res1b4 = GetResSourceB();
    void* mem = operator_new(0x174, "Graphics", 0, 0, 0, 0);
    cViewer* v = mem ? new (mem) cViewer() : 0;
    g.a.viewer = v;
    v->Init(0);
    slots.Init(10);
    GetMaterialManager()->Register(10, g_matDesc, slots.mpBegin);
    IMessageServer* ms = GetMessageServer();
    if (ms) ms->AddListener(static_cast<cListenerBase*>(this), 0x692ea61);
    return true;
}

// @ 0x00777060
bool cShaderPreviewA::Shutdown() {
    IMessageServer* ms = GetMessageServer();
    if (ms) ms->RemoveListener(static_cast<cListenerBase*>(this), 0x692ea61, 0xffffd8f1);
    ClearTexVec();
    if (g.a.viewer) {
        g.a.viewer->Cleanup();
        cViewer* v = g.a.viewer;
        if (v) {
            v->~cViewer();
            operator_delete__(v);
        }
    }
    ClearSlotVec();
    return true;
}

// @ 0x00777130
bool cShaderPreviewB::Init() {
    g.b.vec[0] = g_vec4[0]; g.b.vec[1] = g_vec4[1]; g.b.vec[2] = g_vec4[2]; g.b.vec[3] = g_vec4[3];
    g.b.flagA = 0;
    g.b.mode = 0xffff;
    g.b.key[0] = 0xffffffff; g.b.key[1] = 0xffffffff;
    res178 = GetResSourceA();
    res17c = GetResSourceB();
    slots.Init(10);
    GetMaterialManager()->Register(10, g_matDesc, slots.mpBegin);
    IMessageServer* ms = GetMessageServer();
    if (ms) ms->AddListener(static_cast<cListenerBase*>(this), 0x692ea61);
    return true;
}

// @ 0x007771f0
bool cShaderPreviewB::Shutdown() {
    IMessageServer* ms = GetMessageServer();
    if (ms) ms->RemoveListener(static_cast<cListenerBase*>(this), 0x692ea61, 0xffffd8f1);
    ClearTexVec();
    ClearSlotVec();
    return true;
}

// @ 0x00777290
bool cShaderBase::LoadTexture(ResKey key) {
    if ((key.a & key.b) == 0xffffffff) return false;
    TexPtr tmp;
    void* res = GetImageSource()->Lookup(key.a, key.b, 0);
    if (!res) return false;
    tmp.Assign(res);
    if (texVec.mpEnd < texVec.mpCap) {
        TexPtr* e = texVec.mpEnd;
        texVec.mpEnd = e + 1;
        if (e) new (e) TexPtr(tmp);
    } else {
        texVec.DoInsertValue(texVec.mpEnd, &tmp);
    }
    int n = (int)(texVec.mpEnd - texVec.mpBegin);
    *hash.Find(&key) = n - 1;
    return true;
}

// @ 0x007773c0
bool cShaderPreviewA::SetSlot(int mode, uint32_t k0, uint32_t k1, int* pNext) {
    *pNext = mode + 1;
    if (mode < 4 || mode > 5) return false;
    g.a.mode = (uint16_t)mode;
    g.a.has = 1;
    if ((k0 & k1) == 0xffffffff) {
        void* def = res1b4->GetDefaultTexture();
        if (def && mode == 5) {
            g.a.key[0] = 0x11330cf;
            g.a.key[1] = 0;
            g.a.has = 1;
            return true;
        }
        g.a.key[0] = 0xffffffff; g.a.key[1] = 0xffffffff;
        return true;
    }
    if (mode == 4) {
        ImgRef local;
        if (k0 != 0x1677f2a || k1 != 0) {
            if (!LoadImg(k0, k1, &local.p)) return false;
            imgRes.Assign(local.p);
        }
        g.a.has = 1;
        return true;
    }
    if (mode == 5) {
        if (k0 == 0x11330cf && k1 == 0) {
            g.a.key[0] = k0;
            g.a.key[1] = k1;
            if (res1b4->IsReady()) {
                g.a.flagB = 1;
                g.a.has = 0;
                return true;
            }
            g.a.has = 1;
            return true;
        }
        ResKey key; key.a = k0; key.b = k1;
        if (LoadTexture(key)) {
            g.a.key[0] = k0;
            g.a.key[1] = k1;
            g.a.has = 1;
            return true;
        }
    }
    return false;
}

// @ 0x007775a0
bool cShaderPreviewB::SetSlot(int mode, uint32_t k0, uint32_t k1, int* pNext) {
    *pNext = mode + 1;
    switch (mode) {
    case 0: case 1: case 2: case 3:
        g.b.mode = (uint16_t)mode;
        g.b.flagA = 1;
        flag174 = 0;
        break;
    default:
        g.b.mode = 1;
        g.b.flagA = 1;
        flag174 = 0;
        break;
    case 6: case 7: case 8: case 9:
        g.b.mode = (uint16_t)(mode - 6);
        g.b.flagA = 1;
        flag174 = 1;
        break;
    }
    if ((k0 & k1) == 0xffffffff) {
        g.b.key[0] = 0xffffffff; g.b.key[1] = 0xffffffff;
        return true;
    }
    if (k0 == 0x11330cf && k1 == 0) {
        g.b.key[0] = k0;
        g.b.key[1] = 0;
        if (res17c->IsReady()) {
            g.b.flagA = 0;
            g.b.flagB = 1;
        }
        return true;
    }
    ResKey key; key.a = k0; key.b = k1;
    if (LoadTexture(key)) {
        g.b.key[0] = k0;
        g.b.key[1] = k1;
        return true;
    }
    return false;
}
