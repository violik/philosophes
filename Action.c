/*
** Action.c for philosophes in /home/denel-_l/rendu/philosophes
**
** Made by denel-_l
** Login   <denel-_l@epitech.net>
**
** Started on  Tue Feb 24 16:12:31 2015 denel-_l
** Last update Fri Feb 27 15:08:38 2015 denel-_l
*/

#include "Action.h"

int		doSleep(t_philo *arg)
{
  if (arg->act != SLEEP && arg->act != THINK)
    {
      arg->act = SLEEP;
      printf("The philosopher n°%d is sleeping\n", arg->id);
      sleep(T_SLEEP);
      arg->priority = true;
      printf("The philosophe n°%d wakes up with priority\n", arg->id);
      return (1);
    }
  return (0);
}


int		doEat(t_philo *arg)
{
  if (arg->left_av == true && arg->next->left_av == true)
    {
      pthread_mutex_lock(&arg->my_mutex);
      arg->act = EAT;
      reserve -= 1;
      arg->left_av = false;
      arg->next->left_av = false;
      printf("The philosopher n°%d, is eating\n", arg->id);
      sleep(T_SLEEP);
      printf("The philosopher n°%d, has finished eating\n", arg->id);
      printf("It remains %d bowls\n", reserve);
      arg->left_av = true;
      arg->next->left_av = true;
      arg->priority = false;
      pthread_mutex_unlock(&arg->my_mutex);
      return (1);
    }
  doThink(arg);
  sleep (2);
  return (0);
}

int		doThink(t_philo *arg)
{
  if ((arg->left_av == true || arg->next->left_av == true) && arg->act != THINK)
    {
      pthread_mutex_lock(&arg->my_mutex);
      arg->act = THINK;
      if (arg->left_av == true)
	{
	  arg->left_av = false;
	  arg->hand_use = LEFT;
	}
      else
	{
	  arg->next->left_av = false;
	  arg->hand_use = RIGHT;
	}
      printf("The philosopher n°%d is thinking\n", arg->id);
      sleep(T_THINK);
      printf("The philosophe n°%d is hungry\n", arg->id);
      arg->priority = false;
      if (arg->hand_use == RIGHT)
	{
	  arg->next->left_av = true;
	  arg->hand_use = WAIT;
	}
      else
	{
	  arg->left_av = true;
	  arg->hand_use = WAIT;
	}
      pthread_mutex_unlock(&arg->my_mutex);
      return (1);
    }
  doSleep(arg);
  return (0);
}

void		getPriority(t_philo *arg)
{
  if (arg->left_av != true && arg->prev->act == THINK)
    {
      pthread_mutex_unlock(&arg->prev->my_mutex);
      arg->prev->act = EAT;
      arg->left_av = true;
    }
  if (arg->next->left_av != true && arg->next->act == THINK)
    {
      pthread_mutex_unlock(&arg->prev->my_mutex);
      arg->next->act = EAT;
      arg->next->left_av = true;
    }
}

void		*doSomeThing(void *arg)
{
  t_philo	*tmp;

  while (reserve > 0)
    {
      tmp = (t_philo*)arg;
      if (tmp->priority == true)
	getPriority(tmp);
      switch (tmp->act)
	{
	case NOTHING: doEat(tmp);
	  break;
	case EAT: doSleep(tmp);
	  break;
	case SLEEP: doEat(tmp);
	  break;
	case THINK: doEat(tmp);
	  break;
	}
    }
  return (tmp);
}
