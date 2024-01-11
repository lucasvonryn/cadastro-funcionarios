#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define max_funcionarios 50
#define meses 12
#define dias 31

int i, opcao, passou, retorno;
char entrada[50];

struct funcionario{
    int codigo;
    int ano;
    int flag;
    char nome[50];
    char cargo[40];
    float valor_hora;
    int horas_trabalhadas[meses][dias];
}funcionario[max_funcionarios];

// Inicializa todas as flags para 0, indicando local vago
void inicializaFlag(){
    for(i=0; i<max_funcionarios; i++)
        funcionario[i].flag = 0;
}

// Consulta um local vago e o retorna
int consultaPosicaoLivre(){
    for(i=0; i<max_funcionarios; i++){
        if(funcionario[i].flag == 0){
            return i;
        }
    }
    return -1;
}

// Valida e retorna se o mes existe ou nao
int validarMes(int mes){
    return (mes >= 1 && mes <= 12);
}

// Valida e retorna se o dia existe naquele mes ou nao
int validarDia(int mes, int dia){
    int diasPorMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (dia >= 1 && dia <= diasPorMes[mes - 1]);
}

// Valida e retorna se um numero e inteiro ou nao
int validarInteiro(char entrada[]){
    if(strlen(entrada) == 0){
        return 0;
    }
    for(i=0; i<strlen(entrada); i++){
        if(!isdigit(entrada[i])){
            return 0;
        }
    }
    return 1;
}

// Valida e retorna se um numero e float ou nao
int validarFloat(char entrada[]){
    if(strlen(entrada) == 0){
        return 0;
    }
    for(i=0; i<strlen(entrada); i++){
        if(!isdigit(entrada[i]) && entrada[i] != '.'){
            return 0;
        }
    }
    return 1;
}

