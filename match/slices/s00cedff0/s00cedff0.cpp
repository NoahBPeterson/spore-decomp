// Slice s00cedff0 -- Spore city-game cheat commands, bundle/container helpers and
// city-game formula math.
//
// Modelled types (retail member offsets are read from the disassembly; objects are
// modelled locally with role-named members and explicit padding for untouched gaps):
//   cCommandSetVehicleWeapons  vtable @0x00, parser @0x04 (parser's vtable @0x00)
//   cCityGameCheatManager      empty marker object @0x00
//   cGameBundleContainer       vtable @0x00 only (AsISpatialObject dispatch)
//   VecObj                     vector begin @0x04, end @0x08 (used by the anonymous
//                              bundle-list helpers)
//   VecObj18                   vtable @0x00, vector @0x04/@0x08/@0x0c, owner @0x18
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-

typedef unsigned int   u32;
typedef unsigned char  u8;
typedef signed char    i8;
typedef unsigned short u16;
typedef int            i32;

// --------------------------------------------------------------- extern decls

extern "C" void  FUN_00e94a00();  // 0x00e94a00  cVehicleView::ToggleShowPaths
extern "C" int   FUN_00837f30();  // 0x00837f30  cArguments::NumArguments (ecx)
extern "C" void *FUN_00837f20();  // 0x00837f20  cArguments::operator[] (ecx)
extern "C" void  FUN_00cac1a0();  // 0x00cac1a0  cVehicle::DebugChangeWeapons (cdecl 1)
extern "C" void *FUN_0067de20();  // 0x0067de20  SP::CheatManager
extern "C" void *FUN_00f473a0();  // 0x00f473a0  operator_new(size,file,0,0,0,0)
extern "C" void *FUN_0083c800();  // 0x0083c800  cCommandBase::cCommandBase (ecx)
extern "C" void *FUN_00b3d300();  // 0x00b3d300  SP::NounManager
extern "C" void *FUN_00b21340();  // 0x00b21340  cGameNounManager::GetGameDataVector (ecx, 5)
extern "C" void *FUN_00b25c30();  // 0x00b25c30  (ecx = noun manager)
extern "C" void  FUN_00be1340();  // 0x00be1340  (ecx = manager)
extern "C" void *FUN_00b3d2b0();  // 0x00b3d2b0  spawn helper (args vary)
extern "C" void  FUN_00ac7ab0();  // 0x00ac7ab0  (ecx = spawned object)
extern "C" void  FUN_00ac7a40();  // 0x00ac7a40  drainNouns (ecx = object, 1 arg)
extern "C" u32   FUN_00a68fb0();  // 0x00a68fb0  RandomUint32Uniform (ecx = rng)
extern "C" void  FUN_0093aa70();  // 0x0093aa70  EA::IO::WriteUint32
extern "C" void  FUN_00692f90();  // 0x00692f90  cVarListSerializer::cVarListSerializer (ecx)
extern "C" void  FUN_00692900();  // 0x00692900  cVarListSerializer::Serialize (ecx)
extern "C" void  FUN_00e25bd0();  // 0x00e25bd0  eastl vector::erase (ecx = vector)
extern "C" void  FUN_006782c0();  // 0x006782c0  eastl::copy_impl
extern "C" void  FUN_00ae6970();  // 0x00ae6970  eastl vector destructor (ecx)
extern "C" void  FUN_00aea5d0();  // 0x00aea5d0  SPVector::DoInsertPtr (ecx = vector)
extern "C" void  FUN_00c36230();  // 0x00c36230  (ecx = value, 1 arg)
extern "C" void  FUN_00c36270();  // 0x00c36270  (ecx = value)
extern "C" void  FUN_00f47380();  // 0x00f47380  operator_delete_array
extern "C" double FUN_00bd7d00();  // 0x00bd7d00  (ecx = object) -> double (x87)
extern "C" double FUN_009360d0();  // 0x009360d0  RandomDoubleUniform (ecx = rng) -> double (x87)
extern "C" double pow(double, double);  // 0x011e08f0  x87 _CIpow
extern "C" double sin(double);          // x87 fsin intrinsic
extern "C" void  FUN_004e7460();  // 0x004e7460  generic 7-argument helper
extern "C" char  FUN_007f2240();  // 0x007f2240  LoadArithmeticaFile(hash,0,dst)
extern "C" void *FUN_00b3d2c0();  // 0x00b3d2c0  SP::RelationshipManager
extern "C" int   FUN_00d00a70();  // 0x00d00a70  relationship query (ecx, 3 args)
extern "C" float FUN_00d00a10();  // 0x00d00a10  relationship value (ecx, 3 args)
extern "C" void *FUN_00b25ca0();  // 0x00b25ca0  cGameNounManager::GetCivilizationList (ecx)
extern "C" void *FUN_00bd9bf0();  // 0x00bd9bf0  cCity::GetCivilization (ecx)
extern "C" char  FUN_00bef8a0();  // 0x00bef8a0

