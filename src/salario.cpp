#include "Salario.h"
#include <numeric>
#include <algorithm>

double calcularDescontoINSS(double salarioBruto) {
    const double TETO = 8475.55;
    double base = std::min(salarioBruto, TETO);
    double desconto = 0.0;

    // Faixa 1: até 1621,00 -> 7,5%
    if (base > 0) {
        double faixa = std::min(base, 1621.00);
        desconto += faixa * 0.075;
    }
    // Faixa 2: 1621,01 a 2902,84 -> 9%
    if (base > 1621.00) {
        double faixa = std::min(base, 2902.84) - 1621.00;
        desconto += faixa * 0.09;
    }
    // Faixa 3: 2902,85 a 4354,27 -> 12%
    if (base > 2902.84) {
        double faixa = std::min(base, 4354.27) - 2902.84;
        desconto += faixa * 0.12;
    }
    // Faixa 4: 4354,28 a 8475,55 (teto) -> 14%
    if (base > 4354.27) {
        double faixa = base - 4354.27;
        desconto += faixa * 0.14;
    }

    return desconto;
}

double calcularDescontoIR(double baseCalculo) {
    if (baseCalculo <= 2428.80) {
        return 0.0;
    } else if (baseCalculo <= 2826.65) {
        return baseCalculo * 0.075 - 182.16;
    } else if (baseCalculo <= 3751.05) {
        return baseCalculo * 0.15 - 394.16;
    } else if (baseCalculo <= 4664.68) {
        return baseCalculo * 0.225 - 675.49;
    } else {
        return baseCalculo * 0.275 - 908.73;
    }
}

double calcularSalarioProporcional(double salarioBase, int diasTrabalhados, int diasUteisMes) {
    if (diasUteisMes <= 0) {
        return 0.0;
    }
    double valorPorDia = salarioBase / diasUteisMes;
    return valorPorDia * diasTrabalhados;
}

double calcularSalarioLiquido(double salarioBase, int diasTrabalhados, int diasUteisMes) {
    double bruto = calcularSalarioProporcional(salarioBase, diasTrabalhados, diasUteisMes);
    double inss = calcularDescontoINSS(bruto);
    double baseIR = bruto - inss;  // IR incide sobre o valor já descontado o INSS
    double ir = calcularDescontoIR(baseIR);
    return bruto - inss - ir;
}

double calcularFolhaTotal(const std::vector<Funcionario>& funcionarios) {
    return std::accumulate(
        funcionarios.begin(),
        funcionarios.end(),
        0.0,
        [](double acumulado, const Funcionario& f) {
            return acumulado + f.salarioBase;
        }
    );
}