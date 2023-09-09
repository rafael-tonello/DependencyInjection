# Dependency Injetion Manger

This is a dependency injection manger I wrote to learn about and facilitade the dependency injection in some projects I working on. Basically, this library can be used to be a central place to store and recovery isntances of classes that implementing some interfaces in C++. You can, for example, get the 'official' instance of a service, that implement an specific interface, without take care about how the interface is implemented or even know who was implemented interface.

# How to use it

You should create an instance of DependencyInjection manger, set the transient or singleton instances of your services and pass this instance where services is needed.

Lets see some examples:

``` c++
class IMyServiceInterface{
public:
    virtual void doSomething() = 0;
    virtual string getSomething() = 0;
};

class MyService: public IMyServiceInterface{
public: 
    void doSomething()
    {
        cout << "A message was write to the stout" << endl;
    }

    string getSomething()
    {
        return string("Something");
    }
};

class This_class_needs_an_intance_of_IMyServiceInterface{
private:
    DependencyInjectionManger &dim;
public:
    This_class_needs_an_intance_of_IMyServiceInterface(DependencyInjectionManger &dim): dim(dim)
    {

    }

    void work()
    {
        //get service
        IMyServiceInterface  *service = dim.get<IMyServiceInterface>();

        //call some method from service
        service->doSomething();

        //call another mothod from service
        string somethingFromService = service->getSomething();
        cout << "Service returned '"+somethingFromService+"'" << endl;
    }

};

int main()
{
    DependencyInjectionManger dim();

    dim.addSingleton<IMyServiceInterface>(new MyService());

    This_class_needs_an_intance_of_IMyServiceInterface temp(dim);
    temp.work();
}
```


