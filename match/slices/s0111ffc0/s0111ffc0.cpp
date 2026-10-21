// Slice s0111ffc0: Havok 3.1.0 (VC .NET 2003, /vc71) — the MOPP compiler core
// (MoppCompiler::buildNode 0x0111ffc0 + MoppCompiler::compile 0x011202d0), the seven per-primitive
// cost helpers (0x01120460..0x01120710), hkWingedEdge::findTriangleOnNearestPlane (0x01120770),
// the winged-edge tetrahedron init (0x01120850) and the hkConvexPenetrationUtil polytope-expansion
// group (0x01120a00..0x01120eb0).
//
// NAMING NOTE: the MOPP-compiler functions (0x0111ffc0 / 0x011202d0) and the seven cost helpers
// (0x01120460..0x01120710) have no symbols in symbols/havok_names.txt; their class/member names below
// are coined from the shapes they compute. The four hkWingedEdge / hkConvexPenetrationUtil functions
// carry their real Havok names.
//
// X87-PRECISION: several helpers keep a value unrounded on the FPU stack across statement boundaries.
// Those points are marked per function.
#include "s0111ffc0.h"
#include <math.h>

// ---------------------------------------------------------------------------------------------------
// Constants (float literals read from the original image)
// ---------------------------------------------------------------------------------------------------
static const float HK_HALF      = 0.5f;          // 0x01471064
static const float HK_ONE       = 1.0f;          // 0x01485720
static const float HK_ZERO      = 0.0f;          // 0x01485378
static const float HK_0_75      = 0.75f;         // 0x01485544
static const float HK_6         = 6.0f;          // 0x0147b9f0
static const float HK_5         = 5.0f;          // 0x01486110
static const float HK_M0_03     = -0.03f;        // 0x0140fed0
static const float HK_1500      = 1500.0f;       // 0x013fec70
static const float HK_3         = 3.0f;          // 0x013eb95c
static const float HK_2_9       = 2.9f;          // 0x014a6120
static const float HK_BIG       = 3.4028202e+37f; // 0x014a6124
static const float HK_RECIP2P31 = 4.656613e-10f; // 0x014a615c

// 0x01103830 fills the six settings floats (1,1,1,1,1,0.5).
static const float HK_SETTINGS_INIT[6] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f };

