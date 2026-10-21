// slice s00aa5940 (batch gold3, slice 54): Spore particle ArgScript command executors.
//   0x00aa5940  FUN_00aa5940                        (colour/opacity command Execute)
//   0x00aa5ab0  cParticleSizeCommand::Execute
//   0x00aa5bb0  cParticleAspectCommand::Execute
//   0x00aa5cb0  cParticleRotateCommand::Execute
//   0x00aa5de0  cParticleForceCommand::Execute
//   0x00aa61c0  cParticleWarpCommand::Execute
//   0x00aa6590  cParticleLifeCommand::Execute
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (scalar SSE, no /EHsc).
#include "types.h"
#include <xmmintrin.h>

extern "C" char* strstr(const char* s, const char* sub);
static inline float sqrtf(float v) { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(v))); }

namespace SP {
void BitDoInsertFloat(float* begin, float* end, int count);   // 0x011e0744
// eastl::SimpleVector<float> (template so the member mangles exactly as the
// original's ?DoInsertValue@?$SimpleVector@M@SP@@QAEXPAMABM@Z; the body is
// never used — resolve.py redirects the call to the original image).
template <class T> struct SimpleVector {
  T*  mpBegin;
  T*  mpEnd;
  T*  mpCapacity;
  void DoInsertValue(T* end, const T& v);
  void clear()
  {
    T* begin = mpBegin;
    T* end   = mpEnd;
    SP::BitDoInsertFloat((float*)begin, (float*)end, 0);
    int n = (int)end - (int)begin;
    mpEnd += -(n >> 2);
  }
  void push_back(const T& v)
  {
    T* end = mpEnd;
    if (end < mpCapacity) {
      mpEnd = end + 1;
      if (end) *end = v;
    } else {
      DoInsertValue(end, v);
    }
  }
};
}  // namespace SP

namespace EA {
namespace ArgScript {

// Argument list passed to an Execute() method (real decorated names in use).
class cArguments { public:
  const char** MainArguments(int* countOut, int minArgs, int maxArgs);
  const char** OptionArguments(const char* name, int minArgs);
  const char** OptionArguments(const char* name, int* countOut, int minArgs, int maxArgs);
  bool  HasFlag(const char* name);
  const char* operator[](int index);
};

// The numeric/vector argument evaluator reached through the executor's +4 field.
// Slots used: +0x98 (float evaluate), +0xa8 (Vector3 evaluate).
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
  virtual float Evaluate(const char* text);                    // +0x98
  virtual void  e39();
  virtual void  e40();
  virtual void  e41();
  virtual float* EvaluateVector(float* out, const char* text);// +0xa8
};

}  // namespace ArgScript
}  // namespace EA

using namespace EA::ArgScript;

// float ParseRangedFloat(int* evaluator, const char* text, float lo, float hi)
float ParseRangedFloat(void* evaluator, const char* text, float lo, float hi);

// ---- external helpers ------------------------------------------------------------
void FUN_00a9a7a0(float* v);         // 0x00a9a7a0 (wiggle transform setup)

float g_piOver180 = 0.017453292f;    // 0x01679348
float g_timeScale = 1.0f;            // 0x016792c0
float g_sinTable[32];                // 0x01677840 (16-entry sin/cos pairs)
float g_defaultGravity[3] = {0.0f, 0.0f, -1.0f};  // 0x016792c4

// The particle description a command mutates. All accesses go through +off.
struct Desc {
  uint8_t p[0x280];

  template <class T> T& at(unsigned off) { return *(T*)(p + off); }
  SP::SimpleVector<float>* vec(unsigned off) { return (SP::SimpleVector<float>*)(p + off); }

  // eastl/SimpleVector<float> push_back: end at endOff, capacity at capOff.
  void pushFloat(unsigned endOff, unsigned capOff, float v)
  {
    (void)capOff;
    ((SP::SimpleVector<float>*)(p + endOff - 4))->push_back(v);
  }
  // Clear the float vector at [off,off+8): eastl::vector<bool>::DoInsertValue(
  // begin,end,0) followed by mpEnd = begin.
  void clearFloat(unsigned off)
  {
    SP::SimpleVector<float>* v = (SP::SimpleVector<float>*)(p + off);
    float* begin = v->mpBegin;
    float* end   = v->mpEnd;
    SP::BitDoInsertFloat(begin, end, 0);
    int n = (int)end - (int)begin;      // byte difference
    v->mpEnd += -(n >> 2);              // == begin
  }
};
struct cCommand {
  uint8_t  pad00[0x04];
  cArgEval* mEval;      // +0x04
  uint8_t  pad08[0x04];
  Desc*    mDesc;       // +0x0c

