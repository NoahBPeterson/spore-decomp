// Slice s00a00980: nSPCreatureAnim::queued_blender command-table management.
// Retail queued_blender layout (offsets confirmed from the disassembly; the 2008
// dev-build PDB has a smaller anim_command of 0x80, retail uses 0xf0).
#include <string.h>
#include <math.h>

typedef unsigned int uint;

struct QueuedBlender;

struct AnimCommand {
    void*         mAnim;            // +0x00
    void*         mAnimBaked;       // +0x04
    uint          mDeferred[8][3];  // +0x08 .. +0x68 (8 ids * 0xc)
    uint          mDeferredIdx;     // +0x68
    uint          mLinkedHandle;    // +0x6c
    float         mDurationOverride;// +0x70
    uint          mHandle;          // +0x74
    float         mDelay;           // +0x78
    uint          mPad7c;           // +0x7c
    uint          mPad80;           // +0x80
    bool          mFlag84;          // +0x84
    char          mPad85[3];        // +0x85
    float         mCursor;          // +0x88
    uint          mPad8c;           // +0x8c
    uint          mPad90;           // +0x90
    uint          mPad94;           // +0x94
    float         mWeight98;        // +0x98
    uint          mPad9c;           // +0x9c
    float         mA0;              // +0xa0
    uint          mPadA4[3];        // +0xa4 .. +0xb0
    uint          mSeq;             // +0xb0
    uint          mSeqGen;          // +0xb4
    float         mBakeScale;       // +0xb8
    uint          mAnimId;          // +0xbc
    uint          mStatus;          // +0xc0
    float         mTransition;      // +0xc4
    int           mEnabled;         // +0xc8
    uint          mPadCC;           // +0xcc
    float         mWeightD0;        // +0xd0
    bool          mActiveD4;        // +0xd4
    char          mPadD5[7];        // +0xd5 .. +0xdc
    int           mCb1;             // +0xdc callback fn ptr
    uint          mCb1a;            // +0xe0
    uint          mCb1b;            // +0xe4
    int           mCb2;             // +0xe8 callback fn ptr
    uint          mCb2a;            // +0xec
};

struct QueuedBlender {
    uint        mSeq;               // +0x000
    uint        mPad04;             // +0x004
    AnimCommand mCommands[16];      // +0x008 (0xf0 each)
    uint        mCommandsTail;      // +0xf08
    uint        mActive[16];        // +0xf0c
    uint        mQueued[16];        // +0xf4c
    bool        mNewlyActivated[16];// +0xf8c
    uint        mQueueTail;         // +0xf9c
    uint        mQueueHead;         // +0xfa0
    uint        mPrimary;           // +0xfa4
    uint        mDefault;           // +0xfa8
    bool        mFlagFac;           // +0xfac
    char        mPadFad[3];         // +0xfad
    uint        mPadFb0;            // +0xfb0
    uint        mPadFb4;            // +0xfb4
    float       mEaseTime;          // +0xfb8
    void*       mCreature;          // +0xfbc
    void*       mBakedMgr;          // +0xfc0
    uint        mPadFc4;            // +0xfc4
    uint        mPadFc8;            // +0xfc8
    bool        mFlagFcc;           // +0xfcc

    void ClearQueued();                          // 00a00980
    void FUN_00a00c40(uint param);               // 00a00c40
    void Activate(uint idx, char force);         // 00a00d50
    void Deactivate(uint idx);                   // 00a00f10
    void FUN_00a00f90(AnimCommand* cmd, uint x); // 00a00f90
    void FUN_00a01050(uint x);                   // 00a01050
    void UpdateCreatureBodies(uint a2, float a3, float a4, uint a5,
                              uint a6, uint a7, float a8); // 00a010c0
};

