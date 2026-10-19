/* $Id: event.c,v 1.2 2003/02/01 23:53:40 mjt Exp $
 * simple event library. 
 * Written by Michael Tokarev <mjt@corpit.ru>
 * LGPL
 */

#define EVENT_USES_SELECT 1 /* poll() case isn't ready yet: POLLHUP/POLLERR */
/*#define EVENT_THREADSAFE 1*/

//  #include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//  #include <sys/time.h> /* for gettimeofday */
#if EVENT_USES_SELECT
//  #include <sys/select.h>
#else
#include <sys/poll.h>
#endif
/* note: on FreeBSD (<5.0), sys/event.h clashes with this module */
#include	"proxyChkCommon.h"
#include "event.h"

#ifndef UNUSED
# ifdef __GNUC__
#  define UNUSED __attribute__((unused))
# else
#  define UNUSED
# endif
#endif

#define su2ms(sec,usec) ((sec) * 1000 + (usec) / 1000)
#define tv2ms(tv) su2ms((tv)->tv_sec, (tv)->tv_usec)
#define ms2tv(ms,tv) \
  ((tv)->tv_sec = (ms) / 1000, (tv)->tv_usec = ((ms) % 1000) * 1000)

#ifndef timercmp
# define timercmp(a, b, CMP) \
  (((a)->tv_sec == (b)->tv_sec) ? \
   ((a)->tv_usec CMP (b)->tv_usec) : \
   ((a)->tv_sec CMP (b)->tv_sec))
#endif
#ifndef timeradd
# define timeradd(a, b, result) \
  do { \
     (result)->tv_sec = (a)->tv_sec + (b)->tv_sec; \
     if (((result)->tv_usec = (a)->tv_usec + (b)->tv_usec) >= 1000000) \
        ++(result)->tv_sec, (result)->tv_usec -= 1000000; \
  } while (0)
#endif

#if EVENT_THREADSAFE
# define ev_cbck evr_cbck_fn
#else
# define ev_cbck ev_cbck_fn
#endif

typedef struct ev_timer {
  struct timeval when;		/* time when to trigger */
  ev_cbck *cbck;
  void *ctx;
  struct ev_timer *next;	/* linked list: next timer */
} ev_timer;

typedef struct {
  ev_cbck *cbck;
  void *ctx;
} ev_io;

struct ev_ctx {
  int nfds;		/* cur. max active fd#-1 for select() # for pool() */
  int nested;		/* flag to prevent nested calls of event_wait() */
  ev_timer *timers;	/* list of timers sorted by time of trigger */
  ev_timer *stimer;	/* a pointer to one spare timer structure */
  struct timeval when;	/* current event's time */
#if EVENT_USES_SELECT
  fd_set xfds, wfds, rfds; /* ready-to-use fdsets consistent with io[] */
  ev_io io[FD_SETSIZE];	/* array of fds indexed by fd */
#else
  int afds;		/* number of fds allocated */
  ev_io *io;		/* array of active io events (size nfds) */
  struct pollfd *pfd;	/* ditto for poll() */
#endif
};

#if EVENT_THREADSAFE

# define efn0(name,c) evr_##name(c)
# define efn1(name,c,a1) evr_##name(c,a1)
# define efn2(name,c,a1,a2) evr_##name(c,a1,a2)
# define efn3(name,c,a1,a2,a3) evr_##name(c,a1,a2,a3)
# define efn4(name,c,a1,a2,a3,a4) evr_##name(c,a1,a2,a3,a4)
# define callback(fn, ec, fd, event, ctx) (*(fn))((ec), (fd), (event), (ctx))

ev_ctx *evr_alloc() {
  ev_ctx *ec = (ev_ctx*)malloc(sizeof(ev_ctx));
  if (!ec)
    return errno = ENOMEM, NULL;
  memset(ec, 0, sizeof(*ec));
  return ec;
}

ev_ctx *evr_free(ev_ctx *ec) {
  while(ec->timers) {
    ev_timer *t = ec->timers;
    ec->timers = t->next;
    free(t);
  }
  if (ec->stimer)
    free(ec->stimer);
#if !EVENT_USES_SELECT
  if (ec->io)
    free(ec->io);
  if (ec->pfd)
    free(ec->pfd);
#endif
  free(ec);
  return NULL;
}

#else /* !EVENT_THREADSAFE */

