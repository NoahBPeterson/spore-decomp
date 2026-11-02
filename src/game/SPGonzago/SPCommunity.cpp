// src/game/SPGonzago/SPCommunity.cpp -- migrated from slice(s) s00c015e0, s00bffad0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCommunity.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cLaneInfo.h"
#include "cSPVector3.h"
#include "SP/cActionCircle.h"
#include "SP/cCity.h"
#include "SP/cCommunity.h"
#include "SP/cEmptyBubble.h"
#include "SP/cVarListSerializer.h"
#include <math.h>
#include <stdlib.h>
#include <new>

// unnamed retail callees and globals (address in the comment)
extern uint32_t g_168d228[8];           // 0x0168d228  cached four-byte ids, seven entries used
extern "C" void EA_IO_WriteUint32(void* stream, const uint32_t& value, int count, int flags); // 0x0093aa70
extern char DAT_015710b8;               // 0x015710b8  cVarList descriptor passed to the serializer

// ---- items of slice s00bffad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VT(obj, off) ((*(void***)(obj))[(off) / 4])
typedef bool     (__thiscall *FnBool)(void*);
typedef void     (__thiscall *FnVoid_Rel)(void*);
extern uint32_t g_168d228[8];           // 0x0168d228  cached four-byte ids, seven entries used
void* SP_PropertyManager();             // 0x0067de30
extern "C" void EA_IO_WriteUint32(void* stream, const uint32_t& value, int count, int flags); // 0x0093aa70
extern char DAT_015710b8;               // 0x015710b8  cVarList descriptor passed to the serializer
typedef void* (__thiscall *FnVp)(void*);
typedef bool  (__thiscall *FnBool2)(void*, uint32_t, void**);
typedef bool  (__thiscall *FnGetProps)(void*, uint32_t, int, void**);
struct cProperty {
    uint8_t  mPad0[0xc];                // +0 is the vtable pointer
    uint16_t mFlags;                    // 0x10
    uint16_t mType;                     // 0x12
    virtual int AddRef();
    virtual int Release();              // vtable slot 1 (+4)
    const char* GetString8();           // 0x0041e990
};
template <class T>
struct AutoRef {
    T* mp;
    AutoRef() : mp(0) {}
    void Reset() { if (mp) { T* p = mp; mp = 0; p->Release(); } }
    void** AsPPTypeParam() { Reset(); return (void**)&mp; }
    ~AutoRef() { if (mp) mp->Release(); }
};
struct cVarListSerializer {
    uint8_t mData[0xa14];
    cVarListSerializer(void* object, const void* descriptor, uint32_t classId);
    void Serialize(void* stream);
};
struct Elem20 {
    float f0, f1, f2, f3, f4, f5, f6;
    uint32_t u;
};
// ---- items of slice s00bffad0 end

// ---- items of slice s00c015e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 { float x, y, z; };
struct PointVec {
    Vec3* mpBegin; Vec3* mpEnd; Vec3* mpCap;
    PointVec() { mpBegin = 0; mpEnd = 0; mpCap = 0; }
    ~PointVec() { if (mpBegin) free(mpBegin); }
};
struct Zone {
    uint32_t pad[0x258 / 4];
    float rMin;     // +0x258
    float rMax;     // +0x25c
    void FillPoints(PointVec* v);
};
struct IRefCounted {                  // vtable: +0x00 v0, +0x04 Release
    virtual void v0();
    virtual void Release();
};
struct IntIdxVec {                    // eastl::vector<unsigned int>
    int* mpBegin;
    int* mpEnd;
    int* mpCap;
    void DoInsertValueI(int* pos, const int& value);            // 0x004558a0
};
struct SpatialRefVec {                // vector<AutoRefCount<cSpatialObject>>
    void* mpBegin;
    void* mpEnd;
    void* mpCap;
    void erase(void* first, void* last);                        // 0x00b48e40
};
struct LogReporterRefVec {            // vector<AutoRefCount<ILogReporter>>
    void* mpBegin;
    void* mpEnd;
    void* mpCap;
    void erase(void* first, void* last);                        // 0x00e25bd0
};
struct ILaneObject {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
    virtual Zone* GetZone();                                   // slot 27 (+0x6c)
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
    virtual void v32();                                        // slot 32 (+0x80)
    virtual void v33();
    virtual void v34();                                        // slot 34 (+0x88)

