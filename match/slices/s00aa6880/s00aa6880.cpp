// slice s00aa6880 (batch gold3, slice 55): particle ArgScript colour commands and
// the ParticlesDescription copy constructor.
//   0x00aa6880  FUN_00aa6880                       (colour command Execute)
//   0x00aa6960  cLoopBoxColorCommand::Execute
//   0x00aa6a60  cMetaParticleLoopBoxColorCommand::Execute
//   0x00aa6bf0  EA::Swarm::CreateParticlesDescriptionCommand
//   0x00aa6c60  Swarm::ParticlesDescription::ParticlesDescription(const&)
//   0x00aa7220  FUN_00aa7220                       (single-colour command Execute)
//   0x00aa72a0  FUN_00aa72a0                       (colour + delay/ramp command Execute)
//   0x00aa73b0  FUN_00aa73b0                       (Build/ensure-description)
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (scalar SSE, no /EHsc).
#include "types.h"
#include <xmmintrin.h>
#include <new>

extern "C" char* strstr(const char* s, const char* sub);
static inline float sqrtf(float v) { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(v))); }

namespace EA {
namespace ArgScript {

class cArguments { public:
  const char** MainArguments(int* countOut, int minArgs, int maxArgs);
  const char** MainArguments(int minArgs);
  const char** MainArgumentsMin(const char** a, int minArgs);
  const char** OptionArguments(const char* name, int minArgs);
  const char** OptionArguments(const char* name, int* countOut, int minArgs, int maxArgs);
  bool  HasFlag(const char* name);
  const char* operator[](int index);
};

// Argument evaluator (+4 of the command): +0x98 float, +0xa8 Vector3, +0xb0 Vector3 into out.
struct cArgEval {
  virtual void e00(); virtual void e01(); virtual void e02(); virtual void e03();
  virtual void e04(); virtual void e05(); virtual void e06(); virtual void e07();
  virtual void e08(); virtual void e09(); virtual void e10(); virtual void e11();
  virtual void e12(); virtual void e13(); virtual void e14(); virtual void e15();
  virtual void e16(); virtual void e17(); virtual void e18(); virtual void e19();
  virtual void e20(); virtual void e21(); virtual void e22(); virtual void e23();
  virtual void e24(); virtual void e25(); virtual void e26(); virtual void e27();
  virtual void e28(); virtual void e29(); virtual void e30(); virtual void e31();
  virtual void e32(); virtual void e33(); virtual void e34(); virtual void e35();
  virtual void e36(); virtual void e37();
  virtual float  Evaluate(const char* text);                    // +0x98
  virtual void   e39(); virtual void e40(); virtual void e41();
  virtual float* EvaluateVector(float* out, const char* text);  // +0xa8
  virtual void   e43();
  virtual float* EvaluateVectorOut(float* out, const char* text, float a, float b); // +0xb0
};

}  // namespace ArgScript
}  // namespace EA

using namespace EA::ArgScript;

namespace SP {
// eastl::SimpleVector<float> / SpVector<float>
template <class T> struct SpVector {
  T*  mpBegin;
  T*  mpEnd;
  T*  mpCapacity;
  void resize(int n);                  // 0x004afc80
  void DoInsertValue(T* end, const T& v) { (void)end; (void)v; }
};
void BitDoInsertFloat(float* begin, float* end, int count);   // 0x011e0744
}  // namespace SP

// ---- external helpers ------------------------------------------------------------
void FUN_00aa3040(cArguments* args, int dst, void* eval);   // shared colour-atom parser
void FUN_004aa350(int n, int vec);                          // resize helper
void FUN_004afc80(int n);                                   // ?resize@?$SpVector@M@@QAEXH@Z
void FUN_007ecc30(uint32_t scale, int vec);                 // scale a float vector
struct DescInstaller { void Install(void* a, int b, void* desc); };  // 0x00a6f9c0 (__thiscall)
uint32_t g_descKeep1 = 0xff1e599d;   // 0x01679394
uint32_t g_descKeep2 = 0xff1a579e;   // 0x01679398
void FUN_006f50f0(void* v);
void FUN_00a87920(void* v);
void FUN_00a9a310(void* v);
void FUN_00a9a370(void* v);
void FUN_00a9a7f0(void* v);
void* operator_new(unsigned size, const char* tag, int a, int b, int c, int d);
void* EA_Swarm_ScaleCurve(void* end, void* value);          // 0x00a9xxxx
void* FUN_00aa2fe0(void* out, void* eval, void* a, void* b);

