#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>


using namespace std;

void afisareTableJoc(int matriceJoc[][50], int dimMatriceJoc, int vizitat[][50])
{
    for(int linie = 0; linie < dimMatriceJoc; linie++)
    {
        for(int coloana = 0; coloana < dimMatriceJoc; coloana++)
            if(vizitat[linie][coloana] == 0) cout << "@ ";
            else cout << (char)(matriceJoc[linie][coloana]+150) << " ";
        cout << "\n";
    }
}

int main()
{
    int nivelJoc;
    cout<<"Alege dificultatea jocului: \n";
    cout<<"Pentru nivel usor apasati tasta 1 \n";
    cout<<"Pentru nivel mediu apasati tasta 2 \n";
    cout<<"Pentru nivel greu apasati tasta 3 \n";
    cin>>nivelJoc;
    while(nivelJoc!= 1 && nivelJoc!= 2 && nivelJoc!=3)
    {
        cout<<"Valoare introdusa nu exista. Eroare.\n";
        cout<<"Introduceti orice tasta pentru a continua";
        getch();
        system("cls"); // sterge tot ce am scris
        cout<<"Alege dificultatea jocului: \n";
        cout<<"Pentru nivel usor apasati tasta 1 \n";
        cout<<"Pentru nivel mediu apasati tasta 2 \n";
        cout<<"Pentru nivel greu apasati tasta 3 \n";
        cin >> nivelJoc;
    }
    system("cls");
    int dimMatriceJoc, maxMutari, maxTimp;
    if(nivelJoc == 1)
    {
        dimMatriceJoc = 2;
        maxMutari = 10;
        maxTimp = 30;
    }
    else if(nivelJoc == 2)
    {
        dimMatriceJoc = 4;
        maxMutari = 30;

        maxTimp = 160;
    }
    else
    {
        dimMatriceJoc = 6;
        maxMutari = 100;
        maxTimp = 660;
    }
    srand(time(NULL));
    int v[200], matriceJoc[50][50], vizitat[50][50];
    memset(v, 0, sizeof(v));

    for(int linie = 0; linie < dimMatriceJoc; linie++)
        for(int coloana = 0; coloana < dimMatriceJoc; coloana++)
        {
            int nrCarte = rand() % (dimMatriceJoc * dimMatriceJoc / 2) + 1;
            while(v[nrCarte] == 2)
                nrCarte = rand() % (dimMatriceJoc * dimMatriceJoc / 2) + 1;
            matriceJoc[linie][coloana] = nrCarte;
            vizitat[linie][coloana] = 0;
            v[nrCarte]++;
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
            cout << "Ai ramas fara timp sau fara mutari. Ai pierdut!\n";
            return 0;
        }
        if(timp <= 0)
        {
            cout<< "Ai ramas fara timp. Ai pierdut!\n";
            return 0;
        }
        cout << "Mai ai:" << timp << " secunde\n";
        cout << "Mai ai:" << mutari << " mutari\n";
        afisareTableJoc(matriceJoc, dimMatriceJoc, vizitat);


        cout << "Introduceti coordonate Prima Carte:\n";
        int xs, ys;
        cin >> xs >> ys;
        xs--;
        ys--;
        if(vizitat[xs][ys] != 0 || xs < 0 || xs >= dimMatriceJoc || ys < 0 || ys >= dimMatriceJoc)
        {
            cout << "Eroare! Cartea a mai fost aleasa o data sau e in afara matrice de joc!";
            cout<<"Introduceti orice tasta pentru a continua";
            getch(); //il pune sa apese o tasta
            continue; // il duce inapoi in while
        }
        system("cls");
        vizitat[xs][ys] = 1;
        afisareTableJoc(matriceJoc, dimMatriceJoc, vizitat);


        cout << "Introdu Coordonate A doua Carte:\n";
        int xf,yf;
        cin >> xf >> yf;
        xf--;
        yf--;
        if(vizitat[xf][yf] != 0 || xf < 0 || xf >= dimMatriceJoc || yf < 0 || yf >= dimMatriceJoc)
        {
            vizitat[xs][ys] = 0;
            cout << "Eroare! Cartea a mai fost aleasa o data sau e in afara matricei de joc!";
            cout<<"Introduceti orice tasta pentru a continua";
            getch();
            continue;
        }
        system("cls");
        vizitat[xf][yf] = 1;
        afisareTableJoc(matriceJoc, dimMatriceJoc, vizitat);

        if(matriceJoc[xs][ys] != matriceJoc[xf][yf])
        {
            vizitat[xs][ys] = 0;
            vizitat[xf][yf] = 0;
            cout << "Nu ai nimerit\n";
        }
        else
        {
            cartonaseNimerite+=2;
            cout << "Ai nimerit!\n";
        }

        nrMutari++;
        cout<<"Introduceti orice tasta pentru a continua";
        getch();

        if(cartonaseNimerite == dimMatriceJoc * dimMatriceJoc)
            break;
    }

    system("cls");

    clock_t finish = clock();
    secunde = (finish - start) / CLOCKS_PER_SEC;

    cout << "Bravo! Ai Castigat\n";
    cout << "Ai rezolvat in:" << secunde << " Secunde" << '\n';
    cout << "Ai folosit doar:" << nrMutari << " Mutari" << '\n';

    return 0;
}
