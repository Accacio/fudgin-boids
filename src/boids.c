#include <math.h>
#include <stdlib.h>
#include <curses.h>
#include <sys/time.h>
#include <locale.h>

#define PI 3.14
#define deg(x) x/180.*PI

double WIDTH = 40;
double HEIGHT = 40;


typedef struct Boid{
  double x, y, theta;
  double dx, dtheta;
  struct Boid * neighbors;
  int nNeighbors;
} Boid;

double tim(struct timeval * t){
  struct timeval n;
  gettimeofday(&n,0);
  int r=(n.tv_sec-t->tv_sec)*1.e6+n.tv_usec-t->tv_usec;
  *t = n;
  return r / 1.e6;
}

void
get_neighbors(Boid * boid,Boid * allboids,int nBoids)
{
  int boidNeigh=0;

}


void
update_bird(Boid * boid,double dt)
{
  boid->x += boid->dx*cos(boid->theta)*dt;
  boid->y -= boid->dx*sin(boid->theta)*dt;

  if(boid->x<0){
    boid->x=WIDTH-(-boid->x);
  } else if (boid->x>WIDTH){
    boid->x-=WIDTH;
  }
  if(boid->y<0){
    boid->y=HEIGHT-(-boid->y);
  } else if (boid->y>HEIGHT){
    boid->y-=HEIGHT;
  }

}

void
draw_bird(Boid boid)
{
  switch (((((int) ( boid.theta/PI*180.0)  % 360) + 360) % 360) / 30) {
    case 0:
    case 11:
      mvprintw(boid.y,boid.x,"➡");
      break;
    case 1:
      mvprintw(boid.y,boid.x,"⬈");
      break;
    case 2:
    case 3:
      mvprintw(boid.y,boid.x,"⬆");
      break;
    case 4:
      mvprintw(boid.y,boid.x,"⬉");
      break;
    case 5:
    case 6:
      mvprintw(boid.y,boid.x,"⬅");
      break;
    case 7:
      mvprintw(boid.y,boid.x,"⬋");
      break;
    case 8:
    case 9:
      mvprintw(boid.y,boid.x,"⬇");
      break;
    case 10:
      mvprintw(boid.y,boid.x,"⬊");
      break;
  }
}


int main(int argc, char *argv[]) {
  char * locale = setlocale(LC_ALL, 0);
  setlocale(LC_ALL, "");

  struct timeval t;
  gettimeofday(&t, 0);

  initscr();
  curs_set(0);

  char ch;

  if (nodelay(stdscr,TRUE)==ERR){
    return -1;
  }

  int nBoids=10;
  Boid myBoids[nBoids];
  srand(t.tv_sec);

  for (int i = 0; i < nBoids; i++) {
    myBoids[i].x=(WIDTH-1)*rand()/RAND_MAX+1;
    myBoids[i].y=(HEIGHT-1)*rand()/RAND_MAX+1;
    myBoids[i].dx=10;
    myBoids[i].dtheta=0;
    myBoids[i].theta=0;
  }

  WINDOW * mybox=subwin(stdscr, WIDTH, HEIGHT, 0,0 );

  for (; ;) {
    ch = getch();
    if (ch!=ERR){
      if(ch==113){
        break;
      }
    }

    float dt =tim(&t);

    /* boid.theta += deg(40)*dt; // control */
    for (int i = 0; i < nBoids; i++) {
      get_neighbors(&myBoids[i],myBoids,nBoids);
    }


    erase();
    for (int i = 0; i < nBoids; i++) {
      update_bird(&myBoids[i],dt);
      draw_bird(myBoids[i]);
      /* myBoids[i].y=fmax(HEIGHT,fmin(random(),0)); */
    }

    box(mybox, ACS_VLINE, ACS_HLINE);

    refresh();
    usleep(20000);
  }


  endwin();
  return 0;
}
