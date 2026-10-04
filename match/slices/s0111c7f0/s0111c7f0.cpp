// Havok 3.1.0: hkGeomHull::initializeWithTriangle, hkDefaultToiResourceMgr, and a block of the MOPP code
// assembler helpers (0x0111C7F0..0x0111D553). Equivalent portable source; x87 semantics noted per function.
//
// NAMING NOTE: the MOPP-assembler functions have no symbols in symbols/havok_names.txt. Their names below
// (MoppAssembler::*, MoppCodeBuffer::*) are Claude-coined from the opcode values they emit (JUMP8..32 = 5..8,
// TERM_REOFFSET8/16/32 = 9..11, TERM4..32 = 0x30..0x53, DOUBLE_CUT = 0x26..0x2b, PROPERTY = 0x60..0x6b) and
// are marked "(name guessed)". Their argument structures are accessed through raw 32-bit offsets (at<T>()).
#include "../s010eb310/hk31_math.h"

// ---- helpers ------------------------------------------------------------------------------------------------
// Typed view at a raw byte offset of a structure whose layout is not recovered (offsets are the 32-bit ones).
template <class T> static inline T& at(void* base, size_t off) { return *(T*)((char*)base + off); }
template <class T> static inline const T& at(const void* base, size_t off) { return *(const T*)((const char*)base + off); }

// ---- hkGeomHull -----------------------------------------------------------------------------------------------
// Half-edge hull. Each edge: origin vertex, twin edge, next edge in the face (+ a padding word).
struct hkGeomEdge
{
	uint16_t m_vertex;
	uint16_t m_twin;
	uint16_t m_next;
	uint16_t m_pad;      // never written by the code in this slice (stack garbage in the binary); 0 here
};

struct hkGeomHull
{
	const hkVector4* m_vertices;       // +0
	hkArray<hkGeomEdge> m_edges;   // +4 (data), +8 (size), +0xc (capacity)

	void initializeWithLine(int a, int b);                 // 0x0111C740 (name guessed: builds the 2-edge degenerate hull)
	void initializeWithTriangle(int a, int b, int c);      // 0x0111C7F0
};

static inline hkGeomEdge makeEdge(int vertex, int twin, int next)
{
	hkGeomEdge e;
	e.m_vertex = (uint16_t)vertex;
	e.m_twin = (uint16_t)twin;
	e.m_next = (uint16_t)next;
	e.m_pad = 0;
	return e;
}

