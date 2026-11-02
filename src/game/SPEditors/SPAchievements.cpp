// src/game/SPEditors/SPAchievements.cpp -- migrated from slice(s) s006783c0, s0067a590, s00679630, s006755c0, s00674640 by tools/migrate/rewrite.py
// Object file: SPEditors/SPAchievements.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"
#include "SP/cString.h"
#include "SP/cVarListSerializer.h"

// unnamed retail callees and globals (address in the comment)
extern void EA_IO_WriteUint32(void* w, void* p, int n, int a); // 0x0093aa70
extern char g_1529330;   // [0x01529330]
#include <string.h>
#include <wchar.h>
#include "EA/UTFWinExtras/WinXHTML.h"
#include "EA/UTFWinExtras/cXHTMLFrameSet.h"
#include <math.h>
#pragma intrinsic(strlen, wcscmp, wcslen)

// ---- items of slice s00674640 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct VObj { void** vt; };
typedef void   (__thiscall *FnV3ipi)(void*, void*, int, void*);
typedef void*  (__thiscall *FnVp0)(void*);
void* __cdecl PropertyManager();          // 0x0067de30
void WriteIntVal(int* io, int v) {
    int* o = (int*)((FnVp0)((VObj*)io)->vt[0x20 / 4])(io);
    void* w = (void*)((FnVp0)((VObj*)o)->vt[0x18 / 4])(o);
    EA_IO_WriteUint32(w, &v, 1, 0);
}
struct cVarListSerializer {
    char data[0x18];
    cVarListSerializer(void* owner, void* key, int id);  // 0x00692f90
    void Serialize(int* io);                             // 0x00692900
};
struct CVarList {
    char pad[0xc];
    int* mpBegin;  // +0xc
    int* mpEnd;    // +0x10
    void Serialize(int* io);
};
// ---- items of slice s00674640 end

