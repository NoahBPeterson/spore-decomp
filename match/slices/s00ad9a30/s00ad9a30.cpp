// s00ad9a30 -- EA Simulator ArgScript command objects that build a 0x40 RefObj message
// and dispatch it through cAppState::AddMessage.

typedef unsigned int u32;

void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);  // 0xf473a0
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

typedef void  (__thiscall *VFn)(void*);

class cArguments {
public:
    const char** MainArguments(int n);                            // 0x838320
    const char** MainArguments(int* pCount, int min, int max);    // 0x838020
    const char** OptionArguments(const char* name, int n);        // 0x838330
    bool HasFlag(const char* name);                               // 0x8380b0
};

extern unsigned int __cdecl FNV1_String8(const char* s, unsigned int seed, int flag);  // 0x932e80

extern char* g_escStop;                 // 0x1566448
extern char* g_noStop;                  // 0x156644c
extern const float k_13eb1bc;           // 0x13eb1bc

// Message object layout (0x40): RefBase primary base (vtable +0, refcount +4),
// MsgData secondary base at +8 (payload +8..0x33), flags at +0x38.
struct MsgData {
    int f08;   // +0x08
    int f0c;   // +0x0c
    int f10;   // +0x10
    int f14;   // +0x14
    int f18;   // +0x18
    int f1c;   // +0x1c
    int f20;   // +0x20
    int f24;   // +0x24
    int f28;   // +0x28
    int f2c;   // +0x2c
    int tag;   // +0x30
    MsgData() : tag(0) {}
};

struct RefBase {                        // vtable 0x13eb90c
    virtual void v0();
    virtual void AddRef();              // slot 1
    virtual void Release();             // slot 2
    long rc;                            // +0x04
    RefBase() { _InterlockedExchange(&rc, 0); }
};

struct Msg : MsgData, RefBase {         // vtable 0x13eb844
    int f34;                            // +0x34
    int flags;                          // +0x38
    int f3c;                            // +0x3c
    Msg() : MsgData(), flags(0) {}
};

struct cAppState {
    char pad[0xc];
    void AddMessage(cArguments* args, Msg* msg, char c);   // 0x7e4190
};

static inline cAppState* STATE(void* self) { return *(cAppState**)((char*)self + 0xc); }

// ArgScript argument parser reached through *(void**)(self+4); value parsers live
// in vtable slots 0x98 (float), 0xa0 (int), 0xa8 (vec3).
struct Parser {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37();
    virtual float ParseF(const char* s);        // 0x98
    virtual void  s39();
    virtual int   ParseI(const char* s);        // 0xa0
    virtual void  s41();
    virtual void* ParseV(void* out, const char* s);  // 0xa8
};

static inline Parser* PARSER(void* self) { return *(Parser**)((char*)self + 4); }


// @ 0x00ad9ff0
void __fastcall FUN_00ad9ff0(void* self, int /*edx*/, cArguments* args)
{
    args->MainArguments(0);
    Msg* m = new ("Simulator", 0, 0, 0, 0) Msg();
    if (m) m->AddRef();
    m->tag = 0x05caabce;
    STATE(self)->AddMessage(args, m, 0);
    m->Release();
}

// @ 0x00ada070
void __fastcall FUN_00ada070(void* self, int /*edx*/, cArguments* args)
{
    int n = 0;
    const char** av = args->MainArguments(&n, 1, 1);
    Msg* m = new ("Simulator", 0, 0, 0, 0) Msg();
    if (m) m->AddRef();
    m->tag = 0x047b92d6;
    const char* s = av[0];
    m->f08 = (int)FNV1_String8(s, 0x811c9dc5, 1);
    STATE(self)->AddMessage(args, m, 0);
    m->Release();
}

// @ 0x00ada110
void __fastcall FUN_00ada110(void* self, int /*edx*/, cArguments* args)
{
    Msg* m = new ("Simulator", 0, 0, 0, 0) Msg();
    if (m) m->AddRef();
    args->MainArguments(0);
    m->tag = 0x04448b88;
    const char** a;
    if ((a = args->OptionArguments("id", 1)))      m->f08 = PARSER(self)->ParseI(a[0]);
    if ((a = args->OptionArguments("data1", 1)))   m->f10 = PARSER(self)->ParseI(a[0]);
    if ((a = args->OptionArguments("data2", 1)))   m->f18 = PARSER(self)->ParseI(a[0]);
    if ((a = args->OptionArguments("data3", 1)))   m->f20 = PARSER(self)->ParseI(a[0]);
    if ((a = args->OptionArguments("data4", 1)))   m->f28 = PARSER(self)->ParseI(a[0]);
    STATE(self)->AddMessage(args, m, 0);
    m->Release();
}

