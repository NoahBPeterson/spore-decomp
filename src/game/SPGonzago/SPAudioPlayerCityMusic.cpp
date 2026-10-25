// src/game/SPGonzago/SPAudioPlayerCityMusic.cpp -- migrated from slice(s) s00eb0ea0, s00eaefa0, s00ead1a0, s00eac530 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPAudioPlayerCityMusic.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Stopwatch.h"

// unnamed retail callees and globals (address in the comment)
extern int32_t g_1488414[];                      // 0x01488414  global property id table
#include <math.h>
#include "EA/Random/RandomLinearCongruential.h"
#pragma warning(disable : 4035)

// ---- items of slice s00eac530 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void v##n();
struct SysAT {
    PV(0) PV(1) PV(2) PV(3) PV(4)
    virtual void Slot14(uint32_t, void**, uint32_t);   // 0x14
    PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    virtual void Slot38(int);                    // 0x38
    virtual void Slot3c(int, float);             // 0x3c
    virtual void Slot40(int, int);               // 0x40
    PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual void Slot58();                       // 0x58
};
struct cPropertyList_s00ea_c530 {
    virtual int  AddRef();                       // +0x00
    virtual int  Release();                      // +0x04
virtual void f8();
virtual void fc();
virtual void f10();
virtual void f14();
virtual void f18();
virtual void f1c();
    virtual void f20();
    virtual bool Query(uint32_t id, void* out);  // +0x24
};
SysAT* GetSystemAT();                            // 0x00a206f0 (cdecl)
void   SetGlobalProperty(int, float);            // 0x005ca880 (cdecl)
void   PauseSound(void*, int);                   // 0x00a37290 (cdecl)
extern int32_t g_1488414[];                      // 0x01488414  global property id table
__forceinline int FloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}
struct Stopwatch160 {
    uint32_t m0;                                 // +0x00  (abs +0x160)
    uint32_t m4;                                 // +0x04  (abs +0x164)
    float    m8;                                 // +0x08  (abs +0x168)
    uint32_t mc;                                 // +0x0c  (abs +0x16c)
    float    m10;                                // +0x10  (abs +0x170)
    float    m14;                                // +0x14  tempo multiplier
    float    m18;                                // +0x18  (abs +0x178)
    float    m1c;                                // +0x1c  (abs +0x17c)
    float    m20;                                // +0x20  (abs +0x180)
    float    m24;                                // +0x24  (abs +0x184)
    float    m28;                                // +0x28  (abs +0x188)
    float    m2c;                                // +0x2c  (abs +0x18c, vector3 x)
    float    m30;                                // +0x30  (abs +0x190)
    float    m34;                                // +0x34  (abs +0x194)
    void     Start();                            // 0x00435480
    int64_t  GetElapsedTimeFloat();              // 0x0093a3a0
    void     SetBoolProperty();                  // 0x0093a2e0
};
struct cCreatureBase {
    char  pad000[0x1e0];
    float m1e0;                                  // +0x1e0
};
namespace SP {
namespace Audio {
struct cPlayerCityMusic {
    char         pad000[0x100];
    uint8_t      m100;                           // +0x100  paused flag
    uint8_t      m101;                           // +0x101
    char         pad102[0x108 - 0x102];
    void*        mp108;                          // +0x108  property scratch
    void*        mp10c;                          // +0x10c  sound handle
    char         pad110[0x118 - 0x110];
    uint32_t     m118;                           // +0x118  sound id
    cPropertyList_s00ea_c530* mp11c;                        // +0x11c  property list
    uint8_t      m120;                           // +0x120
    bool         m121;                           // +0x121
    char         pad122[0x123 - 0x122];
    uint8_t      m123;                           // +0x123
    char         pad124[0x127 - 0x124];
    uint8_t      m127;                           // +0x127
    char         pad128[0x12c - 0x128];
    float        m12c;                           // +0x12c
    float        m130;                           // +0x130
    float        m134;                           // +0x134
    float        m138;                           // +0x138
    float        m13c;                           // +0x13c
    int32_t      m140;                           // +0x140
    float        m144;                           // +0x144
    float        m148;                           // +0x148
    char         pad14c[0x150 - 0x14c];
    float        m150;                           // +0x150  accumulated duration
    float        m154;                           // +0x154
    char         pad158[0x160 - 0x158];
    Stopwatch160 m160;                           // +0x160
    float*       mp198;                          // +0x198  per-slot value array
    char         pad19c[0x1a4 - 0x19c];
    uint32_t     m1a4;                           // +0x1a4
    char         pad1a8[0x1c4 - 0x1a8];
    uint32_t     m1c4;                           // +0x1c4
    uint32_t     m1c8;                           // +0x1c8
    char         pad1cc[0x1e0 - 0x1cc];
    float*       mp1e0;                          // +0x1e0  note-duration array

    cCreatureBase* GetCreature();                // 0x006c0200
    void        CommitAllProperties();           // 0x00eab900

    void        FUN_00eac530();                  // 0x00eac530
    void        SetPosition(float*);             // 0x00eacd50
    bool        SelectRhythm(uint32_t);          // 0x00eacdb0
    bool        SelectInstrument(uint32_t);      // 0x00eace30
    void        PlayMelody(uint32_t);            // 0x00eaceb0
    void        PlayNote(uint32_t);              // 0x00eacf10
    void        FUN_00eacf70(uint8_t);           // 0x00eacf70
    void        Pause(uint8_t);                  // 0x00eacff0
    long double FUN_00ead040();                  // 0x00ead040
    void        FUN_00ead090(int, float);        // 0x00ead090
    void        SetNoteDuration(int, float);     // 0x00ead0c0
};  // namespace Audio
}  // namespace SP
}
struct Elem6c {
    virtual void V0();
    virtual void V1();
    virtual void Slot8(int);                     // +0x008
    char pad[0x6c - 0x04];
};
// ---- items of slice s00eac530 end

