// s00c015e0: obstacle/steering avoidance pass (0xc015e0). Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"
#include <math.h>
#include <stdlib.h>
#include <new>

struct SteerEntry {            // 0x2c bytes; the constructor only sets mKind2 = 1
    int type;
    int flag;
    float x, y, z;
    float w;
    uint32_t pad[5];
    SteerEntry() { flag = 1; }
};

struct SteerVec {
    SteerEntry* mpBegin;
    SteerEntry* mpEnd;
    SteerEntry* mpCap;
    void DoInsertValue(SteerEntry* pos, const SteerEntry& v);
    inline void push_back() {
        if (mpEnd < mpCap) {
            ::new (mpEnd++) SteerEntry();
        } else {
            SteerEntry e;
            DoInsertValue(mpEnd, e);
        }
    }
};

struct SteerCtx {
    float px, py, pz;
    uint32_t pad0[5];
    float tx, ty, tz;
    uint32_t pad1[0x15];
    struct Src {
        virtual void s0();
        virtual void s1();
        virtual void s2();
        virtual void s3();
        virtual void s4();
        virtual void s5();
        virtual void s6();
        virtual void s7();
        virtual void s8();
        virtual void s9();
        virtual void s10();
        virtual void s11();
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
        virtual void s23();
        virtual void s24();
        virtual void s25();
        virtual void s26();
        virtual void s27();
        virtual void s28();
        virtual float Radius(); } *src;   // +0x80
    SteerVec out;                                              // +0x84
};

struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, r; };

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

struct Avoider {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual Vec3* GetPosition(Vec3* out);   // +0x58
    virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
    virtual Zone* GetZone();                // +0x6c
    uint32_t pad[14];
    Vec4* mpObsBegin;                       // +0x3c
    Vec4* mpObsEnd;                         // +0x40
    void Avoid(SteerCtx* ctx);
};

static inline float len3(float x, float y, float z) { return sqrtf(x * x + z * z + y * y); }

void Avoider::Avoid(SteerCtx* ctx)
{
    Vec3 A, B, dir, an;
    A.x = ctx->px; A.y = ctx->py; A.z = ctx->pz;
    B.x = ctx->tx; B.y = ctx->ty; B.z = ctx->tz;
    const float selfR = ctx->src->Radius();

    dir.x = B.x - A.x; dir.y = B.y - A.y; dir.z = B.z - A.z;
    float inv = 1.0f / sqrtf(dir.x * dir.x + dir.z * dir.z + dir.y * dir.y + 1e-8f);
    dir.x = inv * dir.x; dir.y = dir.y * inv; dir.z = dir.z * inv;
    float inv2 = 1.0f / sqrtf(A.x * A.x + A.y * A.y + A.z * A.z + 1e-8f);
    an.x = A.x * inv2; an.y = A.y * inv2; an.z = A.z * inv2;

    int count = (int)(mpObsEnd - mpObsBegin);
    for (int i = 0; i < count; ++i) {
        const Vec4& o = mpObsBegin[i];
        float ox = o.x, oy = o.y, oz = o.z, orad = o.r;
        float ex = ox - A.x, ey = oy - A.y, ez = oz - A.z;
        float d2 = ex * ex + ez * ez + ey * ey;
        float gap = (sqrtf(d2) - orad) - selfR;
        if (gap > 0.0f) {
            if (gap < 4.0f) {
            if (ex * dir.x + ez * dir.z + ey * dir.y > 0.0f) {
                float fx = ox - B.x, fy = oy - B.y, fz = oz - B.z;
                float d2b = fx * fx + fz * fz + fy * fy;
                float db = sqrtf(d2b);
                if (db >= 1.0f) {
                    bool skip = false;
                    if (db < orad + 4.0f) {
                        float i1 = 1.0f / sqrtf(d2b + 1e-8f);
                        float i0 = 1.0f / sqrtf(d2 + 1e-8f);
                        if ((ez * i0) * (fz * i1) + (ey * i0) * (fy * i1) + (i0 * ex) * (i1 * fx) > 0.9f)
                            skip = true;
                    }
                    if (!skip) {
                        ctx->out.push_back();
                        SteerEntry* e = ctx->out.mpEnd - 1;
                        float cx = an.z * dir.y - an.y * dir.z;
                        float cy = dir.z * an.x - an.z * dir.x;
                        float cz = an.y * dir.x - dir.y * an.x;
                        e->type = 2;
                        if (ez * cz + ey * cy + ex * cx > 0.0f) {
                            cx *= -1.0f; cy *= -1.0f; cz *= -1.0f;
                        }
                        float s = 4.0f - gap;
                        e->x = cx * s; e->y = cy * s; e->z = cz * s;
                        if (gap < 1.0f)
                            e->flag = 2;
                    }
                }
            }
            }
        } else {
            float fx = ox - B.x, fy = oy - B.y, fz = oz - B.z;
            if (orad < sqrtf(fx * fx + fy * fy + fz * fz)) {
                ctx->out.push_back();
                SteerEntry* e = ctx->out.mpEnd - 1;
                e->type = 4;
                e->x = ox; e->y = oy; e->z = oz;
                e->flag = 2;
                e->w = 2.0f;
            }
        }
    }

    Zone* zone = GetZone();
    if (!zone) return;
    Vec3 tmp;
    Vec3* pos = GetPosition(&tmp);
    float r1 = zone->rMin;
    float pdx = A.x - pos->x, pdy = A.y - pos->y, pdz = A.z - pos->z;
    float dist = sqrtf(pdx * pdx + pdz * pdz + pdy * pdy);
    if (!(dist > r1 - 4.0f)) return;
    float r2 = zone->rMax;
    if (!(r2 + 4.0f > dist)) return;

    static PointVec pts;
    zone->FillPoints(&pts);
    int n = (int)(pts.mpEnd - pts.mpBegin);
    int j = 0;
    if (n > 0) {
        float thresh = r2 - r1;
        const Vec3* p = pts.mpBegin;
        do {
            float qx = A.x - p->x, qy = A.y - p->y, qz = A.z - p->z;
            if (thresh > sqrtf(qx * qx + qz * qz + qy * qy)) break;
            ++j; ++p;
        } while (j < n);
    }
    if (j == n) {
        ctx->out.push_back();
        SteerEntry* e = ctx->out.mpEnd - 1;
        e->type = 4;
        Vec3* q = GetPosition(&tmp);
        e->x = tmp.x; e->y = tmp.y; e->z = tmp.z;
        (void)q;
        if (r1 > dist) {
            e->w = (4.0f - (r1 - dist)) * 0.25f;
        } else if (dist > r2) {
            e->w = (4.0f - (r2 - dist)) * 0.25f;
        } else {
            e->w = -1.0f;
        }
    }
}

