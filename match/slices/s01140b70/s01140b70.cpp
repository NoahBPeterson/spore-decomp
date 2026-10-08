// Slice s01140b70: RenderWare 4 audio core (rw::audio) - SND voice allocation / SNDI patch
// parsing / filter-node glue.  Built with VC .NET 2003 (cl 13.10) + /GL /LTCG.
// Flags: /vc71 /O2 /MD /Gy /TP
#include "types.h"

// ---------------------------------------------------------------------------
// Globals (addresses from the retail image)
// ---------------------------------------------------------------------------

struct SndVoice;
struct SndDecoder;
struct SndFilter;
struct System;

// 0x16e7c78 : pointer to the voice record array (0x84 bytes per record)
extern "C" SndVoice* g_voices;      // 0x16e7c78
// 0x16e7c20 : short count of voices in g_voices
extern "C" int16_t g_voiceCount;    // 0x16e7c20
// 0x16e8050 : scratch order buffer (shorts), SNDVOICEI_alloc output
extern "C" int16_t g_order[];       // 0x16e8050
// 0x16e805c : generation/flag counter OR'ed into the returned handle
extern "C" uint32_t g_orderFlag;    // 0x16e805c
// 0x16e7c24 : voice timestamp counter
extern "C" uint32_t g_tick;         // 0x16e7c24
// 0x16e7c1e : number of registered callbacks (signed char)
extern "C" int8_t g_cbCount;        // 0x16e7c1e
// 0x16e7c1c : callbacks-enabled flag
extern "C" bool g_cbEnabled;        // 0x16e7c1c
// 0x16e7c40 : callback table (function pointers)
extern "C" int32_t g_callbacks[];   // 0x16e7c40
// 0x16e7bfb : voice-alloc mode selector byte
extern "C" uint8_t g_voiceMode;     // 0x16e7bfb
// 0x16e7c74 : short lookup table
extern "C" int16_t g_16e7c74[];     // 0x16e7c74
// 0x16e8060 : current SND decoder node
extern "C" SndDecoder* g_16e8060;   // 0x16e8060
// 0x16e61a8 : rw::audio::core::System singleton
extern "C" System* g_system;        // 0x16e61a8

// ---------------------------------------------------------------------------
// Structures
// ---------------------------------------------------------------------------

struct SndDecoder {          // 0x1c bytes
    void*        codec;      // +0x00  (object with FUN_01156dd0/70/f0)
    int32_t      f04;        // +0x04
    int32_t      f08;        // +0x08
    uint16_t     w0c;        // +0x0c
    uint16_t     w0e;        // +0x0e
    uint8_t      pad10[8];   // +0x10
    int32_t      refcnt;     // +0x18
};

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

struct SndFilter {           // decode filter object
    void*        filterfn;   // +0x00 = FUN_01141780
    void*        restorefn;  // +0x04 = FUN_01141920
    uint8_t      pad08[0x12];
    uint8_t      b1a;        // +0x1a
    uint8_t      pad1b;
    SndDecoder*  decoder;    // +0x1c
    int32_t      f20;        // +0x20
    int32_t      f24;        // +0x24
    int32_t      f28;        // +0x28
    void*        f2c;        // +0x2c
    int32_t      f30;        // +0x30
    uint8_t      b34;        // +0x34
    uint8_t      b35;        // +0x35
};

struct SndPatch {            // argument to SFILTER_unpackealayer3pinit
    uint8_t      pad00[8];
    int32_t      f08;        // +0x08
    uint8_t      pad0c[0xc];
    int32_t      f18;        // +0x18
};

struct SndParser {           // SNDI tag stream parser context
    const uint8_t* data;     // +0x00
    int32_t        tag;      // +0x04
    uint32_t       f08;      // +0x08  (byte value of the tag)
    const uint8_t* value;    // +0x0c
    uint32_t       size;     // +0x10
};

struct SndPlayParams {       // 5th argument of FUN_01140b70
    uint8_t      pad00[6];
    uint8_t      b06;        // +0x06
    uint8_t      pad07[0x14 - 7];
    int32_t      f14[1];     // +0x14
};

