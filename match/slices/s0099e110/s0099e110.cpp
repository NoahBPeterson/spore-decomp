// Slice s0099e110: creature-animation static-data loader and small helpers.
// Reconstructed from the annotated disassembly; real names from the 2008 PDB where known.
#include "types.h"

// ---------------------------------------------------------------------------
// stubs
// ---------------------------------------------------------------------------
struct S99d060 { void f(); };                 // release a reference (0x99d060)
struct S99ed90 { int f(void*, char*, int); }; // ReadAnimationStaticDataFromStreamWrapper (external)
extern int FUN_0099ed90();                    // skeleton body for the standalone VA
extern void FUN_f47380(void*);                 // operator delete(void*) cdecl
extern int FUN_00a088e0(int);
extern void FUN_11e073e(void*, int, int);
extern void __stdcall FUN_401930(void*, int, int, void*);
extern void FUN_0099cf50();
extern int g_15504dc;

extern "C" __declspec(dllimport) void* __cdecl fopen(const char*, const char*);
extern "C" __declspec(dllimport) int   __cdecl fclose(void*);

// ---------------------------------------------------------------------------
// @ 0x0099e110  AccumulateAnimationMotion (2963 bytes, __cdecl, 6 args)
// Built with /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS- (sibling of 0x0099d460, slice s0099d460)
//
// For every active bone binding of an animation set (flag 1 set, flag 8 clear, in the set's
// layer), evaluates the bone's position/rotation channels (EvaluateBoneTransform) and adds the
// weighted results to the set's and the creature's motion accumulators: absolute pose
// (creature +0x118/+0x128), and the per-frame deltas against the animation's previous pose
// (+0x1c0/+0x1cc), split by the header's 0x100003 channel kind (0x100000 = local, else rotated
// into world space). Scalar type-3 channels add their weight/phase to creature +0x110/+0x114.
// Layouts are local stubs with offsets read from the disassembly.
// ---------------------------------------------------------------------------
namespace e110 {

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};

struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
    Quaternion(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}
    Quaternion& operator=(const Quaternion& o);     // @ 0x00572600
};

struct AnimChannel {                // 0x20 bytes
    uint32_t mFlags;                // +0x00 (bits 0-3 type)
    uint32_t mKey;                  // +0x04
    uint32_t pad08[2];
    uint32_t mIndex;                // +0x10
    uint32_t pad14[3];
};

struct AnimHeader {                 // at animation data +0x88
    uint32_t mFlags;                // +0x00
    uint32_t mKind;                 // +0x04 (& 0x100003)
};

struct AnimData {
    char pad0[0x88];
    AnimHeader mHeader;             // +0x88
    char pad90[0xdc - 0x90];
    uint32_t mChannelCount;         // +0xdc
    AnimChannel* mpChannels;        // +0xe0

    __forceinline AnimChannel* FindChannel(uint32_t type) {
        for (uint32_t i = 0; i < mChannelCount; i++) {
            if ((mpChannels[i].mFlags & 0xf) == type && mpChannels[i].mKey != 0)
                return &mpChannels[i];
        }
        return 0;
    }
};

struct AnimAux {                    // 40 bytes, indexed by channel mIndex - 3
    float mPhase;                   // +0x00
    float mWeight;                  // +0x04
    uint32_t pad[8];
};

struct AnimInstance {               // 0x1f0 bytes
    AnimData* mpData;               // +0x00
    uint32_t pad04[3];
    uint8_t mFlags;                 // +0x10
    char pad11[7];
    float mArg18[3];                // +0x18 (position-channel state)
    float mPosWeight;               // +0x24
    char pad28[0x68 - 0x28];
    float mArg68[4];                // +0x68 (rotation-channel state)
    float mRotWeight;               // +0x78
    char pad7c[0xcc - 0x7c];
    AnimAux mAux[6];                // +0xcc
    uint32_t pad1bc;                // +0x1bc
    Vector3 mPrevPos;               // +0x1c0
    Quaternion mPrevRot;            // +0x1cc
    char pad1dc[0x1f0 - 0x1dc];
};

