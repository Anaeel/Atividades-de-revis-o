#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Ativo {
    std::string ticket;
    int quantidade;
    double precoMedio;
};

void registrarCompra(std::vector<Ativo>& carteira);
void registrarVenda(std::vector<Ativo>& carteira);
void verSaldoAtivo(const std::vector<Ativo>& carteira);
void listarPatrimonio(const std::vector<Ativo>& carteira);
int buscarAtivo(const std::vector<Ativo>& carteira, const std::string& ticket);
int buscaBinaria(const std::vector<Ativo>& carteira, const std::string& ticket, int inicio, int fim);

int main() {
    std::vector<Ativo> carteira;
    int opcao;

    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Registrar compra\n";
        std::cout << "2. Registrar venda\n";
        std::cout << "3. Ver o saldo de um ativo (Busca por Ticket)\n";
        std::cout << "4. Listar patrimonio\n";
        std::cout << "5. Sair\n";
        std::cout << "Selecione uma opcao: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                registrarCompra(carteira);
                break;
            case 2:
                registrarVenda(carteira);
                break;
            case 3:
                verSaldoAtivo(carteira);
                break;
            case 4:
                listarPatrimonio(carteira);
                break;
            case 5:
                std::cout << "Saindo...\n";
                break;
            default:
                std::cout << "Opcao invalida!\n";
        }
    } while (opcao != 5);

    return 0;
}

void registrarCompra(std::vector<Ativo>& carteira) {
    std::string ticket;
    int quantidade;
    double valor;

    std::cout << "Digite o ticket do ativo: ";
    std::cin >> ticket;
    std::cout << "Digite a quantidade comprada: ";
    std::cin >> quantidade;
    std::cout << "Digite o valor do ativo: ";
    std::cin >> valor;

    int index = buscarAtivo(carteira, ticket);

    if (index != -1) {
        Ativo& ativo = carteira[index];
        ativo.precoMedio = ((ativo.precoMedio * ativo.quantidade) + (valor * quantidade)) / (ativo.quantidade + quantidade);
        ativo.quantidade += quantidade;
    } else {
        Ativo novoAtivo = {ticket, quantidade, valor};
        carteira.push_back(novoAtivo);
        std::sort(carteira.begin(), carteira.end(), [](const Ativo& a, const Ativo& b) {
            return a.ticket < b.ticket;
        });
    }

    std::cout << "Compra registrada com sucesso!\n";
}

void registrarVenda(std::vector<Ativo>& carteira) {
    std::string ticket;
    int quantidade;
    double valor;

    std::cout << "Digite o ticket do ativo: ";
    std::cin >> ticket;
    std::cout << "Digite a quantidade vendida: ";
    std::cin >> quantidade;

    int index = buscarAtivo(carteira, ticket);

    if (index != -1) {
        Ativo& ativo = carteira[index];
        if (ativo.quantidade >= quantidade) {
            ativo.quantidade -= quantidade;
            std::cout << "Venda registrada com sucesso!\n";
        } else {
            std::cout << "Erro: Quantidade insuficiente para venda.\n";
        }
    } else {
        std::cout << "Erro: Ativo nao encontrado.\n";
    }
}

void verSaldoAtivo(const std::vector<Ativo>& carteira) {
    std::string ticket;
    std::cout << "Digite o ticket do ativo: ";
    std::cin >> ticket;

    int index = buscarAtivo(carteira, ticket);

    if (index != -1) {
        const Ativo& ativo = carteira[index];
        std::cout << "Ticket: " << ativo.ticket << "\nQuantidade: " << ativo.quantidade << "\nPreco Medio: " << ativo.precoMedio << "\n";
    } else {
        std::cout << "Ativo nao encontrado.\n";
    }
}

void listarPatrimonio(const std::vector<Ativo>& carteira) {
    if (carteira.empty()) {
        std::cout << "Carteira vazia.\n";
        return;
    }

    for (const auto& ativo : carteira) {
        std::cout << "Ticket: " << ativo.ticket << "\nQuantidade: " << ativo.quantidade << "\nPreco Medio: " << ativo.precoMedio << "\n\n";
    }
}

int buscarAtivo(const std::vector<Ativo>& carteira, const std::string& ticket) {
    return buscaBinaria(carteira, ticket, 0, carteira.size() - 1);
}

int buscaBinaria(const std::vector<Ativo>& carteira, const std::string& ticket, int inicio, int fim) {
    if (inicio > fim) {
        return -1;
    }

    int meio = (inicio + fim) / 2;

    if (carteira[meio].ticket == ticket) {
        return meio;
    } else if (carteira[meio].ticket < ticket) {
        return buscaBinaria(carteira, ticket, meio + 1, fim);
    } else {
        return buscaBinaria(carteira, ticket, inicio, meio - 1);
    }
}
