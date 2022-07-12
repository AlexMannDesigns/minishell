#!/bin/sh
#a script which periodically checks for leaks using the leaks command line

while true
do
	leaks minishell;
	sleep 1;
	echo waiting 1;
	sleep 1;
	echo waiting 2;
	sleep 1;
	echo waiting 3;
	sleep 1;
done
