# RPC 2026-10 H - Park

**Type:** Graph / Tree Algorithms (Centroid Decomposition)
**Rating / Context:** Div 2D (RPC 10 2026)
**Tag:** centroid-decomposition-path-length-times-max

## Key Insight

💡 Decompose the tree by centroids so every path `u <-> v` through centroid `c` splits into two pairs `(m_u, d_u)` and `(m_v, d_v)`; sorting pairs by path maximum `m` fixes `max(m_i, m_j) = m_j` for all `i < j`, reducing `sum_{i < j} (d_i + d_j) * m_j` to a linear prefix-sum scan.

## Pattern Trigger

"Sum over all paths in a tree (`N <= 10^5`) of `length(P) * max_{v in P} b_v` where path length and path maximum are multiplied together."

## Breakthrough

Combine all subtree rays at centroid `c` to count all pairs in `O(s log s)`, and subtract the same function applied to each child subtree individually to cancel pairs whose path folds inside the same branch.

## Code Spotlight

```cpp
long long calc_pairs(vector<pair<int, int>>& nodes) {
    sort(nodes.begin(), nodes.end());
    long long res = 0, sum_d = 0;
    for (size_t j = 0; j < nodes.size(); ++j) {
        long long m_j = nodes[j].first, d_j = nodes[j].second;
        res = (res + m_j * (((long long)j * d_j + sum_d) % MOD)) % MOD;
        sum_d = (sum_d + d_j) % MOD;
    }
    return res;
}
```

## Example

Input: `N = 3, b = [2, 1, 3]`, edges `(1,2), (2,3)`
Output: `11`
Why: Paths are `(1,2): 1*2 = 2`, `(2,3): 1*3 = 3`, `(1,3): 2*3 = 6`; total `2 + 3 + 6 = 11`.

---

**Generated:** 2026-11-04
