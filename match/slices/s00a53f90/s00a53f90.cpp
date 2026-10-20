// Slice s00a53f90 - EA::Audio::Eapd (EA's embedded Pure Data) fracplay object "play":
// Play (voice list + parameter map), the play_* atom classes (new/free/anything/start/
// startselect, setup) and the arithmetic float atom classes (add/sub/mul/div/pow/max/min,
// each a bang and a float method).
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "s00a53f90.h"
#include <math.h>

namespace EA { namespace Audio { namespace Eapd {

// ---------------------------------------------------------------------------
// @ 0x00a53f90  EA::Audio::Eapd::play_free
// ---------------------------------------------------------------------------
void play_free(t_play* x)
{
    PlayUpdateManager* mgr = (PlayUpdateManager*)Play_GetUpdateManager();
    if (x->pUpdateCallback)
        mgr->RemoveCallback(x->pUpdateCallback);
    ((PlayDtorStub*)&x->play)->Destroy();
}

// ---------------------------------------------------------------------------
// @ 0x00a53fc0  EA::Audio::Eapd::play_anything
// ---------------------------------------------------------------------------
void play_anything(t_play* x, uint32_t selHash, const char* selName, int argc, PgAtomArg* argv)
{
    char buf[1000];
    if (argc == 1)
        ((Play*)((char*)x + 0x28))->Dolist(selHash, selName, argv);
    else
        AtomsToString(argc, argv, buf, 1000);
}
// ---------------------------------------------------------------------------
// @ 0x00a54020  EA::Audio::Eapd::Play::Play (ctor)
// ---------------------------------------------------------------------------
Play* Play::Ctor(void* voiceManager, void* instance, uint32_t nameHash, const char* name,
                 int steal, int updatePlaying, int stepRule, void* object)
{
    EapdVoiceList_Init((char*)this, "EAPd/VoiceList");
    EapdParamTable_Init((char*)this + 0x38, "EAPd/ParameterMap");
    mVoiceManager = voiceManager;
    mInstance = instance;
    mName.mHash = nameHash;
    mName.mpName = name;
    mbSteal = (steal == 1);
    mnStepRule = stepRule;
    mnBusyVoices = 0;
    mnMaxVoices = 0;
    mnMaxParameters = 0;
    mbPaused = false;
    mpObject = object;
    mbUpdatePlaying = (updatePlaying == 0);
    mnLastGroupID = 0xffffffff;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00a540f0  EA::Audio::Eapd::Play::Start
// ---------------------------------------------------------------------------
void Play::Start(float time)
{
    void* group = Instance_GetGroup(mInstance, mName.mHash, mName.mpName);
    PgSymbol name;
    if (!group) {
        name = *(PgSymbol*)Play_GetLocation(&name);
        gPlaySymbol = name;
        Play_Dispatch(mpObject, mName.mHash, mName.mpName, time);
        return;
    }
    unsigned n = Group_Size(group);
    unsigned idx = 0;
    if (n > 1) {
        if (mnStepRule == STEP_RANDOM) {
            idx = eapd_rand(n);
        } else if (mnStepRule == STEP_INORDER) {
            idx = (mnLastGroupID + 1) % n;
        } else if (mnStepRule == STEP_NOREPEAT) {
            idx = eapd_rand(n - 1);
            if (idx == mnLastGroupID)
                idx = n - 1;
        }
    }
    PgSymbol loc = *(PgSymbol*)Group_Location(&loc, group);
    gPlaySymbol = loc;
    name = *(PgSymbol*)Group_Sample(&name, group, idx);
    mnLastGroupID = idx;
    Play_Dispatch(mpObject, name.mHash, name.mpName, time);
}

// ---------------------------------------------------------------------------
// @ 0x00a54200  EA::Audio::Eapd::Play::StartSelect
// ---------------------------------------------------------------------------
void Play::StartSelect(unsigned group, float time)
{
    void* g = Instance_GetGroup(mInstance, mName.mHash, mName.mpName);
    if (!g)
        return;
    PgSymbol sample = *(PgSymbol*)Group_Sample(&sample, g, group);
    if (sample.mHash == gEmptySymbol.mHash)
        return;
    PgSymbol loc = *(PgSymbol*)Group_Location(&loc, g);
    gPlaySymbol = loc;
    Play_Dispatch(mpObject, sample.mHash, sample.mpName, time);
    mnLastGroupID = group;
}

// ---------------------------------------------------------------------------
// @ 0x00a54290  EA::Audio::Eapd::play_new
// ---------------------------------------------------------------------------
t_play* play_new(uint32_t nameHash, const char* name, void* unused3, int argc, PgAtomArg* argv){
    bool bDynamic = (nameHash != gPlaySymbol.mHash);
    PgSymbol firstSym = gEmptySymbol;
    int stepRule = 0;
    int updatePlaying = 0;
    int steal = 1;
    bool bHaveFirst = false;
    unsigned floatArg = 1;
    bool haveFloat = false;
    bool bStealSet = false;
    bool bSetSet = false;

    for (int i = 0; i < argc; ++i) {
        PgAtomArg* a = &argv[i];
        if (haveFloat) {
            if (bStealSet && bSetSet)
                break;
        } else {
            if (a->a_type == 1) {
                floatArg = (unsigned)(int)(__int64)a->a_w.a_float;
                haveFloat = true;
                continue;
            }
        }
        if (a->a_type == 2) {
            uint32_t sel = a->a_w.a_symbol.mHash;
            if (sel == gStealSymbol.mHash) {
                bStealSet = true;
                steal = 1;
            } else if (sel == gBlockSymbol.mHash) {
                steal = 0;
                bStealSet = true;
            } else if (sel == gSetplayingSymbol.mHash) {
                updatePlaying = 0;
                bSetSet = true;
            } else if (sel == gSetnextSymbol.mHash) {
                bSetSet = true;
                updatePlaying = 1;
            } else if (sel == gInorderSymbol.mHash) {
                stepRule = 1;
            } else if (sel == gRandomSymbol.mHash) {
                stepRule = 0;
            } else if (sel == gNorepeatSymbol.mHash) {
                stepRule = 2;
            } else if (i == 0) {
                bHaveFirst = true;
                firstSym = a->a_w.a_symbol;
            }
        }
    }

    if (!bHaveFirst && !bDynamic)
        return 0;

    void* allocator = System_GetAllocator();
    void* voiceMgr = GetVoiceManager();
    void* instance = CanvasGetCurrentInstance();
    t_play* x = (t_play*)pd_new(gpPlayClass);
    if (x) {
        x->play.Ctor(voiceMgr, instance, firstSym.mHash, firstSym.mpName,
                     steal, updatePlaying, stepRule, x);
    }
    if (!x->play.Init(allocator, floatArg, gUpdateTicks)) {
        pd_free(x);
        return 0;
    }
    x->pDoneOutlet = outlet_new(x, gBangSymbol);
    if (!x->pDoneOutlet) {
        pd_free(x);
        return 0;
    }
    x->bIsDynamic = bDynamic;
    x->pUpdateCallback = 0;
    return x;}

// ---------------------------------------------------------------------------
// @ 0x00a54520  EA::Audio::Eapd::play_start
// ---------------------------------------------------------------------------
void play_start(t_play* x, float time)
{
    x->play.Start(time);
    if (!x->pUpdateCallback)
        x->pUpdateCallback = ((PlayUpdateManager*)Play_GetUpdateManager())->AddCallback(x, (void*)play_update);
}
// ---------------------------------------------------------------------------
// @ 0x00a54560  EA::Audio::Eapd::play_startselect
// ---------------------------------------------------------------------------
void play_startselect(t_play* x, float group, float time)
{
    x->play.StartSelect((unsigned)(__int64)group, time);
    if (!x->pUpdateCallback)
        x->pUpdateCallback = ((PlayUpdateManager*)Play_GetUpdateManager())->AddCallback(x, (void*)play_update);
}

// ---------------------------------------------------------------------------
// @ 0x00a545d0  EA::Audio::Eapd::a_play_setup
// ---------------------------------------------------------------------------
bool a_play_setup()
{
    PgSymbol s;
    bool ok;

    gPlaySymbol       = *gensym(&s, "play");
    gStealSymbol      = *gensym(&s, "steal");
    gBlockSymbol      = *gensym(&s, "block");
    gSetplayingSymbol = *gensym(&s, "setplaying");
    gSetnextSymbol    = *gensym(&s, "setnext");
    gInorderSymbol    = *gensym(&s, "inorder");
    gRandomSymbol     = *gensym(&s, "random");
    gNorepeatSymbol   = *gensym(&s, "norepeat");

    gpPlayClass = class_new(gPlaySymbol, (void*)play_new, (void*)play_free, 0xec, 0, 9, 0);
    ok = gpPlayClass != 0;
    ok &= class_addcreator((void*)play_new, *gensym(&s, "dplay"), 9, 0);
    ok &= class_addmethod2(gpPlayClass, (void*)play_start, *gensym(&s, "start"), 5, 0);
    ok &= class_addmethod3(gpPlayClass, (void*)play_startselect, *gensym(&s, "startselect"), 1, 5, 0);    ok &= class_addmethod0(gpPlayClass, (void*)play_stop, *gensym(&s, "stop"), 0);
    ok &= class_addmethod1(gpPlayClass, (void*)play_pause, *gensym(&s, "pause"), 1, 0);
    ok &= class_addmethod1(gpPlayClass, (void*)play_use, *gensym(&s, "use"), 2, 0);
    ok &= class_addanything(gpPlayClass, (void*)play_anything);
    return ok;
}

// ---------------------------------------------------------------------------
// Arithmetic float atom classes: each broadcast a value to the object's outlets.
// ---------------------------------------------------------------------------
struct FAtomConnect {
    FAtomConnect* mpNext;    // +0x00
    void*         mpTo;      // +0x04
};

struct FAtomOutlet {
    void*         mpOwner;       // +0x00
    void*         mpNext;        // +0x04
    FAtomConnect* mpConnections; // +0x08
};

struct FAtom {
    uint32_t     mGobj[2];   // +0x00
    uint32_t     mBinbuf;    // +0x08
    FAtomOutlet* mpOutlet;   // +0x0c
    uint32_t     pad10[6];   // +0x10
    float        mF1;        // +0x28
    float        mF2;        // +0x2c
};

static __forceinline void Broadcast(FAtom* x, float f)
{
    FAtomOutlet* outlet = x->mpOutlet;
    if (++gOutletCount < 1000) {
        for (FAtomConnect* oc = outlet->mpConnections; oc != 0; oc = oc->mpNext)
            outlet_float(oc->mpTo, f);
    }
    --gOutletCount;
}

// @ 0x00a54890
void add_bang(FAtom* x)
{
    Broadcast(x, x->mF1 + x->mF2);
}

// @ 0x00a548f0
void add_float(FAtom* x, float f)
{
    float v = x->mF2;
    x->mF1 = f;
    float r = v + f;
    Broadcast(x, r);
}

// @ 0x00a549b0
void sub_bang(FAtom* x)
{
    Broadcast(x, x->mF1 - x->mF2);
}

// @ 0x00a54a10
void sub_float(FAtom* x, float f)
{
    x->mF1 = f;
    Broadcast(x, f - x->mF2);
}

// @ 0x00a54ad0
void mul_bang(FAtom* x)
{
    Broadcast(x, x->mF1 * x->mF2);
}

// @ 0x00a54b30
void mul_float(FAtom* x, float f)
{
    float v = x->mF2;
    x->mF1 = f;
    float r = v * f;
    Broadcast(x, r);
}

// @ 0x00a54bf0
void div_bang(FAtom* x)
{
    float d = x->mF2;
    float f = 0.0f;
    if (d != 0.0f)
        f = x->mF1 / d;
    Broadcast(x, f);
}

// @ 0x00a54c60
void div_float(FAtom* x, float f)
{
    float d = x->mF2;
    x->mF1 = f;
    if (d != 0.0f)
        f = f / d;
    else
        f = 0.0f;
    Broadcast(x, f);
}

// @ 0x00a54d30
void pow_bang(FAtom* x)
{
    float f;
    if (x->mF1 > 0.0f)
        f = (float)pow((double)x->mF1, (double)x->mF2);
    else
        f = 0.0f;
    Broadcast(x, f);
}

// @ 0x00a54db0
void pow_float(FAtom* x, float f)
{
    float d = x->mF2;
    x->mF1 = f;
    if (f > 0.0f)
        f = (float)pow((double)f, (double)d);
    else
        f = 0.0f;
    Broadcast(x, f);
}

// @ 0x00a54e80
void max_bang(FAtom* x)
{
    float f;
    if (x->mF1 > x->mF2)
        f = x->mF1;
    else
        f = x->mF2;
    Broadcast(x, f);
}

// @ 0x00a54ef0
void max_float(FAtom* x, float f)
{
    x->mF1 = f;
    float r;
    if (f > x->mF2)
        r = f;
    else
        r = x->mF2;
    Broadcast(x, r);
}

// @ 0x00a54fb0
void min_bang(FAtom* x)
{
    float f;
    if (x->mF1 < x->mF2)
        f = x->mF1;
    else
        f = x->mF2;
    Broadcast(x, f);
}

// @ 0x00a55020
void min_float(FAtom* x, float f)
{
    x->mF1 = f;
    float r;
    if (f < x->mF2)
        r = f;
    else
        r = x->mF2;
    Broadcast(x, r);
}

}}}  // namespace
