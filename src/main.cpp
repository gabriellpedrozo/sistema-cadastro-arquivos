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

void listar(EspecieMarinha v[]){

    cout << endl;
    cout << "--- LISTAGEM DE ESPECIES ---" << endl;
    
    bool alguma = false; // controla pra ver se tem alguma especie ativa 
    
    for(int i = 0; i < pos; i++){
        if(v[i].removido == false){ // so exibe se não estiver removido 
            alguma = true;
            cout << endl << "#" << i + 1 << endl;
            cout << "ID: " << v[i].id << endl;
            cout << "Nome comum: " << v[i].nomeComum << endl;
            cout << "Nome cientifico: " << v[i].nomeCientifico << endl;
            cout << "Habitat: "         << v[i].habitat << endl;
            cout << "Tamanho medio: "   << v[i].tamanhoMedio << " m" << endl;
        }
    }

    if(!alguma){
        cout << "Nenhuma especie cadastrada." << endl;
    }
}

void inserir(EspecieMarinha *&v){ // adiciona item novo manualmente 
    EspecieMarinha nova;

    cout << "Digite o ID: ";
    cin >> nova.id;
    cin.ignore(); // tira um espaço que tava dando b.o aq 

    cout<< "Digite o nome comum: ";
    getline(cin, nova.nomeComum);

    cout << "Digite o nome cientifico: ";
    getline(cin, nova.nomeCientifico);

    cout << "Digite o habitat: ";
    getline(cin, nova.habitat);

    cout << "Digite o tamanho medio (cm): ";
    cin >> nova.tamanhoMedio;

    nova.removido = false; //a especie nova começa ativa

    if (pos >= cap) { // redimensiona se precisar
        EspecieMarinha* aux = new EspecieMarinha[cap + 10];
        for (int i = 0; i < pos; i++)
            aux[i] = v[i];
        delete[] v;
        v = aux;
        cap += 10;
    }

    v[pos] = nova; //guarda a nova na posicao livre
    pos++; // avança posção
    
    cout << "Especie inserida com sucesso!" << endl;
}

void remover(EspecieMarinha v[]){
    int id;
    cout << "Digite o ID da especie a ser removida: ";
    cin >> id;

    bool achou = false;

    for(int i = 0; i < pos; i++){
        if(v[i].id == id and v[i].removido == false){
            v[i].removido = true; // marca como removido
            achou = true;
            cout << "Especie removida com sucesso!" << endl;
            break; //achou já, então sai 
        }
    }

    if(!achou){
        cout << "Especie nao encontrada ou ja removida." << endl;
    }
}

