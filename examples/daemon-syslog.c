#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>

int main (void)
{
	pid_t pid;
	int i;
	/* создание нового процесса */
	pid = fork ();
	if (pid != 0)
		exit (EXIT_SUCCESS);
	/* создание новой сессии и группы процессов */
	setsid();
	/* установка в качестве рабочего каталога корневого каталога */
	if (chdir ("/") == -1)
		return -1;

	/* закрытие всех открытых файлов */	
	for (i = 0; i < 1024; i++)
		close (i);

	/* перенаправление дескрипторов файла 0,1,2 в /dev/null */
	open ("/dev/null", O_RDWR); /* stdin */
	dup (0); /* stdout */
	dup (0); /* stderror */
    
    openlog("MyDaemon", LOG_PID, LOG_DAEMON);
    syslog( LOG_ERR, "Hello from daemon\n" );

	sleep(10);

	return 0;
}