// src/game/SPCreatureAnim/gait_record.cpp -- migrated from slice(s) s009e4450, s009e3580, s009e2490, s009e1df0, s009e0d90, s009dfc40, s009dd6a0, s009db6d0, s009e5070, s009de8b0 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/gait_record.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/ArgScript/cIBlockCommand.h"
#include "EA/ArgScript/cICommand.h"
#include <math.h>
#include <string.h>
#include "nSPCreatureAnim/gait_record.h"
#include "nSPCreatureAnim/gait_record_static_data.h"

// ---- items of slice s009de8b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char kAllocatorFile[];                                // 0x013ebb38
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                            // 0x00f473a0
namespace EA {
namespace ArgScript {
struct cIParser_s009d_e8b0;
}
}
namespace EA {
namespace ArgScript {
struct cState_s009d_e8b0;
}
}
namespace EA {
namespace ArgScript {
struct cArguments_s009d_e8b0;
}
}
namespace EA {
namespace ArgScript {
class cICommand_s009d_e8b0 { public:
    virtual int AddRef();
    virtual int Release();
    virtual void* Cast(uint32_t type);
    virtual void ParseLine(void* line);
    virtual void Execute(cArguments_s009d_e8b0& args);
};
}
}
namespace EA {
namespace ArgScript {
class cCommandBase_s009d_e8b0 : public cICommand_s009d_e8b0 { public:
    cIParser_s009d_e8b0* mParser;                          // +0x04
    int mRefCount;                              // +0x08
    cCommandBase_s009d_e8b0();                             // 0x0083c800
};
}
}
namespace EA {
namespace ArgScript {
class cIBlockCommand_s009d_e8b0 : public cICommand_s009d_e8b0 { public:
    virtual cState_s009d_e8b0* GetChildState();            // +0x14
};
}
}
namespace EA {
namespace ArgScript {
class cBlockCommandBase : public cIBlockCommand_s009d_e8b0 { public:
    cIParser_s009d_e8b0* mParser;                          // +0x04
    int mRefCount;                              // +0x08
    cState_s009d_e8b0* mChildState;                        // +0x0c
    uint32_t mCommands[8];                      // +0x10 hash_map<string, cICommand*>
    void OnRegister(cIParser_s009d_e8b0* parser, cState_s009d_e8b0* state);   // 0x0083c780
    virtual void AddCommand(const char* keyword, cICommand_s009d_e8b0* command);   // +0x18
};
}
}
namespace EA {
namespace ArgScript {
template <typename T, typename Base> struct cCommandStateT_s009d_e8b0 : Base {
    T* mState;                                  // block: +0x30, command: +0x0c
    cCommandStateT_s009d_e8b0() {}
};
}
}
namespace EA {
namespace ArgScript {
template <typename T> class cCommandT : public cCommandStateT_s009d_e8b0<T, cCommandBase_s009d_e8b0> { public:
    cCommandT() {}
};
}
}
namespace EA {
namespace ArgScript {
template <typename T> class cBlockCommandT : public cCommandStateT_s009d_e8b0<T, cBlockCommandBase> { public:
    cBlockCommandT() {}
};
}
}
using EA::ArgScript::cIParser_s009d_e8b0;
using EA::ArgScript::cState_s009d_e8b0;
using EA::ArgScript::cArguments_s009d_e8b0;
namespace {

struct cGaitKeyState;                           // the gait key being parsed (the parser's state object)

struct cGaitKeyBlockCommand : EA::ArgScript::cBlockCommandT<cGaitKeyState> {
    void OnRegister(cIParser_s009d_e8b0* parser, cState_s009d_e8b0* state);
};

// One sub-command class per gait key field; each only overrides Execute.
#define GAIT_KEY_COMMAND(Name)                                                           \
    struct c##Name##Command : EA::ArgScript::cCommandT<cGaitKeyBlockCommand> {          \
        c##Name##Command() {}                                                            \
        virtual void Execute(cArguments_s009d_e8b0& args);                                          \
    };

GAIT_KEY_COMMAND(SpeedI)
GAIT_KEY_COMMAND(StepHeight)
GAIT_KEY_COMMAND(NumFeet)
GAIT_KEY_COMMAND(Taxon)
GAIT_KEY_COMMAND(Trigger)
GAIT_KEY_COMMAND(DutyFactor)
GAIT_KEY_COMMAND(NumPaths)
GAIT_KEY_COMMAND(NumPathPosKeys)
GAIT_KEY_COMMAND(NumPathRotKeys)
GAIT_KEY_COMMAND(NumPathBndKeys)
GAIT_KEY_COMMAND(Tick)
GAIT_KEY_COMMAND(Pos)
GAIT_KEY_COMMAND(Rot)
GAIT_KEY_COMMAND(Bnd)
GAIT_KEY_COMMAND(Spl)
GAIT_KEY_COMMAND(TanFl)
GAIT_KEY_COMMAND(HerFl)
GAIT_KEY_COMMAND(StepGallop)
GAIT_KEY_COMMAND(StepPhaseBiasH)
GAIT_KEY_COMMAND(StepPhaseBiasV)
GAIT_KEY_COMMAND(StepSkew)
GAIT_KEY_COMMAND(FootTilt)
GAIT_KEY_COMMAND(TiltPoint)
GAIT_KEY_COMMAND(ToeCurlMax)
GAIT_KEY_COMMAND(ToeCurlBegin)
GAIT_KEY_COMMAND(ToeCurlEnd)
GAIT_KEY_COMMAND(SwayAmplitude)
GAIT_KEY_COMMAND(SwayPhase)
GAIT_KEY_COMMAND(TrackWidthReduction)
GAIT_KEY_COMMAND(VerticalPhaseOffset)
GAIT_KEY_COMMAND(SagittalPhaseOffset)
GAIT_KEY_COMMAND(LateralPhaseOffset)
GAIT_KEY_COMMAND(MaxVerticalOffset)
GAIT_KEY_COMMAND(VerticalDist)
GAIT_KEY_COMMAND(WalkRunShape)
GAIT_KEY_COMMAND(MaxSagittalOffset)
GAIT_KEY_COMMAND(MaxLateralOffset)
GAIT_KEY_COMMAND(YawPhaseOffset)
GAIT_KEY_COMMAND(PitchPhaseOffset)
GAIT_KEY_COMMAND(RollPhaseOffset)
GAIT_KEY_COMMAND(MaxYawAngle)
GAIT_KEY_COMMAND(MaxPitchAngle)
GAIT_KEY_COMMAND(MaxRollAngle)

// Same block/field-command split for the shorter "steplength" tuning file; only OnRegister is
// reproduced here.
struct cStepLengthKeyBlockCommand : EA::ArgScript::cBlockCommandT<cGaitKeyState> {
    void OnRegister(cIParser_s009d_e8b0* parser, cState_s009d_e8b0* state);
};

struct cStepLengthCommand : EA::ArgScript::cCommandT<cStepLengthKeyBlockCommand> {
    cStepLengthCommand() {}
    virtual void Execute(cArguments_s009d_e8b0& args);
};

}  // namespace
namespace GaitKeywords {
extern const char* bnd;                     // 0x0155152c "bnd"
}
namespace GaitKeywords {
extern const char* dutyfactor;              // 0x01551530 "dutyfactor"
}
namespace GaitKeywords {
extern const char* foottilt;                // 0x01551534 "foottilt"
}
namespace GaitKeywords {
extern const char* herfl;                   // 0x01551538 "herfl"
}
namespace GaitKeywords {
extern const char* lateralphaseoffset;      // 0x0155153c
}
namespace GaitKeywords {
extern const char* maxlateraloffset;        // 0x01551540
}
namespace GaitKeywords {
extern const char* maxpitchangle;           // 0x01551544
}
namespace GaitKeywords {
extern const char* maxrollangle;            // 0x01551548
}
namespace GaitKeywords {
extern const char* maxsagittaloffset;       // 0x0155154c
}
namespace GaitKeywords {
extern const char* maxverticaloffset;       // 0x01551550
}
namespace GaitKeywords {
extern const char* maxyawangle;             // 0x01551554
}
namespace GaitKeywords {
extern const char* numfeet;                 // 0x01551558
}
namespace GaitKeywords {
extern const char* numpathbndkeys;          // 0x0155155c
}
namespace GaitKeywords {
extern const char* numpathposkeys;          // 0x01551560
}
namespace GaitKeywords {
extern const char* numpathrotkeys;          // 0x01551564
}
namespace GaitKeywords {
extern const char* numpaths;                // 0x01551568
}
namespace GaitKeywords {
extern const char* pitchphaseoffset;        // 0x0155156c
}
namespace GaitKeywords {
extern const char* pos;                     // 0x01551570
}
namespace GaitKeywords {
extern const char* rollphaseoffset;         // 0x01551574
}
namespace GaitKeywords {
extern const char* rot;                     // 0x01551578
}
namespace GaitKeywords {
extern const char* sagittalphaseoffset;     // 0x0155157c
}
namespace GaitKeywords {
extern const char* speedi;                  // 0x01551580
}
namespace GaitKeywords {
extern const char* spl;                     // 0x01551584
}
namespace GaitKeywords {
extern const char* stepgallop;              // 0x01551588
}
namespace GaitKeywords {
extern const char* stepheight;              // 0x0155158c
}
namespace GaitKeywords {
extern const char* steplength;              // 0x01551590
}
namespace GaitKeywords {
extern const char* stepphasebiash;          // 0x01551594
}
namespace GaitKeywords {
extern const char* stepphasebiasv;          // 0x01551598
}
namespace GaitKeywords {
extern const char* stepskew;                // 0x0155159c
}
namespace GaitKeywords {
extern const char* swayAmplitude;           // 0x015515a0
}
namespace GaitKeywords {
extern const char* swayPhase;               // 0x015515a4
}
namespace GaitKeywords {
extern const char* tanfl;                   // 0x015515a8
}
namespace GaitKeywords {
extern const char* taxon;                   // 0x015515ac
}
namespace GaitKeywords {
extern const char* tic;                     // 0x015515b0
}
namespace GaitKeywords {
extern const char* tiltpoint;               // 0x015515b4
}
namespace GaitKeywords {
extern const char* toecurlbegin;            // 0x015515b8
}
namespace GaitKeywords {
extern const char* toecurlend;              // 0x015515bc
}
namespace GaitKeywords {
extern const char* toecurlmax;              // 0x015515c0
}
namespace GaitKeywords {
extern const char* trackWidthReduction;     // 0x015515c4
}
namespace GaitKeywords {
extern const char* trigger;                 // 0x015515c8
}
namespace GaitKeywords {
extern const char* verticaldist;            // 0x015515cc
}
namespace GaitKeywords {
extern const char* verticalphaseoffset;     // 0x015515d0
}
namespace GaitKeywords {
extern const char* walkrunshape;            // 0x015515d4
}
namespace GaitKeywords {
extern const char* yawphaseoffset;          // 0x015515d8
}
struct GaitA_s009d_e8b0     { uint8_t mData[0x44]; };      // 0x44
struct GaitC_s009d_e8b0     { uint8_t mData[0x1c]; };      // 0x1c
struct GaitItem  { uint8_t mData[0x0c]; };      // 0x0c
struct AnalysisInfo { uint32_t mA, mB, mC; };    // 0x0c
void CopyGaitA(GaitA_s009d_e8b0* first, GaitA_s009d_e8b0* last, GaitA_s009d_e8b0* result);           // 0x009dc0f0
void CopyGaitC(GaitC_s009d_e8b0* first, GaitC_s009d_e8b0* last, GaitC_s009d_e8b0* result);           // 0x009dc1d0
void CopyGaitItem(GaitItem* first, GaitItem* last, GaitItem* result);   // 0x009dc300
void CopyConstructGaitA(void* outEnd, GaitA_s009d_e8b0* first, GaitA_s009d_e8b0* last, GaitA_s009d_e8b0* dst, int n);   // 0x009dd530
void CopyConstructInfo(void* outEnd, AnalysisInfo* first, AnalysisInfo* last,
                       AnalysisInfo* dst, int tag);                 // 0x00898b80
void CopyInfo(AnalysisInfo* first, AnalysisInfo* last, AnalysisInfo* result);  // 0x00b84c80
void FreeMemory(void* p);                                          // 0x00f47380 (operator delete)
template <typename T> struct Vec_s009d_e8b0 {
    T* mpBegin;          // +0x00
    T* mpEnd;            // +0x04
    T* mpEndOfStorage;   // +0x08

    int size() const { return (int)(mpEnd - mpBegin); }
    unsigned int capacity() const { return (unsigned int)(mpEndOfStorage - mpBegin); }

    void reserve(int n);
    T* allocate_copy(int n, T* first, T* last);
    Vec_s009d_e8b0(unsigned int n, const T& value, int unused = 0);
    Vec_s009d_e8b0& operator=(const Vec_s009d_e8b0& other);
};
template <> AnalysisInfo* Vec_s009d_e8b0<AnalysisInfo>::allocate_copy(int n, AnalysisInfo* first,
                                                          AnalysisInfo* last)
{
    AnalysisInfo* p = n ? (AnalysisInfo*)operator new(n * sizeof(AnalysisInfo),
                                                     "Anim/gait/untagged", 0, 0,
                                                     kAllocatorFile, 0xd1) : 0;
    CopyConstructInfo(&n, first, last, p, n);
    return p;
}
// ---- items of slice s009de8b0 end

// ---- items of slice s009e5070 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_AssignGaits;   // 0x015515dc
inline void* operator new(unsigned, void* p) { return p; }
void operator delete[](void*);   // 0x00f47380
struct Slot {            // 16 bytes
    float a, b;
    bool c, d;
    short e;
    int pad;
};
struct IdBase { int id; };
struct GaitA : IdBase {  // 0x44, vtable 0x01447cc0
    virtual void f0();
    float x, y, z;
    Slot s[3];
};
struct GaitB : IdBase {  // 0x58, vtable 0x01447cc4
    virtual void f0();
    float a, b, c, d;
    Slot s[4];
};
struct GaitCData {       // copied as one block of dwords
    float x, y, z;
    bool c0, c1;
    short c2;
    int pad;
};
struct GaitC : IdBase {  // 0x1c, vtable 0x01447cc8
    virtual void f0();
    GaitCData d;
};
struct Item { float a, b; int c; };   // 12 bytes
template <class T>
struct Vec {             // 0x14 bytes: begin/end/cap + 8-byte allocator
    T* b;
    T* e;
    T* cap;
    int alloc[2];
    Vec() : b(0), e(0), cap(0) {}
    ~Vec() { if (b && ((int*)b)[-1]) operator delete[](b); }
    void realloc_insert(T* pos, const T& v);   // per-instance addresses: symbols/slices/s009e2490.txt
    void reserve(int n);
    void assign(const Vec& o);
    void destroy(T* first, T* last);
    void push_back(const T& v) {
        if (e < cap) { T* p = e++; ::new((void*)p) T(v); }
        else realloc_insert(e, v);
    }
};
struct Gait {            // 0x40
    int id;
    Vec<GaitA> a;
    Vec<GaitB> b;
    Vec<GaitC> c;
    Gait();   // 0x009e1030
    Gait(const Gait& o) : id(o.id) { a.assign(o.a); b.assign(o.b); c.assign(o.c); }
};
template <> inline Vec<Gait>::~Vec() { destroy(b, e); if (b && ((int*)b)[-1]) operator delete[](b); }
struct Inner {           // 0xa0
    int f0;
    float f4;
    int f8;
    Vec<Item> items;     // +0x0c
    Vec<Gait> gaits;     // +0x20
    float p[26];         // +0x34
    bool flag;           // +0x9c
    Inner();                                 // 0x009e1df0
    __declspec(noinline) void __thiscall Assign(const Inner* o);   // 0x009dbc60 scalars (body below: lets cl see ecx survive)
    void __thiscall AssignItems(const Inner* o);   // 0x009e1370 items list
    void __thiscall AssignGaits(const Inner* o);   // 0x009e22f0 gaits list (only if g_AssignGaits)
};
void __thiscall Inner::Assign(const Inner* o)
{
    f0 = o->f0;
    f4 = o->f4;
    f8 = o->f8;
    for (int i = 0; i < 26; i++) p[i] = o->p[i];
    flag = o->flag;
}
struct Entry {           // 0xa4
    float key;
    Inner in;
};
struct EntryArr {        // at Table+0x18
    unsigned count;
    Vec<Entry> v;
    void __thiscall Insert(const Entry* e);   // 0x009e4a00
};
struct Src {             // flat resource header
    char pad[0x10];
    int n10;
    unsigned count;      // +0x14
    // records follow at +0x18 + n10 * 8
};
struct RItem { float a, b; };
struct Rec {             // flat input record (variable length)
    float key;           // +0
    float f4;
    int f8;
    float p[26];         // +0x0c
    unsigned nItems;     // +0x74
    unsigned nGaits;     // +0x78
    RItem items[1];      // +0x7c
};
struct GRec {            // flat nested gait header, followed by nA GaitA, nB GaitB, nC GaitC
    unsigned nA, nB, nC;
};
struct Table {
    char pad[0x18];
    EntryArr arr;        // +0x18
    void __thiscall Load(const Src* s);   // 0x009e5070
};
// ---- items of slice s009e5070 end

