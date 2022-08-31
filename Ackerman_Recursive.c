//These functions works only till function values(2,3)

#include<stdio.h>
#include<math.h>

long long unsigned int Ackermann(int m, int n)
    {
        if(m > 1)
        {
            if (n > 1)
                return Ackermann(m - 1, Ackermann(m, n - 1)); // Using Recursion
            else if ((n == 1)&&(m>=2))
                return Ackermann(m - 1, 2);
        }
        else if(m == 1)
        {
            if(n >= 1)
                return pow(2,n);
        }

    }

void Get_NonRecursive_Ackerman()
 {
    unsigned long long int arr[3][17];   //non Recursive way
        for(int i=1;i<17;i++){  //arr[1][16] is calculated in order to calculate value in element(2,3)=arr(1,16)
            arr[1][i]=pow(2,i);
        }
        arr[2][1]=arr[1][2];
        for(int i=2;i<=3;i++){
        arr[2][i]=arr[1][arr[2][i-1]];
        }

        printf("Ackermann function using Non Recursive Method\n");
     for (int m = 1; m <= 2; ++m)
        {
        for (int n = 1; n <= 3; ++n)
            {
                printf("Ackermann(%d,%d) = %d ", m, n, arr[m][n]);
            }
            printf("\n");
        }
 }


 void Get_Recursive_Ackerman()
 {
     printf("Ackermann function using Recursive Method\n");
     for (int m = 1; m <= 3; ++m)
        {
        for (int n = 1; n <= 4; ++n)
            {
                printf("Ackermann(%d,%d) = %d ", m, n, Ackermann(m, n));
            }
            printf("\n");
        }
        printf("\n\n");
 }



int main()
{
  Get_Recursive_Ackerman();
  Get_NonRecursive_Ackerman();
        return 0;
}

