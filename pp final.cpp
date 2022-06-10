#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>

using namespace std;

struct data
{
    int zi;
    int luna;
    int an;
    int oi;
    int os;
};

class masa{
    int capacitate;
    int rezervata;
    struct data timp_rezervare;

    public:
    masa(){}
    masa(int c,int r, struct data tr){
     this->capacitate=c;
     this->rezervata=r;
     this->timp_rezervare=tr;
    }
    int getCap(){
     return capacitate;
    }
    int getRez(){
     return rezervata;
    }
    void setRez(int x){
        rezervata = x;
    }
    struct data getTR(){
     return timp_rezervare;
    }
    void setTR(struct data tire)
    {
        timp_rezervare=tire;
    }
};

    void append(vector<masa> &l, int capacitate,int disponibilitate,struct data tire)
{
    struct data tr;
    tr.zi=0;
         tr.luna=0;
          tr.an=0;
           tr.oi=0;
            tr.os=0;
    if(disponibilitate==1)
        tr=tire;
    masa masa_new(capacitate,disponibilitate,tr);
    l.push_back(masa_new);
}
void print(vector<masa>&l)
{
    int ok=0;
    int ex=0;
   for (vector<masa>::iterator it = l.begin(); it != l.end(); it++)
    {
    cout<<"id masa: "<<ok<<" "<<"Capacitate: "<<(*it).getCap()<<" "<<"Stare Rezervare: "<<(*it).getRez()<<endl;
     ex=1;
     ok++;
    }
    if(ex==0)
        cout<<"Nu exista mese"<<endl;
}
void print_rezervari(vector<masa>&l)
{
    int ok=0;
    int ex=0;
   for (vector<masa>::iterator it = l.begin(); it != l.end(); it++)
   {
    if((*it).getRez()==1)
    {
    cout<<"id masa: "<<ok<<" "<<"Capacitate: "<<(*it).getCap()<<endl;
      cout<<"Perioada rezervare:"<<(*it).getTR().zi<<"/"<<(*it).getTR().luna<<"/"<<(*it).getTR().an<<" "<<(*it).getTR().oi<<"-"<<(*it).getTR().os<<endl;
      ex=1;
    }
    ok++;
   }
   if(ex==0)
    cout<<"Nu exista rezervari"<<endl;
}
void remove_masa(vector<masa>&l,int capacitate,int rezervata)
{
    int i=0;
    for (vector<masa>::iterator it = l.begin(); it != l.end(); it++)
    {
        if((*it).getRez()==rezervata && (*it).getCap()==capacitate)
        {
            l.erase(l.begin()+i);
            break;
        }
        i++;
    }
}
void cautare_masa(vector<masa>&l,int capacitate,int disponibilitate)
{
    int ok=0;
    int ex=0;
    for (vector<masa>::iterator it = l.begin(); it != l.end(); it++)
     {
       if((*it).getRez()==disponibilitate && (*it).getCap()==capacitate)
    {
       cout<<"id masa:"<<ok<<" "<<(*it).getCap()<<" "<<(*it).getRez()<<endl;
       ex=1;
    }
    ok++;
     }
    if(ex==0)
        cout<<"Nu a fost gasita nicio masa cu aceste caracteristici.\n";
}
int comp_data(masa m, int zi,int luna,int an,int oi,int os)
{
    struct data tr = m.getTR();
    if(tr.an==an)
        if(tr.luna==luna)
            if(tr.zi==zi)
                if(os>tr.oi || oi<tr.os)
                    return 0;
    return 1;
}
void rezervare_masa(vector<masa>&l,int capacitate,int zi, int luna,int an,int oi,int os)
{
    int ok=0;
    for (vector<masa>::iterator it = l.begin(); it != l.end(); it++)
       {
           struct data tr;
           if((*it).getCap()==capacitate)
        {
            if((*it).getRez()==0)
            {
                ok=1;
                tr.zi=zi;
                tr.luna=luna;
                tr.an=an;
                tr.oi=oi;
                tr.os=os;
                (*it).setTR(tr);
                (*it).setRez(1);
            }
        }
        if(ok==1)
        {
            cout<<"Masa a fost rezervata.\n";
            break;
        }
       }
    if(ok==0)
        cout<<"Nu a fost gasita nicio masa disponibila cu capacitatea dorita.\n";
}
void anulare_rezervare(vector<masa>&l,int capacitate,int zi,int luna,int an,int oi,int os)
{

    int ok=0;
   for (vector<masa>::iterator it = l.begin(); it != l.end(); it++)
    {
        struct data tr;
        struct data d;
        d=(*it).getTR();
        if( (*it).getCap()==capacitate && (*it).getRez()==1 && d.zi==zi &&  d.luna==luna &&  d.an==an &&  d.oi==oi &&  d.os==os)
        {
            ok=1;
             (*it).setRez(0);
             tr.zi=0;
             tr.luna=0;
             tr.an=0;
             tr.oi=0;
             tr.os=0;
             (*it).setTR(tr);
            cout<<"Rezervarea a fost anulata.\n";
        }
        if(ok==1)
            break;
    }
    if(ok==0)
        cout<<"Nu exista nicio rezervare pentru acest tip de masa sau pentru aceasta data.\n";
}
int main()
{
     int n;
    int x;
    int k;
    int oc;
    int zi;
    int luna;
    int an;
    char *ptr;
    int oi;
    int os;
    int ok;
    struct data tr;
    vector<masa> pepe;
   ifstream f("mese.txt");
    char line[50];
    char line2[50];
    char line3[50];
    char line4[50];
    char line5[50];
    while (f.getline(line,50))
    {
        if(strlen(line)>1)
        {
            string cuv;
            ptr=strtok(line," ");
            x=atoi(ptr);
            ptr=strtok(NULL," ");
            oc=atoi(ptr);
            if(oc==1)
            {
                ptr=strtok(NULL," ");
                zi=atoi(ptr);
                ptr=strtok(NULL," ");
                luna=atoi(ptr);
                ptr=strtok(NULL," ");
                an=atoi(ptr);
                ptr=strtok(NULL," ");
                oi=atoi(ptr);
                ptr=strtok(NULL," ");
                os=atoi(ptr);
                    tr.zi=zi;
                    tr.luna=luna;
                    tr.an=an;
                    tr.oi=oi;
                    tr.os=os;
            }
            masa new_masa =masa(x,oc,tr);
            pepe.push_back(new_masa);
          }
    }
    f.close();
    cout<<"Buna ziua, va putem ajuta cu ceva?\n";
    cout<<"Introduceti 1 pentru DA sau 0 pentru NU\n";
    cin>>n;
    if(n==1)
    {
        cout<<"\n1.Doresc sa adaug o masa\n";
        cout<<"2.Doresc sa elimin o masa\n";
        cout<<"3.Sa vad toate mesele\n";
        cout<<"4.Sa vad toate rezervarile\n";
        cout<<"5.Sa caut o masa\n";
        cout<<"6.Sa rezerv o masa\n";
        cout<<"7.Sa anulez o rezervare\n";
        cout<<"Introduceti numarul pentru varianta dorita\n\n";
        cin>>k;
        cout<<"\n";
    }
    else
        cout<<"La revedere!";
    while(n!=0)
    {
        switch(k)
        {
        case 1:
            cout<<"Introduceti capacitatea mesei pe care doriti sa o adaugati si 0 daca este disponibila sau 1 daca nu este disponibila:\n";
            cin.ignore();
            cin.getline(line2,50);
            ptr=strtok(line2," ");
            x=atoi(ptr);
            ptr=strtok(NULL," ");
            oc=atoi(ptr);
            if(oc==1)
            {
                cout<<"Introduceti data in formatul DD MM YYYY urmata de ora de inceput si ora de sfarsit a rezervarii\n";
                cin.getline(line3, 50);
                ptr=strtok(line3," ");
                tr.zi=atoi(ptr);
                ptr=strtok(NULL," ");
                tr.luna=atoi(ptr);
                ptr=strtok(NULL," ");
                tr.an=atoi(ptr);
                ptr=strtok(NULL," ");
                tr.oi=atoi(ptr);
                ptr=strtok(NULL," ");
                tr.os=atoi(ptr);
                if(tr.zi>30 || tr.luna >12 ||tr.an<2022 || tr.oi<0||tr.os>24||tr.os<0||tr.oi>24 || tr.oi>os)
                    {cout<<"Eroare:ati introdus data sau ora gresit.\n";

                    }
                    else
                    append(pepe,x,oc,tr);

            }
            else
            {
                tr.zi=0;
                tr.luna=0;
                tr.an=0;
                tr.oi=0;
                tr.os=0;
                append(pepe,x,oc,tr);
            }
            cout<<"Masa a fost adaugata.\n";
            break;

        case 2:
            cout<<"Introduceti capacitatea mesei pe care doriti sa o stergeti si starea de rezervare a acesteia:\n";
            cin>>x>>ok;
            remove_masa(pepe,x,ok);
            cout<<"Masa a fost eliminata.\n";
            break;

        case 3:
            print(pepe);
            break;

        case 4:
            print_rezervari(pepe);
            break;
        case 5:
            cout<<"Introduceti capacitatea mesei pe care doriti sa o cautati si disponibilitatea:\n";
            cin>>x>>ok;
            cautare_masa(pepe,x,oc);
            break;
        case 6:
            cout<<"Introduceti capacitatea mesei pe care doriti sa o rezervati urmata de data in formatul DD MM YYYY si ora de inceput si de sfarsit(doar ore fixe)\n";
            cin.ignore();
            cin.getline(line4,50);
            ptr=strtok(line4," ");
            x=atoi(ptr);
            ptr=strtok(NULL," ");
            zi=atoi(ptr);
            ptr=strtok(NULL," ");
            luna=atoi(ptr);
            ptr=strtok(NULL," ");
            an=atoi(ptr);
            ptr=strtok(NULL," ");
            oi=atoi(ptr);
            ptr=strtok(NULL," ");
            os=atoi(ptr);
            if(zi>30 || luna >12 ||an<2022 || oi<0||os>24||os<0||oi>24 || oi>os)
                cout<<"Eroare:ati introdus data sau ora gresit.\n";
            else
                rezervare_masa(pepe,x,zi,luna,an,oi,os);
            break;
        case 7:
            cout<<"Introduceti capacitatea mesei pentru care doriti sa anulati rezervarea urmata de data in formatul DD MM YYYY iar mai apoi ora de inceput si de sfarsit a rezervarii(doar ore fixe)\n";
            cin.ignore();
            cin.getline(line5,50);
            ptr=strtok(line5," ");
            x=atoi(ptr);
            ptr=strtok(NULL," ");
            zi=atoi(ptr);
            ptr=strtok(NULL," ");
            luna=atoi(ptr);
            ptr=strtok(NULL," ");
            an=atoi(ptr);
            ptr=strtok(NULL," ");
            oi=atoi(ptr);
            ptr=strtok(NULL," ");
            os=atoi(ptr);
            if(zi>30 || luna >12 ||an<2022 || oi<0||os>24||os<0||oi>24 || oi>os)
                cout<<"Eroare:ati introdus data sau ora gresit.\n";
            else
                anulare_rezervare(pepe,x,zi,luna,an,oi,os);
            break;
        default:
            cout<<"Raspunsul introdus nu este un numar\n";
        }
        cout<<"\n1.Doresc sa adaug o masa\n";
        cout<<"2.Doresc sa elimin o masa\n";
        cout<<"3.Sa vad toate mesele\n";
        cout<<"4.Sa vad toate rezervarile\n";
        cout<<"5.Sa caut o masa\n";
        cout<<"6.Sa rezerv o masa\n";
        cout<<"7.Sa anulez o rezervare\n";
        cout<<"\nIntroduceti 1 pentru a continua sau 0 pentru a iesi.\n";
        cin>>n;
        if(n==1)
        {
            cout<<"Introduceti numarul pentru varianta dorita\n";
            cin>>k;
        }
        else
            cout<<"La revedere!";
    }
    ofstream g("mese.txt");
    ok=0;
    for (vector<masa>::iterator it = pepe.begin(); it != pepe.end(); it++)
    {
      ok++;
      tr=(*it).getTR();
      g<<(*it).getCap()<<" "<<(*it).getRez()<<" "<<tr.zi<<" "<<tr.luna<<" "<<tr.an<<" "<<tr.oi<<" "<<tr.os<<endl;
    }
    g.close();
    return 0;
}
