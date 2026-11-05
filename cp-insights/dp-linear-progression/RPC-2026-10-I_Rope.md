# RPC 2026-10 I - Rope

**Type:** Dynamic Programming / Computational Geometry
**Rating / Context:** Div 1B (RPC 10 2026)
**Tag:** polygon-triangulation-dp-minimum-perimeter

## Key Insight

💡 The shortest closed loop enclosing a point subset is its convex hull; fixing the lowest vertex `p_0` and sorting higher points by CCW polar angle decomposes any polygon into disjoint fan triangles `Delta(p_0, pts[i], pts[j])`, allowing an `O(n^4)` DP over perimeter and enclosed point count.

## Pattern Trigger

"Given `n <= 100` points with no three collinear and rope length `r`, maximize the number of points enclosed inside or on a loop of perimeter `<= r`."

## Breakthrough

Because no 3 points are collinear and all points lie in the upper half-plane of `p_0`, a point `pts[k]` lies strictly inside `Delta(p_0, pts[i], pts[j])` (`i < j`) iff `i < k < j` and `cross(pts[i], pts[j], pts[k]) > 0`.

## Code Spotlight

```cpp
for (int i = 0; i < m; ++i) {
    for (int c = 2; c <= i + 2; ++c) {
        if (dp[i][c] + d0[i] <= r) ans = max(ans, c);
        for (int j = i + 1; j < m; ++j)
            dp[j][c + 1 + inside[i][j]] = min(dp[j][c + 1 + inside[i][j]], dp[i][c] + d[i][j]);
    }
}
```

## Example

Input: `n = 5, r = 9`, points `(2,1), (2,2), (3,3), (1,4), (4,0)`
Output: `4`
Why: A loop of perimeter `<= 9` encloses the 4 points `(2,1), (2,2), (3,3), (1,4)`.

---

**Generated:** 2026-11-04
