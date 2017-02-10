#  = 是赋值的用法
# := 变量和值之间使用冒号等号
# 区别： := 只能使用前面定义好的变量，= 可以使用后边定义的变量
ifeq ($(DEBUG), 1) # debug 版本
#@echo 'debug'
CXXFLAGS_EXTRA = -pg -g # 开启调试和 profile 编译选项
DEP_TAIL = .dd
OBJ_TAIL = .do
PROG := ./debug
else # release 版本
#@echo 'release'
CXXFLAGS_EXTRA = -O3
DEP_TAIL = .d
OBJ_TAIL = .o
PROG := ./release
endif

SRC := $(wildcard *.cpp)
# $(var:a=b) 是将 var 变量中每一个单词后面的 a 替换为 b
OBJ := $(SRC:.cpp=.o)
EXC = test
CXX = g++
CXXFLAG = -std=c++11 -Wall

all: $(EXC)
	@echo $(RM)
	@echo $(AR)
	@echo $(CC)
	@echo $(CXX)

$(EXC): $(OBJ)
	@echo "Compiling ..."
	$(CXX) $(CXXFLAG) $(CXXFLAGS_EXTRA) $? -o $@
	@echo "End of compile ..."

%.o:%.cpp
	$(CXX) $(CXXFLAG) $(CXXFLAGS_EXTRA) -c $< -o $@

.PHONY:	relay
relay:
	@echo "查看依赖关系。"
	$(CXX) -MM $(SRC)

# phony : a. 假的 
.PHONY:	clean	# <-- 这句没有也行，但最好加上
clean: 
	@echo "clean"
	$(RM) *.o


