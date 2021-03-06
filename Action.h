/*
** Action.h for philosophes in /home/denel-_l/rendu/philosophes
**
** Made by denel-_l
** Login   <denel-_l@epitech.net>
**
** Started on  Tue Feb 24 16:12:37 2015 denel-_l
** Last update Sun Mar  1 21:11:10 2015 Glubzite
*/

#ifndef ACTION_H_
# define ACTION_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

# define T_EAT 1
# define T_SLEEP 3
# define T_THINK 2

static int		g_reserve = 20;

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
  pthread_mutex_t	my_mutex;
  Hand			hand_use;
  struct s_philo	*next;
  struct s_philo	*prev;
}			t_philo;

t_philo		*init(void);
void		pushafter(t_philo *element, int i);
void		emptyliste(t_philo *list);
void		delliste(t_philo **list);
void		doSleep(t_philo *arg);
void		doThink(t_philo *arg);
void		doEat(t_philo *arg);
void		*doSomeThing(void *arg);
void		getPriority(t_philo *arg);

#endif /* !ACTION_H_ */
