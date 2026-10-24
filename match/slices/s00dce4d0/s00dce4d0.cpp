// s00dce4d0.cpp -- gold6 batch, worker 25
// Reconstructed from the annotated disassembly + Ghidra decompiles in
// work/match/scratch_s00dce4d0_cards.txt.  Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

#define VF(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))

extern "C" void* __cdecl FUN_00b3d290(void);
extern "C" void* __cdecl FUN_00b3d300(void);                                    // SP::NounManager
extern "C" void  __cdecl FUN_00dc8d10(void*, int, void**);
extern "C" void  __cdecl FUN_00ae6e70(void*, void*);
extern "C" void  __cdecl FUN_00dcd590(void*);
extern "C" void  __cdecl FUN_00dcec60(void*, void*, void*);
extern "C" void* __cdecl FUN_00dcd6e0(void*, void*, void*);
extern "C" void  __cdecl FUN_00dc4cc0(void*, void*, void*);
extern "C" void* __cdecl FUN_00f473a0(int, const char*, int, int, int, int);    // operator_new
extern "C" void  __cdecl FUN_00f47380(void*);                                   // operator_delete_array
extern "C" void  __cdecl FUN_00cd7d10();
extern "C" void  __cdecl FUN_00d3d420();
extern "C" void  __cdecl FUN_00ace0f0();
extern "C" void  __cdecl FUN_00b1e500();
extern char DAT_018eb45e;

class TObj {
public:
    // ---- reused __thiscall callees (addresses in comments) -------------------
    void   F_db5b30(void*);                 // 0xdb5b30
    void   F_dc8ed0(void*);                 // 0xdc8ed0  hashtable::operator=
    void   F_d5d4b0(void*);                 // 0xd5d4b0  cActionCircle::operator=
    void   F_ca0940(void*);                 // 0xca0940  RefOps::AssignA
    void*  F_ac15e0();                      // 0xac15e0
    void   F_b48e40(void*, void*);          // 0xb48e40  eastl vector::erase
    void*  F_b21340(void*, void*, void*, void*, void*);   // 0xb21340 GetGameDataVector
    void   F_bab900(void*, void*);          // 0xbab900  eastl vector::insert(pos,val)
    char   F_c0c0e0();                      // 0xc0c0e0  C::Flag388

    // ---- slice targets -------------------------------------------------------
    void  FUN_00dce4d0(void*, uint32_t);
    void  FUN_00dce970(void*);
    void* FUN_00dcea90(void*);
    void  FUN_00dceca0();
    void  FUN_00dced90();
    void  FUN_00dcedb0(void*, uint32_t);
    void* FUN_00dcf180(void*, uint32_t, uint32_t);
};

#define ASSIGN_REF(dst, val) do {                     \
    void* _n = (val);                                 \
    void* _o = (dst);                                 \
    if (_n != _o) {                                   \
        if (_n) ((void(__thiscall*)(void*))VF(_n, 0xbc))(_n); \
        (dst) = _n;                                   \
        if (_o) ((void(__thiscall*)(void*))VF(_o, 0xc0))(_o); \
    }                                                 \
} while (0)

