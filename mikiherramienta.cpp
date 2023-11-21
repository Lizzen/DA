#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Cordel {
    int longitud;
    int costo;
};

bool es_posible_formar_cuerda(int L, const vector<Cordel>& cordeles, vector<vector<int>>& memo) {
    if (L == 0) {
        return true;
    }

    if (memo[L][cordeles.size()] != -1) {
        return memo[L][cordeles.size()] == 1;
    }

    bool posible = false;

    for (const Cordel& cordel : cordeles) {
        if (cordel.longitud <= L && es_posible_formar_cuerda(L - cordel.longitud, cordeles, memo)) {
            posible = true;
            break;
        }
    }

    memo[L][cordeles.size()] = (posible ? 1 : 0);
    return posible;
}

int calcular_num_formas(int L, const vector<Cordel>& cordeles, vector<vector<int>>& memo) {
    if (L == 0) {
        return 1;
    }

    int num_formas = 0;

    for (const Cordel& cordel : cordeles) {
        if (cordel.longitud <= L) {
            num_formas += calcular_num_formas(L - cordel.longitud, cordeles, memo);
        }
    }

    return num_formas;
}

int calcular_min_num_cuerdas(int L, const vector<Cordel>& cordeles, vector<vector<int>>& memo) {
    if (L == 0) {
        return 0;
    }

    int& min_num_cuerdas = memo[L][cordeles.size()];

    if (min_num_cuerdas != -1) {
        return min_num_cuerdas;
    }

    min_num_cuerdas = INT_MAX;

    for (const Cordel& cordel : cordeles) {
        if (cordel.longitud <= L) {
            int num_cuerdas = 1 + calcular_min_num_cuerdas(L - cordel.longitud, cordeles, memo);
            min_num_cuerdas = min(min_num_cuerdas, num_cuerdas);
        }
    }

    return min_num_cuerdas;
}

int calcular_min_costo(int L, const vector<Cordel>& cordeles, vector<vector<int>>& memo) {
    if (L == 0) {
        return 0;
    }

    int& min_costo = memo[L][cordeles.size()];

    if (min_costo != -1) {
        return min_costo;
    }

    min_costo = INT_MAX;

    for (const Cordel& cordel : cordeles) {
        if (cordel.longitud <= L) {
            int costo = cordel.costo + calcular_min_costo(L - cordel.longitud, cordeles, memo);
            min_costo = min(min_costo, costo);
        }
    }

    return min_costo;
}

void construir_cometa(int N, const vector<vector<Cordel>>& casos_prueba) {
    for (int i = 0; i < N; ++i) {
        int L = casos_prueba[i][0].longitud;
        const vector<Cordel>& cordeles = casos_prueba[i];

        vector<vector<int>> memo(L + 1, vector<int>(cordeles.size() + 1, -1));

        if (es_posible_formar_cuerda(L, cordeles, memo)) {
            int num_formas = calcular_num_formas(L, cordeles, memo);
            int min_num_cuerdas = calcular_min_num_cuerdas(L, cordeles, memo);
            int min_costo = calcular_min_costo(L, cordeles, memo);

            cout << "SI " << num_formas << " " << min_num_cuerdas << " " << min_costo << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}

int main() {
    int N;
    cin >> N;

    vector<vector<Cordel>> casos_prueba;

    for (int i = 0; i < N; ++i) {
        int longitud_deseada, num_cordeles;
        cin >> longitud_deseada >> num_cordeles;

        vector<Cordel> cordeles(num_cordeles);
        for (int j = 0; j < num_cordeles; ++j) {
            cin >> cordeles[j].longitud >> cordeles[j].costo;
        }

        casos_prueba.push_back(cordeles);
    }

    construir_cometa(N, casos_prueba);

    return 0;
}
