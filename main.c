#include <stdio.h>
#include <stdlib.h>
#include <String.h>

void ShowMenu()
{
	printf("\nWelcome to Class Roll!\nPlease select one of the following options:");
	printf("\n1: Show all students\n2: Search for students\n3: Add a student\n4: Delete a student\n5: Edit a student's details\n6: Exit\n");
}

struct student
{
	char *name;
	char *usfid;
	char *email;
	int pGrade;
	int eGrade;
	int tGrade;
};

int main()
{
	//make room for 100 students, can increase or decrease this
	struct student students[10];

	FILE *fp = fopen("students.csv", "r");
	const char s[] = ",";
	char *token;
	int i = 0;
	int count = 0;
	char line[500];

	if (fp != NULL)
	{
		while (fgets(line, sizeof line, fp) != NULL)
		{
			char *rest = line;
			token = "";
			while ((token = strdup(strtok_r(rest, ",", &rest))))
			{
				switch (i)
				{
				case 0:
				{
					students[count].name = strdup(token);
					break;
				}
				case 1:
				{
					students[count].usfid = strdup(token);
					break;
				}
				case 2:
				{
					students[count].email = strdup(token);
					break;
				}
				case 3:
				{
					students[count].pGrade = atoi(token);
					break;
				}
				case 4:
				{
					students[count].eGrade = atoi(token);
					break;
				}
				case 5:
				{
					students[count].tGrade = atoi(token);
					break;
				}
				default:
				{
					printf("Read in something for the wrong student");
					break;
				}
				}
				i++;
			}
			count++;
			i = 0;
		}
		fclose(fp);
	}

	while (1)
	{
		int option;
		fgets(line, sizeof line, fp);
		ShowMenu();
		scanf("%d", &option);
		printf("\n");

		switch (option)
		{
		case 1:
		{
			//Show all students
			printf("Students:\n");
			for (int j = 0; j < count; j++)
			{
				printf("\n%s, %s, %s, %d, %d, %d\n", students[j].name, students[j].usfid, students[j].email, students[j].pGrade, students[j].eGrade, students[j].tGrade);
			}
			break;
		}
		case 2:
		{
			//Search for a student (just by uid right now, maybe add more options later?)
			char uid[10];
			printf("Enter a USF ID to search:\n");
			fgets(uid, sizeof uid, stdin); //eat buffer
			fgets(uid, sizeof uid, stdin); //the real input is here
			printf("Student matching (USF ID):\n");
			for (int j = 0; j < count; j++)
			{
				if (!strcmp(uid, students[j].usfid))
					printf("\n%s, %s, %s, %d, %d, %d\n", students[j].name, students[j].usfid, students[j].email, students[j].pGrade, students[j].eGrade, students[j].tGrade);
			}
			break;
		}
		case 3:
		{
			//Add a student
			//Take in input and insert the data at count, then increment count.
			//Make sure to write to file here or call a function to do it
			//Also there should be a cancel function. Maybe a blank input is good enough for that
			char info[500];
			printf("Enter student information in this format:\nFullName,USF ID,Email,PresentationGrade,EssayGrade,TermProjectGrade:\n");
			fgets(info, sizeof info, stdin); //eat buffer
			fgets(info, sizeof info, stdin); //the real input is here
			printf("%s", info);
			if (info[0] != '\0')
			{
				char *rest = strdup(info);
				token = "";
				while ((token = strdup(strtok_r(rest, ",", &rest))))
				{
					switch (i)
					{
					case 0:
					{
						students[count].name = strdup(token);
						break;
					}
					case 1:
					{
						students[count].usfid = strdup(token);
						break;
					}
					case 2:
					{
						students[count].email = strdup(token);
						break;
					}
					case 3:
					{
						students[count].pGrade = atoi(token);
						break;
					}
					case 4:
					{
						students[count].eGrade = atoi(token);
						break;
					}
					case 5:
					{
						students[count].tGrade = atoi(token);
						break;
					}
					default:
					{
						printf("Read in something for the wrong student");
						break;
					}
					}
					i++;
				}
				count++;
				//CallSomeSortOfFileWriteHere();
			}
			else
			{
				//empty string recieved, dont add anything
			}

			//maybe allow for CSV input? Probably just do manual input for now.

			break;
		}
		case 4:
		{
			//Delete a student
			//Get an ID from the user, find that student, copy the last student to that students spot, decrement count
			//Since we'd only print up to the count and always add students to students[count] we can just let the copied data stay
			//until overwritten

			char uid[10];
			printf("Enter a USF ID to delete that student:\n");
			fgets(uid, sizeof uid, stdin); //eat buffer
			fgets(uid, sizeof uid, stdin); //the real input is here
			for (int j = 0; j < count; j++)
			{
				if (!strcmp(uid, students[j].usfid))
				{
					students[j] = students[count - 1];
					count--;
					printf("Deleted student belonging to USF ID: %s", uid);
				}
			}
			//CallSomeSortOfFileWriteHere();
			break;
		}
		case 5:
		{
			//Edit a student

			//This is a tricky one. Do we just read in all of the data on a usf id again, or do we let the user give an ID and then let
			//them chose the data they want to change. Obviously easier the first way but better the second.
			printf("Enter a USF ID to edit that student:\n");
			break;
		}
		case 6:
		{
			//Exit

			printf("Goodbye.\n");
			return 0;
			break;
		}
		default:
		{
			printf("Incorrect Input Encountered.");
			break;
		}
		}
	}

	return 0;
}