// Slice s0053eda0: Swarm "SPSkinPaintParticle" paint-variable evaluator.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// `this` is the particle paint-variable evaluation context (real dev-PDB name
// unknown); fields are recovered from the disassembly and accessed through a
// raw byte offset where the exact type is not known.
#include "types.h"

typedef unsigned int size_t;

// ---------------------------------------------------------------- math
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3& operator=(const cSPVector3&);   // @ 0x4098a0
};

cSPVector3* Vector3_Normalize(cSPVector3* out, const cSPVector3* in);   // @ 0x436ce0
cSPVector3* Vector3_Negate(cSPVector3* out, const cSPVector3* in);      // @ 0x422020
void         Vector3_MulAdd(cSPVector3* v, const float* s);             // @ 0x41dba0

// ---------------------------------------------------------------- EASTL / EA
namespace eastl {
struct sp_vector_allocator { uint32_t mData[2]; };
struct IntFloat { int mInt; float mFloat; };            // eastl::pair<int,float>
template<typename T>
struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    T* erase(T* first, T* last);            // @ 0x530c80
};
} // namespace eastl

extern "C" int __stdcall QueryPerformanceCounter(__int64* pCount); // @ IAT

namespace EA {
namespace Thread { void ThreadSleep(const int* pTime); } // @ 0x921df0
namespace Stopwatch {
    void Stopwatch(void* pThis, int a, int b);        // @ 0x93a560
    void SetTimeLimit(void* pThis, int a, int b);     // @ 0x93a480
}
}

// object pointed at by context +0x90
struct Evaluator {
    virtual void slot0();
    virtual void slot1();
    virtual char Combine(cSPVector3* a, cSPVector3* b);                        // @ 0x4f9250
    virtual cSPVector3* Interp(cSPVector3* out, cSPVector3* a, cSPVector3* b, int mode); // @ 0x4fc100
    virtual char Blend(float t, cSPVector3* a, cSPVector3* b, cSPVector3* out); // @ 0x4fbcc0
};

// ---------------------------------------------------------------- helpers
// External helpers in adjacent functions (all compiled separately).
char*        VecAdd(char* out, const char* a, const char* b);            // @ 0x53eaa0
void         EvalScaledAdd(void* self, cSPVector3* out, uint32_t key);   // @ 0x53eb10
int*         EvalAllocEntry(void* self, int key, uint32_t hash);         // @ 0x53ece0
uint8_t      EvalApplyMode(void* entry, uint8_t mask);                   // @ 0x53e3a0
unsigned int EvalFlush(void* self, int key, uint8_t mask);               // @ 0x53fe30
void         EvalBuild(float* begin, float* end, float* out);            // @ 0x541420
void         EvalInit0(int n);                                          // @ 0x473810
void         EvalInit1(int n);                                          // @ 0x4cd3c0
unsigned int Map1Hash(void* pMap, int key);                             // @ 0x540340
unsigned int Map2Hash(void* pMap, int key);                             // @ 0x540820

// tables indexed by the modifier number
extern uint8_t gPaintVarModNormal[];    // @ 0x15e2d08
extern uint8_t gPaintVarModExtra[];     // @ 0x15e2a38

// ---------------------------------------------------------------- guard
struct EvalGuard {
    int* mpEval;
    EvalGuard(int* p);                 // @ 0x566c50
    void End();                        // @ 0x53f4c0
};

// ---------------------------------------------------------------- context
struct PaintVarCtx {
    char mPad[0x98];
    unsigned char FUN_0053eda0(char bWait);
    void          FUN_0053f300(int key, int* pOut);
    void          FUN_0053f4e0();
};

EvalGuard::EvalGuard(int* p) : mpEval(p) {}

// @ 0x0053f4c0
void EvalGuard::End()
{
    *(int*)((char*)mpEval + 0x1cc) = 0;
}


