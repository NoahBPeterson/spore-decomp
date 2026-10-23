// flags: /O2 /MD /Gy /TP /vc71
// Slice s010f0580: Havok continuous simulation, local-space (hkLs_*) collision
// bookkeeping and the ToI event list of hkContinuousSimulation.
//
// Layouts are the raw 32-bit byte offsets seen in the binary (the Havok headers
// are not available here; names are for readability only).
#include "types.h"
#include <stddef.h>
#include <math.h>

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);

inline void* operator new(unsigned int, void* p) throw() { return p; }

// ---- TLS globals ------------------------------------------------------------------------------------------------
unsigned long g_hkThreadMemoryTls;                 // 0x016e4174
void* g_hkMemoryInstance;                          // 0x016e4178

// ---- thread memory ----------------------------------------------------------------------------------------------
enum { HK_MEMORY_CLASS_ARRAY = 0x14 };
class hkThreadMemory
{
public:
	virtual void tm0();
	virtual void tm1();
	virtual void tm2();
	virtual void* onStackOverflow(int nbytes);   // 3 (+0xc)
	virtual void onStackUnderflow(void* p);      // 4 (+0x10)

	void deallocateChunk(void* p, int nbytes, int cl);   // 0x0107db10

	static __forceinline hkThreadMemory& getInstance() { return *(hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls); }

	__forceinline void* allocateStack(int nbytes)
	{
		int size = (nbytes + 0x10) & ~0xf;
		char* current = m_stackCurrent;
		char* next = current + size;
		if (next <= m_stackEnd)
		{
			m_stackCurrent = next;
			return current;
		}
		return onStackOverflow(size);
	}
	__forceinline void deallocateStack(void* p)
	{
		m_stackCurrent = (char*)p;
		if ((char*)p == m_stackBase)
			onStackUnderflow(p);
	}

	int m_pad04[7];
	char* m_stackCurrent;   // +0x20
	char* m_stackPrev;      // +0x24
	char* m_stackBase;      // +0x28
	char* m_stackEnd;       // +0x2c
};

// ---- arrays -----------------------------------------------------------------------------------------------------
struct hkArrayUtil
{
	static void _reserveExactly(void* arrayBase, int numElem, int elemSize);   // 0x0107f4a0
	static void _reserveMore(void* arrayBase, int elemSize);                   // 0x0107f530
};

template <typename T>
class hkArray
{
public:
	enum { CAPACITY_MASK = 0x3fffffff };
	T* m_data;
	int m_size;
	int m_capacityAndFlags;

	hkArray() : m_data(0), m_size(0), m_capacityAndFlags((int)0x80000000) {}
	int getSize() const { return m_size; }
	T* begin() { return m_data; }
	const T* begin() const { return m_data; }
	T& operator[](int i) { return m_data[i]; }
	const T& operator[](int i) const { return m_data[i]; }
	__forceinline void pushBack(const T& t)
	{
		if (m_size == (m_capacityAndFlags & CAPACITY_MASK))
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		m_data[m_size] = t;
		m_size++;
	}
	__forceinline T& expandOne()
	{
		if (m_size == (m_capacityAndFlags & CAPACITY_MASK))
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		return m_data[m_size++];
	}
};

template <typename T>
struct hkLocalBuffer
{
	__forceinline explicit hkLocalBuffer(int n) { m_p = (T*)hkThreadMemory::getInstance().allocateStack(n * (int)sizeof(T)); }
	__forceinline ~hkLocalBuffer() { hkThreadMemory::getInstance().deallocateStack(m_p); }
	T* begin() { return m_p; }
	T* m_p;
};

template <typename T>
class hkFixedArray
{
public:
	T* m_data;   // +0x00
	int m_size;  // +0x04
};

// ---- Havok game types (raw byte offsets) ------------------------------------------------------------------------
struct hkStepInfo
{
	float m_startTime;      // +0x00
	float m_endTime;        // +0x04
	float m_deltaTime;      // +0x08
	float m_invDeltaTime;   // +0x0c
};

