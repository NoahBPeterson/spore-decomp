// Slice s00c6a270: constructor of the game object whose type-id cast is 0x00c69a00 and whose
// destructor is 0x00c6a430 (bases at +0x00 (two vtables), +0x34, +0x108 and +0x120).

struct IRefObj_s00c6_a270 {
    virtual int AddRef();
    virtual int Release();
};

struct RefPtr_s00c6_a270 {
    IRefObj_s00c6_a270* mp;

    RefPtr_s00c6_a270() : mp(0) {}
};

struct Member1f8_s00c6_a270 {
    char pad00[0x20];
    Member1f8_s00c6_a270();  // 0x00b63890
};

struct Base00a_s00c6_a270 { virtual void v00(); };
struct Base00b_s00c6_a270 { virtual void v00(); };

struct Base00_s00c6_a270 : Base00a_s00c6_a270, Base00b_s00c6_a270 {
    char pad08[0x34 - 8];
    Base00_s00c6_a270();  // 0x00b18660
};

struct ResourceKey_s00c6_a270 {
    unsigned int mInstanceID;
    unsigned int mTypeID;
    unsigned int mGroupID;

    ResourceKey_s00c6_a270(unsigned int instance, unsigned int type, unsigned int group)
        : mInstanceID(instance), mTypeID(type), mGroupID(group) {}
};

struct Base34_s00c6_a270 {
    virtual void v00();
    char pad38[0x88 - 0x38];
    int m88;               // +0x88
    char pad8c[0xa5 - 0x8c];
    bool ma5;              // +0xa5
    char pada6[0xc4 - 0xa6];
    ResourceKey_s00c6_a270 mKey;  // +0xc4
    char padd0[0x108 - 0xd0];
    Base34_s00c6_a270();  // 0x00c89630 (leaves mKey to the derived class)
};

struct Base108_s00c6_a270 {
    virtual void v00();
    char pad04[0x120 - 0x10c];
    Base108_s00c6_a270();  // 0x00ac03d0
};

struct Base120_s00c6_a270 {
    virtual void v00();
    char pad04[0x1e8 - 0x124];
    Base120_s00c6_a270();  // 0x00bfd4e0
};

struct Object_s00c6_a270 : Base00_s00c6_a270, Base34_s00c6_a270, Base108_s00c6_a270, Base120_s00c6_a270 {
    int m1e8;                       // +0x1e8
    bool m1ec;                      // +0x1ec
    int m1f0;                       // +0x1f0
    RefPtr_s00c6_a270 mpRef1f4;     // +0x1f4
    Member1f8_s00c6_a270 m1f8;      // +0x1f8
    RefPtr_s00c6_a270 mpRef218;     // +0x218
    RefPtr_s00c6_a270 mpRef21c;     // +0x21c
    float m220;                     // +0x220

    virtual void v00();
    Object_s00c6_a270();
};

// @ 0x00c6a270
Object_s00c6_a270::Object_s00c6_a270()
    : m1e8(0), m1ec(true), m1f0(10000), m220(1.0f)
{
    m88 = 5;
    mKey = ResourceKey_s00c6_a270(0xa76cd528, 0, 0);
    ma5 = false;
}
