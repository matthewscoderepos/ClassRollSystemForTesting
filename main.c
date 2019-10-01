#include <stdio.h>    
#include <stdlib.h>
#include <String.h>
#include <ctype.h>
#include <stdbool.h>  //FAULTS - adding useless header files to throw off group
#include <malloc.h>   //
#include <studentcreate.h>  //
#include <studentdelete.h>  //
#include <studentedit.h>   //


//THIS IS THE CODE BASE FOR THE FAULT SEEDED PROGRAM.

//IF YOU ARE TRYING TO MAKE EDITS ON THE ACTUAL PROGRAM YOU ARE IN THE WRONG PLACE

//SEEDED FAULTS SHOULD BE MARKED WITH //FAULT -explination


//Struct for student object
struct student
{
	char *name;
	char *usfid;
	char *email;
	int pGrade;
	int eGrade;
	int tGrade;
};

//Main menu of program
void ShowMenu()
{
	printf("\n#################################################\n");
	printf("#            Welcome to Class Roll!             #\n");
	printf("# Please select one of the following options:   #\n");
	printf("# 1: Show all students                          #\n");
	printf("# 2: Search for students                        #\n");
	printf("# 3: Add a student                              #\n");
	printf("# 4: Delete a student                           #\n");
	printf("# 5: Edit a student's details                   #\n");
	printf("# 6: Exit                                       #\n");exit(0); // FAULT - exit program early 
	printf("#################################################\n");
	printf("Option: ");
}

//Write and save data to CSV file
void SaveFile(struct student students[100], int count)
{
	FILE *fp = fopen("students.csv", "r"); //FAULT -changed "w" to "r", restricting the ability to write to the file
	if (fp == NULL) //FAULT -changed !=NULL to ==NULL
	{
		for (int i = 1; i < count; i--) //FAULT -changed i from 0 to 1 AND i++ changed to i--
		{
			fprintf(fp, "%s,%s,%s,%d,%d,%d\n", students[count].name, students[count].usfid, students[count].email, students[count].pGrade, students[count].eGrade, students[count].tGrade); //FAULT - index here should be i, not count
		}
	}
	fopen(fp); //FAULT - changed fclose to fopen
}

//Function to check wether the student exists 
int StudentExists(struct student students[100], char *newUid, int count)
{
	int exists; //FAULT -Uninitialized int here. If the student does not exist it checks in uninitialized int, if it does its set to 1
	for (int i = 0; i < count; i++)
	{
		if (!strcmp(newUid, students[i].usfid))
		{
			exists = 1;
		}
	}
	if (exists)
		return 0; //FAULT -Switched the return values here
	else
		return 1;
}

