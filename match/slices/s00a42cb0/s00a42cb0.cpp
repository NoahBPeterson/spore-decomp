// Slice s00a42cb0 -- SP::Audio::cSystem::ReadTuningValues (00a43a50): reads the tuning values for a resource key,
// then pushes the two float tuning values into the EAPD singleton.
// Module flags (guess, verify): /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace SP {

extern uint32_t gTuningGroupID;                 // 0x015541dc (no PDB name)

struct ResourceKey { uint32_t instanceID; uint32_t typeID; uint32_t groupID; };

struct EAAudioSystemTuning {                    // EA::Audio::System base at this+0; only ReadTuningValues is used here
    bool ReadTuningValues(const ResourceKey* key);   // 0x00a29be0, thiscall, ret 4
};

struct EAPDSystemTuning {                       // EA::Audio::Eapd::ISystem (singleton)
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void SetValue5(float v);            // vtable +0x14
    virtual void SetValue6(float v);            // vtable +0x18
    static EAPDSystemTuning* GetSingletonPtr(); // 0x00a67c60, no args
};

struct TuningReaderStub {                       // object at cSystem +0x1f8
    virtual void slot0();  virtual void slot1();  virtual void slot2();  virtual void slot3();
    virtual void slot4();  virtual void slot5();  virtual void slot6();  virtual void slot7();
    virtual void slot8();  virtual void slot9();  virtual void slot10(); virtual void slot11();
    virtual void ReadFloatById(uint32_t id, float* out);   // vtable +0x30, ret 8
};

struct EventModifierTuning {
    void ReadTuningValues(const ResourceKey* key);         // 0x00a39f90, thiscall, ret 4
};

struct cSystemTuning {                          // SP::Audio::cSystem, only the fields this function touches
    EAAudioSystemTuning base;                   // +0x0 (empty placeholder, size 1)
    char pad0[0x1f8 - 1];
    TuningReaderStub* mpTuningReader;           // +0x1f8
    char pad1[0x15bc78 - 0x1fc];
    EventModifierTuning* mpEventModifier;       // +0x15bc78
    char pad2[0x15bcd8 - 0x15bc7c];
    float mTuneA;                               // +0x15bcd8
    float mTuneB;                               // +0x15bcdc

    void AddSymbolList(uint32_t id);            // 0x00a43580, thiscall, ret 4
    void ReadPolyphonyCounters();               // 0x00a42cb0, thiscall, no args
    bool ReadTuningValues(const ResourceKey* key);
};

// @ 0x00a43a50
bool cSystemTuning::ReadTuningValues(const ResourceKey* key) {
    if (!base.ReadTuningValues(key)) return false;
    if (key->groupID == gTuningGroupID) AddSymbolList(key->instanceID);
    if (mpEventModifier) mpEventModifier->ReadTuningValues(key);
    ReadPolyphonyCounters();
    mTuneA = 0.0f;
    mpTuningReader->ReadFloatById(0xdacee1bd, &mTuneA);
    mTuneB = 0.01f;
    mpTuningReader->ReadFloatById(0x1c05b1a7, &mTuneB);
    EAPDSystemTuning* sys = EAPDSystemTuning::GetSingletonPtr();
    if (sys) {
        sys->SetValue5(mTuneA);
        sys->SetValue6(mTuneB);
    }
    return true;
}

}  // namespace SP
