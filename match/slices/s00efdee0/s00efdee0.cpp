// slice s00efdee0 -- scenario tutorial / planetary UI helpers (planet camera placement, view
// state, checklist window bridging).
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE  (SSE scalar float math, x87 float returns).
#include "types.h"

extern int*  g_016c7b88;               // 0x016c7b88 (checklist singleton)
extern void* gSimulator;               // 0x016c7aa4
extern void* g_15fd918;                // 0x015fd918
extern int*  g_15ad298;                // 0x015ad298
extern float g_16c7b98, g_16c7b9c, g_16c7ba0, g_15ad29c, g_16c7b8c_unused;
extern uint8_t g_16c7b8c, g_16c7b8d, g_15ad344, g_15acb40;
extern float g_148b6e8, g_15ad2ac, g_13ec4b4, g_1471064, g_1488874;

typedef int  (__thiscall *FN0_i)(void*);
typedef void (__thiscall *FN1_i)(void*, int);
typedef void (__thiscall *FN2_ii)(void*, int, int);
typedef void (__thiscall *FN1_p)(void*, void*);
typedef int  (__thiscall *FN1_ir)(void*, int);
typedef int  (__thiscall *FN2_ip)(void*, int, void*);

// Placeholder objects for the direct thiscall helpers used by this slice.  The
// method names carry the original VA so the difftest resolver maps each
// relocation back to the retail function.
struct PluginObj {
    void  FUN_00b5cde0(int);                            // 0x00b5cde0
    void  FUN_00b11870(void*);                          // 0x00b11870
    void  FUN_00b10760(float, float, float);            // 0x00b10760
    void  FUN_00b0f950(int);                            // 0x00b0f950
    void  FUN_00b10c40(int);                            // 0x00b10c40
    void  FUN_00b148c0(float, float, float, float);     // 0x00b148c0
    void  FUN_00b12dd0(float*, float*, int);            // 0x00b12dd0
    void  FUN_00b13bb0(float*, int);                    // 0x00b13bb0
    void  FUN_00b104c0(float);                          // 0x00b104c0
    void* FUN_00b81630(void*, void*);                   // 0x00b81630
    void* FUN_00b7f190(void*, void*);                   // 0x00b7f190
    void* FUN_00ff3f00();                               // 0x00ff3f00
    int   FUN_00f41420(void*, void*, int, int);         // 0x00f41420
    int   FUN_00f3b9e0(void*, void*, int);              // 0x00f3b9e0
    void* FUN_00f3e8a0(void*);                          // 0x00f3e8a0
    void  FUN_00f3bbd0(void*, int);                     // 0x00f3bbd0
    void  FUN_00f45970();                               // 0x00f45970
    int   FUN_00c64a70(void*);                          // 0x00c64a70
    void  FUN_00b5f950(void*);                          // 0x00b5f950
    void  FUN_00c8ad30(int, int);                       // 0x00c8ad30
    void  FUN_00efd020();                               // 0x00efd020
    void  FUN_00efbbe0(int, int);                       // 0x00efbbe0
    void  FUN_0093a480(int, int);                       // 0x0093a480
    void  FUN_0093a2e0();                               // 0x0093a2e0
    int   FUN_005ff1c0();                               // 0x005ff1c0
    void  FUN_006ffe00(void*);                          // 0x006ffe00
    void  FUN_007c40c0(void*, void*);                   // 0x007c40c0
    void* FUN_007c4010(void*);                          // 0x007c4010
    void  FUN_007c3d30(void*, void*, void*, void*);     // 0x007c3d30
    int   FUN_006ffbd0(void*, float);                   // 0x006ffbd0
    void* FUN_0041e920();                               // 0x0041e920
    int   FUN_00efc570(void*, float);                   // 0x00efc570 (sub-object in EAX)
};

// Thiscall entry points belonging to this slice.
struct Scene {
    void FUN_00efe8d0(int, int);
    void FUN_00efe930(void*);
    bool FUN_00efeae0(int);
    void FUN_00efebb0(void*);
    void FUN_00efec90(void*);
};

void* __cdecl FUN_0067dd10();
void* __cdecl FUN_00b3d250();
extern void* g_15ad348;
extern char  g_15ad2b0;
extern char  g_16c7c28[];

