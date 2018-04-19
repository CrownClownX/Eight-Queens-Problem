#include "Engine.h"
#include "Parameter.h"

int main(int argc, char** argv)
{
    char * name = NULL;
    int size = 0;

    checkArg(argv, argc, &size, &name);
    engine(size, name);

    if(name)
        free(name);

    return 0;
}
