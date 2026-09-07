#ifndef SALARIO_H
#define SALARIO_H

#include <vector>
#include "Funcionario.h"

double calcularDescontoINSS(double salarioBruto);
double calcularDescontoIR(double salarioBruto);
double calcularSalarioProporcional(double salarioBase, int diasTrabalhados, int diasUteisMes);
double calcularSalarioLiquido(double salarioBase, int diasTrabalhados, int diasUteisMes);
double calcularFolhaTotal(const std::vector<Funcionario>& funcionarios);

#endif