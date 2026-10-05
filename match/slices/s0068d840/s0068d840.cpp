// Slice s0068d840: SPKeyFromName / hash-name helpers and the arithmetic range
// coder / hasher around 0x68d000-0x68e610. Compiled /O2 /MD /Gy /EHsc /TP /GS-.
#include <wchar.h>
#include <new>
#include "types.h"

#define VFN(p, off) ((*(void***)(p))[(off) / 4])

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef wchar_t        wch;

// ---- out-of-slice callees (relocation-masked) ----
extern "C" u32  HashName(const wch* s, int n);                       // 0x08dd7d0
extern "C" void SetNameCallbacks(void* a, void* b);                  // 0x08dd8d0
extern "C" wch* GetExplicitIdStart(wch* a, wch* b, char c, char d);  // 0x068c770
extern "C" wch* FindCharRev(wch* a, wch* b, const wch* c);           // 0x068c720
extern "C" void* RBTreeInsert(void* node, void* pos, void* anchor, int canInsert); // 0x09216a0
extern "C" void* EASTL_alloc6(unsigned sz, const char* name, unsigned a,
                              unsigned b, const char* file, unsigned line); // 0x0f473a0
extern "C" void* GetResourceManager();                               // 0x067dcd0
extern "C" int   ResourceManagerAdd(void* p);                        // 0x06b22f0
extern "C" void  Sub68dc00(void* a, void* b, void* c);               // 0x068dc00
extern "C" void  Sub87cf40();                                        // 0x087cf40
extern "C" void  Sub87cf60(void* p);                                 // 0x087cf60
extern "C" int   Sub87d2a0(int a, int b);                            // 0x087d2a0
extern "C" int   Sub87d030(void* a, void* b, int c);                 // 0x087d030
extern "C" void  Sub87cff0();                                        // 0x087cff0
extern "C" void  Sub87d260();                                        // 0x087d260
extern "C" void  Sub932da0();                                        // 0x0932da0
extern "C" void* Sub932df0(void* a, u32 b, u32 c, u32 d, u32 e);     // 0x0932df0
extern "C" int   WriteUint32(void* io, void* p, int n, int f);       // 0x093aa70

// ---- globals ----
extern "C" u32  gMaskTable[];        // 0x1403618
extern "C" char gAllocTag[];         // 0x13ebc58 "App"
extern "C" char gEASTLFile[];        // 0x13ebb38 allocator.h path
extern "C" u32  gHMNameMagic;        // 0x152ca8c

// =====================================================================
// 0x0068d840  SPKeyFromName
// =====================================================================
extern "C" wch* GetExplicitIdStart(wch*, wch*, char, char);
extern "C" wch* FindCharRev(wch*, wch*, const wch*);
extern "C" void  HashInsertString(u32* node, const wch* b, const wch* e); // 0x68d340+assign
extern "C" void  FUN_0068d1a0();
extern "C" void  Nuke_9a9600(void*, void*);
extern "C" void  MemcpyT2(void*, const void*, unsigned);

