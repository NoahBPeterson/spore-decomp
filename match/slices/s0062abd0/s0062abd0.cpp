// SP::cSPPlayMode / cSPPlayModeAnimation methods. Region 0x62abd0-0x62bb33.
// Retail layout differs a lot from the 2008 dev PDB; offsets below are taken
// from the retail disassembly.  Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

typedef void  (__thiscall *TF0)(void*);
typedef void  (__thiscall *TF1)(void*, int);
typedef void  (__thiscall *TF2)(void*, int, int);
typedef void* (__thiscall *TFR1)(void*, int);
typedef void  (__thiscall *TF3)(void*, int, int, int);
typedef void  (__thiscall *TF4)(void*, int, int, int, int);
typedef float (__thiscall *TFF0)(void*);
typedef float (__thiscall *TFF5)(void*, unsigned, int, int, int, int);

static inline void** VT(void* p) { return *(void***)p; }

// ------------------------------------------------------------------ stubs
struct AnimRef {                 // AutoRefCount-ish: slot1 = Release
  virtual void s0();
  virtual void s1();
  virtual void s2();
};

struct Vector12 {                // eastl vector (3 pointers)
  void* a; void* b; void* c;
  Vector12() : a(0), b(0), c(0) {}
  ~Vector12();
};

// cSPPlayModeAnimation (retail): vptr; editor base; curr anim id; vector at 0xc;
// 5 dwords; pTooltip[24] at 0x2c.
struct cSPPlayModeAnimation {
  virtual void slot0();
  void* mEditorBase;             // 0x4
  unsigned int mCurrAnimID;      // 0x8
  Vector12 mAnimPanelInfo;       // 0xc
  int mF18;                      // 0x18
  int mF1C;                      // 0x1c
  int mF20;                      // 0x20
  int mF24;                      // 0x24
  int mF28;                      // 0x28
  AnimRef* pTooltip[24];         // 0x2c

  cSPPlayModeAnimation();
  ~cSPPlayModeAnimation();
};

// ------------------------------------------------------------------ externs
extern "C" void* CALLEE_572400(...);
extern "C" void CALLEE_69b760(...);
extern "C" void CALLEE_59ca70(...);
extern "C" void CALLEE_59d110(...);
extern "C" void CALLEE_453b20(...);
extern "C" void CALLEE_41cb40(...);
extern "C" void CALLEE_629c50(...);
extern "C" void CALLEE_63b210(...);
extern "C" void CALLEE_63f1c0(...);
extern "C" void CALLEE_63b5a0(...);
extern "C" void CALLEE_63c200(...);
extern "C" void CALLEE_62f8c0(...);
extern "C" void CALLEE_93a560(...);
extern "C" void CALLEE_1083110(...);
extern "C" void CALLEE_109ae60(...);
extern "C" void CALLEE_f47380(...);
extern "C" void CALLEE_5c7f10(...);
extern "C" void CALLEE_5f3680(...);
extern "C" void CALLEE_62ffd0(...);
extern "C" void CALLEE_629110(...);
extern "C" void CALLEE_629180(...);
extern "C" void CALLEE_582d70(...);
extern "C" void CALLEE_635760(...);
extern "C" void CALLEE_634ef0(...);
extern "C" void CALLEE_635600(...);
extern "C" void CALLEE_635680(...);
extern "C" void CALLEE_635350(...);
extern "C" void CALLEE_401050(...);
extern "C" void CALLEE_45b210(...);
extern "C" void CALLEE_45b150(...);
extern "C" void CALLEE_62f5c0(...);
extern "C" void CALLEE_809db0(...);
extern "C" void CALLEE_6a25a0(...);
extern "C" void CALLEE_93c5a0(...);
extern "C" void CALLEE_930f60(...);
extern "C" void CALLEE_6b5060(...);
extern "C" void CALLEE_6b54b0(...);
extern "C" void CALLEE_6b55c0(...);
extern "C" void CALLEE_6b5240(...);
extern "C" void CALLEE_41e050(...);
extern "C" void CALLEE_930bf0(...);
extern "C" void CALLEE_5f3680b(...);

extern float gHalf;              // 0x1471064

// ---------------------------------------------------------------------------
// Retail cSPPlayMode layout (role+offset names, read off the disassembly).
// ---------------------------------------------------------------------------
struct WStr16 {                     // 0x10-byte wide-string slot
  void*    mBegin;                  // 0x00
  void*    mEnd;                    // 0x04
  void*    mCapacity;               // 0x08
  unsigned mPad0c;                  // 0x0c
};

struct SPPlayMode_7cNode {          // node reached via cSPPlayMode::mVec7cBegin
  unsigned pad00[4];                // 0x00..0x0f
  void*    m10;                     // 0x10
  unsigned pad14[3];                // 0x14..0x1f
  float    m20;                     // 0x20
};

struct SPPlayMode_7cPos {           // node reached via SPPlayMode_7cNode::m10
  unsigned pad00[0xe];              // 0x00..0x37
  float    m38;                     // 0x38
  float    m3c;                     // 0x3c
  float    m40;                     // 0x40
};

