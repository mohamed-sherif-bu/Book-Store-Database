#include <stdio.h>
#include <stdlib.h>
#include  <string.h>

typedef struct list
{
    char bookname[100];
    int id;
    char author[100];
    float price;
} List;
struct listNode
{
    List l;
    struct listNode *nextPtr;
};
typedef struct listNode ListNode;
typedef ListNode *ListNodePtr;

void start();
void save();
void printMessageCenter(const char *message);
void headMessage(const char *message);
void welcomeMessage();
void exitMessage();
void insert(ListNodePtr *sPtr, char *bookname,int id,char *author,float price);
char deletebook(ListNodePtr *sPtr, int id);
int isEmpty(ListNodePtr sPtr);
void displayAll(ListNodePtr currentPtr);
void search();
void FreeData();
void Reset();
int isNameValid(const char *name);
void update ();
int isNumVaild(int *n);
ListNodePtr startPtr = NULL; // initially there are no nodes

int main(void)
{
    int status=0,idd,vaildnum=0;
    ListNode *ptr;
    char bookname_value[100];
    int id_value;
    char author_value[100];
    float price_value;
    int num,i;
    welcomeMessage();
    start();
    unsigned int choice;
    do
    {
        headMessage("MAIN MENU");
        printf("\n\n\n\t\t\t1.Add Books.");
        printf("\n\t\t\t2.Delete Books.");
        printf("\n\t\t\t3.View Books.");
        printf("\n\t\t\t4.Search Book");
        printf("\n\t\t\t5.Clear the books data.");
        printf("\n\t\t\t6.Update book.");
        printf("\n\t\t\t7.Exit.");
        do{
        printf("\n\n\n\t\t\tEnter choice => ");
        fflush(stdin);
        scanf("%u", &choice);
        vaildnum=isNumVaild(&choice);
         if(!vaildnum)
                {
                    printf("\n\t\t\tInvaild Chioce\n");
                }
            }
            while(!vaildnum);
        switch (choice)
        {
        case 1: //insert new book
            system("cls");
            headMessage ("ADD NEW BOOKS");
            printf ("\n\n\t\t\tENTER YOUR DETAILS BELOW:");
            printf ("\n\t\t\t---------------------------------------------------------------------------\n");

            do
            {
                printf("\n\t\t\tHow many of books you want to insert: ");
                fflush(stdin);
                scanf("%d",&num);
                vaildnum=isNumVaild(&num);
                if(!vaildnum)
                {
                    printf("\n\t\t\tInvaild Number.Please enter again.");
                }
            }
            while(!vaildnum);
            system("cls");
            for(i=0; i<num; ++i)
            {
                headMessage ("ADD NEW BOOKS");
                printf ("\n\n\t\t\tENTER YOUR DETAILS BELOW:");
                printf ("\n\t\t\t---------------------------------------------------------------------------\n");
                do
                {
                    printf("\n\t\t\tBook Name: ");
                    fflush(stdin);
                    gets(bookname_value);
                    status=isNameValid(&bookname_value);
                    if(!status)
                    {
                        printf("\n\t\t\tName contains invalid character. Please enter again.");

                    }
                }
                while(!status);
                do
                {
                    printf("\n\t\t\tBook ID NO: ");
                    fflush(stdin);
                    scanf("%d",&id_value);
                    vaildnum=isNumVaild(&id_value);
                    if(!vaildnum)
                    {
                        printf("\n\t\t\tId contains invalid numbers. Please enter again.");

                    }
                }
                while(!vaildnum);
                do
                {
                    printf("\n\t\t\tAuthor Name: ");
                    fflush(stdin);
                    gets(author_value);
                    status=isNameValid(&author_value);
                    if(!status)
                    {
                        printf("\n\t\t\tName contains invalid character. Please enter again.");
                    }
                }
                while(!status);
                do
                {
                    printf("\n\t\t\tPrice: ");
                    fflush(stdin);
                    scanf("%f",&price_value);
                    vaildnum=isNumVaild(&price_value);
                    if(!vaildnum)
                    {
                        printf("\n\t\t\tPrice contains invalid numbers. Please enter again.");

                    }
                }
                while(!vaildnum);
                insert(&startPtr, bookname_value,id_value,author_value,price_value); // insert item in list
                printf("\n\n\t\t\t BOOK INSERTED\n\n");
                system("pause");
                system("cls");
            }
            break;
        case 2: // delete an element
// if list is not empty
            system("cls");
            headMessage("DELETE BOOKS");
            if (!isEmpty(startPtr))
            {
                printf("%s", "\n\t\t\tEnter id to be deleted: ");
                scanf("\n%d", &id_value);

// if character is found, remove it
                if (deletebook(&startPtr, id_value))   // remove item
                {
                    system("cls");
                    headMessage("DELETE BOOKS");
                    printf("\n\t\t\tBook of id %d deleted.\n", id_value);
                    system("pause");
                    system("cls");
                }
                else
                {
                    system("cls");
                    headMessage("DELETE BOOKS");
                    printf("\n\n\t\t\tId No.%d not found.\n", id_value);
                    system("pause");
                    system("cls");
                }
            }
            else
            {
                system("cls");
                headMessage("DELETE BOOKS");
                puts("\n\t\t\tList is empty.\n");
                system("pause");
                system("cls");
            }

            break;

        case 3: //view all books
            displayAll(startPtr);
            break;
        case 4: // search for a certain book
            search();
            break;
        case 5: //clear all data
            Reset();
            break;
        case 6: //update certain book information
            update();
            break;
        case 7: // exit program and save changes
            save();
            system("cls");
            exitMessage();
            exit(1);
            break;
        default:
            puts("\n\t\t\tInvalid choice.\n");
            system("pause");
            break;
        }
    }
    while(1);
}


