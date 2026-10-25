// Slice s009a3c80 - nSPCreatureAnim animation-cache helpers + vector math.
// (0x9a3c80..0x9a4a70, 17 functions).
//
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
//
// The region mixes integer code, EASTL red-black-tree wrappers and SSE/x87 vector math,
// so individual functions were compiled under different code-generation settings.  The
// integer helpers follow the UTFWin defaults (/O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast);
// the x87 vector helpers (LengthSqVec3/NormalizeVec3/PerpPair) were built for the plain
// IA32 float model (the same set without /arch:SSE).  See partial.txt for what is not
// reconstructed.

#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// Shared external helpers / tiny stub object types (calls are thiscall unless noted).
// ---------------------------------------------------------------------------
struct Obj99f0b0 { void FUN_0099f0b0(); };   // 0x99f0b0
struct Obj9c26a0 { void Release(); };        // 0x9c26a0 nSPCreatureAnim::creature_static_data::Release
struct Obj99d060 { void FUN_0099d060(); };   // 0x99d060
struct Obj99c980 { void FUN_0099c980(); };   // 0x99c980
struct Obj9b3450 { void FUN_009b3450(); };   // 0x9b3450

void operator_delete(void* p);               // 0xf47380

namespace nSPCreatureAnim {

// Intrusive red-black-tree node header (EASTL rbtree_node_base layout).
struct AnimNode {
    AnimNode* mpNodeRight;    // +0x00
    AnimNode* mpNodeLeft;     // +0x04
    AnimNode* mpNodeParent;   // +0x08
    char      mColor;         // +0x0c
    char      mPad0[3];
};

// Node of the hash-keyed animation cache (map<unsigned, AutoRefCount<animation_data> >).
struct AnimNodeA : AnimNode {
    unsigned mKey;            // +0x10
    void*    mpValue;         // +0x14
};

// Node of the (creature_static_data*, id)-keyed cache.
struct AnimNodeB : AnimNode {
    void*    mpOwner;         // +0x10
    unsigned mId;             // +0x14
    void*    mpValue;         // +0x18
};

// Value/key pair stored in an anim-cache A node.
struct AnimValueA {
    unsigned mKey;            // +0x00
    void*    mpValue;         // +0x04
};

// Value/key triple stored in an anim-cache B node.
struct AnimValueB {
    void*    mpOwner;         // +0x00
    unsigned mId;             // +0x04
    void*    mpValue;         // +0x08
};
struct AnimKeyB {
    void*    mpOwner;         // +0x00
    unsigned mId;             // +0x04
};
struct InsertRetB {
    AnimNodeB* mpNode;
    bool       mbInserted;
};

// Empty one-byte "unique keys" tag argument (only its byte is initialised, so the
// generated argument push mirrors the original's byte-store-then-dword-push).
struct UniqueKeys { char mPad; UniqueKeys() : mPad(0) {} };

// Intrusive red-black-tree container used by the anim cache.
struct AnimTree {
    int        mCompare;       // +0x00
    AnimNode   mAnchor;        // +0x04
    unsigned   mnSize;         // +0x14
    const char* mpAllocator;   // +0x18

    // 0x9a3c80 - recursively frees a node chain (node[0]=key-link, node[4]=next).
    void FUN_009a3c80(void* node);
    // 0x9a3c40 - sibling free used for the other global list.
    void FUN_009a3c40(void* node);
    InsertRetB FUN_009a3da0(AnimNodeB* position, const AnimValueB* value, UniqueKeys unique); // 0x9a3da0
    static void FUN_009a4190(int param);                      // 0x9a4190
    void** FUN_009a4310(unsigned* key);                        // 0x9a4310
    void** FUN_009a4390(AnimKeyB* key);                        // 0x9a4390