struct MethodHolder {        // stub for the object whose +4 pointer is called
    void FUN_011e6cd0(int a);        // 0x11e6cd0
};

struct Codec {               // object stored in SndDecoder::codec
    void FUN_01157430();             // 0x1157430
    void FUN_01157410();             // 0x1157410
    void FUN_01156dd0();             // 0x1156dd0
    void FUN_01156d70(void* p, int n, void* q); // 0x1156d70
    void FUN_01156df0(void** out, int n);       // 0x1156df0
};

class System {               // rw::audio::core::System
public:
    uint8_t pad00[0x14];
    void* Alloc(int size, const char* name, int align, int flags); // 0x112c820
    void  Free(void* p, int flags);                                // 0x112c850
};

// ---------------------------------------------------------------------------
// Callees (external, annotated with their retail address for differential test)
// ---------------------------------------------------------------------------

void MIX_playinit(int, int, int, int, int, int, int, int, int, int, int, int); // 0x1142740
void MIX_sethighpass(int, int);                       // 0x1156a60
void FUN_011406e0(int);                               // 0x11406e0
void FUN_01140890(int);                               // 0x1140890
void FUN_01140930(int, int);                          // 0x1140930
void FUN_01142900(int);                               // 0x1142900
void FUN_01156940(int, int);                          // 0x1156940
void FUN_011432a0(int);                               // 0x11432a0
void* FUN_01132300(int);                              // 0x1132300
void SNDMEMI_alloc(void*, int);                       // 0x113ec90
void FUN_0113fca0(void*);                             // 0x113fca0
int  FUN_01156bb0(SndParser*);                        // 0x1156bb0
void FUN_01156c40(int, void*, void*, void*, void*);   // 0x1156c40
void* FUN_0112e980(const char*, int);                 // 0x112e980
void* FUN_011e0744(void*, const void*, uint32_t);     // 0x11e0744  (memcpy thunk)
void FUN_0113f8f0(void*, uint8_t, int);               // 0x113f8f0
int  FUN_0113f780(void*, uint8_t, void*, int*);       // 0x113f780
void FUN_01158b10(void*, void*, int, int);            // 0x1158b10
void FUN_01157430(void*);                             // 0x1157430
void FUN_011741b0(void*);                             // 0x11741b0
void* FUN_011402c0(int);                              // 0x11402c0
void FUN_01157410(void*);                             // 0x1157410
void* FUN_01158b90(int);                              // 0x1158b90
int  FUN_01140a00(int);                               // 0x1140a00
uint8_t FUN_01140a20(int);                            // 0x1140a20

// ===========================================================================
//  FUN_01140b70
// ===========================================================================
// @ 0x01140b70
extern "C" int FUN_01140b70(int index, int a1, int a2, int a3, SndPlayParams* pp)
{
    SndVoice* v = &g_voices[index];
    uint8_t n = v->count;
    for (int i = 0; i < (int)n; i++) {
        int sv = v->sub[i];
        MIX_playinit(sv, v->b22, 0, 0, 0, pp->f14[i], n, v->f14, -1, -1, pp->b06, i);
        FUN_011406e0(sv);
    }
    FUN_01140890(index);
    for (int i = 0; i < (int)v->count; i++) {
        FUN_01156940(v->sub[i], a1);
    }
    FUN_01140930(index, a2);
    for (int i = 0; i < (int)v->count; i++) {
        MIX_sethighpass(v->sub[i], a3);
    }
    for (int i = 0; i < (int)v->count; i++) {
        FUN_01142900(v->sub[i]);
    }
    return 0;
}

// ===========================================================================
//  SNDVOICEI_alloc  0x01140cb0
// ===========================================================================
// @ 0x01140cb0
extern "C" int SNDVOICEI_alloc(uint32_t count, uint32_t param_2, uint32_t* param_3,
                               int lo, int hi)
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

