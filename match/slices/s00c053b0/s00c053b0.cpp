// Slice s00c053b0 - SPGonzago/SPCreatureBase.obj region 0x00c053b0..0x00c06640:
// creature locomotion/velocity evaluators, the 0xa0-byte block pool used by the
// creature ability/target containers, cGameData rank thunks and a timer cascade.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /Isrc/game/include  (no /EHsc)
#include "game/types.h"
#include "SP/cGonzagoTimer.h"
#include <math.h>

// ---- external callees / globals (addresses in comments) ----------------
void* __cdecl SP_GetCurrentGameMode();                       // 0x00b5b800
void* __cdecl FUN_00b3d310();                                // 0x00b3d310
void* __cdecl FUN_00b18530(void*);                           // 0x00b18530
int   __cdecl FUN_00f3c0e0(void*);                           // 0x00f3c0e0
void* __cdecl FUN_00401090(const void*);                     // 0x00401090 GetSetting
void* __cdecl FUN_004df550(const void*);                     // 0x004df550 GetProfile
void  __cdecl FUN_00bc9c90(void*);                           // 0x00bc9c90
void  __cdecl FUN_00c04870(void);                            // 0x00c04870
void  __cdecl FUN_00c048c0(void*, void*);                    // 0x00c048c0
void  __cdecl FUN_00ac4060(void*, int, int, int);            // 0x00ac4060 (vector reserve)
void* __cdecl operator_new_eastl(size_t, const char*, int, int, int, int); // 0x00f473a0
void  __cdecl operator_delete__(void*);                      // 0x00f47380
void* __cdecl RotateVector(void* out, const void* v, const void* q); // 0x0059aed0
void* __cdecl FUN_0059ab70(const void* v);                   // 0x0059ab70
void* __cdecl FUN_00799320(void* out, const void* v);        // 0x00799320
void  __cdecl FUN_00c0d1e0(void* v);                         // 0x00c0d1e0 (SetPosition)
void  __cdecl FUN_00c1bbd0(void*);                           // 0x00c1bbd0
void  __cdecl FUN_00c421b0(void*, void*);                    // 0x00c421b0
void  __cdecl FUN_00c44040(void*);                           // 0x00c44040
void  __cdecl FUN_00c43fe0(void*, void*);                    // 0x00c43fe0
void* __cdecl FUN_00b532b0(void*);                           // 0x00b532b0
float __cdecl FUN_00c0c070(void*);                           // 0x00c0c070
void* __cdecl FUN_00c0b750(void*);                           // 0x00c0b750
extern float gF_1582ea0;   // 0x01582ea0  1.5f
extern float gF_1582ea4;   // 0x01582ea4  3.0f
extern float gF_1582ea8;   // 0x01582ea8  3.0f
extern float gF_1582ecc;   // 0x01582ecc  10.0f
extern float gF_1582ed0;   // 0x01582ed0  10.0f
extern float gF_1582e80;   // 0x01582e80  1.0f
extern float gF_1582f50;   // 0x01582f50  1.0f
extern float gF_150c888;   // 0x0150c888  0.25f
extern float gF_150c884;   // 0x0150c884  uint32 timer limit
void* __cdecl FUN_00d20610(void*);                          // 0x00d20610
void* __cdecl FUN_00a64a00(void*);                           // 0x00a64a00
void* __cdecl FUN_00aef390(void*, int, float);               // 0x00aef390
void* __cdecl FUN_00c0c120(void*);                           // 0x00c0c120
void* __cdecl FUN_00c0c130(void*);                           // 0x00c0c130
void* __cdecl FUN_00c0b770(void*);                           // 0x00c0b770
void* __cdecl FUN_00c22470(void*, int);                      // 0x00c22470
void* __cdecl FUN_00c037c0(void*, void*, int, int);          // 0x00c037c0
void* __cdecl FUN_00c21090(void*);                           // 0x00c21090
void* __cdecl FUN_00c042e0(void*);                           // 0x00c042e0
void* __cdecl FUN_00feba90(void*);                           // 0x00feba90 cSPTimer::IsRunning
void* __cdecl FUN_00bc3190(void*);                           // 0x00bc3190 cSPTimer::GetElapsedTime
void* __cdecl FUN_00bc3110(void*);                           // 0x00bc3110 cSPTimer::Stop
void* __cdecl FUN_00c04e50(void*, float);                    // 0x00c04e50
void* __cdecl FUN_00c17de0(void*, float);                    // 0x00c17de0
void* __cdecl FUN_00c0c200(void*, float);                    // 0x00c0c200
void* __cdecl FUN_00c1d5e0(void*, int, int, int);            // 0x00c1d5e0
void* __cdecl FUN_00c17cc0(void*, int, int, int, int, int);  // 0x00c17cc0
void* __cdecl FUN_00c201a0(void*, int, int, int);            // 0x00c201a0
void* __cdecl FUN_00c0d1e0_p(void*);                         // 0x00c0d1e0
void* __cdecl FUN_00bca0c0(void*, int, int, int, int);       // 0x00bca0c0 FindSlot
void* __cdecl FUN_00c06000();                                 // 0x00c06000
void* __cdecl FUN_00c0c0e0(void*, int);                       // 0x00c0c0e0
void       __cdecl FUN_00434040(void*);                       // 0x00434040