// @ 0x00ada250
void __fastcall FUN_00ada250(void* self, int /*edx*/, cArguments* args)
{
    args->MainArguments(0);
    Msg* m = new ("Simulator", 0, 0, 0, 0) Msg();
    if (m) m->AddRef();
    const char** a = args->OptionArguments("secs", 1);
    if (a) {
        m->f08 = 0;
        *(float*)&m->f10 = PARSER(self)->ParseF(a[0]);
    } else if (args->HasFlag("forContinue")) {
        m->f08 = 1;
        *(float*)&m->f10 = k_13eb1bc;
    } else if (args->HasFlag("forButton")) {
        m->f08 = 2;
        *(float*)&m->f10 = k_13eb1bc;
    } else if (args->HasFlag("forNext")) {
        m->f08 = 3;
        *(float*)&m->f10 = k_13eb1bc;
    }
    m->tag = 0x0445f6e8;
    STATE(self)->AddMessage(args, m, 0);
    m->Release();
}

// @ 0x00ada360
void __fastcall FUN_00ada360(void* self, int /*edx*/, cArguments* args)
{
    const char** av = args->MainArguments(1);
    Msg* m = new ("Simulator", 0, 0, 0, 0) Msg();
    if (m) m->AddRef();
    m->tag = 0x04518de0;
    *(float*)&m->f08 = PARSER(self)->ParseF(av[0]);
    STATE(self)->AddMessage(args, m, 0);
    m->Release();
}

// @ 0x00ada3f0
void __fastcall FUN_00ada3f0(void* self, int /*edx*/, cArguments* args)
{
    Msg* m = new ("Simulator", 0, 0, 0, 0) Msg();
    if (m) m->AddRef();
    m->tag = 0x06133baa;
    int z = 0;
    if (args->HasFlag("zoomToEnd")) z = 1;
    int h = 0;
    const char** a = args->OptionArguments("timelineEvent", 1);
    if (a) { const char* s = a[0]; h = (int)FNV1_String8(s, 0x811c9dc5, 1); }
    m->f08 = z;
    m->f10 = h;
    STATE(self)->AddMessage(args, m, 0);
    m->Release();
}

// @ 0x00ada4b0
void __fastcall FUN_00ada4b0(void* self, int /*edx*/, cArguments* args)
{
    Msg* m = new ("Simulator", 0, 0, 0, 0) Msg();
    if (m) m->AddRef();
    m->tag = 0x046ac0ac;
    int pause = 0;
    if (args->HasFlag("pauseGraphics")) pause = 1;
    int se = 0;
    int code = 0;
    if (args->HasFlag("screenEffect")) { se = code + 1; code = 0xdfe90cad; }
    const char** a = args->OptionArguments("effect", 1);
    if (a) { const char* s = a[0]; se = 1; code = (int)FNV1_String8(s, 0x811c9dc5, 1); }
    m->f08 = pause;
    m->f10 = se;
    m->f18 = code;
    STATE(self)->AddMessage(args, m, 0);
    m->Release();
}

// @ 0x00ada620
void __fastcall FUN_00ada620(void* self, int /*edx*/, cArguments* args)
{
    Msg* m = new ("Simulator", 0, 0, 0, 0) Msg();
    if (m) m->AddRef();
    m->tag = 0x046d28ea;
    unsigned char stopped = 1;
    unsigned char avatar = 0;
    if (args->HasFlag("stop")) stopped = 0;
    if (args->HasFlag("avatarOnly")) avatar = 1;
    m->f08 = stopped;
    m->f10 = avatar;
    STATE(self)->AddMessage(args, m, 0);
    m->Release();
}

