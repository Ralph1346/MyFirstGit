/***************************************
* @File name: 12.20.c
* @Author: Makonike
* @Version: 1.4
* @Date: 2020-12-25
* @Email: 1694585033@qq.com
* @Description: 课设-->学生奖学金管理系统
***************************************/
/*************************************************
 @Function: // 函数名称
 @Description: // 函数功能、性能等的描述
 @Calls: // 被本函数调用的函数清单
 @CalledBy: // 调用本函数的函数清单
 @TableAccessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
 @TableUpdated: // 被修改的表（此项仅对于牵扯到数据库操作的程序）
 @Input: // 输入参数说明，包括每个参数的作用、取值说明及参数间关系。
 @Output: // 对输出参数的说明。
 @Return: // 函数返回值的说明
 @Others: // 其它说明
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 15        //NAME
#define C 10        //CLASS
#define SN 15         //STUDENT ID
#define STUDENTS_FILE "student.txt"           //存放学生信息1+追加4
#define STUDENTS_RESIDUE "student1.txt"       //存放删除后剩余的信息5
#define STUDENTS_CREATE "student2.txt"        //存放增加后的信息6
#define STUDENTS_COPY "des.txt"               //存放增加后的信息6

//保存文件-文件名任意

/*    用于功能4(统计)中记录班号和每班得分    */
typedef struct scoreclac{
        char tempclass[6];  //  记录班号(学号前五位)
        double sum;//   每个班求和
        struct scoreclac* next; //  指向下一个班求和结构体
    }scc,*sccptr;

/*    核心结构体-学生个人数据    */
typedef struct Student{
    char Stu_ID[SN];   //       学号
    char Name[N];       //      姓名
    char Class[C];      //      班级
    double Math;         //     高数
    double English;      //     英语
    double Physics;      //     物理
    double Total_Points;   //   总分
    int Rank;           //      名次
    struct Student *next;   //  指向下一个学生
}Stu,*StuPtr;

StuPtr S=NULL;//    作为链表表头，贯穿整个程序，同时用来判断初始化状态
StuPtr Entering(StuPtr S);//录入:输入数据并将链表数据存储到Student.txt
//void ShowAll();      //显示全部记录:读取Student.txt的数据建立新链表然后输出
void ShowAll(StuPtr S);//显示全部记录:输出链表内容
void Seek(StuPtr S);//查询:根据指定条件查询学生的信息
    void Seek_Rank(StuPtr S);//根据名次查找学生的信息
    void Seek_Class(StuPtr S);//根据班级查找学生的信息
    void Seek_Class3(StuPtr S);//根据班级查找前3名学生的信息
        void Seek_Score_Subject(StuPtr S,int n);//根据各学科成绩的分数区间查询学生信息
        void Seek_Score_All(StuPtr S);//根据总分区间查询学生信息
void Stat(StuPtr S);//统计
    void Stat1(StuPtr S);//统计总分
    void Stat2(StuPtr S);//分班统计
void Del(StuPtr S);//删除:删除单个学生的信息
    void DeleteAll(StuPtr S);//删除所有信息
void Add(StuPtr S);//增加:增加特定对象的信息
void Sort(StuPtr S);//排序:根据某个特征进行排序
    void Sort1(StuPtr S);//根据名次进行排序
    void Sort2(StuPtr S);//根据学号进行排序
void Save(StuPtr S);//保存文件
void Copy();//复制文件
void Infile(StuPtr S,const char *p,const char *pp);//录入文件
StuPtr Readfile2(const char* p);//读取文件创建链表(all)
void Sum();//计算总分
void TeacherMenu();//教师面板
void StudentMenu();//学生面板
void LoginTeacherSystem();//管理员/教师登陆系统
int testData(StuPtr S);//测试是否录入初始化

/*************************************************
 @Function: main
 @Description: 显示登陆界面
 @Calls: DeleteAll()、LoginTeacherSystem()、StudentMenu()
 @CalledBy:
 @Input:
 @Return: 空类型，无返回值
 @Others: 显示登陆菜单界面，通过变量option的值调用不同函数完成功能
*************************************************/
int main()
{
ErrorMenu://登陆系统输入错误处理-返回重新输入
    while(1){
        system("cls");
        printf("\n\n                 ||***************************************LOGIN****************************************||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||***********************STUDENT SCHOLARSHIP MANAGEMENT SYSTEM************************||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||====================================================================================||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||==================Welcome to Student Scholarship Management System==================||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||====================================================================================||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>Please select the login method<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||====================================================================================||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||                             1.Administrator login                                  ||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||                             2.Student user login                                   ||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||                             3.Log out                                              ||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||====================================================================================||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||****************************************END*****************************************||\n");
        printf("                 ||->>      Please input your option:");
        int option; //选择变量
        scanf("%d",&option);
        switch(option){
            case 1:
                system("cls");
                LoginTeacherSystem();
                break;
            case 2:
                system("cls");
                StudentMenu();
                break;
            case 3:
                system("cls");

                DeleteAll(S);
                exit(0);

            default:
                system("cls");
                printf("\n\n\n                 ||***********************************STUDENT USER*************************************||\n");
                printf("                 ||                                                                                    ||\n");
                printf("                 ||====================================================================================||\n");
                printf("                 ||                                                                                    ||\n");
                printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ERROR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
                printf("                 ||                                                                                    ||\n");
                printf("                 ||                              Error!Please input 1-3 !                              ||\n");
                printf("                 ||                                                                                    ||\n");
                printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ERROR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
                printf("                 ||                                                                                    ||\n");
                printf("                 ||====================================================================================||\n");
                printf("                 ||                                                                                    ||\n");
                printf("                 ||********************Please [enter] to proceed to the next step**********************||\n");

                fflush(stdin);
                getchar();
                goto ErrorMenu;//错误处理，跳回输入
        }
    }
    return 0;
}

