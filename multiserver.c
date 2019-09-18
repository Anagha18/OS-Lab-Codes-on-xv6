#include <stdio.h>
#include <stdlib.h>  	      // strlen function
#include <string.h>           // strlen function
#include <sys/socket.h>       // socket system calls
#include <unistd.h>           // write system calls
#include <arpa/inet.h>        // inet_addr structure
#include <fcntl.h>            // O_RDONLY flag
#include <pthread.h>          // Threads, link with lpthread
#include <semaphore.h>        // Semaphore init(), sem_wait() and sem_post()

#define BUF_LEN 4096		// Buffer Length constant size
int *new_sock;			

pthread_t t_producer;		// Producer Thread Variable
pthread_t t_consumer;		// Consumer Thread Variable

sem_t buf_mutex, empty_count, fill_count;	// Mutex variables
						// buf_mutex checks buffer LOCKED(0) or UNLOCKED(1)
						// empty_count checks buffer EMPTY(0) or NOTEMPTY(1)
						// fill_count checks buffer FULL(0) or NOTFULL(1)

char buff[BUF_LEN];				// Character buffer array
int server_socket, client_sock, c;		// Client and Server Socket variable

struct sockaddr_in server, client;		// Address structure for Client and Server


int produce()
{
  // TODO:  Use open() system call to open the file and write it to a character buffer "buff"
	int fd=open(sock,O_RDONLY);
	if(fd<0)
	{
		printf("Error Reading\n");
		exit(0);
	}
	//write(
}

int consume()
{
    sleep(3);

    int sock = *(int *)new_sock;

    write(sock, buff, BUF_LEN);

    printf("In consumer %s",buff);

    // TODO:  Read from the buffer written in produce() function and send it to client using write() system call, using the "sock" file descriptor.
	read(sock,buff,BUF_LEN);
}

void* producer(void *args)
{
	// TODO:  Use the three mutex variables, use sem_wait() and sem_post()
	sem_wait(&t_consumer);
	produce();
	sem_post(&t_producer);
	//return NULL;
	/*int i,sum=0;//on stack
	for(i=0;i<10;i++)
	{

		while(stock_max_limit==stock_count)
		{
			printf("\n stock overflow, production on wait..");
			sem_wait(&semC);//waiting for semophore of consumer
			printf("\n production operation continues..");
		}

	sleep(1);
	stock_count ++;
	printf("P :: stock-count:%d\n", stock_count);
	sem_post(&semP);
	printf("P :: post signal\n");
	
	}
*/
	return NULL;
}


void* consumer(void *args)
{
	// TODO:  Use the three mutex variables, use sem_wait() and sem_post()
  	sem_wait(&t_producer);
	consume();
	sem_post(&t_consumer);
	//return NULL;
	/*int i,sum=0;//on stack
	for(i=0;i<10;i++)
	{

		while(0==stock_count)//loop to wait for producer to complete. 
		{
			printf("\n stock overflow, consumption on wait..");
			sem_wait(&semP);//waiting for semophore of consumer
			printf("\n consumption operation continues..");
		}

	sleep(2);
	stock_count --;
	printf("C :: stock-count:%d\n", stock_count);
	sem_post(&semC);
	if()
	printf("C :: post signal\n");//signal: producer produced

	}
*/
	return NULL;
}

int main(void) 
{
	server_socket = socket(AF_INET, SOCK_STREAM, 0);    	// Create socket

	if (server_socket == -1) 				// Check create Socket ERROR=-1
    	{
	      	printf("\nCould not create Socket\n");
    	}

        puts("\nSocket created\n");				// Print Socket Created Sucessfully	

		// Prepare the sockaddr_in structure

        server.sin_family = AF_INET;				// Intialize Address Family
        server.sin_addr.s_addr = INADDR_ANY;			// Intialize Address Type
        server.sin_port = htons(5050);				//Port No :5050

		// Bind socket with sockaddr_in structure

        if(bind(server_socket, (struct sockaddr *)&server, sizeof(server))<0) 
        {
           perror("\nBind Failed. Error\n");	// Print the bind ERROR=-1 message

           return 1;
        }

        puts("\nBind Done\n");			// Bind Successful

        for (size_t i = 0; i < BUF_LEN; i++) 	// Intialize Buffer with 0
        {
           buff[i] = 0;
        }

        listen(server_socket, 3);		// Server Listens, Backlog=3 Clients

        c = sizeof(struct sockaddr_in);

        // Accept and incoming connection

        puts("Waiting for incoming connections...");

        client_sock=accept(server_socket,(struct sockaddr *)&client,(socklen_t *)&c); // Server accepts connection

        new_sock = malloc(1);

       *new_sock = client_sock;

       int err;					// Error variable

       sem_init(&buf_mutex, 0, 1);		// Intialize buf_mutex to 1(BUFFER UNLOCKED/FREE), 0 means Threads
       sem_init(&fill_count, 0, 0);		// Intialize fill_count to 0 (BUFFER FULL)
       sem_init(&empty_count, 0, BUF_LEN); 	// Intialize empty_count to BUF_LEN=4096 (EMPTY)

    // TODO: Create 2 threads t_producer and t_consumer, with producer() and consumer() as their callback functions.
    // TODO: Join the 2 threads
	sem_init(&t_producer,0,0);//binary semaphore
	sem_init(&t_consumer,0,0);
	pthread_create(&t_consumer,NULL,consumer,NULL);
	pthread_create(&t_producer,NULL,producer,NULL);
	pthread_join(t_consumer,NULL);
	pthread_join(t_producer,NULL);
	sem_destroy(&t_consumer);
	sem_destroy(&t_producer);
	

	close(server_socket); 		// Close Server Socket
        close(client_sock);		// Close Client Socket

	return 0;
}

