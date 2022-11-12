#ifndef GRILLE_HPP
#define GRILLE_HPP

#include <string>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QTimer>

class Grille : public QWidget {

    private :
        int nombreColonnes, nombreLignes;
        int *tab;
        QGridLayout *layout;
        bool initialiseAffichage;

        int getValeurTab(int indice);
        int nbVoisin(int i, int j);
        void calculerVie();
        void calculerVieEtAfficher();

    public :
        Grille(int nombreColonnes,int nombreLignes);
        void InitialiserGrille(std::string choix);
        void lancerDefilementVie();
        void afficher();



} ;
#endif //POINT_HPP