struct BoneBinding {                // 16 bytes
    unsigned __int64 mLayerMask;    // +0x00
    uint32_t mChannelMask;          // +0x08 (low 24 bits)
    uint8_t mBone;                  // +0x0c
    uint8_t mAnim;                  // +0x0d
    uint8_t mParent;                // +0x0e
    uint8_t mFlags;                 // +0x0f
};

template <typename T>
struct vector {                     // eastl::vector (begin, end, capacity, allocator)
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t n) { return mpBegin[n]; }
};

struct AnimState {
    uint32_t pad0[7];
    vector<BoneBinding> mBindings;  // +0x1c
};

struct AnimSet {
    void* mpData;                   // +0x00
    uint32_t pad04;
    AnimState* mpState;             // +0x08
    uint32_t mLayer;                // +0x0c
    uint32_t pad10;
    AnimInstance* mpAnims;          // +0x14
    uint32_t pad18[5];
    Vector3 mPosLocal;              // +0x2c
    float mPosLocalWeight;          // +0x38
    Quaternion mRotLocal;           // +0x3c
    float mRotLocalWeight;          // +0x4c
    Vector3 mPos;                   // +0x50
    float mPosWeight;               // +0x5c
    Quaternion mRot;                // +0x60
    float mRotWeight;               // +0x70
};

struct BodyState;

struct CreatureInstance {
    char pad0[0x110];
    float mChannelPhase;            // +0x110
    float mChannelWeight;           // +0x114
    Vector3 mPos;                   // +0x118
    float mPosWeight;               // +0x124
    Quaternion mRot;                // +0x128
    float mRotWeight;               // +0x138
    Vector3 mDeltaPosLocal;         // +0x13c
    float mDeltaPosLocalWeight;     // +0x148
    Quaternion mDeltaRotLocal;      // +0x14c
    float mDeltaRotLocalWeight;     // +0x15c
    Vector3 mDeltaPos;              // +0x160
    float mDeltaPosWeight;          // +0x16c
    Quaternion mDeltaRot;           // +0x170
    float mDeltaRotWeight;          // +0x180
    Vector3 mDeltaPos2;             // +0x184
    float mDeltaPos2Weight;         // +0x190
    Quaternion mDeltaRot2;          // +0x194
    float mDeltaRot2Weight;         // +0x1a4
    uint8_t mHasLocalMotion;        // +0x1a8
    uint8_t mHasMotion;             // +0x1a9
    char pad1aa[0x2e4 - 0x1aa];
    BodyState* mpBodies;            // +0x2e4
};

void __cdecl EvaluateBoneTransform(AnimHeader* header, Vector3* parentPos, AnimChannel* posChannel,
                                   float* arg18, AnimChannel* rotChannel, float* arg68,
                                   CreatureInstance* creature, BodyState* body, Vector3* rootPos,
                                   Quaternion* rootRot, Vector3* outPos, Quaternion* outRot,
                                   int flags);                                  // @ 0x009b0e90
Quaternion __cdecl QuatAccumulate(const Quaternion& a, const Quaternion& b);   // @ 0x0099cba0
Quaternion __cdecl QuatMultiply(const Quaternion& a, const Quaternion& b);     // @ 0x0099c0b0
Vector3 __cdecl QuatRotateInverse(const Quaternion& q, const Vector3& v);      // @ 0x0099c310

inline Quaternion operator*(const Quaternion& q, float s) {
    return Quaternion(q.x * s, q.y * s, q.z * s, q.w * s);
}

