// src/game/SPGonzago/SPAudioPlayerCityMusic.cpp -- migrated from slice(s) s0137ef90, s00eaffc0, s00eae0f0, s00eb0ea0, s00eaefa0, s00ead1a0, s00eac530 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPAudioPlayerCityMusic.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "sse_helpers.h"
#include "EA/Stopwatch.h"

// unnamed retail callees and globals (address in the comment)
extern int32_t g_1488414[];                      // 0x01488414  global property id table
#include <math.h>
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cVarListSerializer.h"
#include "EA/LimitStopwatch.h"
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
// FloorToInt: the vetted SseFloorToInt in sse_helpers.h

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
extern "C" void* __cdecl memcpy_(void* d, const void* s, unsigned n);                          // 0x011e0744
extern "C" __declspec(dllimport) void* __cdecl memmove_imp(void* d, const void* s, unsigned n); // 0x013cc480
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
void* __stdcall ListErase(void* out, void* a, void* b);         // 0x00973d10
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
struct cIntVec {
    int* mpBegin_00;   // +0x00
    int* mpEnd_04;     // +0x04
    int* mpCap_08;     // +0x08
    void FUN_00eade60(unsigned newCap);
};
struct cFloatVec {
    float* mpBegin_00;   // +0x00
    float* mpEnd_04;     // +0x04
    float* mpCap_08;     // +0x08
    void FUN_00eadf40(float* pos, float* value);
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
    void FUN_00ead6a0();  // 0x00ead6a0 (cEditorResource::FUN_00ead6a0)
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

// ---- items of slice s00eae0f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_11e0744_memcpy(void*, const void*, unsigned int);  // 0x011e0744
static int* VecGrowN(int* v, int* pos, unsigned n, int val)
{
    int* begin = (int*)v[0];
    int* end = (int*)v[1];
    unsigned cap = (unsigned)(v[2] - (int)end) >> 2;
    if (cap < n) {
        unsigned oldLen = (unsigned)(end - begin);
        unsigned newCap = oldLen * 2;
        if (oldLen == 0)
            newCap = 1;
        unsigned want = oldLen + n;
        if (newCap < want)
            newCap = want;
        int* dst = newCap ? new int[newCap] : 0;
        int* p = begin;
        int* out = dst;
        while (p != pos)
            *out++ = *p++;
        int* fillEnd = out + n;
        int* q = out;
        while (q != fillEnd)
            *q++ = val;
        while (p != end)
            *out++ = *p++;
        delete[] begin;
        v[0] = (int)dst;
        v[1] = (int)out;
        v[2] = (int)(dst + newCap);
        return out;
    }
    if (n != 0) {
        unsigned tail = (unsigned)(end - pos);
        if (n < tail) {
            unsigned cnt = (unsigned)(end - (pos + n));
            int* d = end;
            int* s = end - n;
            while (cnt--)
                *--d = *--s;
            v[1] = (int)(end + n);
            int* s2 = pos;
            while (s2 != pos + n)
                *s2++ = val;
            return pos;
        } else {
            unsigned copyFirst = tail;
            int* w = end;
            for (unsigned i = 0; i < n - tail; ++i)
                *w++ = val;
            v[1] = (int)w;
            int* s = pos;
            int* d = end;
            while (copyFirst--)
                *d++ = *s++;
            v[1] = (int)d;
            int* s2 = pos;
            while (s2 != pos + n)
                *s2++ = val;
            return pos;
        }
    }
    return pos;
}
struct AT {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38(int);
virtual void v3c(int, float);
virtual void v40(int, int);
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
    virtual void v58();
};
AT* __cdecl GetSystemAT_s00ea_e0f0();   // 0x00a206f0
static void NoteEvent(int which, int val, int tagB)
{
    AT* at = GetSystemAT_s00ea_e0f0();
    if (at) {
        at->v38(0x3cdd1a9);
        at->v40(0x34753a7, which);
        float f = (float)val;
        if (val < 0)
            f += 4294967296.0f;
        at->v3c(0x34753aa, f);
        at->v58();
    }
    at = GetSystemAT_s00ea_e0f0();
    if (at) {
        at->v38(0x3cdd1a9);
        at->v40(0x34753a7, tagB);
        at->v3c(0x34753aa, (float)val);
        at->v58();
    }
}
struct cPlayerCityMusic_s00ea_e0f0 {
    char   pad0[0x110];
    unsigned mNoteStateIdx;   // +0x110
    float* mNoteStatesBegin;  // +0x114
    float* mNoteStatesEnd;    // +0x118
    char   pad11c[0x128 - 0x11c];
    float* mVec128B;          // +0x128
    float* mVec128E;          // +0x12c
    char   pad130[0x13c - 0x130];
    float* mVec13cB;          // +0x13c
    float* mVec13cE;          // +0x140
    char   pad144[0x150 - 0x144];
    float  mDownbeat;         // +0x150
    char   pad154[0x1b8 - 0x154];
    int*   mList1b8;          // +0x1b8
    char   pad1bc[0x1cc - 0x1bc];
    int*   mNoteDegB;         // +0x1cc
    int*   mNoteDegE;         // +0x1d0
    char   pad1d4[0x1e0 - 0x1d4];
    float* mVec1e0B;          // +0x1e0
    float* mVec1e0E;          // +0x1e4
    void DeselectAmbience(float value, unsigned* idx, float* out);  // 0x00eae0f0 (cPlayerCityMusic::DeselectAmbience)
    void RemoveNote(unsigned idx);  // 0x00eae610 (cPlayerCityMusic::RemoveNote)
};
struct IStream;
struct IReader {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual IStream* v20();
};
struct IStream {
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual IStream* s18();
};
void __cdecl ReadInt32(void* stream, int* out, int a, int b);   // 0x0093a780
void __cdecl FUN_00eade60(int a);
void __cdecl FUN_00eadf40(int* at, int* val);
// ---- items of slice s00eae0f0 end

// ---- items of slice s00eaffc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
void  __cdecl operator_delete(void* p);                                  // 0xf47380
struct CVarListSerializer {
    void ctor(void* owner, void* sig, int flags);   // 0x692f90
    bool Serialize(void* stream);                   // 0x693e10
};
static void* move_range(void** dst, void** first, void** last)
{
    memcpy_(dst, first, (unsigned int)((char*)last - (char*)first));
    return dst;
}
struct PtrRange {
    void** mpBegin;      // +0x00
    void** mpEnd;        // +0x04
    void** mpCapacity;   // +0x08
    void clear() {
        void** end = mpEnd;
        void** begin = mpBegin;
        move_range(begin, end, end);
        mpEnd += begin - end;
    }
};
struct EventNode {
    EventNode* mpNext;   // +0x00
    EventNode* mpPrev;   // +0x04
};
struct EventList {
    EventNode mSentinel; // +0x00  mpNext / mpPrev
    void clear() {
        EventNode* sentinel = &mSentinel;
        EventNode* p = sentinel->mpNext;
        while (p != sentinel) {
            EventNode* next = p->mpNext;
            operator_delete(p);
            p = next;
        }
        sentinel->mpNext = sentinel;
        sentinel->mpPrev = sentinel;
    }
};
void __fastcall FUN_00eb05a0(void* self_);  // 0x00eb05a0 (defined below; used by a stub's inline body)
struct cPlayerCityMusic_s00ea_ffc0 {
    char       pad0[0x10c];
    int        m10c;         // +0x10c  "loaded" flag gating Reset
    char       pad1[0x198 - 0x110];
    PtrRange   m198;         // +0x198  layer note range  (begin/end/cap)
    char       pad2[0x1b8 - 0x1a4];
    EventList  m1b8;         // +0x1b8  event list sentinel
    char       pad3[0x1cc - 0x1c0];
    PtrRange   m1cc;         // +0x1cc  layer id range
    char       pad4[0x1e0 - 0x1d8];
    PtrRange   m1e0;         // +0x1e0  layer aux range

