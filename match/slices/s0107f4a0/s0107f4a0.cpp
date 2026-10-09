// Havok 3.1.0 base library, part 3 (0x0107F4A0..0x0108040F): hkArrayUtil, hkPoolMemory (the size-class
// pool allocator behind hkMemory::s_instance), hkCriticalSection::enter, hkMemoryStreamReader and hkClass.
// No floating point in this slice.
#include "../s0107e670/hk31_base.h"
#include <malloc.h>
#if defined(_MSC_VER)
#include <intrin.h>
#define HK_RDTSC32() ((hkUint32)__rdtsc())
#else
#define _aligned_malloc(sz, al) aligned_alloc(al, sz)
#define _aligned_free(p) free(p)
#define HK_RDTSC32() ((hkUint32)__builtin_ia32_rdtsc())
#endif

// ---- hkArrayUtil -----------------------------------------------------------------------------------------

struct hkArrayRaw
{
	void* m_data;
	int m_size;
	int m_capacityAndFlags;
};

// @ 0x0107f4a0
void hkArrayUtil::_reserveExactly(void* array, int newCapacity, int elemSize)
{
	hkArrayRaw* a = (hkArrayRaw*)array;
	void* mem = hkThreadMemory::getInstance().allocateChunk(newCapacity * elemSize, HK_MEMORY_CLASS_ARRAY);
	hkString::memCpy(mem, a->m_data, a->m_size * elemSize);
	if (a->m_capacityAndFlags >= 0)
	{
		hkThreadMemory::getInstance().deallocateChunk(a->m_data, (a->m_capacityAndFlags & 0x3fffffff) * elemSize,
		                                              HK_MEMORY_CLASS_ARRAY);
	}
	a->m_data = mem;
	a->m_capacityAndFlags = (a->m_capacityAndFlags & 0x40000000) | newCapacity;
}

// @ 0x0107f530
void hkArrayUtil::_reserveMore(void* array, int elemSize)
{
	hkArrayRaw* a = (hkArrayRaw*)array;
	int newCapacity = (a->m_size == 0) ? 1 : a->m_size * 2;
	void* mem = hkThreadMemory::getInstance().allocateChunk(newCapacity * elemSize, HK_MEMORY_CLASS_ARRAY);
	hkString::memCpy(mem, a->m_data, a->m_size * elemSize);
	if (a->m_capacityAndFlags >= 0)
	{
		hkThreadMemory::getInstance().deallocateChunk(a->m_data, (a->m_capacityAndFlags & 0x3fffffff) * elemSize,
		                                              HK_MEMORY_CLASS_ARRAY);
	}
	a->m_data = mem;
	a->m_capacityAndFlags = (a->m_capacityAndFlags & 0x40000000) | newCapacity;
}

// @ 0x0107f5d0
// Moves the array into its inplace storage when it fits, otherwise into a smaller heap block (capacity / 2).
// Real name unknown (looks like hkArrayUtil::_reduce / optimizeCapacity).
void hkArrayUtil::_reduce(void* array, int elemSize, void* inplaceStorage, int inplaceCapacity)
{
	hkArrayRaw* a = (hkArrayRaw*)array;
	void* newData;
	int newCapacity;
	hkUint32 flag;
	if (inplaceStorage == 0 || inplaceCapacity <= a->m_size)
	{
		newCapacity = (a->m_capacityAndFlags >> 1) & 0x1fffffff;
		newData = hkThreadMemory::getInstance().allocateChunk(newCapacity * elemSize, HK_MEMORY_CLASS_ARRAY);
		flag = 0;
	}
	else
	{
		newData = inplaceStorage;
		newCapacity = inplaceCapacity;
		flag = 0x80000000;
	}
	hkString::memCpy(newData, a->m_data, a->m_size * elemSize);
	hkThreadMemory::getInstance().deallocateChunk(a->m_data, ((hkUint32)a->m_capacityAndFlags & 0x3fffffffU) * elemSize,
	                                              HK_MEMORY_CLASS_ARRAY);
	a->m_data = newData;
	a->m_capacityAndFlags = (int)(((hkUint32)a->m_capacityAndFlags & 0x40000000U) | flag | (hkUint32)newCapacity);
}

// ---- hkPoolMemory ----------------------------------------------------------------------------------------

