#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "stack_header.h"

t_list  *ft_create_element(void *data)
{

  t_list *tmp;
  tmp = (t_list*)malloc(sizeof(t_list));
  if(tmp)
  {
    tmp->next = 0;
    tmp->data = data;
  }
  return tmp;
}

void  ft_push_back(t_list **begin_list, void *data)
{
  t_list *list;

  list = ft_create_element(data);
  if(*begin_list == 0)
      *begin_list = list;
  else
  {
      list->next = *begin_list;
      *begin_list = list;
  }
}

void	print_list(t_list  *head)
{
  t_list  *tmp;

  tmp = head;
  while (tmp)
  {
   printf("%s\n", (char*)tmp->data);
    tmp = tmp->next;
  }
  printf("\n");
}

void    ft_pop(t_list **begin_list)
{    
    t_list *tmp;
    
    if(*begin_list)
    {
        tmp = *begin_list;
        tmp = tmp->next;
        free(*begin_list);
        *begin_list = tmp;
    }
}