
SERVER = exe_server


OS_NAME = $(shell uname)
LC_OS_NAME = $(shell echo $(OS_NAME) | tr '[A-Z]' '[a-z]')
ifeq ($(LC_OS_NAME), darwin)
LIBS += -lpthread
else 
LIBS += -lpthread -luuid
endif

#LIBS += ../base/libbase.a

COMMON_PATH := .
SRCDIRS   := .
CPPFLAGS  += -I $(COMMON_PATH)
#CPPFLAGS += -Wall -Wno-deprecated -g

SRCEXTS   := .c .cpp
CC      = g++
SHELL   = /bin/sh
SOURCES = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(SRCEXTS))))
OBJS = $(foreach x,$(SRCEXTS),$(patsubst %$(x),./obj/%.o,$(filter %$(x),$(notdir $(SOURCES)))))

all: $(SERVER)

DEPS    = $(patsubst %.o,%.d,$(OBJS))

$(SERVER): $(OBJS)
	$(CC)  $(CPPFLAGS) -o $@ $(OBJS) $(LIBS)

objs : $(OBJS)
./obj/%.o : %.c
	@echo "=================="
	@echo "Compiling $<"
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@
./obj/%.o : %.cpp
	@mkdir -p $(dir $@)
	@echo "=================="
	@echo "Compiling $<"
	$(CC) -c $(CPPFLAGS)  $< -o $@

.PHONY : clean
clean: 
	rm -f $(OBJS)
	rm -f $(SERVER)