    uint32_t pad04[(0x2c - 0x04) / 4];                         // +0x04
    IRefCounted* mpAt2c;                                       // +0x2c
    uint32_t pad30[(0x50 - 0x30) / 4];                         // +0x30
    float mInnerRadius;                                        // +0x50  zone rMin
    float mOuterRadius;                                        // +0x54  zone rMax
    uint32_t pad58[(0x6c - 0x58) / 4];                         // +0x58
    uint8_t mZoneValid;                                        // +0x6c
    uint32_t pad70[(0xd0 - 0x70) / 4];                         // +0x70
    SpatialRefVec mObjects;                                    // +0xd0
    uint32_t padDc[(0xe4 - 0xdc) / 4];                         // +0xdc
    LogReporterRefVec mReporters;                              // +0xe4
    uint32_t padF0[(0x11c - 0xf0) / 4];                        // +0xf0
    IRefCounted* mpAt11c;                                      // +0x11c

    void FUN_00c014c0();                                       // 0x00c014c0
    void UpdateZone(bool force);                               // 0x00c01e20
    void ClearLanes();                                         // 0x00c01e80
};
struct IStreamHolder {                // object returned by ISerializable::Open()
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
    virtual void* GetStream();                                 // slot 6 (+0x18)
};
struct ISerializableObject {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
    virtual void Close();                                      // slot 7 (+0x1c)
    virtual IStreamHolder* Open();                             // slot 8 (+0x20)
};
void ReadInt32(void* stream, uint32_t* value, int count, int flags);  // 0x0093a780
void FreeAllocBlock(void* block);                                     // 0x00f47380
struct cVarListSerializer_s00c0_15e0 {
    uint8_t mStorage[0xa14];
    void Construct(void* record, uint32_t key, uint32_t type);  // 0x00692f90
    void Serialize(void* object);                               // 0x00693e10
};
struct cEmptyBubble {
    float mX, mY, mZ, mW;
    uint32_t mFlags;
};
struct EmptyBubbleVec {
    cEmptyBubble* mpBegin;
    cEmptyBubble* mpEnd;
    cEmptyBubble* mpCap;
    void Reserve(int n);                                              // 0x00c00fb0
    void DoInsertValue(cEmptyBubble* pos, const cEmptyBubble* value); // 0x00bde910
};
cEmptyBubble* CopyBubbleRange(cEmptyBubble* first, cEmptyBubble* last,
                              cEmptyBubble* dst);                     // 0x00951bf0
struct LanePayload;
struct LaneRec {
    Vec3 mPos;                 // +0x00
    union {
        Vec3      mDir;        // +0x0c  lane point
        IntIdxVec mNext;       // +0x0c  lane-graph node
    };
    float mRadius;             // +0x18
    int   mIndex;              // +0x1c

