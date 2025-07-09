#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

bool validarCPF(const std::string& cpf);
bool validarCNPJ(const std::string& cnpj);
std::string limparNumero(const std::string& numero);


#endif