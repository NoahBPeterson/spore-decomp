// s00abe110 -- SP::cInteraction slot containers + EA::Swarm descriptions.
// Retail layout models reconstructed from the retail image (see work/match/scratch_s00abe110_cards.txt).

#include <math.h>

typedef unsigned int u32;
typedef unsigned char u8;

#define NOINLINE __declspec(noinline)

// ---------------------------------------------------------------------------
// external data / functions (call targets and absolute stores are relocated)
// ---------------------------------------------------------------------------
extern char g_vtbl_13ef094;
extern char g_vtbl_14599e8;
extern char g_vtbl_1459a88;
extern char g_vtbl_14599a8;
extern char g_vtbl_1453948;
extern char g_vtbl_1452a38;
extern char g_vtbl_13eb90c;
extern float g_hkRealOne;    // 0x1485720
extern float g_hkRealZero;   // 0x1485378
extern float g_mapFrequency; // 0x13ec478
extern float g_noiseSeed;    // 0x1679f4c

void* __cdecl operator_new(u32 size, const char* tag, int a, int b, int c, int d);
extern "C" void FUN_00abe010();
extern "C" void FUN_00abb820(void* dst, int count, void* src);
extern "C" void FUN_00d018d0(void* first, void* last);
extern "C" void FUN_008399d0(void* pos, const void* value);
extern "C" void EA_IO_ReadInt32(void* io, u32* out, int count, void* flags);
extern "C" void EA_IO_ReadVector(void* io, void* out, int count, void* flags);
extern "C" void FUN_00b2b5b0();

struct MessageServer;
MessageServer* __cdecl EA_Messaging_GetServer();
typedef void (__thiscall* SendMsgFn)(MessageServer*, unsigned, void*, int);

// ---------------------------------------------------------------------------
// spstl slot vector / slot deque (128 entries per block, 8-byte entry)
// ---------------------------------------------------------------------------
struct SlotEntry {
  u32 mMeta;   // bit31 = free, bit30 = end sentinel, bits0..29 = next free slot
  void* mpData;
};

struct SlotBlock {
  SlotEntry mEntries[128];
};

struct SlotVector;
struct SlotIter {
  SlotVector* mpOwner;
  u32 mIndex;
  void increment();
};

static const u32 kSlotEmpty = 0x3fffffff;

int __cdecl SlotDistance(SlotIter first, SlotIter last);

struct SlotVector {
  SlotBlock** mpBegin;   // +0x00
  SlotBlock** mpEnd;     // +0x04
  void* mpField08;       // +0x08
  void* mpField0c;       // +0x0c
  void* mpField10;       // +0x10
  u32 mEndSlot;          // +0x14
  u32 mBeginIndex;       // +0x18
  u32 mFreeHead;         // +0x1c

  SlotEntry* entry(u32 i) { return &mpBegin[i >> 7]->mEntries[i & 0x7f]; }
  u32 endIndex() {
    return (u32)((mpEnd - mpBegin) * 128) + mEndSlot - 0x7f;
  }
  u32 nextAllocated(u32 i);
  void freeTarget(u32 i);
  void freeAgent(u32 i);
  SlotIter begin();
  SlotIter end() {
    SlotIter it;
    it.mpOwner = this;
    it.mIndex = endIndex();
    return it;
  }
  void destroyTargets(int freeMem);
  void destroyAgents(int freeMem);
  int size();
};

struct BlockAllocator {
  void release(SlotBlock* block);
};
extern BlockAllocator* g_pAllocator_16c8b44;

// target interface: slot +0x14 is release, +0x18 is detach, +0x08 is leave
struct cInteractionTarget {
  virtual void t00();
  virtual void t04();
  virtual void t08(void*);
  virtual void t0c();
  virtual void t10();
  virtual void t14();
  virtual void t18();
};

// agent interface: +0x20 interaction owner, +0x30 leave, +0x5c release
struct cInteractionAgent {
  virtual void a00();
  virtual void a04();
  virtual void a08();
  virtual void a0c();
  virtual void a10();
  virtual void a14();
  virtual void a18();
  virtual void a1c();
  virtual void* a20();
  virtual void a24();
  virtual void a28();
  virtual void a2c();
  virtual void a30(void*);
  virtual void a34();
  virtual void a38();
  virtual void a3c();
  virtual void a40();
  virtual void a44();
  virtual void a48();
  virtual void a4c();
  virtual void a50();
  virtual void a54();
  virtual void a58();
  virtual void a5c();
};

