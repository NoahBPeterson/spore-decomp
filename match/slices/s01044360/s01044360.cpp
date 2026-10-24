// Slice s01044360 -- SP::cStarMap action helpers, flag bookkeeping, serializer and
// the eastl::rbtree lookups used by the star-map screen.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

extern "C" float __cdecl SqrtF(float);
extern "C" float __cdecl FabsF(float);

namespace SP {

struct Vector3 { float x, y, z; };
struct Quaternion { float w, x, y, z; };

// --------------------------------------------------------------- eastl red-black tree
struct RBNode {
    RBNode*  mpLeft;       // +0x00
    RBNode*  mpRight;      // +0x04
    RBNode*  mpParent;     // +0x08
    uint32_t mColor;       // +0x0c
    uint32_t mPad10;       // +0x10
    uint32_t mValue;       // +0x14
    uint32_t mKey;         // +0x18
    uint32_t mPad1c;       // +0x1c
    uint32_t mPad20;       // +0x20
    uint8_t  mFlags;       // +0x24
    uint8_t  mPad25[3];    // +0x25
};

struct NodeRange {
    RBNode* mpFirst;
    RBNode* mpSecond;
};

// The tree object begins at cStarMap+0x58; its sentinel node is the first member of
// the anchor and the root/rightmost links follow it.
struct RBTree {
    uint32_t mPad00;       // +0x00
    RBNode*  mpEnd;        // +0x04 (sentinel; also the end iterator)
    RBNode*  mpRoot;       // +0x08
    RBNode*  mpRightmost;  // +0x0c
    uint32_t mSize;        // +0x10
    uint32_t mPad14;       // +0x14
    uint32_t mPad18;       // +0x18
    uint32_t mPad1c;       // +0x1c
    void equal_range(NodeRange* out, const uint32_t* key); // 0x00d4b450
};

RBNode* __cdecl RBTreeIncrement(RBNode* node);                                       // 0x00921580

// --------------------------------------------------------------- external engine types
struct cVtblObject { void* mpVtable; };
struct cSink;

struct cIOStream {
    void* mpVtable;                                        // +0x00
    cSink* GetSink() {
        return ((cSink* (__thiscall*)(cIOStream*))((void**)mpVtable)[0x20 / 4])(this);
    }
    void* GetStream() {
        return ((void* (__thiscall*)(cIOStream*))((void**)mpVtable)[0x1c / 4])(this);
    }
    void WriteRef(void* value) {
        ((void (__thiscall*)(cIOStream*, void*))((void**)mpVtable)[0x2c / 4])(this, value);
    }
};

struct cSink {
    void* mpVtable;                                        // +0x00
    void* GetStream() {
        return ((void* (__thiscall*)(cSink*))((void**)mpVtable)[0x18 / 4])(this);
    }
};

struct cVarListSerializer {
    uint32_t mData[7];                                     // 0x1c bytes
    void Init(void* owner, const void* list, uint32_t line); // 0x00692f90
    bool Serialize(cIOStream* stream);                     // 0x00692900
};

void* __cdecl MemAlloc(uint32_t size, const char* tag, int a, int b,
                       const char* file, uint32_t line);                               // 0x00f473a0
void  __cdecl MemFreeArray(void* p);                                                   // 0x00f47380
void* __cdecl MemCopy(void* dst, const void* src, uint32_t size);                      // 0x011e0744
void* __cdecl MemMove(void* dst, const void* src, uint32_t size);                      // memmove

extern const float gForwardX;      // 0x015b8528
extern const float gForwardY;      // 0x015b852c
extern const float gForwardZ;      // 0x015b8530
extern const float gAltX;          // 0x015b8534
extern const float gAltY;          // 0x015b8538
extern const float gAltZ;          // 0x015b853c
extern const float gEpsilon;       // 0x013ec4b8
extern const float gDotThreshold;  // 0x013eb960
extern const float gSignMask;      // 0x013eb8b0
extern const char  gBannerName;    // 0x016e0688
extern const char  gSerializerList;// 0x015b85a0
extern const char  gAllocatorFile; // 0x013ebb38
extern const char  gAllocatorTag;  // 0x013f09b4 ("Simulator")
extern const char  gEntryName;     // 0x0179c807

struct GameDataVec {
    void* mpBegin;                                         // +0x00
    void* mpEnd;                                           // +0x04
};

struct NounQueryResult {
    uint32_t mPad00;                                       // +0x00
    GameDataVec mVector;                                   // +0x04
};

struct cEmbeddedSource {
    void* mpVtable;                                        // +0x00
    void* GetKey() {
        return ((void* (__thiscall*)(cEmbeddedSource*))((void**)mpVtable)[0x2c / 4])(this);
    }
    Vector3* GetPosition() {
        return ((Vector3* (__thiscall*)(cEmbeddedSource*))((void**)mpVtable)[0x2c / 4])(this);
    }
};

struct cItemOwner {
    void* mpVtable;                                        // +0x00
    bool HasItem(const void* id) {
        return ((bool (__thiscall*)(cItemOwner*, const void*))
            ((void**)mpVtable)[0x74 / 4])(this, id);
    }
};

struct cPlayerInventory {
    cItemOwner* mpOwner;                                   // +0x00
    uint32_t mPad04[0x30 / 4];                             // +0x04
    cEmbeddedSource mKeySource;                            // +0x34
};

struct cLocatedNoun {
    uint32_t mPad00[0x120 / 4];                            // +0x00
    cEmbeddedSource mPositionSource;                       // +0x120
};

struct SubsystemVec {
    void** mpBegin;                                        // +0x00
    void** mpEnd;                                          // +0x04
};

struct cGameNounManager {
    NounQueryResult* __thiscall GetGameDataVector(void* a, void* b, void* c, void* d, void* e);
    SubsystemVec* GetSubsystemVec(void* id);               // 0x00ae7200
};

struct cPlanetView {
    void* mpVtable;                                        // +0x00
    void* FindObject(uint32_t id) {
        return ((void* (__thiscall*)(cPlanetView*, uint32_t))((void**)mpVtable)[0x0c / 4])(this, id);
    }
};

struct cCameraController {
    void* mpVtable;                                        // +0x00
    cPlanetView* GetPlanetView() {
        return ((cPlanetView* (__thiscall*)(cCameraController*))((void**)mpVtable)[0x38 / 4])(this);
    }
};

struct cApp {
    void* mpVtable;                                        // +0x00
    cCameraController* GetCameraController() {
        return ((cCameraController* (__thiscall*)(cApp*))((void**)mpVtable)[0x50 / 4])(this);
    }
};

struct cZoomTarget {
    void* mpVtable;                                        // +0x00
    float GetZoom() {
        return ((float (__thiscall*)(cZoomTarget*))((void**)mpVtable)[0x5c / 4])(this);
    }
    void SetZoom(int a, float b, float c, int d) {
        ((void (__thiscall*)(cZoomTarget*, int, float, float, int))
            ((void**)mpVtable)[0x3c / 4])(this, a, b, c, d);
    }
};

struct cStarMapView {
    void* mpVtable;                                        // +0x00
    long long GetId() {
        return ((long long (__thiscall*)(cStarMapView*))((void**)mpVtable)[0x60 / 4])(this);
    }
};

struct cMiniCaptureHost {
    cStarMapView* mpView;                                  // +0x00
};

struct cBannerList {
    void* mpVtable;                                        // +0x00
    int FindEntry(uint32_t key);                           // 0x00ba6d80
    void Reset();                                          // 0x00ba6490
};

struct cActionTarget {
    uint32_t mData[9];                                     // 0x24 bytes
    ~cActionTarget();
};

struct CamInfo {
    uint32_t mData[0x10];                                  // 0x40 bytes
    void __thiscall init(const Vector3* position, const Quaternion* orientation);
};

struct cTriggerMgr {
    void* mpVtable;                                        // +0x00
    void __thiscall PostAction(uint32_t actionId, cActionTarget* target, int flags);
};

struct cHudBanner {
    void* mpVtable;                                        // +0x00
    void Show(const void* text, int id, int arg) {
        ((void (__thiscall*)(cHudBanner*, const void*, int, int))
            ((void**)mpVtable)[0x4c / 4])(this, text, id, arg);
    }
    void Hide(int id) {
        ((void (__thiscall*)(cHudBanner*, int))((void**)mpVtable)[0x50 / 4])(this, id);
    }
};

struct cProperty {
    void* mpVtable;                                        // +0x00
    uint8_t mPad04[0x0e];                                  // +0x04
    uint16_t mType;                                        // +0x12
    bool Query(uint32_t id, cProperty** out) {
        return ((bool (__thiscall*)(cProperty*, uint32_t, cProperty**))
            ((void**)mpVtable)[0x24 / 4])(this, id, out);
    }
    int* GetInt();                                         // 0x0041e990
    float* GetFloat();                                     // 0x0041ea70
};

struct cPropertyManager {
    void* mpVtable;                                        // +0x00
    void GetProperty(uint32_t a, uint32_t b, cProperty** out) {
        ((void (__thiscall*)(cPropertyManager*, uint32_t, uint32_t, cProperty**))
            ((void**)mpVtable)[0x2c / 4])(this, a, b, out);
    }
};

// ------------------------------------------------------------------ engine entry points
cGameNounManager* __cdecl NounManager();                   // 0x00b3d300
void* __cdecl GetUFOSimulator();                           // 0x00ffbe50
cPlayerInventory* GetPlayerInventoryOf(void*);              // 0x00a1ad60
void* __cdecl FUN_00ac9310(GameDataVec* vec, void* key, char flag); // 0x00ac9310
Quaternion* __cdecl QuaternionFromFacingAndUp(Quaternion* out, const Vector3* facing,
                                              const Vector3* up); // 0x0069b600
cTriggerMgr* __cdecl GetTriggerMgr();                      // 0x00b3d4d0
cApp* __cdecl App();                                       // 0x0067dd10
cHudBanner* __cdecl FUN_0067dd50();                        // 0x0067dd50
int __cdecl GetUniverseContext();                          // 0x01021080
cPropertyManager* __cdecl PropertyManager();               // 0x0067de30
void __cdecl FUN_00feb060(const void* table);              // 0x00feb060
cBannerList* __cdecl StarManager();                        // 0x00b3d2a0
float __cdecl FUN_00c8c5d0(int index, float* out);         // 0x00c8c5d0
void __cdecl WriteUint32(void* stream, const uint32_t* value,
                         int count, int flags);            // 0x0093aa70
void* __cdecl FUN_00b3d4a0();                              // 0x00b3d4a0
char __cdecl FUN_00ae9390();                               // 0x00ae9390
void* __cdecl GameTimeManager();                           // 0x00b3d3d0
void* __cdecl SpaceGameGet();                              // 0x00b1e500
void* __cdecl FUN_00ae7200(void* key);                     // 0x00ae7200
void* __cdecl FUN_005c65e0(void* civData);                 // 0x005c65e0
struct cSPSimulatorSpaceGame {
    void* mpVtable;                                        // +0x00
    cPlayerInventory* GetPlayerInventory();                // 0x00a1ad60
    float GetMaxZ();                                       // 0x00ffbfd0
};
struct cCivData {
    void* mpVtable;                                        // +0x00
    float* GetCities();                                    // 0x005c65e0
    float* GetCityPosition();                              // 0x005c65e0
};
struct cPlayerCityData {
    uint32_t mPad00[0x718 / 4];                            // +0x00
    Vector3  mCityPosition;                                // +0x718
};

// ------------------------------------------------------------------ cStarMap
struct cStarMap {
    uint8_t       mFirstFlag;          // +0x00
    bool          mRequestZoom;        // +0x01
    uint8_t       mPad02[2];           // +0x02
    uint32_t      mSlots[8];           // +0x04
    uint32_t      mPad24[0x28 / 4];    // +0x24 .. +0x4b
    float         mZoomRequestHeight;  // +0x4c
    int           mTravelTrailLength;  // +0x50
    uint32_t      mPad54;              // +0x54
    RBTree        mTree;               // +0x58
    uint32_t      mVisualCount;        // +0x74

