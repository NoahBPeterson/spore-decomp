// ===========================================================================
// slice s00d124e0 -- SPStarManager.obj update/dispatch cluster.
// Reconstructed from work/SporeApp.analysis.bin.
//
//   0x00d124e0  Class12::FUN_00d124e0   per-frame refresh / update
//   0x00d12910  Class12::FUN_00d12910   message dispatch (jump table)
//   0x00d12d00  Class12::FUN_00d12d00   message handler (property / global keys)
//   0x00d12fc0  Class12::FUN_00d12fc0   teardown / release
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
// ===========================================================================

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#pragma warning(disable: 4100 4189 4244 4311 4312)

// ---- free / runtime callees ----------------------------------------------
void  Free5(void* a, void* b, void* c, void* d, void* e);                    // 0x00571db0
void  FreePair(void* a, void* b);                                            // 0x00571d40
void* GlobalManagerA();                                                      // 0x0067ddd0
void* GlobalManagerB();                                                      // 0x00b3d240
void* GlobalManagerC();                                                      // 0x00b3d280
void* GlobalManagerD();                                                      // 0x00b3d250
void* GlobalManagerE();                                                      // 0x00b3d300
u32   FUN_00b5b800();                                                        // 0x00b5b800
void* PropertyServer();                                                      // 0x0067de30
void  FUN_006a12a0(void* pSelf, u32 key, void* pArg);                        // 0x006a12a0
void  FUN_0064aba0(void* p);                                                 // 0x0064aba0
void* FUN_00422eb0(void* a, void* b);                                        // 0x00422eb0
void  FUN_0093db80(void* a, void* b);                                        // 0x0093db80
void* FUN_00804ed0(void* a, void* b);                                        // 0x00804ed0

// ---- thiscall callees (ecx = the receiver passed as pSelf) ----------------
struct CalleeSet {
    void  FUN_00d11f80(void* a, int n, void* b);      // 0x00d11f80
    void  FUN_00d0c5b0(void* a);                      // 0x00d0c5b0
    void  FUN_00d100b0(int a, int b);                 // 0x00d100b0
    void  FUN_00d099c0(void* a);                      // 0x00d099c0
    void  FUN_00d0b540(void* a);                      // 0x00d0b540
    u8    FUN_00d0a160();                             // 0x00d0a160
    void  FUN_00d0e170(void* a, int b);               // 0x00d0e170
    void  FUN_00d0b3b0(void* a);                      // 0x00d0b3b0
    void  FUN_00d0fcc0(void* a);                      // 0x00d0fcc0
    void  FUN_00d10840(void* a, void* b);             // 0x00d10840
    void  FUN_00d10f90(void* a, void* b);             // 0x00d10f90
    void  FUN_00d09770(void* a, void* b);             // 0x00d09770
    void  FUN_00d0c170(void* a, void* b);             // 0x00d0c170
    void  FUN_00d0ae50(void* a, void* b);             // 0x00d0ae50
    void  FUN_00d11730(void* a, void* b);             // 0x00d11730
    void  FUN_00d0a470(void* a, void* b);             // 0x00d0a470
    void  FUN_00d08ad0();                             // 0x00d08ad0
    void  FUN_00d08a70(void* a, void* b);             // 0x00d08a70
    void  FUN_00d08aa0();                             // 0x00d08aa0
    void  FUN_00d0d570(void* a);                      // 0x00d0d570
    void  FUN_005ca980(void* a);                      // 0x005ca980
    void  FUN_005cb240(void* a);                      // 0x005cb240
    void  FUN_005a7840();                             // 0x005a7840
    void  FUN_004582b0(void* a);                      // 0x004582b0
    void  FUN_00bdde70(void* a);                      // 0x00bdde70
    void  FUN_00ea13e0();                             // 0x00ea13e0
    void* FUN_00b25fb0();                             // 0x00b25fb0
    void* FUN_00bef6c0();                             // 0x00bef6c0
    void  FUN_00b10c40(int b);                        // 0x00b10c40
    void  FUN_00b0f210();                             // 0x00b0f210
    void* FUN_00b10260();                             // 0x00b10260
    void  FUN_00b10340();                             // 0x00b10340
    void  FUN_00b13bb0(void* a, void* b);             // 0x00b13bb0
    void* FUN_00b7f190();                             // 0x00b7f190
    void* FUN_00434040();                             // 0x00434040
    void* FUN_00b3d350(void* a);                      // 0x00b3d350
    void* FUN_0059c190(void* a);                      // 0x0059c190
    void* FUN_00705b0(void* a, void* b);              // 0x008105b0
    void  FUN_00811ad0(void* a);                      // 0x00811ad0
};
#define SELF(o) ((CalleeSet*)(o))

