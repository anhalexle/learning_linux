#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <mqueue.h>
#include <errno.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <mqueue.h>
#include <errno.h>
#include <stdbool.h>

#define FILE_NAME "/mqueue"
#define MQ_OPTION (S_IRUSR | S_IWUSR)

typedef struct Person
{
    char Name[20];
    int Age;
    char HomeTown[20];
    char PhoneNumber[10];
} Person;

typedef struct Message
{
    unsigned int Priority_Id;
    Person person;
} Message;

static const Message EmptyStruct;

mqd_t Mymqueue;
Message Mymessage;
struct mq_attr attr;

long currentMsgInQueue(void)
{
    mq_getattr(Mymqueue, &attr);
    return attr.mq_curmsgs;
}

void DisplayMenu()
{
    printf("########################\n");
    printf("##_MESSAGE QUEUE DEMO_##\n");
    printf("########################\n");
    printf("1.-----Input data-------\n");
    printf("2.-----Show data by ID--\n");
    printf("3.-----Show all data----\n");
    printf("4.-----Delete data------\n");
    printf("0.-----Exit-------------\n");
}

void InputData();
bool CheckExistId();
void ShowDataById();

bool CheckExistId(unsigned int user_id_find)
{
    int count = (int)currentMsgInQueue();
    bool found = false;
    Message *messages = malloc(count * sizeof(Message));
    for (int i = 0; i < count; i++)
    {
        mq_receive(Mymqueue, (char *)&messages[i], attr.mq_msgsize, NULL);
        if ((unsigned int)messages[i].Priority_Id == user_id_find)
        {
            found = true;
        }
        mq_send(Mymqueue, (char *)&messages[i], sizeof(messages[i]), 0);
    }
    free(messages);
    return found;
}

void ShowDataById()
{
    unsigned int user_id_find;
    printf("Input user id to find: ");
    scanf("%d", &user_id_find);
    int count = (int)currentMsgInQueue();
    bool found = false;
    Message tempMessage;
    Message *messages = malloc(count * sizeof(Message));
    for (int i = 0; i < count; i++)
    {
        mq_receive(Mymqueue, (char *)&messages[i], attr.mq_msgsize, NULL);
        if ((unsigned int)messages[i].Priority_Id == user_id_find)
        {
            found = true;
            tempMessage = messages[i];
        }
        mq_send(Mymqueue, (char *)&messages[i], sizeof(messages[i]), 0);
    }
    free(messages);
    if (found)
    {
        printf("Person id: %d\n", tempMessage.Priority_Id);
        printf("Person name: %s\n", tempMessage.person.Name);
        printf("Person age: %d\n", tempMessage.person.Age);
        printf("Person Hometown: %s\n", tempMessage.person.HomeTown);
        printf("Person Phone: %s\n", tempMessage.person.PhoneNumber);
    }
    else
        printf("No %d in this list\n", user_id_find);
    printf("Current queue: %ld\n", currentMsgInQueue());
}

void InputData()
{
    Mymessage = EmptyStruct;
    bool isValid = false;
    printf("Input user id: ");
    while (!isValid)
    {
        scanf("%d", &Mymessage.Priority_Id);
        if ((int)currentMsgInQueue() != 0 && CheckExistId(Mymessage.Priority_Id))
        {
            printf("Id %d has exist\n", Mymessage.Priority_Id);
            printf("Input user id again: ");
        }
        else
            isValid = true;
    }
    while (getchar() != '\n')
        ;
    printf("Input Person name: ");
    fgets(Mymessage.person.Name, sizeof(Mymessage.person.Name), stdin);
    Mymessage.person.Name[strcspn(Mymessage.person.Name, "\n")] = '\0';
    printf("Input Person age: ");
    scanf("%d", &Mymessage.person.Age);
    while (getchar() != '\n')
        ;
    printf("Input Person hometown: ");
    fgets(Mymessage.person.HomeTown, sizeof(Mymessage.person.HomeTown), stdin);
    Mymessage.person.HomeTown[strcspn(Mymessage.person.HomeTown, "\n")] = '\0';
    printf("Input Person phone number: ");
    fgets(Mymessage.person.PhoneNumber, sizeof(Mymessage.person.PhoneNumber), stdin);
    Mymessage.person.PhoneNumber[strcspn(Mymessage.person.PhoneNumber, "\n")] = '\0';
    mq_send(Mymqueue, (char *)&Mymessage, sizeof(Mymessage), 0);
    printf("Current queue: %ld\n", currentMsgInQueue());
}

void ShowAllData()
{
    int count = (int)currentMsgInQueue();
    Message *message_array = malloc(count * sizeof(Message));
    if (count == 0)
    {
        printf("No data\n");
        free(message_array);
        return;
    }
    for (int i = 0; i < count; i++)
    {
        // remove the top of queue
        mq_receive(Mymqueue, (char *)&message_array[i], attr.mq_msgsize, NULL);
        printf("Person id: %d\n", message_array[i].Priority_Id);
        printf("Person name: %s\n", message_array[i].person.Name);
        printf("Person age: %d\n", message_array[i].person.Age);
        printf("Person Hometown: %s\n", message_array[i].person.HomeTown);
        printf("Person Phone: %s\n", message_array[i].person.PhoneNumber);
        // push to back of queue
        mq_send(Mymqueue, (char *)&message_array[i], sizeof(message_array[i]), 0);
    }
    free(message_array);
}

void DeleteById()
{
    unsigned int user_id_find;
    printf("Input user id to find: ");
    scanf("%d", &user_id_find);
    int count = (int)currentMsgInQueue();
    Message *message_array = malloc(count * sizeof(Message));
    int deletedNode = -1;
    for (int i = 0; i < count; i++)
    {
        mq_receive(Mymqueue, (char *)&message_array[i], attr.mq_msgsize, NULL);
        if (user_id_find == message_array[i].Priority_Id)
        {
            deletedNode = i;
            printf("Delete this node: \n");
            printf("Person id: %d\n", message_array[i].Priority_Id);
            printf("Person name: %s\n", message_array[i].person.Name);
            printf("Person age: %d\n", message_array[i].person.Age);
            printf("Person Hometown: %s\n", message_array[i].person.HomeTown);
            printf("Person Phone: %s\n", message_array[i].person.PhoneNumber);
        }
        if (i != deletedNode)
            mq_send(Mymqueue, (char *)&message_array[i], sizeof(message_array[i]), 0);
    }
    if (deletedNode == -1)
    {
        printf("No %d in this list\n", user_id_find);
    }
    free(message_array);
}

int main()
{
    mq_unlink(FILE_NAME);
    Mymqueue = mq_open(FILE_NAME, O_CREAT | O_RDWR | O_NONBLOCK, MQ_OPTION, NULL);
    printf("Number in queue: %ld\n", currentMsgInQueue());
    int choice;
    bool isExit = false;
    while (!isExit)
    {
        DisplayMenu();
        printf("Please select your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            InputData();
            break;
        case 2:
            ShowDataById();
            break;
        case 3:
            ShowAllData();
            break;
        case 4:
            DeleteById();
            break;
        default:
            break;
        }
    }
    mq_close(Mymqueue);
    mq_unlink(FILE_NAME);
    return 0;
}