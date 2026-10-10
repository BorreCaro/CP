# ICPC 2026 M - Byte Flu

**Type:** Graph / Shortest Path
**Rating / Context:** Div 1B / Div 2D (ICPC Colombia 2026)
**Tag:** banded-levenshtein-vertex-cut-dinic-flow

## Key Insight

💡 Prevenir el contagio entre dispositivos infectados y críticos desconectando dispositivos normales de costo `c_i` es un problema canónico de corte mínimo de vértices, resuelto duplicando nodos `(i_{in}, i_{out})` con capacidad `c_i` y evaluando adyacencias mediante DP de Levenshtein en banda `|i-j| <= K`.

## Pattern Trigger

"`N <= 1000` cadenas de longitud `<= 20`, aristas si distancia de edición `<= K <= 20`, costo mínimo para desconectar vértices normales e impedir caminos entre infectados y críticos."

## Breakthrough

Transformar el corte mínimo de vértices con pesos en corte mínimo de aristas duplicando cada nodo normal en un par de entrada/salida conectado con capacidad `c_i`, acelerando las consultas de distancia de edición mediante una banda de ancho `K` con poda temprana.

## Code Spotlight

```cpp
Dinic din(2 * N + 2);
for (int i = 0; i < N; i++) din.add(2 * i, 2 * i + 1, type[i] == 0 ? c[i] : INF);
for (int i = 0; i < N; i++) {
    if (type[i] == 1) din.add(S, 2 * i, INF);
    if (type[i] == 2) din.add(2 * i + 1, T, INF);
}
// si within(s[i], s[j], K): din.add(2*i+1, 2*j, INF); din.add(2*j+1, 2*i, INF);
```

## Example

Input: 5 dispositivos con cadenas de longitud 3, `K = 1`, infectado `aaa`, crítico `bba`.
Output: `11`
Why: Los caminos pasan por `baa` (costo 4) y `aba` (costo 7). Desconectar ambos dispositivos normales bloquea todas las rutas con costo `4 + 7 = 11`.

---

**Generated:** 2026-10-10
