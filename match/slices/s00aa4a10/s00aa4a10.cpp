// Slice s00aa4a10: ArgScript particle-effect command registration (one function, 0x00aa4e50, 2484 B).
// Ghidra names it anonymous_namespace'::cParticleEffectCommand::OnRegister. The body is a chain of
// `AddCommand(keyword, new ("ArgScript/<name>", 0, 0, 0, 0) <command>())` blocks followed by
// RegisterPathCommand. Each command class is a cCommandT subclass with its own vtable. Only the
// vtable address (class identity) is visible in the asm, so each class is a template slot
// cParticleCmdT<N>, where N is the index of its vtable in the list below.
#include "types.h"

namespace EA { namespace ArgScript {
struct cIParser;
struct cState;
struct cArguments;
struct cICommand {
    virtual void AddRef();
    virtual void Release();
    virtual void Cast();
};
struct cCommandBase : cICommand {
    cIParser* mParser;
    int mRefCount;
    cCommandBase();                                     // 0x0083c800
};
struct cBlockCommandBase : cICommand {
    cIParser* mParser;                                  // +0x04
    int mRefCount;                                      // +0x08
    cState* mChildState;                                // +0x0c
    uint32_t mCommands[8];                              // +0x10 hash map
    void OnRegister(cIParser* parser, cState* state);   // 0x0083c780
    void SetChildState(cState* state);                  // 0x00fd9450
    virtual void v03(); virtual void v04(); virtual void v05();
    virtual void AddCommand(const char* name, cICommand* command);      // +0x18
};
template <typename T, typename Base> struct cCommandStateT : Base {
    T* mState;                                          // +0x30 in a block command
    cCommandStateT() {}
};
template <typename T> struct cCommandT : cCommandStateT<T, cCommandBase> {
    cCommandT() {}
};
template <typename T> struct cBlockCommandT : cCommandStateT<T, cBlockCommandBase> {
    cBlockCommandT() {}
};
}}  // namespace EA::ArgScript

namespace EA { namespace Swarm {
struct cEffectsParser;
void RegisterPathCommand(void* owner, void* a, void* b, void* c);   // 0x00a7a8d0, cdecl
}}

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                 // 0x00f473a0

// Keyword globals (pointers to name strings), read by value from the data VAs in the asm.
extern const char* kKeyword_015654d0;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654d8;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654d4;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654dc;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654e0;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654e4;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654e8;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654ec;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654f0;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654f4;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654f8;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654fc;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565500;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565504;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565508;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_0156550c;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565510;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565514;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565518;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_0156551c;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565520;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565524;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565528;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_0156552c;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565530;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565534;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565538;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_0156553c;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565540;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565544;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565548;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_0156554c;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565550;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565554;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565558;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_0156555c;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565560;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565564;   // keyword string pointer (data VA in the name)

// ---------------------------------------------------------------- vtable identities
// Vtable VA -> index. 0 = 0x01458e20 ... 30 = 0x01459108 (values from the asm).
namespace {
template <int N> struct cParticleCmdT : EA::ArgScript::cCommandT<EA::Swarm::cEffectsParser> {
    cParticleCmdT() {}
    virtual void Execute(EA::ArgScript::cArguments& args);
};
}  // namespace

namespace {
struct cParticleEffectCommand : EA::ArgScript::cBlockCommandT<EA::Swarm::cEffectsParser> {
    char mPad34[4];                 // +0x34
    char mChildStateBase[0x2b0 - 0x38];   // +0x38 cState subobject (SetChildState target)
    void* mStateCopy;               // +0x2b0 copy of mState
    void OnRegister(EA::ArgScript::cIParser* parser, EA::ArgScript::cState* state);
};
}  // namespace

