// Slice s0097cea0: EA::UTFWinControls WinGrid + ImageCursorProvider tail (MSVC 2008 SP1, /O2).
// PDB names used where known:
//   WinGrid::SetCellWindow / Refresh, ImageDrawable::{GetNaturalSize,CreateRenderables,scalar deleting dtor},
//   CustomWinProc::Release, ImageCursorProvider::*, eastl hashtable helpers, CursorListMarshaller::Read.
#include "types.h"

extern "C" void* ea_new(unsigned, const char*, int, int, const char*, int);
extern "C" void  ea_delete(void*);
extern "C" void  FUN_00951330(void*);              // MultiHeapObject::operator_delete
extern "C" void* UTFWin_GetManager();
extern "C" void* Hashtable_find(void* out, const void* key, void* table);
extern "C" void  Hashtable_DoRehash();
extern "C" void  Hashtable_DoFreeNodes();

extern char g_vtblImageDrawable;
extern char g_vtblImageDrawable2;
extern char g_vtblImageDrawable3;
extern char g_vtblEditorResource;

// ---------------------------------------------------------------------------------------------
// @ 0x0097DA40  EA::UTFWin::CustomWinProc::Release
// ---------------------------------------------------------------------------------------------
struct CustomWinProc2 {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2(int);
    int field4;         // +4
    int mRefCount;      // +8

    int Release();
};

int CustomWinProc2::Release() {
    int n = (*(volatile int*)&mRefCount += -1);
    if (n == 0) slot2(1);
    return n;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0097DA60  EA::UTFWinControls::ImageCursorProvider::AsInterface
// ---------------------------------------------------------------------------------------------
struct ImageCursorProvider {
    virtual void slot0();
    virtual void slot1();   // added to make the vtable live
    char pad[0x0c];
    void* AsInterface(unsigned int id);
};

void* ImageCursorProvider::AsInterface(unsigned int id) {
    if (id <= 0xee3f516e) {
        if (id == 0xee3f516e) return this;
        if (id == 0x2ce4360) return this;
        if (id == 0x2cf3268) return this;
    } else if (id == 0xeec58382 && this != 0) {
        return (char*)this + 4;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0097D950  EA::UTFWinControls::ImageDrawable::`scalar deleting destructor'
// ---------------------------------------------------------------------------------------------
struct ImageDrawable {
    void* vtbl0;        // +0
    void* vtbl1;        // +4
    char  pad[0x1c];
    void* mpImage;      // +0x24
    ImageDrawable* DestroyScalar(unsigned char flags);
};

ImageDrawable* ImageDrawable::DestroyScalar(unsigned char flags) {
    void* img = mpImage;
    vtbl0 = &g_vtblImageDrawable;
    vtbl1 = &g_vtblImageDrawable2;
    ((void**)((char*)this + 0xc))[0] = &g_vtblImageDrawable3;
    if (img) {
        ((void(__thiscall*)(void*))((void**)*(void**)img)[1])(img);
    }
    *(void**)((char*)this + 0xc) = &g_vtblEditorResource;
    vtbl1 = &g_vtblEditorResource;
    vtbl0 = &g_vtblEditorResource;
    if (flags & 1) FUN_00951330(this);
    return this;
}

// ---------------------------------------------------------------------------------------------
// @ 0x0097D080  EA::UTFWinControls::WinGrid::Refresh  (adjustor thunk into FUN_0097bc80)
// ---------------------------------------------------------------------------------------------
extern "C" void FUN_0097bc80(void*);
void WinGrid_Refresh(void* self) { FUN_0097bc80((char*)self - 0x20c); }

// ---------------------------------------------------------------------------------------------
// @ 0x0097D100  intrusive pointer field setter
// ---------------------------------------------------------------------------------------------
void SetIntrusive18(void* self, void* p) {
    if (*(void**)((char*)self + 0x18) != p) {
        if (p) ((void(__thiscall*)(void*))((void**)*(void**)p)[0])(p);
        void* old = *(void**)((char*)self + 0x18);
        if (old) ((void(__thiscall*)(void*))((void**)*(void**)old)[1])(old);
        *(void**)((char*)self + 0x18) = p;
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x0097D170  EA::UTFWinControls::ImageDrawable::GetNaturalSize
// ---------------------------------------------------------------------------------------------
bool ImageDrawable_GetNaturalSize(void* self, int* outW, int* outH) {
    if (*(void**)((char*)self + 0x24) == 0) return false;
    (void)outW; (void)outH;
    return true;   // approximated
}

// ---------------------------------------------------------------------------------------------
// @ 0x0097D1A0 / 0x0097D270 / 0x0097D8D0  ImageDrawable helpers (approximated)
// ---------------------------------------------------------------------------------------------
int  ImageDrawable_GetWidth(void* self) { return self ? *(int*)((char*)self + 0x14) : 0; }
bool ImageDrawable_CreateRenderables(void* self, void* a, void* b) { (void)self;(void)a;(void)b; return true; }
void ImageDrawable_Destroy(void* self) { (void)self; }

// ---------------------------------------------------------------------------------------------
// @ 0x0097CEA0  EA::UTFWinControls::WinGrid::SetCellWindow  (465 bytes)
// ---------------------------------------------------------------------------------------------
extern "C" bool WinGrid_AssignCell(void* self, int row, int col);
bool WinGrid_SetCellWindow(void* self, int row, int col, int window, int flags) {
    (void)flags;
    if (!WinGrid_AssignCell(self, row, col)) {
        return false;
    }
    return true;   // control flow approximated (SparseMatrix cell insert)
}

// ---------------------------------------------------------------------------------------------
// @ 0x0097DAD0  ImageCursorProvider::CursorWindow::CursorWindow  (ctor)
// @ 0x0097DB30  ImageCursorProvider::CursorWindow::OnRebuild
// @ 0x0097DB90  (provider helper)
// @ 0x0097DC00  ImageCursorProvider::UpdateMousePosition
// @ 0x0097DC30  hashtable<...>::DoRehash
// @ 0x0097DD80  (hashtable helper)
// @ 0x0097DDF0  ImageCursorProvider::HasCursor
// @ 0x0097DE20  ImageCursorProvider::SetCursor
// @ 0x0097E030  hashtable<...>::DoFreeNodes
// @ 0x0097E0B0  hash_map<...>::operator[]
// @ 0x0097E140  CursorListMarshaller::Read
// ---------------------------------------------------------------------------------------------
void CursorWindow_ctor(void* self) { (void)self; }
void CursorWindow_OnRebuild(void* self) { (void)self; }
void CursorProvider_helper_db90(void* self) { (void)self; }
void ImageCursorProvider_UpdateMousePosition(void* self) { (void)self; }
void Hashtable_DoRehashStub(void* self) { Hashtable_DoRehash(); }
void Hashtable_helper_dd80(void* self) { (void)self; }

bool ImageCursorProvider_HasCursor(void* self) {
    (void)self;
    return false;   // eastl hashtable<unsigned,...>::find -> approximated
}

bool ImageCursorProvider_SetCursor(void* self, int cursor) {
    (void)self; (void)cursor;
    return false;   // 325-byte manager interaction approximated
}

void Hashtable_DoFreeNodesStub(void* self) { Hashtable_DoFreeNodes(); }

void* Hashmap_operator_index(void* self, unsigned key) {
    (void)self; (void)key;
    return 0;   // find + insert + rehash approximation
}

bool CursorListMarshaller_Read(void* self, void* r) {
    (void)self; (void)r;
    return false;   // stream read approximation
}
