// Slice s0094bb50 -- EA::Sockets: IPAddress helpers, the sockets Manager
// (Winsock init/shutdown, RAS/manual-dialup) and the URL parsing routine.
// Module flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
#include <string.h>
#include <stdlib.h>
#include <new>

// ---------------------------------------------------------------------------
// Win32 / CRT imports (msvcr90, wsock32, ws2_32, advapi32, kernel32)
// ---------------------------------------------------------------------------
extern "C" {
__declspec(dllimport) unsigned long __stdcall inet_addr(const char* cp);          // wsock32!inet_addr
__declspec(dllimport) struct hostent* __stdcall gethostbyname(const char* name);  // wsock32!gethostbyname
__declspec(dllimport) int __stdcall WSAStartup(unsigned short wVersion, void* lpWSAData);
__declspec(dllimport) int __stdcall WSACleanup(void);
__declspec(dllimport) int __stdcall WSAGetLastError(void);
__declspec(dllimport) int __stdcall closesocket(unsigned int s);                  // wsock32!closesocket
__declspec(dllimport) unsigned int __stdcall WSASocketA(int af, int type, int protocol,
        void* lpProtocolInfo, unsigned int g, unsigned int dwFlags);              // ws2_32!WSASocketA
__declspec(dllimport) int __stdcall WSAIoctl(unsigned int s, unsigned long code,
        void* inBuf, unsigned long cbIn, void* outBuf, unsigned long cbOut,
        unsigned long* bytesReturned, void* overlapped, void* completionRoutine); // ws2_32!WSAIoctl

__declspec(dllimport) void* __stdcall LoadLibraryA(const char* name);             // kernel32
__declspec(dllimport) void* __stdcall GetProcAddress(void* mod, const char* name); // kernel32

__declspec(dllimport) long __stdcall RegOpenKeyExA(void* hKey, const char* sub, unsigned long opt,
        unsigned long sam, void** phkResult);                                     // advapi32
__declspec(dllimport) long __stdcall RegQueryValueExA(void* hKey, const char* name, unsigned long* res,
        unsigned long* type, unsigned char* data, unsigned long* cbData);         // advapi32
__declspec(dllimport) long __stdcall RegSetValueExA(void* hKey, const char* name, unsigned long res,
        unsigned long type, const unsigned char* data, unsigned long cbData);     // advapi32
__declspec(dllimport) long __stdcall RegCloseKey(void* hKey);                     // advapi32

__declspec(dllimport) long long __cdecl _time64(long long* timer);                // msvcr90
}

// external Spore helpers
void* __cdecl operator_new(unsigned int size, const char* pName, int a3, int a4,
                           const char* file, int line);                           // 0x00F473A0
void  __cdecl operator_delete__(void* p);                                         // 0x00F47380

struct hostent {
    char*  h_name;       // +0x00
    char** h_aliases;    // +0x04
    short  h_addrtype;   // +0x08
    short  h_length;     // +0x0a
    char** h_addr_list;  // +0x0c
};

struct IPAddress {
    int          mUnused;    // +0x00
    unsigned int mAddress;   // +0x04
};

struct WSAData {
    unsigned short wVersion;        // +0x000
    unsigned short wHighVersion;    // +0x002
    char szDescription[0x101];      // +0x004
    char szSystemStatus[0x81];      // +0x105
    unsigned short iMaxSockets;     // +0x186
    unsigned short iMaxUdpDg;       // +0x188
    void* lpVendorInfo;             // +0x18c
};

typedef void (__cdecl* DialupCallback)(unsigned int, void*, int);

struct RasDialParams {
    unsigned long dwSize;            // +0x000
    char szEntryName[0x101];         // +0x004
    char szPhoneNumber[0x81];        // +0x105
    char szCallbackNumber[0x81];     // +0x186
    char szUserName[0x101];          // +0x207
    char szPassword[0x101];          // +0x308
    char szDomain[0x13];             // +0x409
    unsigned long mTail0;            // +0x41c
    unsigned long mTail1;            // +0x420
};
typedef unsigned long (__stdcall* RasGetEntryDialParams_t)(const char*, RasDialParams*, unsigned long*);

