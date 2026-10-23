// Slice s0111e2c0: Havok 3.1.0 (VC .NET 2003, /vc71 /O2 /MD /Gy /TP) -- the MOPP code writer and the
// MOPP compiler's node/priority-queue helpers. See s0111e2c0.h for the layout/vtable evidence.
//
// Group A: the code writer. It appends bytes to a fixed buffer that is filled from the *end* towards
// the front, so each store lands at  m_buffer[m_capacity - m_position - 1]  and the buffer is doubled
// (and its contents moved to the new buffer's tail) when the position reaches the capacity.
#include "s0111e2c0.h"
#include <string.h>

// ===================================================================================================
// MOPP code writer
// ===================================================================================================

// @ 0x0111eab0  ctor: refcount = 1, install the vtable, allocate the initial buffer.
MoppCodeWriter* MoppCodeWriter::init(int nbytes)
{
    this->m_refCount = 1;
    this->m_vtbl = 0x014a6100u;
    this->m_buffer = (char*)hkMemory::s_instance->allocate(nbytes, HK_MEMORY_CLASS_MOPP);
    this->m_capacity = nbytes;
    this->m_position = 0;
    return this;
}

// @ 0x0111eb20  double the buffer, keeping the already-written bytes at the tail of the new one.
void __declspec(noinline) MoppCodeWriter::growBuffer()
{
    int n = this->m_capacity * 2;
    char* buf = (char*)hkMemory::s_instance->allocate(n, HK_MEMORY_CLASS_MOPP);
    hkString::memCpy(buf + this->m_capacity, this->m_buffer, this->m_capacity);
    this->m_capacity = this->m_capacity * 2;
    hkMemory::s_instance->deallocate(this->m_buffer);
    this->m_buffer = buf;
}

// @ 0x0111eb70  append one byte.
void MoppCodeWriter::putByte(uint8_t v)
{
    this->m_buffer[this->m_capacity - this->m_position - 1] = v;
    if (++this->m_position >= this->m_capacity)
        this->growBuffer();
}

// @ 0x0111eba0  append one byte: the sum of the two values handed in. The values arrive as ints (the
// caller always passes them sign/zero-extended), so the sum is truncated back to a byte for the store.
void MoppCodeWriter::putByteSum(int a, int b)
{
    this->m_buffer[this->m_capacity - this->m_position - 1] = (uint8_t)(b + a);
    if (++this->m_position >= this->m_capacity)
        this->growBuffer();
}

// @ 0x0111ebd0  append two bytes (b first, then a -- the buffer is filled backwards).
void MoppCodeWriter::putBytePair(uint8_t a, uint8_t b)
{
    this->m_buffer[this->m_capacity - this->m_position - 1] = b;
    if (++this->m_position >= this->m_capacity)
        this->growBuffer();
    this->m_buffer[this->m_capacity - this->m_position - 1] = a;
    if (++this->m_position >= this->m_capacity)
        this->growBuffer();
}

// @ 0x0111ec30  append the selector byte after the two signed bytes of v (low byte first).
void MoppCodeWriter::putU16(uint8_t sel, int32_t v)
{
    this->m_buffer[this->m_capacity - this->m_position - 1] = (uint8_t)v;
    if (++this->m_position >= this->m_capacity)
        this->growBuffer();
    this->m_buffer[this->m_capacity - this->m_position - 1] = (uint8_t)(v >> 8);
    if (++this->m_position >= this->m_capacity)
        this->growBuffer();
    this->m_buffer[this->m_capacity - this->m_position - 1] = sel;
    if (++this->m_position >= this->m_capacity)
        this->growBuffer();
}

