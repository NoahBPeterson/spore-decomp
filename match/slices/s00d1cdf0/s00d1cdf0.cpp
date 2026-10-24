// slice s00d1cdf0 = 0x00d1cdf0..0x00d1df00
// SP Simulator rotation modes: the cRotationBall / cRotationRing game-data
// subclasses (construct / destruct / serialise / model handoff / transform) and
// the two cGameEditModeStrategy hooks that run on the simulation tick and on
// posted messages.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Notation: `// @ 0x<va>` markers above each function; callee declarations carry
// the retail address in a trailing comment.

typedef unsigned int   uint;
typedef unsigned char  u8;
typedef unsigned short u16;

// ---------------------------------------------------------------------------
// low level services / globals
// ---------------------------------------------------------------------------
void  operator_delete_array(void* p);                     // 0x00f47380
void  __cdecl memcpy_(void* d, const void* s, uint n);    // 0x011e0744
void  __cdecl memset_(void* d, int v, uint n);            // 0x011e073e
extern "C" unsigned int __cdecl strlen(const char* s);

extern char  gEmptyStr16[];      // 0x01667bac  shared eastl empty string
extern char  gEmptyStr16b[];     // 0x01667bad  &gEmptyStr16 + 1
extern void* gCurrentRot_169dda0; // 0x0169dda0
extern void* gCurrentRot_169dda4; // 0x0169dda4
extern float gDefVec_169dd88;    // 0x0169dd88  default (1,0,0)-ish vector
extern float gDefVec_169dd8c;    // 0x0169dd8c
extern float gDefVec_169dd90;    // 0x0169dd90
extern float gDefUp_169dd94;     // 0x0169dd94
extern float g_c5_1486110;       // 0x01486110  5.0f
extern float g_c1_1485720;       // 0x01485720  1.0f
extern float g_c10_1473c70;      // 0x01473c70  10.0f
extern uint  gEditState_169dca4; // 0x0169dca4

// constructors / destructors of the shared bases (this in ECX)
void __fastcall cGameData_ctor(void* self);         // 0x00b18660
void __fastcall cSpatialObject_ctor(void* self);    // 0x00c89630
void __fastcall cSpatialObject_dtor(void* self);    // 0x00c8a420
void __fastcall cGameData_dtor(void* self);         // 0x00b184c0
struct cGameData {
    void* mpVtbl_00;
    void* mpVtbl_04;
    void Write(void* stream);      // 0x00b18590  (external)
    void Read(void* stream);       // 0x00b18600  (external)
};
void* __stdcall FUN_00b18460(int tag);              // 0x00b18460  tag cast helper
int   __cdecl FUN_00e82280(void);                   // 0x00e82280
void* __cdecl FUN_0059aed0(float* out, const float* def, void* m); // 0x0059aed0
int   __cdecl WriteUint32(void* s, const void* p, int n, int f);   // 0x0093aa70
int   __cdecl ReadInt32(void* s, void* p, int n, int f);           // 0x0093a780

// ---------------------------------------------------------------------------
// vtable-call helpers (this in ECX, returned through the matching convention)
// ---------------------------------------------------------------------------
typedef void   (__thiscall *VFn0) (void*);
typedef void*  (__thiscall *VFnR) (void*);
typedef void   (__thiscall *VFn1) (void*, void*);
typedef void*  (__thiscall *VFnR1)(void*, void*);
typedef void   (__thiscall *VFn2) (void*, void*, void*);
typedef void   (__thiscall *VFn2F)(void*, void*, float);
typedef int    (__thiscall *VFnI) (void*);
typedef int    (__thiscall *VFnI1)(void*, void*);
typedef double (__thiscall *VFnD) (void*);

#define VSLOT(o, off) (*(void**)((char*)(*(void**)(o)) + (off)))

// ---------------------------------------------------------------------------
// shared sub-objects
// ---------------------------------------------------------------------------
struct cSpatialObject {
    void* mpVtbl_00;             // +0x00  (0x1479fd0 / 0x147a128)
};

