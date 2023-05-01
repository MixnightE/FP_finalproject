#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_

typedef struct segment_tree
{
    struct segment_tree *left;
    struct segment_tree *right;
} SegTree;

#endif // _STRUCTURE_H_