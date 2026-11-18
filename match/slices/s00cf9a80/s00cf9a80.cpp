// Slice s00cf9a80: destructor of a singleton manager (bases at +0x00, +0x04 (two vtables),
// +0x20 and +0x24): clears the global instance pointer, then its members go: a member object,
// four interface pointers released three different ways, a ref-counted resource handle and
// three vectors (EASTL vector layout with the counted-block allocator).

struct IRefObj_s00cf_9a80 {
    virtual int AddRef();
    virtual int Release();
};

struct RefPtr_s00cf_9a80 {
    IRefObj_s00cf_9a80* mp;

    ~RefPtr_s00cf_9a80() { if (mp) mp->Release(); }
};

struct IUnknownLike_s00cf_9a80 {
    virtual int QueryInterface();
    virtual int AddRef();
    virtual int Release();  // slot 0x08
};

struct ComPtr_s00cf_9a80 {
    IUnknownLike_s00cf_9a80* mp;

    ~ComPtr_s00cf_9a80() { if (mp) mp->Release(); }
};

struct IService_s00cf_9a80;
typedef void (__thiscall* ServiceShutdownFn_s00cf_9a80)(IService_s00cf_9a80*);

struct IService_s00cf_9a80 {
    void** mpVtbl;
};

struct ServicePtr_s00cf_9a80 {
    IService_s00cf_9a80* mp;

    // released through vtable slot 0xc0
    ~ServicePtr_s00cf_9a80() { if (mp) ((ServiceShutdownFn_s00cf_9a80)mp->mpVtbl[0xc0 / 4])(mp); }
};

struct Resource_s00cf_9a80;
struct ResourceOwner_s00cf_9a80;
typedef void (__thiscall* DestroyResourceFn_s00cf_9a80)(ResourceOwner_s00cf_9a80*, Resource_s00cf_9a80*, bool);

struct ResourceOwner_s00cf_9a80 {
    void** mpVtbl;
};

struct Resource_s00cf_9a80 {
    ResourceOwner_s00cf_9a80* mpOwner;  // +0x00
    unsigned int mFlags : 31;           // +0x04
    unsigned int mbExternal : 1;
    char pad08[0x40 - 8];
    int mRefCount;                      // +0x40
};

struct ResourcePtr_s00cf_9a80 {
    Resource_s00cf_9a80* mp;

    ~ResourcePtr_s00cf_9a80()
    {
        if (mp) {
            int count = mp->mRefCount;
            if (count > 1)
                mp->mRefCount = count - 1;
            else
                ((DestroyResourceFn_s00cf_9a80)mp->mpOwner->mpVtbl[0x170 / 4])(mp->mpOwner, mp, mp->mbExternal != 0);
        }
    }
};

struct Vector_s00cf_9a80 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    int mAllocator[2];

    ~Vector_s00cf_9a80()
    {
        if (mpBegin && ((int*)mpBegin)[-1])
            operator delete(mpBegin);
    }
};

struct Member128_s00cf_9a80 {
    char pad00[0x20];
    ~Member128_s00cf_9a80();  // 0x00b638b0
};

struct BaseA_s00cf_9a80 {
    virtual ~BaseA_s00cf_9a80() {}
};

struct BaseB1_s00cf_9a80 { virtual void v00(); };
struct BaseB2_s00cf_9a80 { virtual void v00(); };

struct BaseB_s00cf_9a80 : BaseB1_s00cf_9a80, BaseB2_s00cf_9a80 {
    char pad0c[0x20 - 0xc];
    ~BaseB_s00cf_9a80();  // 0x00b5b9a0
};

struct BaseC_s00cf_9a80 {
    virtual ~BaseC_s00cf_9a80() {}
};

struct BaseD_s00cf_9a80 {
    virtual ~BaseD_s00cf_9a80() {}
};

struct Manager_s00cf_9a80;
extern Manager_s00cf_9a80* g_pManager_s00cf_9a80;  // 0x0169d2c8

struct Manager_s00cf_9a80 : BaseA_s00cf_9a80, BaseB_s00cf_9a80, BaseC_s00cf_9a80, BaseD_s00cf_9a80 {
    char pad28[4];
    Vector_s00cf_9a80 mVec2c;                  // +0x02c
    Vector_s00cf_9a80 mVec40;                  // +0x040
    Vector_s00cf_9a80 mVec54;                  // +0x054
    char pad68[0xf4 - 0x68];
    ServicePtr_s00cf_9a80 mpServicef4;         // +0x0f4
    char padf8[0x100 - 0xf8];
    ComPtr_s00cf_9a80 mpCom100;                // +0x100
    ResourcePtr_s00cf_9a80 mpResource104;      // +0x104
    ComPtr_s00cf_9a80 mpCom108;                // +0x108
    RefPtr_s00cf_9a80 mpRef10c;                // +0x10c
    char pad110[0x128 - 0x110];
    Member128_s00cf_9a80 m128;                 // +0x128

    virtual ~Manager_s00cf_9a80();
    virtual void v00();
};

// @ 0x00cf9a80
Manager_s00cf_9a80::~Manager_s00cf_9a80()
{
    g_pManager_s00cf_9a80 = 0;
}
