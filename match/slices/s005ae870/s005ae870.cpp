// slice s005ae870 — SP editor limb / manipulation helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

// ---- engine helpers (masked relocations) -----------------------------------
// Every one of these takes its host object in ecx, so model each as a member of a
// named struct (the migrated markers had omitted the hidden `this`).
void* operator_new(int size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0

struct cSPEditorHandle {
    void* GetEditorBlock();                              // 0x0047e6c0
};
struct cSPEditorLimbStructure {
    cSPEditorLimbStructure* Ctor();                      // 0x00488850
    void* BuildLimb(void* block, bool isEmpty, void* joint);  // 0x004891a0
    void* Joints(void* block);                           // 0x0048b2c0 (block on the stack)
    void* Rebuild(void* block);                          // 0x004898a0 (block on the stack)
};
struct cSPEditorBlock {
    char pad0[0x33c];
    cSPEditorBlock* mParentBlock;                        // +0x33c
    char pad340[0xa0];                                   // +0x340 .. +0x3e0
    cSPEditorLimbStructure* mSkinRegion;                 // +0x3e0  limb structure for the skin region
    bool HasAnyBlockFlag();                              // 0x00435d40 (this = the block)
};
struct ManipImplA { void* Ctor(); };                     // 0x005a8580
struct ManipImplB { void* Ctor(); };                     // 0x005a8e30
struct ManipImplC { void* Ctor(); };                     // 0x005a7890
struct ViewerObj { void  ScreenFit(float x, float y, float* out1, float* out2); };  // 0x007c4730 GetWorldRayFromScreenCoords
void* GetLimbRoot(void* block);                          // 0x004a5e10  EditorUtils::GetLimbRoot (cdecl)
void* FUN_005ae5d0(void* dst, void* first, void* last);  // 0x005ae5d0  copy 0x3c-stride records
void* FUN_0067dd10();                                    // 0x0067dd10  SP::App
// eastl::vector<float>::operator= — thiscall, source on the stack (0x0050d4e0).
struct FloatVec {
    void AssignFrom(void* src);   // 0x0050d4e0
};
extern "C" void* memcpy(void* dst, const void* src, unsigned n);   // CRT 0x11e0744

// Inline eastl vector of unsigned: append with growth.  ecx = the vector object,
// args = (insertion slot, const unsigned& value); 0x004558a0.
struct SPVectorU32 {
    int* begin;   // +0  first element
    int* end;     // +4  past the last element
    int* cap;     // +8  past the end of capacity
    void DoInsertValue(unsigned* pos, const unsigned& value);   // 0x4558a0
};
// Append one value, growing through DoInsertValue when full.
static void VecPush(SPVectorU32& v, unsigned value)
{
    if (v.end < v.cap) {
        if (v.end != 0)
            *v.end = (int)value;
        v.end += 1;
    } else {
        v.DoInsertValue((unsigned*)v.end, value);
    }
}

// The USD-controlled manipulation-limb object.
struct ManipLimb {
    char pad00[0x1c];
    void* mHandle;          // +0x1c  cSPEditorHandle*
    void* mManipImpl;       // +0x20  active manipulation implementation (vtbl)
    void* mPrimaryLimb;     // +0x24  cSPEditorLimbStructure* (target limb, nullable)
    void* mSecondaryLimb;   // +0x28  cSPEditorLimbStructure* (symmetric limb, nullable)
    SPVectorU32 mBlocksA;   // +0x2c  primary-limb block list
    char pad38[8];
    SPVectorU32 mBlocksB;   // +0x40  secondary-limb block list (from mBlock+0x3e0)
    char pad4c[8];
    SPVectorU32 mBlocksC;   // +0x54  parent-limb block list
    char pad60[0x58];
    void* mBlock;           // +0xb8  cSPEditorBlock*
    void* mParentBlock;     // +0xbc
    float mC0;              // +0xc0  mBestTry.mLoc (screen x)
    float mC4;              // +0xc4  mBestTry.mBadness (screen y)
    char padc8[0xc];
    float mD4, mD8, mDC;    // +0xd4  saved position
    float mE0, mE4, mE8;    // +0xe0  saved position (dup)
    float mEC, mF0, mF4;    // +0xec  block position cache
    int   mF8;              // +0xf8  limb kind
    int   mFC;              // +0xfc  limb kind (copy)
    void* m104;             // +0x104 manipulation implementation (owned, vtbl)

    void Init(void* handle, void* block, void* h3, float px, float py, float pz, unsigned char mode);
    float* PickOptimalPointOnLine(float* out, int* block, float x0, float y0, float z0,
                                  float x1, float y1, float z1, int count,
                                  float* samples, float* worstOut, int* bestIndex);
};

// The manipulation implementation exposes its badness score via virtual slot 4 (+0x10).
struct ManipImpl {
    void* vftbl;   // +0
};

// ---- additional engine helpers (masked relocations) ------------------------
// (FUN_0067dd10 / FUN_007c4730 / FUN_0050d4e0 / memcpy already declared above.)

// Badness of a sample: virtual slot +0x10 of the manipulation implementation.
static float ImplBadness(void* impl, int* block, float x, float y, float z,
                         float a, float b, float c, float d, float e, float f)
{
    typedef float (__thiscall* Fn)(void*, int*, float, float, float,
                                   float, float, float, float, float, float);
    Fn fn = *(Fn*)(*(char**)impl + 0x10);
    return fn(impl, block, x, y, z, a, b, c, d, e, f);
}
// Viewer screen-fit: virtual slot +0x58 of the App object.
static void* ViewerSlot(void* app, float x, float y, float* out1, float* out2)
{
    typedef void* (__thiscall* Fn)(void*, float, float, float*, float*);
    Fn fn = *(Fn*)(*(char**)app + 0x58);
    return fn(app, x, y, out1, out2);
}
// CRT sqrt (the original inlines the fsqrt at the call site).  Runs before the
// DllMain CRT init here, so compute it with a small Newton iteration instead.
static float Sqrt(float x)
{
    if (x <= 0.0f)
        return 0.0f;
    float g = x * 0.5f;
    int i = 0;
    if (g < 1.0f)
        g = 1.0f;
    for (i = 0; i < 24; i++)
        g = 0.5f * (g + x / g);
    return g;
}

// @ 0x005ae870 — SP::cSPEditorManipulationLimb::cSPEditorManipulationLimb
// (handle, block, flags) plus out-floats; builds the limb structure from the block.
void ManipLimb::Init(void* handle, void* block, void* h3,
                     float px, float py, float pz, unsigned char mode)
{
    ManipLimb* self = this;
    self->mHandle = h3;
    if (handle != 0) {
        self->mBlock = ((cSPEditorHandle*)handle)->GetEditorBlock();
    } else if ((mode & 8) != 0 && (mode & 2) == 0) {
        void* root = GetLimbRoot(block);
        self->mBlock = root;
        px = (*(float*)((char*)root + 0x48) - *(float*)((char*)block + 0x48)) + px;
        py = py + (*(float*)((char*)root + 0x4c) - *(float*)((char*)block + 0x4c));
        pz = pz + (*(float*)((char*)root + 0x50) - *(float*)((char*)block + 0x50));
    } else {
        self->mBlock = block;
    }

    void* mem = operator_new(0x54, "Editor", 0, 0, 0, 0);
    self->mManipImpl = (mem != 0) ? ((cSPEditorLimbStructure*)mem)->Ctor() : 0;
    bool isEmpty = (handle == 0);
    cSPEditorBlock* blk = (cSPEditorBlock*)self->mBlock;
    ((cSPEditorLimbStructure*)self->mManipImpl)->BuildLimb(blk, isEmpty, 0);
    self->mSecondaryLimb = 0;

    if (*(int*)((char*)blk + 0x3e0) == 0) {
        self->mPrimaryLimb = 0;
        if (handle != 0) {
            cSPEditorBlock* parent = blk->mParentBlock;
            if (parent != 0 && *(int*)((char*)parent + 0x3e0) != 0) {
                mem = operator_new(0x54, "Editor", 0, 0, 0, 0);
                self->mSecondaryLimb = (mem != 0) ? ((cSPEditorLimbStructure*)mem)->Ctor() : 0;
                ((cSPEditorLimbStructure*)self->mSecondaryLimb)->BuildLimb(
                    *(void**)((char*)parent + 0x3e0), false, 0);
            }
        }
    } else {
        mem = operator_new(0x54, "Editor", 0, 0, 0, 0);
        self->mPrimaryLimb = (mem != 0) ? ((cSPEditorLimbStructure*)mem)->Ctor() : 0;
        ((cSPEditorLimbStructure*)self->mPrimaryLimb)->BuildLimb(
            *(void**)((char*)blk + 0x3e0), isEmpty, 0);
    }

    // Collect the joint list from the primary limb into mBlocksA.
    cSPEditorLimbStructure* impl = (cSPEditorLimbStructure*)self->mManipImpl;
    void* joints = impl->Joints(blk);
    void* first = *(void**)((char*)joints + 4);
    if (first == 0) {
        VecPush(self->mBlocksA, (unsigned)joints);
    } else {
        int n = (*(int*)((char*)first + 0xc) - *(int*)((char*)first + 8)) >> 2;
        for (int i = 0; i < n; i++) {
            int* v = (int*)(*(int*)((char*)first + 8) + i * 4);
            VecPush(self->mBlocksA, (unsigned)*v);
        }
    }

    if (self->mPrimaryLimb != 0) {
        joints = ((cSPEditorLimbStructure*)self->mPrimaryLimb)->Joints(
            *(void**)((char*)blk + 0x3e0));
        void* f2 = *(void**)((char*)joints + 4);
        if (f2 == 0) {
            VecPush(self->mBlocksB, (unsigned)joints);
        } else {
            int n = (*(int*)((char*)f2 + 0xc) - *(int*)((char*)f2 + 8)) >> 2;
            for (int i = 0; i < n; i++) {
                int* v = (int*)(*(int*)((char*)f2 + 8) + i * 4);
                VecPush(self->mBlocksB, (unsigned)*v);
            }
        }
    }

    if (self->mSecondaryLimb != 0) {
        joints = ((cSPEditorLimbStructure*)self->mSecondaryLimb)->Joints(
            blk->mParentBlock->mSkinRegion);
        if (joints != 0) {
            int n = (*(int*)((char*)joints + 0xc) - *(int*)((char*)joints + 8)) >> 2;
            for (int i = 0; i < n; i++) {
                int* v = (int*)(*(int*)((char*)joints + 8) + i * 4);
                VecPush(self->mBlocksC, (unsigned)*v);
            }
        }
    }

    // Limb kind / manipulation implementation selection.
    if (handle == 0) {
        self->mF8 = blk->HasAnyBlockFlag() ? 7 : 6;
    } else {
        void* newImpl = 0;
        bool doSwap = false;
        switch (*(int*)((char*)joints + 100)) {
        case 0: self->mF8 = 0; break;
        case 1:
            self->mF8 = 1;
            { void* m = operator_new(0x78, "Editor", 0, 0, 0, 0);
              if (m) newImpl = ((ManipImplA*)m)->Ctor(); }
            doSwap = true;
            break;
        case 2:
            self->mF8 = 2;
            { void* m = operator_new(0x78, "Editor", 0, 0, 0, 0);
              if (m) newImpl = ((ManipImplB*)m)->Ctor(); }
            doSwap = true;
            break;
        case 3:
            { void* m = operator_new(0x78, "Editor", 0, 0, 0, 0);
              if (m) newImpl = ((ManipImplC*)m)->Ctor(); }
            doSwap = true;
            self->mF8 = 3;
            break;
        case 4: self->mF8 = 4; break;
        case 5: self->mF8 = 5; break;
        default: self->mF8 = 3; break;
        }
        if (doSwap) {
            void* old = self->m104;
            if (newImpl != old) {
                if (newImpl != 0)
                    (*(void(__thiscall**)(void*))*(void**)newImpl)(newImpl);   // vtbl slot 0
                self->m104 = newImpl;
                if (old != 0)
                    (*(void(__thiscall**)(void*))((*(void***)old)[1]))(old);   // vtbl slot 1
            }
        }
    }

    if (blk != 0)
        self->mParentBlock = blk->mParentBlock;
    self->mFC = self->mF8;
    self->mD4 = px; self->mE0 = px;
    self->mD8 = py; self->mE4 = py;
    self->mDC = pz; self->mE8 = pz;
    self->mEC = *(float*)((char*)blk + 0x48);
    self->mF0 = *(float*)((char*)blk + 0x4c);
    self->mF4 = *(float*)((char*)blk + 0x50);
    impl->Rebuild(blk);
    if (self->mPrimaryLimb != 0)
        ((cSPEditorLimbStructure*)self->mPrimaryLimb)->Rebuild(
            *(void**)((char*)blk + 0x3e0));
}

// @ 0x005aed80 — SP::cSPEditorManipulationLimb::PickOptimalPointOnLine
// Projects the segment through the active viewer, samples `count` points along it,
// scores each with the manipulation implementation (virtual slot +0x10), and keeps
// the best and worst samples.  Sample records are 9 floats (0x24 bytes) at
// `samples[i]`; x/y/z at +0, badness at +4, and an inline float vector at +0x10.
float* ManipLimb::PickOptimalPointOnLine(float* out, int* block,
                                         float x0, float y0, float z0,
                                         float x1, float y1, float z1,
                                         int count, float* samples, float* worstOut, int* bestIndex)
{
    ManipLimb* self = this;
    float* sampleBase = samples;
    int best = -1;
    int worst = -1;

    if (*(float*)&self->m104 != 0.0f) {
        // App()->viewer (vtbl slot 0x58) with the limb's best-try screen pair.
        void* app = FUN_0067dd10();
        float loc = self->mC0;       // mBestTry.mLoc (screen x)
        float bad = self->mC4;       // mBestTry.mBadness (screen y)
        float local18[3], localc[3];
        void* vwr = ViewerSlot(app, loc, bad, local18, localc);
        ((ViewerObj*)vwr)->ScreenFit(loc, bad, local18, localc);   // GetWorldRayFromScreenCoords

        float s0 = (0.0f <= x0) ? 1.0f : -1.0f;
        float s1 = (0.0f <= x1) ? 1.0f : -1.0f;
        int i = 0;
        if (s0 != s1 || ((*(unsigned*)((char*)*block + 0xdc8) >> 15) & 1) != 0) {
            float dx = x1 - x0;
            float dy = y1 - y0;
            float dz = z1 - z0;
            float inv = 1.0f / Sqrt(dx * dx + dy * dy + dz * dz);
            float nx = inv * dx;
            float t = -(x0 / nx);
            samples[2] = z0 + (inv * dz) * t;
            samples[0] = nx * t + x0;
            samples[1] = y0 + (inv * dy) * t;
            samples[3] = ImplBadness(self->m104, block, samples[0], samples[1], samples[2],
                                     local18[0], local18[1], local18[2],
                                     nx, inv * dy, inv * dz);
            best = 0;
            worst = 0;
            i = 1;
        }

        for (; i < count; i++) {
            float t = (float)i / (float)(count - i - 1);
            float* p = samples + i * 9;
            p[0] = (x0 - x1) * t + x1;
            p[1] = y1 + (y0 - y1) * t;
            p[2] = z1 + (z0 - z1) * t;
            float b = ImplBadness(self->m104, block, p[0], p[1], p[2],
                                  local18[0], local18[1], local18[2],
                                  localc[0], localc[1], localc[2]);
            p[3] = b;
            if (best == -1 || b < samples[best * 9 + 3])
                best = i;
            if (worst == -1 || samples[worst * 9 + 3] <= b)
                worst = i;
        }
    }

    *bestIndex = best;
    worstOut[0] = samples[worst * 9 + 0];
    worstOut[1] = samples[worst * 9 + 1];
    worstOut[2] = samples[worst * 9 + 2];
    worstOut[3] = samples[worst * 9 + 3];
    // eastl::vector<float>::operator=(dst = worstOut+0x10, src = samples[worst]+0x10)
    ((FloatVec*)((char*)worstOut + 0x10))->AssignFrom((char*)(samples + worst * 9) + 0x10);

    out[0] = samples[best * 9 + 0];
    out[1] = samples[best * 9 + 1];
    out[2] = samples[best * 9 + 2];
    out[3] = samples[best * 9 + 3];

    // Trailing int vector (element at samples[best]+0x10 .. +0x14) is copied out with
    // a fresh allocation (operator new, then memcpy).
    int* src = (int*)(samples + best * 9);
    int n = (src[5] - src[4]) >> 2;
    void* mem = 0;
    if (n != 0)
        mem = operator_new(n * 4, "Editor", 0, 0, 0, 0);
    out[4] = (float)(int)mem;
    out[5] = (float)(int)mem;
    out[6] = (float)(int)((int)mem + n * 4);
    int sz = src[5] - src[4];
    memcpy(mem, (void*)src[4], sz);
    out[5] = (float)(int)((int)mem + (sz >> 2) * 4);
    return out;
}

// @ 0x005af1c0 — SP::HighlightVector::clear-like erase helper (stride 0x3c)
struct HighlightVec {
    int  mBegin;   // +0  pointer to first 0x3c-stride record
    int  mEnd;     // +4  pointer past the last record
    void Clear();
};
void HighlightVec::Clear() {
    int first = mBegin;
    int last  = mEnd;
    FUN_005ae5d0((void*)last, (void*)last, (void*)first);   // FUN_005ae5d0(dst, first, last)
    int size = (int)((char*)last - (char*)first);
    int count = size / 0x3c;
    mEnd += count * 0x3c;}
