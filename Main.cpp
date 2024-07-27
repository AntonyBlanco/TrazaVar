#include <iostream>
#include "./Trazados.h"
using namespace std;

int main(){
    cout << "Largo de varilla principal a cortar (mm): ";
    int c;
    cin >> c;
    cout << c << endl;

    cout << "Desgaste por corte (mm): ";
    int d;
    cin >> d;
    cout << d << endl;

    cout << "Cantidad de tipos de cortes: ";
    int n;
    cin >> n;
    cout << n << endl;
    
    int **piezas = new int*[n];
    for(int i = 0; i < n; i++){
        piezas[i] = new int[2];
        cout << "Tipo de corte 0" << (i+1) << ":" << endl;

        cout << "  Medida (mm): ";
        cin >> piezas[i][0];
        cout << piezas[i][0] << endl;
        piezas[i][0] += d;

        cout << "  Cantidad: ";
        cin >> piezas[i][1];
        cout << piezas[i][1] << endl;
    }

    cout << endl << "Largo maximo de residuo (mm): ";
    int rtMax;
    cin >> rtMax;
    cout << rtMax << endl;

    cout << endl << "Largo minimo de retazo (mm): ";
    int rtzMin;
    cin >> rtzMin;
    cout << rtzMin << endl;

    cout << endl;
    ProblemaCortes pr = ProblemaCortes((int**)piezas, n, c + d, d);
    pr.addIntervaloResto(0, rtMax);
    pr.addIntervaloResto(rtzMin, c);
    pr.calcularMenorDesperdicio();
    return 0;
}