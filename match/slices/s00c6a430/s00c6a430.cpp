// Slice s00c6a430: destructor of the game object whose type-id cast is 0x00c69a00 (bases at
// +0x00 (two vtables), +0x34, +0x108 and +0x120): releases three ref-counted members and
// destroys one more member before the bases go.

struct IRefObj_s00c6_a430 {
    virtual int AddRef();
    virtual int Release();
};

struct RefPtr_s00c6_a430 {
    IRefObj_s00c6_a430* mp;

    ~RefPtr_s00c6_a430() { if (mp) mp->Release(); }
};

struct Member1f8_s00c6_a430 {
    char pad00[0x20];
    ~Member1f8_s00c6_a430();  // 0x00b638b0
};

struct Base00a_s00c6_a430 { virtual void v00(); };
struct Base00b_s00c6_a430 { virtual void v00(); };

struct Base00_s00c6_a430 : Base00a_s00c6_a430, Base00b_s00c6_a430 {
    char pad08[0x34 - 8];
    ~Base00_s00c6_a430();  // 0x00b184c0
};

struct Base34_s00c6_a430 {
    virtual void v00();
    char pad04[0x108 - 0x38];
    ~Base34_s00c6_a430();  // 0x00c8a420
};

struct Base108_s00c6_a430 {
    virtual void v00();
    char pad04[0x120 - 0x10c];
    ~Base108_s00c6_a430();  // 0x00ac0520
};

struct Base120_s00c6_a430 {
    virtual void v00();
    char pad04[0x1f4 - 0x124];
    ~Base120_s00c6_a430();  // 0x00bfcd00
};

struct Object_s00c6_a430 : Base00_s00c6_a430, Base34_s00c6_a430, Base108_s00c6_a430, Base120_s00c6_a430 {
    RefPtr_s00c6_a430 mpRef1f4;     // +0x1f4
    Member1f8_s00c6_a430 m1f8;      // +0x1f8
    RefPtr_s00c6_a430 mpRef218;     // +0x218
    RefPtr_s00c6_a430 mpRef21c;     // +0x21c

    virtual void v00();
    ~Object_s00c6_a430();
};

// @ 0x00c6a430
Object_s00c6_a430::~Object_s00c6_a430()
{
}