// The object passed in ecx is a base sub-object at offset 8 of a larger object;
// member functions of the *other* base receive that larger object (ecx - 8).
struct BaseView {
    u8      mGap00[0xb4];
    void*   mpB4;              // +0x0b4  (this-8 + 0xb4  == this + 0xac)
};
#define BASEB(o) ((BaseView*)((u8*)(o) - 8))

// Small views for the fields reached through a published object pointer.
struct SelObj { u8 mGap00[0x6e]; u8 mB6e; };          // selection object, flag at +0x6e
struct Vec3   { float x, y, z; };                        // 3-float vector
struct MgrC   { u8 mGap00[0x390]; u8 mB390; };          // global manager C, flag at +0x390
struct PropVal { u8 mGap00[0x10]; u8 mFlags; u8 mGap11; u16 mW12; };  // property value blob

// ---- vtable dispatch through a member pointer (thiscall) ------------------
struct VtblObj {
    void  C0();
    void  C1(void*);
    void  C2(void*, void*);
    void  C3(void*, void*, void*);
    void* R0();
    void* R1(void*);
    void* R2(void*, void*);
    u8    B1(void*);
};
typedef void  (VtblObj::*PMF0)();
typedef void  (VtblObj::*PMF1)(void*);
typedef void  (VtblObj::*PMF2)(void*, void*);
typedef void  (VtblObj::*PMF3)(void*, void*, void*);
typedef void* (VtblObj::*PMR0)();
typedef void* (VtblObj::*PMR1)(void*);
typedef void* (VtblObj::*PMR2)(void*, void*);
typedef u8    (VtblObj::*PMB1)(void*);

inline void  VCall0(void* p, u32 o)                            { (((VtblObj*)p)->*(*(PMF0*)((u8*)*(void**)p + o)))(); }
inline void  VCall1(void* p, u32 o, void* a)                   { (((VtblObj*)p)->*(*(PMF1*)((u8*)*(void**)p + o)))(a); }
inline void  VCall2(void* p, u32 o, void* a, void* b)          { (((VtblObj*)p)->*(*(PMF2*)((u8*)*(void**)p + o)))(a, b); }
inline void  VCall3(void* p, u32 o, void* a, void* b, void* c) { (((VtblObj*)p)->*(*(PMF3*)((u8*)*(void**)p + o)))(a, b, c); }
inline void* VRet0(void* p, u32 o)                             { return (((VtblObj*)p)->*(*(PMR0*)((u8*)*(void**)p + o)))(); }
inline void* VRet1(void* p, u32 o, void* a)                    { return (((VtblObj*)p)->*(*(PMR1*)((u8*)*(void**)p + o)))(a); }
inline void* VRet2(void* p, u32 o, void* a, void* b)           { return (((VtblObj*)p)->*(*(PMR2*)((u8*)*(void**)p + o)))(a, b); }
inline u8    VBool1(void* p, u32 o, void* a)                   { return (((VtblObj*)p)->*(*(PMB1*)((u8*)*(void**)p + o)))(a); }

// A 4-byte intrusive smart pointer: vptr slot 0 = AddRef, slot 1 = Release.
inline void RefRelease(void* p) { if (p) VCall0(p, 0x04); }