struct RasConnStatus {
    unsigned long dwSize;      // +0x000
    unsigned long dwStatus;    // +0x004
    char          pad[0x118];  // +0x008
};
typedef unsigned long (__stdcall* RasDial_t)(void*, const char*, RasDialParams*, unsigned long, void*, void**);
typedef unsigned long (__stdcall* RasGetConnectStatus_t)(void*, void*);
typedef unsigned long (__stdcall* RasHangUp_t)(void*);

void __stdcall Sockets_RasDialFunc(unsigned int unMsg, int rascs, unsigned int dwError);

struct Manager {
    void*          mpVtbl;                        // +0x000
    int            mnRefCount;                    // +0x004
    int            mnLastError;                   // +0x008
    unsigned char  mbInitialized;                 // +0x00c
    unsigned char  mbDriverAvailable;             // +0x00d
    WSAData        mWSAData;                      // +0x010
    void*          mhRASAPI32;                    // +0x1a0
    void*          mhRASConn;                     // +0x1a4
    void*          mpRasEnumConnections;          // +0x1a8
    void*          mpRasEnumEntries;              // +0x1ac
    void*          mpRasGetProjectionInfo;        // +0x1b0
    void*          mpRasGetEntryDialParams;       // +0x1b4
    void*          mpRasDial;                     // +0x1b8
    void*          mpRasGetConnectStatus;         // +0x1bc
    void*          mpRasHangUp;                   // +0x1c0
    unsigned char  mbManualDialupRequired;        // +0x1c4
    unsigned char  mbManualDialupBusy;            // +0x1c5
    DialupCallback mpDialupCallbackFunction;      // +0x1c8

    Manager();                                    // 0x0094C260
    unsigned int GetMaxSockets();              // 0x0094C380
    bool Init();                                  // 0x0094C3C0
    bool Shutdown();                              // 0x0094C420
    bool IsNetworkConnected(int p, char q);       // 0x0094C450
    void* CreateSocket(int type);                 // 0x0094C490
    bool GetAutoDialEnabled();                    // 0x0094C510
    bool SetAutoDialEnabled(unsigned char on);    // 0x0094C580
    bool GetManualDialupNameAndPassword(char* a, char* b, char* c, unsigned n);  // 0x0094C620
    bool DoManualDialup(DialupCallback cb, char* entry, char* user, char* pass, unsigned len);  // 0x0094C7A0
    bool CancelManualDialup();                    // 0x0094C9D0
    bool SetManualDialupResult(int r);            // 0x0094CA60
};

Manager* spManagerForDial;   // 0x0166AA74

// socksv5 socket subclasses (constructed offsite); we only need the ctor + vtbl@8
struct DatagramSocket {
    char  mPad08[8];
    void* mpVtbl08;      // +8
    DatagramSocket();                    // 0x0094E920
};
struct StreamSocket {
    char  mPad08[8];
    void* mpVtbl08;      // +8
    StreamSocket();                      // 0x0094E9A0
};

// ---------------------------------------------------------------------------
// @ 0x0094C190  inet_addr validity test
// ---------------------------------------------------------------------------
bool Sockets_IPIsValid(const char* cp) {
    return inet_addr(cp) != (unsigned long)-1;
}

// ---------------------------------------------------------------------------
// @ 0x0094C1B0  EA::Sockets::IPAddress::LookupName
// ---------------------------------------------------------------------------
unsigned int __declspec(noinline) Sockets_LookupName(const char* name, unsigned int timeout) {
    (void)timeout;
    hostent* h = gethostbyname(name);
    if (h != 0)
        return *(unsigned int*)h->h_addr_list[0];
    return (unsigned int)-1;
}

