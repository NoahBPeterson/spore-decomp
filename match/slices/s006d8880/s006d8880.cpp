// Slice s006d8880: bake evaluators (core 6c4200, acos-len tail) plus two
// container helpers used by the bake pipeline (RB-tree lookup/insert, vector insert).
#include "../s006ccf50/s006ccf50.h"

// uv4u16 / colour4u8 / core FUN_006c4200 / acos weight (axis.y * len)
DEFINE_BAKE(Bake_6d8880, 0, 4, 1, 0, 2)   // @ 0x006d8880
// uv4u8  / colour4f  / core FUN_006c4200 / acos weight (axis.y * len)
DEFINE_BAKE(Bake_6d8c00, 0, 4, 0, 1, 2)   // @ 0x006d8c00
// uv2u16 / colour4f  / core FUN_006c4200 / acos weight (axis.y * len)
DEFINE_BAKE(Bake_6d8f60, 0, 2, 1, 1, 2)   // @ 0x006d8f60
// uv4u16 / colour4f  / core FUN_006c4200 / acos weight (axis.y * len)
DEFINE_BAKE(Bake_6d9280, 0, 4, 1, 1, 2)   // @ 0x006d9280

// ---------------------------------------------------------------------------
// 0x006d95e0: eastl::rbtree lookup, inserting the key when absent.
// Node: left(+0) right(+4) parent(+8) colour(+c) key(+10) value(+14).
// Tree: anchor node embedded at +4 (anchor.parent == root at +c).
struct RBNode
{
    RBNode* mpLeft;     // +0
    RBNode* mpRight;    // +4
    RBNode* mpParent;   // +8
    uint32_t mColour;   // +c
    int mKey;           // +10   value follows at +14
};

struct RBTree
{
    uint32_t mPad;      // +0
    RBNode anchor;      // +4
    void* FindOrInsert(const int* pKey);   // 0x006d95e0
};

// tree insert helper (real name unknown; 0x006c4b50)
void __cdecl FUN_006c4b50(void* self, void** out, RBNode* lower, const void* value, int flag);

void* RBTree::FindOrInsert(const int* pKey)   // @ 0x006d95e0
{
    RBNode* endNode = &this->anchor;
    RBNode* lower = endNode;
    RBNode* node = this->anchor.mpParent;    // root
    if (node != 0)
    {
        do
        {
            if (node->mKey < *pKey)
                node = node->mpLeft;
            else
            {
                lower = node;
                node = node->mpRight;
            }
        } while (node != 0);
    }
    if (lower != endNode && lower->mKey <= *pKey)
        return (char*)lower + 0x14;

    int pair[2];
    pair[0] = *pKey;
    pair[1] = 0;
    void* result = 0;
    FUN_006c4b50(this, &result, lower, pair, 0);
    return (char*)result + 0x14;
}

// ---------------------------------------------------------------------------
// 0x006d9660: eastl vector<T> insert (element stride 0x10, T owned via Handle).
struct VecElem
{
    void Destroy(void* elem);   // out-of-line helper 0x006c2ad0
    void Assign(const void* src);   // Handle::Assign 0x00424f70
    void Shift(void* first, void* last);   // 0x006df340
};
void* __cdecl FUN_006c2b10(void* first, void* last, void* dst);
void __cdecl FUN_0047d3f0(void* first, void* last, void* dst);
void __cdecl eastl_allocator_deallocate(void* p);
void* __cdecl eastl_allocator_allocate(uint32_t size, const char* tag, int a, int b,
                                       const char* file, int line);

void FUN_006d9660(uint32_t* self, uint32_t position, uint32_t value)   // @ 0x006d9660
{
    uint32_t end = self[1];
    if (end != self[2])
    {
        if (position <= value && value < end)
            value += 0x10;
        if (end != 0)
            ((VecElem*)(uint32_t)end)->Destroy((void*)(end - 0x10));
        ((VecElem*)(uint32_t)position)->Shift((void*)(self[1] - 0x10), (void*)self[1]);
        ((VecElem*)(uint32_t)position)->Assign((const void*)value);
        self[1] = self[1] + 0x10;
        return;
    }

    int count = (int)(end - self[0]) >> 4;
    void* newBlock;
    if (count == 0)
    {
        count = 1;
    }
    else
    {
        count *= 2;
    }
    if (count == 0)
        newBlock = 0;
    else
        newBlock = eastl_allocator_allocate(count << 4, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);

    uint32_t begin = self[0];
    void* mid = FUN_006c2b10((void*)begin, (void*)position, newBlock);
    FUN_0047d3f0((void*)begin, (void*)position, newBlock);
    if (mid != 0)
        ((VecElem*)mid)->Destroy((void*)value);

    uint32_t oldEnd = self[1];
    void* newEnd = FUN_006c2b10((void*)position, (void*)oldEnd, (char*)mid + 0x10);
    FUN_0047d3f0((void*)position, (void*)oldEnd, (char*)mid + 0x10);

    uint32_t begin2 = self[0];
    if (begin2 != 0 && begin2 != self[4])
        eastl_allocator_deallocate((void*)begin2);
    self[0] = (uint32_t)newBlock;
    self[1] = (uint32_t)newEnd;
    self[2] = (uint32_t)newBlock + (count << 4);
}
