// Lambdas.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <functional>
#include <vector>
#include <span>

using namespace std;

class Button {
public:
    Button(std::function<void(void)> click) : handler_{ click } {}
    auto on_click() const { handler_(); }
private:
    std::function<void(void)> handler_{};
};

auto create_buttons()
{
    auto beep = Button([counter = 0]() mutable
    {
        std::cout << "Beep:" << counter << "! ";
        ++counter;
    });
    auto bop = Button([] { std::cout << "Bop. "; });
    auto silent = Button([] {});

    return std::vector<Button>{beep, bop, silent};
}

void lambdas_with_buttons()
{
    const auto& buttons = create_buttons();
    for (const auto& b : buttons) {
        b.on_click();
    }
    buttons.front().on_click(); // counter has been incremented
}

void nesting_lambda_expressions()
{
    // The following lambda expression contains a nested lambda
    // expression.
    int timestwoplusthree = [](int x)
    {
       return [](int y) { return y * 2; }(x)+3;
    }
    (5);

    // Print the result.
    std::cout << endl<< "timestwoplusthree produced:" <<  timestwoplusthree << endl;
}

void higher_order_lambda_expression()
{
    // The following code declares a lambda expression that returns
   // another lambda expression that adds two numbers.
   // The returned lambda expression captures parameter x by value.
    auto addtwointegers = [](int x) -> function<int(int)> {
        return [=](int y) { return x + y; };
    };

    // The following code declares a lambda expression that takes another
    // lambda expression as its argument.
    // The lambda expression applies the argument z to the function f
    // and multiplies by 2.
    auto higherorder = [](const function<int(int)>& f, int z) {
        return f(z) * 2;
    };

    // Call the lambda expression that is bound to higherorder.
    auto answer = higherorder(addtwointegers(7), 8);

    // Print the result, which is (7+8)*2.
    cout << answer << endl;
}

void Print(std::span<int, std::dynamic_extent> aSpan)
{
    cout << "Container is: ";
    for (auto i : aSpan)
    {
        cout << i << " ";
    }
    cout << endl;
}

template<class... Args>
std::vector<int> variadicFcn(Args... args)
{
    auto x = [args...] { return std::vector<int>{ args... }; };
    auto container = x();
    Print(container);

}


void size_of_lmbda()
{
    auto noCapture = []()
    {
        cout << " Lambda with no captures and no parameters" << endl;
        return 23;
    };
    noCapture();

    cout << "Sizeof( nopCapture ) is:" << sizeof(noCapture) << endl;

    int x = 9;
    auto someCapture = [&](int aVar)
    {
        return aVar * x;
    };
    std::cout << "Sizeof( someCapture ) is:" << sizeof(someCapture) << endl;
}

int main()
{
    std::cout << "Staring demo with C++ LAMBDAS!\n" << endl;

    //simplest lambda
    auto simplestLambda = []()
    { 
        static int k = 0;
        cout << "Hello from simplest Lambda  K=" << k++ << endl;
    };
    simplestLambda();
    simplestLambda();

    //capture by value
    int x = 10, y = 12, z = 67;

    auto captureByVal = [=]() {
        int res = x * y;
        cout << "captureByVal(): X * Y = " << res << endl;
    };
    x = 20;
    captureByVal();

    cout << endl;

    //capture by reference
    auto captureByRef = [&]() {
        int res = x * y;
        cout << "captureByRef(): X * Y = " << res << endl;
    };
    y = 30;
    captureByRef();

    cout << endl;

    //mutableLambda
    auto mutableLambda = [x = 8]() mutable
    {
        cout << "in mutableLambda() X = " << x << endl;
        x++;
    };
    mutableLambda();

    cout << endl;

    //deduced returnedType
    auto deducedReturnedRype = []()  /* ->float */
    {
        int x = 78;
        cout << "deducedReturnedRype() will return: " << x << endl;
        return x;
    };
    int res = deducedReturnedRype(); res;

    cout << endl;

    //variadicFunction
    variadicFcn(2, 3, 4);






    cout << endl << endl;

    lambdas_with_buttons();


    std::cout << endl;
    nesting_lambda_expressions();

    std::cout << endl;
    higher_order_lambda_expression();
    
    std::cout << endl;
    size_of_lmbda();
}