struct cInteraction;
struct cInteractionAgent;

struct cAgentData {
  int mState;           // +0x00
  u32 mSleepTimeout;    // +0x04
};

struct AgentNode {
  AgentNode* mpLeft;        // +0x00
  AgentNode* mpRight;       // +0x04
  AgentNode* mpParent;      // +0x08
  u32 mColor;               // +0x0c
  cInteractionAgent* mpKey; // +0x10
  cAgentData mData;         // +0x14
};

// eastl::map<cInteractionAgent*, cAgentData>: comparator/allocator at +0x00,
// embedded anchor (left/right/parent/color) at +0x04, root in anchor.parent.
struct AgentMap {
  void* mpField00;      // +0x00
  AgentNode* mpLeft;    // +0x04 (anchor)
  AgentNode* mpRight;   // +0x08
  AgentNode* mpRoot;    // +0x0c (anchor.parent)
  u32 mColor;           // +0x10
  u32 mSize;            // +0x14

  AgentNode* sentinel() { return (AgentNode*)&mpLeft; }
  AgentNode* lower_bound(cInteractionAgent* key) {
    AgentNode* node = mpRoot;
    AgentNode* candidate = sentinel();
    while (node) {
      if (node->mpKey < key) {
        node = node->mpLeft;
      } else {
        candidate = node;
        node = node->mpRight;
      }
    }
    if (candidate != sentinel() && key < candidate->mpKey) candidate = sentinel();
    return candidate;
  }
  AgentNode** find(AgentNode** out, cInteractionAgent* key);
  void erase(cInteractionAgent** key);
};

// predicate used by the agent filter range
struct IsAgentActive {
  cInteraction* mpOwner;  // +0x00
  u8 mCheckMap;           // +0x04
  u8 mPad05[3];
  bool evaluate(cInteractionAgent* agent);
};

struct AgentFilterRange {
  SlotIter mBegin;        // +0x00
  SlotIter mEnd;          // +0x08
  IsAgentActive mPred;    // +0x10
  AgentFilterRange(SlotVector* v, IsAgentActive* pred);
  void advance();
};

struct cInteractionVtbl {
  void* mSlots[24];
};
typedef bool (__thiscall* AddTargetFn)(cInteraction*, cInteractionTarget*);
typedef cInteractionTarget* (__thiscall* RemoveTargetFn)(cInteraction*, SlotIter*, SlotVector*, u32);

struct cInteraction {
  cInteractionVtbl* mpVtbl;   // +0x00
  void* mpRefCount;           // +0x04
  u32 mPad08;                 // +0x08
  SlotVector mTargetList;     // +0x0c
  SlotVector mAgentList;      // +0x2c
  AgentMap mAgentData;        // +0x4c
  u32 mPad64;                 // +0x64
  int mInteractionType;       // +0x68
  int mInteractionDependency; // +0x6c
  int mInteractionState;      // +0x70

  bool IsAgentDefault(cInteractionAgent* agent);
  void SetTarget(cInteractionTarget* target);
  void RemoveAgent(AgentFilterRange range);
  bool HasAgent(cInteractionAgent* agent);
  bool HasTarget(cInteractionTarget* target);
  SlotIter* RemoveTarget(SlotIter* out, SlotVector* vec, u32 index);
};

struct cInteractionTarget;
struct cInteractionAgent;

// ---------------------------------------------------------------------------
// EA::Swarm description objects
// ---------------------------------------------------------------------------
namespace EA {
namespace Swarm {

struct cShakeDescription {
  void* mpVtbl;       // +0x00
  void* mpField04;    // +0x04
  u32 mHash;          // +0x08
  void* mpField0c;    // +0x0c
  float mField10;     // +0x10
  float mField14;     // +0x14
  void* mpField18;    // +0x18
  void* mpField1c;    // +0x1c
  void* mpField20;    // +0x20
  void* mpField24;    // +0x24
  void* mpField28;    // +0x28
  void* mpField2c;    // +0x2c
  void* mpField30;    // +0x30
  void* mpField34;    // +0x34
  void* mpField38;    // +0x38
  void* mpField3c;    // +0x3c
  float mField40;     // +0x40
  void* mpField44;    // +0x44
  float mField48;     // +0x48
  static cShakeDescription* create(void* a, void* b);
};

struct MapDescription {
  void* mpVtbl;       // +0x00
  void* mpField04;    // +0x04
  u32 mFlags;         // +0x08
  u32 mPad0c;         // +0x0c
  union {
    float mField10;     // +0x10
    u32 mField10Int;
  };
  u32 mField14;       // +0x14
  u32 mField18;       // +0x18
  union {
    float mFrequency;   // +0x1c
    u32 mFrequencyInt;
  };
  float mField20;     // +0x20
  float mField24;     // +0x24
  static MapDescription* create(void* a, void* b);
  static void read(void* io, void* a, MapDescription* desc);
};

}  // namespace Swarm
}  // namespace EA