void start()
{

    FILE *fptr;
    if ((fptr=fopen("store.txt","r+") ) == NULL)puts("File could not be opened");
    else
    {
        ListNodePtr current=startPtr;

        while(!feof(fptr))
        {

            ListNodePtr newNode =malloc(sizeof(ListNode));

            newNode->nextPtr=NULL;
            fscanf(fptr,"%d  %19[^\n]%*1[\n]",&newNode->l.id,newNode->l.author);
            fscanf(fptr,"%f  %19[^\n]%*1[\n]",&newNode->l.price,newNode->l.bookname);
            if ( feof(fptr) )break;

            if(startPtr==NULL)
            {
                startPtr=newNode;
                current=startPtr;
            }
            else
            {
                current->nextPtr=newNode;
                current=current->nextPtr;
            }
        }

        fclose(fptr);
    }
}
void save()
{
    FILE *fptr;
    if ((fptr=fopen("store.txt","w") ) == NULL)puts("File could not be opened");
    else
    {
        ListNodePtr current=startPtr;

        current=startPtr;
        while(current!=NULL)
        {
            fprintf(fptr,"%d  %s \n",current->l.id,current->l.author);
            fprintf(fptr,"%f  %s \n",current->l.price,current->l.bookname);
            current=current->nextPtr;
        }

    }
    fclose(fptr);
    return 0;
}

void printMessageCenter(const char *message)
{
    int len = 0;
    int pos = 0;
    //calculate how many space need to print
    len = (78 - strlen(message)) / 2;
    printf("\t\t\t");
    for (pos = 0; pos < len; pos++)             //print space
    {
        printf(" ");
    }
    printf("%s", message);                      //print message
}

void headMessage(const char *message)
{
    system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############            Books-Databases in C                   ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t----------------------------------------------------------------------------");
}

void welcomeMessage()
{
    headMessage("faculty of engineering  shoubra banha");
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                 WELCOME                   =");
    printf("\n\t\t\t        =                   TO                      =");
    printf("\n\t\t\t        =                 Books                     =");
    printf("\n\t\t\t        =               Databases                   =");
    printf("\n\t\t\t        =                 SYSTEM                    =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n                          ");
    system("pause");
}

