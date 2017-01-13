#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define MAX_MUTARI_JUCATOR 100
#define MAX_MATRICE 50
using namespace std;
struct tablaJoc
{
    unsigned int linie;
    unsigned int coloana;
    int valoare[MAX_MATRICE][MAX_MATRICE];
};
struct mutariJucator
{
    unsigned int primaC, adouaC;
    mutariJucator *urm;
};

void afisareTableJoc(tablaJoc matriceJoc, int dimMatriceJoc, tablaJoc vizitat)
{
    for(matriceJoc.linie = 0; matriceJoc.linie < dimMatriceJoc; matriceJoc.linie++)
    {
        for(matriceJoc.coloana = 0; matriceJoc.coloana < dimMatriceJoc; matriceJoc.coloana++)
            if(vizitat.valoare[matriceJoc.linie][matriceJoc.coloana] == 0)
            {
                int valoare = matriceJoc.linie * dimMatriceJoc + matriceJoc.coloana + 1;
                if(valoare < 10)  cout << valoare << "  ";
                else cout << valoare << " ";
            }
            else cout << (char)(matriceJoc.valoare[matriceJoc.linie][matriceJoc.coloana]+150) << "  ";
        cout << "\n";
    }
}

int main()
{
    system ("color 0A");
    int nivelJoc;
    int v[100];
    mutariJucator *listaMutari, *listaMutariStart;
    listaMutari = new mutariJucator;
    listaMutariStart = listaMutari;
    unsigned short culoare;
    tablaJoc matriceJoc, vizitat;
    cout<<"Cum joc? \nJocul are 3 niveluri, care contin cate o tabla cu din ce in ce\nmai multe casute. Aveti restrictii de timp si de mutari. \n";
    cout<<"Casutele de la nivelul usor vor putea fii accesate prin numerele de la 1 la 4.\nCasutele vor putea fii accesate astfel:\n1 2\n3 4 \n";
    cout<<"Pentru nivelul mediu :\n1  2  3  4\n5  6  7  8\n9  10 11 12\n13 14 15 16\nPentru nivelul greu :\n1  2  3  4  5  6\n7  8  9  10 11 12 \n13 14 15 16 17 18\n19 20 21 22 23 24\n25 26 27 28 19 30\n31 32 33 34 35 36\n";

    cout<<"Alege dificultatea jocului: \n";
    cout<<"Pentru nivel usor apasati tasta 1 \n";
    cout<<"Pentru nivel mediu apasati tasta 2 \n";
    cout<<"Pentru nivel greu apasati tasta 3 \n";
    nivelJoc = getch() - 48;
    while(nivelJoc!= 1 && nivelJoc!= 2 && nivelJoc!=3)
    {
        cout<<"Valoare introdusa nu exista. Eroare.\n";
        cout<<"Introduceti orice tasta pentru a continua";
        getch();
        system("cls");
        cout<<"Alege dificultatea jocului: \n";
        cout<<"Pentru nivel usor apasati tasta 1 \n";
        cout<<"Pentru nivel mediu apasati tasta 2 \n";
        cout<<"Pentru nivel greu apasati tasta 3 \n";
        nivelJoc = getch() - 48;
    }
    system("cls");

    unsigned int dimMatriceJoc, maxMutari, maxTimp;
    if(nivelJoc == 1)
    {
        dimMatriceJoc = 2;
        maxMutari = 20;
        maxTimp = 60;
    }
    else if(nivelJoc == 2)
    {
        dimMatriceJoc = 4;
        maxMutari = 30;
        maxTimp = 120;
    }
    else
    {
        dimMatriceJoc = 6;
        maxMutari = 100;
        maxTimp = 600;
    }
    srand(time(NULL));

    memset(v, 0, sizeof(v));

    for(matriceJoc.linie = 0; matriceJoc.linie < dimMatriceJoc; matriceJoc.linie++)
        for(matriceJoc.coloana = 0; matriceJoc.coloana < dimMatriceJoc; matriceJoc.coloana++)
        {
            int nrCarte = rand() % (dimMatriceJoc * dimMatriceJoc / 2) + 1;
            while(v[nrCarte] == 2)
                nrCarte = rand() % (dimMatriceJoc * dimMatriceJoc / 2) + 1;
            matriceJoc.valoare[matriceJoc.linie][matriceJoc.coloana] = nrCarte;
            vizitat.valoare[matriceJoc.linie][matriceJoc.coloana] = 0;
            v[nrCarte]
            ++;
        }

    int cartonaseNimerite = 0, nrMutari = 0, secunde = 0;

    clock_t start = clock();

    while(1)
    {
        system("cls");

        clock_t temp = clock();
        int mutari = maxMutari - nrMutari, timp = maxTimp - (temp - start) / CLOCKS_PER_SEC;
        if(mutari <= 0)
        {
            cout << "Ai ramas fara mutari. Ai pierdut!\n";
            return 0;
        }
        if(timp <= 0)
        {
            cout<<"Ai ramas fara timp. Ai pierdut!\n";
        }
        cout << "Mai ai:" << timp << " secunde\n";
        cout << "Mai ai:" << mutari << " mutari\n";

        afisareTableJoc(matriceJoc, dimMatriceJoc, vizitat);


        cout << "Introduceti prima carte:\n";
        int xs, ys, primaCarte;
        cin >> primaCarte;
        xs=(primaCarte-1)/dimMatriceJoc;
        ys=(primaCarte-1)%dimMatriceJoc;
        if(vizitat.valoare[xs][ys] != 0 || xs < 0 || xs >= dimMatriceJoc || ys < 0 || ys >= dimMatriceJoc)
        {
            cout << "Eroare! Cartea a mai fost aleasa o data sau e in afara matrice de joc!";
            cout<<"Introduceti orice tasta pentru a continua";
            getch();
            continue;
        }
        system("cls");
        vizitat.valoare[xs][ys]= 1;
        afisareTableJoc(matriceJoc, dimMatriceJoc, vizitat);

        cout << "Introduceti coordonatele celei de-a doua carte:\n";
        int xf,yf,aDouaCarte;
        cin >>aDouaCarte;
        xf=(aDouaCarte-1)/dimMatriceJoc;
        yf=(aDouaCarte-1)%dimMatriceJoc;
        if(vizitat.valoare[xf][yf] != 0 || xf < 0 || xf >= dimMatriceJoc || yf < 0 || yf >= dimMatriceJoc)
        {
            vizitat.valoare[xs][ys] = 0;
            cout << "Eroare! Cartea a mai fost aleasa o data sau e in afara matricei de joc!";
            cout<<"Introduceti orice tasta pentru a continua";
            getch();
            continue;
        }
        system("cls");
        vizitat.valoare[xf][yf] = 1;
        afisareTableJoc(matriceJoc, dimMatriceJoc, vizitat);

        if(matriceJoc.valoare[xs][ys] != matriceJoc.valoare[xf][yf])
        {
            vizitat.valoare[xs][ys] = 0;
            vizitat.valoare[xf][yf] = 0;
            cout << "Nu ai nimerit\n";
        }
        else
        {
            cartonaseNimerite+=2;
            cout << "Ai nimerit\n";
        }

        nrMutari++;
        listaMutari -> primaC = primaCarte;
        listaMutari -> adouaC = aDouaCarte;
        listaMutari -> urm = new mutariJucator;
        listaMutari = listaMutari -> urm;

        cout<<"Introduceti orice tasta pentru a continua";
        getch();

        if(cartonaseNimerite == dimMatriceJoc * dimMatriceJoc)
            break;
    }

    listaMutari -> urm = NULL;
    system("cls");

    clock_t finish = clock();
    secunde = (finish - start) / CLOCKS_PER_SEC;

    cout << "Bravo! Ai castigat!\n";
    cout << "Ai rezolvat in:" << secunde << " Secunde" << '\n';
    cout << "Ai folosit doar:" << nrMutari << " Mutari" << '\n';

    cout << "Doriti sa vedeti mutarile? Apasati tasta 1." << '\n';
    int Raspuns;
    Raspuns = getch() - 48;
    if(Raspuns == 1)
    {
        listaMutari = listaMutariStart;
        while(listaMutari->urm != NULL)
        {
            cout << listaMutari->primaC << ' ' << listaMutari->adouaC << '\n';
            listaMutari = listaMutari -> urm;
        }
    }
    return 0;
}

