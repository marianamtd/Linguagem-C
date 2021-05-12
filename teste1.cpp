#include <stdio.h>
#include <string.h>
#include <ctype.h>

const int QTD_MAX = 50;
const int MAX_LEN = 30;

struct Produto {
    int codigo;
    char descricao[MAX_LEN] = {0};
    char categoria;
    int quantidade;
    float preco;
};

int busca_produto (Produto produto[], char vp[])
{
    for (int i = 0; i < QTD_MAX; i++)
        for (int j = 0; j < 5; j++)
            if (produto[i].categoria == vp[j])
                return 1;

    return -1;
}

int busca_categoria (Produto produto[], char categoria)
{
    for (int i = 0; i < QTD_MAX; i++)
        if (produto[i].categoria == categoria)
            return 1;

    return -1;
}

int busca_codigo (Produto produto[], int codigo)
{
    for (int i = 0; i < QTD_MAX; i++)
        if (produto[i].codigo == codigo)
            return 1;

    return -1;
}

void aplica_aumento_desconto(Produto produto[], char vp[])
{
    int codigo, x;
    char operacao, categoria;
    float aumento_perc, desconto_perc, preco, aumento, desconto, novo_preco;

    getchar();

    // Entrada do tipo de opera��o
    printf("Operacao (A-Aumento ou D-Desconto): ");
    scanf("%c", &operacao);

    if (operacao != 'A' && operacao != 'D')
    {
        printf("Operacao invalida!");
        return;
    }

    //getchar();

    // Entrada do c�digo do produto
    printf("Codigo: ");
    scanf("%d", &codigo);

    // Caso o c�digo do produto seja inv�lido por n�o possuir 6 d�gitos:
    if (codigo <= 99999 && codigo != 0 || codigo >= 1000000)
    {
        printf("Codigo invalido!");
        return;
    }

    // Se o c�digo possuir 6 d�gitos
    if (codigo > 99999 && codigo < 1000000)
    {
       // Chamada da fun��o busca_codigo para verificar se h� um produto com esse c�digo
       x = busca_codigo(produto, codigo);

       // Caso n�o h� o codigo:
       if (x == -1)
       {
           printf("Produto nao existe!");
           return;
       }

       // Se h� o c�digo e � desejado realizar um aumento:
       if (x == 1 && operacao == 'A')
       {
           printf("Percentual: ");
           scanf("%f", &aumento_perc);

           //Valor do aumento inv�lido:
           if (aumento_perc <= 0)
           {
               printf("Percentual invalido!");
               return;
           }

           // Passar o pre�o do produto que tem o c�digo informado para a vari�vel pre�o
           for (int i = 0; i < QTD_MAX; i++)
                if (produto[i].codigo == codigo)
                    preco = produto[i].preco;

           // C�lculo do novo pre�o
           aumento = preco * aumento_perc / 100;

           novo_preco = preco + aumento;

           //Passar o novo pre�o para o produto
           for (int i = 0; i < QTD_MAX; i++)
                if (produto[i].codigo == codigo)
                    produto[i].preco = novo_preco;

           printf("Operacao realizada com sucesso. Produtos aumentados: 1\n");
       }

       // Se h� o c�digo e � desejado realizar um aumento:
       else if (x == 1 && operacao == 'D')
       {
           printf("Percentual: ");
           scanf("%f", &desconto_perc);

           // Valor do desconto inv�lido:
           if (desconto_perc <= 0)
           {
               printf("Percentual invalido!");
               return;
           }

           // Passar o pre�o do produto que tem o c�digo informado para a vari�vel pre�o
           for (int i = 0; i < QTD_MAX; i++)
                if (produto[i].codigo == codigo)
                    preco = produto[i].preco;

           // C�lculo do novo pre�o
           desconto = preco * desconto_perc / 100;

           novo_preco = preco - desconto;

           // Passar o novo pre�o para o produto
           for (int i = 0; i < QTD_MAX; i++)
                if (produto[i].codigo == codigo)
                    produto[i].preco = novo_preco;

           printf("Operacao realizada com sucesso. Produtos descontados: 1\n");
       }
    }

    // Se for desejado realizar a opera��o em uma categoria:
    else if (codigo == 0)
    {
        int contador = 0;

        getchar();

        printf("Categoria: ");
        scanf("%c", &categoria);

        if (categoria != 'A' && categoria != 'B' && categoria != 'C' && categoria != 'D' && categoria != 'E' && categoria != 'T')
        {
            printf("Categoria nao existe!");
            return;
        }

        //getchar();

        if (categoria != 'T')
        {
            x = busca_categoria (produto, categoria);

            if (x == -1)
            {
                printf("Nao ha um produto com a categoria informada!");
                return;
            }
        }

        else
        {
            x = busca_produto (produto, vp);

            if (x == -1)
            {
                printf("Nao ha um produto no programa!");
                return;
            }
        }

        /*while (x == -1)
        {
            int decisao;

            puts("Nao ha um produto com a categoria informada ou nao ha um produto no programa.");
            printf("Insira 1 caso queira inserir outra categoria, ou 2 caso queira voltar ao menu principal para inserir um produto: ");
            scanf("%d", &decisao);

            while (decisao != 1 && decisao != 2)
            {
                printf("Valor invalido, insira 1 ou 2: ");
                scanf("%d", &decisao);
            }

            if (decisao == 1)
            {
                getchar();
                printf("Insira uma categoria: ");
                scanf("%c", &categoria);
                x = busca_categoria (produto, categoria);
            }

            else
                return;
        }*/

        if (x == 1)
        {
            //Se for uma categoria espec�fica
            if (categoria != 'T')
            {
                //Em caso de opera��o de aumento:
                if (operacao == 'A')
                {
                    printf("Percentual: ");
                    scanf("%f", &aumento_perc);

                    if (aumento_perc <= 0)
                    {
                        printf("Percentual invalido!");
                        return;
                    }

                    //Pegar o pre�o de cada produto da categoria desejada e atualiz�-lo
                    for (int i = 0; i < QTD_MAX; i++)
                        if (produto[i].categoria == categoria)
                            {
                                contador++;
                                preco = produto[i].preco;
                                aumento = preco * aumento_perc / 100;
                                novo_preco = preco + aumento;
                                produto[i].preco = novo_preco;
                            }

                    printf("Operacao realizada com sucesso. Produtos aumentados: %d\n", contador);
                }

                //Em caso de opera��o de desconto:
                if (operacao == 'D')
                {
                    printf("Percentual: ");
                    scanf("%f", &desconto_perc);

                    if (desconto_perc <= 0)
                    {
                        printf("Percentual invalido!");
                        return;
                    }

                    //Pegar o pre�o de cada produto da categoria desejada e atualiz�-lo
                    for (int i = 0; i < QTD_MAX; i++)
                        if (produto[i].categoria == categoria)
                            {
                                contador++;
                                preco = produto[i].preco;
                                desconto = preco * desconto_perc / 100;
                                novo_preco = preco - desconto;
                                produto[i].preco = novo_preco;
                            }

                    printf("Operacao realizada com sucesso. Produtos descontados: %d\n", contador);
                }
            }

            //Caso queira alterar o pre�o de TODOS os produtos:
            else if (categoria == 'T')
            {
                //Aumentar o pre�o de todos os produtos
                if (operacao == 'A')
                {
                    printf("Percentual: ");
                    scanf("%f", &aumento_perc);

                    if (aumento_perc <= 0)
                    {
                        printf("Percentual invalido!");
                        return;
                    }

                    //Pegar o pre�o de todos os produtos e atualiz�-los
                    for (int i = 0; i < QTD_MAX; i++)
                        for (int j = 0; j < 5; j++)
                            if (produto[i].categoria == vp[j])
                                {
                                    contador++;
                                    preco = produto[i].preco;
                                    aumento = preco * aumento_perc / 100;
                                    novo_preco = preco + aumento;
                                    produto[i].preco = novo_preco;
                                }

                    printf("Operacao realizada com sucesso. Produtos aumentados: %d\n", contador);
                }

                //Descontar o pre�o de todos os produtos
                if (operacao == 'D')
                {
                    printf("Percentual: ");
                    scanf("%f", &desconto_perc);

                    if (desconto_perc <= 0)
                    {
                        printf("Percentual invalido!");
                        return;
                    }

                    //Pegar o pre�o de todos os produtos e atualiz�-los
                    for (int i = 0; i < QTD_MAX; i++)
                        for (int j = 0; j < 5; j++)
                            if (produto[i].categoria == vp[j])
                                {
                                    contador++;
                                    preco = produto[i].preco;
                                    desconto = preco * desconto_perc / 100;
                                    novo_preco = preco - desconto;
                                    produto[i].preco = novo_preco;
                                }

                    printf("Operacao realizada com sucesso. Produtos descontados: %d\n", contador);
                }
            }
        }
    }
}
// listagem por descricao
void listar_por_descricao(Produto produto[], int &total_qtd)
{
    char temp[MAX_LEN];

    bool trocou = true;
    for (int k = total_qtd-1; k>0 && trocou; k--)
    {
    trocou = false;
    for (int i = 0; i < k; i++)
        if (strcmp(produto[i].descricao, produto[i+1].descricao) > 0)
        {
            // descricao
            strcpy(temp, produto[i+1].descricao);
            strcpy(produto[i+1].descricao, produto[i].descricao);
            strcpy(produto[i].descricao, temp);

            // codigo
            int temp2;
            temp2 = produto[i+1].codigo;
            produto[i+1].codigo = produto[i].codigo;
            produto[i].codigo = temp2;

            // categoria
            char temp3;
            temp3 = produto[i+1].categoria;
            produto[i+1].categoria = produto[i].categoria;
            produto[i].categoria = temp3;

            // quantidade
            int temp4;
            temp4 = produto[i+1].quantidade;
            produto[i+1].quantidade = produto[i].quantidade;
            produto[i].quantidade = temp4;

            // preco
            float temp5;
            temp5 = produto[i+1].preco;
            produto[i+1].preco = produto[i].preco;
            produto[i].preco = temp5;

            trocou = true;
        }
    }

    putchar('\n');

    puts("--------------------------------------------------------");
    puts("Codigo Descricao                      Categ  Qtd   Preco");
    puts("--------------------------------------------------------");
    for (int i = 0; i <= total_qtd-1; i++)
        printf("%d %-30s   %c   %4d %7.2f\n", produto[i].codigo, produto[i].descricao, produto[i].categoria, produto[i].quantidade, produto[i].preco);
    puts("--------------------------------------------------------");
}

