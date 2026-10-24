// Slice s00d178a0: the level editor's object-manipulation message handler
// (cGameEditInputStrategy::DoObjectManipulation) together with the three eastl heap-sort
// helpers it is grouped with in the batch (the by-value comparator is
// SP::cPropertyListNameSort, a 0x28-byte functor holding a group id, the resource manager
// and the two file names it resolves during a comparison).
//
//   0x00d178a0  SP::cGameEditInputStrategy::DoObjectManipulation   thiscall, ret 8
//   0x00d18000  cPropertyListNameSort::cPropertyListNameSort(const&) copy ctor, ret 4
//   0x00d180c0  AdjustHeapHole   cdecl (first, top, len, hole, value, compare by value)
//   0x00d18180  AdjustHeap       cdecl (first, last, compare by value)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"

extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
#pragma intrinsic(memcpy)

extern void operator_delete__(void* p);            // 0x00f47380

// ------------------------------------------------------------------ value types
struct Vector3    { float x, y, z; };
struct Quaternion { float x, y, z, w; };

// ------------------------------------------------------------------ EASTL strings
namespace eastl {
extern wchar_t gEmptyString16[];                   // 0x01667bac

class allocator {
public:
    void deallocate(void* p, unsigned int) { operator_delete__(p); }
};

template <class T> struct basic_string {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator mAllocator;

    void AllocateSelf(unsigned int n);             // 0x00429760 (out of line)

    basic_string(const basic_string& x) : mpBegin(0), mpEnd(0), mpCapacity(0) {
        RangeInitialize(x.mpBegin, x.mpEnd);
    }
    ~basic_string() { DeallocateSelf(); }

    void RangeInitialize(const T* pBegin, const T* pEnd) {
        const int n = (int)(pEnd - pBegin);
        AllocateSelf(n + 1);
        T* p = mpBegin;
        memcpy(p, pBegin, n * sizeof(T));
        mpEnd = p + n;
        *mpEnd = 0;
    }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (unsigned int)(mpCapacity - mpBegin));
    }
    void DoFree(T* p, unsigned int n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
};
typedef basic_string<wchar_t> string16;
}

// ------------------------------------------------------------------ properties
// The object a property list hands back for an index; GetValue() is always inlined.
struct Property {
    union {
        struct { void* mpData; uint32_t mnItemSize; uint32_t mnItemCount; };
        uint32_t mValue[4];
    };
    unsigned short mnFlags;                        // +0x10  (0x30 mask => pointer valued)
    unsigned short mnType;                         // +0x12
    void* GetValue() { return (mnFlags & 0x30) ? mpData : (mnType != 0 ? (void*)this : 0); }
};

// ------------------------------------------------------------------ resource manager key
namespace EA { namespace ResourceMan {
class IResourceManager;
} }

// ------------------------------------------------------------------ property list name sort
// The comparator eastl copies by value into every heap helper; it resolves both instance ids
// to file names through the resource manager and then compares the two names.
struct cPropertyListNameSort {
    uint32_t mGroupID;                             // +0x00
    EA::ResourceMan::IResourceManager* mpResMan;   // +0x04
    eastl::string16 mNameA;                        // +0x08
    eastl::string16 mNameB;                        // +0x18

    cPropertyListNameSort(const cPropertyListNameSort& x);      // 0x00d18000
    bool operator()(uint32_t a, uint32_t b) const;              // 0x00d16760
};

void AdjustHeapHole(uint32_t* first, int topIndex, int len, int holeIndex, uint32_t value,
                    cPropertyListNameSort compare);              // 0x00d180c0
void SiftUp(uint32_t* first, int topIndex, int holeIndex, uint32_t value,
            cPropertyListNameSort compare);                      // 0x00d16eb0
void AdjustHeap(uint32_t* first, uint32_t* last, cPropertyListNameSort compare);  // 0x00d18180

// ------------------------------------------------------------------ UTFWin object
class cUiObject;
class cPropertyList;