struct cGameModel {              // the object behind mpModel_108
    void* mpVtbl_00;             // +0x00
    u8    mPad_04[0x6b];         // +0x04
    u8    mbFlag_6f;             // +0x6f
    u8    mPad_70[0x14];         // +0x70
    float mf_84;                 // +0x84
};

struct EaString {                // eastl::basic_string<char>
    char* mpBegin_00;
    char* mpEnd_04;
    char* mpCap_08;
    void SetEmpty() { mpBegin_00 = gEmptyStr16; mpEnd_04 = gEmptyStr16; mpCap_08 = gEmptyStr16b; }
    void FreeIfOwned() {
        if (mpCap_08 - mpBegin_00 > 1 && mpBegin_00 != 0)
            operator_delete_array(mpBegin_00);
    }
    void assign(const char* first, const char* last);   // 0x00454cb0  (external)
};

// ---------------------------------------------------------------------------
// the shared rotation-object layout
// ---------------------------------------------------------------------------
struct cRotationRing;

struct cRotationObj {
    void*     mpVtbl_00;          // +0x000
    void*     mpVtbl_04;          // +0x004
    u8        mPad_08[0x2c];      // +0x008
    cSpatialObject mSpatial_34;   // +0x034
    u8        mPad_38[0x9c];      // +0x038
    void*     mpRuntime_0d4;      // +0x0d4  runtime/frame object
    u8        mPad_d8[0x4];       // +0x0d8
    char*     mpStr2Begin_dc;     // +0x0dc
    char*     mpStr2End_e0;       // +0x0e0
    u8        mPad_e4[0x24];      // +0x0e4
    cGameModel* mpModel_108;      // +0x108  current model (refcounted)
    u8        mPad_10c[0x4];      // +0x10c
    EaString  mName_110;          // +0x110
    u8        mPad_11c[0x4];      // +0x11c
    uint      mn_120;             // +0x120
    uint      mn_124;             // +0x124
    uint      mn_128;             // +0x128
    float     mf_12c;             // +0x12c
    void*     mp_130;             // +0x130
};

struct cRotationBall : cRotationObj {
    void* Cast(int tag);
    char  Write(void* stream);
    char  Read(void* stream);
    void* GetDefaultVec();
    void* SetThing5c(void* v);
    int   IsFlagSet();
    void  SetFlag(u8 v);
    void  SetThing64(void* v, float f);
    bool  IsCurrent();
    double GetRadius();
    void  SetModel(cGameModel* m, void* p);
    cRotationBall* InitBall();
    void  FiniBall();
    void  GetWorldPos(float* out);
};

struct cRotationRing : cRotationObj {
    void* Cast(int tag);
    char  Write(void* stream);
    void* GetDefaultVec2();
    void* SetThing6c(void* v);
    char  GetFlagR();
    void  CopyTo(EaString* dst);
    void  SetNameFromCStr(const char* s);
    cRotationRing* InitRing();
    void  FiniRing();
};

// ===========================================================================
// rotation-object strategy hooks (cGameEditModeStrategy)
// ===========================================================================
extern void* gListSrcA;              // 0x00cd7d10
extern void* gListSrcB;              // 0x00d3d420
extern void* gListSrcC;              // 0x00ace070
extern void* gListSrcD;              // 0x00b1e500