// listagem por categoria
void listar_por_categoria(Produto produto[], int &total_qtd)
{
    char temp[MAX_LEN];
    bool trocou = true;

    for (int k = total_qtd-1; k>0 && trocou; k--)
    {
        trocou = false;
        for (int i = 0; i < k; i++)
        {
           if (produto[i+1].categoria < produto[i].categoria)
            {
                // descricao
                strcpy(temp, produto[i+1].descricao);
                strcpy(produto[i+1].descricao, produto[i].descricao);
                strcpy(produto[i].descricao, temp);

                // codigo
                int temp2;
                temp2 = produto[i+1].codigo;
                produto[i+1].codigo = produto[i].codigo;
                produto[i].codigo = temp2;

                // categoria
                char temp3;
                temp3 = produto[i+1].categoria;
                produto[i+1].categoria = produto[i].categoria;
                produto[i].categoria = temp3;

                // quantidade
                int temp4;
                temp4 = produto[i+1].quantidade;
                produto[i+1].quantidade = produto[i].quantidade;
                produto[i].quantidade = temp4;

                // preco
                float temp5;
                temp5 = produto[i+1].preco;
                produto[i+1].preco = produto[i].preco;
                produto[i].preco = temp5;

                trocou = true;
            }
        }
    }

    putchar('\n');

    puts("--------------------------------------------------------");
    puts("Codigo Descricao                      Categ  Qtd   Preco");
    puts("--------------------------------------------------------");
    for (int i = 0; i <= total_qtd-1; i++)
        printf("%d %-30s   %c   %4d %7.2f\n", produto[i].codigo, produto[i].descricao, produto[i].categoria, produto[i].quantidade, produto[i].preco);
    puts("--------------------------------------------------------");
}

