// Slice s00a2f660 -- EA::Audio::Submix internals (gold7)
//
//   (0x00a2f6e0)  eastl::hashtable node free loop
//   (0x00a2f730)  load a submix object from a resman path and hook it up
//   (0x00a2f960)  Submix constructor
//   (0x00a2fac0)  Submix::Tick
//   (0x00a2fbe0)  Submix::SetPerformanceData
//   (0x00a2fe30)  Submix::SetProperty
//   (0x00a2ffe0)  Submix::ConnectPrimitive
//   (0x00a301f0)  EA::Audio::Submix::DisconnectPrimitive
//   (0x00a30280)  Submix destructor
//
// The object is `EA::Audio::Submix`.  Retail layout:
//   +0x00 vfptr (primary base, size 4)
//   +0x04 vfptr (secondary base, size 4)
//   +0x08 vfptr (secondary base, size 8)   +0x0c int member
//   +0x10 VoiceContainer mVoiceContainer            (size 0x960)
//   +0x970 mId / +0x974 mSendId                     (u32)
//   +0x978 mSendName / +0x988 mName                 (pointer triples)
//   +0x998 mbAddedToTick                            (bool)
//   +0x99c mPrimitives                              (hash table, size 0x438)
//   +0xdd4 mRegisters                               (hash table, size 0x820)
//   +0x15f4 mParams                                 (0x18)
//   +0x160c mSendPlugins                            (hash table, size 0x34)
#include "types.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned __int64 u64;

// ---------------------------------------------------------------------------
// globals / operators
// ---------------------------------------------------------------------------
extern void  operator_delete(void*);        // 0xf47380
extern char  gEmptyString16[];              // 0x1667bac  eastl::gEmptyString16
extern void* gAudioSystem;                  // 0x16e61a8  rw::audio::core::System*
extern void* gEapdDebug;                    // 0x166d9f4

// ---------------------------------------------------------------------------
// external helpers (bodies live in other slices)
// ---------------------------------------------------------------------------
extern void* FUN_008de1a0();                 // EA::Audio::Eapd::Debug::ObjectError
extern void  FUN_00a248a0();                 // ProfileTimer::ProfileTimer(void*)
extern u8    FUN_00a24850(const char*, u8*); // ParseResman
extern void  FUN_00a24900();                 // ProfileTimer::Accumulate
extern u32   FUN_00a2e4c0(u32);              // audio system helper
extern u32   FUN_0093a3a0();                 // Stopwatch::GetElapsedTimeFloat (thiscall)
extern void  FUN_0112c600();                 // System::Lock
extern void  FUN_0112c620();                 // System::Unlock
extern u8    FUN_0112c640(u32);              // System predicate
extern void  FUN_00594410(void*);            // send-plugin table begin
extern u32   FUN_0112ccc0(u32, void*);       // send-plugin table step
extern void  FUN_00645ed0();                 // eastl::hashtable::find (ICF-merged)
extern void  FUN_00a34760();                 // VoiceContainer constructor
extern void  FUN_00a34620();                 // VoiceContainer::DtorTail
extern void  FUN_00a343e0();                 // VoiceContainer::Destroy
extern void  FUN_00a34890();                 // VoiceContainer::Disconnect
extern void  FUN_00a34bf0();                 // VoiceContainer::Connect
extern void  FUN_00a342c0();                 // VoiceContainer::Create
extern u8    FUN_00a33dc0();                 // VoiceContainer::CommitBoundProperties
extern u8    FUN_00a33ee0();                 // VoiceContainer::SetProperty
extern void  FUN_00a340b0();                 // VoiceContainer::MaskPluginBindings
extern void  FUN_00a144c0();                 // primitives table constructor
extern void  FUN_00a24480();                 // PHTable::FreeBuckets
extern void  FUN_00a2a870();                 // registers table constructor
extern void  FUN_00a1b6c0();                 // registers table DoFreeNodes
extern void  FUN_00a2a970();                 // send-plugin table constructor
extern void  FUN_0068fb70();                 // ProfHashTable::FreeBuckets
extern void* FUN_00a16d00(u32);              // PAggC::PAggC(int)
extern void* FUN_00a17090(u32);              // allocate map node
extern void* FUN_00a17100(void*);            // make tween node from a submix
extern void  FUN_00a16fd0();                 // tween node set value (thiscall)
extern void* FUN_00a16ad0(u32);              // allocate PrimitiveAggregate
extern void  FUN_00a16a90(void*);            // release primitive
extern void  FUN_00a26ce0();                 // hashtable insert (thiscall)
extern void  FUN_00a136f0(void*, void*, u32);
extern void  FUN_00d2c9f0();                 // cNodeList::Erase
extern void  FUN_00fccdd0(u32);
extern void  FUN_00a2f660();                 // eastl::hash_node<...>::~hash_node