void __cdecl AccumulateAnimationMotion(float weight, CreatureInstance* creature, AnimSet* set,
                                       bool applyToCreature, bool applyToSet, bool skipDeltas)
{
    if (weight <= 0.0f)
        return;

    unsigned __int64 layerMask = (unsigned __int64)1 << set->mLayer;
    BodyState* bodies = creature->mpBodies;
    uint32_t bindCount = set->mpState->mBindings.size();
    for (uint32_t b = 0; b < bindCount; b++) {
        BoneBinding* bind = &set->mpState->mBindings[b];
        if ((bind->mFlags & 1) == 0 || (bind->mFlags & 8) != 0)
            continue;
        if ((bind->mLayerMask & layerMask) == 0)
            continue;

        AnimInstance* anim = &set->mpAnims[bind->mAnim];
        AnimHeader* header = &anim->mpData->mHeader;
        int bindFlags = bind->mFlags & 2;
        if ((anim->mFlags & 2) != 0) {
            uint32_t kind = header->mKind & 0x100003;
            if (kind == 0x100000)
                creature->mHasLocalMotion |= 1;
            else if (kind == 0x100001)
                creature->mHasMotion |= 1;
        }

        AnimData* data = anim->mpData;
        uint32_t channelMask = bind->mChannelMask & 0xffffff;
        AnimChannel* posChannel = data->FindChannel(1);
        uint32_t posMask = posChannel ? 1u << (posChannel - data->mpChannels) : 0;
        AnimChannel* rotChannel = data->FindChannel(2);
        uint32_t rotMask = rotChannel ? 1u << (rotChannel - data->mpChannels) : 0;

        if ((channelMask & (rotMask | posMask)) != 0 && weight > 0.0f) {
            Vector3 pos(0.0f, 0.0f, 0.0f);
            Quaternion rot(0.0f, 0.0f, 0.0f, 1.0f);
            Vector3 origin(0.0f, 0.0f, 0.0f);
            Quaternion identity(0.0f, 0.0f, 0.0f, 1.0f);
            EvaluateBoneTransform(header, &origin, posChannel, anim->mArg18, rotChannel, anim->mArg68,
                                  creature, bodies, &origin, &identity, &pos, &rot, bindFlags);

            if ((channelMask & posMask) != 0) {
                float pw = anim->mPosWeight * weight;
                if (pw > 0.0f) {
                    if (applyToSet) {
                        if ((header->mKind & 0x100003) == 0x100000) {
                            set->mPosLocal.x = set->mPosLocal.x + pos.x * pw;
                            set->mPosLocal.y = pos.y * pw + set->mPosLocal.y;
                            set->mPosLocal.z = set->mPosLocal.z + pos.z * pw;
                            set->mPosLocalWeight = set->mPosLocalWeight + pw;
                        } else {
                            set->mPos.x = pos.x * pw + set->mPos.x;
                            set->mPos.y = set->mPos.y + pos.y * pw;
                            set->mPos.z = pos.z * pw + set->mPos.z;
                            set->mPosWeight = set->mPosWeight + pw;
                        }
                    }
                    if (applyToCreature) {
                        if ((header->mKind & 0x100003) == 0x100000) {
                            creature->mPos.x = creature->mPos.x + pos.x * pw;
                            creature->mPos.y = pos.y * pw + creature->mPos.y;
                            creature->mPos.z = creature->mPos.z + pos.z * pw;
                            creature->mPosWeight = pw + creature->mPosWeight;
                        }
                        if (!skipDeltas) {
                            if ((header->mKind & 0x100003) == 0x100000) {
                                if ((anim->mFlags & 2) == 0) {
                                    creature->mDeltaPosLocal.x = (pos.x - anim->mPrevPos.x) * pw + creature->mDeltaPosLocal.x;
                                    creature->mDeltaPosLocal.y = creature->mDeltaPosLocal.y + (pos.y - anim->mPrevPos.y) * pw;
                                    creature->mDeltaPosLocal.z = (pos.z - anim->mPrevPos.z) * pw + creature->mDeltaPosLocal.z;
                                    creature->mDeltaPosLocalWeight = creature->mDeltaPosLocalWeight + pw;
                                }
                            } else {
                                Vector3 d((pos.x - anim->mPrevPos.x) * pw, (pos.y - anim->mPrevPos.y) * pw,
                                          (pos.z - anim->mPrevPos.z) * pw);
                                Vector3 r = QuatRotateInverse(anim->mPrevRot, d);
                                creature->mDeltaPos.x = creature->mDeltaPos.x + r.x;
                                creature->mDeltaPos.y = r.y + creature->mDeltaPos.y;
                                creature->mDeltaPos.z = creature->mDeltaPos.z + r.z;
                                creature->mDeltaPosWeight = pw + creature->mDeltaPosWeight;
                                if ((anim->mFlags & 2) == 0) {
                                    creature->mDeltaPos2.x = creature->mDeltaPos2.x + r.x;
                                    creature->mDeltaPos2.y = r.y + creature->mDeltaPos2.y;
                                    creature->mDeltaPos2.z = creature->mDeltaPos2.z + r.z;
                                    creature->mDeltaPos2Weight = creature->mDeltaPos2Weight + pw;
                                }
                            }
                        }
                        anim->mPrevPos.x = pos.x;
                        anim->mPrevPos.y = pos.y;
                        anim->mPrevPos.z = pos.z;
                    }
                }
            }

            if ((channelMask & rotMask) != 0) {
                float rw = anim->mRotWeight * weight;
                if (rw > 0.0f) {
                    if (applyToSet) {
                        if ((header->mKind & 0x100003) == 0x100000) {
                            set->mRotLocal = QuatAccumulate(set->mRotLocal, rot * rw);
                            set->mRotLocalWeight = rw + set->mRotLocalWeight;
                        } else {
                            set->mRot = QuatAccumulate(set->mRot, rot * rw);
                            set->mRotWeight = set->mRotWeight + rw;
                        }
                    }
                    if (applyToCreature) {
                        if ((header->mKind & 0x100003) == 0x100000) {
                            creature->mRot = QuatAccumulate(creature->mRot, rot * rw);
                            creature->mRotWeight = creature->mRotWeight + rw;
                        }
                        if (!skipDeltas) {
                            if ((header->mKind & 0x100003) == 0x100000) {
                                if ((anim->mFlags & 2) == 0) {
                                    Quaternion inv(-anim->mPrevRot.x, -anim->mPrevRot.y, -anim->mPrevRot.z,
                                                   anim->mPrevRot.w);
                                    Quaternion d = QuatMultiply(rot * rw, inv);
                                    creature->mDeltaRotLocal = QuatAccumulate(creature->mDeltaRotLocal, d);
                                    creature->mDeltaRotLocalWeight = creature->mDeltaRotLocalWeight + rw;
                                }
                            } else {
                                Quaternion inv(-anim->mPrevRot.x, -anim->mPrevRot.y, -anim->mPrevRot.z,
                                               anim->mPrevRot.w);
                                Quaternion d = QuatMultiply(rot * rw, inv);
                                creature->mDeltaRot = QuatAccumulate(creature->mDeltaRot, d);
                                creature->mDeltaRotWeight = rw + creature->mDeltaRotWeight;
                                if ((anim->mFlags & 2) == 0) {
                                    creature->mDeltaRot2 = QuatAccumulate(creature->mDeltaRot2, d);
                                    creature->mDeltaRot2Weight = creature->mDeltaRot2Weight + rw;
                                }
                            }
                        }
                        anim->mPrevRot.x = rot.x;
                        anim->mPrevRot.y = rot.y;
                        anim->mPrevRot.z = rot.z;
                        anim->mPrevRot.w = rot.w;
                    }
                }
            }
        }

        channelMask &= ~rotMask & ~posMask;
        uint32_t count = anim->mpData->mChannelCount;
        if (channelMask != 0) {
            for (uint32_t i = 0; i < count; i++) {
                if ((channelMask & (1 << i)) == 0)
                    continue;
                AnimChannel* ch = &anim->mpData->mpChannels[i];
                if ((ch->mFlags & 0xf) != 3)
                    continue;
                AnimAux& aux = anim->mAux[ch->mIndex - 3];
                float cw = aux.mWeight * weight;
                creature->mChannelWeight = creature->mChannelWeight + cw;
                creature->mChannelPhase = creature->mChannelPhase + aux.mPhase * cw;
            }
        }
    }
}

} // namespace e110

