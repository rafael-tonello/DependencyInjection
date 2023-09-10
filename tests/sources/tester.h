#ifndef __TESTER_H
#define __TESTER_H


#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <regex>
#include <fstream>
#include <mutex>
#include <future>

#define __TESTING__ //--> was defined in the makefile

using namespace std;
struct TestResult{
    bool result;
    string expected;
    string returned;
};

struct ObserverAndFilter{
    string filter;
    function<void(string, string, void*)> observer;
};

class Tester{
private:
    string testMsgPrefix = "";
public: //static
    //messagebus system (for more complex responses and behavior analysis)
    static mutex msgBusObserversLocker;
    static vector<ObserverAndFilter> msgBusObservers;
    static int addMsgBusObserver(function<void(string, string, void*)> observer, string prefix = "");
    static void msgBusNotify(string message, string argS = "", void* argV = NULL);
    static void delMsgObserver(int id);
    //this function waits for next message with message prefix (messagePrefix), preAction can be used to 
    //grant a execution of code imediatelly after add the observer and prevent loses of any message.
    static tuple<string, void*> msgBusWaitNext(string messagePrefix, function<void()> preAction = [](){});

    //globalTest result (for simple replicating responses)
    static string global_test_result;

    //these two properties is used to mains a counting of passed and failed tests
    static uint testsFailed;
    static uint testsPassed;

    //utils function to storage and read files 
    static void storeToFile(string fname, string content);
    static string loadFromFile(string fname, string defaultValue = "");

public:
    

    map<string, string> tags;
    void setTag(string tag, string value);
    string getTag(string tag, string defValue = "");

    virtual vector<string> getContexts() = 0;
    virtual void run(string context) = 0;

    void errorMessage(string message);

    void redMessage(string message);
    void greenMessage(string message);
    void yellowMessage(string message);
    void blueMessage(string message);
    void cyanMessage(string message);
    void brightMessage(string message);

    void disableStdout();
    void enableStdout();

    void setTestsMessagesPrefix(string prefix);

    void test(string desc, function<bool()> func, string passMessage = "", string failMessage = "");

    

    template <class T>
    void test(
        string desc, 
        function<T()> func, 
        T expected, 
        function<bool(T, T)> compareFunc = [](T c1, T c2)
        { 
            return c1 == c2;
        },  
        string passMessage = "", 
        string failMessage = ""
    );

    static int runTests(vector<Tester*> testers, int argc = 0, char* argv[] = NULL);



    /*void test(
        string desc, 
        function<Shared::DynamicVar()> func, 
        Shared::DynamicVar expected, 
        function<bool(Shared::DynamicVar, Shared::DynamicVar)> cmpFun = [](Shared::DynamicVar returned, Shared::DynamicVar expected){return returned.getString() == expected.getString();}
    )
    {
        auto ret = func();
        test(desc,
            [&](){
                return cmpFun(ret, expected);
            }, 
            "Expected '" + expected.getString() + "' and received '" + ret.getString()+"'", 
            "Expected '" + expected.getString() + "' but received '" + ret.getString()+"'"
        );
    }*/

    void test(
        string desc, 
        function<TestResult()> func
    );


};

/*
    Examples:
int testefunc(int v1, int v2)
{
    //return 2;
    return v1 + v2;
}


//obs: GuiTester implementes the class Tester
void GuiTester::run(string context)
{
    this->test("testeFunc(1, 2) must return 3", [](){
        return Shared::DynamicVar(testefunc(1, 2));
    }, Shared::DynamicVar(3));

    this->test("testeFunc(1, 1) must return 2", [](){
        return testefunc(1, 1) == 2;
    });

    this->test("testeFunc(1, 5) must return >= 6", [](){
        auto res = testefunc(1, 5);
        return TestResult {
            res >= 6,
            ">=6",
            to_string(res)
        };
    });
    
    this->test("testeFunc(1, 5) must return > 5", [](){
        auto res = testefunc(1, 5);
        return TestResult {
            res >= 5,
            ">=5",
            to_string(res)
        };
    });
}
*/

#endif