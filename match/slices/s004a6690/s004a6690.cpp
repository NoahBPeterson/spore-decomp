// Slice s004a6690: SP editor block-validity / collision-group helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// 0x4a6690 (cdecl): re-assigns the physics collision group of the blocks around `block`.
// Every block of the model gets group `grpAll`; the blocks of `list` (plus, while symmetry is on,
// their symmetric partners, `block`'s partner and the symmetric pile of the partner) get
// `grpSel`; so do the symmetric pile of `block` itself and every other block that is not
// excluded by the flag/skin checks; at the end the physics world's floor filter is set to
// `grpAll` (floorAll) or `grpSel` and its collision filters are refreshed.
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct AllocTag { AllocTag() {} };

template <unsigned N>
struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(unsigned i) const
    {
        if (i < N) {
            const uint32_t word = mWord[i / 32];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};

// EA::RefCountTemplate<int>: Release contains `delete this`, so it stays out of line.
struct RefCountTemplate {
    virtual ~RefCountTemplate();
    int mRefCount;
    int AddRef() { return mRefCount++ + 1; }
    int Release();                                                  // 0x00453540
};

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

struct cSPEditorBlock;
typedef AutoRefCount<cSPEditorBlock> BlockRef;

// eastl::vector<AutoRefCount<cSPEditorBlock>, sp_vector_allocator>
struct BlockVector {
    BlockRef* mpBegin;
    BlockRef* mpEnd;
    BlockRef* mpCapacity;
    uint32_t  mAllocator[2];
    BlockVector(const AllocTag& a = AllocTag());                    // 0x00540470
    ~BlockVector();                                                 // 0x00453eb0
    int size() const { return (int)(mpEnd - mpBegin); }
    BlockRef& operator[](int i) { return mpBegin[i]; }
};

// eastl::fixed_vector<AutoRefCount<cSPEditorBlock>, 8>
struct FixedBlockVector : BlockVector {
    uint32_t mOverflow;
    void*    mBuffer[8];
    FixedBlockVector() { FixedInit(); }
    void FixedInit();                                               // 0x00453770
};

// The same container with the vector destructor expanded inline (the destroy loop and the free
// stay out of line).
struct FixedBlockVectorInl {
    BlockRef* mpBegin;
    BlockRef* mpEnd;
    BlockRef* mpCapacity;
    uint32_t  mAllocator[2];
    uint32_t  mOverflow;
    void*     mBuffer[8];
    void Construct(const AllocTag& a);                              // 0x00540470
    void FixedInit();                                               // 0x00453770
    void DestructRange(BlockRef* first, BlockRef* last);            // 0x00454e90
    void Free();                                                    // 0x00425990
    int size() const { return (int)(mpEnd - mpBegin); }
    BlockRef& operator[](int i) { return mpBegin[i]; }
    FixedBlockVectorInl() { Construct(AllocTag()); FixedInit(); }
    ~FixedBlockVectorInl() { DestructRange(mpBegin, mpEnd); Free(); }
};

struct cSPEditorModelBase {
    virtual ~cSPEditorModelBase();
};
struct cSPEditorPhysicsWorld {
    void SetFloorFilter(int group);                                 // 0x004b9440
    void UpdateCollisionFilters();                                  // 0x004b9420
};

struct cSPEditorBlock {
    virtual void _v0();
    uint32_t pad04[(0x28 - 0x04) / 4];
    struct cSPEditorModel* mpModel;                                 // +0x028
    uint32_t pad2c[(0x3e0 - 0x2c) / 4];
    BlockRef mSymmetricBlock;                                       // +0x3e0
    uint32_t pad3e4[(0xdc8 - 0x3e4) / 4];
    bitset<60> mFlags;                                              // +0xdc8

    cSPEditorModel* GetEditorModel() { return mpModel; }
    cSPEditorBlock* GetSymmetricBlock() { return mSymmetricBlock; }
    bool FUN_43fc20(int a, int b);               // @ 0x43fc20
    void SetValid(bool v);                       // @ 0x43f6b0
    void SetCollisionGroup(int group);                              // 0x00451e50
    bool IsFlagSet(unsigned i) { return mFlags.test(i); }
    bool HasRelevantPoints2(cSPEditorBlock* other);                 // 0x00438420
    int GetSkinIdentifierForPicking();                              // 0x0043a870
};
struct cSPEditorModel : cSPEditorModelBase, RefCountTemplate {      // RefCountTemplate at +4
    cSPEditorBlock* GetBlock(int i);                                // @ 0x4accb0
    int GetBlockCount();                                            // @ 0x4accf0
    bool FUN_4adc40();                                              // @ 0x4adc40
    void FUN_4adc20(int v);                                         // @ 0x4adc20
    cSPEditorPhysicsWorld* GetPhysicsWorld();                       // 0x004ad450
};

bool GetSymmetricPile(cSPEditorBlock* block, BlockVector* list, bool b);   // 0x0049dd20

// @ 0x4a6ca0
void FUN_4a6ca0(cSPEditorModel* model, int value)
{
    bool saved = model->FUN_4adc40();
    model->FUN_4adc20(0);
    int t14 = 0;
    int tmp = model->GetBlockCount();
    for (; t14 < tmp; t14++) {
        cSPEditorBlock* block = model->GetBlock(t14);
        block->SetValid(block->FUN_43fc20(0, value));
    }
    model->FUN_4adc20(saved);
}

// @ 0x4a6690 (cdecl)
// Local names were chosen so that cl's /Od name-hash slot order reproduces the original frame.
void AssignCollisionGroups(cSPEditorBlock* block, BlockVector* list, int grpAll, int grpSel, bool floorAll)
{
    AutoRefCount<cSPEditorModel> model(block->GetEditorModel());
    if (model) {
        bool symmetry = model->FUN_4adc40();
        for (int i = 0, size = model->GetBlockCount(); i < size; i++) {
            cSPEditorBlock* b = model->GetBlock(i);
            b->SetCollisionGroup(grpAll);
        }
        int nBlocks = list->size();
        for (int j = 0; j < nBlocks; j++) {
            (*list)[j]->SetCollisionGroup(grpSel);
            if (symmetry && (*list)[j]->GetSymmetricBlock())
                (*list)[j]->GetSymmetricBlock()->SetCollisionGroup(grpSel);
        }
        block->SetCollisionGroup(grpAll);
        if (symmetry && block->GetSymmetricBlock()) {
            block->GetSymmetricBlock()->SetCollisionGroup(grpSel);
            FixedBlockVectorInl mirror;
            GetSymmetricPile(block->GetSymmetricBlock(), (BlockVector*)&mirror, true);
            for (int k = 0, n = mirror.size(); k < n; k++) {
                cSPEditorBlock* item = mirror[k];
                item->SetCollisionGroup(grpSel);
            }
        }
        FixedBlockVector ownPile;
        GetSymmetricPile(block, &ownPile, true);
        for (int k = 0, n = ownPile.size(); k < n; k++)
            ownPile[k]->SetCollisionGroup(grpSel);
        for (int i = 0, size = model->GetBlockCount(); i < size; i++) {
            cSPEditorBlock* other = model->GetBlock(i);
            if (block != other && !block->HasRelevantPoints2(other)) {
                bool isFlag7;
                isFlag7 = other->IsFlagSet(7);
                bool onlyPin = !isFlag7 && other->mFlags.test(11);
                int skinId = block->GetSkinIdentifierForPicking();
                bool skin01 = (skinId == 1 || skinId == 0);
                bool isSkin = skinId == 1;
                if (skin01 && isFlag7) {
                } else if (onlyPin && isSkin) {
                } else {
                    other->SetCollisionGroup(grpSel);
                }
            }
        }
        if (floorAll)
            model->GetPhysicsWorld()->SetFloorFilter(grpAll);
        else
            model->GetPhysicsWorld()->SetFloorFilter(grpSel);
        model->GetPhysicsWorld()->UpdateCollisionFilters();
        ScratchSlots<8>();
    }
}

// @ 0x4a6d20
void FUN_4a6d20(cSPEditorBlock* block) { (void)block; }
