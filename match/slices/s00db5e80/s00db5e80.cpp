// Slice s00db5e80 : tribe domestication + tribe-vignette decision helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef          int   s32;

// ------------------------------------------------------------------ retail data
#define G1581270       (*(const u32*)0x01581270)
#define G13F9428       (*(const float*)0x013f9428)   // 0.001f
#define G13EBC4C       (*(const float*)0x013ebc4c)   // 60.0f
#define G1485548       (*(const float*)0x01485548)
#define G169F3B8       (*(const float*)0x0169f3b8)
#define G169F3BC       (*(const float*)0x0169f3bc)
#define G169F3C0       (*(const float*)0x0169f3c0)
#define G13EB8A0       (*(const float*)0x013eb8a0)
#define G1485720       (*(const float*)0x01485720)   // _HK_REAL_ONE
#define G147C21C       (*(const float*)0x0147c21c)
#define G147C218       (*(const float*)0x0147c218)   // FLT_MAX, initial nearest-spot distance
#define VTABLE_147C2C4 ((void*)0x0147c2c4)
#define RNG1601760     ((void*)0x01601760)           // EA::Random::RandomLinearCongruential
#define SLIST169B41C   ((void*)0x0169b41c)           // rw::SList singleton

// ------------------------------------------------------------------ indirect-call shapes
typedef void   (__thiscall* FnV0)(void*);
typedef void   (__thiscall* FnV1)(void*, void*);
typedef char   (__thiscall* FnC0)(void*);
typedef u32    (__thiscall* FnU0)(void*);
typedef float  (__thiscall* FnF0)(void*);
typedef void*  (__thiscall* FnP0)(void*);
typedef float* (__thiscall* FnFP0)(void*);
typedef u32    (__thiscall* FnU3)(void*, int, int, int);

struct Cont2                          // { begin, end } pair returned by several containers
{
    char* mBegin;
    char* mEnd;
};

// ------------------------------------------------------------------ direct callees
// Every one of the indirect (ecx) callees below is __thiscall in retail; modelling
// them as members makes cl emit `mov ecx,<this>` plus the same `ret N`.
struct ObjV
{
    void* FUN_00c04590();                        // 0x00c04590  Get() -> herd
    void  FUN_00c045a0(void*);                   // 0x00c045a0  SetHerd
    void* FUN_00c0bbd0();                        // 0x00c0bbd0  GetSpeciesProfile
    void  FUN_00c042e0();                        // 0x00c042e0
    void  FUN_00c0d950(int);                     // 0x00c0d950
    u32   FUN_00c0bc00(void*, u32, int, int);    // 0x00c0bc00
    char  FUN_00c0b770();                        // 0x00c0b770
    char  FUN_00c24560();                        // 0x00c24560
    void* FUN_00c22f50();                        // 0x00c22f50  cSPCreatureCitizen::GetTribe
    char  FUN_00c8e7c0();                         // 0x00c8e7c0
    void* FUN_00c8fee0();                        // 0x00c8fee0
    void  FUN_00c8fef0();                        // 0x00c8fef0  cTribe::InitDomesticatedAnimalsHerd
    void* FUN_00c8e820(int);                     // 0x00c8e820
    char  FUN_00feba90();                        // 0x00feba90  cSPTimer::IsRunning
    long long FUN_00bc3190();                    // 0x00bc3190  cSPTimer::GetElapsedTime
    float FUN_00fc7f80();                        // 0x00fc7f80  GetCost
    int   FUN_00bc2b80(void*);                   // 0x00bc2b80
    int   FUN_00bc3db0(int);                     // 0x00bc3db0
    void* FUN_00bc7610(int, int);                // 0x00bc7610
    u32   FUN_00a68fb0(int);                     // 0x00a68fb0  RandomUint32Uniform
    double FUN_009360d0();                       // 0x009360d0  cRandomGlobal::RandomDouble
    int   FUN_00bca620(u32, void*, void*);       // 0x00bca620  cAgentOrderManager::FindNode
    void* FUN_00d997e0();                        // 0x00d997e0  behavior_stimuli::GetAny
    int   FUN_00d00a70(u32, u32, int);           // 0x00d00a70
    void* FUN_00bfc5f0();                        // 0x00bfc5f0
    void  FUN_00fcc200(u32);                     // 0x00fcc200  rw::SList::SetElementAlignment
    u32   FUN_006766e0(u32);                     // 0x006766e0
    void  FUN_00676710(u32);                     // 0x00676710  AwardAchievement
    void  FUN_0060d860(u32, void*);              // 0x0060d860  UpdateProperty
    void  FUN_00dd8640(u32, u32, void*, int, int, int);  // 0x00dd8640  PostFeedbackEvent
    void  FUN_00cd6980(void*);                   // 0x00cd6980  SignalTribeEvent
    void  FUN_00aea5d0(void*, void*);            // 0x00aea5d0  DoInsertPtr
    // ctor / dtor helpers
    void  FUN_00ac14d0();                        // 0x00ac14d0
    void  FUN_00afba10();                        // 0x00afba10
    void  FUN_00afbad0();                        // 0x00afbad0  cActionCircle::~cActionCircle
    void  FUN_00ad92d0();                        // 0x00ad92d0  eastl vector dtor
    void  FUN_00ac5430();                        // 0x00ac5430  base dtor
    void  FUN_00db5c20(void*, void*);            // 0x00db5c20
    void  FUN_005941f0(void*, void*);            // 0x005941f0
};