// ---- items of slice s00ead1a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_tab_1488420[3];     // 0x01488420
extern char PTR_01488444;          // 0x01488444 (vftable)
extern char PTR_0148843c;          // 0x0148843c
extern char PTR_0148842c;          // 0x0148842c
extern char PTR_013ec458;          // 0x013ec458
extern char PTR_013eb394;          // 0x013eb394
extern char PTR_013eb938;          // 0x013eb938
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
typedef unsigned char u8;
typedef unsigned int u32;
void* EAAllocate(unsigned int n, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void  __cdecl operator_delete_array(void* p);                                                 // 0x00f47380
void* GetSystemAT_s00ea_d1a0();                                            // 0x00a206f0
void* MessageServer();                                          // 0x0067dcc0
void  __cdecl RemoveHandler(void* h, void* a, void* b, void* c, void* d); // 0x00571db0
void  __cdecl FUN_00572020(void* a, void* b);                   // 0x00572020
void  __cdecl KillSetiEffects(void* a, void* b);                // 0x00435ed0
extern u32  g_tab_1488414[3];      // 0x01488414
typedef void  (__thiscall *vfn0)(void*);
typedef void  (__thiscall *vfn1)(void*, int);
typedef void  (__thiscall *vfn2)(void*, int, int);
typedef void  (__thiscall *vfnf)(void*, int, float);
typedef void* (__thiscall *vfnr)(void*);
#define VSLOT(o, off) (*(void**)((char*)(*(void**)(o)) + (off)))
struct cListNode {
    cListNode* mpNext_00;   // +0x00
    cListNode* mpPrev_04;   // +0x04
    int        mKey_08;     // +0x08
};
struct cList {
    cListNode mHead_00;
    void FUN_00eada10(const int* keyPtr);
    void FUN_00eadee0(int* begin, int* end, int dummy);
};
struct cMusicVec {
    void* mpBegin_00;   // +0x00
    void* mpEnd_04;     // +0x04
    void FUN_00ead660();
};
namespace SP {
namespace Audio {
struct cPlayerCityMusic_s00ea_d1a0 {
    void* mpVtbl_000;                    // +0x000
    void* mpVtbl_004;                    // +0x004
    void* mpVtbl_008;                    // +0x008
    u8    mPad_00c[0x40 - 0x0c];
    void* mp_040;                        // +0x040
    u8    mPad_044[0x54 - 0x44];
    void* mp_054;                        // +0x054
    u8    mPad_058[0x68 - 0x58];
    int   mn_068;                        // +0x068
    u8    mPad_06c[0x74 - 0x6c];
    int*  mp_074;                        // +0x074
    u8    mPad_078[0x94 - 0x78];
    int** mpp_094;                       // +0x094
    u8    mPad_098[0xd0 - 0x98];
    void* mp_0d0;                        // +0x0d0
    void* mp_0d4;                        // +0x0d4
    void* mp_0d8;                        // +0x0d8
    void* mp_0dc;                        // +0x0dc
    u8    mPad_0e0[0x101 - 0xe0];
    u8    mb_101;                        // +0x101
    u8    mPad_102[0x108 - 0x102];
    void* mp_108;                        // +0x108
    void* mp_10c;                        // +0x10c
    int   mn_110;                        // +0x110
    void* mp_114;                        // +0x114
    void* mp_118;                        // +0x118
    u8    mPad_11c[0x128 - 0x11c];
    int*  mp_128;                        // +0x128
    int*  mp_12c;                        // +0x12c
    u8    mPad_130[0x13c - 0x130];
    int*  mp_13c;                        // +0x13c
    u8    mPad_140[0x178 - 0x140];
    int*  mp_178;                        // +0x178
    u8    mPad_17c[0x180 - 0x17c];
    int*  mp_180;                        // +0x180
    u8    mPad_184[0x188 - 0x184];
    int*  mp_188;                        // +0x188
    u8    mPad_18c[0x190 - 0x18c];
    int*  mp_190;                        // +0x190
    u8    mPad_194[0x198 - 0x194];
    float* mp_198;                       // +0x198
    u8    mPad_19c[0x1b8 - 0x19c];
    cList mList_1b8;                     // +0x1b8
    u8    mPad_1c4[0x1c4 - 0x1c4];

    // The fields below live past 0x1c4; keep the layout explicit.
    void Reset(char param);  // 0x00ead1a0 (SP::Audio::cPlayerCityMusic::Reset)
    void Start(int arg);  // 0x00ead6f0 (SP::Audio::cPlayerCityMusic::Start)
    void Stop();  // 0x00ead7b0 (SP::Audio::cPlayerCityMusic::Stop)
    void SetNotePitch(int idx, int pitch);  // 0x00ead870 (SP::Audio::cPlayerCityMusic::SetNotePitch)
    void SelectAmbience(int state, u32* outIndex);  // 0x00eadd60 (SP::Audio::cPlayerCityMusic::SelectAmbience)
    ~cPlayerCityMusic_s00ea_d1a0();
};
}
}
namespace SP {
namespace Audio {
struct cPlayerCityMusicTail {
    u8    pad_000[0x1c4 - 0x000];
    int   mn_1c4;                        // +0x1c4
    int   mn_1c8;                        // +0x1c8
    int*  mp_1cc;                        // +0x1cc
    int*  mp_1d0;                        // +0x1d0
    u8    pad_1d4[0x1e0 - 0x1d4];
    float* mp_1e0;                       // +0x1e0
    u8    pad_1e4[0x1f4 - 0x1e4];
    void* mp_1f4;                        // +0x1f4
    void* mp_1f8;                        // +0x1f8
    void* mp_1fc;                        // +0x1fc
    void* mp_200;                        // +0x200
    void* mp_204;                        // +0x204
    void* mp_208;                        // +0x208
    void* mp_20c;                        // +0x20c
    void* mp_210;                        // +0x210
    int   mn_214;                        // +0x214
    int   mn_218;                        // +0x218
};
}
}
namespace SP {
namespace Audio {
#define SELF_TAIL ((cPlayerCityMusicTail*)this)
}
}
struct cEditorResource_s00ea_d1a0 {
    void* mpVtbl_00;
    u8    mPad_04[0x1c - 0x04];
    void* mp_1c;
    u8    mPad_20[0x30 - 0x20];
    void* mp_30;
    u8    mPad_34[0x44 - 0x34];
    void* mp_44;
    u8    mPad_48[0x58 - 0x48];
    void* mp_58;
    void FUN_00ead6a0();
};
struct cQuery840 {
    u8    mPad_00[0xd8];
    void* mp_d8;
    void* mp_dc;
    u8    mPad_e0[0xf0 - 0xe0];
    void* mp_f0;
    u8    mPad_f4[0xfc - 0xf4];
    void* mp_fc;
    bool FUN_00ead840();
};
// ---- items of slice s00ead1a0 end

// ---- items of slice s00eaefa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  FUN_00b93c60(int count, void *pAlloc);           // 0x00b93c60
extern "C" double RandomDoubleUniform(void *pRng);                           // 0x009360d0
extern "C" void *EA__Audio__GetSystemAT();                                   // 0x00a206f0
extern "C" void  FUN_00ea9440(void *pVec, const void *pVal);                 // 0x00ea9440
extern "C" void  FUN_00eae430(void *pVec, const void *pVal);                 // 0x00eae430
typedef unsigned short u16;
typedef int i32s;
long _InterlockedExchange(volatile long *p, long v);
struct Vec4f {
    void *mpBegin;   // +0x00
    void *mpEnd;     // +0x04
    void *mpCap;     // +0x08
    void *mpAlloc;   // +0x0c (fixed allocator payload: SP_STL_Sound)
    void *mpAlloc2;  // +0x10
    void Assign(const Vec4f &src);             // 0x00eae540 (declared, defined elsewhere)
};
#define Vec4fAssign(pT, pS) ((pT)->Assign(*(pS)))
struct ResMusic {
    void *mpVtbl;     // +0x00
    void *mpPad04;    // +0x04
    u32   mField08;   // +0x08
    u32   mField0c;   // +0x0c
    u32   mField10;   // +0x10
    u32   mField14;   // +0x14
    u32   mField18;   // +0x18
    Vec4f mVec1c;     // +0x1c
    Vec4f mVec30;     // +0x30
    Vec4f mVec44;     // +0x44
    Vec4f mVec58;     // +0x58

    // these are declared in-class so the compiler emits __thiscall codegen
    ResMusic(const ResMusic &src);   // 0x00eaf190
    ResMusic *ScalarDeletingDtor(u8 flags);   // 0x00eaf2b0
};
extern "C" void *memcpy(void *d, const void *s, u32 n);           // 0x011e0744
extern "C" void *operator_new(u32 n, const char *pTag, int a, int b); // 0x00f473a0
extern "C" void *memmove(void *d, const void *s, u32 n);           // via [0x13cc480]
extern "C" u32   RandomUint32Uniform(void *pRng, u32 range);                 // 0x00a68fb0
extern "C" u32   RandomUint32WeightedChoice(void *pRng, u32 a, u32 b);       // 0x005e8ec0
extern "C" void  EA__ConvertToString16(void *pOut, const u16 *pStr, int a);  // 0x0093c5a0
extern "C" void  eastl__wstring__range_initialize(void *pThis, u32 a, u32 b);// 0x00579a90
struct WStringStub { void AssignFrom(const void *pSrc); };  // 0x0056e2d0
#define eastl_wstring_ctor(pDst, pSrc) ((WStringStub *)(pDst))->AssignFrom(pSrc)
extern "C" char  SP__TypedValueToStringT_short__Write(void *pThis, void *pOut, int a, const u16 *pName); // 0x00675990
static inline void CopyVecRaw(Vec4f *pDst, const Vec4f *pSrc)
{
    pDst->mpBegin = pSrc->mpBegin;
    pDst->mpEnd   = pSrc->mpEnd;
    pDst->mpCap   = pSrc->mpCap;
}
static void CopyVec(Vec4f *pDst, const Vec4f *pSrc)
{
    int n = (int)((char *)pSrc->mpEnd - (char *)pSrc->mpBegin) >> 2;
    FUN_00b93c60(n, (char *)pSrc + 0xc);
    u32 bytes = (u32)((char *)pSrc->mpEnd - (char *)pSrc->mpBegin);
    char *p = (char *)memcpy(pDst->mpBegin, pSrc->mpBegin, bytes);
    pDst->mpEnd = p + bytes;
}
struct ListNode {
    ListNode *mpNext;   // +0x00
    u32       mPad04;   // +0x04
    u32       mValue;   // +0x08
};
struct VecP {
    void *mpBegin;   // +0x00
    void *mpEnd;     // +0x04
    void *mpCap;     // +0x08
    u32   Count() const { return (u32)((char *)mpEnd - (char *)mpBegin) >> 2; }
    u32   Capacity() const { return (u32)((char *)mpCap - (char *)mpBegin) >> 2; }
    void InsertRange(void *pos, ListNode *first, ListNode *last);  // 0x00eaefa0
};
struct VecU {                     // 12-byte u32/float vector (begin/end/cap)
    float *mpBegin;               // +0x00
    float *mpEnd;                 // +0x04
    float *mpCap;                 // +0x08
};
struct PlayerMusic {
    u8     mPad00[0x2c];
    float  mTempo;                // +0x2c
    u8     mPad30[0x38];
    i32s   mTranspose;            // +0x68
    u8     mPad6c[0x08];
    u32   *mpVolTable;            // +0x74
    u8     mPad78[0x8c];
    u8     mRng[1];               // +0x104 (random generator state)
    u8     mPad105[0x24];
    VecU   mVec128;               // +0x128
    VecU   mVec13c;               // +0x13c
    float  mLastTime;             // +0x150
    u32    mNoteIndex;            // +0x154
    u8     mPad158[0x74];
    VecU   mVec1cc;               // +0x1cc
    VecU   mVec1e0;               // +0x1e0

    void AddNote(u32 *pOut);           // 0x00eaf510
    void MoveNote(u32 noteIndex, u32 numMoved);  // 0x00eaf8d0
};
struct PtrVec {
    void *mpBegin;
    void *mpEnd;
    void *mpCap;
};
// ---- items of slice s00eaefa0 end

// ---- items of slice s00eb0ea0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint16_t gEmptyString16[];                               // 0x01667bac
#pragma intrinsic(_InterlockedExchange)
#define nullptr 0
float GetCyclesToUnitsCoefficient(int32_t nUnits);              // 0x0093a420
void FUN_00eaed40(float* pBuffer, int32_t nCount, const float* pValue);  // 0x00eaed40
class cMessageServer {
public:
virtual void m00();
virtual void m04();
virtual void m08();
virtual void m0c();
virtual void m10();
virtual void m14();
    virtual bool Send(uint32_t nId, int32_t nA, int32_t nB, int32_t nC);   // 0x018
virtual void m1c();
virtual void m20();
    virtual bool Register(uint32_t nId, void* pHandler);                   // 0x024
};
cMessageServer* MessageServer_s00eb_0ea0();                                // 0x0067dcc0
class cEapdMessage {
public:
    uint32_t GetType();                                         // 0x00fcc210
    bool GetNextFloat(float* pValue);                           // 0x00a34e30
    void MarkProcessed();                                       // 0x00a34e80

    uint8_t  mPad004[0x04];                                     // 0x004
    uint32_t mnField08;                                         // 0x008
    uint32_t mnField0C;                                         // 0x00c
    uint32_t mnField10;                                         // 0x010
    uint8_t  mPad014[0x04];                                     // 0x014
    uint32_t mnField18;                                         // 0x018
};
class cPropertyList {
public:
    __forceinline cPropertyList()
    {
        _InterlockedExchange(&mnRefCount, 0);
        mnField08 = 0;
        mnField0C = 0;
        mnField10 = 0;
    }
virtual void p00();
virtual void p04();
virtual void p08();
    virtual void* GetProperty(uint32_t nKey);                   // 0x00c
    virtual void* GetPropertyValue(uint32_t nKey, void** ppValue);  // 0x024

    volatile long mnRefCount;                                   // 0x004
    uint32_t mnField08;                                         // 0x008
    uint32_t mnField0C;                                         // 0x00c
    uint32_t mnField10;                                         // 0x010
};
class cAutoRefCount {
public:
    void Assign(void* pValue)
    {
        void* pOld = mpObject;
        if (pValue != pOld) {
            if (pValue != nullptr)
                ((cPropertyList*)pValue)->p00();
            mpObject = pValue;
            if (pOld != nullptr)
                ((cPropertyList*)pOld)->p04();
        }
    }

    void* mpObject;                                             // 0x000
};
class cResourceCityMusic : public cPropertyList {
public:
    cResourceCityMusic();

    uint32_t mnField14;                                         // 0x014
    uint32_t mnField18;                                         // 0x018
    uint32_t* mpData1CBegin;                                    // 0x01c
    uint32_t* mpData1CEnd;                                      // 0x020
    uint32_t* mpData1CCap;                                      // 0x024
    uint8_t  mPad028[0x08];                                     // 0x028
    uint32_t* mpData30Begin;                                    // 0x030
    uint32_t* mpData30End;                                      // 0x034
    uint32_t* mpData30Cap;                                      // 0x038
    uint8_t  mPad03C[0x08];                                     // 0x03c
    uint32_t* mpData44Begin;                                    // 0x044
    uint32_t* mpData44End;                                      // 0x048
    uint32_t* mpData44Cap;                                      // 0x04c
    uint8_t  mPad050[0x08];                                     // 0x050
    uint32_t* mpData58Begin;                                    // 0x058
    uint32_t* mpData58End;                                      // 0x05c
    uint32_t* mpData58Cap;                                      // 0x060
    uint8_t  mPad064[0x08];                                     // 0x064
};
class cMusicRing;
struct cRingIter {
    cMusicRing* mpRing;                                         // 0x00
    cResourceCityMusic* mpState;                                // 0x04
};
class cMusicRing {
public:
    cMusicRing* resize(int32_t nCount);                         // 0x00eb0d60
    cMusicRing* reserve(int32_t nCount);                        // 0x00eb0df0
    cRingIter erase(cRingIter aFirst, cRingIter aLast);         // 0x00eb0cb0

    int32_t GetCount()
    {
        return (int32_t)((uint8_t*)mpEnd - (uint8_t*)mpBegin) / 0x6c;
    }

    cResourceCityMusic* mpBegin;                                // 0x00
    cResourceCityMusic* mpEnd;                                  // 0x04
    void*    mpField08;                                         // 0x08
    uint8_t  mPad00C[0x08];                                     // 0x0c
    cResourceCityMusic* mpHead;                                 // 0x14
    cResourceCityMusic* mpTail;                                 // 0x18
    uint32_t mnWrap;                                            // 0x1c
};
class cPlayerCityMusicConfig {
public:
    cPlayerCityMusicConfig();
    bool Reload(uint32_t nKeyA, uint32_t nKeyB, uint32_t nKeyC); // 0x00eb14c0

    uint32_t mNumAmbiences;                                     // 0x000
    uint32_t mNumRhythms;                                       // 0x004
    uint32_t mNumInstruments;                                   // 0x008
    uint32_t mMaxAmbienceLayers;                                // 0x00c
    uint32_t mMinNotes;                                         // 0x010
    uint32_t mMaxNotes;                                         // 0x014
    float*   mpNumNoteDistribution;                             // 0x018
    float    mfBeatIncrement;                                   // 0x01c
    float    mfMaxBeats;                                        // 0x020
    uint32_t mMouseWheelIncrement;                              // 0x024
    uint32_t* mpBeatDistSizesBegin;                             // 0x028
    uint32_t* mpBeatDistSizesEnd;                               // 0x02c
    uint32_t* mpBeatDistributionsBegin;                         // 0x030
    uint32_t* mpBeatDistributionsEnd;                           // 0x034
    uint32_t* mpBeatDistributionsCap;                           // 0x038
    uint8_t  mPad03C[0x1c];                                     // 0x03c
    uint32_t mDegreeTransitions[4];                             // 0x058
    float*   mpDegreeNotes[7];                                  // 0x068
    uint32_t* mpDegreeSuggestions[7];                           // 0x084
    uint32_t mMouseWheelUndoTimeMs;                             // 0x0a0
    uint32_t mIcons[3];                                         // 0x0a4
    void*    mpConfig;                                          // 0x0b0
    void*    mpBeatConfig;                                      // 0x0b4
    uint8_t  mPad0B8[0x08];                                     // 0x0b8
    cAutoRefCount mTribeSource;                                 // 0x0c0
    cAutoRefCount mBeatSource;                                  // 0x0c4
};
class cRandom {
public:
    void SetSeed(uint32_t nSeed);                               // 0x00936090
};
class cStopwatch {
public:
    void Init(int32_t nCycles, bool bStart);                    // 0x0093a560
    void Restart();                                             // 0x00571e80

    uint8_t mPad00[0x0c];                                       // 0x00
};
class cPlayerCityMusic_s00eb_0ea0 {
public:
    cPlayerCityMusic_s00eb_0ea0();
    virtual void v00();

    void SaveData(cResourceCityMusic* pState);                  // 0x00eb0390
    void ResetUndoBuffer();                                     // 0x00eb10d0
    void AddUndoState();                                        // 0x00eb1170
    bool HandleMessage(int32_t nType, cEapdMessage* pMessage);  // 0x00eb12a0
    void FUN_00eb0460();                                        // 0x00eb0460
    void Reset(bool bFull);                                     // 0x00ead1a0

    uint8_t  mPad004[0x0c];                                     // 0x004 (IHandler part)
    cPlayerCityMusicConfig mConfig;                             // 0x010
    cMusicRing mUndoBuffer;                                     // 0x0d8
    cMusicRing* mpUndo;                                         // 0x0f8
    cResourceCityMusic* mpUndoBegin;                            // 0x0fc
    uint8_t  mbPaused;                                          // 0x100
    uint8_t  mbQuiet;                                           // 0x101
    uint8_t  mPad102[0x02];                                     // 0x102
    cRandom  mRandom;                                           // 0x104
    uint32_t mnMagic;                                           // 0x108
    void*    mpArray10CBegin;                                   // 0x10c
    void*    mpArray10CEnd;                                     // 0x110
    void*    mpArray10CCap;                                     // 0x114
    void*    mpArray118Begin;                                   // 0x118
    void*    mpArray118End;                                     // 0x11c
    uint8_t  mPad120[0x08];                                     // 0x120
    void*    mpArray128Begin;                                   // 0x128
    void*    mpArray128End;                                     // 0x12c
    void*    mpArray128Cap;                                     // 0x130
    uint8_t  mPad134[0x08];                                     // 0x134
    void*    mpArray13CBegin;                                   // 0x13c
    void*    mpArray13CEnd;                                     // 0x140
    void*    mpArray13CCap;                                     // 0x144
    uint8_t  mPad148[0x08];                                     // 0x148
    float    mfField150;                                        // 0x150
    int32_t  mnField154;                                        // 0x154
    int32_t  mnField158;                                        // 0x158
    int32_t  mnField15C;                                        // 0x15c
    cStopwatch mStopwatch;                                      // 0x160
    float    mfField170;                                        // 0x170
    float    mfField174;                                        // 0x174
    uint16_t* mpVolumesBegin;                                   // 0x178
    uint16_t* mpVolumesEnd;                                     // 0x17c
    uint16_t* mpVolumesCap;                                     // 0x180
    uint8_t  mPad184[0x04];                                     // 0x184
    uint16_t* mpVolumesBufA;                                    // 0x188
    uint16_t* mpVolumesBufB;                                    // 0x18c
    uint16_t* mpVolumesBufC;                                    // 0x190
    uint8_t  mPad194[0x04];                                     // 0x194
    float*   mpNotePitchesBegin;                                // 0x198
    float*   mpNotePitchesEnd;                                  // 0x19c
    float*   mpNotePitchesCap;                                  // 0x1a0
    uint8_t  mPad1A4[0x08];                                     // 0x1a4
    float    mfNotePitchesBuffer[3];                            // 0x1ac
    void*    mpList1B8Next;                                     // 0x1b8
    void*    mpList1B8Prev;                                     // 0x1bc
    void*    mpList1C4;                                         // 0x1c4
    void*    mpList1C8;                                         // 0x1c8
    void*    mpList1CC;                                         // 0x1cc
    void*    mpList1D0;                                         // 0x1d0
    void*    mpList1D4;                                         // 0x1d4
    uint8_t  mPad1D8[0x08];                                     // 0x1d8
    void*    mpList1E0;                                         // 0x1e0
    void*    mpList1E4;                                         // 0x1e4
    void*    mpList1E8;                                         // 0x1e8
    uint8_t  mPad1EC[0x08];                                     // 0x1ec
    cMessageServer* mpMessageServer;                            // 0x1f4
    void*    mpHandler;                                         // 0x1f8
    uint32_t mnHandlerId;                                       // 0x1fc
    int32_t  mnHandlerKind;                                     // 0x200
    void*    mpHandlerData;                                     // 0x204
    uint8_t  mPad208[0x14];                                     // 0x208
};
// ---- items of slice s00eb0ea0 end

// @ 0x00eacd50
void SP::Audio::cPlayerCityMusic::SetPosition(float* p)
{
    if (mp10c != 0) {
        SetGlobalProperty(0x40ef6b1b, p[0]);
        SetGlobalProperty(0x40ef6b1a, p[1]);
        SetGlobalProperty(0x40ef6b19, p[2]);
    }
}

// @ 0x00eacdb0
bool SP::Audio::cPlayerCityMusic::SelectRhythm(uint32_t v)
{
    if (m1c4 != 0)
        SetGlobalProperty(0x7df75892, (float)m1c4);

    bool changed = (m1c4 != v);
    m1c4 = changed ? v : 0;
    if (m1c4 != 0)
        SetGlobalProperty(0xec66947a, (float)m1c4);
    return changed;
}

// @ 0x00eace30
bool SP::Audio::cPlayerCityMusic::SelectInstrument(uint32_t v)
{
    bool changed = (m1c8 != v);
    if (!changed)
        SetGlobalProperty(0xcbc8ae11, (float)m1c8);

    m1c8 = changed ? v : 0;
    if (m1c8 != 0)
        SetGlobalProperty(0xf7db2353, (float)m1c8);
    return changed;
}

// @ 0x00eaceb0
void SP::Audio::cPlayerCityMusic::PlayMelody(uint32_t a)
{
    SysAT* s = GetSystemAT();
    if (s != 0) {
        s->Slot38(0x3cdd1a9);
        s->Slot40(0x34753a7, 0x4b64ae20);
        s->Slot3c(0x34753aa, (float)a);
        s->Slot58();
    }
}

// @ 0x00eacf10
void SP::Audio::cPlayerCityMusic::PlayNote(uint32_t a)
{
    SysAT* s = GetSystemAT();
    if (s != 0) {
        s->Slot38(0x3cdd1a9);
        s->Slot40(0x34753a7, 0x4405c487);
        s->Slot3c(0x34753aa, (float)a);
        s->Slot58();
    }
}

// @ 0x00eacf70
void SP::Audio::cPlayerCityMusic::FUN_00eacf70(uint8_t v)
{
    if (m101 != v)
        SetGlobalProperty(0x6c3a5e1c, (float)v);
    m101 = v;
}

// @ 0x00eacfb0
Elem6c* FUN_00eacfb0(Elem6c* a, Elem6c* b, Elem6c* c)
{
    while (a != b) {
        a->Slot8(0);
        a += 1;
        c += 1;
    }
    return c;
}

// @ 0x00eacff0
void SP::Audio::cPlayerCityMusic::Pause(uint8_t p)
{
    if (mp10c != 0 && p != m100) {
        PauseSound(mp10c, p);
        m100 = p;
        if (p != 0)
            m160.SetBoolProperty();
        else
            m160.Start();
    }
}

// @ 0x00ead040
long double SP::Audio::cPlayerCityMusic::FUN_00ead040()
{
    Stopwatch160* sw = &m160;
    int64_t t = sw->GetElapsedTimeFloat();
    long double e = (long double)t;
    e = e * sw->m14;
    float f = (float)e;
    int i = FloorToInt(f);
    return e - (long double)i;
}

// @ 0x00ead090
void SP::Audio::cPlayerCityMusic::FUN_00ead090(int idx, float v)
{
    mp198[idx] = v;
    SetGlobalProperty(g_1488414[idx], v);
}

// @ 0x00ead0c0
void SP::Audio::cPlayerCityMusic::SetNoteDuration(int idx, float v)
{
    float* slot = mp1e0 + idx;
    m150 = m150 + (v - *slot);
    *slot = v;

    SysAT* s = GetSystemAT();
    if (s != 0) {
        s->Slot38(0x3cdd1a9);
        s->Slot40(0x34753a7, 0xe7b72656);
        s->Slot3c(0x34753aa, (float)(uint32_t)idx);
        s->Slot58();
    }

    s = GetSystemAT();
    if (s != 0) {
        s->Slot38(0x3cdd1a9);
        s->Slot40(0x34753a7, 0xc309bcc9);
        s->Slot3c(0x34753aa, v);
        s->Slot58();
    }
}

// @ 0x00ead1a0
namespace SP { namespace Audio {
void cPlayerCityMusic_s00ea_d1a0::Reset(char param)
{
    cPlayerCityMusicTail* t = SELF_TAIL;
    if (mp_10c == 0) return;
    void* sys;
    int prop;
    if (param != 0) {
        u32 cnt = (u32)((char*)mp_118 - (char*)mp_114) >> 2;
        if ((int)cnt != 0) {
            for (unsigned i = 0; i < (unsigned)((char*)mp_118 - (char*)mp_114) >> 2; ++i) {
                int v = *(int*)((char*)mp_114 + i * 4);
                if (v != 0) {
                    SetGlobalProperty(0x330df985, (float)(unsigned)v);
                    SetGlobalProperty(0x3fbc0a67, (float)(unsigned)(i + 1));
                }
            }
        }
        if (t->mn_1c4 != 0)
            SetGlobalProperty(0xec66947a, (float)(unsigned)t->mn_1c4);
        if (t->mn_1c8 != 0)
            SetGlobalProperty(0xf7db2353, (float)(unsigned)t->mn_1c8);
        for (unsigned b = 0; b < 0xc; b += 4) {
            float f = *(float*)((char*)mp_198 + b);
            u32 p = *(u32*)((char*)g_tab_1488414 + b);
            sys = GetSystemAT_s00ea_d1a0();
            if (sys) {
                (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
                (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, (int)p);
                (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa, f);
                (*(vfn0)VSLOT(sys, 0x58))(sys);
            }
        }
        u32 n2 = (u32)((char*)t->mp_1d0 - (char*)t->mp_1cc) >> 2;
        if (n2 != 0) {
            for (unsigned i = 0; i < n2; ++i) {
                sys = GetSystemAT_s00ea_d1a0();
                if (sys) {
                    (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
                    (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, (int)0xe7b72656);
                    (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa, (float)(unsigned)i);
                    (*(vfn0)VSLOT(sys, 0x58))(sys);
                }
                int v = *(int*)((char*)t->mp_1cc + i * 4);
                sys = GetSystemAT_s00ea_d1a0();
                if (sys) {
                    (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
                    (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, (int)0xfe31e5d9);
                    (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa, (float)(unsigned)v);
                    (*(vfn0)VSLOT(sys, 0x58))(sys);
                }
                float f = *(float*)((char*)t->mp_1e0 + i * 4);
                sys = GetSystemAT_s00ea_d1a0();
                if (sys) {
                    (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
                    (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, (int)0xc309bcc9);
                    (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa, f);
                    (*(vfn0)VSLOT(sys, 0x58))(sys);
                }
            }
        }
        sys = GetSystemAT_s00ea_d1a0();
        if (sys) {
            (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
            (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, (int)0xead8248);
            (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa,
                                      (float)(unsigned)((u32)((char*)t->mp_1d0 - (char*)t->mp_1cc) >> 2));
            (*(vfn0)VSLOT(sys, 0x58))(sys);
        }
        if (mb_101 == 0) return;
        sys = GetSystemAT_s00ea_d1a0();
        if (sys) {
            (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
            (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, (int)0x6c3a5e1c);
            (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa, 1.0f);
            (*(vfn0)VSLOT(sys, 0x58))(sys);
        }
        sys = GetSystemAT_s00ea_d1a0();
        if (sys == 0) return;
        (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
        prop = 0x4b64ae20;
    } else {
        u32 cnt = (u32)((char*)mp_118 - (char*)mp_114) >> 2;
        if ((int)cnt != 0) {
            for (unsigned i = 0; i < cnt; ++i) {
                if (*(int*)((char*)mp_114 + i * 4) != 0)
                    SetGlobalProperty(0xaa1b3b8d, (float)(unsigned)(i + 1));
            }
        }
        if (t->mn_1c4 != 0)
            SetGlobalProperty(0x7df75892, (float)(unsigned)t->mn_1c4);
        if (t->mn_1c8 != 0)
            SetGlobalProperty(0xcbc8ae11, (float)(unsigned)t->mn_1c8);
        sys = GetSystemAT_s00ea_d1a0();
        if (sys) {
            (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
            (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, (int)0xead8248);
            (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa, 0.0f);
            (*(vfn0)VSLOT(sys, 0x58))(sys);
        }
        sys = GetSystemAT_s00ea_d1a0();
        if (sys == 0) return;
        (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
        prop = 0x6c3a5e1c;
    }
    (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, prop);
    (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa, 0.0f);
    (*(vfn0)VSLOT(sys, 0x58))(sys);
}
}}  // namespace SP::Audio

// @ 0x00ead660
void cMusicVec::FUN_00ead660()
{
    char* p = (char*)mpBegin_00;
    char* end = (char*)mpEnd_04;
    while (p < end) {
        (*(vfn1)VSLOT(p, 8))(p, 0);
        p += 0x6c;
    }
    if (mpBegin_00)
        operator_delete_array(mpBegin_00);
}

// @ 0x00ead6a0
void cEditorResource_s00ea_d1a0::FUN_00ead6a0()
{
    if (mp_58)
        operator_delete_array(mp_58);
    if (mp_44)
        operator_delete_array(mp_44);
    if (mp_30)
        operator_delete_array(mp_30);
    if (mp_1c)
        operator_delete_array(mp_1c);
    mpVtbl_00 = (void*)&PTR_013eb938;
}

// @ 0x00ead6f0
namespace SP { namespace Audio {
void cPlayerCityMusic_s00ea_d1a0::Start(int arg)
{
    cPlayerCityMusicTail* t = SELF_TAIL;
    if (mp_10c != 0) return;
    void* sys = GetSystemAT_s00ea_d1a0();
    void* p = sys ? (*(vfnr)VSLOT(sys, 0x20))(sys) : 0;
    mp_10c = p;
    if (p == 0) return;
    char* base = (char*)this + 4;
    void* h = MessageServer();
    t->mp_208 = h;
    t->mp_20c = base;
    t->mp_210 = (void*)g_tab_1488420;
    t->mn_214 = 3;
    t->mn_218 = 0;
    if (h != 0 && base != 0) {
        for (unsigned i = 0; i < 0xc; i += 4)
            (*(vfn2)VSLOT(h, 0x24))(h, (int)base, *(int*)((char*)g_tab_1488420 + i));
    }
    KillSetiEffects(mp_108, mp_10c);
    (*(vfn1)VSLOT(this, 0x30))(this, arg);
    Reset(1);
}
}}  // namespace SP::Audio

// @ 0x00ead7b0
namespace SP { namespace Audio {
void cPlayerCityMusic_s00ea_d1a0::Stop()
{
    cPlayerCityMusicTail* t = SELF_TAIL;
    if (mp_10c == 0) return;
    Reset(0);
    FUN_00572020(mp_10c, 0);
    mp_10c = 0;
    if (t->mp_208 != 0) {
        void* h = t->mp_208;
        t->mp_208 = 0;
        RemoveHandler(h, t->mp_20c, t->mp_210, (void*)t->mn_214, (void*)t->mn_218);
    }
}
}}  // namespace SP::Audio

// @ 0x00ead840
bool cQuery840::FUN_00ead840()
{
    void* v = mp_f0;
    if (v == mp_d8)
        v = mp_dc;
    return mp_fc != (void*)((char*)v - 0x6c);
}

// @ 0x00ead870
namespace SP { namespace Audio {
void cPlayerCityMusic_s00ea_d1a0::SetNotePitch(int idx, int pitch)
{
    cPlayerCityMusicTail* t = SELF_TAIL;
    t->mp_1cc[idx] = pitch;
    unsigned rem = ((unsigned)t->mp_1cc[idx] - (unsigned)mn_068) % 12;
    int found = -1;
    int* tab = mp_074;
    for (int i = 0; i < 7; ++i, ++tab) {
        if (*tab == (int)rem) { found = i; break; }
    }
    mp_13c[idx] = found;
    int val;
    if (mp_13c[idx] == -1) {
        val = 2;
    } else if (idx == 0) {
        val = 0;
    } else {
        int* oct = mp_13c;
        int* arr = (int*)mpp_094[oct[idx - 1]];
        val = (arr[oct[idx]] == 0);
    }
    mp_128[idx] = val;
    int i2 = idx + 1;
    if (i2 < (int)((char*)mp_12c - (char*)mp_128) >> 2) {
        int v2;
        if (mp_13c[i2] == -1) {
            v2 = 2;
        } else if (i2 == 0) {
            v2 = 0;
        } else {
            int* oct = mp_13c;
            int* arr = (int*)mpp_094[oct[i2 - 1]];
            v2 = (arr[oct[i2]] == 0);
        }
        mp_128[i2] = v2;
    }
    void* sys = GetSystemAT_s00ea_d1a0();
    if (sys) {
        (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
        (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, (int)0xe7b72656);
        (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa, (float)(unsigned)idx);
        (*(vfn0)VSLOT(sys, 0x58))(sys);
    }
    sys = GetSystemAT_s00ea_d1a0();
    if (sys) {
        (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
        (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, (int)0xfe31e5d9);
        (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa, (float)(unsigned)pitch);
        (*(vfn0)VSLOT(sys, 0x58))(sys);
    }
}
}}  // namespace SP::Audio

// @ 0x00eada10
void cList::FUN_00eada10(const int* keyPtr)
{
    cListNode* head = &mHead_00;
    cListNode* n = mHead_00.mpNext_00;
    if (n == head) return;
    for (;;) {
        int key = n->mKey_08;
        n = n->mpNext_00;
        if (key == *keyPtr) {
            cListNode* x = n->mpPrev_04;
            x->mpPrev_04->mpNext_00 = x->mpNext_00;
            x->mpNext_00->mpPrev_04 = x->mpPrev_04;
            operator_delete_array(x);
        }
        if (n == head) break;
    }
}

// @ 0x00eada50
void __stdcall FUN_00eada50(cListNode* sentinel, int* begin, int* end, int dummy)
{
    for (; begin != end; ++begin) {
        cListNode* n = (cListNode*)EAAllocate(0xc, "Simulator", 0, 0, "allocator.h", 0xd1);
        if (&n->mKey_08)
            n->mKey_08 = *begin;
        n->mpNext_00 = sentinel;
        n->mpPrev_04 = sentinel->mpPrev_04;
        sentinel->mpPrev_04->mpNext_00 = n;
        sentinel->mpPrev_04 = n;
    }
}

// @ 0x00eadab0
void __stdcall FUN_00eadab0(cListNode* sentinel, unsigned count, const int* valuePtr)
{
    if (count == 0) return;
    for (; count > 0; --count) {
        cListNode* n = (cListNode*)EAAllocate(0xc, "Simulator", 0, 0, "allocator.h", 0xd1);
        if (&n->mKey_08)
            n->mKey_08 = *valuePtr;
        n->mpNext_00 = sentinel;
        n->mpPrev_04 = sentinel->mpPrev_04;
        sentinel->mpPrev_04->mpNext_00 = n;
        sentinel->mpPrev_04 = n;
    }
}

// @ 0x00eadb10
void __cdecl FUN_00eadb10(void** p, int n)
{
    for (; n != 0; --n)
        *p = *(void**)*p;
}

// @ 0x00eadb30
namespace SP { namespace Audio {
cPlayerCityMusic_s00ea_d1a0::~cPlayerCityMusic_s00ea_d1a0()
{
    cPlayerCityMusicTail* t = SELF_TAIL;
    mpVtbl_000 = (void*)&PTR_01488444;
    mpVtbl_004 = (void*)&PTR_0148843c;
    mpVtbl_008 = (void*)&PTR_0148842c;
    _ReadWriteBarrier();
    if (t->mp_208 != 0) {
        void* h = t->mp_208;
        t->mp_208 = 0;
        RemoveHandler(h, t->mp_20c, t->mp_210, (void*)t->mn_214, (void*)t->mn_218);
    }
    if (t->mp_1f4 != 0) {
        void* hh = t->mp_1f4;
        t->mp_1f4 = 0;
        RemoveHandler(hh, t->mp_1f8, t->mp_1fc, t->mp_200, t->mp_204);
    }
    if (t->mp_1e0)
        operator_delete_array(t->mp_1e0);
    if (t->mp_1cc)
        operator_delete_array(t->mp_1cc);
    {
        cListNode* head = &mList_1b8.mHead_00;
        cListNode* n = mList_1b8.mHead_00.mpNext_00;
        while (n != head) {
            cListNode* cur = n;
            n = n->mpNext_00;
            operator_delete_array(cur);
        }
    }
    {
        int* b = mp_188;
        unsigned nn = (unsigned)((char*)mp_190 - (char*)b) & 0xfffffffeu;
        if ((int)nn > 2 && b)
            operator_delete_array(b);
    }
    {
        int* b = mp_178;
        unsigned nn = (unsigned)((char*)mp_180 - (char*)b) & 0xfffffffeu;
        if ((int)nn > 2 && b)
            operator_delete_array(b);
    }
    if (mp_13c)
        operator_delete_array(mp_13c);
    if (mp_128)
        operator_delete_array(mp_128);
    if (mp_114)
        operator_delete_array(mp_114);
    {
        char* end = (char*)mp_0dc;
        char* p = (char*)mp_0d8;
        while (p < end) {
            (*(vfn1)VSLOT(p, 8))(p, 0);
            p += 0x6c;
        }
        if (mp_0d8)
            operator_delete_array(mp_0d8);
    }
    if (mp_0d4)
        (*(vfn0)VSLOT(mp_0d4, 4))(mp_0d4);
    if (mp_0d0)
        (*(vfn0)VSLOT(mp_0d0, 4))(mp_0d0);
    if (mp_054)
        operator_delete_array(mp_054);
    if (mp_040)
        operator_delete_array(mp_040);
    mpVtbl_008 = (void*)&PTR_013ec458;
    mpVtbl_004 = (void*)&PTR_013eb394;
    mpVtbl_000 = (void*)&PTR_013eb938;
}
}}  // namespace SP::Audio

// @ 0x00eadd60
namespace SP { namespace Audio {
void cPlayerCityMusic_s00ea_d1a0::SelectAmbience(int state, u32* outIndex)
{
    cPlayerCityMusicTail* t = SELF_TAIL;
    (void)t;
    *outIndex = 0;
    if ((int)((char*)mp_118 - (char*)mp_114) >> 2 != 0) {
        for (;;) {
            u32 i = *outIndex;
            if (state == *(int*)((char*)mp_114 + i * 4)) {
                *(int*)((char*)mp_114 + (i * 4)) = 0;
                float f = (float)(unsigned)(*outIndex + 1);
                void* sys = GetSystemAT_s00ea_d1a0();
                if (sys) {
                    (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
                    (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, (int)0xaa1b3b8d);
                    (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa, f);
                    (*(vfn0)VSLOT(sys, 0x58))(sys);
                }
                --mn_110;
                break;
            }
            *outIndex = i + 1;
            if ((u32)((char*)mp_118 - (char*)mp_114) >> 2 <= *outIndex) {
                mList_1b8.FUN_00eada10(&state);
                return;
            }
        }
    }
    mList_1b8.FUN_00eada10(&state);
}
}}  // namespace SP::Audio

// @ 0x00eae010
int* __cdecl FUN_00eae010(void* first, void* last, int* out)
{
    while (first != last) {
        *out++ = ((int*)first)[2];
        first = *(void**)first;
    }
    return out;
}

// @ 0x00eae040
int* __cdecl FUN_00eae040(void* first, void* last, int* out)
{
    while (last != first) {
        last = *(void**)((char*)last + 4);
        *--out = ((int*)last)[2];
    }
    return out;
}

// @ 0x00eaefa0
void VecP::InsertRange(void *pos, ListNode *first, ListNode *last)
{
    if (first == last)
        return;

    u32 n = 0;
    for (ListNode *it = first; it != last; it = it->mpNext)
        ++n;

    u32 cap = Capacity();
    if (n <= cap) {
        u32 elemsEnd = (u32)((char *)mpEnd - (char *)mpBegin) >> 2;
        u32 elemsBefore = (elemsEnd - ((u32)((char *)pos - (char *)mpBegin) >> 2));

        if (n < elemsBefore) {
            // shift the tail right by n and splice the source in
            void *pTail = (char *)mpEnd - n * 4;
            FUN_00eae010(mpEnd, pTail, (int *)mpEnd);
            mpEnd = (char *)mpEnd + n * 4;
            memmove((char *)mpEnd - (elemsBefore * 4), pos, elemsBefore * 4);
            FUN_00eae010(first, last, (int *)pos);
            return;
        }

        // append then move the tail
        void *pInsert = pos;
        ListNode *mid = first;
        FUN_00eadb10(&pInsert, elemsBefore);
        FUN_00eae010(mid, last, (int *)mpEnd);
        mpEnd = (char *)mpEnd + (n - elemsBefore) * 4;
        FUN_00eae040(mpEnd, pos, (int *)((char *)mpEnd + elemsBefore * 4));
        mpEnd = (char *)mpEnd + elemsBefore * 4;
        FUN_00eae040(first, mid, (int *)((char *)pos + elemsBefore * 4));
        return;
    }

    // grow: new capacity = max(2*size, 1) rounded up to at least n+size
    u32 size = Count();
    u32 newCap = size * 2;
    if (size == 0)
        newCap = 1;
    u32 need = size + n;
    if (need >= newCap)
        newCap = need;

    void *pNew = 0;
    if (newCap != 0)
        pNew = operator_new(newCap * 4, "Simulator", 0, 0);

    char *pMid = (char *)memcpy(pNew, mpBegin, (u32)((char *)pos - (char *)mpBegin));
    for (ListNode *it = first; it != last; it = it->mpNext) {
        *(u32 *)pMid = it->mValue;
        pMid += 4;
    }
    u32 tailBytes = (u32)((char *)mpEnd - (char *)pos);
    char *pEndNew = (char *)memcpy(pMid, pos, tailBytes) + tailBytes;

    if (mpBegin != 0)
        operator_delete_array(mpBegin);
    mpBegin = pNew;
    mpEnd = pEndNew;
    mpCap = (char *)pNew + newCap * 4;
}

// @ 0x00eaf190
ResMusic::ResMusic(const ResMusic &src)
{
    mpVtbl = (void *)0x013ebcdc;
    _InterlockedExchange((volatile long *)&mpPad04, 0);
    mField08 = src.mField08;
    mField0c = src.mField0c;
    mField10 = src.mField10;
    mpVtbl = (void *)0x014884a0;
    mField14 = src.mField14;
    mField18 = src.mField18;
    CopyVec(&mVec1c, &src.mVec1c);
    CopyVec(&mVec30, &src.mVec30);
    CopyVec(&mVec44, &src.mVec44);
    CopyVec(&mVec58, &src.mVec58);
}

// @ 0x00eaf2b0
ResMusic *ResMusic::ScalarDeletingDtor(u8 flags)
{
    if (mVec58.mpBegin != 0)
        operator_delete_array(mVec58.mpBegin);
    if (mVec44.mpBegin != 0)
        operator_delete_array(mVec44.mpBegin);
    if (mVec30.mpBegin != 0)
        operator_delete_array(mVec30.mpBegin);
    if (mVec1c.mpBegin != 0)
        operator_delete_array(mVec1c.mpBegin);
    mpVtbl = (void *)0x013eb938;
    if ((flags & 1) != 0)
        operator_delete_array(this);
    return this;
}

// @ 0x00eaf350
void do_fill_Music(ResMusic *pDst, ResMusic *pEnd, const ResMusic *pSrc)
{
    if (pDst == pEnd)
        return;
    do {
        pDst->mField08 = pSrc->mField08;
        pDst->mField0c = pSrc->mField0c;
        pDst->mField10 = pSrc->mField10;
        pDst->mField14 = pSrc->mField14;
        pDst->mField18 = pSrc->mField18;
        Vec4fAssign(&pDst->mVec1c, &pSrc->mVec1c);
        Vec4fAssign(&pDst->mVec30, &pSrc->mVec30);
        Vec4fAssign(&pDst->mVec44, &pSrc->mVec44);
        Vec4fAssign(&pDst->mVec58, &pSrc->mVec58);
        pDst = (ResMusic *)((char *)pDst + 0x6c);
    } while (pDst != pEnd);
}

// @ 0x00eaf410
ResMusic *do_copy_Music(ResMusic *pBegin, ResMusic *pEnd, ResMusic *pDst)
{
    if (pBegin == pEnd)
        return pDst;
    do {
        pDst->mField08 = pBegin->mField08;
        pDst->mField0c = pBegin->mField0c;
        pDst->mField10 = pBegin->mField10;
        pDst->mField14 = pBegin->mField14;
        pDst->mField18 = pBegin->mField18;
        Vec4fAssign(&pDst->mVec1c, &pBegin->mVec1c);
        Vec4fAssign(&pDst->mVec30, &pBegin->mVec30);
        Vec4fAssign(&pDst->mVec44, &pBegin->mVec44);
        Vec4fAssign(&pDst->mVec58, &pBegin->mVec58);
        pBegin = (ResMusic *)((char *)pBegin + 0x6c);
        pDst = (ResMusic *)((char *)pDst + 0x6c);
    } while (pBegin != pEnd);
    return pDst;
}

// @ 0x00eaf490
ResMusic *do_copy_backward_Music(ResMusic *pBegin, ResMusic *pEnd, ResMusic *pDst)
{
    if (pEnd == pBegin)
        return pDst;
    do {
        pEnd = (ResMusic *)((char *)pEnd - 0x6c);
        pDst = (ResMusic *)((char *)pDst - 0x6c);
        pDst->mField08 = pEnd->mField08;
        pDst->mField0c = pEnd->mField0c;
        pDst->mField10 = pEnd->mField10;
        pDst->mField14 = pEnd->mField14;
        pDst->mField18 = pEnd->mField18;
        CopyVecRaw(&pDst->mVec1c, &pEnd->mVec1c);
        CopyVecRaw(&pDst->mVec30, &pEnd->mVec30);
        CopyVecRaw(&pDst->mVec44, &pEnd->mVec44);
        CopyVecRaw(&pDst->mVec58, &pEnd->mVec58);
    } while (pEnd != pBegin);
    return pDst;
}

// @ 0x00eaf510
void PlayerMusic::AddNote(u32 *pOut)
{
    PlayerMusic *pThis = this;
    // Step 1: pick a note index (uniform if the degree list is empty, else a
    // weighted choice keyed by the last degree).
    u32 degreeCount = (u32)((char *)pThis->mVec13c.mpEnd - (char *)pThis->mVec13c.mpBegin) >> 2;
    u32 drawn;
    if (pThis->mVec13c.mpBegin == pThis->mVec13c.mpEnd) {
        drawn = RandomUint32Uniform(pThis->mRng, 7);
    } else {
        u32 lastKey = ((u32 *)pThis->mVec13c.mpEnd)[-1];
        u32 weight = ((u32 *)(void *)((char *)pThis + 0x78))[lastKey];
        drawn = RandomUint32WeightedChoice(pThis->mRng, 7, weight);
    }
    // push the drawn degree onto the degree history
    if (pThis->mVec13c.mpEnd < pThis->mVec13c.mpCap) {
        float *p = pThis->mVec13c.mpEnd;
        pThis->mVec13c.mpEnd = p + 1;
        if (p != 0)
            *(u32 *)p = drawn;
    } else {
        FUN_00ea9440(&pThis->mVec13c, &drawn);
    }

    // Step 2: absolute pitch for the drawn degree
    u32 lastKey2 = ((u32 *)pThis->mVec13c.mpEnd)[-1];
    u32 pitch = pThis->mpVolTable[lastKey2] + (u32)pThis->mTranspose;
    if (pThis->mVec1cc.mpEnd < pThis->mVec1cc.mpCap) {
        float *p = pThis->mVec1cc.mpEnd;
        pThis->mVec1cc.mpEnd = p + 1;
        if (p != 0)
            *(u32 *)p = pitch;
    } else {
        FUN_00ea9440(&pThis->mVec1cc, &pitch);
    }

    // Step 3: whether this degree differs from the previous one (rest = 2)
    u32 noteIndex = degreeCount;
    u32 diffFlag;
    u32 cur = ((u32 *)pThis->mVec13c.mpBegin)[noteIndex];
    if (cur == 0xffffffff)
        diffFlag = 2;
    else if (noteIndex == 0)
        diffFlag = 0;
    else {
        u32 prev = ((u32 *)pThis->mVec13c.mpBegin)[noteIndex - 1];
        u32 *row = (u32 *)(void *)((char *)pThis + 0x94 + prev * 4);
        diffFlag = (row[cur] == 0) ? 1 : 0;
    }
    if (pThis->mVec128.mpEnd < pThis->mVec128.mpCap) {
        float *p = pThis->mVec128.mpEnd;
        pThis->mVec128.mpEnd = p + 1;
        if (p != 0)
            *(u32 *)p = diffFlag;
    } else {
        FUN_00ea9440(&pThis->mVec128, &diffFlag);
    }

    // Step 4: compute the next onset time and record the delta.
    float frac = pThis->mLastTime / pThis->mTempo;
    u32 notePos = pThis->mNoteIndex;
    u32 rows = ((u32 *)(void *)((char *)pThis + 0x40))[notePos];
    float *table = *(float **)((char *)(void *)((char *)pThis + 0x54) + notePos * 4);

    u32 step = (u32)(long long)(frac + 0.5) + 1;
    float r;
    do {
        r = (float)RandomDoubleUniform(pThis->mRng);
        step++;
    } while (table[(step - 1) % rows] < r);

    float newTime = (float)step * pThis->mTempo;
    float delta = newTime - pThis->mLastTime;
    if (pThis->mVec1e0.mpEnd < pThis->mVec1e0.mpCap) {
        float *p = pThis->mVec1e0.mpEnd;
        pThis->mVec1e0.mpEnd = p + 1;
        if (p != 0)
            *p = delta;
    } else {
        FUN_00eae430(&pThis->mVec1e0, &delta);
    }
    pThis->mLastTime = newTime;

    // Step 5: emit the debug/trace channel values.
    void *pSys;
    pSys = EA__Audio__GetSystemAT();
    if (pSys != 0) {
        ((void (__thiscall *)(void *, u32))((void **)*(void **)pSys)[0x38/4])(pSys, 0x3cdd1a9);
        ((void (__thiscall *)(void *, u32, u32))((void **)*(void **)pSys)[0x40/4])(pSys, 0x34753a7, 0xe7b72656);
        ((void (__thiscall *)(void *, u32, float))((void **)*(void **)pSys)[0x3c/4])(pSys, 0x34753aa, (float)(i32s)noteIndex);
        ((void (__thiscall *)(void *))((void **)*(void **)pSys)[0x58/4])(pSys);
    }
    pSys = EA__Audio__GetSystemAT();
    if (pSys != 0) {
        ((void (__thiscall *)(void *, u32))((void **)*(void **)pSys)[0x38/4])(pSys, 0x3cdd1a9);
        ((void (__thiscall *)(void *, u32, u32))((void **)*(void **)pSys)[0x40/4])(pSys, 0x34753a7, 0xfe31e5d9);
        ((void (__thiscall *)(void *, u32, float))((void **)*(void **)pSys)[0x3c/4])(pSys, 0x34753aa, (float)(i32s)((u32 *)pThis->mVec1cc.mpEnd)[-1]);
        ((void (__thiscall *)(void *))((void **)*(void **)pSys)[0x58/4])(pSys);
    }
    pSys = EA__Audio__GetSystemAT();
    if (pSys != 0) {
        ((void (__thiscall *)(void *, u32))((void **)*(void **)pSys)[0x38/4])(pSys, 0x3cdd1a9);
        ((void (__thiscall *)(void *, u32, u32))((void **)*(void **)pSys)[0x40/4])(pSys, 0x34753a7, 0xc309bcc9);
        ((void (__thiscall *)(void *, u32, float))((void **)*(void **)pSys)[0x3c/4])(pSys, 0x34753aa, pThis->mVec1e0.mpEnd[-1]);
        ((void (__thiscall *)(void *))((void **)*(void **)pSys)[0x58/4])(pSys);
    }
    pSys = EA__Audio__GetSystemAT();
    if (pSys != 0) {
        ((void (__thiscall *)(void *, u32))((void **)*(void **)pSys)[0x38/4])(pSys, 0x3cdd1a9);
        ((void (__thiscall *)(void *, u32, u32))((void **)*(void **)pSys)[0x40/4])(pSys, 0x34753a7, 0x0ead8248);
        ((void (__thiscall *)(void *, u32, float))((void **)*(void **)pSys)[0x3c/4])(pSys, 0x34753aa,
                (float)(i32s)((u32)((char *)pThis->mVec1cc.mpEnd - (char *)pThis->mVec1cc.mpBegin) >> 2));
        ((void (__thiscall *)(void *))((void **)*(void **)pSys)[0x58/4])(pSys);
    }

    // Step 6: return the newly-appended values.
    pOut[0] = ((u32 *)pThis->mVec1cc.mpEnd)[-1];
    pOut[1] = ((u32 *)pThis->mVec1e0.mpEnd)[-1];
    pOut[2] = ((u32 *)pThis->mVec128.mpEnd)[-1];
}

// @ 0x00eaf8d0
void PlayerMusic::MoveNote(u32 noteIndex, u32 numMoved)
{
    PlayerMusic *pThis = this;
    // Compute the element offset and save the three parallel values for this note.
    u32 off = noteIndex * 4;
    u8 *base = (u8 *)pThis;
    VecU *pVec13c = (VecU *)(base + 0x13c);
    VecU *pVec1cc = (VecU *)(base + 0x1cc);
    VecU *pVec128 = (VecU *)(base + 0x128);
    VecU *pVec1e0 = (VecU *)(base + 0x1e0);

    u32 saved13c = ((u32 *)pVec13c->mpBegin)[noteIndex];
    float saved1e0 = pVec1e0->mpBegin[noteIndex];
    u32 saved1cc = ((u32 *)pVec1cc->mpBegin)[noteIndex];
    u32 saved128 = ((u32 *)pVec128->mpBegin)[noteIndex];

    // Remove the note from each of the four parallel vectors by shifting the
    // tail down one slot and decrementing the end pointer.
    VecU *rm[4];
    rm[0] = pVec1cc;
    rm[1] = pVec13c;
    rm[2] = pVec1e0;
    rm[3] = pVec128;
    for (int i = 0; i < 4; i++) {
        VecU *v = rm[i];
        u8 *p = (u8 *)v->mpBegin + off;
        u8 *q = p + 4;
        if (q < (u8 *)v->mpEnd)
            memcpy(p, q, (u32)((u8 *)v->mpEnd - q));
        v->mpEnd = (float *)((u8 *)v->mpEnd - 4);
    }

    // Re-insert the saved values through the same push_back paths as AddNote.
    if (pVec1cc->mpEnd < pVec1cc->mpCap) {
        float *p = pVec1cc->mpEnd++;
        if (p != 0)
            *(u32 *)p = saved1cc;
    } else {
        FUN_00ea9440(pVec1cc, &saved1cc);
    }
    if (pVec13c->mpEnd < pVec13c->mpCap) {
        float *p = pVec13c->mpEnd++;
        if (p != 0)
            *(u32 *)p = saved13c;
    } else {
        FUN_00ea9440(pVec13c, &saved13c);
    }
    if (pVec1e0->mpEnd < pVec1e0->mpCap) {
        float *p = pVec1e0->mpEnd++;
        if (p != 0)
            *p = saved1e0;
    } else {
        FUN_00eae430(pVec1e0, &saved1e0);
    }
    if (pVec128->mpEnd < pVec128->mpCap) {
        float *p = pVec128->mpEnd++;
        if (p != 0)
            *(u32 *)p = saved128;
    } else {
        FUN_00ea9440(pVec128, &saved128);
    }

    // Re-emit the trace channel values for noteIndex (four groups: one for each
    // parallel vector value).
    void *pSys = EA__Audio__GetSystemAT();
    if (pSys != 0) {
        ((void (__thiscall *)(void *, u32))((void **)*(void **)pSys)[0x38/4])(pSys, 0x3cdd1a9);
        ((void (__thiscall *)(void *, u32, u32))((void **)*(void **)pSys)[0x40/4])(pSys, 0x34753a7, 0xe7b72656);
        ((void (__thiscall *)(void *, u32, float))((void **)*(void **)pSys)[0x3c/4])(pSys, 0x34753aa, (float)(i32s)noteIndex);
        ((void (__thiscall *)(void *))((void **)*(void **)pSys)[0x58/4])(pSys);
    }
    pSys = EA__Audio__GetSystemAT();
    if (pSys != 0) {
        ((void (__thiscall *)(void *, u32))((void **)*(void **)pSys)[0x38/4])(pSys, 0x3cdd1a9);
        ((void (__thiscall *)(void *, u32, u32))((void **)*(void **)pSys)[0x40/4])(pSys, 0x34753a7, 0xfe31e5d9);
        ((void (__thiscall *)(void *, u32, float))((void **)*(void **)pSys)[0x3c/4])(pSys, 0x34753aa, (float)(i32s)((u32 *)pVec1cc->mpBegin)[noteIndex]);
        ((void (__thiscall *)(void *))((void **)*(void **)pSys)[0x58/4])(pSys);
    }
    pSys = EA__Audio__GetSystemAT();
    if (pSys != 0) {
        ((void (__thiscall *)(void *, u32))((void **)*(void **)pSys)[0x38/4])(pSys, 0x3cdd1a9);
        ((void (__thiscall *)(void *, u32, u32))((void **)*(void **)pSys)[0x40/4])(pSys, 0x34753a7, 0xc309bcc9);
        ((void (__thiscall *)(void *, u32, float))((void **)*(void **)pSys)[0x3c/4])(pSys, 0x34753aa, pVec1e0->mpBegin[noteIndex]);
        ((void (__thiscall *)(void *))((void **)*(void **)pSys)[0x58/4])(pSys);
    }
    pSys = EA__Audio__GetSystemAT();
    if (pSys != 0) {
        ((void (__thiscall *)(void *, u32))((void **)*(void **)pSys)[0x38/4])(pSys, 0x3cdd1a9);
        ((void (__thiscall *)(void *, u32, u32))((void **)*(void **)pSys)[0x40/4])(pSys, 0x34753a7, 0x0ead8248);
        ((void (__thiscall *)(void *, u32, float))((void **)*(void **)pSys)[0x3c/4])(pSys, 0x34753aa,
                (float)(i32s)((u32)((char *)pVec13c->mpEnd - (char *)pVec13c->mpBegin) >> 2));
        ((void (__thiscall *)(void *))((void **)*(void **)pSys)[0x58/4])(pSys);
    }

    (void)numMoved;
    (void)saved128;
}

// @ 0x00eafcf0
char PlayerMusic_ToString(PlayerMusic *pThis, void *pWriter, u16 *pName)
{
    (void)pThis;
    // Serializer: opens a "list", writes each circular-list node's payload as a
    // "uint32_t" typed value, then closes the list.  The list head is the first
    // argument (a sentinel whose `next` points at the first element).
    char ok = 1;
    ListNode *pHead = (ListNode *)pWriter;
    if (pHead != pHead->mpNext) {
        u32 w[4];
        void *pKey;
        if (pName != 0) {
            EA__ConvertToString16(w, pName, -1);
            pKey = w;
        } else {
            u32 z[3] = { 0, 0, 0 };
            eastl__wstring__range_initialize(z, 0, 0);
            pKey = z;
        }
        void *pNameStr;
        eastl_wstring_ctor(&pNameStr, pKey);
        // vtable slot 0: BeginList(name)
        ((void (__thiscall *)(void *, void *))((void **)*(void **)pWriter)[0])(pWriter, pNameStr);
        // walk nodes, writing the +8 payload of each
        ListNode *end = (ListNode *)0;
        for (ListNode *it = pHead->mpNext; it != end; it = it->mpNext) {
            if (ok)
                ok = SP__TypedValueToStringT_short__Write(&pNameStr, (void *)it->mValue, 0, (const u16 *)0x1401158);
        }
        // vtable slot 4: EndList(name)
        ((void (__thiscall *)(void *, void *))((void **)*(void **)pWriter)[1])(pWriter, pNameStr);
    }
    return ok;
}

// @ 0x00eafe40
char PlayerMusic_FromString(PtrVec *pVec, u16 *pName, void *pWriter)
{
    // Serializer over a (begin,end) range of u32: BeginList(name), Write each
    // element as "uint32_t", EndList(name).
    char ok = 1;
    if (pVec->mpBegin != pVec->mpEnd) {
        u32 w[4];
        void *pKey;
        if (pName != 0) {
            EA__ConvertToString16(w, pName, -1);
            pKey = w;
        } else {
            u32 z[3] = { 0, 0, 0 };
            eastl__wstring__range_initialize(z, 0, 0);
            pKey = z;
        }
        void *pNameStr;
        eastl_wstring_ctor(&pNameStr, pKey);
        ((void (__thiscall *)(void *, void *))((void **)*(void **)pWriter)[0])(pWriter, pNameStr);
        for (u32 *it = (u32 *)pVec->mpBegin; it != (u32 *)pVec->mpEnd; ++it) {
            if (!ok)
                break;
            ok = SP__TypedValueToStringT_short__Write(&pNameStr, it, 0, (const u16 *)0x1401158);
        }
        ((void (__thiscall *)(void *, void *))((void **)*(void **)pWriter)[1])(pWriter, pNameStr);
    }
    return ok;
}

// @ 0x00eb0ea0
cPlayerCityMusic_s00eb_0ea0::cPlayerCityMusic_s00eb_0ea0()
{
    mUndoBuffer.mpBegin = nullptr;
    mUndoBuffer.mpEnd = nullptr;
    mUndoBuffer.mpField08 = nullptr;
    mUndoBuffer.resize(1);

    mUndoBuffer.mpHead = mUndoBuffer.mpBegin;
    mUndoBuffer.mpTail = mUndoBuffer.mpBegin;
    mUndoBuffer.mnWrap = 0;

    mpUndo = &mUndoBuffer;
    mpUndoBegin = mUndoBuffer.mpTail;

    mbPaused = 0;
    mbQuiet = 0;
    mRandom.SetSeed(0xffffffff);
    mnMagic = 0x5293d931;

    mpArray10CBegin = nullptr;
    mpArray10CEnd = nullptr;
    mpArray10CCap = nullptr;
    mpArray118Begin = nullptr;
    mpArray118End = nullptr;

    mpArray128Begin = nullptr;
    mpArray128End = nullptr;
    mpArray128Cap = nullptr;

    mpArray13CBegin = nullptr;
    mpArray13CEnd = nullptr;
    mpArray13CCap = nullptr;

    mfField150 = 0.0f;
    mnField154 = 0;
    mnField158 = 0;
    mnField15C = 0;

    mStopwatch.Init(1000, false);

    mpVolumesBegin = gEmptyString16;
    mpVolumesEnd = gEmptyString16;
    mpVolumesCap = gEmptyString16 + 1;
    mpVolumesBufA = gEmptyString16;
    mpVolumesBufB = gEmptyString16;
    mpVolumesBufC = gEmptyString16 + 1;

    mpNotePitchesBegin = mfNotePitchesBuffer;
    mpNotePitchesEnd = mfNotePitchesBuffer;
    mpNotePitchesCap = mfNotePitchesBuffer + 3;

    float fOne = 1.0f;
    FUN_00eaed40(mfNotePitchesBuffer, 3, &fOne);

    mpList1B8Next = &mpList1B8Next;
    mpList1B8Prev = &mpList1B8Next;
    mpList1C4 = nullptr;
    mpList1C8 = nullptr;
    mpList1CC = nullptr;
    mpList1D0 = nullptr;
    mpList1D4 = nullptr;
    mpList1E0 = nullptr;
    mpList1E4 = nullptr;
    mpList1E8 = nullptr;

    mpMessageServer = nullptr;
    mpHandler = nullptr;
    mnHandlerId = 0;
    mnHandlerKind = 0;
    mpHandlerData = nullptr;

    mpMessageServer = MessageServer_s00eb_0ea0();
    mpHandler = this;
    mnHandlerId = 0x149c618;
    mnHandlerKind = 1;
    mpHandlerData = nullptr;

    if (mpMessageServer != nullptr && mpHandler != nullptr)
        mpMessageServer->Register(0xf62def, mpHandler);

    FUN_00eb0460();
}

// @ 0x00eb10d0
void cPlayerCityMusic_s00eb_0ea0::ResetUndoBuffer()
{
    cMusicRing* pRing = &mUndoBuffer;

    if (pRing->GetCount() <= 1)
        pRing->reserve(1);

    pRing->mpHead = pRing->mpBegin;
    pRing->mpTail = pRing->mpBegin;
    pRing->mnWrap = 0;

    pRing->mpTail = pRing->mpTail + 1;
    if (pRing->mpTail == pRing->mpEnd)
        pRing->mpTail = pRing->mpBegin;

    if (pRing->mpTail == pRing->mpHead) {
        pRing->mpHead = pRing->mpHead + 1;
        if (pRing->mpHead == pRing->mpEnd)
            pRing->mpHead = pRing->mpBegin;
    }
    else {
        ++pRing->mnWrap;
    }

    cResourceCityMusic* pTail = pRing->mpTail;
    if (pTail == pRing->mpBegin)
        pTail = pRing->mpEnd;

    SaveData(pTail - 1);

    mpUndo = pRing;
    mpUndoBegin = pRing->mpHead;
}

// @ 0x00eb1170
void cPlayerCityMusic_s00eb_0ea0::AddUndoState()
{
    cMusicRing* pRing = &mUndoBuffer;
    cMusicRing* pSaved = mpUndo;

    int32_t nCount = pRing->GetCount();
    cResourceCityMusic* pFirst = mpUndoBegin;
    if (nCount <= 1)
        pFirst = pRing->mpBegin - nCount;

    cResourceCityMusic* pNext = pFirst + 1;
    cRingIter aFirst;
    aFirst.mpRing = pSaved;
    aFirst.mpState = mpUndoBegin;
    cRingIter aLast;
    aLast.mpRing = pRing;
    aLast.mpState = pNext;
    pRing->erase(aFirst, aLast);

    int32_t nSize = pRing->GetCount() - 1;
    if ((uint32_t)nSize <= mConfig.mIcons[2]) {
        cResourceCityMusic* pHead = pRing->mpHead + 1;
        if (pHead == pRing->mpEnd)
            pHead = pRing->mpBegin;
        if (pHead == mpUndoBegin) {
            uint32_t nWanted = (uint32_t)(nSize + 1);
            uint32_t nDoubled = (nSize == 0) ? 1 : (uint32_t)(nSize * 2);
            uint32_t nReserve = (nWanted < nDoubled) ? nWanted : nDoubled;
            pRing->reserve((int32_t)nReserve);
        }
    }

    pRing->mpTail = pRing->mpTail + 1;
    if (pRing->mpTail == pRing->mpEnd)
        pRing->mpTail = pRing->mpBegin;

    if (pRing->mpTail == pRing->mpHead) {
        pRing->mpHead = pRing->mpHead + 1;
        if (pRing->mpHead == pRing->mpEnd)
            pRing->mpHead = pRing->mpBegin;
    }
    else {
        ++pRing->mnWrap;
    }

    cResourceCityMusic* pTail = pRing->mpTail;
    if (pTail == pRing->mpBegin)
        pTail = pRing->mpEnd;

    SaveData(pTail - 1);

    cResourceCityMusic* pSavedTail = pRing->mpTail;
    if (pSavedTail == pRing->mpBegin)
        pSavedTail = pRing->mpEnd;

    mpUndo = pRing;
    mpUndoBegin = pSavedTail - 1;
}

// @ 0x00eb12a0
bool cPlayerCityMusic_s00eb_0ea0::HandleMessage(int32_t nType, cEapdMessage* pMessage)
{
    switch (nType) {
    case 0x69aa284:
        Reset(true);
        return true;

    case 0x539a4cf:
        MessageServer_s00eb_0ea0()->Send(0x69aa284, 0, 0, 0);
        return true;

    case 0xf62def:
        if (!mConfig.Reload(pMessage->mnField08, pMessage->mnField10, pMessage->mnField18))
            return true;
        ResetUndoBuffer();
        FUN_00eb0460();
        return true;

    case 0x41638ca: {
        uint32_t nSubType = pMessage->GetType();
        if (nSubType == 0x620bba33) {
            float fValue;
            pMessage->GetNextFloat(&fValue);
            mnField15C = (int32_t)fValue;
            mfField174 = GetCyclesToUnitsCoefficient(5) * fValue * 0.0010416667f;
        }
        else if (nSubType == 0xdec4e95f) {
            float fValue;
            pMessage->GetNextFloat(&fValue);
            mnField158 = (int32_t)fValue;
            pMessage->MarkProcessed();
            return true;
        }
        else if (nSubType != 0xe66bc36a) {
            pMessage->MarkProcessed();
            return false;
        }

        mStopwatch.Restart();
        pMessage->MarkProcessed();
        return true;
    }

    default:
        break;
    }

    return false;
}
