#include "tester.h"


string Tester::global_test_result = "";
uint Tester::testsFailed = 0;
uint Tester::testsPassed = 0;
mutex Tester::msgBusObserversLocker;
vector<ObserverAndFilter> Tester::msgBusObservers;

void Tester::setTag(string tag, string value){tags[tag] = value;}
string Tester::getTag(string tag, string defValue){if (tags.count(tag) > 0) return tags[tag]; else return defValue;}

void Tester::errorMessage(string message){ cerr << "\e[0;31m        " << "'"<< message << "\e[0m" << endl; }

void Tester::redMessage(string message){ cout << "\e[0;31m        " << message << "\e[0m" << endl; }
void Tester::greenMessage(string message){ cout << "\e[0;32m        " << message << "\e[0m" << endl; }
void Tester::yellowMessage(string message){ cout << "\e[0;33m        " << message << "\e[0m" << endl; }
void Tester::blueMessage(string message){ cout << "\e[0;34m        " << message << "\e[0m" << endl; }
void Tester::cyanMessage(string message){ cout << "\e[0;96m        " << message << "\e[0m" << endl; }
void Tester::brightMessage(string message){ cout << "\e[0;97m        " << message << "\e[0m" << endl; }

void Tester::disableStdout()
{
    std::cout.setstate(std::ios_base::failbit);
    std::cerr.setstate(std::ios_base::failbit);
}

void Tester::enableStdout()
{
    std::cout.clear();
    std::cerr.clear();
}



void Tester::setTestsMessagesPrefix(string prefix){this->testMsgPrefix = prefix;};

void Tester::test(string desc, function<bool()> func, string passMessage, string failMessage){
    if (func())
    {
        Tester::testsPassed++;
        cout << "\e[0;32m"<< "        " << testMsgPrefix << "[✔]" <<  "'"<< desc <<"' PASSED";
        if (passMessage != "")
            cout << ": " << passMessage;
        cout << "\e[0m" << endl;
    }
    else
    {
        Tester::testsFailed++;

        string message = "        " + string(testMsgPrefix) +string("[✘]") +  string("'") + string(desc) + string("' FAILED");
        if (failMessage != "")
            message += ": " + failMessage;

        cerr << "\e[0;31m" << message << "\033[0m" << endl;
    }
}

template <class T>
void Tester::test(
    string desc, 
    function<T()> func, 
    T expected, 
    function<bool(T, T)> compareFunc,
    string passMessage,
    string failMessage
)
{
    T r = func();

    test(desc, [&](){
        return compareFunc(r, expected);
    }, passMessage, failMessage);
}

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

void Tester::test(
    string desc, 
    function<TestResult()> func
)
{
    auto ret = func();
    test(desc,
        [&](){
            return ret.result;
        }, 
        "\n            "+string(testMsgPrefix)+"Expected '" + ret.expected + "'\n            "+string(testMsgPrefix)+"Received '" + ret.returned+"'", 
        "\n            "+string(testMsgPrefix)+"Expected '" + ret.expected + "'\n            "+string(testMsgPrefix)+"Received '" + ret.returned+"'" 
    );
}

void Tester::storeToFile(string fname, string content)
{
    if (fname.find("/") != string::npos)
    {
        //ensure that folder exists
        string fdir = fname.substr(0, fname.find_last_of('/'));
        system(string("mkdir -p " + fdir).c_str());
    }
                
    
    ofstream f(fname);
    f << content;
    f.close();
}

string Tester::loadFromFile(string fname, string defaultValue)
{
    ifstream a = ifstream(fname);
    string result = defaultValue;
    if (a.is_open())
    {
        a >> result;
        a.close();
    }

    return result;
}

int Tester::addMsgBusObserver(function<void(string, string, void*)> observer, string prefix)
{
    int ret = -1;
    msgBusObserversLocker.lock();
    ret = msgBusObservers.size();
    msgBusObservers.push_back(ObserverAndFilter{prefix, observer});
    msgBusObserversLocker.unlock();
    return ret;
}

void Tester::msgBusNotify(string message, string argS , void* argV)
{
    for (auto &c: msgBusObservers)
    {
        if ((c.filter == "") || (message.find(c.filter) == 0))
            c.observer(message, argS, argV);
    }
}

void Tester::delMsgObserver(int id)
{
    msgBusObservers[id] = ObserverAndFilter{"---------------------", [](string m, string a, void* v){}};
}

tuple<string, void*> Tester::msgBusWaitNext(string messagePrefix, function<void()> preAction)
{
    promise<tuple<string, void*>> prom;
    auto fut = prom.get_future();

    addMsgBusObserver([&](string msg, string payloadS, void* payloadV){
        tuple<string, void*> r;
        std::get<0>(r) = payloadS;
        std::get<1>(r) = payloadV;
        prom.set_value(r);
    }, messagePrefix);

    preAction();
    return fut.get();
}


int Tester::runTests(vector<Tester*> testers, int argc, char* argv[])
{
    cout << "Test results:" << endl;
    vector<string> args;
    for (int c = 0; c < argc; c++) args.push_back(string(argv[c]));

    //raises the contexts of the testers and gruoup them by specifcs contexts
    map<string, vector<Tester*>> contexts;// = {"all", {}};
    vector<string> contextsRunOrder;

    for (auto &c: testers)
    {
        
        auto testerContexts = c->getContexts();
        for (auto &c2: testerContexts)
        {
            if (contexts.count(c2) == 0)
            {
                contexts[c2] = {};
                contextsRunOrder.push_back(c2);
            }
            
            contexts[c2].push_back(c);
        }

        //sets ta special tag in the tester indicating that it is not runned yet. This tag will be used to prevent call more one time a tester.
        //c->setTag("main.tested", "false");
    }

    //identify required contexts (or all if no one is informed)
    //calls the testers according to the required contexts

    //checks if user needs help
    if (args.size() > 1 &&  args[1].find(string("-h")) != string::npos)
    {
        //shows the available context and an example of usage

        cout << "This is a test program. It is make to run tests in the code of another program. You can pass some contexts to run a limited test or use the "
                << "special context 'all' to run all tests." << endl
                << "Avaibale contexts are: "<< endl
                << "    all" << endl;
                for (auto &c: contexts)
                    cout << "    " << c.first << endl;


        return 0;
    }

    function<void(string context)> runContext = [&](string context){
        if (contexts.count(context) > 0)
        {
            for (auto &c: contexts[context])
                c->run(context);
        }
        else
            cerr << "        Context '" << context << "' has not found" << endl;

    };

    if (args.size() == 1 || (args.size() == 2 && args[1] == "all"))
        for (auto &c : contextsRunOrder)
        {
            cout << "    Context " << c << ":" << endl;
            runContext(c);
        }

    else
        for (size_t c =1; c < args.size(); c++)
        {
            cout << "    Context " << args[c] << ":" << endl;
            runContext(args[c]);
        }

    cout << endl << "Final statistics: "<< to_string(Tester::testsPassed + Tester::testsFailed) <<" tests perfomed, where " << Tester::testsPassed << " passed and " << Tester::testsFailed << " failed." << endl;;


    return Tester::testsFailed;
}