// ===========================================================================
//  SNDVOICEI_free  0x01141020
// ===========================================================================
// @ 0x01141020
extern "C" void SNDVOICEI_free(int index)
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

// ===========================================================================
//  FUN_01141150
// ===========================================================================
// @ 0x01141150
extern "C" uint32_t FUN_01141150(uint32_t param_1)
{
    int16_t cnt = g_voiceCount;
    if ((int)param_1 < 0)
        return 0xfffffff8;
    uint32_t u = param_1 & 0xff;
    if ((int)cnt <= (int)u)
        return 0xfffffff8;
    SndVoice* v = &g_voices[u];
    if (v->flag69 == 0)
        return 0xfffffff8;
    if (v->handle != (int32_t)param_1)
        return 0xfffffff8;
    return u;
}

// ===========================================================================
//  FUN_01141190   (intrusive list node: zero 3 dwords)
// ===========================================================================
// @ 0x01141190
extern "C" void FUN_01141190(int* p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
}

// ===========================================================================
//  FUN_011411a0   (insert node at head; list = {head, tail, count})
// ===========================================================================
// @ 0x011411a0
extern "C" void FUN_011411a0(int* list, int* node)
{
    node[0] = list[0];
    node[1] = 0;
    if (list[0] != 0) {
        *(int**)(list[0] + 4) = node;
        list[2]++;
        list[0] = (int)node;
    } else {
        list[2]++;
        list[1] = (int)node;
        list[0] = (int)node;
    }
}

// ===========================================================================
//  FUN_011411d0   (insert node at tail)
// ===========================================================================
// @ 0x011411d0
extern "C" void FUN_011411d0(int* list, int* node)
{
    node[0] = 0;
    node[1] = list[1];
    if (list[1] != 0) {
        *(int**)(list[1]) = node;
        list[2]++;
        list[1] = (int)node;
    } else {
        list[2]++;
        list[0] = (int)node;
        list[1] = (int)node;
    }
}

// ===========================================================================
//  FUN_01141200   (pop head)
// ===========================================================================
// @ 0x01141200
extern "C" void FUN_01141200(int* list)
{
    int* head = (int*)list[0];
    if (head) {
        int* next = (int*)*head;
        list[0] = (int)next;
        if (!next) {
            list[1] = 0;
            list[2]--;
            return;
        }
        next[1] = 0;
        list[2]--;
    }
}

// ===========================================================================
//  FUN_01141230   (unlink arbitrary node)
// ===========================================================================
// @ 0x01141230
extern "C" void FUN_01141230(int* list, int* node)
{
    int* head = (int*)list[0];
    if (node == head)
        list[0] = node[0];
    int* tail = (int*)list[1];
    if (node == tail)
        list[1] = ((int*)list[1])[1];
    if ((int*)node[1])
        *(int*)node[1] = node[0];
    if (node[0])
        *(int*)(node[0] + 4) = node[1];
    list[2]--;
}

// ===========================================================================
//  FUN_01141270
// ===========================================================================
// @ 0x01141270
extern "C" void* FUN_01141270(uint32_t param_1)
{
    if ((int)param_1 < 0)
        return 0;
    int o = (int)FUN_01132300(param_1 & 0xff);
    if (o == 0)
        return 0;
    int p = *(int*)((char*)o + 0x114);
    if (p != 0) {
        while (*(uint32_t*)((char*)p + 0xc) != param_1) {
            p = *(int*)p;
            if (p == 0)
                break;
        }
    }
    return (void*)p;
}

