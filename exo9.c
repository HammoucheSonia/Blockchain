#include "projet.h"
#include <string.h>

void submit_vote(Protected* p)
{
    char *str = protected_to_str(p);
    const char* filename = "Pending votes.txt";

    FILE* output_file = fopen(filename, "w+");
    if (!output_file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fwrite(str, 1, strlen(str), output_file);
    printf("Done Writing!\n");

    fclose(output_file);
    exit(EXIT_SUCCESS);
}

void create_block(CellTree* tree, key* author, int d)
{
    Block *bloc = malloc(sizeof(Block));
    bloc = lire_block("Pending votes.txt");
    bloc ->author = author;
    bloc->nonce = d; 
    //gets("Pending votes.txt");
}

