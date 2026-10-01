#include <iostream>
#include <winsock2.h>
#include "mysql.h"
#include <string>
#include <sstream>
#include <clocale>
#include <cstdlib>

using namespace std;

// CONFIGURAÇÕES DE ACESSO AO BANCO DE DADOS
const char* HOST = "localhost";
const char* USER = "root";
const char* PASSWORD = ""; // Deixe vazio se não tiver senha, ou coloque a sua
const char* DATABASE = "sistema_clientes";
const unsigned int PORT = 3306;

// PROTÓTIPOS (o compilador precisa conhecer as funções antes do main)
void cadastrarCliente(MYSQL* conn);
void listarClientes(MYSQL* conn);
void editarCliente(MYSQL* conn);
void excluirCliente(MYSQL* conn);

// Protege o texto digitado contra aspas e SQL injection
string escapar(MYSQL* conn, const string& texto) {
	string saida(texto.size() * 2 + 1, '\0');
	unsigned long n = mysql_real_escape_string(conn, &saida[0], texto.c_str(), texto.length());
	saida.resize(n);
	return saida;
}

// Confere se o ID digitado tem só números
bool idValido(const string& id) {
	if (id.empty()) return false;
	for (size_t i = 0; i < id.size(); i++) {
		if (id[i] < '0' || id[i] > '9') return false;
	}
	return true;
}

int main() {
	setlocale(LC_ALL, "portuguese");

	// montando a conexão com o banco de dados
	MYSQL* conn = mysql_init(NULL);

	if (!conn) {
		cout << "---[ERRO] Falha na inicialização do MySQL---" << endl;
		return 1;
	}

	if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, PORT, NULL, 0)) {
		cout << "---[ERRO] ao conectar ao banco de dados!--- " << mysql_error(conn) << endl;
		mysql_close(conn);
		system("pause");
		return 1;
	}

	mysql_set_character_set(conn, "latin1"); // acentos corretos no console do Windows

	cout << "---[SUCESSO] A Conexão foi estabelecida com sucesso!---" << endl;
	system("pause");

	int opcao = -1;
	do {
		system("CLS");
		cout << "=== SISTEMA DE GESTÃO DE CADASTROS ===" << endl;
		cout << "1. Cadastrar Cliente" << endl;
		cout << "2. Listar Clientes" << endl;
		cout << "3. Editar Cliente" << endl;
		cout << "4. Excluir Cliente" << endl;
		cout << "0. Sair" << endl;
		cout << "Escolha uma Opção: ";

		if (!(cin >> opcao)) {   // se digitar letra, não trava em loop infinito
			cin.clear();
			cin.ignore(1000, '\n');
			opcao = -1;
		} else {
			cin.ignore(1000, '\n');
		}

		switch (opcao) {
			case 1:
				cadastrarCliente(conn);
				break;
			case 2:
				listarClientes(conn);
				break;
			case 3:
				editarCliente(conn);
				break;
			case 4:
				excluirCliente(conn);
				break;
			case 0:
				cout << "\nSaindo do sistema, Até a próxima!" << endl;
				break;
			default:
				cout << "\n[ERRO] Opção Inválida!" << endl;
				system("pause");
		}

	} while (opcao != 0);

	mysql_close(conn);
	return 0;
}

void cadastrarCliente(MYSQL* conn) {
	system("CLS");
	string nome, telefone, email;

	cout << "=== CADASTRAR NOVO CLIENTE ===" << endl;
	cout << "Nome completo: ";
	getline(cin, nome);
	cout << "Telefone: ";
	getline(cin, telefone);
	cout << "E-mail: ";
	getline(cin, email);

	stringstream query;
	query << "INSERT INTO clientes (nome, telefone, email) VALUES ('"
	      << escapar(conn, nome) << "', '"
	      << escapar(conn, telefone) << "', '"
	      << escapar(conn, email) << "');";

	if (mysql_query(conn, query.str().c_str()) == 0) {
		cout << "\n===[SUCESSO!!] O cliente foi Cadastrado!===" << endl;
	} else {
		cout << "\n[ERRO] Falha ao cadastrar! " << mysql_error(conn) << " ---" << endl;
	}

	system("pause");
}