/*************************************************
 @Function: Entering
 @Description: 录入学生信息并初始化核心链表
 @Calls: Infile()
 @CalledBy: TeacherMenu()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
 @Return: #S: 正常退出，返回链表的表头指针
          #NULL: 异常退出，申请空间失败，返回空
 @Others: 输入的数据从链表头链接入链表
*************************************************/
StuPtr Entering(StuPtr S){
    char a;//用于重新进入时重复确认是否再次录入

    fflush(stdin);

    if(S){//链表不为空时才执行如下代码段，这时已经初始化并录入过数据了
Error_re_entry:
        system("cls");
        printf("\n\n                 ||****************************************MENU****************************************||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||************************************** USER ****************************************||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||====================================================================================||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Please enter your choice<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||====================================================================================||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||  You have entered the data as well, and re-entry will overwrite the previous data  ||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||                                        y/n                                         ||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||====================================================================================||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||**************************************END*******************************************||\n");
        printf("                 ||->>      Please input your option:");
        fflush(stdin);
        a=getchar();
        if(a=='n'||a=='N'){
            return S;
        }else if(a=='y'||a=='Y'){}
        else{
            system("cls");
            printf("\n\n\n                 ||************************************** USER ****************************************||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||====================================================================================||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ERROR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||                          Error!Pleas enter 'y' or 'n'!                             ||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ERROR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||====================================================================================||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||********************Please [enter] to proceed to the next step**********************||\n");
            fflush(stdin);
            getchar();
            goto Error_re_entry;
        }
    }


    StuPtr head=(StuPtr)malloc(sizeof(Stu));//
    if(head){//初始化
        head->next=NULL;
        S=head;
    }else{
        printf("\n\n\n\n\n||->>                                            Can't Entering!");
        return NULL;//申请空间失败，返回NULL
    }

    while(1){//录入
        system("cls");
        StuPtr temp=(StuPtr)malloc(sizeof(Stu));

        if(temp){
            printf("\n\n\nNow please enter the member (Enter [@] in ID to end)\n");
            printf("\n||->>                 Please enter your Student ID:");
            scanf("%s",temp->Stu_ID);

            if(temp->Stu_ID[0]=='@'){// 输入学号为@时退出
                free(temp);
                return S;

            }else{
                printf("\n||->>                 Please enter your Name:");
                scanf("%s",temp->Name);
                printf("\n||->>                 Please enter your Class:");
                scanf("%s",temp->Class);
                printf("\n||->>                 Please enter your Score of Advanced Mathematics:");
                scanf("%lf",&temp->Math);
                while(temp->Math<0||temp->Math>100){
                    printf("\n||->>                 Error! Please input 0-100:");
                    scanf("%lf",&temp->Math);
                }

                printf("\n||->>                 Please enter your Score of College English:");
                scanf("%lf",&temp->English);
                while(temp->English<0||temp->English>100){
                    printf("\n||->>                 Error! Please input 0-100:");
                    scanf("%lf",&temp->English);
                }

                printf("\n||->>                 Please enter your Score of College physics:");
                scanf("%lf",&temp->Physics);
                while(temp->Physics<0||temp->Physics>100){
                    printf("\n||->>                 Error! Please input 0-100:");
                    scanf("%lf",&temp->Physics);
                }

                temp->Total_Points=0;// 总分和名次都初始化为零
                temp->Rank=0;

                temp->next=S->next;
                S->next=temp;   //  指向下一个
                system("cls");

                printf("\n\n\n\n\n||->>                                            Add member successfully!");
                fflush(stdin);
                getchar();
                if(S->next->next==NULL){
                    Infile(S->next,STUDENTS_FILE,"w");
                }else{
                    Infile(S->next,STUDENTS_FILE,"a+");
                }
            }
        }else{
            printf("\n\n\n\n\n||->>                                            Can't malloc!");
            return NULL;//申请空间失败，返回NULL
        }
    }
    return S;
}

/*************************************************
 @Function: Add
 @Description: 添加学生信息
 @Calls: Infile()
 @CalledBy: TeacherMenu()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
 @Return: 空类型，无返回值
 @Others: 添加的数据从链表头链接入链表
*************************************************/
void Add(StuPtr S){

    if(!S){
        printf("\n\n\n\n\n||->>                                 You have not initialized, please try it again!");
        return;
    }else{

        StuPtr temp = (StuPtr)malloc(sizeof(Stu));//    为新成员申请空间
        if(!temp){     //  申请失败
            printf("\n\n\n\n\n||->>                                            Can't add!");
            return;
        }else{

            printf("\n\n\n||->>                 Please enter your Student ID:");
            scanf("%s",temp->Stu_ID);
            printf("\n||->>                 Please enter your Name:");
            scanf("%s",temp->Name);
            printf("\n||->>                 Please enter your Class:");
            scanf("%s",temp->Class);
            printf("\n||->>                 Please enter your Score of Advanced Mathematics:");
            scanf("%lf",&temp->Math);
            while(temp->Math<0||temp->Math>100){
                printf("\n||->>                 Error! Please input 0-100:");
                scanf("%lf",&temp->Math);
            }
            printf("\n||->>                 Please enter your Score of College English:");
            scanf("%lf",&temp->English);
            while(temp->English<0||temp->English>100){
                printf("\n||->>                 Error! Please input 0-100:");
                scanf("%lf",&temp->English);
            }
            printf("\n||->>                 Please enter your Score of College physics:");
            scanf("%lf",&temp->Physics);
            while(temp->Physics<0||temp->Physics>100){
                printf("\n||->>                 Error! Please input 0-100:");
                scanf("%lf",&temp->Physics);
            }
            temp->Total_Points=0;   //  初始化总分为0
            temp->Rank=0;           //  初始化排名为0

            temp->next=S->next;
            S->next=temp;
            Infile(temp,STUDENTS_CREATE,"a+");
            system("cls");
            printf("\n\n\n\n\n||->>                                            Add member successfully!");

            return;
        }
    }
}

/*************************************************
 @Function: Infile
 @Description: 将数据写入文件
 @Calls: // 被本函数调用的函数清单
 @CalledBy: Entering()、Add()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
         #const char *p:字符串常量-存放需要打开的文件名
         #const char *pp:字符串常量-表示打开文件方式
 @Return: 空类型，无返回值
 @Others: 从链表头遍历链表，将数据以特定方式写入特定文件中
*************************************************/
void Infile(StuPtr S,const char *p,const char *pp){
    FILE *fp=fopen(p,pp); //  打开文件
    StuPtr p1=S;    //  工具指针，每次只能传输一个成员的信息(不包括总分和名次)
    if(!fp){
        system("cls");
        printf("\n\n\n\n\n||->>                                            Can't open!\n");
    }else{
        if(p1){
            fprintf(fp,"%s\t%s\t%s\t%.2lf\t%.2lf\t%.2lf\n",p1->Stu_ID,
p1->Name,p1->Class,p1->Math,p1->English,p1->Physics);

            fclose(fp);
        }else{
            system("cls");
            printf("\n\n\n\n\n||->>                                            Can't Infile!");
            fclose(fp);
            return;
        }
    }

}

/*************************************************
 @Function: ShowAll
 @Description: 显示链表中的所有数据
 @Calls: // 被本函数调用的函数清单
 @CalledBy: TeacherMenu()、StudentMenu()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
 @Return: 空类型，无返回值
 @Others: 从链表头开始遍历链表输出所有数据
*************************************************/
void ShowAll(StuPtr S){

    printf("\n\n                       ***********************************STUDENT******************************\n");
    printf("                       ------------------------------------------------------------------------\n");
    printf("                       |   Num   |   Name   |  Class  |  Sc1  |  Sc2  |  Sc3  |  Sum  | Order |\n");
    printf("                       ------------------------------------------------------------------------\n\n");

    if(S){
        StuPtr p1;
        Sum(S);
        for(p1=S->next;p1;p1=p1->next){
            printf("                         %-11s%-11s%-10s%-8.2lf%-8.2lf%-8.2lf%-9.2lf%-5d\n\n",p1->Stu_ID,
p1->Name,p1->Class,p1->Math,p1->English,p1->Physics,p1->Total_Points,p1->Rank);
        }
    }
    printf("                       ------------------------------------------------------------------------\n");
    printf("                       **************************************END*******************************\n");

}