void exitMessage()
{
    headMessage("faculty of engineering  shoubra banha");
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                 WITH                      =");
    printf("\n\t\t\t        =                  OUR                      =");
    printf("\n\t\t\t        =                  BEST                     =");
    printf("\n\t\t\t        =                 WISHES                    =");
    printf("\n\t\t\t        =                GOOD LUCK                  =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n                          ");
}

// insert a new value into the list in sorted order
void insert(ListNodePtr *sPtr, char *bookname,int id,char *author,float price)
{
    ListNodePtr newPtr = malloc(sizeof(ListNode)); // create node

    if (newPtr != NULL)   // is space available?
    {
        strcpy(newPtr->l.bookname,bookname);
        newPtr->l.id=id;
        strcpy(newPtr->l.author,author);
        newPtr->l.price=price;
        newPtr->nextPtr = NULL; // node does not link to another node

        ListNodePtr previousPtr = NULL;
        ListNodePtr currentPtr = *sPtr;
// loop to find the correct location in the list
        while (currentPtr != NULL && id > currentPtr->l.id)
        {
            previousPtr = currentPtr; // walk to ...
            currentPtr = currentPtr->nextPtr; // ... next node
        }
// insert new node at beginning of list
        if (previousPtr == NULL)
        {
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        }
        else   // insert new node between previousPtr and currentPtr
        {
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        }
    }
    else
    {
        printf("%d not inserted. No memory available.\n", id);
    }
    system("cls");
    headMessage("ADD NEW BOOKS");
}

// delete a list element
char deletebook(ListNodePtr *sPtr, int id)
{

    if (id == (*sPtr)->l.id)
    {
        ListNodePtr tempPtr = *sPtr; // hold onto node being removed
        *sPtr = (*sPtr)->nextPtr; // de-thread the node
        free(tempPtr); // free the de-threaded node
        return id;
    }
    else
    {
        ListNodePtr previousPtr = *sPtr;
        ListNodePtr currentPtr = (*sPtr)->nextPtr;

// loop to find the correct location in the list
        while (currentPtr != NULL && currentPtr->l.id != id)
        {
            previousPtr = currentPtr; // walk to ...
            currentPtr = currentPtr->nextPtr; // ... next node
        }

// delete node at currentPtr
        if (currentPtr != NULL)
        {
            ListNodePtr tempPtr = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr;
            free(tempPtr);
            return id;
        }
    }

    return '\0';
}

// return 1 if the list is empty, 0 otherwise
int isEmpty(ListNodePtr sPtr)
{
    return sPtr == NULL;
}
// print the list
void displayAll(ListNodePtr currentPtr)
{
    system("cls");
    headMessage ("DISPLAY BOOKS");
// if list is empty
    if (isEmpty(currentPtr))
    {
        puts("\n\t\t\tList is empty.\n");
        system("pause");
        system("cls");
    }
    else
    {
// while not the end of the list
        while (currentPtr != NULL)
        {
            printf("\n\t\t\tBookname:%s\n", currentPtr->l.bookname);
            printf("\t\t\tBook Id:%d\n",currentPtr->l.id);
            printf("\t\t\tBook author:%s\n",currentPtr->l.author);
            printf("\t\t\tBook price:%.2f\n\n",currentPtr->l.price);
            currentPtr = currentPtr->nextPtr;
        }
        system("pause");
        system("cls");
    }
}


