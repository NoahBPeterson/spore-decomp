// Slice s00ccfc20 -- SP::cTribeInputStrategy / cTribeModeStrategy input helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------------------
// external helpers (addresses / reloc targets are masked by the checker)
// ---------------------------------------------------------------------------
void*  GetGameTerrainCursor();                 // 0x00b30d70
void*  FUN_00b3d240();                         // 0x00b3d240
void*  FUN_00b3d280();                         // 0x00b3d280  GetCameraCtl
void*  FUN_00b3d300();                         // 0x00b3d300  SP::NounManager
void*  FUN_00b3d350();                         // 0x00b3d350  SP::PlanetModel
void*  FUN_00435e90();                         // 0x00435e90  GetRecorderState
void   FUN_00435ed0(void*, uint32_t);          // 0x00435ed0  KillSetiEffects
uint32_t FUN_00ccefb0(void*, void*);           // 0x00ccefb0  GetTribeCursorID
void*  FUN_0067cab0();                         // 0x0067cab0
void   FUN_00b69990(void*);                    // 0x00b69990
void*  FUN_00ac80d0(void*, uint32_t);          // 0x00ac80d0
void   FUN_00ad92d0(void*);                    // 0x00ad92d0  eastl vector dtor
void   FUN_00ccece0(void*);                    // 0x00ccece0  ShowSelection
void*  FUN_00cd40b0();                         // 0x00cd40b0  cTribeModeStrategy::Instance
void*  FUN_00bca2c0();                         // 0x00bca2c0  cAgentOrderManager::FirstPending
void   FUN_00b11870(void*, uint32_t);          // 0x00b11870
void*  FUN_00c9d9e0(void*);                    // 0x00c9d9e0
unsigned char FUN_00c8e7c0(void*);             // 0x00c8e7c0
float  FUN_00bfc490(void*);                    // 0x00bfc490
void*  FUN_006bb5e0();                         // 0x006bb5e0

extern "C" void* __cdecl rt_new(unsigned, const char*, int, int, const char*, int); // 0xf473a0
extern "C" void  __cdecl rt_del_array(void*);                                       // 0xf47380
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);                      // 0x11e0744
extern "C" void* __cdecl memmove(void*, const void*, unsigned);                     // 0x13cc480

unsigned char g_ccff40Gate;                    // 0x01686af0

// direct-call helpers with their real calling conventions
void*  FUN_00a206f0();                                      // 0x00a206f0 EA::Audio::GetSystemAT
void*  FUN_008013c0(void*);                                 // 0x008013c0 (thiscall)
unsigned char FUN_00801bb0(void*, uint32_t);                // 0x00801bb0 (thiscall)
void*  FUN_00bfc5f0(void*);                                 // 0x00bfc5f0 (thiscall)
void   FUN_00af1450(void*);                                 // 0x00af1450 (thiscall, 0 args)
void   FUN_00579a90(void*, const wchar_t*);                 // 0x00579a90 (thiscall, 1 arg)
void*  FUN_00b82fc0(void*, void*);                          // 0x00b82fc0 (thiscall)
void*  FUN_00b88590(void*, void*);                          // 0x00b88590 (thiscall)
void*  FUN_00c275b0(void*, int, void*, void*);              // 0x00c275b0 (thiscall)
void   FUN_006a3570(void*, void*);                          // 0x006a3570 (thiscall)
unsigned char FUN_00cd4460(void*, uint32_t);                // 0x00cd4460 (thiscall)
void   FUN_00cd6980(void*, uint32_t);                       // 0x00cd6980 (thiscall)

// ---------------------------------------------------------------------------
// eastl fixed-capacity pointer vector (begin/end/cap/inline-buffer)
// ---------------------------------------------------------------------------
struct PtrVec {
    void**  mpBegin;    // +0x00
    void**  mpEnd;      // +0x04
    void**  mpCap;      // +0x08
    void*   mPad0c;     // +0x0c
    void**  mpBuf;      // +0x10  points at the inline storage
    void push_back(void** value);                // 0x00cd0a70
    void insert(void** position, void** value);  // 0x00cd0550
};

// @ 0x00cd0a70
void PtrVec::push_back(void** value)
{
    void** p = mpEnd;
    if (p < mpCap) {
        mpEnd = p + 1;
        if (p != 0)
            *p = *value;
        return;
    }
    insert(p, value);
}