// ---------------------------------------------------------------------------
// @ 0x0099ecb0  AutoRefCount<SP::cSPCreatureBase>::operator=
// ---------------------------------------------------------------------------
struct S99ecb0 {
  S99ecb0* f(int p);
};
S99ecb0* S99ecb0::f(int p) {
  int old = *(int*)this;
  if (p != old) {
    if (p) *(int*)(p + 0x114) += 1;
    *(int*)this = p;
    if (old) ((S99d060*)(size_t)old)->f();
  }
  return this;
}

// ---------------------------------------------------------------------------
// @ 0x0099ece0  two struct-array initialisers + vector ctor + operator new
// ---------------------------------------------------------------------------
struct E16 { float a; float b; unsigned char c; unsigned char d; unsigned short e; char pad[4]; };
struct S99ece0 {
  S99ece0* f();
};
S99ece0* S99ece0::f() {
  char* self = (char*)this;
  char* p = self + 0x24;
  for (int i = 3; i >= 0; i--) {
    *(float*)(p) = 0.0f;
    *(float*)(p + 4) = 0.0f;
    *(unsigned char*)(p + 8) = 0;
    *(unsigned char*)(p + 9) = 0;
    *(unsigned short*)(p + 0xa) = 0;
    p += 0x10;
  }
  p = self + 0x78;
  for (int i = 4; i >= 0; i--) {
    *(float*)(p) = 0.0f;
    *(float*)(p + 4) = 0.0f;
    *(unsigned char*)(p + 8) = 0;
    *(unsigned char*)(p + 9) = 0;
    *(unsigned short*)(p + 0xa) = 0;
    p += 0x10;
  }
  p = self + 0xd0;
  for (int i = 5; i >= 0; i--) {
    FUN_401930(p, 0x10, 2, (void*)FUN_0099cf50);
    p += 0x28;
  }
  FUN_11e073e(self, 0, 0x1b8);
  *(int*)(self + 4) = g_15504dc;
  g_15504dc += 1;
  return this;
}

