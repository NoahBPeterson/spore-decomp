// Slice s00c2b030: trace-cache hash map instantiation (node copy, find-or-insert, get-or-create).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// The map key is a 32-bit id (an owning object's address); the mapped value is a 0x820-byte trace cache
// made of 8 cached hit records (0x100 bytes each) followed by 8 cached object pointers.  Callees that are
// __thiscall are modelled as members of placeholder structs (MSVC rejects __thiscall on free functions).
#include "types.h"

struct Node;
struct TraceCache;

// Range fill helper: for n = count; n > 0; --n { fn(dst, src); dst += stride; src += stride; }
// (0x00406540, stdcall; it enters the copy functor with dst in ecx and src on the stack).
extern "C" void __stdcall FUN_00406540(void* dst, const void* src, int stride, int count, void* fn);

struct Hit
{
	char mBytes[0x100];          // cached trace entry; only its size matters to this slice
};

struct TraceCache
{
	Hit   hits[8];               // +0x000 .. +0x7ff
	void* objects[8];            // +0x800 .. +0x81f
	TraceCache* Init();          // 0x00c296b0
	void        Destroy();       // 0x00cadb00
};

// 0x00cadb50: zero the eight hit records, then release the eight cached objects.
extern "C" void __cdecl FUN_00cadb50(TraceCache* cache);

struct Value                   // what the table stores: the key plus the mapped cache
{
	unsigned   mKey;             // +0x000
	TraceCache mValue;           // +0x004 .. +0x823
	__declspec(noinline) Value* CopyFrom(const unsigned* key, TraceCache* src);   // 0x00c2b030
};

struct Node : Value            // 0x828-byte bucket node; only the allocated nodes carry the link
{
	Node* mpNext;                // +0x824
};

struct Iter                    // eastl hash iterator (8 bytes)
{
	Node*  mpNode;               // +0x00
	Node** mpBucket;             // +0x04
};

struct InsertResult : Iter     // eastl insert() result, the iterator plus the "already present" flag
{
	bool mInserted;              // +0x08
};

struct Ht                      // global instance at 0x01572460
{
	void*    mField00;           // +0x00 (hash functor)
	Node**   mpBuckets;          // +0x04
	unsigned mBucketCount;       // +0x08
	unsigned mSize;              // +0x0c
	void*    mAllocator;         // +0x10
	void Find(Iter* out, const unsigned* key);                          // 0x00cb00d0
	// 0x00cb1110 only tests the low byte of `existing` (cmp byte [esp+0x10], 0).
	void Insert(InsertResult* out, const Value* value, unsigned existing);
	__declspec(noinline) TraceCache* FindOrInsert(const unsigned* key);  // 0x00c2b080
};

// @ 0x00c2b030
Value* Value::CopyFrom(const unsigned* key, TraceCache* src)
{
	mKey = *key;
	// the helper walks byte offsets: the eight hit records (stride 0x100), then the eight object slots
	char*       pDst = (char*)&mValue;
	const char* pSrc = (const char*)src;
	FUN_00406540(pDst, pSrc, 0x100, 8, (void*)0x00c29ab0);
	FUN_00406540(pDst + 0x800, pSrc + 0x800, 4, 8, (void*)0x00ac8980);
	return this;
}

// @ 0x00c2b080
TraceCache* Ht::FindOrInsert(const unsigned* key)
{
	// The "already present" flag is passed through the first slot of the insert result: the original
	// stores it as a byte and reloads it as a dword, so the two share the slot.
	union InsertSlot
	{
		InsertResult res;        // +0x00
		unsigned     flags;      // +0x00 (low byte: the flag)
		bool         bExisting;  // +0x00
	} out;
	TraceCache temp;
	Value      value;

	Find(&out.res, key);
	if (out.res.mpNode != mpBuckets[mBucketCount])
		return &out.res.mpNode->mValue;

	Value* pValue = value.CopyFrom(key, temp.Init());
	out.bExisting = false;
	Insert(&out.res, pValue, out.flags);
	value.mValue.Destroy();
	temp.Destroy();
	return &out.res.mpNode->mValue;
}

// @ 0x00c2b110
TraceCache* __cdecl FUN_00c2b110(unsigned key)
{
	Ht* ht = (Ht*)0x01572460;
	Iter it;

	ht->Find(&it, &key);
	if (it.mpNode == ht->mpBuckets[ht->mBucketCount])
	{
		TraceCache* cache = ht->FindOrInsert(&key);
		FUN_00cadb50(cache);
		return cache;
	}
	return &it.mpNode->mValue;
}
