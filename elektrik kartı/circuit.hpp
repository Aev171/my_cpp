#pragma once
#include </home/c++_projcts/elektrik kartı/gates.hpp>
#include <functional>
#include <vector>
#include <tuple>
#include <iostream>

class circuit
{
public:
    template <typename First, typename... Rest>
    auto make_circuit(First first, Rest... rest)
    {
        constexpr std::size_t total_funcs = 1 + sizeof...(rest);

        return [=](const std::vector<int>& values) {
            if (values.size() != total_funcs + 1) {
                std::cerr << "Hatalı value sayısı! Beklenen: "
                          << (total_funcs + 1) << ", gelen: " << values.size() << std::endl;
                return -1;
            }

            
            auto result = first(values[0], values[1]);

           
            std::tuple<Rest...> rest_funcs(rest...);

            std::apply([&](auto&&... funcs) {
                int idx = 2;
                ((result = funcs(result, values[idx++])), ...);
            }, rest_funcs);

            return result;
        };
    }
};
