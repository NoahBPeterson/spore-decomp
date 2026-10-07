// Slice s00611860: SP::cPollinator::HandleMessage (0x00611860, 2563 bytes).
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE (no /EHsc).
//
// Message handler of the Pollinator (Spore's online asset sharing client). Each message id
// either posts a new Pollen transaction to the transaction queue (class-specific operator new
// from a fixed allocator + ctor), updates the "my sporecasts" / "my subscriptions" feed lists,
// handles login / shutdown state, or records a pollinate request for a resource key. Every
// handled id then flushes (if a shutdown was requested) and processes the transaction queue;
// unknown ids return straight away. All paths return true.
//
// Member offsets are retail (they differ from the 2008 dev PDB). Transaction classes without a
// recovered name are named after the constructor address.
#include "types.h"

typedef unsigned int size_t;

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

extern "C" __declspec(dllimport) unsigned long __cdecl strtoul(const char* s, char** end, int base);

// ---- EASTL / EA bits ----------------------------------------------------------------------
namespace eastl {
struct allocator {
    allocator() {}
    void deallocate(void* p, size_t) { operator delete[](p); }
};
struct string {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator mAllocator;

    struct CtorSprintf {};
    string(const char* p, const allocator& a = allocator());   // 0x0057ed80
    string(const string& x);                                     // 0x0057cb10
    string(CtorSprintf, const char* pFormat, ...);               // 0x00472f50
    ~string() { DeallocateSelf(); }                              // 0x00530670 when not inlined
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (size_t)(mpCapacity - mpBegin));
    }
    void DoFree(char* p, size_t n)
    {
        if (p)
            mAllocator.deallocate(p, n);
    }
    const char* c_str() const { return mpBegin; }
    bool empty() const { return mpBegin == mpEnd; }
};
bool operator==(const string& a, const string& b);              // 0x00554fb0
} // namespace eastl

namespace EA {
struct Variant {
    void* mValue;                                                // +0x00 (inline storage / pointer)
    uint32_t mStorage[3];
    uint16_t mFlags;                                             // +0x10
    uint16_t mTypeId;                                            // +0x12
    Variant& operator=(const Variant& x);                        // 0x00542b80
    void Destruct(int);                                          // 0x0093db80
};
template <typename T> struct VariantT : Variant {
    VariantT(const Variant& x);                                  // 0x0060d990 (int), 0x0060d9c0 (string)
    ~VariantT() { if (mFlags & 4) Destruct(0); }
    T* Get();                                                    // 0x0060d280 (int), 0x0060ebf0 (string)
};
namespace Thread {
struct ThreadTime {
    int mMS;
    ThreadTime(int ms) : mMS(ms) {}
};
void ThreadSleep(const ThreadTime& t);                           // 0x00921df0
} // namespace Thread
} // namespace EA

struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
};

// int variant read inline: Get() of a VariantT<int> whose tag says int (9) or reference (0x10)
extern int g_DefaultVariantInt;                                  // 0x015d1160
struct cIntVariant : EA::Variant {
    cIntVariant() { mFlags = 2; mTypeId = 9; }
    cIntVariant& operator=(const EA::Variant& x) { EA::Variant::operator=(x); return *this; }
    ~cIntVariant() { if (mFlags & 4) Destruct(0); }
    int* GetPtr()
    {
        if (mTypeId == 9 || mTypeId == 0x10) {
            if (mFlags & 0x30)
                return (int*)mValue;
            return mTypeId ? (int*)this : 0;
        }
        return &g_DefaultVariantInt;
    }
};

// ---- message payloads --------------------------------------------------------------------
struct IResponseCallback {
    PV8 PV2 PV
    virtual void Complete(int result);                           // +0x2c
};
struct IRequest {
    PV4 PV2 PV
    virtual EA::Variant& GetValue(int index);                    // +0x1c
};
struct IRequestMessage {
    PV4
    virtual IRequest* GetRequest();                              // +0x10
    virtual IResponseCallback* GetCallback();                    // +0x14
};

