// slice s0058ba60 -- SP::cAppModeEditorBase::OnMouseMoveUpdate (998 B).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace SP {

struct PickResult {
    void* block;        // +0x00
    void* handle;       // +0x04
    float hit[3];       // +0x08
    bool pickedSkin;    // +0x14
    int region;         // +0x18
};

struct Helper {
    void  h586960();                       // 0x00586960
    bool  h573a60(float x, float y);       // 0x00573a60
    void  h577dd0();                       // 0x00577dd0
    void  h573970();                       // 0x00573970
    void  h5724a0();                       // 0x005724a0
    void  h5810a0();                       // 0x005810a0
    bool  h5ca920();                       // 0x005ca920
    void  h573d70(void* handle, int mode); // 0x00573d70
    void  h573c00(void* block, int region); // 0x00573c00
    void  h5820a0();                       // 0x005820a0
    void* h47e6c0();                       // 0x0047e6c0
};

struct CritList {
    int   count();                         // 0x004accf0
    void* item(int index, int zero);       // 0x004accb0
};

struct CritItem {
    void h43a830();                        // 0x0043a830
};

struct VBase {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual int  id();
};

void* GetBoneForHandle(int* handle);       // 0x004aa030
bool  FUN_004a60a0(void* a, void* b);      // 0x004a60a0
bool  FUN_004a6120(void* p);               // 0x004a6120
void  FUN_004a6660(void* p, int v);        // 0x004a6660
void  FUN_004a6640(void* p, void* q);      // 0x004a6640

class cAppModeEditorBase {
public:
    char pad0[0x600];
    int OnMouseMoveUpdate(float x, float y, unsigned a, unsigned b); // 0x0058ba60
    PickResult Pick(float x, float y, bool blocksOnly);              // 0x0057af00
};

}  // namespace SP

using namespace SP;

inline float SqrtF(float v) { return __builtin_sqrtf(v); }

// @ 0x0058ba60
int cAppModeEditorBase::OnMouseMoveUpdate(float x, float y, unsigned a, unsigned b)
{
    (void)a;
    char* self = (char*)this;
    unsigned char local_1d = 0;

    if (self[0x472] != 0) {
        float fb = (float)(int)b;
        if ((int)b < 0)
            fb += 4294967296.0f;
        float deadline = fb * 0.001f + *(float*)(self + 0x474);
        *(float*)(self + 0x474) = deadline;

        bool expired = deadline >= *(float*)(self + 0x478);
        if (!expired) {
            float dx = x - *(float*)(self + 0x480);
            float dy = y - *(float*)(self + 0x484);
            float dist = SqrtF(dx * dx + dy * dy);
            expired = dist > *(float*)(self + 0x47c);
        }
        if (expired)
            ((Helper*)self)->h586960();
    }

    if (self[0x38] == 0)
        return 1;

    unsigned char cVar5 = (unsigned char)self[0x385];
    self[0x38] = 0;

    if (cVar5 != 0 && *(unsigned*)(self + 0x31c) == 0) {
        if (self[0x4d4] == 0) {
            if (((Helper*)self)->h573a60(x, y)) {
                *(float*)(self + 0x68) = 0.0f;
                ((Helper*)self)->h577dd0();
                ((Helper*)self)->h573970();
            }
        } else {
            float dx = x - *(float*)(self + 0x480);
            float dy = y - *(float*)(self + 0x484);
            float m = *(float*)(self + 0x488);
            if (dx * dx + dy * dy > m * m)
                ((Helper*)self)->h5724a0();
        }
    }

    if (self[0x472] != 0)
        goto Lbdcc;

    {
        unsigned state = *(unsigned*)(self + 0x31c);
        unsigned ret_high = state;
        if (state == 0)
            goto Lbc87;
        if (state == 1) {
            if (self[0x2f1] != 0)
                return 1;

            ((Helper*)(self + 0x39c))->h5810a0();

            {
                CritList* list = *(CritList**)(self + 0x98);
                int n = list->count();
                for (int i = 0; i < n; ++i) {
                    void* item = list->item(i, 0);
                    ((CritItem*)item)->h43a830();
                }
            }

            PickResult pick = Pick(x, y, true);
            *(unsigned*)(self + 0x3c) &= ~1u;

            if (*(void**)(self + 0x3c4) == 0)
                return 1;
            if (!((Helper*)(*(void**)(self + 0x3c4)))->h5ca920())
                return 1;

            ++*(unsigned*)(self + 0x3c);

            if (pick.block != 0 &&
                ((*(unsigned*)((char*)pick.block + 0xdc8) >> 3) & 1) == 0) {
                ((Helper*)self)->h573c00(pick.block, pick.region);
                if (*(unsigned*)(self + 0xcc) != 0) {
                    ((Helper*)self)->h5820a0();
                    return 1;
                }
            }

            ((Helper*)self)->h573c00(0, -1);
            return 1;
        }
        (void)ret_high;
    }
    goto Lbdcc;

Lbc87:
    if (*(unsigned*)(self + 0x148) != 0)
        goto Lbdcc;
    if (*(unsigned*)(self + 0x34) != 0)
        goto Lbdcc;

    {
        void* pc8 = *(void**)(self + 0xe4);
        void* pc10 = *(void**)(self + 0xcc);

        if (pc8 != 0 && pc10 == 0) {
            int id = ((VBase*)pc8)->id();
            if (id == 0x50e8e23)
                pc10 = ((Helper*)pc8)->h47e6c0();
        }
        if (pc10 != 0 && ((*(unsigned*)((char*)pc10 + 0xdc8) >> 1) & 1) != 0)
            pc10 = 0;

        PickResult pick = Pick(x, y, false);
        local_1d = pick.pickedSkin;

        int* bone = 0;
        if (pick.handle != 0 && *(unsigned*)((char*)pick.handle + 0x64) != 0)
            bone = (int*)GetBoneForHandle((int*)((char*)pick.handle + 0x64));

        ((Helper*)self)->h573d70(bone, 1);

        if (*(unsigned*)(self + 0xe4) == 0)
            ((Helper*)self)->h573c00(pick.block, -1);

        if (pick.block != 0 || pick.handle != 0)
            *(float*)(self + 0x68) = 0.0f;

        void* active = *(void**)(self + 0xcc);
        if (bone != 0 && ((VBase*)bone)->id() == 0x50e8e23)
            active = ((Helper*)bone)->h47e6c0();

        bool same = FUN_004a60a0(active, pc8);
        if (!same && pc8 != active) {
            if (pc8 != 0 && FUN_004a6120(pc8))
                FUN_004a6660(pc8, 0);
            if (active != 0 && FUN_004a6120(active))
                FUN_004a6640(active, *(void**)(self + 0x150));
        }
    }

Lbdcc:
    if (*(unsigned*)(self + 0x14c) == 0)
        return 1;

    {
        void* block = *(void**)(self + 0xcc);
        bool b3 = false;
        bool b4 = false;
        if (block != 0) {
            unsigned flags = *(unsigned*)((char*)block + 0xdc8);
            b3 = ((flags >> 7) & 1) == 0;
            b4 = ((flags >> 7) & 1) != 0;
        }

        unsigned char u = 0;
        if (self[0x2b2] != 0 && *(unsigned*)(self + 0x148) == 0 && !b3 &&
            (b4 || local_1d != 0))
            u = 1;

        if ((unsigned char)self[0xe8] != u)
            self[0xe8] = (char)u;
    }

    return 1;
}