void __cdecl FUN_00abd9c0(void* a, void* b, void* obj);

// ---------------------------------------------------------------------------
// creature ability / feedback objects
// ---------------------------------------------------------------------------
struct AbilityConfig {
  u32 mPad00;
  u32 mPad04;
  u32 mFlags;      // +0x08
  u32 mPad0c;
  u32 mField10;    // +0x10
  u32 mField14;    // +0x14
  void* mpOwner;   // +0x18
  float mField1c;  // +0x1c
  float mField20;  // +0x20
};

struct cAbility {
  void* mpVtbl;            // +0x00
  void* mpVtbl2;           // +0x04
  u32 mField08;            // +0x08
  AbilityConfig* mpConfig; // +0x0c
  int mField10;            // +0x10
  int mField14;            // +0x14
  int mField18;            // +0x18
  u8 mActive;              // +0x1c
  void* mpOwner;           // +0x20
  float mAccum;            // +0x24
  float mThreshold;        // +0x28
  float mCurrent;          // +0x2c
  float mReported;         // +0x30
  bool SetParam(int id, const float* value, void* unused);
};

struct cAbilityEventModifier {
  void* mpVtbl;       // +0x00
  void* mpVtbl2;      // +0x04
  u32 mField08;       // +0x08
  void* mpOwner;      // +0x0c
  u32 mField10;       // +0x10
  u32 mField14;       // +0x14
  u32 mField18;       // +0x18
  u8 mField1c;        // +0x1c
  u32 mField20;       // +0x20
  float mField24;     // +0x24
  float mField28;     // +0x28
  float mField2c;     // +0x2c
  float mField30;     // +0x30
  static cAbilityEventModifier* create(void* owner);
};

struct MessageServer {
  void* mSlots[8];
};

struct cFeedbackMessage {
  void* mpVtbl;     // +0x00
  void* mpVtbl2;    // +0x04
  u32 mField08;     // +0x08
  u32 mField0c;     // +0x0c
  int mId;          // +0x10
  int mField14;     // +0x14
  void* mpOwner;    // +0x18
  int mField20;     // +0x20
  int mField24;     // +0x24
  int mField28;     // +0x28
  int mFlag;        // +0x2c
  char mPad30[0x28];
  int mField58;     // +0x58
};

struct cAbilityFeedback {
  void* mpVtbl;            // +0x00
  void* mpVtbl2;           // +0x04
  u32 mField08;            // +0x08
  AbilityConfig* mpConfig; // +0x0c
  int mField10;            // +0x10
  int mField14;            // +0x14
  int mField18;            // +0x18
  u8 mActive;              // +0x1c
  void* mpOwner;           // +0x20
  float mAccum;            // +0x24
  float mThreshold;        // +0x28
  float mCurrent;          // +0x2c
  float mReported;         // +0x30
  void Start(void* arg);
  void Stop(int arg);
  void Update(float dt, void* unused, int* counter);
};

// ---------------------------------------------------------------------------
// small transform owner (0xabe800)
// ---------------------------------------------------------------------------
struct ShapeTransform {
  unsigned short mField0;  // +0x00
  unsigned short mField2;  // +0x02
  float mField4;           // +0x04
  float mField8;           // +0x08
  float mFieldC;           // +0x0c
  float mField10;          // +0x10
  float mMatrix[9];        // +0x14
};

struct Matrix3 {
  void assign(const float* src);
};

struct TransformOps {
  void preTransformBy(void* arg);
};

struct Float3 {
  float x, y, z;
};

struct LocalTransform {
  unsigned short mField0;  // +0x00
  unsigned short mField2;  // +0x02
  Float3 mVec;             // +0x04
  float mField10;          // +0x10
  float mMatrix[9];        // +0x14
};

