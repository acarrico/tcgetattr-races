The purpose of this code is to explore a method for avoiding (or
minimizing) a race condition when getting terminal attributes with
tcgetattr. See the comments in main.c for details. Here is a script of
the running the test in the foreground, and then in the background:

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
