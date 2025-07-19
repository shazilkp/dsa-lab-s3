#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student{
    char name[30];
    char roll[10];
    int age;
};

struct linkedl{
    struct student student;
    struct linkedl* next;
};

typedef struct linkedl ll;

int h(struct student stu){
    int i=0;
    int sum=0;
    while(stu.name[i] != '\0'){
        sum = sum + stu.name[i];
        i++;
    }
    sum+=stu.age; 
    return sum%4;
}

ll* createnode(struct student stu){
    ll * node = (ll*)malloc(sizeof(ll));
    node->student = stu;
    node->next = NULL;
    return node;
}

void insertnode(ll** head,struct student stu){
    ll* node = createnode(stu);
    ll * x = *head;
    if(*head == NULL){
        *head = node;
        return;
    }
    
    while(x->next){
        x=x->next;
    }
    x->next = node;
 //   printf("%s %s %d",x->student.name,x->student.roll,x->student.age);;
}

struct student searchHash(char * name,ll * hash[]){
    struct student stu={" "," ",-1};
    int f=0;
    for(int i = 0 ; i < 4 && f == 0; i++){
        ll * x =hash[i];
        while(x){
            if(!strcmp(x->student.name,name)){
                stu = x->student;
                f=1;
                break;
            }
            x=x->next;
        }
    }

    return stu;
}

void GroupIndexAndSplit(char * name, ll* hash[]){
    struct student stu  = searchHash(name,hash);
    printf("%d\n",h(stu));
}

ll * s_insert(ll * head, struct student stu) {
    ll * node = createnode(stu);
    if (head == NULL || strcmp((head)->student.name, stu.name) > 0) {
        node->next = head;
        head = node;
        return head;
    }

    ll* x = head;
    while (x->next != NULL && strcmp(x->next->student.name, stu.name) < 0) {
        x = x->next;
    }

    node->next = x->next;
    x->next = node;
    return head;
}

void print(ll* hash[]){
    for(int i =0 ; i < 4; i++){
        ll * x = hash[i];
        printf("%d. ",i);
        while(x != NULL){
            printf("%s -> ",x->student.name);
            x=x->next;
        }
        printf("NULL\n");
    }
}

void Group_CountAndList(ll *hash[],int k){
    ll * x = hash[k];
    int count = 0;
    while(x){
        count++;
        x=x->next;
    }
    if(count == 0){
        printf("0\n");
        return;
    }
    printf("%d ",count);
    x=hash[k];
    ll * copy = NULL;
    for(int i = 0;i < count; i++){
        copy = s_insert(copy,x->student);
        x =x ->next;
    }
    while(copy){
        printf("%s ",copy->student.name);
        copy= copy->next;
    }
    printf("\n");
}

void GroupListByBranch(ll * hash[], int k, char b[]){
    char branch[3];
    if((b[0] == 'C' && b[1] == 'S') || (b[0] == 'c' && b[1] == 's')){
        strcpy(branch,"CS");
    }
    if((b[0] == 'E' && b[1] == 'C') || (b[0] == 'e' && b[1] == 'c')){
        strcpy(branch,"EC");
    }
    if((b[0] == 'E' && b[1] == 'E') || (b[0] == 'e' && b[1] == 'e')){
        strcpy(branch,"EE");
    }
    if((b[0] == 'C' && b[1] == 'E') || (b[0] == 'c' && b[1] == 'e')){
        strcpy(branch,"CE");
    }
    ll * x = hash[k];
    int count = 0;
    while(x){
        if(x->student.roll[7] == branch[0] && x->student.roll[8] == branch[1]){
            printf("%s ",x->student.name);
            count++;
        }
        x = x->next;
    }
    if(count!=0){
        printf("\n");
    }
    if(count == 0){
        printf("-1\n");
    }
}

void StudentDetails(char * roll,ll* hash[]){
    for(int i = 0 ; i < 4; i++){
        ll * x = hash[i];
        while(x){
            if(!strcmp(x->student.roll,roll)){
                printf("%s %d %s\n",x->student.name,x->student.age,&x->student.roll[7]);
                return;
            }
            x=x->next;
        }
    }
    printf("-1\n");

}

void GroupTransferAllByBranch(ll * hash[],int source,int desti,char b[]){
    char branch[3];
    if((b[0] == 'C' && b[1] == 'S') || (b[0] == 'c' && b[1] == 's')){
        strcpy(branch,"CS");
    }
    if((b[0] == 'E' && b[1] == 'C') || (b[0] == 'e' && b[1] == 'c')){
        strcpy(branch,"EC");
    }
    if((b[0] == 'E' && b[1] == 'E') || (b[0] == 'e' && b[1] == 'e')){
        strcpy(branch,"EE");
    }
    if((b[0] == 'C' && b[1] == 'E') || (b[0] == 'c' && b[1] == 'e')){
        strcpy(branch,"CE");
    }
    ll * s = hash[source];
    int count =0;
    ll * prev = NULL;
    while(s){
        if(s->student.roll[7] == branch[0] && s->student.roll[8] == branch[1]){
            count++;
            insertnode(&hash[desti],s->student);
            if(prev == NULL){
                hash[source] = hash[source]->next;
            }
            else{
                prev->next = s->next;
            }
        }
        else{
            prev = s;
        }
        s = s->next;
    }
    printf("%d\n",count);
}

int main(){
    ll* hash[4] = {NULL};
    int n;
    scanf("%d",&n);
    struct student students[n];
    char name[30];
    char roll[10];
    int age;
    int k;
    int s,desti;
    char b[3];
   // struct student stu;
    for(int i = 0 ; i < n ; i++){
        scanf("%s %s %d",name,roll,&age);
        students[i].age = age;
        strcpy(students[i].name,name);
        strcpy(students[i].roll,roll);
       // printf("%s %s %d",students[i].name,students[i].roll,students[i].age);
        insertnode(&hash[h(students[i])],students[i]);
        //insertnode(&hash[2],students[i]);
    }
    char c;
    while(1){
        scanf("%c",&c);
        if(c == 'f'){
            break;
        }
        switch(c){
            case 'a':{
                scanf("%s",name);
                GroupIndexAndSplit(name,hash);
                break;
            }

            case 'b':{
                scanf("%d",&k);
                Group_CountAndList(hash,k);
                break;
            }

            case 'c':{
                scanf("%d %s",&k,b);
                GroupListByBranch(hash,k,b);
                break;
            }

            case 'd':{
                scanf("%s",roll);
                StudentDetails(roll,hash);
                break;
            }

            case 'e':{
                scanf("%d %d %s",&s,&desti,b);
                GroupTransferAllByBranch(hash,s,desti,b);
                break;
            }
            /*
            case 'p':{
                print(hash);
                break;
            }
            */

            default:break;

        }
    }
}