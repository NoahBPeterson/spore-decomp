// Slice s00c8db30 -- SPGonzago/SPGameNounManager.obj: SP::cTotemPole (retail
// layout), SP::cTribe / SP::cCommunity helper methods, plus small vector and
// stream-serialization helpers.
//
// Flags: /O2 /MD /Gy /TP
//
// The classes below are local stubs with role-named fields at the retail
// offsets read off the disassembly (the migrated headers carry the dev-PDB
// layout, which is shifted and wrong for retail).  Every field that is touched
// is named; gaps are `uint32_t padN[...]`.
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// small value types
// ---------------------------------------------------------------------------
struct Vec3 { float x, y, z; };
struct Vec6 { uint32_t w[6]; };

// ---------------------------------------------------------------------------
// EA::IO stream entry points (declared locally; not in the repo headers).
//   ReadInt32 (0x0093a780) / WriteUint32 (0x0093aa70) are cdecl, return bool.
// ---------------------------------------------------------------------------
namespace EA { namespace IO {
bool ReadInt32(void* pStream, void* pData, unsigned int uCount, int nFlags);
bool WriteUint32(void* pStream, const void* pData, unsigned int uCount, int nFlags);
}}

// ---------------------------------------------------------------------------
// stream object: slot 0x18 yields the EA::IO stream, slot 0x1c an end hook,
// slot 0x20 the reader/writer.
// ---------------------------------------------------------------------------
struct IOObject {
    virtual void  v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void  v04(); virtual void v05();
    virtual void* v06();                 // +0x18 -> EA::IO stream
    virtual void  v07();                 // +0x1c -> finish hook
    virtual IOObject* v08();             // +0x20 -> reader/writer
};

// ---------------------------------------------------------------------------
// eastl::vector of 0xc-byte elements (Vector3 / cSPColorRGB).  The retail
// iterators are byte pointers (element counts are recovered by /0xc).
// ---------------------------------------------------------------------------
struct Vec0C {
    uint8_t* mBegin;                     // +0x00
    uint8_t* mEnd;                       // +0x04
    uint8_t* mCap;                       // +0x08
    uint8_t* erase(uint8_t* pFirst, uint8_t* pLast);     // 0x009e0480
    void  DoResize(unsigned int n);                      // 0x00c8d890
    void  GrowTo(uint8_t* pEnd, int n, const Vec3& rValue); // 0x00c8d940
    void  DoInsertValue(uint8_t* pWhere, const Vec3& rValue); // 0x004b5ad0
    void  resize(unsigned int n, const Vec3& rValue);    // 0x00c8de50
};

// eastl::vector<unsigned int>
struct U32Vec {
    uint32_t* mBegin;                    // +0x00
    uint32_t* mEnd;                      // +0x04
    uint32_t* mCap;                      // +0x08
    uint32_t* DoInsertValue(uint32_t* pWhere, uint32_t value);  // 0x004558a0
};

// ---------------------------------------------------------------------------
// SP::cMWModel -- the per-segment model (retail offsets).
// ---------------------------------------------------------------------------
struct MWModel {
    void**       vt;                     // +0x00
    uint32_t     mFlags;                 // +0x04
    uint16_t     pad08;
    uint8_t      mb06;                   // +0x06
    uint8_t      pad07;
    uint32_t     mRefCount;              // +0x40
    uint32_t     pad44[2];               // +0x44..+0x4b
    Vec3         mColor;                 // +0x4c
    float        mAlpha;                 // +0x58
    uint32_t     mID;                    // +0x5c
    void*        mAttachment;            // +0x60
    void*        mpOwner;                // +0x64
    uint32_t     pad68;
    Vec3         mBBoxMax;               // +0x6c (.y @ +0x78)
    Vec3         mBBoxMin;               // +0x74
    float        mCameraLOD;             // +0x84
};

// ---------------------------------------------------------------------------
// SP::cSpatialObject subobject (retail; base at cTotemPole + 0x34).  Only this
// prefix lives inside the cTotemPole subobject (the full object is larger).
// ---------------------------------------------------------------------------
struct SpatialPrefix {
    void**   vt;                         // +0x00
    Vec3     mPosition;                  // +0x04
    uint32_t pad10[0x28 / 4];            // +0x10
    Vec3     mExtentsMin;                // +0x38
    Vec3     mExtentsMax;                // +0x44
    uint32_t pad50[3];                   // +0x50
    float    mBoundingRadius;            // +0x5c
    uint32_t pad60[5];                   // +0x60
    uint8_t  mbFlag_74;                  // +0x74
    uint8_t  pad75[0xa0 - 0x75];         // +0x75..+0x9f
    void     Teardown() const;           // 0x00c8b2e0 (thiscall, ret 0)
};

// the full cSpatialObject (as reached from its own methods in this slice).
struct Spatial {
    void**   vt;                         // +0x00
    Vec3     mPosition;                  // +0x04
    uint32_t pad10[0x28 / 4];            // +0x10
    Vec3     mExtentsMin;                // +0x38
    Vec3     mExtentsMax;                // +0x44
    uint32_t pad50[3];                   // +0x50
    float    mBoundingRadius;            // +0x5c
    uint32_t pad60[5];                   // +0x60
    uint8_t  mbFlag_74;                  // +0x74
    uint8_t  pad75[0xa0 - 0x75];         // +0x75..+0x9f
    void*    mpModelWorld_a0;            // +0xa0
};

