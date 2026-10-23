// s010cca60 -- Havok 3.1.0 hkCollisionDispatcher: creation-function reset, contact-manager
// factory registration, statistics/debug bookkeeping, the agent type tables, the collision
// quality info initialiser, the constructor/destructor, hkAabbUtil::calcAabb and two small
// agent forwarders.  Layouts and member offsets come from the disassembly; names follow the
// dev-build PDB and the Havok 3.1 headers.
//
// Module flags: /vc71 /O2 /MD /Gy /TP

#include <string.h>
#include <math.h>

typedef float hkReal;
typedef unsigned char hkBool;
typedef int hkShapeType;

// HK_REAL_MAX in this build: 0x7f7fffee (not FLT_MAX)
#define HK_REAL_MAX 3.402820018375656e38f

class hkStatisticsCollector;
class hkpContactMgrFactory;
class hkCollisionDispatcher;
class hkThreadMemory;

// ---------------------------------------------------------------------------------------------------------
// referenced objects: vptr +0, m_memSizeAndFlags +4, m_referenceCount +6
// ---------------------------------------------------------------------------------------------------------
struct hkRefCounted
{
	void** m_vptr;                          // 0x000
	unsigned short m_memSizeAndFlags;       // 0x004
	unsigned short m_referenceCount;        // 0x006

	typedef void (hkRefCounted::*DeletingDtor)(int);

	void addReference() { if (m_memSizeAndFlags != 0) ++m_referenceCount; }
	void removeReference()
	{
		if (m_memSizeAndFlags != 0)
		{
			m_referenceCount = (unsigned short)(m_referenceCount - 1);
			if (m_referenceCount == 0)
			{
				union { void* p; DeletingDtor d; } u;
				u.p = m_vptr[0];
				(this->*u.d)(1);
			}
		}
	}
};

class hkpContactMgrFactory : public hkRefCounted {};

// hkMemory::s_instance (0x016E4178), vtable slot 1 = deallocate(void*)
class hkMemory
{
public:
	virtual void v00();                 // +0
	virtual void deallocate(void* p);   // +4
	static hkMemory* s_instance;
};

// hkStatisticsCollector slots as called here
class hkStatisticsCollector
{
public:
	virtual void v00();                                                     // +0x00
	virtual void beginObject(const char* name, int mode, const void* obj);  // +0x04
	virtual void addArray(const char* name, int elemSize, const void* ptr,
	                      int usedBytes, int allocBytes);                   // +0x08
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void endObject();                                               // +0x18
};

// hkThreadMemory, deallocateChunk(this, p, nbytes, class) (0x0107DB10)
class hkThreadMemory
{
public:
	void deallocateChunk(void* p, int nbytes, int memClass);
};

struct hkArrayUtil
{
	static void _reserveMore(void* arrayBase, int elemSize);    // 0x0107F530
};

enum { HK_ARRAY_CAPACITY_MASK = 0x3fffffff };

template <typename T>
class hkArray
{
public:
	T* m_data;
	int m_size;
	int m_capacityAndFlags;

	int getCapacity() const { return m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK; }
	void pushBack(const T& t)
	{
		if (m_size == getCapacity())
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		T* slot = &m_data[m_size];
		m_size = m_size + 1;
		*slot = t;
	}
};

// ---------------------------------------------------------------------------------------------------------
// hkMath float min/max (inline: fcomp / fnstsw / test ah)
// ---------------------------------------------------------------------------------------------------------
namespace hkMath
{
	template <typename T> __forceinline T max2(T a, T b) { return (a > b) ? a : b; }
	template <typename T> __forceinline T min2(T a, T b) { return (a < b) ? a : b; }
}

struct hkVector4 { volatile float x, y, z, w; };
struct hkAabb { hkVector4 m_min; hkVector4 m_max; };

struct hkAabbUtil
{
	static void calcAabb(const float* vertexData, int numVertices, int stride, hkAabb& aabb);   // 0x010CD8E0
};