struct SPPlayMode_Creature {        // object returned by GetCreature
  unsigned pad00[0xf];              // 0x00..0x3b
  float    m3c;                     // 0x3c
};

struct SPPlayMode_MgrSlot {         // object at cSPPlayMode::m3614
  unsigned pad00[0xd8];             // 0x000..0x35f
  void*    mCreatureManager;        // 0x360
  unsigned mCreatureID;             // 0x364
  unsigned pad368;                  // 0x368
  void*    mAnimCreatures;          // 0x36c  0x30-byte element vector begin
  void*    mAnimCreaturesEnd;       // 0x370  vector end
};

struct Matrix33 {                   // 0x24: three packed 3-vectors
  float x[3];                       // 0x00
  float y[3];                       // 0x0c
  float z[3];                       // 0x18
};

struct SPPlayMode_Global {          // global object at 0x015f7cf4
  unsigned pad00[0xe];              // 0x00..0x37
  void*    m38;                     // 0x38
  void*    m3c;                     // 0x3c
  void*    m40;                     // 0x40
  unsigned pad44[5];                // 0x44..0x57
  void*    m58;                     // 0x58
};

struct SPPlayMode_RefObj {          // ref-counted object at cSPPlayMode::m3660
  void*    mVtbl;                   // 0x00
  unsigned mFlags;                  // 0x04
  unsigned pad08[0xe];              // 0x08..0x3f
  int      mRefCount;               // 0x40
};

struct cSPPlayMode {
  void*      mVtblIHandler;         // 0x0000
  void*      mUI;                   // 0x0004  cSPPlayModeUI* (HandleMessage)
  void*      mVtblRefCount;         // 0x0008
  void*      mUI2;                  // 0x000c  UI object (IsEventForBaby); released by dtor
  void*      m10;                   // 0x0010  released by dtor
  unsigned   pad14[0xa];            // 0x0014..0x003b
  float      m3c;                   // 0x003c
  float      m40[3];                // 0x0040..0x004b
  unsigned char mShowAnimInfo;      // 0x004c
  unsigned char mShowMomAnimInfo;   // 0x004d
  unsigned short m4e;               // 0x004e
  unsigned char m50;                // 0x0050
  unsigned char m51;                // 0x0051
  unsigned short pad52;             // 0x0052
  float      mPrevCamX;             // 0x0054
  float      mPrevCamY;             // 0x0058
  float      mPrevCamZ;             // 0x005c
  unsigned   pad60;                 // 0x0060
  void*      m64;                   // 0x0064
  void*      m68;                   // 0x0068
  void*      m6c;                   // 0x006c
  unsigned   pad70[2];              // 0x0070..0x0077
  void*      m78;                   // 0x0078
  void*      mVec7cBegin;           // 0x007c
  void*      mVec7cEnd;             // 0x0080
  void*      mVec7cCap;             // 0x0084
  unsigned   pad88[2];              // 0x0088..0x008f
  void*      mModelWorld;           // 0x0090
  void*      mTexturePreload;       // 0x0094
  unsigned   pad98;                 // 0x0098
  void*      m9c;                   // 0x009c
  void*      mPreloadList;          // 0x00a0
  void*      mAnim;                 // 0x00a4
  void*      mPlayMode;             // 0x00a8
  void*      mPath;                 // 0x00ac
  void*      mB0;                   // 0x00b0
  unsigned   padB4[9];              // 0x00b4..0x00d7
  unsigned   mActionD8[0x110 / 4];  // 0x00d8  sub-mode Action
  unsigned   mPhoto1e8[0xfc8 / 4];  // 0x01e8  sub-mode Photo
  unsigned   mDance11b0[0x78 / 4];  // 0x11b0  sub-mode Dance
  unsigned   mMovie1228[0x2360 / 4];// 0x1228  sub-mode Movie
  unsigned   mAnim3588[0x88 / 4];   // 0x3588  cSPPlayModeAnimation (retail size 0x88, not the dev PDB's 0x90)
  unsigned   m3610;                 // 0x3610
  void*      m3614;                 // 0x3614  SPPlayMode_MgrSlot*
  unsigned   mLib3618[0x48 / 4];    // 0x3618  SharedLibList
  void*      m3660;                 // 0x3660
  unsigned   pad3664;               // 0x3664
  float      m3668;                 // 0x3668
  void*      m366c;                 // 0x366c
  void*      m3670;                 // 0x3670
  void*      m3674;                 // 0x3674
  unsigned   pad3678[2];            // 0x3678..0x367f
  void*      m3680;                 // 0x3680
  void*      m3684;                 // 0x3684
  void*      m3688;                 // 0x3688
  unsigned   pad368c[2];            // 0x368c..0x3693
  void*      m3694;                 // 0x3694
  void*      m3698;                 // 0x3698
  void*      m369c;                 // 0x369c
  unsigned   pad36a0[2];            // 0x36a0..0x36a7
  void*      m36a8;                 // 0x36a8
  void*      m36ac;                 // 0x36ac
  void*      m36b0;                 // 0x36b0
  unsigned   pad36b4[4];            // 0x36b4..0x36c3
  void*      m36c4;                 // 0x36c4
  unsigned   pad36c8[2];            // 0x36c8..0x36cf
  unsigned char m36d0;              // 0x36d0
  unsigned char pad36d1[7];         // 0x36d1..0x36d7
  unsigned   m36d8[6];              // 0x36d8..0x36ef
  unsigned   mStopwatch36f0[4];     // 0x36f0  EA::Stopwatch
  unsigned char m3700;              // 0x3700
  unsigned char m3701;              // 0x3701
  unsigned char pad3702[2];         // 0x3702..0x3703
  unsigned   mWide3704;             // 0x3704
  unsigned char m3708;              // 0x3708
  unsigned char m3709;              // 0x3709
  unsigned char m370a;              // 0x370a
  unsigned char pad370b;            // 0x370b
  WStr16     mStringsA[0x104];      // 0x370c..0x474b
  WStr16     mStringsB[0x104];      // 0x474c..0x578b

