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

struct elementPemeBinare{
    string info;
    elementPemeBinare *iMajte, *iDjathte;
};

elementPemeBinare* rezervoElementPB(string info){
    elementPemeBinare *elementIRi = new elementPemeBinare;
    if(elementIRi != NULL){
        elementIRi->info = info;
        elementIRi->iMajte = NULL;
        elementIRi->iDjathte = NULL;
    }
    return elementIRi;
}

void shtoElementNePeme(elementPemeBinare** rrenja,
                       string info){
    if(*rrenja == NULL){
        *rrenja = rezervoElementPB(info);
    }
    else if(info.compare((*rrenja)->info) < 0){
        shtoElementNePeme(&(*rrenja)->iMajte, info);
    }
    else if(info.compare((*rrenja)->info) > 0){
        shtoElementNePeme(&(*rrenja)->iDjathte, info);
    }
}

void shkruajFjalorNeSkedar(/*ofstream outputNeSkedar,*/
                           elementPemeBinare *rrenja){
    if(rrenja == NULL){
        return;
    }
    shkruajFjalorNeSkedar(/*outputNeSkedar,*/ rrenja->iMajte);
    /*outputNeSkedar*///cout<<rrenja->info<<"\n";
    shkruajFjalorNeSkedar(/*outputNeSkedar, */
                          rrenja->iDjathte);
}

void fshiPeme(elementPemeBinare **rrenja){
    if(*rrenja == NULL){
        return;
    }
    if((*rrenja)->iMajte != NULL){
        fshiPeme(&(*rrenja)->iMajte);
    }
    if((*rrenja)->iMajte != NULL){
        fshiPeme(&(*rrenja)->iDjathte);
    }
    delete(*rrenja);
    *rrenja = NULL;
}

void ngaPemaNeVektor(elementPemeBinare *rrenja,
                     string info[],
                     int *i){
    if(rrenja == NULL){
        return;
    }
    if(rrenja->iMajte != NULL){
        ngaPemaNeVektor(rrenja->iMajte, info, i);
    }
    info[*i] = rrenja->info;
    *i = *i + 1;
    if(rrenja->iDjathte != NULL){
        ngaPemaNeVektor(rrenja->iDjathte, info, i);
    }
}

void ngaVektorNePeme(elementPemeBinare **rrenja,
                     int nrElementeve,
                     string info[]){
     if(nrElementeve == 0){
        return;
     }
     *rrenja = rezervoElementPB(info[nrElementeve/2]);
     if(rrenja == NULL){
        return;
     }
     ngaVektorNePeme(&(*rrenja)->iMajte, nrElementeve / 4, info);
     ngaVektorNePeme(&(*rrenja)->iDjathte, 3*nrElementeve / 4, info);
}

void balanco(elementPemeBinare **rrenja){
    if(*rrenja == NULL){
        return;
    }
    string info[100000];
    int nrElementeve = 0;
    ngaPemaNeVektor(*rrenja, info, &nrElementeve);
    ngaVektorNePeme(rrenja, nrElementeve, info);
}

int main()
{
    elementPemeBinare *rrenja = NULL;
    ifstream inputNgaSkedari;
    inputNgaSkedari.open("100000.txt");
    if(!inputNgaSkedari.is_open()){
        cout<<"Deshtoi hapja e skedarit!";
        return 1;
    }
    int nrElementeve = 0;
    while(!inputNgaSkedari.eof()){
        string str;
        inputNgaSkedari>>str;
        shtoElementNePeme(&rrenja, korrigjoString(str));
        nrElementeve++;
        if(nrElementeve % 20 == 0){
            balanco(&rrenja);
        }
    }
    inputNgaSkedari.close();
    ofstream outputNeSkedar;
    outputNeSkedar.open("fjalor.txt");
    if(!outputNeSkedar.is_open()){
        return 2;
    }
    shkruajFjalorNeSkedar(/*outputNeSkedar,*/ rrenja);
    outputNeSkedar.close();
    fshiPeme(&rrenja);
    return 0;
}