// ===========================================================================
//  SNDI_patchtohdr  0x011412b0
// ===========================================================================
// @ 0x011412b0
extern "C" void SNDI_patchtohdr(int arg0, const char* hdr, void* p4, void* p100,
                                void* p28, uint8_t* flag)
{
    SNDMEMI_alloc(p4, 4);
    SNDMEMI_alloc(p100, 0x64);
    SNDMEMI_alloc(p28, 0x1c);

    if ((hdr[0] == 'P' && hdr[1] == 'T') ||
        (hdr[0] == 'G' && hdr[1] == 'S' && hdr[2] == 'T' && hdr[3] == 'R')) {
        FUN_01156c40(0, (void*)hdr, p4, p100, p28);
        if (flag != 0)
            *flag = 1;
        return;
    }

    if (flag != 0)
        *flag = 0;

    FUN_0113fca0(p100);

    uint8_t* p4b = (uint8_t*)p4;
    SndParser parser;
    parser.data = (const uint8_t*)hdr + 4;
    *(uint16_t*)p4b = 0x5622;
    p4b[2] = 1;
    p4b[3] = 10;
    *(uint32_t*)p28 = 0;

    uint32_t* pT = (uint32_t*)((char*)p100 + 0x54);

    while (FUN_01156bb0(&parser)) {
        int tag = parser.tag;
        uint32_t val = parser.f08;
        if (tag == 0xa0) {
            p4b[3] = (uint8_t)val;
        } else if (tag == 0x9c) {
            *(uint16_t*)((char*)p100 + 8) = (uint16_t)val;
        } else if (tag == 0x9d) {
            *(uint16_t*)((char*)p100 + 0xa) = (uint16_t)val;
        } else if (tag == 0x9e) {
            *(uint16_t*)((char*)p100 + 0xc) = (uint16_t)val;
        } else if (tag == 0x9f) {
            *(uint16_t*)((char*)p100 + 0xe) = (uint16_t)val;
        } else if (tag == 0xa6) {
            *(uint16_t*)((char*)p100 + 0x10) = (uint16_t)val;
        } else if (tag == 0xa7) {
            *(uint16_t*)((char*)p100 + 0x12) = (uint16_t)val;
        } else if (tag == 0x98) {
            void* pv = FUN_0112e980("Time Stretch Data Chan 0", parser.size);
            *(void**)((char*)p100 + 0x14) = pv;
            FUN_011e0744(pv, parser.value, parser.size);
            *(uint32_t*)((char*)p100 + 0x2c) = parser.size;
        } else if (tag == 0x99) {
            void* pv = FUN_0112e980("Time Stretch Data Chan 1", parser.size);
            *(void**)((char*)p100 + 0x18) = pv;
            FUN_011e0744(pv, parser.value, parser.size);
            *(uint32_t*)((char*)p100 + 0x30) = parser.size;
        } else if (tag == 0x9a) {
            void* pv = FUN_0112e980("Time Stretch Data Chan 2", parser.size);
            *(void**)((char*)p100 + 0x1c) = pv;
            FUN_011e0744(pv, parser.value, parser.size);
            *(uint32_t*)((char*)p100 + 0x34) = parser.size;
        } else if (tag == 0x9b) {
            void* pv = FUN_0112e980("Time Stretch Data Chan 3", parser.size);
            *(void**)((char*)p100 + 0x20) = pv;
            FUN_011e0744(pv, parser.value, parser.size);
            *(uint32_t*)((char*)p100 + 0x38) = parser.size;
        } else if (tag == 0xa4) {
            void* pv = FUN_0112e980("Time Stretch Data Chan 4", parser.size);
            *(void**)((char*)p100 + 0x24) = pv;
            FUN_011e0744(pv, parser.value, parser.size);
            *(uint32_t*)((char*)p100 + 0x3c) = parser.size;
        } else if (tag == 0xa5) {
            void* pv = FUN_0112e980("Time Stretch Data Chan 5", parser.size);
            *(void**)((char*)p100 + 0x28) = pv;
            FUN_011e0744(pv, parser.value, parser.size);
            *(uint32_t*)((char*)p100 + 0x40) = parser.size;
        } else if (tag == 0x80) {
            ((uint8_t*)p100)[6] = (uint8_t)val;
        } else if (tag == 0x82) {
            p4b[2] = (uint8_t)val;
        } else if (tag == 0x84) {
            *(uint16_t*)p4b = (uint16_t)val;
        } else if (tag == 0x85) {
            *(uint32_t*)p28 = val;
        } else if (tag == 0x13) {
            ((uint8_t*)p100)[5] = (uint8_t)val;
        } else if (tag == 0x06) {
            ((uint8_t*)p100)[2] = (uint8_t)val;
        } else if (tag == 0x88) {
            ((uint32_t*)p28)[1] = val;
        } else if (tag == 0x89) {
            ((uint32_t*)p28)[2] = val;
        } else if (tag == 0x94) {
            ((uint32_t*)p28)[3] = val;
        } else if (tag == 0x95) {
            ((uint32_t*)p28)[4] = val;
        } else if (tag == 0xa2) {
            ((uint32_t*)p28)[5] = val;
        } else if (tag == 0xa3) {
            ((uint32_t*)p28)[6] = val;
        } else if (tag == 0x14) {
            pT[-4] = (uint32_t)(size_t)parser.value;
            *pT = parser.size;
            pT++;
        }
    }

    int i = (int)(uint8_t)p4b[2] - 1;
    if (i >= 0) {
        int* pi = (int*)((char*)p28 + 4 + i * 4);
        int16_t* ps = (int16_t*)((char*)p100 + 8 + i * 2);
        uint8_t numchan = p4b[2];
        do {
            uint8_t t = (uint8_t)p4b[2];
            int idx = i + (int)numchan * 6;
            *ps = (int16_t)(*ps + g_16e7c74[idx]);
            *pi = *pi + arg0;
            i--;
            ps--;
            pi--;
        } while (i >= 0);
    }
}

