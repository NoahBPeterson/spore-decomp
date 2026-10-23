#pragma once
// Havok 3.1.0 slice s0111e2c0 -- the MOPP "code writer" (a byte buffer filled *backwards* by the MOPP
// compiler), the hkMoppCode builder, the MOPP node reset, and the compiler's priority-queue helpers.
//
// The whole slice is code EA linked out of a Havok 3.1.0 static library built with VC .NET 2003, so it
// is compiled with /vc71 (see tools/matching/cl71.sh). None of the sixteen VAs has a symbol in
// symbols/havok_names.txt and none of them is called directly from anywhere in .text (they are only
// reachable through vtables), so every name below is coined from the shapes the code computes; the
// struct layouts are recovered from the member offsets the binary touches.
//
// VTABLE EVIDENCE (from .rdata):
//   0x014a60e8 = the MOPP compiler/builder class (slices/s0111ffc0 calls it MoppCompiler):
//                {0111eaf0 (deleting dtor), 0x0052e650 (purecall), 0111e2a0 (getSizeInBytes -> 0xd),
//                 0111e2b0 (getClass -> 0x016e5ad0), 0111e880, 0111de80}
//   0x014a6100 = a second, larger class in the same hierarchy (0111e880 calls its own slot 5):
//                {0111eaf0, 0x0052e650, 0111fc00, 0x0052e650, 0111fa60, 0111fa90, 011202d0}
//                Its ctor (0x0111eab0) takes a byte count, allocates that buffer at +0x10 and keeps
//                +0x8 = capacity, +0xc = position. 0x0111fa60/0x0111fa90 manage the node free lists.
//   0x014a59b4 = hkMoppCode (work/havok31_classes.json: 0x30 bytes, parent hkReferencedObject,
//                hkMoppCodeCodeInfo at +0x10, hkArray<hkUint8> data at +0x20).
#pragma once
#include "../s0107e670/hk31_base.h"
#include <stddef.h>

// HK_MEMORY_CLASS_MOPP (the 0x25 literal every allocation in this slice passes).
enum { HK_MEMORY_CLASS_MOPP = 0x25 };

struct hkMoppCode;

// ---------------------------------------------------------------------------------------------------
// The code writer: appends bytes to a buffer that is filled from the end towards the front, growing it
// when it wraps. The vtable is 0x014a6100; the vptr is a plain field here (the vtable data is not part
// of the byte-exact comparison, only the functions are).
// ---------------------------------------------------------------------------------------------------
struct MoppCodeWriter
{
    uint32_t m_vtbl;              // +0x00  0x014a6100
    uint16_t m_memSizeAndFlags;   // +0x04
    uint16_t m_refCount;          // +0x06  set to 1 by the ctor
    int32_t  m_capacity;          // +0x08  bytes currently allocated
    int32_t  m_position;          // +0x0c  bytes written so far
    char*    m_buffer;            // +0x10

    MoppCodeWriter* init(int nbytes);           // 0x0111eab0
    // 0x0111eb20 is called (not inlined) from every writer below, so it must stay out of line.
    void __declspec(noinline) growBuffer();
    void putByte(uint8_t v);                    // 0x0111eb70
    void putByteSum(int a, int b);              // 0x0111eba0
    void putBytePair(uint8_t a, uint8_t b);     // 0x0111ebd0
    void putU16(uint8_t sel, int32_t v);        // 0x0111ec30
    void putU24(uint8_t sel, int32_t v);        // 0x0111ecc0
    void putS24(int32_t v);                     // 0x0111ed80
    void putU32(uint8_t sel, uint32_t v);       // 0x0111ee10
    hkMoppCode* getCode();                      // 0x0111eef0
};

