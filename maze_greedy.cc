//Daniel Sánchez Aleo 20521676H

#include <iostream>
#include <vector>
#include <limits>
#include <cstring>
#include <fstream>
#include <string>
using namespace std;
int maze_greedy(vector<vector<char>>& matriz){
    int filas = matriz.size();
    int columnas = matriz[0].size();
    int resultado = 1;
    int movimiento = 0;
    int i = 0;
    int j = 0;
    if (matriz[0][0] == '0')
    {
        return 0;
    }
    
    while ((i != filas-1 || j != columnas -1) && movimiento != -1)
    {
        if (i + 1 < filas && j + 1 < columnas && matriz[i+1][j+1] == '1') {
            matriz[i+1][j+1] = '*';
            i++;
            j++;
            resultado++;
        } else if (j + 1 < columnas && matriz[i][j+1] == '1') {
            matriz[i][j+1] = '*';
            j++;
            resultado++;
        } else if (i + 1 < filas && matriz[i+1][j] == '1') {
            matriz[i+1][j] = '*';
            i++;
            resultado++;
        } else{
            movimiento = -1;
        }
    }
    matriz[0][0] = '*';
    if (i == filas -1 && j == columnas - 1)
    {
        return resultado;
    }
    else{
        return 0;
    }
        
}
int encontrarF(int argc, char* argv[]){
    int pos = -1;
    for (int i = 1; i < argc; i++)
    {
        
        if (strcmp(argv[i], "-f") == 0)
        {
            if (i +1 > argc -1)
            {
                return -1;
            }
            pos = i;
            i++;
        }
    }
    return pos;
}

bool encontrarP2D(int argc, char* argv[]){
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--p2D") == 0)
        {
            return true;
        }
    }
    return false;
}

bool encontrarArgError(int argc, char* argv[]){

    for (int i = 1; i < argc; i++)
    {
        if ((strcmp(argv[i], "--p2D") != 0) && (strcmp(argv[i], "-f") != 0) && (strcmp(argv[i-1], "-f")))
        {
            return true;
        }
        
    }
    return false;
}
/////////////////////
//Leer el Laberinto//
/////////////////////
vector<vector<char>> leerMatrizDesdeArchivo(const string& nombreArchivo){
    int filas,columnas;
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "ERROR: missing filename." << endl;
        cerr << "Usage:" << endl;
        cerr << "maze_greedy  [--p2D] -f file" << endl;
        exit(1);  // Termina el programa si hay error
    }

    archivo >> filas >> columnas;  // Leer dimensiones
    archivo.ignore();  // Ignorar el resto de la línea

    vector<vector<char>> matriz(filas, vector<char>(columnas));

    // Leer la matriz de caracteres
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            archivo >> matriz[i][j];
        }
    }

    archivo.close();
    return matriz;
}

////////
//MAIN//
////////
int main(int argc, char* argv[]){
    if (argc < 3)
    {
        cerr << "Argumentos Incorrectos" << endl;
        cerr << "Usage:" << endl;
        cerr << "maze_greedy  [--p2D] -f file" << endl;
        return 1;
    }
    
    //Encontrar -f y subargumento
    int pos = encontrarF(argc,argv);
    if (pos == -1)
    {
        cerr << "Argumentos Incorrectos" << endl;
        cerr << "Usage:" << endl;
        cerr << "maze_greedy  [--p2D] -f file" << endl;
        return 1;
    }
    if (encontrarArgError(argc,argv))
    {
        cerr << "Argumentos Incorrectos" << endl;
        cerr << "Usage:" << endl;
        cerr << "maze_greedy  [--p2D] -f file" << endl;
        return 1;
    }
    
    //leemos el archivo te texto
    vector<vector<char>> matriz = leerMatrizDesdeArchivo(argv[pos+1]);
    int camino = maze_greedy(matriz);
    cout << camino << endl;

    //Si hay  "--p2D"
    if (encontrarP2D(argc,argv))
    {
        int filas = matriz.size();
        int columnas = matriz[0].size();

        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                cout << matriz[i][j];  // Imprimir cada elemento
            }
            cout << endl;  // Nueva línea al final de cada fila
        }
    }
    return 0;
}