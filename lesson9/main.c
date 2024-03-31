#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <errno.h>

#define MQ_MODE (S_IRUSR | S_IWUSR)

int main(int argc, char *argv[])
{
    struct mq_attr attrp;

    printf("Create message queue\n");

    // create message queue
    mqd_t mqid = mq_open("/mqueue", O_RDWR | O_CREAT | O_NONBLOCK, MQ_MODE, NULL);

    if (mqid == -1)
    {
        printf("mq_open() error %d: %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    // Get attribute
    if (mq_getattr(mqid, &attrp) == -1)
    {
        printf("mq_gettr() error %d: %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (attrp.mq_flags == 0)
    {
        printf("mq_flags = 0\n");
    }
    else
    {
        printf("mq_flags = 0_NONNBLOCK\n");
    }
    printf("mq_maxmsg = %ld\n", attrp.mq_maxmsg);
    printf("mq_msgsize = %ld\n", attrp.mq_msgsize);
    printf("mq_curmsgs = %ld\n", attrp.mq_curmsgs);

    // close mq_queue
    if (mq_close(mqid) == -1)
    {
        printf("mq_close() error %d: %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }
    mq_unlink("/mqueue");
    return 0;
}