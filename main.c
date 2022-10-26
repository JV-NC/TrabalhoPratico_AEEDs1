#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct{ //estrutura p/ os cadastros
    char nome[15];
    int matricula;
    float n[3],media;
}cadastro;

int contalinha();
void abrir_arquivo(cadastro x[], int c); //abrir arquivo e pegar variaveis
float mediafinal(cadastro x[],int c); //calcula media e retorna a media final
void imprimir_normal(cadastro x[],int c); //imprime todos os valores do arranjo
void imprimir_nomes(cadastro x[],int c); //imprime so os nomes
void imprimir_media(cadastro x[],int c); //imprime os nomes e media
void ordenar(cadastro x[],int c); //ordena usando bubblesort
int buscseq(cadastro x[],int c); //puxa dados de um aluno pela matricula
void imprimir_1aluno(cadastro x[],int c,int hold); //depende de busca sequencial
void editar(cadastro x[],int c,int hold); //depende de busca sequencial
int maior_nota(cadastro x[],int c); //descobre a maior media
int menor_nota(cadastro x[],int c); //descobre a menor media
void aprovacao(cadastro x[],int c); //calcula quantos foram aprovados e reprovados
void select(cadastro x[],int c); //menu com as opções em loop
void novo_arquivo(cadastro x[],int c,float m); //cria um novo arquivo com media final

int main()
{
    setlocale(LC_ALL,"Portuguese"); //permitindo acentuação

    int linha;
    float mediaf;
    linha=contalinha();
    printf("%d\n\n",linha);

    cadastro *v;
    v=(cadastro*)malloc(linha*sizeof(cadastro));

    abrir_arquivo(v,linha);

    mediaf=mediafinal(v,linha);

    select(v,linha);

    ordenar(v,linha);

    mediaf=mediafinal(v,linha);

    novo_arquivo(v,linha,mediaf);

    return 0;
}

int contalinha(){
    int linha=1;
	char c;
	FILE *a;

	a=fopen("alunos.txt","r");

	for (c = getc(a); c != EOF; c = getc(a)){ //conta linhas
        if (c == '\n'){
            linha++;}
	}
    fclose(a);

    return linha;
}

void abrir_arquivo(cadastro x[], int c){
    FILE *arq;
    arq=fopen("alunos.txt","r");
    int i;
    for(i=0;i<c;i++){
        fscanf(arq,"%d %s %f %f %f",&x[i].matricula,x[i].nome,&x[i].n[0],&x[i].n[1],&x[i].n[2]);
    }
    fclose(arq);
}

float mediafinal(cadastro x[],int c){
    int i;
    float mediaf=0;
    for(i=0;i<c;i++){
        x[i].media=(x[i].n[0]+x[i].n[1]+x[i].n[2])/3;
    }
    for(i=0;i<c;i++){
        mediaf+=x[i].media;
    }
    mediaf/=c;
    return mediaf;
}
void imprimir_normal(cadastro x[],int c){
    int i;

    for(i=0;i<c;i++){
        printf("Matricula: %d\nNome: %s\nNota 1: %.1f\nNota 2: %.1f\nNota 3: %.1f\n\n",x[i].matricula,x[i].nome,x[i].n[0],x[i].n[1],x[i].n[2]);
    }
}

void imprimir_nomes(cadastro x[],int c){
    int i;

    for(i=0;i<c;i++){
        printf("Nome: %s\n\n",x[i].nome);
    }
}

void imprimir_media(cadastro x[],int c){
    int i;

    for(i=0;i<c;i++){
        printf("Nome: %s\nMedia: %.2f\n\n",x[i].nome,x[i].media);
    }
}

void ordenar(cadastro x[],int c){ //ordena o vetor de estruturas em ordem crescente de matricula
    int step,i;
    cadastro temp;
    for(step=0;step<c-1;step++){
        for(i=0;i<c-step-1;i++){
            if(x[i].matricula>x[i+1].matricula){
                temp=x[i];
                x[i]=x[i+1];
                x[i+1]=temp;
            }
        }
    }
}

int buscseq(cadastro x[],int c){ //busca e imprime as informações da matricula scaneada
    int i,buscmat,hold=-1;
    printf("Digite o número da matricula: ");
    scanf("%d",&buscmat);

    for(i=0;i<c;i++){
        if(buscmat==x[i].matricula){
            hold=i;
            break;
        }

    }
    if(hold==-1){
        printf("Matricula invalida!\nFechando programa\n");
        system("pause");
        exit(1);
    }
    return hold;
}

