// Slice s0073afb0 — SP::cModelInstance methods (2008 retail offsets).
//
// Optimized /O2 (no frame pointer).  Retail member offsets differ from the 2008 dev PDB and the
// 2017 ModAPI; offsets below are those observed in the disassembly, gaps are pad.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast.

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef short int16_t;

#include <intrin.h>
#include <math.h>

namespace SP {
bool IsFinite(float f);                // 0x0059ab10 cdecl
void NotifyAdd(void* info, void* blender, void* other, int arg);   // 0x006c1cd0 cdecl
void NotifyAlloc();                    // 0x007c5490
struct cBindInfo;
void __fastcall FinishNotify(cBindInfo* info);   // 0x01200940 (thiscall, no args)
struct cFileAllocator;
struct cResourceSet;

// 8-byte animation/bone group record.
struct cAnimGroupInfo {
    char  mBindingIdx;      // +0
    char  mBoneCount;       // +1
    short mBoneOffset;      // +2
    char  mAnimCount;       // +4
    char  mAnimFirstDeform; // +5
    short mAnimOffset;      // +6
};

struct cAnimDef {                   // animation definition (a KeyframeAnimation)
    char  pad0[8];
    int   mId;                      // +0x08
    char  pad0c[0x14];
    float mLength;                  // +0x20
};
struct cIdObj { char pad0[0x10]; int mId; };       // +0x10 id
struct cBindInfo {                  // per-binding info (three layouts of the same record are read)
    char    pad0[0xc];
    cIdObj* m0c;                    // +0x0c
    cIdObj* m10;                    // +0x10
    char    pad14[4];
    int     m18;                    // +0x18
};
struct cBlender {                   // animation player / cMultiBlender; vptr of the played interface at +4
    int     pad0;
    void**  mVptr4;                 // +0x04
    char    pad8[0x14];
    cAnimDef* mDef;                 // +0x1c
    float   mTime;                  // +0x20
    bool AnyAnimating();                            // 0x0075a6e0 cMultiBlender::AnyAnimating
    void SetWeight(cAnimDef* d, float w);           // 0x0075b630 cMultiBlender::SetWeight
    void SetAnimTime(cAnimDef* d, float t);         // 0x0075b5d0 cMultiBlender::SetAnimTime
    void SetAllTime(float t);                       // 0x0075a690
    void SetAnim(cAnimDef* d, float start);         // 0x011fdba0
    void SetTime(float t);                          // 0x011fe600
};
struct cBinding {                   // 12-byte binding record
    cBlender*  mBlender;            // +0
    bool       mActive;             // +4
    bool       mLoop;               // +5
    short      pad6;
    cBindInfo* mInfo;               // +8
};
struct cAnimEntry { int mKey; cAnimDef* mDef; };   // 8 bytes

// 0xc4-byte material record (only the callback fields used here).
struct cMaterial {
    cBlender*  mBlender;            // +0 (same prefix as cBinding)
    bool       mActive;             // +4
    bool       mLoop;               // +5
    short      pad6;
    cBindInfo* mInfo;               // +8
    char  pad0[0xb8 - 0xc];
    void* f_b8;             // +0xb8
    void* f_bc;             // +0xbc
    void* f_c0;             // +0xc0
};

class cModelInstance {
public:
    char pad0[8];                   // +0x00
    unsigned mFlags8;               // +0x08 (bit 0x20: multi-blender mode)
    int mFieldC;                    // +0x0c
    void* mField10;                 // +0x10
    cAnimGroupInfo* mGroupBegin;    // +0x14
    cAnimGroupInfo* mGroupEnd;      // +0x18
    char pad1c[0x28 - 0x1c];
    cMaterial* mMaterials;          // +0x28
    cMaterial* mMaterialsEnd;       // +0x2c
    int mField30;                   // +0x30 (address forwarded to a virtual call)
    char pad34[0x3c - 0x34];
    cBinding* mBindABegin;          // +0x3c
    cBinding* mBindAEnd;            // +0x40
    char pad44[0x50 - 0x44];
    cBinding* mBindCBegin;          // +0x50
    cBinding* mBindCEnd;            // +0x54
    char pad58[0x64 - 0x58];
    cBlender** mBlendBegin;         // +0x64
    cBlender** mBlendEnd;           // +0x68
    char pad6c[0x78 - 0x6c];
    cAnimEntry* mEntryBegin;        // +0x78
    cAnimEntry* mEntryEnd;          // +0x7c
    char pad80[0x90 - 0x80];
    long long mCounter;             // +0x90
    char pad98[0xc8 - 0x98];
    unsigned short mFlags;          // +0xc8
    char padca[0xcc - 0xca];
    cFileAllocator* mFieldCC;       // +0xcc (packed-file allocator)
    char padd0[0xec - 0xd0];
    void* mDynDraw;                 // +0xec
    cResourceSet* mFieldF0;         // +0xf0 (bound resource set)
    char padf4[0x60];

public:
    bool UpdateBinding(cBinding* e, float dt);       // 0x0073af20
    void Animate(float dt);
    void MoveToTime(int key, int grp, float t);
    void SetWeight(int key, int grp, float w);
    bool GetAnimationRange(int key, int grp, float* pMin, float* pMax);
    void Notify(struct cNotifyOther* other);
    int GetNumBones();                                      // @ 0x0073B7E0
    void SetBoneTable(int a, void* b);                      // @ 0x0073B800
    cMaterial* SetBoneCallback(int boneIndex, void* a2, void* a3, void* a4);   // @ 0x0073B840
    void SetDynamicDraw(void* p, bool flag);                // @ 0x0073B8E0
    bool QueryAllocator(int* a1, int* a2, int* a3, int* a4, int* a5, int* a6, void** a7);  // @ 0x0073B980
    bool Reseat(int v);                                     // @ 0x0073BA50
    void BuildBoneMatrices(void* state);                    // @ 0x0073BB40
};

// @ 0x0073B7E0 — number of bones = last group's bone count + bone offset.
int cModelInstance::GetNumBones()
{
    if (mGroupBegin == mGroupEnd)
        return 0;
    return (int)mGroupEnd[-1].mBoneCount + (int)mGroupEnd[-1].mBoneOffset;
}

// @ 0x0073B800
void cModelInstance::SetBoneTable(int a, void* b)
{
    cAnimGroupInfo* p = mGroupBegin;
    if (p != mGroupEnd && (int)p->mBoneCount < a)
        mFieldC = (int)p->mBoneCount;
    else
        mFieldC = a;
    mField10 = b;
    mCounter += 1;
}

// @ 0x0073B840 — the original leaves eax live at every ret (equiv's void_hides_eax): the material
// record on the store paths, the bone index on the early-outs, and the low-byte-substituted group
// pointer when a binding index is negative.  Return those values.
cMaterial* cModelInstance::SetBoneCallback(int boneIndex, void* a2, void* a3, void* a4)
{
    uint32_t ret = (uint32_t)boneIndex;
    if (boneIndex == -1) {
        if (mGroupBegin == mGroupEnd)
            return (cMaterial*)(uint32_t)ret;
        cAnimGroupInfo* p = mGroupBegin;
        do {
            int idx = (unsigned char)p->mBindingIdx;
            ret = (ret & 0xFFFFFF00u) | (uint32_t)idx;   // mov al, byte ptr [edx]
            if ((signed char)idx >= 0) {
                cMaterial* m = &mMaterials[idx];
                m->f_b8 = a3;
                m->f_c0 = a4;
                m->f_bc = a2;
                ret = (uint32_t)(uint32_t)m;
            }
            p = (cAnimGroupInfo*)((char*)p + 8);
        } while (p != mGroupEnd);
        return (cMaterial*)(uint32_t)ret;
    }
    if (boneIndex < 0)
        return (cMaterial*)(uint32_t)ret;
    if (boneIndex >= (int)(mGroupEnd - mGroupBegin))
        return (cMaterial*)(uint32_t)ret;
    int idx = (unsigned char)mGroupBegin[boneIndex].mBindingIdx;
    if ((signed char)idx < 0) {
        uint32_t gp = (uint32_t)(void*)&mGroupBegin[boneIndex];
        uint32_t v = (gp & ~0xFFu) | (uint32_t)(unsigned char)idx;
        return (cMaterial*)v;
    }
    cMaterial* m = &mMaterials[idx];
    m->f_b8 = a3;
    m->f_c0 = a4;
    m->f_bc = a2;
    return m;
}

// @ 0x0073B8E0 — set the dynamic-draw object and its flag bit.
struct DynDrawObj {
    void** vftable;                 // +0
    int mnRefCount;                 // +4
};

void cModelInstance::SetDynamicDraw(void* pv, bool flag)
{
    DynDrawObj* p = (DynDrawObj*)pv;
    mFlags = mFlags & 0xfffb;
    if (p != 0) {
        if (flag)
            mFlags |= 4;
        DynDrawObj* dd = (DynDrawObj*)((void*(__thiscall*)(DynDrawObj*))p->vftable[2])(p);
        DynDrawObj* old = (DynDrawObj*)mDynDraw;
        if (dd != old) {
            if (dd != 0)
                ((void(__thiscall*)(DynDrawObj*))dd->vftable[0])(dd);
            mDynDraw = dd;
            if (old != 0)
                ((void(__thiscall*)(DynDrawObj*))old->vftable[1])(old);
        }
        ((void(__thiscall*)(DynDrawObj*, void*))((DynDrawObj*)mDynDraw)->vftable[4])((DynDrawObj*)mDynDraw, &mField30);
        return;
    }
    DynDrawObj* old = (DynDrawObj*)mDynDraw;
    if (old != 0) {
        mDynDraw = 0;
        ((void(__thiscall*)(DynDrawObj*))old->vftable[1])(old);
    }
}

// ---------------------------------------------------------------------------
// Animation drivers
// ---------------------------------------------------------------------------
struct cNotifyOther { char pad0[0x40]; int mField40; };

// Step one binding record (shared prefix of cBinding / cMaterial) by dt.
static __forceinline void StepBinding(cModelInstance* self, cBinding* e, float dt, bool& any)
{
    float t = dt;
    cBlender* b = e->mBlender;
    if (b != 0 && e->mActive) {
        if (self->mFlags8 & 0x20) {
            if (!b->AnyAnimating())
                return;
            ((void(__thiscall*)(cBlender*, float))e->mBlender->mVptr4[0])(e->mBlender, dt);
        } else {
            float end = b->mDef->mLength;
            float cur = b->mTime;
            if (e->mLoop && cur + dt >= end) {
                t = end - cur;
                e->mActive = false;
            }
            ((void(__thiscall*)(cBlender*, float))b->mVptr4[0])(b, t);
        }
        any = true;
    }
}

// @ 0x0073AFB0
void cModelInstance::Animate(float dt)
{
    bool any = false;
    int n = (int)(mBindAEnd - mBindABegin);
    for (int i = 0; i < n; i++) {
        if (UpdateBinding(mBindABegin + i, dt))
            any = true;
    }
    n = (int)(mMaterialsEnd - mMaterials);
    for (int i = 0; i < n; i++)
        StepBinding(this, (cBinding*)(mMaterials + i), dt, any);
    n = (int)(mBindCEnd - mBindCBegin);
    for (int i = 0; i < n; i++)
        StepBinding(this, mBindCBegin + i, dt, any);
    if (any)
        mCounter += 1;
}

// @ 0x0073B530
void cModelInstance::SetWeight(int key, int grp, float w)
{
    if (grp >= 0 && grp < (int)(mGroupEnd - mGroupBegin) && mEntryBegin != mEntryEnd && (mFlags8 & 0x20)) {
        cAnimGroupInfo* g = &mGroupBegin[grp];
        int last = g->mAnimCount + g->mAnimOffset;
        int first = g->mAnimOffset;
        int b0 = g->mBindingIdx;
        int b1 = b0;
        if (g->mBindingIdx != -1)
            b1 = b0 + 1;
        for (int i = first; i < last; i++) {
            if (mEntryBegin[i].mKey == key) {
                cAnimDef* d = mEntryBegin[i].mDef;
                int n = (int)(mBindAEnd - mBindABegin);
                for (int j = 0; j < n; j++) {
                    cBinding* e = mBindABegin + j;
                    if (e->mInfo->m10->mId == d->mId)
                        e->mBlender->SetWeight(d, w);
                }
                for (int m = b0; m < b1; m++) {
                    cMaterial* mat = mMaterials + m;
                    if (mat->mInfo->m0c->mId == d->mId)
                        mat->mBlender->SetWeight(d, w);
                }
                n = (int)(mBindCEnd - mBindCBegin);
                for (int j = 0; j < n; j++) {
                    cBinding* e = mBindCBegin + j;
                    if (e->mInfo->m18 == d->mId)
                        e->mBlender->SetWeight(d, w);
                }
            }
        }
        mCounter += 1;
    }
}

// @ 0x0073B190
void cModelInstance::MoveToTime(int key, int grp, float t)
{
    if (grp >= 0 && grp < (int)(mGroupEnd - mGroupBegin) && mBlendBegin != mBlendEnd
        && !(fabsf(t) > 10000.0f) && IsFinite(t)) {
        cAnimGroupInfo* g = &mGroupBegin[grp];
        int last = g->mAnimCount + g->mAnimOffset;
        int first = g->mAnimOffset;
        int b0 = g->mBindingIdx;
        int b1;
        if (g->mBindingIdx != -1)
            b1 = b0 + 1;
        else
            b1 = b0;
        if (mFlags8 & 0x20) {
            if (key == 0) {
                int n = (int)(mBlendEnd - mBlendBegin);
                for (int i = 0; i < n; i++)
                    mBlendBegin[i]->SetAllTime(t);
            } else {
                for (int i = first; i < last; i++) {
                    if (mEntryBegin[i].mKey == key) {
                        cAnimDef* d = mEntryBegin[i].mDef;
                        int n = (int)(mBindAEnd - mBindABegin);
                        for (int j = 0; j < n; j++) {
                            cBinding* e = mBindABegin + j;
                            if (e->mInfo->m10->mId == d->mId)
                                e->mBlender->SetAnimTime(d, t);
                        }
                        for (int m = b0; m < b1; m++) {
                            cMaterial* mat = mMaterials + m;
                            if (mat->mInfo->m0c->mId == d->mId)
                                mat->mBlender->SetAnimTime(d, t);
                        }
                        n = (int)(mBindCEnd - mBindCBegin);
                        for (int j = 0; j < n; j++) {
                            cBinding* e = mBindCBegin + j;
                            if (e->mInfo->m18 == d->mId)
                                e->mBlender->SetAnimTime(d, t);
                        }
                    }
                }
            }
        } else {
            for (int i = first; i < last; i++) {
                if (mEntryBegin[i].mKey == key) {
                    cAnimDef* d = mEntryBegin[i].mDef;
                    int n = (int)(mBindAEnd - mBindABegin);
                    for (int j = 0; j < n; j++) {
                        cBinding* e = mBindABegin + j;
                        if (e->mInfo->m10->mId == d->mId) {
                            cBlender* b = e->mBlender;
                            if (d != b->mDef)
                                b->SetAnim(d, 0.0f);
                            b->SetTime(t);
                            e->mActive = false;
                        }
                    }
                    for (int m = b0; m < b1; m++) {
                        cMaterial* mat = mMaterials + m;
                        if (mat->mInfo->m0c->mId == d->mId) {
                            cBlender* b = mat->mBlender;
                            if (d != b->mDef)
                                b->SetAnim(d, 0.0f);
                            b->SetTime(t);
                            mat->mActive = false;
                        }
                    }
                    n = (int)(mBindCEnd - mBindCBegin);
                    for (int j = 0; j < n; j++) {
                        cBinding* e = mBindCBegin + j;
                        if (e->mInfo->m18 == d->mId) {
                            cBlender* b = e->mBlender;
                            if (d != b->mDef)
                                b->SetAnim(d, 0.0f);
                            b->SetTime(t);
                            e->mActive = false;
                        }
                    }
                }
            }
        }
        mCounter += 1;
    }
}

// @ 0x0073B6D0
bool cModelInstance::GetAnimationRange(int key, int grp, float* pMin, float* pMax)
{
    if (grp >= 0 && grp < (int)(mGroupEnd - mGroupBegin)) {
        cAnimGroupInfo* g = mGroupBegin + grp;
        int first = g->mAnimOffset;
        int last = g->mAnimCount + first;
        float mx = 0.0f;
        for (int i = first; i < last; i++) {
            if (mEntryBegin[i].mKey == key && mx < mEntryBegin[i].mDef->mLength)
                mx = mEntryBegin[i].mDef->mLength;
        }
        *pMin = 0.0f;
        *pMax = mx;
        if (mx > 0.0f)
            return true;
        return false;
    }
    return false;
}

// @ 0x0073BAB0
void cModelInstance::Notify(cNotifyOther* other)
{
    if (mBlendBegin != mBlendEnd) {
        cBinding* e = mBindABegin;
        cBinding* end = mBindAEnd;
        for (; e != end; e++) {
            if (e->mBlender != 0) {
                ((void(__thiscall*)(cBlender*))e->mBlender->mVptr4[3])(e->mBlender);
                NotifyAdd(e->mInfo, e->mBlender, other, other->mField40);
            }
        }
        cBinding* f = mBindCBegin;
        cBinding* fend = mBindCEnd;
        for (; f != fend; f++) {
            if (f->mInfo != 0) {
                cBlender* bl = f->mBlender;
                if (bl != 0) {
                    ((void(__thiscall*)(cBlender*))bl->mVptr4[3])(bl);
                    *(cBlender**)f->mInfo = f->mBlender;
                    FinishNotify(f->mInfo);
                } else {
                    NotifyAlloc();
                }
            }
        }
    }
}

} // namespace SP