// ---------------------------------------------------------------------------
// eastl-style pointer-triple string
// ---------------------------------------------------------------------------
struct PtrString
{
	void* mpBegin;   // +0x00
	void* mpEnd;     // +0x04
	void* mpCap;     // +0x08
	char  pad0c[4];  // +0x0c

	PtrString()
	{
		mpBegin = gEmptyString16;
		mpEnd   = gEmptyString16;
		mpCap   = (char*)gEmptyString16 + 1;
	}
	~PtrString()
	{
		if ((char*)mpCap - (char*)mpBegin > 1 && mpBegin != 0)
			operator_delete(mpBegin);
	}
};

// ---------------------------------------------------------------------------
// eastl fixed hash table (bucket array at +4, bucket count at +8)
// ---------------------------------------------------------------------------
struct AllocTag { AllocTag() {} };

struct FixedHashTable
{
	char   pad00[4];        // +0x00
	void** mpBucketArray;   // +0x04
	u32    mnBucketCount;   // +0x08
	u32    mnElementCount;  // +0x0c
	char   pad10[0xc];      // +0x10
	void*  mpFreeList;      // +0x1c
	char   pad20[4];        // +0x20
	void*  mpPoolBegin;     // +0x24
	void*  mpPoolEnd;       // +0x28
	char   pad2c[4];        // +0x2c
	void*  mpPoolTail;      // +0x30

	// shared bucket-buffer release/rebind tail of the table destructor
	void ReleaseBucketBuffer()
	{
		void** pBuckets = mpBucketArray;
		mnElementCount = 0;
		if (mnBucketCount > 1 && pBuckets != (void**)mpPoolTail) {
			if (pBuckets < (void**)mpPoolBegin || pBuckets >= (void**)mpPoolEnd) {
				operator_delete(pBuckets);
			} else {
				*pBuckets = mpFreeList;
				mpFreeList = pBuckets;
			}
		}
	}
};

struct PHTable : FixedHashTable
{
	char pad34[0x438 - 0x34];
	PHTable(const AllocTag&, const AllocTag&);
	~PHTable();
};
PHTable::PHTable(const AllocTag& h, const AllocTag& e)
{
	((void(__thiscall*)(PHTable*, const AllocTag*, const AllocTag*))FUN_00a144c0)(this, &h, &e);
}
PHTable::~PHTable()
{
	((void(__thiscall*)(PHTable*, void**, u32))FUN_00a24480)(this, mpBucketArray, mnBucketCount);
	ReleaseBucketBuffer();
}

struct RegTable : FixedHashTable
{
	char pad34[0x820 - 0x34];
	RegTable(const AllocTag&, const AllocTag&);
	~RegTable();
};
RegTable::RegTable(const AllocTag& h, const AllocTag& e)
{
	((void(__thiscall*)(RegTable*, const AllocTag*, const AllocTag*))FUN_00a2a870)(this, &h, &e);
}
RegTable::~RegTable()
{
	((void(__thiscall*)(RegTable*, void**, u32))FUN_00a1b6c0)(this, mpBucketArray, mnBucketCount);
	ReleaseBucketBuffer();
}

