// src/game/Swarm/ParticlesDescription.cpp -- migrated from slice(s) s00aa7470, s00aa4a10 by tools/migrate/rewrite.py
// Object file: Swarm/ParticlesDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/ArgScript/cICommand.h"
#include "EA/ArgScript/cArguments.h"
#include <intrin.h>

// unnamed retail callees and globals (address in the comment)
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

// ---- items of slice s00aa4a10 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace ArgScript {
struct cIParser_s00aa_4a10;
}
}
namespace EA {
namespace ArgScript {
struct cState_s00aa_4a10;
}
}
namespace EA {
namespace ArgScript {
struct cArguments_s00aa_4a10;
}
}
namespace EA {
namespace ArgScript {
struct cICommand_s00aa_4a10 {
    virtual void AddRef();
    virtual void Release();
    virtual void Cast();
};
}
}
namespace EA {
namespace ArgScript {
struct cCommandBase_s00aa_4a10 : cICommand_s00aa_4a10 {
    cIParser_s00aa_4a10* mParser;
    int mRefCount;
    cCommandBase_s00aa_4a10();                                     // 0x0083c800
};
}
}
namespace EA {
namespace ArgScript {
struct cBlockCommandBase : cICommand_s00aa_4a10 {
    cIParser_s00aa_4a10* mParser;                                  // +0x04
    int mRefCount;                                      // +0x08
    cState_s00aa_4a10* mChildState;                                // +0x0c
    uint32_t mCommands[8];                              // +0x10 hash map
    void OnRegister(cIParser_s00aa_4a10* parser, cState_s00aa_4a10* state);   // 0x0083c780
    void SetChildState(cState_s00aa_4a10* state);                  // 0x00fd9450
    virtual void v03(); virtual void v04(); virtual void v05();
    virtual void AddCommand(const char* name, cICommand_s00aa_4a10* command);      // +0x18
};
}
}
namespace EA {
namespace ArgScript {
template <typename T, typename Base> struct cCommandStateT_s00aa_4a10 : Base {
    T* mState;                                          // +0x30 in a block command
    cCommandStateT_s00aa_4a10() {}
};
}
}
namespace EA {
namespace ArgScript {
template <typename T> struct cCommandT : cCommandStateT_s00aa_4a10<T, cCommandBase_s00aa_4a10> {
    cCommandT() {}
};
}
}
namespace EA {
namespace ArgScript {
template <typename T> struct cBlockCommandT : cCommandStateT_s00aa_4a10<T, cBlockCommandBase> {
    cBlockCommandT() {}
};
}
}
namespace EA {
namespace Swarm {
struct cEffectsParser;
}
}
namespace EA {
namespace Swarm {
void RegisterPathCommand(void* owner, void* a, void* b, void* c);   // 0x00a7a8d0, cdecl
}
}
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                 // 0x00f473a0
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
namespace {
template <int N> struct cParticleCmdT : EA::ArgScript::cCommandT<EA::Swarm::cEffectsParser> {
    cParticleCmdT() {}
    virtual void Execute(EA::ArgScript::cArguments_s00aa_4a10& args);
};
}  // namespace
namespace {
struct cParticleEffectCommand : EA::ArgScript::cBlockCommandT<EA::Swarm::cEffectsParser> {
    char mPad34[4];                 // +0x34
    char mChildStateBase[0x2b0 - 0x38];   // +0x38 cState subobject (SetChildState target)
    void* mStateCopy;               // +0x2b0 copy of mState
    void OnRegister(EA::ArgScript::cIParser_s00aa_4a10* parser, EA::ArgScript::cState_s00aa_4a10* state);
};
}  // namespace
// ---- items of slice s00aa4a10 end

// ---- items of slice s00aa7470 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VTP(obj, off)   (*(void**)((char*)(*(void**)(obj)) + (off)))
struct CArgs {
    void* MainArguments(int n);              // 0x838320
    void* MainArgumentsX(void* out, int a, int b);  // 0x838020
    char  HasFlag(const char* name);         // 0x8380b0
};
struct StrAssign {
    void FUN_00454cb0(const char* begin, const char* end);  // eastl::basic_string::assign
};
struct CmdObj {
    void* FUN_00aa3460();     // ctor
    void  FUN_00aa32f0();     // dtor
};
struct Parser {
    void* FUN_00a6f090(void* args, int count, void* extra);  // GetInheritedDescription
};
struct Self {
    char raw[0x2e0];
    Self* FUN_00aa7470(const Self* o);
    void  FUN_00aa82e0(char p);
    void  FUN_00aa8370(int p);
    bool  FUN_00aa7fb0(int p2, int* p3, int p4);
    void  FUN_00aa7910(void* args);
    void  FUN_00aa7a80(void* args);
};
// ---- items of slice s00aa7470 end

// @ 0x00aa4e50
namespace
{
void cParticleEffectCommand::OnRegister(EA::ArgScript::cIParser_s00aa_4a10* parser, EA::ArgScript::cState_s00aa_4a10* state)
{
    mState = state ? (EA::Swarm::cEffectsParser*)((char*)state - 0xc) : 0;
    EA::ArgScript::cBlockCommandBase::OnRegister(parser, state);
    SetChildState((EA::ArgScript::cState_s00aa_4a10*)((char*)this + 0x38));
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
}

// @ 0x00aa7a80
void Self::FUN_00aa7a80(void* args)
{
    char* s = raw;
    CArgs* ca = (CArgs*)args;
    int count = 0;
    char cmdspace[0x260];

    void* puVar2 = ca->MainArgumentsX(&count, 1, 3);

    const char* pcVar1 = *(const char**)puVar2;
    const char* pcVar3;
    do { pcVar3 = pcVar1; pcVar1 = pcVar3 + 1; } while (*pcVar3 != '\0');

    ((StrAssign*)(s + 0x2b8))->FUN_00454cb0(*(const char**)puVar2, pcVar3);

    void* cmd = ((CmdObj*)cmdspace)->FUN_00aa3460();
    ((Self*)(s + 0x40))->FUN_00aa7470((const Self*)cmd);
    ((CmdObj*)cmdspace)->FUN_00aa32f0();

    s[0x2c8] = 0;
    s[0x2c9] = 0;

    if (count > 1) {
        void* desc = ((Parser*)(*(void**)(s + 0x30)))->FUN_00a6f090(puVar2, count, *(void**)(s + 0x34));
        if (desc != 0)
            ((Self*)(s + 0x40))->FUN_00aa7470((const Self*)desc);
    }

    void* o = *(void**)(s + 4);
    ((void(__thiscall*)(void*, void*))VTP(o, 0x8c))(o, this);
}
