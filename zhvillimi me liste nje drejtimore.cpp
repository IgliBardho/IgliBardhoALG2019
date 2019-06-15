#include <iostream>
#include <fstream>

using namespace std;

string korrigjoString(string str){
    string stringuIKorrigjuar = "";
    unsigned int j;
    for(j = 0; j < str.length(); j++){
        if((str.at(j) >= 'A' && str.at(j) <= 'Z') ||
           (str.at(j) >= 'a' && str.at(j) <= 'z')){
            stringuIKorrigjuar = stringuIKorrigjuar + str.at(j);
        }
    }
    return stringuIKorrigjuar;
}

struct elementListe1D{
    string info;
    elementListe1D *iRadhes;
};

elementListe1D* rezervoElement1D(string info){
    elementListe1D *elementIRi = new elementListe1D;
    if(elementIRi != NULL){
        elementIRi->info = info;
        elementIRi->iRadhes = NULL;
    }
    return elementIRi;
}

elementListe1D* shtoElementNeListe(
                    elementListe1D *iPari,
                    string info){
    if(iPari == NULL){
        return rezervoElement1D(info);
    }
    if(info.compare(iPari->info) < 0){
        elementListe1D *elementIRi =
            rezervoElement1D(info);
        if(elementIRi != NULL){
            elementIRi->iRadhes = iPari;
            iPari = elementIRi;
        }
        return iPari;
    }
    if(info.compare(iPari->info) == 0){
        return iPari;
    }
    elementListe1D *shetites = iPari;
    while(shetites->iRadhes != NULL &&
          (info.compare(shetites->iRadhes->info) > 0)){
        shetites = shetites->iRadhes;
    }
    if(shetites->iRadhes != NULL &&
       (info.compare(shetites->iRadhes->info) == 0)){
        return iPari;
    }
    elementListe1D *elementIRi = rezervoElement1D(info);
    if(elementIRi == NULL){
        return iPari;
    }
    elementIRi->iRadhes = shetites->iRadhes;
    shetites->iRadhes = elementIRi;
    return iPari;
}

void afishoListe(elementListe1D *iPari){
    if(iPari == NULL){
        cout<<"Lista eshte bosh!";
        return;
    }
    elementListe1D *shetites = iPari;
    while(shetites != NULL){
        cout<<shetites->info<<"\n";
        shetites = shetites->iRadhes;
    }
}

void shkruajFjalorNeSkedar(elementListe1D *iPari){
    if(iPari == NULL){
        return;
    }
    ofstream outputNeSkedar;
    outputNeSkedar.open("fjalor.txt");
    if(!outputNeSkedar.is_open()){
        return;
    }
    elementListe1D *shetites = iPari;
    while(shetites != NULL){
        outputNeSkedar<<shetites->info<<"\n";
        shetites = shetites->iRadhes;
    }
    outputNeSkedar.close();
}

void fshiListe(elementListe1D *iPari){
    while(iPari != NULL){
        elementListe1D *tmp = iPari;
        iPari = iPari->iRadhes;
        delete(tmp);
    }
}

int main()
{
    elementListe1D *iPari = NULL;
    ifstream inputNgaSkedari;
    inputNgaSkedari.open("1000000.txt");
    if(!inputNgaSkedari.is_open()){
        cout<<"Deshtoi hapja e skedarit!";
        return 1;
    }
    while(!inputNgaSkedari.eof()){
        string str;
        inputNgaSkedari>>str;
        iPari = shtoElementNeListe(iPari,
                    korrigjoString(str));
    }
    inputNgaSkedari.close();
    shkruajFjalorNeSkedar(iPari);
    fshiListe(iPari);
    return 0;
}
