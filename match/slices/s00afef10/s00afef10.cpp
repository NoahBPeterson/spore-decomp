// Slice s00afef10: Simulator::cFruit initialization/cast/serialization helpers,
// SP::cTreeData::GetFruitHeight, surface-decal emission helpers and the
// generic serializer field writers used by the fruit definition table.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

#define VSLOT(n) virtual void _v##n();

// ---------------------------------------------------------------------------
// shared math value types
// ---------------------------------------------------------------------------
class cVector2 {
public:
    float x;    // +0x00
    float y;    // +0x04
    cVector2() {}
    cVector2(float fValue) : x(fValue), y(fValue) {}
};

class cVector3 {
public:
    float x;    // +0x00
    float y;    // +0x04
    float z;    // +0x08
    cVector3() {}
    cVector3(float fValue) : x(fValue), y(fValue), z(fValue) {}
};

class cVector4 {
public:
    float x;    // +0x00
    float y;    // +0x04
    float z;    // +0x08
    float w;    // +0x0c
};

// all-zero vector kept as integer words so that its static initialization is
// emitted as plain dword stores
class cZeroVector3 {
public:
    uint32_t x;     // +0x00
    uint32_t y;     // +0x04
    uint32_t z;     // +0x08
    cZeroVector3() : x(0), y(0), z(0) {}
};

// ---------------------------------------------------------------------------
// EA virtual interfaces used by the serializer helpers
// ---------------------------------------------------------------------------
class IStream {
public:
    uint8_t mnPad00[0x04];  // +0x00
};

class IAVIStream {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5)
    virtual IStream* GetStream();   // +0x18
};

class cOutStream {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    virtual IAVIStream* GetIO();    // +0x20
};

namespace EA {
namespace IO {
bool WriteUint32(IStream* pStream, const uint32_t* pValue, int32_t nCount,
                 int32_t nFlags); // 0x0093aa70
bool WriteUint64(IStream* pStream, const uint64_t* pValue, int32_t nCount,
                 int32_t nFlags); // 0x0093ab10
} // namespace IO
} // namespace EA

// ---------------------------------------------------------------------------
// reference counted object base
// ---------------------------------------------------------------------------
class cRefObject {
public:
    virtual void AddRef();      // +0x00
    virtual void Release();     // +0x04
};

template <class T>
class AutoRefCount {
public:
    T* mpObject;                // +0x00
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount()
    {
        if (mpObject != 0)
            mpObject->Release();
    }
    AutoRefCount& operator=(T* pObject)
    {
        if (mpObject != pObject) {
            if (pObject != 0)
                pObject->AddRef();
            T* pOld = mpObject;
            mpObject = pObject;
            if (pOld != 0)
                pOld->Release();
        }
        return *this;
    }
};

// ---------------------------------------------------------------------------
// host object whose +0x20 slot builds a serialized value in place
// ---------------------------------------------------------------------------
typedef void* (__cdecl* tGetValueFn)(void* pSelf);

class cValueHost {
public:
    uint8_t mnPad00[0x20];      // +0x00
    tGetValueFn mpfnGet;        // +0x20
};

// ---------------------------------------------------------------------------
// transform with a change-tracking header
// ---------------------------------------------------------------------------
class cTransform {
public:
    uint8_t mnPad00[0x0c];              // +0x00
    uint16_t mnFlags;                   // +0x0c
    uint16_t mnVersion;                 // +0x0e
    cVector3 mPosition;                 // +0x10
    void SetPosition(const cVector3* pPosition); // 0x00affde0
};

// ---------------------------------------------------------------------------
// vectors of pointers
// ---------------------------------------------------------------------------
class cPtrItem {
public:
    uint8_t mnPad00[0x48];              // +0x00
    uint32_t mnField48;                 // +0x48
};

class cPtrVector {
public:
    cPtrItem** mpBegin;                 // +0x00
    cPtrItem** mpEnd;                   // +0x04
};

uint32_t CountBits(uint32_t nValue)
{
    nValue = nValue - ((nValue >> 1) & 0x55555555);
    nValue = (nValue & 0x33333333) + ((nValue >> 2) & 0x33333333);
    nValue = ((nValue >> 4) + nValue) & 0x0f0f0f0f;
    return (nValue * 0x01010101) >> 24;
}

