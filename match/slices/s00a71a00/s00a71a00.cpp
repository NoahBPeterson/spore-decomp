// Slice s00a71a00: EA::Swarm::cEffectsWorld - visual-effect state / LOD update.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /fp:fast /arch:SSE
#include "types.h"

// ---------------------------------------------------------------- class shells
// A 0x38-byte transform (EA::Swarm::cSPTransform / cTransform).
struct cSPTransform { unsigned int mData[0x0e]; };

// A 0x84-byte component definition (one entry of cVEDescription::mpCompDefs).
struct cVECompDef {
    char           pad00[0x04];
    unsigned int   mFlags;          // +0x04
    char           pad08[0x38];
    unsigned char  mLODMin;         // +0x40
    unsigned char  mLODMax;         // +0x41
    char           pad42[0x2e];
    unsigned int   mMaskA;          // +0x70
    unsigned int   mMaskB;          // +0x74
    unsigned short mProbThreshold;  // +0x78
    unsigned short mProbStep;       // +0x7a
    float          mBlend;          // +0x7c
    int            m80;             // +0x80
};

// A 0x5c-byte live-component record (one entry of cVisualEffect::mRecBegin..mRecEnd).
struct cVECompRec {
    char           pad00[0x38];
    void*          mComponent;      // +0x38
    int            mDefIndex;       // +0x3c
    char           pad40[0x04];
    unsigned int   mFlags;          // +0x44
    unsigned int*  mIdxBegin;       // +0x48
    unsigned int*  mIdxEnd;         // +0x4c
    unsigned int*  mIdxCap;         // +0x50
    char           pad54[0x08];
};

// A 0x58-byte effect description (cVEDescription).
struct cVEDescription {
    unsigned int   mFlags;          // +0x00
    char           pad04[0x40];
    cVECompDef*    mpCompDefs;      // +0x44
    cVECompDef*    mpCompDefsEnd;   // +0x48
};

// Out-parameter block of cEffectsWorld::CreateComponentFromDescription.
struct cVECreateOut {
    int            mOut;            // +0x00
    cSPTransform   mXform;          // +0x04
    void*          mComponent;      // +0x3c
    char           pad40[0x0c];
    void*          mBuffer;         // +0x4c
};

// The visual-effect element.  +0x20 is a packed effect handle (24-bit record index |
// 8-bit description-table index); the component-type byte the state filters read is the
// high byte of that same dword, so the two views are unioned.
struct cVisualEffect {
    char pad00[0x18];
    int  m18;                     // +0x18
    int  m1c;                     // +0x1c
    union {
        int m20;                                          // +0x20 packed effect handle
        struct { char _pad20[3]; signed char mComponentType; };   // +0x23
    };
    char pad24[0x04];
    int  m28;                     // +0x28 description pointer
    unsigned int m2c;             // +0x2c flags
    char pad30[0x18];
    int  m48;                     // +0x48 current LOD
    float m4c;                    // +0x4c LOD blend
    char pad50[0x84];
    cSPTransform mD4;             // +0xd4
    cSPTransform m10c;            // +0x10c
    cVECompRec* mRecBegin;        // +0x144
    cVECompRec* mRecEnd;          // +0x148
    cVECompRec* mRecCap;          // +0x14c
    char pad150[0x2c];
    int  m17c;                    // +0x17c

    void UpdateDescription(void* desc);   // 0x00a823e0
};

// The manager that owns the description tables (cEffectsWorld::mManager).
struct EffectsManager {
    char  pad00[0x2c];
    void** mTables;    // +0x2c array of description-table pointers
    char  pad30[0x1c];
    int   m4c;         // +0x4c
    char  pad50[0x18];
    int   m68;         // +0x68
    int   ResolveEffectName(int a, int b);   // 0x00a6d7b0
};

// The effects world.  Field offsets recovered from the sibling slice s00a6ff50
// (cEffectsWorld : IWorldVtbl, GmeRefCount) plus this slice's disassembly.
struct cEffectsWorld {
    char             pad00[0x14];
    EffectsManager*  mManager;     // +0x14
    char             pad18[0x08];
    int              mState;       // +0x20
    char             pad24[0x08];
    unsigned int     mFlags;       // +0x2c
    cVisualEffect**  mVE;          // +0x30 begin
    cVisualEffect**  mVEend;       // +0x34 end
    cVisualEffect**  mVEcap;       // +0x38 cap
    char             pad3c[0x1c];
    int*             mActive;      // +0x58 begin
    int*             mActiveEnd;   // +0x5c end
    int*             mActiveCap;   // +0x60 cap