  void     ad70(float* param_2, unsigned param_3, unsigned param_4,
                float p5, float p6, float p7, float p8);
  unsigned HandleMessage(unsigned param_2, int param_3);
  void     IsEventForBaby(int param_2);
  void     FUN_0062b980(int id);    // 0x0062b980  thiscall, ret 4
};

// ------------------------------------------------------------------ data
extern const float    g_015f6ee4;   // 0x015f6ee4  label scale
extern const float    g_015f6ee8;   // 0x015f6ee8
extern const float    g_015f6eec;   // 0x015f6eec
extern const float    g_015f6ef0;   // 0x015f6ef0
extern const float    g_13eb8b0;    // 0x013eb8b0  sign-bit vector
extern const float    g_1485720;    // 0x01485720  1.0f
extern const float    g_13fe0c0;    // 0x013fe0c0  5.0f
extern const float    g_13fe0c4;    // 0x013fe0c4  3.75f
extern const float    g_13f4fd0;    // 0x013f4fd0  2^32
extern void*       g_01667bac;   // 0x01667bac  gEmptyString16 (begin/end)
extern void*       g_01667bae;   // 0x01667bae  gEmptyString16 + 2 (capacity)
extern SPPlayMode_Global* const g_015f7cf4;   // 0x015f7cf4
extern const void*    g_013fe104;   // 0x013fe104  IHandler vftable
extern const void*    g_013fe0fc;   // 0x013fe0fc  RefCountVTemplate vftable
extern const void*    g_013ec458;   // 0x013ec458  IHandler vftable (base)
extern const void*    g_013eb394;   // 0x013eb394  RefCount vftable (base)
extern const unsigned g_013f5c04;   // 0x013f5c04  format 16 string
extern const void*    g_015f6e6c_;  // 0x015f6e6c  (Vector3/axis table)

// direct callees (hex-named so difftest resolves the relocation)
extern "C" void* FUN_00572400(void* out);
extern "C" float FUN_0069b760(void* a, void* b, void* c);
extern "C" unsigned FUN_00453b20(void* a, void* b, float c);
extern "C" void* FUN_0041e050(void* out, const void* fmt, ...);
extern "C" void* FUN_0041e0a0(void* out, ...);
extern "C" void  FUN_00f47380(void* p);
extern "C" unsigned FUN_00930bf0(const void* a, const void* b);

struct TC_626db0 { void FUN_00626db0(); };
struct TC_59ca70 { void* FUN_0059ca70(unsigned id); };
struct TC_59d110 { char FUN_0059d110(unsigned id, float* out); };
struct TC_629c50 { void FUN_00629c50(); };
struct TC_41cb40 { void FUN_0041cb40(unsigned m); };
struct TC_63b210 { void FUN_0063b210(); };
struct TC_63f1c0 { void FUN_0063f1c0(); };
struct TC_63b5a0 { void FUN_0063b5a0(); };
struct TC_63c200 { void FUN_0063c200(); };
struct TC_62b0f0 { void FUN_0062b0f0(); };
struct TC_62f8c0 { void FUN_0062f8c0(); };
struct TC_62f8e0 { void FUN_0062f8e0(); };
struct TC_62b160 { void FUN_0062b160(); };
struct TC_629110 { unsigned FUN_00629110(); };
struct TC_629180 { unsigned FUN_00629180(unsigned id); };
struct TC_582d70 { void FUN_00582d70(int a, int b, unsigned id); };
struct TC_635760 { void FUN_00635760(unsigned a, int b); };
struct TC_63c3f0 { void FUN_0063c3f0(); };
struct TC_63b280 { void FUN_0063b280(); };
struct TC_63f2b0 { void FUN_0063f2b0(); };
struct TC_639b70 { void FUN_00639b70(); };
struct TC_5c7f10 { void FUN_005c7f10(); };
struct TC_5f3680 { void FUN_005f3680(void* a, void* b); };
struct TC_62ffd0 { void FUN_0062ffd0(void* a, void* b, void* c); };
struct TC_93a560 { void* FUN_0093a560(int a, int b); };
struct TC_4490UI { void FUN_00635350(unsigned a, unsigned b); void FUN_00634ef0(unsigned a, int b); };
struct TC_54c0UI { void FUN_00635600(int a); void FUN_00635680(int a); };
struct TC_6b55c0 { const void* FUN_006b55c0(); };
struct TC_c2e4e0 { void FUN_00c2e4e0(); };
struct TC_6411b0 { void FUN_006411b0(); };
struct TC_63ef70 { void FUN_0063ef70(); };
struct TC_6a25a0 { char FUN_006a25a0(unsigned id); };
struct TC_93c5a0 { void* FUN_0093c5a0(void* a, int b); };
struct TC_930f60 { void* FUN_00930f60(const void* a); };
struct TC_6b5060 { void FUN_006b5060(); };
struct TC_6b54b0 { char FUN_006b54b0(unsigned a, unsigned b, int c); };
struct TC_6b5240 { void FUN_006b5240(); };
struct TC_45b210 { int FUN_0045b210(); };
struct TC_45b150 { void FUN_0045b150(); };
struct TC_62f5c0 { void FUN_0062f5c0(); };

