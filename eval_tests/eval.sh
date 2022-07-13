#!/bin/sh

echo "Welcome to the minishell eval script";
sleep 1;
echo "hint 1: run leaks.sh in a separate terminal window before you begin ;)";
echo "hint 2: be sure to run me in minishell ;)";
sleep 1;

while true; do
read -p "Do you want to begin the evaluation? (y/n) : " yn
case $yn in
	[yY] ) echo ok, we will proceed...;
			break;;
	[nN] ) echo exiting...;
			exit;;
	* ) echo invalid response;
		sleep 1;;
esac
done

#author file check
while true; do
read -p "check author file? (y/n/q) : " ynq
case $ynq in
	[yY] ) echo ok, checking...;
		(set -x; cat author);
		break;;
	[nN] ) echo ok, let\'s move on...;
		break;;
	[qQ] ) echo exiting...;
		exit;;
	* ) echo invalid response;
		sleep 1;;
esac
done

#Makefile check
while true; do
read -p "check Makefile? (y/n/q) : " ynq
case $ynq in
	[yY] ) echo ok, checking...;
		(set -x; make clean);
		ls;
		sleep 3;
		(set -x; make fclean);
		ls;
		sleep 3;
		(set -x; make);
		ls;
		sleep 3;
		(set -x; make re);
		ls;
		sleep 3;
		(set -x; make fclean);
		ls;
		sleep 3;
		break;;
	[nN] ) echo ok, let\'s move on...;
		break;;
	[qQ] ) echo exiting...;
		exit;;
	* ) echo invalid response;
		sleep 1;;
esac
done