// ---------------------------------------------------------------------------------------------------------
// hkCollisionQualityInfo (0x3c)
// ---------------------------------------------------------------------------------------------------------
struct hkCollisionQualityInfo
{
	float m_keepContact;                    // 0x00
	float m_create4dContact;                // 0x04
	float m_createContact;                  // 0x08
	float m_manifoldTimDistance;            // 0x0c
	hkBool m_useContinuousPhysics;          // 0x10
	float m_minSeparation;                  // 0x14
	float m_minExtraSeparation;             // 0x18
	float m_minSafeDeltaTime;               // 0x1c
	float m_minAbsoluteSafeDeltaTime;       // 0x20
	float m_toiSeparation;                  // 0x24
	float m_toiExtraSeparation;             // 0x28
	float m_toiAccuracy;                    // 0x2c
	float m_maxContraintViolation;          // 0x30
	float m_minToiDeltaTime;                // 0x34
	unsigned short m_constraintPriority;    // 0x38
};

// ---------------------------------------------------------------------------------------------------------
// hkCollisionDispatcher (0x1c28)
// ---------------------------------------------------------------------------------------------------------
struct AgentFuncs
{
	void (*m_createFunc)();             // 0x00
	void (*m_getPenetrationsFunc)();    // 0x04
	void (*m_getClosestPointFunc)();    // 0x08
	void (*m_linearCastFunc)();         // 0x0c
	hkBool m_isFlipped;                 // 0x10
	hkBool m_isPredictive;              // 0x11
};

struct Agent3Funcs
{
	void (*m_createFunc)();             // 0x00
	void (*m_destroyFunc)();            // 0x04
	void (*m_cleanupFunc)();            // 0x08
	void (*m_removePointFunc)();        // 0x0c
	void (*m_commitPotentialFunc)();    // 0x10
	void (*m_createZombieFunc)();       // 0x14
	void (*m_updateFilterFunc)();       // 0x18
	void (*m_invalidateTimFunc)();      // 0x1c
	void (*m_warpTimeFunc)();           // 0x20
	void (*m_sepNormalFunc)();          // 0x24
	void (*m_processFunc)();            // 0x28
	hkBool m_isPredictive;              // 0x2c
	hkBool m_ignoreSymmetricVersion;    // 0x2d
};

struct Agent3FuncsIntern : Agent3Funcs
{
	int m_symmetric;                    // 0x30
};

struct DebugEntry
{
	char m_typeA;                       // 0x00
	char m_typeB;                       // 0x01
	char m_priority;                    // 0x02
};

struct ShapeInheritance
{
	hkShapeType m_primaryType;          // 0x00
	hkShapeType m_alternateType;        // 0x04
};

struct InitCollisionQualityInfo
{
	float m_gravityLength;                          // 0x00
	float m_collisionTolerance;                     // 0x04
	float m_minDeltaTime;                           // 0x08
	float m_maxLinearVelocity;                      // 0x0c
	unsigned short m_defaultConstraintPriority;     // 0x10
	unsigned short m_toiConstraintPriority;         // 0x12
	unsigned short m_toiHigherConstraintPriority;   // 0x14
	unsigned short m_toiForcedConstraintPriority;   // 0x16
	hkBool m_wantContinuousCollisionDetection;      // 0x18
	hkBool m_enableNegativeManifoldTims;            // 0x19
	hkBool m_enableNegativeToleranceToCreateNon4dContacts; // 0x1a
};

class hkCollisionDispatcher
{
public:
	void** m_vptr;                                          // 0x000
	unsigned short m_memSizeAndFlags;                       // 0x004
	unsigned short m_referenceCount;                        // 0x006
	void (*m_defaultCollisionAgent)();                      // 0x008
	hkpContactMgrFactory* m_contactMgrFactory[8][8];        // 0x00c
	unsigned int m_hasAlternateType[32];                    // 0x10c
	int m_numAgent2Types;                                   // 0x18c
	unsigned char m_agent2Types[32][32];                    // 0x190
	unsigned char m_agent2TypesPred[32][32];                // 0x590
	AgentFuncs m_agent2Func[64];                            // 0x990
	int m_numAgent3Types;                                   // 0xe90
	unsigned char m_agent3Types[32][32];                    // 0xe94
	unsigned char m_agent3TypesPred[32][32];                // 0x1294
	Agent3FuncsIntern m_agent3Func[16];                     // 0x1694
	char m_collisionQualityTable[8][8];                     // 0x19d4
	hkCollisionQualityInfo m_collisionQualityInfo[8];       // 0x1a14
	hkBool m_collisionAgentRegistered;                      // 0x1bf4
	hkBool m_agent3Registered;                              // 0x1bf5
	int m_agent3SectorSize;                                 // 0x1bf8
	int m_agent3AgentSize;                                  // 0x1bfc
	hkBool m_checkEnabled;                                  // 0x1c00
	hkArray<ShapeInheritance> m_shapeInheritance;           // 0x1c04
	DebugEntry (*m_debugAgent2Table)[32][32];               // 0x1c10
	DebugEntry (*m_debugAgent2TablePred)[32][32];           // 0x1c14
	DebugEntry (*m_debugAgent3Table)[32][32];               // 0x1c18
	DebugEntry (*m_debugAgent3TablePred)[32][32];           // 0x1c1c
	float m_expectedMaxLinearVelocity;                      // 0x1c20
	float m_expectedMinPsiDeltaTime;                        // 0x1c24