void* __cdecl FUN_00b3d230();
void  __cdecl FUN_00b5cde0(void*);
void* __cdecl FUN_00b11870(void*);
void  __cdecl FUN_00b10760(float, float, float);
void* __cdecl FUN_00b81630(void*, void*);
void* __cdecl SP_PlanetModel();
void* __cdecl FUN_00b7f190(void*, void*, void*);
void* __cdecl FUN_00b12dd0(void*, void*, int);
void* __cdecl FUN_00ff3f00(void*);
void* __cdecl FUN_00b13bb0(void*, int);
void* __cdecl FUN_00b104c0(float);
void* __cdecl FUN_00b148c0(int, int, int, int);
void* __cdecl FUN_0067dd50();
void* __cdecl SP_App();
void* __cdecl FUN_007c4900(void*, void*);
void* __cdecl FUN_00b82620(void*, void*, void*, int);
void* __cdecl FUN_00b3d350();
void* __cdecl FUN_00b3d280();
void* __cdecl FUN_00eeca30(void*);
void* __cdecl FUN_00eebf80(void*);
void* __cdecl FUN_00b18e00(void*);
void* __cdecl FUN_00b0f950(void*, int);
void* __cdecl FUN_00b10c40(void*, int);
void* __cdecl FUN_00b159e0(void*, int);
void* __cdecl FUN_00b326d0_v();
void* __cdecl Property_GetBool();
int   __cdecl FUN_00b326d0_v2();
int   __cdecl FUN_00efd970(void*);
int   __cdecl FUN_00efd020();
int   __cdecl FUN_00ebf5b0();
void* __cdecl FUN_00ed54b0(void*);
void* __cdecl FUN_00ed4e90(void*);
bool  __cdecl FUN_00efe5d0(int);
int   __cdecl FUN_00f35f70(void*);
void* __cdecl FUN_00c8ad30(void*, int);
void* __cdecl FUN_00eef570(void*, void*);
void* __cdecl FUN_00eef4b0(void*);
void* __cdecl FUN_00f3d780(void*);
void* __cdecl FUN_00f3b9e0(void*, void*, int);
void* __cdecl FUN_00f41420(void*, void*, int, int);
void  __cdecl FUN_006ffe00(void*);
void  __cdecl FUN_006ffbd0(void*, int);
int   __cdecl FUN_00efc930();
bool  __cdecl FUN_00efc530(void*);
void* __cdecl FUN_00efcbe0(int);
int   __cdecl FUN_00efc570(void*);
int   __cdecl FUN_00efc5f0(int, float);
bool  __cdecl FUN_00efe630(int, void*);
void* __cdecl FUN_00eec3d0(void*, void*);
void* __cdecl FUN_00eece20(void*);
void  __cdecl FUN_00efe110();

// @ 0x00efe240
int __cdecl FUN_00efe240()
{
    FUN_00efe110();
    int* p = g_15ad298;
    ((FN0_i)((*(void***)p)[0x10]))(p);
    return FUN_00ebf5b0();
}

// @ 0x00efe5d0
__declspec(noinline) bool __cdecl FUN_00efe5d0(int v)
{
    char* g = (char*)g_016c7b88;
    int n = (*(int*)(g + 0x90) - *(int*)(g + 0x8c)) >> 5;
    if (n > 0) {
        int* p = *(int**)(g + 0x8c);
        for (int i = 0; i < n; i++) {
            if (*p == v)
                return true;
            p += 8;
        }
    }
    return false;
}

// @ 0x00efe610
bool __cdecl FUN_00efe610(void* a)
{
    int r = (int)FUN_00eebf80(a);
    return FUN_00efe5d0(r);
}

// @ 0x00efeaa0
int __fastcall FUN_00efeaa0(char* p)
{
    if (*(int*)((char*)g_016c7b88 + 0xc) == 0 && *(char*)(p + 5) == 0)
        return 0;
    return 1;
}

// @ 0x00efeac0
bool __stdcall FUN_00efeac0(int unused)
{
    (void)unused;
    return *(int*)((char*)g_016c7b88 + 4) != 0;
}

// @ 0x00efe630
bool __cdecl FUN_00efe630(int id, void* p)
{
    if (id == (int)0xcf56099a) {
        if (p == 0)
            return false;
        int a = ((FN1_ir)((*(void***)p)[0x2e]))(p, 0x175cdc9);
        if (a == 0 || *(int*)(a + 0x38) == 0) {
            int b = ((FN1_ir)((*(void***)p)[0x2e]))(p, 0x3a25119);
            if (b == 0 || *(int*)(b + 0x134) == 0)
                return false;
        }
        return true;
    }
    if (id == (int)0xe34e8a60)
        return true;
    if (id == 0x5b3d1d0d)
        return true;
    return false;
}