// callback function pointers passed to GetGameDataVector
extern "C" void FUN_00cd7d10();  // 0x00cd7d10
extern "C" void FUN_00d3d420();  // 0x00d3d420
extern "C" void FUN_00acdff0();  // 0x00acdff0
extern "C" void FUN_00b1e500();  // 0x00b1e500

// ------------------------------------------------------------------- globals

extern "C" void *g_cmdMakeTradeRoutes;      // 0x0158167c
extern "C" void *g_cmdToggleShowPaths;      // 0x01581680
extern "C" void *g_cmdSetVehicleWeapons;    // 0x01581684
extern "C" char  g_dat018c43e8;             // 0x018c43e8
extern "C" char  g_dat015816b8;             // 0x015816b8
extern "C" char  g_sMathRandom;             // 0x01601760

extern "C" float g_169cc10;  // 0x0169cc10
extern "C" float g_169cc14;  // 0x0169cc14
extern "C" float g_169cc18;  // 0x0169cc18
extern "C" float g_169cc1c;  // 0x0169cc1c
extern "C" float g_169cc24;  // 0x0169cc24
extern "C" float g_169cc28;  // 0x0169cc28
extern "C" float g_169cc2c;  // 0x0169cc2c
extern "C" float g_169cc30;  // 0x0169cc30
extern "C" float g_169cc34;  // 0x0169cc34
extern "C" float g_169cc38;  // 0x0169cc38
extern "C" float g_169cc3c;  // 0x0169cc3c
extern "C" float g_169cc58;  // 0x0169cc58
extern "C" char  g_169c340;  // 0x0169c340  tribe chance to recruit formula
extern "C" char  g_169c3d8;  // 0x0169c3d8  player recruit success formula
extern "C" char  g_169c470;  // 0x0169c470  tribe chance to raid formula
extern "C" char  g_169c508;  // 0x0169c508  player raid success formula
extern "C" char  g_169c5a0;  // 0x0169c5a0  tribe food formula
extern "C" char  g_169c2a8;  // 0x0169c2a8  recruit from tribe formula
extern "C" char  g_169c638;  // 0x0169c638  attack chance to die formula
extern "C" char  g_169c6d0;  // 0x0169c6d0  tribe attack when approached
extern "C" char  g_169c768;  // 0x0169c768  lurk formula
extern "C" char  g_169c800;  // 0x0169c800  raid farm formula
extern "C" char  g_169c930;  // 0x0169c930  vehicle stats formula
extern "C" char  g_169c898;  // 0x0169c898  wander formula
extern "C" char  g_169c9c8;  // 0x0169c9c8  (anonymous formula)
extern "C" float g_13eb960;  // 0x013eb960  (0.01)
extern "C" float g_1471064;  // 0x01471064  (0.5)
extern "C" float g_13eb1bc;  // 0x013eb1bc
extern "C" float g_13eb8c8;  // 0x013eb8c8  (0.3)
extern "C" float g_14471e8;  // 0x014471e8  (-0.3)
extern "C" float g_1485ac0;  // 0x01485ac0  (0.7)
extern "C" float g_13f6a38;  // 0x013f6a38  (-0.05)
extern "C" float g_13ec478;  // 0x013ec478  (0.05)
extern "C" float g_13eb8b0;  // 0x013eb8b0  (sign mask)
extern "C" float g_13fdcf8;  // 0x013fdcf8  (600)
extern "C" float g_13f08c0;  // 0x013f08c0  (40)
extern "C" float g_1470f1c;  // 0x01470f1c  (2.0)
extern "C" float g_13eb95c;  // 0x013eb95c  (3.0)
extern "C" float g_13ec480;  // 0x013ec480  (0.2)
extern "C" float g_13f26dc;  // 0x013f26dc  (1/3)
extern "C" float g_145c130;  // 0x0145c130  (4000)
extern "C" float g_145c12c;  // 0x0145c12c  (2000)
extern "C" float g_1469428;  // 0x01469428  (16000)
extern "C" float g_169cc0c;  // 0x0169cc0c
extern "C" float g_1486110;  // 0x01486110  (5.0)
extern "C" float g_14853bc;  // 0x014853bc  (30.0)
extern "C" float g_1488874;  // 0x01488874  (0.1)
extern "C" float g_1485720;  // 0x01485720  (1.0)
extern "C" double g_13f5628; // 0x013f5628
extern "C" double g_140f398; // 0x0140f398
extern "C" double g_140c4f0; // 0x0140c4f0

