// src/game/UTFSpore_Win32/Socket_imp.cpp -- migrated from slice(s) s0094dbc0, s0094cac0, s0094ea80 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Socket_imp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/SSL/FileSystemDefault.h"
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/SSL/SSLManager.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int   __cdecl strcmp(const char*, const char*);
#include <intrin.h>
#include "EA/Sockets/Socket.h"
#include "EA/Sockets/Address.h"
#include "EA/Sockets/Error.h"
#include "EA/Thread/Mutex.h"
#include <string.h>
#include <new>
#include "EA/Sockets/DatagramSocket.h"
#include "EA/Sockets/IPAddress.h"
#include "EA/Sockets/StreamSocket.h"
#pragma intrinsic(_InterlockedIncrement, _InterlockedExchangeAdd, _InterlockedExchange)
#pragma intrinsic(strcmp)

// ---- items of slice s0094ea80 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RefObj94 { virtual void Destroy(int); int mnRefCount; };
// ---- items of slice s0094ea80 end

// ---- items of slice s0094cac0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __stdcall WSAGetLastError(void);                 // wsock32
extern "C" __declspec(dllimport) int __stdcall closesocket(unsigned s);               // wsock32
extern "C" __declspec(dllimport) int __stdcall shutdown(unsigned s, int how);         // wsock32
extern "C" __declspec(dllimport) int __stdcall setsockopt(unsigned s, int level, int optname, const char* optval, int optlen);
extern "C" __declspec(dllimport) int __stdcall getpeername(unsigned s, void* name, int* namelen);
extern "C" __declspec(dllimport) int __stdcall bind(unsigned s, const char* name, int namelen);  // wsock32
#define REPORT_ERROR(self)                                                    \
    do {                                                                     \
        void** vt_ = *(void***)((char*)(self) - 8);                           \
        ((void(__thiscall**)(void*, int))vt_)[1]((char*)(self) - 8,           \
            ((int(__stdcall*)(int))WSAGetLastError)(0));                     \
    } while (0)
struct Socket {
    char           mPad00[4];    // -0x08 owner vptr lives one object earlier
    char           mPad04[4];    // +0x00
    unsigned       hSocket;      // +0x04 (socket handle) ... reached as ecx+4
    unsigned short mFamily;      // +0x08 (7 dwords copied by SetAddressRaw)
    unsigned char  mPad75;       // +0x75
    unsigned char  mPad77;       // +0x77

    void Destroy2();                                        // 0x0094d300
    unsigned QueryInterface(int iid);                       // 0x0094d360
    bool Create();                                          // 0x0094d3c0
    bool Bind(const void* addr);                            // 0x0094d410
    bool Fn0094d470(int how);                               // 0x0094d470
    __declspec(noinline) bool Fn0094d4b0();                // 0x0094d4b0
    bool SetLingerRaw(int a, int b, int c);                 // 0x0094d500
    bool SetAddressRaw(const void* a);                      // 0x0094d520
    bool GetPeerNameRaw(void* addr, unsigned* len);         // 0x0094d550
    bool SetPeerAddressRaw(const void* a);                  // 0x0094d5a0
    int  GetWaitingDataSize(unsigned timeout);              // 0x0094d5c0
    bool WaitReadable(unsigned timeout);                    // 0x0094d690
    bool WaitWritable(unsigned timeout);                    // 0x0094d730
    unsigned WaitMulti(unsigned mode, unsigned timeout);    // 0x0094d7d0
    bool SetOptInt(unsigned char v);                       // 0x0094d960
    bool SetOptInt2(unsigned char v);                      // 0x0094da20
    bool GetOptInt(unsigned char* out, unsigned* val);     // 0x0094da70
    bool SetLingerOpt(unsigned char on, unsigned short level); // 0x0094daf0
    bool GetNonBlocking(unsigned char* out);                // 0x0094db50
    bool SetNonBlockingOption(unsigned char b);             // 0x0094db60
private:
    void ReportError(char scratch) {                        // edx = [self-8], eax = WSAGetLastError()
        void** vt = *(void***)((char*)this - 8);
        int ec = ((int(__stdcall*)(int))WSAGetLastError)(0);
        (void)scratch;
        ((void(__thiscall*)(void*, int))vt[1])((char*)this - 8, ec);
    }
    void SetOpt(uint32_t optname, int value) {              // edx/ecx = hSocket
        unsigned h = *(unsigned*)((char*)this + 4);
        int r = setsockopt(h, 0xffff, (int)optname, (const char*)&value, 4);
        (void)h;
        if (r != 0) {
            ReportError(0);
        }
    }
};
struct TimeVal { long tv_sec; long tv_usec; };
struct FdSet  { unsigned fd_count; unsigned fd_array[64]; };
extern "C" __declspec(dllimport) int __stdcall ioctlsocket(unsigned s, long cmd, unsigned long* argp);  // wsock32
extern "C" __declspec(dllimport) int __stdcall select(int nfds, void* rd, void* wr, void* ex, void* to);
extern "C" __declspec(dllimport) int __stdcall getsockopt(unsigned s, int level, int optname, char* optval, int* optlen);
extern "C" __declspec(dllimport) unsigned __stdcall socket(int af, int type, int protocol);  // wsock32
// ---- items of slice s0094cac0 end

