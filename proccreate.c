/* runs each build command in a new process
* waits for completion
* gets the return code
*/

#include "proccreate.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "buildrep.h"
#include <stdio.h>

static int MAX_ARGS = 100; // Maximum number of arguments

void run_command(Target *target, Target *target_array, int *num_targets) {
        
    char* argv[MAX_ARGS]; // argument array of strings
    pid_t child_pid; // process id for child process
    int child_status; // status of child
    struct stat *buf = malloc(sizeof(struct stat)); // allocation of memory for stat struct
    Target *t = target;
    Target *curr = NULL;
    time_t dep_time;

    /* Target check */
    if (stat (t->name, buf) == 0) {
        // If target is a file name -> its time is the modification time of the named file
        t->modTime = buf->st_mtime; 
    } else {
        // If target is not a file name -> time = 0
        t->modTime = 0;
    }
    
    /* Command line is put into a list of arguments */
    for (int b=0; b < t->num_command_lines; b++) {
        argv[b] = t->command_lines[0];
    }

    /* Iterate through dependencies */
    for (int k = 0; k < t->num_dependencies; k++) {
        // Dependence name is another target and that target is out of date
        for (int j=0; j < num_targets; j++) {
            *curr = target_array[j];
            if (t->dependencies[k] == curr->name) {
                // If target time is out of date
                if (buf->st_mtime > curr->modTime)         
                    create_process(argv);
            }
         }
        // If dependence name is a file whose modification time is more recent then the time of the target        
        if (stat (t->dependencies[k], buf) == 0) {
            dep_time = buf->st_mtime;
            if (dep_time > t->modTime) {
                // Run commands
                create_process(argv);
            }
        } else if (t->dependencies[k] == NULL) {
            // If there is no dependencies
            // Commands always run
            create_process(argv);
        }        
    }
}

/* Use fork and exec together to run the commands 
and check if they are valid */
int create_process(char *argv[]) {
    pid_t child_pid; // process id for child process
    pid_t ppid; // process id for parent process
    int child_status; // status of child
    
    // Fork a child process
    child_pid = fork();

    // This is done by the child process
    if(child_pid == 0) {
        // Arguments are passed as parameters to the exec command
        execvp(argv[0], argv);

        // If execvp returns, it must have failed
        printf("Error with command\n");
        exit(1);
     } else {
        // This is run by the parent
        do {
            // 537make (parent) process will wait for the child process
            ppid = wait(&child_status);
            if(ppid != child_pid) process_terminated(ppid);
        } while(ppid != child_pid);

        return child_status;
     }
}