extern void* FUN_00b3d230(void);                 // SP::NounManager / App
extern void* FUN_00b3d240(void);
extern void* FUN_00b3d320(void);
extern void  FUN_00b3d3b0(void);
extern void  FUN_00b3d3b0v(void*);
extern void  FUN_00b3d3c0(void);
extern void  FUN_00b3d440(void*);
extern void  FUN_00b3d440x(void);
extern void  FUN_00b2ed10(void);
extern void  FUN_00b2f140(void);
extern void  FUN_00b0c190(void*);
extern void  FUN_00b781d0(void);
extern void  FUN_00b2ec80(void*);
extern void  FUN_00b2f350(void*);
extern void  FUN_00b01db0(void*);
extern void  FUN_00b0b150(void);
extern void  FUN_00b79aa0(void);
extern void* FUN_00b5b820(void);
extern void  FUN_00ba0770(void*);
extern void* FUN_00bc30b0(void);
extern char  FUN_00b7ec40(void);
extern void  FUN_00bc2f00(float, float*);
extern void  FUN_00b3d240x(void*);
extern void  FUN_00b76d20(float*, void*, void*, void*, void*);
extern void  FUN_00b5e9a0(void*);
extern void  FUN_00bc40f0(void*);
extern void* FUN_00b01db0p(void);
extern void  FUN_00c83c90(void*, void*, void*);
extern char  FUN_00dc6640(void*, void*);
extern void  FUN_00bab900(void*, void*);
extern void* SP_PlanetModel(void);
extern void* SP_App(void);
extern void* SP_GetCurrentGameMode(void);
extern void* SP_GetGameDataVector(void*, void*, void*, void*, void*, int);
extern void  FUN_00b3d3x(void);
extern void  FUN_00ba0770v(void*);
extern void  FUN_00b0c1(void*);

struct cGameEditModeStrategy {
    u8    mPad_00[0x24];
    void* mp_24;                  // +0x24  input strategy
    void* mp_28;                  // +0x28
    u8    mPad_2c[0x14];
    void** mpVec_40;              // +0x40
    void** mpVecEnd_44;           // +0x44
    void** mpVecCap_48;           // +0x48
    void HandleSimulationUpdate(float dt);
};

void __fastcall SetPlanetInput(void* strategy, void* planet);  // 0x00b3d240-ish

extern float gDefVec_169dd94;
extern uint  gCachedFlag_169dd84;
extern float gCached_169dd78;
extern float gCached_169dd7c;
extern float gCached_169dd80;
void __cdecl matrix33_ctor(void* out, const void* up);
extern void* sLastLoadedScenario;
static void* inner_24(void* p) { return *(void**)((char*)p + 0x24); }

