// src/game/SPTerrain/SPTerrainSphereQuad.cpp -- migrated from slice(s) s00fb39b0, s00fb0100 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainSphereQuad.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cTerrainSphereQuad.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int  FUN_006dde90(int count, void** outBuffer, int* outOffset, int param);
extern "C" void FUN_006ddee0();
#include <math.h>
#include <string.h>
#include "SP/cTerrainSphereDecal.h"

// ---- items of slice s00fb0100 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  uint8;
typedef unsigned int   uint32;
struct Vector3 { float x, y, z; };
struct QuadRange;            // result of vtable slot 3
struct QuadDrawState;        // result of vtable slot 4
struct QuadScene {
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual QuadRange*     GetRange();
    virtual QuadDrawState* GetDrawState();
};
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
struct RibbonSrc { Vector3 posA, posB, normal, tangent; };
struct RibbonDst { Vector3 pos, normal, tangent; };
extern "C" int  FUN_006dde90(int count, void** outBuffer, int* outOffset, int param);
extern "C" void FUN_006ddee0();
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
// ---- items of slice s00fb0100 end

// ---- items of slice s00fb39b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);                              // 0x011e0744
extern "C" int   __cdecl atexit(void (*)());                                                // 0x011e07ef
extern "C" void __cdecl   FUN_00762a30(int);                       // 0x00762a30
extern "C" void  __cdecl FUN_013c9d50(void);                                                    // 0x013c9d50
extern "C" int   __cdecl FUN_00762c60(void* pool, unsigned a, unsigned b, int c, int d, int e); // 0x00762c60
unsigned        DAT_016d66c0;               // 0x016d66c0  "static-init done" flag
unsigned short* DAT_016d66ac;               // 0x016d66ac  vector<unsigned short>::begin
unsigned short* DAT_016d66b0;               // 0x016d66b0  vector<unsigned short>::end
unsigned short* DAT_016d66b4;               // 0x016d66b4  vector<unsigned short>::cap
char            DAT_015d07b0;               // 0x015d07b0  index-buffer pool
struct UShortVec {
    unsigned short* begin;
    unsigned short* end;
    unsigned short* cap;
    void grow(unsigned short* pos, const unsigned short* value);       // 0x006f5bc0
};
struct IndexBuffer {
    void* Lock(unsigned int level, void* locked);                      // 0x011f4f20
    void  Unlock(void* locked);                                        // 0x011f4fd0
};
namespace SP {
struct cTerrainSphereDecal_s00fb_39b0 {
    char GetBBoxForFace(int face, float* out);                     // 0x00fad140
};
}
namespace SP {
struct cTerrainSphereQuad_s00fb_39b0 {
    char  pad0[0x18];
    int   mChunkRes;                                               // 0x18
    int   mFace;                                                   // 0x1c
    char  pad1[0x38];                                              // 0x20..0x57
    float field58;                                                 // 0x58
    float field5c;                                                 // 0x5c
    float field60;                                                 // 0x60

    unsigned char RebuildDecalIndices(unsigned int* param_2);  // 0x00fb3f10 (SP::cTerrainSphereQuad::RebuildDecalIndices)
};
}
// ---- items of slice s00fb39b0 end

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

