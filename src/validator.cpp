#include "validator.h"
#include <algorithm>
#include <cctype>

//função para limpar caracteres que não sao numeros
std::string limparNumero(const std::string& entrada) {
    std::string limpo;
    for(char c : entrada) {
        if(std::isdigit(static_cast<unsigned char>(c))) {
            limpo += c;
        }
    }
    return limpo;
}

//função para receber cpf e retornar true se ele for correto
bool validarCPF(const std::string& cpfRecebido) {
    std::string cpf = limparNumero(cpfRecebido);

    if(cpf.length() != 11 || std::all_of(cpf.begin(), cpf.end(), [&](char c){ return c == cpf[0]; }))
        return false;

    auto calcularDigito = [&](int pesoInicial) {
        int soma = 0;
        for(int i = 0; i < pesoInicial -1; ++i) {
            soma += (cpf[i] - '0') * (pesoInicial - i);
        }
        int resto = soma % 11;
        return (resto < 2) ? 0 : 11 - resto;
    };

    return (cpf[9] - '0') == calcularDigito(10) && (cpf[10] - '0') == calcularDigito(11);
}

//função para receber cnpj e retornar true se ele for correto
bool validarCNPJ(const std::string& cnpjRecebido) {
    std::string cnpj = limparNumero(cnpjRecebido);

    if(cnpj.length() != 14 || std::all_of(cnpj.begin(), cnpj.end(), [&](char c){return c == cnpj[0]; }))
        return false;

    int pesos1[] = {5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};
    int pesos2[] = {6, 5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};

    auto calcDigito = [&](int pesos[], int tamanho) {
        int soma = 0;
        for (int i = 0; i < tamanho; ++i)
            soma += (cnpj[i] - '0') * pesos[i];
        int resto = soma % 11;
        return (resto < 2) ? 0 : 11 - resto;
    };

    return (cnpj[12] - '0') == calcDigito(pesos1, 12) &&
           (cnpj[13] - '0') == calcDigito(pesos2, 13);
}