// ===================================================================================================
// MoppCompiler::buildNode  (__thiscall, ret 0x10)
// ===================================================================================================
// Recursively builds a MOPP tree node. A "leaf" node (primList.count == 1) is delegated to
// 0x0111f9e0; otherwise a fresh node is popped off free list A, initialised from its parent, the three
// child shapes registered with container B (or as a range with container B slot 5), and the recursion
// continued into the two children produced by 0x0111fe30.
// @ 0x0111ffc0
MoppChainNode* MoppCompiler::buildNode(MoppChainNode* parent, const int* primList, int side, int depth)
{
    if (primList[1] == 1)
    {
        if (this->m_freeBCount == 0)
            this->m_ifaceA->addShape((void*)this->m_root, (int)this, 0x800, 0, 0);
        // X87/ABI: the call target takes (parent, primList).
        return hkFun_0111f9e0(parent, primList);
    }

    if (this->m_freeACount == 0)
        this->m_ifaceA->addShape((void*)this->m_root, (int)this, 0x800, 0, 0);

    MoppChainNode* node = this->m_freeA;
    this->m_freeA = node->m_parent;
    this->m_freeACount -= 1;
    hkFun_0111efb0(node);

    node->m_pad4[0] = 0;
    node->m_fc4 = 1.0e6f;                       // 0x49742400
    node->m_fbc = 1.0e10f;                      // 0x501502f9
    node->m_first = 0;
    node->m_last = 0;
    node->m_primCount = primList[1];
    node->m_parent = parent;

    if (parent == 0)
    {
        this->m_root = node;
    }
    else
    {
        if (side == 0)
            parent->m_first = node;
        else
            parent->m_last = node;
        node->m_copies[0] = ((uint32_t*)parent)[3];
        node->m_copies[1] = ((uint32_t*)parent)[4];
        node->m_copies[2] = ((uint32_t*)parent)[5];
        node->m_copies[3] = ((uint32_t*)parent)[6];
        node->m_copies[4] = ((uint32_t*)parent)[7];
        node->m_copies[5] = ((uint32_t*)parent)[8];
    }

    int childIdx[3];
    float faceDist[3];
    // X87-PRECISION: 0x0111f4c0 returns three ints and three floats (two by pointer).
    hkFun_0111f4c0(parent, childIdx, faceDist);

    for (int i = 0; i < 3; ++i)
    {
        int entry = childIdx[i] * 0x20;
        float* e = (float*)(this->m_entries + entry);
        if (node->m_fc4 > faceDist[i] + e[4])
        {
            for (int j = i; j < 3; ++j)
            {
                int e2 = childIdx[j] * 0x20;
                this->m_ifaceB->addShapeRange((void*)(this->m_entries + e2), primList[0], primList[1],
                                              (int*)((char*)node + 0xc + childIdx[j] * 8),
                                              (int*)((char*)node + 0x10 + childIdx[j] * 8));
            }
            break;
        }

        int* slot = (int*)((char*)node + 0xc + childIdx[i] * 8);
        this->m_ifaceB->addShape((void*)(this->m_entries + entry), primList[0], primList[1],
                                 slot, slot + 1);

        if (primList[1] > 1)
            hkFun_0111faa0(primList[0], 0, primList[1] - 1, 0);

        hkFun_0111f670(node, (void*)(this->m_entries + entry), primList, slot, depth);
    }

    if (this->m_numEntries > 3)
    {
        int k = 3;
        int off = 0x60;
        do
        {
            if (node->m_fc4 <= *(float*)(this->m_entries + off + 0x10))
                break;
            this->m_ifaceB->addShape((void*)(this->m_entries + off), primList[0], primList[1],
                                     childIdx, &childIdx[1]);
            if (primList[1] > 1)
                hkFun_0111faa0(primList[0], 0, primList[1] - 1, 0);
            hkFun_0111f670(node, (void*)(this->m_entries + off), primList, childIdx, depth);
            ++k;
            off += 0x20;
        } while (k < this->m_numEntries);
    }

    hkFun_0111f400(primList, node);

    if ((void*)node->m_iB8 != (void*)this->m_scratch)
        this->m_ifaceB->addShape((void*)node->m_iB8, primList[0], primList[1], (int*)node, 0);

    // X87/ABI: 0x0111fe30 splits the primitive list for this node into two child lists.
    hkFun_0111fe30(primList, node, depth, &childIdx[0], &childIdx[1]);

    node->m_last = this->buildNode(node, &childIdx[1], 1, depth + 1);
    node->m_first = this->buildNode(node, &childIdx[0], 0, depth + 1);
    return node;
}

