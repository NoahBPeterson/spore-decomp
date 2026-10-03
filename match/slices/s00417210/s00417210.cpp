// @ 0x00417210 see ExportResources below
// Editor: export resource files to disk under a base path, checking out/in via Perforce (p4.exe).
// Built /Od /Ob1 /MD /Gy /EHsc /TP (frame pointer, all locals in memory).
#include "types.h"

struct WString {
    wchar_t* cur; wchar_t* begin; wchar_t* end; int pad[2];
    wchar_t buf[386];
    inline wchar_t* Data() { return cur; }
};
void __fastcall WString_Init(WString* s);   // 0x0041d600
void __fastcall WString_Free(WString* s);   // 0x004292a0
struct ResKey { uint32_t instance, type, group; };
struct KeyVec { ResKey* first; ResKey* last; inline ResKey* At(int i) { return first + i; } };
struct KeyVec2 { ResKey* first; ResKey* last; };

struct Handler {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual const wchar_t* GetExt(wchar_t* name);          // +0x28
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual bool GetName(ResKey* k, wchar_t* out);         // +0x64
};
struct Manager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual int FindHandler(ResKey* k);                    // +0x58
};

Manager* GetManager();                                      // 0x0067dcd0
const wchar_t* GetBasePath();                               // 0x00688cb0
int __cdecl swprintf_like(void* dst, const wchar_t* fmt, ...); // 0x004c0530
void __cdecl CreateDirs(wchar_t* path);                     // 0x00932960
Handler* __cdecl LookupHandler(int id);                     // 0x00422950
int __fastcall FindChar(WString* s, int a, int b);          // 0x004f6ab0 (thiscall below)
bool __cdecl FileExists(wchar_t* path);                     // 0x00931fa0
void __cdecl SetFileAttr(wchar_t* path, int a, int b);      // 0x009320a0
void __cdecl CopyFileTo(const wchar_t* src, wchar_t* dst, int overwrite); // 0x00932030
void __cdecl RunProcess(const wchar_t* exe, const wchar_t* verb, const wchar_t* args, int wait); // 0x006bb4b0
void __cdecl RunProcess(const wchar_t* exe, const wchar_t* a, const wchar_t* b, const wchar_t* c, int wait); // 0x006bb4b0
struct WStringOps {
    int __thiscall Find(int ch, int pos);                   // 0x004f6ab0
    void __thiscall Erase(int pos, int n);                  // 0x004228e0
    void __thiscall Insert(int pos, const wchar_t* s);      // 0x00422880
};

// @ 0x00417210
void __cdecl ExportResources(KeyVec* keys, const wchar_t* dir, const wchar_t* sub,
                             Handler* h1, Handler* h2, bool checkout)
{
    WString unused;
    Manager* mgr;
    WString path;
    wchar_t name[256];
    WString destName;
    const wchar_t* base;
    int n, i;
    Handler* h;
    mgr = GetManager();
    base = GetBasePath();
    WString_Init(&destName);
    WString_Init(&path);
    swprintf_like(&path, L"%ls%ls/%ls/", base, dir, sub);
    CreateDirs(path.Data());
    WString_Init(&unused);
    i = 0;
    n = keys->last - keys->first;
    for (; i < n; ++i) {
        switch (keys->first[i].type) {
        case 0x3d97a8e4: case 0x2399be55: case 0x24682294: case 0x2b978c46:
        case 0x438f6347: case 0x476a98c7:
            continue;
        }
        h = LookupHandler(mgr->FindHandler(keys->At(i)));
        if (h != h1 && h != h2) continue;
        if (!h->GetName(keys->At(i), name)) continue;
        swprintf_like(&destName, L"%ls%ls", h->GetExt(name));
        swprintf_like(&path, L"%ls%ls/%ls/%ls", base, dir, sub, name);
        if (checkout) {
            WString q; WString_Init(&q);
            swprintf_like(&q, L"\"%ls\"", path.Data());
            int p;
            while ((p = ((WStringOps*)&q)->Find(0x40, 0)) != -1) {
                ((WStringOps*)&q)->Erase(p, 1);
                ((WStringOps*)&q)->Insert(p, L"%40");
            }
            RunProcess(L"p4.exe", L"edit", q.Data(), 0);
            WString_Free(&q);
        }
        if (FileExists(path.Data()))
            SetFileAttr(path.Data(), 2, 1);
        CopyFileTo(destName.Data(), path.Data(), 1);
        if (checkout) {
            WString q2; WString_Init(&q2);
            swprintf_like(&q2, L"\"%ls\"", path.Data());
            RunProcess(L"p4.exe", L"add", L"-f", q2.Data(), 0);
            WString_Free(&q2);
        }
        FileExists(path.Data());
    }
    WString_Free(&unused);
    WString_Free(&path);
    WString_Free(&destName);
}
