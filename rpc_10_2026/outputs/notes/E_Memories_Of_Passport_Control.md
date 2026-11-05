# Problema E: Memories of Passport Control

- **Concurso:** RPC 10 (Octubre 31, 2026)
- **Dificultad Estimada:** Muy Fácil (Div 3A / Div 2A)
- **Estado en Concurso:** Resuelto en Vivo (AC)
- **Archivos de Referencia:**
  - Enunciado: [ProblemsetRPC10.pdf](../../inputs/problemset/ProblemsetRPC10.pdf)
  - Solución del Equipo: [E_Memories_Of_Passport_Control.cpp](../../inputs/solutions/E_Memories_Of_Passport_Control.cpp)

---

## 1. Insight Clave

💡 Para minimizar la cantidad de viajes que suman exactamente `s` páginas selladas cuando cada viaje sella `k` páginas o `1` página, el algoritmo voraz toma el máximo número posible de paquetes de tamaño `k` (`floor(s / k)`) y cubre el residuo con viajes unitarios (`s % k`), dando `(s / k) + (s % k)` en `O(1)`.

---

## 2. Análisis de la Solución en Vivo

La solución enviada durante la competencia (`Memories.cpp`) fue directa e impecable:
- Calculó el cociente entero `a = s / k` y le sumó el resto `s % k`.
- Con `2 <= k <= 50` y `1 <= s <= 50`, no existe riesgo de desbordamiento ni casos borde degenerados.

---

## 3. Patrón de Recurrencia / Sesgo Cognitivo

- **Cambio de Monedas Canónico (*Canonical Coin Change*):** Cuando el sistema de denominaciones consiste únicamente en `{1, k}`, el enfoque voraz es óptimo para cualquier `s >= 1` porque `k` viajes de tamaño `1` pueden reemplazarse exactamente por `1` viaje de tamaño `k` reduciendo el conteo total en `k - 1 > 0`.

---

## 4. Lógica Correcta & Código Limpio

- **Complejidad Temporal:** `O(1)`.
- **Complejidad Espacial:** `O(1)`.

```cpp
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k, s;
    if (cin >> k >> s) {
        cout << (s / k) + (s % k) << "\n";
    }
    return 0;
}
```