// @ 0x0111c7f0
void hkGeomHull::initializeWithTriangle(int a, int b, int c)
{
	m_edges.m_size = 0;
	const hkVector4& pa = m_vertices[a];
	const hkVector4& pb = m_vertices[b];
	const hkVector4& pc = m_vertices[c];

	// X87-PRECISION: x/z/w differences of (b-a), z/w of (c-b) and (a-c).z stay on the x87 stack unstored;
	// y differences and the (c-b), (a-c) x/y/z components are stored to float locals.
	hkX87Real bax = (hkX87Real)pb.x - pa.x;
	float bay = pb.y - pa.y;
	hkX87Real baz = (hkX87Real)pb.z - pa.z;
	hkX87Real baw = (hkX87Real)pb.w - pa.w;
	// 4D squared lengths (w is included) accumulated as ((w*w + x*x) + y*y) + z*z, stored as floats.
	float l10 = (float)(((baw * baw + bax * bax) + (hkX87Real)bay * bay) + baz * baz);   // |b-a|^2 [esp+0x10]

	float cbx = pc.x - pb.x;
	float cby = pc.y - pb.y;
	float cbz = pc.z - pb.z;
	hkX87Real cbw = (hkX87Real)pc.w - pb.w;
	float cbx2 = cbx * cbx;        // [esp+0x38]
	float cby2 = cby * cby;        // [esp+0x40]
	float cbz2 = cbz * cbz;        // [esp+0x48]
	float l18 = (float)(((cbw * cbw + cbx2) + cby2) + cbz2);   // |c-b|^2 [esp+0x18]

	float acx = pa.x - pc.x;
	float acy = pa.y - pc.y;
	float acz = pa.z - pc.z;
	float acw = pa.w - pc.w;
	float l20 = (float)((((hkX87Real)acw * acw + (hkX87Real)acz * acz) + (hkX87Real)acy * acy) + (hkX87Real)acx * acx);   // |a-c|^2 [esp+0x20]

	// Unit directions of b-a and c-b (3D only). Zero length gives a zero vector.
	// X87-PRECISION: the 3D squared length and the reciprocal square root stay on the x87 stack (inline fsqrt).
	hkX87Real len2a = (bax * bax + (hkX87Real)bay * bay) + baz * baz;
	hkX87Real inva = (len2a == 0.0) ? 0.0 : 1.0 / sqrt(len2a);
	float ux = (float)(bax * inva);
	float uy = (float)((hkX87Real)bay * inva);
	float uz = (float)(baz * inva);

	hkX87Real len2c = ((hkX87Real)cbx2 + cby2) + cbz2;
	hkX87Real invc = (len2c == 0.0) ? 0.0 : 1.0 / sqrt(len2c);
	hkX87Real vx = (cbx * invc) - ux;                      // first product stays on the x87 stack
	float vy0 = (float)((hkX87Real)cby * invc);             // fstp [esp+0x54]
	float vz0 = (float)((hkX87Real)cbz * invc);             // fstp [esp+0x58]
	hkX87Real vy = (hkX87Real)vy0 - uy;
	hkX87Real vz = (hkX87Real)vz0 - uz;
	hkX87Real vlen2 = (vz * vz + vy * vy) + vx * vx;

	// 1e-6f (0x358637bd): fcomp / test ah,5 / jp: the edges are built unless the compare is an ordered "less".
	if (!(vlen2 < 9.99999997e-07f))
	{
		m_edges.pushBack(makeEdge(a, 1, 2));
		m_edges.pushBack(makeEdge(b, 0, 5));
		m_edges.pushBack(makeEdge(b, 3, 4));
		m_edges.pushBack(makeEdge(c, 2, 1));
		m_edges.pushBack(makeEdge(c, 5, 0));
		m_edges.pushBack(makeEdge(a, 4, 3));
	}
	else
	{
		// Degenerate (collinear) triangle: keep only the longest edge as a line hull.
		float m = (l18 > l20) ? l18 : l20;
		if (m < l10)
			m = l10;
		if (l10 == m) { initializeWithLine(a, b); return; }
		if (l18 == m) { initializeWithLine(b, c); return; }
		if (l20 == m) { initializeWithLine(c, a); return; }
	}
}

// ---- hkDefaultToiResourceMgr -------------------------------------------------------------------------------------
struct hkToiEvent;
struct hkToiResources
{
	int m_i00;            // 2
	int m_i04;            // 1000
	int m_i08;            // 1000
	int m_i0c;            // 1000
	int m_i10;            // 3
	int m_i14;            // 4
	char* m_stackBuffer;  // +0x18 (32-bit offset)
	int m_stackBytes;     // +0x1c
};

class hkToiResourceMgr : public hkReferencedObject
{
public:
	virtual hkResult beginToiAndSetupResources(const hkToiEvent& event, const hkArray<hkToiEvent>& events, hkToiResources& resources) = 0;
	virtual void endToiAndFreeResources(const hkToiEvent& event, const hkArray<hkToiEvent>& events, const hkToiResources& resources) = 0;
};

class hkDefaultToiResourceMgr : public hkToiResourceMgr
{
public:
	hkDefaultToiResourceMgr();                                                                                      // 0x0111CCF0
	virtual hkResult beginToiAndSetupResources(const hkToiEvent& event, const hkArray<hkToiEvent>& events, hkToiResources& resources);   // 0x0111CD10
	virtual void endToiAndFreeResources(const hkToiEvent& event, const hkArray<hkToiEvent>& events, const hkToiResources& resources);   // 0x0111CD80
	int m_stackSize;   // +8 (0x20000)
};

