// Havok 3.1.0 slice s010a4e40 (continued): hkJobQueue helpers and the
// hkConstraintSolverSetup memory/jacobian builders.
//
// Struct stubs carry members at the x86 offsets of the 32-bit binary (comments).
// Flags: /vc71 /O2 /MD /Gy /TP
#pragma once
#include "types.h"

// hkMemory singleton (vtable slots: +0x10 allocateChunk, +0x14 deallocateChunk).
struct hkMemory
{
	virtual void* slot00();
	virtual void* slot04();
	virtual void* slot08();
	virtual void* slot0c();
	virtual void* allocateChunk(int nbytes, int cl);                // +0x10
	virtual void  deallocateChunk(void* p, int nbytes, int cl);     // +0x14
};

// ---------------------------------------------------------------------------
// hkSemaphore (0x01209800 ctor, 0x01209840 release)
struct hkSemaphore
{
	void* m_handle;                               // +0x00 (4 bytes)
	void ctor(int initialCount, int spinCount);   // 0x01209800
	void release(int count);                      // 0x01209840
};

// hkJobQueue: a critical section at +0, two semaphores at +0x48/+0x4c, an
// allocated "dynamic data" block pointer at +0x40, state bytes around +0x50.
struct hkReleaseCounts;
struct JobQueueDynamicData;

struct hkJobQueue
{
	uint32_t m_cs[0x18 / 4];                      // +0x00..+0x17 CRITICAL_SECTION
	int      m_w18;                               // +0x18
	int      m_w1c;                               // +0x1c
	uint32_t m_csRest[0x20 / 4];                  // +0x20..+0x3f
	JobQueueDynamicData* m_dynamic40;             // +0x40
	uint8_t  m_byte44;                            // +0x44
	uint8_t  m_pad45[3];
	hkSemaphore m_semA;                           // +0x48
	hkSemaphore m_semB;                           // +0x4c
	uint8_t  m_b50;                               // +0x50
	uint8_t  m_b51;                               // +0x51
	uint8_t  m_b52;                               // +0x52
	uint8_t  m_b53;                               // +0x53
	uint8_t  m_b54;                               // +0x54
	uint8_t  m_b55;                               // +0x55
	uint8_t  m_b56;                               // +0x56
	uint8_t  m_b57;                               // +0x57
	uint8_t  m_b58;                               // +0x58
	uint8_t  m_b59;                               // +0x59
	uint32_t m_pad5c[1];

	hkJobQueue* ctor();                          // 0x010a5a90
	void pushEntry(void* entry, int front, int which);   // 0x010a5ba0
	void releaseAll(hkReleaseCounts* counts);           // 0x010a5830
};

// The two counting fields released by 0x010a5830 live at +0x04/+0x08 of the
// object passed in ecx (a queue-count block, not the job queue itself).
struct hkReleaseCounts
{
	int m_pad00;                                  // +0x00
	int m_count04;                                // +0x04
	int m_count08;                                // +0x08
};

// @ 0x010a5830
void hkJobQueue::releaseAll(hkReleaseCounts* counts)
{
	int n = counts->m_count04;
	counts->m_count04 = 0;
	if (n > 0) {
		do {
			m_semA.release(1);
			--n;
		} while (n != 0);
	}
	n = counts->m_count08;
	counts->m_count08 = 0;
	if (n > 0) {
		do {
			m_semB.release(1);
			--n;
		} while (n != 0);
	}
}

// ---------------------------------------------------------------------------
// hkJobQueue entry block: 0x80 bytes; the queue is an hkQueue<JobQueueEntry>.
// reserve() uses an element size of 0x80 (shift by 7) and the Havok chunk
// allocator/deallocator with memory class 0x14.
extern "C" void* hkStringMemCpy(void* dst, const void* src, unsigned int n);   // 0x0107f440

extern "C" hkMemory* g_hkMemoryInstance;    // 0x016e4178 (pointer to the hkMemory singleton)

