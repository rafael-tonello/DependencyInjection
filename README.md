# Dependency Injetion Manger

This is a dependency injection manger I wrote to learn about and facilitade the dependency injection in some projects I working on. Basically, this library can be used to be a central place to store and recovery isntances of classes that implementing some interfaces in C++. You can, for example, get the 'official' instance of a service, that implement an specific interface, without take care about how the interface is implemented or even know who was implemented interface.

You can referer to main class as DependencyInjectionManger or DIM (an using that points to DependencyInjectionManager class)

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

# Macros

As you can see, the DIM helps a lot to working with services in a cpp project, but getting these services from the DIM instance is yet a bit workfull. To solve this, the library contains some macros that automates the getting services process. Bellow, these macros will be discussed in more details

## The macro DimCtProp

The macro DimCtProp is a macro that can automatically expandes the code of definition and getting a service from a DIM instance. DimCtProp comes from "DIM Custom Prop". You can use a custom name for a pointer do a DIM isntance.
The macro signature is: DimCtProp(dimObjectP, propname, interface)

```cpp
class MyClass{
private:
    //the Dependency Injection Manager isntance
    DIM &theDimInstance;

    //services properties
    DimCtProp(theDimInstance, IDataBase, db)

    MyClass(DIM& dimInstance): theDimInstance(dimInstance){

    }
};

```
the code above will generate the following:
```cpp
class MyClass{
private:
    //the Dependency Injection Manager isntance
    DIM &theDimInstance;

    //services properties
    IDataBase* _db = nullptr;
	IDataBase * db() {
		if (_db == nullptr)
			_db = theDimInstance.get<IDatabase>();
		return _db;
    }

    MyClass(DIM& dimInstance): theDimInstance(dimInstance){
        
    }
}
```

The macro DimCtProp works with a reference to DIM instance. But there is a version of this macro that works with a pointer instead a reference (* instead &). This macro just have an additional 'P' letter at the end of the macro name: DimCtPropP. To use it, you just need to change de DIM& to DIM*:

```cpp
class MyClass{
private:
    //LOOK Here, you needs to use a pointer instead a reference
    DIM *theDimInstance;

    //services properties
    DimCtPropP(theDimInstance, IDataBase, db)

    MyClass(DIM* dimInstance): theDimInstance(dimInstance){
        
    }
};
```
the code above will generate the following:
```cpp
class MyClass{
private:
    //the Dependency Injection Manager isntance
    DIM *theDimInstance;

    //services properties
    IDataBase* _db = nullptr;
	IDataBase * db() {
		if (_db == nullptr)
			_db = theDimInstance->get<IDatabase>(); //in this line, 'theDimInstance->' is used in place of 'theDimInstance.' of the previous example
		return _db;
    }

    MyClass(DIM* dimInstance): theDimInstance(dimInstance){
        
    }
}

```

## The macro DimDfProp
Until here, we see how to use create and use a new instance of the DIM library. This is very useful and allow you to create more than one instance of DIM. But, most of time we need only one instance of the DIM for our whole program.

For these cases, the DIM already have an internal defaultInstance method that returns, as it suggests, a default instance of the DependencyInjectionManager class.

```cpp
    //reference to the default instance
    DIM &dimRef = DIM::defaultInstance();

    //pointer to the default instance
    DIM *dimPointer = DIM::defaultInstanceP(); 
```

With this is mind, the macro DimDfPropP can be explained.

This macro allow to creates service/object properties and get their respectives values from the default DIM Instance. Is this case, you do not need to pass a reference or instance to the DIM object you are using to store services/objects:

```cpp
class MyClass{
private:
    DimDfProp(IDatabase, db);
    DimDfProp(ILogger, log);
    DimDfProp(IMyAnotherService, otherService);
}
```
the code above will generate the following:

```cpp
class MyClass{
private:
	IDatabase* _db = nullptr;
	IDatabase * db() {
		if (_db == nullptr)
			_db = DependencyInjectionManager::defaultInstance().get<IDatabase>();
		return _db;
	}

	ILogger* _log = nullptr;
	ILogger * log() {
		if (_log == nullptr)
			_log = DependencyInjectionManager::defaultInstance().get<ILogger>();
		return _log;
	}

    IMyAnotherService* _otherService = nullptr;
	IMyAnotherService * otherService() {
		if (_otherService == nullptr)
			_otherService = DependencyInjectionManager::defaultInstance().get<IMyAnotherService>();
		return _otherService;
    }
}
```