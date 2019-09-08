# Shell_In_C

This is a shell program made in C langage.
Type 'help' to see all the available commands.

Windows 10 OS 64 bits
Eclipse @ toolchain: mingw 64 bits
External library used: pthread.

Setup:
- download mingw-w64 in https://sourceforge.net/projects/mingw-w64/
- install it in default folder (C:\Program Files\mingw-w64)
- download external library pthread at ftp://sourceware.org/pub/pthreads-win32/pthreads-w32-2-9-1-release.zip and install it with the toolchain
- make sure to add '-pthread' command commpilation in you the project (https://i.ibb.co/y8rjpYh/2.png)
- Compile the program (the compilation command will look like this: gcc -pthread -o Shell_In_C "src\\functions.o" "src\\main.o")
- in order to launch the program, add "C:\Program Files\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin" to the path in system environment variables (https://www.architectryan.com/2018/03/17/add-to-the-path-on-windows-10/)
- Have fun!