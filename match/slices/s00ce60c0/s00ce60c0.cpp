// Slice s00ce60c0 -- cTribeTokenTranslator accessors (partial).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

namespace SP {

struct cTokenTranslatorFields {
    void*     mpVtable0;                                     // +0x00
    uint32_t  mPad04;                                        // +0x04
    uint32_t  mPad08;                                        // +0x08
    uint32_t  mValue0c;                                      // +0x0c
    uint32_t  mValue10;                                      // +0x10
    uint32_t  mValue14;                                      // +0x14
    uint32_t  mValue18;                                      // +0x18
};

struct cTribeTokenTranslator {
    uint8_t mPad00[0x0c];                                    // +0x00 .. +0x0b
    float   mValue0c;                                        // +0x0c
    uint8_t mPad10[0x178];                                   // +0x10 .. +0x187
    float   mValues188[5];                                   // +0x188 .. +0x19b
    float   mValues19c[1];                                   // +0x19c .. +0x19f

    double GetValue188(int index);
    double GetValue19c(int index);
    double ComputeMass(struct cMassArg* arg);
};

struct cMassArg {
    uint8_t mPad00[0x554];                                   // +0x00 .. +0x553
    float   mValue554;                                       // +0x554
    float   mValue558;                                       // +0x558
};

extern "C" void BaseCivTokenTranslatorCtor();                // 0x00b32470
extern "C" double __cdecl ComputeDensity(SP::cMassArg* arg); // 0x00ce6960
extern "C" float gMassScale;                                 // 0x0150c8f8
extern "C" float gMassHalf;                                  // 0x01471064
extern "C" float gMassThreshold;                             // 0x015d9930

} // namespace SP

// @ 0x00ce6610
void* __fastcall TribeTokenTranslatorCtor(SP::cTokenTranslatorFields* self)
{
    ((void (__thiscall*)(void*))SP::BaseCivTokenTranslatorCtor)(self);
    self->mValue0c = 0;
    self->mValue10 = 0;
    self->mValue14 = 0;
    self->mValue18 = 0;
    self->mpVtable0 = (void*)0x01477a60;
    return self;
}

// @ 0x00ce68f0
double SP::cTribeTokenTranslator::GetValue188(int index)
{
    return mValues188[index];
}

// @ 0x00ce6910
double SP::cTribeTokenTranslator::GetValue19c(int index)
{
    return mValues19c[index];
}

// @ 0x00ce6a40
double SP::cTribeTokenTranslator::ComputeMass(SP::cMassArg* arg)
{
    double density = SP::ComputeDensity(arg);
    const float* pValue = &mValue0c;
    if (SP::gMassThreshold > mValue0c)
        pValue = &SP::gMassThreshold;
    double a = arg->mValue554;
    double b = arg->mValue558;
    double radial = 0.0;
    radial = sqrt(a * a + b * b);
    return ((density * SP::gMassScale) * *pValue) * radial * SP::gMassHalf;
}
