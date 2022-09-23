/* Author: Anthony Carrico
   Date: 2022-09-22

   I declare this source code to be in the public domain.

   See readme.txt for the purpose of this code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

static struct termios user_terminal_attr;

static void reset_user_terminal_attr()
{
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &user_terminal_attr) == -1)
    {
      perror("tcsetattr");
      _exit(EXIT_FAILURE);
    }
};

int main() {
  if (isatty (STDIN_FILENO) == 0)
    {
      perror("isatty");
      exit(EXIT_FAILURE);
    }

  /* Here is the key idea:

     If the process is started in the background, this empty read will
     provoke the terminal driver into signaling the process group with
     SIGTTIN, stopping the process: */
  if (read(STDIN_FILENO, 0, 0) == -1)
    {
      perror("read");
      exit(EXIT_FAILURE);
    }

  printf("foreground\n");

  /* Now the process is likely to be in the foreground. If it had been
     in the background, this might get bogus termios from some other
     foreground process group: */
  if (tcgetattr(STDIN_FILENO, &user_terminal_attr) == -1)
    {
      perror("tcgetatttr");
      exit(EXIT_FAILURE);
    }

  atexit(reset_user_terminal_attr);

  /* Do something such as changing terminal attributes and handling
     job control signals ... */

  printf("done\n");
  return EXIT_SUCCESS;
}
