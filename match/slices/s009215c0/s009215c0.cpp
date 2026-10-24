// EASTL red-black-tree core (009215C0..00921880) and EA::Thread primitives (00921B40..00922480).
// The rbtree helpers (RBTreeDecrement / RBTreeRotateLeft / RBTreeRotateRight) and the two
// kernel32 wrappers are byte-exact; RBTreeInsert/RBTreeErase use the closest available EASTL
// source (2017 ModAPI form) and are behaviourally complete but not byte-exact against 2008 EASTL.
#include <windows.h>
#define EASTL_API
#include <stddef.h>
#include <string.h>
#include <new>

// ================================================================== EASTL rbtree
struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char              mColor;
};
namespace eastl {
enum { kRBTreeColorRed = 0, kRBTreeColorBlack = 1 };
enum RBTreeSide { kRBTreeSideLeft, kRBTreeSideRight };
rbtree_node_base* RBTreeGetMinChild(const rbtree_node_base* p){ while (p->mpNodeLeft) p = p->mpNodeLeft; return const_cast<rbtree_node_base*>(p); }
rbtree_node_base* RBTreeGetMaxChild(const rbtree_node_base* p){ while (p->mpNodeRight) p = p->mpNodeRight; return const_cast<rbtree_node_base*>(p); }
template <class T> void swap(T& a, T& b){ T t = a; a = b; b = t; }

// @ 0x009215C0
rbtree_node_base* RBTreeDecrement(const rbtree_node_base* pNode)
{
    if (pNode->mpNodeParent->mpNodeParent == pNode && pNode->mColor == kRBTreeColorRed)
        return pNode->mpNodeRight;
    if (pNode->mpNodeLeft)
        return RBTreeGetMaxChild(pNode->mpNodeLeft);
    rbtree_node_base* p = pNode->mpNodeParent;
    while (pNode == p->mpNodeLeft) { pNode = p; p = p->mpNodeParent; }
    return p;
}

// @ 0x00921600
rbtree_node_base* RBTreeRotateLeft(rbtree_node_base* pNode, rbtree_node_base* pNodeRoot)
{
    rbtree_node_base* const pNodeTemp = pNode->mpNodeRight;
    pNode->mpNodeRight = pNodeTemp->mpNodeLeft;
    if (pNodeTemp->mpNodeLeft) pNodeTemp->mpNodeLeft->mpNodeParent = pNode;
    pNodeTemp->mpNodeParent = pNode->mpNodeParent;
    if (pNode == pNodeRoot) pNodeRoot = pNodeTemp;
    else if (pNode == pNode->mpNodeParent->mpNodeLeft) pNode->mpNodeParent->mpNodeLeft = pNodeTemp;
    else pNode->mpNodeParent->mpNodeRight = pNodeTemp;
    pNodeTemp->mpNodeLeft = pNode;
    pNode->mpNodeParent = pNodeTemp;
    return pNodeRoot;
}

// @ 0x00921650
rbtree_node_base* RBTreeRotateRight(rbtree_node_base* pNode, rbtree_node_base* pNodeRoot)
{
    rbtree_node_base* const pNodeTemp = pNode->mpNodeLeft;
    pNode->mpNodeLeft = pNodeTemp->mpNodeRight;
    if (pNodeTemp->mpNodeRight) pNodeTemp->mpNodeRight->mpNodeParent = pNode;
    pNodeTemp->mpNodeParent = pNode->mpNodeParent;
    if (pNode == pNodeRoot) pNodeRoot = pNodeTemp;
    else if (pNode == pNode->mpNodeParent->mpNodeRight) pNode->mpNodeParent->mpNodeRight = pNodeTemp;
    else pNode->mpNodeParent->mpNodeLeft = pNodeTemp;
    pNodeTemp->mpNodeRight = pNode;
    pNode->mpNodeParent = pNodeTemp;
    return pNodeRoot;
}
	/// RBTreeInsert
	/// Insert a node into the tree and rebalance the tree as a result of the 
	/// disturbance the node introduced.
	///
	// @ 0x009216A0
	EASTL_API void RBTreeInsert(rbtree_node_base* pNode,
								rbtree_node_base* pNodeParent, 
								rbtree_node_base* pNodeAnchor,
								RBTreeSide insertionSide)
	{
		rbtree_node_base*& pNodeRootRef = pNodeAnchor->mpNodeParent;

		// Initialize fields in new node to insert.
		pNode->mpNodeParent = pNodeParent;
		pNode->mpNodeRight  = NULL;
		pNode->mpNodeLeft   = NULL;
		pNode->mColor       = kRBTreeColorRed;

		// Insert the node.
		if(insertionSide == kRBTreeSideLeft)
		{
			pNodeParent->mpNodeLeft = pNode; // Also makes (leftmost = pNode) when (pNodeParent == pNodeAnchor)

			if(pNodeParent == pNodeAnchor)
			{
				pNodeAnchor->mpNodeParent = pNode;
				pNodeAnchor->mpNodeRight = pNode;
			}
			else if(pNodeParent == pNodeAnchor->mpNodeLeft)
				pNodeAnchor->mpNodeLeft = pNode; // Maintain leftmost pointing to min node
		}
		else
		{
			pNodeParent->mpNodeRight = pNode;

			if(pNodeParent == pNodeAnchor->mpNodeRight)
				pNodeAnchor->mpNodeRight = pNode; // Maintain rightmost pointing to max node
		}

		// Rebalance the tree.
		while((pNode != pNodeRootRef) && (pNode->mpNodeParent->mColor == kRBTreeColorRed)) 
		{
			
			rbtree_node_base* const pNodeParentParent = pNode->mpNodeParent->mpNodeParent;

			if(pNode->mpNodeParent == pNodeParentParent->mpNodeLeft) 
			{
				rbtree_node_base* const pNodeTemp = pNodeParentParent->mpNodeRight;

				if(pNodeTemp && (pNodeTemp->mColor == kRBTreeColorRed)) 
				{
					pNode->mpNodeParent->mColor = kRBTreeColorBlack;
					pNodeTemp->mColor = kRBTreeColorBlack;
					pNodeParentParent->mColor = kRBTreeColorRed;
					pNode = pNodeParentParent;
				}
				else 
				{
					if(pNode->mpNodeParent && pNode == pNode->mpNodeParent->mpNodeRight) 
					{
						pNode = pNode->mpNodeParent;
						pNodeRootRef = RBTreeRotateLeft(pNode, pNodeRootRef);
					}

					
					pNode->mpNodeParent->mColor = kRBTreeColorBlack;
					pNodeParentParent->mColor = kRBTreeColorRed;
					pNodeRootRef = RBTreeRotateRight(pNodeParentParent, pNodeRootRef);
				}
			}
			else 
			{
				rbtree_node_base* const pNodeTemp = pNodeParentParent->mpNodeLeft;

				if(pNodeTemp && (pNodeTemp->mColor == kRBTreeColorRed)) 
				{
					pNode->mpNodeParent->mColor = kRBTreeColorBlack;
					pNodeTemp->mColor = kRBTreeColorBlack;
					pNodeParentParent->mColor = kRBTreeColorRed;
					pNode = pNodeParentParent;
				}
				else 
				{
					

					if(pNode == pNode->mpNodeParent->mpNodeLeft) 
					{
						pNode = pNode->mpNodeParent;
						pNodeRootRef = RBTreeRotateRight(pNode, pNodeRootRef);
					}

					pNode->mpNodeParent->mColor = kRBTreeColorBlack;
					pNodeParentParent->mColor = kRBTreeColorRed;
					pNodeRootRef = RBTreeRotateLeft(pNodeParentParent, pNodeRootRef);
				}
			}
		}

		
		pNodeRootRef->mColor = kRBTreeColorBlack;

	} // RBTreeInsert