// @ 0x00d1cdf0  cGameEditModeStrategy::HandleSimulationUpdate
void cGameEditModeStrategy::HandleSimulationUpdate(float dt)
{
    float q2[3];
    int ms = (int)(dt * 1000.0f);
    void* nm = FUN_00b3d230();
    void* list = SP_GetGameDataVector(nm, gListSrcA, gListSrcB, gListSrcC, gListSrcD, 0x36be27e);
    void** begin = *(void***)((char*)list + 4);
    void** end   = *(void***)((char*)list + 8);
    if ((((char*)mpVecEnd_44 - (char*)mpVec_40) ^ ((char*)end - (char*)begin)) & ~3u) {
        for (void** it = begin; it != end; ++it) {
            void* obj = *it;
            if (obj && !(*(VFnI)VSLOT(obj, 0x2c))(obj)
                && !FUN_00dc6640(&mpVec_40, &ms)) {
                void* sp = (void*)((char*)obj + 0x34);
                if (sp) (*(VFn0)VSLOT(sp, 0xbc))(sp);
                void** e = mpVecEnd_44;
                if (e < mpVecCap_48) {
                    mpVecEnd_44 = e + 1;
                    if (e) {
                        *e = sp;
                        if (sp) (*(VFn0)VSLOT(sp, 0xbc))(sp);
                    }
                } else {
                    FUN_00bab900(e, &sp);
                }
                if (sp) (*(VFn0)VSLOT(sp, 0xc0))(sp);
            }
        }
    }
    void** it = mpVec_40;
    if (it != mpVecEnd_44) {
        void** nx = it + 1;
        do {
            void* o = *it;
            void* t = 0;
            if (o) t = (void*)(*(VFnR1)VSLOT(o, 0xb8))(o, (void*)0x17f243b);
            if (!o || !t || (*(VFnI)VSLOT(t, 0x2c))(t)) {
                if (nx < mpVecEnd_44) FUN_00c83c90(nx, mpVecEnd_44, it);
                mpVecEnd_44 = (void**)((char*)mpVecEnd_44 - 4);
                void* last = *mpVecEnd_44;
                if (last) (*(VFn0)VSLOT(last, 0xc0))(last);
            } else {
                ++it; ++nx;
            }
        } while (it != mpVecEnd_44);
    }
    if (gEditState_169dca4 == 1) {
        FUN_00b3d3b0();
        FUN_00b2ed10();
        FUN_00b3d3b0();
        FUN_00b2f140();
        FUN_00b3d440x();
        FUN_00b0c1(0);
        FUN_00b3d3c0();
        FUN_00b781d0();
        gEditState_169dca4 = 2;
    } else if (gEditState_169dca4 == 2) {
        gEditState_169dca4 = 3;
    } else if (gEditState_169dca4 == 3) {
        void* input = mp_24;
        void* planet = SP_PlanetModel();
        if (input && *(void**)((char*)planet + 0x24) != 0) {
            void* pm = (*(VFnR)VSLOT(*(void**)((char*)planet + 0x24), 8))(*(void**)((char*)planet + 0x24));
            if (*(int*)((char*)pm + 0xc) != 0)
                SetPlanetInput(input, (char*)pm + 8);
        }
        FUN_00b3d3b0();
        FUN_00b2ec80(0);
        void* m = FUN_00b5b820();
        FUN_00b3d3b0v(m);
        FUN_00b2f350(m);
        void* gm = SP_GetCurrentGameMode();
        FUN_00b3d440(gm);
        FUN_00b01db0(gm);
        FUN_00b3d440x();
        FUN_00b0b150();
        FUN_00b3d3c0();
        FUN_00b79aa0();
        gEditState_169dca4 = 0;
        FUN_00ba0770v(FUN_00b5b820());
    }
    int have = (int)FUN_00bc30b0();
    if (have != 0) {
        SP_PlanetModel();
        if (FUN_00b7ec40()) {
            float f34 = gDefVec_169dd88;
            float f30 = gDefVec_169dd8c;
            float f2c = gDefVec_169dd90;
            float q[4];
            q[0] = 0.0f; q[1] = f34; q[2] = 0.0f; q[3] = f30;
            float tmp = 0.0f;
            matrix33_ctor(&tmp, &gDefVec_169dd94);
            FUN_00bc40f0(q);
            float vec[3]; vec[0] = f34; vec[1] = f30; vec[2] = f2c;
            if ((gCachedFlag_169dd84 & 1) == 0) {
                gCachedFlag_169dd84 |= 1;
                gCached_169dd78 = f34; gCached_169dd7c = f30; gCached_169dd80 = f2c;
            }
            if ((f34 != gDefVec_169dd88 || f30 != gDefVec_169dd8c || f2c != gDefVec_169dd90)
                && (f34 != gCached_169dd78 || f30 != gCached_169dd7c || f2c != gCached_169dd80)) {
                gCached_169dd78 = f34; gCached_169dd7c = f30; gCached_169dd80 = f2c;
                void* b = FUN_00bc30b0();
                float half = *(float*)((char*)b + 0x24) * 0.5f;
                FUN_00bc2f00(half, &tmp);
            }
        }
    }
    void** app = (void**)FUN_00b3d240();
    (*(VFn1)VSLOT(app, 0x44))(app, (void*)1);
    FUN_00b76d20(q2, (void*)0x3f800000, (void*)7, 0, (void*)1);
    void* x = FUN_00b3d230();
    (*(VFn0)VSLOT(x, 0x2c))(x);
    (*(VFn1)VSLOT(mp_28, 4))(mp_28, 0);
    (*(VFn2)VSLOT(mp_24, 8))(mp_24, 0, 0);
    void* y = FUN_00b3d230();
    (*(VFn0)VSLOT(y, 0x30))(y);
    FUN_00b3d230();
    FUN_00b5e9a0(0);
}