class cUiObject {
public:
    virtual void v00();                            // 0x00
    virtual void v04();                            // 0x04
    virtual void v08();                            // 0x08
    virtual cUiObject* v0c(uint32_t id);           // 0x0c  child by id
    virtual cPropertyList* v10();                  // 0x10  property list
    virtual void v14();                            // 0x14
    virtual void v18();                            // 0x18
    virtual Property* v1c(uint32_t index);         // 0x1c
    virtual uint32_t v20();                        // 0x20  class id
    virtual void v24();                            // 0x24
    virtual void v28();                            // 0x28
    virtual void v2c();                            // 0x2c
    virtual void v30();                            // 0x30
    virtual void v34();                            // 0x34
    virtual uint32_t v38();                        // 0x38
    virtual void v3c();                            // 0x3c
    virtual void v40();                            // 0x40
    virtual void v44();                            // 0x44
    virtual void v48();                            // 0x48
    virtual void v4c();                            // 0x4c
    virtual void v50();                            // 0x50
    virtual void v54(cUiObject* obj, int flag);    // 0x54  bind the manipulated object
    virtual cUiObject* v58();                      // 0x58  bound object
    virtual void v5c();                            // 0x5c
    virtual void v60();                            // 0x60
    virtual void v64();                            // 0x64
    virtual void v68();                            // 0x68
    virtual void v6c();                            // 0x6c
    virtual void v70();                            // 0x70
    virtual void v74();                            // 0x74
    virtual void v78();                            // 0x78
    virtual void v7c();                            // 0x7c
    virtual void v80();                            // 0x80
    virtual void v84();                            // 0x84
    virtual void v88();                            // 0x88
    virtual void v8c();                            // 0x8c
    virtual void v90();                            // 0x90
    virtual void v94();                            // 0x94
    virtual void v98();                            // 0x98
    virtual void v9c();                            // 0x9c
    virtual void va0();                            // 0xa0
    virtual void va4();                            // 0xa4
    virtual void va8();                            // 0xa8
    virtual void vac();                            // 0xac
    virtual void vb0();                            // 0xb0
    virtual void vb4();                            // 0xb4
    virtual cUiObject* vb8(uint32_t id);           // 0xb8  handler for a script id
    virtual void vbc();                            // 0xbc
};

class cPropertyList {
public:
    virtual void p00();                            // 0x00
    virtual void p04();                            // 0x04
    virtual void p08();                            // 0x08
    virtual void p0c();                            // 0x0c
    virtual void p10();                            // 0x10
    virtual void p14();                            // 0x14
    virtual void p18();                            // 0x18
    virtual Property* v1c(uint32_t index);         // 0x1c
};

// A spatial object: v2c = position, v38 = set position, v3c = set rotation string/quaternion,
// v50 = "movable", v6c = notify.
class cSpatial {
public:
    virtual void s00();                            // 0x00
    virtual void s04();                            // 0x04
    virtual void s08();                            // 0x08
    virtual void s0c();                            // 0x0c
    virtual void s10();                            // 0x10
    virtual void s14();                            // 0x14
    virtual void s18();                            // 0x18
    virtual void s1c();                            // 0x1c
    virtual void s20();                            // 0x20
    virtual void s24();                            // 0x24
    virtual void s28();                            // 0x28
    virtual void* v2c();                           // 0x2c  position
    virtual void* v30();                           // 0x30  rotation
    virtual void s34();                            // 0x34
    virtual void v38(void* position);              // 0x38  set position
    virtual void v3c(void* rotation);              // 0x3c  set rotation
    virtual void s40();                            // 0x40
    virtual void s44();                            // 0x44
    virtual void s48();                            // 0x48
    virtual void s4c();                            // 0x4c
    virtual bool v50();                            // 0x50  movable / editable
};

// The object cUiObject::vb8 hands back for a marker id: an embedded spatial sub-object at
// +0x34 and the gameplay handler pointer at +0x1a4.
class cMarkerInfo {
public:
    char      mPad00[0x34];
    cSpatial  mSub34;                              // +0x34
    char      mPad38[0x1a4 - 0x38];
    cUiObject* mpField1a4;                         // +0x1a4
};

// A creature of a herd: its own vtable, the spatial sub-object at +0xc0.
class cHerdMember {
public:
    virtual void h00();                            // 0x00
    virtual void h04();                            // 0x04
    virtual void h08();                            // 0x08
    virtual void h0c();                            // 0x0c
    virtual void h10();                            // 0x10
    virtual void h14();                            // 0x14
    virtual void h18();                            // 0x18
    virtual void h1c();                            // 0x1c
    virtual void h20();                            // 0x20
    virtual void h24();                            // 0x24
    virtual void h28();                            // 0x28
    virtual void h2c();                            // 0x2c
    virtual void h30();                            // 0x30
    virtual void h34();                            // 0x34
    virtual void h38();                            // 0x38
    virtual void h3c();                            // 0x3c
    virtual void h40();                            // 0x40
    virtual void h44();                            // 0x44
    virtual void h48();                            // 0x48
    virtual void h4c();                            // 0x4c
    virtual void h50();                            // 0x50
    virtual void h54();                            // 0x54
    virtual void h58();                            // 0x58
    virtual void h5c();                            // 0x5c
    virtual void h60();                            // 0x60
    virtual void h64();                            // 0x64
    virtual void h68();                            // 0x68
    virtual void v6c(int value);                   // 0x6c
    char      mPad04[0xc0 - 0x70];
    cSpatial  mSpatial;                            // +0xc0
};

