// src/game/mix/smixer.cpp.cpp -- migrated from slice(s) s01141a90 by tools/migrate/rewrite.py
// Object file: mix/smixer.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/System.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* g_mixvoices;     // 0x16e8174
extern "C" int g_numChannels;     // 0x15bfe38
extern "C" uint8_t g_numOutputs;  // 0x16e8079

// ---- items of slice s01141a90 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct System;
extern "C" void* g_mixvoices;     // 0x16e8174
extern "C" int g_numChannels;     // 0x15bfe38
extern "C" uint8_t g_numOutputs;  // 0x16e8079
class System {
public:
    uint8_t pad00[0x14];
    void* Alloc(int size, const char* name, int align, int flags); // 0x112c820
    void  Free(void* p, int flags);                                // 0x112c850
};
struct MixVoice {            // 0x5c bytes
    uint8_t state;           // +0x00
    uint8_t b01;             // +0x01
    uint8_t pad02[2];
    float   f04[12];         // +0x04
    float*  p34;             // +0x34
    float*  p38;             // +0x38
    float   f3c;             // +0x3c
    void*   p40;             // +0x40
    int     f44;             // +0x44
    void*   p48;             // +0x48
    void*   p4c;             // +0x4c
    int     f50;             // +0x50
    int     f54;             // +0x54
    int     f58;             // +0x58
};
// ---- items of slice s01141a90 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" float* g_16e8170;      // 0x16e8170
extern "C" float g_16e8158[];     // 0x16e8158
extern "C" System* g_system;      // 0x16e61a8

// @ 0x01142900
extern "C" void FUN_01142900(int voice)
{
    MixVoice* v = (MixVoice*)((char*)g_mixvoices + voice * 0x5c);
    v->f3c = 0.0f;
    v->b01 = 0;
    for (int i = 0; i < g_numChannels; i++)
        v->p34[i] = v->p38[i];
    int i = 0;
    if (g_numOutputs != 0) {
        do {
            v->f04[i] = v->f04[6 + i];
            i++;
        } while (i < g_numOutputs);
    }
    v->state = 2;
}

// @ 0x01142960
namespace  {
void MIX_stop(int voice)
{
    MixVoice* v = (MixVoice*)((char*)g_mixvoices + voice * 0x5c);
    for (int i = 0; i < g_numChannels; i++) {
        g_16e8170[i] = v->p34[i] * v->f3c + g_16e8170[i];
    }
    int i = 0;
    if (g_numOutputs != 0) {
        do {
            g_16e8158[i] = v->f04[i] * v->f3c + g_16e8158[i];
            i++;
        } while (i < g_numOutputs);
    }
    for (;;) {
        int fn = *(int*)((char*)v->p40 + 4);
        if (fn != 0)
            ((void (*)(void*))fn)(v->p40);
        void* next = *(void**)((char*)v->p40 + 8);
        g_system->Free(v->p40, 0);
        v->p40 = next;
        if (next == 0)
            break;
    }
    v->state = 0;
}
}  // namespace 
