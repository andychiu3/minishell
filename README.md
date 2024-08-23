# minishell

printf, malloc, free, write, exit, strerror, perror

open, read, close
readline, add_history
rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay

fork, dup, dup2, pipe, 
kill, wait, waitpid, wait3, wait4, 
signal, sigaction, sigemptyset, sigaddset,

getcwd, chdir, opendir, readdir, closedir,

isatty, ttyname, ttyslot, ioctl,
tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

access, stat, lstat, fstat, unlink, 


echo cd pwd export unset env exit
- env
export, VAR, unset, cd
- ctrl C in bash
signal
- ctrl D
exit -> ^D or \n
- ctrl \
does nothing
- tokenize
- AST
- sgl or dbl quote
- prompt
readline
- history
add_history
- ''
- "$"
- < INPUT
- > TRUNC
- << HEREDOC 
- >> APPEND 
- | PIPE
- $ VAR
- $?
- echo -n
- cd
- pwd
- export
- unset
- env
- exit
- readline() leaks in valgrind

bonus
- ||
- &&
- wildcard *

no
- non interactive
- shlvl?
- ;
- \
