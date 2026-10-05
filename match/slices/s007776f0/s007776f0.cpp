// slice s007776f0: shader-profile helpers and D3D shader-state setters.
// Small routines are reconstructed; the large EH-framed/loop routines are
// skeletons (partial).
#include "types.h"
#include <xmmintrin.h>

// ---------------------------------------------------------------------------
// @ 0x007776f0  SP::PSProfileFromVersion
extern char g_psProfile[];   // 0x01539ec0 ("ps_x_x")
char* PSProfileFromVersion(unsigned int version) {
    int lo = (int)(version & 0xff);
    g_psProfile[3] = (char)(version >> 8) + '0';
    char c = (char)lo;
    if (lo < 10)
        c = c + '0';
    g_psProfile[5] = c;
    return g_psProfile;
}

// ---------------------------------------------------------------------------
// @ 0x007779e0  copy a 0x40-byte matrix (four movaps)
struct __declspec(align(16)) Mat44 {
    __m128 r[4];
    void assignTo(Mat44* dst) const;  // @ 0x007779e0
};
void Mat44::assignTo(Mat44* dst) const {
    dst->r[0] = r[0];
    dst->r[1] = r[1];
    dst->r[2] = r[2];
    dst->r[3] = r[3];
}

// ---------------------------------------------------------------------------
// D3D shader-state setters over an object with a 0x18 header and 0x10-byte slots
// ---------------------------------------------------------------------------
struct ShaderState {
    char pad[0x18];
    void setSlotU0(int idx, char v);  // @ 0x00777a60
    void setSlotU1(int idx, char v);  // @ 0x00777a80
    void setSlotV0(int idx, char v);  // @ 0x00777aa0
    void setSlotV1(int idx, char v);  // @ 0x00777ac0
};

void ShaderState::setSlotU0(int idx, char v) {
    char* p = (char*)this + idx * 0x10;
    p[0x18] = p[0x18] | 1;
    p[0x19] = v;
}
void ShaderState::setSlotU1(int idx, char v) {
    char* p = (char*)this + idx * 0x10;
    p[0x18] = p[0x18] | 2;
    p[0x1a] = v;
}
void ShaderState::setSlotV0(int idx, char v) {
    char* p = (char*)this + idx * 0x10;
    p[0x18] = p[0x18] | 4;
    p[0x1b] = v;
}
void ShaderState::setSlotV1(int idx, char v) {
    char* p = (char*)this + idx * 0x10;
    p[0x18] = p[0x18] | 8;
    p[0x1c] = v;
}

// ---------------------------------------------------------------------------
// Shader-data stack (array of 8-byte {short key; short pad; int value})
// ---------------------------------------------------------------------------
struct ShaderStackEntry {
    short key;
    short pad;
    int value;
};
extern ShaderStackEntry g_shaderStack[];  // 0x016312f0
extern int g_shaderStackTop;              // 0x01632bf0

// @ 0x00777bf0
void pushShaderDataNull() {
    int top = g_shaderStackTop;
    g_shaderStack[top].key = 0;
    g_shaderStack[top].value = 0;
    g_shaderStackTop = top + 1;
}

// @ 0x00777c90
extern char g_shaderStackRaw[];  // 0x016312e8 (= g_shaderStack - 8)
int shaderDataStackNotEmpty() {
    if (g_shaderStackTop > 0 && *(short*)(g_shaderStackRaw + g_shaderStackTop * 8) != 0)
        return 1;
    return 0;
}

// @ 0x00778050
extern int g_table1631ef0[];  // 0x01631ef0
int tableLookup(unsigned short idx) {
    return g_table1631ef0[idx];
}

// ---------------------------------------------------------------------------
// Skeletons (partial).
// ---------------------------------------------------------------------------
void FUN_00777720(int* a, int b, int c) { (void)a; (void)b; (void)c; }
int  FUN_00777740(int* a) { (void)a; return 0; }
int  FUN_00777760(int a, int b) { (void)a; (void)b; return 1; }
int  FUN_00777840(int a, int b, int c) { (void)a; (void)b; (void)c; return 0; }
int  FUN_00777a10() { return 1; }
void FUN_00777ae0(unsigned short a, int b, int c) { (void)a; (void)b; (void)c; }
void FUN_00777b50(int a) { (void)a; }
void FUN_00777c10() {}
void FUN_00777cb0(int a) { (void)a; }
void FUN_00777d60(int a, int b, int c) { (void)a; (void)b; (void)c; }
void FUN_00777e10(int a) { (void)a; }
void FUN_00777e30(int a) { (void)a; }
void FUN_00777e50(int a, int b, int c) { (void)a; (void)b; (void)c; }
void FUN_00777e90(int a, int b, int c) { (void)a; (void)b; (void)c; }
void FUN_00777ed0(int a, int b, int c) { (void)a; (void)b; (void)c; }
void FUN_00777f80(int a, int b, int c) { (void)a; (void)b; (void)c; }
