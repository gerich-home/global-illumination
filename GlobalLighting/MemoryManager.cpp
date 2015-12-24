#include "stdafx.h"
#include "stdio.h"
#include "MemoryManager.h"

#undef new

const char* __file__ = "";
size_t __line__ = 0;

CRITICAL_SECTION cs;
bool csInited = false;

void InitMutex()
{
	if(!csInited)
	{
		InitializeCriticalSection(&cs);
		csInited = true;
	}
}

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

void* __Malloc(size_t size, const char * file, size_t line)
{
	InitMutex();
    
	EnterCriticalSection(&cs);

	memoryRecord* newItem =(memoryRecord*)malloc(sizeof(memoryRecord));
	newItem->size = size;
	newItem->ptr = malloc(size);
	newItem->file = file;
	newItem->line = line;
	newItem->next = memoryList.next;
	memoryList.next = newItem;

	memoryusage += size; 
	
	LeaveCriticalSection(&cs);

	return newItem->ptr;
}

void __Free(void* ptr)
{
	InitMutex();
	EnterCriticalSection(&cs);

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
	
	LeaveCriticalSection(&cs);

	free(ptr);
}

void* __Realloc(void* ptr, size_t newsize, const char * file, size_t line)
{
	InitMutex();
	EnterCriticalSection(&cs);

	if(newsize == 0)
	{
		__Free(ptr);
		return 0;
	}

	if(!ptr)
	{
		return __Malloc(newsize, file, line);
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
	
	LeaveCriticalSection(&cs);

	return current->ptr;
}


#if USE_MEMORY_MANAGER

void* operator new(size_t size)
{
	return  __Malloc(size, __file__, __line__);
}

void operator delete(void* ptr)
{
	return __Free(ptr);	
}

#endif