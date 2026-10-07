// Slice s00e6db70: Cell game -- re-centre the cell world on a new origin (snapped to a 1000-unit
// grid) and rescale everything by 1/scale: cells, effect positions, modifiers, cameras, the
// background tiles and their lookup map. Called from 0x00e73f3a.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// In the original this is a `static` function of the big Cell TU: cl gave it and several of its
// static callees custom register conventions (centre in eax; Snap: edx/xmm3; cell helpers take
// the cell in esi and outputs in edi; GetCellScaleFactor returns in xmm0). Those callees live in
// that TU, so here they are plain extern functions with standard conventions; the body is
// otherwise complete.
#include "types.h"

// float -> int rounding down (the module's asm helper: cvtss2si + cmovb).
__forceinline int FloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}

struct Vector2 {
    float x, y;
    Vector2() {}
    Vector2(float x_, float y_) : x(x_), y(y_) {}
};

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    Vector3 operator*(float f) const { return Vector3(x * f, y * f, z * f); }
    Vector3& operator-=(const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    Vector3& operator*=(float f) { x *= f; y *= f; z *= f; return *this; }
};

struct Matrix3 {
    Vector3 m[3];
};

// row vector * matrix
inline Vector3 operator*(const Vector3& v, const Matrix3& m)
{
    return Vector3(v.x * m.m[0].x + v.y * m.m[1].x + v.z * m.m[2].x,
                   v.x * m.m[0].y + v.y * m.m[1].y + v.z * m.m[2].y,
                   v.x * m.m[0].z + v.y * m.m[1].z + v.z * m.m[2].z);
}

// Transform message applied to modifiers / shapes.
struct TransformMsg {
    short mType;        // +0x00
    short mFlags;       // +0x02
    Vector3 mPosition;  // +0x04
    float mScale;       // +0x10
    Matrix3 mOrient;    // +0x14
};

struct Modifier {
    void AccumulateScaled(const TransformMsg* pMsg);   // 0x0040cd80
};

struct IShape {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void Transform(const TransformMsg* pMsg);   // +0x18
};

// ------------------------------------------------------------------ EASTL vector_map<int,int>
struct IntPair {
    int first;
    int second;
    IntPair(int a, int b) : first(a), second(b) {}
};

template <class InputIterator, class OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
{
    for (; first != last; ++first, ++result)
        *result = *first;
    return result;
}

template <class ForwardIterator>
inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, int value)
{
    int d = (int)(last - first);
    while (d > 0) {
        ForwardIterator i = first;
        int d2 = d >> 1;
        i += d2;
        if (i->first < value) {
            first = ++i;
            d -= d2 + 1;
        } else
            d = d2;
    }
    return first;
}

struct IntMap {
    IntPair* mpBegin;
    IntPair* mpEnd;
    IntPair* mpCapacity;

    IntPair* begin() { return mpBegin; }
    IntPair* end() { return mpEnd; }
    void DoInsertValue(IntPair* position, const IntPair& value);   // 0x00e63d60
    IntPair* vector_insert(IntPair* position, const IntPair& value) {
        const int n = (int)(position - mpBegin);
        if ((position == mpEnd) && (mpEnd != mpCapacity)) {
            IntPair* p = mpEnd++;
            if (p)
                *p = value;
        } else
            DoInsertValue(position, value);
        return mpBegin + n;
    }
    IntPair* erase(IntPair* first, IntPair* last) {
        copy(last, mpEnd, first);
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(begin(), end()); }
    IntPair* insert(IntPair* position, const IntPair& value) {
        IntPair* it;
        if ((position != end()) && (value.first < position->first))
            it = lower_bound(begin(), position, value.first);
        else
            it = lower_bound(position, end(), value.first);
        if ((it == end()) || (value.first < it->first))
            it = vector_insert(it, value);
        return it;
    }
    int& operator[](int key) {
        IntPair* itLB = lower_bound(begin(), end(), key);
        if ((itLB == end()) || (key < itLB->first))
            itLB = insert(itLB, IntPair(key, 0));
        return itLB->second;
    }
};

// ------------------------------------------------------------------ cell objects
struct ObjectPool {
    int Begin();               // 0x00e31100 (returns 0)
    void* Next(int* pIndex);   // 0x00b72230
};

struct cCell {
    int mHandle;            // +0x000
    uint32_t pad04;
    Vector3 mTarget;        // +0x008
    uint32_t pad14[(0x48 - 0x14) / 4];
    short mFlags;           // +0x048
    short mVersion;         // +0x04a
    Vector3 mPosition;      // +0x04c
    float mRadius;          // +0x058
    uint32_t pad5c[(0x90 - 0x5c) / 4];
    Vector3 mVelocity;      // +0x090
    uint32_t pad9c[(0xb4 - 0x9c) / 4];
    float mSize;            // +0x0b4
    float mMass;            // +0x0b8
    float mInvMass;         // +0x0bc
    Modifier mModifier;     // +0x0c0
    uint32_t padc4[(0x108 - 0xc4) / 4];
    int mType;              // +0x108
    uint32_t pad10c[(0x1c4 - 0x10c) / 4];
    Vector3 mGoal;          // +0x1c4
    uint32_t pad1d0[(0x35c - 0x1d0) / 4];
    int mEffectGroup;       // +0x35c
    int mEffect;            // +0x360
    int mObstacle;          // +0x364