// ===========================================================================
// @ 0x00d1d2e0  FUN_00d1d2e0
// ===========================================================================
extern void* FUN_00f48a80(void);                 // 0x00f48a80
extern void* FUN_00401090(void);                 // 0x00401090
extern void* FUN_004df420(void);                 // 0x004df420
extern void  FUN_004cea40(void*, int, void*);    // 0x004cea40
extern int   FUN_004dff50(void*, int, int, int, int); // 0x004dff50
extern void  FUN_00b8d8a0(void*, void*, void*);  // 0x00b8d8a0
extern void* FUN_0067dd50(void);
extern void  SP_SetAvatarSpecies(void*, void*);
extern void* SP_PlanetModelKey(void*);

uint FUN_00d1d2e0(int id, void* msg)
{
    if (id != 0x3d7106a)
        return 0;
    void* objA = (void*)(*(VFnR)VSLOT(FUN_00f48a80(), 0x18))(FUN_00f48a80());
    (void)objA;
    void* objB = FUN_00f48a80();
    (*(VFn1)VSLOT(objB, 0x10))(objB, 0);
    (*(VFn1)VSLOT(SP_App(), 0x28))(SP_App(), 0);
    void* x = FUN_00b3d320();
    *(void**)((char*)x + 0x24) = 0;
    SP_PlanetModel();
    FUN_00b8d8a0(0, 0, (void*)1);
    void* pm = SP_PlanetModel();
    void* inner = inner_24(pm);
    (*(VFn1)VSLOT(inner, 0x8c))(inner, FUN_0067dd50());
    gEditState_169dca4 = 1;
    if (sLastLoadedScenario != 0) {
        void* pk = SP_PlanetModelKey(SP_PlanetModel());
        if (pk) goto done;
    }
    SP_PlanetModel();
    FUN_00b8d8a0(0, 0, (void*)1);
    void* pm2 = SP_PlanetModel();
    void* inner2 = inner_24(pm2);
    (*(VFn1)VSLOT(inner2, 0x8c))(inner2, FUN_0067dd50());
    gEditState_169dca4 = 1;
done:
    void* mgr = FUN_00401090();
    void* sp = FUN_004df420();
    if (sp == 0) {
        void* buf = 0;
        FUN_004cea40(&buf, 1, 0);
        if (FUN_004dff50(0, 0xdada0591, 1, 0, 0) != 0)
            SP_SetAvatarSpecies(mgr, buf);
    }
    return 0;
}

// ===========================================================================
// @ 0x00d1d4d0  cRotationBall::Cast
// ===========================================================================
void* cRotationBall::Cast(int tag)
{
    if (tag == 0x7292112)
        return this;
    if (tag == 0x1186577)
        return this ? (void*)((char*)this + 0x34) : 0;
    return FUN_00b18460(tag);
}

// ===========================================================================
// @ 0x00d1d540  cRotationBall::Write
// ===========================================================================
char cRotationBall::Write(void* stream)
{
    void* impl = (*(VFnR)VSLOT(stream, 0x20))(stream);
    uint tag = 0x7292112;
    void* iface = (*(VFnR)VSLOT(impl, 0x18))(impl);
    WriteUint32(iface, &tag, 1, 0);
    ((cGameData*)this)->Write(stream);
    cGameModel* m = mpModel_108;
    if (m) {
        void* r = (*(VFnR1)VSLOT(m, 0xb8))(m, (void*)0x179c807);
        (*(VFn1)VSLOT(stream, 0x2c))(stream, r);
    } else {
        (*(VFn1)VSLOT(stream, 0x2c))(stream, 0);
    }
    return 1;
}

