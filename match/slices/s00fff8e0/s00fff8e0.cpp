// Decompiled source for bfs3 slice 41 (SP::cSPSimulatorPlayerUFO region).
// Large /O2 functions; raw offsets + vtable slots from the retail disassembly.
#include "types.h"

#define VFN(p, slot) (((void**)*(void**)p)[(slot)/4])

// minimal shared objects
struct Vec4 { float x, y, z, w; };

// @ 0x00cSPLivingUniverse / app helpers
void* GetUniverseContext();                       // 0x01021080
void* FUN_00b3d4d0();                             // 0x00b3d4d0
void* SP_App();                                   // 0x0067dd10
void* FUN_0067dd50();                             // 0x0067dd50
void* SP_EffectsManager();                        // 0x0067ddd0
void* SP_SpaceGameGet();                          // 0x01002bd0
void* SP_EventLog();                              // 0x00b3d3e0
void* SP_GetMissionManager();                     // 0x00feb9f0
void* FUN_0102f810();                             // 0x0102f810
void* FUN_00b3d3d0();                             // 0x00b3d3d0
void* SP_GetActivePlanet();                       // 0x01021260
void* SP_GetActivePlanetRecord();                 // 0x010212a0
void* FUN_00fd9c60();                             // 0x00fd9c60
int   FUN_01004c00(void*);                        // 0x01004c00
void* SP_MessageServer();                         // 0x0067dcc0
void  Matrix3_Assign(void*, void*);               // 0x0041cb40
void* Matrix3FromQuaternion(void*, void*);        // 0x0059c190
void  Locale_SetNumberString(int, int, int*, int); // 0x00881ae0
void  WStr_Format(wchar_t*, const wchar_t*, int, int, int*); // 0x0041e050
void* operator_new(unsigned int, const char*, int, int, int, int);
void  operator_delete(void*);
void  XformMsg_ctor(void*);                       // 0x00434040
void  AddCommodityToInventory(void*, unsigned int); // 0x0103fc10
void  RemoveArtifact(void*, void*, short);        // 0x00c71160
void  FUN_0103a480(void*, void*);                 // 0x0103a480
void* FUN_01005180(void*);                        // 0x01005180
void  FUN_007eb820(void*, int);                   // 0x007eb820
void  FUN_00ae09b0(int, void*, int);             // 0x00ae09b0
void  FUN_00ad79d0(void*, void*);                 // 0x00ad79d0
void  FUN_00ad7ad0(void*);                        // 0x00ad7ad0
void  FUN_0102adf0(void*);                        // 0x0102adf0
void  FUN_01041c50(const char*, int, int);        // 0x01041c50
void  FUN_00fff800(void*, void*, float, float, float);  // 0x00fff800
void  FUN_00fff870(void*, void*, float, float, float);  // 0x00fff870
void  FUN_00fff440(void*, int, int, int);         // 0x00fff440
int   FUN_00ac0810(int, int);                     // 0x00ac0810
int   FUN_00c71e30(void*);                        // 0x00c71e30
int   FUN_00c70fd0(void*, int);                   // 0x00c70fd0
void* FUN_00b8dad0(void*);                        // 0x00b8dad0
int   FUN_00bba100(void*);                        // 0x00bba100

extern int g_15b6244;      // float bits
extern int g_15b6248;
extern int g_15b624c;
extern unsigned char g_15b7434;
extern void* g_16dc0f8;    // current cSpaceInventoryItem*
extern float g_16dc03c, g_16dc040, g_16dc044;
extern float g_16dc018;    // Matrix3 seed
extern float g_13ec5b4;
extern float g_13f0620;

struct cSPSimulatorPlayerUFO;