// ---------------------------------------------------------------------------
struct Class12 {
    u8      mGap00[0x28];
    void*   mp28;
    void*   mp2c;
    void*   mp30;
    void*   mp34;
    void*   mp38;
    void*   mp3c;
    void*   mp40;
    void*   mp44;
    u8      mGap48[0x20];
    void*   mp68;
    void*   mp6c;
    u8      mGap70[0x04];
    void*   mp74;
    u8      mGap78[0x0c];
    void*   mp84;
    u8      mGap88[0x18];
    void*   mpA0;
    u8      mGapA4[0x08];
    void*   mpAc;
    u8      mGapB0[0x04];
    void*   mpB4;
    u8      mGapB8[0x08];
    void*   mpC0;
    u8      mGapC4[0x144];
    u8      mB208;
    u8      mGap209[0x03];
    void*   mp20c;
    u8      mGap210[0x18];
    void*   mp228;
    u8      mGap22c[0x48];
    u8      mB274;
    u8      mGap275[0x03];
    void*   mp278;
    u8      mGap27c[0x14];
    void*   mp290;
    void*   mp294;
    u8      mGap298[0x24];
    u8      mB2bc;
    u8      mGap2bd[0x03];
    void*   mp2c0;
    u8      mGap2c4[0x04];
    float   mF2c8;
    float   mF2cc;
    float   mF2d0;
    float   mF2d4;
    u8      mGap2d8[0x14];
    u32     mF2ec;
    u8      mGap2f0[0x08];
    void*   mp2f8;

    void FUN_00d124e0(void* pArg);
    u8   FUN_00d12910(void* pMsg, int nType);
    u8   FUN_00d12d00(void* pMsg, int nType);
    void FUN_00d12fc0();
};

