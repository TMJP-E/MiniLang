# MiniLang

Analizador léxico y sintáctico para el proyecto final de la asignatura Teoría de la Computación.

## Requerimientos

### Condiciones del lenguaje

#### 1. Palabras reservadas

```none
begin - Inicia el lenguaje, debe existir como linea separada.
end - Termina el lenguaje, debe existir como linea separada.
if
else
while
print
```

#### 2. Operadores

```none
Aritmeticos: + - * / =
Relacionales: < <= > >= == !=
Delimitadores: ( ) { } ;
```

#### 3. Identificadores

Unicamente se puede inicializar variables, usando el operador `=`, posteriormente se pueden llamar.

```none
[A-Za-z_][A-Za-z0-9_]*
```

#### 4. Numeros

Solo se permiten numeros enteros.

```none
[+-]*[0-9][0-9]*
```

#### 5. Cadenas

```none
"[A-Za-z0-9!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~]*"
```

### Forma de Backus-Naur que representa la gramatica

```none
<programa> ::= begin <lista_sentencias> end

<lista_sentencias> ::= <sentencia> <lista_sentencias> | ε

<sentencia> ::= <asignacion>
                | <if>
                | <while>
                | <print>

<asignacion> ::= id = <expresion> ;

<if> ::= if ( <expresion> ) { <lista_sentencias> }
        | if ( <expresion> ) { <lista_sentencias> } else { <lista_sentencias> }

<while> ::= while ( <expresion> ) { <lista_sentencias> }

<print> ::= print ( <expresion> ) ;

<expresion> ::= <termino>
            | <expresion> + <termino>
            | <expresion> - <termino>

<termino> ::= <factor>
            | <termino> * <factor>
            | <termino> / <factor>

<factor> ::= id
            | numero
            | ( <expresion> )
            | <factor> < <factor>
            | <factor> > <factor>
            | <factor> <= <factor>
            | <factor> >= <factor>
            | <factor> == <factor>
            | <factor> != <factor>
```

## Implementacion

El lenguaje se implemento utilizando C, el archivo `minilang.c` solo evalua si el archivo ingresado mediante la linea de comandos, es valido, dentro de la gramatica para MiniLang.

Las 4 funcionalidades principales son puestas a prueba en los archivos dentro de la carpeta `tests`.

Para compilar, ejecute el siguiente comando, dependiendo su sistema:

```bash
#Dentro de la carpeta src/

# Linux
gcc main.c lexer.c parser.c -o minilang.out
# gcc puede ser reemplazado por el compilador de su eleccion.
# Por razones de compatibilidad, no podemos compilarlo para todos los sistemas.
```

Para ejecutarlo, se tiene que indicar la direccion de un archivo de texto en la linea de comando.

```bash
# Ejemplo para las pruebas
./minilang.out ./../tests/assignment.mini
```
