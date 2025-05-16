CXX = C:/msys64/ucrt64/bin/g++.exe
CXXFLAGS = -std=c++17 -Wall -Iinclude -Ideps/asio-$(ASIO_VERSION)/include

ASIO_VERSION = 1.34.2
ASIO_URL = https://downloads.sourceforge.net/project/asio/asio/$(ASIO_VERSION)%20%28Stable%29/asio-$(ASIO_VERSION).zip
ASIO_ZIP = deps/asio-$(ASIO_VERSION).zip
ASIO_DIR = deps/asio/asio-$(ASIO_VERSION)

SRC_DIR = src
OBJ_DIR = obj
BIN = main.exe

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: prepare_asio $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lws2_32

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

prepare_asio:
	@if [ ! -d "$(ASIO_DIR)" ]; then \
		echo "Downloading ASIO..."; \
		mkdir -p deps; \
		curl -L "$(ASIO_URL)" -o "$(ASIO_ZIP)"; \
		unzip -q "$(ASIO_ZIP)" -d deps; \
		rm "$(ASIO_ZIP)"; \
	fi

clean:
	rm -rf $(OBJ_DIR) $(BIN)

.PHONY: all clean prepare_asio
