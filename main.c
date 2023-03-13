#include<stdio.h>
#include"mymalloc.h"

struct node{
    int data;
    struct node *next;
    struct node *prev;
}node;

int main()
{
    int *ptr1=(int *)MyMalloc(sizeof(int));//4 
    printf("ptr1 : %d\tAllocated size : %d\n",ptr1,sizeof(int));//36

    double *ptr2=(double *)MyMalloc(sizeof(double));//8
    printf("ptr2 : %d\tAllocated size : %d\n",ptr2,sizeof(double));//36+40=76

    char *ptr3=(char *)MyMalloc(100*sizeof(char));//100
    printf("ptr3 : %d\tAllocated size : %d\n",ptr3,100);//76+132=208

    struct node *ptr4=(struct node *)MyMalloc(10*sizeof(struct node));//240
    printf("ptr4 : %d\tAllocated size : %d\n",ptr4,240);//208+272=480

    float *ptr5=(float *)MyMalloc(10*sizeof(float));//40
    printf("ptr5 : %d\tAllocated size : %d\n",ptr5,40);//480+72=552

    MyFree(ptr1);//free 4
    MyFree(ptr2);//free 4+8+32=44
    MyFree(ptr3);//free 44+100+32=176

    int *ptr6=(int *)MyMalloc(24000);//24000
    printf("ptr6 : %d\tAllocated size : %d\n",ptr6,24000);//552+24032=24584

    int *ptr7=(int *)MyMalloc(500);//500
    printf("ptr7 : %d\t\tAllocated size : %d\n",ptr7,0);//24584+532=25116 overflow

    int *ptr8=(int *)MyMalloc(200);//200
    printf("ptr8 : %d\tAllocated size : %d\n",ptr8,200);//24584+232=24816

    int *ptr9=(int *)MyMalloc(200);//200
    printf("ptr9 : %d\t\tAllocated size : %d\n",ptr9,0);//overflow 232

    int *ptr10=(int *)MyMalloc(50);
    printf("ptr10 : %d\tAllocated size : %d\n",ptr10,50);//24816+82=24898

    MyFree(ptr4); //free  

    int *ptr11=(int *)MyMalloc(220);
    printf("ptr11 : %d\tAllocated size : %d\n",ptr11,220);

    int *ptr12=(int *)MyMalloc(100);
    printf("ptr12 : %d\tAllocated size : %d\n",ptr12,100);

    int *ptr13=(int *)MyMalloc(30);
    printf("ptr13 : %d\tAllocated size : %d\n",ptr13,30);

    int *ptr14=(int *)MyMalloc(500);
    printf("ptr14 : %d\t\tAllocated size : %d\n",ptr14,0);

    return 0;
}