template <typename T>
struct hkQueue
{
	T*    m_data;                                 // +0x00
	int   m_size;                                 // +0x04 (allocated element count)
	int   m_capacity;                             // +0x08 (usable element count)
	int   m_head;                                 // +0x0c
	int   m_tail;                                 // +0x10
	int   m_count;                                // +0x14

	void reserve(int newCapacity);                // 0x010a5890
	void growInternal();                          // 0x010a58f0
	void pushFront(const T& e);                   // 0x010a59f0
	void pushBack(const T& e);                    // 0x010a5a40
};

// @ 0x010a5890
template <typename T>
void hkQueue<T>::reserve(int newCapacity)
{
	if (m_size < newCapacity) {
		T* p = (T*)g_hkMemoryInstance->allocateChunk(newCapacity << 7, 0x14);
		if (m_data != 0)
			hkStringMemCpy(p, m_data, m_size << 7);
		if (m_size != 0)
			g_hkMemoryInstance->deallocateChunk(m_data, m_size << 7, 0x14);
		m_data = p;
		m_size = newCapacity;
	}
}

// @ 0x010a58f0
template <typename T>
void hkQueue<T>::growInternal()
{
	int count = m_count;
	int mask = (m_tail > m_head) ? 0 : m_tail;

	if (m_size == 0) {
		int cap = m_capacity;
		if (cap < 8)
			cap = 8;
		reserve(cap);
	} else {
		unsigned need = (m_capacity + m_size * 2 + mask) << 7;
		unsigned c = 1;
		if (need > 1) {
			do { c <<= 1; } while (need > c);
		}
		reserve(c >> 7);
	}

	if (mask != 0) {
		if (mask > 0) {
			unsigned dst = (unsigned)count << 7;
			unsigned src = 0;
			int n = mask;
			do {
				T* d = (T*)((char*)m_data + dst);
				T* s = (T*)((char*)m_data + src);
				*d = *s;
				src += 0x80;
				dst += 0x80;
				--n;
			} while (n != 0);
		}
	}
	m_tail = count + mask;
}

// @ 0x010a59f0
template <typename T>
void hkQueue<T>::pushFront(const T& e)
{
	if (m_capacity + m_count >= m_size) {
		growInternal();
	} else if (m_tail == m_size) {
		m_tail = 0;
	}
	T* p = (T*)((char*)m_data + m_tail * 0x80);
	*p = e;
	++m_tail;
	++m_count;
}

// @ 0x010a5a40
template <typename T>
void hkQueue<T>::pushBack(const T& e)
{
	if (m_capacity + m_count >= m_size)
		growInternal();
	if (m_head == 0)
		m_head = m_size;
	--m_head;
	T* p = (T*)((char*)m_data + m_head * 0x80);
	*p = e;
	++m_count;
}

// ---------------------------------------------------------------------------
// DynamicData (the block pointed to by hkJobQueue + 0x40): 3 x hkQueue headers
// of 0x18 bytes each, at +0x10/+0x28/+0x40, plus its own header words.
// The three queue headers inside DynamicData (0x18 bytes each): data/size/cap/head/tail/count.
struct hkQueueHdr
{
	int m_data;                                   // +0x00
	int m_size;                                   // +0x04
	int m_capacity;                               // +0x08
	int m_head;                                   // +0x0c
	int m_tail;                                   // +0x10
	int m_count;                                  // +0x14
};

struct JobQueueDynamicData
{
	int        m_w00;                             // +0x00
	int        m_w04;                             // +0x04
	int        m_w08;                             // +0x08
	int        m_w0c;                             // +0x0c
	hkQueueHdr m_queues[3];                       // +0x10..+0x57

	~JobQueueDynamicData();                       // 0x010a59b0
};

// @ 0x010a59b0
JobQueueDynamicData::~JobQueueDynamicData()
{
	// Walk +0x58 backwards in 0x18 steps, freeing each queue's buffer.
	int* p = (int*)((char*)this + 0x58);
	for (int i = 3; i != 0; --i) {
		int count = p[-5];          // the queue's count at (p - 0x14)
		p = (int*)((char*)p - 0x18);
		if (count != 0) {
			g_hkMemoryInstance->deallocateChunk((void*)p[0], count << 7, 0x14);
		}
	}
}