// @ 0x00cd0550
void PtrVec::insert(void** position, void** value)
{
    if (mpEnd != mpCap) {
        void** v = value;
        if (v >= position && v < mpEnd)
            v = v + 1;
        if (mpEnd != 0)
            *mpEnd = mpEnd[-1];
        void** last = mpEnd - 1;
        int n = (int)((char*)last - (char*)position);
        memmove((char*)mpEnd - ((n >> 2) * 4), position, n);
        *position = *v;
        mpEnd = mpEnd + 1;
        return;
    }

    int newcap = (int)(mpEnd - mpBegin);
    void** nb;
    if (newcap <= 0) {
        newcap = 1;
    } else {
        newcap = newcap * 2;
        if (newcap == 0) {
            nb = 0;
            goto alloc_done;
        }
    }
    nb = (void**)rt_new(newcap * 4, "Simulator", 0, 0, "alloc", 0xd1);
alloc_done:
    void** p = (void**)memcpy(nb, mpBegin, (unsigned)((char*)position - (char*)mpBegin));
    p = (void**)((char*)p + ((char*)position - (char*)mpBegin));
    if (p != 0)
        *p = *value;
    void** e = mpEnd;
    void* q = memcpy(p + 1, position, (unsigned)((char*)e - (char*)position));
    void** ne = (void**)((char*)q + ((((char*)e - (char*)position) >> 2) * 4));
    if (mpBegin != 0 && mpBegin != mpBuf)
        rt_del_array(mpBegin);
    mpBegin = nb;
    mpEnd = ne;
    mpCap = nb + newcap;
}

// ---------------------------------------------------------------------------
// eastl vector<AutoRefCount,...> with an inline fixed buffer on the stack
// ---------------------------------------------------------------------------
struct StackVec {
    void**  mpBegin;    // +0x00
    void**  mpEnd;      // +0x04
    void**  mpCap;      // +0x08
    void*   mX0c;       // +0x0c
    void*   mX10;       // +0x10
    void*   mX14;       // +0x14
    void*   mBuf[16];   // +0x18
    void init()
    {
        mX14    = 0;
        mpBegin = &mBuf[0];
        mpEnd   = &mBuf[0];
        mpCap   = &mBuf[16];
    }
};

// heap-backed eastl vector header (no inline buffer)
struct HeapVec {
    void** mpBegin;     // +0x00
    void** mpEnd;       // +0x04
    void** mpCap;       // +0x08
};

// ---------------------------------------------------------------------------
// 0x00cd0260 -- predicate over the neighbour-cursor id
// ---------------------------------------------------------------------------
// @ 0x00cd0260
unsigned char __stdcall FUN_00cd0260(void* arg)
{
    switch (FUN_00ccefb0(arg, 0)) {
    case 4:
    case 6:
    case 9:  case 10: case 11: case 12: case 13: case 14: case 15: case 16:
    case 17: case 18: case 19: case 20: case 21: case 22: case 23: case 24:
    case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
    case 33: case 34: case 35: case 36: case 37: case 38: case 39: case 40:
    case 41: case 42: case 43: case 45: case 46: case 47: case 48:
        return 1;
    default:
        return 0;
    }
}

// ---------------------------------------------------------------------------
// input-strategy members
// ---------------------------------------------------------------------------
struct CInput {
    void F_ccfc20(void* arg);                            // 0x00ccfc20
    void F_ccfcf0(void* vec, int key, void* a, void* b); // 0x00ccfcf0
    void F_cd07c0(void* a, void* b, void* c);            // 0x00cd07c0
    int  F_cd0830(void* arg);                            // 0x00cd0830
    void F_cd0950();                                     // 0x00cd0950
    void F_cd02d0(void* pos);                            // 0x00cd02d0
    int  F_cd0660(void* flags, void* pos, void* c);      // 0x00cd0660
};

struct CMgr { int M_e9b0(void* vec, int key, void* a, void* b); };