	void resetCreationFunctions();
	void registerContactMgrFactoryWithAll(hkpContactMgrFactory* factory, int responseA);
	void calcStatistics(hkStatisticsCollector* c) const;
	void disableDebugging();
	void internalRegisterCollisionAgent(unsigned char (*agentTypes)[32], int agentType,
	                                    hkShapeType typeA, hkShapeType typeB,
	                                    hkShapeType typeAReg, hkShapeType typeBReg,
	                                    DebugEntry (*debugTable)[32][32], int level);
	void updateHasAlternateType(hkShapeType typeA, hkShapeType typeB, int level);
	void initCollisionQualityInfo(InitCollisionQualityInfo& info);
	void registerCollisionAgent(AgentFuncs& funcs, hkShapeType typeA, hkShapeType typeB);
	int registerAgent3(Agent3Funcs& funcs, hkShapeType typeA, hkShapeType typeB);
	void registerAlternateShapeType(hkShapeType typeA, hkShapeType typeB);
	hkCollisionDispatcher* init(hkpContactMgrFactory* factory);
	~hkCollisionDispatcher();
};

// ---------------------------------------------------------------------------------------------------------
// external callees / data, VA-resolved (addresses are relocations at link time)
// ---------------------------------------------------------------------------------------------------------
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern unsigned long g_hkThreadMemoryTls;                           // 0x016E4174

const char* hkShapeType_toString(int type);                         // 0x010E7E30
int hkString_snprintf(char* buf, int size, const char* fmt, ...);   // 0x0107F390
void hkAgent3Bridge_registerBridgeAgent3(hkCollisionDispatcher* d);// 0x010EBB30
extern "C" void hkAgent1nMachine_Destroy(void* track, void* dispatcher, void* contactMgr); // 0x01104760
extern "C" void hkNullAgent_getNullAgent();                          // 0x010CD8D0
extern "C" void hkNullAgent3_create();                               // 0x010CCA40
extern "C" void hkNullAgent_getPenetrations();                       // 0x00C2E4E0
extern "C" void hkNullAgent_getClosestPoint();                       // 0x00C2E4E0
extern "C" void hkNullAgent_linearCast();                            // 0x00C2E4E0
extern "C" void hkNullAgent3_destroy();                              // 0x00C2E4E0
extern "C" void FUN_010cca50();                                      // 0x010CCA50

// hkBvTreeStreamAgent::cleanup's target (0x010CDA50)
struct hkBvTreeStreamAgent
{
	void** m_vptr;              // 0x00
	char m_pad08[0x28];         // 0x08 .. 0x2f (dispatcher +8, contactMgr +0xc, machine +0x30)
	void cleanup();
};

