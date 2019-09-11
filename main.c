#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include <stdbool.h>

struct student
{
	char *name;
	char *usfid;
	char *email;
	int pGrade;
	int eGrade;
	int tGrade;
};

void ShowMenu()
{
	printf("\nWelcome to Class Roll!\nPlease select one of the following options:");
	printf("\n1: Show all students\n2: Search for students\n3: Add a student\n4: Delete a student\n5: Edit a student's details\n6: Exit\n");
}

void SaveFile(struct student students[100], int count)
{
	FILE *fp = fopen("students.csv", "w");
	if (fp != NULL)
	{
		for (int i = 0; i < count; i++)
		{
			fprintf(fp, "%s,%s,%s,%d,%d,%d\n", students[i].name, students[i].usfid, students[i].email, students[i].pGrade, students[i].eGrade, students[i].tGrade);
		}
	}
	fclose(fp);
}

bool CheckStudentFormat(char entered[500])
{
	int i = 0;
	int num = 0;
	while (entered[i] != '\n' && entered[i] != '\0')
	{
		if (entered[i] == ',')
			num++;
		i++;
	}

	if (num == 5)
		return true;
	else
		return false;
}

int main()
{
	//I'm putting a *lot* of the code into main here because it will be easier to screw with this way.
	//Get ready for a long main function.

	//Also theres basically no validation (for now)

	//make room for 100 students, can increase or decrease this
	struct student students[100];

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
		fflush(stdin);
		printf("\n");
		switch (option)
		{
		case 1:
		{
			//Show all students
			printf("Students:\n");
			printf("%-20s  %-10s  %-30s  %-10s  %-10s  %-10s\n", "Name", "USF ID", "Email", "P Grade", "E Grade", "T Grade");
			for (int j = 0; j < count; j++)
			{
				printf("%-20s  %-10s  %-30s  %-10d  %-10d  %-10d\n", students[j].name, students[j].usfid, students[j].email, students[j].pGrade, students[j].eGrade, students[j].tGrade);
			}
			break;
		}
		case 2:
		{
			//Search for a student (just by uid right now, maybe add more options later?)
			char uid[10];
			printf("Enter a USF ID to search:\n");
			fgets(uid, sizeof uid, stdin); //the input
			printf("Student matching USF ID:\n");
			printf("%-20s  %-10s  %-30s  %-10s  %-10s  %-10s\n", "Name", "USF ID", "Email", "P Grade", "E Grade", "T Grade");
			for (int j = 0; j < count; j++)
			{
				if (!strcmp(uid, students[j].usfid))
					printf("%-20s  %-10s  %-30s  %-10d  %-10d  %-10d\n", students[j].name, students[j].usfid, students[j].email, students[j].pGrade, students[j].eGrade, students[j].tGrade);
			}
			break;
		}
		case 3:
		{
			//Add a student
			//Take in input and insert the data at count, then increment count.
			//TODO: I handle an empty string being entered, but not a format error.
			//maybe allow for CSV input?

			char info[500];
			printf("Enter student information in this format:\nFullName,USF ID,Email,PresentationGrade,EssayGrade,TermProjectGrade:\n");
			fgets(info, sizeof info, stdin); //the input
			if (info[0] != '\n')
			{
				if (CheckStudentFormat(info))
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
					i = 0;
					printf("Added student %s.\n", students[count].usfid);
					count++;
					SaveFile(students, count);
				}
				else
				{
					printf("Incorrect format of student data. Canceling student add.\n");
					break;
				}
			}
			else
			{
				//empty string recieved, dont add anything
				printf("Empty string encountered, add student canceled.\n");
			}
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
			//fgets(uid, sizeof uid, stdin); //eat buffer
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
			SaveFile(students, count);
			break;
		}
		case 5:
		{
			//Edit a student

			//TODO: Editing details adds an extra newline

			char input[10];
			char newData[500];
			printf("Enter a USF ID to edit that student:\n");
			fgets(input, sizeof input, stdin); //the input
			fflush(stdin);
			printf("Student you are editing:\n");
			printf("%-20s  %-10s  %-30s  %-10s  %-10s  %-10s\n", "Name", "USF ID", "Email", "P Grade", "E Grade", "T Grade");
			for (int j = 0; j < count; j++)
			{
				if (!strcmp(input, students[j].usfid))
				{
					printf("%-20s  %-10s  %-30s  %-10d  %-10d  %-10d\n", students[j].name, students[j].usfid, students[j].email, students[j].pGrade, students[j].eGrade, students[j].tGrade);
					printf("Which value would you like to edit? \n1: Name\n2: USF ID\n3: Email\n4: P Grade\n5: E Grade\n6: T Grade\n7: Cancel Edit\nPlease enter a number 1-7: ");
					fgets(input, sizeof input, stdin);
					fflush(stdin);
					printf("Please enter the new data: ");
					fgets(newData, sizeof newData, stdin);
					strtok(newData, "\n"); //removes newline from end of entered data
					fflush(stdin);

					switch (atoi(input))
					{
					case 1:
					{
						students[j].name = strdup(newData);
						break;
					}
					case 2:
					{
						students[j].usfid = strdup(newData);
						break;
					}
					case 3:
					{
						students[j].email = strdup(newData);
						break;
					}
					case 4:
					{
						students[j].pGrade = atoi(strdup(newData));
						break;
					}
					case 5:
					{
						students[j].eGrade = atoi(strdup(newData));
						break;
					}
					case 6:
					{

						students[j].tGrade = atoi(strdup(newData));
						break;
					}
					default:
					{
						printf("Incorrect option recieved. Canceling edit.");
						break;
					}
					}
				}
			}
			SaveFile(students,count);
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