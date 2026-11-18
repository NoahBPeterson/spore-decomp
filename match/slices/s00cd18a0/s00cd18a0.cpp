// Slice s00cd18a0: destructor of an object built on a base that owns two maps (EASTL rbtree
// layout with a non-empty compare) and an empty polymorphic base; it releases three ref-counted
// pointers, destroys two more maps, releases a handle and frees a buffer block.

struct IRefObj_s00cd_18a0 {
    virtual int AddRef();
    virtual int Release();
};

struct RefPtr_s00cd_18a0 {
    IRefObj_s00cd_18a0* mp;

    ~RefPtr_s00cd_18a0() { if (mp) mp->Release(); }
};

struct IHandle_s00cd_18a0 {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void Release();  // slot 0x0c
};

struct HandlePtr_s00cd_18a0 {
    IHandle_s00cd_18a0* mp;

    ~HandlePtr_s00cd_18a0() { if (mp) mp->Release(); }
};

struct MapNode_s00cd_18a0;

struct MapA_s00cd_18a0 {
    int mCompare;
    MapNode_s00cd_18a0* mpNodeRight;
    MapNode_s00cd_18a0* mpNodeLeft;
    MapNode_s00cd_18a0* mpNodeParent;
    int mColor;
    int mnSize;
    int mAllocator;

    ~MapA_s00cd_18a0() { DoNukeSubtree(mpNodeParent); }
    void DoNukeSubtree(MapNode_s00cd_18a0* node);  // 0x00b1b830
};

struct MapB_s00cd_18a0 {
    int mCompare;
    MapNode_s00cd_18a0* mpNodeRight;
    MapNode_s00cd_18a0* mpNodeLeft;
    MapNode_s00cd_18a0* mpNodeParent;
    int mColor;
    int mnSize;
    int mAllocator;

    ~MapB_s00cd_18a0() { DoNukeSubtree(mpNodeParent); }
    void DoNukeSubtree(MapNode_s00cd_18a0* node);  // 0x00e4b990
};

void FreeBlock_s00cd_18a0(void* p, int a, int b, int c, int d);  // 0x00571db0

struct Block_s00cd_18a0 {
    void* mpData;  // +0x00
    int mA, mB, mC, mD;

    ~Block_s00cd_18a0()
    {
        if (mpData) {
            void* p = mpData;
            mpData = 0;
            FreeBlock_s00cd_18a0(p, mA, mB, mC, mD);
        }
    }
};

struct MapPair_s00cd_18a0 {
    MapA_s00cd_18a0 mFirst;   // +0x00
    MapB_s00cd_18a0 mSecond;  // +0x1c
};

struct BaseA_s00cd_18a0 {
    MapPair_s00cd_18a0 mMaps;  // +0x04

    virtual ~BaseA_s00cd_18a0() {}
};

struct BaseB_s00cd_18a0 {
    virtual ~BaseB_s00cd_18a0() {}
};

struct Object_s00cd_18a0 : BaseA_s00cd_18a0, BaseB_s00cd_18a0 {
    char pad40[4];
    Block_s00cd_18a0 mBlock;           // +0x44
    char pad58[4];
    HandlePtr_s00cd_18a0 mpHandle;     // +0x5c
    MapPair_s00cd_18a0 mMaps2;         // +0x60
    RefPtr_s00cd_18a0 mpRef98;         // +0x98
    RefPtr_s00cd_18a0 mpRef9c;         // +0x9c
    char pada0[0xc0 - 0xa0];
    RefPtr_s00cd_18a0 mpRefc0;         // +0xc0

    virtual ~Object_s00cd_18a0();
};

// @ 0x00cd18a0
Object_s00cd_18a0::~Object_s00cd_18a0()
{
}
