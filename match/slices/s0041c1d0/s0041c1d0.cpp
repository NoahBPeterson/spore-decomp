// Editor block-data export: loads/creates "Editors_BlockData.package" and dumps each
// block-data resource of 6 resource types to "<dir>0x<type>!0x<instance>.blockdata".
// Unoptimized module (/Od /Ob1). Behavioral reconstruction; not byte-exact (see nonmatching.txt).
#include "types.h"

struct ResKey { uint32_t instance, type, group; };

struct IUnknownLike { virtual void AddRef(); virtual void Release(); };
struct Stream { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                virtual void v5(); virtual int GetFlags(); };
struct Package { virtual void v0(); virtual void Release(); virtual void v2(); virtual void v3(); virtual void v4();
                 virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
                 virtual void v10(); virtual void SetPath(const wchar_t*); };
struct Manager { virtual void v0(); virtual void v1(); virtual void v2(); virtual int GetRecord(uint32_t, uint32_t, int); };

extern uint32_t g_ResTypes[6];
extern void* GetResourceManager();
extern const wchar_t* GetBasePath();
extern void FormatPath(wchar_t* dst, const wchar_t* fmt, ...);
extern void SetOutputDir(const wchar_t*);
extern bool LoadBlockData(int record, void* out);
extern void ReleaseRecord(int record);
extern void GetResourceKeys(uint32_t type, uint32_t** begin);
extern void* AllocEditor(int size, const char* name, int, int, int, int);

// @ 0x0041c1d0
void ExportEditorBlockData(int keyList, int unused)
{
    wchar_t path[256];
    uint32_t* keys[3] = { 0, 0, 0 };
    FormatPath(path, L"%lsEditors_BlockData.package", GetBasePath());
    AllocEditor(0x388, "Editor", 0, 0, 0, 0);
    FormatPath(path, L"%lsBlockData/", GetBasePath());
    SetOutputDir(path);
    for (unsigned t = 0; t < 6; ++t) {
        GetResourceKeys(g_ResTypes[t], keys);
        for (int i = 0; i < (int)(keys[1] - keys[0]); ++i) {
            int rec = ((Manager*)GetResourceManager())->GetRecord(keys[0][i], g_ResTypes[t], 4);
            if (rec) {
                if (LoadBlockData(rec, path)) {
                    FormatPath(path, L"%s0x%08x!0x%08x.blockdata", path, g_ResTypes[t], keys[0][i]);
                }
                ReleaseRecord(rec);
            }
        }
    }
}
