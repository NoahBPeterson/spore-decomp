// s00b9bed0.cpp -- gold6 batch, worker 25
// Reconstructed from the annotated disassembly + Ghidra decompiles in
// work/match/scratch_s00b9bed0_cards.txt.  Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include <new>
#include <xmmintrin.h>

#define VF(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))

class TObj {
public:
    int*  mBegin;    // +0x00
    int*  mEnd;      // +0x04
    void* mArr;      // +0x08
    int   m0c;       // +0x0c
    int   m10;       // +0x10
    int   m14;       // +0x14
    int   m18;       // +0x18
    void* mRef1c;    // +0x1c
    void* mRef20;    // +0x20
    int   m24;       // +0x24
    int   m28;       // +0x28
    int   m2c;       // +0x2c
    void* mSub30;    // +0x30

    void FUN_00b9c250(void);        // 0xb9c250
    void FUN_00b9c5c0(void);        // 0xb9c5c0
    void F_1023030(int, int);       // 0x1023030  eastl vector dtor-ish (thiscall, 2 args)
    void F_b9a630(void);            // 0xb9a630
};

extern "C" int  __cdecl FUN_00b969a0(int, int, int);   // 0xb969a0
extern "C" void __cdecl FUN_00b9bb40(int);             // 0xb9bb40
extern "C" void __cdecl FUN_00f47380(void*);           // 0xf47380 operator_delete_array

// ===========================================================================
// 0x00b9c250 - shrink a vector<...> back by one 0x14-byte element and destroy it
// ===========================================================================
// @ 0x00b9c250
void TObj::FUN_00b9c250(void) {
    int iVar3 = (int)mBegin;
    int iVar1 = (int)mEnd;
    int uVar2 = FUN_00b969a0(iVar1, iVar1, iVar3);
    F_1023030(uVar2, (int)mEnd);
    mEnd = (int*)((int)mEnd + (-((iVar1 - iVar3) / 0x14)) * 0x14);
}

// ===========================================================================
// 0x00b9c5b0 - tail-call forwarder: fn(this->mSub30)
// ===========================================================================
// @ 0x00b9c5b0
void __cdecl FUN_00b9c5b0(TObj* p) {
    FUN_00b9bb40((int)p->mSub30);
}

// ===========================================================================
// 0x00b9c5c0 - release the two AutoRefCount members and free the +8 array
// ===========================================================================
// @ 0x00b9c5c0
void TObj::FUN_00b9c5c0(void) {
    F_b9a630();
    void* r20 = mRef20;
    if (r20 != 0) {
        unsigned* rc = (unsigned*)((char*)r20 + 4);
        unsigned c = rc[0] + -1;
        rc[0] = c;
        if (c == 0) {
            rc[0] = 1;
            ((void(__thiscall*)(void*, int))VF(r20, 0))(r20, 1);
        }
    }
    void* r1c = mRef1c;
    if (r1c != 0) {
        unsigned* rc = (unsigned*)((char*)r1c + 4);
        unsigned c = rc[0] + -1;
        rc[0] = c;
        if (c == 0) {
            rc[0] = 1;
            ((void(__thiscall*)(void*, int))VF(r1c, 0))(r1c, 1);
        }
    }
    void* a = mArr;
    if (a != 0 && *(int*)((char*)a - 4) != 0) {
        FUN_00f47380(a);
    }
}

// ===========================================================================
// Shared layouts and callee declarations for the remaining reconstructions.
// ===========================================================================

struct Vec3 { float x, y, z; };
struct Range { void** mpBegin; void** mpEnd; };
struct CharRange { char* mpBegin; char* mpEnd; };

// ---- SP::cGameNounManager::GetGameDataVector ------------=-----------------
typedef void (*GameDataFn)();
template<class T> struct PtrVec { T** mpBegin; T** mpEnd; };
template<class T> struct VecOut { char mPad0[4]; PtrVec<T> mVec; };

