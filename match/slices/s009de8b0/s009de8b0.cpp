// Slice s009de8b0 -- `anonymous namespace'::cGaitKeyBlockCommand::OnRegister: the ArgScript block
// command for a gait key (animation gait tuning files) registers one sub-command per gait field.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                            // 0x00f473a0
void operator delete(void* p, const char* name, int flags, unsigned debugFlags,
                     const char* file, int line);

// ---------------------------------------------------------------- EA::ArgScript
namespace EA { namespace ArgScript {
struct cIParser;
struct cState;
struct cArguments;

class cICommand { public:
    virtual int AddRef();
    virtual int Release();
    virtual void* Cast(uint32_t type);
    virtual void ParseLine(void* line);
    virtual void Execute(cArguments& args);
};
class cCommandBase : public cICommand { public:
    cIParser* mParser;                          // +0x04
    int mRefCount;                              // +0x08
    cCommandBase();                             // 0x0083c800
};
class cIBlockCommand : public cICommand { public:
    virtual cState* GetChildState();            // +0x14
};
class cBlockCommandBase : public cIBlockCommand { public:
    cIParser* mParser;                          // +0x04
    int mRefCount;                              // +0x08
    cState* mChildState;                        // +0x0c
    uint32_t mCommands[8];                      // +0x10 hash_map<string, cICommand*>
    void OnRegister(cIParser* parser, cState* state);   // 0x0083c780
    virtual void AddCommand(const char* keyword, cICommand* command);   // +0x18
};

template <typename T, typename Base> struct cCommandStateT : Base {
    T* mState;                                  // block: +0x30, command: +0x0c
    cCommandStateT() {}
};
template <typename T> class cCommandT : public cCommandStateT<T, cCommandBase> { public:
    cCommandT() {}
};
template <typename T> class cBlockCommandT : public cCommandStateT<T, cBlockCommandBase> { public:
    cBlockCommandT() {}
};
}}  // namespace EA::ArgScript

using EA::ArgScript::cIParser;
using EA::ArgScript::cState;
using EA::ArgScript::cArguments;

namespace {

struct cGaitKeyState;                           // the gait key being parsed (the parser's state object)

struct cGaitKeyBlockCommand : EA::ArgScript::cBlockCommandT<cGaitKeyState> {
    void OnRegister(cIParser* parser, cState* state);
};

// One sub-command class per gait key field; each only overrides Execute.
#define GAIT_KEY_COMMAND(Name)                                                           \
    struct c##Name##Command : EA::ArgScript::cCommandT<cGaitKeyBlockCommand> {          \
        c##Name##Command() {}                                                            \
        virtual void Execute(cArguments& args);                                          \
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
    void OnRegister(cIParser* parser, cState* state);
};

struct cStepLengthCommand : EA::ArgScript::cCommandT<cStepLengthKeyBlockCommand> {
    cStepLengthCommand() {}
    virtual void Execute(cArguments& args);
};

}  // namespace

// Gait file keywords (an alphabetical table of `const char*` at 0x0155152c..0x015515d8).
namespace GaitKeywords {
extern const char* bnd;                     // 0x0155152c "bnd"
extern const char* dutyfactor;              // 0x01551530 "dutyfactor"
extern const char* foottilt;                // 0x01551534 "foottilt"
extern const char* herfl;                   // 0x01551538 "herfl"
extern const char* lateralphaseoffset;      // 0x0155153c
extern const char* maxlateraloffset;        // 0x01551540
extern const char* maxpitchangle;           // 0x01551544
extern const char* maxrollangle;            // 0x01551548
extern const char* maxsagittaloffset;       // 0x0155154c
extern const char* maxverticaloffset;       // 0x01551550
extern const char* maxyawangle;             // 0x01551554
extern const char* numfeet;                 // 0x01551558
extern const char* numpathbndkeys;          // 0x0155155c
extern const char* numpathposkeys;          // 0x01551560
extern const char* numpathrotkeys;          // 0x01551564
extern const char* numpaths;                // 0x01551568
extern const char* pitchphaseoffset;        // 0x0155156c
extern const char* pos;                     // 0x01551570
extern const char* rollphaseoffset;         // 0x01551574
extern const char* rot;                     // 0x01551578
extern const char* sagittalphaseoffset;     // 0x0155157c
extern const char* speedi;                  // 0x01551580
extern const char* spl;                     // 0x01551584
extern const char* stepgallop;              // 0x01551588
extern const char* stepheight;              // 0x0155158c
extern const char* steplength;              // 0x01551590
extern const char* stepphasebiash;          // 0x01551594
extern const char* stepphasebiasv;          // 0x01551598
extern const char* stepskew;                // 0x0155159c
extern const char* swayAmplitude;           // 0x015515a0
extern const char* swayPhase;               // 0x015515a4
extern const char* tanfl;                   // 0x015515a8
extern const char* taxon;                   // 0x015515ac
extern const char* tic;                     // 0x015515b0
extern const char* tiltpoint;               // 0x015515b4
extern const char* toecurlbegin;            // 0x015515b8
extern const char* toecurlend;              // 0x015515bc
extern const char* toecurlmax;              // 0x015515c0
extern const char* trackWidthReduction;     // 0x015515c4
extern const char* trigger;                 // 0x015515c8
extern const char* verticaldist;            // 0x015515cc
extern const char* verticalphaseoffset;     // 0x015515d0
extern const char* walkrunshape;            // 0x015515d4
extern const char* yawphaseoffset;          // 0x015515d8
}

