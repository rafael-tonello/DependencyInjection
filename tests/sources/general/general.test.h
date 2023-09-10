#ifndef _CONTROLLER_TEST_H_
#define _CONTROLLER_TEST_H_

#include <tester.h>
#include <dependencyInjectionManager.h>

using namespace std;

class GeneralTester: public Tester{
private:
    void testSetAndGet();
    void testMacros();
public:

    GeneralTester(); 
public:
    /*Tester 'interface'*/
    vector<string> getContexts();
    void run(string context);
};

#endif