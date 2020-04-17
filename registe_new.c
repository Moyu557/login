/*************************************************************************
	> File Name: registe.c
	> Author: moyu
	> Mail: 
	> Created Time: 2020年04月17日 星期五 09时05分03秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>


//注册
int registe()
{
    FILE* fp;
    char buf[100];     //处理输入过长的字符

    //打开注册文件
    if ((fp = fopen("people_info.txt", "a+")) == NULL)
    {
        perror("fopen");
        return -1;
    }

    //存储用户名
    printf("Enter your name(don't enter '#'): ");

    fgets(buf, sizeof(buf) - 1, stdin);


    //判断用户名是否已经存在
    char buf_file[32];
    
    while (fgets(buf_file, sizeof(buf_file), fp) != NULL)
    {
        //注意buf还有个结束符
        if (strncmp(buf_file, buf, strlen(buf) - 1) == 0)
        {
            printf("User already exists!\n");
            return -1;
        }
    }

   
    //判断输入是否合法
    int i = 0;
    while (buf[i] != '\n')
    {
        if (buf[i] == '#')
        {
            printf("name have '#'!\n");
            return -1;
        }
        ++i;

        if (i > 30)
        {
            printf("name is too long!\n");
            return -1;
        }
    }



    //加上分隔符
    buf[i] = '#';

    //写入文件
    fwrite(buf, strlen(buf), 1, fp);


    //存储密码
    printf("Enter your passwd: ");

    fgets(buf, sizeof(buf) - 1, stdin);

    
    //写入文件
    fwrite(buf, strlen(buf), 1, fp);

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
    getchar();

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

    char buf[32];
    int flag;
    
        printf("*******************************\n");
        printf("  1.注册    2.登录    3.退出\n");
        printf("*******************************\n");
    
    while (1)
    {
        printf("Enter number: ");
        fgets(buf, sizeof(buf), stdin);
        

        //注册
        if (strcmp(buf,"1\n") == 0)
        {
            flag = registe();
            if (flag == -1)
            {
                printf("注册失败!\n");
            }
            else if (flag == 1)
            {
                printf("注册成功\n");
            }

            continue;
        }

        //登录
        else if (strcmp(buf, "2\n") == 0)
        {
            flag = login();
            
            if (flag == -1)
            {
                printf("登录失败!\n");
            }
            else if (flag == 1)
            {
                printf("登录成功!\n");
            }
            
            continue;
        }
        

        //退出
        else if (strcmp(buf, "3\n") == 0)
        {      
            return 0;
        }


        //其他输入
        else
        {
            printf("Input error! ");
            continue;
        }
        
        //printf("Enter number: ");
    }
}

