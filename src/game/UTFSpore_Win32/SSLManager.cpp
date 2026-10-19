// src/game/UTFSpore_Win32/SSLManager.cpp -- migrated from slice(s) s0094fb80, s0094ea80 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/SSLManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/SSL/SSLManager.h"
#include "EA/SSL/FileSystemDefault.h"
#include "EA/Allocator/ICoreAllocator.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int   __cdecl strcmp(const char*, const char*);
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
extern "C" void* __cdecl BIO_new(void* method);                                                   // 0x01177470
extern "C" long  __cdecl BIO_ctrl(void* bio, int cmd, long larg, void* parg);                     // 0x01177260
extern "C" void  __cdecl BIO_free(void* bio);                                                     // 0x01176f10
extern "C" void* __cdecl Fn117b240(const char* file, void* x);                                    // 0x0117b240
extern "C" void* __cdecl Fn117b210(void* bio, int a, int b, int c);                               // 0x0117b210
extern "C" void* __cdecl SSL_get_peer_certificate(void* ssl);                                     // 0x0117b3c0
extern "C" int   __cdecl Fn11801b0(void* x);                                                      // 0x011801b0
extern "C" void* __cdecl Fn11801f0(void* x509, int i);                                            // 0x011801f0
extern "C" void* __cdecl Fn1180160(void* ext);                                                    // 0x01180160
extern "C" int   __cdecl OBJ_obj2nid(void* obj);                                                  // 0x0117fa60
extern "C" const char* __cdecl Fn117f7f0(int nid);                                                // 0x0117f7f0
extern "C" void* __cdecl X509V3_EXT_get(void* ext);                                               // 0x0117f5f0
extern "C" void* __cdecl ASN1_item_d2i(void* out, void* in, int len, void* it);                   // 0x0117f530
extern "C" int   __cdecl sk_num(void* sk);                                                        // 0x0117dde0
extern "C" void* __cdecl sk_value(void* sk, int i);                                               // 0x0117ddf0
extern "C" void* __cdecl X509_get_subject_name(void* x);                                          // 0x0117d5a0
extern "C" int   __cdecl X509_NAME_get_text_by_NID(void* name, int nid, char* buf, int len);     // 0x0117d4b0
extern "C" void  __cdecl X509_free(void* x);                                                      // 0x0117cf90
extern "C" long  __cdecl SSL_get_verify_result(void* ssl);                                        // 0x0117c410
extern "C" void  __cdecl ERR_put_error(int lib, int func, int reason, const char* file, int line); // 0x01180d50
extern "C" void  __cdecl ERR_add_error_data(int num, ...);                                        // 0x01180a70
extern "C" int   __cdecl SSL_CTX_load_verify_locations(void* ctx, const char* file, const char* path); // 0x0117c3f0
extern "C" void  __cdecl CRYPTO_add_lock(int* p, int n, int type, const char* file, int line);    // 0x011815d0
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
extern "C" char  g_szEmpty[];                      // 0x013ec47c
#include <intrin.h>
#include "EA/Thread/Mutex.h"
#include "EA/Sockets/Socket.h"
#pragma intrinsic(_InterlockedIncrement, _InterlockedExchangeAdd, _InterlockedExchange)
#pragma intrinsic(strcmp)

