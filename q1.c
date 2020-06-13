// 
// Delete k-th element in the one-way list
// 
// C-only
//


#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 7

struct Node
{
   struct Node *next;
   int n;
   // ...
};


//
// k = 0, 1, 2 ...
//
int deleteK(struct Node **pptr, unsigned int k)
{
   if ((*pptr) == NULL)
   {
      return -1;
   }
   if (k == 0)
   {
      struct Node *tmp = (*pptr);
      (*pptr) = (*pptr)->next;
      free(tmp);
      return 0;
   }

   struct Node *p = (*pptr), *prev;
   for(unsigned int i = 0; (i < k) && (p != NULL); i++, prev = p, p = p->next)
   {
      if (p->next == NULL)
      {
	 return -1; // size is less than k
      }

   }

   if (p != NULL)
   {
      prev->next = p->next;
      free(p);
   }
   else
   {
      return -2; // unexpected
   }

   return 0;
}

void freeList(struct Node *ptr)
{
   struct Node *tmp;
   while (ptr)
   {
      tmp = ptr;
      ptr = ptr->next;
      free(tmp);
   }
}

void printList(struct Node *ptr)
{
   for(struct Node *tmp = ptr; tmp != NULL; tmp = tmp->next)
   {
      printf("%d ", tmp->n);
   }
   printf("\n");
}


int main(int argc, char ** argv)
{
   if (argc < 2)
   {
      printf("Usage: q1 <number>\n");
      return 0;
   }
  
   int k = atoi(argv[1]);
   if (k < 0)
   {
      printf("Argument should be positive.\n");
      return 0;
   }

   struct Node * const ptr = malloc(sizeof(struct Node));

   if (ptr)
   {
      struct Node *p = ptr;
      for (int i = 0; i < MAXLEN; i++ && p != NULL, p = p->next)
      {
	 p->n = i;
	 if (i < MAXLEN - 1)
	 {
            p->next = malloc(sizeof(struct Node));
	    if(p->next == NULL)
	    {
	       freeList(ptr);
	       return -1;
	    }
	 }
	 else
	 {
	    p->next = NULL;
	 }
      }

      struct Node *pp = ptr;
      printList(pp);
      if (deleteK(&pp, k))
      {
         printf("Nothing was deleted.\n");
      }
      printList(pp);
      freeList(pp);
   }

   return 0;
}