// ---------------------------------------------------------------------------
// hkJobQueue ctor / worker-push / DynamicData construction.
extern "C" __declspec(dllimport) int __stdcall InitializeCriticalSectionAndSpinCount(void* cs, unsigned spin);   // kernel32

extern "C" void* hkChunkAlloc(int nbytes);        // 0x006abeb0

// @ 0x010a5a90
hkJobQueue* hkJobQueue::ctor()
{
	InitializeCriticalSectionAndSpinCount(this, 0);
	m_semA.ctor(0, 0x3e8);
	m_semB.ctor(0, 0x3e8);
	m_byte44 = 0;

	JobQueueDynamicData* d = (JobQueueDynamicData*)hkChunkAlloc(0x60);
	if (d != 0) {
		d->m_queues[0].m_data = 0; d->m_queues[0].m_size = 0; d->m_queues[0].m_capacity = 0;
		d->m_queues[0].m_head = 0; d->m_queues[0].m_tail = 0; d->m_queues[0].m_count = 0;
		d->m_queues[1].m_data = 0; d->m_queues[1].m_size = 0; d->m_queues[1].m_capacity = 0;
		d->m_queues[1].m_head = 0; d->m_queues[1].m_tail = 0; d->m_queues[1].m_count = 0;
		d->m_queues[2].m_data = 0; d->m_queues[2].m_size = 0; d->m_queues[2].m_capacity = 0;
		d->m_queues[2].m_head = 0; d->m_queues[2].m_tail = 0; d->m_queues[2].m_count = 0;
	}
	m_dynamic40 = d;

	m_dynamic40->m_w04 = 0;
	m_dynamic40->m_w08 = 0;
	m_dynamic40->m_w00 = 0;

	int cap = m_dynamic40->m_queues[1].m_capacity;
	if (cap < 0x80)
		cap = 0x80;
	if (m_dynamic40->m_queues[1].m_data != 0)
		g_hkMemoryInstance->deallocateChunk((void*)m_dynamic40->m_queues[1].m_data,
		                                    m_dynamic40->m_queues[1].m_size << 7, 0x14);
	m_dynamic40->m_queues[1].m_data = (int)g_hkMemoryInstance->allocateChunk(cap << 7, 0x14);
	m_dynamic40->m_queues[1].m_size = cap;

	m_b50 = 3; m_b51 = 0; m_b52 = 1; m_b53 = 2; m_b54 = 3;
	m_b55 = 1; m_b56 = 0; m_b57 = 2; m_b58 = 1; m_b59 = 2;
	return this;
}

// ---------------------------------------------------------------------------
// hkCriticalSection enter/leave
struct hkCriticalSection { void enter(); };                       // 0x0107f820 (__thiscall)
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);   // kernel32

struct hkBQueueEntry { uint32_t m_d[0x80 / 4]; };   // 0x80-byte job-queue entry

struct hkJobQueueFull { };   // not used

// @ 0x010a5ba0
void hkJobQueue::pushEntry(void* entry, int front, int which)
{
	((hkCriticalSection*)this)->enter();
	JobQueueDynamicData* d = m_dynamic40;

	if (front == 0)
		((hkQueue<hkBQueueEntry>*)((char*)d + which * 0x18 + 0x10))->pushBack(*(hkBQueueEntry*)entry);
	else
		((hkQueue<hkBQueueEntry>*)((char*)d + which * 0x18 + 0x10))->pushFront(*(hkBQueueEntry*)entry);

	if (which == 2) {
		if (d->m_w08 != 0) {
			--d->m_w08;
			m_semB.release(1);
		}
	} else {
		if (d->m_w04 != 0) {
			--d->m_w04;
			m_semA.release(1);
		}
	}
	m_w18 = -1;
	m_w1c = -1;
	LeaveCriticalSection(this);
}