struct TransformThing {
  char mPad00[0x10];
  Float3 mVec;     // +0x10
  void SetTransform(void* arg, const ShapeTransform* src);
};

// ---------------------------------------------------------------------------
// noise source (0xabe110)
// ---------------------------------------------------------------------------
struct INoiseConfig {
  virtual void* v00();
  virtual void* v04();
  virtual void* v08();
  virtual void* v0c();
  virtual void* v10();
  virtual void* v14();
  virtual void* v18();
  virtual void* v1c();
  virtual void* v20();
  virtual void* v24();
  virtual void* v28();
  virtual void* v2c();
};

struct RandPair {
  float mX;
  float mY;
};

struct RNG {
  int mState;
  void setSeed(u32 seed);
};

RandPair* g_pairs1Begin;
RandPair* g_pairs1End;
RandPair* g_pairs1Cap;
RandPair* g_pairs2Begin;
RandPair* g_pairs2End;
RandPair* g_pairs2Cap;

RandPair* __cdecl FUN_00abda70(RandPair* out, RNG* rng, const RandPair* minv, const RandPair* maxv);

struct cNoiseSource {
  char mPad00[0x10];
  void* mField10;  // +0x10
  void* mField14;  // +0x14
  void Init(INoiseConfig* cfg, void* a, void* b);
};

// ---------------------------------------------------------------------------
// declaration order for the 0xabece0 helper
// ---------------------------------------------------------------------------
SlotIter* __cdecl FUN_00ac03f0(SlotIter* out, SlotVector* a, u32 ai, SlotVector* b, u32 bi, void* value);

// ===========================================================================
// definitions (one column-0 marker per function)
// ===========================================================================

// @ 0x00abe110
void cNoiseSource::Init(INoiseConfig* cfg, void* a, void* b) {
  mField10 = cfg->v20();
  mField14 = cfg->v2c();
  if (g_pairs1Begin == g_pairs1End) {
    u32 count = (u32)(g_pairs1End - g_pairs1Begin);
    RandPair fillValue;
    if (count < 0x40) {
      FUN_00abb820(g_pairs1End, 0x40 - (int)count, &fillValue);
    } else {
      FUN_00d018d0(g_pairs1Begin + 0x40, g_pairs1End);
    }
    count = (u32)(g_pairs2End - g_pairs2Begin);
    if (count < 0x40) {
      FUN_00abb820(g_pairs2End, 0x40 - (int)count, &fillValue);
    } else {
      FUN_00d018d0(g_pairs2Begin + 0x40, g_pairs2End);
    }
    RNG rng;
    rng.setSeed(0x58);
    RandPair minv;
    RandPair maxv;
    maxv.mX = 10.0f;
    maxv.mY = 10.0f;
    minv.mX = -10.0f;
    minv.mY = -10.0f;
    for (int i = 0; i < 0x40; ++i) {
      RandPair* p = FUN_00abda70(&fillValue, &rng, &minv, &maxv);
      if (g_pairs1End < g_pairs1Cap) {
        *g_pairs1End = *p;
        ++g_pairs1End;
      } else {
        FUN_008399d0(g_pairs1End, p);
      }
    }
    float scale = g_noiseSeed * 0.015625f;
    for (int i = 0; i < 0x40; ++i) {
      RandPair p;
      p.mX = 0.0f;
      p.mY = (float)sinf((float)i * scale) * 10.0f;
      if (g_pairs2End < g_pairs2Cap) {
        *g_pairs2End = p;
        ++g_pairs2End;
      } else {
        FUN_008399d0(g_pairs2End, &p);
      }
    }
  }
}

// @ 0x00abe2f0
namespace EA {
namespace Swarm {
cShakeDescription* cShakeDescription::create(void* a, void* b) {
  cShakeDescription* p = (cShakeDescription*)operator_new(0x4c, "Swarm", 0, 0, 0, 0);
  cShakeDescription* result = 0;
  if (p) {
    float zero = 0.0f;
    float one = g_hkRealOne;
    p->mpField04 = 0;
    p->mHash = 0xcbb908f4;
    p->mpVtbl = (void*)&g_vtbl_14599a8;
    p->mpField0c = 0;
    p->mField10 = zero;
    p->mField14 = one;
    p->mpField18 = 0;
    p->mpField1c = 0;
    p->mpField20 = 0;
    p->mpField2c = 0;
    p->mpField30 = 0;
    p->mpField34 = 0;
    p->mpField44 = 0;
    p->mField40 = one;
    p->mField48 = zero;
    result = p;
  }
  FUN_00abd9c0(a, b, result);
  return result;
}
}  // namespace Swarm
}  // namespace EA

