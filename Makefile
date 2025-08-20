# Variables
CXX = g++
CXXFLAGS = -Wall
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC = main.cc Player.cc Camera.cc WorldObject.cc Coin.cc World.cc Obstacle.cc GameManager.cc UIManager.cc ColorManager.cc Checkpoint.cc
HDR = Player.hh Camera.hh WorldObject.hh Coin.hh World.hh Obstacle.hh GameManager.hh UIManager.hh ColorManager.hh Checkpoint.hh
OBJ = $(SRC:.cc=.o)

TARGET = game

# Regla principal
all: $(TARGET)

# Linkar
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compilar cada .cc a .o, depenent també dels .hh
%.o: %.cc $(HDR)
	$(CXX) $(CXXFLAGS) -c $<

# Netejar
clean:
	rm -f $(OBJ) $(TARGET)
