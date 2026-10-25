.functions[] | select(.name|test("cIVisualEffect.*sp_vector_allocator.*operator=")) | "\(.va) \(.name)"