// @ 0x0111ccf0
hkDefaultToiResourceMgr::hkDefaultToiResourceMgr()
{
	// refcount = 1 (base), vtable 0x014A60B8
	m_stackSize = 0x20000;
}

// @ 0x0111cd10
hkResult hkDefaultToiResourceMgr::beginToiAndSetupResources(const hkToiEvent& event, const hkArray<hkToiEvent>& events, hkToiResources& resources)
{
	int size = m_stackSize;
	resources.m_stackBytes = size;
	// hkThreadMemory::allocateStack(size): round (size + 16) to 16, bump the stack top or fall back to a new chunk.
	hkThreadMemory* tm = hkThreadMemory_getInstance();
	char* top = tm->m_stackTop;
	unsigned rounded = ((unsigned)size + 0x10u) & 0xfffffff0u;
	char* result;
	if (top + rounded <= tm->m_stackEnd)
	{
		tm->m_stackTop = top + rounded;
		result = top;
	}
	else
	{
		result = (char*)tm->allocateStackChunk((int)rounded);
	}
	resources.m_stackBuffer = result;
	resources.m_i08 = 1000;
	resources.m_i0c = 1000;
	resources.m_i04 = 1000;
	resources.m_i10 = 3;
	resources.m_i14 = 4;
	resources.m_i00 = 2;
	return HK_SUCCESS;
}

// @ 0x0111cd80
void hkDefaultToiResourceMgr::endToiAndFreeResources(const hkToiEvent& event, const hkArray<hkToiEvent>& events, const hkToiResources& resources)
{
	char* p = resources.m_stackBuffer;
	hkThreadMemory* tm = hkThreadMemory_getInstance();
	// hkThreadMemory::deallocateStack: pop back to p, releasing the chunk when it empties the stack
	tm->m_stackTop = p;
	if (p == tm->m_stackBase)
		tm->releaseStackChunk(p);
}

// ---- MOPP code assembler helpers (names guessed) ---------------------------------------------------------------------
// Byte buffer that grows backwards: byte k is stored at data[capacity - count - 1].
struct MoppCodeBuffer
{
	void addByte(int b);                         // 0x0111EB70 (name guessed)
	void addByteSum(int op, int v);              // 0x0111EBA0: stores (char)(op + v) (name guessed)
	void addOp8(int op, int v);                  // 0x0111EBD0: v, then op
	void addOp16(int op, int v);                 // 0x0111EC30: v, v>>8, then op
	void addOp24(int op, int v);                 // 0x0111ECC0: v, v>>8, v>>16, then op
	void addBytes24(int v);                      // 0x0111ED80: v, v>>8, v>>16
	void addOp32(int op, int v);                 // 0x0111EE10: v, v>>8, v>>16, v>>24, then op
	char m_pad[8];
	int m_capacity;                              // +8
	int m_count;                                 // +0xc
	// +0x10: data pointer
};

struct MoppAssembler
{
	char m_pad[0x10];
	MoppCodeBuffer* m_buffer;       // +0x10 (32-bit offset)

	void addProperty(int slot, int value);                     // 0x0111CF70
	void addTerminalReoffset(unsigned v);                      // 0x0111D020
	void addDoubleCuts(const void* axisTypes, const void* box);  // 0x0111D060
	void addPropertiesIfNeeded(const int* flag, const void* b, const void* c);   // 0x0111D140
	int addTerminal(const void* a1, const void* a2, const void* a3);              // 0x0111D190
	void addJump(int target);                                  // 0x0111D260
	void addFourBytes(const void* p);                          // 0x0111CFE0
	hkBool needsExtraProperty(const void* a, const int* b) const;   // 0x0111CED0
};

