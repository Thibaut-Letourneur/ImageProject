.PHONY: prog

prog: $(OBJ_DIR)/main.o $(OBJ_DIR)/partitionImage.o $(OBJ_DIR)/momentImage.o $(OBJ_DIR)/rag.o $(OBJ_DIR)/performMerge.o
	$(CC) $^ -o bin/$@ $(LIBS) -no-pie 

$(OBJ_DIR)/main.o: src/main.c include/partitionImage.h
	$(CC) $(CFLAGS) $< -o $@ -c

$(OBJ_DIR)/partitionImage.o: src/partitionImage.c include/partitionImage.h
	$(CC) $(CFLAGS) $< -o $@ -c

$(OBJ_DIR)/momentImage.o: src/momentImage.c include/momentImage.h
	$(CC) $(CFLAGS) $< -o $@ -c

$(OBJ_DIR)/rag.o: src/rag.c include/rag.h
	$(CC) $(CFLAGS) $< -o $@ -c

$(OBJ_DIR)/performMerge.o: src/performMerge.c include/performMerge.h
	$(CC) $(CFLAGS) $< -o $@ -c
