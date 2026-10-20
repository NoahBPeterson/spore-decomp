// match/slices/s00a7a580/s00a7a580.cpp
// Object file: Swarm/Path.obj.  flags /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

struct Vector3 { float x, y, z; };

inline Vector3 operator-(const Vector3& a, const Vector3& b) {
    Vector3 r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; return r;
}

inline Vector3 operator+(const Vector3& a, const Vector3& b) {
    Vector3 r; r.x = a.x + b.x; r.y = a.y + b.y; r.z = a.z + b.z; return r;
}

extern "C" void* memcpy(void*, const void*, unsigned int);
extern "C" double sqrt(double);

// unnamed retail callees and globals (address in the comment)
void* operator new(unsigned int size, const char* name, int, int, int, int);   // 0x00f473a0
void* operator new(unsigned int size, const char* name, int, int, const char*, int);
void  operator delete(void*);                                                 // 0x00f47380
void* operator_new_array(void*, int, unsigned int);                            // 0x011e073e

extern const char* kPath_01554af4;
extern const char* kPath_01554af8;
extern const char* kPath_01554afc;
extern const char* kPath_01554b00;
extern const char* kPath_01554b04;
extern const char* kPath_01554b08;
extern const char* kPath_01554b0c;
extern const char* kPath_01554b10;
extern const char* kPath_01554b14;
extern const char* kPath_01554b18;
extern const char* kPath_01554b1c;
extern const char* kPath_01554b20;
extern const char* kPath_01554b24;

namespace EA { namespace ArgScript {

class cArguments;
class cIParser;
struct cState;
class cICommand;
class cIBlockCommand;

class cICommand {
 public:
    virtual void Execute(cArguments*);
    virtual const char* Description(int) const;
    virtual void OnRegister(cIParser*, cState*);
    virtual int AddRef();
    virtual int Release();
};

class cCommandBase : public cICommand {
 public:
    cCommandBase();                              // 0x0083c800
    virtual ~cCommandBase();
    cIParser* mParser;                           // +0x04
    int mRefCount;                               // +0x08
};

class cBlockCommandBase : public cCommandBase {
 public:
    cState* mChildState;                         // +0x0c
    char mMap[0x20];                             // +0x10
    virtual void OnRegister(cIParser*, cState*); // 0x0083c780
    void SetChildState(cState*);                 // 0x00fd9450
    virtual void AddCommand(const char*, cICommand*);  // +0x18
    virtual void vAfter();                       // +0x1c
};

template <typename State, typename Base>
struct cCommandStateT : Base {
    State* mState;                               // +0x0c for Base=cCommandBase
};

class cArguments {
 public:
    char const* const* MainArguments(int) const; // 0x00838320
    bool HasFlag(const char*);                   // 0x008380b0
};

class cIParser {
 public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34();
    virtual void StartBlock(class cIBlockCommand*);              // slot 35 = +0x8c
    virtual void v36(); virtual void v37();
    virtual float ParseFloat(const char*) const;                 // slot 38 = +0x98
    virtual void v39(); virtual void v40(); virtual void v41();
    virtual Vector3 ParseVector3(const char*) const;             // slot 42 = +0xa8
};

}}  // namespace EA::ArgScript

// ---- vectors -----------------------------------------------------------------

namespace {

template <typename T>
struct Vec {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAlloc[2];
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    void erase(T* first, T* last);                   // out of line
    void DoInsertValue(T* position, const T& value); // out of line
    void push_back(const T& value) {
        T* e = mpEnd;
        if (e < mpCapacity) {
            mpEnd = e + 1;
            if (e) { e->x = value.x; e->y = value.y; e->z = value.z; }
        } else {
            DoInsertValue(e, value);
        }
    }
};

struct VecF {
    float* mpBegin; float* mpEnd; float* mpCapacity; uint32_t mAlloc[2];
    float* begin() { return mpBegin; }
    float* end() { return mpEnd; }
    float* erase(float* first, float* last) {
        memcpy(first, last, (uint32_t)((char*)mpEnd - (char*)last));
        mpEnd -= last - first;
        return first;
    }
    void DoInsertValue(float* position, const float& value);   // out of line 0x00455660
    void push_back(const float& value) {
        float* e = mpEnd;
        if (e < mpCapacity) {
            mpEnd = e + 1;
            if (e) *e = value;
        } else {
            DoInsertValue(e, value);
        }
    }
};

}  // namespace

