// Havok 3.1.0 slice s0111ffc0: the MOPP compiler core (recursive node builder + compile entry), the
// MOPP per-primitive cost helpers, hkWingedEdge::findTriangleOnNearestPlane and the
// hkConvexPenetrationUtil polytope-expansion group.
//
// Struct stubs carry members at the offsets seen in the 32-bit binary (pointer members make 64-bit sizes differ).
#pragma once
#include "types.h"
#include <stddef.h>

typedef float hkReal;

// ---- hkMemory -------------------------------------------------------------------------------------------
// hkMemory::s_instance @0x016e4178 (only the two slots this slice uses).
struct hkMemory {
    virtual void* allocate(int nbytes, int memClass);   // slot 0
    virtual void  deallocate(void* p);                  // slot 1
    static hkMemory* s_instance;
};

// ---- hkVector4 ------------------------------------------------------------------------------------------
struct hkVector4 { float x, y, z, w; };
// ---- MOPP compiler --------------------------------------------------------------------------------------
// The compiler object (this == ecx for 0x0111ffc0 / 0x011202d0). Field offsets recovered from the binary:
//   +8 source array, +0xc scratch pointer, +0x10/+0x14 free-list A (head/count), +0x18/+0x1c free-list B,
//   +0x20 a plain int, +0x24 the "container A" interface, +0x28 the "container B" interface,
//   +0x2c the root node, +0x30 entry count, +0x34 entry array (stride 0x20), +0x38 log2(numChildren).
struct MoppInterface {
    virtual int  getNumSomething();                      // slot 2 (+8)
    virtual void* getData();                             // slot 3 (+0xc)
    virtual void addShape(const void* shape, int first, int last, int* outA, int* outB);   // slot 4 (+0x10)
    virtual void addShapeRange(const void* shape, int first, int last, int* outA, int* outB); // slot 5 (+0x14)
};

// A node of the MOPP tree built by 0x0111ffc0 (0xf8 bytes). `side`==0 means "first child", otherwise "last child".
struct MoppChainNode {
    MoppChainNode* m_parent;      // +0
    // +4 (byte) flag written as 0
    uint8_t  m_pad4[8];           // +4 .. +0xc
    uint32_t m_copies[6];         // +0xc .. +0x24   (six dwords copied from the parent)
    uint32_t m_pad24[0x94];       // +0x24 .. +0xb8
    uint32_t m_iB8;               // +0xb8 (compared against a result field)
    float    m_fbc;               // +0xbc (1.0e10)
    float    m_fc4;               // +0xc4 (1.0e6)
    uint8_t  m_padc8[0x24];       // +0xc8 .. +0xec
    MoppChainNode* m_first;       // +0xec
    MoppChainNode* m_last;        // +0xf0
    int32_t  m_primCount;         // +0xf4 (primitives in the list this node covers)
};

// The compiler object itself.
struct MoppCompiler {
    uint8_t           m_pad0[8];      // +0
    void*             m_source;       // +8
    void*             m_scratch;      // +0xc
    MoppChainNode*    m_freeA;        // +0x10
    int32_t           m_freeACount;   // +0x14
    MoppChainNode*    m_freeB;        // +0x18  (a smaller 0xbc-byte node)
    int32_t           m_freeBCount;   // +0x1c
    int32_t           m_i20;          // +0x20
    MoppInterface*    m_ifaceA;       // +0x24
    MoppInterface*    m_ifaceB;       // +0x28
    MoppChainNode*    m_root;         // +0x2c
    int32_t           m_numEntries;   // +0x30
    uint8_t*          m_entries;      // +0x34  (stride 0x20)
    int32_t           m_log2Children; // +0x38

    // 0x0111ffc0: build a node. `side` selects first/last child, `depth` is the recursion level.
    MoppChainNode* buildNode(MoppChainNode* parent, const int* primList, int side, int depth);
    // 0x011202d0: compile entry point.
    MoppChainNode* compile(void* arg0, MoppInterface* ifaceB, int arg2, MoppInterface* ifaceA, void* source, uint32_t* arena);
};

// The per-primitive record read by the cost helpers (only the fields they touch are named).
struct MoppChainLeaf {
    int32_t m_i00;      // +0
    int32_t m_i04;      // +4
    float   m_f08;      // +8
    float   m_f0c;      // +0xc  (a bound)
    float   m_f10;      // +0x10 (a bound)
    int32_t m_i14;      // +0x14
    float   m_f18;      // +0x18
    float   m_f1c;      // +0x1c
    float   m_f20;      // +0x20
    int32_t m_i24;      // +0x24 (pointer used by costDirect)
    int32_t m_i28;      // +0x28 (compared as an int by costSplitA)
    int32_t m_i2c;      // +0x2c
    int32_t m_i30;      // +0x30
    int32_t m_i34;      // +0x34
    float   m_f38;      // +0x38
};

// Compiler-settings block referenced by the cost helpers (0x20 bytes, vtable 0x014a6128, ctor 0x01120610).
struct hkMoppCompilerSettingsBlock {
    virtual float evalCost(MoppChainLeaf* leaf);   // slot 4 (+0x10)
    virtual void  evalCostPair(MoppChainLeaf* leaf, float* out);   // slot (unknown; not called here)
    uint16_t m_memSize;     // +4
    int16_t  m_refCount;    // +6
    float    m_f08;         // +8
    float    m_f0c;         // +0xc
    float    m_f10;         // +0x10
    float    m_f14;         // +0x14
    float    m_f18;         // +0x18
    float    m_f1c;         // +0x1c

