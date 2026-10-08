// Havok 3.1.0 slice s010a4e40: hkSimulationIsland-style "buildAndSolve" driver (0x010a5070, 1963 bytes).
//
// Takes the stack allocator's whole free space as one block, lays out accumulators (0x80-byte header followed
// by per-entity records), jacobians, solver-element temps and schemas inside it, regrows/relocates the block
// until everything fits, builds the accumulator list, lets every constraint write its jacobians/schemas (low
// priority constraints first, constraints with priority >= 3 deferred through a local array), then runs
// hkSolveConstraints, optionally hkExportImpulsesAndRhs, and releases the stack blocks.
// Struct stubs carry members at the x86 offsets of the 32-bit binary (comments).
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP
#include "../s010cbaa0/hk31_b005.h"

struct hkSolverObj;
struct hkEntity;
struct hkConstraintData;

// callees (cdecl)
int hkSolveConstraints(void* solverInfo, char* schemas, char* accumulators, char* jacobians, char* elemTemp);   // 0x010B8B30
void hkExportImpulsesAndRhs(void* solverInfo, char* schemas, char* accumulators, char* jacobians, char* elemTemp);   // 0x010BD5E0

// ---- hkThreadMemory stack allocator / hkInplaceArray ---------------------------------------------------------------
struct hkThreadMemoryRaw
{
	virtual void vslot0();
	virtual void vslot1();
	virtual void vslot2();
	virtual void* onStackOverflow(int nbytes);          // +0x0c
	virtual void onStackUnderflow(void* p);              // +0x10
	uint32_t pad04[7];
	char* m_stackCurrent;                                // +0x20
	char* m_stackPrev;                                   // +0x24
	char* m_stackBase;                                   // +0x28
	char* m_stackEnd;                                    // +0x2c
	void deallocateChunk(void* p, int nbytes, int cl);   // 0x0107DB10
	static __forceinline hkThreadMemoryRaw& getInstance() { return *(hkThreadMemoryRaw*)TlsGetValue(g_hkThreadMemoryTls); }
};

template <typename T> __forceinline T* hkAllocateStack(int n)
{
	hkThreadMemoryRaw& tm = hkThreadMemoryRaw::getInstance();
	int size = (n * (int)sizeof(T) + 0x10) & ~0xf;
	char* cur = tm.m_stackCurrent;
	char* next = cur + size;
	if ((uint32_t)next <= (uint32_t)tm.m_stackEnd)
	{
		tm.m_stackCurrent = next;
		return (T*)cur;
	}
	return (T*)tm.onStackOverflow(size);
}
template <typename T> __forceinline void hkDeallocateStack(T* p)
{
	hkThreadMemoryRaw& tm = hkThreadMemoryRaw::getInstance();
	tm.m_stackCurrent = (char*)p;
	if ((char*)p == tm.m_stackBase)
		tm.onStackUnderflow(p);
}

