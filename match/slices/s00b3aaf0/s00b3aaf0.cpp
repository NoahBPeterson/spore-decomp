// Spore (SporeApp.exe) -- slice s00b3aaf0: eastl::vector<handle> resize + heap-adjust range.
//
//   0x00B3AAF0  vector<Handle>::resize(newSize): grow via insert(end, n, Handle{0,0})
//               or shrink via erase(begin+newSize, end)
//   0x00B3AB70  make_heap-style loop calling adjust_heap (0xB39970) over a range
//
// Self-contained TU: the owner is modelled with the member offsets the original used.
#include "types.h"

#define NULL 0

// ---------------------------------------------------------------------------
// element type: a refcounted handle slot {pointer, float}  (8 bytes)
//   ptr[0x40] is the shared refcount, bumped by the copy constructor
// ---------------------------------------------------------------------------
struct Handle
{
	int*  ptr;      // +0
	float value;    // +4

	Handle() {}
	Handle(const Handle& o)
	{
		ptr = o.ptr;
		if (ptr != NULL)
			((int*)ptr)[0x10]++;
		value = o.value;
	}
};

// ---------------------------------------------------------------------------
// external callees (defined elsewhere in the image) -- modelled as members of
// data-less stubs so the compiler emits the original __thiscall sequence.
// ---------------------------------------------------------------------------
struct VecStub
{
	void Insert(Handle* where, unsigned int count, const Handle* value);   // 0x00b38690
	void Destroy(Handle* first, Handle* last);                             // 0x00b36130
};

// 0x00b36530  eastl::copy-like helper: copy [first,last) to dst, return new end
extern "C" Handle* __cdecl FUN_00b36530(Handle* first, Handle* last, Handle* dst);

// 0x00b39970  adjust_heap(first, holeIndex, length, topIndex, value, ctx)
extern "C" void __cdecl FUN_00b39970(Handle* first, int holeIndex, int length,
                                     int topIndex, Handle value, int ctx);

// ---------------------------------------------------------------------------
// the vector owner
// ---------------------------------------------------------------------------
struct HandleVec
{
	Handle* mpBegin;     // +0
	Handle* mpEnd;       // +4
	Handle* mpCapacity;  // +8

	void Resize(unsigned int newSize);
};

// ---------------------------------------------------------------------------
// 0x00B3AAF0
// ---------------------------------------------------------------------------
// @ 0x00b3aaf0
void HandleVec::Resize(unsigned int newSize)
{
	Handle* end = mpEnd;
	unsigned int size = (unsigned int)(end - mpBegin);
	if (newSize > size)
	{
		Handle local;
		local.ptr = NULL;
		local.value = 0.0f;
		((VecStub*)this)->Insert(end, newSize - size, &local);
		return;
	}
	Handle* p = mpBegin + newSize;
	Handle* e = FUN_00b36530(end, end, p);
	((VecStub*)this)->Destroy(e, mpEnd);
	mpEnd += -(end - p);
}

// ---------------------------------------------------------------------------
// 0x00B3AB70
// ---------------------------------------------------------------------------
// @ 0x00b3ab70
void FUN_00b3ab70(Handle* first, Handle* last, volatile int ctx)
{
	int length = (int)(last - first);
	if (length < 2)
		return;
	int parent = ((length - 2) >> 1) + 1;
	do
	{
		--parent;
		FUN_00b39970(first, parent, length, parent, first[parent], (int)ctx);
	} while (parent != 0);
}
