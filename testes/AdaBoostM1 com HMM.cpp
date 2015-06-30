#include <iostream>
#include <vector>
#include <exception>
#include <iomanip>

#include "../classificador/classificador_provavel.h"
#include "../corpus/corpusmatriz.h"
#include "../treinador/treinador_provavel.h"
#include "../avaliador/avaliador_prob.h"
#include "../validador/validadorkdobras.h"
#include "../treinador/hmm.h"
#include "../classificador/classificadorhmm.h"

using namespace std;

int main()
{
    try
    {
    	int gabarito, minha_resposta;
    	
    	CorpusMatriz objCorpus;
    	
    	objCorpus.carregarArquivo( "../inputs/train.txt" );
    	gabarito = objCorpus.pegarPosAtributo("pos");
    	minha_resposta = objCorpus.criarAtributo("gabarito", "desconhecido");
    	
    	TreinadorAdaBoostM1 treinador(new HMM("word"), true, 10, "gabarito", "desconhecido");
    	Classificador* objClass = treinador.executarTreinamento( objCorpus, gabarito );
    	
    	objClass->executarClassificacao( objCorpusProva, minha_resposta );
    
       	AvaliadorProvavel vf;
        vector<float> percentual = vf.calcularDesempenho(objCorpus, gabarito, minha_resposta);

        cout << "Avaliacao executada, agora vamos aos resultados.\n";
        /*for (unsigned int i = 1; i < percentual.size(); ++i)
        {
            cout << "Frase " << i << ": " << 100*percentual[i] << endl;
        }*/
        cout << "RESULTADO: " << setprecision(4) << 100*percentual[0] << "%." << endl;

        cout << "\nExecutar a validação. Validador K-Dobras.\nDigite o número de experimentos: ";
        cin >> tab;
        ValidadorKDobras valid(vf, tab);
        vector<vector<float> > dobras = valid.executarExperimento(treinador, objCorpus, gabarito, minha_resposta);
        for (int i = 0; i <
        for (int i = 0; i < tab; i++)
        {
			cout << "Dobra " << i << ": " << setprecision(4) << 100*dobras[0][0] << "%." << endl;
        }
    }
    catch (string e)
    {
        cout << "ERRO: " << e << endl;
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }
    return 0;
}
