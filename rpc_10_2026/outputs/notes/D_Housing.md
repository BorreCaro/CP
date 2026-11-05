# Problema D: Housing

- **Concurso:** RPC 10 (Octubre 31, 2026)
- **Dificultad Estimada:** Media - Alta (Div 2D / Segment Tree + Teorema del Valor Intermedio Discreto)
- **Estado en Concurso:** Upsolved Post-Concurso
- **Archivos de Referencia:**
  - Enunciado: [ProblemsetRPC10.pdf](../../inputs/problemset/ProblemsetRPC10.pdf)
  - Solución: [D_Housing.cpp](../../inputs/solutions/D_Housing.cpp)

---

## 1. Deconstrucción del Enunciado

Dada una permutación `a_1, a_2, ..., a_n` de `{1, 2, ..., n}` (`3 <= n <= 2 * 10^5`), determinar para cada índice `i` si `a_i` es la mediana exacta de algún subarreglo contiguo `a[l..r]` de longitud impar `>= 3` que contenga la posición `i` (`l <= i <= r`).

---

## 2. Pistas en las Restricciones (*Pattern Triggers*)

- **Caracterización de Mediana por Balance `+1 / -1`:** Para un elemento fijo `x = a_i`, si asignamos `+1` a los elementos `> x` y `-1` a los elementos `< x`, entonces `x` es la mediana de `a[l..r]` si y solo si la suma de signos en `[l, i - 1]` más la suma de signos en `[i + 1, r]` es exactamente `0`.
- **Propiedad de Continuidad Discreta (Darboux Discreto):** Como cada paso hacia la izquierda (`l`) o hacia la derecha (`r`) cambia la suma acumulada en `+1` o `-1`, el conjunto de sumas de sufijos no vacíos en `[1, i - 1]` es el intervalo entero continuo `[minL, maxL]`, y el conjunto de sumas de prefijos no vacíos en `[i + 1, n]` es el intervalo entero continuo `[minR, maxR]`.

---

## 3. Técnicas y Conceptos Teóricos

Para que exista un subarreglo `[l, r]` con `r - l + 1 >= 3` y suma total `0`, basta y sobra que se cumpla al menos una de las siguientes cuatro condiciones sobre los extremos `[minL, maxL]` (para `l < i`) y `[minR, maxR]` (para `r > i`):

1. `0 in [minL, maxL]` (`minL <= 0 && maxL >= 0`): existe un sufijo izquierdo `[l, i - 1]` de balance `0` (se toma `r = i`).
2. `0 in [minR, maxR]` (`minR <= 0 && maxR >= 0`): existe un prefijo derecho `[i + 1, r]` de balance `0` (se toma `l = i`).
3. `maxL > 0 && minR < 0`: por continuidad discreta, existe `l < i` con balance `+1` y `r > i` con balance `-1`, cuya suma es `0`.
4. `minL < 0 && maxR > 0`: existe `l < i` con balance `-1` y `r > i` con balance `+1`, cuya suma es `0`.

Al barrer los valores en orden creciente `x = 1, 2, ..., n`, mantenemos un **Segment Tree** donde inicialmente todas las posiciones valen `+1`. En el paso `x` (ubicado en `i = pos[x]`), consultamos `(min_suff, max_suff)` en `[1, i - 1]` y `(min_pref, max_pref)` en `[i + 1, n]`, y luego actualizamos la hoja `i` de `+1` a `-1`.

---

## 4. Estrategia de Implementación Limpia

- **Complejidad Temporal:** `O(n log n)` (una consulta y una actualización puntual por cada `x in [1, n]`).
- **Complejidad Espacial:** `O(n)`.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct Node {
    int sum;
    int min_pref, max_pref;
    int min_suff, max_suff;
};

Node merge_nodes(const Node& L, const Node& R) {
    Node res;
    res.sum = L.sum + R.sum;
    res.min_pref = min(L.min_pref, L.sum + R.min_pref);
    res.max_pref = max(L.max_pref, L.sum + R.max_pref);
    res.min_suff = min(R.min_suff, R.sum + L.min_suff);
    res.max_suff = max(R.max_suff, R.sum + L.max_suff);
    return res;
}

Node make_leaf(int val) {
    return {val, val, val, val, val};
}

int n;
vector<Node> tree;

void build(int node, int l, int r) {
    if (l == r) {
        tree[node] = make_leaf(1);
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    tree[node] = merge_nodes(tree[2 * node], tree[2 * node + 1]);
}

void update(int node, int l, int r, int idx, int val) {
    if (l == r) {
        tree[node] = make_leaf(val);
        return;
    }
    int mid = (l + r) / 2;
    if (idx <= mid) update(2 * node, l, mid, idx, val);
    else update(2 * node + 1, mid + 1, r, idx, val);
    tree[node] = merge_nodes(tree[2 * node], tree[2 * node + 1]);
}

Node query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[node];
    int mid = (l + r) / 2;
    if (qr <= mid) return query(2 * node, l, mid, ql, qr);
    if (ql > mid) return query(2 * node + 1, mid + 1, r, ql, qr);
    return merge_nodes(
        query(2 * node, l, mid, ql, qr),
        query(2 * node + 1, mid + 1, r, ql, qr)
    );
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    vector<int> a(n + 1), pos(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pos[a[i]] = i;
    }

    tree.resize(4 * n + 4);
    build(1, 1, n);

    vector<bool> ans(n + 1, false);

    for (int x = 1; x <= n; ++x) {
        int i = pos[x];
        int minL = INF, maxL = -INF;
        int minR = INF, maxR = -INF;

        if (i > 1) {
            Node left_res = query(1, 1, n, 1, i - 1);
            minL = left_res.min_suff;
            maxL = left_res.max_suff;
        }
        if (i < n) {
            Node right_res = query(1, 1, n, i + 1, n);
            minR = right_res.min_pref;
            maxR = right_res.max_pref;
        }

        bool ok = false;
        if (minL <= 0 && maxL >= 0) ok = true;
        if (minR <= 0 && maxR >= 0) ok = true;
        if (maxL > 0 && minR < 0) ok = true;
        if (minL < 0 && maxR > 0) ok = true;

        ans[i] = ok;
        update(1, 1, n, i, -1);
    }

    for (int i = 1; i <= n; ++i) {
        cout << (ans[i] ? "YES" : "NO") << (i == n ? "" : " ");
    }
    cout << "\n";
    return 0;
}
```
