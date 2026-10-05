// slice s004582b0 -- SP::cSPEditorBudget::Update and small editor/ui helpers.
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast module.
#include "types.h"

struct Float3 { float x, y, z; };
struct Float4 { float x, y, z, w; };

// @ 0x00458a40 -- RGB -> U32 with opaque alpha
unsigned int ColorRGBToU32(const float* c) {
    float r = c[0] > 0.0f ? c[0] : 0.0f;
    r = r * 255.0f;
    if (r > 255.0f) r = 255.0f;
    float g = c[1] > 0.0f ? c[1] : 0.0f;
    g = g * 255.0f;
    if (g > 255.0f) g = 255.0f;
    float b = c[2] > 0.0f ? c[2] : 0.0f;
    b = b * 255.0f;
    if (b > 255.0f) b = 255.0f;
    unsigned char ri = (unsigned char)(int)r;
    unsigned char gi = (unsigned char)(int)g;
    unsigned char bi = (unsigned char)(int)b;
    return ((unsigned int)ri << 0x10) | ((unsigned int)gi << 8) | (unsigned int)bi | 0xff000000u;
}

struct cSPUITooltipWinProc {
    void SetText(void* text, int a, int b);   // 0x00835ed0
};

struct Budget2 {
    char pad0[0x40];
    cSPUITooltipWinProc* mTooltip;   // +0x40

    void SetTooltip(void* p);        // 0x00458b50
    void* InitLayoutWidget();       // 0x00458c00
};

// @ 0x00458b50
void Budget2::SetTooltip(void* p) {
    if (p != 0) {
        cSPUITooltipWinProc* t = mTooltip;
        t->SetText(p, -1, 1);
    }
}

extern void* g_layout;   // 0x015d2dbc

// @ 0x00458c00
extern void FUN_00422c80(void* out);
void* Budget2::InitLayoutWidget() {
    int* p = (int*)((char*)this + 0x14);
    char local[4];
    FUN_00422c80(local);
    ((int*)this)[1] = (int)p;
    ((int*)this)[0] = ((int*)this)[1];
    ((int*)this)[2] = ((int*)this)[0] + 0x20;
    *(unsigned short*)((int*)((int*)this)[0]) = 0;
    return this;
}

// @ 0x00458d80
extern void FUN_00811ad0(void* layout, int one);
void FUN_00458d80() {
    if (g_layout != 0) {
        FUN_00811ad0(g_layout, 1);
        if (g_layout != 0) {
            void* old = g_layout;
            g_layout = 0;
            if (old != 0)
                ((void(__thiscall*)(void*))(*(void***)old)[2])(old);
        }
    }
}

// @ 0x00458de0
extern void SPUIHelpers_GetImageFromLayout(void* layout, unsigned int param);
void FUN_00458de0(unsigned int param) {
    void* p = g_layout;
    SPUIHelpers_GetImageFromLayout(p, param);
}

// @ 0x00458e00
int FUN_00458e00(int id) {
    int r = 0x157aa4e5;
    switch (id) {
        case 0x8f963dcb:
        case 0x441cd3e6:
        case 0x7d433fad:
            r = 0xfd503a02; break;
        case 0xf670aa43:
        case 0x1a4e0708:
        case 0x2a5147a9:
            r = 0x0f615124; break;
        case 0x1f2a25b6:
        case 0x9ad7d4aa:
        case 0x449c040f:
            r = 0x10c8a72e; break;
        default:
            break;
    }
    return r;
}

// @ 0x00458eb0
int FUN_00458eb0(int id) {
    int r = 0x11b78a72;
    switch (id) {
        case 0x8f963dcb:
        case 0x441cd3e6:
        case 0x7d433fad:
            r = 0x06329468; break;
        case 0xf670aa43:
        case 0x1a4e0708:
        case 0x2a5147a9:
            r = 0x0632946a; break;
        case 0x1f2a25b6:
        case 0x9ad7d4aa:
        case 0x449c040f:
            r = 0x06329469; break;
        default:
            break;
    }
    return r;
}

// @ 0x004582b0 -- cSPEditorBudget::Update (1930 bytes, only outlined)
void cSPEditorBudget_Update() {
}

// @ 0x00458c60 -- PreloadLayout (only outlined)
char FUN_00458c60(unsigned int param) {
    (void)param;
    return 0;
}
