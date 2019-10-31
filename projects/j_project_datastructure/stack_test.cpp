
#include "stack_test.h"
#include "test.h"
#include "stack.h"
#include <memory>
#include <string>
#include <stdlib.h>

// override not work ,, stack stored with Object not pointer, 
class ElementType_Op : public ElementType
{
public:
    ~ElementType_Op() {}
    ElementType_Op():ElementType(){}
    ElementType_Op(int k):ElementType(k){}

    void print() override
    {
        printf("[%c, 0x%02x]", key, data);
    }
};

void test_stack_sqstack()
{
    sqstack::SqStack stack;
    sqstack::init(&stack, 10);
    sqstack::print(&stack);

    sqstack::push(&stack, new ElementType(1));
    sqstack::push(&stack, new ElementType(2));
    sqstack::push(&stack, new ElementType(3));
    sqstack::print(&stack);

    ElementType* p = sqstack::getTop(&stack);
    p->print();
    ElementType* top = sqstack::pop(&stack);
    top->print();
    printf("\n");
    sqstack::print(&stack);

    sqstack::push(&stack, new ElementType(4));
    sqstack::push(&stack, new ElementType(5));
    sqstack::print(&stack);

    while( !sqstack::isFull(&stack))
    {
        sqstack::push(&stack, new ElementType(sqstack::datasize(&stack)));
    }
    sqstack::print(&stack);

    while( !sqstack::isEmpty(&stack))
    {
        top = sqstack::pop(&stack);
        top->print();
    }
    printf("\n");
    sqstack::print(&stack);

}

void test_stack_listack()
{
    listack::LiStack stack;
    listack::init(&stack);
    listack::print(&stack);

    listack::push(&stack, new ElementType(45));
    listack::print(&stack);
    listack::pop(&stack);
    listack::print(&stack);
    listack::finit(&stack);
    listack::print(&stack);

    listack::push(&stack, new ElementType(1));
    listack::push(&stack, new ElementType(2));
    listack::push(&stack, new ElementType(3));
    listack::print(&stack);

    ElementType* p = listack::getTop(&stack);
    p->print();
    ElementType* top = listack::pop(&stack);
    top->print();
    printf("\n");
    listack::print(&stack);

    listack::push(&stack, new ElementType(4));
    listack::push(&stack, new ElementType(5));
    listack::print(&stack);

    for (int j = 0;j< 10;j++)
    {
        listack::push(&stack, new ElementType(j));
    }
    listack::print(&stack);

    while( !listack::isEmpty(&stack))
    {
        top = listack::pop(&stack);
        top->print();
    }
    printf("\n");
    listack::print(&stack);

}

/**
 * 计算字符串表达式strSrc的值， 预期结果为want
 * 一个栈存数字 和 操作符, 先转化为 后续表达式， 再读取进展动态出栈
 * "3+4*(15/3+5*(2+3*2))*2-9"  =>  3,4,15,3,/,5,2,3,2,*,+,*,+,*,2,*,+,9,-
 */
void stack_calculate_ex(std::string str, int want)
{
    
}

/**
 * 检查是否有下一个 op 或者 num
 * op 返回 1 ，num 返回 2 没有 返回 0 错误返回 -1
 */
