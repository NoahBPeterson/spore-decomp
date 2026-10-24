// Slice s0103fe90 - SP::cSPSpaceTrading / SP::cSpaceRelationshipTuning rail.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

struct Vec3 { float x, y, z; };

#define VFN(obj, off) (*(void**)((char*)(*(void**)obj) + (off)))

#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);

// ---------------------------------------------------------------------------------------------
// leaf helpers (cdecl) - named FUN_<va> so the resolver maps them by hex
// ---------------------------------------------------------------------------------------------
extern "C" void* __cdecl FUN_0067de30(void);                       // 0x0067de30 SP::PropertyManager
// FUN_004548d0 (SpVector<Vector3>::reserve) is a __thiscall member of SpVec3 (declared below).
extern "C" void  __cdecl FUN_00f47380(void* p);                    // 0x00f47380 operator_delete_array
extern "C" void* __cdecl FUN_00f473a0(int size, const char* file, int a, int b, const char* c, int d); // 0x00f473a0 operator_new
extern "C" void* __stdcall FUN_00b3d2a0(void* a);                  // 0x00b3d2a0 SP::StarManager
extern "C" float __cdecl FUN_010307a0(void* p, int a, int b);      // 0x010307a0
extern "C" void  __cdecl FUN_006a1250(void* obj, int key, void* out); // 0x006a1250 SP::GetPropertyAsKey
extern "C" void  __cdecl FUN_00571db0(void* server, void* handler, void* ids, int count, int prio); // 0x00571db0 EA::Messaging::RemoveHandler
extern "C" void  __cdecl FUN_0011e07ef(void* fn);                  // 0x011e07ef lib_crt::atexit
extern "C" void* __cdecl FUN_01021260(void);                       // 0x01021260 cSPLivingUniverse::GetActivePlanet
extern "C" void* __cdecl FUN_01021300(void);                       // 0x01021300 cSPLivingUniverse::GetPlayerEmpire
extern "C" void  __cdecl FUN_0103fc10(void* a, void* b);           // 0x0103fc10 AddCommodityToInventory
extern "C" void* __cdecl FUN_0103be80(void* a, void* b, void* c);  // 0x0103be80 eastl move construct
extern "C" void* __cdecl FUN_0103c8a0(void* a, void* b, void* c);  // 0x0103c8a0
extern "C" void* __cdecl FUN_0103c8f0(void* a, void* b, void* c);  // 0x0103c8f0
extern "C" void  __cdecl FUN_005cf7f0(void* a, void* b, void* c);  // 0x005cf7f0 eastl move commit
extern "C" void  __cdecl FUN_006606a0(void* a);                    // 0x006606a0
extern "C" void* __cdecl FUN_006609a0(void* a);                    // 0x006609a0 KeyVec::operator=
extern "C" void* __cdecl FUN_00b3d300(void);                       // 0x00b3d300 SP::NounManager
extern "C" void* __cdecl FUN_00ac9310(void* a, void* b, int c);    // 0x00ac9310
extern "C" void* __cdecl FUN_00b3d2c0(void* a);                    // 0x00b3d2c0 SP::RelationshipManager
extern "C" void* __cdecl FUN_00b3d3e0(int a, int b, int c, int d, int e, int f); // 0x00b3d3e0 SP::EventLog
extern "C" void* __cdecl FUN_00b8dad0(void);                       // 0x00b8dad0
extern "C" void* __cdecl FUN_00675250(int a, int b);               // 0x00675250 Achievements::Controller
extern "C" void* __cdecl FUN_00bd81f0(float f);                    // 0x00bd81f0
extern "C" void* __cdecl FUN_00ffbe50(int a, int b);               // 0x00ffbe50 SP::GetUFOSimulator
extern "C" void  __cdecl FUN_00ff5270(void* a, float b, void* c);  // 0x00ff5270 SP::DoCommunityReaction
extern "C" void  __cdecl FUN_013caa00(void);                       // 0x013caa00 static dtor
extern "C" void  __cdecl FUN_00cd7d10(void);                       // 0x00cd7d10
extern "C" void  __cdecl FUN_00d3d420(void);                       // 0x00d3d420
extern "C" void  __cdecl FUN_00acdff0(void);                       // 0x00acdff0
extern "C" void  __cdecl FUN_00b1e500(void);                       // 0x00b1e500