extern "C" void __cdecl FUN_00cd7d10();     // 0x00cd7d10
extern "C" void __cdecl FUN_00d3d420();     // 0x00d3d420
extern "C" void __cdecl FUN_00accbb0();     // 0x00accbb0
extern "C" void __cdecl FUN_00b1e500();     // 0x00b1e500
// Game-data type tags are pushed by the original as fixed image addresses.
#define kTribeTypeTag ((const void*)0x018c6d19)

struct cPlanetModel;
struct cSpawner;

struct cGameNounManager {
    VecOut<void>* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c,
                                    GameDataFn d, const void* tag);       // 0x00b21340
};
namespace SP { cGameNounManager* __cdecl NounManager(); }                 // 0x00b3d300
namespace SP { cPlanetModel* __cdecl PlanetModel(); }                     // 0x00b3d350

struct cPlanetModel {
    float* PickPoint(float* out);              // 0x00b81720
    bool   IsPointValid(const float* pos);     // 0x00b7e3e0
    int    GetContinent(const float* pos);     // 0x00b88590
};

// cArithmeticaProgram is 0x94 bytes (see match/slices/s007f1220).
struct cArithmeticaProgram {
    int mStorage[0x25];                        // 0x94 bytes
    void  Construct();                         // 0x007f1e60
    void  Reset();                             // 0x007f2500
    float GetVar(const char* name);            // 0x007f2590
    void  Destroy();                           // 0x007f1d90
};
extern "C" bool __cdecl LoadArithmeticaFile(void* a, void* b,
                                            cArithmeticaProgram* prog);   // 0x007f2240

struct cSpawnHandle {
    void SetPosition(const float* pos);        // 0x00980c20
};
struct cGameData {
    float* GetPos();                           // 0x006e64f0
};
struct cSpawner {
    int mPad0;
    Range* GetSpawnList();                     // 0x00c71010
    cSpawnHandle* CreateSpawn(int index);      // 0x00c71110
    int  CountSpawns();                        // 0x00c71120
    void RemoveSpawn(int index);               // 0x00c71140
};

extern "C" char __cdecl FUN_00b94420(void* self, float* pos, float r1,
                                      float r2, float r3);                // 0x00b94420
extern "C" bool __cdecl FUN_00b94670(void* self, float* pos, float r1,
                                      float r2, float r3, float r4,
                                      float r5);                          // 0x00b94670

extern const char kNumTribesNearWater[];      // 0x01465bc8
extern const char kMinDistToNeighborTribe[];  // 0x01465bac
extern const char kMaxDistToNeighborTribe[];  // 0x01465b90
extern const char kMaxTribeLocationSlope[];   // 0x01465b74
extern float g_1688890;                       // 0x01688890  Vec3 sentinel .x
extern float g_1688894;                       // 0x01688894  Vec3 sentinel .y
extern float g_1688898;                       // 0x01688898  Vec3 sentinel .z
extern const float kFloatMax;                 // 0x01465984  FLT_MAX

// ---- hash-table lookup helpers -------------------------------------------
struct Key8  { int m0; int m4; };
struct Pair8 { int m0; int m4; };

struct VecTemp {                              // eastl vector temp, 0x14 bytes
    void* mpBegin;                            // +0x00
    void* mpEnd;                              // +0x04
    void* mpCapacity;                         // +0x08
    void* mAllocName;                         // +0x0c
    void* mAllocPad;                          // +0x10
    void Assign(const VecTemp& src);          // 0x01011cc0
    void Destroy();                           // 0x00ae6970
};

struct StarTable {
    int  m00;                                 // +0x00
    int* mSlots04;                            // +0x04
    int  mIndex08;                            // +0x08
    void MakeKey(Key8* out, const int* src);                        // 0x00b95f70
    void FindRecord(const Key8* key, const Pair8* pair, int flag);  // 0x00b98dd0
    int  Find(const int* src);
};

// ---- simulator vector element types -------------------------------------
struct Vec20B {                               // eastl vector member, 0x14 bytes
    void* mpBegin;                            // +0x00
    void* mpEnd;                              // +0x04
    void* mpCapacity;                         // +0x08
    void* mAllocName;                         // +0x0c
    void* mAllocPad;                          // +0x10
    Vec20B(const Vec20B& src);                // 0x00473460
    Vec20B& operator=(const Vec20B& src);     // 0x00473500
};
struct Elem18 {                               // 0x18 bytes
    float  m00;                               // +0x00
    Vec20B mV04;                              // +0x04
};