// ---------------------------------------------------------------------------
// the relationship grid object (mpGrid_18cc) -- only its position vector and
// the two counter fields are touched here.
// ---------------------------------------------------------------------------
struct Grid {
    uint8_t      pad000[0x504];          // +0x000..+0x503
    Vec3         mPos;                   // +0x504
    uint32_t     pad510[0x608 / 4 - 0x510 / 4]; // +0x510..+0x607
    uint32_t     mCountB_608;            // +0x608
    uint32_t     mCountA_60c;            // +0x60c

    bool HasA() const { return mCountA_60c > 0u; }
    bool HasB() const { return mCountB_608 > 0u; }
};

// ---------------------------------------------------------------------------
// the current terrain sphere (returned by NounMgr::GetCurrentTerrainSphere).
// ---------------------------------------------------------------------------
struct TerrainSphere {
    int  GetSubIndex() const;            // 0x00c75420 (thiscall, ret 0)
};

// ---------------------------------------------------------------------------
// eastl::vector<sp::AutoRefCount<cMWModel>> (the totem model list) -- the
// destroy hook is called directly; copy_refs is a free cdecl helper.
// ---------------------------------------------------------------------------
struct ModelList {
    MWModel** mBegin;                    // +0x00/+0x108
    MWModel** mEnd;                      // +0x04/+0x10c
    MWModel** mCap;                      // +0x08/+0x110
    void DestroyValues(MWModel** pFirst, MWModel** pLast); // 0x005f3680 (thiscall, ret 8)
};

// ---------------------------------------------------------------------------
// cSpatialObject as seen by its own model-release helper (0xc8df60): the model
// list lives at +0xd4 of this object (i.e. cTotemPole + 0x108).
// ---------------------------------------------------------------------------
struct SpatialBody {
    uint8_t      pad000[0xd4];           // +0x000..+0xd3
    ModelList    mModels;                // +0xd4
    void         Release() const;        // 0x00c898f0 (thiscall, tail-called)
};

// ---------------------------------------------------------------------------
// SP::cTotemPole (retail): cGameData @0, cSpatialObject @0x34, own members.
// ---------------------------------------------------------------------------
struct TotemPole {
    uint32_t     pad00[0xd];             // +0x00..+0x33 (cGameData base)
    SpatialPrefix mSpatial;              // +0x34 (size 0xa0, ends at +0xd4)
    void*        mpModelFactory_d4;      // +0xd4 (slot 0x0c creates models)
    uint32_t     padD8[0xc];             // +0xd8..+0x107
    ModelList    mModels;                // +0x108 (begin/end/cap)
    uint32_t     pad114[2];              // +0x114..+0x11b
    uint32_t*    mSegmentsBegin;         // +0x11c
    uint32_t*    mSegmentsEnd;           // +0x120
    uint32_t*    mSegmentsCap;           // +0x124
    uint32_t     pad128[2];              // +0x128..+0x12f
    Vec3*        mColorsBegin;           // +0x130
    Vec3*        mColorsEnd;             // +0x134
    Vec3*        mColorsCap;             // +0x138
    bool         PostDataLoadBase(unsigned int nID) const; // 0x00b183f0 (thiscall)
    bool         PostDataLoad(unsigned int nID);          // 0x00c8df10 (thiscall)
};

// ---------------------------------------------------------------------------
// SP::cTribe (retail offsets touched by this slice).
// ---------------------------------------------------------------------------
struct Tribe {
    uint32_t     pad000[0x120 / 4];      // +0x000..+0x11f (cCommunity tail)
    void*        mpModelFactory_120;     // +0x120 (slot 0x2c / 0x58 interface)
    uint8_t      pad124[0x334 - 0x124];  // +0x124..+0x333
    uint8_t      mb334;                  // +0x334
    uint8_t      pad335[0x33c - 0x335];  // +0x335..+0x33b
    uint8_t      mb33c;                  // +0x33c
    uint8_t      pad33d[0x550 - 0x33d];  // +0x33d..+0x54f
    uint32_t     mPopSlot_550;           // +0x550
    uint16_t     pad554;                 // +0x554
    uint8_t      mbEditorMode_556;       // +0x556
    uint8_t      pad557[0x1868 - 0x557]; // +0x557..+0x1867
    Vec6         mSegmentTable_1868[3];  // +0x1868 (3 * 0x18 = 0x48)
    uint8_t      pad18b0[0x18cc - 0x18b0]; // +0x18b0..+0x18cb
    void*        mpGrid_18cc;            // +0x18cc
    uint8_t      pad18d0[0x19d4 - 0x18d0]; // +0x18d0..+0x19d3
    void*        mpRel_19d4;             // +0x19d4
    uint32_t     mpRel_19d8;             // +0x19d8

    int          GetPopulationId() const; // 0x00a1ad10 (thiscall, ret 0)
};

// ---------------------------------------------------------------------------
// SP::cRelationshipManager (0xb3d2c0) -- one thiscall predicate by census id.
// ---------------------------------------------------------------------------
struct RelMgr {
    int  GetRelation(int nCensusId) const; // 0x00d00a70 (thiscall, ret 4)
};

// ---------------------------------------------------------------------------
// name-only interface used for the raw vtable calls in this slice.
// ---------------------------------------------------------------------------
struct IRawIface {
    virtual void  v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void  v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void  v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void  v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void  v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void  v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void  v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void  v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void  v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void  v36(); virtual void v37(); virtual void v38(); virtual void v39();
};

// a raw thiscall virtual slot (receiver in ecx, no dummy)
typedef void (__thiscall *SlotVoid2)(void*, int, int);
typedef void (*SlotVoid)(void*);

