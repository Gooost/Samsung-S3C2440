#include <stdio.h>

void fun_b(void);
void fun_c(void);

void test(void)
{
    char c;
    char *pc;
    printf("&c   =%p\n",&c);
    printf("&pc  =%p\n",&pc);

    c = 'A';
    pc = &c;
    printf("c   =%c\n",c);
    printf("&pc =%p\n",pc);
    printf("*pc =%p\n",*pc);
}




int main(int argc,char **argv)
{
    printf("sizeof(char   )=%d\n",sizeof(char));
    printf("sizeof(int    )=%d\n",sizeof(int ));
    printf("sizeof(char  *)=%d\n",sizeof(char *));
    printf("sizeof(char **)=%d\n",sizeof(char **));    
    printf("/--------------\n");    
    test(); 
    fun_b();
    fun_c();


    return 0;
}
