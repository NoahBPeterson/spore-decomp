// src/game/SPGonzago/SPMissionRequisiteParser.cpp -- migrated from slice(s) s00fef140 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionRequisiteParser.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cEmpire.h"
#include "SP/cGameNounManager.h"
#include "SP/cSPMission.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl FUN_0067dcd0();                            // ::EA::ResourceMan::GetManager
extern "C" void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int);
extern "C" void  __cdecl operator_delete_array(void*);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
extern "C" void* __cdecl FUN_00681a10(void*);
#pragma warning(disable : 4100)

// ---- items of slice s00fef140 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  u32;
typedef unsigned char u8;
struct IEmpty {};
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};
struct cReqElem;
struct cReqVec;
void  __cdecl FUN_00fef9f0(u32, void*);
void* __cdecl FUN_00fef810(cReqElem*, cReqElem*, cReqElem*);
cReqElem* __cdecl FUN_00fef6d0(cReqElem*, cReqElem*, cReqElem*);
extern "C" void* __cdecl FUN_0067dcd0();                            // ::EA::ResourceMan::GetManager
extern "C" void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int);
extern "C" void  __cdecl operator_delete_array(void*);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
extern "C" void* __cdecl FUN_00fef7d0(cReqElem*, cReqElem*, cReqElem*);
extern "C" void* __cdecl FUN_00681a10(void*);
struct spVecF {
    float* mpBegin;                                      // +0x00
    float* mpEnd;                                        // +0x04
    u32    mCap;                                         // +0x08
    u32    mAlloc;                                       // +0x0c
    u32    mExtra;                                       // +0x10

    void* FUN_004aa350(int count, u32* alloc);           // 0x004aa350 (ret 8)  allocate
    void  FUN_0050d4e0(spVecF* src);                     // 0x0050d4e0 (ret 4)  operator=
    void  FUN_00fecc40(void* a, void* b);                // 0x00fecc40 (ret 8)
    void* FUN_00fef570(void* a, void* b);                // 0x00fef570 (ret 8)  our target
};
struct cReqElem {
    u32    mField_00;                                    // +0x00
    u32    mField_04;                                    // +0x04
    spVecF mVec_08;                                      // +0x08
    spVecF mVec_1c;                                      // +0x1c
    u32    mField_30;                                    // +0x30
    u32    mField_34;                                    // +0x34

    cReqElem* FUN_00fef730(cReqElem* src);               // 0x00fef730 (ret 4)  copy-construct
};
struct cReqVec {
    cReqElem* mpBegin;                                   // +0x00
    cReqElem* mpEnd;                                     // +0x04
    cReqElem* mpCap;                                     // +0x08

    void FUN_00fef870(cReqElem* pos, cReqElem* val);     // 0x00fef870 (ret 8)
};
struct IResMan : VPad<3, IEmpty> {
    virtual char FUN_0c(u32*, u32*, int, int, int, int); // +0x0c
};
struct cReqHolder {                                      // vector<cReqElem>
    cReqElem* mpBegin;                                   // +0x00
    cReqElem* mpEnd;                                     // +0x04
    cReqElem* mpCap;                                     // +0x08
};
struct cReqSource {
    u8  pad00[0x6c];
    u8* mpBegin;                                         // +0x6c
    u8* mpEnd;                                           // +0x70
};
// ---- items of slice s00fef140 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void* __cdecl FUN_00fef7d0(cReqElem*, cReqElem*, cReqElem*);

// @ 0x00fef6d0
cReqElem* FUN_00fef6d0(cReqElem* a, cReqElem* b, cReqElem* d)
{
    while (a != b) {
        float* p = a->mVec_1c.mpBegin;
        if (p != 0 && *(int*)((u8*)p - 4) != 0)
            operator_delete_array(p);
        p = a->mVec_08.mpBegin;
        if (p != 0 && *(int*)((u8*)p - 4) != 0)
            operator_delete_array(p);
        a = (cReqElem*)((u8*)a + 0x38);
        d = (cReqElem*)((u8*)d + 0x38);
    }
    return d;
}

