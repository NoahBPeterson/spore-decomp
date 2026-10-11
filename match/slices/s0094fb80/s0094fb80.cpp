// Slice s0094fb80 -- EA::SSL (UTFNetwork/UTFSSL) part 2: SSLManager ctor/Init/Shutdown,
// OpenSSL thread-locking setup, SSLSocket BIO methods and StreamSSLSocket session methods.
// Module flags: /O2 /MD /Gy /EHsc /TP /GS-
#include <intrin.h>

typedef unsigned int uint;

// ---- raw offset accessors ----
#define B(p)         ((char*)(p))
#define I8(p,o)      (*(char*)((char*)(p)+(o)))
#define U8(p,o)      (*(unsigned char*)((char*)(p)+(o)))
#define I16(p,o)     (*(short*)((char*)(p)+(o)))
#define U16(p,o)     (*(unsigned short*)((char*)(p)+(o)))
#define I32(p,o)     (*(int*)((char*)(p)+(o)))
#define U32(p,o)     (*(unsigned*)((char*)(p)+(o)))
#define PTR(p,o)     (*(void**)((char*)(p)+(o)))

extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
#pragma intrinsic(_InterlockedIncrement, _InterlockedExchangeAdd)

void* __cdecl operator new(unsigned int, const char*, int, int, const char*, int);  // 0x00F473A0
void  __cdecl operator_delete__(void*) throw();                                     // 0x00F47380

struct ICoreAllocator {
    virtual void v00();
    virtual void* AllocA(unsigned size, const char* name, int flags, unsigned align, int off); // +4
    virtual void* AllocB(unsigned size, const char* name, int flags);                           // +8
    virtual void  Free(void* p, int flags);                                                     // +0xc
};

extern "C" void* g_spSSLManager;   // 0x0166AAA8
extern "C" int   g_lockArg;        // 0x0143FE18
extern "C" char  g_szFileName[];   // 0x0143FE48
extern "C" char  g_szUTFUp[];      // 0x0143FEE0 "UTF/SSL"
extern "C" char  g_szCiphers[];    // 0x0143FF2C "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"

// ---- thiscall externals with stack args: modelled as methods ----
struct Ext {
    void* ctor(int a, int b);               // 0x009222A0 Mutex::Mutex
    int   Lock(const void* nm);             // 0x009221B0 Mutex::Lock
    void  fixedvec_resize(unsigned n);      // 0x0089CB60 fixed_vector::resize
    void  faf0(void*, void*, void*);        // 0x0094FAF0
    int*  resize(unsigned n);               // 0x00837310 RawFixed::Resize
    void  d470(int a);                      // 0x0094D470
    int   e3a0(int a, int b, int c);        // 0x0094E3A0
    int   e3f0(int a, int b, int c);        // 0x0094E3F0
    int   e650(int a, int b, int c);        // 0x0094E650
    int   e4b0(int a, int b);               // 0x0094E4B0
    void* e340(unsigned iface);             // 0x0094E340 StreamSocket::AsInterface
    void  nuke(void* node);                 // 0x00D3B370 DoNukeSubtree
};

// ---- thiscall externals with no stack args: __fastcall (ecx only) ----
void  __fastcall Mutex_dtor(void* m);                   // 0x00922130
int   __fastcall Mutex_Unlock(void* m);                 // 0x00922270
void  __fastcall Fn0094fa00(void* map);                 // 0x0094FA00 fixed_map ctor
char  __fastcall Fn0094d3c0(void* self);                // 0x0094D3C0
int   __fastcall Fn0094d4b0(void* self);                // 0x0094D4B0
void  __fastcall Fn0094e770(void* self);                // 0x0094E770
void* __fastcall Fn0094e9a0(void* self);                // 0x0094E9A0
void  __fastcall SSLManager_RemoveSession(void* self);  // 0x0094F990

// ---- cdecl externals ----
void* __cdecl memcpy_impl(void* dst, const void* src, unsigned n); // 0x011E0744
int   __cdecl NetSSLVerifyConnection(void* ssl, const char* name); // 0x0094EC00
int   __fastcall RefCount_Release_M8(int* p);                  // 0x0094EA90
int   __cdecl Vsnprintf8(char* buf, unsigned size, const char* fmt, void* ap); // 0x00938400
int   __cdecl FStr_sprintf(char* dst, const char* fmt, const char* a, unsigned b); // 0x00950850
int   __cdecl GetThreadId();                                    // 0x00921CC0