// ---------------------------------------------------------------------------
// SP::cTreeData
// ---------------------------------------------------------------------------
namespace SP {
class cTreeData {
public:
    uint8_t mnPad00[0x74];      // +0x00
    float mFruitHeight;         // +0x74
    float GetFruitHeight() const; // 0x00aff240
};
} // namespace SP

// ---------------------------------------------------------------------------
// rotation serializer
// ---------------------------------------------------------------------------
class RotSerial {
public:
    uint8_t mnPad00[0x38];      // +0x00
    void Load(IStream* pStream);  // 0x006b9230
    void Save(IStream* pStream);  // 0x006b9190
};

// ---------------------------------------------------------------------------
// serialization manager / serializable item
// ---------------------------------------------------------------------------
class cRotList {
public:
    RotSerial* mpBegin;                 // +0x00
    RotSerial* mpEnd;                   // +0x04
};

class cSerializeMgr;

class cSerializeItem {
public:
    VSLOT(0) VSLOT(1)
    virtual void Destroy(int32_t nFlags);              // +0x08
    VSLOT(3)
    virtual void WriteItem(cSerializeMgr* pMgr);       // +0x10
    VSLOT(5) VSLOT(6)
    virtual void ReadItem(cSerializeMgr* pMgr);        // +0x1c
    uint8_t mnPad04[0x7c];                             // +0x004
};

class cSerializeMgr {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6)
    virtual void End();                 // +0x1c
    virtual IAVIStream* GetIO();        // +0x20
};

class cSerializeItemList {
public:
    cSerializeItem* mpBegin;            // +0x00
    cSerializeItem* mpEnd;              // +0x04
};

class cRBNode {
public:
    uint8_t mnPad00[0x18];              // +0x00
    cSerializeItem* mpItem;             // +0x18
};

cRBNode* RBTreeIncrement(cRBNode* pNode); // 0x00921580

class cRBTreeAnchor {
public:
    uint32_t mnColor;                   // +0x00
    cRBNode* mpParent;                  // +0x04
    cRBNode* mpLeft;                    // +0x08
    cRBNode* mpRight;                   // +0x0c
};

class cRBTree {
public:
    uint32_t mnPad00;                   // +0x00
    cRBTreeAnchor mAnchor;              // +0x04
};

// ---------------------------------------------------------------------------
// surface decals
// ---------------------------------------------------------------------------
extern float gRadialDensity;            // 0x0167af14

class cSurfaceDecal {
public:
    uint8_t mbUsed;                     // +0x00
    uint8_t mnPad01[0x0b];              // +0x01
    float mRadius;                      // +0x0c
    float mSize;                        // +0x10
    uint8_t mnPad14[0x04];              // +0x14
    void Emit(uint32_t nKind, float nSize);                    // 0x00afef10
    void Generate(float nRadius);                              // 0x00afc640
    void EmitRadial(float nSize, float nStep, int32_t nCount); // 0x00afd6d0
    void EmitArc(float nSize, float nMin, int32_t nFlags);     // 0x00afdc00
    void EmitRing(float nSize);                                // 0x00afdfe0
    void EmitSweep(float nSize);                               // 0x00afe3a0
    void EmitGrid(float nSize);                                // 0x00afe670
};

class cIntVector {
public:
    int32_t* mpBegin;                   // +0x00
    int32_t* mpEnd;                     // +0x04
    void Resize(int32_t nCount);        // 0x004cd3c0
};

class cSurfaceDecalManager;

void SortDecalsImpl(cSurfaceDecal* pBegin, cSurfaceDecal* pEnd,
                    cVector3 vPosition, cSurfaceDecalManager* pManager); // 0x00afee20
void ShuffleIndices(int32_t* pBegin, int32_t* pEnd, void* pRandom);      // 0x00afb8a0
void InitStackVector(int32_t nCount);                                    // 0x00454b80

class cSurfaceDecalManager {
public:
    uint8_t mnPad00[0x50];              // +0x00
    cSurfaceDecal* mpDecalBegin;        // +0x50
    cSurfaceDecal* mpDecalEnd;          // +0x54
    void SortDecals(const cVector3* pPosition, cIntVector* pOrder); // 0x00afeff0
    cSurfaceDecal* FindFreeDecal();                                  // 0x00aff070
};