class hkWorld;
struct hkEntity;

struct hkProcessCollisionInput
{
	int m_00;                            // +0x00
	int m_04;                            // +0x04
	int m_08;                            // +0x08
	char m_0c;                           // +0x0c
	char m_pad0d[3];
	hkStepInfo m_stepInfo;               // +0x10
	int m_20;                            // +0x20
	int m_24;                            // +0x24
	void* m_28;                          // +0x28
	char m_pad2c[0x3030 - 0x2c];
	int m_3030;                          // +0x3030
	int m_3034;                          // +0x3034
	int m_3038;                          // +0x3038
	int m_303c;                          // +0x303c
};

struct hkAgentNnEntry
{
	int m_00;                            // +0x00
	int m_04;
	signed char m_08;                    // +0x08
	char m_pad09[7];
	void* m_10;                          // +0x10 (object with the virtual manifold callback)
	int m_14;                            // +0x14
	int m_18;                            // +0x18
};

class hkConstraintInstance
{
public:
	enum ConstraintPriority { PRIORITY_INVALID = 0 };
};

struct hkConstraintSchemaInfo
{
	void* m_00;      // +0x00 (points at the constraint schema; +0x18 = priority byte, +0x24 = agent)
	int m_04;        // +0x04
	float m_08;      // +0x08
};
typedef char hkConstraintSchemaInfo_size_check[(sizeof(hkConstraintSchemaInfo) == 0xc) ? 1 : -1];

// The manifold callback object reachable through hkAgentNnEntry::m_10; slot 5 (+0x14) removes a manifold.
class hkAgentManifoldCallback
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void updateManifold(int a, int b, hkProcessCollisionInput& input, void* workspace);   // +0x14
};

__declspec(align(16)) struct hkAgentNnMachine_ProcessAgentContext
{
	void* m_data;               // +0x00
	int m_pad04[11];            // +0x04 .. +0x30
	char m_buffer[0x3004];      // +0x30 .. +0x3034
	int m_3034;                 // +0x3034
	int m_pad38[2];             // +0x3038
	int m_3040;                 // +0x3040
};

void __cdecl hkAgentNnMachine_processAgent(hkAgentNnEntry* entry, hkProcessCollisionInput* input, hkAgentNnMachine_ProcessAgentContext* context);   // 0x10fc180

// hkVector4::setRotatedDir(const hkRotation&, const hkVector4&) -- __thiscall on the destination vector.
class hkVector4Stub
{
public:
	void setRotatedDir(const void* rot, const void* dir);   // 0x10814a0
};

// ---- ToI event list ---------------------------------------------------------------------------------------------
__declspec(align(16)) struct hkContinuousSimulation_ToiEntry
{
	float m_time;      // +0x00
	void* m_a;         // +0x04 (entity that owns the manifold)
	void* m_b;         // +0x08
	int m_0c;          // +0x0c
	int m_10;          // +0x10
	int m_14;          // +0x14
	int m_18;          // +0x18
	int m_1c;          // +0x1c
	int m_20;          // +0x20
	int m_24;          // +0x24
	int m_28;          // +0x28
	int m_2c;          // +0x2c
	int m_30;          // +0x30
	int m_34;          // +0x34
	int m_38;          // +0x38
	int m_3c;          // +0x3c
};
typedef char hkContinuousSimulation_ToiEntry_size_check[(sizeof(hkContinuousSimulation_ToiEntry) == 0x40) ? 1 : -1];

