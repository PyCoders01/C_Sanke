#include<windows.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define MX 100
#define MY 40

int x=30,y=10;
int randx,randy;
int size=2;
int score=0;
int previous_score=0;
char present_name[10];
char previous_name[10];

int bodyx[1000]={30,29,28};
int bodyy[1000]={10,10,10};

void subborder()
{
    int i,j;
    for(i=0;i<=MX;i++)
    {
        for(j=MY+1;j<=MY+8;j++)
        {
            if(i==0||j==MY+1||i==MX||j==MY+8)
            {
                gotoxy(i,j);
                printf("+");
            }
        }
    }
}

void loading_animation()
{
    int i,j;
    gotoxy(29,12);
    printf("==> SNAKE GAME BY VIGNESH HEGDE <==\n");
    gotoxy(42,14);
    printf("LOADING");
    gotoxy(39,15);
        printf("____________");

    for(j=0;j<=1;j++)
    {
        for(i=1;i<=10;i++)
        {
            gotoxy(40+i,15);
            printf(">>");
            delay(70);
            gotoxy(40+i,15);
            printf("__");
        }
        for(i=9;i>=0;i--)
        {
            gotoxy(40+i,15);
            printf("<<");
            delay(70);
            gotoxy(40+i,15);
            printf("__");
        }
    }
}

void scoreupdate()
{
    FILE *fptr;
    fptr=fopen("SCORE.txt","w");
    fprintf(fptr,"%s %d",present_name,score);
    fclose(fptr);
}
int history(void)
{
    char c;
    int i;
    FILE *fptr;
    fptr=fopen("SCORE.txt","r");
    fscanf(fptr,"%s %d",previous_name,&previous_score);
          fclose(fptr);
}
COORD coord={0,0};
void delay(unsigned int msec)
{
        clock_t till=msec+clock();

        while(till>=clock());
}

void gotoxy(int xxx, int yyy)
{
        coord.X=xxx;
        coord.Y=yyy;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void border()
{
    int i,j;


    for(i=0;i<=MY;i++)
    {
        for(j=0;j<=MX;j++)
        {
            if(i==0||j==0||i==MY||j==MX)
            {
                gotoxy(j,i);
                printf("+");
            }


        }
    }
}

void random()
{
	int i;

	point:
	randx=rand()%(MX-1+1-1)+1;
    randy=rand()%(MY-1+1-1)+1;
	for(i=0;i<size;i++)
    {
        if(randx==bodyx[i]&&randy==bodyy[i])
        {
			goto point;
        }

    }




}

void food()
{
    random();
    gotoxy(randx,randy);
    printf("*\n");

}

int motion(int key)
{
    int i,j;

    if(key=='a'||key=='A')
    {
        delay(125);
        gotoxy(bodyx[size],bodyy[size]);
        printf(" \n");
        --bodyx[0];
        if(bodyx[0]==0)
            return 1;
        gotoxy(bodyx[0],bodyy[0]);
        printf("#\n");
        return 0;
    }

    else if(key=='d'||key=='D')
    {
        delay(125);
        gotoxy(bodyx[size],bodyy[size]);
        printf(" \n");
        ++bodyx[0];
        if(bodyx[0]==MX)
            return 1;
        gotoxy(bodyx[0],bodyy[0]);
        printf("#\n");
        return 0;
    }

    else if(key=='w'||key=='W')
    {
        delay(175);
        gotoxy(bodyx[size],bodyy[size]);
        printf(" \n");
        --bodyy[0];
        if(bodyy[0]==0)
            return 1;
        gotoxy(bodyx[0],bodyy[0]);
        printf("#\n");
        return 0;
    }

    else if(key=='s'||key=='S')
    {
        delay(175);
        gotoxy(bodyx[size],bodyy[size]);
        printf(" \n");
        ++bodyy[0];
        if(bodyy[0]==MY)
            return 1;
        gotoxy(bodyx[0],bodyy[0]);
        printf("#\n");
        return 0;
    }
}

char oppkey(char key)
{
    if(key=='a'||key=='A')
        return 'd';

    else if(key=='d'||key=='D')
        return 'a';

    else if(key=='w'||key=='W')
        return 's';

    else if(key=='s'||key=='S')
        return 'w';


}

void end(void)
{
        char x='w';
        system("cls");
        border();
        gotoxy(37,21);
        printf("YOUR SCORE = %d",score);



        while(1)
        {
            delay(100);
            gotoxy(40,19);
            printf("GAME OVER\n");
            gotoxy(32,23);
            printf("==>  Press X to Exit  <==\n");
            delay(500);
            gotoxy(40,19);
            printf("                   ");
            gotoxy(32,23);
            printf("                             \n");
            if(kbhit())
            {
                    break;
            }

        }
}

void main()
{
    int i;
    int crash_flag;
    int exit_flag=0;
    int h_flag=0;

    char key='a',prkey='a';

    border();
    loading_animation();
    system("cls");
    border();
    gotoxy(40,10);
    printf("ENTER NAME: ");
    scanf("%s",present_name);
    system("cls");
    border();
    food();
    gotoxy(25,46);
    printf(" > YOUR SCORE = %d",score);
     gotoxy(25,42);
     printf(" ==> Press p to pause <==\n");
     subborder();
     history();
     gotoxy(25,44);
     if(previous_score==0)
        printf(" > NO HIGH SCORE");
     else
     printf(" > HIGHE SCORE BY %s = %d\n",previous_name,previous_score);

    while(1)
    {


        if(kbhit())
        {
            key=getch();
            if(key=='p'||key=='P')
            {
                start :
                gotoxy(25,42);
                printf("                                      \n");
                delay(100);
                gotoxy(25,42);
                printf(" ==> Press motion keys continue <== \n");
                    delay(500);
                if(!kbhit())
                   {
                       goto start;
                   }
                if(kbhit)
                {
                    key=getch();
                    if(key=='P'||key=='p')
                        goto start;
                }


                gotoxy(25,42);
                printf("                                         \n");
                gotoxy(25,42);
                printf(" ==> Press p to pause <==\n");
            }

            if(key!=oppkey(prkey))
            {
                crash_flag=motion(key);
                prkey=key;
            }
            else
            {
                crash_flag=motion(prkey);
            }
        }

        else
        {
            crash_flag=motion(prkey);
        }

        if(crash_flag)
        {
            end();
            break;
        }

        for(i=size;i>0;i--)
        {
            bodyx[i]=bodyx[i-1];
            bodyy[i]=bodyy[i-1];
        }

        for(i=2;i<size;i++)
        {
            if(bodyx[0]==bodyx[i]&&bodyy[0]==bodyy[i])
            {
                end();
                exit_flag=1;
            }

        }
            if(exit==1)
            break;

        if(bodyx[0]==randx&&bodyy[0]==randy)
        {
            ++size;
            food();
            score+=7;
            gotoxy(25,46);
            printf("                        ");
            gotoxy(25,46);
            printf(" > YOUR SCORE = %d\n",score);
            if(score>previous_score)
            {
                h_flag=1;
                gotoxy(25,44);
                printf(" > NEW HIGHEST SCORE BY %s of %d\n",present_name,score);
            }
        }


    }
    if(h_flag==1)
    {
        scoreupdate();
    }
}