// ---- items of slice s0094ea80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int   __cdecl strcmp(const char*, const char*);
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
void* __cdecl operator new(unsigned int, const char*, int, int, const char*, int);
void  __cdecl operator_delete__(void*) throw();
extern "C" void* __cdecl BIO_new(void* method);                                                   // 0x01177470
extern "C" long  __cdecl BIO_ctrl(void* bio, int cmd, long larg, void* parg);                     // 0x01177260
extern "C" void  __cdecl BIO_free(void* bio);                                                     // 0x01176f10
extern "C" void* __cdecl Fn117b240(const char* file, void* x);                                    // 0x0117b240
extern "C" void* __cdecl Fn117b210(void* bio, int a, int b, int c);                               // 0x0117b210
extern "C" void* __cdecl SSL_get_peer_certificate(void* ssl);                                     // 0x0117b3c0
extern "C" int   __cdecl Fn11801b0(void* x);                                                      // 0x011801b0
extern "C" void* __cdecl Fn11801f0(void* x509, int i);                                            // 0x011801f0
extern "C" void* __cdecl Fn1180160(void* ext);                                                    // 0x01180160
extern "C" int   __cdecl OBJ_obj2nid(void* obj);                                                  // 0x0117fa60
extern "C" const char* __cdecl Fn117f7f0(int nid);                                                // 0x0117f7f0
extern "C" void* __cdecl X509V3_EXT_get(void* ext);                                               // 0x0117f5f0
extern "C" void* __cdecl ASN1_item_d2i(void* out, void* in, int len, void* it);                   // 0x0117f530
extern "C" int   __cdecl sk_num(void* sk);                                                        // 0x0117dde0
extern "C" void* __cdecl sk_value(void* sk, int i);                                               // 0x0117ddf0
extern "C" void* __cdecl X509_get_subject_name(void* x);                                          // 0x0117d5a0
extern "C" int   __cdecl X509_NAME_get_text_by_NID(void* name, int nid, char* buf, int len);     // 0x0117d4b0
extern "C" void  __cdecl X509_free(void* x);                                                      // 0x0117cf90
extern "C" long  __cdecl SSL_get_verify_result(void* ssl);                                        // 0x0117c410
extern "C" void  __cdecl ERR_put_error(int lib, int func, int reason, const char* file, int line); // 0x01180d50
extern "C" void  __cdecl ERR_add_error_data(int num, ...);                                        // 0x01180a70
extern "C" int   __cdecl SSL_CTX_load_verify_locations(void* ctx, const char* file, const char* path); // 0x0117c3f0
extern "C" void  __cdecl CRYPTO_add_lock(int* p, int n, int type, const char* file, int line);    // 0x011815d0
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
extern "C" char  g_szEmpty[];                      // 0x013ec47c
struct Mutex94 {
    int Lock(const void* p);
    int Unlock();
};
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
struct SSLContext {
    char pad[0x14];
    bool LoadVerifyLocations(const char* file);   // 0x0094F0B0
};
struct MutexNew94 {
    void ctor(int a, int b);          // 0x009222A0  EA::Thread::Mutex::Mutex
    void dtor();                      // 0x00922130  EA::Thread::Mutex::~Mutex
};
void* __cdecl memcpy_impl(void* dst, const void* src, unsigned n);   // 0x011E0744
struct StreamRef94 {
    virtual void Destroy(int);       // +0x00
    char pad04[0x20c];
    int  mnRefCount;                 // +0x210
    char pad214[0x18];
    SSLManager* mpManager;           // +0x22c
};
struct FileSystem94 {
    virtual void* OpenFile(const char* name, int m1, int m2);
};
struct RTreeU {
    void find(void** out, const unsigned* key);       // 0x00e5c780
    void erase(void* a, void* b);                     // 0x00898b20
    void DoNukeSubtree(void* node);                   // 0x00d3b370
};
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
// ---- items of slice s0094ea80 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" char  g_szUTFOSSL[];                    // 0x0143fee8 "UTF_SSL/OpenSSL"
extern SSLManager* g_spSSLManager;    // 0x0166aaa8