// ===================================================================================================
// MoppCompiler::compile  (__thiscall, ret 0x14)
// ===================================================================================================
// Stores the six incoming pointers, initialises the two free lists (A: 0x400 four-node spans of 0xf8
// bytes, B: 0x400 four-node spans of 0xbc bytes), queries the container interfaces for the entry count
// and table, allocates the entry array, then runs one buildNode pass over the whole primitive range.
// @ 0x011202d0
MoppChainNode* MoppCompiler::compile(void* arg0, MoppInterface* ifaceB, int arg2, MoppInterface* ifaceA,
                                     void* source, uint32_t* arena)
{
    this->m_source = source;
    this->m_ifaceB = ifaceB;
    this->m_i20 = arg2;
    this->m_ifaceA = ifaceA;

    int numChildren = ifaceB->getNumSomething();
    int numPrims = *(int*)((char*)source + 4);
    uint32_t arena0 = arena[0];

    this->m_log2Children = 0;
    if (numChildren != 0)
    {
        int n = numChildren;
        int bits = 0;
        do { n >>= 1; ++bits; } while (n != 0);
        this->m_log2Children = bits;
    }

    this->m_freeA = 0;
    this->m_freeACount = 0;
    uint8_t* spanA = (uint8_t*)arena[1];
    for (int i = 0; i < 0x400; ++i)
    {
        uint8_t* n0 = spanA;
        *(uint32_t*)n0 = (uint32_t)(uintptr_t)this->m_freeA;
        this->m_freeACount += 1;
        *(uint32_t*)(n0 + 0xf8) = (uint32_t)(uintptr_t)n0;
        this->m_freeACount += 1;
        *(uint32_t*)(n0 + 0x1f0) = (uint32_t)(uintptr_t)(n0 + 0xf8);
        this->m_freeACount += 1;
        *(uint32_t*)(n0 + 0x2e8) = (uint32_t)(uintptr_t)(n0 + 0x1f0);
        this->m_freeA = (MoppChainNode*)(n0 + 0x2e8);
        this->m_freeACount += 1;
        spanA += 0x3e0;
    }

    this->m_freeB = 0;
    this->m_freeBCount = 0;
    uint8_t* spanB = (uint8_t*)arena[2];
    for (int i = 0; i < 0x400; ++i)
    {
        uint8_t* n0 = spanB;
        *(uint32_t*)n0 = (uint32_t)(uintptr_t)this->m_freeB;
        this->m_freeBCount += 1;
        *(uint32_t*)(n0 + 0xbc) = (uint32_t)(uintptr_t)n0;
        this->m_freeBCount += 1;
        *(uint32_t*)(n0 + 0x178) = (uint32_t)(uintptr_t)(n0 + 0xbc);
        this->m_freeBCount += 1;
        *(uint32_t*)(n0 + 0x234) = (uint32_t)(uintptr_t)(n0 + 0x178);
        this->m_freeB = (MoppChainNode*)(n0 + 0x234);
        this->m_freeBCount += 1;
        spanB += 0x2f0;
    }

    this->m_numEntries = ifaceA->getNumSomething();
    this->m_entries = (uint8_t*)ifaceA->getData();

    int primCount = *(int*)((char*)this->m_source + 8) + 2;
    hkMemory* mem = hkMemory::s_instance;
    uint8_t* entryArr = (uint8_t*)mem->allocate(primCount * 4, 0x25);

    int listBuf[4];
    this->m_scratch = listBuf;
    listBuf[0] = 0;              // primList[0]
    listBuf[2] = 0;              // (count written below at +4 via count)
    listBuf[1] = primCount;      // primList[1]
    listBuf[3] = 0;

    MoppChainNode* root = this->buildNode(0, listBuf, 0, 0);
    ifaceA->addShape(root, (int)this, 0x2000, 0, 0);

    this->m_scratch = 0;
    mem->deallocate((void*)(uintptr_t)arena0);
    return root;
}

// ===================================================================================================
// Cost helpers (0x01120460 .. 0x01120710) — __thiscall members of hkMoppCompilerSettingsBlock
// ===================================================================================================
// @ 0x01120460  a single shared scalar read out of the leaf's +0x24 object.
float hkMoppCompilerSettingsBlock::costDirect(MoppChainLeaf* leaf)
{
    return *(float*)(leaf->m_i24 + 0x10);
}

// @ 0x01120470  range cost: |i14 - i34| * f1c, boosted away from the low end when i00 < i04.
// X87-PRECISION: the running value stays on the FPU stack; only the final product is rounded.
float hkMoppCompilerSettingsBlock::costRange(MoppChainLeaf* leaf)
{
    float v = fabs((float)(leaf->m_i14 - leaf->m_i34));   // fild + fabs
    v = v * leaf->m_f1c;
    if (leaf->m_i00 < leaf->m_i04)
    {
        v = (v - HK_0_75) * HK_6;
        if (v < HK_ZERO)
            return HK_ZERO;
    }
    else
    {
        v = v * v;
    }
    float r = v * v * v * v;      // v^4 (with v pre-squared on the else path)
    return r * this->m_f10;
}

