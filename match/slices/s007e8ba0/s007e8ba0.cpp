// Slice s007e8ba0.
#include "../s007e5220/s007e5220.h"

struct CommandLine {
    uint32_t FindSwitch(const wchar_t* name, int a, int b, int c);
};

// @ 0x007E9300  (cAppSystem::InitPlugins)
bool cAppSystem::InitPlugins(void* cmd) {
    CommandLine* cl = (CommandLine*)cmd;
    if (cl->FindSwitch(L"noPlugins", 0, 0, 0) == -1) {
        if (cl->FindSwitch(L"safe", 0, 0, 0) == -1) {
            return LoadPlugins();
        }
    }
    return false;
}

// @ 0x007E93D0  (cAppSystem::SetUserDirNames)
void cAppSystem::SetUserDirNames(wchar_t* publicDir, wchar_t* privateDir) {
    const wchar_t* e = publicDir;
    while (*e) ++e;
    int n = (int)(e - publicDir);
    mPublicDirName.assign(publicDir, publicDir + n);
    mPublicDirName.push_back(L'\\');
    e = privateDir;
    while (*e) ++e;
    n = (int)(e - privateDir);
    mPrivateDirName.assign(privateDir, privateDir + n);
    mPrivateDirName.push_back(L'\\');
}

// @ 0x007E8BA0  (cAppSystem::PreInit)
int cAppSystemPreInit(void* self, void* a) {
    // 1885-byte startup sequence not reconstructed; see partial.txt.
    (void)self; (void)a;
    return 0;
}

// @ 0x007E9450  (cAppSystem::Shutdown)
void cAppSystemShutdown(void* self) {
    // 1453-byte shutdown sequence not reconstructed; see partial.txt.
    (void)self;
}