// ---- items of slice s0094dbc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) unsigned int __stdcall accept(unsigned s, void* addr, int* addrlen);
extern "C" __declspec(dllimport) int __stdcall connect(unsigned s, const void* name, int namelen);
extern "C" __declspec(dllimport) int __stdcall send(unsigned s, const char* buf, int len, int flags);
extern "C" __declspec(dllimport) int __stdcall sendto(unsigned s, const char* buf, int len, int flags, const void* to, int tolen);
extern "C" __declspec(dllimport) int __stdcall recv(unsigned s, char* buf, int len, int flags);
extern "C" __declspec(dllimport) int __stdcall recvfrom(unsigned s, char* buf, int len, int flags, void* from, int* fromlen);
extern "C" __declspec(dllimport) int __stdcall listen(unsigned s, int backlog);
extern "C" __declspec(dllimport) int __stdcall getsockname(unsigned s, void* name, int* namelen);
extern "C" int     g_sockAddrInit;                          // 0x0166AAA4
#pragma intrinsic(_InterlockedExchange)
void __cdecl operator_delete__(void* p) throw();   // 0x00F47380
struct Address {
    unsigned short sa_family;    // +0x00
    char           sa_data[26];  // +0x02
};                               // size 0x1c
struct Error {
    int  mErrorType;             // +0x00
    char mErrorString[32];       // +0x04
    Error() {}
    Error(int t) { mErrorType = t; mErrorString[0] = 0; }
};                               // size 0x24
struct IPAddress {
    int          mUnused;        // +0x00
    unsigned int mAddress;       // +0x04
};
struct fd_set_t {
    unsigned int fd_count;              // +0x00
    unsigned int fd_array[64];          // +0x04
};
struct timeval_t {
    long tv_sec;
    long tv_usec;
};
extern "C" Address g_sockLocalAddress;                      // 0x0166AA88
bool __cdecl Sockets_GetCurrentMachineAddress(IPAddress* out, unsigned int index);  // 0x0094C1D0
void Fn0094d350();                                          // 0x0094D350
struct Callback94 {
    char mData[0x24];
    void ctor();                                        // 0x00929E00
    void dtor();                                        // 0x00929D50
    bool Set(void (*fn)(), unsigned id, int a);         // 0x00929DA0
    bool SetProcessor(int p);                           // 0x0092A7D0
    bool SetStream(void* stream);                       // 0x00929BC0
    bool Schedule(int s);                               // 0x0092A7A0
};
struct Primary {
    virtual void v00();
    virtual void DoError(int err, char const* msg);
};
struct PendingSocket;
struct ISocket {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual int  v07(void const* buf, int len, Address const* to, int flags);
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual bool v13();                                        // Close
    virtual bool v14(unsigned& sockId, Address& addr, bool& ok);  // Accept
    virtual void v15();
    virtual void v16();
    virtual bool v17(Address& a, unsigned& s);                 // GetAddress impl
    virtual void v18();
    virtual void v19();
    virtual bool v20(Address& a, unsigned& s);                 // GetPeerAddress impl
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual bool v25();                                        // IsWaitingDataAvailable

    unsigned mSocketId;   // +0x04

    void Fn0094d4b0();                                          // 0x0094D4B0

    bool GetRouteOption(bool* out);                             // 0x0094DBC0
    bool SetRouteOption(bool b);                                // 0x0094DC30
    bool SetKeepAliveOption(bool b);                            // 0x0094DCF0
    bool GetReceiveBufferOption(int* out);                      // 0x0094DD40
    bool SetReceiveBufferOption(int size);                      // 0x0094DDA0
    bool GetSendBufferOption(int* out);                         // 0x0094DDF0
    bool SetSendBufferOption(int size);                         // 0x0094DE50
    bool SetReuseAddressOption(bool b);                         // 0x0094DF10
    bool SetSendDelayOption(bool b);                            // 0x0094DFD0
    bool GetSendTimeoutOption(int* out);                        // 0x0094E020
    bool SetSendTimeoutOption(int size);                        // 0x0094E080
    bool GetReceiveTimeoutOption(int* out);                     // 0x0094E0D0
    bool SetReceiveTimeoutOption(int size);                     // 0x0094E130
    bool SetOOBOption(bool b);                                  // 0x0094E1F0

