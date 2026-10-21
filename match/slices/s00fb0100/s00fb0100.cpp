// Slice s00fb0100 -- SP::cTerrainSphereQuad ribbon-geometry builder, its bounds
// expander, the two quadtree traversal helpers, and the eastl element-copy
// routines for the 0x28-byte vertex record.
//
// Compiled /O2 /arch:SSE.  The element copies are lowered by MSVC to x87
// fld/fstp even under /arch:SSE (a struct copy of float fields), so they are
// written member-wise here to keep that shape.

#include <math.h>
#include <string.h>

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

// ------------------------------------------------------------------ math types
struct Vector3 { float x, y, z; };
struct Vector2 { float x, y; };

// ------------------------------------------------- vertex record (0x28 bytes)
struct Vertex28 {
    float mPosition[3];      // +0x00
    float mNormal[3];        // +0x0c
    float mTangent[3];       // +0x18
    uint8 mFlag;             // +0x24
    char  pad25[3];          // +0x25
};

// --------------------------------------------------------- forward interfaces
// The scene object owned by *[this+0], and the two objects the scene hands back
// through its vtable slots 3 and 4.
struct QuadRange;            // result of vtable slot 3
struct QuadDrawState;        // result of vtable slot 4
struct QuadScene {
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual QuadRange*     GetRange();
    virtual QuadDrawState* GetDrawState();
};

// Range/state objects only reached through their known members/methods.
struct QuadRange {
    char  pad00[0x34];
    float mBase0;            // +0x34
    float mBase1;            // +0x38
    float mMinSpan;          // +0x3c
    void ComputeSpan(int level, int id, int x0, int y0, float* outA, float* outB);
};
struct QuadDrawState {
    float ComputeBias();
};

// Ribbon source/vertex records: 0x30-byte source (three edge/tangent vectors and
// a second position) and 0x24-byte destination (interpolated position + frame).
struct RibbonSrc { Vector3 posA, posB, normal, tangent; };
struct RibbonDst { Vector3 pos, normal, tangent; };

// Buffer helpers the original calls out to (batch lock/flush).
extern "C" int  FUN_006dde90(int count, void** outBuffer, int* outOffset, int param);
extern "C" void FUN_006ddee0();

// --------------------------------------------------------------- quad object
struct cTerrainSphereQuad {
    QuadScene*           mScene;       // +0x00
    uint32               mUnk04;       // +0x04
    cTerrainSphereQuad*  mChild0;      // +0x08
    cTerrainSphereQuad*  mChild1;      // +0x0c
    cTerrainSphereQuad*  mChild2;      // +0x10
    cTerrainSphereQuad*  mNext;        // +0x14
    uint32               mUnk18;       // +0x18
    int                  mId;          // +0x1c
    float                mMinX;        // +0x20
    float                mMinY;        // +0x24
    float                mMaxX;        // +0x28
    float                mMaxY;        // +0x2c
    uint8                mUnk30[0x64 - 0x30];
    float                mRibbonT;     // +0x64  edge interpolation factor
    uint8                mUnk68[0x6c - 0x68];
    bool                 mSubdivided;  // +0x6c
    uint8                mUnk6d[0x70 - 0x6d];
    float                mBoundMinX;   // +0x70
    float                mBoundMinY;   // +0x74
    float                mBoundMinZ;   // +0x78
    float                mBoundMaxX;   // +0x7c
    float                mBoundMaxY;   // +0x80
    float                mBoundMaxZ;   // +0x84
    float                mExpandX;     // +0x88
    float                mExpandY;     // +0x8c
    uint8                mUnk90[0x1a0 - 0x90];
    RibbonSrc*           mRibbonBegin; // +0x1a0
    RibbonSrc*           mRibbonEnd;   // +0x1a4

    void  BufferDrawRibbonGeometry(int param);            // 00fb0100
    void  ExpandBounds(float scaleX, float scaleY);       // 00fb0730
    void  UpdateBoundsAndDraw(int mode);                  // 00fb0bd0
    void  TraverseSubdivided(int id, float* rect);        // 00fb0d20
};

// ============================================================ copy routines ==

// @ 0x00fb05e0
Vertex28** CopyElems28Guard(Vertex28** outEnd, const Vertex28* first, const Vertex28* last, Vertex28* dst)
{
    *outEnd = dst;
    if (first != last) {
        do {
            if (dst != 0) {
                dst->mPosition[0] = first->mPosition[0];
                dst->mPosition[1] = first->mPosition[1];
                dst->mPosition[2] = first->mPosition[2];
                dst->mNormal[0] = first->mNormal[0];
                dst->mNormal[1] = first->mNormal[1];
                dst->mNormal[2] = first->mNormal[2];
                dst->mTangent[0] = first->mTangent[0];
                dst->mTangent[1] = first->mTangent[1];
                dst->mTangent[2] = first->mTangent[2];
                dst->mFlag = first->mFlag;
            }
            ++first;
            ++dst;
        } while (first != last);
        *outEnd = dst;
    }
    return outEnd;
}

