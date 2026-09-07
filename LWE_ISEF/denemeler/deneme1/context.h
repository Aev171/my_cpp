#include <utility>
#pragma once
#ifndef LWE_ISEF_CONTEXT_H
#define LWE_ISEF_CONTEXT_H

#endif //LWE_ISEF_CONTEXT_H

class LWE_CONTEXT {
public:
    int q = 0;
    int delta = 0;
    int dimension = 0;

    void setContext(int q, int dimension) {
        this->q = q;
        this->dimension = dimension;
        this->delta = q / 2;
    }

    bool isDone() {
        return q != 0 && dimension != 0;
    }
};
enum class Operation {
    POW,
    SUB,
    MUL,
    ADD,
    SUBC,
    MULC,
    ADDC,
    POWC
};

struct CipheredText {

    struct Process {


        void setModulus(int modulus) {
            this->modulus = modulus;
        }

        CipheredText add(CipheredText& left,CipheredText& right) {
            CipheredText result;
            for(int i=0;i<left.a.size();i++) {
                result.a.push_back((left.a[i] + right.a[i]) % modulus);
            }
            result.b=(left.b + right.b)%modulus;

            return result;
        }

        int modulus=0;
    };

    std::vector<int>a;
    int b;
    int message;
    Process process;
    int id;
    CipheredText islem( CipheredText& cipher,Operation& op) {
        if (op==Operation::ADD) {
            this->process.add(*this,cipher);
        }
    }

    CipheredText islem(int costant,Operation& op) {
        
    }
    double error;
};

struct NoiseContext {

    NoiseContext(const std::string& path)
        : file(path, std::ios::app)
    {
    }

    ~NoiseContext() {
        if (file.is_open())
            file.close();}

    void createVariable(const std::string& variable,
                        const CipheredText& cipher)
    {
        file <<"\n===== VARIABLE "<< variable<<"=====\n";

        file<<"ENC: "
             <<variable
             <<" -> c" << cipher.id
             <<" | message=" << cipher.message
             <<" | error=" << cipher.error
             <<'\n';
    }


    void decrypt(const std::string& variable,
                 const CipheredText& cipher)
    {
        file <<"DEC: "
             <<variable
             <<" | c" << cipher.id
             <<" | error=" << cipher.error
             <<'\n';}

    void add(const std::string& resultVariable,
             const std::string& leftVariable,
             const std::string& rightVariable,
             const CipheredText& left,
             const CipheredText& right)
    {
        double error = left.error + right.error;

        file <<"\n===== OPERATION " << resultVariable << " =====\n";

        file <<"ADD: "
             <<leftVariable << " + "
             <<rightVariable
             << " -> " << resultVariable
             << " | error=" << error
             <<'\n';}


    void sub(const std::string& resultVariable,
             const std::string& leftVariable,
             const std::string& rightVariable,
             const CipheredText& left,
             const CipheredText& right)
    {
        double error = left.error - right.error;

        file <<"\n===== OPERATION " << resultVariable << " =====\n";

        file <<"SUB: "
             << leftVariable << " - "
             << rightVariable
             << " -> " << resultVariable
             <<" | error=" << error
             << '\n';}


    void mul(const std::string& resultVariable,
             const std::string& leftVariable,
             const std::string& rightVariable,
             const CipheredText& left,
             const CipheredText& right)
    {
        double error =
            (left.message * right.error) +
            (left.error * right.message) +
            (left.error * right.error);

        file << "\n===== OPERATION " << resultVariable << " =====\n";

        file << "MUL: "
             << leftVariable << " * "
             <<rightVariable
             << " -> " << resultVariable
             << " | error=" << error
             <<'\n';
    }


    void pow(const std::string& resultVariable,
             const std::string& leftVariable,
             const std::string& rightVariable,
             const CipheredText& left,
             const CipheredText& right)
    {
        double error =
            std::pow(
                left.message + left.error,
                right.message + right.error)
            -
            std::pow(
                left.message,
                right.message);

        file << "\n===== OPERATION " << resultVariable << " =====\n";

        file <<"POW: "
             << leftVariable << " ^ "
             << rightVariable
             << " -> " << resultVariable
             << " | error=" << error
             << '\n';
    }

    void add(const std::string& resultVariable,
             const std::string& variable,
             int constant,
             const CipheredText& cipher)
    {
        double error = cipher.error;

        file << "\n===== OPERATION " << resultVariable << " =====\n";

        file << "ADDC: "
             << variable << " + "
             << constant
             << " -> " << resultVariable
             << " | error=" << error
             << '\n';
    }


    void sub(const std::string& resultVariable,
             const std::string& variable,
             int constant,
             const CipheredText& cipher)
    {
        double error = cipher.error;

        file << "\n===== OPERATION " << resultVariable << " =====\n";

        file << "SUBC: "
             << variable << " - "
             << constant
             << " -> " << resultVariable
             << " | error=" << error
             << '\n';
    }

    void mul(const std::string& resultVariable,
             const std::string& variable,
             int constant,
             const CipheredText& cipher)
    {
        double error = cipher.error * constant;

        file << "\n===== OPERATION " << resultVariable << " =====\n";

        file << "MULC: "
             << variable << " * "
             << constant
             << " -> " << resultVariable
             << " | error=" << error
             << '\n';
    }

    void pow(const std::string& resultVariable,
             const std::string& variable,
             int constant,
             const CipheredText& cipher)
    {
        double error =
            std::pow(
                cipher.message + cipher.error,
                constant
            )
            -
            std::pow(
                cipher.message,
                constant
            );

        file << "\n===== OPERATION " << resultVariable << " =====\n";

        file << "POWC: "
             << variable << " ^ "
             << constant
             << " -> " << resultVariable
             << " | error=" << error
             << '\n';
    }

    void bootstrap(const std::string& variable,
                   const CipheredText& cipher)
    {
        file << "\n===== BOOTSTRAP " << variable << " =====\n";

        file << "BOOTSTRAP: "
             << variable
             << " | c" << cipher.id
             << " | error=" << cipher.error
             << '\n';
    }


    void modSwitch(const std::string& variable,
                   const CipheredText& cipher)
    {
        file << "\n===== MODSWITCH " << variable << " =====\n";

        file << "MODSWITCH: "
             << variable
             << " | c" << cipher.id
             << " | error=" << cipher.error
             << '\n';
    }


    void keySwitch(const std::string& variable,
                   const CipheredText& cipher)
    {
        file << "\n===== KEYSWITCH " << variable << " =====\n";

        file << "KEYSWITCH: "
             << variable
             << " | c" << cipher.id
             << " | error=" << cipher.error
             << '\n';
    }

    void changeName(const std::string& newName,const std::string& oldName)
    {
        file << "\n===== NAME CHANGED" << newName << " =====\n";

        file << "name: "
             << oldName << " -----> "
             << newName
             << '\n';
    }
private:
    std::fstream file;
};