class cHerd {
public:
    char          mPad00[0x40];
    cHerdMember** mMembersBegin;                   // +0x40
    cHerdMember** mMembersEnd;                     // +0x44
    char          mPad48[0x160 - 0x48];
    uint32_t      mField160;                       // +0x160
    void SetPosition(Vector3* position);           // 0x00c6ba20
};

// ------------------------------------------------------------------ ref-counted slot
struct AutoRefCount {
    cUiObject* mpObject;
    void Assign(cUiObject* value);                 // 0x00c70110
};

// ------------------------------------------------------------------ engine entry points
class cPlanetModel {
public:
    Vector3*    DirectionToSurfacePosition(Vector3* out, const Vector3* direction);   // 0xb815a0
    Quaternion* BuildSurfaceOrientation(Quaternion* out, const Vector3* position);   // 0xb7f190
    Quaternion* BuildSurfaceOrientation2(Quaternion* out, const Vector3* position,
                                         const Vector3* up);                         // 0xb7f250
    Vector3*    GetNormalAt(Vector3* out, const Vector3* position);                  // 0xb7e3b0
};

// The camera / reference point the editor manipulates around.
class IReferencePoint {
public:
    virtual void r00();                            // 0x00
    virtual void r04();                            // 0x04
    virtual void r08();                            // 0x08
    virtual void r0c();                            // 0x0c
    virtual void r10();                            // 0x10
    virtual void r14();                            // 0x14
    virtual void r18();                            // 0x18
    virtual void r1c();                            // 0x1c
    virtual void r20();                            // 0x20
    virtual void r24();                            // 0x24
    virtual void r28();                            // 0x28
    virtual void r2c();                            // 0x2c
    virtual void r30();                            // 0x30
    virtual void r34();                            // 0x34
    virtual Vector3 GetPos(int flag, Vector3 offset);   // 0x38
};

class cTimer {
public:
    uint32_t mPad[8];
    void Restart();                                // 0x00bc3130
};

class cGameNounManager {
public:
    void RemoveNoun(cUiObject* noun);              // 0x00b225d0
    cUiObject* CreateRotationRing();               // 0x00d0a610
};

// The edit mode strategy singleton: the current selection lives in the vector at +0x40.
class cGameEditModeStrategy {
public:
    char         mPad00[0x40];
    cUiObject**  mSelectedBegin;                   // +0x40
    cUiObject**  mSelectedEnd;                     // +0x44
};

// ------------------------------------------------------------------ SP::cGameEditInputStrategy
class cGameEditInputStrategy {
public:
    char         mPad00[0x4c];
    AutoRefCount mpSelectedObject;                 // +0x4c  the object being manipulated
    AutoRefCount mpField50;                        // +0x50
    cUiObject*   mpSelectedObjectManipulator;      // +0x54
    cTimer       mHoverTimer;                      // +0x58
    char         mPad5c[0xc4 - 0x78];
    Vector3      mFacing;                          // +0xc4
    Vector3      mFrameD0;                         // +0xd0

    void DoObjectManipulation(uint32_t action, cUiObject* message);   // 0x00d178a0
    void FUN_00d15440(Vector3* target);                               // 0x00d15440
    void FUN_00d16f40(Vector3* target);                               // 0x00d16f40
};

// ------------------------------------------------------------------ externals
extern Vector3    g_v169dc28;                      // 0x0169dc28  reference point offset
extern uint8_t    g_169dc20;                       // 0x0169dc20  "herd needs an update" flag
extern Vector3    g_v169dc88;                      // 0x0169dc88  world up
extern float      g_f169dc94;                      // 0x0169dc94  two pi
extern float      g_f1470f1c;                      // 0x01470f1c  2.0f
extern float      g_f1582664;                      // 0x01582664  half turn
extern Vector3    g_v1582668;                      // 0x01582668  spin axis
extern Vector3    g_v1582674;                      // 0x01582674  spin axis