// ------------------------------------------------------------ local type decls

struct ArgParser { void **m_vtbl00; };

struct cCommandToggleShowPaths {
    void Execute(void *args);
};

struct cCommandSetVehicleWeapons {
    void **m_vtbl00;   // +0x00
    ArgParser *m_parser; // +0x04
    void Execute(void *args);
};

struct cCommandMakeTradeRoutes {
    void Execute(void *args);
};

struct CheatManagerObj { void **m_vtbl00; };

struct cCityGameCheatManager {
    ~cCityGameCheatManager();
};

struct CommandObj {
    void **m_vtbl00;
    void *m_field04;
    int   m_refCount;
};

// vector begin/end at +0x04/+0x08 of the owning object
struct VecObj {
    u32    m_field00;
    void **mpBegin;   // +0x04
    void **mpEnd;     // +0x08
};

struct Vec3 {
    void **mpBegin;   // +0x04
    void **mpEnd;     // +0x08
    void **mpCap;     // +0x0c
};

struct VecObj18 {
    void **m_vtbl00;  // +0x00
    Vec3   m_vec;     // +0x04
    u32    m_field10; // +0x10
    u32    m_field14; // +0x14
    void  *m_owner18; // +0x18
};

struct BundleObj {
    u8     m_pad00[0x18];
    void  *m_owner18; // +0x18
    u32    m_field1c; // +0x1c
    float  m_field20; // +0x20
};

struct Obj290 {
    u8  m_pad00[0x1c];
    int m_field1c;    // +0x1c
    float m_field20;  // +0x20
};

struct Obj270 {
    void **m_vtbl00;
};

struct GameDataVec {
    u32    m_field00;
    void **mpBegin;   // +0x04
    void **mpEnd;     // +0x08
};

struct cVarListSerializer {
    u8 m_data[0xa14];
};

struct Frame3d0 {
    u32 m_signature;          // +0x0000
    cVarListSerializer m_ser; // +0x0004
};

// ------------------------------------------------------------------ 0x00cedff0

struct cCommandToggleShowPaths;

// @ 0x00cedff0
void cCommandToggleShowPaths::Execute(void *args)
{
    FUN_00e94a00();
}

// @ 0x00cee010
void cCommandSetVehicleWeapons::Execute(void *args)
{
    if (((int(__thiscall *)(void *))FUN_00837f30)(args) > 1) {
        void **vt = m_parser->m_vtbl00;
        void *a = ((void *(__thiscall *)(void *, int))FUN_00837f20)(args, 1);
        void *r = ((void *(__thiscall *)(void *, void *))vt[0x9c / 4])(m_parser, a);
        ((void(__cdecl *)(void *))FUN_00cac1a0)(r);
    }
}

// @ 0x00cee060
cCityGameCheatManager::~cCityGameCheatManager()
{
    CheatManagerObj *cm = (CheatManagerObj *)FUN_0067de20();
    ((void(__thiscall *)(void *, void *))(*(void ***)cm)[0x1c / 4])(cm, g_cmdMakeTradeRoutes);
    ((void(__thiscall *)(void *, void *))(*(void ***)cm)[0x1c / 4])(cm, g_cmdToggleShowPaths);
    ((void(__thiscall *)(void *, void *))(*(void ***)cm)[0x1c / 4])(cm, g_cmdSetVehicleWeapons);
}

namespace Simulator {
struct cCivModeStrategy {
    cCivModeStrategy();
};
}