template <typename T, int N>
struct HK_ALIGN16 hkInplaceArrayD : hkArray<T>
{
	enum { DONT_DEALLOCATE_FLAG = (int)0x80000000 };
	T m_storage[N];                                      // +0x0c
	__forceinline hkInplaceArrayD()
	{
		this->m_data = m_storage;
		this->m_size = 0;
		this->m_capacityAndFlags = N | (int)0x80000000;
	}
	__forceinline ~hkInplaceArrayD()
	{
		if ((this->m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
			hkThreadMemoryRaw::getInstance().deallocateChunk(this->m_data, (this->m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK) * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
	}
};

// ---- monitor stream records ----------------------------------------------------------------------------------------
struct hkMonitorListCommand { const char* m_name; uint32_t m_time; uint32_t m_pad; const char* m_firstSplit; };
struct hkMonitorValueCommand { const char* m_name; float m_value; };

static __forceinline void hkTimerBeginList(const char* name, const char* firstSplit)
{
	void* end = hkTlsGet(g_hkMonitorStreamEndTls);
	if (hkTlsGet(g_hkMonitorStreamCurrentTls) < end)
	{
		hkMonitorListCommand* c = (hkMonitorListCommand*)hkTlsGet(g_hkMonitorStreamCurrentTls);
		c->m_name = name;
		c->m_firstSplit = firstSplit;
		uint32_t t;
		__asm { rdtsc
		        mov t, eax }
		c->m_time = t;
		hkTlsSet(g_hkMonitorStreamCurrentTls, c + 1);
	}
}
static __forceinline void hkTimerCmd(const char* name)
{
	void* end = hkTlsGet(g_hkMonitorStreamEndTls);
	if (hkTlsGet(g_hkMonitorStreamCurrentTls) < end)
	{
		hkMonitorCommand* c = (hkMonitorCommand*)hkTlsGet(g_hkMonitorStreamCurrentTls);
		c->m_commandAndMonitor = name;
		uint32_t t;
		__asm { rdtsc
		        mov t, eax }
		c->m_time0 = t;
		hkTlsSet(g_hkMonitorStreamCurrentTls, c + 1);
	}
}
static __forceinline void hkMonitorAddValue(const char* name, float v)
{
	void* end = hkTlsGet(g_hkMonitorStreamEndTls);
	if (hkTlsGet(g_hkMonitorStreamCurrentTls) < end)
	{
		hkMonitorValueCommand* c = (hkMonitorValueCommand*)hkTlsGet(g_hkMonitorStreamCurrentTls);
		c->m_name = name;
		c->m_value = v;
		hkTlsSet(g_hkMonitorStreamCurrentTls, c + 1);
	}
}

// ---- objects -------------------------------------------------------------------------------------------------------
// Per-entity solver record (entity +0x58).
struct hkSolverObj
{
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
	virtual char* writeAccumulators(void* world, char* dst);     // 5 (+0x14), returns the advanced pointer
	virtual void importResults(void* world, char* p);            // 6 (+0x18)
	uint32_t m_pad04;
	int m_offset;                                                // +8: offset of the record inside the accumulator block
	uint32_t m_pad0c;
	char m_data[16];                                             // +0x10
};

struct hkEntity;
struct hkConstraintData;

struct hkQueryOut { char* m_jacobians; char* m_schemas; char* m_elemTemp; };

// Jacobian-setup context passed to every constraint's build call.
struct hkQueryIn
{
	char m_pad0[0x20];
	char* m_accumulators;        // +0x20
	char* m_jacobiansBegin;      // +0x24
	char* m_bodyA;               // +0x28
	char* m_bodyB;               // +0x2c
	char* m_dataA;               // +0x30
	char* m_dataB;               // +0x34
	char m_pad38[8];
	uint32_t m_user;             // +0x40
	uint32_t m_userData;         // +0x44
};

struct hkConstraintData
{
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6();
	virtual void build(hkQueryIn* in, hkQueryOut* out);          // 7 (+0x1c)
};

struct hkConstraintInternal                                      // 0x1c bytes
{
	uint32_t m_user;                                             // +0
	hkEntity* m_entityA;                                         // +4
	hkEntity* m_entityB;                                         // +8
	hkConstraintData* m_data;                                    // +0xc
	uint8_t m_priority;                                          // +0x10
	char m_pad11[7];
	uint32_t m_userData;                                         // +0x18
};

struct hkEntity
{
	char m_pad0[0x58];
	hkSolverObj* m_solver;                                       // +0x58
	char m_pad5c[0x70 - 0x5c];
	hkConstraintInternal* m_constraints;                         // +0x70
	int m_numConstraints;                                        // +0x74
};

// Memory-requirement summary computed by the caller.
struct hkSolverSizes
{
	char m_pad0[8];
	int m_x8;                    // +8
	int m_jacobiansSize;         // +0xc
	int m_schemasSize;           // +0x10
	unsigned m_accumulatorsSize; // +0x14 (128 bytes per entity plus one)
	int m_numResults;            // +0x18
};

static __forceinline void BuildConstraint(hkConstraintInternal* c, char* base, hkQueryIn* in, hkQueryOut& out,
                                          char*& jacLimit, char* swapBlock)
{
	if ((uint32_t)out.m_jacobians >= (uint32_t)jacLimit)
	{
		out.m_jacobians = swapBlock;
		jacLimit = (char*)0xffffffff;
	}
	hkSolverObj* a = c->m_entityA->m_solver;
	hkSolverObj* b = c->m_entityB->m_solver;
	in->m_bodyA = base + a->m_offset;
	in->m_dataA = a->m_data;
	in->m_bodyB = base + b->m_offset;
	in->m_dataB = b->m_data;
	in->m_user = c->m_user;
	in->m_userData = c->m_userData;
	c->m_data->build(in, &out);
}

void hkBuildAndSolve(void* world, void* solverInfo, hkQueryIn* in, hkSolverSizes* sz, hkEntity** entities, int numEntities)
{
	hkTimerBeginList("Ltsolver", "memory");

	int ptrBytes = sz->m_numResults * 4 + 8;
	char* swapBlock = 0;
	char* lastBlock = 0;
	hkQueryOut out;

	hkThreadMemoryRaw& tm0 = hkThreadMemoryRaw::getInstance();
	int avail = (int)(tm0.m_stackEnd - tm0.m_stackCurrent) - 0x10;
	char* base = hkAllocateStack<char>(avail);
	char* base0 = base;
	int total = avail;

	for (;;)
	{
		char* limit = base + total;
		char* jacStart = base + sz->m_accumulatorsSize + 0x90;
		out.m_elemTemp = jacStart + sz->m_jacobiansSize;
		char* swapLimit = out.m_elemTemp;
		for (;;)
		{
			int schemasSize = sz->m_schemasSize;
			char* schemasBegin = out.m_elemTemp + ptrBytes;
			char* schemasEnd = schemasBegin + schemasSize + 4;
			if ((uint32_t)schemasEnd <= (uint32_t)limit)
			{
				// ---- everything fits: build and solve ----
				hkTimerCmd("Stmake accum");
				base[0] = 1;
				base[0xc] = 1;
				*(uint32_t*)(base + 0x3c) = 0; *(uint32_t*)(base + 0x38) = 0; *(uint32_t*)(base + 0x34) = 0; *(uint32_t*)(base + 0x30) = 0;
				*(uint32_t*)(base + 0x1c) = 0; *(uint32_t*)(base + 0x18) = 0; *(uint32_t*)(base + 0x14) = 0; *(uint32_t*)(base + 0x10) = 0;
				*(uint32_t*)(base + 0x2c) = 0; *(uint32_t*)(base + 0x28) = 0; *(uint32_t*)(base + 0x24) = 0; *(uint32_t*)(base + 0x20) = 0;
				*(uint32_t*)(base + 0x4c) = 0; *(uint32_t*)(base + 0x48) = 0; *(uint32_t*)(base + 0x44) = 0; *(uint32_t*)(base + 0x40) = 0;
				*(uint32_t*)(base + 0x50) = 0; *(uint32_t*)(base + 0x54) = 0; *(uint32_t*)(base + 0x58) = 0; *(uint32_t*)(base + 0x5c) = 0;
				*(uint32_t*)(base + 0x60) = 0; *(uint32_t*)(base + 0x64) = 0; *(uint32_t*)(base + 0x68) = 0; *(uint32_t*)(base + 0x6c) = 0;
				*(uint32_t*)(base + 0x70) = 0; *(uint32_t*)(base + 0x74) = 0; *(uint32_t*)(base + 0x78) = 0; *(uint32_t*)(base + 0x7c) = 0;
				char* p = base + 0x80;
				for (hkEntity** e = entities; e < entities + numEntities; ++e)
				{
					hkSolverObj* so = (*e)->m_solver;
					if (so->m_offset != p - base)
						so->m_offset = p - base;
					p = so->writeAccumulators(world, p);
				}
				*p = 2;
				for (int i = 0; i < sz->m_numResults; i++)
					((int*)out.m_elemTemp)[i] = 0;

				hkQueryIn* qin = in;
				qin->m_accumulators = base;
				qin->m_jacobiansBegin = jacStart;

				hkTimerCmd("Stmake jac");

				out.m_jacobians = jacStart;
				out.m_schemas = schemasBegin;
				{
				hkInplaceArrayD<hkConstraintInternal*, 256> deferred;
				char* jacLimit = swapLimit;
				for (hkEntity** e = entities; e < entities + numEntities; ++e)
				{
					hkConstraintInternal* c = (*e)->m_constraints;
					hkConstraintInternal* cEnd = c + (*e)->m_numConstraints;
					for (; c < cEnd; c++)
					{
						if (c->m_priority < 3)
							BuildConstraint(c, base, qin, out, jacLimit, swapBlock);
						else
							deferred.pushBack(c);
					}
				}
				for (int i = 0; i < deferred.m_size; i++)
					BuildConstraint(deferred.m_data[i], base, qin, out, jacLimit, swapBlock);
				*out.m_schemas = 0;
				}
				hkTimerCmd("Stsolve");
				int result = hkSolveConstraints(solverInfo, schemasBegin, base, jacStart, out.m_elemTemp);
				hkMonitorAddValue("MiNumJacobians", (float)sz->m_numResults);
				hkMonitorAddValue("MiNumEntities", (float)(sz->m_accumulatorsSize >> 7) - 1.0f);
				hkTimerCmd("Stintegrate bodies");
				if (result == 1)
				{
					hkExportImpulsesAndRhs(solverInfo, schemasBegin, base, jacStart, out.m_elemTemp);
					for (hkEntity** e = entities; e < entities + numEntities; ++e)
					{
						hkSolverObj* so = (*e)->m_solver;
						so->importResults(world, base + so->m_offset);
					}
				}
				hkTimerCmd("lt");
				if (lastBlock)
					hkDeallocateStack(lastBlock);
				hkDeallocateStack(base0);
				return;
			}
			if ((uint32_t)limit <= (uint32_t)jacStart)
				break;
			if ((uint32_t)swapLimit < (uint32_t)limit)
			{
				int n = schemasSize + 4 + ptrBytes;
				char* blk = hkAllocateStack<char>(n);
				lastBlock = blk;
				limit = blk + n;
				out.m_elemTemp = blk;
			}
			else
			{
				char* nElem = (char*)((sz->m_x8 * 2 - (int)limit) + sz->m_jacobiansSize + (int)jacStart);
				int n = (int)nElem + ptrBytes + schemasSize + 4;
				swapBlock = hkAllocateStack<char>(n);
				lastBlock = swapBlock;
				swapLimit = limit - sz->m_x8;
				limit = swapBlock + n;
				out.m_elemTemp = swapBlock + (int)nElem;
			}
		}
		// does not fit even with all the free space: grow to the exact size
		total = (int)(out.m_elemTemp + ptrBytes + sz->m_schemasSize + 4 - base0);
		base = hkAllocateStack<char>(total);
		lastBlock = base;
	}
}