    hkMoppCompilerSettingsBlock* construct(const float* src);  // 0x01120610

    // The cost helpers are __thiscall member functions of the settings block (ecx = the block).
    float costDirect(MoppChainLeaf* leaf);        // 0x01120460
    float costRange(MoppChainLeaf* leaf);         // 0x01120470
    float costSpanA(MoppChainLeaf* leaf);         // 0x011204d0
    float costSpanB(MoppChainLeaf* leaf);         // 0x01120570
    float costSplitA(MoppChainLeaf* leaf);        // 0x01120660
    float costSplitB(MoppChainLeaf* leaf);        // 0x011206c0
    void  costSplitInto(MoppChainLeaf* leaf, float* out);   // 0x01120710
};

// ---- hkWingedEdge ---------------------------------------------------------------------------------------
struct hkWingedEdgeVertex {
    hkVector4 m_w;   // +0
    hkVector4 m_a;   // +0x10
    hkVector4 m_b;   // +0x20
};

// hkWingedEdgeTriangle: 0x50 bytes, normal +0, float m_f10 +0x10, three vertex pointers.
struct hkWingedEdgeTriangle {
    hkVector4 m_normal;              // +0
    float m_f10;                     // +0x10 (a distance)
    hkWingedEdgeVertex* m_v0;        // +0x14
    uint8_t m_pad18[0xc];
    hkWingedEdgeVertex* m_v1;        // +0x24
    uint8_t m_pad28[0xc];
    hkWingedEdgeVertex* m_v2;        // +0x34
    uint8_t m_pad38[0x18];
};

struct hkWingedEdge {
    uint8_t m_pad0[8];               // +0
    int32_t m_i08;                   // +8  (set to 4 by the tetrahedron init)
    int32_t m_i0c;                   // +0xc
    int32_t m_numTriangles;          // +0x10
    uint8_t m_pad14[0xf6c];          // +0x14
    float   m_minDist;               // +0xf80 (smallest per-triangle distance seen)
    hkWingedEdgeTriangle m_triangles[1];   // +0xfc0 (only the first element is addressed directly)

    hkWingedEdgeTriangle* findTriangleOnNearestPlane();        // 0x01120770
    void initializeWithTetrahedron(void* a, void* b, void* c);  // 0x01120850
    void addTetrahedron();                                      // 0x01123580
};

// ---- hkConvexPenetrationUtil ----------------------------------------------------------------------------
struct hkGskOut {
    hkVector4 m_normal;   // +0
    hkVector4 m_point;    // +0x10
    float m_dist;         // +0x20
    float m_half;         // +0x24
};

struct hkRotation;

struct hkConvexPenetrationUtil {
    uint8_t m_pad0[0x40];         // +0
    float m_bestDist;             // +0x40
    float m_f44, m_f48, m_f4c;    // +0x44/+0x48/+0x4c
    float m_eps;                  // +0x50
    uint8_t m_pad54[0xc];         // +0x54
    hkVector4* m_a;               // +0x60 (support points on A)
    hkVector4* m_b;               // +0x64 (support points on B)
    hkVector4* m_w;               // +0x68 (difference vertices)
    int32_t*  m_num;              // +0x6c (live vertex count)

    void  addTetrahedronInput();  // placeholder
    void  addPointToSimplex(const hkWingedEdgeVertex& v);                       // 0x01120a00
    int   tryToExpandPolytope(hkWingedEdge& we, hkWingedEdgeTriangle* tri, hkWingedEdgeVertex* v, int& status);  // 0x01120a80
    void  convertResultToFeature(hkWingedEdge& we, hkWingedEdgeTriangle* tri, hkGskOut& out);  // 0x01120c40
    static void randomVector(int seed, float lo, float hi, hkVector4& out);      // 0x01120eb0
};

// helpers from the wider image used by this slice
void hkVector4_setRotatedInverseDir(hkVector4& out, const hkVector4* dir, const void* rot);   // 0x01081440
void hkCollideTriangleUtil_calcBarycentric(const hkVector4& p, const hkVector4& a, const hkVector4& b, const hkVector4& c, float* out);  // 0x01105630
hkWingedEdgeTriangle* hkWingedEdge_findTriangleNearestOrigin(hkWingedEdge* we, hkWingedEdgeTriangle* tri);   // 0x01123070
int  hkWingedEdge_addVertex(hkWingedEdge* we, hkWingedEdgeTriangle* tri, hkWingedEdgeVertex* v, int* a, int* b);  // 0x01123510
int  eastl_vector_int_DoAssignValues(void* vec, int count, const void* src);   // 0x01123680

// MOPP-compiler helpers outside this slice (declared with the argument counts the caller pushes).
MoppChainNode* hkFun_0111f9e0(MoppChainNode* parent, const int* primList);      // 0x0111f9e0
void  hkFun_0111efb0(MoppChainNode* node);                                       // 0x0111efb0
void  hkFun_0111f4c0(MoppChainNode* node, int* outIdx, float* outDist);          // 0x0111f4c0
void  hkFun_0111faa0(int first, int a, int b, int c);                            // 0x0111faa0
void  hkFun_0111f670(MoppChainNode* node, void* entry, const int* primList, int* a, int b);   // 0x0111f670
void  hkFun_0111f400(const int* primList, MoppChainNode* node);                  // 0x0111f400
void  hkFun_0111fe30(const int* primList, MoppChainNode* node, int depth, int* outA, int* outB);  // 0x0111fe30
void  hkFun_01103830(const float* vals);                                         // 0x01103830

extern const hkVector4 g_hkZeroVector;   // 0x016e42d0