// ---- items of slice s009db6d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_skipScalars;
typedef unsigned int uint32;
float __cdecl sub_9B3C10(float a, float b);                       // 0x009b3c10
struct ValPath;
struct Val3 {               // 0x0c -- one interpolated sample
    float x;                // +0x00
    float y;                // +0x04
    int z;                  // +0x08
};
void __stdcall SampleAt(Val3* out, uint32 index, const ValPath* a, float t, const ValPath* b);
struct Val3b {              // 0x0c -- an (x, y, flag) triple
    float x;                // +0x00
    float y;                // +0x04
    char flag;              // +0x08
};
struct ValPath {            // 3-float value list
    char pad0[0x0c];
    Val3* begin;            // +0x0c
    Val3* end;              // +0x10
};
struct Inner_s009d_b6d0 {
    int f00;                // +0x00
    float f04;              // +0x04
    int f08;                // +0x08
    char skip[0x28];        // +0x0c .. +0x33 (not part of either copy)
    float f34;              // +0x34
    float f38;
    float f3c;
    float f40;
    float f44;
    float f48;
    float f4c;
    float f50;
    float f54;
    float f58;
    float f5c;
    float f60;
    float f64;
    float f68;
    float f6c;
    float f70;
    float f74;
    float f78;
    float f7c;
    float f80;
    float f84;
    float f88;
    float f8c;
    float f90;
    float f94;
    float f98;
    char f9c;               // +0x9c
    void Assign(const Inner_s009d_b6d0* src);
    void CopyMasked(const Inner_s009d_b6d0* src, uint32 mask);
};
struct Rec44 {              // 0x44
    void* vtbl;             // +0x00
    int ref;                // +0x04
    float x, y, z;          // +0x08
    int d[12];              // +0x14
    Rec44* Ctor(const Rec44* src);
    Rec44* Assign(const Rec44* src);
};
struct Rec58 {              // 0x58
    void* vtbl;             // +0x00
    int ref;                // +0x04
    float x, y, z, w;       // +0x08 .. +0x14
    int d[16];              // +0x18
    Rec58* Ctor(const Rec58* src);
    Rec58* Assign(const Rec58* src);
};
struct Rec1C {              // 0x1c
    void* vtbl;             // +0x00
    int ref;                // +0x04
    int d[5];               // +0x08
    Rec1C* Ctor(const Rec1C* src);
};
struct GaitC_s009d_b6d0 {              // 0x1c, copied without its vtable slot
    void* vtbl;             // +0x00
    int ref;                // +0x04
    float t;                // +0x08
    int d[4];               // +0x0c
};
struct Sample {             // 0x0c
    float t;                // +0x00
    float v;                // +0x04
    float d;                // +0x08
};
struct CurveOut {
    float v;                // +0x00
    union {
        float d;            // +0x04 sample value stored on the fallback path
        bool exact;         // +0x04 low byte overwritten by the equality flag
    };
};
struct Curve {
    int count;              // +0x00
    Sample* samples;        // +0x04
    void Eval(float t, CurveOut* out);
};
// ---- items of slice s009db6d0 end

// ---- items of slice s009dd6a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl operator_delete__(void* p);      // 0x00f47380
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef int            i32;
extern "C" void* __cdecl operator_new(u32 size, const char* name, int a, int b, int c, int d); // 0x00f473a0 EAAllocate wrapper
namespace {

struct cArguments;                                        // EA::ArgScript::cArguments
struct Curve760 { void CopyInto(char* dst); };            // 0x009dc760
struct Track2;                                            // this type

void  FUN_009dc760(Curve760* c, char* dst);               // 0x009dc760  CopyInto
i32   Track2_TotalItems(Track2* t);                       // 0x009dc6a0  Track2::TotalItems
void  FUN_009dd780(Track2* t, void* p);                   // 0x009dd780  (defined below)
i32   FUN_009dd6a0(Track2* t);                            // 0x009dd6a0  (defined below)

// The ArgScript argument block.  MainArguments returns the raw 32-bit argument array.
struct cArguments {
    u32* MainArguments(int n);                            // 0x00838320
};

// The evaluated float object: picks the +0x98 vtable slot (a thiscall returning float).
struct FloatEval {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
    virtual float Eval(i32 v);                // +0x98
};

// A Track2 block descriptor (0xa4 bytes).  Only the touched members are named.
struct Block {
    u8  pad00[0x0c];
    i32 mHitTest;            // +0x0c  (0xffffffff = empty slot)
    i32 mPointsBegin;        // +0x10
    i32 mPointsEnd;          // +0x14
    u8  pad18[0x08];
    i32 mIdsBegin;           // +0x20
    i32 mIdsEnd;             // +0x24
    i32 mGroupsBegin;        // +0x28
    u32 mGroupsEnd;          // +0x2c
    u8  pad30[0x08];
    float mTime;             // +0x38
    float mCone[7];          // +0x3c .. +0x57
    u8  pad58[0x4c];
};

// The Track2 object.  `mBlockCount`/`mBlocks` prefix an inline data region; the walk uses
// 0xa4-byte strides.
struct Track2 {
    u8  pad00[0x18];
    u32 mCount;              // +0x18
    Block* mBlocks;          // +0x1c

    void Grids(void* p);                              // 0x009dd780
    i32  ItemCount();                                 // 0x009dd6a0
    i32  TotalItems();                                // 0x009dc6a0
};

// The evaluated-argument host: self+0xc is the track2/block owner chain, self+4 is the
// float-evaluator object whose +0x98 vtable slot converts script tokens to float.
struct Self {
    u8  pad00[0x04];
    FloatEval* mEval;        // +0x04
    u8  pad08[0x04];
    i32 mOwner;              // +0x0c

    void Cmd3(cArguments* a);                         // 0x009ddca0
    void Cmd4(cArguments* a);                         // 0x009ddcf0
    void CmdTable8(cArguments* a);                    // 0x009ddd70
    void CmdTable16(cArguments* a);                   // 0x009ddf80
};

}  // (anonymous)
// ---- items of slice s009dd6a0 end

// ---- items of slice s009dfc40 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char uint8;
struct Elem0C;      // 0x0c
struct Elem0CS;     // 0x0c
struct Elem1C;      // 0x1c
struct Elem14;      // 0x14
struct Elem44;      // 0x44
struct Elem58;      // 0x58
struct Elem40;      // 0x40
struct ElemA4;      // 0xa4
void  CopyA(Elem44* first, Elem44* last, Elem44* result);             // 0x009dc230
void  CopyB(Elem58* first, Elem58* last, Elem58* result);             // 0x009dc270
void  CopyC(Elem1C* first, Elem1C* last, Elem1C* result);             // 0x009dc2b0
void UninitCopyBackA(void** out, Elem44* first, Elem44* last, Elem44* dstEnd, Elem44* dst);  // 0x009dd530
void UninitCopyBackC(void** out, Elem1C* first, Elem1C* last, Elem1C* dstEnd, Elem1C* dst);  // 0x009dd630
void*   Fill0C(Elem0C* first, Elem0C* last, const Elem0C* value);     // 0x00a177f0
void*   FillN0C(Elem0C* first, uint32 n, const Elem0C* value);        // 0x006e5760
void*   FillN0Cb(Elem0C* first, uint32 n, const Elem0C* value);       // 0x00cca0e0
struct Elem0C {                                                       // size 0x0c
    float x, y, z;
};
struct Elem0CS {                                                      // size 0x0c
    float a, b;
    uint8 c;
};
struct Elem1C : IdBase {                                              // size 0x1c
    virtual void _never_called();
    float  f08;                        // +0x08
    uint32 f0c, f10, f14, f18;         // +0x0c .. +0x1c
    void    CopyFrom(const Elem1C& o); // 0x009dbed0 ret 4
    Elem1C& operator=(const Elem1C& o)
    {
        id  = ((IdBase*)&o)->id;
        f08 = o.f08;
        f0c = o.f0c;
        f10 = o.f10;
        f14 = o.f14;
        f18 = o.f18;
        return *this;
    }
};
struct Elem14 {                                                       // size 0x14 (opaque here)
    uint32 w[5];
};
struct Elem44 {                                                       // size 0x44
    uint32 w[0x11];
    void    CopyFrom(const Elem44& o);      // 0x009dbe30 ret 4 (copy-constructs *this)
    Elem44& operator=(const Elem44& o);     // 0x009dbfd0 ret 4
};
struct Elem58 {                                                       // size 0x58
    uint32 w[0x16];
    void    CopyFrom(const Elem58& o);      // 0x009dbe80 ret 4
    Elem58& operator=(const Elem58& o);     // 0x009dc050 ret 4
};
struct Vec44 {                                                          // element 0x44
    Elem44* mpBegin; Elem44* mpEnd; Elem44* mpCapacity; uint32 mPad[2];
    Vec44& operator=(const Vec44& x);                                  // 0x009dfda0 ret 4
    void   DoInsertValue(Elem44* position, const Elem44& value);       // 0x009e0110 ret 8
    void   clear();                                                    // 0x009e0940
    Elem44* DoAllocate(uint32 n, Elem44* first, Elem44* last);         // 0x009df6e0 ret 0xc
};
struct Vec58 {                                                          // element 0x58
    Elem58* mpBegin; Elem58* mpEnd; Elem58* mpCapacity; uint32 mPad[2];
    void   DoInsertValue(Elem58* position, const Elem58& value);       // 0x009e0230 ret 8
    void   clear();                                                    // 0x009e0980
    Elem58* DoAllocate(uint32 n, Elem58* first, Elem58* last);         // 0x009df740 ret 0xc
};
struct Vec1C {                                                          // element 0x1c
    Elem1C* mpBegin; Elem1C* mpEnd; Elem1C* mpCapacity; uint32 mPad[2];
    Vec1C& operator=(const Vec1C& x);                                  // 0x009dffe0 ret 4
    void   DoInsertValue(Elem1C* position, const Elem1C& value);       // 0x009e0330 ret 8
    void   clear();                                                    // 0x009e09c0
    Elem1C* DoAllocate(uint32 n, Elem1C* first, Elem1C* last);         // 0x009df7a0 ret 0xc
};
struct Vec14 {                                                          // element 0x14
    Elem14* mpBegin; Elem14* mpEnd; Elem14* mpCapacity; uint32 mPad[2];
    Vec14& operator=(const Vec14& x);                                  // 0x009dfec0 ret 4
};
struct Elem40 {                                                         // size 0x40
    uint32 id;                         // +0x00
    Vec44  v04;                        // +0x04
    Vec14  v18;                        // +0x18
    Vec1C  v2c;                        // +0x2c
    Elem40& operator=(const Elem40& o)
    {
        if (this != &o) {
            id = o.id;
            v04 = o.v04;
            v18 = o.v18;
            v2c = o.v2c;
        }
        return *this;
    }
};
struct Vec40 {                                                          // element 0x40
    Elem40* mpBegin; Elem40* mpEnd; Elem40* mpCapacity; uint32 mPad[2];
    void DestroyRange(Elem40* first, Elem40* last);                    // 0x009de770 ret 8
};
struct Vec0C {                                                          // element 0x0c
    Elem0C* mpBegin; Elem0C* mpEnd; Elem0C* mpCapacity; uint32 mPad[2];
    Elem0C* erase(Elem0C* first, Elem0C* last);                        // 0x009e0480 ret 8
    void    DoInsertValue(Elem0C* position, const Elem0C& value);      // 0x009e04e0 ret 8
    void    resize(uint32 n, const Elem0C& value);                     // 0x009e0a00 ret 8
    void    Construct(uint32 n, const Elem0C* value, void* alloc);     // 0x009df8b0 ret 0xc
    void    Swap(Vec0C& o);                                            // 0x009e0610 ret 4
};
struct Vec0CS {                                                         // element 0x0c
    Elem0CS* mpBegin; Elem0CS* mpEnd; Elem0CS* mpCapacity; uint32 mPad[2];
    void     DoInsertValue(Elem0CS* position, const Elem0CS& value);   // 0x009e06a0 ret 8
    Elem0CS* insert(Elem0CS* position, const Elem0CS& value);          // 0x009e0b20 ret 8
};
struct ElemA4 {                                                         // size 0xa4
    uint32 f00[4];                     // +0x00
    Vec40  v10;                        // +0x10  (items)
    Vec40  v24;                        // +0x24  (gaits)
    uint32 f38[0x1b];                  // +0x38 .. +0xa4
};
struct AnimA {                          // destructor @ 0x009dfc40
    uint32 pad_000[3];                 // +0x00
    void*  p0c;                        // +0x0c
    uint32 pad_010[4];                 // +0x10
    Vec40  v20;                        // +0x20
    ~AnimA();
};
struct AnimB {                          // destructor @ 0x009dfc90
    uint32 pad_000[0x35];              // +0x00 .. +0xd4
    void*  p0d4;                       // +0x0d4
    uint32 pad_0d8[4];                 // +0x0d8
    void*  p0e8;                       // +0x0e8
    uint32 pad_0ec[4];                 // +0x0ec
    void*  p0fc;                       // +0x0fc
    uint32 pad_100[0x0a];              // +0x100
    void*  p128;                       // +0x128
    uint32 pad_12c[4];                 // +0x12c
    Vec40  v13c;                       // +0x13c
    ~AnimB();
};
struct AnimC {                          // destructor @ 0x009dfd30
    uint32 pad_000[5];                 // +0x00
    void*  p014;                       // +0x14
    uint32 pad_018[4];                 // +0x18
    Vec40  v28;                        // +0x28
    uint32 pad_03c[0x1c];              // +0x3c .. +0xac
    void*  p0ac;                       // +0xac
    void*  p0b0;                       // +0xb0
    ~AnimC();
};
// ---- items of slice s009dfc40 end

// ---- items of slice s009e0d90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_gait_default_id;                                 // 0x013f1cac 50.0f
extern void* g_name_map;                                              // 0x0166c06c global name->object map
void*  CreateByName(const uint32 key);                                // 0x00a08a20
uint32 HashName(const char* s, uint32 basis, int one);                // 0x00932e80 FNV-1a
struct CArgs { void** MainArguments(int n); };                        // 0x00838320 __thiscall ret 4
struct Combiner { void Combine5(void* dst, unsigned i, const void* a,
                               float f, const void* b); };            // 0x009dc5b0 __thiscall
struct GaitA_s009e_0d90; struct GaitB_s009e_0d90; struct GaitC_s009e_0d90;
void  CopyA(GaitA_s009e_0d90* first, GaitA_s009e_0d90* last, GaitA_s009e_0d90* result);                // 0x009dc230 eastl::copy (cdecl)
void  CopyB(GaitB_s009e_0d90* first, GaitB_s009e_0d90* last, GaitB_s009e_0d90* result);                // 0x009dc270 eastl::copy (cdecl)
void  CopyC(GaitC_s009e_0d90* first, GaitC_s009e_0d90* last, GaitC_s009e_0d90* result);                // 0x009dc2b0 eastl::copy (cdecl)
struct RBNode;
struct RBTree0 { void Insert(RBNode** outNode, RBNode* parent, const uint32* key, int flag); };
struct GaitA_s009e_0d90 {                                                         // 0x44, vtable 0x01447cc0
    virtual void f0();
    int   id;                                                          // +0x04
    float x, y, z;                                                     // +0x08
    Slot  s[3];                                                        // +0x14
    GaitA_s009e_0d90(const GaitA_s009e_0d90& o);                                             // 0x009dbe30
};
struct GaitB_s009e_0d90 {                                                         // 0x58, vtable 0x01447cc4
    virtual void f0();
    int   id;                                                          // +0x04
    float a, b, c, d;                                                  // +0x08
    Slot  s[4];                                                        // +0x18
    GaitB_s009e_0d90(const GaitB_s009e_0d90& o);                                             // 0x009dbe80
};
struct GaitC_s009e_0d90 {                                                         // 0x1c, vtable 0x01447cc8
    virtual void f0();
    int   id;                                                          // +0x04
    int   pad8;                                                        // +0x08
    float x, y, z;                                                     // +0x0c
    int   pad18;                                                       // +0x18
    GaitC_s009e_0d90(const GaitC_s009e_0d90& o);                                             // 0x009dbed0
};
struct GaitItem_s009e_0d90 { float a, b; int c; };                                // 0x0c (ItemArr element)
template <class T>
struct Vec_s009e_0d90 {                                                           // 0x14: begin/end/cap + 8-byte alloc
    T* b;
    T* e;
    T* cap;
    int alloc[2];
    Vec_s009e_0d90() : b(0), e(0), cap(0) {}
    ~Vec_s009e_0d90() { if (b && ((int*)b)[-1]) operator delete[](b); }
    Vec_s009e_0d90& operator=(const Vec_s009e_0d90& o);                                      // 0x9dfda0 / 0x9dfec0 / 0x9dffe0 / 0x9df630
    void reserve(int n);                                               // 0x9df400 / 0x9df4c0 / 0x9df570 / 0x9df630 / 0x9df800
    void clear();                                                      // 0x9e0940 / 0x9e0980 / 0x9e09c0
    void realloc_insert(T* pos, const T& v);                           // 0x9e0110 / 0x9e0230 / 0x9e0330 / 0x9e04e0 / 0x9e1990
    void insert(T* pos, const T& v);                                   // 0x9e0b20
    void push_back(const T& v) {
        if (e < cap) {
            T* p = e++;
            if (p) ::new((void*)p) T(v);
        } else {
            realloc_insert(e, v);
        }
    }
};
struct Gait_s009e_0d90 {                                                          // 0x40
    int          id;                                                   // +0x00
    Vec_s009e_0d90<GaitA_s009e_0d90>   a;                                                    // +0x04
    Vec_s009e_0d90<GaitB_s009e_0d90>   b;                                                    // +0x18
    Vec_s009e_0d90<GaitC_s009e_0d90>   c;                                                    // +0x2c
    Gait_s009e_0d90();                                                            // 0x009e1030
    Gait_s009e_0d90(const Gait_s009e_0d90& o);                                               // 0x009e1100
};
struct Inner_s009e_0d90 {                                                         // owner's per-entry data
    int        f0;                                                     // +0x00
    float      f4;                                                     // +0x04
    int        f8;                                                     // +0x08
    Vec_s009e_0d90<Item>  items;                                                  // +0x0c
    Vec_s009e_0d90<Gait_s009e_0d90>  gaits;                                                  // +0x20