// @ 0x0111ecc0  append the selector byte after the three signed bytes of v.
void MoppCodeWriter::putU24(uint8_t sel, int32_t v)
{
    this->m_buffer[this->m_capacity - this->m_position - 1] = (uint8_t)v;
    if (++this->m_position >= this->m_capacity)
        this->growBuffer();
    this->m_buffer[this->m_capacity - this->m_position - 1] = (uint8_t)(v >> 8);
    if (++this->m_position >= this->m_capacity)
        this->growBuffer();
    this->m_buffer[this->m_capacity - this->m_position - 1] = (uint8_t)(v >> 16);
    if (++this->m_position >= this->m_capacity)
        this->growBuffer();
    this->m_buffer[this->m_capacity - this->m_position - 1] = sel;
    if (++this->m_position >= this->m_capacity)
        this->growBuffer();
}

// @ 0x0111ed80  append the three signed bytes of v.
void MoppCodeWriter::putS24(int32_t v)
{
    this->m_buffer[this->m_capacity - this->m_position - 1] = (uint8_t)v;
    if (++this->m_position >= this->m_capacity)
        this->growBuffer();
    this->m_buffer[this->m_capacity - this->m_position - 1] = (uint8_t)(v >> 8);
    if (++this->m_position >= this->m_capacity)
        this->growBuffer();
    this->m_buffer[this->m_capacity - this->m_position - 1] = (uint8_t)(v >> 16);
    if (++this->m_position >= this->m_capacity)
        this->growBuffer();
}

// @ 0x0111ee10  append the selector byte after the four *unsigned* bytes of v.
void MoppCodeWriter::putU32(uint8_t sel, uint32_t v)
{
    this->m_buffer[this->m_capacity - this->m_position - 1] = (uint8_t)v;
    if (++this->m_position >= this->m_capacity)
        this->growBuffer();
    this->m_buffer[this->m_capacity - this->m_position - 1] = (uint8_t)(v >> 8);
    if (++this->m_position >= this->m_capacity)
        this->growBuffer();
    this->m_buffer[this->m_capacity - this->m_position - 1] = (uint8_t)(v >> 16);
    if (++this->m_position >= this->m_capacity)
        this->growBuffer();
    this->m_buffer[this->m_capacity - this->m_position - 1] = (uint8_t)(v >> 24);
    if (++this->m_position >= this->m_capacity)
        this->growBuffer();
    this->m_buffer[this->m_capacity - this->m_position - 1] = sel;
    if (++this->m_position >= this->m_capacity)
        this->growBuffer();
}

// @ 0x0111eef0  build the hkMoppCode for everything written so far: a fresh code object, its data array
// reserved to the exact size, then the buffer copied into it (the caller's buffer is released and the
// writer is reused from the start).
hkMoppCode* MoppCodeWriter::getCode()
{
    int used = this->m_position;
    hkMoppCode* code = (hkMoppCode*)hkMemory::s_instance->allocateChunk(sizeof(hkMoppCode), HK_MEMORY_CLASS_MOPP);
    code->m_memSizeAndFlags = (uint16_t)sizeof(hkMoppCode);
    code->m_refCount = 1;
    code->m_vtbl = 0x014a59b4u;
    // The array and the 16-byte code-info block are both initialised through pointers taken before
    // the four (or three) stores. Spelling the info stores as code->m_infoNN = 0, or binding the
    // array once and using it for everything, makes the compiler hoist the zero register and the
    // array address above the three header stores above and reorder 0x80000000 ahead of them; this
    // spelling reproduces the original instruction order.
    hkArray<uint8_t>& arr = code->m_data;
    arr.m_data = 0;
    arr.m_size = 0;
    arr.m_capacityAndFlags = (int)0x80000000;
    uint32_t* info = &code->m_info10;
    info[3] = 0;
    info[2] = 0;
    info[1] = 0;
    info[0] = 0;
    hkArray<uint8_t>& data = code->m_data;
    if ((data.m_capacityAndFlags & 0x3fffffff) < used)
        hkArrayUtil::_reserveExactly(&data, used, 1);
    if ((data.m_capacityAndFlags & 0x3fffffff) < used)
    {
        int newCapacity = (data.m_capacityAndFlags & 0x3fffffff) * 2;
        if (used >= newCapacity)
            newCapacity = used;
        hkArrayUtil::_reserveExactly(&data, newCapacity, 1);
    }
    data.m_size = used;
    hkString::memCpy(data.m_data, (this->m_buffer - this->m_position) + this->m_capacity, used);
    hkMemory::s_instance->deallocate(this->m_buffer);
    this->m_capacity = used;
    this->m_position = 0;
    return code;
}