extern float gF_1485378;   // 0x01485378  0.0f
extern float gF_1471064;   // 0x01471064  0.5f
extern float gF_15716c0;   // 0x015716c0  0.1f
extern float gF_15716b8;   // 0x015716b8  0.75f
extern float gF_15716bc;   // 0x015716bc  10.0f
extern float gF_1485720;   // 0x01485720  1.0f
extern float gF_168d830;   // 0x0168d830  1.0471976f (pi/3, computed once)
extern uint32_t g_168d834; // 0x0168d834  computed-once guard
extern char   g_169e37f;   // 0x0169e37f  flag byte
extern float gF_169e388;   // 0x0169e388
extern float gF_169e38c;   // 0x0169e38c
extern float gF_169e390;   // 0x0169e390
extern void* g_16c7aa4;    // 0x016c7aa4
extern void* g_168d838;    // 0x0168d838  cLocomotionStrategy template cache

struct Vector3_s { float x, y, z; };

// Stub method-holders for callees that take `this` in ecx (free functions in the
// image, so they can't be declared __thiscall directly).
struct Fn421b0 { void __thiscall f(void*); };   // 0x00c421b0
struct Fn44040 { void __thiscall f(); };         // 0x00c44040
struct Fn43fe0 { void __thiscall f(void*); };    // 0x00c43fe0

// ecx-`this` callees used by the creature evaluators.
struct FnC200  { void  __thiscall f(float); };            // 0x00c0c200
struct FnTimer { char  __thiscall IsRunning(); unsigned long long __thiscall Elapsed(); void __thiscall Stop(); }; // 0x00feba90/0x00bc3190/0x00bc3110
struct Fn4e50  { void  __thiscall f(float); };            // 0x00c04e50
struct Fn17de0 { void  __thiscall f(float); };            // 0x00c17de0
struct Fn20610 { void* __thiscall f(); };                 // 0x00d20610
struct Fn64a00 { int   __thiscall f(); };                 // 0x00a64a00
struct Fnef390 { void  __thiscall f(int, float); };       // 0x00aef390
struct Fnc120  { int   __thiscall f(); };                 // 0x00c0c120
struct Fnc130  { int   __thiscall f(); };                 // 0x00c0c130
struct Fnc070  { float __thiscall f(); };                 // 0x00c0c070
struct Fnb750  { int   __thiscall f(); };                 // 0x00c0b750
struct Fnc770  { int   __thiscall f(); };                 // 0x00c0b770
struct Fnc0e0  { int   __thiscall f(int); };              // 0x00c0c0e0
struct Fn17cc0 { void  __thiscall f(int, int, int, int, int); };  // 0x00c17cc0
struct Fn201a0 { void  __thiscall f(int, int, int); };    // 0x00c201a0
struct Fn1d5e0 { int*  __thiscall f(int, int, int); };    // 0x00c1d5e0
struct Fn434040 { void __thiscall ctor(); };              // 0x00434040 XformMsg::XformMsg
struct XformMsg { char b[0x30]; };
struct Fn22470 { char  __thiscall f(int); };              // 0x00c22470
struct Fn37c0  { char  __thiscall f(void*, int, int); };  // 0x00c037c0
struct Fn21090 { void  __thiscall f(); };                 // 0x00c21090
struct Fn42e0  { void  __thiscall f(); };                 // 0x00c042e0
void* __cdecl GetSetting9(void*);                         // 0x00401090
void* __cdecl GetProfile(void*);                          // 0x004df550