// ---- items of slice s0094fb80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char  g_szCiphers[];    // 0x0143FF2C "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"
extern "C" void  __cdecl CRYPTO_set_id_callback(void* fn);                 // 0x011812F0
extern "C" void  __cdecl CRYPTO_set_locking_callback(void* fn);            // 0x011812E0
extern "C" void  __cdecl Fn011812b0(void* fn);                             // 0x011812B0 dynlock_create
extern "C" void  __cdecl CRYPTO_set_dynlock_lock_callback(void* fn);       // 0x011812C0
extern "C" void  __cdecl CRYPTO_set_dynlock_destroy_callback(void* fn);    // 0x011812D0
extern "C" unsigned __cdecl Fn01181150();                                  // 0x01181150 CRYPTO_num_locks
extern "C" void  __cdecl CRYPTO_set_mem_functions(void* m, void* r, void* f); // 0x01183360
extern "C" void  __cdecl SSL_CTX_free(void* ctx);                          // 0x0117BA10
extern "C" int   __cdecl SSL_CTX_set_verify(void* ctx, int mode, void* cb);// 0x0117BB10
extern "C" void  __cdecl SSL_CTX_set_tmp_dh_callback(void* ctx, void* cb); // 0x0117C420
extern "C" int   __cdecl SSL_CTX_set_purpose(void* ctx, int purpose);      // 0x0117BB30
extern "C" long  __cdecl SSL_CTX_ctrl(void* ctx, int cmd, long larg, void* parg); // 0x0117B500
extern "C" int   __cdecl SSL_CTX_set_cipher_list(void* ctx, const char* list);    // 0x0117B780
extern "C" int   __cdecl Fn011831f0();                                     // 0x011831F0
extern "C" void  __cdecl RAND_seed(void* buf, int n);                      // 0x01178530
extern "C" void  __cdecl Fn011831e0();                                     // 0x011831E0
extern "C" void* __cdecl Fn011831d0();                                     // 0x011831D0
extern "C" void* __cdecl Fn011831a0();                                     // 0x011831A0
extern "C" void* __cdecl Fn01182ab0();                                     // 0x01182AB0
extern "C" void* __cdecl AddStat(unsigned v);                              // 0x0117CA60
extern "C" __declspec(dllimport) __int64 __cdecl _time64(__int64*);        // 0x013CC55C
#pragma intrinsic(_InterlockedIncrement, _InterlockedExchangeAdd)
#define B(p)         ((char*)(p))
#define I8(p,o)      (*(char*)((char*)(p)+(o)))
#define I32(p,o)     (*(int*)((char*)(p)+(o)))
#define PTR(p,o)     (*(void**)((char*)(p)+(o)))
extern "C" void* g_spSSLManager_s0094_fb80;   // 0x0166AAA8
struct Ext {
    void* ctor(int a, int b);               // 0x009222A0 Mutex::Mutex
    int   Lock(const void* nm);             // 0x009221B0 Mutex::Lock
    void  fixedvec_resize(unsigned n);      // 0x0089CB60 fixed_vector::resize
    void* faf0(void* out, void* value, void* b);   // 0x0094FAF0 map::insert(pair<iterator,bool>* out, const value_type* v, bool)
    int*  resize(unsigned n);               // 0x00837310 RawFixed::Resize
    void  d470(int a);                      // 0x0094D470
    int   e3a0(int a, int b, int c);        // 0x0094E3A0
    int   e3f0(int a, int b, int c);        // 0x0094E3F0
    int   e650(int a, int b, int c);        // 0x0094E650
    int   e4b0(int a, int b);               // 0x0094E4B0
    void* e340(unsigned iface);             // 0x0094E340 StreamSocket::AsInterface
    void  nuke(void* node);                 // 0x00D3B370 DoNukeSubtree
};
void  __fastcall Mutex_dtor(void* m);                   // 0x00922130
int   __fastcall Mutex_Unlock(void* m);                 // 0x00922270
void  __fastcall Fn0094fa00(void* map);                 // 0x0094FA00 fixed_map ctor
void  __fastcall SSLManager_RemoveSession(void* self);  // 0x0094F990
int   __cdecl GetThreadId();                                    // 0x00921CC0
struct SSLManager_s0094_fb80 {
    char _b[0x190];
    SSLManager_s0094_fb80* Ctor(ICoreAllocator* alloc);                  // 0x0094FC40
    char RestoreClientSession(void* ssl, unsigned char* name); // 0x0094FD20
    void* DeletingDtor(char flags);                           // 0x0094FE70
    unsigned GetSession(const char* name);                    // 0x0094F910
    void* FindAndRelease(const char* name, char remove);      // 0x0094F870
};
// ---- items of slice s0094fb80 end

// @ 0x0094eb70
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

// @ 0x0094ec00
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

// @ 0x0094ee30
void* __cdecl Fn0094ee30(void* a, void* b)
{
    void* bio = BIO_new(&g_bioMethodTable);
    if (bio != 0)
        BIO_ctrl(bio, 0x6a, (long)b, a);
    return bio;
}

// @ 0x0094ee70
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

// @ 0x0094eec0
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

// @ 0x0094ef10
unsigned __cdecl Fn0094ef10(BIO94* p, char* buf, unsigned len)
{
    unsigned r = 0;
    if (p->f0c != 0 && buf != 0) {
        if (p->obj->i38(buf, len))
            r = len;
    }
    return r;
}

// @ 0x0094efe0
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

// @ 0x0094f030
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

// @ 0x0094f080
void EA::SSL::SSLManager::RegisterFileSystem(EA::SSL::FileSystem * v, bool set)
{
    int v_v = (int)v;
    if (set) {
        *(int*)((char*)this + 0x14c) = v_v;
        return;
    }
    if (*(int*)((char*)this + 0x14c) == v_v)
        *(int*)((char*)this + 0x14c) = 0;
}

// @ 0x0094f0b0
bool SSLContext::LoadVerifyLocations(const char* file)
{
    return SSL_CTX_load_verify_locations(*(void**)((char*)this + 0x14), file, 0) == 1;
}

// @ 0x0094f0e0
void* __cdecl SetSSLManagerGlobal(void* m)
{
    void* old = g_spSSLManager;
    g_spSSLManager = (SSLManager*)m;
    return old;
}

// @ 0x0094f120
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

// @ 0x0094f160
namespace EA {
namespace SSL {
void * SSL_Malloc(unsigned int size)
{
    int* p = (int*)g_spSSLManager->mpCoreAllocator->AllocB((unsigned)size + 8, g_szUTFOSSL, 0);
    if (p != 0) {
        *p = size + 8;
        p[1] = 0;
        p += 2;
    }
    return p;
}
}
}  // namespace EA::SSL