// ---- OpenSSL / lib imports ----
extern "C" {
void  __cdecl CRYPTO_set_id_callback(void* fn);                 // 0x011812F0
void  __cdecl CRYPTO_set_locking_callback(void* fn);            // 0x011812E0
void  __cdecl Fn011812b0(void* fn);                             // 0x011812B0 dynlock_create
void  __cdecl CRYPTO_set_dynlock_lock_callback(void* fn);       // 0x011812C0
void  __cdecl CRYPTO_set_dynlock_destroy_callback(void* fn);    // 0x011812D0
unsigned __cdecl Fn01181150();                                  // 0x01181150 CRYPTO_num_locks
void  __cdecl CRYPTO_set_mem_functions(void* m, void* r, void* f); // 0x01183360
void  __cdecl CRYPTO_add_lock(int* p, int n, int type, const char* file, int line); // 0x011815D0
void* __cdecl BIO_new(void* method);                            // 0x01177470
void  __cdecl BIO_clear_flags(void* bio, int flags);            // 0x01176F90
void  __cdecl SSL_CTX_free(void* ctx);                          // 0x0117BA10
int   __cdecl SSL_CTX_set_verify(void* ctx, int mode, void* cb);// 0x0117BB10
void  __cdecl SSL_CTX_set_tmp_dh_callback(void* ctx, void* cb); // 0x0117C420
int   __cdecl SSL_CTX_set_purpose(void* ctx, int purpose);      // 0x0117BB30
long  __cdecl SSL_CTX_ctrl(void* ctx, int cmd, long larg, void* parg); // 0x0117B500
int   __cdecl SSL_CTX_set_cipher_list(void* ctx, const char* list);    // 0x0117B780
int   __cdecl Fn011831f0();                                     // 0x011831F0
void  __cdecl RAND_seed(void* buf, int n);                      // 0x01178530
void  __cdecl Fn011831e0();                                     // 0x011831E0
void* __cdecl Fn011831d0();                                     // 0x011831D0
void* __cdecl Fn011831a0();                                     // 0x011831A0
void* __cdecl Fn01182ab0();                                     // 0x01182AB0
void* __cdecl AddStat(unsigned v);                              // 0x0117CA60
void* __cdecl Fn0117c560(void* a);                              // 0x0117C560
int   __cdecl Fn0117c940(void* ssl, int cmd, long larg, void* parg);  // 0x0117C940
int   __cdecl SSL_accept(void* ssl);                            // 0x0117CDF0
int   __cdecl SSL_connect(void* ssl);                           // 0x0117CE30
void  __cdecl SSL_free(void* ssl);                              // 0x0117C790
int   __cdecl SSL_set_bio(void* ssl, void* rbio, void* wbio);   // 0x0117B350
void* __cdecl SSL_get1_session(void* ssl);                      // 0x01181620
void  __cdecl SSL_SESSION_free(void* s);                        // 0x01181750
void  __cdecl Fn01181810(void* ssl, void* session);             // 0x01181810 SSL_set_session
int   __cdecl Fn0117c8f0(void* ssl);                            // 0x0117C8F0
void* __cdecl Fn0117c440(void* ctx);                            // 0x0117C440
int   __cdecl Fn0117b410(void* ssl, void* buf, int n);          // 0x0117B410
int   __cdecl Fn0117b4a0(void* ssl, void* buf, int n);          // 0x0117B4A0
int   __cdecl Fn0117ccd0(void* ssl, int n);                     // 0x0117CCD0
int   __cdecl EC_GROUP_get_curve_name(void* g);                 // 0x011B1E50
void* __cdecl Fn00ff0420(void* p);                              // 0x00FF0420
__declspec(dllimport) __int64 __cdecl _time64(__int64*);        // 0x013CC55C
}

struct ISub {
    virtual void a00(); virtual void a04(); virtual void a08(); virtual void a0c();
    virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1c();
    virtual void a20(); virtual void* a24();
};
struct Obj8 {
    virtual void b00(); virtual void b04(); virtual void b08(); virtual void b0c();
    virtual void b10(); virtual void b14(); virtual void b18(); virtual void b1c();
    virtual void b20(); virtual void b24(); virtual void b28(); virtual void b2c();
    virtual void b30(int a);
};