struct Sub1c {                                // 0x1c bytes
    int m[7];
    void AssignFrom(const Sub1c* src);        // 0x00b962d0
};
struct Elem34 {                               // 0x34 bytes
    int   m00;                                // +0x00
    int   m04;                                // +0x04
    int   m08;                                // +0x08
    float m0c;                                // +0x0c
    unsigned char m10;                        // +0x10
    char  mPad11[3];                          // +0x11
    int   m14;                                // +0x14
    Sub1c mSub18;                             // +0x18
    void CopyConstructFrom(const Elem34* src);  // 0x00b97240
};

extern char gAllocator13ebb38;                // 0x013ebb38  EA allocator object
extern const char kSimulatorName[];           // 0x013f09b4  "Simulator"
extern const char kProcLevelGenName[];        // 0x01465be0  "Simulator/ProcLevelGen"

void* __cdecl operator_new(unsigned size, const char* name, int a, int b,
                           const void* allocator, int line);            // 0x00f473a0

extern "C" Elem18* __cdecl FUN_00b97500(Elem18*, Elem18*, Elem18*);     // 0x00b97500
extern "C" Elem18* __cdecl FUN_00b96900(Elem18*, Elem18*, Elem18*);     // 0x00b96900
extern "C" Elem18* __cdecl FUN_00b93d80(Elem18*, Elem18*, Elem18*);     // 0x00b93d80
extern "C" Elem34* __cdecl FUN_00b975a0(Elem34*, Elem34*, Elem34*);     // 0x00b975a0
extern "C" Elem34* __cdecl FUN_00b97460(Elem34*, Elem34*, Elem34*);     // 0x00b97460
extern "C" Elem34* __cdecl FUN_00b96940(Elem34*, Elem34*, Elem34*);     // 0x00b96940

struct Vec18 {
    Elem18* mBegin;                           // +0x00
    Elem18* mEnd;                             // +0x04
    Elem18* mCapacity;                        // +0x08
    void Insert(Elem18* pos, const Elem18* val);
};
struct Vec34 {
    Elem34* mBegin;                           // +0x00
    Elem34* mEnd;                             // +0x04
    Elem34* mCapacity;                        // +0x08
    void Insert(Elem34* pos, const Elem34* val);
};

// ---- clue / proc-level-gen object ----------------------------------------
struct Elem12 { int m00; int m04; float m08; };

struct Container14 {                          // 0x14-byte owned container at clue+8
    int m00, m04, m08, m0c, m10;
    void Init(int count);                     // 0x00d01790
};

struct GenRecord {                            // ref-counted record
    void** mVtable;                           // +0x00
    int    mRefCount;                         // +0x04
    int    mSize;                             // +0x08
    int    m0c;                               // +0x0c
    int    mValue10;                          // +0x10
};

struct GenParams {
    int m00;                                  // +0x00
    int m04;                                  // +0x04
    GenRecord* mA08;                          // +0x08
    GenRecord* mB0c;                          // +0x0c
    int m10, m14, m18, m1c, m20, m24, m28, m2c, m30;
    float m34;                                // +0x34
    float m38;                                // +0x38
    float m3c;                                // +0x3c
};

struct cDirectPropertyList {
    int GetIntProperty(unsigned id);          // 0x006a2660
};
extern cDirectPropertyList* g_pAppProperties; // 0x015fd918

extern "C" void __cdecl FUN_00b90720();                               // 0x00b90720
extern "C" void __stdcall FUN_00401930(void* ptr, unsigned stride,
                                       unsigned count, void* ctor);   // 0x00401930

extern const int   kMaxClueCount;             // 0x0146596c  = 128
extern const float kNegOne;                   // 0x013eb1bc  = -1.0f
extern const float kI16Scale;                 // 0x01449540  = 32767.0f

