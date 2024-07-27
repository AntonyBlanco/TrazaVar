// Autor: Blanco Trujillo Antony Jacob
// Fecha: 07 - 01 - 2023

#include <iostream>
#include <vector>
using namespace std;

// ProblemaCortes busca resolver el problema de obtener los cortes pedidos
// quedando con el menor retazo posible
class ProblemaCortes{
    private:
        vector<int*> combinaciones;
        vector<int> combsRetazos;
        vector<vector<int*>> soluciones;
        vector<vector<int>> retazosSoluciones;
        // guarda en una tabla las combinaciones posibles
        // para realizar los cortes
        void calcularCombinacionesPosibles(){
            int piezas[cantTiposPiezas];
            for(int i = 0; i < cantTiposPiezas; i++) piezas[i] = 0;
            recurCalcularCombsPosibles(piezaPrincipal, piezas, 0);
            // Ordenar orden creciente segun el desperdicio generado
            int combsLen = combsRetazos.size();
            for(int i = 0; i < combsLen - 1; i++){
                for(int j = 0; j < combsLen - i - 1; j++){
                    if(combsRetazos[j] > combsRetazos[j+1]){
                        int tmp = combsRetazos.at(j);
                        combsRetazos.at(j) = combsRetazos.at(j+1);
                        combsRetazos.at(j+1) = tmp;
                        int *tmpArr = combinaciones.at(j);
                        combinaciones.at(j) = combinaciones.at(j+1);
                        combinaciones.at(j+1) = tmpArr;
                    }
                }
            }

            calcularSoluciones(combinaciones, combsRetazos);
            
            // START DEBUG
            /*cout << "Combinaciones de una sola varilla posibles: [" << endl;
            for(int i = 0; i < combsLen; i++){
                if(i != 0) cout << "," << endl;
                cout << "\t" << combinacionToString(combinaciones[i], combsRetazos[i]);
            }
            cout << endl << "]" << endl;*/
            cout << "Leyenda: [" << endl;
            cout << "Medida de corte\t  |  Cantidad" << endl;
            for(int i = 0; i < cantTiposPiezas; i++){
                if(i != 0) cout << endl;
                cout << "\t" << (piezas_cortes[i][0] - this->desgasteCorte) << "mm\t  |\t" << piezas_cortes[i][1];
            }
            cout << endl << "]" << endl;
            int solsLen = soluciones.size();
            cout << "Soluciones posibles (" << solsLen << "): [" << endl;
            for(int i = 0; i < solsLen; i++){
                if(i != 0) cout << "," << endl;
                cout << "\tSolución " << (i + 1) << ": [\n";
                cout << solucionToString(soluciones.at(i), retazosSoluciones.at(i));
                cout << "\n\t]";
            }
            cout << endl << "]" << endl;
            // END DEBUG

        }
        string solucionToString(vector<int*> sol, vector<int> rtzSol){
            int solLen = rtzSol.size();
            string str = "";
            for(int i = 0; i < solLen; i++){
                if(i != 0) str.append(",\n");
                str.append("\t\t");
                str.append(arrToString(sol.at(i), cantTiposPiezas));
                str.append(" | Resto (mm): " + to_string(rtzSol.at(i)));
            }
            return str;
        }
        void recurCalcularCombsPosibles(int resto, int piezas[], int index){
            //int (*piezasA)[cantTiposPiezas] = (int(*)[cantTiposPiezas])(piezas); // DEBUG
            // Verifica si no hay un resto menor posible para la actual combinacion
            bool restoMenor = true;
            for(int i = 0; i < cantTiposPiezas; i++){
                if(resto >= piezas_cortes[i][0]){
                    restoMenor = false;
                    if(i >= index){
                        piezas[i]++;
                        recurCalcularCombsPosibles(resto - piezas_cortes[i][0], piezas, i);
                        piezas[i]--;
                    }
                }
            }
            if((restoMenor && false) || (cantidadMax(piezas) && restoValido(resto))){
                int *tmpArr = new int[cantTiposPiezas];
                for(int j = 0; j < cantTiposPiezas; j++)
                    tmpArr[j] = piezas[j];
                combinaciones.push_back(tmpArr);
                combsRetazos.push_back(resto);
            }
        }
        bool restoValido(int resto){
            //resto <= maxRetazo;
            for(auto i = rangosResto.cbegin(); i != rangosResto.cend(); ++i)
                if(resto >= (*i)[0] && resto <= (*i)[1]) return true;
            return false;
        }
        void calcularSoluciones(vector<int*> combinaciones, vector<int> combsRetazos){
            // Variables temporales para calcular la suma presente total de las cantidades de cada medida
            int actualSum[cantTiposPiezas];
            vector<int> actualSumMatriz;
            for(int i = 0; i < cantTiposPiezas; i++) actualSum[i] = 0;
            recurCalcularSols(combinaciones, combsRetazos, actualSum, actualSumMatriz, 0);
        }
        void recurCalcularSols(vector<int*> combs, vector<int> combsRtzs, int* actualSum, vector<int> actSumMat, int index){
            bool combsFinal = true;
            for(int i = 0; i < cantTiposPiezas; i++)
                if(actualSum[i] != piezas_cortes[i][1]){
                    combsFinal = false;
                    break;
                }
            if(combsFinal){
                if(this->limitarSoluciones && this->retazosSoluciones.size() >= this->maxSoluciones){
                    int actSumMatLen = actSumMat.size();
                    vector<int*> tmpMat;
                    vector<int> tmpRtzVec;
                    int solsLen = soluciones.size();
                    int lenPeorSol = 0;
                    int indicePeor = 0;
                    for(int i = 0; i < solsLen; i++){
                        if(soluciones.at(i).size() > lenPeorSol){
                            lenPeorSol = soluciones.at(i).size();
                            indicePeor = i;
                        }
                    }
                    if(actSumMat.size() < lenPeorSol){
                        // Quitar peor solucion
                        cout << "Solucion considerada a cambiar" << endl;
                        soluciones.erase(soluciones.begin() + indicePeor);
                        retazosSoluciones.erase(retazosSoluciones.begin() + indicePeor);

                        for(int i = 0; i < actSumMatLen; i++){
                            int* tmpArr = new int[cantTiposPiezas];
                            for(int j = 0; j < cantTiposPiezas; j++)
                                tmpArr[j] = combs[actSumMat.at(i)][j];
                            tmpMat.push_back(tmpArr);
                            tmpRtzVec.push_back(combsRtzs.at(actSumMat.at(i)));
                        }
                        soluciones.push_back(tmpMat);
                        retazosSoluciones.push_back(tmpRtzVec);
                    }
                }else{
                    int actSumMatLen = actSumMat.size();
                    vector<int*> tmpMat;
                    vector<int> tmpRtzVec;
                    for(int i = 0; i < actSumMatLen; i++){
                        int* tmpArr = new int[cantTiposPiezas];
                        for(int j = 0; j < cantTiposPiezas; j++)
                            tmpArr[j] = combs[actSumMat.at(i)][j];
                        tmpMat.push_back(tmpArr);
                        tmpRtzVec.push_back(combsRtzs.at(actSumMat.at(i)));
                    }
                    soluciones.push_back(tmpMat);
                    retazosSoluciones.push_back(tmpRtzVec);
                }
                return;
            }
            int combsLen = combsRtzs.size();
            for(int i = index; i < combsLen; i++){
                bool adicionValida = true;
                for(int k = 0; k < cantTiposPiezas; k++)
                    if(combs[i][k] + actualSum[k] > piezas_cortes[k][1])
                        adicionValida = false;
                if(adicionValida){
                    for(int k = 0; k < cantTiposPiezas; k++)
                        actualSum[k] += combs[i][k];
                    actSumMat.push_back(i);
                    recurCalcularSols(combs, combsRtzs, actualSum, actSumMat, i);
                    if(this->soluciones.size() > this->maxSoluciones)
                        return;
                    for(int k = 0; k < cantTiposPiezas; k++)
                        actualSum[k] -= combs[i][k];
                    actSumMat.pop_back();
                }
            }
        }