static ev_ctx ectx; /* zeroed */
# define ec (&ectx)
# define efn0(name,c) ev_##name()
# define efn1(name,c,a1) ev_##name(a1)
# define efn2(name,c,a1,a2) ev_##name(a1,a2)
# define efn3(name,c,a1,a2,a3) ev_##name(a1,a2,a3)
# define efn4(name,c,a1,a2,a3,a4) ev_##name(a1,a2,a3,a4)
# define callback(fn, ec, fd, event, ctx) (*(fn))((fd), (event), (ctx))

#endif /* EVENT_THREADSAFE */

#define settime(ec) if (!ec->when.tv_sec) gettimeofday(&ec->when, NULL)

/* free a timer structure */
#define freetimer(t) \
  if (ec->stimer) free(t); else ec->stimer = t

/* request a new timer or cancel existing one */
int efn3(settimer, ev_ctx *ec, int mstimeout, ev_cbck *cbck, void *ctx) {
  ev_timer *t, **tp, *p;
  if (!cbck)
    return errno = EINVAL, -1;
  for(tp = &ec->timers; (t = *tp) != NULL; tp = &t->next)
    if (t->cbck == cbck && t->ctx == ctx) {
      *tp = t->next;
      tp = &t->next;
      break;
    }
  if (mstimeout < 0) {
    if (!t)
      return errno = ENOENT, -1;
    freetimer(t);
    return 0;
  }
  if (!t) {
    if ((t = ec->stimer) != NULL)
      ec->stimer = NULL;
    else if ((t = (ev_timer*)malloc(sizeof(ev_timer))) == NULL)
      return errno = ENOMEM, -1;
    t->cbck = cbck;
    t->ctx = ctx;
  }
  if (!mstimeout)
    t->when.tv_sec = t->when.tv_usec = 0;
  else {
    struct timeval tv;
    settime(ec);
    ms2tv(mstimeout, &tv);
    timeradd(&tv, &ec->when, &t->when);
  }
  t->cbck = cbck;
  t->ctx = ctx;
  tp = &ec->timers;
  while((p = *tp) != NULL && !timercmp(&t->when, &p->when, <))
    tp = &p->next;
  t->next = *tp;
  *tp = t;
  return 0;
}

int efn0(hasevents, const ev_ctx *ec) { return ec->nfds || ec->timers; }
int efn0(hasioevents, const ev_ctx *ec) { return ec->nfds != 0; }
int efn0(hastimerevents, const ev_ctx *ec) { return ec->timers != NULL; }

time_t efn0(time, const ev_ctx *ec) {
  return ec->when.tv_sec;
}

const struct timeval *efn0(timeofday, const ev_ctx *ec) {
  return &ec->when;
}

const struct timeval *efn0(updtime, ev_ctx *ec) {
  gettimeofday(&ec->when, NULL);
  return &ec->when;
}

#if EVENT_USES_SELECT

/* check if given fd is valid and return ret if not */
#define checkfdvalid(fd, ret) \
  if (fd < 0 || fd >= FD_SETSIZE) return errno = EINVAL, ret
/* check if I/O monitoring was requested for given fd */
#define checkfdpresent(fd, ret) \
  if (!ec->io[fd].cbck) return errno = ENOENT, ret
#define checkfd(fd, ret) checkfdvalid(fd, ret); checkfdpresent(fd, ret)

/* request or cancel I/O monitoring */
int efn4(reqio, ev_ctx *ec, int fd, ev_t event, ev_cbck *cbck, void *ctx) {
  checkfdvalid(fd, -1);
  if (!cbck) { /* cancel request */
    checkfdpresent(fd, -1);
    FD_CLR(fd, &ec->xfds);
    FD_CLR(fd, &ec->rfds);
    FD_CLR(fd, &ec->wfds);
    ec->io[fd].ctx = NULL;
    ec->io[fd].cbck = NULL;
    if (ec->nfds <= fd + 1) {
      while(fd >= 0 && !ec->io[fd].cbck)
        --fd;
      ec->nfds = fd + 1;
    }
  }
  else { /* new monitoring request */
    if (event & EV_EXCPT) FD_SET(fd, &ec->xfds);
    else FD_CLR(fd, &ec->xfds);
    if (event & EV_READ) FD_SET(fd, &ec->rfds);
    else FD_CLR(fd, &ec->rfds);
    if (event & EV_WRITE) FD_SET(fd, &ec->wfds);
    else FD_CLR(fd, &ec->wfds);
    if (ec->nfds <= fd) ec->nfds = fd + 1;
    ec->io[fd].cbck = cbck;
    ec->io[fd].ctx = ctx;
  }
  return 0;
}

