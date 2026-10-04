// slice s00576140 -- SP::cAppModeEditorBase (category switch, layer setup, Shutdown), editor cheats,
// and smart-pointer / EASTL / serialization helpers instantiated in the same TU.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (int->float and float copies still go through x87).
#include "types.h"
#include <intrin.h>

#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement)

void operator delete(void* p);                                              // 0x00f47380

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};

inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

namespace EA {
template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    AutoRefCount& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    AutoRefCount& operator=(const AutoRefCount& x);
};

// EA::RefCountTemplate: vptr, then the count; Release deletes through the virtual dtor.
struct RefCountTemplate {
    virtual ~RefCountTemplate();
    int mnRefCount;
    int Release()
    {
        int n = mnRefCount - 1;
        mnRefCount = n;
        if (n == 0) {
            mnRefCount = 1;
            delete this;
        }
        return n;
    }
};
}  // namespace EA

namespace eastl {
template <typename T> inline const T& min(const T& a, const T& b) { return (b < a) ? b : a; }

struct allocator {
    allocator(const char* = 0) {}
};
extern char gEmptyString[2];                                                // 0x01667bac

template <typename T, typename Allocator = allocator>
class basic_string {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    explicit basic_string(const Allocator& a);
    static int compare(const T* pBegin1, const T* pEnd1, const T* pBegin2, const T* pEnd2);
};

template <typename T> int Compare(const T* p1, const T* p2, size_t n);       // 0x00572930
}  // namespace eastl

// Generic COM-ish interface: AddRef in slot 1, Release in slot 2.
class IRefCounted {
public:
    virtual void Destroy();
    virtual int AddRef();
    virtual int Release();
};

// Interface whose Release lives in slot 1.
class IReleasable {
public:
    virtual void v00();
    virtual int Release();
};

// ---------------------------------------------------------------------------------------------
// Owner-freed reference object (count at +0x40, owner frees it through vtable slot 0x170).
class cObjectOwner;
struct cOwnedObject {
    cObjectOwner* mpOwner;      // +0x00
    uint32_t mFlags;            // +0x04 (bit 31: owner-allocated)
    char pad8[0x40 - 8];
    int mRefCount;              // +0x40
    inline void RemoveReference();
};
class cObjectOwner {
public:
#define PH(n) virtual void ph##n();
    PH(0) PH(1) PH(2) PH(3) PH(4) PH(5) PH(6) PH(7) PH(8) PH(9) PH(10) PH(11) PH(12) PH(13) PH(14)
    PH(15) PH(16) PH(17) PH(18) PH(19) PH(20) PH(21) PH(22) PH(23) PH(24) PH(25) PH(26) PH(27)
    PH(28) PH(29) PH(30) PH(31) PH(32) PH(33) PH(34) PH(35) PH(36) PH(37) PH(38) PH(39) PH(40)
    PH(41) PH(42) PH(43) PH(44) PH(45) PH(46) PH(47) PH(48) PH(49) PH(50) PH(51) PH(52) PH(53)
    PH(54) PH(55) PH(56) PH(57) PH(58) PH(59) PH(60) PH(61) PH(62) PH(63) PH(64) PH(65) PH(66)
    PH(67) PH(68) PH(69) PH(70) PH(71) PH(72) PH(73) PH(74) PH(75) PH(76) PH(77) PH(78) PH(79)
    PH(80) PH(81) PH(82) PH(83) PH(84) PH(85) PH(86) PH(87) PH(88) PH(89) PH(90) PH(91)
#undef PH
    virtual void FreeObject(cOwnedObject* obj, bool ownerAllocated);        // +0x170
};
inline void cOwnedObject::RemoveReference()
{
    if (mRefCount > 1)
        --mRefCount;
    else
        mpOwner->FreeObject(this, (mFlags >> 31) & 1);
}

struct cOwnedObjectPtr {
    cOwnedObject* mpObject;
    ~cOwnedObjectPtr();
    cOwnedObjectPtr& operator=(cOwnedObject* p)
    {
        if (mpObject) {
            cOwnedObject* old = mpObject;
            mpObject = p;
            old->RemoveReference();
        }
        return *this;
    }
};

