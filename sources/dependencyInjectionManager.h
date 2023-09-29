/*
	Some usage examples

		Example1:
			DependencyInjectionManager dim;
			//two points to controller (to allow systems to find it by all it types):
			// the controller can be find by use of get<TheController> and get<ApiMediatorInterface>
			dim.addSingleton<TheController>(new TheController());
			dim.addSingleton<ApiMediatorInterface>(dim.get<TheController>());

			dim.addSingleton<PHOMAU>(new PHOMAU(5021, dim.get<ApiMediatorInterface>()));

		Example 2:
			DependencyInjectionManager dim;
			//another option is the use of names.. Names are very useful when services are requested inside modules.b
			dim.addSingleton<TheController>(new TheController(), {typeid(TheController).name(), typeid(ApiMediatorInterface).name()});
			dim.addSingleton<PHOMAU>(new PHOMAU(5021, dim.get<ApiMediatorInterface>(typeid(ApiMediatorInterface).name()));

	why the class use a string to find types instead of a type_info list
		
		the classes uses a string with names, instead a type_info list, to allow custom names to the objects. So you can
		uses type names (typeid(TheController).name() or your own names for the unities. If you optate to use custom names, I suggest
		you to use const string (only a suggestion).
		
*/

#ifndef _DEPENDENCY_INJECTION_MANAGER_H_
#define _DEPENDENCY_INJECTION_MANAGER_H_
#include <vector>
#include <map>
#include <functional>
#include <string>

#ifdef __TESTING__
    #include <tester.h>
#endif

//note, may use an Interface instead void*



using namespace std;

struct OnDemandInstance{
	function<void*()> createInstance;
	void* instance;
	string typesAndNames;
};

class DependencyInjectionManager{
private:
#ifdef __TESTING__
    public:
#endif
	static DependencyInjectionManager *_defaultInstance;

	int autoNameCount = 0;
	vector<OnDemandInstance> singletons;
	vector<OnDemandInstance> multiInstance;

	#ifdef __OBJECT_POOL__
	vector<OnDemandInstance> pools;
	#endif
public:
	
	~DependencyInjectionManager()
	{
		// for (auto &c: singletons)
		// {
		// 	if (c.instance != NULL)
		// 	{
		// 		//free(c.instance);
		// 		delete c.instance;
		// 	}
		// }
	}

	/// @brief add a new singleton using a function to create the object when it is first needed. As this function is not a template function, you should provide a name to recovery the object. This function is commonly used internally by the D/objectependencyInjectionManger
	/// @param createInstance a function that return a void* to a service/object
	/// @param addition/objectalTypesAndNames names used to identify the object/service
	/// @param instantiateImediately if true, the 'createFunction' will be called immediately.
	void addSingleton(function<void*()> createInstance, vector<string> additionalTypesAndNames = {}, bool instantiateImediately = false)
	{	
		OnDemandInstance p;
		p.createInstance = createInstance;
		p.instance = NULL;
		p.typesAndNames = "";
		for (auto c: additionalTypesAndNames)
			p.typesAndNames += c;
		
		if (instantiateImediately)
			p.instance = createInstance();
		
		singletons.push_back(p);
	}
	
	/// @brief Create a singleton service/object
	/// @tparam T The interface or the class of the object
	/// @param instance the instance o/objectf class that implements the interface (or calss) 'T'
	/// @param additionalTypesAndNames additional names to identify the object.
	template <class T>
	void addSingleton(T* instance, vector<string> additionalTypesAndNames = {})
	{
		additionalTypesAndNames.push_back(typeid(T).name());
		//TODO: pass instance as argument instead capturing it
		this->addSingleton([instance](){
			return (void*)instance;
		}, additionalTypesAndNames, true);
	}
	
	/// @brief Create a singleton service/object. The object will be created only the when the object is needed.
	/// @tparam T The Interface of class of the object
	/// @param createInstance A function that creates and returns the object
	/// @param additionalTypesAndNames Additional names to identify the object
	template <class T>
	void addSingleton(function<T*()> createInstance, vector<string> additionalTypesAndNames = {})
	{
		additionalTypesAndNames.push_back(typeid(T).name());
		//TODO: pass createInstance as argument instead capturing it
		this->addSingleton([createInstance](){
			return (void*)createInstance();
		}, additionalTypesAndNames, false);
	}	

