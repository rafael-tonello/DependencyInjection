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
			//another option is the use of names.. Names are very useful when services are requested inside modules.
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
	
	///Pre instantiated singletons. Very util to create hosted services.
	template <class T>
	void addSingleton(T* instance, vector<string> additionalTypesAndNames = {})
	{
		additionalTypesAndNames.push_back(typeid(T).name());
		//TODO: pass instance as argument instead capturing it
		this->addSingleton([instance](){
			return (void*)instance;
		}, additionalTypesAndNames, true);
	}
	
	///Create the singleton only when needed
	template <class T>
	void addSingleton(function<T*()> createInstance, vector<string> additionalTypesAndNames = {})
	{
		additionalTypesAndNames.push_back(typeid(T).name());
		//TODO: pass createInstance as argument instead capturing it
		this->addSingleton([createInstance](){
			return (void*)createInstance();
		}, additionalTypesAndNames, false);
	}	

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

	
	template <class T>
	T* get(string typeOrName)
	{
		for (auto &c: singletons)
		{
			if (c.typesAndNames.find(typeOrName) != string::npos)
			{
				if (c.instance == NULL)
					c.instance = c.createInstance();

				return (T*)c.instance;
			}
		}

		for (auto &c: multiInstance)
		{
			if (c.typesAndNames.find(typeOrName) != string::npos)
				return (T*)c.createInstance();
		}
		
		return NULL;
	}

	template <class T>
	T* get()
	{
		string type = typeid(T).name();
		for (auto &c: singletons)
		{
			if (c.typesAndNames.find(type) != string::npos)
			{
				if (c.instance == NULL)
					c.instance = c.createInstance();

				return (T*)c.instance;
			}
		}

		for (auto &c: multiInstance)
		{
			if (c.typesAndNames.find(type) != string::npos)
				return (T*)c.createInstance();
		}
		
		return NULL;
	}

	template <class T>
	bool contains()
	{
		string type = typeid(T).name();
		for (auto &c: singletons)
		{
			if (c.typesAndNames.find(type) != string::npos)
			{
				return true;
			}
		}

		for (auto &c: multiInstance)
		{
			if (c.typesAndNames.find(type) != string::npos)
				return true;
		}
		
		return false;
	}

	template <class T>
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

	#ifdef __OBJECT_POOL__
		template<class T>
		Pool<T> getPool();

		
	#endif

	
	/*template <class T>
	void putBack(string name, T* instance)
	{
		if (multiInstance.count(name) > 0)
			delete instance;
	}*/
};




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

#endif