// @ 0x0111cc90
// Constructor of an object holding an inline array of 128 entries (storage at +0x10): data = this+0x10, size 0,
// capacity 128 with the "don't deallocate" flag. The compiled code also contains a dead _reserveExactly branch.
struct MoppInplaceArrayHolder
{
	int m_unk0;                                   // +0
	hkArray<int> m_array;                     // +4: data, size, capacityAndFlags
	// inline storage starts at +0x10
	MoppInplaceArrayHolder();
};
MoppInplaceArrayHolder::MoppInplaceArrayHolder()
{
	m_unk0 = 0;
	m_array.m_data = (int*)((char*)this + 0x10);   // 32-bit layout assumption: storage directly after the array header
	m_array.m_size = 0;
	m_array.m_capacityAndFlags = (int)0x80000080;   // 128 | DONT_DEALLOCATE
	m_array.m_size = 0;
}

// @ 0x0111cdb0
// Copies a "chunk" description: this[0x38] = p[0x28] - p[0x24], this[0x3c] = p[0x2c], then for each of the
// p[0x2c] entries p[0x30+4i]: this[0x40+4i] = p[0x30+4i], this[0x44+4i] = p[0x34+4i] - p[0x30+4i].
struct MoppChunk
{
	int m_w[0x20];     // raw words; the layout is not recovered (0x80 bytes covers every access here)
	void copyFrom(const void* p);                    // 0x0111CDB0
	void snapBounds();                               // 0x0111CE00
	void setFromFloatBox(const void* box, const float* xform);   // 0x0111D2B0
	void computeShift();                             // 0x0111D340
	MoppChunk* initFromParent(const MoppChunk* parent, const void* box, const float* xform);   // 0x0111D3C0
};
#define CW(off) m_w[(off) / 4]

void MoppChunk::copyFrom(const void* p)
{
	CW(0x38) = at<int>(p, 0x28) - at<int>(p, 0x24);
	CW(0x3c) = at<int>(p, 0x2c);
	for (int i = 0; i < at<int>(p, 0x2c); ++i)
	{
		CW(0x40 + 4 * i) = at<int>(p, 0x30 + 4 * i);
		CW(0x44 + 4 * i) = at<int>(p, 0x34 + 4 * i) - at<int>(p, 0x30 + 4 * i);
	}
}

// @ 0x0111ce00
void MoppChunk::snapBounds()
{
	// Round each axis range [lo, hi] outwards to a multiple of (1 << shift); arithmetic shifts as in the binary.
	int s = CW(0x24) & 31;
	CW(0x48) = (CW(0x0c) >> s) << s;
	CW(0x54) = ((CW(0x10) >> s) + 1) << s;
	s = CW(0x24) & 31;
	CW(0x4c) = (CW(0x14) >> s) << s;
	CW(0x58) = ((CW(0x18) >> s) + 1) << s;
	s = CW(0x24) & 31;
	CW(0x50) = (CW(0x1c) >> s) << s;
	CW(0x5c) = ((CW(0x20) >> s) + 1) << s;
}

// @ 0x0111ce50
// Releases the two buffers a compile context owns (offsets +0xec, +0xf0) unless it is flagged as non-owning (+4).
struct MoppDeallocator { virtual void v0(); virtual void v1(); virtual void release(void* p); };   // slot 2
struct MoppContextOwner
{
	char m_pad[0xc];
	MoppDeallocator* m_allocator;      // +0xc (32-bit offset)
	void releaseBuffers(void* ctx);    // 0x0111CE50
};
void MoppContextOwner::releaseBuffers(void* ctx)
{
	if (at<uint8_t>(ctx, 4) == 0)
	{
		m_allocator->release(at<void*>(ctx, 0xec));
		m_allocator->release(at<void*>(ctx, 0xf0));
		at<void*>(ctx, 0xec) = 0;
		at<void*>(ctx, 0xf0) = 0;
	}
}

