#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct
{
    int id;
    char caller[50];
    char service[20];
    char location[100];
    int priority;
    char status[20];
} Emergency;

/* Queue for Pending Emergencies */
Emergency queue[MAX];
int front = -1;
int rear = -1;

/* Stack for Completed Emergencies */
Emergency completedStack[MAX];
int top = -1;

/* Global Variables */
int nextId = 1;

int totalRequests = 0;
int ambulanceCount = 0;
int fireCount = 0;
int policeCount = 0;

/* Function Prototypes */
void registerEmergency();
void viewPendingEmergencies();
void dispatchEmergency();
void viewLastCompleted();
void viewCompletedHistory();
void undoLastCompletion();
void searchEmergencyById();
void dashboardStatistics();
void saveHistoryToFile();

int isQueueEmpty();
int isStackEmpty();

void enqueue(Emergency e);
void push(Emergency e);
Emergency pop();

/* Queue Functions */

int isQueueEmpty()
{
    return (front == -1);
}

void enqueue(Emergency e)
{
    if (rear == MAX - 1)
    {
        printf("\nQueue is Full!\n");
        return;
    }

    if (front == -1)
        front = 0;

    queue[++rear] = e;
}

/* Stack Functions */

int isStackEmpty()
{
    return (top == -1);
}

void push(Emergency e)
{
    if (top == MAX - 1)
    {
        printf("\nHistory Stack Full!\n");
        return;
    }

    completedStack[++top] = e;
}

Emergency pop()
{
    Emergency temp;

    temp.id = -1;

    if (isStackEmpty())
        return temp;

    return completedStack[top--];
}

/* Register Emergency */

void registerEmergency()
{
    Emergency e;

    e.id = nextId++;

    printf("\nEnter Caller Name: ");
    scanf(" %[^\n]", e.caller);

    printf("Enter Service (Ambulance/Fire/Police): ");
    scanf("%s", e.service);

    printf("Enter Location: ");
    scanf(" %[^\n]", e.location);

    printf("Priority Level\n");
    printf("1. High\n");
    printf("2. Medium\n");
    printf("3. Low\n");
    printf("Enter Priority: ");
    scanf("%d", &e.priority);

    strcpy(e.status, "Pending");

    enqueue(e);

    totalRequests++;

    if (strcmp(e.service, "Ambulance") == 0)
        ambulanceCount++;
    else if (strcmp(e.service, "Fire") == 0)
        fireCount++;
    else if (strcmp(e.service, "Police") == 0)
        policeCount++;

    printf("\nEmergency Registered Successfully!");
    printf("\nEmergency ID: %d\n", e.id);
}

/* View Pending Emergencies */

void viewPendingEmergencies()
{
    int i;

    if (isQueueEmpty())
    {
        printf("\nNo Pending Emergencies.\n");
        return;
    }

    printf("\n========== PENDING EMERGENCIES ==========\n");

    for (i = front; i <= rear; i++)
    {
        printf("\nID       : %d", queue[i].id);
        printf("\nCaller   : %s", queue[i].caller);
        printf("\nService  : %s", queue[i].service);
        printf("\nLocation : %s", queue[i].location);
        printf("\nPriority : %d", queue[i].priority);
        printf("\nStatus   : %s\n", queue[i].status);
    }
}

/* Dispatch Highest Priority Emergency */

void dispatchEmergency()
{
    int i;
    int highestIndex;

    if (isQueueEmpty())
    {
        printf("\nNo Pending Emergencies.\n");
        return;
    }

    highestIndex = front;

    for (i = front + 1; i <= rear; i++)
    {
        if (queue[i].priority < queue[highestIndex].priority)
        {
            highestIndex = i;
        }
    }

    Emergency current = queue[highestIndex];

    for (i = highestIndex; i < rear; i++)
    {
        queue[i] = queue[i + 1];
    }

    rear--;

    if (rear < front)
    {
        front = -1;
        rear = -1;
    }

    strcpy(current.status, "Completed");

    push(current);

    printf("\n===== EMERGENCY DISPATCHED =====\n");
    printf("ID       : %d\n", current.id);
    printf("Caller   : %s\n", current.caller);
    printf("Service  : %s\n", current.service);
    printf("Location : %s\n", current.location);

    if (current.priority == 1)
        printf("Priority : High\n");
    else if (current.priority == 2)
        printf("Priority : Medium\n");
    else
        printf("Priority : Low\n");
}

/* View Last Completed */

void viewLastCompleted()
{
    if (isStackEmpty())
    {
        printf("\nNo Completed Emergencies.\n");
        return;
    }

    Emergency e = completedStack[top];

    printf("\n===== LAST COMPLETED EMERGENCY =====\n");

    printf("ID       : %d\n", e.id);
    printf("Caller   : %s\n", e.caller);
    printf("Service  : %s\n", e.service);
    printf("Location : %s\n", e.location);
    printf("Status   : %s\n", e.status);
}