void listarClientes(MYSQL* conn) {
	system("CLS");
	cout << "=== LISTA DE CLIENTES CADASTRADOS ===" << endl;

	string query = "SELECT id, nome, telefone, email, DATE_FORMAT(data_cadastro, '%d/%m/%Y às %H:%i') FROM clientes;";

	if (mysql_query(conn, query.c_str())) {
		cout << "[ERRO] FALHA AO BUSCAR DADOS: " << mysql_error(conn) << " ---" << endl;
		system("pause");
		return;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (!res) {
		cout << "Nenhum Resultado Retornado. " << endl;
		system("pause");
		return;
	}

	MYSQL_ROW row;
	int total = 0;
	while ((row = mysql_fetch_row(res))) {
		total++;
		cout << "-----------------------------------" << endl;
		cout << "ID: " << row[0] << endl;
		cout << "Nome: " << row[1] << endl;
		cout << "Telefone: " << row[2] << endl;
		cout << "E-mail: " << row[3] << endl;
		cout << "Data de cadastro: " << row[4] << endl;
	}

	if (total == 0) cout << "Nenhum Cliente Cadastrado no sistema ainda." << endl;
	cout << "-----------------------------------" << endl;

	mysql_free_result(res);
	system("pause");
}

void editarCliente(MYSQL* conn) {
	system("CLS");
	string id, novoNome, novoTelefone, novoEmail;

	cout << "=== EDITAR CLIENTE ===" << endl;
	cout << "Digite o ID do cliente que deseja editar: ";
	getline(cin, id);

	if (!idValido(id)) {
		cout << "\n[ERRO] ID inválido! Digite apenas números." << endl;
		system("pause");
		return;
	}

	cout << "Novo nome completo: ";
	getline(cin, novoNome);
	cout << "Novo Telefone: ";
	getline(cin, novoTelefone);
	cout << "Novo E-mail: ";
	getline(cin, novoEmail);

	stringstream query;
	query << "UPDATE clientes SET nome='" << escapar(conn, novoNome)
	      << "', telefone='" << escapar(conn, novoTelefone)
	      << "', email='" << escapar(conn, novoEmail)
	      << "' WHERE id=" << id << ";";

	if (mysql_query(conn, query.str().c_str()) == 0) {
		if (mysql_affected_rows(conn) > 0)
			cout << "\n---[SUCESSO] Cliente Atualizado com sucesso---" << endl;
		else
			cout << "\n[AVISO] Nenhum cliente alterado (ID não existe ou dados iguais)." << endl;
	} else {
		cout << "\n[ERRO] FALHA AO ATUALIZAR " << mysql_error(conn) << " ----" << endl;
	}

	system("pause");
}

void excluirCliente(MYSQL* conn) {
	system("CLS");
	string id;

	cout << "=== EXCLUIR CLIENTE ===" << endl;
	cout << "Digite o ID do cliente que deseja EXCLUIR PERMANENTEMENTE: ";
	getline(cin, id);

	if (!idValido(id)) {
		cout << "\n[ERRO] ID inválido! Digite apenas números." << endl;
		system("pause");
		return;
	}

	stringstream query;
	query << "DELETE FROM clientes WHERE id=" << id << ";";

	if (mysql_query(conn, query.str().c_str()) == 0) {
		if (mysql_affected_rows(conn) > 0)
			cout << "\n[SUCESSO] Cliente Removido com sucesso!!" << endl;
		else
			cout << "\n[AVISO] Nenhum cliente com esse ID." << endl;
	} else {
		cout << "\n---[ERRO] Falha ao Excluir cliente: " << mysql_error(conn) << " ----" << endl;
	}

	system("pause");
}
