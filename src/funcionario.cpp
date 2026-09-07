#include "../include/Funcionario.h"
#include <iostream>

void cadastrarFuncionario(std::vector<Funcionario>& funcionarios) {
    Funcionario novo;

    // id sequencial simples baseado no tamanho atual do vetor
    novo.id = funcionarios.size() + 1;

    std::cout << "\n--- Cadastro de Funcionario ---\n";
    std::cout << "Nome: ";
    std::cin.ignore();
    std::getline(std::cin, novo.nome);

    std::cout << "Cargo: ";
    std::getline(std::cin, novo.cargo);

    std::cout << "Departamento: ";
    std::getline(std::cin, novo.departamento);

    std::cout << "Salario base: ";
    std::cin >> novo.salarioBase;

    funcionarios.push_back(novo);

    std::cout << "Funcionario cadastrado com sucesso! ID: " << novo.id << "\n";
}

void listarFuncionarios(const std::vector<Funcionario>& funcionarios) {
    if (funcionarios.empty()) {
        std::cout << "\nNenhum funcionario cadastrado.\n";
        return;
    }

    std::cout << "\n--- Lista de Funcionarios ---\n";
    for (const Funcionario& f : funcionarios) {
        std::cout << "ID: " << f.id
                   << " | Nome: " << f.nome
                   << " | Cargo: " << f.cargo
                   << " | Departamento: " << f.departamento
                   << " | Salario base: " << f.salarioBase << "\n";
    }
}

Funcionario* buscarFuncionarioPorId(std::vector<Funcionario>& funcionarios, int id) {
    for (Funcionario& f : funcionarios) {
        if (f.id == id) {
            return &f;
        }
    }
    return nullptr;
}