// @ 0x00efe870
int __cdecl FUN_00efe870(int* key)
{
    char* g = (char*)*(void**)((char*)gSimulator + 0x74);
    char* base = *(char**)(g + 0x10);
    int* begin = *(int**)(base + 0x2bf4);
    int* end = *(int**)(base + 0x2bf8);
    int* p = begin;
    while (p != end) {
        if (p[2] == key[0] && p[3] == key[1] && p[4] == key[2])
            return p[0];
        p = (int*)((char*)p + 0x27e8);
    }
    return -1;
}

// @ 0x00efe870 (unused alias)

// ---------------------------------------------------------------------------
// remaining functions (approximate bodies; see partial.txt)
// ---------------------------------------------------------------------------
void* __cdecl FUN_00b5cde0_2();
void  __cdecl FUN_00b10760_2();
void* __cdecl FUN_00b12dd0_2();
void* __cdecl FUN_00b10760_3(float, float, float);
void* __cdecl FUN_00b148c0_2(int,int,int,int);
void  __cdecl FUN_007c40c0(void*, void*);
void* __cdecl FUN_007c4010(void*);
void  __cdecl FUN_006ffbd0_2(void*, int);
void* __cdecl FUN_00b326d0_3();
void* __cdecl FUN_00b18e00_2(void*);
void* __cdecl FUN_00b326d0_4();
int   __cdecl FUN_00efd020_2();
void* __cdecl FUN_00f35f70_2(void*);
void  __cdecl FUN_00efe110_v();

// @ 0x00efdee0
void __cdecl FUN_00efdee0()
{
    void* obj = FUN_00b3d230();
    ((PluginObj*)obj)->FUN_00b5cde0(0xebb801);

    void* app = FUN_0067dd10();
    void* a = (void*)((FN0_i)((*(void***)app)[20]))(app);
    void* b = (void*)((FN0_i)((*(void***)a)[16]))(a);

    void* target = 0;
    if (b != 0) {
        target = (void*)((FN1_ir)((*(void***)b)[3]))(b, 0x11966ed);
        if (target != 0 && *(int*)((char*)target + 0x308) != (int)g_15ad348) {
            ((PluginObj*)target)->FUN_00b11870(g_15ad348);
            ((PluginObj*)target)->FUN_00b10760(0.0f, g_15ad2ac * g_13ec4b4, g_148b6e8);
        }
    }

    char* mgr = *(char**)((char*)gSimulator + 0x74);
    char* base = *(char**)(mgr + 0x10);
    float posA[3];
    float orient[4];
    float radius;
    posA[0] = *(float*)(base + 0x2c30);
    posA[1] = *(float*)(base + 0x2c34);
    posA[2] = *(float*)(base + 0x2c38);
    orient[0] = *(float*)(base + 0x2c3c);
    orient[1] = *(float*)(base + 0x2c40);
    orient[2] = *(float*)(base + 0x2c44);
    orient[3] = *(float*)(base + 0x2c48);
    radius = *(float*)(base + 0x2c4c);

    if (g_16c7b98 == posA[0] && g_16c7b9c == posA[1] && g_16c7ba0 == posA[2]) {
        float vecA[3];
        float* r = (float*)((PluginObj*)FUN_00b3d350())->FUN_00b81630(vecA, &g_15ad2b0);
        posA[0] = r[0];
        posA[1] = r[1];
        posA[2] = r[2];
        float* q = (float*)((PluginObj*)FUN_00b3d350())->FUN_00b7f190(vecA, posA);
        orient[0] = q[0];
        orient[1] = q[1];
        orient[2] = q[2];
        orient[3] = q[3];
        ((PluginObj*)target)->FUN_00b12dd0(posA, orient, 1);
        void* check = ((PluginObj*)*(void**)((char*)gSimulator + 0x74))->FUN_00ff3f00();
        if (check != 0)
            FUN_00efcbe0(1);
    } else {
        ((PluginObj*)target)->FUN_00b12dd0(posA, orient, 1);
        ((PluginObj*)target)->FUN_00b13bb0(posA, 1);
        ((PluginObj*)target)->FUN_00b104c0(radius);
    }
}