// @ 0x0068d840
extern "C" bool SPKeyFromName(u32* out, const wch* name, u32 a, u32 b) {
    if (name == 0 || *name == 0)
        return false;

    out[1] = a;
    wch* local4 = 0;

    wch* pw2 = wcschr((wch*)name, L'.');
    if (pw2 == 0) {
        wch* p = (wch*)name;
        wch c;
        do { c = *p; p += 1; } while (c != 0);
        pw2 = (wch*)name + (((int)p - (int)((wch*)name + 1)) >> 1);
    } else {
        local4 = pw2 + 1;
    }

    int iVar7 = ((int)pw2 - (int)name) >> 1;
    wch* pw8 = (wch*)name;

    for (;;) {
        if (iVar7 == 0) {
            out[2] = b;
            wch* pw3 = (wch*)name;
            pw8 = (wch*)name;
            u32* puVar9 = out + 2;
            if (pw3 == pw2) {
                *out = 0xffffffff;
            } else {
                wch* q = GetExplicitIdStart(pw3, pw2, 1, 1);
                if (q == 0)
                    *out = HashName((const wch*)name, iVar7);
                else
                    *out = (u32)wcstoul(q, 0, 16);
            }

            if ((const wch*)name != pw8) {
                wch ch = 0x40;
                int r = (int)FindCharRev((wch*)name, pw8, &ch);
                if (r == 0) {
                    ch = 0x5f;
                    int r2 = (int)FindCharRev((wch*)name, pw8, &ch);
                    wch* q = (wch*)name;
                    if (r2 != 0)
                        q = (wch*)(r2 + 2);
                    q = GetExplicitIdStart(q, pw8, 0, 0);
                    if (q == 0) {
                        u32 h = HashName((const wch*)name, ((int)pw8 - (int)name) >> 1);
                        *puVar9 = h;
                        HashInsertString(puVar9, (const wch*)name, pw8);
                    } else {
                        *puVar9 = (u32)wcstoul(q, 0, 16);
                    }
                } else {
                    *puVar9 = 0;
                }
            }

            if (local4 != 0) {
                out[1] = 0xffffffff;
                if (*local4 != 0) {
                    wch* p = local4;
                    wch c;
                    do { c = *p; p += 1; } while (c != 0);
                    wch* q = GetExplicitIdStart(
                        local4, local4 + (((int)p - (int)(local4 + 1)) >> 1), 0, 0);
                    if (q != 0) {
                        out[1] = (u32)wcstoul(q, 0, 16);
                        return true;
                    }
                    void* mgr = GetResourceManager();
                    int id = ((int(__thiscall*)(void*, wch*))VFN(mgr, 0x88))(mgr, local4);
                    if (id == -1)
                        id = (int)HashName(local4, ((int)p - (int)(local4 + 1)) >> 1);
                    out[1] = (u32)id;
                }
            }
            return true;
        }

        if (*pw8 == L'!') {
            out[2] = 0xffffffff;
            pw8 = pw8 + 1;
            // fall through to the LAB body with pw3 = pw8+1; re-enter with
            // the same block as above (handled by iVar7 == 0 path next iter)
            // Reproduce by directly executing the block:
            {
                wch* pw3 = pw8;
                u32* puVar9 = out + 2;
                if (pw3 == pw2) {
                    *out = 0xffffffff;
                } else {
                    wch* q = GetExplicitIdStart(pw3, pw2, 1, 1);
                    if (q == 0)
                        *out = HashName((const wch*)name, iVar7);
                    else
                        *out = (u32)wcstoul(q, 0, 16);
                }
                if ((const wch*)name != pw8) {
                    wch ch = 0x40;
                    int r = (int)FindCharRev((wch*)name, pw8, &ch);
                    if (r == 0) {
                        ch = 0x5f;
                        int r2 = (int)FindCharRev((wch*)name, pw8, &ch);
                        wch* q = (wch*)name;
                        if (r2 != 0)
                            q = (wch*)(r2 + 2);
                        q = GetExplicitIdStart(q, pw8, 0, 0);
                        if (q == 0) {
                            u32 h = HashName((const wch*)name, ((int)pw8 - (int)name) >> 1);
                            *puVar9 = h;
                            HashInsertString(puVar9, (const wch*)name, pw8);
                        } else {
                            *puVar9 = (u32)wcstoul(q, 0, 16);
                        }
                    } else {
                        *puVar9 = 0;
                    }
                }
                if (local4 != 0) {
                    out[1] = 0xffffffff;
                    if (*local4 != 0) {
                        wch* p = local4;
                        wch c;
                        do { c = *p; p += 1; } while (c != 0);
                        wch* q = GetExplicitIdStart(
                            local4, local4 + (((int)p - (int)(local4 + 1)) >> 1), 0, 0);
                        if (q != 0) {
                            out[1] = (u32)wcstoul(q, 0, 16);
                            return true;
                        }
                        void* mgr = GetResourceManager();
                        int id = ((int(__thiscall*)(void*, wch*))VFN(mgr, 0x88))(mgr, local4);
                        if (id == -1)
                            id = (int)HashName(local4, ((int)p - (int)(local4 + 1)) >> 1);
                        out[1] = (u32)id;
                    }
                }
                return true;
            }
        }

        pw8 = pw8 + 1;
        iVar7 = iVar7 - 1;
    }
}