    uint32_t* FindNode(int key);
    uint32_t* FindNodeValue(int key);    void SetNodeFlag(int key, char on);
    void SetNodeFlag2(int key, char on);
    void SyncEntryFlags(char enable);
    bool IsSlotSet(int index);
    void Notify(int id, char flag);
    void UpdateDesiredCamera();
    bool UpdateMiniCaptureBar(float value);
    void Init();
    void SerializeSlots(cIOStream* stream);
    uint32_t FindValue(uint32_t bucket, int key);
    uint32_t FindEntryByLongId(uint32_t key, uint32_t lo, uint32_t hi);
};

// Flag grid used by the serializer (rows of 0x40 entries).
struct cFlagGrid {
    uint32_t mPad00;                   // +0x00
    uint32_t mPad04;                   // +0x04
    int*     mpBegin;                  // +0x08
    uint32_t mPad0c;                   // +0x0c
    int*     mpRowEnd;                 // +0x10
    int**    mpRowBase;                // +0x14
    int*     mpEnd;                    // +0x18
    int*     mpEndCap;                 // +0x1c
    uint32_t mPad20;                   // +0x20
    int*     mpLastRowEnd;             // +0x24
};

// Bit block used by the flag insert helper.
struct cBitVector {
    uint32_t* mpData;                  // +0x00
    uint32_t  mCapacity;               // +0x04
    uint32_t  mPad08;                  // +0x08
    uint32_t  mFirstValue;             // +0x0c
    uint32_t  mFirstCap;               // +0x10
    uint32_t* mpBegin;                 // +0x14
    uint32_t  mPad18;                  // +0x18
    uint32_t  mLastValue;              // +0x1c
    uint32_t  mLastCap;                // +0x20
    uint32_t* mpEnd;                   // +0x24
    void __thiscall InsertAtFront(uint32_t count, uint32_t value);
};

struct cFlagEntry {
    void* mpVtable;                    // +0x00
    void SerializeInto(void* stream) {
        ((void (__thiscall*)(cFlagEntry*, void*))((void**)mpVtable)[0x1c / 4])(this, stream);
    }
    void* GetName(const void* id) {
        return ((void* (__thiscall*)(cFlagEntry*, const void*))
            ((void**)mpVtable)[0x0c / 4])(this, id);
    }
};

struct cFlagObj {
    void* mpVtable;                    // +0x00
    void AddRef() {
        ((void (__thiscall*)(cFlagObj*))((void**)mpVtable)[0x00 / 4])(this);
    }
};

struct SharedRefSrc {
    uint32_t  mValue;                  // +0x00
    cFlagObj* mpRef;                   // +0x04
    uint32_t  mA;                      // +0x08
    uint32_t  mB;                      // +0x0c
    uint32_t  mC;                      // +0x10
    uint8_t   mD;                      // +0x14
};

struct SharedRefData {
    uint32_t  mValue;                  // +0x00
    cFlagObj* mpRef;                   // +0x04
    uint32_t  mA;                      // +0x08
    uint32_t  mB;                      // +0x0c
    uint32_t  mC;                      // +0x10
    uint8_t   mD;                      // +0x14
};

struct SharedRefBlock {
    uint32_t      mHeader[4];          // +0x00 .. +0x0f
    SharedRefData mData;               // +0x10
};

// ------------------------------------------------------------------ travel actions
static bool TravelToSystem(uint32_t actionId)
{
    cGameNounManager* nouns = NounManager();
    NounQueryResult* result = nouns->GetGameDataVector(
        (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00acdff0,
        (void*)0x00b1e500, (void*)0x018c43e8);
    if (result->mVector.mpBegin == result->mVector.mpEnd)
        return false;

    void* simulator = GetUFOSimulator();
    cPlayerInventory* inventory = ((cSPSimulatorSpaceGame*)simulator)->GetPlayerInventory();
    void* key = inventory->mKeySource.GetKey();
    cLocatedNoun* noun = (cLocatedNoun*)FUN_00ac9310(&result->mVector, key, 0);
    if (!noun)
        return false;

    Vector3 pos = *noun->mPositionSource.GetPosition();

    float invLen = 1.0f / SqrtF(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z + gEpsilon);
    Vector3 forward;
    forward.x = pos.x * invLen;
    forward.y = pos.y * invLen;
    forward.z = pos.z * invLen;

    float axisX = gForwardX;
    float axisY = gForwardY;
    float axisZ = gForwardZ;
    if (FabsF(axisZ * forward.z + (axisY * forward.y + axisX * forward.x) - 1.0f)
        < gDotThreshold) {
        axisX = -gAltX;
        axisY = -gAltY;
        axisZ = -gAltZ;
    }

    Vector3 right;
    right.x = axisZ * forward.y - axisY * forward.z;
    right.y = axisY * forward.x - axisX * forward.y;
    right.z = axisX * forward.z - axisZ * forward.x;
    float rightLen = 1.0f / SqrtF(right.x * right.x + right.y * right.y
                                            + right.z * right.z + gEpsilon);
    right.x *= rightLen;
    right.y *= rightLen;
    right.z *= rightLen;

    Vector3 up;
    up.x = right.z * forward.y - right.y * forward.z;
    up.y = right.y * forward.x - right.x * forward.y;
    up.z = right.x * forward.z - right.z * forward.x;
    float upLen = 1.0f / SqrtF(up.x * up.x + up.y * up.y + up.z * up.z + gEpsilon);
    up.x *= upLen;
    up.y *= upLen;
    up.z *= upLen;

    Quaternion orientation;
    QuaternionFromFacingAndUp(&orientation, &right, &forward);

    CamInfo info;
    cActionTarget target;
    info.init(noun->mPositionSource.GetPosition(), &orientation);
    GetTriggerMgr()->PostAction(actionId, &target, 0);
    return true;
}

// @ 0x01044360
bool __cdecl FUN_01044360()
{
    return TravelToSystem(0x640b84cf);
}

// @ 0x01044640
bool __cdecl FUN_01044640()
{
    return TravelToSystem(0xcb74853c);
}

// @ 0x01044920
bool __cdecl FUN_01044920()
{
    cApp* app = App();
    cCameraController* camera = app->GetCameraController();
    cPlanetView* view = camera->GetPlanetView();
    if (!view)
        return false;
    void* object = view->FindObject(0x303154cd);
    if (!object)
        return false;
    FUN_00b3d4a0();
    if (FUN_00ae9390())
        return false;
    if (((uint8_t*)GameTimeManager())[0x48] & 1)
        return false;
    void* game = SpaceGameGet();
    cPlayerInventory* inventory = ((cSPSimulatorSpaceGame*)game)->GetPlayerInventory();
    if (!inventory->mpOwner->HasItem(&gBannerName))
        return false;
    if (((char*)GetUFOSimulator())[0x20])
        return false;
    SubsystemVec* vec = NounManager()->GetSubsystemVec((void*)0x0142db2a);
    void** it = vec->mpBegin;
    void** last = vec->mpEnd;
    while (it != last) {
        void* entry = *it;
        if (((bool (__thiscall*)(void*))((void**)*(void**)entry)[0x24 / 4])(entry))
            return false;
        ++it;
    }
    return true;
}

// @ 0x010449e0
bool cStarMap::IsSlotSet(int index)
{
    if (index < 0 || (uint32_t)index > 7)
        return false;
    return mSlots[index] == 1;
}

// @ 0x01044a10
void cStarMap::Notify(int id, char flag)
{
    if (flag && GetUniverseContext() == 2) {
        cHudBanner* banner = FUN_0067dd50();
        banner->Show(&gBannerName, 0x17, 0);
        return;
    }
    if (mSlots[0] != 1 && mSlots[1] != 1) {
        cHudBanner* banner = FUN_0067dd50();
        banner->Hide(0x17);
    }
}

// @ 0x01044a70
void cStarMap::SerializeSlots(cIOStream* stream)
{
    for (int i = 0; i < 7; ++i) {
        uint32_t value = mSlots[i];
        cSink* sink = stream->GetSink();
        WriteUint32(sink->GetStream(), &value, 1, 0);
    }
    cVarListSerializer serializer;
    serializer.Init(this, &gSerializerList, 0x1a80d26);
    serializer.Serialize(stream);
}

// @ 0x01044b00
bool __stdcall UpdateMiniCaptureBar(cMiniCaptureHost* self, float value)
{
    cBannerList* list = StarManager();
    int index = list->FindEntry(*(uint32_t*)&value);
    float ratio = -1.0f;
    StarManager()->Reset();
    long long id = self->mpView->GetId();
    if ((uint32_t)id == 0xff8bbb2b && (uint32_t)(id >> 32) == 0xffffffff)
        ratio = FUN_00c8c5d0(index, &ratio);
    return !(0.0f < ratio);
}

// @ 0x01044b70
void cStarMap::UpdateDesiredCamera()
{
    if (GetUniverseContext() != 2)
        return;
    cApp* app = App();
    cCameraController* camera = app->GetCameraController();
    cPlanetView* view = camera->GetPlanetView();
    if (!view)
        return;
    cZoomTarget* target = (cZoomTarget*)view->FindObject(0x303154cb);
    if (!target)
        return;
    if (mRequestZoom) {
        float zoom = target->GetZoom();
        if (mZoomRequestHeight < zoom) {
            void* vtable = target->mpVtable;
            ((void (__thiscall*)(cZoomTarget*, int, float, float, int))
                ((void**)vtable)[0x3c / 4])(target, 1, 0.0f, 0.0f, 0);
            return;
        }
    }
    mRequestZoom = false;
}

// @ 0x01044bf0
bool __cdecl FUN_01044bf0(cCivData* civData)
{
    cSPSimulatorSpaceGame* simulator = (cSPSimulatorSpaceGame*)GetUFOSimulator();
    float maxZ = simulator->GetMaxZ();
    cPlayerCityData* inventory = (cPlayerCityData*)simulator->GetPlayerInventory();
    float* city = civData->GetCities();
    float dx = city[0] - inventory->mCityPosition.x;
    float dy = city[1] - inventory->mCityPosition.y;
    float dz = city[2] - inventory->mCityPosition.z;
    float dist = SqrtF(dy * dy + (dz * dz + dx * dx));
    return dist < maxZ;
}

// @ 0x01044c60
void cStarMap::Init()
{
    mVisualCount = 0;
    FUN_00feb060(&gBannerName);
    cProperty* property = 0;
    cPropertyManager* manager = PropertyManager();
    if (property) {
        property->mpVtable = 0;
    }
    manager->GetProperty(0xddb63e53, 0x2ae0c7e, &property);
    if (!property)
        return;
    cProperty* value = 0;
    if (property->Query(0x2ba603e, &value)) {
        if (value->mType == 9)
            mTravelTrailLength = *value->GetInt();
    }
    cProperty* zoom = 0;
    if (property->Query(0x54030ee, &zoom)) {
        if (zoom->mType == 0xd)
            mZoomRequestHeight = *zoom->GetFloat();
    }
    ((void (__thiscall*)(cProperty*))((void**)property->mpVtable)[1])(property);
}

// @ 0x01044d30
uint32_t* cStarMap::FindNode(int key)
{
    RBNode* end = (RBNode*)&mTree.mpEnd;
    RBNode* node = mTree.mpRoot;
    if (node != end) {
        do {
            if (key == (int)node->mKey)
                return &node->mValue;
            node = RBTreeIncrement(node);
        } while (node != end);
    }
    return 0;
}

// @ 0x01044d70
void cStarMap::SetNodeFlag(int key, char on)
{
    RBNode* end = (RBNode*)&mTree.mpEnd;
    RBNode* node = mTree.mpRoot;
    if (node != end) {
        do {
            if (key == (int)node->mKey) {
                if (on)
                    node->mFlags &= (uint8_t)~8u;
                else
                    node->mFlags |= 8;
                return;
            }
            node = RBTreeIncrement(node);
        } while (node != end);
    }
}

// @ 0x01044db0
void cStarMap::SetNodeFlag2(int key, char on)
{
    RBNode* end = (RBNode*)&mTree.mpEnd;
    RBNode* node = mTree.mpRoot;
    if (node != end) {
        do {
            if (key == (int)node->mKey) {
                if (on)
                    node->mFlags &= (uint8_t)~4u;
                else
                    node->mFlags |= 4;
                return;
            }
            node = RBTreeIncrement(node);
        } while (node != end);
    }
}

// @ 0x01044df0
void cStarMap::SyncEntryFlags(char enable)
{
    RBNode* end = (RBNode*)&mTree.mpEnd;
    for (RBNode* node = mTree.mpRoot; node != end; node = RBTreeIncrement(node)) {
        if ((node->mKey == 0x70930c64 || node->mKey == 0x166521a5)
            && ((bool)enable != ((node->mFlags & 8) != 8))) {
            uint32_t key = node->mKey;
            RBNode* other = mTree.mpRoot;
            while (other != end) {
                if (key == other->mKey) {
                    if (enable)
                        other->mFlags &= (uint8_t)~8u;
                    else
                        other->mFlags |= 8;
                    break;
                }
                other = RBTreeIncrement(other);
            }
        }
    }
}

// @ 0x01044e70
void __cdecl SerializeFlagGrid(cIOStream* stream, const cFlagGrid* grid)
{
    int rows = (((int)grid->mpLastRowEnd - (int)grid->mpRowBase) >> 2) - 1;
    int cols = ((int)grid->mpEnd - (int)grid->mpEndCap) >> 2;
    int width = ((int)grid->mpRowEnd - (int)grid->mpBegin) >> 2;
    uint32_t index = (uint32_t)(rows * 0x40 + cols + width);
    cSink* sink = stream->GetSink();
    void* out = sink->GetStream();
    WriteUint32(out, &index, 1, 0);

    int* it = grid->mpBegin;
    int* rowEnd = grid->mpRowEnd;
    int** rowBase = grid->mpRowBase;
    int* last = grid->mpEnd;
    while (it != last) {
        void* value = 0;
        if (*it)
            value = ((cFlagEntry*)*it)->GetName(&gEntryName);
        stream->WriteRef(value);
        ++it;
        if (it == rowEnd) {
            it = rowBase[1];
            ++rowBase;
            rowEnd = it + 0x40;
        }
    }
    ((void (__thiscall*)(cIOStream*))((void**)stream->mpVtable)[0x1c / 4])(stream);
}

// @ 0x01044f30
bool __cdecl ForEachFlagEntry(void* stream, const cFlagGrid* grid)
{
    int* rowEnd = grid->mpRowEnd;
    int* last = grid->mpEnd;
    int* it = grid->mpBegin;
    int** rowBase = grid->mpRowBase;
    while (it != last) {
        if (*it)
            ((cFlagEntry*)*it)->SerializeInto(stream);
        ++it;
        if (it == rowEnd) {
            it = rowBase[1];
            ++rowBase;
            rowEnd = it + 0x40;
        }
    }
    return true;
}

// @ 0x01044f80
void __thiscall cBitVector::InsertAtFront(uint32_t count, uint32_t value)
{
    uint32_t used = (uint32_t)(mpEnd - mpBegin);
    uint32_t newSize = used + 1 + count;
    uint32_t* dst;
    if (mCapacity > newSize * 2) {
        dst = mpData + (mCapacity - newSize) / 2 + (value ? count : 0);
        if (dst < mpBegin)
            MemCopy(dst, mpBegin, (used + 1) * 4);
        else
            MemMove(dst + (newSize - (used + 1)), mpBegin, (used + 1) * 4);
    } else {
        uint32_t capacity = (mCapacity > count ? mCapacity : count) + mCapacity + 2;
        uint32_t* data = (uint32_t*)MemAlloc(capacity * 4, &gAllocatorTag, 0, 0,
                                             &gAllocatorFile, 0xd1);
        dst = data + (mpBegin - mpData) + (value ? count : 0);
        if (mpData)
            MemCopy(dst, mpBegin, (used + 1) * 4);
        if (mpData)
            MemFreeArray(mpData);
        mpData = data;
        mCapacity = capacity;
    }
    mpBegin = dst;
    mFirstValue = *dst;
    mFirstCap = mFirstValue + 0x100;
    mpEnd = dst + used;
    mLastValue = *mpEnd;
    mLastCap = mLastValue + 0x100;
}

// @ 0x010450b0
SharedRefBlock* __stdcall AllocSharedRef(const SharedRefSrc* source)
{
    SharedRefBlock* block = (SharedRefBlock*)MemAlloc(0x28, &gAllocatorTag, 0, 0,
                                                      &gAllocatorFile, 0xd1);
    SharedRefData* target = &block->mData;
    if (target) {
        target->mValue = source->mValue;
        target->mpRef = source->mpRef;
        if (target->mpRef)
            target->mpRef->AddRef();
        target->mA = source->mA;
        target->mB = source->mB;
        target->mC = source->mC;
        target->mD = source->mD;
    }
    return block;
}

// @ 0x01045120
uint32_t cStarMap::FindValue(uint32_t bucket, int key)
{
    if (bucket == 0) {
        uint32_t* value = FindNode(key);
        if (value)
            return *value;
        return 0;
    }
    NodeRange range;
    mTree.equal_range(&range, &bucket);
    for (RBNode* node = range.mpFirst; node != range.mpSecond; node = RBTreeIncrement(node)) {
        if ((int)node->mKey == key)
            return node->mValue;
    }
    return 0;
}

// @ 0x01045190
uint32_t cStarMap::FindEntryByLongId(uint32_t key, uint32_t lo, uint32_t hi)
{
    NodeRange range;
    mTree.equal_range(&range, &key);
    RBNode* node = range.mpFirst;
    RBNode* end = range.mpSecond;
    if (node != end) {
        do {
            unsigned long long id = (unsigned long long)((cStarMapView*)node->mValue)->GetId();
            if ((uint32_t)id == lo && (uint32_t)(id >> 32) == hi)
                return node->mValue;
            node = RBTreeIncrement(node);
        } while (node != end);
    }
    return 0;
}

} // namespace SP