extern IReferencePoint* FUN_00b3d240();            // 0x00b3d240
extern cPlanetModel*    PlanetModel();             // 0x00b3d350
extern cGameNounManager* NounManager();            // 0x00b3d300
extern cGameEditModeStrategy* GetEditSelection();  // 0x00d1bf00
extern cUiObject* RotateObject(AutoRefCount* object);                  // 0x00d15330
extern cUiObject* FUN_00ad7360(cUiObject** slot);                      // 0x00ad7360
extern void*      FUN_00ac80d0(cUiObject* object, uint32_t classId);   // 0x00ac80d0
extern Vector3*   Vector3_Normalize(Vector3* out, const Vector3* in);  // 0x00436ce0
extern Vector3*   FUN_0059aed0(Vector3* out, const Vector3* v, const Quaternion* q);  // 0x0059aed0
extern Quaternion* FUN_0059b060(Quaternion* out, const Vector3* axis, float angle);   // 0x0059b060
extern void*      FUN_007dcb00(void* out, const Quaternion* a, const Quaternion* b);  // 0x007dcb00
extern void       OrthogonalVector(Vector3* out, const Vector3* in);                  // 0x006985b0
extern Quaternion* QuaternionFromFacingAndUp(Quaternion* out, const Vector3* facing,
                                             const Vector3* up);                      // 0x0069b600

// ------------------------------------------------------------------ heap helpers

// @ 0x00D18000  cPropertyListNameSort::cPropertyListNameSort
cPropertyListNameSort::cPropertyListNameSort(const cPropertyListNameSort& x)
    : mGroupID(x.mGroupID), mpResMan(x.mpResMan), mNameA(x.mNameA), mNameB(x.mNameB)
{
}

// @ 0x00D180C0  AdjustHeapHole
// Walks the hole down the heap, always into the smaller of the two children, then sifts the
// saved value back up into it.
void AdjustHeapHole(uint32_t* first, int topIndex, int len, int holeIndex, uint32_t value,
                    cPropertyListNameSort compare)
{
    int secondChild = 2 * holeIndex + 2;
    while (secondChild < len) {
        if (compare(first[secondChild], first[secondChild - 1]))
            --secondChild;
        first[holeIndex] = first[secondChild];
        holeIndex = secondChild;
        secondChild = 2 * (secondChild + 1);
    }
    if (secondChild == len) {
        first[holeIndex] = first[secondChild - 1];
        holeIndex = secondChild - 1;
    }
    SiftUp(first, topIndex, holeIndex, value, compare);
}

// @ 0x00D18180  AdjustHeap
// Moves the last element to the front and repairs the heap below it.
void AdjustHeap(uint32_t* first, uint32_t* last, cPropertyListNameSort compare)
{
    uint32_t value = *(last - 1);
    *(last - 1) = *first;
    AdjustHeapHole(first, 0, (int)(last - first) - 1, 0, value, compare);
}

