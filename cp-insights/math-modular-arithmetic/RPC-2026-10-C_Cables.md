# RPC 2026-10 C - Cables

**Type:** Math / Online Linear Basis
**Rating / Context:** Div 1B (RPC 10 2026)
**Tag:** linear-basis-with-timestamps-gaussian-elimination

## Key Insight

💡 A contiguous range of cable types `[i, j]` admits a non-zero balanced flow iff their net degree vectors `d^(q)_v = indeg(v) - outdeg(v)` are linearly dependent in `R^(n-1)`. Maintain an online Gaussian basis with insertion timestamps `pos[c]` that always keeps the newest independent suffix.

## Pattern Trigger

"Find shortest contiguous subarray `[i, j]` of graphs/vectors over `n <= 100` vertices (`k <= 2 * 10^5`) admitting a non-zero linear combination summing to zero."

## Breakthrough

When inserting vector `j`, whenever `cur_pos > pos[c]`, swap `(vec, cur_pos)` with the basis row `(B[c], pos[c])` and continue reducing the older vector. If it reduces to zero, `cur_pos` is the maximum `i <= j` such that `[i, j]` is linearly dependent.

## Code Spotlight

```cpp
if (cur_pos > pos[c]) {
    uint64_t inv = modInverse(vec[c]);
    for (int col = c; col < dim; ++col) vec[col] = (vec[col] % MOD) * inv % MOD;
    if (pos[c] == 0 || j - pos[c] + 1 >= best_len) { B[c] = move(vec); pos[c] = cur_pos; independent = true; break; }
    swap(vec, B[c]); swap(cur_pos, pos[c]);
}
uint64_t factor = MOD - vec[c];
for (int col = c; col < dim; ++col) vec[col] = (vec[col] + factor * B[c][col]) % MOD;
```

## Example

Input: `n = 3, k = 3`, types with net degree vectors `(-1, 1, 0), (0, -1, 1), (-1, 0, 1)`
Output: `3`
Why: Any 2 vectors are independent, while all 3 satisfy `d^(1) + d^(2) - d^(3) = 0`.

---

**Generated:** 2026-11-04