// ---- retail layout of the object this slice's methods belong to.
// Canonical header (src/game/include/SP/cSPCreatureBase.h) is generated and its
// dev-PDB offsets drift from retail; use the offsets read off the disassembly.
struct CB {
    uint8_t  pad0[0xc0];
    uint8_t  padloc[0xb54 - 0xc0];       // +0xc0 locomotion subobject
    void*    mpStrat;                    // +0xb54  locomotion strategy obj
    uint32_t mGeneralFlags;              // +0xb58
    uint8_t  pad1[0x1000 - 0xb5c];
    float    mField1000;                 // +0x1000

    void func74h(int param_2, int param_3);     // 0x00c053b0
    void func58h(float dt);                     // 0x00c05810
    void func5a8h(int param_2);                 // 0x00c05a80
    float func5bf0();                           // 0x00c05bf0
    char func5d40(int param_2);                 // 0x00c05d40
    void func6500();                            // 0x00c06500
    float GetRankThunk(int param_2);            // 0x00c06320
    void  RankForward(int param_2);             // 0x00c06340
};

struct Vector3_pair { Vector3_s a, b; };

// @ 0x00c053b0
void CB::func74h(int param_2, int param_3)
{
    void* body = (char*)this + 0xc0;
    float* p = (float*)(*(void*(__thiscall**)(void*))((*(void***)body)[0x2c / 4]))(body);
    float px = p[0], py = p[1], pz = p[2];

    Vector3_s pos, dir;
    if (((mGeneralFlags >> 9) & 1) && g_169e37f) {
        (*(void(__thiscall**)(void*, void*))((*(void***)body)[0x5c / 4]))(body, &pos);
        (*(void(__thiscall**)(void*, void*))((*(void***)body)[0x60 / 4]))(body, &dir);
        if (!(g_168d834 & 1)) {
            g_168d834 |= 1;
            gF_168d830 = 1.0471976f;
        }
        float d = dir.x * (dir.z * gF_169e388 - dir.y * gF_169e390) +
                  dir.y * (dir.x * gF_169e390 - dir.z * gF_169e388) +
                  dir.z * (dir.y * gF_169e388 - dir.x * gF_169e390);
        if (d > gF_1485378) {
            float a = gF_168d830 * gF_1471064;
            float s = (float)sin(a);
            float c = (float)cos(a);
            Vector3_s v;
            v.x = px * s; v.y = py * s; v.z = pz * s;
            (void)c;
            RotateVector(&v, &v, &a);
        } else {
            float a = -(gF_168d830 * gF_1471064);
            float s = (float)sin(a);
            float c = (float)cos(a);
            Vector3_s v;
            v.x = px * s; v.y = py * s; v.z = pz * s;
            (void)c;
            RotateVector(&v, &v, &a);
        }
    } else {
        pos.x = *(float*)(param_3 + 0x14) - px;
        pos.y = *(float*)(param_3 + 0x18) - py;
        pos.z = *(float*)(param_3 + 0x1c) - pz;
        float len = (float)sqrt((double)(pos.z * pos.z + pos.y * pos.y) + (double)(pos.x * pos.x));
        if (len > gF_15716c0) {
            float inv = 1.0f / len;
            pos.x = pos.x * inv;
            pos.y = pos.y * inv;
            pos.z = pos.z * inv;
        } else {
            pos.x = -gF_169e388;
            pos.y = -gF_169e38c;
            pos.z = -gF_169e390;
            Vector3_s res;
            RotateVector(&res, &pos, (char*)this + 0x164);
            if (!FUN_0059ab70(&res))
                ;
        }
    }
    float w = gF_15716bc;
    float k = gF_1485720 - gF_15716b8;
    void* ac = mpStrat;
    Vector3_s out;
    out.x = (*(float*)((char*)ac + 0x164) * gF_15716b8) + (pos.x * w + px) * k;
    out.y = (*(float*)((char*)ac + 0x168) * gF_15716b8) + (pos.y * w + py) * k;
    out.z = (*(float*)((char*)ac + 0x16c) * gF_15716b8) + (pos.z * w + pz) * k;
    FUN_00c0d1e0(&out);
}

