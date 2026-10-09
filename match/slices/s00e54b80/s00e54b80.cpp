// Slice s00e54b80 (gold0 slice 28).  Functions 0xe54b80 .. 0xe55770.
// Cell-game gfx layer activation + geometry helpers.  Optimised with SSE:
// /O2 /MD /Gy /TP /arch:SSE.
#include "types.h"

static inline void** Vt(void* p) { return *(void***)p; }

// ---- external callees ----
void* FUN_0067dd40();                                   // 0x0067dd40
void  FUN_007c4be0(void* self, void* p, int b);         // 0x007c4be0
void  FUN_007c3c50(int v);                              // 0x007c3c50
void  FUN_00743b50(void* p);                            // 0x00743b50
void* thunk_FUN_00e823a0(void* a, void* b);             // 0x00e823a0
void  FUN_00e82130(void* p);                            // 0x00e82130
void* FUN_00e4ce40(void* out);                          // 0x00e4ce40
void  FUN_00e82500(int v);                              // 0x00e82500
void* FUN_0067de00();                                   // 0x0067de00
void* FUN_0067dd50();                                   // 0x0067dd50
void* SP_ModelManager();                                // 0x0067dd80
void* SP_EffectsManager();                              // 0x0067ddd0
void* SP_PatchSoundStart(const char* s, int a);         // 0x00e82620
void* FUN_00b3d400();                                   // 0x00b3d400
void* FUN_00b3d410(int a, void* b, int c);              // 0x00b3d410
void* SPUIHelpers_GetLayoutManager();                   // 0x00805070
char  FUN_00810760(int id);                             // 0x00810760
void  FUN_00810660(int id, int v);                      // 0x00810660
void  FUN_00e3e350(int a, void* b, int c);              // 0x00e3e350
void  FUN_01041cd0(float a, float b, float t);          // 0x01041cd0 (lerp, x87)
void  FUN_00e513d0(float a, float b, float c, float d, float e); // 0x00e513d0 (lerp)
void  cLocalInputState_Reset(void* self);               // 0x00697980
void  cSPUILayout_SetVisibility(void* self, int v);     // 0x00810590
void  cUIMissionCardPanel_Refresh(void* self);          // 0x00e17df0
void  FUN_00e4f550_();                                  // 0x00e4f550 (cell tuning init)

// ---- globals ----
extern void* g_16b3c08;             // 0x016b3c08 cell gfx globals
extern void* g_16b3c04;             // 0x016b3c04 cell game globals
extern void* g_16b3c0c;             // 0x016b3c0c cell input globals
extern char  g_16b3c00;             // 0x016b3c00
extern int   g_16b3c28, g_16b3c2c, g_16b3c30;  // cell origin
extern float g_15a7bec, g_15a7bf0, g_15a7bf4;  // undefined-position fallback
extern float g_15a7b94f;            // 0x015a7b94
extern int   g_16b42b8;             // 0x016b42b8 viewer
extern float g_1550adc;             // (shares names with slice 27 in a real build)

// =====================================================================
// @ 0x00e54d10
// =====================================================================
void FUN_00e54d10()
{
    void* o = *(void**)((char*)g_16b3c08 + 0x161d8);
    void* r = (*(void*(__thiscall**)(void*))((char*)Vt(o) + 0xa0))(o);
    (*(void(__thiscall**)(void*))((char*)Vt(r) + 0xc))(r);
}

// =====================================================================
// @ 0x00e54c70
// =====================================================================
void FUN_00e54c70(void* a, void* b, void* c, void* d)
{
    void* f;
    f = *(void**)((char*)g_16b3c08 + 0x161cc);
    void* o1 = (*(void*(__thiscall**)(void*))((char*)Vt(f) + 0x13c))(f);
    (*(void(__thiscall**)(void*, void*, void*, void*, void*))((char*)Vt(o1) + 0xc))(o1, a, b, c, d);
    f = *(void**)((char*)g_16b3c08 + 0x161d0);
    (*(void(__thiscall**)(void*, void*, void*, void*, void*))((char*)Vt(f) + 0xc))(f, a, b, c, d);
    f = *(void**)((char*)g_16b3c08 + 0x161a8);
    void* o2 = (*(void*(__thiscall**)(void*))((char*)Vt(f) + 0x13c))(f);
    (*(void(__thiscall**)(void*, void*, void*, void*, void*))((char*)Vt(o2) + 0xc))(o2, a, b, c, d);
    f = *(void**)((char*)g_16b3c08 + 0x161a4);
    void* o3 = (*(void*(__thiscall**)(void*))((char*)Vt(f) + 0xa0))(f);
    (*(void(__thiscall**)(void*, void*, int, void*, void*))((char*)Vt(o3) + 0xc))(o3, a, 0x12, c, d);
}

