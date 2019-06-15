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

int main()
{
    elementPemeBinare *rrenja = NULL;
    ifstream inputNgaSkedari;
    inputNgaSkedari.open("100.txt");
    if(!inputNgaSkedari.is_open()){
        cout<<"Deshtoi hapja e skedarit!";
        return 1;
    }
    while(!inputNgaSkedari.eof()){
        string str;
        inputNgaSkedari>>str;
        shtoElementNePeme(&rrenja, korrigjoString(str));
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
