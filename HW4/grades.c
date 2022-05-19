#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "grades.h"
#include "linked-list.h"

typedef struct grades {
	struct list *students_list;
} grades_t;

/* A linked list that each element in contains a student name, ID number and
 * points to his courses list. */
typedef struct student {
	char *name;
	int id;
	struct list *courses_list;
} student_t;

/* A linked list of a specific student that contains the courses he has 
 * studied and his grades. */
typedef struct course {
	char *name;
	int grade;
} course_t;

student_t* creat_student_iterator(char *name, int id) {
	student_t *iterator = malloc(sizeof(student_t));
	if (iterator == NULL) {
		free(iterator);
		return NULL;
	}
	iterator->name = name;
	iterator->id = id;
	iterator->courses_list = NULL;
	return iterator;
}

course_t* creat_course_iterator(char *name, int grade) {
	course_t *iterator = malloc(sizeof(course_t));
	if (iterator == NULL) {
		free(iterator);
		return NULL;
	}
	iterator->name = name;
	iterator->grade = grade;
	return iterator;
}

int clone_student_iterator(void *element, void **output) {
	student_t *in = (student_t*)element;
	student_t **out = (student_t**)output;
	*out = (student_t*)malloc(sizeof(student_t));
	
	char *clone_name = (char*)malloc((strlen(in->name)+1)*sizeof(char));
	strcpy(clone_name, in->name);
	
	if (!out || !clone_name) {
		free (out);
		free (clone_name);
		return -1;
	}
	(*out)->name = clone_name;
	(*out)->id = in->id;
	(*out)->courses_list = in->courses_list;
	free(in);
	return 0;
}

int clone_course_iterator(void *element, void **output) {
	course_t *in = (course_t*)element;
	course_t **out = (course_t**)output;
	*out = (course_t*)malloc(sizeof(course_t));
	
	char *clone_name = (char*)malloc((strlen(in->name)+1)*sizeof(char));
	strcpy(clone_name, in->name);
	
	if (!out || !clone_name) {
		free (out);
		free (clone_name);
		return -1;
	}
	(*out)->name = clone_name;
	(*out)->grade = in->grade;
	free(in);
	return 0;
}

void destroy_student_iterator(void *iterator) {
	student_t *destroy_iterator = (student_t*)iterator;
	free(destroy_iterator->name);
	list_destroy(destroy_iterator->courses_list);
	free(destroy_iterator);
	return;
}

void destroy_course_iterator(void *iterator) {
	course_t *destroy_iterator = (course_t*)iterator;
	free(destroy_iterator->name);
	free(destroy_iterator);
	return;
}

struct grades* grades_init() {	
	grades_t *all_students_data = malloc(sizeof(grades_t));
	all_students_data->students_list = list_init(clone_student_iterator, 
												destroy_student_iterator);
	return all_students_data;
}

void grades_destroy(struct grades *grades) {
	list_destroy(grades->students_list);
	free(grades);
}

int grades_add_student(struct grades *grades, const char *name, int id) {
	struct iterator *student_iter = list_begin(grades->students_list);
	if ((student_t*)list_get(student_iter) != NULL) {
		size_t students_amount = list_size(grades->students_list);
		for (size_t i=0; i<students_amount; i++) {
			if ((((student_t*)list_get(student_iter))->id) == id) {
				return -1;
			} else {
				student_iter = list_next(student_iter);
			}
		}
	}
	student_t *tmp_student = creat_student_iterator((char*)name, id);
	return list_push_back(grades->students_list, tmp_student);
	
}

