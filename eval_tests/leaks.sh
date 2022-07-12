#!/bin/sh
#a script which periodically checks for leaks using the leaks command line

while true
do
	leaks minishell;
	sleep 1;
	printf "waiting 1";
	sleep 1;
	printf ", 2";
	sleep 1;
	printf ", 3...\n";
	sleep 1;
done
