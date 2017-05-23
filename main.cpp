#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

#define maxtablewidth 35
int tablewidth = 1;

struct type_of_node
{
       char number; //y
       char position; //x
       struct type_of_node *next;
       struct type_of_node *previous;
};

void Updatetable(char y, char x, char table[maxtablewidth][maxtablewidth])
{
       int i, j;
       table[x - 1][y - 1] = y;
       for(i = 0; i < tablewidth; i++)
       {
             if(table[i][y - 1] == 0)
                    table[i][y - 1] = y;
       }
       for(i = 0; i < tablewidth; i++)
       {
             if(table[x - 1][i] == 0)
                    table[x - 1][i] = y;
       }
       for(i = y - 1, j = x - 1; i < tablewidth and j < tablewidth; i++, j++)
       {
             if(table[j][i] == 0)
                    table[j][i] = y;
       }
       for(i = y - 1, j = x - 1; i >= 0 and j >= 0; i--, j--)
       {
             if(table[j][i] == 0)
                    table[j][i] = y;
       }
       for(i = y - 1, j = x - 1; i >= 0 and j < tablewidth; i--, j++)
       {
             if(table[j][i] == 0)
                    table[j][i] = y;
       }
       for(i = y - 1, j = x - 1; i < tablewidth and j >= 0; i++, j--)
       {
             if(table[j][i] == 0)
                    table[j][i] = y;
       }
}

void Cleantable(char table[maxtablewidth][maxtablewidth])
{
     int i, j;
     for(i = 0; i < tablewidth; i++)
           for(j = 0; j < tablewidth; j++)
                 table[i][j] = 0;
}

void Updatetabledel(char junk, char table[maxtablewidth][maxtablewidth])
{
     int i, j;
     for(i = 0; i < tablewidth; i++)
           for(j = 0; j < tablewidth; j++)
                 if(table[i][j] == junk) table[i][j] = 0;
}

type_of_node * Createnode(type_of_node *temp)
{
     temp->next = new(type_of_node);
     temp->next->previous = temp;
     temp->next->next = NULL;
     return temp->next;
}

char Findposition(char y, char x, char table[maxtablewidth][maxtablewidth])
{
     int i;
     for(i = x; i < tablewidth; i++)
           if(table[i][y - 1] == 0) return i + 1;
     return -1;
}

void test(char table[maxtablewidth][maxtablewidth])
{
     int i, j;
     for(i = 0; i < tablewidth; i++)
     {
           printf("\t\n");
           for(j = 0; j < tablewidth; j++)
                 printf("%d", table[j][i]);
     }
     printf("\n");
}

void Printnodes(type_of_node *temp)
{
     printf("--------------------------------\n");
     printf("\tCoordinates\n\tX\tY");
     while(temp->next != NULL)
     {
                  printf("\n%d:\t%d\t%d",temp->number, temp->position, temp->number);
                  temp = temp->next;    
     }
     printf("\n%d:\t%d\t%d",temp->number, temp->position, temp->number);
     printf("\n");
}

void Solve_problem()
{
    int i;
    char table[maxtablewidth][maxtablewidth];
    bool showstatus = false;
    time_t t1,t2;
    int answer = 0;
    printf("Adjust table dimensions with a single number\n(more than 2x2 less than 35x35)\n");
    while(answer < 2 or answer > 35)
          scanf("%d", &answer);
    tablewidth = answer;      
    answer = 0;
    printf("Show progress? (Y=Yes,N=No)\n");
    while(answer != 'Y' and answer != 'y' and answer != 'N' and answer != 'n')
          scanf("%c", &answer);
    if(answer == 'Y' or answer == 'y')
            showstatus = true;  
    struct type_of_node *lista, *temp;
    lista = new(type_of_node);
    lista->number = 1;
    lista->position = 1;
    lista->previous = NULL;
    lista->next = NULL;
    Cleantable(table);
    Updatetable(lista->number, lista->position, table);
    temp = new(type_of_node);
    temp = lista;
    bool flag = 1;
    char position;
    unsigned long int counter = 0;
    for(i = 0; i < tablewidth - 1; i++)
    {
          temp = Createnode(temp);
          temp->number = temp->previous->number + 1;
          temp->position = 0;
    }
    temp = lista->next;
    (void) time(&t1);
    while(flag)
    {
            if(showstatus)
            {
                          counter++;
                          printf("\nStep:%d", counter);
                          test(table);
            }
            else
                counter++;
            position = Findposition(temp->number, temp->position, table);
            if(position != -1)
            {
                       temp->position = position;
                       Updatetable(temp->number, temp->position, table);
                       if(temp->number == tablewidth)
                       {
                                       flag = false;
                                       break; 
                       }
                       temp = temp->next;
            }
            else
            {
                       if(temp->number == 1)
                       {
                                       flag = false;
                                       break;
                       }
                       temp->position = 0;
                       temp = temp->previous;
                       Updatetabledel(temp->number, table);
            }
    }
    printf("\n--------------------------------");
    printf("\nNumber of steps:%d", counter);
    (void) time(&t2);
    printf("\nTime taken = %d seconds", (int) t2-t1);
    printf("\n--------------------------------");
    printf("\nTesting table...");
    test(table);
    if(temp->number == 1)
    {
               printf("\n--------------------------------");
               printf("\nUnable to solve the problem...\n");
    }
    else
        Printnodes(lista);
}

int main(int argc, char *argv[])
{
    int answer = 0;
    Solve_problem();
    printf("\nDo you want to try another variation? (Y=Yes,N=No)\n");
    while(answer != 'N' and answer != 'n')
    {
          scanf("%c", &answer);
          if(answer == 'Y' or answer == 'y')
          {
                    Solve_problem();
                    printf("\nDo you want to try another variation? (Y=Yes,N=No)\n");
                    answer = 0;
          }
    }
    system("PAUSE");
    return 0;
}