// lista por estoque
void listar_por_estoque(Produto produto[], int &total_qtd)
{
    int minima;

    // Le a quantidade minima
    do
    {
        printf("Qtd minima: ");
        scanf("%d", &minima);

        if (minima < 0)
            puts("Digite novamente! Quantidade invalida");

    } while (minima < 0);

    // Procura os produtos com estoque menor que a quantidade minima e imprime seus dados
    puts("--------------------------------------------------------");
    puts("Codigo Descricao                      Categ  Qtd   Preco");
    puts("--------------------------------------------------------");
    for (int i = 0; i < total_qtd; i++)
        if (produto[i].quantidade < minima)
            printf("%d %-30s   %c   %4d %7.2f\n", produto[i].codigo, produto[i].descricao, produto[i].categoria, produto[i].quantidade, produto[i].preco);

    puts("--------------------------------------------------------");
}

// listagem dos produtos
void menu_listagem(Produto produto[], int &total_qtd)
{
    putchar('\n');
    printf("Menu da Listagem\n");
    printf("1-Listar todos os produtos (ordenado por descricao)\n");
    printf("2-Listar todos os produtos (ordenado por categoria/descricao)\n");
    printf("3-Listar produtos com estoque baixo\n");
    printf("4-Voltar\n");

    int operacao;
    do
    {
        printf("Qual operacao voce deseja realizar? ");
        scanf("%d", &operacao);

        if (operacao != 1 && operacao != 2 && operacao != 3 && operacao != 4)
            puts("Operacao invalida");

    } while (operacao != 1 && operacao != 2 && operacao != 3 && operacao != 4);

    switch (operacao)
    {
    case 1: // listar por ordem de descricao
        listar_por_descricao(produto, total_qtd);
        break;

    case 2: // listar por ordem de categoria/descricao
        listar_por_categoria(produto, total_qtd);
        break;

    case 3: // listar por estoque baixo
        listar_por_estoque(produto, total_qtd);
        break;

    case 4: // voltar
        break;
    }
}