// Atomically reference-counted object (count at +8).
namespace EA { namespace Thread {
struct AtomicInt {
    volatile long mValue;
    long GetValue() const { return _InterlockedExchangeAdd((long*)&mValue, 0); }
    long Increment() { return _InterlockedIncrement((long*)&mValue); }
    long Decrement() { return _InterlockedDecrement((long*)&mValue); }
};
} }

struct cAtomicRefObject {
    char pad0[8];
    EA::Thread::AtomicInt mRefCount;    // +0x08
    void AddRef() { mRefCount.Increment(); }
    void Release()
    {
        mRefCount.Decrement();
        if (mRefCount.GetValue() < 1)
            mRefCount.Increment();      // last reference: the object is pooled, not freed
        else
            mRefCount.GetValue();
    }
};

struct cAtomicRefPtr {
    cAtomicRefObject* mpObject;
    ~cAtomicRefPtr();
    cAtomicRefPtr& operator=(cAtomicRefObject* p);
};

// Object whose RefCountTemplate base sits at +4.
struct cRefBase0 { virtual void Base0Fn(); };
struct cRefCountedModel : cRefBase0, EA::RefCountTemplate {};

struct cRefCountedModelPtr {
    cRefCountedModel* mpObject;
    cRefCountedModelPtr& Reset();
    void operator=(int)
    {
        if (mpObject) {
            cRefCountedModel* p = mpObject;
            mpObject = 0;
            p->Release();
        }
    }
};

struct cRefCountedPtr {
    IRefCounted* mpObject;
    cRefCountedPtr& operator=(const cRefCountedPtr& x);
};

// ---------------------------------------------------------------------------------------------
namespace EA { namespace IO {
class IStream;
bool WriteUint32(IStream* s, const uint32_t* p, size_t n, int endian);     // 0x0093aa70
bool ReadInt32(IStream* s, int32_t* p, size_t n, int endian);              // 0x0093a780
bool WriteBool8(IStream* s, const bool* p, size_t n);                       // 0x0093a9a0
} }

class cStreamProvider {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual EA::IO::IStream* GetStream();                                   // +0x18
};
class cSerializer {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void EndBlock();                                                // +0x1c
    virtual cStreamProvider* GetProvider();                                 // +0x20
};

struct cEditorSnapshot {
    int mId;
    float mValues[5];
    bool mFlags[5];
    float mExtra[3];
    int mLast;

    cEditorSnapshot(const cEditorSnapshot& x) { Copy(x); }
    cEditorSnapshot& operator=(const cEditorSnapshot& x);
    __forceinline void Copy(const cEditorSnapshot& x)
    {
        mId = x.mId;
        mValues[0] = x.mValues[0]; mValues[1] = x.mValues[1]; mValues[2] = x.mValues[2];
        mValues[3] = x.mValues[3]; mValues[4] = x.mValues[4];
        mFlags[0] = x.mFlags[0]; mFlags[1] = x.mFlags[1]; mFlags[2] = x.mFlags[2];
        mFlags[3] = x.mFlags[3]; mFlags[4] = x.mFlags[4];
        mExtra[0] = x.mExtra[0]; mExtra[1] = x.mExtra[1]; mExtra[2] = x.mExtra[2];
        mLast = x.mLast;
    }
};
inline void* operator new(size_t, void* p) { return p; }

struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& x);                                              // 0x0041cb40
};
Matrix3& MakeRotation(Matrix3& out, const Vector3& axis, float angle);    // 0x00453b20

struct BoundingBox {
    Vector3 lower;
    Vector3 upper;
    BoundingBox();
};

