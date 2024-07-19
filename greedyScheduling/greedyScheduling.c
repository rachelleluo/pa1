#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Selection sort based approach to sorting jobs

/*
-If a job starts at time 0, it is invalid and should not be scheduled.

-Jobs X and Y are considered overlapping if job X's beginning time is 
LESS THAN OR EQUAL to job Y's ending time (In the example above, jobs A and B overlap).

-If multiple valid jobs have the same ending time, the one with the earliest 
non-overlapping beginning time is optimal (In the example above, 
after scheduling job A, jobs C, D, and E are all valid as they start after time 2. 
Jobs C and E are considered more optimal as they start earlier than job D).

-If multiple optimal jobs have the same beginning time and ending times, 
the one that comes LATER in the input file should take precedent 
(In the example above, jobs C and E have the same beginning time and ending time;
in these cases you should break the tie by selecting the last one in the file, job E). 
*/

//you can get use the provided code here, change any parts of it, or completely start over

//find the earliest and shortest job
int findMin(int rows, int array[rows][3], int start, int currentEnd){
    int index = start;
    int startMin = 1000;
    int endMin = 1000;
    for(int i = start; i < rows; i++){
        if((array[i][2] <= endMin) && (array[i][1] <= startMin) && (array[i][1] != 0) && (array[i][1] > currentEnd)){
            startMin = array[i][1];
            endMin = array[i][2];
            index = i;
        }
    }
    //returns the index of that job so we can start at this new position
    return index;
}

int main(int argc, char* argv[]) {

    // First peek at how many jobs and timeslots there are
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    char buf[256];

    // Read the number of jobs to be scheduled
    if (!fscanf(fp, "%s\n", buf)) {
        perror("reading the number of jobs failed");
        exit(EXIT_FAILURE);
    }
    int jobcount = atoi(buf);

    // Next read the maximum number of timeslots
    if (!fscanf(fp, "%s\n", buf)) {
        perror("reading the number of timeslots failed");
        exit(EXIT_FAILURE);
    }
    int timeslots = atoi(buf);

    //creating 2d array to store jobs and their start and end times
    int jobArray[jobcount][3];
    int counter = 0;

    for (unsigned int slot=0; slot<timeslots; slot++) {
        FILE* fp = fopen(argv[1], "r");
        if (!fp) {
            perror("fopen failed");
            exit(EXIT_FAILURE);
        }

        // First read the number of jobs to be scheduled
        if (!fscanf(fp, "%s\n", buf)) {
            perror("reading the number of jobs failed");
            exit(EXIT_FAILURE);
        }
        // Next read the maximum number of timeslots
        if (!fscanf(fp, "%s\n", buf)) {
            perror("reading the number of timeslots failed");
            exit(EXIT_FAILURE);
        }
        // Now read the rest of the file
        for ( int line=0; line<jobcount; line++ ) {
            //reads line by line like "A 2 5"
            if (!fgets(buf, 256, fp)) {
                perror("reading a line for a job failed");
                exit(EXIT_FAILURE);
            }

            char job;
            unsigned int start;
            unsigned int end;
           
            if (!sscanf(buf, "%c %d %d", &job, &start, &end)) {
                perror("parsing a line for a job failed");
                exit(EXIT_FAILURE);
            }

            if (end == slot){
                //rough sorting into an array
                jobArray[counter][0] = (int)job; 
                jobArray[counter][1] = start;
                jobArray[counter][2] = end;
                counter += 1;
                continue;
            }

        }

    }

    // We've read the number of timeslots so close the file and start over
    fclose(fp);

    int currentEnd = 0;

    //loops through the array
    for(int i = 0; i < jobcount; i++){
        //finds the next earliest and shortest job
        int next = findMin(jobcount, jobArray, i, currentEnd);
        //makes sure it doesn't conflict with the previous job
        if(jobArray[i][1] > currentEnd){
            //prints out the job char
            printf("%c\n", jobArray[next][0]);
            currentEnd = jobArray[next][2];
            //starts at the new index to skip over any non possible jobs
            i = next;
        }
    }

    exit(EXIT_SUCCESS);

}