    void Reset(char full);                                   // 0xead1a0
    void FUN_00eb05a0();                                     // 0xeb05a0
    bool Read(int stream);                                   // 0xeb0a60
};
typedef          int   s32;
void  __fastcall FUN_00eae540(void* self, int, void* src);                                   // 0xeae540
void  __fastcall FUN_00eaeef0(void* self, int, void* first, void* last, void* owner);        // 0xeaeef0
void  __fastcall FUN_00eaefa0(void* self, int, void* a, void* b, void* c, void* d);          // 0xeaefa0
void* __cdecl    FUN_00eaf410(void* first, void* last, void* dest);                          // 0xeaf410
void  __fastcall FUN_00eaf510(void* self, int, void* out);                                   // 0xeaf510 AddNote
void  __fastcall FUN_00eae610(void* self, int, u32 idx);                                     // 0xeae610 RemoveNote
void  __fastcall FUN_00ead1a0(void* self, int, u8 flag);                                     // 0xead1a0 Reset
void  __fastcall FUN_00eb0230(void* self, int, u32 n);                                       // 0xeb0230
void  __fastcall FUN_00eb1460(void* self, int, u32 count, void* tmp);                        // 0xeb1460
void  __fastcall FUN_00eb1d70(void* self);                                                   // 0xeb1d70 cResourceCityMusic ctor
void  __fastcall FUN_00ead6a0(void* self);                                                   // 0xead6a0 cResourceCityMusic dtor
void  __fastcall FUN_00ead660(void* self);                                                   // 0xead660 cResourceCityMusic vector dtor
void  __fastcall FUN_00b93c60(void* out, int, u32 n, void* allocator);                       // 0xb93c60
u32   __fastcall FUN_00a68fb0(void* self, int, u32 n);                                       // 0xa68fb0 RandomUint32Uniform
u32   __cdecl    FUN_005e8ec0(void* rng, u32 count, u32 hi);                                 // 0x5e8ec0 WeightedChoice
void* __cdecl    FUN_00f473a0(u32 size, const char* name, u32 a, u32 b, const char* alloc, u32 line); // operator new
void  __cdecl    FUN_00f47380(void* p);                                                      // operator delete
void  __fastcall FUN_00eadee0(void* self, int, void* first, void* last, void* owner);        // 0xeadee0 cList assign
void  __cdecl    FUN_00da1e70(void* first, void* last, void* owner);                         // 0xda1e70
void* __fastcall FUN_00973d10(void* head, int, void* a, void* b);                            // 0x973d10 ListErase
void  __fastcall FUN_00eadab0(void* self, int, u32 count, void* tmp);                        // 0xeadab0
void* __cdecl    FUN_0067dcc0(void);                                                         // 0x67dcc0 MessageServer
void  __cdecl    FUN_00eaf310(void* a, void* b, void* c, void* d, void* e);                  // 0xeaf310
void  __cdecl    FUN_00eaf350(void* first, void* last, void* value);                         // 0xeaf350 fill
void* __cdecl    FUN_00eaf3d0(void* first, void* last, void* dest);                          // 0xeaf3d0
void  __cdecl    FUN_00eacfb0(void* first, void* last, void* dest);                          // 0xeacfb0
void  __cdecl    FUN_00eaf490(void* first, void* last, void* dest);                          // 0xeaf490
void  __cdecl    FUN_00eaff90(void* dest, u32 count, void* value);                           // 0xeaff90 fill
void  __fastcall FUN_00eaf190(void* self, int, void* src);                                   // 0xeaf190 cResourceCityMusic copy ctor
void* __cdecl    FUN_00eaffc0(void* cont, char* cur, void* cont2, char* last, char* dest);
void  __cdecl    FUN_00eb0050(void** out, void* sCont, char* sCur, void* sCont2, char* sLast, void* dCont, char* dCur);
void  __fastcall FUN_00eb0120(void* self);
void  __fastcall FUN_00eb0290(void* self, int, u32 n, u32* value);
u8    __fastcall FUN_00eb0390(void* self, int, void* out);
void  __fastcall FUN_00eb0460(void* self);
void  __fastcall FUN_00eb05a0(void* self);
void* __fastcall FUN_00eb0810(void* vec, int, char* first, char* last);
void  __fastcall FUN_00eb0870(void* vec, int, void* pos, u32 count, void* value);
u8    __fastcall FUN_00eb0b70(void* self, int, void* in);
void  __fastcall FUN_00eb0c30(void* self);
void  __fastcall FUN_00eb0c70(void* self);
void  __fastcall FUN_00eb0cb0(void* self, int, void* out, void* dCont, char* dCur, void* sCont, char* sCur);
void  __fastcall FUN_00eb0d60(void* vec, int, u32 n);
void  __fastcall FUN_00eb0df0(void* self, int, u32 n);
struct CityMusic
{
    u8     pad_000[0x10];
    u32    mNumAmbiences;    // 0x10  bound passed to RandomUint32Uniform
    u32    mNumRhythms;      // 0x14
    u32    mNumInstruments;  // 0x18
    u32    mNumLayers;       // 0x1c
    u32    mMinNotes;        // 0x20
    u32    mMaxNotes;        // 0x24
    u32    mWeightHi;        // 0x28
    u8     pad_02c[0x54 - 0x2c];
    u32*   mVec54Begin;      // 0x54
    u32*   mVec54End;        // 0x58
    u8     pad_05c[0x68 - 0x5c];
    u32    mDegreeBase;      // 0x68
    u8     pad_06c[0x74 - 0x6c];
    u32*   mDegreeTable;     // 0x74  degree lookup (7 entries)
    u8     pad_078[0x94 - 0x78];
    void** mppSuggestions;   // 0x94  array indexed by the previous note's degree
    u8     pad_098[0x104 - 0x98];
    u8     mRng[0xc];        // 0x104 RandomLinearCongruential (0x104..0x10f)
    u32    mNumActive;       // 0x110
    u32*   mActiveBegin;     // 0x114
    u8     pad_118[0x128 - 0x118];
    u32*   mVecABegin;       // 0x128
    u32*   mVecAEnd;         // 0x12c
    u8     pad_130[0x13c - 0x130];
    u32*   mVecBBegin;       // 0x13c
    u32*   mVecBEnd;         // 0x140
    u8     pad_144[0x150 - 0x144];
    float  mTotalDuration;   // 0x150
    u32    mSomeValue;       // 0x154
    u8     pad_158[0x198 - 0x158];
    u32*   mVecCBegin;       // 0x198
    u32*   mVecCEnd;         // 0x19c
    u8     pad_1a0[0x1b8 - 0x1a0];
    void*  mListHead;        // 0x1b8  list sentinel: [0]=prev, [1]=next
    void*  mListTail;        // 0x1bc
    u8     pad_1c0[0x1c4 - 0x1c0];
    u32    mRandomA;         // 0x1c4
    u32    mRandomB;         // 0x1c8
    u32*   mVecDBegin;       // 0x1cc
    u32*   mVecDEnd;         // 0x1d0
    u8     pad_1d4[0x1e0 - 0x1d4];
    u32*   mVecEBegin;       // 0x1e0
    u32*   mVecEEnd;         // 0x1e4
};
static void ClearBoolVec(void** pBegin, void** pEnd)
{
    char* begin = (char*)*pBegin;
    char* end   = (char*)*pEnd;
    memcpy_(begin, end, 0);
    s32 d = (s32)((end - begin) >> 2);
    *pEnd = end + (-d) * 4;
}
// ---- items of slice s00eaffc0 end

// ---- items of slice s0137ef90 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0137_ef90; 
}
typedef eastl::string8_s0137_ef90 string8_s0137_ef90;
namespace Simulator {
class ISerializerReadStream;
}
namespace Simulator {
class ISerializerWriteStream;
}
namespace Simulator {
struct Attribute;
}
namespace Simulator {
typedef bool  (*ReadFunction_t)(ISerializerReadStream*, void*);
}
namespace Simulator {
typedef bool  (*WriteFunction_t)(ISerializerWriteStream*, void*);
}
namespace Simulator {
typedef void  (*ReadTextFunction_t)(const string8_s0137_ef90&, void*);
}
namespace Simulator {
typedef void  (*WriteTextFunction_t)(char*, void*);
}
namespace Simulator {
typedef bool  (*ValidateFunction_t)();
}
namespace Simulator {
typedef bool  (*ToXmlFunction_t)(void*, const char*, int);
}
namespace Simulator {
typedef void* (*OffsetFunction_t)(Attribute*);
}
namespace Simulator {
typedef void  (*SetDefaultFunction_t)(Attribute*);
}
namespace Simulator {
void* DefaultOffset(Attribute* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
}
namespace Simulator {
void* StaticOffset(Attribute* pAttr);    // 0x011874d0: (void*)pAttr->offset (class statics)
}
namespace Simulator {
struct Attribute
{
    // Member attribute: offset is relative to the current object.
    Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault = 0)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = pSetDefault;
        offsetFunction = DefaultOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
        offset = nOffset;
    }