// @ 0x00abe370
void InitializeSwarmFactories() {
  u32 two = 2;
  extern void* g_factory_1675f78;
  extern void* g_factory_1675f7c;
  extern u32 g_factory_1675f88;
  extern u32 g_factory_1675f8c;
  g_factory_1675f78 = (void*)&FUN_00abe010;
  g_factory_1675f7c = (void*)&EA::Swarm::cShakeDescription::create;
  g_factory_1675f88 = two;
  g_factory_1675f8c = two;
}

void* g_factory_1675f78;
void* g_factory_1675f7c;
u32 g_factory_1675f88;
u32 g_factory_1675f8c;

// @ 0x00abe3a0
namespace EA {
namespace Swarm {
void MapDescription::read(void* io, void* a, MapDescription* desc) {
  u32 local;
  EA_IO_ReadInt32(io, &local, 1, 0);
  desc->mFlags = local & 0x1f;
  EA_IO_ReadVector(io, &desc->mField10, 1, 0);
  EA_IO_ReadInt32(io, &desc->mField18, 1, 0);
  EA_IO_ReadInt32(io, &desc->mFrequencyInt, 1, 0);
  EA_IO_ReadInt32(io, (u32*)&desc->mField20, 1, 0);
  EA_IO_ReadInt32(io, (u32*)&desc->mField24, 1, 0);
}
}  // namespace Swarm
}  // namespace EA

// @ 0x00abe420
bool cAbility::SetParam(int id, const float* value, void* unused) {
  if (id != 0xf) return false;
  mCurrent = *value;
  return true;
}

// @ 0x00abe440
u32 __cdecl ScoreEffect(void* unused, AbilityConfig* cfg, u32* out, int count) {
  u32 a = cfg->mField10;
  u32 b = cfg->mField14;
  u32 r = 0;
  if ((b & a) != 0xffffffff) {
    r = 1;
    if (count > 0) {
      out[0] = a;
      out[1] = b;
      out[2] = 3;
    }
  }
  (void)unused;
  return r;
}

// @ 0x00abe480
void cAbilityFeedback::Start(void* arg) {
  if (!mActive) {
    mAccum = 0.0f;
    mThreshold = 0.0f;
    mReported = g_hkRealOne;
    void* owner = this;
    if ((mpConfig->mFlags >> 4) & 1) owner = mpConfig->mpOwner;
    mpOwner = owner;
    MessageServer* server = EA_Messaging_GetServer();
    if (server) {
      cFeedbackMessage msg;
      msg.mField58 = 0;
      msg.mpVtbl = (void*)&g_vtbl_13eb90c;
      msg.mpVtbl2 = 0;
      msg.mpVtbl = (void*)&g_vtbl_1452a38;
      msg.mField08 = 0;
      msg.mId = (int)mpConfig->mField10;
      msg.mpOwner = mpOwner;
      msg.mField20 = mpConfig->mFlags & 1;
      msg.mFlag = (mpConfig->mFlags >> 1) & 1;
      ((SendMsgFn)server->mSlots[5])(server, 0xff0ec1, &msg, 0);
      mActive = 1;
    }
  }
  (void)arg;
}

// @ 0x00abe540
void cAbilityFeedback::Stop(int arg) {
  if (mActive) {
    mActive = 0;
    if ((mpConfig->mFlags >> 3) & 1) {
      MessageServer* server = EA_Messaging_GetServer();
      if (server) {
        cFeedbackMessage msg;
        msg.mField58 = 0;
        msg.mpVtbl = (void*)&g_vtbl_13eb90c;
        msg.mpVtbl2 = 0;
        msg.mpVtbl = (void*)&g_vtbl_1452a38;
        msg.mField0c = (u32)mpOwner;
        msg.mId = arg != 0;
        ((SendMsgFn)server->mSlots[5])(server, 0xff0ed1, &msg, 0);
      }
    }
  }
}