    void* AsInterfaceDatagram(unsigned id);                     // 0x0094E240
    void* AsInterfaceStream(unsigned id);                       // 0x0094E340

    int  DatagramRead(void* buf, int len, Address* from, int flags);         // 0x0094E290
    int  DatagramWrite(void const* buf, int len, Address const* to, int flags);  // 0x0094E2F0
    int  StreamRead(void* buf, int len, int flags);             // 0x0094E3A0
    int  StreamWrite(void const* buf, int len, int flags);      // 0x0094E3F0
    bool StartListen(int backlog);                              // 0x0094E440
    bool Close();                                               // 0x0094E4A0
    bool Connect(bool* ok, void* stream);                       // 0x0094E4B0
    unsigned WaitForWrite();                                    // 0x0094E560
    bool IsWaitingDataAvailableSub();                           // 0x0094E5E0
    bool AcceptPeer(void* pSocket, bool& ok);                   // 0x0094E5F0
    bool Accept(unsigned* sockId, Address* addr, bool* ok);     // 0x0094E650
    bool DoAccepted(unsigned const& id, Address const& addr, int cs,
                    int family, int type, int protocol);        // 0x0094E6B0
    void SetSocketId(unsigned const& id);                       // 0x0094E700
    bool IsCreated();                                           // 0x0094E710
    bool GetAddress(Address& a);                                // 0x0094E720
    bool GetPeerAddress(Address& a);                            // 0x0094E740
    bool GetAddress2(Address* addr, unsigned* sock);            // 0x0094E7B0
    int  WriteToPeer(void const* buf, int len, int flags);      // 0x0094E960
    bool Shutdown(int mode);                                    // 0x0094EA10
};
struct PendingSocket {
    virtual void p00();
    virtual void p01();
    virtual void p02();
    virtual void p03();
    virtual void p04();
    virtual void p05();
    virtual void p06();
    virtual void p07();
    virtual void p08();
    virtual void p09();
    virtual void p10();
    virtual void p11();
    virtual void p12();
    virtual void p13();
    virtual void p14();
    virtual void p15();
    virtual bool DoAccepted(unsigned const& id, Address const& addr, int cs,
                            int family, int type, int protocol);   // slot 16 (+0x40)
};
struct Socket_s0094_dbc0 {
    void*         mpVtbl;            // 0x00
    int           mnRefCount;        // 0x04
    void*         mpISocketVtbl;     // 0x08
    int           mSocketId;         // 0x0c
    Address       mAddress;          // 0x10
    Address       mPeerAddress;      // 0x2c
    int           mnAddressFamily;   // 0x48
    int           mnType;            // 0x4c
    int           mnProtocol;        // 0x50
    Error         mLastError;        // 0x54
    void*         mpUserData;        // 0x78
    unsigned char mbInitialized;     // 0x7c
    unsigned char mbBound;           // 0x7d
    unsigned char mbSaveSocket;      // 0x7e
    unsigned char mbNonBlocking;     // 0x7f

    void  Destroy();                             // 0x0094E770
    void* DestroyScalar(unsigned flags);         // 0x0094E8D0
};
struct AtomicInt {
    int mValue;
    AtomicInt() { _InterlockedExchange((volatile long*)&mValue, 0); }
};
struct RefCountBase {                    // primary base (obj+0)
    virtual void rcDtor();
    virtual void DoError(int err, char const* msg);
    AtomicInt mRefCount;                 // +0x04
};
struct ISocketBase {                     // secondary base (obj+8)
virtual void b00();
virtual void b01();
virtual void b02();
virtual void b03();
virtual void b04();
virtual void b05();
virtual void b06();
virtual void b07();
virtual void b08();
virtual void b09();
virtual void b10();
virtual void b11();
virtual void b12();
virtual void b13();
virtual void b14();
virtual void b15();
virtual void b16();
virtual void b17();
virtual void b18();
virtual void b19();
virtual void b20();
virtual void b21();
virtual void b22();
virtual void b23();
virtual void b24();
virtual void b25();
};
struct SocketBase : RefCountBase, ISocketBase {
    unsigned      mSocketId;             // 0x0c
    Address       mAddress;              // 0x10
    Address       mPeerAddress;          // 0x2c
    int           mnAddressFamily;       // 0x48
    int           mnType;                // 0x4c
    int           mnProtocol;            // 0x50
    Error         mLastError;            // 0x54
    void*         mpUserData;            // 0x78
    unsigned char mbInitialized;         // 0x7c
    unsigned char mbBound;               // 0x7d
    unsigned char mbSaveSocket;          // 0x7e
    unsigned char mbNonBlocking;         // 0x7f