    void AssignItemsN(const Inner_s009e_0d90* o, uint32 n);                       // 0x009e1160
    void AssignItemsF(const Inner_s009e_0d90* o, uint32 flags);                   // 0x009e1260
    void AssignItems(const Inner_s009e_0d90* o);                                  // 0x009e1370
    void Combine(const Inner_s009e_0d90* a, float f, const Inner_s009e_0d90* b);             // 0x009e1470
};
struct Record {                                                        // 0x150
    GaitC_s009e_0d90       gaitC;                                                 // +0x000
    GaitB_s009e_0d90       gaitB;                                                 // +0x01c
    GaitA_s009e_0d90       gaitA;                                                 // +0x074
    int         maxC;                                                  // +0x0b8
    int         maxB;                                                  // +0x0bc
    int         maxA;                                                  // +0x0c0
    int         kind;                                                  // +0x0c4
    int         flag;                                                  // +0x0c8
    int         pad0cc;                                                // +0x0cc
    Gait_s009e_0d90        gait;                                                  // +0x0d0
    Item        item;                                                  // +0x110
    int         pad11c[3];                                             // +0x11c
    Vec_s009e_0d90<Item>   items;                                                 // +0x128
    Vec_s009e_0d90<Gait_s009e_0d90>   gaits;                                                 // +0x13c
};
struct Holder {                                                        // +0x04 = Record*
    int          f00;                                                  // +0x00
    void*        val;                                                  // +0x04
    Vec_s009e_0d90<void*>   v1;                                                   // +0x08
    Vec_s009e_0d90<void*>   v2;                                                   // +0x1c
};
struct Outer {                                                         // this
    int      pad00;                                                    // +0x00
    void*    eval;                                                     // +0x04
    int      pad08;                                                    // +0x08
    Holder*  hC;                                                       // +0x0c
    int      pad10[8];                                                 // +0x10
    Holder*  h30;                                                      // +0x30

    void AddGait(void* arg);                                           // 0x009e0d90
    void AddItem(void* arg);                                           // 0x009e0f80
    void PushFlag(bool flag);                                          // 0x009e0ff0
    void Select(void* arg);                                            // 0x009e1b40
    void PushGait(bool flag);                                          // 0x009e1cd0
};
struct ItemArr {                                                       // 0x18
    uint32           count;                                            // +0x00
    Vec_s009e_0d90<GaitItem_s009e_0d90>    v;                                                // +0x04
    void Add(const GaitItem_s009e_0d90* value);                                   // 0x009e1610
    void Build(const void* src);                                       // 0x009e1760
};
struct RPair { float a, b; };
struct RBNode {
    RBNode* c0;                                                        // +0x00
    RBNode* c4;                                                        // +0x04
    RBNode* par;                                                       // +0x08
    int     color;                                                     // +0x0c
    uint32  key;                                                       // +0x10
    void*   value;                                                     // +0x14
};
struct RBTree {
    int      f00;                                                      // +0x00
    RBNode*  sentinel;                                                 // +0x04 (its address is the sentinel)
    int      f08;                                                      // +0x08
    RBNode*  root;                                                     // +0x0c

    // A parameter is copied only when it is (potentially) modified; referencing it through a
    // pointer forces the copy the original performs.  The 3rd argument of RBTree0::Insert is
    // the node *payload* pointer (0x009e0c00 writes the key through it); the original stores
    // `&params` there, i.e. the address of its saved-parameters area.
    void** find_or_insert(volatile const uint32* key);                 // 0x009e17d0
    void   FindNode(RBNode** keyOut, const uint32* key);               // 0x00e5c780 (this=p2, edx=p3)
};
struct VRange { void DestroyRangeA4n(ElemA4* first, ElemA4* last); };  // 0x009e0b90 member
struct RecBlob {                                                        // 0x30
    int      f00;                                                       // +0x00
    void*    p04;                                                       // +0x04
    int      pad08[5];                                                  // +0x08
    ElemA4*  vb;                                                        // +0x1c
    ElemA4*  ve;                                                        // +0x20
    ElemA4*  vcap;                                                      // +0x24
    int      alloc[2];                                                  // +0x28
    ~RecBlob();
};
// ---- items of slice s009e0d90 end

// ---- items of slice s009e1df0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_1550b20;                                               // 0x01550b20 1.0f
extern float g_1550b24;                                               // 0x01550b24 1.0f
extern float g_1550b2c;                                               // 0x01550b2c 6.0f
extern float g_1550b30;                                               // 0x01550b30 0.8f
extern float g_1550b34;                                               // 0x01550b34 0.02f
extern float g_1550b38;                                               // 0x01550b38 0.25f
extern float g_1550b3c;                                               // 0x01550b3c 0.75f
extern float g_1550b40;                                               // 0x01550b40 0.5f
extern float g_1550b44;                                               // 0x01550b44 0.1f
extern float g_1550b48;                                               // 0x01550b48 0.1f
extern float g_1550b4c;                                               // 0x01550b4c 0.075f
extern float g_1550b50;                                               // 0x01550b50 0.025f
extern float g_1550b54;                                               // 0x01550b54 0.05f
extern float g_1550b58;                                               // 0x01550b58 0.5f
extern float g_1550b5c;                                               // 0x01550b5c 0.15f
extern float g_1550b60;                                               // 0x01550b60 10.0f
extern float g_1550b64;                                               // 0x01550b64 10.0f
extern float g_1550b68;                                               // 0x01550b68 10.0f
extern float g_166c024;                                               // 0x0166c024
extern float g_166c028;                                               // 0x0166c028
extern float g_166c02c;                                               // 0x0166c02c
extern float g_166c030;                                               // 0x0166c030
extern float g_166c034;                                               // 0x0166c034
extern float g_166c038;                                               // 0x0166c038
extern float g_166c03c;                                               // 0x0166c03c
extern float g_166c040;                                               // 0x0166c040
extern float g_166c044;                                               // 0x0166c044
extern int   g_15515dc;                                               // 0x015515dc alloc-debug flag
struct GaitA; struct GaitB; struct GaitC;
struct Gait_s009e_1df0;
Gait_s009e_1df0* Copy40(Gait_s009e_1df0* first, Gait_s009e_1df0* last, Gait_s009e_1df0* result);                  // 0x009e0cd0 eastl::copy
struct VecA {                                                         // 0x14: begin/end/cap + alloc
    GaitA* b; GaitA* e; GaitA* cap; int alloc[2];
    VecA() : b(0), e(0), cap(0) {}
    ~VecA() { if (b && ((int*)b)[-1]) operator delete[](b); }
    VecA& assign(const VecA& o);                                      // 0x009dfda0
};
struct VecB {
    GaitB* b; GaitB* e; GaitB* cap; int alloc[2];
    VecB() : b(0), e(0), cap(0) {}
    ~VecB() { if (b && ((int*)b)[-1]) operator delete[](b); }
    VecB& assign(const VecB& o);                                      // 0x009dfec0
};
struct VecC {
    GaitC* b; GaitC* e; GaitC* cap; int alloc[2];
    VecC() : b(0), e(0), cap(0) {}
    ~VecC() { if (b && ((int*)b)[-1]) operator delete[](b); }
    VecC& assign(const VecC& o);                                      // 0x009dffe0
};
struct Gait_s009e_1df0 {                                                         // 0x40
    int  id;                                                          // +0x00
    VecA a;                                                           // +0x04
    VecB b;                                                           // +0x18
    VecC c;                                                           // +0x2c
    Gait_s009e_1df0(const Gait_s009e_1df0& o) : a(), b(), c()
    {
        id = o.id; a.assign(o.a); b.assign(o.b); c.assign(o.c);
    }
    Gait_s009e_1df0& operator=(const Gait_s009e_1df0& o)
    {
        if (this != &o) {
            id = o.id; a.assign(o.a); b.assign(o.b); c.assign(o.c);
        }
        return *this;
    }
};
struct VecG {                                                         // 0x14
    Gait_s009e_1df0* b; Gait_s009e_1df0* e; Gait_s009e_1df0* cap; int alloc[2];
    VecG() : b(0), e(0), cap(0) {}
    ~VecG() { destroy(b, e); if (b && ((int*)b)[-1]) operator delete[](b); }
    void reserve(int n);                                              // 0x009e18f0
    void destroy(Gait_s009e_1df0* first, Gait_s009e_1df0* last);                            // 0x009de770
    void realloc_insert(Gait_s009e_1df0* pos, const Gait_s009e_1df0& v);                    // 0x009e1990
    void push_back(const Gait_s009e_1df0& v)
    {
        if (e < cap) { Gait_s009e_1df0* p = e++; ::new((void*)p) Gait_s009e_1df0(v); }
        else realloc_insert(e, v);
    }
    void pop_back() { --e; e->~Gait_s009e_1df0(); }
};
template <class T> inline const T& emin(const T& a, const T& b) { return b < a ? b : a; }
struct VecI {
    Item* b; Item* e; Item* cap; int alloc[2];
    VecI() : b(0), e(0), cap(0) {}
    ~VecI() { if (b && ((int*)b)[-1]) operator delete[](b); }
    Item* erase(Item* first, Item* last);                             // 0x009e0480
};
struct Inner_s009e_1df0 {                                                        // 0xa0
    int    f0;                                                        // +0x00
    float  f4;                                                        // +0x04
    int    f8;                                                        // +0x08
    VecI   items;                                                     // +0x0c
    VecG   gaits;                                                     // +0x20
    float  p[26];                                                     // +0x34
    bool   flag;                                                      // +0x9c
    Inner_s009e_1df0();                                                          // 0x009e1df0
    void AssignGaitsN(const Inner_s009e_1df0* o, uint32 n);                      // 0x009e1fe0
    void AssignGaitsF(const Inner_s009e_1df0* o, uint32 flags);                  // 0x009e2140
    void AssignGaits(const Inner_s009e_1df0* o);                                 // 0x009e22f0
};
// ---- items of slice s009e1df0 end

// ---- items of slice s009e2490 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(sqrt)
struct Slot_s009e_2490 {            // 16 bytes
    float a, b;
    bool c, d;
    short e;
    int pad;
    Slot_s009e_2490() : a(0.0f), b(0.0f), c(false), d(false), e(0) {}
};
struct GaitA_s009e_2490 {           // 0x44
    virtual void f0();   // 0x009dc410 (vtable 0x01447cc0)
    int id;
    float x, y, z;
    Slot_s009e_2490 s[3];
    GaitA_s009e_2490(int i, float px, float py, float pz) : id(i), x(px), y(py), z(pz) {}
};
struct GaitB_s009e_2490 {           // 0x58
    virtual void f0();   // 0x009dc4f0 (vtable 0x01447cc4)
    int id;
    float a, b, c, d;
    Slot_s009e_2490 s[4];
    GaitB_s009e_2490(int i, float pa, float pb, float pc, float pd) : id(i), a(pa), b(pb), c(pc), d(pd) {}
};
struct GaitC_s009e_2490 {           // 0x1c
    virtual void f0();   // 0x009dba20 (vtable 0x01447cc8)
    int id;
    float x, y, z;
    bool c0, c1;
    short c2;
    int pad;
    GaitC_s009e_2490(int i, float px) : id(i), x(px), y(0.0f), z(0.0f), c0(false), c1(false), c2(0) {}
};
template <class T> T* vcopy(T* first, T* last, T* dest);   // eastl::copy (cdecl); instances: symbols/slices/s009e2490.txt
template <class T>
struct Vec_s009e_2490 {             // 0x14 bytes: begin/end/cap + 8-byte allocator
    T* b;
    T* e;
    T* cap;
    int alloc[2];
    Vec_s009e_2490() : b(0), e(0), cap(0) {}
    ~Vec_s009e_2490() { if (b && ((int*)b)[-1]) operator delete[](b); }
    void realloc_insert(T* pos, const T& v);   // per-instance addresses: symbols/slices/s009e2490.txt
    void reserve(int n);
    void assign(const Vec_s009e_2490& o);
    void push_back(const T& v) {
        if (e < cap) { T* p = e++; ::new((void*)p) T(v); }
        else realloc_insert(e, v);
    }
    void clear() {
        T* f = b; T* l = e;
        vcopy(l, e, f);
        e -= (l - f);
    }
    void clear2() {
        T* f = b; T* l = e;
        e -= (l - f);
    }
};
struct Gait_s009e_2490 {            // 0x40
    int id;
    Vec_s009e_2490<GaitA_s009e_2490> a;
    Vec_s009e_2490<GaitB_s009e_2490> b;
    Vec_s009e_2490<GaitC_s009e_2490> c;
    Gait_s009e_2490();   // 0x009e1030
    Gait_s009e_2490(const Gait_s009e_2490& o) : id(o.id) { a.assign(o.a); b.assign(o.b); c.assign(o.c); }
};
struct Item_s009e_2490 { int x, y, idx; };
struct Inner_s009e_2490 {
    int pad1[3];
    Item_s009e_2490* ib;            // +0xc
    Item_s009e_2490* ie;
    int pad2[3];
    Vec_s009e_2490<Gait_s009e_2490> gaits;     // +0x20
    int pad3[(0xa0 - 0x20 - 0x14) / 4];
};
struct Entry_s009e_2490 {           // 0xa4
    int pad0;
    Inner_s009e_2490 in;
};
struct Table_s009e_2490 {
    char pad[0x18];
    int count;
    Entry_s009e_2490* entries;
};
// ---- items of slice s009e2490 end

