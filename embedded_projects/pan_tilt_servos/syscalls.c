#include <sys/stat.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>

#include "../mystm32lib/usart.h"

/* Variables */
extern int __io_putchar(int ch) __attribute__((weak));
extern int __io_getchar(void) __attribute__((weak));


char *__env[1] = { 0 };
char **environ = __env;

static uint32_t min_heap_size = 512;
static uint32_t min_stack_size = 1024;

/* Functions */
void initialise_monitor_handles()
{
}

int _getpid(void)
{
	return 1;
}

int _kill(int pid, int sig)
{
	errno = EINVAL;
	return -1;
}

void _exit (int status)
{
	_kill(status, -1);
	while (1) {}		/* Make sure we hang here */
}


__attribute__ ((weak)) int _read(int file, char *ptr, int len)
{
	
	return USART_read(USART2, ptr, len);
}

int _write(int file, char *ptr, int len)
{
	if (file == 1)
		return USART_write(USART2, ptr, len);
	else
	{
		errno = EBADF;
		return -1;
	}
}


int _close(int file)
{
	return -1;
}


int _fstat(int file, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

int _isatty(int file)
{
	return 1;
}

int _lseek(int file, int ptr, int dir)
{
	return 0;
}

int _open(char *path, int flags, ...)
{
	return -1;
}

int _wait(int *status)
{
	errno = ECHILD;
	return -1;
}

int _unlink(char *name)
{
	errno = ENOENT;
	return -1;
}

int _times(struct tms *buf)
{
	return -1;
}

int _stat(char *file, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

int _link(char *old, char *new)
{
	errno = EMLINK;
	return -1;
}

int _fork(void)
{
	errno = EAGAIN;
	return -1;
}

int _execve(char *name, char **argv, char **env)
{
	errno = ENOMEM;
	return -1;
}

void* _sbrk(ptrdiff_t incr)
{
  static uint8_t* __sbrk_heap_end = NULL;

  extern uint8_t _end; // set by linker
  extern uint8_t _stack; // set by linker
  const uint32_t stack_limit = (uint32_t)&_stack - (uint32_t)min_stack_size;
  const uint8_t* max_heap = (uint8_t*) stack_limit;
  uint8_t* prev_heap_end;

  if (__sbrk_heap_end == NULL)
    __sbrk_heap_end = &_end;

  if (__sbrk_heap_end + incr > max_heap)
  {
    errno = ENOMEM;
    return (void*) -1;
  }

  prev_heap_end = __sbrk_heap_end;
  __sbrk_heap_end += incr;

  return (void*) prev_heap_end;
}
