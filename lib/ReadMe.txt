Yop!

deux lib, la 32 et la 64 bits.
Evidemment, j'ai pu tester que la 32...
l'install ne marchait pas bien chez moi (ubuntu 9.10 karmic) donc j'ai modifié le makefile de la lib32, mais pas celui de la 64 donc à tester pour la 64...

L'install c'est hyper simple:
extraire la bonne lib, aller dedans, et faire "make install"
Ensuite les so sont places au meme endroit que openkn, donc si vous avez deja modif votre .bashrc y'aura pas besoin de le refaire.
Si vous n'avez pas modif votre .bashrc pour kn, faudra le faire là, demander au doc il sait.

Ensuite ça devrait marcher. 
Si ça marche pas y'a juste besoin de libfmodex.so donc au PIRE copiez le so dans vos libs et faites un lien symbolique avec le bon nom à la main.

apres ben la routine, DumbArena, make clean, qmake, make et vous devriez entendre du son. (faut qu'il soit allumé aussi).
Si y'a des erreurs dites le moi.
Si le son vous saoule commentez les .play du main.cpp.

joora



EDIT: le makefile de la version 64bits a été modifié :)
The-Doc
