LINE AND COLUMN
clone de 1010 pour terminal Unix
par Colin Geniet, Youcef Cherfaoui, Victor Huesca et Alexandre Ribeyre

version 1.1.0

----------------------------------------------------------------------------
Utilisation:

compiler :
	make all
La librairie ncurses est requise. Elle devrait être disponible sur la plupart
des systèmes UNIX. Elle peut être obtenue à
ftp://ftp.gnu.org/pub/gnu/ncurses/ncurses.tar.gz

supprimer les fichiers crées à la compilation :
	make clean
Aucun fichier n'est crée à l'extérieur du dossier principal. Pour tout 
désinstaller, il suffit de le supprimer.


lancer :
	./line-and-column

contrôles :
	flèches directionelles pour déplacer le curseur
	1-2-3 pour selectionner une des formes
	entrée pour comfirmer l'emplacement
	q pour quitter
Le jeu s'arrète des qu'aucun mouvement est possible.
	
	
----------------------------------------------------------------------------
Historique des versions :

v 1.1.0
	- problème de rafraichissement fixé
	- les formes ne peuvent plus 'sortir' du plateau

v 1.0.0
	-version initiale
