# Validador API - CPF/CNPJ

Uma API simples feita em C++ com Crow, para validar documentos brasileiros (CPF e CNPJ), com uma interface HTML integrada para testes rápidos no navegador.

## Tecnologias Utilizadas

- **C++**
- **Crow** (Framework Web)
- **nlohmann/json** (Manipulação de JSON)
- **HTML + JavaScript** (Interface básica)
- **CMake** (Build System)
- **vcpkg** (Gerenciador de pacotes)

## Estrutura do Projeto

```
validador-api/
├── CMakeLists.txt
├── index.html
├── README.md
└── src/
    ├── main.cpp
    ├── validator.cpp
    └── validator.h
```

## ▶️ Como Rodar

### Pré-requisitos

- C++20 ou superior
- CMake
- vcpkg (instalado e configurado)

### Passos

1. Clone o repositório:

```bash
git clone https://github.com/seu-usuario/validador-api.git
cd validador-api
```

2. Instale as dependências:

```bash
vcpkg install crow nlohmann-json
```

3. Compile o projeto:

```bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[caminho_para_vcpkg]/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

4. Rode o servidor:

```bash
./build/validador-api
```

Acesse `http://localhost:8080` no navegador.

## 🔗 Interface Web

Você pode usar o arquivo `index.html` que já está no projeto para testar diretamente no navegador. Basta abrir o arquivo com um navegador e ele fará as requisições para o seu backend.

## Rota da API

### `POST /validar`

#### Corpo da Requisição

```json
{
  "documento": "123.456.789-09"
}
```

#### Resposta (Exemplo)

```json
{
  "Tipo": "CPF",
  "Valido": true
}
```

Ou, em caso de erro:

```json
{
  "erro": "Documento inválido"
}
```

## Autor

Pedro H. - Desenvolvedor C++

---