/* return a callback assotiated with fd */
ev_cbck *efn1(io_cbck, const ev_ctx *ec, int fd) {
  checkfd(fd, (ev_cbck*)NULL);
  return ec->io[fd].cbck;
}

/* return a context assotiated with fd */
void *efn1(io_ctx, const ev_ctx *ec, int fd) {
  checkfd(fd, (void*)NULL);
  return ec->io[fd].ctx;
}

/* call a callback for a given fd */
int efn2(iowakeup, ev_ctx *ec, int fd, ev_t event) {
  checkfd(fd, -1);
  callback(ec->io[fd].cbck, ec, fd, event, ec->io[fd].ctx);
  return 0;
}

#else /* EVENT_USES_SELECT */

static int efn2(findfd, const ev_ctx *ec, int fd, int *idxp) {
  int a = 0, b = ec->nfds - 1, m;
  while(a <= b) {
    m = (a + b) >> 1;
    if (ec->pfd[m].fd == fd)
      return m;
    else if (ec->pfd[m].fd < fd)
      a = m + 1;
    else
      b = m - 1;
  }
  if (idxp)
    *idxp = a;
  return -1;
}

#define checkfdvalid(fd, ret) \
  if (fd < 0) return errno = EINVAL, ret
#define checkfdpresent(fd, idx, ret) \
  if ((idx = efn2(findfd, ec, fd, NULL)) < 0) return errno = ENOENT, ret
#define checkfd(fd, idx, ret) \
  checkfdvalid(fd, ret); checkfdpresent(fd, idx, ret)

/* request or cancel I/O monitoring */
int efn4(reqio, ev_ctx *ec, int fd, ev_t event, ev_cbck *cbck, void *ctx) {
  checkfdvalid(fd, -1);
  if (!cbck) { /* cancel request */
    checkfdpresent(fd, fd, -1);
    --ec->nfds;
    if (fd < ec->nfds) {
      memcpy(ec->io + fd, ec->io + fd + 1,
             (ec->nfds - fd) * sizeof(ev_io));
      memcpy(ec->pfd + fd, ec->io + fd + 1,
             (ec->nfds - fd) * sizeof(struct pollfd));
    }
  }
  else { /* new monitoring request */
    int i;
    if (efn2(findfd, ec, fd, &i) < 0) {
      if (ec->afds <= ec->nfds) {
        int j;
        int c = ec->afds + 8;
        ev_io *io = (ev_io *)realloc(ec->io, c * sizeof(ev_io));
        struct pollfd *pfd = (struct pollfd *)
          realloc(ec->pfd, c * sizeof(struct pollfd));
        if (io) ec->io = io;
        if (pfd) ec->pfd = pfd;
        if (!io || !pfd)
          return errno = ENOMEM, -1;
        ec->afds = c;
        for(j = ec->nfds; j > i; --j)
          io[j] = io[j-1], pfd[j] = pfd[j-1];
      }
      ec->pfd[i].fd = fd;
      ++ec->nfds;
    }
    ec->io[i].cbck = cbck;
    ec->io[i].ctx = ctx;
    ec->pfd[i].events = POLLERR|POLLHUP;
    if (event & EV_EXCPT) ec->pfd[i].events |= POLLPRI;
    if (event & EV_READ) ec->pfd[i].events |= POLLIN;
    if (event & EV_WRITE) ec->pfd[i].events |= POLLOUT;
  }
  return 0;
}

/* return a callback assotiated with fd */
ev_cbck *efn1(iocbck, const ev_ctx *ec, int fd) {
  checkfd(fd, fd, NULL);
  return ec->io[fd].cbck;
}

/* return a context assotiated with fd */
void *efn1(ioctx, const ev_ctx *ec, int fd) {
  checkfd(fd, fd, NULL);
  return ec->io[fd].ctx;
}

/* call a callback for a given fd */
int efn2(iowakeup, ev_ctx *ec, int fd, ev_t event) {
  int i;
  checkfd(fd, i, -1);
  callback(ec->io[i].cbck, ec, fd, event, ec->io[i].ctx);
  return 0;
}

