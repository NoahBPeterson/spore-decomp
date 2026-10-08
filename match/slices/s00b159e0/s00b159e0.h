// Slice s00b159e0 (batch bfs1) — shared types.
// Module "Spore"; SP::cTerrainCameraController mouse/scroll handlers and the camera-spline
// builder. Field offsets follow the 2008 PDB up to +0x168 (confirmed against the retail
// disassembly); the spline members are retail-sized (vector = 0x14 bytes, spline = 0x3c).

#pragma once
#include "types.h"

struct cLocalInputState
{
    void Reset();
    bool OnKeyDown(int, int);
    bool OnMouseDown(int, float, float, int);
    bool OnMouseUp(int, float, float, int);
    bool OnMouseWheel(int delta, float x, float y, int flag);
};

struct Vector3 { float x, y, z; };
struct cSPQuaternion { float x, y, z, w; };

// SpVector<T>: begin/end/capacity + two more words in the retail layout.
template<class T> struct SpVector
{
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mExtra[2];
    T& operator[](int i) { return mpBegin[i]; }
    void resize(int n);
};

// SP::cHermiteSplineInterpolation<T> (retail: three vectors, 0x3c bytes).
template<class T> struct cHermiteSplineInterpolation
{
    SpVector<float> times;
    SpVector<T> points;
    SpVector<T> slopes;
    void Clear();
    void ComputeSlopes();
};

struct InterpFloat      // SP::cTerrainCameraController::cInterpolationData<float>, 0x24
{
    bool targetChanged, targetMoving;
    float currentTime, targetTime;
    float start, current, end, target, velocity, targetVelocity;
};
struct InterpVec3       // cInterpolationData<cSPVector3>, 0x54
{
    bool targetChanged, targetMoving;
    float currentTime, targetTime;
    Vector3 start, current, end, target, velocity, targetVelocity;
};
struct InterpQuat       // cInterpolationData<cSPQuaternion>, 0x6c
{
    bool targetChanged, targetMoving;
    float currentTime, targetTime;
    cSPQuaternion start, current, end, target, velocity, targetVelocity;
};

struct cTerrainCameraController
{
    char  pad_00[0x13];
    bool  m13;              // +0x13  mUIZoomIn
    char  pad_14[4];
    InterpFloat mCameraAnchorRadius;            // +0x18
    InterpVec3  mCameraAnchorDirection;         // +0x3c
    InterpQuat  mCameraAnchorOrientation;       // +0x90
    InterpFloat mCameraDistance;                // +0xfc
    InterpFloat mCameraPitch;                   // +0x120
    InterpFloat mCameraYaw;                     // +0x144
    bool  mBallisticMotion;                     // +0x168
    char  pad_169[3];
    cHermiteSplineInterpolation<float>         mDistanceSpline;      // +0x16c
    cHermiteSplineInterpolation<float>         mPitchSpline;         // +0x1a8
    cHermiteSplineInterpolation<Vector3>       mDirectionSpline;     // +0x1e4
    cHermiteSplineInterpolation<cSPQuaternion> mOrientationSpline;   // +0x220
    char  pad_25c[0x294 - 0x25c];
    float m294;             // +0x294
    char  pad_298[0x2a0 - 0x298];
    float m2a0;             // +0x2a0
    char  pad_2a4[0x31c - 0x2a4];
    cLocalInputState mInput;   // +0x31c
    char  pad_31d[0x37c - 0x31d];
    float mTiltDistance;    // +0x37c
    float mTiltMinAngle;    // +0x380

    void FUN_00b148c0(float, float, float, float);   // out-of-slice helper
    void FUN_00b159e0(int);                          // @ 0x00b159e0
    void FUN_00b15a20(unsigned);                     // @ 0x00b15a20
    bool FUN_00b15a80(int, float, float, int);       // @ 0x00b15a80
    void FUN_00b15b00();                             // @ 0x00b15b00
    void FUN_00b16270();                             // @ 0x00b16270
    void GetTargetOrientation(cSPQuaternion* out);   // 0x00b137d0
};

// Free helpers in this slice.
void FUN_00b16450(float* v, int* list);              // @ 0x00b16450
void FUN_00b16490(float* v, float add);              // @ 0x00b16490
bool FUN_00b16520(int* world, float* a, float* b, bool flag, float* out);  // @ 0x00b16520