namespace SwarmImpl {

struct cPathState {
    uint32_t mStateID;            // +0x00
    Vec<Vector3> mPositions;      // +0x04
    VecF mSpeeds;                 // +0x18
    Vec<Vector3> mDeltaPositions; // +0x2c
    VecF mTimes;                  // +0x40
    int mField54;                 // +0x54
    bool* mTractor;               // +0x58
    int mField5c;                 // +0x5c
    ~cPathState();                // 0x00a7a4a0 (frees the four vectors)
};

struct cPathPointCommand : EA::ArgScript::cCommandStateT<cPathState, EA::ArgScript::cCommandBase> {
    virtual void Execute(EA::ArgScript::cArguments*);
};
struct cPathDeltaPointCommand : EA::ArgScript::cCommandStateT<cPathState, EA::ArgScript::cCommandBase> {
    virtual void Execute(EA::ArgScript::cArguments*);
};
struct cPathVelocityCommand : EA::ArgScript::cCommandStateT<cPathState, EA::ArgScript::cCommandBase> {
    virtual void Execute(EA::ArgScript::cArguments*);
};
struct cPathSpeedCommand : EA::ArgScript::cCommandStateT<cPathState, EA::ArgScript::cCommandBase> {
    virtual void Execute(EA::ArgScript::cArguments*);
};
struct cPathTimeCommand : EA::ArgScript::cCommandStateT<cPathState, EA::ArgScript::cCommandBase> {
    virtual void Execute(EA::ArgScript::cArguments*);
};
struct cPathDeltaTimeCommand : EA::ArgScript::cCommandStateT<cPathState, EA::ArgScript::cCommandBase> {
    virtual void Execute(EA::ArgScript::cArguments*);
};

struct cPathCommand : EA::ArgScript::cCommandStateT<cPathState, EA::ArgScript::cBlockCommandBase> {
    cPathCommand(int a, bool* b, int c);
    virtual void Execute(EA::ArgScript::cArguments*);
    virtual void OnRegister(EA::ArgScript::cIParser*, EA::ArgScript::cState*);
    cPathState mChildState;       // +0x34
};

}  // namespace SwarmImpl

using EA::ArgScript::cArguments;
using EA::ArgScript::cIParser;
using EA::ArgScript::cState;
using EA::ArgScript::cICommand;
using EA::ArgScript::cIBlockCommand;
using EA::ArgScript::cBlockCommandBase;
using SwarmImpl::cPathState;
using SwarmImpl::cPathCommand;
using SwarmImpl::cPathPointCommand;
using SwarmImpl::cPathDeltaPointCommand;
using SwarmImpl::cPathVelocityCommand;
using SwarmImpl::cPathSpeedCommand;
using SwarmImpl::cPathTimeCommand;
using SwarmImpl::cPathDeltaTimeCommand;

namespace EA { namespace Swarm {
void RegisterPathCommand(cBlockCommandBase* owner, int a, bool* b, int c);   // 0x00a7a8d0
void* cResourceOverridesParam_Create(int n);                                 // 0x00a7a960
}}  // namespace EA::Swarm

// ---- implementations ---------------------------------------------------------