    void Construct(const LanePayload* src);                            // 0x00be0d70
};
struct AllocBlockHeader {
    uint32_t mRefCount;
};
struct LanePayload {
    Vec3          mPos;        // +0x00  written by the serializer
    IRefCounted*  mpData;      // +0x0c
    uint32_t      mPad10[2];   // +0x10
    uint32_t      mPad18[2];   // +0x18
};
struct LaneRecVec {
    LaneRec* mpBegin;
    LaneRec* mpEnd;
    LaneRec* mpCap;
    void ReservePoints(int n);                                    // 0x00c00f20
    void ReserveNodes(int n);                                     // 0x00c01ef0
    void DoInsertPoint(LaneRec* pos, const LaneRec* value);       // 0x00c01060
    void DoInsertNode(LaneRec* pos, const LanePayload* value);    // 0x00be7aa0
    void DoInsertNodeRec(LaneRec* pos, const LaneRec* value);     // 0x00be7aa0
    void DoDestroy(LaneRec* first, LaneRec* last);                // 0x00bdc770
};
LaneRec* CopyLaneRange(LaneRec* first, LaneRec* last, LaneRec* dst);  // 0x00be0e80
struct PtrVec {
    void** mpBegin;
    void** mpEnd;
    void** mpCap;
};
struct ILaneZone {
    bool Contains(const Vec3* point);                     // 0x00bec0f0
};
struct ILaneSource {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
    virtual Vec3* GetPosition();                          // slot 11 (+0x2c)
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
    virtual Vec3* GetFacing(Vec3* out);                   // slot 23 (+0x5c)
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
    virtual void s28();
    virtual float GetRadius();                            // slot 29 (+0x74)
};
struct cCityHall {
    void UpdateFromSubobject(const Vec3* pos, float* value);   // 0x00bcdd00
};
struct cCity {
    cCityHall* GetCityHall();                                  // 0x00bd9b40
    cCityHall* GetCityHall(Vec3* pos, float* radius);          // 0x00bd9b40
};
void PlanetModel();                                            // 0x00b3d350
struct CircleSpoke {
    uint32_t mPad[3];
    Vec3     mDir;              // +0x0c
};
struct cActionCircle {
    uint32_t pad00[(0x50) / 4];
    CircleSpoke* mpSpokes;      // +0x50
    cActionCircle();                                           // 0x00afba10
    ~cActionCircle();                                          // 0x00afbad0
    void SetAtCenter(const Vec3* center, float radius, const Vec3* facing,
                     float altitude);                          // 0x00af9cf0
    void FUN_00afd6d0(float a, float b, int count);            // 0x00afd6d0
};
static const float kLaneLinkDistance = 6.0f;
struct cCommunity {
virtual void v00();
virtual void v01();
virtual void v02();
    virtual void* Cast(uint32_t typeId);                       // slot 3  (+0x0c)
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
    virtual Vec3* GetPosition(Vec3* out);                      // slot 22 (+0x58)
virtual void v23();
virtual void v24();
virtual void v25();
    virtual void* GetSourceList();                             // slot 26 (+0x68)
    virtual void* GetLaneZone();                               // slot 27 (+0x6c)

    uint32_t pad04[(0x84 - 0x04) / 4];
    LaneRecVec mOut;                                           // +0x84

    void UpdateLanes();                                        // 0x00c01f90
};
// ---- items of slice s00c015e0 end

// @ 0x00c00590
int __fastcall FUN_00c00590(void* ecx_this, void* edx)
{
    int* v = (int*)((FnVp)VT(ecx_this, 0x70))(ecx_this);
    return (v[1] - v[0]) >> 2;
}

// @ 0x00c005b0
void __fastcall FUN_00c005b0(void* ecx_this, void* edx, void* stream)
{
    void* iface = ((FnVp)VT(stream, 0x20))(stream);
    uint32_t tag = 0x17f243b;
    void* io = ((FnVp)VT(iface, 0x18))(iface);
    EA_IO_WriteUint32(io, tag, 1, 0);

    void* p = *(void**)((char*)ecx_this + 0x11c);
    if (p != 0 && ((FnBool)VT(p, 0x2c))(p)) {
        p = *(void**)((char*)ecx_this + 0x11c);
        if (p != 0) {
            *(void**)((char*)ecx_this + 0x11c) = 0;
            ((FnVoid_Rel)VT(p, 4))(p);
        }
    }

    cVarListSerializer ser(ecx_this, &DAT_015710b8, 0x1a80d26);
    ser.Serialize(stream);
}