// ---- items of slice s00679630 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void   (__thiscall *FnV3pii)(void*, void*, int, int);
void DeleteObj(void* p);              // 0x00f47380
void* __cdecl OperatorNew(unsigned n, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void* __cdecl MessageServer();        // 0x0067dcc0
void  __fastcall FUN_00929c60(char* p);
void  __fastcall FUN_00816990(char* p);
void  __fastcall FUN_00678f70(char* p);   // = 0x00678f70 (matched in s006783c0)
void* __cdecl SPPropertyManager();              // 0x0067de30
char  __cdecl VisitWindowTreeDepthFirst(void* win, void* fn, void* ctx); // 0x00807d30
void* __cdecl GetBoundingScreenRect(void* rect, void* win, char mode);   // 0x00808d20
void  __cdecl FUN_00678370(void* obj, void* win);                        // 0x00678370
unsigned char __cdecl FUN_00677f30(void* win, void* ctx);   // 0x00677f30 visitor
unsigned char __cdecl FUN_00678000(void* win, void* ctx);   // 0x00678000 visitor
unsigned char __cdecl FUN_00678050(void* win, void* ctx);   // 0x00678050 visitor
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
#define VS(p, n) (((VObj*)(p))->vt[(n) / 4])
typedef void  (__thiscall *TC0)(void*);
typedef void  (__thiscall *TC1p)(void*, void*);
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
struct CbSub_s0067_9630 {
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
    CbSub_s0067_9630 mCb1b4;            // +0x1b4
    CbSub_s0067_9630 mCb1d8;            // +0x1d8
    CbSub_s0067_9630 mCb1fc;            // +0x1fc
    void Push(Elem* other);      // 0x00679ff0
    char Process(Elem* local);   // 0x00679e50
    void Shutdown();             // 0x0067a090
    char ModifyBool(Elem* elem); // 0x00679630
    char Update(Elem* elem);     // 0x0067a1b0
};
struct VisitCtx { IRefObj* mpResult; unsigned char mFlag; char pad[3]; };
struct ModifyCtx { void* mpObj; void* mpOut; };
struct StrLocal { unsigned short* mpBegin; unsigned short* mpEnd; unsigned short* mpCapacity; };
// ---- items of slice s00679630 end

// ---- items of slice s0067a590 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl ConfigManager();     // FUN_0067dd30
extern "C" void* __cdecl GetManager();        // FUN_00957f30
extern "C" void* __cdecl FUN_0067caf0();
extern "C" void __cdecl BeginModal(void*, int, int);   // 0x008099a0 SPUIHelpers::BeginModal
extern "C" void __cdecl EndModal(void*, int, int);     // 0x00809c50 SPUIHelpers::EndModal
static inline void** VT(void* p) { return *(void***)p; }
struct HM590;
struct Elem134 {
    char data[0x134];
    Elem134(Elem134* src);   // 679b40
    ~Elem134();              // 678f70
};
struct Sub10 {
    char p0[8];
    Elem134* begin;          // +8  (abs +0x18)
    char p1[0xc];
    Elem134* end;            // +0x18 (abs +0x28)
    void Release();          // 6792f0
};
struct Sub1fc {
    void method(int);        // 92a7a0
};
struct HM590 {
    char pad0[0x10];
    Sub10 sub;               // +0x10
    char pad1[0x1cc];
    void Start();            // 67a120
    bool Check(Elem134*);    // 67a1b0
    void Add(Elem134*);      // 679e50
    void possibly(char a, char b);
};
struct C_a590_fwd {
    void possibly(int a, int b);   // 0x0067a590 (same retail method as HM590::possibly)
};
struct C_a120_h {
    void f_67a120();
};
struct C_a6a0 {
    bool handle(int msg, void* data);
};
struct Proc {
    virtual bool Evaluate(int conditionID) = 0;
};
struct VecU {
    int* begin;   // +0
    int* end;     // +4
};
struct C_af {
    char pad0[0xc];
    Proc** pbegin;   // +0xc
    Proc** pend;     // +0x10
    bool All(VecU* v);
    bool Any(VecU* v);
    bool Check(void* a);
};
bool C_af::Any(VecU* v)
{
    unsigned n = (unsigned)(v->end - v->begin) >> 2;
    for (unsigned i = 0; i < n; ++i) {
        if (pend != pbegin) {
            Proc* p = *(pend - 1);
            if (p->Evaluate(v->begin[i]))
                return false;
        }
    }
    return true;
}
bool C_af::Check(void* a)
{
    char* b = (char*)a;
    if (!All((VecU*)(b + 0xc)))
        return false;
    if (((*(int*)(b + 0x24) - *(int*)(b + 0x20)) & 0xfffffffc) != 0
        && !Any((VecU*)(b + 0x20)))
        return false;
    if (((*(int*)(b + 0x38) - *(int*)(b + 0x34)) & 0xfffffffc) != 0
        && All((VecU*)(b + 0x34)))
        return false;
    return true;
}
struct Pt2 {
    float x, y;
    Pt2() {}
    Pt2(float a, float b) : x(a), y(b) {}
    Pt2(const Pt2& o) : x(o.x), y(o.y) {}
    Pt2& operator=(const Pt2& o) { x = o.x; y = o.y; return *this; }
};
struct HMsg {
    int d0, d4;
    int type;      // +0x8
    float px, py;  // +0xc
    int d14, d18;
};
struct HitParent {
virtual void hp0();
virtual void hp1();
virtual void hp2();
virtual void hp3();
virtual void hp4();
virtual void hp5();
virtual void hp6();
virtual void hp7();
virtual void hp8();
virtual void hp9();
virtual void hp10();
virtual void hp11();
virtual void hp12();
virtual void hp13();
virtual void hp14();
virtual void hp15();
virtual void hp16();
    virtual void* HitTest(Pt2* pt);   // +0x44
};
struct HintWin {
virtual void wa0();
virtual void wa1();
virtual void wa2();
virtual void wa3();
virtual void wa4();
    virtual HitParent* GetParent();   // +0x14
virtual void wb0();
virtual void wb1();
virtual void wb2();
virtual void wb3();
virtual void wb4();
virtual void wb5();
virtual void wb6();
virtual void wb7();
virtual void wb8();
virtual void wb9();
virtual void wb10();
virtual void wb11();
virtual void wb12();
virtual void wb13();
virtual void wb14();
virtual void wb15();
virtual void wb16();
virtual void wb17();
virtual void wb18();
virtual void wb19();
virtual void wb20();
virtual void wb21();
virtual void wb22();
virtual void wb23();
virtual void wb24();
virtual void wb25();
virtual void wb26();
virtual void wb27();
virtual void wb28();
virtual void wb29();
virtual void wb30();
virtual void wb31();
virtual void wb32();
virtual void wb33();
virtual void wb34();
virtual void wb35();
virtual void wb36();
virtual void wb37();
virtual void wb38();
virtual void wb39();
virtual void wb40();
virtual void wb41();
    virtual Pt2 ToLocal(Pt2 pt);      // +0xc0
};
struct WinMgr {
virtual void ma0();
virtual void ma1();
virtual void ma2();
virtual void ma3();
virtual void ma4();
virtual void ma5();
    virtual void Send(int a, int b, HMsg* m);   // +0x18
virtual void mb0();
virtual void mb1();
virtual void mb2();
virtual void mb3();
virtual void mb4();
virtual void mb5();
virtual void mb6();
virtual void mb7();
virtual void mb8();
virtual void mb9();
virtual void mb10();
virtual void mb11();
virtual void mb12();
virtual void mb13();
virtual void mb14();
virtual void mb15();
virtual void mb16();
virtual void mb17();
virtual void mb18();
virtual void mb19();
virtual void mb20();
virtual void mb21();
virtual void mb22();
virtual void mb23();
virtual void mb24();
    virtual char IsModal(void* w);    // +0x80
};
struct CbSub {
    void Cancel();   // 0x00929c60 EA::CallbackSystem::Callback::Cancel
};
struct HM6e0 {
    char pad0[0xec];
    void* p_ec;          // +0xec
    char padF0[0x199 - 0xf0];
    char b199;           // +0x199
    char pad19a[0x1f4 - 0x19a];
    CbSub sub1f4;        // +0x1f4
    bool handle(HintWin* win, HMsg* msg);
};
// ---- items of slice s0067a590 end

// ---- items of slice s006755c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gpEmptyBucketArray[2];   // 0x0154DF28
void EAFree(void* p);                                                            // 0x00F47380
struct HashInsertResult {
    void* mpNode;     // +0x00
    void* mpBucket;   // +0x04
    char  mbInserted; // +0x08
};
struct UIntHashTable {
    char     mPad00[4];       // +0x00  use_first/equal_to/hash/mod_range_hashing
    void**   mpBucketArray;   // +0x04
    uint32_t mnBucketCount;   // +0x08
    uint32_t mnElementCount;  // +0x0c
    float    mfMaxLoadFactor; // +0x10
    float    mfGrowthFactor;  // +0x14
    uint32_t mnNextResize;    // +0x18
    char     mAllocator[4];   // +0x1c

    void DoFreeNodes(void** pNodeArray, uint32_t n);   // 0x006B6570
    void rehash(uint32_t nNewBucketCount);             // 0x00675650
    // Returns pResult (the original leaves it in eax) - 0x006758A0
    HashInsertResult* DoInsertValue(HashInsertResult* pResult, const uint32_t* pKey, bool bHint);

    // eastl::hashtable default construction (the allocator member is left as-is).
    void init()
    {
        mfMaxLoadFactor = 1.0f;
        mfGrowthFactor  = 2.0f;
        mnElementCount  = 0;
        mnNextResize    = 0;
        mnBucketCount   = 1;
        mpBucketArray   = &gpEmptyBucketArray[0];
    }

    void reset()
    {
        mnBucketCount  = 1;
        mpBucketArray  = &gpEmptyBucketArray[0];
        mnElementCount = 0;
        mnNextResize   = 0;
    }
    void clear()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
    ~UIntHashTable()
    {
        clear();
        if (mnBucketCount > 1)
            EAFree(mpBucketArray);
    }
};
struct FourHashMaps {
    UIntHashTable m0;   // +0x00
    UIntHashTable m1;   // +0x20
    UIntHashTable m2;   // +0x40
    UIntHashTable m3;   // +0x60
    ~FourHashMaps();
};
struct IPropStream {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
    virtual void* GetStream();                                 // +0x18
};
struct IPropWriter {
    virtual bool Begin(const wchar_t* pName);                  // +0x00
    virtual bool End(const wchar_t* pName);                    // +0x04
    virtual bool Attr(const wchar_t* pName, const wchar_t* pValue);  // +0x08
    virtual bool Text(const wchar_t* pText);                   // +0x0c
virtual void v10();
virtual void v14();
virtual void v18();
    virtual void NextEntry();                                  // +0x1c
    virtual IPropStream* GetWriter();                          // +0x20
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
    virtual bool ReadProp(void* pData, int nSize);             // +0x38
};
void      __cdecl EA_IO_ReadInt32(void* pStream, void* pValue, int nCount, int nFlags);          // 0x0093A780
struct U32Vec {
    uint32_t* mpBegin;   // +0x00
    uint32_t* mpEnd;     // +0x04
    uint32_t* mpCap;     // +0x08
    void DoInsertValue(uint32_t* pPos, const uint32_t* pValue);   // 0x005481D0
};
struct SubjectA {
    void*        mpVtbl0;    // +0x00
    void*        mpVtbl1;    // +0x04
    uint32_t     mu08;       // +0x08
    uint32_t     mu0c;       // +0x0c  block freed with EAFree
    uint32_t     mu10;       // +0x10
    uint32_t     mu14;       // +0x14
    uint32_t     mu18;       // +0x18  untouched by the constructor
    uint32_t     mu1c;       // +0x1c
    uint32_t     mu20;       // +0x20
    uint32_t     mu24;       // +0x24  block freed with EAFree
    uint32_t     mu28;       // +0x28
    uint32_t     mu2c;       // +0x2c
    uint32_t     mu30;       // +0x30  untouched by the constructor
    uint32_t     mu34;       // +0x34
    uint32_t     mu38;       // +0x38
    FourHashMaps mMaps;      // +0x3c
    SubjectA* Ctor();        // 0x00675D70
};
struct VObject {
    virtual void v0();   // +0x00
    virtual void v1();   // +0x04
    virtual void v2();   // +0x08
};
struct SubjectB {
    void*        mpVtbl;  // +0x00
    VObject*     mp04;    // +0x04
    VObject*     mp08;    // +0x08
    void*        mp0c;    // +0x0c  block freed with EAFree
    uint32_t     mu10;    // +0x10
    uint32_t     mu14;    // +0x14
    uint32_t     mu18;    // +0x18  untouched by the constructor
    uint32_t     mu1c;    // +0x1c
    uint32_t     mu20;    // +0x20
    char         mb24;    // +0x24
    char         mPad25[3];
    FourHashMaps mMaps;   // +0x28
};
// ---- items of slice s006755c0 end

// ---- items of slice s006783c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(sqrt, atan2, fabs)
typedef void (__thiscall *FnV1)(void*);
void __fastcall FUN_008e2b20(char* p);
// ---- items of slice s006783c0 end

// @ 0x006751a0
void __stdcall FUN_006751a0(void* a, void* b)
{
    void* pm = PropertyManager();
    ((FnV3ipi)((VObj*)pm)->vt[0x2c / 4])(pm, a, 0x5befd27, b);
}

// @ 0x006751c0
bool __stdcall FUN_006751c0(unsigned* p)
{
    switch ((*p >> 8) & 7) {
    case 0: return p[1] >= p[2];
    case 1: return p[1] > p[2];
    case 2: return p[1] == p[2];
    case 3: return p[1] < p[2];
    case 4: return p[1] <= p[2];
    case 5: return p[1] != p[2];
    default: return false;
    }
}

// @ 0x00675260
void CVarList::Serialize(int* io)
{
    WriteIntVal(io, 1);
    WriteIntVal(io, (mpEnd - mpBegin) >> 4);
    for (int* p = mpBegin; p != mpEnd; p += 4) {
        WriteIntVal(io, p[0]);
        WriteIntVal(io, p[2]);
    }
    cVarListSerializer s((void*)this, &g_1529330, 0x1a80d26);
    s.Serialize(io);
}

// @ 0x00675370
int __fastcall FUN_00675370(char* p)
{
    if (p[0x24] == 0) return *(int*)(p + 8) + 0x3c;
    return (int)(p + 0x28);
}

// @ 0x00675cc0
FourHashMaps::~FourHashMaps()
{}

// @ 0x00675d70
SubjectA* __fastcall FUN_00675d70(SubjectA* pThis)
{
    // The IEventModifier base constructor installs its own vtable first; it is then
    // replaced by the derived table below.
    *(void* volatile*)&pThis->mpVtbl1 = (void*)0x013EF094;    // SP::Audio::IEventModifier vtable
    pThis->mu08    = 0;
    pThis->mpVtbl0 = (void*)0x01401178;
    pThis->mpVtbl1 = (void*)0x01401174;
    pThis->mu0c    = 0;
    pThis->mu10    = 0;
    pThis->mu14    = 0;
    pThis->mu24    = 0;
    pThis->mu28    = 0;
    pThis->mu2c    = 0;
    pThis->mMaps.m0.init();
    pThis->mMaps.m1.init();
    pThis->mMaps.m2.init();
    pThis->mMaps.m3.init();
    return pThis;
}

// @ 0x006763e0
SubjectB* __fastcall FUN_006763e0(SubjectB* pThis)
{
    pThis->mpVtbl = (void*)0x0140116C;
    pThis->mp04   = 0;
    pThis->mp08   = 0;
    pThis->mp0c   = 0;
    pThis->mu10   = 0;
    pThis->mu14   = 0;
    pThis->mb24   = 0;
    pThis->mMaps.m0.init();
    pThis->mMaps.m1.init();
    pThis->mMaps.m2.init();
    pThis->mMaps.m3.init();
    return pThis;
}

// @ 0x00676490
void* __fastcall FUN_00676490(SubjectB* pThis, int, int nFlags)
{
    pThis->mpVtbl = (void*)0x0140116C;
    pThis->mMaps.~FourHashMaps();
    if (pThis->mp0c != 0)
        EAFree(pThis->mp0c);
    if (pThis->mp08 != 0)
        pThis->mp08->v1();
    if (pThis->mp04 != 0)
        pThis->mp04->v2();
    pThis->mpVtbl = (void*)0x013EB394;
    if ((nFlags & 1) != 0)
        EAFree(pThis);
    return pThis;
}

// @ 0x006764f0
void* __fastcall FUN_006764f0(SubjectA* pThis, int, int nFlags)
{
    pThis->mMaps.~FourHashMaps();
    if (pThis->mu24 != 0)
        EAFree((void*)pThis->mu24);
    if (pThis->mu0c != 0)
        EAFree((void*)pThis->mu0c);
    pThis->mpVtbl1 = (void*)0x013EF094;
    pThis->mpVtbl0 = (void*)0x013EB938;
    if ((nFlags & 1) != 0)
        EAFree(pThis);
    return pThis;
}

// @ 0x00676540
void __cdecl FUN_00676540(IPropWriter* pWriter, U32Vec* pVec)
{
    pVec->mpEnd = pVec->mpBegin;

    uint32_t nCount = 0;
    EA_IO_ReadInt32(pWriter->GetWriter()->GetStream(), &nCount, 1, 0);
    for (uint32_t i = 0; i < nCount; ++i) {
        uint32_t nValue = 0;
        EA_IO_ReadInt32(pWriter->GetWriter()->GetStream(), &nValue, 1, 0);
        pWriter->NextEntry();

        // eastl::lower_bound over the sorted list.
        uint32_t* pInsert = pVec->mpBegin;
        int       nLen    = (int)(pVec->mpEnd - pInsert);
        while (nLen > 0) {
            int nHalf = nLen >> 1;
            uint32_t* pMid = pInsert + nHalf;
            if (*pMid < nValue) {
                pInsert = pMid + 1;
                nLen -= nHalf + 1;
            } else {
                nLen = nHalf;
            }
        }
        if (pInsert == pVec->mpEnd) {
            if (pVec->mpEnd == pVec->mpCap) {
                pVec->DoInsertValue(pInsert, &nValue);
            } else {
                *pVec->mpEnd = nValue;
                ++pVec->mpEnd;
            }
        } else if (nValue < *pInsert) {
            pVec->DoInsertValue(pInsert, &nValue);
        }
    }
    pWriter->NextEntry();
}

// @ 0x00678f70
void __fastcall FUN_00678f70(char* p)
{
    unsigned short* b = *(unsigned short**)(p + 0xd8);
    if ((((char*)(*(char**)(p + 0xe0)) - (char*)b) & ~1) > 2 && b &&
        b != *(unsigned short**)(p + 0xe8))
        DeleteObj(b);
    if (*(void**)(p + 0xb8)) { void* x = *(void**)(p + 0xb8); ((FnV1)((VObj*)x)->vt[1])(x); }
    if (*(void**)(p + 0xb4)) { void* x = *(void**)(p + 0xb4); ((FnV1)((VObj*)x)->vt[1])(x); }
    if (*(void**)(p + 0xb0)) { void* x = *(void**)(p + 0xb0); ((FnV1)((VObj*)x)->vt[1])(x); }
    if (*(void**)(p + 0xac)) { void* x = *(void**)(p + 0xac); ((FnV1)((VObj*)x)->vt[1])(x); }
    FUN_008e2b20(p + 0x14);
}

// @ 0x006792f0
void __fastcall FUN_006792f0(char* p)
{
    char* elem = *(char**)(p + 8);
    int n = (int)elem + 0x134;
    if (n != *(int*)(p + 0x10)) {
        *(int*)(p + 8) = n;
        FUN_00678f70(elem);
        return;
    }
    FUN_00678f70(elem);
    if (*(int*)(p + 0xc)) DeleteObj(*(void**)(p + 0xc));
    int* q = (int*)(*(int*)(p + 0x14) + 4);
    *(int**)(p + 0x14) = q;
    int v = *q;
    *(int*)(p + 0xc) = v;
    *(int*)(p + 0x10) = v + 0x4d0;
    *(int*)(p + 8) = *(int*)(p + 0xc);
}

// @ 0x00679630
char Container::ModifyBool(Elem* elem)
{
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

// @ 0x00679b40
Elem* Elem::CopyFrom(Elem* other)
{
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

// @ 0x00679c90
Elem* Elem::AssignFrom(Elem* other)
{
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

// @ 0x00679e50
char Container::Process(Elem* elem)
{
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

// @ 0x0067a090
void Container::Shutdown()
{
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

// @ 0x0067a120
void __fastcall FUN_0067a120(char* p)
{
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

// @ 0x0067a1b0
char Container::Update(Elem* elem)
{
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

// @ 0x0067a590
void HM590::possibly(char a, char b)
{
    (void)a;
    void* cm = ConfigManager();
    if (((int (__thiscall*)(void*, int))VT(cm)[0x30 / 4])(cm, 0x4ea96cb) == 0)
        Start();
    if (b) {
        ((Sub1fc*)((char*)this + 0x1fc))->method(1);
        return;
    }
    if (sub.begin != sub.end) {
        Elem134 t(sub.begin);
        if (*(int*)((char*)&t + 0xac) != 0) {
            sub.Release();
            Add(&t);
        }
        while (sub.begin != sub.end) {
            if (Check(sub.begin))
                break;
            Elem134 t2(sub.begin);
            sub.Release();
            Add(&t2);
            t2.~Elem134();
        }
        t.~Elem134();
    }
}

// @ 0x0067a680
void __stdcall cb_67a680(void* unused, void* data)
{
    C_a590_fwd* r = (C_a590_fwd*)FUN_0067caf0();
    if (r)
        r->possibly((int)data, 1);
}

// @ 0x0067a6a0
bool C_a6a0::handle(int msg, void* data)
{
    (void)data;
    if (msg == 0x670eccd) {
        void* cm = ConfigManager();
        if (((int (__thiscall*)(void*, int))VT(cm)[0x30 / 4])(cm, 0x4ea96cb) == 0)
            ((C_a120_h*)((char*)this - 0xc))->f_67a120();
        return true;
    }
    return false;
}

// @ 0x0067a6e0
bool HM6e0::handle(HintWin* win, HMsg* msg)
{
    if (p_ec) {
        if (msg->type == 8) {
            Pt2 loc(msg->px, msg->py);
            loc = win->ToLocal(loc);
            void* hit = win->GetParent()->HitTest(&loc);
            char modal = ((WinMgr*)GetManager())->IsModal(p_ec);
            void* cur = p_ec;
            if (cur == win || modal) {
                if (cur != win)
                    return false;
                if (!modal || hit == cur)
                    return false;
                EndModal(cur, 0, 0);
            } else {
                if (hit != cur)
                    return false;
                BeginModal(cur, 0, 0);
            }
            HMsg out = *msg;
            out.px = loc.x;
            out.py = loc.y;
            ((WinMgr*)GetManager())->Send(0, 0, &out);
            return true;
        }
        if (msg->type == 6 || msg->type == 0x287259f6) {
            if (win == p_ec) {
                b199 = 1;
                ((C_a590_fwd*)((char*)this - 8))->possibly(0, 0);
                sub1f4.Cancel();
            }
        }
    }
    return false;
}

// @ 0x0067a850
void __cdecl cb_67a850(void* p)
{
    C_a590_fwd* o = (C_a590_fwd*)p;
    if (o)
        ((void (__thiscall*)(void*))VT(o)[1])(o);
    o->possibly(0, 0);
    if (o)
        ((void (__thiscall*)(void*))VT(o)[2])(o);
}