// ---------------------------------------------------------------------------------------------------
// hkMoppCode (0x30 bytes). Only the fields the builder touches are named. hkMoppCodeCodeInfo (a
// 16-byte block at +0x10) is kept as four dwords: the builder zeroes it with integer stores.
// ---------------------------------------------------------------------------------------------------
struct hkMoppCode
{
    uint32_t         m_vtbl;             // +0x00  0x014a59b4
    uint16_t         m_memSizeAndFlags;  // +0x04  0x30
    uint16_t         m_refCount;         // +0x06  1
    uint32_t         m_u08;              // +0x08
    uint32_t         m_u0c;              // +0x0c
    uint32_t         m_info10;           // +0x10  hkMoppCodeCodeInfo (4 dwords)
    uint32_t         m_info14;           // +0x14
    uint32_t         m_info18;           // +0x18
    uint32_t         m_info1c;           // +0x1c
    hkArray<uint8_t> m_data;             // +0x20
    uint32_t         m_pad2c;            // +0x2c
};

// ---------------------------------------------------------------------------------------------------
// A MOPP tree node (0xf8 bytes). slices/s0111ffc0 models the whole thing; here only the 32-dword
// scratch block that 0x0111efb0 clears (+0x38..+0xb8) matters. The binary clears it as 32 consecutive
// scalar stores (a fully unrolled loop), not as a memset/rep stosd. The fields written by the other
// functions of this slice live inside that same block and are reached through the array (see the
// accessors below).
// ---------------------------------------------------------------------------------------------------
struct MoppChainNode
{
    MoppChainNode* m_parent;      // +0x00
    uint8_t  m_b04;               // +0x04
    uint8_t  m_pad05[7];          // +0x05..+0x0c
    float    m_key;               // +0x0c  the priority key (s0111ffc0 reads this dword as m_copies[0])
    uint32_t m_copies[5];         // +0x10..+0x24  (five more dwords copied from the parent)
    int32_t  m_i24;               // +0x24
    int32_t  m_i28;               // +0x28
    int32_t  m_nAxes;             // +0x2c  number of cell-range entries in the arrays below
    int32_t  m_pad30[2];          // +0x30..+0x38  (start of the cell lo/hi arrays, see the builder)

    uint32_t m_scratch[32];       // +0x38..+0xb8  (0x38 is dword 0, 0xb4 is dword 31)

    uint32_t m_iB8;               // +0xb8
    float    m_fbc;               // +0xbc
    uint32_t m_u_c0;              // +0xc0
    float    m_fc4;               // +0xc4
    uint8_t  m_padc8[0x24];       // +0xc8..+0xec
    MoppChainNode* m_first;       // +0xec
    MoppChainNode* m_last;        // +0xf0
    int32_t  m_primCount;         // +0xf4

    void reset();                 // 0x0111efb0
};

// ---------------------------------------------------------------------------------------------------
// The MOPP compiler/builder object (vtable 0x014a60e8). Its slot 4 (0x0111e880) drives a whole build;
// 0x0111e2c0 (a recursive sub-node builder) and 0x0111e570 (a per-node assembler) are its helpers. The
// field offsets are the ones the code touches: +0x10 is the code writer (its byte position is the
// writer's m_position at +0xc), +0x30 is the 4x3 float transform handed to MoppChunk::setFromFloatBox,
// +0x60 is the maximum number of primitives a leaf chunk may cover.
// ---------------------------------------------------------------------------------------------------
struct MoppChunk;

struct MoppCompiler
{
    uint32_t        m_vtbl;       // +0x00  0x014a60e8
    uint32_t        m_pad04;      // +0x04
    uint32_t        m_pad08;      // +0x08
    void*           m_p0c;        // +0x0c
    MoppCodeWriter* m_writer;     // +0x10
    int32_t         m_i14;        // +0x14
    int32_t         m_i18;        // +0x18
    uint32_t        m_pad1c;      // +0x1c
    int32_t         m_i20;        // +0x20
    int32_t         m_i24;        // +0x24
    uint32_t        m_pad28[2];   // +0x28
    float           m_xform[12];  // +0x30  (4x3 transform: [3] and [5] are the cell scales)
    int32_t         m_i60;        // +0x60

    // 0x0111e2c0: recursively build the sub-tree that covers `node` inside `parent`.
    void buildSubTree(MoppChainNode* node, MoppChunk* parent, MoppChunk* chunk);
    // 0x0111e880: the compiler's virtual build entry (vtable slot 4).
    void build(void* source, MoppChunk* parent, MoppChunk* root);
    // 0x0111e570: assemble one node (returns the number of bytes emitted, or -1).
    int  assembleNode(MoppChainNode* node, MoppChunk* parent, MoppChunk* chunk);