// @ 0x0111cea0
// Marks a node and its chain of predecessors (link at +0) as visited until one is already marked.
void __stdcall markChainVisited(void* node)
{
	while (node != 0 && at<uint8_t>(node, 0x39) == 0)
	{
		at<uint8_t>(node, 0x39) = 1;
		node = at<void*>(node, 0);
	}
}

// @ 0x0111ced0
hkBool MoppAssembler::needsExtraProperty(const void* a, const int* b) const
{
	// signed compares (jge / jg)
	if (at<int>(a, 8) < 0x16)
		return hkBool(true);
	return hkBool(*b > at<int>(this, 0x14));
}

// @ 0x0111cf00
// Chooses between the child's own "level" (+0x34 of the parent) and this assembler's (+0x24 of a1) for the
// property level of a1; the odd condition is a size check on the three operand magnitudes (all unsigned).
void __stdcall chooseLevelForProperty(const void* a1, const void* a2, void* a3)
{
	at<uint32_t>(a3, 0x34) = at<uint32_t>(a2, 0x34);
	uint32_t lvl = at<uint32_t>(a2, 0x34);
	uint32_t base = at<uint32_t>(a1, 0x24);
	uint32_t cur = at<uint32_t>(a3, 0x38);
	uint32_t delta = (cur - lvl) + base;
	if (delta < 0x20)
		return;
	if (!(cur > 2) && delta < 0x100)
		return;
	if (cur < 0x20)
	{
		if (!(at<uint32_t>(a2, 0x38) >= 0x20))
			return;
	}
	else if (cur < 0x100)
	{
		if (!(at<uint32_t>(a2, 0x38) >= 0x100))
			return;
	}
	else
	{
		if (cur >= 0x10000)
			return;
		if (at<uint32_t>(a2, 0x38) < 0x10000)
			return;
	}
	at<uint32_t>(a3, 0x34) = base;
}

// @ 0x0111cf70
void MoppAssembler::addProperty(int slot, int value)
{
	// HK_MOPP_PROPERTY8/16/32 + slot: 0x60.., 0x64.., 0x68.. (negative values use the 32-bit form)
	if (value < 0)
		m_buffer->addOp32(slot + 0x68, value);
	else if (value < 0x100)
		m_buffer->addOp8(slot + 0x60, value);
	else if (value < 0x10000)
		m_buffer->addOp16(slot + 0x64, value);
	else
		m_buffer->addOp32(slot + 0x68, value);
}

// @ 0x0111cfe0
void MoppAssembler::addFourBytes(const void* p)
{
	m_buffer->addByte(at<int>(p, 0x10));
	m_buffer->addByte(at<int>(p, 0x0c));
	m_buffer->addByte(at<int>(p, 0x08));
	m_buffer->addByte(at<int>(p, 0x04));
}

// @ 0x0111d020
void MoppAssembler::addTerminalReoffset(unsigned v)
{
	// HK_MOPP_TERM_REOFFSET8/16/32 = 9, 10, 11
	if (v < 0x100)
		m_buffer->addOp8(9, (int)v);
	else if (v < 0x10000)
		m_buffer->addOp16(10, (int)v);
	else
		m_buffer->addOp32(11, (int)v);
}

// @ 0x0111d060
// Emits a DOUBLE_CUT per axis: types[i] == 1 -> 8-bit form (opcode 0x26+i), == 2 -> 24-bit form (opcode 0x29+i).
void MoppAssembler::addDoubleCuts(const void* axisTypes, const void* box)
{
	for (int i = 0; i < 3; ++i)
	{
		uint8_t type = at<uint8_t>(axisTypes, 0x40 + i);
		if (type == 1)
		{
			int base = at<int>(box, 0x28 + 4 * i);
			int shift = at<int>(box, 0x24);
			int hi = at<int>(box, 0x10 + 8 * i);
			int lo = at<int>(box, 0x0c + 8 * i);
			int hiShifted = (hi - base) >> (shift & 31);
			int loShifted = (lo - base) >> (shift & 31);
			m_buffer->addByte(hiShifted + 1);
			m_buffer->addByte(loShifted);
			m_buffer->addByte(0x26 + i);
		}
		if (type == 2)
		{
			int lo = at<int>(box, 0x0c + 8 * i);
			int hi = at<int>(box, 0x10 + 8 * i);
			m_buffer->addBytes24(hi + 1);
			m_buffer->addBytes24(lo);
			m_buffer->addByte(0x29 + i);
		}
	}
}