// fun��es que leem os dados do inclui_produtos
// L� c�digo
void le_codigo(Produto produto[], int qtd, int i)
{
    int j;
    int codigo_prod;

    do
    {
        printf("Codigo: ");
        scanf("%d", &produto[i].codigo);

        if (produto[i].codigo <= 99999 || produto[i].codigo >= 1000000)
            puts("Codigo invalido. Insira novamente.");

        codigo_prod = produto[i].codigo;
        for (j = i; j > 0; j--)
        {
            if (codigo_prod == produto[j-1].codigo)
            {
                puts("Codigo ja existe.");
                printf("Codigo %d: ", i+1);
                scanf("%d", &produto[i].codigo);
                i--;
            }
        }
    } while(produto[i].codigo <= 99999 || produto[i].codigo >= 1000000 || codigo_prod == produto[j-1].codigo);
}

// L� descri��o
void le_descricao(Produto produto[], int qtd, int i)
{
    do {
        printf("Descricao: ");
        gets(produto[i].descricao);

        strupr(produto[i].descricao);

        if (strlen(produto[i].descricao) < 4 || strlen(produto[i].descricao) > 30)
            puts("Descricao invalida: Insira novamente.");

    } while (strlen(produto[i].descricao) < 4 || strlen(produto[i].descricao) > 30);

    // imprime cada um pra conferir se ta tudo certo
    /* for (int i = 0; i < qtd; i++)
    {
        puts(produto[i].descricao);
    } */
}

// L� categoria
void le_categoria(Produto produto[], int qtd, int i)
{
    do
        {
            // getchar();
            printf("Categoria: ");
            produto[i].categoria = getchar();

            if (produto[i].categoria != 'A' && produto[i].categoria != 'B' && produto[i].categoria != 'C' && produto[i].categoria != 'D' && produto[i].categoria != 'E' && produto[i].categoria != 'a' && produto[i].categoria != 'b' && produto[i].categoria != 'c' && produto[i].categoria != 'd' && produto[i].categoria != 'e')
                printf("Invalido\n");

        } while (produto[i].categoria != 'A' && produto[i].categoria != 'B' && produto[i].categoria != 'C' && produto[i].categoria != 'D' && produto[i].categoria != 'E' && produto[i].categoria != 'a' && produto[i].categoria != 'b' && produto[i].categoria != 'c' && produto[i].categoria != 'd' && produto[i].categoria != 'e');

        int cat = produto[i].categoria;
        if (cat >= 97 && cat <= 101)
            produto[i].categoria = toupper(produto[i].categoria);

    /* for (int i = 0; i < qtd; i++)
    {
        printf("%c ", produto[i].categoria);
    } */
}

// L� quantidade
void le_quantidade(Produto produto[], int qtd, int i)
{
    do
    {
        printf("Qtd.: ");
        scanf("%d", &produto[i].quantidade);

        if (produto[i].quantidade <= 0)
            puts("Quantidade menor ou igual a 0.");

    } while (produto[i].quantidade <= 0);
}

// L� pre�o
void le_preco(Produto produto[], int qtd, int i)
{
    do
    {
        printf("Preco: ");
        scanf("%f", &produto[i].preco);

        if (produto[i].preco <= 0)
            puts("Preco menor ou igual a 0.");

    } while (produto[i].preco <= 0);
}

