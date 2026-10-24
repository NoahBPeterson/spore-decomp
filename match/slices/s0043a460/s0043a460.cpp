// SP::cSPEditorBlock — selection/pinning helpers (unoptimized /Od /Ob1 /arch:SSE).
#include "types.h"

namespace SP {

struct Vec3 { float x, y, z; };
struct Vec4 {
    float x, y, z, w;
    Vec4() {}
    Vec4(const Vec4& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};

class cSPEditorBlock;

// eBlockUIState — the states SetUIState (0x0043A5E0) dispatches on. 3 is not a case.
enum eBlockUIState { kUIState0 = 0, kUIState1, kUIState2, kUIState3, kUIState4, kUIState5 };

// EA::AutoRefCount<cSPEditorBlock> — a 4-byte reference-counted block handle.
struct BlockRef {
    cSPEditorBlock* mBlock;
    BlockRef(cSPEditorBlock* p) : mBlock(p) {}
    cSPEditorBlock* operator->() const { return mBlock; }
    bool operator==(const BlockRef& o) const { return mBlock == o.mBlock; }
};

// eastl::sp_vector_allocator is empty; only its out-of-line copy ctor is left (0x00429360).
struct EmptyAllocator {
    EmptyAllocator() {}
    EmptyAllocator(const EmptyAllocator& x);          // 0x00429360
};

// eastl::vector<BlockRef, EmptyAllocator> (the "BlockVector" destroyed at 0x00453EB0):
// begin/end/capacity followed by the (empty) allocator.
struct BlockVector {
    BlockRef*      mBegin;      // +0x00
    BlockRef*      mEnd;        // +0x04
    BlockRef*      mCapacity;   // +0x08
    EmptyAllocator mAllocator;  // +0x0C

    BlockVector(const EmptyAllocator& a = EmptyAllocator())
        : mBegin(0), mEnd(0), mCapacity(0), mAllocator(a) {}
    BlockRef* begin() const { return mBegin; }
    BlockRef* end() const { return mEnd; }
    int size() const { return (int)(mEnd - mBegin); }
    BlockRef& operator[](int i) const { return mBegin[i]; }
    void erase(BlockRef* first, BlockRef* last);      // 0x00454280
    ~BlockVector();                                   // 0x00453EB0
};

// eastl::remove over an intrusive-pointer range (0x004549B0): compacts out the elements equal
// to value and returns the new end.
BlockRef* Remove(BlockRef* first, BlockRef* last, const BlockRef& value);   // 0x004549B0

// Intrusive 60-bit flag set reached through +0xDC8.
struct BitSet60 {
    uint32_t data[2];
    bool Get(int i) {
        if (i < 60) return (data[i >> 5] & (1u << (i % 32))) != 0;
        return false;
    }
};

// A 12-byte key element vector (begin/end at the head of the field).
struct KeyVec {
    void* begin;
    void* end;
    bool empty() const;   // 0x00526430
};

class cSPEditorBlock { public:
    char     pad00[0x10];
    void*    mModel;                 // +0x10
    char     pad14[0x38 - 0x14];
    uint8_t  f38;                    // +0x38
    uint8_t  f39;                    // +0x39
    char     pad3a[2];
    uint32_t f3c;                    // +0x3C
    uint32_t f40;                    // +0x40
    uint32_t f44;                    // +0x44
    char     pad48[0x1C0 - 0x48];
    float    mBaseJointScale;        // +0x1C0
    float    mUniformScale;          // +0x1C4
    char     pad1c8[0x1D8 - 0x1C8];
    float    f1d8;                   // +0x1D8
    char     pad1dc[0x3E0 - 0x1DC];
    void*    p3e0;                   // +0x3E0
    char     pad3e4[0x3F4 - 0x3E4];
    char     tbl3f4[12];             // +0x3F4
    char     tbl400[12];             // +0x400
    char     pad40c[0xA44 - 0x40C];
    KeyVec   keys;                   // +0xA44
    char     padA4c[0xDC8 - 0xA4C];
    BitSet60 bits;                   // +0xDC8