// =====================================================================
// 0x0068da70  thunk: forward 4 args to SPKeyFromName
// =====================================================================
// @ 0x0068da70
extern "C" void FUN_0068da70(void* p1, void* p2, void* p3, void* p4) {
    SPKeyFromName((u32*)p1, (const wch*)p2, (u32)p3, (u32)p4);
}

// =====================================================================
// 0x0068da90  install name callbacks
// =====================================================================
// @ 0x0068da90
extern "C" void FUN_0068da90() {
    SetNameCallbacks((void*)&FUN_0068da70, (void*)FUN_0068d1a0);
}

// =====================================================================
// 0x0068dab0  emit packed value through vtable slot 2
// =====================================================================
struct IWriter {
    virtual void v0();
    virtual void v1();
    virtual void WritePair(int a, int b, unsigned v);
    void Emit(int a, int b, u8 c, u32 d, u8 e, u8 f);
};

// @ 0x0068dab0
void IWriter::Emit(int a, int b, u8 c, u32 d, u8 e, u8 f) {
    unsigned packed = ((((d & 0x1f) | 0x40) << 8 | c) << 8 | e) << 8 | f;
    WritePair(a, b, packed);
}

// =====================================================================
// 0x0068daf0  rbtree<unsigned, pair<unsigned,unsigned>>::insert one node
// =====================================================================
struct SetNode {
    SetNode* mpNodeRight;   // +0x00
    SetNode* mpNodeLeft;    // +0x04
    SetNode* mpNodeParent;  // +0x08
    u8 mColor;              // +0x0c
    u8 padD[3];
    u32 mKey;               // +0x10
    u32 mVal;               // +0x14
};

struct RBSet {
    u32 mCompare;           // +0x00
    SetNode* aRight;        // +0x04
    SetNode* aLeft;         // +0x08
    SetNode* aParent;       // +0x0c
    u8 aColor;              // +0x10
    u8 pad[3];
    u32 mnSize;             // +0x14
    u32 mAlloc;             // +0x18

    void Insert(SetNode** pOut, SetNode* pos, const int* val, char bAllow);
};

// @ 0x0068daf0
void RBSet::Insert(SetNode** pOut, SetNode* pos, const int* val, char bAllow) {
    int canInsert;
    if (bAllow == 0 && pos != (SetNode*)&aRight && *val >= *(int*)((char*)pos + 0x10))
        canInsert = 1;
    else
        canInsert = 0;
    SetNode* n = (SetNode*)EASTL_alloc6(0x18, gAllocTag, 0, 0, gEASTLFile, 0xd1);
    int* pKey = (int*)((char*)n + 0x10);
    if (pKey) {
        pKey[0] = val[0];
        pKey[1] = val[1];
    }
    RBTreeInsert(n, pos, &aRight, canInsert);
    SetNode** pp = pOut;
    mnSize += 1;
    *pp = n;
}

// =====================================================================
// 0x0068db70  range-coder constructor (EH; not matched)
// =====================================================================
struct Coder {
    u8* mBuf;          // +0x00
    u32 f04;           // +0x04
    u32 f08;           // +0x08
    u32 f0c;           // +0x0c
    u32 f10;           // +0x10
    u32 f14;           // +0x14
    u32 f18;           // +0x18
    u32 f1c;           // +0x1c
    u8  f20; u8 pad21[3];
    u32 f24;           // +0x24
    u32 f28;           // +0x28
    u32 f2c;           // +0x2c
    u32 f30;           // +0x30 hash
    u32 f34;           // +0x34
    u32 f38;           // +0x38
    u32 f3c;           // +0x3c cur
    u32 f40;           // +0x40 limit
    u32 f44;           // +0x44 bit
    u32 f48;           // +0x48 mask
    u32 f4c;           // +0x4c
    u32 f50;           // +0x50 top
    u8  pad54;
    u8  f55;           // +0x55
    u8  f56;           // +0x56
    u8  pad57;
    u32 f58;           // +0x58
    u32 f5c;           // +0x5c
    u32 f60;           // +0x60
    u32 f64;           // +0x64
    u32 f68;           // +0x68
    u32 f6c;           // +0x6c