struct Clue {
    int  mType00;                             // +0x00
    unsigned char mFlag04;                    // +0x04
    char mPad05[3];                           // +0x05
    Container14 mC08;                         // +0x08
    GenRecord* mRef1c;                        // +0x1c
    GenRecord* mRef20;                        // +0x20
    int    m24;                               // +0x24
    float  m28;                               // +0x28
    int    m2c;                               // +0x2c
    int    m30;                               // +0x30
    Elem12* m34;                              // +0x34
    int    m38;                               // +0x38
    int    m3c;                               // +0x3c
    int    m40;                               // +0x40
    float  m44;                               // +0x44
    int    m48;                               // +0x48
    float  m4c;                               // +0x4c
    int    m50;                               // +0x50
    unsigned char* mProc54;                   // +0x54

    void Reset();                             // 0x00b9a630
    void Read(GenParams* src, int count, float value);
};

// ---- prop placement helpers ---------------------------------------------
extern "C" int  __cdecl FUN_00b3d440();                               // 0x00b3d440
extern "C" bool __cdecl GetPropertyAsUint32Array(int list, int prop,
                                                 int* count,
                                                 unsigned** out);     // 0x006a0840
extern "C" void __cdecl PlaceSpawnDefinitionsOnPlanet(float* pos,
                                                      unsigned* ids,
                                                      int count, int a,
                                                      int b);         // 0x00b9b090
extern "C" void __cdecl PlaceArchetypeSubSpawns(float* pos,
                                                unsigned* ids,
                                                int count, int a);    // 0x00b9aa10

// ===========================================================================
// 0x00b9bed0 - place tribe spawn points, then drop the ones left at the
// world sentinel position.
// ===========================================================================
// @ 0x00b9bed0
void __cdecl FUN_00b9bed0(void* arg) {
    cGameNounManager* nouns = SP::NounManager();                      // 0xb3d300
    if (nouns == 0) return;
    VecOut<void>* data = nouns->GetGameDataVector(
        &FUN_00cd7d10, &FUN_00d3d420, &FUN_00accbb0, &FUN_00b1e500,
        kTribeTypeTag);                                              // 0xb21340
    int nounCount = (int)(data->mVec.mpEnd - data->mVec.mpBegin);
    cPlanetModel* model = SP::PlanetModel();                          // 0xb3d350
    if (model == 0) return;

    cArithmeticaProgram prog;
    prog.Construct();                                                 // 0x7f1e60
    LoadArithmeticaFile((void*)0xa1ed6e3c, (void*)0x24a4f5a, &prog);   // 0x7f2240
    prog.Reset();                                                     // 0x7f2500
    float numTribes = prog.GetVar(kNumTribesNearWater);               // 0x7f2590
    float minDist   = prog.GetVar(kMinDistToNeighborTribe);
    float maxDist   = prog.GetVar(kMaxDistToNeighborTribe);
    float maxSlope  = prog.GetVar(kMaxTribeLocationSlope);

    cSpawner* spawner = (cSpawner*)arg;
    Range* list = spawner->GetSpawnList();                            // 0xc71010
    void** it = list->mpBegin;
    if (nounCount > 0) ++it;
    if (it != list->mpEnd) {
        do {
            Vec3 v;
            v.x = g_1688890; v.y = g_1688894; v.z = g_1688898;
            int index = (int)(it - list->mpBegin);
            bool found = false;
            for (int trial = 0; trial < 500; trial++) {
                if (found) break;
                float out[3];
                float* p = model->PickPoint(out);                     // 0xb81720
                v.x = p[0]; v.y = p[1]; v.z = p[2];
                bool valid = model->IsPointValid(&v.x);               // 0xb7e3e0
                if (numTribes > (float)index) {
                    if (!valid) { found = false; }
                    else {
                        found = FUN_00b94420(arg, &v.x, kFloatMax,
                                             minDist, maxSlope) != 0;  // 0xb94420
                    }
                } else {
                    if (!valid) { found = false; }
                    else {
                        found = FUN_00b94670(arg, &v.x, kFloatMax,
                                             kFloatMax, minDist, maxDist,
                                             maxSlope);                // 0xb94670
                    }
                }
            }
            if (found) {
                cSpawnHandle* h = spawner->CreateSpawn(index);        // 0xc71110
                h->SetPosition(&v.x);                                 // 0x980c20
            }
            ++it;
        } while (it != list->mpEnd);
    }

    int i = 0;
    int n = spawner->CountSpawns();                                   // 0xc71120
    if (n > 0) {
        do {
            cGameData* d = (cGameData*)list->mpBegin[i];
            float* p = d->GetPos();                                   // 0x6e64f0
            if (p[0] == g_1688890 && p[1] == g_1688894 &&
                p[2] == g_1688898) {
                spawner->RemoveSpawn(i);                              // 0xc71140
            } else {
                ++i;
            }
            n = spawner->CountSpawns();
        } while (i < n);
    }
    prog.Destroy();                                                   // 0x7f1d90
}