// @ 0x00c05810
void CB::func58h(float dt)
{
    char* self = (char*)this;
    ((FnC200*)self)->f(dt);
    char* timer = self + 0x1628;
    if (((FnTimer*)timer)->IsRunning()) {
        unsigned long long t = ((FnTimer*)timer)->Elapsed();
        if (t > (unsigned long long)*(uint32_t*)0x150c884)
            ((FnTimer*)timer)->Stop();
    }
    if (SP_GetCurrentGameMode() != (void*)0x1654c10)
        ((Fn4e50*)self)->f(dt);
    ((Fn17de0*)self)->f(dt);
    if (*(int*)(self + 0xeac) == 2) {
        char* body = self + 0xc0;
        void* loco = FUN_00b532b0(body);
        if (loco) {
            float* vel = (float*)((Fn20610*)body)->f();
            float vx = vel[0], vy = vel[1], vz = vel[2];
            float* sp = (float*)(*(void*(__thiscall**)(void*))((*(void***)body)[0xd8 / 4]))(body);
            float speed = (float)sqrt((double)((vx * vx + vy * vy) + vz * vz)) * (*sp);
            unsigned char b;
            if ((*(char*)(self + 0x137) != 0) && speed >= gF_1582ecc &&
                ((Fnc120*)self)->f())
                b = 1;
            else if (*(int*)(self + 0xe8c) != -1 &&
                     (*(int*(__thiscall**)(void*, int))((*(void***)self)[0xb4 / 4]))(self, *(int*)(self + 0xe8c))[2] == 0x1f)
                b = 1;
            else
                b = 0;
            if ((char)((Fn64a00*)loco)->f() != (char)b)
                ((Fnef390*)loco)->f(b, gF_1582ed0);
        }
    }
    if (*(int*)(self + 0xeac) < 2) {
        if (((Fnc130*)self)->f()) {
            *(float*)(self + 0xb80) = 0.0f;
            return;
        }
    } else {
        int q = *(int*)(self + 0xb4c);
        if (q != 0 && *(int*)(q + 0x1d8) == 0x2d852e6) {
            *(float*)(self + 0xb80) =
                ((Fnc070*)self)->f() * gF_1582ea8 + *(float*)(self + 0x1000);
            return;
        }
        if (((Fnc130*)self)->f()) {
            *(float*)(self + 0xb80) = 0.0f;
            return;
        }
        if (((Fnc120*)self)->f()) {
            if (*(char*)(self + 0x137) != 0 || (*(uint32_t*)(self + 0x110) & 0x1000))
                goto L_a46;
        } else {
            uint32_t k = (uint32_t)((Fnb750*)self)->f();
            if (k < 4) {
                switch (k) {
                case 0: case 2:
                    if (*(char*)(self + 0x137) != 0 || (*(uint32_t*)(self + 0x110) & 0x1000)) {
                        *(float*)(self + 0xb80) =
                            ((Fnc070*)self)->f() * gF_1582ea0 + *(float*)(self + 0x1000);
                        return;
                    }
                    goto L_e6;
                case 1:
                    *(float*)(self + 0xb80) = 0.0f;
                    return;
                case 3:
                    break;
                }
            }
            if (*(char*)(self + 0x137) != 0 || (*(uint32_t*)(self + 0x110) & 0x1000))
                goto L_a46;
        }
    }
L_e6:
    *(float*)(self + 0xb80) = ((Fnc070*)self)->f() + *(float*)(self + 0x1000);
    return;
L_a46:
    *(float*)(self + 0xb80) = ((Fnc070*)self)->f() * gF_1582ea4 + *(float*)(self + 0x1000);
}

