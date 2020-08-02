# Plim

## 빌드와 실행

> 코드 실행: `plim foo.plim`

> 실행 파일 생성: `plim build foo.plim foo.plm`

> 실행 파일 실행: `plim run foo.plm`

## 타입

| 타입 이름 | 범위                     |
|----------|--------------------------|
| number   | 8바이트 부동소수점         |
| string   | 제한 없음                 |

## 예약어

| 예약어 이름    | 설명                      |
|---------------|---------------------------|
| scanint       | 정수 값을 입력             |
| scanfloat     | 실수 값을 입력             |
| scanline      | 문자열 한 줄을 입력        |

## 연산자

| 우선순위  | 문법     | 설명                  |
|----------|----------|----------------------|
| 1        | a ^ b    | a의 b제곱             |
| 2        | a * b    | a 곱하기 b            |
| 2        | a / b    | a 나누기 b            |
| 2        | a % b    | a 나누기 b 의 나머지   |
| 3        | a + b    | a 더하기 b            |
| 3        | a - b    | a 빼기 b              |
| 4        | a == b   | a와 b가 같은지 비교    |
| 4        | a != b   | a와 b가 다른지 비교    |
| 4        | a < b    | b가 a보다 큰 지 비교   |
| 4        | a > b    | a가 b보다 큰 지 비교   |
| 4        | a <= b   | b가 a보다 크거나 같은지 비교   |
| 4        | a >= b   | a가 b보다 크거나 같은지 비교   |
| 5        | a && b   | a와 b가 둘 다 참인지 확인   |
| 6        | a \|\| b   | a와 b중 하나라도 참인지 확인   |
| 7        | $a = b   | 변수 a에 b의 값 대입   |
| 7        | new : $a  | 새로운 a변수 생성      |
| 7        | const : $a = b  | 값이 변하지 않는 새로운 a변수 생성, b로 초기화    |

## 기본 함수

| 사용법                      | 설명                      |
|----------------------------|---------------------------|
| print(anytype content)     | 콘솔에 content를 출력      |
| exit(number n)             | n코드로 종료               |
| system(string command)     | command를 실행 (CMD)      |

## 블럭

| 문법                             | 설명                                           |
|----------------------------------|--------------------------------------------------|
| if ( expression ) { code }       | 만약 expression이 참이면 code실행                  |
| while ( expression ) { code }       | expression이 참인 동안 code실행                  |
| for ( $var_name, st, en ) { code } | var_name을 st부터 en-1까지 각각 다 넣어 보며 코드 실행 |


## 예제

**Hello World**
```
print("Hello, World!");
```
**A+B**
```
new:$a = scanint;
new:$b = scanint;
print(a + b);
```
**1부터 100까지의 소수**
```
new:$a=0-1;
new:$b
new:$c
print("2 ")
for($a, 2, 100){
    $c=1
    $b=0-1
    for($b,2,a) {
        if(a%b==0) {
            $c=0
        }
    }
    if(c==1){ print(a," ") }
}
```