// @ 0x00abe5c0
void cAbilityFeedback::Update(float dt, void* unused, int* counter) {
  mAccum = dt + mAccum;
  MessageServer* server = EA_Messaging_GetServer();
  if (0.0f < mpConfig->mField1c && mThreshold < mAccum) {
    mThreshold = mpConfig->mField1c + mAccum;
    cFeedbackMessage msg;
    msg.mField58 = 0;
    msg.mpVtbl = (void*)&g_vtbl_13eb90c;
    msg.mpVtbl2 = 0;
    msg.mpVtbl = (void*)&g_vtbl_1452a38;
    msg.mId = mField10;
    msg.mpOwner = mpOwner;
    msg.mField20 = mField14;
    msg.mField24 = mField18;
    ((SendMsgFn)server->mSlots[5])(server, 0xff0f31, &msg, 0);
  }
  if (mReported != mCurrent) {
    mReported = mCurrent;
    cFeedbackMessage msg;
    msg.mField58 = 0;
    msg.mpVtbl = (void*)&g_vtbl_13eb90c;
    msg.mpVtbl2 = 0;
    msg.mpVtbl = (void*)&g_vtbl_1452a38;
    msg.mId = (int)mpOwner;
    msg.mField20 = (int)mCurrent;
    ((SendMsgFn)server->mSlots[5])(server, 0xff0f2c, &msg, 0);
  }
  ++counter[0xb];
  if (0.0f < mpConfig->mField20 && mpConfig->mField20 < mAccum) {
    void** vtp = (void**)mpVtbl;
    ((void(__thiscall*)(cAbilityFeedback*, int))vtp[3])(this, 1);
  }
  (void)unused;
}

// @ 0x00abe700
cAbilityEventModifier* cAbilityEventModifier::create(void* owner) {
  cAbilityEventModifier* p = (cAbilityEventModifier*)operator_new(0x34, "Swarm", 0, 0, 0, 0);
  if (p) {
    p->mpVtbl2 = (void*)&g_vtbl_13ef094;
    p->mField08 = 0;
    p->mField24 = 0.0f;
    p->mField28 = 0.0f;
    float one = g_hkRealOne;
    p->mpVtbl = (void*)&g_vtbl_1459a88;
    p->mpVtbl2 = (void*)&g_vtbl_14599e8;
    p->mpOwner = owner;
    p->mField1c = 0;
    p->mField20 = 0;
    p->mField2c = one;
    p->mField30 = one;
    return p;
  }
  return 0;
}

// @ 0x00abe770
namespace EA {
namespace Swarm {
MapDescription* MapDescription::create(void* a, void* b) {
  MapDescription* p = (MapDescription*)operator_new(0x28, "Swarm", 0, 0, 0, 0);
  MapDescription* result = 0;
  if (p) {
    p->mpField04 = 0;
    p->mpVtbl = (void*)&g_vtbl_1453948;
    p->mFlags = 0;
    p->mFrequency = g_mapFrequency;
    p->mField10Int = 0;
    p->mField14 = 0;
    p->mField20 = 0.0f;
    p->mField24 = 0.0f;
    result = p;
  }
  read(a, b, result);
  return result;
}
}  // namespace Swarm
}  // namespace EA

// @ 0x00abe800
void TransformThing::SetTransform(void* arg, const ShapeTransform* src) {
  LocalTransform local;
  local.mField0 = src->mField0;
  local.mField2 = src->mField2;
  local.mVec.x = src->mField4;
  local.mVec.y = src->mField8;
  local.mVec.z = src->mFieldC;
  local.mField10 = src->mField10;
  ((Matrix3*)local.mMatrix)->assign(src->mMatrix);
  ((TransformOps*)&local)->preTransformBy(arg);
  mVec = local.mVec;
}

// @ 0x00abe8f0
void SlotVector::freeTarget(u32 i) {
  SlotEntry* e = entry(i);
  cInteractionTarget* p = (cInteractionTarget*)e->mpData;
  if (p) p->t14();
  e->mMeta = (mFreeHead & 0x3fffffff) | (e->mMeta & 0xc0000000) | 0x80000000;
  mFreeHead = i;
  if (mBeginIndex == i) mBeginIndex = nextAllocated(i);
}

// @ 0x00abe950
void SlotVector::freeAgent(u32 i) {
  SlotEntry* e = entry(i);
  cInteractionAgent* p = (cInteractionAgent*)e->mpData;
  if (p) p->a5c();
  e->mMeta = (mFreeHead & 0x3fffffff) | (e->mMeta & 0xc0000000) | 0x80000000;
  mFreeHead = i;
  if (mBeginIndex == i) mBeginIndex = nextAllocated(i);
}