// @ 0x00c05a80
void CB::func5a8h(int param_2)
{
    char* self = (char*)this;
    void* gm = SP_GetCurrentGameMode();
    if (gm == (void*)0x1654c01) {
        char* body = self + 0xc0;
        typedef char (__thiscall *VtFn)(void*);
        VtFn vt0 = (VtFn)((*(void***)body)[0x58 / 4]);
        VtFn vt1 = (VtFn)((*(void***)body)[0x48 / 4]);
        if (vt0(body) && *(int*)(self + 0xeac) >= 1) {
            char f = vt1(body);
            char v;
            if (*(char*)(self + 0xfb8) != 0 && f != 0) v = 1; else v = 0;
            ((Fn17cc0*)self)->f(v, 0, (int)0xe1a4bd93, (int)0xf20c24d8, 0);
            ((Fn201a0*)self)->f((char)((Fnc120*)self)->f(), (int)0xe55dc391, (int)0x35052b7);
        }
        char b;
        if (*(char*)(self + 0xb5e) == 0 &&
            FUN_00bca0c0(*(void**)(self + 0xb48), 1, 1, 0, 0) != (void*)-1)
            b = 1;
        else
            b = 0;
        ((Fn1d5e0*)self)->f(b, (int)0xdc5ed5b9, (int)0xdc5ed5b9);
        return;
    }
    uint32_t m = (uint32_t)gm + 0xfe9ab3fc;
    if (m > 1) return;
    float f = *(float*)(self + 0x169c);
    int e = f > gF_1485378;
    char g = (char)((Fnc0e0*)self)->f(0x1f750af4);
    int arg = g ? 0x1f750af4 : 0x1f750af4 - 0x9f7f1be0;
    int* piVar5 = ((Fn1d5e0*)self)->f(e, arg, 0x1f750af4);
    if (!piVar5) return;
    XformMsg msg;
    ((Fn434040*)&msg)->ctor();
    (*(void(__thiscall**)(int*, void*))((*(void***)piVar5)[0x20 / 4]))(piVar5, &msg);
    (*(float(__thiscall**)(void*))((*(void***)(self + 0xc0))[0x34 / 4]))(self + 0xc0);
    *(uint16_t*)((char*)&msg + 2) += 1;
    (*(void(__thiscall**)(int*, void*))((*(void***)piVar5)[0x18 / 4]))(piVar5, &msg);
}

// @ 0x00c05bf0
float CB::func5bf0()
{
    char* self = (char*)this - 0x5a8;
    float base = (*(float(__thiscall**)(void*))((*(void***)self)[0x7c / 4]))(self);
    void* gm = SP_GetCurrentGameMode();
    if (gm != (void*)0x1654c10) {
        float f = gF_1582e80;
        if (!((*(uint32_t*)((char*)this + 0x5b0) >> 9) & 1))
            f = gF_1485720;
        char c = (char)((Fnc770*)self)->f();
        if (c == 0)
            f = gF_150c888 * f;
        else if ((*(uint8_t*)((char*)this + 0x5b0) & 1) != 0)
            f = gF_1582f50 * f;
        return f * base;
    }
    if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
        void* gd = FUN_00b18530(self);
        if (gd) {
            int* e = (int*)(FUN_00f3c0e0(*(void**)((char*)g_16c7aa4 + 0x74)) * 0x4e0 + *(int*)((char*)gd + 0x70));
            if (e) {
                float v = *(float*)((char*)e + 0x48c) * base;
                int i = (int)v;
                if ((float)i < v) i = i + 1;
                return (float)i;
            }
        }
    }
    float v = *(float*)(*(int*)(*(int*)((char*)g_16c7aa4 + 0x74) + 0x10) + 0x170) * base;
    int i = (int)v;
    if ((float)i < v) i = i + 1;
    return (float)i;
}

