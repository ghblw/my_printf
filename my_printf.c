/*************************************************************************
	> File Name: my_printf.c
	> Author:yuxiaowei 
	> Mail:1147407739@qq.com 
	> Created Time: 2018年09月21日 星期五 20时05分28秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <inttypes.h>
#include <math.h>

int my_printf(const char *frm, ...) {
    int cnt = 0;
    va_list arg;
    va_start(arg, frm);
    for (int i = 0; frm[i]; i++) {
        switch (frm[i]) {
            case '%' : {
                i++;
                switch(frm[i]) {
                    case 'd' : {
                        long long temp = va_arg(arg, int),x = 0;//处理INT32_MIN和INT32_MAX时可能溢出
                        int neg=0;
                        //负数
                        if (temp < 0) {
                            neg=1;
                            temp=-temp;
                            cnt++;//字符++
                        }
                        int pre_zero = (int)log10(temp);//前导零初始化
                        cnt += pre_zero+1;//字符++
                        while (temp) {
                            x = x * 10 + temp % 10;
                            temp /= 10;
                        }
                        pre_zero -= (int)log10(x);//前导零个数
                        if (neg == 1) {
                            putchar('-');
                        }
                        while (x) {
                            putchar(x % 10 + '0');
                            x /= 10;
                        } 
                        while (pre_zero--) {
                           putchar('0');
                        }
                    } break;
                    default : 
                        fprintf(stderr, "error : unknow %%%c\n", frm[i]); 
                        exit(1);
                }
            } break;
            default:
                putchar(frm[i]);
                cnt++;//字符++
        }
    }
    return cnt;
}

int main() {
    my_printf("n = %d\n", 12000);
    my_printf("n = %d\n", -567);
    my_printf("n = %d\n", INT32_MIN);
    my_printf("n = %d\n", INT32_MAX);
    return 0;
}