// ===========================================================================
//  FUN_01141690   (register callback)
// ===========================================================================
// @ 0x01141690
extern "C" void FUN_01141690(int32_t p)
{
    g_callbacks[g_cbCount++] = p;
}

// ===========================================================================
//  FUN_011416b0   (unregister callback)
// ===========================================================================
// @ 0x011416b0
extern "C" void FUN_011416b0(int32_t p)
{
    int i = 0;
    int8_t c = g_cbCount;
    if (c > 0) {
        while (g_callbacks[i] != p) {
            i++;
            if (c <= i)
                return;
        }
        c = c - 1;
        g_cbCount = c;
        if (i < c) {
            do {
                g_callbacks[i] = g_callbacks[i + 1];
                i++;
            } while (i < g_cbCount);
        }
    }
}

// ===========================================================================
//  FUN_01141710   (invoke callbacks)
// ===========================================================================
// @ 0x01141710
extern "C" void FUN_01141710(void)
{
    if (g_cbEnabled != 0) {
        int i = 0;
        if (g_cbCount > 0) {
            do {
                ((void (*)())g_callbacks[i])();
                i++;
            } while (i < g_cbCount);
        }
    }
}

// ===========================================================================
//  FUN_01141740
// ===========================================================================
// @ 0x01141740
extern "C" int FUN_01141740(int param_1, int param_2)
{
    if (g_cbEnabled == 0)
        return 0xfffffff6;
    int o = (int)FUN_01132300(param_1);
    if (o == 0)
        return 0xfffffff8;
    void* t = *(void**)((char*)o + 4);
    ((MethodHolder*)t)->FUN_011e6cd0(param_2);
    return 0;
}