/*************************************************
 @Function: Del
 @Description: 根据学号删除链表中学生信息
 @Calls: Infile()
 @CalledBy: TeacherMenu()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
 @Return: 空类型，无返回值
 @Others: 从链表头开始遍历链表查找数据并删除
*************************************************/
void Del(StuPtr S){

    if(!S){
        printf("\n\n\n\n\n||->>                                 You have not initialized, please try it again!");
        return;
    }
    if(!S->next){
        printf("\n\n\n\n\n||->>                                      No data available, please enter retry!");
        return;
    }
    StuPtr p1,p2;   //  工具指针
    char tempID[N]; //  存放要删除的ID

    printf("\n\n\n\n\n||->>                 Please input The student's ID:");
    scanf("%s",tempID);

    for(p1=S;p1->next;p1=p1->next){
        if(strcmp(tempID,p1->next->Stu_ID)==0){
            p2=p1->next;
            p1->next=p2->next;
            free(p2);
            p2=NULL;
            for(p2=S->next;p2;p2=p2->next){
                Infile(p2->next,STUDENTS_RESIDUE,"w"); //  把删除后剩下的数据保存到文件 student1
            }
            system("cls");
            printf("\n\n\n\n\n||->>                                            Delete successfully!");
            return;
        }

    }
    system("cls");
    printf("\n\n\n\n\n||->>                                            Error!Can't find this student!");
    return;

}

/*************************************************
 @Function: DeleteAll
 @Description: 删除链表中的所有数据
 @Calls: // 被本函数调用的函数清单
 @CalledBy: main()、Copy()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
 @Return: 空类型，无返回值
 @Others: 从链表头开始删除数据，直至链表为空
*************************************************/
void DeleteAll(StuPtr S){

    if(S==NULL||S->next==NULL){
        return;
    }

    StuPtr temp;
    for(;S->next!=NULL;){
        temp=S->next;
        S->next=temp->next;
        free(temp);
    }

}

/*************************************************
 @Function: Sum
 @Description: 累加链表中每个学生的各科成绩，然后赋予总分变量
 @Calls: // 被本函数调用的函数清单
 @CalledBy: ShowAll()、Stat1()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
 @Return: 空类型，无返回值
 @Others: 从链表头开始累加各科成绩赋予总分变量
*************************************************/
void Sum(StuPtr S){
    StuPtr temp;
    for(temp=S->next;temp;temp=temp->next){
        temp->Total_Points=temp->Math+temp->English+temp->Physics;
    }
}

/*************************************************
 @Function: Seek
 @Description: 显示查询菜单界面
 @Calls: Seek_Rank()、Seek_Class()、Seek_Class3()、Seek_Score_Subject()、Seek_Score_All()
 @CalledBy: TeacherMenu()、StudentMenu()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
 @Return: 空类型，无返回值
 @Others: 显示查询菜单界面，调用不同子函数完成查询功能
*************************************************/
void Seek(StuPtr S){

    if(!S){
        printf("\n\n\n\n\n||->>                                 You have not initialized, please try it again!");
        return;
    }
    if(!S->next){
        printf("\n\n\n\n\n||->>                                      No data available, please enter retry!");
        return;
    }
Error:
    system("cls");
    printf("\n\n                 ||****************************************MENU****************************************||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||************************************** USER ****************************************||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||====================================================================================||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Please enter your choice<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||====================================================================================||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||       1.Search a student's individual achievement by rank                          ||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||       2.Search a student's individual achievement by scores                        ||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||       3.Check the individual scores of the top 3 students in the class by class    ||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||       4.Query a student's individual achievement by achievement section            ||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||       5.Back to menu                                                               ||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||====================================================================================||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||****************************************END*****************************************||\n");
    printf("                 ||->>      Please input your option:");

//    printf("****************************************\n");
//    printf("1----------按名次查询某学生的个人成绩\n");
//    printf("2----------按班级查询学生的个人成绩\n");
//    printf("3----------按班级查询班级前 3 名学生的个人成绩\n");
//    printf("4----------按成绩段查询某学生的个人成绩\n");
//    printf("****************************************\n");

    int option;

    scanf("%d",&option);    //  输入选择的序号
    switch (option){
        case 1:
            system("cls");

            Seek_Rank(S);
            break;
        case 2:
            system("cls");

            Seek_Class(S);
            break;
        case 3:
            system("cls");

            Seek_Class3(S);
            break;
        case 4:
Error_Scoreoption:
            system("cls");
            printf("\n\n                 ||****************************************MENU****************************************||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||************************************** USER ****************************************||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||====================================================================================||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Please enter your choice<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||====================================================================================||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||                   1.Query according to advanced mathematics scores                 ||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||                   2.Query according to English score                               ||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||                   3.Query according to physical score                              ||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||                   4.Query according to total score                                 ||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||                   5.Back to menu                                                   ||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||====================================================================================||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||****************************************END*****************************************||\n");
            printf("                 ||->>      Please input your option:");
//    printf("****************************************\n");
//    printf("1----------根据高数成绩查询\n");
//    printf("2----------根据英语成绩查询\n");
//    printf("3----------根据物理成绩查询\n");
//    printf("4----------根据总分查询\n");
//    printf("****************************************\n");
            int option2;
            scanf("%d",&option2);
                switch (option2){
                    case 1:
                    case 2:
                    case 3:
                        Seek_Score_Subject(S,option2);
                        break;
                    case 4:
                        Seek_Score_All(S);
                        break;
                    case 5:
                        goto Error;
                    default:
                        system("cls");
                        printf("\n\n\n                 ||************************************** USER ****************************************||\n");
                        printf("                 ||                                                                                    ||\n");
                        printf("                 ||====================================================================================||\n");
                        printf("                 ||                                                                                    ||\n");
                        printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ERROR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
                        printf("                 ||                                                                                    ||\n");
                        printf("                 ||                              Error!Please input 1-5 !                              ||\n");
                        printf("                 ||                                                                                    ||\n");
                        printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ERROR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
                        printf("                 ||                                                                                    ||\n");
                        printf("                 ||====================================================================================||\n");
                        printf("                 ||                                                                                    ||\n");
                        printf("                 ||********************Please [enter] to proceed to the next step**********************||\n");
                        fflush(stdin);
                        getchar();
                        goto Error_Scoreoption;
                }
            break;
        case 5:
            return;
        default:    //  错误处理：返回重新输入
            system("cls");
            printf("\n\n\n                 ||************************************** USER ****************************************||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||====================================================================================||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ERROR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||                              Error!Please input 1-5 !                              ||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ERROR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||====================================================================================||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||********************Please [enter] to proceed to the next step**********************||\n");
            fflush(stdin);
            getchar();
            goto Error;
    }


}