int hasnext(const std::string& str)
{
    if (str.length() == 0 || str.empty())
        return false;

    int length = str.length();
    for (int i=0;i<length;i++)
    {
        char c = str.at(i);
        if ( c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')
            return 1;
        if ( c >= '0' && c <= '9' )
            return 2;
        if ( c != ' ')
        {
            printf("wrong string hasnext %s\n",str.c_str());
            return -1;
        }
    }
    return 0;
}


/**
 * 从str 中摘取前面的number， 返回number
 */
int nextnumber(std::string& str)
{
    int index = 0;
    int start = -1, end = -1;
    const int length = str.length();
    std::string strnum = "";

    for (index = 0;index< length;index++ )
    {
        char c = str.at(index);
        if ( start == -1 && ( c>='0' && c<='9') )
            start = index;
        if ( start != -1 && ( c<'0' || c>'9' ) )
        {
            end = index;
            break;
        } 

        if (start != -1 && end == -1 && index == length-1)
        {
            end = length;
        }
    }

    if (start != -1 && end != -1)
    {
        strnum = str.substr(start, end-start);
        if (end == length)
        {
            str = "";
        }
        else
        {
            str = str.substr(end);
        }
        return atoi(strnum.c_str());
    }

    printf("wrong string parse nextnumber %s\n", str.c_str());
    return 0;
    
}

/**
 * 从str 中摘取前面的op， 返回op
 */
char nextop(std::string& str)
{
    int index = 0;
    int start = -1;
    const int length = str.length();

    for (index = 0;index< length;index++ )
    {
        char c = str.at(index);
        if ( c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' )
        {
            start = index;
            break;
        }
            
    }

    if (start != -1 )
    {
        char nextop = str.at(index);
        str = str.substr(start+1);
        return nextop;
    }

    printf("wrong string parse nextop %s\n", str.c_str());
    return 0;
}

/**
 * 比较优先级.
 * topop 的优先级 高于/等于 op的优先级， 返回true.
 * 
 * 特殊: 
 * ( :任何符号, 遇到 (  都要让他进栈。 ( 遇到别的符号也不出栈。即 ( 优先级最大
 * ) :遇到任何符号， 都要出栈执行计算， 最后一定会执行到只剩一个操作数 和 一个（，如 (12)。 即 ) 优先级最小
 */
bool compareop(char topop, char op)
{
    const char opIndex[]    = { '+', '-', '*', '/', '(', ')' };
    const int opProperty[]  = { 3,   3,   4,   4,   5,   2   };

    int index_topop = 0;
    int index_op = 0;
    for (int i = 0;i<6;i++)
    {
        if (opIndex[i] == topop)
            index_topop = i;
        
        if (opIndex[i] == op)
            index_op = i;
    }
    return opProperty[index_topop] >= opProperty[index_op];
}

/**
 * 从 numstack 出栈两个num，从opstack出栈一个op, 计算
 * 结果再进栈 numstack.
 */
void poptwo_and_calculate_listack(listack::LiStack* numstack, listack::LiStack* opstack)
{

    char op = (char)(listack::pop(opstack)->key);

    int num_top = listack::pop(numstack)->key;
    int num_top_next = listack::pop(numstack)->key;

    int res = 0;
    switch(op)
    {
        case '+': res = num_top_next + num_top;
        break;
        case '-': res = num_top_next - num_top;
        break;
        case '*': res = num_top_next * num_top;
        break;
        case '/': res = num_top_next / num_top;
        break;
        default:
            printf("error unknown op %c\n", op);
    }
    printf("exec op: %d%c%d=%d\n", num_top_next, op, num_top, res);
    listack::push(numstack, new ElementType(res));
}

void poptwo_and_calculate_sqstack(sqstack::SqStack* numstack, sqstack::SqStack* opstack)
{

    char op = (char)(sqstack::pop(opstack)->key);

    int num_top = sqstack::pop(numstack)->key;
    int num_top_next = sqstack::pop(numstack)->key;

    int res = 0;
    switch(op)
    {
        case '+': res = num_top_next + num_top;
        break;
        case '-': res = num_top_next - num_top;
        break;
        case '*': res = num_top_next * num_top;
        break;
        case '/': res = num_top_next / num_top;
        break;
        default:
            printf("error unknown op %c\n", op);
    }
    printf("exec op: %d%c%d=%d\n", num_top_next, op, num_top, res);
    sqstack::push(numstack, new ElementType(res));
}


/**
 * 计算字符串表达式strSrc的值， 预期结果为want
 * 两个栈， 一个栈存数字，一个栈存操作符
 */
void listack_calculate(std::string strSrc, int want)
{
    listack::LiStack numstack;
    listack::LiStack opstack;

    listack::init(&numstack);
    listack::init(&opstack);

    std::string str = strSrc;
    int type = hasnext(str);
    while ( type > 0)
    {
        char topop = listack::isEmpty(&opstack) ? 0 : (char)(listack::getTop(&opstack)->key);

        if (type == 2)
        {
            int num = nextnumber(str);
            listack::push(&numstack, new ElementType(num));
            listack::print(&numstack);
        }
        else
        {
            char op = nextop(str);
            if (listack::isEmpty(&opstack))
            {
                listack::push(&opstack, new ElementType_Op(op));
                listack::print(&opstack);
            }
            else
            {
                // 当前栈顶 的 操作符优先级, 高优先级的遇到低优先级的，即可出栈计算
                while (compareop(topop, op))
                {
                    
                    if (topop == '(' && op == ')')
                    {
                        listack::pop(&opstack);
                        break;
                    }
                    if (topop == '(')
                        break;
                    // num 出栈两个，op 出栈一个，计算，结果进栈 num
                    poptwo_and_calculate_listack(&numstack, &opstack);
                    if (listack::isEmpty(&opstack))
                    {
                        break;
                    }
                    topop = (char)(listack::getTop(&opstack)->key);
                }
                if (op != ')')
                    listack::push(&opstack, new ElementType_Op(op));

                listack::print(&opstack);
                //listack::print(&numstack);
            }
        }

        type = hasnext(str);
    }

    listack::print(&opstack);
    listack::print(&numstack);
    while (!listack::isEmpty(&opstack))
    {
        poptwo_and_calculate_listack(&numstack, &opstack);
    }

    int res = (int)(listack::pop(&numstack)->key);
    printf("stack calculate%s %d, want %d\n", str.c_str(), res, want);
}

void sqstack_calculate(std::string strSrc, int want)
{
    sqstack::SqStack numstack;
    sqstack::SqStack opstack;

    sqstack::init(&numstack, 20);
    sqstack::init(&opstack, 20);

    std::string str = strSrc;
    int type = hasnext(str);
    while ( type > 0)
    {
        char topop = sqstack::isEmpty(&opstack) ? 0 : (char)(sqstack::getTop(&opstack)->key);

        if (type == 2)
        {
            int num = nextnumber(str);
            sqstack::push(&numstack, new ElementType(num));
            sqstack::print(&numstack);
        }
        else
        {
            char op = nextop(str);
            if (sqstack::isEmpty(&opstack))
            {
                sqstack::push(&opstack, new ElementType_Op(op));
                sqstack::print(&opstack);
            }
            else
            {
                // 当前栈顶 的 操作符优先级, 高优先级的遇到低优先级的，即可出栈计算
                while (compareop(topop, op))
                {
                    
                    if (topop == '(' && op == ')')
                    {
                        sqstack::pop(&opstack);
                        break;
                    }
                    if (topop == '(')
                        break;
                    // num 出栈两个，op 出栈一个，计算，结果进栈 num
                    poptwo_and_calculate_sqstack(&numstack, &opstack);
                    if (sqstack::isEmpty(&opstack))
                    {
                        break;
                    }
                    topop = (char)(sqstack::getTop(&opstack)->key);
                }
                if (op != ')')
                    sqstack::push(&opstack, new ElementType_Op(op));

                //listack::print(&opstack);
                //listack::print(&numstack);
            }
        }

        type = hasnext(str);
    }

    sqstack::print(&opstack);
    sqstack::print(&numstack);
    while (!sqstack::isEmpty(&opstack))
    {
        poptwo_and_calculate_sqstack(&numstack, &opstack);
    }

    int res = (int)(sqstack::pop(&numstack)->key);
    printf("stack calculate%s %d, want %d\n", str.c_str(), res, want);
}

// 不支持负数
void test_stack_calculate()
{
    std::string strCal_1 = "3+4*(15/3+5*(2+3*2))*2-9";
    std::string strCal_2 = "3+4-(15/3+5*(2+3*2))*2-9";
    std::string strCal_3 = "3+4*(15/3+5*(2*3+2))+2*9";
    std::string strCal_4 = "3+4*(3)+2*9";
    std::string strCal_5 = "3+2*9";

    listack_calculate(strCal_1, 354);
    listack_calculate(strCal_2, -92);
    listack_calculate(strCal_3, 201);
    listack_calculate(strCal_4, 33);
    listack_calculate(strCal_5, 21);

    // sqstack_calculate(strCal_1, 354);
    // sqstack_calculate(strCal_2, -92);
    // sqstack_calculate(strCal_3, 201);
    // sqstack_calculate(strCal_4, 33);
    // sqstack_calculate(strCal_5, 21);
}

void test_stack()
{
    // test_stack_sqstack();
    // test_stack_listack();
    test_stack_calculate();
}