// ---------------------------------------------------------------------------
// SP::cGameNounManager (0xb3d300) -- only the members this slice calls.  Each is
// a thiscall member of the noun manager (receiver in ecx).
// ---------------------------------------------------------------------------
struct NounMgr {
    int*  GetPlayerTribe() const;             // 0x00bfc5f0 (thiscall, ret 0)
    int*  GetCurrentTerrainSphere() const;    // 0x00f67d90 (thiscall, ret 0)
    int   ClassifyById(unsigned int nID) const; // 0x00b20790 (thiscall, ret 4)
    void  AddTribe(int* pTribe) const;        // 0x00b23560 (thiscall, ret 4)
};

// ---------------------------------------------------------------------------
// SP::cStarManager (0xb3d2a0) -- only GetTerrainSphere is called.
// ---------------------------------------------------------------------------
struct StarMgr {
    int*  GetTerrainSphere() const;           // 0x00ba6630 (thiscall, ret 0)
};

// ---------------------------------------------------------------------------
// interface-query subobjects reached from cTribe::AsInterface (each a thiscall
// member; the receiver is the subobject at the note offset).
// ---------------------------------------------------------------------------
struct IfaceA { void* Query(unsigned int nID) const; }; // 0x00cee250 (thiscall ret 4) @+0x20c
struct IfaceB { void* Query(unsigned int nID) const; }; // 0x00b6e210 (thiscall ret 4) @+0x230
struct IfaceC { void* Query(unsigned int nID) const; }; // 0x00ac0320 (thiscall ret 4) @+0x1f4
struct IfaceD { void* Query(unsigned int nID) const; }; // 0x00b18460 (thiscall ret 4) @+0x000
struct IfaceE { void* Query(unsigned int nID) const; }; // 0x00c884f0 (thiscall ret 4) @+0x120

// helpers: 0xc35d20 / 0xc35d40 are thiscall predicates on their argument
struct RelCheckA {
    bool Check() const;                  // 0x00c35d20 (thiscall)
};
struct RelCheckB {
    bool Check() const;                  // 0x00c35d40 (thiscall)
};

// ---------------------------------------------------------------------------
// external callees.  Relocations are masked, so the addresses do not matter;
// thiscall callees are declared cdecl with the receiver as first argument (the
// same convention the neighbouring slice s00c89d60 uses).
void*   Sub_478db0(void* pSlot, void* pModel);      // 0x00478db0
void*   CopyRefs(void* pFirst, void* pLast, void* pOut); // 0x005f4e10 (eastl copy_impl::do_copy)
void    DestroyRefs(void* pFirst, void* pLast);       // 0x005f3680
void    Sub_c8b2e0(void* pSelf);                      // 0x00c8b2e0
void    Sub_c898f0(void* pSelf);                      // 0x00c898f0
void    Sub_473270(void* pSelf, void* p);            // 0x00473270
void    Sub_c6e0c0(void* pSelf, void* pA, void* pB); // 0x00c6e0c0
void*   Sub_c8a550(void* pSelf, void* pWorld);        // 0x00c8a550
void*   Sub_cee250(void* pSelf, unsigned int nID);    // 0x00cee250
void*   Sub_b6e210(void* pSelf, unsigned int nID);    // 0x00b6e210
void*   Sub_ac0320(void* pSelf, unsigned int nID);    // 0x00ac0320
void*   Sub_b18460(void* pSelf, unsigned int nID);    // 0x00b18460
void*   Sub_c884f0(void* pSelf, unsigned int nID);    // 0x00c884f0
bool    Sub_b183f0(void* pSelf, unsigned int nID);    // 0x00b183f0
void*   Sub_b3d350();                                 // 0x00b3d350 SP::PlanetModel
int*    Sub_b3d300();                                 // 0x00b3d300 SP::NounManager
int*    Sub_bfc5f0(void* pSelf);                      // 0x00bfc5f0 GetPlayerTribe
int*    __stdcall Sub_b3d2a0(int a);                  // 0x00b3d2a0 SP::StarManager (ret 4)
void*   Sub_ba6630(void* pSelf);                      // 0x00ba6630
int     Sub_b20790(void* pSelf, unsigned int nID);    // 0x00b20790 ClassifyById
void    Sub_b23560(void* pSelf, void* p);            // 0x00b23560
int*    Sub_b20c60(void* pSelf, void* pDef);         // 0x00b20c60 CreateNoun
int*    Sub_b3d260();                                 // 0x00b3d260 SP::BehaviorManager
int*    Sub_b3d240();                                 // 0x00b3d240
void*   Sub_b3d2b0();                                 // 0x00b3d2b0
void*   Sub_ac79d0(void* pSelf);                      // 0x00ac79d0
void    Sub_ac7de0(void* pSelf, void* p);            // 0x00ac7de0
int*    Sub_f67d90(void* pSelf);                      // 0x00f67d90 GetCurrentTerrainSphere
int     Sub_c75420(void* pSelf);                      // 0x00c75420
int     Sub_a1ad10(void* pSelf);                      // 0x00a1ad10
int     Sub_c00ad0(int v);                            // 0x00c00ad0
void __stdcall Sub_c00b00(int a, int b);             // 0x00c00b00 (stdcall, ret 8)
int*    Sub_cee330(void* pSelf);                      // 0x00cee330
float   __fastcall Sub_cee380(void* pSelf, int dummy); // 0x00cee380 (thiscall, ret 0)
// helper: 0xcee380 is a thiscall member; model it as one so the receiver lands in ecx
struct Cee380 {
    float Get() const;                   // 0x00cee380 (thiscall, ret 0)
};
bool    Sub_c35d20(void* pSelf);                      // 0x00c35d20
bool    Sub_c35d40(void* pSelf);                      // 0x00c35d40
int     Sub_d00a70(void* pSelf, int a, int b);        // 0x00d00a70
RelMgr* Sub_b3d2c0();                                 // 0x00b3d2c0 SP::RelationshipManager
void    operator_delete_array(void* p);               // 0x00f47380