// @ 0x00D178A0  SP::cGameEditInputStrategy::DoObjectManipulation
// Handles the four "object manipulation" messages: pick up / drop the current object, rotate
// the selection around the reference point, and push the manipulation position into the ring
// object and the objects around it.
void cGameEditInputStrategy::DoObjectManipulation(uint32_t action, cUiObject* message)
{
    cPropertyList* list = message->v10();
    Property* valueProperty = list->v1c(0);
    cUiObject* values = (cUiObject*)valueProperty->GetValue();
    cUiObject* targetRef = 0;                      // 0x17f243b
    cUiObject* sourceRef = 0;                      // 0x1186577
    if (values != 0) {
        targetRef = values->v0c(0x17f243b);
        sourceRef = values->v0c(0x1186577);
    }
    uint32_t mode = list->v1c(1)->mValue[0];

    switch (action) {
    case 0x1271936:
        mpSelectedObject.Assign(sourceRef);
        return;

    case 0x1270f6b: {
        if (mpSelectedObject.mpObject == 0)
            return;

        Vector3 refPos = FUN_00b3d240()->GetPos(0, g_v169dc28);
        cUiObject* marker = RotateObject(&mpSelectedObject);
        if (marker == 0)
            return;

        cMarkerInfo* markerInfo = (cMarkerInfo*)marker;
        Vector3* ringPos = (Vector3*)markerInfo->mSub34.v2c();
        Vector3 delta;
        delta.x = refPos.x - ringPos->x;
        delta.y = refPos.y - ringPos->y;
        delta.z = refPos.z - ringPos->z;

        cPlanetModel* pm = PlanetModel();
        cGameEditModeStrategy* selection = GetEditSelection();
        for (cUiObject** it = selection->mSelectedBegin; it != selection->mSelectedEnd; ++it) {
            cUiObject* noun = *it;
            if (noun == 0)
                continue;
            cMarkerInfo* info = (cMarkerInfo*)noun->vb8(0x36be278);
            if (info == 0)
                continue;
            cSpatial* sub = &info->mSub34;
            if (!sub->v50())
                continue;

            Vector3* cur = (Vector3*)sub->v2c();
            Vector3 target;
            target.x = cur->x + delta.x;
            target.y = cur->y + delta.y;
            target.z = cur->z + delta.z;

            Vector3 placed;
            Vector3* position = pm->DirectionToSurfacePosition(&placed, &target);
            sub->v38(position);
            Quaternion orient;
            Quaternion* rotation = pm->BuildSurfaceOrientation(&orient, (Vector3*)sub->v2c());
            sub->v3c(rotation);

            if (mode != 0x29b || info->mpField1a4 == 0)
                continue;

            cSpatial* handler = (cSpatial*)FUN_00ad7360(&info->mpField1a4);
            if (handler == 0) {
                if (info->mpField1a4->v20() != 0x1be418e)
                    continue;
                cHerd* herd = (cHerd*)FUN_00ac80d0(info->mpField1a4, 0x1be418e);
                if (herd == 0)
                    continue;

                if (herd->mField160 != 0)
                    g_169dc20 = 1;
                herd->SetPosition(&placed);

                Vector3 normal;
                Vector3_Normalize(&normal, &placed);
                Quaternion spinA;
                Quaternion spinB;
                FUN_0059b060(&spinA, &g_v1582668, g_f1582664);
                FUN_0059b060(&spinB, &g_v1582674, g_f1582664);
                Quaternion matrix;
                FUN_007dcb00(&matrix, &spinA, &spinB);
                Vector3 facing;
                FUN_0059aed0(&facing, &placed, &matrix);
                Quaternion frame;
                pm->BuildSurfaceOrientation2(&frame, &placed, &facing);
                Vector3 up;
                FUN_0059aed0(&up, &g_v169dc88, &frame);
                Vector3 upDir;
                Vector3_Normalize(&upDir, &up);

                int index = 1;
                int ring = 1;
                int step = 6;
                for (cHerdMember** member = herd->mMembersBegin;
                     member != herd->mMembersEnd; ++member) {
                    cHerdMember* creature = *member;
                    if (step <= index) {
                        ++ring;
                        step += 6;
                        index = 0;
                    }
                    float radius = (float)ring * g_f1470f1c;
                    float angle = ((float)index * g_f169dc94) / (float)step;
                    Quaternion swing;
                    FUN_0059b060(&swing, &upDir, angle);
                    Vector3 offset;
                    FUN_0059aed0(&offset, &upDir, &swing);
                    Vector3 spot;
                    spot.x = offset.x * radius + placed.x;
                    spot.y = offset.y * radius + placed.y;
                    spot.z = offset.z * radius + placed.z;
                    Vector3 home;
                    creature->mSpatial.v38(pm->DirectionToSurfacePosition(&home, &spot));
                    Quaternion creatureFrame;
                    creature->mSpatial.v3c(pm->BuildSurfaceOrientation(
                        &creatureFrame, (Vector3*)creature->mSpatial.v2c()));
                    creature->v6c(100);
                    ++index;
                }
            } else {
                handler->v38(position);
                Vector3 normal;
                pm->GetNormalAt(&normal, position);
                Vector3 tangent;
                OrthogonalVector(&tangent, &normal);
                Quaternion rotation2;
                Quaternion* q = QuaternionFromFacingAndUp(&rotation2, &tangent, &normal);
                handler->v3c(q);
            }
        }
        return;
    }

    case 0x127433b: {
        if (sourceRef == 0)
            return;
        mpField50.Assign(sourceRef);
        if (targetRef->v38() == 0x2ee8eeb)
            return;
        if (targetRef->v38() == 0x7292112)
            return;
        if (targetRef->v20() != 0x36be27e)
            return;
        mHoverTimer.Restart();
        if (mpSelectedObjectManipulator != 0) {
            if (mpSelectedObjectManipulator->v58() == sourceRef)
                return;
            NounManager()->RemoveNoun(mpSelectedObjectManipulator);
        }
        mpSelectedObjectManipulator = NounManager()->CreateRotationRing();
        mpSelectedObjectManipulator->v54(sourceRef, 0);
        return;
    }

    case 0x127e78c: {
        Vector3 pos = FUN_00b3d240()->GetPos(0, g_v169dc28);
        FUN_00d16f40(&pos);
        return;
    }

    case 0x127ec9d: {
        Vector3 pos = FUN_00b3d240()->GetPos(0, g_v169dc28);
        FUN_00d15440(&pos);
        return;
    }
    }
}