struct PlugTable : FixedHashTable
{
	PlugTable(const AllocTag&, const AllocTag&);
	~PlugTable();
};
PlugTable::PlugTable(const AllocTag& h, const AllocTag& e)
{
	((void(__thiscall*)(PlugTable*, const AllocTag*, const AllocTag*))FUN_00a2a970)(this, &h, &e);
}
PlugTable::~PlugTable()
{
	((void(__thiscall*)(PlugTable*, void**, u32))FUN_0068fb70)(this, mpBucketArray, mnBucketCount);
	ReleaseBucketBuffer();
}

// ---------------------------------------------------------------------------
// VoiceContainer
// ---------------------------------------------------------------------------
struct VoiceContainer
{
	char pad00[0x960];

	VoiceContainer();
	~VoiceContainer();

	void Destroy()                    { ((void(__thiscall*)(VoiceContainer*))FUN_00a343e0)(this); }
	void Disconnect()                 { ((void(__thiscall*)(VoiceContainer*))FUN_00a34890)(this); }
	void Connect()                    { ((void(__thiscall*)(VoiceContainer*))FUN_00a34bf0)(this); }
	void Create(u8 mode)              { ((void(__thiscall*)(VoiceContainer*, u8))FUN_00a342c0)(this, mode); }
	void MaskPluginBindings(const void* a, u32 b)
	                                  { ((void(__thiscall*)(VoiceContainer*, const void*, u32))FUN_00a340b0)(this, a, b); }
	u8   CommitBoundProperties()      { return ((u8(__thiscall*)(VoiceContainer*))FUN_00a33dc0)(this); }
	u8   SetProperty(u32 id, u32 v)   { return ((u8(__thiscall*)(VoiceContainer*, u32, u32))FUN_00a33ee0)(this, id, v); }
};
VoiceContainer::VoiceContainer() { ((void(__thiscall*)(VoiceContainer*))FUN_00a34760)(this); }
VoiceContainer::~VoiceContainer() { ((void(__thiscall*)(VoiceContainer*))FUN_00a34620)(this); }

// ---------------------------------------------------------------------------
// ProfileTimer (constructor is out of line; destructor accumulates the delta)
// ---------------------------------------------------------------------------
struct Stopwatch { u64 mStart; };

struct ProfileTimer
{
	Stopwatch mTimer;     // +0x00
	float     mFactor;    // +0x08
	char      pad0c[0xc]; // +0x0c
	float*    mpTarget;   // +0x18

	ProfileTimer(void* p);
	~ProfileTimer();
};
ProfileTimer::ProfileTimer(void* p)
{
	((void(__thiscall*)(ProfileTimer*, void*))FUN_00a248a0)(this, p);
}
ProfileTimer::~ProfileTimer()
{
	const u64 elapsed = ((u64(__thiscall*)(Stopwatch*))FUN_0093a3a0)(&mTimer);
	float* const pTarget = mpTarget;
	*pTarget = (float)(int64_t)elapsed * mFactor + *pTarget;
}

// ---------------------------------------------------------------------------
// Primitive hash-table node
// ---------------------------------------------------------------------------
struct IPrimitive;
struct IPrimitiveNode
{
	u32          mKey;      // +0x00
	IPrimitive*  mpValue;   // +0x04
	IPrimitiveNode* mpNext; // +0x08
};

// eastl::hashtable_iterator -- a found node plus its bucket slot
struct HTIter
{
	IPrimitiveNode*  mpNode;    // +0x00
	IPrimitiveNode** mpBucket;  // +0x04
};

// ---------------------------------------------------------------------------
// ea::Audio::Submix
// ---------------------------------------------------------------------------
struct RefCountTemplate
{
	virtual void OnRefCountZero();
	virtual ~RefCountTemplate() {}
	int mRefCount;   // +0x04
	RefCountTemplate() : mRefCount(0) {}
};

struct IMixable
{
	virtual void Mixable0();
	virtual void Mixable1();
	virtual void Mixable2();
};

struct SecondaryBase
{
	virtual void Secondary0();
};

