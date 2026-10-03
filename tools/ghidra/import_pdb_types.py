# @runtime PyGhidra
# Import explicit-offset type layouts (from tools/pdb_types.py) into the program's data type manager.
# Linear time: every struct is created as a NON-PACKED fixed-size shell first, then members are placed
# directly at their PDB offsets (no repacking), avoiding Ghidra's quadratic PDB composite reconstruction.
# Args: <types.json> [<root category, default /DevPDB>]
import json, re, time
from ghidra.program.model.data import (CategoryPath, StructureDataType, UnionDataType, EnumDataType, PointerDataType,
    ArrayDataType, DataTypeConflictHandler, CharDataType, UnsignedCharDataType, ShortDataType, UnsignedShortDataType,
    IntegerDataType, UnsignedIntegerDataType, LongLongDataType, UnsignedLongLongDataType, FloatDataType,
    DoubleDataType, BooleanDataType, WideChar16DataType, WideChar32DataType, VoidDataType, Undefined4DataType)

args = getScriptArgs()
data = json.load(open(args[0]))
root = args[1] if len(args) > 1 else "/DevPDB"
dtm = currentProgram.getDataTypeManager()
t0 = time.time()

PRIM = {"char": CharDataType.dataType, "uchar": UnsignedCharDataType.dataType, "short": ShortDataType.dataType,
        "ushort": UnsignedShortDataType.dataType, "int": IntegerDataType.dataType, "uint": UnsignedIntegerDataType.dataType,
        "long": IntegerDataType.dataType, "ulong": UnsignedIntegerDataType.dataType, "longlong": LongLongDataType.dataType,
        "ulonglong": UnsignedLongLongDataType.dataType, "float": FloatDataType.dataType, "double": DoubleDataType.dataType,
        "bool": BooleanDataType.dataType, "wchar_t": WideChar16DataType.dataType, "char16_t": WideChar16DataType.dataType,
        "char32_t": WideChar32DataType.dataType, "void": VoidDataType.dataType, "HRESULT": IntegerDataType.dataType}

def split_name(full):
    parts, depth, cur = [], 0, ""
    i = 0
    while i < len(full):
        c = full[i]
        if c in "<(": depth += 1
        elif c in ">)": depth -= 1
        if depth == 0 and full.startswith("::", i):
            parts.append(cur); cur = ""; i += 2; continue
        cur += c; i += 1
    parts.append(cur)
    clean = lambda s: re.sub(r"[/\\]", "_", s)[:200] or "_"
    return CategoryPath(root + "".join("/" + clean(p) for p in parts[:-1])), clean(parts[-1])

shells = {}
tx = currentProgram.startTransaction("import pdb types")
try:
    # pass 1: shells
    for name, s in data["structs"].items():
        cat, short = split_name(name)
        dt = UnionDataType(cat, short, dtm) if s["kind"] == "union" else StructureDataType(cat, short, max(s["size"], 0), dtm)
        shells[name] = dtm.addDataType(dt, DataTypeConflictHandler.REPLACE_HANDLER)
    for name, e in data["enums"].items():
        cat, short = split_name(name)
        ed = EnumDataType(cat, short, e["size"] if e["size"] in (1, 2, 4, 8) else 4, dtm)
        seen = set()
        for n, v in e["values"]:
            if n in seen: continue
            seen.add(n)
            try:
                ed.add(n, v & ((1 << (8 * ed.getLength())) - 1))
            except Exception:
                pass
        shells["enum:" + name] = dtm.addDataType(ed, DataTypeConflictHandler.REPLACE_HANDLER)
    println("shells: %d in %.1fs" % (len(shells), time.time() - t0))

    def resolve(d):
        if d.startswith("prim:"): return PRIM.get(d[5:], Undefined4DataType.dataType)
        if d.startswith("ptr:"):
            inner = d[4:]
            return PointerDataType(resolve(inner) if not inner.startswith("func") else VoidDataType.dataType, 4, dtm)
        if d.startswith("arr:"):
            _, cnt, esz, inner = d.split(":", 3)
            el = resolve(inner)
            cnt, esz = int(cnt), int(esz)
            if el is None or cnt <= 0 or esz <= 0: return None
            return ArrayDataType(el, cnt, esz, dtm)
        if d.startswith("struct:"): return shells.get(d[7:])
        if d.startswith("enum:"): return shells.get("enum:" + d[5:])
        if d == "func": return VoidDataType.dataType
        return None

    placed = failed = 0
    for name, s in data["structs"].items():
        st = shells[name]
        if s["kind"] == "union":
            for n, off, d, bp, bl, sz in s["members"]:
                dt = resolve(d)
                try:
                    st.add(dt if dt else Undefined4DataType.dataType, max(sz, 1), n, None); placed += 1
                except Exception:
                    failed += 1
            continue
        if s["vfptr"] and not s["bases"]:
            try: st.replaceAtOffset(0, PointerDataType(VoidDataType.dataType, 4, dtm), 4, "vftable", None)
            except Exception: pass
        for d, off, sz in s["bases"]:
            dt = resolve(d)
            if dt is None or sz <= 0: continue
            try:
                st.replaceAtOffset(off, dt, sz, "base_" + d.split(":", 1)[1].split("::")[-1][:60], None); placed += 1
            except Exception:
                failed += 1
        for n, off, d, bp, bl, sz in s["members"]:
            dt = resolve(d)
            try:
                if bl is not None:
                    st.insertBitFieldAt(off, max(sz, 1), bp, dt if dt else IntegerDataType.dataType, bl, n, None)
                elif dt is not None and sz > 0:
                    st.replaceAtOffset(off, dt, sz, n, None)
                else:
                    continue
                placed += 1
            except Exception:
                failed += 1
finally:
    currentProgram.endTransaction(tx, True)
println("import_pdb_types: %d types, %d members placed, %d failed, %.1fs" % (len(shells), placed, failed, time.time() - t0))
