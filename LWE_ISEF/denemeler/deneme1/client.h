//
// Created by LENOVO on 3.09.2026.
//

#ifndef UNTITLED_DENEME1_H
#define UNTITLED_DENEME1_H
#include "baseInclude.h"
#include "context.h"

class client {
    public:
    client(std::shared_ptr<LWE_CONTEXT> context,std::string name):logID(nextId++),
    log(rootName+"/client" + std::to_string(id) + "Log.txt", std::ios::app),
    name(std::move(name)),context(std::move(context)),rd(),gen(rd()){

    }

    std::vector<int> randomVector() {
        std::vector<int> v;
        std::uniform_int_distribution<int> dist(
            0,context->q - 1);
        for (int i = 0; i < context->dimension; i++) {
            v.push_back(dist(gen));
        }
        return v;
    }
    int randomnoise() {
        std::uniform_int_distribution<int> dist(-3, 3);
        return dist(gen);
    }
    std::vector<int> getSecret() {
        return secretVector;
    }

    bool setSecret() {
        if (isCreated) {
            return false;
        }
        std::uniform_int_distribution<int> dist(0, 1);
        for (int i=0;i<context->dimension;i++) {
            secretVector.push_back(dist(gen));
        }
        isCreated=true;
        return true;
    }

    CipheredText encrypt(int message) {
        CipheredText c;
        c.id=id;
        this->id+=1;
        c.message=message;
        int error=randomnoise();
        std::vector<int> randomvector =randomVector();
        int b = std::inner_product(
    randomvector.begin(),
    randomvector.end(),
    secretVector.begin(),0);
        b+=error;
        b+=(message*context->delta);
        c.a=randomvector;
        b%=context->q;
        c.b=b;
        c.error=error;
        return c;
    }
    std::string name;
    private:
    std::vector<int> secretVector;
    std::random_device rd;
    std::mt19937 gen;
    std::shared_ptr<LWE_CONTEXT> context;
    int id=0;
    bool isCreated=false;
    std::unordered_map<std::string, CipheredText> variables;
    std::ofstream log;
    int logID=0;
    inline static int nextId = 0;
    const std::string rootName="C:/Users/LENOVO/CLionProjects/LWE_ISEF/denemeler/deneme1/logs";
    //C:/Users/LENOVO/CLionProjects/LWE_ISEF/ project directory
};


#endif //UNTITLED_DENEME1_H
