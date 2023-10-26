#include<stdio.h>
#include<stdlib.h>
#include "BigInteger.h"
void insert_tail(struct BigInteger*num,int element)
{
    node *temp=(node*)malloc(sizeof(node));
    if(temp==NULL)
    {
        printf("memory allocation failed\n");
        exit(1);

    }
    temp->data=element;
    temp->next=NULL;
    num->size=num->size+1;
    if(num->head==NULL)
    {
        num->head=temp;
        return;
    }
    node*itr=num->head;
    while(itr->next!=NULL)
    {
        itr=itr->next;
    }
    itr->next=temp;

}
void add_node(int element,struct BigInteger* num)
{
    if(num==NULL)
    {
        printf("null is passed\n");
        exit(1);
    }
    node*temp=(node*)malloc(sizeof(node));
    if(temp==NULL)
    {
        printf("memory allocation failed \n");
        exit(1);
    }
    temp->data=element;
    temp->next=num->head;
    num->head=temp;
    num->size=num->size+1;
}
int isEqualToZero(struct BigInteger num)
{
    node*itr=num.head;
    while(itr!=0)
    {
        if(itr->data!=0)
        {
            return 0;
        }
        itr=itr->next;
    }
    return 1;
}

struct BigInteger initialize(char *str)
{
    struct BigInteger num;
    num.head=NULL;
    num.size=0;
    int i=0;
    if (str[0] == '-') {
        num.sign='-';
        i++;
    }
    else{
        num.sign='+';
    }

    while (str[i] != '\0') {

        if (str[i] >= '0' && str[i] <= '9') {
            int digit = str[i] - '0';
            add_node(digit, &num);
        }
        else {
        printf("enter a valid digit\n");
        exit(1);
        }
        i++;
    }

    return num;
}

struct BigInteger get_num()
{
    struct BigInteger num;

    num.head=NULL;
    num.size=0;
    char c;
    if ((c = getchar()) == '-') {
        num.sign='-';
        c = getchar();
    }
    else{
        num.sign='+';
    }
    while (c != '\n') {
        if (c >= '0' && c <= '9') {
            int digit = c - '0';
            add_node(digit, &num);
        }
        else {
        printf("enter a valid digit\n");
        exit(1);
        }
        c = getchar();
    }

    return num;
}

void display_reverse(node*head)
{
    if(head==NULL)
    {
     return;
    }
    display_reverse(head->next);
    printf("%d",head->data);
}
void display(struct BigInteger num)
{

    if(num.sign=='-')
    {
        printf("%c",'-');
    }
    if(num.head==NULL)
    {
        return;
    }

   display_reverse(num.head);
}
struct BigInteger create_empty()
{
    struct BigInteger num;

    num.head=NULL;
    num.sign='+';
    num.size=0;
    return num;
}
struct BigInteger add(struct BigInteger num1, struct BigInteger num2){
    struct BigInteger num3=create_empty();

   if(num1.sign=='-' && num2.sign=='-')
    {
        num3.sign='-';
    }
    else if(num1.sign=='-' )
    {
      num1.sign='+';
      num3=sub(num2,num1);
      num1.sign='-';
      return num3;
    }
    else if(num2.sign=='-')
    {
      num2.sign='+';
      num3=sub(num1,num2);
      num2.sign='-';
      return num3;
    }
    node*l1=num1.head,*l2=num2.head;
    int sum=0;
    int carry=0;
    while(l1!=NULL && l2!=NULL)
    {
        sum=l1->data+l2->data+carry;
        carry=sum/10;
        sum=sum%10;
        insert_tail(&(num3),sum);
        l1=l1->next;
        l2=l2->next;
    }
   while(l1!=NULL)
    {
        sum=l1->data+carry;
        carry=sum/10;
        sum=sum%10;
        insert_tail(&(num3),sum);
        l1=l1->next;
    }
     while(l2!=NULL)
    {
        sum=l2->data+carry;
        carry=sum/10;
        sum=sum%10;
        insert_tail(&(num3),sum);
        l2=l2->next;
    }
    if(carry!=0)
    {
        insert_tail(&(num3),carry);
    }
    return num3;

}
node* reverse(node*head)
{
    node*back=NULL,*front=NULL,*current=head;
    while(current!=NULL)
    {
        front=current->next;
        current->next=back;
        back=current;
        current=front;
    }
    return back;
}
struct BigInteger remove_trailing_zeroes(struct BigInteger num)
{

