// src/game/SPAudio/eapdsymbolmanager.cpp -- migrated from slice(s) s00a670b0, s00a65f90, s009a69d0, s009a7810 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdsymbolmanager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPCreatureAnim/creature_body_instance_data.h"
#include "nSPCreatureAnim/creature_body_static_data.h"
#include "nSPCreatureAnim/creature_effect.h"
#include "nSPCreatureAnim/creature_instance_data.h"
#include "nSPCreatureAnim/dynamics_foot.h"
#include "checkerlib/vector_3.h"
#include "checkerlib/vector_4.h"
#include <intrin.h>
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void FUN_009c8900();

// ---- items of slice s009a7810 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  operator_new__(void* p, int a, int b);   // 0x011e073e (lib_crt placement init)
extern "C" uint32_t FUN_009a5860(uint32_t a0, void* a1, int a2, int a3, void* creature,
                                 uint32_t index, uint32_t defaultValue, int a7); // 0x009a5860
extern "C" char FUN_0099c710(uint32_t a, uint32_t b, uint32_t c);
extern "C" uint32_t FUN_0099d2b0(uint32_t a, int b, int c);
extern "C" void FUN_009a6e60(int a0, int a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5,
                              uint32_t a6, uint32_t a7, void* a8, void* a9, void* a10, uint32_t a11,
                              void* a12, int a13, int a14, uint32_t a15, int* a16, int a17, int a18,
                              uint32_t* a19, int a20);
struct CppRandom { double GenerateDouble(); };
void FUN_009a7810(int, int, int, int, int*, uint32_t, int, uint32_t*, int);
void FUN_009a7d90(uint32_t*, int, int, uint32_t*, int, int, int, int, int, int, uint32_t, float, int);
namespace nSPCreatureAnim {
    uint32_t ComputeEventLocationData(uint32_t flags, uint32_t* p2, uint32_t p3, uint32_t* owner,
                                      uint32_t p5, int p6, int* outLoc, int* outLoc2, uint8_t* outByte);
}
namespace nSPCreatureAnim {
    void ComputeEventLocationState(int a0, uint32_t flags, uint32_t a2, uint32_t a3, int a4,
                                   uint32_t a5, uint32_t a6, void* a7, void* a8, void* a9,
                                   void* a10, void* a11, void* a12, void* a13, int a14);
}
namespace nSPCreatureAnim {
    uint8_t ContextFilterEventLocationData(uint32_t a0, uint32_t a1, int* buf, uint32_t a3, uint32_t a4);
}
struct LocData { int count; int items[254]; };
struct creature_mesh_instance_data;                       // ?RefreshWorldState@... 0x009c8900
struct ht_node_s009a7810 {
    uint32_t                      mKey;    // +0x0  (pair<...>::first)
    creature_mesh_instance_data*  mValue;  // +0x4  (pair<...>::second)
    ht_node_s009a7810*            mpNext;  // +0x8
};
struct ht_iter_s009a7810 {
    ht_node_s009a7810*  mpNode;            // +0x0
    ht_node_s009a7810** mpBucket;          // +0x4
    ht_iter_s009a7810& operator++() {
        mpNode = mpNode->mpNext;
        while (!mpNode) {
            ++mpBucket;
            mpNode = *mpBucket;
        }
        return *this;
    }
};
struct ht_pair_s009a7810 {
    ht_iter_s009a7810 first;               // +0x0
    ht_iter_s009a7810 last;                // +0x8
};
struct ht_s009a7810 {
    uint32_t             mHash;            // +0x0
    ht_node_s009a7810**  mpBucketArray;    // +0x4
    uint32_t             mnBucketCount;    // +0x8
    ht_pair_s009a7810 equal_range(const uint32_t& key);   // 0x009a6dd0
};
struct creature_mesh_instance_data {
    uint8_t  pad_0[0x34];                  // +0x0 .. +0x33
    uint32_t mFlags;                       // +0x34
    void RefreshWorldState();              // ?RefreshWorldState@creature_mesh_instance_data@@QAEXXZ
};
inline ht_s009a7810* ht_table_s009a7810(int p)
{
    return (ht_s009a7810*)(*(char**)(p + 4) + 0x17a0);
}
// ---- items of slice s009a7810 end

// ---- items of slice s009a69d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl fabs(double);
extern float g_01550aa8;                                                            // 0x01550aa8
extern float g_01550aac;                                                            // 0x01550aac
extern float g_hitBodyScale;                                                        // 0x01550ac4
#pragma intrinsic(sqrt)
#pragma intrinsic(fabs)
typedef unsigned int uint32;
namespace checkerlib {
class vector_3_s009a_69d0 {
public:
    float x;   // +0x0
    float y;   // +0x4
    float z;   // +0x8
};
}
namespace checkerlib {
class vector_4_s009a_69d0 {
public:
    float x;   // +0x0
    float y;   // +0x4
    float z;   // +0x8
    float w;   // +0xc
};
}
namespace eastl {
struct hash_node_s009a_69d0 {
    uint32 mKey;                               // +0x00
    void* mpValue;                             // +0x04
    hash_node_s009a_69d0* mpNext;                         // +0x08
};
}
namespace eastl {
struct hashtable_iterator {
    hash_node_s009a_69d0* mpNode;                         // +0x00
    hash_node_s009a_69d0** mpBucket;                      // +0x04
    void Advance();                            // 0x009a69d0
};
}
namespace eastl {
struct hashtable_range {
    hashtable_iterator first;                  // +0x00
    hashtable_iterator second;                 // +0x08
};
}
typedef eastl::hashtable_range EapdRange;
typedef eastl::hash_node_s009a_69d0 EapdHashNode;
typedef eastl::hashtable_iterator EapdIterator;
class EapdHashTable {
public:
    unsigned char mUnknown0[4];                // +0x00
    EapdHashNode** mpBucketArray;              // +0x04
    uint32 mnBucketCount;                      // +0x08
    EapdRange equal_range(const uint32& key);
    EapdIterator begin();                      // 0x00594410
};
struct XformMsg {
    unsigned short mFlags;                     // +0x00
    unsigned short mCount;                     // +0x02
    checkerlib::vector_3_s009a_69d0 mPos;                 // +0x04
    float mScale;                              // +0x10
    float mRot[9];                             // +0x14
    XformMsg();                                // 0x00434040
};
struct IVisualEffect {
    virtual int Unknown0();                    // +0x00
    virtual void Release();                    // +0x04
    virtual void Unknown08();                  // +0x08
    virtual void Unknown0c();                  // +0x0c
    virtual bool IsPlaying();                  // +0x10
    virtual void Unknown14();                  // +0x14
    virtual void SetXform(XformMsg* msg);      // +0x18
    virtual void Unknown1c();                  // +0x1c
    virtual void GetXform(XformMsg* msg);      // +0x20
};
struct effect_ref {
    void* mpObject;                            // +0x00
    effect_ref* assign(void* object);          // 0x0099cab0
};
namespace nSPCreatureAnim {
struct creature_effect_s009a_69d0;
}
namespace nSPCreatureAnim {
struct creature_body_static_data_s009a_69d0 {
    unsigned char mUnknown0[0x138];
    checkerlib::vector_3_s009a_69d0 mFootstepExtent;      // +0x138
    unsigned char mUnknown144[0x150 - 0x144];
    unsigned char mFlags;                      // +0x150
    unsigned char mUnknown151[0x1f8 - 0x151];
    int mFootSoundId;                          // +0x1f8
};
}
namespace nSPCreatureAnim {
struct creature_body_instance_data_s009a_69d0 {
    creature_body_static_data_s009a_69d0* mpStaticData;   // +0x00
    unsigned char mUnknown4[0x10 - 0x04];
    checkerlib::vector_3_s009a_69d0 mCenter;              // +0x10
    unsigned char mUnknown1c[0x4c - 0x1c];
    float mAnimWeight;                         // +0x4c
    unsigned char mUnknown50[0x2bc - 0x50];
};
}
namespace nSPCreatureAnim {
class dynamics_foot_s009a_69d0 {
public:
    unsigned char mUnknown0[0x58];
    int mBodyIdx;                              // +0x58
    bool mFootDown;                            // +0x5c
    bool mEdgeTrigger;                         // +0x5d
    unsigned char mUnknown5e[0x108 - 0x5e];
};
}
namespace nSPCreatureAnim {
struct footstep_event_list {
    dynamics_foot_s009a_69d0* mpBegin;                    // +0x00
    dynamics_foot_s009a_69d0* mpEnd;                      // +0x04
};
}
namespace nSPCreatureAnim {
struct anim_data_15b8 {
    unsigned char mUnknown0[0x24];
    footstep_event_list mEvents;               // +0x24
    footstep_event_list* get_events();         // 0x00a09f50
    unsigned char mUnknown2c[0xa8 - 0x2c];
};
}
namespace nSPCreatureAnim {
struct creature_instance_data_s009a_69d0 {
    void* mpStaticData;                        // +0x00
    void* mpRoot;                              // +0x04
    unsigned char mUnknown08[0x18 - 0x08];
    checkerlib::vector_3_s009a_69d0 mPosition;            // +0x18
    unsigned char mUnknown24[0x3c - 0x24];
    float mQuatW;                              // +0x3c
    float mQuatX;                              // +0x40
    float mQuatY;                              // +0x44
    float mQuatZ;                              // +0x48
    unsigned char mUnknown4c[0x70 - 0x4c];
    float mScale;                              // +0x70
    unsigned char mUnknown74[0x260 - 0x74];
    bool mbField260;                           // +0x260
    bool mbFootstepsEnabled;                   // +0x261
    unsigned char mUnknown262[0x270 - 0x262];
    bool mbField270;                           // +0x270
    unsigned char mUnknown271[0x2ac - 0x271];
    uint32 mField2ac;                          // +0x2ac
    unsigned char* mpEventData;                // +0x2b0
    int mEventDataStride;                      // +0x2b4
    uint32* mpEventDataCount;                  // +0x2b8
    uint32 mEventDataCapacity;                 // +0x2bc
    unsigned char mUnknown2c0[0x2c4 - 0x2c0];
    unsigned char mSoundName[0x2d5 - 0x2c4];   // +0x2c4
    bool mbSecondFootstep;                     // +0x2d5
    unsigned char mUnknown2d6[0x2e4 - 0x2d6];
    creature_body_instance_data_s009a_69d0* mpBodies;     // +0x2e4
    creature_body_instance_data_s009a_69d0* mpBodiesEnd;  // +0x2e8
    unsigned char mUnknown2ec[0x15b8 - 0x2ec];
    anim_data_15b8 mAnimData;                  // +0x15b8
    checkerlib::vector_4_s009a_69d0 mFootstepBasis;       // +0x1660
    unsigned char mUnknown1670[0x17a0 - 0x1670];
    EapdHashTable mEffects;                    // +0x17a0
    void HitBody(uint32 bodyId, const checkerlib::vector_3_s009a_69d0& vec, uint32 a, bool b, float c); // 0x009bb680
    void SetStyleWeightForAllGroups(const char* group, int value, float weight);             // 0x009b7b70
    creature_effect_s009a_69d0* AddEffect(uint32 id, int a, int b);                                     // 0x009cb300
    int Release();                                                                            // 0x009c4cc0
};
}
namespace nSPCreatureAnim {
struct creature_effect_s009a_69d0 {
    uint32 key;                                        // +0x00
    uint32 id;                                         // +0x04
    uint32 bidx;                                       // +0x08
    checkerlib::vector_3_s009a_69d0 local_pos;                    // +0x0c
    // Retail's prelude before allow_dupes is 0xc shorter than the dev header's
    // matrix_3x3, so the retail record starts its flags at +0x30. This function
    // never touches the prelude.
    unsigned char mUnknown18[0x30 - 0x18];             // +0x18
    bool allow_dupes;                                  // +0x30
    bool event_info_valid;                             // +0x31
    unsigned char mPad32[2];                           // +0x32
    uint32 EventTypeAndFlags;                          // +0x34
    uint32 EventSourcePosFlags;                        // +0x38
    uint32 EventSourceRotFlags;                        // +0x3c
    uint32 EventSourceScaleFlags;                      // +0x40
    uint32 EventDestinationFlags;                      // +0x44
    uint32 EventData0I;                                // +0x48
    effect_ref source_pos_creature;                    // +0x4c
    effect_ref source_rot_creature;                    // +0x50
    effect_ref source_scale_creature;                  // +0x54
    uint32 source_pos_bidx;                            // +0x58
    uint32 source_rot_bidx;                            // +0x5c
    uint32 source_scale_bidx;                          // +0x60
    checkerlib::vector_3_s009a_69d0 source_pos_random_offset;     // +0x64
    int rot_relation;                                  // +0x70
    int scale_relation;                                // +0x74
    effect_ref destination_creature;                   // +0x78
    uint32 destination_bidx;                           // +0x7c
    checkerlib::vector_3_s009a_69d0 destination_pos_random_offset;// +0x80
    effect_ref effect;                                 // +0x8c
    effect_ref model;                                  // +0x90
    uint32 sound_id;                                   // +0x94
    checkerlib::vector_3_s009a_69d0 last_sound_pos;               // +0x98
    effect_ref unknown;                                // +0xa4
    void (*set_unknown_posrot)();                      // +0xa8
    void Init(IVisualEffect* effect, uint32 a, uint32 b);  // 0x009caa40
    void Init(uint32 soundId, uint32 a, uint32 b);         // 0x009caa90
    void RefreshWorldState();                              // 0x009c8900
};
}
bool EffectsSpawnThunk(void* manager, uint32 id, const float* pos, const float* mat,
                       IVisualEffect** outEffect);                                  // 0x009fc050