struct ConstructorParams
{
	u32 mFlags0;   // +0x00
	u32 mFlags1;   // +0x04
	u8  mFlag2;    // +0x08
	u8  mFlag3;    // +0x09
	u16 pad0a;     // +0x0a
	union { u32 mStamp; u8 mStampByte; };   // +0x0c
	u8  mFlag4;    // +0x10
	char pad11[3]; // +0x11
	union { u32 mValue; u8 mValueByte; };   // +0x14

	ConstructorParams()
		: mFlags0(0), mFlags1(0), mFlag2(1), mFlag3(0)
		, mStamp(0), mFlag4(0), mValue(0) {}
};

struct HashNode0
{
	char pad00[0x1e4];
	HashNode0* mpNext;   // +0x1e4
};

struct NodeAllocator
{
	void DoFreeNodes(HashNode0** pNodeArray, u32 n);
};

struct Submix : IMixable, SecondaryBase, RefCountTemplate
{
	VoiceContainer    mVoiceContainer;   // +0x10
	u32               mId;               // +0x970
	u32               mSendId;           // +0x974
	PtrString         mSendName;         // +0x978
	PtrString         mName;             // +0x988
	u8                mbAddedToTick;     // +0x998
	char              pad999[3];         // +0x999
	PHTable           mPrimitives;       // +0x99c
	RegTable          mRegisters;        // +0xdd4
	ConstructorParams mParams;           // +0x15f4
	PlugTable         mSendPlugins;      // +0x160c

	Submix();
	~Submix();

	u32  LoadFromResman(const char* resName, u32 flags, u32 extra);
	void Tick(u32, u32);
	u32  SetPerformanceData(int level, const void* a, u32 b);
	void SetProperty(u32 id, u32 value);
	u32  ConnectPrimitive(u32 id, IPrimitive* p);
	void DisconnectPrimitive(u32 id, IPrimitive* p);
};

// =================================================================================================
// (0x00a2f6e0) eastl::hashtable node free loop
// =================================================================================================
// @ 0x00a2f6e0
void NodeAllocator::DoFreeNodes(HashNode0** pNodeArray, u32 n)
{
	for (u32 i = 0; i < n; ++i) {
		HashNode0* pNode = pNodeArray[i];
		while (pNode != 0) {
			HashNode0* const pTmp = pNode;
			pNode = pNode->mpNext;
			((void(__thiscall*)(NodeAllocator*, HashNode0*))FUN_00a2f660)(this, pTmp);
		}
		pNodeArray[i] = 0;
	}
}

// =================================================================================================
// (0x00a2f730) load a submix object from a resman path and hook it up
// =================================================================================================
// @ 0x00a2f730
u32 Submix::LoadFromResman(const char* resName, u32 flags, u32 extra)
{
	ProfileTimer timer((char*)this + 0x5c);
	void* const pDebug = FUN_008de1a0();
	if (pDebug == 0)
		return 0;

	u8 params[0xc] = { 0 };
	if (FUN_00a24850(resName, params) == 0)
		return 0;

	void* const pHook = (*(void*(__thiscall**)(void*, void*))(*(char**)pDebug + 0x58))(pDebug, params);

	void* pRef = 0;
	if (pHook != 0) {
		(*(void(__thiscall**)(void*))(*(char**)pHook + 0x00))(pHook);

		u32 nKind = 0;
		if (flags == 0)
			nKind = 1;
		else if ((flags & 1) != 0)
			nKind = 3;

		if ((*(u8(__thiscall**)(void*, u32*, u32, u32, u32, u32))(*(char**)pHook + 0x34))
				(pHook, &extra, nKind, 6, 1, 0) != 0) {
			pRef = pHook;
			if (FUN_00a2e4c0(0) != 0) {
				(*(void(__thiscall**)(void*))(*(char**)pHook + 0x04))(pHook);
				FUN_00a24900();
				return 1;
			}
		}
	}

	if (pRef != 0)
		(*(void(__thiscall**)(void*))(*(char**)pRef + 0x04))(pRef);

	return 0;
}

// =================================================================================================
// (0x00a2f960) Submix constructor
// =================================================================================================
// @ 0x00a2f960
Submix::Submix()
	: mId(0), mSendId(0), mbAddedToTick(0)
	, mPrimitives(AllocTag(), AllocTag())
	, mRegisters(AllocTag(), AllocTag())
	, mSendPlugins(AllocTag(), AllocTag())
{
}