// ===========================================================================
// 0x00b9c180 - hash lookup that builds a key, and on a bucket hit runs the
// insert path with two empty inline-buffer temporaries.
// ===========================================================================
// @ 0x00b9c180
int StarTable::Find(const int* src) {
    Key8 key;
    MakeKey(&key, src);                                               // 0xb95f70
    if (key.m0 == mSlots04[mIndex08]) {
        // Two empty vectors with 8-pointer inline buffers.  The dword just
        // below each buffer is the allocator's "heap block" tag; the retail
        // destructor only frees the buffer when it is non-zero, so it must be
        // zero here (the original zeroes both slots explicitly).
        struct InlineBuf8 { int mHead; void* mVec[8]; };
        InlineBuf8 sb;
        InlineBuf8 sa;
        sb.mHead = 0;
        sa.mHead = 0;
        void* bufB = sb.mVec;
        void* bufA = sa.mVec;
        VecTemp vb;
        VecTemp va;
        vb.mpBegin = bufB; vb.mpEnd = bufB; vb.mpCapacity = sb.mVec + 8;
        vb.mAllocName = 0; vb.mAllocPad = 0;
        va.mpBegin = bufA; va.mpEnd = bufA; va.mpCapacity = sa.mVec + 8;
        va.mAllocName = 0; va.mAllocPad = 0;
        vb.Assign(va);                                                // 0x1011cc0
        Pair8 pair;
        pair.m0 = src[0];
        pair.m4 = src[1];
        key.m0 &= 0xffffff00;
        FindRecord(&key, &pair, key.m0);                              // 0xb98dd0
        vb.Destroy();                                                 // 0xae6970
        va.Destroy();
    }
    return key.m0 + 8;
}

// ===========================================================================
// 0x00b9c2f0 - growable vector insert, 0x18-byte elements.
// ===========================================================================
// @ 0x00b9c2f0
void Vec18::Insert(Elem18* pos, const Elem18* val) {
    if (mEnd != mCapacity) {
        if (pos <= val && val < mEnd) ++val;
        if (mEnd != 0) {
            Elem18* prev = mEnd - 1;
            mEnd->m00 = prev->m00;
            new (&mEnd->mV04) Vec20B(prev->mV04);                     // 0x473460
        }
        FUN_00b97500(pos, mEnd - 1, mEnd);                            // 0xb97500
        pos->m00 = val->m00;
        pos->mV04 = val->mV04;                                        // 0x473500
        ++mEnd;
        return;
    }
    int n = (int)(mEnd - mBegin);
    int newCap = (n == 0) ? 1 : n * 2;
    Elem18* buf = (Elem18*)operator_new((unsigned)(newCap * 0x18),
                                        kSimulatorName, 0, 0,
                                        &gAllocator13ebb38, 0xd1);    // 0xf473a0
    Elem18* p = FUN_00b96900(mBegin, pos, buf);                       // 0xb96900
    FUN_00b93d80(mBegin, pos, buf);                                   // 0xb93d80
    if (p != 0) {
        p->m00 = val->m00;
        new (&p->mV04) Vec20B(val->mV04);                             // 0x473460
    }
    Elem18* newEnd = FUN_00b96900(pos, mEnd, p + 1);                  // 0xb96900
    FUN_00b93d80(pos, mEnd, p + 1);                                   // 0xb93d80
    if (mBegin != 0 && *(int*)((char*)mBegin - 4) != 0) {
        FUN_00f47380(mBegin);                                         // 0xf47380
    }
    mEnd = newEnd;
    mBegin = buf;
    mCapacity = buf + newCap;
}