void AudioSetEvent1(IVisualEffect* event, float maxDistance);                        // 0x009fbd50
void AudioSetEvent5(IVisualEffect* event, const void* value);                        // 0x009fbd30
void AudioSetEvent9(IVisualEffect* event, const float* value);                       // 0x009fbcd0
void AudioSetEvent10(IVisualEffect* event, float value);                             // 0x009fbcf0
unsigned int PlaySound(const char* name, void* creature, int soundId, const float* pos,
                       char a, char b, float volume);                               // 0x009a5090
void QuaternionToMatrix(float* out, const float* quat);                             // 0x009a46a0
float* NormalizeVec3(float* out, const float* v, float* lenOut);                    // 0x009a49d0
void FUN_00e82690(int a, float b);                                                  // 0x00e82690
namespace nSPCreatureAnim {
uint32 GetEventDataAs32Bits(int a0, void* a1, int a2, int a3, void* creature,
                            uint32 index, float defaultValue, int a7);              // 0x009a5860
}
namespace nSPCreatureAnim {
float GetEventDataAsFloat(int a0, void* a1, int a2, void* p3,
                          uint32 index, float defaultValue, int a6);                // 0x009a59a0
}
namespace nSPCreatureAnim {
bool ContextFilterEventLocationData(uint32 a0, uint32 a1, const uint32* ids,
                                    uint32 a3, uint32 a4);                          // 0x009a4890
}
namespace nSPCreatureAnim {
bool ComputeEventLocationState(char randomize, int evData, uint32 flags, int p4,
                               void* owner, void* creature, uint32 boneIdx,
                               float* pos, float* pos2, void* outQuat, float* outScalar,
                               float* outVec, float* dirIn, float* dirIn2, int p15); // 0x009a59e0
}
struct IMessageServer {
    virtual void Unknown0();                   // +0x00
    virtual void Unknown4();                   // +0x04
    virtual void Unknown8();                   // +0x08
    virtual void Unknown0c();                  // +0x0c
    virtual void Unknown10();                  // +0x10
    virtual void PostMessage(uint32 id, const void* msg, int flags); // +0x14
};
IMessageServer* GetMessageServer();            // 0x0067dcc0
using nSPCreatureAnim::creature_body_instance_data_s009a_69d0;
using nSPCreatureAnim::creature_instance_data_s009a_69d0;
using nSPCreatureAnim::creature_effect_s009a_69d0;
using nSPCreatureAnim::GetEventDataAs32Bits;
using nSPCreatureAnim::GetEventDataAsFloat;
using nSPCreatureAnim::ContextFilterEventLocationData;
using nSPCreatureAnim::ComputeEventLocationState;
using nSPCreatureAnim::dynamics_foot_s009a_69d0;
struct creature_event_data {
    uint32 mEventType;          // +0x00  slot 0
    uint32 mLocFlagsPos;        // +0x04  slot 1
    uint32 mField08;            // +0x08  slot 2
    uint32 mField0c;            // +0x0c  slot 3
    uint32 mLocFlagsRot;        // +0x10  slot 4
    uint32 mField14;            // +0x14  slot 5
    uint32 mField18;            // +0x18  slot 6
    uint32 mLocFlagsScale;      // +0x1c  slot 7
    uint32 mField20;            // +0x20  slot 8
    uint32 mField24;            // +0x24  slot 9
    uint32 mLocFlagsDest;       // +0x28  slot 0xa
    uint32 mField2c;            // +0x2c  slot 0xb
    uint32 mField30;            // +0x30  slot 0xc
    uint32 mField34;            // +0x34  slot 0xd
    uint32 mEventId;            // +0x38  slot 0xe
    uint32 mEffectId;           // +0x3c  slot 0xf
    const char* mpName;         // +0x40  slot 0x10
    uint32 mEventValue;         // +0x44  slot 0x11
    uint32 mField48;            // +0x48  slot 0x12
    uint32 mField4c;            // +0x4c  slot 0x13
};
struct creature_data_event_record {
    uint32 mEffectId;           // +0x00
    uint32 mBoneIdx;            // +0x04
    uint32 mValue;              // +0x08
};
struct creature_event_message {
    uint32 mEffectId;           // +0x00
    const char* mpName;         // +0x04
    void* mpRoot;               // +0x08
    uint32 mBoneIdx;            // +0x0c
    uint32 mEventValue;         // +0x10
    uint32 mField14;            // +0x14
};
// ---- items of slice s009a69d0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void PlayFootstep(void* manager, creature_instance_data_s009a_69d0* creature, creature_body_instance_data_s009a_69d0* body, float volume);  // 0x009a6a00 (stays in the slice: not this object's)