// ---------------------------------------------------------------------------------------------
namespace SP {

class cGameView {
public:
    void SetFlags(int a, int b);                                             // 0x0067c420
    void AddLayer(ResourceKey key, void* handler, int a, float x, float y, float z, int b, int c);  // 0x0067aaf0
    void ClearLayers();                                                      // 0x0067a120
};
cGameView* GameViewA();                                                      // 0x0067cac0
cGameView* GameViewB();                                                      // 0x0067caf0

class cCheatManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void RemoveCheat(const char* name);                              // +0x1c
};
cCheatManager* CheatManager();                                               // 0x0067de20

class cMessageServer {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void RemoveListener(void* listener, uint32_t messageID, int priority);   // +0x2c
};
cMessageServer* MessageServer();                                             // 0x0067dcc0

class cModelManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void ReleaseModels(uint32_t groupID);                            // +0x18
};
cModelManager* ModelManager();                                               // 0x0067dd80

class cEffectsManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void ReleaseEffects(uint32_t groupID);                           // +0x50
};
cEffectsManager* EffectsManager();                                           // 0x0067ddd0

class cSaveRecord {
public:
    virtual void v00(); virtual void v04();
    virtual int Release();                                                   // +0x08
    virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual class cSaveStream* GetStream();                                  // +0x18
    virtual void v1c(); virtual void v20();
    virtual void Close();                                                    // +0x24
};
class cSaveStream {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual void Write(const void* data, uint32_t size);                     // +0x38
};
class cSaveArea {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30();
    virtual bool OpenRecord(const ResourceKey& key, EA::AutoRefCount<cSaveRecord>* record, int access, int disposition, int a, int b);   // +0x34
};
cSaveArea* GetSaveArea(const char* name);                                    // 0x006b1f90

class cSPEditorModel {
public:
    char pad0[0x58];
    int mModelType;                                                          // +0x58
    void ClearModel();                                                       // 0x004ad330
};
struct cSPEditorModelRef : cRefCountedModel {};

class cSPEditorPhysicsWorld : public EA::RefCountTemplate {
public:
    void Clear();                                                            // 0x004b9140
};

class cViewer {
public:
    ~cViewer();                                                              // 0x007c4000
    void Shutdown();                                                         // 0x007c3ba0
};

class cEditorLaunchData {
public:
    char pad0[0xc];
    int mEditorID;                                                           // +0x0c
    char pad10[0x6e - 0x10];
    bool mbShowBackground;                                                   // +0x6e
};

class cSPEditorBudget {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void AddDNA(int a, int amount);                                  // +0x20
};

class cIAppMode {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void Deactivate();                                               // +0x1c
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40();
    virtual uint32_t GetEditorID();                                          // +0x44
};

class cAppModeEditorBase : public cIAppMode {
public:
    char pad4[0x10 - 4];
    uint32_t mMessageListener;                                               // +0x10 (listener base)
    char pad14[0x1c - 0x14];
    uint32_t mLayerHandler;                                                  // +0x1c (layer base)
    void* mApp;                                                              // +0x20
    char pad24[0x84 - 0x24];
    IReleasable* mSaveModelWorld;                                            // +0x84
    IReleasable* mBackgroundModelWorld;                                      // +0x88
    IReleasable* mModelWorld;                                                // +0x8c
    cSPEditorPhysicsWorld* mPhysicsWorld;                                    // +0x90
    IReleasable* mEffectsWorld;                                              // +0x94
    cRefCountedModelPtr mEditorSaveModel;                                    // +0x98
    cSPEditorModelRef* mEditorModel;                                         // +0x9c
    cOwnedObjectPtr mPedestalModel;                                          // +0xa0
    char pada4[4];
    cOwnedObjectPtr mTestEnvironmentModel;                                   // +0xa8
    cOwnedObjectPtr mBackgroundModel;                                        // +0xac
    char padb0[0x15c - 0xb0];
    EA::AutoRefCount<IRefCounted> mTextureFactory;                           // +0x15c
    char pad160[0x1cc - 0x160];
    cEditorLaunchData* mLaunchData;                                          // +0x1cc
    char pad1d0[0x2b0 - 0x1d0];
    bool mbActive;                                                           // +0x2b0
    char pad2b1[0x31c - 0x2b1];
    int mEditorMode;                                                         // +0x31c
    char pad320[0x3cc - 0x320];
    cViewer* mViewers[5];                                                    // +0x3cc
    char pad3e0[0x434 - 0x3e0];
    cSPEditorBudget* mBudget;                                                // +0x434
    char pad438[0x448 - 0x438];
    uint32_t mSaveData[2];                                                   // +0x448
    char pad450[0x4f0 - 0x450];
    int mBackgroundEnabled[6];                                               // +0x4f0
    char pad508[0x59c - 0x508];
    uint32_t mHoverResult;                                                   // +0x59c
    float mHoverRadius;                                                      // +0x5a0
    char pad5a4[0x5c0 - 0x5a4];
    uint32_t mHandler[5];                                                    // +0x5c0 (AutoHandler)