	/// @brief Create a multi-intance (transiente) object. The object will be created every time when it is needed.
	/// @tparam T 
	/// @param createInstance The function that creates and returns the object
	/// @param additionalTypesAndNames Additional names to identify the object
	template <class T>
	void addMultiInstance(function<T*()> createInstance, vector<string> additionalTypesAndNames = {})
	{	
		OnDemandInstance p;
		p.createInstance = createInstance;
		p.instance = NULL;
		p.typesAndNames = typeid(T).name();
		for (auto c: additionalTypesAndNames)
			p.typesAndNames += c;
		
		multiInstance.push_back(p);
	}

	/// @brief Create a multi-intance (transiente) object. The object will be created every time when it is needed. This method redirects the execution to the 'addMultiInstance' method.
	/// @tparam T 
	/// @param createInstance The function that creates and returns the object
	/// @param additionalTypesAndNames Additional names to identify the object
	template <class T>
	void addTransient(function<T*()> createInstance, vector<string> additionalTypesAndNames = {})
	{
		addMultiInstance(createInstance, additionalTypesAndNames);
	}


	/// @brief Foreach over all services. Note that this function will note create any instance of the services, and will just
	/// retuns the information necessary to create the service. If the service is a singleton and is already created, you can access it on .instance
	// of the itens.
	/// @param fSingletons 
	/// @param fTransients 
	void foreachAll(function<void(OnDemandInstance& service)> fSingletons, function<void(OnDemandInstance& service)> fTransients)
	{
		for (auto &c: singletons)
			fSingletons(c);

		for (auto &c: multiInstance)
			fTransients(c);
	}

	vector<void*> getAllP(string typeOrName)
	{
		vector<void*> ret;
		foreachAll([&](OnDemandInstance& curr){
			if (curr.typesAndNames.find(typeOrName) != string::npos)
			{
				if (curr.instance == NULL)
					curr.instance = curr.createInstance();

				ret.push_back(curr.instance);
			}
		}, [&](OnDemandInstance& curr){
			if (curr.typesAndNames.find(typeOrName) != string::npos)
				ret.push_back(curr.createInstance());
		});

		return ret;
	}

	template <class T>
	vector<T*> getAll(string typeOrName)
	{
		vector<T*> result;
		void *tmp = getAllP(typeOrName);

		for (auto c: tmp)
			result.push_back((T*)curr);

		return result;
	}

	template <class T>
	vector<T*> getAll()
	{
		return get(typeid(T).name());
	}

	/// @brief Returns an object/service using a name. This function is commonly used internally by the DependencyInjectionManager
	/// @param typeOrName The name or identification of the object
	/// @return 
	void* getp(string typeOrName)
	{

		for (auto &c: singletons)
		{
			if (c.typesAndNames.find(typeOrName) != string::npos)
			{
				if (c.instance == NULL)
					c.instance = c.createInstance();

				return c.instance;
			}
		}

		for (auto &c: multiInstance)
		{
			if (c.typesAndNames.find(typeOrName) != string::npos)
				return c.createInstance();
		}
		
		return NULL;
	}


	/// @brief Returns an object/service, searching it using an id/name
	/// @tparam T The interface type of the object/service
	/// @param typeOrName the desired name/id
	/// @return 
	template <class T>
	T* get(string typeOrName)
	{
		void *tmp = getp(typeOrName);

		if (tmp == NULL)
			return NULL;
		
		return (T*)tmp;
	}

	/// @brief Returns an object/service
	/// @tparam T the interface type
	/// @return 
	template <class T>
	T* get()
	{
		string type = typeid(T).name();

		return get<T>(type);
	}