// Abater o estoque
void abate_estoque(Produto produto[], int &total_qtd)
{
  // declara��o das vari�veis
    int cod, quantidade;

    printf("Codigo: ");
    scanf("%d", &cod);
    printf("Qtd.: ");
    scanf("%d", &quantidade);

    int pos;
    int existe_estoque = 0;

    // loop para procurar esse codigo no vetor
    for (int i = 0; i < total_qtd; i++)
    {
        if (cod == produto[i].codigo)
        {
            pos = i;
            existe_estoque = 1;
        }
    }

    if (existe_estoque == 1)
    {
        // abate produto quando a quantidade do estoque � maior do que a quantidade que se quer excluir.
        if (produto[pos].quantidade >= quantidade)
        {
            produto[pos].quantidade -= quantidade;
            printf("Quantidade abatida. ");
            printf("Produto %c%s%c agora tem %d em estoque.\n", 34, produto[pos].descricao, 34, produto[pos].quantidade);
        }

        // qtd para abater � maior que a quantidade existente em estoque.
        else if (produto[pos].quantidade < quantidade)
        {
            printf("Produto %c%s%c tem somente %d quantidade em estoque.\n", 34, produto[pos].descricao, 34, produto[pos].quantidade);
        }
    }

    else
        printf("Produto nao existe!\n");
}

// Excluir produto
void exclui_produto(Produto produto[], int &total_qtd, int &p)
{
    int produto_excluir;

    puts("Produto a excluir");
    printf("Codigo: ");
    scanf("%d", &produto_excluir);

    int pos;
    int existe = 0;
    // loop para procurar esse codigo no vetor
    for (int i = 0; i < total_qtd; i++)
        if (produto_excluir == produto[i].codigo)
        {
            pos = i;
            existe = 1;
        }

    if (existe == 1)
    {
        // se a quantidade for > 0, copia o proximo elemento para o atual
        if (produto[pos].quantidade > 0)
            printf("Produto %c%s%c tem %d em estoque!", 34, produto[pos].descricao, 34, produto[pos].quantidade);

        else // if quantidade <= 0
        {
            printf("Produto %c%s%c excluido com sucesso!", 34, produto[pos].descricao, 34);
            // ordena os itens da menor quantidade para a maior
            char temp[MAX_LEN];
            bool trocou = true;

            for (int k = total_qtd-1; k>0 && trocou; k--)
            {
                trocou = false;
                for (int i = 0; i < k; i++)
                {
                    if (produto[i].quantidade > produto[i+1].quantidade)
                    {
                        // descricao
                        strcpy(temp, produto[i+1].descricao);
                        strcpy(produto[i+1].descricao, produto[i].descricao);
                        strcpy(produto[i].descricao, temp);

                        // codigo
                        int temp2;
                        temp2 = produto[i+1].codigo;
                        produto[i+1].codigo = produto[i].codigo;
                        produto[i].codigo = temp2;

                        // categoria
                        char temp3;
                        temp3 = produto[i+1].categoria;
                        produto[i+1].categoria = produto[i].categoria;
                        produto[i].categoria = temp3;

                        // quantidade
                        int temp4;
                        temp4 = produto[i+1].quantidade;
                        produto[i+1].quantidade = produto[i].quantidade;
                        produto[i].quantidade = temp4;

                        // preco
                        float temp5;
                        temp5 = produto[i+1].preco;
                        produto[i+1].preco = produto[i].preco;
                        produto[i].preco = temp5;

                        trocou = true;
                    }
                }
            }

            //printf("Produto %c%s%c excluido com sucesso!", 34, produto[pos].descricao, 34);

            /* // EXCLUIR
            // testando
            for (int i = 0; i < total_qtd-1; i++)
            {
                printf("%d ", produto[i].codigo);
            } */

            // puts("pre exclusao");
            // puts("--------------------------------------------------------");
            // puts("Codigo Descricao                      Categ  Qtd   Preco");
            // puts("--------------------------------------------------------");
            // for (int i = 0; i < total_qtd; i++)
            //     printf("%d %-30s   %c   %4d %7.2f\n", produto[i].codigo, produto[i].descricao, produto[i].categoria, produto[i].quantidade, produto[i].preco);
            // puts("--------------------------------------------------------");

            for (int i = 0; i < total_qtd-1; i++)
            {
                produto[i].codigo = produto[i+1].codigo;
                strcpy(produto[i].descricao, produto[i+1].descricao);
                produto[i].categoria = produto[i+1].categoria;
                produto[i].quantidade = produto[i+1].quantidade;
                produto[i].preco = produto[i+1].preco;
            }

            // putchar('\n');
            // puts("pos exclusao");
            // puts("--------------------------------------------------------");
            // puts("Codigo Descricao                      Categ  Qtd   Preco");
            // puts("--------------------------------------------------------");
            // for (int i = 0; i < total_qtd; i++)
            //     printf("%d %-30s   %c   %4d %7.2f\n", produto[i].codigo, produto[i].descricao, produto[i].categoria, produto[i].quantidade, produto[i].preco);
            // puts("--------------------------------------------------------");

            // diminiui o tamanho do vetor ap�s excluir o produto
            total_qtd = total_qtd - 1;
            p--;

            // putchar('\n');
            // puts("pos exclusao 2");
            // puts("--------------------------------------------------------");
            // puts("Codigo Descricao                      Categ  Qtd   Preco");
            // puts("--------------------------------------------------------");
            // for (int i = 0; i < total_qtd; i++)
            //     printf("%d %-30s   %c   %4d %7.2f\n", produto[i].codigo, produto[i].descricao, produto[i].categoria, produto[i].quantidade, produto[i].preco);
            // puts("--------------------------------------------------------");
        }
    }

    else
        printf("Produto nao existe!");
}

