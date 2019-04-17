# simple_shell

simple_shell is a project to emulate the capabilities of the venerable [Bourne shell](https://en.wikipedia.org/wiki/Bourne_shell). simple_shell aims to replicate shell's functionality allowing the user to interact with a cli to run executables and scripts, access shell built-ins, and manipulate files.

## Getting Started

These instructions will help you get a copy of simple_shell on to your local machine.  They show how to use simple_shell with examples and demonstrate its capabilities.

### Prerequisites

simple_shell has been tested and compiled with `gcc 4.8.4` on `Ubuntu 14.04`.

To check your version of gcc type:

```
gcc --version
```

To install gcc 4.8.8 on Ubuntu 14.04, use the [following directions](https://gist.github.com/application2000/73fd6f4bf1be6600a2cf9f56315a2d91).

For use on other Linux distributions, please see your distributions instructions for installing and setting up gcc.


### Installing

Clone this github repository to have a local copy of the source files.

```
git clone https://github.com/dmaring/simple_shell.git
```

Compile the source code in your simple_shell directory using gcc

```
cd simple_shell && gcc -Wall -pedantic -Werror -Wextra *.c -o simple_shell
```



## Using simple_shell

simple_shell works in two modes just like the Bourne shell.  In interactive mode the user launches shell and inputs commands into the standard input.  These commands are then parsed into tokens and simple_shell searches through the environment PATH for a matching executable of the leading command.  If an executable is found, simple_shell will  run that executable with the supplied options and arguments.

In non-interactive mode, the shell doesn't directly interact with the user.  Instead the shell is used by a script to run commands or commands are piped directly into the shell's standard input.  In this mode the shell is launched, commands are run, and then the shell exits.  Please see the Basic Examples in Non-interactive Mode for more details.

### Basic Examples in Interactive Mode

simple_shell works very similarily to the [Bourne shell](https://en.wikipedia.org/wiki/Bourne_shell).  simple_shell will read in the standard input (the keyboard by default) and send output to the standard output and errors to standard error.

To start simple_shell in Interactive Mode type:
```
$ ./simple_shell
```

### Example: List directory contents in Long Listing Format
Input:

```
($) ls -l
```
Output:

```
total 140
-rw-r--r-- 1 vagrant vagrant  3431 Apr 15  2019 README.md
-rw-r--r-- 1 vagrant vagrant  1272 Apr 12 19:26 _putchar.c
-rw-r--r-- 1 vagrant vagrant   750 Apr  9 22:33 _realloc.c
-rwxr-xr-x 1 vagrant vagrant 28704 Apr 15  2019 a.out
-rw-r--r-- 1 vagrant vagrant   874 Apr 15 17:40 convert.c
-rw-r--r-- 1 vagrant vagrant   690 Apr 12 19:18 envhelpers.c
-rw-r--r-- 1 vagrant vagrant  2096 Apr 15 17:58 helpers.c
-rw-r--r-- 1 vagrant vagrant  2856 Apr 15 00:45 main.c
-rw-r--r-- 1 vagrant vagrant   997 Apr  5 22:57 man_1_simple_shell
-rw-r--r-- 1 vagrant vagrant  1323 Apr 15 00:44 shell.h
-rwxr-xr-x 1 vagrant vagrant 18896 Apr 15 19:19 simple_shell
-rw-r--r-- 1 vagrant vagrant  2701 Apr 12 23:14 string_char.c
-rw-r--r-- 1 vagrant vagrant   526 Apr  9 22:33 string_int.c
```
### Example: Display environment variables using `env` builtin
Input

```
($) env
```

Output

```
XDG_SESSION_ID=28
TERM=xterm-256color
SHELL=/bin/bash
SSH_CLIENT=10.0.2.2 62435 22
SSH_TTY=/dev/pts/2
USER=vagrant
MAIL=/var/mail/vagrant
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games
PWD=/holberton/repos/simple_shell
LANG=en_US.UTF-8
PS1=\[\e]0;\u@\h: \w\a\]\[\033[1;31m\]\u \[\033[1;31m\]@ \[\033[0;36m\]\W \[\033[0;37m\]$(git symbolic-ref --short HEAD 2> /dev/null)\ $ \[\e[00m\]
HOME=/home/vagrant
LOGNAME=vagrant
SSH_CONNECTION=10.0.2.2 62435 10.0.2.15 22
LESSOPEN=| /usr/bin/lesspipe %s
XDG_RUNTIME_DIR=/run/user/1000
LESSCLOSE=/usr/bin/lesspipe %s %s
OLDPWD=/home/vagrant
_=./simple_shell

```

### Basic Examples in Non-Interactive Mode

### Example: Using simple_shell as the directive in a script
File `myscript.sh`

```
#! /holberton/repos/simple_shell/simple_shell
echo "echo Hello World"
```

Execute script

```
($) ./myscript.sh
```

Output

```
Hello World
```

### Example: Pipe commands into simple_shell
Input

```
($) echo "echo hello world" | ./simple_shell
```

Output

```
hello world
```


## Authors

* **Thomas Graeff** - [https://github.com/graefft](https://github.com/graefft)
* **Drew Maring** - [https://github.com/dmaring](https://github.com/dmaring)

See also the list of [contributors](https://github.com/dmaring/simple_shell/blob/master/AUTHORS) who participated in this project.


## Acknowledgments

* Thanks to Holberton School and our fellow cohort 8 members for their time and support
* Inspiration from this project stems from the original [Bourne shell](https://en.wikipedia.org/wiki/Bourne_shell)