// @ 0x00ccfc20
void CInput::F_ccfc20(void* arg)
{
    StackVec vec;
    vec.init();

    void* tc = GetGameTerrainCursor();
    ((void(__thiscall*)(void*, void*)) (*(void***)tc)[0x5c / 4])(tc, &vec);

    for (void** it = vec.mpBegin; it != vec.mpEnd; ++it) {
        if (*it != 0) {
            void* t = ((void*(__thiscall*)(void*, uint32_t)) (*(void***)*it)[0xb8 / 4])(*it, 0x4f176642);
            if (t != 0)
                ((void(__thiscall*)(void*, void*)) (*(void***)t)[0xf0 / 4])(t, arg);
        }
    }
    for (void** it2 = vec.mpEnd; it2 < vec.mpCap; ++it2) {
        if (*it2 != 0)
            ((void(__thiscall*)(void*)) (*(void***)*it2)[0xc0 / 4])(*it2);
    }

    if (vec.mpBegin != 0 && ((int*)vec.mpBegin)[-1] != 0)
        rt_del_array(vec.mpBegin);
}

// @ 0x00ccfcf0
void CInput::F_ccfcf0(void* vec, int key, void* a, void* b)
{
    if (((CMgr*)this)->M_e9b0(vec, key, a, b) != 0)
        return;

    F_ccfc20((void*)key);

    switch (key) {
    case 0:  { FUN_00435ed0(FUN_00435e90(), 0xa1f51624); return; }
    case 1:  { FUN_00435ed0(FUN_00435e90(), 0xcfd23998); return; }
    case 2:  { FUN_00435ed0(FUN_00435e90(), 0x35988437); return; }
    case 5:  { FUN_00435ed0(FUN_00435e90(), 0x0cc04a90); return; }
    case 7:  { FUN_00435ed0(FUN_00435e90(), 0x0b14abee); return; }
    case 8:  case 15: { FUN_00435ed0(FUN_00435e90(), 0x53eb2296); return; }
    case 9:  case 21: { FUN_00435ed0(FUN_00435e90(), 0x2f154034); return; }
    case 10: { FUN_00435ed0(FUN_00435e90(), 0xf3991445); return; }
    case 11: { FUN_00435ed0(FUN_00435e90(), 0xbfc0a391); return; }
    case 12: { FUN_00435ed0(FUN_00435e90(), 0xebf31cbe); return; }
    case 13: { FUN_00435ed0(FUN_00435e90(), 0x3c9af58a); return; }
    case 14: { FUN_00435ed0(FUN_00435e90(), 0xebb53b1a); return; }
    case 20: { FUN_00435ed0(FUN_00435e90(), 0xc30c84c5); return; }
    case 24: { FUN_00435ed0(FUN_00435e90(), 0x76796a51); return; }
    case 25: { FUN_00435ed0(FUN_00435e90(), 0x92bcb575); return; }
    case 26: { FUN_00435ed0(FUN_00435e90(), 0xf1cc1ac4); return; }
    case 27: { FUN_00435ed0(FUN_00435e90(), 0x8a8e072b); }
    }
}

// @ 0x00cd07c0
void CInput::F_cd07c0(void* a, void* b, void* c)
{
    StackVec vec;
    vec.init();

    void* tc = GetGameTerrainCursor();
    ((void(__thiscall*)(void*, void*)) (*(void***)tc)[0x5c / 4])(tc, &vec);

    F_ccfcf0(&vec, (int)a, b, c);
    ((void(__thiscall*)(void*)) FUN_00ad92d0)(&vec);
}

// @ 0x00cd0950
void CInput::F_cd0950()
{
    const wchar_t* str[3];
    if (*(int*)((char*)this + 0xc8) == 1) {
        *(int*)((char*)this + 0xc8) = 0;
        ((void*(__thiscall*)(void*)) FUN_00bfc5f0)(FUN_00b3d300());
        void* cam = FUN_00b3d280();
        if (cam != 0)
            ((void(__thiscall*)(void*, uint32_t)) FUN_00b11870)(cam, 0xcf0a771b);
        void* inst = FUN_00cd40b0();
        str[0] = 0;
        str[1] = 0;
        str[2] = 0;
        ((void(__thiscall*)(void*, const wchar_t*)) FUN_00579a90)((void*)str, L"Free Camera OFF");
        ((void(__thiscall*)(void*)) FUN_00af1450)(((void*(__thiscall*)(void*, void*)) (*(void***)inst)[0x6c / 4])(inst, (void*)str));
        if ((((char*)str[1] - (char*)str[0]) & ~1) > 2 && str[0] != 0)
            rt_del_array((void*)str[0]);
        return;
    }

    *(int*)((char*)this + 0xc8) = 1;
    void* inst = FUN_00cd40b0();
    str[0] = 0;
    str[1] = 0;
    str[2] = 0;
    ((void(__thiscall*)(void*, const wchar_t*)) FUN_00579a90)((void*)str, L"Free Camera ON");
    ((void(__thiscall*)(void*)) FUN_00af1450)(((void*(__thiscall*)(void*, void*)) (*(void***)inst)[0x6c / 4])(inst, (void*)str));
    if ((((char*)str[1] - (char*)str[0]) & ~1) > 2 && str[0] != 0)
        rt_del_array((void*)str[0]);
    if (FUN_00b3d280() != 0)
        ((void(__thiscall*)(void*, uint32_t)) FUN_00b11870)(FUN_00b3d280(), 0xcf14603b);
}