struct SSLManager {
    char _b[0x190];
    SSLManager* Ctor(ICoreAllocator* alloc);                  // 0x0094FC40
    char RestoreClientSession(void* ssl, unsigned char* name); // 0x0094FD20
    void* DeletingDtor(char flags);                           // 0x0094FE70
    unsigned GetSession(const char* name);                    // 0x0094F910
    void* FindAndRelease(const char* name, char remove);      // 0x0094F870
};
struct FixedStr {
    char* begin;   // +0
    char* end;     // +4
    char* cap;     // +8
    void append(char* s, char* e);   // 0x0045F430
};
struct Sock {
    char _b[0x190];
    void* QueryInterface(unsigned iface);                     // 0x00950200
    char SetConnectState(int v);                              // 0x00950330
    unsigned Accept(int a, int b, int c);                     // 0x009503C0
    int Read(int buf, int len, unsigned char flag);           // 0x00950450
    int Write(int buf, int len, unsigned char flag);          // 0x009504D0
    int* Sprintf(const char* fmt, void* ap);                  // 0x00950650
    char GetSessionName(void* out);                           // 0x00950920
    void SetStr(char* str);                                   // 0x00950AD0
    char DoPostConnectionCheck(char* out, int a);             // 0x00950B10
};

// ===========================================================================
// @ 0x0094FB80  THREAD_cleanup
// ===========================================================================
int __cdecl THREAD_cleanup()
{
    void* mgr = g_spSSLManager;
    ICoreAllocator* alloc = (ICoreAllocator*)PTR(mgr, 0x10);
    CRYPTO_set_id_callback(0);
    CRYPTO_set_locking_callback(0);
    Fn011812b0(0);
    CRYPTO_set_dynlock_lock_callback(0);
    CRYPTO_set_dynlock_destroy_callback(0);
    mgr = g_spSSLManager;
    int count = (int)(B(PTR(mgr, 0x158)) - B(PTR(mgr, 0x154))) >> 2;
    for (int i = 0; i < count; ++i) {
        void* m = *(void**)(B(PTR(mgr, 0x154)) + i * 4);
        if (m != 0) {
            Mutex_dtor(m);
            alloc->Free(m, 0);
            mgr = g_spSSLManager;
        }
    }
    void* begin = PTR(mgr, 0x154);
    void* end = PTR(mgr, 0x158);
    memcpy_impl(begin, end, 0);
    int sz = (int)(B(end) - B(begin)) >> 2;
    I32(mgr, 0x158) += -4 * sz;
    return 1;
}

// ===========================================================================
// @ 0x0094FC40  EA::SSL::SSLManager::SSLManager(ICoreAllocator*)
// ===========================================================================
SSLManager* SSLManager::Ctor(ICoreAllocator* alloc)
{
    void* self = this;
    PTR(self, 0) = (void*)0x0143FF28;
    I8(self, 8) = 0;
    I32(self, 0xc) = 1;
    PTR(self, 0x10) = alloc;
    PTR(self, 0x14) = 0;
    ((Ext*)(B(self) + 0x18))->ctor(0, 1);
    Fn0094fa00(B(self) + 0x48);
    PTR(self, 0x14c) = 0;
    PTR(self, 0x150) = 0;
    void* pool = B(self) + 0x16c;
    PTR(self, 0x164) = pool;
    PTR(self, 0x158) = pool;
    PTR(self, 0x154) = pool;
    PTR(self, 0x15c) = B(pool) + 0x20;
    if (g_spSSLManager == 0)
        g_spSSLManager = self;
    return this;
}

// ===========================================================================
// @ 0x0094FCC0  EA::SSL::SSLManager::Shutdown
// ===========================================================================
char __fastcall SSLManager_Shutdown(void* self)
{
    if (I8(self, 8) != 0) {
        I8(self, 8) = 0;
        SSLManager_RemoveSession(self);
        if (PTR(self, 0x14) != 0) {
            SSL_CTX_free(PTR(self, 0x14));
            PTR(self, 0x14) = 0;
        }
        THREAD_cleanup();
        void* d = PTR(self, 0x150);
        PTR(self, 0x14c) = 0;
        if (d != 0) {
            ((ICoreAllocator*)PTR(self, 0x10))->Free(d, 0);
            PTR(self, 0x150) = 0;
        }
    }
    return 1;
}

