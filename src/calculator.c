#include<stdio.h>
int main()
{
  int a,b,choice;
  printf("enter the elements :");
  scanf("%d %d",&a,&b);
  while(1)
    {
      printf("\nenter the choice:");
      scanf("%d",&choice);
      switch(choice)
        {
          case 1:
            int add = (a+b);
            printf("addition is :%d\n",add);
            break;
          case 2:
            int sub = (a-b);
            printf("substraction is :%d\n",sub);
            break;
          case 3:
            int mul = (a*b);
            printf("multiplication is :%d\n",mul);
            break;
          case 4:
            if((a != 0)&& (b != 0))
            {
              float div = (a/b);
              printf("division is :%f\n"div);
            }
            break;
          default :
            break;
            
  return 0;
}
