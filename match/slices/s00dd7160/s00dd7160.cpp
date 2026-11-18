// Slice s00dd7160: destructor of a manager that keeps its entries in a map (EASTL rbtree layout
// with a non-empty compare): removes every entry, deletes its owned object, runs the module
// cleanup and releases its ref-counted helper before the members and bases go.

void ModuleCleanup_s00dd_7160();  // 0x00dd5950

struct IRefObj_s00dd_7160 {
    virtual int AddRef();
    virtual int Release();
};

struct Owned_s00dd_7160 {
    virtual ~Owned_s00dd_7160();
};

struct MapNode_s00dd_7160 {
    MapNode_s00dd_7160* mpNodeRight;   // +0x00
    MapNode_s00dd_7160* mpNodeLeft;    // +0x04
    MapNode_s00dd_7160* mpNodeParent;  // +0x08
    char mColor;                       // +0x0c
    int mKey;                          // +0x10
};

struct Map_s00dd_7160 {
    int mCompare;                      // +0x00
    MapNode_s00dd_7160* mpNodeRight;   // +0x04 (anchor)
    MapNode_s00dd_7160* mpNodeLeft;    // +0x08
    MapNode_s00dd_7160* mpNodeParent;  // +0x0c
    int mColor;                        // +0x10
    int mnSize;                        // +0x14
    int mAllocator;                    // +0x18

    ~Map_s00dd_7160() { DoNukeSubtree(mpNodeParent); }
    void DoNukeSubtree(MapNode_s00dd_7160* node);  // 0x00d0c930
};

struct BaseA_s00dd_7160 {
    virtual ~BaseA_s00dd_7160() {}
};

struct BaseB1_s00dd_7160 {
    virtual void v00();
};

struct BaseB2_s00dd_7160 {
    virtual void v00();
};

struct BaseB_s00dd_7160 : BaseB1_s00dd_7160, BaseB2_s00dd_7160 {
    char pad0c[0x28 - 0xc];
    ~BaseB_s00dd_7160();  // 0x00b5b9a0
};

struct Manager_s00dd_7160 : BaseA_s00dd_7160, BaseB_s00dd_7160 {
    Map_s00dd_7160 mEntries;              // +0x28
    char pad44[0x68 - 0x44];
    Owned_s00dd_7160* mpOwned;            // +0x68
    IRefObj_s00dd_7160* mpHelper;         // +0x6c

    virtual ~Manager_s00dd_7160();
    virtual void v00();
    void Remove(int key);  // 0x00dd6bc0
};

// @ 0x00dd7160
Manager_s00dd_7160::~Manager_s00dd_7160()
{
    while (mEntries.mnSize)
        Remove(mEntries.mpNodeLeft->mKey);
    delete mpOwned;
    mpOwned = 0;
    ModuleCleanup_s00dd_7160();
    if (mpHelper)
        mpHelper->Release();
}
