# Introduction
Ce projet s’intéresse à la problématique de la désignation du vainqueur du processus électoral.
Au cours du processus électoral, chaque participant peut déclarer sa candidature ou voter pour le candidat élu. Le déroulement du processus électoral a traditionnellement soulevé des difficultés en matière de confiance et de transparence, tandis que le taux d'abstention très élevé en France est un problème qui pourrait être amélioré.
Dans ce projet, nous souhaitons proposer une piste de réflexion sur les protocoles et sur les structures de données afin de mettre en œuvre efficacement le processus de détermination du vainqueur d'une élection, tout en garantissant l'intégrité, la sécurité et la transparence de l'élection.

— Partie 1 : Implementation d’outils de cryptographie.
— Partie 2 : Creation d’un systeme de declarations securises par chiﬀrement asym´etrique.
— Partie 3 : Manipulation d’une base centralis´ee de d´eclarations.
— Partie 4 : Implementation d’un mecanisme de consensus.

## Implementation d’outils de cryptographie.

## Creation d’un systeme de declarations securises par chiﬀrement asymetrique.
Storing
Rsa->key->declaration->list de declaration
## Determination du gagnant de l’election 
La fonction commence par creer deux tables de hachage :
— Hc : une table de hachage (de taille sizeC) pour la liste des candidats.
— Hv : une table de hachage (de taille sizeV) pour la liste des votants.
La fonction parcourt ensuite la liste des d´eclarations, et pour chaque d´eclaration, elle verife grace aux
deux tables de hachage que :
— la personne qui vote a le droit de voter et qu’elle n’a pas d´ej`a vot´e,
— et que la personne sur qui porte le vote est bien un candidat de l’´election.

## Impl´ementation d’un m´ecanisme de consensus.