// @ 0x00cee130
Simulator::cCivModeStrategy::cCivModeStrategy()
{
    CommandObj *c;

    FUN_0067de20();

    c = (CommandObj *)((void *(__cdecl *)(u32, void *, u32, u32, u32, u32))FUN_00f473a0)
            (0x10, (void *)0x13f09b4, 0, 0, 0, 0);
    if (c) {
        ((void *(__thiscall *)(void *))FUN_0083c800)(c);
        c->m_vtbl00 = (void **)0x14781d4;
    }

    c = (CommandObj *)((void *(__cdecl *)(u32, void *, u32, u32, u32, u32))FUN_00f473a0)
            (0x10, (void *)0x13f09b4, 0, 0, 0, 0);
    if (c) {
        ((void *(__thiscall *)(void *))FUN_0083c800)(c);
        c->m_vtbl00 = (void **)0x14781bc;
    }

    c = (CommandObj *)((void *(__cdecl *)(u32, void *, u32, u32, u32, u32))FUN_00f473a0)
            (0x10, (void *)0x13f09b4, 0, 0, 0, 0);
    if (c) {
        ((void *(__thiscall *)(void *))FUN_0083c800)(c);
        c->m_vtbl00 = (void **)0x14781ec;
    }
}

// @ 0x00cee1c0
void cCommandMakeTradeRoutes::Execute(void *args)
{
    GameDataVec *v;
    void *mgr;
    int count;
    int i;

    v = (GameDataVec *)((void *(__thiscall *)(void *, void *, void *, void *, void *, void *))FUN_00b21340)
            ((void *)FUN_00b3d300(),
             (void *)FUN_00cd7d10, (void *)FUN_00d3d420,
             (void *)FUN_00acdff0, (void *)FUN_00b1e500,
             &g_dat018c43e8);

    mgr = ((void *(__thiscall *)(void *))FUN_00b25c30)((void *)FUN_00b3d300());
    if (mgr) {
        count = (int)(v->mpEnd - v->mpBegin);
        for (i = 0; i < count; ++i) {
            void *obj = v->mpBegin[i];
            char c = ((char(__thiscall *)(void *))(*(void ***)((u8 *)obj + 0x120))[0x58 / 4])
                        ((u8 *)obj + 0x120);
            if (!c)
                ((void(__thiscall *)(void *, void *, u32))FUN_00be1340)(mgr, obj, 0);
        }
    }
}

// @ 0x00cee270
void __stdcall FUN_00cee270(void *p)
{
    u8 *base = (u8 *)p;
    u8 *o = *(u8 **)(base + 0x34);
    void **fn;

    base += 0x34;
    fn = *(void ***)(o + 0x84);
    ((void(__thiscall *)(void *))fn)(base);
}

// @ 0x00cee290
float __fastcall FUN_00cee290(Obj290 *o, void *edx)
{
    (void)edx;
    return (float)((float)o->m_field1c * o->m_field20);
}

namespace SP {
struct cGameBundleContainer {
    void **m_vtbl00;
    void *AsISpatialObject();
};
}

// @ 0x00cee2a0
void *SP::cGameBundleContainer::AsISpatialObject()
{
    if (this)
        return ((void *(__thiscall *)(void *, void *))m_vtbl00[0x14 / 4])(this, (void *)0x1186577);
    return 0;
}

// @ 0x00cee2c0
void __fastcall FUN_00cee2c0(BundleObj *o, void *edx, void *obj, u32 a, float b, float c, u32 d)
{
    void *old;
    (void)edx;

    old = o->m_owner18;
    if (obj != old) {
        if (obj)
            ((void(__thiscall *)(void *))(*(void ***)obj)[0])(obj);
        o->m_owner18 = obj;
        if (old)
            ((void(__thiscall *)(void *))(*(void ***)old)[1])(old);
    }
    o->m_field20 = b;
    o->m_field1c = a;
    if (c > 0.0f) {
        void *r = ((void *(__cdecl *)(float, BundleObj *, u32))FUN_00b3d2b0)(c, o, d);
        ((void(__thiscall *)(void *))FUN_00ac7ab0)(r);
    }
}

// @ 0x00cee330
void *__fastcall FUN_00cee330(VecObj *v, void *edx)
{
    (void)edx;
    if (v->mpBegin != v->mpEnd)
        return *v->mpBegin;
    return 0;
}

// @ 0x00cee340
void *__fastcall FUN_00cee340(VecObj *v, void *edx)
{
    int n;
    u32 i;
    (void)edx;

    if (v->mpBegin == v->mpEnd)
        return 0;
    n = (int)(v->mpEnd - v->mpBegin);
    i = ((u32(__thiscall *)(void *, u32))FUN_00a68fb0)(&g_sMathRandom, (u32)n);
    return v->mpBegin[i];
}