// Sliding an event list element down over a removed slot leaves the +0x1c field alone.
__forceinline void hkToiEntryMoveLast(hkContinuousSimulation_ToiEntry& d, const hkContinuousSimulation_ToiEntry& s)
{
	d.m_time = s.m_time;
	d.m_a = s.m_a;
	d.m_b = s.m_b;
	d.m_0c = s.m_0c;
	d.m_10 = s.m_10;
	d.m_14 = s.m_14;
	d.m_18 = s.m_18;
	d.m_20 = s.m_20;
	d.m_24 = s.m_24;
	d.m_28 = s.m_28;
	d.m_2c = s.m_2c;
	d.m_30 = s.m_30;
	d.m_34 = s.m_34;
	d.m_38 = s.m_38;
	d.m_3c = s.m_3c;
}

struct hkContactPointRemovedEvent
{
	unsigned short m_00;   // +0x00 (0xffff)
	unsigned short m_pad02;
	void* m_04;            // +0x04
	void* m_08;            // +0x08
	void* m_0c;            // +0x0c
	int m_10;              // +0x10
	int m_14;              // +0x14
};

struct hkWorldCallbackUtil
{
	static void fireContactPointRemoved(hkWorld* world, hkContactPointRemovedEvent& event);   // 0x109f160
};
struct hkEntityCallbackUtil
{
	static void fireContactPointRemovedInternal(hkEntity* entity, hkContactPointRemovedEvent& event);   // 0x109e8e0
};

enum hkStepResult { HK_STEP_RESULT_NONE = 0, HK_STEP_RESULT_SUCCESS = 1, HK_STEP_RESULT_QUIT = 2 };

class hkWorld
{
public:
	int m_00;             // +0x00
	int m_04;
	int m_08;
	float m_0c;           // +0x0c (current time)
	int m_10;
	int m_14;
	float m_18;           // +0x18 (till)
	int m_1c;
	int m_20;
	char m_pad24[0x78 - 0x24];
	void* m_78;           // +0x78 (step-info holder)
	char m_pad7c[0x88 - 0x7c];
	int m_88;             // +0x88
	int m_8c;             // +0x8c (active ToI counter)
	int m_90;
	char m_94;            // +0x94
	char m_pad95[0x170 - 0x95];
	int m_170;            // +0x170 (world step info)
	int m_174;
	int m_178;
	int m_17c;

	void executePendingOperations();   // 0x1082bf0
};

class hkContinuousSimulation
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void toiEvent(hkWorld* world, hkContinuousSimulation_ToiEntry* event, int a3);   // +0x40

	hkStepResult handleAllToisTill(hkWorld* world, float till);   // 0x010f0830
	void addToiEvent(hkProcessCollisionInput* input, hkAgentNnEntry* agent);   // 0x010f0b00
	void FUN_010f0bb0(void** entities, int numEntities);                        // 0x010f0bb0

	int m_04;                              // +0x04
	int m_08;                              // +0x08
	int m_0c;
	int m_10;
	int m_14;
	hkArray<hkContinuousSimulation_ToiEntry> m_events;   // +0x18
	int m_24;
	int m_28;                              // +0x28
};

// The pointer set used to filter the ToI events (raw member offsets).
class hkPointerMap
{
public:
	hkPointerMap();                      // 0x0107de00
	void reserve(int n);                 // 0x0107e5b0
	void insert(int key, int value);     // 0x0107de70
	int find(int key);                   // 0x0107def0
	~hkPointerMap();                     // 0x0107de50

	int m_00;
	int m_04;
	int m_08;                            // "not found" sentinel returned by find()
	int m_0c;
	int m_10;
};

// ======================================================================
// 0x10f0580   run the agent machine for one entry and flush its manifold
// ======================================================================
// @ 0x010f0580 hkLs_updateManifold
void hkLs_updateManifold(hkAgentNnEntry* entry, hkProcessCollisionInput& input)
{
	hkAgentNnMachine_ProcessAgentContext context;
	context.m_data = context.m_buffer;
	context.m_3034 = 0x7f7fffee;
	context.m_3040 = 0;
	input.m_28 = (void*)(input.m_00 + 0x1b40);
	input.m_0c = *(char*)(input.m_00 + 0x1a24 + entry->m_08 * 0x3c);
	hkAgentNnMachine_processAgent(entry, &input, &context);
	if (context.m_data != context.m_buffer)
	{
		hkAgentManifoldCallback* cb = (hkAgentManifoldCallback*)entry->m_10;
		cb->updateManifold(entry->m_14, entry->m_18, input, &context);
	}
}

