// Slice s00480320: cSPEditorHandleRotationRing geometry helpers, /Od /Ob1 /arch:SSE.
#include "types.h"

struct Vector3 { float x, y, z; };

// vector helpers (masked relocations)
Vector3* VecSubtract(Vector3* out, const Vector3* a, const Vector3* b);   // @ 0x0041db10
Vector3* VecNormalize(Vector3* out, const Vector3* in);                  // @ 0x00436ce0
Vector3* VecScale(Vector3* out, const float* s, const Vector3* v);       // @ 0x0041de40
Vector3* VecCross(Vector3* out, const Vector3* a, const Vector3* b);     // @ 0x0041dca0
void     GetLocalTransform(void* entity, void* matrix);                  // @ 0x00436380

// @ 0x00480cf0
void Ring_Reset(char* self)
{
    char matrix[0x38];
    GetLocalTransform(*(void**)(self + 0x10), matrix);

    Vector3 diff, dir;
    VecSubtract(&diff, (Vector3*)(self + 0x90), (Vector3*)(self + 0x9c));
    VecNormalize(&dir, &diff);
    *(Vector3*)(self + 0xc4) = dir;

    float scale = *(float*)0x13eb960;   // 5.0f
    Vector3 scaled, offset;
    VecScale(&scaled, &scale, (Vector3*)(self + 0xc4));
    VecSubtract(&offset, (Vector3*)(self + 0x9c), &scaled);
    *(Vector3*)(self + 0xb8) = offset;

    *(Vector3*)(self + 0xe8) = *(Vector3*)(self + 0x90);
    *(Vector3*)(self + 0x10c) = *(Vector3*)(self + 0x9c);

    void Ring_Rotate(char*, float);      // @ 0x004809c0
    Ring_Rotate(self, *(float*)0x13eb960);
    *(uint8_t*)(self + 0x118) = 1;
}

// @ 0x004809c0 -- PARTIAL: bounding-box / basis rebuild; only the entry BBox call
// and the normalisation tail are reproduced, the inner branchy math is omitted.
void Ring_Rotate(char* self, float angle)
{
    void GetBBox(void*, void*, int, int, int);   // @ 0x00480e90 region helper
    char bbox[0x28];
    GetBBox(*(void**)(self + 0x10), bbox, 1, 0, 0);
    (void)angle;
}

// @ 0x00480320 -- PARTIAL: large transform/basis builder; only the local-transform
// and vector entry sequence is reproduced.
void Ring_Build(char* self)
{
    Vector3 v0, v1, out;
    VecSubtract(&out, (Vector3*)(self + 0x90), (Vector3*)(self + 0x9c));
    VecNormalize(&v0, &out);
    VecScale(&v1, (const float*)0x13eb1bc, &v0);
    *(Vector3*)(self + 0xb8) = v1;
}