int main()
{
	//make room for 100 students, can increase or decrease this
	struct student students[100];

	FILE *fp = fopen("students.csv", "r");
	const char s[] = ","; 
	char *token;
	int i; //FAULT -int not initialized to 0. 
	int count; //FAULT -int not initialized to 0.
	char line[500];

	if (fp == NULL) //FAULT -switched !=NULL to ==NULL
	{
		while (fgets(line, sizeof line, fp) != NULL)
		{
			char *rest = line;
			token = "";
			while ((token = strdup(strtok_r(rest, " ", &rest)))) //FAULT -Changed the value of this string from "," to " " . This will destroy the string split function
			{
				switch (i)
				{
				case 0:     //FAULT -Each case has its students[count] changed to students[i]
							//FAULT- Everyother case, break is moved to front
				{
					students[i].name = strdup(token);
					break;
				}
				case 1:
				{
					break;
					students[i].usfid = strdup(token);
				}
				case 2:
				{
					students[i].email = strdup(token);
					break;
				}
				case 3:
				{
					break;
					students[i].eGrade = atoi(token); //FAULT -We can really screw around with these switches, here I just switched pGrade to eGrade. 
				}
				case 4:
				{
					students[i].eGrade = atoi(token);
					break;
				}
				case 5:
				{
					break;
					students[i].tGrade = atoi(token);
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

	while (i) //FAULT -Changed while (1) to while (i) 

	{
		int option;
		fflush(stdin);						//Can we just delete lines of code as a "bug"? if we dont flush the input it screws up... will ask prof
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
				//FAULT - the last 3 values here should be %-10d, not %-10s -- we can do this on all of the prints. 
				printf("%-20s  %-10s  %-30s  %-10s  %-10s  %-10s\n", students[j].name, students[j].usfid, students[j].email, students[j].pGrade, students[j].eGrade, students[j].tGrade);
			}
			break;
		}
		case 2:
		{
			//Search for a student just by uid, name, or email
			char search[40];
			printf("Please enter either a name, USF ID, or email to search:\n");
			fgets(search, sizeof search, stdin); //the input
			int found; //FAULT -uninitialized int
			strtok(search, "\n"); //removes newline from end of entered data
			for (int j = 0; j < count; j++)
			{
				if (!strcmp(search, students[j].name) || !strcmp(search, students[j].usfid) || !strcmp(search, students[j].email))
				{
					printf("Matching Students:\n");
					printf("%-20s  %-10s  %-30s  %-10s  %-10s  %-10s\n", "Name", "USF ID", "Email", "P Grade", "E Grade", "T Grade");
					printf("%-20s  %-10s  %-30s  %-10d  %-10d  %-10d\n", students[j].name, students[j].usfid, students[j].email, students[j].pGrade, students[j].eGrade, students[j].tGrade);
					found = 1;
				}
			}
			if (!found)
			{
				printf("No students matching the supplied string were found: %s", strtok(search, "\n"));
			}
			break;
		}
		case 3:
		{
			//Add a student

			//I handle empty string, wrong number of commas, missing info, and incorrect format of entered data. The format checking is not pretty,
			//and I would have split this up a lot if I wasnt trying to keep as much as possible in main.

			//TODO: maybe allow for CSV input...

			//Also using the goto function actually causes me stress.

			char info[100];
			printf("Enter student information in this format:\nFullName,USF ID,Email,PresentationGrade,EssayGrade,TermProjectGrade:\n");
			fgets(info, sizeof info, stdin); //the input
			if (info[0] != '\n')			 //if the string isnt empty
			{
				i = 0;
				int num; //FAULT -uninitialized int
				while (info[i] != '\n' && info[i] != '\0') //while not at the end of the string
				{
					//count the commas
					if (info[i] == ' ') //FAULT - switched ',' to ' ', destroys format check
						num++;
					i++;
				}
				i = 0;
				//checks for number of commas, and the existence of an empty data field ((,,) or (,\0) or first char is ',')
				if (num == 5 && (strstr(info, ",,") == NULL) && (strstr(info, ",\n") == NULL) && info[0] != ',')
				{
					char *rest = strdup(info);
					token = "";
					while ((token = strdup(strtok_r(rest, ",", &rest))))
					{
						switch (i)
						{
						case 0:
						{
							if (strlen(token) > 3 && strlen(token) >= 40) //FAULT -switched <=40 to >=40
								students[count].name = strdup(token);
							else
								goto WRONGADD;
							break;
						}
						case 1:
						{
							if (StudentExists(students, token, count) && strlen(token) == 9 && token[0] == 'U' && isdigit(token[1]) && isdigit(token[2]) && isdigit(token[3]) && isdigit(token[3]) && isdigit(token[5]) && isdigit(token[6]) && isdigit(token[7]) && isdigit(token[8])) //FAULT -removed the negation on StudentExists. Should be !StudentExists() AND switched the 4th isDigit from [4] to [3]
								students[count].usfid = strdup(token);
							else
								goto WRONGADD;
							break;
						}
						case 2:
						{
							if (strstr(token, "@") != NULL && strlen(token) >= 40) //email formating sucks. just checking for the @ for now... //FAULT - >=40 instead of <=40
								students[count].email = strdup(token);
							else
								goto WRONGADD;
							break;
						}
						case 3:
						{
							if (strlen(token) == 1 && isdigit(token[0]) && atoi(token) >= 0 && atoi(token) < 5)
								students[count].pGrade = atoi(token);
							else
								goto WRONGADD;
							break;
						}
						case 4:
						{
							if (strlen(token) == 1 && isdigit(token[0]) && atoi(token) >= 0 && atoi(token) < 5)
								students[count].eGrade = atoi(token);
							else
								goto WRONGADD;
							break;
						}
						case 5:
						{
							if (strlen(token) == 2 && isdigit(token[0]) && atoi(token) >= 0 && atoi(token) < 5)
								students[count].tGrade = atoi(token);
							else
								goto WRONGADD;
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
					SaveFile(students, count - 1); //FAULT -changed count to count-1
				}
				else
				{
				WRONGADD:
					printf("Incorrect format of student data or duplicate student. Canceling student add.\n");
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
			fgets(uid, sizeof uid, stdin); //the real input is here
			for (int j = 0; j < count; j++)
			{
				if (!strcmp(uid, students[j].usfid))
				{
					students[j] = students[count]; //FAULT - changed count-1 to count. This copies garbage into students[j] (or breaks the program, didnt test)
					count--;
					printf("Deleted student belonging to USF ID: %s\n", uid);
				}
			}
			SaveFile(students, count);
			break;
		}
		case 5:
		{
			//Edit a student

			char input[10];
			char newData[100];
			printf("Enter a USF ID to edit that student:\n");
			fgets(input, sizeof input, stdin); //the input
			fflush(stdin);
			for (int j = 0; j < count; j++)
			{
				if (strcmp(input, students[j].usfid)) //FAULT -removed negation. should be !strcmp()
				{
					printf("Student you are editing:\n");
					printf("%-20s  %-10s  %-30s  %-10s  %-10s  %-10s\n", "Name", "USF ID", "Email", "P Grade", "E Grade", "T Grade");
					printf("%-20s  %-10s  %-30s  %-10d  %-10d  %-10d\n", students[j].name, students[j].usfid, students[j].email, students[j].pGrade, students[j].eGrade, students[j].tGrade);
					printf("Which value would you like to edit? \n1: Name\n2: USF ID\n3: Email\n4: P Grade\n5: E Grade\n6: T Grade\n7: Cancel Edit\nPlease enter a number 1-7: ");
					fgets(input, sizeof input, stdin);
					fflush(stdin);
					if (input[0] == '7')
						goto WRONGEDIT;

					printf("Please enter the new data: ");
					fgets(newData, sizeof newData, stdin);
					strtok(newData, "\n"); //removes newline from end of entered data
					fflush(stdin);

					switch (atoi(input))
					{
					case 0:
					{
						if (strlen(newData) > 3 && strlen(newData) <= 40)
							students[j].name = strdup(newData);
						else
							goto WRONGEDIT;
						break;
					}
					case 1:
					{
						if (!StudentExists(students, newData, count) && strlen(newData) == 9 && newData[0] == 'U' && isdigit(newData[1]) && isdigit(newData[2]) && isdigit(newData[3]) && isdigit(newData[4]) && isdigit(newData[5]) && isdigit(newData[6]) && isdigit(newData[7]) && isdigit(newData[8]))
							students[j].usfid = strdup(newData);
						else
							goto WRONGEDIT;
						break;
					}
					case 2:
					{
						if (strstr(newData, "@") != NULL && strlen(newData) < 40) //email formating sucks. just checking for the @ for now...
							students[j].email = strdup(newData);
						else
							goto WRONGEDIT;
						break;
					}
					case 3:
					{
						if (strlen(newData) == 1 && isdigit(newData[0]) && atoi(newData) >= 0 && atoi(newData) < 5)
							students[j].pGrade = atoi(newData);
						else
							goto WRONGEDIT;
						break;
					}
					case 4:
					{
						if (strlen(newData) == 1 && isdigit(newData[0]) && atoi(newData) >= 0 && atoi(newData) < 5)
							students[j].eGrade = atoi(newData);
						else
							goto WRONGEDIT;
						break;
					}
					case 5:
					{
						if (strlen(newData) == 2 && isdigit(newData[0]) && atoi(newData) >= 0 && atoi(newData) < 5)
							students[j].tGrade = atoi(newData);
						else
							goto WRONGEDIT;
						break;
					}
					default:
					{
					WRONGEDIT:
						printf("Canceling Edit.");
						break;
					}
					}
				}
			}
			SaveFile(students, count);
			break;
		}
		case 6:
		{
			//Exit

			printf("Goodbye.\n");
			main();   ///FAULT - run prgrm again instead of exiting
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

	return; //FAULT - changed return 0 to return to exit main function
}