extern uint32_t  DAT_016df524;               // 0x016df524 static cRegNode object
extern uint32_t  DAT_016df538;               // 0x016df538 static guard
extern uint32_t  DAT_018c43e8;               // 0x018c43e8
extern const char aSimulator[];              // 0x013f09b4 "Simulator"
extern const char DAT_013ebb38[];            // 0x013ebb38 EASTL allocator.h path

extern uint32_t  vtbl_01499b0c[];            // 0x01499b0c static vtable
extern uint32_t  vtbl_01499cac[];            // 0x01499cac SP::cSpaceRelationshipTuning vtable
extern uint32_t  vtbl_013eb394[];            // 0x013eb394 vtbl_Skinner::PaintSystem
extern float     DAT_014853bc;               // 0x014853bc
extern float     _HK_REAL_ONE;               // 0x01485720
extern float     DAT_01473c70;               // 0x01473c70
extern float     DAT_013ec5b4;               // 0x013ec5b4 1000.0f
extern float     DAT_013eb960;               // 0x013eb960 0.01f

// ---------------------------------------------------------------------------------------------
// thiscall leaf callees, declared on a host so `this` travels in ecx
// ---------------------------------------------------------------------------------------------
class tHost {
public:
    void  __thiscall FUN_00692f60(int a);                    // 0x00692f60 cRegNode::Construct
    char  __thiscall FUN_00ab30c0();                         // 0x00ab30c0
    void  __thiscall FUN_00692850();                         // 0x00692850
    void* __thiscall FUN_00baf700();                         // 0x00baf700
    void  __thiscall FUN_00733030(void* a, void* b);         // 0x00733030
    void* __thiscall FUN_00c71e30();                         // 0x00c71e30
    void* __thiscall FUN_00f67d90();                         // 0x00f67d90 GetCurrentTerrainSphere
    char  __thiscall FUN_00c75650();                         // 0x00c75650 cTerrainSphere::Check
    void  __thiscall FUN_00bdbf10();                         // 0x00bdbf10
    void  __thiscall FUN_00ff0350(float f);                  // 0x00ff0350 cCityData::AddValue
    void  __thiscall FUN_00fffdd0(int a, int b);             // 0x00fffdd0
    void* __thiscall FUN_00d06240(void* a);                  // 0x00d06240 cRelationshipManager::RecordEvent
    void  __thiscall FUN_00dd8640(int a, int b, int c, int d, int e, int f); // 0x00dd8640 PostFeedbackEvent
    void  __thiscall FUN_00676e90(int a, int b);             // 0x00676e90 Achievements::AutoTest
    void* __thiscall FUN_00b21340(void* a, void* b, void* c, void* d, void* e); // 0x00b21340 GetGameDataVector
};

// ---------------------------------------------------------------------------------------------
// small unnamed classes
// ---------------------------------------------------------------------------------------------
class cSpaceTuning {
public:
    uint8_t m00[0x50];           // +0x50 float parameter lives in another view; pad 0x00..0x50
    float   m50;                 // +0x50
    uint8_t m54[0x40];           // +0x54 -> +0x94
    int     m94;                 // +0x94
    uint8_t m98[4];              // +0x98
    float   m9c;                 // +0x9c

    int   __thiscall FUN_010407d0(void* param);
    float __thiscall FUN_01040820(float param);
    uint32_t __thiscall FUN_01040870();
};

class cSpaceTuningInit {
public:
    uint32_t m00;                // +0x00
    uint32_t m04;                // +0x04
    uint32_t m08;                // +0x08
    uint32_t m0c;                // +0x0c
    uint32_t m10;                // +0x10
    uint32_t m14;                // +0x14
    float    m18;                // +0x18
    float    m1c;                // +0x1c
    float    m20;                // +0x20
    float    m24;                // +0x24
    float    m28;                // +0x28
    float    m2c;                // +0x2c
    float    m30;                // +0x30
    float    m34;                // +0x34
    float    m38;                // +0x38
    uint8_t  m3c;                // +0x3c
    uint8_t  m3d;                // +0x3d
    uint8_t  m3e[2];             // +0x3e
    float    m40;                // +0x40
    float    m44;                // +0x44
    float    m48;                // +0x48
    float    m4c;                // +0x4c
    uint8_t  m50;                // +0x50
    uint8_t  m51;                // +0x51
    uint8_t  m52;                // +0x52