// @ 0x00ada6d0
void __fastcall FUN_00ada6d0(void* self, int /*edx*/, cArguments* args)
{
    Msg* m = new ("Simulator", 0, 0, 0, 0) Msg();
    if (m) m->AddRef();
    m->tag = 0x0473eb8d;
    int n = 0;
    const char** av = args->MainArguments(&n, 1, 2);
    const char* s;
    switch (n) {
    case 1: {
        const char* a0 = av[0];
        m->f08 = (int)FNV1_String8(a0, 0x811c9dc5, 1);
        s = av[0];
        break;
    }
    case 2: {
        const char* a0 = av[0];
        m->f08 = (int)FNV1_String8(a0, 0x811c9dc5, 1);
        s = av[1];
        break;
    }
    default:
        goto done;
    }
    m->f10 = (int)FNV1_String8(s, 0x811c9dc5, 1);
    STATE(self)->AddMessage(args, m, 0);
done:
    int f = 0;
    if (args->HasFlag(g_escStop)) f = 1;
    if (args->HasFlag(g_noStop)) f = 2;
    m->f18 = f;
    m->Release();
}

// @ 0x00ada7e0
void __fastcall FUN_00ada7e0(void* self, int /*edx*/, cArguments* args)
{
    Msg* m = new ("Simulator", 0, 0, 0, 0) Msg();
    if (m) m->AddRef();
    m->tag = 0x0473eb91;
    const char** av = args->MainArguments(1);
    const char* s = av[0];
    m->f08 = (int)FNV1_String8(s, 0x811c9dc5, 1);
    STATE(self)->AddMessage(args, m, 0);
    m->Release();
}

// @ 0x00ada880
void __fastcall FUN_00ada880(void* self, int /*edx*/, cArguments* args)
{
    Msg* m = new ("Simulator", 0, 0, 0, 0) Msg();
    if (m) m->AddRef();
    m->tag = 0x04740862;
    const char** av = args->MainArguments(2);
    const char* s = av[0];
    m->f08 = (int)FNV1_String8(s, 0x811c9dc5, 1);
    *(float*)&m->f10 = PARSER(self)->ParseF(av[1]);
    STATE(self)->AddMessage(args, m, 0);
    m->Release();
}

// @ 0x00ada920
void __fastcall FUN_00ada920(void* self, int /*edx*/, cArguments* args)
{
    Msg* m = new ("Simulator", 0, 0, 0, 0) Msg();
    if (m) m->AddRef();
    m->tag = 0x0493440d;
    if (args->HasFlag("off"))       m->f08 = 1;
    else if (args->HasFlag("on"))   m->f08 = 0;
    STATE(self)->AddMessage(args, m, 0);
    m->Release();
}

// ---- 0x8c editor-resource command (00ad9a30) ----------------------------------

extern void* vtbl_145b38c;   // 0x145b38c
extern void* vtbl_13eb938;   // 0x13eb938
extern void* vtbl_145b380;   // 0x145b380
extern const float k_1485720, k_1471064, k_140f7ac;

struct Vec3 { float x, y, z; Vec3() {} Vec3(float a, float b, float c) { x = a; y = b; z = c; } };

struct ResSub {                 // secondary base at +8
    virtual void v0();          // slot 0 (addref)
    virtual void Rel();         // slot 1 (release)
};

struct Res {                    // 0x8c
    void*  f00;       // 0x00  primary vptr
    int    f04;       // 0x04
    ResSub sub;       // 0x08  secondary base (vptr only)
    float  f0c;       // 0x0c
    int    f10;       // 0x10
    Vec3   v14;       // 0x14
    Vec3   v20;       // 0x20
    char   b2c, b2d, b2e, b2f;
    char   b30, b31; char p32[2];
    int    f34;
    int    f38;
    char   b3c, b3d, b3e, b3f;
    int    f40;
    char   b44; char p45[3];
    float  f48, f4c, f50, f54, f58;
    char   b5c, b5d; char p5e[2];
    float  f60, f64;
    int    f68;
    int    f6c, f70, f74;
    int    f78, f7c;
    Vec3   v80;       // 0x80
};