// ======================================================================
// 0x10f0610   move the schemas whose entities are not fixed to the front
// ======================================================================
// @ 0x010f0610 hkLs_sortSchemasOfFixedEntitiesFirst
extern "C" void hkLs_sortSchemasOfFixedEntitiesFirst(hkArray<hkConstraintSchemaInfo>& schemas, int& numFixed, int startIndex)
{
	for (int i = schemas.m_size - startIndex; i < schemas.m_size; i++)
	{
		void** p = *(void***)((char*)*(void**)&schemas.m_data[i] + 0x24);
		if (*(char*)((char*)p[1] + 0x9a) != 0 || *(char*)((char*)p[2] + 0x9a) != 0)
		{
			hkConstraintSchemaInfo* dst = &schemas.m_data[numFixed++];
			hkConstraintSchemaInfo* src = &schemas.m_data[i];
			hkConstraintSchemaInfo tmp = *dst;
			*dst = *src;
			*src = tmp;
		}
	}
}

// ======================================================================
// 0x10f06d0   move the schemas whose entities are frozen to the front
// ======================================================================
// @ 0x010f06d0 hkLs_sortSchemasOfFrozenEntitiesFirst
extern "C" void hkLs_sortSchemasOfFrozenEntitiesFirst(hkArray<hkConstraintSchemaInfo>& schemas, int& numFixed, const hkFixedArray<unsigned char>& flags)
{
	for (int i = numFixed; i < schemas.m_size; i++)
	{
		void** p = *(void***)((char*)*(void**)&schemas.m_data[i] + 0x24);
		if (flags.m_data[*(unsigned short*)((char*)p[1] + 0x94)] == 8 &&
		    flags.m_data[*(unsigned short*)((char*)p[2] + 0x94)] == 8)
		{
			int nf = numFixed++;
			hkConstraintSchemaInfo* dst = &schemas.m_data[nf];
			hkConstraintSchemaInfo* src = &schemas.m_data[i];
			hkConstraintSchemaInfo tmp = *dst;
			*dst = *src;
			*src = tmp;
		}
	}
}

// ======================================================================
// 0x10f0790   copy the entity velocities into the solver accumulators
// ======================================================================
// @ 0x010f0790 hkLs_copyVelocitiesToAccumulators
extern "C" void hkLs_copyVelocitiesToAccumulators(void* resources, hkArray<hkEntity*>& entities)
{
	for (int i = 0; i < entities.m_size; i++)
	{
		char* motion = *(char**)((char*)entities.m_data[i] + 0x58);
		char* acc = (char*)(*(int*)(motion + 8) + *(int*)((char*)resources + 0xc));

		*(int*)(acc + 0x10) = *(int*)(motion + 0xd0);
		*(int*)(acc + 0x14) = *(int*)(motion + 0xd4);
		*(int*)(acc + 0x18) = *(int*)(motion + 0xd8);
		*(int*)(acc + 0x1c) = *(int*)(motion + 0xdc);
		if (*(char*)(acc + 0xc) != 0)
		{
			*(int*)(acc + 0x20) = *(int*)(motion + 0xe0);
			*(int*)(acc + 0x24) = *(int*)(motion + 0xe4);
			*(int*)(acc + 0x28) = *(int*)(motion + 0xe8);
			*(int*)(acc + 0x2c) = *(int*)(motion + 0xec);
		}
		else
		{
			((hkVector4Stub*)(acc + 0x20))->setRotatedDir(acc + 0x50, motion + 0xe0);   // 0x10814a0
		}
	}
}

