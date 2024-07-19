#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/*
using structs and pointers to build a paramRoot data structure, 
and use that paramRoot to check whether a string is properly balanced. 
*/

//each time you see an open thing, add to the paramRoot, each time you find the matching 
//closed character then pop it off of the paramRoot
/*
dot operator reaches in and gets the component inside of the struct
THESE LINES MEAN EXACTLY THE SAME THING
(*root).key = key;
root->key = key;     
*/

// Struct to hold the open and close braces and the pointer to the next element.
struct element {
    char close;
    struct element* next;
};

// Append the new element to the start of the stack
// This is one potential way to write this function signature
struct element* push (struct element** paramRoot, char close) {
    struct element* newElement = malloc ( sizeof ( struct element ) );
    newElement->close = close;
    newElement->next = *paramRoot;
    *paramRoot = newElement;
    return newElement;
}

// Remove element from the top of the stack
char pop ( struct element** paramRoot) {
    if (*paramRoot != NULL) {
        struct element* temp = *paramRoot;
        char new = temp->close;
        *paramRoot = temp->next;
        free ( temp );
        return new;
    } else {
        return '\0';
    }
}

bool check(struct element ** paramRoot, char close){
    if(*paramRoot != NULL){
        struct element* temp = *paramRoot;
        char new = temp->close;
        if(new == close){
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    struct element* root = NULL;
    bool balanced = true;
    int counter = 0;
    int popCounter = 0;

    char buff;
    while ( fscanf(fp, "%c", &buff)==1 ) {
        counter += 1;
        switch(buff) {
            //cases with open characters, push them into the stack
            case '<' :
                push(&root, '>');
                break;
            case '(' :
                push(&root, ')');
                break;
            case '[' :
                push(&root, ']');
                break;
            case '{' :
                push(&root, '}');
                break;
            //cases with closed characters, look through the stack to find its matching
            //open element, if you find it, pop it out of the stack
            case '>' :
                if(check(&root, '>')){
                    pop(&root);
                    popCounter += 1;
                }
                break;
            case ')' :
                if(check(&root, ')')){
                    pop(&root);
                    popCounter += 1;
                }
                break;
            case ']' :
                if(check(&root, ']')){
                    pop(&root);
                    popCounter += 1;
                }
                break;
            case '}' :
                if(check(&root, '}')){
                    pop(&root);
                    popCounter += 1;
                }
                break;          
            default :
                printf("Invalid character\n" );
        }
    }

    if(counter % 2 != 0){
        balanced = false;
    }else{
        if(counter/2 != popCounter){
            balanced = false;
        }
    }

    printf ( balanced ? "yes" : "no" );
    fclose(fp);
    return 0;
}
