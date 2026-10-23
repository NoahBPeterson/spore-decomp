// Slice s010a5c20 -- Havok 3.1.0 job-queue entry points (0x010a5c20..0x010a6770).
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast.
//
//  010a5c20  hkJobQueue::finishJobAndGetNextJob   (this=ecx, 5 stack args, ret 0x14)
//  010a6110  hkJobQueue::finishAddAndGetNextJob   (this=ecx, 5 stack args, ret 0x14)
//  010a65e0  hkJobQueue::~hkJobQueue
//  010a6620  hkJobQueue::getNextJob               (this=ecx, 3 stack args, ret 0xc)
//  010a6640  hkWorldConstraintUtil::removeConstraint
//  010a6770  hkArray<hkConstraintInternal>::insertAt
//
// Both big functions are the classic Havok worker-thread entry points: enter the job queue's
// critical section, fold the just-finished job back into its queue, pick the next runnable job of
// the calling thread type (skipping the "wait for signal" queue when the thread is not the master),
// run it through the queue's job callback (re-queueing it at the head when the callback says the
// job is not ready), and otherwise block on the per-type semaphore.  Every step is wrapped in the
// Havok monitor-stream timer macros.
#include "types.h"

extern "C"
{
	__declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
	__declspec(dllimport) int __stdcall TlsSetValue(unsigned long index, void* value);
	__declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);
	__declspec(dllimport) void __stdcall DeleteCriticalSection(void* cs);
	__declspec(dllimport) int __stdcall InitializeCriticalSectionAndSpinCount(void* cs, unsigned long spin);
	__declspec(dllimport) void* __stdcall CreateSemaphoreA(void* attr, long initial, long max, const char* name);
	__declspec(dllimport) int __stdcall CloseHandle(void* h);
	void* __cdecl memmove(void* dst, const void* src, unsigned long n);
}

// ---- monitor-stream timers (same macros as the other Havok slices) --------------------------------
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorEndTag[];                // 0x0149cc34 "Et"

#define HK_TIMER_SET_TIME(field) { unsigned int ticks_; __asm { rdtsc } __asm { mov ticks_, eax } field = ticks_; }

struct hkMonitorCommand { const char* m_commandAndMonitor; unsigned int m_time0; unsigned int m_time1; };

#define HK_TIMER_BEGIN(name) do { \
	void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
	if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
		hkMonitorCommand* c_ = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
		c_->m_commandAndMonitor = "Tt" name; \
		HK_TIMER_SET_TIME(c_->m_time0) \
		TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_END() do { \
	void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
	if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
		hkMonitorCommand* c_ = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
		c_->m_commandAndMonitor = hkMonitorEndTag; \
		HK_TIMER_SET_TIME(c_->m_time0) \
		TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)

// ---- memory --------------------------------------------------------------------------------------
class hkMemory
{
public:
	virtual void* slot00();
	virtual void* slot04();
	virtual void* slot08();
	virtual void* slot0c();
	virtual void* allocate(int nbytes, int cl);                    // 0x10
	virtual void  deallocate(void* p, int nbytes, int cl);         // 0x14
	static hkMemory* s_instance;                                   // 0x016e4178
	static hkMemory& getInstance() { return *s_instance; }
};

// ---- hkSemaphore ---------------------------------------------------------------------------------
class hkSemaphore
{
public:
	hkSemaphore(int initial, int max);        // 0x01209800
	__declspec(noinline) ~hkSemaphore();      // 0x01209820
	void acquire();                           // 0x01209830
	void release(int n);                      // 0x01209840
	void* m_handle;                           // +0x00
};

// ---- hkCriticalSection ---------------------------------------------------------------------------
class hkCriticalSection
{
public:
	void enter();                             // 0x0107f820
	void leave() { m_owner = 0xffffffffffffffffull; LeaveCriticalSection(m_cs); }
	~hkCriticalSection() { DeleteCriticalSection(m_cs); }
	char m_cs[0x18];                          // +0x00 CRITICAL_SECTION
	unsigned __int64 m_owner;                 // +0x18 (thread id while locked, -1 otherwise)
};