// @ 0x00cee380
double __fastcall FUN_00cee380(VecObj *v, void *edx)
{
    float sum = 0.0f;
    void **it;
    (void)edx;

    if (v->mpBegin != v->mpEnd) {
        for (it = v->mpBegin; it != v->mpEnd; ++it)
            sum = *(float *)((u8 *)*it + 0x134) + sum;
    }
    return (double)sum;
}

// @ 0x00cee3d0
void __fastcall FUN_00cee3d0(void *self, void *edx, void *stream)
{
    void *a;
    void *b;
    Frame3d0 frame;
    (void)edx;

    a = ((void *(__thiscall *)(void *))(*(void ***)stream)[0x20 / 4])(stream);
    frame.m_signature = 0x135b1e8;
    b = ((void *(__thiscall *)(void *))(*(void ***)a)[0x18 / 4])(a);
    ((char(__cdecl *)(void *, u32 *, u32, u32))FUN_0093aa70)(b, &frame.m_signature, 1, 0);
    ((void(__thiscall *)(void *, void *, void *, u32))FUN_00692f90)
            (&frame.m_ser, self, &g_dat015816b8, 0x1a80d26);
    ((char(__thiscall *)(void *, void *))FUN_00692900)(&frame.m_ser, stream);
}

// @ 0x00cee4a0
void *__fastcall FUN_00cee4a0(VecObj *v, void *edx, float *p)
{
    void *best = 0;
    float bestDist = 3.402823466e+38f;
    void **it;
    void **end;
    (void)edx;

    it = v->mpBegin;
    end = v->mpEnd;
    while (it != end) {
        void *obj = *it;
        float *pos = ((float *(__thiscall *)(void *))(*(void ***)((u8 *)obj + 0x34))[0x2c / 4])
                        ((u8 *)obj + 0x34);
        float d = ((p[0] - pos[0]) * (p[0] - pos[0]) +
                   (p[1] - pos[1]) * (p[1] - pos[1])) +
                  (p[2] - pos[2]) * (p[2] - pos[2]);
        if (!best || d < bestDist) {
            best = obj;
            bestDist = d;
        }
        ++it;
    }
    return best;
}

// @ 0x00cee540
void *__fastcall FUN_00cee540(VecObj *v, void *edx, float *p, float threshold)
{
    void *nearObj = 0;
    void *farObj = 0;
    float nearDist = 3.402823466e+38f;
    float farDist = 3.402823466e+38f;
    void **it;
    void **end;
    (void)edx;

    it = v->mpBegin;
    end = v->mpEnd;
    while (it != end) {
        void *obj = *it;
        float *pos = ((float *(__thiscall *)(void *))(*(void ***)((u8 *)obj + 0x34))[0x2c / 4])
                        ((u8 *)obj + 0x34);
        float d = ((p[2] - pos[2]) * (p[2] - pos[2]) +
                   (p[1] - pos[1]) * (p[1] - pos[1])) +
                  (p[0] - pos[0]) * (p[0] - pos[0]);
        if (*(int *)((u8 *)obj + 0x120) == 0) {
            if (!nearObj || d < nearDist) {
                nearObj = obj;
                nearDist = d;
            }
        } else if (threshold < *(float *)((u8 *)obj + 0x134)) {
            if (!farObj || d < farDist) {
                farObj = obj;
                farDist = d;
            }
        }
        ++it;
    }
    return nearObj ? nearObj : farObj;
}

// @ 0x00cee630
void *__fastcall FUN_00cee630(VecObj18 *o, void *edx)
{
    (void)edx;
    o->m_vtbl00 = (void **)0x1478220;
    o->m_vec.mpBegin = 0;
    o->m_vec.mpEnd = 0;
    o->m_vec.mpCap = 0;
    o->m_owner18 = 0;
    return o;
}

// @ 0x00cee650
void __fastcall FUN_00cee650(VecObj *v, void *edx, void *value)
{
    void **found;
    (void)edx;

    if (v->mpBegin == v->mpEnd)
        return;

    if (!value) {
        ((void(__thiscall *)(void *))FUN_00c36270)(*v->mpBegin);
        found = v->mpBegin;
    } else {
        ((void(__thiscall *)(void *))FUN_00c36270)(value);
        found = v->mpBegin;
        if (found == v->mpEnd)
            return;
        while (*found != value) {
            ++found;
            if (found == v->mpEnd)
                return;
        }
    }

    if (found + 1 < v->mpEnd)
        ((void(__cdecl *)(void **, void **, void **))FUN_006782c0)(found + 1, v->mpEnd, found);
    v->mpEnd = v->mpEnd - 1;
    {
        void *last = *v->mpEnd;
        if (last)
            ((void(__thiscall *)(void *))(*(void ***)last)[1])(last);
    }
}

