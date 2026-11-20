// Slice s00c43e40 -- SP::cLocomotiveObject goal setter.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the original has no EH frame).

typedef unsigned char uint8_t;
typedef unsigned int  uint32_t;
typedef int           int32_t;

struct Vector3 {
    float x;
    float y;
    float z;
};

inline bool operator==(const Vector3& a, const Vector3& b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

inline bool operator!=(const Vector3& a, const Vector3& b)
{
    return !(a == b);
}

// The goal record; the locomotive keeps a copy at +0x1f4 and copies it with
// its out-of-line assignment operator at 0x00c43de0.
struct cGoalData {
    uint32_t m00[5];                 // +0x00 .. +0x13
    Vector3  mPos;                   // +0x14
    uint32_t m20[15];                // +0x20 .. +0x5b
    int32_t  m5c;                    // +0x5c
    uint32_t m60[5];                 // +0x60 .. +0x73

    cGoalData& operator=(const cGoalData& o); // 0x00c43de0
};

struct cPathGraph {
    void release(void* node);        // 0x00ac4ef0
};

// Function-local static in the invalid-target fallback: constructed once from
// the first offending goal, torn down at exit (0x013c38c0).
struct cGoalCache {
    cGoalCache(const cGoalData& goal); // 0x00b46d90
    ~cGoalCache();
};

extern "C" int    FUN_01021080();                       // 0x01021080
extern "C" void*  FUN_00b3d290();                       // 0x00b3d290
extern "C" bool   FUN_0059ab70(const Vector3* pPos);    // 0x0059ab70
extern Vector3    kNoGoalPosition;                      // 0x0168e7e4

struct cLocomotiveObject {
    uint8_t  m00[0xd4];              // +0x000 .. +0x0d3
    uint32_t mPath;                  // +0x0d4
    uint8_t  mD8[0x1a0 - 0xd8];      // +0x0d8 .. +0x19f
    float    mSpeed;                 // +0x1a0
    uint8_t  mA4[0x1f4 - 0x1a4];     // +0x1a4 .. +0x1f3
    cGoalData mGoal;                 // +0x1f4
    uint8_t  m268[0x270 - 0x268];    // +0x268 .. +0x26f
    uint32_t mFlags;                 // +0x270
    uint8_t  m274[0x4cc - 0x274];    // +0x274 .. +0x4cb
    uint8_t* mpOwner;                // +0x4cc

    void SetGoal(cGoalData* pGoal);
};

// @ 0x00c43e40
void cLocomotiveObject::SetGoal(cGoalData* pGoal)
{
    bool bApply = FUN_01021080() != 0 || pGoal->m5c == 0
                  || (pGoal->mPos != kNoGoalPosition && FUN_0059ab70(&pGoal->mPos));

    if (bApply) {
        if (mFlags & 4) {
            ((cPathGraph*)FUN_00b3d290())->release(&mPath);
            mFlags &= ~4u;
        }
        mGoal = *pGoal;
        if (mpOwner)
            mpOwner[4] = 1;
        mSpeed = 0.0f;
        return;
    }
    static cGoalCache sCache(*pGoal);
}
