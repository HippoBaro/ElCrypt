# ElCrypt

Rush de première année à Epitech. Réalisation d'un programme de chiffrement symétrique similaire à
DES ou Blowfish (schéma de Feistel). Très gros challenge : délai de 48 heures pour rendre.

# L'essentiel :
    * Utilitaire de chriffrage symétrique à clé privée.
    * Algorithme de chiffrement par bloc de 64 bits basé sur un réseau de
      Feistel à 8 tours.
    * Utilisation de clé de 56 bits (64 bits - LSB)
    * Support du padding PKCS5.
    * Un valgrind impeccable.
    * Code propre, clair et optimisé au maximum (de mes compétences).

# Utilisation :

    ./elcrypt -e/d -f [fichier source] -o [fichier destination] -k [clé]

    * -e : chiffrement
    * -d : déchiffrement
    * -f : source
    * -o : destination
    * -k : clé (héxadécimale) Ex : 0x0123456789ABCDEF

# Info

Le sujet chiffré du rush est inclu dans le repo (sujet.pdf.enc). Décodez-le avec la clé 0x0123456789ABCDEF pour pouvoir le lire ;)

    ./elcrypt -d -f sujet.pdf.enc -o sujet.pdf -k 0x0123456789ABCDEF

With love,
barrau_h.