// =================================================================================================
// (0x00a2fac0) Submix::Tick
// =================================================================================================
// @ 0x00a2fac0
void Submix::Tick(u32, u32)
{
	if (mParams.mStampByte != 0 && FUN_0112c640(mParams.mFlag2) != 0) {
		mParams.mFlag2 = 0;
		mParams.mStampByte = 0;
		mVoiceContainer.Destroy();
	}

	IPrimitiveNode** pBucket = (IPrimitiveNode**)mPrimitives.mpBucketArray;
	IPrimitiveNode* pNode = *pBucket;
	if (pNode == 0) {
		do {
			++pBucket;
			pNode = *pBucket;
		} while (pNode == 0);
	}

	IPrimitiveNode* const pEnd =
		*(IPrimitiveNode**)((char*)mPrimitives.mpBucketArray + mPrimitives.mnBucketCount * 4);

	while (pNode != pEnd) {
		IPrimitive* const pPrim = pNode->mpValue;
		const u32 nId = pNode->mKey;
		if (pPrim != 0)
			(*(void(__thiscall**)(IPrimitive*))(*(char**)pPrim + 0x00))(pPrim);

		if ((*(u8(__thiscall**)(IPrimitive*, u32))(*(char**)pPrim + 0x20))(pPrim, 0) != 0) {
			const float fVal = (float)(*(double(__thiscall**)(IPrimitive*))(*(char**)pPrim + 0x1c))(pPrim);
			u32 v; *(float*)&v = fVal;
			mVoiceContainer.SetProperty(nId, v);
		}
		(*(void(__thiscall**)(IPrimitive*))(*(char**)pPrim + 0x04))(pPrim);

		pNode = pNode->mpNext;
		while (pNode == 0) {
			++pBucket;
			pNode = *pBucket;
		}
	}
}

// =================================================================================================
// (0x00a2fbe0) Submix::SetPerformanceData
// =================================================================================================
// @ 0x00a2fbe0
u32 Submix::SetPerformanceData(int level, const void* a, u32 b)
{
	mVoiceContainer.MaskPluginBindings(a, b);

	const bool bUnderThreshold = level < (int)mParams.mFlags1;
	u32 nActive = (u32)bUnderThreshold;

	if (bUnderThreshold) {
		if (mParams.mFlag3 != 0)
			return nActive;

		if (mParams.mFlag2 != 0) {
			int* pInst = (int*)(*(void*(__thiscall**)(u32))(*(char**)gEapdDebug + 0x17c))(mSendId);
			if (pInst != 0) {
				void* pSend = *(void**)(pInst + 0x14);
				if (gAudioSystem != 0)
					FUN_0112c600();
				if (gAudioSystem != 0) {
					void* it;
					FUN_00594410(&it);
					IPrimitiveNode* const pItEnd = *(IPrimitiveNode**)
						((char*)mSendPlugins.mpBucketArray + mSendPlugins.mnBucketCount * 4);
					while ((IPrimitiveNode*)it != pItEnd) {
						FUN_0112ccc0(0, &pSend);
						it = *(void**)((char*)it + 4);
						while (it == 0) {
							it = *(void**)((char*)it + 4);
						}
					}
					FUN_0112c620();
				}
			}
		}
		mVoiceContainer.Disconnect();
		mParams.mStamp = *(u32*)((char*)gAudioSystem + 0xe0);
		mParams.mFlag4 = 1;
		mParams.mFlag3 = 1;
		return 1;
	}

	if (mParams.mFlag3 == 0)
		return nActive;

	mVoiceContainer.Create(mParams.mValueByte);
	mVoiceContainer.Connect();
	nActive = mVoiceContainer.CommitBoundProperties();
	if (mParams.mFlag2 != 0) {
		if (gAudioSystem != 0)
			FUN_0112c600();
		if (gAudioSystem != 0) {
			void* it;
			FUN_00594410(&it);
			IPrimitiveNode* const pItEnd = *(IPrimitiveNode**)
				((char*)mSendPlugins.mpBucketArray + mSendPlugins.mnBucketCount * 4);
			while ((IPrimitiveNode*)it != pItEnd) {
				void* pPrim = *(void**)&nActive;
				nActive = FUN_0112ccc0(0, &pPrim);
				it = *(void**)((char*)it + 4);
				while (it == 0) {
					it = *(void**)((char*)it + 4);
				}
			}
			FUN_0112c620();
		}
	}
	mParams.mFlag4 = 0;
	mParams.mFlag3 = 0;
	return nActive;
}

