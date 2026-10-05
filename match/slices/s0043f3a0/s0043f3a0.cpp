// SP::cSPEditorBlock — validity/scale helpers (unoptimized /Od /Ob1 /arch:SSE).
#include "types.h"

namespace SP {

struct Vec3 { float x, y, z; };
struct Matrix3 { float m[9]; Matrix3() {} Matrix3(const Matrix3&); };

struct Node { bool Check(); };                 // 004ADC40
struct DefaultRefCounted { void Release(); };

struct BitSet60 {
    uint32_t data[2];
    bool Get(int i) {
        if (i < 60) return (data[i >> 5] & (1u << (i % 32))) != 0;
        return false;
    }
};

struct cSPEditorBlock {
    char             pad00[0x28];
    Node*            node;        // +0x28
    char             pad2c[0x33C - 0x2C];
    cSPEditorBlock*  link33c;     // +0x33C
    struct PtrVec {
        cSPEditorBlock** begin;
        cSPEditorBlock** end;
        int size() const { return (int)(end - begin); }
    }                vec340;      // +0x340
    char             pad348[0x3E0 - 0x348];
    cSPEditorBlock*  link3e0;     // +0x3E0
    char             pad3e4[0x3EC - 0x3E4];
    void*            p3ec;        // +0x3EC
    char             pad3f0[0x454 - 0x3F0];
    float            f454;        // +0x454
    char             pad458[0xDC8 - 0x458];
    BitSet60         bits;        // +0xDC8

    float F3eed0();                            // 0043EED0
    float F3f250();                            // 0043F250
    void  F3eef0(Vec3* out);                   // 0043EEF0
    void* F3f290(Vec3* out, int flag);         // 0043F290
    void  F404f0();                            // 004404F0
    void  F40420(float v, uint8_t b);          // 00440420
    void  F40520(float v, uint8_t b, int c);   // 00440520
    void  F3a5e0(int type, uint8_t a, uint8_t b, char c);  // 0043A5E0
    void  SetValid(char valid, int arg);       // 0043F6B0
    bool  F3fc20(void* pos);                   // 0043FC20

    float F3a0();                              // 0043F3A0
    float F3f0();                              // 0043F3F0
    float F4d0();                              // 0043F4D0
    void  F5b0(Vec3* out, float a, float b, float c, int flag);  // 0043F5B0
    void  FFa0(Matrix3 m);                     // 0043FFA0
    void  F4020(float v, uint8_t b);           // 00440020
    void  F4090(float v, uint8_t b);           // 00440090
    bool  F49b340();                           // 0049B340
};

void  Matrix3_Assign(Matrix3* dst, const Matrix3* src);       // 0041CB40
void  GetBBox(cSPEditorBlock* self, void* out, int, int, int); // from SetValid
void* Sub_41DB10(void* out, void* a, void* b);
void  Sub_4A8E10(Matrix3* out, const void* a, int b);
int   Sub_493640(void* v, float f);
void  Sub_4ADC20(int v);
void  Sub_4ADC40_is_NodeCheck(void);

// @ 0x0043F3A0
float cSPEditorBlock::F3a0()
{
    void* p = p3ec;
    if (p != 0) {
        return F3eed0() * 0.3f * 0.5f * f454;
    }
    return 0.0f;
}

// @ 0x0043F3F0
float cSPEditorBlock::F3f0()
{
    int count = vec340.size();
    for (int i = 0; i < count; i++) {
        cSPEditorBlock* o = vec340.begin[i];
        if (o->bits.Get(31)) return o->F3eed0();
    }
    return 1.0f;
}

// @ 0x0043F4D0
float cSPEditorBlock::F4d0()
{
    int count = vec340.size();
    for (int i = 0; i < count; i++) {
        cSPEditorBlock* o = vec340.begin[i];
        if (o->bits.Get(31)) return o->F3f250();
    }
    return 1.0f;
}

// @ 0x0043F5B0
void cSPEditorBlock::F5b0(Vec3* out, float a, float b, float c, int flag)
{
    Vec3 base;
    F3eef0(&base);
    if (flag > 0) {
        Vec3* p = (Vec3*)F3f290(&base, 0);
        if (0.0f > a + p->x) {
            Vec3* q = (Vec3*)F3f290(&base, 0);
            a = -q->x;
        }
    } else {
        Vec3* p = (Vec3*)F3f290(&base, 1);
        if (a + p->x >= 0.0f) {
            Vec3* q = (Vec3*)F3f290(&base, 1);
            a = -q->x;
        }
    }
    out->x = a;
    out->y = b;
    out->z = c;
}

// @ 0x0043FFA0
void cSPEditorBlock::FFa0(Matrix3 m)
{
    Matrix3 tmp;
    Matrix3_Assign(&tmp, &m);
    F404f0();
    if (node != 0 && node->Check() && link3e0 != 0) {
        Matrix3 tmp2;
        Sub_4A8E10(&tmp2, &m, 0);
        link3e0->F404f0();
    }
}

// @ 0x00440020
void cSPEditorBlock::F4020(float v, uint8_t b)
{
    F40420(v, b);
    if (node != 0) {
        if (node->Check() && link3e0 != 0) {
            link3e0->F40420(v, b);
        }
    }
}

// @ 0x00440090
void cSPEditorBlock::F4090(float v, uint8_t b)
{
    F40520(v, b, 0);
    if (node != 0) {
        if (node->Check() && link3e0 != 0) {
            link3e0->F40520(v, b, 0);
        }
    }
}

// @ 0x0043FC20
bool cSPEditorBlock::F3fc20(void* pos)
{
    int n = (int)node;
    if (n != 0) *(int*)(n + 8) = *(int*)(n + 8) + 1;
    uint8_t saved = node ? (uint8_t)(node->Check() ? 1 : 0) : 0;
    Sub_4ADC20(0);
    bool flag = (bits.data[1] & 0x80000u) != 0;
    uint8_t result = 0;
    if ((bits.data[0] & 0x80u) == 0) {
        Vec3* src = pos ? (Vec3*)pos : (Vec3*)((char*)this + 0x48);
        Vec3 local = *src;
        float f = F3eed0();
        (void)f;
        int r = Sub_493640(&local, f);
        uint8_t notThree = (uint8_t)(r != 3);
        if (notThree && !flag) result = 1;
        if (link33c == 0 && !F49b340()) result = 1;
        if ((bits.data[0] & 0x100000u) != 0) result = 0;
        if ((bits.data[1] & 0x400u) != 0) result = 1;
        if (link33c != 0 && (link33c->bits.data[0] & 2u) != 0) result = 1;
    }
    Sub_4ADC20((int)saved);
    bool b = result == 0;
    if (n != 0) ((DefaultRefCounted*)(n + 4))->Release();
    return b;
}

// @ 0x0043F6B0 (SP::cSPEditorBlock::SetValid) — complex; approximated.
void cSPEditorBlock::SetValid(char valid, int arg)
{
    uint8_t wasLinked = (uint8_t)((bits.data[1] & 2u) != 0);
    F3a5e0(1, (uint8_t)(valid == 0), 1, 0);
    if (valid == 0) {
        F3a5e0(1, 1, 0, 1);
        if (arg != 0 && (bits.data[1] & 0x400u) != 0) { }
        return;
    }
    F3a5e0(0, 1, 0, 0);
    if (arg != 0 && (bits.data[1] & 0x400u) != 0) { }
    (void)wasLinked;
}

} // namespace SP