// ---------------------------------------------------------------------------
// @ 0x0099ed90  ReadAnimationStaticDataFromStreamWrapper  (skeleton body for the VA)
// ---------------------------------------------------------------------------
int FUN_0099ed90() { return 0; }

// ---------------------------------------------------------------------------
// @ 0x0099efa0  uninitialized_copy of 8-byte pairs
// ---------------------------------------------------------------------------
void FUN_0099efa0(char* first, char* last, char* dst) {
  if (first != last) {
    int off = (int)(first - dst);
    do {
      if (dst) {
        *(int*)dst = *(int*)(dst + off);
        *(int*)(dst + 4) = *(int*)(dst + off + 4);
      }
      dst += 8;
    } while (dst + off != last);
  }
}

// ---------------------------------------------------------------------------
// @ 0x0099efd0  nSPCreatureAnim::LoadAnimationStaticData
// ---------------------------------------------------------------------------
int FUN_0099efd0(char* name, int arg) {
  if (name == 0) {
    if (arg != 0) return FUN_00a088e0(arg);
    return 0;
  }
  void* file = fopen(name, "rb");
  if (file == 0) return 0;
  struct { void* vt; void* fp; } local;
  local.vt = (void*)0x1446dd8;
  local.fp = file;
  int r = ((S99ed90*)&local)->f(&local, name, arg);
  fclose(file);
  return r;
}

// ---------------------------------------------------------------------------
// @ 0x0099f050  free array of 0x40 heap blocks
// ---------------------------------------------------------------------------
struct S99f050 { void f(); };
void S99f050::f() {
  int* p = (int*)((char*)this + 0xc2c);
  for (int edi = 0x3f; edi >= 0; edi--) {
    int v = p[-10];
    p = (int*)((char*)p - 0x28);
    if (v && *(int*)(v - 4) != 0) FUN_f47380((void*)v);
  }
}

// ---------------------------------------------------------------------------
// @ 0x0099f090  zero a sub-object
// ---------------------------------------------------------------------------
struct S99f090 { S99f090* f(); };
S99f090* S99f090::f() {
  S99f090* self = this;
  int* p = (int*)this;
  p[0] = 0; p[1] = 0; p[2] = 0; p[3] = 0; p[5] = 0;
  p[7] = 0; p[8] = 0; p[9] = 0; p[0xc] = 0;
  return self;
}
