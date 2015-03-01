/*
** Action.c for philosophes in /home/denel-_l/rendu/philosophes
**
** Made by denel-_l
** Login   <denel-_l@epitech.net>
**
** Started on  Tue Feb 24 16:12:31 2015 denel-_l
** Last update Sun Mar  1 21:07:34 2015 Glubzite
*/

#include "Action.h"

void		doSleep(t_philo *arg)
{
  if (arg->act != SLEEP && arg->act != THINK)
    {
      arg->act = SLEEP;
      printf("The philosopher n°%d is sleeping\n", arg->id);
      sleep(T_SLEEP);
      arg->priority = true;
      printf("The philosophe n°%d wakes up with priority\n", arg->id);
    }
}

void		doEat(t_philo *arg)
{
  arg->priority = false;
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
      return;
    }
  doThink(arg);
  sleep (2);
}

void		doThink(t_philo *arg)
{
  if ((arg->left_av == true || arg->next->left_av == true) && arg->act != THINK)
    {
      pthread_mutex_lock(&arg->my_mutex);
      arg->act = THINK;
      printf("The philosopher n°%d is thinking\n", arg->id);
      if (arg->left_av == true)
	{
	  arg->left_av = false;
	  arg->hand_use = LEFT;
	  sleep(T_THINK);
	  arg->next->left_av = true;
	}
      else
	{
	  arg->next->left_av = false;
	  arg->hand_use = RIGHT;
	  sleep(T_THINK);
	  arg->left_av = true;
	}
      arg->hand_use = WAIT;
      printf("The philosophe n°%d is hungry\n", arg->id);
      pthread_mutex_unlock(&arg->my_mutex);
    }
  else
    doSleep(arg);
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
	getPriority(arg);
      if (tmp->act == NOTHING)
	doEat(arg);
      else if (tmp->act == EAT)
	doSleep(arg);
      else if (tmp->act == SLEEP)
	doEat(arg);
      else if (tmp->act == THINK)
	doEat(arg);
    }
  return (arg);
}