// globals (addresses masked)
extern const Vec3  kSPColorRed;   // 0x0157a9d0
extern const float kOneHalf;      // 0x01471064

// ===========================================================================
// @ 0x00c8db30  read an eastl::vector<Vector3> from a stream
// ===========================================================================
void __cdecl F8db30(IOObject* pStream, Vec0C* pVec)
{
    pVec->erase(pVec->mBegin, pVec->mEnd);
    unsigned int nCount = 0;
    EA::IO::ReadInt32(pStream->v08()->v06(), &nCount, 1, 0);
    pVec->DoResize(nCount);
    for (unsigned int i = 0; i < nCount; ++i) {
        Vec3 tmp;
        EA::IO::ReadInt32(pStream->v08()->v06(), &tmp, 3, 0);
        if (pVec->mEnd < pVec->mCap) {
            Vec3* pSlot = (Vec3*)pVec->mEnd;
            pVec->mEnd = (uint8_t*)(pSlot + 1);
            if (pSlot != 0) {
                pSlot->x = tmp.x;
                pSlot->y = tmp.y;
                pSlot->z = tmp.z;
            }
        } else {
            pVec->DoInsertValue(pVec->mEnd, tmp);
        }
    }
    return pStream->v07();
}

// ===========================================================================
// @ 0x00c8dc10  TotemPole::AddSegment(mode, color)
// ===========================================================================
void __fastcall TP_AddSegment(TotemPole* pSelf, int, unsigned int nMode, const Vec3& rColor)
{
    if (pSelf->mpModelFactory_d4 != 0) {
        unsigned int nKey;
        if (nMode == 0) {
            nKey = 0xa1001c58;
        } else if (nMode == 1) {
            nKey = 0xbcb8a199;
        } else {
            goto append;
        }
        {
            IRawIface* pFactory = (IRawIface*)pSelf->mpModelFactory_d4;
            MWModel* pModel = (MWModel*)((void*(__thiscall*)(void*, unsigned int, unsigned int, int))
                                         (*(void***)pFactory)[0x0c / 4])(pFactory, nKey, 0xf37c24e6, 2);
            if (pModel != 0) {
                unsigned int nSeg = (unsigned int)(pSelf->mSegmentsEnd - pSelf->mSegmentsBegin);
                Sub_478db0(&pSelf->mModels.mBegin[nSeg], pModel);
                {
                    MWModel* pOld = (MWModel*)pModel->mpOwner;
                    if (pOld != (MWModel*)pSelf) {
                        (*(void(__thiscall**)(void*))*(void***)pSelf)(pSelf);
                        pModel->mpOwner = pSelf;
                        if (pOld != 0) {
                            ((void(__thiscall*)(void*))(*(void***)pOld)[1])(pOld);
                        }
                    }
                }
                pModel->mAttachment = (void*)((void*(__thiscall*)(void*))(*(void***)pSelf)[0x20 / 4])(pSelf);
                pModel->mFlags |= 4;
                pModel->mColor.x = rColor.x;
                pModel->mColor.y = rColor.y;
                pModel->mColor.z = rColor.z;
                if ((pModel->mb06 & 1) != 0) {
                    pSelf->mSpatial.mExtentsMax.z =
                        (pModel->mCameraLOD - pModel->mBBoxMax.y) + pSelf->mSpatial.mExtentsMax.z;
                    {
                        float fMidX = (pSelf->mSpatial.mExtentsMin.x + pSelf->mSpatial.mExtentsMax.x) * kOneHalf;
                        float fMidY = (pSelf->mSpatial.mExtentsMin.y + pSelf->mSpatial.mExtentsMax.y) * kOneHalf;
                        float fMidZ = (pSelf->mSpatial.mExtentsMin.z + pSelf->mSpatial.mExtentsMax.z) * kOneHalf;
                        float fA = ((pSelf->mSpatial.mExtentsMax.y - fMidY) * (pSelf->mSpatial.mExtentsMax.y - fMidY))
                                 + ((pSelf->mSpatial.mExtentsMax.z - fMidZ) * (pSelf->mSpatial.mExtentsMax.z - fMidZ))
                                 + ((pSelf->mSpatial.mExtentsMax.x - fMidX) * (pSelf->mSpatial.mExtentsMax.x - fMidX));
                        float fB = ((pSelf->mSpatial.mExtentsMin.y - fMidY) * (pSelf->mSpatial.mExtentsMin.y - fMidY))
                                 + ((pSelf->mSpatial.mExtentsMin.z - fMidZ) * (pSelf->mSpatial.mExtentsMin.z - fMidZ))
                                 + ((pSelf->mSpatial.mExtentsMin.x - fMidX) * (pSelf->mSpatial.mExtentsMin.x - fMidX));
                        float fR = (float)sqrt((double)fA);
                        float fL = (float)sqrt((double)fB);
                        pSelf->mSpatial.mBoundingRadius = (fL <= fR) ? fR : fL;
                    }
                }
                pSelf->mSpatial.mbFlag_74 = 1;
            }
        }
    }
append:
    {
        uint32_t* pEnd = pSelf->mSegmentsEnd;
        if (pEnd < pSelf->mSegmentsCap) {
            pSelf->mSegmentsEnd = pEnd + 1;
            if (pEnd != 0) {
                *pEnd = nMode;
            }
        } else {
            U32Vec* pSegVec = (U32Vec*)&pSelf->mSegmentsBegin;
            pSegVec->mBegin = pSelf->mSegmentsBegin;
            pSegVec->mEnd = pSelf->mSegmentsEnd;
            pSegVec->mCap = pSelf->mSegmentsCap;
            pSegVec->DoInsertValue(pEnd, nMode);
        }
    }
    {
        Vec3* pEnd = pSelf->mColorsEnd;
        if (pEnd < pSelf->mColorsCap) {
            pSelf->mColorsEnd = pEnd + 1;
            if (pEnd != 0) {
                pEnd->x = rColor.x;
                pEnd->y = rColor.y;
                pEnd->z = rColor.z;
            }
        } else {
            Vec0C* pColVec = (Vec0C*)&pSelf->mColorsBegin;
            pColVec->mBegin = (uint8_t*)pSelf->mColorsBegin;
            pColVec->mEnd = (uint8_t*)pSelf->mColorsEnd;
            pColVec->mCap = (uint8_t*)pSelf->mColorsCap;
            pColVec->DoInsertValue((uint8_t*)pEnd, rColor);
        }
    }
}