    void ResetVisualEffectDescription(cVisualEffect* effect);      // 0x00a71f90
    void FUN_00a71910(cVisualEffect* effect);                      // 0x00a71910
    void FUN_00a711c0(int arg);                                    // 0x00a711c0
    void ResetVisualEffectDescriptions(int type);                  // 0x00a72010
    void FUN_00a72060(int type);                                   // 0x00a72060
    void SetState(int state);                                      // 0x00a720b0
    void UpdateVisualEffect(cVisualEffect* effect, int a, int b);  // 0x00a71a00
    void DeactivateAll();                                          // 0x00a70af0
    void DeactivateUnusedVisualEffects();                          // 0x00a70a40
    static void __stdcall UpdateComponentLODs(void* def, void* rec, int lod);  // 0x00a70400
    void CreateComponentFromDescription(void* def, cSPTransform* pXform, int* pOut,
                                        int a, int b);             // 0x00a70fd0
};

// ---------------------------------------------------------- opaque callees (00a71a00)
void __stdcall FUN_00a70f70(void* dst, void* src);                // 0x00a70f70
void* __cdecl FUN_00a71260(void* a, void* b, void* c);            // 0x00a71260
void __stdcall FUN_00a70980(void* a, void* b);                    // 0x00a70980
void __stdcall FUN_00a70910(cSPTransform* self);                  // 0x00a70910
void __stdcall FUN_00a70cc0(void* p);                             // 0x00a70cc0
void __stdcall FUN_00a717d0(void* self, void* a, void* b);        // 0x00a717d0
void __stdcall FUN_00a828a0();                                    // 0x00a828a0
void* __stdcall FUN_007d5590(void* result, void* a, void* b, void* c);   // 0x007d5590
void* __stdcall cSPTransformOps_Assign(void* dst, void* src);     // 0x00537dc0
void __stdcall operator_delete__(void* p);                        // 0x00f47380
void __stdcall DoInsertValue_SI(void* vec, unsigned int* p, const unsigned int* v);  // 0x004558a0
extern char g_sRandom;                                            // 0x016778dc
unsigned int __stdcall RandomUint32Uniform(void* rng, unsigned int range);   // 0x00a68fb0

// @ 0x00a72010
void cEffectsWorld::ResetVisualEffectDescriptions(int type)
{
    int* p = mActive;
    if (p != mActiveEnd) {
        do {
            cVisualEffect* effect = mVE[*p];
            if (type < 0 || type == effect->mComponentType)
                ResetVisualEffectDescription(effect);
            ++p;
        } while (p != mActiveEnd);
    }
    FUN_00a711c0(1);
}

// @ 0x00a72060
void cEffectsWorld::FUN_00a72060(int type)
{
    int* p = mActive;
    if (p != mActiveEnd) {
        do {
            cVisualEffect* effect = mVE[*p];
            if (type < 0 || type == effect->mComponentType) {
                FUN_00a71910(effect);
                ResetVisualEffectDescription(effect);
            }
            ++p;
        } while (p != mActiveEnd);
    }
    FUN_00a711c0(1);
}

// @ 0x00a71f90
void cEffectsWorld::ResetVisualEffectDescription(cVisualEffect* effect)
{
    int a = effect->m18;
    int b = effect->m1c;
    effect->m20 = -1;
    if ((a & b) != -1)
        effect->m20 = mManager->ResolveEffectName(a, b);

    if (effect->m20 >= 0) {
        int handle = effect->m20;
        void** tables = mManager->mTables;
        effect->UpdateDescription((void*)((handle & 0xffffff) * 0x58 +
            *(int*)((char*)tables[handle >> 0x18] + 0x34)));
    } else {
        effect->m28 = 0;
    }

    int old = effect->m48;
    effect->m48 = 0;
    UpdateVisualEffect(effect, old, 1);
}

// @ 0x00a720b0
void cEffectsWorld::SetState(int state)
{
    if (state == mState)
        return;
    if (state == 5) {
        DeactivateAll();
        mState = 5;
        return;
    }

    if (state == 2) {
        for (int* p = mActive; p != mActiveEnd; ++p)
            FUN_00a71910(mVE[*p]);
    } else {
        if (mState == 2)
            ResetVisualEffectDescriptions(-1);
    }
    if (state == 3 || mState == 3) {
        bool bVar3 = (state == 3);
        if (bVar3)
            DeactivateUnusedVisualEffects();
        for (cVisualEffect** v = mVE; v != mVEend; ++v) {
            (*(void(__thiscall**)(cVisualEffect*, int))(*(int*)*v + 0x30))(*v, bVar3);
            (*(void(__thiscall**)(cVisualEffect*, int))(*(int*)*v + 0x2c))(*v, bVar3);
        }
    }
    if (state == 1 || mState == 1) {
        bool b = (state == 1);
        for (cVisualEffect** v = mVE; v != mVEend; ++v)
            (*(void(__thiscall**)(cVisualEffect*, int))(*(int*)*v + 0x2c))(*v, b);
    }
    mState = state;
}