	/// RBTreeErase
	/// Erase a node from the tree.
	///
	// @ 0x00921880
	EASTL_API void RBTreeErase(rbtree_node_base* pNode, rbtree_node_base* pNodeAnchor)
	{
		rbtree_node_base*& pNodeRootRef      = pNodeAnchor->mpNodeParent;
		rbtree_node_base*& pNodeLeftmostRef  = pNodeAnchor->mpNodeLeft;
		rbtree_node_base*& pNodeRightmostRef = pNodeAnchor->mpNodeRight;
		rbtree_node_base*  pNodeSuccessor    = pNode;
		rbtree_node_base*  pNodeChild        = NULL;
		rbtree_node_base*  pNodeChildParent  = NULL;

		if(pNodeSuccessor->mpNodeLeft == NULL)         // pNode has at most one non-NULL child.
			pNodeChild = pNodeSuccessor->mpNodeRight;  // pNodeChild might be null.
		else if(pNodeSuccessor->mpNodeRight == NULL)   // pNode has exactly one non-NULL child.
			pNodeChild = pNodeSuccessor->mpNodeLeft;   // pNodeChild is not null.
		else 
		{
			// pNode has two non-null children. Set pNodeSuccessor to pNode's successor. pNodeChild might be NULL.
			pNodeSuccessor = pNodeSuccessor->mpNodeRight;

			while(pNodeSuccessor->mpNodeLeft)
				pNodeSuccessor = pNodeSuccessor->mpNodeLeft;

			pNodeChild = pNodeSuccessor->mpNodeRight;
		}

		// Here we remove pNode from the tree and fix up the node pointers appropriately around it.
		if(pNodeSuccessor == pNode) // If pNode was a leaf node (had both NULL children)...
		{
			pNodeChildParent = pNodeSuccessor->mpNodeParent;  // Assign pNodeReplacement's parent.

			if(pNodeChild) 
				pNodeChild->mpNodeParent = pNodeSuccessor->mpNodeParent;

			if(pNode == pNodeRootRef) // If the node being deleted is the root node...
				pNodeRootRef = pNodeChild; // Set the new root node to be the pNodeReplacement.
			else 
			{
				if(pNode == pNode->mpNodeParent->mpNodeLeft) // If pNode is a left node...
					pNode->mpNodeParent->mpNodeLeft  = pNodeChild;  // Make pNode's replacement node be on the same side.
				else
					pNode->mpNodeParent->mpNodeRight = pNodeChild;
				// Now pNode is disconnected from the bottom of the tree (recall that in this pathway pNode was determined to be a leaf).
			}

			if(pNode == pNodeLeftmostRef) // If pNode is the tree begin() node...
			{
				// Because pNode is the tree begin(), pNode->mpNodeLeft must be NULL.
				// Here we assign the new begin() (first node).
				if(pNode->mpNodeRight && pNodeChild)
				{
					 // Logically pNodeChild should always be valid.
					pNodeLeftmostRef = RBTreeGetMinChild(pNodeChild); 
				}
				else
					pNodeLeftmostRef = pNode->mpNodeParent; // This  makes (pNodeLeftmostRef == end()) if (pNode == root node)
			}

			if(pNode == pNodeRightmostRef) // If pNode is the tree last (rbegin()) node...
			{
				// Because pNode is the tree rbegin(), pNode->mpNodeRight must be NULL.
				// Here we assign the new rbegin() (last node)
				if(pNode->mpNodeLeft && pNodeChild)
				{
					 // Logically pNodeChild should always be valid.
					pNodeRightmostRef = RBTreeGetMaxChild(pNodeChild);
				}
				else // pNodeChild == pNode->mpNodeLeft
					pNodeRightmostRef = pNode->mpNodeParent; // makes pNodeRightmostRef == &mAnchor if pNode == pNodeRootRef
			}
		}
		else // else (pNodeSuccessor != pNode)
		{
			// Relink pNodeSuccessor in place of pNode. pNodeSuccessor is pNode's successor.
			// We specifically set pNodeSuccessor to be on the right child side of pNode, so fix up the left child side.
			pNode->mpNodeLeft->mpNodeParent = pNodeSuccessor; 
			pNodeSuccessor->mpNodeLeft = pNode->mpNodeLeft;

			if(pNodeSuccessor == pNode->mpNodeRight) // If pNode's successor was at the bottom of the tree... (yes that's effectively what this statement means)
				pNodeChildParent = pNodeSuccessor; // Assign pNodeReplacement's parent.
			else
			{
				pNodeChildParent = pNodeSuccessor->mpNodeParent;

				if(pNodeChild)
					pNodeChild->mpNodeParent = pNodeChildParent;

				pNodeChildParent->mpNodeLeft = pNodeChild;

				pNodeSuccessor->mpNodeRight = pNode->mpNodeRight;
				pNode->mpNodeRight->mpNodeParent = pNodeSuccessor;
			}

			if(pNode == pNodeRootRef)
				pNodeRootRef = pNodeSuccessor;
			else if(pNode == pNode->mpNodeParent->mpNodeLeft)
				pNode->mpNodeParent->mpNodeLeft = pNodeSuccessor;
			else 
				pNode->mpNodeParent->mpNodeRight = pNodeSuccessor;

			// Now pNode is disconnected from the tree.

			pNodeSuccessor->mpNodeParent = pNode->mpNodeParent;
			swap(pNodeSuccessor->mColor, pNode->mColor);
		}

		// Here we do tree balancing as per the conventional red-black tree algorithm.
		if(pNode->mColor == kRBTreeColorBlack) 
		{ 
			while((pNodeChild != pNodeRootRef) && ((pNodeChild == NULL) || (pNodeChild->mColor == kRBTreeColorBlack)))
			{
				if(pNodeChild == pNodeChildParent->mpNodeLeft) 
				{
					rbtree_node_base* pNodeTemp = pNodeChildParent->mpNodeRight;

					if(pNodeTemp->mColor == kRBTreeColorRed) 
					{
						pNodeTemp->mColor = kRBTreeColorBlack;
						pNodeChildParent->mColor = kRBTreeColorRed;
						pNodeRootRef = RBTreeRotateLeft(pNodeChildParent, pNodeRootRef);
						pNodeTemp = pNodeChildParent->mpNodeRight;
					}

					if(((pNodeTemp->mpNodeLeft  == NULL) || (pNodeTemp->mpNodeLeft->mColor  == kRBTreeColorBlack)) &&
						((pNodeTemp->mpNodeRight == NULL) || (pNodeTemp->mpNodeRight->mColor == kRBTreeColorBlack))) 
					{
						pNodeTemp->mColor = kRBTreeColorRed;
						pNodeChild = pNodeChildParent;
						pNodeChildParent = pNodeChildParent->mpNodeParent;
					} 
					else 
					{
						if((pNodeTemp->mpNodeRight == NULL) || (pNodeTemp->mpNodeRight->mColor == kRBTreeColorBlack)) 
						{
							pNodeTemp->mpNodeLeft->mColor = kRBTreeColorBlack;
							pNodeTemp->mColor = kRBTreeColorRed;
							pNodeRootRef = RBTreeRotateRight(pNodeTemp, pNodeRootRef);
							pNodeTemp = pNodeChildParent->mpNodeRight;
						}

						pNodeTemp->mColor = pNodeChildParent->mColor;
						pNodeChildParent->mColor = kRBTreeColorBlack;

						if(pNodeTemp->mpNodeRight) 
							pNodeTemp->mpNodeRight->mColor = kRBTreeColorBlack;

						pNodeRootRef = RBTreeRotateLeft(pNodeChildParent, pNodeRootRef);
						break;
					}
				} 
				else 
				{   
					// The following is the same as above, with mpNodeRight <-> mpNodeLeft.
					rbtree_node_base* pNodeTemp = pNodeChildParent->mpNodeLeft;

					if(pNodeTemp->mColor == kRBTreeColorRed) 
					{
						pNodeTemp->mColor        = kRBTreeColorBlack;
						pNodeChildParent->mColor = kRBTreeColorRed;

						pNodeRootRef = RBTreeRotateRight(pNodeChildParent, pNodeRootRef);
						pNodeTemp = pNodeChildParent->mpNodeLeft;
					}

					if(((pNodeTemp->mpNodeRight == NULL) || (pNodeTemp->mpNodeRight->mColor == kRBTreeColorBlack)) &&
						((pNodeTemp->mpNodeLeft  == NULL) || (pNodeTemp->mpNodeLeft->mColor  == kRBTreeColorBlack))) 
					{
						pNodeTemp->mColor = kRBTreeColorRed;
						pNodeChild       = pNodeChildParent;
						pNodeChildParent = pNodeChildParent->mpNodeParent;
					} 
					else 
					{
						if((pNodeTemp->mpNodeLeft == NULL) || (pNodeTemp->mpNodeLeft->mColor == kRBTreeColorBlack)) 
						{
							pNodeTemp->mpNodeRight->mColor = kRBTreeColorBlack;
							pNodeTemp->mColor              = kRBTreeColorRed;

							pNodeRootRef = RBTreeRotateLeft(pNodeTemp, pNodeRootRef);
							pNodeTemp = pNodeChildParent->mpNodeLeft;
						}

						pNodeTemp->mColor = pNodeChildParent->mColor;
						pNodeChildParent->mColor = kRBTreeColorBlack;

						if(pNodeTemp->mpNodeLeft) 
							pNodeTemp->mpNodeLeft->mColor = kRBTreeColorBlack;

						pNodeRootRef = RBTreeRotateRight(pNodeChildParent, pNodeRootRef);
						break;
					}
				}
			}

			if(pNodeChild)
				pNodeChild->mColor = kRBTreeColorBlack;
		}

	} // RBTreeErase
} // namespace eastl

