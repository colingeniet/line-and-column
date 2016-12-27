LINE AND COLUMN
A 1010 clone on Unix terminal
by Colin Geniet, Youcef Cherfaoui, Victor Huesca and Alexandre Ribeyre

version 2.1.0

-------------------------------------------------------------------------------
Usage :

compile : 
	make all
The ncurses library is required. It is should be available with most 
UNIX system. If you don't have it or want to compile it on your own, you can
get it from http://ftp.gnu.org/pub/gnu/ncurses/

delete all files created during compilation :
	make clean
No files are created outside the build directory. to unsinstall, just delete it.


launch :
	./line-and-column

controls :
	- arrow keys to move cursor
	- 1-2-3 or x-c-v to select one of the forms
	- previous / next page to select previous / next form
	- enter to confirm location
	- q to quit
	- Z / shift-Z to undo / redo
	- use Ctrl-X to quit save/load menu

save system :
	The save files allow both to define the environment (set of forms)
	and to save the games. Refer to exemple_board for syntax details.
	A save file can be given as parameter. By default, default_board will
	be loaded.

mouse support -EXPERIMENTAL- :
	To be playable with mouse, your terminal needs to report all mouse
	movement, which is non-standard behavior. 
	On xterm derivated terminals, try with
	TERM=xterm-1003 ./line-and-column --enable-mouse



-------------------------------------------------------------------------------
versions history :

v 2.1.0 :
	- added history
	- tuned game engine to match precisely the original game rules
	- added a weight in random selection
	- removed useless entries in save files
	- added log file

v 2.0.0 :
	- added menu
	- added save
	- added highscores
	- added experimental mouse support

v 1.1.0 :
	- fixed tearing
	- forms can not move 'outside' of the board anymore

v 1.0.0 :
	- initial release
