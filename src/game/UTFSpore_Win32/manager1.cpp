// src/game/UTFSpore_Win32/manager1.cpp -- migrated from slice(s) s0094bb50 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/manager1.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Sockets/Manager.h"
#include "EA/Sockets/DatagramSocket.h"
#include "EA/Sockets/IPAddress.h"
#include "EA/Sockets/StreamSocket.h"
#include "EA/Internet/URL.h"
#include "WSAData.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) void* __stdcall LoadLibraryA(const char* name);             // kernel32
extern "C" __declspec(dllimport) void* __stdcall GetProcAddress(void* mod, const char* name); // kernel32
extern "C" __declspec(dllimport) long long __cdecl _time64(long long* timer);                // msvcr90
#include <string.h>
#include <stdlib.h>
#include <new>

// ---- items of slice s0094bb50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void* __stdcall LoadLibraryA(const char* name);             // kernel32
extern "C" __declspec(dllimport) void* __stdcall GetProcAddress(void* mod, const char* name); // kernel32
extern "C" __declspec(dllimport) long long __cdecl _time64(long long* timer);                // msvcr90
void* __cdecl operator_new(unsigned int size, const char* pName, int a3, int a4,
                           const char* file, int line);                           // 0x00F473A0
struct WSAData_s0094_bb50 {
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
    WSAData_s0094_bb50        mWSAData;                      // +0x010
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
// ---- items of slice s0094bb50 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" __declspec(dllimport) int __stdcall WSAStartup(unsigned short wVersion, void* lpWSAData);
extern "C" __declspec(dllimport) int __stdcall WSACleanup(void);
extern "C" __declspec(dllimport) int __stdcall WSAGetLastError(void);
extern "C" __declspec(dllimport) long __stdcall RegOpenKeyExA(void* hKey, const char* sub, unsigned long opt,
unsigned long sam, void** phkResult);                                     // advapi32
extern "C" __declspec(dllimport) long __stdcall RegQueryValueExA(void* hKey, const char* name, unsigned long* res,
unsigned long* type, unsigned char* data, unsigned long* cbData);         // advapi32
extern "C" __declspec(dllimport) long __stdcall RegSetValueExA(void* hKey, const char* name, unsigned long res,
unsigned long type, const unsigned char* data, unsigned long cbData);     // advapi32
extern "C" __declspec(dllimport) long __stdcall RegCloseKey(void* hKey);                     // advapi32

// callees this slice defines outside this object (rewrite.py held_callee_protos)
unsigned int __declspec(noinline) Sockets_LookupName(const char* name, unsigned int timeout);  // 0x0094c1b0 (stays in the slice: not this object's)

// @ 0x0094c260
Manager::Manager()
{
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

// @ 0x0094c380
int EA::Sockets::Manager::GetMaxSockets()
{
    return mWSAData.iMaxSockets;
}

// @ 0x0094c3c0
bool EA::Sockets::Manager::Init()
{
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

// @ 0x0094c420
bool EA::Sockets::Manager::Shutdown()
{
    if (mbInitialized) {
        mbInitialized = false;
        if (WSACleanup() != 0) {
            mnLastError = WSAGetLastError();
            return false;
        }
    }
    return true;
}

// @ 0x0094c450
bool EA::Sockets::Manager::IsNetworkConnected(char const * p, bool q)
{
    int p_v = (int)p;
    (void)p_v;
    char c = ((char(__thiscall*)(Manager*))((*(void***)this)[7]))(this);
    if (c != 0 && q == 0)
        ((void(__thiscall*)(Manager*, int))((*(void***)this)[8]))(this, 0);
    return Sockets_LookupName("www.ea.com", 10000) != 0;
}

// @ 0x0094c490
void* Manager::CreateSocket(int type)
{
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

// @ 0x0094c510
bool EA::Sockets::Manager::GetAutoDialEnabled()
{
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

// @ 0x0094c580
bool EA::Sockets::Manager::SetAutoDialEnabled(bool on)
{
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

// @ 0x0094c620
bool Manager::GetManualDialupNameAndPassword(char* name, char* user, char* pass, unsigned len)
{
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

// @ 0x0094c730
void __stdcall Sockets_RasDialFunc(unsigned int unMsg, int rascs, unsigned int dwError)
{
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

// @ 0x0094c7a0
bool Manager::DoManualDialup(DialupCallback cb, char* entry, char* user, char* pass, unsigned len)
{
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

// @ 0x0094c9d0
bool Manager::CancelManualDialup()
{
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

// @ 0x0094ca60
bool Manager::SetManualDialupResult(int r)
{
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