// @ 0x00c05d40
char CB::func5d40(int param_2)
{
    char* self = (char*)this;
    void* key = self + 0xb28;
    void* prof = GetProfile(GetSetting9(key));
    void* ecx = *(void**)(self + 0x1674);
    if (ecx)
        (*(void(__thiscall**)(void*, int))((*(void***)ecx)[0x3c / 4]))(ecx, param_2);
    char bl = ((Fn22470*)self)->f(param_2);
    if (bl) {
        if (*(void**)key != 0) {
            void* prof2 = GetProfile(GetSetting9(key));
            bl = ((Fn37c0*)self)->f(prof2, 0, 1);
            if (prof != prof2) {
                ((Fn21090*)self)->f();
                void* p = *(void**)(self + 0x1674);
                *(uint32_t*)(self + 0xb58) &= 0xffffff7f;
                if (p) *(uint8_t*)((char*)p + 0x191) = 0;
            }
        }
        if (bl) {
            ((Fn42e0*)self)->f();
            (*(void(__thiscall**)(void*))((*(void***)self)[0x54 / 4]))(self);
        }
    }
    return bl;
}

// @ 0x00c06500
void CB::func6500()
{
    void* self = this;
    SP_GetCurrentGameMode();
    *(uint32_t*)((char*)self + 0x2b0) = 0;
    char* body = (char*)self + 0xc0;
    FUN_00b3d310();
    void* v = FUN_00c06000();
    ((Fn421b0*)body)->f(v);
    ((Fn44040*)body)->f();
    int* m = (int*)FUN_00b3d310();
    if (m[0x20 / 4] == 0 || m[0x20 / 4] == 2)
        ((Fn43fe0*)body)->f((void*)0x00b498d0);
    if (((*(uint32_t*)((char*)self + 0xb58) >> 9) & 1) && SP_GetCurrentGameMode() == (void*)0x01654c05) {
        ((Fn43fe0*)body)->f((void*)0x00b49730);
        ((Fn43fe0*)body)->f((void*)0x00b493e0);
        ((Fn43fe0*)body)->f((void*)0x00b4c730);
    }
}



// ======================================================================
// Intrusive 0x14-byte-element block pool used by the creature ability/target
// containers.  Layout read off the disassembly:
//   +0x00 uint32_t* mpBlocksBegin   +0x14 uint32_t** mppFreeListCur
//   +0x04 int       mBlockCount     +0x18 uint8_t*  mpPoolBegin
//   +0x08 uint8_t*  mpPoolCur       +0x1c uint8_t*  mpBlockCur
//   +0x0c uint8_t*  mpPoolAllocEnd  +0x20 uint8_t*  mpBlockEnd
//   +0x10 uint8_t*  mpPoolEnd       +0x24 uint32_t** mppFreeListEnd
// Elements: {a, b, c, refCur, refNext}  (refs released via vtable slot 1).
struct NodePool {
    uint32_t*  mpBlocksBegin;    // 0x00
    int        mBlockCount;      // 0x04
    uint8_t*   mpPoolCur;        // 0x08
    uint8_t*   mpPoolAllocEnd;   // 0x0c
    uint8_t*   mpPoolEnd;        // 0x10
    uint32_t** mppFreeListCur;   // 0x14
    uint8_t*   mpPoolBegin;      // 0x18
    uint8_t*   mpBlockCur;       // 0x1c
    uint8_t*   mpBlockEnd;       // 0x20
    uint32_t** mppFreeListEnd;   // 0x24

    void Free();                 // 0x00c05df0
    void Pop();                  // 0x00c05ea0
    void Reset();                // 0x00c05ee0
    uint8_t* Cur();              // 0x00c05e80
    void AllocChunk(void* key);  // 0x00c06070
};

static void ReleaseRef(void* p)
{
    if (p) (*(void(__thiscall**)(void*))((*(void***)p)[1]))(p);
}

