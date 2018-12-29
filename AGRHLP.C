#include <process.h>
#include <stdlib.h>
#include "agreg.h"

void help(void)
{
 saveskreen(0);
 spawnl(P_WAIT,"AGRVEW.EXE","AGRVEW.EXE","AGRHLP.DAT",NULL);
 saveskreen(1);
}


