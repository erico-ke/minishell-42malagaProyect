# minishell-42malagaProyect


Este proyecto es parte del currículo de la Escuela 42 (Fundación Telefónica). El objetivo de **minishell** es replicar el comportamiento básico de un shell Unix, permitiendo al estudiante entender cómo funciona la ejecución de comandos, los procesos, la gestión de señales y el parsing de entradas.

---

## 🛠 Objetivo del proyecto

Recrear una versión simplificada del shell de Unix, implementando:

- Ejecución de comandos con rutas relativas y absolutas.
- Pipes (`|`) entre múltiples comandos.
- Redirecciones de entrada/salida (`>`, `>>`, `<`, `<<`).
- Manejo de variables de entorno (`env`, `$VAR`, etc.).
- Implementación de comandos *built-in* como:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Gestión adecuada de señales (`SIGINT`, `SIGQUIT`, etc.).
- Manejo correcto de errores y códigos de salida.

> Este proyecto **no** incluye la parte bonus (wildcards, separadores lógicos, etc.).

---

## ✅ Requisitos

- Compilar usando `cc` con las siguientes flags recomendadas:
  ```bash
  cc -Wall -Wextra -Werror

* Ejecutar con:

  ```bash
  ./minishell
  ```

---

## 🚫 Limitaciones

* No se puede usar `system()`.
* Solo se pueden usar funciones permitidas por las normas del proyecto.
* No se pueden usar bibliotecas externas.

---

## 🧪 Ejemplos de uso

```bash
$> echo hola mundo
hola mundo

$> export VAR=42
$> echo $VAR
42

$> ls | grep minishell > salida.txt

$> cat << EOF
> Esto es una prueba
> EOF
Esto es una prueba
```

---

## 🙏 Agradecimientos

Gracias especiales a mi compañero **fracurul** por su ayuda, guía y apoyo durante el desarrollo de este proyecto. Su conocimiento y disposición fueron clave para completar esta minishell.

---

## 📜 Licencia

Este proyecto es de carácter educativo como parte del programa 42. No está destinado a distribución comercial.

```

---

```
