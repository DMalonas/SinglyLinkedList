#include <stdio.h>
#include <stdlib.h>

typedef struct student {
    char name[100];
    float grade;
    int code;
    struct student *next;
} student;

student *head, *tail;

void add_list_end(const student *stud_ptr);
void add_list(const student *stud_ptr, int code);
void show_list();
student *find_node(int code);
void del_node(int code);
void free_list();

int main(void) {
    int sel, code;
    float grade;
    student stud, *ptr;


    head = NULL;
    while(1) {
        fprintf(stdout, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n", "1. Add Node End",
            "2. Add node", "3. Show List", "4. Find item", "5. Modify Node",
            "6. Delete node", "7. Free list and quit");
        while (fscanf(stdin, "%d", &sel) != 1) {
            fprintf(stdout, "\n%s\n", "Enter number: ");
            while(getchar() != '\n');
        }

        switch(sel) {
        case 1:
        case 2:
            getchar();
            printf("\nName: ");
            gets(stud.name);

            printf("\nCode: ");
            while(fscanf(stdin, "%d", &stud.code) != 1) {
                fprintf(stdout, "\n%s\n", "Enter number: ");
                while(getchar() != '\n');
            }

            printf("\nGrade: ");
            while(fscanf(stdin, "%f", &stud.grade) != 1) {
                fprintf(stdout, "\n%s\n", "Enter number: ");
                while(getchar() != '\n');
            }

            if (sel == 1) {
                add_list_end(&stud);
            } else {
                printf("\nEnter student code after which the new student will be added: ");
                scanf("%d", &code);
                add_list(&stud, code);
            }
            break;
        case 3:
            if (head == NULL) {
                printf("\nThe list is empty\n");
            } else {
                show_list();
            }
            break;
        case 4:
            if (head == NULL) {
                printf("\nThe list is empty\n");
            } else {
                printf("\nEnter student code to search: ");
                while(fscanf(stdin, "%d", &code) != 1) {
                    fprintf(stdout, "%s\n", "Enter number");
                    while(getchar() != '\n');
                }
                ptr = find_node(code);
                if (ptr == NULL) {
                    printf("\nStudent with code %d does not exist\n", code);
                } else {
                    printf("\nData: %s %.2f\n\n", ptr->name, ptr->grade);
                }
            }
            break;
        case 5:
            if (head == NULL) {
                printf("\nThe list is empty\n");
            } else {
                printf("\nEnter student code to modify: ");
                scanf("%d", &code);
                printf("Enter new grade: ");
                scanf("%f", &grade);
                ptr = find_node(code);
                if(ptr != NULL) {
                    ptr->grade = grade;
                } else {
                printf("\nStudent with code %d does not exist\n", code);
                }
            }
            break;
        case 6:
            if (head == NULL) {
                printf("\nThe list is empty \n");
            } else {
                printf("\nEnter student code to delete: ");
                scanf("%d", &code);
                del_node(code);
            }
            break;
        case 7:
            if (head != NULL) {
                free_list();
            }
        return 0;
        default:
            printf("\nWrong choice\n\n");
            break;
        }
    }
    return 0;
}


void add_list_end(const student *stud_ptr) {
    student *new_node;

    new_node = (student *) malloc(sizeof(student));
    if (new_node == NULL) {
        printf("Error: Not available memory\n");
        exit(1);
    }
    *new_node = *stud_ptr;
    new_node->next = NULL;

    if(head == NULL) {
        head = tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
}


void add_list(const student *stud_ptr, int code) {
    student *new_node, *ptr;

    ptr = head;

    while(ptr != NULL) {
        if (ptr->code == code) {
            new_node = (student *) malloc(sizeof(student));
            if (new_node == NULL) {
                exit(1);
            }
            *new_node = *stud_ptr;
            new_node->next = ptr->next;
            ptr->next = new_node;

            if(ptr == tail) {
                tail = new_node;
            }
            return;
        }
        ptr = ptr->next;
    }
    printf("\nStudent with code = %d does not exist\n", code);
}

void show_list() {
    student *ptr;
    ptr = head;
    printf("\n*** Student Data *****\n");
    while(ptr != NULL) {
        printf("Code: %d\n", ptr->code);
        printf("Name: %s\n", ptr->name);
        printf("Grade: %.2f\n\n", ptr->grade);
        ptr = ptr->next;
    }
}

student *find_node(int code) {
    student *ptr;
    ptr = head;
    while(ptr != NULL) {
        if(ptr->code == code) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void del_node(int code) {
    student *ptr, *prev_node;

    ptr = prev_node = head;
    while(ptr != NULL) {
        if (ptr->code == code) {
            if (ptr == head) {
                head = ptr->next;
            } else {
                prev_node->next = ptr->next;
                if (ptr == tail) {
                    tail = prev_node;
                }
            }
            free(ptr);
            printf("\nStudent with code = %d is deleted\n", code);
            return;
        }
        prev_node = ptr;
        ptr = ptr->next;
    }
    printf("\nStudent with code %d does not exists", code);
}

void free_list() {
    student *ptr, *next_node;

    ptr = head;
    while(ptr != NULL) {
        next_node = ptr->next;
        free(ptr);
        ptr = next_node;
    }
}