// @ 0x0053eda0
unsigned char PaintVarCtx::FUN_0053eda0(char bWait)
{
    char* self = (char*)this;
    int ev = *(int*)(self + 0x94);
    unsigned char result;

    *(int*)(ev + 0x1cc) = 1;
    eastl::vector<eastl::IntFloat>* mods =
        (eastl::vector<eastl::IntFloat>*)(ev + 0x1b8);
    mods->erase(mods->mpBegin, mods->mpEnd);

    EvalGuard guard((int*)ev);

    char timer[0x24];
    EA::Stopwatch::Stopwatch(timer, 4, 0);
    EA::Stopwatch::SetTimeLimit(timer, 0, 0);
    if (bWait)
        EA::Stopwatch::SetTimeLimit(timer, 2, 0);

    unsigned int spin = 0;
    for (;;) {
        if (*(unsigned int*)(self + 0x38) <= *(unsigned int*)(self + 0x34)) {
            FUN_0053f4e0();
            result = 1;
            guard.End();
            return result;
        }
        if (bWait && (spin & 0xf) == 0) {
            __int64 now;
            QueryPerformanceCounter(&now);
            if (*(__int64*)(timer + 0x18) - now < 0) {
                int wait = 0;
                EA::Thread::ThreadSleep(&wait);
                EA::Stopwatch::SetTimeLimit(timer, 2, 0);
            }
        }

        unsigned int idx = *(unsigned int*)(self + 0x34);
        *(unsigned int*)(self + 0x34) = idx + 1;
        char* entry = (char*)(*(int*)(self + 0x20) + idx * 8);
        int entryValue = *(int*)entry;
        unsigned char applyMask = *(unsigned char*)(entry + 4);
        unsigned char edgeMask = *(unsigned char*)(entry + 5);

        if (applyMask != 0xff) {
            unsigned char bit = 1;
            for (unsigned int i = 0; i < 8; i = i + 1) {
                if ((applyMask & bit) == 0) {
                    char keybuf[4];
                    char* r = VecAdd(keybuf, (char*)&entryValue,
                                     (char*)&gPaintVarModNormal[i * 4]);
                    int out[2];
                    FUN_0053f300(*(int*)r, out);
                    if (*(float*)&out[0] < 0.0f)
                        edgeMask = edgeMask | bit;
                }
                bit = (unsigned char)(bit << 1);
            }
            applyMask = 0xff;
            *(unsigned char*)(entry + 4) = applyMask;
            *(unsigned char*)(entry + 5) = edgeMask;
        }

        unsigned char varBit = 1;
        for (unsigned int j = 0; j < 6; j = j + 1) {
            if ((varBit & *(unsigned char*)((char*)&entryValue + 3)) == 0) {
                char* tableEntry = (char*)&gPaintVarModExtra[j * 0x20];
                char keybuf[4];
                VecAdd(keybuf, (char*)&entryValue, tableEntry + 8);
                int localKey = *(int*)keybuf;
                unsigned int h = Map1Hash((char*)self + 0x3c, localKey);
                int found = 0;
                bool bFound = false;
                if (h < 0x4000) {
                    int mapBegin = *(int*)(self + 0x3c);
                    if (*(int*)(mapBegin + h * 8) == localKey) {
                        found = *(int*)(mapBegin + 4 + h * 8);
                        bFound = true;
                    }
                }
                if (bFound) {
                    if (*(unsigned int*)(self + 0x34) <= (unsigned int)found
                        ? false : true) {
                        int e2 = *(int*)(self + 0x20) + found * 8;
                        *(unsigned char*)(e2 + 3) = *(unsigned char*)(e2 + 3)
                            | *(unsigned char*)(tableEntry + 3);
                        *(unsigned char*)(e2 + 4) = *(unsigned char*)(e2 + 4)
                            | EvalApplyMode(tableEntry, applyMask & *(unsigned char*)(tableEntry + 3));
                        *(unsigned char*)(e2 + 5) = *(unsigned char*)(e2 + 5)
                            | EvalApplyMode(tableEntry, applyMask & edgeMask);
                    }
                    *(unsigned char*)((char*)&entryValue + 3) =
                        *(unsigned char*)((char*)&entryValue + 3) | varBit;
                } else {
                    *(unsigned int*)(self + 0x1c) = h & 0xffffc000 | *(unsigned int*)(self + 0x1c);
                    unsigned char tv = *(unsigned char*)(tableEntry + 3);
                    unsigned char both = edgeMask & tv;
                    if (both != 0 && both != tv) {
                        int fresh = (int)EvalAllocEntry(self, localKey, h);
                        *(unsigned char*)(fresh + 3) = *(unsigned char*)(tableEntry + 3);
                        *(unsigned char*)(fresh + 4) = *(unsigned char*)(tableEntry + 0xd);
                        *(unsigned char*)(fresh + 5) = EvalApplyMode(tableEntry, edgeMask);
                        *(unsigned char*)((char*)&entryValue + 3) =
                            *(unsigned char*)((char*)&entryValue + 3) | varBit;
                    }
                }
            }
            varBit = (unsigned char)(varBit << 1);
        }

        *(unsigned char*)(entry + 3) = *(unsigned char*)((char*)&entryValue + 3);
        if (*(int*)(self + 0x1c) != 0)
            break;
        if (!EvalFlush(this, entryValue, edgeMask)) {
            result = 0;
            guard.End();
            return result;
        }
        spin = spin + 1;
    }
    result = 0;
    guard.End();
    return result;
}