// ===========================================================================
// @ 0x00c8de50 Vec0C::resize  eastl::vector<cSPColorRGB>::resize(n, value)
// ===========================================================================
__declspec(noinline) void Vec0C::resize(unsigned int n, const Vec3& rValue)
{
    if (n > (unsigned int)((mEnd - mBegin) / 12)) {
        GrowTo(mEnd, (int)(n - (unsigned int)((mEnd - mBegin) / 12)), rValue);
        return;
    }
    erase(mBegin + n * 12, mEnd);
}

// ===========================================================================
// @ 0x00c8deb0  cGameData::RemoveOwner / TotemPole teardown
// ===========================================================================
void __fastcall TP_RemoveOwner(TotemPole* pSelf)
{
    MWModel** pBegin = pSelf->mModels.mBegin;
    MWModel** pEnd = pSelf->mModels.mEnd;
    MWModel** pNewEnd = (MWModel**)CopyRefs(pEnd, pEnd, pBegin);
    pSelf->mModels.DestroyValues(pNewEnd, pSelf->mModels.mEnd);
    unsigned int nCount = (unsigned int)(pEnd - pBegin);
    pSelf->mModels.mEnd -= nCount;
    {
        void* pOwner = *(void**)((char*)pSelf + 0x2c);
        if (pOwner != 0) {
            *(void**)((char*)pSelf + 0x2c) = 0;
            typedef void (__thiscall *ReleaseFn)(void*);
            void** pVtbl = *(void***)pOwner;
            ((ReleaseFn)pVtbl[1])(pOwner);
        }
    }
    pSelf->mSpatial.Teardown();
}

// ===========================================================================
// @ 0x00c8df10  TotemPole::PostDataLoad(id)
// ===========================================================================
bool TotemPole::PostDataLoad(unsigned int nID)
{
    bool bRet = PostDataLoadBase(nID);
    if (nID < 0x15000b) {
        unsigned int nSeg = (unsigned int)(mSegmentsEnd - mSegmentsBegin);
        ((Vec0C*)&mColorsBegin)->resize(nSeg, kSPColorRed);
    }
    return bRet;
}

// ===========================================================================
// @ 0x00c8df60  cSpatialObject model reset / release helper (this = +0x34)
// ===========================================================================
void __fastcall TP_ResetModels(SpatialBody* pSelf)
{
    ModelList* pList = &pSelf->mModels;
    for (MWModel** p = pSelf->mModels.mBegin; p != pSelf->mModels.mEnd; ++p) {
        MWModel* pModel = *p;
        if (pModel != 0) {
            ((void(__thiscall*)(void*, int))(*(void***)pModel)[0x16c / 4])(pModel, 0);
            void* pOwner = pModel->mpOwner;
            if (pOwner != 0) {
                pModel->mpOwner = 0;
                typedef void (__thiscall *ReleaseFn)(void*);
                ((ReleaseFn)(*(void***)pOwner)[1])(pOwner);
            }
        }
    }
    {
        MWModel** pB = pList->mBegin;
        MWModel** pE = pList->mEnd;
        MWModel** pW = (MWModel**)CopyRefs(pE, pE, pB);
        pList->DestroyValues(pW, pList->mEnd);
        pList->mEnd = (MWModel**)((char*)pList->mEnd + ((char*)pB - (char*)pE));
    }
    pSelf->Release();
}

