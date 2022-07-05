#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <conio.h>

using namespace std;

void intro();


const int maxPoprawnychOdpowiedzi = 3;
const int maxAktywnychPytan = 20;
int aktualnePytanie = 0;

struct slowko{
    string pytanie;
    string odpowiedz;
    int pkt;
    slowko(string o, string p)
    {
        pytanie = p;
        odpowiedz = o;
        pkt = 2;
    }
};

string dzielString(string tekst,char znak, int numer)
{
    string wynik;
    for(int x =0; x < tekst.size();x++)
    {
        if(tekst[x] == znak) numer--;
        else if(numer==0) wynik+=tekst[x];
    }
    return wynik;
}

vector<slowko> slowa;

void wczytywanie()
{
    intro();
    cout<<endl<<"k - kontynuacja"<<endl<<"o - od nowa";
    string nazwaPliku;
    char klaw = 'a';
    while(klaw != 'k' && klaw != 'o') klaw = getch();
    if(klaw == 'k') nazwaPliku = "kontynuacja.save";
    else nazwaPliku = "pytania.txt";


    fstream plik;
    string linia;
    plik.open(nazwaPliku.c_str(),ios::in);
    if(!plik.good())
    {
        cout<<"Nie mozna otworzyc pliku pytania.txt"<<endl;
        while(true);
    }
    while(!plik.eof())
    {
        getline(plik,linia);
        if(linia[0]!='#' && linia != "")
        {
            slowa.push_back(slowko(dzielString(linia,'@',0),dzielString(linia,'@',1)));
        }
    }
    plik.close();
}

void zapis()
{
    fstream plik;
    string linia;
    plik.open("kontynuacja.save",ios::out);
    if(plik.good())
    {
        plik<<"#Wygenerowano automatycznie"<<endl<<"#Plik nie zawiera pytan na ktore zostala"<<endl<<"#   udzielona odpowiednia ilosc poprawnych odpowiedzi pod rzad"<<endl;
        for(int x=0;x<slowa.size();x++)
        {
            plik<<slowa[x].odpowiedz<<"@"<<slowa[x].pytanie<<"@  pytanie nr "<<x<<endl;
        }
        getline(plik,linia);
        if(linia[0]!='#' && linia != "")
        {
            slowa.push_back(slowko(dzielString(linia,'@',0),dzielString(linia,'@',1)));
        }
    }
    plik.close();
}

void pytanie(int nr = -1)
{
    int pyt;
    if(nr == -1)
    {
        if(slowa.size() <= maxAktywnychPytan) pyt = rand()%(slowa.size());
        else pyt = rand()%(maxAktywnychPytan);
    }
    else pyt = nr;



    cout<<slowa[pyt].pytanie<<"  -  ";
    string odpowiedz;
    getline(cin,odpowiedz);
    if(odpowiedz != slowa[pyt].odpowiedz)
    {
        if(slowa[pyt].pkt >0) slowa[pyt].pkt--;
        cout<<"[ZLE] "<<slowa[pyt].pytanie<<"  -  "<<slowa[pyt].odpowiedz<<endl;
        pytanie(pyt);
    }
    else if(nr == -1)
    {
        slowa[pyt].pkt++;
        if(slowa[pyt].pkt >= maxPoprawnychOdpowiedzi)
        {
            slowa.erase(slowa.begin()+pyt);
            zapis();
        }

    }
}

void intro()
{
    cout<<"Created by Ernest Mezyk v2"<<endl;
    cout<<"------------------------------------------------"<<endl;
    fstream introConfig;
    string line;
    introConfig.open("intro.config",ios::in);
    if(introConfig.good())
        while(!introConfig.eof())
        {
            getline(introConfig,line);
            cout<<line<<endl;
        }
    introConfig.close();
    cout<<"------------------------------------------------"<<endl;
}

int main()
{
    srand(time(NULL));
    wczytywanie();
    intro();
    cout<<endl<<"--Zaladowano "<<slowa.size()<<" pytan--"<<endl<<endl;
    while(slowa.size()>0)
    {
        system("cls");
        intro();
        cout<<endl<<"-- Pozostalo: "<<slowa.size()<<" --"<<endl<<endl;
        pytanie();
    }
    system("cls");
    intro();
    cout<<endl<<"Gratulacje! Zakonczyles szkolenie. Uruchom ponownie by zaczac od poczatku"<<endl;
    while(true);

    return 0;
}