    // Out-of-slice helpers reached through this object (ecx == this). Declared with the shapes the
    // callers use so the generated call sequences line up; none is defined in this translation unit.
    void func0111d7f0(MoppChainNode* node, MoppChunk* chunk);              // 0x0111d7f0
    void func0111d450(MoppChunk* a, void* b, void* out);                   // 0x0111d450
    int  func0111da50(int a);                                              // 0x0111da50
    void func0111db80(MoppChainNode* node, MoppChunk* chunk, int* a, int* b);  // 0x0111db80
    void func0111cea0(MoppChainNode* node);                                // 0x0111cea0
    void func0111ce50(MoppChainNode* node);                                // 0x0111ce50
    void func0111cf00(MoppChainNode* node, MoppChunk* a, MoppChunk* b);    // 0x0111cf00
    void func0111d190(MoppChainNode* node, MoppChunk* a, MoppChunk* b);    // 0x0111d190
    void func0111d140(MoppChainNode* node, MoppChunk* a, MoppChunk* b);    // 0x0111d140
    void func0111d060(MoppChainNode* node, MoppChunk* b);                  // 0x0111d060
    void func0111d020(int v);                                              // 0x0111d020
    void func0111cfe0(void* p);                                            // 0x0111cfe0
    void func0111d8e0(int a, int b, int c, int d, int e);                  // 0x0111d8e0
    hkBool func0111ced0(const void* a, const void* b);                     // 0x0111ced0
    void func0111d560(void* a, void* b, void* c);                          // 0x0111d560
};

// ---------------------------------------------------------------------------------------------------
// A MOPP box/chunk: the quantised cell ranges the assembler works with (layout recovered from the
// helpers 0x0111cdb0/0x0111ce00/0x0111d2b0/0x0111d340 -- see slices/s0111c7f0). Only the dwords the
// three functions of this slice touch are named.
// ---------------------------------------------------------------------------------------------------
struct MoppChunk
{
    int32_t m_w[0x18];   // +0x00..+0x60  raw dwords; the layout is only partly recovered
                         //   +0x00 depth/counter, +0x04 byte flag, +0x0c/+0x10 per-axis cell
                         //   lo/hi (stride 8), +0x24 shift, +0x38/+0x3c and +0x40+4i/+0x44+4i and
                         //   +0x48+4i/+0x54+4i the snapped ranges.

    // Out-of-slice methods (ecx == this). Not defined here.
    void snapBounds();                                             // 0x0111ce00
    void setFromFloatBox(MoppChainNode* node, const float* xform);  // 0x0111d2b0
    void computeShift();                                           // 0x0111d340
    void copyFrom(const void* p);                                  // 0x0111cdb0
    MoppChunk* initFromParent(const MoppChunk* parent, MoppChainNode* box, const float* xform);  // 0x0111d3c0
};
// The root box local in MoppCompiler::build is only 0x48 bytes: the build entry fills the first 0x48
// bytes of a box and never touches the rest, and the frame it reserves for it is exactly 0x48. Using a
// 0x48-byte local here (cast to MoppChunk* for the shared methods) reproduces the original frame layout.
struct MoppChunk48
{
    int32_t m_w[0x12];   // +0x00..+0x48
};

#define MCW(p, off) (*(int32_t*)((char*)(p) + (off)))

// ---------------------------------------------------------------------------------------------------
// The compiler's priority queue: an array of node pointers kept as a max-heap ordered by the float key
// at node+0xc (insert bubbles the new node up; popAbove drains the nodes whose key is below a bound).
// ---------------------------------------------------------------------------------------------------
struct MoppChainNode;

struct MoppPriorityQueue
{
    int32_t          m_count;      // +0x00  number of live entries
    int32_t          m_pad04;      // +0x04
    MoppChainNode**  m_heap;       // +0x08  the growable entry array
    MoppChainNode*   m_out;        // +0x0c  the node most recently popped

    void insert(MoppChainNode* elem);      // 0x0111f020
    void popAbove(float threshold);        // 0x0111f150
};