namespace SwarmImpl {

// cPathPointCommand::Execute
// @ 0x00a7af50
void cPathPointCommand::Execute(cArguments* args)
{
    mState->mPositions.push_back(mParser->ParseVector3(args->MainArguments(1)[0]));
}

// cPathDeltaPointCommand::Execute
// @ 0x00a7afc0
void cPathDeltaPointCommand::Execute(cArguments* args)
{
    Vector3 v = mParser->ParseVector3(args->MainArguments(1)[0]);
    Vec<Vector3>& pos = mState->mPositions;
    if (pos.begin() == pos.end()) {
        pos.push_back(v);
    } else {
        const Vector3& last = pos.end()[-1];
        Vector3 t;
        t.x = last.x + v.x;
        t.y = last.y + v.y;
        t.z = last.z + v.z;
        pos.push_back(t);
    }
}

// cPathVelocityCommand::Execute
// @ 0x00a7b0d0
void cPathVelocityCommand::Execute(cArguments* args)
{
    mState->mDeltaPositions.push_back(mParser->ParseVector3(args->MainArguments(1)[0]));
}

// cPathSpeedCommand::Execute
// @ 0x00a7b140
void cPathSpeedCommand::Execute(cArguments* args)
{
    float v = mParser->ParseFloat(args->MainArguments(1)[0]);
    mState->mSpeeds.push_back(v);
}

// cPathTimeCommand::Execute
// @ 0x00a7b1a0
void cPathTimeCommand::Execute(cArguments* args)
{
    float v = mParser->ParseFloat(args->MainArguments(1)[0]);
    mState->mTimes.push_back(v);
}

// cPathDeltaTimeCommand::Execute
// @ 0x00a7b200
void cPathDeltaTimeCommand::Execute(cArguments* args)
{
    float v = mParser->ParseFloat(args->MainArguments(1)[0]);
    VecF& times = mState->mTimes;
    if (times.begin() == times.end()) {
        times.push_back(0.0f);
        times.push_back(v);
    } else {
        float t = times.end()[-1] + v;
        times.push_back(t);
    }
}

}  // namespace SwarmImpl

// Defining cPathCommand's constructor out-of-line makes the compiler emit the
// implicit virtual destructor and its scalar deleting destructor (??_G).
// @ 0x00a7a8a0
__declspec(noinline) cPathCommand::cPathCommand(int a, bool* b, int c)
{
    (void)a; (void)b; (void)c;
}

// cPathCommand::Execute
// @ 0x00a7b2d0
void cPathCommand::Execute(cArguments* args)
{
    args->MainArguments(0);
    *mChildState.mTractor = args->HasFlag("tractor");
    mChildState.mPositions.erase(mChildState.mPositions.begin(), mChildState.mPositions.end());
    mChildState.mDeltaPositions.erase(mChildState.mDeltaPositions.begin(), mChildState.mDeltaPositions.end());
    mChildState.mSpeeds.erase(mChildState.mSpeeds.begin(), mChildState.mSpeeds.end());
    mChildState.mTimes.erase(mChildState.mTimes.begin(), mChildState.mTimes.end());
    mParser->StartBlock((cIBlockCommand*)this);
}

// @ 0x00a7a580
void cPathCommand::OnRegister(cIParser* parser, cState* state)
{
    mState = (cPathState*)state;
    cBlockCommandBase::OnRegister(parser, state);
    SetChildState((cState*)&mChildState);
    AddCommand(kPath_01554af8, new ("ArgScript/PathPoint", 0, 0, 0, 0) cPathPointCommand());
    AddCommand(kPath_01554b00, new ("ArgScript/PathDeltaPoint", 0, 0, 0, 0) cPathDeltaPointCommand());
    AddCommand(kPath_01554b08, new ("ArgScript/PathVelocity", 0, 0, 0, 0) cPathVelocityCommand());
    AddCommand(kPath_01554b10, new ("ArgScript/PathSpeed", 0, 0, 0, 0) cPathSpeedCommand());
    AddCommand(kPath_01554b18, new ("ArgScript/PathTime", 0, 0, 0, 0) cPathTimeCommand());
    AddCommand(kPath_01554b20, new ("ArgScript/PathDeltaTime", 0, 0, 0, 0) cPathDeltaTimeCommand());
    AddCommand(kPath_01554afc, new ("ArgScript/PathPointLong", 0, 0, 0, 0) cPathPointCommand());
    AddCommand(kPath_01554b04, new ("ArgScript/PathDeltaPointLong", 0, 0, 0, 0) cPathDeltaPointCommand());
    AddCommand(kPath_01554b0c, new ("ArgScript/PathVelocityLong", 0, 0, 0, 0) cPathVelocityCommand());
    AddCommand(kPath_01554b14, new ("ArgScript/PathSpeedLong", 0, 0, 0, 0) cPathSpeedCommand());
    AddCommand(kPath_01554b1c, new ("ArgScript/PathTimeLong", 0, 0, 0, 0) cPathTimeCommand());
    AddCommand(kPath_01554b24, new ("ArgScript/PathDeltaTimeLong", 0, 0, 0, 0) cPathDeltaTimeCommand());
}

