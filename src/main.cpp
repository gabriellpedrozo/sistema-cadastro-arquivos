#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int cap = 40, pos = 0; // capacidade e posição

struct EspecieMarinha { //Struct principal 
    int id;
    string nomeComum;
    string nomeCientifico;
    string habitat;
    float tamanhoMedio;
    bool removido = false;  //REMOÇÃO LÓGICA ((false = ativo no sistema) (true = removido (não aparece mais nas listagens)))
};

int main(){
    
    ifstream arq("especies.csv"); // abre o arquivo pra leitura

    string cabecalho;
    getline(arq, cabecalho);// le e descarta a priemira linha 

    EspecieMarinha* p = new EspecieMarinha[cap]; //aloca dinamicamente o vetor com capacidade de 40(lá em cima cap = 40)
    
    while(arq >> p[pos].id){
        arq.ignore(); //ignora a virgula depois de id

        getline(arq, p[pos].nomeComum, ';'); //le ate a proxima virgula
        getline(arq, p[pos].nomeCientifico, ';'); // ""
        getline(arq, p[pos].habitat, ';'); // ""

        arq >> p[pos].tamanhoMedio; // lê o float (último da linha)
        arq.ignore();               // ignora o 'endl' para ir para próxima linha

        p[pos].removido = false; //deixa que o registro lido começa ativo

        pos++; //avança posição

        if(pos >= cap) {
            EspecieMarinha* novo = new EspecieMarinha [cap + 10];

            for(int i = 0; i < pos; i++)
            novo[i] = p[i];//copia tudo  pro novo veto

            delete[]p;// libera o vetor antigo da memoria
            p = novo;// p aponta pro novo
            cap += 10; // atualiza a capacidade
        }
    }
    delete[]p; //libera memoria pra finalizar 
    return 0;
}