// @ 0x010cca60  hkCollisionDispatcher::resetCreationFunctions
void hkCollisionDispatcher::resetCreationFunctions()
{
	m_numAgent2Types = 1;
	m_numAgent3Types = 1;
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			if (m_debugAgent2Table)
			{
				(*m_debugAgent2Table)[i][j].m_priority = 100;
				(*m_debugAgent2TablePred)[i][j].m_priority = 100;
				(*m_debugAgent3Table)[i][j].m_priority = 100;
				(*m_debugAgent3TablePred)[i][j].m_priority = 100;
			}
			m_agent2Types[i][j] = 0;
			m_agent3Types[i][j] = 0;
			m_agent2TypesPred[i][j] = 0;
			m_agent3TypesPred[i][j] = 0;
		}
	}

	m_agent2Func[0].m_createFunc = (void (*)())hkNullAgent_getNullAgent;
	m_agent2Func[0].m_getPenetrationsFunc = (void (*)())hkNullAgent_getPenetrations;
	m_agent2Func[0].m_getClosestPointFunc = (void (*)())hkNullAgent_getClosestPoint;
	m_agent2Func[0].m_linearCastFunc = (void (*)())hkNullAgent_linearCast;
	m_agent2Func[0].m_isFlipped = 0;
	m_agent2Func[0].m_isPredictive = 1;

	m_agent3Func[0].m_createFunc = (void (*)())hkNullAgent3_create;
	m_agent3Func[0].m_destroyFunc = (void (*)())hkNullAgent3_destroy;
	m_agent3Func[0].m_cleanupFunc = 0;
	m_agent3Func[0].m_removePointFunc = 0;
	m_agent3Func[0].m_commitPotentialFunc = 0;
	m_agent3Func[0].m_createZombieFunc = 0;
	m_agent3Func[0].m_updateFilterFunc = 0;
	m_agent3Func[0].m_sepNormalFunc = 0;
	m_agent3Func[0].m_invalidateTimFunc = 0;
	m_agent3Func[0].m_warpTimeFunc = 0;
	m_agent3Func[0].m_processFunc = (void (*)())FUN_010cca50;
	m_agent3Func[0].m_symmetric = 0;

	hkAgent3Bridge_registerBridgeAgent3(this);
	m_collisionAgentRegistered = 0;

	if (m_debugAgent3Table)
	{
		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				(*m_debugAgent3Table)[i][j].m_priority = 100;
				(*m_debugAgent3TablePred)[i][j].m_priority = 100;
			}
		}
	}
}

// @ 0x010ccbd0  hkCollisionDispatcher::registerContactMgrFactoryWithAll
void hkCollisionDispatcher::registerContactMgrFactoryWithAll(hkpContactMgrFactory* factory, int responseA)
{
	for (int i = 0; i < 8; i++)
	{
		factory->addReference();
		m_contactMgrFactory[i][responseA]->removeReference();
		m_contactMgrFactory[i][responseA] = factory;

		factory->addReference();
		m_contactMgrFactory[responseA][i]->removeReference();
		m_contactMgrFactory[responseA][i] = factory;
	}
}

// @ 0x010ccc50  hkCollisionDispatcher::calcStatistics
void hkCollisionDispatcher::calcStatistics(hkStatisticsCollector* c) const
{
	c->beginObject(0, 2, this);
	if (m_debugAgent2Table)
	{
		c->addArray("DebugTable", 4, m_debugAgent2Table, 0xc00, 0);
		c->addArray("DebugTable", 4, m_debugAgent2TablePred, 0xc00, 0);
		c->addArray("DebugTable", 4, m_debugAgent3Table, 0xc00, 0);
		c->addArray("DebugTable", 4, m_debugAgent3TablePred, 0xc00, 0);
	}
	c->endObject();
}

// @ 0x010cccf0  hkCollisionDispatcher::disableDebugging
void hkCollisionDispatcher::disableDebugging()
{
	if (m_debugAgent2Table)
	{
		hkMemory::s_instance->deallocate(m_debugAgent2Table);
		hkMemory::s_instance->deallocate(m_debugAgent2TablePred);
		hkMemory::s_instance->deallocate(m_debugAgent3Table);
		hkMemory::s_instance->deallocate(m_debugAgent3TablePred);
		m_debugAgent2Table = 0;
		m_debugAgent2TablePred = 0;
		m_debugAgent3Table = 0;
		m_debugAgent3TablePred = 0;
	}
}

