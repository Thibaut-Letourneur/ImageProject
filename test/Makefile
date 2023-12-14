.PHONY: testPartitionImage testMomentImage


testPartitionImage: $(OBJ_DIR)/testPartitionImage.o $(OBJ_DIR)/partitionImage.o
	$(CC) $^ -o bin/test/$@ $(LIBS) -no-pie

$(OBJ_DIR)/testRag.o: test/testRag.c include/rag.h
	$(CC) $(CFLAGS) $< -o $@ -c


testMomentImage: $(OBJ_DIR)/testMomentImage.o $(OBJ_DIR)/partitionImage.o $(OBJ_DIR)/momentImage.o
	$(CC) $^ -o bin/test/$@ $(LIBS) -no-pie

$(OBJ_DIR)/testMomentImage.o: test/testMomentImage.c include/momentImage.h
	$(CC) $(CFLAGS) $< -o $@ -c


testRag: $(OBJ_DIR)/testRag.o $(OBJ_DIR)/rag.o $(OBJ_DIR)/partitionImage.o $(OBJ_DIR)/momentImage.o
	$(CC) $^ -o bin/test/$@ $(LIBS) -no-pie

$(OBJ_DIR)/testPartitionImage.o: test/testPartitionImage.c include/partitionImage.h
	$(CC) $(CFLAGS) $< -o $@ -c

testPerformMerge: $(OBJ_DIR)/testPerformMerge.o $(OBJ_DIR)/performMerge.o $(OBJ_DIR)/rag.o $(OBJ_DIR)/partitionImage.o $(OBJ_DIR)/momentImage.o
	$(CC) $^ -o bin/test/$@ $(LIBS) -no-pie

$(OBJ_DIR)/testPerformMerge.o: test/testPerformMerge.c include/performMerge.h
	$(CC) $(CFLAGS) $< -o $@ -c