// ===========================================================================
// 0x00b9c450 - growable vector insert, 0x34-byte elements.
// ===========================================================================
// @ 0x00b9c450
void Vec34::Insert(Elem34* pos, const Elem34* val) {
    if (mEnd != mCapacity) {
        if (pos <= val && val < mEnd) {
            val = (const Elem34*)((const char*)val + 0x34);
        }
        if (mEnd != 0) {
            mEnd->CopyConstructFrom(mEnd - 1);                        // 0xb97240
        }
        FUN_00b975a0(pos, mEnd - 1, mEnd);                            // 0xb975a0
        pos->m00 = val->m00;
        pos->m04 = val->m04;
        pos->m08 = val->m08;
        pos->m0c = val->m0c;
        pos->m10 = val->m10;
        pos->m14 = val->m14;
        pos->mSub18.AssignFrom(&val->mSub18);                         // 0xb962d0
        ++mEnd;
        return;
    }
    int n = (int)(mEnd - mBegin);
    int newCap = (n == 0) ? 1 : n * 2;
    Elem34* buf = (Elem34*)operator_new((unsigned)(newCap * 0x34),
                                        kSimulatorName, 0, 0,
                                        &gAllocator13ebb38, 0xd1);    // 0xf473a0
    Elem34* p = FUN_00b97460(mBegin, pos, buf);                       // 0xb97460
    FUN_00b96940(mBegin, pos, buf);                                   // 0xb96940
    if (p != 0) {
        p->CopyConstructFrom(val);                                    // 0xb97240
    }
    Elem34* newEnd = FUN_00b97460(pos, mEnd, p + 1);                  // 0xb97460
    FUN_00b96940(pos, mEnd, p + 1);                                   // 0xb96940
    if (mBegin != 0 && *(int*)((char*)mBegin - 4) != 0) {
        FUN_00f47380(mBegin);                                         // 0xf47380
    }
    mEnd = newEnd;
    mBegin = buf;
    mCapacity = buf + newCap;
}

// ===========================================================================
// 0x00b9c630 - reset a clue and fill it from generation parameters.
// ===========================================================================
// @ 0x00b9c630
void Clue::Read(GenParams* src, int count, float value) {
    Reset();                                                          // 0xb9a630
    mFlag04 = 1;
    mType00 = g_pAppProperties->GetIntProperty(0x4f421d6);             // 0x6a2660
    if (mType00 < 0 || mType00 > 2) mType00 = 0;

    mC08.Init(0xc000);                                                // 0xd01790

    unsigned char* proc = (unsigned char*)operator_new(
        0x120000, kProcLevelGenName, 0, 0, 0, 0);                     // 0xf473a0
    if (proc != 0) {
        FUN_00401930(proc, 0x18, 0xc000, (void*)&FUN_00b90720);       // 0x401930
    }
    mProc54 = proc;
    for (int i = 0; i < 0xc000; i++) {
        mProc54[i * 0x18] = 0;
    }

    m24 = (count < 0x80) ? count : kMaxClueCount;
    m28 = value;

    float scaled = src->m3c * kI16Scale;
    int biased = _mm_cvt_ss2si(*(__m128*)&scaled) + 0x8000;
    m40 = (biased > 0) ? (int)(unsigned short)biased : 0;
    m44 = src->m38;
    m4c = src->m34;

    GenRecord* recA = src->mA08;
    int size = recA->mSize;
    m38 = size;
    m3c = size * size;
    m48 = (int)(((unsigned)size / (unsigned)(2 * count)) *
                (unsigned)(size + 1));

    if (recA != mRef1c) {
        recA->mRefCount += 1;
        GenRecord* old = mRef1c;
        mRef1c = recA;
        if (old != 0) {
            int c = old->mRefCount - 1;
            old->mRefCount = c;
            if (c == 0) {
                old->mRefCount = 1;
                ((void(__thiscall*)(GenRecord*, int))
                    old->mVtable[0])(old, 1);
            }
        }
    }
    GenRecord* recB = src->mB0c;
    if (recB != mRef20) {
        if (recB != 0) recB->mRefCount += 1;
        GenRecord* old = mRef20;
        mRef20 = recB;
        if (old != 0) {
            int c = old->mRefCount - 1;
            old->mRefCount = c;
            if (c == 0) {
                old->mRefCount = 1;
                ((void(__thiscall*)(GenRecord*, int))
                    old->mVtable[0])(old, 1);
            }
        }
    }
    m2c = mRef1c->mValue10;
    m30 = mRef20->mValue10;

    int total = count * count * 6;
    unsigned bytes = (unsigned)total * 12u;
    if (bytes / 12u != (unsigned)total) bytes = 0xffffffffu;
    Elem12* arr = (Elem12*)operator_new(bytes, kProcLevelGenName,
                                        0, 0, 0, 0);                  // 0xf473a0
    if (arr != 0) {
        for (int i = 0; i < total; i++) {
            arr[i].m00 = 0;
            arr[i].m04 = 0;
            arr[i].m08 = kNegOne;
        }
    }
    m34 = arr;
}

