// Slice s0094ea80 -- EA::SSL (UTFNetwork/UTFSSL): refcount adjustor thunks,
// SSLManager, OpenSSL BIO/file bridges and the SSL file_ctrl BIO method.
// Module flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"
#include <intrin.h>

extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedIncrement, _InterlockedExchangeAdd, _InterlockedExchange)

extern "C" int   __cdecl strcmp(const char*, const char*);
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, unsigned int);
#pragma intrinsic(strcmp)

void* __cdecl operator new(unsigned int, const char*, int, int, const char*, int);
void  __cdecl operator_delete__(void*) throw();

// ---- eastl / lib_openssl externals (addresses drive equivalence resolution) ----
void* __cdecl RBTreeIncrement(void* node);                                   // 0x00921580
void  __cdecl RBTreeInsert(void* node, void* parent, void* header, int left); // 0x009216A0

// ---- OpenSSL / lib imports (addresses in comments drive equivalence resolution) ----
extern "C" {
void* __cdecl BIO_new(void* method);                                                   // 0x01177470
long  __cdecl BIO_ctrl(void* bio, int cmd, long larg, void* parg);                     // 0x01177260
void  __cdecl BIO_free(void* bio);                                                     // 0x01176f10
void* __cdecl Fn117b240(const char* file, void* x);                                    // 0x0117b240
void* __cdecl Fn117b210(void* bio, int a, int b, int c);                               // 0x0117b210
void* __cdecl SSL_get_peer_certificate(void* ssl);                                     // 0x0117b3c0
int   __cdecl Fn11801b0(void* x);                                                      // 0x011801b0
void* __cdecl Fn11801f0(void* x509, int i);                                            // 0x011801f0
void* __cdecl Fn1180160(void* ext);                                                    // 0x01180160
int   __cdecl OBJ_obj2nid(void* obj);                                                  // 0x0117fa60
const char* __cdecl Fn117f7f0(int nid);                                                // 0x0117f7f0
void* __cdecl X509V3_EXT_get(void* ext);                                               // 0x0117f5f0
void* __cdecl ASN1_item_d2i(void* out, void* in, int len, void* it);                   // 0x0117f530
int   __cdecl sk_num(void* sk);                                                        // 0x0117dde0
void* __cdecl sk_value(void* sk, int i);                                               // 0x0117ddf0
void* __cdecl X509_get_subject_name(void* x);                                          // 0x0117d5a0
int   __cdecl X509_NAME_get_text_by_NID(void* name, int nid, char* buf, int len);     // 0x0117d4b0
void  __cdecl X509_free(void* x);                                                      // 0x0117cf90
long  __cdecl SSL_get_verify_result(void* ssl);                                        // 0x0117c410
void  __cdecl ERR_put_error(int lib, int func, int reason, const char* file, int line); // 0x01180d50
void  __cdecl ERR_add_error_data(int num, ...);                                        // 0x01180a70
int   __cdecl SSL_CTX_load_verify_locations(void* ctx, const char* file, const char* path); // 0x0117c3f0
void  __cdecl CRYPTO_add_lock(int* p, int n, int type, const char* file, int line);    // 0x011815d0
void  __cdecl SSL_SESSION_free(void* s);                                               // 0x01181750
void* __cdecl Fn01177470(void* methodTable);                                           // 0x01177470
}

// ---- data globals ----
extern "C" void* g_bioMethodTable;                 // 0x0154ec00
extern "C" void* g_dh512;                          // 0x0166aab0
extern "C" void* g_dh1024;                         // 0x0166aaac
extern "C" int   g_lockArg;                        // 0x0143fe18
extern "C" char  g_szR[];                          // 0x0141c53c "r"
extern "C" char  g_szA[];                          // 0x01414a98 "a"
extern "C" char  g_szAPlus[];                      // 0x0143ff20 "a+"
extern "C" char  g_szRPlus[];                      // 0x0143ff1c "r+"
extern "C" char  g_szW[];                          // 0x013ef03c "w"
extern "C" char  g_szWPlus[];                      // 0x0143ff18 "w+"
extern "C" char  g_szComma[];                      // 0x0143ff10 "','"
extern "C" char  g_szClose[];                      // 0x0143ff14 "')"
extern "C" char  g_szOpenFmt[];                    // 0x0143fef8 "pFileSystem->OpenFile('"
extern "C" char  g_szFileName[];                   // 0x0143fe48 "..\\..\\UTFNetwork\\UTFSSL\\source\\SSLManager.cpp"
extern "C" char  g_szDNS[];                        // 0x0143fe34 "DNS"
extern "C" char  g_szSAN[];                        // 0x0143fe38 "subjectAltName"
extern "C" char  g_szUTFSSL[];                     // 0x0143fec8 "UTFSSL/StreamSSLSocket"
extern "C" char  g_szUTFUp[];                      // 0x0143fee0 "UTF/SSL"
extern "C" char  g_szUTFOSSL[];                    // 0x0143fee8 "UTF_SSL/OpenSSL"
extern "C" char  g_szEmpty[];                      // 0x013ec47c