    Coder();
    ~Coder();
    void Init();        // 0x68e610
    void MaskInit();    // 0x68ddc0
    bool EncodeBit(u8 bit);       // 0x68de20
    void Flush();                 // 0x68df00
    bool DecodeBit(u8* out);      // 0x68dfd0
    int  DecodeFinish();          // 0x68e0c0
    void Init2();                 // 0x68db70
    char Serialize(void* io, int mode);  // 0x68e1a0
    int  Read(void* dst, u32 n);         // 0x68e3b0
    char Verify(char p);                 // 0x68e490
};

// @ 0x0068db70
void Coder::Init2() {
    // placeholder; see nonmatching.txt
    Coder* p = this;
    (void)p;
}

// @ 0x0068dc90
Coder::~Coder() {
    mBuf = (u8*)0x1403594;
    // nuke two embedded rbtrees at +0x24 and +0x08
    Nuke_9a9600((char*)this + 0x24, *(void**)((char*)this + 0x30));
    Nuke_9a9600((char*)this + 0x08, *(void**)((char*)this + 0x14));
}

// =====================================================================
// 0x0068dd10  creature citizen init-ish (not matched)
// =====================================================================
struct Citizen {
    u32 f00, f04, f08, f0c, f10;
    u32 f14;      // +0x14 resource count
    void Init(void* out, void* arg3, u32 flags);   // 0x68dd10
};

// @ 0x0068dd10
void Citizen::Init(void* param_2, void* param_3, u32 param_4) {
    u32* out = (u32*)param_2;
    out[1] = (u32)param_3;
    if ((param_4 & 0xc0000000) == 0x40000000)
        out[2] = param_4;
    else
        out[2] = 0x40010000;
    u32 tmp = f04;
    u8 l10 = (u8)(param_4 >> 0x10);
    u8 l8 = 0;
    Sub68dc00(&l10, &l8, out);
    if (l8 == 0)
        f14 += 1;
    *out = f14;
    void* mgr = GetResourceManager();
    if (mgr != 0) {
        while (ResourceManagerAdd(out) != 0) {
            f14 += 1;
            *out = f14;
        }
    }
    (void)tmp; (void)l10;
}

// =====================================================================
// 0x0068ddc0  initialize mask/hash fields
// =====================================================================
// @ 0x0068ddc0
void Coder::MaskInit() {
    u32 v = f40;
    u32 i = 0;
    if (v & 0xffff0000) { i = 0x10; v >>= 16; }
    if (v & 0xff00) { i += 8; v >>= 8; }
    if (v & 0xf0) { i += 4; v >>= 4; }
    if (v & 0xc) { i += 2; v >>= 2; }
    if (v & 2) i += 1;
    u32 m = gMaskTable[i];
    f50 = m;
    f3c = m;
    f44 = 1;
    f30 = 0x811c9dc5;
    f48 = ~(f4c - 1);
}