// ---------------------------------------------------------------------------
// @ 0x0094C1D0  EA::Sockets::IPAddress::GetCurrentMachineAddress
// ---------------------------------------------------------------------------
bool __cdecl Sockets_GetCurrentMachineAddress(IPAddress* out, unsigned int index) {
    unsigned char outBuf[0x5f0];
    unsigned long bytes;
    bool ok = false;
    unsigned int s = WSASocketA(2, 2, 0, 0, 0, 0);
    if (s != (unsigned int)-1) {
        if (WSAIoctl(s, 0x4004747f, 0, 0, outBuf, 0x5f0, &bytes, 0, 0) != -1) {
            if (index < bytes / 0x4c) {
                out->mAddress = ((unsigned int*)outBuf)[index * 0x13 + 2];
                ok = true;
            }
        }
        closesocket(s);
    }
    return ok;
}

// ---------------------------------------------------------------------------
// @ 0x0094C130  numeric-or-dotted address parser
// ---------------------------------------------------------------------------
unsigned int Sockets_ParseAddress(char* s) {
    char c = *s;
    char* p = s;
    while (c != 0) {
        if (c == '.')
            return inet_addr(s);
        if (c < '0')
            return (unsigned int)-1;
        if (c > '9')
            return (unsigned int)-1;
        c = p[1];
        ++p;
    }
    unsigned int v = (unsigned int)atoi(s);
    return ((v & 0x00ff0000u | v >> 0x10) >> 8) | ((v & 0x0000ff00u | v << 0x10) << 8);
}

