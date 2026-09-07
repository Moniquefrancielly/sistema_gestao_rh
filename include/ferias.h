#ifndef FERIAS_H
#define FERIAS_H

#include <string>
#include <vector>

struct RegistroFerias {
    int idFuncionario;
    std::string dataInicio;
    int diasRestantes;  // calculado com base na data atual
};

void agendarFerias(std::vector<RegistroFerias>& ferias, int idFuncionario);
void listarFerias(const std::vector<RegistroFerias>& ferias);
int calcularDiasRestantes(const std::string& dataInicio);
bool feriasProximas(int diasRestantes, int limiteDias);
std::vector<RegistroFerias> filtrarFeriasProximas(const std::vector<RegistroFerias>& ferias, int limiteDias);

#endif