// EA::Swarm::RegisterPathCommand
// @ 0x00a7a8d0
void EA::Swarm::RegisterPathCommand(cBlockCommandBase* owner, int a, bool* b, int c)
{
    owner->AddCommand(kPath_01554af4, new ("ArgScript/Path", 0, 0, 0, 0) cPathCommand(a, b, c));
}

// EA::Swarm::cResourceOverridesParam::Create
// @ 0x00a7a960
void* EA::Swarm::cResourceOverridesParam_Create(int n)
{
    int size = n * 0x10;
    uint32_t* p = (uint32_t*)operator new(size + 0x10, "Swarm/ResourceOverrides", 0, 0, 0, 0);
    uint32_t* q;
    if (p) {
        ((volatile uint32_t*)p)[1] = 0x13ef094;
        ((volatile uint32_t*)p)[2] = 0;
        ((volatile uint32_t*)p)[0] = 0x14582ec;
        ((volatile uint32_t*)p)[1] = 0x14188c0;
        q = p;
    } else {
        q = 0;
    }
    q[3] = (uint32_t)n;
    operator_new_array(q + 4, 0, (uint32_t)size);
    return q;
}

// ---- path sampler ------------------------------------------------------------

namespace {

struct cPathSample { Vector3 pos; Vector3 dir; float dist; };   // 0x1c

struct SampleVec {
    cPathSample* mpBegin; cPathSample* mpEnd; cPathSample* mpCapacity; uint32_t mAlloc[2];
    cPathSample* begin() { return mpBegin; }
    cPathSample* end() { return mpEnd; }
    void DoInsertValue(cPathSample* position, const cPathSample& value);  // 0x00a7a9d0
    void erase(cPathSample* first, cPathSample* last);                    // 0x00d73090
    void push_back(const cPathSample& value) {
        cPathSample* e = mpEnd;
        if (e < mpCapacity) {
            mpEnd = e + 1;
            if (e) *e = value;
        } else {
            DoInsertValue(e, value);
        }
    }
};

cPathSample* vec_copy(const cPathSample*, const cPathSample*, cPathSample*);   // 0x00a78e30

struct cPathOpts {
    uint16_t mFlags;              // +0x00
    char mPad02[2];
    Vector3 mOffset;              // +0x04
    float mScale;                 // +0x10
    Vector3 mRow0;                // +0x14
    Vector3 mRow1;                // +0x20
    Vector3 mRow2;                // +0x2c
};

extern const float kOne_01485720;     // 1.0f
extern const float kEps_013f11c8;
extern const float gDirDef_016770dc;
extern const float gDirDef_016770e0;
extern const float gDirDef_016770e4;

}  // namespace

