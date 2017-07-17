/************************************************************************
* CREATED TIME: 2017-7-17 20:21:57
* LAST MODIFIED TIME: 2017-7-17 20:21:57
* DESCRIPTION: 内部辅助类
* BY: 357688981@qq.com
************************************************************************/

#include <iostream>
using namespace std;

namespace z {
    namespace base {
        // Internal helper class that prevent copy constructor for class
        // detail When using this class simply inherit it privately
        class NoCopy {
        protected:
            NoCopy(void) {}
        private:
            NoCopy(const NoCopy&);
            NoCopy& operator=(const NoCopy&);
        };


        // Internal helper class that makes all default constructors private.
        // This prevents initializing class making it static unless an explicit constructor is declared.
        // When using this class simply inherit it privately
        class StaticClass {
        private:
            StaticClass(void);
            StaticClass(const StaticClass&);
            StaticClass& operator=(const StaticClass&);
        };
    }
}


class A : z::base::NoCopy {
public:
    A() {}
    ~A(){}
};

class B : z::base::StaticClass {
public:
    static void show(int i) {
        cout << i << endl;
    }
    static const int pp = 123;
};

int main() {
    return 0;
}