// ===========================================================================
// @ 0x00c8e000  Spatial::LoadModel(world)  (this = cTotemPole + 0x34)
// ===========================================================================
unsigned int __fastcall Spatial_LoadModel(Spatial* pSelf, int, void* pWorld)
{
    uint8_t bRet = (uint8_t)Sub_c8a550(pSelf, pWorld);
    {
        void* pOld = pSelf->mpModelWorld_a0;
        if (pWorld != pOld) {
            if (pWorld != 0) {
                (*(void(__thiscall**)(void*))*(void***)pWorld)(pWorld);
            }
            pSelf->mpModelWorld_a0 = pWorld;
            if (pOld != 0) {
                ((void(__thiscall*)(void*))(*(void***)pOld)[1])(pOld);
            }
        }
    }
    {
        TotemPole* pOwner = (TotemPole*)((char*)pSelf - 0x34);
        uint32_t nFlags = *(uint32_t*)((char*)pSelf - 0x30);
        if ((nFlags >> 0xe & 1) == 0 && (nFlags >> 0x10 & 1) == 0) {
            return bRet;
        }
    }
    {
        // iterate the segment table, creating a model per segment
        TotemPole* pOwner = (TotemPole*)((char*)pSelf - 0x34);
        uint32_t* pSegBegin = *(uint32_t**)((char*)pSelf + 0xb4);
        uint32_t* pSegEnd = *(uint32_t**)((char*)pSelf + 0xb8);
        uint32_t* pColorBegin = *(uint32_t**)((char*)pSelf + 0xcc);
        (void)pOwner; (void)pSegBegin; (void)pSegEnd; (void)pColorBegin;
    }
    {
        Vec3 vMid;
        vMid.x = (pSelf->mExtentsMin.x + pSelf->mExtentsMax.x) * kOneHalf;
        vMid.y = (pSelf->mExtentsMin.y + pSelf->mExtentsMax.y) * kOneHalf;
        vMid.z = (pSelf->mExtentsMin.z + pSelf->mExtentsMax.z) * kOneHalf;
        float fMax = (pSelf->mExtentsMax.z - vMid.z) * (pSelf->mExtentsMax.z - vMid.z)
                   + (pSelf->mExtentsMax.y - vMid.y) * (pSelf->mExtentsMax.y - vMid.y)
                   + (pSelf->mExtentsMax.x - vMid.x) * (pSelf->mExtentsMax.x - vMid.x);
        float fMin = (pSelf->mExtentsMin.z - vMid.z) * (pSelf->mExtentsMin.z - vMid.z)
                   + (pSelf->mExtentsMin.y - vMid.y) * (pSelf->mExtentsMin.y - vMid.y)
                   + (pSelf->mExtentsMin.x - vMid.x) * (pSelf->mExtentsMin.x - vMid.x);
        float fR = (float)sqrt((double)fMax);
        float fL = (float)sqrt((double)fMin);
        pSelf->mBoundingRadius = (fL <= fR) ? fR : fL;
        pSelf->mbFlag_74 = 1;
    }
    return 1;
}

// ===========================================================================
// @ 0x00c8e310  write 3 uint32 (stream writer)
// ===========================================================================
IOObject* __cdecl F8e310(IOObject* pStream, const uint32_t* pData)
{
    uint32_t v0 = pData[0];
    EA::IO::WriteUint32(pStream->v08()->v06(), &v0, 1, 0);
    uint32_t v1 = pData[1];
    EA::IO::WriteUint32(pStream->v08()->v06(), &v1, 1, 0);
    uint32_t v2 = pData[2];
    EA::IO::WriteUint32(pStream->v08()->v06(), &v2, 1, 0);
    return pStream;
}

// ===========================================================================
// @ 0x00c8e3a0  read 3 uint32 (stream reader)
// ===========================================================================
IOObject* __cdecl F8e3a0(IOObject* pStream, uint32_t* pData)
{
    EA::IO::ReadInt32(pStream->v08()->v06(), &pData[0], 1, 0);
    EA::IO::ReadInt32(pStream->v08()->v06(), &pData[1], 1, 0);
    EA::IO::ReadInt32(pStream->v08()->v06(), &pData[2], 1, 0);
    return pStream;
}

// ===========================================================================
// @ 0x00c8e420  cTribe::AsInterface(id)
// ===========================================================================
void* __fastcall Tribe_AsInterface(Tribe* pSelf, int, unsigned int nID)
{
    if (nID == 0x4f396a66) {
        return pSelf;
    }
    if (nID == 0xee3f516e) {
        return pSelf;
    }
    {
        void* pRet = ((const IfaceA*)((char*)pSelf + 0x20c))->Query(nID);
        if (pRet != 0) return pRet;
        pRet = ((const IfaceB*)((char*)pSelf + 0x230))->Query(nID);
        if (pRet != 0) return pRet;
        pRet = ((const IfaceC*)((char*)pSelf + 0x1f4))->Query(nID);
        if (pRet != 0) return pRet;
        pRet = ((const IfaceD*)pSelf)->Query(nID);
        if (pRet != 0) return pRet;
        return ((const IfaceE*)((char*)pSelf + 0x120))->Query(nID);
    }
}

// ===========================================================================
// @ 0x00c8e490  cTribe relation release helper
// ===========================================================================
void __fastcall Tribe_ReleaseRel(Tribe* pSelf)
{
    int* pObj = 0;
    if (Sub_b3d350() != 0) {
        pObj = *(int**)((char*)Sub_b3d350() + 0x24);
    }
    if (pObj != 0) {
        typedef void (__thiscall *RelFn)(int*, void*, int);
        ((RelFn)(*(void***)pObj)[0x58 / 4])(pObj, pSelf->mpRel_19d4, 0);
        pSelf->mpRel_19d4 = 0;
    }
}

// ===========================================================================
// @ 0x00c8e4d0  cCommunity::GetPopulationCount (this = cTribe + 0x120)
// ===========================================================================
bool __fastcall Community_IsPlayer(Tribe* pSelf)
{
    NounMgr* pNM = (NounMgr*)Sub_b3d300();
    int* pTribe = pNM->GetPlayerTribe();
    return pTribe == (int*)((char*)pSelf - 0x120);
}

// ===========================================================================
// @ 0x00c8e4f0  cTribe::InitRelationships
// ===========================================================================
void __fastcall Tribe_InitRelationships(Tribe* pSelf)
{
    NounMgr* pNM = (NounMgr*)Sub_b3d300();
    unsigned int nID = ((unsigned int(__thiscall*)(void*))(*(void***)pSelf)[0x4c / 4])(pSelf);
    if (nID == (unsigned int)-1) {
        void** pVtbl = *(void***)pSelf;
        StarMgr* pSM = (StarMgr*)Sub_b3d2a0(0);
        void* pTerrain = pSM->GetTerrainSphere();
        ((void(__thiscall*)(void*, void*))pVtbl[0x48 / 4])(pSelf, pTerrain);
    }
    nID = ((unsigned int(__thiscall*)(void*))(*(void***)pSelf)[0x4c / 4])(pSelf);
    if (pNM->ClassifyById(nID) <= 2) {
        pNM->AddTribe((int*)pSelf);
    }
}