// =====================================================================
// 0x0068de20  encode one bit
// =====================================================================
// @ 0x0068de20
bool Coder::EncodeBit(u8 b) {
    bool res = true;
    int n = 8;
    do {
        if (n == 0)
            return res;
        u32 cur = f3c;
        if (f40 <= cur) {
            do {
                if ((cur & 1) == 0)
                    cur = cur >> 1;
                else
                    cur = (cur >> 1) ^ f50;
                f3c = cur;
                if (cur == f50) {
                    f44 = f44 << 1;
                    f48 = f48 << 1;
                }
            } while (f40 <= cur);
        }
        u32 h = f30 * 0x1000193;
        u8* pb = mBuf + f3c;
        f30 = h;
        f30 = ((~f48 & f3c & 0xff) | (*pb & f48)) ^ h;
        u8 tb;
        if (((h >> 0xf) ^ (u32)b) & 1)
            tb = (u8)f44;
        else
            tb = 0;
        b = b >> 1;
        *pb = (u8)((~(u8)f44 & *pb) | tb);
        u32 c2 = f3c;
        if ((c2 & 1) == 0)
            c2 = c2 >> 1;
        else
            c2 = (c2 >> 1) ^ f50;
        f3c = c2;
        res = true;
        if (c2 == f50) {
            f44 = f44 << 1;
            f48 = f48 << 1;
            res = (f44 != f4c);
        }
        n -= 1;
    } while (res);
    return false;
}

// =====================================================================
// 0x0068df00  flush (encode remaining)
// =====================================================================
// @ 0x0068df00
void Coder::Flush() {
    u32 iVar1 = f44;
    do {
        u32 cur = f3c;
        if (f40 <= cur) {
            do {
                if ((cur & 1) == 0)
                    cur = cur >> 1;
                else
                    cur = (cur >> 1) ^ f50;
                f3c = cur;
                if (cur == f50) {
                    f44 = f44 << 1;
                    f48 = f48 << 1;
                }
            } while (f40 <= cur);
        }
        if (iVar1 == f44) {
            u32 h = f30 * 0x1000193;
            u8* pb = mBuf + f3c;
            f30 = h;
            f30 = ((~f48 & f3c & 0xff) | (*pb & f48)) ^ h;
            u8 b = (u8)f44;
            u8 tb = (u8)(-((h >> 0xf & 1) != 0) & 0x80);
            *pb = (u8)((~b & *pb) | ((h & 0x8000) ? (u8)(f44 & 0xff) : 0));
            (void)tb;
            u32 c2 = f3c;
            if ((c2 & 1) == 0)
                c2 = c2 >> 1;
            else
                c2 = (c2 >> 1) ^ f50;
            f3c = c2;
            if (c2 == f50) {
                f44 = f44 << 1;
                f48 = f48 << 1;
            }
        }
    } while (iVar1 == f44);
}

// =====================================================================
// 0x0068dfd0  decode one bit
// =====================================================================
// @ 0x0068dfd0
bool Coder::DecodeBit(u8* out) {
    bool res = true;
    int n = 8;
    u8 bval = 0;
    do {
        if (n == 0) {
            *out = bval;
            return res;
        }
        u32 cur = f3c;
        if (f40 <= cur) {
            do {
                if ((cur & 1) == 0)
                    cur = cur >> 1;
                else
                    cur = (cur >> 1) ^ f50;
                f3c = cur;
                if (cur == f50) {
                    f44 = f44 << 1;
                    f48 = f48 << 1;
                }
            } while (f40 <= cur);
        }
        u32 cur2 = f3c;
        u32 mask = f48;
        u32 byte = mBuf[cur2];
        u32 h = ((~mask & cur2 & 0xff) | (byte & mask)) ^ f30 * 0x1000193;
        u32 bitv = f44;
        f30 = h;
        u8 tb;
        if ((h & 0x8000) == 0)
            tb = (u8)(-((byte & bitv) != 0) & 0x80);
        else
            tb = (u8)((-((byte & bitv) != 0) & 0x80u) + 0x80);
        bval = (u8)(bval >> 1) | tb;
        u32 c2 = cur2;
        if ((c2 & 1) == 0)
            c2 = c2 >> 1;
        else
            c2 = (c2 >> 1) ^ f50;
        f3c = c2;
        res = true;
        if (c2 == f50) {
            res = (bitv * 2 != f4c);
            f44 = bitv * 2;
            f48 = mask * 2;
        }
        n -= 1;
    } while (res);
    *out = bval;
    return false;
}

