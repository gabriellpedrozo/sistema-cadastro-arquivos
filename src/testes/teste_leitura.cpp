#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct EspecieMarinha {
    int id;
    string nomeComum;
    string nomeCientifico;
    string habitat;
    float tamanhoMedio;
    bool removido = false;
};

int main(){

    ifstream arq("../dados/especies.csv");

    if(!arq){
        cout << "Erro ao abrir arquivo!" << endl;
        return 1;
    }

    cout << "Arquivo abriu com sucesso!" << endl;

    string cabecalho;

    getline(arq, cabecalho);

    cout << "Cabecalho encontrado:" << endl;
    cout << cabecalho << endl;


    EspecieMarinha especie;

    int contador = 0;


    while(arq >> especie.id){

        arq.ignore();

        getline(arq, especie.nomeComum, ';');
        getline(arq, especie.nomeCientifico, ';');
        getline(arq, especie.habitat, ';');

        arq >> especie.tamanhoMedio;

        arq.ignore();


        cout << "\nRegistro encontrado:" << endl;
        cout << "ID: " << especie.id << endl;
        cout << "Nome: " << especie.nomeComum << endl;
        cout << "Cientifico: " << especie.nomeCientifico << endl;
        cout << "Habitat: " << especie.habitat << endl;
        cout << "Tamanho: " << especie.tamanhoMedio << endl;


        contador++;
    }


    cout << "\nQuantidade carregada: " << contador << endl;


    return 0;
}