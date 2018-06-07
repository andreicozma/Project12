#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include"consola.h"
#include"service.h"
#include"repo.h"
#include"masina.h"
#include<vector>
#include"test.h"

int main() {
	/*
	{
		test t;
		t.run_tests();
	}
	*/
	{
		Irepo<masina>* ir = new repoFile<masina>("masini.txt");
		service serv{ ir };
		consola c{ serv };
		c.run_main();
		delete ir;
		
	}
	_CrtDumpMemoryLeaks();

	

	return 0;
}