// ---------------------------------------------------------------------------
// generic object with a key -> field mapping
// ---------------------------------------------------------------------------
class cKeyedValue {
public:
    uint8_t mnPad00[0x14];              // +0x00
    uint32_t mField14;                  // +0x14
    uint32_t mField18;                  // +0x18
    uint32_t mField1c;                  // +0x1c
    uint32_t GetValue(uint32_t nKey);   // 0x00aff250
};

// ---------------------------------------------------------------------------
// Simulator::cFruit
// ---------------------------------------------------------------------------
class cObstacle {
public:
    uint8_t mnPad00[0x44];              // +0x00
    float mField44;                     // +0x44
};

class cObstacleMgr {
public:
    uint64_t MakeKey(uint32_t nA, uint32_t nB, uint32_t nC); // 0x00b72410
    cObstacle* FindById(uint64_t nKey);                      // 0x00b74e90
};

class cVarListSerializer {
public:
    uint8_t mnData[0xa14];              // +0x000
    cVarListSerializer(void* pOwner, void* pVarList, uint32_t nKey); // 0x00692f90
    bool Serialize(cOutStream* pStream);                             // 0x00692900
};

extern uint8_t gVarListDataFruit[];     // 0x01567860
extern uint8_t gVarListDataGame[];      // 0x0167b858

class cGameData {
public:
    bool Write(cOutStream* pStream);    // 0x00b18590
};

namespace Simulator {

class cDecalSubObject {
public:
    void* mpVtbl;                       // +0x00
    uint8_t mnPad04[0x1c];              // +0x04
    void* Cast(uint32_t nType);         // 0x00ac0320
    void Init();                        // 0x00ac0520
};

class cCastSubObject {
public:
    void* mpVtbl;                       // +0x00
    void* Cast(uint32_t nType);         // 0x00ac0320
};

extern void* gVtblFruit[];              // 0x0145c5c8
extern void* gVtblFruit04[];            // 0x0145c5b4
extern void* gVtblFruit34[];            // 0x0145c4f0
extern void* gVtblFruit130[];           // 0x0145c4d0

class cFruit {
public:
    void* mpVtbl00;                     // +0x000
    void* mpVtbl04;                     // +0x004
    uint8_t mnPad08[0x2c];              // +0x008
    cCastSubObject mSub34;              // +0x034
    uint8_t mnPad38[0x14];              // +0x038
    uint32_t mField4c;                  // +0x04c
    uint32_t mField50;                  // +0x050
    uint32_t mField54;                  // +0x054
    uint8_t mnPad58[0xd8];              // +0x058
    cDecalSubObject mDecal;             // +0x130
    uint32_t mField150;                 // +0x150
    uint32_t mField154;                 // +0x154
    uint32_t mnKey158;                  // +0x158
    uint32_t mField15c;                 // +0x15c
    uint32_t mField160;                 // +0x160
    uint32_t mField164;                 // +0x164
    uint32_t mField168;                 // +0x168
    uint8_t mnPad16c[0x1ba18c - 0x16c]; // +0x16c
    int32_t mnTimer;                    // +0x1ba18c

    void Initialize();                                  // 0x00aff280
    void Release();                                     // 0x00c3f850
    bool BaseWrite(cOutStream* pStream);                // 0x00c3fb00
    void* Cast(uint32_t nType);                         // 0x00aff330
    void Reset();                                       // 0x00aff370
    bool Write(cOutStream* pStream);                    // 0x00aff400
    void* CastOther(uint32_t nType);                    // 0x00aff520
    float GetObstacleValue();                           // 0x00aff550
    void AddTime(int32_t nUnused, int32_t nDelta);      // 0x00aff700
    void Finish();                                      // 0x00c3fa70
    void ResetState();                                  // 0x00c3f880
    void* CastBase(uint32_t nType);                     // 0x00c3f850
    void* CastVariant(uint32_t nType);                  // 0x00b18460
    cObstacleMgr* GetObstacleMgr();                     // 0x00b3d3c0
};

} // namespace Simulator

using Simulator::cFruit;

