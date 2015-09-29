# IHM_Lab1

## Commande a utiliser
### Récupèrer les métadata avec ffprobe
Fichier de test : small.mp4

`ffprobe small.mp4`


### Utilisation de ffmpeg

Fichier de test : small.mp4

Fichier de sortie : output.avi

Interval choisie : de 1:20 à 1:30

`ffmpeg -i small.mp4 -read_intervals 1:20%1:30 output.avi`