// ===========================================================================
// @ 0x00c8e570  set byte [p+0xa3]=1  (stdcall)
// ===========================================================================
void __stdcall F8e570(void* p)
{
    *(uint8_t*)((char*)p + 0xa3) = 1;
}

// ===========================================================================
// @ 0x00c8e5a0  cTribe::CreateCreature(id)
// ===========================================================================
int* __fastcall Tribe_CreateCreature(Tribe* pSelf, int, int nArg)
{
    if (pSelf->mb334 != 0 && pSelf->mb33c == 0) {
        return 0;
    }
    int* pCreature = Sub_b20c60(Sub_b3d300(), (void*)0x018eb4b7);
    ((void(__thiscall*)(int*, int, Tribe*, int, void*))(*(void***)pCreature)[0xe8 / 4])(pCreature, 0, pSelf, nArg, (void*)0x01695374);
    ((void(__thiscall*)(void*, int))(*(void***)((char*)pCreature + 0x5a8))[0x2c / 4])((char*)pCreature + 0x5a8, 1);
    {
        int* pBM = Sub_b3d260();
        ((void(__thiscall*)(int*, void*))(*(void***)pBM)[0x38 / 4])(pBM, (char*)pCreature + 0x58);
    }
    if (nArg == 0) {
        void* pOld = *(void**)((char*)pCreature + 0xc0);
        *(uint8_t*)((char*)pCreature + 0xbd) = 0;
        {
            void* pNew = ((void*(__thiscall*)(void*, void*))(*(void***)pSelf->mpModelFactory_120)[0x2c / 4])(pSelf->mpModelFactory_120, (void*)0x01695374);
            ((void(__thiscall*)(void*, void*))(*(void***)pOld)[0x38 / 4])(pOld, pNew);
        }
    }
    return pCreature;
}

// ===========================================================================
// @ 0x00c8e650  cTribe::GetPlayer
// ===========================================================================
int* __fastcall Tribe_GetPlayer(Tribe* pSelf)
{
    NounMgr* pNM = (NounMgr*)Sub_b3d300();
    if (pNM->GetPlayerTribe() == (int*)pSelf) {
        return ((NounMgr*)Sub_b3d300())->GetCurrentTerrainSphere();
    }
    return 0;
}

// ===========================================================================
// @ 0x00c8e680  vcall slot 0x9c(arg, 1)
// ===========================================================================
void __fastcall F8e680(void* pSelf, int, int nArg)
{
    void** pVt = *(void***)pSelf;
    ((SlotVoid2)pVt[0x9c / 4])(pSelf, nArg, 1);
}

// ===========================================================================
// @ 0x00c8e6d0  truncating int cast of member float
// ===========================================================================
int __fastcall F8e6d0(void* pSelf)
{
    float f = ((const Cee380*)((char*)pSelf + 0x20c))->Get();
    return (int)f;
}

// ===========================================================================
// @ 0x00c8e720  call 0xc00b00(0, arg)
// ===========================================================================
void __stdcall F8e720(int nArg)
{
    Sub_c00b00(0, nArg);
}

// ===========================================================================
// @ 0x00c8e730  cTribe editor-mode setter
// ===========================================================================
void __fastcall Tribe_SetEditorMode(Tribe* pSelf, int, uint8_t bMode)
{
    if (bMode != pSelf->mbEditorMode_556) {
        if (bMode == 1) {
            int* pObj = Sub_b3d240();
            void* pName = ((void*(__thiscall*)(void*, void*))(*(void***)pSelf->mpModelFactory_120)[0x2c / 4])(pSelf->mpModelFactory_120, (void*)0x0169543c);
            ((void(__thiscall*)(int*, int, void*))(*(void***)pObj)[0x60 / 4])(pObj, 0x1046f5ef, pName);
            int* pIter = Sub_cee330((char*)pSelf + 0x20c);
            while (pIter != 0) {
                void* pA = Sub_ac79d0(Sub_b3d2b0());
                Sub_ac7de0((void*)pIter, pA);
                pIter = Sub_cee330((char*)pSelf + 0x20c);
            }
        }
        pSelf->mbEditorMode_556 = bMode;
    }
}

// ===========================================================================
// @ 0x00c8e830  set table entry
// ===========================================================================
void __fastcall F8e830(Tribe* pSelf, int, void* pValue, int nIndex)
{
    *(void**)((char*)pSelf + 0x18cc + nIndex * 4) = pValue;
}

// ===========================================================================
// @ 0x00c8e850  grid flag A
// ===========================================================================
bool __fastcall F8e850(Tribe* pSelf)
{
    void* pGrid = pSelf->mpGrid_18cc;
    if (pGrid != 0) {
        return *(unsigned int*)((char*)pGrid + 0x60c) > 0u;
    }
    return false;
}

// ===========================================================================
// @ 0x00c8e870  grid flag B
// ===========================================================================
bool __fastcall F8e870(Tribe* pSelf)
{
    void* pGrid = pSelf->mpGrid_18cc;
    if (pGrid != 0) {
        return *(unsigned int*)((char*)pGrid + 0x608) > 0u;
    }
    return false;
}