namespace SP {
struct ISporepediaQuery;
namespace Feed {
struct FeedDescription {
    uint32_t pad00[0x54 / 4];
    eastl::string mFeedID;                                       // +0x54
    uint32_t pad64[3];
    FeedDescription& operator=(const FeedDescription& x);       // 0x005496a0
};                                                               // size 0x70
}

struct FeedDescriptionVector {
    Feed::FeedDescription* mpBegin;
    Feed::FeedDescription* mpEnd;
    Feed::FeedDescription* mpCapacity;
    uint32_t mAllocator[2];
    void push_back(const Feed::FeedDescription& x);              // 0x00611830
    Feed::FeedDescription* erase(Feed::FeedDescription* it);     // 0x00611550
};

struct UIntPair { uint32_t first, second; };
struct UIntVectorMap {
    UIntPair* mpBegin;
    UIntPair* mpEnd;
    uint32_t pad[3];
    UIntPair* find(const uint32_t& key);                         // 0x00ea9bb0
    UIntPair* end() const { return mpEnd; }
};

struct KeySetInsertResult { void* node; bool second; };
struct KeySet {
    KeySetInsertResult insert(const ResourceKey& key);           // 0x0060ebc0
};

struct cUploadRequest {
    ResourceKey mKey;
    bool mbA, mbB;
    cUploadRequest(const ResourceKey& key, bool a, bool b);      // 0x0060ccc0
};
struct UploadQueue {
    void push_back(const cUploadRequest& r);                     // 0x0060f080
};

namespace Pollen {
struct cITransaction {};
struct cTransactionQueue {
    bool Add(cITransaction* p, bool front);                      // 0x0060eaf0
    void Clear();                                                // 0x00610e90
};
struct cAssetDirectory {
    void Touch(uint64_t assetID, int flags);                     // 0x0054ed50
};

struct cAssetStatusTransaction : cITransaction {                                 // 0xf0 bytes
    uint32_t mData[0xf0 / 4];
    static void* operator new(size_t n);                         // 0x006158b0
    cAssetStatusTransaction(int type, uint32_t a, uint32_t b, int c);    // 0x00618d40
    cAssetStatusTransaction(int type, const char* id, int c);            // 0x00618da0
};
struct cSnapshotUploadTransaction : cITransaction {                              // 0x54 bytes
    uint32_t mData[0x54 / 4];
    static void* operator new(size_t n);                         // 0x00615a90
    cSnapshotUploadTransaction(const ResourceKey& key, const char* a, const char* b, const char* c, const char* d);  // 0x00619250
};
struct cYouTubeAuthenticationTransaction : cITransaction {                       // 0x3c bytes
    uint32_t mData[0x3c / 4];
    static void* operator new(size_t n);                         // 0x00615af0
    cYouTubeAuthenticationTransaction(const char* a, const char* b, const char* c, bool d);  // 0x00619300
};
struct cYouTubeVideoUploadTransaction : cITransaction {                          // 0x74 bytes
    uint32_t mData[0x74 / 4];
    static void* operator new(size_t n);                         // 0x00615b20
    cYouTubeVideoUploadTransaction(const char* a, const char* b, const char* c, const char* d,
                                   const char* e, ResourceKey key, uint32_t f);  // 0x00619390
};
struct cYouTubeVideoURLTransaction : cITransaction {                             // 0x48 bytes
    uint32_t mData[0x48 / 4];
    static void* operator new(size_t n);                         // 0x00615b50
    cYouTubeVideoURLTransaction(const char* a, const char* b, const char* c, const char* d);  // 0x00619470
};
struct cTransaction6166e0 : cITransaction {                                      // 0x10 bytes
    uint32_t mData[0x10 / 4];
    static void* operator new(size_t n);                         // 0x00615b80
    cTransaction6166e0(uint32_t a, uint32_t b);                  // 0x006166e0
};
struct cTransaction616660 : cITransaction {                                      // 0x18 bytes
    uint32_t mData[0x18 / 4];
    static void* operator new(size_t n);                         // 0x00615ac0
    cTransaction616660(ISporepediaQuery* q, uint64_t userID);  // 0x00616660
};
} // namespace Pollen

struct ISporepediaQuery {
    PV4 PV2 PV
    virtual uint32_t GetCount();                                 // +0x1c
    PV2
    virtual void Reset(int a, int b);                            // +0x28
};
struct cOnlineState {
    uint32_t pad00[0x30 / 4];
    uint64_t mUserID;                                            // +0x30
    ISporepediaQuery* mpQuery;                                   // +0x3c
};
cOnlineState* OnlineState();                                     // 0x0067de90

struct cHTTPClient { void SetTimeout(int a, int ms); };          // 0x00943a30
struct cFeedManager {
    void Init();                                                 // 0x0061faf0
    bool IsBusy();                                               // 0x0061e180
};
cFeedManager* FeedManager();                                     // 0x0061df20

struct IMessageServer {
    PV4 PV
    virtual void PostMSG(uint32_t id, void* a, void* b);         // +0x14
    PV8
    virtual void Update();                                       // +0x38
};
IMessageServer* MessageServer();                                 // 0x0067dcc0

struct cAppPropertiesData { uint32_t pad[0x118 / 4]; int mbOffline; };  // +0x118
struct cAppProperties { uint32_t pad[0x3c / 4]; cAppPropertiesData* mpData; };  // +0x3c
extern cAppProperties* sAppProperties;                           // 0x015fd918

struct cPollinator {
    void* mpHandlerVtbl;                                         // +0x00 (IHandler)
    cHTTPClient* mpHTTPClient;                                   // +0x04
    Pollen::cTransactionQueue mTransactionQueue;                 // +0x08
    uint32_t pad0c[(0x58 - 0x0c) / 4];
    Pollen::cAssetDirectory* mpAssetDirectory;                   // +0x58
    uint32_t pad5c;
    uint64_t mnNextAssetID;                                      // +0x60
    UploadQueue mUploadQueue;                                    // +0x68
    uint32_t pad6c[(0x7c - 0x6c) / 4];
    KeySet mPollinateRequests;                                   // +0x7c
    uint32_t pad80[(0x98 - 0x80) / 4];
    UIntVectorMap mFeedStatus;                                   // +0x98
    uint32_t padac[(0xb0 - 0xac) / 4];
    bool mbShutdownInProgress;                                   // +0xb0
    uint8_t padb1[3];
    FeedDescriptionVector mMySporecasts;                         // +0xb4
    FeedDescriptionVector mMySubscriptions;                      // +0xc8
    uint32_t paddc[(0xf0 - 0xdc) / 4];
    bool mbFlushQueue;                                           // +0xf0
    bool mbPollinationEnabled;                                   // +0xf1
    uint8_t padf2[2];
    UIntVectorMap mAssetStatus;                                  // +0xf4

