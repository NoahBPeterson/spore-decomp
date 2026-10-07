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

struct cICommand {
    virtual int AddRef();
    virtual int Release();
    virtual void* Cast(uint32_t type);
    virtual void ParseLine(void* line);
    virtual void Execute(cArguments& args);
};
struct cCommandBase : cICommand {
    cIParser* mParser;                          // +0x04
    int mRefCount;                              // +0x08
    cCommandBase();                             // 0x0083c800
};
struct cIBlockCommand : cICommand {
    virtual cState* GetChildState();            // +0x14
};
struct cBlockCommandBase : cIBlockCommand {
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
template <typename T> struct cCommandT : cCommandStateT<T, cCommandBase> {
    cCommandT() {}
};
template <typename T> struct cBlockCommandT : cCommandStateT<T, cBlockCommandBase> {
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
