#include "general.test.h"

GeneralTester::GeneralTester()
{

}

vector<string> GeneralTester::getContexts()
{
    return {"General"};
}

void GeneralTester::run(string context)
{
    if (context != "General") return;

    testSetAndGet();
    testMacros();
}

void GeneralTester::testSetAndGet()
{
    this->test("Set service", [](){
        class IService{ public: virtual string work() = 0; };
        class Service: public IService{ public: string work() override { return string("working"); }};

        DependencyInjectionManager *dim = new DependencyInjectionManager();

        dim->addTransient<IService>([](){ return new Service(); });

            return dim->multiInstance.size() == 1 && dim->multiInstance[0].typesAndNames.find("IService") != string::npos;
    });

    this->test("Get right service", [](){
        class IService{ public: virtual string work() = 0; };
        class Service: public IService{ public: string work() override { return string("working"); }};

        DependencyInjectionManager *dim = new DependencyInjectionManager();

        dim->addTransient<IService>([](){ return new Service(); });

        string result = dim->get<IService>()->work();
        delete dim;
        return TestResult{
            .result  = (result == string("working")),
            .expected = string("working"),
            .returned = result,
        };

    });

    this->test("Getting the right service", [](){
        class IService{ public: virtual string work() = 0; };
        class Service: public IService{ public: string work() override { return string("working"); }};

        DependencyInjectionManager *dim = new DependencyInjectionManager();

        dim->addTransient<IService>([](){ return new Service(); });

        auto result = dim->get<IService>();
        delete dim;

        return TestResult{
            .result  = (result != NULL),
            .expected = "!= NULL",
            .returned = to_string((uint64_t)((void*)result)),
        };

    });

    this->test("Getting the wrong service", [](){
        class IService{ public: virtual string work() = 0; };
        class IService2{ };
        class Service: public IService{ public: string work() override { return string("working"); }};

        DependencyInjectionManager *dim = new DependencyInjectionManager();

        dim->addTransient<IService>([](){ return new Service(); });

        auto result = dim->get<IService2>();
        delete dim;

        return TestResult{
            .result  = (result == NULL),
            .expected = "NULL",
            .returned = to_string((uint64_t)((void*)result)),
        };

    });

    this->test("Calling a service method", [](){
        class IService{ public: virtual string work() = 0; };
        class Service: public IService{ public: string work() override { return string("working"); }};

        DependencyInjectionManager *dim = new DependencyInjectionManager();

        dim->addTransient<IService>([](){ return new Service(); });

        string result = dim->get<IService>()->work();
        delete dim;
        return TestResult{
            .result  = (result == string("working")),
            .expected = string("working"),
            .returned = result,
        };
    });
 
}

void GeneralTester::testMacros()
{
    test("DimCtProp macro", [&](){
        class IService{ public: virtual string work() = 0; };
        class Service: public IService{ public: string work() override { return string("working"); }};

        class TmpClass{
        public:
            DIM &dim;

            DimCtProp(dim, IService, service);


            TmpClass(DIM &dim): dim(dim){}
            string doSomething()
            {
                return this->service()->work();
            }

        };
        DIM dim;
        dim.addSingleton<IService>(new Service());
        TmpClass *tmp = new TmpClass(dim);
        auto result = tmp->doSomething();
        delete tmp;

        return result == "working";
    });

    test("DimCtPropP macro", [&](){
        class IService{ public: virtual string work() = 0; };
        class Service: public IService{ public: string work() override { return string("working"); }};

        class TmpClass{
        public:
            DIM *dim;

            DimCtPropP(dim, IService, service);


            TmpClass(DIM *dim): dim(dim){}
            string doSomething()
            {
                return this->service()->work();
            }

        };
        DIM dim;
        dim.addSingleton<IService>(new Service());
        TmpClass *tmp = new TmpClass(&dim);
        auto result = tmp->doSomething();
        delete tmp;

        return result == "working";
    });

    test("DimDfProp macro", [&](){
        class IService{ public: virtual string work() = 0; };
        class Service: public IService{ public: string work() override { return string("working"); }};

        class TmpClass{
        public:
            DimDfProp(IService, service);

            string doSomething()
            {
                return this->service()->work();
            }

        };
        DIM::defaultInstance().addSingleton<IService>(new Service());

        TmpClass tmp;
        auto result = tmp.doSomething();

        return result == "working";
    });
}