// =================================================================================================
// (0x00a2fe30) Submix::SetProperty
// =================================================================================================
// @ 0x00a2fe30
void Submix::SetProperty(u32 id, u32 value)
{
	if ((value & 0x7fffffff) == 0
			|| (((value - 0x800000) & 0x7f800000) < 0x7f000000)
			|| (((value & 0x7fffffff) - 1) < 0x7fffff)) {
		void* const pPrim = (*(void*(__thiscall**)(u32))(*(char**)gEapdDebug + 0xf8))(id);
		if (pPrim == 0) {
			mVoiceContainer.SetProperty(id, value);
			return;
		}

		IPrimitiveNode* pFound;
		((void(__thiscall*)(RegTable*, u32*, IPrimitiveNode**))FUN_00645ed0)(&mRegisters, &id, &pFound);

		IPrimitive* pCreated = 0;
		IPrimitiveNode* const pEnd =
			*(IPrimitiveNode**)((char*)mRegisters.mpBucketArray + mRegisters.mnBucketCount * 4);

		if (pFound == pEnd) {
			IPrimitiveNode* const pStorage = (IPrimitiveNode*)FUN_00a17090(0x1c);
			if (pStorage != 0)
				pCreated = (IPrimitive*)FUN_00a17100(this);
			if (pCreated != 0)
				(*(void(__thiscall**)(IPrimitive*))(*(char**)pCreated + 0x00))(pCreated);

			FUN_00fccdd0(id);
			((void(__thiscall*)(IPrimitive*, u32))FUN_00a16fd0)(pCreated, value);
			((void(__thiscall*)(RegTable*, IPrimitiveNode*, u32))FUN_00a26ce0)
				(&mRegisters, (IPrimitiveNode*)&pStorage, value & 0xffffff00);
			(*(void(__thiscall**)(Submix*, u32, IPrimitive*))(*(char**)this + 0x18))(this, id, pCreated);
		} else {
			IPrimitive* const pValue = pFound->mpValue;
			if (pValue != 0) {
				(*(void(__thiscall**)(IPrimitive*))(*(char**)pValue + 0x00))(pValue);
				pCreated = pValue;
			}
			((void(__thiscall*)(IPrimitive*, u32))FUN_00a16fd0)(pCreated, value);
		}

		if (pCreated != 0)
			(*(void(__thiscall**)(IPrimitive*))(*(char**)pCreated + 0x04))(pCreated);
	}
}

