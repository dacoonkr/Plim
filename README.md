# Plim

## Build & Run

> 코드 실행: `plim foo.plim`

> 실행 파일 생성: `plim build foo.plim foo.plm`

> 실행 파일 실행: `plim run foo.plm`

## Type
| TypeName | Range                    |
|----------|--------------------------|
| number   | -2147483648 ~ 2147483647 |
| number   | 8byte floating point     |
| string   | no limit                 |

## System Variable
| Variable name | Value                     |
|---------------|---------------------------|
| scanint       | input number(int) value   |
| scanfloat     | input number(float) value |
| scanline      | input string              |

## Operator

| Priority | Operator | Action               |
|----------|----------|----------------------|
| 1        | a ^ b    | a to the power of b  |
| 2        | a * b    | a multi b            |
| 2        | a / b    | a division b         |
| 2        | a % b    | a mod b              |
| 3        | a + b    | a plus b             |
| 3        | a - b    | a minus b            |
| 4        | $a = b   | assign a to b        |
| 4        | a == b   | compare a to b       |
| 4        | $new:$a  | definition variable a|

## Basic Function

| Definition                 | Action                    |
|----------------------------|---------------------------|
| print(anytype content)     | print content on console  |
| exit(number n)             | exit with code n          |
| system(string command)     | execute command           |

## Block

| Syntax                           | Action                                           |
|----------------------------------|--------------------------------------------------|
| if ( expression ) { code }       | if expression is true, run code                  |
| for ( $var_name, st, en )        | set var_name from st to en - 1 and each run code |


## Examples

**Hello World**
```
print("Hello, World!");
```
**A+B**
```
$new:$a = scanint;
$new:$b = scanint;
print(a + b);
```