// @ 0x011204d0  span cost A: uses face offset +0x20, guard "x < 0 -> 0".
float hkMoppCompilerSettingsBlock::costSpanA(MoppChainLeaf* leaf)
{
    float A = leaf->m_f20 - (leaf->m_f0c + leaf->m_f08) * HK_HALF;   // kept on the FPU stack
    float r;
    if (leaf->m_i00 < leaf->m_i04)
    {
        float f1 = leaf->m_f0c - leaf->m_f08;
        float f2 = (this->m_f1c <= f1) ? this->m_f1c : f1;
        float s = f1 + f2;
        r = (s <= HK_ZERO) ? HK_BIG : HK_ONE / s;
    }
    else
    {
        r = leaf->m_f10;
    }
    float x = r * A;
    if (x < HK_ZERO)
        return HK_ZERO;
    float x2 = x * x;
    float x4 = x2 * x2;
    float poly = x2 * HK_2_9 + (x4 * HK_3 + (x4 * x4) * HK_1500);
    return poly * this->m_f14;
}

// @ 0x01120570  span cost B: same as A but face offset +0x38 and guard "x > 0 -> 0".
float hkMoppCompilerSettingsBlock::costSpanB(MoppChainLeaf* leaf)
{
    float A = leaf->m_f38 - (leaf->m_f0c + leaf->m_f08) * HK_HALF;   // kept on the FPU stack
    float r;
    if (leaf->m_i00 < leaf->m_i04)
    {
        float f1 = leaf->m_f0c - leaf->m_f08;
        float f2 = (f1 <= this->m_f1c) ? f1 : this->m_f1c;
        float s = f2 + f1;
        r = (s <= HK_ZERO) ? HK_BIG : HK_ONE / s;
    }
    else
    {
        r = leaf->m_f10;
    }
    float x = r * A;
    if (x > HK_ZERO)
        return HK_ZERO;
    float x2 = x * x;
    float x4 = x2 * x2;
    float poly = x2 * HK_2_9 + (x4 * HK_3 + (x4 * x4) * HK_1500);
    return poly * this->m_f14;
}

// @ 0x01120660  split cost A: 011204d0(leaf) + virtual evalCost(leaf) + a small penalty term.
// X87-PRECISION: 011204d0's result stays on the FPU stack while the virtual call runs, then the two
// terms are added in FPU order (evalCost first, then the stored 011204d0 result).
float hkMoppCompilerSettingsBlock::costSplitA(MoppChainLeaf* leaf)
{
    float a = this->costSpanA(leaf);
    float v = this->evalCost(leaf);
    float s = (leaf->m_i2c - leaf->m_i28 < 0x10) ? this->m_f18 * HK_M0_03 : HK_ZERO;
    return (s + v) + a;
}

// @ 0x011206c0  split cost B (a different evaluator shape). X87 order is preserved.
float hkMoppCompilerSettingsBlock::costSplitB(MoppChainLeaf* leaf)
{
    float s1 = this->costSpanB(leaf);
    float s2 = this->costRange(leaf);
    float t1 = (leaf->m_f38 - leaf->m_f20) * leaf->m_f10 * this->m_f0c;
    float t2 = (float)leaf->m_i30 * leaf->m_f1c * this->m_f08 * HK_5;
    return (t1 + t2) + s2 + s1;
}

// @ 0x01120710  fills an 8-float record: [0]=t2, [1]=011204d0, [3]=01120570, [4]=01120470,
// [5]=t1, [6]=leaf->m_f08, [7]=leaf->m_f0c.  (thiscall, ret 8)
void hkMoppCompilerSettingsBlock::costSplitInto(MoppChainLeaf* leaf, float* out)
{
    out[1] = this->costSpanA(leaf);
    out[3] = this->costSpanB(leaf);
    out[4] = this->costRange(leaf);
    out[0] = (float)leaf->m_i30 * leaf->m_f1c * this->m_f08 * HK_5;
    out[5] = (leaf->m_f38 - leaf->m_f20) * leaf->m_f10 * this->m_f0c;
    out[6] = leaf->m_f08;
    out[7] = leaf->m_f0c;
}