// @ 0x00c00850
void FUN_00c00850(Elem20* first, Elem20* last, Elem20* dst)
{
    for (; first != last; ++first, ++dst) {
        if (dst) {
            dst->f0 = first->f0;
            dst->f1 = first->f1;
            dst->f2 = first->f2;
            dst->f3 = first->f3;
            dst->f4 = first->f4;
            dst->f5 = first->f5;
            dst->f6 = first->f6;
            dst->u = first->u;
        }
    }
}

// @ 0x00c008c0
void FUN_00c008c0(uint32_t* out)
{
    void* val;
    if (out[0] != 0) {
        return;
    }
    AutoRef<cProperty> prop;
    void* pm = SP_PropertyManager();
    if (((FnGetProps)VT(pm, 0x2c))(pm, 0x16d4dff8, 0, prop.AsPPTypeParam())) {
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e43, &val) &&
            ((cProperty*)val)->mType == 9)
            out[0] = *(const uint32_t*)((cProperty*)val)->GetString8();
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e44, &val) &&
            ((cProperty*)val)->mType == 9)
            out[1] = *(const uint32_t*)((cProperty*)val)->GetString8();
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e45, &val) &&
            ((cProperty*)val)->mType == 9)
            out[2] = *(const uint32_t*)((cProperty*)val)->GetString8();
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e46, &val) &&
            ((cProperty*)val)->mType == 9)
            out[3] = *(const uint32_t*)((cProperty*)val)->GetString8();
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e47, &val) &&
            ((cProperty*)val)->mType == 9)
            out[4] = *(const uint32_t*)((cProperty*)val)->GetString8();
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e48, &val) &&
            ((cProperty*)val)->mType == 9)
            out[5] = *(const uint32_t*)((cProperty*)val)->GetString8();
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e49, &val) &&
            ((cProperty*)val)->mType == 9)
            out[6] = *(const uint32_t*)((cProperty*)val)->GetString8();
    }
}

// @ 0x00c00aa0
int FUN_00c00aa0(int value)
{
    FUN_00c008c0(g_168d228);
    for (int i = 0; i < 7; ++i) {
        if (value <= (int)g_168d228[i]) {
            return i;
        }
    }
    return 0;
}

// @ 0x00c00ad0
uint32_t FUN_00c00ad0(int index)
{
    if (index < 8) {
        FUN_00c008c0(g_168d228);
        return g_168d228[index];
    }
    return 0;
}

// @ 0x00c01ce0
void FUN_00c01ce0(ISerializableObject* object, EmptyBubbleVec* vec)
{
    cEmptyBubble* begin = vec->mpBegin;
    cEmptyBubble* end = vec->mpEnd;
    // Inlined vector bookkeeping: the tail copy is an empty range, the end
    // pointer then rewinds onto the begin pointer.
    CopyBubbleRange(end, end, begin);
    vec->mpEnd -= (end - begin);

    uint32_t count = 0;
    IStreamHolder* holder = object->Open();
    void* stream = holder->GetStream();
    ReadInt32(stream, &count, 1, 0);
    vec->Reserve((int)count);

    for (uint32_t i = 0; i < count; ++i) {
        cEmptyBubble value;
        value.mW = 0.0f;
        value.mFlags = 0;
        cVarListSerializer_s00c0_15e0 serializer;
        serializer.Construct(&value, 0x1570f10, 0x1a80d26);
        serializer.Serialize(object);

        if (vec->mpEnd < vec->mpCap) {
            cEmptyBubble* slot = vec->mpEnd;
            vec->mpEnd = slot + 1;
            if (slot != 0) {
                slot->mX = value.mX;
                slot->mY = value.mY;
                slot->mZ = value.mZ;
                slot->mW = value.mW;
                slot->mFlags = value.mFlags;
            }
        } else {
            vec->DoInsertValue(vec->mpEnd, &value);
        }
    }
    object->Close();
}