// @ 0x00fff8e0
void* cSPSimulatorPlayerUFO_GetStarRecordUnderMouse(void* self)
{
    char* t = (char*)self;
    bool bVar4 = true;
    int ctx = (int)((int(__cdecl*)())GetUniverseContext)();
    if (ctx == 2) {
        void* p = FUN_00b3d4d0();
        int st = *(int*)((char*)p + 0x2c);
        if (st != 1 && st != 2) {
            void* app = SP_App();
            void* q = ((void*(__thiscall*)(void*))VFN(app, 0x50))(app);
            void* r = ((void*(__thiscall*)(void*, int))VFN(q, 0x40))(q, 0x1103192);
            if (r != 0) {
                void* m = ((void*(__thiscall*)(void*, int))VFN(r, 0xc))(r, 0x303154cc);
                if (m != 0) {
                    void* hud = FUN_0067dd50();
                    int info = ((int(__thiscall*)(void*))VFN(hud, 0x1c))(hud);
                    void* rec = *(void**)(t + 0x40);
                    if (*(unsigned char*)((char*)rec + 0x74c) == 0
                        || *(int*)((char*)info + 8) != g_15b624c
                        || *(int*)((char*)info + 0xc) != g_15b6248
                        || *(float*)((char*)m + 0) != 0.0f) {
                        g_15b624c = *(int*)((char*)info + 8);
                        g_15b6248 = *(int*)((char*)info + 0xc);
                        float fv = ((float(__thiscall*)(void*))VFN(m, 0x5c))(m);
                        *(float*)&g_15b6244 = fv;
                    } else {
                        bVar4 = false;
                        if (g_15b7434 == 0)
                            return g_16dc0f8;
                    }
                }
            }
        } else {
            g_15b6248 = -1;
            g_15b624c = -1;
        }
    } else {
        g_15b6248 = -1;
        g_15b624c = -1;
    }
    if (bVar4) {
        g_16dc0f8 = 0;
        void* app = SP_App();
        void* q = ((void*(__thiscall*)(void*))VFN(app, 0x50))(app);
        void* v = ((void*(__thiscall*)(void*))VFN(q, 0x1c))(q);
        float a[8] = {0};
        FUN_00fff800(v, v, 0, 0, 0);
        float dx = a[4] - a[0], dy = a[5] - a[1], dz = a[6] - a[2];
        float dist = dx * dx + dy * dy + dz * dz;
        (void)dist;
        (void)0;
    }
    return g_16dc0f8;
}

// @ 0x00fffc90
void FUN_00fffc90(int* param_1, int* param_2, int* param_3,
                  float f1, float f2, float f3)
{
    FUN_00fff800(param_1, param_2, f1, f2, f3);
    for (int* it = param_2; it < param_3; ++it) {
        if (FUN_00ac0810(*it, *param_1)) {
            int* old = (int*)*it;
            if (old != 0)
                ((void(__thiscall*)(void*))VFN(old, 0))(old);
            int* src = (int*)*param_1;
            if (src != old) {
                if (src != 0)
                    ((void(__thiscall*)(void*))VFN(src, 0))(src);
                *it = (int)src;
                if (old != 0)
                    ((void(__thiscall*)(void*, int))VFN(old, 4))(old, 1);
            }
            FUN_00fff440(param_1, 0, (int)param_2 - (int)param_1 >> 2, 0);
            if (old != 0)
                ((void(__thiscall*)(void*, int))VFN(old, 4))(old, 1);
        }
    }
    FUN_00fff870(param_1, param_2, f1, f2, f3);
}

// @ 0x00fffdd0
void FUN_00fffdd0(void* self, int p1, int p2)
{
    (void)p1; (void)p2;
    char* t = (char*)self;
    int ctx = (int)((int(__cdecl*)())GetUniverseContext)();
    int key;
    if (ctx == 0) key = (int)0xb2b0ae6a;
    else if (ctx == 1) key = (int)0x92d2d44f;
    else if (ctx == 2) key = (int)0x3e43e2d6;
    else key = p1;
    void* fx = SP_EffectsManager();
    void* out = 0;
    char ok = ((char(__thiscall*)(void*, int, int, void**))VFN(fx, 0x2c))(fx, key, 0, &out);
    if (ok) {
        ((void(__thiscall*)(void*, int))VFN(out, 8))(out, 0);
        float m[12];
        m[4] = g_16dc03c;
        m[5] = g_16dc040;
        m[6] = g_16dc044;
        m[7] = 1.0f;
        Matrix3_Assign(&m[7], &g_16dc018);
        void* e = *(void**)(t + 0x40);
        void* q = ((void*(__thiscall*)(void*))VFN((char*)e + 0x34, 0x2c))((char*)e + 0x34);
        m[4] = ((float*)q)[0];
        m[5] = ((float*)q)[1];
        m[6] = ((float*)q)[2];
        ((void(__thiscall*)(void*, void*))VFN(out, 0x14))(out, &m[4]);
    }
    if (out != 0)
        ((void(__thiscall*)(void*, int))VFN(out, 4))(out, 1);
    if (out != 0)
        ((void(__thiscall*)(void*, int))VFN(out, 4))(out, 1);
}

// @ 0x01000000
void cSPSimulatorPlayerUFO_AutoAddSpiceToCargo(void* self, int param_2)
{
    char* t = (char*)self;
    (void)t;
    int empire = (int)((int(__cdecl*)())GetUniverseContext)();
    (void)empire;
    (void)param_2;
}

// @ 0x01000520
void cSPSimulatorPlayerUFO_OnPlanetMoveDone(void* self)
{
    (void)self;
    void* planet = SP_GetActivePlanet();
    void* rec = SP_GetActivePlanetRecord();
    if (planet != 0 && rec != 0) {
        FUN_00fd9c60();
        void* sg = SP_SpaceGameGet();
        (void)sg;
    }
    SP_MessageServer();
}
