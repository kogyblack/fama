#include <iostream>
#include <fstream>

#include "../../../treinador/treinador.h"
#include "../../../treinador/adaboost.h"
#include "../../../stump/stump.h"
#include "../../../classificador/classificador.h"
#include "../../../corpus/corpusmatriz.h"
#include "../../../avaliador/avaliador_acuracia.h"
#include "../../../validador/validadorkdobras.h"

using namespace std;


int main()
{
    vector<string> atributos, classes;
    int atributo, novoatributo, c;
    Classificador *cl;//,*cl2;

    float media;

    //carrega conjunto de dados
    CorpusMatriz objCorpus(atributos, ',', true, true);
    objCorpus.carregarArquivo( "../../../inputs/adult.data.medium" );
    atributo = objCorpus.pegarPosAtributo("resposta");

    classes.push_back("<=50K");
    classes.push_back(">50K");

    atributos = objCorpus.pegarAtributos();
    atributos.pop_back();

    //treina
    DecisionStump stump(atributos,classes);
    TreinadorAdaboost adab(stump, classes, 30);

    cl = adab.executarTreinamento(objCorpus, atributo);
    cout << cl->descricaoConhecimento() << endl;
    cl->gravarConhecimento("xpto");

//    cl2 = new ClassificadorMaisEsperto;
    cl->carregarConhecimento("xpto");

    //classifica
    novoatributo = objCorpus.criarAtributo("me");
//    cl2->executarClassificacao(objCorpus, novoatributo);
    cl->executarClassificacao(objCorpus, novoatributo);

    objCorpus.gravarArquivo("#testeout.txt");

    //avalia
    AvaliadorAcuracia objAvalAcur;
    cout << 100 * objAvalAcur.calcularDesempenho(objCorpus, atributo, novoatributo)[0] << "%\n";

    //faz experimento
    int ndobras = 10;
    ValidadorKDobras objValidador(objAvalAcur, ndobras);
    vector< vector< float > > v = objValidador.executarExperimento(adab, objCorpus, atributo, novoatributo);

    media = 0;
    for (c=0;c<ndobras;c++){
        cout << c << " - " << v[c][0] << "\n";
        media += v[c][0];
    }
    cout << "*" << media/ndobras << "\n";

    return 0;
}