// @ 0x010ccd60  hkCollisionDispatcher::internalRegisterCollisionAgent
void hkCollisionDispatcher::internalRegisterCollisionAgent(
	unsigned char (*agentTypes)[32], int agentType,
	hkShapeType typeA, hkShapeType typeB,
	hkShapeType typeAReg, hkShapeType typeBReg,
	DebugEntry (*debugTable)[32][32], int level)
{
	m_collisionAgentRegistered = 1;

	for (int i = 0; i < m_shapeInheritance.m_size; i++)
	{
		if (m_shapeInheritance.m_data[i].m_alternateType == typeA)
		{
			internalRegisterCollisionAgent(agentTypes, agentType,
				m_shapeInheritance.m_data[i].m_primaryType, typeB,
				typeAReg, typeBReg, debugTable, level + 1);
		}
		else if (m_shapeInheritance.m_data[i].m_alternateType == typeB)
		{
			if (m_shapeInheritance.m_data[i].m_alternateType == typeA)
			{
				internalRegisterCollisionAgent(agentTypes, agentType,
					m_shapeInheritance.m_data[i].m_primaryType, typeB,
					typeAReg, typeBReg, debugTable, level + 1);
			}
			else
			{
				internalRegisterCollisionAgent(agentTypes, agentType,
					typeA, m_shapeInheritance.m_data[i].m_primaryType,
					typeAReg, typeBReg, debugTable, level + 1);
			}
		}
	}

	int aStart = typeA;
	int aEnd = typeA + 1;
	int bStart = typeB;
	int bEnd = typeB + 1;
	if (typeA == -1)
	{
		aStart = 1;
		aEnd = 32;
		level++;
	}
	if (typeB == -1)
	{
		bStart = 1;
		bEnd = 32;
		level++;
	}

	for (int a = aStart; a < aEnd; a++)
	{
		for (int b = bStart; b < bEnd; b++)
		{
			agentTypes[a][b] = (unsigned char)agentType;
			if (debugTable)
			{
				DebugEntry* e = &(*debugTable)[a][b];
				if (m_checkEnabled && level > e->m_priority)
				{
					char buf[1000];
					hkString_snprintf(buf, 1000,
						"Agent handling types <%s-%s> would override more specialized agent <%s-%s>\n"
						"Maybe the order of registering your collision agent is wrong, make sure you register your alternate type agents first",
						hkShapeType_toString(typeA), hkShapeType_toString(typeB),
						hkShapeType_toString(e->m_typeA), hkShapeType_toString(e->m_typeB));
				}
				e->m_typeA = (char)typeAReg;
				e->m_typeB = (char)typeBReg;
				e->m_priority = (char)level;
			}
		}
	}
}

// @ 0x010ccfc0  hkCollisionDispatcher::updateHasAlternateType
void hkCollisionDispatcher::updateHasAlternateType(hkShapeType typeA, hkShapeType typeB, int level)
{
	m_hasAlternateType[typeA] |= m_hasAlternateType[typeB];
	for (int i = 0; i < m_shapeInheritance.m_size; i++)
	{
		int alternateType = m_shapeInheritance.m_data[i].m_alternateType;
		if (alternateType == typeA)
		{
			updateHasAlternateType(m_shapeInheritance.m_data[i].m_primaryType,
				alternateType, level + 1);
		}
	}
}