// ===================================================================================================
// MOPP node reset
// ===================================================================================================

// @ 0x0111efb0  clear the node's 32-dword scratch block (+0x38..+0xb8).
void MoppChainNode::reset()
{
    for (int i = 0; i < 32; ++i)
        this->m_scratch[i] = 0;
}

// ===================================================================================================
// The compiler's priority queue (a max-heap of nodes keyed by the float at node+0xc)
// ===================================================================================================

// @ 0x0111f020  push elem onto the heap: walk the hole from the last slot towards the root, moving a
// parent down while its key is smaller than elem's. The compiler unrolls the walk four deep.
void MoppPriorityQueue::insert(MoppChainNode* elem)
{
    float key = elem->m_key;
    int i = this->m_count - 1;
    while (i >= 0)
    {
        MoppChainNode* p = this->m_heap[i];
        if (p == 0 || !(p->m_key < key))
            break;
        this->m_heap[i + 1] = p;
        --i;
    }
    this->m_heap[i + 1] = elem;
    ++this->m_count;
}

// @ 0x0111f150  pop every node whose key is below threshold off the top of the heap (the popped node
// is parked in m_out and its slot cleared); the walk from the last slot towards the root is unrolled
// four deep exactly like insert()'s.
void MoppPriorityQueue::popAbove(float threshold)
{
    int i = this->m_count - 1;
    while (i >= 0)
    {
        if (this->m_heap[i] == 0 || !(this->m_heap[i]->m_key < threshold))
            break;
        this->m_out = this->m_heap[i];
        this->m_heap[i] = 0;
        --this->m_count;
        --i;
    }
}

// ===================================================================================================
// The MOPP compiler's recursive tree walk
// ===================================================================================================
namespace hkMath { int hkFloatToInt(float x); }   // 0x0120ad30

// A stand-in vtable shape for the compiler so the slot-5 call in 0x0111e880 dispatches through
// this->m_vtbl exactly as the binary does (call dword ptr [vtable+0x14]).
struct MoppCompilerVtable
{
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14(void* a, void* b);
};

