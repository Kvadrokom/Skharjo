#ifndef HEAD_H
# define HEAD_H

typedef struct            	s_list
{
  struct  s_list      		*next;
  void                  	*data;
}                         	t_list;

t_list  *ft_create_element(void *data);

void  ft_push_back(t_list **begin_list, void *data);

void	print_list(t_list  *head);

void	ft_pop(t_list **begin_list);



#endif