// match/slices/s00a73ef0/s00a73ef0.cpp
// Object file: Swarm/Help.obj.  flags /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned int uint32_t;

// unnamed retail callees and globals (address in the comment)
void __cdecl operator_delete__(void* p);                        // 0x00f47380 operator delete
void __cdecl operator_delete_arr__(void* p);                    // 0x00f47380
extern const char* gEmitStrength;                               // 0x01554808 ("emitStrength")
extern const char* gModelOverride;                              // 0x015548e0 ("modelOverride")

namespace EA { namespace ArgScript {
struct cArguments;
struct cIParser;
class cCommandBase {
 public:
    cCommandBase();
    virtual void Execute(cArguments*);
    virtual const char* Description(int) const;
    virtual void OnRegister(cIParser*, void*);
    virtual int AddRef();
    virtual int Release();
    virtual ~cCommandBase();
    cIParser* mParser;                                          // +0x04
    int mRefCount;                                              // +0x08
};
struct cArgumentSpec {
    cArgumentSpec(bool);
    ~cArgumentSpec();
    int ConstructSpec(const char* name, ...);                   // 0x0083bcd0
    char pad[0xc8];
};
}}  // namespace EA::ArgScript

struct Vector3 { float x, y, z; };

template <class T>
struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAlloc[2];
    vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~vector() { if (mpBegin && ((int*)mpBegin)[-1] != 0) operator_delete__(mpBegin); }
};

struct StringVector {
    void* mpBegin; void* mpEnd; void* mpCapacity; uint32_t mAlloc[2];
    StringVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~StringVector()
    {
        destruct((void**)mpBegin, (void**)mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
    }
    void destruct(void** first, void** last);                   // 0x006a4950
};

struct EffectVector {
    void* mpBegin; void* mpEnd; void* mpCapacity; uint32_t mAlloc[2];
    EffectVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~EffectVector();                                            // 0x004b5440
};

namespace EA { namespace Swarm {

class cEffectsManager;
class cIVisualEffect;

class cEffectCheat : public EA::ArgScript::cCommandBase {
 public:
    cEffectCheat(cEffectsManager* manager);
    virtual void Execute(EA::ArgScript::cArguments*);

    char pad0c[4];                                              // +0x0c
    cEffectsManager* mManager;                                  // +0x10
    EffectVector mTestEffects;                                  // +0x14
    EA::ArgScript::cArgumentSpec mArgSpec;                      // +0x28
    const char* mWorldName;                                     // +0xf0
    const char* mEffectName;                                    // +0xf4
    const char* mModel;                                         // +0xf8
    const char* mTexture;                                       // +0xfc
    Vector3 mPosition;                                          // +0x100
    float mScale;                                               // +0x10c
    int mID;                                                    // +0x110
    int mFrame;                                                 // +0x114
    int mStateIndex;                                            // +0x118
    bool mHidden;                                               // +0x11c
    bool mPaused;                                               // +0x11d
    char pad11e[2];                                             // +0x11e
    int mSeed;                                                  // +0x120
    int mOverrideSet;                                           // +0x124
    char pad128[16];                                            // +0x128 mColour
    StringVector mOverrideNames;                                // +0x138
    vector<int> mOverrideSets;                                  // +0x14c
    vector<float> mOverrideRanges;                              // +0x160
    int mFloatParam;                                            // +0x174
    vector<float> mFloatParams;                                 // +0x178
    int mIntParam;                                              // +0x18c
    vector<int> mIntParams;                                     // +0x190
};

class cEffectsManagerCheat : public EA::ArgScript::cCommandBase {
 public:
    cEffectsManagerCheat();
    virtual void Execute(EA::ArgScript::cArguments*);

    char pad0c[4];                                              // +0x0c
    cEffectsManager* mManager;                                  // +0x10
    EA::ArgScript::cArgumentSpec mArgSpec;                      // +0x14
};

// Defining the class ctor out-of-line makes the compiler emit the implicit virtual
// destructor (??1) and its scalar deleting destructor (??_G) alongside it.
cEffectsManagerCheat::cEffectsManagerCheat() : mManager(0), mArgSpec(true) {}
void cEffectsManagerCheat::Execute(EA::ArgScript::cArguments*) {}   // key function: emits the class vtable

}}  // namespace EA::Swarm

using EA::Swarm::cEffectCheat;
using EA::Swarm::cEffectsManagerCheat;
using EA::Swarm::cEffectsManager;

// @ 0x00a73ef0
cEffectCheat::cEffectCheat(cEffectsManager* manager)
    : mManager(manager), mArgSpec(true)
{
    mArgSpec.ConstructSpec(
        "Starts the named effect, or, with no arguments, stops the current effect.",
        ":floatParams", &gEmitStrength,
        ":intParams", &gModelOverride,
        "[<effectName:cstring>]", &mEffectName,
        "Set the current effect and start it, or stop the current effect, if no effect name or options given.",
        "-pos^ <x:float> <y:float> [<z:float>^]", 0, &mPosition, &mPosition.y, &mPosition.z,
        1, "Where to place the effect, or move the current effect",
        "-offset^ <p:vector3>^", 0, &mPosition,
        1, "Where to place the effect, or move the current effect",
        "-scale^ <s:float>", 2, &mScale,
        "Scale the effect rigidly",
        "-id <n:int>", &mID,
        "Apply this command to effect slot 'n'. The default slot is 0. This can be used to run several effects simultaneously.",
        "-start^", 3, "(Re)start current effect.",
        "-stop^", 4, "Stop current effect.",
        "-hard^", 6, "Modifier on -start or -stop.",
        "-soft^", 5, "Modifier on -start or -stop.",
        "-clear^", 7, "Drop reference to the current effect. (for testing.)",
        "-world <name:cstring>", &mWorldName,
        "Use given effects world rather than default one.",
        "-edit^", 8, "If file location tracking is on, open effect in editor",
        "-floatParams^ <param:floatParams> <param0:float> ...", 13, &mFloatParam, &mFloatParams,
        "Set the given float params for the current effect. E.g., -floatParams color 0 1 0, or -floatParams emitRateScale 2",
        "-intParams^ <param:intParams> <param0:int> ...", 14, &mIntParam, &mIntParams,
        "Set the given int params for the current effect. E.g., -intParams selectFrame 2",
        "-model^ <name:cstring> [<set:int>]", 9, &mModel, &mOverrideSet,
        "Set an override model for the current effect.",
        "-texture^ <name:cstring> [<set:int>]", 10, &mTexture, &mOverrideSet,
        "Set an override texture for the current effect.",
        "-models^ <names:string[]> <sets:int[]>", 9, &mOverrideNames, &mOverrideSets,
        "Set multiple override models for the current effect.",
        "-textures^ <names:string[]> <sets:int[]>", 10, &mOverrideNames, &mOverrideSets,
        "Set multiple override textures for the current effect.",
        "-frame^ <n:int>", 11, &mFrame,
        "Select the given texture particle frame.",
        "-state^ <n:int>", 12, &mStateIndex,
        "Select the given state. (See the effect 'states' command).",
        "-paused^ <bool>", 15, &mPaused,
        "Set whether current effect is paused.",
        "-hidden^ <bool>", 16, &mHidden,
        "Set whether current effect is hidden.",
        "-seed^ <int>", 17, &mSeed,
        "Set RNG seed",
        0);
}

// @ 0x00a74150
// @ 0x00a74230