// @ 0x00cee7a0
void __fastcall FUN_00cee7a0(VecObj18 *o, void *edx)
{
    (void)edx;
    o->m_vtbl00 = (void **)0x1478220;
    if (o->m_vec.mpBegin != o->m_vec.mpEnd)
        ((void(__thiscall *)(Vec3 *, void **, void **))FUN_00e25bd0)
                (&o->m_vec, o->m_vec.mpBegin, o->m_vec.mpEnd);
    if (o->m_owner18)
        ((void(__thiscall *)(void *))(*(void ***)o->m_owner18)[1])(o->m_owner18);
    ((void(__thiscall *)(Vec3 *))FUN_00ae6970)(&o->m_vec);
}

// @ 0x00cee7e0
void __fastcall FUN_00cee7e0(VecObj18 *o, void *edx)
{
    void *r;
    (void)edx;

    r = ((void *(__thiscall *)(void *))FUN_00b3d2b0)(o);
    ((void(__thiscall *)(void *, void *))FUN_00ac7a40)(r, o);
    if (o->m_owner18) {
        void *p = o->m_owner18;
        o->m_owner18 = 0;
        ((void(__thiscall *)(void *))(*(void ***)p)[1])(p);
    }
    ((void(__thiscall *)(Vec3 *, void **, void **))FUN_00e25bd0)
            (&o->m_vec, o->m_vec.mpBegin, o->m_vec.mpEnd);
}

// @ 0x00cee820
void __fastcall FUN_00cee820(VecObj18 *o, void *edx, void *value)
{
    void *v;
    void **end;
    (void)edx;

    ((void(__thiscall *)(void *, void *))FUN_00c36230)(value, o);
    v = value;
    if (v)
        ((void(__thiscall *)(void *))(*(void ***)v)[0])(v);

    end = o->m_vec.mpEnd;
    if (end < o->m_vec.mpCap) {
        o->m_vec.mpEnd = end + 1;
        if (end) {
            *end = v;
            if (v)
                ((void(__thiscall *)(void *))(*(void ***)v)[0])(v);
        }
    } else {
        ((void(__thiscall *)(Vec3 *, void **, void **))FUN_00aea5d0)(&o->m_vec, end, &v);
    }

    if (v)
        ((void(__thiscall *)(void *))(*(void ***)v)[1])(v);
}

// @ 0x00cee890
void *__fastcall FUN_00cee890(VecObj18 *o, void *edx, u8 flags)
{
    (void)edx;
    o->m_vtbl00 = (void **)0x1478220;
    if (o->m_vec.mpBegin != o->m_vec.mpEnd)
        ((void(__thiscall *)(Vec3 *, void **, void **))FUN_00e25bd0)
                (&o->m_vec, o->m_vec.mpBegin, o->m_vec.mpEnd);
    if (o->m_owner18)
        ((void(__thiscall *)(void *))(*(void ***)o->m_owner18)[1])(o->m_owner18);
    ((void(__thiscall *)(Vec3 *))FUN_00ae6970)(&o->m_vec);
    if (flags & 1)
        ((void(__cdecl *)(void *))FUN_00f47380)(o);
    return o;
}

// @ 0x00cee8e0
void __stdcall FUN_00cee8e0(float a, int b, float *out)
{
    *out = ((a + 1.0f) * g_169cc10 + (float)b * g_169cc14) + g_169cc18;
}

// @ 0x00cee920
void __stdcall FUN_00cee920(void *obj, void *arg2, float c, void *arg4, float *out)
{
    float f;
    float v;
    (void)arg2;
    (void)arg4;

    f = (float)(((double(__thiscall *)(void *))FUN_00bd7d00)(obj) * g_13eb960 - g_1471064);
    v = (c - f * 0.5f) - g_169cc1c;
    *out = v;
    v = v * g_169cc1c;
    *out = v;
    if (v > 1.0f)
        *out = 1.0f;
    else if (v >= 0.0f) {
        if (v < 0.05f)
            *out = 0.05f;
    } else {
        if (v > -0.05f)
            *out = -0.05f;
        else if (v < -1.0f)
            *out = -1.0f;
    }
}

// @ 0x00cee9c0
void __stdcall FUN_00cee9c0(float a, float b, float *out)
{
    if (a < 0.0f)
        *out = (float)(sin(pow((double)a * g_13eb1bc, g_140c4f0)) * g_1471064 + b);
    else
        *out = (float)(sin(pow((double)a, g_140c4f0)) * g_1471064 + b);
}

