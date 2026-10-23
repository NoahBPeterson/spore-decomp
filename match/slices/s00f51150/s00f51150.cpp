// s00f51150 -- FUN_00f51150  0x00f51150 (1285 bytes)
//
// Simulator object constructor (__thiscall, one pointer argument, ret 4).  Three inlined
// base-class constructors write the GB1 / GameRefCount vtable slots at +4/+8 first, then the
// derived vtable at +0/+4/+8, followed by a long run of member initialisers, the two
// rw::math::Vector constructors (by-value temporaries built from global vectors), the matrix
// construction from DAT_016c9174, an AddRef on the passed-in object, the cLocalInputState
// construction at +0x31c, and finally the second member-init run.
//
// Every float initialiser reads a global float (declared below as a one-member struct so the
// compiler lowers the load/store pair through SSE), and the two Vector arguments are non-POD
// by-value temporaries copied from global vectors -- both are exactly the code shapes the
// original emits.

struct F1 { float f; };

extern F1 c13eb1bc, c1486110, c1488874, c1447a28, c1473c70, c145cff4, c145cff0,
          c145cfec, c1447a08, c13ec4d0, c16c9058, c16c905c, c16c9060,
          c1485720, c13f0620, c1485ac0, c147b9f0, c142eae0, c145cfe8;

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Vec4 {
    float x, y, z, w;
    Vec4() {}
    Vec4(const Vec4& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};

extern Vec3 gVec3Src;   // 0x015b0aac
extern Vec4 gVec4Src;   // 0x015b0ab8

struct VCtor3 { void FUN_00f4f5a0(Vec3 v); };     // 0x00f4f5a0
struct VCtor4 { void FUN_00f4fe50(Vec4 v); };     // 0x00f4fe50
struct MCtor  { void FUN_0041cb40(void* src); };  // rw::math::fpu::Matrix33Template<float,0>::Matrix33Template 0x0041cb40

struct IRefCount { virtual void AddRef(); };
struct C00f51150Stub { void* FUN_00f51150(void* param_2); };

extern "C" void __fastcall FUN_00697960(void* self);   // 0x00697960  SP::cLocalInputState

// ---
// @ 0x00f51150
// ---
void* C00f51150Stub::FUN_00f51150(void* param_2)
{
    char* self = (char*)this;
    float k260 = c13eb1bc.f;
    float zero = 0.0F;
    float k274 = c1486110.f;
    float f, g;

    // --- inlined base constructor: GB1 / GameRefCount vtable slots ---
    *(volatile int*)(self + 4) = 0x13eb384;
    *(volatile int*)(self + 8) = 0x13ef094;
    *(int*)(self + 0xc) = 0;
    // --- derived vtable ---
    *(int*)(self + 0) = 0x148e810;
    *(int*)(self + 4) = 0x148e7fc;
    *(int*)(self + 8) = 0x148e7f8;
    *(unsigned char*)(self + 0x10) = 1;
    *(unsigned char*)(self + 0x11) = 0;
    *(unsigned char*)(self + 0x12) = 0;
    *(unsigned char*)(self + 0x13) = 0;
    *(unsigned char*)(self + 0x14) = 0;
    *(unsigned char*)(self + 0x15) = 0;
    *(unsigned char*)(self + 0x16) = 0;
    *(unsigned char*)(self + 0x168) = 0;
    *(unsigned char*)(self + 0x169) = 0;
    *(int*)(self + 0x16c) = 0;
    *(int*)(self + 0x170) = 0;
    *(int*)(self + 0x174) = 0;

    *(int*)(self + 0x180) = 0;
    *(int*)(self + 0x184) = 0;
    *(int*)(self + 0x188) = 0;
    *(int*)(self + 0x194) = 0;
    *(int*)(self + 0x198) = 0;
    *(int*)(self + 0x19c) = 0;
    *(int*)(self + 0x1a8) = 0;
    *(int*)(self + 0x1ac) = 0;
    *(int*)(self + 0x1b0) = 0;
    *(int*)(self + 0x1bc) = 0;
    *(int*)(self + 0x1c0) = 0;
    *(int*)(self + 0x1c4) = 0;
    *(int*)(self + 0x1d0) = 0;
    *(int*)(self + 0x1d4) = 0;
    *(int*)(self + 0x1d8) = 0;
    *(int*)(self + 0x1e4) = 0;
    *(int*)(self + 0x1e8) = 0;
    *(int*)(self + 0x1ec) = 0;
    *(int*)(self + 0x1f8) = 0;
    *(int*)(self + 0x1fc) = 0;
    *(int*)(self + 0x200) = 0;
    *(int*)(self + 0x20c) = 0;
    *(int*)(self + 0x210) = 0;
    *(int*)(self + 0x214) = 0;
    *(int*)(self + 0x220) = 0;
    *(int*)(self + 0x224) = 0;
    *(int*)(self + 0x228) = 0;
    *(int*)(self + 0x234) = 0;
    *(int*)(self + 0x238) = 0;
    *(int*)(self + 0x23c) = 0;
    *(int*)(self + 0x248) = 0;
    *(int*)(self + 0x24c) = 0;
    *(int*)(self + 0x250) = 0;

    *(float*)(self + 0x25c) = zero;
    *(float*)(self + 0x260) = k260;

    f = c1488874.f;
    *(float*)(self + 0x278) = f;
    *(float*)(self + 0x27c) = f;
    *(float*)(self + 0x280) = f;
    *(float*)(self + 0x284) = f;
    *(float*)(self + 0x288) = f;

    *(float*)(self + 0x290) = c1447a28.f;
    *(float*)(self + 0x294) = c1473c70.f;
    *(float*)(self + 0x298) = c145cff4.f;
    *(float*)(self + 0x29c) = c145cff0.f;

    f = c145cfec.f;
    *(float*)(self + 0x264) = zero;
    *(float*)(self + 0x268) = zero;
    *(float*)(self + 0x26c) = zero;
    *(float*)(self + 0x270) = zero;
    *(float*)(self + 0x274) = k274;
    *(float*)(self + 0x28c) = zero;
    *(float*)(self + 0x2ac) = zero;

    g = c1447a08.f;
    *(float*)(self + 0x2a0) = f;
    f = c13ec4d0.f;
    *(float*)(self + 0x2b0) = g;
    *(float*)(self + 0x2a4) = f;
    *(float*)(self + 0x2a8) = f;
    *(float*)(self + 0x2b4) = k274;

    *(unsigned short*)(self + 0x2cc) = 0;
    *(unsigned short*)(self + 0x2ce) = 0;
    *(float*)(self + 0x2d0) = c16c9058.f;
    *(float*)(self + 0x2d4) = c16c905c.f;
    *(float*)(self + 0x2d8) = c16c9060.f;
    *(float*)(self + 0x2dc) = c1485720.f;

    ((MCtor*)(self + 0x2e0))->FUN_0041cb40((void*)0x16c9174);

    *(unsigned char*)(self + 0x304) = 1;
    *(int*)(self + 0x308) = 0;
    *(void**)(self + 0x30c) = param_2;
    if (param_2 != 0) {
        ((IRefCount*)param_2)->AddRef();
    }

    *(float*)(self + 0x310) = c1485720.f;
    *(float*)(self + 0x314) = c13f0620.f;
    *(unsigned char*)(self + 0x318) = 0;
    *(unsigned char*)(self + 0x319) = 0;
    *(unsigned char*)(self + 0x31a) = 0;

    FUN_00697960(self + 0x31c);

    f = c1485ac0.f;
    g = c1473c70.f;
    *(float*)(self + 0x368) = f;
    *(float*)(self + 0x374) = f;
    *(float*)(self + 0x378) = c147b9f0.f;
    *(float*)(self + 0x36c) = g;
    *(float*)(self + 0x37c) = c142eae0.f;
    *(float*)(self + 0x370) = c1485720.f;
    *(unsigned char*)(self + 0x364) = 1;
    *(unsigned char*)(self + 0x365) = 1;
    *(int*)(self + 0x380) = 0x3e9;

    *(unsigned char*)(self + 0x18) = 0;
    *(unsigned char*)(self + 0x19) = 0;
    *(float*)(self + 0x20) = zero;
    *(float*)(self + 0x1c) = zero;
    *(float*)(self + 0x30) = zero;
    *(float*)(self + 0x2c) = zero;
    *(float*)(self + 0x28) = zero;
    *(float*)(self + 0x24) = zero;
    *(float*)(self + 0x34) = zero;
    *(float*)(self + 0x38) = zero;

    ((VCtor3*)(self + 0x3c))->FUN_00f4f5a0(gVec3Src);
    ((VCtor4*)(self + 0x90))->FUN_00f4fe50(gVec4Src);

    f = c1485720.f;
    *(float*)(self + 0x114) = f;
    *(float*)(self + 0x110) = f;
    *(float*)(self + 0x10c) = f;
    *(float*)(self + 0x108) = f;

    f = c145cfe8.f;
    *(unsigned char*)(self + 0xfc) = 0;
    *(unsigned char*)(self + 0xfd) = 0;
    *(float*)(self + 0x104) = zero;
    *(float*)(self + 0x100) = zero;
    *(float*)(self + 0x118) = zero;
    *(float*)(self + 0x11c) = zero;
    *(unsigned char*)(self + 0x120) = 0;
    *(unsigned char*)(self + 0x121) = 0;
    *(float*)(self + 0x128) = zero;
    *(float*)(self + 0x124) = zero;
    *(float*)(self + 0x138) = f;
    *(float*)(self + 0x134) = f;
    *(float*)(self + 0x130) = f;
    *(float*)(self + 0x12c) = f;
    *(float*)(self + 0x13c) = zero;
    *(float*)(self + 0x140) = zero;
    *(unsigned char*)(self + 0x144) = 0;
    *(unsigned char*)(self + 0x145) = 0;
    *(float*)(self + 0x14c) = zero;
    *(float*)(self + 0x148) = zero;
    *(float*)(self + 0x15c) = zero;
    *(float*)(self + 0x158) = zero;
    *(float*)(self + 0x154) = zero;
    *(float*)(self + 0x150) = zero;
    *(float*)(self + 0x160) = zero;
    *(float*)(self + 0x164) = zero;

    return self;
}