// cdecl callees (args cleaned by the caller)
char  __cdecl FUN_00c0d3a0(void*);                       // 0x00c0d3a0
void  __cdecl FUN_00acca00(void*, void**);               // 0x00acca00  spstl::remove_1st
u32   __cdecl FUN_00b6f0c0(u32);                         // 0x00b6f0c0
void* __cdecl FUN_00cd40b0(void*);                       // 0x00cd40b0  cTribeModeStrategy::Instance
void* __cdecl FUN_00b3d4e0(u32);                         // 0x00b3d4e0
void* __cdecl FUN_00bc9b00();                           // 0x00bc9b00  agent-order manager singleton
u8    __cdecl FUN_00da7140(void*, void*);                // 0x00da7140  order-node predicate
float __cdecl FUN_004e1c70(u32, u32, float);             // 0x004e1c70  SP::GetPropertyT<float>
void* __cdecl FUN_00bc30b0(void*);                       // 0x00bc30b0
void* __cdecl FUN_00b3d2c0(void*, void*, int);           // 0x00b3d2c0  RelationshipManager
void* __cdecl FUN_00b3d300();                            // 0x00b3d300  NounManager
void* __cdecl FUN_00675250(u32);                         // 0x00675250  Achievements::Controller
void* __cdecl FUN_0067cb30(u32, void*);                  // 0x0067cb30
void* __cdecl FUN_00e398e0(u32, void*, void*);           // 0x00e398e0
void* __cdecl FUN_00b3d3e0(u32, u32, void*);             // 0x00b3d3e0  EventLog
void  __cdecl FUN_00f47380(void*);                       // 0x00f47380  operator delete

// local eastl-style fixed_vector<int,16> (Also the inline buffer lives at +0x18.)
struct FVecV
{
    u32*  mBegin;        // 0x00
    u32*  mCur;          // 0x04
    u32*  mCap;          // 0x08
    u32*  mFieldC;       // 0x0c
    u32*  mHeapBase;     // 0x10
    u32*  mField14;      // 0x14
    u32   mInline[16];   // 0x18
    void  FUN_004281d0(u32* pos, const u32& v);          // 0x004281d0  DoInsertValue
};

// ------------------------------------------------------------------ functions

