// Slice s00b34610 -- planet ray picking helpers and the high-resolution texture
// level console command.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

typedef unsigned int  u32;
typedef unsigned char u8;
typedef signed char   s8;

struct Float3 { float x, y, z; };

extern "C" double sqrt(double);
extern "C" int    strcmp(const char*, const char*);
#pragma intrinsic(strcmp)

// ---------------------------------------------------------------------------------------------
// retail globals
// ---------------------------------------------------------------------------------------------
extern Float3      g_kvec;        // 0x0167e9a4 / 0x0167e9a8 / 0x0167e9ac  (invalid hit vector)
extern float       g_scale99;     // 0x013ef480  0.99f
extern float       g_scale80;     // 0x01486374  0.8f
extern float       g_combatLen;   // 0x0143ee00  3.0f
extern const char* g_levelNames[4]; // 0x015695dc
extern void*       g_obj54;       // 0x0167ea54
extern void*       g_obj58;       // 0x0167ea58

// ---------------------------------------------------------------------------------------------
// virtual interfaces (one struct per used slot group so the slot offsets stay exact)
// ---------------------------------------------------------------------------------------------
struct IUnk {                                   // 0x00..0x50, no args -> void*
    virtual void *v00(), *v04(), *v08(), *v0C(), *v10(), *v14(), *v18(), *v1C(),
                 *v20(), *v24(), *v28(), *v2C(), *v30(), *v34(), *v38(), *v3C(),
                 *v40(), *v44(), *v48(), *v4C(), *v50();
};

struct ICfg {                                   // SP::ConfigManager
    virtual void d00(), d04(), d08(), d0C(), d10(), d14(), d18(), d1C(),
                 d20(), d24(), d28();
    virtual void v2C(u32, u32);
    virtual u32  v30(u32);
    virtual u32  v34(u32);
    virtual void d38();
    virtual void v3C();
};

struct IMsg {                                   // SP::MessageServer
    virtual void d00(), d04(), d08(), d0C(), d10(), d14(), d18(), d1C(),
                 d20(), d24(), d28();
    virtual void v2C(void*, u32, u32);
};

struct IModelMgr {                              // SP::ModelManager
    virtual void d00(), d04(), d08(), d0C(), d10(), d14();
    virtual void  v18(u32);
    virtual void* v1C(u32);
};

struct IEffects {                               // SP::EffectsManager
    virtual void d00(), d04(), d08(), d0C(), d10(), d14(), d18(), d1C(),
                 d20(), d24(), d28(), d2C(), d30(), d34(), d38(), d3C(),
                 d40(), d44(), d48(), d4C();
    virtual void  v50(u32);
    virtual void* v54(u32);
};

struct ILight {                                 // SP::LightingManager
    virtual void d00(), d04(), d08(), d0C(), d10(), d14(), d18(), d1C();
    virtual void v20(u32);
};

struct IObjRef {                                // refcounted object: AddRef / Release
    virtual void v00();
    virtual void v04();
};

struct IObj18 {                                 // object with slot 0x18
    virtual void v00(), v04(), v08(), v0C(), v10(), v14(), v18();
};

struct IObj20 {                                 // object with slot 0x20 + refcount
    virtual void v00(), v04(), v08(), v0C(), v10(), v14(), v18(), v1C();
    virtual void v20();
};

struct IGonzWorld {                             // SP::GonzagoModelWorld
    virtual void v00(), v04(), v08(), v0C(), v10(), v14(), v18(), v1C(),
                 v20(), v24(), v28(), v2C(), v30(), v34(), v38(), v3C(),
                 v40(), v44(), v48(), v4C(), v50(), v54(), v58(), v5C(),
                 v60(), v64(), v68(), v6C(), v70(), v74(), v78(), v7C(),
                 v80(), v84(), v88(), v8C(), v90(), v94(), v98(), v9C(),
                 vA0(), vA4(), vA8(), vAC(), vB0(), vB4(), vB8(), vBC(),
                 vC0(), vC4(), vC8(), vCC(), vD0(), vD4(), vD8(), vDC(),
                 vE0(), vE4(), vE8(), vEC(), vF0(), vF4(), vF8(), vFC(),
                 v100(), v104(), v108(), v10C(), v110(), v114(), v118(), v11C(),
                 v120(), v124(), v128(), v12C(), v130(), v134();
    virtual char v138();
};