// vtables (their addresses are stored into objects)
extern "C" char vtbl_94_0[];                       // 0x0143fbd8
extern "C" char vtbl_94_8a[];                      // 0x0143fb00
extern "C" char vtbl_94_80[];                      // 0x013eb938
extern "C" char vtbl_94_0b[];                      // 0x013fb19c
extern "C" char vtbl_filesys[];                    // 0x0143fe78

// ===========================================================================
// Refcount adjustor thunks (inline bodies; -4 / -8 this adjustment)
// ===========================================================================
struct RefObj94 { virtual void Destroy(int); int mnRefCount; };

// @ 0x0094EA80
int __fastcall RefCount_AddRef_M4(int* p)
{
    return _InterlockedIncrement((volatile long*)(p - 1));
}

// @ 0x0094EA90
int __fastcall RefCount_Release_M8(int* self)
{
    RefObj94* p = (RefObj94*)(self - 2);
    int n = _InterlockedExchangeAdd((volatile long*)&p->mnRefCount, -1);
    n--;
    if (n == 0) {
        _InterlockedExchange((volatile long*)&p->mnRefCount, 1);
        if (p)
            p->Destroy(1);
    }
    return n;
}

// ===========================================================================
// Destructor of the resource object (three vtables at +0, +8, +0x80)
// ===========================================================================
struct Sub94d4b0 { void Fn0094d4b0(); };

struct ResObj94 {
    void* Destroy(int flags);
};
// @ 0x0094EAE0
void* ResObj94::Destroy(int flags)
{
    void** p = (void**)this;
    p[0x20] = vtbl_94_80;
    p[0]     = vtbl_94_0;
    p[2]     = vtbl_94_8a;
    if ((int)p[3] != -1 && *((char*)this + 0x7e) == 0)
        ((Sub94d4b0*)(p + 2))->Fn0094d4b0();
    p[2] = vtbl_94_80;
    p[0] = vtbl_94_0b;
    if (flags & 1)
        operator_delete__(this);
    return this;
}

// ===========================================================================
// Lock / unlock dispatch for a mutex
// ===========================================================================
struct Mutex94 {
    int Lock(const void* p);
    int Unlock();
};

// @ 0x0094EB50
int __cdecl Fn0094eb50(int flag, Mutex94* m)
{
    if (flag & 1)
        return m->Lock(&g_lockArg);
    return m->Unlock();
}

// ===========================================================================
// tmp_dh_callback: lazily load DH parameters from PEM files
// ===========================================================================
// @ 0x0094EB70
void* __cdecl tmp_dh_callback(int a, int b, int bits)
{
    if (g_dh512 == 0) {
        void* bio = Fn117b240("dh512.pem", g_szR);
        if (bio != 0) {
            g_dh512 = Fn117b210(bio, 0, 0, 0);
            BIO_free(bio);
        }
    }
    if (g_dh1024 == 0) {
        void* bio = Fn117b240("dh1024.pem", g_szR);
        if (bio != 0) {
            g_dh1024 = Fn117b210(bio, 0, 0, 0);
            BIO_free(bio);
        }
    }
    void* r = g_dh1024;
    if (bits != 0x200)
        return r;
    return g_dh512;
}