// ================================================================== EA::Thread primitives
namespace EA { namespace Thread {

// CRT/kernel imports are dllimport through the IAT.
extern "C" __declspec(dllimport) HANDLE __stdcall GetCurrentThread();
extern "C" __declspec(dllimport) BOOL __stdcall GetThreadPriority(HANDLE);
extern "C" __declspec(dllimport) BOOL __stdcall SetThreadPriority(HANDLE, int);
extern "C" __declspec(dllimport) DWORD __stdcall SleepEx(DWORD, BOOL);
extern "C" __declspec(dllimport) HANDLE __stdcall GetCurrentProcess();

unsigned GetThreadTime();              // 0x0094d340 (jmp GetTickCount)
void ThreadSleep(unsigned* pMilliseconds);

extern "C" long _InterlockedIncrement(volatile long*);
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedIncrement, _InterlockedExchangeAdd, _InterlockedExchange)

// EA::Thread::AtomicInt<T> -- one value, ctor stores via interlocked exchange (xchg [this],reg).
template <typename T>
class AtomicInt {
public:
    volatile T mValue;                                  // +0x00
    AtomicInt(T n = 0) { SetValue(n); }
    void SetValue(T n) { _InterlockedExchange((long*)&mValue, n); }
};

// EA::Thread::ThreadName -- 0x11-byte name holder (flag byte at 0, "name" string at +1).  PDB: ThreadName.
struct ThreadName {
    unsigned char mFlag;  // +0x00
    char    mName[0x10];  // +0x01
    char* Set(unsigned char flag, const char* pName);   // 0x00921e00
};

// EA::Thread::MutexParameters -- { bool mbIntraProcess; char mName[...] }.  PDB shape.
struct MutexParameters {
    unsigned char mbIntraProcess;  // +0x00
    char          mName[0x10];     // +0x01
    MutexParameters() {}
    MutexParameters(int count, bool intra, const char* name);  // 0x009225d0-style, unused
};

// EA::Thread::ConditionParameters -- { bool mbIntraProcess; char mName[...] }.
struct ConditionParameters {
    unsigned char mbIntraProcess;  // +0x00
    char          mName[0x10];     // +0x01
};

// EA::Thread::RWMutexParameters -- { bool mbIntraProcess; char mName[...] }.
struct RWMutexParameters {
    unsigned char mbIntraProcess;  // +0x00
    char          mName[0x10];     // +0x01
};

// EA::Thread::SemaphoreParameters -- { int mnCount; bool mbIntraProcess; char mName[...] }.
struct SemaphoreParameters {
    int           mnCount;         // +0x00
    bool          mbIntraProcess;  // +0x04
    char          mName[0x10];     // +0x05
    SemaphoreParameters() {}
    SemaphoreParameters(int count, bool intra, const char* name);  // 0x009225d0
};

struct EAMutexData {
    unsigned __int64 mData[4];        // +0x00
    int              mnLockCount;     // +0x20
    unsigned char    mbIntraProcess;  // +0x24
    void*            mThreadId;       // +0x28
};
struct EASemaphoreData {
    void* mhSemaphore;       // +0x00
    int   mnCount;           // +0x04
    int   mnCancelCount;     // +0x08
    bool  mbIntraProcess;    // +0x0c
    __declspec(noinline) ~EASemaphoreData();   // 0x00922610
};
class Semaphore {
public:
    EASemaphoreData mSemaphoreData;                     // +0x00, size 0x10
    Semaphore(const SemaphoreParameters* p, bool bDefault);  // 0x00922820
    bool Init(const SemaphoreParameters* p);            // 0x00922620
    int  Wait(unsigned const& timeout);                 // 0x00922690
    int  Post(int n);                                   // 0x00922740
};
class Mutex {
public:
    EAMutexData mMutexData;      // +0x00, size 0x30
    Mutex(const MutexParameters* p = 0, bool bDefault = true);   // 0x009222a0
    __declspec(noinline) ~Mutex();                              // 0x00922130
    bool Init(const MutexParameters* p);                        // 0x00922150
    int  Lock(unsigned const& timeout);                         // 0x009221b0
    int  Unlock();                                              // 0x00922270
};
// EA::Thread::EAConditionData at +0x00, size 0x60.
struct EAConditionData {
    AtomicInt<int> mnWaitersBlocked;    // +0x00
    int            mnWaitersToUnblock;  // +0x04
    int            mnWaitersDone;       // +0x08
    Semaphore      mSemaphoreBlockQueue;// +0x0c
    Semaphore      mSemaphoreBlockLock; // +0x1c
    Mutex          mUnblockLock;        // +0x30
    __forceinline EAConditionData()
        : mnWaitersBlocked(0), mnWaitersToUnblock(0), mnWaitersDone(0),
          mSemaphoreBlockQueue((const SemaphoreParameters*)0, false),
          mSemaphoreBlockLock((const SemaphoreParameters*)0, false),
          mUnblockLock((const MutexParameters*)0, false) {}
};
class Condition {
public:
    EAConditionData mConditionData;                      // +0x00, size 0x60
    Condition(const ConditionParameters* p = 0, bool bInit = true);  // 0x00921f00
    __declspec(noinline) ~Condition();                    // 0x00921e40
    bool Init(const ConditionParameters* pParameters);   // 0x00921e60
    int  Wait(Mutex* pMutex, unsigned const& timeout);   // 0x00921f80
    bool Signal(bool bAll);                              // 0x00922050
};
// unblockLock timeout constant used by Condition/Mutex calls (DAT_0143dc58 / _64)
extern unsigned g_mutexTimeout;   // 0x0143dc58
extern unsigned g_rwTimeout;      // 0x0143dc64

// EA::Thread::RWMutex -- PDB EARWMutexData, size 0x100.
struct EARWMutexData {
    int       mnReadWaiters;    // +0x00
    int       mnWriteWaiters;   // +0x04
    int       mnReaders;        // +0x08
    void*     mThreadIdWriter;  // +0x0c
    Mutex     mMutex;           // +0x10
    Condition mReadCondition;   // +0x40
    Condition mWriteCondition;  // +0xa0
};
class RWMutex {
public:
    enum LockType { kLockTypeNone = 0, kLockTypeRead = 1, kLockTypeWrite = 2 };
    EARWMutexData mRWMutexData;         // +0x00, size 0x100
    ~RWMutex();                         // 0x00922310
    bool Init(const RWMutexParameters* pParameters);  // 0x00922330
    int  Lock(LockType lockType, unsigned const& timeout);   // 0x009223a0
    int  Unlock();                      // 0x00922480
};

// @ 0x009222A0
Mutex::Mutex(const MutexParameters* p, bool bDefault) {
    mMutexData.mnLockCount = 0;
    mMutexData.mThreadId = 0;
    mMutexData.mbIntraProcess = true;
    memset(mMutexData.mData, 0, sizeof(mMutexData.mData));
    if (p == 0 && bDefault) {
        MutexParameters d;
        d.mbIntraProcess = 1;
        d.mName[0] = 0;
        Init(&d);
        return;
    }
    Init(p);
}
// @ 0x00922130
Mutex::~Mutex() {
    if (mMutexData.mbIntraProcess) { DeleteCriticalSection((CRITICAL_SECTION*)this); return; }
    CloseHandle(*(HANDLE*)mMutexData.mData);
}
// @ 0x00922150
bool Mutex::Init(const MutexParameters* p) {
    if (p) {
        mMutexData.mnLockCount = 0;
        unsigned char intra = p->mbIntraProcess;
        mMutexData.mbIntraProcess = intra;
        if (intra) { InitializeCriticalSection((CRITICAL_SECTION*)this); return true; }
        HANDLE h = CreateMutexA(0, 0, p->mName[0] ? p->mName : 0);
        *(HANDLE*)mMutexData.mData = h;
        return h != 0;
    }
    return false;
}
// @ 0x009221B0
int Mutex::Lock(unsigned const& timeout) {
    if (!mMutexData.mbIntraProcess) {
        unsigned t = timeout;
        if (t != 0xffffffffu && t != 0) {
            unsigned now = GetThreadTime();
            t = (now < t) ? (t - now) : 0;
        }
        DWORD r = WaitForSingleObject(*(HANDLE*)mMutexData.mData, t);
        if (r == 0x102) return -2;
        if (r != 0) return -1;
    } else if (timeout == 0xffffffffu) {
        EnterCriticalSection((CRITICAL_SECTION*)this);
    } else if (!TryEnterCriticalSection((CRITICAL_SECTION*)this)) {
        for (;;) {
            unsigned now = GetThreadTime();
            if (timeout <= now) return -2;
            unsigned one = 1;
            ThreadSleep(&one);
            if (TryEnterCriticalSection((CRITICAL_SECTION*)this)) break;
        }
    }
    return ++mMutexData.mnLockCount;
}
// @ 0x00922270
int Mutex::Unlock() {
    int n = --mMutexData.mnLockCount;
    if (mMutexData.mbIntraProcess) { LeaveCriticalSection((CRITICAL_SECTION*)this); return n; }
    ReleaseMutex(*(HANDLE*)mMutexData.mData);
    return n;
}

// @ 0x00921DF0
void ThreadSleep(unsigned* pMilliseconds) { SleepEx(*pMilliseconds, TRUE); }
// @ 0x00921D70
void GetCurrentThreadPriority() { GetThreadPriority(GetCurrentThread()); }
// @ 0x00921D80
bool SetCurrentThreadPriority(int nPriority) {
    HANDLE h = GetCurrentThread();
    int r = SetThreadPriority(h, nPriority);
    h = GetCurrentThread();
    for (;;) {
        if (r != 0) return true;
        if (nPriority > 0xe)  { return SetThreadPriority(h, 0xf) != 0; }
        if (nPriority < -0xe) { return SetThreadPriority(h, -0xf) != 0; }
        r = SetThreadPriority(h, nPriority);
        ++nPriority;
    }
}

// ---- thread-handle table (16 slots + a critical section) at 0x01667BC0
struct ThreadGroup {
    HANDLE           mThreads[16];   // +0x00
    CRITICAL_SECTION mCS;            // +0x40
    void ClearThreads(bool bWait);              // 0x00921B40
    void AddRemoveThread(HANDLE h, char bAdd);  // 0x00921BC0
};
extern ThreadGroup g_ThreadGroup;
extern unsigned long g_ThreadTlsIndex;   // 0x0154DF38

// @ 0x00921B40
void ThreadGroup::ClearThreads(bool bWait) {
    EnterCriticalSection(&mCS);
    for (unsigned i = 0; i < 16; ++i) {
        HANDLE h = mThreads[i];
        if (h) {
            DWORD code = 0;
            if (!bWait) {
                if (GetExitCodeThread(h, &code) && code == 0x103) continue;
            }
            CloseHandle(mThreads[i]);
            mThreads[i] = 0;
        }
    }
    LeaveCriticalSection(&mCS);
}
// @ 0x00921BC0
void ThreadGroup::AddRemoveThread(HANDLE h, char bAdd) {
    if (!h) return;
    EnterCriticalSection(&mCS);
    if (bAdd) {
        for (unsigned i = 0; i < 16; ++i) {
            if (mThreads[i] == 0) { mThreads[i] = h; LeaveCriticalSection(&mCS); return; }
        }
        CloseHandle(h);
        LeaveCriticalSection(&mCS);
        return;
    }
    for (unsigned i = 0; i < 16; ++i) {
        if (mThreads[i] == h) {
            CloseHandle(h);
            mThreads[i] = 0;
            break;
        }
    }
    LeaveCriticalSection(&mCS);
}
// @ 0x00921C50
void SetCurrentThreadHandle(HANDLE h, char bAdd) {
    if (g_ThreadTlsIndex == 0xfffffffful) {
        g_ThreadTlsIndex = TlsAlloc();
        if (g_ThreadTlsIndex == 0xfffffffful) return;
    }
    g_ThreadGroup.ClearThreads(false);
    if (bAdd) {
        if (h) g_ThreadGroup.AddRemoveThread(h, 1);
        else {
            HANDLE t = TlsGetValue(g_ThreadTlsIndex);
            if (t) g_ThreadGroup.AddRemoveThread(t, 0);
        }
    }
    TlsSetValue(g_ThreadTlsIndex, h);
}
// @ 0x00921CC0
HANDLE GetThreadId() {
    if (g_ThreadTlsIndex != 0xfffffffful) {
        HANDLE t = TlsGetValue(g_ThreadTlsIndex);
        if (t) return t;
    }
    HANDLE src = GetCurrentThread();
    HANDLE proc = GetCurrentProcess();
    HANDLE dup = 0;
    if (!DuplicateHandle(proc, src, proc, &dup, 0, TRUE, 2)) return dup;
    if (g_ThreadTlsIndex == 0xfffffffful) {
        g_ThreadTlsIndex = TlsAlloc();
        if (g_ThreadTlsIndex == 0xfffffffful) return dup;
    }
    g_ThreadGroup.ClearThreads(false);
    if (dup) g_ThreadGroup.AddRemoveThread(dup, 1);
    else {
        HANDLE t = TlsGetValue(g_ThreadTlsIndex);
        if (t) g_ThreadGroup.AddRemoveThread(t, 0);
    }
    TlsSetValue(g_ThreadTlsIndex, dup);
    return dup;
}

// @ 0x00921E00
char* ThreadName::Set(unsigned char flag, const char* src) {
    char* dst = (char*)&mFlag;
    dst[0] = (char)flag;
    if (src) { strncpy(dst + 1, src, 0xf); dst[0x10] = 0; return dst; }
    dst[1] = 0;
    return dst;
}

}} // namespace EA::Thread