// ======================================================================
// 0x10f0830   step every pending ToI whose time is before "till"
// ======================================================================
// @ 0x010f0830 hkContinuousSimulation::handleAllToisTill
hkStepResult hkContinuousSimulation::handleAllToisTill(hkWorld* world, float till)
{
	for (;;)
	{
		float minTime = till;
		int bestIndex = -1;
		int i = 0;
		if (m_events.m_size <= 0)
			return HK_STEP_RESULT_NONE;
		int bestOffset = -0x40;
		for (int offset = 0; i < m_events.m_size; i++, offset += 0x40)
		{
			hkContinuousSimulation_ToiEntry& cur = *(hkContinuousSimulation_ToiEntry*)((char*)m_events.m_data + offset);
			if (minTime > cur.m_time)
			{
				bestIndex = i;
				minTime = cur.m_time;
				bestOffset = offset;
			}
			else if (minTime == cur.m_time && bestIndex != -1)
			{
				hkContinuousSimulation_ToiEntry& best = *(hkContinuousSimulation_ToiEntry*)((char*)m_events.m_data + bestOffset);
				unsigned int a0 = *(unsigned int*)((char*)cur.m_a + 0xcc);
				unsigned int a1 = *(unsigned int*)((char*)cur.m_b + 0xcc);
				unsigned int b0 = *(unsigned int*)((char*)best.m_a + 0xcc);
				unsigned int b1 = *(unsigned int*)((char*)best.m_b + 0xcc);
				if (a0 < b0 || (a0 == b0 && a1 < b1))
				{
					bestIndex = i;
					minTime = cur.m_time;
					bestOffset = offset;
				}
			}
		}
		if (bestIndex < 0)
			return HK_STEP_RESULT_NONE;
		hkContinuousSimulation_ToiEntry event = m_events.m_data[bestIndex];
		hkToiEntryMoveLast(m_events.m_data[bestIndex], m_events.m_data[--m_events.m_size]);

		float endTime = world->m_18;
		float delta = endTime - event.m_time;
		world->m_0c = event.m_time;
		float invDelta = (delta == 0.0f) ? 0.0f : 1.0f / delta;
		world->m_170 = (int&)event.m_time;
		world->m_174 = (int&)endTime;
		world->m_178 = (int&)delta;
		world->m_17c = (int&)invDelta;
		{
			char* si = (char*)world->m_78 + 0x10;
			*(float*)(si + 0x00) = event.m_time;
			*(float*)(si + 0x04) = endTime;
			*(float*)(si + 0x08) = delta;
			*(float*)(si + 0x0c) = invDelta;
		}
		world->m_8c++;
		toiEvent(world, &event, m_08);

		hkContactPointRemovedEvent removed;
		removed.m_04 = &event.m_10;
		removed.m_0c = event.m_b;
		removed.m_00 = 0xffff;
		removed.m_08 = event.m_a;
		removed.m_14 = event.m_18;
		hkWorldCallbackUtil::fireContactPointRemoved(*(hkWorld**)((char*)event.m_a + 8), removed);
		if (*(int*)((char*)event.m_a + 0xa0) != 0)
			hkEntityCallbackUtil::fireContactPointRemovedInternal((hkEntity*)event.m_a, removed);
		if (*(int*)((char*)event.m_b + 0xa0) != 0)
			hkEntityCallbackUtil::fireContactPointRemovedInternal((hkEntity*)event.m_b, removed);
		if (--world->m_8c == 0 && world->m_88 != 0 && world->m_94 == 0)
			world->executePendingOperations();
		m_28++;
		if (*(int*)((char*)g_hkMemoryInstance + 4) == 1)
			return HK_STEP_RESULT_QUIT;
	}
}