/*************************************************
 @Function: Seek_Rank
 @Description: 根据学生名次查找信息
 @Calls: // 被本函数调用的函数清单
 @CalledBy: Seek()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
 @Return: 空类型，无返回值
 @Others: 从链表头开始遍历链表至相应名次时输出信息
*************************************************/
void Seek_Rank(StuPtr S){
    StuPtr p1;
    int tempRank,i=0;       //因为添加成员 是从链表头加入
    if(S->next->Rank==0){   //一般来说如果没有排序的学生会排在第一个
        system("cls");
        printf("\n\n\n\n\n||->>                                            You haven't sorted yet, please sort and try again!");
        return;
    }

    printf("\n\n\n||->>                 Please input the Student's rank:");
    scanf("%d",&tempRank);
    system("cls");
    printf("\n\n                       ***********************************STUDENT******************************\n");
    printf("                       ------------------------------------------------------------------------\n");
    printf("                       |   Num   |   Name   |  Class  |  Sc1  |  Sc2  |  Sc3  |  Sum  | Order |\n");
    printf("                       ------------------------------------------------------------------------\n\n");
    for(p1=S->next;p1;p1=p1->next){
        if(tempRank==p1->Rank){
            i++;
            printf("                         %-11s%-11s%-10s%-8.2lf%-8.2lf%-8.2lf%-9.2lf%-5d\n\n",p1->Stu_ID,
p1->Name,p1->Class,p1->Math,p1->English,p1->Physics,p1->Total_Points,p1->Rank);
            return;
        }
    }
    if(!i){
        printf("\n\n                                                         not find!                      \n\n\n\n");
    }
    printf("                       ------------------------------------------------------------------------\n");
    printf("                       **************************************END*******************************\n");
}

/*************************************************
 @Function: Seek_Rank
 @Description: 根据班级查找前三名信息
 @Calls: // 被本函数调用的函数清单
 @CalledBy: Seek()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
 @Return: 空类型，无返回值
 @Others: 从链表头开始遍历链表至相应班级时，再通过遍历筛选前三名输出信息
*************************************************/
void Seek_Class3(StuPtr S){


    int i,j=0;//    i->>记录该班同学名次,j->>检测该班同学数量
    StuPtr p1,p2;   //  p1-大循环,p2-筛选并排名
    char tempClass[C];  //  临时存放输入的班级
    printf("\n\n\n||->>                 Please input the Class:");
    scanf("%s",tempClass);
    system("cls");
    printf("\n\n                       ***********************************STUDENT******************************\n");
    printf("                       ------------------------------------------------------------------------\n");
    printf("                       |   Num   |   Name   |  Class  |  Sc1  |  Sc2  |  Sc3  |  Sum  | Order |\n");
    printf("                       ------------------------------------------------------------------------\n\n");

    for(p1=S->next;p1;p1=p1->next){
        i=1;    //  默认排名初始化为1
        for(p2=S->next;p2;p2=p2->next){
            if(strcmp(tempClass,p2->Class)==0){
                j++;
                if(p1->Total_Points<p2->Total_Points){
                    i++;
                }
            }
        }

        if(i<=3&&(strcmp(tempClass,p1->Class)==0)){
            printf("                         %-11s%-11s%-10s%-8.2lf%-8.2lf%-8.2lf%-9.2lf%-5d\n\n",p1->Stu_ID,
p1->Name,p1->Class,p1->Math,p1->English,p1->Physics,p1->Total_Points,p1->Rank);
        }

    }
    if(!j){
        printf("\n\n                                                         not find!                      \n\n\n\n");
    }
    printf("                       ------------------------------------------------------------------------\n");
    printf("                       **************************************END*******************************\n");

}

/*************************************************
 @Function: Seek_Class
 @Description: 根据班级查找信息
 @Calls: // 被本函数调用的函数清单
 @CalledBy: Seek()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
 @Return: 空类型，无返回值
 @Others: 从链表头开始遍历链表至相应班级时输出信息
*************************************************/
void Seek_Class(StuPtr S){
    StuPtr p1;
    char tempClass[C];
    int j=0;
    printf("\n\n\n||->>                 Please input the class:");
    scanf("%s",tempClass);
    system("cls");
    printf("\n\n                       ***********************************STUDENT******************************\n");
    printf("                       ------------------------------------------------------------------------\n");
    printf("                       |   Num   |   Name   |  Class  |  Sc1  |  Sc2  |  Sc3  |  Sum  | Order |\n");
    printf("                       ------------------------------------------------------------------------\n\n");

    for(p1=S->next;p1;p1=p1->next){
        if(strcmp(tempClass,p1->Class)==0){
            j++;
            printf("                         %-11s%-11s%-10s%-8.2lf%-8.2lf%-8.2lf%-9.2lf%-5d\n\n",p1->Stu_ID,
p1->Name,p1->Class,p1->Math,p1->English,p1->Physics,p1->Total_Points,p1->Rank);
        }
    }
    if(!j){
        printf("\n\n                                                         not find!                      \n\n\n\n");
    }
    printf("                       ------------------------------------------------------------------------\n");
    printf("                       **************************************END*******************************\n");
}

/*************************************************
 @Function: Seek_Score_Subject
 @Description: 根据各科成绩段查找信息
 @Calls: // 被本函数调用的函数清单
 @CalledBy: Seek()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
         #int n: 整型变量-用来选择对应的学科
 @Return: 空类型，无返回值
 @Others: 从链表头开始遍历链表，输出相应科目成绩在成绩段的节点信息
*************************************************/
void Seek_Score_Subject(StuPtr S,int n){
    StuPtr p1=S->next;
    double score1,score2;
    int i=0;
Error_Score1:
    system("cls");
    printf("\n\n\n||->>                 Please input the range of score(example 60 - 90):");
    scanf("%lf-%lf",&score1,&score2);
    if(score1<0||score2>100||score1>score2){
        system("cls");
        printf("\n\n\n\n\n||->>                                            Error!Please input the right score(1 - 100)!");
        fflush(stdin);
        getchar();
        goto Error_Score1;
    }
    system("cls");
    printf("\n\n                       ***********************************STUDENT******************************\n");
    printf("                       ------------------------------------------------------------------------\n");
    printf("                       |   Num   |   Name   |  Class  |  Sc1  |  Sc2  |  Sc3  |  Sum  | Order |\n");
    printf("                       ------------------------------------------------------------------------\n\n");

    switch(n){
        case 1://高数
            for(;p1;p1=p1->next){
                if(score1<=p1->Math&&p1->Math<=score2){
                    i++;
                    printf("                         %-11s%-11s%-10s%-8.2lf%-8.2lf%-8.2lf%-9.2lf%-5d\n\n",p1->Stu_ID,
p1->Name,p1->Class,p1->Math,p1->English,p1->Physics,p1->Total_Points,p1->Rank);
                }
            }
            break;
        case 2://英语
            for(;p1;p1=p1->next){
                if(score1<=p1->English&&p1->English<=score2){
                    i++;
                    printf("                         %-11s%-11s%-10s%-8.2lf%-8.2lf%-8.2lf%-9.2lf%-5d\n\n",p1->Stu_ID,
p1->Name,p1->Class,p1->Math,p1->English,p1->Physics,p1->Total_Points,p1->Rank);
                }
            }
            break;
        case 3://物理
            for(;p1;p1=p1->next){
                if(score1<=p1->Physics&&p1->Physics<=score2){
                    i++;
                    printf("                         %-11s%-11s%-10s%-8.2lf%-8.2lf%-8.2lf%-9.2lf%-5d\n\n",p1->Stu_ID,
p1->Name,p1->Class,p1->Math,p1->English,p1->Physics,p1->Total_Points,p1->Rank);
                }
            }
            break;
    }
//    for(;p1;p1=p1->next){
//        if(score1<=p1->Math&&p1->Math<=score2){
//            i++;
//            printf("                         %-11s%-11s%-10s%-8.2lf%-8.2lf%-8.2lf%-9.2lf%-5d\n\n",p1->Stu_ID,
//p1->Name,p1->Class,p1->Math,p1->English,p1->Physics,p1->Total_Points,p1->Rank);
//        }
//    }
    if(!i){
        printf("\n\n                                                         not find!                      \n\n\n\n");
    }
    printf("                       ------------------------------------------------------------------------\n");
    printf("                       **************************************END*******************************\n");
}