// ===========================================================================
// @ 0x0094FD20  SSLManager::RestoreClientSession(SSL*, const char*)
// ===========================================================================
char SSLManager::RestoreClientSession(void* ssl, unsigned char* name)
{
    void* self = this;
    ((Ext*)(B(self) + 0x18))->Lock(&g_lockArg);
    GetSession((const char*)name);
    CRYPTO_add_lock((int*)(B(ssl) + 0x9c), 1, 0xe, g_szFileName, 0x581);
    unsigned h = 0x811c9dc5;
    unsigned char c = *name;
    unsigned char* p = name;
    while (c != 0) {
        p++;
        h = h * 0x1000193 ^ c;
        c = *p;
    }
    void* out[4];
    out[1] = ssl;
    ((Ext*)(B(self) + 0x48))->faf0(&out[1], &h, (void*)((unsigned)name & 0xffffff00u));
    Mutex_Unlock(B(self) + 0x18);
    return 1;
}

// ===========================================================================
// @ 0x0094FDC0  THREAD_setup
// ===========================================================================
int __cdecl THREAD_setup()
{
    void* mgr = g_spSSLManager;
    ICoreAllocator* alloc = (ICoreAllocator*)PTR(mgr, 0x10);
    unsigned n = Fn01181150();
    ((Ext*)(B(mgr) + 0x154))->fixedvec_resize(n);
    for (unsigned i = 0; i < n; ++i) {
        void* m = alloc->AllocA(0x30, g_szUTFUp, 0, 8, 0);
        void* r;
        if (m != 0)
            r = ((Ext*)m)->ctor(0, 1);
        else
            r = 0;
        *(void**)(B(PTR(g_spSSLManager, 0x154)) + i * 4) = r;
    }
    CRYPTO_set_id_callback((void*)0x0094EB40);
    CRYPTO_set_locking_callback((void*)0x0094F0F0);
    Fn011812b0((void*)0x0094F120);
    CRYPTO_set_dynlock_lock_callback((void*)0x0094EB50);
    CRYPTO_set_dynlock_destroy_callback((void*)0x0094F850);
    return 1;
}

// ===========================================================================
// @ 0x0094FE70  EA::SSL::SSLManager::`scalar deleting destructor'
// ===========================================================================
void* SSLManager::DeletingDtor(char flags)
{
    void* self = this;
    PTR(self, 0) = (void*)0x0143FF28;
    SSLManager_Shutdown(self);
    void* p = PTR(self, 0x154);
    if (p != 0 && p != PTR(self, 0x164))
        operator_delete__(p);
    Ext* map = (Ext*)(B(self) + 0x48);
    void* node = PTR(self, 0x54);
    map->nuke(node);
    Mutex_dtor(B(self) + 0x18);
    if (flags & 1)
        operator_delete__(self);
    return self;
}

