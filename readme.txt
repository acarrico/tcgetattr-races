Author: Anthony Carrico
Date: 2022-09-22

I declare this source code to be in the public domain.

The purpose of this code is to explore a method for avoiding (or
minimizing) a race condition when getting terminal attributes with
tcgetattr.

The foreground process group will normally be sent SIGTSTP when the
user decides to suspend it, but the process group could also be
started in the background. In this case, when the background process
group accesses the terminal, the terminal driver usually stops it with
SIGTTIN or SIGTTOU. However, the terminal driver does not send these
signals when a process gets the terminal attributes with tcgetattr.

How should a process avoid calling tcgetattr while running in the
background? Typical sample code for managing terminal attributes in a
job control context (Linux Programming Interface, glibc manual, etc.)
doesn't seem to address this issue. Leaving the possibility that the
process will get bogus termios from some other foreground process
group. The purpose of this code is to explore a method for avoiding
(or minimizing) this race condition.

Here is a script of the running the test in the foreground, and then
in the background:

$ cc -o test main.c
$ ./test
foreground
done
$ ./test &
[1] 204351
$ 

[1]+  Stopped                 ./test
$ 
$ fg
./test
foreground
done
$ exit
exit