// ===========================================================================
// @ 0x00c8e890  read table row (kind, out6)
// ===========================================================================
void __fastcall F8e890(Tribe* pSelf, int, Vec6* pOut, unsigned int nKind, int)
{
    int nRow;
    if (nKind == 7) {
        nRow = 0;
    } else if (nKind == 8) {
        nRow = 1;
    } else if (nKind == 9) {
        nRow = 2;
    } else {
        pOut->w[0] = 0;
        pOut->w[1] = 0;
        pOut->w[2] = 0;
        pOut->w[3] = 0xffffffff;
        pOut->w[4] = 0;
        pOut->w[5] = 0;
        return;
    }
    Vec6* pRow = &pSelf->mSegmentTable_1868[nRow];
    pOut->w[0] = pRow->w[0];
    pOut->w[1] = pRow->w[1];
    pOut->w[2] = pRow->w[2];
    pOut->w[3] = pRow->w[3];
    pOut->w[4] = pRow->w[4];
    pOut->w[5] = pRow->w[5];
}

// ===========================================================================
// @ 0x00c8e930  combined relation check
// ===========================================================================
bool __fastcall F8e930(Tribe* pSelf, int, int* pArg)
{
    Grid* pGrid = (Grid*)pSelf->mpGrid_18cc;
    if (pGrid != 0 && pGrid->HasA()) {
        if (((const RelCheckA*)pArg)->Check()) {
            return true;
        }
    }
    if (pSelf->mpGrid_18cc != 0 && pGrid->HasB()) {
        if (((const RelCheckB*)pArg)->Check()) {
            return true;
        }
    }
    return false;
}

// ===========================================================================
// @ 0x00c8e990  relation state (1/2/3)
// ===========================================================================
uint32_t __fastcall F8e990(Tribe* pSelf)
{
    Grid* pGrid = (Grid*)pSelf->mpGrid_18cc;
    if (pGrid != 0 && pGrid->HasA()) {
        if (!(pGrid != 0 && pGrid->HasB())) {
            return 1;
        }
    }
    if (!(pGrid != 0 && pGrid->HasB())) {
        return 3;
    }
    if (pGrid != 0 && pGrid->HasA()) {
        return 3;
    }
    return 2;
}

// ===========================================================================
// @ 0x00c8e9f0  relation status id (0x268e/0x268d/0x268f)
// ===========================================================================
uint32_t __fastcall F8e9f0(Tribe* pSelf)
{
    Grid* pGrid = (Grid*)pSelf->mpGrid_18cc;
    if (pGrid != 0 && pGrid->HasB()) {
        if (pGrid != 0 && pGrid->HasA()) {
            return 0x268f;
        }
        return 0x268d;
    }
    return 0x268e;
}

// ===========================================================================
// @ 0x00c8ea70  pop-cap table lookup
// ===========================================================================
void* __cdecl F8ea70(unsigned int nSlot)
{
    if (nSlot - 1 <= 0x1e) {
        int nTerrain = ((TerrainSphere*)((NounMgr*)Sub_b3d300())->GetCurrentTerrainSphere())->GetSubIndex();
        return (char*)0x01695458 + (nTerrain * 0x20 + (int)nSlot) * 0xb8;
    }
    int nTerrain = ((TerrainSphere*)((NounMgr*)Sub_b3d300())->GetCurrentTerrainSphere())->GetSubIndex();
    return (char*)0x01695458 + nTerrain * 0x1700;
}

// ===========================================================================
// @ 0x00c8eae0  cTribe::GetMaxPopulation
// ===========================================================================
int __fastcall Tribe_GetMaxPopulation(Tribe* pSelf)
{
    if (pSelf->mPopSlot_550 > 0u && pSelf->mPopSlot_550 < 0x20) {
        int nTerrain = ((TerrainSphere*)((NounMgr*)Sub_b3d300())->GetCurrentTerrainSphere())->GetSubIndex();
        return *(int*)((char*)0x01695460
                       + (nTerrain * 0x20 + (int)pSelf->mPopSlot_550) * 0xb8);
    }
    {
        void* pIface = (char*)pSelf + 0x120;
        if (((char(__thiscall*)(void*))(*(void***)pIface)[0x58 / 4])(pIface) != 0) {
            return Sub_c00ad0(pSelf->GetPopulationId());
        }
    }
    return Sub_c00ad0(2);
}

// ===========================================================================
// @ 0x00c8eb50  read grid position vector (out3)
// ===========================================================================
bool __fastcall F8eb50(Tribe* pSelf, int, Vec3* pOut)
{
    Grid* pGrid = (Grid*)pSelf->mpGrid_18cc;
    if (pGrid != 0) {
        *pOut = pGrid->mPos;
        return true;
    }
    return false;
}

// ===========================================================================
// @ 0x00c8eb90  cTribe relation check against player
// ===========================================================================
bool __fastcall F8eb90(Tribe* pSelf)
{
    int* pPlayer = ((NounMgr*)Sub_b3d300())->GetPlayerTribe();
    if ((int*)pSelf == pPlayer) {
        return false;
    }
    {
        unsigned int a = ((unsigned int(__thiscall*)(int*, int))(*(void***)pPlayer)[0x4c / 4])(pPlayer, 1);
        unsigned int b = ((unsigned int(__thiscall*)(void*, unsigned int))(*(void***)pSelf)[0x4c / 4])(pSelf, a);
        int nRes = Sub_b3d2c0()->GetRelation((int)b);
        return nRes != 4;
    }
}

// ===========================================================================
// @ 0x00c8ebe0  set population flag bit
// ===========================================================================
void __fastcall F8ebe0(Tribe* pSelf, int, unsigned int nBit)
{
    pSelf->mpRel_19d8 |= 1u << nBit;
}

// ===========================================================================
// @ 0x00c8ec00  test population flag bit
// ===========================================================================
bool __fastcall F8ec00(Tribe* pSelf, int, unsigned int nBit)
{
    uint32_t nFlags = pSelf->mpRel_19d8;
    uint32_t nMask = 1u << nBit;
    return (nFlags & nMask) != 0;
}