// SampleVec::DoInsertValue
// @ 0x00a7a9d0
void SampleVec::DoInsertValue(cPathSample* position, const cPathSample& value)
{
    cPathSample* e = mpEnd;
    if (e != mpCapacity) {
        const cPathSample* v = &value;
        if (v >= position && v < e)
            v = v + 1;
        if (e) {
            e->pos.x = e[-1].pos.x; e->pos.y = e[-1].pos.y; e->pos.z = e[-1].pos.z;
            e->dir.x = e[-1].dir.x; e->dir.y = e[-1].dir.y; e->dir.z = e[-1].dir.z;
            e->dist  = e[-1].dist;
        }
        cPathSample* dst = mpEnd;
        cPathSample* src = dst - 1;
        while (src != position) {
            --src;
            --dst;
            *dst = *src;
        }
        *position = *v;
        mpEnd += 1;
        return;
    }
    uint32_t count = (uint32_t)(e - mpBegin);
    uint32_t newCap = count ? count * 2 : 1;
    cPathSample* p = newCap ? (cPathSample*)operator new(newCap * sizeof(cPathSample), "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    cPathSample* oldBegin = mpBegin;
    cPathSample* mid = vec_copy(oldBegin, position, p);
    if (mid) {
        mid->pos.x = value.pos.x; mid->pos.y = value.pos.y; mid->pos.z = value.pos.z;
        mid->dir.x = value.dir.x; mid->dir.y = value.dir.y; mid->dir.z = value.dir.z;
        mid->dist  = value.dist;
    }
    cPathSample* oldEnd = mpEnd;
    cPathSample* ne = vec_copy(position, oldEnd, mid + 1);
    if (mpBegin && ((int*)mpBegin)[-1]) operator delete(mpBegin);
    mpBegin = p;
    mpEnd = ne;
    mpCapacity = p + newCap;
}

// @ 0x00a7ab40
void BuildPath(int count, Vector3* pts, float spdScale, cPathOpts* opts, SampleVec* out)
{
    out->erase(out->begin(), out->end());
    float dist = 0.0f;
    if (count <= 0) return;

    int lastIdx = count - 1;
    for (int i = 1; i <= count; i++) {
        int idxA = (i - 2 >= 0) ? (i - 2) : 0;
        int idxB = (i <= lastIdx) ? i : lastIdx;
        Vector3 d;
        d.x = pts[idxB].x - pts[idxA].x;
        d.y = pts[idxB].y - pts[idxA].y;
        d.z = pts[idxB].z - pts[idxA].z;
        float sc = opts->mScale;
        if (sc != kOne_01485720) {
            float inv = kOne_01485720 / sc;
            d.x *= inv; d.y *= inv; d.z *= inv;
        }
        if (opts->mFlags & 2) {
            Vector3 t;
            t.x = d.x * opts->mRow0.x + d.y * opts->mRow0.y + d.z * opts->mRow0.z;
            t.y = d.x * opts->mRow1.x + d.y * opts->mRow1.y + d.z * opts->mRow1.z;
            t.z = d.x * opts->mRow2.x + d.y * opts->mRow2.y + d.z * opts->mRow2.z;
            d = t;
        }
        Vector3 delta;
        delta.x = pts[i - 1].x - opts->mOffset.x;
        delta.y = pts[i - 1].y - opts->mOffset.y;
        delta.z = pts[i - 1].z - opts->mOffset.z;
        float len = (float)sqrt(d.y * d.y + d.z * d.z + d.x * d.x);
        if (sc != kOne_01485720) {
            float inv = kOne_01485720 / sc;
            delta.x *= inv; delta.y *= inv; delta.z *= inv;
        }
        if (opts->mFlags & 2) {
            Vector3 t;
            t.x = delta.x * opts->mRow0.x + delta.y * opts->mRow0.y + delta.z * opts->mRow0.z;
            t.y = delta.x * opts->mRow1.x + delta.y * opts->mRow1.y + delta.z * opts->mRow1.z;
            t.z = delta.x * opts->mRow2.x + delta.y * opts->mRow2.y + delta.z * opts->mRow2.z;
            delta = t;
        }
        Vector3 dir;
        dir.x = gDirDef_016770dc;
        dir.y = gDirDef_016770e0;
        dir.z = gDirDef_016770e4;
        if (len > kEps_013f11c8) {
            float s = spdScale / len;
            dir.x = d.x * s;
            dir.y = d.y * s;
            dir.z = d.z * s;
        }
        if (i != 1) {
            Vector3 dd;
            dd.x = pts[i - 1].x - pts[i - 2].x;
            dd.y = pts[i - 1].y - pts[i - 2].y;
            dd.z = pts[i - 1].z - pts[i - 2].z;
            dist += (float)sqrt(dd.z * dd.z + dd.y * dd.y + dd.x * dd.x) / spdScale;
        }
        cPathSample s;
        s.pos = delta;
        s.dir = dir;
        s.dist = dist;
        out->push_back(s);
    }
}