// @ 0x00ceea20
void __stdcall FUN_00ceea20(float a, float *p2, float *p3)
{
    *p2 = 0.0f;
    *p3 = 0.0f;
    if (a > 0.3f) {
        *p3 = 1.0f;
        return;
    }
    if (a > -0.3f) {
        float t = a + 0.7f;
        *p3 = t;
        *p2 = 1.0f - t;
        return;
    }
    *p2 = 1.0f;
}

// @ 0x00ceea90
void __stdcall FUN_00ceea90(float a, float *out)
{
    float v;
    float t;
    *out = 0.0f;
    t = (a - g_169cc24) * g_169cc28;
    t = -t;
    v = t + g_169cc2c;
    *out = v;
    if (v <= 0.0f)
        *out = 0.0f;
}

// @ 0x00ceead0
double __stdcall FUN_00ceead0(void *a, int b, float c)
{
    double p;
    double r;
    (void)a;

    p = pow((double)b, g_140c4f0);
    r = ((double)c * g_1486110 + p * g_1471064) * g_14853bc;
    if (r < 1.0)
        r = g_1485720;
    return r;
}

// @ 0x00ceeb20
float __stdcall FUN_00ceeb20(void *a, int b, float c)
{
    float v;
    (void)a;

    v = (((c + 0.5f) * 600.0f) / ((float)b + 40.0f)) * 2.0f + 1.0f;
    if (v < 1.0f)
        v = 1.0f;
    return v;
}

// @ 0x00ceeb80
float __stdcall FUN_00ceeb80(float a, float b, float c)
{
    float v;

    v = ((g_169cc0c * b) * (c + 3.0f)) * 0.2f;
    if (c == 1.0f)
        v = (v * 2.0f) * 0.33333334f;
    if (a > 4000.0f)
        a = 4000.0f;
    v = v - a;
    if (v < 2000.0f)
        v = 2000.0f;
    else if (v > 16000.0f)
        v = 16000.0f;
    return v;
}

// @ 0x00ceec10
void __stdcall FUN_00ceec10(u32 a1, float a2, float a3, float a4, u32 a5, u32 a6, u32 a7)
{
    ((void(__cdecl *)(u32, float, float, float, u32, u32, u32))FUN_004e7460)
            (a1, a2, a3, a4, a5, a6, a7);
}

// @ 0x00ceec50
int __stdcall FUN_00ceec50(void *unused)
{
    (void)unused;
    __asm { cvtss2si eax, dword ptr [g_169cc58] }
}

namespace SP {
namespace nCityGameFormulas {
void LoadFormulas();
}
}

// @ 0x00ceec60
void SP::nCityGameFormulas::LoadFormulas()
{
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0x76a22983, 0, &g_169c340);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0xacb97b49, 0, &g_169c3d8);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0x58eee579, 0, &g_169c470);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0xe0fc6df9, 0, &g_169c508);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0x12a50d5f, 0, &g_169c5a0);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0x3d7b29fa, 0, &g_169c2a8);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0xdbe48be7, 0, &g_169c638);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0x027b0c3c, 0, &g_169c6d0);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0xdb334a60, 0, &g_169c768);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0x2278cc41, 0, &g_169c800);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0xe86722a6, 0, &g_169c930);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0xfe791351, 0, &g_169c898);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0xb3a05c62, 0, &g_169c9c8);
}

// @ 0x00ceed50
void __fastcall FUN_00ceed50(void *self, void *edx, void *a, int *out)
{
    float x;
    float r;
    double limit;
    (void)self;
    (void)edx;

    x = (float)(((double(__thiscall *)(void *))FUN_00bd7d00)(a) * g_13eb960);
    r = (float)((double(__thiscall *)(void *))FUN_009360d0)(&g_sMathRandom);
    limit = pow((double)x, g_13f5628) + g_140f398;
    if (r < limit)
        *out = 1;
    else
        *out = 0;
}

// @ 0x00ceedb0
void __stdcall FUN_00ceedb0(float a, int *out)
{
    float v;

    if (a > 0.0f)
        v = g_169cc30 + a;
    else
        v = (a + 1.0f) * g_169cc30;

    if (v > 0.0f) {
        v = (float)(g_1488874 + (double)v);
        double r = ((double(__thiscall *)(void *))FUN_009360d0)(&g_sMathRandom);
        if (r < (double)v) {
            *out = 1;
            return;
        }
    }
    *out = 0;
}

