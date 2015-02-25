/*
** Action.h for philosophes in /home/denel-_l/rendu/philosophes
**
** Made by denel-_l
** Login   <denel-_l@epitech.net>
**
** Started on  Tue Feb 24 16:12:37 2015 denel-_l
** Last update Wed Feb 25 10:10:54 2015 denel-_l
*/

#ifndef ACTION_H_
# define ACTION_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include<pthread.h>

# define T_EAT 1
# define T_SLEEP 3
# define T_THINK 2

typedef enum		e_Action
  {
    NOTHING,
    EAT,
    SLEEP,
    THINK
  }			Action;

typedef enum		e_Hand
  {
    WAIT,
    RIGHT,
    LEFT
  }			Hand;

typedef			int bool;
enum
  {
    true,
    false
  };


typedef struct		s_philo
{
  int			id;
  Action		act;
  bool			priority;
  bool			left_av;
  pthread_t		my_thread;
  Hand			hand_use;
  struct s_philo	*next;
  struct s_philo	*prev;
}			t_philo;


t_philo		*init(void);
void		pushafter(t_philo *element);
void		emptyliste(t_philo *list);
void		delliste(t_philo **list);
int		doSleep(t_philo *arg);
int		doThink(t_philo *arg);
int		doEat(t_philo *arg);
void		*doSomeThing(void *arg);
void		getPriority(t_philo *arg);





#endif /* !ACTION_H_ */