// @ 0x00a71a00
// Applies a new level of detail to one effect: pass 1 drops the live components whose
// definition no longer matches the new LOD / mask / flag tests, pass 2 instantiates the
// definitions the new LOD wants (with the per-definition probability gate) and hands the
// whole set to ApplyParams.
void cEffectsWorld::UpdateVisualEffect(cVisualEffect* effect, int lod, int flag)
{
    char* eff = (char*)effect;
    unsigned int handle = *(unsigned int*)(eff + 0x20);
    if ((int)handle >= 0) {
        // ---- pass 1: prune the live-component vector ----
        if (*(int*)(eff + 0x144) != *(int*)(eff + 0x148)) {
            cVECompRec** recBegin = (cVECompRec**)(eff + 0x144);
            cVEDescription* desc = (cVEDescription*)((handle & 0xffffff) * 0x58 +
                *(int*)((char*)mManager->mTables[(int)handle >> 0x18] + 0x34));
            unsigned int count = (*(int*)(eff + 0x148) - *(int*)(eff + 0x144)) / 0x5c;
            unsigned int kept = 0;
            unsigned int i = 0;
            unsigned int recOff = 0;
            unsigned int keepOff = 0;
            if (count != 0) {
                do {
                    cVECompRec* rec = (cVECompRec*)((char*)*recBegin + recOff);
                    cVECompDef* def = (cVECompDef*)(rec->mDefIndex * 0x84 + (char*)desc->mpCompDefs);
                    if (lod < (int)def->mLODMin || (int)def->mLODMax <= lod ||
                        (mManager->m68 & (int)def->mMaskB) != (int)def->mMaskA ||
                        ((rec->mFlags >> 7) & 1) != 0) {
                        int v = mManager->m4c;
                        unsigned int df = desc->mFlags;
                        if (((df >> 5) & 1) || ((df >> 0x14) & 1))
                            v = 1;
                        else if ((df >> 0x15) & 1)
                            v = 0;
                        (*(void(__thiscall**)(void*, int))(*(int*)rec->mComponent + 0xc))(rec->mComponent, v);
                        if (v == 0) {
                            char r = (*(char(__thiscall**)(void*))(*(int*)rec->mComponent + 0x10))(rec->mComponent);
                            if (r != 0) {
                                if (((rec->mFlags >> 7) & 1) == 0) {
                                    rec->mFlags |= 0x80;
                                    if (0.5f <= *(float*)(eff + 0x4c))
                                        rec->mFlags |= 0x100;
                                    else
                                        rec->mFlags &= ~0x100u;
                                }
                                goto keep1;
                            }
                        }
                        (*(void(__thiscall**)(void*))(*(int*)rec->mComponent + 4))(rec->mComponent);
                        if (rec->mComponent != 0) {
                            void* comp = rec->mComponent;
                            rec->mComponent = 0;
                            (*(void(__thiscall**)(void*))(*(int*)comp + 0x38))(comp);
                        }
                        goto next1;
                    }
                    if (lod != *(int*)(eff + 0x48))
                        UpdateComponentLODs(def, rec, lod);
                keep1:
                    if (i != kept)
                        FUN_00a70f70((char*)*recBegin + keepOff, rec);
                    ++kept;
                    keepOff += 0x5c;
                next1:
                    recOff += 0x5c;
                    ++i;
                } while (i < count);
            }
            // erase the dropped tail of the vector
            {
                int end = *(int*)(eff + 0x148);
                int newEnd = (int)kept * 0x5c + (int)*recBegin;
                void* res = FUN_00a71260((void*)end, (void*)end, (void*)newEnd);
                FUN_00a70980(res, (void*)end);
                *(int*)(eff + 0x148) = end + ((end - newEnd) / 0x5c) * 0x5c;
            }
        }

        // ---- pass 2: instantiate the components the new LOD needs ----
        {
            unsigned int h2 = *(unsigned int*)(eff + 0x20);
            cVEDescription* desc2 = (cVEDescription*)((h2 & 0xffffff) * 0x58 +
                *(int*)((char*)mManager->mTables[(int)h2 >> 0x18] + 0x34));
            unsigned int defCount = (*(int*)((char*)desc2 + 0x48) - *(int*)((char*)desc2 + 0x44)) / 0x84;
            unsigned int prevThresh = 0;
            unsigned int probAcc = 0;
            unsigned int randThresh = 0;
            unsigned char alreadyCreated = 0;
            unsigned char anyCreated = 0;
            unsigned int idx = 0;
            if (defCount != 0) {
                do {
                    cVECompDef* def = (cVECompDef*)(idx * 0x84 + *(int*)((char*)desc2 + 0x44));
                    bool lodOk = !(lod < (int)def->mLODMin || (int)def->mLODMax <= lod ||
                                   (mManager->m68 & (int)def->mMaskB) != (int)def->mMaskA);
                    bool curOk = !(*(int*)(eff + 0x48) < (int)def->mLODMin ||
                                   (int)def->mLODMax <= *(int*)(eff + 0x48) ||
                                   (mFlags & def->mMaskB) != def->mMaskA);
                    if (def->m80 >= 0 && !curOk && lodOk) {
                        if (def->mProbThreshold != 0) {
                            if (def->mProbThreshold != prevThresh) {
                                randThresh = RandomUint32Uniform(&g_sRandom, 0x10000);
                                probAcc = 0;
                            }
                            probAcc += def->mProbStep;
                            prevThresh = def->mProbThreshold;
                            if (probAcc < randThresh)
                                goto nextDef;
                            randThresh = 0x10000;
                        } else {
                            prevThresh = def->mProbThreshold;
                        }
                        bool bit3 = ((def->mFlags >> 3) & 1) != 0;
                        anyCreated = 1;
                        if (alreadyCreated == 0) {
                            cVECreateOut out;
                            FUN_00a70910(&out.mXform);
                            CreateComponentFromDescription(def, &out.mXform, &out.mOut,
                                *(int*)(eff + 0x17c), (int)h2);
                            void* component = out.mComponent;
                            if (component != 0) {
                                UpdateComponentLODs(def, &out.mXform, lod);
                                cSPTransformOps_Assign(&out.mXform, (char*)def + 8);
                                float blend = def->mBlend;
                                (void)blend;
                                cSPTransform tr;
                                void* p = FUN_007d5590(&tr, (char*)def + 8, eff + 0x10c, eff + 0xd4);
                                (*(void(__thiscall**)(void*, void*))(*(int*)component + 0x18))(component, p);
                                if ((mFlags >> 1) & 1)
                                    (*(void(__thiscall**)(void*, int))(*(int*)component + 0x28))(component, 0);
                                if (((mFlags >> 9) & 1) && !((mFlags >> 0xa) & 1)) {
                                    (*(void(__thiscall**)(void*, int))(*(int*)component + 8))(component, flag);
                                    if (flag == 1)
                                        mFlags |= 0x100;
                                }
                                if (*(int*)(eff + 0x148) < *(int*)(eff + 0x14c)) {
                                    void* slot = (void*)*(int*)(eff + 0x148);
                                    *(int*)(eff + 0x148) = (int)slot + 0x5c;
                                    if (slot != 0)
                                        FUN_00a70cc0(&out.mXform);
                                } else {
                                    FUN_00a717d0((void*)*(int*)(eff + 0x144),
                                        (void*)*(int*)(eff + 0x148), &out.mXform);
                                }
                            }
                            if (out.mBuffer != 0 && *(int*)((char*)out.mBuffer - 4) != 0)
                                operator_delete__(out.mBuffer);
                            if (out.mComponent != 0)
                                (*(void(__thiscall**)(void*))(*(int*)out.mComponent + 0x38))(out.mComponent);
                        }
                        if (bit3) {
                            char* v = (char*)*(int*)(eff + 0x148) - 0x14;
                            unsigned int* e = *(unsigned int**)(v + 4);
                            if (e < *(unsigned int**)(v + 8)) {
                                *(unsigned int**)(v + 4) = e + 1;
                                if (e != 0)
                                    *e = idx;
                            } else {
                                DoInsertValue_SI(v, e, &idx);
                            }
                            alreadyCreated = ((def->mFlags >> 4) & 1) == 0;
                        }
                    }
                nextDef:
                    ++idx;
                } while (idx < defCount);
                if (anyCreated)
                    FUN_00a828a0();
            }
        }
    }
    *(int*)(eff + 0x48) = lod;
}