// ================================================================== Condition / Semaphore / RWMutex bodies
namespace EA { namespace Thread {

// EASemaphoreData destroy (0x00922610): close the handle if set.
__declspec(noinline) EASemaphoreData::~EASemaphoreData() { if (mhSemaphore) CloseHandle(mhSemaphore); }

// @ 0x00921E40
Condition::~Condition() {
    // member destructors run automatically after this (empty) body: unblock mutex, then
    // the two semaphores -- exactly the original's 0x30 / 0x1c / 0x0c sequence.
}


// @ 0x00921F80
int Condition::Wait(Mutex* pMutex, unsigned const& timeout) {
    _InterlockedIncrement((volatile long*)&mConditionData.mnWaitersBlocked);
    int r = pMutex->Unlock();
    if (r < 0) return r;
    r = mConditionData.mSemaphoreBlockQueue.Wait(timeout);
    mConditionData.mUnblockLock.Lock(g_mutexTimeout);
    int n = mConditionData.mnWaitersToUnblock;
    if (n != 0) {
        mConditionData.mnWaitersToUnblock = n - 1;
    } else {
        ++mConditionData.mnWaitersDone;
        if (mConditionData.mnWaitersDone == 0x3fffffff) {
            mConditionData.mSemaphoreBlockLock.Wait(g_mutexTimeout);
            _InterlockedExchangeAdd((volatile long*)&mConditionData.mnWaitersBlocked,
                                    -mConditionData.mnWaitersDone);
            mConditionData.mSemaphoreBlockLock.Post(1);
            mConditionData.mnWaitersDone = 0;
        }
    }
    mConditionData.mUnblockLock.Unlock();
    if (n == 1) mConditionData.mSemaphoreBlockLock.Post(1);
    if (pMutex->Lock(g_mutexTimeout) == -1) return -1;
    return r;
}
// @ 0x00922050
bool Condition::Signal(bool bBroadcast) {
    if (mConditionData.mUnblockLock.Lock(g_mutexTimeout) < 0) return false;
    int n;
    if (mConditionData.mnWaitersToUnblock != 0) {
        if (_InterlockedExchangeAdd((volatile long*)&mConditionData.mnWaitersBlocked, 0) == 0) {
            mConditionData.mUnblockLock.Unlock();
            return true;
        }
        if (bBroadcast) {
            n = _InterlockedExchange((volatile long*)&mConditionData.mnWaitersBlocked, 0);
            mConditionData.mnWaitersToUnblock += n;
            mConditionData.mUnblockLock.Unlock();
            mConditionData.mSemaphoreBlockQueue.Post(n);
            return true;
        }
        ++mConditionData.mnWaitersToUnblock;
        n = 1;
    } else {
        if (_InterlockedExchangeAdd((volatile long*)&mConditionData.mnWaitersBlocked, 0)
                <= mConditionData.mnWaitersDone) {
            mConditionData.mUnblockLock.Unlock();
            return true;
        }
        if (mConditionData.mSemaphoreBlockLock.Wait(g_mutexTimeout) == -1) {
            mConditionData.mUnblockLock.Unlock();
            return false;
        }
        if (mConditionData.mnWaitersDone != 0) {
            _InterlockedExchangeAdd((volatile long*)&mConditionData.mnWaitersBlocked,
                                    -mConditionData.mnWaitersDone);
            mConditionData.mnWaitersDone = 0;
        }
        if (bBroadcast) {
            n = _InterlockedExchange((volatile long*)&mConditionData.mnWaitersBlocked, 0);
            mConditionData.mnWaitersToUnblock = n;
            mConditionData.mUnblockLock.Unlock();
            mConditionData.mSemaphoreBlockQueue.Post(n);
            return true;
        }
        mConditionData.mnWaitersToUnblock = 1;
        n = 1;
    }
    _InterlockedExchangeAdd((volatile long*)&mConditionData.mnWaitersBlocked, -1);
    mConditionData.mUnblockLock.Unlock();
    mConditionData.mSemaphoreBlockQueue.Post(n);
    return true;
}

// @ 0x00921E60
bool Condition::Init(const ConditionParameters* pParameters) {
    if (!pParameters) return false;
    const char* name = (pParameters->mName[0] != 0) ? pParameters->mName : 0;
    unsigned char flag = pParameters->mbIntraProcess;
    SemaphoreParameters q(0, flag, name);
    SemaphoreParameters r(1, flag, name);
    ThreadName tn;
    tn.Set(flag, name);
    if (!mConditionData.mSemaphoreBlockQueue.Init(&q)) return false;
    if (!mConditionData.mSemaphoreBlockLock.Init(&r)) return false;
    if (!mConditionData.mUnblockLock.Init((const MutexParameters*)&tn)) return false;
    return true;
}
// @ 0x009225D0
SemaphoreParameters::SemaphoreParameters(int count, bool intra, const char* name) {
    mnCount = count;
    mbIntraProcess = intra;
    if (name) { strncpy(mName, name, 0xf); mName[0xf] = 0; }
    else mName[0] = 0;
}
// @ 0x00922820
Semaphore::Semaphore(const SemaphoreParameters* p, bool bDefault) {
    mSemaphoreData.mhSemaphore = 0;
    mSemaphoreData.mnCount = 0;
    mSemaphoreData.mnCancelCount = 0;
    mSemaphoreData.mbIntraProcess = true;
    if (p == 0 && bDefault) {
        SemaphoreParameters d;
        d.mnCount = 0;
        d.mbIntraProcess = false;
        d.mName[0] = 0;
        Init(&d);
        return;
    }
    Init(p);
}
// @ 0x00921F00
Condition::Condition(const ConditionParameters* pParameters, bool bInitialize)
    : mConditionData() {
    ConditionParameters lDefault;
    if (pParameters == 0 && bInitialize) {
        lDefault.mbIntraProcess = true;
        lDefault.mName[0] = 0;
        pParameters = &lDefault;
    }
    Init(pParameters);
}

// @ 0x00922310
RWMutex::~RWMutex() {
    // member destructors run automatically after this (empty) body: write condition,
    // read condition, then the mutex -- the original's 0xa0 / 0x40 / 0x10 sequence.
}
// @ 0x00922330
bool RWMutex::Init(const RWMutexParameters* pParameters) {
    if (!pParameters) return false;
    unsigned char flag = pParameters->mbIntraProcess;
    ThreadName tn;
    tn.Set(flag, 0);
    mRWMutexData.mMutex.Init((const MutexParameters*)&tn);
    ThreadName tn2;
    tn2.Set(flag, 0);
    mRWMutexData.mReadCondition.Init((const ConditionParameters*)&tn2);
    mRWMutexData.mWriteCondition.Init((const ConditionParameters*)&tn2);
    return true;
}
// @ 0x009223A0
int RWMutex::Lock(LockType lockType, unsigned const& timeout) {
    Mutex* m = &mRWMutexData.mMutex;
    int r = 0;
    m->Lock(g_rwTimeout);
    if (lockType == kLockTypeRead) {
        while (mRWMutexData.mThreadIdWriter != 0) {
            ++mRWMutexData.mnReadWaiters;
            r = mRWMutexData.mReadCondition.Wait(m, timeout);
            --mRWMutexData.mnReadWaiters;
            if (r == -2) { m->Unlock(); return -2; }
        }
        r = ++mRWMutexData.mnReaders;
        m->Unlock();
        return r;
    }
    if (lockType == kLockTypeWrite) {
        while (mRWMutexData.mnReaders > 0 || mRWMutexData.mThreadIdWriter != 0) {
            ++mRWMutexData.mnWriteWaiters;
            r = mRWMutexData.mWriteCondition.Wait(m, timeout);
            --mRWMutexData.mnWriteWaiters;
            if (r == -2) { m->Unlock(); return -2; }
        }
        r = 1;
        mRWMutexData.mThreadIdWriter = GetThreadId();
    }
    m->Unlock();
    return r;
}
// @ 0x00922480
int RWMutex::Unlock() {
    Mutex* m = &mRWMutexData.mMutex;
    int r;
    m->Lock(g_rwTimeout);
    if (mRWMutexData.mThreadIdWriter != 0) {
        mRWMutexData.mThreadIdWriter = 0;
    } else {
        r = --mRWMutexData.mnReaders;
        if (r > 0) { m->Unlock(); return r; }
    }
    if (mRWMutexData.mnWriteWaiters > 0) {
        mRWMutexData.mWriteCondition.Signal(false);
        m->Unlock();
        return 0;
    }
    if (mRWMutexData.mnReadWaiters > 0) mRWMutexData.mReadCondition.Signal(true);
    m->Unlock();
    return 0;
}
}} // namespace EA::Thread