// ---- external thiscall callees: use a stub class so __thiscall is legal ----
struct XC {
    void  FUN_00a00490();
    void* FUN_009a34a0();
    void  FUN_0099c970();
    void  FUN_009a3630();
    void  FUN_009ae1c0();
    void  FUN_009a3220(uint, uint, uint);
    void  FUN_009fee90();
    void  FUN_00a00670(bool, int);
    void  FUN_009ff440();
    uint  FUN_009ff380();
    uint  FUN_009ff040();
    uint  FUN_009aa8a0(uint, uint, uint);
    void  FUN_009abe90(uint, uint, uint, uint);
    void  FUN_009a9b90(uint);
    void  FUN_00a008b0();
    void  FUN_009b9090();
    float FUN_009ac2b0(float, float, int, uint);
    float FUN_009afe90(float);
    void  FUN_009ffb50();
};

// ---- external cdecl callees ----
void  __cdecl FUN_009a1ad0(void*);
uint  __cdecl FUN_009a4550(uint, uint);
void  __cdecl FUN_009a2cc0(uint, uint);
void  __cdecl FUN_009f9b40(void*);
void  __cdecl FUN_009fbb80(void*, float);
void  __cdecl FUN_009bcab0(void*, float, float);
void  __cdecl FUN_009bd2b0(void*);
void  __cdecl FUN_009bcc70(void*, float);
void  __cdecl FUN_009a6cc0(uint, void*);
void  __cdecl FUN_009bd550(float, float, void*, int);
void  __cdecl FUN_009bd6f0(void*);
void  __cdecl FUN_009cb760(void*);
void  __cdecl FUN_009be150(void*);
void  __cdecl FUN_009a7f10(uint, void*, void*, uint, float);
void  __cdecl FUN_009ff880(void*, void*);
char  __cdecl FUN_009ffa00(void*, void*);
void* __cdecl operator_new(size_t, const char*, int, int, int, int);
extern "C" uint* g_166c064;   // 0x0166c064
extern "C" int DAT_015509dc;
extern "C" int DAT_01550ad4;
extern "C" int DAT_015509f4;
extern "C" int DAT_0166bff0;
extern "C" int DAT_0166cbec;
extern "C" uint DAT_0166cbe8;

uint FUN_00a009e0(QueuedBlender* b);
AnimCommand* FUN_00a00b10(QueuedBlender* b, AnimCommand* src, uint handle, uint a2);

// @ 0x00a00980
void QueuedBlender::ClearQueued() {
    uint* p = mQueued;
    int n = 0x10;
    do {
        uint v = *p;
        if (v != 0xffffffffu && v != mDefault)
            ((XC*)&mCommands[v])->FUN_00a00490();
        *p = 0xffffffffu;
        p++;
        n--;
    } while (n != 0);
    mQueueHead = 0xffffffffu;
    mQueueTail = 0xffffffffu;
}

// @ 0x00a009e0
uint FUN_00a009e0(QueuedBlender* b) {
    uint best = 0xffffffffu;
    int it = 0;
    for (;;) {
        if ((int)best >= 0 && best < 0x10 && best != b->mDefault) {
            AnimCommand* c = &b->mCommands[best];
            if (c->mAnim == 0 &&
                ((uint)c->mDeferredIdx >= 8 || c->mDeferred[c->mDeferredIdx][0] == 0))
                return best;
        }
        if (best <= 0x10) {
            AnimCommand* c = &b->mCommands[best];
            if (c->mAnim == 0) {
                uint h = c->mHandle;
                if (h == 0) { ((XC*)c)->FUN_00a00490(); return best; }
                AnimCommand* s = &b->mCommands[(h & 0xff) - 1];
                if (s->mSeqGen != (h >> 8)) { ((XC*)c)->FUN_00a00490(); return best; }
                if (s->mAnim == 0) {
                    uint h2 = s->mLinkedHandle;
                    if (h2 == 0) { ((XC*)c)->FUN_00a00490(); return best; }
                    AnimCommand* s2 = &b->mCommands[(h2 & 0xff) - 1];
                    if (s2->mSeqGen != (h2 >> 8)) { ((XC*)c)->FUN_00a00490(); return best; }
                    if (s2->mAnim == 0) { ((XC*)c)->FUN_00a00490(); return best; }
                }
            }
        }
        uint t = b->mCommandsTail;
        int nx = (int)(t + 1);
        if (nx < 0) {
            uint m = (uint)(-nx) & 0x8000000fu;
            if ((int)m < 0) m = ((m - 1) | 0xfffffff0u) + 1;
            nx = 0;
            if (m != 0) nx = (int)(0x10 - m);
        } else {
            nx = (int)((uint)nx & 0x8000000fu);
            if (nx < 0) nx = (int)((((uint)nx - 1) | 0xfffffff0u) + 1);
        }
        if (t == 0xf) b->mSeq++;
        it++;
        b->mCommandsTail = (uint)nx;
        if (it >= 0x10) return 0xffffffffu;
        best = (uint)nx;
    }
}