// @ 0x00aa4e50 anonymous_namespace'::cParticleEffectCommand::OnRegister
namespace {
void cParticleEffectCommand::OnRegister(EA::ArgScript::cIParser* parser, EA::ArgScript::cState* state)
{
    mState = state ? (EA::Swarm::cEffectsParser*)((char*)state - 0xc) : 0;
    EA::ArgScript::cBlockCommandBase::OnRegister(parser, state);
    SetChildState((EA::ArgScript::cState*)((char*)this + 0x38));
    mStateCopy = mState;
    AddCommand(kKeyword_015654d0, new ("ArgScript/ParticleColor", 0, 0, 0, 0) cParticleCmdT<0>());
    AddCommand(kKeyword_015654d8, new ("ArgScript/ParticleColor255", 0, 0, 0, 0) cParticleCmdT<0>());
    AddCommand(kKeyword_015654d4, new ("ArgScript/ParticleColour", 0, 0, 0, 0) cParticleCmdT<0>());
    AddCommand(kKeyword_015654dc, new ("ArgScript/ParticleColour255", 0, 0, 0, 0) cParticleCmdT<0>());
    AddCommand(kKeyword_015654e0, new ("ArgScript/ParticleAlpha", 0, 0, 0, 0) cParticleCmdT<1>());
    AddCommand(kKeyword_015654e4, new ("ArgScript/ParticleAlpha255", 0, 0, 0, 0) cParticleCmdT<1>());
    AddCommand(kKeyword_015654e8, new ("ArgScript/ParticleSize", 0, 0, 0, 0) cParticleCmdT<2>());
    AddCommand(kKeyword_015654ec, new ("ArgScript/ParticleAspect", 0, 0, 0, 0) cParticleCmdT<3>());
    AddCommand(kKeyword_015654f0, new ("ArgScript/ParticleRotate", 0, 0, 0, 0) cParticleCmdT<4>());
    AddCommand(kKeyword_015654f4, new ("ArgScript/ParticleSource", 0, 0, 0, 0) cParticleCmdT<5>());
    AddCommand(kKeyword_015654f8, new ("ArgScript/ParticleEmit", 0, 0, 0, 0) cParticleCmdT<6>());
    AddCommand(kKeyword_015654fc, new ("ArgScript/ParticleForce", 0, 0, 0, 0) cParticleCmdT<7>());
    AddCommand(kKeyword_01565500, new ("ArgScript/ParticleWarp", 0, 0, 0, 0) cParticleCmdT<8>());
    AddCommand(kKeyword_01565504, new ("ArgScript/ParticleDirectedWalk", 0, 0, 0, 0) cParticleCmdT<9>());
    AddCommand(kKeyword_01565508, new ("ArgScript/ParticleRandomWalk", 0, 0, 0, 0) cParticleCmdT<10>());
    AddCommand(kKeyword_0156550c, new ("ArgScript/ParticleStretch", 0, 0, 0, 0) cParticleCmdT<11>());
    AddCommand(kKeyword_01565510, new ("ArgScript/ParticleLife", 0, 0, 0, 0) cParticleCmdT<12>());
    AddCommand(kKeyword_01565514, new ("ArgScript/ParticleRate", 0, 0, 0, 0) cParticleCmdT<13>());
    AddCommand(kKeyword_01565518, new ("ArgScript/ParticleInject", 0, 0, 0, 0) cParticleCmdT<14>());
    AddCommand(kKeyword_0156551c, new ("ArgScript/ParticleMaintain", 0, 0, 0, 0) cParticleCmdT<15>());
    AddCommand(kKeyword_01565528, new ("ArgScript/ParticleMaterial", 0, 0, 0, 0) cParticleCmdT<16>());
    AddCommand(kKeyword_01565520, new ("ArgScript/ParticleTexture", 0, 0, 0, 0) cParticleCmdT<17>());
    AddCommand(kKeyword_01565524, new ("ArgScript/ParticleModel", 0, 0, 0, 0) cParticleCmdT<18>());
    AddCommand(kKeyword_0156552c, new ("ArgScript/ParticleFrames", 0, 0, 0, 0) cParticleCmdT<19>());
    AddCommand(kKeyword_01565530, new ("ArgScript/ParticleAlignment", 0, 0, 0, 0) cParticleCmdT<20>());
    AddCommand(kKeyword_01565534, new ("ArgScript/ParticleLoopBoxColor", 0, 0, 0, 0) cParticleCmdT<21>());
    AddCommand(kKeyword_0156553c, new ("ArgScript/ParticleLoopBoxColor255", 0, 0, 0, 0) cParticleCmdT<21>());
    AddCommand(kKeyword_01565538, new ("ArgScript/ParticleLoopBoxAlpha", 0, 0, 0, 0) cParticleCmdT<22>());
    AddCommand(kKeyword_01565540, new ("ArgScript/ParticleLoopBoxAlpha255", 0, 0, 0, 0) cParticleCmdT<22>());
    AddCommand(kKeyword_01565544, new ("ArgScript/ParticleSurface", 0, 0, 0, 0) cParticleCmdT<23>());
    AddCommand(kKeyword_01565548, new ("ArgScript/ParticleMapEmit", 0, 0, 0, 0) cParticleCmdT<24>());
    AddCommand(kKeyword_0156554c, new ("ArgScript/ParticleMapEmitColor", 0, 0, 0, 0) cParticleCmdT<25>());
    AddCommand(kKeyword_01565550, new ("ArgScript/ParticleMapEmitColour", 0, 0, 0, 0) cParticleCmdT<25>());
    AddCommand(kKeyword_01565554, new ("ArgScript/ParticleMapCollide", 0, 0, 0, 0) cParticleCmdT<26>());
    AddCommand(kKeyword_01565558, new ("ArgScript/ParticleMapRepel", 0, 0, 0, 0) cParticleCmdT<27>());
    AddCommand(kKeyword_0156555c, new ("ArgScript/ParticleMapAdvect", 0, 0, 0, 0) cParticleCmdT<28>());
    AddCommand(kKeyword_01565560, new ("ArgScript/ParticleMapForce", 0, 0, 0, 0) cParticleCmdT<29>());
    AddCommand(kKeyword_01565564, new ("ArgScript/ParticlePhysics", 0, 0, 0, 0) cParticleCmdT<30>());
    EA::Swarm::RegisterPathCommand(this, (char*)this + 0x2c8, (char*)this + 0x2c9, (char*)this + 0x29c);
}
}  // namespace
