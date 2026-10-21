// src/game/SPCreatureAnim/gait_record.cpp -- migrated from slice(s) s009e5070, s009de8b0 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/gait_record.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/ArgScript/cIBlockCommand.h"
#include "EA/ArgScript/cICommand.h"

// ---- items of slice s009de8b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct cICommand_s009d_e8b0 {
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
struct cCommandBase_s009d_e8b0 : cICommand_s009d_e8b0 {
    cIParser_s009d_e8b0* mParser;                          // +0x04
    int mRefCount;                              // +0x08
    cCommandBase_s009d_e8b0();                             // 0x0083c800
};
}
}
namespace EA {
namespace ArgScript {
struct cIBlockCommand_s009d_e8b0 : cICommand_s009d_e8b0 {
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
