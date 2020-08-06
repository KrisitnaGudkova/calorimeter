root_include_dir := include
root_source_dir := src
source_subdirs := .

compile_flags := $(shell geant4-config --cflags) $(shell root-config --cflags)
  
link_flags := -s -pipe $(shell root-config --ldflags)
libraries := $(shell geant4-config --libs) -L/usr/lib64/root -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lMathCore -lThread -pthread -lm -ldl -rdynamic
 
relative_include_dirs := $(addprefix ../../, $(root_include_dir))
relative_source_dirs := $(addprefix ../../$(root_source_dir)/, $(source_subdirs))
objects_dirs := $(addprefix $(root_source_dir)/, $(source_subdirs))
objects := $(patsubst ../../%, %, $(wildcard $(addsuffix /*.c*, $(relative_source_dirs))))
objects := $(objects:.cpp=.o)
objects := $(objects:.c=.o)

love : release
	@echo	Make love
	@echo Not War!
all : $(program_name)

$(program_name) : obj_dirs $(objects)
	g++ -o $@ $(objects) $(link_flags) $(libraries)
obj_dirs :
	mkdir -p $(objects_dirs)

VPATH := ../../
%.o : %.cpp
	g++ -o $@ -c $< $(compile_flags) $(build_flags) $(addprefix -I, $(relative_include_dirs))
%.o : %.c
	g++ -o $@ -c $< $(compile_flags) $(build_flags) $(addprefix -I, $(relative_include_dirs))
.PHONY : clean
clean :
	rm -rf bin obj
prepare:
	mkdir -p bin
	mkdir -p obj
	mkdir -p obj/Debug
	mkdir -p obj/Release
release: prepare
	make all --directory=./obj/Release --makefile=../../Makefile build_flags="-O2 -fomit-frame-pointer" program_name=../../bin/petroleum
debug: prepare
	make all --directory=./obj/Debug --makefile=../../Makefile build_flags="-O0 -g3 -D_DEBUG" program_name=../../bin/debug
include $(wildcard $(addsuffix /*.d, $(objects_dirs)))