// ---------------------------------------------------------------------------
// game data object that owns the fruit var-list block
// ---------------------------------------------------------------------------
class cFruitGameData : public cGameData {
public:
    bool WriteData(cOutStream* pStream);   // 0x00aff5e0
};

// ---------------------------------------------------------------------------
// SP::cSpatialObjectView
// ---------------------------------------------------------------------------
namespace SP {

class cSpatialObjectData {
public:
    uint8_t mnPad00[0x75];              // +0x000
    uint8_t mbActive;                   // +0x075
    bool IsActive();                    // 0x00c888c0
};

class cSpatialObjectView {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8) VSLOT(9) VSLOT(10)
    virtual void* GetObject();          // +0x2c
    uint8_t mnPad04[0x08];              // +0x04
    cSpatialObjectData* mpData;         // +0x0c
    void HandleSimulationUpdate(uint32_t nA, uint32_t nB); // 0x00e92ca0
    void Update(uint32_t nA, uint32_t nB);                 // 0x00afffa0
};

} // namespace SP

// ---------------------------------------------------------------------------
// state machine object
// ---------------------------------------------------------------------------
class cSubState {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8) VSLOT(9) VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14)
    VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21)
    VSLOT(22) VSLOT(23) VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28)
    VSLOT(29) VSLOT(30) VSLOT(31) VSLOT(32) VSLOT(33) VSLOT(34) VSLOT(35)
    VSLOT(36)
    virtual void SetData(void* pData);  // +0x94
};

extern uint8_t gStateData[];            // 0x01567410

class cStateObject {
public:
    uint8_t mnPad00[0x34];              // +0x000
    cSubState mSub;                     // +0x034
    uint8_t mnPad38[0xa3 - 0x38];       // +0x038
    uint8_t mbFlagA3;                   // +0x0a3
    uint8_t mbFlagA4;                   // +0x0a4
    uint8_t mbFlagA5;                   // +0x0a5
    uint8_t mnPadA6[0x108 - 0xa6];      // +0x0a6
    cRefObject* mpObject108;            // +0x108
    uint8_t mnPad10c[0x168 - 0x10c];    // +0x10c
    uint32_t mField168;                 // +0x168
    uint32_t mnState;                   // +0x16c
    void SetState(int32_t nState, bool bForce); // 0x00b00080
};

// ---------------------------------------------------------------------------
// split reader/writer serializer
// ---------------------------------------------------------------------------
class cSubObject {
public:
    VSLOT(0)
    virtual void Release();             // +0x04
    VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13)
    virtual void Close();               // +0x38
};

class cSplitSerializer {
public:
    uint32_t mField00;                  // +0x00
    uint32_t mnPad04;                   // +0x04
    uint32_t mField08;                  // +0x08
    uint32_t mField0c;                  // +0x0c
    cSubObject* mpReader;               // +0x10
    cSubObject* mpWriter;               // +0x14
    uint32_t mField18;                  // +0x18
    void Reset();                       // 0x00b00150
};

// ---------------------------------------------------------------------------
// fruit editor data
// ---------------------------------------------------------------------------
namespace EA {
namespace Messaging {
class Server;
class IHandler {
public:
    uint8_t mnPad00[0x04];              // +0x00
};
Server* GetServer(); // 0x00883860
class Server {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8)
    virtual void AddHandler(IHandler* pHandler, uint32_t nMessageId); // +0x24
};
} // namespace Messaging
} // namespace EA

class cSPEditorAnimatedCreatureData {
public:
    uint8_t mnPad00[0x04];              // +0x00
    void SetLastAnimationPlayed(uint32_t nAnimation); // 0x007cd950
    void ResetAnimation();                            // 0x007cd960
};

extern uint32_t gFruitMessageIds[];     // 0x0145c6b0
extern void* gFruitAutoHandlerVtbl[];   // 0x0145c6b0

class cFruitEditorData : public EA::Messaging::IHandler {
public:
    uint8_t mnPad00[0x1c];              // +0x00004
    EA::Messaging::Server* mpServer;    // +0x00020
    EA::Messaging::IHandler* mpHandler; // +0x00024
    uint32_t* mpIdArray;                // +0x00028
    uint32_t mnIdCount;                 // +0x0002c
    int32_t mnPriority;                 // +0x00030
    uint8_t mnPad34[0x1b8f30 - 0x34];   // +0x00034
    cSPEditorAnimatedCreatureData* mpCreatureData; // +0x1b8f30
    uint8_t mnPad1b8f34[0x1ba18c - 0x1b8f34]; // +0x1b8f34
    uint32_t mnFlags;                   // +0x1ba18c
    void OnCreated();                   // 0x00b001b0
};