// @ 0x0111e2c0  build the sub-tree that covers `node` (a child of the chunk `chunk` inside `parent`).
// For every node whose scratch flag (+0x38) is clear: if it is already a leaf (+4 != 0) just snap its
// bounds and hand it to 0x0111d7f0; otherwise quantise a fresh child chunk from `chunk` + the node's
// box, recurse into it, then update the node's per-axis min/max from the child and merge the flags.
void MoppCompiler::buildSubTree(MoppChainNode* node, MoppChunk* parent, MoppChunk* chunk)
{
    if (*(uint8_t*)((char*)node + 0x38) != 0)
        return;

    if (node->m_b04 != 0)
    {
        chunk->snapBounds();                 // 0x0111ce00 (ecx = chunk)
        this->func0111d7f0(node, chunk);     // 0x0111d7f0
        return;
    }

    char out14[20];
    if (*(uint8_t*)((char*)node + 0x3c) == 1)
        this->func0111d450(parent, chunk, out14);      // 0x0111d450

    chunk->snapBounds();
    int n = this->func0111da50(node->m_iB8);           // 0x0111da50
    int idx;                                           // local_94 (reused as the loop index)
    MoppChainNode* last;                               // local_84
    this->func0111db80(node, chunk, &idx, (int*)&last);  // 0x0111db80
    last = node->m_last;

    MoppChainNode* heads[2];
    heads[0] = node->m_last;                           // +0xf0
    heads[1] = node->m_first;                          // +0xec

    for (int i = 0; i < 3; ++i)
    {
        hkMath::hkFloatToInt(this->m_xform[3] * this->m_xform[5]);
        MCW(node, 0x44 + 4 * i) = 0;
        MCW(node, 0x50 + 4 * i) = 0x7fffffff;
    }

    for (idx = 0; idx < 2; ++idx)
    {
        MoppChainNode* cn = (MoppChainNode*)heads[idx];
        if (cn == 0)
            continue;

        // ---- MoppChunk::initFromParent(chunk, cn, this->m_xform), inlined here ----
        MoppChunk child;
        memcpy(&child, chunk, 0x48);   // rep movsd, 0x12 dwords
        MCW(&child, 0x38) = MCW(cn, 0x28) - MCW(cn, 0x24);
        MCW(&child, 0x3c) = MCW(cn, 0x2c);
        for (int k = 0; k < MCW(cn, 0x2c); ++k)
        {
            MCW(&child, 0x40 + 4 * k) = MCW(cn, 0x30 + 4 * k);
            MCW(&child, 0x44 + 4 * k) = MCW(cn, 0x34 + 4 * k) - MCW(cn, 0x30 + 4 * k);
        }
        child.setFromFloatBox(cn, this->m_xform);
        MCW(&child, 0x00) = chunk->m_w[0] + 1;
        ((uint8_t*)&child)[4] = 0;
        child.computeShift();
        // --------------------------------------------------------------------------

        this->buildSubTree(cn, chunk, &child);

        if (cn == last)
        {
            if (n < 3)
                MCW(cn, 0x44 + 4 * n) = 0;
        }
        else if (n < 3)
        {
            MCW(cn, 0x50 + 4 * n) = 0x7fffffff;
        }

        int* pchild = (int*)((char*)cn + 0x44);
        int* pnodemax = (int*)((char*)node + 0x44);
        int* pnodemin = (int*)((char*)node + 0x50);
        int* plo = (int*)((char*)chunk + 0x10);
        int* phi = (int*)((char*)chunk + 0x54);
        for (int i = 0; i < 3; ++i)
        {
            int8_t t = ((int8_t*)((char*)cn + 0x40))[i];
            if (t == 1)
            {
                if (pchild[0] <= phi[-3] && phi[0] <= pchild[3])
                {
                    int8_t v = ((int8_t*)((char*)node + 0x40))[i];
                    ((int8_t*)((char*)node + 0x40))[i] = (v > 0) ? v : 1;
                    ((int8_t*)((char*)cn + 0x40))[i] = 0;
                }
            }
            else if (t == 2 && pchild[0] <= plo[-1] && plo[0] <= pchild[3])
            {
                ((int8_t*)((char*)node + 0x40))[i] = 2;
                ((int8_t*)((char*)cn + 0x40))[i] = 0;
            }
            if (((int8_t*)((char*)cn + 0x40))[i] == 0)
            {
                int a = pnodemax[0];
                int b = pchild[0];
                pnodemax[0] = (b < a) ? a : b;
                int c = pnodemin[0];
                int d = pchild[3];
                pnodemin[0] = (c < d) ? c : d;
            }
            pchild += 1;
            pnodemax += 1;
            pnodemin += 1;
            phi += 1;
            plo += 2;
        }
    }
}

