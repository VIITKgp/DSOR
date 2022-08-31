 #include<stdio.h>
 #include<math.h>
 #include<stdlib.h>
 #define MIN -1000
 #define MAX 1000

 struct nodetype
 {
  char board[3][3];
  int turn;
  struct nodetype *child, *next;
 };
 typedef struct nodetype *NODEPTR;

 NODEPTR getnode()
 {
    NODEPTR p;
    p=(NODEPTR)malloc(sizeof(struct nodetype));
    p->child = NULL;
    p->next = NULL;
    return (p);
 }

 int value(char g[3][3])
 {
 int i=0,j=0,cal=0;
        for(i=0;i<3;i++)
        {
             if(g[i][0] == '-' || g[i][0]== 'X')
               if(g[i][1] == 'X' || g[i][1] == '-')
                 if(g[i][2] == 'X' || g[i][2] == '-')
                  {
                   if (g[i][0] == g[i][1] && g[i][1] == g[i][2])
                      cal=cal+1000;
                      cal++;
                  }
             if(g[i][0] == '-' || g[i][0]== '0')
               if(g[i][1] == '0' || g[i][1] == '-')
                 if(g[i][2] == '0' || g[i][2] == '-')
                   {if (g[i][0] == g[i][1] && g[i][1] == g[i][2])
                      cal=cal-1000;
                     cal--;

                   }

        }
        for(j=0;j<3;j++)
        {
             if(g[0][j] == '-' || g[0][j]== 'X')
               if(g[1][j] == 'X' || g[1][j] == '-')
                 if(g[2][j] == 'X' || g[2][j] == '-')
                   { if (g[0][j] == g[1][j] && g[1][j] == g[2][j])
                      cal=cal+1000;
                      cal++;
                   }

             if(g[0][j] == '-' || g[0][j]== '0')
               if(g[1][j] == '0' || g[1][j] == '-')
                 if(g[2][j] == '0' || g[2][j] == '-')
                   { if (g[0][j] == g[1][j] && g[1][j] == g[2][j])
                      cal=cal - 1000;

                       cal--;
        }}
            if(g[0][0] == '-' || g[0][0]== 'X')
               if(g[1][1] == 'X' || g[1][1] == '-')
                 if(g[2][2] == 'X' || g[2][2] == '-')
                   {if (g[0][0] == g[1][1] && g[1][1] == g[2][2])
                      cal=cal+1000;
                      cal++;
                   }

             if(g[0][0] == '-' || g[0][0]== '0')
               if(g[1][1] == '0' || g[1][1] == '-')
                 if(g[2][2] == '0' || g[2][2] == '-')
                   {if (g[0][0] == g[1][1] && g[1][1] == g[2][2])
                      cal=cal-1000;
                      cal--;
                   }
            if(g[2][0] == '-' || g[2][0]== 'X')
               if(g[1][1] == 'X' || g[1][1] == '-')
                 if(g[0][2] == 'X' || g[0][2] == '-')
                   {if (g[2][0] == g[1][1] && g[1][1] == g[0][2])
                      cal=cal+1000;
                      cal++;
                   }

            if(g[2][0] == '-' || g[2][0]== '0')
               if(g[1][1] == '0' || g[1][1] == '-')
                 if(g[0][2] == '0' || g[0][2] == '-')
                   {if (g[2][0] == g[1][1] && g[1][1] == g[0][2])
                      cal=cal-1000;
                      cal--;
                   }
   return cal;
}



int calculate(NODEPTR NEW,int nextturn)
{   int curr_val;
    if(!NEW) return ((nextturn == 1)?MIN:MAX);
     if(nextturn == 1)
         NEW->turn = NEW->turn >= calculate(NEW->child,nextturn) ? NEW->turn:calculate(NEW->child,nextturn);

     else   NEW->turn = NEW->turn <= calculate(NEW->child,nextturn) ? NEW->turn:calculate(NEW->child,nextturn);

     curr_val = calculate(NEW->next,nextturn);
     if(nextturn == 1)
         curr_val = NEW->turn >= curr_val ? NEW->turn:curr_val;

     else   curr_val = NEW->turn <=  curr_val?NEW->turn:curr_val;
    return curr_val ;
}

NODEPTR record(int nextturn,char g[3][3])
{
    NODEPTR p,root,NEW;
    char ch;
    if(nextturn==1) ch= 'X';
    else ch= '0';
    p=getnode();
    root=getnode();
    NEW=getnode();
    for(int i=0;i<3;i++)
     for(int j=0;j<3;j++)
      p->board[i][j] = g[i][j];
    root= NULL;
    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    {   for(int m=0;m<3;m++)
            for(int n=0;n<3;n++)
                p->board[m][n] = g[m][n];

         if(p->board[i][j] != '-')
          continue;

          else
            {
              p->board[i][j] = ch;
              NEW = p;
              NEW->turn = value(NEW->board);

             p->next = getnode();
             p=p->next;
             NEW->next = p;

             if(!root)
                 root= NEW;
            }
    }
    NEW->next = NULL;
    free(p);
    return root;
}

void calmove(NODEPTR NEW,int level,int nextturn)
{
      if(!NEW || !level)
            return;
       else
        {
          NEW->child= record(nextturn,NEW->board);
          calmove(NEW->child,level-1,-nextturn);
          calmove(NEW->next,nextturn,level);
        }
}

void tictactoe()
{
    int level,nextturn;
    NODEPTR get,NEW;
    get=getnode();
    NEW= getnode();

    char board[3][3];
    printf("Enter the current position: \nUse 'X' for first player and '0' for second player.\nUse '-' For empty places!\n");
    printf("An Example of a valid input is:\n - | - | X |\n___|___|___|\n X | 0 | - |\n___|___|___|\n - | 0 | - |\n___|___|___|\n\nEnter Here:\n");

	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			scanf("%s",&board[i][j]);
		}
	}

    for(int i=0;i<3;i++)
     for(int j=0;j<3;j++)
      get->board[i][j] = board[i][j];
    for(int i=0;i<3;i++)
    {
     for(int j=0;j<3;j++)
      printf(" %c |",get->board[i][j]);
     printf("\n___|___|___|\n");
     }
     printf("Whose turn it is?\n 1 for 'X' turn\n 0 for '0' turn\n");
     scanf("%d",&nextturn);
     printf("How many future turns should look ahead for ::\n (Example 4) \n ");
     scanf("%d",&level);
     calmove(get,level-1,nextturn);

    get->turn = calculate(get->child,1);
     NEW=get->child;
     while(NEW)
      {
        if(NEW->turn == get->turn )
             break;
         NEW= NEW->next;
     }
    printf("\nThe position of the board with the best move played is:\n");
    for(int i=0;i<3;i++)
    {
     for(int j=0;j<3;j++)

     printf(" %c |",NEW->board[i][j]);
    printf("\n___|___|___|\n");
   }

}



int main()
{
    tictactoe();
    return 0;
}