void search ()
{
    int id;
    int vaildnum=0;
    ListNodePtr current = startPtr;
    headMessage("SEARCH");
    if(startPtr == NULL)
    {
        printf("\n\t\t\tList is Empty\n");
        system("pause");
        system("cls");
    }
    else
    {

       do
                {
                    printf("\n\t\t\tBook ID NO: ");
                    fflush(stdin);
                    scanf("%d",&id);
                    vaildnum=isNumVaild(&id);
                    if(!vaildnum)
                    {
                        printf("\n\t\t\tId contains invalid numbers. Please enter again.");

                    }
                }
                while(!vaildnum);
        system("cls");
        headMessage("SEARCH");
        while (current != NULL)
        {
            if (current->l.id == id)
            {
                printf ("\n\t\t\tbook_Name: %s\n", current->l.bookname);
                printf ("\t\t\tID Number: %d\n", current->l.id);
                printf ("\t\t\tauthor_name: %s\n", current->l.author);
                printf ("\t\t\tprice: %.2f\n", current->l.price);
                system("pause");
                system("cls");
                return;
            }
            current = current->nextPtr;
        }
        if(current==NULL)
        {
            printf("\n\t\t\tId Not found\n");
            system("pause");
            system("cls");
        }

    }
}
void FreeData()
{
    if (startPtr == NULL)
    {
        printf("\n\t\t\tlinked list is empty.\n");
    }
    else
    {
        ListNode* first_book = startPtr;
        startPtr = startPtr->nextPtr;
        free(first_book);
    }
}

void Reset()
{
    do
    {
        FreeData();
    }
    while(startPtr != NULL);
    system("cls");
    headMessage("CLEAR THE BOOKS DATA");
    printf("\n\n\t\t\tBooks data has been cleared.\n");
    system("pause");
    system("cls");
}

int isNameValid(const char *name)
{
    int validName = 1;
    int len = 0;
    int index = 0;
    len = strlen(name);
    for (index = 0; index < len; ++index)
    {
        if (!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' '))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}

void update ()
{
    ListNodePtr current = startPtr;
    int id,status=0,vaildnum=0;
    system("cls");
    headMessage("UPDATE");
    if(startPtr == NULL)
    {
        printf("\n\t\t\tList is Empty\n") ;
        system("pause");
        system("cls");
    }
    else
    {
        printf("\n\t\t\tEnter Id of the book: ");
        scanf("%d",&id);
        system("cls");
        headMessage("UPDATE");
        while (current != NULL)
        {
            if (current->l.id == id)
            {
                printf ("\n\t\t\tRecord with ID number %d Found !!!\n", id);
                system("pause");
                system("cls");
                headMessage("UPDATE");
                do
                {
                    printf("\n\t\t\tEnter new Book Name: ");
                    fflush(stdin);
                    gets(current->l.bookname);
                    status=isNameValid(&current->l.bookname);
                    if(!status)
                    {
                        printf("\n\t\t\tName contains invalid character. Please enter again.");

                    }
                }
                while(!status);
                do
                {
                    printf("\n\t\t\tEnter new author Name: ");
                    fflush(stdin);
                    gets(current->l.author);
                    status=isNameValid(&current->l.author);
                    if(!status)
                    {
                        printf("\n\t\t\tName contains invalid character. Please enter again.");

                    }
                }
                while(!status);

                do
                {
                    printf("\n\t\t\tEnter New Price: ");
                    fflush(stdin);
                    scanf("%f",&current->l.price);
                    vaildnum=isNumVaild(&current->l.price);
                    if(!vaildnum)
                    {
                        printf("\n\t\t\tPrice contains invalid numbers. Please enter again.");

                    }
                }
                while(!vaildnum);

                printf ("\n\t\t\tData has been updated successfully!!!!\n");
                system("pause");
                system("cls");
                return;
            }
            current = current->nextPtr;

        }
        if(current==NULL)
        {
            headMessage("UPDATE");
            printf("\n\t\t\tId Not found\n");
            system("pause");
            system("cls");
        }
    }
}

int isNumVaild(int *n)
{
    int vaildnum=1;

    if (!(isdigit(&n))&& !isspace(&n)&& getchar()!= '\n')
    {
        vaildnum=0;
    }
    return vaildnum;
}
