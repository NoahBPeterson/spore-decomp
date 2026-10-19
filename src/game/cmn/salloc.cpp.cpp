// src/game/cmn/salloc.cpp.cpp -- migrated from slice(s) s01140b70 by tools/migrate/rewrite.py
// Object file: cmn/salloc.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/System.h"

// ---- items of slice s01140b70 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct SndVoice;
struct SndVoice {            // 0x84 bytes
    int32_t      handle;     // +0x00
    int16_t      sub[8];     // +0x04  sub-voice indices (count at +0x23)
    int32_t      f14;        // +0x14
    uint8_t      pad18[2];   // +0x18
    uint8_t      b1a;        // +0x1a
    uint8_t      pad1b;      // +0x1b
    void*        p1c;        // +0x1c
    uint8_t      pad20[2];   // +0x20
    uint8_t      b22;        // +0x22
    uint8_t      count;      // +0x23
    uint8_t      b24;        // +0x24
    uint8_t      b25;        // +0x25
    uint8_t      pad26[2];   // +0x26
    int16_t      w28;        // +0x28
    uint8_t      b2a;        // +0x2a
    uint8_t      pad2b;      // +0x2b
    uint32_t     counter;    // +0x2c
    uint8_t      pad30[4];   // +0x30
    uint8_t      b34;        // +0x34
    uint8_t      b35;        // +0x35
    uint8_t      pad36[0x33];// +0x36
    uint8_t      flag69;     // +0x69
    uint8_t      tail[0x84 - 0x6a]; // pad to 0x84
};
void FUN_011432a0(int);                               // 0x11432a0
// ---- items of slice s01140b70 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" SndVoice* g_voices;      // 0x16e7c78
extern "C" int16_t g_voiceCount;    // 0x16e7c20
extern "C" int16_t g_order[];       // 0x16e8050
extern "C" uint32_t g_orderFlag;    // 0x16e805c
extern "C" uint32_t g_tick;         // 0x16e7c24
extern "C" uint8_t g_voiceMode;     // 0x16e7bfb

// @ 0x01140cb0
namespace  {
int SNDVOICEI_alloc(int count, int param_2, int * param_3, int lo, int hi)
{
    uint32_t local_c = 0;

    if ((int)count > 0) {
        for (uint32_t k = 0; k < count; k++)
            g_order[k] = (int16_t)-1;
    }

    g_orderFlag += 0x100;
    if ((int)g_orderFlag < 0)
        g_orderFlag = 0;

    if ((int)count > 0) {
        int16_t* dst = g_order;
        uint32_t rem = count;
        do {
            int best = -1;
            uint32_t bestv = 0xffffffff;
            if (lo < hi) {
                SndVoice* v = &g_voices[lo];
                int j = lo;
                for (; j < hi; j++, v++) {
                    if (v->flag69 == 0) {
                        int i = 0;
                        if (dst > g_order) {
                            do {
                                if (g_order[i] == j)
                                    goto next1;
                                i++;
                            } while (i < (int)local_c);
                        }
                        if (v->counter < bestv) {
                            bestv = v->counter;
                            best = j;
                        }
                    }
                next1:;
                }
            }
            if (best >= 0) {
                local_c++;
                *dst++ = (int16_t)best;
            }
            rem--;
        } while (rem != 0);
    }

    if ((int)local_c < (int)count) {
        int16_t* dst = &g_order[local_c];
        uint32_t rem = local_c;
        do {
            uint32_t p2 = param_2;
            if (g_voiceMode == 0)
                p2 = param_2 - 1;
            int best = -1;
            uint32_t bestv = 0xffffffff;
            if (lo < hi) {
                uint8_t* pb = (uint8_t*)&g_voices[lo] + 0x2a;
                int j = lo;
                for (; j < hi; j++, pb += 0x84) {
                    int i = 0;
                    if (dst > g_order) {
                        do {
                            if (g_order[i] == j)
                                goto next2;
                            i++;
                        } while (i < (int)local_c);
                    }
                    if (*pb < 0x65) {
                        uint32_t u = *pb;
                        uint32_t cand;
                        if ((int)u < (int)p2) {
                            cand = *(uint32_t*)(pb + 2);
                            p2 = u;
                        } else {
                            cand = *(uint32_t*)(pb + 2);
                            if (u != p2 || bestv <= cand)
                                goto next2;
                        }
                        bestv = cand;
                        best = j;
                    }
                next2:;
                }
                if (best >= 0) {
                    local_c++;
                    *dst++ = (int16_t)best;
                    if ((int)count <= (int)local_c)
                        break;
                }
            }
            rem++;
        } while ((int)rem < (int)count);
    }

    if (local_c != count)
        return -9;

    for (;;) {
        int sorted = 1;
        int i = 0;
        if ((int)(count - 1) < 1)
            break;
        do {
            int16_t a = g_order[i];
            int16_t b = g_order[i + 1];
            if (b < a) {
                g_order[i] = b;
                g_order[i + 1] = a;
                sorted = 0;
            }
            i++;
        } while (i < (int)(count - 1));
        if (sorted)
            break;
    }

    *param_3 = (uint32_t)g_order[0] | g_orderFlag;
    int ret = (int)g_order[0];

    for (int i = 0; i < (int)local_c; i++) {
        SndVoice* v = &g_voices[g_order[i]];
        int h = v->handle;
        if (v->flag69 != 0) {
            if (h < 0)
                h = g_voices[v->w28].handle;
            FUN_011432a0(h);
        }
        v->flag69 = 1;
        v->counter = g_tick;
        v->b2a = (uint8_t)param_2;
    }

    g_voices[g_order[0]].handle = (int32_t)*param_3;
    g_voices[g_order[0]].sub[0] = g_order[0];
    g_voices[g_order[0]].w28 = (int16_t)-1;

    for (int i = 1; i < (int)local_c; i++) {
        int idx = g_order[i];
        g_voices[g_order[0]].sub[i] = (int16_t)idx;
        g_voices[idx].handle = -1;
        g_voices[idx].w28 = g_order[0];
    }

    return ret;
}
}  // namespace 

// @ 0x01141020
namespace  {
void SNDVOICEI_free(int index)
{
    SndVoice* v = &g_voices[index];
    uint8_t b = v->b24;
    int matches = 0;
    int other = -1;
    uint8_t local = b;

    if (b == 0) {
        v->flag69 = 0;
        v->b24 = 0;
        v->b25 = 0;
        v->counter = g_tick;
        return;
    }

    if (g_voiceCount > 0) {
        int j = 0;
        SndVoice* p = g_voices;
        do {
            if (p->b24 == local && p->handle >= 0 && p->flag69 != 0) {
                matches++;
                if (p->b25 != 0)
                    other = j;
            }
            j++;
            p++;
        } while (j < g_voiceCount);
    }

    if (matches != 1) {
        SndVoice* o = &g_voices[other];
        if (o->flag69 == 2 && index != other && matches == 2) {
            v->flag69 = 0;
            v->b24 = 0;
            v->b25 = 0;
            v->counter = g_tick;
            o->flag69 = 0;
            o->b24 = 0;
            o->b25 = 0;
            o->counter = g_tick;
            return;
        }
        if (o->flag69 == 1 && index == other) {
            o->flag69 = 2;
            return;
        }
    }

    v->flag69 = 0;
    v->b24 = 0;
    v->b25 = 0;
    v->counter = g_tick;
}
}  // namespace 