// ===========================================================================
// 0x00dcea90 - cMovingFormation entity copy-assignment (0x178-byte element)
// ===========================================================================
// @ 0x00dcea90
void* TObj::FUN_00dcea90(void* param_2) {
    char* s = (char*)param_2;
    char* d = (char*)this;
    ((TObj*)this)->F_db5b30(param_2);
    ((TObj*)(d + 0x38))->F_dc8ed0(s + 0x38);
    ASSIGN_REF(*(void**)(d + 0x58), *(void**)(s + 0x58));
    ASSIGN_REF(*(void**)(d + 0x5c), *(void**)(s + 0x5c));
    ASSIGN_REF(*(void**)(d + 0x60), *(void**)(s + 0x60));
    *(uint32_t*)(d + 0x64) = *(uint32_t*)(s + 0x64);
    *(uint32_t*)(d + 0x68) = *(uint32_t*)(s + 0x68);
    *(uint32_t*)(d + 0x6c) = *(uint32_t*)(s + 0x6c);
    *(uint32_t*)(d + 0x70) = *(uint32_t*)(s + 0x70);
    *(uint32_t*)(d + 0x74) = *(uint32_t*)(s + 0x74);
    *(uint32_t*)(d + 0x78) = *(uint32_t*)(s + 0x78);
    *(float*)(d + 0x7c) = *(float*)(s + 0x7c);
    *(float*)(d + 0x80) = *(float*)(s + 0x80);
    *(float*)(d + 0x84) = *(float*)(s + 0x84);
    *(float*)(d + 0x88) = *(float*)(s + 0x88);
    *(float*)(d + 0x8c) = *(float*)(s + 0x8c);
    *(float*)(d + 0x90) = *(float*)(s + 0x90);
    *(float*)(d + 0x94) = *(float*)(s + 0x94);
    *(uint8_t*)(d + 0x98) = *(uint8_t*)(s + 0x98);
    *(float*)(d + 0x9c) = *(float*)(s + 0x9c);
    ((TObj*)(d + 0xa0))->F_d5d4b0(s + 0xa0);
    ((TObj*)(d + 0x104))->F_d5d4b0(s + 0x104);
    *(uint32_t*)(d + 0x168) = *(uint32_t*)(s + 0x168);
    *(uint32_t*)(d + 0x16c) = *(uint32_t*)(s + 0x16c);
    *(uint32_t*)(d + 0x170) = *(uint32_t*)(s + 0x170);
    *(uint32_t*)(d + 0x174) = *(uint32_t*)(s + 0x174);
    return this;
}

// ===========================================================================
// 0x00dced90 - constructor: refresh entity list then set a 1000/0 pair
// ===========================================================================
// @ 0x00dced90
void TObj::FUN_00dced90() {
    ((TObj*)this)->FUN_00dceca0();
    *(uint32_t*)((char*)this + 0x50) = 0x3e8;
    *(uint32_t*)((char*)this + 0x54) = 0;
}