// The description object a command mutates; offset-addressed.
struct Desc {
  uint8_t p[0x2d0];
  template <class T> T& at(unsigned off) { return *(T*)(p + off); }

  void pushFloat(unsigned endOff, unsigned capOff, float v)
  {
    float* end = at<float*>(endOff);
    if (end < at<float*>(capOff)) {
      at<float*>(endOff) = end + 1;
      if (end) *end = v;
    } else {
      SP::SpVector<float> vec;
      vec.mpBegin = at<float*>(endOff - 4);
      vec.mpEnd = end;
      vec.mpCapacity = at<float*>(capOff);
      vec.DoInsertValue(end, v);
    }
  }

  // Clear the float vector at [off,off+8): eastl DoInsertValue(begin,end,0) then
  // mpEnd = begin.
  void clearFloat(unsigned off)
  {
    uint8_t* b = p + off;
    float* begin = *(float**)(b + 0);
    float* end   = *(float**)(b + 4);
    SP::BitDoInsertFloat(begin, end, 0);
    int n = (int)end - (int)begin;
    *(int*)(b + 4) = (int)end + (-((n >> 2) * 4));
  }
};

struct cCommand {
  uint8_t   pad00[0x04];
  cArgEval* mEval;      // +0x04
  uint8_t   pad08[0x04];
  Desc*     mDesc;      // +0x0c

  void ExecuteColorList(cArguments* args);
  void ExecuteLoopBoxColor(cArguments* args);
  void ExecuteMetaLoopBoxColor(cArguments* args);
  void ExecuteSingleColor(cArguments* args);
  void ExecuteColorRamp(cArguments* args);
  void BuildDescription(bool force);
};

// ================================================================================
// @ 0x00aa6880
// Parses an optional colour list into the description's vector at +0x70 and then
// runs the shared colour-atom parser over the description's +8 block (when any
// main argument was present).
void cCommand::ExecuteColorList(cArguments* args)
{
  int count = 0;
  const char** main = args->MainArguments(&count, 0, 0x7fffffff);
  Desc* d = mDesc;

  if (count > 0) {
    d->clearFloat(0x70);
    for (int i = 0; i < count; ++i)
      d->pushFloat(0x74, 0x78, mEval->Evaluate(main[i]));
  }

  FUN_00aa3040(args, (int)(d->p + 8), mEval);
}

// ================================================================================
// @ 0x00aa6960
// Loop-box colour: clears the colour curve at +0x18c, evaluates each main ColRGBA
// argument (+0xb0), optionally rescales by 1/255 on "255", sets flag 0x40000000
// and parses "orient".
void cCommand::ExecuteLoopBoxColor(cArguments* args)
{
  int count = 0;
  const char** main = args->MainArguments(&count, 1, 0x7fffffff);
  Desc* d = mDesc;

  FUN_004afc80(0);   // erase the colour vector at +0x18c

  for (int i = 0; i < count; ++i) {
    float v[3];
    float* r = mEval->EvaluateVectorOut(v, main[i], 0.0f, 0.0f);
    float* end = d->at<float*>(0x190);
    if (end < d->at<float*>(0x194)) {
      d->at<float*>(0x190) = end + 3;
      if (end) { end[0] = r[0]; end[1] = r[1]; end[2] = r[2]; }
    } else {
      EA_Swarm_ScaleCurve(end, r);
    }
  }

  const char* a0 = (*args)[0];
  if (a0 && strstr(a0, "255"))
    FUN_007ecc30(0x3b808081, (int)(d->p + 0x18c));

  d->at<uint32_t>(0x10) |= 0x40000000;
  args->HasFlag("orient");
}

// ================================================================================
// @ 0x00aa6a60
// Meta-particle loop-box colour: colour list at +0x1a0, optional 1/255 rescale,
// flag 0x40000000, "orient".
void cCommand::ExecuteMetaLoopBoxColor(cArguments* args)
{
  int count = 0;
  const char** main = args->MainArguments(&count, 1, 0x7fffffff);
  Desc* d = mDesc;

  d->clearFloat(0x1a0);

  for (int i = 0; i < count; ++i)
    d->pushFloat(0x1a4, 0x1a8, mEval->Evaluate(main[i]));

  const char* a0 = (*args)[0];
  if (a0 && strstr(a0, "255")) {
    float* begin = d->at<float*>(0x1a0);
    int n = (int)(d->at<float*>(0x1a4) - begin);
    for (int i = 0; i < n; ++i)
      begin[i] = begin[i] * 0.003921569f;
  }

  d->at<uint32_t>(0x10) |= 0x40000000;
  args->HasFlag("orient");
}

