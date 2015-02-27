/*
** Action.c for philosophes in /home/denel-_l/rendu/philosophes
**
** Made by denel-_l
** Login   <denel-_l@epitech.net>
**
** Started on  Tue Feb 24 16:12:31 2015 denel-_l
** Last update Fri Feb 27 14:38:18 2015 denel-_l
*/

#include "Action.h"

static int		reserve = 20;

int		doSleep(t_philo *arg)
{
  if (arg->act != SLEEP && arg->act != THINK) {
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
  /* printf("The philosopher n°%d is waiting for chopsticks, he gonna try to find one\n", arg->id); */
  return (0);
}

int		doThink(t_philo *arg)
{
  if ((arg->left_av == true || arg->next->left_av == true) && arg->act != THINK) {
    pthread_mutex_lock(&arg->my_mutex);
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
    pthread_mutex_unlock(&arg->my_mutex);
    return (1);
  }
  doSleep(arg);
  /* printf("The philosopher n°%d fell asleep, he can't think\n", arg->id); */
  return (0);
}

void		getPriority(t_philo *arg)
{
  if (arg->left_av != true && arg->prev->act == THINK) {
    pthread_mutex_unlock(&arg->prev->my_mutex);
    arg->prev->act = EAT;
    arg->left_av = true;
  }
  if (arg->next->left_av != true && arg->next->act == THINK) {
    pthread_mutex_unlock(&arg->prev->my_mutex);
    arg->next->act = EAT;
    arg->next->left_av = true;
  }
}

void		*doSomeThing(void *arg)
{
  while (reserve > 0) {
  t_philo	*tmp;
  tmp = (t_philo*)arg;
  /* pthread_mutex_lock(&tmp->my_mutex); */
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
  /* pthread_mutex_unlock(&tmp->my_mutex); */
  }
  return (NULL);
}

int		main(void)
{
  t_philo	*philo;
   t_philo	*tmp;
  int		i;
  i = 1;
  philo = init();
  while (i < 7) {
    pushafter(philo, i + 1);
    i++;
  }
  tmp = philo->next;
  if (pthread_create(&philo->my_thread, NULL, doSomeThing, (void*)philo) != 0)
    return (0);
  if (pthread_mutex_init(&philo->my_mutex, NULL) != 0)
    return (0);
  while (tmp != philo && reserve > 0) {
    if (pthread_create(&tmp->my_thread, NULL, doSomeThing, (void*)tmp) != 0)
      return (0);
    if (pthread_mutex_init(&tmp->my_mutex, NULL) != 0)
      return (0);
    tmp = tmp->next;
  }
  tmp = philo->next;
  pthread_join(philo->my_thread, NULL);
  while (tmp != philo) {
    pthread_join(tmp->my_thread, NULL);
    tmp = tmp->next;
  }
  return (0);
}