void imprimir_1aluno(cadastro x[],int c,int hold){
    printf("Matricula: %d\nNome: %s\nNota 1: %.1f\nNota 2: %.1f\nNota 3: %.1f\nMedia: %.2f\n\n",x[hold].matricula,x[hold].nome,x[hold].n[0],x[hold].n[1],x[hold].n[2],x[hold].media);
}

void editar(cadastro x[],int c,int hold){
    int check;
    printf("\nDeseja alterar a primeira nota:(1 p/ sim, 0 p/ não)\n");
    scanf("%d",&check);
    if(check==1){
        printf("Nota 1: ");
        scanf("%f",&x[hold].n[0]);
    }
    printf("\nDeseja alterar a segunda nota:(1 p/ sim, 0 p/ não)\n");
    scanf("%d",&check);
    if(check==1){
        printf("Nota 2: ");
        scanf("%f",&x[hold].n[1]);
    }
    printf("\nDeseja alterar a terceira nota:(1 p/ sim, 0 p/ não)\n");
    scanf("%d",&check);
    if(check==1){
        printf("Nota 3: ");
        scanf("%f",&x[hold].n[2]);
    }
    x[hold].media=(x[hold].n[0]+x[hold].n[1]+x[hold].n[2])/3;

    printf("Media e notas alteradas,\n");
}

int maior_nota(cadastro x[],int c){
    int i,hold=0;

    for(i=0;i<c;i++){
       if(x[i].media>x[hold].media){
            hold=i;
       }
    }
    return hold;
}

int menor_nota(cadastro x[],int c){
    int i,hold=0;

    for(i=0;i<c;i++){
       if(x[i].media<x[hold].media){
            hold=i;
       }
    }
    return hold;
}

void aprovacao(cadastro x[],int c){
    int i,aprov=0,reprov=0;
    float mediaf=0;

    for(i=0;i<c;i++){
        if(x[i].media>=6.0){ // checa se o aluno atual tem media maior q a media de aprovacao
            aprov++;
        }
        else{
            reprov++;
        }
    }
    for(i=0;i<c;i++){
    mediaf+=x[i].media;
    }
    mediaf/=c;

        printf("\nAprovados: %d\nReprovados: %d\nMedia Geral: %.2f\n\n",aprov,reprov,mediaf);

}

void select(cadastro x[],int c){
    int val;

    while(val!=0){
        printf("**************************************************\n                Trabalho Prático 1                \n**************************************************\n\nDigite:\n\n");
        printf("1 para imprimir todos os elementos do arranjo;\n2 para imprimir apenas os nomes dos alunos;\n3 para imprimir o nome dos alunos e sua respectiva nota final;\n4 para buscar por busca sequencial;\n5 imprimir os alunos ordenados por matricula;\n6 para editar as notas de um aluno;\n7 mostrar aluno com maior nota;\n8 mostrar aluno com menor nota\n9 para imprimir aprovação dos alunos e a media final;\n0 para sair do programa;\n\n");

        scanf("%d",&val);

        switch(val){
            case 0:

            break;

            case 1:
                imprimir_normal(x,c);
            break;

            case 2:
                imprimir_nomes(x,c);
            break;

            case 3:
                imprimir_media(x,c);
            break;

            case 4:
                imprimir_1aluno(x,c,buscseq(x,c));
            break;

            case 5:
                ordenar(x,c);
                imprimir_normal(x,c);
            break;

            case 6:
                editar(x,c,buscseq(x,c));
                imprimir_1aluno(x,c,buscseq(x,c));
            break;

            case 7:
                imprimir_1aluno(x,c,maior_nota(x,c));
            break;

            case 8:
                imprimir_1aluno(x,c,menor_nota(x,c));
            break;

            case 9:
                aprovacao(x,c);
            break;

            default:
                printf("Valor invalido!\nColoque outro valor.\n");
            break;
        }
    }
}

void novo_arquivo(cadastro x[],int c,float m){
    FILE *arq;
    int i;
    arq=fopen("alunos2","w");

    for(i=0;i<c;i++){
        fprintf(arq,"%d %s %.1f %.1f %.1f %.2f\n",x[i].matricula,x[i].nome,x[i].n[0],x[i].n[1],x[i].n[2],x[i].media);
    }
    fprintf(arq,"Média Final:%.2f",m);

    if(arq!=NULL){
        printf("Novo arquivo criado com sucesso!\n");
    }
    else{
        printf("Falha ao criar novo arquivo!\n");
    }
    fclose(arq);
}