// ===========================================================================
// NetSSLVerifyConnection
// ===========================================================================
// @ 0x0094EC00
int __cdecl NetSSLVerifyConnection(void* ssl, const char* name)
{
    void* cert = SSL_get_peer_certificate(ssl);
    if (cert != 0) {
        if (name != 0) {
            int nExt = Fn11801b0(cert);
            if (nExt > 0) {
                int i = 0;
                do {
                    void* ext = Fn11801f0(cert, i);
                    const char* sn = Fn117f7f0(OBJ_obj2nid(Fn1180160(ext)));
                    if (strcmp(sn, g_szSAN) == 0) {
                        void* method = X509V3_EXT_get(ext);
                        if (method == 0)
                            break;
                        int* pExt = *(int**)((char*)ext + 8);
                        int local = pExt[2];
                        void* val;
                        if (*(int*)((char*)method + 8) == 0)
                            val = ((void* (__cdecl*)(int, void*, void*))
                                   *(void**)((char*)method + 0x14))(0, &local, (void*)pExt[0]);
                        else
                            val = ASN1_item_d2i(0, &local, pExt[0], *(void**)((char*)method + 8));
                        val = ((void* (__cdecl*)(void*, void*, int))
                               *(void**)((char*)method + 0x24))(method, val, 0);
                        int j = 0;
                        int cnt = sk_num(val);
                        if (cnt > 0) {
                            do {
                                int* ent = (int*)sk_value(val, j);
                                if (strcmp(*(const char**)((char*)ent + 4), g_szDNS) == 0) {
                                    if (strcmp(*(const char**)((char*)ent + 8), name) == 0)
                                        goto Lverify;
                                }
                                j++;
                            } while (j < sk_num(val));
                        }
                    }
                    i++;
                } while (i < nExt);
            }
            void* subj = X509_get_subject_name(cert);
            if (subj == 0)
                goto Lverify;
            char buf[0x100];
            if (X509_NAME_get_text_by_NID(subj, 0xd, buf, 0x100) < 1)
                goto Lverify;
            buf[0xff] = 0;
            if (_stricmp(buf, name) == 0)
                goto Lverify;
        }
        X509_free(cert);
        return 0x32;
    Lverify:
        X509_free(cert);
        return (int)SSL_get_verify_result(ssl);
    }
    return 0x32;
}

// ===========================================================================
// BIO_new wrapper over the SSL BIO method table
// ===========================================================================
// @ 0x0094EE30
void* __cdecl Fn0094ee30(void* a, void* b)
{
    void* bio = BIO_new(&g_bioMethodTable);
    if (bio != 0)
        BIO_ctrl(bio, 0x6a, (long)b, a);
    return bio;
}

// ===========================================================================
// BIO <-> stream bridge helpers
// ===========================================================================
struct SLInner {
    virtual void i00();
    virtual void i04();
    virtual void i08();
    virtual void i0c();
    virtual void i10();
    virtual void i14();
    virtual void i18();
    virtual void i1c();
    virtual void i20();
    virtual int  i24(int a);
    virtual char i28(int a, int b);
    virtual int  i2c();
    virtual int  i30(int a, int b);
    virtual int  i34();
    virtual char i38(const void* a, int b);
};

struct BIO94 {
    char pad00[0xc];      // +0x00
    int  f0c;             // +0x0c
    int  f10;             // +0x10
    int  f14;             // +0x14
    char pad18[8];        // +0x18
    SLInner* obj;         // +0x20
};

// @ 0x0094EE70
int __cdecl Fn0094ee70(BIO94* p)
{
    if (p == 0)
        return 0;
    if (p->f10 != 0 && p->f0c != 0) {
        SLInner* o = p->obj;
        if (o != 0) {
            o->i18();
            o->i08();
            p->obj = 0;
            p->f14 = 0;
            p->f0c = 0;
        }
    }
    return 1;
}

// @ 0x0094EEC0
int __cdecl Fn0094eec0(BIO94* p, int a, int b)
{
    int r = 0;
    if (p->f0c != 0 && a != 0) {
        r = p->obj->i30(a, b);
        if (r == -1) {
            ERR_put_error(0x20, 0x82, 2, g_szFileName, 0x307);
            r = -1;
        }
    }
    return r;
}

// @ 0x0094EF10
unsigned __cdecl Fn0094ef10(BIO94* p, char* buf, unsigned len)
{
    unsigned r = 0;
    if (p->f0c != 0 && buf != 0) {
        if (p->obj->i38(buf, len))
            r = len;
    }
    return r;
}