  void ExecuteColor(cArguments* args);
  void cParticleSizeExecute(cArguments* args);
  void cParticleAspectExecute(cArguments* args);
  void cParticleRotateExecute(cArguments* args);
  void cParticleForceExecute(cArguments* args);
  void cParticleWarpExecute(cArguments* args);
  void cParticleLifeExecute(cArguments* args);
};

// ================================================================================
// @ 0x00aa5940
// Colour/opacity command: parses the main colour list into the description's
// colour vector at +0xfc, the "vary" option into +0x110, and rescales by 1/255
// when the first argument contains "255".
void cCommand::ExecuteColor(cArguments* args)
{
  int count = 0;
  const char** main = args->MainArguments(&count, 1, 0x7fffffff);
  Desc* d = mDesc;

  d->clearFloat(0xfc);

  for (int i = 0; i < count; ++i)
    d->pushFloat(0x100, 0x104, mEval->Evaluate(main[i]));

  const char** opt = args->OptionArguments("vary", 1);
  if (opt)
    d->at<float>(0x110) = ParseRangedFloat(mEval, *opt, 0.0f, 1.0f);

  const char* a0 = (*args)[0];
  if (a0 && strstr(a0, "255")) {
    float* begin = d->at<float*>(0xfc);
    int n = (int)(d->at<float*>(0x100) - begin);
    for (int i = 0; i < n; ++i)
      begin[i] = begin[i] * 0.003921569f;
  }
}

// ================================================================================
// @ 0x00aa5ab0
void cCommand::cParticleSizeExecute(cArguments* args)
{
  int count = 0;
  const char** main = args->MainArguments(&count, 1, 0x7fffffff);
  Desc* d = mDesc;

  d->clearFloat(0x90);

  for (int i = 0; i < count; ++i)
    d->vec(0x90)->push_back(mEval->Evaluate(main[i]));

  const char** opt = args->OptionArguments("vary", 1);
  if (opt)
    d->at<float>(0xa4) = ParseRangedFloat(mEval, *opt, 0.0f, 1.0f);
}

// ================================================================================
// @ 0x00aa5bb0
void cCommand::cParticleAspectExecute(cArguments* args)
{
  int count = 0;
  const char** main = args->MainArguments(&count, 1, 0x7fffffff);
  Desc* d = mDesc;

  d->clearFloat(0xa8);

  for (int i = 0; i < count; ++i)
    d->pushFloat(0xac, 0xb0, mEval->Evaluate(main[i]));

  const char** opt = args->OptionArguments("vary", 1);
  if (opt)
    d->at<float>(0xbc) = ParseRangedFloat(mEval, *opt, 0.0f, 1.0f);
}

// ================================================================================
// @ 0x00aa5cb0
void cCommand::cParticleRotateExecute(cArguments* args)
{
  int count = 0;
  const char** main = args->MainArguments(&count, 1, 0x7fffffff);
  Desc* d = mDesc;

  d->clearFloat(0xc0);

  for (int i = 0; i < count; ++i)
    d->pushFloat(0xc4, 0xc8, mEval->Evaluate(main[i]));

  const char** opt = args->OptionArguments("vary", 1);
  if (opt)
    d->at<float>(0xd4) = ParseRangedFloat(mEval, *opt, 0.0f, 1.0f);

  const char** off = args->OptionArguments("offset", 2);
  if (off)
    d->at<float>(0xd8) = mEval->Evaluate(*off);
}