// ---- items of slice s00a65f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol {
    uint32_t    mHash;    // +0x00
    const char* mpName;   // +0x04
};
}  // namespace EA::Audio::Eapd
}
}
struct NamedAllocator {
    void*       mpVtbl;   // +0x00
    int         mA;       // +0x04
    const char* mpName;   // +0x08
};
class FixedPool {
public:
    NamedAllocator mInitAllocator;       // +0x00
    NamedAllocator mOverflowAllocator;   // +0x0c
    uint32_t  mnNodeSize;                // +0x18
    void*     mpPoolBegin;               // +0x1c
    void*     mpPoolEnd;                 // +0x20
    void*     mpHead;                    // +0x24
    uint32_t  mnCurrentSize;             // +0x28
    uint32_t  mnPeakSize;                // +0x2c
    bool Init(uint32_t nodeSize, uint32_t count, void* a1, void* a2);   // 0xa53210
    ~FixedPool();                                                       // 0xa531b0
};
class FixedHashtableAllocator : public FixedPool {
public:
    uint32_t mnBucketCount;              // +0x30
    void*    mpBucketBuffer;             // +0x34
    bool InitTables(uint32_t a, uint32_t b, uint32_t c, uint32_t d); // 0xa669d0
    void DestroyAllocator();                                         // 0xa67d30
};
struct HashNode { uint32_t mKey; void* mValue; HashNode* mpNext; };
struct HashIter { HashNode* mpNode; HashNode** mpBucket; HashNode* mpEnd; };
struct HashFind { HashNode* mpNode; HashNode** mpBucket; };
class Hashtable {
public:
    uint32_t   mFunctors;                 // +0x00
    HashNode** mpBucketArray;             // +0x04
    uint32_t   mnBucketCount;             // +0x08
    uint32_t   mnElementCount;            // +0x0c
    float      mfMaxLoadFactor;           // +0x10
    uint32_t   mnGrowthFactor;            // +0x14
    uint32_t   mnNextResize;              // +0x18
    FixedHashtableAllocator mAlloc;       // +0x1c

    Hashtable* Construct(void* name);                                 // 0xa665f0
    void      Destruct();                                             // 0xa66550
    void      ClearBuckets(HashNode** arr, uint32_t n);               // 0xa660e0
    HashIter  erase(HashIter it);                                     // 0xa66cc0
    void      Rehash(uint32_t n);                                     // 0xa66b40
};
HashFind HashTableFind(Hashtable* self, const uint32_t* key);         // 0xa3b2c0
HashIter HashTableEqualRange(Hashtable* self, const uint32_t* key);   // 0x9a6dd0
class SymbolManager {
public:
    void*          mpVtbl;                   // +0x00
    NamedAllocator mAllocA;                  // +0x04
    NamedAllocator mAllocB;                  // +0x10
    char           pad1c[0x10];              // +0x1c
    Hashtable      mSymbols;                 // +0x2c
    Hashtable      mBindings;                // +0x80
    uint32_t     (__cdecl *mHashFunction)(const char*);  // +0xd4
    void* Hash(const char* s);                                   // 0xa66970 (free fn EapdHashString)
    uint32_t HashCall(uint32_t a);                               // 0xa669b0
    void  ClearClasses();                                        // 0xa66d60
    bool  FindSym(uint32_t key, EA::Audio::Eapd::t_symbol* out);                  // 0xa66de0
    bool  Unbind(uint32_t key, void* value);                     // 0xa66e30
    void* BindX(uint32_t key, uint32_t b);                       // 0xa66ec0
    void* FindByClass(uint32_t key, void* a2, void* a3);         // 0xa66f10
    void  SendBang(uint32_t key, uint32_t a2);                   // 0xa66f70
    void  SendFloat(uint32_t key, uint32_t a2, float f);         // 0xa66fd0
    void  SendSymbol(uint32_t key, void* a2, void* a3);          // 0xa67040
};
class EapdRec {
public:
    char     pad00[0x28];
    uint32_t m28;                        // +0x28
    char     pad2c[0x70 - 0x2c];
    uint32_t m70;                        // +0x70
    uint32_t m74;                        // +0x74
    char     pad78[0xc4 - 0x78];
    uint32_t mC4;                        // +0xc4
    uint32_t mC8;                        // +0xc8
    void GetC4(uint32_t* a, uint32_t* b, uint32_t* c);   // 0xa66c60
    void GetC8(uint32_t* a, uint32_t* b, uint32_t* c);   // 0xa66c90
};
class EapdSystemOverflow {
public:
    void*    mpVtbl;      // +0x00
    void*    mpAlloc;     // +0x04
    uint32_t mField08;    // +0x08
    uint32_t mField0c;    // +0x0c
    uint32_t mField10;    // +0x10
    uint32_t mField14;    // +0x14
    uint32_t mField18;    // +0x18
    void*    mpArena;     // +0x1c
    void*    mpLimit;     // +0x20
    void*    mpCursor;    // +0x24
    uint32_t mUsed;       // +0x28
    uint32_t mField2c;    // +0x2c

    ~EapdSystemOverflow();                                                  // 0xa66830
    bool  Init(uint32_t size, uint32_t a3, uint32_t a4);                    // 0xa66890
    void* Alloc(uint32_t n);                                                // 0xa66900
    void  Free(void* p);                                                    // 0xa66930
};
uint32_t EapdPrimeBelow(uint32_t n);                              // 0x921340
void  OutletBang(void* atom);                                     // 0xa49560
void  OutletFloat(void* atom, float f);                           // 0xa49570
void  OutletSymbol(void* atom, void* name);                       // 0xa49590
void  EapdClearBucketsRaw(Hashtable* self, HashNode** arr, uint32_t n);  // 0xa66bf0
// ---- items of slice s00a65f90 end

// ---- items of slice s00a670b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" uint32_t EapdRoundUpSize(uint32_t n);                               // 0x9213c0
namespace EA {
namespace Audio {
namespace Eapd {
inline bool operator==(const t_symbol& a, const t_symbol& b) { return a.mHash == b.mHash; }
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_atom {
    int a_type;
    union { float w_float; t_symbol w_symbol; } a_w;
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
typedef t_class* t_pd;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class {
    char pad00[0x1c];
    void*  c_methods;                                   // +0x1c
    int    c_nmethod;                                   // +0x20
    char   pad24[4];
    void (*c_bangmethod)(t_pd* x);                      // +0x28
    void (*c_floatmethod)(t_pd* x, float f);            // +0x2c
    void (*c_symbolmethod)(t_pd* x, t_symbol s);        // +0x30
    void (*c_listmethod)(t_pd* x, t_symbol s, int argc, t_atom* argv);  // +0x34
    void (*c_anymethod)(t_pd* x, t_symbol s, int argc, t_atom* argv);   // +0x38
};
}
}
}
extern "C" extern EA::Audio::Eapd::t_symbol gEmptySymbol_s00a6_70b0;       // 0x167589c
extern "C" extern EA::Audio::Eapd::t_symbol gFloatSymbol_s00a6_70b0;       // 0x16758c4
extern "C" extern EA::Audio::Eapd::t_symbol gSymbolSymbol_s00a6_70b0;      // 0x1675894
extern "C" extern EA::Audio::Eapd::t_symbol gBangSymbol_s00a6_70b0;        // 0x16758b4
extern "C" extern EA::Audio::Eapd::t_symbol gListSymbol_s00a6_70b0;        // 0x16758ac
extern "C" extern EA::Audio::Eapd::t_symbol gAnythingSymbol_s00a6_70b0;    // 0x16758cc
extern "C" extern EA::Audio::Eapd::t_symbol gHashXSymbol_s00a6_70b0;       // 0x16758bc
extern "C" extern EA::Audio::Eapd::t_symbol gHashNSymbol_s00a6_70b0;       // 0x16758a4
extern "C" void  pd_list_s00a6_70b0(EA::Audio::Eapd::t_pd* x, EA::Audio::Eapd::t_symbol s, int argc, EA::Audio::Eapd::t_atom* argv);         // 0xa495b0
extern "C" void  pd_typedmess_s00a6_70b0(EA::Audio::Eapd::t_pd* x, EA::Audio::Eapd::t_symbol s, int argc, EA::Audio::Eapd::t_atom* argv);    // 0xa48100
class SymbolManager_s00a6_70b0;
inline void* AllocatorAlloc(void* a, unsigned n)
{
    void** v = *(void***)a;
    return ((void* (__thiscall*)(void*, unsigned))v[2])(a, n);
}
inline void AllocatorFree(void* a, void* p)
{
    void** v = *(void***)a;
    ((void (__thiscall*)(void*, void*))v[3])(a, p);
}
struct KeyValue { uint32_t mKey; void* mValue; };
struct Iterator { HashNode* mpNode; HashNode** mpBucket; };
class FixedPool_s00a6_70b0 {
public:
    NamedAllocator mInitAllocator;       // +0x00
    NamedAllocator mOverflowAllocator;   // +0x0c
    uint32_t  mnNodeSize;                // +0x18
    void*     mpPoolBegin;               // +0x1c
    void*     mpPoolEnd;                 // +0x20
    void*     mpHead;                    // +0x24
    uint32_t  mnCurrentSize;             // +0x28
    uint32_t  mnPeakSize;                // +0x2c
    void Destroy();                      // 0xa531b0  (~FixedPool)
};
class FixedHashtableAllocator_s00a6_70b0 : public FixedPool_s00a6_70b0 {
public:
    uint32_t mnBucketCount;              // +0x30
    void*    mpBucketBuffer;             // +0x34
    bool Initialize(unsigned n, int a2, int a3);           // 0xa67d90
    bool InitTables(uint32_t a, uint32_t b, uint32_t c);   // 0xa669d0
    void DestroyAllocator();                               // 0xa67d30
};
class Hashtable_s00a6_70b0 {
public:
    uint32_t   mFunctors;                 // +0x00
    HashNode** mpBucketArray;             // +0x04
    uint32_t   mnBucketCount;             // +0x08
    uint32_t   mnElementCount;            // +0x0c
    float      mfMaxLoadFactor;           // +0x10
    uint32_t   mnGrowthFactor;            // +0x14
    uint32_t   mnNextResize;              // +0x18
    FixedHashtableAllocator_s00a6_70b0 mAlloc;       // +0x1c

