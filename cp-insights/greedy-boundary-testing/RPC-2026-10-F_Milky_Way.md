# RPC 2026-10 F - Milky way

**Type:** Data Structures / Prefix Sums
**Rating / Context:** Div 2A (RPC 10 2026)
**Tag:** prefix-sum-adjacent-drops-monotonicity

## Key Insight

💡 A subarray `a[l..r]` is non-decreasing iff it contains zero adjacent drops (`a[i] < a[i - 1]` for `i in [l + 1, r]`), which is checked in `O(1)` via a prefix sum array `diff[r] == diff[l]`.

## Pattern Trigger

"Answer `q <= 10^5` range queries asking whether `a[l..r]` is sorted in non-decreasing order."

## Breakthrough

When indexing 1-based (`1 .. n`), allocate `diff(n + 1, 0)` (never `diff(n)`, which causes out-of-bounds access at `diff[n]`) and start accumulating drops at `i = 2`.

## Code Spotlight

```cpp
vector<int> diff(n + 1, 0);
for (int i = 2; i <= n; ++i)
    diff[i] = diff[i - 1] + (a[i] < a[i - 1]);
while (q--) {
    int l, r; cin >> l >> r;
    cout << (diff[l] == diff[r] ? "YES\n" : "NO\n");
}
```

## Example

Input: `a = [1, 3, 2, 4, 6]`, query `(3, 5)`
Output: `YES`
Why: `diff = [0, 0, 0, 1, 1, 1]`, so `diff[5] == diff[3] == 1`.

---

**Generated:** 2026-11-04