// ===========================================================================
// @ 0x0094FED0  EA::SSL::SSLManager::Init
// ===========================================================================
char __fastcall SSLManager_Init(void* self)
{
    if (I8(self, 8) != 0)
        return 1;
    if (PTR(self, 0x14c) == 0) {
        char* p = (char*)((ICoreAllocator*)PTR(self, 0x10))->AllocA(8, g_szUTFUp, 0, 4, 0);
        void* r;
        if (p == 0) {
            r = 0;
        } else {
            PTR(p, 0) = (void*)0x0143FF24;
            PTR(p, 4) = self;
            r = p;
        }
        PTR(self, 0x150) = r;
        PTR(self, 0x14c) = r;
    }
    PTR((void*)0x016F198C, 0) = (void*)0x0094F2A0;
    PTR((void*)0x016F1990, 0) = (void*)0x0094EE30;
    PTR((void*)0x016F1994, 0) = (void*)0x0094EE60;
    CRYPTO_set_mem_functions((void*)0x0094F160, (void*)0x0094F1C0, (void*)0x0094F1A0);
    if (THREAD_setup() == 0)
        return 1;
    if (Fn011831f0() == 0)
        return 1;
    unsigned char buf[16];
    *(__int64*)buf = _time64(0);
    *(int*)(buf + 8) = GetThreadId();
    *(void**)(buf + 12) = buf;
    RAND_seed(buf, 0x10);
    Fn011831e0();
    if (I32(self, 0xc) != 1)
        I32(self, 0xc) = 3;
    void* ctx = PTR(self, 0x14);
    if (ctx == 0) {
        void* t;
        int mode = I32(self, 0xc);
        if (mode == 1)
            t = Fn01182ab0();
        else if (mode == 2)
            t = Fn011831a0();
        else
            t = Fn011831d0();
        ctx = AddStat((unsigned)t);
        if (ctx == 0)
            goto done;
    }
    PTR(self, 0x14) = ctx;
    if (I32(self, 0xc) == 2 || I32(self, 0xc) == 3) {
        SSL_CTX_set_verify(ctx, 1, (void*)0x00E4A9C0);
        SSL_CTX_set_tmp_dh_callback(ctx, (void*)0x0094EB70);
    } else {
        SSL_CTX_set_verify(ctx, 3, (void*)0x00E4A9C0);
    }
    SSL_CTX_set_purpose(ctx, 4);
    SSL_CTX_ctrl(ctx, 0x20, 0x1100fff, 0);
    SSL_CTX_set_cipher_list(ctx, g_szCiphers);
    SSL_CTX_ctrl(ctx, 0x21, 4, 0);
done:
    I8(self, 8) = 1;
    return 1;
}

// ===========================================================================
// @ 0x00950060
// ===========================================================================
int __cdecl Fn00950060(int p)
{
    int z = 0;
    I32(p, 0xc) = 1;
    I32(p, 0x1c) = z;
    I32(p, 0x20) = z;
    I32(p, 0x14) = z;
    return z + 1;
}

// ===========================================================================
// @ 0x00950080  SSLSocketBIOShutdown
// ===========================================================================
int __cdecl SSLSocketBIOShutdown(void* p)
{
    int r = 0;
    if (p != 0) {
        if (I32(p, 0x10) != 0) {
            if (I32(p, 0xc) != 0) {
                Obj8* o = (Obj8*)(B(I32(p, 0x20)) + 8);
                o->b30(2);
            }
            I32(p, 0xc) = 0;
            I32(p, 0x14) = 0;
        }
        r = 1;
    }
    return r;
}

// ===========================================================================
// @ 0x009500C0  SSLSocketBIOControl
// ===========================================================================
unsigned __cdecl SSLSocketBIOControl(void* p, int cmd, int arg, int* parg)
{
    switch (cmd) {
    case 1:
        SSLSocketBIOShutdown(p);
        return 0;
    case 8:
        return (unsigned)I32(p, 0x10);
    case 9:
        I32(p, 0x10) = arg;
        return 1;
    case 0xb:
    case 0xc:
        return 1;
    case 0x68:
        I32(p, 0x1c) = *parg;
        I32(p, 0x10) = arg;
        I32(p, 0xc) = 1;
        return 1;
    case 0x69:
        break;
    default:
        return 0;
    }
    if (I32(p, 0xc) != 0) {
        if (parg != 0)
            *parg = I32(p, 0x1c);
        return (unsigned)I32(p, 0x1c);
    }
    return 0xffffffffu;
}

// ===========================================================================
// @ 0x00950200
// ===========================================================================
void* Sock::QueryInterface(unsigned iface)
{
    void* self = this;
    if (iface == 0x0164C507) {
        if ((int)self - 8 != 0)
            return B(self) + 0x80;
        return 0;
    }
    return ((Ext*)self)->e340(iface);
}

// ===========================================================================
// @ 0x00950280  StreamSSLSocket connection init
// ===========================================================================
char __fastcall Fn00950280(void* self)
{
    char r = Fn0094d3c0(self);
    if (r == 0)
        return 0;
    I32(self, 0x90) = 0;
    I32(self, 0xcc) = -1;
    if (I8(self, 0x84) != 0) {
        I8(self, 0x85) = 1;
        void* ctx = Fn00ff0420(PTR(self, 0x94));
        if (ctx == 0)
            return 1;
        void* ssl = PTR(self, 0x88);
        if (ssl == 0) {
            ssl = Fn0117c560(ctx);
            PTR(self, 0x88) = ssl;
            if (ssl == 0)
                return 1;
        }
        void* bio = PTR(self, 0x8c);
        if (bio == 0) {
            bio = BIO_new((void*)0x0154EC2C);
            PTR(self, 0x8c) = bio;
            if (bio == 0)
                return 1;
        }
        SSL_set_bio(ssl, bio, bio);
        PTR(bio, 0x20) = B(self) - 8;
        Fn0117c940(ssl, 0x21, 4, 0);
    }
    return 1;
}