struct IModel140 {                              // loaded model object
    virtual void v00(), v04(), v08(), v0C(), v10(), v14(), v18(), v1C(),
                 v20(), v24(), v28(), v2C(), v30(), v34(), v38(), v3C(),
                 v40(), v44(), v48(), v4C(), v50(), v54(), v58(), v5C(),
                 v60(), v64(), v68(), v6C(), v70(), v74(), v78(), v7C(),
                 v80(), v84(), v88(), v8C(), v90(), v94(), v98(), v9C(),
                 vA0(), vA4(), vA8(), vAC(), vB0(), vB4(), vB8(), vBC(),
                 vC0(), vC4(), vC8(), vCC(), vD0(), vD4(), vD8(), vDC(),
                 vE0(), vE4(), vE8(), vEC(), vF0(), vF4(), vF8(), vFC(),
                 v100(), v104(), v108(), v10C(), v110(), v114(), v118(), v11C(),
                 v120(), v124(), v128(), v12C(), v130(), v134(), v138(), v13C();
    virtual void v140(int, int, int);
};

struct IObj3C {                                 // object with a 0x3c slot
    virtual void d00(), d04(), d08(), d0C(), d10(), d14(), d18(), d1C(),
                 d20(), d24(), d28(), d2C(), d30(), d34(), d38();
    virtual void* v3C(void*, int);
};

// ---------------------------------------------------------------------------------------------
// modelled classes
// ---------------------------------------------------------------------------------------------
struct cViewer {
    void GetCameraLocationInfo(Float3*, Float3*, u32, u32) const; // 0x007c3d30
    char GetCameraRay(Float3*, Float3*);                          // 0x007c4900
};

struct cPlanetModel {
    void          ProjectRay(Float3* out, Float3* pos, Float3* dir, u32);  // 0x00b82470
    void          FUN_00b82060(Float3* out, const Float3* pos, const Float3* dir); // 0x00b82060
    Float3*       SnapB(Float3* out, const Float3* in, u32);      // 0x00b82970
    float         FUN_00b7e4d0();                                 // 0x00b7e4d0
    float         GetWaterHeight();                               // 0x00b7e390
};

struct CCmd {                                   // high-res texture level command
    u8     pad00[4];
    void*  mStream;                             // +0x04
};

struct ArgArgs {
    const char** MainArguments(void** out, int, int); // 0x00838020
};

struct CAct {                                   // game mode teardown object
    u8       pad00[0x80];
    IObj20*  m80;                               // +0x80
    u8       pad84[0x58];
    IObj20*  mDC;                               // +0xDC
    IObj20*  mE0;                               // +0xE0
    u8       padE4[0x04];
    void*    mE8;                               // +0xE8
    u8       padEC[0x04];
    void*    mF0;                               // +0xF0
    u8       padF4[0x0C];
    IObj20*  m100;                              // +0x100
};

// ---------------------------------------------------------------------------------------------
// retail functions
// ---------------------------------------------------------------------------------------------
extern "C" void*  __cdecl SP_App(void);              // 0x0067dd10
extern "C" void*  __cdecl SP_ConfigManager(void);    // 0x0067dd30
extern "C" void*  __cdecl SP_ModelManager(void);     // 0x0067dd80
extern "C" void*  __cdecl SP_LightingManager(void);  // 0x0067dd90
extern "C" void*  __cdecl SP_MessageServer(void);    // 0x0067dcc0
extern "C" void*  __cdecl SP_EffectsManager(void);   // 0x0067ddd0
extern "C" void*  __cdecl SP_PlanetModel(void);      // 0x00b3d350
extern "C" void*  __cdecl SP_GonzagoModelWorld(void); // 0x00b3d520

Float3* __cdecl SegmentPhysics(Float3* out, const Float3* a, float len,
                               const Float3* b, const Float3* c);      // 0x00699800
char    __cdecl IntersectRaySphere(const Float3* origin, const Float3* dir,
                                   const Float3* center, float radius, float* outT); // 0x005a9c40
char    __cdecl Vector3_NotEqual(const Float3*, const Float3*);         // 0x0041dd30
int     __cdecl CombatLineTest(const Float3* pos, const Float3* dir, float len,
                               void** hit, Float3* out, int param, int flag); // 0x00cb69e0