// Size class (row) for a request of n bytes, n <= 0x2000. Anything bigger is a bug and breaks into the debugger.
static inline int hkPoolRowForSize(int n)
{
	int row;
	if (n < 9) row = 1;
	else if (n < 0x11) row = 2;
	else if (n < 0x21) row = 3;
	else if (n < 0x31) row = 4;
	else if (n < 0x41) row = 5;
	else if (n < 0x61) row = 6;
	else if (n < 0x81) row = 7;
	else if (n < 0xa1) row = 8;
	else if (n < 0xc1) row = 9;
	else if (n < 0x101) row = 10;
	else if (n < 0x141) row = 11;
	else if (n < 0x201) row = 12;
	else if (n < 0x401) row = 13;
	else if (n < 0x801) row = 14;
	else if (n < 0x1001) row = 15;
	else
	{
		if (0x2000 < n)
			HK_BREAKPOINT();
		row = 16;
	}
	return row;
}

// @ 0x0107f670
int hkPoolMemory::getAllocatedSize(int nbytes)
{
	if (0x2000 < nbytes)
	{
		if (0x10 < nbytes)
			return ((nbytes + 0xf) & 0xfffffff0) + 0x10;
		return nbytes + 8;
	}
	if (nbytes < 0x201)
		return m_rowSizes[(int)m_sizeToRow[nbytes]];
	return m_rowSizes[m_bigSizeToRow[(nbytes - 1) >> 10]];
}

// @ 0x0107f6c0
hkPoolMemory::~hkPoolMemory()
{
	while (m_pageList != 0)
	{
		hkUint8* page = m_pageList;
		m_pageList = *(hkUint8**)page;
		_aligned_free(page);
	}
	DeleteCriticalSection(m_lock.m_cs);
}

// @ 0x0107f700
void hkPoolMemory::printStatistics(hkOstream* o)
{
	o->printf("Statistics are disabled, please enable them in hkbase/config/hkConfigMemoryStats.h\n");
}

// @ 0x0107f720
void* hkPoolMemory::allocate(int nbytes, int cl)
{
	// 16-byte debug header: {magic, nbytes, class, pad}; the caller gets the block after it.
	hkUint32* h = (hkUint32*)allocateChunk(nbytes + 0x10, cl);
	h[1] = (hkUint32)nbytes;
	h[2] = (hkUint32)cl;
	h[0] = 0x2345656;
	return h + 4;
}

// @ 0x0107f750
void hkPoolMemory::deallocate(void* p)
{
	if (p != 0)
	{
		hkUint32* h = (hkUint32*)p - 4;
		h[0] = 0xdeadbeef;
		deallocateChunk(h, (int)h[1] + 0x10, (int)h[2]);
	}
}

// @ 0x0107f780
void* hkPoolMemory::alignedAllocate(int alignment, int nbytes, int cl)
{
	char* base = (char*)allocateChunk(alignment + nbytes + 0x10, cl);
	hkUlong aligned = ((hkUlong)base + 0xf + (hkUlong)alignment) & ~((hkUlong)alignment - 1);
	hkUint32* h = (hkUint32*)aligned;
	h[-3] = (hkUint32)(alignment + nbytes);
	h[-2] = (hkUint32)cl;
	h[-4] = 0x2345656;
	h[-1] = (hkUint32)(aligned - (hkUlong)base);
	return (void*)aligned;
}

// @ 0x0107f7d0
void hkPoolMemory::alignedDeallocate(void* p)
{
	if (p != 0)
	{
		hkUint32* h = (hkUint32*)p;
		h[-4] = 0xdeadbeef;
		deallocateChunk((char*)p - h[-1], (int)h[-3] + 0x10, (int)h[-2]);
	}
}

// @ 0x0107f800
void hkPoolMemory::getStatSynopsis(hkMemoryStatistics* s)
{
	*s = m_stats;
}

