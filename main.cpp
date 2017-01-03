#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

using namespace std;

void afisaretablejoc(int matricejoc[50][50], int dim, int viz[50][50])
{
    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j < dim; j++)
            if(viz[i][j] == 0) cout << "@ ";
            else cout << (char)(matricejoc[i][j]+150) << " ";//v[matricejoc[i][j]
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
        cout<<"Press any key to continue";
        getch();
        system("cls"); // sterge tot ce am scris
        cout<<"Alege dificultatea jocului: \n";
        cout<<"Pentru nivel usor apasati tasta 1 \n";
        cout<<"Pentru nivel mediu apasati tasta 2 \n";
        cout<<"Pentru nivel greu apasati tasta 3 \n";
        cin >> nivelJoc;
    }
    system("cls");
    int dim, MaxMutari, MaxTimp;
    if(nivelJoc == 1)
    {
        dim = 2;
        MaxMutari = 10;
        MaxTimp = 20;
    }
    else if(nivelJoc == 2)
    {
        dim = 4;
        MaxMutari = 30;
        MaxTimp = 120;
    }
    else
    {
        dim = 6;
        MaxMutari = 100;
        MaxTimp = 600;
    }
    srand(time(NULL)); // initializeaza rand
    int v[200], matricejoc[50][50], viz[50][50];
    memset(v, 0, sizeof(v));

    for(int i = 0; i < dim; i++)
        for(int j = 0; j < dim; j++)
        {
            int nrcarte = rand() % (dim * dim / 2) + 1;
            while(v[nrcarte] == 2) nrcarte = rand() % (dim * dim / 2) + 1;
            matricejoc[i][j] = nrcarte;
            viz[i][j] = 0;
            v[nrcarte]++;
        }

    int nimerite = 0, NrMutari = 0, Secunde = 0;

    clock_t start = clock();

    while(1)
    {
        system("cls");

        clock_t temp = clock();
        int mutari = MaxMutari - NrMutari, timp = MaxTimp - (temp - start) / CLOCKS_PER_SEC;
        if(mutari <= 0 || timp <= 0)
        {
            cout << "Ai ramas fara timp sau fara mutari, Ai pierdut!\n";
            return 0;
        }
        cout << "Mai ai:" << timp << " secunde\n";
        cout << "Mai ai:" << mutari << " mutari\n";
        afisaretablejoc(matricejoc, dim, viz);


        cout << "Introdu Coordonate Prima Carte:\n";
        int xs, ys;
        cin >> xs >> ys;
        xs--;
        ys--;
        if(viz[xs][ys] != 0 || xs < 0 || xs >= dim || ys < 0 || ys >= dim)
        {
            cout << "Eroare! Cartea a mai fost aleasa o data sau e in afara matrice de joc!";
            cout<<"Press any key to continue";
            getch(); //il pune sa apese o tasta
            continue; // il duce inapoi in while
        }
        system("cls");
        viz[xs][ys] = 1;
        afisaretablejoc(matricejoc, dim, viz);


        cout << "Introdu Coordonate A doua Carte:\n";
        int xf,yf;
        cin >> xf >> yf;
        xf--;
        yf--;
        if(viz[xf][yf] != 0 || xf < 0 || xf >= dim || yf < 0 || yf >= dim)
        {
            viz[xs][ys] = 0;
            cout << "Eroare! Cartea a mai fost aleasa o data sau e in afara matricei de joc!";
            cout<<"Press any key to continue";
            getch();
            continue;
        }
        system("cls");
        viz[xf][yf] = 1;
        afisaretablejoc(matricejoc, dim, viz);

        if(matricejoc[xs][ys] != matricejoc[xf][yf])
        {
            viz[xs][ys] = 0;
            viz[xf][yf] = 0;
            cout << "Nu ai nimerit\n";
        }
        else
        {
            nimerite+=2;
            cout << "Ai nimerit\n";
        }

        NrMutari++;
        cout<<"Press any key to continue";
        getch();

        if(nimerite == dim * dim) break;
    }

    system("cls");

    clock_t finish = clock();
    Secunde = (finish - start) / CLOCKS_PER_SEC;

    cout << "Bravo Ai Castigat\n";
    cout << "Ai rezolvat in:" << Secunde << " Secunde" << '\n';
    cout << "Ai folosit doar:" << NrMutari << " Mutari" << '\n';

    return 0;
}