int grades_add_grade(struct grades *grades, const char *name, int id, 
																int grade) {
	if (grades == NULL) {
		return -1;
	}
	if ((grade < 0) || (grade > 100)) {
		return -1;
	}
	struct iterator *student_iter = list_begin(grades->students_list);
	size_t students_amount = list_size(grades->students_list);
	for (size_t i=0; i<students_amount; i++) {
		student_t *tmp_student = (student_t*)list_get(student_iter);
		if (tmp_student->id == id) {
			if ((tmp_student->courses_list) == NULL) {
				tmp_student->courses_list = list_init(clone_course_iterator, 
													destroy_course_iterator);
				course_t *new_course = creat_course_iterator((char*)name, 
																	grade);
				if(!(list_push_back(tmp_student->courses_list, new_course))) {
					return 0;
				} else {
					return -1;
				}
			} else {
				struct iterator *course_iter = 
										list_begin(tmp_student->courses_list);
				size_t courses_amount = list_size(tmp_student->courses_list);
			
				for (size_t i=0; i<courses_amount; i++) {
					course_t *tmp_course = (course_t*)list_get(course_iter);
					if(!(strcmp(name, tmp_course->name))) {
						return -1;
					} else {
						course_iter = list_next(course_iter);
					}
				}
				course_t *new_course = creat_course_iterator((char*)name, 
																	grade);
				if (!(list_push_back(tmp_student->courses_list, new_course))) {
					return 0;
				} else {
					return -1;
				}
			}
		} else {
			student_iter = list_next(student_iter);
		}
	}
	return -1;
}

/* This function calculates the average of the course grades of
 * a specific student. Also, the variable 'out' will point the string 
 * of the student name. */
float grades_calc_avg(struct grades *grades, int id, char **out) {
	if (grades == NULL) {
		return -1;
	}
	struct iterator *student_iter = list_begin(grades->students_list);
	size_t students_amount = list_size(grades->students_list);

	for (int i=0; i<students_amount; i++) {
		student_t *tmp_student = ((student_t*)list_get(student_iter));
		if ((tmp_student->id) == id) {
			char *name_student = (char*)malloc((strlen(((student_t*)
				list_get(student_iter))->name)+1)*sizeof(char));
			strcpy(name_student,
				((student_t*)list_get(student_iter))->name);
			(*out) = name_student;

			struct iterator *course_iter = list_begin(((student_t*)
				list_get(student_iter))->courses_list);
			float courses_sum = 0;
			float grades_sum = 0;

			size_t courses_amount = list_size(tmp_student->courses_list);
			if (courses_amount == 0) {
				return 0;
			}

			for (int j=0; j<courses_amount; j++){
				courses_sum += 1;
				grades_sum += ((course_t*)list_get(course_iter))->grade;
				course_iter = list_next(course_iter);
			}
 
			float average = grades_sum / courses_sum;
			return average;
		}
		student_iter = list_next(student_iter);
	}
	return -1;
}

/* This function prints the student name, ID number, course names and grades
 * for a specific student.*/
int grades_print_student(struct grades *grades, int id) {
	if (grades == NULL){
		return -1;
	}
	struct iterator *search_id = list_begin(grades->students_list);
	student_t *tmp_student;
	size_t students_amount = list_size(grades->students_list);

	for (int i=0; i<students_amount; i++){

		if ((((student_t*)(list_get(search_id)))->id) == id) {
			tmp_student = ((student_t*)list_get(search_id));
			struct iterator *course_iter = 
										list_begin(tmp_student->courses_list);
	
			printf("%s %d:",tmp_student->name, tmp_student->id);
			
			int courses_amount = list_size(tmp_student->courses_list);
			if (courses_amount == 0){
				printf("\n");
				return 0;
			}
			for (int j=0; j<courses_amount-1; j++){
				printf(" %s %d,",
					((course_t*)list_get(course_iter))->name,
					((course_t*)list_get(course_iter))->grade);
				course_iter = list_next(course_iter);
			}
			printf(" %s %d",
				((course_t*)list_get(course_iter))->name,
				((course_t*)list_get(course_iter))->grade);
			printf("\n");
			return 0;
		}
		search_id = list_next(search_id);		
	}
	return -1;
}

/* This function prints the student's name, ID number, course names and grades
 * for each of the students on the list, using the 'grades_print_student'
 * function that performs this for a single student.*/
int grades_print_all(struct grades *grades) {
	if (grades == NULL) {
		return -1;
	}
	struct iterator *student_iter = list_begin(grades->students_list);
	size_t students_amount = list_size(grades->students_list);

	for(int i=0; i<students_amount; i++){
		grades_print_student(grades,
			((student_t*)list_get(student_iter))->id);
		student_iter = list_next(student_iter);
	}
	return 0;
}