extern const unsigned char g_013ec468;   // 0x013ec468
extern const unsigned g_013fe144;        // 0x013fe144
extern const unsigned g_013fe134;        // 0x013fe134  L" %s%s%s"
extern const unsigned g_013fe12c;        // 0x013fe12c  L" %s%s"
extern void* const    g_015fd918;        // 0x015fd918  cDirectPropertyList*
extern "C" void  FUN_00809db0(int a, void* b);
extern "C" void* FUN_00401050(void* a);

struct MsgRes { unsigned a; unsigned b; unsigned c; };
static void FreeWStr16(const void* begin, const void* cap) {
  unsigned d = ((unsigned)cap - (unsigned)begin) & 0xfffffffeu;
  if ((int)d > 2 && begin != 0) FUN_00f47380((void*)begin);
}

// @ 0x0062abd0
// SP::cSPPlayMode::MakeCreaturesFaceCamera.
void __fastcall cSPPlayMode_MakeCreaturesFaceCamera(void* self) {
  cSPPlayMode* s = (cSPPlayMode*)self;
  float cam[3];
  float pos[3];
  s->m4e = 0x0101;
  s->m50 = 1;
  void* camMgr = FUN_00572400(cam);
  ((TC_626db0*)camMgr)->FUN_00626db0();
  SPPlayMode_MgrSlot* w = (SPPlayMode_MgrSlot*)s->m3614;
  void* animMgr = w->mCreatureManager;
  unsigned id = w->mCreatureID;
  ((TC_59ca70*)animMgr)->FUN_0059ca70(id);
  ((TC_59d110*)animMgr)->FUN_0059d110(id, pos);
  s->mPrevCamX = cam[0];
  s->mPrevCamY = cam[1];
  s->mPrevCamZ = cam[2];
  float v0[4];
  float v1[4];
  v1[0] = -g_015f6ee8;
  v1[1] = -g_015f6eec;
  v1[2] = 0.0f;
  v1[3] = 0.0f;
  v0[0] = -g_015f6ef0;
  v0[1] = cam[0] - pos[0];
  v0[2] = cam[1] - pos[1];
  v0[3] = 0.0f;
  float r = FUN_0069b760(v0, v1, (void*)&g_015f6e6c_);
  s->m3c = -r;
  s->m51 = 1;
  ((TC_629c50*)s)->FUN_00629c50();
}

// @ 0x0062ace0
// float f(void* p, char b): half the larger horizontal extent of a box,
// optionally scaled by p->scale.
float __stdcall FUN_0062ace0(void* p, char b) {
  char* q = *(char**)((char*)p + 0x180);
  float* v = (float*)(q + 0x70);
  float dx = v[3] - v[0];
  float dy = v[4] - v[1];
  float d  = dx;
  if (dy > dx) d = dy;
  if (b) d = *(float*)((char*)p + 0x3c) * d;
  return d * gHalf;
}

