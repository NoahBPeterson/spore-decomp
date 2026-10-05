// SP::cSPEditorBlock — selection/pinning helpers (unoptimized /Od /Ob1 /arch:SSE).
#include "types.h"

namespace SP {

struct Vec3 { float x, y, z; };
struct Vec4 {
    float x, y, z, w;
    Vec4() {}
    Vec4(const Vec4& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};

// Intrusive 60-bit flag set reached through +0xDC8.
struct BitSet60 {
    uint32_t data[2];
    bool Get(int i) {
        if (i < 60) return (data[i >> 5] & (1u << (i % 32))) != 0;
        return false;
    }
};

// A 12-byte key element vector (begin/end at the head of the field).
struct KeyVec { void* begin; void* end; };

// Small local object used by the vector-building helper.
struct TmpKey { void Init(void* p); };

struct cSPEditorBlock {
    char     pad00[0x10];
    void*    mModel;                 // +0x10
    char     pad14[0x38 - 0x14];
    uint8_t  f38;                    // +0x38
    uint8_t  f39;                    // +0x39
    char     pad3a[2];
    uint32_t f3c;                    // +0x3C
    uint32_t f40;                    // +0x40
    uint32_t f44;                    // +0x44
    char     pad48[0x1C0 - 0x48];
    float    mBaseJointScale;        // +0x1C0
    float    mUniformScale;          // +0x1C4
    char     pad1c8[0x1D8 - 0x1C8];
    float    f1d8;                   // +0x1D8
    char     pad1dc[0x3E0 - 0x1DC];
    void*    p3e0;                   // +0x3E0
    char     pad3e4[0x3F4 - 0x3E4];
    char     tbl3f4[12];             // +0x3F4
    char     tbl400[12];             // +0x400
    char     pad40c[0xA44 - 0x40C];
    KeyVec   keys;                   // +0xA44
    char     padA4c[0xDC8 - 0xA4C];
    BitSet60 bits;                   // +0xDC8

