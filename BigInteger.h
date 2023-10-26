# ifndef BigInteger_h
# define BigInteger_h

typedef struct node{
    int data;
    struct node*next;
}node;

struct BigInteger{
    node*head;
    char sign;
    long int size;
};

void insert_tail(struct BigInteger*num,int element);
void add_node(int element,struct BigInteger* num);
struct BigInteger initialize(char *str);
struct BigInteger get_num();
void display_reverse(node*head);
void display(struct BigInteger num);
struct BigInteger create_empty();
struct BigInteger add(struct BigInteger num1, struct BigInteger num2);
node* reverse(node*head);
struct BigInteger remove_trailing_zeroes(struct BigInteger num);
int compare(struct BigInteger num1,struct BigInteger num2);
struct BigInteger sub(struct BigInteger num1, struct BigInteger num2);
struct BigInteger mul(struct BigInteger n1,struct BigInteger n2);
struct BigInteger copy_BigInteger(struct BigInteger num);
struct BigInteger increment_by_one(struct BigInteger num);
struct BigInteger div1(struct BigInteger dividend,struct BigInteger divisor);
void sub_div(struct BigInteger dividend,struct BigInteger divisor,struct BigInteger*q,struct BigInteger*remain);
struct BigInteger mod(struct BigInteger dividend,struct BigInteger divisor);
int isEqualToZero(struct BigInteger num);
#endif