// ---- job entries ---------------------------------------------------------------------------------
struct hkJobQueueEntry
{
	unsigned char m_data[0x80];               // opaque 0x80-byte job record
};

// The job callbacks operate on a wrapper: an 8-byte routing header followed by the queued record.
struct hkJobLocal
{
	int m_type;                               // +0x00 queue selector (0..2)
	int m_mode;                               // +0x04 0 = push to the head, else the tail
	hkJobQueueEntry m_entry;                  // +0x08
};

// ---- hkQueue<T> ----------------------------------------------------------------------------------
template <typename T>
class hkQueue
{
public:
	T*   m_data;                              // +0x00
	int  m_capacity;                          // +0x04
	int  m_size;                              // +0x08
	int  m_head;                              // +0x0c
	int  m_tail;                              // +0x10
	int  m_numElements;                       // +0x14

	void reserve(int n);                      // 0x010a5890
	void grow();                              // 0x010a58f0
};

// ---- hkJobQueue ----------------------------------------------------------------------------------
struct hkJobQueueDynamicData
{
	int m_unk00;                              // +0x00 jobs checked out
	int m_unk04;                              // +0x04
	int m_unk08;                              // +0x08
	int m_unk0c;                              // +0x0c
	hkQueue<hkJobQueueEntry> m_queues[3];     // +0x10, +0x28, +0x40

	__declspec(noinline) ~hkJobQueueDynamicData();   // 0x010a59b0
};

struct hkJobThreadTypeJobs
{
	unsigned char m_count;                    // +0x00
	unsigned char m_types[3];                 // +0x01
};

class hkJobQueue
{
public:
	int  getNextJob(int threadType, hkJobQueueEntry& job, int wait);                       // 0x010a6620
	int  finishJobAndGetNextJob(int threadType, const hkJobQueueEntry* oldJob,
	                            hkJobQueueEntry& jobOut, void* threadData, int wait);      // 0x010a5c20
	int  finishAddAndGetNextJob(int jobType, int mode, int threadType,
	                            hkJobQueueEntry& job, int wait);                           // 0x010a6110
	void releaseSemaphores(hkJobQueueDynamicData* dd);                                     // 0x010a5830
	__declspec(noinline) ~hkJobQueue();                                                    // 0x010a65e0

	hkCriticalSection m_criticalSection;      // +0x00
	char m_pad20[0x20];                       // +0x20
	hkJobQueueDynamicData* m_dynamicData;     // +0x40
	unsigned char m_unk44;                    // +0x44
	char m_pad45[3];                          // +0x45
	hkSemaphore m_sem48;                      // +0x48
	hkSemaphore m_sem4c;                      // +0x4c
	hkJobThreadTypeJobs m_threadTypeJobs[3];  // +0x50
	int (*m_runJob)(hkJobQueueEntry* job, hkJobQueueEntry& jobOut);                        // +0x5c
	int (*m_finishJob)(const hkJobQueueEntry* oldJob, hkJobLocal* out, void* threadData);  // +0x60
};

// ---- constraint world / array --------------------------------------------------------------------
class hkConstraintInstance;
class hkEntity;

class hkConstraintInternalOwner
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(void* local);
};

class hkConstraintOwner
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(hkConstraintInstance* c, void* local);
};

struct hkConstraintInternal
{
	void* m_ptr00;                            // +0x00
	void* m_ptr04;                            // +0x04 body A
	void* m_ptr08;                            // +0x08 body B
	hkConstraintInternalOwner* m_p0c;         // +0x0c
	unsigned char  m_b10;                     // +0x10
	unsigned char  m_b11;                     // +0x11 selector (0 or 1)
	unsigned short m_w12;                     // +0x12 index
	unsigned short m_w14;                     // +0x14 offset
	unsigned short m_w16;                     // +0x16
	void* m_p18;                              // +0x18
};