// ===========================================================================
// 0x00dceca0 - refresh: drop the first element, then gather the game-data
//              spatial objects satisfying Flag388 and append them
// ===========================================================================
// @ 0x00dceca0
void TObj::FUN_00dceca0() {
    char* d = (char*)this;
    ((TObj*)(d + 0x38))->F_b48e40(*(void**)(d + 0x38), *(void**)(d + 0x3c));
    TObj* nm = (TObj*)FUN_00b3d300();
    char* vec = (char*)nm->F_b21340((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                   (void*)FUN_00ace0f0, (void*)FUN_00b1e500, &DAT_018eb45e);
    void** begin = *(void***)(vec + 4);
    void** end = *(void***)(vec + 8);
    while (begin != end) {
        TObj* o = (TObj*)*begin;
        if (o != 0 && *(uint8_t*)((char*)o + 0x135) != 0 && ((TObj*)o)->F_c0c0e0() != 0) {
            TObj* e = (TObj*)((char*)o + 0xc0);
            void* local = e;
            if (e != 0) {
                ((void(__thiscall*)(void*))VF(e, 0xbc))(e);
            }
            void** pos = *(void***)(d + 0x3c);
            if (pos < *(void***)(d + 0x40)) {
                *(void***)(d + 0x3c) = pos + 1;
                if (pos != 0) {
                    *pos = e;
                    if (e != 0) {
                        ((void(__thiscall*)(void*))VF(e, 0xbc))(e);
                    }
                }
            } else {
                ((TObj*)(d + 0x38))->F_bab900(pos, &local);
            }
            if (e != 0) {
                ((void(__thiscall*)(void*))VF(e, 0xc0))(e);
            }
        }
        begin++;
    }
}

// ===========================================================================
// 0x00dce970 - cTrackingAction/cMovingFormation node assignment
// ===========================================================================
// @ 0x00dce970
void TObj::FUN_00dce970(void* param_2) {
    char* d = (char*)this;
    char* s = (char*)param_2;
    ((TObj*)(d + 0x64))->F_ca0940(param_2);
    TObj* t = (TObj*)FUN_00b3d290();
    *(uint32_t*)(d + 0x90) = (uint32_t)t->F_ac15e0();
    uint32_t src = *(uint32_t*)s;
    uint32_t nv;
    if (src != 0) {
        nv = ((uint32_t(__thiscall*)(void*, uint32_t))VF((void*)src, 0xc))((void*)src, 0xee9b2232);
    } else {
        nv = 0;
    }
    uint32_t ov = *(uint32_t*)(d + 0x94);
    if (nv != ov) {
        if (nv != 0) {
            ((void(__thiscall*)(void*))VF((void*)nv, 0))((void*)nv);
        }
        *(uint32_t*)(d + 0x94) = nv;
        if (ov != 0) {
            ((void(__thiscall*)(void*))VF((void*)ov, 4))((void*)ov);
        }
    }
    *(uint32_t*)(d + 0x98) = *(uint32_t*)(s + 0x14);
    ((TObj*)(d + 0x64))->F_ca0940(param_2);
    uint32_t* v1 = (uint32_t*)(d + 0x9c);
    uint32_t e1 = v1[1];
    uint32_t b1 = v1[0];
    int n1 = (int)(e1 - b1) >> 2;
    if ((uint32_t)n1 < 3u) {
        void* z = 0;
        FUN_00dc8d10((void*)e1, 3 - n1, &z);
    } else {
        FUN_00ae6e70((void*)(b1 + 0xc), (void*)e1);
    }
    uint32_t* v2 = (uint32_t*)(d + 0xb0);
    uint32_t e2 = v2[1];
    uint32_t b2 = v2[0];
    int n2 = (int)(e2 - b2) >> 2;
    if ((uint32_t)n2 < 3u) {
        void* z = 0;
        FUN_00dc8d10((void*)e2, 3 - n2, &z);
    } else {
        FUN_00ae6e70((void*)(b2 + 0xc), (void*)e2);
    }
}

// ===========================================================================
// 0x00dcf180 - eastl vector<0x178-byte element> insert / grow (DoInsertValue)
// ===========================================================================
// @ 0x00dcf180
void* TObj::FUN_00dcf180(void* param_2, uint32_t param_3, uint32_t param_4) {
    uint32_t* v = (uint32_t*)this;
    if (v[1] != v[2]) {
        uint32_t b = param_4;
        if (param_3 <= param_4 && param_4 < v[1]) {
            b = param_4 + 0x178;
        }
        if (v[1] != 0) {
            FUN_00dcd590((void*)(v[1] - 0x178));
        }
        FUN_00dcec60(param_2, (void*)(v[1] - 0x178), (void*)v[1]);
        ((TObj*)param_2)->FUN_00dcea90((void*)b);
        v[1] = v[1] + 0x178;
        return this;
    }
    int cnt = (int)((v[1] - v[0])) / 0x178;
    int cap;
    if (cnt == 0) {
        cap = 1;
    } else {
        cap = cnt * 2;
        if (cap == 0) {
            cap = 0;
            goto have;
        }
    }
    {
        int sz = cap * 0x178;
        (void)sz;
    }
have:
    int cap2;
    if (cnt == 0) {
        cap2 = 1;
    } else {
        cap2 = cnt * 2;
    }
    void* buf = 0;
    if (cap2 != 0) {
        buf = FUN_00f473a0(cap2 * 0x178, "Simulator", 0, 0, 0x13ebb38, 0xd1);
    }
    uint32_t first = v[0];
    uint32_t iVar3 = (uint32_t)FUN_00dcd6e0((void*)first, param_2, buf);
    FUN_00dc4cc0((void*)first, param_2, buf);
    if (iVar3 != 0) {
        FUN_00dcd590((void*)param_4);
    }
    uint32_t last = v[1];
    uint32_t iVar4 = (uint32_t)FUN_00dcd6e0(param_2, (void*)last, (void*)(iVar3 + 0x178));
    FUN_00dc4cc0(param_2, (void*)last, (void*)(iVar3 + 0x178));
    uint32_t old = v[0];
    if (old != 0 && *(uint32_t*)(old - 4) != 0) {
        FUN_00f47380((void*)old);
    }
    v[0] = (uint32_t)buf;
    v[1] = iVar4;
    v[2] = (uint32_t)(cap2 * 0x178 + (int)buf);
    return this;
}