// @ 0x00efe110
void __cdecl FUN_00efe110()
{
    char* g = (char*)g_016c7b88;
    if (*(char*)(g + 0xa5) == 0) {
        void* m = FUN_0067dd50();
        void* v = (void*)((FN0_i)((*(void***)m)[7]))(m);
        int dx = *(int*)(g + 0xa8) - *(int*)((char*)v + 8);
        int dy = *(int*)(g + 0xac) - *(int*)((char*)v + 0xc);
        *(char*)(g + 0xa5) = (char)(((dx < 0 ? -dx : dx) > 2 || (dy < 0 ? -dy : dy) > 2) ? 1 : 0);
    }
    void* app = FUN_0067dd10();
    void* viewer = (void*)((FN0_i)((*(void***)app)[22]))(app);
    float cam[2];
    char a[4];
    char b[10];
    ((PluginObj*)viewer)->FUN_007c40c0(a, cam);
    char* list = (char*)((PluginObj*)viewer)->FUN_007c4010(b);
    g_15ad29c = (float)(*(int*)(list + 0xc) - *(int*)(list + 4)) * g_1471064 * cam[0];
    ((PluginObj*)&g_16c7c28)->FUN_006ffe00((char*)viewer + 0xc0);

    char** descSlot = (char**)&cam[0];
    if (g_15fd918 != 0
        && ((FN2_ip)((*(void***)g_15fd918)[9]))(g_15fd918, 0xbc2db1cd, descSlot)
        && *(uint16_t*)(*descSlot + 0x12) == 1) {
        void* val = ((PluginObj*)*descSlot)->FUN_0041e920();
        g_16c7b8c = *(uint8_t*)val;
    }
    if (g_15fd918 != 0
        && ((FN2_ip)((*(void***)g_15fd918)[9]))(g_15fd918, 0xfd290b85, descSlot)
        && *(uint16_t*)(*descSlot + 0x12) == 1) {
        void* val = ((PluginObj*)*descSlot)->FUN_0041e920();
        g_16c7b8d = *(uint8_t*)val;
    }
}

// @ 0x00efe260
void __cdecl FUN_00efe260()
{
    int* p = g_15ad298;
    ((FN0_i)((*(void***)p)[8]))(p);
    char* g = (char*)g_016c7b88;
    void* q = *(void**)(g + 0x10);
    if (q != 0) {
        *(void**)(g + 0x10) = 0;
        ((FN0_i)((*(void***)q)[1]))(q);
    }
    void* r = FUN_00eebf80((void*)0);
    if (r != 0)
        FUN_00ed54b0(r);
    else
        FUN_00ed4e90(0);
}

// @ 0x00efe310
void __cdecl FUN_00efe310(int flag)
{
    void* app = FUN_0067dd10();
    void* a = (void*)((FN0_i)((*(void***)app)[20]))(app);
    void* b = (void*)((FN0_i)((*(void***)a)[14]))(a);
    if (b == 0)
        return;
    void* o = (void*)((FN1_ir)((*(void***)b)[3]))(b, 0x11966ed);
    if (o == 0)
        return;
    void* sim = *(void**)((char*)gSimulator + 0xd4);
    ((FN2_ii)((*(void***)sim)[4]))(sim, 0xf, 0x10);
    ((PluginObj*)o)->FUN_00b0f950(flag);
    void* l = (void*)g_15ad298;
    ((FN0_i)((*(void***)l)[14]))(l);
    void* m = FUN_0067dd50();
    void* vp = (void*)((FN0_i)((*(void***)m)[7]))(m);
    char* g = (char*)g_016c7b88;

    if ((char)flag != 0) {
        ((PluginObj*)(g + 0xb0))->FUN_0093a480(200, 1);
        g = (char*)g_016c7b88;
        *(char*)(g + 0xa5) = 0;
        *(int*)(g + 0xa8) = *(int*)((char*)vp + 8);
        *(int*)(g + 0xac) = *(int*)((char*)vp + 0xc);
        return;
    }

    int dx = *(int*)(g + 0xa8) - *(int*)((char*)vp + 8);
    int dy = *(int*)(g + 0xac) - *(int*)((char*)vp + 0xc);
    if (*(char*)(g + 0xa5) != 0 || (dx < 0 ? -dx : dx) > 2 || (dy < 0 ? -dy : dy) > 2) {
        if ((*(int*)(g + 0xb0) | *(int*)(g + 0xb4)) == 0)
            return;
        if (((PluginObj*)(g + 0xb0))->FUN_005ff1c0() != 0)
            return;
    }

    if (FUN_00efc930() != 0) {
        ((PluginObj*)o)->FUN_00b148c0(0.0f, 0.0f, 0.0f, 0.0f);
        FUN_00efcbe0(0);
    }
    g = (char*)g_016c7b88;
    *(char*)(g + 0xa5) = 1;
    *(int*)(g + 0xac) = 0;
    *(int*)(g + 0xa8) = 0;
    ((PluginObj*)(g + 0xb0))->FUN_0093a2e0();
}