// ================================================================================
// @ 0x00aa6bf0
// A command object: vtable at +0, base AppPropsFields ctor, a nested ctor at +0x40,
// then a description pointer and magic tag.
struct AppPropsFields { char m[0x34]; AppPropsFields(); };           // ctor 0x0083cdd0
struct Mid38 { uint32_t tag38; char gap3c[4]; };                     // view at +0x38
struct Sub40 { char m[0x2b8 - 0x40]; void Ctor(); };                 // ctor 0x00aa3460
struct ParticleEffectCommand : AppPropsFields {
  uint32_t pad34;      // +0x34
  Mid38    mid38;      // +0x38 (tag38) .. +0x40
  Sub40    sub40;      // +0x40 .. +0x2b8
  uint32_t tag2b8;     // +0x2b8
  uint32_t tag2bc;     // +0x2bc
  uint32_t tag2c0;     // +0x2c0
};
void* CreateParticlesDescriptionCommand(void* param_1)
{
  ParticleEffectCommand* p = (ParticleEffectCommand*)operator_new(0x2d0, "ArgScript/ParticleEffect", 0, 0, 0, 0);
  if (p) {
    p->AppPropsFields::AppPropsFields();
    *(uint32_t*)p = 0x01458dfc;
    p->pad34 = (uint32_t)(unsigned)param_1;
    p->mid38.tag38 = 0xeba93c76;
    Sub40* s = &p->sub40;
    s->Ctor();
    uint32_t tag = 0x01667bac;
    p->tag2b8 = tag;
    p->tag2bc = tag;
    p->tag2c0 = 0x01667bad;
  }
  return p;
}

// ================================================================================
// @ 0x00aa6c60
// ParticlesDescription(const ParticlesDescription& src): copies src's plain dword
// fields and deep-copies each owned float vector (the +0x68/+0x88/+0xa0/+0xb8/
// +0xf4/+0x198/+0x240 vectors), then runs the nested sub-object copy helpers.
struct ParticlesDescription {
  uint8_t m[0x270];
  ParticlesDescription(const ParticlesDescription& src);
};

// ================================================================================
// @ 0x00aa7220
// Single flat colour: forces a 1-entry colour vector at +0x70, stores the value,
// sets flag bit 0 and the default alpha/params, then runs the shared parser.
void cCommand::ExecuteSingleColor(cArguments* args)
{
  const char** main = args->MainArguments(1);

  ((SP::SpVector<float>*)(mDesc->p + 0x70))->resize(1);
  float* dst = mDesc->at<float*>(0x70);
  *dst = mEval->Evaluate(main[0]);

  mDesc->at<uint32_t>(0x10) |= 1;
  mDesc->at<float>(0x84) = 0.01f;
  mDesc->at<uint16_t>(0x88) = 1;

  FUN_00aa3040(args, (int)(mDesc->p + 8), mEval);
}

// ================================================================================
// @ 0x00aa72a0
// Colour ramp: 1-entry colour at +0x70, flag 0x2, optional "delay" (+0x24/+0x28),
// and a "hold"/"kill" option setting flag 0x10000000 or 0x8000000 + bit 0x14:1.
void cCommand::ExecuteColorRamp(cArguments* args)
{
  const char** main = args->MainArgumentsMin((const char**)0, 1);
  Desc* d = mDesc;

  FUN_004afc80(1);
  float* dst = d->at<float*>(0x70);
  *dst = mEval->Evaluate(main[0]);

  d->at<uint32_t>(0x10) |= 2;

  {
    int cnt = 0;
    const char** dl = args->OptionArguments("delay", &cnt, 1, 2);
    if (dl) {
      float v[2];
      float* r = (float*)FUN_00aa2fe0(v, mEval, (void*)0, (void*)0);
      d->at<float>(0x24) = r[0];
      d->at<float>(0x28) = r[1];
    }
  }

  int rcnt = 0;
  const char** ramp = args->OptionArguments("hold", &rcnt, 1, 0x7fffffff);
  if (ramp == 0) {
    int cnt = 0;
    ramp = args->OptionArguments("kill", &cnt, 1, 2);
    if (ramp == 0)
      return;
    d->at<uint32_t>(0x10) |= 0x8000000;
    d->at<uint32_t>(0x14) |= 1;
  } else {
    d->at<uint32_t>(0x10) |= 0x10000000;
  }

  d->at<float>(0x84) = mEval->Evaluate(ramp[0]);
  d->at<uint16_t>(0x88) = 1;
}