// @ 0x00db5e80
char __cdecl FUN_00db5e80(void* creature_, void* tribe_)
{
    char* creature = (char*)creature_;
    char* tribe    = (char*)tribe_;
    u32   evt      = 0xab6fe2a9;
    char  ret      = 0;
    int   count    = 0;
    char* herd;

    herd = (char*)((ObjV*)tribe_)->FUN_00c8fee0();
    if (herd == 0)
    {
        ((ObjV*)tribe_)->FUN_00c8fef0();
        herd = (char*)((ObjV*)tribe_)->FUN_00c8fee0();
        if (herd == 0)
            goto L_c2;
    }
    if ((char*)((ObjV*)creature_)->FUN_00c04590() == herd)
        goto L_c2;

    {
        char* it  = *(char**)(herd + 0x40);
        char* end = *(char**)(herd + 0x44);
        ret = 1;
        if (it != end)
        {
            do
            {
                char* e = *(char**)it;
                if (e[0xb5e] == 0)
                {
                    count++;
                    if (*(float*)(e + 0xb20) == *(float*)(creature + 0xb20))
                        ret = 0;
                }
                it += 4;
            } while (it != end);
            if (ret == 0)
            {
                evt = 0xbea77fd3;
                goto L_c2;
            }
        }
        if (!((u32)count < G1581270))
        {
            evt = 0xab6fe2a9;
            goto L_c2;
        }
    }

    evt = 0x4f7d2332;
    FUN_00c0d3a0(creature_);
    FUN_00acca00((char*)((ObjV*)creature_)->FUN_00c04590() + 0x40, (void**)&creature_);
    ((ObjV*)creature_)->FUN_00c045a0(herd);

    {   // eastl::vector<EA::AutoRefCount<cSPCreatureBase>>::push_back at herd+0x40
        void*  keep = creature_;
        void** pos;
        void*  rel;
        if (creature_ != 0)
            ((FnV0)(*(void***)creature_)[0])(creature_);          // AddRef
        pos = *(void***)(herd + 0x44);
        rel = creature_;
        if (pos < *(void***)(herd + 0x48))
        {
            *(void***)(herd + 0x44) = pos + 1;
            if (pos != 0)
            {
                *pos = creature_;
                if (creature_ != 0)
                    ((FnV0)(*(void***)creature_)[0])(creature_);  // AddRef
            }
        }
        else
        {
            ((ObjV*)(herd + 0x40))->FUN_00aea5d0(pos, &keep);
            rel = keep;
        }
        if (rel != 0)
            ((FnV0)(*(void***)rel)[1])(rel);                      // Release
    }

    ((ObjV*)creature_)->FUN_00c042e0();
    {
        u32 u12 = FUN_00b6f0c0(*(u32*)(tribe + 0x234));
        ((FnV1)(*(void***)creature_)[0xe4 / 4])(creature_, (void*)u12);
        ((ObjV*)creature_)->FUN_00c0d950(1);
        u32 u13 = ((FnU0)(*(void***)tribe_)[0x4c / 4])(tribe_);
        ((FnV1)(*(void***)creature_)[0x48 / 4])(creature_, (void*)u13);
    }
    ((ObjV*)FUN_00cd40b0((void*)0x84f037b0))->FUN_00cd6980((void*)0x84f037b0);

    if (((FnC0)(*(void***)(tribe + 0x120))[0x58 / 4])(tribe + 0x120) != 0)
    {
        u32 n = ((ObjV*)FUN_00675250(0x9073fca4))->FUN_006766e0(0x9073fca4);
        if ((u32)(count + 1) >= n)
            ((ObjV*)FUN_00675250(0x9073fca4))->FUN_00676710(0x9073fca4);

        {
            u32 loc0 = 0;
            u32 loc1 = 0;
            u32 loc2 = 0;
            u32 bc   = ((ObjV*)creature_)->FUN_00c0bc00(&loc0, *(u32*)(tribe + 0x234), 0, 0);
            void* prof = (char*)((ObjV*)creature_)->FUN_00c0bbd0() + 0x504;
            void* r12  = (char*)((ObjV*)tribe_)->FUN_00c8e820(0) + 0x504;
            void* prop;
            FUN_00e398e0(0x7a7d8111, r12, (void*)bc);
            prop = FUN_0067cb30(0x3110f7cf, prof);
            ((ObjV*)prop)->FUN_0060d860(0x3110f7cf, prof);
        }
    }

L_c2:
    if (((FnC0)(*(void***)(tribe + 0x120))[0x58 / 4])(tribe + 0x120) != 0)
    {
        u32   a;
        void* lg;
        ((ObjV*)SLIST169B41C)->FUN_00fcc200(*(u32*)(creature + 0xb20));
        a  = ((FnU3)(*(void***)(creature + 0xc0))[0x2c / 4])(creature + 0xc0, 0, 1, 0);
        lg = FUN_00b3d3e0(evt, 0x182cd6ce, (void*)a);
        ((ObjV*)lg)->FUN_00dd8640(evt, 0x182cd6ce, (void*)a, 0, 1, 0);
    }
    return ret;
}