    cSpaceTuningInit* __thiscall FUN_01040730();
};

class PaintSystem {
public:
    virtual ~PaintSystem() {}
    virtual void _v01();
};

class cSpaceRelationshipTuning : public PaintSystem {
public:
    void* mpServer;              // +0x04
    void* mpHandler;             // +0x08
    void* mpIdArray;             // +0x0c
    int   mnIdArrayCount;        // +0x10
    int   mnPriority;            // +0x14
    void* mPropList;             // +0x18
    void* mUIPropList;           // +0x1c

    void __thiscall FUN_010408f0();
    virtual ~cSpaceRelationshipTuning();
};

class SpVec24 {
public:
    void* mBegin;                // +0x00
    void* mEnd;                  // +0x04
    void* mCap;                  // +0x08
    void __thiscall FUN_01040090(void* dst, void* src);
};

class SpVec3 {
public:
    void* mBegin;                // +0x00
    void* mEnd;                  // +0x04
    void* mCap;                  // +0x08
    void* __thiscall FUN_0050f740(void* a, void* b);
    void  __thiscall FUN_004548d0(int n);   // 0x004548d0 reserve
    void  __thiscall FUN_004e3e10(void* a, void* b); // 0x004e3e10 SPVector<Key>::DoInsertKey
};

class cSPSpaceTrading {
public:
    void*    mpVfptr;            // +0x000
    uint8_t  m004[0x1c];         // +0x004
    SpVec3   mVec20;             // +0x020
    uint8_t  m02c[8];            // +0x02c
    SpVec3   mVec34;             // +0x034
    uint8_t  m040[0x70];         // +0x040 -> +0x0b0
    SpVec3   mVecB0;             // +0x0b0
    SpVec24  mVecBC;             // +0x0bc
    uint8_t  m0c8[0x570];        // +0x0c8 -> +0x638
    void*    m638;               // +0x638
    void*    m63c;               // +0x63c
    uint8_t  m640[0xc];          // +0x640 -> +0x64c
    int      m64c;               // +0x64c
    int      m650;               // +0x650
    int      m654;               // +0x654

    void __thiscall FUN_01040220();
    void __thiscall FUN_01040610();
    void __thiscall FUN_010406d0();
    static void __cdecl CollectSpicePile(void* param_1, void* param_2);
};

