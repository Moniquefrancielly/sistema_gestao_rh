#ifndef PONTO_H
#define PONTO_H

#include <string>
#include <vector>

struct RegistroPonto {
    int idFuncionario;
    std::string tipo;       // "Entrada" ou "Saida"
    std::string horario;    // capturado automaticamente
    std::string data;
};

std::string horarioAtual();
std::string dataAtual();
std::string gerarSenhaAleatoria();
bool confirmarSenha(const std::string& senhaGerada);
void baterPonto(std::vector<RegistroPonto>& registros, int idFuncionario, const std::string& tipo);
void listarRegistrosPonto(const std::vector<RegistroPonto>& registros, int idFuncionario);

#endif