class hkConstraintInstance
{
public:
	virtual void s0(int);
	short m_unk04;                            // +0x04
	short m_refCount;                         // +0x06
	hkConstraintOwner* m_owner;               // +0x08
	char m_pad0c[0x18];                       // +0x0c
	hkConstraintInternal* m_internal;         // +0x24
};

struct hkEntityLayout
{
	char m_pad00[0x70];
	hkConstraintInternal* m_constraints;      // +0x70
	int  m_numConstraints;                    // +0x74
	int  m_unk78;                             // +0x78
	int* m_map7c;                             // +0x7c
	int  m_mapSize80;                         // +0x80
	int  m_unk84;                             // +0x84
	int  m_unk88;                             // +0x88
	int  m_unk8c;                             // +0x8c
};

template <typename T>
class hkArray
{
public:
	T*  m_data;                               // +0x00
	int m_size;                               // +0x04
	int m_capacityAndFlags;                   // +0x08
	void insertAt(int index, const hkArray<T>& src);   // 0x010a6770
	int  getSize() const { return m_size; }
	T&   operator[](int i) { return m_data[i]; }
	void popBack() { m_size--; }
};

class hkWorldConstraintUtil
{
public:
	static void removeConstraint(hkConstraintInstance* c);   // 0x010a6640
};

struct hkArrayUtil
{
	static void _reserveExactly(void* array, int newCapacity, int elemSize);   // 0x0107f4a0
};

// =================================================================================================
// 0x010a5c20 -- fold the finished job back in, then hand out the next runnable job
// =================================================================================================
// @ 0x010a5c20
int hkJobQueue::finishJobAndGetNextJob(int threadType, const hkJobQueueEntry* oldJob,
                                       hkJobQueueEntry& jobOut, void* threadData, int wait)
{
	HK_TIMER_BEGIN("GetNextJob");
	hkJobLocal local;
	for (;;)
	{
		((hkCriticalSection*)this)->enter();
		hkJobQueueDynamicData* dd = m_dynamicData;
		bool jobFinished = false;
		if (oldJob)
		{
			if (m_finishJob(oldJob, &local, threadData) == 0)
			{
				int type = local.m_type;
				if (type == 2)
					dd->m_unk0c--;
				hkQueue<hkJobQueueEntry>& q = dd->m_queues[type];
				if (local.m_mode == 0)
				{
					if (q.m_size + q.m_numElements >= q.m_capacity)
						q.grow();
					if (q.m_head == 0)
						q.m_head = q.m_capacity;
					q.m_head--;
					*(hkJobQueueEntry*)((char*)q.m_data + q.m_head * 0x80) = local.m_entry;
				}
				else
				{
					if (q.m_size + q.m_numElements >= q.m_capacity)
						q.grow();
					else if (q.m_tail == q.m_capacity)
						q.m_tail = 0;
					*(hkJobQueueEntry*)((char*)q.m_data + q.m_tail * 0x80) = local.m_entry;
					q.m_tail++;
				}
				q.m_numElements++;
				jobFinished = 1;
			}
			dd->m_unk00--;
			oldJob = 0;
		}

		int found = 1;
		int numTypes = m_threadTypeJobs[threadType].m_count;
		if (numTypes > 0)
		{
			for (int i = 0; i < numTypes; i++)
			{
				int jobType = m_threadTypeJobs[threadType].m_types[i];
				hkQueue<hkJobQueueEntry>& q = dd->m_queues[jobType];
				if (threadType != 2 && jobType == 2 && dd->m_unk08 >= q.m_numElements)
					continue;
				if (q.m_numElements == 0)
					continue;
				*(hkJobQueueEntry*)((char*)q.m_data + q.m_head * 0x80);
				hkJobQueueEntry popped = *(hkJobQueueEntry*)((char*)q.m_data + q.m_head * 0x80);
				if (++q.m_head == q.m_capacity)
					q.m_head = 0;
				q.m_numElements--;
				if (m_runJob(&popped, jobOut) == 1)
				{
					if (q.m_size + q.m_numElements >= q.m_capacity)
						q.grow();
					if (q.m_head == 0)
						q.m_head = q.m_capacity;
					q.m_head--;
					*(hkJobQueueEntry*)((char*)q.m_data + q.m_head * 0x80) = popped;
					q.m_numElements++;
				}
				dd->m_unk00++;
				found = 0;
				break;
			}
		}

		if (jobFinished)
		{
			if (local.m_type == 2)
			{
				if (dd->m_unk08 != 0)
				{
					dd->m_unk08--;
					m_sem4c.release(1);
				}
			}
			else if (dd->m_unk04 != 0)
			{
				dd->m_unk04--;
				m_sem48.release(1);
			}
		}

		if (found == 0)
		{
			((hkCriticalSection*)this)->leave();
			HK_TIMER_END();
			return 0;
		}
		if (dd->m_unk00 == 0 && dd->m_queues[0].m_numElements == 0 &&
		    dd->m_queues[1].m_numElements == 0 && dd->m_queues[2].m_numElements == 0)
		{
			if (threadType != 2)
				releaseSemaphores(dd);
			((hkCriticalSection*)this)->leave();
			HK_TIMER_END();
			return 2;
		}
		if (threadType == 2 && dd->m_unk0c == dd->m_unk08)
		{
			((hkCriticalSection*)this)->leave();
			HK_TIMER_END();
			return 2;
		}
		if (wait == 1)
		{
			((hkCriticalSection*)this)->leave();
			return 1;
		}
		if (threadType == 2)
		{
			dd->m_unk08++;
			((hkCriticalSection*)this)->leave();
			HK_TIMER_BEGIN("WaitForSignal");
			m_sem4c.acquire();
		}
		else
		{
			dd->m_unk04++;
			((hkCriticalSection*)this)->leave();
			HK_TIMER_BEGIN("WaitForSignal");
			m_sem48.acquire();
		}
		HK_TIMER_END();
	}
}

