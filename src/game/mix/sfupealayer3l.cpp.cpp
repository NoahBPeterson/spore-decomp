// src/game/mix/sfupealayer3l.cpp.cpp -- migrated from slice(s) s01141a90 by tools/migrate/rewrite.py
// Object file: mix/sfupealayer3l.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/System.h"

// ---- items of slice s01141a90 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct SndFilter;
struct Dec19;
struct System;
extern "C" Dec19* g_16e8064;      // 0x16e8064
extern "C" System* g_system;      // 0x16e61a8
struct Dec19 {               // EALayer3 decoder node
    void*    codec;          // +0x00
    int      f04;            // +0x04
    int      f08;            // +0x08
    uint16_t w0c;            // +0x0c
    uint16_t w0e;            // +0x0e
    int      f10;            // +0x10
    int      f14;            // +0x14
    uint8_t  b18;            // +0x18
    uint8_t  b19;            // +0x19
};
struct SndFilter {           // decode filter object
    void*    filterfn;       // +0x00
    void*    restorefn;      // +0x04
    uint8_t  pad08[0x12];
    uint8_t  b1a;            // +0x1a
    uint8_t  pad1b;
    Dec19*   decoder;        // +0x1c
    int      f20;            // +0x20
    int      mode;           // +0x24
    int      f28;            // +0x28
    int      f2c;            // +0x2c
    int      f30;            // +0x30
};
struct Patch19 {             // patch/params argument of the init functions
    int      f00;            // +0x00
    int      f04;            // +0x04
    int      mode;           // +0x08
    int      f0c;            // +0x0c
    int      f10;            // +0x10
    int      f14;            // +0x14
    uint8_t  pad18[0xc];
    int      f24;            // +0x24
};
struct Codec {               // decoder instance (this = Dec19::codec)
    int  FUN_01156df0(void** out, int n);          // 0x1156df0
    void FUN_01156dd0();                           // 0x1156dd0
    void FUN_01156d70(void* p, int n, void* q);    // 0x1156d70
    void FUN_01157410();                           // 0x1157410
    void FUN_01157430();                           // 0x1157430
};
class System {
public:
    uint8_t pad00[0x14];
    void* Alloc(int size, const char* name, int align, int flags); // 0x112c820
    void  Free(void* p, int flags);                                // 0x112c850
};
void* FUN_011402c0(int);                           // 0x11402c0
void  FUN_0116bda0(void);                          // 0x116bda0
// ---- items of slice s01141a90 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" Dec19* g_16e8064;      // 0x16e8064
extern "C" System* g_system;      // 0x16e61a8

// @ 0x01141c30
extern "C" int FUN_01141a90(SndFilter* f, int n, int unused, void* buf);   // 0x01141a90 (no module: stays in the slice)
extern "C" void FUN_01141bc0(SndFilter* f);                                // 0x01141bc0 (no module: stays in the slice)
extern "C" void SFILTER_unpackealayer3linit(SndFilter* f, Patch19* patch)
{
    Dec19* saved = g_16e8064;
    (void)saved;
    if (patch->mode == 2) {
        if (f->b1a == 0) {
            g_16e8064 = (Dec19*)g_system->Alloc(0x14, "StereoLoopedEALayer3Decode", 0x10, 0);
            f->decoder = g_16e8064;
            void* d = FUN_011402c0(0x1d8);
            if (d != 0) {
                ((Codec*)d)->FUN_01157410();
                ((Codec*)d)->FUN_01156dd0();
            } else {
                d = 0;
            }
            g_16e8064->codec = d;
            ((Codec*)g_16e8064->codec)->FUN_01156dd0();
            f->f30 = patch->f04;
            f->f28 = patch->f10;
            f->f2c = patch->f14;
            ((Codec*)g_16e8064->codec)->FUN_01156d70((void*)patch->f00, 0x7fffffff,
                                                     (void*)patch->f10);
            g_16e8064->w0c = 0;
            g_16e8064->w0e = 0;
            g_16e8064->f10 = 1;
            g_16e8064->f04 = 0;
            g_16e8064->f08 = 0;
        } else {
            f->decoder = g_16e8064;
            g_16e8064->f10 = 2;
        }
    } else {
        g_16e8064 = (Dec19*)g_system->Alloc(0x14, "LoopEALayer3Decode", 0x10, 0);
        f->decoder = g_16e8064;
        void* d = FUN_011402c0(0x1d8);
        if (d != 0) {
            ((Codec*)d)->FUN_01157410();
            ((Codec*)d)->FUN_01156dd0();
        } else {
            d = 0;
        }
        g_16e8064->codec = d;
        ((Codec*)g_16e8064->codec)->FUN_01156dd0();
        f->f30 = patch->f04;
        f->f28 = patch->f10;
        f->f2c = patch->f14;
        ((Codec*)g_16e8064->codec)->FUN_01156d70((void*)patch->f00, 0x7fffffff,
                                                 (void*)patch->f10);
        g_16e8064->w0c = 0;
        f->decoder->f10 = 1;
        f->decoder->f04 = 0;
        f->decoder->f08 = 0;
    }
    f->filterfn = (void*)&FUN_01141a90;
    f->restorefn = (void*)&FUN_01141bc0;
    patch->f24 = (int)&FUN_0116bda0;
    f->f20 = 0;
    f->mode = patch->mode;
}
