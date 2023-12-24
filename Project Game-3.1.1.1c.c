#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
	
int random(){
	int unique[8], currentNum;
	static int numbers[16];
	srand(time(NULL));
	
	for(int i = 0;i < 8;i++){
		bool check;
		
		do{
			currentNum = rand() % 26 + 65;
			check = true;
													//Untuk dapatin 8 angka berbeda
			for(int j = 0;j < i;j++){
				if(unique[j] == currentNum){
					check = false;
					break;
				}
			}
		} while(!check);
		unique[i] = currentNum;
	}
		
	
	for(int i = 0;i < 8;i++){
		for(int j = 0;j < 2;j++){      
			numbers[(i*2)+j] = unique[i];			//Dapatin pasangan dari 8 angka yg uda ada
		}
	}
	
	for(int i = 15;i > 0;i--){
		int j = rand() % (i+1);
		int temp = numbers[i];
		numbers[i] = numbers[j];				//Acak urutan angka
		numbers[j] = temp;
	}
	
	return numbers;
}

void print(){
	for(int i = 0;i < 4;i++){
		for(int j = 0;j < 4;j++){
			printf("#\t");
		}
		printf("\n");
	}
}

void printMatch(int keep[], int size){
	for(int i = 0;i < 16;i++){
		bool pass = false;
		if(i % 4 == 0 && i > 0){
			printf("\n");
		}
		for(int j = 0;j < size;j++){
			if(i == keep[j] - 1){
				printf(" \t");
				pass = true;
				break;
			}
		}
		if(pass){
			continue;
		} else{
			printf("#\t");
		}
	}
}

void choiceGuide(int keep[], int size, bool correct){
	for(int i = 1;i <= 16;i++){
		bool pass = false;
		if(correct){
			for(int j = 0;j < size;j++){
				if(i == keep[j]){
					printf(" \t");
					pass = true;
					break;
				}
			}
		}
		if(pass){
			if(i % 4 == 0){
				printf("\n");
			}
			continue;
		} else{
			printf("%d\t", i);
			if(i % 4 == 0){
			printf("\n");
			}
		}

	}
}

int scanChoice(int choice1, int choice2, int keep[], int size, bool correct){
	if(choice1 > 16 || choice2 > 16){
		printf("Invalid choices. Please try again!\n\n");
		return -1;
	} else if(choice1 == 0 || choice2 == 0){
		printf("Thank you for playing!\n");
		return 0;
	} else if(choice1 == choice2){
		printf("Choice may not be the same as the first!\n\n");
		return 2;
	} else if(correct){
		for(int i = 0;i < size;i++){
			if(choice1 == keep[i] || choice2 == keep[i]){
				printf("Your choice is matched previously.\n\n");
				return -3;
			}
		}
	}
	return 1;
}

void printRules() {
    printf("=========================================================\n");
    printf("                   Memory Game Rules                     \n");
    printf("=========================================================\n");
    printf("1. The game consists of a 4x4 grid of cards.\n");
    printf("2. Each card has a matching pair.\n");
    printf("3. Your goal is to find all matching pairs.\n");
    printf("4. Enter the card numbers to flip them.\n");
    printf("5. The game continues until all pairs are found.\n");
    printf("6. Enter '0' to exit the game.\n");
    printf("=========================================================\n\n");
}

void saveScore(char playerName[], int score) {
    FILE *file = fopen("leaderboard.txt", "a");
    if (file == NULL) {
        printf("Error opening the leaderboard file.\n");
        return;
    }

    fprintf(file, "%s %d\n", playerName, score);
    fclose(file);
}	


