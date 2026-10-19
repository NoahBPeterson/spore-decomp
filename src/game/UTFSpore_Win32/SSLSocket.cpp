// src/game/UTFSpore_Win32/SSLSocket.cpp -- migrated from slice(s) s0094fb80 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/SSLSocket.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Sockets/Socket.h"
#include "EA/Thread/Mutex.h"
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/SSL/SSLManager.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl BIO_new(void* method);                            // 0x01177470
extern "C" void  __cdecl BIO_clear_flags(void* bio, int flags);            // 0x01176F90
extern "C" void* __cdecl Fn0117c560(void* a);                              // 0x0117C560
extern "C" int   __cdecl Fn0117c940(void* ssl, int cmd, long larg, void* parg);  // 0x0117C940
extern "C" int   __cdecl SSL_accept(void* ssl);                            // 0x0117CDF0
extern "C" int   __cdecl SSL_connect(void* ssl);                           // 0x0117CE30
extern "C" void  __cdecl SSL_free(void* ssl);                              // 0x0117C790
extern "C" int   __cdecl SSL_set_bio(void* ssl, void* rbio, void* wbio);   // 0x0117B350
extern "C" int   __cdecl Fn0117c8f0(void* ssl);                            // 0x0117C8F0
extern "C" void* __cdecl Fn0117c440(void* ctx);                            // 0x0117C440
extern "C" int   __cdecl Fn0117b410(void* ssl, void* buf, int n);          // 0x0117B410
extern "C" int   __cdecl Fn0117b4a0(void* ssl, void* buf, int n);          // 0x0117B4A0
extern "C" int   __cdecl Fn0117ccd0(void* ssl, int n);                     // 0x0117CCD0
extern "C" int   __cdecl EC_GROUP_get_curve_name(void* g);                 // 0x011B1E50
extern "C" void* __cdecl Fn00ff0420(void* p);                              // 0x00FF0420
#include <intrin.h>
#pragma intrinsic(_InterlockedIncrement, _InterlockedExchangeAdd)

// ---- items of slice s0094fb80 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define B(p)         ((char*)(p))
#define I8(p,o)      (*(char*)((char*)(p)+(o)))
#define U16(p,o)     (*(unsigned short*)((char*)(p)+(o)))
#define I32(p,o)     (*(int*)((char*)(p)+(o)))
#define PTR(p,o)     (*(void**)((char*)(p)+(o)))
void  __cdecl operator_delete__(void*) throw();                                     // 0x00F47380
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
char  __fastcall Fn0094d3c0(void* self);                // 0x0094D3C0
int   __fastcall Fn0094d4b0(void* self);                // 0x0094D4B0
void  __fastcall Fn0094e770(void* self);                // 0x0094E770
void* __fastcall Fn0094e9a0(void* self);                // 0x0094E9A0
int   __cdecl NetSSLVerifyConnection(void* ssl, const char* name); // 0x0094EC00
int   __fastcall RefCount_Release_M8(int* p);                  // 0x0094EA90
int   __cdecl Vsnprintf8(char* buf, unsigned size, const char* fmt, void* ap); // 0x00938400
int   __cdecl FStr_sprintf(char* dst, const char* fmt, const char* a, unsigned b); // 0x00950850
extern "C" void* __cdecl BIO_new(void* method);                            // 0x01177470
extern "C" void  __cdecl BIO_clear_flags(void* bio, int flags);            // 0x01176F90
extern "C" void* __cdecl Fn0117c560(void* a);                              // 0x0117C560
extern "C" int   __cdecl Fn0117c940(void* ssl, int cmd, long larg, void* parg);  // 0x0117C940
extern "C" int   __cdecl SSL_accept(void* ssl);                            // 0x0117CDF0
extern "C" int   __cdecl SSL_connect(void* ssl);                           // 0x0117CE30
extern "C" void  __cdecl SSL_free(void* ssl);                              // 0x0117C790
extern "C" int   __cdecl SSL_set_bio(void* ssl, void* rbio, void* wbio);   // 0x0117B350
extern "C" int   __cdecl Fn0117c8f0(void* ssl);                            // 0x0117C8F0
extern "C" void* __cdecl Fn0117c440(void* ctx);                            // 0x0117C440
extern "C" int   __cdecl Fn0117b410(void* ssl, void* buf, int n);          // 0x0117B410
extern "C" int   __cdecl Fn0117b4a0(void* ssl, void* buf, int n);          // 0x0117B4A0
extern "C" int   __cdecl Fn0117ccd0(void* ssl, int n);                     // 0x0117CCD0
extern "C" int   __cdecl EC_GROUP_get_curve_name(void* g);                 // 0x011B1E50
extern "C" void* __cdecl Fn00ff0420(void* p);                              // 0x00FF0420
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
// ---- items of slice s0094fb80 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
char __fastcall StreamSSLSocket_Connect(void* self);  // 0x00950970 (stays in the slice: not this object's)
char __fastcall StreamSSLSocket_SaveClientSession(void* self);  // 0x00950a20 (stays in the slice: not this object's)

// @ 0x00950080
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

// @ 0x009500c0
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

// @ 0x00950200
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

// @ 0x00950280
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

// @ 0x00950330
bool EA::Sockets::Socket::Shutdown(EA::Sockets::ShutdownMode v)
{
    void* self = this;
    if (I32(self, 0xcc) == -1) {
        I32(self, 0xcc) = v;
        return 1;
    }
    return 0;
}

// @ 0x00950350
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

// @ 0x009503c0
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

// @ 0x00950450
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

// @ 0x009504d0
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

// @ 0x00950540
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

// @ 0x00950580
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

// @ 0x009505c0
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

// @ 0x00950610
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

// @ 0x00950650
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

// @ 0x00950740
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

// @ 0x00950870
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

// @ 0x00950920
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

// @ 0x00950ad0
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

// @ 0x00950b10
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