// ===========================================================================
// static line reader (register-arg helper, called from Fn0094efb0 / file_ctrl)
// ===========================================================================
// @ 0x0094EF50
char* __cdecl ReadLine94(char* buf, int maxLen, SLInner* s)
{
    char* out = buf;
    int left = maxLen - 1;
    char c = (char)-1;
    int r = -1;
    if (left > 0) {
        for (;;) {
            r = s->i30((int)&c, 1);
            if (r != 1)
                break;
            if (c < 0)
                break;
            *out++ = c;
            if (c == '\n')
                break;
            if (--left <= 0)
                break;
        }
    }
    *out = 0;
    if (r < 0 && out == buf)
        return 0;
    return buf;
}

// ===========================================================================
// @ 0x0094EFB0
int __cdecl Fn0094efb0(BIO94* p, char* buf, int maxLen)
{
    SLInner* s = (SLInner*)*(void**)((char*)p + 0x20);
    char* out = buf;
    int left = maxLen - 1;
    char c = (char)-1;
    if (left > 0) {
        while (s->i30((int)&c, 1) == 1) {
            if (c < 0)
                break;
            *out++ = c;
            if (c == '\n')
                break;
            if (--left <= 0)
                break;
        }
    }
    *out = 0;
    char* q = buf + 1;
    do { c = *buf; buf++; } while (c != 0);
    return (int)buf - (int)q;
}

// @ 0x0094EFE0
int __cdecl Fn0094efe0(BIO94* p, char* str)
{
    char* q = str;
    char c;
    do { c = *q; q++; } while (c != 0);
    int len = (int)q - (int)(str + 1);
    int r = 0;
    if (p->f0c != 0 && str != 0) {
        if (p->obj->i38(str, len))
            r = len;
    }
    return r;
}

// ===========================================================================
// EA::SSL::SSLManager::CreateStreamSSLSocket
// ===========================================================================
struct ICoreAllocator {
    virtual void v00();
    virtual void* AllocA(unsigned size, const char* name, int flags, unsigned align, int off);
    virtual void* AllocB(unsigned size, const char* name, int flags);
    virtual void  Free(void* p, int flags);
};

struct SSLManager;

struct SSS94 {
    virtual void s00(); virtual void s04(); virtual void s08();
    virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30(void* manager);
};

struct StreamSSLSocketCtor {
    void* Construct();
};

struct SSLManager {
    char vtbl[4];                     // +0x00
    int  mUnk4;                       // +0x04
    bool mbInit;                      // +0x08
    char pad9[3];
    int  mMode;                       // +0x0c
    ICoreAllocator* mpCoreAllocator;  // +0x10
    void* mpDriverContext;            // +0x14
    char mMutex[0x30];                // +0x18
    char mMap[0x104];                 // +0x48
    void* mpFileSystem;               // +0x14c
    void* mpFileSystemDefault;        // +0x150
    char mMutexPtrArray[0x34];        // +0x154

    void* CreateStreamSSLSocket();              // 0x0094F030
    void  SetFileSystem(int v, bool set);       // 0x0094F080
    unsigned GetSession(const char* name);      // 0x0094F910
    void  RemoveSession();                      // 0x0094F990
};

extern SSLManager* g_spSSLManager;    // 0x0166aaa8

// @ 0x0094F030
void* __thiscall SSLManager::CreateStreamSSLSocket()
{
    StreamSSLSocketCtor* p = (StreamSSLSocketCtor*)
        operator new(0xd8, g_szUTFSSL, 0, 0, 0, 0);
    SSS94* q;
    if (p != 0) {
        p = (StreamSSLSocketCtor*)p->Construct();
        if (p != 0)
            q = (SSS94*)((char*)p + 0x88);
        else
            q = 0;
    } else {
        q = 0;
    }
    q->s0c();
    q->s30(this);
    return q;
}

// @ 0x0094F080
void __thiscall SSLManager::SetFileSystem(int v, bool set)
{
    if (set) {
        *(int*)((char*)this + 0x14c) = v;
        return;
    }
    if (*(int*)((char*)this + 0x14c) == v)
        *(int*)((char*)this + 0x14c) = 0;
}

