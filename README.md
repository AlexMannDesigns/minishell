# minishell
My very own shell program.

To deepen my understanding of Unix systems I have built a very basic implementation of a shell, using bash as a reference.

To compile and run the program, simply run the following command. Please note, this program runs best on MacOS: 

```
make; make clean; ./minishell
```

You'll then be greeted with a title, and will be able to run commands as you would in a "normal" Unix shell:

<img width="1025" alt="Screen Shot 2022-07-27 at 3 24 29 PM" src="https://user-images.githubusercontent.com/69106035/181247850-c8f7965b-60a8-4371-abcc-547b712e520e.png">

Please note, this program does not feature cursor control and will only handle basic commands. Piping, redirects, logical operators and semicolons (to name a few features) are not supported.

The following built-in functions are supported:

```
  - cd (change your working directory)
  - echo (including the '-n' flag, prints text to the standard output)
  - env (including the '-i' flag, allows you to run programs in a temporary environment)
  - setenv (from c-shell, works like 'export' in bash, i.e. allows you to update existing or add new environment variables)
  - unsetenv (lets you permanently environment variables)
  - exit (exits the shell)
```

Beyond those built-in functions, any other command you attempt to run will be searched for in the `$PATH` environment variable, and if it can't be found an error message will be printed and the prompt returned:

<img width="1025" alt="Screen Shot 2022-07-27 at 3 53 39 PM" src="https://user-images.githubusercontent.com/69106035/181251724-26d7f984-33a4-480a-a8e4-a075c5ca5d74.png">

Simple tilde `~` and dollar `$` expansions are supported, as can be seen in the 1st screenshot.
