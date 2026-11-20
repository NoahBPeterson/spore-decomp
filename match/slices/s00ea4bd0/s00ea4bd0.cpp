// Slice s00ea4bd0: destructor of an object with two empty polymorphic bases: shuts itself
// down, then its members go: a buffer block, a member object, five ref-counted pointers (one
// of them an interface whose Release is the third slot) and two vectors.

struct IRefObj_s00ea_4bd0 {
    virtual int AddRef();
    virtual int Release();
};

struct RefPtr_s00ea_4bd0 {
    IRefObj_s00ea_4bd0* mp;

    ~RefPtr_s00ea_4bd0() { if (mp) mp->Release(); }
};

struct IUnknownLike_s00ea_4bd0 {
    virtual int QueryInterface();
    virtual int AddRef();
    virtual int Release();  // slot 0x08
};

struct ComPtr_s00ea_4bd0 {
    IUnknownLike_s00ea_4bd0* mp;

    ~ComPtr_s00ea_4bd0() { if (mp) mp->Release(); }
};

struct Vector_s00ea_4bd0 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    int mAllocator;

    ~Vector_s00ea_4bd0()
    {
        if (mpBegin)
            operator delete(mpBegin);
    }
};

void FreeBlock_s00ea_4bd0(void* p, int a, int b, int c, int d);  // 0x00571db0

struct Block_s00ea_4bd0 {
    void* mpData;
    int mA, mB, mC, mD;

    ~Block_s00ea_4bd0()
    {
        if (mpData) {
            void* p = mpData;
            mpData = 0;
            FreeBlock_s00ea_4bd0(p, mA, mB, mC, mD);
        }
    }
};

struct Membere0_s00ea_4bd0 {
    char pad00[0xf8 - 0xe0];
    ~Membere0_s00ea_4bd0();  // 0x00ea0e60
};

struct BaseA_s00ea_4bd0 {
    virtual ~BaseA_s00ea_4bd0() {}
};

struct BaseB_s00ea_4bd0 {
    virtual ~BaseB_s00ea_4bd0() {}
};

struct Object_s00ea_4bd0 : BaseA_s00ea_4bd0, BaseB_s00ea_4bd0 {
    char pad08[0x3c - 8];
    Vector_s00ea_4bd0 mVec3c;          // +0x3c
    char pad4c[4];
    Vector_s00ea_4bd0 mVec50;          // +0x50
    char pad60[0xcc - 0x60];
    RefPtr_s00ea_4bd0 mpRefcc;         // +0xcc
    RefPtr_s00ea_4bd0 mpRefd0;         // +0xd0
    RefPtr_s00ea_4bd0 mpRefd4;         // +0xd4
    ComPtr_s00ea_4bd0 mpComd8;         // +0xd8
    RefPtr_s00ea_4bd0 mpRefdc;         // +0xdc
    Membere0_s00ea_4bd0 me0;           // +0xe0
    Block_s00ea_4bd0 mBlock;           // +0xf8

    void Shutdown();  // 0x00ea4b40
    virtual ~Object_s00ea_4bd0();
};

// @ 0x00ea4bd0
Object_s00ea_4bd0::~Object_s00ea_4bd0()
{
    Shutdown();
}
