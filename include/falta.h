#ifndef FALTA_H
#define FALTA_H

#include <string>
#include <vector>

struct RegistroFalta {
    int idFuncionario;
    std::string data;
    std::string tipo;        // "Atestado", "Injustificada", "Advertencia"
    std::string observacao;  // motivo ou detalhe
};

void registrarFalta(std::vector<RegistroFalta>& faltas, int idFuncionario);
void listarFaltas(const std::vector<RegistroFalta>& faltas, int idFuncionario);
int contarFaltasInjustificadas(const std::vector<RegistroFalta>& faltas, int idFuncionario);
int calcularDiasTrabalhados(int diasUteisMes, const std::vector<RegistroFalta>& faltas, int idFuncionario);

#endif