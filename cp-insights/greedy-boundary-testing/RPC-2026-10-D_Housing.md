# RPC 2026-10 D - Housing

**Type:** Data Structures / Discrete Continuity
**Rating / Context:** Div 2D (RPC 10 2026)
**Tag:** median-sweep-segment-tree-discrete-ivt

## Key Insight

💡 Under `+1 / -1` encoding relative to `x = a_i`, suffix sums on `[1, i - 1]` and prefix sums on `[i + 1, n]` change by `+-1` per step, so their achieved values form contiguous integer intervals `[minL, maxL]` and `[minR, maxR]`. Thus `a_i` is the median of some subarray of length `>= 3` iff `0 in [minL, maxL]`, `0 in [minR, maxR]`, `(maxL > 0 && minR < 0)`, or `(minL < 0 && maxR > 0)`.

## Pattern Trigger

"For every element `a_i` in a permutation of size `n <= 2 * 10^5`, decide if `a_i` is the exact median of some odd-length subarray `[l, r]` of length `>= 3` containing `i`."

## Breakthrough

Because step sizes are `+-1` (Discrete Intermediate Value Theorem), you never need to check parity or individual sums: tracking only `min/max` prefix and suffix sums in a Segment Tree while sweeping `x = 1..n` (flipping `pos[x]` from `+1` to `-1`) solves all indices in `O(n log n)`.

## Code Spotlight

```cpp
Node L = query(1, 1, n, 1, i - 1), R = query(1, 1, n, i + 1, n);
bool ok = (L.min_suff <= 0 && L.max_suff >= 0) ||
          (R.min_pref <= 0 && R.max_pref >= 0) ||
          (L.max_suff > 0 && R.min_pref < 0) ||
          (L.min_suff < 0 && R.max_pref > 0);
ans[i] = ok;
update(1, 1, n, i, -1);
```

## Example

Input: `n = 4, a = [2, 4, 1, 3]`
Output: `YES NO NO YES`
Why: `2` is median of `[2, 4, 1]` and `3` is median of `[4, 1, 3]`.

---

**Generated:** 2026-11-04