// ===========================================================================
// @ 0x00950330
// ===========================================================================
char Sock::SetConnectState(int v)
{
    void* self = this;
    if (I32(self, 0xcc) == -1) {
        I32(self, 0xcc) = v;
        return 1;
    }
    return 0;
}

// ===========================================================================
// @ 0x00950350  StreamSSLSocket teardown
// ===========================================================================
void __fastcall Fn00950350(void* self)
{
    if (I32(self, 0x90) == 2)
        Fn0117c8f0(PTR(self, 0x88));
    else
        Fn0117c440(PTR(self, 0x88));
    if (I32(self, 0x8c) != 0)
        I32(self, 0x8c) = 0;
    if (PTR(self, 0x88) != 0) {
        SSL_free(PTR(self, 0x88));
        PTR(self, 0x88) = 0;
    }
    I32(self, 0x7c) = 0;
    Fn0094d4b0(self);
}

// ===========================================================================
// @ 0x009503C0  StreamSSLSocket::Accept
// ===========================================================================
unsigned Sock::Accept(int a, int b, int c)
{
    void* self = this;
    unsigned r = (unsigned)((Ext*)self)->e650(a, b, c);
    if ((char)r != 0) {
        int acc = SSL_accept(PTR(self, 0x10));
        if (acc > 0) {
            ISub* s = (ISub*)(B(self) + 8);
            void* nm = s->a24();
            if (NetSSLVerifyConnection(PTR(self, 0x10), (const char*)nm) == 0) {
                return 1;
            }
        }
        Fn0117c8f0(PTR(self, 0x10));
        I32(self, 4) = 4;
        ((Ext*)(B(self) - 0x78))->d470(2);
        I32(self, 4) = 0;
        r = (unsigned)Fn0094d4b0(B(self) - 0x78);
    }
    return r & 0xffffff00u;
}

// ===========================================================================
// @ 0x00950450  StreamSSLSocket read
// ===========================================================================
int Sock::Read(int buf, int len, unsigned char flag)
{
    void* self = this;
    if (flag & 2)
        return -1;
    if ((flag & 1) == 0 && I32(self, 0x54) != 2 && I32(self, 0x54) != 0) {
        int r = 0;
        if (len > 0) {
            r = Fn0117b410(PTR(self, 0x10), (void*)buf, len);
            if (r <= 0) {
                Fn0117ccd0(PTR(self, 0x10), r);
                unsigned u = (unsigned)EC_GROUP_get_curve_name(PTR(self, 0x10));
                I32(self, 0x18) = ((u & 2) != 0) + 1;
            }
        }
        return r;
    }
    return -1;
}

// ===========================================================================
// @ 0x009504D0  StreamSSLSocket write
// ===========================================================================
int Sock::Write(int buf, int len, unsigned char flag)
{
    void* self = this;
    if ((flag & 1) == 0 && I32(self, 0x54) != 2 && I32(self, 0x54) != 1) {
        int r = 0;
        if (len > 0) {
            r = Fn0117b4a0(PTR(self, 0x10), (void*)buf, len);
            if (r <= 0) {
                Fn0117ccd0(PTR(self, 0x10), len);
                unsigned u = (unsigned)EC_GROUP_get_curve_name(PTR(self, 0x10));
                I32(self, 0x18) = ((u & 2) != 0) + 1;
            }
        }
        return r;
    }
    return -1;
}

// ===========================================================================
// @ 0x00950540
// ===========================================================================
int __cdecl Fn00950540(void* bio, int b, int c)
{
    int r = 0;
    if (b != 0) {
        void* t = (void*)(B(I32(bio, 0x20)) + 0x80);
        r = ((Ext*)t)->e3a0(b, c, 0);
        BIO_clear_flags(bio, 0xf);
    }
    return r;
}