/*************************************************
 @Function: Seek_Score_All
 @Description: 根据总分成绩段查找信息
 @Calls: // 被本函数调用的函数清单
 @CalledBy: Seek()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
 @Return: 空类型，无返回值
 @Others: 从链表头开始遍历链表，输出总分成绩在成绩段的节点信息
*************************************************/
void Seek_Score_All(StuPtr S){
    StuPtr p1=S;
    double score1,score2;
    int i=0;
    system("cls");
    printf("\n\n\n||->>                 Please input the range of score(example 180-240):");
Error_Score4:
    scanf("%lf-%lf",&score1,&score2);
    if(score1<0||score2>300||score1>score2){
        system("cls");
        printf("\n\n\n\n\n||->>                                            Error!Please input the right score(0 - 300)!");
        fflush(stdin);
        getchar();
        goto Error_Score4;
    }
    system("cls");
    printf("\n\n                       ***********************************STUDENT******************************\n");
    printf("                       ------------------------------------------------------------------------\n");
    printf("                       |   Num   |   Name   |  Class  |  Sc1  |  Sc2  |  Sc3  |  Sum  | Order |\n");
    printf("                       ------------------------------------------------------------------------\n\n");

    for(;p1;p1=p1->next){
        if(score1<=p1->Total_Points&&p1->Total_Points<=score2){
            i++;
            printf("                         %-11s%-11s%-10s%-8.2lf%-8.2lf%-8.2lf%-9.2lf%-5d\n\n",p1->Stu_ID,
p1->Name,p1->Class,p1->Math,p1->English,p1->Physics,p1->Total_Points,p1->Rank);
        }
    }
    if(!i){
        printf("\n\n                                                         not find!                      \n\n\n\n");
    }
    printf("                       ------------------------------------------------------------------------\n");
    printf("                       **************************************END*******************************\n");
}

/*************************************************
 @Function: Stat
 @Description: 显示统计菜单界面
 @Calls: Stat1()、Stat2()
 @CalledBy: TeacherMenu()、StudentMenu()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
 @Return: 空类型，无返回值
 @Others: 显示统计菜单界面，调用不同子函数完成统计功能
*************************************************/
void Stat(StuPtr S){
    if(!S){
        system("cls");
        printf("\n\n\n\n\n||->>                                 You have not initialized, please try it again!");
        return;
    }
    if(!S->next){
        printf("\n\n\n\n\n||->>                                      No data available, please enter retry!");
        return;
    }

Error_Sta:
    system("cls");
    printf("\n\n                 ||****************************************MENU****************************************||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||************************************** USER ****************************************||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||====================================================================================||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Please enter your choice<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||====================================================================================||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||                                    1.Aggregate                                     ||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||                                    2.Class statistics                              ||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||                                    3.Back to menu                                  ||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||====================================================================================||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||****************************************END*****************************************||\n");
    printf("                 ||->>      Please input your option:");

//    printf("****************************************\n");
//    printf("1--------------总计\n");
//    printf("2--------------分班统计\n");
//    printf("****************************************\n");

    int option;
    scanf("%d",&option);    //  输入选择的序号
    switch (option){
        case 1:
            system("cls");
            Stat1(S);
            break;
        case 2:
            system("cls");
            Stat2(S);
            break;
        case 3:
            return;
        default:
            system("cls");
            printf("\n\n\n                 ||************************************** USER ****************************************||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||====================================================================================||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ERROR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||                              Error!Please input 1-3 !                              ||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ERROR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||====================================================================================||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||********************Please [enter] to proceed to the next step**********************||\n");

            fflush(stdin);
            getchar();

            goto Error_Sta;
    }

}

/*************************************************
 @Function: Stat1
 @Description: 统计链表中所有学生的总分
 @Calls: // 被本函数调用的函数清单
 @CalledBy: Stat()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
 @Return: 空类型，无返回值
 @Others: 从表头开始遍历链表，累加求和所有节点的总分
*************************************************/
void Stat1(StuPtr S){

    StuPtr p1=S;
    Sum(S);
    double sum=0;
    for(p1=S->next;p1;p1=p1->next){
        sum+=p1->Total_Points;
    }
    printf("\n\n\n\n\n||->>                                           The total score is %.2lf\n",sum);
}

