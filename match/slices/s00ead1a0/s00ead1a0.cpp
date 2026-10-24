// Slice s00ead1a0: SP::Audio::cPlayerCityMusic (0xead1a0-0xeae040).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
// Callees outside the slice are masked relocations, so they are declared with the
// right calling convention only.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int i32;
typedef float f32;

// ---- external callees (masked relocations) ----------------------------------

void* EAAllocate(unsigned int n, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void  __cdecl operator_delete_array(void* p);                                                 // 0x00f47380
extern "C" void* __cdecl memcpy_(void* d, const void* s, unsigned n);                          // 0x011e0744
extern "C" __declspec(dllimport) void* __cdecl memmove_imp(void* d, const void* s, unsigned n); // 0x013cc480

void* GetSystemAT();                                            // 0x00a206f0
void* MessageServer();                                          // 0x0067dcc0
void  SetGlobalProperty(int key, float value);                  // 0x005ca880
void  __cdecl RemoveHandler(void* h, void* a, void* b, void* c, void* d); // 0x00571db0
void  __cdecl FUN_00572020(void* a, void* b);                   // 0x00572020
void  __cdecl KillSetiEffects(void* a, void* b);                // 0x00435ed0
void* __stdcall ListErase(void* out, void* a, void* b);         // 0x00973d10

// globals referenced by absolute address
extern u32  g_tab_1488414[3];      // 0x01488414
extern void* g_tab_1488420[3];     // 0x01488420
extern char PTR_01488444;          // 0x01488444 (vftable)
extern char PTR_0148843c;          // 0x0148843c
extern char PTR_0148842c;          // 0x0148842c
extern char PTR_013ec458;          // 0x013ec458
extern char PTR_013eb394;          // 0x013eb394
extern char PTR_013eb938;          // 0x013eb938

// ---- vtable dispatch helpers ------------------------------------------------

typedef void  (__thiscall *vfn0)(void*);
typedef void  (__thiscall *vfn1)(void*, int);
typedef void  (__thiscall *vfn2)(void*, int, int);
typedef void  (__thiscall *vfnf)(void*, int, float);
typedef void* (__thiscall *vfnr)(void*);
#define VSLOT(o, off) (*(void**)((char*)(*(void**)(o)) + (off)))

// ---- eastl intrusive list node ----------------------------------------------

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct cListNode {
    cListNode* mpNext_00;   // +0x00
    cListNode* mpPrev_04;   // +0x04
    int        mKey_08;     // +0x08
};

struct cList {
    cListNode mHead_00;
    void FUN_00eada10(const int* keyPtr);
    void FUN_00eadee0(int* begin, int* end, int dummy);
};

// @ 0x00eada10
void cList::FUN_00eada10(const int* keyPtr) {
    cListNode* head = &mHead_00;
    cListNode* n = mHead_00.mpNext_00;
    if (n == head) return;
    for (;;) {
        int key = n->mKey_08;
        n = n->mpNext_00;
        if (key == *keyPtr) {
            cListNode* x = n->mpPrev_04;
            x->mpPrev_04->mpNext_00 = x->mpNext_00;
            x->mpNext_00->mpPrev_04 = x->mpPrev_04;
            operator_delete_array(x);
        }
        if (n == head) break;
    }
}

// @ 0x00eada50
void __stdcall FUN_00eada50(cListNode* sentinel, int* begin, int* end, int dummy) {
    for (; begin != end; ++begin) {
        cListNode* n = (cListNode*)EAAllocate(0xc, "Simulator", 0, 0, "allocator.h", 0xd1);
        if (&n->mKey_08)
            n->mKey_08 = *begin;
        n->mpNext_00 = sentinel;
        n->mpPrev_04 = sentinel->mpPrev_04;
        sentinel->mpPrev_04->mpNext_00 = n;
        sentinel->mpPrev_04 = n;
    }
}

// @ 0x00eadab0
void __stdcall FUN_00eadab0(cListNode* sentinel, unsigned count, const int* valuePtr) {
    if (count == 0) return;
    for (; count > 0; --count) {
        cListNode* n = (cListNode*)EAAllocate(0xc, "Simulator", 0, 0, "allocator.h", 0xd1);
        if (&n->mKey_08)
            n->mKey_08 = *valuePtr;
        n->mpNext_00 = sentinel;
        n->mpPrev_04 = sentinel->mpPrev_04;
        sentinel->mpPrev_04->mpNext_00 = n;
        sentinel->mpPrev_04 = n;
    }
}

// @ 0x00eadee0
void cList::FUN_00eadee0(int* begin, int* end, int dummy) {
    cListNode* n = mHead_00.mpNext_00;
    while (n != &mHead_00) {
        if (begin == end) break;
        n->mKey_08 = *begin;
        n = n->mpNext_00;
        ++begin;
    }
    if (begin == end) {
        ListErase(&begin, n, &mHead_00);
        return;
    }
    FUN_00eada50(&mHead_00, begin, end, dummy);
}

// @ 0x00eadb10
void __cdecl FUN_00eadb10(void** p, int n) {
    for (; n != 0; --n)
        *p = *(void**)*p;
}

// @ 0x00eae010
int* __cdecl FUN_00eae010(void* first, void* last, int* out) {
    while (first != last) {
        *out++ = ((int*)first)[2];
        first = *(void**)first;
    }
    return out;
}

// @ 0x00eae040
int* __cdecl FUN_00eae040(void* first, void* last, int* out) {
    while (last != first) {
        last = *(void**)((char*)last + 4);
        *--out = ((int*)last)[2];
    }
    return out;
}

// ---- eastl vectors ----------------------------------------------------------

struct cMusicVec {
    void* mpBegin_00;   // +0x00
    void* mpEnd_04;     // +0x04
    void FUN_00ead660();
};

// @ 0x00ead660
void cMusicVec::FUN_00ead660() {
    char* p = (char*)mpBegin_00;
    char* end = (char*)mpEnd_04;
    while (p < end) {
        (*(vfn1)VSLOT(p, 8))(p, 0);
        p += 0x6c;
    }
    if (mpBegin_00)
        operator_delete_array(mpBegin_00);
}

struct cIntVec {
    int* mpBegin_00;   // +0x00
    int* mpEnd_04;     // +0x04
    int* mpCap_08;     // +0x08
    void FUN_00eade60(unsigned newCap);
};

// @ 0x00eade60
void cIntVec::FUN_00eade60(unsigned newCap) {
    if (newCap <= (unsigned)(mpCap_08 - mpBegin_00)) return;
    int* p = newCap ? (int*)EAAllocate(newCap * 4, "Simulator", 0, 0, "allocator.h", 0xd1) : 0;
    memcpy_(p, mpBegin_00, (char*)mpEnd_04 - (char*)mpBegin_00);
    if (mpBegin_00)
        operator_delete_array(mpBegin_00);
    int n = (int)((char*)mpEnd_04 - (char*)mpBegin_00) >> 2;
    mpBegin_00 = p;
    mpEnd_04 = p + n;
    mpCap_08 = p + newCap;
}

struct cFloatVec {
    float* mpBegin_00;   // +0x00
    float* mpEnd_04;     // +0x04
    float* mpCap_08;     // +0x08
    void FUN_00eadf40(float* pos, float* value);
};

// @ 0x00eadf40
void cFloatVec::FUN_00eadf40(float* pos, float* value) {
    if (mpEnd_04 != mpCap_08) {
        float* src = value;
        if (pos <= value && value < mpEnd_04) src = value + 1;
        if (mpEnd_04 != 0)
            *mpEnd_04 = *(mpEnd_04 - 1);
        int sz = (int)((char*)(mpEnd_04 - 1) - (char*)pos);
        memmove_imp((char*)mpEnd_04 + ((sz >> 2) * -4), pos, (unsigned)sz);
        *pos = *src;
        mpEnd_04 += 1;
        return;
    }
    float* begin = mpBegin_00;
    float* oldEnd = mpEnd_04;
    int n = (int)(oldEnd - begin);
    int newCap = n * 2;
    if (n == 0) newCap = 1;
    int off = (int)((char*)value - (char*)begin);
    float* slot = (float*)((char*)memcpy_(0, begin, (unsigned)off) + ((off >> 2) * 4));
    if (slot)
        *slot = *value;
    int tail = (int)((char*)oldEnd - (char*)value);
    void* r = memcpy_(slot + 1, value, (unsigned)tail);
    mpBegin_00 = 0;
    mpEnd_04 = (float*)((char*)r + ((tail >> 2) * 4));
    mpCap_08 = (float*)(newCap * 4);
}

// ---- SP::Audio::cPlayerCityMusic --------------------------------------------

namespace SP { namespace Audio {

struct cPlayerCityMusic {
    void* mpVtbl_000;                    // +0x000
    void* mpVtbl_004;                    // +0x004
    void* mpVtbl_008;                    // +0x008
    u8    mPad_00c[0x40 - 0x0c];
    void* mp_040;                        // +0x040
    u8    mPad_044[0x54 - 0x44];
    void* mp_054;                        // +0x054
    u8    mPad_058[0x68 - 0x58];
    int   mn_068;                        // +0x068
    u8    mPad_06c[0x74 - 0x6c];
    int*  mp_074;                        // +0x074
    u8    mPad_078[0x94 - 0x78];
    int** mpp_094;                       // +0x094
    u8    mPad_098[0xd0 - 0x98];
    void* mp_0d0;                        // +0x0d0
    void* mp_0d4;                        // +0x0d4
    void* mp_0d8;                        // +0x0d8
    void* mp_0dc;                        // +0x0dc
    u8    mPad_0e0[0x101 - 0xe0];
    u8    mb_101;                        // +0x101
    u8    mPad_102[0x108 - 0x102];
    void* mp_108;                        // +0x108
    void* mp_10c;                        // +0x10c
    int   mn_110;                        // +0x110
    void* mp_114;                        // +0x114
    void* mp_118;                        // +0x118
    u8    mPad_11c[0x128 - 0x11c];
    int*  mp_128;                        // +0x128
    int*  mp_12c;                        // +0x12c
    u8    mPad_130[0x13c - 0x130];
    int*  mp_13c;                        // +0x13c
    u8    mPad_140[0x178 - 0x140];
    int*  mp_178;                        // +0x178
    u8    mPad_17c[0x180 - 0x17c];
    int*  mp_180;                        // +0x180
    u8    mPad_184[0x188 - 0x184];
    int*  mp_188;                        // +0x188
    u8    mPad_18c[0x190 - 0x18c];
    int*  mp_190;                        // +0x190
    u8    mPad_194[0x198 - 0x194];
    float* mp_198;                       // +0x198
    u8    mPad_19c[0x1b8 - 0x19c];
    cList mList_1b8;                     // +0x1b8
    u8    mPad_1c4[0x1c4 - 0x1c4];

    // The fields below live past 0x1c4; keep the layout explicit.
    void Reset(char param);
    void Start(int arg);
    void Stop();
    void SetNotePitch(int idx, int pitch);
    void SelectAmbience(int state, u32* outIndex);
    ~cPlayerCityMusic();
};

// Ghidra treats cPlayerCityMusic as a base at +0 and a second sub-object at +1c4;
// flatten the remaining fields with a separate struct viewed via offset.
struct cPlayerCityMusicTail {
    u8    pad_000[0x1c4 - 0x000];
    int   mn_1c4;                        // +0x1c4
    int   mn_1c8;                        // +0x1c8
    int*  mp_1cc;                        // +0x1cc
    int*  mp_1d0;                        // +0x1d0
    u8    pad_1d4[0x1e0 - 0x1d4];
    float* mp_1e0;                       // +0x1e0
    u8    pad_1e4[0x1f4 - 0x1e4];
    void* mp_1f4;                        // +0x1f4
    void* mp_1f8;                        // +0x1f8
    void* mp_1fc;                        // +0x1fc
    void* mp_200;                        // +0x200
    void* mp_204;                        // +0x204
    void* mp_208;                        // +0x208
    void* mp_20c;                        // +0x20c
    void* mp_210;                        // +0x210
    int   mn_214;                        // +0x214
    int   mn_218;                        // +0x218
};

#define SELF_TAIL ((cPlayerCityMusicTail*)this)

// @ 0x00ead1a0
void cPlayerCityMusic::Reset(char param) {
    cPlayerCityMusicTail* t = SELF_TAIL;
    if (mp_10c == 0) return;
    void* sys;
    int prop;
    if (param != 0) {
        u32 cnt = (u32)((char*)mp_118 - (char*)mp_114) >> 2;
        if ((int)cnt != 0) {
            for (unsigned i = 0; i < (unsigned)((char*)mp_118 - (char*)mp_114) >> 2; ++i) {
                int v = *(int*)((char*)mp_114 + i * 4);
                if (v != 0) {
                    SetGlobalProperty(0x330df985, (float)(unsigned)v);
                    SetGlobalProperty(0x3fbc0a67, (float)(unsigned)(i + 1));
                }
            }
        }
        if (t->mn_1c4 != 0)
            SetGlobalProperty(0xec66947a, (float)(unsigned)t->mn_1c4);
        if (t->mn_1c8 != 0)
            SetGlobalProperty(0xf7db2353, (float)(unsigned)t->mn_1c8);
        for (unsigned b = 0; b < 0xc; b += 4) {
            float f = *(float*)((char*)mp_198 + b);
            u32 p = *(u32*)((char*)g_tab_1488414 + b);
            sys = GetSystemAT();
            if (sys) {
                (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
                (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, (int)p);
                (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa, f);
                (*(vfn0)VSLOT(sys, 0x58))(sys);
            }
        }
        u32 n2 = (u32)((char*)t->mp_1d0 - (char*)t->mp_1cc) >> 2;
        if (n2 != 0) {
            for (unsigned i = 0; i < n2; ++i) {
                sys = GetSystemAT();
                if (sys) {
                    (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
                    (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, (int)0xe7b72656);
                    (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa, (float)(unsigned)i);
                    (*(vfn0)VSLOT(sys, 0x58))(sys);
                }
                int v = *(int*)((char*)t->mp_1cc + i * 4);
                sys = GetSystemAT();
                if (sys) {
                    (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
                    (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, (int)0xfe31e5d9);
                    (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa, (float)(unsigned)v);
                    (*(vfn0)VSLOT(sys, 0x58))(sys);
                }
                float f = *(float*)((char*)t->mp_1e0 + i * 4);
                sys = GetSystemAT();
                if (sys) {
                    (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
                    (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, (int)0xc309bcc9);
                    (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa, f);
                    (*(vfn0)VSLOT(sys, 0x58))(sys);
                }
            }
        }
        sys = GetSystemAT();
        if (sys) {
            (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
            (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, (int)0xead8248);
            (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa,
                                      (float)(unsigned)((u32)((char*)t->mp_1d0 - (char*)t->mp_1cc) >> 2));
            (*(vfn0)VSLOT(sys, 0x58))(sys);
        }
        if (mb_101 == 0) return;
        sys = GetSystemAT();
        if (sys) {
            (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
            (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, (int)0x6c3a5e1c);
            (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa, 1.0f);
            (*(vfn0)VSLOT(sys, 0x58))(sys);
        }
        sys = GetSystemAT();
        if (sys == 0) return;
        (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
        prop = 0x4b64ae20;
    } else {
        u32 cnt = (u32)((char*)mp_118 - (char*)mp_114) >> 2;
        if ((int)cnt != 0) {
            for (unsigned i = 0; i < cnt; ++i) {
                if (*(int*)((char*)mp_114 + i * 4) != 0)
                    SetGlobalProperty(0xaa1b3b8d, (float)(unsigned)(i + 1));
            }
        }
        if (t->mn_1c4 != 0)
            SetGlobalProperty(0x7df75892, (float)(unsigned)t->mn_1c4);
        if (t->mn_1c8 != 0)
            SetGlobalProperty(0xcbc8ae11, (float)(unsigned)t->mn_1c8);
        sys = GetSystemAT();
        if (sys) {
            (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
            (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, (int)0xead8248);
            (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa, 0.0f);
            (*(vfn0)VSLOT(sys, 0x58))(sys);
        }
        sys = GetSystemAT();
        if (sys == 0) return;
        (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
        prop = 0x6c3a5e1c;
    }
    (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, prop);
    (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa, 0.0f);
    (*(vfn0)VSLOT(sys, 0x58))(sys);
}

// @ 0x00ead6f0
void cPlayerCityMusic::Start(int arg) {
    cPlayerCityMusicTail* t = SELF_TAIL;
    if (mp_10c != 0) return;
    void* sys = GetSystemAT();
    void* p = sys ? (*(vfnr)VSLOT(sys, 0x20))(sys) : 0;
    mp_10c = p;
    if (p == 0) return;
    char* base = (char*)this + 4;
    void* h = MessageServer();
    t->mp_208 = h;
    t->mp_20c = base;
    t->mp_210 = (void*)g_tab_1488420;
    t->mn_214 = 3;
    t->mn_218 = 0;
    if (h != 0 && base != 0) {
        for (unsigned i = 0; i < 0xc; i += 4)
            (*(vfn2)VSLOT(h, 0x24))(h, (int)base, *(int*)((char*)g_tab_1488420 + i));
    }
    KillSetiEffects(mp_108, mp_10c);
    (*(vfn1)VSLOT(this, 0x30))(this, arg);
    Reset(1);
}

// @ 0x00ead7b0
void cPlayerCityMusic::Stop() {
    cPlayerCityMusicTail* t = SELF_TAIL;
    if (mp_10c == 0) return;
    Reset(0);
    FUN_00572020(mp_10c, 0);
    mp_10c = 0;
    if (t->mp_208 != 0) {
        void* h = t->mp_208;
        t->mp_208 = 0;
        RemoveHandler(h, t->mp_20c, t->mp_210, (void*)t->mn_214, (void*)t->mn_218);
    }
}

// @ 0x00ead870
void cPlayerCityMusic::SetNotePitch(int idx, int pitch) {
    cPlayerCityMusicTail* t = SELF_TAIL;
    t->mp_1cc[idx] = pitch;
    unsigned rem = ((unsigned)t->mp_1cc[idx] - (unsigned)mn_068) % 12;
    int found = -1;
    int* tab = mp_074;
    for (int i = 0; i < 7; ++i, ++tab) {
        if (*tab == (int)rem) { found = i; break; }
    }
    mp_13c[idx] = found;
    int val;
    if (mp_13c[idx] == -1) {
        val = 2;
    } else if (idx == 0) {
        val = 0;
    } else {
        int* oct = mp_13c;
        int* arr = (int*)mpp_094[oct[idx - 1]];
        val = (arr[oct[idx]] == 0);
    }
    mp_128[idx] = val;
    int i2 = idx + 1;
    if (i2 < (int)((char*)mp_12c - (char*)mp_128) >> 2) {
        int v2;
        if (mp_13c[i2] == -1) {
            v2 = 2;
        } else if (i2 == 0) {
            v2 = 0;
        } else {
            int* oct = mp_13c;
            int* arr = (int*)mpp_094[oct[i2 - 1]];
            v2 = (arr[oct[i2]] == 0);
        }
        mp_128[i2] = v2;
    }
    void* sys = GetSystemAT();
    if (sys) {
        (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
        (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, (int)0xe7b72656);
        (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa, (float)(unsigned)idx);
        (*(vfn0)VSLOT(sys, 0x58))(sys);
    }
    sys = GetSystemAT();
    if (sys) {
        (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
        (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, (int)0xfe31e5d9);
        (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa, (float)(unsigned)pitch);
        (*(vfn0)VSLOT(sys, 0x58))(sys);
    }
}

// @ 0x00eadd60
void cPlayerCityMusic::SelectAmbience(int state, u32* outIndex) {
    cPlayerCityMusicTail* t = SELF_TAIL;
    (void)t;
    *outIndex = 0;
    if ((int)((char*)mp_118 - (char*)mp_114) >> 2 != 0) {
        for (;;) {
            u32 i = *outIndex;
            if (state == *(int*)((char*)mp_114 + i * 4)) {
                *(int*)((char*)mp_114 + (i * 4)) = 0;
                float f = (float)(unsigned)(*outIndex + 1);
                void* sys = GetSystemAT();
                if (sys) {
                    (*(vfn1)VSLOT(sys, 0x38))(sys, 0x3cdd1a9);
                    (*(vfn2)VSLOT(sys, 0x40))(sys, 0x34753a7, (int)0xaa1b3b8d);
                    (*(vfnf)VSLOT(sys, 0x3c))(sys, 0x34753aa, f);
                    (*(vfn0)VSLOT(sys, 0x58))(sys);
                }
                --mn_110;
                break;
            }
            *outIndex = i + 1;
            if ((u32)((char*)mp_118 - (char*)mp_114) >> 2 <= *outIndex) {
                mList_1b8.FUN_00eada10(&state);
                return;
            }
        }
    }
    mList_1b8.FUN_00eada10(&state);
}

// @ 0x00eadb30
cPlayerCityMusic::~cPlayerCityMusic() {
    cPlayerCityMusicTail* t = SELF_TAIL;
    mpVtbl_000 = (void*)&PTR_01488444;
    mpVtbl_004 = (void*)&PTR_0148843c;
    mpVtbl_008 = (void*)&PTR_0148842c;
    _ReadWriteBarrier();
    if (t->mp_208 != 0) {
        void* h = t->mp_208;
        t->mp_208 = 0;
        RemoveHandler(h, t->mp_20c, t->mp_210, (void*)t->mn_214, (void*)t->mn_218);
    }
    if (t->mp_1f4 != 0) {
        void* hh = t->mp_1f4;
        t->mp_1f4 = 0;
        RemoveHandler(hh, t->mp_1f8, t->mp_1fc, t->mp_200, t->mp_204);
    }
    if (t->mp_1e0)
        operator_delete_array(t->mp_1e0);
    if (t->mp_1cc)
        operator_delete_array(t->mp_1cc);
    {
        cListNode* head = &mList_1b8.mHead_00;
        cListNode* n = mList_1b8.mHead_00.mpNext_00;
        while (n != head) {
            cListNode* cur = n;
            n = n->mpNext_00;
            operator_delete_array(cur);
        }
    }
    {
        int* b = mp_188;
        unsigned nn = (unsigned)((char*)mp_190 - (char*)b) & 0xfffffffeu;
        if ((int)nn > 2 && b)
            operator_delete_array(b);
    }
    {
        int* b = mp_178;
        unsigned nn = (unsigned)((char*)mp_180 - (char*)b) & 0xfffffffeu;
        if ((int)nn > 2 && b)
            operator_delete_array(b);
    }
    if (mp_13c)
        operator_delete_array(mp_13c);
    if (mp_128)
        operator_delete_array(mp_128);
    if (mp_114)
        operator_delete_array(mp_114);
    {
        char* end = (char*)mp_0dc;
        char* p = (char*)mp_0d8;
        while (p < end) {
            (*(vfn1)VSLOT(p, 8))(p, 0);
            p += 0x6c;
        }
        if (mp_0d8)
            operator_delete_array(mp_0d8);
    }
    if (mp_0d4)
        (*(vfn0)VSLOT(mp_0d4, 4))(mp_0d4);
    if (mp_0d0)
        (*(vfn0)VSLOT(mp_0d0, 4))(mp_0d0);
    if (mp_054)
        operator_delete_array(mp_054);
    if (mp_040)
        operator_delete_array(mp_040);
    mpVtbl_008 = (void*)&PTR_013ec458;
    mpVtbl_004 = (void*)&PTR_013eb394;
    mpVtbl_000 = (void*)&PTR_013eb938;
}

}}  // namespace SP::Audio

// ---- standalone editor resource dtor / list helper --------------------------

struct cEditorResource {
    void* mpVtbl_00;
    u8    mPad_04[0x1c - 0x04];
    void* mp_1c;
    u8    mPad_20[0x30 - 0x20];
    void* mp_30;
    u8    mPad_34[0x44 - 0x34];
    void* mp_44;
    u8    mPad_48[0x58 - 0x48];
    void* mp_58;
    void FUN_00ead6a0();
};

// @ 0x00ead6a0
void cEditorResource::FUN_00ead6a0() {
    if (mp_58)
        operator_delete_array(mp_58);
    if (mp_44)
        operator_delete_array(mp_44);
    if (mp_30)
        operator_delete_array(mp_30);
    if (mp_1c)
        operator_delete_array(mp_1c);
    mpVtbl_00 = (void*)&PTR_013eb938;
}

struct cQuery840 {
    u8    mPad_00[0xd8];
    void* mp_d8;
    void* mp_dc;
    u8    mPad_e0[0xf0 - 0xe0];
    void* mp_f0;
    u8    mPad_f4[0xfc - 0xf4];
    void* mp_fc;
    bool FUN_00ead840();
};

// @ 0x00ead840
bool cQuery840::FUN_00ead840() {
    void* v = mp_f0;
    if (v == mp_d8)
        v = mp_dc;
    return mp_fc != (void*)((char*)v - 0x6c);
}