    if(num.head==NULL || num.head->next==NULL)
    {
        return num;
    }
     num.head=reverse(num.head);
    while(num.head!=NULL &&(num.head)->next!=NULL )
    {

       if( (num.head)->data==0)
       {
            node*temp=num.head;
            num.head=(num.head)->next;
            num.size=num.size-1;

            free(temp);
        }
        else
        {
            break;
        }
    }
 num.head= reverse(num.head);
 return num;
}
/*struct BigInteger remove_trailing_zeroes(struct BigInteger num)
{

    if(num.head==NULL || num.head->next==NULL)
    {
        return num;
    }
    struct BigInteger copy=create_empty();
    node*itr=num.head;
    while(itr!=NULL)
    {
        add_node(itr->data,&copy);
        itr=itr->next;
    }
    //itr=copy.head;
     //num.head=reverse(num.head);
    while(copy.head!=NULL &&(copy.head)->next!=NULL )
    {

       if( (copy.head)->data==0)
       {
            node*temp=copy.head;
            copy.head=(copy.head)->next;
            copy.size=copy.size-1;

            free(temp);
        }
        else
        {
            break;
        }
    }
 copy.head= reverse(copy.head);
 return copy;
}*/
int compare(struct BigInteger num1,struct BigInteger num2)
{

    //printf("num1 %d num2 %d",num1.size,num2.size);
    remove_trailing_zeroes(num1);
    remove_trailing_zeroes(num2);
    int return_val=-1;
    //it would return 1 if n2 is greater 0 if smaller and if equal then -1
    if((num2.size)>(num1.size))
    {
        return 1;
    }
    else if((num2.size)<(num1.size))
    {
        return 0;
    }
    else if(num2.size==num1.size)
    {
        num1.head= reverse(num1.head);
        num2.head= reverse(num2.head);
        //printf("num1 \n");
        //display(num1);
        node*head1=num1.head,*head2=num2.head;
        while(head1!=NULL && head2!=NULL)
        {
            if((head2->data)>(head1->data))
            {

               //printf("",head2->data);
                return_val= 1;
                break;
            }
            else if((head2->data)<(head1->data))
            {
                return_val= 0;
                break;
            }
            head1=head1->next;
            head2=head2->next;
        }
        num1.head= reverse(num1.head);
        num2.head= reverse(num2.head);

    }
    return return_val;
}
struct BigInteger sub(struct BigInteger num1, struct BigInteger num2){

    num1=remove_trailing_zeroes(num1);
    num2=remove_trailing_zeroes(num2);
    node*l1=num1.head,*l2=num2.head;
    struct BigInteger num3=create_empty();
    if(num1.sign=='+' && num2.sign=='-')
    {
        num2.sign='+';
        num3=add(num1,num2);
        //num2.sign='-';
        num3.sign='+';
        return num3;
    }
    else if(num1.sign=='-'&& num2.sign=='+' )
    {
      num1.sign='+';
      num3=add(num2,num1);
     // num1.sign='-';
      num3.sign='-';
      return num3;
    }


     if(compare(num1,num2)==1)
    {
       // printf("ch");
        node*temp=l1;
        l1=l2;
        l2=temp;
        num3.sign='-';
    }

    int sub=0;
    int borrow=0;
    while(l1!=NULL && l2!=NULL)
    {
        sub=l1->data-l2->data+borrow;
        if(sub<0)
        {
            borrow=-1;
            sub=sub+10;
        }
        else
        {
            borrow=0;
        }
        insert_tail(&(num3),sub);
        l1=l1->next;
        l2=l2->next;
    }
   while(l1!=NULL)
    {
        sub=l1->data+borrow;
        if(sub<0)
        {
            borrow=-1;
            sub=sub+10;
        }
        else
        {
            borrow=0;
        }
        insert_tail(&(num3),sub);
        l1=l1->next;
    }
    if(num1.sign=='-'&& num2.sign=='-')
    {
     //   printf("\n the minus minus is being implemented\n");
        if(num3.sign=='-')
        {
            num3.sign='+';
        }
        else
        {
            num3.sign='-';
        }
    }
    num3=remove_trailing_zeroes(num3);
    return num3;
}

struct BigInteger mul(struct BigInteger n1,struct BigInteger n2)
{
    struct BigInteger result=create_empty(),mid;
    node*num1=n1.head,*num2=n2.head;
    if(num1==NULL || num2==NULL)
    {
        printf("the numbers are not initialized yet\n");
        return result;
    }
    int carry=0,product=0,i=0;
    while(num2!=NULL)
    {
        node*num1=n1.head;
        carry=0;
        mid=create_empty();
        for(int j=0;j<i;j++)
        {
            insert_tail(&(mid),0);
        }
        while(num1!=NULL)
        {
            product=(num1->data)*(num2->data)+carry;
            insert_tail(&(mid),product%10);
            carry=product/10;
            num1=num1->next;
        }

        if(carry>0)
        {
             insert_tail(&mid,carry);
        }

        result=add(mid,result);
        free(mid.head);
        num2=num2->next;
        i++;
    }
    if(n1.sign!=n2.sign)
    {
        result.sign='-';
    }
    return result;
}
struct BigInteger copy_BigInteger(struct BigInteger num)
{
    struct BigInteger copy=create_empty();
    node*itr=num.head;
    while(itr!=NULL)
    {
        insert_tail(&copy,itr->data);
        itr=itr->next;
    }
    return copy;
}
/*struct BigInteger decrement_by_one(struct BigInteger num)
{

    struct BigInteger temp=create_empty();
    add_node(1,&temp);
    struct BigInteger new_node= sub(num,temp);
    return new_node;
}*/
struct BigInteger increment_by_one(struct BigInteger num)
{

