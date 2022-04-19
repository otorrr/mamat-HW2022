#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MIN_GRADE 1
#define MAX_GRADE 100
#define HISTO_LENGTH 100
#define PASS_GRADE 55
#define CALC_PREC 100

int main(int argc, char *argv[]) {
    if (argc < 1) {
        fprintf(stderr, "Error\n");
        return 1;
    }

    /* Create the new file "course_statistics" with write permission. */
	FILE *fp1, *fp2;
    int size_of_dest = strlen(argv[1]) + strlen("/course_statistics.txt") + 1;
    char *dest = NULL; 
    dest = (char*)malloc(sizeof(char)* size_of_dest);
    if(dest == NULL){
    	return 0;
    }
    strcat(dest, argv[1]);
    strcat(dest, "/course_statistics.txt");
    fp1 = fopen(dest, "w");
    if (!fp1) {
    	printf("ERROR !!!\n");
    	exit(0);
    }
    /* Open the file "grades" with read permission. */
	fp2 = fopen(argv[2], "r");
    if (!fp2) {
    	printf("ERROR !!!\n");
    	exit(0);
    }
	
    int stud_num = 0;
    int sum = 0;
    int min=MAX_GRADE, max = MIN_GRADE;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int pass_grades = 0;
    float pass_stud = 0;
    float avg = 0.0;
    int grades_hist[HISTO_LENGTH] = {0};
    int median = 0;
    int counter = 0;
    int median_grade = 0;
	
    while((read = getline(&line, &len, fp2)) != -1) {
    	stud_num++;
    	sum += atoi(line);
    	if(atoi(line) >= PASS_GRADE){
    		pass_grades++;
    	}

    	if(atoi(line) < min){
    		min = atoi(line);
    	}

    	if(atoi(line) > max){
    		max = atoi(line);
    	}
    	grades_hist[atoi(line) - 1]++;
    }
    avg = (float)sum/stud_num;
    pass_stud = ((float)pass_grades/stud_num)*CALC_PREC;
    
	median = (stud_num + 1)/2;
    for(int i = 0; i < HISTO_LENGTH; i++){
    	if(grades_hist[i] != 0){
    		counter = counter + grades_hist[i];
    	}
    	
    	if(counter >= median){
    		median_grade = i + 1;
    		break;
    	}
    }
    
	fprintf(fp1, "num of students = %d\navg = %.3f\n", stud_num, avg);
   	fprintf(fp1, "the median is - %d\nmax grade = %d, min grade = %d\n", 
			median_grade, max, min);
   	fprintf(fp1, "pass rate = %.2f%%\n", pass_stud);
	
   	for(int j = 0; j < HISTO_LENGTH; j++){
   		if(j%10 == 0 && j != 0){
   			fprintf(fp1, "\n");
   		}
		
		if (((j+1) % 10) == 0) {
			fprintf(fp1, "%d", grades_hist[j]);
		} else {
			fprintf(fp1, "%d ", grades_hist[j]);
		}
   	}
   	fprintf(fp1, "\n");

	/* Once we have opened a file we must close it. */
    fclose(fp1);
    fclose(fp2);

    return 0;
}