/* View Completed History */

void viewCompletedHistory()
{
    int i;

    if (isStackEmpty())
    {
        printf("\nNo Completed History Available.\n");
        return;
    }

    printf("\n===== COMPLETED HISTORY =====\n");

    for (i = top; i >= 0; i--)
      {
        printf("\nID       : %d", completedStack[i].id);
        printf("\nCaller   : %s", completedStack[i].caller);
        printf("\nService  : %s", completedStack[i].service);
        printf("\nLocation : %s", completedStack[i].location);
        printf("\nStatus   : %s\n", completedStack[i].status);
    }
}

/* Undo Last Completion */

void undoLastCompletion()
{
    if (isStackEmpty())
    {
        printf("\nNothing To Undo.\n");
        return;
    }

    Emergency e = pop();

    strcpy(e.status, "Pending");

    enqueue(e);

    printf("\nUndo Successful!\n");
    printf("Emergency ID %d Restored To Queue.\n", e.id);
}

/* Search Emergency */

void searchEmergencyById()
{
    int id;
    int found = 0;
    int i;

    printf("\nEnter Emergency ID: ");
    scanf("%d", &id);

    for (i = front; i <= rear; i++)
    {
        if (!isQueueEmpty() && queue[i].id == id)
        {
            printf("\nFound In Pending Queue");
            printf("\nCaller  : %s", queue[i].caller);
            printf("\nService : %s\n", queue[i].service);
            found = 1;
        }
    }

    for (i = 0; i <= top; i++)
    {
        if (completedStack[i].id == id)
        {
            printf("\nFound In Completed History");
            printf("\nCaller  : %s", completedStack[i].caller);
            printf("\nService : %s\n", completedStack[i].service);
            found = 1;
        }
    }

    if (!found)
    {
        printf("\nEmergency ID Not Found.\n");
    }
}

/* Dashboard */

void dashboardStatistics()
{
    int pending = 0;
    int completed = top + 1;

    if (!isQueueEmpty())
        pending = rear - front + 1;

    printf("\n========== DASHBOARD ==========\n");

    printf("\nTotal Requests      : %d", totalRequests);
    printf("\nPending Emergencies : %d", pending);
    printf("\nCompleted Cases     : %d", completed);

    printf("\n\n----- SERVICE BREAKDOWN -----\n");
    printf("Ambulance Calls : %d\n", ambulanceCount);
    printf("Fire Calls      : %d\n", fireCount);
    printf("Police Calls    : %d\n", policeCount);
}

/* Save History */

void saveHistoryToFile()
{
    FILE *fp;
    int i;

    fp = fopen("history.txt", "w");

    if (fp == NULL)
    {
        printf("\nUnable To Create File.\n");
        return;
    }

    fprintf(fp, "EMERGENCY SERVICE MANAGEMENT SYSTEM\n");
    fprintf(fp, "COMPLETED EMERGENCY HISTORY\n\n");

    for (i = top; i >= 0; i--)
    {
        fprintf(fp, "ID       : %d\n", completedStack[i].id);
        fprintf(fp, "Caller   : %s\n", completedStack[i].caller);
        fprintf(fp, "Service  : %s\n", completedStack[i].service);
        fprintf(fp, "Location : %s\n", completedStack[i].location);
        fprintf(fp, "Status   : %s\n", completedStack[i].status);
        fprintf(fp, "-----------------------------------\n");
    }

    fclose(fp);

    printf("\nHistory Saved Successfully To history.txt\n");
}

/* Main Function */

int main()
{
    int choice;

    do
    {
        printf("\n");
        printf("=========================================\n");
        printf(" Emergency Service Management System\n");
        printf("=========================================\n");

        printf("1. Register Emergency\n");
        printf("2. View Pending Emergencies\n");
        printf("3. Dispatch Emergency\n");
        printf("4. View Last Completed Emergency\n");
        printf("5. View Completed History\n");
        printf("6. Undo Last Completion\n");
        printf("7. Search Emergency By ID\n");
        printf("8. Dashboard Statistics\n");
        printf("9. Save History To File\n");
        printf("10. Exit\n");

        printf("\nEnter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            registerEmergency();
            break;

        case 2:
            viewPendingEmergencies();
            break;

        case 3:
            dispatchEmergency();
            break;

        case 4:
            viewLastCompleted();
            break;

        case 5:
            viewCompletedHistory();
            break;

        case 6:
            undoLastCompletion();
            break;

        case 7:
            searchEmergencyById();
            break;

        case 8:
            dashboardStatistics();
            break;

        case 9:
            saveHistoryToFile();
            break;

        case 10:
            printf("\nThank You For Using SERS!\n");
            break;

        default:
            printf("\nInvalid Choice!\n");
        }

    } while (choice != 10);

    return 0;
}