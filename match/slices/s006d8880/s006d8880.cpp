// Slice s006d8880: bake evaluators (core 6c4200, acos-len tail) plus two
// container helpers used by the bake pipeline (RB-tree lookup/insert, vector insert).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "../s006ccf50/s006ccf50.h"

// The four evaluators share one body shape, written out per VA (the DEFINE_BAKE template in
// ../s006ccf50/s006ccf50.h is instantiated by many sibling slices, so it stays untouched):
//   - the uv channels are fetched by pointer (u16/u8) and kept as uint32_t elements,
//   - the colour is built as floats in xmm,
//   - the acos tail computes the weight from |res.xy - axis.zw| and scales by a double constant.
//
// uv4u16 / colour4u8 / core FUN_006c4200 / acos weight (axis.y * len)
#define BAKE_PROLOG()                                                                                 \
    Elem32* base = table->mBegin;                                                                     \
    Handle hA = base[index].handle;                                                                   \
    Handle hB;                                                                                        \
    if (handleIndex >= 0)                                                                             \
        hB.Assign(&base[handleIndex].handle);                                                         \
    if (count == 0)                                                                                   \
        return true;                                                                                  \
    {                                                                                                 \
        float axisDir[3] = { 1.0f, 0.0f, 0.0f };                                                      \
        float white[4] = { 1.0f, 0.0f, 0.0f, 0.0f };                                                  \
        float* o = out;                                                                               \
        BakeEntry* e = entries;                                                                       \
        int n = count;                                                                                \
        do                                                                                            \
        {                                                                                             \
            float color[4];                                                                           \
            float p3[3];                                                                              \
            float res[3];                                                                             \
            float scratch[3];                                                                         \
            (void)white;                                                                              \
            (void)color; (void)p3; (void)res; (void)scratch;

#define BAKE_EPILOG()                                                                                 \
            o += 2;                                                                                   \
            e += 1;                                                                                   \
        } while (--n);                                                                                \
    }                                                                                                 \
    return true;

#define BAKE_TAIL_ACOS()                                                                              \
            float scale = scaleInfo->scale;                                                           \
            float dx = res[0] - axis[2];                                                              \
            float dy = res[1] - axis[3];                                                              \
            float sq = dx * dx + dy * dy;                                                             \
            float len = (float)sqrt((double)sq);                                                      \
            float angle = (float)acos((double)(dx / len));                                            \
            o[0] = ((axis[0] * angle) * 1.2732406f) * scale;                                          \
            o[1] = (1.0f - axis[1] * len) * scale;

// @ 0x006d8880
bool Bake_6d8880(float* out, int count, ElemTable* table, BakeEntry* entries, StreamDesc* pos,
                 float* axis, ScaleInfo* scaleInfo, int index, int handleIndex, int param10)
{
    BAKE_PROLOG()
    uint16_t* s = (uint16_t*)(hA.b + hA.d * e->fc);
    uint32_t uv[4];
    uv[0] = s[0] / 3; uv[1] = s[1] / 3; uv[2] = s[2] / 3; uv[3] = s[3] / 3;
    (void)uv;
    {
        uint8_t* c = (uint8_t*)(hB.b + hB.d * e->f8);
        color[0] = (float)c[0] * (1.0f / 255.0f); color[1] = (float)c[1] * (1.0f / 255.0f);
        color[2] = (float)c[2] * (1.0f / 255.0f); color[3] = (float)c[3] * (1.0f / 255.0f);
    }
    float* ps = (float*)(pos->base + pos->stride * e->f0);
    p3[0] = ps[0]; p3[1] = ps[1]; p3[2] = ps[2];
    FUN_006c4200(res, scratch, p3, axisDir, color, uv, param10);
    BAKE_TAIL_ACOS()
    BAKE_EPILOG()
}