// ======================================================================
// 0x10f0b00   append one ToI event for the given agent
// ======================================================================
// @ 0x010f0b00 hkContinuousSimulation::addToiEvent
void hkContinuousSimulation::addToiEvent(hkProcessCollisionInput* input, hkAgentNnEntry* agent)
{
	hkContinuousSimulation_ToiEntry& event = m_events.expandOne();
	event.m_time = (float&)input->m_3034;
	event.m_0c = input->m_3030;
	event.m_20 = *(int*)((char*)input + 0x10);
	event.m_24 = *(int*)((char*)input + 0x14);
	event.m_28 = *(int*)((char*)input + 0x18);
	event.m_2c = *(int*)((char*)input + 0x1c);
	event.m_30 = *(int*)((char*)input + 0x20);
	event.m_34 = *(int*)((char*)input + 0x24);
	event.m_38 = *(int*)((char*)input + 0x28);
	event.m_3c = *(int*)((char*)input + 0x2c);
	event.m_a = (void*)(*(int*)(agent->m_14 + 0x10) + agent->m_14);
	event.m_b = (void*)(*(int*)(agent->m_18 + 0x10) + agent->m_18);
	event.m_10 = input->m_3038;
	event.m_14 = input->m_303c;
	event.m_18 = (int)agent->m_10;
}

// ======================================================================
// 0x10f0bb0   drop every ToI event whose entities are not in the given set
// ======================================================================
// @ 0x010f0bb0 hkContinuousSimulation::FUN_010f0bb0
void hkContinuousSimulation::FUN_010f0bb0(void** entities, int numEntities)
{
	if (m_events.m_size == 0)
		return;

	hkPointerMap map;
	map.reserve(numEntities);
	for (int i = 0; i < numEntities; i++)
		map.insert((int)entities[i], 0);

	for (int i = 0; i < m_events.m_size; i++)
	{
		hkContinuousSimulation_ToiEntry& event = m_events.m_data[i];
		int fa = map.find((int)event.m_a);
		int fb = map.find((int)event.m_b);
		if (fa <= map.m_08 || fb <= map.m_08)
		{
			hkContactPointRemovedEvent removed;
			removed.m_04 = &event.m_10;
			removed.m_0c = event.m_b;
			removed.m_00 = 0xffff;
			removed.m_08 = event.m_a;
			removed.m_14 = event.m_18;
			hkWorldCallbackUtil::fireContactPointRemoved(*(hkWorld**)((char*)event.m_a + 8), removed);
			if (*(int*)((char*)event.m_a + 0xa0) != 0)
				hkEntityCallbackUtil::fireContactPointRemovedInternal((hkEntity*)event.m_a, removed);
			if (*(int*)((char*)event.m_b + 0xa0) != 0)
				hkEntityCallbackUtil::fireContactPointRemovedInternal((hkEntity*)event.m_b, removed);
			hkToiEntryMoveLast(m_events.m_data[i], m_events.m_data[--m_events.m_size]);
			i--;
		}
	}
}

// ======================================================================
// 0x10f0d60   bring the world's manifolds up to date for one sub-step
// ======================================================================
// @ 0x010f0d60 hkLs_updateEntityManifolds
struct hkSweptTransformUtil
{
	static void lerp2(void* out, float t, const void* from);   // 0x1209c50
};

