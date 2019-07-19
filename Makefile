ERL_PATH = $(shell erl -eval "io:format(\"~s~n\", [code:root_dir()])" -s init stop -noshell)
ERL_EI_INCLUDE_DIR ?= $(ERL_PATH)/usr/include
ERL_EI_LIBDIR ?= $(ERL_PATH)/usr/lib

CFLAGS = -g -I$(ERL_EI_INCLUDE_DIR)
LDFLAGS = -L$(ERL_EI_LIBDIR) -lerl_interface -lei -lpthread -llibdrm

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

ifeq ($(BUILD_PORTS),)
all:
else
all: priv/gpu
endif

priv/gpu: priv $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDLIBS) $(LDFLAGS)

priv:
	mkdir -p priv

clean:
	rm -rf priv $(OBJ) $(LIB_OBJ) $(BEAM_FILES)