// @ 0x00c05df0
void NodePool::Free()
{
    uint8_t* cur = mpPoolCur;
    uint8_t* blkCur = mpPoolEnd;
    uint32_t** fl = mppFreeListCur;
    if (cur != mpPoolBegin) {
        do {
            ReleaseRef(*(void**)(cur + 0x10));
            ReleaseRef(*(void**)(cur + 0xc));
            cur += 0x14;
            if (cur == blkCur) {
                blkCur = (uint8_t*)fl[1];
                fl += 1;
                mppFreeListCur = fl;
                mpPoolEnd = blkCur;
            }
        } while (cur != mpPoolBegin);
    }
    if (mpBlocksBegin) {
        uint8_t** p = (uint8_t**)mpPoolEnd;
        uint8_t** q = (uint8_t**)((char*)mppFreeListEnd + 4);
        if (p < q) {
            do {
                if (*p) operator_delete__(*p);
                p += 1;
            } while (p < q);
        }
        if (mpBlocksBegin) operator_delete__(mpBlocksBegin);
    }
}

// @ 0x00c05e80
uint8_t* NodePool::Cur()
{
    uint8_t*   a = mpPoolBegin;
    uint8_t*   b = mpBlockCur;
    uint32_t** c = mppFreeListEnd;
    if (a != b)
        return a - 0x14;
    return (uint8_t*)c[-1] + 0x8c;
}

// @ 0x00c05ea0
void NodePool::Pop()
{
    uint8_t* cur = mpPoolBegin;
    if (cur == mpBlockCur) {
        FUN_00c04870();
        return;
    }
    uint8_t* esi = cur - 0x14;
    mpPoolBegin = esi;
    ReleaseRef(*(void**)(esi + 0x10));
    ReleaseRef(*(void**)(esi + 0xc));
}

// @ 0x00c05ee0
void NodePool::Reset()
{
    uint8_t* poolCur = mpPoolCur;
    uint32_t** fl = mppFreeListCur;
    if (fl == mppFreeListEnd) {
        if (poolCur < mpPoolBegin) {
            do {
                ReleaseRef(*(void**)(poolCur + 0x10));
                ReleaseRef(*(void**)(poolCur + 0xc));
                poolCur += 0x14;
            } while (poolCur < mpPoolBegin);
        }
    } else {
        if (poolCur < mpPoolAllocEnd) {
            do {
                ReleaseRef(*(void**)(poolCur + 0x10));
                ReleaseRef(*(void**)(poolCur + 0xc));
                poolCur += 0x14;
            } while (poolCur < mpPoolAllocEnd);
        }
        poolCur = mpBlockCur;
        if (poolCur < mpPoolBegin) {
            do {
                ReleaseRef(*(void**)(poolCur + 0x10));
                ReleaseRef(*(void**)(poolCur + 0xc));
                poolCur += 0x14;
            } while (poolCur < mpPoolBegin);
        }
        if (mpBlockCur) operator_delete__(mpBlockCur);
    }
    uint32_t** q = mppFreeListCur + 1;
    if (q < mppFreeListEnd) {
        do {
            uint8_t* e = (uint8_t*)*q;
            uint8_t* end = e + 0xa0;
            if (e < end) {
                do {
                    ReleaseRef(*(void**)(e + 0x10));
                    ReleaseRef(*(void**)(e + 0xc));
                    e += 0x14;
                } while (e < end);
            }
            if (*q) operator_delete__(*q);
            q += 1;
        } while (q < mppFreeListEnd);
    }
    mpPoolBegin = mpPoolCur;
    mpBlockCur = mpPoolAllocEnd;
    mpBlockEnd = mpPoolEnd;
    mppFreeListEnd = mppFreeListCur;
    mpPoolEnd = (uint8_t*)mppFreeListCur;
}

// @ 0x00c06070
void NodePool::AllocChunk(void* param_2)
{
    uint8_t scratch[0x14];
    FUN_00c048c0(param_2, &scratch[0]);
    int n = (((int)mppFreeListEnd - (int)mpBlocksBegin) >> 2) + 1;
    if (n >= mBlockCount)
        FUN_00ac4060(this, 1, 1, 0);
    void* blk = operator_new_eastl(0xa0, "Simulator", 0, 0, 0x13ebb38, 0xd1);
    *(void**)((char*)mppFreeListEnd + 4) = blk;
    if (mpPoolBegin) FUN_00c048c0(&scratch[0], 0);
    uint32_t** fl = mppFreeListEnd;
    mppFreeListEnd = fl + 1;
    uint8_t* nb = (uint8_t*)fl[1];
    mpBlockCur = nb;
    mpBlockEnd = nb + 0xa0;
    mpPoolBegin = mpBlockCur;
    ReleaseRef(*(void**)(scratch + 0xc));
    ReleaseRef(*(void**)(scratch + 0x4));
}

