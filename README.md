# PECHAIN
Notre fichier de configuration est stocké dans `scr/utility.h`. La plupart des paramètres du projet peuvent être modifiés en changeant ce fichier.

## Erreur code

| ereurCode | message              |
| --------- | -------------------- |
| 1         | not a natural number |
| 2         | try too many times   |
| 3         | malloc   failed      |
| 4         | other problem        |

## Commande
Compiler et tester tout le code
```shell
// - windows
./run.bat
// - linux
./run.sh
```
Vérification des fuites de mémoire
Les fichiers générés sont dans le répertoire `./test/log`
```shell
make checkMem
```
Tester un exercice
```shell
make ex1
make ex2
...
make ex9
```
Dessin (q1.5, q7.8)
```shell
cd test 
python test_q1_5_1.py
python test_q1_5_2.py
python test_q7_8.py
```

