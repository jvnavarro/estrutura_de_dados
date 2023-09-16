#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct carro
{
    int placaDoCarro;
    int numeroDeVezesQueFoiManobrado;
    struct carro *proximoCarro;
}carro;

void imprimir_menu();
int conta_vagas_disponiveis(carro **carroMaisProximoDaSaida);
void entrar_com_carro_no_estacionamento(carro **carroMaisProximoDaSaida, carro **carrosQueNaoConseguiramEntrar, int placa);
void coloca_carro_no_estacionamento(carro **carroMaisProximoDaSaida, int dado);
void coloca_carro_na_rua(carro **maisProximoDaSaida, int placa);
void mostrar_carros_estacionados(carro **ultimoEstacionado);
void mostrar_carros_que_n_conseguiram_entrar(carro **ultimoQueNaoConseguiuVaga);
void le_placa_do_carro(int *placa, int entradaOuSaida);
void da_saida_pra_fora(carro **carroMaisProximoDaSaida, carro **manobradoPraFora);
int busca_placa(carro **carroMaisProximoDaSaida,int placaBuscada);
void sair_com_carro_do_estacionamento(carro **carroMaisProximaDaSaida, carro **carrosQueSairam, int placaBuscada);

int main()
{
    carro *carroMaisProximoSaida = NULL, 
          *carrosQueNaoConseguiramEntrar = NULL, 
          *carrosQueSairamDoEstacionamento = NULL;
    int opcao, 
        placa;
    
        do
        {
            imprimir_menu();
            scanf("%d", &opcao);
        
            switch(opcao)
            {
                case 1: //entrar com carro no estacionamento
                    le_placa_do_carro(&placa, 1);
                    entrar_com_carro_no_estacionamento(&carroMaisProximoSaida, &carrosQueNaoConseguiramEntrar, placa);
                    break;                                             
                case 2://sair com carro do estacionamento
                    mostrar_carros_estacionados(&carroMaisProximoSaida);
                    printf("\nEstes sao os carros estacionados no momento e suas respectivas placas.\n");
                    le_placa_do_carro(&placa, 2);
                    sair_com_carro_do_estacionamento(&carroMaisProximoSaida, &carrosQueSairamDoEstacionamento, placa);
                    break;
                case 3:
                    mostrar_carros_estacionados(&carroMaisProximoSaida);
                    break;
                case 4:
                    mostrar_carros_que_n_conseguiram_entrar(&carrosQueNaoConseguiramEntrar);
                    break;
                case 5:
                    printf("Voce saiu do programa com sucesso!\n\n");
                    break;
                default:
                    printf("Opcao invalida. Tente novamente uma opcao valida.\n\n");
                    break;
                
            }    
        }while(opcao != 5);
    return 0;
}
void imprimir_menu()
{
    printf("\nMenu:\n");
    printf("1. Entrar com um carro no estacionamento.\n");
    printf("2. Sair com um carro do estacionamento.\n");
    printf("3. Mostrar carros que estao no estacionamento.\n");
    printf("4. Mostrar carros que estao na rua.\n");
    printf("5. Sair do programa.\n");
    printf("Sua escolha: ");
}
/*int conta_vaga_disponivel():
    é a função que vou usar para saber se tenho vagas livres quando um cliente chegar
    querendo deixar seu carro no estacionamento. Ela retorna o numero de vagas livres
    no presente momento. Acho que vou por ela dentro da função de entrar com um carro
    no estacionamento.
*/
int conta_vagas_disponiveis(carro **carroMaisProximoDaSaida)
{
    carro *percorreEstacionamento;
    int numeroDeCarrosEstacionados = 0, numeroDeVagasLivres;

    percorreEstacionamento = *carroMaisProximoDaSaida;

    if(percorreEstacionamento == NULL)
    {
        printf("\nO estacionamento esta vazio no momento.\n");
        numeroDeVagasLivres = 10;
        return numeroDeVagasLivres;
    }
    else
    {
        while(percorreEstacionamento != NULL)
        {
            numeroDeCarrosEstacionados++;
            percorreEstacionamento = percorreEstacionamento->proximoCarro;
        }
        numeroDeVagasLivres = 10 - numeroDeCarrosEstacionados;
        
        return numeroDeVagasLivres;
    }
}
void entrar_com_carro_no_estacionamento(carro **carroMaisProximoDaSaida, carro **carrosQueNaoConseguiramEntrar, int placa)
{
    int numeroDeVagasLivres;

    numeroDeVagasLivres = conta_vagas_disponiveis(carroMaisProximoDaSaida);

    if(numeroDeVagasLivres == 0)
    {
        printf("\nNao existem vagas livres para estacionar seu carro no momento.\n");
        coloca_carro_na_rua(carrosQueNaoConseguiramEntrar, placa);
    }
    else
    {
        coloca_carro_no_estacionamento(carroMaisProximoDaSaida, placa);
    }
}

