// Slice s00628d50: SP::cSPPlayMode button handling and baby helpers (retail layout, raw offsets).
#include "types.h"
#include <math.h>

struct V3 {
  float x, y, z;
  V3() {}
  V3(float a, float b, float c) : x(a), y(b), z(c) {}
  V3(const V3& o) : x(o.x), y(o.y), z(o.z) {}
  V3& operator=(const V3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
inline V3 operator-(const V3& a, const V3& b) { return V3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline V3 operator-(const V3& a) { return V3(-a.x, -a.y, -a.z); }

extern const V3 gUpAxis;      // 0x15f6ee8
extern const float gAngleRef; // 0x15f6e6c (opaque constant block)
extern const float gHalf;     // 0x1471064

namespace EA { namespace Audio {
struct ISystem { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void* Notify(); };
ISystem* GetSystemAT();
} }
void KillSetiEffects(uint32_t id, void* sys);   // SP::cSPUISpace::KillSetiEffects (cdecl)

struct Animator {
  virtual void v0(); virtual void v1(); virtual void v2();
  virtual float Play(uint32_t creature, uint32_t anim, int a, int b, int c);  // +0x0c
};

struct Baby {
  uint32_t id;
  uint8_t pad0[0x14];
  uint8_t b18;      // +0x18
  uint8_t spawned;  // +0x19
  uint8_t b1a;      // +0x1a
  int8_t state;     // +0x1b
  int8_t callState; // +0x1c
  uint8_t pad1[3];
  float t20;        // +0x20
  float timer;      // +0x24
  float timer2;     // +0x28
  uint8_t pad2[4];
};

struct Creature {
  virtual void v0(); virtual void v1();
  virtual uint32_t A(uint32_t a, int b);      // +0x08
  virtual void B(uint32_t h, int b);          // +0x0c
  virtual void v4(); virtual void v5();
  virtual void C(uint32_t h);                 // +0x18
  virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13();
  virtual void D(uint32_t h, float f);        // +0x38
  virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21();
  virtual void F(uint32_t* a, uint32_t* b, uint32_t* c, int d);  // +0x58
  virtual void v23();
  virtual float E(uint32_t h);                // +0x60
  bool IsOrientIdleAnim(uint32_t anim);   // 0x00a027a0 (equiv t2)
};

struct CreatureStruct {
  uint32_t pad0[2];
  Creature* anim;     // +0x08
  uint32_t pad1[(0x48 - 0x0c) / 4];
  float angle;        // +0x48
  float f4c;          // +0x4c
  float f50;          // +0x50
};

struct RandomLinearCongruential {
  uint32_t seed;
  void SetSeed(uint32_t s);
  uint32_t RandomUint32Uniform(uint32_t n);
};

struct DanceSub { bool IsDancingAnim(uint32_t anim, int flag); };
struct ActionSub { float SetIdleAnimation(Creature* c, uint32_t id, int a, int b); };

struct BabyVec {
  Baby* mpBegin;
  Baby* mpEnd;
  uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
  int ssize() const { return (int)(mpEnd - mpBegin); }
  uint32_t IDAt(uint32_t i) {
    uint32_t n = size();
    Baby* b = mpBegin;
    if (n == 0) return 0xffffffff;
    if (i < n) return b[i].id;
    return b[0].id;
  }
  Baby* begin() { return mpBegin; }
  Baby* end() { return mpEnd; }
  Baby& operator[](uint32_t i) { return *(i + mpBegin); }
};

struct Flagged { uint32_t pad; uint32_t flags; };

struct CreatureMgr {
  Creature* GetCreature(uint32_t id);   // 0x0059ca70 (equiv t2)
  void GetCreaturePosition(uint32_t id, V3* out);   // 0x0059d110 (equiv t2)
  CreatureStruct* GetCreatureStructure(uint32_t id);
  bool IsPlayingAnimation(uint32_t id);   // 0x0059cd20 (equiv t2)
};

struct Editor {
  uint32_t pad0[0x2b];
  Flagged* flagged;            // +0xac
  uint32_t pad1[(0x360 - 0xb0) / 4];
  CreatureMgr* mgr;            // +0x360
  uint32_t momId;              // +0x364
  uint32_t pad2;
  BabyVec babies;              // +0x36c
  void FUN_00574110(uint32_t id, int a, float b, float c);
  void FUN_005dbbb0(int v);
};

struct SubMode { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
  virtual bool HandleButton(uint32_t id); };   // +0x2c

struct ButtonState {
  bool FUN_0062f7f0(int id);
  bool FUN_0062f6c0();
};

class cSPPlayMode {
 public:
  uint32_t pad00[8];
  uint8_t mFlag20;                          // +0x20
  uint8_t pad20[3];
  uint32_t mCrouchBaby;                     // +0x24
  uint32_t pad28[5];
  float mMomCrouchChangeTime;               // +0x3c
  float mBabyCelebratingChangeTime[3];      // +0x40
  uint32_t pad1[(0xc8 - 0x4c) / 4];
  SubMode* mSubModes[4];                    // +0xc8
  uint32_t pad2[(0x3588 - 0xd8) / 4];
  Animator mAnimator;                       // +0x3588
  uint32_t pad3[(0x3614 - 0x358c) / 4];
  Editor* mEditor;                          // +0x3614
  ButtonState mButtons;                     // +0x3618
  uint8_t pad4[0x36d0 - 0x3619];
  uint8_t mNumBabies;                       // +0x36d0

  bool HandleButton(int id);
  void SetMomToFaceBaby(uint32_t baby);
  uint32_t GetLatestBabyID();
  int GetLatestBabyIndex();
  uint32_t GetAnimatedBabyIndex(uint32_t id);
  uint32_t FUN_006291d0(uint32_t index);
  void SetAllBabySitUp();
  uint32_t GetRandomEnvironmentReactionAnim();
  void SendButtonEventToBabies(bool b);
  void SetAllOtherBabiesToIdle(uint32_t id, uint32_t anim, float f);
  void SetBabySpawned(uint32_t index, uint8_t v);
  void SetBabySocialCallState(uint32_t id, uint32_t anim, float f);
  float SetBabyCelebrationAnim();
  int GetMouthPartIdx();
  bool FUN_00629590();
  void ForceBabiesToIdle(int param);
  void FUN_006298b0(uint32_t exceptId);
  void FUN_00629960(int dt);
  bool BabiesReachedTargetAngle();
  void SetAllBabyRotateSpeeds(float speed);
  float FUN_00629bd0(CreatureStruct* s);
};

// @ 0x00628d50
bool cSPPlayMode::HandleButton(int id) {
  bool result = false;
  if (mButtons.FUN_0062f7f0(id)) {
  EA::Audio::ISystem* sys = EA::Audio::GetSystemAT();
  void* r0 = sys ? sys->Notify() : 0;
  KillSetiEffects(0xa03e74b2, r0);
  Flagged* f = mEditor->flagged;
  if (f) {
    if (mButtons.FUN_0062f6c0()) f->flags |= 1; else f->flags &= ~1u;
  }
  bool b = mButtons.FUN_0062f6c0();
  SendButtonEventToBabies(b);
  if (id == 0x445b018 || id == 0x445b318 || id == 0x445b340 || id == 0x445b388) {
    uint32_t anim = GetRandomEnvironmentReactionAnim();
    mAnimator.Play(mEditor->momId, anim, 0, 1, 0);
    mAnimator.Play(mEditor->momId, 0x4330667, 1, 0, 0);
    mEditor->FUN_00574110(0x70842ef6, -1, 1.0f, 0.0f);
    switch (id) {
      case 0x445b018: mEditor->FUN_005dbbb0(0); return true;
      case 0x445b318: mEditor->FUN_005dbbb0(1); return true;
      case 0x445b340: mEditor->FUN_005dbbb0(2); return true;
      case 0x445b388: mEditor->FUN_005dbbb0(3); break;
    }
  }
  return true;
  }
  for (int i = 0; i < 4; i++) result |= mSubModes[i]->HandleButton(id);
  return result;
}

V3 Fn_0059aed0(const V3& a, const void* c);
bool Fn_0059ab70(V3* v);
float Fn_0069b760(const V3& a, const V3& b, const float* c);

// @ 0x00628f10
void cSPPlayMode::SetMomToFaceBaby(uint32_t baby) {
  CreatureMgr* mgr = mEditor->mgr;
  mgr->GetCreature(baby);
  uint32_t mom = mEditor->momId;
  char* c = (char*)mgr->GetCreature(mom);
  V3 momPos, babyPos;
  mgr->GetCreaturePosition(mom, &momPos);
  mgr->GetCreaturePosition(baby, &babyPos);
  V3 up = -gUpAxis;
  V3 a = up;
  a = Fn_0059aed0(a, c + 0x10);
  if (!Fn_0059ab70(&a)) a = up;
  Fn_0069b760(babyPos - momPos, a, &gAngleRef);
  float ang = Fn_0069b760(babyPos - momPos, -gUpAxis, &gAngleRef);
  mgr->GetCreatureStructure(mom);
  mMomCrouchChangeTime = -ang;
}

// @ 0x00629110
uint32_t cSPPlayMode::GetLatestBabyID() {
  Editor* e = mEditor;
  BabyVec& v = e->babies;
  int n = v.size();
  if (n == 0) return 0xffffffff;
  Baby* b = v.mpBegin;
  return b[n - 1].id;
}

// @ 0x00629150
int cSPPlayMode::GetLatestBabyIndex() {
  Editor* e = mEditor;
  return e->babies.ssize() - 1;
}

// @ 0x00629180
uint32_t cSPPlayMode::GetAnimatedBabyIndex(uint32_t id) {
  Editor* e = mEditor;
  BabyVec& v = e->babies;
  uint32_t n = v.size();
  Baby* b = v.mpBegin;
  for (uint32_t i = 0; i < n; i++, b++) {
    if (b->id == id) return i;
  }
  return 0xffffffff;
}

// @ 0x006291d0
uint32_t cSPPlayMode::FUN_006291d0(uint32_t index) {
  Editor* e = mEditor;
  BabyVec& v = e->babies;
  uint32_t n = v.size();
  Baby* b = v.mpBegin;
  if (n == 0) return 0xffffffff;
  if (index < n) return b[index].id;
  return b[0].id;
}

// @ 0x00629220
void cSPPlayMode::SetAllBabySitUp() {
  Editor* e = mEditor;
  BabyVec& v = e->babies;
  uint32_t n = v.size();
  for (uint32_t i = 0; i < n; i++) {
    Baby* b = &v[i];
    if (b->state >= 3 && b->state == 4) mAnimator.Play(b->id, 0x4079859, 0, 1, 0);
    v[i].state = 0;
    v[i].timer = 0.0f;
  }
}

// @ 0x006292b0
void cSPPlayMode::SetAllOtherBabiesToIdle(uint32_t id, uint32_t anim, float f) {
  Editor* e = mEditor;
  BabyVec* pv = &e->babies;
  BabyVec& v = *pv;
  uint32_t idx = GetAnimatedBabyIndex(id);
  if (idx < v.size() && v[idx].state == 1) {
    v[idx].state = 2;
    Creature* c = mEditor->mgr->GetCreature(id);
    uint32_t h = c->A(anim, 0);
    c->B(h, 1);
    c->C(h);
    c->D(h, f);
    v[idx].timer = c->E(anim) * f * 0.5f;
  }
}

// @ 0x00629380
void cSPPlayMode::SetBabySpawned(uint32_t index, uint8_t value) {
  BabyVec& v = mEditor->babies;
  if (index < v.size()) v[index].spawned = value;
}

// @ 0x006293d0
void cSPPlayMode::SetBabySocialCallState(uint32_t id, uint32_t anim, float f) {
  Editor* e = mEditor;
  BabyVec& v = e->babies;
  uint32_t idx = GetAnimatedBabyIndex(id);
  if (idx < v.size() && v[idx].callState == 1) {
    Creature* c = e->mgr->GetCreature(id);
    uint32_t h = c->A(anim, 0);
    c->B(h, 1);
    c->C(h);
    c->D(h, f);
    v[idx].timer = c->E(anim) * f * 0.5f;
    if (GetMouthPartIdx() != -1) {
      v[idx].timer2 = f * 0.5f;
      v[idx].callState = 2;
    } else {
      v[idx].callState = 3;
    }
  }
}

// @ 0x006294e0
float cSPPlayMode::SetBabyCelebrationAnim() {
  Editor* e = mEditor;
  Baby* b = e->babies.mpBegin;
  int latest;
  int n0 = (int)(e->babies.mpEnd - b);
  if (n0 == 0) latest = -1; else latest = b[n0 - 1].id;
  float result = 0.0f;
  if (latest != -1) {
    int n = (int)(e->babies.mpEnd - b);
    float t = mAnimator.Play(latest, 0x43736c5, 0, 1, 0);
    mBabyCelebratingChangeTime[n - 1] = t;
    mAnimator.Play(latest, 0x4330667, 1, 0, 0);
  }
  return result;
}

extern const float gTwo;       // 0x1470f1c
extern const float gMs;        // 0x13f9428 (0.001f)
extern const float gOne;       // 0x15f6de4
extern const float gAngleScale;// 0x15f6ee4
extern const float gA, gB, gC; // 0x1522250, 0x13fe0e4, 0x15224b0
float Fn_009b3c10(float a, float b);

// @ 0x00629590
bool cSPPlayMode::FUN_00629590() {
  bool result = false;
  if (mNumBabies != 0) {
    RandomLinearCongruential rng;
    rng.SetSeed(0xffffffff);
    if (rng.RandomUint32Uniform(100) > 0x46) {
      uint32_t baby;
      if (mNumBabies == 1) {
        baby = FUN_006291d0(0);
      } else {
        do {
          uint32_t r = rng.RandomUint32Uniform(mNumBabies);
          BabyVec& v = mEditor->babies;
          uint32_t n = v.size();
          Baby* b = v.mpBegin;
          if (n == 0) baby = 0xffffffff;
          else if (r < n) baby = b[r].id;
          else baby = b[0].id;
        } while (baby == mCrouchBaby);
      }
      V3 momPos, babyPos;
      CreatureMgr* mgr = mEditor->mgr;
      mgr->GetCreaturePosition(mEditor->momId, &momPos);
      mgr->GetCreaturePosition(baby, &babyPos);
      float dz = momPos.z - babyPos.z;
      float dy = momPos.y - babyPos.y;
      float dx = momPos.x - babyPos.x;
      if (gTwo <= dz * dz + dy * dy + dx * dx) {
        SetMomToFaceBaby(baby);
        mCrouchBaby = baby;
        mFlag20 = 1;
        result = true;
      }
    }
  }
  return result;
}

// @ 0x006296e0
void cSPPlayMode::ForceBabiesToIdle(int param) {
  uint32_t i = 0;
  bool flag = false;
  if (mNumBabies > 0) {
    int off = 0;
    float* p = (float*)&mBabyCelebratingChangeTime[0];
    do {
      Editor* e = mEditor;
      BabyVec& v = e->babies;
      uint32_t n = v.size();
      Baby* b = v.mpBegin;
      uint32_t id;
      if (n == 0) id = 0xffffffff;
      else if (i < n) id = *(uint32_t*)(off + (char*)b);
      else id = b[0].id;
      bool doIdle;
      if (param == -1) {
        flag = true;
        doIdle = true;
      } else {
        CreatureMgr* mgr = e->mgr;
        CreatureStruct* cs = mgr->GetCreatureStructure(id);
        uint32_t a, bb, c;
        if (mgr->IsPlayingAnimation(id) && (cs->anim->F(&a, &bb, &c, 0), (int)a == param)) {
          flag = true;
          doIdle = true;
        } else {
          doIdle = flag;
        }
      }
      if (doIdle) {
        mAnimator.Play(id, 0x4330667, 1, 1, 0);
        { BabyVec& w = mEditor->babies; if (i < w.size()) ((Baby*)(off + (char*)w.mpBegin))->spawned = 0; }
        *p = 0.0f;
        { BabyVec& w = mEditor->babies; if (i < w.size()) ((Baby*)(off + (char*)w.mpBegin))->b18 = 0; }
        { BabyVec& w = mEditor->babies; if (i < w.size()) ((Baby*)(off + (char*)w.mpBegin))->b1a = 0; }
      }
      p++;
      off += 0x30;
      i++;
    } while (i < mNumBabies);
  }
}

// @ 0x006298b0
void cSPPlayMode::FUN_006298b0(uint32_t exceptId) {
  BabyVec& v = mEditor->babies;
  uint32_t n = v.size();
  for (uint32_t i = 0; i < n; i++) {
    uint32_t id = v[i].id;
    if (id != exceptId) {
      Creature* c = mEditor->mgr->GetCreature(id);
      ((ActionSub*)((char*)this + 0xd8))->SetIdleAnimation(c, id, 0, 0);
      mAnimator.Play(id, 0x4330667, 1, 0, 0);
    }
  }
}

// @ 0x00629960
void cSPPlayMode::FUN_00629960(int dt) {
  BabyVec& v = mEditor->babies;
  uint32_t n = v.size();
  for (uint32_t i = 0; i < n; i++) {
    Baby* b = &v[i];
    if (b->b1a != 0) {
      if (v[i].t20 > 0.0f) v[i].t20 = v[i].t20 - (float)(uint32_t)dt * gMs;
      if (v[i].t20 < 0.0f) {
        Creature* c = mEditor->mgr->GetCreature(v[i].id);
        uint32_t anim;
        c->F(&anim, 0, 0, 0);
        if (!c->IsOrientIdleAnim(anim) &&
            !((DanceSub*)((char*)this + 0x11b0))->IsDancingAnim(anim, 1) &&
            !mEditor->mgr->IsPlayingAnimation(v[i].id)) {
          v[i].b1a = 0;
          v[i].b18 = 0;
          v[i].spawned = 0;
        }
      }
    }
  }
}

// @ 0x00629a90
bool cSPPlayMode::BabiesReachedTargetAngle() {
  CreatureMgr* mgr = mEditor->mgr;
  uint8_t i = 0;
  while (i < mNumBabies) {
    uint32_t idx = i;
    uint32_t id = mEditor->babies.IDAt(idx);
    if (mgr->GetCreatureStructure(id)->angle != mMomCrouchChangeTime) return false;
    i++;
  }
  return true;
}

// @ 0x00629b30
void cSPPlayMode::SetAllBabyRotateSpeeds(float speed) {
  CreatureMgr* mgr = mEditor->mgr;
  for (int i = 0; i < (int)mNumBabies; i++) {
    uint32_t id = mEditor->babies.IDAt(i);
    CreatureStruct* cs = mgr->GetCreatureStructure(id);
    cs->f4c = 2.5f;
    cs->f50 = speed;
  }
}

template <class T> inline const T& MinRef(const T& a, const T& b) { return (b < a) ? b : a; }

// @ 0x00629bd0
float cSPPlayMode::FUN_00629bd0(CreatureStruct* s) {
  if (s) {
    float sa = s->angle;
    float d = Fn_009b3c10(mMomCrouchChangeTime - sa, gAngleScale);
    float k = gA * gB;
    float m = fabsf(d) * gC;
    return MinRef(m, k);
  }
  return gOne;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct CreatureMgr {
    void GetCreatureStructure(unsigned int); // 0x0059cac0
};
struct RandomLinearCongruential {
    void RandomUint32Uniform(unsigned int); // 0x00a68fb0
    void SetSeed(unsigned int); // 0x00936090
};
}

namespace __equiv_ann1 {   // address annotations for the equivalence checker; never referenced
struct DanceSub {
    void IsDancingAnim();   // 0x0063b570 (equiv t2)
};
}