/*************************************************
 @Function: Stat2
 @Description: 分别统计链表中每个班级的总分
 @Calls: // 被本函数调用的函数清单
 @CalledBy: Stat()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
 @Return: 空类型，无返回值
 @Others: 从表头开始遍历链表，遇到相应班级就使该班级对应的结构体总分累加
*************************************************/
void Stat2(StuPtr S){

    int i;//用来判断班级统计链表中是否存在该班级
    sccptr head=(sccptr)malloc(sizeof(scc));
    if(!head){
        printf("\n\n\n\n\n||->>                                            Can't malloc!");
        return;
    }
    sccptr s1,s2;
    head->next=NULL;
    StuPtr p1;
    for(p1=S->next;p1;p1=p1->next){

        for(s1=head->next,i=0;s1;s1=s1->next){//遍历是否存在
            if(strncmp(p1->Stu_ID, s1->tempclass, 5)==0){
                i++;
                break;
            }
        }

        if(!i){//初始化，如果没有就增加这个班级并且累加
            s2=(sccptr)malloc(sizeof(scc));
            if(!s2){
                system("cls");
                printf("\n\n\n\n\n||->>                                            Can't malloc!");
                return;
            }
            s2->sum=0;
            memcpy(s2->tempclass,p1->Stu_ID,5);
            s2->tempclass[5]='\0';
            if(head->next==NULL){
                s2->next=NULL;
            }else{
                s2->next=head->next;
            }
            head->next=s2;
            s2->sum+=p1->Total_Points;
        }else{//有就累计
            s1->sum+=p1->Total_Points;
        }
    }

    printf("                       ------------------------------------------------------------------------\n");
    printf("                       *************************************************************************\n\n");
    for(s1=head->next;s1;s1=s1->next){
        printf("                                  Class Number: %6s           Sum : %.2lf\n\n",s1->tempclass,s1->sum);
    }
    printf("                       ------------------------------------------------------------------------\n");
    printf("                       **************************************END*******************************\n");


    FILE *fp=fopen(STUDENTS_FILE,"a+"); //  打开文件
    sccptr s3;    //  工具指针，每次只能传输一个成员的所有信息
    if(!fp){
        system("cls");
        printf("\n\n\n\n\n||->>                                            Can't open!\n");
        fflush(stdin);
        getchar();
    }else{
        fprintf(fp,"\n************************************STUDENT***************************\n");
        fprintf(fp,"\n**********************************************************************\n");
        for(s3=head->next;s3;s3=s3->next){
            fprintf(fp,"Class Number: %5s  Sum : %.2lf\n",s3->tempclass,s3->sum);
        }
        fprintf(fp,"\n**********************************************************************\n");
        fprintf(fp,"\n**************************************END*****************************\n");
        fclose(fp);

        /*  释放空间  */
        if(head==NULL||head->next==NULL){
            printf("\n||->>                                            It's null now!");
            return;
        }
        for(;head->next!=NULL;){
            s1=head->next;
            head->next=s1->next;
            free(s1);
        }


        return;
    }

}

/*************************************************
 @Function: Save
 @Description: 保存链表数据至文件
 @Calls: // 被本函数调用的函数清单
 @CalledBy: TeacherMenu()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
 @Return: 空类型，无返回值
 @Others:通过打开指定文件，以写入形式w遍历链表，把链表数据写入文件
*************************************************/
void Save(StuPtr S){
    if(!S){
        system("cls");
        printf("\n\n\n\n\n||->>                                 You have not initialized, please try it again!");
        return;
    }
    if(!S->next){
        printf("\n\n\n\n\n||->>                                      No data available, please enter retry!");
        return;
    }

    fflush(stdin);
    char Savename[20];
    system("cls");
    printf("\n\n\n                 ||->>Please input your filename:");
    gets(Savename);
    strcat(Savename,".txt");
    FILE *fp=fopen(Savename,"r"); //  打开文件
    StuPtr p1;    //  工具指针，每次只能传输一个成员的所有信息

    if(!fp){
        system("cls");
        printf("\n\n\n\n\n||->>                                            Can't save!\n");
        return;
    }else{
        for(p1=S->next;p1;p1=p1->next){
            fprintf(fp,"%s\t%s\t%s\t%.2lf\t%.2lf\t%.2lf\t%.2lf\t%d\n",p1->Stu_ID,
p1->Name,p1->Class,p1->Math,p1->English,p1->Physics,p1->Total_Points,p1->Rank);
        }
    }
    fclose(fp);
    system("cls");
    printf("\n\n\n\n\n||->>                                            Save successfully!");
}

/*************************************************
 @Function: Copy
 @Description: 复制任意文件数据至指定文件des.txt
 @Calls: Readfile2()、DeleteAll()
 @CalledBy: TeacherMenu()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
 @Return: 空类型，无返回值
 @Others:通过打开指定文件，创建新链表读取该文件数据，再以写入形式w遍历链表，把链表数据写入文件
*************************************************/
void Copy(){

    if(!S){
        system("cls");
        printf("\n\n\n\n\n||->>                                 You have not initialized, please try it again!");
        return;
    }
    if(!S->next){
        printf("\n\n\n\n\n||->>                                      No data available, please enter retry!");
        return;
    }
    system("cls");
    printf("\n\n                 ||****************************************MENU****************************************||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||************************************** USER ****************************************||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||====================================================================================||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Please enter your choice<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||====================================================================================||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||                        Now you have these files you can copy                       ||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||              student.txt/student1.txt/student2.txt/others you created              ||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||====================================================================================||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||**************************************END*******************************************||\n");
    printf("                 ||->>please input which file you want to copy:");


//    printf("****************************************\n");
//    printf("Now you have these files you can copy:\n");
//    printf("student.txt/student1.txt/student2.txt/others you created\n");
//    printf("****************************************\n");
//    printf("please input which file you want to copy:");

    fflush(stdin);
    char copyfile1[20];
    gets(copyfile1);
    strcat(copyfile1,".txt");
//    printf("                 ||->>please input the filename you want to save:");
//    fflush(stdin);
//    char copyfile2[20];
//    gets(copyfile2);
//    strcat(copyfile2,".txt");


    StuPtr p1,p2;    //  工具指针，每次只能传输一个成员的所有信息
    p1=Readfile2(copyfile1);
    if(!p1){
        system("cls");
        printf("\n\n\n\n\n||->>                            Can't find the file named %s !\n",copyfile1);
    }else{
        FILE *fp=fopen(STUDENTS_COPY,"w"); //  打开文件
        for(p2=p1->next;p2;p2=p2->next){
            fprintf(fp,"%s\t%s\t%s\t%.2lf\t%.2lf\t%.2lf\t%.2lf\t%d\n",p2->Stu_ID,
p2->Name,p2->Class,p2->Math,p2->English,p2->Physics,p2->Total_Points,p2->Rank);
        }
        DeleteAll(p1);
        fclose(fp);
        return;
    }

    system("cls");
    printf("\n\n\n\n\n||->>                                            Save successfully!");
}

/*************************************************
 @Function: Sort
 @Description: 显示排序菜单界面
 @Calls: Sort1()、Sort2()
 @CalledBy: TeacherMenu()、StudentMenu()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
 @Return: 空类型，无返回值
 @Others: 显示排序菜单界面，调用不同子函数完成排序功能
*************************************************/
void Sort(StuPtr S){

    if(!S){
        printf("\n\n\n\n\n||->>                                 You have not initialized, please try it again!");
        return;
    }
    if(!S->next){
        printf("\n\n\n\n\n||->>                                      No data available, please enter retry!");
        return;
    }
Error_Sort:
    system("cls");
    printf("\n\n                 ||****************************************MENU****************************************||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||************************************** USER ****************************************||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||====================================================================================||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Please enter your choice<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||====================================================================================||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||                                 1.Sort by rank                                     ||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||                                 2.Sort by student number                           ||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||                                 3.Back to munu                                     ||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||====================================================================================||\n");
    printf("                 ||                                                                                    ||\n");
    printf("                 ||**************************************END*******************************************||\n");
    printf("                 ||->>      Please input your option:");

//    printf("****************************************\n");
//    printf("1----------对所有学生按名次排序\n");
//    printf("2----------对所有学生按学号排序\n");
//    printf("****************************************\n");

    int option;
    scanf("%d",&option);    //  输入选择的序号
    switch (option){
        case 1:
            system("cls");
            Sort1(S);
            break;
        case 2:
            system("cls");
            Sort2(S);
            break;
        case 3:
            return;
        default:
            system("cls");
            printf("\n\n\n                 ||************************************** USER ****************************************||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||====================================================================================||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ERROR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||                              Error!Please input 1-3 !                              ||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ERROR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||====================================================================================||\n");
            printf("                 ||                                                                                    ||\n");
            printf("                 ||********************Please [enter] to proceed to the next step**********************||\n");

            fflush(stdin);
            getchar();
            goto Error_Sort;
    }
}

