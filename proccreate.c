/* runs each build command in a new process
* waits for completion
* gets the return code
*/

#include "proccreate.h"
#include <sys/types.h>
#include <stat.h>
#include <unistd.h>

/*TODO:
* get strings from specification
* seperate strings into targets & dependencies
* seperate strings into commands & arguments
*/
int run_command(char target, char *target_array) {
        
    char* argv[MAX_ARGS];
    pid_t child_pid;
    int child_status;
    struct stat *buf = malloc(sizeof(struct stat));

    /* target check */
    if (stat (t->name, buf) == 0) {
        // if target is a file name -> its time is the modification time of the named file
        target_time = buf->st_mtime; 
    } else {
        // if target is not a file name -> time = 0
        target_time = 0;
    }
    
    // iterate through dependencies
    for (int k = 0; k < num_dependencies; k++) {
        // dependence name is another target and that target is out of date
        for (int j=0; j < num_targets; j++) {
            // TODO: how to get name of iterated target?
            if (t->dependencies[k] == target_array[j]->name) {
                // check st_mtime for that target
                if ()         
                    // if out of date, run commands
            }
         }
        
        /* command is run if dependence is out of date (check the 3 criteria) */
        if (stat (t->dependencies[k], buf) == 0) {
            // dependence name is a file whose modification time is more recent then the time of the target
            dep_time = buf->st_mtime;
            if (dep_time > target_time)
                // run commands
        } else if (t->dependencies[k] == NULL) {
            // no dependencies
            // commands always run
        }
    }

    /* TODO:
    * put together top piece and bottom piece
    * overlay itself (exec) the command in the file named by "cmd"
    * command line is parsed by your program into a list of character strings
    * arguments are passed as parameters to the exec command
    */ 
    
    // fork a child process
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
            pid_t tpid = wait(&child_status);
            if(tpid != child_pid) process_terminated(tpid);
        } while(tpid != child_pid);

        return child_status;
    }
}