void ordenarPorId(EspecieMarinha v[]){

    for(int i = 1; i < pos; i++){
        EspecieMarinha temp = v[i]; // guarda o item atual numa variavel temporaria
        int j = i - 1;

        while(j >= 0 and v[j].id > temp.id){ // empurra os maiores pra direita, e deixa o espaço pra temporaria
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = temp; // coloca no lugar certo
    }
    cout << "Ordenado por ID com sucesso!" << endl;
}

void ordenarPorNome(EspecieMarinha v[]){

    for(int i = 1; i < pos; i++){
        EspecieMarinha temp = v[i]; // guarda o item atual numa variavel temporaria
        int j = i - 1;

        while(j >= 0 and v[j].nomeComum > temp.nomeComum){ // empurra os maiores pra direita, e deixa o espaço pra temporaria
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = temp; // coloca no lugar certo
    }
    cout << "Ordenado por nome com sucesso!" << endl;
}

void ordenarPorTamanho(EspecieMarinha v[]){
    for(int i = 0; i < pos - 1; i++){
        int maior = i; //pega o atual como maior por enquanto

        for(int j = i + 1; j < pos; j++){
            if(v[j].tamanhoMedio < v[maior].tamanhoMedio){ //menor pro maior 
                maior = j; //achou maior muda
            }
        }

        if(maior != i){ // troca se realmente for maior 
            EspecieMarinha temp = v[i];
            v[i] = v[maior];
            v[maior] = temp;
        }
    }
    cout << "Ordenado por tamanho com sucesso!" << endl;
}

void menuOrdenar(EspecieMarinha v[]){

    int opc;
    cout << endl;
    cout << "Ordenar por:" << endl;
    cout << "1 - ID" << endl;
    cout << "2 - Nome comum" << endl;
    cout << "3 - Tamanho medio" << endl;
    cout << "4 - Voltar" << endl;
    cin >> opc;

     if (opc == 1) {
        ordenarPorId(v);
    } else if (opc == 2) {
        ordenarPorNome(v);
    } else if (opc == 3) {
        ordenarPorTamanho(v);
    } else if (opc == 4) { // volta, não faz nada
    } else {
        cout << "Opcao invalida!" << endl;
    }

}

void buscarPorId(EspecieMarinha v[]){
    
    ordenarPorId(v);

    int id;
    cout << "Digite o Id da especie: ";
    cin >> id;

    int inicio = 0, fim = pos - 1, meio, posicao = -1;
    bool achou = false;
    
    while(inicio <= fim){
        meio = (inicio + fim) / 2;

        if(id == v[meio].id){
        posicao = meio;
        achou = true;
        inicio = meio + 1; // pra sair do loop
        }else if(id > v[meio].id){
            inicio = meio + 1; // o que procuro ta na direita
        }else {
            fim = meio - 1;// o que procuro ta na esquerda
        }
    }

    if (achou) {
        cout << "Posicao: #" << posicao + 1 << endl;
        cout << "Nome comum: " << v[posicao].nomeComum << endl;
        cout << "Nome cientifico: " << v[posicao].nomeCientifico << endl;
    } else {
        cout << "Nao existe especie com esse ID." << endl;
    }
}

void buscarPorTamanho(EspecieMarinha v[]) {
    ordenarPorTamanho(v); // garante que está ordenado por tamanho 
    float tamanho;
    cout << "Digite o tamanho medio da especie (cm): ";
    cin >> tamanho;

    int inicio = 0, fim = pos - 1, meio, posicao = -1;
    bool achou = false;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;

        if (tamanho == v[meio].tamanhoMedio) {
            posicao = meio;
            achou = true;
            inicio = fim + 1;
        }else if (tamanho > v[meio].tamanhoMedio) {
            inicio = meio + 1; //  maiores ficam a direita menor -> maior
        }else {
            fim = meio - 1; // valores menores ficam à esquerda
        }
    }

    if (achou) {
        cout << "Posicao: #" << posicao + 1 << endl;
        cout << "Nome comum: " << v[posicao].nomeComum << endl;
        cout << "ID: " << v[posicao].id << endl;
    } else {
        cout << "Nao existe especie com esse tamanho." << endl;
    }
}

void menuBuscar(EspecieMarinha v[]) {
    int opc;
    cout << endl;
    cout << "Buscar por:" << endl;
    cout << "1 - ID" << endl;
    cout << "2 - Tamanho medio" << endl;
    cout << "3 - Voltar" << endl;
    cin >> opc;

    if (opc == 1) {
        buscarPorId(v);
    }else if (opc == 2) {
        buscarPorTamanho(v);
    }else if (opc == 3) {// volta, não faz nada
    }else {
        cout << "Opcao invalida!" << endl;
    }
}

int exibirMenu() {
    int opcao;
    cout << endl;
    cout << "==== ESPECIES MARINHAS ====" << endl;
    cout << "0 - Sair" << endl;
    cout << "1 - Listar especies" << endl;
    cout << "2 - Inserir especie" << endl;
    cout << "3 - Remover especie" << endl;
    cout << "4 - Ordenar especies" << endl;
    cout << "5 - Buscar especie" << endl;
    cin >> opcao;
    return opcao;
}

void executarOpcao(int opcao, EspecieMarinha *&v) {
    if (opcao == 0) {
        cout << "Encerrando" << endl;
    } else if (opcao == 1) {
        listar(v);
    } else if (opcao == 2) {
        inserir(v);
    } else if(opcao == 3){
        remover(v);
    } else if (opcao == 4){
        menuOrdenar(v);
    }else if (opcao == 5){
        menuBuscar(v);
    }else {
        cout << "Opcao invalida!" << endl;
    }
}

int main(){
    
    ifstream arq("../dados/especies.csv"); // abre o arquivo pra leitura

    string cabecalho;
    getline(arq, cabecalho);// le e descarta a priemira linha 

    EspecieMarinha* especies = new EspecieMarinha[cap]; //aloca dinamicamente o vetor com capacidade de 40(lá em cima cap = 40)
    
    while(arq >> especies[pos].id){
        arq.ignore(); //ignora a virgula depois de id

        getline(arq, especies[pos].nomeComum, ';'); //le ate a proxima virgula
        getline(arq, especies[pos].nomeCientifico, ';'); // ""
        getline(arq, especies[pos].habitat, ';'); // ""

        arq >> especies[pos].tamanhoMedio; // lê o float (último da linha)
        arq.ignore(); // ignora o 'endl' para ir para próxima linha

        especies[pos].removido = false; //deixa que o registro lido começa ativo

        pos++; //avança posição

        if(pos >= cap) { 
            EspecieMarinha* novo = new EspecieMarinha [cap + 10];

            for(int i = 0; i < pos; i++)
            novo[i] = especies[i];//copia tudo  pro novo veto

            delete[]especies;// libera o vetor antigo da memoria
            especies = novo;// p aponta pro novo
            cap += 10; // atualiza a capacidade
        }
    }
        int opcao = -1;

        while(opcao != 0){
            opcao = exibirMenu();
            executarOpcao(opcao, especies);
        }

    delete[]especies; //libera memoria pra finalizar 
    return 0;
}