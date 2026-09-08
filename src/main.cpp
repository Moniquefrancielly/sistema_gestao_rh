#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "Funcionario.h"
#include "Salario.h"
#include "Ponto.h"
#include "Falta.h"
#include "Ferias.h"

const int DIAS_UTEIS_MES = 22;  // valor fixo simplificado pro projeto

void exibirMenuPrincipal() {
    std::cout << "\n_________RH-LOJASBELLINY_________\n";
    std::cout << "1 - Acesso RH\n";
    std::cout << "2 - Acesso Funcionario\n";
    std::cout << "0 - Sair\n";
    std::cout << "___________________________________\n";
    std::cout << "Escolha uma opcao: ";
}

void exibirMenuRH() {
    std::cout << "\n______ MENU RH ______\n";
    std::cout << "1 - Cadastrar funcionario\n";
    std::cout << "2 - Listar funcionarios\n";
    std::cout << "3 - Registrar falta/advertencia\n";
    std::cout << "4 - Ver faltas de um funcionario\n";
    std::cout << "5 - Agendar ferias de um funcionario\n";
    std::cout << "6 - Ver folha de pagamento total\n";
    std::cout << "7 - Listar funcionarios por departamento\n";
    std::cout << "0 - Voltar\n";
    std::cout << "_______________________\n";
    std::cout << "Escolha uma opcao: ";
}

void exibirMenuFuncionario() {
    std::cout << "\n______ MEU PAINEL ______\n";
    std::cout << "1 - Bater ponto\n";
    std::cout << "2 - Ver meus registros de ponto\n";
    std::cout << "3 - Ver minhas faltas\n";
    std::cout << "4 - Ver meu salario liquido\n";
    std::cout << "5 - Ver minhas ferias\n";
    std::cout << "0 - Voltar\n";
    std::cout << "__________________________\n";
    std::cout << "Escolha uma opcao: ";
}

void menuRH(std::vector<Funcionario>& funcionarios,
            std::vector<RegistroFalta>& faltas,
            std::vector<RegistroFerias>& ferias) {

    int opcao;

    do {
        exibirMenuRH();
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                cadastrarFuncionario(funcionarios);
                break;

            case 2:
                listarFuncionarios(funcionarios);
                break;

            case 3: {
                int id;
                std::cout << "ID do funcionario: ";
                std::cin >> id;

                Funcionario* f = buscarFuncionarioPorId(funcionarios, id);
                if (f != nullptr) {
                    registrarFalta(faltas, id);
                } else {
                    std::cout << "Funcionario nao encontrado.\n";
                }
                break;
            }

            case 4: {
                int id;
                std::cout << "ID do funcionario: ";
                std::cin >> id;
                listarFaltas(faltas, id);
                break;
            }

            case 5: {
                int id;
                std::cout << "ID do funcionario: ";
                std::cin >> id;

                Funcionario* f = buscarFuncionarioPorId(funcionarios, id);
                if (f != nullptr) {
                    agendarFerias(ferias, id);
                } else {
                    std::cout << "Funcionario nao encontrado.\n";
                }
                break;
            }

            case 6: {
                double total = calcularFolhaTotal(funcionarios);
                std::cout << "\nFolha de pagamento total (bruta): R$ " << total << "\n";
                break;
            }

            case 7: {
                std::string departamento;
                std::cout << "Departamento: ";
                std::cin.ignore();
                std::getline(std::cin, departamento);

                std::vector<Funcionario> doDepartamento = filtrarPorDepartamento(funcionarios, departamento);
                listarFuncionarios(doDepartamento);
                break;
            }

            case 0:
                std::cout << "Voltando ao menu principal...\n";
                break;

            default:
                std::cout << "Opcao invalida. Tente novamente.\n";
                break;
        }

    } while (opcao != 0);
}

void menuFuncionario(std::vector<Funcionario>& funcionarios,
                      std::vector<RegistroPonto>& registrosPonto,
                      std::vector<RegistroFalta>& faltas,
                      std::vector<RegistroFerias>& ferias) {

    int id;
    std::cout << "\nDigite seu ID de funcionario: ";
    std::cin >> id;

    Funcionario* f = buscarFuncionarioPorId(funcionarios, id);

    if (f == nullptr) {
        std::cout << "ID nao encontrado. Volte e cadastre-se pelo RH primeiro.\n";
        return;
    }

    std::cout << "Bem-vindo(a), " << f->nome << "!\n";

    int opcao;

    do {
        exibirMenuFuncionario();
        std::cin >> opcao;

        switch (opcao) {
            case 1: {
                int tipoPonto;
                std::cout << "1 - Entrada | 2 - Saida: ";
                std::cin >> tipoPonto;
                std::string tipo = (tipoPonto == 1) ? "Entrada" : "Saida";
                baterPonto(registrosPonto, id, tipo);
                break;
            }

            case 2:
                listarRegistrosPonto(registrosPonto, id);
                break;

            case 3:
                listarFaltas(faltas, id);
                break;

            case 4: {
                int diasTrabalhados = calcularDiasTrabalhados(DIAS_UTEIS_MES, faltas, id);
                double liquido = calcularSalarioLiquido(f->salarioBase, diasTrabalhados, DIAS_UTEIS_MES);

                std::cout << "\n--- Meu Salario ---\n";
                std::cout << "Dias trabalhados: " << diasTrabalhados << "/" << DIAS_UTEIS_MES << "\n";
                std::cout << "Salario liquido: R$ " << liquido << "\n";
                break;
            }

            case 5: {
                std::vector<RegistroFerias> minhasFerias = filtrarFeriasPorFuncionario(ferias, id);
                std::cout << "\n--- Minhas Ferias ---\n";
                listarFerias(minhasFerias);
                break;
            }

            case 0:
                std::cout << "Voltando ao menu principal...\n";
                break;

            default:
                std::cout << "Opcao invalida. Tente novamente.\n";
                break;
        }

    } while (opcao != 0);
}

int main() {
    srand(time(0));  // essencial pra senha do ponto nao repetir

    std::vector<Funcionario> funcionarios;
    std::vector<RegistroPonto> registrosPonto;
    std::vector<RegistroFalta> faltas;
    std::vector<RegistroFerias> ferias;

    int opcao;

    do {
        exibirMenuPrincipal();
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                menuRH(funcionarios, faltas, ferias);
                break;

            case 2:
                menuFuncionario(funcionarios, registrosPonto, faltas, ferias);
                break;

            case 0:
                std::cout << "Encerrando o sistema...\n";
                break;

            default:
                std::cout << "Opcao invalida. Tente novamente.\n";
                break;
        }

    } while (opcao != 0);

    return 0;
}