/*
    Author: Abhishek Adhikari
    Date: 15th September 2024
    Topic: This is a Smart Farm Management System Application Project of the C program that is well structured into different sections corresponding to the functionalities described.
    Program Structure:
      o Main Menu:
            Manage Crops
            Irrigation Scheduling
            Expense Tracking
            Exit

      o Manage Crops:
            Add Crop Details
            View All Crops
            Update Crop Status
            Delete Crop

      o Irrigation Scheduling:
            Input Field Data
            Irrigation Need Calculation
            Water Requirement Calculation
            Generate Irrigation Schedule

      o Expense Tracking:
            Add Expenses
            View Monthly Expenses
            Calculate Total and Average Expenses
            Expense Log

      o Exit:
            Save all data to farmerDetails.txt and exit.

    Additional: The program will keep asking for input until a valid data type is entered. This filters the inputs and avoid crashing the program.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define FILENAME "farmerDetails.txt"
#define MAX_LINE_LENGTH 256

//? Structure Definitions
typedef struct
{
    char name[50];
    float area;
    float yield;
    char plantingDate[11];
    char harvestDate[11];
    char status[20];
} Crop;

typedef struct
{
    float amount;
    char category[20];
    char description[100];
} Expense;

typedef struct
{
    char cropType[50];
    float area;
    float soilMoisture;
} Field;

//* Function Prototypes or definations
void mainMenu();

// Managing Crops Functions
void manageCropsMenu();
void addCrop();
void viewCrops();
void updateCropStatus();
void deleteCrop();

// Irrigation Scheduling Functions
void irrigationSchedulingMenu();
void inputFieldData();
void calculateIrrigationNeed();
void calculateWaterRequirement();

void generateIrrigationSchedule();

// Expense Tracking Functions
void expenseTrackingMenu();
void addExpense();
void viewMonthlyExpenses();
void calculateTotalAndAverageExpenses();
void viewExpenseLog();

// Utility Functions
void loadData();
void saveData();
char *lowerCase(char *s);
void holdingTerminal()
{
    // todos: Pausing in Windows
    system("pause");

    // todos: Pausing in UNIX based systems -> Linux or MacOS
    //  system("read -n 1 -s")

    // todos: Pausing in Enviroment Container -> Docker Container
    //  system("read -p 'Press Enter to continue...' var");
}

// Global Variables
FILE *fp;
Crop *crops = NULL;
Expense *expenses = NULL;
Field *fields = NULL;
int cropCount = 0, expenseCount = 0, fieldCount = 0;

int main()
{
    loadData();
    mainMenu();
    return 0;
}

void mainMenu()
{
    int choice, validInput;

    do
    {
        printf("\033[1;34m\nWelcome to Smart Farm Management System\033[0m\n");
        printf("\033[1;34m------------------------------------------------------\033[0m\n");
        printf("\033[1;37m1.\033[0m Manage Crops\n");
        printf("\033[1;37m2.\033[0m Irrigation Scheduling\n");
        printf("\033[1;37m3.\033[0m Expense Tracking\n");
        printf("\033[1;37m4.\033[0m Exit\n");
        do
        {
            printf("Enter your choice: ");
            validInput = scanf("%d", &choice);

            if (validInput != 1)
            {
                printf("\033[1;31mInvalid input. Please enter only an integer.\033[0m\n");
                while (getchar() != '\n')
                    ;
            }
        } while (validInput != 1);

        printf("\n");
        switch (choice)
        {
        case 1:
            manageCropsMenu();
            break;
        case 2:
            irrigationSchedulingMenu();
            break;
        case 3:
            expenseTrackingMenu();
            break;
        case 4:
            printf("\033[1;33mSaving Data State Into File... Please Wait.\033[0m\n");
            saveData();
            free(crops);
            free(expenses);
            printf("\033[1;32mSaved Successfully.\033[0m\n");
            break;
        default:
            printf("\033[1;31mInvalid choice. Please try again.\033[0m\n");
        }
    } while (choice != 4);
}

void manageCropsMenu()
{
    int choice, validInput;

    do
    {
        printf("\n\033[1;35mManage Crops Menu\033[0m\n");
        printf("\033[1;35m------------------------------------------------------\033[0m\n");
        printf("\033[1;37m1.\033[0m Add Crop Details\n");
        printf("\033[1;37m2.\033[0m View All Crops\n");
        printf("\033[1;37m3.\033[0m Update Crop Status\n");
        printf("\033[1;37m4.\033[0m Delete Crop\n");
        printf("\033[1;37m5.\033[0m Back to Main Menu\n");
        do
        {
            printf("Enter your choice: ");
            validInput = scanf("%d", &choice);

            if (validInput != 1)
            {
                printf("\033[1;31mInvalid input. Please enter only an integer.\033[0m\n");
                while (getchar() != '\n')
                    ;
            }

        } while (validInput != 1);
        printf("\n");
        switch (choice)

        {
        case 1:
            addCrop();
            break;
        case 2:
            viewCrops();
            break;
        case 3:
            updateCropStatus();
            break;
        case 4:
            deleteCrop();
            break;
        case 5:
            return;
        default:
            printf("\033[1;31mInvalid choice. Please try again.\033[0m\n");
        }
    } while (choice != 5);
}

void addCrop()
{
    // Dynamically allocate or reallocate memory for crops
    crops = realloc(crops, sizeof(Crop) * (cropCount + 1));
    if (crops == NULL)
    {
        perror("Failed to allocate memory for new crop");
        holdingTerminal();
        return;
    }

    Crop newCrop;
    printf("Enter Crop Name: ");
    scanf("%s", &newCrop.name);

    printf("Enter Area (in hectares): ");
    scanf("%f", &newCrop.area);

    printf("Enter Yield (in tons): ");
    scanf("%f", &newCrop.yield);

    printf("Enter Planting Date (YYYY-MM-DD): ");
    scanf("%s", &newCrop.plantingDate);

    printf("Enter Harvest Date (YYYY-MM-DD): ");
    scanf("%s", &newCrop.harvestDate);

    printf("Enter Status (Planted | Harvested | Ready to Harvest): ");
    scanf("%s", &newCrop.status);

    crops[cropCount++] = newCrop;

    printf("\033[1;32mCrop Added Successfully!\033[0m\n");
    holdingTerminal();
}

void viewCrops()
{
    if (cropCount == 0)
    {
        printf("\033[1;31mNo crops available to display.\033[0m\n");
        holdingTerminal();
        return;
    }

    printf("\n\033[1;32mCrop Details:\033[0m\n");
    printf("\033[1;37m+-----+---------------------+----------------+----------------+------------------+------------------+------------------+\033[0m\n");
    printf("\033[1;37m|\033[1;36m No. \033[1;37m|\033[1;36m Name                \033[1;37m|\033[1;36m Area (hectares)\033[1;37m|\033[1;36m Yield (tons)   \033[1;37m|\033[1;36m Planting Date    \033[1;37m|\033[1;36m Harvest Date     \033[1;37m|\033[1;36m Status           \033[1;37m|\033[0m\n");
    printf("\033[1;37m+-----+---------------------+----------------+----------------+------------------+------------------+------------------+\033[0m\n");

    for (int i = 0; i < cropCount; i++)
    {
        printf("\033[1;37m| \033[1;33m%-3d \033[1;37m| %-19s | %-14.2f | %-14.2f | %-16s | %-16s | %-16s |\033[0m\n",
               i + 1, crops[i].name, crops[i].area, crops[i].yield, crops[i].plantingDate, crops[i].harvestDate, crops[i].status);
    }

    printf("\033[1;37m+-----+---------------------+----------------+----------------+------------------+------------------+------------------+\033[0m\n");
    holdingTerminal();
}

void updateCropStatus()
{
    if (cropCount == 0)
    {
        printf("\033[1;31mNo crops available to update.\033[0m\n");
        holdingTerminal();
        return;
    }

    char cropName[50];
    int cropFound = 0;

    printf("Enter the name of the crop to update: ");
    scanf("%s", cropName);

    for (int i = 0; i < cropCount; i++)
    {
        if (strcmp(lowerCase(crops[i].name), lowerCase(cropName)) == 0)
        {
            cropFound = 1;
            printf("\033[1;36mUpdating status for crop '%s':\033[0m\n", crops[i].name);

            printf("\033[1;31mAvoid using spaces. Instead use _\033[0m\n");
            printf("Enter new Status (Planted | Harvested | Ready_to_Harvest) [current: %s]: ", crops[i].status);
            scanf("%s", crops[i].status);

            printf("\033[1;32mCrop Status Updated Successfully!\033[0m\n");
            break;
        }
    }

    if (!cropFound)
    {
        printf("\033[1;31mNo crop found with the name '%s'.\033[0m\n", cropName);
    }
    holdingTerminal();
}

void deleteCrop()
{
    if (cropCount == 0)
    {
        printf("\033[1;31mNo crops available to delete.\033[0m\n");
        holdingTerminal();
        return;
    }

    char cropName[50];
    int cropIndex = -1;

    printf("Enter the name of the crop to delete: ");
    scanf("%s", cropName);

    for (int i = 0; i < cropCount; i++)
    {
        if (strcmp(lowerCase(crops[i].name), lowerCase(cropName)) == 0)
        {
            cropIndex = i;
            break;
        }
    }

    if (cropIndex == -1)
    {
        printf("\033[1;31mNo crop found with the name '%s'.\033[0m\n", cropName);
        holdingTerminal();
        return;
    }

    for (int i = cropIndex; i < cropCount - 1; i++)
    {
        crops[i] = crops[i + 1];
    }

    // Reallocate memory to shrink the array
    crops = realloc(crops, sizeof(Crop) * (cropCount - 1));
    if (crops == NULL && cropCount > 1)
    {
        perror("Failed to reallocate memory for crops");
        holdingTerminal();
        return;
    }

    cropCount--;
    printf("\033[1;32mCrop '%s' deleted successfully!\033[0m\n", cropName);
    holdingTerminal();
}

void irrigationSchedulingMenu()
{
    int choice, validInput;

    do
    {
        printf("\n\033[1;35mIrrigation Scheduling Menu\033[0m\n");
        printf("\033[1;35m------------------------------------------------------\033[0m\n");
        printf("\033[1;37m1.\033[0m Input Field Data\n");
        printf("\033[1;37m2.\033[0m Calculate Irrigation Need\n");
        printf("\033[1;37m3.\033[0m Calculate Water Requirement\n");
        printf("\033[1;37m4.\033[0m Generate Irrigation Schedule\n");
        printf("\033[1;37m5.\033[0m Back to Main Menu\n");
        do
        {
            printf("Enter your choice: ");
            validInput = scanf("%d", &choice);

            if (validInput != 1)
            {
                printf("\033[1;31mInvalid input. Please enter only an integer.\033[0m\n");
                while (getchar() != '\n')
                    ;
            }

        } while (validInput != 1);
        printf("\n");
        switch (choice)

        {
        case 1:
            inputFieldData();
            break;
        case 2:
            calculateIrrigationNeed();
            break;
        case 3:
            calculateWaterRequirement();
            break;
        case 4:
            generateIrrigationSchedule();
            break;
        case 5:
            return;
        default:
            printf("\033[1;31mInvalid choice. Please try again.\033[0m\n");
        }
    } while (choice != 5);
}

void inputFieldData()
{
    int validInput;
    fields = realloc(fields, sizeof(Field) * (fieldCount + 1));
    if (fields == NULL)
    {
        perror("Failed to allocate memory for new field");
        holdingTerminal();
        return;
    }

    Field newField;

    printf("Enter Crop Type: ");
    scanf("%s", newField.cropType);

    do
    {
        printf("Enter Area (in acres): ");
        validInput = scanf("%f", &newField.area);

        if (validInput != 1)
        {
            printf("\033[1;31mInvalid input. Please enter a valid number for area.\033[0m\n");
            while (getchar() != '\n')
                ;
        }
    } while (validInput != 1);

    do
    {
        printf("Enter Current Soil Moisture Level (percentage): ");
        validInput = scanf("%f", &newField.soilMoisture);

        if (newField.soilMoisture < 0 || newField.soilMoisture > 100)
        {
            validInput = 0;
            newField.soilMoisture = 0;
        }

        if (validInput != 1)
        {
            printf("\033[1;31mInvalid input. Please enter a valid percentage.\033[0m\n");
            while (getchar() != '\n')
                ;
        }
    } while (validInput != 1);

    fields[fieldCount++] = newField;

    printf("\033[1;32mField Data Added Successfully!\033[0m\n");
    holdingTerminal();
}

void calculateIrrigationNeed()
{
    if (fieldCount == 0)
    {
        printf("\033[1;31mNo fields available to calculate irrigation need.\033[0m\n");
        printf("\033[1;33mFirst of all Select option No. 1 and Input FIeld Data.\033[0m\n");
        holdingTerminal();
        return;
    }
    for (int i = 0; i < fieldCount; i++)
    {
        int irrigationNeeded = fields[i].soilMoisture < 40.0 ? 1 : 0;
        if (irrigationNeeded)
        {
            printf("\033[1;33mField %d\033[0m (Crop: %s) requires irrigation.\n", i + 1, fields[i].cropType);
        }
        else
        {
            printf("Field %d (Crop: %s) does not require irrigation.\n", i + 1, fields[i].cropType);
        }
    }
    holdingTerminal();
}

void calculateWaterRequirement()
{
    if (fieldCount == 0)
    {
        printf("\033[1;31mNo fields available to calculate Water Requirement.\033[0m\n");
        printf("\033[1;33mFirst of all Select option No. 1 and Input FIeld Data.\033[0m\n");
        holdingTerminal();
        return;
    }
    for (int i = 0; i < fieldCount; i++)
    {
        float waterNeeded = fields[i].area * (100 - fields[i].soilMoisture) * 10;
        printf("Field %d (Crop: %s) needed %.1f litres of water.\n", i + 1, fields[i].cropType, waterNeeded);
    }
    holdingTerminal();
}

void generateIrrigationSchedule()
{
    if (fieldCount == 0)
    {
        printf("\033[1;31mNo fields available to calculate irrigation need.\033[0m\n");
        printf("\033[1;33mFirst of all Select option No. 1 and Input FIeld Data.\033[0m\n");
        holdingTerminal();
        return;
    }

    printf("\033[1;37m+-------+---------------------+-------------------+---------------------+\033[0m\n");
    printf("\033[1;37m|\033[1;36m Field \033[1;37m|\033[1;36m Crop                \033[1;37m|\033[1;36m Water Needed      \033[1;37m|\033[1;36m Irrigation Needed   \033[1;37m|\033[0m\n");
    printf("\033[1;37m+-------+---------------------+-------------------+---------------------+\033[0m\n");

    for (int i = 0; i < fieldCount; i++)
    {
        float waterNeeded = fields[i].area * (100 - fields[i].soilMoisture) * 10;
        int irrigationNeeded = fields[i].soilMoisture < 40.0 ? 1 : 0;

        printf("\033[1;37m| \033[1;33m%-5d \033[1;37m| %-19s | %-13.1f ltr | %-19s |\033[1;\n", i + 1, fields[i].cropType, waterNeeded, irrigationNeeded == 1 ? "Yes" : "No");
    }
    printf("\033[1;37m+-------+---------------------+-------------------+---------------------+\033[0m\n");
    holdingTerminal();
}

void expenseTrackingMenu()
{
    int choice, validInput;

    do
    {
        printf("\n\033[1;35mExpense Tracking Menu\033[0m\n");
        printf("\033[1;35m------------------------------------------------------\033[0m\n");
        printf("\033[1;37m1.\033[0m Add Expenses\n");
        printf("\033[1;37m2.\033[0m View Monthly Expenses\n");
        printf("\033[1;37m3.\033[0m Calculate Total and Average Expenses\n");
        printf("\033[1;37m4.\033[0m View Expense Log\n");
        printf("\033[1;37m5.\033[0m Back to Main Menu\n");
        do
        {
            printf("Enter your choice: ");
            validInput = scanf("%d", &choice);

            if (validInput != 1)
            {
                printf("\033[1;31mInvalid input. Please enter only an integer.\033[0m\n");
                while (getchar() != '\n')
                    ;
            }

        } while (validInput != 1);
        printf("\n");
        switch (choice)

        {
        case 1:
            addExpense();
            break;
        case 2:
            viewMonthlyExpenses();
            break;
        case 3:
            calculateTotalAndAverageExpenses();
            break;
        case 4:
            viewExpenseLog();
            break;
        case 5:
            return;
        default:
            printf("\033[1;31mInvalid choice. Please try again.\033[0m\n");
        }
    } while (choice != 5);
}

void addExpense()
{
    int validInput;
    expenses = realloc(expenses, sizeof(Expense) * (expenseCount + 1));
    if (expenses == NULL)
    {
        perror("Failed to allocate memory for new expense");
        holdingTerminal();
        return;
    }

    Expense newExpense;
    printf("Enter Expense Category: ");
    scanf("%s", &newExpense.category);

    printf("\033[1;31mAvoid using spaces. Instead use _\033[0m\n");
    printf("Enter Expense Description: ");
    scanf("%s", &newExpense.description);

    do
    {
        printf("Enter Expense Amount: ");
        validInput = scanf("%f", &newExpense.amount);

        if (validInput != 1)
        {
            printf("\033[1;31mInvalid input. Please enter a positive number for the amount.\033[0m\n");
            while (getchar() != '\n')
                ;
        }
    } while (validInput != 1);

    expenses[expenseCount++] = newExpense;

    printf("\033[1;32mExpenses Added Successfully!\033[0m\n");

    holdingTerminal();
}

void viewMonthlyExpenses()
{
    if (expenseCount == 0)
    {
        printf("\033[1;31mNo crops available to display.\033[0m\n");
        holdingTerminal();
        return;
    }

    printf("\n\033[1;32mMonthly Expenses:\033[0m\n");
    printf("\033[1;37m+-----+-----------------+-----------------+----------------------------------+\033[0m\n");
    printf("\033[1;37m|\033[1;36m No. \033[1;37m|\033[1;36m Category        \033[1;37m|\033[1;36m Amount          \033[1;37m|\033[1;36m Description                      \033[1;37m|\033[0m\n");
    printf("\033[1;37m+-----+-----------------+-----------------+----------------------------------+\033[0m\n");

    for (int i = 0; i < expenseCount; i++)
    {
        printf("\033[1;37m| \033[1;33m%-3d \033[1;37m| %-15s | $%-14.2f | %-32s |\033[0m\n", i + 1, expenses[i].category, expenses[i].amount, expenses[i].description);
    }

    printf("\033[1;37m+-----+-----------------+-----------------+----------------------------------+\033[0m\n");
    holdingTerminal();
}

void calculateTotalAndAverageExpenses()
{
    if (expenseCount == 0)
    {
        printf("\033[1;31mNo expenses available to calculate.\033[0m\n");
        holdingTerminal();
        return;
    }

    float totalExpenses = 0.0;

    for (int i = 0; i < expenseCount; i++)
    {
        totalExpenses += expenses[i].amount;
    }

    float averageExpenses = totalExpenses / expenseCount;

    printf("\033[1;32mExpense Summary:\033[0m\n");
    printf("\033[1;37mTotal Expenses: $ %.2f\033[0m\n", totalExpenses);
    printf("\033[1;37mAverage Expense: $ %.2f\033[0m\n", averageExpenses);
    holdingTerminal();
}

void viewExpenseLog()
{
    if (expenseCount == 0)
    {
        printf("\033[1;31mNo expenses available to display.\033[0m\n");
        holdingTerminal();
        return;
    }

    printf("\n\033[1;32mExpense Log:\033[0m\n");
    printf("\033[1;37m+-----+-----------------+-----------------+----------------------------------+\033[0m\n");
    printf("\033[1;37m|\033[1;36m No. \033[1;37m|\033[1;36m Category        \033[1;37m|\033[1;36m Amount          \033[1;37m|\033[1;36m Description                      \033[1;37m|\033[0m\n");
    printf("\033[1;37m+-----+-----------------+-----------------+----------------------------------+\033[0m\n");

    for (int i = 0; i < expenseCount; i++)
    {
        printf("\033[1;37m| \033[1;33m%-3d \033[1;37m| %-15s | $%-14.2f | %-32s |\033[0m\n", i + 1, expenses[i].category, expenses[i].amount, expenses[i].description);
    }

    printf("\033[1;37m+-----+-----------------+-----------------+----------------------------------+\033[0m\n");
    holdingTerminal();
}

void loadData()
{
    fp = fopen(FILENAME, "r");
    if (fp == NULL)
    {
        perror("Failed to open file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int section = 0; // 0: none, 1: crops, 2: expenses

    while (fgets(line, sizeof(line), fp))
    {
        // Determine which section of the file we're reading
        if (strncmp(line, "Crops:", 6) == 0)
        {
            section = 1;
            continue;
        }
        else if (strncmp(line, "Expenses:", 9) == 0)
        {
            section = 2;
            continue;
        }

        // Read Crop data
        if (section == 1 && line[0] != '\n')
        {
            Crop crop;
            sscanf(line, "%s %f %f %s %s %s", crop.name, &crop.area, &crop.yield, crop.plantingDate, crop.harvestDate, crop.status);
            crops = realloc(crops, sizeof(Crop) * (cropCount + 1));
            if (crops == NULL)
            {
                perror("Failed to allocate memory for crops");
                fclose(fp);
                return;
            }
            crops[cropCount++] = crop;
        }
        // Read Expense data
        else if (section == 2 && line[0] != '\n')
        {
            Expense expense;
            sscanf(line, "%s %f %s", expense.category, &expense.amount, expense.description);
            expenses = realloc(expenses, sizeof(Expense) * (expenseCount + 1));
            if (expenses == NULL)
            {
                perror("Failed to allocate memory for expenses");
                fclose(fp);
                return;
            }
            expenses[expenseCount++] = expense;
        }
    }

    fclose(fp);
    printf("Data loaded successfully!\n");
}

void saveData()
{
    fp = fopen(FILENAME, "w");
    if (fp == NULL)
    {
        perror("Failed to open file");
        return;
    }

    fprintf(fp, "Crops:\n");
    for (int i = 0; i < cropCount; i++)
    {
        fprintf(fp, "%s %.2f %.2f %s %s %s\n", crops[i].name, crops[i].area, crops[i].yield, crops[i].plantingDate, crops[i].harvestDate, crops[i].status);
    }

    fprintf(fp, "Expenses:\n");
    for (int i = 0; i < expenseCount; i++)
    {
        fprintf(fp, "%s %.2f %s\n", expenses[i].amount, expenses[i].category, expenses[i].description);
    }

    fclose(fp);
    printf("Data saved successfully!\n");
}

char *lowerCase(char *s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}