// =============================================================================================
// 0x0103fe90 SP::cSPSpaceTrading::CollectSpicePile
// =============================================================================================
// @ 0x0103fe90
void __cdecl cSPSpaceTrading::CollectSpicePile(void* param_1, void* param_2)
{
    (void)param_1;
    cSPSpaceTrading* self = (cSPSpaceTrading*)param_2;

    int local_c = self->m64c;
    int local_8 = self->m650;
    int local_4 = self->m654;
    void* piVar1 = (void*)&self->m638;

    FUN_0103fc10((void*)&local_c, self->m638);
    void* ebx = FUN_01021260();
    void* pcVar4 = FUN_00b3d300();
    void* iVar5 = (void*)((tHost*)pcVar4)->FUN_00b21340((void*)FUN_00cd7d10,
                       (void*)FUN_00d3d420, (void*)FUN_00acdff0, (void*)FUN_00b1e500, (void*)&DAT_018c43e8);
    void* uVar6 = ((void*(__thiscall*)(void*))VFN((void*)&self->mVec34, 0x2c))((void*)&self->mVec34);
    void* piVar7 = FUN_00ac9310((char*)iVar5 + 4, uVar6, (int)((uint32_t)param_2 & 0xffffff00u));

    if (piVar7 != 0) {
        void* iVar5b = ((tHost*)ebx)->FUN_00c71e30();
        void* iVar8 = FUN_01021300();
        if (iVar5b != iVar8) {
            void* pcVar9 = FUN_00b3d300();
            void* sphere = ((tHost*)pcVar9)->FUN_00f67d90();
            char cVar3 = ((tHost*)sphere)->FUN_00c75650();
            if (cVar3 == 0) {
                void* uVar10 = ((void*(__thiscall*)(void*, int))VFN(piVar7, 0x4c))(piVar7, 0x526e5d8);
                void* rel = FUN_00b3d2c0(uVar10);
                float fVar13 = *(float*)&uVar10;
                fVar13 = *(float*)&uVar10;
                (void)rel;
                ((tHost*)rel)->FUN_00d06240((void*)0x3f800000);
                ((tHost*)piVar7)->FUN_00bdbf10();
                void* uVar6c = ((void*(__thiscall*)(void*))VFN(((char*)piVar7 + 0x120), 0x2c))((char*)piVar7 + 0x120);
                FUN_00ff5270(piVar7, fVar13, uVar6c);
            }
            void* pcVar11 = FUN_00b3d3e0(0x70983f0e, 0x131a9f54, 0, 0, 1, 0);
            ((tHost*)pcVar11)->FUN_00dd8640(0x70983f0e, 0x131a9f54, 0, 0, 1, 0);
            local_c = 0; local_8 = 0; local_4 = 0;
            FUN_006a1250(self->m63c, 0x34f1a4f, &local_c);
            if (local_c == 0x82af541) {
                void* pCVar12 = FUN_00675250(0x7c1a0684, 1);
                ((tHost*)pCVar12)->FUN_00676e90(0x7c1a0684, 1);
            }
        }
        local_8 = self->m650;
        int iVar5c = self->m64c;
        int iVar8c = self->m654;
        void* piVar7b = FUN_00b8dad0();
        if (((int*)piVar7b)[0] == iVar5c && ((int*)piVar7b)[1] == local_8 && ((int*)piVar7b)[2] == iVar8c) {
            float fVar18 = (float)*(int*)piVar1;
            if (*(int*)piVar1 < 0) {
                fVar18 = fVar18 + 4294967296.0f;
            }
            fVar18 = -fVar18;
            void* r1 = FUN_00bd81f0(fVar18);
            ((tHost*)r1)->FUN_00ff0350(fVar18);
            int iVar5d = *(int*)piVar1;
            void* r2 = FUN_00ffbe50(1, iVar5d);
            ((tHost*)r2)->FUN_00fffdd0(1, iVar5d);
        }
    }
}

// =============================================================================================
// 0x01040090 SpVec24::FUN_01040090  (SpVector<0x24-byte element> insert)
// =============================================================================================
// @ 0x01040090
void __thiscall SpVec24::FUN_01040090(void* dst, void* src)
{
    void* end = mEnd;
    if (end != mCap) {
        void* d = dst;
        if (d <= src && src < end) {
            src = (char*)src + 0x24;
        }
        if (end != 0) {
            *(uint32_t*)end = *(uint32_t*)((char*)end - 0x24);
            *(uint32_t*)((char*)end + 4) = *(uint32_t*)((char*)end - 0x20);
            *(uint32_t*)((char*)end + 8) = *(uint32_t*)((char*)end - 0x1c);
            *(uint32_t*)((char*)end + 0xc) = *(uint32_t*)((char*)end - 0x18);
            FUN_006606a0((char*)end - 0x14);
        }
        FUN_0103c8f0(d, (char*)mEnd - 0x24, mEnd);
        *(uint32_t*)d = *(uint32_t*)src;
        *(uint32_t*)((char*)d + 4) = *(uint32_t*)((char*)src + 4);
        *(uint32_t*)((char*)d + 8) = *(uint32_t*)((char*)src + 8);
        *(uint32_t*)((char*)d + 0xc) = *(uint32_t*)((char*)src + 0xc);
        FUN_006609a0((char*)src + 0x10);
        mEnd = (char*)mEnd + 0x24;
        return;
    }

    int count = (int)((char*)end - (char*)mBegin) / 0x24;
    int cap;
    void* buf;
    if (count == 0) {
        cap = 1;
        buf = FUN_00f473a0(cap * 0x24, aSimulator, 0, 0, DAT_013ebb38, 0xd1);
    } else {
        cap = count * 2;
        if (cap == 0) {
            buf = 0;
        } else {
            buf = FUN_00f473a0(cap * 0x24, aSimulator, 0, 0, DAT_013ebb38, 0xd1);
        }
    }
    void* base = mBegin;
    void* p = FUN_0103be80(base, dst, buf);
    FUN_005cf7f0(base, dst, buf);
    if (p != 0) {
        *(uint32_t*)p = *(uint32_t*)src;
        *(uint32_t*)((char*)p + 4) = *(uint32_t*)((char*)src + 4);
        *(uint32_t*)((char*)p + 8) = *(uint32_t*)((char*)src + 8);
        *(uint32_t*)((char*)p + 0xc) = *(uint32_t*)((char*)src + 0xc);
        FUN_006606a0((char*)src + 0x10);
    }
    void* e2 = mEnd;
    void* r = FUN_0103be80(dst, e2, (char*)p + 0x24);
    FUN_005cf7f0(dst, e2, (char*)p + 0x24);
    if (mBegin != 0 && *(int*)((char*)mBegin - 4) != 0) {
        FUN_00f47380(mBegin);
    }
    mEnd = r;
    mBegin = buf;
    mCap = (char*)buf + cap * 0x24;
}

