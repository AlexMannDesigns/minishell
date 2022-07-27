# minishell
My very own shell program.

To deepen my understanding of Unix systems I have built a very basic implementation of a shell, using bash as a reference.

To compile the program, simply run the command: "make; make clean". You can then run the program with: "./minishell".

<img width="1025" alt="Screen Shot 2022-07-27 at 3 32 24 PM" src="https://user-images.githubusercontent.com/69106035/181247816-7545d6bf-5dfb-4c48-a9a1-4390f96e1e46.png">

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

Simple tilde (~) and dollar ($) expansions are supported, as can be seen in the above screenshot.