// @ 0x00c01e20
void ILaneObject::UpdateZone(bool force)
{
    if (mZoneValid == 0 && !force)
        return;

    FUN_00c014c0();
    Zone* zone = GetZone();
    if (zone == 0) {
        mOuterRadius = 0.0f;
        mInnerRadius = 0.0f;
    } else {
        mInnerRadius = zone->rMin;
        mOuterRadius = zone->rMax;
    }
    v32();
    v34();
}

// @ 0x00c01e80
void ILaneObject::ClearLanes()
{
    mObjects.erase(mObjects.mpBegin, mObjects.mpEnd);
    mReporters.erase(mReporters.mpBegin, mReporters.mpEnd);

    IRefCounted* p = mpAt11c;
    if (p != 0) {
        mpAt11c = 0;
        p->Release();
    }

    p = mpAt2c;
    if (p != 0) {
        mpAt2c = 0;
        p->Release();
    }
}

// @ 0x00c01f90
void cCommunity::UpdateLanes()
{
    LaneRec* begin = mOut.mpBegin;
    LaneRec* end = mOut.mpEnd;
    LaneRec* it = CopyLaneRange(end, end, begin);
    mOut.DoDestroy(it, mOut.mpEnd);
    mOut.mpEnd -= (end - begin);

    PtrVec* sources = (PtrVec*)GetSourceList();
    PlanetModel();
    if (sources->mpBegin == sources->mpEnd)
        return;

    ILaneZone* zone = (ILaneZone*)GetLaneZone();

    LaneRecVec points;
    points.mpBegin = 0;
    points.mpEnd = 0;
    points.mpCap = 0;
    points.ReservePoints((int)(sources->mpEnd - sources->mpBegin) + 1);

    int sourceCount = (int)(sources->mpEnd - sources->mpBegin);
    int index = 0;
    int i = 0;
    while (i < sourceCount) {
        ILaneSource* source = (ILaneSource*)sources->mpBegin[i];
        bool keep = true;
        if (zone != 0)
            keep = zone->Contains(source->GetPosition());
        if (keep) {
            LaneRec* entry;
            if (points.mpEnd < points.mpCap) {
                entry = points.mpEnd++;
            } else {
                LaneRec scratch;
                points.DoInsertPoint(points.mpEnd, &scratch);
                entry = points.mpEnd - 1;
            }
            entry->mPos = *source->GetPosition();
            entry->mRadius = source->GetRadius();
            Vec3 facing;
            source->GetFacing(&facing);
            entry->mDir = facing;
            entry->mIndex = index;
        }
        ++i;
        index += 6;
    }

    cCity* city = (cCity*)Cast(0xee9b2232);
    if (city != 0 && city->GetCityHall() != 0) {
        Vec3 hallPos;
        float hallRadius;
        cCityHall* hall = city->GetCityHall(&hallPos, &hallRadius);
        hall->UpdateFromSubobject(&hallPos, &hallRadius);

        LaneRec* entry;
        if (points.mpEnd < points.mpCap) {
            entry = points.mpEnd++;
        } else {
            LaneRec scratch;
            points.DoInsertPoint(points.mpEnd, &scratch);
            entry = points.mpEnd - 1;
        }
        entry->mPos = hallPos;
        entry->mRadius = hallRadius;

        Vec3 self;
        GetPosition(&self);
        float dx = hallPos.x - self.x;
        float dy = hallPos.y - self.y;
        float dz = hallPos.z - self.z;
        float inv = 1.0f / sqrtf(dz * dz + dy * dy + dx * dx + 1e-8f);
        entry->mDir.x = dx * inv;
        entry->mDir.y = dy * inv;
        entry->mDir.z = dz * inv;
        entry->mIndex = i * 6;
    }

    cActionCircle circle;
    int laneCount = (int)(points.mpEnd - points.mpBegin);
    for (int lane = 0; lane < laneCount; ++lane) {
        LaneRec* point = points.mpBegin + lane;
        int laneIndex = point->mIndex;
        circle.SetAtCenter(&point->mPos, point->mRadius + 2.0f, &point->mDir, 0.0f);
        circle.FUN_00afd6d0(1.0f, 1.0f, 6);

        for (int spoke = 0; spoke < 6; ++spoke) {
            LaneRec* node;
            if (mOut.mpEnd < mOut.mpCap) {
                node = mOut.mpEnd++;
                node->mNext.mpBegin = 0;
                node->mNext.mpEnd = 0;
                node->mNext.mpCap = 0;
            } else {
                LaneRec scratch;
                scratch.mNext.mpBegin = 0;
                scratch.mNext.mpEnd = 0;
                scratch.mNext.mpCap = 0;
                mOut.DoInsertNodeRec(mOut.mpEnd, &scratch);
                node = mOut.mpEnd - 1;
            }
            node->mPos = circle.mpSpokes[spoke].mDir;

            int next = laneIndex + spoke + 1;
            if (spoke == 5)
                next = laneIndex;
            node->mNext.DoInsertValueI(node->mNext.mpEnd, next);

            int prev = laneIndex + spoke - 1;
            if (spoke == 0)
                prev = laneIndex + 5;
            node->mNext.DoInsertValueI(node->mNext.mpEnd, prev);
        }
    }

    int nodeCount = (int)(mOut.mpEnd - mOut.mpBegin);
    if (nodeCount - 6 > 0) {
        int window = 6;
        int a = 0;
        do {
            LaneRec* pa = mOut.mpBegin + a;
            Vec3 posA = pa->mPos;
            int b = a + window;
            if (b < nodeCount) {
                do {
                    LaneRec* pb = mOut.mpBegin + b;
                    float dx = posA.x - pb->mPos.x;
                    float dy = posA.y - pb->mPos.y;
                    float dz = posA.z - pb->mPos.z;
                    if (sqrtf(dz * dz + dy * dy + dx * dx) < kLaneLinkDistance) {
                        pa->mNext.DoInsertValueI(pa->mNext.mpEnd, b);
                        pb->mNext.DoInsertValueI(pb->mNext.mpEnd, a);
                    }
                    ++b;
                } while (b < nodeCount);
            }
            --window;
            if (window == 0)
                window = 6;
            ++a;
        } while (a < nodeCount - 6);
    }

    if (points.mpBegin != 0)
        FreeAllocBlock(points.mpBegin);
}