    void SetEnabledState(uint32_t state);                        // 0x0060cec0
    void HandleTransactionResult(void* pResult);                 // 0x006111c0
    void CancelTransactions(uint32_t id);                        // 0x00611170
    void HandlePollinateRequest(const ResourceKey& key, bool a, bool b);  // 0x0060ee90
    void ProcessTransactionQueue();                              // 0x00610140
    bool HandleMessage(uint32_t messageID, void* pMessage);
};

struct cAssetIDMessage { uint32_t mLow, mHigh; };
struct cSnapshotUploadMessage {
    ResourceKey mKey;
    eastl::string mA, mB, mC, mD;                                // +0x0c, +0x1c, +0x2c, +0x3c
};
struct cYouTubeAuthMessage {
    eastl::string mA, mB, mC;                                    // +0x00, +0x10, +0x20
    bool mD;                                                     // +0x30
};
struct cYouTubeUploadMessage {
    eastl::string mA, mB, mC, mD, mE;                            // +0x00 .. +0x40
    ResourceKey mKey;                                            // +0x50
    uint32_t mF;                                                 // +0x5c
};
struct cYouTubeURLMessage {
    eastl::string mA, mB, mC, mD;                                // +0x00 .. +0x30
};
struct cPairMessage { uint32_t pad[3]; uint32_t mA, mB; };       // +0x0c, +0x10

// @ 0x00611860
bool cPollinator::HandleMessage(uint32_t messageID, void* pMessage)
{
    switch (messageID) {
    case 0x192dc39:
        if (mbPollinationEnabled) {
            uint64_t assetID = *(uint64_t*)pMessage;
            mpAssetDirectory->Touch(assetID, 0);
            mTransactionQueue.Add(new Pollen::cAssetStatusTransaction(3, eastl::string(eastl::string::CtorSprintf(), "%I64u", assetID).c_str(), 0), false);
        }
        break;
    case 0x19168dd:
        if (mbPollinationEnabled) {
            cAssetIDMessage* pID = (cAssetIDMessage*)pMessage;
            mTransactionQueue.Add(new Pollen::cAssetStatusTransaction(0, pID->mLow, pID->mHigh, 0), false);
        }
        break;
    case 0x164d214:
        HandleTransactionResult(pMessage);
        break;
    case 0x238de9c: {
        mbFlushQueue = true;
        mTransactionQueue.Clear();
        mpHTTPClient->SetTimeout(1, 10000);
        cFeedManager* pFeedManager = FeedManager();
        if (pFeedManager) {
            uint32_t i = 0;
            pFeedManager->Init();
            while (pFeedManager->IsBusy() && i++ < 40) {
                ProcessTransactionQueue();
                MessageServer()->Update();
                EA::Thread::ThreadSleep(EA::Thread::ThreadTime(250));
            }
        }
        break;
    }
    case 0x23a1f6c: {
        IRequestMessage* pRequest = (IRequestMessage*)pMessage;
        IResponseCallback* pCallback = pRequest->GetCallback();
        int value = *EA::VariantT<int>(pRequest->GetRequest()->GetValue(0)).Get();
        if (value) {
            SetEnabledState(0x4c4d2c3);
            pCallback->Complete(0);
        } else {
            mbPollinationEnabled = false;
            mbShutdownInProgress = false;
            pCallback->Complete(0);
        }
        break;
    }
    case 0x23a1f6d: {
        IRequestMessage* pRequest = (IRequestMessage*)pMessage;
        IResponseCallback* pCallback = pRequest->GetCallback();
        eastl::string feedID(*EA::VariantT<eastl::string>(pRequest->GetRequest()->GetValue(0)).Get());
        uint32_t id = strtoul(feedID.c_str(), 0, 0);
        UIntPair* it = mFeedStatus.find(id);
        if (it != mFeedStatus.end() && it->second != 0)
            pCallback->Complete(0);
        else
            pCallback->Complete(2);
        break;
    }
    case 0x30547f1:
        break;
    case 0x3cdd5f9:
        if (pMessage)
            mMySporecasts.push_back(*(Feed::FeedDescription*)pMessage);
        break;
    case 0x3cf0359: {
        eastl::string feedID((const char*)pMessage);
        if (!feedID.empty()) {
            Feed::FeedDescription* it = mMySporecasts.mpBegin;
            Feed::FeedDescription* end = mMySporecasts.mpEnd;
            for (; it != end; ++it) {
                if (it->mFeedID == feedID)
                    break;
            }
            if (it != end)
                mMySporecasts.erase(it);
        }
        break;
    }
    case 0x3d1cd0b:
        if (pMessage)
            mMySubscriptions.push_back(*(Feed::FeedDescription*)pMessage);
        break;
    case 0x3ffd8c9:
        if (pMessage) {
            eastl::string feedID((const char*)pMessage);
            if (!feedID.empty()) {
                Feed::FeedDescription* it = mMySubscriptions.mpBegin;
                Feed::FeedDescription* end = mMySubscriptions.mpEnd;
                for (; it != end; ++it) {
                    if (it->mFeedID == feedID)
                        break;
                }
                if (it != end)
                    mMySubscriptions.erase(it);
            }
        }
        break;
    case 0x457076f: {
        cSnapshotUploadMessage* pMsg = (cSnapshotUploadMessage*)pMessage;
        mTransactionQueue.Add(new Pollen::cSnapshotUploadTransaction(pMsg->mKey, pMsg->mA.c_str(), pMsg->mB.c_str(), pMsg->mC.c_str(), pMsg->mD.c_str()), false);
        break;
    }
    case 0x45883b0:
        if (mbPollinationEnabled && !sAppProperties->mpData->mbOffline) {
            uint32_t assetID = *(uint32_t*)pMessage;
            uint32_t status = 5;
            UIntPair* it = mAssetStatus.find(assetID);
            if (it != mAssetStatus.end())
                status = it->second;
            mTransactionQueue.Add(new Pollen::cAssetStatusTransaction(0, assetID, status, 0), false);
        }
        break;
    case 0x46d05ee:
        if (mbPollinationEnabled) {
            ISporepediaQuery* pQuery = OnlineState()->mpQuery;
            if (pQuery && pQuery->GetCount() > 0) {
                pQuery->Reset(0, 0);
                mTransactionQueue.Add(new Pollen::cTransaction616660(pQuery, OnlineState()->mUserID), false);
            }
        }
        break;
    case 0x49a3777:
        if (pMessage) {
            Feed::FeedDescription* pFeed = (Feed::FeedDescription*)pMessage;
            Feed::FeedDescription* it = mMySporecasts.mpBegin;
            Feed::FeedDescription* end = mMySporecasts.mpEnd;
            for (; it != end; ++it) {
                if (it->mFeedID == pFeed->mFeedID)
                    break;
            }
            if (it != end)
                *it = *pFeed;
        }
        break;
    case 0x55be439: {
        cYouTubeAuthMessage* pMsg = (cYouTubeAuthMessage*)pMessage;
        mTransactionQueue.Add(new Pollen::cYouTubeAuthenticationTransaction(pMsg->mA.c_str(), pMsg->mB.c_str(), pMsg->mC.c_str(), pMsg->mD), false);
        break;
    }
    case 0x55e8bc8: {
        cYouTubeUploadMessage* pMsg = (cYouTubeUploadMessage*)pMessage;
        mTransactionQueue.Add(new Pollen::cYouTubeVideoUploadTransaction(pMsg->mA.c_str(), pMsg->mB.c_str(), pMsg->mC.c_str(), pMsg->mD.c_str(), pMsg->mE.c_str(), pMsg->mKey, pMsg->mF), false);
        break;
    }
    case 0x56cd8c4: {
        cYouTubeURLMessage* pMsg = (cYouTubeURLMessage*)pMessage;
        mTransactionQueue.Add(new Pollen::cYouTubeVideoURLTransaction(pMsg->mA.c_str(), pMsg->mB.c_str(), pMsg->mC.c_str(), pMsg->mD.c_str()), false);
        break;
    }
    case 0x56d09b3: {
        IRequestMessage* pRequest = (IRequestMessage*)pMessage;
        IResponseCallback* pCallback = pRequest->GetCallback();
        cIntVariant v;
        v = pRequest->GetRequest()->GetValue(0);
        int value = *v.GetPtr();
        mbShutdownInProgress = value != 0;
        pCallback->Complete(0);
        break;
    }
    case 0x5d313c7:
        CancelTransactions(*(uint32_t*)pMessage);
        break;
    case 0x5fff3ff:
        if (mbPollinationEnabled && pMessage) {
            cPairMessage* pMsg = (cPairMessage*)pMessage;
            if (mTransactionQueue.Add(new Pollen::cTransaction6166e0(pMsg->mA, pMsg->mB), false))
                break;
        }
        MessageServer()->PostMSG(0x60ba744, 0, 0);
        break;
    case 0x632d709: {
        UIntPair* it = mAssetStatus.mpBegin;
        UIntPair* end = mAssetStatus.mpEnd;
        for (; it != end; ++it)
            mTransactionQueue.Add(new Pollen::cAssetStatusTransaction(0, it->first, it->second, 0), false);
        break;
    }
    case 0x2ba2010:
    case 0x73e46f6:
    case 0x611a3f72:
        if (mbPollinationEnabled && !mbShutdownInProgress) {
            bool bA = messageID == 0x73e46f6;
            bool bB = messageID == 0x611a3f72;
            ResourceKey key = *(ResourceKey*)pMessage;
            if (mPollinateRequests.insert(key).second) {
                if (mnNextAssetID == 0xffffffffffffffffULL)
                    mUploadQueue.push_back(cUploadRequest(key, bA, bB));
                else
                    HandlePollinateRequest(key, bA, bB);
            }
        }
        break;
    default:
        return true;
    }

    if (mbFlushQueue)
        mTransactionQueue.Clear();
    ProcessTransactionQueue();
    return true;
}
} // namespace SP
