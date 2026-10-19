// src/game/SPMovie/videorenderer_rw4.cpp -- migrated from slice(s) s00fd90c0 by tools/migrate/rewrite.py
// Object file: SPMovie/videorenderer_rw4.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00fd90c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
extern u8    DAT_01493dcc[];  // "VideoRenderable data buffer"
void* __cdecl  FUN_011e58c0();                       // 0x011e58c0
void  __cdecl  FUN_00fcdf40(int, int, int, int, void*); // VideoRenderable::GetDataBufSizes
static inline void** VTP(void* o) { return *(void***)o; }
struct Vid {
    u32 x;
    void  f9460(void* p);
    u8    f9480(int param_2);
    void  f9610(int param_2);
    Vid*  f9680();
    void  f96d0();    void  f9750(int, int, int);
    void  f97c0(void* param_2);
    void  f9b70(int, int, int, int, u32);
};
// ---- items of slice s00fd90c0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern u8    DAT_01493dcc[];  // "VideoRenderable data buffer"

// @ 0x00fd9460
void Vid::f9460(void* p)
{
    *(void**)((char*)this + 4) = p;
    *(void**)((char*)this + 8) = FUN_011e58c0();
}

// @ 0x00fd9610
void Vid::f9610(int param_2)
{
    char* s = (char*)this;
    int n = *(int*)(param_2 + 0x38);
    if (n != 0) {
        int* pu = (int*)(param_2 + 4);
        do {
            u32 stack[4];
            stack[0] = pu[0];
            stack[1] = 0;
            stack[2] = 0;
            stack[3] = 0;
            void* p = *(void**)(s + 8);
            ((void(__thiscall*)(void*, void*))VTP(p)[8 / 4])(p, stack);
            pu[0] = 0;
            pu[3] = 0;
            pu++;
            n--;
        } while (n != 0);
    }
    *(int*)(param_2 + 0x28) = 0;
    *(int*)(param_2 + 0x2c) = 0;
    *(int*)(param_2 + 0x30) = 4;
}

// @ 0x00fd9b70
void Vid::f9b70(int param_2, int param_3, int param_4, int param_5, u32 param_6)
{
    char* s = (char*)this;
    *(u32*)(param_2 + 0x38) = param_6;
    u32 stack[8];
    FUN_00fcdf40(param_3, param_4, param_5, param_6, stack);
    if (param_6 != 0) {
        int* pu = (int*)(param_2 + 0x10);
        for (u32 i = 0; i < param_6; ++i) {
            u32 buf[8];
            buf[0] = stack[i];
            buf[1] = 0; buf[2] = 0; buf[3] = 0;
            buf[4] = 4; buf[5] = 1; buf[6] = 1; buf[7] = 1;
            void* alloc = *(void**)(s + 8);
            void* vt2 = *(void**)(alloc);
            ((void(__thiscall*)(void*, u32*, u32*, const char*))VTP(alloc)[1])(
                alloc, &buf[1], buf, (const char*)DAT_01493dcc);
            (void)vt2;
            pu[-3] = buf[1];
            *pu = stack[i];
            pu++;
        }
    }
    *(int*)(param_2 + 0x28) = param_3;
    *(int*)(param_2 + 0x2c) = param_4;
    *(int*)(param_2 + 0x30) = param_5;
}