// @ 0x00efe4a0
void __cdecl FUN_00efe4a0(int flag)
{
    void* app = (void*)SP_App();
    void* a = (void*)((FN0_i)((*(void***)app)[0x14]))(app);
    void* b = (void*)((FN0_i)((*(void***)a)[0xe]))(a);
    if (b == 0)
        return;
    void* o = (void*)((FN0_i)((*(void***)b)[3]))(b);
    if (o == 0)
        return;
    if (*(char*)((char*)o + 0x319) == 0 && flag == 0) {
        void* d4 = *(void**)((char*)gSimulator + 0xd4);
        ((FN2_ii)((*(void***)d4)[4]))(d4, 0x13, 0x14);
    }
    FUN_00b10c40(o, flag);
}

// @ 0x00efe510
void __cdecl FUN_00efe510(float f)
{
    void* app = (void*)SP_App();
    void* a = (void*)((FN0_i)((*(void***)app)[0x14]))(app);
    void* b = (void*)((FN0_i)((*(void***)a)[0xe]))(a);
    if (b == 0)
        return;
    void* o = (void*)((FN0_i)((*(void***)b)[3]))(b);
    if (o == 0)
        return;
    (void)f;
}

// @ 0x00efe6a0
int __cdecl FUN_00efe6a0(int param)
{
    int* o = (int*)FUN_00eeca30((void*)param);
    float scale = 1.0f;
    if ((*(uint8_t*)((char*)o + 0x50) & 0x10) == 0)
        scale = ((float (__thiscall*)(void*))(*(void***)o)[28])(o);

    if (g_16c7b8c != 0 && *(uint8_t*)((char*)o + 0x78) != 0)
        return 2;

    void* app = FUN_0067dd10();
    void* viewer = (void*)((FN0_i)((*(void***)app)[22]))(app);
    float vecA[3];
    float vecB[3];
    ((PluginObj*)viewer)->FUN_007c3d30(vecA, vecB, 0, 0);

    float* pos = (float*)((FN0_i)((*(void***)o)[11]))(o);
    float dot = (vecB[2] * (pos[2] - vecA[2]) + vecB[1] * (pos[1] - vecA[1]))
              + vecB[0] * (pos[0] - vecA[0]);
    float* pos2 = (float*)((FN0_i)((*(void***)o)[11]))(o);
    if (((PluginObj*)&g_16c7c28)->FUN_006ffbd0(pos2, scale) == 0x40)
        return 2;

    void* e = (void*)((FN0_i)((*(void***)o)[43]))(o);
    int result;
    if (e == 0 || ((*(uint32_t*)((char*)e + 4) >> 14) & 1) == 0
        || ((*(uint32_t*)((char*)e + 4) >> 18) & 1) != 0) {
        result = 1;
    } else {
        result = FUN_00efc5f0(param, dot);
        if (result == 0) {
            if (((PluginObj*)o)->FUN_00efc570(e, dot) == 0)
                result = 1;
        }
    }

    char local[12];
    FUN_00eec3d0(local, (void*)param);
    int id = (int)FUN_00eece20(local);
    if (result == 1) {
        if (g_16c7b8d == 0 && !FUN_00efe630(id, o))
            return 0;
        float* pf = (float*)param;
        float dot2 = (pf[2] * vecB[1] + pf[3] * vecB[2]) + pf[1] * vecB[0];
        if (-dot2 < 0.0f)
            result = 2;
    }
    return result;
}

// @ 0x00efe8d0
void Scene::FUN_00efe8d0(int a, int b)
{
    ((FN1_i)((*(void***)this)[6]))(this, b == 1);
    if (b != 2)
        ((FN1_i)((*(void***)this)[8]))(this, (b != 0) ? a : 0);
    if (b == 1 && *(int*)((char*)g_016c7b88 + 4) != 0)
        FUN_00efd970(*(void**)((char*)g_016c7b88 + 4));
}

