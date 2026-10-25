// Slice s00c982a0: SP::cTribe::UpdateToolPosition (0x00c987b0, 2445 bytes).
// Signature from the asm: __thiscall, one stack int (tool type), ret 4, no return value.
//
// The action circle for the tool type is fetched from the map at +0x394, every slot
// object it currently holds is AddRef'd into a scratch hash map, the circle is rebuilt
// for the tool type (0xa / 0xc / 0xd branches, otherwise the generic tool definition
// path), the reservation grid at +0x558 is refreshed and finally the held objects are
// re-reserved into the rebuilt circle before the scratch map drops its references.
#include "types.h"
#include <math.h>

namespace SP {

class cGameData;

struct Vec3 { float x, y, z; };

struct cRefCounted {                    // vtable view of a reference-counted object
    virtual void AddRef();              // +0x00
    virtual void Release();             // +0x04
};

struct cSpatialView {                   // vtable view embedded at object +0x34 / +0x70
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vec3* GetPosition();          // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58();
    virtual const Vec3* GetFacing(Vec3* out);   // +0x5c
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70();
    virtual float GetHeight();                  // +0x74
};

struct cSpatialObject {                 // object whose spatial interface sits at +0x34
    char pad0[0x34];
    cSpatialView mSpatial;
};

struct cSpatialObject70 {               // object whose spatial interface sits at +0x70
    char pad0[0x70];
    cSpatialView mSpatial;
};

struct cPropertyValue {
    char pad0[0x12];
    uint16_t mType;                     // +0x12
    float* GetFloat();                  // 0x0041ea70
};

struct cPropertyHolder {                // property set returned by the property manager
    virtual void AddRef();              // +0x00
    virtual void Release();             // +0x04
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20();
    virtual char GetProperty(unsigned key, void** out);     // +0x24
};

struct cPropertyManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual char GetPropertyObject(unsigned keyA, unsigned keyB, void** out);  // +0x2c
};

struct cSpeciesProfile;

struct cReserveParams {                 // global singleton at 0x01581208
    float GetRadius(cSpeciesProfile* profile);      // 0x00ce6a40
};

extern "C" cReserveParams gReserveParams;                       // 0x01581208
extern "C" void*          gToolPriceTable;                      // 0x0158128c
extern "C" cPropertyManager* PropertyManager();                 // 0x0067de30
extern "C" int  GetTutorialToolPrice(void* table, unsigned key, int fallback);  // 0x004e1c30
extern "C" void FreeTribeBlock(void* block);                    // 0x00f47380

struct cToolDef {
    char pad0[0x3c];
    int mLayout;                        // +0x3c
};
extern "C" cToolDef* GetToolDef(int type);       // 0x00c9cec0

struct cActionSlot {                    // 0x18-byte element of cActionCircle's slot array
    uint8_t mbOccupied;                 // +0x00
    char pad1[3];
    void* mpObject;                     // +0x04
    void* mpUnk08;                      // +0x08
    Vec3 mPlacement;                    // +0x0c, handed back by cTribe::ReserveToolSlot
    void Clear();                       // 0x00afa0a0
    void Reserve(void* object);         // 0x00afa030
    void* GetObject();                  // 0x00fcc210
};

struct cActionCircle {
    char pad0[0x14];
    float mPosition[3];                 // 0x14, weighted-position input of the slot search
    char pad20[0x30];
    cActionSlot* mpSlotsBegin;          // 0x50
    cActionSlot* mpSlotsEnd;            // 0x54
    cActionSlot* At(int index);                                 // 0x00af9ff0
    void SetAtCenter(const Vec3* center, float radius, const Vec3* facing, float altitude);  // 0x00af9cf0
    void ConfigureSlots(float radius, float height, int layout);    // 0x00afdc00
    int FindClosestFreeSlotWeighted(int weight);                // 0x00afa7c0
};

struct cActionCircleMap {
    cActionCircle* FindOrAdd(int* key);                // 0x00c27d20
};

struct cReservationGrid {
    char mData[0x1374];                                 // opaque body, methods address into it
    void* GetReservedList();                            // 0x00cc7070, returns this + 0x984
    void RemoveReservedByID(void* entries, const void* id);      // 0x00cc86a0
    void AddReserved(void* entries, const Vec3* pos, float radius, const void* id);  // 0x00cc8350
};

struct cSlotRefNode {                   // node of the scratch slot->object hash map
    int mIndex;                         // +0x00
    void* mpObject;                     // +0x04
    cSlotRefNode* mpNext;               // +0x08
};

