# Librería readline

## ¿Para que sirve la librería readline?
Es una **herramienta para manejar la entrada del usuario en programas C**. Permite leer la entrada del usuario de una manera fácil. Además incluye funciones como:
  - Tener un historial de las entradas.
  - Editar las líneas de entrada.
  - Autocompletado (p.e. con el botón *tab*).
  - etc.

## Installación de la librería
**Para poder utilizar las funciones de la librería**, al no ser una librería que viene por defecto al instalar C (como sí lo hacen *stdio* o *unistd*), **es necesario instalarla**. Con el siguiente comando se instalaran la  biblioteca readline y sus archivos de desarrollo:

```shell
sudo apt install libreadline-dev
```

## Compilación de la librería
Para compilar el código C junto la biblioteca readline, **es necesario vincular la biblioteca con el programa**. Puedes esto añade la flag *-lreadline* al compilar:

```shell
gcc main.c -lreadline
./a.out
```

## Programación con *readline*
```c
// Headers
#include <stdio.h>
#include <readline/readline.h>

// Prototipo
char *readline (const char *prompt);
```
El *string* "prompt" será en texto que aparecerá como prefijo a la linea de entrada que haga el usuario.

### Ejemplo básico
Con este script, el programa estará pudiendo al usuario que introduzca una linea en la terminal para después ser impresa en la propia terminal, hasta que se escriba la palabra "exit".

```c
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

int main(int argc, char const *argv[], char *envp[])
{
	char	*prompt;

	prompt = NULL;
	while (1)
	{
		if (prompt)
		{
			free (prompt);
			prompt = (char *)NULL;
		}
		prompt = readline("Readline input: ");
		if (!prompt || !prompt[0])
			continue;

		printf("\tprompt= %s\n", prompt);

		if (strcmp(prompt, "exit") == 0)
			break ;
	}
	return (0);
}
```

Ejemplo de ejecución:
```shell
Readline input: Test
└───────┬──────┘└─┬┘
        │         └─────> User input
        └───────────────> readline prefix
        prompt= Test
Readline input: this is a line test
        prompt= this is a line test
Readline input: exit
        prompt= exit
```

### Comportamiento de *readline* ante diferentes lineas de entrada
Hay que tener en cuenta que la función *readline* no siempre devuelve una cadena de caracteres. En el siguiente programa se replican 2 casos:
  1. Cuando se detecta una interrupción (Ctr-D), readline devuelve un puntero nulo.
  2. Cuando el valor de entrada es unicamente un salto de linea, readline devuelve un *string* vacío.

```c
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

int main(int argc, char const *argv[], char *envp[])
{
	char	*prompt;

	prompt = NULL;
	while (1)
	{
		if (prompt)
		{
			free (prompt);
			prompt = (char *)NULL;
		}
		prompt = readline("Test: ");
		if (!prompt)
		{
			printf("\tCase 1: Some signal is activated (e.g. ctrl-D).\n", prompt);
			printf("\tprompt = %p\n", prompt);
			return (1);
		}
		if (!prompt[0])
		{
			printf("\tCase 2: An \"intro\" have been pressed.\n", prompt);
			printf("\tprompt = %p, but prompt[0] = %s\n", \
				prompt, prompt[0]);
			continue ;
		}
		printf("\tCase 3: \"readline\" function get the user prompt.\n");
		printf("\tprompt = %s\n", prompt);

		if (strcmp(prompt, "exit") == 0)
			break ;
	}
	return (0);
}
```

Output:
```shell
Test: test
        Case 3: "readline" function get the user prompt.
        prompt = test
Test:
        Case 2: An "intro" have been pressed.
        prompt = 0x564e4baa9460, but prompt[0] = (null)
Test:
        Case 1: Some signal is activated (e.g. ctrl-D).
        prompt = (nil)
```

