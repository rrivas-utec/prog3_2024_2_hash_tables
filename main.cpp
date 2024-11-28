#include <iostream>
#include <unordered_map>
#include <string>
#include <functional>
#include <cmath>

void example_unordered_map() {
    std::unordered_map<std::string, int> contacts;
    contacts.insert({"John Smith", 5211234});
    contacts.insert({"Lisa Smith", 5218976});
    contacts.insert({"Sam Doe", 5215030});
    contacts.insert({"Ted Baker", 4184165});
    contacts.insert({"Sandra Doe", 5219655});

    // Ubicar un elemento
    std::cout << contacts["Lisa Smith"] << std::endl;
    if (contacts.contains("Juan Perez"))
        std::cout << contacts["Juan Perez"] << std::endl;

    // Valor de m
    auto m = contacts.bucket_count();
    std::cout << m << std::endl;
    // valor de n
    auto n = contacts.size();
    std::cout << n << std::endl;
    // Factor de carga actual (n/m)
    std::cout << contacts.load_factor() << " " << static_cast<double>(n)/static_cast<double>(m) << std::endl;
    std::cout << contacts.max_load_factor() << std::endl;
    contacts.max_load_factor(2);
    std::cout << contacts.max_load_factor() << std::endl;
}

size_t division_hash(size_t pre_index, size_t m) {
    return pre_index % m;
}

size_t multiple_hash(size_t pre_index, size_t m) {
    auto a = (std::sqrt(5) - 1) / 2;
    return std::floor(std::fmod(static_cast<double>(pre_index) * a, 1.0) * static_cast<double>(m));
}

void example_prehashing_and_hashing() {
    std::string key = "John Smith";

    // Creando la funcion prehash
    std::hash<std::string> pre_hash_fun; // Objeto Funcion (Functor)

    // Obtener preindex
    auto pre_index = pre_hash_fun(key);
    std::cout << pre_index << std::endl;

    // Obtener el index
    size_t m = 13;
    std::cout << division_hash(pre_index, m) << std::endl;
    std::cout << multiple_hash(pre_index, m) << std::endl;
}

int main() {
//    example_prehashing_and_hashing();
    example_unordered_map();
    return 0;
}