// =================================================================================================
// 0x010a6110 -- add one job, then hand out the next runnable job
// =================================================================================================
// @ 0x010a6110
int hkJobQueue::finishAddAndGetNextJob(int jobType, int mode, int threadType,
                                       hkJobQueueEntry& job, int wait)
{
	HK_TIMER_BEGIN("GetNextJob");
	hkJobLocal local;
	bool add = true;
	for (;;)
	{
		((hkCriticalSection*)this)->enter();
		hkJobQueueDynamicData* dd = m_dynamicData;
		if (add)
		{
			if (jobType == 2)
				dd->m_unk0c--;
			hkQueue<hkJobQueueEntry>& q = dd->m_queues[jobType];
			if (mode == 0)
			{
				if (q.m_size + q.m_numElements >= q.m_capacity)
					q.grow();
				if (q.m_head == 0)
					q.m_head = q.m_capacity;
				q.m_head--;
				*(hkJobQueueEntry*)((char*)q.m_data + q.m_head * 0x80) = job;
			}
			else
			{
				if (q.m_size + q.m_numElements >= q.m_capacity)
					q.grow();
				else if (q.m_tail == q.m_capacity)
					q.m_tail = 0;
				*(hkJobQueueEntry*)((char*)q.m_data + q.m_tail * 0x80) = job;
				q.m_tail++;
			}
			q.m_numElements++;
			dd->m_unk00--;
		}

		int found = 1;
		int numTypes = m_threadTypeJobs[threadType].m_count;
		if (numTypes > 0)
		{
			for (int i = 0; i < numTypes; i++)
			{
				int jt = m_threadTypeJobs[threadType].m_types[i];
				hkQueue<hkJobQueueEntry>& q = dd->m_queues[jt];
				if (threadType != 2 && jt == 2 && dd->m_unk08 >= q.m_numElements)
					continue;
				if (q.m_numElements == 0)
					continue;
				hkJobQueueEntry popped = *(hkJobQueueEntry*)((char*)q.m_data + q.m_head * 0x80);
				if (++q.m_head == q.m_capacity)
					q.m_head = 0;
				q.m_numElements--;
				if (m_runJob(&popped, job) == 1)
				{
					if (q.m_size + q.m_numElements >= q.m_capacity)
						q.grow();
					if (q.m_head == 0)
						q.m_head = q.m_capacity;
					q.m_head--;
					*(hkJobQueueEntry*)((char*)q.m_data + q.m_head * 0x80) = popped;
					q.m_numElements++;
				}
				dd->m_unk00++;
				found = 0;
				break;
			}
		}

		if (add)
		{
			if (jobType == 2)
			{
				if (dd->m_unk08 != 0)
				{
					dd->m_unk08--;
					m_sem4c.release(1);
				}
			}
			else if (dd->m_unk04 != 0)
			{
				dd->m_unk04--;
				m_sem48.release(1);
			}
		}
		add = 0;

		if (found == 0)
		{
			((hkCriticalSection*)this)->leave();
			HK_TIMER_END();
			return 0;
		}
		if (dd->m_unk00 == 0 && dd->m_queues[0].m_numElements == 0 &&
		    dd->m_queues[1].m_numElements == 0 && dd->m_queues[2].m_numElements == 0)
		{
			if (threadType != 2)
				releaseSemaphores(dd);
			((hkCriticalSection*)this)->leave();
			HK_TIMER_END();
			return 2;
		}
		if (threadType == 2 && dd->m_unk0c == dd->m_unk08)
		{
			((hkCriticalSection*)this)->leave();
			HK_TIMER_END();
			return 2;
		}
		if (wait == 1)
		{
			((hkCriticalSection*)this)->leave();
			return 1;
		}
		if (threadType == 2)
		{
			dd->m_unk08++;
			((hkCriticalSection*)this)->leave();
			HK_TIMER_BEGIN("WaitForSignal");
			m_sem4c.acquire();
		}
		else
		{
			dd->m_unk04++;
			((hkCriticalSection*)this)->leave();
			HK_TIMER_BEGIN("WaitForSignal");
			m_sem48.acquire();
		}
		HK_TIMER_END();
	}
}