	/// @brief Checks if the DependencyInjectionManager (the current instance) contains a service (if is prepared to return the object of type T). The serach by the service is done using and id/name
	/// @param typeOrName the name/id
	/// @return 
	bool contains(string typeOrName)
	{
		for (auto &c: singletons)
		{
			if (c.typesAndNames.find(typeOrName) != string::npos)
			{
				return true;
			}
		}

		for (auto &c: multiInstance)
		{
			return true;
		}
		
		return false;
	}


	/// @brief Check if the Dependency Injection Manager (the current instance) contains a service definition. Th search is done using the Interface Type 'T'
	/// @tparam T The interface of the service
	/// @return 
	template <class T>
	bool contains()
	{
		string type = typeid(T).name();
		
		return contains<T>(type);
	}


	static DependencyInjectionManager *defaultInstanceP(){ if (_defaultInstance == nullptr) _defaultInstance = new DependencyInjectionManager(); return _defaultInstance; };
	static DependencyInjectionManager &defaultInstance(){ auto p = defaultInstanceP(); return *p;};

	

	#ifdef __OBJECT_POOL__
		template<class T>
		Pool<T> getPool();

		
	#endif
};

//#define DIM DependencyInjectionManager
using DIM = DependencyInjectionManager;




/*auto di = new DependencyInjectionManager();
di->addSingleton<IController>("controller", new Controller());

di->addSingleton<IAPI>("api", new API(di->get<IController>("controller")));

class IAPI{};
class API2: public IAPI{
public:
	IController controller;
	API2(DependencyInjectionManager* di)
	{
		this->controller = di->get<IController>("controller"); 
		
	}
}

di->addSingleton<IAPI>("api2", new API2(di));*/

//Automatically creates a service/object property and get the  respective value from a DependencyInjectionManagerObject
#define DimCtProp(dimObjectP, interface, propname) \
	interface* _##propname = nullptr;\
	interface * propname() {\
		if (_##propname == nullptr)\
			_##propname = dimObjectP.get<interface>();\
		return _##propname;\
	}

#define DimCtPropP(dimObjectP, interface, propname) \
	interface* _##propname = nullptr;\
	interface * propname() {\
		if (_##propname == nullptr)\
			_##propname = dimObjectP->get<interface>();\
		return _##propname;\
	}

///Automatically creates service/object property ang get its respective value from a DependencyInjectionManger object. The DIM Object should be available as "DependencyInjectionManager &dim" within the class
#define DimProp(interface, propname) \
	interface* _##propname = nullptr;\
	interface * propname() {\
		if (_##propname == nullptr)\
			_##propname = dim.get<interface>();\
		return _##propname;\
	}

#define DimPropP(interface, propname) \
	interface* _##propname = nullptr;\
	interface * propname() {\
		if (_##propname == nullptr)\
			_##propname = dim->get<interface>();\
		return _##propname;\
	}

///Defines a constructors that receives a DependencyInjectionManager& as parameter and creates (and sets) a class property for this DIM as "DependencyInjectionManager &dim"
#define DimCtor(className) protected: DependencyInjectionManager &dim; public className(DependencyInjectionManager &dim): dim(dim)
#define DimCtorP(className) protected: DependencyInjectionManager *dim; public className(DependencyInjectionManager *dim): dim(dim)


/*
Diprop and Dictor allow the 'automatically' get services from dim as follow:

class MyClass{
private:
    DimProp(ILogger, log);
    DimProp(IDatabase, db);

public:
    DimCtor(MyClass){

    }

};*/


///creates a service/object property and automatically get its respective values from the default instance of DependencyInjectioManager (DependencyInjectionManager::defaultIntancep())
#define DimDfProp(interface, propname) \
	interface* _##propname = nullptr;\
	interface &propname() {\
		if (_##propname == nullptr)\
			_##propname = DependencyInjectionManager::defaultInstance().get<interface>();\
		return *(_##propname);\
	}


#define DimDfPropP(interface, propname) \
	interface* _##propname = nullptr;\
	interface * propname() {\
		if (_##propname == nullptr)\
			_##propname = DependencyInjectionManager::defaultInstanceP()->get<interface>();\
		return _##propname;\
	}


#endif
