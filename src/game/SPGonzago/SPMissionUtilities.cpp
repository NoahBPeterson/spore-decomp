// src/game/SPGonzago/SPMissionUtilities.cpp -- migrated from slice(s) s00fef140 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cEmpire.h"
#include "SP/cGameNounManager.h"
#include "SP/cSPMission.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl FUN_00b3d300();                            // SP::NounManager
extern "C" void* __cdecl FUN_00b3d350();                            // SP::PlanetModel
extern "C" void* __cdecl FUN_00b3d260();                            // SP::BehaviorManager
extern "C" void* __cdecl FUN_00b3d480();
extern "C" void* __cdecl FUN_00c099e0(void*, void*, int, void*, int, int);
extern "C" void  __cdecl FUN_00b81780(void*, void*, void*);
extern "C" void* __cdecl FUN_00acd2d0(void*);
#pragma warning(disable : 4100)

// ---- items of slice s00fef140 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  u32;
typedef unsigned char u8;
struct IEmpty {};
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};
extern "C" void* __cdecl FUN_00b3d300();                            // SP::NounManager
extern "C" void* __cdecl FUN_00b3d350();                            // SP::PlanetModel
extern "C" void* __cdecl FUN_00b3d260();                            // SP::BehaviorManager
extern "C" void* __cdecl FUN_00b3d480();
extern "C" void* __cdecl FUN_00c099e0(void*, void*, int, void*, int, int);
extern "C" void  __cdecl FUN_00b81780(void*, void*, void*);
extern "C" u32   __cdecl FUN_00a68fb0(u32);                         // EA::Random::RandomUint32Uniform
extern "C" void* __cdecl FUN_00c03170(u32);
extern "C" void* __cdecl FUN_00c1d430(u32);
extern "C" void* __cdecl FUN_00acd2d0(void*);
struct IVM00 : VPad<3, IEmpty>  { virtual void* FUN_0c(u32); };              // +0x0c
struct IVM01 : VPad<7, IVM00>   { virtual bool  FUN_2c(); };                  // +0x2c
struct IVM02 : VPad<9, IVM01>   { virtual void  FUN_54(); };                  // +0x54
struct IBehaviorMgr : VPad<14, IEmpty> { virtual void FUN_38(void*); };       // +0x38 (slot 14)
struct cNearNoun {
    void* GetPosition(float, float);                     // 0x00c6acc0
};
// ---- items of slice s00fef140 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" u32   __cdecl FUN_00a68fb0(u32);                         // EA::Random::RandomUint32Uniform
extern "C" void* __cdecl FUN_00c03170(u32);
extern "C" void* __cdecl FUN_00c1d430(u32);

// @ 0x00fefbb0
void FUN_00fefbb0(void* param1, void* param2, int count, u32 param4, u32 param5)
{
    void* u1 = FUN_00b3d480();
    void* planet = FUN_00b3d350();
    void* nm = FUN_00b3d300();
    (void)u1; (void)nm;
    if (count > 0) {
        int n = count;
        do {
            float pos[3];
            void* ret = ((cNearNoun*)param2)->GetPosition(0.0f, 10.0f);
            FUN_00b81780(planet, pos, ret);
            u32 r = FUN_00a68fb0(10);
            void* o = FUN_00c099e0(pos, param1, r >= 2 ? 1 : 0, param2, 0, 1);
            if (o != 0) {
                FUN_00c03170(param4);
                *(u8*)((u8*)o + 0xb62) = 1;
                FUN_00c1d430(param5);
                FUN_00acd2d0(o);
                void* bm = FUN_00b3d260();
                void* g = ((IVM00*)o)->FUN_0c(0x11c0ba3);
                ((IBehaviorMgr*)bm)->FUN_38(g);
                u8* g2 = (u8*)((IVM00*)o)->FUN_0c(0x116dd1b);
                if (g2 != 0) {
                    g2[0x71] = 0;
                    g2[0x75] = 1;
                }
                ((IVM02*)o)->FUN_54();
            }
        } while (--n != 0);
    }
}