// uv4u8  / colour4f  / core FUN_006c4200 / acos weight (axis.y * len)
// @ 0x006d8c00
bool Bake_6d8c00(float* out, int count, ElemTable* table, BakeEntry* entries, StreamDesc* pos,
                 float* axis, ScaleInfo* scaleInfo, int index, int handleIndex, int param10)
{
    BAKE_PROLOG()
    uint8_t* s = (uint8_t*)(hA.b + hA.d * e->fc);
    uint32_t uv[4];
    uv[0] = s[0] / 3; uv[1] = s[1] / 3; uv[2] = s[2] / 3; uv[3] = s[3] / 3;
    (void)uv;
    {
        float* c = (float*)(hB.b + hB.d * e->f8);
        color[0] = c[0]; color[1] = c[1]; color[2] = c[2]; color[3] = c[3];
    }
    float* ps = (float*)(pos->base + pos->stride * e->f0);
    p3[0] = ps[0]; p3[1] = ps[1]; p3[2] = ps[2];
    FUN_006c4200(res, scratch, p3, axisDir, color, uv, param10);
    BAKE_TAIL_ACOS()
    BAKE_EPILOG()
}

// uv2u16 / colour4f  / core FUN_006c4200 / acos weight (axis.y * len)
// @ 0x006d8f60
bool Bake_6d8f60(float* out, int count, ElemTable* table, BakeEntry* entries, StreamDesc* pos,
                 float* axis, ScaleInfo* scaleInfo, int index, int handleIndex, int param10)
{
    BAKE_PROLOG()
    uint16_t* s = (uint16_t*)(hA.b + hA.d * e->fc);
    uint32_t uv[4];
    uv[0] = s[0] / 3; uv[1] = s[1] / 3;
    uv[2] = 0; uv[3] = 0;
    (void)uv;
    {
        float* c = (float*)(hB.b + hB.d * e->f8);
        color[0] = c[0]; color[1] = c[1]; color[2] = c[2]; color[3] = c[3];
    }
    float* ps = (float*)(pos->base + pos->stride * e->f0);
    p3[0] = ps[0]; p3[1] = ps[1]; p3[2] = ps[2];
    FUN_006c4200(res, scratch, p3, axisDir, color, uv, param10);
    BAKE_TAIL_ACOS()
    BAKE_EPILOG()
}

// uv4u16 / colour4f  / core FUN_006c4200 / acos weight (axis.y * len)
// @ 0x006d9280
bool Bake_6d9280(float* out, int count, ElemTable* table, BakeEntry* entries, StreamDesc* pos,
                 float* axis, ScaleInfo* scaleInfo, int index, int handleIndex, int param10)
{
    BAKE_PROLOG()
    uint16_t* s = (uint16_t*)(hA.b + hA.d * e->fc);
    uint32_t uv[4];
    uv[0] = s[0] / 3; uv[1] = s[1] / 3; uv[2] = s[2] / 3; uv[3] = s[3] / 3;
    (void)uv;
    {
        float* c = (float*)(hB.b + hB.d * e->f8);
        color[0] = c[0]; color[1] = c[1]; color[2] = c[2]; color[3] = c[3];
    }
    float* ps = (float*)(pos->base + pos->stride * e->f0);
    p3[0] = ps[0]; p3[1] = ps[1]; p3[2] = ps[2];
    FUN_006c4200(res, scratch, p3, axisDir, color, uv, param10);
    BAKE_TAIL_ACOS()
    BAKE_EPILOG()
}

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

// The EASTL insert tag: a bool in a 1-byte struct, passed as one stack dword.
struct TrueTypeTag { bool b; };

// The inserted element is a (key, mapped value) pair; the node constructor copies both words
// into the node's payload (key then mapped value).
struct MapEntry
{
    int mKey;       // stored at node +0x10
    int mMapped;    // stored at node +0x14
};

// 0x006c4b50: eastl rbtree DoInsertValue(hint-iterator, value, true_type); `this` arrives in
// ecx and the four remaining dwords are (out, position, &value, tag), popped by the callee.
struct TreeInsert
{
    void* DoInsertValue(void** out, RBNode* position, const MapEntry* value, TrueTypeTag tag);
};

// @ 0x006d95e0
void* RBTree::FindOrInsert(const int* pKey)
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
    if (lower == endNode || *pKey < lower->mKey)
    {
        MapEntry entry = { *pKey, 0 };
        void* result = 0;
        TrueTypeTag tag;
        tag.b = false;
        ((TreeInsert*)this)->DoInsertValue(&result, lower, &entry, tag);
        return (char*)result + 0x14;
    }
    return (char*)lower + 0x14;
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

struct HandleVec
{
    uint32_t mWords[5];
    void Insert(uint32_t position, uint32_t value);
};

// @ 0x006d9660
void HandleVec::Insert(uint32_t position, uint32_t value)
{
    uint32_t* self = mWords;
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