// @ 0x01120610  constructor: install the vtable, run 0x01103830, then copy six dwords from the source.
hkMoppCompilerSettingsBlock* hkMoppCompilerSettingsBlock::construct(const float* src)
{
    this->m_refCount = 1;
    this->m_memSize = 1;
    *(uint32_t*)((char*)this) = 0x014a6128u;       // vtable
    hkFun_01103830(HK_SETTINGS_INIT);
    this->m_f08 = src[0];
    this->m_f0c = src[1];
    this->m_f10 = src[2];
    this->m_f14 = src[3];
    this->m_f18 = src[4];
    this->m_f1c = src[5];
    return this;
}

// ===================================================================================================
// hkWingedEdge::findTriangleOnNearestPlane   (__thiscall, no args)
// ===================================================================================================
// Scans the triangle array recording the triangle whose per-triangle distance (+0x60 relative to the
// 0x50-byte stride) is smallest. The loop is unrolled by four with a scalar remainder.
// @ 0x01120770
hkWingedEdgeTriangle* hkWingedEdge::findTriangleOnNearestPlane()
{
    float best = this->m_minDist;                 // +0xf80
    uint8_t* base = (uint8_t*)this + 0xf70;
    int n = this->m_numTriangles - 2;             // ecx = numTriangles - 2
    int m = this->m_numTriangles - 1;             // eax = numTriangles - 1
    uint8_t* cur = base;
    hkWingedEdgeTriangle* bestTri = (hkWingedEdgeTriangle*)base;

    if (m >= 4)
    {
        int count = m >> 2;
        int extra = n - count * 4;
        do
        {
            float f0 = *(float*)(cur + 0x60);
            if (f0 < best) { bestTri = (hkWingedEdgeTriangle*)(cur + 0x50); best = f0; }
            float f1 = *(float*)(cur + 0xb0);
            if (f1 < best) { bestTri = (hkWingedEdgeTriangle*)(cur + 0xa0); best = f1; }
            float f2 = *(float*)(cur + 0x100);
            if (f2 < best) { bestTri = (hkWingedEdgeTriangle*)(cur + 0xf0); best = f2; }
            float f3 = *(float*)(cur + 0x150);
            if (f3 < best) { bestTri = (hkWingedEdgeTriangle*)(cur + 0x140); best = f3; }
            cur += 0x140;
            --count;
        } while (count != 0);
        n = extra;
    }
    if (n >= 0)
    {
        int r = n + 1;
        do
        {
            float* pf = (float*)(cur + 0x60);
            cur += 0x50;
            if (*pf < best) { bestTri = (hkWingedEdgeTriangle*)cur; best = *pf; }
            --r;
        } while (r != 0);
    }
    return bestTri;
}