// @ 0x0111e570  assemble one node. Returns the number of code bytes emitted for the node, or -1 when
// the node could not be emitted. Emits a leaf directly when the node is a leaf or the chunk's depth
// budget is exhausted, otherwise recurses into the two children.
int MoppCompiler::assembleNode(MoppChainNode* node, MoppChunk* parent, MoppChunk* chunk)
{
    if (*(uint8_t*)((char*)node + 0x38) != 0)
        return 3;

    if (chunk->m_w[0] > this->m_i14
        || (uint8_t)chunk->m_w[1] != 0
        || (chunk->m_w[0] % this->m_i60) != 0)
    {
        if (*(uint8_t*)((char*)node + 4) != 0)
        {
            this->func0111cea0(node);
            if (MCW(node, 8) < 0x16 || chunk->m_w[0] > this->m_i14)
            {
                ++this->m_i24;
                int base = MCW(this->m_writer, 0x0c);
                this->func0111d190(node, parent, chunk);         // 0x0111d190
                this->func0111d060(node, chunk);                 // 0x0111d060
                MCW(node, 0x5c) = MCW(this->m_writer, 0x0c);
                int after = MCW(this->m_writer, 0x0c);
                *(uint8_t*)((char*)node + 0x38) = 1;
                return after - base;
            }
        }
        else
        {
            char out64[20];
            out64[0] = 0;
            if (*(uint8_t*)((char*)node + 0x3c) == 1)
                this->func0111d450(parent, chunk, out64);      // 0x0111d450
            this->func0111cf00(node, parent, chunk);           // 0x0111cf00
            int n = this->func0111da50(node->m_iB8);           // 0x0111da50
            int q1, q0;
            this->func0111db80(node, chunk, &q1, &q0);         // 0x0111db80

            int a = -1;                                        // local_7c
            int b = -1;                                        // local_84
            MoppChunk48 child;                                 // local_50 (0x48 bytes in the original frame)

            MoppChainNode* cn = node->m_last;
            if (cn != 0)
            {
                ((MoppChunk*)&child)->initFromParent(chunk, cn, this->m_xform);      // 0x0111d3c0
                b = this->assembleNode(cn, chunk, (MoppChunk*)&child);
                if (b >= 0)
                {
                    a = MCW(cn, 0x5c);
                    this->func0111ce50(cn);                          // 0x0111ce50
                }
            }

            cn = node->m_first;
            if (cn != 0)
            {
                MoppChainNode* cn0 = cn;
                ((MoppChunk*)&child)->initFromParent(chunk, cn0, this->m_xform);
                int e = this->assembleNode(cn0, chunk, (MoppChunk*)&child);
                if (e >= 0)
                {
                    int cnval = MCW(cn0, 0x5c);
                    this->func0111ce50(cn0);
                    if (b >= 0 && this->func0111ced0(node, chunk))   // 0x0111ced0 (hkBool)
                    {
                        this->func0111cea0(node);                    // 0x0111cea0
                        ++this->m_i24;
                        int base = MCW(this->m_writer, 0x0c);
                        this->func0111d8e0(q0, q1, n, cnval, a);     // 0x0111d8e0
                        int v = MCW(chunk, 0x34) - MCW(parent, 0x34);
                        if (v != 0)
                            this->func0111d020(v);                   // 0x0111d020
                        this->func0111d140(node, parent, chunk);     // 0x0111d140
                        this->func0111d060(node, chunk);             // 0x0111d060
                        if (out64[0] != 0)
                            this->func0111cfe0(out64);               // 0x0111cfe0
                        MCW(node, 0x5c) = MCW(this->m_writer, 0x0c);
                        *(uint8_t*)((char*)node + 0x38) = 1;
                        return (MCW(this->m_writer, 0x0c) - base) + e + b;
                    }
                }
            }
        }
        return -1;
    }

    // Depth budget not exhausted: bump the "already handled" byte and re-run this node against a copy
    // of the chunk while the depth budget lasts and the node stays unmarked.
    (*(uint8_t*)((char*)chunk + 4)) = 1;
    int saved = this->m_i14;
    char c = *(uint8_t*)((char*)node + 0x38);
    int result = -1;
    while (c == 0)
    {
        int base = MCW(this->m_writer, 0x0c);
        MoppChunk48 tmp;
        memcpy(&tmp, chunk, 0x48);   // rep movsd, 0x12 dwords
        result = this->assembleNode(node, parent, (MoppChunk*)&tmp);
        if (this->m_i24 > this->m_i20)
            break;
        if (base == MCW(this->m_writer, 0x0c))
        {
            if (this->m_i14 < 0)
                break;
            this->m_i14 -= this->m_i60;
        }
        c = *(uint8_t*)((char*)node + 0x38);
    }
    this->m_i14 = saved;
    (*(uint8_t*)((char*)chunk + 4)) = 0;
    return result;
}