/*************************************************
 @Function: Sort1
 @Description: 根据名次排序学生信息
 @Calls: // 被本函数调用的函数清单
 @CalledBy: Sort()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
 @Return: 空类型，无返回值
 @Others: 从表头开始遍历链表，用选择排序法根据总分从大到小排序并赋予名次
*************************************************/
void Sort1(StuPtr S){
    StuPtr temp=(StuPtr)malloc(sizeof(Stu));
    StuPtr p1,p2,p3;
    int i=1,j=1;
    double tempscore=S->next->Total_Points;
    for(p1=S->next;p1->next;p1=p1->next,i++){
        p3=p1;
        for(p2=p1->next;p2;p2=p2->next){
            if(p3->Total_Points<p2->Total_Points){
                p3=p2;
            }
        }
        strcpy(temp->Stu_ID,p3->Stu_ID);
        strcpy(temp->Name,p3->Name);
        strcpy(temp->Class,p3->Class);
        temp->Math=p3->Math;
        temp->English=p3->English;
        temp->Physics=p3->Physics;
        temp->Total_Points=p3->Total_Points;

        strcpy(p3->Stu_ID,p1->Stu_ID);
        strcpy(p3->Name,p1->Name);
        strcpy(p3->Class,p1->Class);
        p3->Math=p1->Math;
        p3->English=p1->English;
        p3->Physics=p1->Physics;
        p3->Total_Points=p1->Total_Points;

        strcpy(p1->Stu_ID,temp->Stu_ID);
        strcpy(p1->Name,temp->Name);
        strcpy(p1->Class,temp->Class);
        p1->Math=temp->Math;
        p1->English=temp->English;
        p1->Physics=temp->Physics;
        p1->Total_Points=temp->Total_Points;
        if(tempscore==p1->Total_Points){
            p1->Rank=j;
        }else{
            p1->Rank=i;
        }
        j=p1->Rank;
        tempscore=p1->Total_Points;
    }
    if(tempscore==p1->Total_Points){
        p1->Rank=j;
    }else{
        p1->Rank=i;
    }
    free(temp);
    printf("\n\n\n\n\n||->>                                            Sort successfully!");
}

/*************************************************
 @Function: Sort2
 @Description: 根据学号排序学生信息
 @Calls: // 被本函数调用的函数清单
 @CalledBy: Sort()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
 @Return: 空类型，无返回值
 @Others: 从表头开始遍历链表，用选择排序法根据学号从大到小排序
*************************************************/
void Sort2(StuPtr S){

    StuPtr temp=(StuPtr)malloc(sizeof(Stu));
    StuPtr p1,p2,p3;
    for(p1=S->next;p1->next;p1=p1->next){
        p3=p1;
        for(p2=p1->next;p2;p2=p2->next){
            if(strcmp(p3->Stu_ID,p2->Stu_ID)<0){
                p3=p2;
            }

        }
        strcpy(temp->Stu_ID,p3->Stu_ID);
        strcpy(temp->Name,p3->Name);
        strcpy(temp->Class,p3->Class);
        temp->Math=p3->Math;
        temp->English=p3->English;
        temp->Physics=p3->Physics;
        temp->Total_Points=p3->Total_Points;
        temp->Rank=p3->Rank;

        strcpy(p3->Stu_ID,p1->Stu_ID);
        strcpy(p3->Name,p1->Name);
        strcpy(p3->Class,p1->Class);
        p3->Math=p1->Math;
        p3->English=p1->English;
        p3->Physics=p1->Physics;
        p3->Total_Points=p1->Total_Points;
        p3->Rank=p1->Rank;

        strcpy(p1->Stu_ID,temp->Stu_ID);
        strcpy(p1->Name,temp->Name);
        strcpy(p1->Class,temp->Class);
        p1->Math=temp->Math;
        p1->English=temp->English;
        p1->Physics=temp->Physics;
        p1->Total_Points=temp->Total_Points;
        p1->Rank=temp->Rank;

    }
    free(temp);

    printf("\n\n\n\n\n||->>                                            Sort successfully!");
}

/*************************************************
 @Function: Readfile2
 @Description: 读取文件数据创建并新链表
 @Calls: // 被本函数调用的函数清单
 @CalledBy: Copy()
 @Input: #const char *p: 字符串常量-用来存放需要读取的文件名
 @Return: #head: 正常退出，返回新链表的表头指针
          #NULL: 异常退出，申请空间失败，返回空
 @Others: 读取文件并创建新链表接受
*************************************************/
StuPtr Readfile2(const char* p){
        FILE *fp=fopen(p,"r");
    if(!fp){    //  打开文件失败
        printf("\n\n\n\n\n||->>                                            Can't open!");
        return NULL;

    }else{      //  打开文件成功
        StuPtr head,p1;     //  head->新建链表头   p1->工具指针
        head=(StuPtr)malloc(sizeof(Stu));

        if(!head){          //  申请失败
            printf("\n\n\n\n\n||->>                                            Can't malloc!");
            fclose(fp);
            return NULL;

        }else{
            head->next=NULL;    //  初始化head->next

            while(!feof(fp)){
                p1=(StuPtr)malloc(sizeof(Stu));//   读取文件数据
                fscanf(fp,"%s%s\t%s\t%lf\t%lf\t%lf\t%lf\t%d\n",p1->Stu_ID,
p1->Name,p1->Class,&p1->Math,&p1->English,&p1->Physics,&p1->Total_Points,&p1->Rank);
                if(head->next==NULL){
                    p1->next=NULL;  //  头指针指向的第一个元素
                }else{
                    p1->next=head->next;
                }
                head->next=p1;
            }

        }
        fclose(fp); //  关闭文件
        return head;//  返回头指针
    }
}