// ================================================================================
// @ 0x00aa5de0
void cCommand::cParticleForceExecute(cArguments* args)
{
  args->MainArguments((int*)0, 0, 0);
  Desc* d = mDesc;

  if (args->HasFlag("reset")) {
    d->at<float>(0x144) = g_defaultGravity[0];
    d->at<float>(0x148) = g_defaultGravity[1];
    d->at<float>(0x14c) = g_defaultGravity[2];
  }

  {
    const char** g = args->OptionArguments("gravity", 1);
    if (g)
      d->at<float>(0x14c) = d->at<float>(0x14c) - mEval->Evaluate(*g);
  }

  {
    int cnt = 0;
    const char** dir = args->OptionArguments("wind", &cnt, 1, 0x7fffffff);
    if (dir) {
      float tmp[3];
      float* v = mEval->EvaluateVector(tmp, *dir);
      float inv = 1.0f / sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + 1e-08f);
      float x = v[0] * inv, y = v[1] * inv, z = v[2] * inv;
      if (cnt > 1) {
        float s = mEval->Evaluate(dir[1]);
        x *= s; y *= s; z *= s;
      }
      d->at<float>(0x144) += x;
      d->at<float>(0x148) += y;
      d->at<float>(0x14c) += z;
    }
  }

  {
    const char** ww = args->OptionArguments("worldWind", 1);
    if (ww)
      d->at<float>(0x150) = mEval->Evaluate(*ww);
  }
  {
    const char** wg = args->OptionArguments("worldGravity", 1);
    if (wg)
      d->at<float>(0x154) = mEval->Evaluate(*wg);
  }
  {
    int cnt = 0;
    const char** air = args->OptionArguments("bomb", &cnt, 1, 2);
    if (air) {
      d->at<float>(0x158) = mEval->Evaluate(*air);
      if (cnt > 1) {
        float tmp[3];
        float* v = mEval->EvaluateVector(tmp, air[1]);
        d->at<float>(0x15c) = v[0];
        d->at<float>(0x160) = v[1];
        d->at<float>(0x164) = v[2];
      }
    }
  }
  {
    int cnt = 0;
    const char** bf = args->OptionArguments("drag", &cnt, 1, 2);
    if (bf)
      d->at<float>(0x168) = mEval->Evaluate(*bf);
  }

  int have = 0;
  const char** rest = 0;
  {
    int cnt = 0;
    const char** at = args->OptionArguments("attractor", &cnt, 3, 0x7fffffff);
    if (at) {
      float tmp[3];
      float* v = mEval->EvaluateVector(tmp, *at);
      d->at<float>(0x23c) = v[0];
      d->at<float>(0x240) = v[1];
      d->at<float>(0x244) = v[2];
      have = cnt - 1;
      rest = at + 1;
    } else {
      int c2 = 0;
      rest = args->OptionArguments("presetAttractor", &c2, 2, 0x7fffffff);
      if (!rest)
        return;
      have = c2;
    }
  }

  d->at<float>(0x25c) = mEval->Evaluate(*rest);
  d->clearFloat(0x248);

  for (int i = 1; i < have; ++i)
    d->pushFloat(0x24c, 0x250, mEval->Evaluate(rest[i]));

  d->at<uint32_t>(0x10) |= 0x800000;
  if (have > 0)
    d->at<uint32_t>(0x10) |= 0x1000000;
  else
    d->at<uint32_t>(0x10) &= ~0x1000000u;

  {
    const char** kr = args->OptionArguments("killRange", 1);
    if (kr)
      d->at<float>(0x260) = mEval->Evaluate(*kr);
  }
}

