// src/game/SPEditors/SPURL.cpp -- migrated from slice(s) s00621830, s00620bd0, s00548d90, s00546160 by tools/migrate/rewrite.py
// Object file: SPEditors/SPURL.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern char  gEmptyString[];        // @ 0x1667bac
#include <wchar.h>
#include "cSPUILayout.h"

// ---- items of slice s00546160 begin (TODO(rewrite): local stubs, replace by canonical classes)
int*   LowerBound(int* first, int* last, unsigned int* key, char cmp);
int*   FUN_00547d80(int* pos, void* value);
void   FUN_0047d390(const void* a, const void* b);
void   FUN_005477e0();
extern char  gEmptyString[];        // @ 0x1667bac
struct Obj42 {
    char mPad[0x200];
    int* FUN_00546630();                       // ctor
    void FUN_00546800();                       // push_back 0x34
    int  FUN_00546880(int pos);                // erase one 0x34
    unsigned int* FUN_00546930(unsigned int* key); // vector_map operator[]
    void FUN_00546a60(void* value);            // push_back 0x10
    void FUN_00546b70();                       // push_back 0x118
    int* FUN_00546c20();                       // ctor of 0x118 entry
};
// ---- items of slice s00546160 end

// ---- items of slice s00620bd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t* gMapA;        // 0x15f5bbc
extern uint32_t* gMapAEnd;     // 0x15f5bc0
extern uint8_t   gMapACmp;     // 0x15f5bd0
extern uint32_t* gMapB;        // 0x15f5bd4
extern uint32_t* gMapBEnd;     // 0x15f5bd8
extern uint8_t   gMapBCmp;     // 0x15f5be8
extern const wchar_t gURLFormat[];  // 0x13f3da0
void  __cdecl EA_Free(void* p);                                                     // 0xf47380
void* __cdecl WStr_Format(void* dst, const void* fmt, ...);                         // 0x41e050
uint32_t* __cdecl eastl_lower_bound(uint32_t* first, uint32_t* last,
                                    const uint32_t* key, int comp);                 // 0x549dc0
void* __cdecl String8_CtorSprintf(void* self, int tag, const char* fmt, ...);       // 0x472f50
struct String8 {
  char* mpBegin;      // +0x00
  char* mpEnd;        // +0x04
  char* mpCapacity;   // +0x08
  char* mpAllocator;  // +0x0c
  void assign(const char* pBegin, const char* pEnd);   // 0x454cb0
};
struct URLMap {
  String8* op_index(const void* key);                  // 0x546930
};
// ---- items of slice s00620bd0 end

// ---- items of slice s00621830 begin (TODO(rewrite): local stubs, replace by canonical classes)
void __cdecl FUN_00621540(uint32_t key, const char* url);                    // 0x621540 SanitizeURL
bool __cdecl RegisterURL(uint32_t storeKey, uint32_t typeKey, const char* path);          // 0x6216b0
bool __cdecl RegisterInsecureURL(uint32_t storeKey, uint32_t typeKey, const char* path);  // 0x621770
extern const char* gURL1520cf4;   // 0x1520cf4
extern const char* gURL1520cf8;   // 0x1520cf8
extern const char* gURL1520cfc;   // 0x1520cfc
extern const char* gURL1520d00;   // 0x1520d00
// ---- items of slice s00621830 end

// @ 0x00546930
unsigned int* Obj42::FUN_00546930(unsigned int* key)
{
    int* p = (int*)this;
    int* lb = LowerBound((int*)p[0], (int*)p[1], key, *(char*)((char*)p + 5));
    if (lb == (int*)p[1] || *key < *(unsigned int*)lb) {
        unsigned int local_20[4];
        local_20[0] = *key;
        local_20[1] = 0;
        local_20[2] = 0;
        local_20[3] = 0;
        FUN_0047d390(gEmptyString, gEmptyString);
        lb = FUN_00547d80(lb, local_20);
        FUN_005477e0();
    }
    return (unsigned int*)lb + 1;
}