void    __cdecl ArgOutput(void* stream, const char* fmt, ...);          // 0x00841000
void    __cdecl FUN_00761110(void* p);                                  // 0x00761110

struct CObj3ba0 {
    void FUN_007c3ba0();                                                // 0x007c3ba0
};

// @ 0x00b34610
Float3* __stdcall FUN_00b34610(Float3* out, int flag)
{
    void* app = SP_App();
    void* mgr = ((IUnk*)app)->v50();
    cViewer* viewer = (cViewer*)((IUnk*)mgr)->v1C();
    Float3 pos, dir;
    viewer->GetCameraLocationInfo(&pos, &dir, 0, 0);
    cPlanetModel* pm = (cPlanetModel*)SP_PlanetModel();
    pm->ProjectRay(out, &pos, &dir, 0);
    if (flag == 1 && out->x == g_kvec.x && out->y == g_kvec.y && out->z == g_kvec.z) {
        double d2 = ((double)pos.x * (double)pos.x + (double)pos.y * (double)pos.y) +
                    (double)pos.z * (double)pos.z;
        float dist = (float)sqrt(d2) * 0.99f;
        float w = ((cPlanetModel*)SP_PlanetModel())->FUN_00b7e4d0() * 0.8f;
        const float& m = (dist < w) ? dist : w;
        Float3 tmp;
        *out = *SegmentPhysics(&tmp, &g_kvec, m, &pos, &dir);
        if (out->x != g_kvec.x || out->y != g_kvec.y || out->z != g_kvec.z) {
            *out = *pm->SnapB(&tmp, out, 0);
        }
    }
    return out;
}

// @ 0x00b34790
void __stdcall FUN_00b34790(Float3* out, int flag, float dx, float dy, float dz)
{
    void* app = SP_App();
    void* mgr = ((IUnk*)app)->v50();
    cViewer* viewer = (cViewer*)((IUnk*)mgr)->v1C();
    Float3 pos, dir;
    if (viewer->GetCameraRay(&pos, &dir)) {
        pos.x = pos.x + dx;
        pos.y = pos.y + dy;
        pos.z = pos.z + dz;
        cPlanetModel* pm = (cPlanetModel*)SP_PlanetModel();
        Float3 tmp;
        pm->FUN_00b82060(&tmp, &pos, &dir);
        if (flag == 1 && tmp.x == g_kvec.x && tmp.y == g_kvec.y && tmp.z == g_kvec.z) {
            double d2 = (double)pos.x * (double)pos.x +
                        ((double)pos.y * (double)pos.y + (double)pos.z * (double)pos.z);
            float dist = (float)sqrt(d2) * 0.99f;
            float w = ((cPlanetModel*)SP_PlanetModel())->FUN_00b7e4d0() * 0.8f;
            const float& m = (dist < w) ? dist : w;
            Float3 hit;
            tmp = *SegmentPhysics(&hit, &g_kvec, m, &pos, &dir);
            if (tmp.x != g_kvec.x || tmp.y != g_kvec.y || tmp.z != g_kvec.z) {
                tmp = *pm->SnapB(&hit, &tmp, 0);
            }
        }
        *out = tmp;
        return;
    } else {
        out->x = g_kvec.x;
        out->y = g_kvec.y;
        out->z = g_kvec.z;
        return;
    }
}