// @ 0x00db6130
float __cdecl FUN_00db6130(void* citizen_, void* a2, void* a3, void* a4, char* stimuli_, u8* flag_)
{
    char* tribe  = (char*)((ObjV*)citizen_)->FUN_00c22f50();
    void* tribe_ = (void*)tribe;

    if ((char)((ObjV*)tribe)->FUN_00c8e7c0() != 0)
        return 0.0f;

    if ((char)((ObjV*)(tribe + 0x270))->FUN_00feba90() != 0)
    {
        long long et = ((ObjV*)(tribe + 0x270))->FUN_00bc3190();
        if ((float)((double)et * 0.001f) < 60.0f)
            return 0.0f;
    }

    {
        float* pos1 = ((FnFP0)(*(void***)(tribe + 0x120))[0x2c / 4])(tribe + 0x120);
        float  r    = ((FnF0)(*(void***)tribe_)[0x60 / 4])(tribe_);
        float  r2   = r * r;
        float* pos2 = ((FnFP0)(*(void***)((char*)citizen_ + 0xc0))[0x2c / 4])((char*)citizen_ + 0xc0);
        float  dx   = pos2[0] - pos1[0];
        float  dy   = pos2[1] - pos1[1];
        float  dz   = pos2[2] - pos1[2];
        float  d2   = dz * dz + dy * dy + dx * dx;

        if (d2 > r2)
            return 0.0f;

        {
            int rel = *(int*)(tribe + 0x26c);

            if (rel == -1)
            {
                void*  h    = FUN_00b3d4e0(0x55172d5);
                Cont2* cont = (Cont2*)((ObjV*)h)->FUN_00bc7610(0x55172d5, 0);

                if (cont->mBegin != cont->mEnd)
                {
                    int   local60;
                    float cost;
                    int   ncnt = 0;
                    FVecV vec;
                    int   nrec;

                    {
                        void* tm = FUN_00bc30b0(pos1);
                        int   b  = ((ObjV*)tm)->FUN_00bc2b80(pos1);
                        local60  = 2 - (int)(b != 0);
                    }
                    cost = ((ObjV*)tribe_)->FUN_00fc7f80();

                    {
                        Cont2* elems = (Cont2*)((FnP0)(*(void***)tribe_)[0x90 / 4])(tribe_);
                        char** p     = (char**)elems->mBegin;
                        char** pe    = (char**)elems->mEnd;
                        if (p == pe)
                            return 0.0f;
                        for (; p != pe; p++)
                        {
                            char* e = *p;
                            if ((char)((ObjV*)e)->FUN_00c0b770() != 0
                                && *(char*)(e + 0x135) != 0
                                && *(char*)(e + 0xb5e) == 0
                                && (char)((ObjV*)e)->FUN_00c24560() != 0
                                && (*(u8*)(e + 0xb58) & 0x10) == 0)
                            {
                                float* p2 = ((FnFP0)(*(void***)(e + 0xc0))[0x2c / 4])(e + 0xc0);
                                float  ex = p2[0] - pos1[0];
                                float  ey = p2[1] - pos1[1];
                                float  ez = p2[2] - pos1[2];
                                if (r2 > ez * ez + ey * ey + ex * ex)
                                    ncnt++;
                            }
                        }
                    }
                    if (ncnt <= 0)
                        return 0.0f;

                    rel = -1;
                    {
                        int   relv = -1;
                        u32   u20  = ((FnU0)(*(void***)tribe_)[0x4c / 4])(tribe_);
                        void* pt   = ((ObjV*)FUN_00b3d300())->FUN_00bfc5f0();

                        if (pt != 0 && pt != tribe_)
                        {
                            u32   u21 = ((FnU0)(*(void***)pt)[0x4c / 4])(pt);
                            void* mgr = FUN_00b3d2c0((void*)u20, (void*)u21, 1);
                            relv  = ((ObjV*)mgr)->FUN_00d00a70(u20, u21, 1);
                            rel   = relv;
                        }
                        else
                        {
                            rel = relv;
                        }

                        {
                            u32    mask = 0;
                            Cont2* tools = (Cont2*)((FnP0)(*(void***)tribe_)[0xbc / 4])(tribe_);
                            char** q   = (char**)tools->mBegin;
                            char** qe  = (char**)tools->mEnd;
                            for (; q != qe; q++)
                            {
                                u8 b = (u8)((FnC0)(*(void***)(*q))[0x58 / 4])(*q);
                                mask |= 1u << (b & 0x1f);
                            }

                            {
                                Cont2* recs = cont;
                                u32    kval = 0;

                                nrec = (int)(recs->mEnd - recs->mBegin) / 0x7b4;

                                vec.mBegin    = vec.mInline;
                                vec.mCur      = vec.mInline;
                                vec.mCap      = vec.mInline + 16;
                                vec.mHeapBase = vec.mInline;

                                if (nrec > 0)
                                {
                                    for (int k = 0; k < nrec; k++)
                                    {
                                        char* rec = recs->mBegin + k * 0x7b4;
                                        if (*(float*)(rec + 0x78c) <= cost
                                            && cost <= *(float*)(rec + 0x790)
                                            && (*(int*)(rec + 0x7a0) == 0 || *(int*)(rec + 0x7a0) == local60)
                                            && (*(int*)(rec + 0x7a4) == -1 || rel == -1 || *(int*)(rec + 0x7a4) == rel)
                                            && *(int*)(rec + 0x04) <= ncnt
                                            && (*(u32*)(rec + 0x7ac) == 0 || (*(u32*)(rec + 0x7ac) & mask) == *(u32*)(rec + 0x7ac)))
                                        {
                                            kval = (u32)k;
                                            if (vec.mCur < vec.mCap)
                                            {
                                                *vec.mCur = kval;
                                                vec.mCur++;
                                            }
                                            else
                                            {
                                                vec.FUN_004281d0(vec.mCur, kval);
                                            }
                                        }
                                    }

                                    if (vec.mBegin != vec.mCur)
                                    {
                                        u32 u      = ((ObjV*)RNG1601760)->FUN_00a68fb0((int)(vec.mCur - vec.mBegin));
                                        u32 chosen = vec.mBegin[u];
                                        if (stimuli_ != 0)
                                            ((ObjV*)stimuli_)->FUN_00d997e0();
                                        *(u32*)(stimuli_ + 0x18) = chosen;
                                        *(u32*)(stimuli_ + 0x1c) = 0x55172d5;
                                        *flag_ = 1;
                                        if (vec.mBegin != 0 && vec.mBegin != vec.mInline)
                                            FUN_00f47380(vec.mBegin);
                                        return 1.0f;
                                    }
                                    if (vec.mBegin != 0 && vec.mBegin != vec.mInline)
                                        FUN_00f47380(vec.mBegin);
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                void* tm = FUN_00b3d4e0((u32)rel);
                int   rc = ((ObjV*)tm)->FUN_00bc3db0(rel);
                if (rc > 0)
                {
                    if (stimuli_ != 0)
                        ((ObjV*)stimuli_)->FUN_00d997e0();
                    *(u32*)(stimuli_ + 0x18) = 0;
                    *(u32*)(stimuli_ + 0x1c) = 0;
                    *flag_ = 1;
                    return 1.0f;
                }
            }
        }
    }
    return 0.0f;
}

// @ 0x00db6c50
void* __fastcall FUN_00db6c50(void* self_)
{
    char* self = (char*)self_;
    u8    b;

    ((ObjV*)self)->FUN_00ac14d0();
    *(void**)self = VTABLE_147C2C4;
    *(u32*)(self + 0x08) = 0;
    *(u32*)(self + 0x0c) = 0;
    *(u32*)(self + 0x10) = 0;
    *(char**)(self + 0x1c) = self + 0x34;
    *(char**)(self + 0x20) = self + 0x34;
    *(char**)(self + 0x24) = self + 0x54;
    *(u32*)(self + 0x30) = 0;
    ((ObjV*)(self + 0x54))->FUN_00db5c20(&b, &b);

    *(void**)(self + 0x18c) = 0;
    *(void**)(self + 0x190) = 0;
    *(float*)(self + 0x194) = G169F3B8;
    *(float*)(self + 0x198) = G169F3BC;
    *(float*)(self + 0x19c) = G169F3C0;
    *(float*)(self + 0x1a0) = G169F3B8;
    *(float*)(self + 0x1a4) = G169F3BC;
    *(float*)(self + 0x1a8) = G169F3C0;
    *(float*)(self + 0x1ac) = 0.0f;
    *(float*)(self + 0x1b0) = G13EB8A0;
    *(float*)(self + 0x1b4) = G1485720;
    *(float*)(self + 0x1b8) = G1485720;
    *(float*)(self + 0x1bc) = G1485548;
    *(float*)(self + 0x1c0) = G147C21C;
    *(float*)(self + 0x1c4) = G1485720;
    *(float*)(self + 0x1c8) = 0.0f;
    *(u32*)(self + 0x1cc) = 1;
    *(u8*)(self + 0x1d0) = 1;
    *(u8*)(self + 0x1d1) = 1;
    ((ObjV*)(self + 0x1d4))->FUN_00afba10();
    *(u32*)(self + 0x238) = 0;
    *(u32*)(self + 0x240) = 0;
    *(u8*)(self + 0x244) = 0;
    *(u32*)(self + 0x248) = 0;
    *(u8*)(self + 0x23c) = 1;
    return self_;
}

// @ 0x00db6db0
void __fastcall FUN_00db6db0(void* self_)
{
    char* self = (char*)self_;

    *(void**)self = VTABLE_147C2C4;
    ((ObjV*)(self + 0x1d4))->FUN_00afbad0();

    {
        void* o = *(void**)(self + 0x190);
        if (o != 0)
            ((FnV0)(*(void***)o)[0xc0 / 4])(o);
    }
    {
        void* o = *(void**)(self + 0x18c);
        if (o != 0)
            ((FnV0)(*(void***)o)[0xc0 / 4])(o);
    }

    {
        char* s  = self + 0x54;
        void* a1 = *(void**)(self + 0x58);
        void* a2 = *(void**)(self + 0x5c);
        void* p;
        ((ObjV*)s)->FUN_005941f0(a1, a2);
        p = *(void**)(s + 0x04);
        *(u32*)(s + 0x0c) = 0;
        if (*(u32*)(s + 0x08) > 1 && p != *(void**)(s + 0x30))
        {
            if (p < *(void**)(s + 0x24) || p >= *(void**)(s + 0x28))
            {
                FUN_00f47380(p);
            }
            else
            {
                *(void**)p = *(void**)(s + 0x1c);
                *(void**)(s + 0x1c) = p;
            }
        }
    }

    ((ObjV*)(self + 0x1c))->FUN_00ad92d0();
    {
        void* p2 = *(void**)(self + 0x08);
        if (p2 != 0 && *(u32*)((char*)p2 - 4) != 0)
            FUN_00f47380(p2);
    }
    ((ObjV*)self)->FUN_00ac5430();
}

// ------------------------------------------------------------------ vignette data records

// One entry of the tribe's spot array (tribe +0x294), stride 0x14.
struct VignetteSpot
{
    float x;              // +0x00
    float y;              // +0x04
    float z;              // +0x08
    float mField0C;       // +0x0c
    u8    mFlag10;        // +0x10  non-zero = unusable spot
    u8    mPad11[3];
};

// One candidate inside the IDLE_VIGNETTE event container, stride 0x7b4.
struct VignetteRecord
{
    u8    mPad00[4];
    int   mMaxCitizens04;          // +0x04
    u8    mPad08[0x78c - 0x08];
    float mfMinCost078C;           // +0x78c
    float mfMaxCost0790;           // +0x790
    u8    mPad794[0x7a0 - 0x794];
    int   mnTimeOfDay07A0;         // +0x7a0  0 = any
    int   mnRelation07A4;          // +0x7a4  -1 = any
    u8    mPad7A8[4];
    u32   muToolMask07AC;          // +0x7ac  0 = any
    u8    mPad7B0[4];
};

// @ 0x00db65a0
// SP::IDLE_VIGNETTE_Decide -- picks the object a citizen plays its idle vignette on
// and writes the chosen object plus its context into the behaviour stimuli.
float __cdecl FUN_00db65a0(void* citizen_, void* a2, void* a3, u32 nFlags, char* stimuli_, u8* flag_)
{
    char* citizen = (char*)citizen_;
    u8    cVar4;
    u32   fBit5 = (nFlags >> 5) & 1;
    u32   evt;

    if (*(char*)(citizen + 0xf90) == 0 || (nFlags & 0x400) != 0)
        return 0.0f;

    cVar4 = (u8)((ObjV*)citizen_)->FUN_00c0b770();

    // A citizen that is already ordered around skips the probability roll entirely.
    if (fBit5 == 0 && cVar4 == 1)
    {
        void* mgr  = FUN_00bc9b00();
        int   node = ((ObjV*)mgr)->FUN_00bca620(0x55241ec, (void*)FUN_00da7140, citizen_);

        if (node != 0)
        {
            if (stimuli_ != 0)
                ((ObjV*)stimuli_)->FUN_00d997e0();
            *flag_ = 1;
            *(int*)stimuli_ = node;
            return 1.0f;
        }
    }

    {
        float prob = FUN_004e1c70(*(const u32*)0x01581288, 0x633e78a1, 0.5f);

        if (((ObjV*)RNG1601760)->FUN_009360d0() > (double)prob)
            return 0.0f;
    }

    if (cVar4 == 0)
        evt = 0x7dcc4e7e;
    else
        evt = (fBit5 != 0 ? 0xb546d379u : 0u) + 0x5523ddcu;

    {
        Cont2* cont = (Cont2*)((ObjV*)FUN_00b3d4e0(evt))->FUN_00bc7610((int)evt, 0);

        if (cont->mBegin == cont->mEnd)
            return 0.0f;

        {
            char*  tribe = (char*)((ObjV*)citizen_)->FUN_00c22f50();
            int    nBest = -1;
            float  fBest = G147C218;
            float* pos   = ((FnFP0)(*(void***)(citizen + 0xc0))[0x2c / 4])(citizen + 0xc0);

            {   // nearest unused spot of the tribe
                VignetteSpot* spots  = *(VignetteSpot**)(tribe + 0x294);
                VignetteSpot* spotsE = *(VignetteSpot**)(tribe + 0x298);
                for (int i = 0; i < (int)(spotsE - spots); i++)
                {
                    VignetteSpot& s = spots[i];
                    float dx, dy, dz, d2;

                    if (s.mFlag10 != 0)
                        continue;
                    dx = pos[0] - s.x;
                    dy = pos[1] - s.y;
                    dz = pos[2] - s.z;
                    d2 = dz * dz + dy * dy + dx * dx;
                    if (fBest > d2)
                    {
                        fBest = d2;
                        nBest = i;
                    }
                }
            }

            if (nBest == -1)
                return 0.0f;

            {
                float* tpos    = ((FnFP0)(*(void***)(tribe + 0x120))[0x2c / 4])(tribe + 0x120);
                int    daypart = 2 - (int)(((ObjV*)FUN_00bc30b0(tpos))->FUN_00bc2b80(tpos) != 0);
                float  cost;
                float  r2;
                int    ncnt = 0;
                int    rel  = -1;
                u32    mask = 0;

                cost = ((ObjV*)tribe)->FUN_00fc7f80();

                {
                    float r = ((FnF0)(*(void***)tribe)[0x60 / 4])(tribe);
                    r2 = r * r;
                }

                {   // citizens already in range of the spot
                    Cont2* elems = (Cont2*)((FnP0)(*(void***)tribe)[0x90 / 4])(tribe);
                    char** p     = (char**)elems->mBegin;
                    char** pe    = (char**)elems->mEnd;

                    for (; p != pe; p++)
                    {
                        char* e = *p;

                        if ((char)((ObjV*)e)->FUN_00c0b770() == 0)
                            continue;
                        if (*(char*)(e + 0x135) == 0)
                            continue;
                        if (*(char*)(e + 0xb5e) != 0)
                            continue;
                        if ((char)((ObjV*)e)->FUN_00c24560() == 0)
                            continue;
                        if ((*(u8*)(e + 0xb58) & 0x10) != 0)
                            continue;
                        if (*(u32*)(*(u32*)(e + 0xb4c) + 0x1d8) == 0x5524115)
                            continue;
                        {
                            float* p2 = ((FnFP0)(*(void***)(e + 0xc0))[0x2c / 4])(e + 0xc0);
                            float  ex = p2[0] - tpos[0];
                            float  ey = p2[1] - tpos[1];
                            float  ez = p2[2] - tpos[2];

                            if (r2 > ez * ez + ey * ey + ex * ex)
                                ncnt++;
                        }
                    }
                }

                {   // tool types available to the tribe
                    Cont2* tools = (Cont2*)((FnP0)(*(void***)tribe)[0xbc / 4])(tribe);
                    char** q     = (char**)tools->mBegin;
                    char** qe    = (char**)tools->mEnd;

                    for (; q != qe; q++)
                    {
                        u8 b = (u8)((FnC0)(*(void***)(*q))[0x58 / 4])(*q);
                        mask |= 1u << (b & 0x1f);
                    }
                }

                {   // relationship class towards the player tribe
                    u32   tid = ((FnU0)(*(void***)tribe)[0x4c / 4])(tribe);
                    void* pt  = ((ObjV*)FUN_00b3d300())->FUN_00bfc5f0();

                    if (pt != 0 && pt != (void*)tribe)
                    {
                        u32   oid = ((FnU0)(*(void***)pt)[0x4c / 4])(pt);
                        void* mgr = FUN_00b3d2c0((void*)tid, (void*)oid, 1);
                        rel = ((ObjV*)mgr)->FUN_00d00a70(tid, oid, 1);
                    }
                }

                {
                    int   nrec = (int)((cont->mEnd - cont->mBegin) / 0x7b4);
                    FVecV vec;

                    vec.mBegin    = vec.mInline;
                    vec.mCur      = vec.mInline;
                    vec.mCap      = vec.mInline + 16;
                    vec.mHeapBase = vec.mInline;

                    if (nrec <= 0)
                        return 0.0f;

                    for (int k = 0; k < nrec; k++)
                    {
                        VignetteRecord* r = (VignetteRecord*)(cont->mBegin + k * 0x7b4);
                        u32 kval = (u32)k;

                        if (r->mfMinCost078C > cost)
                            continue;
                        if (cost > r->mfMaxCost0790)
                            continue;
                        if (r->mnTimeOfDay07A0 != 0 && r->mnTimeOfDay07A0 != daypart)
                            continue;
                        if (r->mnRelation07A4 != -1 && rel != -1 && r->mnRelation07A4 != rel)
                            continue;
                        if (r->mMaxCitizens04 > ncnt)
                            continue;
                        if (r->muToolMask07AC != 0 && (r->muToolMask07AC & mask) != r->muToolMask07AC)
                            continue;

                        if (vec.mCur < vec.mCap)
                        {
                            *vec.mCur = kval;
                            vec.mCur++;
                        }
                        else
                        {
                            vec.FUN_004281d0(vec.mCur, kval);
                        }
                    }

                    if (vec.mBegin != vec.mCur)
                    {
                        u32 u      = ((ObjV*)RNG1601760)->FUN_00a68fb0((int)(vec.mCur - vec.mBegin));
                        u32 chosen = vec.mBegin[u];

                        if (stimuli_ != 0)
                            ((ObjV*)stimuli_)->FUN_00d997e0();
                        *(u32*)(stimuli_ + 0x18) = chosen;
                        *(u32*)(stimuli_ + 0x1c) = (u32)nBest;
                        *(u32*)(stimuli_ + 0x20) = evt;
                        *flag_ = 1;
                        if (vec.mBegin != 0 && vec.mBegin != vec.mInline)
                            FUN_00f47380(vec.mBegin);
                        return 1.0f;
                    }
                    if (vec.mBegin != 0 && vec.mBegin != vec.mInline)
                        FUN_00f47380(vec.mBegin);
                }
            }
        }
    }
    return 0.0f;
}