// ===========================================================================
// @ 0x00d1d5c0  cRotationBall::GetWorldPos
// ===========================================================================
void cRotationBall::GetWorldPos(float* out)
{
    if (!mpModel_108) {
        out[0] = gDefVec_169dd88;
        out[1] = gDefVec_169dd8c;
        out[2] = gDefVec_169dd90;
        return;
    }
    float* a = (float*)(*(VFnR)VSLOT(mpModel_108, 0x2c))(mpModel_108);
    float ax = a[0], ay = a[1], az = a[2];
    void* mtx = (*(VFnR)VSLOT(mpModel_108, 0x30))(mpModel_108);
    float local[3];
    float* b = (float*)FUN_0059aed0(local, &gDefUp_169dd94, mtx);
    float bx = b[0], by = b[1], bz = b[2];
    void* r = (*(VFnR)VSLOT(mpModel_108, 0xac))(mpModel_108);
    if (r) {
        double s = (*(VFnD)VSLOT(mpModel_108, 0x34))(mpModel_108) * *(float*)((char*)r + 0x84);
        float fs = (float)s;
        ax = bx * fs + ax;
        ay = by * fs + ay;
        az = bz * fs + az;
    }
    out[0] = bx * g_c10_1473c70 + ax;
    out[1] = by * g_c10_1473c70 + ay;
    out[2] = bz * g_c10_1473c70 + az;
}

// ===========================================================================
// @ 0x00d1d740  cRotationBall::Read
// ===========================================================================
char cRotationBall::Read(void* stream)
{
    void* impl = (*(VFnR)VSLOT(stream, 0x20))(stream);
    int tag = 0;
    void* iface = (*(VFnR)VSLOT(impl, 0x18))(impl);
    ReadInt32(iface, &tag, 1, 0);
    ((cGameData*)this)->Read(stream);
    void* obj = 0;
    (*(VFn2)VSLOT(stream, 0x28))(stream, (void*)0x179c807, &obj);
    if (obj) {
        cGameModel* casted = (cGameModel*)(*(VFnR1)VSLOT(obj, 0xc))(obj, (void*)0x1186577);
        cGameModel* old = mpModel_108;
        if (casted != old) {
            if (casted) (*(VFn0)VSLOT(casted, 0xbc))(casted);
            mpModel_108 = casted;
            if (old) (*(VFn0)VSLOT(old, 0xc0))(old);
        }
    } else {
        cGameModel* old = mpModel_108;
        if (old) {
            mpModel_108 = 0;
            (*(VFn0)VSLOT(old, 0xc0))(old);
        }
    }
    if (obj) (*(VFn0)VSLOT(obj, 4))(obj);
    return 1;
}

// ===========================================================================
// @ 0x00d1d810  cRotationBall::InitBall
// ===========================================================================
cRotationBall* cRotationBall::InitBall()
{
    cGameData_ctor(this);
    cSpatialObject* sp = &mSpatial_34;
    cSpatialObject_ctor(sp);
    mpVtbl_00 = (void*)0x147a0a8;
    mpVtbl_04 = (void*)0x147a094;
    sp->mpVtbl_00 = (void*)0x1479fd0;
    mpModel_108 = 0;
    mName_110.SetEmpty();
    mn_124 = 0x2f4e681b;
    mn_128 = 0x40606000;
    mn_120 = 0x0ca40c72;
    return this;
}

// ===========================================================================
// @ 0x00d1d930  cRotationBall::GetDefaultVec
// ===========================================================================
void* cRotationBall::GetDefaultVec()
{
    void* rt = mpRuntime_0d4;
    if (rt)
        return (*(VFnR)VSLOT(rt, 0x2c))(rt);
    return (void*)&gDefVec_169dd88;
}

// ===========================================================================
// @ 0x00d1d950  cRotationBall::SetThing5c
// ===========================================================================
void* cRotationBall::SetThing5c(void* v)
{
    void* rt = mpRuntime_0d4;
    (*(VFn1)VSLOT(rt, 0x5c))(rt, v);
    return v;
}

