#include <iostream>
#include <string>
#include <QApplication>
#include "Grille.h"
#include "Grille.cpp"


int main(int argc, char **argv)
{
  QApplication app (argc, argv);

  int nombreColonnes = 20;
  int nombreLignes = 20;

  Grille *grille = new Grille(nombreColonnes, nombreLignes);
  grille->InitialiserGrille("aleatoire");
  grille->afficher();
  grille->show();

  grille->lancerDefilementVie();

  return app.exec();
}