void bubbleSort() {
    FILE *file = fopen("leaderboard.txt", "r");
    if (file == NULL) {
        printf("No leaderboard data found.\n");
        return;
    }

    // Read entries into an array
    struct Entry {
        char playerName[200];
        int score;
    };

    int numEntries = 0;
    struct Entry entries[100];  // Assuming a maximum of 100 entries

    while (fscanf(file, "%s %d", entries[numEntries].playerName, &entries[numEntries].score) != EOF) {
        numEntries++;
    }

    fclose(file);

    // Perform bubble sort in ascending order (lowest to highest)
    for (int i = 0; i < numEntries - 1; i++) {
        for (int j = 0; j < numEntries - i - 1; j++) {
            if (entries[j].score > entries[j + 1].score) {
                // Swap entries
                struct Entry temp = entries[j];
                entries[j] = entries[j + 1];
                entries[j + 1] = temp;
            }
        }
    }

    // Print the sorted leaderboard with numbers
    printf("\n===== Leaderboard =====\n");
    for (int i = 0; i < numEntries; i++) {
        printf("%d. %s - %d\n", i + 1, entries[i].playerName, entries[i].score);
    }
    printf("\n");
}
void printLeaderboard() {
    

    FILE *file = fopen("leaderboard.txt", "r");
    if (file == NULL) {
        printf("No leaderboard data found.\n");
        return;
    }

    // Read entries into an array
    struct Entry {
        char playerName[200];
        int score;
    };

    int numEntries = 0;
    struct Entry entries[100];  // Assuming a maximum of 100 entries

    while (fscanf(file, "%s %d", entries[numEntries].playerName, &entries[numEntries].score) != EOF) {
        numEntries++;
    }

    fclose(file);

    
    

    bubbleSort(); // Sort and print the leaderboard
}

void printOpen(bool correct, int keep[], int choice1, int choice2, int size, int nums[]){
	bool check = false;
	for(int i = 1;i <= 16;i++){
		if(correct){
			for(int j = 0;j < size;j++){
				if(i == keep[j]){
					check = true;
					break;
				}
			}
		}
		if(i == choice1){
			printf("%c\t", nums[choice1 - 1]);
		} else if(i == choice2){
			printf("%c\t", nums[choice2 - 1]);
		} else if(check){
			check = false;
			printf(" \t");
		} else{
			printf("#\t");
		}
		if(i % 4 == 0){
			printf("\n");
		}
	}
	printf("\n");
}

int main(){
	restart:
	printf("\n\n");
    printf("=========================================================\n");
    printf("                 WELCOME TO MEMORY GAMES                 \n");
    printf("=========================================================\n\n");
	
	printRules();
	char playerName[100];
    printf("\nEnter your first name: ");
    scanf("%s", &playerName);
    printf("Lets play's memory games %s\n\n", playerName);
   
	time_t t;
	srand((unsigned) time(&t));
	char restart[5];
	int m = 0, score = 0;
	bool check = false, correct = false;
	int* nums = random();
	int choice1 = 1, choice2 = 1, confirm;
	int keepChoice[16];
	
	while (choice1 > 0){
		if(correct){
			printMatch(keepChoice, m);
			printf("\n\n");
			choiceGuide(keepChoice, m, correct);
			printf("\n");
		} else{
			print();
			printf("\n");
			choiceGuide(keepChoice, m, correct);
			printf("\n");
		}
		
		again1:
		printf("Press 0 to exit.\nEnter your choice between 1 - 16: ");
		scanf("%d", &choice1);
		confirm = scanChoice(choice1, -5, keepChoice, m, correct);
		if(confirm == -1){
			goto again1;
		} else if(confirm == 0){
			return 0;
		} else if(confirm == -3){
			goto again1;
		}
		
		printOpen(correct, keepChoice, choice1, -1, m, nums);
		
		again2:
		printf("Press 0 to exit.\nEnter your choice between 1 - 16: ");
		scanf("%d", &choice2);
		confirm = scanChoice(choice1, choice2, keepChoice, m, correct);
		if(confirm == -1){
			goto again2;
		} else if(confirm == 0){
			return 0;
		} else if(confirm == 2){
			goto again2;
		} else if(confirm == -3){
			goto again2;
		}
		
		printOpen(correct, keepChoice, choice1, choice2, m, nums);
		
		score++;
		
		if(nums[choice1 - 1] == nums[choice2 - 1]){
			printf("Your choices matched!\n");
			keepChoice[m] = choice1;
			m++;
			keepChoice[m] = choice2;
			m++;
			correct = true;
			if(m == 16){
				printf("You beat the Game!!!.\n");
				printf("Your score: %d\n", score);
				saveScore(playerName, score);
				printLeaderboard();
				printf("Do you want to restart the game? (Type YES or NO)\n");
				scanf("%s", restart);
				if(strcmp(restart, "YES||yes") == 0){
					system("cls");
					goto restart;
				} else if(strcmp(restart, "NO||no") == 0){
					printf("Thanks for playing the game %s!\n", playerName);
					return 0;
				}
			} else{
				printf("Clearing in 3 seconds.");
				sleep(3);
				system("cls");
			}
		} else{
			printf("Your choices doesn't match.\nClearing in 3 seconds.\n");
			sleep(3);
			system("cls");
		}
		
	}
	
	return 0;
}