// Incluir produto
void inclui_produto(Produto produto[], int &total_qtd, int &qtd, int &cont, int &p)
{
    // printf("p agora: %d\n", p);

    printf("Quantidade de produtos: ");
    scanf("%d", &qtd);

    putchar('\n');

    // soma quantidade lida ao total
    total_qtd += qtd;
    // printf("total qtd: %d\n", total_qtd);

    // se a quantidade total > 50, diminui a quantidade lida
    if (total_qtd > 50)
    {
        puts("Limite de estoque e de 50 produtos.");
        total_qtd -= qtd;
    }

    else
    {
        if (cont == 1)
        {
            puts("TA AQUI 1");
            for (int i = 0; i < total_qtd; i++)
            {
                printf("DADOS DO PRODUTO %d\n", i+1);
                le_codigo(produto, total_qtd, i);
                getchar();
                le_descricao(produto, total_qtd, i);
                le_categoria(produto, total_qtd, i);
                le_quantidade(produto, total_qtd, i);
                le_preco(produto, total_qtd, i);
                printf("Produto cadastrado com sucesso!\n");
                putchar('\n');
            }

            p = p + total_qtd;
        }

        else if (cont > 1)
        {
            puts("TA AQUI 2");
            for (p; p < total_qtd; p++)
            {
                printf("DADOS DO PRODUTO %d\n", p+1);
                le_codigo(produto, total_qtd, p);
                getchar();
                le_descricao(produto, total_qtd, p);
                le_categoria(produto, total_qtd, p);
                le_quantidade(produto, total_qtd, p);
                le_preco(produto, total_qtd, p);
                printf("Produto cadastrado com sucesso!\n");
                putchar('\n');
            }
        }

        /* // tudo daqui p baixo � s� teste
        // p = p + qtd;
        printf("p embaixo: %d", p);

        // imprimindo todos os produtos aqui p testar
        putchar('\n');
        for (int i = 0; i < total_qtd; i++)
        {
            printf("%d %s\n", produto[i].codigo, produto[i].descricao);
        } */
    }
}

int main()
{
    Produto produto[QTD_MAX];
    int opcao;
    int codigo_prod;
    int qtd;
    int cont = 0;
    int total_qtd = 0;
    int p = 0;
    char vp[5] = {'A', 'B', 'C', 'D', 'E'};

    // menu principal
    do
    {
        puts("\nMenu Principal");
        puts("1-Incluir Produto");
        puts("2-Excluir Produto");
        puts("3-Abater do estoque");
        puts("4-Listar produtos");
        puts("5-Aplicar aumento/desconto");
        puts("6-Fim");

        printf("Qual operacao voce deseja realizar? ");
        scanf("%d", &opcao);

        putchar('\n');

        switch (opcao)
        {
        case 1: // incluir produto
            cont++;
            printf("contador: %d\n", cont);
            inclui_produto(produto, total_qtd, qtd, cont, p);
            break;

        case 2: // excluir produto
            exclui_produto(produto, total_qtd, p);
            break;

        case 3: // abater do estoque
            abate_estoque(produto, total_qtd);
            break;

        case 4: // listar produtos -> menu_listagem
            menu_listagem(produto, total_qtd);
            break;

        case 5: // menu aumento/desconto
            aplica_aumento_desconto(produto, vp);
            break;

        case 6: // fim
            break;

        default: // opcao invalida
            puts("Opcao invalida");
        }
    } while (opcao != 6);
}