// ================================================================================
// @ 0x00aa61c0
void cCommand::cParticleWarpExecute(cArguments* args)
{
  args->MainArguments((int*)0, 0, 0);
  Desc* d = mDesc;

  {
    const char** s = args->OptionArguments("screw", 1);
    if (s)
      d->at<float>(0x170) = mEval->Evaluate(*s);
  }
  {
    const char** sp = args->OptionArguments("spiral", 1);
    if (sp) {
      d->at<float>(0x170) = mEval->Evaluate(*sp);
      d->at<uint32_t>(0x10) |= 0x20000000;
    }
  }
  {
    const char** w = args->OptionArguments("wiggle", 4);
    if (w) {
      float amp = mEval->Evaluate(w[0]);
      float freq = mEval->Evaluate(w[1]);
      float phase = mEval->Evaluate(w[2]);
      float rnd = ParseRangedFloat(mEval, w[3], 0.0f, 1.0f);

      float scaled = g_timeScale * (0.5f * rnd) + 12582912.0f;
      uint32_t idx = (uint32_t)scaled & 0xf;
      float sc = g_sinTable[idx * 2];
      float cc = g_sinTable[idx * 2 + 1];
      float frac = 0.5f * rnd - (float)((int)scaled - 0x4b400000) * g_piOver180;

      float w1 = -(((cc - (sc * frac) * 0.5f) * frac + sc) * phase);
      float w2 = (cc - ((cc * frac) * 0.5f + sc) * frac) * phase;

      float wig[5];
      wig[0] = amp;   // amplitude
      wig[1] = freq;  // frequency
      wig[2] = 0.0f;
      wig[3] = w2;
      wig[4] = w1;
      (void)frac;
      FUN_00a9a7a0(wig);
    }
  }
  {
    int cnt = 0;
    const char** wd = args->OptionArguments("wiggleDir", &cnt, 2, 3);
    if (wd) {
      float x = mEval->Evaluate(wd[0]);
      float tmp[3];
      float* v = mEval->EvaluateVector(tmp, wd[1]);
      float dir[3];
      dir[0] = v[0]; dir[1] = v[1]; dir[2] = v[2];
      float axis[3];
      axis[0] = g_defaultGravity[0];
      axis[1] = g_defaultGravity[1];
      axis[2] = g_defaultGravity[2];
      if (cnt > 2) {
        float t2[3];
        float* v2 = mEval->EvaluateVector(t2, wd[2]);
        axis[0] = v2[0]; axis[1] = v2[1]; axis[2] = v2[2];
      }
      (void)x;
      FUN_00a9a7a0(dir);
    }
  }
  {
    const char** ba = args->OptionArguments("bloomAlpha", 2);
    if (ba) {
      float v0 = mEval->Evaluate(ba[0]);
      float c0 = v0 < 0.0f ? 0.0f : v0;
      c0 *= 255.0f;
      if (c0 > 255.0f) c0 = 255.0f;
      d->at<uint8_t>(0x189) = (uint8_t)(int)(c0 + 0.5f);

      float v1 = mEval->Evaluate(ba[1]) * 0.0625f;
      float c1 = v1 < 0.0f ? 0.0f : v1;
      c1 *= 255.0f;
      if (c1 > 255.0f) c1 = 255.0f;
      d->at<uint8_t>(0x188) = (uint8_t)(int)(c1 + 0.5f);
    }
  }
  {
    const char** bs = args->OptionArguments("bloomSize", 2);
    if (bs) {
      float v0 = mEval->Evaluate(bs[0]);
      float c0 = v0 < 0.0f ? 0.0f : v0;
      c0 *= 255.0f;
      if (c0 > 255.0f) c0 = 255.0f;
      d->at<uint8_t>(0x18b) = (uint8_t)(int)(c0 + 0.5f);

      float v1 = mEval->Evaluate(bs[1]) * 0.0625f;
      float c1 = v1 < 0.0f ? 0.0f : v1;
      c1 *= 255.0f;
      if (c1 > 255.0f) c1 = 255.0f;
      d->at<uint8_t>(0x18a) = (uint8_t)(int)(c1 + 0.5f);
    }
  }
}

// ================================================================================
// @ 0x00aa6590
void cCommand::cParticleLifeExecute(cArguments* args)
{
  int count = 0;
  const char** main = args->MainArguments(&count, 0, 0x7fffffff);
  Desc* d = mDesc;

  for (int i = 0; i < count; ++i)
    d->pushFloat(0x228, 0x22c, ParseRangedFloat(mEval, main[i], -1.0f, 1.0f));

  d->at<uint32_t>(0x10) |= 0x80000;

  {
    int cnt = 0;
    const char** dl = args->OptionArguments("delay", &cnt, 1, 2);
    if (dl) {
      float lo = mEval->Evaluate(dl[0]);
      float hi = 0.0f;
      if (cnt > 1)
        hi = mEval->Evaluate(dl[1]);
      d->at<float>(0x208) = lo - hi;
      d->at<float>(0x20c) = lo + hi;
    }
  }
  {
    int cnt = 0;
    const char** st = args->OptionArguments("strength", &cnt, 1, 2);
    if (st) {
      float lo = mEval->Evaluate(st[0]);
      float hi = 0.0f;
      if (cnt > 1)
        hi = mEval->Evaluate(st[1]);
      d->at<float>(0x210) = lo - hi;
      d->at<float>(0x214) = lo + hi;
    }
  }
  {
    int cnt = 0;
    const char** rt = args->OptionArguments("randomTurn", &cnt, 1, 0x7fffffff);
    if (!rt) {
      d->at<uint32_t>(0x218) = 0;
      d->at<uint32_t>(0x21c) = 0;
    } else {
      d->at<float>(0x218) = ParseRangedFloat(mEval, rt[0], 0.0f, 1.0f);
      if (cnt < 2)
        d->at<uint32_t>(0x21c) = 0;
      else
        d->at<float>(0x21c) = ParseRangedFloat(mEval, rt[1], 0.0f, 1.0f);
    }
  }

  d->at<uint8_t>(0x238) = 2;
  if (args->HasFlag("sustain"))
    d->at<uint8_t>(0x238) = 1;
  if (args->HasFlag("loop"))
    d->at<uint8_t>(0x238) = 0;

  {
    const char** ir = args->OptionArguments("mix", 1);
    if (ir)
      d->at<float>(0x220) = ParseRangedFloat(mEval, *ir, 0.0f, 1.0f);
  }

  if (args->HasFlag("wait"))
    d->at<uint32_t>(0x10) |= 0x100000;
}