// ---------------------------------------------------------------------------
// @ 0x0073BDC0 — release a refcounted object stored at this+0xc.
// ---------------------------------------------------------------------------
struct RefObjR {
    void** vftable;                 // +0
    int mnRefCount;                 // +4
};

struct RefHolderC {
    char pad0[0xc];
    void* mpObj;                    // +0xc
    void Release();
};

void RefHolderC::Release()
{
    RefObjR* p = (RefObjR*)mpObj;
    if (p != 0) {
        int n = (*(volatile int*)&p->mnRefCount += -1);
        if (n == 0) {
            (*(volatile int*)&p->mnRefCount) = 1;
            _ReadWriteBarrier();
            ((void(__thiscall*)(RefObjR*, int))p->vftable[0])(p, 1);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x0073BD60 — collect textures and materials into a manager.
// ---------------------------------------------------------------------------
struct Model47;                                    // fwd
extern "C" void TextureCollect(void* tex, void* a, void* b);   // 0x007140E0
extern "C" void MaterialCollect(void* mat, void* a, void* b);  // 0x00713E20

struct Model47 {
    char pad0[0x30];
    void** mTexBegin;               // +0x30
    void** mTexEnd;                 // +0x34
    char pad38[0xc];
    void** mMatBegin;               // +0x44
    void** mMatEnd;                 // +0x48
    void Collect(void* a, void* b);
};

void Model47::Collect(void* a, void* b)
{
    void** p = mMatBegin;
    void** end = mMatEnd;
    for (; p != end; ++p) {
        if (*p != 0)
            TextureCollect(*p, a, b);
    }
    p = mTexBegin;
    end = mTexEnd;
    for (; p != end; ++p)
        MaterialCollect(*p, a, b);
}

namespace SP {

// ---------------------------------------------------------------------------
// @ 0x0073B980 — describe the packed-file allocator bound at +0xcc: element
// size (0x10), the two capacity limits and the format table entries.
// ---------------------------------------------------------------------------
struct cAllocLayout {
    char pad0[0x34];
    int  m34;                       // +0x34
    int  m38;                       // +0x38
    int* m3c;                       // +0x3c (vertex format table)
};

struct cFileAllocator {
    void**        vftable;          // +0
    cAllocLayout* GetLayout();      // 0x007F54D0
    int           GetFormat();      // 0x00762380
};

bool cModelInstance::QueryAllocator(int* a1, int* a2, int* a3, int* a4, int* a5, int* a6,
                                    void** a7)
{
    if (mFieldCC != 0) {
        cAllocLayout* layout = mFieldCC->GetLayout();
        *a1 = 0x10;
        *a2 = 0x10;
        *a5 = layout->m38;
        *a6 = layout->m34;
        *a3 = mFieldCC->GetFormat();
        *a4 = layout->m3c[2];
        ((void(__thiscall*)(cFileAllocator*))mFieldCC->vftable[0])(mFieldCC);
        *a7 = mFieldCC;
        return true;
    }
    *a2 = 0;
    *a1 = 0;
    *a5 = 0;
    *a6 = 0;
    *a4 = 0;
    *a3 = 0;
    *a7 = 0;
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0073BA50 — rebind the first material of the resource set at +0xf0 to a
// new bind-info value, prepare it, then restore the previous value.
// ---------------------------------------------------------------------------
struct cBindCtx {
    int  GetValue();                // 0x00FCC210 (thiscall)
    void SetValue(int v);           // 0x00FCCDD0 (thiscall)
};
void __cdecl    F796650(void* p);                              // 0x00796650
void __cdecl    PrepareMaterial(cMaterial* m, void* extra);    // 0x0073A900

struct cResourceSet {
    char  pad0[0x28];
    cMaterial* mBegin;              // +0x28
    cMaterial* mEnd;                // +0x2c
};

bool cModelInstance::Reseat(int v)
{
    if (mFieldF0->mBegin == mFieldF0->mEnd)
        return false;
    cMaterial* m = mFieldF0->mBegin;
    cBindCtx* ctx = (cBindCtx*)m->mInfo;
    int saved = ctx->GetValue();
    ctx->SetValue(v);
    PrepareMaterial(m, 0);
    ctx->SetValue(saved);
    F796650(0);
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x0073BB40 — rebuild the per-bone 3x4 matrices in the shared table:
// per-group material preparation, then identity-filling of unbound ranges and
// a final upload of the instance's own bone table.
// ---------------------------------------------------------------------------
struct cBoneMatrix {                // 0x30 (3x4 floats)
    float m[12];
};

struct cBoneArg {                   // argument block for PrepareMaterial
    cBoneMatrix* mMatrices;         // +0x00
    int          mCount;            // +0x04
};

struct cBoneState {                 // caller-owned scratch
    char pad0[0x48];
    bool mDone;                     // +0x48
    char pad49[3];
    int  mCount;                    // +0x4c
};

cBoneMatrix    gBoneMatrices[0x100];                // 0x0162B870
extern unsigned char* gShaderFlag;                  // 0x016F6EE0
void __cdecl SetShaderParam(int id, int value, int extra);   // 0x00777AE0

void cModelInstance::BuildBoneMatrices(void* statev)
{
    cBoneState* state = (cBoneState*)statev;
    int nGroups = (int)(mGroupEnd - mGroupBegin);
    state->mCount = mFieldC;
    bool done = (mFieldC == 0) ? (mBlendBegin == mBlendEnd) : (mField10 == 0);
    state->mDone = done;
    if (mGroupBegin != mGroupEnd && mGroupBegin->mBindingIdx == -1 &&
        mGroupBegin->mBoneCount > 0 && mField10 == 0)
        state->mDone = true;
    if (state->mDone)
        return;
    if (nGroups > 1) {
        cAnimGroupInfo* last = mGroupEnd - 1;
        int n = (int)last->mBoneCount + (int)last->mBoneOffset;
        if (state->mCount < n)
            state->mCount = n;
    }
    if (state->mCount >= 0x100)
        state->mCount = mFieldC;
    if (mFieldC != 0 && mFieldC >= state->mCount)
        return;

    bool failed = false;
    for (int i = 0; i < nGroups; i++) {
        cAnimGroupInfo* g = &mGroupBegin[i];
        if (g->mBindingIdx != -1) {
            cMaterial* mat = &mMaterials[(signed char)g->mBindingIdx];
            cBoneArg arg;
            void* parg = 0;
            if (state->mCount != 0) {
                arg.mMatrices = &gBoneMatrices[g->mBoneOffset];
                arg.mCount = g->mBoneCount;
                parg = &arg;
            }
            PrepareMaterial(mat, parg);
            cBlender* b = mat->mBlender;
            if (b != 0) {
                if ((unsigned char)(*(unsigned int*)((char*)b + 0xc) >> 8) > 3)
                    failed = true;
            }
        } else {
            int cnt = g->mBoneCount;
            if (cnt <= 0)
                continue;
            int off = g->mBoneOffset;
            int last = cnt + off;
            if (last <= mFieldC)
                continue;
            if (off < mFieldC)
                off = mFieldC;
            int count = last - off;
            cBoneMatrix identity;
            memset(&identity, 0, sizeof(identity));
            identity.m[0] = 1.0f;
            identity.m[5] = 1.0f;
            identity.m[10] = 1.0f;
            cBoneMatrix* dst = &gBoneMatrices[off];
            if (count != 0) {
                memcpy(dst, &identity, sizeof(identity));
                memcpy(dst + 1, dst, (count - 1) * sizeof(identity));
            }
        }
    }
    int v = 0;
    if (failed && gShaderFlag != 0 && (*gShaderFlag & 1))
        v = 8;
    SetShaderParam(0x207, v, 0);
    if (mFieldC != 0)
        memcpy(gBoneMatrices, mField10, mFieldC * sizeof(cBoneMatrix));
}

} // namespace SP

// ---------------------------------------------------------------------------
// @ 0x0073BDF0 — bone/weight vertex-attribute lookup.
//
// Walks the section's vertex format table looking for the element array that
// matches the requested format id (and the optional key filters), then
// resolves the value through the two element-array indirections.
// ---------------------------------------------------------------------------
struct cEltRefV {                   // 0x10
    int            mNumElts;        // +0x00
    unsigned char* mData;           // +0x04
    unsigned short mEltSize;        // +0x08
    unsigned short mEltStride;      // +0x0a
    void*          mDataRC;         // +0x0c
};

struct cFmtEntryV {                 // 4 bytes
    short mElts;                    // +0x00 (element-array index)
    short mIndices;                 // +0x02 (per-bone array index)
};

struct cMDEltsV {                   // 0x20
    int      m0;                    // +0x00
    int      m4;                    // +0x04
    int      m8;                    // +0x08
    int      mC;                    // +0x0c
    cEltRefV mRef;                  // +0x10
};

struct cMDSectionV {                // 0x8c
    cEltRefV      mVertIndices;     // +0x00
    int           mNumVertices;     // +0x10
    cFmtEntryV*   mFormatBegin;     // +0x14
    cFmtEntryV*   mFormatEnd;       // +0x18
    char          pad1c[0x44 - 0x1c];
    cEltRefV*     mEltsBegin;       // +0x44
    cEltRefV*     mEltsEnd;         // +0x48
};

struct cMeshDataV {                 // 0x58
    void*       vftable;            // +0x00
    int         mRefCount;          // +0x04
    cMDEltsV*   mEltBegin;          // +0x08
    cMDEltsV*   mEltEnd;            // +0x0c
    cMDEltsV*   mEltCap;            // +0x10
    char        pad14[0x8];
    cMDSectionV* mSectionBegin;     // +0x1c
};

extern const int gEltMask[8];       // 0x0140D5AC (mask per element size)

struct cBoneVertexRef {
    void* mMesh;                    // +0x00
    char  pad4[4];
    int   mSection;                 // +0x08
    char  padc[4];
    int   mVertexBase;              // +0x10
    int   mVertexCount;             // +0x14
    bool LookupBone(int* out, int match, int vertexIdx, int key, int key2);
};

bool cBoneVertexRef::LookupBone(int* out, int match, int vertexIdx, int key, int key2)
{
    if (vertexIdx < 0 || vertexIdx >= mVertexCount)
        return false;
    vertexIdx += mVertexBase;
    cMeshDataV* md = (cMeshDataV*)mMesh;
    cMDSectionV* sec = (cMDSectionV*)((char*)md->mSectionBegin + mSection * 0x8c);
    cMDEltsV* elts = md->mEltBegin;
    int nFmt = (int)(sec->mFormatEnd - sec->mFormatBegin);
    int fmt;
    int i;
    for (i = 0; i < nFmt; i++) {
        fmt = sec->mFormatBegin[i].mElts;
        cMDEltsV* e = &elts[fmt];
        if ((key == 0 || e->m0 == key) && (key2 == -1 || e->m4 == key2) &&
            e->m8 == match)
            break;
    }
    if (i >= nFmt)
        return false;

    cMDEltsV* ea = &elts[fmt];
    int val;
    if (sec->mVertIndices.mData != 0)
        val = *(int*)(sec->mVertIndices.mData + sec->mVertIndices.mEltStride * vertexIdx)
              & gEltMask[sec->mVertIndices.mEltSize];
    else
        val = vertexIdx;
    if (sec->mEltsBegin != sec->mEltsEnd) {
        cEltRefV* r = &sec->mEltsBegin[sec->mFormatBegin[i].mIndices];
        if (r->mData != 0)
            val = *(int*)(r->mData + r->mEltStride * val) & gEltMask[r->mEltSize];
    }
    *out = *(int*)(ea->mRef.mData + ea->mRef.mEltStride * val);
    return true;
}
