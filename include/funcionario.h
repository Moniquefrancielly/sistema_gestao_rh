#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <string>
#include <vector>

struct Funcionario {
    int id;
    std::string nome;
    std::string cargo;
    std::string departamento;
    double salarioBase;
};

void cadastrarFuncionario(std::vector<Funcionario>& funcionarios);
void listarFuncionarios(const std::vector<Funcionario>& funcionarios);
Funcionario* buscarFuncionarioPorId(std::vector<Funcionario>& funcionarios, int id);
std::vector<Funcionario> filtrarPorDepartamento(const std::vector<Funcionario>& funcionarios, const std::string& departamento);

#endif