// @ 0x00549dc0
unsigned* FUN_00549dc0(unsigned* param_1, int param_2, unsigned* param_3)
{
    int n = (param_2 - (int)param_1) / 0x14;
    for (;;) {
        int local = n;
        if (local <= 0) break;
        n = local >> 1;
        if (param_1[n * 5] < *param_3) {
            param_1 = param_1 + n * 5 + 5;
            n = local - (n + 1);
        }
    }
    return param_1;
}

// @ 0x006214c0
bool GetURL(uint32_t key, String8* out)
{
  uint32_t* end = gMapBEnd;
  uint32_t* r = eastl_lower_bound(gMapB, end, &key, (int)gMapBCmp);
  if (r != end && key >= *r && r != r + 5) {
    if (out != 0) WStr_Format(out, gURLFormat, *(String8*)(r + 1));
    return true;
  }
  return false;
}

// @ 0x00621540
void SanitizeURL(void* out, char* url)
{
  if (url == 0) return;
  char* end = url;
  while (*end) ++end;
  String8 tmp;
  tmp.mpBegin = 0; tmp.mpEnd = 0; tmp.mpCapacity = 0; tmp.mpAllocator = 0;
  (void)end;
  (void)out;
}

// @ 0x006216b0
bool RegisterURL(uint32_t storeKey, uint32_t typeKey, const char* path)
{
  uint32_t* end = gMapAEnd;
  uint32_t* r = eastl_lower_bound(gMapA, end, &typeKey, (int)gMapACmp);
  if (r != end && typeKey >= *r && r != r + 5 && path != 0 && *path == '/') {
    char tag = 0;
    String8 local;
    String8* src = (String8*)String8_CtorSprintf(&local, tag, "https://%hs%hs",
                                                 *(char**)(r + 1), path);
    String8* dst = ((URLMap*)&gMapB)->op_index(&storeKey);
    if (src != dst) dst->assign(src->mpBegin, src->mpEnd);
    if ((local.mpCapacity - local.mpBegin) > 1 && local.mpBegin) EA_Free(local.mpBegin);
    return true;
  }
  return false;
}

// @ 0x00621770
bool RegisterInsecureURL(uint32_t storeKey, uint32_t typeKey, const char* path)
{
  uint32_t* end = gMapAEnd;
  uint32_t* r = eastl_lower_bound(gMapA, end, &typeKey, (int)gMapACmp);
  if (r != end && typeKey >= *r && r != r + 5 && path != 0 && *path == '/') {
    char tag = 0;
    String8 local;
    String8* src = (String8*)String8_CtorSprintf(&local, tag, "http://%hs%hs",
                                                 *(char**)(r + 1), path);
    String8* dst = ((URLMap*)&gMapB)->op_index(&storeKey);
    if (src != dst) dst->assign(src->mpBegin, src->mpEnd);
    if ((local.mpCapacity - local.mpBegin) > 1 && local.mpBegin) EA_Free(local.mpBegin);
    return true;
  }
  return false;
}