// @ 0x00b349b0
Float3* __stdcall FUN_00b349b0(Float3* out, int flag)
{
    Float3 pos, dir;
    if (SP_App() != 0 &&
        ((cViewer*)((IUnk*)((IUnk*)SP_App())->v50())->v1C())->GetCameraRay(&pos, &dir)) {
        cPlanetModel* pm = (cPlanetModel*)SP_PlanetModel();
        Float3 tmp;
        pm->FUN_00b82060(&tmp, &pos, &dir);
        if (flag == 1 && tmp.x == g_kvec.x && tmp.y == g_kvec.y && tmp.z == g_kvec.z) {
            double d2 = (double)pos.x * (double)pos.x +
                        ((double)pos.y * (double)pos.y + (double)pos.z * (double)pos.z);
            float dist = (float)sqrt(d2) * 0.99f;
            float w = ((cPlanetModel*)SP_PlanetModel())->FUN_00b7e4d0() * 0.8f;
            const float& m = (dist < w) ? dist : w;
            Float3 hit;
            tmp = *SegmentPhysics(&hit, &g_kvec, m, &pos, &dir);
            if (Vector3_NotEqual(&tmp, &g_kvec)) {
                tmp = *pm->SnapB(&hit, &tmp, 0);
            }
        }
        float h = pm->GetWaterHeight();
        float t;
        if (IntersectRaySphere(&pos, &dir, &g_kvec, h, &t)) {
            float dz = tmp.z - pos.z;
            float dy = tmp.y - pos.y;
            float dx = tmp.x - pos.x;
            float d2 = dz * dz + dy * dy + dx * dx;
            if ((tmp.x == g_kvec.x && tmp.y == g_kvec.y && tmp.z == g_kvec.z) || d2 > h * h) {
                tmp.x = dir.x * h + pos.x;
                tmp.y = dir.y * h + pos.y;
                tmp.z = dir.z * h + pos.z;
            }
        }
        *out = tmp;
        return out;
    } else {
        out->x = g_kvec.x;
        out->y = g_kvec.y;
        out->z = g_kvec.z;
        return out;
    }
}

// @ 0x00b34c60
Float3* __fastcall FUN_00b34c60(void* ecx_this, void* edx_dummy, Float3* out, int param,
                               int arg)
{
    out->x = g_kvec.x;
    out->y = g_kvec.y;
    out->z = g_kvec.z;
    void* app = SP_App();
    void* mgr = ((IUnk*)app)->v50();
    cViewer* viewer = (cViewer*)((IUnk*)mgr)->v1C();
    if (viewer != 0) {
        Float3 pos, dir;
        if (viewer->GetCameraRay(&pos, &dir)) {
            void* hit = 0;
            if (CombatLineTest(&pos, &dir, g_combatLen, &hit, out, arg, 4) == 3) {
                if (param == 0) {
                    *out = g_kvec;
                } else {
                    Float3 t;
                    *out = *(Float3*)((IObj3C*)ecx_this)->v3C(&t, param);
                }
            }
            if (hit != 0) {
                ((IObjRef*)hit)->v04();
            }
        }
    }
    return out;
}

// @ 0x00b34d60
const char* __stdcall FUN_00b34d60(int arg)
{
    return arg ? "no arguments       display the current level\n"
                 "<off/low/medium/high>  set the high res texture level\n"
               : "set or display the high res texture level";
}

// @ 0x00b34d80
void __fastcall FUN_00b34d80(CCmd* ecx_this, void* edx, void* args)
{
    const char** argv = ((ArgArgs*)args)->MainArguments((void**)&args, 0, 1);
    u32 level;
    if ((int)args == 0) {
        level = ((ICfg*)SP_ConfigManager())->v30(0x8488f95);
        if (level >= 4) level = 0;
        if (((ICfg*)SP_ConfigManager())->v30(0x461709f) < 3) level = 0;
        ArgOutput(ecx_this->mStream,
                  "Current high resolution texture level: %s\n", g_levelNames[level]);
        return;
    }
    if ((int)args != 1) return;
    {
        const char* s = argv[0];
        if (strcmp(s, "off") == 0) {
            if (((ICfg*)SP_ConfigManager())->v30(0x461709f) == 3) {
                u32 v = ((ICfg*)SP_ConfigManager())->v34(0x461709f);
                ((ICfg*)SP_ConfigManager())->v2C(0x461709f, v);
            }
            level = 0;
        } else if (strcmp(s, "low") == 0) {
            level = 1;
        } else if (strcmp(s, "medium") == 0) {
            level = 2;
        } else if (strcmp(s, "high") == 0) {
            level = 3;
        } else {
            ArgOutput(ecx_this->mStream,
                      "Unsupported high resolution texture level: %s\n", s);
            return;
        }
        if (level != 0) {
            if (((ICfg*)SP_ConfigManager())->v30(0x461709f) < 3) {
                ((ICfg*)SP_ConfigManager())->v2C(0x461709f, 3);
            }
            ((ICfg*)SP_ConfigManager())->v2C(0x8488f95, level);
            ((ICfg*)SP_ConfigManager())->v3C();
        }
    }
    ArgOutput(ecx_this->mStream,
              "Current high resolution texture level: %s\n", g_levelNames[level]);
}