// ===========================================================================
//  FUN_01141780   (SFILTER filter function: pull decoded samples)
// ===========================================================================
// @ 0x01141780
extern "C" int FUN_01141780(SndFilter* f, int n, int unused, int buf)
{
    SndDecoder* dec = f->decoder;
    int written = 0;

    if (f->f28 != 0) {
        FUN_0113f8f0(f->f2c, f->b35, f->f28);
        f->f28 = 0;
    }

    while (written < n) {
        int base = written;
        if (f->f20 <= f->f24) {
            int out = 0;
            int r = FUN_0113f780(f->f2c, f->b35, &f->f20, &out);
            f->f30 = r;
            if (r == 0) {
                base = n;
                if (f->f28 != 0)
                    SNDMEMI_alloc((void*)(buf + written * 4), (n - written) * 4);
            } else {
                if (f->b1a == 0 || f->b34 > 2) {
                    if (out == 0)
                        ((Codec*)dec->codec)->FUN_01156dd0();
                    ((Codec*)dec->codec)->FUN_01156d70((void*)f->f30, 0x7fffffff, (void*)f->f20);
                }
                f->f24 = 0;
            }
        }

        int cnt = f->f20 - f->f24;
        if (n - base < cnt)
            cnt = n - base;
        f->f28 += cnt;
        f->f24 += cnt;

        if (cnt != 0) {
            if (f->b1a == 0) {
                if (f->b34 == 2) {
                    int c = (uint32_t)dec->w0c + cnt;
                    if (dec->f08 < c)
                        FUN_01158b10(&dec->f04, &dec->f08, c, 4);
                }
            } else if (f->b34 < 3) {
                FUN_011e0744((void*)(buf + base * 4),
                             (const void*)(*(int*)((char*)dec + 4) + (uint32_t)dec->w0e * 4),
                             cnt * 4);
                goto label;
            }

            {
                int local8 = buf + base * 4;
                int local4 = 0;
                if (f->b34 == 2)
                    local4 = *(int*)((char*)dec + 4) + (uint32_t)dec->w0c * 4;
                ((Codec*)dec->codec)->FUN_01156df0((void**)&local8, cnt);
            }
        }

    label:
        {
            int16_t* p = (int16_t*)((char*)dec + 0xc + f->b1a * 2);
            *p = (int16_t)(*p + cnt);
        }
        written = base + cnt;
        if (dec->w0c == dec->w0e) {
            dec->w0c = 0;
            dec->w0e = 0;
        }
    }
    return f->f28;
}

// ===========================================================================
//  FUN_01141920   (SFILTER restore function: release the decoder)
// ===========================================================================
// @ 0x01141920
extern "C" void FUN_01141920(SndFilter* f)
{
    if (f->decoder != 0) {
        f->decoder->refcnt--;
        if (f->decoder->refcnt == 0) {
            void* c = f->decoder->codec;
            if (c != 0) {
                ((Codec*)c)->FUN_01157430();
                FUN_011741b0(c);
            }
            void* p = (void*)f->decoder->f04;
            if (p != 0) {
                g_system->Free(p, 0);
                f->decoder->f04 = 0;
            }
            g_system->Free(f->decoder, 0);
            f->decoder = 0;
        }
    }
}

// ===========================================================================
//  SFILTER_unpackealayer3pinit  0x01141990
// ===========================================================================
// @ 0x01141990
extern "C" void SFILTER_unpackealayer3pinit(SndFilter* f, SndPatch* patch)
{
    if (patch->f08 == 2) {
        if (f->b1a != 0) {
            f->decoder = g_16e8060;
            g_16e8060->refcnt = 2;
            goto label;
        }
        g_16e8060 = (SndDecoder*)g_system->Alloc(0x1c, "ealayer3pdecode", 0x10, 0);
    } else {
        g_16e8060 = (SndDecoder*)g_system->Alloc(0x1c, "ealayer3pdecode", 0x10, 0);
    }
    f->decoder = g_16e8060;

    {
        void* d = FUN_011402c0(0x1d8);
        if (d != 0) {
            ((Codec*)d)->FUN_01157410();
            ((Codec*)d)->FUN_01156dd0();
        } else {
            d = 0;
        }
        g_16e8060->codec = d;
        g_16e8060->w0c = 0;
        g_16e8060->w0e = 0;
        f->decoder->refcnt = 1;
        f->decoder->f04 = 0;
        f->decoder->f08 = 0;
    }

label:
    f->filterfn = (void*)&FUN_01141780;
    f->restorefn = (void*)&FUN_01141920;
    f->f2c = FUN_01158b90(FUN_01140a00(patch->f18));
    f->decoder->f08 = 0;
    f->f20 = 0;
    f->f24 = 0;
    f->b34 = (uint8_t)patch->f08;
    f->f30 = 0;
    f->f28 = 0;
    f->b35 = FUN_01140a20(patch->f18);
}
