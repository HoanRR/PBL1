#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct book
{
	char ID[20];
	char name[100];
	char author[200];
	char pub[200];
	long year;
	long amount; 
};

struct book *create_book(const char *id, const char *n, const char *a, const char *p, long y, long am) {
    struct book *bk= (book*)malloc(sizeof(book));
    strcpy(bk->ID, id);
    strcpy(bk->name, n);
    strcpy(bk->author, a);
    strcpy(bk->pub, p);
    bk->year = y;
    bk->amount = am;
    return bk;
}

struct booknode
{
	struct booknode *next;
	struct book *element;
};

typedef struct booknode booknode;
typedef struct book book;

booknode *makenode(book bk){
	booknode *newnode = (booknode*)malloc(sizeof(booknode));
	newnode->next=NULL;
	newnode->element = create_book(bk.ID, bk.name, bk.author, bk.pub, bk.year, bk.amount);;
	return newnode;
}

// in thu vien
void print_book(booknode *head){
	
	while(head!=NULL){
		printf("ID: %s \n Name: %s \n Author: %s \n Publisher: %s\n Year: %ld \n Amount: %ld\n",
               head->element->ID, head->element->name, head->element->author,
               head->element->pub, head->element->year, head->element->amount);
        head = head->next;
	}
}


void node_pushhead(booknode **head, book bk) // them vao dau ds
{
	booknode *newnode = makenode(bk);
	newnode->next= *head;
	*head = newnode;
}
void node_pushend(booknode **head,book bk)
{
	booknode *newnode = makenode(bk);
	if (*head==NULL){
		*head = newnode;
		return;
	}
	booknode *temp =*head;
	while (temp->next != NULL) temp = temp->next;
	temp->next = newnode;
}

void r_lib(booknode **head){
	FILE *fi=fopen("thuvien.txt","r"); // mo file thu vien
	char line[1024];

	// kiem tra mo file
	if (fi==NULL){
		printf("Khổng thể mở file\n");
		return;
	}

	while (fgets(line,sizeof(line),fi)){
		book bk;
        char *token;
        line[strcspn(line, "\n")] = 0; // Xóa ký tự xuống dòng nếu có
        
        token = strtok(line, "|");
        if (token) strcpy(bk.ID, token);

        token = strtok(NULL, "|");
        if (token) strcpy(bk.name, token);

        token = strtok(NULL, "|");
        if (token) strcpy(bk.author, token);

        token = strtok(NULL, "|");
        if (token) strcpy(bk.pub, token);

        token = strtok(NULL, "|");
        if (token) bk.year = atol(token);

        token = strtok(NULL, "|");
        if (token) bk.amount = atol(token);
		node_pushend(head,bk);

	}
	fclose(fi);
}

void free_list(booknode *head) {
    while (head) {
        booknode *temp = head;
        head = head->next;
        free(temp->element); // Giải phóng dữ liệu sách
        free(temp); // Giải phóng node
    }
}

int main (){
	booknode *head = NULL;
	r_lib(&head);
	print_book(head);
	free(head);	
	return 0;
}