

#include "../source/assembler.h"	
#include "../source/softcpu.h"	



int main()
{

	void* testInstr = nullptr;

	if (assemble("ASM_TEST_FACTORIAL", &testInstr) != OK)
		return 1;

		//printf("instrPtr %p\n", testInstr);




	CPU_t machine;

	if (cpuCtor(&machine) != OK)
		return 1;


		if (loadInstuction(&machine, testInstr) != OK)
			return 1;

		if (runProgram(&machine) != OK)
			return 1;


	if (cpuDtor(&machine) != OK)
		return 1;


	free(testInstr);

	return 0;
}