    bool F3AC40(int type, uint8_t a, uint8_t b);          // 0043AC40
    bool F5a0();                                          // 0043A5A0
    bool F5c0();                                          // 0043A5C0
    float Length1();                                      // 0043A460
    Vec3* GetVec1(Vec3* out);                             // 0043A490
    float Length2();                                      // 0043A500
    Vec3* GetVec2(Vec3* out);                             // 0043A530
    bool SetUIState(eBlockUIState state, bool b1, bool b2, bool b3);   // 0x0043A5E0
    void F830(uint8_t p);                                 // 0043A830
    int  GetSkinIdentifierForPicking();                   // 0043A870
    void F9a0(uint8_t a, uint8_t b);                      // 0043A9A0
    bool F9e0(uint8_t a, uint8_t b);                      // 0043A9E0
    bool Fb90(uint8_t p);                                 // 0043AB90
    void F3cfc0(int a, uint8_t b);                        // 0043CFC0
    void F448a80();                                       // 00448A80
    void F448690(Vec4 v);                                 // 00448690
    void F3cad0();                                        // 0043CAD0
};

void BuildPileList(cSPEditorBlock* block, BlockVector* piles, int flag);   // 0x0048C790

float VectorLength(const Vec3* v);                        // 0040AE50
void* Sub_41DCA0(void* out, void* table, const float* key);  // 0041DCA0
bool  ModelKey_HasResourceType(void* modelKey);           // 00526430 (thiscall)
bool  Sub_43AC40_2(void* self, int type, uint8_t a, uint8_t b);  // 0043AC40 helper

extern const Vec4 g_v4_a;   // 015D21B8
extern const Vec4 g_v4_b;   // 015D21D4

// @ 0x0043A460
float cSPEditorBlock::Length1()
{
    Vec3 v;
    GetVec1(&v);
    return VectorLength(&v);
}

// @ 0x0043A490
Vec3* cSPEditorBlock::GetVec1(Vec3* out)
{
    float t = f1d8;
    float key = t;
    Vec3 tmp;
    Vec3* r = (Vec3*)Sub_41DCA0(&tmp, tbl3f4, &key);
    out->x = r->x;
    out->y = r->y;
    out->z = r->z;
    return out;
}

// @ 0x0043A500
float cSPEditorBlock::Length2()
{
    Vec3 v;
    GetVec2(&v);
    return VectorLength(&v);
}

// @ 0x0043A530
Vec3* cSPEditorBlock::GetVec2(Vec3* out)
{
    float t = f1d8;
    float key = t;
    Vec3 tmp;
    Vec3* r = (Vec3*)Sub_41DCA0(&tmp, tbl400, &key);
    out->x = r->x;
    out->y = r->y;
    out->z = r->z;
    return out;
}

// @ 0x0043A5E0
// Ask this block's pile list whether it accepts `state`. F3AC40 runs the query on this block,
// then every pile in the list is asked the same question and the answers are ANDed; the list
// is built first, so the block itself is removed from it. Runs only when forced and only
// while the "piles built" bit (bit 7 of the flag set) is clear.
bool cSPEditorBlock::SetUIState(eBlockUIState state, bool b1, bool b2, bool b3)
{
    bool changed = F3AC40(state, b1, b2);
    if (b3 && !bits.Get(7)) {
        BlockVector piles;
        BuildPileList(this, &piles, 0);
        piles.erase(Remove(piles.begin(), piles.end(), BlockRef(this)), piles.end());
        for (int i = 0, n = piles.size(); i < n; i++) {
            switch (state) {
            case kUIState0:
                // A block with no settled child asks 2 (the child state), one without asks 0.
                if (F5a0() || F5c0()) {
                    changed = changed & piles[i]->F3AC40(kUIState2, b1, b2);
                } else {
                    changed = changed & piles[i]->F3AC40(kUIState0, b1, b2);
                }
                break;
            case kUIState1:
            case kUIState2:
            case kUIState4:
            case kUIState5:
                changed = changed & piles[i]->F3AC40(state, b1, b2);
                break;
            default:
                break;
            }
        }
    }
    return changed;
}

// @ 0x0043A830
void cSPEditorBlock::F830(uint8_t p)
{
    if (Fb90(p)) {
        SetUIState((eBlockUIState)f3c, true, false, true);
    }
}

// @ 0x0043A870
int cSPEditorBlock::GetSkinIdentifierForPicking()
{
    int result = 3;
    bool useParent = false;
    if ((char*)&keys == 0) {
        useParent = true;
    } else {
        if (!keys.empty()) {
            int count = (int)(((char*)keys.end - (char*)keys.begin) / 12);
            for (int i = 0; i < count; i++) {
                uint32_t id = *(uint32_t*)((char*)keys.begin + i * 12);
                if (id == 0xE16370D5u) result = 1;
                else if (id == 0x6189D2DEu) result = 0;
            }
        } else {
            useParent = true;
        }
    }
    if (useParent) {
        if (bits.Get(11)) result = 0;
        else result = 1;
    }
    return result;
}

// @ 0x0043A9A0
void cSPEditorBlock::F9a0(uint8_t a, uint8_t b)
{
    if (F9e0(a, b)) {
        SetUIState((eBlockUIState)f3c, true, false, true);
    }
}

// @ 0x0043A9E0
bool cSPEditorBlock::F9e0(uint8_t a, uint8_t b)
{
    if (bits.Get(1)) return false;
    if (f39 == a) return false;
    f40 = *(uint32_t*)&f38;
    f44 = f3c;
    if (f39 != 0) {
        F3cfc0(0, b);
        F448a80();
    } else {
        void* model = mModel;
        if (model != 0) {
            *(uint32_t*)((char*)model + 4) |= 8;
            *(uint8_t*)((char*)model + 0x5C) = 7;
            F448690(g_v4_b);
        }
        F3cad0();
    }
    f39 = a;
    return true;
}

// @ 0x0043AB90
bool cSPEditorBlock::Fb90(uint8_t p)
{
    if (f38 == p) return false;
    f40 = *(uint32_t*)&f38;
    f44 = f3c;
    f38 = p;
    if (f3c == 3) {
        if (p == 0) {
            F448a80();
        } else {
            F448690(g_v4_a);
        }
    }
    return true;
}

} // namespace SP