// ===========================================================================
// 0x00b9c830 - place spawn definitions / archetype sub-spawns on world
// elements near `pos` that lie on the same continent.
// ===========================================================================
// @ 0x00b9c830
void __cdecl FUN_00b9c830(int propList, float* pos, float maxDistSq,
                          int propSpawns, int propArchetypes) {
    cPlanetModel* model = SP::PlanetModel();                          // 0xb3d350
    int base = FUN_00b3d440();                                        // 0xb3d440
    CharRange* world = (CharRange*)(base + 0x1e5f0);
    int continent = model->GetContinent(pos);                         // 0xb88590

    int countA = 0;
    unsigned* idsA = 0;
    if (GetPropertyAsUint32Array(propList, propSpawns, &countA, &idsA) &&
        countA > 0) {                                                 // 0x6a0840
        for (char* it = world->mpBegin; it != world->mpEnd; it += 0x19a8) {
            float* p = (float*)(it + 8);
            float dx = pos[0] - p[0];
            float dz = pos[2] - p[2];
            float dy = pos[1] - p[1];
            float d = dx * dx + dz * dz + dy * dy;
            if (maxDistSq == kFloatMax || d < maxDistSq) {
                if (model->GetContinent(p) == continent) {            // 0xb88590
                    PlaceSpawnDefinitionsOnPlanet(p, idsA, countA, 0, 1); // 0xb9b090
                }
            }
        }
    }

    int countB = 0;
    unsigned* idsB = 0;
    if (GetPropertyAsUint32Array(propList, propArchetypes,
                                 &countB, &idsB) &&
        countB > 0) {                                                 // 0x6a0840
        for (int k = 0; k < countB; k++) {
            int countC = 0;
            unsigned* idsC = 0;
            if (GetPropertyAsUint32Array(propList, (int)idsB[k],
                                         &countC, &idsC) &&
                countC > 0) {                                         // 0x6a0840
                for (char* it = world->mpBegin; it != world->mpEnd;
                     it += 0x19a8) {
                    float* p = (float*)(it + 8);
                    float dz = pos[2] - p[2];
                    float dy = pos[1] - p[1];
                    float dx = pos[0] - p[0];
                    float d = dz * dz + dy * dy + dx * dx;
                    if (maxDistSq == kFloatMax || d < maxDistSq) {
                        if (model->GetContinent(p) == continent) {    // 0xb88590
                            PlaceArchetypeSubSpawns(p, idsC, countC, 0); // 0xb9aa10
                        }
                    }
                }
            }
        }
    }
}