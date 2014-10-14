Tests systemtap
===============

Présentation
------------

Ce projet vis à reconstituer la trace d'appels système, de l'entrée dans le
noyau à la sortie. On cherche à savoir quelles sont les fonctions appelées par
l'appel système. On ne s'intéresse qu'aux fonctions déclarées dans le même
fichier que l'appel système et aux fonctions de sécurité.

Arborescence du projet
----------------------

.
├── bin 		-- fichiers de tests compilés
├── dependencies 	-- pour chaque appel système,
│		    	   un fichier de même nom que celui-ci indiquant 
│		    	   quel est son fichier d'origine
├── modules		-- scripts SystemTap instanciés et compilés
│			   sous la forme de modules du noyau
├── results		-- trace d'appels de chaque appel système
├── syscaller.stp	-- script SystemTap de base
└── samples		-- codes de tests, rangés par sous-système

SystemTap
---------

SystemTap est à la fois un langage et une suite de compilation servant à
produire des modules d'instrumentation chargeables dans le noyau Linux. Il
permet de tracer des appels de fonctions, de programmer des points d'arrêts, 
etc. Cela peut servir au débogage ou au test.