// @ 0x009de8b0
void cGaitKeyBlockCommand::OnRegister(cIParser* parser, cState* state)
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

// The "steplength" variant registers only the field commands it understands.
// @ 0x009df360
void cStepLengthKeyBlockCommand::OnRegister(cIParser* parser, cState* state)
{
    mState = (cGaitKeyState*)state;
    cBlockCommandBase::OnRegister(parser, state);

    AddCommand(GaitKeywords::speedi,
               new ("ArgScript/SpeedI", 0, 0, 0, 0) cSpeedICommand());
    AddCommand(GaitKeywords::steplength,
               new ("ArgScript/StepLength", 0, 0, 0, 0) cStepLengthCommand());
}

// ---------------------------------------------------------------------------------------------
// Gait-animation vectors (0x009df400 .. 0x009df9b0). `Vec<T>` is a begin / end / capacity-end
// vector allocated through the EA debug operator new; every element type here is raw storage,
// with the element copy-construct and range-copy helpers supplied out of line.

struct GaitA     { uint8_t mData[0x44]; };      // 0x44
struct GaitC     { uint8_t mData[0x1c]; };      // 0x1c
struct GaitItem  { uint8_t mData[0x0c]; };      // 0x0c
struct AnalysisInfo { uint32_t mA, mB, mC; };    // 0x0c

void CopyGaitA(GaitA* first, GaitA* last, GaitA* result);           // 0x009dc0f0
void CopyGaitC(GaitC* first, GaitC* last, GaitC* result);           // 0x009dc1d0
void CopyGaitItem(GaitItem* first, GaitItem* last, GaitItem* result);   // 0x009dc300

void CopyConstructGaitA(void* outEnd, GaitA* first, GaitA* last, GaitA* dst, int n);   // 0x009dd530
void CopyConstructInfo(void* outEnd, AnalysisInfo* first, AnalysisInfo* last,
                       AnalysisInfo* dst, int tag);                 // 0x00898b80
void CopyInfo(AnalysisInfo* first, AnalysisInfo* last, AnalysisInfo* result);  // 0x00b84c80

void FreeMemory(void* p);                                          // 0x00f47380 (operator delete)
extern const char kAllocatorFile[];                                // 0x013ebb38

template <typename T> struct Vec {
    T* mpBegin;          // +0x00
    T* mpEnd;            // +0x04
    T* mpEndOfStorage;   // +0x08

    int size() const { return (int)(mpEnd - mpBegin); }
    unsigned int capacity() const { return (unsigned int)(mpEndOfStorage - mpBegin); }

    void reserve(int n);
    T* allocate_copy(int n, T* first, T* last);
    Vec(unsigned int n, const T& value, int unused = 0);
    Vec& operator=(const Vec& other);
};

// @ 0x009df400
template <> void Vec<GaitA>::reserve(int n)
{
    if ((unsigned int)n > capacity()) {
        GaitA* p = n ? (GaitA*)operator new(n * sizeof(GaitA), "Anim/gait/untagged",
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
template <> void Vec<GaitC>::reserve(int n)
{
    if ((unsigned int)n > capacity()) {
        GaitC* p = n ? (GaitC*)operator new(n * sizeof(GaitC), "Anim/gait/untagged",
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

// @ 0x009df6e0 Vec::allocate_copy
template <> GaitA* Vec<GaitA>::allocate_copy(int n, GaitA* first, GaitA* last)
{
    GaitA* p = n ? (GaitA*)operator new(n * sizeof(GaitA), "Anim/gait/untagged",
                                        0, 0, kAllocatorFile, 0xd1) : 0;
    CopyConstructGaitA(&n, first, last, p, n);
    return p;
}

// @ 0x009df800 Vec::reserve
template <> void Vec<GaitItem>::reserve(int n)
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

// @ 0x009df8b0 Vec::Vec
template <> Vec<GaitItem>::Vec(unsigned int n, const GaitItem& value, int unused)
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

template <> AnalysisInfo* Vec<AnalysisInfo>::allocate_copy(int n, AnalysisInfo* first,
                                                          AnalysisInfo* last)
{
    AnalysisInfo* p = n ? (AnalysisInfo*)operator new(n * sizeof(AnalysisInfo),
                                                     "Anim/gait/untagged", 0, 0,
                                                     kAllocatorFile, 0xd1) : 0;
    CopyConstructInfo(&n, first, last, p, n);
    return p;
}

// @ 0x009df9b0 Vec::operator=
template <> Vec<AnalysisInfo>& Vec<AnalysisInfo>::operator=(const Vec<AnalysisInfo>& other)
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
