#include <iostream>

struct ADescriptor {};
struct BDescriptor {};
struct CDescriptor {};

class A {
public:
    void Whoami() {
        std::cout << "A" << std::endl;
    }
};

class B {
public:
    void Whoami() {
        std::cout << "B" << std::endl;
    }
};

class C {
private:
    A a_;
    B b_;
public:
    C(A a, B b) : a_(a), b_(b) {
    }

    void Whoami() {
        std::cout << "C" << std::endl;
    }
};

template <typename TDescriptor>
struct Binding;

template <>
struct Binding<ADescriptor> {
    using TService = A;
};

template <>
struct Binding<BDescriptor> {
    using TService = B;
};

template <>
struct Binding<CDescriptor> {
    using TService = C;
    using TArgs = std::tuple<A, B>;
};

class Container {
public:
    template<typename TDescriptor>
    auto Resolve() -> decltype(auto) {
        using TBinding = Binding<TDescriptor>;
        using TService = typename TBinding::TService;

        TService service;

        return service;
    }
};

int main() {
    Container ioc;

    ioc.Resolve<ADescriptor>().Whoami();
    ioc.Resolve<BDescriptor>().Whoami();

    return 0;
}