// @ 0x0094f1a0
void __cdecl EA_SSL_SSL_Free(void* p)
{
    g_spSSLManager->mpCoreAllocator->Free((char*)p - 8, 0);
}

// @ 0x0094f1c0
namespace EA {
namespace SSL {
void * SSL_Realloc(void * oldp, unsigned int size)
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
}
}  // namespace EA::SSL

// @ 0x0094f260
int __fastcall Fn0094f260(StreamRef94* p)
{
    if (p->mnRefCount > 1)
        return p->mnRefCount = p->mnRefCount - 1;
    ICoreAllocator* a = p->mpManager->mpCoreAllocator;
    p->Destroy(0);
    a->Free(p, 0);
    return 0;
}

// @ 0x0094f2a0
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

// @ 0x0094f4d0
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

// @ 0x0094f850
void __cdecl Fn0094f850(MutexNew94* m)
{
    if (m != 0) {
        m->dtor();
        operator_delete__(m);
    }
}

// @ 0x0094f870
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

// @ 0x0094f910
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

// @ 0x0094fb80
namespace  {
int THREAD_cleanup()
{
    void* mgr = g_spSSLManager_s0094_fb80;
    EA::Allocator::ICoreAllocator* alloc = (EA::Allocator::ICoreAllocator*)PTR(mgr, 0x10);
    CRYPTO_set_id_callback(0);
    CRYPTO_set_locking_callback(0);
    Fn011812b0(0);
    CRYPTO_set_dynlock_lock_callback(0);
    CRYPTO_set_dynlock_destroy_callback(0);
    mgr = g_spSSLManager_s0094_fb80;
    int count = (int)(B(PTR(mgr, 0x158)) - B(PTR(mgr, 0x154))) >> 2;
    for (int i = 0; i < count; ++i) {
        void* m = *(void**)(B(PTR(mgr, 0x154)) + i * 4);
        if (m != 0) {
            Mutex_dtor(m);
            alloc->Free(m, 0);
            mgr = g_spSSLManager_s0094_fb80;
        }
    }
    void* begin = PTR(mgr, 0x154);
    void* end = PTR(mgr, 0x158);
    memcpy_impl(begin, end, 0);
    int sz = (int)(B(end) - B(begin)) >> 2;
    I32(mgr, 0x158) += -4 * sz;
    return 1;
}
}  // namespace 

// @ 0x0094fc40
SSLManager_s0094_fb80* SSLManager_s0094_fb80::Ctor(ICoreAllocator* alloc)
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
    if (g_spSSLManager_s0094_fb80 == 0)
        g_spSSLManager_s0094_fb80 = self;
    return this;
}

// @ 0x0094fcc0
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

// @ 0x0094fd20
char SSLManager_s0094_fb80::RestoreClientSession(void* ssl, unsigned char* name)
{
    void* self = this;
    ((Ext*)(B(self) + 0x18))->Lock(&g_lockArg);
    GetSession((const char*)name);
    CRYPTO_add_lock((int*)(B(ssl) + 0x9c), 1, 0xe, g_szFileName, 0x581);
    unsigned h = 0x811c9dc5;
    unsigned c = *name;
    unsigned char* p = name;
    while (c != 0) {
        p++;
        h = h * 0x1000193 ^ c;
        c = *p;
    }
    struct MapValue { unsigned key; void* ssl; } v;
    v.key = h;
    v.ssl = ssl;
    void* result[2];
    // the original pushes the dead `name` argument slot with its low byte cleared (a bool temp stored over it)
    ((Ext*)(B(self) + 0x48))->faf0(result, &v, (void*)((unsigned)name & 0xffffff00u));
    Mutex_Unlock(B(self) + 0x18);
    return 1;
}

// @ 0x0094fdc0
int __cdecl THREAD_setup()
{
    void* mgr = g_spSSLManager_s0094_fb80;
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
        *(void**)(B(PTR(g_spSSLManager_s0094_fb80, 0x154)) + i * 4) = r;
    }
    CRYPTO_set_id_callback((void*)0x0094EB40);
    CRYPTO_set_locking_callback((void*)0x0094F0F0);
    Fn011812b0((void*)0x0094F120);
    CRYPTO_set_dynlock_lock_callback((void*)0x0094EB50);
    CRYPTO_set_dynlock_destroy_callback((void*)0x0094F850);
    return 1;
}

// @ 0x0094fe70
void* SSLManager_s0094_fb80::DeletingDtor(char flags)
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

// @ 0x0094fed0
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