// @ 0x00cd0830
int CInput::F_cd0830(void* arg)
{
    void* sub = (char*)arg + 0x120;
    float f158 = *(float*)((char*)arg + 0x158);
    if (f158 > ((float(__thiscall*)(void*)) (*(void***)sub)[0x58 / 4])(sub)) {
        if (FUN_00bfc490(sub) > 0.0f) {
            F_cd07c0((void*)0x18, arg, 0);
            return 1;
        }
    }

    switch (((int(__thiscall*)(void*)) (*(void***)arg)[0x58 / 4])(arg)) {
    case 1: case 2: case 3: case 4: case 5:
    case 6: case 7: case 8: case 9:
        F_cd07c0((void*)3, arg, 0);
        return 1;
    case 10: {
        void* t = FUN_00c9d9e0(arg);
        void* sub2 = (char*)t + 0x120;
        if (((unsigned char(__thiscall*)(void*)) (*(void***)sub2)[0x58 / 4])(sub2)) {
            if (!FUN_00c8e7c0(t)) {
                F_cd07c0((void*)0xc, arg, 0);
                void* b = (char*)arg + 0x34;
                float f = ((float(__thiscall*)(void*, int)) (*(void***)b)[0x34 / 4])(b, 1);
                void* r = ((void*(__thiscall*)(void*, uint32_t, int, float)) (*(void***)b)[0x2c / 4])(b, 0x4ae30884, 0, f);
                FUN_00ccece0(r);
            }
        }
        break;
    }
    }
    return 1;
}

// @ 0x00ccff40
void FUN_00ccff40()
{
    if (g_ccff40Gate != 0)
        return;

    void* o  = FUN_00b3d240();
    void* ob = ((void*(__thiscall*)(void*)) (*(void***)o)[0x30 / 4])(o);
    uint32_t di = 0;
    if (ob != 0)
        di = (uint32_t)((void*(__thiscall*)(void*, uint32_t)) (*(void***)ob)[0xc / 4])(ob, 0x17f243b);

    uint32_t esi = 0x1002;
    switch (FUN_00ccefb0(ob, 0)) {
    case 0: case 1: break;
    case 2: esi = (uint32_t)((void*(__thiscall*)(void*)) FUN_008013c0)(FUN_0067cab0()); break;
    case 3: case 5: esi = 0x5ecbdffd; break;
    case 4: esi = 0xf212a38b; break;
    case 6: esi = 0xf6879190; break;
    case 7: esi = 0x03a204b0; break;
    case 8: esi = 0x0600cd69; break;
    case 9:  FUN_00b69990((void*)di); esi = 0x0525ff0f; break;
    case 10: case 11: case 12: FUN_00b69990((void*)di); esi = 0x03570021; break;
    case 13: FUN_00b69990((void*)di); esi = 0xf59ce677; break;
    case 14: FUN_00b69990(FUN_00ac80d0((void*)di, 0x1e4daae)); esi = 0x8b875bdc; break;
    case 15: FUN_00b69990(FUN_00ac80d0((void*)di, 0x1e4daae)); break;
    case 16: FUN_00b69990((void*)di); esi = 0x8b875bdc; break;
    case 17: FUN_00b69990((void*)di); esi = 0x03febe37; break;
    case 18: FUN_00b69990((void*)di); esi = 0x03febe38; break;
    case 19: FUN_00b69990((void*)di); esi = 0x063fe8d9; break;
    case 20: FUN_00b69990((void*)di); esi = 0x063fe8d7; break;
    case 21: FUN_00b69990((void*)di); esi = 0x063fe8d8; break;
    case 22: FUN_00b69990((void*)di); esi = 0x063fe8d5; break;
    case 23: FUN_00b69990((void*)di); esi = 0x063fe8d4; break;
    case 24: FUN_00b69990((void*)di); esi = 0x063fe8d6; break;
    case 25: FUN_00b69990((void*)di); esi = 0x03febe3b; break;
    case 26: FUN_00b69990((void*)di); esi = 0x03febe3d; break;
    case 27: case 28: case 29: case 35: case 36: case 37:
        esi = 0x03febe40; break;
    case 30: esi = 0x03febe51; break;
    case 31: esi = 0x03febe50; break;
    case 32: esi = 0x03febe52; break;
    case 33: esi = 0x03febe42; break;
    case 34: esi = 0x03febe3f; break;
    case 38: {
        void* o2 = ((void*(__thiscall*)(void*)) FUN_00bfc5f0)(FUN_00b3d300());
        FUN_00b69990(((void*(__thiscall*)(void*)) (*(void***)o2)[0xac / 4])(o2));
        break;
    }
    case 39: case 43: case 45: FUN_00b69990((void*)di); esi = 0x0525ff7d; break;
    case 40: FUN_00b69990((void*)di); esi = 0x03febe33; break;
    case 41: FUN_00b69990((void*)di); esi = 0xe382f00e; break;
    case 42: case 44: case 46: FUN_00b69990((void*)di); break;
    case 47: FUN_00b69990((void*)di); esi = 0x0648fbf1; break;
    }

    if ((uint32_t)((void*(__thiscall*)(void*)) FUN_008013c0)(FUN_0067cab0()) != esi)
        ((unsigned char(__thiscall*)(void*, uint32_t)) FUN_00801bb0)(FUN_0067cab0(), esi);
}