#endif /* !EVENT_USES_SELECT */

int efn1(wait, ev_ctx *ec, int mstimeout) {
  ev_timer *t;
  int n;
#if EVENT_USES_SELECT
  int fd;
  fd_set wfd, rfd, xfd;
  struct timeval tv, *tvp;
#else
  int i;
#endif

  if (ec->nested)
    return errno = EAGAIN, -1;
  if (!mstimeout)
    ;
  else if ((t = ec->timers) != NULL) {
    settime(ec);
    n = su2ms(t->when.tv_sec - ec->when.tv_sec,
	      t->when.tv_usec - ec->when.tv_usec);
    if (n <= 0)
      mstimeout = 0;
    else if (mstimeout < 0 || n < mstimeout)
      mstimeout = n;
  }

#if EVENT_USES_SELECT
  if (mstimeout < 0)
    tvp = NULL;
  else {
    ms2tv(mstimeout, &tv);
    tvp = &tv;
  }

  rfd = ec->rfds;
  wfd = ec->wfds;
  xfd = ec->xfds;

  n = select(ec->nfds, &rfd, &wfd, &xfd, tvp);

#else

  n = poll(ec->pfd, ec->nfds, mstimeout);

#endif

  if (n < 0)
    return -1;

  ++ec->nested;

  gettimeofday(&ec->when, NULL);

  while((t = ec->timers) != NULL && !timercmp(&t->when, &ec->when, >)) {
    ec->timers = t->next;
    callback(t->cbck, ec, -1, EV_TIMER, t->ctx);
    freetimer(t);
  }

#if EVENT_USES_SELECT
  for(fd = 0; n > 0 && fd < ec->nfds; ++fd) {
    ev_t e;
    if (!ec->io[fd].cbck) continue;
    else if (FD_ISSET(fd, &xfd)) e = EV_EXCPT;
    else if (FD_ISSET(fd, &wfd)) e = EV_WRITE;
    else if (FD_ISSET(fd, &rfd)) e = EV_READ;
    else continue;
    callback(ec->io[fd].cbck, ec, fd, e, ec->io[fd].ctx);
    --n;
  }
#else
  for(i = 0; n > 0 && i < ec->nfds; ++i) {
    ev_t e;
    if (!ec->pfd[i].revents)
      continue;
    if (ec->pfd[i].revents & POLLERR) e = EV_ERRNO; /* errno? */
    else if (ec->pfd[i].revents & POLLPRI) e = EV_EXCPT;
    else if (ec->pfd[i].revents & POLLOUT) e = EV_WRITE;
    else if (ec->pfd[i].revents & POLLIN) e = EV_READ;
    else if (ec->pfd[i].revents & POLLHUP) e = EV_HUNGUP;
    else if (ec->pfd[i].revents & POLLNVAL) e = EV_ERRNO, errno = EBADF;
    else e = EV_EXCPT;
    callback(ec->io[i].cbck, ec, i, e, ec->io[i].ctx);
    --n;
  }
#endif

  --ec->nested;
  return 0;
}

#ifdef TEST

#include <stdio.h>

#if EVENT_THREADSAFE
# define ectx ev_ctx UNUSED *ec,
#else
# define ectx
#endif

static void ding(ectx int UNUSED fd, ev_t UNUSED event, void *ctx) {
  char *c = (char*)ctx;
  write(1, c, 1);
  if (*c >= 'A' && *c <= 'Z') *c += 'a' - 'A';
  else if (*c >= 'a' && *c <= 'z') *c += 'A' - 'a';
  efn3(settimer, ec, 1500, ding, ctx);
}

static void echo(ectx int UNUSED fd, ev_t UNUSED event, void UNUSED *ctx) {
  char buf[BUFSIZ];
  if (fgets(buf, sizeof(buf), stdin) == 0)
    exit(0);
  printf("Result: %s", buf);
}

int eventMain(void) {
  static char text[] = "\rdingdong ";
  char   *cp;
#if EVENT_THREADSAFE
  ev_ctx *ec = evr_alloc();
#endif
  for (cp = text; *cp; cp++)
     efn3(settimer, ec, 0, ding, cp);
  efn4(reqio, ec, fileno(stdin), EV_READ, echo, 0);
  for (;;)
    efn1(wait, ec, -1);
}

#endif
