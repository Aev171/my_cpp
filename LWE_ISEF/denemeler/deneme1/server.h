//
// Created by LENOVO on 4.09.2026.
//

#ifndef LWE_ISEF_SERVER_H
#define LWE_ISEF_SERVER_H

#endif //LWE_ISEF_SERVER_H
#include "client.h"
struct clientVector {
    std::string name;
    std::shared_ptr<client> ptr;
};

class server {
private:
    std::vector<clientVector> clients;

public:
    void addClient(const std::string& name, std::shared_ptr<client> ptr) {
        clients.push_back({name, ptr});
    }

    std::shared_ptr<client> getClient(const std::string& name) {
        for (const clientVector& c : clients) {
            if (c.name == name) {
                return c.ptr;
            }
        }

        return nullptr;
    }

    std::string getClient(int index) {
        int k=0;
        for (const clientVector& c : clients) {
            if (k == index) {
                return c.name;
            }
            k++;
        }

        return nullptr;
    }

    int cSize() {
        return clients.size();
    }
};