    void SetPosition(const Vector3& v) {
        mFlags |= 4;
        mPosition = v;
        mVersion++;
    }
    void SetRadius(float r) {
        mVersion++;
        mRadius = r;
    }
};

struct cBackgroundTile {
    int mHandle;            // +0x000
    int mLayer;             // +0x004
    int mLevel;             // +0x008
    int mX;                 // +0x00c
    int mY;                 // +0x010
    uint32_t pad14[(0x300 - 0x14) / 4];
    IShape* mpShape;        // +0x300
};

struct cCellEffectPositions {
    uint32_t pad0;
    Vector3 mPositions[0x5dc];          // +0x00004
    uint32_t pad[(0x18e74 - 0x4654) / 4];
    int mActive[0x5dc];                 // +0x18e74
};

struct cCellLevelInfo { uint32_t pad[7]; int mStage; };   // +0x1c

struct cCellGame {
    uint32_t pad0;
    float mWorldScale;                          // +0x0004
    uint32_t pad8[(0x1c - 0x8) / 4];
    ObjectPool mCells;                          // +0x001c
    uint32_t pad20[(0x38 - 0x20) / 4];
    ObjectPool mTiles;                          // +0x0038
    uint32_t pad3c[(0x4104 - 0x3c) / 4];
    int mObstacleGrid;                          // +0x4104
    cCellEffectPositions* mpEffectPositions;    // +0x4108
    uint32_t pad410c[(0x4128 - 0x410c) / 4];
    IntMap mTileMap;                            // +0x4128
    uint32_t pad4134[(0x514c - 0x4134) / 4];
    float mCellSize;                            // +0x514c
    uint32_t pad5150[(0x5190 - 0x5150) / 4];
    cCellLevelInfo* mpLevelInfo;                // +0x5190
};

struct cCellModifierEntry { uint32_t pad[0x74 / 4]; };

struct cCellGfx {
    uint32_t pad0[0x4c / 4];
    float mScale;                               // +0x4c
    uint32_t pad50[(0x161dc - 0x50) / 4];
    cCellModifierEntry* mModifiersBegin;        // +0x161dc
    cCellModifierEntry* mModifiersEnd;          // +0x161e0
};

struct cCellCameraState {
    uint32_t pad[0x48 / 4];
    Vector3 mPosition;     // +0x48
    Vector3 mTarget;       // +0x54
    Vector3 mOffset;       // +0x60
};

struct cCellStageInfo {
    int mLevel;            // +0x00
    int mStart;            // +0x04
    int pad[5];
};

extern cCellGame* gspCellGame;              // 0x016b3c04
extern cCellGfx* gspCellGfx;                // 0x016b3c08
extern cCellCameraState* gspCellCamera;     // 0x016b3c0c
extern Vector3 gCellWorldCenter;            // 0x016b3c28
extern Matrix3 gCellWorldOrient;            // 0x016b3c60
extern Matrix3 gCellTileOrient;             // 0x016b3dac
extern const float kLevelSize[];            // 0x01483bd0
extern const cCellStageInfo kCellStages[];  // 0x01483c14
extern const cCellStageInfo kCellEditorStage;   // 0x01483e60

void SnapToGrid(Vector3& v, float grid);   // 0x00e4f920 (in place: floor(v / grid) * grid)
void CellRescaleEffects();                                          // 0x00e86b60
float GetCellScaleFactor(int type);                                 // 0x00e4f9d0
void CellUpdateSpeed(cCell* pCell);                                 // 0x00e5a1a0
void GetCellBounds(cCell* pCell, Vector3* pCenter, float* pRadius); // 0x00e6d790
int CellMoveEffect(int group, const Vector3* pCenter, float radius, int handle);   // 0x00e868f0
void MoveObstacle(int grid, int obstacle, const Vector2* pMin, const Vector2* pMax); // 0x00bbc2f0 (thunk to 0x00bbbe60)

inline const cCellStageInfo* GetCellStage(int stage)
{
    if (stage == 1000)
        return &kCellEditorStage;
    int i = 0;
    while (stage >= kCellStages[i + 1].mStart)
        i++;
    return &kCellStages[i];
}

inline float GetLevelScale(int d)
{
    if (d < -1)
        return 1.0f;
    if (d >= 5)
        return 0.03125f;
    switch (d) {
    case -1: return 1.0f;
    case 1: return 0.25f;
    case 2: return 0.125f;
    case 3: return 0.0625f;
    case 4: return 0.03125f;
    default: return 0.5f;
    }
}

