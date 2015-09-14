#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<dirent.h>
#include<time.h>
int main()
{
    int blog_class=-1;//用于选择生成文档类型
    int num=0,max_num=0;//用于储存当前编号，最大编号 等等
    int i;//计数器
    DIR * pdir;//DIR指针用于指向opendir的返回值
    struct dirent *entry;//entry结构体指针 用于保存readdir的结果
    pdir=opendir("./");//打开opendir
    while(blog_class>3||blog_class<0)
    {
        system("cls");
        printf("请选择你要写的Blog类型\n");
        printf("1. Tech   类\n");
        printf("2. Motion 类\n");
        printf("3. Other  类\n");
        printf("0. 退     出\n");
        scanf("%d",&blog_class);
    }
    system("cls");
    while(blog_class)
    {
        while(entry=readdir(pdir))//循环entry
        {
            if((entry->d_name[0]=='t'&&blog_class==1)||(entry->d_name[0]=='m'&&blog_class==2)||(entry->d_name[0]=='o'&&blog_class==3))
            {
                num=entry->d_name[1]-'0';
                for(i=2; entry->d_name[i]!='.'; i++)
                {
                    num*=10;
                    num+=(entry->d_name[i]-'0');
                }
                if(max_num<num) max_num=num;
            }
        }
        creatBlog(blog_class,max_num+1);
        blog_class=0;
    }
    return 0;
}
void creatBlog(int blog_class,int blog_num)
{
    char bclass;
    char title[300],category[50],Tags[20][50];
    int i,j;
    SYSTEMTIME t;
    switch(blog_class)
    {
        case 1: bclass='t';strcpy(category,"Tech");break;
        case 2: bclass='m';strcpy(category,"Motion");break;
        case 3: bclass='o';strcpy(category,"Others");break;
    }
    printf("it will creat %d blog\n and class is %c",blog_num,bclass);
    printf("请输入你要键入的文章标题\n");
    gets(title);
    system("cls");
    printf("请输入该文章的Tag(输入'0'表示输入结束)");
    do{
        gets(Tags[i]);
        i++;
    }while(Tags[i][0]!='0'&&Tags[i][1]!='\0');
    printf("Title:%s\n",title);
    GetLocalTime(&t);
    printf("Date:%4d-%2d-%02d %d:%d\n",t.wYear,t.wMonth,t.wDay,t.wHour,t.wHour);
    printf("Category:%s\n",category);
    printf("Tags:");

    for(i=0;strcmp(Tags[i],"0");i++)
        printf("%s,",Tags[i]);
    printf("\n");

    printf("all done\n");
}