// @ 0x00cd02d0
void CInput::F_cd02d0(void* posf)
{
    float* pos = (float*)posf;
    void* auth = FUN_00a206f0();
    uint32_t uSound = 0;
    if (auth != 0)
        uSound = (uint32_t)((void*(__thiscall*)(void*)) (*(void***)auth)[0x20 / 4])(auth);

    void* au = FUN_00a206f0();
    if (au != 0) {
        ((void(__thiscall*)(void*, uint32_t)) (*(void***)au)[0x38 / 4])(au, 0x3475365);
        ((void(__thiscall*)(void*, uint32_t, uint32_t)) (*(void***)au)[0x40 / 4])(au, 0x3475381, 0xc45c1574);
        ((void(__thiscall*)(void*, uint32_t, uint32_t)) (*(void***)au)[0x40 / 4])(au, 0x3475385, uSound);
        ((void(__thiscall*)(void*)) (*(void***)au)[0x58 / 4])(au);
    }

    void* planet   = FUN_00b3d350();
    void* someObj  = ((void*(__thiscall*)(void*, void*)) FUN_00b82fc0)(planet, posf);
    void* someObj2 = ((void*(__thiscall*)(void*, void*)) FUN_00b88590)(planet, posf);
    void* tribe    = ((void*(__thiscall*)(void*)) FUN_00bfc5f0)(FUN_00b3d300());
    void* inner0   = (char*)tribe + 0x120;
    void* id       = ((void*(__thiscall*)(void*)) (*(void***)inner0)[0x2c / 4])(inner0);
    void* plr      = ((void*(__thiscall*)(void*, void*)) FUN_00b88590)(planet, id);

    if (someObj == 0) {
        if (FUN_00ccefb0(0, posf) != 7) {
            HeapVec vec;
            vec.mpBegin = 0;
            vec.mpEnd = 0;
            vec.mpCap = 0;
            void* tc = GetGameTerrainCursor();
            ((void(__thiscall*)(void*, void*)) (*(void***)tc)[0x5c / 4])(tc, &vec);

            char first = 1;
            for (void** it = vec.mpBegin; it != vec.mpEnd; ++it) {
                void* citizen = 0;
                if (*it != 0)
                    citizen = ((void*(__thiscall*)(void*, uint32_t)) (*(void***)*it)[0xb8 / 4])(*it, 0x4f176642);

                void* inner = (char*)citizen + 0xc0;
                void* cid = ((void*(__thiscall*)(void*)) (*(void***)inner)[0x2c / 4])(inner);
                void* cobj = ((void*(__thiscall*)(void*, void*)) FUN_00b88590)(planet, cid);

                if (someObj == cobj
                 || *((char*)cobj + *(int*)((char*)planet + 100)) == 0
                 || someObj == someObj2) {
                    if (first) {
                        first = 0;
                        void* m = FUN_00b3d240();
                        ((void(__thiscall*)(void*, uint32_t, void*)) (*(void***)m)[0x6c / 4])(m, 0x1d110a0, posf);
                    }
                    void* ord = FUN_00bca2c0();
                    if (ord == 0 || *(int*)ord != 4 || *(short*)((char*)ord + 0x4b) != 0x31) {
                        void* ord2 = ((void*(__thiscall*)(void*, int, void*, void*)) FUN_00c275b0)(citizen, 4, 0, 0);
                        ((void(__thiscall*)(void*, void*)) FUN_006a3570)((char*)ord2 + 0x39, posf);
                    } else {
                        float* pf;
                        short s = *(short*)((char*)ord + 0x4b);
                        if (s == 0x31 || s == 0x10) {
                            if ((*(unsigned char*)((char*)ord + 0x49) & 0x30) == 0)
                                pf = (float*)((char*)ord + 0x39);
                            else
                                pf = *(float**)((char*)ord + 0x39);
                        } else {
                            pf = (float*)FUN_006bb5e0();
                        }
                        float dx = pf[0] - pos[0];
                        float dy = pf[1] - pos[1];
                        float dz = pf[2] - pos[2];
                        if (dx*dx + dy*dy + dz*dz > 1.0f) {
                            void* ord2 = ((void*(__thiscall*)(void*, int, void*, void*)) FUN_00c275b0)(citizen, 4, 0, 0);
                            ((void(__thiscall*)(void*, void*)) FUN_006a3570)((char*)ord2 + 0x39, posf);
                        }
                    }
                    ((void(__thiscall*)(void*, int)) (*(void***)citizen)[0xf0 / 4])(citizen, 4);
                } else {
                    void* m = FUN_00b3d240();
                    ((void(__thiscall*)(void*, uint32_t, void*)) (*(void***)m)[0x6c / 4])(m, 0xb062b167, posf);
                }
            }
            ((void(__thiscall*)(void*)) FUN_00ad92d0)(&vec);
            return;
        }
    }
    void* m = FUN_00b3d240();
    ((void(__thiscall*)(void*, uint32_t, void*)) (*(void***)m)[0x6c / 4])(m, 0xb062b167, posf);
}