// @ 0x00ad9a30
void __fastcall FUN_00ad9a30(void* self, int /*edx*/, cArguments* args)
{
    args->MainArguments(0);
    Res* r = new ("Simulator", 0, 0, 0, 0) Res();
    void** psub = (void**)&r->sub;
    if (r) {
        r->f04 = 0;
        psub[0] = &vtbl_13eb938;
        r->f00 = &vtbl_145b38c;
        psub[0] = &vtbl_145b380;
        r->f6c = 0;
        r->f70 = 0;
        r->f74 = 0;
        r->sub.v0();
    }
    r->v80 = Vec3(0, 0, 0);
    r->v14 = Vec3(0, 0, 0);
    r->v20 = Vec3(0, 0, 0);
    r->f0c = 0;
    r->f10 = 0;
    r->f58 = k_1485720;
    r->f60 = k_1471064;
    r->f64 = k_140f7ac;
    r->f40 = 4;
    r->b44 = 0;
    r->b3c = 1;
    r->b2c = 0; r->b2d = 0; r->b2e = 0; r->b2f = 0;
    r->b30 = 0; r->b31 = 0;
    r->f34 = 0;
    r->b3d = 0; r->b3e = 0;
    r->f48 = 0; r->f4c = 0; r->f50 = 0; r->f54 = 0;
    r->b5d = 0;
    r->f38 = 0;

    Msg* m = new ("Simulator", 0, 0, 0, 0) Msg();
    if (m) m->AddRef();
    m->tag = 0x04448b81;
    if ((m->flags & 1) && m->f08) ((ResSub*)m->f08)->Rel();
    m->f08 = (int)&r->sub;
    if (m->f08) ((ResSub*)m->f08)->v0();
    m->flags |= 1;

    if (args->HasFlag("backToStart")) r->b44 = 1;
    const char** a;
    if ((a = args->OptionArguments("target", 1))) { const char* s = a[0]; r->f10 = (int)FNV1_String8(s, 0x811c9dc5, 1); }
    if ((a = args->OptionArguments("offset", 1))) r->f0c = PARSER(self)->ParseF(a[0]);
    if (args->HasFlag("noWait")) r->b3c = 0;
    if (args->HasFlag("follow")) r->b2c = 1;
    if (args->HasFlag("orient")) r->b2d = 1;
    if (args->HasFlag("orientFlat")) r->b2e = 1;
    if (args->HasFlag("anchored")) r->f40 = 0;
    else if (args->HasFlag("ballistic")) r->f40 = 1;
    else if (args->HasFlag("satellite")) r->f40 = 2;
    if (args->HasFlag("useFootprint")) r->b2f = 1;
    if (args->HasFlag("useRadius")) r->b30 = 1;
    if (args->HasFlag("useHeight")) r->b31 = 1;
    if ((a = args->OptionArguments("radiusTarget", 1))) { const char* s = a[0]; r->f34 = (int)FNV1_String8(s, 0x811c9dc5, 1); }
    if ((a = args->OptionArguments("offset", 1))) r->f0c = PARSER(self)->ParseF(a[0]);
    if (args->HasFlag("snap")) r->b3d = 1;
    if (args->HasFlag("ease")) r->b3e = 1;
    {
        float v[3];
        if ((a = args->OptionArguments("targetOffset", 1))) {
            float* p = (float*)PARSER(self)->ParseV(v, a[0]);
            r->v14.x = p[0]; r->v14.y = p[1]; r->v14.z = p[2];
        }
        if ((a = args->OptionArguments("extraTargetOffset", 1))) {
            float* p = (float*)PARSER(self)->ParseV(v, a[0]);
            r->v20.x = p[0]; r->v20.y = p[1]; r->v20.z = p[2];
        }
        if (args->HasFlag("targetTerrain")) r->f38 = 2;
        else if (args->HasFlag("targetHead")) r->f38 = 1;
        if ((a = args->OptionArguments("targetpos", 1))) {
            float* p = (float*)PARSER(self)->ParseV(v, a[0]);
            r->v80.x = p[0]; r->v80.y = p[1]; r->v80.z = p[2];
        }
    }
    if ((a = args->OptionArguments("fov", 1))) r->f54 = PARSER(self)->ParseF(a[0]);
    if ((a = args->OptionArguments("nearClip", 1))) r->f60 = PARSER(self)->ParseF(a[0]);
    if ((a = args->OptionArguments("farClip", 1))) r->f64 = PARSER(self)->ParseF(a[0]);
    if ((a = args->OptionArguments("duration", 1))) r->f58 = PARSER(self)->ParseF(a[0]);
    if ((a = args->OptionArguments("heading", 1))) r->f48 = PARSER(self)->ParseF(a[0]);
    if ((a = args->OptionArguments("pitch", 1))) r->f4c = PARSER(self)->ParseF(a[0]);
    if ((a = args->OptionArguments("roll", 1))) r->f50 = PARSER(self)->ParseF(a[0]);
    if (args->HasFlag("sphere")) r->b5d = 1;

    STATE(self)->AddMessage(args, m, 0);
    m->Release();
    ((ResSub*)psub)->Rel();
}
