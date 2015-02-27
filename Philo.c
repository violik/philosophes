/*
** Philo.c for philosophes in /home/denel-_l/rendu/philosophes
**
** Made by denel-_l
** Login   <denel-_l@epitech.net>
**
** Started on  Tue Feb 24 22:50:45 2015 denel-_l
** Last update Fri Feb 27 15:09:56 2015 denel-_l
*/

#include "Action.h"
#include <stdlib.h>

int		main(void)
{
  t_philo	*philo;
  t_philo	*tmp;
  int		i;

  i = 1;
  philo = init();
  while (i < 7)
    {
      pushafter(philo, i + 1);
      i++;
    }
  tmp = philo->next;
  if (pthread_create(&philo->my_thread, NULL, doSomeThing, (void*)philo) != 0)
    return (0);
  if (pthread_mutex_init(&philo->my_mutex, NULL) != 0)
    return (0);
  while (tmp != philo && reserve > 0)
    {
      if (pthread_create(&tmp->my_thread, NULL, doSomeThing, (void*)tmp) != 0)
	return (0);
      if (pthread_mutex_init(&tmp->my_mutex, NULL) != 0)
	return (0);
      tmp = tmp->next;
    }
  tmp = philo->next;
  pthread_join(philo->my_thread, NULL);
  while (tmp != philo)
    {
      pthread_join(tmp->my_thread, NULL);
      tmp = tmp->next;
    }
  return (0);
}

t_philo		*init(void)
{
  t_philo	*philo;

  philo = (t_philo*)malloc(sizeof(*philo));
  if (philo != NULL)
    {
      philo->id = 1;
      philo->act = NOTHING;
      philo->priority = false;
      philo->hand_use = false;
      philo->prev = philo;
      philo->next = philo;
      printf("philo n°%d join the table\n", philo->id);
    }
  else
    {
      printf("Malloc Fail !\n");
      return (NULL);
    }
  return (philo);
}

void		pushafter(t_philo *element, int i)
{
  t_philo	*new_element;

  new_element = (t_philo*)malloc(sizeof(*new_element));
  if ( new_element != NULL )
    {
      new_element->id = i;
      new_element->act = NOTHING;
      new_element->priority = false;
      new_element->hand_use = false;
      new_element->prev = element->prev;
      new_element->next = element;
      element->prev->next = new_element;
      element->prev = new_element;
      printf("philo n°%d join the table\n", new_element->id);
    }
  else
    {
      printf("Malloc Fail !\n");
      exit(1);
    }
}

void		emptyliste(t_philo *list)
{
  t_philo	*it;
  t_philo	*nextt;

   nextt = list->next;
   while (nextt != list)
    {
      it = nextt;
      nextt = it->next;
      free(it);
    }
}

void		delliste(t_philo **list)
{
  emptyliste(*list);
  free(*list);
  *list = NULL;
}
