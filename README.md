# TrazaVar
Este proyecto busca desarrollar un algoritmo para optimizar el corte y el trazado de varillas de materiales diversos (acero, hierro, aluminio, madera, tuberías, etc.) con el fin de cubrir el perímetro de estructuras o perímetros de superficies definidas. Utilizando varillas de tamaño estándar, el algoritmo maximiza el uso del material y minimiza el desperdicio, proporcionando una solución eficiente y económica para ajustar el material al contorno requerido.

El algoritmo fué diseñado después del curso de Análisis y Desarrollo de Algoritmos, el cuál ayudó a establecer bases teóricas para el desarrollo e implementación del mismo.

## 1. **Ejemplos de Uso**
Construcción: El algoritmo puede aplicarse en la instalación de cercas perimetrales, ajustando varillas de acero a lo largo de terrenos irregulares, o en la fabricación de marcos metálicos para maquinaria y estructuras.

Carpintería: En proyectos de carpintería, el algoritmo facilita el corte preciso de madera para enmarcar áreas específicas, optimizando el uso del material y reduciendo el desperdicio.

Fontanería y Tubos: En la instalación de sistemas de tuberías, el algoritmo ayuda a planificar el corte y la disposición de tuberías para cubrir perímetros de áreas con un ajuste eficiente y minimización de desperdicios.

## 2. **Funcionalidad Abstracta**
El algoritmo implementado solicita diversos valores de entrada para la obtención detallada de información relevante al trazo de cortes. A continuación se presenta la información requerida y brindada por el presente algoritmo.

### 2.1. **Requisitos de Entrada**
El algoritmo requiere los siguientes valores:
 - Longitud de la varilla principal: La longitud de la barra estándar en la que se trabaja el material escogido.
 - Lista de logitud de cortes pedidos: Los cortes que se requieren y deben realizar en la varilla principal para completar el pedido. Se solicita un tamaño de corte y la cantidad de ese tipo de corte.
 - Longitud mínima de retazo útil: Al realizar cortes en una varilla, quedan retazos que se pueden volver a utiizar en otros pedidos.
 - Longitud máxima de residuo a desechar: Al realizar cortes en una varilla, quedan piezas demasiado pequeñas que no se pueden volver a utilizar en otros pedidos.

> Se define _Longitud mínima de retazo útil_ y _Longitud máxima de residuo_ puesto que el rango de medidas entre ambos valores se consideran medidas que no pueden ser reutilizadas pero desperdician material lo que no 

### 2.2. **Valores de Salida**
El algoritmo retorna los siguientes valores:
 - Cantidad mínima de varillasprincipales necesarias
 - Cantidad de cada varilla pedida a cortar en cada varilla principal

## 3. **Consideraciones de Rendimiento**
Debido que el algoritmo utiliza recursividad para la exploración de combinaciones posibles de 2 niveles, posee complejidad temporal exponencial respecto a la cantidad de pedidos de cortes que se solicitan.

Debido a la búsqueda y posterior almacenamiento no suficientemente ordenado de las combinaciones del nivel 1 es que la búsqueda se realiza de manera poco óptima.

## 5. **Manejo de Errores**
Aún no se ha implementado manejo de errores ante entradas inesperadas.

## 6. **Detalles Tecnicos (Desarrolladores)**
El algoritmo utiliza recursividad para realizar una búsqueda exhaustiva de las posibles combinaciones de los cortes pedidos en una cantidad variada de varillas principales en 2 niveles.
 - Nivel 1: Se encarga a buscar todas las combinaciones posibles de cortes en una varilla, ordenandolos según el residuo de la combinación.
 - Nivel 2: Se encarga de buscar las combinaciones de nivel 1, comenzando desde las que tienen menor residuo, aquellas que permiten completar el pedido y contabilizando el residuo de cada combinación en una sola combinación de nivel 2.

## 7. **Bitácora de diseño y desarrollo**
 - 2023-01-xx: Se comienza a diseñar el algoritmo y posteriormente a implementarlo en el lenguaje de programación C.
 - 2023-01-07: Primeros resultados del algoritmo. El algoritmo puede calcular las dimensiones requeridas en un ejemplo simple de cortes de varillas de aluminio.
 - 2023-01-08: Primeros errores del algoritmo. El algoritmo contiene errores en los primeros resultados obtenidos que no permite optimizar correctamente los cortes ante una lista grande de medidas de corte.
 - 2023-01-22: Proyecto en descanso. Debido a falta de tiempo se pausa el desarrollo y mejora de los errores encontrados en el algoritmo, el algoritmo queda guardado en un dispositivo de almacenamiento para su futura mejora.
 - 2024-07-28: Documentación. El algoritmo pasa por un proceso de documentación para su debido mantemiento, se planea realizar diferentes buenas prácticas como diseño de pruebas de software, programación funcional, e investigación (la investigación se realizará despues que el algoritmo se optimice a un nivel aceptable). La aceptabilidad está definida por:
   * Optimización del tiempo de respuesta: El tiempo de respuesta es bastante amplio debido a la recursividad que incrementa exponencialmente la complejidad algorítmica.
   * Buenas prácticas: Programación funcional para mejor entendimiento del código, y automatización de pruebas de software para poder acelerar el desarrollo
 - 2024-07-29: Github. El proyecto es subido a github en la cuenta AntonyBlanco que es utilizada para proyectos de la universidad.