// Valida e retorna se e uma string ou nao
int validarString(char entrada[]){
    if(strlen(entrada) > 0 && entrada[strlen(entrada) - 1] != '\0'){
        for(i=0; i<strlen(entrada); i++){
            if(!isalpha(entrada[i]) && entrada[i] != ' '){
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

// Recebe um mes e retorna quantos dias ele tem
int consultaDiasDoMes(int mes){
    int diasPorMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return diasPorMes[mes - 1];
}

// Faz a entrada do nome
int entradaNome(int posicao){
    printf("Nome: ");
    fflush(stdin);
    gets(entrada);

    if(validarString(entrada) == 1){
        strcpy(funcionario[posicao].nome, entrada);
        return 1;
    }else{
        printf("Nome invalido.\n");
        return 0;
    }
}

// Faz a entrada do ano
int entradaAno(int posicao){
    printf("Ano: ");
    fflush(stdin);
    gets(entrada);

    if(validarInteiro(entrada) == 1){
        funcionario[posicao].ano = atoi(entrada);
        return 1;
    }else{
        printf("Ano invalido.\n");
        return 0;
    }
}

// Faz a entrada do cargo
int entradaCargo(int posicao){
    printf("Cargo: ");
    fflush(stdin);
    gets(entrada);

    if(validarString(entrada) == 1){
        strcpy(funcionario[posicao].cargo, entrada);
        return 1;
    }else{
        printf("Cargo invalido.\n");
        return 0;
    }
}

// Faz a entrada do valor hora
int entradaValorHora(int posicao){
    printf("Valor hora: ");
    fflush(stdin);
    gets(entrada);

    if(validarFloat(entrada) == 1){
        funcionario[posicao].valor_hora = atof(entrada);
        return 1;
    }else{
        printf("Valor hora invalido.\n");
        return 0;
    }
}

// Salva os dados dos funcionarios
void salvarDados(){
    // Nao deu tempo :/
}

// Carrega os dados dos funcionarios
void carregarDados(){
    // Tambem nao deu tempo :/
}

// Cadastra novos funcionarios
void cadastrar(){
    int posicao = consultaPosicaoLivre();

    if(posicao != -1){
        funcionario[posicao].codigo = posicao + 1;
        printf("\nCODIGO: %d\n", funcionario[posicao].codigo);

        // Entrada dos dados
        // Nome
        do{
            retorno = entradaNome(posicao);
        }while(retorno == 0);

        // Ano
        do{
            retorno = entradaAno(posicao);
        }while(retorno == 0);

        // Cargo
        do{
            retorno = entradaCargo(posicao);
        }while(retorno == 0);

        // Valor hora
        do{
            retorno = entradaValorHora(posicao);
        }while(retorno == 0);

        funcionario[posicao].flag = 1;
        printf("Funcionario cadastrado com sucesso.\n\n");
    }else{
        printf("Nao ha posicao livre para cadastro.\n\n");
    }
}

// Insere a quantidade de horas trabalhadas durante certo dia
void inserirHorasTrabalhadas(){
    int mes, dia, horas, posicao, registro_existente;

    do{
        passou = 0;
        // Entrada do nome
        printf("\nDigite o nome do funcionario que deseja inserir horas de trabalho: ");
        fflush(stdin);
        gets(entrada);

        // Validacao de entrada
        if(validarString(entrada) == 0){
            printf("Entrada invalida.");
            continue;
        }
        passou = 1;
    }while(passou == 0);

    for(i=0; i<max_funcionarios; i++){
        if(strcmp(funcionario[i].nome, entrada) == 0 && funcionario[i].flag == 1){
            posicao = i;

            do{
                // Entrada do mes
                passou = 0;
                printf("Mes (1-12): ");
                fflush(stdin);
                gets(entrada);

                // Validacao do mes
                if(validarInteiro(entrada) == 1){
                    mes = atoi(entrada);
                    if(!validarMes(mes)){
                        printf("Mes invalido.\n");
                        continue;
                    }
                }else{
                    printf("Entrada invalida.\n");
                    continue;
                }
                passou = 1;
            }while(passou == 0);

            do{
                passou = 0;
                // Entrada do dia
                printf("Dia (1-%d): ", consultaDiasDoMes(mes));
                fflush(stdin);
                gets(entrada);

                // Validacao do dia
                if(validarInteiro(entrada) == 1){
                    dia = atoi(entrada);
                    if(!validarDia(mes, dia)){
                        printf("Dia invalido para esse mes.\n");
                        continue;
                    }
                }else{
                    printf("Entrada invalida.\n");
                    continue;
                }
                passou = 1;
            }while(passou == 0);

            do{
                passou = 0;
                // Entrada das horas trabalhadas
                printf("Horas trabalhadas (1-8): ");
                fflush(stdin);
                gets(entrada);

                // Validacao das horas trabalhadas
                if(validarInteiro(entrada) == 1){
                    if(atoi(entrada) < 1){
                        printf("Nao e possivel inserir menos que 1 hora de trabalho.\n");
                        continue;
                    }else if(atoi(entrada) > 8){
                        printf("Nao e possivel inserir mais de 8 horas de trabalho.\n");
                        continue;
                    }else{
                        horas = atoi(entrada);
                    }
                }else{
                    printf("Entrada invalida.\n");
                    continue;
                }
                passou = 1;
            }while(passou == 0);

            // Atribuicao das horas trabalhadas
            registro_existente = funcionario[posicao].horas_trabalhadas[mes - 1][dia - 1];
            if(funcionario[posicao].horas_trabalhadas[mes - 1][dia - 1] > 0){
                printf("Ja existe um registro de %d hora(s) nesse dia.\n", registro_existente);

                do{
                    passou = 0;
                    // Entrada da resposta
                    printf("Deseja alterar? (s/n): ");
                    fflush(stdin);
                    gets(entrada);

                    // Validacao da resposta
                    if(validarString(entrada) == 1){
                        if(tolower(entrada[0]) != 's'){
                            printf("Nao houve alteracao nas horas registradas.\n\n");
                            return;
                        }
                    }else{
                        printf("Entrada invalida.\n");
                        continue;
                    }
                    passou = 1;
                }while(passou == 0);
            }

            funcionario[posicao].horas_trabalhadas[mes - 1][dia - 1] = horas;
            printf("Horas inseridas com sucesso.\n\n");
            return;
        }
    }
    printf("Nenhum registro encontrado com esse nome.\n\n");
}

// Calcula o salario do funcionario no mes selecionado
void calcularSalario(){
    int mes, dia, total_horas = 0;
    int posicao;
    float salario = 0.0;
    char nome[50];

    do{
        passou = 0;
        // Entrada do nome
        printf("\nDigite o nome do funcionario: ");
        fflush(stdin);
        gets(entrada);

        // Validacao do nome
        if(validarString(entrada) == 1){
            strcpy(nome, entrada);
        }else{
            printf("Entrada invalida.");
            continue;
        }
        passou = 1;
    }while(passou == 0);

    do{
        passou = 0;
        // Entrada do mes
        printf("Digite o mes para calcular o salario (1-12): ");
        fflush(stdin);
        gets(entrada);

        // Validacao do mes
        if(validarInteiro(entrada) == 1){
            mes = atoi(entrada);
            if(!validarMes(mes)){
                printf("Mes invalido.\n");
                continue;
            }
        }else{
            printf("Entrada invalida.\n");
            continue;
        }
        passou = 1;
    }while(passou == 0);

    for(i=0; i<max_funcionarios; i++){
        if(strcmp(funcionario[i].nome, nome) == 0 && funcionario[i].flag == 1){
            for(dia=0; dia<consultaDiasDoMes(mes); dia++){
                total_horas += funcionario[i].horas_trabalhadas[mes - 1][dia];
            }
            salario = total_horas * funcionario[i].valor_hora;
            printf("O salario de %s no mes %d e: R$%.2f\n\n", nome, mes, salario);
            return;
        }
    }
    printf("Nenhum registro foi encontrado com esse nome.\n\n");
}

// Lista todos os funcionarios cadastrados
void listarFuncionarios(){
    int achou = 0;

    printf("\n");
    for(i=0; i<max_funcionarios; i++){
        if(funcionario[i].flag == 1){
            printf("CODIGO: %d\n", funcionario[i].codigo);
            printf("Nome: %s\n", funcionario[i].nome);
            printf("Ano: %d\n", funcionario[i].ano);
            printf("Cargo: %s\n", funcionario[i].cargo);
            printf("Valor hora: R$%.2f\n", funcionario[i].valor_hora);
            printf("---------------------------------\n");
            achou = 1;
        }
    }
    if(achou == 0){
        printf("Nenhum registro encontrado.\n\n");
    }else{
        printf("\n");
    }
}

// Altera as informacoes do funcionario selecionado
void alterarInformacoes(){
    int retorno, posicao;

    do{
        passou = 0;
        // Entrada do nome
        printf("\nDigite o nome do funcionario que deseja alterar informacoes: ");
        fflush(stdin);
        gets(entrada);

        // Validacao de entrada
        if(validarString(entrada) == 0){
            printf("Entrada invalida.");
            continue;
        }
        passou = 1;
    }while(passou == 0);

    for(i=0; i<max_funcionarios; i++){
        if(strcmp(funcionario[i].nome, entrada) == 0 && funcionario[i].flag == 1){
            posicao = i;
            do{
                printf("\nEscolha qual informacao deseja alterar:\n");
                printf("1 - Nome\n2 - Ano\n3 - Cargo\n4 - Valor hora\n");
                printf("5 - Sair da alteracao\n");

                // Entrada da escolha
                printf("Opcao: ");
                fflush(stdin);
                gets(entrada);

                // Validacao de entrada
                if(validarInteiro(entrada) == 1){
                    opcao = atoi(entrada);
                }else{
                    printf("Entrada invalida.\n");
                    continue;
                }

                // Validacao de entrada
                if(opcao < 1 || opcao > 5){
                    printf("Opcao invalida.\n");
                    continue;
                }


                // Alteracao dos dados
                switch(opcao){
                    case 1:
                        do{
                            retorno = entradaNome(posicao);
                        }while(retorno == 0);
                        break;
                    case 2:
                        do{
                            retorno = entradaAno(posicao);
                        }while(retorno == 0);
                        break;
                    case 3:
                        do{
                            retorno = entradaCargo(posicao);
                        }while(retorno == 0);
                        break;
                    case 4:
                        do{
                            retorno = entradaValorHora(posicao);
                        }while(retorno == 0);
                        break;
                    case 5: break;
                }
            }while(opcao != 5);
            printf("Alteracao realizada com sucesso.\n\n");
            return;
        }
    }
    printf("Nenhum registro encontrado com esse nome.\n\n");
}

// Exclui o registro do funcionario selecionado
void excluir(){
    int codigo, posicao;


    do{
        passou = 0;
        printf("\nDigite o codigo do funcionario que deseja excluir: ");
        fflush(stdin);
        gets(entrada);

        // Validacao de entrada
        if(validarInteiro(entrada) == 1){
            codigo = atoi(entrada);
        }else{
            printf("Entrada invalida.");
            continue;
        }
        passou = 1;
    }while(passou == 0);

    // Confirmacao de exclusao do registro
    for(i=0; i<max_funcionarios; i++){
        if(funcionario[i].codigo == codigo && funcionario[i].flag == 1){
            posicao = i;
            printf("CODIGO: %d\n", funcionario[i].codigo);
            printf("Nome: %s\n", funcionario[i].nome);
            printf("Ano: %d\n", funcionario[i].ano);
            printf("Cargo: %s\n", funcionario[i].cargo);
            printf("Valor hora: R$%.2f\n", funcionario[i].valor_hora);
            printf("---------------------------------\n");

            do{
                passou = 0;
                // Entrada da resposta
                printf("Deseja excluir esse registro? (s/n): ");
                fflush(stdin);
                gets(entrada);

                // Validacao da resposta
                if(validarString(entrada) == 1){
                    if(tolower(entrada[0] != 's')){
                        printf("O registro nao foi excluido.\n\n");
                        return;
                    }else{
                        funcionario[posicao].flag = 0;
                        printf("Registro excluido com sucesso.\n\n");
                        return;
                    }
                }else{
                    printf("Entrada invalida.\n");
                    continue;
                }
                passou = 1;
            }while(passou == 0);
        }
    }
    printf("Nenhum registro encontrado.\n\n");
    return;
}

// Consulta as horas trabalhadas pelo funcionario selecionado
void consultarHorasTrabalhadas(){
    int mes, dia; 
    int total_horas = 0;
    char nome[50];

    do{
        passou = 0;
        // Entrada do nome buscado
        printf("\nDigite o nome do funcionario que deseja consultar as horas trabalhadas: ");
        fflush(stdin);
        gets(entrada);

        // Validacao de entrada
        if(validarString(entrada) == 0){
            printf("Entrada invalida.");
            continue;
        }else{
            strcpy(nome, entrada);
        }
        passou = 1;
    }while(passou == 0);

    do{
        passou = 0;
        // Entrada do mes desejado
        printf("Mes (1-12): ");
        fflush(stdin);
        gets(entrada);

        // Validacao de entrada
        if(validarInteiro(entrada) == 1){
            mes = atoi(entrada);
            if(!validarMes(mes)){
                printf("Mes invalido.\n");
                continue;
            }
        }else{
            printf("Entrada invalida.\n");
            continue;
        }
        passou = 1;
    }while(passou == 0);

    for(i=0; i<max_funcionarios; i++){
        if(strcmp(funcionario[i].nome, nome) == 0 && funcionario[i].flag == 1){
            printf("\nHoras trabalhadas no mes %d:\n", mes);
            for(dia=0; dia<consultaDiasDoMes(mes); dia++){
                printf("Dia %d: %d hora(s)\n", dia + 1, funcionario[i].horas_trabalhadas[mes - 1][dia]);
                total_horas += funcionario[i].horas_trabalhadas[mes - 1][dia];
            }
            printf("Total de horas trabalhadas: %d\n\n", total_horas);
            return;
        }
    }
    printf("Nenhum registro encontrado com esse nome.\n\n");
}

// Programa principal
int main(){
    inicializaFlag();
    printf("Ficticia LTDA - Registro de empregados\n\n");

    do{
        printf("========== Menu ==========\n");
        printf("1 - Cadastar novo funcionario\n2 - Inserir horas trabalhadas\n3 - Calcular salario\n");
        printf("4 - Listar funcionarios cadastrados\n5 - Alterar informacoes do funcionario\n");
        printf("6 - Excluir\n7 - Consultar horas trabalhadas\n8 - Sair do programa\n");

        // Entrada da escolha
        printf("Opcao: ");
        fflush(stdin);
        gets(entrada);

        // Validacao de entrada
        if(validarInteiro(entrada) == 1){
            opcao = atoi(entrada);
        }else{
            printf("Opcao invalida.\n\n");
            continue;
        }

        // Validacao de entrada
        if(opcao < 1 || opcao > 8){
            printf("Opcao invalida.\n\n");
            continue;
        }

        switch(opcao){
            case 1: cadastrar(); break;
            case 2: inserirHorasTrabalhadas(); break;
            case 3: calcularSalario(); break;
            case 4: listarFuncionarios(); break;
            case 5: alterarInformacoes(); break;
            case 6: excluir(); break;
            case 7: consultarHorasTrabalhadas(); break;
            case 8:
                printf("\nSaindo...\n");
                break;
        }
    }while(opcao != 8);

    return 0;
}