// ===========================================================================
// @ 0x00950580
// ===========================================================================
int __cdecl Fn00950580(void* bio, int b, int c)
{
    int r = 0;
    if (b != 0) {
        void* t = (void*)(B(I32(bio, 0x20)) + 0x80);
        r = ((Ext*)t)->e3f0(b, c, 0);
        BIO_clear_flags(bio, 0xf);
    }
    return r;
}

// ===========================================================================
// @ 0x009505C0
// ===========================================================================
int __cdecl Fn009505c0(void* bio, char* str)
{
    char* p = str;
    char c;
    do { c = *p; p++; } while (c != 0);
    int len = (int)p - (int)(str + 1);
    int r = 0;
    if (str != 0) {
        void* t = (void*)(B(I32(bio, 0x20)) + 0x80);
        r = ((Ext*)t)->e3f0((int)str, len, 0);
        BIO_clear_flags(bio, 0xf);
    }
    return r;
}

// ===========================================================================
// @ 0x00950610  StreamSSLSocket refcount release
// ===========================================================================
int __fastcall Fn00950610(int* p)
{
    int old = (int)_InterlockedExchangeAdd((volatile long*)(p - 1), 0);
    if (old > 1)
        return RefCount_Release_M8(p);
    void* q = (char*)p - 8;
    ((void(__thiscall*)(void*, int))*(void**)(I32(q, 8) + 0x30))(B(q) + 8, 2);
    ((void(__thiscall*)(void*, int))*(void**)I32(q, 0))(q, 1);
    return 0;
}

// ===========================================================================
// @ 0x00950650  fixed_string::sprintf
// ===========================================================================
int* Sock::Sprintf(const char* fmt, void* ap)
{
    int* self = (int*)this;
    int used = self[1] - self[0];
    int avail;
    if ((void*)self[0] == (void*)0x01667BAC)
        avail = 0;
    else
        avail = self[2] - self[1];
    int n = Vsnprintf8((char*)self[1], (unsigned)avail, fmt, ap);
    if (n < self[2] - self[1]) {
        if (n < 0) {
            int a = (self[1] - self[0]) * 2;
            int seven = 7;
            int cap = (a > 7) ? a : seven;
            do {
                if ((unsigned)cap >= 0xf4240)
                    break;
                ((Ext*)self)->resize((unsigned)cap);
                n = Vsnprintf8((char*)(self[0] + used), (unsigned)(cap - used) + 1, fmt, ap);
                cap *= 2;
            } while (n < 0);
        }
    } else {
        ((Ext*)self)->resize((unsigned)(n + used));
        n = Vsnprintf8((char*)(self[0] + used), (unsigned)(n + 1), fmt, ap);
    }
    if (n >= 0)
        self[1] = self[0] + n + used;
    return self;
}

// ===========================================================================
// @ 0x00950740  StreamSSLSocket destructor
// ===========================================================================
void __fastcall Fn00950740(void* self)
{
    PTR(self, 0) = (void*)0x014400F0;
    PTR(self, 8) = (void*)0x01440018;
    PTR(self, 0x80) = (void*)0x0143FFC8;
    PTR(self, 0x88) = (void*)0x0143FF90;
    char* v = (char*)PTR(self, 0xa0);
    if ((int)(B(PTR(self, 0xa8)) - v) > 1 && v != 0 && v != (char*)PTR(self, 0xb0))
        operator_delete__(v);
    PTR(self, 0x80) = (void*)0x013EB938;
    Fn0094e770(self);
}

// ===========================================================================
// @ 0x00950870  UTFSSL::StreamSSLSocket::StreamSSLSocket
// ===========================================================================
void* __fastcall StreamSSLSocket_ctor(void* self)
{
    Fn0094e9a0(self);
    PTR(self, 0x88) = (void*)0x0143FF5C;
    char* buf = B(self) + 0xb4;
    PTR(self, 0) = (void*)0x014400F0;
    PTR(self, 8) = (void*)0x01440018;
    PTR(self, 0x80) = (void*)0x0143FFC8;
    PTR(self, 0x88) = (void*)0x0143FF90;
    I8(self, 0x8c) = 1;
    I8(self, 0x8d) = 0;
    I32(self, 0x90) = 0;
    I32(self, 0x94) = 0;
    I32(self, 0x98) = 0;
    I32(self, 0x9c) = 0;
    PTR(self, 0xb0) = buf;
    PTR(self, 0xa4) = buf;
    PTR(self, 0xa0) = buf;
    PTR(self, 0xa8) = buf + 0x20;
    *buf = 0;
    I32(self, 0xd4) = -1;
    return self;
}