// @ 0x00d124e0
void Class12::FUN_00d124e0(void* pArg)
{
    if (mp40 == 0) {
        SELF(this)->FUN_00d08ad0();
        return;
    }

    void* edi = mp40 ? VRet1(mp40, 0x0c, (void*)0xee9b2232) : 0;
    if (mp40)
        VCall1(mp40, 0x0c, (void*)0x4f396a66);

    void* esi = pArg;

    if (edi) {
        SELF(this)->FUN_00d11f80(&mp20c, 0, pArg);
        SELF(this)->FUN_00d11f80(&mp228, 1, pArg);
    }
    if (mpB4) SELF(mpB4)->FUN_005ca980(esi);

    if (mp68) {
        void* eax = VRet1(mp68, 0x04, 0);
        if (mp74 != eax) {
            SELF(mp68)->FUN_005a7840();
            eax = VRet1(mp68, 0x04, 0);
            mp74 = eax;
        }
    }
    if (mp6c) SELF(mp6c)->FUN_004582b0(esi);
    SELF(this)->FUN_00d0c5b0(esi);

    if (edi && mpA0)
        SELF(edi)->FUN_00bdde70(mpA0);

    if (mpC0 == 0)
        goto tail;

    {
        u8 al = ((SelObj*)mpC0)->mB6e;

        if (mp278 == 0) {
            mB274 = al;
            void* edi2 = (al ? mp294 : mp290);
            void* esi2 = GlobalManagerA();
            RefRelease(mp278);
            mp278 = 0;
            VCall3(esi2, 0x2c, edi2, 0, &mp278);
            if (mp278 == 0)
                goto tail;
            {
                u8 local44[0x1c];
                SELF(local44)->FUN_00434040();
                {
                    void* eax = VRet0(mpC0, 0x2c);
                    void* t = SELF(local44 + 0x04)->FUN_00b3d350(eax);
                    void* u = SELF(t)->FUN_00b7f190();
                    void* v = SELF(local44 + 0x14)->FUN_0059c190(u);
                    for (int i = 0; i < 9; ++i) ((u32*)local44)[9 + i] = ((u32*)v)[i];
                    *(u16*)(local44 + 0x08) |= 2;
                    *(u16*)(local44 + 0x0a) += 1;
                    {
                        void* w = VRet0(mpC0, 0x2c);
                        *(u32*)(local44 + 0x04) = ((u32*)w)[0];
                        *(u32*)(local44 + 0x08) = ((u32*)w)[1];
                        *(u32*)(local44 + 0x0c) = ((u32*)w)[2];
                    }
                    *(u16*)(local44 + 0x00) |= 4;
                    *(u16*)(local44 + 0x02) += 1;
                    VCall1(mp278, 0x18, local44);
                    {
                        void* ep = mp278;
                        VCall2(*(void**)ep, 0x08, 0, 0);
                    }
                }
            }
        } else if (mB274 != al) {
            mB274 = al;
            VCall1(mp278, 0x0c, (void*)1);
            RefRelease(mp278);
            mp278 = 0;
            {
                void* edi2 = (mB274 ? mp294 : mp290);
                void* esi2 = GlobalManagerA();
                VCall3(esi2, 0x2c, edi2, 0, &mp278);
                if (mp278 == 0)
                    goto tail;
                {
                    u8 local44[0x1c];
                    SELF(local44)->FUN_00434040();
                    {
                        void* eax = VRet0(mpC0, 0x2c);
                        void* t = SELF(local44 + 0x04)->FUN_00b3d350(eax);
                        void* u = SELF(t)->FUN_00b7f190();
                        void* v = SELF(local44 + 0x14)->FUN_0059c190(u);
                        for (int i = 0; i < 9; ++i) ((u32*)local44)[9 + i] = ((u32*)v)[i];
                        *(u16*)(local44 + 0x08) |= 2;
                        *(u16*)(local44 + 0x0a) += 1;
                        {
                            void* w = VRet0(mpC0, 0x2c);
                            FreePair(local44 + 0x04, w);
                        }
                        *(u16*)(local44 + 0x00) |= 4;
                        *(u16*)(local44 + 0x02) += 1;
                        VCall1(mp278, 0x18, local44);
                        {
                            void* ep = mp278;
                            VCall2(*(void**)ep, 0x08, 0, 0);
                        }
                    }
                }
            }
        } else {
            u8 local44[0x1c];
            SELF(local44)->FUN_00434040();
            {
                void* eax = VRet0(mpC0, 0x2c);
                void* t = SELF(local44 + 0x04)->FUN_00b3d350(eax);
                void* u = SELF(t)->FUN_00b7f190();
                void* v = SELF(local44 + 0x14)->FUN_0059c190(u);
                for (int i = 0; i < 9; ++i) ((u32*)local44)[9 + i] = ((u32*)v)[i];
                *(u16*)(local44 + 0x08) |= 2;
                *(u16*)(local44 + 0x0a) += 1;
                {
                    void* w = VRet0(mpC0, 0x2c);
                    *(u32*)(local44 + 0x04) = ((u32*)w)[0];
                    *(u32*)(local44 + 0x08) = ((u32*)w)[1];
                    *(u32*)(local44 + 0x0c) = ((u32*)w)[2];
                }
                *(u16*)(local44 + 0x00) |= 4;
                *(u16*)(local44 + 0x02) += 1;
                VCall1(mp278, 0x18, local44);
                {
                    void* ep = mp278;
                    VCall2(*(void**)ep, 0x08, 0, 0);
                }
            }
        }
    }

tail:
    if (mB2bc) {
        SELF(this)->FUN_00d099c0(mp2c0);
        mp2c0 = 0;
    }
    if (mB208 == 0) {
        if (GlobalManagerC()) {
            Vec3* w = (Vec3*)SELF(GlobalManagerC())->FUN_00b10260();
            float v[3];
            v[0] = w->x;
            v[1] = w->y;
            v[2] = w->z;
            SELF(this)->FUN_00d0b540(v);
        }
        if (GlobalManagerC()) {
            float v[3];
            SELF(GlobalManagerC())->FUN_00b13bb0(v, 0);
        }
    }
    {
        void* mgr = GlobalManagerB();
        void* f = VRet0(mgr, 0x34);
        if (f == 0) {
            SELF(this)->FUN_00d08ad0();
            return;
        }
        {
            void* e = VRet1(f, 0x0c, (void*)0x17f243b);
            SELF(e)->FUN_00d08ad0();
        }
    }
}