// @ 0x00a00b10
AnimCommand* FUN_00a00b10(QueuedBlender* b, AnimCommand* src, uint handle, uint a2) {
    uint idx = FUN_00a009e0(b);
    if (idx >= 0x10) return 0;
    AnimCommand* c = &b->mCommands[idx];
    ((XC*)c)->FUN_00a00490();
    if (g_166c064[0] == g_166c064[1]) {
        void* p = operator_new(0xe0, "Anim/aid", 0, 0, 0, 0);
        void* nv = p ? ((XC*)p)->FUN_009a34a0() : 0;
        void* old = c->mAnim;
        if (nv != old) {
            if (nv) ((XC*)nv)->FUN_0099c970();
            c->mAnim = nv;
            if (old) ((XC*)old)->FUN_009a3630();
        }
    } else {
        void* nv = (void*)*(uint*)(g_166c064[1] - 4);
        void* old = c->mAnim;
        if (nv != old) {
            if (nv) ((XC*)nv)->FUN_0099c970();
            c->mAnim = nv;
            if (old) ((XC*)old)->FUN_009a3630();
        }
        g_166c064[1] -= 4;
        void* v = (void*)*(uint*)(g_166c064[1]);
        if (v) ((XC*)v)->FUN_009a3630();
    }
    uint r = FUN_009a4550(*(uint*)b->mCreature, a2);
    ((XC*)c->mAnim)->FUN_009a3220(a2, (uint)b->mCreature, r);
    ((XC*)c)->FUN_009fee90();
    c->mActiveD4 = true;
    ((AnimCommand*)c->mAnim)->mActiveD4 = true;
    c->mSeqGen = b->mSeq;
    c->mLinkedHandle = handle;
    src->mLinkedHandle = b->mSeq * 0x100 + 1 + (idx & 0xff);
    return c;
}

// @ 0x00a00c40
void QueuedBlender::FUN_00a00c40(uint param) {
    uint v = mActive[param];
    if (v != mDefault) {
        AnimCommand* src = &mCommands[v];
        AnimCommand* dst = &mCommands[mDefault];
        mActive[param] = mDefault;
        uint i = 0;
        do {
            if (i != param && mActive[i] == mDefault)
                mActive[i] = 0xffffffffu;
            i++;
        } while (i < 0x10);
        if (dst->mStatus == 3)
            dst->mStatus = 1;
        uint h = src->mLinkedHandle;
        if (h != 0) {
            dst->mLinkedHandle = h;
            AnimCommand* s = &mCommands[(h & 0xff) - 1];
            if ((h & 0xff) - 1 < 0x10 && s->mSeqGen == (h >> 8))
                s->mHandle = dst->mSeqGen * 0x100 + 1 + (mDefault & 0xff);
            ((XC*)dst)->FUN_00a00490();
        } else {
            dst->mLinkedHandle = src->mSeqGen * 0x100 + 1 + (v & 0xff);
            src->mLinkedHandle = dst->mSeqGen * 0x100 + 1 + (mDefault & 0xff);
        }
    }
}

