#######Makefile Begin#######################

TARGET_NAME := test
BUILD_TYPE := Debug

MODULE_TYPE := executable

TARGET := $(TARGET_NAME)

GOV_FLG = 1

SRCDIRS := ./ 

CPPFLAGS += -Duse_namespace -fPIC  -I ./
CPPFLAGS += -I./
LDFLAGS := -L -lpthread 

SRCEXTS   := .c .cpp
CC      = g++
SHELL   = /bin/sh
SOURCES = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(SRCEXTS))))
OBJS= $(patsubst %.cpp,./obj/%.o,$(notdir $(SOURCES)))
GCNOS= $(patsubst %.cpp,./obj/%.gcno,$(notdir $(SOURCES)))
#OBJS= $(patsubst %.c,./obj/%.o,$(notdir $(SOURCES)))
#GCNOS= $(patsubst %.c,./obj/%.gcno,$(notdir $(SOURCES)))

vpath %.o ./obj
vpath %.cpp $(dir $(SOURCES))

DEPS    = $(patsubst %.o,%.d,$(OBJS))
.PHONY : all objs clean cleanall rebuild install
all : $(TARGET) 

ifeq ($(BUILD_TYPE), Debug)
CFLAGS += -g -D DEBUG
CPPFLAGS += -g -D DEBUG
endif

objs : $(OBJS)
./obj/%.o : %.c
	@mkdir -p $(dir $@)
	@echo "gcc ============="
	@echo "Compiling $<"
	$(CC) -c $(CPPFLAGS) $< -o $@ $(CGOV)

./obj/%.o : %.cpp
	@mkdir -p $(dir $@)
	@echo "============="
	@echo "Compiling $<"
	$(CC) -c $(CPPFLAGS)  $< -o $@ $(CGOV)


$(TARGET) : $(OBJS)
	@mkdir -p ./bin/$(BUILD_TYPE)

ifeq ($(MODULE_TYPE), dynamic_lib)
	$(CC) -o ./bin/$(BUILD_TYPE)/lib_$(TARGET_NAME).so -shared $(OBJS) $(STATIC_LIBS) $(LDFLAGS) $(CGOV)
endif

ifeq ($(MODULE_TYPE), static_lib)
	ar rcs ./bin/$(BUILD_TYPE)/lib_$(TARGET_NAME).a $(OBJS)  
endif

ifeq ($(MODULE_TYPE), executable)
	$(CC) -o ./exe_$(TARGET_NAME) $(OBJS) $(LDFLAGS) $(CGOV)
endif

-include $(DEPS)

install : all
	@mkdir -p $(INSTALL_DIR)/bin
	@mkdir -p $(INSTALL_DIR)/lib
	@mkdir -p $(INSTALL_DIR)/etc
	@mkdir -p $(INSTALL_DIR)/dat
	@mkdir -p $(INSTALL_DIR)/config
	@mkdir -p $(INSTALL_DIR)/sh


rebuild: clean all


clean :
	@echo "cleaning ..."
	@echo "rm objects ..."
	rm -f $(OBJS)
	@echo "rm gcnos ..."
	rm -f $(GCNOS)
	rm -f ./bin/$(BUILD_TYPE)/*

cleanall: clean

	@$(RM) $(PROGRAM) $(PROGRAM).exe

###############################################################################