// @ 0x00b34ff0
void __fastcall FUN_00b34ff0(CAct* ecx_this, void* edx)
{
    if (ecx_this->m80 != 0) {
        IObj20* p = ecx_this->m80;
        ecx_this->m80 = 0;
        p->v04();
    }
    if (SP_GonzagoModelWorld() != 0) {
        if (((IGonzWorld*)SP_GonzagoModelWorld())->v138() != 0) {
            ((IObj18*)((char*)ecx_this - 8))->v18();
        }
    }
    void* msg = SP_MessageServer();
    if (msg != 0) {
        void* p = (char*)ecx_this - 8;
        void* arg = p ? (void*)((char*)ecx_this - 4) : 0;
        ((IMsg*)msg)->v2C(arg, 0x30c11c7, 0xffffd8f1);
        arg = p ? (void*)((char*)ecx_this - 4) : 0;
        ((IMsg*)msg)->v2C(arg, 0x3047cb34, 0xffffd8f1);
        arg = p ? (void*)((char*)ecx_this - 4) : 0;
        ((IMsg*)msg)->v2C(arg, 0x1a0219e, 0xffffd8f1);
        arg = p ? (void*)((char*)ecx_this - 4) : 0;
        ((IMsg*)msg)->v2C(arg, 0x4b719d4, 0xffffd8f1);
        arg = p ? (void*)((char*)ecx_this - 4) : 0;
        ((IMsg*)msg)->v2C(arg, 0x712924f2, 0xffffd8f1);
        arg = p ? (void*)((char*)ecx_this - 4) : 0;
        ((IMsg*)msg)->v2C(arg, 0x712924f3, 0xffffd8f1);
    }
    if (SP_GonzagoModelWorld() != 0) {
        ((IModelMgr*)SP_ModelManager())->v18(0xeb9968);
    }
    if (ecx_this->mDC != 0) {
        ((IModelMgr*)SP_ModelManager())->v18(0x317ccba);
    }
    if (ecx_this->mE0 != 0) {
        ((IModelMgr*)SP_ModelManager())->v18(0x5de6030);
    }
    void* eff = ((IEffects*)SP_EffectsManager())->v54(0xeb9968);
    if (eff != 0) {
        ((IObjRef*)eff)->v00();
        ((IEffects*)SP_EffectsManager())->v50(0xeb9968);
    }    if (ecx_this->mE8 != 0) {
        ((CObj3ba0*)ecx_this->mE8)->FUN_007c3ba0();
        ecx_this->mE8 = 0;
    }
    if (ecx_this->mF0 != 0) {
        FUN_00761110(ecx_this->mF0);
        ecx_this->mF0 = 0;
    }
    if (((IEffects*)SP_EffectsManager())->v54(0x23541242) != 0) {
        ((IEffects*)SP_EffectsManager())->v50(0x23541242);
    }
    if (((IEffects*)SP_EffectsManager())->v54(0x3701a5c) != 0) {
        ((IEffects*)SP_EffectsManager())->v50(0x3701a5c);
    }
    if (g_obj54 != 0) {
        IModel140* model = (IModel140*)((IModelMgr*)SP_ModelManager())->v1C(0x3fbae24);
        if (model != 0) {
            model->v00();
            model->v140(0, 0, 1);
            model->v140(0, 1, 1);
        }
        if (g_obj54 != 0) {
            IObjRef* o = (IObjRef*)g_obj54;
            g_obj54 = 0;
            o->v04();
        }
        ((ILight*)SP_LightingManager())->v20(0x4a4dea0);
        if (model != 0) {
            model->v04();
        }
    }
    if (g_obj58 != 0) {
        ((IObj20*)g_obj58)->v20();
        if (g_obj58 != 0) {
            IObj20* o = (IObj20*)g_obj58;
            g_obj58 = 0;
            o->v04();
        }
    }
    if (ecx_this->m100 != 0) {
        ecx_this->m100->v20();
        if (ecx_this->m100 != 0) {
            IObj20* o = ecx_this->m100;
            ecx_this->m100 = 0;
            o->v04();
        }
    }
    if (eff != 0) {
        ((IObjRef*)eff)->v04();
    }
}
