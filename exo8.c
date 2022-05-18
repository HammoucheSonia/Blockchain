#include "projet.h"
//structure arboresante

CellTree* create_node(Block* b)
{
    CellTree *bloc = malloc(sizeof(CellTree));
    bloc->height = 0;
    bloc->block = b;
    return (bloc);
}

int update_height(CellTree* father, CellTree* child)
{
    if (father->height == child->height-1)
        return (1);
    return (0);
}

void add_child(CellTree* father, CellTree* child)
{
    CellTree *arbre = malloc(sizeof(CellTree));
    arbre->height = father->height +1;
    arbre->father = father;
    arbre->firstChild = child; 
    CellTree *new_child = malloc(sizeof(CellTree));
    new_child->height = child->height -1;
    child->firstChild = new_child;
}

void print_tree(CellTree *arbre)
{
    if (arbre)
        printf("%s, %d", block_to_str(arbre->block),arbre->height);
    print_tree(arbre->father);
    print_tree(arbre->firstChild);
    print_tree(arbre->nextBro);
}

void delete_node(CellTree* node)
{
    if (node)
        delete_block(node->block);
    delete_node(node->father);
    delete_node(node->firstChild);
    delete_node(node->nextBro);
}

CellTree* highest_child(CellTree* cell)
{
    if ((cell->father->height > cell->firstChild->height) && (cell->father->height > cell->nextBro->height))
        return (cell->father);
    if ((cell->firstChild->height > cell->father->height) && (cell->firstChild->height > cell->nextBro->height))
        return(cell->firstChild);
    else
        return (cell->nextBro);
}

CellTree* last_node(CellTree* tree)
{
    return (last_node(highest_child(tree)));
}
