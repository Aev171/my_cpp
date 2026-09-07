//
// Created by LENOVO on 5.09.2026.
//

#ifndef LWE_ISEF_PARSER_H
#define LWE_ISEF_PARSER_H

#endif //LWE_ISEF_PARSER_H
#include "client.h"
#include "server.h"



struct Parser {
    Parser(std::shared_ptr<LWE_CONTEXT> context)
        : context(std::move(context)) {}

    void parse(std::string& t) {
        this->text=t;
        if (text.find("nclient") != std::string::npos) { //nclient client_name
            size_t pos = text.find("nclient");
            std::string name = text.substr(pos + 8);
            auto c = std::make_shared<client>(context,name);
            server.addClient(name,c);

        }
        else if (text.find("creates") != std::string::npos) { //client_name: creates
            if (this->client_ptr!=nullptr) {
                this->client_ptr->setSecret();
            }

            else {
                std::cout <<"Lütfen istemci seçiniz -use"<<std::endl;
            }
        }
        else if (text.find("clients") != std::string::npos) {
            size_t pos = text.find("clients");
            for (int i = 0; i < server.cSize(); i++) {
                std::cout <<i<<". " <<server.getClient(i) << std::endl;
            }
        }

        else if (text.find("use") != std::string::npos) {
            size_t pos = text.find("use");
            std::string name = text.substr(pos + 4);
            this->client_ptr=server.getClient(name);
        }


    }

    void printPrompt() {
        if (client_ptr)
            std::cout << client_ptr->name << ": ";
        else
            std::cout << "> ";
    }
private:
    std::string text;
    Operation operation;
    std::variant<int,std::string>right;
    std::variant<int,std::string>left;
    server server;
    std::shared_ptr<LWE_CONTEXT> context;
    int id=1;
    std::string name;
    std::shared_ptr<client> client_ptr;

};