// @ 0x00cd0660
int CInput::F_cd0660(void* flags, void* pos, void* c)
{
    void* tc = GetGameTerrainCursor();
    ((void(__thiscall*)(void*, int)) (*(void***)tc)[0xb8 / 4])(tc, 0);
    tc = GetGameTerrainCursor();
    ((void(__thiscall*)(void*)) (*(void***)tc)[0xa4 / 4])(tc);
    tc = GetGameTerrainCursor();
    ((void(__thiscall*)(void*, float)) (*(void***)tc)[0xac / 4])(tc, 1.0f);
    tc = GetGameTerrainCursor();
    ((void(__thiscall*)(void*, float)) (*(void***)tc)[0xb0 / 4])(tc, 1.0f);

    StackVec vec;
    vec.init();
    tc = GetGameTerrainCursor();
    ((void(__thiscall*)(void*, void*)) (*(void***)tc)[0x5c / 4])(tc, &vec);

    if (flags == 0 && vec.mpBegin != vec.mpEnd) {
        if (((unsigned char(__thiscall*)(void*, uint32_t)) FUN_00cd4460)(*(void**)((char*)this + 0x40), 0x56d1871))
            goto done0;
        if (!((unsigned char(__thiscall*)(void*, uint32_t)) FUN_00cd4460)(*(void**)((char*)this + 0x40), 0x64be5ff))
            goto done0;
        ((void(__thiscall*)(void*, uint32_t)) FUN_00cd6980)(*(void**)((char*)this + 0x40), 0x5ac72d7c);
        ((void(__thiscall*)(void*)) FUN_00ad92d0)(&vec);
        return 0;
    }

    if (((int)flags & 2) != 0) {
        if (vec.mpBegin == vec.mpEnd) {
            ((void(__thiscall*)(void*)) FUN_00ad92d0)(&vec);
            return 1;
        }
        float* p = (float*)pos;
        if (p[0]*p[0] + p[1]*p[1] + p[2]*p[2] > 0.0f)
            F_cd02d0(pos);
    }

done0:
    ((void(__thiscall*)(void*)) FUN_00ad92d0)(&vec);
    return 0;
}