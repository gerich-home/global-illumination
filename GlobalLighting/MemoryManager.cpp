#include "stdafx.h"
#include "stdio.h"
#include "MemoryManager.h"
//#include "Utils.h"

#undef new

const char* __file__ = "";
size_t __line__ = 0;

//CCriticalSection *Mutex;
//bool mutexInited = false;

/*void InitMutex()
{
	if(!mutexInited)
	{
		Mutex = (CCriticalSection*)malloc(sizeof(CCriticalSection));
		new(Mutex) CCriticalSection();
		mutexInited = true;
	}
}*/

struct memoryRecord
{
	void *ptr;
	size_t size;
	const char *file;
	size_t line;
	
	memoryRecord *next;
};

memoryRecord memoryList = {0};
size_t memoryusage = 0;

size_t MemoryUsage()
{
	return memoryusage;
}

void PrintMemoryTable()
{
	static bool fisrtOpen  = true;
	FILE* file;
	if(fisrtOpen)
	{
		file = fopen("memory_log.csv","w");
		fprintf(file,"FILE NAME;LINE;SIZE OF BLOCK;ADDRESS\n");
		fisrtOpen = false;
	}
	else
	{
		file = fopen("memory_log.csv","a");
		fprintf(file,"\n");
	}
	memoryRecord* current = memoryList.next;
	while(current)
	{
		fprintf(file,"%s;",current->file);
		fprintf(file,"%i;",current->line);
		fprintf(file,"%i;",current->size);
		fprintf(file,"%x\n",current->ptr);
		current = current->next;
	}

	fclose(file);
}

void PrintMemoryUsage()
{
	FILE* file = fopen("memory_log.txt","a");
	
	fprintf(file,"==============================\n");
	fprintf(file,"Memory usage = %i \n", MemoryUsage());
	
	fclose(file);
}

void* __taluMalloc(size_t size, const char * file, size_t line)
{
	//InitMutex();
    //CSyncObjectLock locker(*Mutex);

	memoryRecord* newItem =(memoryRecord*)malloc(sizeof(memoryRecord));
	newItem->size = size;
	newItem->ptr = malloc(size);
	newItem->file = file;
	newItem->line = line;
	newItem->next = memoryList.next;
	memoryList.next = newItem;

	memoryusage += size; 
	
	return newItem->ptr;
}

void __taluFree(void* ptr)
{
	//InitMutex();
	//CSyncObjectLock locker(*Mutex);
	memoryRecord* current = memoryList.next;
	memoryRecord* prev = &memoryList;

	while(current)
	{
		if(current->ptr == ptr)
		{	
			memoryusage -= current->size;
			prev->next = current->next;
			free(current);
			break;
		}
		prev = current;
		current = current->next;
	}

	free(ptr);
}

void* __taluRealloc(void* ptr, size_t newsize, const char * file, size_t line)
{
	//InitMutex();
	//CSyncObjectLock locker(*Mutex);
	if(newsize == 0)
	{
		__taluFree(ptr);
		return 0;
	}

	if(!ptr)
	{
		return __taluMalloc(newsize, file, line);
	}

	memoryRecord* current = memoryList.next;

	while(current)
	{
		if(current->ptr == ptr)
		{	
			current->ptr = realloc(ptr,newsize);
			memoryusage += newsize - current->size;
			current->size = newsize;
			break;
		}
		current = current->next;
	}

	return current->ptr;
}

void* operator new(size_t size)
{
	return  __taluMalloc(size, __file__, __line__);
}

void operator delete(void* ptr)
{
	return __taluFree(ptr);	
}
