 # My third makefile
 
# Name of the project
PROJ_NAME=tests
# .c files

#teste app includes
CUSTOM_INCLUDE_PATH = -I"./sources"

#main app includes
CUSTOM_INCLUDE_PATH += -I"../sources/Controller"
CUSTOM_INCLUDE_PATH += -I"../sources/Controller/Internal"
CUSTOM_INCLUDE_PATH += -I"../sources/Services"
CUSTOM_INCLUDE_PATH += -I"../sources/Services/APIs"
CUSTOM_INCLUDE_PATH += -I"../sources/Services/APIs/VSTP"
CUSTOM_INCLUDE_PATH += -I"../sources/Services/APIs/http"
CUSTOM_INCLUDE_PATH += -I"../sources/Services/http/varsexporters"
CUSTOM_INCLUDE_PATH += -I"../sources/Services/Storage"
CUSTOM_INCLUDE_PATH += -I"../sources/Shared"
CUSTOM_INCLUDE_PATH += -I"../sources/Shared/Misc"
CUSTOM_INCLUDE_PATH += -I"../sources/Shared/Libs"
CUSTOM_INCLUDE_PATH += -I"../sources/Shared/Libs/DynamicVar/sources"
CUSTOM_INCLUDE_PATH += -I"../sources/Shared/Libs/json_maker/sources"
CUSTOM_INCLUDE_PATH += -I"../sources/Shared/Libs/Confs"
CUSTOM_INCLUDE_PATH += -I"../sources/Shared/Libs/Confs/internal"
CUSTOM_INCLUDE_PATH += -I"../sources/Shared/Libs/DependencyInjection/sources"
CUSTOM_INCLUDE_PATH += -I"../sources/Shared/Libs/Logger/sources"
CUSTOM_INCLUDE_PATH += -I"../sources/Shared/Libs/Logger/sources/writers"
CUSTOM_INCLUDE_PATH += -I"../sources/Shared/Libs/TCPServer/sources"
CUSTOM_INCLUDE_PATH += -I"../sources/Shared/Libs/ThreadPool"
CUSTOM_INCLUDE_PATH += -I"../sources/Shared/Libs/VarSystem"
CUSTOM_INCLUDE_PATH += -I"../sources/Shared/Libs/MessageBus"
CUSTOM_INCLUDE_PATH += -I"../sources/Shared/Libs/KwWebServer/sources"
CUSTOM_INCLUDE_PATH += -I"../sources/Shared/Libs/KwWebServer/sources/Workers"