// ===========================================================================
// @ 0x00d1d990  cRotationBall::IsFlagSet
// ===========================================================================
int cRotationBall::IsFlagSet()
{
    cGameModel* m = mpModel_108;
    if (m && m->mbFlag_6f != 0)
        return 1;
    return 0;
}

// ===========================================================================
// @ 0x00d1d9b0  cRotationBall::SetFlag
// ===========================================================================
void cRotationBall::SetFlag(u8 v)
{
    mpModel_108->mbFlag_6f = v;
}

// ===========================================================================
// @ 0x00d1d9e0  cRotationBall::SetThing64
// ===========================================================================
void cRotationBall::SetThing64(void* v, float f)
{
    void* rt = mpRuntime_0d4;
    (*(VFn2F)VSLOT(rt, 0x64))(rt, v, f);
}

// ===========================================================================
// @ 0x00d1da10  cRotationRing::SetThing6c
// ===========================================================================
void* cRotationRing::SetThing6c(void* v)
{
    void* rt = mpRuntime_0d4;
    (*(VFn1)VSLOT(rt, 0x6c))(rt, v);
    return v;
}

// ===========================================================================
// @ 0x00d1da60  cRotationBall::FiniBall
// ===========================================================================
void cRotationBall::FiniBall()
{
    cSpatialObject* sp = &mSpatial_34;
    mpVtbl_00 = (void*)0x147a0a8;
    mpVtbl_04 = (void*)0x147a094;
    sp->mpVtbl_00 = (void*)0x1479fd0;
    mName_110.FreeIfOwned();
    if (mpModel_108)
        (*(VFn0)VSLOT(mpModel_108, 0xc0))(mpModel_108);
    cSpatialObject_dtor(sp);
    cGameData_dtor(this);
}

// ===========================================================================
// @ 0x00d1dac0  cRotationRing::SetNameFromCStr
// ===========================================================================
void cRotationRing::SetNameFromCStr(const char* s)
{
    mName_110.assign(s, s + strlen(s));
}

// ===========================================================================
// @ 0x00d1db10  cRotationRing::Cast
// ===========================================================================
void* cRotationRing::Cast(int tag)
{
    if (tag == 0x2ee8eeb)
        return this;
    if (tag == 0x1186577)
        return this ? (void*)((char*)this + 0x34) : 0;
    return FUN_00b18460(tag);
}

// ===========================================================================
// @ 0x00d1db40  cRotationBall::SetModel
// ===========================================================================
void cRotationBall::SetModel(cGameModel* m, void* p)
{
    cGameModel* old = mpModel_108;
    if (m != old) {
        if (m) (*(VFn0)VSLOT(m, 0xbc))(m);
        mpModel_108 = m;
        if (old) (*(VFn0)VSLOT(old, 0xc0))(old);
    }
    if (!m)
        (*(VFn1)VSLOT(this, 0x6c))(this, 0);
    else
        (*(VFn1)VSLOT(this, 0x6c))(this, p);
}

// ===========================================================================
// @ 0x00d1dba0  cRotationRing::Write
// ===========================================================================
char cRotationRing::Write(void* stream)
{
    void* impl = (*(VFnR)VSLOT(stream, 0x20))(stream);
    uint tag = 0x2ee8eeb;
    void* iface = (*(VFnR)VSLOT(impl, 0x18))(impl);
    WriteUint32(iface, &tag, 1, 0);
    ((cGameData*)this)->Write(stream);
    cGameModel* m = mpModel_108;
    if (m) {
        void* r = (*(VFnR1)VSLOT(m, 0xb8))(m, (void*)0x179c807);
        (*(VFn1)VSLOT(stream, 0x2c))(stream, r);
    } else {
        (*(VFn1)VSLOT(stream, 0x2c))(stream, 0);
    }
    return 1;
}

