# Problema A: Accident

- **Concurso:** RPC 10 (Octubre 31, 2026)
- **Dificultad Estimada:** Fácil - Media (Div 2B / Geometría)
- **Estado en Concurso:** Upsolved Post-Concurso
- **Archivos de Referencia:**
  - Enunciado: [ProblemsetRPC10.pdf](../../inputs/problemset/ProblemsetRPC10.pdf)
  - Solución: [A_Accident.cpp](../../inputs/solutions/A_Accident.cpp)

---

## 1. Deconstrucción del Enunciado

Se entregan tres puntos no colineales `A, B, C` en el plano con coordenadas enteras en `[-100, 100]`. Se desea desplazar **exactamente uno** de los tres vértices la menor distancia euclidiana posible de modo que el triángulo resultante sea rectángulo y no degenerado.

---

## 2. Pistas en las Restricciones (*Pattern Triggers*)

- **Solo 3 puntos fijos y 1 vértice móvil:** Existen únicamente `3` elecciones para el vértice móvil `R` (dejando fijos los otros dos vértices `P` y `Q`), y para cada elección existen exactamente `3` vértices donde puede ubicarse el ángulo de `90` grados (`P`, `Q` o el nuevo punto `R'`). Esto reduce el problema continuo a evaluar `3 * 3 = 9` lugares geométricos elementales en `O(1)`.
- **Garantía de no colinealidad:** Al no ser colineales `P, Q, R`, la proyección ortogonal de `R` sobre las rectas perpendiculares en `P` o `Q`, así como la proyección radial de `R` sobre la circunferencia de diámetro `PQ`, jamás colapsan sobre `P` ni `Q`, evitando triángulos degenerados.

---

## 3. Técnicas y Conceptos Teóricos

Si fijamos el segmento `PQ` y movemos el tercer vértice `R` hacia `R'`:

1. **Ángulo recto en `P` (`PR' perp PQ`):**
   El lugar geométrico de `R'` es la recta `L_P` que pasa por `P` y es perpendicular al vector `PQ`. Como `PQ` es el vector normal a `L_P`, la distancia mínima desde `R` hasta `L_P` es la magnitud de la proyección escalar de `R - P` sobre `Q - P`:
   `dist(R, L_P) = |dot(R - P, Q - P)| / |Q - P|`

2. **Ángulo recto en `Q` (`QR' perp PQ`):**
   Análogamente, el lugar geométrico de `R'` es la recta `L_Q` que pasa por `Q` perpendicular a `PQ`:
   `dist(R, L_Q) = |dot(R - Q, P - Q)| / |P - Q|`

3. **Ángulo recto en `R'` (`PR' perp QR'`):**
   Por el **Teorema de Thales**, el conjunto de puntos `R'` desde los cuales el segmento `PQ` se observa bajo un ángulo de `90` grados es la circunferencia con centro en el punto medio `M = (P + Q) / 2` y radio `rad = |P - Q| / 2`. La distancia mínima desde `R` hasta dicha circunferencia a lo largo del rayo `MR` es:
   `dist(R, Circ) = ||R - M| - rad|`

---

## 4. Estrategia de Implementación Limpia

- **Complejidad Temporal:** `O(1)` (9 evaluaciones geométricas directas).
- **Complejidad Espacial:** `O(1)`.

```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Pt {
    double x, y;
};

double dist(Pt a, Pt b) {
    return hypot(a.x - b.x, a.y - b.y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Pt p[3];
    if (!(cin >> p[0].x >> p[0].y)) return 0;
    cin >> p[1].x >> p[1].y;
    cin >> p[2].x >> p[2].y;

    double ans = 1e18;

    for (int i = 0; i < 3; ++i) {
        Pt R = p[i];
        Pt P = p[(i + 1) % 3];
        Pt Q = p[(i + 2) % 3];

        double pq = dist(P, Q);

        // 1. Ángulo recto en P
        double dotP = (R.x - P.x) * (Q.x - P.x) + (R.y - P.y) * (Q.y - P.y);
        ans = min(ans, abs(dotP) / pq);

        // 2. Ángulo recto en Q
        double dotQ = (R.x - Q.x) * (P.x - Q.x) + (R.y - Q.y) * (P.y - Q.y);
        ans = min(ans, abs(dotQ) / pq);

        // 3. Ángulo recto en R' (Circunferencia de Thales)
        Pt M = {(P.x + Q.x) / 2.0, (P.y + Q.y) / 2.0};
        double rad = pq / 2.0;
        ans = min(ans, abs(dist(R, M) - rad));
    }

    cout << fixed << setprecision(9) << ans << "\n";
    return 0;
}
```