// =================================================================================================
// 0x010a65e0 -- hkJobQueue destructor
// =================================================================================================
// @ 0x010a65e0
hkJobQueue::~hkJobQueue()
{
	hkJobQueueDynamicData* dd = m_dynamicData;
	if (dd)
	{
		dd->~hkJobQueueDynamicData();
		::operator delete(dd);
	}
}

// @ 0x010a6620
int hkJobQueue::getNextJob(int threadType, hkJobQueueEntry& job, int wait)
{
	return finishJobAndGetNextJob(threadType, 0, job, 0, wait);
}

// =================================================================================================
// 0x010a6640 -- hkWorldConstraintUtil::removeConstraint
// =================================================================================================
// @ 0x010a6640
void hkWorldConstraintUtil::removeConstraint(hkConstraintInstance* c)
{
	hkConstraintInternal* internal = c->m_internal;
	*(unsigned char*)((char*)c->m_owner + 0x26) = 1;
	unsigned char local10[16];
	internal->m_p0c->s8(local10);
	c->m_owner->s4(c, local10);
	c->m_owner = 0;

	unsigned short idx = internal->m_w12;
	hkEntityLayout* a = (hkEntityLayout*)((void**)internal)[2 - internal->m_b11];
	hkArray<hkConstraintInstance*>& slave = *(hkArray<hkConstraintInstance*>*)&a->m_map7c;
	int moved = (int)slave.m_data[slave.m_size - 1];
	slave.m_data[idx] = (hkConstraintInstance*)moved;
	slave.popBack();
	*(unsigned short*)(*(int*)(moved + 0x24) + 0x12) = idx;

	hkEntityLayout* b = (hkEntityLayout*)((void**)internal)[internal->m_b11 + 1];
	void* dst = internal->m_p18;
	int negOff = 0;
	if (dst)
	{
		negOff = -(int)internal->m_w14;
		void* src = (char*)dst + internal->m_w14;
		int size = b->m_unk8c + b->m_unk88 - (int)src;
		memmove(dst, src, size);
		b->m_unk8c -= internal->m_w14;
		internal->m_p18 = 0;
	}
	c->m_internal = 0;

	int n = b->m_numConstraints;
	hkConstraintInternal* end = (hkConstraintInternal*)((char*)b->m_constraints + n * 0x1c - 0x1c);
	for (hkConstraintInternal* p = internal; p < end; p = (hkConstraintInternal*)((char*)p + 0x1c))
	{
		*(hkConstraintInternal*)p = *(hkConstraintInternal*)((char*)p + 0x1c);
		*(int**)((char*)p->m_ptr00 + 0x24) = (int*)p;
		p->m_p18 = p->m_p18 ? (void*)((char*)p->m_p18 + negOff) : 0;
	}
	b->m_numConstraints--;

	if (c->m_unk04 != 0)
	{
		c->m_refCount--;
		if (c->m_refCount == 0)
			c->s0(1);
	}
}