struct cSlotRefMap {
    void* mpPad00;                      // +0x00
    void** mpBuckets;                   // +0x04
    unsigned mBucketCount;              // +0x08
    char mPad0C[0x1c - 0x0c];
    void* mpFreeList;                   // +0x1c
    char mPad20[0x24 - 0x20];
    void* mpPoolBegin;                  // +0x24
    void* mpPoolEnd;                    // +0x28
    char mPad2C[0x30 - 0x2c];
    void* mpPoolCap;                    // +0x30
    char mState[0x180 - 0x34];
    void Construct(const void* a, const void* b);       // 0x00d2d5c0
    void** Find(int* key);                              // 0x00b76460
    void DestroyBuckets(void** buckets, unsigned count);        // 0x00a24480
};

struct cToolContext {                   // interface embedded in cGameData at +0xc0
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual int ComputeWeight(float* position, float radius);      // +0x2c
};

struct cGameData {                      // slice-local view: only +0xc0 is used here
    char pad0[0xc0];
    cToolContext mToolContext;          // 0xc0
};

class cTribe
{ public:
    void UpdateToolPosition(int toolType);                     // 0x00c987b0
    cSpatialObject* GetToolOfType(int toolType);               // 0x00c8f6e0
    void FindSpot(int spot, int index);                        // 0x00c98750
    void* ReserveToolSlot(int weight, int* outIndex, cGameData* gameData);   // 0x00c986d0
    void GetToolPositionAndFacing(int type, Vec3* outPos, Vec3* outFacing);  // 0x00c905c0

    char pad0[0x260];
    cSpatialObject* mpHut260;           // 0x260
    char pad264[0x368 - 0x264];
    cSpatialObject* mpHut368;           // 0x368
    char pad36c[0x394 - 0x36c];
    cActionCircleMap mActionCircleMap;  // 0x394
    char pad398[0x504 - 0x398];
    Vec3 mToolAnchor;                   // 0x504
    char pad510[0x558 - 0x510];
    cReservationGrid mReservationGrid558;   // 0x558, size 0x1374 -> ends at 0x18cc
    cSpeciesProfile* mpProfile18CC;     // 0x18cc
    char pad18d0[0x19c4 - 0x18d0];
    cSpatialObject70* mpTool19C4;       // 0x19c4
    cSpatialObject70* mpTool19C8;       // 0x19c8
    char pad19cc[0x19d0 - 0x19cc];
    cSpatialObject* mpTotem19D0;        // 0x19d0
};
}

