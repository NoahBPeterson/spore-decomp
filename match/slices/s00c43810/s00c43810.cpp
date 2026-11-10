// Flags: /O2 /MD /Gy /TP
typedef bool (__cdecl* Pred)(void* p);
void** remove_copy_if(void** first, void** last, void** dest, Pred pred); // 0x00c43270

// @ 0x00c43810
void** FUN_00c43810(void** first, void** last, Pred pred)
{
    while (first != last) {
        if (pred(*first))
            break;
        ++first;
    }
    if (first != last) {
        void** next = first;
        return remove_copy_if(++next, last, first, pred);
    }
    return first;
}
