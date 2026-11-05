# RPC 2026-10 A - Accident

**Type:** Math / Computational Geometry
**Rating / Context:** Div 2B (RPC 10 2026)
**Tag:** geometry-orthogonal-projection-thales-circle

## Key Insight

💡 Fixing two vertices `P` and `Q` leaves only three geometric loci for the moving third vertex `R'` to form a right angle: the line through `P` perpendicular to `PQ`, the line through `Q` perpendicular to `PQ`, and the Thales circle with diameter `PQ`.

## Pattern Trigger

"Three non-collinear points in 2D; move exactly one point by minimum Euclidean distance so the triangle becomes right-angled."

## Breakthrough

Instead of optimizing coordinates of `R'`, evaluate the 3 point-to-locus distance formulas directly across all 3 choices of moving vertex (`3 * 3 = 9` checks in `O(1)`). Non-collinearity guarantees no projection ever degenerates onto `P` or `Q`.

## Code Spotlight

```cpp
double pq = hypot(Q.x - P.x, Q.y - P.y);
double dotP = (R.x - P.x) * (Q.x - P.x) + (R.y - P.y) * (Q.y - P.y);
double dotQ = (R.x - Q.x) * (P.x - Q.x) + (R.y - Q.y) * (P.y - Q.y);
Pt M = {(P.x + Q.x) / 2.0, (P.y + Q.y) / 2.0};
ans = min({ans, abs(dotP) / pq, abs(dotQ) / pq, abs(hypot(R.x - M.x, R.y - M.y) - pq / 2.0)});
```

## Example

Input: `(2, 2), (-1, 1), (3, -2)`
Output: `0.600000000`
Why: Moving `(2, 2)` onto the Thales circle or perpendicular line of the opposite segment requires distance `0.6`.

---

**Generated:** 2026-11-04