// @ 0x0111d140
void MoppAssembler::addPropertiesIfNeeded(const int* flag, const void* b, const void* c)
{
	if (*flag == 0)
	{
		if (at<int>(c, 0x44) == 0 && at<int>(c, 0x40) != 0)
			addProperty(0, at<int>(c, 0x40));
	}
	else if (at<int>(c, 0x44) == 0 && at<int>(b, 0x44) != 0)
	{
		addProperty(0, at<int>(c, 0x40));
	}
}

// @ 0x0111d190
// Emits a terminal for the primitive count, then the per-slot properties; returns the number of bytes added.
int MoppAssembler::addTerminal(const void* a1, const void* a2, const void* a3)
{
	int before = m_buffer->m_count;
	unsigned u = (unsigned)(*at<const int*>(a1, 0xb8) - at<int>(a3, 0x34));
	if (u < 0x20)
		m_buffer->addByteSum(0x30, (int)u);          // HK_MOPP_TERM4_0 + u
	else if (u < 0x100)
		m_buffer->addOp8(0x50, (int)u);              // HK_MOPP_TERM8
	else if (u < 0x10000)
		m_buffer->addOp16(0x51, (int)u);             // HK_MOPP_TERM16
	else if (u < 0x1000000)
		m_buffer->addOp24(0x52, (int)u);             // HK_MOPP_TERM24
	else
		m_buffer->addOp32(0x53, (int)u);             // HK_MOPP_TERM32
	for (int i = 0; i < at<int>(a1, 0x2c); ++i)
	{
		int v = at<int>(a1, 0x30 + 4 * i);
		if (v != 0 && at<int>(a2, 0x44 + 4 * i) != 0)
			addProperty(i, v);
	}
	return m_buffer->m_count - before;
}

// @ 0x0111d260
void MoppAssembler::addJump(int target)
{
	// HK_MOPP_JUMP8/16/24/32 = 5..8 with the distance from the current end of the code
	int d = m_buffer->m_count - target;
	if (d > 0)
	{
		if (d < 0xff)
			m_buffer->addOp8(5, d);
		else if (d < 0xffff)
			m_buffer->addOp16(6, d);
		else if (d < 0xffffff)
			m_buffer->addOp24(7, d);
		else
			m_buffer->addOp32(8, d);
	}
}

// @ 0x0111d2b0
// Quantizes a float box (min/max per axis at +0xc.. +0x20, stride 8) into integer cell ranges:
// lo = floor((min - origin[i]) * scale), hi = floor((max - origin[i]) * scale) + 1.
namespace hkMath { float hkFloor(float x); int hkFloatToInt(float x); }   // 0x0120AC90, 0x0120AD30
void MoppChunk::setFromFloatBox(const void* box, const float* xform)
{
	for (int i = 0; i < 3; ++i)
	{
		// the x87 scale register is reloaded from xform[3] for each product; operands are stored to float args
		float lo = (at<float>(box, 0x0c + 8 * i) - xform[i]) * xform[3];
		CW(0x0c + 8 * i) = hkMath::hkFloatToInt(hkMath::hkFloor(lo));
		float hi = (at<float>(box, 0x10 + 8 * i) - xform[i]) * xform[3];
		int hiCell = hkMath::hkFloatToInt(hkMath::hkFloor(hi));
		CW(0x10 + 8 * i) = hiCell + 1;
		// (the binary also tracks the largest cell extent in a local that is never used)
	}
}

