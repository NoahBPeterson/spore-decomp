// Slice s00679630 - property-UI element/container (SP::cPropertyUI) and
// SP::Achievements::Controller::Shutdown.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE.
#include "types.h"

struct VObj { void** vt; };
typedef void   (__thiscall *FnV1)(void*);
typedef void   (__thiscall *FnV3pii)(void*, void*, int, int);
void DeleteObj(void* p);              // 0x00f47380
void* __cdecl OperatorNew(unsigned n, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void* __cdecl MessageServer();        // 0x0067dcc0
void  __fastcall FUN_00929c60(char* p);
void  __fastcall FUN_00816990(char* p);
void  __fastcall FUN_00678f70(char* p);   // = 0x00678f70 (matched in s006783c0)

// ---- callees shared with the recovered bodies --------------------------
void* __cdecl GetManager();                     // 0x00957f30 EA::UTFWin::GetManager
void* __cdecl SPPropertyManager();              // 0x0067de30
void  __cdecl EndModal(void* w, int a, int b);  // 0x00809c50 SPUIHelpers::EndModal
char  __cdecl VisitWindowTreeDepthFirst(void* win, void* fn, void* ctx); // 0x00807d30
void* __cdecl GetBoundingScreenRect(void* rect, void* win, char mode);   // 0x00808d20
void  __cdecl FUN_00678370(void* obj, void* win);                        // 0x00678370
unsigned char __cdecl FUN_00677f30(void* win, void* ctx);   // 0x00677f30 visitor
unsigned char __cdecl FUN_00678000(void* win, void* ctx);   // 0x00678000 visitor
unsigned char __cdecl FUN_00678050(void* win, void* ctx);   // 0x00678050 visitor

// ---- callees for the property-UI reconstruction (convention cast at use) -
void  FUN_00ac9480();   // 0x00ac9480  thiscall(self, void* out)
void  FUN_006a0840();   // 0x006a0840  cdecl GetPropertyAsUint32Array(props,key,out1,out2)
char  FUN_006a1400();   // 0x006a1400  cdecl GetPropertyAsString16(props,key,outStr)
void  FUN_004af210();   // 0x004af210  cdecl GetPropertyAsUint32(props,key,outU32)
void  FUN_00407190();   // 0x00407190  cdecl GetBoolProperty(props,key,outBool)
char  FUN_0064f350();   // 0x0064f350  cdecl (props,key,int)
void* FUN_0041ea00();   // 0x0041ea00  thiscall(prop) -> uint*
void* FUN_0041ea70();   // 0x0041ea70  thiscall(prop) -> float*
void  FUN_00435ed0();   // 0x00435ed0  stdcall KillSetiEffects(key,at)
void* FUN_00a206f0();   // 0x00a206f0  cdecl EA::Audio::GetSystemAT
void* FUN_00816cb0();   // 0x00816cb0  thiscall CalloutMessageBox ctor(self,parent)
void* FUN_00816ca0();   // 0x00816ca0  thiscall CalloutMessageBox::GetWindow(self)
void  FUN_00816a20();   // 0x00816a20  thiscall CalloutMessageBox::Show(self,a,b,f1,f2)
char  FUN_00817040();   // 0x00817040  thiscall cSPUIMessageBox::Init(self,&key,flag)
void  FUN_0092a7a0();   // 0x0092a7a0  thiscall Callback::Schedule(self,int)

// vtable-slot call helper.
#define VS(p, n) (((VObj*)(p))->vt[(n) / 4])
typedef void  (__thiscall *TC0)(void*);
typedef void  (__thiscall *TC1p)(void*, void*);
typedef void  (__thiscall *TC2i)(void*, int, int);
typedef void  (__thiscall *TCuup)(void*, unsigned, unsigned, void**);
typedef void  (__thiscall *TCff)(void*, float, float);
typedef void* (__thiscall *TCp0)(void*);
typedef void* (__thiscall *TCp2i)(void*, int, int);
typedef char  (__thiscall *TCq2)(void*, unsigned, void**);
typedef char  (__thiscall *TCq_pc)(void*, void*, char);
typedef void* (__thiscall *TCp_p)(void*, void*);

struct IRefObj {
    virtual void AddRef();    // vtable +0x00
    virtual void Release();   // vtable +0x04
};

struct RefVec {
    int* mpBegin;      // +0x00
    int* mpEnd;        // +0x04
    int* mpCapacity;   // +0x08
    int  mPad0c;       // +0x0c
    int* mpInline;     // +0x10
    int  mPad14;       // +0x14
    int  mInlineBuf[0x20];  // +0x18 .. +0x98
    void Assign(int* first, int* last, void* owner);  // 0x00679340
    void Erase(int* first, int* last);                // 0x00e25bd0
    void Insert(int* pos, void* val);                 // 0x006791a0
    void PushBack(void* val);                         // 0x006794e0
};

struct Str16 {
    unsigned short* mpBegin;    // +0x00
    unsigned short* mpEnd;      // +0x04
    unsigned short* mpCapacity; // +0x08
    int             mPad0c;     // +0x0c
    unsigned short* mpInline;   // +0x10
    unsigned short  mInlineBuf[0x20];  // +0x14 .. +0x54
    void Assign(const unsigned short* first, const unsigned short* last); // 0x00672750
    void Assign(const unsigned short* s);                                 // 0x00678ff0
};

// Returned by the property-manager lookups (SP::Property::GetProperty).
struct PropVal {
    void*         mpData;    // +0x00 (inline value, or pointer when referenced)
    unsigned int  mPad04[3]; // +0x04 .. +0x0f
    unsigned char mFlags;    // +0x10
    unsigned char mPad11;    // +0x11
    short         mType;     // +0x12
};

struct Elem {
    unsigned char mFlag;     // +0x00
    unsigned char mPad01[3];
    unsigned int  mKeyA;     // +0x04
    unsigned int  mKeyB;     // +0x08
    unsigned int  mKeyC;     // +0x0c
    IRefObj*      mpObj10;   // +0x10
    RefVec        mVec;      // +0x14
    IRefObj*      mpRef0;    // +0xac
    IRefObj*      mpRef1;    // +0xb0
    IRefObj*      mpRef2;    // +0xb4
    IRefObj*      mpRef3;    // +0xb8
    float         mX;        // +0xbc
    float         mY;        // +0xc0
    float         mF1;       // +0xc4
    float         mF2;       // +0xc8
    float         mF3;       // +0xcc
    float         mF4;        // +0xd0
    float         mF5;        // +0xd4
    Str16         mStr;      // +0xd8
    unsigned char mByte12c;  // +0x12c
    unsigned char mByte12d;  // +0x12d
    unsigned short mPad12e;
    unsigned int (__cdecl* mpFunc130)(void*); // +0x130
    Elem() {}
    Elem(int a, int b, int c, int d);   // 0x00679080
    Elem* CopyFrom(Elem* other);        // 0x00679b40
    Elem* AssignFrom(Elem* other);      // 0x00679c90
};

struct CbSub {
    unsigned int mPad[9];
    void Cancel();       // 0x00929c60  EA::CallbackSystem::Callback::Cancel
    void Schedule(int a); // 0x0092a7a0  EA::CallbackSystem::Callback::Schedule
};  // 0x24 bytes

struct Container {
    void*          mpVt00;   // +0x00
    unsigned int   mRef04;   // +0x04
    void*          mpVt08;   // +0x08
    void*          mpVt0c;   // +0x0c
    unsigned int   pad10;    // +0x10
    int* mpBlockBegin;       // +0x14
    int* mpCur;              // +0x18
    int* mpCurBlock;         // +0x1c
    int* mpCurBlockEnd;      // +0x20
    int* mpBlockEnd;         // +0x24
    int* mpEnd;              // +0x28
    unsigned int pad2c[4];   // +0x2c .. +0x3b
    Elem mElem;              // +0x3c
    unsigned int pad170[0xc];// +0x170 .. +0x19f
    unsigned char mByte1a0;  // +0x1a0
    unsigned char mByte1a1;  // +0x1a1
    unsigned char pad1a2[2];
    unsigned int pad1a4[4];  // +0x1a4 .. +0x1b3
    CbSub mCb1b4;            // +0x1b4
    CbSub mCb1d8;            // +0x1d8
    CbSub mCb1fc;            // +0x1fc
    void Push(Elem* other);      // 0x00679ff0
    char Process(Elem* local);   // 0x00679e50
    void Shutdown();             // 0x0067a090
    char ModifyBool(Elem* elem); // 0x00679630
    char Update(Elem* elem);     // 0x0067a1b0
};
struct Grow { void GrowVec(int a, int b); };       // 0x006780a0

// ---- 0x00679b40 : Elem copy-construct ---------------------------------
// @ 0x00679b40
Elem* Elem::CopyFrom(Elem* other) {
    mFlag = other->mFlag;
    mKeyA = other->mKeyA;
    mKeyB = other->mKeyB;
    mKeyC = other->mKeyC;
    mpObj10 = other->mpObj10;
    mVec.mpInline = mVec.mInlineBuf;
    mVec.mpEnd = mVec.mInlineBuf;
    mVec.mpBegin = mVec.mInlineBuf;
    mVec.mpCapacity = mVec.mInlineBuf + 0x20;
    mVec.Assign(other->mVec.mpBegin, other->mVec.mpEnd, other);
    mpRef0 = other->mpRef0;
    if (mpRef0) mpRef0->AddRef();
    mpRef1 = other->mpRef1;
    if (mpRef1) mpRef1->AddRef();
    mpRef2 = other->mpRef2;
    if (mpRef2) mpRef2->AddRef();
    mpRef3 = other->mpRef3;
    if (mpRef3) mpRef3->AddRef();
    mX = other->mX;
    mY = other->mY;
    mF1 = other->mF1;
    mF2 = other->mF2;
    mF3 = other->mF3;
    mF4 = other->mF4;
    mF5 = other->mF5;
    mStr.mpInline = mStr.mInlineBuf;
    mStr.mpCapacity = mStr.mInlineBuf + 0x20;
    mStr.mpEnd = mStr.mInlineBuf;
    mStr.mpBegin = mStr.mInlineBuf;
    *mStr.mpBegin = 0;
    mStr.Assign(other->mStr.mpBegin, other->mStr.mpEnd);
    mByte12c = other->mByte12c;
    mByte12d = other->mByte12d;
    mpFunc130 = other->mpFunc130;
    return this;
}

// ---- 0x00679c90 : Elem assign -----------------------------------------
// @ 0x00679c90
Elem* Elem::AssignFrom(Elem* other) {
    mFlag = other->mFlag;
    mKeyA = other->mKeyA;
    mKeyB = other->mKeyB;
    mKeyC = other->mKeyC;
    mpObj10 = other->mpObj10;
    if (&mVec != &other->mVec) {
        mVec.Erase(mVec.mpBegin, mVec.mpEnd);
        mVec.Assign(other->mVec.mpBegin, other->mVec.mpEnd, other);
    }
    if (other->mpRef0 != mpRef0) {
        if (other->mpRef0) other->mpRef0->AddRef();
        IRefObj* old = mpRef0;
        mpRef0 = other->mpRef0;
        if (old) old->Release();
    }
    if (other->mpRef1 != mpRef1) {
        if (other->mpRef1) other->mpRef1->AddRef();
        IRefObj* old = mpRef1;
        mpRef1 = other->mpRef1;
        if (old) old->Release();
    }
    if (other->mpRef2 != mpRef2) {
        if (other->mpRef2) other->mpRef2->AddRef();
        IRefObj* old = mpRef2;
        mpRef2 = other->mpRef2;
        if (old) old->Release();
    }
    if (other->mpRef3 != mpRef3) {
        if (other->mpRef3) other->mpRef3->AddRef();
        IRefObj* old = mpRef3;
        mpRef3 = other->mpRef3;
        if (old) old->Release();
    }
    mX = other->mX;
    mY = other->mY;
    mF1 = other->mF1;
    mF2 = other->mF2;
    mF3 = other->mF3;
    mF4 = other->mF4;
    mF5 = other->mF5;
    if (&mStr != &other->mStr) {
        if (mStr.mpBegin != mStr.mpEnd) {
            *mStr.mpBegin = 0;
            mStr.mpEnd = mStr.mpBegin;
        }
        mStr.Assign(other->mStr.mpBegin, other->mStr.mpEnd);
    }
    mByte12c = other->mByte12c;
    mByte12d = other->mByte12d;
    mpFunc130 = other->mpFunc130;
    return this;
}

// ---- 0x00679e50 : container reset / element teardown -------------------
struct VisitCtx { IRefObj* mpResult; unsigned char mFlag; char pad[3]; };
// @ 0x00679e50
char Container::Process(Elem* elem) {
    void* mgr = GetManager();
    if (((char (__thiscall*)(void*, void*))VS(mgr, 0x80))(mgr, mElem.mpRef3))
        EndModal(mElem.mpRef3, 0, 0);
    IRefObj* o10 = elem->mpObj10;
    if (o10) o10->AddRef();
    mByte1a1 = 0;
    mCb1b4.Cancel();
    mCb1d8.Cancel();
    if (elem->mFlag) {
        int n = (int)(elem->mVec.mpEnd - elem->mVec.mpBegin);
        int* begin = elem->mVec.mpBegin;
        for (int i = 0; i < n; ++i) {
            IRefObj* w = (IRefObj*)begin[i];
            if (w) {
                VisitCtx ctx;
                ctx.mpResult = 0;
                ctx.mFlag = elem->mByte12c;
                VisitWindowTreeDepthFirst(w, (void*)FUN_00677f30, &ctx);
                IRefObj* r = ctx.mpResult;
                if (r) r->Release();
            }
        }
        if (elem->mpRef0) {
            if (mElem.mpRef0 == elem->mpRef0) {
                Elem tmp(0, 0, 0, 0);
                mElem.AssignFrom(&tmp);
                FUN_00678f70((char*)&tmp);
                mElem.mFlag = 0;
            }
            FUN_00816990((char*)elem->mpRef0);
        }
        IRefObj* p3 = elem->mpRef3;
        if (p3) { elem->mpRef3 = 0; p3->Release(); }
        IRefObj* p1 = elem->mpRef1;
        if (p1) { elem->mpRef1 = 0; p1->Release(); }
        IRefObj* p0 = elem->mpRef0;
        if (p0) { elem->mpRef0 = 0; p0->Release(); }
        elem->mVec.Erase(elem->mVec.mpBegin, elem->mVec.mpEnd);
        elem->mFlag = 0;
    }
    return 1;
}

// ---- 0x0067a090 : SP::Achievements::Controller::Shutdown -------------
// @ 0x0067a090
void Container::Shutdown() {
    char* thisp = (char*)this;
    void* set = thisp ? thisp + 0xc : 0;
    void* srv = MessageServer();
    ((FnV3pii)((VObj*)srv)->vt[0x2c / 4])(srv, set, 0x670eccd, -0x270f);
    FUN_00929c60(thisp + 0x1b4);
    FUN_00929c60(thisp + 0x1d8);
    FUN_00929c60(thisp + 0x1fc);
    int e = *(int*)(thisp + 0x18);
    if (e != *(int*)(thisp + 0x28)) {
        Elem local;
        local.CopyFrom((Elem*)e);
        char* lp = (char*)&local;
        if (*(void**)(lp + 0xac)) FUN_00816990(*(char**)(lp + 0xac));
        FUN_00678f70(lp);
    }
}

// ---- 0x00679ff0 : container push (copies into a new block slot) ------
// @ 0x00679ff0
void Container::Push(Elem* other) {
    char* thisp = (char*)this;
    Elem local;
    local.CopyFrom(other);
    int n = (*(int*)(thisp + 0x24) - *(int*)thisp) >> 2;
    if (n + 1 >= *(int*)(thisp + 4))
        ((Grow*)thisp)->GrowVec(1, 1);
    void* p = OperatorNew(0x4d0, "Editor", 0, 0, "allocator.h", 0xd1);
    *(void**)(*(int*)(thisp + 0x24) + 4) = p;
    if (*(int*)(thisp + 0x18) != 0)
        (*(Elem**)(thisp + 0x18))->CopyFrom(&local);
    int q = *(int*)(thisp + 0x24);
    *(int*)(thisp + 0x24) = q + 4;
    int v = *(int*)(q + 4);
    *(int*)(thisp + 0x1c) = v;
    *(int*)(thisp + 0x20) = v + 0x4d0;
    *(int*)(thisp + 0x18) = *(int*)(thisp + 0x1c);
    FUN_00678f70((char*)&local);
}

// ---- 0x0067a120 : destroy every element ------------------------------
// @ 0x0067a120
void __fastcall FUN_0067a120(char* p) {
    if (*(int*)(p + 0x18) == *(int*)(p + 0x28)) return;
    do {
        Elem local;
        char* elem = *(char**)(p + 0x18);
        local.CopyFrom((Elem*)elem);
        int n = (int)elem + 0x134;
        if (n == *(int*)(p + 0x20)) {
            FUN_00678f70(elem);
            if (*(int*)(p + 0x1c)) DeleteObj(*(void**)(p + 0x1c));
            int* q = (int*)(*(int*)(p + 0x24) + 4);
            *(int**)(p + 0x24) = q;
            int v = *q;
            *(int*)(p + 0x1c) = v;
            *(int*)(p + 0x20) = v + 0x4d0;
            *(int*)(p + 0x18) = *(int*)(p + 0x1c);
        } else {
            *(int*)(p + 0x18) = n;
            FUN_00678f70(elem);
        }
        ((Container*)p)->Process(&local);
        FUN_00678f70((char*)&local);
    } while (*(int*)(p + 0x18) != *(int*)(p + 0x28));
}

// ---- 0x00679630 : cPropertyUI::ModifyBool ----------------------------
struct ModifyCtx { void* mpObj; void* mpOut; };
// @ 0x00679630
char Container::ModifyBool(Elem* elem) {
    IRefObj* pProp = 0;
    void* mgr;
    int flag = 0;
    void* pm = SPPropertyManager();
    if (pProp) { IRefObj* t = pProp; pProp = 0; ((TC0)VS(t, 4))(t); }
    ((TCuup)VS(pm, 0x2c))(pm, elem->mKeyA, elem->mKeyC, (void**)&pProp);
    { void* m = GetManager(); mgr = ((TCp0)VS(m, 4))(m); }
    if (pProp) {
        PropVal* out = 0;
        if (((TCq2)VS(pProp, 0x24))(pProp, 0x64bd8e9u, (void**)&out)) {
            if (out->mType == 10) {
                unsigned v = *(unsigned*)((TCp0)FUN_0041ea00)(out);
                if (v) {
                    void* t = ((TCp2i)VS(mgr, 0xf0))(mgr, (int)v, 1);
                    if (t) mgr = t;
                }
            }
        }
    }
    if (elem->mX == -1.0f && elem->mY == -1.0f && elem->mpRef1 == 0) {
        if (pProp == 0) goto L94e;
        {
            unsigned v = 0;
            ((void (__cdecl*)(void*, unsigned, void*))FUN_004af210)(pProp, 0x615a45eu, &v);
            if (v == 0 && elem->mpFunc130)
                v = elem->mpFunc130(pProp);
            bool b = false;
            ((void (__cdecl*)(void*, unsigned, void*))FUN_00407190)(pProp, 0x761fbbdu, &b);
            if (v == 0 && !b) goto L785;
            char c = ((char (__cdecl*)(void*, unsigned, int))FUN_0064f350)(pProp, 0x6280c2fu, 0);
            ModifyCtx ctx;
            ctx.mpObj = (void*)v;
            ctx.mpOut = 0;
            void* visitor = c ? (void*)FUN_00678000 : (void*)FUN_00678050;
            VisitWindowTreeDepthFirst(mgr, visitor, &ctx);
            ((void (__thiscall*)(void*, void*))FUN_00ac9480)(&elem->mpRef1, &ctx.mpOut);
            if (elem->mpRef1) {
                float r[4];
                float* rp = (float*)GetBoundingScreenRect(r, elem->mpRef1, 0);
                float fx = (rp[2] + rp[0]) * 0.5f;
                float fy = (rp[3] + rp[1]) * 0.5f;
                elem->mX = fx; elem->mF2 = fx;
                elem->mY = fy; elem->mF3 = fy;
                elem->mVec.PushBack(&elem->mpRef1);
            }
            if (ctx.mpOut) ((TC0)VS(ctx.mpOut, 4))(ctx.mpOut);
        }
    }
L85a:
    if (pProp == 0) goto L94e;
    {
        PropVal* out = 0;
        if (!((TCq2)VS(pProp, 0x24))(pProp, 0x75e3dbdu, (void**)&out)) goto L94e;
        if (out->mType != 10) goto L94e;
        unsigned v = *(unsigned*)((TCp0)FUN_0041ea00)(out);
        if (v == 0) goto L94e;
        if (elem->mpRef1 == 0) goto L94e;
        void* val;
        void* t = 0;
        if ((unsigned)(int)((TCp0)VS(elem->mpRef1, 0x1c))(elem->mpRef1) == v) {
            val = elem->mpRef1;
        } else {
            t = ((TCp2i)VS(elem->mpRef1, 0xf0))(elem->mpRef1, (int)v, 1);
            if (t) ((TC0)VS(t, 0))(t);
            flag = 1;
            val = t;
        }
        if (flag && t) ((TC0)VS(t, 4))(t);
        if (val == 0) goto L94a;
        ((TC0)VS(val, 0))(val);
        { void* slot = val; elem->mVec.PushBack(&slot); if (slot) ((TC0)VS(slot, 4))(slot); }
        goto L933;
    }
L94a:
L94e:
    if (elem->mX == -1.0f || elem->mY == -1.0f) goto L785;
    {
        unsigned* arr = 0;
        int count = 0;
        ((void (__cdecl*)(void*, unsigned, void*, void*))FUN_006a0840)(pProp, 0x64bd8e8u, &count, &arr);
        for (int i = 0; i < count; ++i) {
            unsigned w = arr[i];
            if (w == 0) continue;
            void* val;
            if ((unsigned)(int)((TCp0)VS(mgr, 0x1c))(mgr) == w) {
                val = mgr;
            } else {
                val = ((TCp2i)VS(mgr, 0xf0))(mgr, (int)w, 1);
                if (val == 0) continue;
            }
            void* slot = val;
            ((TC0)VS(val, 0))(val);
            if (elem->mVec.mpEnd < elem->mVec.mpCapacity) {
                int* p = elem->mVec.mpEnd;
                elem->mVec.mpEnd = p + 1;
                *(void**)p = val;
                if (val) ((TC0)VS(val, 0))(val);
            } else {
                elem->mVec.Insert(elem->mVec.mpEnd, &slot);
            }
            if (val) ((TC0)VS(val, 4))(val);
        }
        {
            if (pProp) {
                PropVal* pv = 0;
                if (((TCq2)VS(pProp, 0x24))(pProp, 0x64beceeu, (void**)&pv)) {
                    if (pv->mType == 1) {
                        void* q = (pv->mFlags & 0x30) ? pv->mpData : (void*)pv;
                        elem->mByte12c = *(unsigned char*)q;
                    } else {
                        elem->mByte12c = 1;
                    }
                } else {
                    elem->mByte12c = 1;
                }
            } else {
                elem->mByte12c = 1;
            }
            void* t3 = 0;
            bool got3 = false;
            if (pProp) {
                PropVal* p3 = 0;
                if (((TCq2)VS(pProp, 0x24))(pProp, 0x652468fu, (void**)&p3)) {
                    if (p3->mType == 10) {
                        unsigned x = (p3->mFlags & 0x30)
                            ? *(unsigned*)p3->mpData
                            : *(unsigned*)p3;
                        if (x) {
                            void* o = ((TCp2i)VS(mgr, 0xf0))(mgr, (int)x, 1);
                            t3 = o;
                            got3 = true;
                        }
                    }
                }
            }
            if (!got3) {
                if (elem->mpRef1 == 0) goto L933;
                if (((unsigned (__thiscall*)(void*, unsigned))VS(elem->mpRef1, 0xc))(elem->mpRef1, 0x8ed27e7au) == 0)
                    goto L933;
                t3 = elem->mpRef1;
            }
            {
                IRefObj* old3 = elem->mpRef3;
                if ((IRefObj*)t3 != old3) {
                    if (t3) ((TC0)VS(t3, 0))(t3);
                    elem->mpRef3 = (IRefObj*)t3;
                    if (old3) ((TC0)VS(old3, 4))(old3);
                }
            }
        }
    }
L933:
    if (pProp) ((TC0)VS(pProp, 4))(pProp);
    return 1;
L785:
    if (pProp) ((TC0)VS(pProp, 4))(pProp);
    return 0;
}

// ---- 0x0067a1b0 : property UI update ---------------------------------
struct StrLocal { unsigned short* mpBegin; unsigned short* mpEnd; unsigned short* mpCapacity; };
// @ 0x0067a1b0
char Container::Update(Elem* elem) {
    IRefObj* pProp = 0;
    char modify = ModifyBool(elem);
    void* pm = SPPropertyManager();
    if (pProp) { IRefObj* t = pProp; pProp = 0; ((TC0)VS(t, 4))(t); }
    ((TCuup)VS(pm, 0x2c))(pm, elem->mKeyA, elem->mKeyC, (void**)&pProp);
    void* boxmem = OperatorNew(0x78, "UI/CalloutMessageBox", 0, 0, 0, 0);
    void* box = 0;
    if (boxmem)
        box = ((TCp_p)FUN_00816cb0)(boxmem, (char*)this + 0x170);
    {
        IRefObj* old = elem->mpRef0;
        if ((IRefObj*)box != old) {
            if (box) ((TC0)VS(box, 0))(box);
            elem->mpRef0 = (IRefObj*)box;
            if (old) ((TC0)VS(old, 4))(old);
        }
    }
    char ok = ((TCq_pc)FUN_00817040)((void*)elem->mpRef0, &elem->mKeyA, 1);
    if (ok) {
        void* at = ((void* (__cdecl*)(void))FUN_00a206f0)();
        at = at ? ((TCp0)VS(at, 0x20))(at) : 0;
        ((void (__stdcall*)(unsigned, void*))FUN_00435ed0)(0x2c1b3216u, at);
        ((void (__thiscall*)(void*, void*, void*, float, float))FUN_00816a20)(
            (void*)elem->mpRef0, (void*)0x15112d6, (void*)0x15112d2, -1.0f, -1.0f);
        float f1 = 0.5f;
        {
            PropVal* out = 0;
            if (pProp && ((TCq2)VS(pProp, 0x24))(pProp, 0x678b195u, (void**)&out) && out->mType == 0xd)
                f1 = *(float*)((TCp0)FUN_0041ea70)(out);
        }
        float f2 = 0.5f;
        {
            PropVal* out = 0;
            if (pProp && ((TCq2)VS(pProp, 0x24))(pProp, 0x64bd8efu, (void**)&out) && out->mType == 0xd)
                f2 = *(float*)((TCp0)FUN_0041ea70)(out);
        }
        void* win = ((TCp0)FUN_00816ca0)((void*)elem->mpRef0);
        FUN_00678370((char*)this + 8, win);
        float* r1 = (float*)((TCp0)VS(win, 0x38))(win);
        float x1 = r1[0], y1 = r1[1], x2 = r1[2], y2 = r1[3];
        void* par = ((TCp0)VS(win, 0x10))(win);
        float* r2 = (float*)((TCp0)VS(par, 0x38))(par);
        float px1 = r2[0], py1 = r2[1], px2 = r2[2], py2 = r2[3];
        float tx = px2 - (x2 - x1);
        float nx = (px1 < tx) ? (tx - px1) * (1.0f - f1) + px1 : x1;
        float ty = py2 - (y2 - y1);
        float ny = (ty > py1) ? (ty - py1) * (1.0f - f2) + py1 : y1;
        ((TCff)VS(win, 0x70))(win, nx, ny);
        if (modify) {
            void* t2 = ((TCp2i)VS(win, 0xf0))(win, 0x64be838, 1);
            if (t2) ((TC0)VS(t2, 0))(t2);
            IRefObj* old2 = elem->mpRef2;
            if ((IRefObj*)t2 != old2) {
                if (t2) ((TC0)VS(t2, 0))(t2);
                elem->mpRef2 = (IRefObj*)t2;
                if (old2) ((TC0)VS(old2, 4))(old2);
            }
            if (t2) {
                StrLocal sl;
                sl.mpBegin = (unsigned short*)0x1667bac;
                sl.mpEnd = (unsigned short*)0x1667bac;
                sl.mpCapacity = (unsigned short*)0x1667bae;
                char sok = ((char (__cdecl*)(void*, unsigned, void*))FUN_006a1400)(pProp, 0x64bd9cau, &sl);
                if (sok) elem->mStr.Assign(sl.mpBegin);
                ((void (__thiscall*)(void*, int, int))VS(t2, 0x7c))(t2, 1, 0);
                if (elem->mpRef3)
                    ((TC1p)VS(elem->mpRef3, 0x104))(elem->mpRef3, (char*)this + 8);
                ((void (__thiscall*)(void*, int))FUN_0092a7a0)(&this->mCb1b4, 1);
                if ((((int)sl.mpCapacity - (int)sl.mpBegin) & 0xfffffffe) > 2 && sl.mpBegin)
                    DeleteObj(sl.mpBegin);
                ((TC0)VS(t2, 4))(t2);
            }
        }
    }
    elem->mFlag = (unsigned char)ok;
    this->mElem.AssignFrom(elem);
    if (pProp) ((TC0)VS(pProp, 4))(pProp);
    return ok;
}