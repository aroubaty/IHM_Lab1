# IHM_Lab1

## Commande a utiliser
### Récupèrer les métadata avec ffprobe
Fichier de test : small.mp4

`ffprobe small.mp4`


### Utilisation de ffmpeg

Fichier de test : small.mp4

Fichier de sortie : output.avi

Début à 2 sec et durée de 1 sec

`ffmpeg -i small.mp4 -ss 2 -t 1 output.avi`


