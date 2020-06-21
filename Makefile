g++ main.cpp `pkg-config --cflags --libs opencv` -o vidux

# # Makefile_header
# # プログラム名とオブジェクトファイル名
# PROGRAM = vidux
# OBJS = main.o

# # 定義済みマクロの再定義
# CC = g++
# CFLAGS = -Wall -O2 $(pkg-config --cflags opencv)
# LDFLAGS = -L/usr/local/lib
# LIBS = $(pkg-config --libs opencv)



# # サフィックスルール適用対象の拡張子の定義
# .SUFFIXES: .c .o .cpp

# # プライマリターゲット
# .PHONY: all
# all: depend $(PROGRAM)

# # プログラムの生成ルール
# $(PROGRAM): $(OBJS)
# 	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $(PROGRAM) $^

# # サフィックスルール
# .c.o:
# 	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -c $<

# # ファイル削除用ターゲット
# .PHONY: clean
# clean:
# 	$(RM) $(PROGRAM) $(OBJS) depend.inc

# # ヘッダファイルの依存関係
# .PHONY: depend
# depend: $(OBJS:.o=.cpp)
# 	-@ $(RM) depend.inc
# 	-@ for i in $^; do cpp -MM $$i | sed "s/\ [_a-zA-Z0-9][_a-zA-Z0-9]*\.cpp//g" >> depend.inc; done

# -include depend.inc