// @ 0x00fb0650
Vertex28* FillElems28(Vertex28* dst, uint32 count, const Vertex28* src)
{
    for (; count != 0; --count) {
        if (dst != 0) {
            dst->mPosition[0] = src->mPosition[0];
            dst->mPosition[1] = src->mPosition[1];
            dst->mPosition[2] = src->mPosition[2];
            dst->mNormal[0] = src->mNormal[0];
            dst->mNormal[1] = src->mNormal[1];
            dst->mNormal[2] = src->mNormal[2];
            dst->mTangent[0] = src->mTangent[0];
            dst->mTangent[1] = src->mTangent[1];
            dst->mTangent[2] = src->mTangent[2];
            dst->mFlag = src->mFlag;
        }
        ++dst;
    }
    // The original's code base pointer is dst+0x14, and it leaves that value in
    // eax on every return path, so callers observe end+0x14.
    return (Vertex28*)((char*)dst + 0x14);
}

// @ 0x00fb06b0
Vertex28* CopyElems28(Vertex28* first, Vertex28* last, Vertex28* dst)
{
    if (first == last)
        return dst;
    do {
        if (dst != 0) {
            dst->mPosition[0] = first->mPosition[0];
            dst->mPosition[1] = first->mPosition[1];
            dst->mPosition[2] = first->mPosition[2];
            dst->mNormal[0] = first->mNormal[0];
            dst->mNormal[1] = first->mNormal[1];
            dst->mNormal[2] = first->mNormal[2];
            dst->mTangent[0] = first->mTangent[0];
            dst->mTangent[1] = first->mTangent[1];
            dst->mTangent[2] = first->mTangent[2];
            dst->mFlag = first->mFlag;
        }
        ++first;
        ++dst;
    } while (first != last);
    return dst;
}

// ========================================================== geometry builder

// @ 0x00fb0100
void cTerrainSphereQuad::BufferDrawRibbonGeometry(int param)
{
    RibbonSrc* first = mRibbonBegin;
    int count = (int)(((char*)mRibbonEnd - (char*)mRibbonBegin) / 0x30);
    void* buffer = 0;
    int   offset = 0;

    for (int remaining = count; remaining > 0; ) {
        int got = FUN_006dde90(remaining, &buffer, &offset, param);
        int done = 0;
        float t = mRibbonT;

        if (got > 3) {
            int groups = ((uint32)(got - 4) >> 2) + 1;
            done = groups * 4;
            const RibbonSrc* s = first;
            RibbonDst* d = (RibbonDst*)((char*)buffer + offset);
            for (; groups != 0; --groups) {
                for (int k = 0; k < 4; ++k) {
                    d[k].pos.x    = s[k].posA.x + (s[k].posB.x - s[k].posA.x) * t;
                    d[k].pos.y    = s[k].posA.y + (s[k].posB.y - s[k].posA.y) * t;
                    d[k].pos.z    = s[k].posA.z + (s[k].posB.z - s[k].posA.z) * t;
                    d[k].normal   = s[k].normal;
                    d[k].tangent  = s[k].tangent;
                }
                s += 4;
                d += 4;
            }
        }

        if (done < got) {
            const RibbonSrc* s = first + done;
            RibbonDst* d = (RibbonDst*)((char*)buffer + offset + done * 0x24);
            for (int left = got - done; left != 0; --left, ++s, ++d) {
                d->pos.x   = s->posA.x + (s->posB.x - s->posA.x) * t;
                d->pos.y   = s->posA.y + (s->posB.y - s->posA.y) * t;
                d->pos.z   = s->posA.z + (s->posB.z - s->posA.z) * t;
                d->normal  = s->normal;
                d->tangent = s->tangent;
            }
        }

        FUN_006ddee0();
        first = (RibbonSrc*)((char*)first + got * 0x30);
        remaining -= got;
    }
}