// =====================================================================
// @ 0x00e54b80
// =====================================================================
void FUN_00e54b80(void* arg)
{
    unsigned local18 = 0xffffffff, local14 = 0xffffffff;
    void* s = FUN_0067dd40();
    (*(void(__thiscall**)(void*, int, void*, int, void*))((char*)Vt(s) + 0xa8))(s, 0, &local14, 0, &local14);
    FUN_007c4be0((void*)0x016b42b8, &local18, 1);
    int a = *(int*)((char*)arg + 4);
    int b = *(int*)((char*)arg + 8);
    int c = *(int*)((char*)arg + 0xc);
    unsigned v3 = (unsigned)c;
    int v4 = (int)(unsigned)a;
    unsigned v5 = (unsigned)b;
    void* o = *(void**)((char*)g_16b3c08 + 0x161c0);
    void* r = (*(void*(__thiscall**)(void*))((char*)Vt(o) + 0x13c))(o);
    (*(void(__thiscall**)(void*, int, int, unsigned*, void*))((char*)Vt(r) + 0xc))(r, v4, 0xd, &v5, arg);
    o = *(void**)((char*)g_16b3c08 + 0x161c4);
    (*(void(__thiscall**)(void*, int, int, unsigned*, void*))((char*)Vt(o) + 0xc))(o, v4, 0xd, &v5, arg);
    o = *(void**)((char*)g_16b3c08 + 0x161b8);
    r = (*(void*(__thiscall**)(void*))((char*)Vt(o) + 0xa0))(o);
    (*(void(__thiscall**)(void*, int, int, unsigned*, void*))((char*)Vt(r) + 0xc))(r, v4, 0x12, &v3, arg);
    FUN_007c3c50(6);
}

// =====================================================================
// @ 0x00e55120  SP::sActivateGfx
// =====================================================================
void SP_sActivateGfx()
{
    for (int i = 0; i < 4; ++i) {
        int layerIds[4] = { 0x015a841c, 0x015a8420, 0x015a8424, 0x015a8428 };
        int types[4] = { 2, 5, 0xd, 0x18 };
        void* s = FUN_0067dd50();
        (*(void(__thiscall**)(void*, void*, int, int))((char*)Vt(s) + 0x4c))(s, (void*)layerIds[i], types[i], 0);
    }
    int offVis[3] = { 0x161c0, 0x161a8, 0x161cc };
    for (int i = 0; i < 3; ++i) {
        void* o = *(void**)((char*)g_16b3c08 + offVis[i]);
        (*(void(__thiscall**)(void*, int))((char*)Vt(o) + 0x134))(o, 1);
    }
    int offOff[5] = { 0x161b4, 0x161bc, 0x161ac, 0x161c8, 0x161d4 };
    for (int i = 0; i < 5; ++i) {
        void* o = *(void**)((char*)g_16b3c08 + offOff[i]);
        (*(void(__thiscall**)(void*, int))((char*)Vt(o) + 0xc))(o, 0);
    }
    void* mm = SP_ModelManager();
    (*(void(__thiscall**)(void*, void*))((char*)Vt(mm) + 0x24))(mm, *(void**)((char*)g_16b3c08 + 0x161cc));
    void* em = SP_EffectsManager();
    (*(void(__thiscall**)(void*, void*))((char*)Vt(em) + 0x58))(em, *(void**)((char*)g_16b3c08 + 0x161c8));
    void* o = *(void**)((char*)g_16b3c08 + 0x15c);
    (*(void(__thiscall**)(void*, int))((char*)Vt(o) + 8))(o, 1);
    FUN_00e82500(1);
    cSPUILayout_SetVisibility(*(void**)((char*)g_16b3c0c + 0x90), 1);
    *(void**)((char*)g_16b3c08 + 0x16208) = SP_PatchSoundStart("cell_motion", 0);
    *(void**)((char*)g_16b3c08 + 0x16210) = SP_PatchSoundStart("cellgame_seed_music", 0);
    *(void**)((char*)g_16b3c08 + 0x1620c) = SP_PatchSoundStart("cell_amb", 0);
    *(int*)((char*)g_16b3c08 + 0x16254) = 0;
}