// @ 0x00c987b0
// Rebuild the action circle for `toolType` and refresh its entry in the reservation grid.
void SP::cTribe::UpdateToolPosition(int toolType)
{
    cSpatialObject* tool = GetToolOfType(toolType);
    if (toolType == 0xd && mpHut260 == 0)
        return;
    if (tool == 0 && toolType != 0xd && toolType != 0xc)
        return;

    int key = toolType;
    cActionCircle* circle = mActionCircleMap.FindOrAdd(&key);

    // Snapshot every object the circle's slots currently hold so the rebuilt circle can
    // get them back. The retail code keeps this in a scratch hash map; the observable
    // effect is the AddRef/Release pairing plus the re-reserve below.
    cSlotRefMap refs;
    refs.Construct(&key, &key);

    int slotCount = (int)(circle->mpSlotsEnd - circle->mpSlotsBegin);
    for (int index = 0; index < slotCount; ++index) {
        void* object = (circle->mpSlotsBegin + index)->GetObject();
        if (object) {
            void** value = refs.Find(&index);
            void* old = *value;
            if (object != old) {
                static_cast<cRefCounted*>(object)->AddRef();
                *value = object;
                if (old)
                    static_cast<cRefCounted*>(old)->Release();
            }
        }
    }

    switch (toolType) {
    case 0xa: {
        // The tool simply faces the hut: anchor it a fixed five units along the line.
        const Vec3* hut = mpHut368->mSpatial.GetPosition();
        const Vec3* toolPos = tool->mSpatial.GetPosition();
        const void* id = (const void*)0xa;
        mReservationGrid558.RemoveReservedByID(mReservationGrid558.GetReservedList(), id);
        mReservationGrid558.AddReserved(mReservationGrid558.GetReservedList(), toolPos, 5.0f, id);
        float dx = hut->x - toolPos->x;
        float dy = hut->y - toolPos->y;
        float dz = hut->z - toolPos->z;
        float dist = sqrtf(dx * dx + dy * dy + dz * dz + 1e-8f);
        float scale = 1.0f / dist;
        mToolAnchor.x = toolPos->x + dx * scale * 5.0f;
        mToolAnchor.y = toolPos->y + dy * scale * 5.0f;
        mToolAnchor.z = toolPos->z + dz * scale * 5.0f;
        break;
    }
    case 0xc: {
        float radius = gReserveParams.GetRadius(mpProfile18CC);
        float height = mpHut368->mSpatial.GetHeight();
        Vec3 scratch;
        circle->SetAtCenter(mpHut368->mSpatial.GetPosition(), height + radius,
                            mpHut368->mSpatial.GetFacing(&scratch), 0.0f);
        circle->ConfigureSlots(radius, height,
                               GetTutorialToolPrice(gToolPriceTable, 0x570b5bab, 8));
        if (mpTool19C4) {
            float toolHeight = mpTool19C4->mSpatial.GetHeight();
            const Vec3* toolPos = mpTool19C4->mSpatial.GetPosition();
            float span = (toolHeight + radius) * (toolHeight + radius);
            for (int index = 0; ; ++index) {
                cActionSlot* slot = circle->At(index);
                if (!slot)
                    break;
                if (!slot->mbOccupied) {
                    float dx = slot->mPlacement.x - toolPos->x;
                    float dz = slot->mPlacement.z - toolPos->z;
                    float dy = slot->mPlacement.y - toolPos->y;
                    float dist2 = dx * dx + dz * dz + dy * dy;
                    if (dist2 < span)
                        slot->Reserve(mpTool19C4);
                }
            }
        }
        const void* id = (const void*)0xe;
        mReservationGrid558.RemoveReservedByID(mReservationGrid558.GetReservedList(), id);
        mReservationGrid558.AddReserved(mReservationGrid558.GetReservedList(),
                                        mpHut368->mSpatial.GetPosition(),
                                        height + 2.0f * radius, id);
        break;
    }
    case 0xd: {
        float radius = gReserveParams.GetRadius(mpProfile18CC);
        float height = mpHut260->mSpatial.GetHeight() + 0.4f;
        if (mpTotem19D0) {
            height = mpTotem19D0->mSpatial.GetHeight() + 0.4f;
            cPropertyHolder* holder = 0;
            cPropertyManager* manager = PropertyManager();
            if (holder) {
                holder = 0;
                holder->Release();
            }
            if (manager->GetPropertyObject(0x93256b8, 0xf37c24e6, (void**)&holder)) {
                if (holder) {
                    void* property = 0;
                    if (holder->GetProperty(0x579ef6c, &property)) {
                        cPropertyValue* value = static_cast<cPropertyValue*>(property);
                        if (value->mType == 0xd)
                            height = 0.4f + *value->GetFloat();
                    }
                }
            }
            if (holder)
                holder->Release();
        }
        const Vec3* hutPos = mpHut260->mSpatial.GetPosition();
        float slotSpan = 2.0f * radius;
        float reservedSpan = slotSpan + height;
        const Vec3* center = mpTotem19D0 ? mpTotem19D0->mSpatial.GetPosition() : hutPos;
        Vec3 scratch;
        const Vec3* hutFacing = mpHut260->mSpatial.GetFacing(&scratch);
        Vec3 negFacing;
        negFacing.x = -hutFacing->x;
        negFacing.y = -hutFacing->y;
        negFacing.z = -hutFacing->z;
        circle->SetAtCenter(center, height + radius, &negFacing, 0.0f);
        circle->ConfigureSlots(radius, height, 0);
        if (mpTotem19D0) {
            for (int index = 0; ; ++index) {
                cActionSlot* slot = circle->At(index);
                if (!slot)
                    break;
                if (slot->GetObject() == mpHut260)
                    slot->Clear();
                if (!slot->mbOccupied) {
                    float dx = slot->mPlacement.x - hutPos->x;
                    float dz = slot->mPlacement.z - hutPos->z;
                    float dy = slot->mPlacement.y - hutPos->y;
                    float dot = dx * negFacing.x + dz * negFacing.z + dy * negFacing.y;
                    if (!(dot > 0.0f)) {
                        float dist2 = dx * dx + dz * dz + dy * dy;
                        if (dist2 < slotSpan)
                            slot->Reserve(mpHut260);
                    }
                }
            }
        }
        const void* id = (const void*)0xd;
        mReservationGrid558.RemoveReservedByID(mReservationGrid558.GetReservedList(), id);
        mReservationGrid558.AddReserved(mReservationGrid558.GetReservedList(), hutPos,
                                        reservedSpan, id);
        Vec3 toolPos;
        Vec3 toolFacing;
        GetToolPositionAndFacing(0xd, &toolPos, &toolFacing);
        const Vec3* anchor = mpHut260->mSpatial.GetPosition();
        float dx = toolPos.x - anchor->x;
        float dy = toolPos.y - anchor->y;
        float dz = toolPos.z - anchor->z;
        float dist = sqrtf(dx * dx + dy * dy + dz * dz);
        float span = slotSpan + dist * 0.5f;
        float scale = 1.0f / (dist + 1.52587890625e-05f);
        Vec3 anchorPos;
        anchorPos.x = anchor->x + dx * scale * span;
        anchorPos.y = anchor->y + dy * scale * span;
        anchorPos.z = anchor->z + dz * scale * span;
        mReservationGrid558.AddReserved(mReservationGrid558.GetReservedList(), &anchorPos,
                                        span, id);
        break;
    }
    default: {
        cToolDef* def = GetToolDef(toolType);
        float radius = gReserveParams.GetRadius(mpProfile18CC);
        float height = tool->mSpatial.GetHeight();
        Vec3 scratch;
        circle->SetAtCenter(tool->mSpatial.GetPosition(), radius + height,
                            tool->mSpatial.GetFacing(&scratch), 0.0f);
        circle->ConfigureSlots(radius, height, def->mLayout);
        const void* id = (const void*)toolType;
        mReservationGrid558.RemoveReservedByID(mReservationGrid558.GetReservedList(), id);
        mReservationGrid558.AddReserved(mReservationGrid558.GetReservedList(),
                                        tool->mSpatial.GetPosition(),
                                        2.0f * radius + height, id);
        break;
    }
    }

    // Walk the scratch map (bucket chains, then next non-empty bucket) and give each held
    // object back to the rebuilt circle before the map itself drops its references.
    void** buckets = refs.mpBuckets;
    cSlotRefNode* node = reinterpret_cast<cSlotRefNode*>(buckets[0]);
    void** bucket = buckets;
    if (!node) {
        bucket = buckets + 1;
        while (*bucket == 0)
            ++bucket;
        node = reinterpret_cast<cSlotRefNode*>(*bucket);
    }
    cSlotRefNode* end = reinterpret_cast<cSlotRefNode*>(buckets[refs.mBucketCount]);
    while (node != end) {
        cActionSlot* slot = circle->At(node->mIndex);
        if (slot)
            slot->Reserve(node->mpObject);
        node = node->mpNext;
        if (!node) {
            do {
                node = reinterpret_cast<cSlotRefNode*>(bucket[1]);
                ++bucket;
            } while (!node);
        }
    }
    refs.DestroyBuckets(buckets, refs.mBucketCount);
    unsigned bucketCount = refs.mBucketCount;
    refs.mBucketCount = 0;
    if (bucketCount > 1) {
        void* block = buckets;
        if (block != refs.mpPoolCap) {
            if ((uintptr_t)block < (uintptr_t)refs.mpPoolBegin ||
                (uintptr_t)block >= (uintptr_t)refs.mpPoolEnd) {
                FreeTribeBlock(block);
            } else {
                *reinterpret_cast<void**>(block) = refs.mpFreeList;
            }
        }
    }
}

// @ 0x00c98750
// Clear the slot at `index` of the action circle keyed by `spot` when the index is in range.
void SP::cTribe::FindSpot(int spot, int index)
{
    int key = spot;
    cActionCircle* circle = mActionCircleMap.FindOrAdd(&key);
    if (index >= 0 && index < (int)(circle->mpSlotsEnd - circle->mpSlotsBegin)) {
        cActionSlot* slot = circle->mpSlotsBegin + index;
        if (slot)
            slot->Clear();
    }
}

// @ 0x00c986d0
// Reserve the best free action circle slot for `gameData` and publish its index through outIndex.
void* SP::cTribe::ReserveToolSlot(int weight, int* outIndex, cGameData* gameData)
{
    int key = weight;
    cActionCircle* circle = mActionCircleMap.FindOrAdd(&key);
    cToolContext* context = &gameData->mToolContext;
    int score = context->ComputeWeight(circle->mPosition, 0.8f);
    int index = circle->FindClosestFreeSlotWeighted(score);
    *outIndex = index;
    if (index >= 0) {
        cActionSlot* slot = circle->mpSlotsBegin + index;
        if (slot) {
            slot->Reserve(gameData);
            return &slot->mPlacement;
        }
    }
    return circle->mPosition;
}