// @ 0x00c024f0
void FUN_00c024f0(ISerializableObject* object, LaneRecVec* vec)
{
    LaneRec* begin = vec->mpBegin;
    LaneRec* end = vec->mpEnd;
    // Inlined eastl::vector::erase(begin, end): copy the (empty) tail range,
    // destroy the live range and rewind the end pointer.
    LaneRec* it = CopyLaneRange(end, end, begin);
    vec->DoDestroy(it, vec->mpEnd);
    vec->mpEnd -= (end - begin);

    uint32_t count = 0;
    IStreamHolder* holder = object->Open();
    void* stream = holder->GetStream();
    ReadInt32(stream, &count, 1, 0);
    vec->ReserveNodes((int)count);

    for (uint32_t i = 0; i < count; ++i) {
        LanePayload value;
        value.mpData = 0;
        value.mPad10[0] = 0;
        value.mPad10[1] = 0;
        cVarListSerializer_s00c0_15e0 serializer;
        serializer.Construct(&value, 0x1571000, 0x1a80d26);
        serializer.Serialize(object);

        if (vec->mpEnd < vec->mpCap) {
            LaneRec* slot = vec->mpEnd;
            vec->mpEnd = slot + 1;
            if (slot != 0)
                slot->Construct(&value);
        } else {
            vec->DoInsertNode(vec->mpEnd, &value);
        }
        if (value.mpData != 0 && ((AllocBlockHeader*)value.mpData)[-1].mRefCount != 0)
            FreeAllocBlock(value.mpData);
    }
    object->Close();
}
