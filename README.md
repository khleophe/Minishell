*This project has been created as part of the 42 curriculum by sdabbas and jdelmott*

# Minishell

## Description
This project consists of creating a **rudimentary Shell** in C, capable of executing commands and handling basic user interactions. The primary goal is to gain a deep understanding of process management, file descriptors, and inter-process communication via pipes.

**Key Features:**
* **Full Parsing**: Token management (words, pipes, redirections) and quote handling (single and double).
* **Execution**: Launching binaries via the `PATH` environment variable or through relative/absolute paths.
* **Built-ins**: Custom implementation of `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
* **Pipes & Redirections**: Handling of pipes (`|`) and redirections (`<`, `>`, `<<`, `>>`).
* **Signals**: Handling of `Ctrl+C`, `Ctrl+\`, and `Ctrl+D`.

## Instructions
To compile the program, simply run the command `make` in your terminal; this will create the `minishell` executable. To start the shell, run it with `./minishell`.

Once the prompt appears, you can use it like a standard terminal:
* **Basic commands**: Type any command like `ls`, `cat`, or `grep`.
* **Built-ins**: Use internal commands such as `cd` to move, `echo -n` to display text, or `export` to set variables.
* **Redirections**: You can send output to a file with `< Makefile cat` or chain commands using pipes like `cat Makefile | grep RESET`.
* **Exit**: To leave the program, simply type `exit` or press `Ctrl+D`.

## Ressources
&emsp;Articles utiles: <br />
-https://linuxize.com/series/bash-scripting-fundamentals/ <br />
-https://mediumcom@gibratdylanminishell-42-lart-de-créer-un-shell-performant-et-maintenable-53c0aede140e <br />
-https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf <br />
-https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218 <br />
-https://medium.com/@mostafa.omrane/mes-conseils-si-je-devais-recommencer-minishell-a9783c51ba1b <br />
-https://github.com/ugozchi/42_Minishell <br />
-https://42-cursus.gitbook.io/guide/3-rank-03/minishell/functions#stat-and-lstat-and-fstat <br />
-https://ft42.notion.site/Minishell-04-06-25-2099c27081be80448dadca1fe664857c <br />
-https://www.youtube.com/watch?v=SwIPOf2YAgI <br />
-https://igupta.in/blog/writing-a-unix-shell-part-1/ <br />
-https://medium.com/@gibrat.dylan/minishell-42-lart-de-créer-un-shell-performant-et-maintenable-53c0aede140e <br />
-https://linuxize.com/post/bash-read/ <br />
-https://brennan.io/2015/01/16/write-a-shell-in-c/ <br />
-https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218 <br />
-https://www.gnu.org/software/bash/manual/bash.html#Shell-Commands <br />
-https://www.ibm.com/docs/fr/aix/7.2.0?topic=e-exec-execl-execle-execlp-execv-execve-execvp-exect-fexecve-subroutine <br />
-https://man7.org/linux/man-pages/man3/readline.3.html <br />
-https://web.mit.edu/gnu/doc/html/rlman_2.html <br />
-http://marionpatrick.free.fr/man_html/html/tuto_shell.html#chp3.3.2.3 <br />
-https://github.com/ugozchi/42_Minishell/blob/main/sources/4_builtins/builtins_utils.c <br />
-https://www.lamsade.dauphine.fr/~bnegrevergne/ens/Unix/static/projet.pdf <br />
-https://www.codequoi.com/manipuler-un-fichier-a-laide-de-son-descripteur-en-c/#open--ouvrir-ou-créer-un-fichier-en-c <br />
-http://manpagesfr.free.fr/man/man3/exit.3.html <br />
-https://www.malekal.com/la-commande-cd-linux-utilisation-et-exemple/ <br />
-https://fr.wikipedia.org/wiki/Unset <br />