// @ 0x0111d340
// shift = min(24, max over axes of bitlength(extent + (1 << (bitlength(maxExtent) - 4)))).
void MoppChunk::computeShift()
{
	int ex = CW(0x10) - CW(0x0c);
	int ey = CW(0x18) - CW(0x14);
	if (ex <= ey) ex = ey;
	int ez = CW(0x20) - CW(0x1c);
	if (ex <= ez) ex = ez;
	unsigned extent = (unsigned)ex;
	int bits = 0;
	for (unsigned t = extent; t != 0; t >>= 1)
		++bits;
	int best = -1;
	for (int axis = 3; axis != 0; --axis)
	{
		int n = 0;
		for (unsigned t = (1u << ((bits - 4) & 31)) + extent; t != 0; t >>= 1)
			++n;
		if (best < n)
			best = n;
	}
	CW(8) = (best > 0x18) ? 0x18 : best;
}

// @ 0x0111d3c0
MoppChunk* MoppChunk::initFromParent(const MoppChunk* parent, const void* box, const float* xform)
{
	for (int i = 0; i < 0x12; ++i)      // rep movsd, 0x48 bytes
		m_w[i] = parent->m_w[i];
	copyFrom(box);
	setFromFloatBox(box, xform);
	m_w[0] = parent->m_w[0] + 1;
	at<uint8_t>(this, 4) = 0;
	computeShift();
	return this;
}

// @ 0x0111d410
// True when more than 2 levels remain: min(a - max(b-8, 0), a) > 2, a = c.shift(+0x24), b = d(+8).
hkBool __stdcall hasSpareLevels(const void* unused, const void* c, const void* d)
{
	int t = at<int>(d, 8) - 8;
	if (t <= 0)
		t = 0;
	int level = at<int>(c, 0x24);
	int remaining = level - t;
	if (remaining > level)
		remaining = level;
	return hkBool(remaining > 2);
}

// @ 0x0111d450
// Result of the sub-division search: out[0] = ok, out[4] = number of levels dropped, out[8..16] = 3 cell offsets.
void __stdcall subdivideChunk(const void* parent, void* child, void* out)
{
	int t0 = at<int>(child, 8) - 8;
	if (t0 <= 0)
		t0 = 0;
	int level = at<int>(parent, 0x24);
	int drop = level - t0;
	if (drop > level)
		drop = level;
	at<uint8_t>(out, 0) = 0;
	if (drop > 0)
	{
		if (drop >= 4)
			drop = 4;
		for (;;)
		{
			at<int>(child, 0x24) = at<int>(parent, 0x24) - drop;
			bool ok = true;
			for (int k = 0; k < 3; ++k)
			{
				int base = at<int>(parent, 0x28 + 4 * k);
				int v = (at<int>(child, 0x0c + 8 * k) - base) >> (at<int>(parent, 0x24) & 31);
				at<int>(child, 0x28 + 4 * k) = (v << (at<int>(parent, 0x24) & 31)) + base;
				at<int>(out, 8 + 4 * k) = v;
				int span = (at<int>(child, 0x10 + 8 * k) - at<int>(child, 0x28 + 4 * k)) >> (at<int>(child, 0x24) & 31);
				if (span >= 0xff)
				{
					ok = false;
					break;
				}
			}
			if (ok)
			{
				at<int>(out, 4) = drop;
				at<uint8_t>(out, 0) = 1;
				return;
			}
			--drop;
		}
	}
	at<int>(child, 0x24) = at<int>(parent, 0x24);
	at<int>(child, 0x28) = at<int>(parent, 0x28);
	at<int>(child, 0x2c) = at<int>(parent, 0x2c);
	at<int>(child, 0x30) = at<int>(parent, 0x30);
}
