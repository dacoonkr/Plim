# Plim

## Type
| TypeName | Range                    |
|----------|--------------------------|
| number   | -2147483648 ~ 2147483647 |
| number   | 8byte floating point     |
| string   | no limit                 |

## Operator

| Priority | Operator | Action              |
|----------|----------|---------------------|
| 1        | a ^ b    | a to the power of b |
| 2        | a * b    | a multi b           |
| 2        | a / b    | a division b        |
| 2        | a % b    | a mod b             |
| 3        | a + b    | a plus b            |
| 3        | a - b    | a minus b           |
| 4        | $a = b   | assign a to b       |

## Basic Function

| Definition                 | Action                    |
|----------------------------|---------------------------|
| print(anytype content)     | print content on console  |
| exit(number n)             | exit with code n          |
| system(string command)     | execute command           |