/*************************************************
 @Function: TeacherMenu
 @Description: 显示教师菜单界面
 @Calls: Copy()、Save()、Sort()、Add()、Del()、Stat()、Seek()、ShowAll()、Entering()
 @CalledBy: LoginTeacherSystem()
 @Input:
 @Return: 空类型，无返回值
 @Others: 显示教师菜单界面，调用不同子函数完成各个功能
*************************************************/
void TeacherMenu(){

    int option;
ErrorTeacher:
    while(1){
        system("cls");
        printf("\n\n                 ||****************************************MENU****************************************||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||***********************************TEACHER USER*************************************||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||====================================================================================||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Please enter your choice<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||====================================================================================||\n");
        printf("                 ||                       1.Input Data               2.Display All Records             ||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||                       3.Query                    4.Statistics                      ||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||                       5.Delete                   6.Add                             ||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||                       7.Sort                     8.Save File                       ||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||                       9.Copy File                10.Logout                         ||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||====================================================================================||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||****************************************END*****************************************||\n");
        printf("                 ||->>      Please input your option:");

        scanf("%d",&option);
        switch(option){

            case 1:
                system("cls");
                S=Entering(S);

                fflush(stdin);
                getchar();
                break;
            case 2:
                system("cls");
                ShowAll(S);

                fflush(stdin);
                getchar();
                break;
            case 3:
                system("cls");
                Seek(S);

                fflush(stdin);
                getchar();
                break;
            case 4:
                system("cls");
                Stat(S);

                fflush(stdin);
                getchar();
                break;
            case 5:
                system("cls");
                Del(S);

                fflush(stdin);
                getchar();
                break;
            case 6:
                system("cls");
                Add(S);

                fflush(stdin);
                getchar();
                break;
            case 7:
                system("cls");
                Sort(S);

                fflush(stdin);
                getchar();
                break;
            case 8:
                system("cls");
                Save(S);

                fflush(stdin);
                getchar();
                break;
            case 9:
                system("cls");
                Copy(S);

                fflush(stdin);
                getchar();
                break;
            case 10:
                return;
            default:

                system("cls");
                printf("\n\n\n                 ||***********************************TEACHER USER*************************************||\n");
                printf("                 ||                                                                                    ||\n");
                printf("                 ||====================================================================================||\n");
                printf("                 ||                                                                                    ||\n");
                printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ERROR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
                printf("                 ||                                                                                    ||\n");
                printf("                 ||                              Error!Please input 1-10 !                              ||\n");
                printf("                 ||                                                                                    ||\n");
                printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ERROR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
                printf("                 ||                                                                                    ||\n");
                printf("                 ||====================================================================================||\n");
                printf("                 ||                                                                                    ||\n");
                printf("                 ||********************Please [enter] to proceed to the next step**********************||\n");

                fflush(stdin);
                getchar();
                goto ErrorTeacher;//错误处理，跳回输入
        }
    }
}

/*************************************************
 @Function: StudentMenu
 @Description: 显示学生菜单界面
 @Calls: Sort()、Stat()、Seek()、ShowAll()、testData()
 @CalledBy: main()
 @Input:
 @Return: 空类型，无返回值
 @Others: 显示学生菜单界面，调用不同子函数完成各个功能
*************************************************/
void StudentMenu(){
    int option;
ErrorStudent:
    while(1){
        system("cls");
        printf("\n\n                 ||****************************************MENU****************************************||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||***********************************STUDENT USER*************************************||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||====================================================================================||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Please enter your choice<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||====================================================================================||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||                                 1.IQuery                                           ||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||                                 2.Statistics                                       ||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||                                 3.Display All Records                              ||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||                                 4.Logout                                           ||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||====================================================================================||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||****************************************END*****************************************||\n");
        printf("                 ||->>      Please input your option:");

        scanf("%d",&option);
        switch(option){
            case 1:
                if(!testData(S)){
                    return;
                }
                Seek(S);
                fflush(stdin);
                getchar();
                break;
            case 2:
                if(!testData(S)){
                    return;
                }
                Sort(S);
                fflush(stdin);
                getchar();
                break;
            case 3:
                if(!testData(S)){
                    return;
                }
                ShowAll(S);
                fflush(stdin);
                getchar();
                break;
            case 4:
                return;
            default:
                system("cls");
                printf("\n\n\n                 ||***********************************STUDENT USER*************************************||\n");
                printf("                 ||                                                                                    ||\n");
                printf("                 ||====================================================================================||\n");
                printf("                 ||                                                                                    ||\n");
                printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ERROR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
                printf("                 ||                                                                                    ||\n");
                printf("                 ||                              Error!Please input 1-4 !                              ||\n");
                printf("                 ||                                                                                    ||\n");
                printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ERROR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
                printf("                 ||                                                                                    ||\n");
                printf("                 ||====================================================================================||\n");
                printf("                 ||                                                                                    ||\n");
                printf("                 ||********************Please [enter] to proceed to the next step**********************||\n");

                fflush(stdin);
                getchar();
                goto ErrorStudent;//错误处理，跳回输入
        }

    }
}

/*************************************************
 @Function: LoginTeacherSystem
 @Description: 显示教师登陆界面
 @Calls: TeacherMenu()
 @CalledBy: main()
 @Input:
 @Return: 空类型，无返回值
 @Others: 显示教师登陆界面，账号密码正确即可进入教师菜单界面，反之则返回登陆界面
*************************************************/
void LoginTeacherSystem(){
    char tempaccount[20];
    char password[20];
    printf("\n\n\n                 ||********************************ADMIN LOGIN SYSTEM********************************||\n\n");
    fflush(stdin);
    printf("                            Please input your account number :");
    gets(tempaccount);
    printf("                            Please input your password       :");
    fflush(stdin);
    gets(password);
    if(strcmp(tempaccount,"3120005180")||strcmp(password,"3120005180")){
        system("cls");
        printf("\n\n\n                 ||*************************************** USER ***************************************||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||====================================================================================||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ERROR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||                      Error!Your account/password is wrong!                         ||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ERROR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||====================================================================================||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||********************Please [enter] to proceed to the next step**********************||\n");
        fflush(stdin);
        getchar();
        return;
    }else{
        system("cls");
        printf("\n\n\n                 ||*************************************** USER ***************************************||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||====================================================================================||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CORRECT<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||                    Input correct!   Welcome to the administrator system!           ||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CORRECT<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||====================================================================================||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||********************Please [enter] to proceed to the next step**********************||\n");
        fflush(stdin);
        getchar();
        TeacherMenu();
    }
}

/*************************************************
 @Function: testData
 @Description: 用于学生系统检测是否初始化
 @Calls:
 @CalledBy: StudentMenu()
 @Input: #StuPtr S: 结构体指针-储存学生信息的链表表头
 @Return: #0: false-表示还没有录入数据初始化
          #1: right-表示已经初始化
 @Others: 通过判断表头S是否为空，返回相应的值来确定是否进行下一步操作
*************************************************/
int testData(StuPtr S){
    system("cls");
    if(S==NULL){
        printf("\n\n\n                 ||***********************************STUDENT USER*************************************||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||====================================================================================||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ERROR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||               Please input the data by the teacher,and then try again!             ||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ERROR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||====================================================================================||\n");
        printf("                 ||                                                                                    ||\n");
        printf("                 ||********************Please [enter] to proceed to the next step**********************||\n");
        fflush(stdin);
        getchar();
        return 0;
    }
    return 1;
}