// @ 0x0062ad70
// Clamp/reposition a point toward the creature's reference position.
void cSPPlayMode::ad70(float* param_2, unsigned param_3, unsigned param_4,
                       float p5, float p6, float p7, float p8) {
  float local_60 = param_2[0];
  float local_5c = param_2[1];
  float local_58 = param_2[2];
  SPPlayMode_7cNode* n = *(SPPlayMode_7cNode**)mVec7cBegin;
  float len = sqrtf(local_58 * local_58 + local_5c * local_5c + local_60 * local_60);
  if (5.0f < len) {
    float inv = g_1485720 / len;
    // Retail order: (inv * x) * 5.0f, three 32-bit multiplies. /fp:fast would reassociate to
    // (5.0f * inv) * x, which rounds differently for denormals; the volatile stores pin the order.
    volatile float s0 = inv * local_60;
    volatile float s1 = inv * local_5c;
    volatile float s2 = local_58 * inv;
    local_60 = s0 * g_13fe0c0;
    local_5c = s1 * g_13fe0c0;
    local_58 = s2 * g_13fe0c0;
  }
  SPPlayMode_MgrSlot* w = (SPPlayMode_MgrSlot*)m3614;
  SPPlayMode_Creature* c =
      (SPPlayMode_Creature*)((TC_59ca70*)w->mCreatureManager)->FUN_0059ca70(param_3);
  float lim = c->m3c * n->m20 + n->m20;
  if (3.75f < lim) lim = 3.75f;
  SPPlayMode_7cPos* q = (SPPlayMode_7cPos*)n->m10;
  float f8 = q->m38;
  float f2 = q->m3c;
  float f3 = q->m40;
  float d0 = f8 - local_60;
  float d1 = f2 - local_5c;
  float d2 = f3 - local_58;
  float dist = sqrtf(d2 * d2 + d1 * d1 + d0 * d0);
  if (dist < lim) {
    unsigned char tmp24[0x24];
    float ang = ((float)param_4 / (float)(m36d0 + 1)) * g_015f6ee4;
    unsigned mtxArg = FUN_00453b20(tmp24, (void*)&g_015f6e6c_, ang);
    Matrix33 mtx;
    ((TC_41cb40*)&mtx)->FUN_0041cb40(mtxArg);
    float a0 = -g_015f6ee8 * p5;
    float a1 = -g_015f6eec * p5;
    float a2 = -g_015f6ef0 * p5;
    local_60 = (((mtx.z[0] * a2 + mtx.y[0] * a1) + mtx.x[0] * a0) + f8) + p6;
    local_5c = p7 + (((mtx.z[1] * a2 + mtx.y[1] * a1) + mtx.x[1] * a0) + f2);
    local_58 = p8 + (((mtx.z[2] * a2 + mtx.y[2] * a1) + mtx.x[2] * a0) + f3);
  }
  param_2[0] = local_60;
  param_2[1] = local_5c;
  param_2[2] = local_58;
}

// @ 0x0062b000
// Clear the play-mode creature list and the havok rigid-body list.
struct HkWorldObject { void removeReference(); };
struct Bp { void FUN_01083110(int a); };
void __fastcall FUN_0062b000(void* self) {
  char* s = (char*)self;
  unsigned n = (*(unsigned*)(s + 0x3670) - *(unsigned*)(s + 0x366c)) >> 2;
  if (n != 0) {
    for (unsigned i = 0; i < n; ++i) {
      char* o = *(char**)(*(unsigned*)(s + 0x366c) + i * 4);
      char* m0 = *(char**)o;
      char* vtb = *(char**)m0;
      TF1 fn = (TF1)(*(void**)(vtb + 0x16c));
      fn(m0, 0);
    }
    for (unsigned k = n; k != 0; --k) {
      *(unsigned*)(s + 0x3670) -= 4;
      char* o = **(char***)(s + 0x3670);
      if (o != 0) {
        if (*(int*)(o + 0x40) < 2) {
          char* m0 = *(char**)o;
          char* vtb = *(char**)m0;
          TF2 fn = (TF2)(*(void**)(vtb + 0x170));
          fn(m0, (int)o, (*(unsigned*)(o + 4)) >> 31 & 1);
        } else {
          (*(int*)(o + 0x40)) -= 1;
        }
      }
    }
  }
  unsigned m = (*(unsigned*)(s + 0x3698) - *(unsigned*)(s + 0x3694)) >> 2;
  for (unsigned i = 0; i < m; ++i) {
    char* o = *(char**)(*(unsigned*)(s + 0x3694) + i * 4);
    int x = *(int*)(o + 8);
    char b = 0;
    ((Bp*)(char*)x)->FUN_01083110((int)&b);
    ((HkWorldObject*)o)->removeReference();
  }
  for (unsigned k = m; k != 0; --k) {
    *(unsigned*)(s + 0x3698) -= 4;
  }
}

// @ 0x0062b0f0
cSPPlayModeAnimation::cSPPlayModeAnimation() {
  mF20 = 0;
  for (int i = 0; i < 24; ++i) pTooltip[i] = 0;
}

// @ 0x0062b160
cSPPlayModeAnimation::~cSPPlayModeAnimation() {
  AnimRef** p = pTooltip + 24;
  int n = 23;
  do {
    AnimRef* t = *--p;
    if (t != 0) t->s1();
  } while (--n >= 0);
}

