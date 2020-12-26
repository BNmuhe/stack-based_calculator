#define _CRT_SECURE_NO_WARNINGS
#include"LStack.h"
#include"Link.h"
#include<iostream>
using namespace std;

double result;
int isp(char ch);
int osp(char ch);
bool cal(char op,double x,double y,double &r);
void GetNextchar(char*string,char& ch);
bool IsOperator(char ch);
bool Get2Operands(LStack<double>& opnd,double &x,double &y);

void main() {

    //声明计算过程中所需的变量
    char* string =(char*) malloc(sizeof(char) * 50);
    char ch=NULL,op,prior_char='=',OPTR_Top;
    double oprand1, oprand2,result, prior_num = 0, oprand;
    int number_xiaoshu = 0;
    int flag;

    LStack<double> OPND;   //  操作数栈定义
    LStack<char>   OPTR; //  操作符栈定义



    printf("********************欢迎使用calculator_第四组*****************************\n");
    printf("使用说明：\n");
    printf("表达式可包含：\n");
    printf("1. 加(+)、减(-)、乘(*)、除(/)、求模（%） 、开n次方(&)和乘方(^) 运算符\n");
    printf("例：计算  (1+2)*5&(2)=\n结果应为：6.7082\n");
    printf("2. 括号\n");
    printf("\n");
    while (1) {
        
        //循环所需的初始操作
        ch = NULL;
        prior_num = 0;
        prior_char = '=';
        strcpy(string,"");
        OPND.clear();
        OPTR.clear();
        OPTR.push('=');
        
        //输入字符串
        cout << "请输入表达式<以 \"=\" 结束>(按0+enter退出)：" << endl;
        cin >> string;
        
        
        //判断是否选择退出
        if (!strcmp(string,"0")) {
            return;
        }

       


        GetNextchar(string, ch);
        OPTR_Top = OPTR.topValue();
        while ((ch != '=' || OPTR_Top != '=')) {




            if (isdigit(ch) || ch == '.') {//判断是否为数字
                prior_char = '0';
                cin.putback(ch);
                cin >> oprand;
                OPND.push(oprand);
                GetNextchar(string, ch);


                while (isdigit(ch)) {
                    cin.putback(ch);
                    cin >> oprand;
                    prior_num = OPND.topValue();
                    OPND.pop();
                    OPND.push(10 * prior_num + oprand);
                    GetNextchar(string,ch);
             }
                if (ch == '.') {
                    GetNextchar(string, ch);
                }
                while (isdigit(ch)) {
                    number_xiaoshu++;
                    cin.putback(ch);
                    cin >> oprand;
                    prior_num = OPND.topValue();
                    OPND.pop();
                    OPND.push(prior_num + pow(0.1, number_xiaoshu) * oprand);
                    GetNextchar(string, ch);
                }


                number_xiaoshu = 0;

            }


            if (!IsOperator(ch)) {//判断是否为操作符
                cout << "输入非法字符，程序退出" << endl;
                return;
            }
            else {                   //为操作符之后的操作



                /*
                
                  判断一个数子是否为有符号数，如果为有符号数，就先压入0，表示  0 +/- ch  
                
                */
                if ((prior_char == '=' || prior_char == '(') && (ch == '+' || ch == '-')) {
                    OPND.push(0);
                }


                if (isp(OPTR.topValue()) < osp(ch)) {//栈内顶部的优先级小于栈外优先级
                    prior_char = ch;
                    OPTR.push(ch);
                    GetNextchar(string, ch);
                }
                else if (isp(op = OPTR.topValue()) > osp(ch)) {//栈内顶部的优先级大于栈外优先级
                    Get2Operands(OPND, oprand1, oprand2);
                    OPTR.pop();

                    if (cal(op, oprand1, oprand2, result)) {
                        OPND.push(result);
                    }
                    else {
                        cout << "计算失败，程序退出" << endl;
                        return;
                    }

                }
                else {
                    prior_char = ch;
                    OPTR.pop();
                    GetNextchar(string, ch);
                }


            }
            OPTR_Top = OPTR.topValue();





        }



        cout << "结果为：" << OPND.topValue() << endl;
        system("pause");
    }


}
void GetNextchar(char* string, char& ch) {
    static  int index = 0;
    if (ch == NULL) {
        index = 0;
    }
    ch = string[index];
    index++;


}
bool  cal(char op, double x, double y, double& r) {      // 计算r = x op y， 计算成功，返回true.

    switch (op) {
    case   '+':
        r = x + y;
        return true;
        break;
    case   '-':
        r = x - y;
        return true;
        break;
    case   '*':
        r = x * y;
        return true;
        break;
    case   '%':
        if ((x - (int)x) != 0 || y - (int)y != 0) {
            return false;
        }
        r = (int)x % (int)y;
        return true;
        break;
    case   '/':
        if (y == 0)
            return false;
        else {
            r = x / y;
            return true;
        }
        break;
    case '&':
        
        r = pow(x, 1.0/y);
        return true;
        break;
    case '^':
      
        r = pow(x, y);
        return true;
        break;
    default:
        return false;
    }

}

int osp(char ch) {    // 获取并返回操作符 ch 的栈外优先级
    switch (ch)
    {
    case '=':
        return 0;
        break;
    case '+':
        return 2;
        break;
    case '-':
        return 2;
        break;
    case '*':
        return 4;
        break;
    case '/':
        return 4;
        break;
    case '%':
        return 4;
        break;
    case '(':
        return 8;
        break;
    case ')':
        return 1;
        break;
    case '^':
        return 6;
        break;
    case '&':
        return 6;
        break;
    default:
        break;
    }
}


int isp(char ch) {   //获取并返回操作符 ch 的栈内优先级
    switch (ch)
    {
    case '=':
        return 0;
        break;
    case '+':
        return 3;
        break;
    case '-':
        return 3;
        break;
    case '*':
        return 5;
        break;
    case '/':
        return 5;
        break;
    case '%':
        return 5;
        break;
    case '(':
        return 1;
        break;
    case ')':
        return 8;
        break;
    case '^':
        return 7;
        break;
    case '&':
        return 7;
        break;
    default:
        break;
    }
}


bool Get2Operands(LStack<double>& opnd, double& x, double& y) {
    y = opnd.topValue();
    opnd.pop();
    x = opnd.topValue();
    opnd.pop();

    return true;


}

bool IsOperator(char ch) {    //判断ch是否为操作符

    if (ch == '=' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '(' || ch == ')' || ch == '^' || ch == '&') {
        return true;
    }
    return false;
}
