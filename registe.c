#include <stdio.h>
#include <string.h>


//注册
int registe()
{
    FILE* fp;
    char c;

    //打开注册文件
    if ((fp = fopen("people_info.txt", "a+")) == NULL)
    {
        perror("fopen");
        return -1;
    }

    //存储用户名
    printf("Enter your name(don't enter '#'): ");

    //读取输入的用户名
    while ((c = getc(stdin)) != '\n')
    {
        putc(c, fp);
    }

    //加上分隔符
    putc('#', fp);


    //存储密码
    printf("Enter your passwd: ");

    //读取密码
    while ((c = getc(stdin)) != '\n')
    {
        putc(c, fp);
    }

    //加上换行符
    putc('\n', fp);

    //关闭文件描述符
    fclose(fp);

    return 1;
}


//登录
int login()
{
    char in_name[60];       //输入的用户名
    char in_passwd[30];     //输入的密码
    FILE* fp;
    char buf[60];

    //输入用户名
    printf("Enter your name: ");
    scanf("%s", in_name);

    //输入密码
    printf("Enter passwd: ");
    scanf("%s", in_passwd);

    //用户名加‘#’，还原存储格式
    strcat(in_name, "#");
    strcat(in_passwd, "\n");
    strcat(in_name, in_passwd);

    //打开文件
    if ((fp = fopen("people_info.txt", "r")) == NULL)
    {
        perror("fopen");
        return -1;
    }

    //读取文件一行，进行比对
    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        //printf("%s", buf);
        if (strcmp(buf, in_name) == 0)
        {
            return 1;
        }
    }

    return -1;
}



int main()
{
    printf("*******************************\n");
    printf("  1.注册    2.登录    3.退出\n");
    printf("*******************************\n");

    int choice;
    int flag;
    printf("Enter number: ");
    while (scanf("%d", &choice) == 1)
    {
        getchar();

        switch(choice)
        {
        case (1):     //注册
            flag = registe();
            if (flag == -1)
            {
                printf("注册失败!\n");
            }
            else if (flag == 1)
            {
                printf("注册成功\n");
            }
            break;

        case (2):     //登录
            flag = login();
            if (flag == -1)
            {
                printf("登录失败!\n");
            }
            else if (flag == 1)
            {
                printf("登录成功!\n");
            }
            break;
            
        case(3):
            return 0;

        default:
            break;
        }

        printf("Enter number: ");
    }

    return 0;
}
