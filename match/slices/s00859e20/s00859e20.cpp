// Slice s00859e20 (batch hk2 slice 0).  One function: 0085acc0, 150 bytes, __cdecl void(Owner*).
// Rebuilds one row per record of a 2-buffered table: for record i it computes a row
// length from three record fields, stores a row count into the buffer header for
// record 0, then repeats the element just before the cut point across the rest of
// the row (n = 2 * step elements).  32-bit MSVC 2008 SP1, /O2 /MD /Gy /EHsc /TP.

struct Elem054 {               // record stride 0x54, array at owner+0xd8
    char pad0[0xc];
    int a;                     // +0x0c  (piVar6[0])
    char pad1[0x14];
    int b;                     // +0x24  (piVar6[6])
    int pad2;
    int c;                     // +0x2c  (piVar6[8])
    char pad3[0x24];
};

struct Buf {                   // pointed to by owner+0x5a8
    char  pad0[0x38];
    int** planes[2];           // +0x38: planes[which] points to an array of row pointers
    int   which;               // +0x40
    int   pad1;
    int   rowCount;            // +0x48
};

struct Owner {
    char  pad0[0x20];
    int   count;               // +0x20
    char  pad1[0xd8 - 0x24];
    Elem054* elems;            // +0xd8
    char  pad2[0x53c - 0xdc];
    int   divisor;             // +0x53c
    char  pad3[0x5a8 - 0x540];
    Buf*  buf;                 // +0x5a8
};

// 0085acc0 Owner_BuildRows
void Owner_BuildRows(Owner* p) {
    Buf* buf = p->buf;
    Elem054* e = p->elems;
    for (int i = 0; i < p->count; ++i, ++e) {
        unsigned int total = (unsigned int)(e->b * e->a);
        int step = (int)total / p->divisor;
        unsigned int start = (unsigned int)e->c % total;
        if (start == 0) start = total;
        if (i == 0) buf->rowCount = (int)(start - 1) / step + 1;
        int* row = buf->planes[buf->which][i];
        int n = step * 2;
        int* dst = row + start;
        if (n > 0) {
            int* q = dst;
            do { *q = dst[-1]; q++; n--; } while (n != 0);
        }
    }
}