// @ 0x010cd030  hkCollisionDispatcher::initCollisionQualityInfo
void hkCollisionDispatcher::initCollisionQualityInfo(InitCollisionQualityInfo& info)
{
	m_expectedMinPsiDeltaTime = info.m_minDeltaTime;
	m_expectedMaxLinearVelocity = info.m_maxLinearVelocity;

	hkReal tim = info.m_minDeltaTime * info.m_minDeltaTime * info.m_gravityLength * 0.5f;

	hkCollisionQualityInfo& q1 = m_collisionQualityInfo[1];
	q1.m_keepContact = info.m_collisionTolerance;
	q1.m_create4dContact = info.m_collisionTolerance;
	q1.m_manifoldTimDistance = info.m_collisionTolerance;
	if (info.m_enableNegativeManifoldTims)
		q1.m_manifoldTimDistance = tim * -2.0f;
	q1.m_createContact = info.m_collisionTolerance;
	if (info.m_enableNegativeToleranceToCreateNon4dContacts)
		q1.m_createContact = tim * -1.0f;

	q1.m_maxContraintViolation = HK_REAL_MAX;
	q1.m_useContinuousPhysics = 0;
	q1.m_toiAccuracy = (hkReal)fabs(-5.000000174710194e18);
	q1.m_constraintPriority = info.m_defaultConstraintPriority;
	q1.m_minSeparation = -5.000000100204387e19f;
	q1.m_minExtraSeparation = -5.000000100204387e19f;
	q1.m_toiSeparation = -9.999999980506448e18f;
	q1.m_toiExtraSeparation = -9.999999980506448e18f;
	q1.m_minSafeDeltaTime = 1.0f;
	q1.m_minAbsoluteSafeDeltaTime = 1.0f;
	q1.m_minToiDeltaTime = 1.0f;

	hkCollisionQualityInfo& q5 = m_collisionQualityInfo[5];
	q5 = q1;
	m_collisionQualityInfo[2] = q1;
	m_collisionQualityInfo[3] = q1;
	m_collisionQualityInfo[4] = q1;

	q5.m_manifoldTimDistance = info.m_collisionTolerance;
	q5.m_create4dContact = info.m_collisionTolerance;
	q5.m_createContact = info.m_collisionTolerance;

	if (info.m_wantContinuousCollisionDetection)
	{
		hkCollisionQualityInfo& q2 = m_collisionQualityInfo[2];
		q2.m_minSeparation = -0.6f;
		q2.m_minExtraSeparation = -0.2f;
		q2.m_toiSeparation = -0.3f;
		q2.m_toiExtraSeparation = -0.14f;
		q2.m_toiAccuracy = 0.042f;
		q2.m_maxContraintViolation = 0.2f;
		q2.m_minSafeDeltaTime = 5.0f / info.m_maxLinearVelocity;
		q2.m_minAbsoluteSafeDeltaTime = 0.005f / info.m_maxLinearVelocity;
		q2.m_minToiDeltaTime = (-0.2f / info.m_maxLinearVelocity) * -2.0f;
		q2.m_constraintPriority = info.m_toiConstraintPriority;
		q2.m_useContinuousPhysics = 1;

		if (info.m_wantContinuousCollisionDetection)
		{
			hkCollisionQualityInfo& q3 = m_collisionQualityInfo[3];
			q3.m_minSeparation = -0.5f;
			q3.m_minExtraSeparation = -0.16666667f;
			q3.m_toiSeparation = -0.25f;
			q3.m_toiExtraSeparation = -0.11666667f;
			q3.m_toiAccuracy = 0.035f;
			q3.m_maxContraintViolation = 0.16666667f;
			q3.m_minSafeDeltaTime = 5.0f / info.m_maxLinearVelocity;
			q3.m_minAbsoluteSafeDeltaTime = 0.005f / info.m_maxLinearVelocity;
			q3.m_minToiDeltaTime = (-0.16666667f / info.m_maxLinearVelocity) * -1.0f;
			q3.m_constraintPriority = info.m_toiHigherConstraintPriority;
			q3.m_useContinuousPhysics = 1;
		}
	}

	m_collisionQualityInfo[4].m_keepContact = info.m_collisionTolerance;

	if (info.m_wantContinuousCollisionDetection)
	{
		hkCollisionQualityInfo& q4 = m_collisionQualityInfo[4];
		q4.m_minSeparation = -0.4f;
		q4.m_minExtraSeparation = -0.031578947f;
		q4.m_toiSeparation = -0.2f;
		q4.m_toiExtraSeparation = -0.022105263f;
		q4.m_toiAccuracy = 0.006631579f;
		q4.m_maxContraintViolation = 0.031578947f;
		q4.m_minSafeDeltaTime = 5.0f / info.m_maxLinearVelocity;
		q4.m_minAbsoluteSafeDeltaTime = 0.005f / info.m_maxLinearVelocity;
		q4.m_minToiDeltaTime = (-0.031578947f / info.m_maxLinearVelocity) * -1.0f;
		q4.m_constraintPriority = info.m_toiForcedConstraintPriority;
		q4.m_useContinuousPhysics = 1;
	}

	memset(m_collisionQualityTable, 1, 64);
	m_collisionQualityTable[1][3] = 1;
	m_collisionQualityTable[1][1] = 0;
	m_collisionQualityTable[1][2] = 0;
	m_collisionQualityTable[1][4] = 3;
	m_collisionQualityTable[1][5] = 4;
	m_collisionQualityTable[1][6] = 3;
	m_collisionQualityTable[2][1] = 0;
	m_collisionQualityTable[2][2] = 0;
	m_collisionQualityTable[2][3] = 1;
	m_collisionQualityTable[2][4] = 2;
	m_collisionQualityTable[2][5] = 2;
	m_collisionQualityTable[2][6] = 2;
	m_collisionQualityTable[3][1] = 1;
	m_collisionQualityTable[3][2] = 1;
	m_collisionQualityTable[3][3] = 1;
	m_collisionQualityTable[3][4] = 1;
	m_collisionQualityTable[3][5] = 1;
	m_collisionQualityTable[3][6] = 2;
	m_collisionQualityTable[4][1] = 3;
	m_collisionQualityTable[4][2] = 2;
	m_collisionQualityTable[4][3] = 1;
	m_collisionQualityTable[4][4] = 1;
	m_collisionQualityTable[4][5] = 2;
	m_collisionQualityTable[4][6] = 2;
	m_collisionQualityTable[5][1] = 4;
	m_collisionQualityTable[5][2] = 2;
	m_collisionQualityTable[5][3] = 1;
	m_collisionQualityTable[5][4] = 2;
	m_collisionQualityTable[5][5] = 2;
	m_collisionQualityTable[5][6] = 2;
	m_collisionQualityTable[6][1] = 3;
	m_collisionQualityTable[6][2] = 2;
	m_collisionQualityTable[6][3] = 2;
	m_collisionQualityTable[6][4] = 2;
	m_collisionQualityTable[6][5] = 2;
	m_collisionQualityTable[6][6] = 2;
}