// =================================================================================================
// (0x00a2ffe0) Submix::ConnectPrimitive
// =================================================================================================
// @ 0x00a2ffe0
u32 Submix::ConnectPrimitive(u32 id, IPrimitive* p)
{
	IPrimitiveNode* pFound;
	((void(__thiscall*)(PHTable*, u32*, IPrimitiveNode**))FUN_00645ed0)(&mPrimitives, &id, &pFound);

	IPrimitiveNode* const pEnd =
		*(IPrimitiveNode**)((char*)mPrimitives.mpBucketArray + mPrimitives.mnBucketCount * 4);

	if (pFound == pEnd) {
		if (p != 0)
			(*(void(__thiscall**)(IPrimitive*))(*(char**)p + 0x00))(p);
		IPrimitive* const pNew = p;
		if (pNew != 0)
			(*(void(__thiscall**)(IPrimitive*))(*(char**)pNew + 0x00))(pNew);
		FUN_00a136f0((void*)&pFound, (void*)&pFound, id & 0xffffff00);
		if (pNew != 0)
			(*(void(__thiscall**)(IPrimitive*))(*(char**)pNew + 0x04))(pNew);
		if (p != 0)
			(*(void(__thiscall**)(IPrimitive*))(*(char**)p + 0x04))(p);
		return 1;
	}

	void* const pPrim = (*(void*(__thiscall**)(u32))(*(char**)gEapdDebug + 0xf8))(id);
	if (pPrim == 0)
		return 0;

	IPrimitive* pExisting = pFound->mpValue;
	IPrimitive* pMatch = 0;
	if (pExisting != 0)
		pMatch = (IPrimitive*)(*(void*(__thiscall**)(IPrimitive*, u32))(*(char**)pExisting + 0x0c))(pExisting, 0x4e73a43a);

	if (pMatch == 0
			|| (*(int(__thiscall**)(IPrimitive*))(*(char**)pMatch + 0x30))(pMatch) != (int)(long)this) {
		void* const pMem = FUN_00a16ad0(0x6c);
		IPrimitive* pAgg = 0;
		if (pMem != 0)
			pAgg = (IPrimitive*)FUN_00a16d00((u32)(long)this);
		if (pAgg != 0)
			(*(void(__thiscall**)(IPrimitive*))(*(char**)pAgg + 0x00))(pAgg);

		((void(__thiscall*)(IPrimitive*, void*))FUN_00a16a90)(pExisting, pPrim);
		(*(void(__thiscall**)(IPrimitive*, IPrimitive*))(*(char**)pExisting + 0x10))(pExisting, pExisting);
		(*(void(__thiscall**)(IPrimitive*, IPrimitive*))(*(char**)pAgg + 0x10))(pAgg, pAgg);
		(*(void(__thiscall**)(IPrimitive*))(*(char**)pAgg + 0x10))(pAgg);
		(*(void(__thiscall**)(IPrimitive*, u32))(*(char**)pAgg + 0x2c))(pAgg, 1);

		pExisting = pFound->mpValue;
		if (pAgg != pExisting) {
			(*(void(__thiscall**)(IPrimitive*))(*(char**)pAgg + 0x00))(pAgg);
			pFound->mpValue = pAgg;
			if (pExisting != 0)
				(*(void(__thiscall**)(IPrimitive*))(*(char**)pExisting + 0x04))(pExisting);
		}
		(*(void(__thiscall**)(IPrimitive*))(*(char**)pAgg + 0x04))(pAgg);
	} else {
		(*(void(__thiscall**)(IPrimitive*, u32))(*(char**)pMatch + 0x10))(pMatch, id);
	}
	return 1;
}

// =================================================================================================
// (0x00a301f0) EA::Audio::Submix::DisconnectPrimitive
// =================================================================================================
// @ 0x00a301f0
void Submix::DisconnectPrimitive(u32 id, IPrimitive* p)
{
	PHTable& tbl = mPrimitives;
	HTIter it;
	((void(__thiscall*)(PHTable*, IPrimitiveNode**, u32*))FUN_00645ed0)(&tbl, (IPrimitiveNode**)&it, &id);

	if (it.mpNode == (IPrimitiveNode*)tbl.mpBucketArray[tbl.mnBucketCount])
		return;

	IPrimitive* const pExisting = it.mpNode->mpValue;
	if (pExisting != 0) {
		IPrimitive* const pMatch =
			(IPrimitive*)(*(void*(__thiscall**)(IPrimitive*, u32))(*(char**)pExisting + 0x0c))(pExisting, 0x4e73a43a);
		if (pMatch != 0) {
			(*(void(__thiscall**)(IPrimitive*, IPrimitive*))(*(char**)pMatch + 0x14))(pMatch, p);
			return;
		}
	}
	if (pExisting == p) {
		((void(__thiscall*)(PHTable*, HTIter, HTIter*))FUN_00d2c9f0)(&tbl, it, &it);
	}
}

// =================================================================================================
// (0x00a30280) Submix destructor
// =================================================================================================
// @ 0x00a30280
Submix::~Submix()
{
}