# 🖥️ CPPeople

> Sistema de gestão de cadastros desenvolvido em **C++**, com integração direta a um banco de dados **MySQL** via WampServer.

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![MySQL](https://img.shields.io/badge/MySQL-4479A1?style=for-the-badge&logo=mysql&logoColor=white)
![Status](https://img.shields.io/badge/status-concluído-brightgreen?style=for-the-badge)

---

## 📌 Sobre o projeto

O **CPPeople** é um sistema de gestão de cadastros via terminal, com operações completas de **CRUD** (Create, Read, Update, Delete), conectado a um banco de dados relacional real. O projeto foi criado como exercício acadêmico para colocar em prática a integração entre **C++** e **MySQL**, cobrindo desde a configuração do ambiente de desenvolvimento até a persistência e manipulação de dados.

## ✨ Funcionalidades

- ✅ Conexão com banco de dados MySQL via `libmysql`
- ✅ Cadastrar cliente (nome, email, idade)
- ✅ Listar todos os clientes cadastrados
- ✅ Editar dados de um cliente existente
- ✅ Excluir cliente do banco
- ✅ Menu interativo via terminal
- ✅ Tratamento de erros de conexão e de operações no banco

## 🛠️ Tecnologias utilizadas

- **C++** — lógica da aplicação
- **MySQL** — persistência dos dados
- **WampServer** — ambiente local de banco de dados
- **Dev-C++ (TDM-GCC)** — compilador utilizado no desenvolvimento

## 🗂️ Estrutura do banco de dados

```sql
CREATE DATABASE IF NOT EXISTS sistema_clientes;

USE sistema_clientes;

CREATE TABLE clientes (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE,
    idade INT NOT NULL,
    criado_em TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

## ▶️ Como executar

### Pré-requisitos
- [WampServer](https://www.wampserver.com/) (ou outro servidor MySQL) instalado e rodando
- Compilador compatível com C++ (Dev-C++, g++, etc.)
- Biblioteca `mysql.h` configurada no compilador

### Passos

```bash
# Clone o repositório
git clone https://github.com/ItsmeEduu/CPPeople.git

# Entre na pasta do projeto
cd CPPeople

# Compile (ajuste os caminhos do MySQL conforme sua instalação)
g++ main.cpp -o CPPeople -IC:\wamp64\bin\mysql\mysql8.4.7\include -LC:\wamp64\bin\mysql\mysql8.4.7\lib -lmysql

# Execute
CPPeople.exe
```

> ⚠️ As DLLs `libmysql.dll`, `libssl-3-x64.dll` e `libcrypto-3-x64.dll` precisam estar na mesma pasta do executável.

## 📸 Demonstração

=== SISTEMA DE GESTÃO DE CADASTROS ===
1. Cadastrar Cliente
2. Listar Clientes
3. Editar Cliente
4. Excluir Cliente
5. Sair
Escolha uma opção: 1

Nome: Maria Silva
Email: maria.silva@exemplo.com
Idade: 28

[SUCESSO] Cliente cadastrado com sucesso!.


## 👨‍💻 Autor

**Eduardo Ferreira de Souza**
Estudante de Análise e Desenvolvimento de Sistemas — Universidade Cruzeiro do Sul

- 📧 E-mail: duduferreira09@gmail.com
- 💼 LinkedIn: [linkedin.com/in/itsmeeduu](https://www.linkedin.com/in/itsmeeduu)
- 🐙 GitHub: [github.com/ItsmeEduu](https://github.com/ItsmeEduu)

---
⭐ Se esse projeto te ajudou de alguma forma, deixe uma estrela no repositório!