    // Inlined cache-node-list clear helpers (used by FUN_009a3ef0).
    void ClearA()
    {
        FUN_009a3c40(mAnchor.mpNodeParent);
        AnimNode* base = &mAnchor;
        mAnchor.mpNodeRight = base;
        mAnchor.mpNodeLeft = base;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
    void ClearB()
    {
        FUN_009a3c80(mAnchor.mpNodeParent);
        AnimNode* base = &mAnchor;
        mAnchor.mpNodeRight = base;
        mAnchor.mpNodeLeft = base;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
};

// Creature animation static data (only the fields touched here).
struct creature_static_data {
    char     mPad00[4];
    int      mByteSize;        // +0x04
    char     mPad08[0x108];
    unsigned mAnimId;          // +0x110
    void AddRef();             // 0x9b3450
    void Release();            // 0x9c26a0
};

// Animation record passed to the cache lookup/insert (only the fields touched here).
struct animation_record {
    char     mPad00[0x110];
    unsigned mAnimId;          // +0x110
};

// Animation data block as seen by the hash-keyed cache.
struct animation_static_data {
    char mPad00[4];
    int  mByteSize;            // +0x04
    char mPad08[4];
    char mFilename[0x120];     // +0x0c .. +0x12c
    int  mSerial;              // +0x12c
    void AddRef();             // 0x99c660 (increments this+0x114)
    void Release();            // 0x99d060
};

// Reference-counted animation bind record stored in the B cache.
struct animation_bind_record {
    void AddRef();             // 0x99c980
    void Release();            // 0x99f0b0
};

// Animation cache manager holding the tree of finished/queued entries.
struct animation_cache_manager {
    unsigned FUN_009aba80(void* key, unsigned limit);   // 0x9aba80
    unsigned FUN_009ab540(void* key, unsigned limit);   // 0x9ab540
};

int FUN_009a4430(char* filename, int hash, char* name);        // 0x9a4430
int FUN_009a4550(creature_static_data* data, animation_record* record); // 0x9a4550
void FUN_009a3ef0();                                           // 0x9a3ef0
unsigned FUN_009a3f50(int key, unsigned limit);                // 0x9a3f50
unsigned FUN_009a4020(int data, unsigned limit);               // 0x9a4020

} // namespace nSPCreatureAnim

// ---------------------------------------------------------------------------
// 0x009a3c80  AnimTree::FUN_009a3c80 (recursive node-chain delete)
// ---------------------------------------------------------------------------
// @ 0x009a3c80
void nSPCreatureAnim::AnimTree::FUN_009a3c80(void* node)
{
    while (node != 0) {
        this->FUN_009a3c80(*(void**)node);
        void* next = *(void**)((char*)node + 4);
        if (*(void**)((char*)node + 0x18) != 0)
            (*(Obj99f0b0**)((char*)node + 0x18))->FUN_0099f0b0();
        if (*(void**)((char*)node + 0x10) != 0)
            (*(Obj9c26a0**)((char*)node + 0x10))->Release();
        operator_delete(node);
        node = next;
    }
}

// ---------------------------------------------------------------------------
// 0x009a3ef0  cache shutdown (clears both global anim-cache trees)
// ---------------------------------------------------------------------------
// @ 0x009a3ef0
void nSPCreatureAnim::FUN_009a3ef0()
{
    if (*(nSPCreatureAnim::AnimTree**)0x166c058 != 0)
        (*(nSPCreatureAnim::AnimTree**)0x166c058)->ClearA();
    if (*(nSPCreatureAnim::AnimTree**)0x166c05c != 0)
        (*(nSPCreatureAnim::AnimTree**)0x166c05c)->ClearB();
}

// ---------------------------------------------------------------------------
// 0x009a4660  Morton-style bit interleave helper
// ---------------------------------------------------------------------------
// @ 0x009a4660
unsigned FUN_009a4660(unsigned param_1, unsigned param_2)
{
    unsigned result = 0;
    for (unsigned bit = 1; param_2 != 0 && param_1 != 0; bit <<= 1) {
        unsigned t = (param_1 - 1) & param_1;
        unsigned x = t ^ param_1;
        result |= (unsigned)((x & param_2) ? 0xffffffffu : 0u) & bit;
        param_2 &= ~x;
        param_1 = t;
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x009a47e0  nSPCreatureAnim::CheckEventLocationType
// ---------------------------------------------------------------------------
namespace nSPCreatureAnim {

// @ 0x009a47e0
bool CheckEventLocationType(unsigned param_1, int param_2)
{
    if ((param_1 & 0xc00000) == 0x400000) {
        if ((param_2 == 0) || (*(char*)(param_2 + 0x2d6) == 0))
            return false;
    } else if (((param_1 & 0xc00000) == 0x800000) && (param_2 != 0) && (*(char*)(param_2 + 0x2d6) != 0)) {
        return false;
    }
    if ((param_1 & 0xc000000) == 0x4000000) {
        if ((param_2 == 0) || (*(char*)(param_2 + 0x2d4) == 0))
            return false;
    } else if (((param_1 & 0xc000000) == 0x8000000) && (param_2 != 0) && (*(char*)(param_2 + 0x2d4) != 0)) {
        return false;
    }
    if ((param_1 & 0x3000000) == 0x1000000) {
        if ((param_2 == 0) || (*(char*)(param_2 + 0x2d5) == 0))
            return false;
    } else if (((param_1 & 0x3000000) == 0x2000000) && (param_2 != 0) && (*(char*)(param_2 + 0x2d5) != 0)) {
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x009a4890  nSPCreatureAnim::ContextFilterEventLocationData
// ---------------------------------------------------------------------------
// @ 0x009a4890
bool ContextFilterEventLocationData(unsigned param_1, int param_2, int* param_3, int param_4, int param_5)
{
    switch (param_1 & 0x70) {
    case 0x00:
        return true;
    case 0x10:
        return param_2 == 0;
    case 0x20:
        return param_2 != 0;
    case 0x30:
        return param_4 == -1 || param_3[param_2] == param_4;
    case 0x40:
        return param_4 == -1 || param_3[param_2] != param_4;
    case 0x50:
        return param_3[param_2] == param_5;
    case 0x60:
        return param_3[param_2] != param_5;
    default:
        return false;
    }
}

} // namespace nSPCreatureAnim

// ---------------------------------------------------------------------------
// 0x009a46a0  quaternion -> 3x3 matrix (row major, SSE)
// ---------------------------------------------------------------------------
// @ 0x009a46a0
void FUN_009a46a0(float* out, float* q)
{
    float f1 = q[1];
    float f2 = q[2];
    float f3 = q[0];
    float f4 = q[3];
    out[0] = 1.0f - (f2 * f2 + f1 * f1) * 2.0f;
    out[1] = (f1 * f3 - f4 * f2) * 2.0f;
    out[2] = (f4 * f1 + f2 * f3) * 2.0f;
    out[3] = (f4 * f2 + f1 * f3) * 2.0f;
    out[4] = 1.0f - (f2 * f2 + f3 * f3) * 2.0f;
    out[5] = (f2 * f1 - f4 * f3) * 2.0f;
    out[6] = (f2 * f3 - f4 * f1) * 2.0f;
    out[7] = (f4 * f3 + f2 * f1) * 2.0f;
    out[8] = 1.0f - (f1 * f1 + f3 * f3) * 2.0f;
}

// ---------------------------------------------------------------------------
// 0x009a49b0  LengthSqVec3
// ---------------------------------------------------------------------------
// @ 0x009a49b0
float LengthSqVec3(float* v)
{
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

// ---------------------------------------------------------------------------
// 0x009a49d0  NormalizeVec3
// ---------------------------------------------------------------------------
// @ 0x009a49d0
void NormalizeVec3(float* out, float* in, float* lengthOut)
{
    float x = in[0];
    float z = in[2];
    float y = in[1];
    float len = sqrtf(y * y + z * z + x * x);
    if (lengthOut != 0) {
        *lengthOut = len;
    }
    if (len != 0.0f) {
        float inv = 1.0f / len;
        x = inv * x;
        y = inv * y;
        z = inv * z;
    }
    out[0] = x;
    out[1] = y;
    out[2] = z;
}

// ---------------------------------------------------------------------------
// 0x009a4a70  PerpPair
// ---------------------------------------------------------------------------
// @ 0x009a4a70
void PerpPair(float* n, float* out1, float* out2)
{
    float v[3] = { 1.0f, 1.0f, 1.0f };
    float best = 0.0f;
    float x = n[0];
    if (0.0f < fabsf(x))
        best = fabsf(x);
    float a1 = fabsf(n[1]);
    bool b = best < a1;
    if (b)
        best = a1;
    unsigned idx = (unsigned)b;
    if (best < fabsf(n[2]))
        idx = 2;
    float n2 = n[2];
    float n1 = n[1];
    v[idx] = 0.0f;

    float f4 = n2 * v[1] - n1 * v[2];
    float f5 = n1 * v[0] - x * v[1];
    float f3 = x * v[2] - n2 * v[0];
    float len = sqrtf(f4 * f4 + (f3 * f3 + f5 * f5));
    if (len != 0.0f) {
        len = 1.0f / len;
        f4 = len * f4;
        f3 = len * f3;
        f5 = len * f5;
    }
    out1[0] = f4;
    out1[1] = f3;
    out1[2] = f5;

    float g7 = n[1] * f5 - n[2] * f3;
    float g5 = n[2] * f4 - n[0] * f5;
    float g3 = n[0] * f3 - n[1] * f4;
    float len2 = sqrtf(g7 * g7 + (g3 * g3 + g5 * g5));
    if (len2 != 0.0f) {
        len2 = 1.0f / len2;
        g7 = len2 * g7;
        g5 = len2 * g5;
        g3 = len2 * g3;
    }
    out2[0] = g7;
    out2[1] = g5;
    out2[2] = g3;
}

// ---------------------------------------------------------------------------
// EASTL red-black-tree / anim-cache entry points.
// ---------------------------------------------------------------------------
namespace nSPCreatureAnim {

extern AnimTree*                  g_animTreeA;      // 0x166c058
extern AnimTree*                  g_animTreeB;      // 0x166c05c
extern unsigned                   g_animByteCount;  // 0x166c060
extern unsigned                   g_animByteLimit;  // 0x1550b7c
extern animation_cache_manager*   g_animCacheMgr;   // 0x166c084

// Tree B node/insert helper: DoInsertValueImpl (0x9a3a10).
struct AnimTreeInserter {
    void Insert(AnimNodeB** out, AnimNodeB* parent, const AnimValueB* value, char force); // 0x9a3a10
};

// Tree A hinted insert: DoInsertValue(position, value, true_type) (0x9a3cd0).
struct InsertRetA {
    AnimNodeA* mpNode;
    bool       mbInserted;
};
struct AnimTreeInserterA {
    InsertRetA Insert(AnimNodeA* position, const AnimValueA* value, UniqueKeys unique);  // 0x9a3cd0
};

// Tree B regular insert: DoInsertValue(value, true_type) (0x9a3b10).
struct AnimTreeRegularInserter {
    void Insert(InsertRetB* out, const AnimValueB* value, UniqueKeys unique);      // 0x9a3b10
};

// Tree B lower_bound (0x9a3760).
struct TreeBLowerBound {
    void LowerBound(AnimNodeB** out, const AnimKeyB* key);                         // 0x9a3760
};

// Tree A find helper: eastl::rbtree<unsigned, AutoRefCount<...> >::find (0xe5c780).
struct TreeAFinder {
    void Find(void** out, const unsigned* key);            // 0xe5c780
};

// Animation bind record constructor (0x99f090).
struct BindRecordCtor {
    void* Construct();
};

} // namespace nSPCreatureAnim

extern int g_animSerial;                                    // 0x166b260
extern "C" void* __cdecl operator_new(unsigned size, const char* name,
                                      int a, int b, const char* file, int line); // 0xf473a0

extern "C" nSPCreatureAnim::AnimNodeB* __stdcall FUN_009a3890(const nSPCreatureAnim::AnimValueB* value); // 0x9a3890
extern "C" nSPCreatureAnim::AnimNode* __cdecl FUN_00921580(nSPCreatureAnim::AnimNode* node);            // 0x921580
extern "C" void __cdecl FUN_00921880(nSPCreatureAnim::AnimNode* node, nSPCreatureAnim::AnimNode* anchor); // 0x921880
extern "C" void __cdecl FUN_009216a0(nSPCreatureAnim::AnimNode* node, nSPCreatureAnim::AnimNode* parent,
                                     nSPCreatureAnim::AnimNode* anchor, int side);                       // 0x9216a0
extern "C" bool __cdecl FUN_009a38f0(void* owner, unsigned id, void** out);                              // 0x9a38f0
extern "C" void* __cdecl FUN_0099efd0(const char* filename, int hash);                                   // 0x99efd0
extern "C" unsigned __cdecl FUN_00932e80(const char* text, unsigned seed, int flag);                     // 0x932e80
extern "C" void __cdecl FUN_009a9b70(void* handle, unsigned size, char* buffer, int flag);               // 0x9a9b70
extern "C" bool __cdecl FUN_009a1ee0(nSPCreatureAnim::animation_record* record,
                                     nSPCreatureAnim::creature_static_data* data, void* bindRecord);     // 0x9a1ee0

namespace nSPCreatureAnim {

static inline bool KeyLessNodeValue(const AnimNodeB* node, const AnimValueB& value)
{
    if (value.mpOwner > node->mpOwner)
        return true;
    if (value.mpOwner < node->mpOwner)
        return false;
    if (node->mId < value.mId)
        return true;
    return false;
}

static inline bool KeyLessValueNode(const AnimValueB& value, const AnimNodeB* node)
{
    if (node->mpOwner > value.mpOwner)
        return true;
    if (node->mpOwner < value.mpOwner)
        return false;
    if (value.mId < node->mId)
        return true;
    return false;
}

static inline bool KeyLessKeyNode(const AnimKeyB& key, const AnimNodeB* node)
{
    if (node->mpOwner > key.mpOwner)
        return true;
    if (node->mpOwner < key.mpOwner)
        return false;
    if (key.mId < node->mId)
        return true;
    return false;
}

static inline bool KeyLessNodeKey(const AnimNodeB* node, const AnimKeyB& key)
{
    if (node->mpOwner < key.mpOwner)
        return true;
    if (key.mpOwner < node->mpOwner)
        return false;
    if (node->mId < key.mId)
        return true;
    return false;
}

} // namespace nSPCreatureAnim

// Hinted insert into the (owner,id)-keyed tree, mirroring the EASTL
// insert(position, value) dispatch at 0x9a3da0.
// @ 0x009a3da0
nSPCreatureAnim::InsertRetB nSPCreatureAnim::AnimTree::FUN_009a3da0(
        AnimNodeB* position, const AnimValueB* value, UniqueKeys)
{
    AnimNodeB* const last = (AnimNodeB*)mAnchor.mpNodeRight;
    AnimNodeB* const head = (AnimNodeB*)&mAnchor;
    InsertRetB result;

    if ((position != last) && (position != head)) {
        AnimNodeB* const next = (AnimNodeB*)FUN_00921580(position);
        if (KeyLessNodeValue(position, *value) && KeyLessValueNode(*value, next)) {
            if (position->mpNodeRight != 0) {
                AnimNodeB* node = FUN_009a3890(value);
                FUN_009216a0(node, next, head, 0);
                mnSize += 1;
                result.mpNode = node;
                return result;
            }
            ((AnimTreeInserter*)this)->Insert(&result.mpNode, position, value, 0);
            return result;
        }
    } else if ((mnSize != 0) && KeyLessNodeValue(last, *value)) {
        int side = ((last == head) || KeyLessValueNode(*value, last)) ? 0 : 1;
        AnimNodeB* node = FUN_009a3890(value);
        FUN_009216a0(node, last, head, side);
        mnSize += 1;
        result.mpNode = node;
        return result;
    }

    InsertRetB regular;
    ((AnimTreeRegularInserter*)this)->Insert(&regular, value, UniqueKeys());
    result.mpNode = regular.mpNode;
    return result;
}

// Erase up to `limit` entries whose key owner equals `key` (first tree key field).
// @ 0x009a3f50
unsigned nSPCreatureAnim::FUN_009a3f50(int key, unsigned limit)
{
    unsigned savedEcx;
    __asm { mov savedEcx, ecx }
    unsigned count = 0;
    if (key != 0) {
        if (g_animCacheMgr != 0)
            count = g_animCacheMgr->FUN_009aba80((void*)key, limit);
        if ((g_animTreeB != 0) && (count < limit)) {
            AnimNodeB* const head = (AnimNodeB*)&g_animTreeB->mAnchor;
            AnimNodeB* node = (AnimNodeB*)head->mpNodeLeft;
            while (node != head) {
                if (node->mpOwner == (void*)key) {
                    g_animTreeB->mnSize -= 1;
                    AnimNodeB* next = (AnimNodeB*)FUN_00921580(node);
                    FUN_00921880(node, (AnimNode*)head);
                    if (node->mpValue != 0)
                        ((animation_bind_record*)node->mpValue)->Release();
                    if (node->mpOwner != 0)
                        ((creature_static_data*)node->mpOwner)->Release();
                    operator_delete(node);
                    count += 1;
                    if (count == limit)
                        break;
                    node = next;
                } else {
                    node = (AnimNodeB*)FUN_00921580(node);
                }
            }
        }
    }
    __asm { mov ecx, savedEcx }
    return count;
}

// Erase up to `limit` cached entries belonging to `data`: first the (owner,id) tree
// entries whose id matches, then the hash-keyed tree entries whose animation data
// pointer matches (adjusting the global byte counter).
// @ 0x009a4020
unsigned nSPCreatureAnim::FUN_009a4020(int data, unsigned limit)
{
    unsigned savedEcx;
    __asm { mov savedEcx, ecx }
    unsigned count = 0;
    if (data == 0) {
        __asm { mov ecx, savedEcx }
        return 0;
    }
    if (g_animCacheMgr != 0)
        count = g_animCacheMgr->FUN_009ab540((void*)data, limit);

    if ((g_animTreeB != 0) && (count < limit)) {
        AnimNodeB* const head = (AnimNodeB*)&g_animTreeB->mAnchor;
        AnimNodeB* node = (AnimNodeB*)head->mpNodeLeft;
        while (node != head) {
            if ((node->mId == ((creature_static_data*)data)->mAnimId) && (node->mpValue != 0)) {
                g_animTreeB->mnSize -= 1;
                AnimNodeB* next = (AnimNodeB*)FUN_00921580(node);
                FUN_00921880(node, (AnimNode*)head);
                if (node->mpValue != 0)
                    ((animation_bind_record*)node->mpValue)->Release();
                if (node->mpOwner != 0)
                    ((creature_static_data*)node->mpOwner)->Release();
                operator_delete(node);
                count += 1;
                if (count == limit)
                    break;
                node = next;
            } else {
                node = (AnimNodeB*)FUN_00921580(node);
            }
        }
    }

    if ((g_animTreeA != 0) && (count < limit)) {
        AnimNodeA* const head = (AnimNodeA*)&g_animTreeA->mAnchor;
        AnimNodeA* node = (AnimNodeA*)head->mpNodeLeft;
        while (node != head) {
            if (node->mpValue == (void*)data) {
                g_animByteCount -= ((creature_static_data*)data)->mByteSize;
                g_animTreeA->mnSize -= 1;
                AnimNodeA* next = (AnimNodeA*)FUN_00921580((AnimNode*)node);
                FUN_00921880((AnimNode*)node, (AnimNode*)head);
                if (node->mpValue != 0)
                    ((animation_static_data*)node->mpValue)->Release();
                operator_delete(node);
                count += 1;
                if (count == limit)
                    break;
                node = next;
            } else {
                node = (AnimNodeA*)FUN_00921580((AnimNode*)node);
            }
        }
    }
    __asm { mov ecx, savedEcx }
    return count;
}

namespace nSPCreatureAnim {

// SP::SimpleVector<void*> used by the cache walk (begin/end/cap, 4-byte elements).
struct CacheVec {
    void* mpBegin;
    void* mpEnd;
    void* mpCap;
    void FUN_009529d0(unsigned n);                       // 0x9529d0  reserve(n)
    void FUN_00a80dd0(void** pos, void* const& value);   // 0xa80dd0  DoInsertValue(pos, value)
};

} // namespace nSPCreatureAnim

// Empty one-byte heap comparator; MSVC materialises the temporary in a byte slot and
// pushes it as one dword, which is what the original call sites do.
struct CacheLess { char mPad; CacheLess() : mPad(0) {} };

void* __cdecl FUN_00921580(void* node);                                     // 0x921580 eastl::RBTreeIncrement
void __cdecl FUN_009a36a0(void* first, int a, int b, void* value, CacheLess c);  // 0x9a36a0 heap sift-up
void __cdecl FUN_009a36f0(void* first, int a, int b, int hole, void* value, CacheLess c);  // 0x9a36f0 heap sift-down
unsigned __cdecl FUN_009a4020_cdecl(int key, unsigned limit);               // 0x9a4020 tree erase-by-key (cdecl entry)

// Walks the global anim-cache tree in key order, pushing each node payload (node+0x14)
// onto a temporary vector as a max-heap keyed on the node's +0x12c field, then drains
// the heap while the global counter 0x166c060 stays above 60% of the limit 0x1550b7c,
// erasing every popped entry from the tree (FUN_009a4020) except the one equal to param.
// @ 0x009a4190
void nSPCreatureAnim::AnimTree::FUN_009a4190(int param)
{
    if (*(unsigned*)0x166c060 <= *(unsigned*)0x1550b7c)
        return;

    char* cache = *(char**)0x166c058;
    nSPCreatureAnim::CacheVec v = { 0, 0, 0 };
    v.FUN_009529d0(*(unsigned*)(cache + 0x14));

    char* const anchor = cache + 4;
    for (char* node = *(char**)(cache + 8); node != anchor; node = (char*)FUN_00921580(node)) {
        void* item = *(void**)(node + 0x14);
        if (item == 0)
            continue;
        void** slot = (void**)v.mpEnd;
        if (slot < (void**)v.mpCap) {
            v.mpEnd = slot + 1;
            *slot = item;
        } else {
            void* tmp = item;
            v.FUN_00a80dd0(slot, tmp);
        }
        FUN_009a36a0(v.mpBegin, 0, (int)(((char*)v.mpEnd - (char*)v.mpBegin) >> 2) - 1,
                     *((void**)v.mpEnd - 1), CacheLess());
    }

    int limit = (int)(*(unsigned*)0x1550b7c * 0.6);
    void** first = (void**)v.mpBegin;
    void** last = (void**)v.mpEnd;
    while (*(unsigned*)0x166c060 > (unsigned)limit) {
        int count = (int)(last - first);
        if (count <= 1)
            break;
        void* popped = last[-1];
        last[-1] = first[0];
        FUN_009a36f0(first, 0, count - 1, 0, popped, CacheLess());
        void* top = last[-1];
        v.mpEnd = --last;
        if (top != (void*)param)
            FUN_009a4020_cdecl((int)top, 0xffffffffu);
    }

    if (v.mpBegin != 0 && ((int*)v.mpBegin)[-1] != 0)
        operator_delete(v.mpBegin);
}

// ---------------------------------------------------------------------------
// AnimTree::FUN_009a4310 - find-or-insert in the hash-keyed cache (tree A).
// Returns the address of the node's AutoRefCount payload slot.
// @ 0x009a4310
void** nSPCreatureAnim::AnimTree::FUN_009a4310(unsigned* key)
{
    AnimNodeA* const head = (AnimNodeA*)&mAnchor;
    unsigned const k = *key;
    AnimNodeA* lowerBound = head;
    AnimNodeA* current = (AnimNodeA*)mAnchor.mpNodeParent;
    while (current != 0) {
        if (current->mKey < k) {
            current = (AnimNodeA*)current->mpNodeRight;
        } else {
            lowerBound = current;
            current = (AnimNodeA*)current->mpNodeLeft;
        }
    }
    if ((lowerBound != head) && (lowerBound->mKey <= k))
        return &lowerBound->mpValue;

    AnimValueA value;
    value.mKey = k;
    value.mpValue = 0;
    return &((AnimTreeInserterA*)this)->Insert(lowerBound, &value, UniqueKeys()).mpNode->mpValue;
}

// ---------------------------------------------------------------------------
// AnimTree::FUN_009a4390 - find-or-insert in the (owner,id)-keyed cache (tree B).
// Returns the address of the node's bind-record payload slot.
// @ 0x009a4390
void** nSPCreatureAnim::AnimTree::FUN_009a4390(AnimKeyB* key)
{
    AnimNodeB* const head = (AnimNodeB*)&mAnchor;
    AnimNodeB* lowerBound;
    ((TreeBLowerBound*)this)->LowerBound(&lowerBound, key);
    if ((lowerBound != head) && !KeyLessKeyNode(*key, lowerBound))
        return &lowerBound->mpValue;

    AnimValueB value;
    value.mpOwner = key->mpOwner;
    if (value.mpOwner != 0)
        ((creature_static_data*)value.mpOwner)->AddRef();
    value.mId = key->mId;
    value.mpValue = 0;
    InsertRetB result = FUN_009a3da0(lowerBound, &value, UniqueKeys());
    if (value.mpOwner != 0)
        ((creature_static_data*)value.mpOwner)->Release();
    return &result.mpNode->mpValue;
}

// ---------------------------------------------------------------------------
// nSPCreatureAnim::LoadAndCacheAnimationStaticData - resolve an animation by
// file name / hash, create it on demand, stamp its serial and add it to the
// hash-keyed cache; then run the cache-size trimmer.
// @ 0x009a4430
int nSPCreatureAnim::FUN_009a4430(char* filename, int hash, char* name)
{
    char buffer[0x200];
    if (hash == 0) {
        if (filename == 0)
            return 0;
        FUN_009a9b70(filename, 0x200, buffer, 0);
        hash = (int)FUN_00932e80(buffer, 0x811c9dc5, 1);
    }

    unsigned key = (unsigned)hash;
    AnimNodeA* it;
    ((TreeAFinder*)g_animTreeA)->Find((void**)&it, &key);
    AnimNodeA* const head = (AnimNodeA*)&g_animTreeA->mAnchor;
    animation_static_data* data;
    if ((it == head) || ((data = (animation_static_data*)it->mpValue) == 0)) {
        data = (animation_static_data*)FUN_0099efd0(filename, hash);
        void** slot = g_animTreeA->FUN_009a4310(&key);
        void* old = *slot;
        if ((void*)data != old) {
            if (data != 0)
                data->AddRef();
            *slot = data;
            if (old != 0)
                ((animation_static_data*)old)->Release();
        }
        if (data == 0)
            goto finish;

        if (name != 0) {
            char* dst = data->mFilename;
            for (;;) {
                char c = *name++;
                *dst++ = c;
                if (c == 0)
                    break;
            }
        }
        g_animByteCount += (unsigned)data->mByteSize;
    }

    data->mSerial = g_animSerial;
    g_animSerial += 1;

finish:
    AnimTree::FUN_009a4190((int)data);
    return (int)data;
}

// ---------------------------------------------------------------------------
// nSPCreatureAnim::FUN_009a4550 - find-or-create the animation bind record for
// (static data, animation record), store it in tree B and return a borrowed
// pointer to it.
// @ 0x009a4550
int nSPCreatureAnim::FUN_009a4550(creature_static_data* data, animation_record* record)
{
    void* found = 0;
    bool bFound = FUN_009a38f0(data, record->mAnimId, &found);
    animation_bind_record* result = (animation_bind_record*)found;

    if (!bFound) {
        animation_bind_record* created =
            (animation_bind_record*)operator_new(0x38, "Anim/abd/struct", 0, 0, 0, 0);
        if (created != 0)
            created = (animation_bind_record*)((BindRecordCtor*)created)->Construct();

        animation_bind_record* value = (animation_bind_record*)found;
        if (created != found) {
            if (created != 0)
                created->AddRef();
            value = created;
            if (found != 0)
                ((animation_bind_record*)found)->Release();
        }

        bool ok = FUN_009a1ee0(record, data, value);
        result = value;
        if (!ok && (value != 0)) {
            result = 0;
            value->Release();
        }

        AnimKeyB key;
        key.mpOwner = data;
        key.mId = record->mAnimId;
        if (data != 0)
            data->AddRef();
        void** slot = g_animTreeB->FUN_009a4390(&key);
        void* old = *slot;
        if ((void*)result != old) {
            if (result != 0)
                result->AddRef();
            *slot = result;
            if (old != 0)
                ((animation_bind_record*)old)->Release();
        }
        if (data != 0)
            data->Release();
    }

    if (result != 0)
        result->Release();
    return (int)result;
}