// @ 0x00efe930
void Scene::FUN_00efe930(void* obj)
{
    char* g = (char*)g_016c7b88;
    if (g == 0 || *(int*)(g + 0x20) == 0)
        return;

    if (obj == 0) {
        void* p = *(void**)(g + 0x10);
        if (p != 0) {
            *(void**)(g + 0x10) = 0;
            ((FN0_i)((*(void***)p)[1]))(p);
        }
        ((FN1_i)((*(void***)this)[6]))(this, 0);
    }

    if (FUN_00efc530(obj)) {
        g = (char*)g_016c7b88;
        ((PluginObj*)(g + 0x10))->FUN_00b5f950(obj);
        return;
    }

    g = (char*)g_016c7b88;
    void* old = *(void**)(g + 4);
    bool changed = (old != obj);
    if (changed && old != 0) {
        void* o2 = FUN_00b18e00(old);
        if (o2 != 0)
            ((PluginObj*)o2)->FUN_00c8ad30(0x65640a90, 1);
    }

    if (obj != 0) {
        void* r = (void*)((FN1_ir)((*(void***)obj)[3]))(obj, 0x175cdc9);
        if (r != 0) {
            void* v = *(void**)((char*)r + 0x50);
            if (v != 0) {
                g = (char*)g_016c7b88;
                ((PluginObj*)(g + 4))->FUN_00b5f950(v);
                g = (char*)g_016c7b88;
                ((PluginObj*)(g + 0x10))->FUN_00b5f950(*(void**)(g + 0x28));
                goto after;
            }
        }
    }

    g = (char*)g_016c7b88;
    ((PluginObj*)(g + 4))->FUN_00b5f950(obj);
    g = (char*)g_016c7b88;
    if (*(void**)(g + 0x10) != 0) {
        void* p = *(void**)(g + 0x10);
        *(void**)(g + 0x10) = 0;
        ((FN0_i)((*(void***)p)[1]))(p);
    }

after:
    g = (char*)g_016c7b88;
    if (obj == 0) {
        void* p8 = *(void**)(g + 8);
        if (p8 != 0) {
            *(void**)(g + 8) = 0;
            ((FN0_i)((*(void***)p8)[1]))(p8);
        }
    }

    g = (char*)g_016c7b88;
    void* p4 = *(void**)(g + 4);
    if (p4 != 0)
        FUN_00eef570(p4, g + 0x8c);
    else
        FUN_00eef4b0(g + 0x8c);

    ((PluginObj*)this)->FUN_00efd020();

    if (changed) {
        void* o3 = FUN_00b3d250();
        int val = (obj != 0) ? (int)0xd7614d9d : (int)0x91247de4;
        ((FN2_ii)((*(void***)o3)[25]))(o3, val, 1);
    }
}

// @ 0x00efeae0
bool Scene::FUN_00efeae0(int arg)
{
    char bl = 0;
    void* o = FUN_00eebf80((void*)arg);
    if (o == 0)
        return bl == 0;

    bool flag = (g_15acb40 != 0 && arg != 0 && arg == *(int*)((char*)g_016c7b88 + 0xc));

    bl = (char)((PluginObj*)*(void**)((char*)this + 8))->FUN_00f41420(o, o, flag, 0);

    if (g_15acb40 == 0 || arg == 0)
        return bl == 0;
    char* g = (char*)g_016c7b88;
    if (arg != *(int*)(g + 4))
        return bl == 0;

    int* p = *(int**)(g + 0x8c);
    int* end = *(int**)(g + 0x90);
    while (p != end) {
        int elem = *p;
        bl &= (char)((PluginObj*)*(void**)((char*)this + 8))->FUN_00f41420((void*)elem, o, 0, 1);
        bl &= (char)((PluginObj*)*(void**)((char*)this + 8))->FUN_00f3b9e0((void*)elem,
                 FUN_00b18e00(FUN_00f3d780((void*)elem)), 1);
        p += 8;
    }
    return bl == 0;
}

