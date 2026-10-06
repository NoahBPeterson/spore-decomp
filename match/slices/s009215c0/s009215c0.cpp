// EASTL red-black-tree core (009215C0..00921880) and EA::Thread primitives (00921B40..00922480).
// The rbtree helpers (RBTreeDecrement / RBTreeRotateLeft / RBTreeRotateRight) and the two
// kernel32 wrappers are byte-exact; RBTreeInsert/RBTreeErase use the closest available EASTL
// source (2017 ModAPI form) and are behaviourally complete but not byte-exact against 2008 EASTL.
#include <windows.h>
#define EASTL_API
#include <stddef.h>
#include <string.h>

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

unsigned GetThreadTime();
void ThreadSleep(unsigned* pMilliseconds);

struct EAMutexData {
    unsigned __int64 mData[4];   // +0x00
    int              mnLockCount;    // +0x20
    bool             mbIntraProcess; // +0x24
    void*            mThreadId;      // +0x28
};
class Mutex {
public:
    EAMutexData mMutexData;      // +0x00, size 0x30
    Mutex(int name, char intraProcess);
    ~Mutex();
    bool Init(char* pName);
    int  Lock(unsigned* pTimeout);
    int  Unlock();
};

// @ 0x009222A0
Mutex::Mutex(int name, char intraProcess) {
    mMutexData.mnLockCount = 0;
    mMutexData.mThreadId = 0;
    mMutexData.mbIntraProcess = true;
    memset(mMutexData.mData, 0, sizeof(mMutexData.mData));
    if (name == 0 && intraProcess != 0) { char n[2]; n[0] = 1; n[1] = 0; Init(n); return; }
    Init((char*)name);
}
// @ 0x00922130
Mutex::~Mutex() {
    if (mMutexData.mbIntraProcess) { DeleteCriticalSection((CRITICAL_SECTION*)this); return; }
    CloseHandle(*(HANDLE*)mMutexData.mData);
}
// @ 0x00922150
bool Mutex::Init(char* pName) {
    if (!pName) return false;
    mMutexData.mnLockCount = 0;
    mMutexData.mbIntraProcess = (*pName != 0);
    if (mMutexData.mbIntraProcess) { InitializeCriticalSection((CRITICAL_SECTION*)this); return true; }
    HANDLE h = CreateMutexA(0, 0, pName[1] ? (pName + 1) : 0);
    *(HANDLE*)mMutexData.mData = h;
    return h != 0;
}
// @ 0x009221B0
int Mutex::Lock(unsigned* pTimeout) {
    if (!mMutexData.mbIntraProcess) {
        unsigned t = *pTimeout;
        if (t != 0xffffffffu && t != 0) {
            unsigned now = GetThreadTime();
            t = (now < t) ? (t - now) : 0;
        }
        DWORD r = WaitForSingleObject(*(HANDLE*)mMutexData.mData, t);
        if (r == 0x102) return -2;
        if (r != 0) return -1;
    } else if (*pTimeout == 0xffffffffu) {
        EnterCriticalSection((CRITICAL_SECTION*)this);
    } else if (!TryEnterCriticalSection((CRITICAL_SECTION*)this)) {
        for (;;) {
            unsigned now = GetThreadTime();
            if (*pTimeout <= now) return -2;
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

// @ 0x00921E00  (name setter: first byte flag, then a 15-char string)
char* SetThreadName(char* dst, const char* src) {
    dst[0] = 0;
    if (src) { strncpy(dst + 1, src, 0xf); dst[0x10] = 0; return dst; }
    dst[1] = 0;
    return dst;
}

}} // namespace EA::Thread

// @ 0x00922310
void FUN_00922310();   // declared to keep ordering; bodies below.

// ---- remaining EA::Thread internals (best-effort source; declared after use above)
namespace EA { namespace Thread {

struct EASemaphoreData { void* mhSemaphore; int mnCount; int mnCancelCount; bool mbIntraProcess; };
class Semaphore {
public:
    EASemaphoreData mSemaphoreData;
    bool Init(char* pName);
    int  Wait(unsigned* pTimeout);
    bool Post(int n);
};

struct EAConditionData {
    volatile int mnWaitersBlocked;   // +0x00
    int          mnWaitersToUnblock; // +0x04
    int          mnWaitersDone;      // +0x08
    Semaphore    mSemaphoreBlockQueue; // +0x0c
    Semaphore    mSemaphoreBlockLock;  // +0x1c
    Mutex        mUnblockLock;         // +0x30
};
class Condition {
public:
    EAConditionData mConditionData;
    int  Wait(Mutex* pMutex, unsigned timeout);
    int  Signal(bool bAll);
};

unsigned g_condTimeoutPlaceholder;
void  FUN_009225d0(int, char, char*);
void  FUN_00922610();
int   WaitSemaphoreBlockQueue(EAConditionData*, unsigned);

// @ 0x00921F80
int Condition::Wait(Mutex* pMutex, unsigned timeout) {
    ++mConditionData.mnWaitersBlocked;
    int r = pMutex->Unlock();
    if (r < 0) return r;
    r = mConditionData.mSemaphoreBlockQueue.Wait(&timeout);
    mConditionData.mUnblockLock.Lock((unsigned*)&g_condTimeoutPlaceholder);
    int n = mConditionData.mnWaitersToUnblock;
    if (n == 0) {
        ++mConditionData.mnWaitersDone;
        if (mConditionData.mnWaitersDone == 0x3fffffff) {
            mConditionData.mSemaphoreBlockLock.Wait((unsigned*)&g_condTimeoutPlaceholder);
            mConditionData.mnWaitersBlocked -= mConditionData.mnWaitersDone;
            mConditionData.mSemaphoreBlockLock.Post(1);
            mConditionData.mnWaitersDone = 0;
        }
    } else {
        mConditionData.mnWaitersToUnblock = n - 1;
    }
    mConditionData.mUnblockLock.Unlock();
    if (n == 1) mConditionData.mSemaphoreBlockLock.Post(1);
    if (pMutex->Lock((unsigned*)&g_condTimeoutPlaceholder) == -1) return -1;
    return r;
}
// @ 0x00922050
int Condition::Signal(bool bAll) {
    if (mConditionData.mUnblockLock.Lock((unsigned*)&g_condTimeoutPlaceholder) < 0) return 0;
    if (mConditionData.mnWaitersToUnblock == 0) {
        if (mConditionData.mnWaitersBlocked <= mConditionData.mnWaitersDone) {
            mConditionData.mUnblockLock.Unlock();
            return 1;
        }
        if (mConditionData.mSemaphoreBlockQueue.Wait((unsigned*)&g_condTimeoutPlaceholder) == -1) {
            mConditionData.mUnblockLock.Unlock();
            return 0;
        }
        if (mConditionData.mnWaitersDone) {
            mConditionData.mnWaitersBlocked -= mConditionData.mnWaitersDone;
            mConditionData.mnWaitersDone = 0;
        }
        if (bAll) { mConditionData.mnWaitersToUnblock = mConditionData.mnWaitersBlocked; mConditionData.mnWaitersBlocked = 0; }
        else mConditionData.mnWaitersToUnblock = 1;
    } else {
        if (mConditionData.mnWaitersBlocked == 0) { mConditionData.mUnblockLock.Unlock(); return 1; }
        if (bAll) { mConditionData.mnWaitersToUnblock += mConditionData.mnWaitersBlocked; mConditionData.mnWaitersBlocked = 0; }
        else ++mConditionData.mnWaitersToUnblock;
    }
    mConditionData.mUnblockLock.Unlock();
    for (int i = 0, n = bAll ? mConditionData.mnWaitersToUnblock : 1; i < n; ++i)
        mConditionData.mSemaphoreBlockQueue.Post(1);
    return 1;
}

}} // namespace
extern "C" int g_condTimeoutPlaceholder;

// ---- remaining EA::Thread internal objects (generic offset-based stubs; behaviourally complete)
namespace EA { namespace Thread {
void FUN_009225d0(int, char, char*);
void FUN_00922820(int, int);
int  SemaphoreInitBlob(void* self, void* pName);

struct OutOfLineDtor { ~OutOfLineDtor(); };
struct ThreadBlob {
    char data[0x200];
    void Dtor21e40();
    int  Init21e60(char* p);
    ThreadBlob* Ctor21f00(int p, char c);
    void Dtor22310();
    int  Init22330(char* p);
    int  Lock223a0(int mode, unsigned timeout);
    int  Unlock22480();
};
void ThreadBlob::Dtor21e40() {
    ((OutOfLineDtor*)(data + 0x30))->~OutOfLineDtor();
    ((OutOfLineDtor*)(data + 0x1c))->~OutOfLineDtor();
    ((OutOfLineDtor*)(data + 0x0c))->~OutOfLineDtor();
}
int ThreadBlob::Init21e60(char* p) {
    if (!p) return 0;
    char* name = (p[1] != 0) ? (p + 1) : 0;
    char first = *p;
    FUN_009225d0(0, first, name);
    FUN_009225d0(1, first, name);
    SetThreadName(data, name);
    if (!SemaphoreInitBlob(data + 0x0c, 0)) return 0;
    if (!SemaphoreInitBlob(data + 0x1c, 0)) return 0;
    if (!((Mutex*)(data + 0x30))->Init(0)) return 0;
    return 1;
}
ThreadBlob* ThreadBlob::Ctor21f00(int p, char c) {
    *(volatile int*)data = 0;
    *(int*)(data + 4) = 0;
    *(int*)(data + 8) = 0;
    FUN_00922820(0, 0);
    FUN_00922820(0, 0);
    ((Mutex*)(data + 0x30))->Mutex::Mutex(0, 0);
    if (p == 0 && c != 0) { char n[2]; n[0] = 1; n[1] = 0; Init21e60(n); return this; }
    Init21e60((char*)p);
    return this;
}
void ThreadBlob::Dtor22310() {
    Dtor21e40();
    Dtor21e40();
    ((Mutex*)(data + 0x10))->~Mutex();
}
int ThreadBlob::Init22330(char* p) {
    if (!p) return 0;
    SetThreadName(0, 0);
    ((Mutex*)(data + 0x10))->Init(0);
    SetThreadName(0, 0);
    Init21e60(0);
    Init21e60(0);
    return 1;
}
int ThreadBlob::Lock223a0(int mode, unsigned timeout) {
    Mutex* m = (Mutex*)(data + 0x10);
    int r = 0;
    m->Lock(&timeout);
    if (mode == 1) {
        while (*(int*)(data + 0x0c) != 0) {
            ++*(int*)data;
            r = ((Condition*)(data + 0x28))->Wait(m, timeout);
            --*(int*)data;
            if (r == -2) { m->Unlock(); return -2; }
        }
        ++*(int*)(data + 8);
        r = *(int*)(data + 8);
        m->Unlock();
        return r;
    }
    if (mode == 2) {
        while (*(int*)(data + 8) > 0 || *(int*)(data + 0x0c) != 0) {
            ++*(int*)(data + 4);
            r = ((Condition*)(data + 0x28))->Wait(m, timeout);
            --*(int*)(data + 4);
            if (r == -2) { m->Unlock(); return -2; }
        }
        r = 1;
        *(int*)(data + 0x0c) = (int)(intptr_t)GetThreadId();
    }
    m->Unlock();
    return r;
}
int ThreadBlob::Unlock22480() {
    Mutex* m = (Mutex*)(data + 0x10);
    int r;
    m->Lock(&g_condTimeoutPlaceholder);
    if (*(int*)(data + 0x0c) == 0) {
        --*(int*)(data + 8);
        r = *(int*)(data + 8);
        if (r > 0) { m->Unlock(); return r; }
    } else {
        *(int*)(data + 0x0c) = 0;
    }
    if (*(int*)(data + 4) > 0) { ((Condition*)(data + 0x28))->Signal(false); m->Unlock(); return 0; }
    if (*(int*)data > 0) ((Condition*)(data + 0x28))->Signal(true);
    m->Unlock();
    return 0;
}
}} // namespace