void coloca_carro_no_estacionamento(carro **maisProximoDaSaida, int placa)
{
    carro *aux;

        aux = (carro*) malloc(sizeof(carro));
        aux->placaDoCarro = placa;
        aux->proximoCarro = NULL;
        if(*maisProximoDaSaida == NULL)
        {
            *maisProximoDaSaida = aux;
            (*maisProximoDaSaida)->numeroDeVezesQueFoiManobrado = 0;
            printf("\nO primeiro carro foi estacionado com sucesso.\n");
            aux = NULL;
        }
        else
        {
            aux->proximoCarro = *maisProximoDaSaida;
            *maisProximoDaSaida = aux;
            (*maisProximoDaSaida)->numeroDeVezesQueFoiManobrado = 0;
            aux = NULL;

            printf("\nO carro de placa %d entrou no estacionamento com sucesso, e eh o mais proximo da saida.\n", (*maisProximoDaSaida)->placaDoCarro);
        }
}
void coloca_carro_na_rua(carro **maisProximoDaSaida, int placa)
{
    carro *aux;

        aux = (carro*) malloc(sizeof(carro));
        aux->placaDoCarro = placa;
        aux->proximoCarro = NULL;
        if(*maisProximoDaSaida == NULL)
        {
            *maisProximoDaSaida = aux;
            (*maisProximoDaSaida)->numeroDeVezesQueFoiManobrado = 0;
            printf("\nPrimeiro carro a nao conseguir vaga, estacionamento lotado.\n");
            printf("\nNao havia lugar livre no estacionamento, logo o carro seguiu para rua.\n");
            aux = NULL;
        }
        else
        {
            aux->proximoCarro = *maisProximoDaSaida;
            *maisProximoDaSaida = aux;
            (*maisProximoDaSaida)->numeroDeVezesQueFoiManobrado = 0;
            aux = NULL;

            printf("\nO carro de placa %d nao conseguiu entrar no estacionamento com sucesso, pois o mesmo se encontra lotado.\n", (*maisProximoDaSaida)->placaDoCarro);
        }
}
void mostrar_carros_estacionados(carro **ultimoEstacionado)
{
    carro *aux;
    int vaga = 1;
    aux = *ultimoEstacionado;
    
    if(aux == NULL)
    {
        printf("O estacionamento esta vazio.\n");
    }
    else
    {
        while(aux != NULL)
        {
            printf("Carro na vaga numero %d, de Placa %d \n", vaga, aux->placaDoCarro);
            vaga++;
            aux = aux->proximoCarro;
        }
    }
}
void mostrar_carros_que_n_conseguiram_entrar(carro **ultimoQueNaoConseguiuVaga)
{
    carro *aux;
    int numero=1;
    aux = *ultimoQueNaoConseguiuVaga;
    
    if(aux == NULL)
    {
        printf("\nPor enquanto todos conseguiram entrar no estacionamento, ou o mesmo se encontra vazio.\n");
    }
    else
    {
        while(aux != NULL)
        {
            printf("Carro numero %d, de Placa %d \n", numero, aux->placaDoCarro);
            numero++;
            aux = aux->proximoCarro;
        }
    }
}
void le_placa_do_carro(int *placa, int entradaOuSaida)
{
    int placaLocal = 0;
    if(entradaOuSaida == 1)
    {
        printf("Digite a placa do carro que deseja colocar no estacionamento: ");
        scanf("%d", &placaLocal);
        while(placaLocal < 0 || placaLocal > 99)
        {
            printf("Digite a placa do carro que deseja colocar no estacionamento: ");
            scanf("%d", &placaLocal); // usarei placas de 0 a 99 por enquanto.
        }
        *placa = placaLocal;
    }
    else
    {
        printf("Digite a placa do carro que deseja tirar do estacionamento: ");
        scanf("%d", &placaLocal);
        while(placaLocal < 0 || placaLocal > 99)
        {
            printf("Digite a placa do carro que deseja tirar do estacionamento: ");
            scanf("%d", &placaLocal); // usarei placas de 0 a 99 por enquanto.
        }
        *placa = placaLocal;
    }

    
}
int busca_placa(carro **carroMaisProximoDaSaida,int placaBuscada)
{
    int placaEncontrada = 0; // 0 = nao encontrada, 1 = encontrada;
    if(*carroMaisProximoDaSaida == NULL)
    {
        printf("\nO estacionamento se encontra vazio, logo nao eh possivel buscar por placa alguma.\n");
        return placaEncontrada;
    }
    else
    {
        while(*carroMaisProximoDaSaida != NULL)
        {
            if((*carroMaisProximoDaSaida)->placaDoCarro == placaBuscada)
            {
                placaEncontrada = 1;
            }
            *carroMaisProximoDaSaida = (*carroMaisProximoDaSaida)->proximoCarro;
        }
        return placaEncontrada;
    }
}
void da_saida_pra_fora(carro **carroMaisProximoDaSaida, carro **manobradoPraFora)
{
    carro *aux;
    
    if(*carroMaisProximoDaSaida == NULL) //verifica se a pilha 1 esta vazia.
    {
        printf("\nNao existe dado algum na pilha para passar de uma para a outra.\n");
    }                                                           //      Ilustracao do uso de aux:
    else                                                        //      *carroMaisProximoDaSaida ->  3 -------¬
    {                                                           //                          *aux ->  2        V 
        // aux:aqui serve para guardar o endereco                                                    1-||     3-||
        // aqui serve para guardar o endereco  do item anterior ao carroMaisProximoDaSaida.        pilha1  pilha2
        // sua funcao é atribuir o endereco que ela guarda ao *carroMaisProximoDaSaida, 
        // apos fazer meu topo
        //   
        aux = (*carroMaisProximoDaSaida)->proximoCarro;
        /* if(*manobradoPraFora == NULL): verifica se a pilha2 esta vazia, caso esteja transfiro 
                o  endereco em *carroMaisProximoDaSaida para *manobradoPraFora e faco com que esse carro aponte para NULL, o que 
                significa que é o primeiro item da pilha 2, em seguida faco meu carroMaisProximoDaSaida apontar
                de fato para o carroMaisProximoDaSaida, ao fazer a atribuicao "*carroMaisProximoDaSaida = aux".
        */
        if(*manobradoPraFora == NULL)   
        {               
            *manobradoPraFora = *carroMaisProximoDaSaida;
            (*manobradoPraFora)->proximoCarro = NULL;
            *carroMaisProximoDaSaida = aux;
            (*manobradoPraFora)->numeroDeVezesQueFoiManobrado++; 
            printf("\nO dado %d foi passado para a pilha 2 com sucesso!\n", (*manobradoPraFora)->placaDoCarro);
        }

        else                                              
        {                                                  
            (*carroMaisProximoDaSaida)->proximoCarro = *manobradoPraFora;// "emendo" o carro do *carroMaisProximoDaSaida, na pilha2
            *manobradoPraFora = *carroMaisProximoDaSaida;     // como este virou o topo da pilha 2, faco esta atribuicao
            /*if(*carroMaisProximoDaSaida == aux): quer dizer que cheguei no primeiro e ultimo item da minha pilha1
                    tenho que atribuir a *carroMaisProximoDaSaida, NULL, para que nao tenha problemas quando
                    voltar outra vez na funcao.
            */
            if(*carroMaisProximoDaSaida == aux)
            {
                *carroMaisProximoDaSaida = NULL;
                printf("\nO ultimo item no topo da pilha 1 foi alocado para pilha 2 com sucesso!\n");
                (*manobradoPraFora)->numeroDeVezesQueFoiManobrado++; 
            }
            else
            {
                *carroMaisProximoDaSaida = aux; // faz meu *carroMaisProximoDaSaida apontar de fato para o carroMaisProximoDaSaida.
                printf("\nO item no topo da pilha 1 foi alocado para pilha 2 com sucesso!\n");
                (*manobradoPraFora)->numeroDeVezesQueFoiManobrado++; 
            }
        }
    }
}
void sair_com_carro_do_estacionamento(carro **carroMaisProximaDaSaida, carro **carrosQueSairam, int placaBuscada)
{
    carro *auxPercorreEstacionamento, *movidoPraFora, *guardaProximoCarro;
    int /*contadorQuantosCarrosSeraoManobrados = 0*/, placaEncontradaOuNao;

    auxPercorreEstacionamento = *carroMaisProximaDaSaida;

    if(*carroMaisProximaDaSaida == NULL)
    {
        printf("Ainda nao tem nenhum carro no estacionamento.\n");
    }
    else
    {
        placaEncontradaOuNao = busca_placa(carroMaisProximaDaSaida, placaBuscada); //encontrada = 1, nao encontrada = 0;
        if(placaEncontradaOuNao == 1)
        {
            while(auxPercorreEstacionamento->placaDoCarro != placaBuscada)
            {
                da_saida_pra_fora(&auxPercorreEstacionamento, &movidoPraFora);
                if(auxPercorreEstacionamento->placaDoCarro == placaBuscada)
                {
                    guardaProximoCarro = auxPercorreEstacionamento->proximoCarro;
                    
                }
                auxPercorreEstacionamento = auxPercorreEstacionamento->proximoCarro;
            }

        }
        else
        {
            printf("O carro com a placa %d nao foi encontrado no estacionamento, verifique se digitou corretamente o numero da mesma.\n", placaBuscada);
        }
    }
}