// @ 0x00abe8a0
u32 SlotVector::nextAllocated(u32 i) {
  u32 m = entry(i)->mMeta;
  do {
    if ((m >> 30) & 1) return kSlotEmpty;
    ++i;
    m = entry(i)->mMeta;
  } while ((int)m < 0);
  return i;
}

// @ 0x00abe9b0
NOINLINE void SlotIter::increment() {
  u32 cur;
  do {
    cur = mIndex;
    mIndex = cur + 1;
    if ((mpOwner->entry(cur)->mMeta >> 30) & 1) return;
  } while ((int)mpOwner->entry(mIndex)->mMeta < 0);
}

// @ 0x00abea40
bool cInteraction::IsAgentDefault(cInteractionAgent* agent) {
  AgentNode* node;
  AgentNode** it = mAgentData.find(&node, agent);
  node = *it;
  if (node == mAgentData.sentinel()) return false;
  return node->mData.mState == 0 && node->mData.mSleepTimeout == 0;
}

// @ 0x00abea90
bool IsAgentActive::evaluate(cInteractionAgent* agent) {
  cInteraction* owner = mpOwner;
  if (owner) {
    if (mCheckMap) {
      AgentNode* node;
      AgentNode** it = owner->mAgentData.find(&node, agent);
      node = *it;
      if (node == owner->mAgentData.sentinel()) return true;
      if (node->mData.mState == 0) return true;
    }
    if (!owner->IsAgentDefault(agent)) return false;
  }
  return true;
}

// @ 0x00abeaf0
SlotIter SlotVector::begin() {
  u32 i = mBeginIndex;
  if (i >= kSlotEmpty) i = endIndex();
  SlotIter it;
  it.mpOwner = this;
  it.mIndex = i;
  return it;
}

// @ 0x00abeb20
void AgentFilterRange::advance() {
  for (;;) {
    mBegin.increment();
    if ((u32)mEnd.mpOwner + mEnd.mIndex == (u32)mBegin.mpOwner + mBegin.mIndex) return;
    cInteractionAgent* agent = (cInteractionAgent*)mBegin.mpOwner->entry(mBegin.mIndex)->mpData;
    cInteraction* owner = mPred.mpOwner;
    if (!owner) return;
    if (mPred.mCheckMap) {
      AgentNode* node = owner->mAgentData.lower_bound(agent);
      if (node == owner->mAgentData.sentinel()) return;
      if (node->mData.mState == 0) return;
    }
    AgentNode* node = owner->mAgentData.lower_bound(agent);
    if (node == owner->mAgentData.sentinel()) continue;
    if (node->mData.mState != 0) continue;
    if (node->mData.mSleepTimeout != 0) continue;
    return;
  }
}

// @ 0x00abec00
void SlotVector::destroyTargets(int freeMem) {
  while (mpBegin != mpEnd) {
    SlotEntry* e = &mpEnd[-1]->mEntries[mEndSlot];
    u32 meta = e->mMeta;
    u8 free = (u8)(meta >> 31);
    if ((free & 1) == 0) {
      void* data = e->mpData;
      if (data) ((cInteractionTarget*)data)->t14();
    }
    if (mEndSlot == 0) {
      g_pAllocator_16c8b44->release(mpEnd[-1]);
      --mpEnd;
      mEndSlot = 0x7f;
    } else {
      --mEndSlot;
    }
  }
  (void)freeMem;
}

// @ 0x00abec70
void SlotVector::destroyAgents(int freeMem) {
  while (mpBegin != mpEnd) {
    SlotEntry* e = &mpEnd[-1]->mEntries[mEndSlot];
    u32 meta = e->mMeta;
    u8 free = (u8)(meta >> 31);
    if ((free & 1) == 0) {
      void* data = e->mpData;
      if (data) ((cInteractionAgent*)data)->a5c();
    }
    if (mEndSlot == 0) {
      g_pAllocator_16c8b44->release(mpEnd[-1]);
      --mpEnd;
      mEndSlot = 0x7f;
    } else {
      --mEndSlot;
    }
  }
  (void)freeMem;
}