// ---------------------------------------------------------------------------
// @ 0x0094C380  Manager::GetMaxSockets
// ---------------------------------------------------------------------------
unsigned int Manager::GetMaxSockets() {
    return mWSAData.iMaxSockets;
}
// ---------------------------------------------------------------------------
// @ 0x0094C3C0  Manager::Init
// ---------------------------------------------------------------------------
bool Manager::Init() {
    if (!mbInitialized) {
        mbInitialized = true;
        mnLastError = 0;
        int r = WSAStartup(2, &mWSAData);
        mnLastError = r;
        if (r == 0) {
            mWSAData.iMaxSockets = 0x7fff;
            mWSAData.iMaxUdpDg = 0x7fff;
        } else {
            r = WSAStartup(0x101, &mWSAData);
            mnLastError = r;
            if (r != 0) {
                mbInitialized = false;
                return false;
            }
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x0094C420  Manager::Shutdown
// ---------------------------------------------------------------------------
bool Manager::Shutdown() {
    if (mbInitialized) {
        mbInitialized = false;
        if (WSACleanup() != 0) {
            mnLastError = WSAGetLastError();
            return false;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x0094C450  Manager::IsNetworkConnected
// ---------------------------------------------------------------------------
bool Manager::IsNetworkConnected(int p, char q) {
    (void)p;
    char c = ((char(__thiscall*)(Manager*))((*(void***)this)[7]))(this);
    if (c != 0 && q == 0)
        ((void(__thiscall*)(Manager*, int))((*(void***)this)[8]))(this, 0);
    return Sockets_LookupName("www.ea.com", 10000) != 0;
}

// ---------------------------------------------------------------------------
// @ 0x0094C490  Manager::CreateSocket
// ---------------------------------------------------------------------------
void* Manager::CreateSocket(int type) {
    void* s;
    if (type == 2) {
        s = operator_new(0x84, "UTF/Sockets", 0, 0, 0, 0);
        if (s == 0)
            return 0;
        new (s) DatagramSocket();
    } else if (type == 3) {
        s = operator_new(0x88, "UTF/Sockets", 0, 0, 0, 0);
        if (s == 0)
            return 0;
        new (s) StreamSocket();
    } else {
        return 0;
    }
    if (s != 0)
        ((void(__thiscall*)(void*))((*(void***)((char*)s + 8))[0]))((char*)s + 8);
    return s;
}

// ---------------------------------------------------------------------------
// @ 0x0094C510  Manager::GetAutoDialEnabled
// ---------------------------------------------------------------------------
bool Manager::GetAutoDialEnabled() {
    bool result = false;
    void* hKey;
    if (RegOpenKeyExA((void*)0x80000001,
            "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings",
            0, 0xf003f, &hKey) == 0) {
        unsigned int v = 0;
        unsigned long sz = 4;
        if (RegQueryValueExA(hKey, "EnableAutodial", 0, 0, (unsigned char*)&v, &sz) == 0)
            result = (v != 0);
        RegCloseKey(hKey);
    }
    return result;
}

// ---------------------------------------------------------------------------
// @ 0x0094C580  Manager::SetAutoDialEnabled
// ---------------------------------------------------------------------------
bool Manager::SetAutoDialEnabled(unsigned char on) {
    void* hKey;
    bool result = false;
    if (RegOpenKeyExA((void*)0x80000001,
            "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings",
            0, 0xf003f, &hKey) == 0) {
        unsigned int v = 0;
        unsigned long sz = 4;
        if (RegQueryValueExA(hKey, "EnableAutodial", 0, 0, (unsigned char*)&v, &sz) != 0 || v != on) {
            v = (on != 0);
            if (RegSetValueExA(hKey, "EnableAutodial", 0, 3, (unsigned char*)&v, 4) != 0)
                goto done;
        }
        result = true;
    done:
        RegCloseKey(hKey);
    }
    return result;
}

// ---------------------------------------------------------------------------
// @ 0x0094C620  Manager::GetManualDialupNameAndPassword
// ---------------------------------------------------------------------------
bool Manager::GetManualDialupNameAndPassword(char* name, char* user, char* pass, unsigned len) {
    if (len != 0) {
        *user = 0;
        *pass = 0;
        if (mpRasGetEntryDialParams != 0) {
            unsigned long flag = 0;
            RasDialParams dp;
            dp.dwSize = sizeof(RasDialParams);
            dp.szEntryName[0] = 0;
            dp.szPhoneNumber[0] = 0;
            dp.szCallbackNumber[0] = 0;
            dp.szUserName[0] = 0;
            dp.szPassword[0] = 0;
            dp.szDomain[0] = 0;
            dp.mTail0 = 0;
            dp.mTail1 = 0;
            strncpy(dp.szEntryName, name, 0x100);
            dp.szEntryName[0xff] = 0;
            if (((RasGetEntryDialParams_t)mpRasGetEntryDialParams)(0, &dp, &flag) == 0) {
                strncpy(user, dp.szUserName, len);
                user[len - 1] = 0;
                strncpy(pass, dp.szPassword, len);
                pass[len - 1] = 0;
                return true;
            }
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0094C7A0  Manager::DoManualDialup
// ---------------------------------------------------------------------------
bool Manager::DoManualDialup(DialupCallback cb, char* entry, char* user, char* pass, unsigned len) {
    if (mbManualDialupBusy == 0) {
        if (((bool(__thiscall*)(Manager*, int, int))((*(void***)this)[5]))(this, 0, 0) == 0) {
            if (mpRasDial != 0 && mpRasGetConnectStatus != 0) {
                unsigned long flag = 0;
                mbManualDialupBusy = true;
                spManagerForDial = this;
                if (cb != 0)
                    cb(0x15783920, this, 1);
                if (mpDialupCallbackFunction != 0)
                    mpDialupCallbackFunction(0x15783923, this, 1);
                mpDialupCallbackFunction = cb;
                RasDialParams dp;
                dp.dwSize = sizeof(RasDialParams);
                dp.szEntryName[0] = 0;
                dp.szPhoneNumber[0] = 0;
                dp.szCallbackNumber[0] = 0;
                dp.szUserName[0] = 0;
                dp.szPassword[0] = 0;
                dp.szDomain[0] = 0;
                dp.mTail0 = 0;
                dp.mTail1 = 0;
                if (entry != 0 && *entry != 0) {
                    strncpy(dp.szEntryName, entry, 0x100);
                    dp.szEntryName[0xff] = 0;
                }
                ((RasGetEntryDialParams_t)mpRasGetEntryDialParams)(0, &dp, &flag);
                if (user != 0 && *user != 0) {
                    strncpy(dp.szUserName, user, len);
                    dp.szUserName[len - 1] = 0;
                }
                if (pass != 0 && *pass != 0) {
                    strncpy(dp.szPassword, pass, len);
                    dp.szPassword[len - 1] = 0;
                }
                mhRASConn = 0;
                if (cb != 0) {
                    unsigned long r = ((RasDial_t)mpRasDial)(0, 0, &dp, 0, (void*)Sockets_RasDialFunc, &mhRASConn);
                    if (r != 0) {
                        if (mhRASConn != 0)
                            ((RasHangUp_t)mpRasHangUp)(mhRASConn);
                        mhRASConn = 0;
                    }
                    return r == 0;
                }
                unsigned long r = ((RasDial_t)mpRasDial)(0, 0, &dp, 0, 0, &mhRASConn);
                if (r == 0 && mhRASConn != 0) {
                    RasConnStatus st;
                    st.dwSize = 0x120;
                    return (((RasGetConnectStatus_t)mpRasGetConnectStatus)(mhRASConn, &st) == 0) && (st.dwStatus == 0x2000);
                }
                if (mhRASConn != 0)
                    ((RasHangUp_t)mpRasHangUp)(mhRASConn);
                mhRASConn = 0;
            }
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0094C730  EA::Sockets::RasDialFunc
// ---------------------------------------------------------------------------
void __stdcall Sockets_RasDialFunc(unsigned int unMsg, int rascs, unsigned int dwError) {
    (void)dwError;
    if (unMsg != 0xcccd)
        return;
    if (rascs == 3) {
        Manager* m = spManagerForDial;
        if (m != 0) {
            DialupCallback cb = m->mpDialupCallbackFunction;
            if (cb != 0)
                cb(0x15783921, m, 1);
        }
    } else if (rascs == 0x2000 || rascs == 0x2001) {
        Manager* m = spManagerForDial;
        if (m != 0) {
            typedef void (__thiscall* Vtfn)(void*, int);
            Vtfn fn = *(Vtfn*)((char*)*(void**)m + 0x3c);
            fn(m, rascs == 0x2000);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x0094CA60  Manager::SetManualDialupResult
// ---------------------------------------------------------------------------
bool Manager::SetManualDialupResult(int r) {
    if (mbManualDialupBusy) {
        if (mpDialupCallbackFunction != 0) {
            mpDialupCallbackFunction(0x15783922, this, r);
            mpDialupCallbackFunction(0x15783923, this, 1);
            mpDialupCallbackFunction = 0;
        }
        mbManualDialupBusy = false;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0094C9D0  Manager::CancelManualDialup
// ---------------------------------------------------------------------------
bool Manager::CancelManualDialup() {
    if (mbManualDialupBusy) {
        if (mhRASConn != 0) {
            long long t = _time64(0) + 3;
            long long now;
            do {
                now = _time64(0);
            } while (now < t);
            mhRASConn = 0;
        }
        if (mpDialupCallbackFunction != 0) {
            mpDialupCallbackFunction(0x15783923, this, 1);
            mpDialupCallbackFunction = 0;
        }
        mhRASConn = 0;
        mbManualDialupBusy = false;
        return true;
    }
    mhRASConn = 0;
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0094C260  Manager::Manager  (ctor)
// ---------------------------------------------------------------------------
Manager::Manager() {
    mpVtbl = (void*)0x143f918;
    mnRefCount = 0;
    mnLastError = 0;
    mbInitialized = false;
    mbDriverAvailable = false;
    memset(&mWSAData, 0, 0x190);
    mhRASAPI32 = 0;
    mhRASConn = 0;
    mpRasEnumConnections = 0;
    mpRasEnumEntries = 0;
    mpRasGetProjectionInfo = 0;
    mpRasGetEntryDialParams = 0;
    mpRasDial = 0;
    mpRasGetConnectStatus = 0;
    mpRasHangUp = 0;
    mbManualDialupRequired = false;
    mbManualDialupBusy = false;
    mpDialupCallbackFunction = 0;
    void* h = LoadLibraryA("rasapi32.dll");
    mhRASAPI32 = h;
    if (h != 0) {
        mpRasEnumConnections = GetProcAddress(h, "RasEnumConnectionsA");
        mpRasEnumEntries = GetProcAddress((void*)mhRASAPI32, "RasEnumEntriesA");
        mpRasGetProjectionInfo = GetProcAddress((void*)mhRASAPI32, "RasGetProjectionInfoA");
        mpRasGetEntryDialParams = GetProcAddress((void*)mhRASAPI32, "RasGetEntryDialParamsA");
        mpRasDial = GetProcAddress((void*)mhRASAPI32, "RasDialA");
        mpRasGetConnectStatus = GetProcAddress((void*)mhRASAPI32, "RasGetConnectStatusA");
        mpRasHangUp = GetProcAddress((void*)mhRASAPI32, "RasHangUpA");
    }
}

// ---------------------------------------------------------------------------
// EASTL string (16-byte layout) and EA::Internet::URL
// ---------------------------------------------------------------------------
namespace eastl {

struct allocator { int mAlloc; };

template <class T>
struct basic_string {
    T* mpBegin;                 // +0x00
    T* mpEnd;                   // +0x04
    T* mpCapacity;              // +0x08
    allocator mAllocator;       // +0x0c

    void clear() { if (mpBegin != mpEnd) { *mpBegin = 0; mpEnd = mpBegin; } }
    unsigned int length() const { return (unsigned int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }

    void AssignRange(const T* first, const T* last);  // 0x00454cb0
    void AssignCStr(const T* p);                      // 0x006a4380
    void Append(const T* first, const T* last);       // 0x00455d60
    void CopyFrom(const basic_string& o);             // 0x0057cb10
    unsigned int RFind(T c, unsigned int pos) const;  // 0x00609f40
    void Erase(unsigned int pos, unsigned int n);     // 0x0061e200
    void Destroy();                                   // 0x00530670
};

typedef basic_string<char> string;

}  // namespace eastl

struct URL {
    bool          mbStrictConformance;    // +0x00
    int           mnMaxComponentLength;   // +0x04
    bool          mbParsed;               // +0x08
    int           mURLType;               // +0x0c
    eastl::string msURL;                  // +0x10
    eastl::string msComponent[9];         // +0x20

    void Construct(const char* p);                 // 0x0094a560
    void Destroy();                                // 0x0060a100
    URL& Assign(const URL& o);                     // 0x0094a630
    void SetComponent(int index, const char* p);   // 0x0094a6f0
    void SetPort(unsigned int port);               // 0x0094a750
    eastl::string* GetComponent(int index);        // 0x0094baf0
    bool ParseURL(eastl::string* pstr);            // 0x0094b760
    void Finalize();                               // 0x0094b8e0
    static void CanonicalizePath(const char* pszPath, eastl::string* pstr);  // 0x0094a7a0

    bool FUN_0094bb50(char* a, char* b);
};

// Inlined eastl `assign(const char*)` SSO build reached four times from the body.
static void EaStrAssign(eastl::string& s, const char* p) {
    unsigned int n = (unsigned int)strlen(p);
    unsigned int size = n + 1;
    if (size < 2) {
        s.mpBegin = (char*)0x01667bac;
        s.mpCapacity = (char*)0x01667bad;
    } else {
        s.mpBegin = (char*)operator_new(size, "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        s.mpCapacity = s.mpBegin + size;
    }
    memcpy(s.mpBegin, p, n);
    s.mpEnd = s.mpBegin + n;
    *s.mpEnd = 0;
}

static void EaStrFree(eastl::string& s) {
    if ((int)(s.mpCapacity - s.mpBegin) > 1 && s.mpBegin != 0)
        operator_delete__(s.mpBegin);
}

// ---------------------------------------------------------------------------
// @ 0x0094bb50
// ---------------------------------------------------------------------------
bool URL::FUN_0094bb50(char* a, char* b) {
    mbParsed = false;            // +0x08
    mURLType = 0;                // +0x0c
    msURL.clear();               // +0x10
    msComponent[0].clear();      // +0x20
    msComponent[2].clear();      // +0x40
    msComponent[3].clear();      // +0x50
    msComponent[4].clear();      // +0x60
    msComponent[5].clear();      // +0x70

    // b is null or empty: parse `a` straight into this object.
    if (b == 0 || *b == 0) {
        eastl::string tmp;
        EaStrAssign(tmp, a);
        if (a != 0)
            msURL.AssignRange(a, a + strlen(a));
        else
            msURL.clear();
        bool r = ParseURL(&tmp);
        EaStrFree(tmp);
        return r;
    }

    // a is null or empty: keep `b` verbatim.
    if (a == 0 || *a == 0) {
        msURL.AssignRange(b, b + strlen(b));
        return true;
    }

    // Both present: parse each side, then resolve the relative URL.
    URL urlA;
    URL urlB;

    eastl::string ta;
    EaStrAssign(ta, a);
    urlA.Construct(a);
    urlA.ParseURL(&ta);
    urlA.msURL.clear();

    eastl::string tb;
    EaStrAssign(tb, b);
    urlB.Construct(b);
    urlB.ParseURL(&tb);

    if (!urlA.GetComponent(0)->empty()) {
        msURL.AssignCStr(a);
    } else {
        urlA.SetComponent(0, urlB.GetComponent(0)->mpBegin);

        if (urlA.GetComponent(3)->empty())
            urlA.SetComponent(3, urlB.GetComponent(3)->mpBegin);
        if (urlA.GetComponent(1)->empty())
            urlA.SetComponent(1, urlB.GetComponent(1)->mpBegin);
        if (urlA.GetComponent(2)->empty())
            urlA.SetComponent(2, urlB.GetComponent(2)->mpBegin);

        unsigned long port = strtoul(urlA.msComponent[4].mpBegin, 0, 10);
        if (port == 0) {
            port = strtoul(urlB.msComponent[4].mpBegin, 0, 10);
            urlA.SetPort((unsigned int)port);
        }

        eastl::string* c5 = urlA.GetComponent(5);
        if ((int)(c5->mpEnd - c5->mpBegin) >= 1) {
            if (*c5->mpBegin != '/') {
                eastl::string path;
                path.CopyFrom(*urlB.GetComponent(5));
                unsigned int pos = path.RFind('/', 0xffffffff);
                unsigned int plen = path.length();
                if (pos < plen)
                    path.Erase(pos + 1, (plen - pos) - 1);
                eastl::string* ac5 = urlA.GetComponent(5);
                path.Append(ac5->mpBegin, ac5->mpEnd);
                URL::CanonicalizePath(path.mpBegin, &path);
                urlA.SetComponent(5, path.mpBegin);
                path.Destroy();
            }
        } else {
            urlA.SetComponent(5, urlB.GetComponent(5)->mpBegin);
            if (urlA.GetComponent(6)->empty()) {
                urlA.SetComponent(6, urlB.GetComponent(6)->mpBegin);
                if (urlA.GetComponent(7)->empty()) {
                    urlA.SetComponent(7, urlB.GetComponent(7)->mpBegin);
                    if (urlA.GetComponent(8)->empty())
                        urlA.SetComponent(8, urlB.GetComponent(8)->mpBegin);
                }
            }
        }

        urlA.Finalize();
        Assign(urlA);
    }

    urlB.Destroy();
    EaStrFree(tb);
    urlA.Destroy();
    EaStrFree(ta);
    return true;
}