// =================================================================================================
// 0x010a6770 -- hkArray<hkConstraintInternal>::insertAt
// =================================================================================================
// @ 0x010a6770
template <typename T>
void hkArray<T>::insertAt(int index, const hkArray<T>& src)
{
	int numtoinsert = src.m_size;
	int newSize = m_size + numtoinsert;
	int numtomove = m_size - index;
	if ((m_capacityAndFlags & 0x3fffffff) < newSize)
	{
		int newCap = (m_capacityAndFlags & 0x3fffffff) * 2;
		if (newCap <= newSize)
			newCap = newSize;
		hkArrayUtil::_reserveExactly(this, newCap, 0x1c);
	}
	T* data = m_data;
	T* dst = data + index + numtoinsert;
	T* s = data + index;
	for (int i = numtomove - 1; i >= 0; --i)
		dst[i] = s[i];
	T* d = data + index;
	T* sd = src.m_data;
	for (int j = numtoinsert - 1; j >= 0; --j)
		d[j] = sd[j];
	m_size = newSize;
}

template void hkArray<hkConstraintInternal>::insertAt(int, const hkArray<hkConstraintInternal>&);

// =================================================================================================
// Out-of-line helpers referenced by the code above (own slices).
// =================================================================================================
__declspec(noinline) hkJobQueueDynamicData::~hkJobQueueDynamicData()
{
	for (int i = 2; i >= 0; --i)
	{
		hkQueue<hkJobQueueEntry>& q = m_queues[i];
		if (q.m_data)
			hkMemory::getInstance().deallocate(q.m_data, q.m_capacity * 0x80, 0x14);
	}
}

template <typename T>
void hkQueue<T>::reserve(int n)
{
	if (m_capacity >= n)
		return;
	T* mem = (T*)hkMemory::getInstance().allocate(n * (int)sizeof(T), 0x14);
	int count = m_numElements;
	for (int i = 0; i < count; ++i)
		mem[i] = m_data[(m_head + i) % (m_capacity ? m_capacity : 1)];
	if (m_capacity != 0)
		hkMemory::getInstance().deallocate(m_data, m_capacity * (int)sizeof(T), 0x14);
	m_data = mem;
	m_capacity = n;
	m_head = 0;
	m_tail = count;
}

template <typename T>
void hkQueue<T>::grow()
{
	int numElems = m_numElements;
	int extra = (m_tail > m_head) ? m_tail : 0;
	int newCap;
	if (m_capacity == 0)
		newCap = (m_size < 8) ? 8 : m_size;
	else
	{
		unsigned int x = (unsigned int)((m_size + m_capacity * 2 + extra) << 7);
		unsigned int p = 1;
		while (p < x)
			p <<= 1;
		newCap = (int)(p >> 7);
	}
	reserve(newCap);
	if (extra != 0)
	{
		int a = numElems;
		int d = 0;
		for (int i = 0; i < extra; ++i)
		{
			*(T*)((char*)m_data + a * 0x80) = *(T*)((char*)m_data + d * 0x80);
			d++;
			a++;
		}
	}
	m_tail = numElems + extra;
}

template class hkQueue<hkJobQueueEntry>;