    struct BigInteger temp=create_empty();
    add_node(1,&temp);
    struct BigInteger new_node= add(num,temp);
    return new_node;
}


void sub_div(struct BigInteger dividend,struct BigInteger divisor,struct BigInteger*q,struct BigInteger*remain)
{
      dividend=remove_trailing_zeroes(dividend);
      divisor=remove_trailing_zeroes(divisor);


  int count=0;
  
 if(compare(dividend,divisor)==1)//it would return 1 if n2 is greater 0 if smaller and if equal then -1
 {
     *remain=copy_BigInteger(dividend);
     add_node(0,q);
     return ;
 }

  dividend.sign='+';
  divisor.sign='+';

 if( isEqualToZero(divisor))
 {
    printf("sub_div by zero is not possible\n");
    exit(1);
 }
  struct BigInteger rem;
  rem=create_empty();
  rem=copy_BigInteger(dividend);
  int comparision;
  do{
      rem=sub(rem,divisor);
      count++;
      if(rem.sign=='-')
      {
          break;
      }
    
      comparision=compare(divisor,rem);//it would return 1 if rem is greater, 0 if smaller and if equal then -1
  }while(comparision!=0);

  add_node(count,q);
 // printf("count%d\n",count);
 // insert_tail(q,count);
  *remain=rem;
}

struct BigInteger div1(struct BigInteger dividend,struct BigInteger divisor)
{
    //copying the numbers to the size of divisor
  if( isEqualToZero(divisor))
 {
    printf("sub_div by zero is not possible\n");
    exit(1);
 }

  struct BigInteger count=create_empty();
  add_node(0,&count);
 if(compare(dividend,divisor)==1)//it would return 1 if n2 is greater 0 if smaller and if equal then -1
 {
     return count;
 }
  struct BigInteger new_dividend,q,remain,rev_dividend;
  rev_dividend=create_empty();
  node*itr=dividend.head;
  while(itr!=NULL)
  {
      add_node(itr->data,&rev_dividend);
      itr=itr->next;
  }
  //display(rev_dividend);
  remain=create_empty();
  q=create_empty();
  new_dividend=create_empty();
  itr=rev_dividend.head;
 // display(rev_dividend);
  int i;
  for(i=0;i<divisor.size;i++)
  {
    //insert_tail(&new_dividend,itr->data);
    add_node(itr->data,&new_dividend);
    if(i==divisor.size)
    {
        break;
    }
    itr=itr->next;
  }
 // printf("dividend1: ");
 // display(new_dividend);
 // display(new_dividend);
  int sign=1;
  if(dividend.sign=='-' && divisor.sign=='+')
  {
      sign=-1;
  }
  else if(dividend.sign=='+' && divisor.sign=='-')
  {
     sign=-1;
  }
  divisor.sign='+';
  new_dividend.sign='+';


  while(itr!=NULL)
  {
      sub_div(new_dividend,divisor,&q,&remain);//it would append new q with would
      //insert_at_head
      
      add_node(itr->data,&remain);
      free(new_dividend.head);
      new_dividend.head=NULL;
      new_dividend=remain;
      itr=itr->next;
  }
  sub_div(new_dividend,divisor,&q,&remain);
  if(sign==-1)
  {
      q.sign='-';
  }
  q=remove_trailing_zeroes(q);
  return q;
}



struct BigInteger mod(struct BigInteger dividend,struct BigInteger divisor)
{
    //copying the numbers to the size of divisor
  if( isEqualToZero(divisor))
 {
    printf("sub_div by zero is not possible\n");
    exit(1);
 }

 if(compare(dividend,divisor)==1)//it would return 1 if n2 is greater 0 if smaller and if equal then -1
 {
     return dividend;
 }
  struct BigInteger new_dividend,q,remain,rev_dividend;
  rev_dividend=create_empty();
  node*itr=dividend.head;
  while(itr!=NULL)
  {
      add_node(itr->data,&rev_dividend);
      itr=itr->next;
  }
  //display(rev_dividend);
  remain=create_empty();
  q=create_empty();
  new_dividend=create_empty();
  itr=rev_dividend.head;
 // display(rev_dividend);
  int i;
  for(i=0;i<divisor.size;i++)
  {
    //insert_tail(&new_dividend,itr->data);
    add_node(itr->data,&new_dividend);
    if(i==divisor.size)
    {
        break;
    }
    itr=itr->next;
  }

  divisor.sign='+';
  new_dividend.sign='+';


  while(itr!=NULL)
  {
      sub_div(new_dividend,divisor,&q,&remain);//it would append new q with would
      //insert_at_head
      
      add_node(itr->data,&remain);
      free(new_dividend.head);
      new_dividend.head=NULL;
      new_dividend=remain;
      itr=itr->next;
  }
  sub_div(new_dividend,divisor,&q,&remain);
  remain=remove_trailing_zeroes(remain);
  return remain;
}