    SocketBase();                        // 0x0094E850
};
struct IDgramBase {                      // DatagramSocket's second base (obj+0x80)
virtual void d00();
virtual void d01();
virtual void d02();
virtual void d03();
virtual void d04();
virtual void d05();
virtual void d06();
virtual void d07();
virtual void d08();
virtual void d09();
virtual void d10();
virtual void d11();
};
struct DatagramSocketBase : SocketBase, IDgramBase {
    DatagramSocketBase();                // 0x0094E920
};
struct IStrBase {                        // StreamSocket's second base (obj+0x80)
virtual void t00();
virtual void t01();
virtual void t02();
virtual void t03();
virtual void t04();
virtual void t05();
virtual void t06();
virtual void t07();
virtual void t08();
virtual void t09();
virtual void t10();
virtual void t11();
};
struct StreamSocketBase : SocketBase, IStrBase {
    int mConnectStatus;                  // 0x84
    StreamSocketBase();                  // 0x0094E9A0
};
// ---- items of slice s0094dbc0 end

// @ 0x0094d300
void Socket::Destroy2()
{
    *(void**)((char*)this + 0x7c) = 0;
    Fn0094d4b0();
}

// @ 0x0094d360
unsigned Socket::QueryInterface(int iid)
{
    if (iid == 0x23e12220)
        return ((unsigned)this - 8) ? (unsigned)this : 0;
    if (iid == 0x23e12230)
        return (unsigned)this - 8;
    if (iid == 0xee3f516e)
        return ((unsigned)this - 8) ? (unsigned)this : 0;
    return 0;
}

// @ 0x0094d410
bool Socket::Bind(const void* addr)
{
    memcpy((char*)this + 8, (const char*)addr, 7 * 4);
    if (bind(*(unsigned*)((char*)this + 4), (const char*)this + 8, 0x10) != 0) {
        *(unsigned char*)((char*)this + 0x75) = 0;
        REPORT_ERROR(this);
        return false;
    }
    *(unsigned char*)((char*)this + 0x75) = 1;
    return true;
}

// @ 0x0094d470
bool Socket::Fn0094d470(int how)
{
    unsigned h = *(unsigned*)((char*)this + 4);
    if (h != 0xffffffffu) {
        if (shutdown(h, how) != 0) {
            REPORT_ERROR(this);
            return false;
        }
    }
    return true;
}

// @ 0x0094d4b0
bool Socket::Fn0094d4b0()
{
    unsigned h = *(unsigned*)((char*)this + 4);
    *(unsigned char*)((char*)this + 0x75) = 0;
    if (h != 0xffffffffu) {
        int r = closesocket(h);
        *(unsigned*)((char*)this + 4) = 0xffffffffu;
        if (r != 0) {
            REPORT_ERROR(this);
            return false;
        }
    }
    return true;
}

// @ 0x0094d500
bool EA::Sockets::Socket::SetStyle(int a, int b, int c)
{
    *(int*)((char*)this + 0x40) = a;
    *(int*)((char*)this + 0x44) = b;
    *(int*)((char*)this + 0x48) = c;
    return true;
}

// @ 0x0094d520
bool Socket::SetAddressRaw(const void* a)
{
    if (*(unsigned char*)((char*)this + 0x75) == 0) {
        memcpy((char*)this + 8, (const char*)a, 7 * 4);
        return true;
    }
    return false;
}

// @ 0x0094d550
bool Socket::GetPeerNameRaw(void* addr, unsigned* len)
{
    int local = 0x1c;
    unsigned h = *(unsigned*)((char*)this + 4);
    if (getpeername(h, addr, &local) != 0) {
        REPORT_ERROR(this);
        return false;
    }
    if (len) *len = (unsigned)local;
    return true;
}

// @ 0x0094d5a0
bool Socket::SetPeerAddressRaw(const void* a)
{
    memcpy((char*)this + 0x24, (const char*)a, 7 * 4);
    return true;
}

