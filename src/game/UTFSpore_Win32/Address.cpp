// src/game/UTFSpore_Win32/Address.cpp -- migrated from slice(s) s0094bb50 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Address.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Sockets/DatagramSocket.h"
#include "EA/Sockets/IPAddress.h"
#include "EA/Sockets/Manager.h"
#include "EA/Sockets/StreamSocket.h"
#include "WSAData.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int __stdcall closesocket(unsigned int s);                  // wsock32!closesocket
extern "C" __declspec(dllimport) unsigned int __stdcall WSASocketA(int af, int type, int protocol,
void* lpProtocolInfo, unsigned int g, unsigned int dwFlags);              // ws2_32!WSASocketA
extern "C" __declspec(dllimport) int __stdcall WSAIoctl(unsigned int s, unsigned long code,
void* inBuf, unsigned long cbIn, void* outBuf, unsigned long cbOut,
unsigned long* bytesReturned, void* overlapped, void* completionRoutine); // ws2_32!WSAIoctl
#include <string.h>
#include <stdlib.h>
#include <new>

// ---- items of slice s0094bb50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) struct hostent* __stdcall gethostbyname(const char* name);  // wsock32!gethostbyname
extern "C" __declspec(dllimport) int __stdcall closesocket(unsigned int s);                  // wsock32!closesocket
extern "C" __declspec(dllimport) unsigned int __stdcall WSASocketA(int af, int type, int protocol,
void* lpProtocolInfo, unsigned int g, unsigned int dwFlags);              // ws2_32!WSASocketA
extern "C" __declspec(dllimport) int __stdcall WSAIoctl(unsigned int s, unsigned long code,
void* inBuf, unsigned long cbIn, void* outBuf, unsigned long cbOut,
unsigned long* bytesReturned, void* overlapped, void* completionRoutine); // ws2_32!WSAIoctl
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
// ---- items of slice s0094bb50 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" __declspec(dllimport) struct hostent* __stdcall gethostbyname(const char* name);  // wsock32!gethostbyname

// @ 0x0094c1b0
unsigned int __declspec(noinline) Sockets_LookupName(const char* name, unsigned int timeout)
{
    (void)timeout;
    hostent* h = gethostbyname(name);
    if (h != 0)
        return *(unsigned int*)h->h_addr_list[0];
    return (unsigned int)-1;
}

// @ 0x0094c1d0
bool __cdecl Sockets_GetCurrentMachineAddress(IPAddress* out, unsigned int index)
{
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