// ---------------------------------------------------------------------------
// noun plumbing
// ---------------------------------------------------------------------------
class cGameNounManager {
public:
    cFruit* CreateNoun(uint32_t nType); // 0x00b20c60
};

cGameNounManager* NounManager(uint32_t nType); // 0x00b3d300

extern uint32_t gNextFruitId;           // 0x0167af58
extern uint32_t gFruitNounData[];       // 0x0167af5c
extern uint8_t gFruitNounData2[];       // 0x0156741c

cFruit* CreateFruit();                  // 0x00b00220

// ---------------------------------------------------------------------------
// global defaults used by the serializer field writers
// ---------------------------------------------------------------------------
static cVector2 const gDefaultVector2(0.0f); // 0x0167bab8
static uint8_t gDefaultByte = 0;             // 0x0167bae8

// ---------------------------------------------------------------------------
// implementations
// ---------------------------------------------------------------------------

// @ 0x00afef10
void cSurfaceDecal::Emit(uint32_t nKind, float nSize)
{
    mSize = nSize;
    switch (nKind) {
    case 0:
        Generate(0.0f);
        break;
    case 1:
        EmitRadial(nSize, 1.0f,
                   (int32_t)(((mRadius - nSize) / nSize) * gRadialDensity));
        break;
    case 2:
        EmitArc(nSize, mRadius - nSize, 0);
        break;
    case 3:
        EmitRing(nSize);
        break;
    case 4:
        EmitSweep(nSize);
        break;
    case 5:
        EmitGrid(nSize);
        break;
    }
}

// @ 0x00afeff0
void cSurfaceDecalManager::SortDecals(const cVector3* pPosition,
                                      cIntVector* pOrder)
{
    int32_t nCount = (int32_t)(((uint8_t*)mpDecalEnd - (uint8_t*)mpDecalBegin) /
                               0x18);
    pOrder->Resize(nCount);
    for (int32_t i = 0; i < nCount; ++i)
        pOrder->mpBegin[i] = i;
    SortDecalsImpl(mpDecalBegin, mpDecalEnd, *pPosition, this);
}

// @ 0x00aff070
cSurfaceDecal* cSurfaceDecalManager::FindFreeDecal()
{
    int32_t nCount = (int32_t)(((uint8_t*)mpDecalEnd - (uint8_t*)mpDecalBegin) /
                               0x18);
    if (nCount == 0)
        return 0;
    int32_t nOrder[64];
    InitStackVector(nCount);
    for (int32_t i = 0; i < nCount && i < 64; ++i)
        nOrder[i] = i;
    ShuffleIndices(nOrder, nOrder + (nCount < 64 ? nCount : 64), 0);
    for (int32_t i = 0; i < nCount && i < 64; ++i) {
        cSurfaceDecal* pDecal = mpDecalBegin + nOrder[i];
        if (pDecal->mbUsed == 0)
            return pDecal;
    }
    return 0;
}

// @ 0x00aff160
uint32_t SmearBits(uint32_t nValue)
{
    nValue |= nValue >> 1;
    nValue |= nValue >> 2;
    nValue |= nValue >> 4;
    nValue |= nValue >> 8;
    return nValue | (nValue >> 16);
}

// @ 0x00aff240
float SP::cTreeData::GetFruitHeight() const
{
    return mFruitHeight * 0.25f;
}

// @ 0x00aff250
uint32_t cKeyedValue::GetValue(uint32_t nKey)
{
    switch (nKey) {
    case 0x29c388a:
        return mField18;
    case 0x3a8be428:
        return mField14;
    case 0x6d60a1cc:
        return mField1c;
    }
    return 0;
}