void hkLs_updateEntityManifolds(hkEntity* entity, hkConstraintInstance::ConstraintPriority priority,
                                hkProcessCollisionInput& input, float dt, hkFixedArray<unsigned char>& flags)
{
	float delta = dt - input.m_stepInfo.m_startTime;
	hkStepInfo saved = input.m_stepInfo;
	input.m_stepInfo.m_deltaTime = delta;
	input.m_stepInfo.m_endTime = dt;
	input.m_stepInfo.m_invDeltaTime = (delta <= 0.0f) ? 0.0f : 1.0f / delta;

	for (int i = 0; i < *(int*)((char*)entity + 0x44); i++)
	{
		char* entry = *(char**)((char*)entity + 0x40) + i * 8;
		hkAgentNnEntry* agent = *(hkAgentNnEntry**)entry;
		if ((int)priority > (int)(unsigned char)((char*)agent)[8])
			continue;
		{
			char* h = *(char**)(entry + 4);
			char* body = (char*)((int)h + *(int*)(h + 0x10));
			if (*(char*)(body + 0x99) == 0)
			{
				if (flags.m_data[*(unsigned short*)(body + 0x94)] == 8)
					continue;
				if (*(char*)(body + 0x99) == 0)
				{
					unsigned char* p = &flags.m_data[*(unsigned short*)(body + 0x94)];
					if (*p == 0)
					{
						*p = 1;
						char* motion = *(char**)(body + 0x58);
						hkSweptTransformUtil::lerp2(motion + 0x50, dt, motion + 0x10);
					}
				}
			}
			hkLs_updateManifold(agent, input);
		}
	}
	input.m_stepInfo = saved;
}

// ======================================================================
// 0x10f0e90   return the first velocity component over the accumulated limit
// ======================================================================
// @ 0x010f0e90 hkLs_areVelocitiesOk
int hkLs_areVelocitiesOk(float scale, const hkConstraintSchemaInfo& info, const float* velocities, int numVelocities, const hkProcessCollisionInput& input)
{
	float maxV = *(float*)(*(int*)&input + 0x1a44 + (int)(*(signed char*)(*(int*)&info + 0x18)) * 0x3c) * info.m_08;
	int found = -1;
	int i = 0;
	for (; i < numVelocities - 3; i += 4)
	{
		const float* p = velocities + i + 2;
		float t;
		t = (float)fabs(p[-2]) * scale;
		if (t > maxV) { found = i; maxV = t; }
		t = (float)fabs(p[-1]) * scale;
		if (t > maxV) { found = i + 1; maxV = t; }
		t = (float)fabs(p[0]) * scale;
		if (t > maxV) { found = i + 2; maxV = t; }
		t = (float)fabs(p[1]) * scale;
		if (t > maxV) { found = i + 3; maxV = t; }
	}
	for (; i < numVelocities; i++)
	{
		float t = (float)fabs(velocities[i]) * scale;
		if (t > maxV) { found = i; maxV = t; }
	}
	return found;
}

// ======================================================================
// 0x10f0f90   re-check every constraint schema of the ToI entities
// ======================================================================
// @ 0x010f0f90 hkLs_toiCheckValidityOfConstraints
struct hkConstraintSolverResources
{
	int m_00;      // +0x00 (points at an object with a float at +8)
	int m_04;      // +0x04
	int m_08;      // +0x08
	int m_0c;      // +0x0c
	int m_10;      // +0x10
	int m_14;      // +0x14
};

struct hkVelocitySnapshot
{
	int m_00, m_04, m_08, m_0c, m_10, m_14, m_18, m_1c;
};
typedef char hkVelocitySnapshot_size_check[(sizeof(hkVelocitySnapshot) == 0x20) ? 1 : -1];

int __cdecl FUN_010b1d70(int a1, int a2, int a3, int a4, int a5, void* out);   // 0x010b1d70

