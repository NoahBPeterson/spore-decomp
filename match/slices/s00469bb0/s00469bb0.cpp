// s00469bb0

typedef unsigned int uint32_t;
template <int N> inline void ScratchSlots()
{
    uint32_t s[N];
    (void)s;
}

struct V3 {
    float x, y, z;
    V3(const V3& o) { x = o.x; y = o.y; z = o.z; }
};

struct Vec3i {
    int x, y, z;
};

struct Tail {
    char b[0x3c];
};

struct M18real {
    int a, b;
    Vec3i i8, i14;
    V3 arr[3];
    Tail tail;
};

// Force emission of the compiler-generated M18real copy ctor (target 0046a7c0).
M18real M18_force_copy(const M18real& o)
{
    M18real t(o);
    return t;
}

// Opaque 0x80-byte member used by S630 (keeps its copy call out-of-line).
struct M18 {
    char pad[0x80];
    M18(const M18&);
};

struct B750 {
    virtual void bv();
    char pad[0x14];
    B750(const B750&);
};

struct T50 {
    char pad[0x14];
    T50(const T50&);
};

struct T31 {
    char pad[0x14];
    T31(const T31&);
};

struct T31b {
    char pad[0x14];
    T31b(const T31b&);
};

struct M98 {
    char pad[0x14];
    M98(const M98&);
};

struct S630 : B750 {
    virtual void v();
    M18 m18;
    M98 m98;
    T50 mAc;
    T31 mC0;
    T50 mD4;
    T50 mE8;
    T50 mFc;
    int f110;
    T31b m114;
    S630(const S630&);
};

// @ 0x0046a630
S630::S630(const S630& o)
    : B750(o), m18(o.m18), m98(o.m98), mAc(o.mAc), mC0(o.mC0), mD4(o.mD4), mE8(o.mE8),
      mFc(o.mFc), f110(o.f110), m114(o.m114)
{
    ScratchSlots<4>();
}

// ---- not yet reproduced -----------------------------------------------------

// @ 0x00469bb0
void F_00469bb0() {}

// @ 0x0046a510
void F_0046a510() {}

// @ 0x0046a750
void F_0046a750() {}

// @ 0x0046a7c0
void F_0046a7c0() {}

// @ 0x0046a8a0
void F_0046a8a0() {}