// =============================================================================================
// 0x01040220 cSPSpaceTrading::FUN_01040220
// =============================================================================================
// @ 0x01040220
void __thiscall cSPSpaceTrading::FUN_01040220()
{
    int n = (int)((char*)mVec34.mEnd - (char*)mVec34.mBegin) / 0xc;
    void* local_4c = 0;
    int local_30[3];
    local_30[0] = 0; local_30[1] = 0; local_30[2] = 0;

    void* oldEnd = mVecBC.mEnd;
    void* r = FUN_0103c8a0(oldEnd, oldEnd, mVecBC.mBegin);
    ((tHost*)&mVecBC)->FUN_00733030(r, mVecBC.mEnd);
    mVecBC.mEnd = (char*)mVecBC.mEnd - ((int)((char*)oldEnd - (char*)mVecBC.mBegin) / 0x24) * 0x24;

    if (n > 0) {
        for (int pass = 0; pass < 2; pass++) {
            int key = (pass == 0) ? (int)0x7ecbe6f5 : (int)0xeb1a8062;
            for (int i = 0; i < n; i++) {
                uint8_t* elem = (uint8_t*)mVec34.mBegin + i * 0xc;
                uint32_t elemId = *(uint32_t*)elem;
                void* pm = FUN_0067de30();
                if (local_4c != 0) {
                    void* old = local_4c;
                    local_4c = 0;
                    ((void(__thiscall*)(void*))VFN(old, 4))(old);
                }
                ((void(__thiscall*)(void*, uint32_t, int, void**))VFN(pm, 0x2c))(pm, elemId, 0x34d97fa, &local_4c);
                FUN_006a1250(local_4c, 0x34f1a4f, local_30);
                if (local_30[0] != key) continue;

                int val = 0;
                if (local_4c != 0) {
                    void* tmp = 0;
                    char c = ((char(__thiscall*)(void*, int, void**))VFN(local_4c, 0x24))(local_4c, 0x3c72dc6, &tmp);
                    if (c != 0 && *(uint16_t*)((char*)tmp + 0x12) == 9) {
                        void* t = tmp;
                        if ((*(uint8_t*)((char*)tmp + 0x10) & 0x30) != 0) {
                            t = *(void**)tmp;
                        }
                        val = *(int*)t;
                    }
                }

                int cnt = (int)((char*)mVecBC.mEnd - (char*)mVecBC.mBegin) / 0x24;
                if (pass == 0) {
                    int idx;
                    for (idx = 0; idx < cnt; idx++) {
                        if (*(int*)((char*)mVecBC.mBegin + idx * 0x24 + 0xc) == val) break;
                    }
                    if (idx >= cnt) {
                        uint8_t* base = (uint8_t*)mVecBC.mEnd;
                        if (mVecBC.mEnd < mVecBC.mCap) {
                            mVecBC.mEnd = base + 0x24;
                        } else {
                            uint8_t tmpItem[0x24];
                            *(uint32_t*)(tmpItem + 0x00) = 0;
                            *(uint32_t*)(tmpItem + 0x04) = 0;
                            *(uint32_t*)(tmpItem + 0x08) = 0;
                            *(uint32_t*)(tmpItem + 0x10) = 0;
                            *(uint32_t*)(tmpItem + 0x14) = 0;
                            *(uint32_t*)(tmpItem + 0x18) = 0;
                            mVecBC.FUN_01040090(mVecBC.mEnd, tmpItem);
                            base = (uint8_t*)mVecBC.mEnd - 0x24;
                        }
                        *(uint32_t*)(base + 0x00) = 0;
                        *(uint32_t*)(base + 0x04) = 0;
                        *(uint32_t*)(base + 0x08) = 0;
                        *(uint32_t*)(base + 0x10) = 0;
                        *(uint32_t*)(base + 0x14) = 0;
                        *(uint32_t*)(base + 0x18) = 0;
                        *(int*)(base + 0x0c) = val;
                    }
                    uint8_t* item = (uint8_t*)mVecBC.mBegin + idx * 0x24;
                    SpVec3* sub = (SpVec3*)(item + 0x10);
                    if (sub->mEnd < sub->mCap) {
                        uint8_t* e = (uint8_t*)sub->mEnd;
                        sub->mEnd = e + 0xc;
                        *(uint32_t*)(e + 0) = *(uint32_t*)elem;
                        *(uint32_t*)(e + 4) = *(uint32_t*)(elem + 4);
                        *(uint32_t*)(e + 8) = *(uint32_t*)(elem + 8);
                    } else {
                        sub->FUN_004e3e10(sub->mEnd, elem);
                    }
                } else {
                    for (int j = 0; j < cnt; j++) {
                        uint8_t* item = (uint8_t*)mVecBC.mBegin + j * 0x24;
                        if (*(int*)(item + 0xc) == val) {
                            *(uint32_t*)(item + 0x00) = *(uint32_t*)elem;
                            *(uint32_t*)(item + 0x04) = *(uint32_t*)(elem + 4);
                            *(uint32_t*)(item + 0x08) = *(uint32_t*)(elem + 8);
                        }
                    }
                }
            }
        }
    }
    if (local_4c != 0) {
        void* o = local_4c;
        ((void(__thiscall*)(void*))VFN(o, 4))(o);
    }
}

