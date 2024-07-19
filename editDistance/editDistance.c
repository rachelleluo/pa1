#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//SUBPROBLEMS ARE SOLVED RECURSIVELY

//The edit distance measures the difference between two strings of characters.

/*

algorithm you should look up: wagner-fisher
creates a 2d array and build a table (puts a blank before both words)

   _  i  t      CHECKS DIAGONALLY TOO (starts after first column)
_  0  1  2      checks to see if it matches in the table, if it doesn't then it adds 1
i  1  0  1      if they do match, it adds 0
n  2  1  1      AT THE END, LOOK AT THE LAST ROW AND SEE WHICH ONE IS THE SMALLEST
t  3  2  1

*/

/*you should be using a 2d array 
https://hyperskill.org/learn/step/35106 
*/

size_t min ( size_t x, size_t y ) {
    return x<y ? x : y;
}

size_t wagner_fischer(char* source, char* target){
    //gets lengths of the words
    int m = strlen(source);
    int n = strlen(target);
    //initializes array
    int array[m+2][n+2];

    //sets all array values to 0
    for(int i = 0; i <= m+1; i++){
        for(int j = 0; j <= n+1; j++){
            array[i][j] = 0;
        }
    }

    //sets up a table with the source word going up and down and the target word 
    //going across with the [0][0] element kept as 0
    /* ex) source = in, target = int
        0 i n t
        i 0 0 0
        n 0 0 0
    */
    for(int i = 2; i <= m+1; i++){
        for(int j = 2; j <= n+1; j++){
            array[i][0] = source[i-2];
            array[0][j] = target[j-2];
        }
    }

    //loops through the aray
    for(int i = 1; i <= m+1; i++){
        for(int j = 1; j <= n+1; j++){
            int cost = 0;
            //checks to see if the corresponding characters in the source and target are equal
            //if they aren't the cost is 1, otherwise cost is 0
            if(array[i][0] != array[0][j]){
                cost = 1;
            }
            //find all possible costs for either insertion, deletion, and substitution
            size_t ins = array[i][j-1] + 1;
            size_t del = array[i-1][j] + 1;
            size_t sub = array[i-1][j-1] + cost;
            //find the minimum and set the current value equal to it
            array[i][j] = min(min(ins, del), sub);
        }
    }

    //returns final value in the 2d array which should be the minimum edit distance
    return array[m+1][n+1];
}

int main(int argc, char* argv[])
{

    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    char source[32];
    char target[32];

    fscanf (inputFile, "%s\n%s", source, target);
    // wagner_fischer ( source, target );

    printf("%ld\n", wagner_fischer ( source, target ));

    return EXIT_SUCCESS;

}