// ===================================================================================================
// hkWingedEdge tetrahedron init   (__thiscall, ret 0xc)
// ===================================================================================================
// Copies three 0x40-byte vertex records (param2/param3/param4) into the interleaved tetrahedron
// slots, clears the small integer fields, then runs addTetrahedron.
// @ 0x01120850
void hkWingedEdge::initializeWithTetrahedron(void* a, void* b, void* c)
{
    const uint32_t* pa = (const uint32_t*)a;   // param2 -> +0x30.., +0x70.., +0xb0.., +0xf0..
    uint32_t* self = (uint32_t*)this;

    this->m_i08 = 4;
    self[0xc]  = pa[0];  self[0xd]  = pa[1];  self[0xe]  = pa[2];  self[0xf]  = pa[3];
    {
        const uint32_t* pb = (const uint32_t*)b;   // param3 -> +0x40.., +0x80.., +0xc0.., +0x100..
        self[0x10] = pb[0];  self[0x11] = pb[1];  self[0x12] = pb[2];  self[0x13] = pb[3];
        {
            const uint32_t* pc = (const uint32_t*)c;   // param4 -> +0x20.., +0x60.., +0xa0.., +0xe0..
            self[0x8]  = pc[0];  self[0x9]  = pc[1];  self[0xa]  = pc[2];  self[0xb]  = pc[3];
            self[0x14] = 0;
            self[0x1c] = pa[4];  self[0x1d] = pa[5];  self[0x1e] = pa[6];  self[0x1f] = pa[7];
            self[0x20] = pb[4];  self[0x21] = pb[5];  self[0x22] = pb[6];  self[0x23] = pb[7];
            self[0x18] = pc[4];  self[0x19] = pc[5];  self[0x1a] = pc[6];  self[0x1b] = pc[7];
            self[0x24] = 0;
            self[0x2c] = pa[8];  self[0x2d] = pa[9];  self[0x2e] = pa[10]; self[0x2f] = pa[11];
            self[0x30] = pb[8];  self[0x31] = pb[9];  self[0x32] = pb[10]; self[0x33] = pb[11];
            self[0x28] = pc[8];  self[0x29] = pc[9];  self[0x2a] = pc[10]; self[0x2b] = pc[11];
            self[0x34] = 0;
            self[0x3c] = pa[12]; self[0x3d] = pa[13]; self[0x3e] = pa[14]; self[0x3f] = pa[15];
            self[0x40] = pb[12]; self[0x41] = pb[13]; self[0x42] = pb[14]; self[0x43] = pb[15];
            self[0x38] = pc[12]; self[0x39] = pc[13]; self[0x3a] = pc[14]; self[0x3b] = pc[15];
        }
    }
    self[0x44] = 0;
    this->addTetrahedron();
    this->m_i0c = 0;
}

// ===================================================================================================
// hkConvexPenetrationUtil::addPointToSimplex   (__thiscall, ret 4)
// ===================================================================================================
// @ 0x01120a00
void hkConvexPenetrationUtil::addPointToSimplex(const hkWingedEdgeVertex& v)
{
    int n = *this->m_num;
    hkVector4* w = this->m_w + n;
    w->x = v.m_w.x; w->y = v.m_w.y; w->z = v.m_w.z; w->w = v.m_w.w;
    hkVector4* a = this->m_a + n;
    a->x = v.m_a.x; a->y = v.m_a.y; a->z = v.m_a.z; a->w = v.m_a.w;
    hkVector4* b = this->m_b + n;
    b->x = v.m_b.x; b->y = v.m_b.y; b->z = v.m_b.z; b->w = v.m_b.w;
    *this->m_num = *this->m_num + 1;
}

// ===================================================================================================
// hkConvexPenetrationUtil::tryToExpandPolytope   (__thiscall, ret 0x10)
// ===================================================================================================
// Returns hkResult: 0 = expanded, 1 = keep going (status out), 3 = error status.
// @ 0x01120a80
int hkConvexPenetrationUtil::tryToExpandPolytope(hkWingedEdge& we, hkWingedEdgeTriangle* tri,
                                                 hkWingedEdgeVertex* v, int& status)
{
    (void)0;
    float d0[4], d1[4], d2[4];
    const hkVector4* a0 = (const hkVector4*)tri->m_v0;
    const hkVector4* a1 = (const hkVector4*)tri->m_v1;
    const hkVector4* a2 = (const hkVector4*)tri->m_v2;
    const hkVector4& base = v->m_w;
    d0[0] = base.x - a0->x; d0[1] = base.y - a0->y; d0[2] = base.z - a0->z; d0[3] = base.w - a0->w;
    d1[0] = base.x - a1->x; d1[1] = base.y - a1->y; d1[2] = base.z - a1->z; d1[3] = base.w - a1->w;
    d2[0] = base.x - a2->x; d2[1] = base.y - a2->y; d2[2] = base.z - a2->z; d2[3] = base.w - a2->w;

    hkVector4 local;
    hkVector4_setRotatedInverseDir(local, (const hkVector4*)d0, tri);

    bool b0 = (local.x < this->m_bestDist);
    bool b2 = (local.z < this->m_f48);
    bool b3 = (local.w < this->m_f4c);
    bool b1 = (local.y < this->m_f44);
    (void)b2; (void)b3; (void)b1;
    if ((b0 != 0) || (local.y < this->m_f44) || (local.z < this->m_f48) || (local.w < this->m_f4c))
    {
        status = 0;
        return 1;
    }

    int local58 = 0;
    int local54 = 0;
    int r = hkWingedEdge_addVertex(&we, tri, v, &local58, &local54);
    if (r != 0)
    {
        status = 3;
        return 1;
    }
    if ((*(int*)((char*)&we + 0xc) - *(int*)((char*)&we + 0x10)) + 0x37 < local58)
    {
        status = 2;
        return 1;
    }
    r = eastl_vector_int_DoAssignValues(&we, local54, v);
    if (r != 0)
    {
        status = 3;
        return 1;
    }
    return 0;
}

