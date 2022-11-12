#include "Grille.h"
#include <iostream>
#include <string>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QTimer>
#include <time.h>

Grille::Grille(int nombreColonnes, int nombreLignes)
{
    this->nombreColonnes = nombreColonnes; // colonne de la grille
    this->nombreLignes = nombreLignes; // ligne de la grille
    this->tab = new int[nombreColonnes * nombreLignes]; // la grille au dimention colonne*ligne
    this->initialiseAffichage = false; // variable pour savoir si la grille a été initaliser

    this->setWindowTitle("Jeux de la vie !");
    // fixe la taille de la grille
    this->setFixedSize(nombreColonnes * 30 + 60, nombreLignes * 30 + 60);
    // ajoute au layout
    this->layout = new QGridLayout();
    this->setLayout(this->layout);
}

// methode pour initialiser la grille qui prend en paramettre une chaine de caractère.
// La chaine de caractère corespond au choix de l'initallisation de la grille
void Grille::InitialiserGrille(std::string choix)
{
    int damier = 0;
    srand(time(NULL));

    // boucle sur les ligne et collonne
        for (int indiceLigne = 0; indiceLigne < nombreLignes; indiceLigne++)
        {
            for (int indiceColonne = 0; indiceColonne < nombreColonnes; indiceColonne++)
            {
                int indiceCaseTab = indiceLigne * nombreColonnes + indiceColonne;

                // option ou la grille et remplie
                if (choix == "remplie")
                {
                    tab[indiceCaseTab] = 1;
                }

               // option ou la grille est remplie de façon aléatoire
                else if (choix == "aleatoire")
                {
                    tab[indiceCaseTab] = rand() % 2;
                }

                // option ou la grille est remplie en damier -> 101010101...
                else if (choix == "damier")
                {
                    if (damier == 0)
                    {
                        tab[indiceCaseTab] = 0;
                        damier = 1;
                    }
                    else
                    {
                        tab[indiceCaseTab] = 1;
                        damier = 0;
                    }
                }
                // sinon la grille est vide
                else
                {
                    tab[indiceCaseTab] = 0;
                }
            }
        }
}

// methode permetant de jouer le jeu de la vie avec le differante methode de la classe
void Grille::calculerVieEtAfficher() {
   this->calculerVie();
   this->afficher();
   this->lancerDefilementVie();
}

// lance l'application jeu de la vie avec un timer
void Grille::lancerDefilementVie() {
   QTimer::singleShot(500, this, &Grille::calculerVieEtAfficher);
}

// methode permettant d'afficher la grille
void Grille::afficher()
{
    //boucle sur les lignes et les collonnes
    for (int indiceLigne = 0; indiceLigne < nombreLignes; indiceLigne++)
    {
        for (int indiceColonne = 0; indiceColonne < nombreColonnes; indiceColonne++)
        {
           // création d'un bouton
           QPushButton *button;

           //si la fenêtre a déja etait afficher  recupère tout les boutton de la grille
           if (this->initialiseAffichage) {
                QLayoutItem *item = layout->itemAtPosition(indiceLigne, indiceColonne);
                QWidget *widget = item->widget();
                button = dynamic_cast<QPushButton*>(widget);
            }
           // sinon crée des boutton pour chaque case de la grille
            else {
                button = new QPushButton(" ");
                this->layout->addWidget(button, indiceLigne, indiceColonne);
            }

            // choisie la couleur du boutton en fonction de si elle est vide ou non
            // -> vide : gris / remplis : jaune
            if (tab[indiceLigne * nombreColonnes + indiceColonne] == 0) {
                button->setStyleSheet("background-color:gray;");
            }
            else {
                button->setStyleSheet("background-color:yellow;");
            }
        }
    }

    // affiche la grille dans le terminale
    for (int indiceLigne = 0; indiceLigne < nombreLignes; indiceLigne++)
    {
        for (int indiceColonne = 0; indiceColonne < nombreColonnes; indiceColonne++)
        {
            std::cout << tab[indiceLigne * nombreColonnes + indiceColonne];
        }
        std::cout << std::endl;
    }
    this->initialiseAffichage = true;
}

// methode qui donne la somme des voisin d'une case
int Grille::nbVoisin(int indiceLigne, int indiceColonne)
{

    int sommeVoisin = getValeurTab(((indiceLigne + 1) * nombreColonnes) + indiceColonne) +
                      getValeurTab(((indiceLigne - 1) * nombreColonnes) + indiceColonne);

    if (indiceColonne > 0)
    {
        sommeVoisin += getValeurTab((indiceLigne * nombreColonnes) + (indiceColonne - 1)) +
                       getValeurTab(((indiceLigne + 1) * nombreColonnes) + (indiceColonne - 1));
        if (indiceLigne > 0)
        {
            getValeurTab(((indiceLigne - 1) * nombreColonnes) + (indiceColonne - 1));
        }
    }

    if (indiceColonne < (nombreColonnes - 1))
    {
        sommeVoisin += getValeurTab((indiceLigne * nombreColonnes) + (indiceColonne + 1)) +
                       getValeurTab(((indiceLigne + 1) * nombreColonnes) + (indiceColonne + 1));
        if (indiceLigne > 0)
        {
            getValeurTab(((indiceLigne - 1) * nombreColonnes) + (indiceColonne + 1));
        }
    }

    return sommeVoisin;
}

//methode qui donne la valeur d'une case
int Grille::getValeurTab(int indice)
{
    if (indice >= 0 && indice < (nombreColonnes * nombreLignes))
    {
        return tab[indice];
    }
    else
    {
        return 0;
    }
}

//methode permettant de calculer une iteration du jeu de la vie
void Grille::calculerVie()
{
    int tabVoisin[nombreColonnes * nombreLignes];
    for (int indiceLigne = 0; indiceLigne < nombreLignes; indiceLigne++)
    {
        for (int indiceColonne = 0; indiceColonne < nombreColonnes; indiceColonne++)
        {
            tabVoisin[indiceLigne * nombreColonnes + indiceColonne] = nbVoisin(indiceLigne, indiceColonne);
        }
    }

    for (int indiceLigne = 0; indiceLigne < nombreLignes; indiceLigne++)
    {
        for (int indiceColonne = 0; indiceColonne < nombreColonnes; indiceColonne++)
        {
            if (tab[indiceLigne * nombreColonnes + indiceColonne] == 1)
            {
                int nombreVoisin = tabVoisin[indiceLigne * nombreColonnes + indiceColonne];
                if (tabVoisin[indiceLigne * nombreColonnes + indiceColonne] <= 1 || tabVoisin[indiceLigne * nombreColonnes + indiceColonne] >= 4)
                {
                    tab[indiceLigne * nombreColonnes + indiceColonne] = 0;
                }
            }
            else
            {
                if (tabVoisin[indiceLigne * nombreColonnes + indiceColonne] == 3)
                {
                    tab[indiceLigne * nombreColonnes + indiceColonne] = 1;
                }
            }
        }
    }
}