// =============================================================================================
// 0x01040610 cSPSpaceTrading::FUN_01040610  (RefreshCommodities)
// =============================================================================================
// @ 0x01040610
void __thiscall cSPSpaceTrading::FUN_01040610()
{
    mVec34.FUN_0050f740(mVec34.mBegin, mVec34.mEnd);
    mVec20.FUN_0050f740(mVec20.mBegin, mVec20.mEnd);

    void* local[3];
    local[0] = 0; local[1] = 0; local[2] = 0;
    void* pm = FUN_0067de30();
    ((void(__thiscall*)(void*, int, void**))VFN(pm, 0x48))(pm, 0x34d97fa, local);

    int n = (int)((char*)local[1] - (char*)local[0]) >> 2;
    mVec34.FUN_004548d0(n);
    for (int i = 0; i < n; i++) {
        uint32_t* puVar2 = (uint32_t*)((char*)mVec34.mBegin + i * 0xc);
        puVar2[0] = ((uint32_t*)local[0])[i];
        puVar2[1] = 0;
        puVar2[2] = 0;
    }
    FUN_01040220();
    if (local[0] != 0 && *(int*)((char*)local[0] - 4) != 0) {
        FUN_00f47380(local[0]);
    }
}

// =============================================================================================
// 0x010406d0 cSPSpaceTrading::InitGonzagoSubsystem
// =============================================================================================
// @ 0x010406d0
void __thiscall cSPSpaceTrading::FUN_010406d0()
{
    FUN_01040610();
    if ((DAT_016df538 & 1) == 0) {
        DAT_016df538 |= 1;
        ((tHost*)&DAT_016df524)->FUN_00692f60(0);
        DAT_016df524 = (uint32_t)vtbl_01499b0c;
        FUN_0011e07ef((void*)FUN_013caa00);
    }
    if (((tHost*)&DAT_016df524)->FUN_00ab30c0() == 0) {
        ((tHost*)&DAT_016df524)->FUN_00692850();
    }
}