// @ 0x00621830
namespace SP {
namespace Pollen {
void InitURLs()
{
  FUN_00621540(0x5384c3f, gURL1520cf4);
  FUN_00621540(0x53dd8c2, gURL1520cf8);
  FUN_00621540(0x55bdfd6, gURL1520cfc);
  FUN_00621540(0x55e9027, gURL1520d00);
  RegisterURL(0x539f4e1, 0x5384c3f, "/pollinator/handshake");
  RegisterURL(0x539f864, 0x5384c3f, "/pollinator/public-interface/login");
  RegisterURL(0x5387572, 0x5384c3f, "/pollinator/public-interface/AssetUploadServlet");
  RegisterURL(0x68cb17d, 0x5384c3f, "/pollinator/upload/status/");
  RegisterURL(0x539e135, 0x5384c3f, "/pollinator/atom/randomAsset");
  RegisterURL(0x539e146, 0x5384c3f, "/pollinator/atom/subscribe");
  RegisterURL(0x539e14b, 0x5384c3f, "/pollinator/atom/userAssets");
  RegisterURL(0x539e150, 0x5384c3f, "/pollinator/atom/static/");
  RegisterURL(0x539f3e1, 0x5384c3f, "/pollinator/atom/creatureMatch");
  RegisterURL(0x539f69d, 0x5384c3f, "/pollinator/atom/delete");
  RegisterURL(0x539f705, 0x5384c3f, "/pollinator/atom/unsubscribe");
  RegisterURL(0x539f953, 0x5384c3f, "/pollinator/telemetry");
  RegisterURL(0x539f86b, 0x5384c3f, "/pollinator/atom/subscribe");
  RegisterURL(0x541aed9, 0x5384c3f, "/pollinator/atom/asset/");
  RegisterURL(0xe10f3837, 0x5384c3f, "/pollinator/atom/asset");
  RegisterURL(0x5efa12b, 0x53dd8c2, "/community/assetBrowser/deleteAsset/");
  RegisterURL(0x5ffeebf, 0x5384c3f, "/pollinator/event/upload");
  RegisterURL(0x538766b, 0x53dd8c2, "/community/auth/registerNew");
  RegisterURL(0x53f0df9, 0x53dd8c2, "/community/assetBrowser/comment/");
  RegisterURL(0xf4a5bd1e, 0x53dd8c2, "/community/assetBrowser/requiredPacks");
  RegisterInsecureURL(0x55192fa, 0x53dd8c2, "/static/thumb/");
  RegisterInsecureURL(0x56bbbd1, 0x53dd8c2, "/community/auth/help");
  RegisterURL(0x5908ef2, 0x53dd8c2, "/community/assetBrowser/createSporecast");
  RegisterURL(0x539e13b, 0x53dd8c2, "/community/assetBrowser/createSporecast");
  RegisterURL(0x539e141, 0x53dd8c2, "/community/assetBrowser/editSporecast");
  RegisterURL(0x53dd7c4, 0x53dd8c2, "/community/assetBrowser/home");
  RegisterURL(0x5436cc92, 0x53dd8c2, "/community/assetBrowser/findBuddy");
  RegisterURL(0x5436cc93, 0x53dd8c2, "/community/assetBrowser/findSporecast");
  RegisterURL(0x5436cc94, 0x53dd8c2, "/community/assetBrowser/createSporecast");
  RegisterURL(0x5436cc95, 0x53dd8c2, "/community/assetBrowser/store");
  RegisterURL(0x34c040d5, 0x53dd8c2, "/community/assetBrowser/achievements");
  RegisterURL(0x615ae67, 0x53dd8c2, "/community/assetBrowser/singleDownload");
  RegisterURL(0x62ec46a, 0x53dd8c2, "/community/assetBrowser/profile/");
  RegisterURL(0x53c3e41, 0x53dd8c2, "/community/public-interface/SnapshotUploadServlet");
  RegisterURL(0x56518ed, 0x53dd8c2, "/community-csa/csa/CSABrowser.html");
  RegisterURL(0x55bd0c8, 0x55bdfd6, "/youtube/accounts/ClientLogin");
  RegisterInsecureURL(0x55e8f9c, 0x55e9027, "/feeds/users");
  RegisterURL(0x56cded4, 0x53dd8c2, "/community/public-interface/VideoPathUploadServlet");
  RegisterURL(0x811c9dc5, 0x53dd8c2, "/community/assetBrowser/leaderBoardDlg/");
  RegisterURL(0x811c9dc7, 0x53dd8c2, "/community/assetBrowser/largeCard/gamesUsed/");
  RegisterURL(0x811c9dc8, 0x53dd8c2, "/community/assetBrowser/largeCard/comments/");
  RegisterURL(0x811c9dc9, 0x53dd8c2, "/community/assetBrowser/largeCard/leaderboard/");
  RegisterURL(0xf8671bdb, 0x53dd8c2, "/community/assetBrowser/rate");
}
}
}  // namespace SP::Pollen
