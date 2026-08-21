#include <stdio.h>

int main()
{
    int n,i,rev=0,bit;
    scanf("%d",&n);
    for(i=0;i<n;i--)
    {
        if(1<<i)
            printf("1");
            else
            {
                printf(0);
                        }
    while(n!=0)
    {
        bit=n&1;
        rev=(rev<<1)|bit;
        n=n>>1;
    }
    printf("%d",rev);
}