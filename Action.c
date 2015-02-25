/*
** Action.c for philosophes in /home/denel-_l/rendu/philosophes
**
** Made by denel-_l
** Login   <denel-_l@epitech.net>
**
** Started on  Tue Feb 24 16:12:31 2015 denel-_l
** Last update Wed Feb 25 10:16:06 2015 denel-_l
*/

#include "Action.h"

static int		reserve = 20;

int		doSleep(t_philo *arg)
{
  if (arg->act != SLEEP) {
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
  if (arg->left_av == true && arg->next->left_av == true) {
    arg->act = EAT;
    arg->left_av = false;
    arg->next->left_av = false;
    printf("The philosopher n°%d, is eating\n", arg->id);
    sleep(T_SLEEP);
    printf("The philosopher n°%d, has finished heating\n", arg->id);
    reserve -= 1;
    printf("It remains %d bowls\n", reserve);
    arg->left_av = true;
    arg->next->left_av = true;
    arg->priority = false;
    return (1);
  }
  doThink(arg);
  printf("The philosopher n°%d is waiting for chopsticks, he gonna try to find one\n", arg->id);
  return (0);
}

int		doThink(t_philo *arg)
{
  if (arg->left_av == true || arg->next->left_av == true) {
    arg->act = THINK;
    if (arg->left_av == true) {
      arg->left_av = false;
      arg->hand_use = LEFT; }
    else {
      arg->next->left_av = false;
      arg->hand_use = RIGHT; }
    printf("The philosopher n°%d is thinking\n", arg->id);
    sleep(T_THINK);
    printf("The philosophe n°%d is hungry\n", arg->id);
    arg->priority = false;
    if (arg->hand_use == RIGHT) {
      arg->next->left_av = true;
      arg->hand_use = WAIT; }
    else {
      arg->left_av = true;
      arg->hand_use = WAIT; }
    return (1);
  }
  doSleep(arg);
  printf("The philosopher n°%d fell asleep, he can't think\n", arg->id);
  return (0);
}

void		getPriority(t_philo *arg)
{
  if (arg->left_av != true && arg->prev->act == THINK) {
    arg->prev->act = EAT;
    arg->left_av = true;
  }
  if (arg->next->left_av != true && arg->next->act == THINK) {
    arg->next->act = EAT;
    arg->next->left_av = true;
  }
}

void		*doSomeThing(void *arg)
{
  t_philo	*tmp;
  tmp = (t_philo*)&arg;
  if (tmp->priority == true) {
    getPriority(tmp);
  }
  switch (tmp->act) {
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

int		main(void)
{
  t_philo	*philo;
  t_philo	*tmp;
  int		i;
  i = 0;
  philo = init();
  while (i < 6)
    {
      pushafter(philo);
      i++;
    }
  tmp = philo->next;
  printf("philo n°%d join the table\n", philo->id);
  while (tmp != philo)
    {
      printf("philo n°%d join the table\n", tmp->id);
      tmp = tmp->next;
    }
  return 0;
}
