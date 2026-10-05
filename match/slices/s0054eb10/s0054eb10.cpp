// Slice s0054eb10: SP::Pollen::cAssetDirectory container/dispatch methods (mutex-guarded
// map/set lookups and a job helper). Module flags:
// /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

// thiscall callees modelled as stub-class members.
struct Mtx {
    int Lock(const void* p);   // EA::Thread::Mutex::Lock
    int Unlock();              // EA::Thread::Mutex::Unlock
};
struct Ctr {
    void F90(void* out, int key);          // 0x553090 map find
    void F9d0(void* out, const void* key); // 0x5529d0 map lower_bound
    void Fc20(const void* iter);           // 0x552c20 map erase
    void F620(const void* key);            // 0x553620 set/map find
    void F3a0(void* first, void* last);    // 0x5543a0 vector clear
    void F140(void* out);                  // 0x564140 hash find
    void FreeNodes(void* first, void* last); // 0x5687d0 hashtable DoFreeNodes
};
struct Dir {
    void F210(int ptr);        // 0x550210
    bool FUN_0054eb10(int param2, char param3);
    bool FUN_0054ed50(int param2, int param3, char param4);
    char FUN_0054efb0();
    int  FUN_0054f0f0();
};
struct CJob {
    int GetStatus();           // 0x690120
};

int*  ObjectTemplateDB();      // 0x67cb40
void  FUN_0054f1a0(int self);
void* FUN_0068f4d0();
int   FUN_006909b0();
void  FUN_0068f5a0();

struct It { int a; int b; };

// @ 0x0054eb10
bool Dir::FUN_0054eb10(int param2, char param3)
{
    int self = (int)this;
    char* s = (char*)self;
    bool r = false;
    Mtx* mtx = (Mtx*)(s + 8);
    mtx->Lock(&r);
    if (*(char*)(s + 0x38) != 0) {
        It it;
        ((Ctr*)(s + 0x5c))->F90(&it, param2);
        int* miss = (int*)(*(int*)(s + 0x60) + *(int*)(s + 100) * 4);
        if (*(int*)&it != *miss) {
            It it2;
            ((Ctr*)(s + 0x3c))->F9d0(&it2, (char*)&it + 0x10);
            int* miss2 = (int*)(*(int*)(s + 0x40) + *(int*)(s + 0x44) * 4);
            if (*(int*)&it2 != *miss2) {
                ((Ctr*)(s + 0x3c))->Fc20(&it2);
                ((Ctr*)(s + 0x5c))->Fc20(&it);
                ((Ctr*)(s + 0x9c))->F620((char*)&it + 0x10);
                if (param3 != 0) {
                    int* db = ObjectTemplateDB();
                    ((void(__thiscall*)(void*, int, int))((*(void***)db)[0x78 / 4]))(db, param2, 0);
                } else {
                    ((Dir*)s)->F210(param2);
                }
                *(int*)(s + 0xbc) = *(int*)(s + 0xbc) + 1;
            }
            r = true;
        }
    }
    mtx->Unlock();
    return r;
}

// @ 0x0054ed50
bool Dir::FUN_0054ed50(int param2, int param3, char param4)
{
    int self = (int)this;
    char* s = (char*)self;
    bool r = false;
    Mtx* mtx = (Mtx*)(s + 8);
    mtx->Lock(&r);
    if (*(char*)(s + 0x38) != 0) {
        It it2;
        ((Ctr*)(s + 0x9c))->F620(&param2);
        It it;
        ((Ctr*)(s + 0x3c))->F9d0(&it, &param2);
        int* miss = (int*)(*(int*)(s + 0x40) + *(int*)(s + 0x44) * 4);
        if (*(int*)&it != *miss) {
            if (param4 == 0) {
                ((Dir*)s)->F210(it2.a);
            } else {
                int* db = ObjectTemplateDB();
                ((void(__thiscall*)(void*, int, int))((*(void***)db)[0x78 / 4]))(db, (int)(char*)&it + 8, 0);
            }
            ((Ctr*)(s + 0x3c))->Fc20(&it);
            It it3;
            ((Ctr*)(s + 0x5c))->F90(&it3, *(int*)&it);
            int* miss2 = (int*)(*(int*)(s + 0x60) + *(int*)(s + 100) * 4);
            if (*(int*)&it3 != *miss2 && *(int*)((char*)&it3 + 0x10) == param2
                && *(int*)((char*)&it3 + 0x14) == param3) {
                ((Ctr*)(s + 0x5c))->Fc20(&it3);
            }
            *(int*)(s + 0xbc) = *(int*)(s + 0xbc) + 1;
            r = true;
        }
    }
    mtx->Unlock();
    return r;
}

// @ 0x0054efb0
char Dir::FUN_0054efb0()
{
    int self = (int)this;
    char* s = (char*)self;
    if (*(char*)(s + 0x38) != 0) {
        Mtx* mtx = (Mtx*)(s + 8);
        mtx->Lock(0);
        void* q[2];
        ((Ctr*)(s + 0x5c))->F140(q);
        ((Ctr*)(s + 0x3c))->F3a0(*(void**)(s + 0x40), *(void**)(s + 0x44));
        *(int*)(s + 0x48) = 0;
        ((Ctr*)(s + 0x5c))->F3a0(*(void**)(s + 0x60), *(void**)(s + 100));
        *(int*)(s + 0x68) = 0;
        ((Ctr*)(s + 0x9c))->FreeNodes(*(void**)(s + 0xa0), *(void**)(s + 0xa4));
        *(int*)(s + 0xa8) = 0;
        FUN_0054f1a0(self);
        mtx->Unlock();
    }
    return *(char*)(s + 0x38);
}

// @ 0x0054f0f0
int Dir::FUN_0054f0f0()
{
    int* job = 0;
    int* sched = (int*)FUN_0068f4d0();
    if (job != 0) {
        ((CJob*)job)->GetStatus();
    }
    int ok = ((int(__thiscall*)(int*, int**))((*(void***)sched)[0x10 / 4]))(sched, &job);
    if (ok == 0) {
        if (job != 0) ((CJob*)job)->GetStatus();
        return 0;
    }
    job[6] = 4;
    job[0] = (int)&FUN_0068f5a0;
    job[1] = 0x15e3188;
    FUN_006909b0();
    if (job != 0) ((CJob*)job)->GetStatus();
    return 1;
}