// @ 0x0107f820
void hkCriticalSection::enter()
{
	// Timer record written into the thread's monitor stream: {command string, tsc low, unused}.
	struct TimerCommand { const char* m_command; hkUint32 m_time0; hkUint32 m_time1; };

	if (!TryEnterCriticalSection(m_cs))
	{
		if (TlsGetValue(g_hkMonitorTlsEnabled) == 0)
		{
			EnterCriticalSection(m_cs);
		}
		else
		{
			// HK_TIMER_BEGIN("CriticalLock")
			if (TlsGetValue(g_hkMonitorTlsCurrent) < TlsGetValue(g_hkMonitorTlsEnd))
			{
				TimerCommand* c = (TimerCommand*)TlsGetValue(g_hkMonitorTlsCurrent);
				c->m_command = "TtCriticalLock";
				c->m_time0 = HK_RDTSC32();
				TlsSetValue(g_hkMonitorTlsCurrent, c + 1);
			}
			EnterCriticalSection(m_cs);
			// HK_TIMER_END()
			if (TlsGetValue(g_hkMonitorTlsCurrent) < TlsGetValue(g_hkMonitorTlsEnd))
			{
				TimerCommand* c = (TimerCommand*)TlsGetValue(g_hkMonitorTlsCurrent);
				c->m_command = "Et";
				c->m_time0 = HK_RDTSC32();
				TlsSetValue(g_hkMonitorTlsCurrent, c + 1);
			}
		}
	}
	m_owner = hkGetCurrentThreadId();
}

// @ 0x0107f910
hkPoolMemory::hkPoolMemory()
{
	InitializeCriticalSectionAndSpinCount(m_lock.m_cs, 4000);
	m_pageStart = 0;
	m_pageEnd = 0;
	m_pageCur = 0;
	m_pageList = 0;
	for (int i = 16; i >= 0; --i)
	{
		m_freeLists[i] = 0;
		m_rowCounts[i] = 0;
	}
	for (int n = 0; n < 0x201; ++n)
	{
		int row = hkPoolRowForSize(n);
		m_sizeToRow[n] = (char)row;
		m_rowSizes[row] = n;
	}
	int n = 0x400;
	int* big = m_bigSizeToRow;
	do
	{
		int row = hkPoolRowForSize(n);
		*big = row;
		m_rowSizes[row] = n;
		n += 0x400;
		big++;
	} while (n < 0x2400);
	m_stats.m_numBigBlocks = 0;
	m_stats.m_bigBlockBytes = 0;
	m_stats.m_peakBigBlockBytes = 0;
	m_stats.m_numPages = 0;
	m_stats.m_inUseBytes = 0;
	m_stats.m_pageSize = 0x2000;
	m_stats.m_pageAlignment = 0x40;
}

// Pops one block from size class `row`, refilling the row from a fresh 0x2040-byte page when its free list is empty.
void* hkPoolMemory::_allocateFromRow(int row)
{
	m_rowCounts[row] = m_rowCounts[row] + 1;
	m_stats.m_inUseBytes = m_stats.m_inUseBytes + m_rowSizes[row];
	void** head = (void**)m_freeLists[row];
	void* result;
	if (head == 0)
	{
		int sz = m_rowSizes[row];
		if (row < 0xd)
		{
			// Small rows are carved from the shared bump page.
			if ((hkUlong)m_pageEnd < (hkUlong)(m_pageCur + sz))
			{
				hkUint8* page = (hkUint8*)_aligned_malloc(0x2040, 0x40);
				*(hkUint8**)page = m_pageList;
				m_pageList = page;
				m_pageStart = page + 0x40;
				m_pageCur = page + 0x40;
				m_pageEnd = page + 0x2040;
				m_stats.m_numPages = m_stats.m_numPages + 1;
			}
			result = m_pageCur;
			hkUint8* p = m_pageCur + sz;
			m_pageCur = p;
			int saved = m_rowCounts[row];
			int off = sz;
			while (off < 0x100 && (hkUlong)(p + sz) < (hkUlong)m_pageEnd)
			{
				m_rowCounts[row] = m_rowCounts[row] - 1;
				*(void**)p = m_freeLists[row];
				m_freeLists[row] = p;
				p = m_pageCur + sz;
				off += sz;
				m_pageCur = p;
			}
			m_rowCounts[row] = saved;
		}
		else
		{
			// Large rows get a page of their own.
			hkUint8* page = (hkUint8*)_aligned_malloc(0x2040, 0x40);
			if (m_pageList == 0)
			{
				*(hkUint8**)page = 0;
				m_pageList = page;
			}
			else
			{
				*(hkUint8**)page = *(hkUint8**)m_pageList;
				*(hkUint8**)m_pageList = page;
			}
			m_stats.m_numPages = m_stats.m_numPages + 1;
			int saved = m_rowCounts[row];
			result = page + 0x40;
			hkUint8* p = (hkUint8*)result + sz;
			if (sz < 0x2000)
			{
				int off = (int)(p - (hkUint8*)result);
				do
				{
					m_rowCounts[row] = m_rowCounts[row] - 1;
					*(void**)p = m_freeLists[row];
					m_freeLists[row] = p;
					off += sz;
					p += sz;
				} while (off < 0x2000);
			}
			m_rowCounts[row] = saved;
		}
	}
	else
	{
		m_freeLists[row] = *head;
		result = head;
	}
	return result;
}