// @ 0x00d12910
u8 Class12::FUN_00d12910(void* pMsg, int nType)
{
    u8 bFlag = (mp40 != 0 && mB208 == 0) ? 1 : 0;

    void* ebp = VRet0(pMsg, 0x10);
    void* eax = VRet1(ebp, 0x1c, 0);
    void* ebx;
    if (((PropVal*)eax)->mFlags & 0x30)
        ebx = *(void**)eax;
    else if (((PropVal*)eax)->mW12 == 0)
        ebx = 0;
    else
        ebx = eax;

    void* edi = 0;
    if (ebx) {
        edi = VRet1(ebx, 0x0c, (void*)0x17f243b);
        VCall1(ebx, 0x0c, (void*)0x1186577);
        ebx = *(void**)VRet1(ebp, 0x1c, (void*)1);
    }

    u32 nResult = 0;
    if (bFlag == 0) {
        void* esi = VRet0(pMsg, 0x14);
        nResult = 2;
        u8 local30[0x18];
        *(u16*)(local30 + 0x12) = 0;
        *(u16*)(local30 + 0x16) = 0;
        FUN_00422eb0(local30, &nResult);
        VCall2(esi, 0x20, 0, local30);
        if (*(u8*)(local30 + 0x10) & 4) {
            FUN_0093db80(local30, 0);
            return 0;
        }
    }

    switch (nType) {
    case 0x62ec2a6:
        SELF(this)->FUN_00d08a70(edi, (void*)&ebx);
        goto commit;
    case 0x609ea30:
        SELF(this)->FUN_00d0d570(edi);
        goto commit;
    case 0x332a303a:
        mB2bc = (edi == (void*)1);
        mp2c0 = mB2bc ? edi : 0;
        if (edi == (void*)2) {
            SELF(this)->FUN_00d099c0(edi);
            if (GlobalManagerC()) {
                Vec3* w = (Vec3*)SELF(GlobalManagerC())->FUN_00b10260();
                float v[3];
                v[0] = w->x;
                v[1] = w->y;
                v[2] = w->z;
                SELF(this)->FUN_00d0b540(v);
                SELF(this)->FUN_00d08aa0();
            }
        }
        nResult = 0;
        goto commit;
    case 0x332a303b:
        SELF(this)->FUN_00d0b3b0(edi);
        goto commit;
    case 0x71d4dfc3:
        if (edi)
            SELF(this)->FUN_00d0fcc0(VRet1(edi, 0x0c, (void*)0x1186577));
        else
            SELF(this)->FUN_00d0fcc0(0);
        goto commit;
    default:
        {
            u32 idx = (u32)nType + 0x8e2b203c;
            if (idx > 0xa) { nResult = 0; goto commit; }
            switch (idx) {
            case 0:
                FUN_00804ed0(&mF2c8, &mF2cc);
                if (GlobalManagerC() && ((MgrC*)GlobalManagerC())->mB390 == 0)
                    SELF(GlobalManagerC())->FUN_00b10c40(1);
                nResult = 0;
                goto commit;
            case 1:
                FUN_00804ed0(&mF2c8, &mF2cc);
                if (GlobalManagerC()) {
                    SELF(GlobalManagerC())->FUN_00b0f210();
                    SELF(GlobalManagerC())->FUN_00b10340();
                }
                nResult = 0;
                goto commit;
            case 2:
                if (GlobalManagerC())
                    SELF(GlobalManagerC())->FUN_00b10c40(0);
                nResult = 0;
                goto commit;
            case 3:
                SELF(this)->FUN_00d10840(edi, (void*)&ebx);
                goto commit;
            case 4:
                SELF(this)->FUN_00d10f90(edi, (void*)&ebx);
                goto commit;
            case 5:
                SELF(this)->FUN_00d09770(edi, (void*)&ebx);
                goto commit;
            case 6:
                SELF(this)->FUN_00d0c170(edi, (void*)&ebx);
                goto commit;
            case 7:
                SELF(this)->FUN_00d0ae50(edi, (void*)&ebx);
                goto commit;
            case 8:
                SELF(this)->FUN_00d11730(edi, (void*)&ebx);
                goto commit;
            }
        }
    }

commit:
    {
        void* esi = VRet0(pMsg, 0x14);
        u8 local44[0x18];
        *(u16*)(local44 + 0x12) = 0;
        *(u16*)(local44 + 0x16) = 0;
        FUN_00422eb0(local44, &nResult);
        VCall2(esi, 0x20, 0, local44);
        if (*(u8*)(local44 + 0x10) & 4)
            FUN_0093db80(local44, 0);
    }
    return 0;
}

