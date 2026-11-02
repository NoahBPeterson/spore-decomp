// src/game/SPBake/_at_00430000.cpp -- migrated from slice(s) s0043a460 by tools/migrate/rewrite.py
// Object file: SPBake/_at_00430000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s0043a460 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Vec3 { float x, y, z; };
}
namespace SP {
struct Vec4 {
    float x, y, z, w;
    Vec4() {}
    Vec4(const Vec4& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};
}
namespace SP {
class cSPEditorBlock_s0043_a460;
}
namespace SP {
enum eBlockUIState_s0043_a460 { kUIState0_s0043_a460 = 0, kUIState1_s0043_a460, kUIState2_s0043_a460, kUIState3_s0043_a460, kUIState4_s0043_a460, kUIState5_s0043_a460 };
}
namespace SP {
struct BitSet60 {
    uint32_t data[2];
    bool Get(int i) {
        if (i < 60) return (data[i >> 5] & (1u << (i % 32))) != 0;
        return false;
    }
};
}
namespace SP {
struct KeyVec {
    void* begin;
    void* end;
    bool empty() const;   // 0x00526430
};
}
namespace SP {
class cSPEditorBlock_s0043_a460 { public:
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
    bool SetUIState(eBlockUIState_s0043_a460 state, bool b1, bool b2, bool b3);   // 0x0043A5E0
    void F830(uint8_t p);                                 // 0043A830
    int  GetSkinIdentifierForPicking();                   // 0043A870 0x0043a870
    void F9a0(uint8_t a, uint8_t b);                      // 0043A9A0
    bool F9e0(uint8_t a, uint8_t b);                      // 0043A9E0
    bool Fb90(uint8_t p);                                 // 0043AB90
    void F3cfc0(int a, uint8_t b);                        // 0043CFC0
    void F448a80();                                       // 00448A80
    void F448690(Vec4 v);                                 // 00448690
    void F3cad0();                                        // 0043CAD0
};
}
namespace SP {
float VectorLength(const Vec3* v);                        // 0040AE50
}
namespace SP {
void* Sub_41DCA0(void* out, void* table, const float* key);  // 0041DCA0
}
// ---- items of slice s0043a460 end

// @ 0x0043a460
namespace SP {
float cSPEditorBlock_s0043_a460::Length1()
{
    Vec3 v;
    GetVec1(&v);
    return VectorLength(&v);
}
}  // namespace SP

// @ 0x0043a490
namespace SP {
Vec3* cSPEditorBlock_s0043_a460::GetVec1(Vec3* out)
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
}  // namespace SP

// @ 0x0043a500
namespace SP {
float cSPEditorBlock_s0043_a460::Length2()
{
    Vec3 v;
    GetVec2(&v);
    return VectorLength(&v);
}
}  // namespace SP

// @ 0x0043a530
namespace SP {
Vec3* cSPEditorBlock_s0043_a460::GetVec2(Vec3* out)
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
}  // namespace SP