// @ 0x00aff280
void cFruit::Initialize()
{
    mpVtbl00 = gVtblFruit;
    mpVtbl04 = gVtblFruit04;
    mSub34.mpVtbl = gVtblFruit34;
    mDecal.mpVtbl = gVtblFruit130;
    mnKey158 = 0x6d60a1cc;
    mField15c = 0xffffffff;
    mField160 = 0xffffffff;
    mField150 = 0;
    mField154 = 0;
    mField164 = 0xffffffff;
    mField168 = 0;
    mDecal.Init();
    Finish();
}

// @ 0x00aff330
void* cFruit::Cast(uint32_t nType)
{
    switch (nType) {
    case 0x2c9cc8e:
        return this;
    }
    void* pObject = mDecal.Cast(nType);
    if (pObject != 0)
        return pObject;
    return CastBase(nType);
}

// @ 0x00aff370
void cFruit::Reset()
{
    ResetState();
    mField150 = 0xffffffff;
    mField154 = 0;
    mField164 = 0xffffffff;
    mnKey158 = 0x6d60a1cc;
    mField15c = 0xffffffff;
    mField160 = 0xffffffff;
    mField168 = 0;
}

// @ 0x00aff400
bool cFruit::Write(cOutStream* pStream)
{
    uint32_t nType = 0x2c9cc8e;
    IAVIStream* pIO = pStream->GetIO();
    IStream* pOut = pIO->GetStream();
    EA::IO::WriteUint32(pOut, &nType, 1, 0);
    bool bResult = BaseWrite(pStream);
    cVarListSerializer serializer(this, gVarListDataFruit, 0x1a80d26);
    if (bResult && serializer.Serialize(pStream))
        return true;
    return false;
}

// @ 0x00aff520
void* cFruit::CastOther(uint32_t nType)
{
    switch (nType) {
    case 0x2e9688e:
        return this;
    }
    void* pObject = CastVariant(nType);
    if (pObject != 0)
        return pObject;
    return mSub34.Cast(nType);
}

// @ 0x00aff550
float cFruit::GetObstacleValue()
{
    cObstacleMgr* pManager = GetObstacleMgr();
    uint64_t nKey = pManager->MakeKey(mField50, mField4c, mField54);
    cObstacle* pObstacle = pManager->FindById(nKey);
    if (pObstacle != 0)
        return pObstacle->mField44;
    return 0.0f;
}

// @ 0x00aff5e0
bool cFruitGameData::WriteData(cOutStream* pStream)
{
    uint32_t nType = 0x2e9688e;
    IAVIStream* pIO = pStream->GetIO();
    IStream* pOut = pIO->GetStream();
    EA::IO::WriteUint32(pOut, &nType, 1, 0);
    bool bResult = Write(pStream);
    cVarListSerializer serializer(this, gVarListDataGame, 0x1a80d26);
    if (bResult && serializer.Serialize(pStream))
        return true;
    return false;
}

// @ 0x00aff700
void cFruit::AddTime(int32_t nUnused, int32_t nDelta)
{
    if ((int32_t)mnTimer > 0)
        mnTimer -= nDelta;
}

// @ 0x00aff7e0
bool LoadRotation(cOutStream* pStream, RotSerial* pRotation)
{
    pRotation->Load(pStream->GetIO()->GetStream());
    return true;
}

// @ 0x00aff810
bool SaveRotation(cOutStream* pStream, RotSerial* pRotation)
{
    pRotation->Save(pStream->GetIO()->GetStream());
    return true;
}

// @ 0x00aff870
bool WriteUint64Value(cOutStream* pStream, const uint64_t* pValue)
{
    IAVIStream* pIO = pStream->GetIO();
    uint64_t nValue = *pValue;
    IStream* pStream2 = pIO->GetStream();
    EA::IO::WriteUint64(pStream2, &nValue, 1, 0);
    return true;
}

// @ 0x00aff8b0
void WriteVector2Value(cValueHost* pHost)
{
    cVector2* pValue = (cVector2*)pHost->mpfnGet(pHost);
    *pValue = gDefaultVector2;
}

// @ 0x00aff930
void WriteVector3Value(cValueHost* pHost)
{
    cVector3* pValue = (cVector3*)pHost->mpfnGet(pHost);
    static cZeroVector3 sDefault;
    *pValue = reinterpret_cast<cVector3&>(sDefault);
}