// @ 0x00efebb0
void Scene::FUN_00efebb0(void* arg)
{
    void* ebx = ((PluginObj*)*(void**)((char*)this + 8))->FUN_00f3e8a0(*(void**)arg);

    if (arg == ((PluginObj*)*(void**)((char*)this + 8))->FUN_00ff3f00()) {
        ((PluginObj*)*(void**)((char*)gSimulator + 0xd4))->FUN_00efbbe0(4, 5);
        return;
    }

    char local[12];
    void* r = FUN_00eec3d0(local, arg);
    if (*(int*)((char*)r + 4) == 0x2b978c46) {
        ((PluginObj*)*(void**)((char*)gSimulator + 0xd4))->FUN_00efbbe0(0x1f, 0x20);
        ((PluginObj*)*(void**)((char*)gSimulator + 0xd4))->FUN_00efbbe0(0x43, 0x44);
        return;
    }

    int id = (int)FUN_00eece20(ebx);
    if (id == 0xb10e526f) {
        ((PluginObj*)*(void**)((char*)gSimulator + 0xd4))->FUN_00efbbe0(0x2f, 0x30);
        return;
    }
    if (id == 0xe137ff08) {
        ((PluginObj*)*(void**)((char*)gSimulator + 0xd4))->FUN_00efbbe0(0x35, 0x36);
        return;
    }
    if (id == 0x5b3d1d0d || id == 0xd37c1045)
        ((PluginObj*)*(void**)((char*)gSimulator + 0xd4))->FUN_00efbbe0(0x59, 0x5a);
}

// @ 0x00efec90
void Scene::FUN_00efec90(void* arg)
{
    char flag = 0;
    char* g = (char*)g_016c7b88;

    if (arg != 0) {
        void* r = (void*)((FN1_ir)((*(void***)arg)[3]))(arg, 0x137e8e0);
        if (r != 0) {
            g = (char*)g_016c7b88;
            if (*(void**)(g + 0x10) == *(void**)(g + 0x20))
                flag = 1;
        }
    }

    g = (char*)g_016c7b88;
    if (*(void**)(g + 0x10) != *(void**)(g + 0x14)
        && *(void**)(g + 0x10) != *(void**)(g + 0x28)) {
        void* p = *(void**)(g + 0x10);
        void* q = p ? (void*)((FN1_ir)((*(void***)p)[3]))(p, 0x76c67df) : 0;
        if (!((PluginObj*)(g + 0x30))->FUN_00c64a70(q)
            && *(void**)(g + 0x10) != *(void**)(g + 0x2c)
            && flag == 0
            && g_15acb40 != 0
            && *(void**)(g + 0x8c) != *(void**)(g + 0x90)) {
            ((PluginObj*)*(void**)((char*)gSimulator + 0x74))->FUN_00f3bbd0(*(void**)(g + 4), 0);
            return;
        }
    }

    g = (char*)g_016c7b88;
    void* old = *(void**)(g + 0xc);
    if (arg != old) {
        if (arg != 0)
            ((FN0_i)((*(void***)arg)[0]))(arg);
        *(void**)(g + 0xc) = arg;
        if (old != 0)
            ((FN0_i)((*(void***)old)[1]))(old);
    }

    g = (char*)g_016c7b88;
    void* p = *(void**)(g + 0x10);
    void* q = p ? (void*)((FN1_ir)((*(void***)p)[3]))(p, 0x7a309fb) : 0;
    q = (void*)((FN0_i)((*(void***)q)[22]))(q);

    ((PluginObj*)*(void**)((char*)this + 8))->FUN_00f45970();

    g = (char*)g_016c7b88;
    void* obj = FUN_00eebf80(*(void**)(g + 4));
    if (obj != 0) {
        char local[12];
        FUN_00eec3d0(local, obj);
        int id = (int)FUN_00eece20(local);
        if (id == 0xe137ff08) {
            g = (char*)g_016c7b88;
            if (*(void**)(g + 0x10) == *(void**)(g + 0x20))
                ((PluginObj*)*(void**)((char*)gSimulator + 0xd4))->FUN_00efbbe0(0x3b, 0x3c);
            else if (*(void**)(g + 0x10) == *(void**)(g + 0x54))
                ((PluginObj*)*(void**)((char*)gSimulator + 0xd4))->FUN_00efbbe0(0x39, 0x3a);
        }
    }

    g = (char*)g_016c7b88;
    if (flag != 0)
        FUN_00eef570(*(void**)(g + 4), g + 0x8c);
    else
        FUN_00eef4b0(g + 0x8c);
}