// ===========================================================================
// Lane maintenance (slice functions 0x00c01ce0 .. 0x00c024f0).
//
// The lane code keeps two parallel representations in 0x20-byte records: a lane
// *point* (position / facing / radius / index) and a lane-graph *node*
// (position + the indices of the neighbouring nodes).  The same record type is
// used for both; the +0x0c block is a Vec3 in the point phase and an index
// vector in the node phase.
// ===========================================================================

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

// The object that owns the zone-derived radii and the two reference vectors.
// 0x00c01e20 refreshes the radii; 0x00c01e80 releases everything.
struct ILaneObject {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26();
    virtual Zone* GetZone();                                   // slot 27 (+0x6c)
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
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

// ---------------------------------------------------------------------------
// Variable-list stream helpers
// ---------------------------------------------------------------------------

struct IStreamHolder {                // object returned by ISerializable::Open()
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5();
    virtual void* GetStream();                                 // slot 6 (+0x18)
};

struct ISerializableObject {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6();
    virtual void Close();                                      // slot 7 (+0x1c)
    virtual IStreamHolder* Open();                             // slot 8 (+0x20)
};

void ReadInt32(void* stream, uint32_t* value, int count, int flags);  // 0x0093a780
void FreeAllocBlock(void* block);                                     // 0x00f47380

// SP::cVarListSerializer: binds one serialized record and its variable-list key.
struct cVarListSerializer {
    uint8_t mStorage[0xa14];
    void Construct(void* record, uint32_t key, uint32_t type);  // 0x00692f90
    void Serialize(void* object);                               // 0x00693e10
};

// 0x14-byte bubble record read out of a variable list.
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
        cVarListSerializer serializer;
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

// ---------------------------------------------------------------------------
// Lane records
// ---------------------------------------------------------------------------

struct LanePayload;

// 0x20-byte record.  In the lane-point phase +0x0c holds the facing and
// +0x18/+0x1c the radius/index; in the lane-graph phase +0x0c holds the
// neighbour index list.
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

// The EA allocator keeps a reference count in the word in front of a block.
struct AllocBlockHeader {
    uint32_t mRefCount;
};

// Payload filled in by cVarListSerializer before it is turned into a LaneRec.
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
        cVarListSerializer serializer;
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

// ---------------------------------------------------------------------------
// SP::cCommunity::UpdateLanes
// ---------------------------------------------------------------------------

struct PtrVec {
    void** mpBegin;
    void** mpEnd;
    void** mpCap;
};

struct ILaneZone {
    bool Contains(const Vec3* point);                     // 0x00bec0f0
};

// A building/object that contributes a lane point.
struct ILaneSource {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual Vec3* GetPosition();                          // slot 11 (+0x2c)
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual Vec3* GetFacing(Vec3* out);                   // slot 23 (+0x5c)
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
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

// One of the six spokes the action circle lays down for a lane point.
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
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual void* Cast(uint32_t typeId);                       // slot 3  (+0x0c)
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual Vec3* GetPosition(Vec3* out);                      // slot 22 (+0x58)
    virtual void v23(); virtual void v24(); virtual void v25();
    virtual void* GetSourceList();                             // slot 26 (+0x68)
    virtual void* GetLaneZone();                               // slot 27 (+0x6c)

    uint32_t pad04[(0x84 - 0x04) / 4];
    LaneRecVec mOut;                                           // +0x84

    void UpdateLanes();                                        // 0x00c01f90
};

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