// ===================================================================================================
// hkConvexPenetrationUtil::convertResultToFeature   (__thiscall, ret 0xc)
// ===================================================================================================
// @ 0x01120c40
void hkConvexPenetrationUtil::convertResultToFeature(hkWingedEdge& we, hkWingedEdgeTriangle* tri,
                                                     hkGskOut& out)
{
    int n = 0;
    float bary[3];
    for (;;)
    {
        // copy the triangle's three vertices' m_w into m_w[0..2]
        this->m_w[0] = tri->m_v0->m_w;
        this->m_w[1] = tri->m_v1->m_w;
        this->m_w[2] = tri->m_v2->m_w;

        hkCollideTriangleUtil_calcBarycentric(g_hkZeroVector, this->m_w[0], this->m_w[1], this->m_w[2], bary);
        if (bary[0] >= 0.0f && bary[1] >= 0.0f && bary[2] >= 0.0f)
            break;
        tri = hkWingedEdge_findTriangleNearestOrigin(&we, tri);
        ++n;
        if (n >= 10)
            break;
    }

    this->m_a[0] = tri->m_v0->m_a;
    this->m_b[0] = tri->m_v0->m_b;
    this->m_a[1] = tri->m_v1->m_a;
    this->m_b[1] = tri->m_v1->m_b;
    this->m_a[2] = tri->m_v2->m_a;
    this->m_b[2] = tri->m_v2->m_b;
    *this->m_num = 3;

    const hkVector4* a = this->m_a;
    out.m_point.x = bary[2] * a[2].x + (bary[1] * a[1].x + bary[0] * a[0].x);
    out.m_point.y = bary[2] * a[2].y + (bary[1] * a[1].y + bary[0] * a[0].y);
    out.m_point.z = bary[2] * a[2].z + (bary[1] * a[1].z + bary[0] * a[0].z);
    out.m_point.w = bary[2] * a[2].w + (bary[1] * a[1].w + bary[0] * a[0].w);
    out.m_half = -tri->m_f10;
    out.m_normal = tri->m_normal;
    out.m_normal.x = -out.m_normal.x;
    out.m_normal.y = -out.m_normal.y;
    out.m_normal.z = -out.m_normal.z;
    out.m_normal.w = -out.m_normal.w;
}

// ===================================================================================================
// hkConvexPenetrationUtil::randomVector  @ 0x01120eb0   (__cdecl)
// ===================================================================================================
// x87/FPU order: the (hi-lo) span is computed once and kept on the FPU stack while the three LCG
// steps run, each result scaled into [lo, hi).
// @ 0x01120eb0
void hkConvexPenetrationUtil::randomVector(int seed, float lo, float hi, hkVector4& out)
{
    float d = hi - lo;
    seed = (0x3039 - seed * 0x3e39b193) & 0x7fffffff;
    out.x = ((float)seed * HK_RECIP2P31 + lo) * d;
    seed = (0x3039 - seed * 0x3e39b193) & 0x7fffffff;
    out.y = ((float)seed * HK_RECIP2P31 + lo) * d;
    seed = (0x3039 - seed * 0x3e39b193) & 0x7fffffff;
    out.z = ((float)seed * HK_RECIP2P31 + lo) * d;
}