// =============================================================================================
// 0x01040730 cSpaceTuningInit::FUN_01040730
// =============================================================================================
// @ 0x01040730
cSpaceTuningInit* __thiscall cSpaceTuningInit::FUN_01040730()
{
    float one = _HK_REAL_ONE;
    m24 = DAT_014853bc;
    m2c = DAT_01473c70;
    m00 = 0;
    m04 = 0;
    m08 = 0;
    m0c = 0;
    m10 = 0;
    m14 = 1;
    m18 = one;
    m1c = one;
    m20 = one;
    m28 = one;
    m30 = one;
    m34 = one;
    m38 = 0.0f;
    m3c = 0;
    m3d = 0;
    m40 = one;
    m44 = one;
    m48 = 0.0f;
    m4c = 0.0f;
    m50 = 0;
    m51 = 0;
    m52 = 0;
    return this;
}

// =============================================================================================
// 0x010407d0 cSpaceTuning::FUN_010407d0
// =============================================================================================
// @ 0x010407d0
int __thiscall cSpaceTuning::FUN_010407d0(void* param)
{
    void* p = FUN_00b3d2a0(param);
    void* q = ((tHost*)p)->FUN_00baf700();
    float r = FUN_010307a0(q, 0x68d6965, 0x68d696b);
    float f = (float)m94 * r;
    return (int)(f * DAT_013eb960) * 100;
}

// =============================================================================================
// 0x01040820 cSpaceTuning::FUN_01040820
// =============================================================================================
// @ 0x01040820
float __thiscall cSpaceTuning::FUN_01040820(float param)
{
    if (m50 > param) {
        return 0.0f;
    }
    return 1.0f;
}

// =============================================================================================
// 0x01040870 cSpaceTuning::FUN_01040870
// =============================================================================================
// @ 0x01040870
uint32_t __thiscall cSpaceTuning::FUN_01040870()
{
    return (uint32_t)(m9c * DAT_013ec5b4);
}

// =============================================================================================
// 0x010408f0 cSpaceRelationshipTuning::FUN_010408f0
// =============================================================================================
// @ 0x010408f0
void __thiscall cSpaceRelationshipTuning::FUN_010408f0()
{
    if (mPropList != 0) {
        void* p = mPropList;
        mPropList = 0;
        ((void(__thiscall*)(void*))VFN(p, 4))(p);
    }
    if (mUIPropList != 0) {
        void* p = mUIPropList;
        mUIPropList = 0;
        ((void(__thiscall*)(void*))VFN(p, 4))(p);
    }
    if (mpServer != 0) {
        void* s = mpServer;
        mpServer = 0;
        FUN_00571db0(s, mpHandler, mpIdArray, mnIdArrayCount, mnPriority);
    }
}

// =============================================================================================
// 0x01040950 SP::cSpaceRelationshipTuning::~cSpaceRelationshipTuning
// =============================================================================================
// @ 0x01040950
cSpaceRelationshipTuning::~cSpaceRelationshipTuning()
{
    _ReadWriteBarrier();
    void* ui = *(void* volatile*)&mUIPropList;
    if (ui != 0) {
        ((void(__thiscall*)(void*))VFN(ui, 4))(ui);
    }
    void* pl = *(void* volatile*)&mPropList;
    if (pl != 0) {
        ((void(__thiscall*)(void*))VFN(pl, 4))(pl);
    }
    if (mpServer != 0) {
        void* s = mpServer;
        mpServer = 0;
        FUN_00571db0(s, mpHandler, mpIdArray, mnIdArrayCount, mnPriority);
    }
}