void hkLs_toiCheckValidityOfConstraints(hkConstraintSolverResources& resources, hkProcessCollisionInput& input,
                                        hkArray<hkConstraintSchemaInfo>& schemas, int& numSchemas,
                                        hkConstraintInstance::ConstraintPriority priority,
                                        hkFixedArray<unsigned char>& flags,
                                        const hkArray<hkEntity*>& entities, hkArray<hkEntity*>& out)
{
	hkLocalBuffer<hkVelocitySnapshot> buffer(entities.m_size);
	char scratch[0x400];

	for (int i = 0; i < entities.m_size; i++)
	{
		char* motion = *(char**)((char*)entities.m_data[i] + 0x58);
		char* acc = (char*)(*(int*)(motion + 8) + resources.m_0c);
		hkVelocitySnapshot& s = buffer.begin()[i];
		s.m_00 = *(int*)(acc + 0x10);
		s.m_04 = *(int*)(acc + 0x14);
		s.m_08 = *(int*)(acc + 0x18);
		s.m_0c = *(int*)(acc + 0x1c);
		s.m_10 = *(int*)(acc + 0x20);
		s.m_14 = *(int*)(acc + 0x24);
		s.m_18 = *(int*)(acc + 0x28);
		s.m_1c = *(int*)(acc + 0x2c);
		float s6c = *(float*)(motion + 0x6c);
		*(float*)(acc + 0x10) = (*(float*)(motion + 0x60) - *(float*)(motion + 0x50)) * s6c;
		*(float*)(acc + 0x14) = (*(float*)(motion + 0x64) - *(float*)(motion + 0x54)) * s6c;
		*(float*)(acc + 0x18) = (*(float*)(motion + 0x68) - *(float*)(motion + 0x58)) * s6c;
		*(float*)(acc + 0x1c) = (*(float*)(motion + 0x6c) - *(float*)(motion + 0x5c)) * s6c;
		*(float*)(acc + 0x20) = *(float*)(motion + 0xa0) * s6c;
		*(float*)(acc + 0x24) = *(float*)(motion + 0xa4) * s6c;
		*(float*)(acc + 0x28) = *(float*)(motion + 0xa8) * s6c;
		*(float*)(acc + 0x2c) = *(float*)(motion + 0xac) * s6c;
	}

	for (int i = numSchemas; i < schemas.m_size; i++)
	{
		hkConstraintSchemaInfo& schema = schemas.m_data[i];
		if ((int)priority > (int)(unsigned char)*(char*)(*(int*)&schema + 0x18))
			continue;
		void** p = *(void***)((char*)*(int*)&schema + 0x24);
		hkEntity* a = (hkEntity*)p[1];
		hkEntity* other = (hkEntity*)p[1 + (flags.m_data[*(unsigned short*)((char*)a + 0x94)] == 8 ? 1 : 0)];
		if (flags.m_data[*(unsigned short*)((char*)other + 0x94)] == 4)
		{
			hkConstraintSchemaInfo tmp = schemas.m_data[numSchemas];
			schemas.m_data[numSchemas] = schemas.m_data[i];
			schemas.m_data[i] = tmp;
			numSchemas++;
		}
		else
		{
			int n = FUN_010b1d70(resources.m_04, schema.m_04, resources.m_0c, resources.m_14, 0x100, scratch);
			if (hkLs_areVelocitiesOk(*(float*)(*(int*)&resources + 8), schema, (const float*)scratch, n, input) != -1)
			{
				flags.m_data[*(unsigned short*)((char*)other + 0x94)] = 4;
				out.pushBack(other);
				hkConstraintSchemaInfo tmp = schemas.m_data[numSchemas];
				schemas.m_data[numSchemas] = schemas.m_data[i];
				schemas.m_data[i] = tmp;
				numSchemas++;
			}
		}
	}

	for (int i = 0; i < entities.m_size; i++)
	{
		char* motion = *(char**)((char*)entities.m_data[i] + 0x58);
		char* acc = (char*)(*(int*)(motion + 8) + resources.m_0c);
		hkVelocitySnapshot& s = buffer.begin()[i];
		*(int*)(acc + 0x10) = s.m_00;
		*(int*)(acc + 0x14) = s.m_04;
		*(int*)(acc + 0x18) = s.m_08;
		*(int*)(acc + 0x1c) = s.m_0c;
		*(int*)(acc + 0x20) = s.m_10;
		*(int*)(acc + 0x24) = s.m_14;
		*(int*)(acc + 0x28) = s.m_18;
		*(int*)(acc + 0x2c) = s.m_1c;
	}
}
