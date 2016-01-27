#include <stdlib.h>
#include <stdio.h>
#include "../include/allocation.h"
#include "../src/allocation.c"
#include <gtest/gtest.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}

TEST(calloc_memory, ZeroBytes) { 
	void* allocated = allocate_array(sizeof(char), 0,1);
	ASSERT_NE((void*)NULL, allocated);
	free(allocated);
}
TEST(calloc_memory, NegativeBytes) { 
	void* allocated = allocate_array(sizeof(char),-1,1);
	ASSERT_EQ((void*)NULL, allocated);
	free(allocated);
}
TEST(calloc_memory, PositiveBytes) { 
	void* allocated = allocate_array(sizeof(char), BUFSIZ,1);
	ASSERT_NE((void*)NULL, allocated);
	free(allocated);
}
TEST(malloc_memory, ZeroBytes) { 
	void* allocated = allocate_array(sizeof(char), 0,0);
	ASSERT_NE((void*)NULL, allocated);
	free(allocated);
}
TEST(malloc_memory, NegativeBytes) { 
	void* allocated = allocate_array(sizeof(char), -1,0);
	ASSERT_EQ((void*)NULL, allocated);
	free(allocated);
}
TEST(malloc_memory, PositiveBytes) { 
	void* allocated = allocate_array(sizeof(char), BUFSIZ,0);
	ASSERT_NE((void*)NULL, allocated);
	free(allocated);
}
TEST(reallocate, ZeroBytes) { 
	void* allocated = allocate_array(sizeof(char), BUFSIZ,1);
	ASSERT_NE((void*)NULL, allocated);
	void* reallocated = reallocate_array(allocated,0);
	EXPECT_EQ((void*)NULL,reallocated);
	free(reallocated);
}
TEST(reallocate, NegativeBytes) { 
	void* allocated = allocate_array(sizeof(char), BUFSIZ,1);
	ASSERT_NE((void*)NULL, allocated);
	void* reallocated = reallocate_array(allocated,-1);
	EXPECT_EQ((void*)NULL,reallocated);
	free(reallocated);
}
TEST(reallocate, PositiveBytes) { 
	void* allocated = allocate_array(sizeof(char), BUFSIZ,1);
	ASSERT_NE((void*)NULL, allocated);
	void* reallocated = reallocate_array(allocated,BUFSIZ*2);
	EXPECT_NE((void*)NULL,reallocated);
}

TEST(deallocate, ValidPointer) { 
	void* allocated = allocate_array(sizeof(char), BUFSIZ,1);
	deallocate_array(&allocated);
	EXPECT_EQ((void*)NULL,(void*)allocated);
}
TEST(deallocate, NullPointer) { 
	void* allocated = NULL;
	deallocate_array(&allocated);
	EXPECT_EQ((void*)NULL,(void*)allocated);
}
TEST(readline_to_buffer,ValidFile){
	
	char filename[] = "test.txt";
	int fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
	write(fd,"Test",4);
	char* buffer = read_line_to_buffer(filename);
	ASSERT_NE(buffer,(char*)NULL);
	EXPECT_TRUE(strcmp(buffer,"Test") == 0);
	free(buffer);
}