    // Static attribute: the offset field holds the static's address; no ToXml callback.
    Attribute(const char* pName, uint32_t nID, void* pStatic,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = 0;
        offsetFunction = StaticOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = 0;
        offset = (uint32_t)pStatic;
    }

    /* 00h */ const char* name;
    /* 04h */ uint32_t id;
    /* 08h */ uint32_t offset;
    /* 0Ch */ int field_0C;   // not initialized
    /* 10h */ int field_10;   // not initialized
    /* 14h */ int field_14;   // not initialized
    /* 18h */ void* pCurrentObject;
    /* 1Ch */ SetDefaultFunction_t setDefaultFunction;
    /* 20h */ OffsetFunction_t offsetFunction;
    /* 24h */ ReadFunction_t readFunction;
    /* 28h */ WriteFunction_t writeFunction;
    /* 2Ch */ ReadTextFunction_t readTextFunction;
    /* 30h */ WriteTextFunction_t writeTextFunction;
    /* 34h */ ValidateFunction_t validateFunction;
    /* 38h */ ToXmlFunction_t toXmlFunction;
};
}
namespace Simulator {
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);     // 0x00572810
}
namespace Simulator {
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);   // 0x00572840
}
namespace Simulator {
template<typename T> void ReadTextInt(const string8_s0137_ef90& text, void* pData);          // 0x00693090
}
namespace Simulator {
template<typename T> bool AlwaysValid();                                          // 0x00b1fbf0
}
namespace Simulator {
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ac87c0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00eae8a0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00eae9b0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00eaea80(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c33820(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac87f0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00f26ca0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c761c0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c332a0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_00692ff0(const string8_s0137_ef90& text, void* pData);
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0137_ef90& text, void* pData);
}
namespace Simulator {
void ReadText_00694c80(const string8_s0137_ef90& text, void* pData);
}
namespace Simulator {
void WriteText_00692fb0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694ee0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694f00(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694fa0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694c10(char* pBuffer, void* pData);
}
namespace Simulator {
bool ToXml_0057cde0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00675ca0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00acbbc0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_0103c3a0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00eafcf0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00eafe40(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool Validate_00c31ca0();
}
namespace Simulator {
struct AttrSlot { uint32_t d[15]; };
}
namespace Simulator {
extern AttrSlot cMusicData_sAttributes[8];                // 0x015a9198
}
namespace Simulator {
#define INT_ATTR   Read4<int>, Write4<int>, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0
}
namespace Simulator {
#define BOOL_ATTR  Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00
}
namespace Simulator {
#define SHORT_ATTR Read4<short>, Write4<short>, ReadTextInt<short>, WriteText_00694f00, AlwaysValid<short>, ToXml_00675ca0
}
namespace Simulator {
#define ADD_MUSIC(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cMusicData_sAttributes[IDX] = a; }
}
// ---- items of slice s0137ef90 end

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
    int i = SseFloorToInt(f);
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

// @ 0x00eade60
void cIntVec::FUN_00eade60(unsigned newCap)
{
    if (newCap <= (unsigned)(mpCap_08 - mpBegin_00)) return;
    int* p = newCap ? (int*)EAAllocate(newCap * 4, "Simulator", 0, 0, "allocator.h", 0xd1) : 0;
    memcpy_(p, mpBegin_00, (char*)mpEnd_04 - (char*)mpBegin_00);
    if (mpBegin_00)
        operator_delete_array(mpBegin_00);
    int n = (int)((char*)mpEnd_04 - (char*)mpBegin_00) >> 2;
    mpBegin_00 = p;
    mpEnd_04 = p + n;
    mpCap_08 = p + newCap;
}

// @ 0x00eadee0
void cList::FUN_00eadee0(int* begin, int* end, int dummy)
{
    cListNode* n = mHead_00.mpNext_00;
    while (n != &mHead_00) {
        if (begin == end) break;
        n->mKey_08 = *begin;
        n = n->mpNext_00;
        ++begin;
    }
    if (begin == end) {
        ListErase(&begin, n, &mHead_00);
        return;
    }
    FUN_00eada50(&mHead_00, begin, end, dummy);
}

// @ 0x00eadf40
void cFloatVec::FUN_00eadf40(float* pos, float* value)
{
    if (mpEnd_04 != mpCap_08) {
        float* src = value;
        if (pos <= value && value < mpEnd_04) src = value + 1;
        if (mpEnd_04 != 0)
            *mpEnd_04 = *(mpEnd_04 - 1);
        int sz = (int)((char*)(mpEnd_04 - 1) - (char*)pos);
        memmove_imp((char*)mpEnd_04 + ((sz >> 2) * -4), pos, (unsigned)sz);
        *pos = *src;
        mpEnd_04 += 1;
        return;
    }
    float* begin = mpBegin_00;
    float* oldEnd = mpEnd_04;
    int n = (int)(oldEnd - begin);
    int newCap = n * 2;
    if (n == 0) newCap = 1;
    int off = (int)((char*)value - (char*)begin);
    float* slot = (float*)((char*)memcpy_(0, begin, (unsigned)off) + ((off >> 2) * 4));
    if (slot)
        *slot = *value;
    int tail = (int)((char*)oldEnd - (char*)value);
    void* r = memcpy_(slot + 1, value, (unsigned)tail);
    mpBegin_00 = 0;
    mpEnd_04 = (float*)((char*)r + ((tail >> 2) * 4));
    mpCap_08 = (float*)(newCap * 4);
}

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

// @ 0x00eae0f0
void cPlayerCityMusic_s00ea_e0f0::DeselectAmbience(float value, unsigned* idx, float* out)
{
    unsigned count = (unsigned)(this->mNoteStatesEnd - this->mNoteStatesBegin);
    if (this->mNoteStateIdx < count) {
        *idx = 0;
        if (count != 0) {
            do {
                unsigned i = *idx;
                if ((unsigned)this->mNoteStatesBegin[i] == 0) {
                    this->mNoteStatesBegin[i] = value;
                    NoteEvent(0x330df985, (int)value, 0x3fbc0a67);
                    this->mNoteStateIdx++;
                    break;
                }
                *idx = i + 1;
            } while (*idx < count);
        }
    } else {
        int* node = this->mList1b8;
        *out = *(float*)(node[2]);
        *(int*)node[1] = node[0];
        *(int*)(node[0] + 4) = node[1];
        delete node;
        *idx = 0;
        if (count != 0) {
            do {
                unsigned i = *idx;
                if (*out == this->mNoteStatesBegin[i]) {
                    this->mNoteStatesBegin[i] = value;
                    NoteEvent(0xaa1b3b8d, (int)value, 0x330df985);
                    break;
                }
                *idx = i + 1;
            } while (*idx < count);
        }
    }
    float* n = new float[3];
    if (n + 2 != 0)
        n[2] = value;
    *(int*)n = (int)&this->mNoteStatesBegin;
    *(int*)(n + 1) = (int)this->mNoteStatesEnd;
    this->mNoteStatesEnd = n;
}

// @ 0x00eae430
void FUN_00eae430(int* v, int* pos, int* val)
{
    int* end = (int*)v[1];
    if (end != (int*)v[2]) {
        if (pos <= val && val < end)
            val = (int*)((char*)val + 4);
        if (end != 0)
            *end = end[-1];
        int* p = pos;
        int* e = (int*)v[1];
        unsigned n = (unsigned)((e - 1) - pos) + 1;
        int* q = e - n;
        for (unsigned i = 0; i < n; ++i)
            q[i] = p[i];
        *pos = *val;
        v[1] = v[1] + 4;
        return;
    }
    int* begin = (int*)v[0];
    int* end2 = (int*)v[1];
    int oldLen = (int)(end2 - begin);
    int newCap = oldLen ? oldLen * 2 : 1;
    int* dst = newCap ? new int[newCap] : 0;
    int before = (int)(pos - begin);
    for (int i = 0; i < before; ++i)
        dst[i] = begin[i];
    dst[before] = *val;
    for (int i = before; i < oldLen; ++i)
        dst[i + 1] = begin[i];
    if (v[0])
        delete[] begin;
    v[0] = (int)dst;
    v[1] = (int)(dst + oldLen + 1);
    v[2] = (int)(dst + newCap);
}

// @ 0x00eae540
int* FUN_00eae540(int* v, int* other)
{
    if (other == v)
        return v;
    float* src = (float*)other[0];
    float* dst = (float*)v[0];
    float* srcEnd = (float*)other[1];
    unsigned n = (unsigned)(srcEnd - src);
    unsigned cap = (unsigned)((float*)v[2] - dst);
    if (cap < n) {
        float* nw = new float[n];
        float* p = src; float* q = nw;
        while (p != srcEnd) *q++ = *p++;
        if (v[0]) delete[] (float*)v[0];
        v[0] = (int)nw; v[1] = (int)(nw + n); v[2] = (int)(nw + n);
        return v;
    }
    unsigned have = (unsigned)((float*)v[1] - dst);
    if (have < n) {
        float* p = src; float* q = dst;
        while (q != (float*)v[1]) *q++ = *p++;
        float* q2 = (float*)v[1]; float* p2 = (float*)other[0] + have;
        while (p2 != srcEnd) *q2++ = *p2++;
        v[1] = (int)((float*)v[0] + n);
        return v;
    }
    float* p = src; float* q = dst; float* e = (float*)other[1];
    while (p != e) *q++ = *p++;
    v[1] = (int)((float*)v[0] + n);
    return v;
}

// @ 0x00eae8a0
void FUN_00eae8a0(IReader* reader, int* v)
{
    FUN_11e0744_memcpy((void*)v[0], (void*)v[1], 0);
    v[1] += -((int)(v[1] - v[0]) >> 2) * 4;
    int count = 0;
    IStream* s = reader->v20()->s18();
    ReadInt32(s, &count, 1, 0);
    unsigned n = (unsigned)count;
    if ((unsigned)(v[2] - v[0]) >> 2 < n) {
        FUN_11e0744_memcpy((void*)0, (void*)v[0], (unsigned)(v[1] - v[0]));
        int old = v[0];
        v[0] = 0;
        v[1] = ((v[1] - old) >> 2) * 4;
        v[2] = (int)n * 4;
    }
    for (unsigned i = 0; i < n; ++i) {
        IStream* s2 = reader->v20()->s18();
        int val = 0;
        ReadInt32(s2, &val, 1, 0);
        if ((int*)v[1] < (int*)v[2])
            *(int*)v[1] = val, v[1] += 4;
        else
            FUN_00eadf40((int*)v[1], &val);
    }
    reader->v1c();
}

// @ 0x00eaea80
void FUN_00eaea80(IReader* reader, int* v)
{
    FUN_11e0744_memcpy((void*)v[0], (void*)v[1], 0);
    v[1] += -((int)(v[1] - v[0]) >> 2) * 4;
    int count = 0;
    IStream* s = reader->v20()->s18();
    ReadInt32(s, &count, 1, 0);
    FUN_00eade60(count);
    for (unsigned i = 0; i < (unsigned)count; ++i) {
        IStream* s2 = reader->v20()->s18();
        float val = 0.0f;
        ReadInt32(s2, (int*)&val, 1, 0);
        if ((float*)v[1] < (float*)v[2])
            *(float*)v[1] = val, v[1] += 4;
        else
            FUN_00eae430((int*)v, (int*)v[1], (int*)&val);
    }
    reader->v1c();
}

// @ 0x00eaeb60
void FUN_00eaeb60(int* v, int* pos, unsigned n, int* val)
{
    int* end = (int*)v[1];
    unsigned have = (unsigned)(v[2] - (int)end) >> 2;
    if (have < n) {
        VecGrowN(v, pos, n, *val);
        return;
    }
    if (n == 0)
        return;
    int value = *val;
    unsigned tail = (unsigned)(end - pos);
    if (n < tail) {
        int* d = end;
        int* s = end - n;
        while (s != end) *--d = *--s;
        v[1] = v[1] + n * 4;
        int* w = pos;
        unsigned k = n;
        while (k--) *w++ = value;
        return;
    }
    unsigned extra = n - tail;
    int* w = end;
    for (unsigned i = 0; i < extra; ++i)
        *w++ = value;
    v[1] += extra * 4;
    int* s = pos;
    int* d = end;
    while (s != end) *d++ = *s++;
    v[1] += tail * 4;
    int* w2 = pos;
    unsigned k = n;
    while (k--) *w2++ = value;
}

// @ 0x00eaed40
void FUN_00eaed40(int* v, int* pos, unsigned n, float* val)
{
    int* end = (int*)v[1];
    unsigned have = (unsigned)(v[2] - (int)end) >> 2;
    if (have < n) {
        int* begin = (int*)v[0];
        unsigned oldLen = (unsigned)(end - begin) >> 2;
        unsigned newCap = oldLen * 2;
        if (oldLen == 0)
            newCap = 1;
        if (newCap <= oldLen + n)
            newCap = oldLen + n;
        float* dst = newCap ? new float[newCap] : 0;
        unsigned before = (unsigned)(pos - begin) >> 2;
        float* out = dst;
        float* p = (float*)begin;
        for (unsigned i = 0; i < before; ++i) *out++ = *p++;
        float value = *val;
        for (unsigned i = 0; i < n; ++i) *out++ = value;
        while (p != (float*)end) *out++ = *p++;
        if (v[0]) delete[] (float*)v[0];
        v[0] = (int)dst;
        v[1] = (int)out;
        v[2] = (int)(dst + newCap);
        return;
    }
    if (n == 0)
        return;
    float value = *val;
    unsigned tail = (unsigned)(end - pos);
    if (n < tail) {
        int* d = end;
        int* s = end - n;
        while (s != end) *--d = *--s;
        v[1] = v[1] + n * 4;
        float* w = (float*)pos;
        unsigned k = n;
        while (k--) *w++ = value;
        return;
    }
    unsigned extra = n - tail;
    float* w = (float*)end;
    for (unsigned i = 0; i < extra; ++i) *w++ = value;
    v[1] += extra * 4;
    float* s = (float*)pos;
    float* d = (float*)end;
    while (s != (float*)end) *d++ = *s++;
    v[1] += tail * 4;
    float* w2 = (float*)pos;
    unsigned k = n;
    while (k--) *w2++ = value;
}

// @ 0x00eaeef0
void FUN_00eaeef0(int* v, float* first, float* last)
{
    float* begin = (float*)v[0];
    unsigned n = (unsigned)(last - first);
    if ((unsigned)((float*)v[2] - begin) < n) {
        float* nw = new float[n];
        float* p = first; float* q = nw;
        while (p != last) *q++ = *p++;
        if (v[0]) delete[] (float*)v[0];
        v[0] = (int)nw; v[1] = (int)(nw + n); v[2] = (int)(nw + n);
        return;
    }
    unsigned have = (unsigned)((float*)v[1] - begin);
    if (n <= have) {
        float* p = first; float* q = begin;
        while (p != last) *q++ = *p++;
        v[1] = (int)(begin + n);
        return;
    }
    float* mid = first + have;
    float* p = first; float* q = begin;
    while (p != mid) *q++ = *p++;
    float* q2 = (float*)v[1];
    while (mid != last) *q2++ = *mid++;
    v[1] = (int)q2;
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

// @ 0x00eaffc0
void* __cdecl FUN_00eaffc0(void* cont, char* cur, void* cont2, char* last, char* dest)
{
    if (cur == last)
        return dest;
    do
    {
        *(u32*)(dest + 8)    = *(u32*)(cur + 8);
        *(u32*)(dest + 0xc)  = *(u32*)(cur + 0xc);
        *(u32*)(dest + 0x10) = *(u32*)(cur + 0x10);
        *(u32*)(dest + 0x14) = *(u32*)(cur + 0x14);
        *(u32*)(dest + 0x18) = *(u32*)(cur + 0x18);
        FUN_00eae540(dest + 0x1c, 0, cur + 0x1c);
        FUN_00eae540(dest + 0x30, 0, cur + 0x30);
        FUN_00eae540(dest + 0x44, 0, cur + 0x44);
        FUN_00eae540(dest + 0x58, 0, cur + 0x58);
        cur  += 0x6c;
        dest += 0x6c;
        if (cur == *(char**)((char*)cont + 4))
            cur = *(char**)cont;
    } while (cur != last);
    return dest;
}

// @ 0x00eb0050
void __cdecl FUN_00eb0050(void** out, void* sCont, char* sCur, void* sCont2, char* sLast, void* dCont, char* dCur)
{
    if (sCur != sLast)
    {
        do
        {
            *(u32*)(dCur + 8)    = *(u32*)(sCur + 8);
            *(u32*)(dCur + 0xc)  = *(u32*)(sCur + 0xc);
            *(u32*)(dCur + 0x10) = *(u32*)(sCur + 0x10);
            *(u32*)(dCur + 0x14) = *(u32*)(sCur + 0x14);
            *(u32*)(dCur + 0x18) = *(u32*)(sCur + 0x18);
            FUN_00eae540(dCur + 0x1c, 0, sCur + 0x1c);
            FUN_00eae540(dCur + 0x30, 0, sCur + 0x30);
            FUN_00eae540(dCur + 0x44, 0, sCur + 0x44);
            FUN_00eae540(dCur + 0x58, 0, sCur + 0x58);
            dCur += 0x6c;
            if (dCur == *(char**)((char*)dCont + 4))
                dCur = *(char**)dCont;
            sCur += 0x6c;
            if (sCur == *(char**)((char*)sCont + 4))
                sCur = *(char**)sCont;
        } while (sCur != sLast);
    }
    out[1] = dCur;
    out[0] = dCont;
}

// @ 0x00eb0120
void __fastcall FUN_00eb0120(void* self_)
{
    CityMusic* self = (CityMusic*)self_;
    u32 choice = FUN_005e8ec0(self->mRng, (self->mMaxNotes - self->mMinNotes) + 1, self->mWeightHi);
    u32 n      = choice + self->mMinNotes;
    self->mSomeValue = FUN_00a68fb0(self->mRng, 0, (u32)(self->mVec54End - self->mVec54Begin));
    ClearBoolVec((void**)&self->mVecDBegin, (void**)&self->mVecDEnd);
    ClearBoolVec((void**)&self->mVecBBegin, (void**)&self->mVecBEnd);
    ClearBoolVec((void**)&self->mVecEBegin, (void**)&self->mVecEEnd);
    ClearBoolVec((void**)&self->mVecABegin, (void**)&self->mVecAEnd);
    self->mTotalDuration = 0.0f;
    u32 local[3];
    for (u32 k = n; k != 0; --k)
        FUN_00eaf510(self, 0, local);
}

// @ 0x00eb0290
void __fastcall FUN_00eb0290(void* self_, int, u32 n, u32* value)
{
    u32** self = (u32**)self_;
    u32*  begin = self[0];
    if ((u32)(self[2] - begin) >> 2 < n)
    {
        u32 tmp[3];
        FUN_00b93c60(tmp, 0, n, (char*)self_ + 0xc);
        u32 fill = *value;
        u32* nb  = (u32*)tmp[0];
        for (u32 k = n; k != 0; --k)
            *nb++ = fill;
        u32* old = self[0];
        self[0] = (u32*)tmp[0];
        self[1] = (u32*)tmp[0] + n;
        self[2] = (u32*)tmp[2];
        if (old)
            FUN_00f47380(old);
        return;
    }
    u32* end = self[1];
    if ((u32)((char*)end - (char*)begin) >> 2 < n)
    {
        u32 fill = *value;
        for (u32* p = begin; p != end; ++p)
            *p = fill;
        u32 extra = n - (u32)(self[1] - self[0]);
        u32* e = self[1];
        for (u32 k = extra; k != 0; --k)
            *e++ = fill;
        self[1] = self[1] + (n - (u32)(self[1] - self[0]));
        return;
    }
    u32 fill = *value;
    for (u32 k = n; k != 0; --k)
        *begin++ = fill;
    u32* _Src = self[1];
    u32* _Dst = self[0] + n;
    memcpy_(_Dst, _Src, 0);
    s32 delta = -((s32)((char*)_Src - (char*)_Dst) >> 2) * 4;
    self[1] = (u32*)((char*)self[1] + delta);
}

// @ 0x00eb0390
u8 __fastcall FUN_00eb0390(void* self_, int, void* out_)
{
    CityMusic* self = (CityMusic*)self_;
    char*      out  = (char*)out_;
    *(u32*)(out + 0x14) = self->mRandomA;
    *(u32*)(out + 0x18) = self->mRandomB;
    FUN_00eaeef0(out + 0x1c, 0, self->mVecDBegin, self->mVecDEnd, out);
    FUN_00eaeef0(out + 0x30, 0, self->mVecEBegin, self->mVecEEnd, out);
    ClearBoolVec((void**)(out + 0x44), (void**)(out + 0x48));
    char* head  = (char*)self + 0x1b8;
    void* head0 = *(void**)head;
    FUN_00eaefa0(out + 0x44, 0, out + 0x44, head0, head, out);
    FUN_00eaeef0(out + 0x58, 0, self->mVecCBegin, self->mVecCEnd, out);
    return 1;
}

// @ 0x00eb0460
void __fastcall FUN_00eb0460(void* self_)
{
    CityMusic* self = (CityMusic*)self_;
    FUN_00ead1a0(self, 0, 0);
    char* head = (char*)self + 0x1b8;
    for (char* p = *(char**)head; p != head; )
    {
        char* nxt = *(char**)p;
        FUN_00f47380(p);
        p = nxt;
    }
    *(char**)head = head;
    *(char**)(head + 4) = head;
    u32 tmp = 0;
    FUN_00eb1460(&self->mActiveBegin, 0, self->mNumLayers, &tmp);
    self->mNumActive = 0;
    for (u32 i = 0; i < self->mNumLayers; ++i)
    {
        u32 v;
        if (i == 0)
            v = FUN_00a68fb0(self->mRng, 0, self->mNumAmbiences) + 1;
        else
            v = FUN_00a68fb0(self->mRng, 0, self->mNumAmbiences + 1);
        if (v != 0)
        {
            char* e = *(char**)head;
            while (e != head && *(u32*)(e + 8) != v)
                e = *(char**)e;
            if (e == head)
            {
                self->mActiveBegin[i] = v;
                char* node = (char*)FUN_00f473a0(0xc, "Simulator", 0, 0, (const char*)0x13ebb38, 0xd1);
                if (node + 8)
                    *(u32*)(node + 8) = v;
                *(void**)node = head;
                *(void**)(node + 4) = *(void**)(head + 4);
                *(void**)(*(void**)(head + 4)) = node;
                *(void**)(head + 4) = node;
                ++self->mNumActive;
            }
            else
                self->mActiveBegin[i] = 0;
        }
        else
            self->mActiveBegin[i] = 0;
    }
    self->mRandomA = FUN_00a68fb0(self->mRng, 0, self->mNumRhythms) + 1;
    self->mRandomB = FUN_00a68fb0(self->mRng, 0, self->mNumInstruments) + 1;
    FUN_00eb0120(self);
    FUN_00ead1a0(self, 0, 1);
}

// @ 0x00eb05a0
void __fastcall FUN_00eb05a0(void* self_)
{
    CityMusic* self = (CityMusic*)self_;
    if (self->mRandomA > self->mNumRhythms)
        self->mRandomA = FUN_00a68fb0(self->mRng, 0, self->mNumRhythms) + 1;
    if (self->mRandomB > self->mNumInstruments)
        self->mRandomB = FUN_00a68fb0(self->mRng, 0, self->mNumInstruments) + 1;

    u32*   vecB = (u32*)((char*)self + 0x13c);
    u32*   vecA = (u32*)((char*)self + 0x128);
    float* vecE = (float*)((char*)self + 0x1e0);

    u32 dCount = (u32)(self->mVecDEnd - self->mVecDBegin);
    u32 eCount = (u32)(self->mVecEEnd - self->mVecEBegin);
    if (eCount == dCount && dCount != 0)
    {
        FUN_00eb0230(vecB, 0, dCount);
        FUN_00eb0230(vecA, 0, dCount);
        self->mTotalDuration = 0.0f;
        for (u32 i = 0; i < dCount; ++i)
        {
            u32  rem = (self->mVecDBegin[i] - self->mDegreeBase) % 12;
            s32  idx = -1;
            u32* tbl = self->mDegreeTable;
            for (u32 k = 0; k < 7; ++k)
            {
                if (tbl[k] == rem)
                {
                    idx = (s32)k;
                    break;
                }
            }
            vecB[i] = (u32)idx;
            u32 deg = vecB[i];
            u32 v;
            if (deg == 0xffffffffU)
                v = 2;
            else if (i == 0)
                v = 0;
            else
            {
                u32  prev = vecB[i - 1];
                u32* sug  = (u32*)self->mppSuggestions[prev];
                v = (sug[deg] == 0) ? 1 : 0;
            }
            vecA[i] = v;
            self->mTotalDuration += vecE[i];
        }
        if (dCount < self->mMinNotes)
        {
            u32 tmp[3];
            do
            {
                FUN_00eaf510(self, 0, tmp);
                ++dCount;
            } while (dCount < self->mMinNotes);
        }
        if (dCount > self->mMaxNotes)
        {
            do
            {
                --dCount;
                FUN_00eae610(self, 0, dCount);
            } while (dCount > self->mMaxNotes);
        }
    }
    else
        FUN_00eb0120(self);

    char* sent  = (char*)self + 0x1b8;
    u32   count = 0;
    for (char* p = *(char**)sent; p != sent; p = *(char**)p)
        ++count;
    u32 lim = count;
    if (count > self->mNumLayers)
        lim = self->mNumLayers;
    char* cur    = *(char**)sent;
    u32   walked = 0;
    while (cur != sent && walked < lim)
    {
        cur = *(char**)cur;
        ++walked;
    }
    u32 local = 0;
    if (walked == lim)
        FUN_00973d10(sent, 0, cur, &local);
    else
        FUN_00eadab0(sent, 0, lim - walked, &local);

    FUN_00eb0290((char*)self + 0x114, 0, self->mNumLayers, &local);

    self->mNumActive = 0;
    for (char* p = *(char**)sent; p != sent; )
    {
        u32 val = *(u32*)(p + 8);
        if (val > self->mNumAmbiences)
        {
            char* nxt = *(char**)p;
            char* x   = *(char**)(nxt + 4);
            char* xn  = *(char**)(x + 4);
            char* xp  = *(char**)x;
            *(char**)xn = xp;
            *(char**)(xp + 4) = xn;
            FUN_00f47380(x);
            p = nxt;
        }
        else
        {
            u32 i = self->mNumActive;
            self->mNumActive = i + 1;
            (*(u32**)((char*)self + 0x114))[i] = val;
            p = *(char**)p;
        }
    }
    void* ms = FUN_0067dcc0();
    (*(void (__thiscall**)(void*, u32, void*, int))(*(char**)ms + 0x14))(ms, 0x510b72f, self, 0);
}

// @ 0x00eb0810
void* __fastcall FUN_00eb0810(void* vec, int, char* first, char* last)
{
    char* end    = *(char**)((char*)vec + 4);
    char* newEnd = (char*)FUN_00eaf410(last, end, first);
    for (char* p = newEnd; p < end; p += 0x6c)
        (*(void (__thiscall**)(char*, int))(*(char**)p + 8))(p, 0);
    s32 delta = (s32)((first - last) / 0x6c) * 0x6c;
    *(char**)((char*)vec + 4) = end + delta;
    return first;
}

// @ 0x00eb0870
void __fastcall FUN_00eb0870(void* vec_, int, char* pos, u32 count, void* value)
{
    u32** vec   = (u32**)vec_;
    char* begin = (char*)vec[0];
    char* end   = (char*)vec[1];
    char* cap   = (char*)vec[2];
    if (count > (u32)((cap - end) / 0x6c))
    {
        u32   size   = (u32)((end - begin) / 0x6c);
        u32   newCap = size * 2;
        if (size == 0)
            newCap = 1;
        u32 need = size + count;
        if (need < newCap)
            need = newCap;
        char* mem;
        if (need == 0)
            mem = 0;
        else
            mem = (char*)FUN_00f473a0(need * 0x6c, "Simulator", 0, 0, (const char*)0x13ebb38, 0xd1);
        char* a = (char*)FUN_00eaf3d0(begin, pos, mem);
        FUN_00eacfb0(begin, pos, mem);
        FUN_00eaff90(a, count, value);
        a += count * 0x6c;
        char* b = (char*)FUN_00eaf3d0(pos, end, a);
        FUN_00eacfb0(pos, end, a);
        if (begin)
            FUN_00f47380(begin);
        vec[0] = (u32*)mem;
        vec[1] = (u32*)b;
        vec[2] = (u32*)(mem + need * 0x6c);
        return;
    }
    if (count == 0)
        return;
    char local[0x6c];
    FUN_00eaf190(local, 0, value);
    u32 avail = (u32)((end - pos) / 0x6c);
    if (count < avail)
    {
        char  scratch = 0;
        char* m       = end - count * 0x6c;
        FUN_00eaf310(&scratch, m, end, end, &scratch);
        vec[1] = (u32*)(end + count * 0x6c);
        FUN_00eaf490(pos, m, end);
        FUN_00eaf350(pos, m, local);
    }
    else
    {
        FUN_00eaff90(end, count - avail, local);
        vec[1] = (u32*)(end + (count - avail) * 0x6c);
        FUN_00eaf310(local, pos, end, vec[1], local);
        vec[1] = (u32*)((char*)vec[1] + avail * 0x6c);
        FUN_00eaf350(pos, end, local);
    }
    FUN_00ead6a0(local);
}

// @ 0x00eb0a60
bool cPlayerCityMusic_s00ea_ffc0::Read(int stream)
{
    if (m10c != 0)
        Reset(0);

    m198.clear();
    m1b8.clear();
    m1cc.clear();
    m1e0.clear();

    char buf[0xa14];
    CVarListSerializer* ser = (CVarListSerializer*)buf;
    ser->ctor(this, (void*)0x15a9198, 0x1a80d26);
    bool ok = ser->Serialize((void*)stream);
    FUN_00eb05a0();
    if (m10c != 0)
        Reset(1);
    return ok;
}

// @ 0x00eb0b70
u8 __fastcall FUN_00eb0b70(void* self_, int, void* in_)
{
    CityMusic* self = (CityMusic*)self_;
    char*      in   = (char*)in_;
    FUN_00ead1a0(self, 0, 0);
    self->mRandomA = *(u32*)(in + 0x14);
    self->mRandomB = *(u32*)(in + 0x18);
    FUN_00eaeef0((char*)self + 0x1cc, 0, *(void**)(in + 0x1c), *(void**)(in + 0x20), in);
    FUN_00eaeef0((char*)self + 0x1e0, 0, *(void**)(in + 0x30), *(void**)(in + 0x34), in);
    FUN_00eadee0((char*)self + 0x1b8, 0, *(void**)(in + 0x44), *(void**)(in + 0x48), in);
    if ((((*(u32*)(in + 0x5c) - *(u32*)(in + 0x58)) ^
          (*(u32*)((char*)self + 0x19c) - *(u32*)((char*)self + 0x198))) & 0xfffffffcU) == 0)
        FUN_00da1e70(*(void**)(in + 0x58), *(void**)(in + 0x5c), in);
    FUN_00eb05a0(self);
    FUN_00ead1a0(self, 0, 1);
    return 1;
}

// @ 0x00eb0c30
void __fastcall FUN_00eb0c30(void* self_)
{
    CityMusic* self = (CityMusic*)self_;
    if (*(u32*)((char*)self + 0xec) == *(u32*)((char*)self + 0xfc))
        return;
    u32* p = *(u32**)((char*)self + 0xf8);
    if (*(u32*)((char*)self + 0xfc) == p[0])
        *(u32*)((char*)self + 0xfc) = p[1];
    *(u32*)((char*)self + 0xfc) -= 0x6c;
    FUN_00eb0b70(self, 0, *(void**)((char*)self + 0xfc));
}

// @ 0x00eb0c70
void __fastcall FUN_00eb0c70(void* self_)
{
    CityMusic* self = (CityMusic*)self_;
    if (*(u32*)((char*)self + 0xf0) == *(u32*)((char*)self + 0xfc))
        return;
    u32* p = *(u32**)((char*)self + 0xf8);
    *(u32*)((char*)self + 0xfc) += 0x6c;
    if (*(u32*)((char*)self + 0xfc) == p[1])
        *(u32*)((char*)self + 0xfc) = p[0];
    FUN_00eb0b70(self, 0, *(void**)((char*)self + 0xfc));
}

// @ 0x00eb0cb0
void __fastcall FUN_00eb0cb0(void* self_, int, void** out, void* dCont, char* dCur, void* sCont, char* sCur)
{
    u32** self = (u32**)self_;
    u32   count = 0;
    if (dCur != sCur)
    {
        char* p = dCur;
        do
        {
            p += 0x6c;
            ++count;
            if (p == *(char**)((char*)dCont + 4))
                p = *(char**)dCont;
        } while (p != sCur);
    }
    char local[8];
    FUN_00eb0050((void**)local, sCont, sCur, self, (char*)self[6], dCont, dCur);
    if (count != 0)
    {
        char* p = (char*)self[6];
        u32   n = (u32)self[7];
        do
        {
            --count;
            if (p == (char*)self[0])
                p = (char*)self[1];
            p -= 0x6c;
            --n;
        } while (count != 0);
        self[6] = (u32*)p;
        self[7] = (u32*)n;
    }
    out[0] = dCont;
    out[1] = dCur;
}

// @ 0x00eb0d60
void __fastcall FUN_00eb0d60(void* vec_, int, u32 n)
{
    u32** vec   = (u32**)vec_;
    char* begin = (char*)vec[0];
    char* end   = (char*)vec[1];
    if (n > (u32)((end - begin) / 0x6c))
    {
        char local[0x6c];
        FUN_00eb1d70(local);
        u32 size = (u32)(((char*)vec[1] - (char*)vec[0]) / 0x6c);
        FUN_00eb0870(vec, 0, (char*)vec[1], n - size, local);
        FUN_00ead6a0(local);
        return;
    }
    FUN_00eb0810(vec, 0, begin + n * 0x6c, end);
}

// @ 0x00eb0df0
void __fastcall FUN_00eb0df0(void* self_, int, u32 n)
{
    u32** self = (u32**)self_;
    u32   cap  = (u32)(((char*)self[1] - (char*)self[0]) / 0x6c);
    if (cap - 1 < n)
    {
        u32* local[3] = {0, 0, 0};
        FUN_00eb0d60(local, 0, n + 1);
        FUN_00eaffc0(self, (char*)self[5], self, (char*)self[6], (char*)local[0]);
        u32* n0 = local[0];
        u32* n1 = local[1];
        u32* n2 = local[2];
        u32* o0 = self[0];
        u32* o1 = self[1];
        u32* o2 = self[2];
        self[0] = n0;
        self[1] = n1;
        self[2] = n2;
        self[5] = self[0];
        self[6] = (u32*)((char*)self[0] + (u32)self[7] * 0x6c);
        local[0] = o0;
        local[1] = o1;
        local[2] = o2;
        FUN_00ead660(local);
    }
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

// @ 0x01387660
namespace Simulator {
void InitMusicDataAttributes()
{
    ADD_MUSIC(0, "mName", 0x511dfb9, 0x178, Read_00ac87c0, Write_00ac87f0, ReadText_00694c80, WriteText_00694c10, AlwaysValid<int>, ToXml_00acbbc0)
    ADD_MUSIC(1, "mDescription", 0x511dfc3, 0x188, Read_00ac87c0, Write_00ac87f0, ReadText_00694c80, WriteText_00694c10, AlwaysValid<int>, ToXml_00acbbc0)
    ADD_MUSIC(2, "mVolumes", 0x4d81cfe, 0x198, Read_00eae8a0, Write_00f26ca0, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<int>, ToXml_0103c3a0)
    ADD_MUSIC(3, "mAmbienceHistory", 0x4226180, 0x1b8, Read_00c33820, Write_00c332a0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00c31ca0, ToXml_00eafcf0)
    ADD_MUSIC(4, "mRhythm", 0x4226186, 0x1c4, INT_ATTR)
    ADD_MUSIC(5, "mInstrument", 0x4226189, 0x1c8, INT_ATTR)
    ADD_MUSIC(6, "mNotePitches", 0x4e551ee, 0x1cc, Read_00eae9b0, Write_00c761c0, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<int>, ToXml_00eafe40)
    ADD_MUSIC(7, "mNoteDurations", 0x4f7c02d, 0x1e0, Read_00eaea80, Write_00f26ca0, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<int>, ToXml_0103c3a0)
}
}  // namespace Simulator