#test app files
C_SOURCE=$(wildcard ./sources/*.cpp)
C_SOURCE+=$(wildcard ./sources/mocks/*.cpp)
C_SOURCE+=$(wildcard ./sources/Controller/*.cpp)
C_SOURCE+=$(wildcard ./sources/Controller/Internal/*.cpp)
C_SOURCE+=$(wildcard ./sources/Services/APIs/VSTP/*.cpp)
C_SOURCE+=$(wildcard ./sources/Services/APIs/http/*.cpp)
C_SOURCE+=$(wildcard ./sources/Shared/Libs/DependencyInjectionManager/*.cpp)
C_SOURCE+=$(wildcard ./sources/Shared/Libs/Confs/*.cpp)
C_SOURCE+=$(wildcard ./sources/Shared/Libs/Confs/internal/*.cpp)
C_SOURCE+=$(wildcard ./sources/Shared/Misc/TaggedObject/*.cpp)

#main app files
C_SOURCE+=$(wildcard ../sources/Controller/*.cpp)
C_SOURCE+=$(wildcard ../sources/Controller/Internal/*.cpp)
C_SOURCE+=$(wildcard ../sources/Services/*.cpp)
C_SOURCE+=$(wildcard ../sources/Services/APIs/*.cpp)
C_SOURCE+=$(wildcard ../sources/Services/APIs/VSTP/*.cpp)
C_SOURCE+=$(wildcard ../sources/Services/APIs/http/*.cpp)
C_SOURCE+=$(wildcard ../sources/Services/http/*.cpp)
C_SOURCE+=$(wildcard ../sources/Services/http/varsexporters/*.cpp)
C_SOURCE+=$(wildcard ../sources/Services/Storage/*.cpp)
C_SOURCE+=$(wildcard ../sources/Shared/*.cpp)
C_SOURCE+=$(wildcard ../sources/Shared/Misc/*.cpp)
C_SOURCE+=$(wildcard ../sources/Shared/Libs/*.cpp)
C_SOURCE+=$(wildcard ../sources/Shared/Libs/DynamicVar/sources/*.cpp)
C_SOURCE+=$(wildcard ../sources/Shared/Libs/json_maker/sources/*.cpp)
C_SOURCE+=$(wildcard ../sources/Shared/Libs/Confs/*.cpp)
C_SOURCE+=$(wildcard ../sources/Shared/Libs/Confs/internal/*.cpp)
C_SOURCE+=$(wildcard ../sources/Shared/Libs/DependencyInjection/sources/*.cpp)
C_SOURCE+=$(wildcard ../sources/Shared/Libs/Logger/sources/*.cpp)
C_SOURCE+=$(wildcard ../sources/Shared/Libs/Logger/sources/writers/*.cpp)
C_SOURCE+=$(wildcard ../sources/Shared/Libs/TCPServer/sources/*.cpp)
C_SOURCE+=$(wildcard ../sources/Shared/Libs/ThreadPool/*.cpp)
C_SOURCE+=$(wildcard ../sources/Shared/Libs/VarSystem/*.cpp)
C_SOURCE+=$(wildcard ../sources/Shared/Libs/MessageBus/*.cpp)
C_SOURCE+=$(wildcard ../sources/Shared/Libs/KwWebServer/sources/*.cpp)
C_SOURCE+=$(wildcard ../sources/Shared/Libs/KwWebServer/sources/Workers/*.cpp)
  
# .h files
#test app files
H_SOURCE=$(wildcard ./sources/*.h)
H_SOURCE+=$(wildcard ./sources/mocks/*.h)
H_SOURCE+=$(wildcard ./sources/Controller/*.h)
H_SOURCE+=$(wildcard ./sources/Controller/Internal/*.h)
H_SOURCE+=$(wildcard ./sources/Services/APIs/VSTP/*.h)
H_SOURCE+=$(wildcard ./sources/Services/APIs/http/*.h)
H_SOURCE+=$(wildcard ./sources/Shared/Libs/DependencyInjectionManager/*.h)
H_SOURCE+=$(wildcard ./sources/Shared/Libs/Confs/*.h)
H_SOURCE+=$(wildcard ./sources/Shared/Libs/Confs/internal/*.h)
H_SOURCE+=$(wildcard ./sources/Shared/Misc/TaggedObject/*.h)

#main app files
H_SOURCE+=$(wildcard ../sources/Controller/*.h)
H_SOURCE+=$(wildcard ../sources/Controller/Internal/*.h)
H_SOURCE+=$(wildcard ../sources/Services/*.h)
H_SOURCE+=$(wildcard ../sources/Services/APIs/*.h)
H_SOURCE+=$(wildcard ../sources/Services/APIs/VSTP/*.h)
H_SOURCE+=$(wildcard ../sources/Services/APIs/http/*.h)
H_SOURCE+=$(wildcard ../sources/Services/APIs/http/varsexporters/*.h)
H_SOURCE+=$(wildcard ../sources/Services/Storage/*.h)
H_SOURCE+=$(wildcard ../sources/Shared/*.h)
H_SOURCE+=$(wildcard ../sources/Shared/Misc/*.h)
H_SOURCE+=$(wildcard ../sources/Shared/Libs/*.h)
H_SOURCE+=$(wildcard ../sources/Shared/Libs/json_maker/sources/*.h)
H_SOURCE+=$(wildcard ../sources/Shared/Libs/DynamicVar/sources/*.h)
H_SOURCE+=$(wildcard ../sources/Shared/Libs/Confs/*.h)
H_SOURCE+=$(wildcard ../sources/Shared/Libs/Confs/internal/*.h)
H_SOURCE+=$(wildcard ../sources/Shared/Libs/DependencyInjection/sources/*.h)
H_SOURCE+=$(wildcard ../sources/Shared/Libs/Logger/sources/*.h)
H_SOURCE+=$(wildcard ../sources/Shared/Libs/Logger/sources/writers/*.h)
H_SOURCE+=$(wildcard ../sources/Shared/Libs/TCPServer/sources/*.h)
H_SOURCE+=$(wildcard ../sources/Shared/Libs/ThreadPool/*.h)
H_SOURCE+=$(wildcard ../sources/Shared/Libs/VarSystem/*.h)
H_SOURCE+=$(wildcard ../sources/Shared/Libs/MessageBus/*.h)
H_SOURCE+=$(wildcard ../sources/Shared/Libs/KwWebServer/sources/*.h)
H_SOURCE+=$(wildcard ../sources/Shared/Libs/KwWebServer/sources/Workers/*.h)

objFolder:
	@ mkdir -p objects/tests/
	@ mkdir -p objects/tests/Controller
	@ mkdir -p objects/tests/Controller/Internal
	@ mkdir -p objects/tests/Services/APIs/VSTP
	@ mkdir -p objects/tests/Services/APIs/http
	@ mkdir -p objects/tests/Shared/Libs/DependencyInjectionManager
	@ mkdir -p objects/tests/Shared/Libs/Confs 
	@ mkdir -p objects/tests/Shared/Libs/Confs/internal
	@ mkdir -p objects/tests/Shared/Misc/TaggedObject
#	the main app directories
	@ mkdir -p objects/main/Services/APIs/http
	@ mkdir -p objects/main/Services/APIs/VSTP
	@ mkdir -p objects/main/Services/http/varsexporters
	@ mkdir -p objects/main/Controller
	@ mkdir -p objects/main/Controller/Internal
	@ mkdir -p objects/main/Services
	@ mkdir -p objects/main/Services/Storage
	@ mkdir -p objects/main/Shared/Misc
	@ mkdir -p objects/main/Shared/Libs/DynamicVar/sources
	@ mkdir -p objects/main/Shared/Libs/json_maker/sources
	@ mkdir -p objects/main/Shared/Libs/Confs/internal
	@ mkdir -p objects/main/Shared/Libs/DependencyInjection/sources
	@ mkdir -p objects/main/Shared/Libs/Logger/sources/writers
	@ mkdir -p objects/main/Shared/Libs/TCPServer/sources
	@ mkdir -p objects/main/Shared/Libs/ThreadPool
	@ mkdir -p objects/main/Shared/Libs/VarSystem
	@ mkdir -p objects/main/Shared/Libs/MessageBus
	@ mkdir -p objects/main/Shared/Libs/KwWebServer/sources/Workers
	
	

prebuild:
# 	prepares the folder built/gui. This folder contains files copied from GUI/resources. These files contains the HTML5 User interface.
	@ clear
	@ mkdir ./build | true
	@ cp -r ./sources/copyToBuildFolder/* ./build | true
 
# Object files
OBJ=$(subst .cpp,.o,$(subst ./sources,./objects/tests,$(subst ../sources,./objects/main,$(C_SOURCE))))
 
# Compiler and linker
#CC=g++
CC=clang++
 
# Flags for compiler
#		 -W         
#        -Wall      
#         -pedantic  
CC_FLAGS=-D__TESTING__ \
		 -c			\
         -ansi      \
		 -pthread   \
		 -g			\
		 -std=c++17 \
		 -I"./sources/" \
		 -lssl      \
		 -lcrypto   \
		 $(CUSTOM_INCLUDE_PATH)
		 


# Flags for linker
#		 -W 		
#         -Wall      
#         -pedantic  
LK_FLAGS=-D__TESTING__\
         -ansi      \
		 -pthread   \
		 -g			\
		 -std=c++17 \
		 -I"./sources/" \
		 -lssl      \
		 -lcrypto   \
		 $(CUSTOM_INCLUDE_PATH)
 
# Command used at clean target
RM = rm -rf
#
# Compilation and linking
#
all: objFolder prebuild $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
	@ echo 'Building binary using GCC linker: $@'
	$(CC) $^ $(LK_FLAGS) -o build/$@
	@ echo 'Finished building binary: $@'
	@ echo ' '
 
./objects/main/%.o: ../sources/%.cpp ../sources/%.h
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

./objects/tests/%.o: ./sources/%.cpp ./sources/%.h
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '
 
./objects/tests/main.o: ./sources/main.cpp $(H_SOURCE)
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '
	
clean:
	@ $(RM) ./objects/*.o $(PROJ_NAME) *~
	@ rm -rf objects
 
.PHONY: all clean