// @ 0x0062b1c0
// SP::cSPPlayMode::cSPPlayMode
void __fastcall cSPPlayMode_ctor(void* self) {
  cSPPlayMode* s = (cSPPlayMode*)self;
  s->mUI = 0;
  s->mVtblRefCount = (void*)&g_013eb394;
  s->mVtblIHandler = (void*)&g_013fe104;
  s->mVtblRefCount = (void*)&g_013fe0fc;
  s->mUI = 0;
  s->m10 = 0;
  s->mShowAnimInfo = 0;
  s->mShowMomAnimInfo = 0;
  s->m64 = 0;
  s->m68 = 0;
  s->m6c = 0;
  s->m78 = 0;
  s->mVec7cBegin = 0;
  s->mVec7cEnd = 0;
  s->mVec7cCap = 0;
  s->mModelWorld = 0;
  s->mTexturePreload = 0;
  s->m9c = 0;
  s->mPreloadList = 0;
  s->mAnim = 0;
  s->mPlayMode = 0;
  s->mPath = 0;
  s->mB0 = 0;
  ((TC_63b210*)&s->mActionD8[0])->FUN_0063b210();
  ((TC_63f1c0*)&s->mPhoto1e8[0])->FUN_0063f1c0();
  ((TC_63b5a0*)&s->mDance11b0[0])->FUN_0063b5a0();
  ((TC_63c200*)&s->mMovie1228[0])->FUN_0063c200();
  ((TC_62b0f0*)&s->mAnim3588[0])->FUN_0062b0f0();
  ((TC_62f8c0*)&s->mLib3618[0])->FUN_0062f8c0();
  s->m3660 = 0;
  s->m3668 = g_1485720;
  s->m366c = 0;
  s->m3670 = 0;
  s->m3674 = 0;
  s->m3680 = 0;
  s->m3684 = 0;
  s->m3688 = 0;
  s->m3694 = 0;
  s->m3698 = 0;
  s->m369c = 0;
  s->m36a8 = 0;
  s->m36ac = 0;
  s->m36b0 = 0;
  s->m36d0 = 0;
  ((TC_93a560*)&s->mStopwatch36f0[0])->FUN_0093a560(5, 0);
  s->m3709 = 0;
  s->m370a = 0;
  {
    void* e0 = g_01667bac;
    void* e1 = g_01667bae;
    WStr16* p = s->mStringsA;
    for (int i = 0; i < 52; ++i) {
      for (int j = 0; j < 5; ++j) {
        p->mBegin = e0;
        p->mEnd = e0;
        p->mCapacity = e1;
        ++p;
      }
    }
    WStr16* q = s->mStringsB;
    for (int i = 0; i < 52; ++i) {
      for (int j = 0; j < 5; ++j) {
        q->mBegin = e0;
        q->mEnd = e0;
        q->mCapacity = e1;
        ++q;
      }
    }
  }
  s->m4e = 0;
  s->m50 = 0;
}

// @ 0x0062b3a0
// SP::cSPPlayMode::~cSPPlayMode
void __fastcall cSPPlayMode_dtor(void* self) {
  cSPPlayMode* s = (cSPPlayMode*)self;
  s->mVtblIHandler = (void*)&g_013fe104;
  s->mVtblRefCount = (void*)&g_013fe0fc;
  {
    WStr16* p = s->mStringsB + 0x104;
    int n = 0x103;
    do {
      WStr16* slot = p - 1;
      unsigned begin = (unsigned)slot->mBegin;
      unsigned cap = (unsigned)slot->mCapacity;
      --p;
      unsigned d = (cap - begin) & 0xfffffffeu;
      if ((int)d > 2 && begin != 0) FUN_00f47380((void*)begin);
    } while (--n >= 0);
  }
  {
    WStr16* p = s->mStringsA + 0x104;
    int n = 0x103;
    do {
      WStr16* slot = p - 1;
      unsigned begin = (unsigned)slot->mBegin;
      unsigned cap = (unsigned)slot->mCapacity;
      --p;
      unsigned d = (cap - begin) & 0xfffffffeu;
      if ((int)d > 2 && begin != 0) FUN_00f47380((void*)begin);
    } while (--n >= 0);
  }
  if (s->m36a8 != 0 && *(int*)((char*)s->m36a8 - 4) != 0) FUN_00f47380(s->m36a8);
  if (s->m3694 != 0 && *(int*)((char*)s->m3694 - 4) != 0) FUN_00f47380(s->m3694);
  ((TC_5f3680*)&s->m3680)->FUN_005f3680(s->m3680, s->m3684);
  if (s->m3680 != 0 && *(int*)((char*)s->m3680 - 4) != 0) FUN_00f47380(s->m3680);
  ((TC_5f3680*)&s->m366c)->FUN_005f3680(s->m366c, s->m3670);
  if (s->m366c != 0 && *(int*)((char*)s->m366c - 4) != 0) FUN_00f47380(s->m366c);
  {
    SPPlayMode_RefObj* o = (SPPlayMode_RefObj*)s->m3660;
    if (o != 0) {
      if (o->mRefCount > 1) {
        o->mRefCount -= 1;
      } else {
        void* vt = o->mVtbl;
        ((TF1)(*(void**)((char*)vt + 0x170)))(o, (int)((o->mFlags >> 31) & 1));
      }
    }
  }
  ((TC_62f8e0*)&s->mLib3618[0])->FUN_0062f8e0();
  ((TC_62b160*)&s->mAnim3588[0])->FUN_0062b160();
  ((TC_63c3f0*)&s->mMovie1228[0])->FUN_0063c3f0();
  ((TC_63b280*)&s->mDance11b0[0])->FUN_0063b280();
  ((TC_63f2b0*)&s->mPhoto1e8[0])->FUN_0063f2b0();
  ((TC_639b70*)&s->mActionD8[0])->FUN_00639b70();
  if (s->mTexturePreload != 0) {
    void* vt = *(void**)s->mTexturePreload;
    ((TF0)(*(void**)((char*)vt + 4)))(s->mTexturePreload);
  }
  if (s->mModelWorld != 0) {
    void* vt = *(void**)s->mModelWorld;
    ((TF0)(*(void**)((char*)vt + 4)))(s->mModelWorld);
  }
  ((TC_5c7f10*)&s->mVec7cBegin)->FUN_005c7f10();
  if (s->m78 != 0) {
    void* vt = *(void**)s->m78;
    ((TF0)(*(void**)((char*)vt + 8)))(s->m78);
  }
  if (s->m64 != 0 && *(int*)((char*)s->m64 - 4) != 0) FUN_00f47380(s->m64);
  if (s->m10 != 0) {
    void* vt = *(void**)s->m10;
    ((TF0)(*(void**)((char*)vt + 4)))(s->m10);
  }
  if (s->mUI2 != 0) {
    void* vt = *(void**)s->mUI2;
    ((TF0)(*(void**)((char*)vt + 4)))(s->mUI2);
  }
  s->mVtblIHandler = (void*)&g_013ec458;
  s->mVtblRefCount = (void*)&g_013eb394;
}