// @ 0x00d12d00
u8 Class12::FUN_00d12d00(void* pMsg, int nType)
{
    u8* pB = (u8*)pMsg;
    u32 key0 = *(u32*)(pB + 0x08);
    u32 key1 = *(u32*)(pB + 0x0c);

    if (key0 != 0x287259f6) {
        if (key0 == 0x0a && key1 == 1) {
            int b0 = 0, b1 = 0;
            void* pSub = *(void**)(pB + 0x18);
            if (pSub) {
                void* r = VRet0(pSub, 0x1c);
                if (r == (void*)0x65f6003) b0 = 1;
                else if (r == (void*)0x65f6004) b1 = 1;
            }
            {
                void* a = SELF((u8*)this + 0x80)->FUN_00705b0((void*)0x66758d6, (void*)1);
                if (a) VCall2(a, 0x7c, (void*)1, (void*)b0);
                SELF((u8*)this - 8)->FUN_00d0a470((void*)0x66758d6, (void*)0x66f3f12);
            }
            {
                void* a = SELF((u8*)this + 0x80)->FUN_00705b0((void*)0x66758d7, (void*)1);
                if (a) VCall2(a, 0x7c, (void*)1, (void*)b1);
                SELF((u8*)this - 8)->FUN_00d0a470((void*)0x66758d7, (void*)0x66f3f13);
            }
        }
        return 0;
    }

    if (key1 == 0x1036a039) {
        VCall2(GlobalManagerD(), 0x64, (void*)0x3e80, (void*)1);
        return 1;
    }
    if (key1 == 0x44efe63) {
        void* out = 0;
        void* other = 0;
        void* srv = PropertyServer();
        VCall2(srv, 0x30, (void*)0x6b3f727b, &out);
        u32 g = FUN_00b5b800() - 0x1654c02;
        if (g == 0)      FUN_006a12a0(out, 0xd3a9b56, &other);
        else if (g == 2) FUN_006a12a0(out, 0x5ca318f3, &other);
        else if (g == 3) FUN_006a12a0(out, 0x2fd9f52e, &other);
        if (other) FUN_0064aba0(other);
        RefRelease(out);
        return 1;
    }

    {
        u32 k = key1 + 0x8b4412c3;
        if (k > 1)
            return 0;
        void* p38 = mp38;
        if (p38 == 0)
            return 0;
        void* ebx = VRet1(p38, 0x0c, (void*)0xee9b2232);
        if (ebx == 0)
            return 0;
        {
            void* h = SELF(GlobalManagerE())->FUN_00b25fb0();
            if (h == 0) return 0;
            void* v = SELF(h)->FUN_00bef6c0();
            void* beg = *(void**)v;
            void* end = *(void**)((u8*)v + 4);
            int n = (int)(((u8*)end - (u8*)beg) / 4);
            int idx = 0;
            for (int i = 0; i < n; ++i)
                if (((void**)beg)[i] == ebx) { idx = i; break; }
            if (key1 == 0x74bbed3d) {
                if (++idx >= n) idx = 0;
            } else {
                if (--idx < 0) idx = n - 1;
            }
            void* pElem = ((void**)beg)[idx];
            if (pElem == 0 || pElem == ebx)
                return 0;
            void* sub = (u8*)this - 8;
            if (!SELF(sub)->FUN_00d0a160())
                return 0;
            SELF(sub)->FUN_00d100b0(0, 0);
            SELF(sub)->FUN_00d0e170(pElem, 1);
            if (BASEB(this)->mpB4)
                SELF(BASEB(this)->mpB4)->FUN_005cb240((void*)(u32)mF2ec);
            return 0;
        }
    }
}

// @ 0x00d12fc0
void Class12::FUN_00d12fc0()
{
    if (mp28) {
        Free5(mp28, mp2c, mp30, mp34, mp38);
        mp28 = 0;
    }
    if (mp40)
        SELF(this)->FUN_00d100b0(1, 0);
    if (mp3c) {
        void* old = mp3c;
        mp3c = 0;
        RefRelease(old);
    }
    if (mp84) {
        VCall0(mp84, 0x24);
        if (mp84) {
            void* old = mp84;
            mp84 = 0;
            RefRelease(old);
        }
    }
    if (mpAc) {
        SELF(mpAc)->FUN_00ea13e0();
        if (mpAc) {
            void* old = mpAc;
            mpAc = 0;
            RefRelease(old);
        }
    }
    {
        void* edi = (u8*)this + 0x88;
        void* q = SELF(edi)->FUN_00705b0((void*)-1, (void*)1);
        if (q) {
            void* c = mp2f8 ? (u8*)mp2f8 + 4 : 0;
            VCall1(q, 0xdc, c);
            if (mp2f8) {
                void* old = mp2f8;
                mp2f8 = 0;
                RefRelease(old);
            }
        }
        SELF(edi)->FUN_00811ad0((void*)1);
    }
    if (mp44) {
        void* old = mp44;
        mp44 = 0;
        VCall0(old, 0x08);
    }
}