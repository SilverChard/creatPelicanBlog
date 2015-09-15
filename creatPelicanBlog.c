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
    char name[15];
    char title[300],category[50],Tags[20][50],temp[2];
    int i,j;
    SYSTEMTIME t;
    FILE * fp;
    switch(blog_class)
    {
    case 1:
        bclass='t';
        strcpy(category,"Tech");
        strcpy(name,"t");
        break;
    case 2:
        bclass='m';
        strcpy(category,"Motion");
        strcpy(name,"m");
        break;
    case 3:
        bclass='o';
        strcpy(category,"Others");
        strcpy(name,"o");
        break;
    }
    for(i=1000; i!=0; i/=10)//循环将数字变成字符串储存进name后
    {
        j=blog_num/i;
        temp[0]='0'+j;
        temp[1]='\0';
        strcat(name,temp);
    }
    strcat(name,".md");//填补后缀
    printf("请输入你要键入的文章标题\n");
    getchar();
    gets(title);
    system("cls");
    for(i=0;Tags[i-1][0]!='0'||Tags[i-1][1]!='\0';i++)
    {
        system("cls");
        printf("请输入该文章的第%d条Tag(输入'0'表示输入结束):\n",i+1);
        scanf("%s",Tags[i]);
        system("cls");
    }

    fp=fopen(name,"w+");//开始创建文件
    if(fp==NULL)
    {
        printf("错误，文件创建失败\n");
        exit(0);
    }
    GetLocalTime(&t);//获取系统时间 开始写入
    fprintf(fp,"Title:%s\n",title);
    fprintf(fp,"Date:%4d-%02d-%02d %d:%02d:%02d\n",t.wYear,t.wMonth,t.wDay,t.wHour,t.wHour,t.wSecond);
    fprintf(fp,"Category:%s\n",category);
    fprintf(fp,"Tags:");
    for(i=0; strcmp(Tags[i],"0"); i++)//循环写入tags
        fprintf(fp,"%s,",Tags[i]);
    fprintf(fp,"\n");
    fprintf(fp,"status: draft\n");
    fprintf(fp,"\n此处开始写正文，完成后请不要忘记将status:draft 删除。");
    fprintf(fp,"all done");
    printf("成功");
    fflush(fp);
    fclose(fp);
}