### Gestión del historial: *add_history* y *rl_clear_history*
Para poder utilizar las funciones relacionadas con la gestión del historial de comandos se tiene que añadir el header `#include <readline/history.h>`. Gracias a la implementación del historial es posible navegar entre los comandos previamente escritos (usando las fechas ↑ o ↓ por ejemplo).

```c
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char const *argv[], char *envp[])
{
	char	*prompt;

	prompt = NULL;
	while (1)
	{
		if (prompt)
		{
			free (prompt);
			prompt = (char *)NULL;
		}
		prompt = readline("Test: ");
		if (!prompt || !prompt[0])
			continue;
		printf("\tprompt = %s\n", prompt);
		add_history (prompt);

		if (strcmp(prompt, "clear") == 0)
			rl_clear_history();

		if (strcmp(prompt, "exit") == 0)
			break ;
	}
	return (0);
}
```

### Otras funciones de interés:
#### *rl_replace_line*
Esta funcíón modifica lo hay dentro del buffer de entrada de la función readline.
El buffer de entrada es la variable `rl_line_buffer`

```c
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

int main(int argc, char const *argv[], char *envp[])
{
	char	*prompt;

	prompt = NULL;
	while (1)
	{
		if (prompt)
		{
			free (prompt);
			prompt = (char *)NULL;
		}
		prompt = readline("Readline input: ");
		if (!prompt || !prompt[0])
			continue;

		printf("\tReadline return = %s\n", prompt);
		printf("\tOld buffer: %s\n", rl_line_buffer);
		rl_replace_line(">>Buffer overwritten<<", 0);
		printf("\tReadline return = %s\n", prompt);
		printf("\tNew buffer: %s\n", rl_line_buffer);

		if (strcmp(prompt, "exit") == 0)
			break ;
	}
	return (0);
}
```

Output:
```shell
Readline input: test
        Readline return = test
        Old buffer: test
        Readline return = test
        New buffer: >>Buffer overwritten<<
Readline input: exit
        Readline return = exit
        Old buffer: exit
        Readline return = exit
        New buffer: >>Buffer overwritten<<
```

#### *rl_redisplay*
Cuando se **detecta una señal de entrada se llama a esta función**. En ella se puede ejecutar lo que se deseé.

```c
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

int main(int argc, char const *argv[], char *envp[])
{
	char	*prompt;

	prompt = NULL;
	while (1)
	{
		if (prompt)
		{
			free (prompt);
			prompt = (char *)NULL;
		}
		prompt = readline("Readline input: ");
		if (!prompt || !prompt[0])
			continue;

		printf("\tprompt= %s\n", prompt);

		if (strcmp(prompt, "exit") == 0)
			break ;
	}
	return (0);
}

void rl_redisplay()
{
	printf(">>redisplay triggered<< Buffer value: %s\n", rl_line_buffer);
}
```

#### *rl_on_new_line*
Cuando se **detecta un salto de línea se llama a esta función**. En ella se puede ejecutar lo que se deseé.

```c
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

int main(int argc, char const *argv[], char *envp[])
{
	char	*prompt;

	prompt = NULL;
	while (1)
	{
		if (prompt)
		{
			free (prompt);
			prompt = (char *)NULL;
		}
		prompt = readline("Readline input: ");
		if (!prompt || !prompt[0])
			continue;

		printf("\tprompt= %s\n", prompt);

		if (strcmp(prompt, "exit") == 0)
			break ;
	}
	return (0);
}

int rl_on_new_line()
{
	printf("\t>>New line flag triggered<<\n");
}
```

Output:
```shell
        >>New line flag triggered<<
        >>New line flag triggered<<
        >>New line flag triggered<<
Readline input: test
        prompt= test
        >>New line flag triggered<<
        >>New line flag triggered<<
Readline input: exit
        prompt= exit
```

## Referencias
  - https://progidea.com/post/how-to-use-the-readline-library-in-linux-c-programming/
  - https://web.mit.edu/gnu/doc/html/rlman_2.html#SEC21