// @ 0x0107fbe0
void* hkPoolMemory::allocateChunk(int nbytes, int cl)
{
	m_lock.enter();
	void* result;
	if (nbytes < 0x2001)
	{
		int row;
		if (nbytes < 0x201)
			row = (int)m_sizeToRow[nbytes];
		else
			row = m_bigSizeToRow[(nbytes - 1) >> 10];
		result = _allocateFromRow(row);
	}
	else
	{
		int total = m_stats.m_bigBlockBytes + nbytes;
		m_stats.m_numBigBlocks = m_stats.m_numBigBlocks + 1;
		m_stats.m_bigBlockBytes = total;
		if (m_stats.m_peakBigBlockBytes < total)
			m_stats.m_peakBigBlockBytes = total;
		result = _aligned_malloc(nbytes, 0x40);
	}
	m_lock.leave();
	return result;
}

// @ 0x0107fdd0
void* hkPoolMemory::allocateChunkByRow(int row, int cl)
{
	m_lock.enter();
	void* result = _allocateFromRow(row);
	m_lock.leave();
	return result;
}

// @ 0x0107ff60
void hkPoolMemory::deallocateChunk(void* p, int nbytes, int cl)
{
	m_lock.enter();
	if (p != 0)
	{
		if (nbytes < 0x2001)
		{
			int row;
			if (nbytes < 0x201)
				row = (int)m_sizeToRow[nbytes];
			else
				row = m_bigSizeToRow[(nbytes - 1) >> 10];
			m_stats.m_inUseBytes = m_stats.m_inUseBytes - m_rowSizes[row];
			m_rowCounts[row] = m_rowCounts[row] - 1;
			*(void**)p = m_freeLists[row];
			m_freeLists[row] = p;
		}
		else
		{
			m_stats.m_bigBlockBytes = m_stats.m_bigBlockBytes - nbytes;
			_aligned_free(p);
		}
	}
	m_lock.leave();
}

// @ 0x0107fff0
void hkPoolMemory::deallocateChunkByRow(void* p, int row)
{
	m_lock.enter();
	m_stats.m_inUseBytes = m_stats.m_inUseBytes - m_rowSizes[row];
	m_rowCounts[row] = m_rowCounts[row] - 1;
	*(void**)p = m_freeLists[row];
	m_freeLists[row] = p;
	m_lock.leave();
}

// ---- hkMemoryStreamReader --------------------------------------------------------------------------------

// @ 0x01080040
int hkMemoryStreamReader::read(void* buf, int nbytes)
{
	if (isOk())
	{
		int avail = m_length - m_pos;
		int n = nbytes;
		if (avail <= nbytes)
			n = avail;
		hkString::memCpy(buf, m_buf + m_pos, n);
		m_pos = m_pos + n;
		if (n == 0 && nbytes != 0)
			m_pos = m_length + 1;   // read past the end: poisons isOk()
		return n;
	}
	return 0;
}

// @ 0x010800b0
int hkMemoryStreamReader::skip(int nbytes)
{
	if (isOk())
	{
		int avail = m_length - m_pos;
		if (nbytes < avail)
			avail = nbytes;
		m_pos = m_pos + avail;
		if (avail == 0 && nbytes != 0)
			m_pos = m_length + 1;
		return avail;
	}
	return 0;
}

// @ 0x01080100
hkBool hkMemoryStreamReader::isOk() const
{
	return m_pos != m_length + 1;
}

// @ 0x01080120
hkBool hkMemoryStreamReader::markSupported() const
{
	return m_length != 0;
}

// @ 0x01080140
hkResult hkMemoryStreamReader::setMark(int markLimit)
{
	m_mark = m_pos;
	return HK_SUCCESS;
}

// @ 0x01080150
hkResult hkMemoryStreamReader::rewindToMark()
{
	if (m_mark >= 0)
	{
		m_pos = m_mark;
		return HK_SUCCESS;
	}
	return HK_FAILURE;
}