// @ 0x010cd3e0  hkCollisionDispatcher::registerCollisionAgent
void hkCollisionDispatcher::registerCollisionAgent(AgentFuncs& funcs, hkShapeType typeA, hkShapeType typeB)
{
	m_agent2Func[m_numAgent2Types] = funcs;
	internalRegisterCollisionAgent(m_agent3Types, 1, typeA, typeB, typeA, typeB,
		m_debugAgent3Table, 0);
	internalRegisterCollisionAgent(m_agent2Types, m_numAgent2Types, typeA, typeB, typeA, typeB,
		m_debugAgent2Table, 0);
	if (funcs.m_isPredictive)
	{
		internalRegisterCollisionAgent(m_agent3TypesPred, 1, typeA, typeB, typeA, typeB,
			m_debugAgent3TablePred, 0);
		internalRegisterCollisionAgent(m_agent2TypesPred, m_numAgent2Types, typeA, typeB, typeA, typeB,
			m_debugAgent2TablePred, 0);
	}
	m_numAgent2Types++;
}

// @ 0x010cd4c0  hkCollisionDispatcher::registerAgent3
int hkCollisionDispatcher::registerAgent3(Agent3Funcs& funcs, hkShapeType typeA, hkShapeType typeB)
{
	Agent3FuncsIntern fi;
	m_agent3AgentSize = 0x80;
	m_agent3SectorSize = 0x200;
	m_agent3Registered = 1;

	memcpy(&fi, &funcs, sizeof(funcs));
	fi.m_symmetric = 0;

	if (typeA != typeB && !funcs.m_ignoreSymmetricVersion)
	{
		fi.m_symmetric = 2;
		m_agent3Func[m_numAgent3Types] = fi;
		internalRegisterCollisionAgent(m_agent3Types, m_numAgent3Types, typeB, typeA, typeB, typeA,
			m_debugAgent3Table, 0);
		if (fi.m_isPredictive)
		{
			internalRegisterCollisionAgent(m_agent3TypesPred, m_numAgent3Types, typeA, typeB, typeA, typeB,
				m_debugAgent3TablePred, 0);
		}
		m_numAgent3Types++;
		fi.m_symmetric = 1;
	}

	m_agent3Func[m_numAgent3Types] = fi;
	internalRegisterCollisionAgent(m_agent3Types, m_numAgent3Types, typeA, typeB, typeA, typeB,
		m_debugAgent3Table, 0);
	if (fi.m_isPredictive)
	{
		internalRegisterCollisionAgent(m_agent3TypesPred, m_numAgent3Types, typeA, typeB, typeA, typeB,
			m_debugAgent3TablePred, 0);
	}
	return m_numAgent3Types++;
}

// @ 0x010cd630  hkCollisionDispatcher::registerAlternateShapeType
void hkCollisionDispatcher::registerAlternateShapeType(hkShapeType typeA, hkShapeType typeB)
{
	for (int i = 0; i < m_shapeInheritance.m_size; i++)
	{
		if (m_shapeInheritance.m_data[i].m_primaryType == typeA &&
		    m_shapeInheritance.m_data[i].m_alternateType == typeB)
		{
			m_shapeInheritance.m_size = m_shapeInheritance.m_size - 1;
			for (int j = i; j < m_shapeInheritance.m_size; j++)
				m_shapeInheritance.m_data[j] = m_shapeInheritance.m_data[j + 1];
			i--;
		}
	}

	updateHasAlternateType(typeA, typeB, 0);

	ShapeInheritance si;
	si.m_primaryType = typeA;
	si.m_alternateType = typeB;
	m_shapeInheritance.pushBack(si);
}