// ===========================================================================
// @ 0x00d1dc20  cRotationRing::InitRing
// ===========================================================================
cRotationRing* cRotationRing::InitRing()
{
    cGameData_ctor(this);
    cSpatialObject* sp = &mSpatial_34;
    cSpatialObject_ctor(sp);
    mpVtbl_00 = (void*)0x147a200;
    mpVtbl_04 = (void*)0x147a1ec;
    sp->mpVtbl_00 = (void*)0x147a128;
    mpModel_108 = 0;
    mName_110.SetEmpty();
    mp_130 = 0;
    mf_12c = 0.0f;
    mn_124 = 0x2f4e681b;
    mn_128 = 0x40606000;
    mn_120 = 0x0c1ef506;
    return this;
}

// ===========================================================================
// @ 0x00d1dd30  cRotationBall::IsCurrent
// ===========================================================================
bool cRotationBall::IsCurrent()
{
    return gCurrentRot_169dda0 == (void*)this;
}

// ===========================================================================
// @ 0x00d1dd70  cRotationBall::GetRadius
// ===========================================================================
double cRotationBall::GetRadius()
{
    cGameModel* m = mpModel_108;
    if (m)
        return (*(VFnD)VSLOT(m, 0x74))(m) + g_c5_1486110;
    float one = g_c1_1485720;
    return one;
}

// ===========================================================================
// @ 0x00d1ddb0  cRotationRing::GetDefaultVec2
// ===========================================================================
void* cRotationRing::GetDefaultVec2()
{
    void* rt = mpRuntime_0d4;
    if (rt)
        return (*(VFnR)VSLOT(rt, 0x2c))(rt);
    return (void*)&gCurrentRot_169dda4;
}

// ===========================================================================
// @ 0x00d1dde0  cRotationRing::GetFlagR
// ===========================================================================
char cRotationRing::GetFlagR()
{
    return (char)mpModel_108->mbFlag_6f;
}

// ===========================================================================
// @ 0x00d1de10  cRotationRing::FiniRing
// ===========================================================================
void cRotationRing::FiniRing()
{
    cSpatialObject* sp = &mSpatial_34;
    mpVtbl_00 = (void*)0x147a200;
    mpVtbl_04 = (void*)0x147a1ec;
    sp->mpVtbl_00 = (void*)0x147a128;
    mName_110.FreeIfOwned();
    if (mpModel_108)
        (*(VFn0)VSLOT(mpModel_108, 0xc0))(mpModel_108);
    cSpatialObject_dtor(sp);
    cGameData_dtor(this);
}

// ===========================================================================
// @ 0x00d1de70  cRotationRing::CopyTo
// ===========================================================================
void cRotationRing::CopyTo(EaString* dst)
{
    dst->assign(mpStr2Begin_dc, mpStr2End_e0);
}

// ===========================================================================
// @ 0x00d1deb0  cRefObj::Init
// ===========================================================================
struct cRefObj {
    void* mpVtbl_00;              // +0x00
    void* mp_04;                  // +0x04
    void* mp_08;                  // +0x08
    cRefObj* Init(void* o);
    void Destroy();
};

cRefObj* cRefObj::Init(void* o)
{
    mpVtbl_00 = (void*)0x147a2b0;
    mp_04 = 0;
    mp_08 = 0;
    void* old = mp_08;
    if (o != old) {
        if (o) (*(VFn0)VSLOT(o, 0))(o);
        mp_08 = o;
        if (old) (*(VFn0)VSLOT(old, 4))(old);
    }
    return this;
}

// ===========================================================================
// @ 0x00d1df00  cRefObj::Destroy
// ===========================================================================
struct cSPUILayoutObj {
    void Shutdown(unsigned flags);       // 0x00811ad0
};

void cRefObj::Destroy()
{
    if (mp_04) {
        ((cSPUILayoutObj*)mp_04)->Shutdown(1);
        void* c = mp_04;
        if (c) {
            mp_04 = 0;
            (*(VFn0)VSLOT(c, 8))(c);
        }
    }
    if (mp_08) {
        void* c = mp_08;
        mp_08 = 0;
        (*(VFn0)VSLOT(c, 4))(c);
    }
}