// @ 0x0094d5c0
int EA::Sockets::Socket::GetWaitingDataSize(unsigned int timeout)
{
    unsigned long avail = 0xffffffffu;

    if (timeout != 0) {
        TimeVal tv;
        TimeVal* ptv = 0;
        if (timeout != 0xffffffffu) {
            tv.tv_sec  = timeout / 1000;
            tv.tv_usec = (timeout % 1000) * 1000;
            ptv = &tv;
        }
        FdSet rd;
        unsigned h = *(unsigned*)((char*)this + 4);
        rd.fd_array[0] = h;
        rd.fd_count = 1;
        int r = select(1, &rd, 0, 0, ptv);
        if (r == -1) {
            REPORT_ERROR(this);
            return -1;
        }
        if (r == 0)
            return 0;
    }
    if (ioctlsocket(*(unsigned*)((char*)this + 4), 0x4004667f, &avail) != 0) {
        avail = 0;
        REPORT_ERROR(this);
        return -1;
    }
    return (int)avail;
}

// @ 0x0094d690
bool EA::Sockets::Socket::IsWaitingDataAvailable(unsigned int timeout)
{
    TimeVal tv;
    TimeVal* ptv = 0;
    if (timeout != 0xffffffffu) {
        tv.tv_sec  = timeout / 1000;
        tv.tv_usec = (timeout % 1000) * 1000;
        ptv = &tv;
    }
    FdSet rd;
    rd.fd_array[0] = *(unsigned*)((char*)this + 4);
    rd.fd_count = 1;
    int r = select(1, &rd, 0, 0, ptv);
    if (r == -1) {
        REPORT_ERROR(this);
        return false;
    }
    return (bool)(r != 0);
}

// @ 0x0094d730
bool EA::Sockets::Socket::IsWritable(unsigned int timeout)
{
    TimeVal tv;
    TimeVal* ptv = 0;
    if (timeout != 0xffffffffu) {
        tv.tv_sec  = timeout / 1000;
        tv.tv_usec = (timeout % 1000) * 1000;
        ptv = &tv;
    }
    FdSet wr;
    wr.fd_array[0] = *(unsigned*)((char*)this + 4);
    wr.fd_count = 1;
    int r = select(1, 0, &wr, 0, ptv);
    if (r == -1) {
        REPORT_ERROR(this);
        return false;
    }
    return (bool)(r != 0);
}

// @ 0x0094d7d0
int EA::Sockets::Socket::IsReadableAndOrWritable(EA::Sockets::IOType mode, unsigned int timeout)
{
    TimeVal tv;
    TimeVal* ptv = 0;
    if (timeout != 0xffffffffu) {
        tv.tv_sec  = timeout / 1000;
        tv.tv_usec = (timeout % 1000) * 1000;
        ptv = &tv;
    }
    FdSet rd;
    rd.fd_count = 0;
    if (mode & 1) {
        rd.fd_count = 1;
        rd.fd_array[0] = *(unsigned*)((char*)this + 4);
    }
    FdSet wr;
    wr.fd_count = 0;
    if (mode & 2) {
        wr.fd_count = 1;
        wr.fd_array[0] = *(unsigned*)((char*)this + 4);
    }
    int r = select(1, (mode & 1) ? &rd : 0, (mode & 2) ? &wr : 0, 0, ptv);
    if (r == -1) {
        REPORT_ERROR(this);
        return 0x80;
    }
    unsigned result = 0;
    if (select(1, &rd, 0, 0, ptv) != 0) result |= 1;
    if (select(1, 0, &wr, 0, ptv) != 0) result |= 2;
    return result;
}

// @ 0x0094d960
bool Socket::SetOptInt(unsigned char v)
{
    SetOpt(0x20, v);
    return true;
}

// @ 0x0094da20
bool Socket::SetOptInt2(unsigned char v)
{
    SetOpt(1, v);
    return true;
}

// @ 0x0094da70
bool EA::Sockets::Socket::GetLingerOption(bool & out, unsigned int & val)
{
    struct { unsigned short on; unsigned short sec; } opts;
    opts.on = 0;
    opts.sec = 0;
    unsigned h = *(unsigned*)((char*)this + 4);
    int len = 4;
    if (getsockopt(h, 0xffff, 0x80, (char*)&opts, &len) != 0) {
        REPORT_ERROR(this);
        return false;
    }
    out = (opts.on != 0);
    val = opts.sec;
    return true;
}

// @ 0x0094daf0
bool Socket::SetLingerOpt(unsigned char on, unsigned short level)
{
    struct { unsigned short on; unsigned short sec; } opts;
    opts.on = (unsigned short)(on != 0);
    opts.sec = level;
    unsigned h = *(unsigned*)((char*)this + 4);
    int r = setsockopt(h, 0xffff, 0x80, (const char*)&opts, 4);
    (void)h;
    if (r != 0) {
        ReportError(0);
        return false;
    }
    return true;
}

