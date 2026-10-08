// Slice s00bee450: 0x00BEE450, the cSpatialObject::LoadModel override of Simulator::cCityWalls
// (cSpatialObject sub-object at cCityWalls+0x34; the method name is Claude-coined).
//
// It loads the model, then reads the wall layout from the model's property list:
//   Turrets, Main/Side/Sea/Harvest/Freight gates, boat position, City_Hall + Buildings, Plazas,
//   Decorations, the 14 building-link rows, and three floats (inner radius, outer radius,
//   city-hall dias height); finally it tells the planet model.
// (cCityWalls layout from the ModAPI header, offsets below are relative to the sub-object.)
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
typedef unsigned int size_t;
inline void* operator new(size_t, void* p) { return p; }

struct Vector3 {
    float x, y, z;
    __forceinline Vector3() {}
    __forceinline Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Raw3 { uint32_t a, b, c; };

struct Prop {
    void*    mpData;
    uint32_t pad[3];
    uint8_t  mFlags;      // +0x10 (0x30: indirect)
    uint8_t  pad11;
    uint16_t mType;       // +0x12 (0xd: float)
};

struct PropList {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t id, Prop** out);   // 0x24
};

bool GetPropertyAsVector3(PropList* l, uint32_t id, Raw3* out);                 // 0x006a1110 cdecl
bool GetPropertyAsVector3Array(PropList* l, uint32_t id, int* n, Vector3** v);  // 0x006a0990 cdecl
bool GetPropertyAsBytes(PropList* l, uint32_t id, uint32_t* n, uint8_t** p);    // 0x006a0760 cdecl

extern uint32_t g_LinkRowIds[14];   // 0x01468f98

struct sp_vector_allocator { uint32_t mData[2]; };

struct SpVector {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    sp_vector_allocator mAllocator;
    void DoInsertValue(Vector3* position, const Vector3& value);   // 0x004b5ad0
    void resize(int n);                                            // 0x00473810
    Vector3* erase(Vector3* first, Vector3* last);                 // 0x0050f740
    __forceinline void push_back(const Vector3& value)
    {
        if (mpEnd < mpCapacity)
            ::new ((void*)mpEnd++) Vector3(value);
        else
            DoInsertValue(mpEnd, value);
    }
    __forceinline void erase_inline(Vector3* first, Vector3* last)
    {
        Vector3* d = first;
        for (Vector3* s = last; s != mpEnd; ++s, ++d) {
            d->x = s->x; d->y = s->y; d->z = s->z;
        }
        mpEnd -= (last - first);
    }
};

struct Model {
    uint32_t pad0;
    uint32_t mFlags;      // +0x04
    uint32_t pad08[17];
    Raw3     mColor;      // +0x4c
    uint32_t pad58[14];
    PropList* mpProps;    // +0x90
};

struct Civilization { uint32_t pad[0x31]; Raw3 mColor; };   // +0xc4

struct cCity {
    Civilization* GetCivilization();    // 0x00bd9bf0 (returns [this+0x590])
    void FUN_00be6f90();                // 0x00be6f90
};

struct cPlanetModel {
    void FUN_00b83c40(int arg);   // 0x00b83c40
};
cPlanetModel* PlanetModel();            // 0x00b3d350 (cdecl)

struct cCityWalls;

struct Spatial {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual int  v2c(float f, void* p, int a, int b);     // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual bool v58();                                   // 0x58

    uint8_t  pad04[0x98];
    Model*   mpModel;               // +0x9c
    uint8_t  pad_a0[0x128 - 0xa0];
    SpVector mTurrets;              // +0x128
    SpVector mTurretsT;             // +0x13c
    SpVector mGates;                // +0x150
    SpVector mGatesT;               // +0x164
    SpVector mBuildings;            // +0x178
    SpVector mBuildingsT;           // +0x18c
    SpVector mDecorations;          // +0x1a0
    SpVector mDecorationsT;         // +0x1b4
    SpVector mPlazas;               // +0x1c8
    SpVector mPlazasT;              // +0x1dc
    Raw3     mFirstBoatPos;         // +0x1f0
    Raw3     mFirstBoatPosT;        // +0x1fc
    Raw3     mModelDocksOffset;     // +0x208
    Raw3     mModelDocksOffsetT;    // +0x214
    int      mWallSize;             // +0x220
    float    mInnerRadius;          // +0x224
    float    mOuterRadius;          // +0x228
    float    mCityHallDiasHeight;   // +0x22c
    cCity*   mpCity;                // +0x230
    Raw3     mField268;             // +0x234
    uint8_t  mBuildingLinks[14][14];// +0x240

    bool LoadModel(int arg);        // 0x00c8a550 (cSpatialObject::LoadModel)
    cCityWalls* Walls() { return (cCityWalls*)((char*)this - 0x34); }
    bool LoadModelWalls(int arg);   // 0x00bee450
};