// @ 0x00ceee30
double __stdcall FUN_00ceee30(void *city, void *b)
{
    unsigned int savedEcx;
    volatile float result;
    __declspec(align(16)) unsigned char savedXmm[16];

    __asm {
        mov savedEcx, ecx
        movups xmmword ptr [savedXmm], xmm0
    }

    if (*(u8 *)((u8 *)b + 0x89) == 0) {
        u32 u4 = ((u32(__thiscall *)(void *))(*(void ***)city)[0x4c / 4])(city);
        u32 u5 = ((u32(__thiscall *)(void *))(*(void ***)b)[0x4c / 4])(b);
        void *rm = FUN_00b3d2c0();
        int r = ((int(__thiscall *)(void *, u32, u32, u32))FUN_00d00a70)(rm, u5, u4, 1);
        if (r <= 1) {
            result = 0.0f;
            goto done;
        }
    }

    {
        u8 *sub = (u8 *)city + 0x120;
        char c = ((char(__thiscall *)(void *))(*(void ***)sub)[0x58 / 4])(sub);
        if (c != 0) {
            if (!((char(__thiscall *)(void *))FUN_00bef8a0)(b)) {
                result = 0.0f;
                goto done;
            }
            result = 1.0f;
            goto done;
        }
    }

    {
        int r = ((int(__thiscall *)(void *, u32, u32, u32))FUN_00d00a70)
                (FUN_00b3d2c0(),
                 ((u32(__thiscall *)(void *))(*(void ***)city)[0x4c / 4])(city),
                 ((u32(__thiscall *)(void *))(*(void ***)b)[0x4c / 4])(b),
                 1);
        if (r >= 3) {
            result = 1.0f;
            goto done;
        }
        if (*(u8 *)((u8 *)b + 0x89) == 0 || r != 2) {
            result = 0.0f;
            goto done;
        }

        {
            void *civ = ((void *(__thiscall *)(void *))FUN_00bd9bf0)(city);
            if (*(u8 *)((u8 *)civ + 0x8a) != 0) {
                result = 0.0f;
                goto done;
            }
        }

        {
            float f = ((float(__thiscall *)(void *, u32, u32, u32))FUN_00d00a10)
                        (FUN_00b3d2c0(),
                         ((u32(__thiscall *)(void *))(*(void ***)city)[0x4c / 4])(city),
                         ((u32(__thiscall *)(void *))(*(void ***)b)[0x4c / 4])(b),
                         1);

            void *nm = FUN_00b3d300();
            void **list = (void **)((void *(__thiscall *)(void *))FUN_00b25ca0)(nm);
            void **begin = (void **)list[0];
            void **end = (void **)list[1];
            int count = (int)(end - begin);
            int i;

            for (i = 0; i < count; ++i) {
                void *pi = begin[i];
                u32 a = ((u32(__thiscall *)(void *))(*(void ***)city)[0x4c / 4])(city);
                u32 bb = ((u32(__thiscall *)(void *))(*(void ***)pi)[0x4c / 4])(pi);
                if (bb != a && pi != b && *(u8 *)((u8 *)pi + 0x8a) == 0) {
                    float f2 = ((float(__thiscall *)(void *, u32, u32, u32))FUN_00d00a10)
                                (FUN_00b3d2c0(),
                                 ((u32(__thiscall *)(void *))(*(void ***)pi)[0x4c / 4])(pi),
                                 ((u32(__thiscall *)(void *))(*(void ***)b)[0x4c / 4])(b),
                                 1);
                    if (f < f2) {
                        result = 0.0f;
                        goto done;
                    }
                }
            }
        }
        result = 1.0f;
        goto done;
    }

done:
    __asm {
        mov ecx, savedEcx
        movups xmm0, xmmword ptr [savedXmm]
    }
    return (double)result;
}

// @ 0x00ceefd0
void __stdcall FUN_00ceefd0(float a, float *p2, float *p3)
{
    int i = (int)a;
    float v;
    float *src;
    float w;

    if (i < 100)
        i = (i / 10 + 1) * 10;
    v = ((float)i * g_169cc38) * 0.01f;
    *p3 = v;
    if (g_169cc34 > v)
        src = &g_169cc34;
    else
        src = p3;
    *p3 = *src;
    w = a - g_169cc3c;
    *p2 = w;
    if (w < 0.0f)
        *p2 = 0.0f;
}