// @ 0x01080170
hkResult hkMemoryStreamReader::seek(int offset, SeekWhence whence)
{
	int pos = offset;
	if (whence != 0)
	{
		if (whence == 1)
		{
			pos = m_pos + offset;
		}
		else
		{
			pos = -1;
			if (whence == 2)
				pos = m_length - offset;
		}
	}
	if (pos >= 0)
	{
		if (pos <= m_length)
		{
			m_pos = pos;
			return HK_SUCCESS;
		}
		m_pos = m_length;
		return HK_FAILURE;
	}
	m_pos = 0;
	return HK_FAILURE;
}

// @ 0x010801d0
hkMemoryStreamReader::hkMemoryStreamReader(const void* mem, int size, MemoryType t)
{
	m_pos = 0;
	m_length = size;
	m_mark = -1;
	m_memType = t;
	if (t == MEMORY_COPY)
	{
		char* copy = (char*)hkMemory::s_instance->allocate(size, HK_MEMORY_CLASS_STREAM);
		m_buf = copy;
		hkString::memCpy(copy, mem, size);
		return;
	}
	m_buf = (const char*)mem;
}

// @ 0x01080240 (scalar deleting destructor)
hkMemoryStreamReader::~hkMemoryStreamReader()
{
	if (m_memType == MEMORY_COPY || m_memType == MEMORY_TAKE)
		hkMemory::s_instance->deallocate((void*)m_buf);
}

// ---- hkReferencedObject placement init, hkClass ----------------------------------------------------------

class hkPlainReferencedObject : public hkReferencedObject
{
public:
	hkPlainReferencedObject() {}
};

// @ 0x01080290
// Null-checked in-place construction of a plain hkReferencedObject (vtable 0x013EF7F4, refcount 1). Real name unknown.
void hkReferencedObject_constructAt(hkReferencedObject* p)
{
	if (p != 0)
		new (p) hkPlainReferencedObject();
}

// @ 0x010802b0
hkClass::hkClass(const char* name, const hkClass* parent, int objectSize, const hkClass** implementedInterfaces,
                 int numImplementedInterfaces, const hkClassEnum* enums, int numEnums,
                 const hkClassMember* members, int numMembers, const void* defaults)
{
	m_name = name;
	m_parent = parent;
	m_objectSize = objectSize;
	m_numImplementedInterfaces = numImplementedInterfaces;
	m_declaredEnums = enums;
	m_numDeclaredEnums = numEnums;
	m_declaredMembers = members;
	m_numDeclaredMembers = numMembers;
	m_defaults = defaults;
}

// ---- hkClass -------------------------------------------------------------------------------------------

// @ 0x01080300
hkBool hkClass::isSuperClass(const hkClass& k) const
{
	const hkClass* c = &k;
	for (;;)
	{
		if (c == 0)
			return false;
		if (c == this)
			break;
		c = c->m_parent;
	}
	return true;
}

// @ 0x01080330
int hkClass::getNumMembers() const
{
	int n = m_numDeclaredMembers;
	for (const hkClass* p = m_parent; p != 0; p = p->m_parent)
		n += p->m_numDeclaredMembers;
	return n;
}

// @ 0x01080350
const hkClassMember& hkClass::getMember(int index) const
{
	int n = m_numDeclaredMembers;
	for (const hkClass* p = m_parent; p != 0; p = p->m_parent)
		n += p->m_numDeclaredMembers;
	index = index - n;
	const hkClass* c = this;
	do
	{
		index = index + c->m_numDeclaredMembers;
		if (index >= 0)
			return c->m_declaredMembers[index];
		c = c->m_parent;
	} while (c != 0);
	return m_declaredMembers[0];
}

// @ 0x010803b0
const hkClassMember& hkClass::getDeclaredMember(int index) const
{
	return m_declaredMembers[index];
}

// @ 0x010803c0
const hkClassMember* hkClass::getMemberByName(const char* name) const
{
	int i = 0;
	for (;;)
	{
		if (getNumMembers() <= i)
			return 0;
		const hkClassMember* m = &getMember(i);
		if (hkString::strCmp(m->m_name, name) == 0)
			return m;
		i++;
	}
}
// --- equivalence checker address annotations
    extern unsigned int g_hkThreadMemoryTls; // 0x016e4174

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