// ---- items of slice s009e3580 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_Half;                                                    // 0x01471064 0.5f
extern float g_Eps;                                                     // 0x01447c88 1e-7f
extern float g_OneMinusEps;                                             // 0x01447ccc ~0.99999f
extern float g_ChannelGain;                                             // 0x01447cbc 0.8f
extern int   g_1515dc;                                                  // 0x015515dc
void* EAAllocate(unsigned size, const char* tag, int a, int b, int c, int d);  // 0x00f473a0
double WrapRange(float delta, float period);                            // 0x009b3c10
double iat_floor(double x);                                             // 0x011e0906
struct Slot_s009e_3580 {                                                           // 0x10
    float a, b;
    bool  c, d;
    short e;
    int   pad;                                                          // never written by the ctors
    Slot_s009e_3580() : a(0.0f), b(0.0f), c(0), d(0), e(0) {}
};
struct IdBase_s009e_3580 { int id; IdBase_s009e_3580() : id(0) {} };
struct GaitA_s009e_3580 : IdBase_s009e_3580 {                                                 // 0x44, vtable 0x01447cc0
    __forceinline GaitA_s009e_3580() : x(0.0f), y(0.0f), z(0.0f), s() {}
    virtual void f0();
    float x, y, z;
    Slot_s009e_3580  s[3];
};
struct GaitB_s009e_3580 : IdBase_s009e_3580 {                                                 // 0x58, vtable 0x01447cc4
    __forceinline GaitB_s009e_3580() : a(g_Eps), b(g_Eps), c(g_Eps), d(g_OneMinusEps), s() {}
    virtual void f0();
    float a, b, c, d;
    Slot_s009e_3580  s[4];
};
struct GaitCData_s009e_3580 {                                                      // 0x14
    float x, y, z;
    bool  c0, c1;
    short c2;
    int   pad;                                                          // never written by the ctors
    GaitCData_s009e_3580() : x(0.0f), y(0.0f), z(0.0f), c0(0), c1(0), c2(0) {}
    GaitCData_s009e_3580(float xv) : x(xv), y(0.0f), z(0.0f), c0(0), c1(0), c2(0) {}
};
struct GaitC_s009e_3580 {                                                          // 0x18: no vtable of its own
    int id;
    GaitCData_s009e_3580 d;
    __forceinline GaitC_s009e_3580() : id(0), d(g_Half) {}
};
template <class T>
struct Vec_s009e_3580 {                                                            // 0x14 every T here
    T*   b;
    T*   e;
    T*   cap;
    int  alloc[2];
    Vec_s009e_3580() : b(0), e(0), cap(0) {}
    ~Vec_s009e_3580() { if (b && ((int*)b)[-1]) operator delete[](b); }
    void reserve(int n);
    void destroy(T* first, T* last);
    void resize(unsigned n, const T& v);                                // Vec<Item> only
};
struct Gait_s009e_3580 {                                                           // 0x40
    int id;
    Vec_s009e_3580<GaitA_s009e_3580> a;
    Vec_s009e_3580<GaitB_s009e_3580> b;
    Vec_s009e_3580<GaitC_s009e_3580> c;
    Gait_s009e_3580();                                                             // 0x009e1030
};
template <> inline Vec_s009e_3580<Gait_s009e_3580>::~Vec_s009e_3580()
{
    destroy(b, e);
    if (b && ((int*)b)[-1]) operator delete[](b);
}
struct Inner_s009e_3580;                                                           // 0xa0
struct Entry_s009e_3580;                                                           // 0xa4
struct Inner_s009e_3580 {
    int    f0;                                                          // +0x00 blend flags
    float  f4;                                                          // +0x04
    int    f8;                                                          // +0x08 key index, -1 = unused
    Vec_s009e_3580<Item> items;                                                    // +0x0c
    Vec_s009e_3580<Gait_s009e_3580> gaits;                                                    // +0x20
    float  p[26];                                                       // +0x34 tune values
    bool   flag;                                                        // +0x9c
    Inner_s009e_3580();
    Inner_s009e_3580(const Inner_s009e_3580& o);
    Inner_s009e_3580(int index, int count);
    Inner_s009e_3580& operator=(const Inner_s009e_3580& o);
    void __thiscall Assign(const Inner_s009e_3580* o);                             // 0x009dbc60
    void __thiscall AssignItems(const Inner_s009e_3580* o);                        // 0x009e1370
    void __thiscall AssignGaits(const Inner_s009e_3580* o);                        // 0x009e22f0
    void __thiscall BlendKeys(const Inner_s009e_3580* a, float t, const Inner_s009e_3580* b); // 0x009e1470
    void __thiscall Blend(const Inner_s009e_3580* a, float t, const Inner_s009e_3580* b);
};
struct Entry_s009e_3580 {
    float key;
    Inner_s009e_3580 in;
    Entry_s009e_3580() : key(0.0f) {}
    Entry_s009e_3580(const Entry_s009e_3580& o);
    Entry_s009e_3580& operator=(const Entry_s009e_3580& o) { key = o.key; in = o.in; return *this; }
};
struct EntryArr_s009e_3580 {                                                       // Table + 0x18
    unsigned count;
    Vec_s009e_3580<Entry_s009e_3580> v;
    void Insert(const Entry_s009e_3580* e);                                        // 0x009e4a00
    void Sample(float key, Inner_s009e_3580* out);
};
struct ChannelTail { Gait_s009e_3580* b; Gait_s009e_3580* e; Gait_s009e_3580* cap; };                    // +0xa8
struct ChannelHead {                                                    // +0x00 of a channel cell
    float gain;
    bool  on;
    char  pad[3];                                                       // left uninitialised
    ChannelHead() : gain(g_ChannelGain), on(true) {}
};
struct Channel {                                                        // 0xb4
    float       gain;                                                   // +0x00
    bool        on;                                                     // +0x04
    char        pad[3];                                                 // +0x05
    Inner_s009e_3580       in;                                                     // +0x08
    ChannelTail tail;                                                   // +0xa8
    Channel();
    void Reset();
};
struct gcmddTable {                                                     // 0x12c0
    int m00;                                                            // +0x00
    int m04[6];                                                         // +0x04
    int   mA[6][4];                                                     // +0x1c integer keys
    float mB[6][4];                                                     // +0x7c
    float mC[6][4];                                                     // +0xdc
    int m13c;                                                           // +0x13c
    Channel channels[24];                                               // +0x140
    Inner_s009e_3580   inner;                                                      // +0x1220
    gcmddTable();
    void Reset(int n, int m);
};
struct Path {                                                           // 0x18
    int unknown;                                                        // +0x00 (left alone by the ctor)
    int a;                                                              // +0x04
    int b;                                                              // +0x08
    int c;                                                              // +0x0c
    int d;                                                              // +0x10
    int e;                                                              // +0x14
    Path() : a(0), b(0), c(-1), d(0), e(0) {}
};
namespace Anim {
struct gcmdd : GaitC_s009e_3580 {                                                  // 0x1c8, vtable 0x01447cc8
    virtual void notify();                                              // vfptr at +0, GaitC base at +4
    GaitB_s009e_3580 b;                                                            // +0x1c
    GaitA_s009e_3580 a;                                                            // +0x74
    Path  path;                                                         // +0xb8
    Gait_s009e_3580  gait;                                                         // +0xd0
    float f110;                                                         // +0x110
    float f114;                                                         // +0x114
    int   i118;                                                         // +0x118
    Inner_s009e_3580 inner;                                                        // +0x11c
    float f1bc;                                                         // +0x1bc
    bool  f1c0;                                                         // +0x1c0
    float f1c4;                                                         // +0x1c4
    gcmdd();
};  // namespace Anim
}
struct gcmddHost {
    void Create(int unused);
};
void Anim::gcmdd::notify() {}
Entry_s009e_3580::Entry_s009e_3580(const Entry_s009e_3580& o)
    : key(o.key), in(o.in)
{
}
// ---- items of slice s009e3580 end

// ---- items of slice s009e4450 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_Zero;                                                    // 0x01485378 0.0f
extern float g_One;                                                     // 0x01485720 1.0f
extern int   g_alloc;                                                   // 0x013ebb38 (allocator)
void* EAAllocate(unsigned size, const char* tag, int a, int b, int* allocator, int line);  // 0x00f473a0
void* ArgScriptCreateParser();                                          // 0x008408d0
struct Slot_s009e_4450 {                                                           // 0x10
    float a, b;
    bool  c, d;
    short e;
    int   pad;
    Slot_s009e_4450() : a(0.0f), b(0.0f), c(0), d(0), e(0) {}
};
struct IdBase_s009e_4450 { int id; IdBase_s009e_4450() : id(0) {} };
struct GaitA_s009e_4450 : IdBase_s009e_4450 {                                                 // 0x44, vtable 0x01447cc0
    __forceinline GaitA_s009e_4450() : x(0.0f), y(0.0f), z(0.0f), s() {}
    virtual void f0();
    float x, y, z;
    Slot_s009e_4450  s[3];
};
struct GaitB_s009e_4450 : IdBase_s009e_4450 {                                                 // 0x58, vtable 0x01447cc4
    __forceinline GaitB_s009e_4450() : a(g_Eps), b(g_Eps), c(g_Eps), d(g_OneMinusEps), s() {}
    virtual void f0();
    float a, b, c, d;
    Slot_s009e_4450  s[4];
};
struct GaitCData_s009e_4450 {                                                      // 0x14
    float x, y, z;
    bool  c0, c1;
    short c2;
    int   pad;
    GaitCData_s009e_4450() : x(0.0f), y(0.0f), z(0.0f), c0(0), c1(0), c2(0) {}
    GaitCData_s009e_4450(float xv) : x(xv), y(0.0f), z(0.0f), c0(0), c1(0), c2(0) {}
};
struct GaitC_s009e_4450 {                                                          // 0x18
    int id;
    GaitCData_s009e_4450 d;
    __forceinline GaitC_s009e_4450() : id(0), d(g_Half) {}
};
template <class T>
struct Vec_s009e_4450 {                                                            // 0x14 every T here
    T*   b;
    T*   e;
    T*   cap;
    int  alloc[2];
    Vec_s009e_4450() : b(0), e(0), cap(0) {}
    ~Vec_s009e_4450() { if (b && ((int*)b)[-1]) operator delete[](b); }
    void reserve(int n);
    void destroy(T* first, T* last);
    void resize(unsigned n, const T& v);
};
struct Gait_s009e_4450 {                                                           // 0x40
    int id;
    Vec_s009e_4450<GaitA_s009e_4450> a;
    Vec_s009e_4450<GaitB_s009e_4450> b;
    Vec_s009e_4450<GaitC_s009e_4450> c;
    Gait_s009e_4450();
};
template <> inline Vec_s009e_4450<Gait_s009e_4450>::~Vec_s009e_4450()
{
    destroy(b, e);
    if (b && ((int*)b)[-1]) operator delete[](b);
}
struct Inner_s009e_4450;                                                           // 0xa0
struct Entry_s009e_4450;                                                           // 0xa4
struct Inner_s009e_4450 {
    int    f0;                                                          // +0x00 blend flags
    float  f4;                                                          // +0x04
    int    f8;                                                          // +0x08 key index, -1 = unused
    Vec_s009e_4450<Item> items;                                                    // +0x0c
    Vec_s009e_4450<Gait_s009e_4450> gaits;                                                    // +0x20
    float  p[26];                                                       // +0x34 tune values
    bool   flag;                                                        // +0x9c
    Inner_s009e_4450();
    Inner_s009e_4450(const Inner_s009e_4450& o);
    Inner_s009e_4450(int index, int count);
    Inner_s009e_4450& operator=(const Inner_s009e_4450& o);
    void __thiscall Assign(const Inner_s009e_4450* o);                             // 0x009dbc60
    void __thiscall AssignItems(const Inner_s009e_4450* o);                        // 0x009e1370
    void __thiscall AssignItemsN(const Inner_s009e_4450* o, unsigned n);           // 0x009e1160
    void __thiscall AssignGaits(const Inner_s009e_4450* o);                        // 0x009e22f0
    void __thiscall AssignGaitsN(const Inner_s009e_4450* o, unsigned n);           // 0x009e1fe0
    void __thiscall AssignGaitsF(const Inner_s009e_4450* o, unsigned n);           // 0x009e2140
    void __thiscall CopyMasked(const Inner_s009e_4450* o, unsigned mask);          // 0x009dba90
    void __thiscall CopyItems(const Inner_s009e_4450* o, unsigned mask);           // 0x009e1260
    void __thiscall BlendKeys(const Inner_s009e_4450* a, float t, const Inner_s009e_4450* b); // 0x009e1470
    void __thiscall Blend(const Inner_s009e_4450* a, float t, const Inner_s009e_4450* b);     // 0x009e37c0
    bool __thiscall ValidBlocks();                                      // 0x009de630
};
struct Entry_s009e_4450 {
    float key;
    Inner_s009e_4450 in;
    Entry_s009e_4450() : key(0.0f) {}
    Entry_s009e_4450(const Entry_s009e_4450& o);                                              // 0x009e4120
};
void  EntryConstructN(Entry_s009e_4450* dst, unsigned n, const Entry_s009e_4450* src, int extra);   // 0x009e4170
Entry_s009e_4450* EntryAssignRange(Entry_s009e_4450* first, Entry_s009e_4450* last, Entry_s009e_4450* result);            // 0x009e41e0
Entry_s009e_4450* EntryCopy(Entry_s009e_4450* first, Entry_s009e_4450* last, Entry_s009e_4450* result);                   // 0x009e4260
Entry_s009e_4450* EntryCopyBackward(Entry_s009e_4450* first, Entry_s009e_4450* last, Entry_s009e_4450* result);           // 0x009e42d0
Entry_s009e_4450* DestroyRangeA4(Entry_s009e_4450* first, Entry_s009e_4450* last, Entry_s009e_4450* result);              // 0x009e07d0
struct VecEntry {                                                       // 0x14
    Entry_s009e_4450* b;
    Entry_s009e_4450* e;
    Entry_s009e_4450* cap;
    int    alloc[2];
    VecEntry();
    VecEntry(unsigned n, const Entry_s009e_4450& v);                               // 0x009e4630
    ~VecEntry() { if (b && ((int*)b)[-1]) operator delete[](b); }
    void __thiscall reserve(int n);                                     // 0x009e4700
    Entry_s009e_4450* __thiscall insert(Entry_s009e_4450* pos, const Entry_s009e_4450& value);           // 0x009e4990
    void __thiscall realloc_insert(Entry_s009e_4450* pos, const Entry_s009e_4450& value);     // 0x009e47c0
    void __thiscall destroyRange(Entry_s009e_4450* first, Entry_s009e_4450* last);            // 0x009e0b90
};
struct EntryArr_s009e_4450 {                                                       // Table + 0x18
    unsigned count;
    VecEntry v;
    void Insert(const Entry_s009e_4450* e);                                        // 0x009e4a00
    void Reset();                                                       // 0x009e4940
    void Sample(float key, Inner_s009e_4450* out);                                 // 0x009e4030
    float Lookup(float key, Inner_s009e_4450** out);                              // 0x009dd480
};
struct Elem0C_s009e_4450 {                                                         // 0x0c
    float v0;
    float v1;
    bool  flag;
    char  pad[3];
};
struct Vec0C_s009e_4450 {                                                          // 0x14
    Elem0C_s009e_4450* b;
    Elem0C_s009e_4450* e;
    Elem0C_s009e_4450* cap;
    int     alloc[2];
    Vec0C_s009e_4450() : b(0), e(0), cap(0) {}
    ~Vec0C_s009e_4450() { if (b && ((int*)b)[-1]) operator delete[](b); }
    void reserve(int n);                                                // 0x009df800
    Elem0C_s009e_4450* erase(Elem0C_s009e_4450* first, Elem0C_s009e_4450* last);                         // 0x009e0480
};
struct Gcmdst {                                                         // 0x30
    unsigned count;                                                     // +0x00
    Vec0C_s009e_4450    v;                                                         // +0x04
    EntryArr_s009e_4450 arr;                                                       // +0x18
    Gcmdst() : count(0) {}
    void __thiscall AddElem(const Elem0C_s009e_4450& e);                           // 0x009e1610
    void __thiscall ResetDefault();                                     // 0x009e4aa0
    void __thiscall BuildFromSource(const void* src);                   // 0x009e4c00
};
struct CurveOut_s009e_4450 { float v; bool flag; char pad[3]; };
struct Curve_s009e_4450 {                                                          // the record's curve part
    void __thiscall Eval(float t, CurveOut_s009e_4450* out);                       // 0x009dbf10
};
struct CurveNode {                                                      // what mCurves[][] points at
    char     pad[0x18];                                                 // +0x00 the curve record
    EntryArr_s009e_4450 arr;                                                       // +0x18 the key list
};
struct ChannelTail_s009e_4450 {                                                    // +0xa8
    float  gain;
    Inner_s009e_4450* a;
    Inner_s009e_4450* b;
};
struct Channel_s009e_4450 {                                                        // 0xb4
    float       gain;                                                   // +0x00
    bool        on;                                                     // +0x04
    char        pad[3];                                                 // +0x05
    Inner_s009e_4450       in;                                                     // +0x08
    ChannelTail_s009e_4450 tail;                                                   // +0xa8
    bool __thiscall ValidBlocks();                                      // 0x009de630
};
struct GaitTable {                                                      // 0x12c0
    int        mGroups;                                                 // +0x00
    int        m04[6];                                                  // +0x04
    CurveNode* mCurves[6][4];                                           // +0x1c
    int        m7c[49];                                                 // +0x7c
    Channel_s009e_4450    channels[24];                                            // +0x140
    Inner_s009e_4450      inner;                                                   // +0x1220
    void Sample(float t, int lane, bool first, unsigned mask);          // 0x009e4450
    void SampleAt(float, float, float, int, int, int, int lane);        // 0x009e4600
};
float __stdcall CurveClamp2(float* v);                                  // 0x009dc7a0
// ---- items of slice s009e4450 end