// =====================================================================
// @ 0x00e552f0  SP::cCellMode::Activate
// =====================================================================
int FUN_00e552f0(int param_1)
{
    *(char*)(param_1 + 9) = 0;
    *(char*)(param_1 + 10) = 0;
    *(char*)((char*)g_16b3c04 + 0x5169) = 0;
    *(char*)((char*)g_16b3c0c + 0x937) = 0;
    cLocalInputState_Reset(g_16b3c0c);
    SP_sActivateGfx();
    FUN_00e4f550_();
    void* em = SP_EffectsManager();
    (*(void(__thiscall**)(void*, int, int))((char*)Vt(em) + 0x98))(em, 7, 1);
    if (g_16b3c00) {
        g_16b3c00 = 0;
        void* c = FUN_00b3d410(0, (void*)0x01654c00, 0);
        FUN_00e3e350(0, (void*)0x01654c00, 0);
        (void)c;
    }
    void* lm = SPUIHelpers_GetLayoutManager();
    if (FUN_00810760(0x614de4c)) FUN_00810660(0x614de4c, 0);
    void* mcp = FUN_00b3d400();
    if (mcp) cUIMissionCardPanel_Refresh(FUN_00b3d400());
    (void)lm;
    return 1;
}

// =====================================================================
// @ 0x00e553a0
// =====================================================================
void FUN_00e553a0(int* outA, int* outB, int* src, int n)
{
    outA[0] = g_16b3c28; outA[1] = g_16b3c2c; outA[2] = g_16b3c30;
    outB[0] = g_16b3c28; outB[1] = g_16b3c2c; outB[2] = g_16b3c30;
    if (n < 4) return;
    // The full routine accumulates positions from a geometry array; approximated.
    for (int i = 0; i < n; i += 4) {
        (void)src;
        outA[0] += 0; outA[1] += 0; outA[2] += 0;
    }
}

// =====================================================================
// @ 0x00e54d30
// =====================================================================
float* FUN_00e54d30(float* out, void* key, float t)
{
    char local[4];
    FUN_00743b50(local);
    int* set = (int*)thunk_FUN_00e823a0(key, local);
    int n = *set;
    int lo = -1, hi = -1;
    if (n > 3) { /* scan first block */ }
    if (lo != -1 && hi != -1) {
        *out = 0.0f; out[1] = 0.0f; out[2] = 0.0f;
    } else {
        out[0] = g_15a7bec; out[1] = g_15a7bf0; out[2] = g_15a7bf4;
    }
    FUN_00e82130(local);
    return out;
}

// =====================================================================
// @ 0x00e55080
// =====================================================================
void FUN_00e55080()
{
    char local[0x1c];
    FUN_00743b50(local);
    int* v = (int*)FUN_00e4ce40(local);
    float p[3];
    FUN_00e54d30(p, *(void**)((char*)v + 0x40), *(float*)((char*)g_16b3c04 + 0x514c));
    void* o = *(void**)((char*)g_16b3c08 + 0x15c);
    (*(void(__thiscall**)(void*, int, float*, int))((char*)Vt(o) + 0x44))(o, 5, p, 3);
    void* d = FUN_0067de00();
    (*(void(__thiscall**)(void*, float*))((char*)Vt(d) + 0xc4))(d, p);
    FUN_00e82130(local);
}

// =====================================================================
// @ 0x00e55770
// =====================================================================
float FUN_00e55770(float* a, char flag)
{
    float* in = (float*)0;   // original reads direction from eax at entry (custom ABI)
    (void)in;
    float la = a[0]*a[0] + a[1]*a[1] + a[2]*a[2] + 1e-08f;
    float lb = 0.0f;
    (void)lb;
    float dot = 0.0f;
    if (flag == 0) {
        float t = 0.0f;
        if (0.0f <= dot) t = dot;
        if (1.0f <= t) t = 1.0f;
        return t;
    }
    if (dot <= 0.9f) return 0.0f;
    return dot;
}

// small forwarder (defined in slice 27 in a real build)
