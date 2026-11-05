# RPC 2026-10 G - Nightmare

**Type:** Graph / Connectivity (DSU)
**Rating / Context:** Div 2B (RPC 10 2026)
**Tag:** bicolored-graph-single-color-cycle-dsu

## Key Insight

💡 A bicolored graph contains a simple cycle with **exactly one** edge of color `c` iff some edge `(u, v)` of color `c` has its endpoints connected in the subgraph of color `1 - c`.

## Pattern Trigger

"Check whether every simple cycle in a 2-colored graph is either monochromatic or contains at least 2 edges of each color."

## Breakthrough

Do not enumerate cycles with DFS; build two DSUs (`d0` for color 0, `d1` for color 1) and verify that no edge `(u, v, c)` satisfies `d_{1-c}.same(u, v)`.

## Code Spotlight

```cpp
for (const auto& e : edges) {
    if (e.c == 0) d0.unite(e.u, e.v);
    else d1.unite(e.u, e.v);
}
for (const auto& e : edges) {
    if ((e.c == 0 && d1.same(e.u, e.v)) || (e.c == 1 && d0.same(e.u, e.v)))
        return cout << "NO\n", 0;
}
```

## Example

Input: Triangle with 2 red edges `(0,1), (1,2)` and 1 blue edge `(0,2)`
Output: `NO`
Why: Blue edge `(0,2)` has endpoints connected in the red DSU.

---

**Generated:** 2026-11-04
