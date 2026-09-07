#include "Ferias.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <sstream>

void agendarFerias(std::vector<RegistroFerias>& ferias, int idFuncionario) {
    RegistroFerias nova;
    nova.idFuncionario = idFuncionario;

    std::cout << "\n--- Agendar Ferias ---\n";
    std::cout << "Data de inicio (dd/mm/aaaa): ";
    std::cin >> nova.dataInicio;

    nova.diasRestantes = calcularDiasRestantes(nova.dataInicio);

    ferias.push_back(nova);
    std::cout << "Ferias agendadas com sucesso.\n";
}

int calcularDiasRestantes(const std::string& dataInicio) {
    int dia, mes, ano;
    char separador;

    std::istringstream ss(dataInicio);
    ss >> dia >> separador >> mes >> separador >> ano;

    tm dataFerias = {};
    dataFerias.tm_mday = dia;
    dataFerias.tm_mon = mes - 1;
    dataFerias.tm_year = ano - 1900;

    time_t tempoFerias = mktime(&dataFerias);
    time_t agora = time(0);

    double segundosRestantes = difftime(tempoFerias, agora);
    int diasRestantes = static_cast<int>(segundosRestantes / (60 * 60 * 24));

    return diasRestantes;
}

bool feriasProximas(int diasRestantes, int limiteDias) {
    return diasRestantes >= 0 && diasRestantes <= limiteDias;
}

std::vector<RegistroFerias> filtrarFeriasProximas(const std::vector<RegistroFerias>& ferias, int limiteDias) {
    std::vector<RegistroFerias> proximas;

    std::copy_if(
        ferias.begin(),
        ferias.end(),
        std::back_inserter(proximas),
        [limiteDias](const RegistroFerias& f) {
            return feriasProximas(f.diasRestantes, limiteDias);
        }
    );

    return proximas;
}

void listarFerias(const std::vector<RegistroFerias>& ferias) {
    std::cout << "\n--- Ferias Agendadas ---\n";

    if (ferias.empty()) {
        std::cout << "Nenhuma ferias agendada.\n";
        return;
    }

    for (const RegistroFerias& f : ferias) {
        std::cout << "Funcionario ID " << f.idFuncionario
                   << " | Inicio: " << f.dataInicio
                   << " | Dias restantes: " << f.diasRestantes << "\n";
    }
}