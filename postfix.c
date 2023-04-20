#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

typedef enum  //우선순위에 대한 구조체
{
    lparen = 0, /* ( 왼쪽 괄호 */
    rparen = 9, /* ) 오른쪽 괄호*/
    times = 7,  /* * 곱셈 */
    divide = 6, /* / 나눗셈 */
    plus = 5,   /* + 덧셈 */
    minus = 4,  /* - 뺄셈 */
    operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];  //infix 배열
char postfixExp[MAX_EXPRESSION_SIZE];  //postfix 배열
char postfixStack[MAX_STACK_SIZE];  //postfix 스택 배열
int evalStack[MAX_STACK_SIZE];  //계산 스택배열
int postfixStackTop = -1;  //postfix 스택의 탑은 -1로 초기화
int evalStackTop = -1;  //계산 스택의 탑은 -1로 초기화
int evalResult = 0;  //계산 결과

//함수 선언
void postfixPush(char x);  
char postfixPop();
void evalPush(int x); 
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char *c);
void toPostfix(); 
void debug(); 
void reset(); 
void evaluation(); 

int main()
{
    printf("김민서 2022040010\n");
    char command;
    do
    {
        printf("----------------------------------------------------------------\n");
        printf(" Infix to Postfix, then Evaluation\n");
        printf("----------------------------------------------------------------\n");
        printf(" Infix=i, Postfix=p, Eval=e, Debug=d, Reset=r,Quit=q \n");
        printf("----------------------------------------------------------------\n");
        printf("Command = ");
        scanf(" %c", &command);
        
        //command 값에 따른 케이스
        switch(command) {
            case 'i':
            case 'I':
                getInfix();
                break;
            case 'p':
            case 'P':
                toPostfix();
                break;
            case 'e':
            case 'E':
                evaluation();
                break;
            case 'd':
            case 'D':
                debug();
                break;
            case 'r':
            case 'R':
                reset();
                break;
            case 'q':
            case 'Q':
                break;
            default:
            printf("\n >>>>> Concentration!! <<<<<\n");
            break;  
        }
    } 
    while (command != 'q' && command != 'Q');
        return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;  //postfix 스택 배열에 x값 push
}

char postfixPop()
{
    char x;
    if (postfixStackTop == -1)  //아직 스택이 쌓인게 없으면
        return '\0';
    else  //아니면 스택에 쌓여있던 거 pop
    {
        x = postfixStack[postfixStackTop--];
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x;  //계산 스택 배열에 x값 push
}

int evalPop()
{
    if (evalStackTop == -1)  //아직 스택이 쌓인게 없으면
        return -1;
    else  //아니면 스택에 쌓여있던 거 pop
        return evalStack[evalStackTop--];
}

void getInfix()  //infix 입력
{
    printf("Type the expression >>> ");
    scanf("%s", infixExp);
}

precedence getToken(char symbol)
{
    switch (symbol)  //우선순위 구조체에 있던 내용에 따른 숫자를 연산자에 붙여줌(연산자에도 우선순위 생김)
    {
        case '(': return lparen;
        case ')': return rparen;
        case '+': return plus;
        case '-': return minus;
        case '/': return divide;
        case '*': return times;
        default: return operand;
    }
}

precedence getPriority(char x) 
{
    return getToken(x);
}

void charCat(char *c)
{
    if (postfixExp == '\0')  //비어있으면
        strncpy(postfixExp, c, 1);  //c를 복사해서 postfixExp에 넣음
    else  //아니면
        strncat(postfixExp, c, 1);  //postfix에 c 문자 하나 붙음
}
/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
    /* infixExp의 문자 하나씩을 읽기위한 포인터 */
    char *exp = infixExp;
    char x; /* 문자하나를 임시로 저장하기 위한 변수 */
    /* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
    while (*exp != '\0')  //배열이 null이 아닌 조건에서 반복문 시작
    {
        if (getPriority(*exp) == operand)
        {
            x = *exp;
            charCat(&x);
        }
        else if (getPriority(*exp) == lparen)
        {
            postfixPush(*exp);
        }
        else if (getPriority(*exp) == rparen)
        {
            while ((x = postfixPop()) != '(')
            {
                charCat(&x);
            }
        }
        else
        {
            while (getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))  //우선순위 비교
            {
                x = postfixPop();
                charCat(&x);
            }
            postfixPush(*exp);
        }
        exp++;
    }
    while (postfixStackTop != -1)  //스택에 남아있는 연산자 모두 pop
    {
        x = postfixPop();
        charCat(&x);
    }
}

void debug()  //프린트로 계산이 잘되었는 지 확인
{
    printf("\n---DEBUG\n");
    printf("infixExp = %s\n", infixExp);
    printf("postExp = %s\n", postfixExp);
    printf("eval result = %d\n", evalResult);
    printf("postfixStack : ");
    for (int i = 0; i < MAX_STACK_SIZE; i++)
        printf("%c ", postfixStack[i]);
    printf("\n");
}

void reset()  //모든 값 초기화
{
    infixExp[0] = '\0';
    postfixExp[0] = '\0';
    for (int i = 0; i < MAX_STACK_SIZE; i++)
        postfixStack[i] = '\0';
    postfixStackTop = -1;
    evalStackTop = -1;
    evalResult = 0;
}

void evaluation()  //postfix 계산
{
    int opr1, opr2, i;
    int length = strlen(postfixExp);  //문자열 길이
    char symbol;
    evalStackTop = -1;
    for (i = 0; i < length; i++)
    {
        symbol = postfixExp[i];
        if (getToken(symbol) == operand)  //연산자면 push
        {
            evalPush(symbol - '0');
        }
        else
        {
            opr2 = evalPop();  //연산자 앞의 두 수
            opr1 = evalPop();
            switch (getToken(symbol))  //경우에 따라 연산
            {
                case plus:
                    evalPush(opr1 + opr2);
                    break;
                case minus:
                    evalPush(opr1 - opr2);
                    break;
                case times:
                    evalPush(opr1 * opr2);
                    break;
                case divide:
                    evalPush(opr1 / opr2);
                    break;
                default:
                    break;
            }
        }
    }
    evalResult = evalPop();  //연산 결과
}