    bool F3AC40(int type, uint8_t a, uint8_t b);          // 0043AC40
    bool F5a0();                                          // 0043A5A0
    bool F5c0();                                          // 0043A5C0
    float Length1();                                      // 0043A460
    Vec3* GetVec1(Vec3* out);                             // 0043A490
    float Length2();                                      // 0043A500
    Vec3* GetVec2(Vec3* out);                             // 0043A530
    bool F5e0(int type, uint8_t a, uint8_t b, char c);    // 0043A5E0
    void F830(uint8_t p);                                 // 0043A830
    int  GetSkinIdentifierForPicking();                   // 0043A870
    void F9a0(uint8_t a, uint8_t b);                      // 0043A9A0
    bool F9e0(uint8_t a, uint8_t b);                      // 0043A9E0
    bool Fb90(uint8_t p);                                 // 0043AB90
    void F3cfc0(uint8_t a, int b);                        // 0043CFC0
    void F448a80();                                       // 00448A80
    void F448690(Vec4 v);                                 // 00448690
    void F3cad0();                                        // 0043CAD0
    void F48C790(void* out, int flag);                    // 0048C790
};

float VectorLength(const Vec3* v);                        // 0040AE50
void* Sub_41DCA0(void* out, void* table, const float* key);  // 0041DCA0
bool  ModelKey_HasResourceType(void* modelKey);           // 00526430 (thiscall)
bool  Sub_43AC40_2(void* self, int type, uint8_t a, uint8_t b);  // 0043AC40 helper
void  Sub_429360(TmpKey* self, void* out);                // 00429360
void  Sub_4549B0(void* a, void* b, void* c, void* d);     // 004549B0
void  Sub_454280(void* p, int n);                         // 00454280
void  Sub_453EB0(void* v);                                // 00453EB0

extern const Vec4 g_v4_a;   // 015D21B8
extern const Vec4 g_v4_b;   // 015D21D4

// @ 0x0043A460
float cSPEditorBlock::Length1()
{
    Vec3 v;
    GetVec1(&v);
    return VectorLength(&v);
}

// @ 0x0043A490
Vec3* cSPEditorBlock::GetVec1(Vec3* out)
{
    float t = f1d8;
    float key = t;
    Vec3 tmp;
    Vec3* r = (Vec3*)Sub_41DCA0(&tmp, tbl3f4, &key);
    out->x = r->x;
    out->y = r->y;
    out->z = r->z;
    return out;
}

// @ 0x0043A500
float cSPEditorBlock::Length2()
{
    Vec3 v;
    GetVec2(&v);
    return VectorLength(&v);
}

// @ 0x0043A530
Vec3* cSPEditorBlock::GetVec2(Vec3* out)
{
    float t = f1d8;
    float key = t;
    Vec3 tmp;
    Vec3* r = (Vec3*)Sub_41DCA0(&tmp, tbl400, &key);
    out->x = r->x;
    out->y = r->y;
    out->z = r->z;
    return out;
}

// @ 0x0043A5E0
bool cSPEditorBlock::F5e0(int type, uint8_t a, uint8_t b, char c)
{
    uint8_t result = F3AC40(type, a, b) ? 1 : 0;
    if (c != 0 && !bits.Get(7)) {
        KeyVec list;
        list.begin = 0;
        list.end = 0;
        TmpKey tmp;
        Sub_429360(&tmp, &tmp);
        F48C790(&list, 0);
        void* end = list.end;
        void* begin = list.begin;
        Sub_4549B0(begin, list.begin, this, end);
        Sub_454280(list.begin, (int)((char*)list.end - (char*)list.begin));
        int count = (int)(((char*)list.end - (char*)list.begin) >> 2);
        for (int i = 0; i < count; i++) {
            uint8_t r = result;
            if (type == 0) {
                bool t = !F5a0() && !F5c0();
                uint8_t x = F3AC40(t ? 0 : 2, a, b) ? 1 : 0;
                result = r & x;
            } else if (type != 5) {
                uint8_t x = F3AC40(type, a, b) ? 1 : 0;
                result = r & x;
            }
        }
        Sub_453EB0(&list);
    }
    return result != 0;
}

// @ 0x0043A830
void cSPEditorBlock::F830(uint8_t p)
{
    if (Fb90(p)) {
        F5e0((int)f3c, 1, 0, 1);
    }
}

// @ 0x0043A870
int cSPEditorBlock::GetSkinIdentifierForPicking()
{
    int result = 3;
    bool useParent = false;
    if ((char*)&keys == 0) {
        useParent = true;
    } else {
        if (!ModelKey_HasResourceType(&keys)) {
            int count = (int)(((char*)keys.end - (char*)keys.begin) / 12);
            for (int i = 0; i < count; i++) {
                uint32_t id = *(uint32_t*)((char*)keys.begin + i * 12);
                if (id == 0xE16370D5u) result = 1;
                else if (id == 0x6189D2DEu) result = 0;
            }
        } else {
            useParent = true;
        }
    }
    if (useParent) {
        if (bits.Get(11)) result = 0;
        else result = 1;
    }
    return result;
}

// @ 0x0043A9A0
void cSPEditorBlock::F9a0(uint8_t a, uint8_t b)
{
    if (F9e0(a, b)) {
        F5e0((int)f3c, 1, 0, 1);
    }
}

// @ 0x0043A9E0
bool cSPEditorBlock::F9e0(uint8_t a, uint8_t b)
{
    if (bits.Get(1)) return false;
    if (f39 == a) return false;
    f40 = *(uint32_t*)&f38;
    f44 = f3c;
    if (f39 != 0) {
        F3cfc0(b, 0);
        F448a80();
    } else {
        void* model = mModel;
        if (model != 0) {
            *(uint32_t*)((char*)model + 4) |= 8;
            *(uint8_t*)((char*)model + 0x5C) = 7;
            F448690(g_v4_b);
        }
        F3cad0();
    }
    f39 = a;
    return true;
}

// @ 0x0043AB90
bool cSPEditorBlock::Fb90(uint8_t p)
{
    if (f38 == p) return false;
    f40 = *(uint32_t*)&f38;
    f44 = f3c;
    f38 = p;
    if (f3c == 3) {
        if (p == 0) {
            F448a80();
        } else {
            F448690(g_v4_a);
        }
    }
    return true;
}

} // namespace SP
