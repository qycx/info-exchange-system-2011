/* $Id: event.h,v 1.2 2003/02/01 23:53:40 mjt Exp $
 * simple event library.
 * Written by Michael Tokarev <mjt@corpit.ru>
 * LGPL
 */

#ifndef _EVENT_H_INCLUDED
#define _EVENT_H_INCLUDED

#include <sys/types.h>

struct timeval;

typedef enum {
  EV_TIMER	= 0x00,
  EV_READ	= 0x01,
  EV_WRITE	= 0x02,
  EV_RDWR	= EV_READ|EV_WRITE,
  EV_EXCPT	= 0x04,  /* cannot be used in event_io_register() */
  EV_ERRNO	= 0x08,  /* error: errno is set appropriately */
  EV_HUNGUP	= 0x10   /* Hung up: used only with poll() */
} ev_t;

typedef void ev_cbck_fn(int fd, ev_t event, void *ctx);

time_t ev_time();
const struct timeval *ev_timeofday();
const struct timeval *ev_updtime();

int ev_hasevents();
int ev_hasioevents();
int ev_hastimerevents();
int ev_wait(int mstimeout);

int ev_settimer(int mstimeout, ev_cbck_fn *cbck, void *ctx);
int ev_reqio(int fd, ev_t event, ev_cbck_fn *cbck, void *ctx);
ev_cbck_fn *ev_iocbck(int fd);
void *ev_ioctx(int fd);
int ev_iowakeup(int fd, ev_t event);

/* thread-safe variants */

struct ev_ctx;
typedef struct ev_ctx ev_ctx;

typedef void evr_cbck_fn(ev_ctx *ec, int fd, ev_t event, void *ctx);

ev_ctx *evr_alloc();
ev_ctx *evr_free(ev_ctx *ec);

time_t evr_time(const ev_ctx *ec);
const struct timeval *evr_timeofday(const ev_ctx *ec);
const struct timeval *evr_updtime(ev_ctx *ec);

int evr_hasevents(const ev_ctx *ec);
int evr_hasioevents(const ev_ctx *ec);
int evr_hastimerevents(const ev_ctx *ec);
int evr_wait(ev_ctx *ec, int mstimeout);

int evr_settimer(ev_ctx *ec, int mstimeout, evr_cbck_fn *cbck, void *ctx);
int evr_ioreq(ev_ctx *ec, int fd, ev_t event, evr_cbck_fn *cbck, void *ctx);
evr_cbck_fn *evr_iocbck(const ev_ctx *ec, int fd);
void *evr_ioctx(const ev_ctx *ec, int fd);
int evr_iowakeup(ev_ctx *ec, int fd, ev_t event);

#endif