// @ 0x0094F0B0
struct SSLContext {
    char pad[0x14];
    bool LoadVerifyLocations(const char* file);   // 0x0094F0B0
};
bool SSLContext::LoadVerifyLocations(const char* file)
{
    return SSL_CTX_load_verify_locations(*(void**)((char*)this + 0x14), file, 0) == 1;
}

// @ 0x0094F0E0
void* __cdecl SetSSLManagerGlobal(void* m)
{
    void* old = g_spSSLManager;
    g_spSSLManager = (SSLManager*)m;
    return old;
}

// ===========================================================================
// Mutex factory / OpenSSL allocator shims
// ===========================================================================
struct MutexNew94 {
    void ctor(int a, int b);          // 0x009222A0  EA::Thread::Mutex::Mutex
    void dtor();                      // 0x00922130  EA::Thread::Mutex::~Mutex
};

// @ 0x0094F120
MutexNew94* __cdecl Fn0094f120()
{
    MutexNew94* m = (MutexNew94*)
        g_spSSLManager->mpCoreAllocator->AllocA(0x30, g_szUTFUp, 0, 8, 0);
    if (m != 0) {
        m->ctor(0, 1);
        return m;
    }
    return 0;
}

// @ 0x0094F160
void* __cdecl EA_SSL_SSL_Malloc(int size)
{
    int* p = (int*)g_spSSLManager->mpCoreAllocator->AllocB((unsigned)size + 8, g_szUTFOSSL, 0);
    if (p != 0) {
        *p = size + 8;
        p[1] = 0;
        p += 2;
    }
    return p;
}

// @ 0x0094F1A0
void __cdecl EA_SSL_SSL_Free(void* p)
{
    g_spSSLManager->mpCoreAllocator->Free((char*)p - 8, 0);
}

void* __cdecl memcpy_impl(void* dst, const void* src, unsigned n);   // 0x011E0744

// @ 0x0094F1C0
void* __cdecl EA_SSL_SSL_Realloc(void* oldp, unsigned size)
{
    if (size != 0) {
        int* dst = (int*)g_spSSLManager->mpCoreAllocator->AllocB(size + 8, g_szUTFOSSL, 0);
        if (dst != 0) {
            *dst = size + 8;
            dst[1] = 0;
            dst += 2;
        }
        if (oldp != 0) {
            unsigned asz = (unsigned)(*(int*)((char*)oldp - 8) - 8);
            void* src = oldp;
            void* base = (char*)oldp - 8;
            if (asz >= size)
                asz = size;
            memcpy_impl((void*)dst, src, asz);
            g_spSSLManager->mpCoreAllocator->Free(base, 0);
        }
        return dst;
    }
    if (oldp != 0)
        g_spSSLManager->mpCoreAllocator->Free((char*)oldp - 8, 0);
    return 0;
}

// ===========================================================================
// Stream refcount release
// ===========================================================================
struct StreamRef94 {
    virtual void Destroy(int);       // +0x00
    char pad04[0x20c];
    int  mnRefCount;                 // +0x210
    char pad214[0x18];
    SSLManager* mpManager;           // +0x22c
};

// @ 0x0094F260
int __fastcall Fn0094f260(StreamRef94* p)
{
    if (p->mnRefCount > 1)
        return p->mnRefCount = p->mnRefCount - 1;
    ICoreAllocator* a = p->mpManager->mpCoreAllocator;
    p->Destroy(0);
    a->Free(p, 0);
    return 0;
}

// ===========================================================================
// BIO_new_file_override
// ===========================================================================
struct FileSystem94 {
    virtual void* OpenFile(const char* name, int m1, int m2);
};