// @ 0x0062b5c0
// SP::cSPPlayMode::HandleMessage
unsigned cSPPlayMode::HandleMessage(unsigned param_2, int param_3) {
  if (param_2 <= 0x5b053b5) {
    if (param_2 == 0x5b053b5) {
      WStr16 s1 = { g_01667bac, g_01667bac, g_01667bae };
      WStr16 s2 = { g_01667bac, g_01667bac, g_01667bae };
      FUN_0041e050(&s1, (const void*)&g_013f5c04,
                   *(void**)(*(int*)(param_3 + 8) + 0xc));
      FUN_0041e050(&s2, (const void*)&g_013f5c04,
                   *(void**)(*(int*)(param_3 + 0x10) + 0xc));
      g_015f7cf4->m40 = s1.mBegin;
      g_015f7cf4->m3c = s2.mBegin;
      MsgRes r;
      r.a = 0x213abb63u; r.b = 0xb1b104u; r.c = 0x490f6945u;
      FUN_00809db0(0, &r);
      ((TC_4490UI*)mUI)->FUN_00634ef0(0x5b02188u, 1);
      FreeWStr16(s2.mBegin, s2.mCapacity);
      FreeWStr16(s1.mBegin, s1.mCapacity);
      return 0;
    }
    if (param_2 == 0x3eaed50) {
      void* photo = (void*)((char*)this + 0x1e0);
      ((TC_c2e4e0*)photo)->FUN_00c2e4e0();
      ((TC_6411b0*)photo)->FUN_006411b0();
      ((TC_63ef70*)photo)->FUN_0063ef70();
      return 1;
    }
    if (param_2 == 0x58b8059) {
      WStr16 s2 = { g_01667bac, g_01667bac, g_01667bae };
      unsigned char convBuf[0x40];
      ((TC_93c5a0*)convBuf)->FUN_0093c5a0(*(void**)(*(int*)(param_3 + 8) + 0xc), -1);
      FUN_0041e050(&s2, (const void*)&g_013f5c04, *(void**)convBuf);
      if (((TC_6a25a0*)g_015fd918)->FUN_006a25a0(0x61b67b6u) == 0) {
        g_015f7cf4->m38 = s2.mBegin;
        g_015f7cf4->m58 = (void*)&g_013ec468;
      } else {
        unsigned char strA[0x14];
        unsigned char strB[0x14];
        unsigned char strC[0x14];
        ((TC_930f60*)convBuf)->FUN_00930f60(s2.mBegin);
        ((TC_6b5060*)strB)->FUN_006b5060();
        ((TC_6b5060*)strC)->FUN_006b5060();
        ((TC_6b5060*)strA)->FUN_006b5060();
        ((TC_6b54b0*)strB)->FUN_006b54b0(0x19f76d11u, 0x5ca8d97u, 0x13fe144);
        ((TC_6b54b0*)strC)->FUN_006b54b0(0x19f76d11u, 0x5ca8d9au, 0x13fe144);
        void* t4744 = (void*)&mStringsA[0x103].mCapacity;
        unsigned v = FUN_00930bf0(convBuf, 0);
        (void)v;
        FUN_0041e050(t4744, (const void*)&g_013fe134,
                     ((TC_6b55c0*)strB)->FUN_006b55c0(),
                     ((TC_6b55c0*)strC)->FUN_006b55c0(), v);
        g_015f7cf4->m38 = mStringsA[0x103].mCapacity;
        ((TC_6b54b0*)strA)->FUN_006b54b0(0x19f76d11u, 0x61b68c1u, 0x13fe144);
        void* t3704 = (void*)&mWide3704;
        FUN_0041e050(t3704, (const void*)&g_013fe12c,
                     ((TC_6b55c0*)strA)->FUN_006b55c0());
        g_015f7cf4->m58 = *(void**)t3704;
        ((TC_6b5240*)strA)->FUN_006b5240();
        ((TC_6b5240*)strC)->FUN_006b5240();
        ((TC_6b5240*)strB)->FUN_006b5240();
      }
      MsgRes r;
      r.a = 0x2bd2c601u; r.b = 0xb1b104u; r.c = 0x490f6945u;
      FUN_00809db0(0, &r);
      ((TC_4490UI*)mUI)->FUN_00634ef0(0x58b74e8u, 1);
      ((TC_54c0UI*)mUI)->FUN_00635600(1);
      ((TC_54c0UI*)mUI)->FUN_00635680(1);
      ((TC_4490UI*)mUI)->FUN_00635350(1, 1);
      m3701 = 0;
      FreeWStr16(s2.mBegin, s2.mCapacity);
      return 0;
    }
  } else if (param_2 == 0x692ea61) {
    void* mm = FUN_00401050(m36c4);
    if (((TC_45b210*)mm)->FUN_0045b210() != 0) {
      void* mm2 = FUN_00401050(m36c4);
      ((TC_45b150*)mm2)->FUN_0045b150();
    }
    ((TC_62f5c0*)&m3610)->FUN_0062f5c0();
    return 1;
  }
  return 0;
}

