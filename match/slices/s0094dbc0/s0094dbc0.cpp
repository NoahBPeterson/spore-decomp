// Slice s0094dbc0 -- EA::Sockets: ISocket option accessors, socket interface
// dispatch (AsInterface / GetAddress), Datagram/Stream socket read/write/connect
// and the Socket base ctor/dtor.
// Object UTFSpore_Win32/Socket_imp.obj
// Module flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"
#include <string.h>
#include <intrin.h>

extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

// ---------------------------------------------------------------------------
// wsock32 imports (stdcall: callee pops)
// ---------------------------------------------------------------------------
extern "C" {
__declspec(dllimport) int __stdcall getsockopt(unsigned s, int level, int optname, char* optval, int* optlen);
__declspec(dllimport) int __stdcall setsockopt(unsigned s, int level, int optname, const char* optval, int optlen);
__declspec(dllimport) int __stdcall WSAGetLastError(void);
__declspec(dllimport) unsigned int __stdcall accept(unsigned s, void* addr, int* addrlen);
__declspec(dllimport) int __stdcall connect(unsigned s, const void* name, int namelen);
__declspec(dllimport) int __stdcall send(unsigned s, const char* buf, int len, int flags);
__declspec(dllimport) int __stdcall sendto(unsigned s, const char* buf, int len, int flags, const void* to, int tolen);
__declspec(dllimport) int __stdcall recv(unsigned s, char* buf, int len, int flags);
__declspec(dllimport) int __stdcall recvfrom(unsigned s, char* buf, int len, int flags, void* from, int* fromlen);
__declspec(dllimport) int __stdcall listen(unsigned s, int backlog);
__declspec(dllimport) int __stdcall select(int nfds, void* readfds, void* writefds, void* exceptfds, const void* timeout);
__declspec(dllimport) int __stdcall getsockname(unsigned s, void* name, int* namelen);
__declspec(dllimport) int __stdcall shutdown(unsigned s, int how);
}

void __cdecl operator_delete__(void* p) throw();   // 0x00F47380

// ---------------------------------------------------------------------------
// POD helpers
// ---------------------------------------------------------------------------
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

extern "C" int     g_sockAddrInit;                          // 0x0166AAA4
extern "C" Address g_sockLocalAddress;                      // 0x0166AA88
bool __cdecl Sockets_GetCurrentMachineAddress(IPAddress* out, unsigned int index);  // 0x0094C1D0

void Fn0094d350();                                          // 0x0094D350

// ---------------------------------------------------------------------------
// Callback94 (EA::CallbackSystem::Callback) -- opaque 0x24-byte object
// ---------------------------------------------------------------------------
struct Callback94 {
    char mData[0x24];
    void ctor();                                        // 0x00929E00
    void dtor();                                        // 0x00929D50
    bool Set(void (*fn)(), unsigned id, int a);         // 0x00929DA0
    bool SetProcessor(int p);                           // 0x0092A7D0
    bool SetStream(void* stream);                       // 0x00929BC0
    bool Schedule(int s);                               // 0x0092A7A0
};

// ---------------------------------------------------------------------------
// Primary object (obj+0): slot1 = DoError
// ---------------------------------------------------------------------------
struct Primary {
    virtual void v00();
    virtual void DoError(int err, char const* msg);
};

struct PendingSocket;

// ---------------------------------------------------------------------------
// ISocket interface (obj+8); the same 26-slot layout is reused for the
// Datagram/Stream sub-object view at obj+0x80.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// Socket base (obj+0)
// ---------------------------------------------------------------------------
struct Socket {
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

// ---------------------------------------------------------------------------
// Multiple-inheritance model of the same object, so the compiler emits the
// ctor vptr-store interleaving seen in the original object file:
//   Socket        : EA::COM::RefCountTemplate<AtomicInt> (+0), ISocket (+8)
//   DatagramSocket: Socket, IDatagramSocket              (+0x80)
//   StreamSocket  : Socket, IStreamSocket                (+0x80)
// ---------------------------------------------------------------------------
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
    virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
    virtual void b04(); virtual void b05(); virtual void b06(); virtual void b07();
    virtual void b08(); virtual void b09(); virtual void b10(); virtual void b11();
    virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15();
    virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19();
    virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23();
    virtual void b24(); virtual void b25();
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
    virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
    virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
    virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
};