// @ 0x009dba90
void Inner_s009d_b6d0::CopyMasked(const Inner_s009d_b6d0* src, uint32 mask)
{
    f00 = src->f00;
    if (g_skipScalars == 0 && (mask & 1) == 0)
        f04 = src->f04;
    f08 = src->f08;
    if ((mask & 4) == 0)
        f34 = src->f34;
    if ((mask & 8) == 0)
        f38 = src->f38;
    if ((mask & 0x10) == 0)
        f3c = src->f3c;
    if ((mask & 0x20) == 0)
        f40 = src->f40;
    if ((mask & 0x40) == 0)
        f44 = src->f44;
    if ((mask & 0x80) == 0)
        f48 = src->f48;
    if ((mask & 0x100) == 0)
        f4c = src->f4c;
    if ((mask & 0x200) == 0)
        f50 = src->f50;
    if ((mask & 0x400) == 0)
        f54 = src->f54;
    if ((mask & 0x800) == 0)
        f58 = src->f58;
    if ((mask & 0x1000) == 0)
        f5c = src->f5c;
    if ((mask & 0x2000000) == 0)
        f60 = src->f60;
    if ((mask & 0x2000) == 0)
        f64 = src->f64;
    if ((mask & 0x4000) == 0)
        f68 = src->f68;
    if ((mask & 0x8000) == 0)
        f6c = src->f6c;
    if ((mask & 0x10000) == 0)
        f70 = src->f70;
    if ((mask & 0x8000000) == 0)
        f74 = src->f74;
    if ((mask & 0x10000000) == 0)
        f78 = src->f78;
    if ((mask & 0x20000) == 0)
        f7c = src->f7c;
    if ((mask & 0x40000) == 0)
        f80 = src->f80;
    if ((mask & 0x80000) == 0)
        f84 = src->f84;
    if ((mask & 0x100000) == 0)
        f88 = src->f88;
    if ((mask & 0x200000) == 0)
        f8c = src->f8c;
    if ((mask & 0x400000) == 0)
        f90 = src->f90;
    if ((mask & 0x800000) == 0)
        f94 = src->f94;
    if ((mask & 0x1000000) == 0)
        f98 = src->f98;
    f9c = src->f9c;
}

// @ 0x009dbc60
void Inner_s009d_b6d0::Assign(const Inner_s009d_b6d0* src)
{
    f00 = src->f00;
    f04 = src->f04;
    f08 = src->f08;
    f34 = src->f34;
    f38 = src->f38;
    f3c = src->f3c;
    f40 = src->f40;
    f44 = src->f44;
    f48 = src->f48;
    f4c = src->f4c;
    f50 = src->f50;
    f54 = src->f54;
    f58 = src->f58;
    f5c = src->f5c;
    f60 = src->f60;
    f64 = src->f64;
    f68 = src->f68;
    f6c = src->f6c;
    f70 = src->f70;
    f74 = src->f74;
    f78 = src->f78;
    f7c = src->f7c;
    f80 = src->f80;
    f84 = src->f84;
    f88 = src->f88;
    f8c = src->f8c;
    f90 = src->f90;
    f94 = src->f94;
    f98 = src->f98;
    f9c = src->f9c;
}

// @ 0x009dbe30
Rec44* Rec44::Ctor(const Rec44* src)
{
    const int* r = src ? (const int*)src + 1 : 0;
    ref = *r;
    vtbl = (void*)0x1447cc0;
    x = src->x;
    y = src->y;
    z = src->z;
    memcpy(d, src->d, sizeof d);
    return this;
}

// @ 0x009dbe80
Rec58* Rec58::Ctor(const Rec58* src)
{
    const int* r = src ? (const int*)src + 1 : 0;
    ref = *r;
    vtbl = (void*)0x1447cc4;
    x = src->x;
    y = src->y;
    z = src->z;
    w = src->w;
    memcpy(d, src->d, sizeof d);
    return this;
}

// @ 0x009dbed0
Rec1C* Rec1C::Ctor(const Rec1C* src)
{
    const int* r = src ? (const int*)src + 1 : 0;
    ref = *r;
    vtbl = (void*)0x1447cc8;
    d[0] = src->d[0];
    memcpy(&d[1], &src->d[1], 4 * sizeof(int));
    return this;
}

// @ 0x009dbf10
void Curve::Eval(float t, CurveOut* out)
{
    int n = count;
    int i = 0;
    int idx = 0;
    if (n != 0) {
        for (; i != n; ++i) {
            if (!(t >= samples[i].t))
                break;
            idx = i;
        }
        if (i != 0 && i != n) {
            const Sample& a = samples[idx];
            const Sample& b = samples[i];
            out->v = (t - a.t) / (b.t - a.t) * (b.v - a.v) + a.v;
            out->exact = (t == a.t);
            return;
        }
    }
    out->v = samples[idx].v;
    out->d = samples[idx].d;
    out->exact = (t == samples[idx].t);
}

// @ 0x009dbfd0
Rec44* Rec44::Assign(const Rec44* src)
{
    const int* r = src ? (const int*)src + 1 : 0;
    ref = *r;
    x = src->x;
    y = src->y;
    z = src->z;
    d[0] = src->d[0];
    d[1] = src->d[1];
    d[2] = src->d[2];
    d[3] = src->d[3];
    d[4] = src->d[4];
    d[5] = src->d[5];
    d[6] = src->d[6];
    d[7] = src->d[7];
    d[8] = src->d[8];
    d[9] = src->d[9];
    d[10] = src->d[10];
    d[11] = src->d[11];
    return this;
}

// @ 0x009dc050
Rec58* Rec58::Assign(const Rec58* src)
{
    const int* r = src ? (const int*)src + 1 : 0;
    ref = *r;
    x = src->x;
    y = src->y;
    z = src->z;
    w = src->w;
    d[0] = src->d[0];
    d[1] = src->d[1];
    d[2] = src->d[2];
    d[3] = src->d[3];
    d[4] = src->d[4];
    d[5] = src->d[5];
    d[6] = src->d[6];
    d[7] = src->d[7];
    d[8] = src->d[8];
    d[9] = src->d[9];
    d[10] = src->d[10];
    d[11] = src->d[11];
    d[12] = src->d[12];
    d[13] = src->d[13];
    d[14] = src->d[14];
    d[15] = src->d[15];
    return this;
}

// @ 0x009dc0f0
Rec44* Copy44(const Rec44* first, const Rec44* last, Rec44* dst)
{
    for (; first != last; ++first, ++dst) {
        if (dst != 0) {
            const int* ref = first ? (const int*)first + 1 : 0;
            dst->ref = *ref;
            dst->vtbl = (void*)0x1447cc0;
            dst->x = first->x;
            dst->y = first->y;
            dst->z = first->z;
            memcpy(dst->d, first->d, sizeof dst->d);
        }
    }
    return dst;
}

// @ 0x009dc160
Rec58* Copy58(const Rec58* first, const Rec58* last, Rec58* dst)
{
    for (; first != last; ++first, ++dst) {
        if (dst != 0) {
            const int* ref = first ? (const int*)first + 1 : 0;
            dst->ref = *ref;
            dst->vtbl = (void*)0x1447cc4;
            dst->x = first->x;
            dst->y = first->y;
            dst->z = first->z;
            dst->w = first->w;
            memcpy(dst->d, first->d, sizeof dst->d);
        }
    }
    return dst;
}

// @ 0x009dc1d0
Rec1C* Copy1C(const Rec1C* first, const Rec1C* last, Rec1C* dst)
{
    for (; first != last; ++first, ++dst) {
        if (dst != 0) {
            const int* ref = first ? (const int*)first + 1 : 0;
            dst->ref = *ref;
            dst->vtbl = (void*)0x1447cc8;
            dst->d[0] = first->d[0];
            dst->d[1] = first->d[1];
            dst->d[2] = first->d[2];
            dst->d[3] = first->d[3];
            dst->d[4] = first->d[4];
        }
    }
    return dst;
}

// @ 0x009dc2b0
GaitC_s009d_b6d0* vcopyGaitC(const GaitC_s009d_b6d0* first, const GaitC_s009d_b6d0* last, GaitC_s009d_b6d0* dst)
{
    for (; first != last; ++first, ++dst) {
        const int* ref = first ? (const int*)first + 1 : 0;
        dst->ref = *ref;
        dst->t = first->t;
        dst->d[0] = first->d[0];
        dst->d[1] = first->d[1];
        dst->d[2] = first->d[2];
        dst->d[3] = first->d[3];
    }
    return dst;
}

// @ 0x009dc300
Val3b* CopyVal3b(const Val3b* first, const Val3b* last, Val3b* dst)
{
    for (; first != last; ++first, ++dst) {
        if (dst != 0) {
            dst->x = first->x;
            dst->y = first->y;
            dst->flag = first->flag;
        }
    }
    return dst;
}

// @ 0x009dc3c0
GaitC_s009d_b6d0* vcopyGaitCBack(const GaitC_s009d_b6d0* first, const GaitC_s009d_b6d0* last, GaitC_s009d_b6d0* dst)
{
    while (last != first) {
        --last;
        --dst;
        const int* ref = last ? (const int*)last + 1 : 0;
        dst->ref = *ref;
        dst->t = last->t;
        dst->d[0] = last->d[0];
        dst->d[1] = last->d[1];
        dst->d[2] = last->d[2];
        dst->d[3] = last->d[3];
    }
    return dst;
}

// @ 0x009dc5b0
void __stdcall SampleAt(Val3* out, uint32 index, const ValPath* a, float t, const ValPath* b)
{
    uint32 na = (uint32)(a->end - a->begin);
    uint32 nb = (uint32)(b->end - b->begin);
    if (index < na) {
        if (index < nb) {
            float base = a->begin[index].x;
            float v = sub_9B3C10(b->begin[index].x - base, 1.0f) * t + base;
            out->x = v - (float)floor((double)v);
            out->y = (b->begin[index].y - a->begin[index].y) * t + a->begin[index].y;
            out->z = a->begin[index].z;
            return;
        }
        *out = a->begin[index];
        return;
    }
    if (index < nb)
        *out = b->begin[index];
}

// @ 0x009de630
bool __fastcall FUN_009de630(void* self)
{
    u32* slot = (u32*)((u8*)self + 0xac);
    for (i32 pass = 0; pass < 2; ++pass, ++slot) {
        u32 arr = *slot;
        if (arr == 0) return false;
        u8* ap = (u8*)arr;
        i32 nb = (*(i32*)(ap + 0x24) - *(i32*)(ap + 0x20)) >> 6;
        if (nb == 0) return false;
        if (nb > 0) {
            i32* it = (i32*)(*(i32*)(ap + 0x20) + 0x1c);
            for (i32 i = 0; i < nb; ++i, it += 0x10) {
                if ((*(it - 5) - *(it - 6)) / 0x44 == 0) return false;
                if ((*(it)     - *(it - 1)) / 0x58 == 0) return false;
                if ((*(it + 5) - *(it + 4)) / 0x1c == 0) return false;
            }
        }
    }
    return true;
}

// @ 0x009de6e0
bool __cdecl FUN_009de6e0(Track2* t, void* serializer)
{
    i32 n1 = t->ItemCount();
    i32 n2 = Track2_TotalItems(t);
    u32 nBlocks = t->mCount;
    u32 size = (u32)(0x18 + n1 + n2 + (i32)nBlocks * 8 + (i32)nBlocks * 0x7c);

    u8* p = (u8*)operator_new(size, "Anim/bingr", 0, 0, 0, 0);
    *(u32*)(p + 0x00) = 0x54494147;          // 'GAIT'
    *(u32*)(p + 0x04) = size;
    *(u32*)(p + 0x08) = 0xb;
    *(u32*)(p + 0x0c) = 1;

    FUN_009dc760((Curve760*)t, (char*)p);
    FUN_009dd780(t, p);

    u32 expect = *(u32*)(p + 4);
    void** vt = *(void***)serializer;
    i32 (*fn)(void*, u8*, u32) = (i32 (*)(void*, u8*, u32))vt[3];
    i32 got = fn(serializer, p, expect);

    operator_delete__(p);
    return got == (i32)expect;
}

// @ 0x009de770
void __stdcall FUN_009de770(u8* begin, u8* end)
{
    while (begin < end) {
        u8* a = *(u8**)(begin + 0x2c);
        if (a != 0 && *(i32*)(a - 4) != 0) operator_delete__(a);
        u8* b = *(u8**)(begin + 0x18);
        if (b != 0 && *(i32*)(b - 4) != 0) operator_delete__(b);
        u8* c = *(u8**)(begin + 0x04);
        if (c != 0 && *(i32*)(c - 4) != 0) operator_delete__(c);
        begin += 0x40;
    }
}

// @ 0x009de7d0
u8* __cdecl FUN_009de7d0(u8* src, u8* end, u8* dst)
{
    void* p = 0;
    if (src != end) {
        do {
            u8* a = *(u8**)(src + 0x2c);
            if (a != 0 && *(i32*)(a - 4) != 0) operator_delete__(a);
            u8* b = *(u8**)(src + 0x18);
            if (b != 0 && *(i32*)(b - 4) != 0) operator_delete__(b);
            u8* c = *(u8**)(src + 0x04);
            if (c != 0 && *(i32*)(c - 4) != 0) operator_delete__(c);
            src += 0x40;
            dst += 0x40;
        } while (src != end);
        p = dst;
    } else {
        p = dst;
    }
    return (u8*)p;
}