// ======================================================================
// cLocomotionStrategy template singleton accessor.
// @ 0x00c06000
void* __cdecl FUN_00c06000()
{
    if (g_168d838 == 0) {
        void* p = operator_new_eastl(0x10, "Simulator/LocomotionStrategy_Template", 0, 0, 0, 0);
        if (p) {
            *(void**)((char*)p + 8) = (void*)0x13ec458;
            *(void**)((char*)p + 0xc) = 0;
            *(void**)p = (void*)0x1469e38;
            *(void**)((char*)p + 8) = (void*)0x1475114;
            g_168d838 = p;
            (*(void(__thiscall**)(void*))*(void**)p)(p);
            return g_168d838;
        }
        g_168d838 = 0;
        (*(void(__thiscall**)(void*))0)(0);
    }
    return g_168d838;
}

// ======================================================================
// Timer cascade + tag stores (vtable/global images 0x146a0e0.. are the
// cCreatureAnimal ctor's vptrs; the object is treated as a byte buffer here).
// @ 0x00c061b0
void __fastcall FUN_00c061b0(void* self)
{
    void* edi = *(void**)((char*)self + 0x1624);
    *(void**)self = (void*)0x146a0e0;
    *(void**)((char*)self + 4) = (void*)0x146a0cc;
    *(void**)((char*)self + 0x34) = (void*)0x146a088;
    *(void**)((char*)self + 0x58) = (void*)0x146a020;
    *(void**)((char*)self + 0xc0) = (void*)0x1469f20;
    *(void**)((char*)self + 0x194) = (void*)0x1469f14;
    *(void**)((char*)self + 0x590) = (void*)0x1469ef8;
    *(void**)((char*)self + 0x5a8) = (void*)0x1469e90;
    *(void**)((char*)self + 0x670) = (void*)0x1469e74;
    if (edi) {
        FUN_00bc9c90(edi);
        operator_delete__(edi);
    }
    void* p = *(void**)((char*)self + 0x1698);
    if (p) (*(void(__thiscall**)(void*))((*(void***)p)[0x64 / 4]))(p);
    p = *(void**)((char*)self + 0x1674);
    if (p) (*(void(__thiscall**)(void*))((*(void***)p)[4 / 4]))(p);
    ((SP::cGonzagoTimer*)((char*)self + 0x1628))->~cGonzagoTimer();
    p = *(void**)((char*)self + 0x140c);
    if (p && *(int*)((char*)p - 4)) operator_delete__(p);
    p = *(void**)((char*)self + 0x13d4);
    if (p && *(int*)((char*)p - 4)) operator_delete__(p);
    p = *(void**)((char*)self + 0x133c);
    if (p && *(int*)((char*)p - 4)) operator_delete__(p);
    p = *(void**)((char*)self + 0x1124);
    if (p && *(int*)((char*)p - 4)) operator_delete__(p);
    p = *(void**)((char*)self + 0x108c);
    if (p && *(int*)((char*)p - 4)) operator_delete__(p);
    ((NodePool*)((char*)self + 0x1060))->Free();
    ((NodePool*)((char*)self + 0x1034))->Free();
    p = *(void**)((char*)self + 0x1020);
    if (p && *(int*)((char*)p - 4)) operator_delete__(p);
    ((SP::cGonzagoTimer*)((char*)self + 0xfe0))->~cGonzagoTimer();
    ((SP::cGonzagoTimer*)((char*)self + 0xfc0))->~cGonzagoTimer();
    FUN_00c1bbd0(self);
}

// @ 0x00c06320
float CB::GetRankThunk(int param_2) { (void)param_2; return 0.0f; }

// @ 0x00c06340
void CB::RankForward(int param_2)
{
    (*(void(__thiscall**)(CB*, int))((*(void***)this)[0x3c / 4]))(this, param_2);
}