// @ 0x00a00d50
void QueuedBlender::Activate(uint i, char force) {
    if (i >= 0x10) return;
    uint v = mActive[i];
    if (v >= 0x10) return;
    AnimCommand* c = &mCommands[v];
    if (c->mWeightD0 > 0.0f)
        FUN_00a00c40(i);
    v = mActive[i];
    c = &mCommands[v];
    if (c->mEnabled != 0) return;
    void* anim = c->mAnim;
    if (c->mLinkedHandle == 0 && c->mCb1 != 0) {
        ((void (__cdecl*)(uint, uint, QueuedBlender*, uint))c->mCb1)
            (c->mCb1a, c->mCb1b, this, c->mSeq * 0x100 + 1 + (v & 0xff));
    }
    if (!mFlagFcc) {
        c->mStatus = 2;
        c->mWeight98 = 0.0f;
        mFlagFcc = true;
    } else {
        c->mStatus = 1;
    }
    c->mTransition = c->mCursor;
    FUN_009a2cc0((uint)anim, c->mAnimId);
    *(double*)((char*)anim + 0xb0) = (double)c->mDurationOverride;
    if (c->mFlag84) {
        uint d = mDefault;
        if (mActive[mPrimary] == d)
            mPrimary = i;
        AnimCommand* dc = &mCommands[d];
        if (dc->mEnabled == 0) {
            ((XC*)this)->FUN_00a008b0();
        } else {
            uint v2 = mActive[i];
            if (v2 != d && v2 < 0x10 && d < 0x10)
                ((XC*)dc)->FUN_00a00670(1, 0);
        }
        mDefault = mActive[i];
    }
    if (force) {
        uint creature = *(uint*)mCreature;
        ((XC*)mBakedMgr)->FUN_009abe90(creature, (uint)anim, c->mAnimId, 0);
        uint r = ((XC*)mBakedMgr)->FUN_009aa8a0(creature, (uint)anim, c->mAnimId);
        ((XC*)&c->mAnimBaked)->FUN_009a9b90(r);
    }
    mNewlyActivated[i] = true;
}

// @ 0x00a00f10
void QueuedBlender::Deactivate(uint idx) {
    if (idx < 0x10) {
        uint v = mActive[idx];
        if (v < 0x10) {
            mActive[idx] = 0xffffffffu;
            AnimCommand* c = &mCommands[v];
            if (v != mDefault) {
                ((XC*)c)->FUN_00a00490();
            } else {
                if (c->mAnim != 0)
                    FUN_009a1ad0(c->mAnim);
                c->mTransition = 0.0f;
                c->mStatus = 0;
            }
        }
    }
    if (idx == mPrimary)
        ((XC*)this)->FUN_009ff440();
}

// @ 0x00a00f90
void QueuedBlender::FUN_00a00f90(AnimCommand* cmd, uint x) {
    bool b1 = (mDefault < 0x10) && (cmd == &mCommands[mDefault]);
    bool b2 = (mPrimary < 0x10) && (cmd == &mCommands[mActive[mPrimary]]);
    if (!b1 || mQueueHead != 0xffffffffu) {
        ((XC*)cmd)->FUN_00a00670(!b1, (int)x);
        if (cmd->mStatus == 0) {
            uint* p = mActive;
            int n = 0x10;
            do {
                if (cmd == &mCommands[*p])
                    *p = 0xffffffffu;
                p++;
                n--;
            } while (n != 0);
        }
        if (b2)
            ((XC*)this)->FUN_009ff440();
    }
}

// @ 0x00a01050
void QueuedBlender::FUN_00a01050(uint x) {
    uint* p = mActive;
    int n = 0x10;
    do {
        uint v = *p;
        if (v < 0x10) {
            AnimCommand* c = &mCommands[v];
            if (c->mAnim != 0 ||
                (c->mDeferredIdx < 8 && c->mDeferred[c->mDeferredIdx][0] != 0))
                FUN_00a00f90(c, x);
        }
        p++;
        n--;
    } while (n != 0);
    mPrimary = ((XC*)this)->FUN_009ff380();
}