// @ 0x0094F2A0
void* __cdecl BIO_new_file_override(const char* name, const char* mode)
{
    FileSystem94* fs = (FileSystem94*)g_spSSLManager->mpFileSystem;
    int m1 = 0, m2 = 0;
    if (strcmp(mode, g_szAPlus) == 0)       { m1 = 3; m2 = 4; }
    else if (strcmp(mode, g_szA) == 0)      { m1 = 2; m2 = 4; }
    else if (strcmp(mode, g_szRPlus) == 0)  { m1 = 3; m2 = 3; }
    else if (strcmp(mode, g_szW) == 0)      { m1 = 2; m2 = 2; }
    else if (strcmp(mode, g_szWPlus) == 0)  { m1 = 3; m2 = 2; }
    else if (strcmp(mode, g_szR) == 0)      { m1 = 1; m2 = 3; }
    else ERR_put_error(0x20, 0x6d, 0x65, g_szFileName, 0x29e);

    SLInner* st = (SLInner*)fs->OpenFile(name, m1, m2);
    if (st == 0) {
        ERR_add_error_data(5, g_szOpenFmt, name, g_szComma, mode, g_szClose);
        return 0;
    }
    st->i04();
    void* bio = BIO_new(&g_bioMethodTable);
    if (bio != 0) {
        BIO_ctrl(bio, 0x6a, 1, st);
        return bio;
    }
    st->i18();
    st->i08();
    return 0;
}

// ===========================================================================
// file_ctrl: the SSL file BIO's control method
// ===========================================================================
// @ 0x0094F4D0
unsigned __cdecl file_ctrl(BIO94* bio, int cmd, unsigned arg, void* parg)
{
    SLInner* obj = bio->obj;
    switch (cmd) {
    case 1:
    case 0x80:
        return (obj->i28((int)arg, 0) != 0) ? 0u : 0xffffffffu;
    case 2:
        return obj->i2c() != 0;
    case 3:
    case 0x85:
        return (unsigned)obj->i24(0);
    case 8:
        return (unsigned)bio->f10;
    case 9:
        bio->f10 = (int)arg;
        return 1;
    case 0xb:
        obj->i34();
        return 1;
    case 0x6a:
        Fn0094ee70(bio);
        bio->f10 = (int)(arg & 1);
        bio->f0c = 1;
        bio->obj = (SLInner*)parg;
        return 1;
    case 0x6b:
        if (parg != 0)
            *(SLInner**)parg = obj;
        return 1;
    case 0xc:
        return 1;
    case 0x6c: {
        Fn0094ee70(bio);
        bio->f10 = (int)(arg & 1);
        int m1, m2;
        if ((arg & 8) == 0) {
            if ((arg & 2) == 0) {
                if ((arg & 4) == 0)
                    goto mode2;
                m1 = 2; m2 = 2;
            } else if ((arg & 4) == 0) {
mode2:
                if ((arg & 2) == 0) {
                    ERR_put_error(0x20, 0x74, 0x65, g_szFileName, 0x36d);
                    return 0;
                }
                m1 = 1; m2 = 3;
            } else {
                m1 = 3; m2 = 3;
            }
        } else {
            m2 = 4;
            m1 = ((arg & 2) == 0) ? 2 : 3;
        }
        FileSystem94* fs = (FileSystem94*)g_spSSLManager->mpFileSystem;
        void* st = fs->OpenFile((const char*)parg, m1, m2);
        if (st != 0) {
            bio->obj = (SLInner*)st;
            bio->f0c = 1;
            return 1;
        }
        ERR_add_error_data(5, g_szOpenFmt, (void*)parg, g_szComma, g_szEmpty, g_szClose);
        return 0;
    }
    default:
        return 0;
    }
}

// ===========================================================================
// EA::SSL::FileSystemDefault::OpenFile
// ===========================================================================
struct IFileStream94 {
    virtual void v00(int); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(int a);
    virtual void v44();
    virtual void v48();
    virtual bool v4c(int a, int b, int c, int d);
};

struct FileStreamCtor94 {
    void ctor(int);   // 0x00931DA0
};

struct FileSystemDefault {
    void* vtbl;                  // +0x0
    SSLManager* mpSSLManager;    // +0x4
    IFileStream94* OpenFile(const char* name, int m1, int m2);
};

// @ 0x0094F720
IFileStream94* __thiscall FileSystemDefault::OpenFile(const char* name, int m1, int m2)
{
    ICoreAllocator* alloc = mpSSLManager->mpCoreAllocator;
    FileStreamCtor94* p = (FileStreamCtor94*)
        alloc->AllocA(0x230, g_szUTFUp, 0, 4, 0);
    if (p == 0)
        return 0;
    p->ctor(0);
    IFileStream94* io = (IFileStream94*)p;
    ((void**)io)[0] = vtbl_filesys;
    *(SSLManager**)((char*)io + 0x22c) = mpSSLManager;
    io->v40((int)name);
    if (io->v4c(m1, m2, 1, 0))
        return io;
    io->v00(0);
    alloc->Free(io, 0);
    return 0;
}