struct DatagramSocketBase : SocketBase, IDgramBase {
    DatagramSocketBase();                // 0x0094E920
};

struct IStrBase {                        // StreamSocket's second base (obj+0x80)
    virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03();
    virtual void t04(); virtual void t05(); virtual void t06(); virtual void t07();
    virtual void t08(); virtual void t09(); virtual void t10(); virtual void t11();
};

struct StreamSocketBase : SocketBase, IStrBase {
    int mConnectStatus;                  // 0x84
    StreamSocketBase();                  // 0x0094E9A0
};

// ===========================================================================
// Option accessors
// ===========================================================================

// @ 0x0094DBC0
bool ISocket::GetRouteOption(bool* out) {
    int val; int len = 4;
    if (getsockopt(mSocketId, 0xffff, 0x10, (char*)&val, &len)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    *out = (val == 0);
    return true;
}

// @ 0x0094DC30
bool ISocket::SetRouteOption(bool b) {
    int v = (b == 0);
    if (setsockopt(mSocketId, 0xffff, 0x10, (char*)&v, 4)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094DCF0
bool ISocket::SetKeepAliveOption(bool b) {
    int v = (b != 0);
    if (setsockopt(mSocketId, 0xffff, 8, (char*)&v, 4)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094DD40
bool ISocket::GetReceiveBufferOption(int* out) {
    int len = 4;
    if (getsockopt(mSocketId, 0xffff, 0x1002, (char*)out, &len)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094DDA0
bool ISocket::SetReceiveBufferOption(int size) {
    if (setsockopt(mSocketId, 0xffff, 0x1002, (char*)&size, 4)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094DDF0
bool ISocket::GetSendBufferOption(int* out) {
    int len = 4;
    if (getsockopt(mSocketId, 0xffff, 0x1001, (char*)out, &len)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094DE50
bool ISocket::SetSendBufferOption(int size) {
    if (setsockopt(mSocketId, 0xffff, 0x1001, (char*)&size, 4)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094DF10
bool ISocket::SetReuseAddressOption(bool b) {
    int v = (b != 0);
    if (setsockopt(mSocketId, 0xffff, 4, (char*)&v, 4)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094DFD0
bool ISocket::SetSendDelayOption(bool b) {
    int v = b;
    if (setsockopt(mSocketId, 6, 1, (char*)&v, 4)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094E020
bool ISocket::GetSendTimeoutOption(int* out) {
    int len = 4;
    if (getsockopt(mSocketId, 0xffff, 0x1005, (char*)out, &len)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094E080
bool ISocket::SetSendTimeoutOption(int size) {
    if (setsockopt(mSocketId, 0xffff, 0x1005, (char*)&size, 4)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094E0D0
bool ISocket::GetReceiveTimeoutOption(int* out) {
    int len = 4;
    if (getsockopt(mSocketId, 0xffff, 0x1006, (char*)out, &len)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094E130
bool ISocket::SetReceiveTimeoutOption(int size) {
    if (setsockopt(mSocketId, 0xffff, 0x1006, (char*)&size, 4)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// @ 0x0094E1F0
bool ISocket::SetOOBOption(bool b) {
    int v = b;
    if (setsockopt(mSocketId, 0xffff, 0x100, (char*)&v, 4)) {
        ((Primary*)((char*)this - 8))->DoError(WSAGetLastError(), 0);
        return false;
    }
    return true;
}

// ===========================================================================
// Interface dispatch
// ===========================================================================

// @ 0x0094E240
void* ISocket::AsInterfaceDatagram(unsigned id) {
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

// @ 0x0094E340
void* ISocket::AsInterfaceStream(unsigned id) {
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

// ===========================================================================
// Datagram / Stream IO (this = obj+0x80)
// ===========================================================================

// @ 0x0094E290
int ISocket::DatagramRead(void* buf, int len, Address* from, int flags) {
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

// @ 0x0094E2F0
int ISocket::DatagramWrite(void const* buf, int len, Address const* to, int flags) {
    if (len > 0) {
        int r = sendto(*(int*)((char*)this - 0x74), (char*)buf, len, 0, to, 0x10);
        if (r < 0)
            ((Primary*)((char*)this - 0x80))->DoError(WSAGetLastError(), 0);
        return r;
    }
    return 0;
}

// @ 0x0094E3A0
int ISocket::StreamRead(void* buf, int len, int flags) {
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

// @ 0x0094E3F0
int ISocket::StreamWrite(void const* buf, int len, int flags) {
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

// @ 0x0094E440
bool ISocket::StartListen(int backlog) {
    if (listen(*(int*)((char*)this - 0x74), backlog) != 0) {
        Error e(WSAGetLastError());
        *(Error*)((char*)this - 0x2c) = e;
        return false;
    }
    *(int*)((char*)this + 4) = 3;
    return true;
}

// @ 0x0094E4A0
bool ISocket::Close() {
    ((ISocket*)((char*)this - 0x78))->v13();
    return true;
}

// @ 0x0094E4B0
bool ISocket::Connect(bool* ok, void* stream) {
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

// @ 0x0094E560
unsigned ISocket::WaitForWrite() {
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

// @ 0x0094E5E0
bool ISocket::IsWaitingDataAvailableSub() {
    return ((ISocket*)((char*)this - 0x78))->v25();
}

// @ 0x0094E5F0
bool ISocket::AcceptPeer(void* pSocket, bool& ok) {
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

// @ 0x0094E650
bool ISocket::Accept(unsigned* sockId, Address* addr, bool* ok) {
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

// @ 0x0094E6B0
bool ISocket::DoAccepted(unsigned const& id, Address const& addr, int cs,
                         int family, int type, int protocol) {
    *(unsigned*)((char*)this - 0x74) = id;
    *(Address*)((char*)this - 0x54) = addr;
    *(int*)((char*)this + 4) = cs;
    *(int*)((char*)this - 0x38) = family;
    *(int*)((char*)this - 0x34) = type;
    *(int*)((char*)this - 0x30) = protocol;
    return true;
}

// @ 0x0094E700
void ISocket::SetSocketId(unsigned const& id) {
    mSocketId = id;
}

// @ 0x0094E710
bool ISocket::IsCreated() {
    return mSocketId != (unsigned)-1;
}

// @ 0x0094E720
bool ISocket::GetAddress(Address& a) {
    return v17(a, mSocketId);
}

// @ 0x0094E740
bool ISocket::GetPeerAddress(Address& a) {
    return v20(a, mSocketId);
}

// @ 0x0094E7B0
bool ISocket::GetAddress2(Address* addr, unsigned* sock) {
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

// @ 0x0094E960
int ISocket::WriteToPeer(void const* buf, int len, int flags) {
    return v07(buf, len, (Address const*)((char*)this - 0x54), flags);
}

// @ 0x0094EA10
bool ISocket::Shutdown(int mode) {
    char* self = (char*)this;
    int* pStatus = (int*)(self + 0x7c);
    *pStatus = 4;
    int s = *(int*)(self + 4);
    if (s != -1) {
        if (shutdown(s, mode) != 0) {
            ((Primary*)(self - 8))->DoError(WSAGetLastError(), 0);
            return false;
        }
    }
    return true;
}

// ===========================================================================
// Socket base
// ===========================================================================

// @ 0x0094E850
SocketBase::SocketBase() {
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

// @ 0x0094E770
void Socket::Destroy() {
    mpVtbl = (void*)0x143fbd8;
    mpISocketVtbl = (void*)0x143fb00;
    if (mSocketId != -1 && mbSaveSocket == 0)
        ((ISocket*)((char*)this + 8))->Fn0094d4b0();
    mpISocketVtbl = (void*)0x13eb938;
    mpVtbl = (void*)0x13fb19c;
}

// @ 0x0094E8D0
void* Socket::DestroyScalar(unsigned flags) {
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

// @ 0x0094E920
DatagramSocketBase::DatagramSocketBase() {
    mnAddressFamily = 2;
    mnType = 2;
    mnProtocol = 0;
}

// @ 0x0094E9A0
StreamSocketBase::StreamSocketBase() {
    mConnectStatus = 0;
    mnProtocol = 0;
    mnAddressFamily = 2;
    mnType = 1;
}