// @ 0x0111e880  the compiler's virtual build entry (vtable 0x014a60e8 slot 4). Stores the context and
// budget, lets the subclass initialise (slot 5), then drives the whole build: quantise the root box,
// assemble the root node, then the two half-boxes, and finally the top node.
void MoppCompiler::build(void* source, MoppChunk* parent, MoppChunk* root)
{
    this->m_p0c = parent;
    this->m_i20 = (int)(intptr_t)root;
    this->m_i24 = 0;
    ((MoppCompilerVtable*)this)->v14(source, this->m_xform);           // 0x0111de80
    if (source == 0)
        return;

    this->m_i14 = 0;
    uint32_t bits = MCW(source, 0x28);
    if (bits != 0)
    {
        int c = 0;
        while (bits != 0) { bits >>= 1; ++c; }
        this->m_i14 = c;
    }
    this->m_i18 = this->m_i14 >> 1;
    this->m_i14 = (this->m_i14 / this->m_i60 + 2) * this->m_i60 - 1;

    MoppChunk48 boxA;               // the root box (0x48 bytes in the original frame)
    MoppChunk   boxB;               // the second half-box
    MoppChunk   boxC;               // the working box copied between the two
    MoppChunk*  pa = (MoppChunk*)&boxA;

    pa->setFromFloatBox((MoppChainNode*)source, this->m_xform);
    MCW(&boxA, 0x24) = 0x10;
    MCW(&boxA, 0x30) = 0;
    MCW(&boxA, 0x2c) = 0;
    MCW(&boxA, 0x28) = 0;
    MCW(&boxA, 0x00) = -1;
    MCW(&boxA, 0x34) = 0;
    *(uint8_t*)((char*)&boxA + 4) = 0;
    pa->copyFrom(source);
    pa->computeShift();

    // boxC := boxA, prepared as a child of boxA (the inlined MoppChunk::initFromParent).
    memcpy(&boxC, &boxA, 0x48);   // rep movsd, 0x12 dwords
    boxC.copyFrom(source);
    boxC.setFromFloatBox((MoppChainNode*)source, this->m_xform);
    MCW(&boxC, 0x00) = MCW(&boxA, 0x00) + 1;
    *(uint8_t*)((char*)&boxC + 4) = 0;
    boxC.computeShift();
    this->func0111d560(source, &boxA, &boxC);                       // 0x0111d560

    // boxC: re-initialised as a root box.
    boxC.setFromFloatBox((MoppChainNode*)source, this->m_xform);
    MCW(&boxC, 0x24) = 0x10;
    MCW(&boxC, 0x30) = 0;
    MCW(&boxC, 0x2c) = 0;
    MCW(&boxC, 0x28) = 0;
    MCW(&boxC, 0x00) = -1;
    MCW(&boxC, 0x34) = 0;
    *(uint8_t*)((char*)&boxC + 4) = 0;
    boxC.copyFrom(source);
    boxC.computeShift();

    // boxB := boxC, prepared as a child of boxC.
    memcpy(&boxB, &boxC, 0x48);   // rep movsd, 0x12 dwords
    boxB.copyFrom(source);
    boxB.setFromFloatBox((MoppChainNode*)source, this->m_xform);
    MCW(&boxB, 0x00) = MCW(&boxC, 0x00) + 1;
    *(uint8_t*)((char*)&boxB + 4) = 0;
    boxB.computeShift();
    this->buildSubTree((MoppChainNode*)source, &boxC, &boxB);       // 0x0111e2c0

    // boxC := boxA, prepared as a child of boxA.
    memcpy(&boxC, &boxA, 0x48);   // rep movsd, 0x12 dwords
    boxC.copyFrom(source);
    boxC.setFromFloatBox((MoppChainNode*)source, this->m_xform);
    MCW(&boxC, 0x00) = MCW(&boxA, 0x00) + 1;
    *(uint8_t*)((char*)&boxC + 4) = 0;
    boxC.computeShift();
    this->assembleNode((MoppChainNode*)source, (MoppChunk*)&boxA, &boxC);  // 0x0111e570
}