// @ 0x00aff9e0
void WriteByteValue(cValueHost* pHost)
{
    uint8_t* pValue = (uint8_t*)pHost->mpfnGet(pHost);
    *pValue = gDefaultByte;
}

// @ 0x00affae0
void WriteVector3Value2(cValueHost* pHost)
{
    cVector3* pValue = (cVector3*)pHost->mpfnGet(pHost);
    static cZeroVector3 sDefault;
    *pValue = reinterpret_cast<cVector3&>(sDefault);
}

// @ 0x00affb30
void WriteVector3Value3(cValueHost* pHost)
{
    cVector3* pValue = (cVector3*)pHost->mpfnGet(pHost);
    static cZeroVector3 sDefault;
    *pValue = reinterpret_cast<cVector3&>(sDefault);
}

// @ 0x00affb80
void WriteVector3Value4(cValueHost* pHost)
{
    cVector3* pValue = (cVector3*)pHost->mpfnGet(pHost);
    static cZeroVector3 sDefault;
    *pValue = reinterpret_cast<cVector3&>(sDefault);
}

// @ 0x00affc90
void __stdcall DestroyItemRange(cSerializeItem* pBegin, cSerializeItem* pEnd)
{
    while (pBegin < pEnd) {
        pBegin->Destroy(0);
        ++pBegin;
    }
}

// @ 0x00affcc0
cSerializeItem* DestroyItemRangeInto(cSerializeItem* pBegin,
                                     cSerializeItem* pEnd,
                                     cSerializeItem* pOut)
{
    while (pBegin != pEnd) {
        pBegin->Destroy(0);
        ++pBegin;
        ++pOut;
    }
    return pOut;
}

// @ 0x00affde0
void cTransform::SetPosition(const cVector3* pPosition)
{
    mPosition = *pPosition;
    mnFlags |= 4;
    ++mnVersion;
}

// @ 0x00affe10
uint32_t CountItemBits(const cPtrVector* pVector)
{
    if (pVector == 0)
        return 0;
    uint32_t nCount = (uint32_t)(pVector->mpEnd - pVector->mpBegin);
    uint32_t nSum = 0;
    for (uint32_t i = 0; i < nCount; ++i)
        nSum += CountBits(pVector->mpBegin[i]->mnField48);
    return nSum;
}

// @ 0x00afff30
void* VectorAt(const cPtrVector* pVector, uint32_t nIndex)
{
    if (pVector == 0)
        return 0;
    if (nIndex < (uint32_t)(pVector->mpEnd - pVector->mpBegin))
        return pVector->mpBegin[nIndex];
    return 0;
}

// @ 0x00afffa0
void SP::cSpatialObjectView::Update(uint32_t nA, uint32_t nB)
{
    if (mpData->mbActive == 0)
        return;
    if (GetObject() == 0) {
        if (!mpData->IsActive())
            return;
    }
    HandleSimulationUpdate(nA, nB);
}

// @ 0x00b00000
float RandomRange()
{
    extern double RandomUniform();      // 0x009360d0
    extern float gRangeMin;             // 0x01567398
    extern float gRangeMax;             // 0x0156739c
    if (gRangeMin == -1.0f || gRangeMax == -1.0f)
        return -1.0f;
    return RandomUniform() * (gRangeMax - gRangeMin) + gRangeMin;
}

// @ 0x00b00080
void cStateObject::SetState(int32_t nState, bool bForce)
{
    if (!bForce && nState == (int32_t)mnState)
        return;
    switch (nState) {
    case 0:
        mnState = nState;
        mbFlagA4 = 1;
        mbFlagA3 = 1;
        break;
    case 2:
        mnState = nState;
        mField168 = 0;
        break;
    case 3:
        mnState = nState;
        mbFlagA5 = 1;
        break;
    case 4:
        mbFlagA4 = 0;
        mbFlagA3 = 0;
        mSub.SetData(gStateData);
        mnState = nState;
        break;
    case 5:
    case 6:
        if (mpObject108 != 0) {
            cRefObject* pObject = mpObject108;
            mpObject108 = 0;
            pObject->Release();
        }
        // fall through
    case 1:
        mnState = nState;
        break;
    }
}