// @ 0x0094db50
bool Socket::GetNonBlocking(unsigned char* out)
{
    *out = *(unsigned char*)((char*)this + 0x77);
    return true;
}

// @ 0x0094db60
bool EA::Sockets::Socket::SetNonBlockingOption(bool b)
{
    unsigned long value = (unsigned long)(b != 0);
    unsigned h = *(unsigned*)((char*)this + 4);
    int r = ioctlsocket(h, 0x8004667e, &value);
    (void)h;
    if (r != 0) {
        REPORT_ERROR(this);
        return false;
    }
    *(unsigned char*)((char*)this + 0x77) = b;
    return true;
}

// @ 0x0094dbc0
bool ISocket::GetRouteOption(bool* out)
{
    int val; int len = 4;
    if (getsockopt(mSocketId, 0xffff, 0x10, (char*)&val, &len)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    *out = (val == 0);
    return true;
}

// @ 0x0094dc30
bool ISocket::SetRouteOption(bool b)
{
    int v = (b == 0);
    if (setsockopt(mSocketId, 0xffff, 0x10, (char*)&v, 4)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094dcf0
bool ISocket::SetKeepAliveOption(bool b)
{
    int v = (b != 0);
    if (setsockopt(mSocketId, 0xffff, 8, (char*)&v, 4)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094dd40
bool ISocket::GetReceiveBufferOption(int* out)
{
    int len = 4;
    if (getsockopt(mSocketId, 0xffff, 0x1002, (char*)out, &len)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094dda0
bool ISocket::SetReceiveBufferOption(int size)
{
    if (setsockopt(mSocketId, 0xffff, 0x1002, (char*)&size, 4)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094ddf0
bool ISocket::GetSendBufferOption(int* out)
{
    int len = 4;
    if (getsockopt(mSocketId, 0xffff, 0x1001, (char*)out, &len)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094de50
bool ISocket::SetSendBufferOption(int size)
{
    if (setsockopt(mSocketId, 0xffff, 0x1001, (char*)&size, 4)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094df10
bool ISocket::SetReuseAddressOption(bool b)
{
    int v = (b != 0);
    if (setsockopt(mSocketId, 0xffff, 4, (char*)&v, 4)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094dfd0
bool ISocket::SetSendDelayOption(bool b)
{
    int v = b;
    if (setsockopt(mSocketId, 6, 1, (char*)&v, 4)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094e020
bool ISocket::GetSendTimeoutOption(int* out)
{
    int len = 4;
    if (getsockopt(mSocketId, 0xffff, 0x1005, (char*)out, &len)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094e080
bool ISocket::SetSendTimeoutOption(int size)
{
    if (setsockopt(mSocketId, 0xffff, 0x1005, (char*)&size, 4)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094e0d0
bool ISocket::GetReceiveTimeoutOption(int* out)
{
    int len = 4;
    if (getsockopt(mSocketId, 0xffff, 0x1006, (char*)out, &len)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094e130
bool ISocket::SetReceiveTimeoutOption(int size)
{
    if (setsockopt(mSocketId, 0xffff, 0x1006, (char*)&size, 4)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094e1f0
bool ISocket::SetOOBOption(bool b)
{
    int v = b;
    if (setsockopt(mSocketId, 0xffff, 0x100, (char*)&v, 4)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094e240
void* ISocket::AsInterfaceDatagram(unsigned id)
{
    Primary* p;
    switch (id) {
    case 0x23e12221u:
        p = (Primary*)((char*)this - 8);
        return p ? (void*)((char*)this + 0x78) : 0;
    case 0x23e12231u:
        return (void*)((char*)this - 8);
    }
    if (id == 0x23e12220u) {
        p = (Primary*)((char*)this - 8);
        return p ? (void*)this : 0;
    }
    if (id == 0x23e12230u)
        return (void*)((char*)this - 8);
    if (id == 0xee3f516eu) {
        p = (Primary*)((char*)this - 8);
        return p ? (void*)this : 0;
    }
    return 0;
}

// @ 0x0094e290
int ISocket::DatagramRead(void* buf, int len, Address* from, int flags)
{
    int r;
    if (len > 0) {
        int fromlen = 0x1c;
        r = recvfrom(*(int*)((char*)this - 0x74), (char*)buf, len, flags, from, &fromlen);
        if (r == -1) {
            ((Primary*)((char*)this - 0x80))->DoError(WSAGetLastError(), 0);
            return -1;
        }
    } else {
        r = 0;
    }
    return r;
}

// @ 0x0094e2f0
int ISocket::DatagramWrite(void const* buf, int len, Address const* to, int flags)
{
    if (len > 0) {
        int r = sendto(*(int*)((char*)this - 0x74), (char*)buf, len, 0, to, 0x10);
        if (r < 0)
            ((Primary*)((char*)this - 0x80))->DoError(WSAGetLastError(), 0);
        return r;
    }
    return 0;
}

// @ 0x0094e340
void* ISocket::AsInterfaceStream(unsigned id)
{
    Primary* p;
    switch (id) {
    case 0x23e12222u:
        p = (Primary*)((char*)this - 8);
        return p ? (void*)((char*)this + 0x78) : 0;
    case 0x23e12232u:
        return (void*)((char*)this - 8);
    }
    if (id == 0x23e12220u) {
        p = (Primary*)((char*)this - 8);
        return p ? (void*)this : 0;
    }
    if (id == 0x23e12230u)
        return (void*)((char*)this - 8);
    if (id == 0xee3f516eu) {
        p = (Primary*)((char*)this - 8);
        return p ? (void*)this : 0;
    }
    return 0;
}

// @ 0x0094e3a0
int ISocket::StreamRead(void* buf, int len, int flags)
{
    int r;
    if (len > 0) {
        r = recv(*(int*)((char*)this - 0x74), (char*)buf, len, flags);
        if (r < 0) {
            int err = WSAGetLastError();
            if (err != 0x274c)
                ((Primary*)((char*)this - 0x80))->DoError(err, 0);
            return -1;
        }
    } else {
        r = 0;
    }
    return r;
}

// @ 0x0094e3f0
int ISocket::StreamWrite(void const* buf, int len, int flags)
{
    int r;
    if (len > 0) {
        r = send(*(int*)((char*)this - 0x74), (char*)buf, len, flags);
        if (r < 0) {
            ((Primary*)((char*)this - 0x80))->DoError(WSAGetLastError(), 0);
            return -1;
        }
    } else {
        r = 0;
    }
    return r;
}

// @ 0x0094e440
bool ISocket::StartListen(int backlog)
{
    if (listen(*(int*)((char*)this - 0x74), backlog) != 0) {
        Error e(WSAGetLastError());
        *(Error*)((char*)this - 0x2c) = e;
        return false;
    }
    *(int*)((char*)this + 4) = 3;
    return true;
}

// @ 0x0094e4b0
bool ISocket::Connect(bool* ok, void* stream)
{
    Callback94 cb;
    cb.ctor();
    if (stream != 0) {
        cb.Set(&Fn0094d350, *(unsigned*)((char*)this - 0x74), 0);
        cb.SetProcessor(1);
        cb.SetStream(stream);
        cb.Schedule(1);
    }
    if (connect(*(int*)((char*)this - 0x74), (void*)((char*)this - 0x54), 0x10) != 0) {
        *ok = false;
        ((Primary*)((char*)this - 0x80))->DoError(WSAGetLastError(), 0);
        cb.dtor();
        return false;
    }
    *ok = true;
    *(int*)((char*)this + 4) = 2;
    cb.dtor();
    return true;
}

// @ 0x0094e560
unsigned ISocket::WaitForWrite()
{
    int s = *(int*)((char*)this - 0x74);
    if (s == -1)
        return 0;
    fd_set_t fds;
    timeval_t tv;
    fds.fd_array[0] = s;
    fds.fd_count = 1;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    if (select(1, &fds, 0, 0, &tv) != -1)
        return 2;
    ((Primary*)((char*)this - 0x80))->DoError(WSAGetLastError(), 0);
    return 0;
}

// @ 0x0094e5e0
bool ISocket::IsWaitingDataAvailableSub()
{
    return ((ISocket*)((char*)this - 0x78))->v25();
}

// @ 0x0094e5f0
bool ISocket::AcceptPeer(void* pSocket, bool& ok)
{
    Address address;
    address.sa_family = 0;
    unsigned sockId;
    bool r = v14(sockId, address, ok);
    if (r && ok) {
        ((PendingSocket*)pSocket)->DoAccepted(sockId, address, 2,
            *(int*)((char*)this - 0x38), *(int*)((char*)this - 0x34), *(int*)((char*)this - 0x30));
    }
    return r;
}

// @ 0x0094e650
bool ISocket::Accept(unsigned* sockId, Address* addr, bool* ok)
{
    int len = 0x1c;
    unsigned s = accept(*(int*)((char*)this - 0x74), addr, &len);
    *sockId = s;
    if (s == (unsigned)-1) {
        *ok = false;
        ((Primary*)((char*)this - 0x80))->DoError(WSAGetLastError(), 0);
        return false;
    }
    *ok = true;
    return true;
}

// @ 0x0094e6b0
bool ISocket::DoAccepted(unsigned const& id, Address const& addr, int cs, int family, int type, int protocol)
{
    *(unsigned*)((char*)this - 0x74) = id;
    *(Address*)((char*)this - 0x54) = addr;
    *(int*)((char*)this + 4) = cs;
    *(int*)((char*)this - 0x38) = family;
    *(int*)((char*)this - 0x34) = type;
    *(int*)((char*)this - 0x30) = protocol;
    return true;
}

// @ 0x0094e700
void ISocket::SetSocketId(unsigned const& id)
{
    mSocketId = id;
}

// @ 0x0094e710
bool ISocket::IsCreated()
{
    return mSocketId != (unsigned)-1;
}

// @ 0x0094e720
bool ISocket::GetAddress(Address& a)
{
    return v17(a, mSocketId);
}

// @ 0x0094e740
bool ISocket::GetPeerAddress(Address& a)
{
    return v20(a, mSocketId);
}

// @ 0x0094e770
void Socket_s0094_dbc0::Destroy()
{
    mpVtbl = (void*)0x143fbd8;
    mpISocketVtbl = (void*)0x143fb00;
    if (mSocketId != -1 && mbSaveSocket == 0)
        ((ISocket*)((char*)this + 8))->Fn0094d4b0();
    mpISocketVtbl = (void*)0x13eb938;
    mpVtbl = (void*)0x13fb19c;
}

// @ 0x0094e7b0
bool ISocket::GetAddress2(Address* addr, unsigned* sock)
{
    int len = 0x1c;
    if (getsockname(*sock, addr, &len) != 0) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    if ((g_sockAddrInit & 1) == 0) {
        g_sockAddrInit |= 1;
        g_sockLocalAddress.sa_family = 2;
        *(unsigned*)&g_sockLocalAddress.sa_data[2] = 0;
        *(unsigned short*)g_sockLocalAddress.sa_data = 0;
    } else if (*(unsigned*)&g_sockLocalAddress.sa_data[2] != 0) {
        goto done;
    }
    Sockets_GetCurrentMachineAddress((IPAddress*)&g_sockLocalAddress, 0);
done:
    *(unsigned*)&addr->sa_data[2] = *(unsigned*)&g_sockLocalAddress.sa_data[2];
    return true;
}

// @ 0x0094e850
SocketBase::SocketBase()
{
    mSocketId = -1;
    mPeerAddress.sa_family = 0;
    mnAddressFamily = 2;
    mnProtocol = 0;
    mnType = 1;
    mLastError.mErrorType = 0;
    mLastError.mErrorString[0] = 0;
    mpUserData = 0;
    mbInitialized = 0;
    mbBound = 0;
    mbSaveSocket = 0;
    mbNonBlocking = 0;
    memset(&mAddress, 0, sizeof(mAddress));
    mAddress.sa_family = (unsigned short)mnAddressFamily;
}

// @ 0x0094e8d0
void* Socket_s0094_dbc0::DestroyScalar(unsigned flags)
{
    mpVtbl = (void*)0x143fbd8;
    mpISocketVtbl = (void*)0x143fb00;
    if (mSocketId != -1 && mbSaveSocket == 0)
        ((ISocket*)((char*)this + 8))->Fn0094d4b0();
    mpISocketVtbl = (void*)0x13eb938;
    mpVtbl = (void*)0x13fb19c;
    if (flags & 1)
        operator_delete__(this);
    return this;
}

// @ 0x0094e920
DatagramSocketBase::DatagramSocketBase()
{
    mnAddressFamily = 2;
    mnType = 2;
    mnProtocol = 0;
}

// @ 0x0094e960
int ISocket::WriteToPeer(void const* buf, int len, int flags)
{
    return v07(buf, len, (Address const*)((char*)this - 0x54), flags);
}

// @ 0x0094e9a0
StreamSocketBase::StreamSocketBase()
{
    mConnectStatus = 0;
    mnProtocol = 0;
    mnAddressFamily = 2;
    mnType = 1;
}

// @ 0x0094ea80
int __fastcall RefCount_AddRef_M4(int* p)
{
    return _InterlockedIncrement((volatile long*)(p - 1));
}

// @ 0x0094ea90
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