// @ 0x0053f300
void PaintVarCtx::FUN_0053f300(int key, int* pOut)
{
    char* self = (char*)this;
    unsigned int h = Map2Hash((char*)self + 0x68, key);
    bool bFound = false;
    if (h < 0x8000) {
        int mapBegin = *(int*)(self + 0x68);
        if (*(int*)(mapBegin + h * 0xc) == key) {
            pOut[0] = *(int*)(mapBegin + 4 + h * 0xc);
            pOut[1] = *(int*)(mapBegin + 8 + h * 0xc);
            bFound = true;
        }
    }
    if (!bFound) {
        *(unsigned int*)(self + 0x1c) = h & 0xffff8000 | *(unsigned int*)(self + 0x1c);
        cSPVector3 v;
        EvalScaledAdd(self, &v, (uint32_t)key);
        int count = *(int*)(self + 0x64);
        int tbl = *(int*)(self + 0x50);
        char* te = (char*)(tbl + count * 0x18);
        *(int*)te = key;
        *(cSPVector3*)(te + 0xc) = v;
        *(int*)(te + 4) = -1;
        Evaluator* evaluator = *(Evaluator**)(self + 0x90);
        evaluator->Combine(&v, (cSPVector3*)pOut);
        pOut[1] = count;
        int k0 = pOut[0];
        int k1 = pOut[1];
        int mapBegin = *(int*)(self + 0x68);
        *(int*)(mapBegin + (h & 0x7fff) * 0xc) = key;
        *(int*)(mapBegin + 4 + (h & 0x7fff) * 0xc) = k0;
        *(int*)(mapBegin + 8 + (h & 0x7fff) * 0xc) = k1;
        *(int*)(self + 0x64) = count + 1;
    }
}

// @ 0x0053f4e0
void PaintVarCtx::FUN_0053f4e0()
{
    char* self = (char*)this;
    int ev = *(int*)(self + 0x94);

    EvalInit0((*(int*)(ev + 0xc) - *(int*)(ev + 8)) / 0xc);
    EvalInit1((*(int*)(ev + 0x5c) - *(int*)(ev + 0x58)) >> 2);
    EvalBuild((float*)*(int*)(ev + 0x58),
              (float*)*(int*)(ev + 0x5c),
              (float*)*(int*)(ev + 0x6c));

    for (unsigned int i = 0; ; i = i + 1) {
        if ((unsigned int)((*(int*)(ev + 0xc) - *(int*)(ev + 8)) / 0xc) <= i)
            break;
        cSPVector3* vecA = (cSPVector3*)(*(int*)(ev + 8) + i * 0xc);
        cSPVector3* vecB = (cSPVector3*)(*(int*)(ev + 0x1c) + i * 0xc);
        int* mod = (int*)(*(int*)(ev + 0x1b8) + i * 8);
        float inv = 1.0f / (float)(unsigned int)mod[1];
        Vector3_MulAdd(vecA, &inv);

        Evaluator* evaluator = *(Evaluator**)(self + 0x90);
        char r = evaluator->Combine(vecA, vecB);
        if (r == 0) {
            int tbl = *(int*)(self + 0x50);
            int entry = tbl + 0xc + *(int*)(tbl + mod[0] * 0x18 + 8) * 0x18;
            cSPVector3 interpOut;
            cSPVector3* pv = evaluator->Interp(&interpOut, (cSPVector3*)entry, vecA, 0);
            cSPVector3 a = *pv;
            cSPVector3 blendOut;
            char r2 = evaluator->Blend(*(float*)(self + 0x14), &a,
                                       (cSPVector3*)entry, &blendOut);
            if (r2 == 0) {
                *vecA = a;
                cSPVector3 tmp;
                evaluator->Combine(vecA, &tmp);
                cSPVector3 n;
                Vector3_Normalize(&n, &blendOut);
                cSPVector3 neg;
                Vector3_Negate(&neg, &n);
                *vecA = neg;
            } else {
                *vecA = a;
                cSPVector3 n;
                Vector3_Normalize(&n, &blendOut);
                cSPVector3 neg;
                Vector3_Negate(&neg, &n);
                *vecB = neg;
            }
        } else {
            cSPVector3 n;
            Vector3_Normalize(&n, vecB);
            cSPVector3 neg;
            Vector3_Negate(&neg, &n);
            *vecB = neg;
        }
    }
}
