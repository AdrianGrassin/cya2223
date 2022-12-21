# PRACTICA 11 - ALGORITMOS VORACES

---

Autor: [Adrian Grassin](https://github.com/AdrianGrassin)\
Asignatura: [Computabilidad y Algoritmia](https://campusingenieriaytecnologia2223.ull.es/mod/assign/view.php?id=18101)

---

## REQUISITOS FUNCIONALES MINIMOS

- [x] Dada una cierta cantidad **N**, devolver el conjunto de monedas que sumen **N**
   


El programa realizado ha de ejecutarse indicando en la línea de comandos la cantidad n (numero real). Debe emitir como resultado el conjunto de monedas y número total de monedas en la solución.

```bash
$ monedas <n>
Solución: <conjunto_de_moneda>
Total monedas: <número_total_de_monedas>
```

---
## REQUISITOS FUNCIONALES OPCIONALES

- [x] Devolver el cambio **contando el número de monedas de cada tipo**.
  + Por ejemplo, si n = 7,98€, el cambio devuelto será S = {3×2€, 1€, 50¢, 2×20¢, 5¢, 2¢, 1¢}.
- [x] Considerar tanto **monedas** como **billetes** utilizando la **opción -b**.
- [x] Diseñar un nuevo **algoritmo más eficiente**, con orden de complejidad **O(m)**