// ================================================================================
// @ 0x00aa73b0
// Build/refresh the description: unless forced, latch the effect state byte at
// +0x170, allocate a 0x270-byte ParticlesDescription copy-constructed from the
// object at +0x40, install it, then terminate the pending byte vector at +0x2b8.
void cCommand::BuildDescription(bool force)
{
  uint8_t* self = (uint8_t*)this;
  if (!force) {
    if (*(uint8_t*)(self + 0x2c8))
      *(uint32_t*)(self + 0x48) |= 0x80000000;
    if (*(uint8_t*)(self + 0x170) == 0) {
      if (*(bool*)(self + 0x2c8) != 0) {
        *(uint8_t*)(self + 0x170) = 2;
      } else {
        if (((g_descKeep2 & *(uint32_t*)(self + 0x4c)) |
             (g_descKeep1 & *(uint32_t*)(self + 0x48))) != 0)
          *(uint8_t*)(self + 0x170) = 1;
      }
    }
    void* p = operator_new(0x270, "Swarm/ParticlesDescription", 0, 0, 0, 0);
    ParticlesDescription* desc =
        p ? ::new ((void*)p) ParticlesDescription(*(const ParticlesDescription*)(self + 0x40))
          : (ParticlesDescription*)0;
    ((DescInstaller*)*(void**)(self + 0x30))->Install(*(void**)(self + 0x2b8),
                                                      *(int*)(self + 0x34), desc);
  }
  if (*(uint8_t**)(self + 0x2b8) != *(uint8_t**)(self + 0x2bc)) {
    **(uint8_t**)(self + 0x2b8) = 0;
    *(uint32_t*)(self + 0x2bc) = (uint32_t)(unsigned)*(uint8_t**)(self + 0x2b8);
  }
}

// ================================================================================
// ParticlesDescription(const ParticlesDescription&) — see declaration at 0x00aa6c60.
ParticlesDescription::ParticlesDescription(const ParticlesDescription& src)
{
  uint32_t* dst = (uint32_t*)m;
  const uint8_t* s = src.m;
  dst[1] = 0;
  dst[0] = 0x01458d00;   // ParticlesDescription vtable (0x01458dxx placeholder)
  for (int i = 2; i <= 0x19; ++i)
    dst[i] = *(const uint32_t*)(s + i * 4);

  FUN_004aa350((*(int*)(s + 0x6c) - *(int*)(s + 0x68)) >> 2, (int)(s + 0x74));
  FUN_004aa350((*(int*)(s + 0x8c) - *(int*)(s + 0x88)) >> 2, (int)(s + 0x94));
  FUN_004aa350((*(int*)(s + 0xa4) - *(int*)(s + 0xa0)) >> 2, (int)(s + 0xac));
  FUN_004aa350((*(int*)(s + 0xbc) - *(int*)(s + 0xb8)) >> 2, (int)(s + 0xc4));
  FUN_004aa350((*(int*)(s + 0xf8) - *(int*)(s + 0xf4)) >> 2, (int)(s + 0x100));
  FUN_004aa350((*(int*)(s + 0x19c) - *(int*)(s + 0x198)) >> 2, (int)(s + 0x1a4));
  FUN_004aa350((*(int*)(s + 0x244) - *(int*)(s + 0x240)) >> 2, (int)(s + 0x24c));

  for (int i = 0x44; i <= 0x4b; ++i)
    dst[i] = *(const uint32_t*)(s + i * 4);
  FUN_006f50f0((void*)(s + 0xd4));
  FUN_00a9a310((void*)(s + 0x16c));
  FUN_006f50f0((void*)(s + 0x184));
  FUN_00a87920((void*)(s + 0x1ac));
  FUN_00a9a7f0((void*)(s + 0x200));
  FUN_00a9a370((void*)(s + 0x25c));
}