// @ 0x010cd700  hkCollisionDispatcher::init (constructor)
hkCollisionDispatcher* hkCollisionDispatcher::init(hkpContactMgrFactory* factory)
{
	m_defaultCollisionAgent = (void (*)())factory;
	m_referenceCount = 1;
	m_vptr = (void**)0x014a4360;

	for (int i = 0; i < 64; i++)
	{
		m_agent2Func[i].m_isFlipped = 0;
		m_agent2Func[i].m_isPredictive = 0;
	}

	for (int i = 0; i < 16; i++)
	{
		m_agent3Func[i].m_updateFilterFunc = 0;
		m_agent3Func[i].m_invalidateTimFunc = 0;
		m_agent3Func[i].m_warpTimeFunc = 0;
		m_agent3Func[i].m_sepNormalFunc = 0;
		m_agent3Func[i].m_isPredictive = 0;
		m_agent3Func[i].m_ignoreSymmetricVersion = 0;
	}

	m_shapeInheritance.m_data = 0;
	m_shapeInheritance.m_size = 0;
	m_shapeInheritance.m_capacityAndFlags = (int)0x80000000;
	m_debugAgent2Table = 0;
	m_debugAgent2TablePred = 0;
	m_debugAgent3Table = 0;
	m_debugAgent3TablePred = 0;
	m_collisionAgentRegistered = 0;
	m_checkEnabled = 1;
	m_numAgent3Types = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_contactMgrFactory[i][j] = factory;
			if (factory)
				factory->addReference();
		}
	}

	for (int i = 0; i < 32; i++)
		m_hasAlternateType[i] = 1 << i;

	resetCreationFunctions();

	m_agent3AgentSize = 0x80;
	m_agent3SectorSize = 0x200;
	m_agent3Registered = 0;
	return this;
}

// @ 0x010cd810  hkCollisionDispatcher::~hkCollisionDispatcher
hkCollisionDispatcher::~hkCollisionDispatcher()
{
	m_vptr = (void**)0x014a4360;
	disableDebugging();

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_contactMgrFactory[i][j])
				m_contactMgrFactory[i][j]->removeReference();
		}
	}

	if (!(m_shapeInheritance.m_capacityAndFlags & (int)0x80000000))
	{
		hkThreadMemory* tm = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
		int capacity = m_shapeInheritance.m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK;
		tm->deallocateChunk(m_shapeInheritance.m_data, capacity << 3, 0x14);
	}

	m_vptr = (void**)0x013ef094;
}

// @ 0x010cd8e0  hkAabbUtil::calcAabb
void hkAabbUtil::calcAabb(const float* vertexData, int numVertices, int stride, hkAabb& aabb)
{
	aabb.m_min.x = vertexData[0];
	aabb.m_min.y = vertexData[1];
	aabb.m_min.z = vertexData[2];
	aabb.m_min.w = 0.0f;
	aabb.m_max.x = aabb.m_min.x;
	aabb.m_max.y = aabb.m_min.y;
	aabb.m_max.z = aabb.m_min.z;
	aabb.m_max.w = aabb.m_min.w;

	const float* v = vertexData + 2;
	for (int i = 0; i < numVertices; i++)
	{
		aabb.m_max.x = hkMath::max2(aabb.m_max.x, v[-2]);
		aabb.m_max.y = hkMath::max2(aabb.m_max.y, v[-1]);
		aabb.m_max.z = hkMath::max2(aabb.m_max.z, v[0]);
		aabb.m_min.x = hkMath::min2(aabb.m_min.x, v[-2]);
		aabb.m_min.y = hkMath::min2(aabb.m_min.y, v[-1]);
		aabb.m_min.z = hkMath::min2(aabb.m_min.z, v[0]);
		v = (const float*)((const char*)v + stride);
	}
}

// @ 0x010cda20  FUN_010cda20 (5-argument __stdcall forwarder)
extern "C" void __cdecl FUN_010e49c0(void*, void*, void*, void*, void*);   // 0x010E49C0
void __stdcall FUN_010cda20(void* a, void* b, void* c, void* d, void* e)
{
	FUN_010e49c0(a, b, c, d, e);
}

// @ 0x010cda50  hkBvTreeStreamAgent::cleanup
void hkBvTreeStreamAgent::cleanup()
{
	hkAgent1nMachine_Destroy((char*)this + 0x30, *(void**)((char*)this + 0x0c), *(void**)((char*)this + 0x08));
	typedef void (hkBvTreeStreamAgent::*DeletingDtor)(int);
	union { void* p; DeletingDtor d; } u;
	u.p = m_vptr[0];
	(this->*u.d)(1);
}