        // Verifica que solo se considere aquellas combinaciones que contengan una cantidad
        // menor o igual de las que se piden
        bool cantidadMax(int* piezas){
            for(int i = 0; i < cantTiposPiezas; i++)
                if(piezas[i] > piezas_cortes[i][1]) return false;
            return true;
        }
        string combinacionToString(int* combinacion, int combRetazo){
            string str = "";
            str.append(arrToString(combinacion, cantTiposPiezas));
            str.append(" | Resto (mm): " + to_string(combRetazo));
            return str;
        }
        string arrToString(int *arr, int n){ // DEBUG FUNCTION
            string s = "[";
            for(int i = 0; i < n; i++){
                if(i != 0) s += ", ";
                s += to_string(arr[i]);
            }
            s += "]";
            return s;
        }
    public:
        void calcularMenorDesperdicio(){
            calcularCombinacionesPosibles();
            // Algoritmo voraz similar a problema de la mochila
            
        }
    private:
        int** piezas_cortes;
        int cantTiposPiezas;
        int piezaPrincipal;
        vector<int*> rangosResto;
        int maxSoluciones;
        bool limitarSoluciones;
        int desgasteCorte;
    public:
        ProblemaCortes(int** pc, int ctp, int pp, int dc){
            this->piezas_cortes = pc;
            this->cantTiposPiezas = ctp;
            this->piezaPrincipal = pp;
            this->maxSoluciones = 10;
            this->limitarSoluciones = true;
            this->desgasteCorte = dc;
        }
        void addIntervaloResto(int min, int max){
            rangosResto.push_back(new int[2]{min, max});
        }
};