// @ 0x009de8b0
void cGaitKeyBlockCommand::OnRegister(cIParser_s009d_e8b0* parser, cState_s009d_e8b0* state)
{
    mState = (cGaitKeyState*)state;
    cBlockCommandBase::OnRegister(parser, state);

#define REGISTER(Name, keyword) \
    AddCommand(GaitKeywords::keyword, new ("ArgScript/" #Name, 0, 0, 0, 0) c##Name##Command())

    REGISTER(SpeedI, speedi);
    REGISTER(StepHeight, stepheight);
    REGISTER(NumFeet, numfeet);
    REGISTER(Taxon, taxon);
    REGISTER(Trigger, trigger);
    REGISTER(DutyFactor, dutyfactor);
    REGISTER(NumPaths, numpaths);
    REGISTER(NumPathPosKeys, numpathposkeys);
    REGISTER(NumPathRotKeys, numpathrotkeys);
    REGISTER(NumPathBndKeys, numpathbndkeys);
    REGISTER(Tick, tic);
    REGISTER(Pos, pos);
    REGISTER(Rot, rot);
    REGISTER(Bnd, bnd);
    REGISTER(Spl, spl);
    REGISTER(TanFl, tanfl);
    REGISTER(HerFl, herfl);
    REGISTER(StepGallop, stepgallop);
    REGISTER(StepPhaseBiasH, stepphasebiash);
    REGISTER(StepPhaseBiasV, stepphasebiasv);
    REGISTER(StepSkew, stepskew);
    REGISTER(FootTilt, foottilt);
    REGISTER(TiltPoint, tiltpoint);
    REGISTER(ToeCurlMax, toecurlmax);
    REGISTER(ToeCurlBegin, toecurlbegin);
    REGISTER(ToeCurlEnd, toecurlend);
    REGISTER(SwayAmplitude, swayAmplitude);
    REGISTER(SwayPhase, swayPhase);
    REGISTER(TrackWidthReduction, trackWidthReduction);
    REGISTER(VerticalPhaseOffset, verticalphaseoffset);
    REGISTER(SagittalPhaseOffset, sagittalphaseoffset);
    REGISTER(LateralPhaseOffset, lateralphaseoffset);
    REGISTER(MaxVerticalOffset, maxverticaloffset);
    REGISTER(VerticalDist, verticaldist);
    REGISTER(WalkRunShape, walkrunshape);
    REGISTER(MaxSagittalOffset, maxsagittaloffset);
    REGISTER(MaxLateralOffset, maxlateraloffset);
    REGISTER(YawPhaseOffset, yawphaseoffset);
    REGISTER(PitchPhaseOffset, pitchphaseoffset);
    REGISTER(RollPhaseOffset, rollphaseoffset);
    REGISTER(MaxYawAngle, maxyawangle);
    REGISTER(MaxPitchAngle, maxpitchangle);
    REGISTER(MaxRollAngle, maxrollangle);

#undef REGISTER
}

// @ 0x009df360
void cStepLengthKeyBlockCommand::OnRegister(cIParser_s009d_e8b0* parser, cState_s009d_e8b0* state)
{
    mState = (cGaitKeyState*)state;
    cBlockCommandBase::OnRegister(parser, state);

    AddCommand(GaitKeywords::speedi,
               new ("ArgScript/SpeedI", 0, 0, 0, 0) cSpeedICommand());
    AddCommand(GaitKeywords::steplength,
               new ("ArgScript/StepLength", 0, 0, 0, 0) cStepLengthCommand());
}

// @ 0x009df400
template <> void Vec_s009d_e8b0<GaitA_s009d_e8b0>::reserve(int n)
{
    if ((unsigned int)n > capacity()) {
        GaitA_s009d_e8b0* p = n ? (GaitA_s009d_e8b0*)operator new(n * sizeof(GaitA_s009d_e8b0), "Anim/gait/untagged",
                                             0, 0, kAllocatorFile, 0xd1) : 0;
        CopyGaitA(mpBegin, mpEnd, p);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            FreeMemory(mpBegin);
        int count = size();
        mpBegin = p;
        mpEnd = p + count;
        mpEndOfStorage = p + n;
    }
}

// @ 0x009df570
template <> void Vec_s009d_e8b0<GaitC_s009d_e8b0>::reserve(int n)
{
    if ((unsigned int)n > capacity()) {
        GaitC_s009d_e8b0* p = n ? (GaitC_s009d_e8b0*)operator new(n * sizeof(GaitC_s009d_e8b0), "Anim/gait/untagged",
                                             0, 0, kAllocatorFile, 0xd1) : 0;
        CopyGaitC(mpBegin, mpEnd, p);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            FreeMemory(mpBegin);
        int count = size();
        mpBegin = p;
        mpEnd = p + count;
        mpEndOfStorage = p + n;
    }
}

// @ 0x009df6e0
template <> GaitA_s009d_e8b0* Vec_s009d_e8b0<GaitA_s009d_e8b0>::allocate_copy(int n, GaitA_s009d_e8b0* first, GaitA_s009d_e8b0* last)
{
    GaitA_s009d_e8b0* p = n ? (GaitA_s009d_e8b0*)operator new(n * sizeof(GaitA_s009d_e8b0), "Anim/gait/untagged",
                                        0, 0, kAllocatorFile, 0xd1) : 0;
    CopyConstructGaitA(&n, first, last, p, n);
    return p;
}

// @ 0x009df800
template <> void Vec_s009d_e8b0<GaitItem>::reserve(int n)
{
    if ((unsigned int)n > capacity()) {
        GaitItem* p = n ? (GaitItem*)operator new(n * sizeof(GaitItem), "Anim/gait/untagged",
                                                   0, 0, kAllocatorFile, 0xd1) : 0;
        CopyGaitItem(mpBegin, mpEnd, p);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            FreeMemory(mpBegin);
        int count = size();
        mpBegin = p;
        mpEnd = p + count;
        mpEndOfStorage = p + n;
    }
}

// @ 0x009df8b0
template <> Vec_s009d_e8b0<GaitItem>::Vec_s009d_e8b0(unsigned int n, const GaitItem& value, int unused)
{
    GaitItem* p = n ? (GaitItem*)operator new(n * sizeof(GaitItem), "Anim/gait/untagged",
                                              0, 0, kAllocatorFile, 0xd1) : 0;
    mpEndOfStorage = p + n;
    mpBegin = p;
    mpEnd = p;
    for (unsigned int i = n; i > 0; --i) {
        if (p)
            *p = value;
        ++p;
    }
    mpEnd = mpBegin + n;
}

// @ 0x009df9b0
template <> Vec_s009d_e8b0<AnalysisInfo>& Vec_s009d_e8b0<AnalysisInfo>::operator=(const Vec_s009d_e8b0<AnalysisInfo>& other)
{
    if (this != &other) {
        int n = other.size();
        if (capacity() < (unsigned int)n) {
            AnalysisInfo* p = allocate_copy(n, other.mpBegin, other.mpEnd);
            if (mpBegin && ((int*)mpBegin)[-1] != 0)
                FreeMemory(mpBegin);
            mpEndOfStorage = p + n;
            mpBegin = p;
            mpEnd = p + n;
        } else {
            int live = size();
            if (live < n) {
                CopyInfo(other.mpBegin, other.mpBegin + live, mpBegin);
                CopyConstructInfo(&n, other.mpBegin + live, other.mpEnd, mpEnd,
                                  (int)(uint32_t)other.mpEnd);
                mpEnd = mpBegin + n;
            } else {
                CopyInfo(other.mpBegin, other.mpEnd, mpBegin);
                mpEnd = mpBegin + n;
            }
        }
    }
    return *this;
}

// @ 0x009dfc40
AnimA::~AnimA()
{
    v20.DestroyRange(v20.mpBegin, v20.mpEnd);
    if (v20.mpBegin && ((int*)v20.mpBegin)[-1] != 0)
        operator delete[](v20.mpBegin);
    if (p0c && ((int*)p0c)[-1] != 0)
        operator delete[](p0c);
}

// @ 0x009dfc90
AnimB::~AnimB()
{
    v13c.DestroyRange(v13c.mpBegin, v13c.mpEnd);
    if (v13c.mpBegin && ((int*)v13c.mpBegin)[-1] != 0)
        operator delete[](v13c.mpBegin);
    if (p128 && ((int*)p128)[-1] != 0)
        operator delete[](p128);
    if (p0fc && ((int*)p0fc)[-1] != 0)
        operator delete[](p0fc);
    if (p0e8 && ((int*)p0e8)[-1] != 0)
        operator delete[](p0e8);
    if (p0d4 && ((int*)p0d4)[-1] != 0)
        operator delete[](p0d4);
}

// @ 0x009dfd30
AnimC::~AnimC()
{
    if (p0ac != 0)
        p0ac = 0;
    if (p0b0 != 0)
        p0b0 = 0;
    Vec40* v = &v28;
    v->DestroyRange(v->mpBegin, v->mpEnd);
    if (v->mpBegin && ((int*)v->mpBegin)[-1] != 0)
        operator delete[](v->mpBegin);
    if (p014 && ((int*)p014)[-1] != 0)
        operator delete[](p014);
}

// @ 0x009dfda0
Vec44& Vec44::operator=(const Vec44& x)
{
    if (this != &x) {
        uint32 n = (uint32)(x.mpEnd - x.mpBegin);
        if (n > (uint32)(mpCapacity - mpBegin)) {
            Elem44* p = DoAllocate(n, x.mpBegin, x.mpEnd);
            if (mpBegin && ((int*)mpBegin)[-1] != 0)
                operator delete[](mpBegin);
            mpBegin = p;
            mpCapacity = p + n;
        } else {
            uint32 s = (uint32)(mpEnd - mpBegin);
            if (n > s) {
                CopyA(x.mpBegin, x.mpBegin + s, mpBegin);
                Elem44* tmp;
                UninitCopyBackA((void**)&tmp, x.mpBegin + s, x.mpEnd, mpEnd, x.mpEnd);
            } else {
                CopyA(x.mpBegin, x.mpEnd, mpBegin);
            }
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x009dffe0
Vec1C& Vec1C::operator=(const Vec1C& x)
{
    if (this != &x) {
        uint32 n = (uint32)(x.mpEnd - x.mpBegin);
        if (n > (uint32)(mpCapacity - mpBegin)) {
            Elem1C* p = DoAllocate(n, x.mpBegin, x.mpEnd);
            if (mpBegin && ((int*)mpBegin)[-1] != 0)
                operator delete[](mpBegin);
            mpBegin = p;
            mpCapacity = p + n;
        } else {
            uint32 s = (uint32)(mpEnd - mpBegin);
            if (n > s) {
                CopyC(x.mpBegin, x.mpBegin + s, mpBegin);
                Elem1C* tmp;
                UninitCopyBackC((void**)&tmp, x.mpBegin + s, x.mpEnd, mpEnd, x.mpEnd);
            } else {
                CopyC(x.mpBegin, x.mpEnd, mpBegin);
            }
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x009e0480
Elem0C* Vec0C::erase(Elem0C* first, Elem0C* last)
{
    Elem0C* end = mpEnd;
    Elem0C* dst = first;
    for (Elem0C* src = last; src != end; ++src, ++dst)
        *dst = *src;
    mpEnd -= (last - first);
    return first;
}

// @ 0x009e07d0
ElemA4* DestroyRangeA4(ElemA4* first, ElemA4* last, ElemA4* result)
{
    while (first != last) {
        first->v24.DestroyRange(first->v24.mpBegin, first->v24.mpEnd);
        if (first->v24.mpBegin && ((int*)first->v24.mpBegin)[-1] != 0)
            operator delete[](first->v24.mpBegin);
        if (first->v10.mpBegin && ((int*)first->v10.mpBegin)[-1] != 0)
            operator delete[](first->v10.mpBegin);
        ++first;
        ++result;
    }
    return result;
}

// @ 0x009e0940
void Vec44::clear()
{
    Elem44* first = mpBegin;
    Elem44* last = mpEnd;
    CopyA(last, mpEnd, first);
    mpEnd -= (last - first);
}

// @ 0x009e0980
void Vec58::clear()
{
    Elem58* first = mpBegin;
    Elem58* last = mpEnd;
    CopyB(last, mpEnd, first);
    mpEnd -= (last - first);
}

// @ 0x009e09c0
void Vec1C::clear()
{
    Elem1C* first = mpBegin;
    Elem1C* last = mpEnd;
    CopyC(last, mpEnd, first);
    mpEnd -= (last - first);
}

// @ 0x009e0a00
void Vec0C::resize(uint32 n, const Elem0C& value)
{
    if (n > (uint32)(mpCapacity - mpBegin)) {
        Vec0C tmp;
        tmp.Construct(n, &value, &mPad[0]);
        Swap(tmp);
        if (tmp.mpBegin && ((int*)tmp.mpBegin)[-1] != 0)
            operator delete[](tmp.mpBegin);
        return;
    }
    if (n > (uint32)(mpEnd - mpBegin)) {
        Fill0C(mpBegin, mpEnd, &value);
        FillN0C(mpEnd, n - (uint32)(mpEnd - mpBegin), &value);
        mpEnd += (n - (uint32)(mpEnd - mpBegin));
        return;
    }
    FillN0Cb(mpBegin, n, &value);
    erase(mpBegin + n, mpEnd);
}

// @ 0x009e0b20
Elem0CS* Vec0CS::insert(Elem0CS* position, const Elem0CS& value)
{
    int i = (int)(position - mpBegin);
    if (position == mpEnd && mpEnd != mpCapacity) {
        Elem0CS* p = mpEnd;
        mpEnd = mpEnd + 1;
        if (p != 0) {
            p->a = value.a;
            p->b = value.b;
            p->c = value.c;
        }
        return mpBegin + i;
    }
    DoInsertValue(position, value);
    return mpBegin + i;
}

// @ 0x009e0b90
void __stdcall DestroyRangeA4n(ElemA4* first, ElemA4* last)
{
    if (first >= last)
        return;
    uint32 count = ((uint32)((char*)last - (char*)first) - 1) / 0xa4 + 1;
    do {
        first->v24.DestroyRange(first->v24.mpBegin, first->v24.mpEnd);
        if (first->v24.mpBegin && ((int*)first->v24.mpBegin)[-1] != 0)
            operator delete[](first->v24.mpBegin);
        if (first->v10.mpBegin && ((int*)first->v10.mpBegin)[-1] != 0)
            operator delete[](first->v10.mpBegin);
        ++first;
        --count;
    } while (count != 0);
}

// @ 0x009e0cd0
Elem40* Copy40(Elem40* first, Elem40* last, Elem40* result)
{
    for (; first != last; ++first, ++result) {
        if (result != first)
            *result = *first;
    }
    return result;
}

// @ 0x009e0d30
Elem40* CopyBack40(Elem40* first, Elem40* last, Elem40* result)
{
    while (last != first) {
        --last;
        --result;
        if (result != last)
            *result = *last;
    }
    return result;
}

// @ 0x009e0d90
void Outer::AddGait(void* arg)
{
    Record* rec = (Record*)hC->val;
    switch (rec->kind) {
    case 0: {
        void** a = ((CArgs*)arg)->MainArguments(6);
        for (int off = 0x88; off < 0xb8; off += 0x10)
            for (int j = 0; j < 2; j++)
                *(float*)((char*)hC->val + off + 4 * j) =
                    ((float (__thiscall*)(void*, void*))(*(void***)eval)[0x98 / 4])(eval, *(a++));
        rec->gait.a.push_back(rec->gaitA);
        break;
    }
    case 1: {
        void** a = ((CArgs*)arg)->MainArguments(8);
        for (int off = 0x34; off < 0x74; off += 0x10)
            for (int j = 0; j < 2; j++)
                *(float*)((char*)hC->val + off + 4 * j) =
                    ((float (__thiscall*)(void*, void*))(*(void***)eval)[0x98 / 4])(eval, *(a++));
        rec->gait.b.push_back(rec->gaitB);
        break;
    }
    case 2: {
        void** a = ((CArgs*)arg)->MainArguments(2);
        for (int off = 0xc; off < 0x14; off += 4)
            *(float*)((char*)hC->val + off) =
                ((float (__thiscall*)(void*, void*))(*(void***)eval)[0x98 / 4])(eval, *(void**)((char*)a + off - 0xc));
        rec->gait.c.push_back(rec->gaitC);
        break;
    }
    }
}

// @ 0x009e0f80
void Outer::AddItem(void* arg)
{
    void** a = ((CArgs*)arg)->MainArguments(1);
    Record* rec = (Record*)hC->val;
    rec->item.b = ((float (__thiscall*)(void*, void*))(*(void***)eval)[0x98 / 4])(eval, a[0]);
    rec->items.push_back(rec->item);
}

// @ 0x009e0ff0
void Outer::PushFlag(bool flag)
{
    if (!flag)
        h30->v1.push_back(h30->val);
}

// @ 0x009e1030
Gait_s009e_0d90::Gait_s009e_0d90()
{
    float f = g_gait_default_id;
    id = (int)f;
    CopyA(a.e, a.e, a.b);
    a.e += a.e - a.b;
    CopyB(b.e, b.e, b.b);
    b.e += b.e - b.b;
    CopyC(c.e, c.e, c.b);
    c.e += c.e - c.b;
}

// @ 0x009e1100
Gait_s009e_0d90::Gait_s009e_0d90(const Gait_s009e_0d90& o)
{
    id = o.id;
    a = o.a;
    b = o.b;
    c = o.c;
}

// @ 0x009e1160
void Inner_s009e_0d90::AssignItemsN(const Inner_s009e_0d90* o, uint32 n)
{
    uint32 myCount = (uint32)(items.e - items.b);
    uint32 oCount  = (uint32)(o->items.e - o->items.b);
    uint32 cp = myCount < oCount ? myCount : oCount;
    for (uint32 i = 0; i < cp; i++)
        items.b[i] = o->items.b[i];
    uint32 m = oCount < n ? oCount : n;
    items.reserve((int)m);
    for (uint32 i = cp; i < m; i++)
        items.push_back(o->items.b[i]);
}

// @ 0x009e1260
void Inner_s009e_0d90::AssignItemsF(const Inner_s009e_0d90* o, uint32 flags)
{
    uint32 myCount = (uint32)(items.e - items.b);
    uint32 oCount  = (uint32)(o->items.e - o->items.b);
    uint32 cp = myCount < oCount ? myCount : oCount;
    if (oCount < myCount) {
        for (uint32 i = oCount; i < myCount; i++)
            --items.e;
    }
    if (!(flags & 2)) {
        for (uint32 i = 0; i < cp; i++)
            items.b[i] = o->items.b[i];
    }
    items.reserve((int)oCount);
    for (uint32 i = cp; i < oCount; i++)
        items.push_back(o->items.b[i]);
}

// @ 0x009e1370
void Inner_s009e_0d90::AssignItems(const Inner_s009e_0d90* o)
{
    uint32 myCount = (uint32)(items.e - items.b);
    uint32 oCount  = (uint32)(o->items.e - o->items.b);
    uint32 cp = myCount < oCount ? myCount : oCount;
    if (oCount < myCount) {
        for (uint32 i = oCount; i < myCount; i++)
            --items.e;
    }
    for (uint32 i = 0; i < cp; i++)
        items.b[i] = o->items.b[i];
    items.reserve((int)oCount);
    for (uint32 i = cp; i < oCount; i++)
        items.push_back(o->items.b[i]);
}

// @ 0x009e1470
void Inner_s009e_0d90::Combine(const Inner_s009e_0d90* a, float f, const Inner_s009e_0d90* b)
{
    f8 = a->f8 < b->f8 ? b->f8 : a->f8;

    uint32 myCount = (uint32)(items.e - items.b);
    uint32 aCount  = (uint32)(a->items.e - a->items.b);
    uint32 bCount  = (uint32)(b->items.e - b->items.b);
    uint32 m = aCount < bCount ? aCount : bCount;
    uint32 n = m < myCount ? m : myCount;

    if (m < myCount) {
        for (uint32 i = m; i < myCount; i++)
            --items.e;
    }
    if (!(f0 & 2)) {
        for (uint32 i = 0; i < n; i++)
            ((Combiner*)this)->Combine5(&items.b[i], i, a, f, b);
    }
    items.reserve((int)m);
    for (uint32 i = myCount; i < m; i++) {
        Item it;
        it.a = 0.0f;
        it.b = 0.5f;
        it.c = 0;
        ((Combiner*)this)->Combine5(&it, i, a, f, b);
        items.push_back(it);
    }
}

// @ 0x009e1610
void ItemArr::Add(const GaitItem_s009e_0d90* value)
{
    uint32 count = this->count;
    uint32 i = 0;
    for (; i < count; i++) {
        if (!(v.b[i].a < value->a))
            break;
    }
    if (i < count && v.b[i].a == value->a) {
        v.b[i] = *value;
    } else {
        v.insert(v.b + i, *value);
        this->count++;
    }
}

// @ 0x009e1690
Gait_s009e_0d90* UninitCopyGait(const Gait_s009e_0d90* first, const Gait_s009e_0d90* last, Gait_s009e_0d90* result)
{
    while (first != last) {
        result->a.b = result->a.e = result->a.cap = 0;
        result->b.b = result->b.e = result->b.cap = 0;
        result->c.b = result->c.e = result->c.cap = 0;
        result->id = first->id;
        result->a = first->a;
        result->b = first->b;
        result->c = first->c;
        ++first;
        ++result;
    }
    return result;
}

// @ 0x009e1710
RecBlob::~RecBlob()
{
    ((VRange*)&vb)->DestroyRangeA4n(vb, ve);
    if (vb && ((int*)vb)[-1] != 0)
        operator delete[](vb);
    if (p04 && ((int*)p04)[-1] != 0)
        operator delete[](p04);
}

// @ 0x009e1760
void ItemArr::Build(const void* src)
{
    const uint32 n = *(const uint32*)((const char*)src + 0x10);
    const RPair* pairs = (const RPair*)((const char*)src + 0x18);
    v.reserve((int)n);
    for (uint32 i = 0; i < n; i++) {
        GaitItem_s009e_0d90 it;
        it.a = pairs[i].a;
        it.b = pairs[i].b;
        Add(&it);
    }
}

// @ 0x009e17d0
void** RBTree::find_or_insert(volatile const uint32* key)
{
    RBNode* sentinel = (RBNode*)((char*)this + 4);
    RBNode* x = root;
    RBNode* y = sentinel;
    uint32 k = *key;
    while (x) {
        if (x->key >= k) {
            y = x;
            x = x->c4;
        } else {
            x = x->c0;
        }
    }
    if (y != sentinel && y->key <= k)
        return &y->value;

    RBNode* n = y;
    RBNode* saved = y;
    uint32 kc[2] = { k, 0 };
    const volatile uint32* kp = key;
    ((RBTree0*)this)->Insert(&n, saved, kc, (int)(size_t)kp);
    return &n->value;
}

// @ 0x009e1850
void* __stdcall FindOrCreate(const char* name, uint32 hash)
{
    RBTree* map = (RBTree*)g_name_map;
    RBNode* out = (RBNode*)((char*)map + 4);
    RBNode** pout = &out;
    const char* nm = name;
    map->FindNode(pout, (const uint32*)&hash);
    if (out != (RBNode*)((char*)map + 4)) {
        void* v = out->value;
        if (v)
            return v;
    }
    void* obj = CreateByName(hash);
    if (obj) {
        void** slot = map->find_or_insert(&hash);
        *slot = obj;
        return obj;
    }
    return 0;
}

// @ 0x009e18c0
bool nSPCreatureAnim::gait_record::LoadGaitFile(char const * name, nSPCreatureAnim::dynamics_phasegroup * a1, int a2)
{
    uint32 h = HashName(name, 0x811c9dc5u, 1);
    return FindOrCreate(name, h);
}

// @ 0x009e1b40
void Outer::Select(void* arg)
{
    Record* rec = (Record*)hC->val;
    int aCount = (int)(rec->gait.a.e - rec->gait.a.b);
    int bCount = (int)(rec->gait.b.e - rec->gait.b.b);
    int cCount = (int)(rec->gait.c.e - rec->gait.c.b);
    if (aCount < rec->maxA) {
        rec->kind = 0;
    } else if (bCount < rec->maxB) {
        rec->kind = 1;
    } else if (cCount < rec->maxC) {
        rec->kind = 2;
    } else {
        rec->gaits.push_back(rec->gait);
        rec->gait.a.clear();
        rec->gait.b.clear();
        rec->gait.c.clear();
        rec->kind = 0;
    }

    void** a = ((CArgs*)arg)->MainArguments(1);
    float fv = ((float (__thiscall*)(void*, void*))(*(void***)eval)[0x98 / 4])(eval, a[0]);
    int id = (int)fv;

    int k = rec->kind;
    if (k == 0)
        rec->gaitA.id = id;
    else if (k == 1)
        rec->gaitB.id = id;
    else
        rec->gaitC.id = id;
}

// @ 0x009e1cd0
void Outer::PushGait(bool flag)
{
    if (flag)
        return;
    Record* rec = (Record*)h30->val;
    if (rec->flag == 0) {
        h30->v2.push_back(h30->val);
        return;
    }
    rec->gaits.push_back(rec->gait);
    h30->v2.push_back(h30->val);
    rec->gait.a.clear();
    rec->gait.b.clear();
    rec->gait.c.clear();
}

// @ 0x009e1df0
Inner_s009e_1df0::Inner_s009e_1df0()
: f0(0), f4(g_1550b20), f8(-1), items(), gaits()
{
    p[0]  = g_1550b24;
    p[1]  = g_166c024;
    p[2]  = g_166c028;
    p[3]  = g_166c02c;
    p[4]  = g_1550b2c;
    p[5]  = g_1550b30;
    p[6]  = g_1550b34;
    p[7]  = g_1550b38;
    p[8]  = g_1550b3c;
    p[9]  = g_166c030;
    p[10] = g_1550b40;
    p[11] = g_166c034;
    p[12] = g_1550b44;
    p[13] = g_166c038;
    p[14] = g_1550b48;
    p[15] = g_1550b4c;
    p[16] = g_166c03c;
    p[17] = g_166c040;
    p[18] = g_1550b50;
    p[19] = g_1550b54;
    p[20] = g_1550b58;
    p[21] = g_1550b5c;
    p[22] = g_166c044;
    p[23] = g_1550b60;
    p[24] = g_1550b64;
    p[25] = g_1550b68;
    flag = true;

    items.erase(items.b, items.e);
    if (g_15515dc) {
        int last = (int)gaits.e;
        int first = (int)gaits.b;
        Gait_s009e_1df0* t = Copy40(gaits.e, gaits.e, gaits.b);
        gaits.destroy(t, gaits.e);
        gaits.e = (Gait_s009e_1df0*)((int)gaits.e + ((last - first) >> 6) * -0x40);
    }
}

// @ 0x009e1fe0
void Inner_s009e_1df0::AssignGaitsN(const Inner_s009e_1df0* o, uint32 n)
{
    VecG& g = gaits;
    uint32 myCount = (uint32)(g.e - g.b);
    uint32 oCount  = (uint32)(o->gaits.e - o->gaits.b);
    uint32 cp  = emin(myCount, oCount);
    uint32 lim = emin(n, oCount);
    for (uint32 i = 0; i < cp; i++)
        g.b[i] = o->gaits.b[i];
    g.reserve((int)lim);
    for (uint32 i = cp; i < lim; i++)
        g.push_back(o->gaits.b[i]);
}

// @ 0x009e2140
void Inner_s009e_1df0::AssignGaitsF(const Inner_s009e_1df0* o, uint32 flags)
{
    uint32 myCount = (uint32)(gaits.e - gaits.b);
    uint32 oCount  = (uint32)(o->gaits.e - o->gaits.b);
    uint32 cp = emin(myCount, oCount);
    if (oCount < myCount) {
        for (uint32 i = oCount; i < myCount; i++)
            gaits.pop_back();
    }
    if (!(flags & 0x4000000)) {
        for (uint32 i = 0; i < cp; i++)
            gaits.b[i] = o->gaits.b[i];
    }
    gaits.reserve((int)oCount);
    for (uint32 i = cp; i < oCount; i++)
        gaits.push_back(o->gaits.b[i]);
}

// @ 0x009e22f0
void Inner_s009e_1df0::AssignGaits(const Inner_s009e_1df0* o)
{
    uint32 myCount = (uint32)(gaits.e - gaits.b);
    uint32 oCount  = (uint32)(o->gaits.e - o->gaits.b);
    uint32 cp = emin(myCount, oCount);
    if (oCount < myCount) {
        for (uint32 i = oCount; i < myCount; i++)
            gaits.pop_back();
    }
    for (uint32 i = 0; i < cp; i++)
        gaits.b[i] = o->gaits.b[i];
    gaits.reserve((int)oCount);
    for (uint32 i = cp; i < oCount; i++)
        gaits.push_back(o->gaits.b[i]);
}

// @ 0x009e2490
void __stdcall BuildGaits(Table_s009e_2490* t)
{
    if (!t) return;
    int count = t->count;
    if (count == 0) return;
    for (int i = 0; i < count; i++) {
        Inner_s009e_2490* en = &t->entries[i].in;
        if ((int)((char*)en->gaits.e - (char*)en->gaits.b) & ~0x3f) continue;
        int n = (int)(en->ie - en->ib);
        en->gaits.reserve(n);
        for (int j = 0; j < n; j++) {
            float s84 = (float)sqrt(0.84f);
            float s91 = (float)sqrt(0.91f);
            Gait_s009e_2490 g;
            g.a.clear2();
            g.a.push_back(GaitA_s009e_2490(0, 0.0f, 1.0f, 0.0f));
            g.a.push_back(GaitA_s009e_2490(0x19, 0.0f, 0.0f, 1.0f));
            g.a.push_back(GaitA_s009e_2490(0x32, 0.0f, -1.0f, 0.0f));
            {
                GaitA_s009e_2490* last = g.a.e - 1;
                for (int k = 0; k < 3; k++) { last->s[k].c = true; last->s[k].d = true; last->s[k].e = 1; }
            }
            g.a.push_back(GaitA_s009e_2490(100, 0.0f, 1.0f, 0.0f));
            g.b.clear2();
            g.b.push_back(GaitB_s009e_2490(0, 1e-6f, 1e-6f, 1e-6f, 0.999999f));
            g.b.push_back(GaitB_s009e_2490(0xc, 0.4f, 1e-6f, 1e-6f, s84));
            g.b.push_back(GaitB_s009e_2490(0x19, 1e-6f, 1e-6f, 1e-6f, 0.999999f));
            g.b.push_back(GaitB_s009e_2490(0x26, -0.3f, 1e-6f, 1e-6f, s91));
            g.b.push_back(GaitB_s009e_2490(0x32, 1e-6f, 1e-6f, 1e-6f, 0.999999f));
            g.b.push_back(GaitB_s009e_2490(100, 1e-6f, 1e-6f, 1e-6f, 0.999999f));
            g.c.clear();
            g.c.push_back(GaitC_s009e_2490(0, 0.5f));
            g.c.push_back(GaitC_s009e_2490(5, 0.75f));
            g.c.push_back(GaitC_s009e_2490(0x19, 0.05f));
            g.c.push_back(GaitC_s009e_2490(0x2d, 0.75f));
            g.c.push_back(GaitC_s009e_2490(0x32, 0.5f));
            {
                GaitC_s009e_2490* last = g.c.e - 1;
                last->c0 = true; last->c1 = true; last->c2 = 1;
            }
            g.c.push_back(GaitC_s009e_2490(100, 0.5f));
            en->gaits.push_back(g);
        }
    }
    for (int i = 0; i < count; i++) {
        Inner_s009e_2490* en = &t->entries[i].in;
        int n = (int)(en->ie - en->ib);
        for (int j = 0; j < n; j++) en->ib[j].idx = j;
    }
}

// @ 0x009e3580
Anim::gcmdd::gcmdd()
: GaitC_s009e_3580(), b(), a(), path(), gait(),
      f110(0.0f), f114(g_Half), i118(0),
      inner(), f1bc(g_ChannelGain), f1c0(true), f1c4(0.0f)
{
}

// @ 0x009e3740
void gcmddHost::Create(int /*unused*/)
{
    void* mem = EAAllocate(0x1c8, "Anim/gcmdd", 0, 0, 0, 0);
    Anim::gcmdd* g = mem ? new (mem) Anim::gcmdd() : 0;
    *(Anim::gcmdd**)((char*)*(void**)((char*)this + 0x30) + 4) = g;
    void* obj = *(void**)((char*)this + 4);
    void** vt = *(void***)obj;
    ((void (__thiscall*)(void*, void*))vt[0x23])(obj, this);
}

// @ 0x009e3790
Inner_s009e_3580& Inner_s009e_3580::operator=(const Inner_s009e_3580& o)
{
    if (this != &o) {
        Assign(&o);
        AssignItems(&o);
        if (g_1515dc) AssignGaits(&o);
    }
    return *this;
}

// @ 0x009e37c0
void Inner_s009e_3580::Blend(const Inner_s009e_3580* a, float t, const Inner_s009e_3580* b)
{
    if (a->f8 == -1) {
        *this = *b;
        return;
    }
    if (b->f8 == -1) {
        *this = *a;
        return;
    }

    if (!g_1515dc && !(f0 & 0x1))
        f4 = (b->f4 - a->f4) * t + a->f4;

    BlendKeys(a, t, b);

    if (!(f0 & 0x4))       p[0]  = (b->p[0]  - a->p[0])  * t + a->p[0];
    if (!(f0 & 0x8))       p[1]  = (b->p[1]  - a->p[1])  * t + a->p[1];
    if (!(f0 & 0x10))      p[2]  = (b->p[2]  - a->p[2])  * t + a->p[2];
    if (!(f0 & 0x20))      p[3]  = (b->p[3]  - a->p[3])  * t + a->p[3];
    if (!(f0 & 0x40))      p[4]  = (b->p[4]  - a->p[4])  * t + a->p[4];
    if (!(f0 & 0x80))      p[5]  = (b->p[5]  - a->p[5])  * t + a->p[5];
    if (!(f0 & 0x100))     p[6]  = (b->p[6]  - a->p[6])  * t + a->p[6];
    if (!(f0 & 0x200))     p[7]  = (b->p[7]  - a->p[7])  * t + a->p[7];
    if (!(f0 & 0x400))     p[8]  = (b->p[8]  - a->p[8])  * t + a->p[8];
    if (!(f0 & 0x800))     p[9]  = (b->p[9]  - a->p[9])  * t + a->p[9];
    if (!(f0 & 0x1000))    p[10] = (b->p[10] - a->p[10]) * t + a->p[10];
    if (!(f0 & 0x2000000)) p[11] = (b->p[11] - a->p[11]) * t + a->p[11];

    if (!(f0 & 0x2000)) {
        float v = (float)(WrapRange(b->p[12] - a->p[12], 1.0f) * (double)t + (double)a->p[12]);
        p[12] = v - (float)iat_floor((double)v);
    }
    if (!(f0 & 0x4000)) {
        float v = (float)(WrapRange(b->p[13] - a->p[13], 1.0f) * (double)t + (double)a->p[13]);
        p[13] = v - (float)iat_floor((double)v);
    }
    if (!(f0 & 0x8000)) {
        float v = (float)(WrapRange(b->p[14] - a->p[14], 1.0f) * (double)t + (double)a->p[14]);
        p[14] = v - (float)iat_floor((double)v);
    }

    if (!(f0 & 0x10000))     p[15] = (b->p[15] - a->p[15]) * t + a->p[15];
    if (!(f0 & 0x8000000))   p[16] = (b->p[16] - a->p[16]) * t + a->p[16];
    if (!(f0 & 0x10000000))  p[17] = (b->p[17] - a->p[17]) * t + a->p[17];
    if (!(f0 & 0x20000))     p[18] = (b->p[18] - a->p[18]) * t + a->p[18];
    if (!(f0 & 0x40000))     p[19] = (b->p[19] - a->p[19]) * t + a->p[19];

    if (!(f0 & 0x80000)) {
        float v = (float)(WrapRange(b->p[20] - a->p[20], 1.0f) * (double)t + (double)a->p[20]);
        p[20] = v - (float)iat_floor((double)v);
    }
    if (!(f0 & 0x100000)) {
        float v = (float)(WrapRange(b->p[21] - a->p[21], 1.0f) * (double)t + (double)a->p[21]);
        p[21] = v - (float)iat_floor((double)v);
    }
    if (!(f0 & 0x200000)) {
        float v = (float)(WrapRange(b->p[22] - a->p[22], 1.0f) * (double)t + (double)a->p[22]);
        p[22] = v - (float)iat_floor((double)v);
    }

    if (!(f0 & 0x400000))    p[23] = (b->p[23] - a->p[23]) * t + a->p[23];
    if (!(f0 & 0x800000))    p[24] = (b->p[24] - a->p[24]) * t + a->p[24];
    if (!(f0 & 0x1000000))   p[25] = (b->p[25] - a->p[25]) * t + a->p[25];
}

// @ 0x009e3cf0
Channel::Channel()
: gain(g_ChannelGain), on(true), in()
{
    ChannelHead head;
    *(ChannelHead*)this = head;
    Inner_s009e_3580 def;
    in = def;
    tail.b = 0;
    tail.e = 0;
    tail.cap = 0;
}

// @ 0x009e3de0
void Channel::Reset()
{
    ChannelHead head;
    *(ChannelHead*)this = head;
    Inner_s009e_3580 def;
    in = def;
    tail.b = 0;
    if (tail.e) tail.e = 0;
    if (tail.cap) tail.cap = 0;
}

// @ 0x009e3ec0
gcmddTable::gcmddTable()
: m00(0), m13c(0), channels(), inner()
{
    for (int a = 0; a < 6; a++) {
        for (int k = 0; k < 4; k++) {
            mB[a][k] = 0.0f;
            mC[a][k] = 0.0f;
            mA[a][k] = 0;
            channels[a * 4 + k].Reset();
        }
        m04[a] = 0;
    }
}

// @ 0x009e3f70
void gcmddTable::Reset(int n, int m)
{
    if (n > 0) {
        for (int a = 0; a < n; a++) {
            for (int k = 0; k < m; k++) {
                mB[a][k] = 0.0f;
                mC[a][k] = 0.0f;
                if (mA[a][k] != 0) mA[a][k] = 0;
                channels[a * 4 + k].Reset();
            }
            m04[a] = 0;
        }
    }
    m13c = 0;
}

// @ 0x009e4030
void EntryArr_s009e_3580::Sample(float key, Inner_s009e_3580* out)
{
    unsigned count = this->count;
    unsigned prev = 0;
    unsigned i = 0;

    if (count != 0) {
        for (; i < count; i++) {
            if (key < v.b[i].key)
                break;
            prev = i;
        }
        if (i != 0 && i != count) {
            Entry_s009e_3580* e0 = &v.b[prev];
            Entry_s009e_3580* e1 = &v.b[i];
            out->Blend(&e0->in, (key - e0->key) / (e1->key - e0->key), &e1->in);
            goto tail;
        }
    }
    *out = v.b[prev].in;
tail:
    out->flag = key == v.b[prev].key;
}

// @ 0x009e4120
Inner_s009e_3580::Inner_s009e_3580(const Inner_s009e_3580& o)
{
    items.b = items.e = items.cap = 0;
    gaits.b = gaits.e = gaits.cap = 0;
    Assign(&o);
    AssignItems(&o);
    if (g_1515dc) AssignGaits(&o);
}

// @ 0x009e4170
void EntryConstructN(Entry_s009e_3580* dst, unsigned n, const Entry_s009e_3580* src)
{
    for (; n != 0; n--, dst++) {
        if (dst) {
            dst->key = src->key;
            dst->in.items.b = dst->in.items.e = dst->in.items.cap = 0;
            dst->in.gaits.b = dst->in.gaits.e = dst->in.gaits.cap = 0;
            dst->in.Assign(&src->in);
            dst->in.AssignItems(&src->in);
            if (g_1515dc) dst->in.AssignGaits(&src->in);
        }
    }
}

// @ 0x009e41e0
void EntryAssignRange(Entry_s009e_3580* first, Entry_s009e_3580* last, Entry_s009e_3580* dst)
{
    for (; first != last; first++, dst++) {
        if (dst) {
            dst->key = first->key;
            if (&dst->in != &first->in) {
                dst->in.Assign(&first->in);
                dst->in.AssignItems(&first->in);
                if (g_1515dc) dst->in.AssignGaits(&first->in);
            }
        }
    }
}

// @ 0x009e4260
Entry_s009e_3580* EntryCopy(Entry_s009e_3580* first, Entry_s009e_3580* last, Entry_s009e_3580* dst)
{
    for (; first != last; first++, dst++) {
        dst->key = first->key;
        if (&dst->in != &first->in) {
            dst->in.Assign(&first->in);
            dst->in.AssignItems(&first->in);
            if (g_1515dc) dst->in.AssignGaits(&first->in);
        }
    }
    return dst;
}

// @ 0x009e42d0
Entry_s009e_3580* EntryCopyBackward(Entry_s009e_3580* first, Entry_s009e_3580* last, Entry_s009e_3580* dstEnd)
{
    while (last != first) {
        --last;
        --dstEnd;
        dstEnd->key = last->key;
        if (&dstEnd->in != &last->in) {
            dstEnd->in.Assign(&last->in);
            dstEnd->in.AssignItems(&last->in);
            if (g_1515dc) dstEnd->in.AssignGaits(&last->in);
        }
    }
    return dstEnd;
}

// @ 0x009e4350
Inner_s009e_3580::Inner_s009e_3580(int index, int count)
: items(), gaits()
{
    *this = Inner_s009e_3580();
    f8 = index;
    items.reserve(count);
    Item def = {0.0f, 0.5f, 0};
    items.resize(count, def);
    if (g_1515dc) gaits.reserve(count);
}

// @ 0x009e4450
void GaitTable::Sample(float t, int lane, bool first, unsigned mask)
{
    if (!first && mCurves[0][lane] != 0) {
        CurveOut_s009e_4450 out;
        out.v = g_ChannelGain;
        out.flag = true;
        ((Curve_s009e_4450*)mCurves[0][lane])->Eval(t, &out);
        *(CurveOut_s009e_4450*)&channels[lane].gain = out;
    }

    if (mGroups <= 0) return;

    CurveNode** pp = &mCurves[0][lane];
    Channel_s009e_4450*    ch = channels + lane;
    int k = 0;
    do {
        CurveNode* node = *pp;
        if (node != 0) {
            if ((ch->in.f0 & 0x4000000) == 0) {
                ch->tail.gain = node->arr.Lookup(t, &ch->tail.a);
            }
            if (g_1515dc != 0 && ch->ValidBlocks()) {
                inner.Blend(ch->tail.a, ch->tail.gain, ch->tail.b);
                if (ch->tail.gain == g_Zero || ch->tail.gain == g_One) {
                    inner.flag = true;
                } else {
                    inner.flag = false;
                }
            } else {
                node->arr.Sample(t, &inner);
            }
            if (mask != 0) {
                ch->in.CopyMasked(&inner, mask);
                ch->in.CopyItems(&inner, mask);
                if (g_1515dc != 0) ch->in.AssignGaitsF(&inner, mask);
            } else {
                ch->in.Assign(&inner);
                ch->in.AssignItems(&inner);
                if (g_1515dc != 0) ch->in.AssignGaits(&inner);
            }
            ch->in.f0 = (int)mask;
        }
        pp += 4;
        ch += 4;
        k++;
    } while (k < mGroups);
}

// @ 0x009e4600
void GaitTable::SampleAt(float a0, float a1, float a2, int a3, int a4, int a5, int lane)
{
    float v = CurveClamp2(&a0);
    Sample(v, lane, false, 0);
}

// @ 0x009e4630
VecEntry::VecEntry(unsigned n, const Entry_s009e_4450& v)
{
    Entry_s009e_4450* p;
    if (n != 0) {
        p = (Entry_s009e_4450*)EAAllocate(n * 0xa4, "Anim/gait/untagged", 0, 0, &g_alloc, 0xd1);
    } else {
        p = 0;
    }
    cap = p + n;
    b = p;
    e = p;
    {
        Entry_s009e_4450 def;
        int extra;
        EntryConstructN(b, n, &def, extra);
    }
    e = b + n;
}

// @ 0x009e47c0
void VecEntry::realloc_insert(Entry_s009e_4450* pos, const Entry_s009e_4450& value)
{
    if (e != cap) {
        Entry_s009e_4450* val = (Entry_s009e_4450*)&value;
        if (val >= pos && val < e) {
            val = val + 1;
        }
        if (e != 0) {
            new (e) Entry_s009e_4450(*(e - 1));
        }
        EntryCopyBackward(pos, e - 1, e);
        pos->key = val->key;
        Inner_s009e_4450* dst = &pos->in;
        const Inner_s009e_4450* src = &val->in;
        if (dst != src) {
            dst->Assign(src);
            dst->AssignItems(src);
            if (g_1515dc != 0) dst->AssignGaits(src);
        }
        e = e + 1;
        return;
    }

    int old = (int)(e - b);
    int ncap;
    if (old == 0) {
        ncap = 1;
    } else {
        ncap = old * 2;
    }
    Entry_s009e_4450* buf;
    if (ncap == 0) {
        buf = 0;
    } else {
        buf = (Entry_s009e_4450*)EAAllocate(ncap * 0xa4, "Anim/gait/untagged", 0, 0, &g_alloc, 0xd1);
    }
    Entry_s009e_4450* p = EntryAssignRange(b, pos, buf);
    DestroyRangeA4(b, pos, buf);
    if (p) {
        new (p) Entry_s009e_4450(value);
    }
    Entry_s009e_4450* q = EntryAssignRange(pos, e, p + 1);
    DestroyRangeA4(pos, e, p + 1);
    if (b && ((int*)b)[-1]) operator delete[](b);
    b = buf;
    e = q;
    cap = buf + ncap;
}

// @ 0x009e4940
void EntryArr_s009e_4450::Reset()
{
    VecEntry* vec = &v;
    Entry_s009e_4450* first = vec->b;
    Entry_s009e_4450* last  = vec->e;
    Entry_s009e_4450* r = EntryCopy(last, last, first);
    vec->destroyRange(r, vec->e);
    vec->e -= last - first;
    count = 0;
}

// @ 0x009e4990
Entry_s009e_4450* VecEntry::insert(Entry_s009e_4450* pos, const Entry_s009e_4450& value)
{
    unsigned idx = (unsigned)(pos - b);
    Entry_s009e_4450* slot = e;
    if (pos == slot && slot != cap) {
        e = slot + 1;
        if (slot) {
            new (slot) Entry_s009e_4450(value);
        }
    } else {
        realloc_insert(pos, value);
    }
    return b + idx;
}

// @ 0x009e4a00
void EntryArr_s009e_4450::Insert(const Entry_s009e_4450* val)
{
    unsigned n = count;
    unsigned i = 0;
    if (n != 0) {
        Entry_s009e_4450* p = v.b;
        do {
            if (p->key >= val->key) break;
            i++;
            p++;
        } while (i < n);
    }
    if (i < n) {
        Entry_s009e_4450* p = v.b + i;
        float key = val->key;
        if (p->key == key) {
            p->key = key;
            const Inner_s009e_4450* src = &val->in;
            if (&p->in != src) {
                p->in.Assign(src);
                p->in.AssignItems(src);
                if (g_1515dc != 0) p->in.AssignGaits(src);
            }
            return;
        }
    }
    v.insert(v.b + i, *val);
    count++;
}

// @ 0x009e4aa0
void Gcmdst::ResetDefault()
{
    v.erase(v.b, v.e);

    Elem0C_s009e_4450 elem;
    elem.v0 = 0.0f;
    elem.v1 = 0.8f;
    elem.flag = true;

    count = 0;
    AddElem(elem);
    arr.Reset();

    Inner_s009e_4450 tmpA;
    Entry_s009e_4450 tmp;
    tmp.in.Assign(&tmpA);
    tmp.in.AssignItems(&tmpA);
    if (g_1515dc != 0) tmp.in.AssignGaits(&tmpA);
    arr.Insert(&tmp);
}

// @ 0x009e4c00
void Gcmdst::BuildFromSource(const void* src)
{
    char* s = (char*)src;

    unsigned n = (unsigned)((*(int*)(s + 0x0c) - *(int*)(s + 0x08)) >> 2);
    v.reserve((int)n);
    for (unsigned i = 0; i < n; i++) {
        char* e = *(char**)(*(int*)(s + 0x08) + i * 4);
        Elem0C_s009e_4450 elem;
        elem.v0 = *(float*)(e + 0x1c4);
        elem.v1 = *(float*)(e + 0x1bc);
        elem.flag = *(bool*)(e + 0x1c0);
        AddElem(elem);
    }

    unsigned m = (unsigned)((*(int*)(s + 0x20) - *(int*)(s + 0x1c)) >> 2);
    arr.v.reserve((int)m);
    for (unsigned j = 0; j < m; j++) {
        char* e = *(char**)(*(int*)(s + 0x1c) + j * 4);
        float key = *(float*)(e + 0x1c4);
        const Inner_s009e_4450* sin = (const Inner_s009e_4450*)(e + 0x11c);
        unsigned cnt = (unsigned)((*(int*)(e + 0x12c) - *(int*)(e + 0x128)) / 0xc);

        Inner_s009e_4450 a;
        a.Assign(sin);
        a.AssignItemsN(sin, cnt);
        if (g_1515dc != 0) a.AssignGaitsN(sin, cnt);

        Entry_s009e_4450 entry;
        entry.key = key;
        entry.in.Assign(&a);
        entry.in.AssignItems(&a);
        if (g_1515dc != 0) entry.in.AssignGaits(&a);
        arr.Insert(&entry);
    }
}

// @ 0x009e4e30
bool nSPCreatureAnim::gait_record_static_data::ReadFromText(char * a1, int a2)
{
    void* parser;
    Gcmdst* g = (Gcmdst*)EAAllocate(0x30, "Anim/gcmdst", 0, 0, 0, 0);
    if (g) {
        g->count = 0;
        g->v.b = g->v.e = g->v.cap = 0;
        g->arr.count = 0;
        g->arr.v.b = g->arr.v.e = g->arr.v.cap = 0;
    } else {
        g = 0;
    }

    parser = ArgScriptCreateParser();
    if (parser) {
        void** vt = *(void***)parser;
        ((void (__thiscall*)(void*))vt[0])(parser);
        ((void (__thiscall*)(void*))vt[2])(parser);
        ((void (__thiscall*)(void*))vt[0x28 / 4])(parser);

        Gcmdst* k2 = (Gcmdst*)EAAllocate(0x34, "Anim/slkblkcmd", 0, 0, 0, 0);
        if (k2) { k2->count = 0; }
        ((void (__thiscall*)(void*, const char*))vt[0x14 / 4])(parser, "steplengthkey");

        Gcmdst* k3 = (Gcmdst*)EAAllocate(0x34, "Anim/ggkblkcmd", 0, 0, 0, 0);
        if (k3) { k3->count = 0; }
        ((void (__thiscall*)(void*, const char*))vt[0x14 / 4])(parser, "gaitgroupkey");

        ((void (__thiscall*)(void*))vt[0x30 / 4])(parser);
        ((void (__thiscall*)(void*, int))vt[0x34 / 4])(parser, 1);
        ((void (__thiscall*)(void*))vt[3])(parser);
        ((void (__thiscall*)(void*))vt[1])(parser);
    }

    if (g == 0) {
        return 0;
    }
    g->ResetDefault();
    return 0;
}

// @ 0x009e5070
void __thiscall Table::Load(const Src* s)
{
    arr.v.reserve(s->count);
    const Rec* r = (const Rec*)((const char*)s + 0x18 + s->n10 * 8);
    for (unsigned i = 0; i < s->count; i++) {
        float key = r->key;
        Inner in;
        in.f4 = r->f4;
        in.p[0] = r->p[0];
        in.p[1] = r->p[1];
        in.p[2] = r->p[2];
        in.p[3] = r->p[3];
        in.p[4] = r->p[4];
        in.p[5] = r->p[5];
        in.p[6] = r->p[6];
        in.p[7] = r->p[7];
        in.p[8] = r->p[8];
        in.p[9] = r->p[9];
        in.p[10] = r->p[10];
        in.p[11] = r->p[11];
        in.p[12] = r->p[12];
        in.p[13] = r->p[13];
        in.p[14] = r->p[14];
        in.p[15] = r->p[15];
        in.p[16] = r->p[16];
        in.p[17] = r->p[17];
        in.p[18] = r->p[18];
        in.p[19] = r->p[19];
        in.p[20] = r->p[20];
        in.p[21] = r->p[21];
        in.p[22] = r->p[22];
        in.p[23] = r->p[23];
        in.p[24] = r->p[24];
        in.p[25] = r->p[25];
        in.f8 = r->f8;
        in.flag = true;
        in.items.reserve(r->nItems);
        const RItem* ri = r->items;
        for (unsigned k = 0; k < r->nItems; k++, ri++) {
            Item it;
            it.a = ri->a;
            it.b = ri->b;
            it.c = 0;
            in.items.push_back(it);
        }
        in.gaits.reserve(r->nGaits);
        const GRec* gr = (const GRec*)ri;
        for (unsigned gi = 0; gi < r->nGaits; gi++) {
            Gait g;
            g.a.reserve(gr->nA);
            const char* q = (const char*)(gr + 1);
            for (unsigned k = 0; k < gr->nA; k++, q += sizeof(GaitA))
                g.a.push_back(*(const GaitA*)q);
            g.b.reserve(gr->nB);
            for (unsigned k = 0; k < gr->nB; k++, q += sizeof(GaitB))
                g.b.push_back(*(const GaitB*)q);
            g.c.reserve(gr->nC);
            for (unsigned k = 0; k < gr->nC; k++, q += sizeof(GaitC))
                g.c.push_back(*(const GaitC*)q);
            in.gaits.push_back(g);
            gr = (const GRec*)q;
        }
        Entry e;
        e.key = key;
        e.in.Assign(&in);
        e.in.AssignItems(&in);
        if (g_AssignGaits) e.in.AssignGaits(&in);
        arr.Insert(&e);
        r = (const Rec*)gr;
    }
}