// @ 0x00b00150
void cSplitSerializer::Reset()
{
    mField00 = 0;
    mField08 = 0;
    mField0c = 0;
    if (mpReader != 0) {
        cSubObject* pReader = mpReader;
        mpReader = 0;
        pReader->Release();
    }
    if (mpWriter != 0) {
        cSubObject* pWriter = mpWriter;
        mpWriter = 0;
        pWriter->Close();
    }
    mField18 = 0;
    if (mpWriter != 0)
        mpWriter->Close();
    if (mpReader != 0)
        mpReader->Release();
}

// @ 0x00b001b0
void cFruitEditorData::OnCreated()
{
    EA::Messaging::Server* pServer = EA::Messaging::GetServer();
    mpServer = pServer;
    mpHandler = this;
    mpIdArray = gFruitMessageIds;
    mnIdCount = 4;
    mnPriority = 0;
    EA::Messaging::IHandler* pHandler = this;
    if (pServer != 0 && pHandler != 0) {
        for (uint32_t i = 0; i < 4; ++i)
            pServer->AddHandler(pHandler, gFruitMessageIds[i]);
    }
    mpCreatureData->SetLastAnimationPlayed(0x30fc4ec);
    mpCreatureData->ResetAnimation();
    mnFlags |= 0x28;
}

// @ 0x00b00220
cFruit* CreateFruit()
{
    cFruit* pFruit = NounManager(0x2c9cc91)->CreateNoun(0x2c9cc91);
    if (pFruit == 0)
        return 0;
    pFruit->Initialize();
    ++gNextFruitId;
    pFruit->Release();
    return pFruit;
}

// @ 0x00b002e0
void SetObjectValue(cValueHost* pHost)
{
    AutoRefCount<cRefObject>* pValue =
        (AutoRefCount<cRefObject>*)pHost->mpfnGet(pHost);
    static AutoRefCount<cRefObject> sDefault;
    *pValue = sDefault.mpObject;
}

// @ 0x00b00350
void WriteVector3Value5(cValueHost* pHost)
{
    cVector3* pValue = (cVector3*)pHost->mpfnGet(pHost);
    static cVector3 const sDefault;
    *pValue = sDefault;
}

// @ 0x00b00390
void WriteItemList(cSerializeMgr* pMgr, const cSerializeItemList* pList)
{
    IAVIStream* pIO = pMgr->GetIO();
    uint32_t nCount = (uint32_t)(pList->mpEnd - pList->mpBegin);
    IStream* pStream = pIO->GetStream();
    EA::IO::WriteUint32(pStream, &nCount, 1, 0);
    cSerializeItem* pItem = pList->mpBegin;
    cSerializeItem* pEnd = pList->mpEnd;
    for (; pItem != pEnd; ++pItem)
        pItem->WriteItem(pMgr);
    pMgr->End();
}

// @ 0x00b00400
bool ReadItemList(cSerializeMgr* pMgr, const cSerializeItemList* pList)
{
    cSerializeItem* pItem = pList->mpBegin;
    cSerializeItem* pEnd = pList->mpEnd;
    for (; pItem != pEnd; ++pItem) {
        cSerializeItem* pReadItem = pItem;
        if (pReadItem != 0)
            pReadItem->ReadItem(pMgr);
    }
    return true;
}

// @ 0x00b00450
void WriteRotationList(cSerializeMgr* pMgr, const cRotList* pList)
{
    uint32_t nCount = (uint32_t)((pList->mpEnd - pList->mpBegin));
    IAVIStream* pIO = pMgr->GetIO();
    IStream* pStream = pIO->GetStream();
    EA::IO::WriteUint32(pStream, &nCount, 1, 0);
    RotSerial* pItem = pList->mpBegin;
    RotSerial* pEnd = pList->mpEnd;
    for (; pItem != pEnd; ++pItem)
        pItem->Save(pMgr->GetIO()->GetStream());
    pMgr->End();
}

// @ 0x00b004e0
bool ReadTreeItems(cSerializeMgr* pMgr, const cRBTree* pTree)
{
    for (cRBNode* pNode = pTree->mAnchor.mpParent;
         pNode != (cRBNode*)&pTree->mAnchor; pNode = RBTreeIncrement(pNode)) {
        if (pNode->mpItem != 0)
            pNode->mpItem->ReadItem(pMgr);
    }
    return true;
}