    Hashtable_s00a6_70b0(const char* name);                                    // 0xa67770
    void  Destroy();                                               // 0xa672e0
    void  ClearBuckets(HashNode** arr, uint32_t n);                // 0xa66bf0
    void  Rehash(uint32_t n);                                      // 0xa66b40
    HashNode** AllocateBuckets(uint32_t n);                        // 0xa67ee0
    void  RehashTo(uint32_t n);                                    // 0xa67f60
    bool  Init(uint32_t a, uint32_t b, uint32_t c);                // 0xa67440
    Iterator find(const uint32_t& key);                            // 0x645ed0
    Iterator equal_range(const uint32_t& key);                     // 0x9a6dd0
    Iterator* DoInsertValue(Iterator* sret, const KeyValue* value, const uint32_t* key); // 0xa67370
};
class SymbolManager_s00a6_70b0 {
public:
    void*         mpVtbl;                    // +0x00
    NamedAllocator mAllocA;                  // +0x04
    NamedAllocator mAllocB;                  // +0x10
    char          pad1c[0x10];               // +0x1c
    Hashtable_s00a6_70b0     mSymbols;                  // +0x2c
    Hashtable_s00a6_70b0     mBindings;                 // +0x80
    uint32_t (*mHashFunction)(const char*);  // +0xd4

    SymbolManager_s00a6_70b0();

    // callees
    void  VguiBind(uint32_t a, uint32_t b, uint32_t c);                  // 0xa66e30
    void  BindX(uint32_t a, uint32_t b);                                 // 0xa66ec0
    EA::Audio::Eapd::t_pd* FindByClass(uint32_t a, uint32_t b, uint32_t c);               // 0xa66f10
    void  SendBang(uint32_t a, uint32_t b);                              // 0xa66f70
    void  SendFloat(uint32_t a, uint32_t b, float f);                    // 0xa66fd0
    void  SendSymbol(uint32_t a, uint32_t b, uint32_t c, uint32_t d);    // 0xa67040
    bool  InitBuffer(uint32_t a, uint32_t b, uint32_t c);                // 0xa66890
    bool  FindSym(uint32_t a, EA::Audio::Eapd::t_symbol* out);                            // 0xa66de0
    bool  ClearClasses();                                                // 0xa66d60