// @ 0x0062b980
// Erase the shared-library entry whose id (field +0x1c) equals `id`.
// Retail ABI: __thiscall (ecx = the SPPlayMode vector owner, one stack argument, ret 4); the
// slice-era free `__fastcall(self, id)` spelled the same mangled name but emitted ret 0.
void cSPPlayMode::FUN_0062b980(int id) {
  char* s = (char*)this;
  char** end = *(char***)(s + 0x80);
  char** it  = *(char***)(s + 0x7c);
  while (it != end) {
    char* o = *it;
    if (o != 0) {
      char* vt = *(char**)o;
      ((TF0)(*(void**)(vt + 4)))(o);      // this is the element itself, not its vtable pointer
    }
    if (*(int*)(o + 0x1c) == id) {
      if ((char**)(it + 1) < *(char***)(s + 0x80)) {
        CALLEE_62ffd0(it + 1, *(char***)(s + 0x80), it);
      }
      *(unsigned*)(s + 0x80) -= 4;
      char* last = **(char***)(s + 0x80);
      if (last != 0) {
        char* lv = *(char**)last;
        ((TF0)(*(void**)(lv + 8)))(last);
      }
      char* ov = *(char**)o;
      ((TF0)(*(void**)(ov + 8)))(o);
      return;
    }
    it = (char**)((char*)it + 4);
    char* ov = *(char**)o;
    ((TF0)(*(void**)(ov + 8)))(o);
  }
}

// @ 0x0062ba10
// SP::cSPPlayMode::IsEventForBaby
void cSPPlayMode::IsEventForBaby(int param_2) {
  if (m36d0 == 0) return;
  unsigned baby;
  unsigned idx;
  SPPlayMode_MgrSlot* w = (SPPlayMode_MgrSlot*)m3614;
  if (param_2 == -1) {
    baby = ((TC_629110*)this)->FUN_00629110();
    int count = (int)((char*)w->mAnimCreaturesEnd - (char*)w->mAnimCreatures) / 48;
    idx = (unsigned)(count - 1);
    ((TC_582d70*)w)->FUN_00582d70(1, 1, 0);
  } else {
    baby = m36d8[param_2];
    idx = ((TC_629180*)this)->FUN_00629180(baby);
    ((TC_582d70*)w)->FUN_00582d70(1, 0, baby);
    m36d8[param_2] = 0;
  }
  w = (SPPlayMode_MgrSlot*)m3614;
  int count = (int)((char*)w->mAnimCreaturesEnd - (char*)w->mAnimCreatures) / 48;
  if ((int)idx < count) {
    ((char*)w->mAnimCreatures)[idx * 0x30 + 0x19] = 0;
  }
  m40[idx] = 0.0f;
  FUN_0062b980((int)baby);
  m36d0 = (unsigned char)(m36d0 - 1);
  if (m36d0 != 0) return;
  ((TC_635760*)mUI2)->FUN_00635760(0x4066678u, 0);
  ((TC_635760*)mUI2)->FUN_00635760(0x40666b8u, 0);
  void** vt = *(void***)&mAnim3588;
  TFF5 fn = (TFF5)vt[3];
  float r = fn(&mAnim3588, w->mCreatureID, 0x4373694, 0, 1, 0);
  (void)r;
}