// ===========================================================================
// @ 0x0094F850
void __cdecl Fn0094f850(MutexNew94* m)
{
    if (m != 0) {
        m->dtor();
        operator_delete__(m);
    }
}

// ===========================================================================
// eastl map lookups in the SSLManager
// ===========================================================================
struct RTreeU {
    void find(void** out, const unsigned* key);       // 0x00e5c780
    void erase(void* a, void* b);                     // 0x00898b20
    void DoNukeSubtree(void* node);                   // 0x00d3b370
};

struct SessionNode { char pad[0x14]; int value; };

struct SessionOwner {
    char pad00[0x48];
    RTreeU tree;                    // +0x48 (anchor at +0x48, end marker at +0x4c)

    void* FindAndRelease(const char* name, char remove);   // 0x0094F870
};

static unsigned Fnv1(const char* s)
{
    unsigned h = 0x811c9dc5;
    for (; *s; ++s) {
        h = h * 0x1000193;
        h ^= (unsigned char)*s;
    }
    return h;
}

// @ 0x0094F870
void* __thiscall SessionOwner::FindAndRelease(const char* name, char remove)
{
    unsigned h = Fnv1(name);
    void* node = 0;
    tree.find(&node, &h);
    if ((char*)node == (char*)this + 0x4c)
        return 0;
    int v = *(int*)((char*)node + 0x14);
    if (v == 0)
        return 0;
    if (remove == 0) {
        CRYPTO_add_lock((int*)(v + 0x9c), 1, 0xe, g_szFileName, 0x566);
        return (void*)v;
    }
    tree.erase(&h, node);
    return (void*)v;
}

// @ 0x0094F910
unsigned __thiscall SSLManager::GetSession(const char* name)
{
    Mutex94* m = (Mutex94*)((char*)this + 0x18);
    m->Lock(&g_lockArg);
    unsigned h = Fnv1(name);
    void* node = 0;
    RTreeU* tree = (RTreeU*)((char*)this + 0x48);
    tree->find(&node, &h);
    if ((char*)node != (char*)this + 0x4c)
        tree->erase(&h, node);
    return (unsigned)m->Unlock() & 0xffffff00u;
}

// @ 0x0094F990
void __thiscall SSLManager::RemoveSession()
{
    Mutex94* m = (Mutex94*)((char*)this + 0x18);
    m->Lock(&g_lockArg);
    RTreeU* tree = (RTreeU*)((char*)this + 0x48);
    void* end = (char*)this + 0x4c;
    for (void* n = *(void**)((char*)this + 0x50); n != end; ) {
        SSL_SESSION_free(*(void**)((char*)n + 0x14));
        n = RBTreeIncrement(n);
    }
    tree->DoNukeSubtree(*(void**)((char*)this + 0x54));
    *(void**)((char*)this + 0x50) = (char*)this + 0x4c;
    *(void**)((char*)this + 0x4c) = (char*)this + 0x4c;
    *(void**)((char*)this + 0x54) = 0;
    *(char*)((char*)this + 0x58) = 0;
    *(int*)((char*)this + 0x5c) = 0;
    m->Unlock();
}

// @ 0x0094FA60
void __fastcall Fn0094fa60(int param_1, int, void** out, void* parent, unsigned* key, char flag)
{
    int lt = (flag == 0 && parent != (void*)(param_1 + 4) && *(unsigned*)((char*)parent + 0x10) <= *key) ? 1 : 0;
    void* node = *(void**)(param_1 + 0x18);
    if (node == 0)
        node = operator new(*(unsigned*)(param_1 + 0x28),
                           "EASTL", 0, 0,
                           "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                           0xd1);
    else
        *(void**)(param_1 + 0x18) = *(void**)node;
    if ((char*)node + 0x10 != 0) {
        *(unsigned*)((char*)node + 0x10) = key[0];
        *(unsigned*)((char*)node + 0x14) = key[1];
    }
    RBTreeInsert(node, parent, (void*)(param_1 + 4), lt);
    *(int*)(param_1 + 0x14) = *(int*)(param_1 + 0x14) + 1;
    *out = node;
}