// @ 0x00e6db70
void CellRecenterWorld(const Vector3& newCenter, float scale)
{
    Vector3 center = newCenter;
    if (center.z * center.z + center.y * center.y + center.x * center.x > 1000000.0f)
        SnapToGrid(center, 1000.0f);
    else
        center = gCellWorldCenter;

    float invScale = 1.0f / scale;
    float worldScale = invScale;

    cCellEffectPositions* pEffects = gspCellGame->mpEffectPositions;
    for (int i = 0; i < 0x5dc; i++) {
        if (pEffects->mActive[i]) {
            Vector3& p = pEffects->mPositions[i];
            p.x = (p.x - center.x) * invScale;
            p.y = (p.y - center.y) * invScale;
            p.z = (p.z - center.z) * invScale;
        }
    }
    CellRescaleEffects();

    TransformMsg msg;
    msg.mType = 4;
    msg.mFlags = 3;
    Matrix3 orient = gCellWorldOrient;
    msg.mOrient = orient;
    msg.mPosition = center + (gCellWorldCenter - (gCellWorldCenter * invScale) * orient);
    msg.mScale = invScale;

    int index = gspCellGame->mCells.Begin();
    for (cCell* pCell = (cCell*)gspCellGame->mCells.Next(&index); pCell; pCell = (cCell*)gspCellGame->mCells.Next(&index)) {
        Vector3 pos = (pCell->mPosition - center) * invScale;
        float radius = pCell->mRadius;
        pCell->mModifier.AccumulateScaled(&msg);
        pCell->SetPosition(pos);
        pCell->SetRadius(radius * invScale);
        pCell->mVelocity *= invScale;
        float size = pCell->mSize * invScale;
        pCell->mSize = size;
        if (size != 0.0f) {
            float mass = GetCellScaleFactor(pCell->mType) * size * size;
            pCell->mMass = mass;
            pCell->mInvMass = 1.0f / mass;
        }
        CellUpdateSpeed(pCell);

        Vector3 boundsCenter;
        float boundsRadius;
        GetCellBounds(pCell, &boundsCenter, &boundsRadius);
        pCell->mEffect = CellMoveEffect(pCell->mEffectGroup, &boundsCenter, boundsRadius, pCell->mHandle);
        if (pCell->mObstacle != -1) {
            Vector3 c;
            float r;
            GetCellBounds(pCell, &c, &r);
            Vector2 vMax(c.x + r, c.y + r);
            Vector2 vMin(c.x - r, c.y - r);
            MoveObstacle(gspCellGame->mObstacleGrid, pCell->mObstacle, &vMin, &vMax);
        }
        pCell->mTarget -= center;
        pCell->mTarget *= invScale;
        pCell->mGoal *= invScale;
    }

    for (int i = 0; i < (int)(gspCellGfx->mModifiersEnd - gspCellGfx->mModifiersBegin); i++)
        ((Modifier*)&gspCellGfx->mModifiersBegin[i])->AccumulateScaled(&msg);
    gspCellGfx->mScale *= invScale;

    gspCellCamera->mPosition -= center;
    gspCellCamera->mPosition *= invScale;
    gspCellCamera->mTarget -= center;
    gspCellCamera->mTarget *= invScale;
    gspCellCamera->mOffset -= center;
    gspCellCamera->mOffset *= invScale;

    gspCellGame->mTileMap.clear();

    index = gspCellGame->mTiles.Begin();
    for (cBackgroundTile* pTile = (cBackgroundTile*)gspCellGame->mTiles.Next(&index); pTile;
         pTile = (cBackgroundTile*)gspCellGame->mTiles.Next(&index)) {
        float tileScale = 1.0f / ((kLevelSize[pTile->mLevel] / gspCellGame->mCellSize) *
            (GetLevelScale(pTile->mLevel - GetCellStage(gspCellGame->mpLevelInfo->mStage)->mLevel) * 0.85f));
        pTile->mX -= FloorToInt(tileScale * center.x);
        pTile->mY -= FloorToInt(center.y * tileScale);

        if (pTile->mpShape) {
            int level = pTile->mLevel;
            float levelSize = kLevelSize[level];
            float border = level * 0.0f;
            float x0 = pTile->mX * levelSize + border;
            float y0 = pTile->mY * levelSize + border;
            float x1 = (pTile->mX + 1) * levelSize - border;
            float y1 = (pTile->mY + 1) * levelSize - border;
            float s = 1.0f / (gspCellGame->mCellSize /
                (GetLevelScale(level - GetCellStage(gspCellGame->mpLevelInfo->mStage)->mLevel) * 0.85f));
            Vector3 vMin = Vector3(x0, y0, 0.0f) * s;
            Vector3 vMax = Vector3(x1, y1, 0.0f) * s;

            TransformMsg tileMsg;
            tileMsg.mOrient = gCellTileOrient;
            tileMsg.mPosition = (vMax + vMin) * 0.5f;
            tileMsg.mType = 4;
            tileMsg.mFlags = 2;
            tileMsg.mScale = vMax.x - vMin.x;
            pTile->mpShape->Transform(&tileMsg);
        }

        int key = ((((pTile->mLayer << 8) | (pTile->mLevel & 0xff)) << 8 | (pTile->mX & 0xff)) << 8) | (pTile->mY & 0xff);
        gspCellGame->mTileMap[key] = pTile->mHandle;
    }

    gspCellGame->mWorldScale *= worldScale;
}
