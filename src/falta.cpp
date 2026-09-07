#include "Falta.h"
#include <iostream>
#include <algorithm>

void registrarFalta(std::vector<RegistroFalta>& faltas, int idFuncionario) {
    RegistroFalta nova;
    nova.idFuncionario = idFuncionario;

    std::cout << "\n--- Registro de Falta ---\n";
    std::cout << "Data (dd/mm/aaaa): ";
    std::cin >> nova.data;

    int opcao;
    std::cout << "Tipo de ocorrencia:\n";
    std::cout << "1 - Falta com atestado\n";
    std::cout << "2 - Falta injustificada\n";
    std::cout << "3 - Advertencia\n";
    std::cout << "Escolha: ";
    std::cin >> opcao;

    switch (opcao) {
        case 1:
            nova.tipo = "Atestado";
            break;
        case 2:
            nova.tipo = "Injustificada";
            break;
        case 3:
            nova.tipo = "Advertencia";
            break;
        default:
            std::cout << "Opcao invalida. Registrando como Injustificada.\n";
            nova.tipo = "Injustificada";
            break;
    }

    std::cout << "Observacao: ";
    std::cin.ignore();
    std::getline(std::cin, nova.observacao);

    faltas.push_back(nova);
    std::cout << "Registro adicionado com sucesso.\n";
}

void listarFaltas(const std::vector<RegistroFalta>& faltas, int idFuncionario) {
    std::cout << "\n--- Faltas e Advertencias ---\n";
    bool encontrou = false;

    for (const RegistroFalta& f : faltas) {
        if (f.idFuncionario == idFuncionario) {
            std::cout << f.data << " | " << f.tipo << " | " << f.observacao << "\n";
            encontrou = true;
        }
    }

    if (!encontrou) {
        std::cout << "Nenhum registro encontrado para este funcionario.\n";
    }
}

int contarFaltasInjustificadas(const std::vector<RegistroFalta>& faltas, int idFuncionario) {
    return std::count_if(
        faltas.begin(),
        faltas.end(),
        [idFuncionario](const RegistroFalta& f) {
            return f.idFuncionario == idFuncionario && f.tipo == "Injustificada";
        }
    );
}

int calcularDiasTrabalhados(int diasUteisMes, const std::vector<RegistroFalta>& faltas, int idFuncionario) {
    int injustificadas = contarFaltasInjustificadas(faltas, idFuncionario);
    int diasTrabalhados = diasUteisMes - injustificadas;

    if (diasTrabalhados < 0) {
        diasTrabalhados = 0;
    }

    return diasTrabalhados;
}