// @ 0x00a010c0
void QueuedBlender::UpdateCreatureBodies(uint a2, float a3, float a4, uint a5,
                                         uint a6, uint a7, float a8) {
    bool bl = (a5 & 0xff) != 0;
    if (mFlagFac && !bl) {
        if (DAT_015509dc)
            FUN_009f9b40(mCreature);
        if (DAT_01550ad4)
            FUN_009fbb80(mCreature, a3);
        void* cr = mCreature;
        if (*(char*)((char*)cr + 0x260) && DAT_0166bff0 &&
            !*(char*)((char*)(*(void**)cr) + 0x3f5) && *(char*)((char*)cr + 0x168c))
            ((XC*)cr)->FUN_009b9090();
    }
    if (!bl) {
        float v = mEaseTime;
        if (v > 0.0f) {
            if (v > 1.0f) v = 1.0f;
        } else v = 0.0f;
        FUN_009bcab0(mCreature, 1.0f - v, v);
        if ((a6 & 0xff) != 0 && mEaseTime > 0.0f) {
            uint* p = mActive;
            int n = 0x10;
            do {
                uint idx = *p;
                if (idx < 0x10) {
                    AnimCommand* c = &mCommands[idx];
                    if (c->mAnim != 0 && c->mAnimBaked != 0 && c->mStatus != 0 &&
                        c->mWeight98 > 0.0f) {
                        float t = c->mWeight98 / mEaseTime;
                        float r = ((XC*)c->mAnimBaked)->FUN_009ac2b0(1.0f - t, t, 1, (uint)mCreature);
                        ((XC*)c->mAnimBaked)->FUN_009afe90(r * c->mBakeScale);
                    }
                }
                p++;
                n--;
            } while (n != 0);
        }
        {
            void* cr = mCreature;
            if (*(char*)((char*)cr + 0x260))
                FUN_009bd2b0(cr);
            FUN_009bcc70(cr, a3);
            if (!(DAT_0166cbec & 1)) {
                DAT_0166cbec |= 1;
                uint ecx = 1;
                uint edi = 7;
                uint esi = 0x20007;
                uint ebx = 0;
                do {
                    if (esi == 0) break;
                    uint edx = (esi - 1) & esi;
                    uint eax = edx ^ esi;
                    esi = eax;
                    esi &= edi;
                    esi = (uint)(-(int)esi);
                    esi = (uint)((int)esi >> 31);
                    esi &= ecx;
                    eax = ~eax;
                    ebx |= esi;
                    edi &= eax;
                    ecx += ecx;
                    esi = edx;
                } while (edi != 0);
                DAT_0166cbe8 = 1u << (ebx & 0x1f);
            }
            if ((mFlagFac || *(char*)((char*)cr + 0x2d5)) &&
                *(char*)((char*)cr + 0x260) && (a7 & DAT_0166cbe8))
                FUN_009a6cc0(a2, cr);
            if (DAT_015509dc)
                FUN_009bd550(a3, a4, cr, 1);
            if (DAT_015509f4 && *(char*)((char*)cr + 0x168c))
                FUN_009bd6f0(cr);
            FUN_009cb760(cr);
            FUN_009be150(cr);
        }
    }
    // L_a3
    if (mPrimary >= 0x10 && mQueueHead < 0x10) {
        if (mQueueHead == 0xffffffffu)
            mPrimary = ((XC*)this)->FUN_009ff380();
        else
            mPrimary = ((XC*)this)->FUN_009ff040();
    }
    {
        uint* p = mActive;
        int n = 0x10;
        do {
            uint idx = *p;
            if (idx < 0x10) {
                AnimCommand* c = &mCommands[idx];
                if (c->mAnim != 0 && c->mStatus != 0)
                    FUN_009a7f10(a2, mCreature, c->mAnim, a7, a8);
            }
            p++;
            n--;
        } while (n != 0);
    }
    uint i = 0;
    for (;;) {
        uint idx = mActive[i];
        if (idx < 0x10) {
            AnimCommand* c = &mCommands[idx];
            if (c->mAnim != 0 && c->mStatus != 0) {
                uint st = c->mStatus;
                if (st == 1) {
                    c->mTransition -= a3;
                    if (!(c->mTransition > 0.0f))
                        c->mStatus = 2;
                } else if (st == 2) {
                    if (c->mA0 == 0.0f) {
                        FUN_00a00f90(c, 0);
                    } else if (c->mA0 > 0.0f) {
                        int li = (int)(long long)(ceil((double)c->mA0) - 1.0);
                        if ((int)c->mSeq == li) {
                            double q = *(double*)((char*)c->mAnim + 0xb0) /
                                       *(double*)((char*)c->mAnim + 0xb8);
                            double ip;
                            double frac = modf(q, &ip);
                            if (q < 0.0) frac = 1.0 - frac;
                            double value =
                                (double)c->mHandle / *(double*)((char*)c->mAnim + 0xb8) +
                                ((double)c->mA0 - (double)c->mSeq);
                            if (frac >= value)
                                FUN_00a00f90(c, 0);
                        }
                    }
                } else if (st == 3) {
                    c->mTransition -= a3;
                    if (!(c->mTransition > 0.0f))
                        Deactivate(i);
                }
                if (c->mEnabled == 0) {
                    c->mSeq = *(uint*)((char*)c->mAnim + 0xc4);
                } else if (c->mStatus != 3 &&
                           (*(double*)((char*)c->mAnim + 0xb8) - (double)c->mDelay) <
                           *(double*)((char*)c->mAnim + 0xb0)) {
                    c->mSeq++;
                    uint ni = FUN_00a009e0(this);
                    if (ni >= 0x10) return;
                    AnimCommand* nc = &mCommands[ni];
                    ((XC*)nc)->FUN_009ffb50();
                    c->mCb2a = 0;
                    FUN_009ff880(c, nc);
                    uint k = 0;
                    uint* pp = mActive;
                    do {
                        if (*pp == 0xffffffffu) { mActive[k] = ni; break; }
                        k++;
                        pp++;
                    } while (k < 0x10);
                    if (c->mAnim != 0) {
                        void* oa = c->mAnim;
                        c->mAnim = 0;
                        ((XC*)oa)->FUN_009a3630();
                    }
                    if (c->mAnimBaked != 0) {
                        void* ob = c->mAnimBaked;
                        c->mAnimBaked = 0;
                        ((XC*)ob)->FUN_009ae1c0();
                    }
                    memset(&c->mDeferred[0][0], 0, 0x60);
                    c->mDeferredIdx = 0;
                    uint local = 0;
                    ((void (__cdecl*)(uint, QueuedBlender*, void*, int, uint*))c->mCb2)
                        (c->mCb2a, this, &c->mDeferred[0][0], 8, &local);
                    if (FUN_009ffa00(this, c)) {
                        if (c->mAnim != 0)
                            FUN_009a1ad0(c->mAnim);
                        c->mTransition = 0.0f;
                        c->mStatus = 0;
                    } else {
                        uint h = c->mSeqGen * 0x100 + 1 + (idx & 0xff);
                        AnimCommand* ret = FUN_00a00b10(this, c, h, a2);
                        if (c->mAnim != 0)
                            FUN_009a1ad0(c->mAnim);
                        c->mTransition = 0.0f;
                        c->mStatus = 0;
                        mActive[i] = 0xffffffffu;
                        ret->mPad7c = 1;
                        uint ri = (uint)(((char*)ret - (char*)mCommands) / 0xf0);
                        uint k2 = 0;
                        uint* pp2 = mActive;
                        do {
                            if (*pp2 == 0xffffffffu) { mActive[k2] = ri; break; }
                            k2++;
                            pp2++;
                        } while (k2 < 0x10);
                        if (mPrimary == i)
                            mPrimary = k2;
                    }
                }
            }
        }
        i++;
        if (i >= 0x10) return;
    }
}
