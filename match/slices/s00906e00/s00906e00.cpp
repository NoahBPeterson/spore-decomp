// slice s00906e00 -- expat 2.0.1 xmlparse.c tokenizer / DTD helpers
// Flags: /O2 /MD /Gy /EHsc /TP

int reportProcessingInstruction(int parser, const char* s, const char* next);
int reportComment(int parser);
void reportDefault(const char* s);
int appendAttributeValue(void* parser, void* enc, int isCdata, const char* ptr, const char* end, int* pool);
int poolGrow(int* pool);

int externalEntityInitProcessor3(int parser, const char* start, const char* end, const char** endPtr);

// @ 0x00906e00
int epilogProcessor(int parser, const char* param_2, const char* param_3, const char** param_4)
{
    int iVar3 = parser;
    const char* uVar2 = param_2;
    const char* uVar4 = param_3;
    const char* uVar6;
    const char* local;
    int iVar5;

    *(void**)(parser + 0x118) = (void*)&epilogProcessor;
    *(const char**)(parser + 0x120) = param_2;
    local = 0;
    iVar5 = (*(int (**)(void*, const char*, const char*, const char**))(*(void**)(parser + 0x90)))
                (*(void**)(parser + 0x90), param_2, param_3, &local);
    *(const char**)(iVar3 + 0x124) = local;
    while ((unsigned)(iVar5 + 0xf) < 0x1f) {
        switch ((unsigned)(iVar5 + 0xf)) {
        case 0:
            *(const char**)(iVar3 + 0x120) = local;
            return 4;
        case 0xb:
            iVar5 = reportProcessingInstruction(iVar3, uVar2, local);
            break;
        case 0xd:
            iVar5 = reportComment(iVar3);
            break;
        case 0xf:
            uVar6 = local;
            if (*(int*)(iVar3 + 0x50) != 0) {
                reportDefault(uVar2);
                uVar6 = local;
            }
            goto LAB_eb9;
        case 0xfffffffe:
            if (*(char*)(iVar3 + 0x1e4) != 0)
                return 6;
            /* fallthrough */
        case 0xfffffffc:
            *param_4 = uVar2;
            return 0;
        case 0xffffffff:
            if (*(char*)(iVar3 + 0x1e4) != 0)
                return 5;
            *param_4 = uVar2;
            return 0;
        case 0xfffffff1:
            if (*(int*)(iVar3 + 0x50) != 0) {
                reportDefault(uVar2);
                if (*(int*)(iVar3 + 0x1e0) == 2)
                    return 0x23;
            }
            *param_4 = local;
            return 0;
        default:
            return 9;
        }
        uVar6 = local;
        if (iVar5 == 0)
            return 1;
    LAB_eb9:
        *(const char**)(iVar3 + 0x120) = uVar6;
        if (*(int*)(iVar3 + 0x1e0) == 2)
            return 0x23;
        if (*(int*)(iVar3 + 0x1e0) == 3) {
            *param_4 = uVar6;
            return 0;
        }
        local = 0;
        iVar5 = (*(int (**)(void*, const char*, const char*, const char**))(*(void**)(iVar3 + 0x90)))
                    (*(void**)(iVar3 + 0x90), uVar6, uVar4, &local);
        *(const char**)(iVar3 + 0x124) = local;
        uVar2 = uVar6;
    }
    return 9;
}

// @ 0x00907000
int storeAttributeValue(void* parser, void* enc, int isCdata, const char* ptr, const char* end, int* pool)
{
    int iVar2;
    short* psVar3;

    iVar2 = appendAttributeValue(parser, enc, isCdata, ptr, end, pool);
    if (iVar2 == 0) {
        if (isCdata == 0 &&
            (((pool[3] - pool[4]) & 0xfffffffe) != 0) &&
            (psVar3 = (short*)(pool[3] - 2), *psVar3 == 0x20)) {
            pool[3] = (int)psVar3;
        }
        if (pool[3] == pool[2]) {
            if (poolGrow(pool) == 0)
                return 1;
        }
        *(short*)pool[3] = 0;
        pool[3] = pool[3] + 2;
        iVar2 = 0;
    }
    return iVar2;
}

// @ 0x00907420
int externalEntityInitProcessor2(int parser, const char* start, const char* end, const char** endPtr)
{
    const char* next = start;
    void* enc = *(void**)(parser + 0x90);
    int tok = ((int (*)(void*, const char*, const char*, const char**))(*(void***)enc)[1])
                  (enc, start, end, &next);

    if (tok == -2) {
        if (*(char*)(parser + 0x1e4) != 0) {
            *(int*)(parser + 0x120) = (int)start;
            return 6;
        }
        *endPtr = start;
        return 0;
    }
    if (tok == -1) {
        if (*(char*)(parser + 0x1e4) == 0) {
            *endPtr = start;
            return 0;
        }
        *(int*)(parser + 0x120) = (int)start;
        return 5;
    }
    if (tok != 14 || next != end || *(char*)(parser + 0x1e4) != 0) {
        *(void**)(parser + 0x118) = (void*)&externalEntityInitProcessor3;
        return externalEntityInitProcessor3(parser, next, end, endPtr);
    }
    *endPtr = next;
    return 0;
}
