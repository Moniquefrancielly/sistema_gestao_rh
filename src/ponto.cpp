#include "Ponto.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

std::string horarioAtual() {
    time_t agora = time(0);
    tm* ltm = localtime(&agora);

    char buffer[9];
    sprintf(buffer, "%02d:%02d:%02d", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    return std::string(buffer);
}

std::string dataAtual() {
    time_t agora = time(0);
    tm* ltm = localtime(&agora);

    char buffer[11];
    sprintf(buffer, "%02d/%02d/%04d", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
    return std::string(buffer);
}

std::string gerarSenhaAleatoria() {
    std::string senha = "";
    for (int i = 0; i < 5; i++) {
        char letra = 'A' + (rand() % 26);
        senha += letra;
    }
    return senha;
}

bool confirmarSenha(const std::string& senhaGerada) {
    std::string tentativa;
    int tentativas = 0;
    const int MAX_TENTATIVAS = 3;

    do {
        std::cout << "Digite a senha exibida na maquina: ";
        std::cin >> tentativa;
        tentativas++;

        if (tentativa == senhaGerada) {
            return true;
        } else {
            std::cout << "Senha incorreta. Tentativas restantes: "
                       << (MAX_TENTATIVAS - tentativas) << "\n";
        }
    } while (tentativas < MAX_TENTATIVAS);

    return false;
}

void baterPonto(std::vector<RegistroPonto>& registros, int idFuncionario, const std::string& tipo) {
    std::string senha = gerarSenhaAleatoria();
    std::cout << "\n--- Confirmacao de Ponto (" << tipo << ") ---\n";
    std::cout << "Senha da maquina: " << senha << "\n";

    if (confirmarSenha(senha)) {
        RegistroPonto novo;
        novo.idFuncionario = idFuncionario;
        novo.tipo = tipo;
        novo.horario = horarioAtual();
        novo.data = dataAtual();

        registros.push_back(novo);

        std::cout << tipo << " registrada as " << novo.horario
                   << " em " << novo.data << "\n";
    } else {
        std::cout << "Falha na confirmacao. Ponto NAO registrado.\n";
    }
}

void listarRegistrosPonto(const std::vector<RegistroPonto>& registros, int idFuncionario) {
    std::cout << "\n--- Registros de Ponto ---\n";
    bool encontrou = false;

    for (const RegistroPonto& r : registros) {
        if (r.idFuncionario == idFuncionario) {
            std::cout << r.data << " | " << r.tipo << " | " << r.horario << "\n";
            encontrou = true;
        }
    }

    if (!encontrou) {
        std::cout << "Nenhum registro encontrado para este funcionario.\n";
    }
}