    cSPEditorModel* SaveModel() { return (cSPEditorModel*)mEditorSaveModel.mpObject; }
    int GetEditorCategory();
    void UpdateBackgroundLayer();
    uint32_t PickHover(const Vector3& pos);
    bool Shutdown();
    void AddDNA();                                                           // 0x00575f70
};

extern Vector3 sHoverCenter;                                                 // 0x015e4f18
extern ResourceKey kBackgroundLayerA;                                        // 0x0150cfe8
extern ResourceKey kBackgroundLayerB;                                        // 0x0150d024
extern const char kEditorSaveArea[];                                         // 0x011ac19c
extern ResourceKey kEditorSaveKey;                                           // 0x0150cfa0
extern EA::AutoRefCount<IRefCounted> sEditorResource;                       // 0x015eebec

void ShutdownEditorSubsystem();                                              // 0x00563de0
void ShutdownEditorUI();                                                     // 0x005a98f0

}  // namespace SP

namespace EA { namespace ArgScript {
class cArguments { public: const char** MainArguments(size_t* numArgs, int minArgs, int maxArgs) const; };  // 0x00838020
typedef cArguments Line;
class ICommand {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual int AddRef();                                                    // +0x0c
    virtual int Release();                                                   // +0x10
};
} }

namespace EA { namespace Messaging {
void RemoveHandler(uint32_t h, uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // 0x00571db0
} }

namespace EA { namespace Audio {
class IAudioSystem {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void BeginMessage(uint32_t id);                                  // +0x38
    virtual void v3c();
    virtual void AddParam(uint32_t id, uint32_t value);                      // +0x40
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void SendMessage();                                              // +0x58
};
IAudioSystem* GetSystemAT();                                                 // 0x00a206f0
} }

using namespace SP;

// @ 0x00576140
int cAppModeEditorBase::GetEditorCategory()
{
    int result = 6;
    if (mLaunchData) {
        switch (mLaunchData->mEditorID) {
        case 0x1d2ec0a0: case 0x1d2ec0a4: case 0x1d2ec0a5: case 0x1d2ec0a6: case 0x1d2ec0a7:
        case 0x3615a30b:
            result = 0;
            break;
        case 0xb7af8ff8: case 0x281f5960: case 0x290adace: case 0x312e9d6a: case 0x465c50ba:
        case 0x5bf8f774:
            result = 1;
            break;
        case 0x8707be7d: case 0x99e92f05: case 0xbdd15f3d: case 0xd817cd63: case 0x4e3f7777:
        case 0x72c49181:
            result = 2;
            break;
        case 0x8f963dcb: case 0x96b24187: case 0x99f87089: case 0x9ad7d4aa: case 0xbc1041e6:
        case 0xc15695da: case 0xf670aa43: case 0x1a4e0708: case 0x1f2a25b6: case 0x2090a11b:
        case 0x2a5147a9: case 0x441cd3e6: case 0x449c040f: case 0x7d433fad:
            result = 3;
            break;
        case 0x9adf00a9: case 0xa56567f7: case 0x156276d1: case 0x247e2615: case 0x37e82da1:
            result = 4;
            break;
        case 0xe46c381e: case 0xfd4902bd:
            result = 5;
            break;
        }
    } else {
        switch (SaveModel()->mModelType) {
        case 0xdfad9f51:
            result = 0;
            break;
        case 0x9ea3031a:
            result = 1;
            break;
        case 0x99e92f05: case 0xbdd15f3d: case 0x47c10953: case 0x4e3f7777: case 0x72c49181:
            result = 2;
            break;
        case 0x8f963dcb: case 0x98e03c0d: case 0x9ad7d4aa: case 0xbc1041e6: case 0xc0b74287:
        case 0xc15695da: case 0xf670aa43: case 0x1a4e0708: case 0x1f2a25b6: case 0x2090a11b:
        case 0x2a5147a9: case 0x441cd3e6: case 0x449c040f: case 0x7d433fad:
            result = 3;
            break;
        case 0xccc35c46: case 0x372e2c04: case 0x4178b8e8: case 0x65672ade:
            result = 4;
            break;
        }
    }
    return result;
}

// @ 0x00576440
void cAppModeEditorBase::UpdateBackgroundLayer()
{
    if (GameViewB() && mLaunchData && mLaunchData->mbShowBackground) {
        int category = GetEditorCategory();
        if (category < 6 && mBackgroundEnabled[category] == 1) {
            GameViewB()->ClearLayers();
            switch (GetEditorCategory()) {
            case 0:
                GameViewB()->AddLayer(kBackgroundLayerA, &mLayerHandler, 0, -1.0f, -1.0f, 0.0f, 0, 0);
                break;
            case 1:
                GameViewB()->AddLayer(kBackgroundLayerB, &mLayerHandler, 0, -1.0f, -1.0f, 0.0f, 0, 0);
                break;
            default:
                return;
            }
            GameViewA()->SetFlags(0, 1);
        }
    }
}

// @ 0x00576550
uint32_t cAppModeEditorBase::PickHover(const Vector3& pos)
{
    if (GetEditorID() == 0x465c50ba && mEditorMode == 2)
        return 0;
    Vector3 d = pos - sHoverCenter;
    if (d.y * d.y + d.z * d.z + d.x * d.x < mHoverRadius * mHoverRadius)
        return mHoverResult;
    return 0;
}

// @ 0x005765e0
cOwnedObjectPtr::~cOwnedObjectPtr()
{
    if (mpObject)
        mpObject->RemoveReference();
}

// @ 0x00576620
cAtomicRefPtr::~cAtomicRefPtr()
{
    if (mpObject)
        mpObject->Release();
}

// @ 0x00576650
cAtomicRefPtr& cAtomicRefPtr::operator=(cAtomicRefObject* p)
{
    cAtomicRefObject* old = mpObject;
    if (p != old) {
        if (p)
            p->AddRef();
        mpObject = p;
        if (old)
            old->Release();
    }
    return *this;
}

// @ 0x005766b0
cRefCountedModelPtr& cRefCountedModelPtr::Reset()
{
    if (mpObject) {
        cRefCountedModel* p = mpObject;
        mpObject = 0;
        p->Release();
    }
    return *this;
}

// @ 0x005766e0
cRefCountedPtr& cRefCountedPtr::operator=(const cRefCountedPtr& x)
{
    IRefCounted* p = x.mpObject;
    IRefCounted* old = mpObject;
    if (p != old) {
        if (p)
            p->AddRef();
        mpObject = p;
        if (old)
            old->Release();
    }
    return *this;
}

// @ 0x00576750
template <>
eastl::basic_string<char>::basic_string(const eastl::allocator&)
    : mpBegin(gEmptyString), mpEnd(gEmptyString), mpCapacity(gEmptyString + 1)
{
}

// @ 0x00576770
template <>
eastl::basic_string<wchar_t>::basic_string(const eastl::allocator&)
    : mpBegin((wchar_t*)gEmptyString), mpEnd((wchar_t*)gEmptyString), mpCapacity((wchar_t*)gEmptyString + 1)
{
}

struct BoolVector { uint8_t* mpBegin; uint8_t* mpEnd; };

// @ 0x005767f0
void WriteBoolVector(cSerializer* s, const BoolVector& v)
{
    uint32_t count = (uint32_t)(v.mpEnd - v.mpBegin);
    EA::IO::WriteUint32(s->GetProvider()->GetStream(), &count, 1, 0);
    for (const uint8_t* it = v.mpBegin; it != v.mpEnd; ++it) {
        bool b = *it != 0;
        EA::IO::WriteBool8(s->GetProvider()->GetStream(), &b, 1);
    }
    s->EndBlock();
}

// @ 0x00576880
bool ReadIntArray6(cSerializer* s, int32_t* values)
{
    int32_t count;
    EA::IO::ReadInt32(s->GetProvider()->GetStream(), &count, 1, 0);
    int n = eastl::min(count, 6);
    for (int i = 0; i < n; i++)
        EA::IO::ReadInt32(s->GetProvider()->GetStream(), &values[i], 1, 0);
    return true;
}

// @ 0x00576900
cEditorSnapshot& cEditorSnapshot::operator=(const cEditorSnapshot& x)
{
    Copy(x);
    return *this;
}

// @ 0x00576970
template <>
int eastl::basic_string<wchar_t>::compare(const wchar_t* pBegin1, const wchar_t* pEnd1, const wchar_t* pBegin2, const wchar_t* pEnd2)
{
    const int n1 = (int)(pEnd1 - pBegin1);
    const int n2 = (int)(pEnd2 - pBegin2);
    const int cmp = Compare(pBegin1, pBegin2, (size_t)eastl::min(n1, n2));
    return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
}

// @ 0x005769d0
void uninitialized_fill_n_ref(EA::AutoRefCount<IRefCounted>* dest, size_t n, const EA::AutoRefCount<IRefCounted>& value)
{
    EA::AutoRefCount<IRefCounted>* cur = dest;
    for (; n > 0; --n, ++cur)
        ::new(cur) EA::AutoRefCount<IRefCounted>(value);
}

// @ 0x00576a10
cEditorSnapshot* uninitialized_copy_snapshot(const cEditorSnapshot* first, const cEditorSnapshot* last, cEditorSnapshot* dest)
{
    for (; first != last; ++first, ++dest)
        ::new(dest) cEditorSnapshot(*first);
    return dest;
}

// @ 0x00576ab0
Vector3* ColorToVector3(Vector3* out, uint32_t color)
{
    out->x = (float)((color >> 16) & 0xff) * (1.0f / 255.0f);
    out->y = (float)((color >> 8) & 0xff) * (1.0f / 255.0f);
    out->z = (float)(color & 0xff) * (1.0f / 255.0f);
    return out;
}

// @ 0x00576b00
Matrix3 RotationMatrix(const Vector3& axis, float angle)
{
    Matrix3 m;
    return MakeRotation(m, axis, angle);
}

// @ 0x00576b40
BoundingBox::BoundingBox()
{
    lower = Vector3(3.402823466e+38f, 3.402823466e+38f, 3.402823466e+38f);
    upper = Vector3(-3.402823466e+38f, -3.402823466e+38f, -3.402823466e+38f);
}

namespace {
class cEditorCheatBase : public EA::ArgScript::ICommand {
public:
    char pad4[0x10 - 4];
    cAppModeEditorBase* mpEditor;                                            // +0x10
};
class cEditorBudgetCheat : public cEditorCheatBase {
public:
    void ParseLine(const EA::ArgScript::Line& line);
};
class cEditorAddDNACheat : public cEditorCheatBase {
public:
    void Execute(const EA::ArgScript::Line& line);
};
}

// @ 0x00576bb0
void cEditorBudgetCheat::ParseLine(const EA::ArgScript::Line& line)
{
    if (this)
        AddRef();
    size_t numArgs;
    line.MainArguments(&numArgs, 0, 0x7fffffff);
    cAppModeEditorBase* editor = mpEditor;
    if (editor->mbActive)
        editor->mBudget->AddDNA(0, 150);
    Release();
}

// @ 0x00576c10
void cEditorAddDNACheat::Execute(const EA::ArgScript::Line& line)
{
    if (this)
        AddRef();
    size_t numArgs;
    line.MainArguments(&numArgs, 0, 0x7fffffff);
    mpEditor->AddDNA();
    Release();
}

static inline void DeleteViewer(cViewer*& viewer)
{
    if (viewer) {
        viewer->Shutdown();
        delete viewer;
        viewer = 0;
    }
}

// @ 0x00576c50
bool cAppModeEditorBase::Shutdown()
{
    if (mbActive)
        Deactivate();
    CheatManager()->RemoveCheat("addDNA");
    CheatManager()->RemoveCheat("toggleeditorbackground");
    CheatManager()->RemoveCheat("colladaexport");
    mApp = 0;

    cMessageServer* server = MessageServer();
    if (server) {
        if (mHandler[0]) {
            uint32_t h = mHandler[0];
            mHandler[0] = 0;
            EA::Messaging::RemoveHandler(h, mHandler[1], mHandler[2], mHandler[3], mHandler[4]);
        }
        server->RemoveListener(&mMessageListener, 0x29d57f4, -9999);
        server->RemoveListener(&mMessageListener, 0x3fc3f13, -9999);
        server->RemoveListener(&mMessageListener, 0x62628f0, -9999);
    }
    ShutdownEditorSubsystem();
    ShutdownEditorSubsystem();

    if (mEditorSaveModel.mpObject) {
        SaveModel()->ClearModel();
        mEditorSaveModel = 0;
    }
    if (mEditorModel) {
        ((cSPEditorModel*)mEditorModel)->ClearModel();
        mEditorSaveModel = 0;
    }
    mPedestalModel = 0;
    mTestEnvironmentModel = 0;
    mBackgroundModel = 0;

    if (mSaveModelWorld) {
        IReleasable* p = mSaveModelWorld;
        mSaveModelWorld = 0;
        p->Release();
    }
    if (mModelWorld) {
        IReleasable* p = mModelWorld;
        mModelWorld = 0;
        p->Release();
    }
    if (mBackgroundModelWorld) {
        IReleasable* p = mBackgroundModelWorld;
        mBackgroundModelWorld = 0;
        p->Release();
    }
    ModelManager()->ReleaseModels(0xe4c6e4);
    ModelManager()->ReleaseModels(0x21b37d6);
    ModelManager()->ReleaseModels(0x5557b15);
    if (mEffectsWorld) {
        IReleasable* p = mEffectsWorld;
        mEffectsWorld = 0;
        p->Release();
    }
    EffectsManager()->ReleaseEffects(0xe4c6e4);
    if (mTextureFactory)
        mTextureFactory = 0;
    if (mPhysicsWorld) {
        mPhysicsWorld->Clear();
        if (mPhysicsWorld) {
            cSPEditorPhysicsWorld* p = mPhysicsWorld;
            mPhysicsWorld = 0;
            p->Release();
        }
    }
    DeleteViewer(mViewers[1]);
    DeleteViewer(mViewers[2]);
    DeleteViewer(mViewers[0]);
    DeleteViewer(mViewers[3]);
    DeleteViewer(mViewers[4]);

    EA::Audio::IAudioSystem* audio = EA::Audio::GetSystemAT();
    if (audio) {
        audio->BeginMessage(0x347536b);
        audio->AddParam(0x3475385, 0xb07c3bbf);
        audio->AddParam(0x34753a0, 1);
        audio->SendMessage();
    }

    cSaveArea* area = GetSaveArea(kEditorSaveArea);
    if (area) {
        EA::AutoRefCount<cSaveRecord> record;
        if (area->OpenRecord(kEditorSaveKey, &record, 2, 2, 1, 0)) {
            record->GetStream()->Write(mSaveData, 8);
            record->Close();
        }
        if (record.mpObject)
            record.mpObject->Release();
    }
    ShutdownEditorUI();
    sEditorResource = 0;
    return true;
}