// @ 0x00fb3f10
unsigned char __thiscall SP::cTerrainSphereQuad_s00fb_39b0::RebuildDecalIndices(unsigned int* param_2)
{
    int   chunk  = mChunkRes;
    int   stride = chunk + 3;
    float bbox[4];
    int   iRow;
    int   iCol;
    int   base;

    if (((SP::cTerrainSphereDecal_s00fb_39b0*)*param_2)->GetBBoxForFace(mFace, bbox) == 0) {
        return 0;
    }

    if ((DAT_016d66c0 & 1) == 0) {
        DAT_016d66c0 = DAT_016d66c0 | 1;
        DAT_016d66ac = 0;
        DAT_016d66b0 = 0;
        DAT_016d66b4 = 0;
        atexit(FUN_013c9d50);
    }

    {
        UShortVec* vec = (UShortVec*)&DAT_016d66ac;
        unsigned short* first = vec->begin;
        unsigned short* last  = vec->end;
        if (first != last) {
            unsigned short* d = first;
            for (unsigned short* s = last; s != vec->end; ++s, ++d) {
                *d = *s;
            }
            vec->end = (unsigned short*)((int)vec->end - (int)(last - first) * 2);
        }
    }

    if (chunk + 1 > 1) {
        base = stride;
        for (iRow = 1; iRow < chunk + 1; iRow++) {
            for (iCol = 1; iCol < chunk + 1; iCol++) {
                float res   = (float)chunk;
                float morph = field60;
                float a = ((float)(iCol - 1) / res) * morph + field58;
                float b = ((float)(iRow - 1) / res) * morph + field5c;

                if (bbox[0] < morph / res + a && a < bbox[2] &&
                    bbox[1] < morph / res + b && b < bbox[3]) {
                    unsigned int v0 = (unsigned int)(base + iCol);
                    unsigned int v1 = v0 + 1;
                    UShortVec* vec = (UShortVec*)&DAT_016d66ac;
                    unsigned short v;

                    v = (unsigned short)v1;
                    if (vec->end < vec->cap) {
                        unsigned short* p = vec->end;
                        vec->end = vec->end + 1;
                        if (p != 0) *p = v;
                    } else {
                        vec->grow(vec->end, &v);
                    }

                    v = (unsigned short)(stride + v0 + 1);
                    if (vec->end < vec->cap) {
                        unsigned short* p = vec->end;
                        vec->end = vec->end + 1;
                        if (p != 0) *p = v;
                    } else {
                        vec->grow(vec->end, &v);
                    }

                    v = (unsigned short)(stride + v0);
                    if (vec->end < vec->cap) {
                        unsigned short* p = vec->end;
                        vec->end = vec->end + 1;
                        if (p != 0) *p = v;
                    } else {
                        vec->grow(vec->end, &v);
                    }

                    v = (unsigned short)(stride + v0);
                    if (vec->end < vec->cap) {
                        unsigned short* p = vec->end;
                        vec->end = vec->end + 1;
                        if (p != 0) *p = v;
                    } else {
                        vec->grow(vec->end, &v);
                    }

                    v = (unsigned short)v0;
                    if (vec->end < vec->cap) {
                        unsigned short* p = vec->end;
                        vec->end = vec->end + 1;
                        if (p != 0) *p = v;
                    } else {
                        vec->grow(vec->end, &v);
                    }

                    v = (unsigned short)v1;
                    if (vec->end < vec->cap) {
                        unsigned short* p = vec->end;
                        vec->end = vec->end + 1;
                        if (p != 0) *p = v;
                    } else {
                        vec->grow(vec->end, &v);
                    }
                }
            }
            base += stride;
        }
    }

    if ((unsigned short*)DAT_016d66ac != DAT_016d66b0) {
        int idxBuf = (int)param_2[1];
        unsigned count = (unsigned)((int)DAT_016d66b0 - (int)DAT_016d66ac) >> 1;

        if (idxBuf != 0 && *(int*)(idxBuf + 8) != (int)count) {
            FUN_00762a30(idxBuf);
            param_2[1] = 0;
        }
        if (param_2[1] == 0) {
            param_2[1] = (unsigned int)FUN_00762c60(&DAT_015d07b0, count / 3, count, 8, 4, 0);
        }
        {
            int locked[3];
            if (((IndexBuffer*)param_2[1])->Lock(2, locked) == 0) {
                return 0;
            }
            memcpy((void*)locked[0], DAT_016d66ac,
                   (unsigned)((int)DAT_016d66b0 - (int)DAT_016d66ac) >> 1 << 1);
            ((IndexBuffer*)param_2[1])->Unlock(locked);
            return 1;
        }
    }

    if (param_2[1] != 0) {
        FUN_00762a30((int)param_2[1]);
        param_2[1] = 0;
    }
    return 1;
}