    // defined here
    void  BindingsListDispatch(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f);      // 0xa670b0
    void  BindingsTypedmessDispatch(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f); // 0xa67130
    bool  GetSymbolFromName(const char* name, EA::Audio::Eapd::t_symbol* out);            // 0xa67570
    bool  InsertSymbol(uint32_t hash, const char* name, EA::Audio::Eapd::t_symbol* out);  // 0xa674e0
    bool  Init(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t (*hashFn)(const char*)); // 0xa67670
};
SymbolManager_s00a6_70b0* GetSymbolManager();   // 0xa67cc0
// ---- items of slice s00a670b0 end

// @ 0x009a6dd0
EapdRange EapdHashTable::equal_range(const uint32& key)
{
    EapdHashNode** const buckets = this->mpBucketArray;
    EapdHashNode** const bucket = &buckets[key % this->mnBucketCount];
    EapdHashNode* node = *bucket;
    while (node != 0) {
        if (key == node->mKey)
            break;
        node = node->mpNext;
    }

    EapdRange result;
    if (node == 0) {
        _ReadWriteBarrier();
        EapdHashNode** const endBucket = &this->mpBucketArray[this->mnBucketCount];
        EapdHashNode* const endNode = *endBucket;
        result.first.mpNode = endNode;
        result.first.mpBucket = endBucket;
        result.second.mpNode = endNode;
        result.second.mpBucket = endBucket;
        return result;
    }

    EapdHashNode* next = node->mpNext;
    while (next != 0 && key == next->mKey)
        next = next->mpNext;

    EapdHashNode** nextBucket = bucket;
    if (next == 0) {
        nextBucket = bucket + 1;
        while (*nextBucket == 0)
            ++nextBucket;
        next = *nextBucket;
    }

    result.first.mpNode = node;
    result.first.mpBucket = bucket;
    result.second.mpNode = next;
    result.second.mpBucket = nextBucket;
    return result;
}

// @ 0x009a6e60
void __cdecl HandleEventType(void* param1, creature_instance_data_s009a_69d0* param2, creature_instance_data_s009a_69d0* param3, void* param4, void* param5, uint32 param6, uint32 param7, uint32 param8, const float* param9, const float* param10, const float* param11, float param12, const float* param13, int param14, int param15, creature_instance_data_s009a_69d0* param16, const uint32* param17, uint32 param18, uint32 param19, creature_event_data* param20, int param21)
{
    const uint32 eventType = param20->mEventType;
    const uint32 mode = eventType & 0x20007;

    // Modes above 0x20000: only exactly 0x20001 posts a message, the rest are ignored.
    if (mode > 0x20000) {
        if (mode != 0x20001)
            return;
        creature_event_message msg;
        msg.mEffectId = param20->mEffectId;
        msg.mpName = param20->mpName;
        msg.mpRoot = param3 != 0 ? param3->mpRoot : 0;
        msg.mBoneIdx = param6;
        msg.mEventValue = param20->mEventValue;
        msg.mField14 = param20->mField4c;
        if (GetMessageServer() != 0)
            GetMessageServer()->PostMessage(param20->mEffectId, &msg, 0);
        return;
    }

    if (mode == 0x20000) {
        if (param3 == 0)
            return;
        const uint32 v1 = GetEventDataAs32Bits((int)eventType, &param20->mField4c, 1, 0,
                                               param3, param6, 0.0f, param21);
        const uint32 v2 = GetEventDataAs32Bits((int)eventType, &param20->mEventValue, 0, 1,
                                               param3, param6, 0.0f, param21);
        param3->SetStyleWeightForAllGroups(param20->mpName, (int)v2, *(const float*)&v1);
        return;
    }

    switch (mode) {
    case 0: {
        // Sound event: create the sound handle and register it in the effect table.
        const uint32 sound = PlaySound(param20->mpName, param3, (int)param6, param9, 1,
                                       (char)((eventType >> 10) & 1), 0.0f);
        if (sound == 0)
            return;
        creature_effect_s009a_69d0* ev = param2->AddEffect(param19, 1, 0);
        ev->Init(sound, param6, param20->mEventId);
        ev->allow_dupes = true;
        ev->EventTypeAndFlags = eventType;
        ev->EventData0I = param20->mEventValue;
        ev->EventSourcePosFlags = param20->mLocFlagsPos;
        ev->EventSourceRotFlags = param20->mLocFlagsRot;
        ev->EventSourceScaleFlags = param20->mLocFlagsScale;
        ev->source_pos_creature.assign(param3);
        ev->source_rot_creature.assign(param4);
        ev->source_scale_creature.assign(param5);
        ev->source_scale_bidx = param8;
        ev->source_rot_bidx = param7;
        ev->source_pos_bidx = param6;
        ev->source_pos_random_offset.x = param13[0];
        ev->source_pos_random_offset.y = param13[1];
        ev->source_pos_random_offset.z = param13[2];
        ev->scale_relation = param15;
        ev->rot_relation = param14;
        ev->EventDestinationFlags = 0;
        creature_instance_data_s009a_69d0* oldDest =
            (creature_instance_data_s009a_69d0*)ev->destination_creature.mpObject;
        if (oldDest != 0) {
            ev->destination_creature.mpObject = 0;
            oldDest->Release();
        }
        ev->destination_bidx = 0;
        ev->destination_pos_random_offset.x = 0.0f;
        ev->destination_pos_random_offset.y = 0.0f;
        ev->destination_pos_random_offset.z = 0.0f;
        return;
    }

    case 1: {
        // Visual effect event: resolve each candidate location, spawn the effect and
        // register the fully populated effect record.
        float pos[3];
        float pos2[3];
        float quatOut[4];
        float scalar;
        float vec[3];

        const uint32 count = param18 != 0 ? param18 : 1;
        uint32 bodyId = 0xffffffff;
        for (uint32 i = 0; i < count; ++i) {
            if (param18 != 0) {
                if (!ContextFilterEventLocationData(param20->mLocFlagsDest, i, param17,
                                                    param2->mField2ac, param6))
                    continue;
                bodyId = param17[i];
                ComputeEventLocationState(1, (int)eventType, param20->mLocFlagsDest,
                                          (int)param20->mEventValue, param2, param16, bodyId,
                                          pos, pos2, quatOut, &scalar, vec, pos, pos2, param21);
            }

            float mat[9];
            QuaternionToMatrix(mat, param11);

            IVisualEffect* effect = 0;
            if (EffectsSpawnThunk(param1, param20->mEffectId, param9, mat, &effect)) {
                AudioSetEvent1(effect, param12);
                if ((eventType & 0x200000) != 0) {
                    XformMsg info;
                    effect->GetXform(&info);
                    ++info.mCount;
                    info.mScale = param12;
                    effect->SetXform(&info);
                }
                if (param3 != 0 && (eventType & 0x10000) != 0)
                    AudioSetEvent5(effect, &param3->mSoundName[0]);

                creature_effect_s009a_69d0* ev = param2->AddEffect(param19, 1, 0);
                ev->Init(effect, param6, param20->mEventId);
                ev->allow_dupes = true;
                ev->EventTypeAndFlags = eventType;
                ev->EventData0I = param20->mEventValue;
                ev->EventSourcePosFlags = param20->mLocFlagsPos;
                ev->EventSourceRotFlags = param20->mLocFlagsRot;
                ev->EventSourceScaleFlags = param20->mLocFlagsScale;
                ev->source_pos_creature.assign(param3);
                ev->source_rot_creature.assign(param4);
                ev->source_scale_creature.assign(param5);
                ev->source_scale_bidx = param8;
                ev->source_rot_bidx = param7;
                ev->source_pos_bidx = param6;
                ev->source_pos_random_offset.x = param13[0];
                ev->source_pos_random_offset.y = param13[1];
                ev->source_pos_random_offset.z = param13[2];
                ev->scale_relation = param15;
                ev->rot_relation = param14;
                if (param18 != 0) {
                    AudioSetEvent9(effect, pos);
                    AudioSetEvent10(effect, 1.0f);
                    ev->EventDestinationFlags = param20->mLocFlagsDest;
                    ev->destination_creature.assign(param16);
                    ev->destination_bidx = bodyId;
                    ev->destination_pos_random_offset.x = vec[0];
                    ev->destination_pos_random_offset.y = vec[1];
                    ev->destination_pos_random_offset.z = vec[2];
                } else {
                    ev->EventDestinationFlags = 0;
                    creature_instance_data_s009a_69d0* oldDest =
                        (creature_instance_data_s009a_69d0*)ev->destination_creature.mpObject;
                    if (oldDest != 0) {
                        ev->destination_creature.mpObject = 0;
                        oldDest->Release();
                    }
                    ev->destination_bidx = 0;
                    ev->destination_pos_random_offset.x = 0.0f;
                    ev->destination_pos_random_offset.y = 0.0f;
                    ev->destination_pos_random_offset.z = 0.0f;
                }
            }
            if (effect != 0)
                effect->Release();
        }
        return;
    }

    case 2: {
        // Append a (effect id, bone, value) record to the creature's data-event buffer.
        if (param3 == 0 || param3->mpEventDataCount == 0 || param3->mpEventData == 0)
            return;
        if (*param3->mpEventDataCount >= param3->mEventDataCapacity)
            return;
        creature_data_event_record* record = (creature_data_event_record*)
            (param3->mpEventData + param3->mEventDataStride * *param3->mpEventDataCount);
        record->mEffectId = param20->mEffectId;
        record->mBoneIdx = param6;
        record->mValue = param20->mEventValue;
        ++*param3->mpEventDataCount;
        return;
    }

    case 3: {
        // Hit-body event: apply the scaled event direction as a hit to each candidate body.
        if (param16 == 0)
            return;
        for (uint32 i = 0; i < param18; ++i) {
            const uint32 bodyId = param17[i];
            if (!ContextFilterEventLocationData(param20->mLocFlagsDest, i, param17,
                                                param2->mField2ac, param6))
                continue;
            float value = GetEventDataAsFloat((int)eventType, &param20->mEventValue, 0,
                                              param3, param6, g_01550aa8, param21);
            value *= g_01550aac;
            float dir[3];
            const float* n = NormalizeVec3(dir, param10, (float*)0);
            checkerlib::vector_3_s009a_69d0 hit;
            hit.x = value * n[0];
            hit.y = value * n[1];
            hit.z = value * n[2];
            param16->HitBody(bodyId, hit, 0, false, g_hitBodyScale);
        }
        return;
    }

    case 4: {
        // Refresh the named effect entries in the creature's effect table.
        EapdHashTable* table = &param2->mEffects;
        EapdIterator first;
        EapdIterator second;
        if ((eventType & 0x400000) != 0) {
            second.mpNode = table->mpBucketArray[table->mnBucketCount];
            second.mpBucket = &table->mpBucketArray[table->mnBucketCount];
            first = table->begin();
        } else {
            const uint32 key = param19;
            const EapdRange range = table->equal_range(key);
            first = range.first;
            second = range.second;
        }
        if (first.mpNode == table->mpBucketArray[table->mnBucketCount])
            return;
        while (first.mpNode != second.mpNode) {
            creature_effect_s009a_69d0* ev = (creature_effect_s009a_69d0*)first.mpNode->mpValue;
            if (ev->id == param20->mEventId)
                ev->RefreshWorldState();
            first.Advance();
        }
        return;
    }

    case 5: {
        // Update the stored event value of the named effect entries.
        EapdHashTable* table = &param2->mEffects;
        EapdIterator first;
        EapdIterator second;
        if ((eventType & 0x400000) != 0) {
            second.mpNode = table->mpBucketArray[table->mnBucketCount];
            second.mpBucket = &table->mpBucketArray[table->mnBucketCount];
            first = table->begin();
        } else {
            const uint32 key = param19;
            const EapdRange range = table->equal_range(key);
            first = range.first;
            second = range.second;
        }
        if (first.mpNode == table->mpBucketArray[table->mnBucketCount])
            return;
        while (first.mpNode != second.mpNode) {
            creature_effect_s009a_69d0* ev = (creature_effect_s009a_69d0*)first.mpNode->mpValue;
            if (ev->id == param20->mEventId)
                ev->EventData0I = param20->mEventValue;
            first.Advance();
        }
        return;
    }

    case 6: {
        // Raw float event forwarded to the caller-supplied handler.
        const float value = GetEventDataAsFloat((int)eventType, &param20->mEventValue, 0,
                                                param3, param6, 0.0f, param21);
        FUN_00e82690((int)param20->mEffectId, value);
        return;
    }

    case 7: {
        // Footstep event at the given body.
        if (param3 == 0)
            return;
        const uint32 bodyCount = (uint32)(param3->mpBodiesEnd - param3->mpBodies);
        if (param6 >= bodyCount)
            return;
        const float volume = GetEventDataAsFloat((int)eventType, &param20->mEventValue, 0,
                                                 param3, param6, 0.0f, param21);
        PlayFootstep(param1, param3, &param3->mpBodies[param6], volume);
        return;
    }

    default:
        return;
    }
}

// @ 0x009a7810
void FUN_009a7810(int param_1, int param_2, int param_3, int param_4, int* param_5, uint32_t param_6, int param_7, uint32_t* param_8, int param_9)
{
    LocData local_A, local_B, local_D;
    int local_1034 = 0;
    uint32_t local_102c;
    int local_1064;
    int local_1060;
    uint32_t local_1044 = 0, local_103c = 0, local_104c = 0;
    uint32_t local_1048, local_1050;
    char local_1066 = 0, local_1065 = 0, local_1068 = 0;
    char local_1067 = 0;
    float local_1058;
    uint32_t local_101c;
    uint32_t local_1040, local_1030, local_1038;
    uint32_t local_105c, local_1054, local_1053x;
    uint8_t local_1018[12];
    uint8_t local_100c[16];
    uint8_t local_1028[12];
    uint8_t local_ffc[12];

    local_A.count = -1; operator_new__(&local_A.items[0], 0, 0x3f8);
    local_102c = nSPCreatureAnim::ComputeEventLocationData(param_8[10], param_8 + 0xb, *param_5 + 0x88,
                                                           (uint32_t*)param_2, param_3, param_4,
                                                           &local_1034, &local_A.count, (uint8_t*)&local_1068);
    uint32_t uVar3 = param_8[1];
    if ((uVar3 != param_8[4]) || (param_8[2] != param_8[5]) || (param_8[3] != param_8[6])) {
        local_1064 = 1;
    } else {
        local_1064 = 0;
    }
    if ((uVar3 == param_8[7]) && (param_8[2] == param_8[8]) && (param_8[3] == param_8[9])) {
        local_1060 = 0;
    } else if ((param_8[4] != param_8[7]) || (param_8[5] != param_8[8]) || (param_8[6] != param_8[9])) {
        local_1060 = 2;
    } else {
        local_1060 = 1;
    }
    int iVar4 = local_1060;
    local_1044 = 0; local_103c = 0; local_104c = 0;
    local_1066 = 0; local_1065 = 0; local_1068 = 0;

    local_B.count = -1; operator_new__(&local_B.items[0], 0, 0x3f8);
    local_D.count = -1; operator_new__(&local_D.items[0], 0, 0x3f8);
    LocData local_C;
    local_C.count = -1; operator_new__(&local_C.items[0], 0, 0x3f8);

    uVar3 = nSPCreatureAnim::ComputeEventLocationData(uVar3, param_8 + 2, *param_5 + 0x88,
                                                      (uint32_t*)param_2, param_3, param_4,
                                                      (int*)&local_1044, &local_B.count, (uint8_t*)&local_1066);
    local_101c = uVar3;
    if (local_1064 == 0) {
        local_1048 = 1;
    } else {
        local_1048 = nSPCreatureAnim::ComputeEventLocationData(param_8[4], param_8 + 5, *param_5 + 0x88,
                                                               (uint32_t*)param_2, param_3, param_4,
                                                               (int*)&local_103c, &local_C.count, (uint8_t*)&local_1065);
    }
    if (iVar4 == 2) {
        local_1050 = nSPCreatureAnim::ComputeEventLocationData(param_8[7], param_8 + 8, *param_5 + 0x88,
                                                               (uint32_t*)param_2, param_3, param_4,
                                                               (int*)&local_104c, &local_D.count, (uint8_t*)&local_1068);
    } else {
        local_1050 = 1;
    }
    local_1058 = 1.0f;
    local_1040 = 0;
    if (uVar3 != 0) {
        do {
            local_105c = (uint32_t)((int*)&local_B.count)[local_1040];
            uVar3 = local_1040;
            if (local_1066 == 0) uVar3 = param_6;
            uint32_t uVar1 = param_8[1];
            char cVar2 = (char)nSPCreatureAnim::ContextFilterEventLocationData(
                             uVar1, uVar3, &local_B.count, *(uint32_t*)(param_2 + 0x2ac), local_105c);
            if (cVar2 != 0) {
                if (((*param_8 & 0x8000) == 0) || (local_1067 = 0, local_1064 == 0)) {
                    local_1067 = 1;
                }
                nSPCreatureAnim::ComputeEventLocationState(
                    1, *param_8, uVar1, param_8[0x11], param_2, local_1044, local_105c, local_1018,
                    (void*)(uint32_t)(-(uint32_t)(local_1067 != 0) & (uint32_t)local_1028),
                    (void*)(uint32_t)(~-(uint32_t)(local_1064 != 0) & (uint32_t)local_100c),
                    (void*)(uint32_t)(~-(uint32_t)(iVar4 != 0) & (uint32_t)&local_1058),
                    local_ffc, local_1018, local_1028, param_9);
                local_1030 = 0;
                if (local_1048 != 0) {
                    do {
                        if (local_1064 == 1) {
                            local_1054 = (uint32_t)((int*)&local_C.count)[local_1030];
                            uVar3 = local_1030;
                            if (local_1065 == 0) uVar3 = param_6;
                            uVar1 = param_8[4];
                            cVar2 = (char)nSPCreatureAnim::ContextFilterEventLocationData(
                                        uVar1, uVar3, &local_C.count, *(uint32_t*)(param_2 + 0x2ac), local_105c);
                            if (cVar2 != 0) {
                                nSPCreatureAnim::ComputeEventLocationState(
                                    1, *param_8, uVar1, param_8[0x11], param_2, local_103c, local_1054, 0,
                                    (void*)(uint32_t)(((local_1067 != 0) - 1) & (uint32_t)local_1028),
                                    local_100c,
                                    (void*)(uint32_t)(~-(uint32_t)(iVar4 != 1) & (uint32_t)&local_1058),
                                    0, local_1018, local_1028, param_9);
                                goto LAB_009a7c23;
                            }
                        } else {
                            local_1054 = local_105c;
LAB_009a7c23:
                            local_1038 = 0;
                            if (local_1050 != 0) {
                                do {
                                    uint32_t uVar5;
                                    if (iVar4 == 2) {
                                        uVar5 = (uint32_t)((int*)&local_D.count)[local_1038];
                                        uVar3 = local_1038;
                                        if (local_1068 == 0) uVar3 = param_6;
                                        uVar1 = param_8[7];
                                        cVar2 = (char)nSPCreatureAnim::ContextFilterEventLocationData(
                                                    uVar1, uVar3, &local_D.count,
                                                    *(uint32_t*)(param_2 + 0x2ac), local_105c);
                                        iVar4 = local_1060;
                                        if (cVar2 != 0) {
                                            nSPCreatureAnim::ComputeEventLocationState(
                                                1, *param_8, uVar1, param_8[0x11], param_2, local_104c,
                                                uVar5, 0, 0, 0, &local_1058, 0, local_1018, local_1028, param_9);
                                            iVar4 = local_1060;
                                            goto LAB_009a7cc7;
                                        }
                                    } else {
                                        uVar5 = local_1054;
                                        if (iVar4 != 1) uVar5 = local_105c;
LAB_009a7cc7:
                                        FUN_009a6e60(param_1, param_2, local_1044, local_103c, local_104c,
                                                     local_105c, local_1054, uVar5, local_1018, local_1028,
                                                     local_100c, (uint32_t)local_1058, local_ffc, local_1064,
                                                     iVar4, local_1034, &local_A.count, local_102c, param_7,
                                                     param_8, param_9);
                                    }
                                    local_1038 = local_1038 + 1;
                                } while (local_1038 < local_1050);
                            }
                        }
                        local_1030 = local_1030 + 1;
                    } while (local_1030 < local_1048);
                }
            }
            local_1040 = local_1040 + 1;
        } while (local_1040 < local_101c);
    }
}

// @ 0x009a7d90
void FUN_009a7d90(uint32_t* param_1, int param_2, int param_3, uint32_t* param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10, uint32_t param_11, float param_12, int param_13)
{
    bool bVar2 = false;
    for (;;) {
        if (param_2 == 0) return;
        if (((param_10 == 0) || ((*param_1 & 8) == 0)) &&
            (((*param_1 & 0x1000000) == 0) ||
             (FUN_0099c710(*param_4, param_1[0x14], param_1[0x15]) != 0))) {
            uint32_t uVar8 = *param_1;
            uint8_t bVar6 = 0;
            uint8_t bVar1 = 1;
            uint32_t uVar4 = 0x20007;
            while ((uVar8 != 0) && (uVar4 != 0)) {
                uint32_t uVar7 = (uVar4 - 1) & uVar4;
                uVar4 = uVar7 ^ uVar4;
                bVar6 = (uint8_t)(bVar6 | (uint8_t)(-(uint32_t)((uVar4 & uVar8) != 0) & bVar1));
                uVar8 = uVar8 & ~uVar4;
                bVar1 = (uint8_t)(bVar1 * 2);
                uVar4 = uVar7;
            }
            float eventTime = *(float*)&param_1[0x12];
            if ((param_12 < eventTime) || ((param_11 & (1u << (bVar6 & 0x1f))) != 0)) {
                uint32_t uVar9 = param_1[0xd];
                if (uVar9 != 0) {
                    if (uVar9 == param_4[0xaa]) {
                        bVar2 = true;
                    } else if ((uVar9 != 0xffffffff) || (param_4[0xaa] == 0) || bVar2) {
                        goto LAB_009a7ef7;
                    }
                }
                if ((*param_1 & 0x2000000) != 0) {
                    float fVar5 = (float)FUN_009a5860(*param_1, param_1 + 0x13, 1, 0, (void*)param_4,
                                                      0, 0x3f800000u, param_13);
                    double fVar9 = ((CppRandom*)0x166b4b8)->GenerateDouble();
                    if ((double)fVar5 < fVar9) goto LAB_009a7ef7;
                }
                FUN_009a7810(param_3, (int)param_4, param_5, param_6, (int*)param_7, param_8, param_9,
                             param_1, param_13);
            }
        }
LAB_009a7ef7:
        param_1 = param_1 + 0x18;
        param_2 = param_2 - 1;
    }
}

// @ 0x009a7f10
void FUN_009a7f10(int param_1, int param_2, int* param_3, int param_4, int param_5)
{
    uint64_t uVar10 = 1ull << (uint32_t)param_3[3];
    uint32_t uVar6 = (uint32_t)((param_3[0x33] - param_3[0x32]) >> 3);
    int iVar3 = (*(int*)(param_3[2] + 0x20) - *(int*)(param_3[2] + 0x1c)) >> 4;
    uint8_t local_400[1024];
    uint32_t local_424 = 0;
    if (uVar6 != 0) {
        do {
            uint32_t iVar1 = *(uint32_t*)(param_3[0x32] + 4 + local_424 * 8);
            uint32_t uVar8 = (uint32_t)*(uint16_t*)(param_3[0x32] + local_424 * 8);
            int iVar7 = 0;
            if (iVar3 != 0) {
                int local_428 = 0;
                int local_420 = iVar3;
                do {
                    uint32_t* puVar5 = (uint32_t*)(*(int*)(param_3[2] + 0x1c) + local_428);
                    if ((((*puVar5 & (uint32_t)uVar10) != 0) || ((puVar5[1] & (uint32_t)(uVar10 >> 0x20)) != 0)) &&
                        ((*(uint8_t*)((int)puVar5 + 0xf) & 4) == 0)) {
                        char cVar2 = (char)puVar5[3];
                        if (cVar2 == -1) cVar2 = 0;
                        uint32_t local_418;
                        if (*(uint8_t*)((int)puVar5 + 0xe) == 0xff) local_418 = 0xffffffff;
                        else local_418 = (uint32_t)*(uint8_t*)((int)puVar5 + 0xe);
                        if (uVar8 == (uint32_t)*(uint8_t*)((int)puVar5 + 0xd)) {
                            int* piVar9 = (int*)(uVar8 * 0x1f0 + param_3[5]);
                            int iVar4 = (int)FUN_0099d2b0((uint32_t)*piVar9, 0, -1);
                            iVar4 = *(int*)(iVar4 + 0xc) * (int)iVar1 + *(int*)(*piVar9 + 0xd8) + *(int*)(iVar4 + 8);
                            *(int*)(piVar9[0x77] + (int)iVar1 * 4) = param_3[0x30];
                            FUN_009a7d90((uint32_t*)((uint32_t)*(uint16_t*)(iVar4 + 8) * 0x60 + *(int*)(*param_3 + 0x140)),
                                         *(uint8_t*)(iVar4 + 10), param_1, (uint32_t*)param_2, cVar2, (int)local_418,
                                         (int)piVar9, iVar7, param_3[4], param_3[0x31], param_4, (float)param_5,
                                         (int)(size_t)&local_400[0]);
                            iVar7 = iVar7 + 1;
                        }
                    }
                    local_428 = local_428 + 0x10;
                    local_420 = local_420 - 1;
                } while (local_420 != 0);
            }
            local_424 = local_424 + 1;
        } while (local_424 < uVar6);
    }
    (void)local_400;
}

// @ 0x009a80e0
void FUN_009a80e0(int param_1)
{
    if (*(int**)(param_1 + 4) != 0) {
        uint32_t key = *(uint32_t*)(param_1 + 0x10);
        ht_pair_s009a7810 range = ht_table_s009a7810(param_1)->equal_range(key);
        ht_iter_s009a7810 it = range.first;
        if (it.mpNode !=
            ht_table_s009a7810(param_1)->mpBucketArray[ht_table_s009a7810(param_1)->mnBucketCount]) {
            ht_node_s009a7810* lastNode = range.last.mpNode;
            for (; it.mpNode != lastNode; ++it) {
                creature_mesh_instance_data* p = it.mpNode->mValue;
                if ((p->mFlags & 0x800020) == 0)
                    p->RefreshWorldState();
            }
        }
    }
}

// @ 0x00a66890
bool EapdSystemOverflow::Init(uint32_t size, uint32_t a3, uint32_t a4)
{
    if (mpArena) {
        void* a = &mpAlloc;
        ((void (__thiscall*)(void*, void*))(*(void***)a)[3])(a, mpArena);
        mpArena = 0;
    }
    mField08 = *(uint32_t*)(a3 + 4);
    mField14 = *(uint32_t*)(a4 + 4);
    void* p = ((void* (__thiscall*)(void*, uint32_t))(*(void***)&mpAlloc)[2])(&mpAlloc, size);
    mpArena = p;
    mpCursor = p;
    mpLimit = (char*)p + size;
    mUsed = 0;
    return p != 0;
}

// @ 0x00a669d0
bool FixedHashtableAllocator::InitTables(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    if (mpBucketBuffer) {
        void* v = mInitAllocator.mpVtbl;
        ((void (__thiscall*)(void*, void*))(*(void***)&mInitAllocator)[3])(&mInitAllocator, mpBucketBuffer);
        mpBucketBuffer = 0;
        (void)v;
    }
    float f = (float)a;
    if ((int)a < 0)
        f += 4294967296.0f;
    uint32_t nb = (uint32_t)(long long)(f * 1.3333334f);
    mnBucketCount = nb;
    if (nb < 3) {
        mnBucketCount = 3;
    } else {
        mnBucketCount = EapdPrimeBelow(nb) + 1;
    }
    if ((mnBucketCount << 2) == 0xc)
        return Init(0xc, a + 1, (void*)b, (void*)c);
    if (!Init(0xc, a, (void*)b, (void*)c))
        return false;
    void* p = ((void* (__thiscall*)(void*, uint32_t))(*(void***)&mInitAllocator)[2])(&mInitAllocator, mnBucketCount * 4);
    mpBucketBuffer = p;
    (void)d;
    return p != 0;
}

// @ 0x00a66b40
void Hashtable::Rehash(uint32_t n)
{
    HashNode** arr = (HashNode**)EapdPrimeBelow(n);
    for (uint32_t i = 0; i < mnBucketCount; ++i) {
        HashNode* node = mpBucketArray[i];
        while (node) {
            uint32_t key = node->mKey;
            mpBucketArray[i] = node->mpNext;
            node->mpNext = arr[key % n];
            arr[key % n] = node;
            node = mpBucketArray[i];
        }
    }
    HashNode* old = (HashNode*)mpBucketArray;
    if (mnBucketCount > 1 && old != (HashNode*)mAlloc.mpBucketBuffer) {
        --mAlloc.mnCurrentSize;
        if ((uint8_t*)old < (uint8_t*)mAlloc.mpPoolBegin ||
            (uint8_t*)old >= (uint8_t*)mAlloc.mpPoolEnd) {
            void* v = &mAlloc.mOverflowAllocator;
            ((void (__thiscall*)(void*, void*))(*(void***)v)[3])(v, old);
        } else {
            *(void**)old = mAlloc.mpHead;
            mAlloc.mpHead = old;
        }
    }
    mpBucketArray = arr;
    mnBucketCount = n;
}

// @ 0x00a66bf0
void EapdClearBucketsRaw(Hashtable* self, HashNode** arr, uint32_t n)
{
    for (uint32_t i = 0; i < n; ++i) {
        HashNode* node = arr[i];
        while (node) {
            HashNode* next = node->mpNext;
            if (node != (HashNode*)self->mAlloc.mpBucketBuffer) {
                --self->mAlloc.mnCurrentSize;
                if ((uint8_t*)node < (uint8_t*)self->mAlloc.mpPoolBegin ||
                    (uint8_t*)node >= (uint8_t*)self->mAlloc.mpPoolEnd) {
                    void* v = &self->mAlloc.mOverflowAllocator;
                    ((void (__thiscall*)(void*, void*))(*(void***)v)[3])(v, node);
                } else {
                    *(void**)node = self->mAlloc.mpHead;
                    self->mAlloc.mpHead = node;
                }
            }
            node = next;
        }
        arr[i] = 0;
    }
}

// @ 0x00a66c60
void EapdRec::GetC4(uint32_t* a, uint32_t* b, uint32_t* c)
{
    *a = mC4;
    *b = m70;
    *c = m28;
}

// @ 0x00a66c90
void EapdRec::GetC8(uint32_t* a, uint32_t* b, uint32_t* c)
{
    *a = mC8;
    *b = m74;
    *c = m28;
}

// @ 0x00a66cc0
HashIter Hashtable::erase(HashIter it)
{
    HashNode* p = it.mpEnd;
    HashNode* node = it.mpNode;
    HashNode** bucket = it.mpBucket;
    HashIter out;
    out.mpNode = node->mpNext;
    out.mpBucket = bucket;
    if (!out.mpNode) {
        do {
            ++out.mpBucket;
            out.mpNode = *out.mpBucket;
        } while (!out.mpNode);
    }
    HashNode* head = *bucket;
    if (head == node) {
        *bucket = head->mpNext;
    } else {
        HashNode* prev = head;
        while (prev->mpNext != node)
            prev = prev->mpNext;
        prev->mpNext = node->mpNext;
    }
    if (p != (HashNode*)mAlloc.mpBucketBuffer) {
        --mAlloc.mnCurrentSize;
        if ((uint8_t*)p >= (uint8_t*)mAlloc.mpPoolBegin && (uint8_t*)p < (uint8_t*)mAlloc.mpPoolEnd) {
            *(void**)p = mAlloc.mpHead;
            mAlloc.mpHead = p;
        } else {
            void* v = &mAlloc.mOverflowAllocator;
            ((void (__thiscall*)(void*, void*))(*(void***)v)[3])(v, p);
        }
    }
    --mnElementCount;
    return out;
}

// @ 0x00a66d60
void SymbolManager::ClearClasses()
{
    Hashtable& h = mSymbols;
    HashNode* node = *h.mpBucketArray;
    HashNode** bucket = h.mpBucketArray;
    if (!node) {
        bucket = h.mpBucketArray + 1;
        while (!*bucket)
            ++bucket;
        node = *bucket;
    }
    HashNode* end = h.mpBucketArray[h.mnBucketCount];
    for (; node != end; ) {
        mHashFunction((const char*)node->mValue);
        HashIter it;
        it.mpNode = node;
        it.mpBucket = bucket;
        it.mpEnd = node;
        HashIter r = h.erase(it);
        node = r.mpNode;
        bucket = r.mpBucket;
    }
}

// @ 0x00a66de0
bool SymbolManager::FindSym(uint32_t key, EA::Audio::Eapd::t_symbol* out)
{
    Hashtable* h = &mSymbols;
    bool found = false;
    HashFind t = HashTableFind(h, &key);
    if (h->mpBucketArray[h->mnBucketCount] != t.mpNode) {
        out->mpName = (const char*)t.mpNode->mValue;
        out->mHash = key;
        found = true;
    }
    return found;
}

// @ 0x00a66e30
bool SymbolManager::Unbind(uint32_t key, void* value)
{
    Hashtable& h = mBindings;
    HashIter it = HashTableEqualRange(&h, &key);
    while (it.mpNode != it.mpEnd) {
        if (it.mpNode->mValue == value) {
            HashIter dummy;
            dummy.mpNode = it.mpNode;
            dummy.mpBucket = it.mpBucket;
            dummy.mpEnd = it.mpNode;
            h.erase(dummy);
            return true;
        }
        it.mpNode = it.mpNode->mpNext;
        while (!it.mpNode)
            it.mpNode = *++it.mpBucket;
    }
    return false;
}

// @ 0x00a66ec0
void* SymbolManager::BindX(uint32_t key, uint32_t b)
{
    Hashtable& h = mBindings;
    HashIter it = HashTableEqualRange(&h, &key);
    if (it.mpNode == it.mpEnd)
        return 0;
    void* r = it.mpNode->mValue;
    if (it.mpNode->mpNext == 0) {
        while (!*++it.mpBucket)
            ;
    }
    (void)b;
    return r;
}

// @ 0x00a66f10
void* SymbolManager::FindByClass(uint32_t key, void* a2, void* a3)
{
    Hashtable& h = mBindings;
    HashIter t = HashTableEqualRange(&h, &key);
    HashNode*  node   = t.mpNode;
    HashNode** bucket = t.mpBucket;
    HashNode*  end    = t.mpEnd;
    void* found = 0;
    while (node != end) {
        void* val = node->mValue;
        HashNode* next = node->mpNext;
        if (*(void**)val == a3)
            found = val;
        node = next;
        while (!node)
            node = *++bucket;
    }
    (void)a2;
    return found;
}

// @ 0x00a66f70
void SymbolManager::SendBang(uint32_t key, uint32_t a2)
{
    Hashtable& h = mBindings;
    HashIter t = HashTableEqualRange(&h, &key);
    HashNode*  node   = t.mpNode;
    HashNode** bucket = t.mpBucket;
    HashNode*  end    = t.mpEnd;
    while (node != end) {
        OutletBang(node->mValue);
        node = node->mpNext;
        while (!node)
            node = *++bucket;
    }
    (void)a2;
}

// @ 0x00a66fd0
void SymbolManager::SendFloat(uint32_t key, uint32_t a2, float f)
{
    Hashtable& h = mBindings;
    HashIter t = HashTableEqualRange(&h, &key);
    HashNode*  node   = t.mpNode;
    HashNode** bucket = t.mpBucket;
    HashNode*  end    = t.mpEnd;
    while (node != end) {
        OutletFloat(node->mValue, f);
        node = node->mpNext;
        while (!node)
            node = *++bucket;
    }
    (void)a2;
}

// @ 0x00a67040
void SymbolManager::SendSymbol(uint32_t key, void* a2, void* a3)
{
    Hashtable& h = mBindings;
    HashIter t = HashTableEqualRange(&h, &key);
    HashNode*  node   = t.mpNode;
    HashNode** bucket = t.mpBucket;
    HashNode*  end    = t.mpEnd;
    while (node != end) {
        OutletSymbol(node->mValue, a2);
        node = node->mpNext;
        while (!node)
            node = *++bucket;
    }
    (void)a3;
}

// @ 0x00a670b0
void SymbolManager_s00a6_70b0::BindingsListDispatch(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f)
{
    EA::Audio::Eapd::t_symbol s;
    s.mHash = c;
    s.mpName = (const char*)d;
    Hashtable_s00a6_70b0* h = &mBindings;
    Iterator it = h->equal_range(a);
    HashNode** end = h->mpBucketArray + h->mnBucketCount;
    if (it.mpNode != *end) {
        do {
            pd_list_s00a6_70b0((EA::Audio::Eapd::t_pd*)it.mpNode->mValue, s, (int)e, (EA::Audio::Eapd::t_atom*)f);
            it.mpNode = it.mpNode->mpNext;
            while (!it.mpNode)
                it.mpNode = *++it.mpBucket;
        } while (it.mpNode != *end);
    }
}

// @ 0x00a67130
void SymbolManager_s00a6_70b0::BindingsTypedmessDispatch(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f)
{
    EA::Audio::Eapd::t_symbol s;
    s.mHash = c;
    s.mpName = (const char*)d;
    Hashtable_s00a6_70b0* h = &mBindings;
    Iterator it = h->equal_range(a);
    HashNode** end = h->mpBucketArray + h->mnBucketCount;
    if (it.mpNode != *end) {
        do {
            pd_typedmess_s00a6_70b0((EA::Audio::Eapd::t_pd*)it.mpNode->mValue, s, (int)e, (EA::Audio::Eapd::t_atom*)f);
            it.mpNode = it.mpNode->mpNext;
            while (!it.mpNode)
                it.mpNode = *++it.mpBucket;
        } while (it.mpNode != *end);
    }
}

// @ 0x00a671b0
void sys_vgui(uint32_t a, uint32_t b, uint32_t c)
{
    GetSymbolManager()->VguiBind(a, b, c);
}

// @ 0x00a671d0
void EapdBindRemove(uint32_t a, uint32_t b)
{
    GetSymbolManager()->BindX(a, b);
}

// @ 0x00a671f0
EA::Audio::Eapd::t_pd* pd_findbyclass(uint32_t a, uint32_t b, uint32_t c)
{
    return GetSymbolManager()->FindByClass(a, b, c);
}

// @ 0x00a67210
void pd_send_bang(uint32_t a, uint32_t b)
{
    GetSymbolManager()->SendBang(a, b);
}

// @ 0x00a67230
void pd_send_float(uint32_t a, uint32_t b, float f)
{
    GetSymbolManager()->SendFloat(a, b, f);
}

// @ 0x00a67250
void pd_send_symbol(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    GetSymbolManager()->SendSymbol(a, b, c, d);
}

// @ 0x00a67280
void pd_list_bindings(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f)
{
    GetSymbolManager()->BindingsListDispatch(a, b, c, d, e, f);
}

// @ 0x00a672b0
void pd_typedmess_bindings(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f)
{
    GetSymbolManager()->BindingsTypedmessDispatch(a, b, c, d, e, f);
}

// @ 0x00a672e0
void Hashtable_s00a6_70b0::Destroy()
{
    ClearBuckets(mpBucketArray, mnBucketCount);
    HashNode** b = mpBucketArray;
    mnElementCount = 0;
    if (mnBucketCount > 1 && b != (HashNode**)mAlloc.mpBucketBuffer) {
        --mAlloc.mnCurrentSize;
        if (b < (HashNode**)mAlloc.mpPoolBegin || b >= (HashNode**)mAlloc.mpPoolEnd) {
            AllocatorFree(&mAlloc.mOverflowAllocator, b);
        } else {
            *(void**)b = mAlloc.mpHead;
            mAlloc.mpHead = b;
        }
    }
    mAlloc.DestroyAllocator();
}

// @ 0x00a67370
Iterator* Hashtable_s00a6_70b0::DoInsertValue(Iterator* sret, const KeyValue* value, const uint32_t* key)
{
    // eastl::prime_rehash_policy::need_rehash (0x921440)
    struct RehashResult { bool mNeed; uint32_t mNewCount; };
    RehashResult rr;
    ((RehashResult* (__thiscall*)(void*, RehashResult*, uint32_t, uint32_t, uint32_t))
        (*(void***)((char*)this + 0x10))[0])((char*)this + 0x10, &rr, mnBucketCount, mnElementCount, 1);
    if (rr.mNeed)
        Rehash(rr.mNewCount);

    uint32_t h = *key;
    uint32_t bc = mnBucketCount;
    HashNode* node = (HashNode*)mAlloc.mpHead;
    if (node)
        mAlloc.mpHead = *(void**)node;
    else
        node = (HashNode*)AllocatorAlloc(&mAlloc.mOverflowAllocator, mAlloc.mnNodeSize);
    if (node) {
        ++mAlloc.mnCurrentSize;
        if (mAlloc.mnCurrentSize > mAlloc.mnPeakSize)
            mAlloc.mnPeakSize = mAlloc.mnCurrentSize;
        node->mKey = value->mKey;
        node->mValue = value->mValue;
    }
    node->mpNext = 0;
    uint32_t idx = h % bc;
    HashNode* head = mpBucketArray[idx];
    if (head) {
        HashNode* p = head;
        do {
            if (value->mKey == p->mKey) {
                node->mpNext = p->mpNext;
                p->mpNext = node;
                goto inserted;
            }
            p = p->mpNext;
        } while (p);
    }
    node->mpNext = head;
    mpBucketArray[idx] = node;
inserted:
    ++mnElementCount;
    sret->mpNode = node;
    sret->mpBucket = &mpBucketArray[idx];
    return sret;
}

// @ 0x00a67440
bool Hashtable_s00a6_70b0::Init(uint32_t a, uint32_t b, uint32_t c)
{
    bool r = mAlloc.InitTables(a, b, c);
    if (r) {
        Rehash(mAlloc.mnBucketCount - 1);
        mfMaxLoadFactor = 10000.0f;
        mnGrowthFactor = 2;
        mnNextResize = 0;
        uint32_t n = EapdRoundUpSize(mnElementCount);
        if (n > mnBucketCount)
            Rehash(n);
    }
    return r;
}

// @ 0x00a674e0
bool SymbolManager_s00a6_70b0::InsertSymbol(uint32_t hash, const char* name, EA::Audio::Eapd::t_symbol* out)
{
    int n = (int)strlen(name) + 1;
    char* copy = (char*)AllocatorAlloc(this, n);
    if (!copy)
        return false;
    char* dst = copy;
    const char* src = name;
    char ch;
    do {
        ch = *src;
        *dst = ch;
        ++dst;
        ++src;
    } while (ch);
    out->mHash = hash;
    out->mpName = copy;
    KeyValue kv;
    kv.mKey = hash;
    kv.mValue = copy;
    Iterator it;
    uint32_t key = hash & 0xffffff00u;
    mSymbols.DoInsertValue(&it, &kv, &key);
    return true;
}

// @ 0x00a67570
bool SymbolManager_s00a6_70b0::GetSymbolFromName(const char* name, EA::Audio::Eapd::t_symbol* out)
{
    uint32_t h = mHashFunction(name);
    Iterator it = mSymbols.find(h);
    if (mSymbols.mpBucketArray[mSymbols.mnBucketCount] != it.mpNode) {
        out->mHash = h;
        out->mpName = (const char*)it.mpNode->mValue;
        if (_stricmp(out->mpName, name) == 0)
            return true;
        return false;
    }
    return InsertSymbol(h, name, out);
}

// @ 0x00a675f0
EA::Audio::Eapd::t_symbol* gensym(EA::Audio::Eapd::t_symbol* out, const char* name)
{
    if (!GetSymbolManager()->GetSymbolFromName(name, out))
        *out = gEmptySymbol_s00a6_70b0;
    return out;
}

// @ 0x00a67620
bool pd_bind(void* x, EA::Audio::Eapd::t_symbol s)
{
    GetSymbolManager();
    KeyValue kv;
    kv.mKey = s.mHash;
    kv.mValue = x;
    Iterator it;
    uint32_t key = (uint32_t)x & 0xffffff00u;
    GetSymbolManager()->mBindings.DoInsertValue(&it, &kv, &key);
    return true;
}

// @ 0x00a67670
bool SymbolManager_s00a6_70b0::Init(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t (*hashFn)(const char*))
{
    if (hashFn)
        mHashFunction = hashFn;
    bool r = InitBuffer(c, d, e) & 1;
    r &= mSymbols.Init(b, d, e);
    r &= mBindings.Init(a, d, e);
    r &= GetSymbolFromName("float", &gFloatSymbol_s00a6_70b0);
    r &= GetSymbolFromName("symbol", &gSymbolSymbol_s00a6_70b0);
    r &= GetSymbolFromName("bang", &gBangSymbol_s00a6_70b0);
    r &= GetSymbolFromName("list", &gListSymbol_s00a6_70b0);
    r &= GetSymbolFromName("anything", &gAnythingSymbol_s00a6_70b0);
    r &= GetSymbolFromName("#N", &gHashNSymbol_s00a6_70b0);
    r &= GetSymbolFromName("#X", &gHashXSymbol_s00a6_70b0);
    r &= GetSymbolFromName("", &gEmptySymbol_s00a6_70b0);
    return r;
}