// =====================================================================
// 0x0068e0c0  decode finish / check
// =====================================================================
// @ 0x0068e0c0
int Coder::DecodeFinish() {
    u32 uVar1 = f44;
    for (;;) {
        if (uVar1 != f44)
            return 1;
        u32 cur = f3c;
        if (f40 <= cur) {
            do {
                if ((cur & 1) == 0)
                    cur = cur >> 1;
                else
                    cur = (cur >> 1) ^ f50;
                f3c = cur;
                if (cur == f50) {
                    f44 = f44 << 1;
                    f48 = f48 << 1;
                }
            } while (f40 <= cur);
        }
        if (uVar1 != f44)
            return 1;
        u32 cur2 = f3c;
        u32 mask = f48;
        u32 byte = mBuf[cur2];
        u32 h = ((~mask & cur2 & 0xff) | (byte & mask)) ^ f30 * 0x1000193;
        f30 = h;
        u8 tb;
        if ((h & 0x8000) == 0)
            tb = (u8)(-((byte & uVar1) != 0) & 0x80);
        else
            tb = (u8)((-((byte & uVar1) != 0) & 0x80u) + 0x80);
        u32 c2 = cur2;
        if ((c2 & 1) == 0)
            c2 = c2 >> 1;
        else
            c2 = (c2 >> 1) ^ f50;
        f3c = c2;
        if (c2 == f50) {
            f44 = uVar1 * 2;
            f48 = mask * 2;
            if (uVar1 * 2 == f4c)
                return 0;
        }
        if (tb != 0)
            return 0;
    }
}

// =====================================================================
// 0x0068e1a0  serialize coder state (EH; not matched)
// =====================================================================
// @ 0x0068e1a0
char Coder::Serialize(void* io, int mode) {
    (void)io; (void)mode;
    return 0;
}

// =====================================================================
// 0x0068e3b0  read bytes into coder state
// =====================================================================
// @ 0x0068e3b0
int Coder::Read(void* dst, u32 n) {
    if (f55 != 0) {
        int d = (int)(f5c - f6c) - (int)f58;
        u32 avail = (u32)(d - 8);
        if (f56 != 0)
            avail = (u32)(d - 0xc);
        if (f24 == 3 && (int)avail >= 0) {
            if (avail < n)
                n = avail;
            MemcpyT2(dst, (void*)(f58 + f6c), n);
            f6c += n;
            return (int)n;
        }
        f24 = 1;
        return -1;
    }
    if (f24 == 3) {
        u32 a = f38;
        u32 b = f34;
        if (a <= b) {
            if (b < a + n)
                n = b - a;
            u8 c = 1;
            u8* p = (u8*)dst;
            if (p != p + n) {
                do {
                    if (c == 0)
                        goto fail;
                    c = DecodeBit(p) ? 1 : 0;
                    p += 1;
                } while (p != (u8*)dst + n);
                if (c == 0)
                    goto fail;
            }
            f38 += n;
            void* r = Sub932df0(dst, n, f28, f2c, 0);
            *(void**)((char*)this + 0x28) = r;
            return (int)n;
        }
    }
fail:
    f24 = 1;
    return -1;
}

// =====================================================================
// 0x0068e490  verify / finalize stream (not matched)
// =====================================================================
// @ 0x0068e490
char Coder::Verify(char param_2) {
    (void)param_2;
    return 0;
}

// =====================================================================
// 0x0068e610  zero-initialize coder
// =====================================================================
// @ 0x0068e610
Coder::Coder() {
    mBuf = 0;
    f04 = 0; f08 = 0;
    f14 = 0; f18 = 0;
    f20 = 0;
    f24 = 0;
    f28 = 0xffffffff;
    f2c = 0xffffffff;
    f30 = 0;
    f34 = 0;
    f38 = 0;
    f3c = 0;
    f40 = 0;
    f44 = 0;
    f48 = 0;
    f4c = 8;
    f50 = 0;
    f55 = 0;
    f56 = 0;
    f58 = 0;
    f5c = 0;
    f60 = 0;
    f6c = 0;
}