// @ 0x00fb0730
void cTerrainSphereQuad::ExpandBounds(float scaleX, float scaleY)
{
    mExpandX = scaleX;
    mExpandY = scaleY;

    // Nine sample points of the quad: four corners, centre and four edge midpoints.
    float midX = (mMinX + mMaxX) * 0.5f;
    float midY = (mMinY + mMaxY) * 0.5f;
    float px[9] = { mMinX, mMinX, mMaxX, mMaxX, midX, mMinX, midX, mMaxX, midX };
    float py[9] = { mMinY, mMaxY, mMinY, mMaxY, midY, midY,  mMinY, midY, mMaxY };

    mBoundMinX = mBoundMinY = mBoundMinZ = 3.4028234e38f;   // +FLT_MAX
    mBoundMaxX = mBoundMaxY = mBoundMaxZ = -3.4028234e38f;  // -FLT_MAX

    for (int i = 0; i < 9; ++i) {
        float sx = px[i] * 2.0f - 1.0f;
        float sy = py[i] * 2.0f - 1.0f;
        float inv = 1.0f / sqrtf(sx * sx + sy * sy + 1.0f);

        float nx = inv * sx;
        float ny = inv * sy;
        float nz = inv;
        if (mId & 1) {
            nx = -nx;
            nz = -nz;
        }

        float ax = nx * scaleX, ay = ny * scaleX, az = nz * scaleX;
        float bx = nx * scaleY, by = ny * scaleY, bz = nz * scaleY;

        // Merge point A into [mBoundMin, mBoundMax].
        if (mBoundMinX <= mBoundMaxX) {
            if (mBoundMinX <= ax) { if (mBoundMaxX < ax) mBoundMaxX = ax; }
            else                  { mBoundMinX = ax; }
            if (mBoundMinY <= ay) { if (mBoundMaxY < ay) mBoundMaxY = ay; }
            else                  { mBoundMinY = ay; }
            if (mBoundMinZ <= az) { if (mBoundMaxZ < az) mBoundMaxZ = az; }
            else                  { mBoundMinZ = az; }
        } else {
            mBoundMinX = mBoundMaxX = ax;
            mBoundMinY = mBoundMaxY = ay;
            mBoundMinZ = mBoundMaxZ = az;
        }

        // Merge point B.
        if (mBoundMinX <= mBoundMaxX) {
            if (mBoundMinX <= bx) { if (mBoundMaxX < bx) mBoundMaxX = bx; }
            else                  { mBoundMinX = bx; }
            if (mBoundMinY <= by) { if (mBoundMaxY < by) mBoundMaxY = by; }
            else                  { mBoundMinY = by; }
            if (mBoundMinZ <= bz) { if (mBoundMaxZ < bz) mBoundMaxZ = bz; }
            else                  { mBoundMinZ = bz; }
        } else {
            mBoundMinX = mBoundMaxX = bx;
            mBoundMinY = mBoundMaxY = by;
            mBoundMinZ = mBoundMaxZ = bz;
        }
    }
}

// ======================================================== quadtree traversal

// @ 0x00fb0bd0
void cTerrainSphereQuad::UpdateBoundsAndDraw(int mode)
{
    QuadRange*     range = mScene->GetRange();
    QuadDrawState* draw  = mScene->GetDrawState();

    float base0 = range->mBase0;
    float base1 = range->mBase1;

    if (mSubdivided) {
        float span = draw->ComputeBias() * base1 + base0;
        ExpandBounds(span, span);
        return;
    }

    float scale = 1.0f / (mMaxX - mMinX);
    int   level = 0;
    for (int n = (int)(scale + 0.5f); n > 1; n /= 2)
        ++level;

    float outA, outB;
    range->ComputeSpan(level, mId, (int)(mMinX * scale + 0.5f), (int)(mMinY * scale + 0.5f),
                       &outA, &outB);

    float lo = outB;
    if (lo < range->mMinSpan)
        lo = range->mMinSpan;

    ExpandBounds(outA * base1 + base0, lo * base1 + base0);
}

// @ 0x00fb0d20
void cTerrainSphereQuad::TraverseSubdivided(int id, float* rect)
{
    cTerrainSphereQuad* node = this;
    if (id != node->mId)
        return;

    float cx, cy;
    for (;;) {
        node->UpdateBoundsAndDraw(1);

        cx = (node->mMinX + node->mMaxX) * 0.5f;
        cy = (node->mMinY + node->mMaxY) * 0.5f;

        if (cx > rect[0]) {            if (cy > rect[1] && node->mChild0 != 0)
                node->mChild0->TraverseSubdivided(id, rect);
            if (cy <= rect[3] && node->mChild2 != 0)
                node->mChild2->TraverseSubdivided(id, rect);
        }

        if (rect[2] < cx)
            return;

        if (cy > rect[1] && node->mChild1 != 0)
            node->mChild1->TraverseSubdivided(id, rect);

        if (rect[3] < cy)
            return;

        node = node->mNext;
        if (node == 0)
            return;
        if (node->mId != id)
            return;
    }
}