#include <crow.h>
#include "validator.h"
#include <nlohmann/json.hpp>
#include <filesystem>

int main() {

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([] {
        std::ifstream html("../index.html");

        if (!html.is_open()) {
            std::cerr << "[ERRO] Não achou index.html no diretório: "
                      << std::filesystem::current_path() << std::endl;
            return crow::response(404, "Arquivo index.html NÃO encontrado");
        }

        std::stringstream buffer;
        buffer << html.rdbuf();
        html.close();

        crow::response res(buffer.str());
        res.set_header("Content-Type", "text/html");
        return res;
    });



    CROW_ROUTE(app, "/validar").methods(crow::HTTPMethod::Post)(
    [](const crow::request& req) {
        crow::response res;
        try {
            auto body = nlohmann::json::parse(req.body);
            std::string documento = body.value("documento", std::string{});

            if(documento.empty()) {
                res.code = 400;
                res.body = R"({"error": "Campo 'documento' e obrigatorio."})";
                return res;
            }

            std::string numero = limparNumero(documento);
            nlohmann::json resposta;

            if(numero.length() == 11) {
                resposta["Tipo"] = "CPF";
                resposta["Valido"] = validarCPF(numero);
                std::cout << "RETORNO DA FUNCAO VALIDAR CPF: " << validarCPF(numero) << '\n';
            }else if(numero.length() == 14) {
                resposta["Tipo"] = "CNPJ";
                resposta["Valido"] = validarCNPJ(numero);
                std::cout << "RETORNO DA FUNCAO VALIDAR CNPJ: " << validarCNPJ(numero) << '\n';
            }else {
                res.code = 400;
                res.body = R"({"error": "Campo 'documento' e obrigatorio."})";
                return res;
            }

            res.code = 200;
            res.body = resposta.dump();
            res.set_header("Content-Type", "application/json");
        }catch(const std::exception& e) {
            res.code = 500;
            res.body = std::string(R"({"erro": ")") + e.what() + R"("})";
        }

        return res;
    });

    std::cout << "Servidor rodando na porta http://localhost:8080" << '\n';
    app.port(8080).multithreaded().run();
    return 0;
}