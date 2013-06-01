#include <sulydulieu.h>
#include <stdarg.h>
void varfunc (char *buf, int id, ...) {
  va_list tag=buf;

  va_start (tag, id);

  if (id == 0) {
    int arg1;
    char *arg2;
    long arg3;

    arg1 = va_arg (tag, int);
    arg2 = va_arg (tag, char *);
    arg3 = va_arg (tag, long);
  }

  else {
    char *arg1;
    char *arg2;
    long arg3;

    arg1 = va_arg (tag, char *);
    arg2 = va_arg (tag, char *);
    arg3 = va_arg (tag, long);
  }

  va_end (tag);
}