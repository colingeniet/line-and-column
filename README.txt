LINE AND COLUMN
A 1010 clone on Unix terminal
by Colin Geniet, Youcef Cherfaoui, Victor Hueca and Alexandre Ribeyre

version 1.1.0

-------------------------------------------------------------------------------
USAGE :

compile : 
	make all
The ncurses library is required. It is should be available with most 
UNIX system. If you don't have it or want to compile it on your own, you can
get it from ftp://ftp.gnu.org/pub/gnu/ncurses/ncurses.tar.gz

delete all files created during compilation :
	make clean
No files are created outside the build directory. to unsinstall, just delete it.


launch :
	./line-and-column

controls :
	arrow keys to move cursor
	1-2-3 to select one of the forms
	enter to confirm location
	q to quit
The game quit as soon as no move are possible



-------------------------------------------------------------------------------
version history :

v 1.1.0 :
	- fixed tearing
	- forms can not move 'outside' of the board anymore

v 1.0.0 :
	- initial release