// @ 0x00fef730
cReqElem* cReqElem::FUN_00fef730(cReqElem* src)
{
    mField_00 = src->mField_00;
    mField_04 = src->mField_04;

    spVecF* v = &mVec_08;
    int count = src->mVec_08.mpEnd - src->mVec_08.mpBegin;
    v->FUN_004aa350(count, &src->mVec_08.mAlloc);
    int bytes = (int)((char*)src->mVec_08.mpEnd - (char*)src->mVec_08.mpBegin);
    v->mpEnd = (float*)((char*)memcpy(v->mpBegin, src->mVec_08.mpBegin, bytes) + (bytes >> 2) * 4);

    spVecF* w = &mVec_1c;
    int count2 = src->mVec_1c.mpEnd - src->mVec_1c.mpBegin;
    w->FUN_004aa350(count2, &src->mVec_1c.mAlloc);
    int bytes2 = (int)((char*)src->mVec_1c.mpEnd - (char*)src->mVec_1c.mpBegin);
    w->mpEnd = (float*)((char*)memcpy(w->mpBegin, src->mVec_1c.mpBegin, bytes2) + (bytes2 >> 2) * 4);

    mField_30 = src->mField_30;
    mField_34 = src->mField_34;
    return this;
}

// @ 0x00fef870
void cReqVec::FUN_00fef870(cReqElem* pos, cReqElem* val)
{
    cReqElem* end = mpEnd;
    if (end != mpCap) {
        if (pos <= val && val < end)
            val = (cReqElem*)((u8*)val + 0x38);
        if (end != 0)
            end->FUN_00fef730((cReqElem*)((u8*)end - 0x38));
        FUN_00fef810(pos, (cReqElem*)((u8*)mpEnd - 0x38), mpEnd);
        pos->mField_00 = val->mField_00;
        pos->mField_04 = val->mField_04;
        pos->mVec_08.FUN_0050d4e0(&val->mVec_08);
        pos->mVec_1c.FUN_0050d4e0(&val->mVec_1c);
        pos->mField_30 = val->mField_30;
        pos->mField_34 = val->mField_34;
        mpEnd = (cReqElem*)((u8*)mpEnd + 0x38);
        return;
    }

    int cnt = (int)(((char*)end - (char*)mpBegin) / 0x38);
    int cap;
    cReqElem* buf;
    if (cnt == 0) {
        cap = 1;
    } else {
        cap = cnt * 2;
        if (cap == 0) {
            buf = 0;
            goto LAB;
        }
    }
    buf = (cReqElem*)operator_new(cap * 0x38, "Simulator", 0, 0,
                                 (const char*)0x13ebb38, 0xd1);
LAB:;
    cReqElem* old = mpBegin;
    cReqElem* r1 = (cReqElem*)FUN_00fef7d0(old, pos, buf);
    FUN_00fef6d0(old, pos, buf);
    if (r1 != 0)
        r1->FUN_00fef730(val);
    cReqElem* oldEnd = mpEnd;
    cReqElem* r2 = (cReqElem*)FUN_00fef7d0(pos, oldEnd, (cReqElem*)((u8*)r1 + 0x38));
    FUN_00fef6d0(pos, oldEnd, (cReqElem*)((u8*)r1 + 0x38));
    if (old != 0 && *(int*)((u8*)old - 4) != 0)
        operator_delete_array(old);
    mpEnd = r2;
    mpBegin = buf;
    mpCap = (cReqElem*)((u8*)buf + cap * 0x38);
}

// @ 0x00fef9f0
void FUN_00fef9f0(u32 param1, void* param2v)
{
    cReqHolder* dst = (cReqHolder*)param2v;
    u32 local_a8 = 0;
    u32 local_a4 = param1;
    u32 local_a0 = 0x55ada24;
    u32 local_9c = 0x2ae1a8e;
    spVecF* vec = (spVecF*)dst;
    vec->FUN_00fef570(vec->mpBegin, vec->mpEnd);
    (void)local_a0; (void)local_9c;

    IResMan* mgr = (IResMan*)FUN_0067dcd0();
    cReqSource* src = 0;
    char ok = mgr->FUN_0c(&local_a4, &local_a8, 0, 0, 0, 0);
    if (ok != 0) {
        u8* it = src->mpBegin;
        u8* end = src->mpEnd;
        while (it != end) {
            FUN_00681a10(&local_a4);
            it += 0x60;
        }
    }
    (void)local_a8;
}
