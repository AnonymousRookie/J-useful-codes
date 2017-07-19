#include <iostream>
#include <Calculator.h>
using namespace std;

#ifdef Z_USING_LIB

#ifdef NDEBUG
#pragma comment(lib, "../LibCalculator/static_release/LibCalculator.lib")
#else 
#ifdef _DEBUG
#pragma comment(lib, "../LibCalculator/static_debug/LibCalculator.lib")
#endif
#endif

#else

//#define Z_USING_DLL
#ifdef NDEBUG
#pragma comment(lib, "../LibCalculator/dll_release/LibCalculator.lib")
#else 
#ifdef _DEBUG
#pragma comment(lib, "../LibCalculator/dll_debug/LibCalculator.lib")
#endif
#endif


#endif

int main()
{
    z::Calculator calc;
    int ret = calc.add(1,2);
    cout << ret<< endl;


    int r = z::test(3);
    cout << r << endl;

    getchar();

    return 0;
}