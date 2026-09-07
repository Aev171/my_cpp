//
// Created by LENOVO on 4.09.2026.
//

#include "parser.h"

int main() {
    std::shared_ptr<LWE_CONTEXT> context;
    std::string text;
    Parser parser(context);
    while (true) {
        parser.printPrompt();
        std::getline(std::cin,text);
        if (text == "q") {
            break;
        }

        if (context->isDone()) {
            //devam

        }

        else {
            std::cout << "Lütfen yeni bir context oluşturun: " << std::endl;
        }
    }
}