struct cCityWalls {
    void FUN_00beccf0();                            // 0x00beccf0
    void FUN_00bee150();                            // 0x00bee150
    void FUN_00becc80();                            // 0x00becc80
    void FUN_00bee200();                            // 0x00bee200
    Raw3 FUN_00becb10(const Raw3& v);               // 0x00becb10 (ret 8)
};

// Reads a float property (type 0xd) into out.
#define READ_FLOAT_PROP(id, out)                                                        \
    do {                                                                                \
        PropList* l = mpModel->mpProps;                                                 \
        Prop* p;                                                                        \
        if (l && l->GetProperty((id), &p) && p->mType == 0xd) {                         \
            float* d = (float*)p;                                                       \
            if (p->mFlags & 0x30) d = *(float**)p;                                      \
            (out) = *d;                                                                 \
        }                                                                               \
    } while (0)

// @ 0x00bee450
bool Spatial::LoadModelWalls(int arg)
{
    bool ok = LoadModel(arg);
    if (ok) {
        mpModel->mFlags |= 4;
        mpModel->mColor = mpCity->GetCivilization()->mColor;
        if (v58())
            mpModel->mFlags &= 0xfffff7ff;
        else
            mpModel->mFlags |= 0x800;

    if (mpModel->mpProps != 0) {

        Raw3 v;
        int n;
        Vector3* arr;
        if (GetPropertyAsVector3(mpModel->mpProps, 0x64ba57b, &v))
            mModelDocksOffset = v;

        cCityWalls* walls = Walls();
        walls->FUN_00beccf0();

        if (GetPropertyAsVector3Array(mpModel->mpProps, 0x43c4e1f, &n, &arr)) {
            mTurrets.resize(n);
            mTurretsT.resize(n);
            for (int i = 0; i < n; ++i)
                *(Raw3*)&mTurrets.mpBegin[i] = *(Raw3*)&arr[i];
            walls->FUN_00bee150();
        }

        if (GetPropertyAsVector3(mpModel->mpProps, 0x43c4e76, &v))
            *(Raw3*)&mGates.mpBegin[0] = v;

        if (GetPropertyAsVector3Array(mpModel->mpProps, 0x43c4e68, &n, &arr)) {
            if (n > 0)
                *(Raw3*)&mGates.mpBegin[1] = *(Raw3*)&arr[0];
            if (n > 1)
                *(Raw3*)&mGates.mpBegin[2] = *(Raw3*)&arr[1];
        }
        if (GetPropertyAsVector3(mpModel->mpProps, 0x43c4e96, &v))
            *(Raw3*)&mGates.mpBegin[3] = v;
        if (GetPropertyAsVector3(mpModel->mpProps, 0x43c4e94, &v))
            *(Raw3*)&mGates.mpBegin[5] = v;
        if (GetPropertyAsVector3(mpModel->mpProps, 0x43c4e95, &v))
            *(Raw3*)&mGates.mpBegin[4] = v;
        walls->FUN_00becc80();

        if (GetPropertyAsVector3(mpModel->mpProps, 0x6284ef8, &v))
            mFirstBoatPos = v;
        mFirstBoatPosT = walls->FUN_00becb10(mFirstBoatPos);

        mBuildings.erase(mBuildings.mpBegin, mBuildings.mpEnd);
        if (GetPropertyAsVector3(mpModel->mpProps, 0x43c4e97, &v))
            mBuildings.push_back(*(Vector3*)&v);
        if (GetPropertyAsVector3Array(mpModel->mpProps, 0x43c4e98, &n, &arr)) {
            for (int i = 0; i < n; ++i)
                mBuildings.push_back(arr[i]);
        }

        mPlazas.erase(mPlazas.mpBegin, mPlazas.mpEnd);
        if (GetPropertyAsVector3Array(mpModel->mpProps, 0x44041e3, &n, &arr)) {
            for (int i = 0; i < n; ++i)
                mPlazas.push_back(arr[i]);
        }

        mDecorations.erase_inline(mDecorations.mpEnd, mDecorations.mpEnd);
        if (GetPropertyAsVector3Array(mpModel->mpProps, 0x446ff4e, &n, &arr)) {
            for (int i = 0; i < n; ++i)
                mDecorations.push_back(arr[i]);
        }

        walls->FUN_00bee200();

        READ_FLOAT_PROP(0x4408ed6, mInnerRadius);
        READ_FLOAT_PROP(0x4408ed7, mOuterRadius);

        for (int row = 0; row < 14; ++row) {
            uint8_t* bytes = 0;
            uint32_t cnt = 0;
            if (GetPropertyAsBytes(mpModel->mpProps, g_LinkRowIds[row], &cnt, &bytes)) {
                if (cnt > 14)
                    cnt = 14;
                for (int j = 0; j < (int)cnt; ++j)
                    mBuildingLinks[row][j] = bytes[j];
            }
        }

        READ_FLOAT_PROP(0x5ef5f2d, mCityHallDiasHeight);

        void* unused;
        int r = v2c(mOuterRadius, unused, 0x10000000, 0);
        PlanetModel()->FUN_00b83c40(r);
    mpCity->FUN_00be6f90();
    }
    }
    return ok;
}