// ===========================================================================
// @ 0x00950920  EA::SSL::StreamSSLSocket::GetSessionName
// ===========================================================================
char Sock::GetSessionName(void* out)
{
    void* self = this;
    ISub* s = (ISub*)(B(self) + 0x88);
    char* name = (char*)s->a24();
    if (name != 0 && *name != 0) {
        unsigned short port = U16(self, 0x2e);
        port = (unsigned short)((port >> 8) | (port << 8));
        FStr_sprintf((char*)out, "%s:%u", name, (unsigned)port);
    }
    return 0;
}
// ===========================================================================
// @ 0x00950970  EA::SSL::StreamSSLSocket::Connect
// ===========================================================================
char __fastcall StreamSSLSocket_Connect(void* self)
{
    void* ctx = PTR(self, 0x90);
    if (ctx == 0)
        return 0;
    if (I32(self, 0x9c) == 0)
        return 0;
    void* sess = SSL_get1_session(ctx);
    if (sess != 0) {
        char buf[0x20];
        buf[0] = 0;
        ((Sock*)self)->GetSessionName(buf);
        ((SSLManager*)PTR(self, 0x9c))->RestoreClientSession(sess, (unsigned char*)buf);
        SSL_SESSION_free(sess);
        int len = (int)(B(buf + 0x20) - buf);
        if (len > 1 && buf != 0 && buf != buf + 0x20)
            operator_delete__(buf);
    }
    return 0;
}

// ===========================================================================
// @ 0x00950A20  EA::SSL::StreamSSLSocket::SaveClientSession
// ===========================================================================
char __fastcall StreamSSLSocket_SaveClientSession(void* self)
{
    if (PTR(self, 0x90) == 0)
        return 0;
    if (I32(self, 0x9c) == 0)
        return 0;
    char buf[0x20];
    buf[0] = 0;
    ((Sock*)self)->GetSessionName(buf);
    void* sess = ((SSLManager*)PTR(self, 0x9c))->FindAndRelease(buf, 1);
    if (sess != 0) {
        Fn01181810(PTR(self, 0x90), sess);
        SSL_SESSION_free(sess);
    }
    int len = (int)(B(buf + 0x20) - buf);
    if (len > 1 && buf != 0 && buf != buf + 0x20)
        operator_delete__(buf);
    return 0;
}

// ===========================================================================
// @ 0x00950AD0  fixed_string assignment
// ===========================================================================
void Sock::SetStr(char* str)
{
    FixedStr* fs = (FixedStr*)(B(this) + 0x18);
    char* begin = fs->begin;
    if (begin != str) {
        if (begin != fs->end) {
            *begin = 0;
            fs->end = fs->begin;
        }
        char* p = str;
        char c;
        do { c = *p; p++; } while (c != 0);
        int len = (int)p - (int)(str + 1);
        fs->append(str, str + len);
    }
}

// ===========================================================================
// @ 0x00950B10  StreamSSLSocket::DoPostConnectionCheck
// ===========================================================================
char Sock::DoPostConnectionCheck(char* out, int a)
{
    void* self = this;
    char r = 0;
    if (!((Ext*)self)->e4b0((int)out, a))
        return 0;
    char* base = B(self) - 0x80;
    StreamSSLSocket_SaveClientSession(base);
    if (SSL_connect(PTR(self, 0x10)) > 0) {
        ISub* s = (ISub*)(B(self) + 8);
        void* nm = s->a24();
        if (NetSSLVerifyConnection(PTR(self, 0x10), (const char*)nm) == 0) {
            StreamSSLSocket_Connect(base);
            return 1;
        }
    }
    Fn0117c8f0(PTR(self, 0x10));
    char* b2 = B(self) - 0x78;
    I32(b2, 4) = 4;
    ((Ext*)b2)->d470(2);
    I32(b2, 4) = 0;
    Fn0094d4b0(b2);
    *out = 0;
    return r;
}
