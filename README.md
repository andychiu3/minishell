# minishell

printf, malloc, free, write, exit, strerror, perror

open, read, close
readline, add_history
rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay

fork, dup, dup2, pipe, 
kill, wait, waitpid, wait3, wait4, 
signal, sigaction, sigemptyset, sigaddset,

getcwd, chdir, opendir, readdir, closedir, access, getenv

isatty, ttyname, ttyslot, ioctl,
tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

stat, lstat, fstat, unlink, 


echo cd pwd export unset env exit
- env
export, VAR, unset, cd
- ctrl C in bash -> newline
signal
- ctrl D -> EOF
exit -> ^D or \n
- ctrl \ -> signal quit
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
- < INPUT 4
- > TRUNC 5
- << HEREDOC 7
- >> APPEND 6
- | PIPE
- $ VAR
- $?
- echo -n v
- cd
- pwd v
- export v
- unset
- env v
- exit 1 2
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