// @ 0x00abece0
bool __cdecl SlotVectorInsert(SlotVector* v, void* value) {
  u32 end = v->endIndex();
  u32 begin = v->mBeginIndex;
  if (begin >= kSlotEmpty) begin = end;
  SlotIter buf;
  SlotIter* it = FUN_00ac03f0(&buf, v, begin, v, end, value);
  return (u32)v + end != (u32)it->mpOwner + it->mIndex;
}

// @ 0x00abed40
void cInteraction::SetTarget(cInteractionTarget* target) {
  if (mTargetList.mBeginIndex != kSlotEmpty) {
    do {
      u32 i = mTargetList.mBeginIndex;
      if (i >= kSlotEmpty) i = mTargetList.endIndex();
      SlotIter out;
      ((RemoveTargetFn)mpVtbl->mSlots[20])(this, &out, &mTargetList, i);
    } while (mTargetList.mBeginIndex != kSlotEmpty);
  }
  ((AddTargetFn)mpVtbl->mSlots[19])(this, target);
}

// @ 0x00abedb0
void cInteraction::RemoveAgent(AgentFilterRange range) {
  cInteractionAgent* p = (cInteractionAgent*)range.mBegin.mpOwner->entry(range.mBegin.mIndex)->mpData;
  if (p) {
    if ((cInteraction*)p->a20() == this) {
      mAgentList.freeAgent(range.mBegin.mIndex);
      mAgentData.erase(&p);
      p->a30(this);
    }
  }
}

// @ 0x00abee20
bool cInteraction::HasAgent(cInteractionAgent* agent) {
  SlotVector* v = &mAgentList;
  SlotIter it = v->begin();
  SlotIter last = v->end();
  if ((u32)v + it.mIndex != (u32)v + last.mIndex) {
    do {
      if (v->entry(it.mIndex)->mpData == agent) return true;
      it.increment();
    } while ((u32)v + it.mIndex != (u32)v + last.mIndex);
  }
  return false;
}

// @ 0x00abeeb0
bool cInteraction::HasTarget(cInteractionTarget* target) {
  SlotVector* v = &mTargetList;
  SlotIter it = v->begin();
  SlotIter last = v->end();
  if ((u32)v + it.mIndex != (u32)v + last.mIndex) {
    do {
      if (v->entry(it.mIndex)->mpData == target) return true;
      it.increment();
    } while ((u32)v + it.mIndex != (u32)v + last.mIndex);
  }
  return false;
}

// @ 0x00abef40
SlotIter* cInteraction::RemoveTarget(SlotIter* out, SlotVector* vec, u32 index) {
  cInteractionTarget* p = (cInteractionTarget*)vec->entry(index)->mpData;
  if (p) {
    p->t18();
    mTargetList.freeTarget(index);
    SlotIter it;
    it.mpOwner = vec;
    it.mIndex = index;
    it.increment();
    out->mpOwner = it.mpOwner;
    out->mIndex = it.mIndex;
    p->t08(this);
  } else {
    out->mpOwner = vec;
    out->mIndex = index;
  }
  if (p) p->t14();
  return out;
}

// @ 0x00abefd0
int SlotVector::size() {
  u32 end = endIndex();
  u32 begin = mBeginIndex;
  if (begin >= kSlotEmpty) begin = end;
  typedef int(__cdecl * Distance5)(SlotVector*, u32, SlotVector*, u32, SlotVector*);
  return ((Distance5)SlotDistance)(this, begin, this, end, this);
}

// @ 0x00abea00
NOINLINE int __cdecl SlotDistance(SlotIter first, SlotIter last) {
  int n = 0;
  while ((u32)first.mpOwner + first.mIndex != (u32)last.mpOwner + last.mIndex) {
    first.increment();
    ++n;
  }
  return n;
}

// @ 0x00abf010
AgentFilterRange::AgentFilterRange(SlotVector* v, IsAgentActive* pred) {
  mBegin.mIndex = v->mBeginIndex;
  if (mBegin.mIndex >= kSlotEmpty) mBegin.mIndex = v->endIndex();
  mBegin.mpOwner = v;
  mEnd.mIndex = v->endIndex();
  mEnd.mpOwner = v;
  mPred = *pred;
  if ((u32)mEnd.mpOwner + mEnd.mIndex != (u32)mBegin.mpOwner + mBegin.mIndex) {
    cInteractionAgent* agent = (cInteractionAgent*)mBegin.mpOwner->entry(mBegin.mIndex)->mpData;
    if (!mPred.evaluate(agent)) advance();
  }
}
